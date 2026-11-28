#ifndef GUARD_HOENN_FLAGS_H
#define GUARD_HOENN_FLAGS_H

// Hoenn & Seek's flag and var storage (src/hoenn_flags.c).
// ID ranges: constants/hoenn_layout.h. 2.0 allocations: constants/hoenn_events.h.
#include "constants/hoenn_layout.h"

#if IS_HNS
u8 *HoennGetFlagPointer(u16 id);
u16 *HoennGetVarPointer(u16 id);
void HoennClearAllFlagsAndVars(void);
void HoennClearEventFlagsAndVars(void);
void HoennClearDailyFlags(void);
void HoennClearWeeklyFlags(void);
void HoennClearNightlyFlags(void);
#endif

#endif // GUARD_HOENN_FLAGS_H
