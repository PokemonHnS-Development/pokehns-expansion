#!/usr/bin/env python3
"""Ops for the Trainer Hill and Battle Tent runs (ht.py). Imported after r3bf (hns + r2sf ops).

    battle2 PREFIX [MAXTURNS] [MODE]
        fight the battle on screen to its end; every text page is a shot (PREFIX_tNN_MM).
        At each action prompt of the first player battler the foes' battle HP is set by MODE:
          ko     foes at 1 HP (default): the first hit wins
          keep   foes back to their HP at the start of the battle every turn (nobody faints; the
                 Battle Arena judges after three turns)
        Every player battler picks FIGHT, move slot 0 and the default target.
        A party menu after a faint picks the first Pokemon that can come in (A, A).
    hpall SIDE HP        set the battle HP of every SIDE (player/enemy) battler that is not fainted
    battlers             print species and HP of gBattleMons[0..3]
"""
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(HERE, "..", ".."))
import hns  # noqa: E402
from hns import script_op, HnsError, TourTimeout, _arg  # noqa: E402

BM_SIZE = 0x88
BM_HP = hns.BATTLE_OFF["BattlePokemon.hp"]


def battlers(emu):
    n = emu.r8(emu.sym("gBattlersCount"))
    base = emu.sym("gBattleMons")
    out = []
    for b in range(n):
        raw = emu.read(base + BM_SIZE * b, BM_SIZE)
        out.append((b, int.from_bytes(raw[0:2], "little"), int.from_bytes(raw[BM_HP:BM_HP + 2], "little")))
    return out


def set_hp(emu, side, hp, only_alive=True):
    base = emu.sym("gBattleMons")
    for b, sp, cur in battlers(emu):
        if (b & 1) != (1 if side == "enemy" else 0):
            continue
        if only_alive and (cur == 0 or sp == 0):
            continue
        emu.w16(base + BM_SIZE * b + BM_HP, hp)


@script_op("hpall")
def _op_hpall(emu, f, path):
    set_hp(emu, f[1], int(f[2], 0))
    print("hpall %s %s: %s" % (f[1], f[2], battlers(emu)))


@script_op("battlers")
def _op_battlers(emu, f, path):
    print("battlers %s" % battlers(emu))


