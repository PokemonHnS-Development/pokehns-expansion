#!/usr/bin/env python3
"""hns.py plus the r2 service ops (scripts/r2_safari_pokeblock_bug_contest/r2sf.py: textwatch,
burst, scenewatch, scrollshots, scrollmem, warpraw, startmenux, ss, sl, loc, playwhile, bagseek,
bagpocket, waitwarp) and the ops the r3 Battle Frontier tours (bf_*.txt) use.
Run:  r3bf.py tour ROM OUT --tours <this folder> [--clip] [--only RE]

Added here:
    drive PREFIX TARGET [MAXPAGES] [MAXFRAMES]
        walk field dialogue through movements, warps and map scripts: one shot per text page
        (PREFIX_NN, then A), until TARGET:
            free            the player can walk
            menu            a script choice menu (multichoice / yes-no) reads input
            cb2:SYM         gMain.callback2 is SYM (a new screen, e.g. the Factory rental screen)
            task:SYM        a task running SYM is active
            battle          a battle has started (BattleMainCB2)
        Any other choice menu on the way stops the drive with an error.
    pick N              move a script menu's cursor (sMenu.cursorPos) to row N and press A
    pyrfloor            print the Pyramid floor state
    frontier            print the frontier challenge vars
"""
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(HERE, "..", ".."))                                # tools/hebrew/emu
sys.path.insert(0, os.path.join(HERE, "..", "r2_safari_pokeblock_bug_contest"))
import hns  # noqa: E402
import r2sf  # noqa: E402,F401  (registers the r2 ops)
from hns import script_op, HnsError, TourTimeout, _arg  # noqa: E402

LOADS = ("CB2_DoChangeMap", "CB2_LoadMap", "CB2_LoadMap2", "CB2_ReturnToField",
         "CB2_ReturnToFieldLocal", "CB2_ReturnToFieldContinueScript", "CB2_ReturnToFieldContinueScriptPlayMapMusic",
         "CB2_ReturnToFieldFadeFromBlack", "CB2_ReturnToFieldWithOpenMenu")


def _shot(emu, name):
    emu.frames(2)
    emu.shot(name)
    emu.shots = getattr(emu, "shots", []) + [name]
    if getattr(emu, "clip", None):
        try:
            emu.clip.poll(name)
        except Exception:
            pass


@script_op("drive")
def _op_drive(emu, f, path):
    prefix, target = f[1], f[2]
    maxpages = _arg(f, 3, 60)
    maxframes = _arg(f, 4, 6000)
    ow = emu.sym("CB2_Overworld")
    bcb2 = emu.sym("BattleMainCB2")
    want_cb2 = emu.sym(target[4:]) if target.startswith("cb2:") else None
    want_task = target[5:] if target.startswith("task:") else None
    n, idle = 0, 0
    last_box = None

    def reached():
        cb = emu.cb2()
        if want_cb2 is not None:
            return cb == want_cb2
        if want_task is not None:
            return emu.task_active(want_task)
        if target == "battle":
            return cb == bcb2
        if target == "free":
            return emu.controllable()
        return False

    while True:
        if reached():
            if target == "free":
                emu.frames(8)
                if not emu.controllable():
                    continue
            print("drive %s: %d page(s), reached %s @%d" % (prefix, n, target, emu.sync()))
            return
        if idle >= maxframes:
            raise TourTimeout("drive %s: stuck %d frames after %d page(s) (callback2 %s, tasks %s)"
                              % (prefix, idle, n, emu.cb2_name(), [t[2] for t in emu.tasks()]))
        if n >= maxpages:
            raise HnsError("drive %s: %d pages and no %s" % (prefix, n, target))
        cb = emu.cb2()
        if cb == ow:
            menus = emu.tasks_named(emu.MENU_TASKS)
            if menus:
                emu.wait_menu_ready()
                emu.frames(2)
                if target == "menu":
                    n += 1
                    _shot(emu, "%s_%02d" % (prefix, n))
                    print("drive %s: %d page(s), menu %s @%d" % (prefix, n, menus[0], emu.sync()))
                    return
                n += 1
                _shot(emu, "%s_%02d" % (prefix, n))
                raise HnsError("drive %s: unexpected menu %s" % (prefix, menus[0]))
        st = emu.text_state()
        if st == "busy" or emu.fading():
            emu.frames(2)
            idle += 2
            continue
        if emu.wants_key():
            emu.wait_quiet(600)
            box = hns.message_box(emu) if cb in (ow, bcb2) else None
            if box is None or box != last_box:
                n += 1
                _shot(emu, "%s_%02d" % (prefix, n))
            last_box = box
            emu.tap("A", 0)
            emu.wait_until(lambda: not emu.wants_key(), 90, "the text to take the key", step=1)
            idle = 0
            continue
        emu.frames(2)
        idle += 2


@script_op("pick")
def _op_pick(emu, f, path):
    """pick N [nopress]: move the script menu cursor (sMenu.cursorPos, menu:sMenu+2) to row N, press A."""
    want = int(f[1])
    try:
        addr = emu.sym("menu:sMenu") + 2
    except HnsError:
        addr = emu.sym("sMenu") + 2
    emu.wait_menu_ready()
    for _ in range(12):
        cur = emu.r8(addr)
        if cur == want:
            break
        emu.tap("DOWN" if cur < want else "UP", 4)
        emu.wait_quiet(300)
    if emu.r8(addr) != want:
        raise HnsError("pick: cursor stayed %d" % emu.r8(addr))
    if not (len(f) > 2 and f[2] == "nopress"):
        emu.tap("A", 4)
    print("pick %d @%d" % (want, emu.sync()))


@script_op("vars")
def _op_vars(emu, f, path):
    """vars NAME...: print save-block vars (VAR_*)."""
    sb1 = emu.sb1()
    out = []
    for name in f[1:]:
        v = emu.const(name)
        out.append("%s=%d" % (name, emu.r16(sb1 + hns.OFF["SB1.vars"] + 2 * (v - 0x4000))))
    print("vars " + " ".join(out))


if __name__ == "__main__":
    sys.argv[0] = hns.__file__
    sys.exit(hns.main())
