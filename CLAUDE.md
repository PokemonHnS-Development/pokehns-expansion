# Hoenn & Seek: notes for Claude sessions

A fork of Heart & Soul (HnS) 2.0.6 (pokeemerald-expansion 1.15.2) that adds Hoenn as an open, post-Emerald region. Design decisions, the audit and the 20-part roadmap live in the claude.ai Project "Pokemon":
- `claude/hns-hoenn-roadmap.md`
- `claude/hns-hoenn-design-decisions.md`
- `claude/hns-2.0.6-hoenn-audit.md`
- `claude/hns-hoenn-prestart-checklist.md`

Read the roadmap entry for the part you're working on before starting.

## Build
- `make hns RELEASE=1 -j$(nproc)` produces `pokehns-release.gba`. **Never use plain `make` or `make release`.** Those build the Emerald target, which is broken upstream (`FLAG_RECEIVED_TOGEPI_EGG`).
- Patch: `tools/hoenn/build_patch.sh <emerald-U.gba>` produces `dist/*.ups`. It verifies the base ROM sha1 and round-trips the patch.
- `tools/hoenn/build_patch.sh --debug <rom>` builds without RELEASE=1 (keeps the HnS debug menu for warping) and produces `dist/*-debug.ups`.
- Baselines for 2.0.6 with arm-none-eabi-gcc 13.2:
  - Release build: ROM 31,310,548 B (2,191 KB free), EWRAM 94.62%.
  - Non-release build: ~31.71 MB used (~1.76 MB free).
  - The official `pokemonHnS_v2.0.6.ups` output uses 31,707,732 B, which matches a non-release build. Our builds are not byte-identical to official (compiler differs).
  - Budget content against the release figure, but keep the debug build under 32 MB too, since testing uses it.
  - Report the ROM delta after any content change.
- Size history (ROM used / free):

