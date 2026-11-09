# Handoff: the Hebrew translation of Pokémon Heart & Soul 2.0.6

This file is for whoever continues this project, a person or an AI agent. It covers:

- where everything lives;
- how to set up, build, translate, test, debug and release;
- what is still open.

It links the detailed documents rather than copying them, but it gives enough to work from a
fresh clone.

**Conventions**

- Commands run from the repository root unless a step says otherwise.
- `..` is the folder that holds this repository. The tools expect sibling worktrees there.
- Expected output is shown in `# ...` comments.
- Each fact cites a file and line, a commit, or a command that was run. Anything that was not
  seen working is marked **unverified**.
- Two folders are not in this repository:
  - `<private>` is the private working folder. On the reference machine it is the sibling folder
    `../hns-tools`. It is not a git repository and has no remote.
  - `<builds>` is a clone of the private builds repository, `../pokehns-hebrew-builds` on the
    reference machine.

| Read next | For |
| --- | --- |
| [`docs/hebrew_translation.md`](docs/hebrew_translation.md) | how Hebrew is stored and drawn (RTL renderer, window modes, fonts, budgets) |
| [`tools/hebrew/README.md`](tools/hebrew/README.md) | every tool and the `HNS_*` locations |
| [`tools/hebrew/emu/README.md`](tools/hebrew/emu/README.md) | the headless emulator harness, tours, sweep, map walk, save ladder |
| [`tools/hebrew/release/README.md`](tools/hebrew/release/README.md) | the release scripts; [`REVIEW.md`](tools/hebrew/release/REVIEW.md) there is the screenshot review |
| [`tools/hebrew/testmsgs/README.md`](tools/hebrew/testmsgs/README.md) | the Hebrew battle-test message table |
| [`translation/hebrew/STYLE.md`](translation/hebrew/STYLE.md) | the binding style rules |
| [`translation/hebrew/DECISIONS.md`](translation/hebrew/DECISIONS.md) | 74 recorded decisions, up to Q138, and the names review |
| [`translation/hebrew/transliteration_rules.md`](translation/hebrew/transliteration_rules.md) | how names are transliterated |
| [`translation/hebrew/STATUS.md`](translation/hebrew/STATUS.md) | per-file state (generated) |
| [`translation/hebrew/glossary.csv`](translation/hebrew/glossary.csv) | every name and fixed term |
| [`.github/workflows/hebrew.yml`](.github/workflows/hebrew.yml) | CI |

---

## 0. State at handoff (2026-11-10)

| Item | Value | Check |
| --- | --- | --- |
| `he/main` | `fe509e0043` (on GitHub too), before the merge of round 19's fixes and this documentation pass (`he/wip-r19`) | `git rev-parse --short he/main` |
| Release | One release, 1.0, replaced in place on each update (ROM, `SHA1SUMS`, `TESTING.md`); the builds repo's commit history keeps the older builds. Current 1.0: built from `he/main` `08027d9879` | `<builds>/README.md` |
| 1.0 ROM | `pokehns-he-2.0.6-1.0.gba`: 33554432 bytes, SHA-1 `d1fd03270572d00e06762fe6c27e1408ed2f323e`, CRC32 `A3648409` | `<builds>/SHA1SUMS` |
| Releasing | Build a candidate with `tools/hebrew/release/`, then replace the three files in the builds repo and say in the commit message which `he/main` commit it was built from; keep `tools/hebrew/release/notes.json` at `"release": "1.0"`. A candidate is published with hand play declared as not tested (`DECISIONS.md` Q138) | section 5 |
| CI | the last three runs on `he/main` are green: 41918360015 at `85705e4bc9`, 41929345455 at `08027d9879` and 41933578987 at `fe509e0043` | `gh run list -R ronyeh2/pokehns-expansion-heb --workflow hebrew.yml --branch he/main` |
| Static checks | drift 0 FAIL (708 files); audit 0 errors and 48 warnings; namecheck 0 problems and 0 warnings (60 allowlisted); plurals 0 problems; the Pokédex A–Z, Easy Chat and live-label generators up to date; 137 tool tests OK on Python 3.9.6, 3.11.9 and 3.14.7 (`he/wip-r19`) | section 4.2 |
| Translation status | every live file is translated: 650 files, 525 seen on screen, 125 translated, none blocked | `translation/hebrew/STATUS.md:5` |

**What remains** (details in section 8):

1. **Declared, not doable here:** hand play from a new game to the first badge (it needs a
   person), real hardware (a 32 MiB flash cart with FLASH 128 KB and an RTC), and a read of the
   shipped wording by a native speaker. All three are in `notes.json` `not_tested`, so every
   `TESTING.md` says so; section 8.5 lists the lines reviewers flagged for a native read.
2. **Integrate round 19:**
   - merge `he/wip-r19` into `he/main` with `--no-ff`;
   - cherry-pick the Pokéblock graph commit `946ae2f132` onto `he/renderer`, and push
     `he/renderer` before `he/main` (section 8.1);
   - fast-forward `he/upstream-fixes` to `8d52b4cccf`, the hydra summary guard. `he/main` already
     has it, merged in `08027d9879` (section 4.3).
