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
| [`tools/hebrew/release/README.md`](tools/hebrew/release/README.md) | the release scripts |
| [`tools/hebrew/testmsgs/README.md`](tools/hebrew/testmsgs/README.md) | the Hebrew battle-test message table |
| [`translation/hebrew/STYLE.md`](translation/hebrew/STYLE.md) | the binding style rules |
| [`translation/hebrew/DECISIONS.md`](translation/hebrew/DECISIONS.md) | 58 recorded decisions and the names review |
| [`translation/hebrew/transliteration_rules.md`](translation/hebrew/transliteration_rules.md) | how names are transliterated |
| [`translation/hebrew/STATUS.md`](translation/hebrew/STATUS.md) | per-file state (generated) |
| [`translation/hebrew/glossary.csv`](translation/hebrew/glossary.csv) | every name and fixed term |
| [`.github/workflows/hebrew.yml`](.github/workflows/hebrew.yml) | CI |

---

## 0. State at handoff (2026-10-22)

| Item | Value | Check |
| --- | --- | --- |
| `he/main` | `4a9c6858b1` | `git rev-parse --short he/main` |
| Release | One release, 1.0, replaced in place on each update (ROM, `SHA1SUMS`, `TESTING.md`); the builds repo's commit history keeps the older builds. Current 1.0: built from `he/main` `651e35c35b` | `<builds>/README.md` |
| 1.0 ROM | `pokehns-he-2.0.6-1.0.gba`: 33554432 bytes, SHA-1 `6438a720bfbdec7c666ccbd54e5b6a9d6755d770`, CRC32 `A2523184` | `<builds>/SHA1SUMS` |
| Releasing | Build a candidate with `tools/hebrew/release/`, then replace the three files in the builds repo and say in the commit message which `he/main` commit it was built from; keep `tools/hebrew/release/notes.json` at `"release": "1.0"` | section 5 |
| CI | the last two runs on `he/main` are green (39494370746, 39496758687) | `gh run list -R ronyeh2/pokehns-expansion-heb --workflow hebrew.yml` |
| Static checks on `he/main` | drift 0 FAIL; audit 0 errors and 48 warnings; namecheck 0 problems; plurals 0 problems; 67 tool tests OK | section 4.2 |
| Translation status | every live file is translated: 510 seen on screen, 132 translated, 19 blocked | `translation/hebrew/STATUS.md:5` |

**First things to pick up**, in order (details in section 8):

1. Port the fixed nickname tour into the fork. The fork's copy is stale: it types `CDE` for
   `ABC` and still reports OK.
2. Regenerate the Hebrew A–Z Pokédex order. 4 species are out of place.
3. Settle Easy Chat: the docs say English, but the tree is about half Hebrew.
4. Fix the doc lags listed in section 8.3.
5. Still never done: hand play from a new game to the first badge, and real hardware.

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
| `ronyeh2/pokehns-expansion-heb` (this repo) | public | engine, text, graphics, tools, docs | default branch `master`; **no tags** (`git ls-remote` on 2026-10-22) |
| `PokemonHnS-Development/pokehns-expansion` | public | upstream | `Release-v2.0.6` = its `master` = `167aa6d537` |
| `ronyeh2/pokehns-hebrew-builds` | **private** | the ROMs, `SHA1SUMS`, `TESTING.md` per release, a README table | `.gitattributes` has `*.gba binary`; one ROM per milestone |
| `<private>` (no remote) | local only | the translated unit chunks (`translation/units/B01..B40`, `G01`), release candidates `release/rc1..rc5`, the built `emu/hnsrun`, the mGBA 0.10.5 build (`mgba/`), the save ladder (`emu/saves`), the libretro cores (`cores/`), the English reference runs (`runs/tour_en`, `runs/mapwalk_en`), working notes (`notes/*.md`) | nothing in it is version-controlled or backed up. Section 2.6 says how to rebuild each piece from the fork |

The Spanish (`SergioBonet/hns_es`) and French (`nhykola/HeartAndSoul-FR`) forks were used only
as a cross-check, never as source text (`STYLE.md` §1).

### 1.2 Branches

| Branch | What | Rule |
| --- | --- | --- |
| `master` | identical to upstream `167aa6d537` | never commit to it |
| `he/main` | the translation; the release branch | feature branches merge into it with `--no-ff` |
| `he/renderer` | the Hebrew engine with the **English** strings. It is the drift baseline (`HNS_BASELINE`) and the chunk source | every engine or graphics commit is cherry-picked onto it; text commits never are |
| `he/fonts`, `he/graphics`, `he/naming-keyboard`, `he/preview`, `he/upstream-fixes` | feature branches, already merged | kept for history |
| `he/fix-*` | one fix topic each (for example `he/fix-k5-cosmetics`, `he/fix-vr-dex`), already merged | merge title `Merge he/<branch>: <what it brings>` |

On GitHub (2026-10-22): `master` `167aa6d537`, `he/main` `4a9c6858b1`, `he/renderer` `9e9e82ab14`,
and the 16 other `he/*` branches.

The local branch `he/fix-screens` (worktree `../pokehns-heb-screens`, at `he/main`) is **not** on
GitHub. Whether it holds work in progress is unverified.

### 1.3 Worktrees the tools expect

| Folder | Content | Used by |
| --- | --- | --- |
| `.` | `he/main` (or your feature branch) | everything |
| `../pokehns-heb-engine` | `he/renderer` | `drift.py`, `make_chunks.py`, `units.py --tree` (`HNS_BASELINE`) |
| `../pokehns-en` | detached at `Release-v2.0.6`, with `make hns` built | `audit.py --baseline`, `rom_sweep.py`, the save ladder (`HNS_UPSTREAM`, `HNS_EN_ROM`) |
| `../pokehns-release` | detached at the release commit | `tools/hebrew/release/*.sh` (`HNS_RELEASE_WORKTREE`); the build script removes and re-creates it |

`python3 tools/hebrew/paths.py` prints every location the tools resolved.

### 1.4 What must never be published

