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
#include "global.h"
#include "event_data.h"
#include "hoenn.h"

#if IS_HNS
#include "constants/hoenn_events.h"
#include "constants/hoenn_phone.h"

u16 HoennLaneADueCall(void)
{
    u16 call = HoennCipherDueCall(); // part 27a (src/hoenn_cipher.c)

    if (call != HOENN_CALL_NONE)
        return call;
    // Lane A's next calls go here, e.g.
    //     if (FlagGet(FLAG_HOENN_X_MET) && !FlagGet(FLAG_HOENN_CALL_X))
    //         return HOENN_CALL_X;
    return HoennLaneBDueCall(); // lane B's calls come after lane A's
}

#endif // IS_HNS
