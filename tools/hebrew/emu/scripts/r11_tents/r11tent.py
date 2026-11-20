#!/usr/bin/env python3
"""Ops for the r11 Battle Tent roster tours (tours/r11_tents/*.txt), on top of r7roster.py
(bfpops / bffops / r3bf: drive, drivex, pick, saveyes, bwinr, bpalace, oppname ...).
Run:  r11tent.py tour ROM OUT --tours <emu>/tours/r11_tents [--clip] [--only RE]

    tstate save|load NAME   savestate OUTDIR/NAME.ss (written as a path relative to the current
                            directory when that is shorter: hnsrun reads at most 127 characters)
    tentpin ID              pin TRAINER_BATTLE_PARAM.opponentA (gTrainerBattleParameter+2) to ID
                            (the r7 roster method); the tent's own pick (SetNextBattleTentOpponent,
                            src/battle_tower.c:2065, or GenerateOpponentMons, src/battle_tent.c:362)
                            is overwritten before the next frame, so the battle, its intro, send-out
                            and defeat lines use trainer ID of gFacilityTrainers (the tent's table,
                            SetTentPtrsGetLevel, src/battle_tower.c:2032)
    tentlog PREFIX          after the battle started: one JSON line in OUTDIR/roster.jsonl with the
                            pinned id, gFacilityTrainers and the trainer's facility class and name
                            bytes as the ROM holds them (struct BattleFrontierTrainer: facilityClass
                            at 0, trainerName[8] at 4, include/battle_frontier.h:7)
    tentwin PREFIX          win the battle: bpalace when the battle is a Palace one (Verdanturf),
                            else bwinr (r7roster.py)
"""
import json
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(HERE, "..", "r7_roster"))
sys.path.insert(0, HERE)
import r7roster  # noqa: E402,F401  (registers hns + the r2/r3/r7 Frontier ops)
import hns  # noqa: E402
import r11sym  # noqa: E402,F401  (FILE:sym lookups without a linker map)
from hns import script_op, HnsError  # noqa: E402

BFT_SIZE = 0x34          # sizeof(struct BattleFrontierTrainer): 4 + 8 + 3 * 12 + 4
BATTLE_TYPE_PALACE = 1 << 17   # include/constants/battle.h:96, both trees


def _state(emu, name):
    p = os.path.join(emu.outdir, name + ".ss")
    r = os.path.relpath(p)
    p = r if len(r) < len(p) else p
    if len(p) > 127:
        raise HnsError("state path longer than 127 characters: %s" % p)
    return p


@script_op("tstate")
def _op_tstate(emu, f, path):
    what, name = f[1], f[2]
    p = _state(emu, name)
    if what == "save":
        emu.send("ss %s" % p)
    elif what == "load":
        emu.send("sl %s" % p)
        emu._bw_box = None
    else:
        raise HnsError("tstate save|load NAME")
    print("tstate %s %s @%d" % (what, p, emu.sync()))


@script_op("tentpin")
def _op_tentpin(emu, f, path):
    tid = int(f[1], 0)
    addr = emu.sym("gTrainerBattleParameter") + 2
    emu.send("pin %x %02X%02X" % (addr, tid & 0xFF, tid >> 8))
    emu.tent_id = tid
    print("tentpin %d @%d" % (tid, emu.sync()))


@script_op("tentlog")
def _op_tentlog(emu, f, path):
    tid = emu.r16(emu.sym("gTrainerBattleParameter") + 2)
    ft = emu.r32(emu.sym("gFacilityTrainers"))
    rec = {"shot": f[1], "pinned": getattr(emu, "tent_id", None), "opponentA": tid,
           "gFacilityTrainers": "%08x" % ft}
    if ft and tid < 30:
        base = ft + BFT_SIZE * tid
        rec["facilityClass"] = emu.r8(base)
        rec["name_bytes"] = emu.read(base + 4, 8).hex()
    for sym in ("gSlateportBattleTentTrainers", "gVerdanturfBattleTentTrainers", "gFallarborBattleTentTrainers"):
        if ft == emu.sym(sym):
            rec["table"] = sym
    with open(os.path.join(emu.outdir, "roster.jsonl"), "a") as fh:
        fh.write(json.dumps(rec) + "\n")
    print("tentlog %s" % rec)


@script_op("tentwin")
def _op_tentwin(emu, f, path):
    prefix = f[1]
    flags = emu.r32(emu.sym("gBattleTypeFlags"))
    if flags & BATTLE_TYPE_PALACE:
        hns.SCRIPT_OPS["bpalace"](emu, ["bpalace", prefix, "20"], path)
    else:
        hns.SCRIPT_OPS["bwinr"](emu, ["bwinr", prefix], path)


if __name__ == "__main__":
    sys.argv[0] = hns.__file__
    sys.exit(hns.main())
