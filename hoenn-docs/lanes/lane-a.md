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
| 28 | PR #101 open (Nov 27), waiting for review; synced onto `hoenn` after #92 (31a) | `v2-28-cipher-sanctum` | built on 27b (#88) + 27r (#93); flags `HOENN_LANE_A_FLAGS_E` + 0x16–0x1A (0x1B–0x1F spare), daily + 5, call 42 |
| 31a | merged (PR #92, Nov 27) | `v2-31a-sneasel-thief` | flags `HOENN_LANE_A_FLAGS_E` + 0x20–0x26, daily + 0x00, call 39 (built while #88 (27b) waits for review; 27b took + 0x0B–0x15 and call 38, 28 gets + 0x16–0x1F, 32 + 0x27–0x2F) |
| 32 | — | — | lane B's 33 waits for it |
| 34b | next (Nov 27): 34a is merged; builds on part 32 (#97, now lane B's) | — | flags F + 0x0E–0x1F, vars F + 2 on, call 46 on |
| 35b | — | — | |
| 37 | PR open (Nov 27), waiting for review; **stacked on 28 (#101)**, so it merges after #101 | `v2-37-wishes-and-giants` | flags `HOENN_LANE_A_FLAGS_F` + 0x20–0x2D (0x2E–0x3F spare; 34b takes + 0x0E–0x1F), vars `HOENN_LANE_A_VARS_F` + 0, 1, calls 43–45 |

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
- Part 37: `data/scripts/hoenn_lane_b.inc` (lane B's file): one line in `HoennSeek_EventScript_MoonHollowPoolNight` hands the pool at night to lane A's wish (the hook 31b left for 37).
- Part 37 (HnS maps, all lane A's in README section 1): `MtMoon_Outside_hns` (white rock sign + Jirachi object swapped), `OlivineCity_hns` (the ticket fan swapped), `SinjohRuins_hns` (three boulder objects, one OnTransition `call`), `SinjohRuins_ArceusRoom_hns` (one hook line), and Hoenn's `MossdeepCity_SpaceCenter_2F` (scientist swap, window signs) and `MeteorFalls_Clifftop_hoenn` (boulder signs).