| Part | Release | Debug |
|---|---|---|
| Baseline 2.0.6 | 31,310,548 / 2,191 KB | 31,706,804 / 1,804 KB |
| Part 2 (271 Hoenn layouts + tilesets) | 32,226,292 / 1,297 KB | 32,387,076 / 1,140 KB |
| Part 3 (351 Hoenn maps: headers, events, connections) | 32,318,292 / 1,207 KB | 32,479,076 / 1,050 KB |
| Part 4 (513 Hoenn trainers, trainer cap 864→1168) | 32,498,404 / 1,031 KB | 32,646,212 / 887 KB |
| Part 5 (Hoenn door animations, mapsecs, warp safety) | 32,527,764 / 1,002 KB | 32,675,540 / 858 KB |
| Part 6 (region map/Fly per region, Hoenn wild tables) | 32,547,620 / 983 KB | 32,695,364 / 839 KB |
| Part 7 (HM09 Dive, Steven's letter) | 32,549,332 / 981 KB | 32,698,084 / 836 KB |
| Part 8 (Oak's ticket, ferry, Mt. Silver gate, Hoenn new-game flags) | 32,551,572 / 979 KB | 32,700,308 / 834 KB |
| Part 9 (stamps on the trainer card, gym level scaling) | 32,552,996 / 978 KB | 32,701,860 / 833 KB |

## How the codebase is organized
- One tree builds Emerald, FRLG and HnS. Each map/layout's `game_version` field (`emerald` / `frlg` / `hns`) decides whether `tools/mapjson` compiles it into a build. Hoenn maps are tagged `emerald` and are currently excluded from HnS.
- **Hoenn inclusion lists (Hoenn & Seek):**
  - `data/hoenn/exclude.json` holds the hand-edited cut rules: prefixes, exact names, and substrings.
  - `tools/hoenn/gen_hoenn_lists.py` regenerates `data/hoenn/maps.json` and `data/hoenn/layouts.json` from it. Commit the generated files.
  - `tools/mapjson` treats any `emerald` layout or map listed in `data/hoenn/layouts.json` / `maps.json` as part of the HnS build. Map constants exist for every map; excluded maps get a NULL header.
  - Emerald maps that HnS already copied as `<Name>_hns` are skipped automatically.
- Emerald tilesets are compiled into HnS: `src/data/tilesets/headers.h` and `metatiles.h` use `#if !IS_FRLG`. In debug builds, 7 tilesets that no kept layout uses waste ~39 KB; release builds drop them through LTO/gc-sections.
- **Map sections (part 5).** `tools/hoenn/gen_hoenn_mapsecs.py` appends the 79 Hoenn sections used by kept maps to `hns_map_sections` in `src/data/region_map/region_map_sections.json` (HnS values 1–124 unchanged; Hoenn 125–203; `MAPSEC_NONE` = 204).
  - Before this, every Hoenn section was `= 0` in HnS.
  - Sections after `JOHTO_MAPSEC_END` make `GetRegionForSectionId()` return `REGION_HOENN`, but so do HnS's own Battle Frontier, Trainer Hill and Birth/Faraway/Southern Island sections. **Use `IsHoennMapSec(id)` from `include/hoenn.h` for runtime Hoenn checks** (part 6). It reads `include/constants/hoenn_mapsecs.h`, which `gen_hoenn_mapsecs.py` writes.
  - Four sections HnS already lists (ABANDONED_SHIP, LILYCOVE_CITY, SAFARI_ZONE, VICTORY_ROAD) sit before Pallet, outside every range, so they also count as Hoenn.
- **Region map and Fly (part 6):** `src/region_map.c` shows Emerald's Hoenn map whenever the player is in a Hoenn section, so Fly only reaches Hoenn towns from Hoenn and Johto/Kanto towns from there. The Pokédex area page (`src/pokedex_area_screen.c`) only marks areas in the region whose map is shown. Edge case: HnS's own contest lobby copy uses `MAPSEC_LILYCOVE_CITY`, so it shows the Hoenn map.
- **Wild encounters (part 6):** `tools/wild_encounters/wild_encounters_to_header.py` builds Emerald tables for maps in `data/hoenn/maps.json` into HnS (116 tables, in the TIME_DAY slot). Levels are still Emerald's; part 15 rescales them.
- **HM09 Dive (part 7):**
  - `ITEM_HM09` = 901, the slot after the HnS items (`ITEM_HM09_SLOT`, checked by a `STATIC_ASSERT` in `src/data/items.h`). `F(DIVE)` is appended to the HnS `FOREACH_HM`, which makes Dive teachable (151 species), unforgettable (`IsMoveHM`) and an HM in the bag.
  - `include/constants/tms_hms.h` now includes `constants/global.h`: `battle_anim_scripts.s` used to expand the HM list with `IS_HNS` undefined, which clashed at link time once both lists had `ITEM_HM_DIVE`.
  - Steven's house (`MossdeepCity_StevensHouse`): Steven is away, his letter is always on the table, and reading it gives HM09 (`FLAG_RECEIVED_HM_DIVE`, now a real Hoenn flag; `gen_hoenn_ids.py` remaps `FLAG_RECEIVED_HM_*` names that are 0 in HnS).
  - Dive still unlocks with `FLAG_BADGE07_GET` (Glacier Badge), which every player reaching Hoenn has. Surface with **B**.
  - Dive spots: Routes 124, 126, 127, 128 (deep water) and 134 (map script into Underwater Route 134; its Sealed Chamber door stays shut). Route 125 has no dive spots; `Underwater_Route125` only led to the Marine Cave and is unreachable.
- **Hoenn new-game state (part 8):** `tools/hoenn/gen_hoenn_newgame.py` writes `data/scripts/hoenn_new_game.inc` (`EventScript_ResetAllMapFlagsHoenn`): the flags Emerald sets at new game that are Hoenn-owned (146), then `data/hoenn/newgame_overrides.json` (post-Emerald state: what to show or hide). `NewGameInitData` runs it right after clearing the Hoenn flags. **Put post-Emerald object visibility in the overrides file**, not in map OnTransition scripts. Re-run after `gen_hoenn_ids.py`.
- **Hand-defined Hoenn flags/vars (part 8):** `include/constants/hoenn_custom.h`, in the reserved tails 0x1BC0–0x1BFF and 0x7070–0x707F (the generator stops before them). Stamp flags `FLAG_HOENN_STAMP_GYM_1..8` and `FLAG_HOENN_STAMP_WALLACE` live here.
- **Ferry and gating (part 8),** scripts in `data/scripts/hoenn_ferry.inc`:
  - Oak (16 badges) gives `ITEM_TIDAL_TICKET` (key item after `ITEM_HM09_SLOT`) instead of opening Mt. Silver.
  - Vermilion's sailor menu gets SLATEPORT CITY. It's a scrolling `dynmultichoice` because seven entries don't fit HnS's fixed multichoice.
  - Slateport and Lilycove harbor attendants (map.json script swapped) sail to Vermilion, the other harbor, or HnS's Battle Frontier. No S.S. Tidal interior ride. Arrivals: Hoenn harbors (8,11), Vermilion port (8,9).
  - Mt. Silver: `ReceptionGate_hns` OnTransition hides the Silver guard and sets `VAR_ROUTE28_SCIENTIST` = 1 once `FLAG_HOENN_STAMP_WALLACE` is set. Oak's later dialogue reflects it.
- **Stamps and gym scaling (part 9):**
  - Hoenn gym scripts set and check `FLAG_HOENN_STAMP_GYM_1..8` instead of `FLAG_BADGE0x_GET` (43 references in 20 kept Hoenn maps were rewritten once; new Emerald scripts brought in later need the same rewrite).
  - Trainer card: the back shows the 8 stamps (Emerald's badge art, loaded after HnS's 16 badges at BG3 tile 192+64) on tile rows 8–9, above the Kanto row. Rows 8–9 only overlap the link-trades stat line.
  - `src/hoenn_scaling.c`: `HoennScaleTrainerMonLevel()` is called from the one `CreateMon` in `CreateNPCTrainerPartyFromTrainer` (`HOENN_TRAINER_MON_LEVEL`). For Hoenn gym leaders the ace is 68 at 0 stamps up to 78 at 7 (`HoennGymAceLevel`); gym trainers get ace − 4; each mon keeps its Emerald gap below the ace. Moves without custom sets come from the new level.
  - `tools/hoenn/gen_hoenn_gyms.py` writes `src/data/hoenn_gym_trainers.h` (8 leaders, 57 gym trainers from maps whose name contains `_Gym`). Re-run after `gen_hoenn_ids.py`.
  - Gym leader text still says BADGE and lists HM uses, and gym TMs are still Emerald's (part 13).
- **Doors:** `src/field_door.c`'s `sDoorAnimGraphicsTable` includes Emerald's doors in HnS. The lookup matches metatile + tileset, so they don't clash with HnS doors.
- Each layout's `layout_version` selects the primary tileset size at runtime: HnS 640 tiles/7 palettes, Emerald 512/6. Hoenn layouts must stay `emerald`.
- C code switches on `IS_HNS` / `IS_FRLG` at build time (570 uses across 127 files). Hoenn needs some Emerald behavior at runtime, so convert those switches to region checks where needed. Don't flip them globally.
- **Hoenn IDs (part 4).** `tools/hoenn/gen_hoenn_ids.py` regenerates `include/constants/hoenn_{flags,vars,trainers}.h`, `src/data/trainers_hoenn.party` and `data/hoenn/remap_report.json`. Re-run it whenever `data/hoenn/maps.json` or Hoenn scripts change.
  - Those headers `#undef`/`#define` Emerald names so Hoenn gets its own IDs. They're included at the end of `flags.h`, `vars.h` and `opponents.h`.
  - `-DHOENN_NO_REMAP` turns the remap off; the generator uses it when resolving.
  - `tools/hoenn/resolve_consts.py` evaluates any constant with the real compiler.
- **Storage** (`include/constants/hoenn_layout.h`):
  - Hoenn flags 0x1800–0x1BFF and Hoenn trainer flags 0x1C00–0x1FFF live in `gSaveBlock3Ptr->hoennFlags`.
  - Hoenn vars 0x7000–0x707F live in `hoennVars`.
  - Reached through hooks in `GetFlagPointer`/`GetVarPointer` (`src/event_data.c`). Cleared in `NewGameInitData`. SaveBlock3 is 564 of 1,624 bytes.
  - Hidden-item flags must stay below 0x20E9 (13-bit offset from `FLAG_HIDDEN_ITEMS_START`); the generator puts them first.
- **Trainers.**
  - Hoenn trainers get IDs from `HOENN_TRAINERS_START` (653) up: 513 now, 653–1165.
  - Their "defeated" flags come from `TRAINER_FLAG_ID(id)` (used in `battle_setup.c`, `debug.c`), not `TRAINER_FLAGS_START + id`.
  - `MAX_TRAINERS_COUNT_HNS` was raised to 1168, which moves `TRAINER_PARTNER()` IDs and grows `sTrainerSlides`.
- **Remap rules:**
  - Remapped:
    - Emerald names that resolved to 0.
    - All `FLAG_HIDDEN_ITEM_*` (HnS collapses them onto one ID).
    - Emerald vars aliased onto HnS slots (e.g. `VAR_ROUTE121_STATE` == `VAR_NEWBARKTOWN_LABSTATE`).
  - Kept shared: `FLAG_SYS_*`, **`FLAG_BADGE0x_GET`** (same names as HnS badges; code does `FLAG_BADGE01_GET + n`), `FLAG_RECEIVED_HM_*`, vars HnS owns, and `*_UNSAFE`-aliased engine vars.
  - **Never remap a name HnS uses with arithmetic.** The generator's input is checked for that; re-check when adding names.
- HnS's own flags stay below the `ENGINE_FLAGS_START` pin (0x960). Old-save compatibility is **not** a goal.

## Known Hoenn issues (found in part 3, fix in later parts)
- **All Emerald map scripts and text were already assembled into HnS** (`data/event_scripts.s` includes every map's `scripts.inc`). Script and text cost is already in the baseline, so cutting story text *saves* ROM.
- **Flags and vars:** Emerald flag/var names resolve to 0 in HnS. FlagGet(0) is FALSE and FlagSet(0) does nothing; VarGet(0) returns 0 and VarSet(0) does nothing. Story `map_script_2` frame triggers therefore re-fire forever. Fix in part 4.
- **Dangling links (handled in part 5):**
  - `tools/hoenn/check_links.py` still lists the 21 targets, for reference.
  - **Doors:** `gen_hoenn_lists.py` writes `data/hoenn/blocked_maps.json`, and `tools/mapjson` emits warps into those maps inside `.if IS_HNS` with coordinates 0x7FFF, so the door stays shut (the warp keeps its index).
  - **Scripts:** `ApplyCurrentWarp` (`src/overworld.c`) refuses any warp whose map header is NULL and keeps the player in place.
  - Still to give a real destination: Lilycove contest lobby (part 17).
- **9 specials used by Hoenn maps have HnS-specific branches inside:**
  - `GameClear` (part 13)
  - `EnterSafariMode` / `ExitSafariMode` (part 17)
  - `HasAllRegionalMons` and `SetUnlockedPokedexFlags` (Birch / Pokédex)
  - `DoPCTurnOnEffect` (PC metatiles)
  - `ShowScrollableMultichoice`
  - `UpdateShoalTideFlag`
  - `BufferFanClubTrainerName`
  
  Re-check each when its area is worked on.
- **Part 4 leftovers:**
  - ~~Hoenn gyms still use HnS badge flags~~ Fixed in part 9 (stamp flags).
  - `VAR_ELITE_4_STATE` is shared with HnS's league (part 13).
  - Lilycove museum/contest flags that HnS's own contest copy references now really work (they used to be 0).
- **Space opportunities:**
  - `sTrainerSlides` (src/trainer_slide.c) is ~197 KB of NULL pointers sized `[3][TRAINER_PARTNER(PARTNER_COUNT)][slides]`; HnS defines no slides.
  - Curating Hoenn trainers to ≤211 (part 14) lets `MAX_TRAINERS_COUNT_HNS` drop back to 864.

## Conventions
- **Touch upstream HnS files as little as possible**, so future HnS fixes merge cleanly. Put new code and data in new `hoenn`-named files (`tools/hoenn/`, `src/hoenn_*.c`, `data/maps/*_hoenn/`, etc.) and keep edits to shared files to small hooks.
- Work on a `part-NN-<slug>` branch off `hoenn` and open a PR into `hoenn`. Don't commit to `master` (it mirrors upstream).
- **Emulator tests:** a libmgba harness (not in the repo yet) plays scripted input, takes screenshots and reads/writes memory. Useful recipes:
  - Debug menu: hold R + Start. Warp is Utilities → 2nd item; numbers use ↑/↓ for the value and → for the next digit.
  - Flags & Vars → items 14–16 turn off collision, encounters and trainer sight.
- Never commit ROMs, base ROMs or patches. `baserom/` and `dist/` are git-ignored.
- The project owner tests in mGBA. Every part should end with a building ROM and a patch.
