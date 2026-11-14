#!/usr/bin/env python3
"""hns.py plus the r6 story ops (scripts/r6_story_johto/r6story.py: walkto, objs, scene, bwin ...)
plus the ops the r10 travel tours use (tours/r10_bridges/*.txt): walk a map as a player would,
read every sign, talk to every NPC, use the PC and the furniture, enter every building.

    visit MAP [X Y]        warp to MAP (at X,Y, else at a tile picked from the map's warps,
                           signs and objects so that most of them can be reached on foot), shot
                           the map-name pop-up (PREFIX_popup) once it is fully on screen, run
                           whatever the map starts (drive). PREFIX is the map name in lower case
                           without MAP_ and _HNS, or the one `prefix` set.
    prefix NAME            shot prefix for the next ops
    signs                  read every sign bg_event of the current map (stand where its
                           player_facing_dir allows, face it, A, drive): PREFIX_sNN_MM
    npcs [SKIP ...]        talk to every live object event with a script (counters handled):
                           PREFIX_nLL_MM (LL = local id). SKIP: local ids to leave alone
    furniture              interact once with the first tile of each furniture behavior (PC,
                           TV, bookshelves, shelves, trash can, region map ...): PREFIX_fKIND_MM
    buildings [SKIP ...]   for each warp of the map to another map (once per destination):
                           walk onto it, then in there `visit`-like pop-up, signs, npcs,
                           furniture, and warp back next to the door. A failure inside one
                           building reloads a save state and goes on with the next.
                           SKIP: MAP_* names not to enter
    town [SKIP ...]        visit-free shorthand: signs, npcs, furniture, buildings
    drive PREFIX           run text / menus / battles / other screens until the player is free

Every screenshot also logs the decoded message buffer (gStringVar4, or gDisplayedStringBattle in
a battle), the map and position and what was being done to OUTDIR/TOUR/texts.jsonl.

Run:  r10travel.py tour ROM OUT --tours <emu>/tours/r10_bridges [--clip] [--only RE]
"""
import json
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(HERE, "..", "r6_story_johto"))
sys.path.insert(0, os.path.join(HERE, "..", "r2_hill_tents"))
import r6story  # noqa: E402,F401  (registers the r2-r6 ops on top of hns.py)
import hns  # noqa: E402
import hilltent_ops as ht  # noqa: E402
from hns import script_op, HnsError, TourTimeout, _arg  # noqa: E402

TOOLS = os.path.normpath(os.path.join(HERE, "..", "..", ".."))
sys.path.insert(0, TOOLS)
import textwidth as tw  # noqa: E402

FURNITURE = ("MB_PC", "MB_TELEVISION", "MB_REGION_MAP", "MB_BOOKSHELF", "MB_POKEMON_CENTER_BOOKSHELF",
             "MB_POKEMART_SHELF", "MB_PICTURE_BOOK_SHELF", "MB_TRASH_CAN", "MB_CABINET", "MB_KITCHEN",
             "MB_DRESSER", "MB_SNACKS", "MB_PAINTING", "MB_BLUEPRINT", "MB_BLUEPRINTS",
             "MB_RUNNING_SHOES_INSTRUCTION", "MB_BOOKSHELF_GREEN", "MB_TRAINER_HILL_TIMER")
EXTRA_MENU_TASKS = ["Task_ShopMenu"]
# gates toured on their own (tours/r10_bridges/g_*.txt), not again as a town's building
GATE_TOURS = {"MAP_FUCHSIA_CITY_ROUTE15_GATE_HNS", "MAP_FUCHSIA_ROUTE19GATE_HNS", "MAP_RECEPTION_GATE_HNS",
              "MAP_CLIFF_EDGE_GATE_HNS", "MAP_ROUTE5_TUNNEL_ENTRANCE_HNS", "MAP_ROUTE6_TUNNEL_ENTRANCE_HNS",
              "MAP_ROUTE7_TUNNEL_ENTRANCE_HNS", "MAP_ROUTE8_TUNNEL_ENTRANCE_HNS", "MAP_SAFARI_ZONE_GATE_HNS",
              "MAP_OLIVINE_CITY_PORT_INSIDE_HNS", "MAP_VERMILION_CITY_PORT_INSIDE_HNS",
              "MAP_GOLDENROD_CITY_TRAIN_STATION_HNS", "MAP_SAFFRON_CITY_TRAIN_STATION_HNS"}
FACE = {"UP": (0, -1), "DOWN": (0, 1), "LEFT": (-1, 0), "RIGHT": (1, 0)}


# ---------------------------------------------------------------------------- map data

_MAPS = {}


def maps(emu):
    src = hns.src_dir(emu.elf)
    if src not in _MAPS:
        out = {}
        root = os.path.join(src, "data", "maps")
        for d in os.listdir(root):
            p = os.path.join(root, d, "map.json")
            if os.path.exists(p):
                m = json.load(open(p))
                if "id" in m:
                    m["_dir"] = d
                    out[m["id"]] = m
        _MAPS[src] = out
    return _MAPS[src]


def current_map(emu):
    (g, n, _, _, _), _ = emu.location()
    for name, m in maps(emu).items():
        try:
            if hns.map_lookup(emu.elf, name) == (g, n):
                return m
        except HnsError:
            continue
    raise HnsError("no map.json for %d.%d" % (g, n))


def short(mapid):
    s = mapid
    for a in ("MAP_",):
        if s.startswith(a):
            s = s[len(a):]
    if s.endswith("_HNS"):
        s = s[:-4]
    return s.lower()


# ---------------------------------------------------------------------------- text log

