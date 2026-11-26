// Hoenn & Seek 2.0 (parts 20+): hidden events, Hoenn (plan section 7). The scenes
// are scripts (data/scripts/hoenn_hidden.inc); this file holds what scripts
// can't do on their own.
//
// - special HoennTuneWildMon: every event Pokémon has something special (plan
//   section 9): a move it can't normally learn, perfect IVs or a held item. Run it
//   after HoennSetupScaledWildBattle (which creates gEnemyParty[0]) and before
//   dowildbattle.
// - HoennHiddenDueCall(): the PokéGear event calls these events add. It runs from
//   HoennSpeciesDueCall() (src/hoenn_species.c), after the species calls.
#include "global.h"
#include "event_data.h"
#include "move.h"
#include "pokemon.h"
#include "hoenn.h"

#if IS_HNS
#include "constants/hoenn_custom.h"
#include "constants/hoenn_events.h"
#include "constants/hoenn_phone.h"

// VAR_0x8005 = a move to teach (MOVE_NONE: none). It replaces the last move,
//              unless the Pokémon already knows it or has an empty slot.
// VAR_0x8006 = TRUE: all six IVs become 31.
// VAR_0x8007 = held item (ITEM_NONE: keep whatever it rolled).
void HoennTuneWildMon(void)
{
    struct Pokemon *mon = &gEnemyParty[0];
    u16 move = VarGet(VAR_0x8005);
    u16 item = VarGet(VAR_0x8007);
    u32 i;

    if (move != MOVE_NONE)
    {
        bool32 known = FALSE;
        u32 slot = MAX_MON_MOVES - 1;
        for (i = MAX_MON_MOVES; i-- > 0;)
        {
            u16 cur = GetMonData(mon, MON_DATA_MOVE1 + i);
            if (cur == move)
                known = TRUE;
            else if (cur == MOVE_NONE)
                slot = i; // ends on the first empty slot
        }
        if (!known)
        {
            u8 pp = GetMovePP(move);
            SetMonData(mon, MON_DATA_MOVE1 + slot, &move);
            SetMonData(mon, MON_DATA_PP1 + slot, &pp);
        }
    }
    if (VarGet(VAR_0x8006))
    {
        u8 iv = MAX_PER_STAT_IVS;
        for (i = 0; i < NUM_STATS; i++)
            SetMonData(mon, MON_DATA_HP_IV + i, &iv);
        CalculateMonStats(mon);
    }
    if (item != ITEM_NONE)
        SetMonData(mon, MON_DATA_HELD_ITEM, &item);
}

// Part 20's calls. Each caller says how they heard:
//  - Brendan, the Munchlax: the glassblower on Route 113 makes glassware for
//    Birch's lab, and he told Birch who he made the GLASS FLUTE for.
//  - May, the Slaking: Petalburg Woods was her dad Norman's old training spot,
//    and he still hears about everything that goes on there.
u16 HoennHiddenDueCall(void)
{
    if (FlagGet(FLAG_HOENN_MUNCHLAX_DONE) && !FlagGet(FLAG_HOENN_CALL_MUNCHLAX))
        return HOENN_CALL_MUNCHLAX;
    if (FlagGet(FLAG_HOENN_SLAKING_DONE) && !FlagGet(FLAG_HOENN_CALL_SLAKING))
        return HOENN_CALL_SLAKING;
    return HOENN_CALL_NONE;
}

#endif // IS_HNS
