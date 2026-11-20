#!/usr/bin/env python3
"""hns.py plus ops for the bedroom PC DECORATION screens (src/decoration.c):

    decorprobe                  print the doll inventory (gDecorationInventories[DECORCAT_DOLL]:
                                items pointer + size, src/decoration_inventory.c:6-27) and the
                                player-room decorations and positions (SaveBlock1
                                playerRoomDecorations[12] + playerRoomDecorationPositions[12],
                                0x7C bytes before decorationDolls, include/global.h:1242-1250)
    decorwait [MAX]             run until Task_SelectLocation reads the D-pad (placement or
                                put-away cursor, src/decoration.c:1890) and the screen is quiet
    decorgoto X Y [MAX]         move the placement / put-away cursor to map tile X,Y: tCursorX/Y
                                (task data[0]/[1], src/decoration.c:46-47) hold the tile plus
                                MAP_OFFSET (7); one 3-frame tap moves one tile (the camera sprite
                                walks 16 px in 8 frames, src/decoration.c:1905-1950)
Usage: decor.py <hns.py args>   (e.g. decor.py tour ROM OUT --tours DIR --only RE --clip)
"""
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
EMU = os.path.dirname(os.path.dirname(HERE))
sys.path.insert(0, EMU)
import hns  # noqa: E402
from hns import script_op, HnsError, TourTimeout, _arg  # noqa: E402

MAP_OFFSET = 7
ROOM_BEFORE_DOLLS = 0x2798 - 0x271C      # include/global.h:1242, 1250


def _names(emu):
    if not hasattr(emu, "_decor_names"):
        import re
        src = os.environ.get("HNS_SRC") or os.path.dirname(emu.elf.path)
        rev = {}
        for line in open(os.path.join(src, "include/constants/decorations.h"), errors="replace"):
            m = re.match(r"\s*#define\s+(DECOR_\w+)\s+(\d+)\b", line)
            if m:
                rev.setdefault(int(m.group(2)), m.group(1))
        emu._decor_names = rev
    return emu._decor_names


@script_op("decorprobe")
def _op_decorprobe(emu, f, path):
    inv = emu.sym("gDecorationInventories")
    items, size = emu.r32(inv), emu.r8(inv + 4)
    dolls = list(emu.read(items, size))
    names = _names(emu)
    room = list(emu.read(items - ROOM_BEFORE_DOLLS, 12))
    pos = list(emu.read(items - ROOM_BEFORE_DOLLS + 12, 12))
    out = ["dolls (%d of %d): %s" % (sum(1 for d in dolls if d), size,
                                     ",".join(names.get(d, str(d)) for d in dolls if d)),
           "room: " + ", ".join("%s@(%d,%d)" % (names.get(d, d), p >> 4, p & 15)
                                for d, p in zip(room, pos) if d)]
    for line in out:
        print("decorprobe: " + line)
    emu.log.extend("decorprobe: " + line for line in out)


def _cursor(emu):
    d = emu.task_data("Task_SelectLocation")
    if not d:
        return None
    return d[0][0] - MAP_OFFSET, d[0][1] - MAP_OFFSET


@script_op("decorwait")
def _op_decorwait(emu, f, path):
    emu.wait_until(lambda: _cursor(emu) is not None, _arg(f, 1, 900),
                   "Task_SelectLocation (the decoration cursor)", step=2)
    emu.wait_quiet(600)
    emu.frames(10)
    print("decorwait ok at %s @%d" % (_cursor(emu), emu.sync()))


@script_op("decorgoto")
def _op_decorgoto(emu, f, path):
    want = (int(f[1], 0), int(f[2], 0))
    for _ in range(_arg(f, 3, 40)):
        cur = _cursor(emu)
        if cur is None:
            raise HnsError("decorgoto: the decoration cursor is not active")
        if cur == want:
            emu.frames(4)
            print("decorgoto %d %d ok @%d" % (want[0], want[1], emu.sync()))
            return
        if cur[0] != want[0]:
            key = "LEFT" if cur[0] > want[0] else "RIGHT"
        else:
            key = "UP" if cur[1] > want[1] else "DOWN"
        emu.tap(key, 14)
        if _cursor(emu) == cur:
            emu.frames(8)
            if _cursor(emu) == cur:
                raise TourTimeout("decorgoto: %s did not move the cursor from %s" % (key, cur))
    raise TourTimeout("decorgoto: cursor at %s, wanted %s" % (_cursor(emu), want))


SPRITE_SIZE, SPRITE_FLAGS = 0x44, 0x3E    # struct Sprite, include/sprite.h:190-217 (invisible = bit 2)


@script_op("decorshow")
def _op_decorshow(emu, f, path):
    """decorshow: the cursor sprite blinks while placing (15 of every 32 frames visible,
    InitializePuttingAwayCursorSprite2, src/decoration.c:2083-2099): run until it has just turned
    visible, so the next snap shows the decoration on the cursor."""
    spr = emu.sym("gSprites") + SPRITE_SIZE * emu.r8(emu.sym("sDecor_CameraSpriteObjectIdx1"))
    hidden = lambda: bool(emu.r8(spr + SPRITE_FLAGS) & 4)
    emu.wait_until(hidden, 64, "the cursor sprite to blink off", step=1)
    emu.wait_until(lambda: not hidden(), 64, "the cursor sprite to blink on", step=1)
    emu.frames(2)
    print("decorshow ok @%d" % emu.sync())


@script_op("decormsg")
def _op_decormsg(emu, f, path):
    """decormsg [MAX]: a DisplayItemMessageOnField message has printed. Its callback (e.g.
    CantPlaceDecorationPrompt, which waits for A/B) is called every frame by
    Task_ContinueTaskAfterMessagePrints (src/menu_helpers.c), so the task func stays that one:
    wait for it, then for the printer to finish."""
    emu.wait_until(lambda: emu.task_active("Task_ContinueTaskAfterMessagePrints"), _arg(f, 1, 900),
                   "Task_ContinueTaskAfterMessagePrints", step=2)
    emu.wait_quiet(900)
    emu.frames(4)
    print("decormsg ok @%d" % emu.sync())


@script_op("decorrow")
def _op_decorrow(emu, f, path):
    """decorrow N: in the decoration items list, tap DOWN/UP until the selected row
    (sDecorationsScrollOffset + sDecorationsCursorPos, u16 each, kept up to date by
    HandleDecorationItemsMenuInput, src/decoration.c:1026) is N; then waitquiet."""
    want = int(f[1], 0)
    so, cp = emu.sym("sDecorationsScrollOffset"), emu.sym("sDecorationsCursorPos")
    for _ in range(_arg(f, 2, 60)):
        cur = emu.r16(so) + emu.r16(cp)
        if cur == want:
            emu.wait_quiet(600)
            print("decorrow %d ok (scroll %d, cursor %d) @%d" % (want, emu.r16(so), emu.r16(cp), emu.sync()))
            return
        emu.tap("DOWN" if cur < want else "UP", 4)
        emu.wait_quiet(600)
    raise TourTimeout("decorrow: row %d, wanted %d" % (emu.r16(so) + emu.r16(cp), want))


if __name__ == "__main__":
    sys.argv[0] = hns.__file__
    sys.exit(hns.main())
