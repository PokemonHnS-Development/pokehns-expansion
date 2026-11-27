// Hoenn & Seek 2.0, lane B: parts 31b, 34a, 29, 30a, 30b, 33, 36 and 35a (Kanto, the Safari Zone, the birds, Mewtwo/Mew, Hoenn's weather legendaries).
//
// Since Nov 27 two builders work in parallel, each on its own lane of parts
// (hoenn-docs/lanes/README.md has the rules; hoenn-docs/lanes/lane-b.md the
// status). Each lane keeps its C code in its own file so the two never edit the
// same lines: lane B's code goes here (or in a new src/hoenn_*.c of its own),
// lane A's in src/hoenn_lane_a.c. Scripts and texts: data/scripts/hoenn_lane_b.inc.
//
// - HoennLaneBDueCall(): lane B's PokéGear event calls. The chain is
//   GetDueEventCall (src/hoenn_phone.c) → HoennSpeciesDueCall → HoennHiddenDueCall
//   → HoennLaneADueCall → HoennLaneBDueCall. Add one `if` per call, in the order
//   they should ring; IDs come from lane B's range in constants/hoenn_phone.h.
#include "global.h"
#include "battle.h"
#include "event_data.h"
#include "fieldmap.h"
#include "hoenn.h"
#include "hoenn_caps.h"
#include "item.h"
#include "rtc.h"
#include "safari_zone.h"
#include "script_pokemon_util.h"
#include "constants/battle.h"
#include "constants/items.h"
#include "constants/rtc.h"

#if IS_HNS
#include "constants/hoenn_events.h"
#include "constants/hoenn_phone.h"

u16 HoennLaneBDueCall(void)
{
    // Part 31b: Brendan, once you've followed the Ursaring up to the moon hollow.
    if (FlagGet(FLAG_HOENN_MOON_HOLLOW_FOUND) && !FlagGet(FLAG_HOENN_CALL_MOON_HOLLOW))
        return HOENN_CALL_MOON_HOLLOW;
    // Part 34a: May, once a feather has called a bird down (Bill told Birch).
    if (!FlagGet(FLAG_HOENN_CALL_BIRDS)
     && (FlagGet(FLAG_HOENN_ARTICUNO_LANDED) || FlagGet(FLAG_HOENN_ZAPDOS_LANDED) || FlagGet(FLAG_HOENN_MOLTRES_LANDED)
      || FlagGet(FLAG_HOENN_CAUGHT_ARTICUNO) || FlagGet(FLAG_HOENN_CAUGHT_ZAPDOS) || FlagGet(FLAG_HOENN_CAUGHT_MOLTRES)))
        return HOENN_CALL_BIRDS;
    // Part 29: Brendan, once the crystal Onix is yours (a Lavender hiker saw it).
    if (FlagGet(FLAG_HOENN_ONIX_CAUGHT) && !FlagGet(FLAG_HOENN_CALL_TUNNELS))
        return HOENN_CALL_TUNNELS;
    // Part 30a: May, once the Kangaskhan baby is back with its mother.
    if (FlagGet(FLAG_HOENN_KANGA_REUNITED) && !FlagGet(FLAG_HOENN_CALL_KANGASKHAN))
        return HOENN_CALL_KANGASKHAN;
    return HOENN_CALL_NONE; // the end of the chain
}

// ---------------------------------------------------------------------------
// Part 34a: the three birds. Each bird's roost (Seafoam B1F, the Power Plant's
// back yard on Route 10, Mt. Silver's Moltres room) asks these from its map's
// OnTransition and battle script, with the bird's HOENN_BIRD_* index in
// VAR_0x8009 (VAR_0x8004-0x8006 are taken by seteventmon). Its flags come in
// Articuno, Zapdos, Moltres order in constants/hoenn_events.h.

static const u16 sBirdFeathers[HOENN_BIRD_COUNT] = {
    [HOENN_BIRD_ARTICUNO] = ITEM_FROST_FEATHER,
    [HOENN_BIRD_ZAPDOS]   = ITEM_THUNDER_FEATHER,
    [HOENN_BIRD_MOLTRES]  = ITEM_FLAME_FEATHER,
};

static u32 BirdIndex(void)
{
    return gSpecialVar_0x8009 < HOENN_BIRD_COUNT ? gSpecialVar_0x8009 : HOENN_BIRD_ARTICUNO;
}

