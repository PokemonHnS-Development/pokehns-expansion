#!/usr/bin/env python3
"""Hoenn & Seek 2.0 (part 4b): trainer followers.

Puts a Pokémon object next to each trainer listed in data/hoenn/trainer_followers.json
(gym leaders, the Elite Four, Red), using the species' overworld sprite, like HGSS's
leaders standing with their ace. No code: each follower is one object event (~24 bytes).

For each entry the generator finds the trainer object on the map (by graphics_id) and
appends a follower object:
  - graphics_id OBJ_EVENT_GFX_MON_BASE+SPECIES_X;
  - walks in place facing the way the trainer faces (down for MOVEMENT_TYPE_NONE);
  - the trainer's flag, so it hides whenever the trainer does;
  - the trainer's elevation;
  - script HoennSeek_EventScript_TrainerFollower (data/scripts/hoenn_followers.inc), which
    plays the cry. The script name is how re-runs find and replace the objects, so this is
    idempotent. Run it after gen_hoenn_trainers.py and gen_hoenn_ow_mons.py (both rewrite
    Hoenn map.json objects; neither touches objects with this script).

TILE CHOICE (unless the entry gives "at"): the first of straight behind (skipped for a
trainer facing up), right, left, up-right, up-left, down-right, down-left of the trainer
where
  - the tile is walkable floor (collision 0, a plain behavior) at the trainer's elevation
    (or elevation 0, which matches any);
  - no object, warp, sign or trigger is on it, and it isn't in front of any object;
  - no neighbour is ice, a slide/spin/arrow tile or a current (a follower next to a sliding
    puzzle could end a slide early or trap the player);
  - no trainer's line of sight crosses it (it would block their walk up to the player);
  - blocking it doesn't cut the player off from anything: an object, warp, sign or trigger,
    or a tile next to an object or sign (flood fill from the warps; a bare dead-end corner
    behind the follower is fine).
The script stops with an error if no tile fits, so a new entry never lands somewhere odd.
"""
import json, os, re, struct, sys

ROOT = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "..")
P = lambda *a: os.path.join(ROOT, *a)
SCRIPT = "HoennSeek_EventScript_TrainerFollower"
DIRS = {"DOWN": (0, 1), "UP": (0, -1), "LEFT": (-1, 0), "RIGHT": (1, 0)}


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
# Tiles a follower may stand on.
FLOOR = {MB[n] for n in ("MB_NORMAL", "MB_SHORT_GRASS", "MB_SAND", "MB_CAVE", "MB_INDOOR_ENCOUNTER",
                         "MB_MOUNTAIN_TOP", "MB_FOOTPRINTS", "MB_SNOW") if n in MB}
# Tiles that move the player on their own: never next to a follower.
FORCED = {v for n, v in MB.items()
          if re.search(r"ICE|SLIDE_|WALK_(EAST|WEST|NORTH|SOUTH)|SPIN_|STOP_SPINNING|ARROW_WARP|CURRENT|SLOPE", n)
          and n != "MB_BRIDGE_OVER_ICE"}


