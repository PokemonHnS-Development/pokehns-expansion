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
#include "item.h"
#include "hoenn.h"
#include "constants/battle.h"
#include "constants/items.h"

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

#endif // IS_HNS