def install_textlog(emu):
    if getattr(emu, "_tl_installed", False):
        return
    emu._tl_installed = True
    cm = tw.Charmap(os.path.join(hns.src_dir(emu.elf), "charmap.txt"))
    sv4 = emu.sym("gStringVar4")
    bstr = emu.sym("gDisplayedStringBattle")
    bcb2 = emu.sym("BattleMainCB2")
    path = os.path.join(emu.outdir, "texts.jsonl")
    emu._ctx = ""
    shot = emu.shot

    def shot_and_log(name):
        p = shot(name)
        try:
            inb = emu.cb2() == bcb2
            raw = emu.read(bstr if inb else sv4, 600)
            txt = cm.decode(raw)
            (g, n, _, _, _), pos = emu.location()
            rec = dict(shot=name, map="%d.%d" % (g, n), pos=list(pos), battle=inb, ctx=emu._ctx, text=txt)
        except HnsError as e:
            rec = dict(shot=name, error=str(e))
        with open(path, "a", encoding="utf-8") as fh:
            fh.write(json.dumps(rec, ensure_ascii=False) + "\n")
        return p

    emu.shot = shot_and_log


def note(emu, what, **kw):
    """Append a line to OUTDIR/TOUR/notes.jsonl (unreachable signs, skipped NPCs, failures)."""
    rec = dict(note=what, ctx=getattr(emu, "_ctx", ""), **kw)
    with open(os.path.join(emu.outdir, "notes.jsonl"), "a", encoding="utf-8") as fh:
        fh.write(json.dumps(rec, ensure_ascii=False) + "\n")
    print("note %s %s" % (what, kw))


def state_path(emu, name):
    """A save-state path hnsrun can take (its command parser keeps 127 characters): relative to
    the working directory when the absolute path is too long."""
    p = os.path.join(emu.outdir, name)
    return p if len(p) < 120 else os.path.relpath(p)


def _shot(emu, name):
    emu.frames(2)
    emu.shot(name)
    emu.shots = getattr(emu, "shots", []) + [name]


# ---------------------------------------------------------------------------- drive

def _loads(emu):
    out = set()
    for n in ("CB2_DoChangeMap", "CB2_LoadMap", "CB2_LoadMap2", "CB2_ReturnToField", "CB2_ReturnToFieldLocal",
              "CB2_ReturnToFieldContinueScript", "CB2_ReturnToFieldContinueScriptPlayMapMusic",
              "CB2_ReturnToFieldFadeFromBlack", "CB2_ReturnToFieldWithOpenMenu", "CB2_OverworldBasic",
              "CB2_InitBattle", "CB2_HandleStartBattle", "CB2_PreInitMultiBattle",
              "CB2_PreInitIngamePlayerPartnerBattle", "CB2_WhiteOut"):
        try:
            out.add(emu.sym(n))
        except HnsError:
            pass
    return out


def shop_tour(emu, prefix):
    """At the mart's BUY / SELL / QUIT menu: shot it, open BUY (shot the list, scroll, shot),
    back, open SELL (the bag: shot each pocket), back, QUIT. Once per tour."""
    _shot(emu, prefix + "_shop")
    emu.tap("A", 4)                                  # BUY
    emu.wait_until(lambda: emu.cb2_name().endswith("CB2_BuyMenu"), 600, "the buy menu", step=4)
    emu.wait_quiet(600)
    emu.frames(20)
    _shot(emu, prefix + "_buy_01")
    for i in range(2, 5):
        for _ in range(4):
            emu.tap("DOWN", 4)
        emu.wait_quiet(300)
        emu.frames(6)
        _shot(emu, prefix + "_buy_%02d" % i)
    emu.tap("A", 6)                                  # how many? (quantity window)
    emu.wait_quiet(300)
    emu.frames(20)
    _shot(emu, prefix + "_buy_qty")
    for _ in range(6):                               # back out to the shop menu
        if emu.in_overworld() and emu.tasks_named(["Task_ShopMenu"]):
            break
        emu.tap("B", 6)
        emu.frames(40)
    emu.wait_until(lambda: emu.in_overworld() and bool(emu.tasks_named(["Task_ShopMenu"])), 900,
                   "the shop menu again", step=4)
    emu.wait_quiet(600)
    emu.frames(10)
    emu.tap("DOWN", 6)
    emu.wait_quiet(300)
    _shot(emu, prefix + "_shop_sell")
    emu.tap("A", 4)                                  # SELL: the bag
    emu.wait_until(lambda: not emu.in_overworld(), 600, "the sell bag", step=4)
    emu.wait_until(lambda: emu.task_active("Task_BagMenu_HandleInput"), 900, "the bag input", step=4)
    emu.wait_quiet(600)
    emu.frames(10)
    for i in range(1, 8):
        _shot(emu, prefix + "_sell_p%d" % i)
        emu.tap("RIGHT", 6)
        emu.wait_quiet(300)
        emu.frames(20)
    emu.tap("A", 6)                                  # pick the first item: how many to sell
    emu.wait_quiet(300)
    emu.frames(20)
    _shot(emu, prefix + "_sell_item")
    for _ in range(8):
        if emu.in_overworld() and emu.tasks_named(["Task_ShopMenu"]):
            break
        emu.tap("B", 6)
        emu.frames(40)
    emu.wait_until(lambda: emu.in_overworld() and bool(emu.tasks_named(["Task_ShopMenu"])), 900,
                   "the shop menu after selling", step=4)
    emu.wait_quiet(600)
    emu.frames(10)
    emu.tap("B", 6)                                  # QUIT
    emu._shop_done = True


