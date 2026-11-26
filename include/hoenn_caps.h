#ifndef GUARD_HOENN_CAPS_H
#define GUARD_HOENN_CAPS_H

// Hoenn & Seek 2.0 (part 4a): level caps after the eighth Johto badge
// (Kanto badges, Kanto champion, Hoenn badges, Hoenn E4). See src/hoenn_caps.c.
#if IS_HNS
u32 HoennGetPostJohtoLevelCap(u32 johtoCap, bool32 hard);
#endif

#endif // GUARD_HOENN_CAPS_H
