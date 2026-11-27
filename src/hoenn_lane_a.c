// Hoenn & Seek 2.0, lane A: parts 27b, 28, 31a, 32, 34b, 35b and 37 (Johto, the Unown Cipher, the sea, Lugia, Ho-Oh, the Regis).
//
// Since Nov 27 two builders work in parallel, each on its own lane of parts
// (hoenn-docs/lanes/README.md has the rules; hoenn-docs/lanes/lane-a.md the
// status). Each lane keeps its C code in its own file so the two never edit the
// same lines: lane A's code goes here (or in a new src/hoenn_*.c of its own),
// lane B's in src/hoenn_lane_b.c. Scripts and texts: data/scripts/hoenn_lane_a.inc.
//
// - HoennLaneADueCall(): lane A's PokéGear event calls. The chain is
//   GetDueEventCall (src/hoenn_phone.c) → HoennSpeciesDueCall → HoennHiddenDueCall
//   → HoennLaneADueCall → HoennLaneBDueCall. Add one `if` per call, in the order
//   they should ring; IDs come from lane A's range in constants/hoenn_phone.h.
//
// Part 27b (Unown Cipher B, the glyph sites; plan section 8 item 3):
// - Each of 27a's night words names a place. Once you've seen a weekday's word
//   in the Words rooms, that place shows a RING of Unown at night, in a quiet
//   corner, spelling the word clockwise from the top (sGlyphSites below; the
//   objects are in each map.json with FLAG_HOENN_CIPHER_HIDE_RING, which every
//   site map's ON_TRANSITION decides through HoennGlyphRingShows).
// - Talk to the ring and one letter leaves it to battle (a scaled wild Unown of
//   that form). Caught or knocked out, the ring is gone and a TABLET FRAGMENT
//   carved with that letter lies where it was (FLAG_HOENN_CIPHER_FRAGMENT_SUN +
//   weekday). Ran: the ring stays. The seven letters spell ANCIENT, which the
//   lab researcher reads once you have them all (part 28 starts there).
// - The Unown forms share one overworld palette (gOverworldPalette_Unown) but
//   each form would load its own copy, so a ring of six could take six of the
//   sixteen sprite palettes. HoennObjectPaletteSpecies() (one hook line in
//   LoadDynamicFollowerPalette, src/event_object_movement.c) makes every form
//   use plain Unown's palette tag, so a ring takes one.
//
// Part 28 (Unown Cipher C, the sanctum; plan section 8 item 4):
// - The tablet's mark is the boulder in the middle of the Ruins of Alph
//   (Outside, 23,27). At night with the tablet, examining its face plays the
//   opening: three Unown gather, the ground shakes and a cave mouth opens
//   (metatile 0xA9, the Union Cave doorway; the Outside's ON_LOAD redraws it once
//   FLAG_HOENN_CIPHER_SANCTUM_OPEN is set). Its warp leads down a ladder into
//   RuinsOfAlph_Sanctum_hoenn, a composed map of the inner chamber's blocks.
// - The sanctum's north wall is a mural of the Unown frieze. Once a day it calls
//   the letter you pick, any of the 28 forms (HoennSanctumLetter, then 27b's
//   HoennGlyphSetupBattle, which also gives plain Unown an A personality).
// - The middle statue holds the final inscription: Unown and Hoenn braille that
//   point to the Sinjoh Ruins and the three giants behind its doors
//   (FLAG_HOENN_CIPHER_INSCRIPTION, part 37's start). The lab researcher reads it
//   with you and phones Birch (Brendan's call).
// - Radio: the Ruins' Unown station (HnS played only music there) now spells a
//   word through the static once the Rosetta is read: the place of a fragment
//   you're still missing (a different one each week), then what to do next
//   (HoennRadioUnownBroadcast, one hook line in src/pokenav_radio.c).
//
// Part 37 (Jirachi, Deoxys, the Regis, Arceus; plan section 4):
// - Jirachi: a wish on a shooting star, at night, at three spots: the Meteor
//   Falls clifftop (part 23's map), the Space Center's 2F windows and the moon
//   hollow's pool (lane B's part 31b). With all three made, the white rock at
//   Mt. Moon Square answers on the Clefairy's Monday night (part 3), which is
//   when HnS's own summon runs. HoennWishCount() counts them.
// - Deoxys: the Space Center's 2F scientist picks up a signal from a meteorite
//   at night. HoennDeoxysSignalNight() counts each night once (a night is dusk
//   to dawn, like HoennNightWeekday), and on the third different night he gives
//   the AURORA TICKET, which HnS's Olivine fan used to give to any champion.
// - The Regis and Arceus are script-only (data/scripts/hoenn_lane_a.inc).
#include "global.h"
#include "event_data.h"
#include "event_object_movement.h"
#include "field_player_avatar.h"
#include "field_screen_effect.h"
#include "item.h"
#include "overworld.h"
#include "constants/items.h"
#include "fieldmap.h"
#include "metatile_behavior.h"
#include "script.h"
#include "pokemon.h"
#include "rtc.h"
#include "string_util.h"
#include "constants/characters.h"
#include "constants/event_objects.h"
#include "constants/event_object_movement.h"
#include "constants/map_event_ids.h"
#include "constants/map_groups.h"
#include "constants/rtc.h"
#include "constants/species.h"
#include "hoenn.h"

