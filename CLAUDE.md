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
| Part 14 (trainer curation 506→211, cap back to 864; Devon Scope backtrack, Rusturf dig, TV news) | 32,461,540 / 1,067 KB | 32,609,716 / 922 KB |
| Part 13b (badges wording, gym prerequisites, Rare Candies, League + Wallace, rematches) | 32,465,204 / 1,063 KB | 32,613,284 / 919 KB |
| Part 15 (Hoenn wild levels 35–70, 36 night tables, 41 items upgraded) | 32,467,444 / 1,061 KB | 32,615,540 / 917 KB |
| Part 16a (Aqua/Magma quests, Maxie + Archie double, Norman's call, Brendan & May; 220 trainers, cap 880) | 32,480,596 / 1,048 KB | 32,628,660 / 904 KB |
| Part 16b (harbor aide, Birch's Mudkip, Wally at the lab, Steven's shiny Beldum egg) | 32,483,380 / 1,045 KB | 32,631,412 / 901 KB |
| Part 16c (36 Hoenn phone trainers + rematch teams; 256 trainers, cap 912) | 32,510,404 / 1,019 KB | 32,658,548 / 874 KB |
| Part 16d (Brendan & May's calls, Elm's Johto starters, Wally's rematch calls, relationship lines; 257 trainers) | 32,517,300 / 1,012 KB | 32,665,236 / 868 KB |
| Part 17 (Lilycove contest door into HnS's lobby, Hoenn Safari exits, May's contest call) | 32,518,116 / 1,012 KB | 32,665,876 / 867 KB |
| Part 17 (Lilycove's own lobby + walk-in hall copies, twin NPCs) | 32,522,196 / 1,008 KB | 32,669,940 / 863 KB |
| Part 18 (secret bases: all 8 decoration categories, Brendan's base call) | 32,523,236 / 1,007 KB | 32,670,852 / 862 KB |

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
- **Region map and Fly (part 6):** `src/region_map.c` shows Emerald's Hoenn map whenever the player is in a Hoenn section, so Fly only reaches Hoenn towns from Hoenn and Johto/Kanto towns from there. The Pokédex area page (`src/pokedex_area_screen.c`) only marks areas in the region whose map is shown. HnS's contest lobby and walk-in hall use `MAPSEC_VIRIDIAN_CITY`; Lilycove's copies (part 17) use `MAPSEC_LILYCOVE_CITY`.
- **Wild encounters (part 6, reworked in part 15):** `tools/hoenn/gen_hoenn_wild.py` turns the Emerald tables of kept maps into `data/hoenn/wild_encounters_hoenn.json` (commit it), using `data/hoenn/wild_rules.json`:
  - `bands`: each map (longest name prefix) gets a level band from Lv 35 (Routes 101–104) to 70 (Victory Road). Every table type is stretched onto it (fishing starts 5 lower), and species evolve through `EVO_LEVEL` evolutions the new minimum level reaches (Zigzagoon becomes Linoone, Magikarp becomes Gyarados).
  - `rules`: `day`/`night` ops (`swap` species, or replace `slots`). A map with night ops gets a `_Night` table built from the original Emerald table. Day/night pairs replace version exclusives: Solrock/Lunatone in Meteor Falls, Zangoose/Seviper on Route 114, Mawile/Sableye in Granite Cave and Victory Road. Night also brings Volbeat/Illumise (117), Poochyena/Oddish (101–104, 116), Absol/Kecleon/Murkrow/Hoothoot/Spinarak (Petalburg Woods, 119, 120), ghosts (113, 123, Mt. Pyre's exterior, with Misdreavus) and Chinchou on the super rod (124–134).
  - `tools/wild_encounters/wild_encounters_to_header.py` appends those `gHoenn_*_hns` tables for HnS and guards the Emerald tables of the same maps with `#ifdef EMERALD`.
  - `items`: the same generator upgrades early-game item balls and hidden items on kept maps, in their map.json (Potion → Hyper Potion, Poké/Great Ball → Ultra Ball, status heals → Full Heal, Repels → Max Repel, Ether → Max Ether). All 256 Hoenn item flags are unique Hoenn flags (checked in part 15).
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
  - Mt. Silver: `ReceptionGate_hns` OnTransition hides the Silver guard and sets `VAR_ROUTE28_SCIENTIST` = 1 once `FLAG_HOENN_BEAT_BM` is set (Wallace's badge until part 16a). Oak's later dialogue reflects it.
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
- **Trainer curation (part 14):** `data/hoenn/trainer_curation.json` gives every Hoenn trainer a role (defaults by class, overrides by name, `_Gym` maps always `keep`). Run `tools/hoenn/gen_hoenn_trainers.py` **before** `gen_hoenn_ids.py`.
  - Roles: `keep` (gyms, E4, Winstrates, Wally, Steven, special scripts), `battle` (clueless, Emerald team), `hopeful` (stamp curve − 14), `strong` (curve − 6), `fake:follower|autograph|cheer|foresee|song`, `npc`, `drop` (hidden story trainers, S.S. Tidal). 211 kept an ID (653–863); part 16a brought back 9 (team leaders and admins, Brendan, May), so 220.
  - The generator writes `data/scripts/hoenn_trainers.inc`, swaps object scripts in map.json (NPCs also get `TRAINER_TYPE_NONE`, sight 0), and writes `data/hoenn/trainer_roles.json` (read by `gen_hoenn_ids.py`) and `src/data/hoenn_scaled_trainers.h` (read by `src/hoenn_scaling.c`). `data/hoenn/trainer_objects.json` records each object's **original** script so re-runs are idempotent; delete it only on a clean tree.
  - `gen_hoenn_ids.py` fully evolves hopeful/strong teams and drops their Emerald movesets; `data/hoenn/trainer_parties.party` replaces teams outright (gyms, leaders, Wally VR, Steven). Gym levels there are placeholders; scaling keeps the gaps.
  - **Fake fights** use the engine's sight dry run: a script that reaches a non-`trainerbattle` effect makes the trainer walk up and run it. Once done (flag `HOENN_FAKE_FLAGS_START + n`, 0x1F00+, above all trainer flags), the talk path starts with `callnative HoennSeek_EndScriptIfSeeing, requests_effects=1`, which ends only the sight dry run (`ctx->breakOnTrainerBattle`). The talk dry run (`Script_HasNoEffect`) must keep going, or talking does nothing.
  - Autograph and song fakes set `VAR_HOENN_NEWS`; `EventScript_TV` calls `HoennSeek_EventScript_TVNews` first, which shows it once.
- **World friction (part 14):** Route 120's tester has no scope until you fetch it from Mr. Stone (`FLAG_HOENN_SCOPE_BROKEN`); the bridge clears on `FLAG_HIDE_ROUTE_120_STEVEN`, not on owning the scope. Rusturf Tunnel starts sealed (state 3, rocks and the couple shown); Emerald's Rock Smash → `TryUpdateRusturfTunnelState` scene runs, giving a Star Piece instead of HM Strength. Wally waits at the Victory Road exit (VR state 3).
- **Gyms and League (part 13b):** scripts in `data/scripts/hoenn_gyms.inc`; flags `FLAG_HOENN_COZMO_GAVE_METEORITE`, `FLAG_HOENN_METEORITE_DELIVERED`, `FLAG_HOENN_WINONA_BACK`, `FLAG_HOENN_WINONA_GYM_HIDDEN`, var `VAR_HOENN_E4_STATE` (`hoenn_custom.h`). The text says BADGE; the flags are still `FLAG_HOENN_STAMP_*`.
  - Prerequisites, each a `call` at the top of the leader's script: Norman needs 4 Hoenn badges; Wattson hands over the Basement Key and only battles once `VAR_NEW_MAUVILLE_STATE` is 2; Tate & Liza need Cozmo's meteorite delivered to the Space Center 1F scientist (Cozmo's and the scientist's scripts are map.json swaps); Winona waits outside the Weather Institute on Route 119 (new object, flag `FLAG_HOENN_WINONA_BACK`) and Fortree Gym's OnTransition hides her gym object until then.
  - Each leader's defeat script calls `HoennSeek_EventScript_GymRareCandies` (3 Rare Candies). Gym TMs are Emerald's (all are in HnS's TM list).
  - **League:** the door guards want 8 Hoenn badges; the lobby's OnTransition resets the run (`HoennSeek_EventScript_ResetHoennE4`). The E4 rooms use `VAR_HOENN_E4_STATE`, not HnS's `VAR_ELITE_4_STATE`. After Wallace: the League badge (`FLAG_HOENN_STAMP_WALLACE`), the Hall of Fame machine, then back to the lobby. **No `GameClear` and no Emerald game-clear flags** (that's HnS's ending). The HoF script waits on `FLDEFF_HALL_OF_FAME_RECORD_FRLG`: HnS's record effect removes that ID, so waiting on the Emerald one hangs.
  - E4 (Lv 76–81) and Wallace (Lv 80–84) have fixed teams in `trainer_parties.party`.
  - **Rematches:** after Wallace, talking to a leader offers a rematch (`HoennSeek_EventScript_Rematch<Leader>`, which clears the trainer flag). `HoennGymAceLevel` returns 85 once `FLAG_HOENN_STAMP_WALLACE` is set, so leaders and gym trainers scale up.
  - `gen_hoenn_ids.py` ignores `FLAG_HOENN_*` / `VAR_HOENN_*` (hand-defined).
- **Teams and rivals (part 16a):** scripts in `data/scripts/hoenn_teams.inc`, flags `FLAG_HOENN_AQUA_QUEST` … `FLAG_HOENN_BM_EGGS` (custom 0x18–0x24). Design: `claude/hns-hoenn-aqua-magma-quests.md`.
  - **Aqua:** Matt (Slateport harbor) clears `FLAG_ITEM_ABANDONED_SHIP_HIDDEN_FLOOR_ROOM_2_SCANNER`, so the Scanner ball appears in the ship's hidden floor rooms. Archie waits in **Aqua Hideout B1F** (30,3): 1F is all water. Handing over the Scanner starts his battle, then Damp Rock + 5 Dive Balls. Shelly (Weather Institute 1F) points to Matt.
  - **Magma:** Tabitha (Magma Hideout 1F) → the station's Torkoal on the Fiery Path past the boulders (9,4; its object flag is `FLAG_HOENN_TORKOAL_FOUND`), a scaled wild battle with `FLAG_NO_WILD_CATCHING` → back to Tabitha (`FLAG_HOENN_MAGMA_REPORT`) → Maxie at Mt. Chimney's summit: battle, Heat Rock + 3 Lava Cookies.
  - Finishing both clears `FLAG_HOENN_HIDE_SUMMIT_LEADERS`: Maxie + Archie at the Mt. Pyre summit, a `trainerbattle_two_trainers` double (Drought Torkoal vs Drizzle Pelipper; Archie's half is `TRAINER_SHELLY_SEAFLOOR_CAVERN` renamed in `trainer_parties.party`). Afterwards they mention the Kanto tower (Embedded Tower, part 18+). Every team battle is repeatable: the scripts clear the trainer flag first.
  - **May's call (Norman's until part 16d):** `HoennSeek_EventScript_HallOfFameDone` calls `HoennSeek_EventScript_BMBackCall` once (`FLAG_HOENN_BM_BACK_CALLED`; HnS's `setspeaker` + `pokenavcall` phone window). It shows Brendan & May outside in Littleroot (`FLAG_HOENN_HIDE_BM_OUTSIDE`).
  - **Brendan & May:** a two-trainer double (3 each, Lv 85–87). The first win sets `FLAG_HOENN_BEAT_BM`, gives the Treecko and Torchic eggs (needs 2 free slots; otherwise they offer them again at home) and moves them home (`FLAG_HOENN_HIDE_BM_HOME`), where either one offers a double rematch.
  - **Mt. Silver now opens on `FLAG_HOENN_BEAT_BM`**, not Wallace's badge (`hoenn_ferry.inc`; Oak's and the guard's text say "prove yourself in Hoenn").
  - `gen_hoenn_newgame.py` accepts `FLAG_HOENN_*` in the overrides (the three hide flags are set at new game); `gen_hoenn_ids.py` now scans `data/scripts/hoenn_*.inc` too.
- **Arrival gifts (part 16b):** scripts in `data/scripts/hoenn_arrival.inc`.
  - **Slateport harbor:** Birch's aide stands at (9,11), next to the ferry arrival tile. A harbor `ON_FRAME` entry (`VAR_HOENN_AIDE_STATE` == 0) makes him greet you once with directions; his object flag is `FLAG_HOENN_RECEIVED_MUDKIP`, so he's gone once you have Mudkip.
  - **Birch's lab:** Birch's object script is `HoennSeek_EventScript_Birch`: Mudkip Lv 5 (`FLAG_HOENN_RECEIVED_MUDKIP`), then lines that follow Brendan & May's state. `VAR_DEX_UPGRADE_JOHTO_STARTER_STATE` is now 6, so the table layout stays but the Johto starter balls never appear. Wally stands at (9,5) until you talk to him (`FLAG_HOENN_HIDE_LAB_WALLY`).
  - **Silph Co. (`SaffronCity_SilphCo_hns`):** Steven's object script is `HoennSeek_EventScript_SilphSteven` (same scene and exit as HnS's): a shiny Beldum egg from `specialvar VAR_RESULT, HoennGiveShinyEgg` (species in `VAR_0x8004`; hatching keeps `MON_DATA_IS_SHINY`). It still sets `FLAG_GOT_HOENN_STARTER`.
  - Oak's ticket text mentions the aide and Birch's gift.
- **PokéGear phone rematches (part 16c):** `gen_hoenn_trainers.py` picks every Emerald rematch trainer (`#else` branch of `gRematchTable` in `src/battle_setup.c`) whose role is battle/hopeful/strong: 36, exactly the 36 normal rematch slots HnS leaves free (`REMATCH_JERRY` … `REMATCH_KIRA_AND_DAN`; HnS reuses the earlier names for Johto trainers). The registered-trainer flags are fixed at `TRAINER_REGISTERED_FLAGS_START + slot` and the next flags follow straight after, so **the enum can't grow**: more Hoenn phone trainers need another flag scheme.
  - Their generated scripts (`hoenn_trainers.inc`) register after the first win (Emerald's register text, POKéNAV → POKéGEAR copies as `HoennSeek_Text_Gear_*`) and run Emerald's rematch texts.
  - Rematch team = the trainer's last Emerald tier (`_5`, Amy & Liv `_6`), fully evolved by `gen_hoenn_ids.py` (IV 28; `trainer_roles.json` → `rematch`), scaled in-game to the gym-ace level with no gap (`sHoennRematchTrainers`, `GYM_ROLE_REMATCH`): 68–78 by badges, 85 after Wallace.
  - Generated: `src/data/hoenn_rematches.h` (included at the end of HnS's `gRematchTable`), `src/data/hoenn_match_call.h` + `_decls.h` (included in `sHnsMatchCallTrainers`, `src/match_call.c`), `data/text/match_call_hoenn.inc` from `data/hoenn/phone_texts.json` (2 general lines + a battle request per trainer; boxes are word-wrapped at 26 columns and two-speaker lines split per speaker).
  - Calls come from HnS's engine: the 255-step route counter (same map) or the timed random call. Both need `FLAG_HAS_MATCH_CALL` (0x1F3), which `mkbase.sh` doesn't set: write bit 3 of SaveBlock1 flags byte 0x3E to test.
  - Decided: gym leaders and the E4 never call (they rematch when you talk to them). Only Wally does (part 16d). The other 13 special slots stay free for later.
- **PokéGear calls (part 16d):** `src/hoenn_phone.c`, scripts and all text in `data/scripts/hoenn_phone.inc`, call IDs in `include/constants/hoenn_phone.h`, flags 0x27–0x2F in `hoenn_custom.h`.
  - **Brendan & May** are Hoenn & Seek's friends, not Emerald's rivals. Birch gives both numbers with Mudkip (`FLAG_HOENN_BM_PHONE`); they're in Kanto training to battle Red until you beat Wallace. Their contacts are HnS's `MC_HEADER_BRENDAN`/`MAY`, turned into `MC_TYPE_NPC` entries in the HnS branch of `src/pokenav_match_call_data.c`. When you call them you get the highest line whose flag is set (badge-call flags, Wallace, beating them, the Maxie + Archie double, Red).
  - **Event calls** ring once each when due: `HoennTryEventCall()` runs from the overworld step hook (`src/field_control_avatar.c`, every 16 steps, outdoors or in caves) and starts `HoennSeek_EventScript_PhoneEvent` with the call ID in `VAR_0x8004`. Calls: May at the 1st badge, Brendan at the 4th, May at the 8th (only the highest reached rings; lower ones are marked done), Elm after Brendan & May, Brendan after the Maxie + Archie double, May after Red (`HasTrainerBeenFought(TRAINER_RED_HNS)`). The call flags double as stages for the contact lines.
  - **Elm's call** clears the hide flags of the two Johto starter balls you didn't pick (`VAR_STARTER_MON` 0/1/2 = Chikorita/Cyndaquil/Totodile) and sets `FLAG_HOENN_JOHTO_STARTERS_READY`. The three balls in `NewBarkTown_Lab_hns` run `HoennSeek_EventScript_LabBall*` (map.json swap), which fall back to HnS's own scripts until then. Lv 5, like Mudkip.
  - **Wally** registers after his Victory Road battle (`HoennSeek_EventScript_VRWally`, kept through `gen_hoenn_trainers.py` by the curation file's `script_swaps`). He's the only special trainer in the random-call pool (`HoennIsCallableSpecialSlot`, hooked into `GetNumRegisteredTrainers`/`GetActiveMatchCallTrainerId` in `src/match_call.c`); `HoennPhoneCallText` picks his lines and arms his rematch on half the calls once he's beaten. Rematch team `TRAINER_WALLY_VR_5` (fixed Lv 83–87, with Gallade, not scaled) in `REMATCH_WALLY_VR`.
  - **Every phone line says how the caller knows** (Norman hears every gym result through the League; Birch is Norman's neighbor; Oak calls both dads; Maxie works with Birch; Brendan & May see Kanto firsthand). Keep that up, and when a later part adds content, add a stage line or an event call for it here (see Conventions).
  - **In person, the same relationships come up:** Norman's gym gate (he reads every League report; May calls asking about you), May's mom (May calls home for the reports), Brendan's mom (Birch and Norman chat over the fence; Birch measures volcanoes with Maxie), Birch (Norman tells him your gym results; Oak calls him weekly), Maxie's rematch line (Birch was just up there), Oak (talks to Birch weekly; after Red he phoned Birch and Norman, `goto_if_defeated TRAINER_RED_HNS`).
  - Testing: the debug save has no PokéGear in the start menu, so the contact list itself wasn't checked in the emulator. Random calls are rare; to force one, zero `sMatchCallState.minutes` (`sMatchCallState` in the ELF) before every step.
- **Contests and Safari (part 17):**
  - **Contests:** HnS already has a full contest lobby and halls (`LilycoveCity_ContestLobby_hns` / `_ContestHall_hns`, Emerald's art, Berry Blenders, the Pokéblock Case at reception), entered from **Viridian City**. Lilycove gets its own copies, `LilycoveCity_ContestLobby_hoenn` and `LilycoveCity_ContestHall_hoenn` (game_version `hns`, appended to `gMapGroup_SpecialArea_Hns`): same layouts and the HnS lobby's scripts (receptionist flow, blenders, OnFrame artist scene), Lilycove map section, static exits to `LilycoveCity` warp 4.
    - The contest stages (`ContestHall*_hns`) stay shared. The Lilycove lobby's OnTransition sets `FLAG_HOENN_LILYCOVE_CONTEST`, HnS's lobby OnTransition clears it, and `ContestHall_EventScript_SetExitWarp_hns` jumps to `HoennSeek_EventScript_ContestSetExitWarp` when it's set, so you come back to the lobby you entered from.
    - **The ambient NPCs are the Viridian NPCs' twins** (same sprites, a few nudged spots, new lines in the two `_hoenn` maps' `scripts.inc`). The receptionist explains her twin and the shared ledger once (`FLAG_HOENN_MET_CONTEST_TWIN`), then runs HnS's receptionist script. Emerald's own lobby/hall maps stay excluded. Contest paintings already go to the Lilycove Museum (part 4 note).
  - **Safari Zone:** Route 121's entrance runs on HnS's Safari engine (`EnterSafariMode` gives 30 Safari Balls in the bag). It sets `FLAG_HOENN_IN_SAFARI_ZONE`; the shared exits in `data/scripts/safari_zone.inc` (retire, time up, out of balls, mid-battle) check it first and send you back to Route 121 (`data/scripts/hoenn_safari.inc`), before HnS's Kanto/Johto checks. Safari levels are part 15's band (48–55).
  - **Phone:** May's event call after your first contest win (`GAME_STAT_WON_CONTEST` > 0; she watches the broadcasts), May's 4th-badge contact line points to the contest hall, Brendan's 8th-badge line to Birch's fieldwork at the Safari Zone, and May's mom mentions the contest shows.
- **Secret bases (part 18):** Emerald's secret base code, the 75 Hoenn spots, the 25 base interiors, Fortree's decoration shop, Lilycove Dept. Store 5F and the Route 111 Secret Power man (TM43; HnS also has the TM at Lake of Rage) were already in the build and work as they are.
  - **The fix was the decoration categories.** HnS cut `enum DecorationCategory` to dolls only (`DECORCAT_DOLL` = 0, the same value as `DECORCAT_DESK`), so bought furniture landed in the doll list. `include/decoration.h`, `src/decoration.c` and `src/decoration_inventory.c` now use Emerald's 8 categories for every build. The player's room (HnS's New Bark bedroom too) still only takes dolls and cushions: Emerald greys the other categories out there.
  - Phone: Brendan's event call `HOENN_CALL_BASE` once you own a base (`secretBases[0].secretBaseId`; one of Birch's aides saw you), and Brendan's mom adds a line (`special CheckPlayerHasSecretBase`). Both mention Brendan & May's old base on Route 111.
  - Custom flags 0x35–0x3F (11) are all that's left in `hoenn_custom.h`'s reserved tail; the next part that needs many flags should widen it.
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
  - Hoenn trainers get IDs from `HOENN_TRAINERS_START` (653) up: 257 since part 16d (220 + 36 rematch teams + Wally's), 653–909.
  - Their "defeated" flags come from `TRAINER_FLAG_ID(id)` (used in `battle_setup.c`, `debug.c`), not `TRAINER_FLAGS_START + id`.
  - `MAX_TRAINERS_COUNT_HNS` is set by the generator (912 since part 16c; it moves `TRAINER_PARTNER()` IDs and grows `sTrainerSlides`).
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
  - Lilycove's contest door got a real destination in part 17 (Lilycove's copy of HnS's lobby).
- **9 specials used by Hoenn maps have HnS-specific branches inside:**
  - `GameClear` (part 13)
  - ~~`EnterSafariMode` / `ExitSafariMode`~~ work for Hoenn as they are (part 17)
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

## Conventions
- **Touch upstream HnS files as little as possible**, so future HnS fixes merge cleanly. Put new code and data in new `hoenn`-named files (`tools/hoenn/`, `src/hoenn_*.c`, `data/maps/*_hoenn/`, etc.) and keep edits to shared files to small hooks.
- Work on a `part-NN-<slug>` branch off `hoenn` and open a PR into `hoenn`. Don't commit to `master` (it mirrors upstream).
- **Emulator tests:** a libmgba harness (not in the repo yet) plays scripted input, takes screenshots and reads/writes memory. Useful recipes:
  - Debug menu: hold R + Start. Party → Hatch an Egg hatches a party egg on the spot. Scripts are main item 6, then Script N; a test-only ROM can put any script in `Debug_EventScript_Script_7/8` (restore `debug.inc` afterwards). Warp is Utilities → 2nd item; numbers use ↑/↓ for the value and → for the next digit.
  - Flags & Vars → items 14–16 turn off collision, encounters and trainer sight.
  - `tools/hoenn/emu/mkbase.sh ROM OUT.ss` (run from the harness directory) makes a new game with the debug party, all badges, HnS's HM-received/Headbutt/Running Shoes flags, and the debug menu open. The debug party (`src/data/debug_trainers.party`, debug builds only) is Lapras (lead), Machamp, Pidgeot, Blissey, Miltank and Wobbuffet; between them they know every move with an overworld use: the 9 HMs, Headbutt, Secret Power, Dig, Teleport, Sweet Scent, Milk Drink and Soft-Boiled.
  - Memory (2.0.6 debug build): SaveBlock1 flags at `gSaveBlock1Ptr + 0x198C`; SaveBlock2 battle style is bit 1 of byte `+21`; Hoenn vars at `gSaveBlock3Ptr + 0x132`; enemy battler HP at `gBattleMons + 136 + 42`.
- **Phone dialogue is part of every content part.** When a part adds a quest, area or battle, add a line for it to Brendan's/May's contact lists (`src/pokenav_match_call_data.c`) or an event call (`src/hoenn_phone.c`), and make the line say who told them. Done for contests (17) and secret bases (18); planned: the Kanto tower (2.0).
- **Keep the playtest list current.** Anything a part couldn't test in the emulator goes into `claude/hns-hoenn-playtest-checklist.md` (claude.ai Project), so part 20 can play it through.
- Never commit ROMs, base ROMs or patches. `baserom/` and `dist/` are git-ignored.
- The project owner tests in mGBA. Every part should end with a building ROM and a patch.
