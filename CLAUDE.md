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
| Part 10 (post-Emerald state, west/south; +6 script-swapped layouts) | 32,583,540 / 948 KB | 32,732,404 / 803 KB |
| Part 11 (post-Emerald state, north/east; scaled Kecleon, gifts moved) | 32,584,628 / 947 KB | 32,733,460 / 801 KB |
| Part 12 (post-Emerald state, sea; legendary sites sealed: −Cave of Origin, −Seafloor Cavern, −2 swap layouts) | 32,551,860 / 979 KB | 32,700,660 / 834 KB |
| Part 13 (dialogue pass, Steven's stone case, gym story side effects removed) | 32,554,436 / 976 KB | 32,702,916 / 831 KB |
| Part 14a (Mossdeep mind reader: IVs and abilities for Star Pieces) | 32,558,132 / 973 KB | 32,706,228 / 828 KB |

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
  - Gym leader text talks about stamps since part 13 ("ROXANNE stamped {PLAYER}'s TRAINER CARD…"). Gym TMs are still Emerald's.
- **Story strip (part 10+):** Hoenn starts in its post-Emerald state instead of having story scripts deleted.
  - `data/hoenn/newgame_overrides.json` sets each story var to its after-the-story value (so its coord/frame triggers never fire) and shows/hides story objects. Emerald's scripts stay as they are.
  - `tools/hoenn/story_audit.py PREFIX...` lists, per map, the triggers (with the var value that fires them), flag-hidden objects and every value each var is set to. Use it to pick final values for the next area; `@ State descriptions` comments in Emerald scripts document some vars.
  - The generator only accepts Hoenn-owned names (remapped, or HnS-reserved `*_UNSAFE` slots).
  - Part 10 covers Littleroot–Rustboro, Dewford, Slateport, Mauville, Routes 101–110 and 116–118. Notable choices: Birch is home with the three Johto starters on his table (no "catch every Hoenn Pokémon" gate); both Littleroot houses belong to the rival families (Brendan/May themselves come in part 16); Rusturf Tunnel is open; Petalburg Gym is open from the start (the other gyms no longer advance `VAR_PETALBURG_GYM_STATE`).
- **Story strip, north and east (part 11):** overrides cover Mauville→Fortree→Lilycove, Lavaridge/Mt. Chimney/Jagged Pass, Meteor Falls, Mt. Pyre, the Weather Institute and both hideouts (empty, Groudon gone). Story gifts that the deleted events used to hand out moved to `data/scripts/hoenn_story.inc`:
  - Flannery gives the Go-Goggles after her battle; Wattson gives the Basement Key after his (Thunderbolt TM once New Mauville is done).
  - Mr. Stone (Devon 3F) gives a Lucky Egg instead of the Exp. Share H&S already hands out.
  - Route 120: Steven is replaced by a Devon field tester (Devon employee sprite) who gives the Devon Scope after the Kecleon; he fades out instead of flying.
  - `special HoennSetupScaledWildBattle` (`src/hoenn_scaling.c`) starts a wild battle with `VAR_0x8004` as species at gym-ace level − 8 (60–70). Use it for any other scripted Hoenn wild battle.
- **Story strip, sea (part 12):** overrides cover Mossdeep and the Space Center (after Magma's raid), Sootopolis (state 6: gym open, the Cave of Origin expert guards the door), Route 128, Pacifidlog and the Abandoned Ship (Scanner hidden; Captain Stern's quest is cut).
  - Steven's house: the old Beldum ball is Steven's stone case (`HoennSeek_EventScript_StevensStone`, part 13). The player picks one stone: EVOLUTION (10 stones + Oval Stone) or OTHER (Everstone, Hard/Float Stone, Odd Keystone). **No Megas in Hoenn & Seek:** nothing gives a Mega Ring or Mega Stone, and NPC teams use non-Mega forms. Lists live in `src/hoenn_specials.c`.
  - The Weather Institute scientist moves to (2,2) once `FLAG_SYS_GAME_CLEAR` is set (every Hoenn visitor has it), so look for him there.
- **Legendary sites sealed until 2.0 (part 12, one commit: "Seal Hoenn's legendary sites").** To undo it: `git revert --no-commit 23adc4fc && git checkout HEAD -- CLAUDE.md` (that commit also carries these notes), then re-run the generators and update the notes. It:
  - adds `CaveOfOrigin_`, `SeafloorCavern_` and `Underwater_SeafloorCavern` to `data/hoenn/exclude.json` (Sky Pillar, Sealed Chamber, the Regi caves, Terra/Marine Cave and the islands were already excluded since part 2);
  - puts a sign event running `HoennSeek_EventScript_SealedSite` (`data/scripts/hoenn_sealed.inc`) on each entrance tile: Routes 105, 111, 120 and 131, Sootopolis and Underwater Route 128. The Sealed Chamber hole on Underwater Route 134 is walk-on, so it gets a step trigger that shows the text and moves you back;
  - drops Mirage Island (Route 130 never swaps its layout) and the Sootopolis legends layout, and stops the Weather Institute scientist from starting abnormal weather (Terra/Marine Cave). `FLAG_SYS_WEATHER_CTRL` is never set in our world, so the Groudon/Kyogre clash weather can't show either.
- **Dialogue pass (part 13):** you're a visitor from Johto, not Brendan or May. `tools/hoenn/dialogue_audit.py [--all] [PREFIX...]` lists reachable texts that still assume the Emerald story (Mom, Norman as dad, `{RIVAL}`, Brendan/May, Magma/Aqua, "moved here", champion); it follows branches on story vars too, so check each hit's script.
  - New and replacement NPC scripts are in `data/scripts/hoenn_dialogue.inc` (map.json script swaps); rewritten Emerald lines stay in their map's `scripts.inc`.
  - Specials (`src/hoenn_specials.c`): `specialvar VAR_RESULT, HoennGetStampCount`; `specialvar VAR_RESULT, HoennBufferFollower` (TRUE if a Pokémon follows you; nickname in STR_VAR_1, species in STR_VAR_2); `HoennPushStoneList` / `HoennStoneFromIndex` for Steven's case.
  - Gym guides call `HoennSeek_EventScript_GymGuideGreeting` first: the greeting changes at 0, 1–3 and 4–7 stamps.
  - Littleroot: May's house is Norman's family (May's mom), Brendan's house is Birch's. The twin outside mistakes you for Brendan or May (by player gender). `FLAG_RESCUED_BIRCH` is set at new game so she stands in her normal spot.
  - Reformed teams: Aqua runs sea rescues from the Lilycove hideout, Magma does research. Lilycove, Mossdeep, the Weather Institute, Cozmo, Capt. Stern, the museum grunt and the Route 110 sign say so.
  - Follower lines: May's mom, the Slateport shopper, the Fortree boy and the Lavaridge bather.
  - **Gym leader scripts had Emerald story side effects that undid the post-Emerald state** (removed): Roxanne set `VAR_RUSTBORO_CITY_STATE` to 1 (Devon Goods theft replayed), Brawly armed Roxanne's PokéNav call, Winona armed Scott's, Tate & Liza restarted the Space Center raid, Norman hid Mr. Briney and moved Wattson out of his gym, then ran the Wally's-dad/HM Surf scene. Leaders no longer register in the PokéNav. Check any other scripts brought in later for `setvar`/`setflag` lines like these.
- **Mossdeep mind reader (part 14a):** Emerald's unused link-games building (`MossdeepCity_GameCorner_1F`) is the guru's parlor; scripts in `data/scripts/hoenn_mind_reader.inc`, specials in `src/hoenn_specials.c`.
  - Locked until Tate & Liza are beaten (`FLAG_HOENN_STAMP_GYM_7`); `FLAG_HOENN_MET_MIND_READER` (0x1BD2) skips his intro after the first visit.
  - POTENTIAL: one IV to 31 for 1 Star Piece (the list shows current IVs). ABILITY: the species' other regular ability for 1, its hidden ability for 3. Star Pieces: a handful on Hoenn/Johto routes, and wild Staryu/Starmie can hold them.
  - **Dynamic menus free every entry's name when they close**, so anything pushed with `MultichoiceDynamic_PushElement` must be an `Alloc`ed copy, never a pointer into ROM (that hung the ability list).
- **Script-swapped layouts (part 10):** `gen_hoenn_lists.py` also keeps layouts that kept maps swap in with `setmaplayoutindex` (Birch's lab table, Shoal Cave tides, ...). Missing ones drew a black screen. Part 12 dropped the Mirage Island and Sootopolis legends ones.
- **Doors:** `src/field_door.c`'s `sDoorAnimGraphicsTable` includes Emerald's doors in HnS. The lookup matches metatile + tileset, so they don't clash with HnS doors.
- Each layout's `layout_version` selects the primary tileset size at runtime: HnS 640 tiles/7 palettes, Emerald 512/6. Hoenn layouts must stay `emerald`.
- C code switches on `IS_HNS` / `IS_FRLG` at build time (570 uses across 127 files). Hoenn needs some Emerald behavior at runtime, so convert those switches to region checks where needed. Don't flip them globally.
- **Hoenn IDs (part 4).** `tools/hoenn/gen_hoenn_ids.py` regenerates `include/constants/hoenn_{flags,vars,trainers}.h`, `src/data/trainers_hoenn.party` and `data/hoenn/remap_report.json`. Re-run it whenever `data/hoenn/maps.json` or Hoenn scripts change.
  - Those headers `#undef`/`#define` Emerald names so Hoenn gets its own IDs. They're included at the end of `flags.h`, `vars.h` and `opponents.h`.
  - They include `constants/global.h` themselves (part 10 fix): `config/randomizer.h` pulls in `vars.h` before `IS_HNS` is defined in the `.s` files, so until part 10 **the var remap never applied to assembled scripts** and Emerald scripts wrote HnS's var slots.
  - `-DHOENN_NO_REMAP` turns the remap off; the generator uses it when resolving.
  - `tools/hoenn/resolve_consts.py` evaluates any constant with the real compiler.
- **Storage** (`include/constants/hoenn_layout.h`):
  - Hoenn flags 0x1800–0x1BFF and Hoenn trainer flags 0x1C00–0x1FFF live in `gSaveBlock3Ptr->hoennFlags`.
  - Hoenn vars 0x7000–0x707F live in `hoennVars`.
  - Reached through hooks in `GetFlagPointer`/`GetVarPointer` (`src/event_data.c`). Cleared in `NewGameInitData`. SaveBlock3 is 564 of 1,624 bytes.
  - Hidden-item flags must stay below 0x20E9 (13-bit offset from `FLAG_HIDDEN_ITEMS_START`); the generator puts them first.
- **Trainers.**
  - Hoenn trainers get IDs from `HOENN_TRAINERS_START` (653) up: 506 now (part 12), 653–1158.
  - Their "defeated" flags come from `TRAINER_FLAG_ID(id)` (used in `battle_setup.c`, `debug.c`), not `TRAINER_FLAGS_START + id`.
  - `MAX_TRAINERS_COUNT_HNS` was raised (1160 since part 12; the generator sets it), which moves `TRAINER_PARTNER()` IDs and grows `sTrainerSlides`.
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