#if IS_HNS
#include "constants/hoenn_custom.h"
#include "constants/hoenn_events.h"
#include "constants/hoenn_phone.h"

bool8 HoennCipherIsOpen(void); // src/hoenn_cipher.c (part 27a)

extern const u8 HoennSeek_EventScript_GlyphRing[];
extern const u8 HoennSeek_EventScript_AmpharosAshore[];

// ---- Part 27b: the glyph sites ----------------------------------------------
struct GlyphSite
{
    u16 map;      // MAP_* (group << 8 | num)
    u16 species;  // the form that leaves the ring to battle
    const u8 *word;
    u8 letter;    // its letter, as a string index into sLetters
};

static const u8 sWordTower[]  = _("TOWER");
static const u8 sWordMoon[]   = _("MOON");
static const u8 sWordIce[]    = _("ICE");
static const u8 sWordWhirl[]  = _("WHIRL");
static const u8 sWordMortar[] = _("MORTAR");
static const u8 sWordUnion[]  = _("UNION");
static const u8 sWordFoam[]   = _("FOAM");
static const u8 sLetters[]    = _("ENCITNA");

// Indexed by weekday (HOENN_SUNDAY = 0), like 27a's night words. One letter of
// each word; in weekday order they're E N C I T N A, which rearrange to ANCIENT.
static const struct GlyphSite sGlyphSites[] = {
    [HOENN_SUNDAY]    = {MAP_TIN_TOWER_2F_HNS,       SPECIES_UNOWN_E, sWordTower,  0}, // the BELL TOWER
    [HOENN_MONDAY]    = {MAP_MT_MOON_OUTSIDE_HNS,    SPECIES_UNOWN_N, sWordMoon,   1}, // MT. MOON SQUARE
    [HOENN_TUESDAY]   = {MAP_ICE_PATH_1F_HNS,        SPECIES_UNOWN_C, sWordIce,    2},
    [HOENN_WEDNESDAY] = {MAP_WHIRL_ISLANDS_B2F_HNS,  SPECIES_UNOWN_I, sWordWhirl,  3},
    [HOENN_THURSDAY]  = {MAP_MT_MORTAR_1F_SOUTH_HNS, SPECIES_UNOWN_T, sWordMortar, 4},
    [HOENN_FRIDAY]    = {MAP_UNION_CAVE_B1F_HNS,     SPECIES_UNOWN_N, sWordUnion,  5},
    [HOENN_SATURDAY]  = {MAP_SEAFOAM_ISLANDS_1F_HNS, SPECIES_UNOWN,   sWordFoam,   6},
};

