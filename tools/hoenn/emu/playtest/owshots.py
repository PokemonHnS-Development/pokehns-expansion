"""Part 20a: screenshot overworld Pokémon. Run from the harness dir:
   python3 owshots.py TZ TAG MAP...   (TZ e.g. Etc/GMT+7 for day, Etc/GMT-4 for night;
   mGBA's clock follows TZ). Writes p20/ow_TAG_MAP.png."""
import sys, os, json; sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), "..")); sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", ".."))
from pt import *
DATA = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "..", "..", "..", "data", "maps")
import gen_hoenn_ow_mons as G
tz, tag = sys.argv[1], sys.argv[2]
os.environ["TZ"] = tz
e = Emu("pt.gba", "pt.elf")
maps = sys.argv[3:]
for name in maps:
    d = json.load(open(os.path.join(DATA, name, "map.json")))
    mons = [(o["x"], o["y"]) for o in d["object_events"] if o["script"] == "HoennSeek_EventScript_OWMon"]
    occ = {(o["x"], o["y"]) for o in d["object_events"]}
    w, h, cells = G.grid(d["layout"])
    # the screen (15x10) that holds the most mons, then the nearest free land tile to its center
    if not mons:
        print(name, "no mons"); continue
    best = max(((sum(1 for mx, my in mons if abs(mx - x) <= 7 and abs(my - y) <= 4), x, y) for (x, y) in mons))
    _, cx, cy = best
    cand = [(abs(x - cx) + abs(y - cy), x, y) for (x, y), (c, el, b, cv) in cells.items()
            if not c and b in G.LAND and (x, y) not in occ and (x, y) not in mons]
    if not cand:
        print(name, "no land tile"); continue
    _, px, py = min(cand)
    g, n = map_of(name)
    s = e.go("pt/birch1.ss", g, n, px, py, "_ow.ss")
    e.run([f"loadstate {s}", "wait 90", f"shot p20/ow_{tag}_{name}.png"])
    print(name, (px, py), best[0], flush=True)
