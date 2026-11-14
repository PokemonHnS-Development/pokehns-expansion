#!/usr/bin/env python3
"""hns.py plus the r1 service ops (textwatch, scenewatch, burst, scrollshots, scrollmem from
scripts/r1_npc_services/svc.py) and ops for the Game Corner minigames:

    vfwait [MAX]                 run until the Voltorb Flip board reads input
                                 (Task_VoltorbFlipWaitForKeyPress) and the screen is quiet
    vfgoto X Y                   move the Voltorb Flip cursor to card (X, Y) with the D-pad
    vfflip WHAT [N]              flip cards: WHAT = mult (the first N hidden x2/x3 cards,
                                 default all: wins the board), one (N hidden 1-cards, default 1),
                                 voltorb (the first hidden Voltorb: loses the board)
    vfboard                      print the board (values, shown flags) to the log
    slotstate STATE [MAX]        run until sSlotMachine->state == STATE (an SLOTTASK_* name or
                                 number from src/slot_machine.c)
    setcoins N                   write the coin count while a script runs (`ev` needs a free
                                 player): gSaveBlock1Ptr->coins (+0x498, from SetCoins'
                                 disassembly) = N ^ gSaveBlock2Ptr->encryptionKey (+0xAC)
    slotbias HEX                 overwrite sSlotMachine->machineBias (+4) and set didNotFailBias
                                 (+6) after the spin drew its own bias (state
                                 SLOTTASK_RESET_BIAS_FAILURE), e.g. 80 = BIAS_STRAIGHT_7, 02 = cherry
    rlwin MULT [WON]             roulette: once the ball has landed (Task_SlideGridOnscreen),
                                 set tWonBet = WON (default 1) and, unless MULT is 0, the
                                 multiplier (src/roulette.c:1174-1181; 12 = jackpot)

Usage: gc.py <hns.py args>   (e.g. gc.py tour ROM OUT --tours DIR --only RE --clip)
"""
import os
import re
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
EMU = os.path.dirname(os.path.dirname(HERE))
sys.path.insert(0, EMU)
sys.path.insert(0, os.path.join(EMU, "scripts", "r1_npc_services"))
import hns  # noqa: E402
import svc  # noqa: E402,F401  (registers textwatch, scenewatch, burst, scrollshots, scrollmem)
from hns import script_op, HnsError, TourTimeout, _arg  # noqa: E402

# struct VoltorbFlipState (src/voltorb_flip.c:131-142): 25 card states (value:4, isShown:1,
# note1..3 in byte 0, noteVoltorb in byte 1; -mabi=apcs-gnu pads each to 4 bytes, seen in a
# memory dump), then pointerSprite, outlineSprite, cursorX, cursorY, cursorWriteValue.
VF_CARDS, VF_STRIDE, VF_CURX, VF_CURY = 0, 4, 0x66, 0x67
VF_VALUE_VOLTORB = 3


def _src_enum(emu, path, first):
    """Names of the enum in source file PATH whose first member is FIRST -> index."""
    src = os.environ.get("HNS_SRC") or os.path.dirname(emu.elf.path)
    text = open(os.path.join(src, path), errors="replace").read()
    i = text.index(first)
    body = text[i:text.index("}", i)]
    names = [re.sub(r"\s*=.*", "", x).strip() for x in body.split(",")]
    return {n: k for k, n in enumerate(n for n in names if n and not n.startswith("//"))}


def vf_state(emu):
    p = emu.r32(emu.sym("voltorb_flip:sVoltorbFlipState"))
    if not p:
        raise HnsError("Voltorb Flip is not running (sVoltorbFlipState is NULL)")
    return p


def vf_cards(emu):
    raw = emu.read(vf_state(emu) + VF_CARDS, 25 * VF_STRIDE)
    return [(raw[VF_STRIDE * i] & 0xF, (raw[VF_STRIDE * i] >> 4) & 1) for i in range(25)]


def vf_idle(emu):
    return any(fn == emu.sym("Task_VoltorbFlipWaitForKeyPress") for _, fn, _ in emu.tasks()) \
        and not emu.fading()


@script_op("vfwait")
def _op_vfwait(emu, f, path):
    emu.wait_until(lambda: vf_idle(emu), _arg(f, 1, 900), "the Voltorb Flip board to read input", step=2)
    emu.wait_quiet(600)
    print("vfwait ok @%d" % emu.sync())


