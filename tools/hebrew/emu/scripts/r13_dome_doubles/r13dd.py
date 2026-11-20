#!/usr/bin/env python3
"""Ops for the r13 Battle Dome double-battle tours (tours/r13_dome_doubles/*.txt), on top of
r11tent.py (tstate, the r7 roster ops dometrainers / domecards / bwinr, the r2/r3 Frontier ops
drive / drivex / pick / saveyes / bwin / blose, and r11sym's FILE:sym lookups for a clip ELF
without a linker map).
Run:  r13dd.py tour ROM OUT --tours <emu>/tours/r13_dome_doubles [--clip] [--only RE]

    dstate save|load NAME   savestate OUT/_states/NAME.ss, shared by every tour of one run
                            (a later tour starts from a state an earlier one saved)
    domesync dump|load NAME the Dome tourney in the save block: domeTrainers[16] (u32 each,
                            trainerId:10 isEliminated:1 eliminatedAt:2 forfeited:3) at
                            SB2+0xD24 and domeMonIds[16][3] (u16) at SB2+0xD64 (offsets from
                            r7roster.py, measured with probe/offsets.c against both trees).
                            dump writes $DD_SYNC/NAME.json, load writes it back, so the English
                            run plays the tourney (trainers, their Pokemon, the other matches'
                            results) the Hebrew run drew.
    domeinfo                print the tourney slots, the round and the opponent
    partylog                print the player's party (species, level, hp)
    bhp4 FOE ALLY USER      in a double battle at the action menu: foes' (battlers 1, 3) hp,
                            the player's battler 2 hp and battler 0 hp (numbers, 'max' = maxHP)
    bmove0 BATTLER MOVE     put MOVE_x into move slot 0 of a player battler (gBattleMons) with
                            10 pp
    bshot NAME              snap after the battle screen is quiet
    drivemap PREFIX MAP     drivex until the player is on MAP and a message there waits for a
                            key (shot, not pressed): a point between the battle room's
                            dome_resolvewinners and the pre-battle room's static tree
    pfx PREFIX / psnap SUF  snap PREFIX_SUF (shot names per call site inside an include)
DD_SYNC (default 'sync') is the folder for domesync; DD_LANG he|en (run.sh sets it) picks dump or
load for 'dumpif'; DD_NOSYNC=1 skips every load.
"""
import json
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(HERE, "..", "r11_tents"))
sys.path.insert(0, HERE)
import r11tent  # noqa: E402,F401  (registers hns + the r2/r3/r7/r11 Frontier ops)
import hns  # noqa: E402
from hns import script_op, HnsError  # noqa: E402

DOME_TRAINERS = 0xD24
DOME_MONS = 0xD64
BM = 0x88                       # sizeof(struct BattlePokemon), hns / bffops
BM_MOVES, BM_PP, BM_HP, BM_MAXHP = 0x0C, 0x25, 0x2A, 0x2E


def _state(emu, name):
    d = os.path.join(emu.outdir, "..", "_states")
    os.makedirs(d, exist_ok=True)
    p = os.path.normpath(os.path.join(d, name + ".ss"))
    r = os.path.relpath(p)
    p = r if len(r) < len(p) else p
    if len(p) > 127:
        raise HnsError("state path longer than 127 characters: %s" % p)
    return p


@script_op("dstate")
def _op_dstate(emu, f, path):
    what, name = f[1], f[2]
    p = _state(emu, name)
    if what == "save":
        emu.send("ss %s" % p)
    elif what == "load":
        if not os.path.exists(p):
            raise HnsError("dstate load: no state %s" % p)
        emu.send("sl %s" % p)
        emu._bw_box = None
    else:
        raise HnsError("dstate save|load NAME")
    print("dstate %s %s @%d" % (what, p, emu.sync()))


def _sync_path(name):
    d = os.environ.get("DD_SYNC", "sync")
    os.makedirs(d, exist_ok=True)
    return os.path.join(d, name + ".json")


@script_op("domesync")
def _op_domesync(emu, f, path):
    what, name = f[1], f[2]
    sb2 = emu.sb2()
    p = _sync_path(name)
    if what == "dump":
        tr = [emu.r32(sb2 + DOME_TRAINERS + 4 * i) for i in range(16)]
        mons = [emu.r16(sb2 + DOME_MONS + 2 * i) for i in range(48)]
        json.dump({"trainers": tr, "mons": mons}, open(p, "w"))
        print("domesync dump %s: %s" % (p, [t & 0x3FF for t in tr]))
    elif what == "load":
        if os.environ.get("DD_NOSYNC"):
            print("domesync load %s: DD_NOSYNC set, skipped" % p)
            return
        if os.environ.get("DD_LANG") == "he" and not os.path.exists(p):
            print("domesync load %s: none (Hebrew run), skipped" % p)
            return
        d = json.load(open(p))
        for i, t in enumerate(d["trainers"]):
            emu.w32(sb2 + DOME_TRAINERS + 4 * i, t)
        for i, m in enumerate(d["mons"]):
            emu.w16(sb2 + DOME_MONS + 2 * i, m)
        print("domesync load %s: %s" % (p, [t & 0x3FF for t in d["trainers"]]))
    elif what == "dumpif":
        # dump only on the Hebrew run (the English run loads)
        if os.environ.get("DD_LANG") == "he":
            _op_domesync(emu, ["domesync", "dump", name], path)
        else:
            _op_domesync(emu, ["domesync", "load", name], path)
    else:
        raise HnsError("domesync dump|load|dumpif NAME")