- **ROMs, ELFs and maps** (`*.gba`, `*.elf`, `*.map`) and **saves** (`*.sa*`). A built ROM is
  the copyrighted game, and a DMCA notice can take the public fork down with it. They are
  git-ignored (`.gitignore:4-5, 26, 29`), and `build/` is ignored too (`.gitignore:31`). A ROM
  goes only to the private builds repository, one per milestone. The CI workflow never uploads
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
| Python 3 | 3.11.9 (CI: Ubuntu 24.04's python3) | standard library only, except `tools/hebrew/fontcells.py` |
| Pillow | 12.2.0 | `python3 -m pip install Pillow`. Only `fontcells.py` needs it; the harness writes PNGs itself |
| cmake | 4.4.3 | only for building mGBA for the harness |

**Linux (what CI installs, `hebrew.yml:22-25`):**

```bash
sudo apt-get install -y --no-install-recommends binutils-arm-none-eabi gcc-arm-none-eabi \
     libnewlib-arm-none-eabi libpng-dev python3
```

On ubuntu-24.04 this gives gcc-arm-none-eabi 13.2. It builds and tests fine, but it is **not the
release toolchain**: its ROM differs from the release ROM (for example, EWRAM 248320 B against
248324 B with devkitARM). Releases are always built locally with devkitARM.

Not tried: a Linux host build with devkitPro pacman, and the minimum Python version (only 3.11.9
and Ubuntu 24.04's python3 have run the tools).

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

**Unverified:** this exact sequence has not been run end to end on a fresh machine. The 0.2
rebuild in section 2.7 was run from a `git clone --shared` of the reference repository.

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
| `make hns -j12` | `pokehns.gba`, `.elf`, `.map` | `build/hns` | the release ROM. `hns` is detected only when `$(BUILD)` or the **whole** goal list is exactly `hns` (`Makefile:21`). Not a `RELEASE=1` build, so asserts stay live (`Makefile:63`, `Makefile:632`) |
| `make hns RTL_CLIP_REPORT=1 -j12` | `pokehns-clip.gba`, `.elf`, `.map` | `build/hns-clip` | diagnostic ROM that logs every glyph drawn outside its window (`Makefile:36-41, 176-177`; `src/text.c:1047`). **Never shipped.** Builds next to the release build without a clean |
| `make hns RTL_STRING_REPORT=1 -j12` | `pokehns-strrep.gba`, `.elf`, `.map` | `build/hns-strrep` | diagnostic ROM that records every ROM string copied or printed, read by `tools/hebrew/strcov.py` (`Makefile:42-47, 185-187, 632-643`; hooks in `src/string_util.c`). **Never shipped.** Every hook is under `#if RTL_STRING_REPORT` and followed by `#line`, so the release ROM is byte-identical with or without them |
| `make check BUILD=hns -j12` | `pokehns-test.elf`, `pokehns-test-headless.elf`, results on stdout | `build/hns-test` | the upstream test suite. Judge the result with `check_tests.py` (section 4.3) |
| `make BUILD=hns -j2 pokehns-test.elf` | test ELF only | `build/hns-test` | what CI builds (`hebrew.yml:80`) |
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
- The local English build has CRC32 `FB9F58C5`, but the official 2.0.6 UPS output is `01713508`.
  Why they differ was never recorded (**unverified**).

### 2.6 Harness and the pieces that are not in the fork

| Piece | How to get it from the fork | Reference machine |
| --- | --- | --- |
| `hnsrun` (headless libmgba runner) | build mGBA 0.10.5 in a **permanent** folder, then the runner (`tools/hebrew/emu/README.md:21-45`); set `HNS_RUNNER` if you keep it outside `tools/hebrew/emu/` | `<private>/emu/hnsrun`, rpath to `<private>/mgba/build` |
| save ladder `ladder1_newgame.sav` … `ladder6_postgame.sav` | on the **English** ROM: `hns.py --rom "$HNS_EN_ROM" run $E/scripts/ladder1_newgame.txt OUT --save OUT/none.sav --save-out "$HNS_SAVES/ladder1_newgame.sav"`, then `$E/scripts/make_ladder.sh` (`emu/README.md:99-109`) | `<private>/emu/saves` (each 131088 B = 128 KiB flash + 16-byte RTC footer) |
| unit chunks (the sweep's labels) | `python3 tools/hebrew/make_chunks.py all` → `build/hebrew/units`, 7,209 labels, the same set 0.2 was swept with | `<private>/translation/units` (these also hold the Hebrew) |
| **translated** unit chunks | none: only `<private>` has them. `sweep.py selftest` and `sweep.py --translated` need them | `<private>/translation/units` |
| `crosscore` (libretro frontend) | `cc -O2 tools/hebrew/emu/crosscore.c -o build/hebrew/crosscore` | |
| libretro cores | `vbam`, `vba_next`, `gpsp`, `mednafen_gba`, `skyemu` `_libretro.dylib` in `build/hebrew/cores`; the mGBA core is RetroArch's own (`$HOME/Library/Application Support/RetroArch/cores/mgba_libretro.dylib`). **Where the 0.2 cores were downloaded from was not recorded** | `<private>/cores` |
| English map walk | `python3 tools/hebrew/emu/mapwalk.py "$HNS_EN_ROM" "$HNS_SAVES/ladder6_postgame.sav" build/hebrew/mapwalk_en` | `<private>/runs/mapwalk_en` |
| English tour run (for side-by-side review) | `python3 tools/hebrew/emu/hns.py tour "$HNS_EN_ROM" build/hebrew/tour_en`. **Unverified:** whether all 24 tours run on the English ROM; the 0.2 reference run held 18 (no naming, cardgear or dex_forms tours) | `<private>/runs/tour_en` |
| width budgets | `tools/hebrew/data/budgets.json` is the canonical source; `docs/hebrew_translation.md:86` still cites the private `notes/budgets.md` | `<private>/notes/budgets.md` |

The mGBA build that 0.2 used is tag 0.10.5 (`26b7884`), with Qt, SDL, GL, FFmpeg and Lua off.

Smoke test for the runner:

```bash
mkdir -p build/hebrew/hnsrun-check
printf '60 -\nshot boot\nquit\n' | "${HNS_RUNNER:-tools/hebrew/emu/hnsrun}" pokehns.gba build/hebrew/hnsrun-check
# OK: booted 240x160 rtc=1767268800
# shot boot @60
# OK: 60 frames pc=000001F8
```

**Unverified:**

- whether `make_ladder.sh` gives byte-identical saves on another machine (its header says
  "Deterministic: the same ROM gives byte-identical saves");
- building mGBA, `hnsrun` and `crosscore` on Linux.

The fork's `tools/hebrew/` copies are canonical. `<private>/emu` and `<private>/tools` hold older
copies with hard-coded paths. The one exception is `tours/naming_nickname.txt`, where the private
copy is newer (section 8.1).

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

- A different compiler gives a different SHA-1 (CI's GCC 13, any other devkitARM). Record the
  toolchain with every build.
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
| `graphics/**` | labels drawn into PNGs (and a few `.bin` tilemaps) | edited PNGs, committed as engine or asset commits; the drawing scripts are not in the fork | 129 |
| `test/hebrew_battle_messages.h`, `test/bag.c`, `test/text.c` | test expectations that depend on the Hebrew | `tools/hebrew/testmsgs/`, or a direct edit | 3 |

**Left in English on purpose:**

- dead labels (`tools/hebrew/data/live_labels.json`, key `dead`) and unreachable Emerald maps
  (`tools/hebrew/data/inventory.json`, `reach_class` `dead`);
- the R+START debug menu (`src/debug.c`, `data/scripts/debug.inc`), except two labels
  (`STYLE.md` §5);
- braille;
- Latin literals that code compares (the Odd Egg names, the mystery-gift sample code).

`status_report.py:23-51` (`KEPT_LATIN`) lists the deliberate Latin per file.

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
    {NO}`, and may reorder only `{B_BUFF1..3}` among themselves (`drift.py:30-33`).
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
  - the battle debug menu translated and the R+START menu English (Q118, Q120).

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
| overworld dialogue, signs, battle text | normal | 208 px per line, **200 px on a line ending in `\l` or `\p`** (the down arrow sits inside the box, `src/text.c:1862-1866`), 2 lines |
| phone call | normal | 192 / 184 px, 2 lines |
| item description | normal | 102 px × 3 |
| summary move description | normal | 152 px × 2 |
| Pokédex entry | normal | 224 px × 3 |
| bag item name / shop item name / battle move name | narrow | 88 / 84 / 64 px |
| healthbox name / party nickname | small | 55 / 40 px |

**Hard byte limits** (`namecheck.py:18-22`):

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
  6,525 rows. The tools read `proposed_hebrew`.
  - Status `inherited` (1,946) comes from the FireRed fork.
  - Status `proposed` (4,578) is new and has not been checked against an official Hebrew source.
  - One row is `todo`.
- `translation/hebrew/glossary_sources.csv`: `kind,constant,english,source,pattern` (5,529 rows).
  `make_chunks.py` uses it to pre-fill name fields.

**Where a name comes from** (`transliteration_rules.md` §0):

1. the FireRed fork;
2. the Pokémon Israel Pokédex;
3. the rules in that file.

Keep families together; `python3 tools/hebrew/translit_stats.py 'EON$'` lists the precedents.

**Renaming or adding a name** is a checklist; no tool propagates a rename:

1. Commit `glossary.csv` alone, **before** any text that uses the name.
2. `python3 tools/hebrew/namecheck.py --all` should print `rows 6524, still empty 0, problems 0`;
   then run `python3 tools/hebrew/glossary_widths.py` (`0 over budget`).
3. Change every dialogue use (`git grep` the old Hebrew and the English), one file per commit.
4. For trainer or map names, run `python3 tools/hebrew/apply_names.py --dry-run`, then without
   `--dry-run`.
5. For species, run `python3 tools/hebrew/gen_dex_alpha.py` and commit `pokedex_orders.h` alone.
6. Update test expectations where order or text changes. For example, `4c6ba54599` updated
   `test/bag.c` for the berry names.
7. After a bulk glossary edit, diff the row **keys** between revisions (section 6.2): a rewrite
   once dropped 5 rows silently.

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

- **`units.py apply` overwrites Hebrew without comparing.** It checks a unit's `en` against the
  tree only when the tree string has no Hebrew (`units.py:167, 269`). Re-applying an old chunk
  silently undoes later fixes, such as the review decisions. For a fix to existing Hebrew, edit
  the file directly.
- **The token rules differ between tools.** `units.py` and `checkunits.py` allow only `{POKE}`,
  `{PKMN}` and `{POKEBLOCK}` to be dropped, and no reordering (`units.py:35`,
  `checkunits.py:26`). `drift.py` also allows dropping `{ID}{NO}` and reordering the B_BUFFs.
  Strings that use those freedoms (`src/battle_message.c` #486, #488, #517, #573) cannot go
  through `units.py apply`; edit them directly.
- `units.py` handles `.inc`, `.s`, `.c` and `.h` only. `.party` and `.json` go through
  `apply_names.py`.
- A blank line inside a `.string` block ends the unit (`b81dddd2b3`).
- `gen_dex_alpha.py --check` only prints the first 15 entries; it compares nothing. To check,
  copy `src/data/pokemon/pokedex_orders.h` into `SCRATCH/src/data/pokemon/`, run
  `gen_dex_alpha.py --tree SCRATCH`, and `diff` the two.
- `namecheck.py --all` keys rows on `(kind, constant)` (`namecheck.py:102`), so a duplicate key
  hides a row. It reports 6,524 of 6,525 rows, and it cannot detect a lost row or a truncated
  Hebrew value.
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
| one file vs English | `drift.py` | anything changed outside strings, token order, `$`, charset | 3 s for 683 files |
| whole tree | `audit.py --baseline ../pokehns-en` | WIDTH, LINES, BUFFER, BYTES, TERMINATOR, CHARSET | 28 s |
| glossary | `namecheck.py --all` | byte limits, final letters, duplicates | instant |
| tool tests | `python3 -m unittest discover -s tools/hebrew/tests` | the tools themselves (40 tests) | 4 s |
| game logic | `make check BUILD=hns` + `check_tests.py` | a test that passes upstream but fails in Hebrew | about 15 min locally (inferred from file times), 21 min in CI |
| screens | `hns.py tour` (24 tours) | crashes, timeouts; screenshots for review | 40 s |
| glyphs outside windows | `hns.py tour --clip`, `sweep.py` on the clip ROM | every glyph drawn outside its window | about 2 min for 7,209 labels |
| every map | `mapwalk.py` | CRASH, maps that never give control back | 329 s for 543 maps |
| saves | `ladder.py run scripts/ladder_validate.txt` | English 2.0.x saves still load and work | about 1.5 s per save |
| other emulators | `crosscore` + libretro cores + `ccdiff.py` | renderer differences between cores | about 2 s per core |
| English left in ROM | `rom_sweep.py` | English runs in the binary | 4 s |
| eyes | `pairsheets.py`, `hns.py tourdiff`, reviewers plus refuters | overlap, mirroring, digit order, glyph shapes, wrong translation | per release |

Two rules from the original brief:

- Mark anything not seen on screen as unverified.
- Test the exact `.gba` you ship, never a build tree.

### 4.2 Static checks: the CI `audit` job, run locally

CI creates the two worktrees from `origin/he/renderer` and `origin/master` (`hebrew.yml:41-46`).
Locally, the tag `Release-v2.0.6` (fetched in section 2.3) stands in for CI's `origin/master`.

```bash
set -o pipefail
# 1. drift (hebrew.yml:48-52): only strings may differ from he/renderer
git diff --name-only Release-v2.0.6...HEAD -- data src | grep -E '\.(inc|s|c|h)$' | xargs python3 tools/hebrew/drift.py --quiet
#    he/main: exit 0; 683 files, 0 FAIL, 384 files with warnings only (LATIN / UNTRANSLATED)
# 2. layout audit (hebrew.yml:54-55)
mkdir -p build/hebrew && python3 tools/hebrew/audit.py --baseline ../pokehns-en --report build/hebrew/audit.txt; head -3 build/hebrew/audit.txt   # nothing on stdout with --report
#    audit ...: 41195 strings (24712 translated)
#    == translated strings: 0 errors, 42 warnings, 84 suppressed by baseline ../pokehns-en
#    == English (untranslated) strings, baseline only: 448 errors, 0 warnings   <- informational
# 3. glossary (hebrew.yml:57-58)
python3 tools/hebrew/namecheck.py --all
#    rows 6524, still empty 0, problems 0
# 4. tool tests (hebrew.yml:60-61)
python3 -m unittest discover -s tools/hebrew/tests
#    Ran 40 tests ... OK          (CI: OK (skipped=1), it has no English ROM)
```

**How to read the results**

- **drift errors** (exit 1) are `STRUCTURE`, `TOKENS`, `TERMINATOR`, `CHARSET` and `SHRUNK`.
  Warnings (`PAGES`, `LATIN`, `UNTRANSLATED`) never fail the run unless you pass `--strict`.
  Section 6.2 lists every kind.
- **audit:** the exit status is 1 only for a Hebrew error that the baseline does not suppress.
  - The 42 warnings are `FIT`: 12 item names and 30 move names that fit only after the game falls
    back to a narrower font.
  - A finding reads `w item_name FIT 79 > 72 p1 r1 [summary held item FONT_NORMAL] (...)
    src/data/items.h:3095`: kind, check, measured > budget, page and row, where it is drawn, and
    the source line.

**What CI's drift step skips:** `.json` and `.party` files. Run
`python3 tools/hebrew/drift.py src/data/region_map/region_map_sections.json` by hand; it passes
today.

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

- **Ignore make's exit status.** On macOS the 0.2 log ends with `make: *** [check] Segmentation fault: 11`.
  The likely cause is the hydra runner's summary arrays: they have room for 50 × 32 entries but
  are indexed by the running fail count (`tools/mgba-rom-test-hydra/main.c:40-41, 764-765, 819-826`).
  This was reasoned from the code, not proven (**unverified**).
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
- `check_chunked.py` was not run locally for this handoff; only its chunk plan was computed.

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
export HNS_RUNNER=<path to hnsrun> HNS_SAVES=<save ladder folder>
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
12:00 UTC), and `HNS_LOG=1` echoes every mGBA log line.

### 4.5 Tours, clip reports, the dialogue sweep

**Tours.** `tools/hebrew/emu/tours/*.txt` holds 24 tours, one per screen family:

- `menu_*`: bag, Center/PC, fly map, Mart, Name Rater and day care, options, party, Pokédex,
  PokéGear, save, trainer card;
- `cardgear_*`, `dex_forms`;
- `naming_player`, `naming_nickname`;
- `battle_*`: wild, trainer, catch, level-up, effects, whiteout.

`menu_00_setup` builds the base save that the menu tours start from. Each file's header says what
it covers.

```bash
python3 $E/hns.py tour pokehns.gba OUT                              # all 24: "24 tour(s): 24 OK, 0 not OK", 40 s
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
  right**: a stale tour still reports OK (section 8.1).

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
python3 <repo>/tools/hebrew/emu/sweep.py run <repo>/pokehns-clip.gba sw --shots clip   # rc5: 7209 labels, OK 7062, SKIP 147, 121.7 s
python3 <repo>/tools/hebrew/emu/sweep.py run CLIP.gba sw --batch B20 --limit 40       # a subset
python3 <repo>/tools/hebrew/emu/sweep.py report sw         # rebuild sw/sweep.json + sw/report.txt
python3 <repo>/tools/hebrew/emu/sweep.py selftest CLIP.gba st   # proves the detector; needs TRANSLATED units
```

- **Statuses:** CRASH, HANG, ABNORMAL, CLIP, OK, SKIP. `SKIP` is a label not assembled into
  this build: 147 Emerald and Kanto labels.
- **Selections:** `--label`, `--labels-file`, `--match`, `--file`, `--batch`, `--translated`,
  `--sample`, `--offset/--limit`; add `--resume` to continue a run.
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
# 661 files -> ...: {'seen on screen': 510, 'translated': 132, 'blocked': 19}   (rc5 reproduces STATUS.md byte for byte)
```

- Without `--sweep`, every "seen on screen" row falls back to "translated".
- "Seen on screen" means **the harness rendered the label**, not that a person read it.
- STATUS counts a string as Hebrew if it holds any Hebrew letter (`status_report.py:81`), so mixed
  Latin-and-Hebrew lines pass (section 8.2).

### 4.6 Map walk, save ladder, cross-core, ROM sweep

```bash
python3 $E/mapwalk.py pokehns.gba "$HNS_SAVES/ladder6_postgame.sav" OUT [--only RE] [--max N]
# rc5: 543 maps in 329 s: {'OK': 507, 'HELD': 36}
python3 $E/ladder.py --rom pokehns.gba run $E/scripts/ladder_validate.txt OUT --save "$HNS_SAVES/ladder2_badge1.sav"
# continue, leave the Center, open Pokédex, party, bag, card, PokéGear: 13 screenshots, exit 0
python3 tools/hebrew/rom_sweep.py pokehns.gba --json OUT.json
# 6283 text runs (6365 candidates), 6255 still English, 4.2s   exit 1 (always, on this build)
```

- **Map walk:**
  - `HELD` means the game never gave control back within the frame budget. Compare with an
    English walk before calling it a bug: 34 of the 36 HELD maps also hold in English (Frontier
    rooms, Pyramid, Tents, Union Room). The other 2 are Battle Arena rooms, where the Hebrew run
    won the first battle.
  - Treat any `CRASH` as real until the English ROM with the same save crashes the same way.
    The English walk once crashed in the Dome pre-battle room (`pc=0A0E8ECC`); that was never
    investigated.
- **Save ladder:** six saves made **on the English ROM**, then loaded in the Hebrew one. Rung 1
  validation exits 1 by design (`leavecenter: blocked inside 1.4`): the save is in the bedroom,
  not a Center.
- **ROM sweep:** do not gate on its exit status. Of the 6,255 runs, 0 are on live labels, 3,265
  on dead Emerald labels, 16 debug-only, and 2,974 untracked (mostly `data/event_scripts.o` and
  `src/credits_hns.o`). Compare its `--json` with the previous candidate's.
- **Cross-core:** `crosscore CORE.dylib ROM OUTDIR [save] < tools/hebrew/release/crosscore_menus.txt`,
  then `python3 tools/hebrew/release/ccdiff.py REF_DIR DIR...`. Expected differences:
  - intro, start-menu clock and animation frames differ on every core;
  - VBA-Next has no RTC, so it shows the "battery has run dry" notice;
  - SkyEmu segfaults the frontend, also on the English ROM.

### 4.7 CI

`.github/workflows/hebrew.yml` runs on a push to `he/**`, a pull request to `he/main`, and by
hand. It uses Ubuntu's gcc-arm-none-eabi.

| Job | Steps | Last green time |
| --- | --- | --- |
| `build` | `make hns -j$(nproc) -O`, then the clip ROM | 6m34s |
| `audit` | the two worktrees, drift, audit, namecheck, tool tests | 1m0s |
| `check` | test ELF at `-j2`, with a `[mon]` memory line every minute; `check_chunked.py --skip-crashing --chunk-timeout 900`; `check_tests.py`; artifact `check-log` (14 days) | 21m5s |

```bash
gh run list -R ronyeh2/pokehns-expansion-heb --workflow hebrew.yml --limit 8
gh run view <id> -R ronyeh2/pokehns-expansion-heb --log | grep -E 'results,|NEW FAILURE|Ran [0-9]+ tests|translated strings'
```

- **Push `he/renderer` before `he/main`** when an engine commit is involved. CI's drift
  compares with `origin/he/renderer`, so a missing cherry-pick fails it.
- **Act on these annotations before they break CI:**
  - `ubuntu-latest` moves to Ubuntu 26 from 2026-10-19. A new image brings a new
    gcc-arm-none-eabi; if compiling starts to fail, pin `runs-on: ubuntu-24.04` first.
  - `actions/checkout@v4` and `upload-artifact@v4` run on Node 20, which is deprecated.
- The upstream workflow `.github/workflows/build.yml` runs on any pull request with
  `UNUSED_ERROR: 1`, and does not build `hns`. Whether it would fail a pull request into `he/main`
  is **unverified**.
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
   (`DECISIONS.md:1384-1398`).
5. **When a screenshot is ambiguous:** dump the pixels, read the string from RAM, or simulate
   the pen. Never argue from a downscaled image.

The review prompts and any script that ran the reviewers are not in the fork or the private
folder (**not found**).

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
- the save ladder;
- `make_chunks.py all`;
- `crosscore` and the cores;
- the English map walk at `build/hebrew/mapwalk_en/mapwalk.json` (`HNS_EN_MAPWALK`).

**Steps**

1. **Pick the commit.** `he/main` with CI green and section 4.2 clean.

2. **Build in a clean worktree.** The script removes and re-creates `../pokehns-release`
   (`HNS_RELEASE_WORKTREE`); it refuses a folder that is not a worktree of this repository. It accepts any other worktree of this repository and removes it with `git worktree remove --force`, which discards uncommitted changes: never point `HNS_RELEASE_WORKTREE` at `../pokehns-en`, `../pokehns-heb-engine` or a feature worktree, and read the `worktree` line of `--check` first.
   ```bash
   RC=build/hebrew/release/rcN
   tools/hebrew/release/build_release.sh --check he/main "$RC" && tools/hebrew/release/build_release.sh he/main "$RC"
   ```
   - `RC` gets `pokehns.gba/.elf/.map`, `pokehns-clip.gba/.elf`, the build logs, and
     `gbafix.log`, which must end in `gbafix: header already valid`.
   - It also gets `build_info.json` with the commit and the size, SHA-1 and CRC32 of both ROMs.

3. **`make check` on the same commit:**
   ```bash
   (cd ../pokehns-release && make check BUILD=hns -j12) > "$RC/make_check.log" 2>&1
   python3 tools/hebrew/check_tests.py "$RC/make_check.log" | tee "$RC/check_tests.txt"
   ```
   How the 0.2 log was produced was not recorded; this is the README's command.

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
   - **Fix the stale nickname tour first** (section 8.1); otherwise its frames differ from 0.2's
     while reporting OK.

5. **Visual review** (section 4.8). Record the findings in `RC/visual_findings.json`. A finding
   that needs a fix means a new candidate, `rcN+1`.

6. **Edit `tools/hebrew/release/notes.json`** for the new release.
   - `release` must match the ROM name.
   - Also edit `known_issues`, `not_tested` (never empty), `visual_review` and `crosscore_notes`.
   - `static_checks` is typed from the CI run of the release commit, because the scripts do not
     run those checks.
   - Update `map_walk.hebrew_only_held` to what the data shows.

7. **Write the report:**
   ```bash
   python3 tools/hebrew/release/make_testing_md.py "$RC" pokehns-he-2.0.6-X.Y.gba "$RC/TESTING.md"
   ```
   It exits 1 instead of writing a sentence that its inputs contradict:
   - a changed header;
   - a failing selfcheck;
   - a clipped, crashed, hung or abnormal label;
   - a crashed map;
   - held maps that `notes.json` does not explain.

   Check every number against the logs anyway.

8. **Publish in the private builds repository** (`<builds>`):
   - Copy `RC/pokehns.gba` as `pokehns-he-2.0.6-X.Y.gba`.
   - Append its line to `SHA1SUMS` and check with `shasum -c SHA1SUMS`.
   - Rename the old `TESTING.md` to `TESTING-<previous>.md` and add the new one.
   - Add a row to the README table: version, file, source commit, report.
   - Commit **one ROM per milestone**, authored with the fork owner's GitHub noreply identity
     (`git config user.email` is set in that clone). The message names the source commit, SHA-1
     and CRC32, as in `9f6aef6`.
   - Push as in section 7.3.

9. **Back in the fork,** in separate commits:
   - regenerate `STATUS.md` from `RC/tests/sweep/sweep.json`;
   - record the review outcomes in `DECISIONS.md`.

**Open policy question for the project owner.** The brief says a ROM that has not been played by
hand is not committed. 0.1 and 0.2 were committed with hand play listed under "Not tested". Do
not change this silently.

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
| Release SHA-1 differs from `SHA1SUMS` | `arm-none-eabi-gcc --version` | another toolchain (CI's GCC 13, another devkitARM) | build with devkitARM r68 / GCC 16.1.0 in a clean worktree of the named commit | — |
| `gbafix.log` says `HEADER CHANGED` | `gbafix.log` | the build did not fix the header | investigate before releasing; never seen so far | — |
| Harness stops working months later | `otool -L $HNS_RUNNER` (`@rpath/libmgba...`) | the runner's rpath points at a deleted mGBA build | build mGBA in a permanent folder and rebuild `hnsrun`, or set `HNS_RUNNER` | — |
| Text breaks the compile (seen in the Spanish fork, not here) | the compiler error line | an ASCII `"` in a C literal or `\"` in `.string`; a name longer than its fixed array | the charmap's `”`; `checkunits.py` / `namecheck.py` enforce byte limits before a build | — |

### 6.2 Static checks

| Symptom | Check | Cause | Fix | Commit |
| --- | --- | --- | --- | --- |
| drift `E STRUCTURE changed outside strings` | the `-`/`+` lines in the output | an edit outside a string; a raw `"` inside `.string` (also gives `string count 15 -> 14`); an engine commit missing from `he/renderer`, or a stale `../pokehns-heb-engine` | revert it; write `”`; cherry-pick the engine commit onto `he/renderer` and update that worktree | — |
| drift `STRUCTURE label order A vs B` | | blocks moved or merged | restore the English block order | — |
| drift `E TOKENS <label>: ['{PLAYER}'] -> []` | | a placeholder was dropped or reordered | keep English order. Droppable: `{POKE} {PKMN} {POKEBLOCK} {ID} {NO}`; reorderable: `{B_BUFF1..3}` | `43e43941b4`, `dbf3d07e01` |
| drift `E TERMINATOR`, `E CHARSET <label>: €`, `SHRUNK` | | `$` lost or added; a character the charmap cannot encode; the file is under 60% of the English bytes | restore the `$`; use the charmap form; restore the file | — |
| drift `w PAGES 2 -> 1`, `w LATIN`, `w UNTRANSLATED` | | warnings only | `\p` changes only when a page would not fit; translate the Latin or confirm it is on `LATIN_OK` (`drift.py:48-52`) | — |
| drift flattened `#if/#else` string branches | | an old drift could not parse literals split by preprocessor lines | translate every branch; drift parses them now | `c3aa635b6a` |
| audit `E ... WIDTH 278 > 200 ... (prompt line)` | `textwidth.py` | the line is too wide; a line ending in `\l`/`\p` gets 200 px | `wrap.py`, or shorter wording | `57ba9f052e` (prompt budget) |
| audit or checkunits `BYTES` | `namecheck.py --all` | a hard field limit; for example the Frontier trainer name field is 7 bytes, not 8 | a shorter form for that copy | `ca1e85587c` |
| audit `FIT` warning | | fits only in the narrower fallback font | allowed; look at it on screen | — |
| checkunits `w DIGITS ['20'] -> ['02']` | | a number reversed or lost | write digits in reading order | — |
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
| `make check` ends in `Segmentation fault: 11` and prints no summary (macOS) | `check_tests.py LOG` | probably the hydra summary arrays (section 4.3), **unverified** | ignore make's status; judge with `check_tests.py` | — |
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
| `the save ladder is not set (HNS_SAVES)` | `python3 tools/hebrew/paths.py` | no default for the saves | set `HNS_SAVES` (section 2.6) |
| tour `ERROR ... constant SPECIES_TYPHLOSION not found in <dir>/include` | where the ROM is | the ROM was copied out of its source tree | set `HNS_SRC=<tree>`, or use the in-tree ROM (the release script does) |
| `path too long for hnsrun (N chars)` | the length of OUTDIR | hnsrun keeps 127 characters (`hnsrun.c:200`); `sweep.py:367-373` guards at 120 | `cd` to a short folder; the sweep passes relative paths when shorter |
| `sweep: no script units in .../build/hebrew/units` | `ls $HNS_UNITS` | no units | `python3 tools/hebrew/make_chunks.py all` |
| `selftest: no translated label with a long enough two-row page` | | the units have no Hebrew (`make_chunks.py` output) | point `HNS_UNITS` at translated chunks (only `<private>` has them) |
| `sweep.py selftest --label X`: `TypeError: unhashable type: 'list'` | | `--label` is an append list (`sweep.py:1102`), and `sweep.py:1021` wraps it again | omit `--label`, or change line 1021 to `cands = list(a.label)` |
| `--clip`: `... is not an RTL_CLIP_REPORT build` | | a release ROM | use `pokehns-clip.gba` |
| `selfcheck` prints FAIL | | a saved struct changed size (`include/global.h`, `main.h`) | `HNS_WORK=<scratch> bash tools/hebrew/emu/probe/measure.sh`, update `OFF`/`SIZES` in `hns.py`. It also misses a field reordered inside an unchanged size, so rerun the probe after any change to those headers |
| `render`: `'waitcb2' needs hns.py run (not plain hnsrun)` | | a live op in a script for bare hnsrun | use `hns.py run` |
| tour TIMEOUT or CRASH | `OUT/TOUR/_timeout.png`, `_crash.png`, `run.log`; `hns.py where <pc>` | a wait never matched; a bad pointer | fix the script or the ROM |
| tour OK, but frames differ from the previous candidate | `hns.py tourdiff` | a stale script, or a real change | look at each DIFF (section 8.1) |
| savestate gives plausible nonsense | | `ss`/`sl` states work for the same build only (`hnsrun.c:23`) | cold-boot from the battery `.sav` after a rebuild |
| values read from the save block are wrong after a warp | | the save block moves on every map load and battle | use `@SB1@`/`@SB2@`/`@POS@`, which are re-read per line; never cache them |
| a battle differs between runs | | input timing moves `Random()` | `pinrng` (`hns.py:1500-1539`) |
| map walk `HELD` | the same map on the English ROM | a scripted sequence the B-only walker cannot finish | a harness limit unless English behaves differently |
| ladder1 validation exits 1 (`leavecenter: blocked inside 1.4`) | | rung 1 is the bedroom, not a Center | expected |
| `rom_sweep.py` exits 1 with about 6,255 runs | | dead Emerald text compiled in | informational; diff against the previous candidate |
| cross-core: VBA-Next differs on whole frames; SkyEmu exit 139 | | no RTC in VBA-Next; SkyEmu crashes the minimal frontend | expected |
| a tester reports a "crash" | does the screen show an assert message? | `make hns` keeps asserts (`RELEASE ?= 0`, `Makefile:63`); the ROM contains `AssertfCrashScreen` | read the assert. R+START (the debug menu) is compiled in (`include/config/debug.h`); R is also the DexNav button |

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
- **Pre-2.0 (1.2.1) saves do not load.** The sector layout differs (SaveBlock3), and 2.0.6
  migrates only 2.0.x saves (`src/save.c:930-980`). This comes from a code trace in
  `<private>/scratch/save12/REPORT.md`; no 1.2.1 save was ever loaded (**unverified**).
- **Leave the Pokémon Center first** after loading a save from another build. This is the
  official upgrade step; see `tools/hebrew/emu/scripts/continue.txt:5-7`.

---

## 7. Rules and conventions

### 7.1 Commits

- **One file per text commit.** 959 of the 1,012 non-merge commits on `he/main` touch one file.
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
- **No AI attribution**: no `Co-Authored-By` trailer, no "Generated with" line. All 1,030 commits
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
  `he/main` has 18 such merges.
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
| **Stale nickname tour.** `tools/hebrew/emu/tours/naming_nickname.txt:8` still says "a page swap keeps the cursor's column", the rule before `41d363d8ed`. Last changed in `98e5af4a55`. On the 0.2 ROM it reports OK, but 8 of its 35 frames differ from rc5's: it types `CDE` for `ABC`, and the `2` of `פיקה 2` is never typed | `hns.py tour pokehns.gba nn --only '^naming_nickname$'`, then `tourdiff` against rc5 → `30 identical, 8 differ` (run for this handoff; the two frames viewed). The fixed copy is `<private>/emu/tours/naming_nickname.txt` | port that file as its own tools commit, then confirm `tourdiff` shows 0 differences against rc5 |
| **Hebrew A–Z Pokédex order out of date** for ZACIAN, PAWMI, PAWMO and PAWMOT. `pokedex_orders.h` was generated in `51b35c64fe`, before the names review renamed them (`bb8db5c703`). The 0.2 ROM has this | `gen_dex_alpha.py --tree <scratch copy>` + `diff` → those 4 moved (run for this handoff) | run `python3 tools/hebrew/gen_dex_alpha.py`, commit `pokedex_orders.h` alone; check the Pokédex A–Z list on screen |
| **`sweep.py selftest --label` crashes** | `sweep.py:1021` vs `:1102` | `cands = list(a.label)` |
| **`make_testing_md.py` clip-count bug** (old private copy) | fixed in `tools/hebrew/release/make_testing_md.py` | — |
| Known issues shipped in 0.2 (`tools/hebrew/release/notes.json`) | `<builds>/TESTING.md` | each is a candidate fix: imperial dex height `”` left of the digits (found in code, not seen); dex stat-label shadow touches the border; a nickname geresh touches the portrait box; a colon at a page end touches the continue arrow; EXEGGUTOR-A spelled without the ק |

### 8.2 Content gaps

- **Latin left inside Hebrew strings.** The live ones now have glossary rows and Hebrew text
  (round 17; the 16 new rows are `proposed`). drift prints 133 `w LATIN` lines (it no longer
  caps them at 40 per file), and each is either kept on purpose or in text H&S does not reach:
  - kept: button names, game titles, the credits' team names, the Odd Egg interview's Easy Chat
    words in `src/data/help_window.h`, and the save-type name on the no-flash screen; the reasons
    are in `tools/hebrew/status_report.py` (KEPT_LATIN) and `tools/hebrew/drift.py` (LATIN_OK);
  - unreachable: Emerald maps and names, the Battle Tents, the TV shows and their PokéNews
    (`FLAG_SYS_TV_START` is defined as 0, `data/scripts/tv.inc:8`), the PokéNav match calls (66
    lines; their `FLAG_ENABLE_*_MATCH_CALL` and `FLAG_REGISTERED_*` flags are defined as 0 in
    `include/constants/flags_hns.h`, and `FlagGet(0)` is false), the Ruby/Sapphire berry fix,
    and the item descriptions this build does not compile.
  - `tools/hebrew/data/live_labels.json` still counts the match-call and TV labels as live: its
    builder follows references and ignores flags. Only Mom and Baoba can call.
- **Easy Chat contradicts the docs.**
  - `docs/hebrew_translation.md:149`, STATUS.md and TESTING.md say Easy Chat stays English, and
    `make_chunks.py:28` skips `src/data/easy_chat/`.
  - The tree holds 517 Hebrew and 491 Latin words, from 19 "Translate src/data/easy_chat/..."
    commits (for example `7a223ace31`, `36040b98f7`).
  - Why, and how the letter-indexed chat keyboard behaves with them, is **unverified**.
  - Decide before touching Easy Chat.
- **Questions for the owner from the string-coverage round** (round 16). None is fixed; each
  needs a decision:
  - the battle debug menu: the stat-up hold rows all as 'X +' like the other six, and the AI
    points page label ('עובר לפוקימון ' at the English width, or the species placed after the
    label under `TEXT_RTL`);
  - two faults of H&S 2.0.6 itself, the same in English: the Battle Dome style scoring assigns
    instead of adding, so only RISKY, RARE_MOVE and BALANCED can show; Scott's Silver and Gold
    Shields cannot be received. Release-note them, or fix them outside the translation;
  - with no flash chip the game shows the debug build's English assert screen before the
    no-flash message: ship an `NDEBUG` build (which changes Q120's debug menu) or keep it;
  - the Emerald maps outside the Battle Frontier cannot be walked into; the only path found, a
    poison white-out in the Battle Pike with SURVIVE POISON off, crashes in English too. A lead,
    **unverified**: the HNS build gives the non-hns maps a NULL map header
    (`tools/mapjson/mapjson.cpp:470-479`);
  - an H&S 2.0.6 art fault, the same in English: the Gen 4 battle UI's FROSTBITE tag is a copy of
    the BURN tag (row 6 of `graphics/battle_interface/gen4/status*.png`), so it would read כויה.
    Frostbite is off (`B_USE_FROSTBITE` FALSE) and only the debug menus can set it. Redraw the
    row as קור like `hns/status*.png`, or release-note it.
- **Questions for the owner from the Pokédex rounds** (rounds 16b and 17). Neither is decided:
  - the five Pokédex terms round 17 proposed: Hisui היסואי, Mt. Coronet הר הנזר (its glossary
    note gives the transliterated הר קורונט as the alternative), Ultra Wormhole חור תולעת
    אולטרה, Team Plasma צוות פלזמה and Rose רוז. None is checked against an official Hebrew
    source;
  - 'psychic power' in Pokédex prose: על-חושי (as in the PSY- move names) or פסיכי (as in the
    type name), applied across the tree.
- **Proposed names.** The 4,578 `proposed` glossary rows were never checked against an official
  Hebrew source or by a native speaker on screen.
- **Not seen by a person:**
  - nobody has played from a new game to the first badge;
  - nothing has run on real hardware (needs a 32 MiB cart, FLASH 128 KB save and an RTC);
  - no real 2.0.x save from a long playthrough has been loaded;
  - link features have not been tried;
  - no tour reaches the Frontier facilities, full contests, Trainer Hill, Battle Tents, mail, the
    credits, the Hall of Fame or every dex form page.
- **Unreachable English in the ROM** (resolved). `rom_sweep` lists 104 untracked English runs
  sourced to `BattleFrontier_BattlePyramidFloor_hns`. None can print: its 129 text labels have no
  referrer outside their own definitions, `tools/hebrew/data/inventory.json` marks the file dead,
  and the Pyramid's live text comes from `src/battle_pyramid.c` and `src/start_menu.c`, which are
  Hebrew.

### 8.3 Stale documentation (fix in docs-only commits)

| Where | Says | Reality |
| --- | --- | --- |
| `docs/hebrew_translation.md:86` | budgets come from `notes/budgets.md` | that file is private; the fork's source is `tools/hebrew/data/budgets.json` |
| `docs/hebrew_translation.md:145-148` | `{ID}{NO}` and `POKéGEAR` are open style calls | settled in 0.2 (K2 `מס'`, K3 פוקיגיר; `DECISIONS.md`) |
| `docs/hebrew_translation.md:149` | Easy Chat stays English | about half Hebrew (section 8.2) |
| `docs/hebrew_translation.md`, `tools/hebrew/README.md` | do not mention `tools/hebrew/release/` | they should link it |
| `tools/hebrew/wrap.py:8-9` (docstring) | dialogue 216 px, 208 on `\l`/`\p` | the code and `budgets.json` use 208 / 200 |
| `tools/hebrew/textwidth.py:100` | down arrow at `src/text.c:1175-1215` | now `src/text.c:1862-1910` |
| `STYLE.md:67-71, 80-81` | keep every token in order; three droppable tokens | `drift.py:30-33`: five droppable, B_BUFF1..3 reorderable |
| `units.py:35`, `checkunits.py:26` | three droppable tokens, no reorder | out of step with `drift.py` (section 3.7) |
| `<private>/translation/glossary.csv` | | differs from the fork's (first difference at line 184); the fork's is canonical |

Tests are missing for `units.py`, `drift.py`, `checkunits.py`, `make_chunks.py` and
`namecheck.py`. The 40 tool tests cover audit, check_chunked, cliptour, rom_sweep, textwidth and
wrap.

### 8.4 Things only on the reference machine (bus factor)

The private folder is not a git repository and has no backup. It alone holds:

- **the translated unit chunks.** `sweep.py selftest` and `--translated` need them;
- **release candidates rc1–rc5** (logs, review JSON);
- **the libretro cores**, with no record of their source;
- **the English reference runs** (they can be regenerated: section 2.6);
- **the working notes** (`notes/harness.md`, `sweep.md`, `lessons.md`, `graphics_*.md`). They
  describe how the graphics labels were drawn; the drawing scripts themselves are not in the fork.

Decide whether to move what is still needed into the fork (tools) or into the private builds
repository (data).

### 8.5 Facts not verified for this handoff

- A fresh `git clone` of the fork followed by section 2.3 end to end, and a Linux build with
  devkitPro pacman.
- That another machine with devkitARM r68 reproduces the 0.2 SHA-1.
- Why the local English 2.0.6 build (CRC32 `FB9F58C5`) differs from the official UPS output
  (`01713508`).
- The cause of the hydra segfault at the end of a full local `make check`.
- The command and job count that produced the 0.2 `make_check.log`; the wall time of a full local
  `make check`.
- Where the libretro cores came from; whether every core accepts mGBA's 131088-byte `.sav`.
- That `make_ladder.sh` gives byte-identical saves elsewhere; the harness on Linux.
- Whether all 24 tours run on the English ROM.
- Whether a pull request into `he/main` would fail the upstream "CI" workflow (`UNUSED_ERROR=1`).
- Whether the Ubuntu 26 runner image breaks the CI build.
- That an over-long species, item or move name is a hard compile error under GCC 16 (not tried).
- The cause of the English map walk's Dome crash.
- Whether `he/fix-screens` (local only) holds work in progress.
- How the stale A–Z entries and the imperial height look on screen.
- Loading a save written by the Hebrew ROM into the English ROM.

## Notes from the fresh-clone test

This document was followed end to end on a fresh clone; the release ROM it builds matched release 0.2 byte for byte (SHA-1 `07753efc…`, clip build `4d7cfac5…`). Points to keep in mind:

- Give every `HNS_*` variable as an absolute path: a relative one is resolved against the folder a command runs from. A sweep that finds no units prints `sweep: no script units in …`, selects 0 labels and still exits 0, so check that its `totals:` line is not empty.
- `audit.py --report` prints nothing on stdout; the summary is the head of the report, and `build/hebrew/` must exist first.
- `drift.py --quiet` prints no summary line: success is exit 0 with only `ok` lines and no `FAIL`.
- `drift.py` reports every renamed `Name:` line of a `.party` file as STRUCTURE (exit 1), so it is no check for those files.
- `run_release_tests.sh --check` only tests that some unit chunk exists: confirm `make_chunks.py all` wrote the folders `B01`–`B40`.
- `ccdiff.py --help` prints its usage line but exits 1.
- In the troubleshooting table, the drift `#if/#else` row's parsing came with the tools in `98e5af4a55`; `c3aa635b6a` is the text fix.
