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
| 27r | next (reviewer, Nov 27) | — | review items 34–35 (reading the floor lines from the wall; the word changing at midnight). Goes before 27b |
| 27b | after 27r, after 27a merges and Aidan says go | — | |
| 28 | — | — | |
| 31a | — | — | |
| 32 | PR open (Nov 27), waiting for review | `v2-32-olivine-nights` | flags `HOENN_LANE_A_FLAGS_E` + 0x27–0x2B, daily + 1, call 40; lane B's 33 can start once it merges |
| 34b | — | — | needs lane B's 34a |
| 35b | — | — | |
| 37 | — | — | needs lane B's 31b |

## Claims on shared things
Anything outside lane A's ranges or maps (a spare flag, another lane's map, a new trainer ID), one line each, before the part that uses it.
- Seafoam: `SeafoamIslands_1F_hns` only (27b's FOAM ring).
