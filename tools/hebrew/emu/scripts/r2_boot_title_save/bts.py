#!/usr/bin/env python3
"""hns.py plus the tour ops the boot / title / save-system tours need (r2_boot_title_save).

    textwatch PREFIX UNTILCB2 [MAX] [KEY]  shot PREFIX_NN whenever a text printer has just finished
        and whenever text waits for a key (then tap KEY, '-' = none), until callback2 == UNTILCB2.
    burst PREFIX COUNT EVERY               COUNT shots EVERY frames apart, identical frames dropped.
    regionwatch PREFIX MAX Y0 Y1 [X0 X1] [UNTILCB2]
        every 2 frames compare the screen rows Y0..Y1 (columns X0..X1); keep a shot PREFIX_NN each
        time that region changed and then held still for 4 frames (a message drawn at once while
        a long C loop runs, e.g. the save-failed screen). Ends after MAX frames or at UNTILCB2.
    taskpoke FUNC IDX VAL                  write data[IDX] (s16) of the task that runs FUNC.
    taskwaitfunc FUNC_NOW FUNC_NEXT [MAX]  find the task running FUNC_NOW and run frame by frame
        until its func becomes FUNC_NEXT (per-frame precise: the next task step has not run yet).
    setcb2 SYMBOL                          SetMainCallback2(SYMBOL): gMain.callback2 = SYMBOL,
        gMain.state = 0 (what the game does when it switches screens).
    softreset                              hold A+B+START+SELECT (the game's soft reset).
    pinsym SYMBOL HEXBYTES / unpinsym SYMBOL   pin / unpin bytes at a symbol (hnsrun pin).
    ptrpoke 8|16|32 PTRSYM HEXOFF VAL      write VAL into the heap struct that PTRSYM points to.
    ptrpin PTRSYM HEXOFF HEXBYTES          pin bytes inside the heap struct that PTRSYM points to.
    pinptr SYMBOL TARGET / pokeptr SYMBOL TARGET   pin / write the address of TARGET (a function
        keeps its Thumb bit) into the pointer variable SYMBOL.

Usage: bts.py <hns.py args>   (e.g. bts.py tour ROM OUT --tours DIR --only RE --clip)
"""
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.dirname(os.path.dirname(HERE)))     # tools/hebrew/emu
import hns                                                     # noqa: E402
from hns import script_op, HnsError, TourTimeout, _arg         # noqa: E402

TASK_SIZE, TASK_DATA = 40, 8          # struct Task (include/task.h): func, isActive, prev, next, priority, data[16]


def _shot(emu, name):
    p = emu.shot(name)
    emu.shots = getattr(emu, "shots", []) + [name]
    return p


def _drop(emu, p, name):
    os.remove(p)
    emu.shots = [s for s in getattr(emu, "shots", []) if s != name]


@script_op("textwatch")
def _op_textwatch(emu, f, path):
    prefix, until = f[1], emu.sym(f[2])
    maxf = _arg(f, 3, 3000)
    key = f[4] if len(f) > 4 else "A"
    n, waited, prev, last = 0, 0, "idle", None
    while waited < maxf:
        if emu.cb2() == until:
            break
        st = emu.text_state()
        if (prev == "busy" and st != "busy") or st == "key":
            emu.frames(3)
            n += 1
            name = "%s_%02d" % (prefix, n)
            p = _shot(emu, name)
            data = open(p, "rb").read()
            if data == last:
                _drop(emu, p, name)
                n -= 1
            last = data
            if st == "key" and key != "-":
                emu.tap(key, 0)
                emu.wait_until(lambda: emu.text_state() != "key", 120, "text to take the key", step=1)
            st = emu.text_state()
        prev = st
        emu.frames(2)
        waited += 2
    print("textwatch %s: %d shot(s), %d frames, callback2 %s @%d" % (prefix, n, waited, emu.cb2_name(), emu.sync()))


@script_op("burst")
def _op_burst(emu, f, path):
    prefix, count, every = f[1], int(f[2]), int(f[3])
    last, n = None, 0
    for _ in range(count):
        emu.frames(every)
        n += 1
        name = "%s_%02d" % (prefix, n)
        p = _shot(emu, name)
        data = open(p, "rb").read()
        if data == last:
            _drop(emu, p, name)
            n -= 1
        last = data
    print("burst %s: %d distinct @%d" % (prefix, n, emu.sync()))


