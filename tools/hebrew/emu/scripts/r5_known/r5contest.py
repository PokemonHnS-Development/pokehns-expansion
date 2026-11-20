#!/usr/bin/env python3
"""scripts/r2_pokegear_ribbons_contests/rc.py (contest ops) plus one op for the r5 contest tours:

    pinptr SYM PTROFF OFF HEXBYTES   pin HEXBYTES (hnsrun `pin`, rewritten before every frame) at
                                     P + OFF, where P is the pointer stored at offset PTROFF of the
                                     struct the pointer variable SYM points to (all hex): e.g.
                                     gContestResources->status + OFF once the contest has started

    r5contest.py tour ROM OUTDIR --tours <this folder>/tours_contest [--clip] [--only RE]
"""
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(HERE, "..", ".."))                      # tools/hebrew/emu
sys.path.insert(0, os.path.join(HERE, "..", "r2_pokegear_ribbons_contests"))
import hns  # noqa: E402
import rc  # noqa: E402,F401  (contest ops)
from hns import script_op, HnsError  # noqa: E402


@script_op("pinptr")
def _op_pinptr(emu, f, path):
    obj = emu.r32(emu.sym(f[1]))
    base = emu.r32(obj + int(f[2], 16)) if obj else 0
    if not base:
        raise HnsError("pinptr: %s->+%s is NULL" % (f[1], f[2]))
    addr = base + int(f[3], 16)
    emu.expect_after("pin %08X %s" % (addr, f[4]), r"^PIN ")
    print("pinptr %08X = %s @%d" % (addr, f[4], emu.sync()))


if __name__ == "__main__":
    sys.argv[0] = hns.__file__
    sys.exit(hns.main())
