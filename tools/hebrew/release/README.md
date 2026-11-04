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
| `HNS_SAVES` | tests | none. The save ladder `ladder1_newgame.sav` ... `ladder6_postgame.sav` (`emu/README.md`). |
| `HNS_RUNNER` | tests | `tools/hebrew/emu/hnsrun` (build it as described in `emu/README.md`) |
| `HNS_UNITS` | tests (sweep labels) | `$HNS_WORK/units` |
| `HNS_EN_ROM` | tests (ROM sweep) | `../pokehns-en/pokehns.gba`, with its `.elf` next to it |
| `HNS_CROSSCORE` | tests | `$HNS_WORK/crosscore` |
| `HNS_CORES` | tests | `$HNS_WORK/cores` |
| `HNS_MGBA_CORE` | tests | `~/Library/Application Support/RetroArch/cores/mgba_libretro.dylib` |
| `HNS_EN_MAPWALK` | TESTING.md | `$HNS_WORK/mapwalk_en/mapwalk.json` |
| `HNS_WORK` | all | `build/hebrew`, which git ignores |

The scripts have only been run on macOS. The cross-core step loads `.dylib` cores.

## One-time setup

1. **The English tree.** Check out `Release-v2.0.6` as `../pokehns-en` and run `make hns` in it.
   This gives `HNS_EN_ROM` and its ELF.
2. **The runner.** Build `hnsrun` as described in `../emu/README.md`.
3. **The save ladder.** Build it as described in `../emu/README.md` (`scripts/make_ladder.sh`), then
   set `HNS_SAVES` to its folder.
4. **The sweep's labels.** Run `python3 tools/hebrew/make_chunks.py all`, which writes
   `build/hebrew/units`. This command gives the same 7,209 labels that release 0.2 was swept
   with.
5. **Cross-core.** Build the frontend with `cc -O2 tools/hebrew/emu/crosscore.c -o build/hebrew/crosscore`.
   Put `vbam`, `vba_next`, `gpsp`, `mednafen_gba` and `skyemu` `_libretro.dylib` in
   `build/hebrew/cores`. The mGBA core is RetroArch's own. The source of the cores that release
   0.2 used was not recorded.
6. **The English map walk.** Run it once per upstream version. It tells which held maps also hold
   in English:
   `python3 tools/hebrew/emu/mapwalk.py "$HNS_EN_ROM" "$HNS_SAVES/ladder6_postgame.sav" build/hebrew/mapwalk_en`.
   The exact command behind the 0.2 English run was not recorded. Its output has the same form
   (`mapwalk.json`, 543 maps).

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
   `RC/visual_findings.json`. `TESTING.md` gets a visual-review row only when that file exists.
   The row's text comes from `notes.json`.
2. **Edit `notes.json`** for the new release (see the table below). The static-check result comes
   from the CI run of the release commit (`.github/workflows/hebrew.yml`: drift, layout audit,
   `namecheck.py`), because these scripts do not run those checks.
3. **Write the report** with
   `HNS_EN_MAPWALK=... python3 tools/hebrew/release/make_testing_md.py "$RC" pokehns-he-2.0.6-X.Y.gba "$RC/TESTING.md"`.
4. **Publish in the private builds repository.** Copy `RC/pokehns.gba` under the release name.
   Add its line to `SHA1SUMS`. Rename the previous `TESTING.md` to `TESTING-<previous>.md` and add
   the new one. Add the row to its `README.md`. Commit only there. Never commit a ROM to the fork.

The 0.2 `make_check.log` ends in `make: *** [check] Segmentation fault: 11`, and
`check_tests.py` still read 5,074 results from it. What counts is the comparison with
`../data/known_test_failures.txt`, not the exit status of `make`. On a runner with little
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
