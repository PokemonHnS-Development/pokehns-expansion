#!/usr/bin/env python3
"""Print a harness script that debug-warps to a map and screenshots it.
    warp.py STATE GROUP MAP NAME [WARP] | ./harness ROM
    warp.py STATE GROUP MAP NAME --xy X Y [--elf pokehns.elf] | ./harness ROM
STATE must be a savestate with the debug main menu open (cursor on Utilities),
e.g. one made right after new_game_to_debug_menu.txt.
--xy lands on an exact tile: it overwrites sWarpDestination's coordinates right
after the warp starts (the symbol is read from the ELF). Landing on water
starts you surfing."""
import os, subprocess, sys

def num(n):
    o = []
    for i, k in enumerate([n % 10, (n // 10) % 10, (n // 100) % 10]):
        if i: o.append("press RIGHT")
        o += ["press UP"] * k
    return o

def symbol(elf, name):
    out = subprocess.run(["arm-none-eabi-nm", elf], capture_output=True, text=True, check=True).stdout
    for line in out.splitlines():
        p = line.split()
        if len(p) == 3 and p[2] == name:
            return int(p[0], 16)
    sys.exit(f"{name} not found in {elf}")

args = sys.argv[1:]
xy = elf = None
if "--elf" in args:
    i = args.index("--elf"); elf = args[i + 1]; del args[i:i + 2]
if "--xy" in args:
    i = args.index("--xy"); xy = (int(args[i + 1]), int(args[i + 2])); del args[i:i + 3]
state, g, m, name = args[0], int(args[1]), int(args[2]), args[3]
w = int(args[4]) if len(args) > 4 else 0
after = []
if xy:
    elf = elf or os.path.join(os.path.dirname(__file__), "..", "..", "..", "pokehns.elf")
    dest = symbol(elf, "sWarpDestination")  # struct WarpData { s8 group, num, warpId; s16 x, y; }
    after = ["wait 2", f"w8 {dest + 2:x} 255", f"w16 {dest + 4:x} {xy[0]}", f"w16 {dest + 6:x} {xy[1]}"]  # warpId = WARP_ID_NONE
print("\n".join([f"loadstate {state}", "press A", "wait 20", "press DOWN", "wait 10", "press A", "wait 30"] + num(g)
                + ["press A", "wait 20"] + num(m) + ["press A", "wait 20"] + num(w) + ["press A"] + after
                + ["wait 300", f"shot {name}.png", f"savestate {name}.ss"]))