def drive(emu, prefix, maxpages=40, maxframes=6000, path=""):
    """Run whatever is on screen until the player can walk. Text: one shot per page, A.
    Choice menus: shot, B (the NO / cancel branch). Battles: bwin. The mart menu: shop_tour
    once, else QUIT. Anything else that sits still: shot, then B (a menu, a PC screen ...).
    Returns (shots, how)."""
    ow, bcb2 = emu.sym("CB2_Overworld"), emu.sym("BattleMainCB2")
    loads = _loads(emu)
    n, idle, last_box, stuck, menus, battles, offscreen, screens = 0, 0, None, 0, 0, 0, 0, 0
    was_busy = False
    total = 0
    while True:
        if total > maxframes * 4:
            raise TourTimeout("drive %s: still busy after %d frames" % (prefix, total))
        cb = emu.cb2()
        if cb == bcb2:
            battles += 1
            if battles > 4:
                raise HnsError("drive %s: a 5th battle" % prefix)
            hns.SCRIPT_OPS["bwin"](emu, ["bwin", "%s_b%d" % (prefix, battles)], path)
            last_box = None
            continue
        if cb == ow:
            offscreen = 0
            if emu.controllable():
                emu.frames(8)
                if emu.controllable():
                    return n, "free"
                continue
            if emu.tasks_named(["Task_ShopMenu"]):
                emu.wait_quiet(600)
                if not getattr(emu, "_shop_done", False):
                    shop_tour(emu, prefix)
                else:
                    n += 1
                    _shot(emu, "%s_%02d_shop" % (prefix, n))
                    emu.tap("B", 6)
                emu.frames(20)
                continue
            if emu.tasks_named(emu.MENU_TASKS):
                emu.wait_menu_ready()
                emu.wait_quiet(600)
                n += 1
                _shot(emu, "%s_%02d_menu" % (prefix, n))
                menus += 1
                if menus > 8:
                    raise HnsError("drive %s: 9 menus" % prefix)
                emu.tap("B", 6)
                emu.frames(10)
                last_box = None
                continue
        elif cb not in loads and not emu.fading():
            offscreen += 2
            if offscreen > 90:
                screens += 1
                if screens > 12:
                    raise TourTimeout("drive %s: stuck on screen %s" % (prefix, emu.cb2_name()))
                n += 1
                _shot(emu, "%s_%02d_screen" % (prefix, n))
                emu.tap("B" if screens % 2 else "A", 6)
                offscreen = 0
            emu.frames(2)
            total += 2
            continue
        st = emu.text_state()
        if st == "busy" or emu.fading():
            was_busy = True
            emu.frames(2)
            idle += 2
            total += 2
            continue
        if was_busy and not emu.wants_key() and cb == ow:
            was_busy = False
            emu.frames(2)
            box = hns.message_box(emu)
            if box is not None and box != last_box:
                n += 1
                _shot(emu, "%s_%02d" % (prefix, n))
                last_box = box
            continue
        was_busy = False
        if emu.wants_key():
            emu.wait_quiet(600)
            box = hns.message_box(emu) if cb == ow else None
            if box is None or box != last_box:
                n += 1
                if n > maxpages:
                    raise HnsError("drive %s: more than %d pages" % (prefix, maxpages))
                _shot(emu, "%s_%02d" % (prefix, n))
            last_box = box
            emu.tap("A", 0)
            try:
                emu.wait_until(lambda: not emu.wants_key(), 90, "the text to take the key", step=1)
            except TourTimeout:
                emu.tap("B", 4)
            idle = 0
            continue
        emu.frames(2)
        idle += 2
        total += 2
        if idle > 360:
            stuck += 1
            if stuck > 10:
                raise TourTimeout("drive %s: nothing moves (callback2 %s, tasks %s)"
                                  % (prefix, emu.cb2_name(), [t[2] for t in emu.tasks()]))
            n += 1
            _shot(emu, "%s_%02d_wait" % (prefix, n))
            emu.tap("B" if stuck % 3 else "A", 6)
            idle = 0


@script_op("drive")
def _op_drive(emu, f, path):
    install_textlog(emu)
    n, how = drive(emu, f[1], _arg(f, 2, 40), path=path)
    print("drive %s: %d shot(s), %s @%d" % (f[1], n, how, emu.sync()))


# ---------------------------------------------------------------------------- walking

def objects(emu):
    """hilltent objects() without the follower Pokemon (OBJ_EVENT_ID_FOLLOWER 0xFE,
    include/constants/event_objects.h:673): the player walks through it (they swap places)."""
    return [o for o in ht.objects(emu) if o[0] < 0xF0]


