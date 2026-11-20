#!/usr/bin/env python3
"""hns.py with the r3 frontier ops (scripts/r3_frontier/r3bf.py: drive, pick, loc, ss, sl, ...), the
r2 frontier ops (scripts/r2_battle_frontier_facilities/bffops.py: saveyes, drivex), the hill/tent
walk ops (scripts/r2_hill_tents/hilltent_ops.py: walkto, grid) and the ops of the
Emerald-world leak walk (tours/r16_emerald_leak): can a player of H&S walk into a map of the
Emerald world (a map without the _hns suffix) and does it load?

Run:  emleak.py tour ROM OUT --tours tools/hebrew/emu/tours/r16_emerald_leak [--clip] [--only RE]
      with HNS_SRC = the tree the ROM was built from (map names and constants), HNS_SAVES = the
      save ladder (ladder6_postgame.sav, r6r3_islands_base.sav) and HNS_MAX_FRAMES (e.g. 20000):
      the Emerald maps these tours reach crash the game. One tour per run, one run at a time.
      Every step is a real key press; a tour may warp only to an H&S map (_hns) to start a walk.

Added here:
    where LABEL         print and log the map (name from HNS_SRC), position and callback2
                        to OUT/<tour>/where.jsonl; 'emerald' is true for a map without _HNS
    trystep DIR [TRIES] [WAIT]
                        one tile toward DIR with a real key press (hns.go_step); when blocked
                        (an object walking past) wait WAIT frames (default 30) and press again,
                        TRIES times (default 8). A warp whose map does not load (callback2 stuck,
                        or the runner stops) is logged as such with a shot, and the tour ends.
    watchload PREFIX [MAXFRAMES] [EVERY] [STEP]
                        after a script started a warp: press A on text and START on a debug
                        error screen, run until the player walks on another map ('loaded'), or
                        report 'stuck' / 'stopped' (crash)
    poisonsurvive 0|1   the New Game option SURVIVE POISON (default 1: field poison stops at 1 HP)
    setpoison HP        give every party Pokemon poison (status 1 << 3) and HP (field poison then
                        faints them: OW_POISON_DAMAGE GEN_3)
"""
import json
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(HERE, "..", ".."))                                # tools/hebrew/emu
sys.path.insert(0, os.path.join(HERE, "..", "r3_frontier"))
sys.path.insert(0, os.path.join(HERE, "..", "r2_hill_tents"))
sys.path.insert(0, os.path.join(HERE, "..", "r2_battle_frontier_facilities"))
import hns  # noqa: E402
import r3bf  # noqa: E402,F401  (hns + r2sf + r3 frontier ops)
import bffops  # noqa: E402,F401  (saveyes, drivex)
import hilltent_ops  # noqa: E402,F401  (walkto, grid)
from hns import script_op, HnsError, TourTimeout, _arg  # noqa: E402

_NAMES = {}
STATUS1_POISON = 1 << 3
MON_SIZE = 0x64                    # struct Pokemon; status +0x50, hp +0x56 (hns.BATTLE_OFF)
MON_STATUS = 0x50


def map_name(emu, g, n):
    src = hns.src_dir(emu.elf)
    if src not in _NAMES:
        _NAMES[src] = {v: k for k, v in hns.map_constants(src).items()}
    return _NAMES[src].get((g, n), "?%d.%d" % (g, n))


def where(emu, label, extra=None):
    (g, n, _, _, _), pos = emu.location()
    name = map_name(emu, g, n)
    rec = {"label": label, "map": name, "group": g, "num": n, "x": pos[0], "y": pos[1],
           "cb2": emu.cb2_name(), "emerald": not name.endswith("_HNS"), "frame": emu.sync()}
    if extra:
        rec.update(extra)
    with open(os.path.join(emu.outdir, "where.jsonl"), "a", encoding="utf-8") as fh:
        fh.write(json.dumps(rec) + "\n")
    print("where %s: %s (%d.%d) (%d,%d) cb2 %s%s @%d" % (label, name, g, n, pos[0], pos[1], rec["cb2"],
                                                       " EMERALD" if rec["emerald"] else "", rec["frame"]))
    return rec


@script_op("where")
def _op_where(emu, f, path):
    where(emu, f[1])


@script_op("trystep")
def _op_trystep(emu, f, path):
    d, tries, wait = f[1], _arg(f, 2, 8), _arg(f, 3, 30)
    before = emu.location()
    for k in range(tries):
        try:
            r = hns.go_step(emu, d)
        except TourTimeout as e:
            name = "trystep_hang_%d" % emu.sync()
            emu.shot(name)
            where(emu, "hang", {"error": str(e), "shot": name})
            raise
        if r is not None:
            break
        emu.frames(wait)
    after = emu.location()
    print("trystep %s: %s after %d press(es), %s -> %s @%d" % (d, r or "blocked", k + 1, before[1], after[1],
                                                              emu.sync()))
    if r is None:
        where(emu, "blocked_%s" % d)


# the debug build's resumable error screen (src/assertf.c): 'Press START to continue.'
ASSERT_FUNCS = ("AssertfCrashScreen", "BusyWaitForVBlank")


