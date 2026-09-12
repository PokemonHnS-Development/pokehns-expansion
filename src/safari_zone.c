#include "global.h"
#include "battle.h"
#include "event_data.h"
#include "field_player_avatar.h"
#include "item.h"
#include "overworld.h"
#include "main.h"
#include "pokeblock.h"
#include "safari_zone.h"
#include "script.h"
#include "string_util.h"
#include "tv.h"
#include "constants/game_stat.h"
#include "constants/items.h"
#include "field_screen_effect.h"

struct PokeblockFeeder
{
    /*0x00*/ s16 x;
    /*0x02*/ s16 y;
    /*0x04*/ s8 mapNum;
    //u8 padding;
    /*0x06*/ u16 stepCounter;
    /*0x08*/ struct Pokeblock pokeblock;
};

#define NUM_POKEBLOCK_FEEDERS 10

// Manhattan distance, in tiles, that a Pokeblock feeder lures wild Pokemon from.
// Set to POKEBLOCK_FEEDER_RANGE_WHOLE_MAP for the feeder to cover its entire map.
#define POKEBLOCK_FEEDER_RANGE_WHOLE_MAP -1
#define POKEBLOCK_FEEDER_RANGE POKEBLOCK_FEEDER_RANGE_WHOLE_MAP

// How many steps a Pokeblock lasts once placed on a feeder. For reference, a full
// Safari Game is 500 steps (600 on the FRLG build). Max 65535.
#define POKEBLOCK_FEEDER_STEPS 300

extern const u8 SafariZone_EventScript_TimesUp[];
extern const u8 SafariZone_EventScript_RetirePrompt[];
extern const u8 SafariZone_EventScript_OutOfBallsMidBattle[];
extern const u8 SafariZone_EventScript_OutOfBalls[];
extern const u8 SafariZone_EventScript_PokeblockGone[];

EWRAM_DATA u8 gNumSafariBalls = 0;
EWRAM_DATA u16 gSafariZoneStepCounter = 0;
EWRAM_DATA static u8 sSafariZoneCaughtMons = 0;
EWRAM_DATA static u8 sSafariZonePkblkUses = 0;
EWRAM_DATA static struct PokeblockFeeder sPokeblockFeeders[NUM_POKEBLOCK_FEEDERS] = {0};

static void ClearAllPokeblockFeeders(void);
static bool8 DecrementFeederStepCounters(void);

bool32 GetSafariZoneFlag(void)
{
    return FlagGet(FLAG_SYS_SAFARI_MODE);
}

void SetSafariZoneFlag(void)
{
    FlagSet(FLAG_SYS_SAFARI_MODE);
}

void ResetSafariZoneFlag(void)
{
    FlagClear(FLAG_SYS_SAFARI_MODE);
}

void EnterSafariMode(void)
{
    FlagClear(FLAG_START_NUZLOCKE); // suspends the nuzlocke, allows multi-catching
    IncrementGameStat(GAME_STAT_ENTERED_SAFARI_ZONE);
    SetSafariZoneFlag();
    ClearAllPokeblockFeeders();
    gNumSafariBalls = 30;
#if IS_HNS
    AddBagItem(ITEM_SAFARI_BALL, 30);
#endif
    if (IS_FRLG)
        gSafariZoneStepCounter = 600;
    else
        gSafariZoneStepCounter = 500;
    sSafariZoneCaughtMons = 0;
    sSafariZonePkblkUses = 0;
}

void ExitSafariMode(void)
{
    FlagSet(FLAG_START_NUZLOCKE);
    TryPutSafariFanClubOnAir(sSafariZoneCaughtMons, sSafariZonePkblkUses);
    ResetSafariZoneFlag();
    ClearAllPokeblockFeeders();
#if IS_HNS
    {
        u16 remaining = CountTotalItemQuantityInBag(ITEM_SAFARI_BALL);
        if (remaining > 0)
            RemoveBagItem(ITEM_SAFARI_BALL, remaining);
    }
#endif
    gNumSafariBalls = 0;
    gSafariZoneStepCounter = 0;
}

bool8 SafariZoneTakeStep(void)
{
    bool8 pokeblockRanOut;

    if (GetSafariZoneFlag() == FALSE)
    {
        return FALSE;
    }

    pokeblockRanOut = DecrementFeederStepCounters();
    gSafariZoneStepCounter--;
    if (gSafariZoneStepCounter == 0)
    {
        ScriptContext_SetupScript(SafariZone_EventScript_TimesUp);
        return TRUE;
    }
    if (pokeblockRanOut == TRUE)
    {
        ScriptContext_SetupScript(SafariZone_EventScript_PokeblockGone);
        return TRUE;
    }
    return FALSE;
}

void SafariZoneRetirePrompt(void)
{
    ScriptContext_SetupScript(SafariZone_EventScript_RetirePrompt);
}

void CB2_EndSafariBattle(void)
{
    sSafariZonePkblkUses += gBattleResults.pokeblockThrows;
    if (gBattleOutcome == B_OUTCOME_CAUGHT)
        sSafariZoneCaughtMons++;
    if (gNumSafariBalls != 0)
    {
        SetMainCallback2(CB2_ReturnToField);
    }
    else if (gBattleOutcome == B_OUTCOME_NO_SAFARI_BALLS)
    {
        RunScriptImmediately(SafariZone_EventScript_OutOfBallsMidBattle);
        WarpIntoMap();
        gFieldCallback = FieldCB_ReturnToFieldNoScriptCheckMusic;
        SetMainCallback2(CB2_LoadMap);
    }
    else if (gBattleOutcome == B_OUTCOME_CAUGHT)
    {
        ScriptContext_SetupScript(SafariZone_EventScript_OutOfBalls);
        ScriptContext_Stop();
        SetMainCallback2(CB2_ReturnToFieldContinueScriptPlayMapMusic);
    }
}