class Grid:
    """The loaded map as the player walks it: collision, water (needs Surf), elevation
    (src/event_object_movement.c IsElevationMismatchAt / ObjectEventUpdateElevation: 0 is a
    transition tile, 15 a bridge tile that keeps the walker's elevation) and ledges."""

    WATER_WORDS = ("DEEP_WATER", "OCEAN_WATER", "POND_WATER", "WATERFALL", "SEAWEED", "CURRENT",
                   "NO_SURFACING", "SOOTOPOLIS_DEEP_WATER")

    def __init__(self, emu):
        base = emu.sym("gBackupMapLayout")
        W, H, ptr = emu.r32(base), emu.r32(base + 4), emu.r32(base + 8)
        raw = emu.read(ptr, W * H * 2)
        self.W, self.H = W, H
        self.cells = [int.from_bytes(raw[i:i + 2], "little") for i in range(0, len(raw), 2)]
        self.w, self.h = W - 15, H - 14
        beh = ht._behavior_reader(emu)
        ht._mb(emu, "MB_NORMAL")
        water = {v for k, v in emu._mbs.items() if any(x in k for x in self.WATER_WORDS)}
        jd = {ht._mb(emu, "MB_JUMP_EAST"): "RIGHT", ht._mb(emu, "MB_JUMP_WEST"): "LEFT",
              ht._mb(emu, "MB_JUMP_NORTH"): "UP", ht._mb(emu, "MB_JUMP_SOUTH"): "DOWN"}
        ice = {ht._mb(emu, "MB_ICE"), ht._mb(emu, "MB_TRICK_HOUSE_PUZZLE_8_FLOOR")}
        sd = {}
        for kind in ("SLIDE", "WALK"):
            sd.update({ht._mb(emu, "MB_%s_EAST" % kind): "RIGHT", ht._mb(emu, "MB_%s_WEST" % kind): "LEFT",
                       ht._mb(emu, "MB_%s_NORTH" % kind): "UP", ht._mb(emu, "MB_%s_SOUTH" % kind): "DOWN"})
        self.beh = {}
        self.water = set()
        self.ledge = {}
        self.ice = set()
        self.slide = {}
        for y in range(self.h):
            for x in range(self.w):
                c = self.cell(x, y)
                b = beh(c & 0x3FF)
                self.beh[(x, y)] = b
                if b in water:
                    self.water.add((x, y))
                if b in jd:
                    self.ledge[(x, y)] = jd[b]
                if b in ice:
                    self.ice.add((x, y))
                if b in sd:
                    self.slide[(x, y)] = sd[b]
        self.refresh(emu)

    def refresh(self, emu):
        self.player_elev = 0
        raw = emu.read(emu.sym("gObjectEvents"), 16 * 0x24)
        for i in range(16):
            o = raw[i * 0x24:(i + 1) * 0x24]
            if o[0] & 1 and o[2] & 1:
                self.player_elev = o[0x0B] & 0xF
        return self

    def cell(self, x, y):
        X, Y = x + 7, y + 7
        if not (0 <= X < self.W and 0 <= Y < self.H):
            return 0x0C00
        return self.cells[X + self.W * Y]

    def inside(self, t):
        return 0 <= t[0] < self.w and 0 <= t[1] < self.h

    def blocked(self, t):
        return (not self.inside(t)) or bool(self.cell(*t) & 0x0C00) or t in self.water

    def elev(self, t):
        return self.cell(*t) >> 12

    def step(self, state, d, avoid):
        """The state after one press of D from STATE=(x, y, e), or None."""
        x, y, e = state
        dx, dy = FACE[d]
        n = (x + dx, y + dy)
        if self.ledge.get(n) == d:
            n2 = (n[0] + dx, n[1] + dy)
            if self.blocked(n2) or n2 in avoid:
                return None
            ne = self.elev(n2)
            return (n2[0], n2[1], e if ne in (0, 15) else ne)
        if self.blocked(n) or n in avoid or n in self.ledge:
            return None
        me = self.elev(n)
        if e != 0 and me not in (0, 15) and me != e:
            return None
        ne = e if (me == 15 or self.elev((x, y)) == 15) else me
        # ice keeps the walker going the same way, slide/walk tiles push it their way
        for _ in range(64):
            if n in self.ice:
                dd = d
            elif n in self.slide:
                dd = self.slide[n]
            else:
                break
            ddx, ddy = FACE[dd]
            nxt = (n[0] + ddx, n[1] + ddy)
            if self.blocked(nxt) or nxt in self.ledge:
                break
            n = nxt
        return (n[0], n[1], ne)

    def search(self, start, avoid, goal=None, elev=None):
        """BFS from START (x, y); returns {tile: path} for every reachable tile (paths are
        lists of directions), or only up to GOAL."""
        from collections import deque
        s0 = (start[0], start[1], self.player_elev if elev is None else elev)
        prev = {s0: None}
        best = {start: []}
        q = deque([s0])
        while q:
            c = q.popleft()
            if goal is not None and (c[0], c[1]) == goal:
                break
            for d in ("UP", "DOWN", "LEFT", "RIGHT"):
                n = self.step(c, d, avoid - ({goal} if goal else set()))
                if n is None or n in prev:
                    continue
                prev[n] = (c, d)
                q.append(n)
                t = (n[0], n[1])
                if t not in best:
                    path, k = [], n
                    while prev[k]:
                        k0, dd = prev[k]
                        path.append(dd)
                        k = k0
                    best[t] = path[::-1]
        return best


def grid(emu):
    """Grid of the loaded map, cached per map (the player's elevation is re-read)."""
    (gr, n, _, _, _), _ = emu.location()
    key = (gr, n, emu.r32(emu.sym("gBackupMapLayout") + 8))
    c = getattr(emu, "_grid_cache", {})
    if key not in c:
        c = {key: Grid(emu)}
        emu._grid_cache = c
        return c[key]
    return c[key].refresh(emu)


def plan(emu, start, goal, avoid):
    g = grid(emu)
    objs = {(o[1], o[2]) for o in objects(emu)} - {goal}
    return g.search(start, set(avoid) | objs, goal).get(goal)


def warp_tiles(m):
    return {(w["x"], w["y"]) for w in m.get("warp_events", [])}


def trigger_tiles(m):
    return {(c["x"], c["y"]) for c in m.get("coord_events", [])}


