#!/usr/bin/env python3
"""hns.py with the svc.py / mart.py tour ops (scripts/r1_npc_services, scripts/r3_marts) plus a few
for the move tutors' field teach flow (src/field_specials.c sMoveLearnUI, src/chooseboxmon.c LearnMove):

    waitlearn STATE [MAX]      run until the field Task_LearnMove (field_specials.c) has data[0] == STATE
                               and the screen is quiet (enum LearnMoveState, src/chooseboxmon.c:261:
                               5 = replace YES/NO up, 8 = stop-teaching YES/NO up)
    freezenpc LOCALID X Y      freeze a wandering NPC on its start tile (gObjectEvents[].frozen)
    boxgo AREA POS             move the PC cursor (see boxpick) without pressing A
    boxmenu NAME               A on the mon under the cursor, shot NAME_menu, B
    boxpick AREA POS [NAME]    in the chooseboxmon PC (CB2_PokeStorage): area 0 = box (POS 0-29),
                               1 = party (POS 0-5); move the cursor there, shot NAME (if given), A,
                               wait for the submenu, shot NAME_menu, A (SELECT)

Usage: tutor.py <hns.py args>   (e.g. tutor.py tour ROM OUT --tours DIR --only RE --clip)
"""
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
EMU = os.path.dirname(os.path.dirname(HERE))
sys.path.insert(0, EMU)
sys.path.insert(0, os.path.join(EMU, "scripts", "r3_marts"))
import hns  # noqa: E402
import mart  # noqa: E402,F401  (svc ops + setbp, setmoney)
from hns import script_op, HnsError, _arg  # noqa: E402

LEARN_TASK = "field_specials:Task_LearnMove"


def _shot(emu, name):
    emu.shot(name)
    emu.shots = getattr(emu, "shots", []) + [name]


@script_op("waitlearn")
def _op_waitlearn(emu, f, path):
    want = int(f[1], 0)
    emu.wait_until(lambda: any(d[0] == want for d in emu.task_data(LEARN_TASK)), _arg(f, 2, 1200),
                   "Task_LearnMove state %d" % want, step=1)
    emu.wait_quiet(600)
    emu.frames(4)
    print("waitlearn %d ok @%d" % (want, emu.sync()))


def _storage_idle(emu):
    p = emu.r32(emu.sym("pokemon_storage_system:sStorage"))
    return p != 0 and emu.r8(p) == 0 and emu.task_active("Task_PokeStorageMain")


def _wait_storage(emu, n=600):
    emu.wait_until(lambda: _storage_idle(emu), n, "the PC to read input", step=2)
    emu.wait_quiet(600)


def box_go(emu, area, pos):
    area_a = emu.sym("pokemon_storage_system:sCursorArea")
    pos_a = emu.sym("pokemon_storage_system:sCursorPosition")
    _wait_storage(emu, 900)
    if area == 1 and emu.r8(area_a) != 1:
        for _ in range(8):                     # up to the buttons row, then PARTY POKEMON
            if emu.r8(area_a) == 3:
                break
            emu.tap("UP", 4)
            _wait_storage(emu)
        if emu.r8(area_a) != 3:
            raise HnsError("boxpick: cannot reach the buttons row (area %d)" % emu.r8(area_a))
        for key in ("LEFT", "RIGHT", "RIGHT"):  # pos 0 = PARTY POKEMON (mirrored on TEXT_RTL?)
            if emu.r8(pos_a) == 0:
                break
            emu.tap(key, 4)
            _wait_storage(emu)
        if emu.r8(pos_a) != 0:
            raise HnsError("boxpick: cannot reach PARTY POKEMON")
        emu.tap("A", 4)
        _wait_storage(emu)
    if area == 0 and emu.r8(area_a) == 1:     # leave the party pane (B), then down into the box
        emu.tap("B", 4)
        _wait_storage(emu)
    swap = False                               # LEFT/RIGHT mirrored on the Hebrew box grid?
    for _ in range(40):
        if emu.r8(area_a) == area and emu.r8(pos_a) == pos:
            break
        cur = emu.r8(pos_a)
        horiz = False
        if area == 1:
            key = "DOWN" if cur < pos else "UP"
        else:
            cr, cc, wr, wc = cur // 6, cur % 6, pos // 6, pos % 6
            if emu.r8(area_a) != 0:
                key = "DOWN"
            elif cr != wr:
                key = "DOWN" if cr < wr else "UP"
            else:
                horiz = True
                key = "RIGHT" if (cc < wc) != swap else "LEFT"
        emu.tap(key, 4)
        _wait_storage(emu)
        if horiz and emu.r8(area_a) == 0:
            nc = emu.r8(pos_a) % 6
            if abs(nc - wc) > abs(cc - wc):
                swap = not swap
    if not (emu.r8(area_a) == area and emu.r8(pos_a) == pos):
        raise HnsError("boxpick: cursor at area %d pos %d, wanted %d %d"
                       % (emu.r8(area_a), emu.r8(pos_a), area, pos))
    emu.frames(4)


