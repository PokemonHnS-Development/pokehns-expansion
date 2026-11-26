// Hoenn & Seek 2.0 part 22a: Absol, the storm wanderer (plan section 7).
//
// Absol is a roamer that never leaves Route 120 and only walks on the route's
// storm day (its weather cycle, part 5), in the evening or at night. It lives in
// a normal roamer slot (gSaveBlock1Ptr->roamer), so it keeps its HP and status
// between battles and flees like Raikou and Entei. What's different:
//
// - It's marked by its locationTableId (HOENN_ROAMER_TABLE_ABSOL) and its
//   species, never by its slot: roamers take the first free slot, so Absol can
//   be anywhere in the four (HnS uses up to three: Raikou, Entei, one Lati).
// - It never moves. Emerald's RoamerMove needs a location set of 3+ maps or it
//   loops forever; Absol has no location table at all. Each roamer.c function
//   that would read one returns early for Absol (one-line hooks), and IsRoamerAt
//   asks HoennAbsolIsAt instead of the shared location array (which only ever
//   holds map group 0 anyway; Route 120 is in another group).
// - Knocked out, it isn't lost: battle_main.c marks it inactive like any roamer,
//   but its slot stays reserved (HoennRoamerSlotReserved, hooked into
//   GetFirstInactiveRoamerIndex) until it's caught. The Hall of Fame's InitRoamer
//   and InitKantoRoamers only clear their own tables and then take free slots, so
//   they can't overwrite it. Repeating the cliff scene revives the same Absol
//   (same IVs, nature, shininess, level) at full HP.
// - Its moves and item are set every time a battle creates it
//   (HoennTuneRoamerMon): roamers don't store moves.
//
// Specials:
//   specialvar VAR_RESULT, HoennAbsolState  -> HOENN_ABSOL_ASLEEP/ROAMING/DOWN/CAUGHT
//   specialvar VAR_RESULT, HoennWakeAbsol   -> creates or revives it; FALSE if no
//                                              roamer slot was free (never with
//                                              HnS's three roamers)
//   specialvar VAR_RESULT, HoennAbsolIsOut  -> TRUE on Route 120's storm day,
//                                              evening or night (the cliff scene
//                                              and the encounters use the same test)
#include "global.h"
#include "event_data.h"
#include "move.h"
#include "ow_synchronize.h"
#include "battle.h"
#include "pokemon.h"
#include "random.h"
#include "roamer.h"
#include "rtc.h"
#include "constants/battle.h"
#include "constants/items.h"
#include "constants/moves.h"
#include "hoenn.h"
#include "hoenn_time.h"

#if IS_HNS
#include "constants/hoenn_events.h"

#define ABSOL_MAP_GROUP MAP_GROUP(MAP_ROUTE120)
#define ABSOL_MAP_NUM   MAP_NUM(MAP_ROUTE120)

static const u16 sAbsolMoves[MAX_MON_MOVES] =
{
    MOVE_EARTHQUAKE, MOVE_ERUPTION, MOVE_EXTREME_SPEED, MOVE_FUTURE_SIGHT,
};

bool32 HoennIsAbsolRoamer(u32 roamerIndex)
{
    const struct Roamer *roamer = &gSaveBlock1Ptr->roamer[roamerIndex];

    return roamer->locationTableId == HOENN_ROAMER_TABLE_ABSOL && roamer->species == SPECIES_ABSOL;
}

// The slot holding Absol, active or not, or ROAMER_COUNT.
static u32 FindAbsolSlot(void)
{
    u32 i;

    for (i = 0; i < ROAMER_COUNT; i++)
        if (HoennIsAbsolRoamer(i))
            return i;
    return ROAMER_COUNT;
}

// Route 120's storm day, evening or night.
u16 HoennAbsolIsOut(void)
{
    u32 time = GetTimeOfDay();

    return HoennIsSpecialWeatherDay(ABSOL_MAP_GROUP, ABSOL_MAP_NUM)
        && (time == TIME_EVENING || time == TIME_NIGHT);
}

// Hook in IsRoamerAt.
bool32 HoennAbsolIsAt(u32 roamerIndex, u8 mapGroup, u8 mapNum)
{
    return gSaveBlock1Ptr->roamer[roamerIndex].active
        && gSaveBlock1Ptr->roamer[roamerIndex].hp != 0
        && mapGroup == ABSOL_MAP_GROUP && mapNum == ABSOL_MAP_NUM
        && HoennAbsolIsOut();
}

// Hook in GetRoamerLocation (the Pokédex area page).
void HoennGetAbsolLocation(u8 *mapGroup, u8 *mapNum)
{
    *mapGroup = ABSOL_MAP_GROUP;
    *mapNum = ABSOL_MAP_NUM;
}