// The weekday whose site is the current map, or HOENN_WEEKDAY_COUNT.
static u32 GlyphSiteHere(void)
{
    u32 map = (gSaveBlock1Ptr->location.mapGroup << 8) | gSaveBlock1Ptr->location.mapNum;
    u32 i;

    for (i = 0; i < ARRAY_COUNT(sGlyphSites); i++)
    {
        if (sGlyphSites[i].map == map)
            return i;
    }
    return HOENN_WEEKDAY_COUNT;
}

// specialvar VAR_RESULT, HoennGlyphRingShows: TRUE if this map's ring is out
// now: night, the Unown letters learned, this place's word seen, and its
// fragment not found yet. Every site map's ON_TRANSITION asks (on arrival).
bool8 HoennGlyphRingShows(void)
{
    u32 day = GlyphSiteHere();

    return day != HOENN_WEEKDAY_COUNT
        && GetTimeOfDay() == TIME_NIGHT
        && FlagGet(FLAG_HOENN_CIPHER_ROSETTA)
        && FlagGet(FLAG_HOENN_CIPHER_WORD_SUN + day)
        && !FlagGet(FLAG_HOENN_CIPHER_FRAGMENT_SUN + day);
}

// special HoennGlyphRingPrepare: for this map's ring, STR_VAR_1 = its word,
// STR_VAR_2 = the letter that comes out, VAR_0x8004 = that Unown's species (for
// HoennSetupScaledWildBattle) and VAR_0x8005 = its object's local ID (for
// applymovement). Only runs from the ring's own objects, so the map is a site.
void HoennGlyphRingPrepare(void)
{
    const struct GlyphSite *site = &sGlyphSites[GlyphSiteHere()];
    const struct ObjectEventTemplate *templates = gMapHeader.events->objectEvents;
    u32 i;

    StringCopy(gStringVar1, site->word);
    gStringVar2[0] = sLetters[site->letter];
    gStringVar2[1] = EOS;
    gSpecialVar_0x8004 = site->species;
    gSpecialVar_0x8005 = 0;
    for (i = 0; i < gMapHeader.events->objectEventCount; i++)
    {
        if (templates[i].script == HoennSeek_EventScript_GlyphRing
         && templates[i].graphicsId == OBJ_EVENT_GFX_MON_BASE + site->species)
            gSpecialVar_0x8005 = templates[i].localId;
    }
}

// special HoennGlyphSetupBattle: the scaled wild Unown of this ring's letter
// (species from HoennGlyphRingPrepare in VAR_0x8004). Letter forms are their
// own species, but plain SPECIES_UNOWN shows the letter its personality picks,
// so FOAM's A gets a personality whose letter is A.
void HoennGlyphSetupBattle(void)
{
    struct Pokemon *mon = &gEnemyParty[0];
    u32 level;

    HoennSetupScaledWildBattle();
    // (also skipped when HnS's randomizer swapped the species)
    if (GetMonData(mon, MON_DATA_SPECIES) != SPECIES_UNOWN)
        return;
    level = GetMonData(mon, MON_DATA_LEVEL);
    ZeroEnemyPartyMons();
    CreateMonWithIVs(mon, SPECIES_UNOWN, level,
                     GetMonPersonality(SPECIES_UNOWN, MON_GENDER_RANDOM, NATURE_RANDOM, 1), // letter 1 = A
                     OTID_STRUCT_PLAYER_ID, USE_RANDOM_IVS);
    GiveMonInitialMoveset(mon);
}

