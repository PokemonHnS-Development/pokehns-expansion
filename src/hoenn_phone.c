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
#include "constants/hoenn_phone.h"

extern const u8 HoennSeek_EventScript_PhoneEvent[];
extern const u8 HoennSeek_Text_WallyCall1[];
extern const u8 HoennSeek_Text_WallyCall2[];
extern const u8 HoennSeek_Text_WallyCallBattle[];

#define EVENT_CALL_STEP_INTERVAL 16 // look for a due call every 16 steps

static EWRAM_DATA u8 sEventCallSteps = 0;

// Which event call is due, if any. Badge calls only ring for the highest
// milestone reached; skipped lower ones are marked done.
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
    // Part 18: one of Birch's aides saw you duck into your new secret base.
    if (FlagGet(FLAG_HOENN_BM_PHONE) && gSaveBlock1Ptr->secretBases[0].secretBaseId != 0 && !FlagGet(FLAG_HOENN_CALL_BASE))
        return HOENN_CALL_BASE;
    return HOENN_CALL_NONE;
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
