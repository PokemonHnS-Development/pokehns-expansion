#!/usr/bin/env python3
"""r6trainers.py (the r5/r6 league, trainer and walk ops) and rc5.py (talknpc / readsign) plus the
travel ops of the r10 post-game league and islands tours (tours/r10_postgame/*.txt).

    arrive MAP X Y PREFIX   warp to MAP (X, Y) (a door, a boat or a fly landing loads the map the
                            same way), then one shot every 6 frames while the map-name pop-up
                            (Task_MapNamePopUpWindow) runs, repeats dropped (PREFIX_pNN), and the
                            field once the player is free (PREFIX_field)
    stepmap DIR PREFIX [N]  walk DIR (at most N tiles) until a warp or a connection loads another
                            map, then the pop-up shots as in arrive
    visit PREFIX [OPT...]   every live object with a script and every sign of the current map
                            (HNS_SRC data/maps/<map>/map.json), nearest first. An object: walk next
                            to it, face it, A, then `converse` (PREFIX_oLID_..). A sign: walk below
                            it (or beside it), face it, A, `converse` (PREFIX_sX_Y_..). An object
                            the walk cannot reach (water, ledges, Strength boulders) is warped next
                            to: the harness does not surf. Objects with the same script and
                            graphics as one already talked to (boulders, rocks, berry trees) are
                            skipped. OPT: skip=LID,LID  yes=LID,LID (menus answered with A)
                            only=LID,LID  nosigns  noobjs  signs=X:Y,X:Y (only these signs)
    converse PREFIX [yes]   the dialogue after A, to the free player: text pages (PREFIX_NN),
                            choice menus (shot, then B, or A with yes; a menu that B cannot close
                            gets A), a shop (shop menu, BUY list one shot per row to the end, back
                            out), battles (tbwin: PREFIX_bK_..), other screens (shots, B until the
                            field is back)
    talkobj LID PREFIX [yes]   one object (as visit)
    sign X Y PREFIX            one sign (as visit)
    wild PREFIX [MAXSTEPS]  walk to the nearest wild-encounter tile and pace on it until a wild
                            battle starts; the intro pages up to the action menu, RUN, the escape
                            pages, back to the field
    hofwatch PREFIX [MAXF]  from the Hall of Fame map's cutscene: Lance's pages, the record, every
                            Hall of Fame panel (shot when each one is complete), the welcome and the
                            player panel; returns at the credits (CB2 of the credits) or the field
Writes OUTDIR/visit.jsonl: one JSON line per object or sign (map, id, script, how it ended, shots).
Run:  r10pg.py tour ROM OUT --tours <emu>/tours/r10_postgame [--clip] [--only RE]
"""
import glob
import json
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(HERE, "..", "r6_trainers"))
sys.path.insert(0, os.path.join(HERE, "..", "r5_contests"))
import r6trainers  # noqa: E402  (hns + r5leg / r6league / hilltent ops)
import rc5  # noqa: E402,F401  (talknpc / readsign)
import hns  # noqa: E402
import rc  # noqa: E402
import hilltent_ops as ho  # noqa: E402
from hns import script_op, HnsError, TourTimeout, _arg  # noqa: E402

ENCOUNTER_MB = {2, 3, 5, 6, 8, 11, 12}
_MAPS = {}
LIST_TASK = "ListMenuDummyTask"


def _maps(emu):
    """(group, num) -> (folder, map.json dict) for every map of HNS_SRC."""
    src = hns.src_dir(emu.elf)
    if src not in _MAPS:
        out = {}
        for mj in glob.glob(os.path.join(src, "data", "maps", "*", "map.json")):
            d = json.load(open(mj, encoding="utf-8"))
            try:
                gn = hns.map_lookup(emu.elf, d["id"])
            except HnsError:
                continue
            out[gn] = (os.path.basename(os.path.dirname(mj)), d)
        _MAPS[src] = out
    return _MAPS[src]


def here(emu):
    (g, n, _, _, _), pos = emu.location()
    folder, d = _maps(emu).get((g, n), (None, {}))
    return g, n, folder, d, pos


def _log(emu, rec):
    mode = "a" if getattr(emu, "_vlog", False) else "w"
    emu._vlog = True
    with open(os.path.join(emu.outdir, "visit.jsonl"), mode, encoding="utf-8") as fh:
        fh.write(json.dumps(rec, ensure_ascii=False) + "\n")


