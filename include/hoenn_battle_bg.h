#ifndef GUARD_HOENN_BATTLE_BG_H
#define GUARD_HOENN_BATTLE_BG_H

// Hoenn & Seek 2.0 (part 13b): battle backgrounds of their own for Hoenn places
// (Route 111's desert, Route 113's ash, Mt. Pyre's graves). See src/hoenn_battle_bg.c.

#if IS_HNS
// Hooks in upstream files (one line each)
s32 HoennMapEnvironment(s32 mapDefault, u16 tileBehavior); // BattleSetup_GetEnvironmentId(), src/battle_setup.c
void HoennBattleBackground(u32 environment, u32 timeOfDay, const void **tileset, const void **tilemap, const void **palette); // LoadBattleEnvironmentGfx(), src/battle_bg.c
void HoennBattleBackgroundEntry(u32 environment, const void **tileset, const void **tilemap); // LoadBattleEnvironmentEntryGfx(), src/battle_bg.c
#endif

#endif // GUARD_HOENN_BATTLE_BG_H