3. **Replace 1.0 with a new candidate.** The graph fix changes the ROM. A build of `he/wip-r19`
   `59d5bc76ce` with devkitARM r68 gives `pokehns.gba` SHA-1
   `243df47e01332faed3262167d69464f554da194f` (CRC32 `94674527`) and `pokehns-clip.gba`
   `d08b8262a656634980d351d09db243ccb247d74e` (CRC32 `61FBC99A`). Only graphics data changed:
   the compressed graph is 20 bytes larger, so the data from `gUsePokeblockGraph_Pal` up to
   `0x09103C88` moves by 16 to 24 bytes (alignment); code, the later data and every RAM symbol
   stay where they were (rc21's `.map` against the new one).
   - Run `make_chunks.py all` before the candidate's sweep (section 5).
   - Add rc21's row and the new candidate's row to `<builds>/records/README.md`. rc21's records
     are in `records/rc21/`, but the index stops at rc20.
4. The open rows of section 8.1: two small tool rows, and the Pokéblock case list's
   three-digit level, which play most likely never makes (by code reading and a frame model).

---

## 1. What this is and where everything lives

This is a Hebrew translation of **Pokémon Heart & Soul 2.0.6**, a GBA ROM hack built on
pokeemerald-expansion 1.15.2. Upstream is `PokemonHnS-Development/pokehns-expansion`; its tag
`Release-v2.0.6` is `167aa6d537b109bb229c231ddce4616974c4da71`. The work has four parts:

- **Engine:** a right-to-left text renderer, window RTL modes and fonts with Hebrew letters,
  behind `TEXT_RTL` (`include/config/text.h:20`).
- **Text:** the translated text.
- **Graphics:** labels redrawn in the art.
- **Tools:** the tools and the emulator harness that check all of it.

### 1.1 Repositories

| Repository | Visibility | Holds | Notes |
| --- | --- | --- | --- |
| `ronyeh2/pokehns-expansion-heb` (this repo) | public | engine, text, graphics, tools, docs | default branch `master`; **no tags** (`git ls-remote` on 2026-11-10) |
| `PokemonHnS-Development/pokehns-expansion` | public | upstream | `Release-v2.0.6` = its `master` = `167aa6d537` |
| `ronyeh2/pokehns-hebrew-builds` | **private** | the one release 1.0 (ROM, `SHA1SUMS`, `TESTING.md`), replaced in place; `saves/`, `reference/` (libretro cores, English map walk), `records/rcNN/` (each candidate's logs and review JSON), `archive/` (history only) | `.gitattributes` has `*.gba`, `*.sav`, `*.zip`, `*.tar.gz` binary; git history keeps the older builds |
| `<private>` (no remote) | local only | the mGBA 0.10.5 build (`mgba/`), `emu/hnsrun`, the candidates' ROMs, ELFs and screenshots (`release/rc1..rc21`, 7.9 GB), the round screenshots (`scratch/`, about 140 GB) | everything the release needs is in the fork or `<builds>` (section 8.4); the rest is rebuilt (section 2.6) |

The Spanish (`SergioBonet/hns_es`) and French (`nhykola/HeartAndSoul-FR`) forks were used only
as a cross-check, never as source text (`STYLE.md` §1).

### 1.2 Branches

| Branch | What | Rule |
| --- | --- | --- |
| `master` | identical to upstream `167aa6d537` | never commit to it |
| `he/main` | the translation; the release branch | feature branches merge into it with `--no-ff` |
| `he/renderer` | the Hebrew engine with the **English** strings. It is the drift baseline (`HNS_BASELINE`) and the chunk source | every engine or graphics commit is cherry-picked onto it; text commits never are |
| `he/upstream-fixes` | upstream bug fixes, kept apart from text and engine work | `he/fix-upstream-hydra` (`8d52b4cccf`, branched from it) is merged into `he/main` (`08027d9879`); fast-forward `he/upstream-fixes` to it |
| `he/fonts`, `he/graphics`, `he/naming-keyboard`, `he/preview` | feature branches, already merged | kept for history |
| `he/fix-*` | one fix topic each (for example `he/fix-k5-cosmetics`, `he/fix-vr-dex`), already merged | merge title `Merge he/<branch>: <what it brings>` |

On GitHub (2026-11-10): `master` `167aa6d537`, `he/main` `fe509e0043`, `he/renderer` `384104fb15`,
`he/upstream-fixes` `f96cb7a4f9`, `he/fix-upstream-hydra` `8d52b4cccf`, and 40 other `he/*`
branches.

The branch `he/fix-screens` is merged into `he/main`. Nine local-only branches
(`he/wip-screens-r6` to `-r9`, `-r11`, `-r13`, `-r14`, `-r14b` and `-r17`) and the pushed
`he/fix-screens-r3` and `-r4` have commits that `git cherry` does not find in `he/main`, but their
content is there. A file-by-file check of each branch's net change against `he/main` found every
file identical or with every added line present; the few lines that differ were changed later
in `he/main` on purpose: r6's TUSCANY, FRIEDA and SANTOS came in through `cfff10fcef` and were put
in Hebrew by `e2bd13c8db` and `a58ce649ac`, r17's glossary notes gained "; decided Q133", and r3's
tool scripts were reworked (relative includes, `Emu.rowkeys` in `27cb8ce38f`). The pushed r3 and r4
tips equal the fork's. They are history only.

### 1.3 Worktrees the tools expect

| Folder | Content | Used by |
| --- | --- | --- |
| `.` | `he/main` (or your feature branch) | everything |
| `../pokehns-heb-engine` | `he/renderer` | `drift.py`, `make_chunks.py`, `units.py --tree` (`HNS_BASELINE`) |
| `../pokehns-en` | detached at `Release-v2.0.6`, with `make hns` built | `audit.py --baseline`, `rom_sweep.py`, the save ladder (`HNS_UPSTREAM`, `HNS_EN_ROM`) |
| `../pokehns-release` | detached at the release commit | `tools/hebrew/release/*.sh` (`HNS_RELEASE_WORKTREE`); the build script removes and re-creates it |
| `../pokefirered-heb` | the FireRed Hebrew translation, optional | `namecheck.py --fr-sync` (`HNS_FIRERED`); without it the check prints `FRSYNC skipped` |

`python3 tools/hebrew/paths.py` prints every location the tools resolved.

### 1.4 What must never be published

- **ROMs, ELFs and maps** (`*.gba`, `*.elf`, `*.map`) and **saves** (`*.sa*`). A built ROM is
  the copyrighted game, and a DMCA notice can take the public fork down with it. They are
  git-ignored (`.gitignore:4-5, 26, 29`), and `build/` is ignored too (`.gitignore:31`). A ROM
  goes only to the private builds repository, as the one release 1.0, replaced in place. The CI workflow never uploads
  a ROM (`hebrew.yml:3-4`).
- **Screenshots of a whole run.** `tools/hebrew/emu/README.md` says not to commit them. Put run
  output under `build/hebrew/` (`HNS_WORK`).
- **Credentials.** Never write a token into a file, a remote URL or a commit. See section 7.3.
- **Personal names and AI attribution.** Keep both out of commits, docs and release notes.
- **The private folder's contents** (section 1.1). They contain absolute paths of one machine.

---

## 2. Setup and build

### 2.1 Prerequisites

Reference machine: Apple Silicon, macOS.

| Need | Version used | Install |
| --- | --- | --- |
| devkitARM (arm-none-eabi gcc, binutils, newlib) | devkitARM r68: gcc 16.1.0, binutils 2.46, newlib 4.6 | macOS: the devkitPro pacman installer, then `sudo dkp-pacman -Sy && sudo dkp-pacman -S gba-dev devkitarm-rules` (`docs/install/mac/MAC_OS.md:64-74`) |
| host C compiler | Apple clang (Xcode Command Line Tools) | `xcode-select --install`; Linux: `build-essential` |
| libpng, pkg-config | Homebrew libpng 1.6.58 | `brew install libpng pkg-config`; Linux: `libpng-dev` |
| GNU make | macOS ships 3.81 | 3.81 builds fine but has no `-O` (section 6.1) |
| git | any | the build refuses to run without git history (section 6.1) |
| Python 3 | 3.9 or newer: the 137 tool tests pass on 3.9.6, 3.11.9 and 3.14.7, and all 242 scripts under `tools/hebrew` compile with every warning turned into an error on 3.9.6 and 3.14.7 (CI: Ubuntu 26.04's python3) | standard library only, except the picture tools |
| Pillow | 12.2.0 | `python3 -m pip install Pillow`. Needed by `fontcells.py`, `tools/hebrew/graphics/`, the font previews and the review-sheet scripts; the harness writes PNGs itself |
| numpy | any recent | only `tools/hebrew/inventory/` |
| cmake | 4.4.3 | only for building mGBA for the harness |

**Linux (what CI installs, `hebrew.yml:24-27`):**

```bash
sudo apt-get install -y --no-install-recommends binutils-arm-none-eabi gcc-arm-none-eabi \
     libnewlib-arm-none-eabi libpng-dev python3
```

On ubuntu-26.04 (CI pins it) this gives gcc-arm-none-eabi 14.2 (`15:14.2.rel1-1`, run
41918360015). It builds and tests fine, but it is **not the release toolchain**: its ROM differs
from the release ROM (ubuntu-24.04's 13.2 gave, for example, EWRAM 248320 B against 248324 B with
devkitARM). Releases are always built locally with devkitARM.

Not tried: a Linux host build with devkitPro pacman. On Python 3.14 the only tracked file that
gives a `SyntaxWarning` is upstream's `migration_scripts/1.8/item_ball_refactor.py:29` (`\w` in a
plain string), unchanged from `Release-v2.0.6` and not used by the build.

### 2.2 Environment (macOS)

Set this for every build:

```bash
export DEVKITPRO=/opt/devkitpro DEVKITARM=/opt/devkitpro/devkitARM \
       CPATH=/opt/homebrew/include LIBRARY_PATH=/opt/homebrew/lib
```

`CPATH` and `LIBRARY_PATH` are needed because devkitPro's `pkg-config` (`/opt/devkitpro/tools/bin`)
comes first in `PATH` and does not know Homebrew's libpng. The Makefile puts `$DEVKITARM/bin` first in `PATH`
(`Makefile:84-95`). Without `DEVKITARM` it uses whatever `arm-none-eabi-*` is on `PATH`, which is
how CI builds.

### 2.3 Clone, remotes, worktrees

```bash
git clone https://github.com/ronyeh2/pokehns-expansion-heb.git
cd pokehns-expansion-heb
git remote add upstream https://github.com/PokemonHnS-Development/pokehns-expansion.git
git fetch upstream --tags                 # the fork has no tags; Release-v2.0.6 comes from upstream
git switch he/main
git worktree add ../pokehns-heb-engine he/renderer
git worktree add --detach ../pokehns-en Release-v2.0.6
python3 tools/hebrew/paths.py             # prints HNS_BASELINE, HNS_UPSTREAM, ...
```

This sequence was followed end to end on a fresh clone on the reference machine ("Notes from the
fresh-clone test" at the end); a fresh machine was never tried (**unverified**).

`.git` is about 677 MB on the reference machine, including three extra remotes.

**How the reference clone differs**

- `origin` is **upstream** (PokemonHnS-Development), not the fork. The extra remotes are `es`,
  `fr` and `sigon`.
- There is no remote for the fork, so never `git push origin` there.
- Pushes to the fork go to an explicit URL (section 7.3).
- `gh` needs `-R ronyeh2/pokehns-expansion-heb`.

### 2.4 Build targets

| Command | Output | Object dir | Notes |
| --- | --- | --- | --- |
| `make hns -j12` | `pokehns.gba`, `.elf`, `.map` | `build/hns` | the release ROM. `hns` is detected only when `$(BUILD)` or the **whole** goal list is exactly `hns` (`Makefile:21`). Not a `RELEASE=1` build, so asserts stay live (`RELEASE ?= 0` at `Makefile:69`; `-DRELEASE` only at `Makefile:188-189`; section 8.2) |
| `make hns RTL_CLIP_REPORT=1 -j12` | `pokehns-clip.gba`, `.elf`, `.map` | `build/hns-clip` | diagnostic ROM that logs every glyph drawn outside its window (`Makefile:36-41, 176-177`; `src/text.c:1047`). **Never shipped.** Builds next to the release build without a clean |
| `make hns RTL_STRING_REPORT=1 -j12` | `pokehns-strrep.gba`, `.elf`, `.map` | `build/hns-strrep` | diagnostic ROM that records every ROM string copied or printed, read by `tools/hebrew/strcov.py` (`Makefile:42-47, 185-187, 632-643`; hooks in `src/string_util.c`). **Never shipped.** Every hook is under `#if RTL_STRING_REPORT` and followed by `#line`, so the release ROM is byte-identical with or without them |
| `make check BUILD=hns -j12` | `pokehns-test.elf`, `pokehns-test-headless.elf`, results on stdout | `build/hns-test` | the upstream test suite. Judge the result with `check_tests.py` (section 4.3). Plain `make check` builds the Emerald tests and stops at a compile error in `src/braille_puzzles.c:379` |
| `make BUILD=hns -j2 pokehns-test.elf` | test ELF only | `build/hns-test` | what CI builds (`hebrew.yml:93`) |
| `make clean` / `make tidy` | | | `tidy` keeps the tools and the graphics |

> **Never type `make hns check` or `make hns <file>`.** The goal list is then not exactly `hns`,
> so the build becomes Emerald and rewrites `.map_version` to `emerald` (`map_data_rules.mk:45-46`).
> Use `make check BUILD=hns` or `make BUILD=hns <target>`. If it happened, the next `make hns`
> regenerates the map data (`cat .map_version` should print `hns`).

**Config switches, not make flags:**

- `TEXT_RTL` is `#define TEXT_RTL TRUE` (`include/config/text.h:20`). There is no
  `make TEXT_RTL=0`.
- `RTL_CLIP_REPORT` defaults to FALSE (`text.h:22-24`); the Makefile passes it with
  `-DRTL_CLIP_REPORT=TRUE`.
- `RTL_STRING_REPORT` defaults to FALSE (`text.h:25-29`); the Makefile passes it with
  `-DRTL_STRING_REPORT=TRUE`.
- `TEXT_NAME_SUFFIX_IN_BATTLE` (`text.h:31-33`).

**Expected noise, not errors:**

- `bKGD: invalid index` from libpng, 253 times.
- `-Woverride-init`, 122 times (demoted for H&S, `Makefile:207-209`).
- Some `-Wunused-*` warnings (demoted unless `UNUSED_ERROR=1`).
- `LOAD segment with RWX permissions`.

**Memory at 0.2 (devkitARM)**

| Build | EWRAM | IWRAM | ROM |
| --- | --- | --- | --- |
| release | 248324 B (94.73%) | 25700 B (78.43%) | 31471828 B of 32 MiB (93.79%) |
| clip | 248520 B (94.80%) | same | 31471988 B |

`gbafix -p` pads the image to 33554432 bytes.

**Timings**

| Where | Build | Time |
| --- | --- | --- |
| reference Mac, `-j12` | fresh clone, `make hns` including host tools and every graphic | 1107 s, an upper bound (another build ran at the same time) |
| reference Mac | clip build right after | 149 s |
| CI, 4 vCPU | `make hns` | 159 s |
| CI | clip build | 53 s |
| CI | test ELF at `-j2` | 315 s |
| CI | chunked suite | 433 s |

### 2.5 The English baseline

```bash
(cd ../pokehns-en && make hns -j12)     # gives HNS_EN_ROM = ../pokehns-en/pokehns.gba + .elf
```

- The English build is needed by `audit.py --baseline` (source only), `rom_sweep.py`, the save
  ladder and one tool test.
- To run `make check` in the English tree you need the include-order fix from `49adf9cc99` /
  `70df00d417`: in `test/test_runner.c`, `#include "global.h"` goes before `fake_rtc.h`. On the
  reference machine it is a staged, uncommitted change in `../pokehns-en`.
- **The official binary.** The release rests on source identity with `167aa6d537` plus drift, not
  on matching the official binary. Three builds of `167aa6d537` with devkitARM r68, each 33554432
  bytes:

  | Command | CRC32 | SHA-1 |
  | --- | --- | --- |
  | `make hns` | `FB9F58C5` | `2fc84dcb426683a1bb0c5245b85538f7ccff8c46`, byte-identical to `../pokehns-en/pokehns.gba` |
  | `make hns RELEASE=1` (LTO on, the default, `config.mk:2`) | `6D616135` | `f55861b4f9843c06a649e4504c3598ab4a44df7e` |
  | `make hns RELEASE=1 USE_LTO_ON_RELEASE=0` | `20CFE51A` | `70590dd11a4794d16da2d5abfbf583c5db8ac424` |

  - None matches the official 2.0.6 UPS output, `01713508`. The likely cause is the compiler.
    Upstream documents its build with Ubuntu's `apt install ... gcc-arm-none-eabi`
    (`docs/install/windows/WSL.md:57`), and section 2.7 already says another compiler gives another
    binary. Upstream CI's `release` job builds Emerald, not H&S (`.github/workflows/build.yml`).
  - Whether the official build is a `RELEASE=1` build is **unverified**, but the evidence leans to
    a plain `make hns`. `INSTALL.md:65` and `:94` say `make hns`. And 2.0.1 changed
    `include/config/debug.h` from `DISABLED_ON_RELEASE` to `FALSE` (`b2366daa11`), a change that
    only matters in a build without `RELEASE`.
  - **The decisive test** needs the official UPS and an Emerald base ROM, neither of them on the
    reference machine. The plain build holds the assert strings `out of memory trying to allocate`
    and `src/malloc.c` (ROM offsets `042A0BF`, `042A0A4`); both release builds have neither.
  - What a `RELEASE=1` build changes, and why 1.0 stays a plain build, is in section 8.2.
  - `make release BUILD=hns` sets the same variables as `RELEASE=1` (`Makefile:21`, `:80-81`).
    `make hns release` builds **Emerald**, because the goal list is not exactly `hns`.

### 2.6 Harness and the pieces that are not in the fork

| Piece | How to get it from the fork | Where it is kept |
| --- | --- | --- |
| `hnsrun` (headless libmgba runner) | build mGBA 0.10.5 in a **permanent** folder, then the runner (`tools/hebrew/emu/README.md:21-45`); set `HNS_RUNNER` if you keep it outside `tools/hebrew/emu/` | rebuilt; on the reference machine `<private>/emu/hnsrun`, rpath to `<private>/mgba/build` |
| save ladder `ladder1_newgame.sav` … `ladder6_postgame.sav` and the tour base saves | the ladder on the **English** ROM: `hns.py --rom "$HNS_EN_ROM" run $E/scripts/ladder1_newgame.txt OUT --save OUT/none.sav --save-out "$HNS_SAVES/ladder1_newgame.sav"`, then `$E/scripts/make_ladder.sh` (`emu/README.md`); no script in the fork makes `pif2_base` or `r1field_menuA_base` | `<builds>/saves` (`HNS_SAVES`): at the top the ladder and every save a release tour starts from (`menuA_base`, `pif2_base`, `r1field_menuA_base` and others); the round tours' saves in subfolders (section 4.5). Each is 131088 B = 128 KiB flash + 16-byte RTC footer |
| unit chunks (the sweep's labels) | `python3 tools/hebrew/make_chunks.py all` → `build/hebrew/units`, 6,611 labels (the 7,209 that 0.2 was swept with, less the 451 flag-gated and 147 unbuilt labels that `flag_gates.py` takes out). Make them again whenever `live_labels.json` changes: the sweep reads whatever units are there | rebuilt; never stored |
| `crosscore` (libretro frontend) | nothing to install: `run_release_tests.sh` builds `tools/hebrew/emu/crosscore.c` with `cc -O2` into `RCDIR/tests/bin` on every run | |
| libretro cores | `vbam`, `vba_next`, `gpsp`, `mednafen_gba`, `skyemu` `_libretro.dylib` in `HNS_CORES` (`build/hebrew/cores`); the mGBA core is RetroArch's own (`$HOME/Library/Application Support/RetroArch/cores/mgba_libretro.dylib`) | `<builds>/reference/cores/`: copies of the five, with their SHA-1 and inferred source (the libretro buildbot's macOS arm64 nightlies, files dated 2026-10-17; `SOURCE.md`). RetroArch's mGBA core is not stored |
| English map walk | `python3 tools/hebrew/emu/mapwalk.py "$HNS_EN_ROM" "$HNS_SAVES/ladder6_postgame.sav" build/hebrew/mapwalk_en` | `<builds>/reference/mapwalk_en.json` (`HNS_EN_MAPWALK`) |
| English tour run (for side-by-side review) | `python3 tools/hebrew/emu/hns.py tour "$HNS_EN_ROM" build/hebrew/tour_en`: 70 of the 71 tours report OK in 2:37; the two `naming_*` tours are Hebrew-only by design (section 4.5) | regenerated; not stored |
| graphics drawing scripts | `tools/hebrew/graphics/` (its README; `gpaths.LATER_EDITS` protects the 17 files fixed by hand later) | — |
| Hebrew glyph designs and installer | `tools/hebrew/fonts/` | — |
| inventory builder (`live_labels.json`, `inventory.json`, `c_strings.json`) | `python3 tools/hebrew/inventory/build.py --release <English release ROM> --compare` (`inventory/README.md`) | — |

`<private>/translation` held the translated unit chunks and the pre-fork drafts. Both are archived
in `<builds>/archive` (history only) and must not be used: an old chunk would undo later fixes.
`sweep.py selftest` no longer needs them (it picks a label whose string in the ROM has Hebrew).

The mGBA build that 0.2 used is tag 0.10.5 (`26b7884`), with Qt, SDL, GL, FFmpeg and Lua off.

Smoke test for the runner:

```bash
mkdir -p build/hebrew/hnsrun-check
printf '60 -\nshot boot\nquit\n' | "${HNS_RUNNER:-tools/hebrew/emu/hnsrun}" pokehns.gba build/hebrew/hnsrun-check
# OK: booted 240x160 rtc=1767268800
# shot boot @60
# OK: 60 frames pc=000001F8
```

**The save ladder is reproducible, with one condition: the time zone.**

- `make_ladder.sh` rebuilt rungs 2-6 in 52 s, and the command in `tools/hebrew/emu/README.md`
  rebuilt rung 1. All six are `cmp`-identical to `<builds>/saves`, the 16-byte RTC footer
  included (round 19, reference machine, `TZ` unset, zone Asia/Jerusalem).
- The clock is fixed: `hnsrun` sets it to `HNS_RTC` (default 2026-01-01 12:00 UTC,
  `tools/hebrew/emu/hnsrun.c:189-191`), and mGBA advances it by emulated frames, not by wall time
  (mGBA 0.10.5 `src/core/interface.c:41-42`).
- But mGBA hands it to the game in the host's local time (`localtime_r`,
  `src/gba/cart/gpio.c:288`), and a save's footer carries its clock forward into the next run
  (`src/gba/savedata.c:643-695`).
  - Under `TZ=UTC`, rung 2 built from the stored rung 1 is still byte-identical. Rungs 3-6 also
    start from a stored save with a footer, so by the same mechanism they should not depend on
    the zone either; only rung 2 was measured.
  - A new rung 1 under `TZ=UTC` differs in one footer byte, the hour: 0x12, against the stored
    0x14 (`cmp` byte 131077).
  - Rung 2 built from that rung 1 differs a lot: the encryption key and 1,804 bytes of
    SaveBlock1, among them the party's personality values and IVs.
  - So a new rung 1, and any tour that starts a new game (`start empty`), match the stored
    saves only in a UTC+2 zone on 2026-01-01, for example `TZ=Asia/Jerusalem`.

**Unverified:** building mGBA, `hnsrun` and `crosscore` on Linux, and the ladder there; how the
clock's hour reaches the game's random numbers.

The fork's `tools/hebrew/` copies are canonical. `<private>/emu` and `<private>/tools` hold older
copies with hard-coded paths; do not use them.

### 2.7 Check that your toolchain reproduces the release

```bash
git worktree add --detach ../pokehns-repro 40279b7f5f
cd ../pokehns-repro && make hns -j12 > build.log 2>&1
python3 -c "import hashlib,zlib; b=open('pokehns.gba','rb').read(); print(len(b), hashlib.sha1(b).hexdigest(), '%08X'%(zlib.crc32(b)&0xffffffff))"
# 33554432 07753efc17e5c1a1c23e791b65cc79b14f1df955 A974ED1F
make hns RTL_CLIP_REPORT=1 -j12 > build_clip.log 2>&1 && shasum pokehns-clip.gba
# 4d7cfac5dd4b5694eb3a441b62b8c7fb3d10eec6  pokehns-clip.gba
git status --porcelain                  # empty: the build leaves the tree clean
```

Both SHA-1s were reproduced from a fresh clone of `40279b7f5f` with devkitARM r68.

- A different compiler gives a different SHA-1 (CI's Ubuntu arm-none-eabi-gcc 14.2, any other
  devkitARM). Record the toolchain with every build.
- 0.1 (`6202f6bd3f1d317cc3a24d27d6883ff963b9a203`) was built from `19bb11a3da`.
- **Unverified:** another machine with the same devkitARM r68 was never tried.

---

## 3. The translation workflow

Every live file is already in Hebrew. New work is therefore one of three things:

- a **fix** to an existing line (edit it directly);
- **new English text** from an upstream merge, or a name still in Latin (extract units,
  translate, check, apply);
- a **name** change (glossary first).

### 3.1 Where text lives

| Source | What | How it is changed | Files changed on `he/main` vs `master` |
| --- | --- | --- | --- |
| `data/maps/*/scripts.inc` | dialogue, signs, event text (`.string "..."` under a label) | direct edit, or `units.py` | 488 |
| `data/text/*.inc` | shared texts (PC, nurse, TV, match call, `oak_speech_hns`) | same | 29 |
| `data/scripts/*.inc`, `data/event_scripts.s` | shared scripts | same | 21 + 1 |
| `src/*.c` | UI and battle strings in `_()`, `__()`, `COMPOUND_STRING()`, `ITEM_NAME()` | same | 88 |
| `src/data/**/*.h` | names and descriptions: items, moves, abilities, species, types, radio, Frontier, contests, decorations | `units.py`; `make_chunks.py` pre-fills name fields from the glossary | about 59 |
| `src/data/trainers_hns.party`, `battle_partners.party` | trainer `Name:` lines | `apply_names.py` (glossary `trainer_name` rows) | 2 |
| `src/data/region_map/region_map_sections.json` | map-section names | `apply_names.py` (glossary `mapsec` rows) | 1 |
| `src/data/pokemon/pokedex_orders.h` | Hebrew A–Z dex order (the `#if TEXT_RTL` branch) | `gen_dex_alpha.py` | 1 |
| `graphics/**` | labels drawn into PNGs (and a few `.bin` tilemaps) | edited PNGs, committed as engine or asset commits; the drawing scripts are in `tools/hebrew/graphics/` | 129 |
| `test/hebrew_battle_messages.h`, `test/bag.c`, `test/text.c` | test expectations that depend on the Hebrew | `tools/hebrew/testmsgs/`, or a direct edit | 3 |

**Left in English on purpose:**

- dead labels (`tools/hebrew/data/live_labels.json`, key `dead`) and unreachable Emerald maps
  (`tools/hebrew/data/inventory.json`, `reach_class` `dead`);
- the R+START debug menu (`src/debug.c`, `data/scripts/debug.inc`), except two labels
  (`STYLE.md` §5);
- braille;
- Latin literals that code compares (the Odd Egg names, the mystery-gift sample code).

`status_report.py:22-48` (`KEPT_LATIN`) lists the deliberate Latin per file.

**Find which file prints a line:** search the English in the baseline worktree. The label is the
same in both trees; the line number can differ.

```bash
grep -rn "came back, and you even" ../pokehns-heb-engine/data ../pokehns-heb-engine/src
# ../pokehns-heb-engine/data/maps/AzaleaTown_House1_hns/scripts.inc:115:	.string "The SLOWPOKE came back, and you even\n"
```

`tools/hebrew/data/inventory.json` gives each file's batch (`B01`–`B40`), story stage and
reachability. This one is `B21`, `live`.

### 3.2 The rules a translator applies

The binding sources, in order:

1. [`STYLE.md`](translation/hebrew/STYLE.md);
2. [`glossary.csv`](translation/hebrew/glossary.csv);
3. [`transliteration_rules.md`](translation/hebrew/transliteration_rules.md).

The glossary wins for names, STYLE.md for everything else (`STYLE.md:3-4`). In short:

- **Source and voice:** translate from the English upstream source. Write natural modern Hebrew,
  with no nikud. Keep each character's voice. Never add or drop information.
- **Gender:** every Pokémon is masculine. The player is addressed in the masculine singular;
  prefer neutral phrasing, and never use slash forms. NPCs keep their own gender: check the
  speaker's `OBJ_EVENT_GFX_*` in `map.json` (`units.py` puts it in `context.speaker_gfx`).
- **Names:** every proper noun and fixed term comes from the glossary. **A name that is missing
  stays in English and is reported; never invent a spelling** (STYLE §3). Generic place words
  are translated and proper parts transliterated (`העיירה ניו בארק`).
- **Move names:** bare in dialogue, quoted `”…”` only where the English quotes them or inside a
  description sentence.
- **Characters:** only what `charmap.txt` encodes.
  - Hebrew letters `0x3A`–`0x4F`.
  - Final letters at word end only: ך `0x50`, ם–ץ `0x5E`–`0x61`.
  - Geresh is the ASCII `'` (`0xB4`); gershayim is `”` (`0xB2`); there is **no straight `"`**.
  - `…` is one character (`0xB0`).
  - Digits are written in normal reading order and never reversed.
- **Structure:** keep every `{TOKEN}` and the `$` terminator.
  - `\n` is the next line, `\l` scrolls one line, `\p` is a new page.
  - You may move `\n`/`\l`. Add or remove `\p` only when a page would not fit otherwise.
  - Placeholders keep the English order. Hebrew may drop only `{POKE} {PKMN} {POKEBLOCK} {ID}
    {NO}` and the `{PK}` of the Easy Chat word `{PK}RS`, and `{B_BUFF1..3}` may swap places with
    each other (`drift.py:32-47`; `units.py` and `checkunits.py` import the same rule).
- **Battle grammar:** "wild" and "opposing" are definite suffixes (` הפראי`, ` היריב`), and verbs
  are masculine.
- **Engine-coupled strings** (STYLE §9): the battle prefixes, the Pokédex search letter groups
  and AM/PM have exact values. Do not change them casually.
- **Decided; do not reopen:**
  - gender (STYLE §2);
  - definite battle suffixes (K1);
  - `מס'` for the ID label (K2);
  - פוקיגיר (K3);
  - berries as פרי / פירות (K6);
  - מזל טוב for Congratulations (Q6);
  - צוות זוגי for tag team (Q12, Q17, Q62);
  - the battle debug menu translated and the R+START menu English (Q118, Q120);
  - the link battle lines without the player's gender (Q132);
  - the five Pokédex terms היסואי, הר הנזר, חור תולעת אולטרה, צוות פלזמה, רוז (Q133);
  - 'psychic power' as כוח פסיכי in Pokédex prose (Q134);
  - Easy Chat in Hebrew, with the Hebrew-letter keyboard (Q135);
  - only errors in a name follow FireRed's later changes (Q136).

### 3.3 Width: what the renderer does and how to measure

- Hebrew is typed in logical (reading) order. The engine keeps upstream's logical pen and
  mirrors only the blit (`docs/hebrew_translation.md:26-34`), so a string that fits in English
  fits in Hebrew.
- Latin and digit runs are drawn left to right as one block (`docs/...:36-40`). You write
  `דרך 32` and `500¥` as you read them.
- **Measure in pixels; do not count letters.**
- **A glyph past the left edge of a window is simply not drawn.** It looks like a spelling mistake,
  not like clipping (`src/text.c:1401-1421`). Static tools model this, but only the clip build
  proves it (section 4.5).

The common budgets (`tools/hebrew/data/budgets.json`, 61 kinds):

| Kind | Font | Budget |
| --- | --- | --- |
| overworld dialogue, signs, battle text | normal | 208 px per line, **200 px on a line ending in `\l` or `\p`** (the down arrow sits inside the box: `TextPrinterDrawDownArrow`, placed by `RtlDownArrowX` in `src/text.c`), 2 lines |
| phone call | normal | 192 / 184 px, 2 lines |
| item description | normal | 102 px × 3 |
| summary move description | normal | 152 px × 2 |
| Pokédex entry | normal | 224 px × 3 |
| bag item name / shop item name / battle move name | narrow | 88 / 84 / 64 px |
| healthbox name / party nickname | small | 55 / 40 px |

**Hard byte limits** (`namecheck.py:34-38`, letters without the terminator):

| Field | Bytes |
| --- | --- |
| species | 12 |
| move | 16 |
| ability | 16 |
| item | 19 |
| item plural | 21 |
| type | 8 |
| trainer name | 10 |
| trainer class | 12 |
| berry | 6 |
| map section | 19 |
| category | 12 |
| nature | 12 |
| speaker | 16 |

With devkitARM's GCC 16 an over-long species (13 letters) or item (20) is a compile error
(`excess elements in array initializer`, `-Werror`); a move name has no compile-time limit
(`include/move.h:77` is a pointer), so `namecheck.py` and the audit's `BYTES` are its only guard.

Buffers: an expanded field message must stay under 999 bytes (`gStringVar4`), a battle message
under 424. Placeholders are measured at worst case: `{PLAYER}`/`{RIVAL}` 7 glyphs, species 12,
items 20, moves 16.

```bash
python3 tools/hebrew/textwidth.py "<text as in .string, with \n \l \p and \$>"   # px per row, bytes
python3 tools/hebrew/wrap.py "<text>" [--kind KIND | --px N] [--no-scroll]        # moves only \n/\l
python3 tools/hebrew/audit.py data/maps/<Map>                                    # every string of a folder
```

### 3.4 Worked example: change one dialogue line, end to end

The target is `CharcoalKiln_Text_Apprentice4` in `data/maps/AzaleaTown_House1_hns/scripts.inc`. It
is now:

```
CharcoalKiln_Text_Apprentice4:
	.string "הסלופוק חזרו, ואפילו מצאת את פארפג'ד.\p"
	.string "אתה הכי מגניב, אחי!$"
```

Suppose the line should read "…מצאת את פארפג'ד בתוך היער החשוך." The outputs below are real.
The steps up to the commit were run on a scratch copy; the demo text was never committed.

**1. Branch.** Use one worktree per topic:

```bash
git worktree add ../pokehns-heb-<topic> -b he/fix-<topic> he/main
cd ../pokehns-heb-<topic>
```

**2. Measure the new text.** It is too wide for the prompt line:

```bash
python3 tools/hebrew/textwidth.py "הסלופוק חזרו, ואפילו מצאת את פארפג'ד בתוך היער החשוך.\pאתה הכי מגניב, אחי!\$"
#    p1 r1  278 px +8 arrow  (p)
#    p2 r1   96 px  ($)
#    73 bytes after expansion
```

**3. Re-wrap.** `wrap.py` moves only the breaks:

```bash
python3 tools/hebrew/wrap.py "הסלופוק חזרו, ואפילו מצאת את פארפג'ד בתוך היער החשוך.\pאתה הכי מגניב, אחי!\$"
# הסלופוק חזרו, ואפילו מצאת את פארפג'ד\nבתוך היער החשוך.\pאתה הכי מגניב, אחי!$
#    p1 190/208 px FONT_NORMAL הסלופוק חזרו, ואפילו מצאת את פארפג'ד
#    p1  85/200 px FONT_NORMAL בתוך היער החשוך.
#    p2  96/208 px FONT_NORMAL אתה הכי מגניב, אחי!
```

**4. Edit the source.** Write one `.string` line per `\n`, `\l` or `\p`, indented with a tab:

```
CharcoalKiln_Text_Apprentice4:
	.string "הסלופוק חזרו, ואפילו מצאת את פארפג'ד\n"
	.string "בתוך היער החשוך.\p"
	.string "אתה הכי מגניב, אחי!$"
```

The alternative for many strings is the unit route:

```bash
python3 tools/hebrew/make_chunks.py B21 --out build/hebrew/units   # B21: 50 files, 582 units (0 names pre-filled), 5 chunks
# keep the units you change in CHUNK.json; write TR.json = {"<unit id>": "<hebrew>"}
python3 tools/hebrew/merge_he.py CHUNK.json TR.json
python3 tools/hebrew/checkunits.py CHUNK.json      # exit 1 on any error
python3 tools/hebrew/units.py apply CHUNK.json --dry-run && python3 tools/hebrew/units.py apply CHUNK.json
```

Here the unit id is `data/maps/AzaleaTown_House1_hns/scripts.inc::CharcoalKiln_Text_Apprentice4`.

A `checkunits.py` failure looks like this; the first version above lacked the `$`:

```
E data/maps/AzaleaTown_House1_hns/scripts.inc::CharcoalKiln_Text_Apprentice4
    E TERMINATOR
    E WIDTH page 1 line 1: 278 px > 200
9 units, 8 translated and clean, 1 with errors
```

Read section 3.7 before using `units.py apply` on a file that is already Hebrew.

**5. The CI checks on the file:**

```bash
python3 tools/hebrew/drift.py data/maps/AzaleaTown_House1_hns/scripts.inc
# ok   data/maps/AzaleaTown_House1_hns/scripts.inc
python3 tools/hebrew/audit.py data/maps/AzaleaTown_House1_hns
# == translated strings: 0 errors, 0 warnings
```

For a name, also run `namecheck.py --all` and `glossary_widths.py`.

**6. Build the clip-report ROM:**

```bash
make hns RTL_CLIP_REPORT=1 -j12
```

From a clean tree this took 1298 s on the reference machine, with another build running at the
same time. A tree exported with `git archive` first needs `touch .histignore`.

**7. Render the label.** This takes seconds:

```bash
export HNS_RUNNER=<runner> HNS_SAVES=<saves>
cd <a short folder>        # every path handed to hnsrun must be <= 120 characters
python3 <repo>/tools/hebrew/emu/sweep.py run <repo>/pokehns-clip.gba sd --label CharcoalKiln_Text_Apprentice4 --shots all
# totals: OK 1        sd/results.jsonl: "status": "OK", "pages": 2, "clips": 0
#                     sd/shots/CharcoalKiln_Text_Apprentice4_01.png, _02.png
```

**Open the PNGs and read them.** `OK` means no clipping and no crash; it does not mean correct
Hebrew. On a clipped line the end of the line in reading order is simply missing. To see what a
clip report looks like, run `sweep.py selftest` (section 4.5).

**8. Commit and merge:**

```bash
git add data/maps/AzaleaTown_House1_hns/scripts.inc
git commit        # one file; imperative subject; the body says why
git -C <main worktree> merge --no-ff he/fix-<topic> -m "Merge he/fix-<topic>: <what it brings>"
```

- Text is never cherry-picked onto `he/renderer`.
- `STATUS.md` is regenerated from the next release candidate's full sweep (section 5).
- A change counts as seen on screen only on the ROM that ships.

### 3.5 Glossary and names

**Files**

- `translation/hebrew/glossary.csv`: columns `kind,constant,english,firered_hebrew,proposed_hebrew,status,notes`;
  7,092 rows, with CRLF line ends. The tools read `proposed_hebrew`.
  - Status `inherited` (1,940) comes from the FireRed fork.
  - Status `proposed` (5,152) is new and has not been checked against an official Hebrew source.
- `translation/hebrew/glossary_sources.csv`: `kind,constant,english,source,pattern` (5,529 rows).
  `make_chunks.py` uses it to pre-fill name fields.

**Where a name comes from** (`transliteration_rules.md` §0):

1. the FireRed fork;
2. the Pokémon Israel Pokédex;
3. the rules in that file.

Keep families together; `python3 tools/hebrew/translit_stats.py 'EON$'` lists the precedents.

**Renaming or adding a name** is a checklist; no tool propagates a rename:

1. Commit `glossary.csv` alone, **before** any text that uses the name.
2. `python3 tools/hebrew/namecheck.py --all --warnings` should print `rows 7092, still empty 0,
   problems 0` and `warnings 0, allowlisted 60`; then run `python3 tools/hebrew/glossary_widths.py`
   (today `1 over budget`: the EXEGGUTOR-A healthbox name, 49 px against 48, decided in Q129).
3. Change every dialogue use (`git grep` the old Hebrew and the English), one file per commit.
4. For trainer or map names, run `python3 tools/hebrew/apply_names.py --dry-run`, then without
   `--dry-run`.
5. For species, run `python3 tools/hebrew/gen_dex_alpha.py` and commit `pokedex_orders.h` alone.
   Its `TEXT_RTL` list is engine data, so cherry-pick that commit onto `he/renderer` too
   (`f47c725548` there); drift fails until the baseline has it. For a species, move or Easy Chat
   word, run `gen_ec_order.py` and `gen_ec_letters.py` (CI runs all three with `--check`).
6. Update test expectations where order or text changes. For example, `4c6ba54599` updated
   `test/bag.c` for the berry names.
7. After a bulk glossary edit, diff the row **keys** between revisions (section 6.2): a rewrite
   once dropped 5 rows silently.

**Consistency warnings** (`namecheck.py --warnings`; they never change the exit status):

- `--fr-sync` compares each name with the FireRed Hebrew tree as it is now (`HNS_FIRERED`, default
  `../pokefirered-heb`), within the same kind. Take FireRed's name only when it fixes an error in
  ours (`DECISIONS.md` Q136); type names stay.
- `--translit` flags transliteration slips in `proposed` rows; `--dupes` flags one English person
  name with two Hebrew spellings.
- `tools/hebrew/data/namecheck_allow.json` lists every difference kept on purpose, with the reason.
  An entry pins both names, so a later change on either side warns again, and an entry that no
  longer matches is reported `STALE`.

### 3.6 How a decision is made

Do not guess on a style call that STYLE.md and the glossary do not cover. Raise it.
`DECISIONS.md` records each one with:

- the question and its source;
- an analysis with path:line evidence and pixel measurements;
- an options table (option, how, risk);
- the choice and the reason;
- the files it changed.

Q2 (`DECISIONS.md:237-255`) is a typical entry.

Apply a decision in this order:

1. glossary rows first (`153dd6f057`);
2. one commit per file, titled "Apply the review decisions to `<file>`";
3. any new rule into STYLE.md (`68258b07c8`);
4. re-review the affected screens on the next release candidate.

### 3.7 Pitfalls in the text tools

- `units.py apply` refuses a tree string that changed since extraction, and one that already
  holds Hebrew other than the unit's `he` (an old chunk would undo a later fix).
  `--overwrite-hebrew` replaces such Hebrew on purpose.
- **One token rule.** `drift.py` defines it (`DROPPABLE_TOKENS`, `REORDERABLE_TOKENS`,
  `same_tokens`), and `units.py` and `checkunits.py` import it: `{POKE}` `{PKMN}` `{POKEBLOCK}`
  `{ID}` `{NO}` `{PK}` may go; `{B_BUFF1}`..`{B_BUFF3}` may trade places with each other (also
  across another token), never with another token.
- `units.py` handles `.inc`, `.s`, `.c` and `.h` only. `.party` and `.json` go through
  `apply_names.py`.
- A blank line inside a `.string` block ends the unit (`b81dddd2b3`).
- `gen_dex_alpha.py --check` regenerates the order in memory, lists each entry that would move and
  exits 1 when the header is stale (CI). Of the five entries its last regeneration moved, only
  EXEGGUTOR-A is visible in H&S's list.
- `namecheck.py --all` keys rows on `(kind, constant)` and reports a key that appears twice in
  `glossary.csv` as `DUPKEY` (exit 1). It cannot detect a lost row or a truncated Hebrew value.
- **Battle text has test expectations.** Changing a string listed in
  `test/hebrew_battle_messages.h` (66 entries) gives a `NEW FAILURE` in `make check` until the
  table is rebuilt (`tools/hebrew/testmsgs/README.md`).

---

## 4. Testing

### 4.1 The ladder, cheapest first

| Level | Tool | Catches | Time (reference machine) |
| --- | --- | --- | --- |
| one string | `textwidth.py`, `wrap.py` | px width, rows, bytes | instant |
| one chunk | `checkunits.py` | tokens, `$`, escapes, charset, digits, Latin, width, lines | instant |
| one file vs English | `drift.py` | anything changed outside strings, token order, `$`, charset | 3 s for 708 files |
| whole tree | `audit.py --baseline ../pokehns-en` | WIDTH, LINES, BUFFER, BYTES, TERMINATOR, CHARSET | 28 s |
| glossary | `namecheck.py --all --warnings` | byte limits, final letters, duplicates; warnings for FireRed differences, transliteration slips, two-way names | instant |
| generated data | `gen_dex_alpha.py`, `gen_ec_order.py`, `gen_ec_letters.py`, `flag_gates.py`, each `--check` | a stale A–Z order, Easy Chat list or live-label list | instant |
| tool tests | `python3 -m unittest discover -s tools/hebrew/tests` | the tools themselves (137 tests) | 10 s |
| game logic | `make check BUILD=hns` + `check_tests.py` | a test that passes upstream but fails in Hebrew | about 4 min at `-j12` in the release worktree (rc5, rc20: `make_check.log` created to last written; 15 hydra runners), 13 to 20 min in CI |
| screens | `hns.py tour` (71 tours) | crashes, timeouts, wrong typed bytes; screenshots for review | about 3 min |
| glyphs outside windows | `hns.py tour --clip`, `sweep.py` on the clip ROM | every glyph drawn outside its window | about 2.5 min: 6,611 labels in 150 s on rc21's clip ROM (191 s with a cold cache) |
| every map | `mapwalk.py` | CRASH, maps that never give control back | 329 s for 543 maps |
| saves | `ladder.py run scripts/ladder_validate.txt` | English 2.0.x saves still load and work | about 1.5 s per save |
| other emulators | `crosscore` + libretro cores + `ccdiff.py` | renderer differences between cores | about 2 s per core |
| English left in ROM | `rom_sweep.py` | English runs in the binary | 4 s |
| eyes | `pairsheets.py`, `hns.py tourdiff`, reviewers plus refuters (`tools/hebrew/release/REVIEW.md`) | overlap, mirroring, digit order, glyph shapes, wrong translation | per release |

Two rules from the original brief:

- Mark anything not seen on screen as unverified.
- Test the exact `.gba` you ship, never a build tree.

### 4.2 Static checks: the CI `audit` job, run locally

CI creates the two worktrees from `origin/he/renderer` and `origin/master` (`hebrew.yml:43-48`).
Locally, the tag `Release-v2.0.6` (fetched in section 2.3) stands in for CI's `origin/master`. The
expected output below is a local run on `he/wip-r19` (2026-11-09).

```bash
set -o pipefail
# 1. drift (hebrew.yml:50-54): only strings may differ from he/renderer
git diff --name-only Release-v2.0.6...HEAD -- data src | grep -E '\.(inc|s|c|h|party|json)$' | xargs python3 tools/hebrew/drift.py --quiet
#    last line: drift: 708 files, 0 FAIL, 336 with warnings only   (exit 0)
# 2. layout audit (hebrew.yml:56-57); creates build/hebrew; prints the report's two == lines
python3 tools/hebrew/audit.py --baseline ../pokehns-en --report build/hebrew/audit.txt
#    == translated strings: 0 errors, 48 warnings, 85 suppressed by baseline ../pokehns-en
#    == English (untranslated) strings, baseline only: 448 errors, 0 warnings   <- informational
#    line 1 of the report: audit ...: 41539 strings (25592 translated)
# 3. glossary (hebrew.yml:59-60)
python3 tools/hebrew/namecheck.py --all --warnings
#    rows 7092, still empty 0, problems 0
#    warnings 0, allowlisted 60
# 4. generated data (hebrew.yml:62-71)
python3 tools/hebrew/gen_dex_alpha.py --check     # gen_dex_alpha: 1080 entries, the TEXT_RTL list is up to date
python3 tools/hebrew/gen_ec_order.py --check      # gen_ec_order: 18 groups, the header is up to date
python3 tools/hebrew/gen_ec_letters.py --check    # gen_ec_letters: 23 lists, the header is up to date
python3 tools/hebrew/flag_gates.py --check        # total: live 6585, flag_off 451, not_built 147 / no change
# 5. tool tests (hebrew.yml:73-74)
python3 -m unittest discover -s tools/hebrew/tests
#    Ran 137 tests ... OK   (no skip with tools/preproc built and ../pokehns-en/pokehns.gba present)
# not in CI: item plurals
python3 tools/hebrew/plurals.py                   # items 902, stackable 693, problems 0
```

**How to read the results**

- **drift errors** (exit 1) are `STRUCTURE`, `TOKENS`, `TERMINATOR`, `CHARSET` and `SHRUNK`.
  Warnings (`PAGES`, `LATIN`, `UNTRANSLATED`) never fail the run unless you pass `--strict`.
  Section 6.2 lists every kind. `.party` and `.json` files are checked too: a renamed `Name:` line
  counts as a string.
- **audit:** the exit status is 1 only for a Hebrew error that the baseline does not suppress.
  - The 48 warnings are `FIT`: 13 item names, 30 move names and 5 EXEGGUTOR-A rows (Q129) that
    fit only after the game falls back to a narrower font.
  - A finding reads `w item_name FIT 79 > 72 p1 r1 [summary held item FONT_NORMAL] (...)
    src/data/items.h:3095`: kind, check, measured > budget, page and row, where it is drawn, and
    the source line.
  - CI counts fewer strings (run 41933578987 at `fe509e0043`: `39059 strings (24836
    translated)`), with the same 0 errors, 48 warnings and 85 suppressed. The difference is the
    build. `walk_tree` (`audit.py:448-464`) reads every `.c` and `.h` under `src/`, and a built tree
    has six git-ignored headers that `make` generates:
    - `src/data/trainers.h`, `trainers_hns.h`, `trainers_frlg.h`, `battle_partners.h` and
      `debug_trainers.h`, made from the `.party` files (`trainer_rules.mk:3-12`);
    - `src/data/region_map/region_map_entries.h`, made from the JSON (`json_data_rules.mk:4-6`).

    They add 2,480 strings (756 translated), all repeats of the `.party` and JSON names, and no
    finding. A clean `git archive` of the commit gives CI's count exactly, with the same findings
    (round 19). Section 8.1 has the fix.
- **tool tests in CI:** `Ran 132 tests ... OK (skipped=2)` at `fe509e0043` (no built
  `tools/preproc`, no English ROM); `he/wip-r19` adds 5.

### 4.3 The test suite

**The rule:** upstream 2.0.6 fails 1,899 of its own tests. The Hebrew build is held to "no test
fails that passes upstream" (`check_tests.py:2-9`; `docs/hebrew_translation.md:119-126`). The
brief's "every test passes" no longer matches practice.

```bash
make check BUILD=hns -j12 > make_check.log 2>&1
python3 tools/hebrew/check_tests.py make_check.log
# 5074 results, 1899 failing, 1899 of them known upstream failures
# 4 known failures now pass                              (0.2 / rc5, exit 0)
```

- **Ignore make's exit status.** It is 2 whenever a test fails, and upstream fails its own tests.
- **The hydra segfault.** On macOS the 0.2 log ends with `make: *** [check] Segmentation fault: 11`
  and prints no summary. The cause: the hydra runner's summary lists hold 32 × 50 = 1,600 rows
  (`tools/mgba-rom-test-hydra/main.c:40-41`), but each runner's rows are written at the running
  total of failures, guarded only by the per-runner limit of 50. With one runner per core (15 on
  the reference machine) and about 1,900 failures, the later runners wrote past the arrays.
  Commit `8d52b4cccf` (branch `he/fix-upstream-hydra`, from `he/upstream-fixes`) also limits the
  destination index at `main.c:793`, `:802`, `:812` and `:821`; the counters still count everything
  and the printed lists are unchanged. With it, `make check BUILD=hns -j8` (12 min 18 s in a fresh
  worktree) printed the whole summary (`FAILED 1924`, `TOTAL 5135`) and no segfault, with runners
  12-14 starting past row 1,600; `check_tests.py` found 1,903 failing tests, all known. Only the
  test tool changes, not the ROM. It is merged into `he/main` (`08027d9879`, the commit 1.0 is
  built from): rc21's `make_check.log` ends with the whole summary (`FAILED 1920`, `TOTAL 5135`)
  and no segfault. `he/upstream-fixes` gets it by a fast-forward to `8d52b4cccf`.
- `check_tests.py` parses the `[NN] NAME: RESULT` lines. It counts FAIL, ERROR, TIMEOUT and CRASH
  as failing, prints `NEW FAILURE: <name>` for any name missing from
  `tools/hebrew/data/known_test_failures.txt` (1,903 names), and exits 1 then.
- `--write-known` rewrites that list. **Only ever run it on a log of the English upstream tree**;
  a Hebrew log would hide regressions.

**Chunked run (what CI does; use it on a machine short of memory):**

```bash
make BUILD=hns -j12 pokehns-test.elf
python3 tools/hebrew/check_chunked.py --build hns --jobs 12 --log check.log --skip-crashing --chunk-timeout 900
python3 tools/hebrew/check_tests.py check.log
# CI: 5754 test names, 47 chunks; 5073 results, 1898 failing, 1898 of them known upstream failures
```

- `check_chunked.py` runs one test-name prefix per chunk.
- `--skip-crashing` skips the one test in `tools/hebrew/data/crashing_tests.txt` (`Capture: ball
  data is properly set in captured pokemon`, `test/battle/capture.c:212`). On Linux it does not
  report a crash: the emulator spins and eats memory.
- Exit 3 means a chunk passed `--chunk-timeout`; exit 2 is a setup error (no test ELF, or a
  crashing name that is not in `test/`).
- `check_chunked.py` was not run locally for this handoff; only its chunk plan was computed. CI
  runs it on every push (run 41918360015: `5073 results, 1898 failing, 1898 of them known upstream
  failures`).

**Hebrew-specific test changes**

| Change | Where |
| --- | --- |
| battle tests compare against Hebrew messages | `test/test_runner_battle.c:3409-3440` and `test/hebrew_battle_messages.h` (`310277816e`) |
| bag sort order | `test/bag.c` (`903ce11705`, `4c6ba54599`) |
| item-name widths | `test/text.c:175,202` (`30abd6d566`) |

### 4.4 Emulator harness: setup and smoke checks

`tools/hebrew/emu/hnsrun.c` is a headless libmgba runner. It reads commands from stdin and stops
with `CRASH` when the PC leaves BIOS, ROM or RAM. `hns.py` drives it and resolves every address
by name from the ELF next to the ROM.

```bash
export HNS_RUNNER=<path to hnsrun> HNS_SAVES=<builds>/saves
export HNS_UNITS="$PWD/build/hebrew/units"   # absolute: the sweep runs from another folder
export HNS_WORK=<a SHORT folder>        # hnsrun keeps 127 characters of a path; sweep.py allows 120
E=tools/hebrew/emu
python3 $E/hns.py selfcheck
# ok    sizeof(SaveBlock1) = 0x3D90 (measured 0x3D90) ... all checks passed
python3 $E/hns.py sym gMain CB2_Overworld      # addresses from the ELF
python3 $E/hns.py where <hex pc>               # symbol+offset, also for a CRASH pc
python3 $E/hns.py map NEW_BARK                 # MAP_NEW_BARK_TOWN_HNS group 0 num 0
```

The full environment table is in `tools/hebrew/emu/README.md` ("Environment"). In it, `HNS_SRC`
is the source tree for `MAP_*` and `SPECIES_*`, `HNS_RTC` is the fake clock (default 2026-01-01
12:00 UTC; the game reads it in the host's time zone, section 2.6), and `HNS_LOG=1` echoes every
mGBA log line.

### 4.5 Tours, clip reports, the dialogue sweep

**Tours.** `tools/hebrew/emu/tours/*.txt` holds the 71 release tours (files starting with `_` are
includes); its subfolders hold the review rounds' tours, which the release does not run. Families:
`pbi_*` 17, `menu_*` 12, `bv_*` 11, `chr_*` 10, `battle_*` 6, `cardgear_*` 3, `ncm_*` 3, `btw_*` 3,
`naming_*` 2, `bfm_*` 2, `dex_forms`, `field_*`.

`menu_00_setup` builds the base save that the menu tours start from. Each file's header says what
it covers. The release tours start from saves at the top of `<builds>/saves`. A round tour
(`tours/<round>/`) that names a save found only in a subfolder needs `HNS_SAVES` set to the folder
that holds it: `saves/r8` for round 8, a folder under `saves/r10/` or `saves/r11/` for those
rounds, and `saves/r7/saves_aug` for rounds 3-7 and `verify_ctxdpad` (`<builds>/README.md`).

On the English ROM, 70 of the 71 tours report OK. `naming_nickname` stops with ERROR at its first
check of the typed Hebrew bytes (`tours/naming_nickname.txt:71`), and `naming_player` reports OK
only because it has no byte checks; both type on the Hebrew keyboard, so they are Hebrew-only by
design. The other 69 run on English.

```bash
python3 $E/hns.py tour pokehns.gba OUT                              # all: "71 tour(s): 71 OK", about 3 min (rc20: 188 s)
python3 $E/hns.py tour pokehns.gba OUT --only '^menu_trainercard$'  # one tour plus its dependency
python3 $E/hns.py tourdiff PREV_OUT OUT                             # DIFF / ONLY1 / ONLY2 per PNG; exit 1 if any differ
python3 $E/hns.py sheet OUT/sheet.png OUT/menu_bag --cols 4         # contact sheet
python3 tools/hebrew/pairsheets.py EN_TOURS OUT SHEETS --per 6 --scale 2   # English left, Hebrew right
```

- **Statuses** (`OUT/tour_report.json`):
  - `OK`;
  - `CRASH`: the PC is out of range;
  - `TIMEOUT`: a wait never matched;
  - `ERROR`: a script or setup error;
  - `SKIPPED`: a dependency failed.
- A failed tour saves `OUT/TOUR/_crash.png` or `_timeout.png`, plus `run.log`.
- **Tours are deterministic:** the same ROM and tours give byte-identical PNGs. So always
  `tourdiff` a candidate against the previous one, and look at every DIFF. **OK does not mean
  right**: a tour without byte checks reports OK whatever it typed. `naming_nickname` checks every
  byte of its three typed names (17 `expect8` lines) for this reason.

**Clip reports.** Build `pokehns-clip.gba` (section 2.4), then:

```bash
python3 $E/hns.py tour pokehns-clip.gba OUT --clip     # OUT/<tour>/clip.json, tour_report "clipped"
python3 tools/hebrew/cliptour.py run SCRIPT OUT --rom pokehns-clip.gba --save S   # one script
```

- A record names the window, the font, x, and the clipped glyph, marked `⟦ ⟧` in the decoded
  string.
- `lost` > 0 means more than 16 clips happened between two shots, overflowing the ring buffer.
- The renderer's log is `gRtlClipLog[16]` / `gRtlClipCount` (`src/text.c:1047-1077`).
  `hns.py sym gRtlClipLog` fails on a release ELF, which is a quick way to tell the two builds
  apart.

**The dialogue sweep** draws every live script text label in the message box, from
`ladder4_league.sav`:

```bash
cd <short dir>
python3 <repo>/tools/hebrew/emu/sweep.py run <repo>/pokehns-clip.gba sw --shots clip   # rc21, fresh units: 6611 labels, OK 6611, 150.3 s
python3 <repo>/tools/hebrew/emu/sweep.py run CLIP.gba sw --batch B20 --limit 40       # a subset
python3 <repo>/tools/hebrew/emu/sweep.py report sw         # rebuild sw/sweep.json + sw/report.txt
python3 <repo>/tools/hebrew/emu/sweep.py selftest CLIP.gba st   # proves the detector on a label whose string in this ROM has Hebrew
```

- **Statuses:** CRASH, HANG, ABNORMAL, CLIP, OK, SKIP. `SKIP` is a label not assembled into
  this build. `flag_gates.py` moves the 147 Emerald and Kanto labels that rc20 skipped to
  `not_built` in `live_labels.json`. With units made again by `make_chunks.py all`, the sweep of
  rc21's clip ROM selected 6,611 labels: 6,611 OK, 0 SKIP, 0 CLIP (round 19). rc21's own release
  sweep still read older units: 7,209 labels, 7,062 OK, 147 SKIP. The 6,611 are a subset of those
  7,209, so every live label was OK there too. Make the units again before a candidate's sweep
  (section 5).
- **Selections:** `--label`, `--labels-file`, `--match`, `--file`, `--batch`, `--translated` (the
  unit file has Hebrew), `--hebrew-only` (the string in this ROM has Hebrew), `--sample`,
  `--offset/--limit`; add `--resume` to continue a run. `make_chunks.py` writes its units from the
  English baseline, so with them use `--hebrew-only`. `--translated` on them stops with
  `sweep: no unit has Hebrew; use --hebrew-only` and exit 2 (`sweep.py:127-133`).
- With no unit files and no `--label`, the sweep stops with `sweep: no script units in ...` and
  exit 2.
- **A real CLIP line,** from the selftest's deliberately broken ROM:
  `CLIP gText_Oak_MainSpeech  9 glyph(s) outside the window; page 1 row 1 (translated): 9 glyph(s) past the left edge, up to 38 px (window 216 px, win 0)`
  - A `+placeholder` kind is usually the worst-case `{STR_VAR}`.
  - A plain `translated` CLIP is too-wide Hebrew: re-wrap it.
  - A false CLIP happens where the game puts a number in `STR_VAR_1..3` but the sweep fills a
    species name (apprentice rank, BP). Rerun with `--strvar-text`.
- **What the clip report cannot see:** overlap inside a window, a cursor over text,
  sprite-drawn UI, and vertical overflow (except the sweep's third-row warning). Use screenshots.

**STATUS.md from a sweep:**

```bash
python3 tools/hebrew/status_report.py --sweep RC/tests/sweep/sweep.json
# 650 files -> ...: {'seen on screen': 525, 'translated': 125}   (rc20's sweep, after flag_gates.py)
```

- Without `--sweep`, every "seen on screen" row falls back to "translated".
- "Seen on screen" means **the harness rendered the label**, not that a person read it.
- STATUS counts a string as Hebrew if it holds any Hebrew letter (`status_report.py:82`), so mixed
  Latin-and-Hebrew lines pass (section 8.2).

### 4.6 Map walk, save ladder, cross-core, ROM sweep

```bash
python3 $E/mapwalk.py pokehns.gba "$HNS_SAVES/ladder6_postgame.sav" OUT [--only RE] [--max N]
# rc5: 543 maps in 329 s: {'OK': 507, 'HELD': 36}
python3 $E/ladder.py --rom pokehns.gba run $E/scripts/ladder_validate.txt OUT --save "$HNS_SAVES/ladder2_badge1.sav"
# continue, leave the Center, open Pokédex, party, bag, card, PokéGear: 13 screenshots, exit 0
python3 $E/ladder.py --rom pokehns.gba run $E/scripts/ladder_validate_newgame.txt OUT --save "$HNS_SAVES/ladder1_newgame.sav"
# rung 1 (the bedroom): continue, bag, trainer card
python3 tools/hebrew/rom_sweep.py pokehns.gba --json OUT.json
# 6283 text runs (6365 candidates), 6255 still English, 4.2s   exit 1 (always, on this build)
```

- **Map walk:**
  - `HELD` means the game never gave control back within the frame budget. Compare with an
    English walk before calling it a bug: 34 of the 36 HELD maps also hold in English (Frontier
    rooms, Pyramid, Tents, Union Room). The other 2 are Battle Arena rooms, where the Hebrew run
    won the first battle.
  - Treat any `CRASH` as real until the English ROM with the same save crashes the same way.
  - The English walk of 0.2 crashed in the Dome pre-battle room (`pc=0A0E8ECC`, the ROM's
    wait-state mirror of `0x080E8ECC`, `FillBitmapRect4Bit+0xA0`: valid code reached through a
    pointer with bit 25 set). Walked alone (`--only DOME_PRE_BATTLE`), the English map is HELD at the
    room's own "Your 1st-round match is next" text and does not crash, so the crash needs state
    from earlier in the full walk. Which state is **unverified**; the Hebrew walk holds the map
    too. No release note.
- **Save ladder:** six saves made **on the English ROM**, then loaded in the Hebrew one. Rung 1 is
  in the bedroom, not a Center, so it is validated with its own script
  (`ladder_validate_newgame.txt`); `run_release_tests.sh` records each rung's exit code and
  `make_testing_md.py` refuses a rung whose log does not end in `exit 0`.
- **The other way round:** saves written by the Hebrew ROM load in the English ROM.
  - A bedroom save whose player name is the Hebrew גולד (`<builds>/saves/ncm_base_he.sav`):
    `ladder_validate_newgame.txt` exits 0 there. The bedroom, bag and trainer card work, and the
    Hebrew name shows as **blank** on CONTINUE and on the card.
  - A mid-game and a post-game save (round 19, rc21). `ladder3_ecruteak` and `ladder6_postgame`
    were loaded in the Hebrew ROM and saved in game in the Pokémon Center. In the English ROM,
    `ladder_validate.txt` exits 0 on both, and so does a script that opens BILL's PC, MOVE
    POKéMON, the box options and the JUMP list. There is no crash.
  - The same steps on an English-written control save of the same moment give md5-identical
    screenshots: 13 validation and 11 PC shots per save, showing GOLD, ID 23773, ₽17200 or
    ₽351300, the party, the bag, the Pokédex, the PokéGear and the boxes.
  - Byte for byte, the two saves differ only in a sub-second play-time counter (SaveBlock2
    `0x12`) and in the `script` pointers of SaveBlock1's object event templates. Each pair of
    pointers names the same label in the two ELFs, and the English ROM rewrites them on CONTINUE
    (`src/overworld.c:2200` calls `LoadSaveblockObjEventScripts`, `:592-600`).
  - Saving after leaving the Center and walking back in also validates.
  - Not tried (**unverified**): a save made outside a Pokémon Center, such as on a Battle Pyramid
    or Trainer Hill floor. Those floors load their object scripts their own way
    (`src/overworld.c:2195-2198`).
  - The scripts and logs are in `<private>/scratch/screens/r19/emu-facts/t1/`.
- **ROM sweep:** do not gate on its exit status. Of the 6,255 runs, 0 are on live labels, 3,265
  on dead Emerald labels, 16 debug-only, and 2,974 untracked (mostly `data/event_scripts.o` and
  `src/credits_hns.o`). Compare its `--json` with the previous candidate's.
- **Cross-core:** `crosscore CORE.dylib ROM OUTDIR [save] < tools/hebrew/release/crosscore_menus.txt`,
  then `python3 tools/hebrew/release/ccdiff.py REF_DIR DIR...` (frames compared in RGB555). The
  frontend answers every core option with the core's default, plus
  `gba_use_mednafen_save_method=libretro` (`tools/hebrew/emu/README.md`, "Cross-core"). All six
  cores load the save and draw every screen like mGBA. Expected differences, on every core: the
  intro frame (the animation runs at another point), the start-menu clock, and an animation frame
  of the bag arrows or party icons; on the main menu the two darkened buttons are one step of the
  5-bit colour apart (`notes.json` `crosscore_notes`).

### 4.7 CI

`.github/workflows/hebrew.yml` runs on a push to `he/**`, a pull request to `he/main`, and by
hand. Every job names its image, `runs-on: ubuntu-26.04`, and uses Ubuntu's gcc-arm-none-eabi
(14.2). The actions are `actions/checkout@v5` and `actions/upload-artifact@v6`, which run on
Node 24; run 41918360015 has no Node 20 annotation.

| Job | Steps | Time in runs 41918360015 / 41933578987 |
| --- | --- | --- |
| `build` | `make hns -j$(nproc) -O`, then the clip ROM | 5m47s / 4m32s |
| `audit` | the two worktrees, drift (`.inc`, `.s`, `.c`, `.h`, `.party`, `.json`), audit, `namecheck.py --all --warnings`, the `--check` of `gen_dex_alpha.py`, `gen_ec_order.py`, `gen_ec_letters.py` and `flag_gates.py`, tool tests | 49s / 1m3s |
| `check` | test ELF at `-j2`, with a `[mon]` memory line every minute; `check_chunked.py --skip-crashing --chunk-timeout 900`; `check_tests.py`; artifact `check-log` (14 days) | 13m1s / 20m0s (test ELF 7m56s, chunks 11m38s) |

```bash
gh run list -R ronyeh2/pokehns-expansion-heb --workflow hebrew.yml --limit 8
gh run view <id> -R ronyeh2/pokehns-expansion-heb --log | grep -E 'results,|NEW FAILURE|Ran [0-9]+ tests|translated strings'
```

- **Push `he/renderer` before `he/main`** when an engine commit is involved. CI's drift
  compares with `origin/he/renderer`, so a missing cherry-pick fails it.
- **A new runner image** brings a new gcc-arm-none-eabi. Move to it by changing the three
  `runs-on:` lines in one commit and checking that run.
- The upstream workflow `.github/workflows/build.yml` runs only on pushes and pull requests to
  `master` and `upcoming`, so a pull request into `he/main` runs only the Hebrew workflow.
- **CI never runs** the emulator harness, the sweep, the map walk or any visual check.

### 4.8 Visual review

Automated checks cannot see these, so every release candidate gets a screenshot review:

- overlap and cursor position;
- mirroring and digit order;
- glyph shapes;
- English left on screen;
- a wrong translation.

1. **Against English:** `pairsheets.py` on the English tour run and the candidate's tours.
2. **Against the previous candidate:** `hns.py tourdiff`, then look at every DIFF. rc3 to rc4
   gave `435 identical, 60 differ`, the "60 tour frames" of `DECISIONS.md:1386`.
3. **Dialogue pages:** sweep screenshots (`--shots all`) of the labels a change touched. 0.2
   reviewed 119 labels on 336 pages.
4. **Reviewers and refuters:** several independent reviewers, split by batch. Each finding then
   goes to a second reviewer who tries to refute it. Outcomes are `confirmed_expected`,
   `confirmed` (fix it or list it as a known issue) or `refuted`. 0.2: 8 confirmed, 8 refuted
   (`DECISIONS.md`, "Review of the changed screens").
5. **When a screenshot is ambiguous:** dump the pixels, read the string from RAM, or simulate
   the pen. Never argue from a downscaled image.

The procedure, the lenses, the finding format, the refuter outcomes and one reviewer and one
refuter prompt are in [`tools/hebrew/release/REVIEW.md`](tools/hebrew/release/REVIEW.md). The
scripts that ran the earlier reviewers were not kept; the workflow script that translated the G01
chunks is archived as `<builds>/archive/rounds/hns-translate-g01.js`.

---

## 5. Releasing

The scripts are in `tools/hebrew/release/` (see its [README](tools/hebrew/release/README.md)).
Each prints usage with `--help`. The two shell scripts also take `--check`, which checks every
input, prints the resolved values and changes nothing. They have only run on macOS.

Ported from `<private>/scratch/release/`, the new `make_testing_md.py` reproduces the 0.2
`TESTING.md` byte for byte from rc5 (SHA-1 `6ec054019a3418c5293a8fb13625c8f49b3acbae`).

**One-time setup** (section 2.6):

- the English tree built;
- `hnsrun`;
- `HNS_SAVES` pointed at `<builds>/saves`;
- `make_chunks.py all`, run again before each candidate (rc21's sweep read units older than
  `flag_gates.py`: 7,209 labels, 147 skipped, instead of 6,611; section 4.5);
- the cores from `<builds>/reference/cores/` unzipped into `HNS_CORES` (`crosscore` is built by the
  test script);
- `HNS_EN_MAPWALK` pointed at `<builds>/reference/mapwalk_en.json`.

**Steps**

1. **Pick the commit.** `he/main` with CI green and section 4.2 clean.

2. **Build in a clean worktree.** The script removes and re-creates `../pokehns-release`
   (`HNS_RELEASE_WORKTREE`); it refuses a folder that is not a worktree of this repository. It accepts any other worktree of this repository and removes it with `git worktree remove --force`, which discards uncommitted changes: never point `HNS_RELEASE_WORKTREE` at `../pokehns-en`, `../pokehns-heb-engine` or a feature worktree, and read the `worktree` line of `--check` first.
   ```bash
   RC=build/hebrew/release/rcN
   tools/hebrew/release/build_release.sh --check he/main "$RC" && tools/hebrew/release/build_release.sh he/main "$RC"
   ```
   - `RC` gets `pokehns.gba/.elf/.map`, `pokehns-clip.gba/.elf/.map`, the build logs, and
     `gbafix.log`, which must end in `gbafix: header already valid`.
   - It also gets `build_info.json` with the commit and the size, SHA-1 and CRC32 of both ROMs.

3. **`make check` on the same commit:**
   ```bash
   (cd ../pokehns-release && make check BUILD=hns -j12) > "$RC/make_check.log" 2>&1
   python3 tools/hebrew/check_tests.py "$RC/make_check.log" | tee "$RC/check_tests.txt"
   ```
   This is the release README's command; the rc5 and rc20 logs start with the test build, hydra
   ran 15 runners, and each took about 4 min. Since the hydra guard (`08027d9879`) the log ends
   with the whole summary; rc21's does, and `check_tests.py` read 5,074 results from it, 1,899
   failing, all known (section 4.3).

4. **Every harness test on the exact files:**
   ```bash
   tools/hebrew/release/run_release_tests.sh --check "$RC" && tools/hebrew/release/run_release_tests.sh "$RC"
   ```
   - It first checks that the worktree's ROMs are byte-identical to `RC`'s and that the worktree
     HEAD matches `build_info.json`.
   - It then runs, into `RC/tests`:
     1. the tours;
     2. the clip tours;
     3. the full sweep;
     4. `selfcheck`;
     5. `ladder_validate` on all six saves;
     6. the map walk;
     7. cross-core on six cores, plus `ccdiff.py`;
     8. `rom_sweep`.
   - A failing step does not stop the later ones: read the logs.

5. **Visual review** (section 4.8, `tools/hebrew/release/REVIEW.md`). Record the findings in
   `RC/visual_findings.json`. A finding that needs a fix means a new candidate, `rcN+1`.

6. **Edit `tools/hebrew/release/notes.json`** for the new release.
   - `release` must match the ROM name.
   - Also edit `known_issues`, `not_tested` (never empty), `visual_review` and `crosscore_notes`.
   - `static_checks` is typed from the CI run of the release commit (drift, audit,
     `namecheck.py --all --warnings`, the generator and `flag_gates.py` checks), because the
     scripts do not run those checks.
   - Update `map_walk.hebrew_only_held` to what the data shows.

7. **Write the report:**
   ```bash
   python3 tools/hebrew/release/make_testing_md.py "$RC" pokehns-he-2.0.6-1.0.gba "$RC/TESTING.md"
   ```
   It exits 1 instead of writing a sentence that its inputs contradict:
   - a changed header;
   - a failing selfcheck;
   - a clipped, crashed, hung or abnormal label;
   - a crashed map;
   - held maps that `notes.json` does not explain.

   Check every number against the logs anyway.

8. **Publish in the private builds repository** (`<builds>`). There is one release, 1.0, and each
   update replaces it in place; git history keeps the older builds:
   - Replace `pokehns-he-2.0.6-1.0.gba` with `RC/pokehns.gba`.
   - Replace its line in `SHA1SUMS` (check with `shasum -c SHA1SUMS`) and replace `TESTING.md`.
   - Commit with the message `Update 1.0 to the build of he/main <short sha>`, authored with the
     fork owner's GitHub noreply identity (`git config user.email` is set in that clone), as in
     `20b4aad`.
   - Copy the candidate's small records into `records/rcNN/` and add its row to
     `records/README.md`.
   - Push as in section 7.3.

9. **Back in the fork,** in separate commits:
   - regenerate `STATUS.md` from `RC/tests/sweep/sweep.json`;
   - record the review outcomes in `DECISIONS.md`.

**Policy** (`DECISIONS.md` Q138): a candidate that passes these steps is published to the private
builds repository even though nobody has played it by hand; `not_tested` always says so.

---

## 6. Troubleshooting catalogue

Columns: what you see, how to confirm it, the cause, the fix, and the commit that fixed it (where
there is one). Engine fixes exist twice: the commit merged into `he/main`, and its cherry-pick on
`he/renderer`, shown in parentheses.

### 6.1 Build and environment

| Symptom | Check | Cause | Fix | Commit |
| --- | --- | --- | --- | --- |
| `convert_png.c:5:10: fatal error: 'png.h' file not found` (macOS) | `which pkg-config` → `/opt/devkitpro/tools/bin/pkg-config` | `tools/gbagfx/Makefile:4-7` asks pkg-config; devkitPro's comes first in `PATH` and does not see Homebrew. `PKG_CONFIG_PATH` does not help | `export CPATH=/opt/homebrew/include LIBRARY_PATH=/opt/homebrew/lib`, or put `/opt/homebrew/bin` before devkitPro in `PATH` | — |
| `make: invalid option -- O` | `make --version` → 3.81 | macOS make has no `--output-sync`; CI's commands use `-O` | drop `-O`, or install GNU make 4 (`gmake`) | — |
| `fatal: no git history found` before anything builds | `git rev-parse --is-inside-work-tree` | `check_history.sh:28-34` refuses a tree that is not a git work tree | build from a clone or worktree; for a `git archive` export, `touch .histignore` | — |
| Emerald gets built; `.map_version` says `emerald` | `cat .map_version` | `make hns check` / `make hns <file>`: `Makefile:21` compares the whole goal list with `hns` | `make check BUILD=hns`, `make BUILD=hns <target>`; then `make hns` | — |
| `gSaveBlock3Ptr` undeclared in `fake_rtc.h` during `make check` (also at the upstream tag) | build log | `test/test_runner.c` included `fake_rtc.h` before `global.h` | include `global.h` first; the English worktree needs the same edit | `49adf9cc99`, `70df00d417` |
| Release SHA-1 differs from `SHA1SUMS` | `arm-none-eabi-gcc --version` | another toolchain (CI's Ubuntu arm-none-eabi-gcc 14.2, another devkitARM) | build with devkitARM r68 / GCC 16.1.0 in a clean worktree of the named commit | — |
| `gbafix.log` says `HEADER CHANGED` | `gbafix.log` | the build did not fix the header | investigate before releasing; never seen so far | — |
| Harness stops working months later | `otool -L $HNS_RUNNER` (`@rpath/libmgba...`) | the runner's rpath points at a deleted mGBA build | build mGBA in a permanent folder and rebuild `hnsrun`, or set `HNS_RUNNER` | — |
| Text breaks the compile (seen in the Spanish fork, not here) | the compiler error line | an ASCII `"` in a C literal or `\"` in `.string`; a name longer than its fixed array (GCC 16: `excess elements in array initializer` for a species over 12 or an item over 19 letters; a move name has no compile-time limit) | the charmap's `”`; `checkunits.py` / `namecheck.py` enforce byte limits before a build | — |
| `make check` stops at `src/braille_puzzles.c:379` (`FLAG_RECEIVED_TOGEPI_EGG`) | the make command | plain `make check` builds the Emerald tests | `make check BUILD=hns` | — |

### 6.2 Static checks

| Symptom | Check | Cause | Fix | Commit |
| --- | --- | --- | --- | --- |
| drift `E STRUCTURE changed outside strings` | the `-`/`+` lines in the output | an edit outside a string; a raw `"` inside `.string` (also gives `string count 15 -> 14`); an engine commit missing from `he/renderer`, or a stale `../pokehns-heb-engine` | revert it; write `”`; cherry-pick the engine commit onto `he/renderer` and update that worktree | — |
| drift `STRUCTURE label order A vs B` | | blocks moved or merged | restore the English block order | — |
| drift `E TOKENS <label>: ['{PLAYER}'] -> []` | | a placeholder was dropped or reordered | keep English order. Droppable: `{POKE} {PKMN} {POKEBLOCK} {ID} {NO} {PK}`; `{B_BUFF1..3}` may swap with each other | `43e43941b4`, `dbf3d07e01`, `43acd4d4e3` |
| drift `E TERMINATOR`, `E CHARSET <label>: €`, `SHRUNK` | | `$` lost or added; a character the charmap cannot encode; the file is under 60% of the English bytes | restore the `$`; use the charmap form; restore the file | — |
| drift `w PAGES 2 -> 1`, `w LATIN`, `w UNTRANSLATED` | | warnings only | `\p` changes only when a page would not fit; translate the Latin or confirm it is on `LATIN_OK` (`drift.py:52-62`) | — |
| drift flattened `#if/#else` string branches | | an old drift could not parse literals split by preprocessor lines | translate every branch; drift parses them now | `98e5af4a55` (parser), `c3aa635b6a` (text restored) |
| drift `STRUCTURE` on `src/data/pokemon/pokedex_orders.h` only | `git log he/renderer -- src/data/pokemon/pokedex_orders.h` | the regenerated A–Z order is engine data and is not on `he/renderer` yet | cherry-pick the `pokedex_orders.h` commit onto `he/renderer` | `f47c725548` (on `he/renderer`) |
| audit `E ... WIDTH 278 > 200 ... (prompt line)` | `textwidth.py` | the line is too wide; a line ending in `\l`/`\p` gets 200 px | `wrap.py`, or shorter wording | `57ba9f052e` (prompt budget) |
| audit or checkunits `BYTES` | `namecheck.py --all` | a hard field limit; for example the Frontier trainer name field is 7 bytes, not 8 | a shorter form for that copy | `ca1e85587c` |
| audit `FIT` warning | | fits only in the narrower fallback font | allowed; look at it on screen | — |
| checkunits `w DIGITS ['20'] -> ['02']` | | a number reversed or lost | write digits in reading order | — |
| namecheck `WARN FRSYNC`, `TRANSLIT`, `SAMENAME` or `STALE` | `namecheck.py --warnings` | a name differs from FireRed's current one, a transliteration slip, one person with two spellings, or an allow entry that no longer matches | fix the name if it is an error (Q136); otherwise add or update its entry, with the reason, in `tools/hebrew/data/namecheck_allow.json` | `49394ba1ad` |
| `gen_dex_alpha`, `gen_ec_order`, `gen_ec_letters` or `flag_gates` `--check` exits 1 | the entries it lists | a rename or a script change without regenerating | run the tool without `--check` and commit its output alone | `c022422009` |
| A glossary name went back to Latin; a row vanished | diff the row keys (below) | a bulk rewrite of `glossary.csv` dropped rows: `bb8db5c703` lost 5 (four radio DJs and `TERM_NURSE_JOY`) | restore the rows; review every bulk glossary edit with the key diff | `d8de0c8fd0` |
| 8 multi-word names held only the first word | read the row | truncation during a rewrite (which commit is unknown) | restored in the names review | `DECISIONS.md:1361-1382` |
| STATUS.md undercounts, units vanish | `units.py status FILE` | `units.py` skipped any string without a Latin letter | fixed; regenerate STATUS.md with `--sweep` | `29170c3421`, `4a9c6858b1` |
| A unit cut short | | a blank line inside a `.string` block | remove the blank line | `b81dddd2b3` |
| Chunk pre-fill offers a name inside a longer name (PASS in FRONTIER PASS) | | substring match | fixed | `4e2fc2ed56` |

Row-key diff for `glossary.csv`. Use it after any bulk edit; in zsh, quote `"${rev}:path"`:

```bash
python3 - <<'EOF'
import csv, io, subprocess
def keys(rev):
    t = subprocess.run(['git','show',rev+':translation/hebrew/glossary.csv'],capture_output=True,text=True,check=True).stdout
    return {(r[0],r[1]) for r in csv.reader(io.StringIO(t)) if len(r)>1}
a, b = keys('OLD'), keys('NEW')
print('lost:', sorted(a-b)); print('added:', len(b-a))
EOF
```

### 6.3 Test suite and CI

| Symptom | Check | Cause | Fix | Commit |
| --- | --- | --- | --- | --- |
| `make check` ends in `Segmentation fault: 11` and prints no summary (macOS) | `check_tests.py LOG` | the hydra summary lists written past their 1,600 rows (section 4.3); only in trees without the guard | judge with `check_tests.py`; build from `he/main` `08027d9879` or later | `8d52b4cccf` (merged in `08027d9879`) |
| CI `check` killed: exit code 143, "The runner has received a shutdown signal" | `gh run view <id> --log-failed`; the `[mon]` lines | test build at `-j4` exhausted the runner; then memory grew over one long run; then one test spins the Linux emulator (about 1.2 GB a minute) | `-j2`; a separate test-ELF step with a resource log; `check_chunked.py`; `--skip-crashing` and `--chunk-timeout 900` | `77250f4224`, `d04ba18ed2`, `7cf1c4771e`, `8714ee20ef` |
| later tests in a chunk do not run after a crash | | after a crash the runner rebuilds its share of tests without the name filter (`check_chunked.py:10-14`) | each crashing test gets its own chunk; list new crashers in `crashing_tests.txt` | `7cf1c4771e` |
| `check_chunked.py` exits 3 / 2 | `== TIMEOUT` in the log / the message | a chunk ran past the timeout / no test ELF, or a crashing name missing from `test/` | look at that chunk; `make BUILD=hns pokehns-test.elf`; fix the list | — |
| `NEW FAILURE: <battle test>` | the test's expected `MESSAGE` | that battle string's Hebrew changed | rebuild `test/hebrew_battle_messages.h` (`tools/hebrew/testmsgs/README.md`) | `310277816e` |
| bag A–Z sort tests fail | | the order is Hebrew; berries all start with `פרי` | update `test/bag.c` after renaming items or berries | `903ce11705`, `4c6ba54599` |
| 181 battle tests fail only in Hebrew | | the tests expect English messages | the message table | `310277816e` |
| `check_tests.py`: `no test results` | `wc -l LOG` | an empty log, or the wrong file | re-run | — |

### 6.4 Harness

| Symptom | Check | Cause | Fix |
| --- | --- | --- | --- |
| `no runner at ...: build emu/hnsrun.c (emu/README.md) or set HNS_RUNNER` | `ls tools/hebrew/emu/hnsrun` | the runner is git-ignored and not built | build it, or set `HNS_RUNNER` |
| `the save ladder is not set (HNS_SAVES)` | `python3 tools/hebrew/paths.py` | no default for the saves | set `HNS_SAVES` to `<builds>/saves` (section 2.6) |
| tour `ERROR ... constant SPECIES_TYPHLOSION not found in <dir>/include` | where the ROM is | the ROM was copied out of its source tree | set `HNS_SRC=<tree>`, or use the in-tree ROM (the release script does) |
| `path too long for hnsrun (N chars)` | the length of OUTDIR | hnsrun keeps 127 characters (`hnsrun.c:200`); `sweep.py:391-396` guards at 120 | `cd` to a short folder; the sweep passes relative paths when shorter |
| `sweep: no script units in .../build/hebrew/units`, exit 2 | `ls $HNS_UNITS` | no units | `python3 tools/hebrew/make_chunks.py all` |
| `selftest: no label with Hebrew letters and a long enough two-row page` | | the ROM is not the Hebrew build, or `--label` names a label with no two-row Hebrew page | use the Hebrew clip ROM; pick another label |
| `sweep: no unit has Hebrew; use --hebrew-only`, exit 2 | | `--translated` keeps units that hold Hebrew, and `make_chunks.py` units come from the English baseline and hold none | use `--hebrew-only` |
| tour `ERROR ... <file>:<name> matches 0 symbols` | is there a `.map` next to the ROM's ELF? | `FILE:NAME` symbols come from the linker map (`hns.py:176-209`); the folders of rc21 and earlier keep `pokehns-clip.gba` and `.elf` but no `pokehns-clip.map`; `build_release.sh` copies it since round 19 | run the ROM in its build tree (the release worktree, as `run_release_tests.sh` does), or copy the `.map` next to it |
| `--clip`: `... is not an RTL_CLIP_REPORT build` | | a release ROM | use `pokehns-clip.gba` |
| `selfcheck` prints FAIL | | a saved struct changed size (`include/global.h`, `main.h`) | `HNS_WORK=<scratch> bash tools/hebrew/emu/probe/measure.sh`, update `OFF`/`SIZES` in `hns.py`. It also misses a field reordered inside an unchanged size, so rerun the probe after any change to those headers |
| `render`: `'waitcb2' needs hns.py run (not plain hnsrun)` | | a live op in a script for bare hnsrun | use `hns.py run` |
| tour TIMEOUT or CRASH | `OUT/TOUR/_timeout.png`, `_crash.png`, `run.log`; `hns.py where <pc>` | a wait never matched; a bad pointer | fix the script or the ROM |
| tour OK, but frames differ from the previous candidate | `hns.py tourdiff` | a stale script, or a real change | look at each DIFF (section 4.5) |
| savestate gives plausible nonsense | | `ss`/`sl` states work for the same build only (`hnsrun.c:23`) | cold-boot from the battery `.sav` after a rebuild |
| values read from the save block are wrong after a warp | | the save block moves on every map load and battle | use `@SB1@`/`@SB2@`/`@POS@`, which are re-read per line; never cache them |
| a battle differs between runs | | input timing moves `Random()` | `pinrng` (`hns.py:1500-1539`) |
| map walk `HELD` | the same map on the English ROM | a scripted sequence the B-only walker cannot finish | a harness limit unless English behaves differently |
| ladder1 validation exits 1 (`leavecenter: blocked inside 1.4`) | which script ran | `ladder_validate.txt` leaves a Center; rung 1 is the bedroom | validate rung 1 with `ladder_validate_newgame.txt` (`run_release_tests.sh` does) |
| `rom_sweep.py` exits 1 with about 6,255 runs | | dead Emerald text compiled in | informational; diff against the previous candidate |
| cross-core: VBA-Next differs on whole frames (no RTC); SkyEmu exit 139 | `crosscore` log | an old frontend that answered core options with NULL | use the frontend `run_release_tests.sh` builds from `crosscore.c` (it answers with the defaults) |
| a tester reports a "crash" | does the screen show an assert message? | `make hns` keeps asserts (`RELEASE ?= 0`, `Makefile:69`); the ROM contains `AssertfCrashScreen` | read the assert. R+START (the debug menu) is compiled in (`include/config/debug.h`); R is also the DexNav button |

### 6.5 On screen: clipped, misplaced or misordered text

| Symptom | Check | Cause | Fix | Commit |
| --- | --- | --- | --- | --- |
| letters missing at the left end of a line (reads like a typo) | clip build + `hns.py tour --clip` or `sweep.py` | the line is wider than its window; whole glyphs past the edge are not drawn (`src/text.c:1401-1421`) | shorten or re-wrap; measure in the screen's own font before cutting | `a3615d7dd3`, `47790b34d0`, `1056f5075f` |
| text off its box art, although it fits the window | `git grep -n 'SetWindowRtlMirrorWidth' -- src` | the mirror axis is the window width, but the art is narrower | `SetWindowRtlMirrorWidth(id, px)` (`src/window.c:46`) | `aba432739a`, `d02bbbb543`, `108a0ef3f1`, `c9f132be4c`, `a459a5995e` |
| text, cursor or icon on the wrong side; text over sprites or fixed art | `git grep -n 'SetWindowRtlMode' -- src` (44 calls in 13 files) | the wrong window mode. The mode resets on `AddWindow` and friends | `WINDOW_RTL_IN_PLACE` for text on fixed art, partly copied windows and tilemap cursors; set it right after creating the window | `c9f132be4c`, `795f5d49b4`, `dc86d6f578`, `108a0ef3f1`, `809187e408`, `a4c59d59d0`, `fe52aadb6c` |
| sprite-drawn menus (mark menu, dex START menu) stay English or unmirrored | | mirroring never reaches sprites or baked tiles | place and flip under `TEXT_RTL`; redraw the tiles | `dd6fdce85b` (`040ef17c53`), `066d60d2ad` (`9f449b137c`) |
| LEFT/RIGHT move against the picture in grids and option rows | | in a mirrored window the visual direction flips | swap them in mirrored windows | `aac92d7b81`, `884af88a6d` |
| naming screen: a page swap puts the cursor on the far side (K4) | | the column was kept across a swap that crosses the Hebrew page | mirror the column (`src/naming_screen.c:863-868`) | `41d363d8ed` (`35dc418711`) |
| `ב20-` for ב-20 | | a hyphen before a digit always started a number run | a hyphen right after a Hebrew letter is the prefix hyphen | `f91641668d` (`4394a1648c`) |
| words around `{PAUSE}` or placeholders reversed; `?s nickname'TYPHLOSION` | | the run ended at the pause or placeholder bytes | runs continue over them | `a1c5d26885`, `976f20ffb7` |
| `[R] Press`, `(AUTORUN (SURF` misplaced | | an icon ended the run; brackets were mirrored inside it | icons count as Latin; a closing bracket stays with its opener | `1b4b8a2857` |
| `.21.2 kg` | | a trailing neutral period goes to the far end | period dropped under `TEXT_RTL`; unknown measures written unit-first | `df74d3cfae` (`5e93dbf3b3`), `b456e3a263`, `e38401e5c4` |
| healthbox name backwards | | a gender `{COLOR}` made the sprite reorder give up (`src/text.c:1518-1521`) | colours travel with their glyphs | `c34d22d99f` |
| HP `56/` + `/ 56` pulled apart | | in-place mirroring of a segment with no Hebrew | such segments keep the English layout | `d6ed5b874c` |
| `פוקיבולs`; berry name eaten in a shop | | English grammar in C (a plural `s`; cutting the last 6 bytes) | singular under `TEXT_RTL`; drop the first word instead | `578a2e5181` (`655c46a6dc`), `18af1160af` (`2d02edb827`) |
| two items overlap inside a window; a descender on a frame | `pairsheets.py` against English | the clip report cannot see it | case by case; examples: dex evolution pitch, PP label, status tags | `dec6f549ed`, `bcc1012ed3`, `fdbf0d552c`, `60c357ee10`, `aedb9c43e3`, `072ad4c245`, `40279b7f5f` (`9e9e82ab14`) |
| a new Hebrew glyph prints blank in a narrow font | `python3 tools/hebrew/fontcells.py . 3A 50 87` | the glyph is missing in one of the nine fonts | add it to every font | `6fa10945bb` |
| English labels in art while strings are Hebrew | | the labels are baked into PNGs | redraw them; tiles shared between phrases need re-allocation | `a575d03ca5`, `d93afb1f02` (`b867e6e02e`) |

### 6.6 Saves

- **2.0.x English saves load in the Hebrew ROM.** The translation changes no saved struct:
  SaveBlock1 is 0x3D90 and SaveBlock2 0xF34 in both ELFs (`hns.py selfcheck`). Keep it that way:
  never widen a `*_NAME_LENGTH` or any buffer in a saved struct.
- **Hebrew-written saves load in the English ROM** (section 4.6): a new-game save in the bedroom,
  and mid-game and post-game saves made in a Pokémon Center. A Hebrew player name shows blank
  there. A save made on a Battle Pyramid or Trainer Hill floor was not tried (**unverified**).
- **Pre-2.0 (1.2.1) saves do not load.** The sector layout differs (SaveBlock3), and 2.0.6
  migrates only 2.0.x saves (`src/save.c:930-980`). This comes from a code trace in
  `<builds>/archive/rounds/save12/REPORT.md`; no 1.2.1 save was ever loaded (**unverified**).
- **Leave the Pokémon Center first** after loading a save from another build. This is the
  official upgrade step; see `tools/hebrew/emu/scripts/continue.txt:5-7`.

---

## 7. Rules and conventions

### 7.1 Commits

- **One file per text commit.** 1,214 of the 1,368 non-merge commits on `he/main` (at `85705e4bc9`)
  touch one file.
  Subjects:
  - "Translate `<file>` into Hebrew";
  - "Apply the review decisions to `<file>`";
  - a one-line reason, such as `1f0316735a` "Make the boy ask MIMI to be his friend, not his
    girlfriend".
- **Engine and text never share a commit.** Engine work is reviewed against screenshots, text
  against the English.
- **Glossary rows land before the dialogue that uses them**, in their own commit. Four commits
  broke this (`6cb6003de9`, `3aaedfe560`, `5a5d14a16b`, `3059edf098`); do not follow them.
- **Engine and graphics commits are cherry-picked onto `he/renderer`; text commits never are.**
  Check with `git cherry -v he/main he/renderer`.
- **Messages** say what and why, never ticket IDs or history. Code comments say what and why.
  Anything not seen on screen is marked unverified, in the commit, the docs and the release notes.
- **No AI attribution**: no `Co-Authored-By` trailer, no "Generated with" line. All 1,407 commits
  on `he/main` follow this.

### 7.2 Identity

- Every commit on `he/main` is authored with the fork owner's GitHub **noreply** address. Check
  with `git log -1 --format='%ae' he/main`.
- Set it in the clone's local config (`git config user.email ...`) before the first commit,
  because a machine's global identity may be a different account.
- The same applies to the builds repository.

### 7.3 Pushing

- **With the fork as `origin`** (a fresh clone), push `he/renderer` first if it changed, then the
  feature branch and `he/main`.
- **On the reference machine** `origin` is upstream, and the global git config rewrites HTTPS to
  SSH with a different account's key. A plain push fails or goes to the wrong account. Push to an
  explicit URL with the fork owner's `gh` token, bypassing the global config, and **never write
  the token into a file or a remote URL**:

  ```bash
  T=$(gh auth token -u <fork-owner-account>) && GIT_CONFIG_GLOBAL=/dev/null git \
    -c credential.helper= \
    -c credential.helper="!f(){ echo username=<fork-owner-account>; echo password=$T; }; f" \
    push https://github.com/ronyeh2/pokehns-expansion-heb.git he/renderer he/main
  ```

  The same pattern pushes the builds repository (`.../pokehns-hebrew-builds.git main`).
- Check the result with
  `GIT_CONFIG_GLOBAL=/dev/null git ls-remote https://github.com/ronyeh2/pokehns-expansion-heb.git`.

### 7.4 Stop and ask the owner first

Ask the owner before you:

- rename or delete a pushed branch;
- close or recreate a pull request, or open one upstream;
- rewrite pushed history;
- change a gameplay constant;
- make a style call that neither the decisions nor the glossary covers;
- make a ROM or the builds repository public.

### 7.5 Branch workflow

- One topic per branch (`he/fix-<topic>`), in its own worktree (`../pokehns-heb-<topic>`).
- Merge into `he/main` with `git merge --no-ff he/fix-<topic> -m "Merge he/fix-<topic>: <what>"`.
  `he/main` has 39 such merges.
- Keep `master` identical to upstream. Keep upstream bug fixes on `he/upstream-fixes`, separate
  from text and engine work (`00dd646cc1`, `4d5d2b9ada`).
- Before touching an engine function, `git log -S` it upstream to see why it looks the way it
  does.
- Keep every diagnostic behind a config switch (like `RTL_CLIP_REPORT`), so that the release ROM
  is free of it.

---

## 8. Open, stale and unverified

### 8.1 Open defects in the repository

| Item | Evidence | What to do |
| --- | --- | --- |
| **The Pokéblock case list would cut the first digit of a three-digit level.** English shows `Lv255` in full; play most likely never makes such a level | `PutPokeblockListMenuString` (`src/pokeblock.c:750-761`) skips to x 87 and prints `Lv` and the level in the 112 px list window (`WIN_LIST`, 14 tiles, `:322-330`), in the narrow font. Mirrored, the first digit of a three-digit level starts 3 px past the left edge: the clip ROM logs the `2` of a level-255 test block cut on the case list of `tours/r19_fix/pb_feed_graph.txt` (window 1, 112 px, font 7). By code reading, play needs a top speed of about 230 RPM to get there. Only the Berry Blender makes Pokéblocks (`AddPokeblock`, `src/berry_blender.c:3586`), and every H&S blend is with NPCs: the link blender runs only from Emerald's `LilycoveCity_ContestLobby` (`data/maps/LilycoveCity_ContestLobby/map.json:391`, `game_version` emerald), which this build leaves out. The level is the highest flavour (`src/pokeblock.c:1335-1348`), and a repeated berry gives a black block (`src/berry_blender.c:2274-2282`). With the NPCs' berries (`SetOpponentsBerryData`, `:1531-1569`; the Blend Master's for one opponent, since his hide flag is 0, `include/constants/flags_hns.h:1927`) the best blend is an Enigma Berry against the Blend Master: 59 before the speed factor of (max RPM / 333 + 100) % (`:2428`), so level 100 needs 229.77 RPM. A frame model of a perfect two-player blend (a BEST hit at every chance; `:1983-1997`, `:2028-2055`, `:2096-2115`, `:3287-3295`) peaks at 197.64 RPM, level 94 (`<private>/scratch/screens/r19/review/pbspeed.py`, `pbbound.py`). A real blend was not measured (**unverified**) | measure a perfect blend against the Blend Master with an Enigma Berry (`sBerryBlender->maxRPM`). If it can pass 229.77 RPM, place the level so `Lv` and three digits fit inside the window, check it with the tour's level-255 block, and cherry-pick the fix onto `he/renderer` if it is engine code |
| **`he/renderer` still has the old Pokéblock condition graph.** `946ae2f132` (on `he/wip-r19`) re-ran `tools/hebrew/graphics/side/do_graph.py` on `graphics/pokeblock/use_screen/graph.png` (blob `5e88e5b3` → `398c66e3`, 449 pixels in the label rows). The panel now equals the Pokégear one cell for cell | on the feeding screen, rc21's ק of קשיחות and left י of יופי are 1 px from the pentagon outline; with the new art 3 px and 4 px, at conditions 0 and 255. Only those label rows change on screen (`tours/r19_fix/pb_feed_graph.txt`, run with `scripts/r16_contests/con16.py`) | cherry-pick `946ae2f132` onto `he/renderer`. It has the same old blob `5e88e5b3` and the same Pokégear graph (`884f98a9`), so it should apply cleanly. Push `he/renderer` before `he/main` |
| The harness shoots the battle debug menu's AI party page before its tilemap reaches the screen, so later six-Pokémon pages look blank (section 8.5) | `scripts/r16_debug_menu/dbgmenu.py` `view()` (`:95-103`) shoots 8 frames after the page's task starts and closes it at once; the page's tilemap copy lands about 22 frames late | wait until `sDma3Requests` has no pending entry, or at least 30 frames, before the shot and before B; then drop the one-page-per-run note in its docstring (`:18-21`) |
| `audit.py` on a built tree counts 2,480 more strings than CI (section 4.2) | `walk_tree` (`audit.py:448-464`) also reads the six generated headers | skip `src/data/trainers*.h`, `battle_partners.h`, `debug_trainers.h` and `region_map/region_map_entries.h` in `walk_tree`; the local count should then equal CI's (39,059 at `fe509e0043`) |

### 8.2 Content gaps and decisions

- **Latin left inside Hebrew strings.** The live ones have glossary rows and Hebrew text. drift
  prints 127 `w LATIN` lines, and each is either kept on purpose or in text H&S does not reach:
  - kept: button names, game titles, the credits' team names, the abbreviation IV in the help
    windows (`src/data/help_window.h`), the Odd Egg name list the game compares with the player's
    name, and the save-type name on the no-flash screen; the reasons are in
    `tools/hebrew/status_report.py` (KEPT_LATIN) and `tools/hebrew/drift.py` (LATIN_OK);
  - unreachable: Emerald maps and names, the Battle Tents, the TV shows and their PokéNews
    (`FLAG_SYS_TV_START` is defined as 0, `data/scripts/tv.inc:8`), the PokéNav match calls (their
    `FLAG_ENABLE_*_MATCH_CALL` and `FLAG_REGISTERED_*` flags are defined as 0 in
    `include/constants/flags_hns.h`, and `FlagGet(0)` is false), the Ruby/Sapphire berry fix,
    and the item descriptions this build does not compile.
  - `tools/hebrew/flag_gates.py` keeps these out of `tools/hebrew/data/live_labels.json`: it moves
    the match calls (all but Mom and Baoba), the TV shows and PokéNews to `flag_off` (451 labels)
    and the 147 labels that are not built to `not_built`; 6,585 stay live. CI runs `--check`.
- **Easy Chat is Hebrew** (`DECISIONS.md` Q135). All 999 words have Hebrew texts; the words the game
  compares (the Odd Egg passwords, the questionnaire's Mystery Gift phrase) each print a text of
  their own; the group lists follow the Hebrew order; the ABC keyboard shows the 22 letters and
  אחר; and the screen mirrors inside its frames, which fixed round 16's three layout faults (the
  word-select cursor on the other column, the group keyboard hiding a column, the YES/NO box over
  the phrase). Only phrases from a linked game were not seen.
- **Decided in round 18:** the battle debug menu's stat rows and label (Q131), the link battle lines
  without the player's gender (Q132), the five Pokédex terms (Q133; their rows stay `proposed`),
  'psychic power' as כוח פסיכי (Q134), the Gen 4 FROSTBITE tag redrawn as קור (Q137), the names
  compared with FireRed's (Q136) and publishing without hand play (Q138).
- **Faults of H&S 2.0.6 itself, the same in English, listed as known issues** in `notes.json`,
  because any fix changes gameplay or belongs upstream (section 7.4):
  - **Battle Dome style scoring** assigns instead of adding, so a trainer card shows only three of
    the style descriptions (`src/battle_dome.c:882`, `:887`, `:909`).
  - **Scott's Silver and Gold Shields** cannot be received: H&S has no ornament inventory
    (`include/decoration.h:30-52`, `src/decoration_inventory.c:6`), so `GetFirstEmptyDecorSlot(3)`
    reads past the array, finds 0 and the script always says "come back for this later"
    (`BattleFrontier_ScottsHouse_hns/scripts.inc:99-106`).
  - **No flash chip:** `textWin[]` in `src/save_failed_screen.c:417-428` has no
    `DUMMY_WIN_TEMPLATE` terminator, so `InitWindows` reads the next ROM object and an allocation
    assert shows the blue English screen before the Hebrew no-flash message (upstream `ad0778722b`).
    It shows because `make hns` is not a `RELEASE` build (`include/assertf.h:70-77`); 1.0 stays a
    plain build (below).
  - **Battle Pike poison white-out** with SURVIVE POISON (הישרדות מרעל) off crashes. The HNS build
    gives every map whose `game_version` is not `hns` a NULL header
    (`tools/mapjson/mapjson.cpp:712-733`, `:470-479`), `src/overworld.c:684-687` returns it
    unchecked, and the white-out runs the Emerald retire script (`data/scripts/field_poison.inc:27-32`,
    `data/scripts/battle_pike.inc:222-226`), which warps to the Emerald Pike lobby. The option is
    on by default (`src/challenge_menu.c:1364`). A scan of the warps found no walkable warp from an
    H&S map to an Emerald map except the unreachable Artisan Cave ones.
  - **Birth Island:** YES to the sailor warps to `MAP_LILYCOVE_CITY_HARBOR`
    (`data/maps/BirthIsland_Harbor_hns/scripts.inc:17`), an Emerald map with the same NULL header,
    and the game hangs on a black screen. Leaving with Fly works on both ROMs: the player lands in
    Cherrygrove City and can move (`tools/hebrew/emu/tours/r16_emerald_leak/eld2_birth_island_fly.txt`).
  - Not run, as it needs a real link: the Battle Frontier Pokémon Center's link rooms warp to the
    Emerald colosseum, trade and record rooms, NULL in this build (Goldenrod uses the `_hns`
    rooms); English is the same.
- **The build type stays plain `make hns`** (decided by evidence in round 19; section 2.5 has the
  builds). A `RELEASE=1` build of the English source was made and compared:
  - **The no-flash blue screen goes.** Seen on screen with `scripts/r16_field_odds/noflash.py`
    and `tours/r16_field_odds/fo_flash.txt` on the English builds: the plain build
    shows the blue `SRC/MALLOC.C:104 ... OUT OF MEMORY TRYING TO ALLOCATE 46848 BYTES` screen
    first, and the release build (without LTO) shows the no-flash message at once. Every other
    assert screen goes too (`AssertfCrashScreen` is not in the release ELF), while the code after
    each assert still runs.
  - **The debug menus stay.** The three switches are literal `TRUE`
    (`include/config/debug.h:5`, `:11`, `:15`, the same in 2.0.6 and `he/main`), not
    `DISABLED_ON_RELEASE`. Both release ELFs still hold `CB2_BattleDebugMenu`, and the one without
    LTO also `Debug_ShowMainMenu`. Q120 does not depend on the build type.
  - **Debug output goes.** `NDEBUG` (`include/config/general.h:11-12`) turns off mGBA print and
    the allocation location strings. LTO, on by default (`config.mk:2`), lays out all code
    differently.
  - **No gameplay change was found.** `I_SHOW_NO_ID_TRAINER` flips (`include/config/item.h:41`),
    but only the VS Seeker reads it (`src/vs_seeker.c:417`), and the VS Seeker is off
    (`item.h:40`). This is from reading the code.
  - **Why plain:** the official build type is not established and leans plain (section 2.5). A
    release build would void every test of rc21, which all ran on plain builds. And testers
    benefit from the assert screens (section 6.4). Revisit only if the decisive test of section
    2.5 finds no assert strings in the official ROM. Then build with `make hns RELEASE=1` (LTO on,
    as upstream's `release` target) and run every release test again.
- **Ariana's class** מנהל רוקט stays masculine: the class is shared with Archer, Proton, Petrel and
  Giovanni and is printed before the name, so no text-only form fits (Q124, Q127; a known issue).
- **The radio's Pokédex Show** wraps two place names across its lines (הר / הנזר in the
  Typhlosion-H entry, נהרות / היסואי in Basculegion's). Accepted: the ticker breaks between words,
  nothing clips, and 1.0 and English split at the same places.
- **Proposed names.** The 5,152 `proposed` glossary rows were never checked against an official
  Hebrew source. `namecheck.py --warnings` checks them for consistency with FireRed and for
  transliteration slips (Q136); the roughly 3,000 rows translated by meaning stay `proposed` until
  a native speaker reads them.
- **Not seen by a person:**
  - nobody has played from a new game to the first badge;
  - nothing has run on real hardware (needs a 32 MiB cart, FLASH 128 KB save and an RTC);
  - no real 2.0.x save from a long playthrough, and no 1.2.1 save, has been loaded;
  - a real link with a second GBA was never tried; the trade screen, link battles, the cable
    club, record mixing and Mystery Gift were seen with the partner faked in memory
    (`tours/r14_link`, `tours/r16_link`);
  - the Battle Frontier facilities, full contests, the Trainer Hill, the Battle Tents, mail, the
    credits, the Hall of Fame and the Pokédex form pages were seen in the rounds' own tours
    (`tools/hebrew/emu/tours/<round>/`), which the release does not run again. Re-run the matching
    round tour whenever a change touches those screens;
  - no native speaker has read the text on screen.
- **Unreachable English in the ROM** (resolved). `rom_sweep` lists 104 untracked English runs
  sourced to `BattleFrontier_BattlePyramidFloor_hns`. None can print: its 129 text labels have no
  referrer outside their own definitions, `tools/hebrew/data/inventory.json` marks the file dead,
  and the Pyramid's live text comes from `src/battle_pyramid.c` and `src/start_menu.c`, which are
  Hebrew.
- **The battle debug menu's AI party page cuts its last column** (an English 2.0.6 limit, kept).
  Column i starts at x = i × 41 (`src/battle_debug.c:976-978`), so column 6 starts at x 205 of the
  232 px window and its 7-byte hold-effect copies run past the edge: Hebrew loses the מ' of
  התק' מ' and the מ of רצועת מ, English shows 'Sp Att' for 'Sp Atta'. The clip build records these
  glyphs. Debug-only; no change.

### 8.3 Stale documentation

None known at the end of round 19. Round 19 corrected six line references: `RELEASE ?= 0` is at
`Makefile:69`, `KEPT_LATIN` at `status_report.py:22-48`, the Hebrew count at
`status_report.py:82`, the sweep's path guard at `sweep.py:391-396`, `walk_tree` at
`audit.py:448-464` and `LoadSaveblockObjEventScripts` at `src/overworld.c:592-600`. Every text
tool has tests: 137 tests in 21 files under `tools/hebrew/tests`, with small committed fixtures
in `tools/hebrew/tests/data/`. Add a row here when a document and the tree disagree, and fix it
in a docs-only commit.

### 8.4 Things only on the reference machine

None that the release needs. `<builds>` holds the saves (`saves/`, `HNS_SAVES`), the libretro cores
(`reference/cores/`, with SHA-1 and inferred source), the English map walk
(`reference/mapwalk_en.json`, `HNS_EN_MAPWALK`), each candidate's records (`records/rcNN/`, indexed
by `records/README.md`) and, as history only, the old unit chunks, the pre-fork translation drafts,
the October notes and the round reports (`archive/`). The fork holds every tool, including the
graphics scripts (`tools/hebrew/graphics/`), the font designs and installer (`tools/hebrew/fonts/`)
and the inventory builder (`tools/hebrew/inventory/`).

Rebuilt, never stored: mGBA 0.10.5 and `hnsrun`, `crosscore`, RetroArch's mGBA core, the unit
chunks (`make_chunks.py all`), the English tour run, and any candidate's ROM, ELF and map (build
its commit with devkitARM r68 and compare the SHA-1 in `records/README.md`). Regenerable and still
only local: the latest candidate's tour screenshots (the next `tourdiff` compares against them)
and the round screenshots. Freeing that disk is the owner's call.

### 8.5 Facts verified and not verified

**Verified in round 18:**

- A fresh clone, followed through section 2.3 on the reference machine, rebuilt 0.2 byte for byte
  ("Notes from the fresh-clone test"). CI builds and tests on Linux (ubuntu-26.04, Ubuntu's
  toolchain).
- The hydra segfault's cause, and the guard `8d52b4cccf` (section 4.3), now merged into `he/main`
  (`08027d9879`). The 0.2 and rc20 `make_check.log` came from `make check BUILD=hns -j12` (the
  release README), with 15 hydra runners, in about 4 min.
- Every libretro core loads the 131088-byte `.sav` at the frontend level (section 4.6); copies of
  the cores are in `<builds>/reference/cores/`, whose source is inferred, not recorded.
- 69 of the 71 tours run on the English ROM; the two `naming_*` tours are Hebrew-only.
- A pull request into `he/main` runs only the Hebrew workflow; the ubuntu-26.04 image builds and
  tests.
- GCC 16 rejects a species over 12 or an item over 19 letters; move names have no compile-time
  limit (section 3.3).
- `he/fix-screens` is merged into `he/main`.
- The Hebrew A–Z Pokédex order is regenerated and was seen on screen; the imperial height was
  fixed in `196a1bdc71` and seen in round 5.
- A Hebrew-written bedroom save loads in the English ROM, with the Hebrew name blank (section 4.6).
- The 27 evolution-page sheets of round 16b that nobody had viewed (269 pages) were viewed: no
  clipped line and no line touching a border; the closest is 2 px above the bottom border
  (Milcery/Alcremie). Kingambit's wrapped line on the Pawniard and Bisharp pages touches the line
  above at 3 pixel columns, where English touches at 2 with the same spacing: the game's layout,
  not a translation defect.
- Leaving Birth Island with Fly works on both ROMs (section 8.2).
- `make_chunks.py all` on this tree gives the sweep 6,611 labels (section 2.6), and the static steps
  of the worked example in section 3.4 (`textwidth.py`, `wrap.py`, `make_chunks.py B21`,
  `checkunits.py`, `drift.py`, `audit.py`) print the outputs shown there.

**Verified in round 19** (on rc21, the current 1.0, unless a line says otherwise; scripts, logs
and screenshots that are not in the fork are under `<private>/scratch/screens/r19/`):

- **Hebrew-written mid-game and post-game saves load in the English ROM** and show the same
  screens as English-written saves of the same moment (section 4.6).
- **The sweep skips nothing.** With units made again by `make_chunks.py all`, rc21's clip ROM gives
  6,611 labels, all OK, 0 SKIP and 0 CLIP, in 150.3 s (section 4.5).
- **The two name fixes of Q136 are on screen,** with 0 clipped glyphs in a 15-shot tour on the clip
  ROM (`emu-facts/t2/tours/q136_names.txt`), next to English:
  - SONIC BOOM is `בום על-קולי`, in full, in the battle fight menu, its START move-info window and
    the summary's BATTLE MOVES page, with its description;
  - EARLY BIRD is `ציפור מקדימה`, with `מתעורר מהר משינה.`, in the ABILITY box of the summary's
    INFO page. In H&S the SKILLS page shows stats only.
- **`make_ladder.sh` rebuilds the stored ladder byte for byte,** with the time-zone condition of
  section 2.6.
- **The Pokéblock feeding screen's condition graph:** on rc21 two labels are 1 px from the pentagon
  outline; the art of `946ae2f132` moves them to 3 px and 4 px, and nothing else on screen changes
  (section 8.1; `tours/r19_fix/pb_feed_graph.txt`, run on rc21, on a build with the new art and on
  English).
- **Why the local audit counts more strings than CI:** six generated headers in a built tree; the
  findings are the same (section 4.2).
- **The official English binary:** no build type made with devkitARM r68 matches it (section 2.5),
  and a `RELEASE=1` build hides the assert screens but keeps the debug menus (section 8.2).
- **The battle debug menu's AI party page** draws its text about 22 frames after it opens. This
  was measured on the English 2.0.6 ROM; `PutAiPartyText` is the same in `he/main`. The blank
  later pages that round 16's harness showed come from the harness, not the game:
  - Each string is printed at speed 0, which copies the whole 14,848-byte window to VRAM
    (`src/text.c:538-543`). A six-Pokémon page queues 45 copy requests (`src/battle_debug.c:962-985`).
    The queue moves at most 40 KiB per frame (`src/dma3_manager.c:56`), so the window's tilemap
    lands last.
  - The harness shoots the page about 14 frames after it opens and closes it at once.
    `ClearWindowTilemap` (`src/battle_debug.c:1159`) then runs while the copies are still
    queued, and the queued tilemap copy writes a blank map for the next page.
  - A page held 30 frames shows its full text, and pages held 60 frames each all draw. The
    harness fix is in section 8.1. A one-line ROM change (`TEXT_SKIP_DRAW` in those prints)
    would make one copy, but the menu is debug-only and upstream, so it stays.
- **The branches whose commits `git cherry` does not find are contained in `he/main`** (section
  1.2).
- All 242 scripts under `tools/hebrew` compile with every warning turned into an error on Python
  3.9.6 and 3.14.7, and the 137 tool tests pass on 3.9.6, 3.11.9 and 3.14.7 (`he/wip-r19`).

**Not verified:**

- A Linux build with devkitPro pacman; another machine with devkitARM r68 reproducing the 0.2
  SHA-1.
- Whether the official English 2.0.6 binary (CRC32 `01713508`) is a `RELEASE=1` build. The
  evidence leans to a plain build, and the decisive test needs the official UPS and an Emerald base
  ROM (section 2.5). Also whether Ubuntu's apt `gcc-arm-none-eabi` reproduces it.
- RetroArch's own `.srm` loader with the 131088-byte save.
- The harness and the ladder on Linux; how the clock's hour reaches the game's random numbers
  (section 2.6).
- The state that makes the English full map walk crash in the Dome pre-battle room (section 4.6).
- A Hebrew-written save made outside a Pokémon Center, for example on a Battle Pyramid or Trainer
  Hill floor, loaded in the English ROM (section 4.6).
- Pre-2.0 (1.2.1) saves: they do not load, by a code trace only (section 6.6).
- Whether a real blend can make a Pokéblock of level 100 or more. It needs about 230 RPM against
  the Blend Master with an Enigma Berry; a frame model of a perfect blend peaks at 198 RPM, level
  94 (section 8.1).
- The out-of-bounds read behind Scott's shields could write through a stray pointer after a link
  Dodrio Berry Picking game (needs a link).
- A native speaker's read. Reviewers asked for one on: the radio's adjective pairs
  (`src/data/text/radio_strings.h:54-69`), the Ultra Beast Pokédex entries
  (`src/data/pokemon/species_info/gen_7_families.h`), the Day Care take-back question
  (`data/maps/Route34_DayCare_hns/scripts.inc:594`), Tucker's line (`DECISIONS.md` Q59) and the
  Easy Chat words.

## Notes from the fresh-clone test

This document was followed end to end on a fresh clone; the release ROM it builds matched release 0.2 byte for byte (SHA-1 `07753efc…`, clip build `4d7cfac5…`). Points to keep in mind:

- Give every `HNS_*` variable as an absolute path: a relative one is resolved against the folder a command runs from (`paths.py`). A sweep that finds no units prints `sweep: no script units in …` and exits 2.