// Hook in GetFirstInactiveRoamerIndex: a knocked-out Absol keeps its slot.
bool32 HoennRoamerSlotReserved(u32 roamerIndex)
{
    return HoennIsAbsolRoamer(roamerIndex) && FlagGet(FLAG_HOENN_ABSOL_WOKEN) && !FlagGet(FLAG_HOENN_ABSOL_CAUGHT);
}

// Hook at the end of CreateRoamerMonInstance.
void HoennTuneRoamerMon(u32 roamerIndex, struct Pokemon *mon)
{
    u32 i;
    u16 item = ITEM_RAZOR_CLAW;

    if (!HoennIsAbsolRoamer(roamerIndex))
        return;
    for (i = 0; i < MAX_MON_MOVES; i++)
        SetMonMoveSlot(mon, sAbsolMoves[i], i);
    SetMonData(mon, MON_DATA_HELD_ITEM, &item);
}

// Hook in UpdateRoamerHPStatus, after every roamer battle (battle_main.c then
// marks the roamer inactive if it was caught or knocked out).
void HoennRoamerBattleEnded(u32 roamerIndex)
{
    if (HoennIsAbsolRoamer(roamerIndex) && gBattleOutcome == B_OUTCOME_CAUGHT)
        FlagSet(FLAG_HOENN_ABSOL_CAUGHT);
}

u16 HoennAbsolState(void)
{
    u32 slot;

    if (FlagGet(FLAG_HOENN_ABSOL_CAUGHT))
        return HOENN_ABSOL_CAUGHT;
    slot = FindAbsolSlot();
    if (!FlagGet(FLAG_HOENN_ABSOL_WOKEN) || slot == ROAMER_COUNT)
        return HOENN_ABSOL_ASLEEP;
    // An active roamer with no HP left can't be met: count it as knocked out,
    // so the cliff scene brings it back.
    if (gSaveBlock1Ptr->roamer[slot].active && gSaveBlock1Ptr->roamer[slot].hp != 0)
        return HOENN_ABSOL_ROAMING;
    return HOENN_ABSOL_DOWN;
}

// Revives the Absol in `slot` (full HP, no status) or creates it there.
static void SetUpAbsol(u32 slot, bool32 create)
{
    struct Roamer *roamer = &gSaveBlock1Ptr->roamer[slot];
    struct Pokemon *mon = &gEnemyParty[0];

    if (create)
    {
        u8 level = HoennGymAceLevel() - HOENN_SCALED_WILD_GAP;
        u32 personality = GetMonPersonality(SPECIES_ABSOL,
            GetSynchronizedGender(ROAMER_ORIGIN, SPECIES_ABSOL),
            GetSynchronizedNature(ROAMER_ORIGIN, SPECIES_ABSOL),
            RANDOM_UNOWN_LETTER);
        CreateMonWithIVs(mon, SPECIES_ABSOL, level, personality, OTID_STRUCT_PLAYER_ID, USE_RANDOM_IVS);
        roamer->ivs = GetMonData(mon, MON_DATA_IVS);
        roamer->personality = GetMonData(mon, MON_DATA_PERSONALITY);
        roamer->species = SPECIES_ABSOL;
        roamer->level = level;
        roamer->cool = GetMonData(mon, MON_DATA_COOL);
        roamer->beauty = GetMonData(mon, MON_DATA_BEAUTY);
        roamer->cute = GetMonData(mon, MON_DATA_CUTE);
        roamer->smart = GetMonData(mon, MON_DATA_SMART);
        roamer->tough = GetMonData(mon, MON_DATA_TOUGH);
        roamer->shiny = GetMonData(mon, MON_DATA_IS_SHINY);
        roamer->locationTableId = HOENN_ROAMER_TABLE_ABSOL;
    }
    else
    {
        // The same Absol: rebuild it from what the slot kept, only for its max HP.
        CreateMonWithIVsPersonality(mon, SPECIES_ABSOL, roamer->level, roamer->ivs, roamer->personality);
    }
    roamer->hp = GetMonData(mon, MON_DATA_MAX_HP);
    roamer->statusA = 0;
    roamer->statusB = 0;
    roamer->active = TRUE;
    ZeroEnemyPartyMons();
}

u16 HoennWakeAbsol(void)
{
    u32 slot = FindAbsolSlot();

    // A slot can hold a stale Absol from an older game on the same save (a new
    // game clears the flags, not the roamer data): only revive it once this
    // game's cliff scene has woken it.
    if (slot < ROAMER_COUNT && FlagGet(FLAG_HOENN_ABSOL_WOKEN))
    {
        SetUpAbsol(slot, FALSE);
        return TRUE;
    }
    if (slot == ROAMER_COUNT || gSaveBlock1Ptr->roamer[slot].active)
    {
        for (slot = 0; slot < ROAMER_COUNT; slot++)
            if (!gSaveBlock1Ptr->roamer[slot].active)
                break;
        if (slot == ROAMER_COUNT)
            return FALSE;
    }
    SetUpAbsol(slot, TRUE);
    return TRUE;
}

#endif // IS_HNS
