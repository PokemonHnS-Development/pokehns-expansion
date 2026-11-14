"""Helpers for the Pyramid Bag, exec'd into a sess.py session (emu, hns in globals)."""
ITEMS = ["ITEM_HYPER_POTION", "ITEM_ETHER", "ITEM_FULL_RESTORE", "ITEM_MAX_REVIVE", "ITEM_X_SP_DEF",
         "ITEM_FULL_HEAL", "ITEM_LEFTOVERS", "ITEM_QUICK_CLAW", "ITEM_BRIGHT_POWDER", "ITEM_MAX_ELIXIR"]
QTY = [1, 1, 3, 2, 5, 4, 2, 1, 1, 2]


def pyr_fill(items=ITEMS, qty=QTY):
    sb2 = emu.sb2()
    lv = emu.r8(sb2 + 0xCA9) & 3
    for i in range(10):
        it = items[i] if i < len(items) else None
        emu.w16(sb2 + 0xE2C + 20 * lv + 2 * i, emu.const(it) if it else 0)
        emu.w8(sb2 + 0xE54 + 10 * lv + i, qty[i] if it else 0)
    print("pyramid bag (lv %d):" % lv, [(hex(emu.r16(sb2 + 0xE2C + 20 * lv + 2 * i)), emu.r8(sb2 + 0xE54 + 10 * lv + i)) for i in range(10)])


def bag_index():
    st = emu.sym("gPyramidBagMenuState")
    return emu.r16(st + 6) + emu.r16(st + 8)


def bag_seek(n):
    for _ in range(30):
        cur = bag_index()
        if cur == n:
            break
        emu.tap("DOWN" if cur < n else "UP", 4)
        emu.frames(6)
        emu.wait_quiet(300)
    print("bag index", bag_index())


def menu_pos():
    return emu.r8(emu.sym("menu:sMenu") + 2)
