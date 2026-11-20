# Headless harness

`hnsrun` is a small headless GBA runner on top of libmgba. It boots a ROM with an optional
battery save and reads commands from stdin: hold or tap keys, take screenshots, read and write
memory, wait for a value, pin bytes, save and load states. It stops with `CRASH` when the PC leaves
BIOS, RAM, ROM and the ROM's wait-state mirrors. The Python files drive it with addresses taken from
the build's ELF.

| File | What it is |
| --- | --- |
| `hnsrun.c` | the runner (its command list is at the top of the file) |
| `hns.py` | driver: ELF symbols, a live runner session, the script language, warps, saves, `selfcheck`, `render`, screen tours, `tourdiff`, contact sheets |
| `ladder.py` | extra script commands for building saves (event scripts in RAM, start menu, leaving a Center) |
| `evasm.py` | assembles an event script with the source tree's own macros, to run it in RAM |
| `sweep.py` | shows every live script text label in the message box and reports CLIP / CRASH / HANG / ABNORMAL |
| `mapwalk.py` | warps into every H&S map, fights or reads through whatever starts, takes a screenshot of each |
| `textalign.py` | compares each text window of a Hebrew screenshot with the English one of the same moment: margins mirrored, centring, ink on the window edge, rows, cursor side (below, "Text alignment") |
| `tours/` | the 71 release tours (`pbi_*` 17, `menu_*` 12, `bv_*` 11, `chr_*` 10, `battle_*` 6, `cardgear_*`, `ncm_*`, `btw_*` 3 each, `naming_*`, `bfm_*` 2 each, `dex_forms`, `field_*`); `_*.txt` are includes; the subfolders hold the review rounds' tours, which the release does not run |
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
| `HNS_SAVES` | the saves a tour starts from (`start saves/NAME`): the save ladder and the tour base saves `menuA_base.sav`, `pif2_base.sav`, `r1field_menuA_base.sav` and others (`<builds>/saves`, the private builds repository); the `selfcheck` save; the sweep's default save | none |
| `HNS_RUNNER` | the `hnsrun` binary | `tools/hebrew/emu/hnsrun` |
| `HNS_WORK` | `selfcheck` output, `evasm.py` host tools and headers (`evasm/`), `probe/`, `ladder_run/` | `build/hebrew` |
| `HNS_UNITS` | the unit chunks `sweep.py` takes its labels from | `$HNS_WORK/units` |
| `HNS_EN_ROM` | the ROM `make_ladder.sh` builds the ladder on | `$HNS_UPSTREAM/pokehns.gba` |
| `DEVKITARM` | `arm-none-eabi-readelf`/`nm`/`as`/`ld`/`cpp` for symbols and `evasm.py` | `/opt/devkitpro/devkitARM` |
| `HNS_RTC` | fake RTC start, Unix seconds (`--rtc` sets it); mGBA hands it to the game in the host's time zone | 2026-01-01 12:00 UTC |
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
`start empty`. The release tours (`tours/*.txt`) start from saves at the top of the builds
repository's `saves/`. A round tour (`tours/<round>/`) that names a save found only in a subfolder
needs `HNS_SAVES` set to the folder that holds it: `saves/r8` for round 8, a folder under
`saves/r10/` or `saves/r11/` for those rounds, `saves/r4_bag` for `r20_names`' `n20_bag` and
`n20_dexsearch` (both start from `menuA_base_copy.sav`), and `saves/r7/saves_aug` for rounds 3-7
and `verify_ctxdpad` (the builds repository's README).

A step that only one build has goes between `ifsym SYMBOL` and `endif`: those lines run only when
the ELF defines SYMBOL. The Hebrew build asks "give up learning the move?" before a Pokémon gives up
a new move (`P_ASK_MOVE_CONFIRMATION` follows `TEXT_RTL`; the English game does not ask), and that
option compiles in `Task_HandleStopLearningMoveYesNoInput`, so the tours that turn a move down answer
the box inside `ifsym Task_HandleStopLearningMoveYesNoInput` and run the same on the English ROM.

`startmenu NAME`, `savegame` and `ladder.py`'s `startmenu` press START only when the start menu is
not drawn and reading input, which `Emu.start_menu_ready` reads as a `Task_ShowStartMenu` task in
its input state (`data[0]` = 1) with `gMenuCallback` = `HandleStartMenuInput`. `gMenuCallback`
alone does not tell: it keeps naming `HandleStartMenuInput` after B or START closes the menu, on
every map. A menu the game draws again on the way back from the party, bag or card is waited for
and used, not closed by a second START.

**On the English ROM** (`hns.py tour "$HNS_EN_ROM" OUT`, for side-by-side review): 70 of the 71
tours report OK and `naming_nickname` stops with ERROR at its first check of the typed Hebrew
bytes. Both `naming_*` tours type on the Hebrew keyboard, so they are Hebrew-only by design:
`naming_player` reports OK on English only because it has no byte checks, and its screenshots
show nothing useful there. The other 69 run on English.

**The save ladder** (`HNS_SAVES` must point at a writable folder). Rung 1 is a new game saved in
the bedroom. Rungs 2-6 are built from it on the English ROM, and the script validates each rung:

```bash
python3 $E/hns.py --rom "$HNS_EN_ROM" run $E/scripts/ladder1_newgame.txt OUT --save OUT/none.sav \
        --save-out "$HNS_SAVES/ladder1_newgame.sav"
$E/scripts/make_ladder.sh [WORKDIR]                          # default WORKDIR: $HNS_WORK/ladder_run
```

To make one rung by hand, run
`python3 $E/ladder.py run $E/scripts/ladder2_badge1.txt OUT --save "$HNS_SAVES/ladder1_newgame.sav" --save-out ...`.

The runs repeat byte for byte: the clock starts at `HNS_RTC` and moves with the emulated frames.
But mGBA converts it to the host's local time (`localtime_r` in mGBA's `src/gba/cart/gpio.c`),
and a save's 16-byte footer carries its clock into the next run. So `make_ladder.sh` should rebuild
rungs 2-6 from the stored rung 1 in any time zone; rung 2 was checked under `TZ=UTC`. A new
rung 1, and any tour that starts a new game (`start empty`), match the stored saves only in a
UTC+2 zone on 2026-01-01, for example `TZ=Asia/Jerusalem`: under `TZ=UTC` rung 1's footer hour
differs, and the rungs built from it differ widely.

