#!/usr/bin/env python3
"""hns.py plus the r6 league ops (r6league.py: r5leg bwin / scene / approach / ss / sl ...) and the
ops of the r6 field-trainer tours (tours/r6_trainers/*.txt).

    tbase                   set the trainer flag of every field trainer in the list
                            (trainerlist.py over HNS_SRC), so no other trainer spots the player
                            while one is tested; then savestate OUTDIR/tbase.ss
    trainer MAP LOCAL [OPT...]
                            one field trainer, from the tbase state (MAP is the data/maps folder,
                            LOCAL the object's local id):
                              - skipped (logged) when the object's hide flag is set;
                              - clear its trainer flag, warp next to it on the side it faces
                                (walk: 2-3 tiles out along its sight line), wait for the '!';
                                if it does not see the player, face it and press A;
                              - PREFIX_f_NNN: the field scene up to the battle (walk: a shot every
                                8 frames during the '!' and the walk-up, repeats dropped);
                              - PREFIX_b_tTT_MM: the battle (each turn the foes at 1 HP, the
                                player's first move Ice Shard; the SHIFT YES/NO prompt is shot
                                (PREFIX_b_tTT_prompt) and answered NO);
                              - PREFIX_a_NNN: the field after the battle (a YES/NO such as the
                                PokeGear registration is shot and answered YES);
                              - PREFIX_t_NNN: talk to the trainer again (its after-battle line).
                            OPT: walk; rematch (after that, write trainerRematches[tableId] = 1
                            and talk again: PREFIX_r_NNN field, PREFIX_rb_ battle, PREFIX_ra_ after,
                            PREFIX_rt_ talk); notenough (instead of the battle: every party
                            Pokemon but slot 0 at 0 HP, talk: PREFIX_n_NNN, the double battle
                            refusal); nobattle (stop after the field intro).
                            Writes one JSON line per trainer to OUTDIR/trainers.jsonl.
Run:  r6trainers.py tour ROM OUT --tours <emu>/tours/r6_trainers [--clip] [--only RE]
"""
import json
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(HERE, "..", "r6_league"))
sys.path.insert(0, HERE)
import r6league  # noqa: E402,F401  (registers the r5/r6 ops on top of hns.py)
import hns  # noqa: E402
import rc  # noqa: E402
import hilltent_ops  # noqa: E402
import trainerlist  # noqa: E402
from hns import script_op, HnsError  # noqa: E402

DIRV = {"UP": (0, -1), "DOWN": (0, 1), "LEFT": (-1, 0), "RIGHT": (1, 0)}
OPP = {"UP": "DOWN", "DOWN": "UP", "LEFT": "RIGHT", "RIGHT": "LEFT"}
SB1_REMATCHES = 0x10E8
TRAINER_FLAGS_START = 0x500


def rows(emu):
    if not hasattr(emu, "_trows"):
        src = os.environ.get("HNS_SRC") or hns.src_dir(emu.elf)
        emu._trows = trainerlist.build(src)
    return emu._trows


def facing(move):
    """The direction an object of this movement type faces when the map loads."""
    m = move.replace("MOVEMENT_TYPE_", "")
    for pre in ("FACE_", "WALK_SEQUENCE_", "WALK_", "WANDER_", "LOOK_"):
        if m.startswith(pre):
            m = m[len(pre):]
            break
    w = m.split("_")[0]
    return w if w in DIRV else "DOWN"


def tflag(emu, trainer):
    return TRAINER_FLAGS_START + emu.const(trainer)


def obj_live(emu, local):
    """(x, y, facing) of the object with this local id, or None."""
    base = emu.sym("gObjectEvents")
    size = emu.elf.size("gObjectEvents") // 16
    raw = emu.read(base, size * 16)
    for i in range(16):
        b = raw[i * size:(i + 1) * size]
        if b[0] & 1 and not b[2] & 1 and b[8] == local:
            x = int.from_bytes(b[0x10:0x12], "little", signed=True) - 7
            y = int.from_bytes(b[0x12:0x14], "little", signed=True) - 7
            d = {1: "DOWN", 2: "UP", 3: "LEFT", 4: "RIGHT"}.get(b[0x18] & 0xF, "DOWN")
            return x, y, d
    return None


def grid_cell(emu):
    """cell(x, y) -> (collision, elevation) of the loaded map (gBackupMapLayout, MAP_OFFSET 7)."""
    base = emu.sym("gBackupMapLayout")
    w, h, ptr = emu.r32(base), emu.r32(base + 4), emu.r32(base + 8)
    raw = emu.read(ptr, w * h * 2)

    def cell(x, y):
        X, Y = x + 7, y + 7
        if not (0 <= X < w and 0 <= Y < h):
            return 3, 15
        v = int.from_bytes(raw[2 * (X + w * Y):2 * (X + w * Y) + 2], "little")
        return (v >> 10) & 3, v >> 12
    return cell