@script_op("domeinfo")
def _op_domeinfo(emu, f, path):
    sb2 = emu.sb2()
    tr = [emu.r32(sb2 + DOME_TRAINERS + 4 * i) for i in range(16)]
    print("domeinfo: %s" % [(t & 0x3FF, (t >> 10) & 1, (t >> 11) & 3) for t in tr])
    print("domeinfo: opponentA = %d" % emu.r16(emu.sym("gTrainerBattleParameter") + 2))


@script_op("partylog")
def _op_partylog(emu, f, path):
    party = emu.sym("gPlayerParty")
    n = emu.r8(emu.sym("gPlayerPartyCount"))
    out = []
    for i in range(n):
        out.append((emu.r16(party + 0x64 * i + hns.BATTLE_OFF["Pokemon.hp"]),))
    print("partylog: %d mon(s), hp %s" % (n, out))


def _hpval(emu, b, v):
    bm = emu.sym("gBattleMons")
    return emu.r16(bm + BM * b + BM_MAXHP) if v == "max" else int(v, 0)


@script_op("bhp4")
def _op_bhp4(emu, f, path):
    bm = emu.sym("gBattleMons")
    foe, ally, user = f[1], f[2], f[3]
    for b, v in ((1, foe), (3, foe), (2, ally), (0, user)):
        if emu.r16(bm + BM * b + BM_HP):
            emu.w16(bm + BM * b + BM_HP, _hpval(emu, b, v))
    print("bhp4: %s" % [emu.r16(bm + BM * b + BM_HP) for b in range(4)])


@script_op("bmove0")
def _op_bmove0(emu, f, path):
    bm = emu.sym("gBattleMons")
    b = int(f[1])
    emu.w16(bm + BM * b + BM_MOVES, emu.const(f[2]))
    emu.w8(bm + BM * b + BM_PP, 10)
    print("bmove0 %d %s" % (b, f[2]))


@script_op("bshot")
def _op_bshot(emu, f, path):
    emu.wait_quiet(600)
    emu.frames(2)
    emu.snap(f[1]) if hasattr(emu, "snap") else emu.shot(f[1])
    emu.shots = getattr(emu, "shots", []) + [f[1]]
    if getattr(emu, "clip", None):
        try:
            emu.clip.poll(f[1])
        except Exception:
            pass


@script_op("drivemap")
def _op_drivemap(emu, f, path):
    """drivemap PREFIX MAP_NAME [MAXPAGES] [MAXFRAMES]: drivex (a shot per new text page, then A)
    until the player is on MAP_NAME and a message there waits for a key: that page is shot and
    left on screen (not pressed), so an op can run between two script lines (domesync after the
    battle room resolved the round and before the pre-battle room draws the static tree)."""
    import r3bf
    prefix, mapname = f[1], f[2]
    maxpages = hns._arg(f, 3, 60)
    maxframes = hns._arg(f, 4, 9000)
    g, n = hns.map_lookup(emu.elf, mapname)
    ow = emu.sym("CB2_Overworld")
    bcb2 = emu.sym("BattleMainCB2")
    k, idle, prev = 0, 0, "idle"
    last_box = hns.message_box(emu) if emu.cb2() in (ow, bcb2) else None

    def shoot():
        nonlocal k
        k += 1
        r3bf._shot(emu, "%s_%02d" % (prefix, k))

    while True:
        if idle >= maxframes:
            raise hns.TourTimeout("drivemap %s: stuck %d frames after %d shot(s) (callback2 %s)"
                                  % (prefix, idle, k, emu.cb2_name()))
        if k >= maxpages:
            raise HnsError("drivemap %s: %d shots and not on %s" % (prefix, k, mapname))
        cb = emu.cb2()
        if cb == ow and emu.tasks_named(emu.MENU_TASKS):
            emu.wait_menu_ready()
            shoot()
            raise HnsError("drivemap %s: unexpected menu" % prefix)
        st = emu.text_state()
        if st == "busy" or emu.fading():
            prev = "busy" if st == "busy" else prev
            emu.frames(2)
            idle += 2
            continue
        if emu.wants_key():
            emu.wait_quiet(600)
            box = hns.message_box(emu) if cb in (ow, bcb2) else None
            if box is None or box != last_box:
                shoot()
            last_box = box
            (lg, ln, _, _, _), _ = emu.location()
            if (lg, ln) == (g, n) and cb == ow:
                print("drivemap %s: %d shot(s), on %s @%d" % (prefix, k, mapname, emu.sync()))
                return
            emu.tap("A", 0)
            emu.wait_until(lambda: not emu.wants_key(), 90, "the text to take the key", step=1)
            idle, prev = 0, "idle"
            continue
        if prev == "busy":
            emu.frames(4)
            box = hns.message_box(emu) if cb in (ow, bcb2) else None
            if box is not None and box != last_box:
                shoot()
                last_box = box
        prev = st
        emu.frames(2)
        idle += 2


@script_op("pfx")
def _op_pfx(emu, f, path):
    """pfx PREFIX: the prefix psnap uses (so an include can name its shots per call site)."""
    emu.ddpfx = f[1]


@script_op("psnap")
def _op_psnap(emu, f, path):
    """psnap SUFFIX: snap PREFIX_SUFFIX (PREFIX from pfx)."""
    name = "%s_%s" % (getattr(emu, "ddpfx", "dd"), f[1])
    print("snap %s @%d" % (name, emu.sync()))
    emu.snap(name)


if __name__ == "__main__":
    sys.argv[0] = hns.__file__
    sys.exit(hns.main())