@script_op("battle2")
def _op_battle2(emu, f, path):
    prefix = f[1]
    maxturns = _arg(f, 2, 20)
    mode = f[3] if len(f) > 3 else "ko"
    turn, start_hp, presses = 0, None, 0
    seg = 0
    while True:
        seg += 1
        n, end = hns.battle_walk(emu, "%s_t%02d_%02d" % (prefix, turn, seg), (), 80,
                                 stop_tasks=("Task_HandleMultichoiceInput", "Task_HandleYesNoInput"))
        print("  battle2 %s seg %d: %d page(s), %s" % (prefix, seg, n, end))
        if end == "free" or (not hns.in_battle(emu) and ("Multichoice" in end or "YesNo" in end)):
            print("battle2 %s: over after %d turn(s) @%d" % (prefix, turn, emu.sync()))
            return
        if end == "maxpages":
            continue
        if start_hp is None and hns.in_battle(emu):
            start_hp = {b: hp for b, _, hp in battlers(emu)}
        if end.startswith("input:"):
            func = end[6:].split("#")[0]
            b = 2 if end.endswith("#2") else 0
            if func == "HandleInputChooseAction":
                if b == 0:
                    turn += 1
                    seg = 0
                    if turn > maxturns:
                        raise HnsError("battle2 %s: still going after %d turns" % (prefix, maxturns))
                    base = emu.sym("gBattleMons")
                    for bb, sp, cur in battlers(emu):
                        if not bb & 1 and cur:
                            mx = emu.r16(base + BM_SIZE * bb + BM_HP + 4)
                            if mx >= cur:
                                emu.w16(base + BM_SIZE * bb + BM_HP, mx)
                    if mode == "ko":
                        set_hp(emu, "enemy", 1)
                    elif mode == "keep":
                        base = emu.sym("gBattleMons")
                        for bb, sp, cur in battlers(emu):
                            if bb & 1 and cur:
                                emu.w16(base + BM_SIZE * bb + BM_HP, start_hp.get(bb, cur))
                    print("  battle2 turn %d: %s" % (turn, battlers(emu)))
                hns.battle_cursor(emu, "gActionSelectionCursor", 0, battler=b)
                emu.tap("A", 4)
            elif func == "HandleInputChooseMove":
                hns.battle_cursor(emu, "gMoveSelectionCursor", (turn - 1) % 2 if mode == "ko" else 0, battler=b)
                emu.tap("A", 4)
            elif func in ("HandleInputChooseTarget", "HandleInputShowTargets", "HandleInputShowEntireFieldTargets"):
                emu.tap("A", 4)
            elif func == "PlayerHandleYesNoInput":
                emu.tap("B", 4)
            else:
                emu.tap("A", 4)
            emu.frames(4)
            continue
        if end.startswith("task:"):
            presses += 1
            if presses > 12:
                raise HnsError("battle2 %s: stuck at %s" % (prefix, end))
            if "Task_HandleChooseMonInput" in end:
                # a Pokemon fainted: the cursor starts on the one in battle; the right column
                # holds the bench (slots 2-5 in a double battle, 1-5 in a single)
                _shot(emu, "%s_t%02d_party" % (prefix, turn))
                emu.tap("RIGHT", 6)
                emu.wait_quiet(300)
                for _ in range(presses - 1):
                    emu.tap("DOWN", 6)
                    emu.wait_quiet(300)
                emu.tap("A", 20)
                emu.wait_quiet(300)
            elif "Task_HandleSelectionMenuInput" in end:
                _shot(emu, "%s_t%02d_partymenu" % (prefix, turn))
                emu.tap("A", 20)
            else:
                emu.tap("A", 20)
            emu.frames(20)
            continue
        if end.startswith("prompt:"):
            emu.tap("B", 4)
            emu.frames(8)
            continue
        raise HnsError("battle2 %s: unexpected end %s" % (prefix, end))


SAVE_INPUT = ("SaveConfirmInputCallback", "SaveOverwriteInputCallback")


def _shot(emu, name):
    emu.frames(2)
    emu.shot(name)
    emu.shots = getattr(emu, "shots", []) + [name]