class Shooter:
    def __init__(self, emu, prefix):
        self.emu, self.prefix, self.n, self.last, self.names = emu, prefix, 0, None, []

    def __call__(self, tag="", dedupe=False):
        self.n += 1
        name = "%s_%02d%s" % (self.prefix, self.n, ("_" + tag) if tag else "")
        p = rc._shot(self.emu, name)
        data, same = rc._same_as(p, self.last)
        if same and dedupe:
            os.remove(p)
            self.emu.shots = self.emu.shots[:-1]
            self.n -= 1
            return None
        self.last = data
        self.names.append(name)
        return name


def popup_shots(emu, prefix, maxf=300):
    """Shots while the map-name pop-up runs (every 6 frames, repeats dropped)."""
    sh = Shooter(emu, prefix + "_p")
    seen = False
    for _ in range(maxf // 6):
        if emu.task_active("Task_MapNamePopUpWindow"):
            seen = True
            sh(dedupe=True)
        elif seen:
            break
        emu.frames(6)
    return sh.names


@script_op("arrive")
def _op_arrive(emu, f, path):
    mapc, x, y, prefix = f[1], int(f[2], 0), int(f[3], 0), f[4]
    g, n = hns.map_lookup(emu.elf, mapc)
    if not emu.in_overworld():
        raise HnsError("arrive: not in the overworld (%s)" % emu.cb2_name())
    sb1 = emu.sb1()
    pos, loc = sb1 + hns.OFF["SB1.pos"], sb1 + hns.OFF["SB1.location"]
    emu.w16(pos, x)
    emu.w16(pos + 2, y)
    emu.w8(loc, g)
    emu.w8(loc + 1, n)
    emu.w8(loc + 2, 0xFF)
    emu.w16(loc + 4, x)
    emu.w16(loc + 6, y)
    emu.w32(emu.CB2, emu.sym("CB2_LoadMap"))
    if not emu.wait32(emu.CB2, emu.sym("CB2_Overworld"), 600):
        raise HnsError("arrive: the map load did not return (%s)" % emu.cb2_name())
    names = popup_shots(emu, prefix)
    if not emu.wait_controllable(1200):
        emu.shot(prefix + "_held")
        print("arrive %s: a script holds the player" % mapc)
    else:
        emu.frames(4)
        rc._shot(emu, prefix + "_field")
    print("arrive %s (%d.%d) %d,%d: %d pop-up shot(s) @%d" % (mapc, g, n, x, y, len(names), emu.sync()))


@script_op("stepmap")
def _op_stepmap(emu, f, path):
    d, prefix, maxn = f[1], f[2], _arg(f, 3, 30)
    (g0, n0, _, _, _), _ = emu.location()
    w, h, coll, behavior = ho.map_grid(emu)
    pos = emu.location()[1]
    edge = {"UP": [(x, 0) for x in range(w)], "DOWN": [(x, h - 1) for x in range(w)],
            "LEFT": [(0, y) for y in range(h)], "RIGHT": [(w - 1, y) for y in range(h)]}[d]
    for t in sorted((t for t in edge if not coll(*t)), key=lambda t: abs(t[0] - pos[0]) + abs(t[1] - pos[1])):
        if _route(emu, t) is not None:
            _walk(emu, t)
            break
    for _ in range(maxn):
        emu.frames(16, d)
        (g, n, _, _, _), _ = emu.location()
        if (g, n) != (g0, n0) or not emu.in_overworld():
            break
    emu.wait32(emu.CB2, emu.sym("CB2_Overworld"), 600)
    names = popup_shots(emu, prefix)
    emu.wait_controllable(1200)
    rc._shot(emu, prefix + "_field")
    print("stepmap %s: now %s, %d pop-up shot(s) @%d" % (d, emu.location(), len(names), emu.sync()))


def list_pos(emu):
    d = emu.task_data(LIST_TASK)
    if len(d) != 1:
        return None
    return d[0][12] + d[0][13]


def shop(emu, sh):
    """The shop menu is up: BUY, every row of the list, out, SEE YA."""
    emu.wait_quiet(300)
    emu.frames(2)
    sh("shopmenu")
    emu.tap("A", 0)
    if not emu.wait32(emu.CB2, emu.sym("CB2_BuyMenu"), 900):
        raise HnsError("shop: no buy menu (%s)" % emu.cb2_name())
    emu.wait_until(lambda: emu.task_active("Task_BuyMenu"), 900, "Task_BuyMenu")
    emu.wait_quiet(300)
    sh("buy")
    first = list_pos(emu)
    for i in range(80):
        emu.tap("DOWN", 10)
        emu.frames(6)
        p = list_pos(emu)
        sh("buy")
        if p == first or p is None:
            break
    emu.tap("B", 0)
    emu.wait32(emu.CB2, emu.sym("CB2_Overworld"), 900)
    emu.wait_until(lambda: emu.task_active("Task_ShopMenu"), 900, "Task_ShopMenu")
    emu.wait_quiet(300)
    emu.tap("B", 6)


def converse(emu, prefix, yes=False, maxf=60000, picks=None):
    """See the module doc. PICKS: rows to take at the first menus (DOWN x row, A), in order.
    Returns (end, shot names)."""
    ow, bcb2 = emu.sym("CB2_Overworld"), emu.sym("BattleMainCB2")
    picks = list(picks or [])
    sh = Shooter(emu, prefix)
    waited, stuck, menus, screens, battles, stucks = 0, 0, 0, 0, 0, 0
    prev = "idle"
    shops = 0
    while waited < maxf:
        cb = emu.cb2()
        if cb == bcb2:
            battles += 1
            r6trainers.tbwin(emu, "%s_b%d" % (prefix, battles))
            sh.names.append("%s_b%d_*" % (prefix, battles))
            prev, stuck = "idle", 0
            continue
        if emu.controllable():
            emu.frames(8)
            if emu.controllable():
                if emu.task_active("Task_MapNamePopUpWindow"):
                    sh.names += popup_shots(emu, prefix + "_%02d" % (sh.n + 1))
                return "free", sh.names
            continue
        if cb == ow and emu.task_active("Task_ShopMenu") and emu.text_state() != "busy" and not emu.wants_key():
            shops += 1
            if shops > 3:
                raise HnsError("converse %s: shop menu again" % prefix)
            shop(emu, sh)
            prev, stuck = "idle", 0
            continue
        if cb == ow and emu.tasks_named(emu.MENU_TASKS):
            emu.wait_menu_ready()
            emu.wait_quiet(300)
            emu.frames(2)
            sh("menu")
            menus += 1
            if menus > 10:
                raise HnsError("converse %s: more than 10 menus" % prefix)
            if picks:
                for _ in range(picks.pop(0)):
                    emu.tap("DOWN", 6)
                    emu.wait_quiet(120)
                emu.frames(2)
                sh("pick")
                emu.tap("A", 6)
                emu.frames(20)
                prev, stuck = "idle", 0
                continue
            emu.tap("A" if yes else "B", 6)
            emu.frames(20)
            if not yes and emu.tasks_named(emu.MENU_TASKS) and not emu.wants_key() and emu.text_state() != "busy":
                # B is ignored by this menu: take the highlighted row
                emu.tap("A", 6)
                emu.frames(10)
            prev, stuck = "idle", 0
            continue
        if cb == ow and emu.task_active("Task_MapNamePopUpWindow") and not emu.wants_key():
            names = popup_shots(emu, prefix + "_%02d" % (sh.n + 1))
            sh.names += names
            continue
        if emu.wants_key():
            emu.wait_quiet(600)
            emu.frames(2)
            sh()
            _press(emu)
            prev, stuck = emu.text_state(), 0
            waited += 10
            continue
        st = emu.text_state()
        if prev == "busy" and st != "busy" and cb == ow:
            emu.frames(2)
            sh(dedupe=True)
            stuck = 0
        elif cb != ow and not emu.fading() and st != "busy":
            stuck += 2
            if stuck >= 240:
                sh("scr", dedupe=True)
                screens += 1
                if screens > 40:
                    raise TourTimeout("converse %s: still on %s" % (prefix, emu.cb2_name()))
                emu.tap("B", 6)
                stuck = 0
        elif cb == ow and not emu.fading() and st != "busy":
            stuck += 2
            if stuck >= 1500:
                sh("stuck", dedupe=True)
                stucks += 1
                if stucks > 4:
                    raise TourTimeout("converse %s: stuck (tasks %s)" % (prefix, [t[2] for t in emu.tasks()]))
                emu.tap("B", 6)
                stuck = 0
        prev = st
        emu.frames(2)
        waited += 2
    raise TourTimeout("converse %s: not free after %d frames (%s)" % (prefix, maxf, emu.cb2_name()))


def _press(emu, tries=6):
    emu.tap("A", 0)
    for _ in range(tries):
        for _ in range(45):
            if not emu.wants_key():
                return
            emu.frames(2)
        emu.tap("A", 4)
    raise TourTimeout("the text did not take the key")


@script_op("converse")
def _op_converse(emu, f, path):
    end, names = converse(emu, f[1], yes=len(f) > 2 and f[2] == "yes")
    print("converse %s: %s, %d shot(s) @%d" % (f[1], end, len(names), emu.sync()))


MB_COUNTER = 128
_ORIG_OBJECTS = ho.objects


def _objects_and_warps(emu):
    """hilltent_ops.objects plus every warp tile of the map as a pseudo-object (local id 255), so
    walkto / bfs route around warps instead of stepping on one by accident."""
    out = _ORIG_OBJECTS(emu)
    try:
        d = here(emu)[3]
    except HnsError:
        return out
    return out + [(255, int(w["x"]), int(w["y"])) for w in d.get("warp_events") or []]


ho.objects = _objects_and_warps


def _free_adjacent(emu, ox, oy):
    """Free tiles next to (ox, oy), and the tile beyond a counter (talking across a counter)."""
    w, h, coll, behavior = ho.map_grid(emu)
    others = {(o[1], o[2]) for o in ho.objects(emu)}
    out = []
    for (dx, dy), face in (((0, 1), "UP"), ((0, -1), "DOWN"), ((1, 0), "LEFT"), ((-1, 0), "RIGHT")):
        t = (ox + dx, oy + dy)
        if not (0 <= t[0] < w and 0 <= t[1] < h):
            continue
        if not coll(*t) and t not in others:
            out.append((t, face))
        elif behavior(*t) == MB_COUNTER:
            t2 = (ox + 2 * dx, oy + 2 * dy)
            if 0 <= t2[0] < w and 0 <= t2[1] < h and not coll(*t2) and t2 not in others:
                out.append((t2, face))
    return out


_ORIG_CONTROLLABLE = hns.Emu.controllable


def _controllable(self):
    """hns.Emu.controllable, plus the state a `waitstate` leaves when the screen it waited for
    returned through CB2_ReturnToField (the wall clock): the script context stays WAITING, but
    field controls are unlocked and the player can walk (DoCB1_Overworld only checks the lock)."""
    if _ORIG_CONTROLLABLE(self):
        return True
    return (self.cb2() == self.sym("CB2_Overworld")
            and self.r32(self.CB1) == self.sym("CB1_Overworld")
            and self.r8(self.sym("sGlobalScriptContextStatus")) == 1
            and self.r8(self.sym("sLockFieldControls")) == 0
            and self.text_state() == "idle" and not self.fading()
            and not self.tasks_named(self.MENU_TASKS))


hns.Emu.controllable = _controllable


def _route(emu, goal):
    w, h, coll, behavior = ho.map_grid(emu)
    others = {(o[1], o[2]) for o in ho.objects(emu)} - {goal}
    pos = emu.location()[1]
    return ho.bfs(w, h, coll, pos, goal, others, ho.ledge_map(emu, w, h, behavior),
                  ho.slide_map(emu, w, h, behavior), ho.ice_set(emu, w, h, behavior))


def repel(emu, steps=250):
    emu.set_var(emu.const("VAR_REPEL_STEP_COUNT"), steps)


def _walk(emu, tile):
    """walkto; returns 'reached', 'taken' (a script took the player), 'warp' or 'fail'. A wild
    battle on the way (the repel ran out) is fought and the walk tried again."""
    (g0, n0, _, _, _), _ = emu.location()
    for attempt in range(3):
        repel(emu)
        try:
            ho._op_walkto(emu, ["walkto", str(tile[0]), str(tile[1])], None)
            break
        except HnsError as e:
            if emu.cb2() == emu.sym("BattleMainCB2"):
                r6trainers.tbwin(emu, "walkbattle_%d" % emu.sync())
                emu.wait_controllable(2400)
                continue
            print("   walk %s: %s" % (tile, e))
            return "fail"
    (g, n, _, _, _), pos = emu.location()
    if (g, n) != (g0, n0):
        return "warp"
    if pos == tuple(tile):
        return "reached"
    if not emu.controllable():
        return "taken"
    return "fail"


def _face_a(emu, face):
    emu.frames(2, face)
    emu.frames(14)
    emu.tap("A", 2)
    for _ in range(12):
        emu.frames(2)
        if not emu.controllable():
            return True
    return False


def _warp_next_to(emu, tiles):
    g, n, _, _, _ = here(emu)
    for t, face in tiles:
        try:
            emu.warp(g, n, t[0], t[1])
            return t, face
        except HnsError as e:
            print("   warp next to: %s" % e)
    return None, None


def _approach_spawn(emu, lid, xy):
    """An object off camera is not in gObjectEvents: walk toward its map.json tile until it
    spawns (the nearest reachable tile within 4 of it), else warp there."""
    if any(o[0] == lid for o in ho.objects(emu)):
        return True
    w, h, coll, behavior = ho.map_grid(emu)
    x0, y0 = xy
    cands = sorted(((x, y) for y in range(max(0, y0 - 4), min(h, y0 + 5)) for x in range(max(0, x0 - 4), min(w, x0 + 5))
                    if not coll(x, y)), key=lambda t: abs(t[0] - x0) + abs(t[1] - y0))
    for t in cands[:12]:
        if _route(emu, t) is not None:
            _walk(emu, t)
            break
    emu.frames(8)
    if any(o[0] == lid for o in ho.objects(emu)):
        return True
    g, n, _, _, _ = here(emu)
    for t in cands[:8]:
        try:
            emu.warp(g, n, t[0], t[1])
            break
        except HnsError as e:
            print("   spawn warp %s: %s" % (t, e))
            continue
    emu.frames(8)
    return any(o[0] == lid for o in ho.objects(emu))


def talk_object(emu, lid, prefix, yes=False, xy=None, picks=None):
    """Walk next to the live object LID, face it, A, converse. Returns (how, shots)."""
    names = []
    failed = set()
    if xy is not None and not _approach_spawn(emu, lid, xy):
        return "nospawn", names
    for attempt in range(6):
        obj = [o for o in ho.objects(emu) if o[0] == lid]
        if not obj:
            return "gone", names
        _, ox, oy = obj[0]
        pos = emu.location()[1]
        adj = _free_adjacent(emu, ox, oy)
        here_face = {(ox, oy + 1): "UP", (ox, oy - 1): "DOWN", (ox + 1, oy): "LEFT", (ox - 1, oy): "RIGHT"}
        here_face.update({t: fc for t, fc in adj})
        if pos in here_face and (pos, (ox, oy)) not in failed:
            if _face_a(emu, here_face[pos]):
                end, nm = converse(emu, prefix, yes, picks=picks)
                return "talked", names + nm
            failed.add((pos, (ox, oy)))
            continue
        best = None
        for t, face in adj:
            if (t, (ox, oy)) in failed:
                continue
            r = _route(emu, t)
            if r is not None and (best is None or len(r) < len(best[1])):
                best = (t, r)
        if best is None:
            t, face = _warp_next_to(emu, [a for a in adj if (a[0], (ox, oy)) not in failed])
            if t is None:
                return "unreachable", names
            names.append("(warped)")
            continue
        how = _walk(emu, best[0])
        if how == "taken":
            end, nm = converse(emu, prefix + "_spot")
            names += nm
            continue
        if how == "warp":
            return "warped-away", names
        if how == "fail":
            failed.add((best[0], (ox, oy)))
            emu.frames(20)
    return "noresponse", names


def read_sign(emu, sx, sy, prefix):
    w, h, coll, behavior = ho.map_grid(emu)
    cands = [((sx, sy + 1), "UP"), ((sx + 1, sy), "LEFT"), ((sx - 1, sy), "RIGHT"), ((sx, sy - 1), "DOWN")]
    tried = []
    for (t, face) in cands:
        if not (0 <= t[0] < w and 0 <= t[1] < h) or coll(*t):
            continue
        tried.append((t, face))
        if emu.location()[1] != t:
            if _route(emu, t) is None:
                continue
            if _walk(emu, t) != "reached":
                continue
        if _face_a(emu, face):
            return converse(emu, prefix)[0], prefix
    for (t, face) in tried:
        g, n, _, _, _ = here(emu)
        try:
            emu.warp(g, n, t[0], t[1])
        except HnsError:
            continue
        if _face_a(emu, face):
            return "warped+" + converse(emu, prefix)[0], prefix
    return "unreachable", prefix


@script_op("talkobj")
def _op_talkobj(emu, f, path):
    """talkobj LID PREFIX [yes] [pick=R,R]"""
    lid, prefix = int(f[1], 0), f[2]
    picks = [int(x) for o in f[3:] if o.startswith("pick=") for x in o[5:].split(",")]
    how, names = talk_object(emu, lid, prefix, yes="yes" in f[3:], picks=picks)
    g, n, folder, d, pos = here(emu)
    _log(emu, dict(map=folder, kind="obj", id=lid, prefix=prefix, how=how, shots=len(names)))
    print("talkobj %d: %s, %d shot(s) @%d" % (lid, how, len(names), emu.sync()))


@script_op("sign")
def _op_sign(emu, f, path):
    sx, sy, prefix = int(f[1]), int(f[2]), f[3]
    how, _ = read_sign(emu, sx, sy, prefix)
    g, n, folder, d, pos = here(emu)
    _log(emu, dict(map=folder, kind="sign", id="%d,%d" % (sx, sy), prefix=prefix, how=how))
    print("sign %d,%d: %s @%d" % (sx, sy, how, emu.sync()))


SKIP_SCRIPTS = {"NULL", "0x0", "0", ""}


@script_op("visit")
def _op_visit(emu, f, path):
    prefix = f[1]
    opts = {}
    for o in f[2:]:
        k, _, v = o.partition("=")
        opts[k] = v
    ids = lambda k: {int(x) for x in opts.get(k, "").split(",") if x}  # noqa: E731
    skip, yes, only = ids("skip"), ids("yes"), ids("only")
    g, n, folder, d, pos = here(emu)
    if not d:
        raise HnsError("visit: no map.json for %d.%d" % (g, n))
    objs = d.get("object_events") or []
    seen_keys = getattr(emu, "_visit_keys", set())
    emu._visit_keys = seen_keys
    todo = []
    if "noobjs" not in opts:
        live = {o[0]: (o[1], o[2]) for o in ho.objects(emu)}
        for i, o in enumerate(objs):
            lid = i + 1
            scr = str(o.get("script", ""))
            if scr in SKIP_SCRIPTS or lid in skip or (only and lid not in only):
                continue
            flag = str(o.get("flag", "0"))
            if lid not in live and flag not in ("0", "", "None") and emu.get_flag(emu.const(flag)):
                _log(emu, dict(map=folder, kind="obj", id=lid, script=scr, how="hidden", flag=flag))
                continue
            if lid not in live:
                live[lid] = (int(o["x"]), int(o["y"]))      # off camera: spawns when the player is near
            gfx = o.get("graphics_id", "")
            key = (scr, gfx)
            item = "Item" in scr or "ITEM_BALL" in gfx
            if key in seen_keys and not item:
                _log(emu, dict(map=folder, kind="obj", id=lid, script=scr, how="dup"))
                continue
            seen_keys.add(key)
            todo.append(("obj", lid, live[lid], scr))
    if "nosigns" not in opts:
        want = {tuple(int(v) for v in s.split(":")) for s in opts.get("signs", "").split(",") if s}
        for b in d.get("bg_events") or []:
            if b.get("type") != "sign":
                continue
            xy = (int(b["x"]), int(b["y"]))
            if want and xy not in want:
                continue
            scr = str(b.get("script", ""))
            key = ("sign", scr)
            if key in seen_keys:
                _log(emu, dict(map=folder, kind="sign", id="%d,%d" % xy, script=scr, how="dup"))
                continue
            seen_keys.add(key)
            todo.append(("sign", xy, xy, scr))
    print("visit %s: %s, %d target(s)" % (prefix, folder, len(todo)))
    cur = emu.location()[1]
    while todo:
        todo.sort(key=lambda t: abs(t[2][0] - cur[0]) + abs(t[2][1] - cur[1]))
        kind, ident, xy, scr = todo.pop(0)
        g1, n1, _, _, _ = here(emu)
        if (g1, n1) != (g, n):
            print("   visit: left the map (now %d.%d); back" % (g1, n1))
            emu.warp(g, n, cur[0], cur[1])
        try:
            if kind == "obj":
                p = "%s_o%02d" % (prefix, ident)
                how, names = talk_object(emu, ident, p, yes=ident in yes, xy=xy)
                _log(emu, dict(map=folder, kind="obj", id=ident, script=scr, prefix=p, how=how, shots=len(names)))
            else:
                p = "%s_s%d_%d" % (prefix, xy[0], xy[1])
                how, _ = read_sign(emu, xy[0], xy[1], p)
                _log(emu, dict(map=folder, kind="sign", id="%d,%d" % xy, script=scr, prefix=p, how=how))
        except (HnsError, TourTimeout) as e:
            emu.shot("%s_err_%s" % (prefix, str(ident).replace(",", "_").replace(" ", "")))
            _log(emu, dict(map=folder, kind=kind, id=str(ident), script=scr, how="error", detail=str(e)[:300]))
            print("   visit %s %s: %s" % (kind, ident, e))
            for _ in range(60):
                if emu.controllable():
                    break
                if emu.cb2() == emu.sym("BattleMainCB2"):
                    r6trainers.tbwin(emu, "%s_rec" % prefix)
                    continue
                emu.tap("B", 10)
            if not emu.controllable():
                raise
        print("   %s %s %s: %s" % (kind, ident, scr, how))
        cur = emu.location()[1]
    print("visit %s done @%d" % (prefix, emu.sync()))


@script_op("wild")
def _op_wild(emu, f, path):
    try:
        _wild(emu, f)
    except (HnsError, TourTimeout) as e:
        if emu.cb2() == emu.sym("BattleMainCB2") or not emu.controllable():
            raise
        emu.shot(f[1] + "_err")
        _log(emu, dict(map=here(emu)[2], kind="wild", prefix=f[1], how="error", detail=str(e)[:200]))
        print("wild %s: %s (skipped)" % (f[1], e))


def _wild(emu, f):
    prefix, maxsteps = f[1], _arg(f, 2, 400)
    w, h, coll, behavior = ho.map_grid(emu)
    repel(emu)
    pos = emu.location()[1]
    others = {(o[1], o[2]) for o in ho.objects(emu)}
    enc = {(x, y) for y in range(h) for x in range(w)
           if behavior(x, y) in ENCOUNTER_MB and not coll(x, y) and (x, y) not in others}
    tiles = sorted((t for t in enc if any((t[0] + dx, t[1] + dy) in enc for dx, dy in ((1, 0), (-1, 0), (0, 1), (0, -1)))),
                   key=lambda t: abs(t[0] - pos[0]) + abs(t[1] - pos[1]))
    start = None
    tries = 0
    for t in tiles[:80]:
        if _route(emu, t) is None:
            continue
        tries += 1
        if _walk(emu, t) == "reached":
            start = t
            break
        if tries >= 8:
            break
    if start is None and pos in tiles:
        start = pos
    if start is None:
        g, n, _, _, _ = here(emu)
        for t in tiles[:10]:
            try:
                emu.warp(g, n, t[0], t[1])
                start = t
                break
            except HnsError:
                continue
    if start is None:
        raise HnsError("wild: no reachable encounter tile")
    others = {(o[1], o[2]) for o in ho.objects(emu)}
    # pace between two adjacent encounter tiles
    x, y = start
    pair = None
    for d, (dx, dy) in (("LEFT", (-1, 0)), ("RIGHT", (1, 0)), ("UP", (0, -1)), ("DOWN", (0, 1))):
        t = (x + dx, y + dy)
        if 0 <= t[0] < w and 0 <= t[1] < h and behavior(*t) in ENCOUNTER_MB and not coll(*t) and t not in others:
            back = {"LEFT": "RIGHT", "RIGHT": "LEFT", "UP": "DOWN", "DOWN": "UP"}[d]
            pair = (d, back)
            break
    if pair is None:
        raise HnsError("wild: no second encounter tile next to %s" % (start,))
    bcb2 = emu.sym("BattleMainCB2")
    steps = 0
    repel(emu, 0)
    while steps < maxsteps:
        for d in pair:
            emu.frames(16, d)
            steps += 1
            for _ in range(20):
                if emu.cb2() == bcb2 or emu.controllable():
                    break
                emu.frames(4)
            if not emu.controllable():
                break
        if not emu.controllable():
            break
    if emu.cb2() != bcb2:
        emu.wait_until(lambda: emu.cb2() == bcb2 or emu.controllable(), 600, "the battle")
    if emu.cb2() != bcb2:
        raise HnsError("wild: no encounter in %d steps" % steps)
    n, end = hns.battle_walk(emu, prefix, (), 30, 6000)
    print("  wild intro: %d page(s), %s" % (n, end))
    if end.startswith("input:HandleInputChooseAction"):
        rc._shot(emu, prefix + "_action")
        hns.battle_cursor(emu, "gActionSelectionCursor", 3)
        emu.tap("A", 4)
        n2, end2 = hns.battle_walk(emu, prefix + "_run", (), 20, 6000)
        print("  wild run: %d page(s), %s" % (n2, end2))
        if emu.cb2() == bcb2 and not end2.startswith("free"):
            r6trainers.tbwin(emu, prefix + "_win")
    elif emu.cb2() == bcb2:
        r6trainers.tbwin(emu, prefix + "_win")
    emu.wait_controllable(2400)
    rc._shot(emu, prefix + "_after")
    _log(emu, dict(map=here(emu)[2], kind="wild", prefix=prefix, steps=steps))
    print("wild %s: %d step(s) @%d" % (prefix, steps, emu.sync()))


@script_op("hofwatch")
def _op_hofwatch(emu, f, path):
    """See the module doc."""
    prefix, maxf = f[1], _arg(f, 2, 40000)
    sh = Shooter(emu, prefix)
    hofs = {emu.sym("CB2_DoHallOfFameScreen"), emu.sym("CB2_HallOfFame")}
    waited = 0
    seen_tasks = set()
    while waited < maxf:
        cb = emu.cb2()
        if cb not in hofs and emu.wants_key():
            emu.wait_quiet(600)
            emu.frames(2)
            sh()
            _press(emu)
            continue
        if cb in hofs:
            names = {t[2] for t in emu.tasks()}
            for want in ("Task_Hof_WaitToDisplayMon", "Task_Hof_TryDisplayAnotherMon",
                         "Task_Hof_DoConfetti", "Task_Hof_ExitOnKeyPressed", "Task_Hof_WaitBorderFadeAway"):
                hit = [nm for nm in names if nm.endswith(want)]
                if hit:
                    key = (want, emu.r8(emu.sym("gSaveBlock2Ptr")) if False else waited // 120)
                    if want == "Task_Hof_TryDisplayAnotherMon":
                        emu.frames(4)
                        sh("mon", dedupe=True)
                        emu.wait_until(lambda: not any(t[2].endswith(want) for t in emu.tasks()), 900, "next mon")
                    elif want not in seen_tasks:
                        seen_tasks.add(want)
                        emu.frames(20 if want == "Task_Hof_DoConfetti" else 4)
                        sh(want.split("_")[-1].lower(), dedupe=True)
                        if want == "Task_Hof_ExitOnKeyPressed":
                            emu.frames(30)
                            sh("player", dedupe=True)
                            emu.tap("A", 10)
            emu.frames(2)
            waited += 2
            continue
        if seen_tasks and cb not in hofs and cb != emu.sym("CB2_Overworld"):
            print("hofwatch %s: left the Hall of Fame for %s, %d shot(s) @%d" % (prefix, emu.cb2_name(), sh.n, emu.sync()))
            return
        if emu.controllable() and (sh.n or waited > 600):
            print("hofwatch %s: free, %d shot(s) @%d" % (prefix, sh.n, emu.sync()))
            return
        emu.frames(2)
        waited += 2
    raise TourTimeout("hofwatch %s: %d frames (%s)" % (prefix, maxf, emu.cb2_name()))


@script_op("periodicx")
def _op_periodicx(emu, f, path):
    """periodicx PREFIX FRAMES EVERY: one shot every EVERY frames for FRAMES frames on any screen,
    repeats dropped (credits)."""
    prefix, frames, every = f[1], int(f[2]), int(f[3])
    sh = Shooter(emu, prefix)
    t = 0
    while t < frames:
        emu.frames(every)
        t += every
        sh(dedupe=True)
    print("periodicx %s: %d shot(s) @%d" % (prefix, sh.n, emu.sync()))


@script_op("ctlinfo")
def _op_ctlinfo(emu, f, path):
    print("ctlinfo cb1 %s cb2 %s scriptctx %d lock %d" % (emu.elf.where(emu.r32(emu.CB1)), emu.cb2_name(),
          emu.r8(emu.sym("sGlobalScriptContextStatus")), emu.r8(emu.sym("sLockFieldControls"))))


@script_op("flagsx")
def _op_flagsx(emu, f, path):
    print("flags " + " ".join("%s=%d" % (n, emu.get_flag(emu.const(n))) for n in f[1:]))


if __name__ == "__main__":
    sys.argv[0] = hns.__file__
    sys.exit(hns.main())