def talk_tile(emu, ox, oy, od):
    """The tile next to (ox, oy) to talk from: the one it faces when that tile is walkable at the
    object's elevation, else the first other side that is (a fisherman faces the water)."""
    cell = grid_cell(emu)
    _, oe = cell(ox, oy)
    others = {(o[1], o[2]) for o in hilltent_ops.objects(emu)}
    order = [od] + [d for d in ("DOWN", "UP", "LEFT", "RIGHT") if d != od]
    for d in order:
        dx, dy = DIRV[d]
        t = (ox + dx, oy + dy)
        c, e = cell(*t)
        if c == 0 and (e == oe or e in (0, 15) or oe in (0, 15)) and t not in others:
            return t
    dx, dy = DIRV[od]
    return ox + dx, oy + dy


def fast_warp(emu, mapc, x, y):
    """hns warp without waiting for control: returns as soon as callback2 is CB2_Overworld."""
    g, n = hns.map_lookup(emu.elf, mapc)
    sb1 = emu.sb1()
    pos = sb1 + hns.OFF["SB1.pos"]
    loc = sb1 + hns.OFF["SB1.location"]
    emu.w16(pos, x)
    emu.w16(pos + 2, y)
    emu.w8(loc + 0, g)
    emu.w8(loc + 1, n)
    emu.w8(loc + 2, 0xFF)
    emu.w16(loc + 4, x)
    emu.w16(loc + 6, y)
    emu.w32(emu.CB2, emu.sym("CB2_LoadMap"))
    if not emu.wait32(emu.CB2, emu.sym("CB2_Overworld"), 600):
        raise HnsError("warp %s: no CB2_Overworld" % mapc)


def wait_spot_or_free(emu, maxf=240):
    """After a warp: 'free' when the player has control for 16 frames, 'taken' when a script
    (a trainer that saw the player) runs after the fade-in."""
    good, t = 0, 0
    while t < maxf:
        if emu.controllable():
            good += 2
            if good >= 16:
                return "free"
        else:
            good = 0
            if not emu.fading() and emu.r8(emu.sym("sGlobalScriptContextStatus")) != 2:
                return "taken"
        emu.frames(2)
        t += 2
    return "free" if emu.controllable() else "taken"


def face_and_talk(emu, local):
    """Face the object LOCAL (warping next to it when not adjacent) and press A."""
    o = obj_live(emu, local)
    if o is None:
        raise HnsError("no object %d" % local)
    ox, oy, _ = o
    _, pos = emu.location()
    adj = {(ox, oy + 1): "UP", (ox, oy - 1): "DOWN", (ox + 1, oy): "LEFT", (ox - 1, oy): "RIGHT"}
    if pos not in adj:
        hns.SCRIPT_OPS["approach"](emu, ["approach", str(local)], None)
        _, pos = emu.location()
    emu.frames(2, adj[pos])
    emu.frames(14)
    emu.tap("A", 4)


def opponent(emu):
    p = emu.sym("gTrainerBattleParameter")
    b = emu.read(p, 20)
    return int.from_bytes(b[2:4], "little"), int.from_bytes(b[17:19], "little")


def scene(emu, prefix, every=0, maxf=12000):
    hns.SCRIPT_OPS["scene"](emu, ["scene", prefix, str(maxf), str(every)], None)


def walkup(emu, prefix, every, maxf=600):
    """One shot every EVERY frames (repeats dropped) from the warp until the first text box
    starts printing or a battle starts: the trainer's '!' and its walk to the player."""
    last, k, t = None, 0, 0
    bcb2 = emu.sym("BattleMainCB2")
    while t < maxf:
        if emu.cb2() == bcb2 or emu.text_state() != "idle" or emu.controllable():
            break
        emu.frames(every)
        t += every
        if emu.fading():
            continue
        k += 1
        p = rc._shot(emu, "%s_%02d" % (prefix, k))
        data, same = rc._same_as(p, last)
        if same:
            os.remove(p)
            emu.shots = emu.shots[:-1]
            k -= 1
        last = data


