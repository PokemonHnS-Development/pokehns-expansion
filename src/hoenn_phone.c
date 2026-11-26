// Hoenn & Seek (part 16d): Brendan & May's and Elm's event calls, and Wally on
// the PokéGear.
//
// Event calls are one-off PokéGear calls tied to progress (a badge milestone, the
// Maxie + Archie double, Red...). HoennTryEventCall() runs from the overworld step
// hook: when one is due and the player is outdoors, it starts
// HoennSeek_EventScript_PhoneEvent with the call's ID in VAR_0x8004. The script
// plays the call and sets the call's done flag.
//
// Wally is the only special trainer who calls at random (gym leaders and the
// Elite Four don't): HoennIsCallableSpecialSlot() lets his rematch slot into the
// random-call pool, and HoennPhoneCallText() picks his lines and arms his rematch.
#include "global.h"
#include "battle_setup.h"
#include "event_data.h"
#include "constants/game_stat.h"
#include "hoenn.h"
#include "match_call.h"
#include "overworld.h"
#include "random.h"
#include "script.h"
#include "string_util.h"
#include "constants/opponents.h"
#include "constants/rematches.h"

#if IS_HNS
#include "constants/hoenn_custom.h"
#include "constants/hoenn_events.h"
#include "constants/secret_bases.h"
#include "constants/hoenn_phone.h"

extern const u8 HoennSeek_EventScript_PhoneEvent[];
extern const u8 HoennSeek_Text_WallyCall1[];
extern const u8 HoennSeek_Text_WallyCall2[];
extern const u8 HoennSeek_Text_WallyCallBattle[];

#define EVENT_CALL_STEP_INTERVAL 16 // look for a due call every 16 steps

static EWRAM_DATA u8 sEventCallSteps = 0;

// 2.0 parts 12/12b: the base spots at the reopened legendary sites.
static bool32 HoennIsLegendarySiteBase(u8 secretBaseId)
{
    return HOENN_IS_SITE_BASE(secretBaseId); // data/hoenn/base_spots.json
}

// 2.0 part 13a: the base spots in Johto and Kanto.
static bool32 HoennIsJohtoKantoBase(u8 secretBaseId)
{
    return HOENN_IS_JOHTO_KANTO_BASE(secretBaseId); // data/hoenn/base_spots.json
}

// Which event call is due, if any. Badge calls only ring for the highest
// milestone reached; skipped lower ones are marked done.
// 2.0 part 15a: TRUE once the unclaimed Johto starter (the one Birch sent Elm
// that got loose) is with you. VAR_STARTER_MON: 0 Chikorita, 1 Cyndaquil,
// 2 Totodile; the unclaimed one is the third starter, never yours or the rival's
// (Cyndaquil if you chose Totodile, Chikorita if Cyndaquil, Totodile if Chikorita).
static bool32 HoennFoundBirchStarter(void)
{
    switch (VarGet(VAR_STARTER_MON))
    {
    case 0:  return FlagGet(FLAG_HOENN_TOTODILE_DONE);
    case 1:  return FlagGet(FLAG_HOENN_CHIKORITA_DONE);
    case 2:  return FlagGet(FLAG_HOENN_CYNDAQUIL_DONE);
    default: return FALSE;
    }
}