// special HoennGlyphTakeFragment: the ring is gone (every object running the
// ring script is removed and the hide flag set) and this place's fragment is
// found. STR_VAR_2 keeps the letter from HoennGlyphRingPrepare.
void HoennGlyphTakeFragment(void)
{
    const struct ObjectEventTemplate *templates = gMapHeader.events->objectEvents;
    u32 i;

    for (i = 0; i < gMapHeader.events->objectEventCount; i++)
    {
        if (templates[i].script == HoennSeek_EventScript_GlyphRing)
            RemoveObjectEventByLocalIdAndMap(templates[i].localId, gSaveBlock1Ptr->location.mapNum,
                                             gSaveBlock1Ptr->location.mapGroup);
    }
    FlagSet(FLAG_HOENN_CIPHER_HIDE_RING);
    FlagSet(FLAG_HOENN_CIPHER_FRAGMENT_SUN + GlyphSiteHere());
}

// specialvar VAR_RESULT, HoennCipherFragmentCount (0-7), also in STR_VAR_3;
// STR_VAR_1 gets the letters found so far, in weekday order ("E N C").
u16 HoennCipherFragmentCount(void)
{
    u8 *end = gStringVar1;
    u32 i, count = 0;

    for (i = 0; i < HOENN_WEEKDAY_COUNT; i++)
    {
        if (!FlagGet(FLAG_HOENN_CIPHER_FRAGMENT_SUN + i))
            continue;
        if (count++ != 0)
            *end++ = CHAR_SPACE;
        *end++ = sLetters[sGlyphSites[i].letter];
    }
    *end = EOS;
    ConvertIntToDecimalStringN(gStringVar3, count, STR_CONV_MODE_LEFT_ALIGN, 1);
    return count;
}

// One hook line in LoadDynamicFollowerPalette: the Unown forms all use plain
// Unown's palette, so they share one palette tag (see the header).
u32 HoennObjectPaletteSpecies(u32 species)
{
    if (species >= SPECIES_UNOWN_B && species <= SPECIES_UNOWN_QUESTION)
        return SPECIES_UNOWN;
    return species;
}

// ---- Part 28: the sanctum ---------------------------------------------------

// special HoennSanctumLetter: the mural's menu answer (VAR_RESULT, 0-27 = A-Z ! ?)
// becomes the Unown species in VAR_0x8004 (for HoennGlyphSetupBattle) and its
// letter in STR_VAR_1. Letter forms are their own species; A is plain Unown.
void HoennSanctumLetter(void)
{
    static const u8 sMarks[] = _("!?");
    u32 i = gSpecialVar_Result < HOENN_SANCTUM_LETTERS ? gSpecialVar_Result : 0;

    gSpecialVar_0x8004 = (i == 0) ? SPECIES_UNOWN : SPECIES_UNOWN_B + i - 1;
    gStringVar1[0] = (i < 26) ? CHAR_A + i : sMarks[i - 26];
    gStringVar1[1] = EOS;
}

static const u8 sText_RadioUnownStatic[] = _("…Strange cries in the static…");
static const u8 sText_RadioUnownSpells[] = _("The UNOWN signal spells:");
static const u8 sWordLab[]    = _("LAB");
static const u8 sWordMiddle[] = _("MIDDLE");
static const u8 sWordNight[]  = _("NIGHT");
static const u8 sWordDown[]   = _("DOWN");
static const u8 sWordSinjoh[] = _("SINJOH");
static const u8 sWordGiants[] = _("GIANTS");

// "T-O-W-E-R… T-O-W-E-R…" into line (a 40-byte radio buffer; words are short).
static void SpellWord(u8 *line, const u8 *word)
{
    u32 n, i;

    for (n = 0; n < 2; n++)
    {
        for (i = 0; word[i] != EOS; i++)
        {
            if (i != 0)
                *line++ = CHAR_HYPHEN;
            *line++ = word[i];
        }
        *line++ = CHAR_ELLIPSIS;
        if (n == 0)
            *line++ = CHAR_SPACE;
    }
    *line = EOS;
}

