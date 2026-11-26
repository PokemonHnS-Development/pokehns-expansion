"""Part 20a: walk in grass/caves until a wild battle starts and screenshot the battle
background (also prints gBattleEnvironment). Run from the harness dir; writes p20/bg_MAP.png."""
import sys, os, json; sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), "..")); sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", ".."))
from pt import *
DATA = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "..", "..", "..", "data", "maps")
import gen_hoenn_ow_mons as G
e = Emu("pt.gba", "pt.elf")
B = "pt/birch1.ss"
def spot(name, want_grass=True):
    d = json.load(open(os.path.join(DATA, name, "map.json")))
    w, h, cells = G.grid(d["layout"])
    occ = {(o["x"], o["y"]) for o in d["object_events"]}
    best = None
    for (x, y), (c, el, b, cv) in sorted(cells.items(), key=lambda kv: (kv[0][1], kv[0][0])):
        if c or (x, y) in occ or x < 2 or x >= w - 2: continue
        ok = all(cells[(x + dx, y)][0] == 0 and cells[(x + dx, y)][1] == el and (x + dx, y) not in occ for dx in (-1, 1))
        if not ok: continue
        if want_grass and b in G.GRASS: return x, y
        if not want_grass and b in G.LAND and best is None: best = (x, y)
    return best
tests = [("Route111", True), ("Route113", True), ("Route119", True), ("FieryPath", False), ("MeteorFalls_1F_1R", False),
         ("ShoalCave_LowTideIceRoom", False), ("GraniteCave_1F", False), ("VictoryRoad_1F", False), ("MtPyre_Exterior", True),
         ("Route120", True), ("JaggedPass", True), ("SafariZone_North", True)]
res = {}
for name, grass in tests:
    xy = spot(name, grass)
    if not xy: res[name] = "no spot"; continue
    g, n = map_of(name)
    s = e.go(B, g, n, xy[0], xy[1], "_bg.ss")
    cmds = [f"loadstate {s}"]
    for i in range(40):
        cmds += ["press LEFT 16", "wait 2", "press RIGHT 16", "wait 2"]
    cmds += ["wait 330", f"shot p20/bg_{name}.png", f"r8 {e.s('gMain') + 0x439:x}", f"r8 {e.s('gBattleEnvironment'):x}"]
    out = e.run(cmds)
    res[name] = (xy, [l.split(': ')[1] for l in out])
    print(name, res[name], flush=True)