def dialogue(emu, prefix, expect, maxpages=60, maxframes=6000, first=1):
    """Walk field text (one shot per page, A to go on) to the first decision point:
       menu     a script choice menu reads input (shot taken)
       save     the save dialog's YES/NO reads input (shot taken)
       free     the player can walk
       battle   a battle has started
       screen   callback2 left the overworld for another screen (not a battle, not a map load)
    EXPECT: '|'-separated names; anything else stops with an error. Returns (pages, end)."""
    ow = emu.sym("CB2_Overworld")
    bcb2 = emu.sym("BattleMainCB2")
    loads = set()
    for n in ("CB2_DoChangeMap", "CB2_LoadMap", "CB2_LoadMap2", "CB2_ReturnToField", "CB2_ReturnToFieldLocal",
              "CB2_ReturnToFieldContinueScript", "CB2_ReturnToFieldContinueScriptPlayMapMusic",
              "CB2_ReturnToFieldFadeFromBlack", "CB2_ReturnToFieldWithOpenMenu", "CB2_OverworldBasic",
              "CB2_InitBattle", "CB2_HandleStartBattle", "CB2_PreInitMultiBattle", "CB2_PreInitIngamePlayerPartnerBattle"):
        try:
            loads.add(emu.sym(n))
        except HnsError:
            pass
    save_cbs = {emu.sym("start_menu:" + s) if False else emu.sym(s) for s in SAVE_INPUT}
    sdc = emu.sym("sSaveDialogCallback")
    n, idle, last_box, offscreen = first - 1, 0, None, 0
    was_busy = False
    exp = expect.split("|")

    def done(end):
        if end not in exp:
            _shot(emu, "%s_%02d_unexpected" % (prefix, n + 1))
            raise HnsError("dlg %s: stopped at %s, expected %s (callback2 %s, tasks %s)"
                           % (prefix, end, expect, emu.cb2_name(), [t[2] for t in emu.tasks()]))
        print("dlg %s: %d page(s), %s @%d" % (prefix, n - first + 1, end, emu.sync()))
        return n, end

    while True:
        cb = emu.cb2()
        if cb == bcb2:
            return done("battle")
        if cb != ow and cb not in loads and not emu.fading():
            offscreen += 2
            if offscreen > 30:
                return done("screen")
        else:
            offscreen = 0
        if cb == ow:
            if emu.controllable():
                emu.frames(8)
                if emu.controllable():
                    return done("free")
                continue
            menus = emu.tasks_named(emu.MENU_TASKS)
            if menus:
                emu.wait_menu_ready()
                emu.wait_quiet(600)
                n += 1
                _shot(emu, "%s_%02d" % (prefix, n))
                return done("menu")
            if emu.r32(sdc) in save_cbs and emu.text_state() != "busy":
                emu.wait_quiet(600)
                emu.frames(4)
                n += 1
                _shot(emu, "%s_%02d" % (prefix, n))
                return done("save")
        if idle >= maxframes:
            raise TourTimeout("dlg %s: stuck %d frames after %d page(s) (callback2 %s, tasks %s)"
                              % (prefix, idle, n, emu.cb2_name(), [t[2] for t in emu.tasks()]))
        if n >= maxpages + first - 1:
            raise HnsError("dlg %s: %d pages" % (prefix, n))
        st = emu.text_state()
        if st == "busy" or emu.fading():
            was_busy = True
            emu.frames(2)
            idle += 2
            continue
        if was_busy and not emu.wants_key() and cb == ow:
            # a message the script does not wait on (a fanfare, an item jingle): keep it once
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
                _shot(emu, "%s_%02d" % (prefix, n))
            last_box = box
            emu.tap("A", 0)
            emu.wait_until(lambda: not emu.wants_key(), 90, "the text to take the key", step=1)
            idle = 0
            continue
        emu.frames(2)
        idle += 2


@script_op("dlg")
def _op_dlg(emu, f, path):
    """dlg PREFIX EXPECT [MAXPAGES] [FIRST]: see dialogue()."""
    dialogue(emu, f[1], f[2], _arg(f, 3, 60), first=_arg(f, 4, 1))


@script_op("yes", "no")
def _op_yesno(emu, f, path):
    """yes / no: answer the save dialog's or a script's YES/NO (cursor to row 0/1, A)."""
    want = 0 if f[0] == "yes" else 1
    emu.frames(4)
    cur = emu.r8(emu.sym("sMenu") + 2) if False else None
    if want == 1:
        emu.tap("DOWN", 6)
    emu.tap("A", 6)
    print("%s @%d" % (f[0], emu.sync()))


def _behavior_reader(emu):
    layout = emu.r32(emu.sym("gMapHeader"))
    prim, sec, ver = emu.r32(layout + 0x10), emu.r32(layout + 0x14), emu.r8(layout + 0x18)
    nprim = 640 if ver in (1, 2) else 512          # GetNumMetatilesInPrimary, src/fieldmap.c:438
    wide = ver == 1                                 # FRLG layouts keep u32 attributes
    pa, sa = emu.r32(prim + 0x10), emu.r32(sec + 0x10)
    cache = {}

    def beh(mt):
        if mt not in cache:
            if mt < nprim:
                a = emu.r32(pa + 4 * mt) if wide else emu.r16(pa + 2 * mt)
            else:
                a = emu.r32(sa + 4 * (mt - nprim)) if wide else emu.r16(sa + 2 * (mt - nprim))
            cache[mt] = a & (0x1FF if wide else 0xFF)
        return cache[mt]
    return beh