static void ClearPokeblockFeeder(u8 index)
{
    memset(&sPokeblockFeeders[index], 0, sizeof(struct PokeblockFeeder));
}

static void ClearAllPokeblockFeeders(void)
{
    memset(sPokeblockFeeders, 0, sizeof(sPokeblockFeeders));
}

void GetPokeblockFeederInFront(void)
{
    s16 x, y;
    u16 i;

    GetXYCoordsOneStepInFrontOfPlayer(&x, &y);

    for (i = 0; i < NUM_POKEBLOCK_FEEDERS; i++)
    {
        // An unused feeder slot is all zeroes, so skip it before comparing coords.
        if (sPokeblockFeeders[i].stepCounter == 0)
            continue;

        if (gSaveBlock1Ptr->location.mapNum == sPokeblockFeeders[i].mapNum
         && sPokeblockFeeders[i].x == x
         && sPokeblockFeeders[i].y == y)
        {
            gSpecialVar_Result = i;
            StringCopy(gStringVar1, gPokeblockNames[sPokeblockFeeders[i].pokeblock.color]);
            return;
        }
    }

    gSpecialVar_Result = -1;
}

void GetPokeblockFeederWithinRange(void)
{
    s16 x, y;
    u16 i;

    PlayerGetDestCoords(&x, &y);

    for (i = 0; i < NUM_POKEBLOCK_FEEDERS; i++)
    {
        s16 dx, dy;

        // An unused feeder slot is all zeroes, so skip it before comparing the map.
        if (sPokeblockFeeders[i].stepCounter == 0)
            continue;

        if (gSaveBlock1Ptr->location.mapNum != sPokeblockFeeders[i].mapNum)
            continue;

        // Distance from the Pokeblock feeder. Measured from the player's own coords each
        // time, so that a second feeder on the same map is still compared correctly.
        dx = abs(x - sPokeblockFeeders[i].x);
        dy = abs(y - sPokeblockFeeders[i].y);
        if (POKEBLOCK_FEEDER_RANGE != POKEBLOCK_FEEDER_RANGE_WHOLE_MAP && (dx + dy) > POKEBLOCK_FEEDER_RANGE)
            continue;

        gSpecialVar_Result = i;
        return;
    }

    gSpecialVar_Result = -1;
}

// unused
struct Pokeblock *SafariZoneGetPokeblockInFront(void)
{
    GetPokeblockFeederInFront();

    if (gSpecialVar_Result == 0xFFFF)
        return NULL;
    else
        return &sPokeblockFeeders[gSpecialVar_Result].pokeblock;
}

struct Pokeblock *SafariZoneGetActivePokeblock(void)
{
    GetPokeblockFeederWithinRange();

    if (gSpecialVar_Result == 0xFFFF)
        return NULL;
    else
        return &sPokeblockFeeders[gSpecialVar_Result].pokeblock;
}

void SafariZoneActivatePokeblockFeeder(u8 pkblId)
{
    s16 x, y;
    u8 i;

    for (i = 0; i < NUM_POKEBLOCK_FEEDERS; i++)
    {
        // Find free entry in sPokeblockFeeders
        if (sPokeblockFeeders[i].mapNum == 0
         && sPokeblockFeeders[i].x == 0
         && sPokeblockFeeders[i].y == 0)
        {
            // Initialize Pokeblock feeder
            GetXYCoordsOneStepInFrontOfPlayer(&x, &y);
            sPokeblockFeeders[i].mapNum = gSaveBlock1Ptr->location.mapNum;
            sPokeblockFeeders[i].pokeblock = gSaveBlock1Ptr->pokeblocks[pkblId];
            sPokeblockFeeders[i].stepCounter = POKEBLOCK_FEEDER_STEPS;
            sPokeblockFeeders[i].x = x;
            sPokeblockFeeders[i].y = y;
            break;
        }
    }
}

// Returns TRUE if a feeder on the map the player is currently on ran out this step,
// so that the caller can show a message. Feeders that run out on another map expire
// silently, since the player has no way of seeing them.
static bool8 DecrementFeederStepCounters(void)
{
    u8 i;
    bool8 expiredHere = FALSE;

    for (i = 0; i < NUM_POKEBLOCK_FEEDERS; i++)
    {
        if (sPokeblockFeeders[i].stepCounter != 0)
        {
            sPokeblockFeeders[i].stepCounter--;
            if (sPokeblockFeeders[i].stepCounter == 0)
            {
                if (gSaveBlock1Ptr->location.mapNum == sPokeblockFeeders[i].mapNum)
                {
                    // Copy the name out before the feeder is wiped, for the message.
                    StringCopy(gStringVar1, gPokeblockNames[sPokeblockFeeders[i].pokeblock.color]);
                    expiredHere = TRUE;
                }
                ClearPokeblockFeeder(i);
            }
        }
    }

    return expiredHere;
}

// unused
bool8 GetInFrontFeederPokeblockAndSteps(void)
{
    GetPokeblockFeederInFront();

    if (gSpecialVar_Result == 0xFFFF)
    {
        return FALSE;
    }

    ConvertIntToDecimalStringN(gStringVar2,
        sPokeblockFeeders[gSpecialVar_Result].stepCounter,
        STR_CONV_MODE_LEFT_ALIGN, 5);

    return TRUE;
}