def tilesets():
    """Metatile attribute arrays per tileset symbol (behavior = low byte)."""
    sym2path = {}
    for m in re.finditer(r"const u16 (gMetatileAttributes_\w+)\[\] = INCBIN_U16\(\"([^\"]+)\"\)",
                         open(P("src/data/tilesets/metatiles.h")).read()):
        sym2path[m.group(1)] = m.group(2)
    ts = {}
    for m in re.finditer(r"const struct Tileset (gTileset_\w+) =\s*\{(.*?)\};",
                         open(P("src/data/tilesets/headers.h")).read(), re.S):
        a = re.search(r"\.metatileAttributes = (\w+)", m.group(2))
        if a and a.group(1) in sym2path:
            d = open(P(sym2path[a.group(1)]), "rb").read()
            ts[m.group(1)] = struct.unpack("<%dH" % (len(d) // 2), d)
    return ts


TS = tilesets()
LAYOUTS = {l["id"]: l for l in json.load(open(P("data/layouts/layouts.json")))["layouts"] if "id" in l}


def grid(layout_id):
    """{(x, y): (collision, elevation, behavior)} for a layout."""
    l = LAYOUTS[layout_id]
    w, h = l["width"], l["height"]
    d = struct.unpack("<%dH" % (w * h), open(P(l["blockdata_filepath"]), "rb").read()[: w * h * 2])
    pri, sec = TS[l["primary_tileset"]], TS[l["secondary_tileset"]]
    npri = 640 if l.get("layout_version") == "hns" else 512  # primary tileset size
    cells = {}
    for y in range(h):
        for x in range(w):
            v = d[y * w + x]
            mt = v & 0x3FF
            attr = pri[mt] if mt < npri else (sec[mt - npri] if mt - npri < len(sec) else 0)
            cells[x, y] = (v >> 10 & 3, v >> 12, attr & 0xFF)
    return cells


def facing(obj):
    for d in DIRS:
        if obj["movement_type"].endswith("_" + d):
            return d
    return "DOWN"


def reachable(cells, m, objs, extra_block=None):
    """Tiles the player can walk to from the warps (objects' tiles count as stops, not walls,
    so a tile only reachable by walking through an NPC still counts as reachable)."""
    obj_tiles = {(int(o["x"]), int(o["y"])) for o in objs}
    seen, todo = set(), [(w["x"], w["y"]) for w in m.get("warp_events", [])]
    while todo:
        xy = todo.pop()
        if xy in seen or xy not in cells or xy == extra_block:
            continue
        seen.add(xy)
        if xy in obj_tiles:
            continue  # can stand next to an object, not walk through it
        x, y = xy
        for dx, dy in DIRS.values():
            n = (x + dx, y + dy)
            if n in cells and not cells[n][0] and n not in seen:
                todo.append(n)
    return seen


def sight_tiles(objs):
    out = set()
    for o in objs:
        if o.get("trainer_type", "TRAINER_TYPE_NONE") in ("TRAINER_TYPE_NONE", "0"):
            continue
        sight = int(o.get("trainer_sight_or_berry_tree_id", "0") or 0)
        x, y = int(o["x"]), int(o["y"])
        dirs = DIRS.values() if "LOOK_AROUND" in o["movement_type"] or "ROTATE" in o["movement_type"] \
            else [DIRS[facing(o)]]
        for dx, dy in dirs:
            for k in range(1, sight + 1):
                out.add((x + dx * k, y + dy * k))
    return out


def choose_tile(name, m, cells, objs, trainer):
    tx, ty = int(trainer["x"]), int(trainer["y"])
    fdx, fdy = DIRS[facing(trainer)]
    # The tile in front of every object that faces a fixed way: where the player stands to
    # talk to it (Tate's front is next to Liza).
    fronts = {(int(o["x"]) + DIRS[facing(o)][0], int(o["y"]) + DIRS[facing(o)][1]) for o in objs}
    taken = {(int(o["x"]), int(o["y"])) for o in objs}
    taken |= {(e["x"], e["y"]) for k in ("warp_events", "coord_events", "bg_events") for e in m.get(k, [])}
    sight = sight_tiles(objs)
    before = reachable(cells, m, objs)
    # Tiles that matter: anything on them, or next to something the player can talk to or
    # check. Cutting off a bare dead-end corner is fine.
    things = taken | {(int(o["x"]) + a, int(o["y"]) + b) for o in objs for a, b in DIRS.values()}
    things |= {(e["x"] + a, e["y"] + b) for e in m.get("bg_events", []) for a, b in DIRS.values()}
    useful = before & things
    elev = int(trainer.get("elevation", 0))
    # Order: beside, then behind, then in front (diagonals), relative to the trainer's facing.
    sx, sy = -fdy, fdx  # one side
    order = [(sx, sy), (-sx, -sy), (sx - fdx, sy - fdy), (-sx - fdx, -sy - fdy),
             (sx + fdx, sy + fdy), (-sx + fdx, -sy + fdy)]
    # Straight behind the trainer comes first where there's room (Bryan, part 17r): it
    # looks cleaner and big sprites stop covering their trainer. Not for a trainer who
    # faces up (Red): his "behind" is the tile in front of him on screen.
    if facing(trainer) != "UP":
        order.insert(0, (-fdx, -fdy))
    why = []
    for dx, dy in order:
        xy = (tx + dx, ty + dy)
        c = cells.get(xy)
        reason = None
        if c is None:
            reason = "off map"
        elif c[0] or c[2] not in FLOOR:
            reason = "not floor"
        elif elev and c[1] not in (0, elev):  # elevation 0 tiles take any height
            reason = "elevation %d" % c[1]
        elif xy in taken or xy in fronts:
            reason = "taken"
        elif any(cells.get((xy[0] + a, xy[1] + b), (0, 0, 0))[2] in FORCED for a, b in DIRS.values()):
            reason = "next to a forced-move tile"
        elif xy in sight:
            reason = "in a trainer's sight"
        else:
            lost = (before - {xy}) - reachable(cells, m, objs, extra_block=xy)
            if lost & useful:
                reason = "cuts off %s" % sorted(lost & useful)
        if reason is None:
            return xy
        why.append("%s: %s" % (xy, reason))
    sys.exit("%s: no tile for a follower next to %s (%s)" % (name, trainer["graphics_id"], "; ".join(why)))


def main():
    cfg = json.load(open(P("data/hoenn/trainer_followers.json")))["followers"]
    by_map = {}
    for f in cfg:
        by_map.setdefault(f["map"], []).append(f)
    # Also clear followers from maps that are no longer listed.
    for name in sorted(os.listdir(P("data/maps"))):
        path = P("data/maps", name, "map.json")
        if not os.path.exists(path):
            continue
        text = open(path).read()
        if SCRIPT not in text and name not in by_map:
            continue
        m = json.loads(text)
        objs = [o for o in m.get("object_events", []) if o.get("script") != SCRIPT]
        added = []
        for f in by_map.get(name, []):
            trainers = [o for o in objs if o["graphics_id"] == f["trainer"]]
            if len(trainers) != 1:
                sys.exit("%s: expected one %s, found %d" % (name, f["trainer"], len(trainers)))
            t = trainers[0]
            if "at" in f:
                x, y = f["at"]
            else:
                x, y = choose_tile(name, m, grid(m["layout"]), objs + added, t)
            o = {}
            if "local_id" in f:
                o["local_id"] = f["local_id"]
            o.update({
                "graphics_id": "OBJ_EVENT_GFX_MON_BASE+SPECIES_" + f["species"],
                "x": x,
                "y": y,
                "elevation": t.get("elevation", 0),
                "movement_type": "MOVEMENT_TYPE_WALK_IN_PLACE_" + facing(t),
                "movement_range_x": 0,
                "movement_range_y": 0,
                "trainer_type": "TRAINER_TYPE_NONE",
                "trainer_sight_or_berry_tree_id": "0",
                "script": SCRIPT,
                "flag": t.get("flag", "0"),
            })
            added.append(o)
            print("%-30s %-10s at %2d,%2d (trainer %d,%d)" % (name, f["species"], x, y, int(t["x"]), int(t["y"])))
        m["object_events"] = objs + added
        with open(path, "w") as fh:
            json.dump(m, fh, indent=2, ensure_ascii=False)
            fh.write("\n")


if __name__ == "__main__":
    main()
