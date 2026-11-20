#!/usr/bin/env python3
r"""hns.py plus the ops the r5 Latin-leftover NPC tours (tours/r5_latin/*.txt) use:

    rc.py      fieldwatch, copyrom, ... and through r3bf.py / r2sf.py: drive, pick, vars, textwatch,
               scenewatch, scrollshots, warpraw, ss/sl, loc, ...
    tutor.py   boxgo, boxpick, boxmenu, freezenpc, approachnpc (and through mart.py / svc.py: setmoney, ...)
    sumvar.py  monprobe, monset, sumwait, sumkey


Added here:
    partyinfo                print the party count and each slot's species (debugging)
    flags NAME...            print save-block flags (FLAG_*)
    fieldwatch ...           rc.py's fieldwatch, with one change: after the A that answers a page, it
                             waits for the page to be taken (no text box waits for a key, or the active
                             printer's currentChar moved on) and re-taps A up to 3 times. rc.py's
                             version stops when the key wait is never seen to end, which happens on a
                             one-glyph page ("…\p", Route37_Text_Sunny_GaveGift) in both ROMs: the next
                             page is reached within the frame that takes the key.

Run:  r5lat.py tour ROM OUT --tours <emu>/tours/r5_latin [--clip] [--only RE]
"""
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
EMU = os.path.dirname(os.path.dirname(HERE))
sys.path.insert(0, EMU)
for sub in ("r4_tutors", "r2_pokegear_ribbons_contests", "r2_summary_info_page_variants"):
    sys.path.insert(0, os.path.join(EMU, "scripts", sub))
import hns  # noqa: E402
import tutor  # noqa: E402,F401
import rc  # noqa: E402,F401
import sumvar  # noqa: E402,F401

from hns import script_op, HnsError, _arg  # noqa: E402


@script_op("partyinfo")
def _op_partyinfo(emu, f, path):
    n = emu.r8(emu.sym("gPlayerPartyCount"))
    out = []
    for i in range(n):
        m = sumvar.mon_fields(emu, i)
        out.append("%d:%d%s" % (i, m["species"], " egg" if m["egg"] else ""))
    print("partyinfo: %d mon(s) %s" % (n, " ".join(out)))


def _cur_chars(emu):
    return tuple(int.from_bytes(emu.read(p, 4), "little") for p, _, a, _ in emu.text_printers() if a)


def _take_key(emu):
    """Tap A on a page that waits for a key; return once it is taken (see the docstring)."""
    for attempt in range(4):
        before = _cur_chars(emu)
        emu.tap("A", 0)
        for _ in range(60):
            if not emu.wants_key() or _cur_chars(emu) != before:
                if attempt:
                    print("fieldwatch: the key was taken on tap %d" % (attempt + 1))
                return
            emu.frames(1)
    raise hns.TourTimeout("fieldwatch: 4 taps of A did not take the page (callback2 %s)" % emu.cb2_name())


@script_op("fieldwatch")
def _op_fieldwatch(emu, f, path):
    prefix, target = f[1], f[2]
    maxf, every = _arg(f, 3, 20000), _arg(f, 4, 0)
    want_cb2 = emu.sym(target[4:]) if target.startswith("cb2:") else None
    want_task = target[5:] if target.startswith("task:") else None
    ow = emu.sym("CB2_Overworld")
    n, k, waited, since, last, prev = 0, 0, 0, 0, None, "idle"

    def shoot(periodic=False):
        nonlocal n, k, last, since
        since = 0
        if periodic:
            k += 1
            name = "%s_%03d_p%02d" % (prefix, n, k)
        else:
            n += 1
            k = 0
            name = "%s_%03d" % (prefix, n)
        p = rc._shot(emu, name)
        data, same = rc._same_as(p, last)
        if same and periodic:
            os.remove(p)
            emu.shots = emu.shots[:-1]
            k -= 1
            return
        last = data

    def reached():
        cb = emu.cb2()
        if want_cb2 is not None:
            return cb == want_cb2
        if want_task is not None:
            return emu.task_active(want_task)
        if target == "free":
            return emu.controllable()
        return False

    while waited < maxf:
        if reached():
            if target == "free":
                emu.frames(8)
                if not emu.controllable():
                    continue
            print("fieldwatch %s: %d shot(s), reached %s @%d" % (prefix, n, target, emu.sync()))
            return
        if emu.cb2() == ow and emu.tasks_named(emu.MENU_TASKS):
            emu.wait_menu_ready()
            emu.frames(2)
            shoot()
            if target == "menu":
                print("fieldwatch %s: %d shot(s), menu %s @%d" % (prefix, n, emu.tasks_named(emu.MENU_TASKS)[0], emu.sync()))
                return
            raise HnsError("fieldwatch %s: unexpected menu %s" % (prefix, emu.tasks_named(emu.MENU_TASKS)[0]))
        st = emu.text_state()
        if emu.wants_key():
            emu.wait_quiet(600)
            emu.frames(2)
            shoot()
            _take_key(emu)
            prev = emu.text_state()
            waited += 10
            continue
        if prev == "busy" and st != "busy":
            emu.frames(2)
            shoot()
        elif every and since >= every and st != "busy" and not emu.fading():
            shoot(periodic=True)
        prev = st
        emu.frames(2)
        waited += 2
        since += 2
    raise hns.TourTimeout("fieldwatch %s: no %s after %d frames (callback2 %s, tasks %s)"
                          % (prefix, target, maxf, emu.cb2_name(), [t[2] for t in emu.tasks()]))


@script_op("flags")
def _op_flags(emu, f, path):
    print("flags " + " ".join("%s=%d" % (n, emu.get_flag(emu.const(n))) for n in f[1:]))


if __name__ == "__main__":
    sys.argv[0] = hns.__file__
    sys.exit(hns.main())