// One hook line in the Unown station's case of the radio (src/pokenav_radio.c,
// which only plays it at the Ruins of Alph). Nothing until the cipher opens,
// then static until the Rosetta is read; after that a word, which changes each
// week while you're looking for fragments and then follows the story.
u32 HoennRadioUnownBroadcast(const u8 **lines, u8 *line)
{
    u32 week = VarGet(VAR_HOENN_WEEK_SEEN);
    const u8 *word = NULL;
    u32 i;

    if (!HoennCipherIsOpen())
        return 0;
    if (!FlagGet(FLAG_HOENN_CIPHER_ROSETTA))
    {
        lines[0] = sText_RadioUnownStatic;
        return 1;
    }
    if (FlagGet(FLAG_HOENN_CIPHER_INSCRIPTION))
        word = (week & 1) ? sWordGiants : sWordSinjoh;
    else if (FlagGet(FLAG_HOENN_CIPHER_SANCTUM_OPEN))
        word = sWordDown;
    else if (FlagGet(FLAG_HOENN_CIPHER_TABLET))
        word = (week & 1) ? sWordNight : sWordMiddle;
    else
    {
        // A place whose fragment is still missing, a different one each week.
        for (i = 0; i < HOENN_WEEKDAY_COUNT && word == NULL; i++)
        {
            u32 day = (week + i) % HOENN_WEEKDAY_COUNT;
            if (!FlagGet(FLAG_HOENN_CIPHER_FRAGMENT_SUN + day))
                word = sGlyphSites[day].word;
        }
        if (word == NULL)
            word = sWordLab; // all seven: take them to the lab
    }
    SpellWord(line, word);
    lines[0] = sText_RadioUnownSpells;
    lines[1] = line;
    return 2;
}

// ---- Part 32: the stranded Ampharos ---------------------------------------
// Bryan (32 review): a rescue, not a battle. VAR_HOENN_AMPHAROS_STATE counts
// the BERRIES it has taken from you (one a night, HOENN_AMPHAROS_TRUSTS of
// them); then it rides with you (HOENN_AMPHAROS_RIDING) and shows as your
// follower Pokémon, so it's seen the moment you land on any shore. Your first
// step on land plays the hop-off (HoennSeek_EventScript_AmpharosAshore): it
// runs off, and a short scene at the lighthouse top (HOENN_AMPHAROS_ARRIVING)
// shows it reaching JASMINE and AMPHY before you're put back where you landed.

static bool32 AmpharosWithYou(void)
{
    u32 state = VarGet(VAR_HOENN_AMPHAROS_STATE);
    return state == HOENN_AMPHAROS_RIDING || state == HOENN_AMPHAROS_ARRIVING;
}

// One hook line in TryStartStepCountScript (src/field_control_avatar.c), after
// the follow-the-lights one. Landing from Surf isn't a step; the next one is.
bool32 HoennLaneAOnStep(void)
{
    if (VarGet(VAR_HOENN_AMPHAROS_STATE) != HOENN_AMPHAROS_RIDING)
        return FALSE;
    if (gPlayerAvatar.flags & (PLAYER_AVATAR_FLAG_SURFING | PLAYER_AVATAR_FLAG_UNDERWATER))
        return FALSE;
    ScriptContext_SetupScript(HoennSeek_EventScript_AmpharosAshore);
    return TRUE;
}

// Called first by HoennFollowerOverride (src/hoenn_lane_b.c, part 30a's hook
// in GetFollowerInfo): while it rides with you, it's your follower.
bool32 HoennLaneAFollowerOverride(u32 *species, bool32 *shiny, bool32 *female)
{
    if (!AmpharosWithYou())
        return FALSE;
    *species = SPECIES_AMPHAROS;
    *shiny = FALSE;
    *female = FALSE;
    return TRUE;
}

// specialvar VAR_RESULT, HoennHasAnyBerry: anything in the BERRIES pocket.
u16 HoennHasAnyBerry(void)
{
    u32 i;

    for (i = 0; i < gBagPockets[POCKET_BERRIES].capacity; i++)
    {
        if (GetBagItemId(POCKET_BERRIES, i) != ITEM_NONE && GetBagItemQuantity(POCKET_BERRIES, i) != 0)
            return TRUE;
    }
    return FALSE;
}