def walk_to(emu, goal, avoid=(), face=None, maxit=300):
    """hilltent walkto over the live grid with AVOID tiles (warps, triggers) never stepped on
    (unless one is the goal). Returns 'reached', 'taken', 'warp' or None (no path)."""
    goal = tuple(goal)
    avoid = set(avoid) - {goal}
    blocked = set()
    (g0, n0, _, _, _), _ = emu.location()
    for it in range(maxit):
        (g, n, _, _, _), pos = emu.location()
        if (g, n) != (g0, n0):
            return "warp"
        if pos == goal:
            break
        route = plan(emu, pos, goal, blocked | avoid)
        if not route:
            return None
        d = route[0]
        r = hns.go_step(emu, d)
        if r is None:
            if not emu.controllable():
                return "taken"
            dx, dy = FACE[d]
            nxt = (pos[0] + dx, pos[1] + dy)
            if nxt == goal:
                return None
            blocked.add(nxt)
            continue
        if r == "warp":
            return "warp"
        if not emu.controllable():
            emu.frames(4)
            if not emu.controllable():
                return "taken"
    else:
        return None
    if face:
        emu.frames(2, face)
        emu.frames(14)
    return "reached"


def reachable(emu, start, avoid):
    """Tiles reachable on foot from START (elevation, water and ledges as the game has them)."""
    g = grid(emu)
    objs = {(o[1], o[2]) for o in objects(emu)}
    return set(g.search(start, set(avoid) | objs).keys())


def sign_stands(b):
    x, y = b["x"], b["y"]
    fd = b.get("player_facing_dir", "BG_EVENT_PLAYER_FACING_ANY")
    allc = {"BG_EVENT_PLAYER_FACING_NORTH": [((x, y + 1), "UP")],
            "BG_EVENT_PLAYER_FACING_SOUTH": [((x, y - 1), "DOWN")],
            "BG_EVENT_PLAYER_FACING_EAST": [((x - 1, y), "RIGHT")],
            "BG_EVENT_PLAYER_FACING_WEST": [((x + 1, y), "LEFT")]}
    return allc.get(fd, [((x, y + 1), "UP"), ((x - 1, y), "RIGHT"), ((x + 1, y), "LEFT"), ((x, y - 1), "DOWN")])


def object_stands(emu, ox, oy):
    """(tile, facing) pairs from which A reaches the object, across a counter too."""
    g = grid(emu)
    counter = ht._mb(emu, "MB_COUNTER")
    out = []
    for d, (dx, dy) in (("UP", (0, 1)), ("DOWN", (0, -1)), ("LEFT", (1, 0)), ("RIGHT", (-1, 0))):
        t = (ox + dx, oy + dy)
        out.append((t, d))
        if g.beh.get(t) == counter:
            out.append(((ox + 2 * dx, oy + 2 * dy), d))
    return out


def go_and_face(emu, stands, avoid):
    """Walk to the nearest reachable stand tile and face; returns the tile, 'taken', 'warp' or None."""
    _, pos = emu.location()
    g = grid(emu)
    objs = {(o[1], o[2]) for o in objects(emu)}
    paths = g.search(pos, set(avoid) | objs)
    cands = []
    for t, d in stands:
        if t == pos:
            cands.append((0, t, d))
        elif t in paths:
            cands.append((len(paths[t]), t, d))
    for _, t, d in sorted(cands):
        r = walk_to(emu, t, avoid)
        if r in ("taken", "warp"):
            return r
        if r == "reached":
            emu.frames(2, d)
            emu.frames(14)
            return t
    return None


# ---------------------------------------------------------------------------- ops

def prefix_of(emu):
    return getattr(emu, "_prefix", "x")


@script_op("prefix")
def _op_prefix(emu, f, path):
    emu._prefix = f[1]


def popup_shot(emu, name, maxframes=240):
    """Wait until the map-name pop-up has slid in (Task_MapNamePopUpWindow tState == STATE_WAIT,
    src/map_name_popup.c:548-556), then shot NAME. Returns False when no pop-up came."""
    waited = 0
    while waited < maxframes:
        d = emu.task_data("Task_MapNamePopUpWindow") if emu.task_active("Task_MapNamePopUpWindow") else []
        if d and d[0][0] == 1:
            emu.frames(4)
            _shot(emu, name)
            return True
        emu.frames(2)
        waited += 2
    return False


def avoid_tiles(m):
    return warp_tiles(m) | trigger_tiles(m)


def targets_of(emu, m):
    tiles = []
    for b in m.get("bg_events", []):
        if b["type"] == "sign":
            tiles += [t for t, _ in sign_stands(b)]
    for o in m.get("object_events", []):
        if o.get("script", "NULL") != "NULL" and "x" in o:
            x, y = o["x"], o["y"]
            tiles += [(x, y + 1), (x - 1, y), (x + 1, y), (x, y - 1)]
    for wv in m.get("warp_events", []):
        tiles += [(wv["x"], wv["y"] + 1), (wv["x"], wv["y"] - 1)]
    return tiles


def do_warp(emu, mapid, x, y):
    g, n = hns.map_lookup(emu.elf, mapid)
    try:
        emu.warp(g, n, x, y)
    except HnsError as e:
        if "landed at" not in str(e):
            raise
    if not emu.controllable():
        drive(emu, prefix_of(emu) + "_arrive")


def spawn_choice(emu, m, start):
    """A tile from which most targets are reachable, as close to START as possible."""
    g = grid(emu)
    objs = {(o[1], o[2]) for o in objects(emu)}
    av = avoid_tiles(m) | objs
    tgt = [t for t in targets_of(emu, m) if not g.blocked(t)]
    comps, done = [], set()
    for t in [start] + tgt:
        if t in done or t in av or g.blocked(t):
            continue
        e = g.elev(t)
        comp = set(g.search(t, av, elev=0 if e == 15 else e).keys())
        done |= comp
        comps.append((sum(1 for x in tgt if x in comp), comp))
    if not comps:
        return start
    comps.sort(key=lambda c: -c[0])
    score, comp = comps[0]
    if start in comp:
        return start
    return min(comp, key=lambda t: abs(t[0] - start[0]) + abs(t[1] - start[1]))