// specialvar VAR_RESULT, HoennBirdRoostState: decides on every arrival whether
// the bird is shown (it landed earlier and is still waiting), can be called
// down (you carry its feather), or neither. Hides the bird unless it's waiting.
u16 HoennBirdRoostState(void)
{
    u32 bird = BirdIndex();

    FlagSet(FLAG_HOENN_HIDE_ARTICUNO + bird);
    if (FlagGet(FLAG_HOENN_CAUGHT_ARTICUNO + bird) || FlagGet(FLAG_HOENN_DAILY_ARTICUNO_GONE + bird))
        return HOENN_ROOST_EMPTY;
    if (FlagGet(FLAG_HOENN_ARTICUNO_LANDED + bird))
    {
        FlagClear(FLAG_HOENN_HIDE_ARTICUNO + bird);
        return HOENN_ROOST_WAITING;
    }
    if (!CheckBagHasItem(sBirdFeathers[bird], 1))
        return HOENN_ROOST_EMPTY;
    return HOENN_ROOST_CALL;
}

// special HoennBirdLand: the feather called the bird down. The script shows it.
void HoennBirdLand(void)
{
    u32 bird = BirdIndex();

    FlagSet(FLAG_HOENN_ARTICUNO_LANDED + bird);
    FlagClear(FLAG_HOENN_HIDE_ARTICUNO + bird);
}

// specialvar VAR_RESULT, HoennBirdBattleEnded: after the battle. Caught: gone
// for good. Knocked out: it flies off until tomorrow, and the feather can call
// it again then. Ran (or anything else): it stays. Returns TRUE if it leaves,
// so the script removes the object.
bool16 HoennBirdBattleEnded(void)
{
    u32 bird = BirdIndex();

    switch (gBattleOutcome)
    {
    case B_OUTCOME_CAUGHT:
        FlagSet(FLAG_HOENN_CAUGHT_ARTICUNO + bird);
        break;
    case B_OUTCOME_WON:
        FlagSet(FLAG_HOENN_DAILY_ARTICUNO_GONE + bird);
        break;
    default:
        return FALSE;
    }
    FlagClear(FLAG_HOENN_ARTICUNO_LANDED + bird);
    return TRUE;
}

// ---------------------------------------------------------------------------
// Part 29: shifting tunnels. Levels for these Johto/Kanto events follow your
// progress, like DAMIAN's team (src/hoenn_scaling.c): HnS's Normal level cap for
// your Johto badges, then the post-Johto cap (Kanto badges, Hoenn badges), 85
// after Wallace; the Pokémon comes in 5 below it, never under VAR_0x8005.

#define PROGRESS_WILD_GAP       5
#define PROGRESS_AFTER_WALLACE  85
#define PROGRESS_JOHTO_CHAMPION 56 // the floor before Kanto badges (as for DAMIAN)

// HnS's Normal caps by Johto badge count (src/caps.c); 0 badges: Lv 10.
static const u8 sJohtoBadgeLevels[] = { 10, 15, 19, 24, 29, 31, 33, 42 };

static u32 HoennProgressLevel(void)
{
    u32 i, badges = 0;

    if (FlagGet(FLAG_HOENN_STAMP_WALLACE))
        return PROGRESS_AFTER_WALLACE;
    for (i = 0; i < 8; i++)
        if (FlagGet(FLAG_BADGE01_GET + i))
            badges++;
    if (badges < 8)
        return sJohtoBadgeLevels[badges];
    return HoennGetPostJohtoLevelCap(PROGRESS_JOHTO_CHAMPION, FALSE);
}

// special HoennSetupProgressWildBattle: VAR_0x8004 = species, VAR_0x8005 = the
// lowest level it may have. Follow with HoennTuneWildMonSlot as usual.
void HoennSetupProgressWildBattle(void)
{
    u32 level = HoennProgressLevel() - PROGRESS_WILD_GAP;

    if (level < VarGet(VAR_0x8005))
        level = VarGet(VAR_0x8005);
    CreateScriptedWildMon(VarGet(VAR_0x8004), level, ITEM_NONE);
}

static void SetBlock(s32 x, s32 y, u16 metatile)
{
    MapGridSetMetatileIdAt(x + MAP_OFFSET, y + MAP_OFFSET, metatile);
}

// --- The tunneling Onix (Rock Tunnel B1F) ---
// One hole per weekday (HOENN_SUNDAY = 0), each on the face of a different rock
// wall, with open floor below it. Each has a door warp into the bore in
// RockTunnel_B1F_hns's map.json, in the same order (warps 6-12); the warp only
// works while the hole is drawn (MB_NON_ANIMATED_DOOR), so on any other night
// that wall is just rock.
#define ONIX_HOLE_METATILE 0x342 // Cave_Gray's hole in a rock face (a non-animated door)

