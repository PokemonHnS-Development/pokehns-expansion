#!/usr/bin/env python3
"""hns.py plus ladder.py plus the ops the r4 misc tours use (Berry Blender speed-record sign,
Pokedex AREA page at night, overworld debug menu).

    r4misc.py run SCRIPT OUTDIR [--save SAV] [--save-out SAV]
    r4misc.py tour ROM OUTDIR --tours <this folder>/tours [--clip] [--only RE]

Added here:
    blender R2 R3 R4       SaveBlock1.berryBlenderRecords[0..2] = R2, R3, R4 (u16, hundredths of an RPM;
                           the sign prints record / 100 "." record % 100, src/berry_blender.c
                           ShowBerryBlenderRecordWindow). The offset, SB1+0x10D8, is read from the
                           code: `ldrh r7, [r3, r2]` with r3 = (i + 0x86C) << 1 and r2 = gSaveBlock1Ptr,
                           the same in the English and the 0.2 ELF (the r2 note's "0x86C" is the
                           halfword index). Each value is read back.
    dexopen                start menu > POKEDEX in national mode, numerical order (scripts/r2_pokedex/
                           dexsweep.py Dex.open_dex)
    dexgoto POS            list cursor to 0-based position POS (national numerical: POS = dex number - 1)
    dexinfo                A on the list: the INFO page
    dexarea                RIGHT on INFO: the AREA page, once it reads input
    dextoggle KEY          UP or DOWN on AREA (day <-> night, src/pokedex_area_screen.c:928-940), then
                           wait for the page to read input again; prints gAreaTimeOfDay
    dexback                from AREA: LEFT (INFO), B (the list)
    rtlmode FUNC IDX MODE  set the RTL mode of the window id in data[IDX] of task FUNC (an experiment
                           for SetWindowRtlMode; a no-op on the English ROM)
    dexstate               print the entry's dex number, list position and gAreaTimeOfDay
"""
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(HERE, "..", ".."))                                # tools/hebrew/emu
import hns     # noqa: E402
import ladder  # noqa: E402,F401  (registers event, eventstart, rungoto, warpto, ...)
sys.path.insert(0, os.path.join(HERE, "..", "r2_pokedex"))
import dexsweep  # noqa: E402
from hns import script_op, HnsError  # noqa: E402

SB1_BLENDER_RECORDS = 0x10D8


def _dex(emu):
    d = getattr(emu, "_r4dex", None)
    if d is None:
        src = os.environ.get("HNS_SRC")
        if not src:
            raise HnsError("set HNS_SRC to the source tree of the ROM")
        d = dexsweep.Dex(emu, src, emu.outdir if hasattr(emu, "outdir") else ".")
        emu._r4dex = d
    return d


@script_op("blender")
def _op_blender(emu, f, path):
    vals = [int(x, 0) for x in f[1:4]]
    base = emu.sb1() + SB1_BLENDER_RECORDS
    before = [emu.r16(base + 2 * i) for i in range(3)]
    for i, v in enumerate(vals):
        emu.w16(base + 2 * i, v & 0xFFFF)
    got = [emu.r16(base + 2 * i) for i in range(3)]
    if got != [v & 0xFFFF for v in vals]:
        raise HnsError("blender: wrote %s, reads %s" % (vals, got))
    print("blender records %s -> %s" % (before, got))


@script_op("dexopen")
def _op_dexopen(emu, f, path):
    d = _dex(emu)
    d.open_dex(None)
    print("dexopen: %d entries @%d" % (d.pv16("PV.pokemonListCount"), emu.sync()))


@script_op("dexgoto")
def _op_dexgoto(emu, f, path):
    d = _dex(emu)
    d.list_goto(int(f[1]))
    print("dexgoto %s: #%d %s @%d" % (f[1], d.dexnum(), d.name(d.dexnum()), emu.sync()))


@script_op("dexinfo")
def _op_dexinfo(emu, f, path):
    _dex(emu).list_to_info()


@script_op("dexarea")
def _op_dexarea(emu, f, path):
    d = _dex(emu)
    d.key("RIGHT")
    d.wait_area()
    print("dexarea: time of day %d @%d" % (emu.r8(emu.sym("gAreaTimeOfDay")), emu.sync()))


@script_op("dextoggle")
def _op_dextoggle(emu, f, path):
    d = _dex(emu)
    tod = emu.sym("gAreaTimeOfDay")
    before = emu.r8(tod)
    d.key(f[1])
    emu.wait_until(lambda: emu.r8(tod) != before, 60, "gAreaTimeOfDay to change", step=1)
    emu.frames(4)
    d.wait_area()
    print("dextoggle %s: time of day %d -> %d @%d" % (f[1], before, emu.r8(tod), emu.sync()))


@script_op("dexback")
def _op_dexback(emu, f, path):
    """dexback: from AREA, LEFT (INFO) then B (the list)."""
    d = _dex(emu)
    d.key("LEFT")
    d.wait("Task_HandleInfoScreenInput")
    d.key("B")
    d.wait("Task_HandlePokedexInput")
    emu.frames(16)
    print("dexback: on the list at %d @%d" % (d.sel(), emu.sync()))


@script_op("rtlmode")
def _op_rtlmode(emu, f, path):
    """rtlmode TASKFUNC DATAIDX MODE: sWindowRtlMode[windowId] = MODE (0 mirror, 1 in place, 2 LTR;
    include/window.h:47-51) for the window id held in data[DATAIDX] of the task running TASKFUNC
    (the debug menu keeps its list window in data[1], an extra window in data[2]). An experiment:
    what SetWindowRtlMode(windowId, MODE) after AddWindow would show. AddWindow resets the mode,
    so it holds until the window is re-created. The next print uses it; press a key to reprint."""
    if "sWindowRtlMode" not in emu.elf.byname:
        print("rtlmode: no sWindowRtlMode in this ELF (not a TEXT_RTL build), skipped")
        return
    data = emu.task_data(f[1])
    if not data:
        raise HnsError("rtlmode: no task runs %s" % f[1])
    win = data[0][int(f[2])] & 0xFF
    addr = emu.sym("sWindowRtlMode") + win
    before = emu.r8(addr)
    emu.w8(addr, int(f[3]))
    # the pixels the earlier (mirrored) print left behind would show through the reprint: fill the
    # window's buffer with PIXEL_FILL(1) as FillWindowPixelBuffer does (struct Window: template
    # bytes 0-7, width +3, height +4, u8 *tileData +8; stride 12, include/window.h)
    w = emu.sym("gWindows") + 12 * win
    tiles = emu.r8(w + 3) * emu.r8(w + 4)
    buf = emu.r32(w + 8)
    for off in range(0, tiles * 32, 4):
        emu.w32(buf + off, 0x11111111)
    print("rtlmode: window %d mode %d -> %s, %d tiles cleared" % (win, before, f[3], tiles))


@script_op("dexstate")
def _op_dexstate(emu, f, path):
    d = _dex(emu)
    print("dexstate: #%d %s, list pos %d, time of day %d"
          % (d.dexnum(), d.name(d.dexnum()), d.sel(), emu.r8(emu.sym("gAreaTimeOfDay"))))


if __name__ == "__main__":
    sys.exit(hns.main())
