#!/usr/bin/env python3
"""hns.py with the svc.py tour ops (scripts/r1_npc_services/svc.py) plus a few for the shop screens:

    listshots PREFIX [MAX]     snap PREFIX_01, then DOWN + snap while the shop list's cursor moves on
                               (ListMenu scrollOffset + selectedRow in the list task's data; the
                               scroll arrows animate, so the screen never stops changing at the end,
                               and the shop list wraps from CANCEL to the top). Ends on the top row.
    listgo IDX                 UP/DOWN until the shop list's cursor is on row IDX (0 = first item)
    setexpensive N             challengeSettings.tx_Challenges_Expensive = N (0 x1, 1 x5, 2 x10, 3 x50;
                               src/item.c GetItemPrice); byte SB3+0x1A bits 0-2 (measured with the
                               build's ABI flags, same in the Hebrew and English trees)
    setinfinitetms 0|1         challengeSettings.tx_Mode_InfiniteTMs (byte SB3+0x2C bit 0; src/item.c GetItemImportance)
    setmoney N                 gSaveBlock1Ptr->money = N (SetMoney: XOR with SB2 encryptionKey)
    setbp N                    gSaveBlock2Ptr->frontier.battlePoints = N (SB2+0xEB8, u16)
    expectmoney N              stop unless GetMoney() == N

Usage: mart.py <hns.py args>   (e.g. mart.py tour ROM OUT --tours DIR --only RE --clip)
"""
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
EMU = os.path.dirname(os.path.dirname(HERE))
sys.path.insert(0, EMU)
sys.path.insert(0, os.path.join(EMU, "scripts", "r1_npc_services"))
import hns  # noqa: E402
import svc  # noqa: E402,F401  (registers textwatch, burst, scenewatch, scrollshots, scrollmem)
from hns import script_op, HnsError, _arg  # noqa: E402

SB3_EXPENSIVE = 0x10 + 0x0A       # offsetof(SaveBlock3, challengeSettings) + byte of the bitfield
SB3_INFINITE_TMS = 0x10 + 0x1C
SB1_MONEY = 0x494
SB2_ENCKEY = 0xAC
SB2_BP = 0xEB8
# struct ListMenu sits in the list task's data[]: template (0x18 bytes), then u16 scrollOffset,
# u16 selectedRow (include/list_menu.h:84-93) = data[12], data[13]
LIST_TASK = "ListMenuDummyTask"


def _sb3(emu):
    return emu.r32(emu.sym("gSaveBlock3Ptr"))


def _sb1(emu):
    return emu.r32(emu.sym("gSaveBlock1Ptr"))


def _sb2(emu):
    return emu.r32(emu.sym("gSaveBlock2Ptr"))


def list_pos(emu):
    d = emu.task_data(LIST_TASK)
    if len(d) != 1:
        raise HnsError("listpos: %d list tasks active" % len(d))
    return d[0][12] + d[0][13]


def _shot(emu, name):
    emu.shot(name)
    emu.shots = getattr(emu, "shots", []) + [name]


@script_op("listshots")
def _op_listshots(emu, f, path):
    prefix, mx = f[1], _arg(f, 2, 60)
    n = 0
    while n < mx:
        emu.wait_quiet(900)
        emu.frames(2)
        n += 1
        _shot(emu, "%s_%02d" % (prefix, n))
        before = list_pos(emu)
        emu.tap("DOWN", 6)
        emu.wait_quiet(900)
        if list_pos(emu) <= before:      # stuck at the end, or wrapped to the top
            break
    print("listshots %s: %d shot(s), last row %d @%d" % (prefix, n, list_pos(emu), emu.sync()))


@script_op("listgo")
def _op_listgo(emu, f, path):
    want = int(f[1], 0)
    for _ in range(120):
        cur = list_pos(emu)
        if cur == want:
            break
        emu.tap("DOWN" if cur < want else "UP", 6)
        emu.wait_quiet(900)
    if list_pos(emu) != want:
        raise HnsError("listgo %d: cursor stuck at %d" % (want, list_pos(emu)))
    emu.frames(2)
    print("listgo %d ok @%d" % (want, emu.sync()))


@script_op("setexpensive")
def _op_setexpensive(emu, f, path):
    n = int(f[1], 0) & 7
    a = _sb3(emu) + SB3_EXPENSIVE
    old = emu.r8(a)
    emu.w8(a, (old & ~7) | n)
    print("setexpensive %d: byte %08X %02X -> %02X" % (n, a, old, emu.r8(a)))


@script_op("setinfinitetms")
def _op_setinfinitetms(emu, f, path):
    a = _sb3(emu) + SB3_INFINITE_TMS
    old = emu.r8(a)
    emu.w8(a, (old & ~1) | (int(f[1], 0) & 1))
    print("setinfinitetms %s: byte %08X %02X -> %02X" % (f[1], a, old, emu.r8(a)))


@script_op("setmoney")
def _op_setmoney(emu, f, path):
    v = int(f[1], 0)
    key = emu.r32(_sb2(emu) + SB2_ENCKEY)
    emu.w32(_sb1(emu) + SB1_MONEY, v ^ key)
    print("setmoney %d" % v)


@script_op("expectmoney")
def _op_expectmoney(emu, f, path):
    v = int(f[1], 0)
    got = emu.r32(_sb1(emu) + SB1_MONEY) ^ emu.r32(_sb2(emu) + SB2_ENCKEY)
    if got != v:
        raise HnsError("expectmoney %d: money is %d" % (v, got))
    print("expectmoney %d ok" % v)


@script_op("setbp")
def _op_setbp(emu, f, path):
    emu.w16(_sb2(emu) + SB2_BP, int(f[1], 0))
    print("setbp %s" % f[1])


if __name__ == "__main__":
    sys.argv[0] = hns.__file__
    sys.exit(hns.main())
