# Lane B: status

**Builder:** the account that was building 27a when the lanes were set up (Nov 27). After 27a it builds lane B. Rules: `README.md` in this folder.

**Owns:** Kanto, the Safari, Mewtwo/Mew and Hoenn's legends: 31b, 34a, 29, 30a, 30b, 33, 36, 35a. Maps and IDs: `README.md` sections 1 and 3.

Only lane B's builder edits this file (the reviewer may add a line when it merges).

## Parts
| Part | State | Branch / PR | Notes |
|---|---|---|---|
| 31b | PR open, Nov 27 | `v2-31b-honey-trail`, PR #TBD | lane A's 37 needs it: built first. Hook for 37: the hollow pool's `HoennSeek_EventScript_MoonHollowPool`, flag `FLAG_HOENN_MOON_HOLLOW_FOUND` |
| 34a | — | — | lane A's 34b needs it: build it second |
| 29 | — | — | |
| 30a | — | — | |
| 30b | — | — | |
| 33 | — | — | waits for lane A's 32; freezes wild tables (rule 3.6) |
| 36 | — | — | |
| 35a | — | — | |

## Claims on shared things
Anything outside lane B's ranges or maps, one line each, before the part that uses it.
- Seafoam: `SeafoamIslands_B1F_hns` (34a) and `SeafoamIslands_SecretCave_hns` (36).
- 31b: `Route45_BeekeeperHouse_hoenn` and `Route45_MoonHollow_hoenn` appended to `gMapGroup_SpecialArea2_Hns`; Route 45 (`Route45_hns`) got an ON_TRANSITION, three objects, a door and a patch; the Blackthorn Mart's cool trainer became a hint NPC (key `BlackthornMartTrainer`).
