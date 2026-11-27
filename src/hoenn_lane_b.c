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
#include "event_object_movement.h"
#include "fieldmap.h"
#include "hoenn.h"
#include "hoenn_caps.h"
#include "item.h"
#include "overworld.h"
#include "pokemon.h"
#include "rtc.h"
#include "safari_zone.h"
#include "script.h"
#include "script_pokemon_util.h"
#include "task.h"
#include "constants/battle.h"
#include "constants/event_object_movement.h"
#include "constants/items.h"
#include "constants/map_event_ids.h"
#include "constants/map_groups.h"
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
    // Part 30b: Brendan, once the stampede's lead bull is yours.
    if (FlagGet(FLAG_HOENN_STAMPEDE_LEADER_CAUGHT) && !FlagGet(FLAG_HOENN_CALL_STAMPEDE))
        return HOENN_CALL_STAMPEDE;
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

// ---- Part 30b: the Tauros stampede ----
// Monday mornings, six Tauros charge across the Safari Zone's highland
// (FuchsiaCity_SafariZoneHighland_hoenn), one per lane: each runs from one side
// wall to the other, paws the ground, turns and charges back. The player keeps
// control the whole time; a Tauros that runs into the player's tile starts
// HoennSeek_EventScript_StampedeHit, which knocks them back to the canyon.
//
// A task drives the herd (started from the map's ON_RESUME script, so it
// comes back after battles and menus). Each lane's state (x, direction, a
// countdown) lives in sHerd; the object's template coords follow x on every
// step, so a Tauros that leaves the screen and is respawned reappears where
// it should be. Off screen the countdown alone paces it, so the herd keeps the
// same rhythm whether or not you can see it. The task idles while a script or
// menu holds the player (ArePlayerFieldControlsLocked). After the lead bull's
// battle (caught or knocked out) the herd stops where it is and grazes for the
// rest of the week.

#define STAMPEDE_TURN_PAUSE 24 // frames a Tauros paws the ground at a lane's end

enum { STAMPEDE_NORMAL, STAMPEDE_FAST, STAMPEDE_FASTER };
static const u8 sStampedeFrames[] = { [STAMPEDE_NORMAL] = 16, [STAMPEDE_FAST] = 8, [STAMPEDE_FASTER] = 4 };

struct StampedeLane
{
    u8 localId;
    u8 y, xMin, xMax; // the lane's row and its grass between the side walls
    u8 speed;         // STAMPEDE_*
};

// Start positions and directions are the objects' own in the map.json. The
// player walks a tile in 16 frames (no running in the Safari Zone).
static const struct StampedeLane sStampedeLanes[] = {
    { LOCALID_HOENN_STAMPEDE_1,  7, 4, 21, STAMPEDE_FAST },
    { LOCALID_HOENN_STAMPEDE_2,  9, 3, 22, STAMPEDE_FAST },
    { LOCALID_HOENN_STAMPEDE_3, 10, 4, 21, STAMPEDE_NORMAL },
    { LOCALID_HOENN_STAMPEDE_4, 12, 5, 23, STAMPEDE_FASTER },
    { LOCALID_HOENN_STAMPEDE_5, 14, 3, 22, STAMPEDE_FAST },
    { LOCALID_HOENN_STAMPEDE_6, 15, 3, 20, STAMPEDE_FAST },
};
#define STAMPEDE_LANES ARRAY_COUNT(sStampedeLanes)

static EWRAM_DATA struct
{
    bool8 ready; // cleared on every arrival (HoennStampedeReset)
    s8 dir[STAMPEDE_LANES]; // +1 east, -1 west
    u8 wait[STAMPEDE_LANES]; // frames until the next step or the end of a pause
} sHerd = {0};

static bool32 OnHighland(void)
{
    return gSaveBlock1Ptr->location.mapGroup == MAP_GROUP(MAP_FUCHSIA_CITY_SAFARI_ZONE_HIGHLAND_HOENN)
        && gSaveBlock1Ptr->location.mapNum == MAP_NUM(MAP_FUCHSIA_CITY_SAFARI_ZONE_HIGHLAND_HOENN);
}

// The herd is out (Monday mornings) and still has its leader this week: once
// the lead bull is caught or knocked out, the Tauros stand and graze.
static bool32 HerdCharging(void)
{
    return !FlagGet(FLAG_HOENN_HIDE_STAMPEDE) && !FlagGet(FLAG_HOENN_WEEKLY_LEAD_BULL);
}

static const struct ObjectEventTemplate *LaneTemplate(u32 i)
{
    return GetObjectEventTemplateByLocalIdAndMap(sStampedeLanes[i].localId,
        gSaveBlock1Ptr->location.mapNum, gSaveBlock1Ptr->location.mapGroup);
}

// The lane's Tauros object if it's on screen.
static struct ObjectEvent *LaneObject(u32 i)
{
    u8 objId;

    if (TryGetObjectEventIdByLocalIdAndMap(sStampedeLanes[i].localId, gSaveBlock1Ptr->location.mapNum,
                                           gSaveBlock1Ptr->location.mapGroup, &objId))
        return NULL;
    return &gObjectEvents[objId];
}

static u8 StampedeWalkAction(u32 i, u32 dir)
{
    switch (sStampedeLanes[i].speed)
    {
    case STAMPEDE_NORMAL: return GetWalkNormalMovementAction(dir);
    case STAMPEDE_FAST:   return GetWalkFastMovementAction(dir);
    default:              return GetWalkFasterMovementAction(dir);
    }
}

