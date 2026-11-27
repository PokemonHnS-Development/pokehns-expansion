# Lane B: status

**Builder:** the account that was building 27a when the lanes were set up (Nov 27). After 27a it builds lane B. Rules: `README.md` in this folder.

**Owns:** Kanto, the Safari, Mewtwo/Mew and Hoenn's legends: 31b, 34a, 29, 30a, 30b, 33, 36, 35a. Maps and IDs: `README.md` sections 1 and 3.

Only lane B's builder edits this file (the reviewer may add a line when it merges).

## Parts
| Part | State | Branch / PR | Notes |
|---|---|---|---|
| 31b | PR open, Nov 27 | `v2-31b-honey-trail`, PR #90 | lane A's 37 needs it: built first. Hook for 37: the hollow pool's `HoennSeek_EventScript_MoonHollowPool`, flag `FLAG_HOENN_MOON_HOLLOW_FOUND` |
| 34a | PR open, Nov 27 | `v2-34a-birds`, PR #91 (stacked on #90) | lane A's 34b needs it. Feathers: `ITEM_FROST_FEATHER` (26b), `ITEM_THUNDER_FEATHER`, `ITEM_FLAME_FEATHER`; flags `FLAG_HOENN_GOT_*_FEATHER`, caught flags `FLAG_HOENN_*_CAUGHT` |
| 29 | PR open, Nov 27 | `v2-29-shifting-tunnels`, PR #TBD (stacked on #91) | progress-level wild battles: `HoennSetupProgressWildBattle` (`src/hoenn_lane_b.c`) |
| 30a | — | — | |
| 30b | — | — | |
| 33 | — | — | waits for lane A's 32; freezes wild tables (rule 3.6) |
| 36 | — | — | |
| 35a | — | — | |

## Claims on shared things
Anything outside lane B's ranges or maps, one line each, before the part that uses it.
- Seafoam: `SeafoamIslands_B1F_hns` (34a) and `SeafoamIslands_SecretCave_hns` (36).
- 31b: `Route45_BeekeeperHouse_hoenn` and `Route45_MoonHollow_hoenn` appended to `gMapGroup_SpecialArea2_Hns`; Route 45 (`Route45_hns`) got an ON_TRANSITION, three objects, a door and a patch; the Blackthorn Mart's cool trainer became a hint NPC (key `BlackthornMartTrainer`).
- 34a: two key items `ITEM_THUNDER_FEATHER` (907) and `ITEM_FLAME_FEATHER` (908), appended after `ITEM_FROST_FEATHER`. Script swaps: Bill (`GoldenrodCity_BillsHouse_hns`) and the Power Plant manager (`Route10_PowerPlantBackRoom_hns`). The bird objects on `Route10_hns`, `SeafoamIslands_B1F_hns` (now has an ON_TRANSITION) and `MtSilver_1F_MoltresRoom_hns` take lane B flags; those maps' OnTransitions got one `call` each, plus coord triggers. Route 113 got two objects, 11 triggers and an OnTransition `call`. Hint NPCs keyed `PowerPlantEngineer` (`Route10_PowerPlantEntrance_hns`) and `GlassWorkshopBoy` (`Route113_GlassWorkshop`); a Route 10 forecast.
- 29: `RockTunnel_OnixBore_hoenn` and `DarkCave_Burrow_hoenn` appended to `gMapGroup_SpecialArea2_Hns`. `RockTunnel_B1F_hns` got warps 6–12, an ON_LOAD, an ON_FRAME table and an OnTransition `call`; `DarkCave_SouthSide_hns` warps 3–7 and an ON_LOAD; `Route21_hns` five objects, a hidden item and an OnTransition `call`. Hint NPCs keyed `LavenderPokefan`, `VioletYoungster`, `PalletFatman`. Lane B hidden-item flags +0, +1.
