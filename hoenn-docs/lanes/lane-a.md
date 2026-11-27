# Lane A: status

**Builder:** the account that built the lane setup PR (Aidan's project "Pokemon Romhack"). Rules: `README.md` in this folder.

**Owns:** Johto, the Unown Cipher and the sea: 27a (built by lane B's builder), 27b, 28, 31a, 32, 34b, 35b, 37. Maps and IDs: `README.md` sections 1 and 3.

Only lane A's builder edits this file (the reviewer may add a line when it merges).

## Setup
- Lane setup PR #85 (rules, ranges, lane files, hint keys, `regen_all.sh`): built by lane A, merged by the reviewer (Nov 27) after syncing it onto 27a.

## Parts
| Part | State | Branch / PR | Notes |
|---|---|---|---|
| 27a | merged (Nov 27; review fixes by the reviewer before merging) | PR #86 | built by lane B's builder; flags `HOENN_LANE_A_FLAGS_E` + 0x00–0x0A, call 37: **27b continues from + 0x0B and call 38** |
| 27r | merged (PR #93, Nov 27) | `v2-27r-cipher-fixes` | review items 34–35 (reading the floor lines from the wall; the word changing at midnight). Goes before 27b; #88 will be synced onto it |
| 27b | merged (PR #88, Nov 27; the reviewer hid the follower while a ring is out) | `v2-27b-cipher-sites` | E +0x0B–0x15, call 38; touches HnS maps Bell Tower 2F, Mt. Moon Square, Ice Path 1F, Whirl Islands B2F, Mt. Mortar 1F south, Union Cave B1F, Seafoam 1F (all lane A's) |
| 28 | merged (PR #101, Nov 27; the reviewer turned the floating Unown to face you and fixed the sanctum's top edge) | `v2-28-cipher-sanctum` | built on 27b (#88) + 27r (#93); flags `HOENN_LANE_A_FLAGS_E` + 0x16–0x1A (0x1B–0x1F spare), daily + 5, call 42 |
| 31a | merged (PR #92, Nov 27) | `v2-31a-sneasel-thief` | flags `HOENN_LANE_A_FLAGS_E` + 0x20–0x26, daily + 0x00, call 39 (built while #88 (27b) waits for review; 27b took + 0x0B–0x15 and call 38, 28 gets + 0x16–0x1F, 32 + 0x27–0x2F) |
| 32 | PR open (Nov 27), waiting for review; **handed to lane B's builder (Aidan, Nov 27)** | PR #97 | built by lane A. Lane B's builder now owns it: review fixes, syncs onto `hoenn`, and the follow-up for its own 33. Its IDs stay in lane A's ranges (flags `HOENN_LANE_A_FLAGS_E` + 0x27–0x2B, daily + 1, call 40) and its code in lane A's files; lane A keeps out of the branch. 34b (lane A) builds on it once it merges |
| 34b | paused (Nov 27): waits for lane B's 34a (`v2-34a-birds`) and part 32 (#97) to merge | — | needs lane B's 34a |
| 35b | — | — | |
| 37 | paused (Nov 27): waits for lane B's 31b (`v2-31b-honey-trail`) and part 28 (#101) to merge | — | needs lane B's 31b |

## ID plan (inside lane A's ranges)
So parts built out of order don't collide: 27b E +0x0B–0x15 (used); 28 E +0x16–0x1F; 31a E +0x20–0x25; 32 E +0x26–0x2F; 34b, 35b, 37 F +0x00 on. Calls 38 (27b) on, in build order. Vars, daily, weekly and hidden flags in build order.

## Claims on shared things
Anything outside lane A's ranges or maps (a spare flag, another lane's map, a new trainer ID), one line each, before the part that uses it.
- Seafoam: `SeafoamIslands_1F_hns` only (27b's FOAM ring).
- `data/specials.inc`: 27b added a lane A block and an empty lane B block after `HoennCipherWordCount` (like the other markers); lane B adds its specials under its own marker.
- `src/event_object_movement.c`: one hook line (27b, `HoennObjectPaletteSpecies`).
- `RuinsOfAlph_Outside_hns` (28): three Unown objects, warp 10 and a sign at the boulder (23,27), an ON_LOAD entry and one OnTransition `call`.
- `src/pokenav_radio.c` (28): `#include "hoenn.h"` (the same line 35b adds) and one line in the Unown station's case.
- `gMapGroup_SpecialArea2_Hns` (28): `RuinsOfAlph_Sanctum_hoenn` appended.
- `tools/hoenn/gen_hoenn_composed_maps.py` (28): `"border": "source"` copies the source layout's border.
