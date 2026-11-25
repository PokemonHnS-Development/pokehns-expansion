#ifndef GUARD_CONSTANTS_HOENN_CUSTOM_H
#define GUARD_CONSTANTS_HOENN_CUSTOM_H

// Hoenn & Seek: hand-defined flags and vars (not generated). They live in the
// reserved tail of the Hoenn ranges in constants/hoenn_layout.h, which
// tools/hoenn/gen_hoenn_ids.py never assigns.
#include "constants/hoenn_layout.h"

// Trainer card stamps (part 9 adds the UI and gym hooks). Wallace's stamp is
// the Hoenn League win; it opens Mt. Silver (ReceptionGate_hns).
#define FLAG_HOENN_STAMP_GYM_1       (HOENN_CUSTOM_FLAGS_START + 0x00)
#define FLAG_HOENN_STAMP_GYM_2       (HOENN_CUSTOM_FLAGS_START + 0x01)
#define FLAG_HOENN_STAMP_GYM_3       (HOENN_CUSTOM_FLAGS_START + 0x02)
#define FLAG_HOENN_STAMP_GYM_4       (HOENN_CUSTOM_FLAGS_START + 0x03)
#define FLAG_HOENN_STAMP_GYM_5       (HOENN_CUSTOM_FLAGS_START + 0x04)
#define FLAG_HOENN_STAMP_GYM_6       (HOENN_CUSTOM_FLAGS_START + 0x05)
#define FLAG_HOENN_STAMP_GYM_7       (HOENN_CUSTOM_FLAGS_START + 0x06)
#define FLAG_HOENN_STAMP_GYM_8       (HOENN_CUSTOM_FLAGS_START + 0x07)
#define FLAG_HOENN_STAMP_WALLACE     (HOENN_CUSTOM_FLAGS_START + 0x08)

// Ferry (part 8)
#define FLAG_HOENN_SILVER_GATE_OPEN  (HOENN_CUSTOM_FLAGS_START + 0x11) // the gate guard has stepped aside
#define FLAG_HOENN_MET_MIND_READER   (HOENN_CUSTOM_FLAGS_START + 0x12) // Mossdeep guru introduced himself (part 14a)

#define HOENN_CUSTOM_FLAGS_END       (HOENN_CUSTOM_FLAGS_START + 0x3F)

#endif // GUARD_CONSTANTS_HOENN_CUSTOM_H
