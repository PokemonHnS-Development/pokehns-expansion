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
| [`translation/hebrew/DECISIONS.md`](translation/hebrew/DECISIONS.md) | 76 recorded decisions, up to Q140, and the names review |
| [`translation/hebrew/transliteration_rules.md`](translation/hebrew/transliteration_rules.md) | how names are transliterated |
| [`translation/hebrew/STATUS.md`](translation/hebrew/STATUS.md) | per-file state (generated) |
| [`translation/hebrew/glossary.csv`](translation/hebrew/glossary.csv) | every name and fixed term |
| [`.github/workflows/hebrew.yml`](.github/workflows/hebrew.yml) | CI |

---

## 0. State at handoff (2026-11-10)

| Item | Value | Check |
| --- | --- | --- |
| `he/main` | the merge of round 21 (`he/fix-r21`, `8aeb3a0f2b`, the build of 1.0; on GitHub too), then the commits that point the documents and `notes.json` at the new 1.0 | `git rev-parse --short he/main` |
| `he/renderer` | `ec407862cd` (on GitHub too): `67df13ff43` plus round 21's engine commit `cd5fb48abe` (the Pokéblock case list's level column). Built in English (`TEXT_RTL` FALSE) before and after the pick, the ROM differs in 2 bytes, an assert's line number (`<private>/scratch/screens/r21/engproof/PROOF.md`) | `git rev-parse --short he/renderer` |
| Release | One release, 1.0, replaced in place on each update (ROM, `SHA1SUMS`, `TESTING.md`); the builds repo's commit history keeps the older builds. Current 1.0: built from `he/main` `8aeb3a0f2b` (rc23) | `git -C <builds> log` (`f438012` "Update 1.0 to the build of he/main 8aeb3a0f2b"); `<builds>/records/README.md:44` |
| 1.0 ROM | `pokehns-he-2.0.6-1.0.gba`: 33554432 bytes, SHA-1 `383e16ba227ae4c62ae1c1ff01bfaa0c0793eedf`, CRC32 `A6214055` (clip build `66be59802683abf1b1d69be586e38d04dc03c4bb`, CRC32 `08A267D5`) | `<builds>/SHA1SUMS` |
| Releasing | Build a candidate with `tools/hebrew/release/`, then replace the three files in the builds repo and say in the commit message which `he/main` commit it was built from; keep `tools/hebrew/release/notes.json` at `"release": "1.0"`. A candidate is published with hand play declared as not tested (`DECISIONS.md` Q138) | section 5 |
| CI | green in all three jobs at `8aeb3a0f2b` (run 42802955754) and at `c1cfd8a30b` (run 42721195219: `build` 4m46s, `audit` 1m22s, `check` 20m42s), at `dd6d82f504` (42724124742) and at `0514c9b57b` (42725640966); so were the runs before them on `he/main` (41918360015 at `85705e4bc9`, 41929345455 at `08027d9879`, 41933578987 at `fe509e0043`) | `gh run list -R ronyeh2/pokehns-expansion-heb --workflow hebrew.yml --branch he/main` |
| Static checks | at `he/main` `8aeb3a0f2b`, baseline `he/renderer` `ec407862cd`: drift 708 files, 0 FAIL, 336 with warnings only; audit 0 errors and 54 warnings, 39,059 strings as in CI; namecheck 0 problems and 0 warnings (34 allowlisted); plurals 0 problems; the Pokédex A–Z, Easy Chat and live-label generators up to date; 147 tool tests OK on Python 3.9.6, 3.11.9 and 3.14.7 at the tip | section 4.2 |
| Translation status | every live file is translated: 650 files, 525 seen on screen, 125 translated, none blocked (rc22's sweep, regenerated after round 21's C-liveness fix, with the same totals) | `translation/hebrew/STATUS.md:5` |

**What remains** (details in section 8):

1. **Declared, not doable here:** hand play from a new game to the first badge (it needs a
   person), real hardware (a 32 MiB flash cart with FLASH 128 KB and an RTC), and a read of the
   shipped wording by a native speaker. All three are in `notes.json` `not_tested`, so every
   `TESTING.md` says so; section 8.5 lists the lines reviewers flagged for a native read.
2. **Done: 1.0 is rc23, built from `8aeb3a0f2b`** (round 21 merged, its engine commit on
   `he/renderer`, all pushed; CI green). Its ROM is the one round 21 built twice, from the
   worktree and from a clean archive (SHA-1 `383e16ba…`). Against rc22: `make check` the same
   (5074 results, 1899 failing, all known upstream failures); all 2,056 tour shots and all 2,056
   clip-tour shots identical (`tourdiff`); the sweep OK for all 6,611 labels, read from units made
   into an empty folder (rc22 read 6,821 with 210 stale flag-off labels, section 4.5); the
   self-check, save ladder and map walk (507 OK, the same 36 HELD) pass; the ROM sweep finds the
   same labels; the cross-core table differs only in the start menu's clock. Records are in
   `<builds>/records/rc23/`, indexed in `<builds>/records/README.md`. Before its `TESTING.md` the
   English reference walk was replaced (`<builds>` `c10184c`: a walk of 2026-11-10 by the current
   walker, 507 OK and the same 36 HELD; command in `<private>/runs/mapwalk_en/COMMAND.txt`, the
   old walk kept as `<private>/runs/mapwalk_en_2026-10-12`) and `notes.json`
   `map_walk.hebrew_only_held` set to `[]`, so `TESTING.md` now says all 36 held maps also hold
   in English. `make_testing_md.py` printed "None skipped" in the sweep row when nothing was
   skipped; it now prints 0.
3. **Round 22** (local branches `he/wip-r22a`, `he/wip-r22b`, `he/wip-r22c`, not merged): the
   remaining tool rows of section 8.1. None of them changes the ROM.
