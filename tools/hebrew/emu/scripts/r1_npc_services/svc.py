#!/usr/bin/env python3
"""hns.py with two extra tour ops for scenes whose text does not wait for a key:

    textwatch PREFIX UNTILCB2 [MAX] [KEY]   run until callback2 == UNTILCB2 (or MAX frames);
        shot PREFIX_NN whenever a text printer has just finished drawing (busy -> not busy)
        and whenever a text box waits for a key (then tap KEY, default A; '-' taps nothing).
    burst PREFIX COUNT EVERY                COUNT shots EVERY frames apart, identical frames dropped.

Usage: svc.py <hns.py args>   (e.g. svc.py tour ROM OUT --tours DIR --only RE --clip)
"""
import os, sys
sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", ".."))
import hns
from hns import script_op, HnsError, _arg


def _shot(emu, name):
    emu.shot(name)
    emu.shots = getattr(emu, "shots", []) + [name]
    return os.path.join(emu.outdir, name + ".png")


@script_op("textwatch")
def _op_textwatch(emu, f, path):
    prefix, until = f[1], emu.sym(f[2])
    maxf = _arg(f, 3, 3000)
    key = f[4] if len(f) > 4 else "A"
    n, waited, prev = 0, 0, "idle"
    last = None
    while waited < maxf:
        if emu.cb2() == until:
            break
        st = emu.text_state()
        if (prev == "busy" and st != "busy") or st == "key":
            emu.frames(3)
            n += 1
            p = _shot(emu, "%s_%02d" % (prefix, n))
            data = open(p, "rb").read() if os.path.exists(p) else None
            if data is not None and data == last:
                os.remove(p); n -= 1
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
    for i in range(count):
        emu.frames(every)
        n += 1
        p = _shot(emu, "%s_%02d" % (prefix, n))
        emu.sync()
        data = open(p, "rb").read()
        if data == last:
            os.remove(p); n -= 1
        last = data
    print("burst %s: %d distinct @%d" % (prefix, n, emu.sync()))


@script_op("scenewatch")
def _op_scenewatch(emu, f, path):
    """scenewatch PREFIX UNTILCB2 MAX Y0 Y1 [KEY] [KEYEVERY]: sample the screen every 6 frames
    until callback2 == UNTILCB2; keep a shot PREFIX_NN when rows Y0..Y1 changed from the last
    kept shot and are stable over two samples (a message drawn at once, not through a text
    printer). Taps KEY every KEYEVERY frames ('-' = never)."""
    prefix, until, maxf, y0, y1 = f[1], emu.sym(f[2]), int(f[3]), int(f[4]), int(f[5])
    key = f[6] if len(f) > 6 else "-"
    kev = int(f[7]) if len(f) > 7 else 90
    tmp = "_scan"
    kept, prev, n, waited = None, None, 0, 0
    while waited < maxf and emu.cb2() != until:
        emu.frames(6)
        waited += 6
        if key != "-" and waited % kev < 6:
            emu.tap(key, 0)
        emu.expect_after("shot %s" % tmp, r"^shot %s @" % tmp)
        pth = os.path.join(emu.outdir, tmp + ".png")
        w, h, rows = hns.read_png_rgb(pth)
        reg = b"".join(rows[y0:y1])
        if reg == prev and reg != kept:
            n += 1
            os.replace(pth, os.path.join(emu.outdir, "%s_%02d.png" % (prefix, n)))
            emu.shots = getattr(emu, "shots", []) + ["%s_%02d" % (prefix, n)]
            if getattr(emu, "clip", None):
                emu.clip.poll("%s_%02d" % (prefix, n))
            kept = reg
        prev = reg
    tp = os.path.join(emu.outdir, tmp + ".png")
    if os.path.exists(tp):
        os.remove(tp)
    print("scenewatch %s: %d shot(s), %d frames, callback2 %s @%d" % (prefix, n, waited, emu.cb2_name(), emu.sync()))


@script_op("scrollshots")
def _op_scrollshots(emu, f, path):
    """scrollshots PREFIX KEY [MAX] [IDLE]: snap PREFIX_01, then press KEY and snap again until
    the screen stops changing (the end of a list) or MAX shots; the repeated last shot is dropped."""
    prefix, key, mx, idle = f[1], f[2], _arg(f, 3, 60), _arg(f, 4, 4)
    n, last = 0, None
    while n < mx:
        emu.wait_quiet(900)
        emu.frames(2)
        n += 1
        p = _shot(emu, "%s_%02d" % (prefix, n))
        data = open(p, "rb").read()
        if data == last:
            os.remove(p); n -= 1
            emu.shots = emu.shots[:-1]
            break
        last = data
        emu.tap(key, idle)
    print("scrollshots %s: %d shot(s) @%d" % (prefix, n, emu.sync()))


@script_op("scrollmem")
def _op_scrollmem(emu, f, path):
    """scrollmem PREFIX KEY HEXADDR [MAX] [WIDTH]: snap PREFIX_01, press KEY, snap ... while the
    WIDTH-bit value at ADDR (a list cursor/scroll state) keeps changing; stops at the list end."""
    prefix, key, addr, mx = f[1], f[2], int(f[3], 16), _arg(f, 4, 80)
    width = _arg(f, 5, 32)
    rd = {8: emu.r8, 16: emu.r16, 32: emu.r32}[width]
    n = 0
    while n < mx:
        emu.wait_quiet(900)
        emu.frames(2)
        n += 1
        _shot(emu, "%s_%02d" % (prefix, n))
        before = rd(addr)
        emu.tap(key, 6)
        emu.wait_quiet(900)
        if rd(addr) == before:
            break
    print("scrollmem %s: %d shot(s) @%d" % (prefix, n, emu.sync()))


if __name__ == "__main__":
    sys.argv[0] = hns.__file__
    sys.exit(hns.main())
