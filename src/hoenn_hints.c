// Hoenn & Seek 2.0 (part 7): NPC hint lines, rumors, field notes and forecasts.
//
// Data: data/hoenn/npc_hints.json → tools/hoenn/gen_hoenn_hints.py →
// src/data/hoenn_hints.h (tables, included below) and data/scripts/hoenn_hints.inc
// (one wrapper script per hint NPC, the field-notes researcher, every text).
//
// Hint NPCs alternate: talking to any of them flips one global toggle
// (VAR_HOENN_HINT_TOGGLE), so one talk runs the NPC's own script and the next
// shows their extra line. There are no per-NPC flags. An NPC's extra line is the
// first of their lines whose conditions hold, so lines are listed in priority
// order (stories that expire first, then rumors and tips). Rumor lines say
// "before" until the rumor is found (its own conditions, e.g. the Pokémon was
// caught), then "after". Forecast lines show the first forecast that applies.
//
// The wrapper scripts look like this (generated):
//     callnative HoennSeek_NpcHint
//     .2byte <npc index>
//     goto_if_eq VAR_RESULT, FALSE, <the NPC's own script>
//     callstd MSGBOX_NPC
// HoennSeek_NpcHint leaves the text pointer in the script's data[0], which is
// exactly what msgbox's `loadword 0, text` would do, so callstd shows it.
#include "global.h"
#include "caps.h"
#include "event_data.h"
#include "fieldmap.h"
#include "hoenn.h"
#include "hoenn_hints.h"
#include "hoenn_time.h"
#include "pokedex.h"
#include "pokemon.h"
#include "script.h"
#include "string_util.h"
#include "constants/flags.h"
#include "constants/hoenn_events.h"
#include "constants/species.h"

#if IS_HNS

enum HoennHintCondType
{
    HINT_IF_FLAG,
    HINT_IF_NOT_FLAG,
    HINT_IF_VAR_MIN,
    HINT_IF_VAR_BELOW,
    HINT_IF_STAMPS_MIN,   // Hoenn gym badges (stamp flags)
    HINT_IF_STAMPS_BELOW,
    HINT_IF_BADGES_MIN,   // HnS's 16 Johto + Kanto badges
    HINT_IF_BADGES_BELOW,
    HINT_IF_CAUGHT,       // Pokédex caught flag
    HINT_IF_NOT_CAUGHT,
    HINT_IF_LEVEL_CAP,    // HnS's LEVEL CAP challenge setting is on
};

enum HoennHintKind
{
    HINT_TIP,
    HINT_STORY,
    HINT_RUMOR,
    HINT_FORECAST,
};

struct HoennHintCond
{
    u8 type;
    u16 id;     // flag, var or species
    u16 value;  // var / badge threshold
};

struct HoennHintRumor
{
    const struct HoennHintCond *found;
    u8 foundCount;
    const u8 *before;
    const u8 *after;
    const u8 *notes;  // the field-notes researcher's vague hint
};

struct HoennHintLine
{
    const struct HoennHintCond *conds;
    u8 condCount;
    const u8 *text;   // NULL for rumor and forecast lines
    u8 kind;
    u8 rumor;         // HINT_RUMOR: index into sHintRumors
};

struct HoennHintNpc
{
    const u8 *lines;  // indices into sHintLines, in priority order
    u8 lineCount;
    bool8 always;     // skip the toggle: the line comes first whenever one holds
};

struct HoennForecast
{
    u16 map;
    const struct HoennHintCond *conds;
    u8 condCount;
    const u8 *text;   // {STR_VAR_1} = "today" / "tomorrow"
    bool8 hoenn;      // shown in Hoenn (TRUE) or in Johto/Kanto (FALSE)
};

#include "data/hoenn_hints.h"

static const u8 sText_Today[] = _("today");
static const u8 sText_Tomorrow[] = _("tomorrow");

static u32 CountHnsBadges(void)
{
    u32 flag, count = 0;

    for (flag = FLAG_BADGE01_GET; flag <= FLAG_BADGE16_GET; flag++)
        if (FlagGet(flag))
            count++;
    return count;
}

static bool32 IsCaught(u16 species)
{
    return GetSetPokedexFlag(SpeciesToNationalPokedexNum(species), FLAG_GET_CAUGHT);
}

static bool32 CondHolds(const struct HoennHintCond *cond)
{
    switch (cond->type)
    {
    case HINT_IF_FLAG:         return FlagGet(cond->id);
    case HINT_IF_NOT_FLAG:     return !FlagGet(cond->id);
    case HINT_IF_VAR_MIN:      return VarGet(cond->id) >= cond->value;
    case HINT_IF_VAR_BELOW:    return VarGet(cond->id) < cond->value;
    case HINT_IF_STAMPS_MIN:   return HoennCountStamps() >= cond->value;
    case HINT_IF_STAMPS_BELOW: return HoennCountStamps() < cond->value;
    case HINT_IF_BADGES_MIN:   return CountHnsBadges() >= cond->value;
    case HINT_IF_BADGES_BELOW: return CountHnsBadges() < cond->value;
    case HINT_IF_CAUGHT:       return IsCaught(cond->id);
    case HINT_IF_NOT_CAUGHT:   return !IsCaught(cond->id);
    case HINT_IF_LEVEL_CAP:    return gSaveBlock3Ptr->challengeSettings.tx_Challenges_LevelCap != 0;
    }
    return FALSE;
}

