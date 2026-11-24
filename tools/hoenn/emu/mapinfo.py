#!/usr/bin/env python3
"""ASCII view of a map for planning emulator test routes.
    mapinfo.py MAP_NAME [x0 y0 x1 y1]
Legend: . walkable  # blocked  ~ water  W waterfall  D deep water (dive spot)  w warp  o object  ? unknown
"""
import json, os, re, struct, sys
ROOT = os.path.normpath(os.path.join(os.path.dirname(__file__), "..", "..", ".."))
def rd(p): return open(os.path.join(ROOT, p), "rb").read()

beh_txt = open(os.path.join(ROOT, "include/constants/metatile_behaviors.h")).read()
enum = beh_txt[beh_txt.index("{") + 1:beh_txt.index("}")]
names, v = {}, 0
for line in enum.splitlines():
    m = re.match(r"\s*(MB_\w+)(?:\s*=\s*(\w+))?", line)
    if m:
        if m.group(2): v = int(m.group(2), 0)
        names[v] = m.group(1); v += 1

def tileset_attr_path(sym):
    t = open(os.path.join(ROOT, "src/data/tilesets/metatiles.h")).read()
    m = re.search(r"gMetatileAttributes_" + sym + r"\[\] = INCBIN_U(16|32)\(\"([^\"]+)\"\)", t)
    return (m.group(2), int(m.group(1)) // 8) if m else (None, None)

def main():
    name = sys.argv[1]
    md = json.load(open(os.path.join(ROOT, f"data/maps/{name}/map.json")))
    lay = next(l for l in json.load(open(os.path.join(ROOT, "data/layouts/layouts.json")))["layouts"] if l.get("id") == md["layout"])
    w, h = lay["width"], lay["height"]
    ver = lay.get("layout_version", "emerald")
    nprim = {"emerald": 512, "hns": 640, "frlg": 640}[ver]
    blk = struct.unpack(f"<{w*h}H", rd(lay["blockdata_filepath"]))
    attrs = {}
    for which in ("primary_tileset", "secondary_tileset"):
        sym = lay[which].replace("gTileset_", "")
        path, size = tileset_attr_path(sym)
        data = rd(path)
        vals = struct.unpack(f"<{len(data)//size}{'H' if size == 2 else 'I'}", data)
        attrs[which] = vals
    mask = 0x1FF if ver == "frlg" else 0xFF
    def beh(mid):
        if mid < nprim: a = attrs["primary_tileset"]; i = mid
        else: a = attrs["secondary_tileset"]; i = mid - nprim
        return names.get(a[i] & mask, "?") if i < len(a) else "?"
    x0, y0, x1, y1 = (0, 0, w - 1, h - 1) if len(sys.argv) < 6 else map(int, sys.argv[2:6])
    warps = {(e["x"], e["y"]): i for i, e in enumerate(md.get("warp_events", []))}
    objs = {(e["x"], e["y"]): e.get("graphics_id", "") for e in md.get("object_events", [])}
    print(f"{name}: {w}x{h} layout={lay['id']} ver={ver}")
    print("    " + "".join(str(x % 10) for x in range(x0, x1 + 1)))
    for y in range(y0, y1 + 1):
        row = ""
        for x in range(x0, x1 + 1):
            b = blk[y * w + x]; mid = b & 0x3FF; col = (b >> 10) & 3; n = beh(mid)
            if (x, y) in warps: c = "w"
            elif (x, y) in objs: c = "o"
            elif "WATERFALL" in n: c = "W"
            elif n == "MB_DEEP_WATER": c = "D"
            elif n in ("MB_OCEAN_WATER", "MB_POND_WATER", "MB_SEMI_DEEP_WATER", "MB_INTERIOR_DEEP_WATER", "MB_SOOTOPOLIS_DEEP_WATER", "MB_FAST_WATER", "MB_NO_SURFACING", "MB_EASTWARD_CURRENT", "MB_WESTWARD_CURRENT", "MB_NORTHWARD_CURRENT", "MB_SOUTHWARD_CURRENT"): c = "~"
            elif col: c = "#"
            else: c = "."
            row += c
        print(f"{y:3} {row}")
    for (x, y), i in sorted(warps.items(), key=lambda k: k[1]): print(f"warp {i}: ({x},{y}) -> {md['warp_events'][i]['dest_map']}")
    for (x, y), g in objs.items():
        if any(k in g for k in ("WHIRLPOOL", "BOULDER", "BREAKABLE", "CUTTABLE")): print(f"object {g} at ({x},{y})")

if __name__ == "__main__":
    main()
