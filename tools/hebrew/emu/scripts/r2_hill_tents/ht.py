#!/usr/bin/env python3
"""Trainer Hill and Battle Tent screen runs: one script on the Hebrew clip ROM or the English ROM,
from a battery save or from a savestate an earlier step left, with the clip report on for Hebrew.

    ht.py run he|en SCRIPT [--from STATE | --save SAV] [--to STATE] [--save-out SAV] [--out NAME]

  he   R/rom/pokehns-clip.gba (rc5 clip build), HNS_SRC=../pokehns-release
  en   ../pokehns-en/pokehns.gba, HNS_SRC=../pokehns-en
  R    HT_OUT (default ../hns-tools/scratch/screens/r2_trainer_hill_and_battle_tents)

Screenshots go to R/<he|en>/<NAME>/ (NAME = the script's basename unless --out). Savestates are
per ROM (R/<he|en>/_states/STATE.ss): --from boots the battery in the state's folder, then loads
the state; --to writes one when the script ends. A battery save made by either ROM loads in both.
The script language is hns.py's plus the r2/r3 ops (r3bf.py) and the ops below:
    hillstate            print the trainerHill save fields (mode, timer, flags)
    battle2 PREFIX [MAX] fight a (double) battle to the end with move 0 on every player battler,
                         KO-ing the foes with sethp after each turn; one shot per text page
    sethpall SIDE HP     set every battler of SIDE (player/enemy) to HP (doubles too)
"""
import argparse
import os
import shutil
import sys

R = os.environ.get("HT_OUT", "../hns-tools/scratch/screens/r2_trainer_hill_and_battle_tents")
ROMS = {
    "he": (os.path.join(R, "rom", "pokehns-clip.gba"), "../pokehns-release"),
    "en": ("../pokehns-en/pokehns.gba", "../pokehns-en"),
}
HERE = os.path.dirname(os.path.abspath(__file__))


def main():
    ap = argparse.ArgumentParser()
    sub = ap.add_subparsers(dest="cmd", required=True)
    p = sub.add_parser("run")
    p.add_argument("which", choices=sorted(ROMS))
    p.add_argument("script")
    p.add_argument("--from", dest="frm")
    p.add_argument("--save")
    p.add_argument("--to")
    p.add_argument("--save-out")
    p.add_argument("--out")
    p.add_argument("--noclip", action="store_true")
    a = ap.parse_args()
    rom, src = ROMS[a.which]
    os.environ["HNS_SRC"] = src
    os.environ.setdefault("HNS_RUNNER", "../hns-tools/emu/hnsrun")
    os.environ.setdefault("HNS_WORK", os.path.join(R, "work" if a.which == "he" else "work_en"))
    sys.path.insert(0, os.path.join(HERE, "..", "r3_frontier"))
    import r3bf  # noqa: F401  (hns + r2sf + r3bf ops)
    import hns
    import hilltent_ops  # noqa: F401
    name = a.out or os.path.splitext(os.path.basename(a.script))[0]
    outdir = os.path.join(R, a.which, name)
    os.makedirs(outdir, exist_ok=True)
    for old in os.listdir(outdir):
        if old.endswith(".png"):
            os.remove(os.path.join(outdir, old))
    states = os.path.join(R, a.which, "_states")
    os.makedirs(states, exist_ok=True)
    cur = os.path.join(outdir, "cur.sav")
    if a.frm:
        sav = os.path.join(states, a.frm + ".sav")
        shutil.copyfile(sav, cur)
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
        if a.which == "he" and not a.noclip:
            hns.clip_hook(emu, outdir)
        emu.run_script(a.script)
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
    if rc == 0 and a.save_out:
        shutil.copyfile(cur, a.save_out)
        print("save written: %s" % a.save_out)
    clip = getattr(emu, "clip", None)
    if clip:
        print("clip total %d, lost %d" % (clip.total(), clip.lost))
    print("exit %d (runner %s)" % (rc, code))
    return rc


if __name__ == "__main__":
    sys.path.insert(0, HERE)
    sys.exit(main())
