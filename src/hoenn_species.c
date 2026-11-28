// Hoenn & Seek 2.0 (parts 18-19): species events. The scenes themselves are
// scripts (data/scripts/hoenn_species.inc); this file holds what scripts can't
// do on their own.
//
// - special HoennPlayerIsRushing: the Ralts event on Route 102 needs to know
//   whether you came running or riding (Gardevoir teleports it away) or walking.
// - HoennSpeciesDueCall(): the PokéGear event calls these events add. It runs
//   from GetDueEventCall() (src/hoenn_phone.c, one hook line), after the calls
//   that were there before, so earlier calls keep their order.
#include "global.h"
#include "event_data.h"
#include "field_player_avatar.h"
#include "hoenn.h"

#if IS_HNS
#include "constants/hoenn_custom.h"
#include "constants/hoenn_events.h"
#include "constants/hoenn_phone.h"

// specialvar VAR_RESULT, HoennPlayerIsRushing: TRUE while the player runs or
// rides a bike. Coord triggers fire on the step that reaches the tile, while
// the avatar flags still describe that step; call it before lockall, which
// stops the player and clears the running flag.
bool8 HoennPlayerIsRushing(void)
{
    return TestPlayerAvatarFlags(PLAYER_AVATAR_FLAG_DASH | PLAYER_AVATAR_FLAG_BIKE) ? TRUE : FALSE;
}

// Part 18's calls. Each caller says how they heard:
//  - Brendan, the Swampert dive: Birch's aide counts Route 102's Pokémon every
//    morning and saw you at the pond (Birch is Brendan's dad).
//  - Wally, the Ralts: his Gardevoir came from that same Gardevoir's family on
//    Route 102, and it sensed its little sibling choose you. He only rings once
//    you have his number (after Victory Road).
//  - Brendan, Kiyo: Chuck in Cianwood told him (he and Kiyo write to each
//    other about their training, and Kiyo wrote about you).
//  - May, the Scizor: Bugsy hosts the Bug-Catching Contest show on the radio and
//    talked about the trainer who saw the Scizor.
// Part 19's calls:
//  - Brendan, the Gengar: he and May train near Lavender, and Mr. Fuji at the
//    Soul House told him about the trainer whose shadow laughed.
//  - May, the Slowking's prophecy: Kurt hears the Slowking from his house by the
//    well, and she stopped by for Apricorn balls.
u16 HoennSpeciesDueCall(void)
{
    if (FlagGet(FLAG_HOENN_WALLY_PHONE) && FlagGet(FLAG_HOENN_RALTS_DONE) && !FlagGet(FLAG_HOENN_CALL_RALTS))
        return HOENN_CALL_RALTS;
    if (!FlagGet(FLAG_HOENN_BM_PHONE))
        return HOENN_CALL_NONE;
    if (FlagGet(FLAG_HOENN_POND_SEEN) && !FlagGet(FLAG_HOENN_CALL_POND))
        return HOENN_CALL_POND;
    if (FlagGet(FLAG_HOENN_KIYO_BLACK_BELT) && !FlagGet(FLAG_HOENN_CALL_KIYO))
        return HOENN_CALL_KIYO;
    if (FlagGet(FLAG_HOENN_SCIZOR_QUICK_CLAW) && !FlagGet(FLAG_HOENN_CALL_SCIZOR))
        return HOENN_CALL_SCIZOR;
    if (FlagGet(FLAG_HOENN_GENGAR_DONE) && !FlagGet(FLAG_HOENN_CALL_GENGAR))
        return HOENN_CALL_GENGAR;
    if (FlagGet(FLAG_HOENN_SLOWKING_PROPHECY) && !FlagGet(FLAG_HOENN_CALL_PROPHECY))
        return HOENN_CALL_PROPHECY;
    return HoennHiddenDueCall(); // 2.0 parts 20+ (src/hoenn_hidden.c)
}

#endif // IS_HNS