def _function(emu, pc):
    return emu.elf.where(pc).split("+")[0].split(":")[-1].split(" ")[0]


@script_op("watchload")
def _op_watchload(emu, f, path):
    """watchload PREFIX [MAXFRAMES] [EVERY] [STEP]: after a script started a warp (a ferry, a
    white-out), run until the player can walk on another map, looking every STEP frames (default 30)
    as a player would: A on a text page, START on the error screen of a debug build (AssertfCrashScreen,
    'Press START to continue.'; shot PREFIX_assert_N first, at most 4). Logs callback2 whenever it
    changes, the functions the CPU was found in (pc samples) and a shot PREFIX_NN every EVERY frames
    (default 240, at most 8). Ends with 'loaded' (where PREFIX), 'stuck' (no field in MAXFRAMES,
    default 6000) or 'stopped' (the runner ended: a crash, or HNS_MAX_FRAMES)."""
    prefix, maxf, every, step = f[1], _arg(f, 2, 6000), _arg(f, 3, 240), _arg(f, 4, 30)
    start = emu.location()[0][:2]
    trail, shots, waited, last, asserts = [], 0, 0, None, 0
    samples = {}
    try:
        while waited < maxf:
            cb = emu.cb2_name()
            fn = _function(emu, emu.pc())
            samples[fn] = samples.get(fn, 0) + 1
            if cb != last:
                trail.append((waited, cb))
                last = cb
            if fn in ASSERT_FUNCS:
                asserts += 1
                trail.append((waited, "assert screen %d: START" % asserts))
                if asserts <= 4:
                    emu.shot("%s_assert_%d" % (prefix, asserts))
                emu.tap("START", 10)
                waited += 13
                continue
            if emu.in_overworld() and emu.location()[0][:2] != start and emu.controllable():
                emu.shot(prefix + "_loaded")
                where(emu, prefix, {"result": "loaded", "trail": trail, "asserts": asserts})
                return
            if emu.wants_key():
                emu.tap("A", 4)
                waited += 7
            else:
                emu.frames(step)
                waited += step
            if waited // every > shots and shots < 8:
                shots += 1
                emu.shot("%s_%02d" % (prefix, shots))
        emu.shot(prefix + "_stuck")
        top = sorted(samples.items(), key=lambda kv: -kv[1])[:6]
        where(emu, prefix, {"result": "stuck", "trail": trail, "frames": waited, "asserts": asserts,
                            "pc_samples": top})
    except (HnsError, TourTimeout, OSError, BrokenPipeError) as e:
        rec = {"result": "stopped", "error": str(e)[:300], "trail": trail, "frames": waited, "asserts": asserts}
        try:                                    # the runner may still answer: map, pc and a last shot
            pc = emu.pc()
            emu.shot(prefix + "_stopped")
            where(emu, prefix, dict(rec, pc="%08X" % pc, pc_in=emu.elf.where(pc), shot=prefix + "_stopped"))
        except (HnsError, OSError, BrokenPipeError):
            with open(os.path.join(emu.outdir, "where.jsonl"), "a", encoding="utf-8") as fh:
                fh.write(json.dumps(dict(rec, label=prefix)) + "\n")
        print("watchload %s: stopped after %d frames: %s" % (prefix, waited, str(e)[:300]))
        raise


# offsetof(struct SaveBlock3, challengeSettings) + the byte of tx_Mode_PoisonSurvive (bit 1), measured
# with an offsetof()/bit-field probe compiled against include/global.h of the release tree and of
# English 2.0.6 (the same in both)
SB3_POISON_SURVIVE = (0x10 + 28, 1)


@script_op("poisonsurvive")
def _op_poisonsurvive(emu, f, path):
    """poisonsurvive 0|1: the New Game MODE option SURVIVE POISON (challengeSettings.
    tx_Mode_PoisonSurvive, default ON: src/new_game.c), so a later field-poison tick can faint the
    party (0) or leaves it at 1 HP (1)."""
    off, bit = SB3_POISON_SURVIVE
    a = emu.r32(emu.sym("gSaveBlock3Ptr")) + off
    v = emu.r8(a)
    v = (v | (1 << bit)) if int(f[1]) else (v & ~(1 << bit))
    emu.w8(a, v)
    print("poisonsurvive %s: byte %08X = %02X @%d" % (f[1], a, emu.r8(a), emu.sync()))


@script_op("setpoison")
def _op_setpoison(emu, f, path):
    hp = int(f[1])
    party = emu.sym("gPlayerParty")
    n = emu.r8(emu.sym("gPlayerPartyCount"))
    hp_off = hns.BATTLE_OFF["Pokemon.hp"]
    for i in range(n):
        base = party + MON_SIZE * i
        emu.w32(base + MON_STATUS, STATUS1_POISON)
        emu.w16(base + hp_off, hp)
    print("setpoison: %d Pokemon poisoned at %d HP @%d" % (n, hp, emu.sync()))


if __name__ == "__main__":
    sys.argv[0] = hns.__file__
    sys.exit(hns.main())
