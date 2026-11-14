#!/usr/bin/env python3
"""hns.py plus the ops the r5 gym leader / Elite Four / champion / rematch tours use
(tours/r5_league/*.txt). Everything comes from scripts/r5_legends/r5leg.py (bwin, scene, stepto,
approach, closeall, pick, ss/sl, fieldwatch, walkto, objs ...).
Run:  r5league.py tour ROM OUT --tours <emu>/tours/r5_league [--clip] [--only RE]
"""
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(HERE, "..", "r5_legends"))
import r5leg  # noqa: E402,F401  (registers the r5 legend ops on top of hns.py)
import hns  # noqa: E402

if __name__ == "__main__":
    sys.argv[0] = hns.__file__
    sys.exit(hns.main())
