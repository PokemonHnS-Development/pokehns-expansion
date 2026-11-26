#!/usr/bin/env python3
"""Hoenn & Seek 2.0 (part 8a): list HnS's fake doors.

A fake door is an outdoor door metatile (MB_NON_ANIMATED_DOOR / MB_ANIMATED_DOOR)
on an HnS map (game_version "hns", outdoor map type) with no warp on it. HnS draws
many town buildings without interiors; 2.0-plan section 3a opens them.

Adjacent door tiles (double doors) count as one building. For each building the
report says what else is on or next to the door (a sign or a script reads it as
"locked", a warp next to it means the door is decorative or part of a building
that already opens elsewhere).

Usage: tools/hoenn/find_fake_doors.py [--json OUT]
Prints a table; --json writes the list (used by gen_hoenn_buildings.py's review).
"""
import json, os, re, struct, sys

ROOT = os.path.normpath(os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", ".."))
P = lambda *a: os.path.join(ROOT, *a)
OUTDOOR = {"MAP_TYPE_TOWN", "MAP_TYPE_CITY", "MAP_TYPE_ROUTE", "MAP_TYPE_OCEAN_ROUTE"}


def behavior_ids():
    """Metatile behavior name -> number, from the enum."""
    ids, n = {}, -1
    for line in open(P("include/constants/metatile_behaviors.h")):
        m = re.match(r"\s*(MB_\w+)\s*(?:=\s*(\w+))?\s*,", line)
        if m:
            n = int(m.group(2), 0) if m.group(2) else n + 1
            ids[m.group(1)] = n
    return ids


MB = behavior_ids()
DOORS = {MB["MB_NON_ANIMATED_DOOR"], MB["MB_ANIMATED_DOOR"]}

_hdr = open(P("src/data/tilesets/headers.h")).read()
_met = open(P("src/data/tilesets/metatiles.h")).read()
_attr_cache = {}


def attributes(tileset):
    if tileset not in _attr_cache:
        blk = _hdr[_hdr.index(tileset + " ="):][:900]
        sym = re.search(r"metatileAttributes = (\w+)", blk).group(1)
        m = re.search(sym + r'\[\] = INCBIN_U16\("([^"]+)"\)', _met)
        data = open(P(m.group(1)), "rb").read()
        _attr_cache[tileset] = struct.unpack("<%dH" % (len(data) // 2), data)
    return _attr_cache[tileset]


def layouts():
    return {l["id"]: l for l in json.load(open(P("data/layouts/layouts.json")))["layouts"] if "id" in l}


def door_tiles(layout):
    """[(x, y, metatile)] of door metatiles in a layout."""
    prim, sec = attributes(layout["primary_tileset"]), attributes(layout["secondary_tileset"])
    nprim = 640 if layout.get("layout_version") == "hns" else 512
    data = open(P(layout["blockdata_filepath"]), "rb").read()
    w, out = layout["width"], []
    for i in range(len(data) // 2):
        mt = struct.unpack_from("<H", data, 2 * i)[0] & 0x3FF
        attr = prim[mt] if mt < nprim else (sec[mt - nprim] if mt - nprim < len(sec) else 0)
        if attr & 0xFF in DOORS:
            out.append((i % w, i // w, mt))
    return out


def scan():
    lays = layouts()
    found = []
    for name in sorted(os.listdir(P("data/maps"))):
        path = P("data/maps", name, "map.json")
        if not os.path.exists(path):
            continue
        m = json.load(open(path))
        if m.get("game_version") != "hns" or m.get("map_type") not in OUTDOOR or m["layout"] not in lays:
            continue
        warps = {(w["x"], w["y"]) for w in m.get("warp_events") or []}
        signs = {(b["x"], b["y"]): b.get("script", b.get("type")) for b in m.get("bg_events") or []}
        coords = {(c["x"], c["y"]): c.get("script") for c in m.get("coord_events") or []}
        doors = [d for d in door_tiles(lays[m["layout"]]) if (d[0], d[1]) not in warps]
        seen = set()
        for x, y, mt in doors:
            if (x, y) in seen:
                continue
            group = [(x, y)]
            seen.add((x, y))
            # double doors: neighbours in the same row
            for dx in (1, 2):
                if any(d[0] == x + dx and d[1] == y for d in doors):
                    group.append((x + dx, y))
                    seen.add((x + dx, y))
                else:
                    break
            near_warp = sorted((wx, wy) for wx, wy in warps
                               if any(abs(wx - gx) <= 1 and abs(wy - gy) <= 1 for gx, gy in group))
            notes = []
            for gx, gy in group:
                for (sx, sy), s in signs.items():
                    if abs(sx - gx) + abs(sy - gy) <= 1:
                        notes.append("sign %s at %d,%d" % (s, sx, sy))
                for (cx, cy), s in coords.items():
                    if (cx, cy) in ((gx, gy), (gx, gy + 1)):
                        notes.append("trigger %s at %d,%d" % (s, cx, cy))
            found.append({"map": name, "x": x, "y": y, "width": len(group), "metatile": mt,
                          "warp_next_to": near_warp, "notes": notes})
    return found


def main():
    found = scan()
    for f in found:
        print("%-34s %3d,%-3d w%d mt%-4d %s %s" % (f["map"], f["x"], f["y"], f["width"], f["metatile"],
                                                ("warp next to %s" % f["warp_next_to"]) if f["warp_next_to"] else "",
                                                "; ".join(f["notes"])))
    print("%d fake doors on %d maps" % (len(found), len({f["map"] for f in found})))
    if "--json" in sys.argv:
        out = sys.argv[sys.argv.index("--json") + 1]
        json.dump(found, open(out, "w"), indent=1)


if __name__ == "__main__":
    main()
