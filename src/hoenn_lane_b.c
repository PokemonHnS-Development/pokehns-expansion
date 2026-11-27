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
#include "event_data.h"
#include "hoenn.h"

#if IS_HNS
#include "constants/hoenn_events.h"
#include "constants/hoenn_phone.h"

u16 HoennLaneBDueCall(void)
{
    // Part 31b: Brendan, once you've followed the Ursaring up to the moon hollow.
    if (FlagGet(FLAG_HOENN_MOON_HOLLOW_FOUND) && !FlagGet(FLAG_HOENN_CALL_MOON_HOLLOW))
        return HOENN_CALL_MOON_HOLLOW;
    return HOENN_CALL_NONE; // the end of the chain
}

#endif // IS_HNS
