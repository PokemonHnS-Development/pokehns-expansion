#!/usr/bin/env python3
"""Round-16 Trainer Hill runs on any ROM: the r7 steps (scripts/r7_hill: Variety, Unique, Expert) and
the r2 Normal-mode steps (scripts/r2_hill_tents: h00..h07), chained by savestates per ROM.

    hill16.py run ROM SCRIPT OUTROOT [--from STATE | --save SAV] [--to STATE] [--clip] [--name NAME]

ROM      the ROM under test; its .elf must sit next to it
SCRIPT   one step (a .txt of scripts/r7_hill or scripts/r2_hill_tents)
OUTROOT  shots go to OUTROOT/NAME/ (NAME = the script's basename), savestates to OUTROOT/_states/
--from   boot the battery saved with the state, then load the state (a state of the same ROM)
--to     write OUTROOT/_states/STATE.ss and .sav when the step ends without an error
--clip   install the clip report (an RTL_CLIP_REPORT build only)

HNS_SRC must be the tree the ROM was built from. With HNS_STRCOV set and a string-report build the
hook logs the strings per shot. HNS_MAX_FRAMES caps the frames of one step. chain.sh runs the steps
in order.

Ops: everything of r7ht.py (hillstate, hilltimer, hillbest, walkto2, walkdbg), the r2 hill ops
(hilltent_ops.py: walkto, talkto, dlg, battle2, ...) and the r3 frontier ops (r3bf.py), with one
change: battle2 is replaced by a bounded version. A move the game refuses (Torment, Disable, no PP)
sends the player back to the move menu; the r2 op then chose the same move forever and wrote a shot
per try. Here a refused move moves the cursor to the next slot and refills the PP of the player's
battlers, a turn may take at most 40 segments, and the battle at most MAX turns (default 20).
"""
import argparse
import os
import shutil
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
SCRIPTS = os.path.dirname(HERE)
sys.path.insert(0, os.path.dirname(SCRIPTS))                      # tools/hebrew/emu
sys.path.insert(0, os.path.join(SCRIPTS, "r7_hill"))
sys.path.insert(0, os.path.join(SCRIPTS, "r2_hill_tents"))
sys.path.insert(0, os.path.join(SCRIPTS, "r3_frontier"))
sys.path.insert(0, os.path.join(SCRIPTS, "r11_tents"))
import hns  # noqa: E402
import r11sym  # noqa: E402,F401  (FILE:sym lookups for a clip ELF without a linker map)
import r3bf  # noqa: E402,F401  (hns + r2sf + r3bf ops)
import hilltent_ops as ho  # noqa: E402
import r7ht  # noqa: E402,F401  (hillstate, hilltimer, hillbest, walkto2, walkdbg)
from hns import script_op, HnsError, _arg  # noqa: E402

BM_SIZE = ho.BM_SIZE
BM_HP = ho.BM_HP
BM_MOVES = 0x0C
BM_PP = 0x25                 # struct BattlePokemon pp[4] (scripts/r13_dome_doubles/r13dd.py)
MAX_SEGS = 40


def _refill_pp(emu):
    base = emu.sym("gBattleMons")
    for b, sp, cur in ho.battlers(emu):
        if b & 1 or not sp:
            continue
        for k in range(4):
            emu.w8(base + BM_SIZE * b + BM_PP + k, 10)