static const struct { u8 x, y; } sOnixHoles[] = {
    {30,  3}, // Sunday: the north passage
    {19, 11}, // Monday: the block by the ladder
    {35, 11}, // Tuesday: the long block in the middle
    {50, 17}, // Wednesday: the east passage's wall
    {23, 18}, // Thursday: the block above the south room
    { 5, 27}, // Friday: the west end of the great wall
    {13, 27}, // Saturday: the middle of the great wall
};

// specialvar VAR_RESULT, HoennOnixHoleTonight: tonight's hole (0-6), or
// HOENN_ONIX_NO_HOLE by day. The holes keep opening after the Onix is caught,
// so the bore's items stay within reach. A night is one weekday from dusk to
// dawn (HoennNightWeekday, 27r), so the hole doesn't move at midnight.
u16 HoennOnixHoleTonight(void)
{
    if (GetTimeOfDay() != TIME_NIGHT)
        return HOENN_ONIX_NO_HOLE;
    return HoennNightWeekday() % ARRAY_COUNT(sOnixHoles);
}

// special HoennDrawOnixHole (Rock Tunnel B1F's ON_LOAD): opens tonight's hole.
void HoennDrawOnixHole(void)
{
    u32 hole = HoennOnixHoleTonight();

    if (hole < ARRAY_COUNT(sOnixHoles))
        SetBlock(sOnixHoles[hole].x, sOnixHoles[hole].y, ONIX_HOLE_METATILE);
}

// special HoennOnixHoleExit: where the bore lets you out, the floor below
// tonight's hole, in VAR_0x8008/VAR_0x8009 (warp takes vars). Uses the night's
// weekday even by day, so leaving after dawn still puts you below a hole's
// floor (the one you came in by, unless you went in after midnight).
void HoennOnixHoleExit(void)
{
    u32 hole = HoennNightWeekday() % ARRAY_COUNT(sOnixHoles);

    gSpecialVar_0x8008 = sOnixHoles[hole].x;
    gSpecialVar_0x8009 = sOnixHoles[hole].y + 1;
}

// --- The Dunsparce burrows (Dark Cave) ---
// One burrow hole per time of day on Dark Cave's south side (HOENN_TIME_*
// order). Each has a warp in DarkCave_SouthSide_hns's map.json (warps 3-6) into
// the burrow; the warp only works while its hole is drawn (MB_MT_PYRE_HOLE: you
// fall through).
#define BURROW_HOLE_METATILE 0x286 // Cave_Default's hole in the floor

static const struct { u8 x, y; } sBurrowHoles[] = {
    [TIME_MORNING] = {12,  8}, // the north-west corner, past the pebbles
    [TIME_DAY]     = {19, 16}, // the long passage west of the lake
    [TIME_EVENING] = {34,  9}, // the lake's east shore
    [TIME_NIGHT]   = {47, 13}, // the east hall
};

// special HoennDrawBurrowHole (Dark Cave south side's ON_LOAD).
void HoennDrawBurrowHole(void)
{
    u32 t = GetTimeOfDay();

    if (t < ARRAY_COUNT(sBurrowHoles))
        SetBlock(sBurrowHoles[t].x, sBurrowHoles[t].y, BURROW_HOLE_METATILE);
}

static u32 BurrowDigs(void)
{
    u32 t, digs = 0;

    for (t = 0; t < HOENN_BURROW_DIGS_NEEDED; t++)
        if (FlagGet(FLAG_HOENN_BURROW_DUG_MORNING + t))
            digs++;
    return digs;
}

// The passage from the burrow's room up to the chamber (x 10-11, rows 7-10) is
// choked with rubble; each dig clears the lowest row left.
#define BURROW_PASSAGE_X    10
#define BURROW_PASSAGE_TOP  7
#define BURROW_RUBBLE_A     (0x283 | MAPGRID_COLLISION_MASK)
#define BURROW_RUBBLE_B     (0x282 | MAPGRID_COLLISION_MASK)

// special HoennDrawBurrowRubble (the burrow's ON_LOAD).
void HoennDrawBurrowRubble(void)
{
    s32 y, rows = HOENN_BURROW_DIGS_NEEDED - BurrowDigs();

    for (y = 0; y < rows; y++)
    {
        SetBlock(BURROW_PASSAGE_X, BURROW_PASSAGE_TOP + y, (y & 1) ? BURROW_RUBBLE_B : BURROW_RUBBLE_A);
        SetBlock(BURROW_PASSAGE_X + 1, BURROW_PASSAGE_TOP + y, (y & 1) ? BURROW_RUBBLE_A : BURROW_RUBBLE_B);
    }
}

