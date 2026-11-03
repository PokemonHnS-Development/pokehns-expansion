# Headless harness

`hnsrun` is a small headless GBA runner on top of libmgba. It boots a ROM with an optional
battery save and reads commands from stdin: hold or tap keys, take screenshots, read and write
memory, wait for a value, pin bytes, save and load states. It stops with `CRASH` when the PC leaves
BIOS, ROM or RAM. The Python files drive it with addresses taken from the build's ELF.

| File | What it is |
| --- | --- |
| `hnsrun.c` | the runner (its command list is at the top of the file) |
| `hns.py` | driver: ELF symbols, a live runner session, the script language, warps, saves, `selfcheck`, `render`, screen tours, `tourdiff`, contact sheets |
| `ladder.py` | extra script commands for building saves (event scripts in RAM, start menu, leaving a Center) |
| `evasm.py` | assembles an event script with the source tree's own macros, to run it in RAM |
| `sweep.py` | shows every live script text label in the message box and reports CLIP / CRASH / HANG / ABNORMAL |
| `mapwalk.py` | warps into every H&S map, fights or reads through whatever starts, takes a screenshot of each |
| `tours/` | screen tours (`menu_*`, `battle_*`, `naming_*`, `dex_*`, `cardgear_*`); `_*.txt` are includes |
| `tours_mapwalk/` | the map walk as one scripted tour (warp, wait, snap per map) |
| `scripts/` | boot, new game, continue, the save-ladder scripts (`ladder*.txt`, `ladder/*.inc`), `make_ladder.sh` |
| `probe/` | `measure.sh` + `offsets.c`: re-measure the struct offsets `hns.py` uses when `selfcheck` fails |

## Build hnsrun

Build mGBA 0.10.5 as a shared library, then compile the runner against it. `MGBA_DIR` is your
mGBA checkout:

```bash
git clone --branch 0.10.5 https://github.com/mgba-emu/mgba.git "$MGBA_DIR"
cmake -S "$MGBA_DIR" -B "$MGBA_DIR/build" -DCMAKE_BUILD_TYPE=Release \
      -DBUILD_QT=OFF -DBUILD_SDL=OFF -DUSE_FFMPEG=OFF -DUSE_LUA=OFF \
      -DBUILD_GL=OFF -DBUILD_GLES2=OFF -DBUILD_GLES3=OFF -DUSE_EPOXY=OFF
cmake --build "$MGBA_DIR/build" --target mgba          # libmgba.dylib / libmgba.so

cc -O2 -I"$MGBA_DIR/include" -I"$MGBA_DIR/build/include" tools/hebrew/emu/hnsrun.c \
   -L"$MGBA_DIR/build" -lmgba -lz -Wl,-rpath,"$MGBA_DIR/build" -o tools/hebrew/emu/hnsrun
```

`build/include` holds the generated `mgba/flags.h`. `-lz` is needed for the PNG writer. The rpath
lets the runner find libmgba without installing it. `emu/hnsrun` is git-ignored. To keep the binary
somewhere else, point `HNS_RUNNER` at it. Check the runner with:

```bash
mkdir -p build/hebrew/hnsrun-check
printf '60 -\nshot boot\nquit\n' | tools/hebrew/emu/hnsrun pokehns.gba build/hebrew/hnsrun-check
# prints "OK: booted 240x160 ...", "shot boot @60" and writes build/hebrew/hnsrun-check/boot.png
```

## Environment

| Variable | Used for | Default |
| --- | --- | --- |
| `HNS_ROM` | the ROM `hns.py`, `ladder.py` and `cliptour.py run` boot; the ELF is taken from next to it | `$HNS_TREE/pokehns.gba` |
| `HNS_ELF` | a different ELF for `hns.py` (only when `--rom` is not given) and `evasm.py` | none |
| `HNS_SRC` | source tree for `MAP_*`/`FLAG_*` constants, event-script macros and labels | the ELF's directory |
| `HNS_SAVES` | the save ladder: `start saves/NAME` in a tour, the `selfcheck` save, the sweep's default save | none |
| `HNS_RUNNER` | the `hnsrun` binary | `tools/hebrew/emu/hnsrun` |
| `HNS_WORK` | `selfcheck` output, `evasm.py` host tools and headers (`evasm/`), `probe/`, `ladder_run/` | `build/hebrew` |
| `HNS_UNITS` | the unit chunks `sweep.py` takes its labels from | `$HNS_WORK/units` |
| `HNS_EN_ROM` | the ROM `make_ladder.sh` builds the ladder on | `$HNS_UPSTREAM/pokehns.gba` |
| `DEVKITARM` | `arm-none-eabi-readelf`/`nm`/`as`/`ld`/`cpp` for symbols and `evasm.py` | `/opt/devkitpro/devkitARM` |
| `HNS_RTC` | fake RTC start, Unix seconds (`--rtc` sets it) | 2026-01-01 12:00 UTC |
| `HNS_LOG` | `1` echoes every mGBA log line | off |
| `HNS_MAX_FRAMES` | frame limit per runner process (one tour): a command that would step past it ends the tour as TIMEOUT | none |