**The label sweep** (every live script text label from the unit chunks in `HNS_UNITS`, booted
from `ladder4_league.sav` in `HNS_SAVES` unless `--save` is given):

```bash
python3 $E/sweep.py run pokehns-clip.gba OUT [--batch B20] [--hebrew-only] [--limit N] [--resume]
python3 $E/sweep.py report OUT          # rebuild OUT/sweep.json and OUT/report.txt
python3 $E/sweep.py list --batch B20    # which labels a selection holds
python3 $E/sweep.py selftest pokehns-clip.gba OUT   # proves the clip detector on a patched copy
```

A clip build reports CLIP. Any other build is still checked for CRASH, HANG and ABNORMAL.
`--hebrew-only` keeps the labels whose string in the ROM has Hebrew. `--translated` keeps the
units that hold a Hebrew text; units from `make_chunks.py` hold none, so it exits 2 on them.

**The map walk** (crash test over every H&S map, from the post-game save). There are two forms:

```bash
python3 $E/mapwalk.py pokehns.gba "$HNS_SAVES/ladder6_postgame.sav" OUT [--only RE] [--max N]
python3 $E/hns.py tour pokehns.gba OUT --tours $E/tours_mapwalk
```

`mapwalk.py` reads the maps from `data/maps` next to the ROM, fights or reads through anything
that starts, and writes `OUT/mapwalk.json`. The scripted tour warps, waits and takes a screenshot
per map. It does not fight, so it stops with TIMEOUT at the first map that starts a battle on
entry (the Battle Arena battle room).

