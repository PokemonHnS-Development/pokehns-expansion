#!/usr/bin/env python3
"""hns.py plus the ops the r6 Johto story-scene tours use (tours/r6_story_johto/*.txt):
everything from scripts/r6_league/r6league.py (scene, sceneto, stepto, approach, bwin, bitem,
walkto, objs, ...), plus:

    yesno PREFIX YES|NO     a YES/NO box is open (scene stopped on it): shot PREFIX, then pick
                            YES (A) or NO (B)
Run:  r6story.py tour ROM OUT --tours <emu>/tours/r6_story_johto [--clip] [--only RE]
"""
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(HERE, "..", "r6_league"))
import r6league  # noqa: E402,F401  (registers the r5/r6 ops on top of hns.py)
import hns  # noqa: E402
from hns import script_op  # noqa: E402


@script_op("yesno")
def _op_yesno(emu, f, path):
    emu.wait_menu_ready()
    emu.frames(2)
    name = f[1]
    emu.shot(name)
    emu.shots = getattr(emu, "shots", []) + [name]
    emu.tap("A" if f[2].upper() == "YES" else "B", 4)
    print("yesno %s %s @%d" % (f[1], f[2], emu.sync()))


if __name__ == "__main__":
    sys.argv[0] = hns.__file__
    sys.exit(hns.main())
