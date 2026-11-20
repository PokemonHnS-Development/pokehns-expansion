#!/usr/bin/env python3
"""hns.py plus the ops the r5 known-issue tours use: the Pokedex ops of scripts/r4_misc/r4misc.py
(dexopen, dexgoto, dexinfo, dexback; it also loads ladder.py's event ops) and the storage ops of
scripts/r2_pc_storage/pcs.py (pcwait, pcgoto, ...).

    r5known.py tour ROM OUTDIR --tours <this folder>/tours [--clip] [--only RE]
"""
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(HERE, "..", ".."))                      # tools/hebrew/emu
sys.path.insert(0, os.path.join(HERE, "..", "r4_misc"))
sys.path.insert(0, os.path.join(HERE, "..", "r2_pc_storage"))
import hns  # noqa: E402
import r4misc  # noqa: E402,F401  (dex ops, ladder ops)
import pcs  # noqa: E402,F401  (storage ops)

if __name__ == "__main__":
    sys.argv[0] = hns.__file__
    sys.exit(hns.main())
