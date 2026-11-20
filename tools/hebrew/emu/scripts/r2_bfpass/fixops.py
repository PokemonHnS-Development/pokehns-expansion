#!/usr/bin/env python3
"""Ops for the round-2 fix checks (bfp_fix_*.txt in this folder), on top of bfpops.py.
Run:  fixops.py tour ROM OUT --tours <this folder> [--clip] [--only '^bfp_fix_']

    pyrfill           fill the Pyramid Bag of the current level mode with ten items
                      (SaveBlock2 frontier.pyramidBag: items at 0xE2C + 20 * lvlMode, quantities
                      at 0xE54 + 10 * lvlMode, lvlMode at 0xCA9; include/global.h)
    pyrseek N         move the Pyramid Bag cursor to item N (gPyramidBagMenuState scroll + cursor)
    menupos           print the open menu's cursor position (menu.c sMenu.cursorPos)
"""
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
sys.path.insert(0, os.path.join(HERE, "..", ".."))                                # tools/hebrew/emu
import hns  # noqa: E402
import bfpops  # noqa: E402,F401  (registers passarea / gamestat and the bffops / r3bf ops)
from hns import script_op, HnsError  # noqa: E402

PYR_ITEMS = ["ITEM_HYPER_POTION", "ITEM_ETHER", "ITEM_FULL_RESTORE", "ITEM_MAX_REVIVE", "ITEM_X_SP_DEF",
             "ITEM_FULL_HEAL", "ITEM_LEFTOVERS", "ITEM_QUICK_CLAW", "ITEM_BRIGHT_POWDER", "ITEM_MAX_ELIXIR"]
PYR_QTY = [1, 1, 3, 2, 5, 4, 2, 1, 1, 2]
SB2_LVL_MODE = 0xCA9
SB2_PYR_ITEMS = 0xE2C
SB2_PYR_QTY = 0xE54


@script_op("pyrfill")
def _op_pyrfill(emu, f, path):
    sb2 = emu.sb2()
    lv = emu.r8(sb2 + SB2_LVL_MODE) & 3
    for i, (item, qty) in enumerate(zip(PYR_ITEMS, PYR_QTY)):
        emu.w16(sb2 + SB2_PYR_ITEMS + 20 * lv + 2 * i, emu.const(item))
        emu.w8(sb2 + SB2_PYR_QTY + 10 * lv + i, qty)
    print("pyrfill lv %d: %s @%d" % (lv, [hex(emu.r16(sb2 + SB2_PYR_ITEMS + 20 * lv + 2 * i)) for i in range(10)],
                                    emu.sync()))


def _pyr_index(emu):
    st = emu.sym("gPyramidBagMenuState")
    return emu.r16(st + 6) + emu.r16(st + 8)


@script_op("pyrseek")
def _op_pyrseek(emu, f, path):
    want = int(f[1], 0)
    for _ in range(30):
        cur = _pyr_index(emu)
        if cur == want:
            break
        emu.tap("DOWN" if cur < want else "UP", 4)
        emu.frames(6)
        emu.wait_quiet(300)
    if _pyr_index(emu) != want:
        raise HnsError("pyrseek %d: the cursor is on %d" % (want, _pyr_index(emu)))
    print("pyrseek %d ok @%d" % (want, emu.sync()))


@script_op("menupos")
def _op_menupos(emu, f, path):
    print("menupos %d @%d" % (emu.r8(emu.sym("menu:sMenu") + 2), emu.sync()))


if __name__ == "__main__":
    sys.argv[0] = hns.__file__
    sys.exit(hns.main())
