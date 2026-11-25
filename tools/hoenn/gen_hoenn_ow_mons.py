#!/usr/bin/env python3
"""Hoenn & Seek (part 20a): overworld Pokémon on Hoenn maps.

HnS places Pokémon objects (OBJ_EVENT_GFX_MON_BASE+SPECIES_X) in Johto/Kanto towns for
atmosphere and on routes to show what lives there. This does the same for Hoenn:

- routes, caves and other maps with a wild table get mons drawn from it (land table on
  grass or cave floor, surf table on open water); a map with a _Night table gets day
  mons (FLAG_DAY_POKEMON) and night mons (FLAG_NIGHT_POKEMON) sharing tiles;
- towns get the hand-picked mons in data/hoenn/ow_mons.json.

Spots are chosen from the layout: an open 3x3 of the same kind of tile (so a mon that
wanders one step never blocks a path or leaves its terrain), away from warps, signs,
triggers, map edges, other objects and trainers' lines of sight, and never more than 9
objects (11 in towns) within one screen. Generated objects run HoennSeek_EventScript_OWMon (cry); the
script name is how re-runs find and replace them. Placement is deterministic per map.
"""
import json, os, random, re, struct, zlib

ROOT = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "..")
P = lambda *a: os.path.join(ROOT, *a)
SCRIPT = "HoennSeek_EventScript_OWMon"
LAND_RATES = [20, 20, 10, 10, 10, 10, 5, 5, 4, 4, 1, 1]
WATER_RATES = [60, 30, 5, 4, 1]


def behaviors():
    names, i = {}, 0
    for line in open(P("include/constants/metatile_behaviors.h")):
        m = re.match(r"\s*(MB_\w+)\s*(?:=\s*(\w+))?,", line)
        if m:
            if m.group(2):
                i = int(m.group(2), 0)
            names[m.group(1)] = i
            i += 1
    return names


MB = behaviors()
GRASS = {MB[n] for n in ("MB_TALL_GRASS", "MB_LONG_GRASS", "MB_ASHGRASS")}
LAND = GRASS | {MB[n] for n in ("MB_NORMAL", "MB_SHORT_GRASS", "MB_SAND", "MB_CAVE", "MB_FOOTPRINTS",
                                "MB_INDOOR_ENCOUNTER", "MB_MOUNTAIN_TOP")}
WATER = {MB[n] for n in ("MB_POND_WATER", "MB_OCEAN_WATER")}


