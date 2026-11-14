#!/usr/bin/env python3
"""Driver for the round-16 menu tours (tours/r16_menus): hns.py plus the PC storage ops of pcs.py
(pcwait, pcgoto, ...) and the Easy Chat and r2/r3 ops of hwec.py (ecwait, ec, ecgroup, ecletter,
eclist, ecputword, seek, talk helpers, ...). Nothing new is added; this only loads both op sets so
one tour folder runs with one driver.

Run:  menu16.py tour ROM OUT --tours tools/hebrew/emu/tours/r16_menus [--clip] [--only RE]
Saves: HNS_SAVES=hns-tools/emu/saves_all (menuA_base, ladder6_postgame, pcs_postgame).
"""
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
SCRIPTS = os.path.dirname(HERE)
sys.path.insert(0, os.path.dirname(SCRIPTS))                                # tools/hebrew/emu
for d in ("r2_pc_storage", "r2_help_windows_and_easy_chat"):
    sys.path.insert(0, os.path.join(SCRIPTS, d))
import hns  # noqa: E402
import pcs  # noqa: E402,F401  (PC storage ops)
import hwec  # noqa: E402,F401  (Easy Chat ops; r3bf, r2sf)

if __name__ == "__main__":
    sys.argv[0] = hns.__file__
    sys.exit(hns.main())