def _mb(emu, name):
    if not hasattr(emu, "_mbs"):
        src = os.environ.get("HNS_SRC") or hns.src_dir(emu.elf)
        txt = open(os.path.join(src, "include", "constants", "metatile_behaviors.h")).read()
        body = txt[txt.index("{") + 1:txt.index("}")]
        names = [l.strip().rstrip(",").split("=")[0].strip() for l in body.splitlines()]
        names = [n for n in names if n.startswith("MB_")]
        emu._mbs = {n: i for i, n in enumerate(names)}
    return emu._mbs[name]


def map_grid(emu):
    """(width, height, collision(x, y), behavior(x, y)) of the loaded map in map coordinates
    (gBackupMapLayout, include/global.fieldmap.h:133; MAP_OFFSET 7 border tiles on each side)."""
    base = emu.sym("gBackupMapLayout")
    w, h, ptr = emu.r32(base), emu.r32(base + 4), emu.r32(base + 8)
    raw = emu.read(ptr, w * h * 2)
    cells = [int.from_bytes(raw[i:i + 2], "little") for i in range(0, len(raw), 2)]
    beh = _behavior_reader(emu)

    def coll(x, y):
        X, Y = x + 7, y + 7
        if not (0 <= X < w and 0 <= Y < h):
            return True
        return bool(cells[X + w * Y] & 0x0C00)

    def behavior(x, y):
        X, Y = x + 7, y + 7
        if not (0 <= X < w and 0 <= Y < h):
            return 0
        return beh(cells[X + w * Y] & 0x3FF)
    return w - 15, h - 14, coll, behavior


DIRS = (("UP", (0, -1)), ("DOWN", (0, 1)), ("LEFT", (-1, 0)), ("RIGHT", (1, 0)))


def bfs(w, h, coll, start, goal, blocked, ledges=None, slides=None, ice=None):
    """Shortest list of key directions from START to GOAL. LEDGES maps a tile to the direction
    a jump over it goes (MB_JUMP_*: the player lands two tiles on, whatever the tile's collision).
    SLIDES maps a tile to the direction it pushes the player (MB_SLIDE_* / MB_WALK_*): a step onto
    it carries on that way until a tile that is not one (a slide that runs into a wall is a trap)."""
    from collections import deque
    ledges = ledges or {}
    slides = slides or {}
    ice = ice or set()
    step = dict(DIRS)

    def free(t):
        return 0 <= t[0] < w and 0 <= t[1] < h and not coll(*t) and t not in blocked

    def land(t):
        seen = set()
        while t in slides:
            if t in seen:
                return None
            seen.add(t)
            dx, dy = step[slides[t]]
            nxt = (t[0] + dx, t[1] + dy)
            if not free(nxt) and ledges.get(nxt) != slides[t]:
                return None
            if ledges.get(nxt) == slides[t]:
                nxt = (nxt[0] + dx, nxt[1] + dy)
                if not free(nxt):
                    return None
            t = nxt
        return t

    prev = {start: None}
    q = deque([start])
    while q:
        c = q.popleft()
        if c == goal:
            break
        for d, (dx, dy) in DIRS:
            n = (c[0] + dx, c[1] + dy)
            if ledges.get(n) == d:
                n = (n[0] + dx, n[1] + dy)
                if coll(*n) or n in blocked or n in ledges:
                    continue
            elif n == goal:
                if coll(*n):
                    continue
            elif not free(n):
                continue
            if n != goal and n in slides:
                n = land(n)
                if n is None:
                    continue
            while n in ice and n != goal:          # ice: slide on in the same direction
                nxt = (n[0] + dx, n[1] + dy)
                if not free(nxt):
                    break
                n = nxt
            if n in prev or not (0 <= n[0] < w and 0 <= n[1] < h):
                continue
            prev[n] = (c, d)
            q.append(n)
    if goal not in prev:
        return None
    path, c = [], goal
    while prev[c]:
        c0, d = prev[c]
        path.append(d)
        c = c0
    return path[::-1]


