#!/usr/bin/env python3
"""hns.py plus the r2-r4 tour ops (scripts/r2_pokegear_ribbons_contests/rc.py: fieldwatch,
partyclear, ...) and fmwatch, for the r5 field-move tours (tours/r5_fieldmoves).
Run:  fm.py tour ROM OUT --tours tours/r5_fieldmoves [--clip] [--only RE]

    fmwatch PREFIX [MAX] [EVERY]   fieldwatch PREFIX free, except that a wild battle on the way
                                   (a Rock Smash or Headbutt encounter, RockSmashWildEncounter,
                                   src/wild_encounter.c:928) does not end the watch: its pages are
                                   walked to the action menu (PREFIX_b_NN), the menu is shot
                                   (PREFIX_b_action), RUN is chosen and the walk goes on through the
                                   run-away pages and any field text after the battle (the item
                                   finds of EventScript_SmashRock) until the player is free
                                   (PREFIX_r_NN). Prints "fmwatch PREFIX: battle" or ": no battle".
"""
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(HERE, "..", ".."))                      # tools/hebrew/emu
sys.path.insert(0, os.path.join(HERE, "..", "r2_pokegear_ribbons_contests"))
import hns  # noqa: E402
import rc  # noqa: E402,F401  (registers the r2-r4 ops)
from hns import script_op, HnsError, TourTimeout, _arg  # noqa: E402


@script_op("fmwatch")
def _op_fmwatch(emu, f, path):
    prefix = f[1]
    maxf, every = _arg(f, 2, 20000), _arg(f, 3, 0)
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

    # the A that started the scene has to lock the player first (the script starts next frame)
    emu.wait_until(lambda: not emu.controllable(), 60, "the field script to start", step=1)
    while waited < maxf:
        if hns.in_battle(emu):
            pages, end = hns.battle_walk(emu, prefix + "_b", ("input:HandleInputChooseAction",))
            emu.wait_quiet(600)
            rc._shot(emu, prefix + "_b_action")
            hns.battle_cursor(emu, "gActionSelectionCursor", hns.BATTLE_ACTIONS["RUN"])
            emu.tap("A", 4)
            # After the battle the field script stays in its `waitstate` (EventScript_SmashRock
            # data/scripts/field_move_scripts_hns.inc:99; CONTEXT_WAITING, src/script.c): nothing
            # re-enables it, so the item finds after it never run and the player walks with the
            # context still waiting. Emu.controllable() wants CONTEXT_SHUTDOWN, so the walk ends
            # on its idle limit; then the waiting context is shut down (as the next script the
            # player starts would replace it) so the tour can go on.
            try:
                pages2, end2 = hns.battle_walk(emu, prefix + "_r", ("free",), maxframes=400)
            except HnsError:
                ctx = emu.sym("sGlobalScriptContext")
                status = emu.sym("sGlobalScriptContextStatus")
                where = emu.elf.where(emu.r32(ctx + 8))
                if not (emu.in_overworld() and emu.r8(status) == 1 and emu.r8(emu.sym("sLockFieldControls")) == 0):
                    print("fmwatch %s: not free after the battle: script %s, status %d, lock %d, tasks %s"
                          % (prefix, where, emu.r8(status), emu.r8(emu.sym("sLockFieldControls")),
                             [t[2] for t in emu.tasks()]))
                    raise
                pages2, end2 = getattr(emu, "_bw_pages", 0), "script left waiting at %s" % where
                emu.w8(status, 2)
                emu.wait_controllable(600)
            print("fmwatch %s: battle, %d+%d page(s), %s @%d" % (prefix, pages, pages2, end2, emu.sync()))
            return
        if emu.controllable():
            emu.frames(8)
            if emu.controllable() and not hns.in_battle(emu):
                print("fmwatch %s: no battle, %d shot(s) @%d" % (prefix, n, emu.sync()))
                return
            continue
        if emu.cb2() == emu.sym("CB2_Overworld") and emu.tasks_named(emu.MENU_TASKS):
            emu.wait_menu_ready()
            emu.frames(2)
            shoot()
            raise HnsError("fmwatch %s: unexpected menu %s" % (prefix, emu.tasks_named(emu.MENU_TASKS)[0]))
        st = emu.text_state()
        if emu.wants_key():
            emu.wait_quiet(600)
            emu.frames(2)
            shoot()
            emu.tap("A", 0)
            emu.wait_until(lambda: not emu.wants_key(), 90, "the text to take the key", step=1)
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
    raise TourTimeout("fmwatch %s: not free after %d frames (callback2 %s)" % (prefix, maxf, emu.cb2_name()))


if __name__ == "__main__":
    sys.argv[0] = hns.__file__
    sys.exit(hns.main())
