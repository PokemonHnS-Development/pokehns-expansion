# Release pipeline

These scripts build a release candidate from one commit, run every harness test on the exact
files that ship, and write the `TESTING.md` that goes next to the ROM. A ROM is the copyrighted
game, so a ROM never goes into this repository. The ROM, `SHA1SUMS` and `TESTING.md` are committed
to the private builds repository (`ronyeh2/pokehns-hebrew-builds`).

| File | What it does |
| --- | --- |
| `build_release.sh` | Builds `make hns` and `make hns RTL_CLIP_REPORT=1` in a clean worktree of the commit. Copies the ROMs, ELFs and map into the candidate folder, checks the header with `gbafix`, and writes `build_info.json` (commit, size, SHA-1, CRC32). |
| `run_release_tests.sh` | Runs the screen tours, clip-report tours, dialogue sweep, self-check, save ladder, map walk, cross-core frames and ROM sweep on the worktree copies of those files. Output goes to `RCDIR/tests`. |
| `make_testing_md.py` | Writes `TESTING.md` from the candidate folder and `notes.json`. |
| `notes.json` | The text that belongs to one release: known issues, the visual review, static checks, what was not tested. |
| `ccdiff.py` | Compares cross-core frame dumps after reducing every pixel to RGB555, the GBA's own 15-bit colour. |
| `crosscore_menus.txt` | The input that `crosscore` plays on every core. |

Each script prints its usage with `--help`. The two shell scripts also take `--check`, which
checks every input, prints the values it resolved, and stops before changing anything. A missing
input stops each script before it runs anything, with exit status 2 and a message that names the
input.

## Environment

The defaults are relative to this repository. The `HNS_*` values that `tools/hebrew/paths.py`
knows are resolved by it (`python3 tools/hebrew/paths.py` prints them). An empty variable counts
as unset.

| Variable | Used by | Default |
| --- | --- | --- |
| `HNS_RELEASE_WORKTREE` | build, tests | `../pokehns-release` next to the repository. `build_release.sh` removes and re-creates it. |
| `HNS_JOBS` | build | `12` |
| `DEVKITPRO`, `DEVKITARM` | build, tests | `/opt/devkitpro`, `$DEVKITPRO/devkitARM` |
| `CPATH`, `LIBRARY_PATH` | build (libpng for the host tools) | `/opt/homebrew/include`, `/opt/homebrew/lib` |
| `HNS_EMU` | tests | `tools/hebrew/emu` |
| `HNS_SAVES` | tests | none. The saves a tour starts from (`start saves/NAME` is read as `$HNS_SAVES/NAME`): the save ladder `ladder1_newgame.sav` ... `ladder6_postgame.sav` and the tour base saves `menuA_base.sav`, `pif2_base.sav`, `r1field_menuA_base.sav` and others, at the top of the builds repository's `saves/`; the `selfcheck` save; the sweep's default save. |
| `HNS_RUNNER` | tests | `tools/hebrew/emu/hnsrun` (build it as described in `emu/README.md`) |
| `HNS_UNITS` | tests (sweep labels) | `$HNS_WORK/units`, with a folder for every batch of `data/inventory.json` (`make_chunks.py all`) |
| `HNS_EN_ROM` | tests (ROM sweep) | `../pokehns-en/pokehns.gba`, with its `.elf` next to it |
| `HNS_CORES` | tests | `$HNS_WORK/cores` |
| `HNS_MGBA_CORE` | tests | `~/Library/Application Support/RetroArch/cores/mgba_libretro.dylib` |
| `HNS_EN_MAPWALK` | TESTING.md | `$HNS_WORK/mapwalk_en/mapwalk.json` |
| `HNS_WORK` | all | `build/hebrew`, which git ignores |

The scripts have only been run on macOS. The cross-core step loads `.dylib` cores.

## One-time setup

1. **The English tree.** Check out `Release-v2.0.6` as `../pokehns-en` and run `make hns` in it.
   This gives `HNS_EN_ROM` and its ELF.
2. **The runner.** Build `hnsrun` as described in `../emu/README.md`.
3. **The saves.** Point `HNS_SAVES` at the builds repository's `saves/`, which holds the save ladder
   and every save a release tour starts from. To make the ladder again, follow `../emu/README.md`
   (`scripts/make_ladder.sh`).
4. **The sweep's labels.** Run `python3 tools/hebrew/make_chunks.py all`, which writes
   `build/hebrew/units`. This command gives 6,611 labels: the 7,209 that release 0.2 was swept
   with, less the 451 match-call, TV and PokéNews lines behind flags defined as 0 and the 147
   labels that are not assembled into the build (`tools/hebrew/flag_gates.py`). Run it again
   before each candidate, into an empty folder (`rm -rf build/hebrew/units` first): the sweep
   reads whatever units are there, and `make_chunks.py` never removes an old chunk file. rc21's
   sweep read units made before `flag_gates.py` and selected 7,209 labels, 147 of them skipped;
   rc22's read three old chunk files besides the fresh ones, 6,821 labels.
5. **Cross-core.** `run_release_tests.sh` builds the frontend from `tools/hebrew/emu/crosscore.c`
   with `cc -O2` into `RCDIR/tests/bin` on every run, so nothing is installed for it. Put `vbam`,
   `vba_next`, `gpsp`, `mednafen_gba` and `skyemu` `_libretro.dylib` in `build/hebrew/cores`. The
   mGBA core is RetroArch's own. Copies of the five cores, with their SHA-1 and inferred source,
   are in the builds repository's `reference/cores/`; unzip them into `HNS_CORES`.