def ice_set(emu, w, h, behavior):
    """Tiles that keep the player sliding the way they went (MB_ICE, MB_TRICK_HOUSE_PUZZLE_8_FLOOR:
    MetatileBehavior_IsIce / IsIce_2)."""
    kinds = {_mb(emu, "MB_ICE"), _mb(emu, "MB_TRICK_HOUSE_PUZZLE_8_FLOOR")}
    return {(x, y) for y in range(h) for x in range(w) if behavior(x, y) in kinds}


def slide_map(emu, w, h, behavior):
    sd = {}
    for kind in ("SLIDE", "WALK"):
        sd.update({_mb(emu, "MB_%s_EAST" % kind): "RIGHT", _mb(emu, "MB_%s_WEST" % kind): "LEFT",
                   _mb(emu, "MB_%s_NORTH" % kind): "UP", _mb(emu, "MB_%s_SOUTH" % kind): "DOWN"})
    out = {}
    for y in range(h):
        for x in range(w):
            b = behavior(x, y)
            if b in sd:
                out[(x, y)] = sd[b]
    return out


def ledge_map(emu, w, h, behavior):
    jd = {_mb(emu, "MB_JUMP_EAST"): "RIGHT", _mb(emu, "MB_JUMP_WEST"): "LEFT",
          _mb(emu, "MB_JUMP_NORTH"): "UP", _mb(emu, "MB_JUMP_SOUTH"): "DOWN"}
    out = {}
    for y in range(h):
        for x in range(w):
            b = behavior(x, y)
            if b in jd:
                out[(x, y)] = jd[b]
    return out


@script_op("walkto")
def _op_walkto(emu, f, path):
    """walkto X Y [FACE]: walk to (X, Y) along a shortest path over the live collision grid,
    re-planning around tiles that turn out blocked (objects). Stops early, without error, when a
    script takes the player over (a trainer's sight) or a warp loads another map. FACE turns the
    player at the end. Prints how it ended: walkto ... reached / taken / warp."""
    goal = (int(f[1]), int(f[2]))
    face = f[3] if len(f) > 3 else None
    blocked = set()
    (g0, n0, _, _, _), _ = emu.location()
    for it in range(400):
        (g, n, _w, _x, _y), pos = emu.location()
        if (g, n) != (g0, n0):
            print("walkto %s: warp to %d.%d %s @%d" % (goal, g, n, pos, emu.sync()))
            return
        if pos == goal:
            break
        w, h, coll, behavior = map_grid(emu)
        slides = slide_map(emu, w, h, behavior)
        for _wait in range(60):                  # let a slide in progress end first
            if pos not in slides or not emu.controllable():
                break
            emu.frames(4)
            pos = emu.location()[1]
        if pos == goal:
            break
        objs = {(o[1], o[2]) for o in objects(emu)} - {goal}
        route = bfs(w, h, coll, pos, goal, blocked | objs, ledge_map(emu, w, h, behavior), slides,
                    ice_set(emu, w, h, behavior))
        if not route:
            raise HnsError("walkto: no path from %s to %s (blocked %s)" % (pos, goal, sorted(blocked)))
        d = route[0]
        r = hns.go_step(emu, d)
        if getattr(emu, "_walk_dbg", 0) or it > 30:
            print("   walkto step %d: at %s route %s -> %s, ctl %s" % (it, pos, "".join(x[0] for x in route), r, emu.controllable()))
        if r is None:
            if not emu.controllable():
                print("walkto %s: taken at %s @%d" % (goal, emu.location()[1], emu.sync()))
                emu._walk_end = "taken"
                return
            dx, dy = {"UP": (0, -1), "DOWN": (0, 1), "LEFT": (-1, 0), "RIGHT": (1, 0)}[d]
            if (pos[0] + dx, pos[1] + dy) == goal:
                raise HnsError("walkto: the goal %s is occupied (standing at %s)" % (goal, pos))
            blocked.add((pos[0] + dx, pos[1] + dy))
            continue
        if r == "warp":
            print("walkto %s: warp at %s @%d" % (goal, emu.location(), emu.sync()))
            return
        if not emu.controllable():
            emu.frames(4)
            if not emu.controllable():
                print("walkto %s: taken at %s @%d" % (goal, emu.location()[1], emu.sync()))
                emu._walk_end = "taken"
                return
    else:
        raise HnsError("walkto: gave up")
    if face:
        emu.frames(2, face)
        emu.frames(14)
    print("walkto %s: reached @%d" % (goal, emu.sync()))