@script_op("battle2")
def _op_battle2(emu, f, path):
    """battle2 PREFIX [MAX] [ko|keep]: hilltent_ops battle2 with a refused move handled and every
    loop bounded (see the module docstring)."""
    prefix = f[1]
    maxturns = _arg(f, 2, 20)
    mode = f[3] if len(f) > 3 else "ko"
    turn, start_hp, presses, seg, total = 0, None, 0, 0, 0
    slot_try = 0
    while True:
        seg += 1
        total += 1
        if seg > MAX_SEGS:
            raise HnsError("battle2 %s: turn %d took more than %d segments" % (prefix, turn, MAX_SEGS))
        n, end = hns.battle_walk(emu, "%s_t%02d_%02d" % (prefix, turn, seg), (), 80,
                                 stop_tasks=("Task_HandleMultichoiceInput", "Task_HandleYesNoInput"))
        print("  battle2 %s seg %d: %d page(s), %s" % (prefix, seg, n, end))
        if end == "free" or (not hns.in_battle(emu) and ("Multichoice" in end or "YesNo" in end)):
            print("battle2 %s: over after %d turn(s) @%d" % (prefix, turn, emu.sync()))
            return
        if end == "maxpages":
            continue
        if start_hp is None and hns.in_battle(emu):
            start_hp = {b: hp for b, _, hp in ho.battlers(emu)}
        if end.startswith("input:"):
            func = end[6:].split("#")[0]
            b = 2 if end.endswith("#2") else 0
            if func == "HandleInputChooseAction":
                if b == 0:
                    turn += 1
                    seg = 0
                    slot_try = 0
                    if turn > maxturns:
                        raise HnsError("battle2 %s: still going after %d turns" % (prefix, maxturns))
                    base = emu.sym("gBattleMons")
                    for bb, sp, cur in ho.battlers(emu):
                        if not bb & 1 and cur:
                            mx = emu.r16(base + BM_SIZE * bb + BM_HP + 4)
                            if mx >= cur:
                                emu.w16(base + BM_SIZE * bb + BM_HP, mx)
                    if mode == "ko":
                        ho.set_hp(emu, "enemy", 1)
                    elif mode == "keep":
                        for bb, sp, cur in ho.battlers(emu):
                            if bb & 1 and cur:
                                emu.w16(base + BM_SIZE * bb + BM_HP, start_hp.get(bb, cur))
                    print("  battle2 turn %d: %s" % (turn, ho.battlers(emu)))
                hns.battle_cursor(emu, "gActionSelectionCursor", 0, battler=b)
                emu.tap("A", 4)
            elif func == "HandleInputChooseMove":
                base_slot = (turn - 1) % 2 if mode == "ko" else 0
                if slot_try:
                    _refill_pp(emu)
                hns.battle_cursor(emu, "gMoveSelectionCursor", (base_slot + slot_try) % 4, battler=b)
                slot_try += 1
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
                ho._shot(emu, "%s_t%02d_party" % (prefix, turn))
                emu.tap("RIGHT", 6)
                emu.wait_quiet(300)
                for _ in range(presses - 1):
                    emu.tap("DOWN", 6)
                    emu.wait_quiet(300)
                emu.tap("A", 20)
                emu.wait_quiet(300)
            elif "Task_HandleSelectionMenuInput" in end:
                ho._shot(emu, "%s_t%02d_partymenu" % (prefix, turn))
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


def main():
    ap = argparse.ArgumentParser()
    sub = ap.add_subparsers(dest="cmd", required=True)
    p = sub.add_parser("run")
    p.add_argument("rom")
    p.add_argument("script")
    p.add_argument("outroot")
    p.add_argument("--from", dest="frm")
    p.add_argument("--save")
    p.add_argument("--to")
    p.add_argument("--clip", action="store_true")
    p.add_argument("--name")
    a = ap.parse_args()
    if not os.environ.get("HNS_SRC"):
        raise SystemExit("set HNS_SRC to the tree the ROM was built from")
    rom = os.path.abspath(a.rom)
    root = os.path.abspath(a.outroot)
    name = a.name or os.path.splitext(os.path.basename(a.script))[0]
    outdir = os.path.join(root, name)
    os.makedirs(outdir, exist_ok=True)
    for old in os.listdir(outdir):
        if old.endswith(".png"):
            os.remove(os.path.join(outdir, old))
    states = os.path.join(root, "_states")
    os.makedirs(states, exist_ok=True)
    cur = os.path.join(outdir, "cur.sav")
    if a.frm:
        shutil.copyfile(os.path.join(states, a.frm + ".sav"), cur)
    elif a.save:
        shutil.copyfile(a.save, cur)
    elif os.path.exists(cur):
        os.remove(cur)
    elf = hns.Elf(os.path.splitext(rom)[0] + ".elf")
    emu = hns.Emu(rom, elf, outdir, cur)
    rc = 1
    try:
        if a.frm:
            emu.frames(30)
            emu.send("sl %s" % os.path.join(states, a.frm + ".ss"))
            emu._bw_box = None
            emu.sync()
            emu.frames(2)
        if a.clip:
            hns.clip_hook(emu, outdir)
        emu.run_script(os.path.abspath(a.script))
        if a.to:
            emu.send("ss %s" % os.path.join(states, a.to + ".ss"))
            emu.sync()
        rc = 0
    except hns.HnsError as e:
        print("ERROR: %s" % e)
        try:
            print("  callback2 %s, tasks %s, loc %s" % (emu.cb2_name(), [t[2] for t in emu.tasks()], emu.location()))
            emu.shot("_error")
        except Exception:
            pass
    finally:
        code = emu.close()
        with open(os.path.join(outdir, "run.log"), "w") as fh:
            fh.write("\n".join(emu.log) + "\n")
    if rc == 0 and a.to:
        shutil.copyfile(cur, os.path.join(states, a.to + ".sav"))
    clip = getattr(emu, "clip", None)
    if clip:
        print("clip total %d, lost %d" % (clip.total(), clip.lost))
    print("exit %d (runner %s)" % (rc, code))
    return rc


if __name__ == "__main__":
    sys.exit(main())