// The digger waits on the floor just below the lowest row of rubble left.
static u32 LowestRubbleRow(void)
{
    return BURROW_PASSAGE_TOP + HOENN_BURROW_DIGS_NEEDED - BurrowDigs() - 1;
}

// specialvar VAR_RESULT, HoennBurrowPrepare (the burrow's OnTransition):
// TRUE if this time of day's Dunsparce hasn't dug yet; then its digger is shown
// and goes to VAR_0x8008/VAR_0x8009 (setobjectxyperm). Also decides whether the
// Dudunsparce sleeps in the chamber (passage open, not caught, not knocked out
// today).
bool16 HoennBurrowPrepare(void)
{
    u32 t = GetTimeOfDay();
    bool32 due = t < HOENN_BURROW_DIGS_NEEDED && BurrowDigs() < HOENN_BURROW_DIGS_NEEDED
              && !FlagGet(FLAG_HOENN_BURROW_DUG_MORNING + t);

    FlagSet(FLAG_HOENN_HIDE_BURROW_DIGGER);
    FlagSet(FLAG_HOENN_HIDE_DUDUNSPARCE);
    if (BurrowDigs() == HOENN_BURROW_DIGS_NEEDED && !FlagGet(FLAG_HOENN_DUDUNSPARCE_CAUGHT)
     && !FlagGet(FLAG_HOENN_DAILY_DUDUNSPARCE_GONE))
        FlagClear(FLAG_HOENN_HIDE_DUDUNSPARCE);
    if (!due)
        return FALSE;
    FlagClear(FLAG_HOENN_HIDE_BURROW_DIGGER);
    gSpecialVar_0x8008 = BURROW_PASSAGE_X;
    gSpecialVar_0x8009 = LowestRubbleRow() + 1;
    return TRUE;
}

// specialvar VAR_RESULT, HoennBurrowDig: this time of day's Dunsparce digs out
// the lowest row of rubble. VAR_0x8008 gets that row's y (the script clears it
// with setmetatile); the result is the number of rows still left (0: open).
u16 HoennBurrowDig(void)
{
    u32 t = GetTimeOfDay();

    gSpecialVar_0x8008 = LowestRubbleRow();
    if (t < HOENN_BURROW_DIGS_NEEDED)
        FlagSet(FLAG_HOENN_BURROW_DUG_MORNING + t);
    return HOENN_BURROW_DIGS_NEEDED - BurrowDigs();
}

// ---- Part 30a: the lost Kangaskhan baby ----
// The baby walks behind you as your follower Pokémon would: while it follows,
// the follower system shows it instead of your lead (four one-line hooks in
// src/event_object_movement.c call the functions below). Its sprite is our own
// (graphics/hoenn/kanga_baby, drawn in Kangaskhan's overworld palette), and it
// stands in for SPECIES_NONE, which no real follower or overworld Pokémon ever
// uses; only inside the Safari Zone does SPECIES_NONE mean the baby. The map
// objects of the baby use OBJ_EVENT_GFX_MON_BASE+SPECIES_NONE too.

// The baby is following you (only inside the Safari Zone: leaving it ends the
// walk, and the Safari entrance clears the flag).
static bool32 KangaBabyFollowing(void)
{
    return FlagGet(FLAG_HOENN_KANGA_BABY_FOLLOWING) && GetSafariZoneFlag();
}

// SpeciesToGraphicsInfo: draw the baby for this species?
bool32 HoennIsKangaBabyGfx(u32 species)
{
    return species == SPECIES_NONE && GetSafariZoneFlag();
}

// LoadDynamicFollowerPalette*: the baby uses its mother's overworld palette.
u32 HoennFollowerPaletteSpecies(u32 species)
{
    return HoennIsKangaBabyGfx(species) ? SPECIES_KANGASKHAN : species;
}

// GetFollowerInfo: TRUE (and the baby's "species") while it follows you.
bool32 HoennFollowerOverride(u32 *species, bool32 *shiny, bool32 *female)
{
    if (!KangaBabyFollowing())
        return FALSE;
    *species = SPECIES_NONE;
    *shiny = FALSE;
    *female = FALSE;
    return TRUE;
}

// Talking to the follower: the baby's own script while it follows, else NULL.
const u8 *HoennFollowerScript(void)
{
    return KangaBabyFollowing() ? HoennSeek_EventScript_KangaBabyFollower : NULL;
}

#endif // IS_HNS