6. **The English map walk.** Run it once per upstream version. It tells which held maps also hold
   in English:
   `python3 tools/hebrew/emu/mapwalk.py "$HNS_EN_ROM" "$HNS_SAVES/ladder6_postgame.sav" build/hebrew/mapwalk_en`.
   The builds repository keeps one as `reference/mapwalk_en.json`; point `HNS_EN_MAPWALK` at it.
   That file is stale: an older `mapwalk.py`, which answered with A and B in turn, made it, and
   it holds only 34 of the 36 maps the current walker holds in both languages. Replace it with a
   walk made by the command above, and in the same change set `map_walk.hebrew_only_held` in
   `notes.json` to `[]`; `make_testing_md.py` checks that list against the two walks.

## Making a release

```bash
RC=build/hebrew/release/rc1                       # one folder per candidate
tools/hebrew/release/build_release.sh --check he/main "$RC" && tools/hebrew/release/build_release.sh he/main "$RC"

# make check on the same commit; make_testing_md.py reads RCDIR/make_check.log
(cd ../pokehns-release && make check BUILD=hns -j12) > "$RC/make_check.log" 2>&1
python3 tools/hebrew/check_tests.py "$RC/make_check.log" | tee "$RC/check_tests.txt"

tools/hebrew/release/run_release_tests.sh --check "$RC" && tools/hebrew/release/run_release_tests.sh "$RC"
```

Then:

1. **Review the screenshots.** Compare the tour screenshots of `RC/tests` with the English build
   (`../pairsheets.py` makes side-by-side sheets), and record the findings in
   `RC/visual_findings.json`. `REVIEW.md` gives the lenses, the finding format, the refuting step
   and the prompts. `TESTING.md` gets a visual-review row only when that file exists.
   The row's text comes from `notes.json`.
2. **Edit `notes.json`** for the new release (see the table below). The static-check result comes
   from the CI run of the release commit (`.github/workflows/hebrew.yml`: drift, layout audit,
   `namecheck.py --all --warnings`, the generator `--check`s and `flag_gates.py --check`), because
   these scripts do not run those checks.
3. **Write the report** with
   `HNS_EN_MAPWALK=... python3 tools/hebrew/release/make_testing_md.py "$RC" pokehns-he-2.0.6-1.0.gba "$RC/TESTING.md"`.
4. **Publish in the private builds repository.** There is one release, 1.0, replaced in place:
   replace `pokehns-he-2.0.6-1.0.gba` with `RC/pokehns.gba`, and replace its line in `SHA1SUMS`
   (check with `shasum -c SHA1SUMS`) and `TESTING.md`. The commit message names the `he/main`
   commit: `Update 1.0 to the build of he/main <short sha>`. Commit only there. Never commit a ROM
   to the fork. A candidate is published although nobody has played it by hand; `not_tested` says
   so (`translation/hebrew/DECISIONS.md` Q138).

The 0.2 `make_check.log` ends in `make: *** [check] Segmentation fault: 11`, and
`check_tests.py` still read 5,074 results from it. The cause: the hydra runner's summary lists
hold 1,600 rows but were written at the running failure count, so with 15 runners the later ones
wrote past them. The guard (`8d52b4cccf`, branch `he/fix-upstream-hydra`, from `he/upstream-fixes`)
is merged into `he/main` since `08027d9879`; with it, `make check BUILD=hns -j8` printed the whole
summary and no segfault, and so did rc21's `make_check.log`. `make` still exits 2,
because upstream fails its own tests. What counts is the comparison with
`../data/known_test_failures.txt`, not the exit status of `make`. Plain `make check` (without
`BUILD=hns`) builds the Emerald tests and stops at a compile error in `src/braille_puzzles.c`. On a runner with little
memory, use `../check_chunked.py` the way CI does.

## notes.json

| Key | Where it goes |
| --- | --- |
| `release` | must match the ROM name (`...-RELEASE.gba`), so last release's notes are never reused |
| `upstream_version`, `branch`, `toolchain` | the first line, the save-ladder row, the "Built with" row |
| `static_checks` | the Static checks row |
| `visual_review` | the Visual review row (when `RC/visual_findings.json` exists) |
| `crosscore_notes` | the paragraph under the cross-core table |
| `map_walk.held_reason` | why maps hold, in the held-maps paragraph |
| `map_walk.hebrew_only_held`, `map_walk.hebrew_only_reason` | the maps that hold in Hebrew but not in English, and why. The list must equal what the data shows. |
| `known_issues_intro`, `known_issues` | Known issues |
| `not_tested` | Not tested, which is never empty |

`make_testing_md.py` refuses to write a sentence that its inputs contradict, and exits with
status 1 when:

- `gbafix.log` does not end in `gbafix: header already valid`.
- `selfcheck.log` does not end in `all checks passed`.
- A save-ladder log (`tests/ladder_*.log`) does not end in `exit 0`.
- The sweep has a CLIP, CRASH, HANG or ABNORMAL label.
- A map in the map walk ends in a status other than OK or HELD.
- The maps held only in Hebrew differ from `map_walk.hebrew_only_held`.