def tileset_attrs():
    """Per tileset: (attributes, covered) where covered[i] is True if metatile i draws
    anything on its top layer (a roof edge or treetop that would hide a mon or show it
    standing on top)."""
    sym2path = {}
    for m in re.finditer(r"const u16 (gMetatile(?:s|Attributes)_\w+)\[\] = INCBIN_U16\(\"([^\"]+)\"\)",
                         open(P("src/data/tilesets/metatiles.h")).read()):
        sym2path[m.group(1)] = m.group(2)
    ts = {}
    for m in re.finditer(r"const struct Tileset (gTileset_\w+) =\s*\{(.*?)\};", open(P("src/data/tilesets/headers.h")).read(), re.S):
        a = re.search(r"\.metatileAttributes = (\w+)", m.group(2))
        g = re.search(r"\.metatiles = (\w+)", m.group(2))
        if a and a.group(1) in sym2path and g and g.group(1) in sym2path:
            d = open(P(sym2path[a.group(1)]), "rb").read()
            attrs = struct.unpack("<%dH" % (len(d) // 2), d)
            t = open(P(sym2path[g.group(1)]), "rb").read()
            tiles = struct.unpack("<%dH" % (len(t) // 2), t)
            # layer type (attribute bits 12-15) 1 = COVERED draws both halves under objects
            covered = [(i >= len(attrs) or attrs[i] >> 12 != 1) and any(tiles[i * 8 + k] & 0x3FF for k in range(4, 8))
                       for i in range(len(tiles) // 8)]
            ts[m.group(1)] = (attrs, covered)
    return ts


TS = tileset_attrs()
LAYOUTS = {l["id"]: l for l in json.load(open(P("data/layouts/layouts.json")))["layouts"] if "id" in l}


def grid(layout_id):
    l = LAYOUTS[layout_id]
    w, h = l["width"], l["height"]
    d = struct.unpack("<%dH" % (w * h), open(P(l["blockdata_filepath"]), "rb").read()[: w * h * 2])
    (pri, pcov), (sec, scov) = TS[l["primary_tileset"]], TS[l["secondary_tileset"]]
    npri = 512  # Emerald layouts (layout_version emerald)
    cells = {}
    for y in range(h):
        for x in range(w):
            v = d[y * w + x]
            mt, col, elev = v & 0x3FF, (v >> 10) & 3, v >> 12
            if mt < npri:
                attr, cov = pri[mt], pcov[mt]
            else:
                i = mt - npri
                attr, cov = (sec[i], scov[i]) if i < len(sec) else (0, True)
            # a covered tile counts as blocked for placement
            cells[x, y] = (col or (2 if cov else 0), elev, attr & 0xFF)
    return w, h, cells


def species_weights(table, rates):
    wts = {}
    for i, mon in enumerate(table["mons"]):
        wts[mon["species"]] = wts.get(mon["species"], 0) + (rates[i] if i < len(rates) else 1)
    top = sorted(wts.items(), key=lambda kv: -kv[1])[:4]
    tot = sum(v for _, v in top)
    return [(s, v) for s, v in top if v * 100 >= tot * 8]


def pick(rng, wts):
    r = rng.uniform(0, sum(v for _, v in wts))
    for s, v in wts:
        r -= v
        if r <= 0:
            return s
    return wts[-1][0]


def main():
    cfg = json.load(open(P("data/hoenn/ow_mons.json")))
    kept = json.load(open(P("data/hoenn/maps.json")))["items"]
    wild = {}
    for e in json.load(open(P("data/hoenn/wild_encounters_hoenn.json")))["encounters"]:
        name = re.match(r"gHoenn_(\w+?)_hns(_Night)?$", e["base_label"])
        wild.setdefault(name.group(1), {})["night" if name.group(2) else "day"] = e
    total, maps_done = 0, 0
    for name in sorted(kept):
        path = P("data/maps", name, "map.json")
        m = json.load(open(path))
        objs = [o for o in m.get("object_events", []) if o.get("script") != SCRIPT]
        changed = len(objs) != len(m.get("object_events", []))
        m["object_events"] = objs
        skip = any(name.startswith(s) for s in cfg["skip"])
        mtype = m["map_type"]
        is_town = mtype in ("MAP_TYPE_TOWN", "MAP_TYPE_CITY")
        outdoorish = mtype in ("MAP_TYPE_TOWN", "MAP_TYPE_CITY", "MAP_TYPE_ROUTE", "MAP_TYPE_UNDERGROUND", "MAP_TYPE_OCEAN_ROUTE") \
            or any(name.startswith(s) for s in cfg["indoor_ok"])
        plan = []  # (kind, day_wts, night_wts, count, fixed_species_flag)
        if not skip and outdoorish:
            if name in cfg["towns"]:
                for sp, n, where in cfg["towns"][name]:
                    kind = "water" if where.startswith("water") else "land"
                    flag = {"day": "FLAG_DAY_POKEMON", "night": "FLAG_NIGHT_POKEMON", "water_night": "FLAG_NIGHT_POKEMON"}.get(where, "0")
                    plan.append((kind, "SPECIES_" + sp, flag, n))
            elif name in wild and not is_town:
                tabs = wild[name]
                cave = mtype == "MAP_TYPE_UNDERGROUND" or not mtype.endswith("ROUTE")
                never = {"SPECIES_" + sp for sp in cfg["never_species"]}
                for key, kind, rates in (("land_mons", "land", LAND_RATES), ("water_mons", "water", WATER_RATES)):
                    if key not in tabs["day"] or (kind == "land" and name in cfg["no_land"]):
                        continue
                    dw = [sw for sw in species_weights(tabs["day"][key], rates) if sw[0] not in never]
                    nw = [sw for sw in species_weights(tabs["night"][key], rates) if sw[0] not in never] \
                        if "night" in tabs and key in tabs["night"] else None
                    if not dw:
                        continue
                    plan.append((kind, dw, nw, "cave" if (kind == "land" and cave) else ("water" if kind == "water" else "route")))
        if not plan:
            if changed:
                json.dump(m, open(path, "w"), indent=2, ensure_ascii=False)
                open(path, "a").write("\n")
            continue

        w, h, cells = grid(m["layout"])
        rng = random.Random(zlib.crc32(name.encode()))
        blocked = set()

        def block(x0, y0, r):
            for yy in range(y0 - r, y0 + r + 1):
                for xx in range(x0 - r, x0 + r + 1):
                    blocked.add((xx, yy))

        for wp in m.get("warp_events", []):
            block(wp["x"], wp["y"], 2)
        for c in m.get("coord_events", []):
            block(c["x"], c["y"], 2)
        for b in m.get("bg_events", []):
            block(b["x"], b["y"], 1)
        pos = []  # existing object positions, for the per-screen limit
        for o in objs:
            x, y = int(o["x"]), int(o["y"])
            rx, ry = int(o.get("movement_range_x", 0) or 0), int(o.get("movement_range_y", 0) or 0)
            for yy in range(y - ry - 1, y + ry + 2):
                for xx in range(x - rx - 1, x + rx + 2):
                    blocked.add((xx, yy))
            pos.append((x, y))
            if o.get("trainer_type", "TRAINER_TYPE_NONE") != "TRAINER_TYPE_NONE":
                sight = int(o.get("trainer_sight_or_berry_tree_id", "0") or 0) + 1
                for d in range(-sight, sight + 1):
                    blocked.add((x + d, y))
                    blocked.add((x, y + d))

        def good(xx, yy, elev, kind):
            col, e, b = cells[xx, yy]
            return not col and e == elev and b in (WATER if kind == "water" else LAND)

        def open_spot(x, y, kind, full=False):
            """The tile and its 4 neighbours are open (full: the whole 3x3, needed to wander)."""
            if (x, y) in blocked or x < 3 or y < 3 or x >= w - 3 or y >= h - 3:
                return False
            elev = cells[x, y][1]
            ring = [(x + dx, y + dy) for dx in (-1, 0, 1) for dy in (-1, 0, 1) if full or not (dx and dy)]
            return all(good(xx, yy, elev, kind) for xx, yy in ring)

        limit = 11 if is_town else 9  # town counts include story objects that are hidden after Emerald

        def screen_ok(x, y):
            return sum(1 for px, py in pos if abs(px - x) <= 8 and abs(py - y) <= 6) < limit

        tiles = {k: sum(1 for c in cells.values() if not c[0] and c[2] in (WATER if k == "water" else LAND)) for k in ("land", "water")}
        spots = {}
        for k in ("land", "water"):
            cand = sorted(xy for xy in cells if open_spot(*xy, k))
            grass = [xy for xy in cand if cells[xy][2] in GRASS]
            rest = [xy for xy in cand if cells[xy][2] not in GRASS]
            rng.shuffle(grass)
            rng.shuffle(rest)
            spots[k] = rest + grass  # take() pops from the end: grass first

        def take(kind):
            while spots[kind]:
                x, y = spots[kind].pop()
                if (x, y) in blocked or not screen_ok(x, y):
                    continue
                block(x, y, 2)
                pos.append((x, y))
                return x, y
            return None

        def add(sp, x, y, flag, kind):
            wander_ok = open_spot(x, y, kind, full=True) or (x, y) in blocked and all(
                good(x + dx, y + dy, cells[x, y][1], kind) for dx in (-1, 0, 1) for dy in (-1, 0, 1))
            mv = rng.choice(["MOVEMENT_TYPE_WANDER_AROUND", "MOVEMENT_TYPE_LOOK_AROUND"] if kind == "water" else
                            ["MOVEMENT_TYPE_WANDER_AROUND", "MOVEMENT_TYPE_WANDER_AROUND", "MOVEMENT_TYPE_LOOK_AROUND",
                             "MOVEMENT_TYPE_WALK_IN_PLACE_DOWN", "MOVEMENT_TYPE_FACE_DOWN_LEFT_AND_RIGHT"])
            if mv == "MOVEMENT_TYPE_WANDER_AROUND" and not wander_ok:
                mv = "MOVEMENT_TYPE_LOOK_AROUND"
            r = 1 if mv == "MOVEMENT_TYPE_WANDER_AROUND" else 0
            m["object_events"].append({
                "graphics_id": "OBJ_EVENT_GFX_MON_BASE+" + sp, "x": x, "y": y, "elevation": 0,
                "movement_type": mv, "movement_range_x": r, "movement_range_y": r,
                "trainer_type": "TRAINER_TYPE_NONE", "trainer_sight_or_berry_tree_id": "0",
                "script": SCRIPT, "flag": flag})

        added = 0
        day_tiles = {"land": [], "water": []}  # town day mons; night mons share their tiles
        for entry in plan:
            if len(m["object_events"]) >= 62:
                break
            if isinstance(entry[1], str):  # town: fixed species
                kind, sp, flag, n = entry
                for _ in range(n):
                    if flag == "FLAG_NIGHT_POKEMON" and day_tiles[kind]:
                        xy = day_tiles[kind].pop(0)
                    else:
                        xy = take(kind)
                        if xy and flag == "FLAG_DAY_POKEMON":
                            day_tiles[kind].append(xy)
                    if xy and len(m["object_events"]) < 63:
                        add(sp, *xy, flag, kind)
                        added += 1
                continue
            kind, dw, nw, cls = entry
            n = max(1, min(cfg["caps"][cls], round(tiles[kind] / cfg["tiles_per_mon"][cls])))
            for i in range(n):
                if len(m["object_events"]) > 61:
                    break
                xy = take(kind)
                if not xy:
                    break
                sd = dw[i][0] if i < len(dw) else pick(rng, dw)
                night_only = [(s_, v) for s_, v in nw if s_ not in dict(dw)] if nw else []
                if not nw or sd in dict(nw):
                    add(sd, *xy, "0", kind)  # out day and night
                    added += 1
                    continue
                add(sd, *xy, "FLAG_DAY_POKEMON", kind)
                added += 1
                if night_only:
                    add(pick(rng, night_only), *xy, "FLAG_NIGHT_POKEMON", kind)
                    added += 1
        json.dump(m, open(path, "w"), indent=2, ensure_ascii=False)
        open(path, "a").write("\n")
        if added:
            total += added
            maps_done += 1
    print(f"{total} overworld Pokémon on {maps_done} Hoenn maps")


if __name__ == "__main__":
    main()