static bool32 IsOpenLand(s32 x, s32 y)
{
    if (MapGridGetCollisionAt(x, y))
        return FALSE;
    if (MetatileBehavior_IsSurfableWaterOrUnderwater(MapGridGetMetatileBehaviorAt(x, y)))
        return FALSE;
    return GetObjectEventIdByXY(x, y) == OBJECT_EVENTS_COUNT;
}

// specialvar VAR_RESULT, HoennAmpharosRunDir: the way the follower (the
// Ampharos) runs off, with 3 tiles of open land: away from you first, then
// to the sides. DIR_NONE if it isn't showing (it then just leaves off screen).
u16 HoennAmpharosRunDir(void)
{
    static const s8 sDeltas[][2] = {
        [DIR_SOUTH] = {0, 1}, [DIR_NORTH] = {0, -1}, [DIR_WEST] = {-1, 0}, [DIR_EAST] = {1, 0},
    };
    static const u8 sOrder[] = {DIR_NORTH, DIR_SOUTH, DIR_WEST, DIR_EAST};
    struct ObjectEvent *follower = GetFollowerObject();
    struct ObjectEvent *player = &gObjectEvents[gPlayerAvatar.objectEventId];
    s32 x, y;
    u32 i, k, away;

    if (follower == NULL || follower->invisible)
        return DIR_NONE;
    x = follower->currentCoords.x;
    y = follower->currentCoords.y;
    if (x < player->currentCoords.x)
        away = DIR_WEST;
    else if (x > player->currentCoords.x)
        away = DIR_EAST;
    else if (y < player->currentCoords.y)
        away = DIR_NORTH;
    else
        away = DIR_SOUTH;
    for (i = 0; i < ARRAY_COUNT(sOrder) + 1; i++)
    {
        u32 dir = (i == 0) ? away : sOrder[i - 1];

        if (dir == GetOppositeDirection(away))
            continue; // that's toward you
        for (k = 1; k <= 3; k++)
        {
            if (!IsOpenLand(x + sDeltas[dir][0] * k, y + sDeltas[dir][1] * k))
                break;
        }
        if (k > 3)
            return dir;
    }
    return DIR_NONE;
}

// Where to put you back after the lighthouse scene. Kept in EWRAM, not in
// gSaveBlock1Ptr->dynamicWarp (doors use that), and written field by field:
// SetDynamicWarpWithCoords/SetWarpDestination take s8 coordinates, so any x
// past 127 (the lighthouse is 170 tiles wide) came out as the map's centre.
// The scene can't be saved during, and a reset replays it from RIDING.
static EWRAM_DATA struct WarpData sAmpharosReturn = {0};

static void WarpToCoords(s8 mapGroup, s8 mapNum, s16 x, s16 y)
{
    struct WarpData saved = gSaveBlock1Ptr->dynamicWarp;

    gSaveBlock1Ptr->dynamicWarp.mapGroup = mapGroup;
    gSaveBlock1Ptr->dynamicWarp.mapNum = mapNum;
    gSaveBlock1Ptr->dynamicWarp.warpId = WARP_ID_NONE;
    gSaveBlock1Ptr->dynamicWarp.x = x;
    gSaveBlock1Ptr->dynamicWarp.y = y;
    SetWarpDestinationToDynamicWarp(0);
    gSaveBlock1Ptr->dynamicWarp = saved;
}

// special HoennAmpharosSaveReturn: remember your tile.
void HoennAmpharosSaveReturn(void)
{
    sAmpharosReturn.mapGroup = gSaveBlock1Ptr->location.mapGroup;
    sAmpharosReturn.mapNum = gSaveBlock1Ptr->location.mapNum;
    sAmpharosReturn.warpId = WARP_ID_NONE;
    sAmpharosReturn.x = gSaveBlock1Ptr->pos.x;
    sAmpharosReturn.y = gSaveBlock1Ptr->pos.y;
}