def vf_goto(emu, x, y):
    st = vf_state(emu)
    for _ in range(12):
        cx, cy = emu.r8(st + VF_CURX), emu.r8(st + VF_CURY)
        if (cx, cy) == (x, y):
            return
        key = "LEFT" if cx > x else "RIGHT" if cx < x else "UP" if cy > y else "DOWN"
        emu.tap(key, 4)
    raise TourTimeout("vfgoto: cursor stuck at %d,%d (wanted %d,%d)" % (cx, cy, x, y))


@script_op("vfgoto")
def _op_vfgoto(emu, f, path):
    vf_goto(emu, int(f[1]), int(f[2]))
    emu.wait_quiet(300)
    print("vfgoto %s %s ok @%d" % (f[1], f[2], emu.sync()))


@script_op("vfboard")
def _op_vfboard(emu, f, path):
    cards = vf_cards(emu)
    for y in range(5):
        print("vfboard " + " ".join(("V" if v == 3 else str(v + 1)) + ("*" if s else " ")
                                    for v, s in cards[y * 5:y * 5 + 5]))


@script_op("vfflip")
def _op_vfflip(emu, f, path):
    what, n = f[1], _arg(f, 2, 1)
    cards = vf_cards(emu)
    if what == "mult":
        todo = [i for i, (v, s) in enumerate(cards) if v in (1, 2) and not s][:_arg(f, 2, 25)]
    elif what == "one":
        todo = [i for i, (v, s) in enumerate(cards) if v == 0 and not s][:n]
    elif what == "voltorb":
        todo = [i for i, (v, s) in enumerate(cards) if v == VF_VALUE_VOLTORB and not s][:1]
    else:
        raise HnsError("vfflip: unknown %s" % what)
    for k, i in enumerate(todo):
        if not vf_idle(emu):
            break
        vf_goto(emu, i % 5, i // 5)
        emu.tap("A", 6)
    print("vfflip %s: flipped %d card(s) @%d" % (what, len(todo), emu.sync()))


@script_op("slotstate")
def _op_slotstate(emu, f, path):
    names = _src_enum(emu, "src/slot_machine.c", "SLOTTASK_UNFADE")
    want = names[f[1]] if f[1] in names else int(f[1], 0)
    ptr = emu.sym("slot_machine:sSlotMachine")

    def ok():
        p = emu.r32(ptr)
        return p != 0 and emu.r8(p) == want
    emu.wait_until(ok, _arg(f, 2, 900), "sSlotMachine->state == %s" % f[1], step=2)
    print("slotstate %s ok @%d" % (f[1], emu.sync()))


SB1_COINS, SB2_KEY = 0x498, 0xAC


@script_op("setcoins")
def _op_setcoins(emu, f, path):
    key = emu.r32(emu.sb2() + SB2_KEY) & 0xFFFF
    emu.w16(emu.sb1() + SB1_COINS, int(f[1], 0) ^ key)
    print("setcoins %s @%d" % (f[1], emu.sync()))


@script_op("slotbias")
def _op_slotbias(emu, f, path):
    p = emu.r32(emu.sym("slot_machine:sSlotMachine"))
    emu.w8(p + 4, int(f[1], 16))
    emu.w8(p + 6, 1)                                    # didNotFailBias (+6)
    print("slotbias %s @%d" % (f[1], emu.sync()))


@script_op("rlwin")
def _op_rlwin(emu, f, path):
    """rlwin MULT [WON]: see the module docstring; WON 0 makes the spin a miss, MULT 0 keeps
    the bet's own multiplier."""
    mult, won = int(f[1]), _arg(f, 2, 1)
    want = emu.sym("roulette:Task_SlideGridOnscreen")
    emu.wait_until(lambda: any(fn == want for _, fn, _ in emu.tasks()), _arg(f, 3, 2400),
                   "the roulette ball to land", step=1)
    for tid, fn, _ in emu.tasks():
        if fn == want:
            base = emu.sym("gTasks") + tid * 0x28 + 8      # struct Task: data[16] at +8
            if mult:
                emu.w16(base + 2 * 2, mult)                 # tMultiplier = data[2]
            emu.w16(base + 5 * 2, won)                      # tWonBet = data[5]
    print("rlwin %d %d @%d" % (mult, won, emu.sync()))


if __name__ == "__main__":
    sys.argv[0] = hns.__file__
    sys.exit(hns.main())