@script_op("visit")
def _op_visit(emu, f, path):
    """visit MAP [X Y]: see the module doc."""
    install_textlog(emu)
    mapid = f[1]
    m = maps(emu)[mapid]
    emu._prefix = short(mapid)
    emu._ctx = "visit %s" % mapid
    if len(f) > 3:
        x, y = int(f[2]), int(f[3])
        do_warp(emu, mapid, x, y)
    else:
        ws = m.get("warp_events", [])
        objs = [o for o in m.get("object_events", []) if "x" in o]
        signs = [b for b in m.get("bg_events", [])]
        if ws:
            x, y = ws[0]["x"], ws[0]["y"] + 1
        elif objs:
            x, y = objs[0]["x"], objs[0]["y"] + 1
        elif signs:
            x, y = signs[0]["x"], signs[0]["y"] + 1
        else:
            x, y = 5, 5
        do_warp(emu, mapid, x, y)
        _, pos = emu.location()
        best = spawn_choice(emu, m, pos)
        if best != pos:
            print("visit %s: re-warp from %s to %s" % (mapid, pos, best))
            do_warp(emu, mapid, best[0], best[1])
    if m.get("show_map_name"):
        if not popup_shot(emu, emu._prefix + "_popup"):
            note(emu, "nopopup", map=mapid)
            _shot(emu, emu._prefix + "_here")
    else:
        emu.wait_quiet(300)
        _shot(emu, emu._prefix + "_here")
    print("visit %s at %s @%d" % (mapid, emu.location()[1], emu.sync()))


def done_set(emu, m, kind):
    d = getattr(emu, "_done", None)
    if d is None:
        d = emu._done = {}
    return d.setdefault(m["id"], {"s": set(), "n": set(), "f": set()})[kind]


def _signs(emu, m, prefix, path):
    av = avoid_tiles(m)
    for i, b in enumerate(m.get("bg_events", [])):
        if b["type"] != "sign" or b.get("script", "NULL") in ("NULL", "0"):
            continue
        if "WallClock" in b.get("script", ""):        # its own screen; toured in r1 (ofui_wallclock)
            continue
        if i in done_set(emu, m, "s"):
            continue
        emu._ctx = "sign %d (%d,%d) %s %s" % (i, b["x"], b["y"], b.get("player_facing_dir", ""), b.get("script"))
        r = go_and_face(emu, sign_stands(b), av)
        if r is None:
            note(emu, "unreachable_sign", map=m["id"], idx=i, x=b["x"], y=b["y"], script=b.get("script"))
            continue
        done_set(emu, m, "s").add(i)
        name = "%s_s%02d" % (prefix, i)
        if r in ("taken", "warp"):
            note(emu, "sign_walk_" + r, map=m["id"], idx=i)
            if r == "taken":
                drive(emu, name + "_x", path=path)
            if r == "warp":
                return False
            continue
        emu.tap("A", 4)
        n, how = drive(emu, name, path=path)
        if n == 0:
            note(emu, "sign_no_text", map=m["id"], idx=i, x=b["x"], y=b["y"], script=b.get("script"))
        if current_map(emu)["id"] != m["id"]:
            note(emu, "sign_left_map", map=m["id"], idx=i)
            return False
    return True


@script_op("signs")
def _op_signs(emu, f, path):
    install_textlog(emu)
    m = current_map(emu)
    _signs(emu, m, prefix_of(emu), path)


def approach_spot(emu, x, y, avoid):
    """Walk to the reachable tile nearest to (X, Y) (so that the objects there spawn: object
    events exist only near the camera). Returns walk_to's result or None."""
    _, pos = emu.location()
    comp = reachable(emu, pos, avoid)
    if not comp:
        return None
    best = min(comp, key=lambda t: abs(t[0] - x) + abs(t[1] - y))
    if best == pos:
        return "reached"
    r = walk_to(emu, best, avoid)
    print("approach (%d,%d): from %s to %s: %s, now %s" % (x, y, pos, best, r, emu.location()[1]))
    return r


def _npcs(emu, m, prefix, path, skip=()):
    av = avoid_tiles(m)
    tmpl = m.get("object_events", [])
    for idx, t in enumerate(tmpl):
        lid = idx + 1
        if lid in skip or "x" not in t:
            continue
        if t.get("script", "NULL") in ("NULL", "0") or t.get("type", "object") != "object":
            continue
        if lid in done_set(emu, m, "n"):
            continue
        emu._ctx = "npc %d %s %s %s" % (lid, t.get("graphics_id", ""), t["script"], t.get("trainer_type", ""))
        name = "%s_n%02d" % (prefix, lid)
        if not [o for o in objects(emu) if o[0] == lid]:
            r = approach_spot(emu, t["x"], t["y"], av)
            if r == "warp":
                note(emu, "npc_walk_warp", map=m["id"], lid=lid)
                return False
            if r == "taken":
                drive(emu, name + "_x", path=path)
            if not [o for o in objects(emu) if o[0] == lid]:
                note(emu, "npc_absent", map=m["id"], lid=lid, script=t["script"], flag=t.get("flag"))
                continue
        got = 0
        for attempt in range(3):
            live = [o for o in objects(emu) if o[0] == lid]
            if not live:
                break
            _, ox, oy = live[0]
            r = go_and_face(emu, object_stands(emu, ox, oy), av)
            if r is None:
                note(emu, "unreachable_npc", map=m["id"], lid=lid, script=t["script"], at=[ox, oy])
                break
            if r == "warp":
                note(emu, "npc_walk_warp", map=m["id"], lid=lid)
                return False
            if r == "taken":
                drive(emu, name + "_x", path=path)
                continue
            done_set(emu, m, "n").add(lid)
            emu.tap("A", 4)
            n, how = drive(emu, name if attempt == 0 else "%s_r%d" % (name, attempt), path=path)
            got += n
            if n:
                break
        if not got:
            note(emu, "npc_no_text", map=m["id"], lid=lid, script=t["script"])
        if current_map(emu)["id"] != m["id"]:
            note(emu, "npc_left_map", map=m["id"], lid=lid)
            return False
    return True