// special HoennAmpharosToLighthouse (then waitstate): `warpsilent` to the
// lighthouse top's (158,11), which a script command can't reach (s8 x).
void HoennAmpharosToLighthouse(void)
{
    WarpToCoords(MAP_GROUP(MAP_OLIVINE_CITY_LIGHTHOUSE_HNS), MAP_NUM(MAP_OLIVINE_CITY_LIGHTHOUSE_HNS), 158, 11);
    DoDiveWarp();
    ResetInitialPlayerAvatarState();
}

// special HoennAmpharosReturn (then waitstate): back to the saved tile.
void HoennAmpharosReturn(void)
{
    WarpToCoords(sAmpharosReturn.mapGroup, sAmpharosReturn.mapNum, sAmpharosReturn.x, sAmpharosReturn.y);
    DoWarp();
    ResetInitialPlayerAvatarState();
}

// special HoennAmpharosHidePlayer (the lighthouse's ON_WARP_INTO_MAP entry,
// after objects spawn and before the fade-in): you aren't in the scene.
void HoennAmpharosHidePlayer(void)
{
    gObjectEvents[gPlayerAvatar.objectEventId].invisible = TRUE;
}

// ---------------------------------------------------------------------------
// Part 34b: Lugia. Route 41 already holds 64 object templates, the most a map
// can have, so the Lugia that surfaces there borrows part 32's Lanturn light:
// once the lagoon is found that light never shows again. Its template is the
// RAM copy in SaveBlock1, so changing its graphics here only lasts until the
// map loads again (the next load copies the ROM template back).
void HoennLugiaCameoPrepare(void)
{
    u32 i;
    struct ObjectEventTemplate *templates = gSaveBlock1Ptr->objectEventTemplates;

    for (i = 0; i < gMapHeader.events->objectEventCount; i++)
    {
        if (templates[i].localId == LOCALID_HOENN_LANTURN_LIGHT)
        {
            templates[i].graphicsId = OBJ_EVENT_GFX_MON_BASE + SPECIES_LUGIA;
            templates[i].movementType = MOVEMENT_TYPE_FACE_DOWN;
            return;
        }
    }
}

// ---- Part 37: Jirachi's wishes, Deoxys's signal -----------------------------
// specialvar VAR_RESULT, HoennWishCount: how many of the three wishes are made.
u16 HoennWishCount(void)
{
    return FlagGet(FLAG_HOENN_WISH_METEOR_FALLS) + FlagGet(FLAG_HOENN_WISH_SPACE_CENTER)
         + FlagGet(FLAG_HOENN_WISH_MOON_HOLLOW);
}

// specialvar VAR_RESULT, HoennDeoxysSignalNight: the scientist's check.
//   0: it isn't night (the signal only comes through at night)
//   1: night, but tonight is already in his log
//   2: a new night: VAR_HOENN_DEOXYS_SIGNAL went up by one
// A night runs from dusk to dawn, so the hours after midnight belong to the
// day before (as in HoennNightWeekday). VAR_HOENN_DEOXYS_NIGHT keeps that
// night's day number + 2, so 0 means no night logged yet.
u16 HoennDeoxysSignalNight(void)
{
    u16 night;

    RtcCalcLocalTime();
    if (GetTimeOfDay() != TIME_NIGHT)
        return 0;
    // The hours before noon belong to the night that began the day before.
    // Counting from days + 2 keeps that from underflowing on day 0 and keeps
    // every logged night above 0.
    night = gLocalTime.days + 2;
    if (gLocalTime.hours < 12)
        night--;
    if (VarGet(VAR_HOENN_DEOXYS_NIGHT) == night)
        return 1;
    VarSet(VAR_HOENN_DEOXYS_NIGHT, night);
    if (VarGet(VAR_HOENN_DEOXYS_SIGNAL) < HOENN_DEOXYS_NIGHTS)
        VarSet(VAR_HOENN_DEOXYS_SIGNAL, VarGet(VAR_HOENN_DEOXYS_SIGNAL) + 1);
    return 2;
}

