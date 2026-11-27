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
| 32 | merged (PR #97, Nov 27; reworked in review into a rescue: three BERRIES for trust, the Ampharos rides as your follower, a lighthouse arrival scene); **built by lane A, finished by lane B's builder and the reviewer** | PR #97 | built by lane A. Lane B's builder now owns it: review fixes, syncs onto `hoenn`, and the follow-up for its own 33. Its IDs stay in lane A's ranges (flags `HOENN_LANE_A_FLAGS_E` + 0x27–0x2D, daily + 1, var `HOENN_LANE_A_VARS_E` + 0, call 40) and its code in lane A's files; lane A keeps out of the branch. 34b (lane A) builds on it once it merges |
| 34b | ✅ merged (PR #106, Nov 27; reviewed and merged by lane A at Aidan's request) | `v2-34b-lugia` | flags `HOENN_LANE_A_FLAGS_F` + 0x0E–0x10, call 46 (35b has F + 0x00–0x0D, 37 F + 0x20 on; calls 41–45 stay with 35b, 28, 37) |
| 35b | PR #99 merged (Nov 27, review item 49: Ilex soil moved to (30,35)) | `v2-35b-johto-legends` | flags `HOENN_LANE_A_FLAGS_F` + 0x00–0x0D, daily + 2–4, call 41; built the radio hook (`HoennRadioEusineReport` in OAK's POKéMON TALK), so 28 reuses it instead of building it |
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
- 35b: Celadon Pokémon Center (EUSINE's object script), Tin Tower 1F (middle sage) and both roofs, Ecruteak City (one object, an ON_FRAME table, an OnTransition call), bg events in Ilex Forest, Viridian Forest and Petalburg Woods; one hook line each in `src/pokenav_radio.c` (OAK's POKéMON TALK intro) and `src/hoenn_roamer.c`.
- 34b: HnS's `WhirlIslands_LugiaChamber_hns/scripts.inc` (one `goto_if_unset` line), Route 41's coord events (row 56) and `OlivineCity_PokemonCenter_hns`'s fisher (hint). Writes HnS's `FLAG_HIDE_WHIRL_ISLANDS_TENTACRUEL` and `VAR_COMPLETED_LUGIA` (3 → 4 only).