def tbwin(emu, prefix, maxturns=30, notes=None):
    """bffops bwin with a shot of each battle-script YES/NO prompt before it is answered NO, and
    Shadow Sneak instead of Ice Shard on odd turns after turn 5 (Wonder Guard, Ice immunity)."""
    bcb2 = emu.sym("BattleMainCB2")
    bm = emu.sym("gBattleMons")
    ice = emu.const("MOVE_ICE_SHARD")
    sneak = emu.const("MOVE_SHADOW_SNEAK")
    for turn in range(maxturns):
        if emu.cb2() != bcb2 and emu.task_active("Task_WeatherMain"):
            break
        n, end = hns.battle_walk(emu, "%s_t%02d" % (prefix, turn), (), 60, 6000,
                                 stop_tasks=("Task_WeatherMain",))
        print("  tbwin turn %d: %d page(s), %s" % (turn, n, end))
        if end.startswith("task:Task_WeatherMain") or end == "free":
            break
        if end.startswith("input:HandleInputChooseAction"):
            b = 2 if end.endswith("#2") else 0
            for bb in ((1, 3) if emu.r8(emu.sym("gBattlersCount")) > 2 else (1,)):
                if emu.r16(bm + 0x88 * bb + 0x2A):
                    emu.w16(bm + 0x88 * bb + 0x2A, 1)
            emu.w16(bm + 0x88 * b + 0x2A, emu.r16(bm + 0x88 * b + 0x2E))
            emu.w16(bm + 0x88 * b + 0x0C, sneak if (turn > 5 and turn % 2) else ice)
            if emu.r8(bm + 0x88 * b + 0x25) == 0:
                emu.w8(bm + 0x88 * b + 0x25, 10)
            hns.wait_battle_input(emu, "HandleInputChooseAction", battler=b)
            hns.battle_cursor(emu, "gActionSelectionCursor", 0, battler=b)
            emu.tap("A", 4)
            hns.wait_battle_input(emu, "HandleInputChooseMove", battler=b)
            hns.battle_cursor(emu, "gMoveSelectionCursor", 0, battler=b)
            emu.tap("A", 4)
        elif end.startswith("input:"):
            if "YesNo" in end or "Yes" in end:
                emu.wait_quiet(300)
                emu.frames(2)
                rc._shot(emu, "%s_t%02d_prompt" % (prefix, turn))
                emu.tap("B", 4)
            else:
                emu.tap("A", 4)
        elif end.startswith("task:"):
            raise HnsError("tbwin %s: stopped at %s" % (prefix, end))
        elif end.startswith("prompt:"):
            emu.wait_quiet(300)
            emu.frames(2)
            rc._shot(emu, "%s_t%02d_prompt" % (prefix, turn))
            if notes is not None:
                notes.setdefault("prompts", []).append("%s_t%02d_prompt" % (prefix, turn))
            emu.tap("B", 4)
        else:
            emu.tap("A", 4)
    else:
        raise hns.TourTimeout("tbwin %s: still in battle after %d turns" % (prefix, maxturns))


def after_battle(emu, prefix):
    """The field after a battle: scene until free; a YES/NO or multichoice is shot by scene and
    answered with A (YES), then the scene goes on."""
    for k in range(4):
        scene(emu, "%s%d" % (prefix, k) if k else prefix)
        if emu.controllable():
            return
        if emu.cb2() == emu.sym("BattleMainCB2"):
            return
        emu.tap("A", 4)
        emu.frames(10)
    hns.SCRIPT_OPS["closeall"](emu, ["closeall"], None)


def prefix_of(r):
    t = r["trainer"].replace("TRAINER_", "").replace("_HNS", "").lower()
    return "%s_%d" % (t, r["local"])


def state_path(emu):
    """OUTDIR/tbase.ss, relative to the current directory when that is shorter: hnsrun reads at
    most 127 characters of a path (hnsrun.c:201)."""
    p = os.path.join(emu.outdir, "tbase.ss")
    r = os.path.relpath(p)
    p = r if len(r) < len(p) else p
    if len(p) > 127:
        raise HnsError("state path longer than 127 characters: %s" % p)
    return p


@script_op("tbase")
def _op_tbase(emu, f, path):
    n = 0
    for r in rows(emu):
        try:
            emu.set_flag(tflag(emu, r["trainer"]), True)
            n += 1
        except Exception as e:  # noqa: BLE001
            print("tbase: %s: %s" % (r["trainer"], e))
    emu.send("ss %s" % state_path(emu))
    print("tbase: %d trainer flags set, state saved @%d" % (n, emu.sync()))