static void Task_HoennStampede(u8 taskId)
{
    u32 i;
    struct ObjectEvent *player = &gObjectEvents[gPlayerAvatar.objectEventId];

    if (!OnHighland() || !HerdCharging())
    {
        DestroyTask(taskId);
        return;
    }
    if (ArePlayerFieldControlsLocked())
        return;

    for (i = 0; i < STAMPEDE_LANES; i++)
    {
        const struct StampedeLane *lane = &sStampedeLanes[i];
        const struct ObjectEventTemplate *template = LaneTemplate(i);
        struct ObjectEvent *obj = LaneObject(i);
        s32 x, next;
        u32 dir;

        if (template == NULL)
            continue;
        // Run into: the Tauros has started a step onto the player's tile.
        if (obj != NULL && obj->currentCoords.x == player->currentCoords.x
                        && obj->currentCoords.y == player->currentCoords.y)
        {
            ScriptContext_SetupScript(HoennSeek_EventScript_StampedeHit);
            return;
        }
        if (sHerd.wait[i] > 0)
        {
            sHerd.wait[i]--;
            continue;
        }
        if (obj != NULL && ObjectEventIsMovementOverridden(obj) && !ObjectEventClearHeldMovementIfFinished(obj))
            continue; // still finishing the last tile

        x = template->x;
        next = x + sHerd.dir[i];
        if (next < lane->xMin || next > lane->xMax)
        {
            // The lane's end: paw the ground, turn, charge back.
            sHerd.dir[i] = -sHerd.dir[i];
            sHerd.wait[i] = STAMPEDE_TURN_PAUSE;
            if (obj != NULL)
                ObjectEventSetHeldMovement(obj, GetWalkInPlaceFastMovementAction(sHerd.dir[i] > 0 ? DIR_EAST : DIR_WEST));
            continue;
        }
        dir = sHerd.dir[i] > 0 ? DIR_EAST : DIR_WEST;
        SetObjEventTemplateCoords(lane->localId, next, lane->y);
        if (obj != NULL)
            ObjectEventSetHeldMovement(obj, StampedeWalkAction(i, dir)); // paces itself
        else
            sHerd.wait[i] = sStampedeFrames[lane->speed] - 1; // off screen: the clock paces it
    }
}

// special HoennStampedeReset (the highland's OnTransition): the herd starts
// from the map.json's places, facing the map.json's ways.
void HoennStampedeReset(void)
{
    sHerd.ready = FALSE;
}

// special HoennStartStampede (the highland's ON_RESUME): start the herd's task
// if the herd is out and it isn't running yet.
void HoennStartStampede(void)
{
    u32 i;

    if (!HerdCharging() || FuncIsActiveTask(Task_HoennStampede))
        return;
    if (!sHerd.ready)
    {
        for (i = 0; i < STAMPEDE_LANES; i++)
        {
            const struct ObjectEventTemplate *template = LaneTemplate(i);
            sHerd.dir[i] = (template != NULL && template->movementType == MOVEMENT_TYPE_FACE_LEFT) ? -1 : 1;
            sHerd.wait[i] = 0;
        }
        sHerd.ready = TRUE;
    }
    CreateTask(Task_HoennStampede, 80);
}

// specialvar VAR_RESULT, HoennStampedeBreed: this week's lead bull (HOENN_BULL_*):
// the three breeds take turns by week, skipping any already caught;
// HOENN_BULL_NONE once all three are.
u16 HoennStampedeBreed(void)
{
    u32 i, first = VarGet(VAR_HOENN_WEEK_SEEN) % HOENN_BULL_COUNT;

    for (i = 0; i < HOENN_BULL_COUNT; i++)
    {
        u32 breed = (first + i) % HOENN_BULL_COUNT;
        if (!FlagGet(FLAG_HOENN_CAUGHT_BULL_COMBAT + breed))
            return breed;
    }
    return HOENN_BULL_NONE;
}

// special HoennTuneLeadBull (after HoennSetupProgressWildBattle): perfect
// Attack and Speed, the bull's two best stats.
void HoennTuneLeadBull(void)
{
    u8 iv = MAX_PER_STAT_IVS;

    SetMonData(&gEnemyParty[0], MON_DATA_ATK_IV, &iv);
    SetMonData(&gEnemyParty[0], MON_DATA_SPEED_IV, &iv);
    CalculateMonStats(&gEnemyParty[0]);
}

// specialvar VAR_RESULT, HoennLeadBullBattleEnded: TRUE when the bull leaves
// (caught, or knocked out: back next Monday); FALSE if you ran.
bool16 HoennLeadBullBattleEnded(void)
{
    u32 breed = HoennStampedeBreed();

    switch (gBattleOutcome)
    {
    case B_OUTCOME_CAUGHT:
        if (breed < HOENN_BULL_COUNT)
            FlagSet(FLAG_HOENN_CAUGHT_BULL_COMBAT + breed);
        FlagSet(FLAG_HOENN_STAMPEDE_LEADER_CAUGHT);
        break;
    case B_OUTCOME_WON:
        break;
    default:
        return FALSE;
    }
    FlagSet(FLAG_HOENN_WEEKLY_LEAD_BULL);
    return TRUE;
}

#endif // IS_HNS

