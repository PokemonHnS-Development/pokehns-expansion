#!/usr/bin/env python3
"""Print a harness script that debug-warps to a map and screenshots it.
    warp.py STATE GROUP MAP NAME [WARP] | ./harness ROM
STATE must be a savestate with the debug main menu open (cursor on Utilities),
e.g. one made right after new_game_to_debug_menu.txt."""
import sys
def num(n):
    o = []
    for i, k in enumerate([n % 10, (n // 10) % 10, (n // 100) % 10]):
        if i: o.append("press RIGHT")
        o += ["press UP"] * k
    return o
state, g, m, name = sys.argv[1], int(sys.argv[2]), int(sys.argv[3]), sys.argv[4]
w = int(sys.argv[5]) if len(sys.argv) > 5 else 0
print("\n".join([f"loadstate {state}", "press A", "wait 20", "press DOWN", "wait 10", "press A", "wait 30"] + num(g)
                + ["press A", "wait 20"] + num(m) + ["press A", "wait 20"] + num(w) + ["press A", "wait 300",
                   f"shot {name}.png", f"savestate {name}.ss"]))
