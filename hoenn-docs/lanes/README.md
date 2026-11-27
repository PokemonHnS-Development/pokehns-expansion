# Two builder lanes + one reviewer

**Status: approved by Aidan (Nov 27), who asked for the setup PR (section 5).** Decided: the reviewer Claude merges every builder PR; 35a is in lane B; the lane A builder builds the setup PR. Written against `hoenn` at `d16b90e4b8` (parts 1–26b merged, PR #79 = 24r open).

**Who is who.** Aidan runs three Claude accounts that share only this repo:
- **Lane A builder:** the account that wrote this proposal and the setup PR (Aidan's project "Pokemon Romhack", thread "Split remaining parts into two lanes"). It also built 24r (#79).
- **Lane B builder:** the account that was already building **27a** when the lanes were set up (Nov 27). It finishes 27a (a lane A part, built before the split; it keeps whatever IDs and files it used), then switches to lane B, starting with 31b. Lane A's builder picks up from 27b once 27a is merged.
- **Reviewer:** the third account. It reviews and merges.
If you're a new session and don't know your lane, ask Aidan before claiming a part.

Remaining parts: 27a–37 (14 parts), then 38–40 (finish).

**27a** was started by lane B's builder before the setup PR. It keeps whatever IDs and files it used; the rules below apply to every part after it. Whichever of 27a and the setup PR merges second syncs onto the other (rule 3.5).

## 1. The two lanes

The split follows **maps**: each lane owns a set of places, so its PRs rarely touch a map the other lane touches. Seafoam is the only place both lanes need (rule 3.2).

### Lane A: Johto, the Cipher and the sea (Lugia's side)
| Order | Part | Size | Maps / systems it touches | Needs |
|---|---|---|---|---|
| A1 | 27a Unown Cipher A (**built by lane B's builder**, started before the split) | M | Ruins of Alph (lab, Words rooms, new Rosetta wall) | 3 ✅ |
| A2 | 27b Unown Cipher B | L | glyph rings: Bell/Tin Tower, Mt. Moon (Cave), Ice Path, Whirl Islands, Mt. Mortar, Union Cave, **Seafoam 1F** | A1 |
| A3 | 28 Unown Cipher C | M | Ruins sanctum (new map), **PokéGear radio hook** | A2 |
| A4 | 31a Sneasel thief | M | Ice Path B2F/B3F | 3 ✅ |
| A5 | 32 Olivine nights | L | Route 41, Whirl Islands, Olivine, `light_paths.json` (25a ✅) | 25a ✅ |
| A6 | 34b Lugia | M | Whirl Islands, Slowpoke Well, Route 41 | 19 ✅, A5, **B2 (34a)** |
| A7 | 35b Ho-Oh, beasts, Celebi | L | Tin Tower roof, Ecruteak, Ruins puzzle, radio (Eusine), Ilex/Viridian/Petalburg Woods berry spots | 3 ✅ |
| A8 | 37 Jirachi, Deoxys, Regis, Arceus | L | Mt. Moon outside, Meteor Falls, Space Center, Sinjoh Ruins, Route 45 moon hollow | 22b/23/25b ✅, A3, **B1 (31b)** |

### Lane B: Kanto, the Safari, Mewtwo/Mew and Hoenn's legends
| Order | Part | Size | Maps / systems it touches | Needs |
|---|---|---|---|---|
| B1 | 31b Teddiursa honey trail | L | Route 45 + beekeeper house (buildings generator), honey tree, moon hollow (new map) | 3 ✅ |
| B2 | 34a Birds | L | Bill's house, Power Plant (Route 10 storm day), Route 113 ash, **Seafoam B1F** (Articuno), Mt. Silver Moltres room | 5 ✅, 26b ✅ |
| B3 | 29 Shifting tunnels | L | Rock Tunnel, Dark Cave, Route 21 | 3 ✅ |
| B4 | 30a Kangaskhan baby | M | Fuchsia Safari (Beach, Brush) | 3 ✅ |
| B5 | 30b Tauros stampede | M | Fuchsia Safari (Mountain, gate) | 3 ✅ |
| B6 | 33 Distribution + living dex | L | every wild table, overworld objects (see rule 3.6) | all of 15–32 (**A5**) |
| B7 | 36 Hoenn weather legendaries | L | Mt. Pyre, Route 19 cave, **Seafoam Secret Cave**, Sky Pillar, Embedded Tower, Southern Island, Pewter Museum | 5 ✅, 12 ✅ |

| B8 | 35a Mewtwo + Mew | L | Cinnabar, Silph Co., Celadon Game Corner, Rocket hideouts (incl. Mahogany's), Cerulean Cave, Mew's three grassy spots at dawn | 3 ✅ |

Load: lane A is 4 L + 4 M, lane B is 6 L + 2 M (Aidan put 35a in lane B, Nov 27). Lane B's 35a can swap with 36 freely; neither depends on the other.

### Then the lanes join (one at a time, in this order)
38 Sweep → 39a → 39b → 40 Bryan's playtest. They read and touch everything, so both builders stop new work; one builder does each part, the other only does review fixes.

## 2. Dependencies that force the order

| Dependency | Why | How the order handles it |
|---|---|---|
| 27a → 27b → 28 | one chain (Rosetta wall → fragments → sanctum) | lane A's first three parts |
| 28 → 37 | the Cipher's final inscription opens the Regi chain | A3 long before A8 |
| 32 → 34b | Lugia's shrine sits in 32's Lanturn lagoon | both lane A, in order |
| **34a (B) → 34b (A)** | Lugia's shrine needs the three feathers | B does 34a second; A needs it sixth |
| **31b (B) → 37 (A)** | the moon hollow is one of Jirachi's wishing spots | B does 31b first; A needs it last |
| **all events 15–32 → 33 (B)** | 33 removes the other sources of the one-of-a-kind species (Sneasel from 31a, …) | B6 waits for A5 (32). If A5 isn't merged yet, B swaps B6 and B7 |
| everything → 38–40 | audits and playthroughs | the join |

Cross-lane waits only happen if a lane falls far behind. When one would, the waiting lane builds its next independent part and says so in its lane file.

## 3. Coordination rules

### 3.1 Reserved ID ranges (applied in the setup PR, after approval)
Every range below is inside the blocks `include/constants/hoenn_events.h` already defines. Each lane adds its definitions **in its own section** of that file (`// ==== Lane A ====` near the phase-E block, `// ==== Lane B ====` near the phase-F block), never at the shared end of the file.

| Resource | Lane A | Lane B | Left over |
|---|---|---|---|
| Event flags, E Johto/Kanto block (0x21A0–0x21FF, 96) | +0x00–0x2F | +0x30–0x5F | — |
| Event flags, F Legendaries block (0x2200–0x227F, 128) | +0x00–0x3F | +0x40–0x7F | — |
| Daily flags (0x2300 block; 0x00–0x12 used) | 0x13–0x27 | 0x28–0x3B | 0x3C–0x3F |
| Weekly flags (0x2340 block; 0x00–0x08 used) | 0x09–0x22 | 0x23–0x3C | 0x3D–0x3F |
| Hidden-item flags (0x2000 block; 0x00–0x03 used) | 0x04–0x1F | 0x20–0x3B | 0x3C–0x3F |
| Event vars, E block (0x70A8, 40) | +0x00–0x13 | +0x14–0x27 | — |
| Event vars, F block (0x70D0, 24) | +0x00–0x0B | +0x0C–0x17 | — |
| PokéGear event call IDs (`hoenn_phone.h`, 0–36 used) | 37–69 | 70–99 | 100+ |
| Spare flag block (0x2290, 112) / spare vars (0x70F0, 16) | — | — | claimed by PR, reviewer approves |
| G Finish block (flags 0x2280, vars 0x70E8) | — | — | the join (38–40) |

If a lane runs out, it takes from Spare and writes the claim in its lane file in the same PR.

Things that **can't** be reserved by range, and the rule for each:
- **Key items** (`include/constants/items.h`, appended after `ITEM_FROST_FEATHER`): both lanes append; on a conflict keep both, in merge order. Never hard-code an item number in tests (use `pt.resolve`).
- **New maps** (`gMapGroup_SpecialArea2_Hns`, 9 of 127 used): both append; map numbers follow merge order. Never hard-code a map number.
- **Trainer IDs**: adding a Hoenn trainer shifts every ID after it. Avoid new trainers; if a part needs one, it says so in its lane file *before* starting, and the other lane re-runs the generators when it next syncs.
- **Roamer slots**: find by species/table, never by slot (already the rule). 35b (Raikou/Entei) is the only remaining roamer part.

### 3.2 Map ownership
A lane owns the maps in its table. **Touching a map the other lane owns needs a line in your lane file first**, and the reviewer merges those two PRs in sequence, never in parallel.
- **Seafoam is split by floor:** lane A uses `SeafoamIslands_1F_hns` for the FOAM glyph ring (27b); lane B owns `SeafoamIslands_B1F_hns` (Articuno, 34a) and `SeafoamIslands_SecretCave_hns` (Groudon, 36).
- **Mt. Moon:** all lane A (27b's ring in `MtMoon_Cave_hns`, 37's Jirachi outside). 31b only *mentions* Mt. Moon in text.
- **Route 113:** lane B (34a's Moltres ash). Its existing events (20, 24b) are done.
- **Radio:** lane A owns the PokéGear radio hook (28 builds it, 35b reuses it). Lane B doesn't touch the radio.

### 3.3 Shared code: one file per lane, small hooks
The hot spots today are `data/scripts/hoenn_hidden.inc` and `src/hoenn_hidden.c`, where every part appends at the end. Proposed:
- Lane A: `data/scripts/hoenn_lane_a.inc` + `src/hoenn_lane_a.c`. Lane B: `data/scripts/hoenn_lane_b.inc` + `src/hoenn_lane_b.c`. Named by lane, not region, because each lane mixes regions (lane A has Meteor Falls, lane B has Dark Cave). A part may add its own file instead (`hoenn_cipher.inc`, …) if it's big; it's still that lane's file.
- **Phone:** `HoennHiddenDueCall()` ends with `return HoennLaneADueCall();`, which ends with `return HoennLaneBDueCall();`. The event-call `switch` in `hoenn_phone.inc` falls through to `HoennSeek_EventScript_PhoneEventLaneA` (in lane A's file), then `…LaneB`. Each lane only edits its own function and switch.
- **Phone call texts** go in the lane's own script file, next to its scenes.
- Text files, `event_scripts.s` includes, `hoenn_phone.inc`: the setup PR adds a lane A and a lane B section marker in each, far apart, so appends never land on adjacent lines.

### 3.4 Generated files: never hand-merge
`npc_hints.json` was the one real trap: **the generator named hint wrappers by list position** (`HoennSeek_EventScript_HintNpc%d`), so two lanes each appending an NPC both made "HintNpc55", and after the merge the second one's map object was matched to the wrong entry. Since the setup PR, **every new hint NPC needs a `"key"`** (letters, digits, `_`; unique), and its wrapper is `HoennSeek_EventScript_Hint_<key>`. The first 55 entries keep their old positional names, so they must never be moved or deleted (the generator stops if an entry past them has no key). Building NPCs get keys from their building automatically.

For every generated file (maps' `map.json` objects, `hoenn_hints.inc`, `hoenn_flags.h`/`vars.h`/`trainers.h`, composed layouts, light paths, overworld Pokémon, …): on a conflict, **take `hoenn`'s side, keep both sides of the hand-written inputs (the JSON in `data/hoenn/`, scripts), then run `tools/hoenn/regen_all.sh`** and rebuild. It runs all 20 generators in their dependency order (listed in its header). On a clean tree, `regen_all.sh --check` must report no changes; if it doesn't, a generator or an input is out of date.

### 3.5 Claiming, syncing, merging
- **Claim:** a part is claimed by pushing its branch `v2-NN-<slug>` and a line in your lane file (`hoenn-docs/lanes/lane-a.md` / `lane-b.md`: "27a: claimed, Nov 27, branch …"). The roadmap itself isn't edited for claims.
- **Sync before PR:** `git fetch origin hoenn && git merge origin/hoenn` into your branch (merge, not rebase: no force pushes), `regen_all.sh`, rebuild release + debug, re-measure size, re-run one smoke test of your event. Do it again if `hoenn` moved before your PR is merged.
- **Draft until synced:** open the PR as a draft; mark it ready only after the sync.
- **Merge order:** the reviewer merges, one PR at a time, in the order PRs became ready (first ready, first merged), except that a PR the other lane is waiting on (31b, 34a, 32) jumps the queue. After each merge, the other lane's open PR syncs again before it can merge.
- **Builders don't wait for the merge** to start their next part: they branch the next part off `hoenn` and merge their own previous branch in if it isn't merged yet.

### 3.6 Part 33's freeze
33 touches every wild table and many overworld objects. While it's open, lane A doesn't edit `wild_encounters*.json`, `wild_rules.json`, `weather_wild.json` or `ow_mons.json`; if a lane A part needs a wild-table change, it waits for 33 to merge or lists the change for 33 to include.

### 3.7 Docs without conflicts
| Doc | Today | Proposed |
|---|---|---|
| Roadmap status paragraph | every part rewrites one long line | frozen at "see `hoenn-docs/lanes/`"; each lane keeps its status (claimed / PR / merged / next) in its own lane file |
| Roadmap tables | ✅ on adjacent rows | each lane only marks ✅ on its own rows; the setup PR regroups the remaining rows into a lane A table and a lane B table so edits are never adjacent |
| CLAUDE.md size table | one table, a row per part | two tables, "Lane A sizes" and "Lane B sizes", each row the whole ROM measured **after syncing**, so the newest row in either is the current size |
| CLAUDE.md codebase notes | a bullet per part, appended at one spot | two sections, "Lane A parts" and "Lane B parts", far apart |
| Playtest checklist | appended at the end | a lane A and a lane B section |
| `review-notes.md` | shared | only the reviewer writes it |

**ROM budget:** 831 KB release / 675 KB debug free after 26b. Parts 18–26b averaged ~4–6 KB. Each lane gets a soft budget of **250 KB release**, leaving ~330 KB for the join and fixes; a part over 25 KB says why in its PR.

## 4. The reviewer

- **What it reviews:** every builder PR, in the merge order above. Checklist per PR: the part's "Done when"; IDs inside the lane's ranges; no edits to the other lane's maps or files without a lane-file note; generated files match a fresh `regen_all.sh`; release + debug build; size row; debug `.ups` and screenshots in `/mnt/project-files/hoenn-2.0/part-NN/`; edge-case pass done; phone and hint lines added; docs updated in the right lane section.
- **Plays it:** applies the debug patch, runs the part's event once in the harness (as 24r did), and checks the map art at 2× (the hand-made-maps convention).
- **Writes notes, not fixes:** findings go in `review-notes.md` with the part number. Small fixes go back to the owning lane as an `NNr` part before its next part; the reviewer only builds a fix itself when it's cross-lane (both lanes' code) or the owning lane is mid-part and the fix blocks the other lane.
- **Merges (decided, Aidan Nov 27):** the reviewer is the one that merges every builder PR, after its review passes and within the run Aidan has authorised, then tells the other lane to sync. Builders never merge their own PRs.
- **Order when two PRs are ready at once:** the one the other lane depends on first (31b, 34a, 32), then the older one. Review fixes (`NNr`) go before new parts of the same lane.
- **At the join:** the reviewer runs 38's audit checklist against both lanes' notes, then reviews 39a/b's fixes.

## 5. Setup PR (built by the lane A builder; PR #85)
One small PR before either lane starts, so neither lane has to touch shared files for structure. All six are done in PR #85 (no content; release −96 B, debug +32 B; hint NPCs and the phone chain emulator-tested):
1. `hoenn_events.h`: lane A / lane B section markers and the range comments from 3.1 (no flags defined yet).
2. `hoenn_phone.h` call-ID range comments; `HoennLaneADueCall` / `HoennLaneBDueCall` stubs chained after `HoennHiddenDueCall`, and the phone switch falling through to each lane.
3. New empty lane script/source files, included and built.
4. `gen_hoenn_hints.py`: stable keys instead of list positions (re-run; no behavior change).
5. `tools/hoenn/regen_all.sh`.
6. Docs: `hoenn-docs/lanes/lane-a.md` + `lane-b.md`, the roadmap regrouped into lane tables, CLAUDE.md lane sections and size tables, playtest checklist sections, README pointer.

## Questions Aidan answered (Nov 27)
- ~~Is 35a a floater?~~ Decided: lane B.
- ~~Who merges?~~ Decided: the reviewer.
- ~~Who builds the setup PR?~~ Decided: the lane A builder.