The ROM must be built and keep its `.elf` next to it, because every address is resolved by name
from the ELF. The saves are battery files (`.sav`). Do not commit them, and do not commit ROMs or
screenshots. Put run output under `build/hebrew/` (`HNS_WORK`), which git ignores.

## Running

The tools work from any directory. The examples are written from the repository root, with
`E=tools/hebrew/emu`; `OUT` is any output folder (for example one under `build/hebrew/`).

**Smoke checks**

```bash
python3 $E/hns.py selfcheck                     # struct offsets vs the ELF, then a live boot from ladder 1
python3 $E/hns.py sym gMain CB2_Overworld       # symbol addresses
python3 $E/hns.py map NEW_BARK                  # MAP_* -> group, num
python3 $E/hns.py run $E/scripts/continue.txt OUT --save "$HNS_SAVES/ladder1_newgame.sav"
```

`run` boots a copy of the save (`OUT/cur.sav`), so the ladder is never written to. A `--save` path
that does not exist means an empty battery, which NEW GAME needs.

**A tour** (one script per screen family, screenshots in `OUT/<tour>/`, a summary in
`OUT/tour_report.json`):

```bash
python3 $E/hns.py tour pokehns.gba OUT                       # every tour in tours/
python3 $E/hns.py tour pokehns.gba OUT --only '^menu_bag$'   # one tour, plus the tours it depends on
python3 $E/hns.py tour pokehns-clip.gba OUT --clip           # clip build: glyphs drawn outside a window
python3 $E/hns.py tourdiff OUT_A OUT_B                       # compare two runs screenshot by screenshot
python3 $E/hns.py sheet OUT/sheet.png OUT/menu_bag           # contact sheet
```

A tour starts with `start saves/NAME.sav`, which is a file in `HNS_SAVES`. It can also start
with `start save:NAME`, a save that an earlier tour exported with `keepsave NAME`, or with
`start empty`.

**The save ladder** (`HNS_SAVES` must point at a writable folder). Rung 1 is a new game saved in
the bedroom. Rungs 2-6 are built from it on the English ROM, and the script validates each rung:

```bash
python3 $E/hns.py --rom "$HNS_EN_ROM" run $E/scripts/ladder1_newgame.txt OUT --save OUT/none.sav \
        --save-out "$HNS_SAVES/ladder1_newgame.sav"
$E/scripts/make_ladder.sh [WORKDIR]                          # default WORKDIR: $HNS_WORK/ladder_run
```

To make one rung by hand, run
`python3 $E/ladder.py run $E/scripts/ladder2_badge1.txt OUT --save "$HNS_SAVES/ladder1_newgame.sav" --save-out ...`.

**The label sweep** (every live script text label from the unit chunks in `HNS_UNITS`, booted
from `ladder4_league.sav` in `HNS_SAVES` unless `--save` is given):

```bash
python3 $E/sweep.py run pokehns-clip.gba OUT [--batch B20] [--translated] [--limit N] [--resume]
python3 $E/sweep.py report OUT          # rebuild OUT/sweep.json and OUT/report.txt
python3 $E/sweep.py list --batch B20    # which labels a selection holds
python3 $E/sweep.py selftest pokehns-clip.gba OUT   # proves the clip detector on a patched copy
```

A clip build reports CLIP. Any other build is still checked for CRASH, HANG and ABNORMAL.

**The map walk** (crash test over every H&S map, from the post-game save). There are two forms:

```bash
python3 $E/mapwalk.py pokehns.gba "$HNS_SAVES/ladder6_postgame.sav" OUT [--only RE] [--max N]
python3 $E/hns.py tour pokehns.gba OUT --tours $E/tours_mapwalk
```

`mapwalk.py` reads the maps from `data/maps` next to the ROM, fights or reads through anything
that starts, and writes `OUT/mapwalk.json`. The scripted tour warps, waits and takes a screenshot
per map. It does not fight, so it stops with TIMEOUT at the first map that starts a battle on
entry (the Battle Arena battle room).

**Other**

```bash
python3 $E/evasm.py asm SCRIPT.inc        # assemble an event script, print bytes and symbols
$E/probe/measure.sh [SRC]                 # re-measure struct offsets (default SRC: HNS_TREE)
```