@script_op("grid")
def _op_grid(emu, f, path):
    """grid: print the collision grid of the loaded map (# blocked, P player)."""
    w, h, coll, _ = map_grid(emu)
    _, pos = emu.location()
    for y in range(h):
        print("   %2d %s" % (y, "".join("P" if (x, y) == pos else ("#" if coll(x, y) else ".") for x in range(w))))


@script_op("behaviors")
def _op_behaviors(emu, f, path):
    """behaviors: print the metatile behavior (hex, '..' for 0) and '#' for collision of every tile."""
    w, h, coll, behavior = map_grid(emu)
    for y in range(h):
        print("   %2d %s" % (y, "".join(("%02X" % behavior(x, y) if behavior(x, y) else "..") + ("#" if coll(x, y) else " ")
                                         for x in range(w))))


def objects(emu):
    """Active object events other than the player: [(localId, x, y)] in map coordinates
    (struct ObjectEvent, include/global.fieldmap.h: active bit 0 of byte 0, isPlayer bit 0 of
    byte 2, localId +8, currentCoords +0x10, 36 bytes each)."""
    base = emu.sym("gObjectEvents")
    size = emu.elf.size("gObjectEvents") // 16
    raw = emu.read(base, size * 16)
    out = []
    for i in range(16):
        b = raw[i * size:(i + 1) * size]
        if b[0] & 1 and not b[2] & 1:
            x = int.from_bytes(b[0x10:0x12], "little", signed=True) - 7
            y = int.from_bytes(b[0x12:0x14], "little", signed=True) - 7
            out.append((b[8], x, y))
    return out


@script_op("objs")
def _op_objs(emu, f, path):
    print("objs %s, player %s" % (objects(emu), emu.location()[1]))


@script_op("talkto")
def _op_talkto(emu, f, path):
    """talkto LOCALID PREFIX EXPECT [MAXPAGES]: walk next to the object with LOCALID (if not there
    already), face it, press A and walk the dialogue (see dlg)."""
    lid = int(f[1], 0)
    obj = [o for o in objects(emu) if o[0] == lid]
    if not obj:
        raise HnsError("talkto: no object %d (%s)" % (lid, objects(emu)))
    _, ox, oy = obj[0]
    _, pos = emu.location()
    adj = {(ox, oy + 1): "UP", (ox, oy - 1): "DOWN", (ox + 1, oy): "LEFT", (ox - 1, oy): "RIGHT"}
    if pos not in adj:
        w, h, coll, behavior = map_grid(emu)
        others = {(o[1], o[2]) for o in objects(emu)}
        best = None
        for t in adj:
            if coll(*t) or t in others:
                continue
            r = bfs(w, h, coll, pos, t, others, ledge_map(emu, w, h, behavior), slide_map(emu, w, h, behavior),
                    ice_set(emu, w, h, behavior))
            if r is not None and (best is None or len(r) < len(best[1])):
                best = (t, r)
        if best is None:
            raise HnsError("talkto: no free tile next to object %d at %s" % (lid, (ox, oy)))
        emu._walk_end = "reached"
        _op_walkto(emu, ["walkto", str(best[0][0]), str(best[0][1])], path)
        if emu._walk_end == "taken":
            dialogue(emu, f[2], f[3], _arg(f, 4, 60))
            return
        _, pos = emu.location()
        if pos not in adj:
            raise HnsError("talkto: walk ended at %s" % (pos,))
    emu.frames(2, adj[pos])
    emu.frames(14)
    emu.tap("A", 4)
    dialogue(emu, f[2], f[3], _arg(f, 4, 60))