@script_op("npcs")
def _op_npcs(emu, f, path):
    install_textlog(emu)
    m = current_map(emu)
    _npcs(emu, m, prefix_of(emu), path, {int(x) for x in f[1:]})


def _furniture(emu, m, prefix, path):
    g = grid(emu)
    kinds = {}
    for k in FURNITURE:
        try:
            kinds[ht._mb(emu, k)] = k
        except KeyError:
            pass
    seen = {}
    for y in range(g.h):
        for x in range(g.w):
            b = g.beh[(x, y)]
            if b in kinds and kinds[b] not in seen:
                seen[kinds[b]] = (x, y)
    av = avoid_tiles(m)
    for k, (x, y) in sorted(seen.items(), key=lambda kv: kv[1][1] * 1000 + kv[1][0]):
        if k in done_set(emu, m, "f"):
            continue
        emu._ctx = "furniture %s (%d,%d)" % (k, x, y)
        stands = [((x, y + 1), "UP"), ((x - 1, y), "RIGHT"), ((x + 1, y), "LEFT"), ((x, y - 1), "DOWN")]
        r = go_and_face(emu, stands, av)
        if r is None or r in ("warp",):
            note(emu, "unreachable_furniture", map=m["id"], kind=k, at=[x, y])
            if r == "warp":
                return False
            continue
        if r == "taken":
            drive(emu, "%s_f%s_x" % (prefix, k[3:].lower()), path=path)
            continue
        done_set(emu, m, "f").add(k)
        emu.tap("A", 4)
        n, how = drive(emu, "%s_f%s" % (prefix, k[3:].lower()), path=path)
        if n == 0:
            note(emu, "furniture_no_text", map=m["id"], kind=k, at=[x, y])
    return True


@script_op("furniture")
def _op_furniture(emu, f, path):
    install_textlog(emu)
    m = current_map(emu)
    _furniture(emu, m, prefix_of(emu), path)


def _interior(emu, m, prefix, path):
    if not (m.get("show_map_name") and popup_shot(emu, prefix + "_popup", 200)):
        emu.wait_quiet(300)
        _shot(emu, prefix + "_here")
    if not emu.controllable():
        drive(emu, prefix + "_arrive", path=path)
    ok = _signs(emu, m, prefix, path)
    ok = ok and _npcs(emu, m, prefix, path)
    ok = ok and _furniture(emu, m, prefix, path)
    return ok


@script_op("buildings")
def _op_buildings(emu, f, path):
    install_textlog(emu)
    town = current_map(emu)
    skip = set(f[1:])
    tp = prefix_of(emu)
    seen = set()
    state = state_path(emu, "_town.ss")
    allmaps = maps(emu)
    for i, wv in enumerate(town.get("warp_events", [])):
        dest = wv["dest_map"]
        if dest in seen or dest in skip or dest == town["id"] or dest not in allmaps:
            continue
        if dest.startswith("MAP_GATE_") or dest in GATE_TOURS:
            seen.add(dest)
            continue
        seen.add(dest)
        dm = allmaps[dest]
        if dm.get("map_type") not in ("MAP_TYPE_INDOOR", "MAP_TYPE_NONE", None):
            note(emu, "skip_outdoor_dest", map=town["id"], dest=dest, type=dm.get("map_type"))
            continue
        bprefix = "%s_%s" % (tp, short(dest).replace(short(town["id"]) + "_", ""))
        emu._ctx = "enter %s via warp %d (%d,%d)" % (dest, i, wv["x"], wv["y"])
        emu.send("ss %s" % state)
        emu.sync()
        (g0, n0, _, _, _), _ = emu.location()
        back = None
        try:
            # stand next to the door, then step on it
            door = (wv["x"], wv["y"])
            av = avoid_tiles(town) - {door}
            stands = [((door[0], door[1] + 1), "UP"), ((door[0] - 1, door[1]), "RIGHT"),
                      ((door[0] + 1, door[1]), "LEFT"), ((door[0], door[1] - 1), "DOWN")]
            r = go_and_face(emu, stands, avoid_tiles(town))
            entered = False
            if r not in (None, "taken", "warp"):
                back = r
                d = {(1, 0): "RIGHT", (-1, 0): "LEFT", (0, 1): "DOWN", (0, -1): "UP"}[(door[0] - r[0], door[1] - r[1])]
                res = hns.go_step(emu, d)
                if res != "warp":
                    res = hns.go_step(emu, d)
                if res == "warp" or current_map(emu)["id"] != town["id"]:
                    entered = True
            if not entered:
                print("buildings: walking into %s failed (%s), warping" % (dest, r))
                dws = dm.get("warp_events", [])
                k = int(str(wv.get("dest_warp_id", "0")), 0)
                dw = dws[k] if k < len(dws) else (dws[0] if dws else None)
                if back is None:
                    _, back = emu.location()
                do_warp(emu, dest, dw["x"], dw["y"] - 1 if dw else 5)
            if not emu.controllable():
                drive(emu, bprefix + "_arrive", path=path)
            here = current_map(emu)
            if here["id"] != dest:
                note(emu, "entered_other_map", town=town["id"], dest=dest, got=here["id"])
            _interior(emu, here, bprefix, path)
        except (HnsError, TourTimeout) as e:
            note(emu, "building_failed", town=town["id"], dest=dest, error=str(e)[:300])
            try:
                _shot(emu, bprefix + "_zz_failed")
            except HnsError:
                pass
            emu.send("sl %s" % state)
            emu.sync()
            emu.frames(10)
            continue
        # back to the town, next to the door
        try:
            if emu.in_overworld():
                g, n = hns.map_lookup(emu.elf, town["id"])
                bx, by = back if back else (wv["x"], wv["y"] + 1)
                try:
                    emu.warp(g, n, bx, by)
                except HnsError as e:
                    if "landed at" not in str(e):
                        raise
                if not emu.controllable():
                    drive(emu, bprefix + "_back", path=path)
            else:
                raise HnsError("not in the overworld after %s" % dest)
        except (HnsError, TourTimeout) as e:
            note(emu, "building_return_failed", town=town["id"], dest=dest, error=str(e)[:300])
            emu.send("sl %s" % state)
            emu.sync()
            emu.frames(10)
    print("buildings %s: %d destination(s) @%d" % (town["id"], len(seen), emu.sync()))