static u16 GetDueEventCall(void)
{
    if (FlagGet(FLAG_HOENN_BM_PHONE) && !FlagGet(FLAG_HOENN_STAMP_WALLACE))
    {
        u32 stamps = HoennCountStamps();

        if (stamps >= 8 && !FlagGet(FLAG_HOENN_CALL_BADGE8))
        {
            FlagSet(FLAG_HOENN_CALL_BADGE1);
            FlagSet(FLAG_HOENN_CALL_BADGE4);
            return HOENN_CALL_BADGE8;
        }
        if (stamps >= 4 && !FlagGet(FLAG_HOENN_CALL_BADGE4))
        {
            FlagSet(FLAG_HOENN_CALL_BADGE1);
            return HOENN_CALL_BADGE4;
        }
        if (stamps >= 1 && !FlagGet(FLAG_HOENN_CALL_BADGE1))
            return HOENN_CALL_BADGE1;
    }
    if (FlagGet(FLAG_HOENN_BEAT_BM) && !FlagGet(FLAG_HOENN_CALL_ELM))
        return HOENN_CALL_ELM;
    if (FlagGet(FLAG_HOENN_BM_PHONE) && FlagGet(FLAG_HOENN_TEAMS_DOUBLE_WON) && !FlagGet(FLAG_HOENN_CALL_TEAMS))
        return HOENN_CALL_TEAMS;
    if (FlagGet(FLAG_HOENN_BEAT_BM) && HasTrainerBeenFought(TRAINER_RED_HNS) && !FlagGet(FLAG_HOENN_CALL_RED))
        return HOENN_CALL_RED;
    // Part 17: May watches the contests on TV (any contest hall, Lilycove or Viridian).
    if (FlagGet(FLAG_HOENN_BM_PHONE) && GetGameStat(GAME_STAT_WON_CONTEST) > 0 && !FlagGet(FLAG_HOENN_CALL_CONTEST))
        return HOENN_CALL_CONTEST;
    // 2.0 part 15a: Elm told Birch that his runaway Johto starter found you.
    if (FlagGet(FLAG_HOENN_BM_PHONE) && HoennFoundBirchStarter() && !FlagGet(FLAG_HOENN_CALL_STARTER_FOUND))
        return HOENN_CALL_STARTER_FOUND;
    // 2.0 part 16: Bill told Birch that a Kanto starter chose you (Bulbasaur in
    // the garden behind his house, Charmander at Nugget Bridge), or Birch's aide heard
    // about the Squirtle Squad at Vermilion's port (part 17).
    if (FlagGet(FLAG_HOENN_BM_PHONE)
     && (FlagGet(FLAG_HOENN_BULBASAUR_DONE) || FlagGet(FLAG_HOENN_CHARMANDER_DONE) || FlagGet(FLAG_HOENN_SQUIRTLE_DONE))
     && !FlagGet(FLAG_HOENN_CALL_KANTO_STARTER))
        return HOENN_CALL_KANTO_STARTER;
    // 2.0 part 14: Mr. Briney saw you surf out of the Tidal Strait and told Norman.
    if (FlagGet(FLAG_HOENN_BM_PHONE) && FlagGet(FLAG_HOENN_CROSSED_STRAIT) && !FlagGet(FLAG_HOENN_CALL_STRAIT))
        return HOENN_CALL_STRAIT;
    // 2.0 part 12: your base is at one of the reopened legendary sites. It replaces
    // Brendan's first-base call (marked done) so the two don't ring back to back.
    if (FlagGet(FLAG_HOENN_BM_PHONE) && HoennIsLegendarySiteBase(gSaveBlock1Ptr->secretBases[0].secretBaseId)
     && !FlagGet(FLAG_HOENN_CALL_SITES))
    {
        FlagSet(FLAG_HOENN_CALL_BASE);
        return HOENN_CALL_SITES;
    }
    // 2.0 part 13a: your base is in Johto or Kanto. A hiker Brendan battled saw it.
    // Like the sites call, it stands in for Brendan's first-base call.
    if (FlagGet(FLAG_HOENN_BM_PHONE) && HoennIsJohtoKantoBase(gSaveBlock1Ptr->secretBases[0].secretBaseId)
     && !FlagGet(FLAG_HOENN_CALL_JK_BASE))
    {
        FlagSet(FLAG_HOENN_CALL_BASE);
        return HOENN_CALL_JK_BASE;
    }
    // Part 18: one of Birch's aides saw you duck into your new secret base.
    if (FlagGet(FLAG_HOENN_BM_PHONE) && gSaveBlock1Ptr->secretBases[0].secretBaseId != 0 && !FlagGet(FLAG_HOENN_CALL_BASE))
        return HOENN_CALL_BASE;
    return HoennSpeciesDueCall(); // 2.0 parts 18+ (src/hoenn_species.c)
}

bool32 HoennTryEventCall(void)
{
    u16 call;

    if (++sEventCallSteps < EVENT_CALL_STEP_INTERVAL)
        return FALSE;
    sEventCallSteps = 0;

    if (!FlagGet(FLAG_HAS_MATCH_CALL)
     || !(Overworld_MapTypeAllowsTeleportAndFly(gMapHeader.mapType) || gMapHeader.mapType == MAP_TYPE_UNDERGROUND))
        return FALSE;

    call = GetDueEventCall();
    if (call == HOENN_CALL_NONE)
        return FALSE;

    gSpecialVar_0x8004 = call;
    ScriptContext_SetupScript(HoennSeek_EventScript_PhoneEvent);
    return TRUE;
}

// Random calls normally skip the special rematch slots (Wally, leaders, E4).
bool32 HoennIsCallableSpecialSlot(u32 rematchIdx)
{
    return rematchIdx == REMATCH_WALLY_VR;
}

// 20a: Wally was picked as often as any registered trainer, which made him the most
// frequent caller early on (few Hoenn trainers registered yet). He now goes ahead with
// one pick in three.
bool32 HoennSpecialCallerAnswers(s32 rematchIdx)
{
    if (rematchIdx != REMATCH_WALLY_VR)
        return TRUE;
    return (Random() % 3) == 0;
}

// Text for a random call from a Hoenn special caller, or NULL to use HnS's tables.
// Once you've beaten Wally, half his calls ask for a rematch (and arm it).
const u8 *HoennPhoneCallText(u16 trainerId, bool32 *newRematchRequest)
{
    if (trainerId != TRAINER_WALLY_VR_2)
        return NULL;

    if (gSaveBlock1Ptr->trainerRematches[REMATCH_WALLY_VR] == 0 && HasTrainerBeenFought(trainerId) && (Random() % 2))
        UpdateRematchIfDefeated(REMATCH_WALLY_VR);
    if (gSaveBlock1Ptr->trainerRematches[REMATCH_WALLY_VR] != 0)
    {
        *newRematchRequest = TRUE;
        return HoennSeek_Text_WallyCallBattle;
    }
    return (Random() % 2) ? HoennSeek_Text_WallyCall1 : HoennSeek_Text_WallyCall2;
}

#endif // IS_HNS