@script_op("regionwatch")
def _op_regionwatch(emu, f, path):
    prefix, maxf, y0, y1 = f[1], int(f[2]), int(f[3]), int(f[4])
    x0 = int(f[5]) if len(f) > 6 else 0
    x1 = int(f[6]) if len(f) > 6 else 240
    until = emu.sym(f[7]) if len(f) > 7 else (emu.sym(f[5]) if len(f) == 6 else None)
    tmp = "_scan"
    kept, prev, still, n, waited = None, None, 0, 0, 0
    while waited < maxf:
        if until is not None and emu.cb2() == until:
            break
        emu.frames(2)
        waited += 2
        emu.expect_after("shot %s" % tmp, r"^shot %s @" % tmp)
        pth = os.path.join(emu.outdir, tmp + ".png")
        w, h, rows = hns.read_png_rgb(pth)
        reg = b"".join(r[x0 * 3:x1 * 3] for r in rows[y0:y1])
        still = still + 2 if reg == prev else 0
        if still >= 4 and reg != kept:
            n += 1
            name = "%s_%02d" % (prefix, n)
            os.replace(pth, os.path.join(emu.outdir, name + ".png"))
            emu.shots = getattr(emu, "shots", []) + [name]
            if getattr(emu, "clip", None):
                emu.clip.poll(name)
            print("regionwatch %s @%d (callback2 %s)" % (name, emu.sync(), emu.cb2_name()))
            kept = reg
        prev = reg
    tp = os.path.join(emu.outdir, tmp + ".png")
    if os.path.exists(tp):
        os.remove(tp)
    print("regionwatch %s: %d shot(s), %d frames, callback2 %s @%d" % (prefix, n, waited, emu.cb2_name(), emu.sync()))


def _task_slot(emu, func):
    want = emu.sym(func)
    for tid, fn, _ in emu.tasks():
        if fn == want:
            return emu.sym("gTasks") + tid * TASK_SIZE
    raise HnsError("no task runs %s; tasks %s" % (func, [t[2] for t in emu.tasks()]))


@script_op("taskpoke")
def _op_taskpoke(emu, f, path):
    slot = _task_slot(emu, f[1])
    idx, val = int(f[2]), emu.const(f[3])
    emu.w16(slot + TASK_DATA + 2 * idx, val)
    print("taskpoke %s data[%d] = %d @%d" % (f[1], idx, val, emu.sync()))


@script_op("taskwaitfunc")
def _op_taskwaitfunc(emu, f, path):
    # FUNC_NOW may appear a few frames late: e.g. the main menu's A handler first runs
    # IsWirelessAdapterConnected, which blocks the main loop for several frames.
    want = emu.sym(f[1])
    emu.wait_until(lambda: any(fn == want for _, fn, _ in emu.tasks()), _arg(f, 3, 600),
                   "task %s" % f[1], step=1)
    slot = _task_slot(emu, f[1])
    ok = emu.wait32(slot, emu.sym(f[2]), _arg(f, 3, 600))
    if not ok:
        raise TourTimeout("taskwaitfunc: task %s did not become %s" % (f[1], f[2]))
    print("taskwaitfunc %s -> %s ok @%d" % (f[1], f[2], emu.sync()))


@script_op("setcb2")
def _op_setcb2(emu, f, path):
    emu.w32(emu.CB2, emu.sym(f[1]))
    emu.w8(emu.sym("gMain") + hns.OFF["Main.state"], 0)
    print("setcb2 %s @%d" % (f[1], emu.sync()))


@script_op("softreset")
def _op_softreset(emu, f, path):
    emu.frames(6, "A+B+START+SELECT")
    emu.frames(2)
    print("softreset @%d" % emu.sync())


@script_op("pinsym")
def _op_pinsym(emu, f, path):
    emu.expect_after("pin %08X %s" % (emu.sym(f[1]), f[2]), r"^PIN ")
    print("pinsym %s %s @%d" % (f[1], f[2], emu.sync()))


@script_op("unpinsym")
def _op_unpinsym(emu, f, path):
    emu.expect_after("unpin %08X" % emu.sym(f[1]), r"^UNPIN ")
    print("unpinsym %s @%d" % (f[1], emu.sync()))


@script_op("ptrpoke")
def _op_ptrpoke(emu, f, path):
    base = emu.r32(emu.sym(f[2]))
    if not base:
        raise HnsError("ptrpoke: %s is NULL" % f[2])
    emu.w(int(f[1]), base + int(f[3], 16), emu.const(f[4]))
    print("ptrpoke %s+%s = %s @%d" % (f[2], f[3], f[4], emu.sync()))


@script_op("ptrpin")
def _op_ptrpin(emu, f, path):
    base = emu.r32(emu.sym(f[1]))
    if not base:
        raise HnsError("ptrpin: %s is NULL" % f[1])
    emu.expect_after("pin %08X %s" % (base + int(f[2], 16), f[3]), r"^PIN ")
    print("ptrpin %s+%s %s @%d" % (f[1], f[2], f[3], emu.sync()))


@script_op("pinptr")
def _op_pinptr(emu, f, path):
    v = emu.sym(f[2])
    emu.expect_after("pin %08X %s" % (emu.sym(f[1]), v.to_bytes(4, "little").hex().upper()), r"^PIN ")
    print("pinptr %s = %s (%08X) @%d" % (f[1], f[2], v, emu.sync()))


@script_op("pokeptr")
def _op_pokeptr(emu, f, path):
    emu.w32(emu.sym(f[1]), emu.sym(f[2]))
    print("pokeptr %s = %s @%d" % (f[1], f[2], emu.sync()))


if __name__ == "__main__":
    sys.argv[0] = hns.__file__
    sys.exit(hns.main())