Compare a Hebrew walk only with an English walk made by the same `mapwalk.py`. With the current
walker the English ROM holds the same 36 maps as the Hebrew one; the builds repository's
`reference/mapwalk_en.json` is such a walk (543 maps: 507 OK, 36 HELD). The walk it replaced was
made by an older walker that answered with A and B in turn: it held 32 of them, had a false CRASH
in the Dome pre-battle room (a PC in the ROM's mirror, which the CRASH check below now accepts) and
an ERROR in the Battle Pike's normal room, and passed the two Battle Arena rooms.

**Cross-core** (`crosscore.c`, a minimal libretro frontend; `run_release_tests.sh` builds it on
every run). It answers every core option with the core's own default, with one override
(`gba_use_mednafen_save_method=libretro`, so that Mednafen-GBA exposes its save RAM), and it
copies the 131088-byte `.sav` into the core's save RAM up to its size: mGBA, VBA-M, gpSP and
SkyEmu load 131072 of 131072 bytes (the 16-byte RTC footer is dropped), Mednafen-GBA and
VBA-Next 131088 of 139264. `../release/ccdiff.py` compares the frames after reducing each pixel to
RGB555, the GBA's own colour depth. Whether RetroArch's own `.srm` loader accepts the 131088-byte
file was not tried.

**The CRASH check.** `hnsrun` checks the PC every 60 frames (`pcIsSane`), and `hns.py`
(`pc_is_sane`) and `sweep.py` check it after a tour or a label. All three accept the regions the
game runs code from: BIOS `00`, EWRAM `02`, IWRAM `03`, ROM `08`-`09`, and the ROM's wait-state
mirrors `0A`-`0D`. The mirrors are normal: the game runs most script commands from `0x0A` on purpose,
because the command table stores every command that requests effects as its address plus
`ROM_SIZE` (`data/script_cmd_table.inc:6-12`) and `RunScriptCommand` calls it there
(`src/script.c:130-138`). `hns.py where` and the CRASH details name a mirror address by the ROM
address it mirrors (`where 0A0E8ECC` prints `FillBitmapRect4Bit+0xA0`, like `080E8ECC`). Any other
region is a crash; so is a run of more than 1000 mGBA log lines about invalid code (`Illegal
opcode`, `Jumped to invalid address`), which `hns.py` reports as `CRASH: the CPU runs invalid code`
because the PC may then sit in the BIOS. The runner reads the PC only at the end of every 60th frame,
so a crash that keeps passing through the BIOS (a jump to cartridge SRAM at `0x0E000000`, where
mGBA runs no code, goes on through the BIOS's undefined-instruction handler) can pass its check and
is then reported by that log rule only. `sweep.py run ... --fault crash:LABEL` proves the runner's
check: it writes a loop that masks IRQs into the last tile of OBJ VRAM (`0x06017FF0`) and points
`gMain.callback2` at it, so the run stops with `CRASH: pc=06017FF8` at the next check and no log
lines. The region list is compiled into the runner, so rebuild `hnsrun` after a change to
`hnsrun.c`.

**Text alignment** (`textalign.py`): checks that each Hebrew line sits in its window the way
`docs/hebrew_translation.md` says it should: flush right with the margin English has on the left,
centred where English is centred, the cursor on the right. It reads only the two PNGs. Run the
same tours on both ROMs (the release tours are deterministic, so a shot shows the same moment in
both builds), then:

```bash
python3 $E/hns.py tour "$HNS_EN_ROM" EN_OUT           # English shots, same names
python3 $E/textalign.py tours EN_OUT OUT TA --jobs 6  # all pairs: about 13 s for the 2,030 of 1.0
python3 $E/textalign.py pair EN.png HE.png --out DIR  # one pair; -v prints every line, --json all
```

`TA/summary.txt` gives the counts per class and lists every window that is not OK, grouped by
tour and place; `TA/windows.txt` lists them one by one; `TA/report.json` has every window with its
lines, margins and rows; `TA/crops/` has an English | Hebrew crop pair (3x, each shot's window
outlined in magenta, flagged lines marked red at the left) for every window that is not OK.

How it finds windows: the text is where the two shots differ. The paper under a group of
differing pixels is the colour the shots share around it; the window is the paper rectangle
grown from there until a frame (a column or row with no paper) stops it, in each shot, so its
edges are the visible box the margins are measured against. A line is a band of rows with text
that moves between the shots; icons and numbers drawn in the same place in both do not count.
The module docstring gives the rules in full.

| Class | Meaning |
| --- | --- |
| `OK` | every line mirrored (Hebrew right margin = English left margin), mirrored as a right-aligned column, or centred |
| `IN-PLACE` | every line keeps English's left or right margin: by design for the windows `docs/hebrew_translation.md` lists under `WINDOW_RTL_IN_PLACE` (party slots, battle menus, healthboxes, bag pocket title...), a defect anywhere else (a menu that was not mirrored is reported this way) |
| `MIRROR-MISMATCH` | a line neither mirrored nor in place, a window whose lines mix the two, or a cursor that was not mirrored |
| `CENTRE-OFF` | an English line centred in its window that is neither centred nor mirrored in Hebrew |
| `EDGE` | Hebrew ink on the window's outermost column where English keeps a gap, or Hebrew text seen through a gap outside its window |
| `ROW-SHIFT` | a line whose top and bottom both moved more than 3 px the same way |
| `UNKNOWN` | cannot measure: text over art (no paper), a window cut by the screen edge or open art on the side a margin needs, or text in one shot only |

The tolerance is 2 px (`--tol`). On 1.0's tours the mirrored lines' Hebrew right margin minus
English left margin is 0 on 6,026 lines, -1 on 683, +1 on 206, -2 on 1,100 (1,008 of them the
battle healthboxes' names, sprites 2 px off the mirror) and +2 on 242, and falls to 86 and 46
paired lines at -3 and +3. One pixel is the font: Hebrew's outer column at the start of a line
is the glyph's shadow, English's is the ink.

Checked on 1.0's release tours (rc26) against English 2.0.6:

- 20 shots across window types, looked at by hand and all correct (dialogue, signs, menus, the
  mart list and quantity box, the bag, options, battle text, the battle and fight menus, the PC,
  yes/no, the save box, the start menu, the PokéGear call screen): 52 windows OK, 2 IN-PLACE (the
  battle and fight menus, by design), 9 UNKNOWN (art labels, a sprite), 1 MIRROR-MISMATCH (the
  PokéGear hint bar, two windows on one bar).
- The Pokéblock case's three-digit level of rc22 (round 21's evidence): EDGE on the one shot
  that shows it; nothing after the fix. The Easy Chat footer seen beside the keyboard in rc24
  (round 25's frame-by-frame shots): 110 frames show it, 108 of them with an English shot of the
  same moment. EDGE on 91 of those 108; the 17 missed are frames where English shows its own OK
  in the same gap. One frame of the keyboard opening is EDGE in both builds, a false finding,
  and it is the only EDGE at the gap on the fixed build.
- rc1's unmirrored PC mark menu, Pokédex START menu and naming hint bar: IN-PLACE in rc1, OK (or
  not measurable: the START menu box runs off the screen) in 1.0.

What it cannot see or gets wrong:

- It compares geometry, not text: a wrong word in the right place is OK.
- A shot where English shows another moment (another page of a message), or draws blank a name
  the Hebrew game wrote into the save, gives MIRROR-MISMATCH or EDGE on that window.
- Animation frames that differ (a bobbing pocket arrow, a sprite) can look like text.
- Two windows on one unbroken paper (the battle debug menu, the PokéGear hint bar) are measured
  as one; a window drawn in another place in Hebrew (a moved YES/NO box) is not paired and counts
  only in "differing regions that are not text".
- Letters drawn as holes in a badge, and art labels with no plain paper around them, are UNKNOWN.
- A row shift of 3 px or less is not seen.

**Known limits**

- In a `ladder.py` script `warpto` takes `GROUP NUM X Y` (`ladder.py:224-228`), not `hns.py`'s
  `warpto MAP_NAME X Y`; `hns.py map NAME` prints the numbers.

**Other**

```bash
python3 $E/evasm.py asm SCRIPT.inc        # assemble an event script, print bytes and symbols
$E/probe/measure.sh [SRC]                 # re-measure struct offsets (default SRC: HNS_TREE)
```
