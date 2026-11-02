#!/usr/bin/env python3
"""hns.py plus the ops the round-10 names tours use (tours/r10_names/*.txt): the r6 league ops
(r5leg bwin, periodic ...), the r6 summary ops (sumwait, sumkey ...), and r8bfe's setpocket.

    setbmon BATTLER FIELD VALUE   write a gBattleMons[BATTLER] field: ability (+0x20, u16),
                                  move0..move3 (+0x0C, u16), hp (+0x29... see OFFS)
Run:  r10names.py tour ROM OUT --tours <emu>/tours/r10_names [--clip] [--only RE]
"""
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
for d in ("r6_league", "r6_trainers", "r6_summary", "r8_bfe"):
    sys.path.insert(0, os.path.join(HERE, "..", d))
import r6league  # noqa: E402,F401
import r6trainers  # noqa: E402,F401
import r6sum  # noqa: E402,F401
import r8bfe  # noqa: E402,F401
import hns  # noqa: E402
from hns import script_op  # noqa: E402

BMON = 0x88
OFFS = {"ability": (0x20, 2), "move0": (0x0C, 2), "move1": (0x0E, 2), "move2": (0x10, 2), "move3": (0x12, 2)}


@script_op("setbmon")
def _op_setbmon(emu, f, path):
    b, field, val = int(f[1]), f[2], emu.const(f[3])
    off, size = OFFS[field]
    addr = emu.sym("gBattleMons") + BMON * b + off
    (emu.w16 if size == 2 else emu.w8)(addr, val)
    print("setbmon %d %s = %d" % (b, field, val))


if __name__ == "__main__":
    sys.argv[0] = hns.__file__
    sys.exit(hns.main())
