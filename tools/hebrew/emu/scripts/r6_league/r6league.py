#!/usr/bin/env python3
"""hns.py plus the ops the r6 gym leader / Elite Four / champion / rematch tours use
(tours/r6_league/*.txt). Everything from scripts/r5_legends/r5leg.py (bwin, scene, stepto,
approach, closeall, pick, ss/sl, fieldwatch, walkto, objs ...), plus:

    sceneto PREFIX MAP [MAX] [EVERY]
                            `scene`, but it also returns as soon as gSaveBlock1 location is MAP
                            (a MAP_* name), e.g. the Hall of Fame warp after Lance; one shot then
    bwinwith MOVE PREFIX [MAXTURNS]
                            bwin, but the player's battler uses MOVE instead of Ice Shard
                            (e.g. MOVE_SHADOW_SNEAK against a Wonder Guard Shedinja)
    bitem PREFIX TURNS      for TURNS turns: at each action menu put the foe at 1/8 HP and make the
                            player's battler use Splash at full HP, so a trainer AI with items
                            (Full Restore) uses one; one shot per page (PREFIX_tNN_MM)
    pickd N                 a choice menu that opens on row 0: N x DOWN, then A (the ELF has
                            several static sMenu symbols, so `pick` cannot read the cursor)
    periodic PREFIX FRAMES EVERY
                            one shot every EVERY frames for FRAMES frames, dropping repeats
                            (door closing, lighting, camera shake)
Run:  r6league.py tour ROM OUT --tours <emu>/tours/r6_league [--clip] [--only RE]
"""
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(HERE, "..", "r5_legends"))
import r5leg  # noqa: E402,F401  (registers the r5 ops on top of hns.py)
import hns  # noqa: E402
import rc  # noqa: E402
from hns import script_op, _arg, HnsError  # noqa: E402

_SCENE = hns.SCRIPT_OPS["scene"]


@script_op("sceneto")
def _op_sceneto(emu, f, path):
    prefix, target = f[1], f[2]
    maxf, every = _arg(f, 3, 30000), _arg(f, 4, 0)
    g, n = hns.map_lookup(emu.elf, target)

    def there():
        (lg, ln, _, _, _), _ = emu.location()
        return (lg, ln) == (g, n)

    real_frames = emu.frames
    hit = [False]

    class Arrived(Exception):
        pass

    def frames(k, *a, **kw):
        r = real_frames(k, *a, **kw)
        if not hit[0] and there():
            hit[0] = True
            raise Arrived()
        return r

    emu.frames = frames
    try:
        _SCENE(emu, ["scene", prefix, str(maxf), str(every)], path)
    except Arrived:
        pass
    finally:
        emu.frames = real_frames
    if hit[0]:
        emu.wait_quiet(600)
        emu.frames(2)
        emu.shot(prefix + "_arrived")
        emu.shots = getattr(emu, "shots", []) + [prefix + "_arrived"]
        print("sceneto %s: at %s @%d" % (prefix, target, emu.sync()))


@script_op("periodic")
def _op_periodic(emu, f, path):
    prefix, total, every = f[1], int(f[2]), int(f[3])
    last, k, t = None, 0, 0
    while t < total:
        emu.frames(every)
        t += every
        k += 1
        p = rc._shot(emu, "%s_%02d" % (prefix, k))
        data, same = rc._same_as(p, last)
        if same:
            os.remove(p)
            emu.shots = emu.shots[:-1]
            continue
        last = data
    print("periodic %s: %d frame(s) @%d" % (prefix, total, emu.sync()))


@script_op("bwinwith")
def _op_bwinwith(emu, f, path):
    want = emu.const(f[1])
    real_const = emu.const

    def const(name, *a, **kw):
        if name == "MOVE_ICE_SHARD":
            return want
        return real_const(name, *a, **kw)

    emu.const = const
    try:
        hns.SCRIPT_OPS["bwin"](emu, ["bwin"] + f[2:], path)
    finally:
        emu.const = real_const


@script_op("bitem")
def _op_bitem(emu, f, path):
    prefix, turns = f[1], int(f[2])
    bm = emu.sym("gBattleMons")
    splash = emu.const("MOVE_SPLASH")
    for turn in range(turns):
        n, end = hns.battle_walk(emu, "%s_t%02d" % (prefix, turn), (), 60, 6000,
                                 stop_tasks=("Task_WeatherMain",))
        print("  bitem turn %d: %d page(s), %s" % (turn, n, end))
        if not end.startswith("input:HandleInputChooseAction"):
            if end.startswith("prompt:"):
                emu.tap("B", 4)
                continue
            raise HnsError("bitem %s: stopped at %s" % (prefix, end))
        mx = emu.r16(bm + 0x88 * 1 + 0x2E)
        emu.w16(bm + 0x88 * 1 + 0x2A, max(1, mx // 8))
        emu.w16(bm + 0x2A, emu.r16(bm + 0x2E))
        emu.w16(bm + 0x0C, splash)
        if emu.r8(bm + 0x25) == 0:
            emu.w8(bm + 0x25, 10)
        hns.wait_battle_input(emu, "HandleInputChooseAction")
        hns.battle_cursor(emu, "gActionSelectionCursor", 0)
        emu.tap("A", 4)
        hns.wait_battle_input(emu, "HandleInputChooseMove")
        hns.battle_cursor(emu, "gMoveSelectionCursor", 0)
        emu.tap("A", 4)
    print("bitem %s ok @%d" % (prefix, emu.sync()))


@script_op("pickd")
def _op_pickd(emu, f, path):
    emu.wait_menu_ready()
    for _ in range(int(f[1])):
        emu.tap("DOWN", 4)
        emu.wait_quiet(300)
    emu.frames(2)
    emu.pickd_n = getattr(emu, "pickd_n", 0) + 1
    name = "pickd_%02d_row%s" % (emu.pickd_n, f[1])
    emu.shot(name)
    emu.shots = getattr(emu, "shots", []) + [name]
    emu.tap("A", 4)
    print("pickd %s @%d" % (f[1], emu.sync()))


if __name__ == "__main__":
    sys.argv[0] = hns.__file__
    sys.exit(hns.main())