static bool32 AllHold(const struct HoennHintCond *conds, u32 count)
{
    u32 i;

    for (i = 0; i < count; i++)
        if (!CondHolds(&conds[i]))
            return FALSE;
    return TRUE;
}

static bool32 IsRumorFound(u32 rumor)
{
    return AllHold(sHintRumors[rumor].found, sHintRumors[rumor].foundCount);
}

// The first forecast that applies in the player's region: a map whose special
// weather day is today, else one where it's tomorrow. Puts "today"/"tomorrow"
// in STR_VAR_1. NULL if none applies.
static const u8 *FindForecast(void)
{
    u32 days, i;
    bool32 inHoenn = IsHoennMapSec(gMapHeader.regionMapSectionId);

    for (days = 0; days < 2; days++)
    {
        for (i = 0; i < ARRAY_COUNT(sForecasts); i++)
        {
            const struct HoennForecast *f = &sForecasts[i];

            if (f->hoenn != inHoenn || !AllHold(f->conds, f->condCount))
                continue;
            if (HoennIsSpecialWeatherInDays(f->map >> 8, f->map & 0xFF, days))
            {
                StringCopy(gStringVar1, days == 0 ? sText_Today : sText_Tomorrow);
                return f->text;
            }
        }
    }
    return NULL;
}

// The text of one line, or NULL if its conditions don't hold.
static const u8 *LineText(const struct HoennHintLine *line)
{
    if (!AllHold(line->conds, line->condCount))
        return NULL;
    switch (line->kind)
    {
    case HINT_RUMOR:
        return IsRumorFound(line->rumor) ? sHintRumors[line->rumor].after : sHintRumors[line->rumor].before;
    case HINT_FORECAST:
        return FindForecast();
    default:
        return line->text;
    }
}

// callnative HoennSeek_NpcHint, .2byte npc: VAR_RESULT = TRUE and the text in
// data[0] when this talk shows the NPC's extra line; FALSE to run their own script.
void HoennSeek_NpcHint(struct ScriptContext *ctx)
{
    u32 npcId = ScriptReadHalfword(ctx);
    const struct HoennHintNpc *npc = &sHintNpcs[npcId];
    const u8 *text = NULL;
    u32 i;

    gSpecialVar_Result = FALSE;
    if (!npc->always)
    {
        // Flip the shared toggle: 0 → their own line this time, 1 → the extra line.
        u16 toggle = VarGet(VAR_HOENN_HINT_TOGGLE);
        VarSet(VAR_HOENN_HINT_TOGGLE, !toggle);
        if (toggle == 0)
            return;
    }
    for (i = 0; i < npc->lineCount && text == NULL; i++)
        text = LineText(&sHintLines[npc->lines[i]]);
    if (text == NULL)
        return;
    ctx->data[0] = (uintptr_t)text;
    gSpecialVar_Result = TRUE;
}

// callnative HoennSeek_FieldNotesCount: STR_VAR_1 = rumors found, STR_VAR_2 =
// rumors in the notes, VAR_RESULT = how many are left.
void HoennSeek_FieldNotesCount(struct ScriptContext *ctx)
{
    u32 i, found = 0;

    for (i = 0; i < ARRAY_COUNT(sHintRumors); i++)
        if (IsRumorFound(i))
            found++;
    ConvertIntToDecimalStringN(gStringVar1, found, STR_CONV_MODE_LEFT_ALIGN, 3);
    ConvertIntToDecimalStringN(gStringVar2, ARRAY_COUNT(sHintRumors), STR_CONV_MODE_LEFT_ALIGN, 3);
    gSpecialVar_Result = ARRAY_COUNT(sHintRumors) - found;
}

// callnative HoennSeek_FieldNotesHint: data[0] = the first unfound rumor's notes.
void HoennSeek_FieldNotesHint(struct ScriptContext *ctx)
{
    u32 i;

    for (i = 0; i < ARRAY_COUNT(sHintRumors); i++)
    {
        if (!IsRumorFound(i))
        {
            ctx->data[0] = (uintptr_t)sHintRumors[i].notes;
            return;
        }
    }
    ctx->data[0] = (uintptr_t)sHintRumors[0].after; // not reached: the script checks the count first
}

// callnative HoennSeek_Forecast: VAR_RESULT = TRUE and the forecast in data[0]
// (STR_VAR_1 = today/tomorrow) when one applies in the player's region.
void HoennSeek_Forecast(struct ScriptContext *ctx)
{
    const u8 *text = FindForecast();

    gSpecialVar_Result = (text != NULL);
    if (text != NULL)
        ctx->data[0] = (uintptr_t)text;
}

#endif // IS_HNS