def box_select(emu, name, press_select=True):
    emu.tap("A", 4)
    emu.wait_until(lambda: emu.task_active("Task_OnSelectedMon"), 300, "the box submenu", step=2)
    p = emu.r32(emu.sym("pokemon_storage_system:sStorage"))
    emu.wait_until(lambda: emu.r8(p) == 2, 300, "the box submenu input", step=2)
    emu.wait_quiet(600)
    emu.frames(2)
    if name:
        _shot(emu, name + "_menu")
    if press_select:
        emu.tap("A", 4)


@script_op("boxgo")
def _op_boxgo(emu, f, path):
    box_go(emu, int(f[1]), int(f[2]))
    print("boxgo %s %s ok @%d" % (f[1], f[2], emu.sync()))


@script_op("boxpick")
def _op_boxpick(emu, f, path):
    name = f[3] if len(f) > 3 else None
    box_go(emu, int(f[1]), int(f[2]))
    if name:
        _shot(emu, name)
    box_select(emu, name)
    print("boxpick %s %s ok @%d" % (f[1], f[2], emu.sync()))


@script_op("boxmenu")
def _op_boxmenu(emu, f, path):
    """boxmenu NAME: A on the mon under the cursor, shot NAME_menu, B (back to the box)."""
    box_select(emu, f[1], press_select=False)
    emu.tap("B", 4)
    _wait_storage(emu)


OBJ_SIZE = 0x24            # struct ObjectEvent (include/global.fieldmap.h:257), gObjectEvents[16]
MAP_OFFSET = 7


@script_op("freezenpc")
def _op_freezenpc(emu, f, path):
    """freezenpc LOCALID X Y: right after a warp, set the `frozen` bit (byte 1 bit 0) of the object
    event LOCALID on this map, so a wandering NPC stays on its start tile X,Y until the next
    `release` (UnfreezeObjectEvents) or map load; stop unless it stands on X,Y."""
    lid, x, y = int(f[1], 0), int(f[2], 0), int(f[3], 0)
    (g, m, _, _, _), _ = emu.location()
    base = emu.sym("gObjectEvents")
    for i in range(16):
        a = base + i * OBJ_SIZE
        if emu.r8(a) & 1 and emu.r8(a + 8) == lid and emu.r8(a + 9) == m and emu.r8(a + 10) == g:
            emu.w8(a + 1, emu.r8(a + 1) | 1)
            cx, cy = emu.r16(a + 0x10) - MAP_OFFSET, emu.r16(a + 0x12) - MAP_OFFSET
            px, py = emu.r16(a + 0x14) - MAP_OFFSET, emu.r16(a + 0x16) - MAP_OFFSET
            if (cx, cy) != (x, y) or (px, py) != (x, y):
                raise HnsError("freezenpc %d: at (%d,%d) from (%d,%d), wanted (%d,%d)" % (lid, cx, cy, px, py, x, y))
            print("freezenpc %d: object %d frozen at (%d,%d) @%d" % (lid, i, x, y, emu.sync()))
            return
    raise HnsError("freezenpc %d: no such object on map %d.%d" % (lid, g, m))


def _npc(emu, lid):
    (g, m, _, _, _), _ = emu.location()
    base = emu.sym("gObjectEvents")
    for i in range(16):
        a = base + i * OBJ_SIZE
        if emu.r8(a) & 1 and emu.r8(a + 8) == lid and emu.r8(a + 9) == m and emu.r8(a + 10) == g:
            return a
    raise HnsError("no object %d on map %d.%d" % (lid, g, m))


@script_op("approachnpc")
def _op_approachnpc(emu, f, path):
    """approachnpc LOCALID: wait until the (wandering) NPC LOCALID stands still on a tile, freeze it
    there (gObjectEvents[].frozen), walk the player to the tile below it (x first, then y) and face
    UP. Stops unless the player gets there."""
    lid = int(f[1], 0)
    a = _npc(emu, lid)
    still = lambda: (not emu.r8(a) & 2 and emu.r16(a + 0x10) == emu.r16(a + 0x14)
                     and emu.r16(a + 0x12) == emu.r16(a + 0x16))
    emu.wait_until(still, 600, "NPC %d to stand still" % lid, step=1)
    emu.w8(a + 1, emu.r8(a + 1) | 1)
    nx, ny = emu.r16(a + 0x10) - MAP_OFFSET, emu.r16(a + 0x12) - MAP_OFFSET
    tx, ty = nx, ny + 1
    for _ in range(30):
        _, (x, y) = emu.location()
        if (x, y) == (tx, ty):
            break
        if x != tx and y == ny:          # on the NPC's row: step down first
            d = "DOWN"
        elif x != tx:
            d = "RIGHT" if x < tx else "LEFT"
        else:
            d = "DOWN" if y < ty else "UP"
        r = hns.go_step(emu, d)
        if r != "step":
            raise HnsError("approachnpc %d: blocked going %s at (%d,%d), NPC at (%d,%d)" % (lid, d, x, y, nx, ny))
    _, (x, y) = emu.location()
    if (x, y) != (tx, ty):
        raise HnsError("approachnpc %d: player at (%d,%d), wanted (%d,%d)" % (lid, x, y, tx, ty))
    emu.frames(2, "UP")
    emu.frames(14)
    print("approachnpc %d: NPC at (%d,%d), player below @%d" % (lid, nx, ny, emu.sync()))


if __name__ == "__main__":
    sys.argv[0] = hns.__file__
    sys.exit(hns.main())