u16 HoennLaneADueCall(void)
{
    u16 call = HoennCipherDueCall(); // part 27a (src/hoenn_cipher.c)

    if (call != HOENN_CALL_NONE)
        return call;
    // Part 27b, May: the Ruins lab phoned Birch once you showed them a fragment.
    if (FlagGet(FLAG_HOENN_BM_PHONE) && FlagGet(FLAG_HOENN_CIPHER_SHOWED_LAB)
     && !FlagGet(FLAG_HOENN_CALL_CIPHER_FRAGMENT))
        return HOENN_CALL_CIPHER_FRAGMENT;
    // Part 31a, Brendan: May's dad (Norman) read Clair's gym report about the Ice Path thief.
    if (FlagGet(FLAG_HOENN_BM_PHONE) && FlagGet(FLAG_HOENN_SNEASEL_STASH) && !FlagGet(FLAG_HOENN_CALL_SNEASEL))
        return HOENN_CALL_SNEASEL;
    // Part 28, Brendan: the lab phoned Birch once it read the inscription with you.
    if (FlagGet(FLAG_HOENN_BM_PHONE) && FlagGet(FLAG_HOENN_CIPHER_LAB_SANCTUM)
     && !FlagGet(FLAG_HOENN_CALL_CIPHER_SANCTUM))
        return HOENN_CALL_CIPHER_SANCTUM;
    // Part 32: the stranded Ampharos is rescued; Jasmine's report reached Norman.
    if (FlagGet(FLAG_HOENN_BM_PHONE) && FlagGet(FLAG_HOENN_RESCUED_AMPHAROS) && !FlagGet(FLAG_HOENN_CALL_AMPHAROS))
        return HOENN_CALL_AMPHAROS;
    // Part 35b: Brendan heard of the rainbow over Ecruteak (src/hoenn_johto_legends.c)
    if (FlagGet(FLAG_HOENN_BM_PHONE) && FlagGet(FLAG_HOENN_HOOH_RAINBOW) && !FlagGet(FLAG_HOENN_CALL_RAINBOW))
        return HOENN_CALL_RAINBOW;
    // Part 34b, Brendan: Bill heard the Olivine lighthouse saw the Whirl Islands' sea go still.
    if (FlagGet(FLAG_HOENN_BM_PHONE) && FlagGet(FLAG_HOENN_LUGIA_SHRINE_OPEN) && !FlagGet(FLAG_HOENN_CALL_LUGIA))
        return HOENN_CALL_LUGIA;
    // Part 37, May: the Space Center's old man phoned Birch about your wishes.
    if (FlagGet(FLAG_HOENN_BM_PHONE) && HoennWishCount() == 3 && !FlagGet(FLAG_HOENN_CALL_WISHES))
        return HOENN_CALL_WISHES;
    // Part 37, Brendan: the Space Center told Birch it gave you the ticket.
    if (FlagGet(FLAG_HOENN_BM_PHONE) && FlagGet(FLAG_HOENN_DEOXYS_TICKET) && !FlagGet(FLAG_HOENN_CALL_DEOXYS))
        return HOENN_CALL_DEOXYS;
    // Part 37, May: Steven heard a door move at the Sinjoh Ruins.
    if (FlagGet(FLAG_HOENN_BM_PHONE) && !FlagGet(FLAG_HOENN_CALL_REGIS)
     && (FlagGet(FLAG_HOENN_REGI_OPEN_ROCK) || FlagGet(FLAG_HOENN_REGI_OPEN_ICE) || FlagGet(FLAG_HOENN_REGI_OPEN_STEEL)))
        return HOENN_CALL_REGIS;
    // Lane A's next calls go here, e.g.
    //     if (FlagGet(FLAG_HOENN_X_MET) && !FlagGet(FLAG_HOENN_CALL_X))
    //         return HOENN_CALL_X;
    return HoennLaneBDueCall(); // lane B's calls come after lane A's
}

#endif // IS_HNS