@script_op("trainer")
def _op_trainer(emu, f, path):
    mapdir, local = f[1], int(f[2])
    opts = set(f[3:])
    r = [x for x in rows(emu) if x["map"] == mapdir and x["local"] == local]
    if not r:
        raise HnsError("trainer: no field trainer %s %d" % (mapdir, local))
    r = r[0]
    pre = prefix_of(r)
    rec = dict(map=mapdir, local=local, trainer=r["trainer"], cls=r["class"], name=r["name"],
               gender=r["gender"], kind=r["kind"], opts=sorted(opts), prefix=pre, status="?")
    emu.send("sl %s" % state_path(emu))
    emu.sync()
    emu._bw_box = None
    shots0 = len(getattr(emu, "shots", []))
    try:
        _trainer(emu, r, pre, opts, rec)
        rec["status"] = rec.get("status") if rec.get("status") not in ("?", None) else "OK"
    except (HnsError, hns.TourTimeout) as e:
        rec["status"] = "FAIL"
        rec["error"] = str(e).splitlines()[0][:300]
        try:
            rc._shot(emu, pre + "_fail")
        except HnsError:
            pass
        print("trainer %s FAIL: %s" % (pre, rec["error"]))
    rec["shots"] = getattr(emu, "shots", [])[shots0:]
    with open(os.path.join(emu.outdir, "trainers.jsonl"), "a", encoding="utf-8") as fh:
        fh.write(json.dumps(rec, ensure_ascii=False) + "\n")
    print("trainer %s %s: %d shots @%d" % (pre, rec["status"], len(rec["shots"]), emu.sync()))


def _trainer(emu, r, pre, opts, rec):
    if r["flag"] not in ("0", 0) and emu.get_flag(emu.const(r["flag"])):
        rec["status"] = "HIDDEN"
        rec["error"] = "%s is set in this save" % r["flag"]
        return
    emu.set_flag(tflag(emu, r["trainer"]), False)
    d = facing(r["move"])
    dx, dy = DIRV[d]
    dist = 1
    if "walk" in opts:
        dist = max(1, min(r["sight"], 3))
    tx, ty = r["x"] + dx * dist, r["y"] + dy * dist
    fast_warp(emu, r["mapc"], tx, ty)
    if "notenough" in opts:
        party = emu.sym("gPlayerParty")
        for s in range(1, emu.r8(emu.sym("gPlayerPartyCount"))):
            emu.w16(party + 0x64 * s + hns.BATTLE_OFF["Pokemon.hp"], 0)
    every = 8 if "walk" in opts else 0
    how = wait_spot_or_free(emu)
    rec["start"] = how
    if how == "free":
        # not seen (a turning / walking trainer, a blocked sight line): warp onto the tile next to
        # its live position on the side it faces now, then face it and talk
        o = obj_live(emu, r["local"])
        if o is None:
            raise HnsError("object %d is not on the map" % r["local"])
        ox, oy, od = o
        tx, ty = talk_tile(emu, ox, oy, od)
        _, pos = emu.location()
        if (pos[0], pos[1]) != (tx, ty):
            fast_warp(emu, r["mapc"], tx, ty)
            how = wait_spot_or_free(emu)
            rec["start"] = "retry-" + how
        if how == "free":
            face_and_talk(emu, r["local"])
            rec["start"] += "+talk"
    if every:
        walkup(emu, pre + "_w", every)
    scene(emu, pre + ("_n" if "notenough" in opts else "_f"))
    if emu.cb2() != emu.sym("BattleMainCB2"):
        if "notenough" in opts or "nobattle" in opts:
            hns.SCRIPT_OPS["closeall"](emu, ["closeall"], None)
            return
        raise HnsError("no battle after the field intro (callback2 %s)" % emu.cb2_name())
    a, b = opponent(emu)
    rec["opponent"] = [a, b]
    if a != emu.const(r["trainer"]):
        rec["status"] = "OTHER"
        rec["error"] = "battle against trainer %d, expected %s" % (a, r["trainer"])
    tbwin(emu, pre + "_b", notes=rec)
    after_battle(emu, pre + "_a")
    if emu.cb2() == emu.sym("BattleMainCB2"):
        raise HnsError("a second battle started after the first")
    face_and_talk(emu, r["local"])
    after_battle(emu, pre + "_t")
    if "rematch" in opts:
        tid = emu.const(r["trainer"])
        tab = emu.sym("gRematchTable")
        nrow = emu.elf.size("gRematchTable") // 16
        idx = None
        for i in range(nrow):
            if emu.r16(tab + 16 * i) == tid:
                idx = i
                break
        if idx is None:
            raise HnsError("rematch: %s is not in gRematchTable" % r["trainer"])
        emu.w8(emu.sb1() + SB1_REMATCHES + idx, 1)
        rec["rematch_idx"] = idx
        face_and_talk(emu, r["local"])
        scene(emu, pre + "_r")
        if emu.cb2() != emu.sym("BattleMainCB2"):
            raise HnsError("rematch: no battle")
        rec["rematch_opponent"] = list(opponent(emu))
        tbwin(emu, pre + "_rb", notes=rec)
        after_battle(emu, pre + "_ra")
        face_and_talk(emu, r["local"])
        after_battle(emu, pre + "_rt")


if __name__ == "__main__":
    sys.argv[0] = hns.__file__
    sys.exit(hns.main())