def _phases(emu, m, p, path):
    state = state_path(emu, "_street.ss")
    emu.send("ss %s" % state)
    emu.sync()
    for what, fn in (("signs", lambda: _signs(emu, m, p, path)), ("npcs", lambda: _npcs(emu, m, p, path)),
                     ("furniture", lambda: _furniture(emu, m, p, path))):
        try:
            ok = fn()
        except (HnsError, TourTimeout) as e:
            note(emu, "street_failed", map=m["id"], what=what, error=str(e)[:300])
            try:
                _shot(emu, "%s_zz_%s_failed" % (p, what))
            except HnsError:
                pass
            ok = False
        if not ok:
            emu.send("sl %s" % state)
            emu.sync()
            emu.frames(10)
        else:
            emu.send("ss %s" % state)
            emu.sync()


def pending_tiles(emu, m):
    """Stand tiles of the signs and NPC templates not done yet."""
    out = []
    ds, dn = done_set(emu, m, "s"), done_set(emu, m, "n")
    for i, b in enumerate(m.get("bg_events", [])):
        if b["type"] == "sign" and b.get("script", "NULL") not in ("NULL", "0") and i not in ds \
                and "WallClock" not in b.get("script", ""):
            out += [t for t, _ in sign_stands(b)]
    for idx, t in enumerate(m.get("object_events", [])):
        if "x" in t and t.get("script", "NULL") not in ("NULL", "0") and idx + 1 not in dn:
            x, y = t["x"], t["y"]
            out += [(x, y + 1), (x - 1, y), (x + 1, y), (x, y - 1)]
    return out


@script_op("town", "area")
def _op_town(emu, f, path):
    """town [SKIP ...]: signs, npcs, furniture (each from a save state, so a failure in one does
    not stop the others), then the same in every other part of the map that cannot be walked to
    (warping there), then buildings (back on the first part). area: the same without buildings."""
    install_textlog(emu)
    m = current_map(emu)
    p = prefix_of(emu)
    _, home = emu.location()
    _phases(emu, m, p, path)
    tried = set()
    for extra in range(4):
        if current_map(emu)["id"] != m["id"]:
            break
        g = grid(emu)
        av = avoid_tiles(m)
        _, pos = emu.location()
        here = reachable(emu, pos, av)
        tried |= here
        pend = [t for t in pending_tiles(emu, m) if g.inside(t) and not g.blocked(t) and t not in tried and t not in av]
        if not pend:
            break
        best = None
        for t in pend[:12]:
            e = g.elev(t)
            comp = set(g.search(t, av, elev=0 if e == 15 else e).keys())
            score = sum(1 for x in pend if x in comp)
            if best is None or score > best[0]:
                best = (score, t, comp)
        score, t, comp = best
        tried |= comp
        print("town %s: part %d at %s (%d pending tiles there)" % (m["id"], extra + 2, t, score))
        try:
            do_warp(emu, m["id"], t[0], t[1])
        except (HnsError, TourTimeout) as e:
            note(emu, "part_warp_failed", map=m["id"], at=list(t), error=str(e)[:200])
            continue
        _phases(emu, m, p, path)
    if f[0] == "town":
        if current_map(emu)["id"] == m["id"]:
            try:
                do_warp(emu, m["id"], home[0], home[1])
            except (HnsError, TourTimeout) as e:
                note(emu, "home_warp_failed", map=m["id"], error=str(e)[:200])
        _op_buildings(emu, ["buildings"] + f[1:], path)


@script_op("forget")
def _op_forget(emu, f, path):
    """forget: treat every sign, NPC and furniture of the current map as not visited yet (to talk
    to the same NPCs again after a story state changed)."""
    m = current_map(emu)
    getattr(emu, "_done", {}).pop(m["id"], None)


@script_op("gridat")
def _op_gridat(emu, f, path):
    """gridat X0 Y0 X1 Y1: print collision/elevation/behavior of the tiles in the box (debugging)."""
    g = grid(emu)
    x0, y0, x1, y1 = (int(v) for v in f[1:5])
    _, pos = emu.location()
    print("gridat: player %s elev %d" % (pos, g.player_elev))
    for y in range(y0, y1 + 1):
        print("   %3d " % y + " ".join("%s%X%02X" % ("#" if g.blocked((x, y)) else ".", g.elev((x, y)), g.beh.get((x, y), 0))
                                     for x in range(x0, x1 + 1)))


if __name__ == "__main__":
    sys.argv[0] = hns.__file__
    sys.exit(hns.main())
