#!/usr/bin/env python3
"""Round-7 Trainer Hill runs (Variety, Unique and Expert tag matches): the r2 runner
(scripts/r2_hill_tents/ht.py: battery or savestate in, one script, clip report on the Hebrew ROM)
plus the ops below. Run it from the fork root; HT_OUT is the output folder and holds
rom/pokehns-clip.gba and its .elf (links to the ROM under test):

    HT_OUT=OUT python3 tools/hebrew/emu/scripts/r7_hill/r7ht.py run he|en SCRIPT [--from S] [--to S] [--save SAV]

Ops added here (offsets measured on the tree with the build's ABI flags; same in the English tree):
    hillstate            print trainerHill.timer / bestTime and trainerHillTimes[0..3]
    hilltimer FRAMES     set trainerHill.timer (60 * 60 frames a minute)
    hillbest MODE FRAMES set trainerHill.bestTime and trainerHillTimes[MODE] (0 Normal .. 3 Expert)
    walkdbg 0|1          print every walkto step
    walkto2 X Y [FACE]   walkto that keeps every object position it has seen as blocked
"""
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
os.environ.setdefault("HNS_RUNNER", "../hns-tools/emu/hnsrun")     # hns reads it on import
sys.path.insert(0, os.path.join(HERE, "..", ".."))
sys.path.insert(0, os.path.join(HERE, "..", "r2_hill_tents"))
sys.path.insert(0, os.path.join(HERE, "..", "r3_frontier"))
import hns  # noqa: E402
from hns import script_op  # noqa: E402

TH_TIMER = 0x3D64        # offsetof(struct SaveBlock1, trainerHill.timer)
TH_BEST = 0x3D68         # offsetof(struct SaveBlock1, trainerHill.bestTime)
TH_TIMES = 0x3B40        # offsetof(struct SaveBlock1, trainerHillTimes)


def _fmt(fr):
    return "%d (%d:%02d.%02d)" % (fr, fr // 3600, fr % 3600 // 60, (fr % 60) * 168 // 100)


@script_op("hillstate")
def _op_hillstate(emu, f, path):
    sb1 = emu.sb1()
    times = [emu.r32(sb1 + TH_TIMES + 4 * i) for i in range(4)]
    print("hillstate timer %s best %s times %s" % (_fmt(emu.r32(sb1 + TH_TIMER)), _fmt(emu.r32(sb1 + TH_BEST)),
                                                  [_fmt(t) for t in times]))


@script_op("hilltimer")
def _op_hilltimer(emu, f, path):
    emu.w32(emu.sb1() + TH_TIMER, int(f[1], 0))
    _op_hillstate(emu, f, path)


@script_op("hillbest")
def _op_hillbest(emu, f, path):
    mode, fr = int(f[1], 0), int(f[2], 0)
    sb1 = emu.sb1()
    emu.w32(sb1 + TH_BEST, fr)
    emu.w32(sb1 + TH_TIMES + 4 * mode, fr)
    _op_hillstate(emu, f, path)


@script_op("walkto2")
def _op_walkto2(emu, f, path):
    """walkto2 X Y [FACE]: walkto (r2_hill_tents/hilltent_ops.py) that keeps every object position
    it has seen as blocked. Objects off camera are not spawned, so plain walkto can flip between two
    routes forever when trainers who walked up to the player stand in the way."""
    import hilltent_ops as ho
    goal = (int(f[1]), int(f[2]))
    face = f[3] if len(f) > 3 else None
    blocked, seen = set(), set()
    (g0, n0, _, _, _), _ = emu.location()
    for it in range(200):
        (g, n, _w, _x, _y), pos = emu.location()
        if (g, n) != (g0, n0):
            print("walkto2 %s: warp to %d.%d %s @%d" % (goal, g, n, pos, emu.sync()))
            return
        if pos == goal:
            break
        w, h, coll, behavior = ho.map_grid(emu)
        seen |= {(o[1], o[2]) for o in ho.objects(emu)}
        route = ho.bfs(w, h, coll, pos, goal, (blocked | seen) - {goal}, ho.ledge_map(emu, w, h, behavior),
                       ho.slide_map(emu, w, h, behavior), ho.ice_set(emu, w, h, behavior))
        if not route:
            raise hns.HnsError("walkto2: no path from %s to %s (blocked %s)" % (pos, goal, sorted(blocked | seen)))
        d = route[0]
        r = hns.go_step(emu, d)
        if getattr(emu, "_walk_dbg", 0):
            print("   walkto2 step %d: at %s route %s -> %s" % (it, pos, "".join(x[0] for x in route), r))
        if r is None:
            if not emu.controllable():
                print("walkto2 %s: taken at %s @%d" % (goal, emu.location()[1], emu.sync()))
                emu._walk_end = "taken"
                return
            dx, dy = {"UP": (0, -1), "DOWN": (0, 1), "LEFT": (-1, 0), "RIGHT": (1, 0)}[d]
            blocked.add((pos[0] + dx, pos[1] + dy))
            continue
        if r == "warp":
            print("walkto2 %s: warp at %s @%d" % (goal, emu.location(), emu.sync()))
            return
    else:
        raise hns.HnsError("walkto2: gave up")
    if face:
        emu.frames(2, face)
        emu.frames(14)
    print("walkto2 %s: reached @%d" % (goal, emu.sync()))


@script_op("walkdbg")
def _op_walkdbg(emu, f, path):
    """walkdbg 0|1: print every walkto step."""
    emu._walk_dbg = int(f[1])


if __name__ == "__main__":
    import ht
    sys.exit(ht.main())