4. The open rows of section 8.1: tool and data rows only (the inventory's C liveness for
   uncompiled `items.h` branches, the harness's mirror check,
   `make_chunks.py`'s old files, `startmenu` on Frontier floors, two leftovers). None changes the
   ROM.

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
| `<private>` (no remote) | local only | the mGBA 0.10.5 build (`mgba/`), `emu/hnsrun`, the candidates' ROMs, ELFs and screenshots (`release/rc1..rc23`, 8.7 GB), the round screenshots (`scratch/`, about 140 GB) | everything the release needs is in the fork or `<builds>` (section 8.4); the rest is rebuilt (section 2.6) |

The Spanish (`SergioBonet/hns_es`) and French (`nhykola/HeartAndSoul-FR`) forks were used only
as a cross-check, never as source text (`STYLE.md` §1).

### 1.2 Branches

| Branch | What | Rule |
| --- | --- | --- |
| `master` | identical to upstream `167aa6d537` | never commit to it |
| `he/main` | the translation; the release branch | feature branches merge into it with `--no-ff` |
| `he/renderer` | the Hebrew engine with the **English** strings. It is the drift baseline (`HNS_BASELINE`) and the chunk source | every engine or graphics commit is cherry-picked onto it; text commits never are |
| `he/upstream-fixes` | upstream bug fixes, kept apart from text and engine work | branch each fix from it, merge the fix into `he/main`, then fast-forward `he/upstream-fixes` to it. It is at `8d52b4cccf`, the hydra guard of `he/fix-upstream-hydra`, merged into `he/main` in `08027d9879` |
| `he/fonts`, `he/graphics`, `he/naming-keyboard`, `he/preview` | feature branches, already merged | kept for history |
| `he/fix-*` | one fix topic each (for example `he/fix-k5-cosmetics`, `he/fix-vr-dex`, and the rounds' `he/fix-r19` and `he/fix-r20`), already merged | merge title `Merge he/<branch>: <what it brings>` |

On GitHub (2026-11-10): `master` `167aa6d537`, `he/main` `0514c9b57b`, `he/renderer` `67df13ff43`,
`he/upstream-fixes` and `he/fix-upstream-hydra` `8d52b4cccf`, `he/fix-r19` `f1d0f9a843`,
`he/fix-r20` `ffdc529fc7`, `he/fix-r20docs` `078bec4671`, and 40 other `he/*` branches (47 `he/*`
branches in all; still no tags). `he/wip-r21` is local only.

`he/renderer` is `384104fb15` plus one pick per graphics or Easy Chat commit of rounds 19 and 20,
in this order: `2f46bee8be` (the Pokéblock graph, from `946ae2f132`), `1057b2f08a` (the Easy Chat
headers, from `81f9b905db`), `784e76146d` (the GHOST and PSYCHIC plates and `menu_info.png`, from
`04d59a585c`) and `8cfd524776` (the `menu_info.png` Psychic plate with the short hyphen, from
`3f2c255dce`). Then the three graphics commits of earlier rounds that had not been picked:
`8c5e324a40` (the paralysis tag, from `d3b59b94fe`), `0b3ccf4430` (the NORMAL rank title, from
`d41a67ebdf`) and `67df13ff43` (the alphabet mode tab, from `9164440ab9`). Round 21 adds one engine
commit to pick, `cd5fb48abe` (the Pokéblock case list's level column); it is not on `he/renderer`
yet (section 0). Each pick has the same
patch as its source commit (`git patch-id --stable`), and `graphics/` on `he/renderer` now equals
`he/main`'s (`git diff --stat he/renderer he/main -- graphics/` prints nothing).

**Checking a pick with an English build.** Build `he/renderer` before and after the picks with
`TEXT_RTL` set to FALSE (`include/config/text.h:20`, in a scratch worktree) and `make hns`, and
compare the two English ROMs. When a picked graphic is compressed and its size changes, every
later ROM object moves, so a raw `cmp` differs almost everywhere. Compare by symbol instead: pair
the ROM symbols of the two ELFs by name (`arm-none-eabi-nm -S --defined-only`), report symbols
added, removed or resized, and compare the bytes of the rest, mapping each aligned 32-bit word
that points into ROM through the symbol-to-symbol relocation before calling it a difference. For
the picks `384104fb15..8cfd524776` this gave: no symbol added or removed; only
`gUsePokeblockGraph_Gfx` (1748 → 1768 B) and `gMoveTypes_Gfx` (2372 → 2468 B) resized; content
changed only in `gMenuInfoElements_Gfx` (194 bytes, the `menu_info.png` plates) and in one
literal of `rfu_MBOOT_CHILD_inheritanceLinkStatus` in librfu, a constant derived from an address
(`0x057a2b38` → `0x057a2bac`) that grows by `0x74`, the two graphics' growth (20 + 96 bytes).
For the three older picks (`8cfd524776..67df13ff43`) no symbol was added, removed or resized, and
content changed only in `gEasyChatMode_Gfx`, `gStatusGfx_Icons` and `gContestResults_Gfx`.
The script and the builds are in `<private>/scratch/screens/r20/engproof/` (`symdiff.py`,
`PROOF.md`).

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
| Python 3 | 3.9 or newer: the 147 tool tests pass on 3.9.6, 3.11.9 and 3.14.7, and all 242 scripts under `tools/hebrew` compile with every warning turned into an error on 3.9.6, 3.11.9 and 3.14.7 (CI: Ubuntu 26.04's python3) | standard library only, except the picture tools |
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
(`Makefile:90-101`). Without `DEVKITARM` it uses whatever `arm-none-eabi-*` is on `PATH`, which is
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
| `make hns RTL_CLIP_REPORT=1 -j12` | `pokehns-clip.gba`, `.elf`, `.map` | `build/hns-clip` | diagnostic ROM that logs every glyph drawn outside its window (`Makefile:36-41, 182-183`; `src/text.c:1047`). **Never shipped.** Builds next to the release build without a clean |
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
- `-Woverride-init`, 122 times (demoted for H&S, `Makefile:216-218`).
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
| unit chunks (the sweep's labels) | `python3 tools/hebrew/make_chunks.py all` → `build/hebrew/units`, 6,611 labels (the 7,209 that 0.2 was swept with, less the 451 flag-gated and 147 unbuilt labels that `flag_gates.py` takes out). Make them again whenever `live_labels.json` changes, **into an empty folder** (`rm -rf build/hebrew/units` first): the sweep reads whatever units are there, and `make_chunks.py` never removes an old chunk file (section 8.1) | rebuilt; never stored |
| `crosscore` (libretro frontend) | nothing to install: `run_release_tests.sh` builds `tools/hebrew/emu/crosscore.c` with `cc -O2` into `RCDIR/tests/bin` on every run | |
| libretro cores | `vbam`, `vba_next`, `gpsp`, `mednafen_gba`, `skyemu` `_libretro.dylib` in `HNS_CORES` (`build/hebrew/cores`); the mGBA core is RetroArch's own (`$HOME/Library/Application Support/RetroArch/cores/mgba_libretro.dylib`) | `<builds>/reference/cores/`: copies of the five, with their SHA-1 and inferred source (the libretro buildbot's macOS arm64 nightlies, files dated 2026-10-17; `SOURCE.md`). RetroArch's mGBA core is not stored |
| English map walk | `python3 tools/hebrew/emu/mapwalk.py "$HNS_EN_ROM" "$HNS_SAVES/ladder6_postgame.sav" build/hebrew/mapwalk_en` (507 OK, 36 HELD, the same 36 maps as rc22's and rc23's Hebrew walks; made 2026-11-10 into `<private>/runs/mapwalk_en`, 373 s) | `<builds>/reference/mapwalk_en.json` (`HNS_EN_MAPWALK`), replaced in `<builds>` `c10184c`; the walk it replaced was made by an older `mapwalk.py` that tapped A and B in turn |
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
| `src/*.c` | UI and battle strings in `_()`, `__()`, `COMPOUND_STRING()`, `ITEM_NAME()` | same | 108 |
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
  - Psychic is על-חושי in every name, line and plate (Q139, which supersedes Q134);
  - Easy Chat in Hebrew, with the Hebrew-letter keyboard (Q135);
  - names follow the FireRed translation's PR #2 conventions; each name kept apart is listed
    with its reason (Q140, which supersedes Q136).

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
  7,093 rows, with CRLF line ends. The tools read `proposed_hebrew`.
  - Status `inherited` (1,915) comes from the FireRed fork.
  - Status `proposed` (5,178) is new and has not been checked against an official Hebrew source.
    It includes the 25 inherited rows that round 20 renamed after FireRed's newer names (Q139,
    Q140); their `firered_hebrew` column still holds the form they were first taken from.
- `translation/hebrew/glossary_sources.csv`: `kind,constant,english,source,pattern` (5,529 rows).
  `make_chunks.py` uses it to pre-fill name fields.

**Where a name comes from** (`transliteration_rules.md` §0):

1. the FireRed fork;
2. the Pokémon Israel Pokédex;
3. the rules in that file.

Keep families together; `python3 tools/hebrew/translit_stats.py 'EON$'` lists the precedents.

**Renaming or adding a name** is a checklist; no tool propagates a rename:

1. Commit `glossary.csv` alone, **before** any text that uses the name.
2. `python3 tools/hebrew/namecheck.py --all --warnings` should print `rows 7093, still empty 0,
   problems 0` and `warnings 0, allowlisted 34`; then run `python3 tools/hebrew/glossary_widths.py`
   (today `1 over budget`: the EXEGGUTOR-A healthbox name, 49 px against 48, decided in Q129).
3. Change every dialogue use (`git grep` the old Hebrew and the English), one file per commit.
4. For trainer or map names, run `python3 tools/hebrew/apply_names.py --dry-run`, then without
   `--dry-run`.
5. For species, run `python3 tools/hebrew/gen_dex_alpha.py` and commit `pokedex_orders.h` alone.
   Its `TEXT_RTL` list is engine data, so cherry-pick that commit onto `he/renderer` too
   (`f47c725548` there); drift fails until the baseline has it. For a species, move or Easy Chat
   word, run `gen_ec_order.py` and `gen_ec_letters.py` (CI runs all three with `--check`). Their
   two headers (`src/data/easy_chat/easy_chat_order_rtl.h`, `easy_chat_words_by_letter_rtl.h`)
   are engine data too, picked the same way: drift fails on those two files until the baseline
   has them. A renamed type also needs its plates redrawn (`graphics/types/<type>.png` and
   `graphics/interface/menu_info.png`, with `tools/hebrew/graphics/`), in a graphics commit of its
   own that is picked as well. Round 20's three picks, in order: `81f9b905db` (the Easy Chat
   headers), `04d59a585c` (the GHOST and PSYCHIC plates and `menu_info.png`) and `3f2c255dce`
   (`menu_info.png` again, the Psychic plate with the short hyphen; it applies only after
   `04d59a585c`). They are `1057b2f08a`, `784e76146d` and `8cfd524776` on `he/renderer`
   (section 1.2).
6. Update test expectations where order or text changes. For example, `4c6ba54599` updated
   `test/bag.c` for the berry names.
7. After a bulk glossary edit, diff the row **keys** between revisions (section 6.2): a rewrite
   once dropped 5 rows silently.

**Consistency warnings** (`namecheck.py --warnings`; they never change the exit status):

- `--fr-sync` compares each name with the FireRed Hebrew tree as it is now (`HNS_FIRERED`, default
  `../pokefirered-heb`), within the same kind. Follow FireRed's current name unless an H&S limit
  (bytes, width, a duplicate) or a FireRed slip stands in the way (`DECISIONS.md` Q140); every
  kept difference is in `namecheck_allow.json` with its reason. The type names follow FireRed
  too (GHOST רפאים, PSYCHIC על-חושי).
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

Q2 (`DECISIONS.md:255-273`) is a typical entry.

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
| tool tests | `python3 -m unittest discover -s tools/hebrew/tests` | the tools themselves (147 tests) | 10 s |
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
expected output below is a local run on `he/wip-r21` `34fee0e811` (2026-11-10), with
`../pokehns-heb-engine` at `he/renderer` `67df13ff43`, on a built tree. There drift prints
`708 files, 1 FAIL`: the FAIL is `src/pokeblock.c`, the engine commit `cd5fb48abe` that is not on
`he/renderer` yet. Against `67df13ff43` plus that commit the file is `ok` with no warning
(`drift.py --en <that tree> src/pokeblock.c`: `drift: 1 file, 0 FAIL, 0 with warnings only`), so
once it is picked the run prints the line below. The other steps printed exactly what is shown.

```bash
set -o pipefail
# 1. drift (hebrew.yml:50-54): only strings may differ from he/renderer
git diff --name-only Release-v2.0.6...HEAD -- data src | grep -E '\.(inc|s|c|h|party|json)$' | xargs python3 tools/hebrew/drift.py --quiet
#    last line: drift: 708 files, 0 FAIL, 336 with warnings only   (exit 0)
# 2. layout audit (hebrew.yml:56-57); creates build/hebrew; prints the report's two == lines
python3 tools/hebrew/audit.py --baseline ../pokehns-en --report build/hebrew/audit.txt
#    == translated strings: 0 errors, 54 warnings, 88 suppressed by baseline ../pokehns-en
#    == English (untranslated) strings, baseline only: 448 errors, 0 warnings   <- informational
#    line 1 of the report: audit ...: 39059 strings (24836 translated)   (the same as CI)
# 3. glossary (hebrew.yml:59-60)
python3 tools/hebrew/namecheck.py --all --warnings
#    rows 7093, still empty 0, problems 0
#    warnings 0, allowlisted 34
# 4. generated data (hebrew.yml:62-71)
python3 tools/hebrew/gen_dex_alpha.py --check     # gen_dex_alpha: 1080 entries, the TEXT_RTL list is up to date
python3 tools/hebrew/gen_ec_order.py --check      # gen_ec_order: 18 groups, the header is up to date
python3 tools/hebrew/gen_ec_letters.py --check    # gen_ec_letters: 23 lists, the header is up to date
python3 tools/hebrew/flag_gates.py --check        # total: live 6585, flag_off 451, not_built 147 / no change
# 5. tool tests (hebrew.yml:73-74)
python3 -m unittest discover -s tools/hebrew/tests
#    Ran 147 tests ... OK   (no skip with tools/preproc built and ../pokehns-en/pokehns.gba present)
# not in CI: item plurals
python3 tools/hebrew/plurals.py                   # items 902, stackable 693, problems 0
```

**How to read the results**

- **drift errors** (exit 1) are `STRUCTURE`, `TOKENS`, `TERMINATOR`, `CHARSET` and `SHRUNK`.
  Warnings (`PAGES`, `LATIN`, `UNTRANSLATED`) never fail the run unless you pass `--strict`.
  Section 6.2 lists every kind. `.party` and `.json` files are checked too: a renamed `Name:` line
  counts as a string.
- **audit:** the exit status is 1 only for a Hebrew error that the baseline does not suppress.
  - The 54 warnings are `FIT`: 16 item names, 33 move names and 5 EXEGGUTOR-A rows (Q129) that
    fit only after the game falls back to a narrower font. Six of them came with round 20's
    Psychic names; Q139 lists them.
  - A finding reads `w item_name FIT 80 > 72 p1 r1 [summary held item FONT_NORMAL] (...)
    src/data/items.h:3402`: kind, check, measured > budget, page and row, where it is drawn, and
    the source line.
  - A built tree and CI's clean checkout give the same report. `walk_tree` (`audit.py:461-481`)
    reads every `.c` and `.h` under `src/` but leaves out the six git-ignored headers that `make`
    generates (`is_generated_header`, `audit.py:451-458`), because the audit already reads their
    sources:
    - `src/data/trainers.h`, `trainers_hns.h`, `trainers_frlg.h`, `battle_partners.h` and
      `debug_trainers.h`, made from the `.party` files (`trainer_rules.mk:3-12`);
    - `src/data/region_map/region_map_entries.h`, made from the JSON (`json_data_rules.mk:4-6`).

    A header without its `.party` or JSON source is still read. Before `34fee0e811` a built tree
    counted their 2,480 strings (756 translated) twice and printed `41539 strings (25592
    translated)`, with the same findings. Now the built tree's report equals a clean `git archive`
    copy's apart from line 1 (the tree path), and the clean copy prints what CI prints
    (`<private>/scratch/screens/r21/fixes/t4/audit_clean.txt` and `fixes/audit_final.txt`).
- **tool tests in CI:** run 42725640966 at `0514c9b57b` printed `Ran 137 tests ... OK (skipped=2)`
  (no built `tools/preproc`, no English ROM). Round 21 adds 10 (8 in `test_units.py`, 2 in
  `test_audit.py`), so `he/wip-r21` has 147; CI has not run them yet.

### 4.3 The test suite

**The rule:** upstream 2.0.6 fails 1,899 of its own tests. The Hebrew build is held to "no test
fails that passes upstream" (`check_tests.py:2-9`; `docs/hebrew_translation.md:131-138`). The
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
  test tool changes, not the ROM. It is merged into `he/main` (`08027d9879`, the commit rc21 was
  built from): rc21's `make_check.log` ends with the whole summary (`FAILED 1920`, `TOTAL 5135`)
  and no segfault. `he/upstream-fixes` was fast-forwarded to `8d52b4cccf`.
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
it covers. Many round tours need a driver from `$E/scripts/` rather than `hns.py tour`;
`tours/r20_names/_runs.txt` names the driver and the command for each of its files, and
`$E/scripts/fight_moves.py --moves MOVE_A,MOVE_B,...` shows only the listed moves in the FIGHT
menu. The release tours start from saves at the top of `<builds>/saves`. A round tour
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
  7,209, so every live label was OK there too. rc22's sweep read 6,821 labels, all OK: the 6,611
  live ones plus 210 flag-off TV and Route 10 labels from three chunk files of 2026-10-22
  (`B25/B25_04.json`, `B25/B25_05.json`, `B31/B31_06.json`) that `make_chunks.py all` had left in
  `build/hebrew/units`. A fresh `--out` gives 6,611 labels, batch for batch the same output as
  `rc22/make_chunks.log` (`<private>/scratch/screens/r21/static/make_chunks.txt`). Make the units
  again, into an empty folder, before a candidate's sweep (section 5).
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
# 650 files -> ...: {'seen on screen': 525, 'translated': 125}   (rc22's sweep, on he/wip-r21 d886483f5c)
```

- Without `--sweep`, every "seen on screen" row falls back to "translated".
- A C literal takes its liveness from `tools/hebrew/data/c_strings.json`, which records it by its
  line in the English tree. `units.py` finds each record in `../pokehns-en` by line and text and
  matches the tree's literals by what they initialise: the variable, or else the designator and
  field, the macro, and the place among the file's literals with the same (`c_live_index`,
  `units.py:209-244`; `c_key`, `:247-258`). A literal on a line only a `TEXT_RTL` build compiles
  (`rtl_only_lines`, `:264-286`), such as a plural name, has no English record: it counts as live
  and takes no place. So Hebrew lines that moved no longer take another literal's verdict, and both
  trees have the same literals under every key. Without an English tree (`HNS_UPSTREAM` unset and
  no `../pokehns-en`) every C literal counts as live, with a line on stderr. `src/data/items.h`
  counts 2,218 live strings, all Hebrew; the build compiles 2,204 of them (section 8.1).
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
# 6276 text runs (6341 candidates), 6252 still English, 4.0s   exit 1 (always, on this build; rc22)
```

- **Map walk:**
  - `HELD` means the game never gave control back within the frame budget. Compare with an
    English walk before calling it a bug. With the current walker all 36 HELD maps of rc22 also
    hold in English (Frontier rooms, Pyramid, Tents, Union Room, and the two Battle Arena rooms at
    the next-opponent menu): an English walk of 2026-11-10 gives `543 maps in 361 s: {'OK': 507,
    'HELD': 36}`, the same 36 maps, and 539 of the 543 records are identical
    (`<private>/scratch/screens/r21/static/mw_en_full/mapwalk.json`). The stored English walk
    (`HNS_EN_MAPWALK`) is older. Of those 36 it holds 32, has the Dome pre-battle room's false
    `CRASH` (below) and an `ERROR` in the Battle Pike's normal room (cause not checked), and passes
    the two Battle Arena rooms; `make_testing_md.py` counts every map not `OK` as held in English,
    so it finds 34 (section 8.1).
  - Treat any `CRASH` as real until the English ROM with the same save crashes the same way, but
    first look at the PC. **A PC in `0x0A000000`-`0x0DFFFFFF` is a false alarm of the harness.**
    pokeemerald-expansion stores every script command that "requests effects" as its address
    plus `ROM_SIZE` (`data/script_cmd_table.inc:6-12`, `ROM_SIZE` `0x2000000` at
    `constants/gba_constants.inc:33`; tested by `src/script.c:561-565`), and `RunScriptCommand`
    calls it there (`src/script.c:130-138`), so those commands run from the ROM's wait-state
    mirror: 232 of the 247 table entries, in English and in rc22. `hnsrun` and `hns.py` accept
    only regions 00, 02, 03, 08 and 09 (`hnsrun.c:129-132`, `hns.py:2160-2164`; section 8.1).
  - That is what the stored English walk's `CRASH pc=0A0E8ECC @21720` in the Dome pre-battle room
    was. Its older walker answered with A and B in turn, so it kept cycling through the room's
    menu (A shows the opponent's card, B closes it), and one 60-frame check fell while the menu
    was being drawn; a copy of `mapwalk.py` with that one change reproduces its records 0-18
    exactly, crash included. The PC was in `FillBitmapRect4Bit` under `ScrCmd_multichoice`, run
    from the mirror; with the check off the next frame is back in the BIOS halt and the menu is
    drawn
    (`<private>/scratch/screens/r21/static/`, `tools/mapwalk_v5.py`, `trace18r/trace.log`,
    `trace18a/after_crash_frame.png`). The current walker presses only B and holds the room.
    Nothing is wrong in the game; no release note.
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
  - The scripts and logs are in `<private>/scratch/screens/r19/emu-facts/t1/`.
  - **Saves made outside a Pokémon Center** (round 21, rc22's release ROM): in Ecruteak City
    outdoors, on Route 37, in Ecruteak House 1, on Trainer Hill 1F during a NORMAL challenge, and
    on Battle Pyramid floor 1 after REST. Each loads in the English ROM with no crash, and the
    English screenshots match those of an English-written save of the same moment: 12 validation
    and 11 PC shots each for the town, the route and the house; 7, then 56 through the Hill's tag
    battle, both trainers' after-battle lines and the stairs to 2F; 6 of 7 on the Pyramid floor.
  - The one visible difference is the Pyramid's party screen. Pokémon the Hebrew ROM created keep
    Hebrew nickname bytes, which English shows blank (PIDGEOT shows only `'`, the geresh of
    פידג'וט), as with the player name.
  - The save bytes differ only in the play time (SaveBlock2 `0x11`-`0x12`); on the Hill, the
    encryption key (788 values re-encrypted to the same plain values) and the Hill timer
    (SaveBlock1 `0x3D64`, 322 against 345 frames); the Pyramid party's nicknames; and 28 object
    template `script` pointers, each pair naming the same label in the two ELFs.
  - On CONTINUE (`src/overworld.c:2192-2200`) the English ROM rewrites those pointers in town and
    on the Pyramid floor (`LoadBattlePyramidFloorObjectEventScripts`,
    `src/battle_pyramid.c:1878-1897`). On a Hill floor the loader is an empty function
    (`LoadTrainerHillFloorObjectEventScripts`, `src/trainer_hill.c:845-851`), so the Hebrew ROM's
    pointer stays in the template. Nothing reads it there: talking to a hill trainer and being
    seen look the script up live (`GetTrainerHillTrainerScript`,
    `src/field_control_avatar.c:442-443`, `src/trainer_see.c:561-563`), and a floor change
    rebuilds the templates (`src/trainer_hill.c:812-843`). The 56 identical Hill shots cover all
    three.
  - Scripts, logs and sheets: `<private>/scratch/screens/r21/emu/` (`facts.md` section 2, `t2/`,
    `sheets/t2_*.png`).
- **ROM sweep:** do not gate on its exit status. Of rc22's 6,252 runs, 0 are on live labels,
  3,265 on dead Emerald labels, 16 debug-only, and 2,971 untracked (mostly `data/event_scripts.o` and
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
   gave `435 identical, 60 differ`, the "60 tour frames" of `DECISIONS.md:1942`.
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
- `make_chunks.py all` into an empty `build/hebrew/units`, run again before each candidate (rc21's
  sweep read units older than `flag_gates.py`: 7,209 labels, 147 skipped, instead of 6,611; rc22's
  read 210 flag-off labels from old chunk files on top of the 6,611; section 4.5);
- the cores from `<builds>/reference/cores/` unzipped into `HNS_CORES` (`crosscore` is built by the
  test script);
- `HNS_EN_MAPWALK` pointed at `<builds>/reference/mapwalk_en.json` (stale until it is replaced,
  section 8.1).

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
| namecheck `WARN FRSYNC`, `TRANSLIT`, `SAMENAME` or `STALE` | `namecheck.py --warnings` | a name differs from FireRed's current one, a transliteration slip, one person with two spellings, or an allow entry that no longer matches | follow FireRed's name unless an H&S limit or a FireRed slip stands in the way (Q140); otherwise add or update its entry, with the reason, in `tools/hebrew/data/namecheck_allow.json` | `49394ba1ad` |
| `gen_dex_alpha`, `gen_ec_order`, `gen_ec_letters` or `flag_gates` `--check` exits 1 | the entries it lists | a rename or a script change without regenerating | run the tool without `--check` and commit its output alone | `c022422009` |
| A glossary name went back to Latin; a row vanished | diff the row keys (below) | a bulk rewrite of `glossary.csv` dropped rows: `bb8db5c703` lost 5 (four radio DJs and `TERM_NURSE_JOY`) | restore the rows; review every bulk glossary edit with the key diff | `d8de0c8fd0` |
| 8 multi-word names held only the first word | read the row | truncation during a rewrite (which commit is unknown) | restored in the names review | `DECISIONS.md:1917-1927` |
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
| a battle differs between runs | | input timing moves `Random()` | `pinrng` (`hns.py:1930-1934`) |
| map walk `HELD` | the same map on the English ROM | a scripted sequence the B-only walker cannot finish | a harness limit unless English behaves differently |
| `CRASH` with a PC in `0x0A`-`0x0D` (for example `pc=0A0E8ECC`), the game fine a frame later | `hns.py where` on the PC less `0x2000000` | a script command that runs from the ROM's wait-state mirror by design (`data/script_cmd_table.inc:6-12`); the harness accepts only regions 00, 02, 03, 08, 09 (`hnsrun.c:129-132`, `hns.py:2160-2164`) | a false alarm (section 4.6); the check should accept the mirrors (section 8.1) |
| ladder1 validation exits 1 (`leavecenter: blocked inside 1.4`) | which script ran | `ladder_validate.txt` leaves a Center; rung 1 is the bedroom | validate rung 1 with `ladder_validate_newgame.txt` (`run_release_tests.sh` does) |
| `ValueError: invalid literal for int() with base 0` from `warpto` in a `ladder.py` script | the `warpto` line | `ladder.py` replaces `hns.py`'s `warpto MAP_NAME X Y` with its own `warpto GROUP NUM X Y` (`ladder.py:224-228`) | give the numbers (`hns.py map NAME` prints them), or run the script with `hns.py` |
| `start menu cursor did not reach BAG (at 1)` on the second `startmenu` of a run on a Trainer Hill or Battle Pyramid floor | `_error.png` shows the menu closed | **unverified**: `start_menu_cursor` opens the menu only when `gMenuCallback` is not `HandleStartMenuInput` (`hns.py:927-929`), and the callback may still hold it after the menu closed | `tap START 30` before the second `startmenu` (section 8.1) |
| `rom_sweep.py` exits 1 with about 6,252 runs | | dead Emerald text compiled in | informational; diff against the previous candidate |
| cross-core: VBA-Next differs on whole frames (no RTC); SkyEmu exit 139 | `crosscore` log | an old frontend that answered core options with NULL | use the frontend `run_release_tests.sh` builds from `crosscore.c` (it answers with the defaults) |
| a tester reports a "crash" | does the screen show an assert message? | `make hns` keeps asserts (`RELEASE ?= 0`, `Makefile:69`); the ROM contains `AssertfCrashScreen` | read the assert. R+START (the debug menu) is compiled in (`include/config/debug.h`); R is also the DexNav button |

### 6.5 On screen: clipped, misplaced or misordered text

| Symptom | Check | Cause | Fix | Commit |
| --- | --- | --- | --- | --- |
| letters missing at the left end of a line (reads like a typo) | clip build + `hns.py tour --clip` or `sweep.py` | the line is wider than its window; whole glyphs past the edge are not drawn (`src/text.c:1401-1421`) | shorten or re-wrap; measure in the screen's own font before cutting | `a3615d7dd3`, `47790b34d0`, `1056f5075f` |
| text off its box art, although it fits the window | `git grep -n 'SetWindowRtlMirrorWidth' -- src` | the mirror axis is the window width, but the art is narrower | `SetWindowRtlMirrorWidth(id, px)` (`src/window.c:46`) | `aba432739a`, `d02bbbb543`, `108a0ef3f1`, `c9f132be4c`, `a459a5995e` |
| text, cursor or icon on the wrong side; text over sprites or fixed art | `git grep -n 'SetWindowRtlMode' -- src` (48 calls in 23 files) | the wrong window mode. The mode resets on `AddWindow` and friends | `WINDOW_RTL_IN_PLACE` for text on fixed art, partly copied windows and tilemap cursors; set it right after creating the window | `c9f132be4c`, `795f5d49b4`, `dc86d6f578`, `108a0ef3f1`, `809187e408`, `a4c59d59d0`, `fe52aadb6c` |
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
- **Hebrew-written saves load in the English ROM** (section 4.6): a new-game save in the bedroom;
  mid-game and post-game saves made in a Pokémon Center; and saves made in a town, on a route, in
  a house, on a Trainer Hill floor during a challenge and on a Battle Pyramid floor. A Hebrew
  player name, and the nickname of a Pokémon the Hebrew game created, shows blank there.
- **Pre-2.0 (1.2.1) saves do not load**, in English 2.0.6 or in Hebrew 1.0, and the game says so.
  - The sector checksums reject them. 2.0.6 sums each sector over its own chunk sizes
    (`sSaveSlotLayout`, `src/save.c:60-78`), and 1.2.1 wrote others: SaveBlock2 3920 bytes
    against 3892, SaveBlock1 4084 × 3 + 3548 against 3968 × 3 + 3856, the PC 4084 × 8 + 3484
    against 3968 × 8 + 2400 (read from each ROM's `sSaveSlotLayout`). The footer is at byte 4084 in
    both, so each written slot counts as present, not empty.
  - Sector 13 always fails: 1.2.1's box names lie in its bytes 3332-3466, which 2.0.6 no longer
    sums. Every written slot is then `SAVE_STATUS_ERROR`, the load is `SAVE_STATUS_CORRUPT`
    (`src/save.c:658`), and `src/intro.c:1151-1156` resets the save blocks.
  - The main menu says "The save file has been erased / due to corruption or damage." (Hebrew
    `קובץ השמירה נמחק / בגלל שיבוש או נזק.`, `src/main_menu.c:260`, `:669-673`), then offers NEW
    GAME and OPTION only. Loading writes nothing: the flash changes only at the first save
    (`src/new_game.c:228`, `src/start_menu.c:1294-1297`, `src/save.c:775-783`).
  - The migration (`src/save.c:930-980`) runs on any loaded save; it is not what stops them.
  - Seen on both ROMs with a synthetic save in 1.2.1's layout, not a real one
    (`<private>/scratch/screens/r21/static/tools/make_save121.py`, `save121/sheet_121.png`:
    `gSaveFileStatus` 2 and the file unchanged after the run). Upstream says the same: saves from
    before 2.0 are not compatible (`../pokehns-en/README.md:16`). A real 1.2.1 save was never
    loaded (**unverified**).
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
- **No AI attribution**: no `Co-Authored-By` trailer, no "Generated with" line. All 1,473 commits
  on `he/main` (at `c1cfd8a30b`, `git rev-list --count he/main ^master`) follow this.

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
  `he/main` has 43 such merges (at `c1cfd8a30b`).
- Keep `master` identical to upstream. Keep upstream bug fixes on `he/upstream-fixes`, separate
  from text and engine work (`00dd646cc1`, `4d5d2b9ada`).
- Before touching an engine function, `git log -S` it upstream to see why it looks the way it
  does.
- Keep every diagnostic behind a config switch (like `RTL_CLIP_REPORT`), so that the release ROM
  is free of it.

---

## 8. Open, stale and unverified

### 8.1 Open defects in the repository

The four rows of round 20 (the Pokéblock case list's three-digit level, `dbgmenu.py`'s early
shots, the C-literal liveness by line, and the audit's count on a built tree) were fixed in
round 21, merged in `8aeb3a0f2b` (section 8.5, round 21), and the stale English reference walk was
replaced before rc23 (section 0, item 2). These are open:

| Item | Evidence | What to do |
| --- | --- | --- |
| `tools/hebrew/data/c_strings.json` marks 14 English literals of `src/data/items.h` live that the build does not compile, so `STATUS.md` counts 2,218 live strings in `items.h` where the build has 2,204 | `arm-none-eabi-gcc -E` of `src/item.c` keeps 2,204 literals of `items.h`, all Hebrew. The 14 are in `#if` branches the build leaves out: the GROWTH, DAMP, STABLE, SURPRISE and BOOST MULCH descriptions, the two ICY ROCK descriptions, EXP. SHARE's and TM HAIL's descriptions, TM70's and HM DIVE's names and descriptions, and METEORITE's description. The inventory searches the ROM for each literal's longest plain run (`inventory/README.md`, "C literals"): 11 of these runs are found in the ROM, and the other 3 texts are compiled from another line. `units.py` takes the verdicts as recorded (`<private>/scratch/screens/r21/fixes/t3/why14.py`) | decide C liveness by what the preprocessor keeps, in `tools/hebrew/inventory/extract.py`, then rebuild `c_strings.json` and regenerate `STATUS.md`. Text only; nothing in the ROM changes |
| The harness calls a PC in the ROM's wait-state mirrors a crash | `pcIsSane` (`hnsrun.c:129-132`) and `pc_is_sane` (`hns.py:2160-2164`) accept only regions 00, 02, 03, 08 and 09, but the game runs most script commands from `0x0A` by design (section 4.6); `sweep.py:887` names a symbol only for 2, 3, 8 and 9 | accept `0x0A`-`0x0D` in both checks and map them to `0x08` for symbol names. Tools only |
| `make_chunks.py` never removes an old chunk file, so a sweep can read labels that are no longer live | it only creates the batch folders (`make_chunks.py:115`, `os.makedirs(..., exist_ok=True)`); `build/hebrew/units` kept three chunk files of 2026-10-22, and rc22's sweep read 6,821 labels instead of 6,611 (section 4.5) | remove the batch's old chunk files before writing, or refuse a folder that is not empty; until then empty the folder first (sections 2.6 and 5) |
| `hns.py` `startmenu NAME` fails on its second use in a run on a Trainer Hill or Battle Pyramid floor | seen in round 21 on the English ROM, the same with a Hebrew-written and an English-written save (`<private>/scratch/screens/r21/emu/t2/val/`): "start menu cursor did not reach BAG (at 1)", the menu closed on screen. The likely cause, a stale `gMenuCallback` (`hns.py:927-929`), is **unverified** | find the cause and open the menu whenever it is not on screen; until then tap START first (section 6.4) |
| Two small leftovers of round 21's tool fixes | `status_report.py` `KEPT_LATIN` (`:22-48`) still lists `src/data/items.h` and `src/pokenav_menu_handler_gfx.c`, which no longer keep any Latin string (`STATUS.md`: 2218/2218 and 18/18). `strcov.py:222-241` has its own copy of the generated-header rule that `audit.py:451-458` now uses | drop the two entries; let `strcov.py` import `audit.is_generated_header`. Harmless as they are |

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
  'psychic power' as כוח פסיכי (Q134, superseded by Q139), the Gen 4 FROSTBITE tag redrawn as קור
  (Q137), the names compared with FireRed's (Q136, superseded by Q139 and Q140) and publishing
  without hand play (Q138).
- **Decided in round 20:** Psychic is על-חושי (Q139) and names follow FireRed's PR #2 conventions
  (Q140).
  - Three Psychic names keep the noun על-חוש where an adjective was possible; the owner left the
    round's open choices to the project, and these are decided, not open. PSYCHIC SURGE נחשול
    על-חוש and PSYCHIC SEED זרע על-חוש take the noun as their siblings do (נחשול חשמל, נחשול
    ערפל, נחשול עשב, זרע חשמל) and as FireRed's PSYBEAM קרן על-חוש; the adjective forms would fit
    too. PSYCHO SHIFT הסטת על-חוש fits the FIGHT menu, the summary and the relearner in their own
    fonts and needs the narrower font only in the contest list (60 px of 59, one of the six FIT
    warnings of Q139). הסטה על-חושית (77 px) would need the narrower font in all four, and
    `audit.py`, which applies the party field-move budget to every move, would report an error.
  - Both Psychic plates, `graphics/types/psychic.png` and the plate in
    `graphics/interface/menu_info.png`, are drawn in FONT_SMALL_NARROWER glyphs with a 2 px hyphen:
    the word is 30 px wide, with 1 px to spare on each side (`tools/hebrew/graphics/README.md`,
    Q139).
  - Kept on purpose and listed with reasons in Q140 and `namecheck_allow.json`: SLASH, CHESTO
    BERRY, IAPAPA BERRY, POKéBLOCK CASE, EXEGGUTOR and ELITE FOUR differ from FireRed's names
    because of an H&S limit or a FireRed slip, and PSYCHO BOOST because FireRed left it on פסיכי.
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
- **Proposed names.** The 5,178 `proposed` glossary rows were never checked against an official
  Hebrew source. `namecheck.py --warnings` checks them for consistency with FireRed and for
  transliteration slips (Q140); the roughly 3,000 rows translated by meaning stay `proposed` until
  a native speaker reads them.
- **Not seen by a person:**
  - nobody has played from a new game to the first badge;
  - nothing has run on real hardware (needs a 32 MiB cart, FLASH 128 KB save and an RTC);
  - no real 2.0.x save from a long playthrough, and no real 1.2.1 save, has been loaded;
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

None known after round 21. A read of every document at `he/main` `0514c9b57b` found the statements
below wrong or stale, and each is corrected where it stands; the evidence is in
`<private>/scratch/screens/r21/static/facts.md` (section 3.2) unless a line says otherwise.

- **Section 0:** `he/main` is `0514c9b57b`, not `c1cfd8a30b` (`git ls-remote`); CI is green in all
  three jobs at `c1cfd8a30b`, where the handoff said two were still running (`gh run view
  42721195219`); the commit 1.0 was built from is named in the builds commit `8bae7a0` and in
  `<builds>/records/README.md:43`, not in `<builds>/README.md`; rc22's sweep read 6,821 labels
  because old chunk files were left in the units folder (section 4.5).
- **Line references:** the toolchain `PATH` is at `Makefile:90-101`, the clip flag at
  `Makefile:182-183`, the `-Woverride-init` demotion at `Makefile:216-218`, Q2 at
  `DECISIONS.md:255-273`, the test rule at `docs/hebrew_translation.md:131-138`, the "60 tour
  frames" at `DECISIONS.md:1942`, the eight truncated names at `DECISIONS.md:1917-1927`, and
  `pinrng` at `hns.py:1930-1934`.
- **Counts:** 108 `src/*.c` files differ from `master` (88 was right on 2026-10-22, `git diff
  --name-only master he/main -- 'src/*.c'`); `SetWindowRtlMode` has 48 calls in 23 files (`git grep
  -n SetWindowRtlMode -- src`, without its definition); the private release folder holds `rc1..rc22`
  in 8.3 GB (`du -sh`); GitHub has 47 `he/*` branches (`he/fix-r20docs` is pushed too); the ROM
  sweep on 1.0 finds 6,276 runs (6,341 candidates), 6,252 still English (`<private>/release/rc22/tests/rom_sweep.txt` line 1), 2,971 of them
  untracked (`rom_sweep_rc22.json` split by `live_labels.json`).
- **Facts:** the English map walk's Dome crash was the harness, and the stored English walk is
  older than the walker (section 4.6); `make_chunks.py all` gives 6,611 labels only into an empty
  folder (section 2.6); 1.2.1 saves fail on the sector checksums, not on the migration (section
  6.6); a Trainer Hill floor does not rewrite its object scripts on CONTINUE (section 4.6).
- **Also:** section 4.3 called `08027d9879` the commit 1.0 is built from, and 8.5 called rc21 the
  current 1.0; both were true before rc22.
- **Found by the round's review:** the stored English walk holds 32 of the 36 maps, not 34 (the
  other two are a false `CRASH` and an `ERROR`; `make_testing_md.py` counts both as held), corrected
  in section 4.6 and the emu and release READMEs; and `audit_final.txt` is in `fixes/`, not
  `fixes/t4/` (section 4.2).
- **Not changed in place:** `notes.json` `map_walk` and the shipped 1.0 `TESTING.md:48` still say
  the two Battle Arena rooms hold only in Hebrew. They change together with the English reference
  walk (section 8.1).

Earlier passes: round 20 corrected the audit's example finding (section 4.2:
`src/data/items.h:3402`, where it had a line no finding names) and the commit and merge counts of
section 7. Round 19 corrected six line references: `RELEASE ?= 0` is at `Makefile:69`, `KEPT_LATIN`
at `status_report.py:22-48`, the Hebrew count at `status_report.py:82`, the sweep's path guard at
`sweep.py:391-396`, `walk_tree` (now at `audit.py:461-481`) and `LoadSaveblockObjEventScripts` at
`src/overworld.c:592-600`. Every text tool has tests: 147 tests in 21 files under
`tools/hebrew/tests`, with small committed fixtures in `tools/hebrew/tests/data/`. Add a row here
when a document and the tree disagree, and fix it in a docs-only commit.

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
  (`08027d9879`); `he/upstream-fixes` is fast-forwarded to it. The 0.2 and rc20 `make_check.log`
  came from `make check BUILD=hns -j12` (the release README), with 15 hydra runners, in about
  4 min.
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
- `make_chunks.py all` on this tree gives the sweep 6,611 labels when its folder starts empty
  (section 2.6), and the static steps
  of the worked example in section 3.4 (`textwidth.py`, `wrap.py`, `make_chunks.py B21`,
  `checkunits.py`, `drift.py`, `audit.py`) print the outputs shown there.

**Verified in round 19** (on rc21, then 1.0, unless a line says otherwise; scripts, logs
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
    INFO page. In H&S the SKILLS page shows stats only. Round 20 renamed it `משכימת קום` (Q140),
    seen in the same box (below).
- **`make_ladder.sh` rebuilds the stored ladder byte for byte,** with the time-zone condition of
  section 2.6.
- **The Pokéblock feeding screen's condition graph:** on rc21 two labels are 1 px from the pentagon
  outline; the art of `946ae2f132` moves them to 3 px and 4 px, and nothing else on screen changes
  (`tours/r19_fix/pb_feed_graph.txt`, run on rc21, on a build with the new art and on English).
  The art is in `he/main` since `b32c6f117c` and on `he/renderer` as `2f46bee8be`.
- **Why the local audit counts more strings than CI:** six generated headers in a built tree; the
  findings are the same. Round 21 made the audit leave them out (below).
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
  - A page held 30 frames shows its full text, and pages held 60 frames each all draw. Round 21
    fixed the harness (below). A one-line ROM change (`TEXT_SKIP_DRAW` in those prints)
    would make one copy, but the menu is debug-only and upstream, so it stays.
- **The branches whose commits `git cherry` does not find are contained in `he/main`** (section
  1.2).
- All 242 scripts under `tools/hebrew` compile with every warning turned into an error on Python
  3.9.6 and 3.14.7, and the 137 tool tests pass on 3.9.6, 3.11.9 and 3.14.7 (`he/wip-r19`).

**Verified in round 20** (the Psychic and FireRed names of Q139 and Q140). Each changed screen was
shot on three builds: rc21's clip ROM (then 1.0), the clip ROM of `he/wip-r20`
`a9ebeeb278`, and English 2.0.6. The two checks after the review fixes ran on a build that equals
`he/fix-r20` `ffdc529fc7`. None of this ran on the candidate built from `c1cfd8a30b`; its own
release tours and sweep cover the screens the release tests reach. The round's tours are in
`tools/hebrew/emu/tours/r20_names/`; scripts, logs, shots and sheets are under
`<private>/scratch/screens/r20/` (`render/render.md`, `fixup/r20_fix.md`).

- **Every changed string that the H&S ROM can draw was drawn and compared** with rc21 and English,
  with 0 clip records on the round's clip build in every run and in all 71 release tours, except
  the places listed under "Not verified". Seen:
  - the renamed moves in the FIGHT menu, also under the Gen 4 battle interface, with their START
    move-info windows, and in the move relearner;
  - all 42 changed dialogue labels that the H&S ROM assembles (the sweep: OK 42, no CLIP);
  - the Battle Tower partners' self-introductions with the new class names;
  - the Easy Chat STATUS and MOVE lists and all 23 ABC lists;
  - Kurt's ball list and the Game Corner TM list, each drawn by a RAM script as a stand-in: no
    H&S script calls `MULTI_KURT_BALLS` or `MULTI_GAME_CORNER_TMS`;
  - the stat-change lines with מאוד, באופן חמור and בצורה קיצונית;
  - the type name on the summary and Pokédex INFO plates, the bag's TM panel plate
    (`menu_info.png`), the FIGHT menu's type field, the relearner, the Pokédex type search and the
    challenge menu's ONE TYPE values;
  - the renamed abilities (also in battle pop-ups and the Trace line, and EARLY BIRD משכימת קום on
    the summary INFO page), items with their descriptions, trainer classes in battle and Pokédex
    entries;
  - after the review fixes, the TM29 panel's על-חושי plate with 1 px to spare on each side, as on
    the summary and Pokédex plates, and the three Bug-Catching Contest results lines with
    מאמנת-העל (OK 3, no clip).
- **The 71 release tours:** 71 OK on rc21 and on the round's build. `hns.py tourdiff` gives 1898
  identical, 157 differ and 1 shot only on the round's build. 144 of the 157 show changed text.
  The other 13, and the extra shot, come from a longer battle message that shifts later frames:
  12 pages of `bv_double` turn 2 (plus `bv_double_turn2_13`) and one animation frame of
  `bv_catch_fail`.
  - In `bv_double`, turn 1 ends 4 frames later (@2824 against @2828, `alltours_*.log:881`), and on
    turn 2 the foe uses Quick Attack first, which adds a page; the battle ends the same way. Why a
    few frames change the foe's choice is **unverified**: the tour pins only `gRngValue` before
    every frame (`hns.py:1930-1934`), and the round changed strings only. Each tour is
    deterministic per ROM: a second run is pixel-identical on both builds.
  - In `bv_catch_fail`, the `fail_norun_after` shot is 16 frames apart (@7290 against @7306,
    `alltours_*.log:746`); the shift grows over the seven turns, from 4 frames to 16.
- **Five changed FRLG Saffron labels are in no H&S ROM:** they are assembled only under
  `.if IS_FRLG` (`data/event_scripts.s:605-1052`).
- **The engine tests a rename can affect** passed on the round's test ELF: every `* fit *` test
  in `test/text.c`, the Magnitude test and the bag sort tests (41 results; the one failure is a
  known upstream one). The full `make check` was not run on `he/fix-r20`; the candidate's
  `make check` of `c1cfd8a30b` covers it (section 5, step 3).
- **The English proof of the `he/renderer` picks** (section 1.2): only the three picked graphics
  change the English ROM.
- The 137 tool tests pass at `c1cfd8a30b` on Python 3.9.6 and 3.11.9.

**Verified in round 21** (the fixes on `he/wip-r21` and a clean build of `34fee0e811`, the rest on
rc22, the current 1.0, and English 2.0.6; scripts, logs and screenshots that are not in the fork
are under `<private>/scratch/screens/r21/`, in `fixes/`, `emu/` and `static/`):

- **The Pokéblock case list shows a three-digit level whole** (`cd5fb48abe`). The narrow font's
  level glyph is 12 px wide against English's 8 (`textwidth.py --font FONT_NARROW "{LV}255"`:
  27 px in the tree, 23 px in `../pokehns-en`), so `Lv` and three digits ended at x 115 of the
  112 px window and, mirrored, the first digit started at x -3. Under `TEXT_RTL` the level column
  now starts at x 83, not 87 (`src/pokeblock.c:757-763`; the English `#else` is unchanged).
  - `tours/r19_fix/pb_feed_graph.txt` now holds a level-99 INDIGO block (the widest name) and a
    level-7 RED block as well (`a931270aa5`). On rc22's clip ROM it logs one clip (the `2` of
    level 255, window 1, font 7, x -3); on the clip ROM of `34fee0e811` it logs
    `clip total 0 lost 0` (`fixes/t1/final_clip/pb_feed_graph/clip.json`).
  - Level 255 starts at x 1 of the window, English's 1 px margin; INDIGO's name keeps 11 px
    before the level glyph (15 px before); the one- and two-digit levels move 4 px with it
    (`fixes/t1/pbg_list_en_before_after.png`, `pbg_list_crop_en_before_after.png`).
  - Only the tour's `pbg_list` and `pbg_back` shots change (`tourdiff`: 16 identical, 2 differ).
  - So whether play can make such a level (a frame model of a perfect blend against the Blend
    Master peaks at level 94; a real blend was not measured) no longer matters.
- **The ROM of `34fee0e811` differs from rc22 in 3 bytes:** `0x81A9EB6` in `UpdatePokeblockList`
  (`adds r3,#0x45` to `#0x41`, the skip 87 to 83) and two digits of an assert's file:line string
  (`src/pokeblock.c:858` to `:864`). No other code or data changes, so gameplay is unchanged. A
  clean build: `pokehns.gba` 33554432 bytes, SHA-1 `383e16ba227ae4c62ae1c1ff01bfaa0c0793eedf`,
  CRC32 `A6214055`; clip build SHA-1 `66be59802683abf1b1d69be586e38d04dc03c4bb`, CRC32 `08A267D5`
  (`fixes/rom/build_info.json`). The merge `8aeb3a0f2b` built the same ROM again as rc23, the current 1.0.
- **`dbgmenu.py` shoots each debug page once its copies are in VRAM** (`9df09379ab`). `view()`
  waits 8 frames, then until `sDma3Requests` has no entry with a size, before the shot and again
  before B, and fails after 240 frames (`dbgmenu.py:47`, `:100-125`). One `--only party` run now
  shows text on all 22 party pages, on rc22 and on the ROM of `34fee0e811`, and the 23 shots are
  identical between the two (`fixes/t2/after_sheet.png`, `final_sheet.png`); before, only the
  first page and the three-Pokémon page had text (`fixes/t2/before_sheet.png`). A probe saw the
  queue drain 8 to 10 frames after the old shot point on every six-Pokémon page. The full run
  (switch, info and party) gives 154 shots.
- **C literals keep their own liveness in `STATUS.md`** (`9519215de4`, `d886483f5c`; section 4.5).
  On the English tree the new key gives every record of `c_strings.json` its own verdict: 0
  mismatches in 156 files. Regenerated from rc22's sweep, `STATUS.md` changes in 15 C rows and
  keeps its totals (650 files, 525 seen on screen, 125 translated): `items.h` is 2218/2218 (STICKY
  BARB's plural and SKULL FOSSIL's description now count, 7 English descriptions of uncompiled
  branches no longer do), the species files lose the Mega and Gigantamax descriptions
  (`P_MEGA_EVOLUTIONS` and `P_GIGANTAMAX_FORMS` are FALSE, `include/config/species_enabled.h:23`,
  `:26`), `strings.c` is 1139/1117 and `pokenav_menu_handler_gfx.c` 18/18.
  - The round's review found the key could still misplace literals of the Hebrew tree, although no
    verdict was wrong yet: 365 keys had a different number of literals in the two trees. A
    variable took a designator from up to 4000 characters back, which translated text moves, and
    a `TEXT_RTL`-only literal took a place, so in `src/data/script_menu.h` the last five literals
    each took the next one's record. `e1e91ea1c0` keys a variable by its name alone and gives a
    `TEXT_RTL`-only literal a key of its own: 0 keys then differ, all 21,034 verdicts of the tree
    and `STATUS.md` are unchanged, and the English tree still gives 0 mismatches.
  - `9519215de4` changed the verdict of 183 literals of the tree. Each whole literal, looked up in
    rc22's clip ROM, agrees with its new verdict except one; for the variables among them, rc22's
    symbol table confirms 20 corrections, and its 3 disagreements are 2 uncompiled `#else` copies
    of a compiled variable and 1 `c_strings.json` verdict. The verdicts still wrong come from
    `c_strings.json` itself (section 8.1), such as the one: the BATTLE pocket name is live there,
    although `I_COMBINE_BAG_POCKETS` is TRUE (`include/config/item.h:55`), because the inventory
    found the run `BATTLE` in the ROM.
  - `363b85706a`: without an English tree (`HNS_UPSTREAM` unset, no `../pokehns-en`), `units.py`,
    `status_report.py` and `make_chunks.py` stopped with a `TypeError` on the first C file; every
    C literal now counts as live there, as the commit message of `9519215de4` meant.
- **The audit counts what CI counts** (`34fee0e811`; section 4.2). The six skipped headers are
  git-ignored, untracked, and byte for byte what trainerproc and jsonproc make from the tracked
  `.party` and JSON files; no tracked file is skipped. A clean `git archive` copy of `34fee0e811`
  gives `39059 strings (24836 translated)`, 0 errors, 54 warnings, 88 suppressed, and the built
  tree now gives the same report (`fixes/t4/audit_clean.txt`, `fixes/audit_final.txt`).
- **The static checks at `34fee0e811`** (section 4.2): audit as above, the 54 warnings the same
  `FIT` list as before (16 item, 33 move, 5 species names); namecheck `rows 7093`, 0 problems,
  0 warnings, 34 allowlisted; plurals 0 problems (items 902, stackable 693); the three generators
  and `flag_gates.py` (`live 6585, flag_off 451, not_built 147`) up to date; drift 708 files with
  one FAIL, `src/pokeblock.c`, which passes against `he/renderer` plus `cd5fb48abe`.
- The 147 tool tests pass on Python 3.9.6, 3.11.9 and 3.14.7 with no skip, and all 242 scripts under
  `tools/hebrew` compile with every warning turned into an error on 3.9.6, 3.11.9 and 3.14.7.
- **The English map walk's Dome "crash" is a false alarm of the harness** (section 4.6, in
  `static/`): reproduced exactly with the older walker, traced to a script command run from the
  ROM mirror, and the game goes on to draw the menu. With the current walker English holds the
  same 36 maps as rc22 (`static/mw_en_full/mapwalk.json`).
- **rc22's sweep read 210 stale labels on top of the 6,611 live ones,** from chunk files that
  `make_chunks.py all` does not remove (section 4.5); all 6,821 were OK.
- **Hebrew-written saves made outside a Pokémon Center load in the English ROM** (section 4.6, in
  `emu/`): a town, a route, a house, a Trainer Hill floor and a Battle Pyramid floor.
- **Why 1.2.1 saves do not load, and what the player sees,** on both ROMs with a synthetic save
  (section 6.6, in `static/`).
- **Round 20's names in the places no test had reached** (in `emu/`, `facts.md` section 1; every
  Hebrew run on rc22's clip ROM, with 0 clip records):
  - PSYCHIC GEM and PSYCHIC TERA SHARD in the PC storage held-item field, in both PC modes, beside
    English. In the 78 px panel the GEM spans x 9..71 and the SHARD x 7..71; English cuts its own
    name to `PSYCHIC TERA SHAR`. A player gets the GEM from the field-item randomizer
    (`src/data/randomizer/item_whitelist.h:383`, `src/randomizer.c:70-75`) and the SHARD only from
    the overworld debug menu (`emu/sheets/a_pc_*.png`).
  - The battle debug menu's hold-effect name חולק ניסיון: in full on AI INFO in a trainer battle
    once OMNISCIENT is set on the foe in the menu (`src/battle_debug.c:910-938`,
    `src/battle_ai_util.c:139-156`), and as `חולק ני` on AI PARTY, the 7-byte cut of
    `src/battle_debug.c:976` (English `Exp Sha`), after FRISK revealed a wild GYARADOS's EXP. SHARE
    (`emu/sheets/b_dbg_*.png`).
  - **Unreachable, in English too:** the Z-move panel's type and the GENESIS SUPERNOVA, MAX
    PHANTASM and MAX MINDSTORM descriptions. The only gimmick toggle is the START branch of
    `HandleInputChooseMove` (`src/battle_controller_player.c:913-924`), and START is
    `B_MOVE_DESCRIPTION_BUTTON` (`include/config/battle.h:343`), whose branch comes first
    (`:907-911`). With the Z-POWER RING, MEWNIUM Z, MEW and PSYCHIC in place the Z icon shows, but
    START only opens the move description, on both ROMs (`emu/sheets/c_zmove.png`). Dynamax is off
    (`B_FLAG_DYNAMAX_BATTLE` is 0, `src/battle_dynamax.c:86-89`; no Dynamax line in
    `trainers_hns.party`), and no move source gives an id at or above `MOVES_COUNT`, the first
    Z-move (`include/constants/moves.h:910-913`).
  - **Unreachable:** `gText_Ghost` רוח רפאים and the Trainer Tower AERODACTYL. The Pokémon Tower
    (map group 66) and the Trainer Tower (group 67) have NULL map headers in both ROMs, and their
    scripts are assembled only under `IS_FRLG` (`data/event_scripts.s:605-1052`, `:1027`). Forced
    from RAM, רוח רפאים fits its healthbox (`emu/sheets/d_ghost*.png`).
  - **Unreachable:** the Trainer Hill AERODACTYLs, HENRY's `mons[3]` and ENRIQUE's `mons[0]` on
    the Variety set's floor 4 (`src/data/battle_frontier/trainer_hill.h:2426`, `:2498`). The
    floor loads slots {0,1,2} for the first trainer and {3,4,5} for the second
    (`src/trainer_hill.c:404-408`, `:1083-1088`); on rc22 and English both send out UNOWN
    (`emu/sheets/d_hill_v4.png`).
  - **Unreachable, confirmed:** the generic phrase מהלך על-חושי, printed only for a move id at or
    above `MOVES_COUNT` that is neither a Z-move nor a Max Move (`src/battle_message.c:2769-2775`,
    `:3299-3305`). Those two kinds fill the whole range up to `MOVES_COUNT_ALL`
    (`include/constants/moves.h:913-1011`), and no string uses `{B_LAST_MOVE}`.
- **The documents against the tree** (in `static/`): every command block of section 4.2 printed
  the documented output at `he/main` `0514c9b57b` on Python 3.11.9 and 3.9.6 (`static/s42/`); the
  examples of section 3.4 print what is shown; the seven `he/renderer` picks have the same
  `git patch-id --stable` as their sources and `graphics/` is equal on both branches; `STATUS.md`
  regenerated from rc22's sweep was byte for byte the committed one (before `d886483f5c`). The
  stale statements it found are listed in section 8.3.

**Not verified:**

- A Linux build with devkitPro pacman; another machine with devkitARM r68 reproducing the 0.2
  SHA-1.
- Whether the official English 2.0.6 binary (CRC32 `01713508`) is a `RELEASE=1` build. The
  evidence leans to a plain build, and the decisive test needs the official UPS and an Emerald base
  ROM (section 2.5). Also whether Ubuntu's apt `gcc-arm-none-eabi` reproduces it.
- RetroArch's own `.srm` loader with the 131088-byte save.
- The harness and the ladder on Linux; how the clock's hour reaches the game's random numbers
  (section 2.6).
- A real pre-2.0 (1.2.1) save: only a synthetic one in its layout was loaded (section 6.6).
- Whether the battle debug menu's AI party page still comes up garbled the first time it opens,
  as `dbgmenu.py`'s docstring says (`:18-19`); it was not checked again after round 21's harness
  fix.
- The out-of-bounds read behind Scott's shields could write through a stray pointer after a link
  Dodrio Berry Picking game (needs a link).
- Of round 20's names, the Union Room trade board's type plate (needs a link,
  `src/union_room.c:4124`). Every other place no test had reached was shown on screen or proved
  unreachable in round 21 (above).
- A native speaker's read. Reviewers asked for one on: the radio's adjective pairs
  (`src/data/text/radio_strings.h:54-69`), the Ultra Beast Pokédex entries
  (`src/data/pokemon/species_info/gen_7_families.h`), the Day Care take-back question
  (`data/maps/Route34_DayCare_hns/scripts.inc:594`), Tucker's line (`DECISIONS.md` Q59) and the
  Easy Chat words.

## Notes from the fresh-clone test

This document was followed end to end on a fresh clone; the release ROM it builds matched release 0.2 byte for byte (SHA-1 `07753efc…`, clip build `4d7cfac5…`). Points to keep in mind:

- Give every `HNS_*` variable as an absolute path: a relative one is resolved against the folder a command runs from (`paths.py`). A sweep that finds no units prints `sweep: no script units in …` and exits 2.
