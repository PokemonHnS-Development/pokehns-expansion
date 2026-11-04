#!/usr/bin/env python3
"""Driver for the round-16 contest tours (tours/r16_contests): r9c.py (setopps, and through rc5.py /
rc.py / r3bf.py / r2sf.py every contest, Blender and Pokeblock op) plus:

    effplan R:A,B,C,D ...
                 forced stand-in for the appeal result messages: when contestplay5 takes the
                 PREFIX_rR_NN_pick shot of round R (the move list is reading input, after
                 Task_ResetForNextRound cleared the round's state, src/contest.c:5203-5235), write
                 effectStringId of contestants 0-3 (struct ContestantStatus +19, 28 bytes each,
                 gContestResources->status, include/contest.h:172-219) = A,B,C,D (CONTEST_STRING_*
                 numbers, include/contest.h:8-73; '-' leaves a slot alone). Each contestant's appeal
                 then prints it through PrintAppealMoveResultText (src/contest.c:1925-1932, 4620-4628)
                 unless its own move sets another one first.
    linkplan R   at the pick shot of round R, set gLinkContestFlags = LINK_CONTEST_FLAG_IS_LINK, so
                 Task_SelectedMove prints the link standby message (src/contest.c:1693-1704); there is
                 no link partner, so the tour has to end right after
    pokeblocks C:SP,DR,SW,BI,SO,FEEL ...
                 write gSaveBlock1Ptr->pokeblocks[0..] (SB1 +0xF98, 40 x 8 bytes: color, spicy, dry,
                 sweet, bitter, sour, feel; the literal of GetFirstFreePokeblockSlot); the rest of the
                 40 slots are cleared, or filled with copies of the last one with 'fill N' (N blocks)
    monsheen SLOT VAL
                 set the sheen (struct PokemonSubstruct2 +11, after six EVs and five conditions,
                 include/pokemon.h:167-180) of gPlayerParty[SLOT]
    pw16 PTRSYM OFF VAL
                 write the u16 VAL (hex) at *PTRSYM + OFF (hex): a field of a heap struct whose
                 pointer is a global, e.g. sBerryBlender->progressBarValue (+0x116, r2sf.py BB_PROGRESS)
    clearpocket POCKET
                 empty every slot of gBagPockets[POCKET] (item 0, quantity 0 xor the SaveBlock2
                 key; the layout fullpocket in r9c.py writes), e.g. POCKET_BERRIES before additem
    nick12 SLOT HEBREW ENGLISH
                 give gPlayerParty[SLOT] a nickname of up to 12 characters ('_' = space; the Hebrew
                 text on a TEXT_RTL build, the English one otherwise): characters 1-10 in
                 BoxPokemon.nickname (+8), 11 and 12 in PokemonSubstruct0.nickname11 / nickname12
                 (include/pokemon.h:129-142), checksum fixed

Run:  con16.py tour ROM OUT --tours tools/hebrew/emu/tours/r16_contests [--clip] [--only RE]
Saves: HNS_SAVES=hns-tools/emu/saves_all (ladder6_postgame).
"""
import os
import re
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
SCRIPTS = os.path.dirname(HERE)
sys.path.insert(0, os.path.dirname(SCRIPTS))                                # tools/hebrew/emu
sys.path.insert(0, os.path.dirname(os.path.dirname(SCRIPTS)))              # tools/hebrew
for d in ("r9_contests", "r2_summary_info_page_variants", "r2_battle_frontier_facilities"):
    sys.path.insert(0, os.path.join(SCRIPTS, d))
import hns  # noqa: E402
import r9c  # noqa: E402,F401  (contest, Blender and Pokeblock ops)
import rc  # noqa: E402
import sumvar  # noqa: E402
from hns import script_op, HnsError  # noqa: E402

STATUS_SIZE, EFFECT_STRING_ID, STRING_NONE = 28, 19, 0xFF
SUB2_SHEEN = 11
RES_STATUS = 4
LINK_CONTEST_FLAG_IS_LINK = 1
SB1_POKEBLOCKS, POKEBLOCK_SIZE, POKEBLOCKS = 0xF98, 8, 40
PICK = re.compile(r"_r(\d+)_\d+_pick$")
_shot_orig = rc._shot


def _status(emu):
    return emu.r32(emu.r32(emu.sym("gContestResources")) + RES_STATUS)


def _apply(emu, name):
    m = PICK.search(name)
    if not m:
        return
    rnd = int(m.group(1))
    ids = getattr(emu, "_effplan", {}).get(rnd)
    if ids:
        st = _status(emu)
        before = [emu.r8(st + i * STATUS_SIZE + EFFECT_STRING_ID) for i in range(4)]
        if any(b != STRING_NONE for b in before):
            raise HnsError("effplan: round %d effectStringId already %s (layout?)" % (rnd, before))
        for i, v in enumerate(ids):
            if v is not None:
                emu.w8(st + i * STATUS_SIZE + EFFECT_STRING_ID, v)
        print("effplan round %d: effectStringId %s -> %s @%d" % (
            rnd, before, [emu.r8(st + i * STATUS_SIZE + EFFECT_STRING_ID) for i in range(4)], emu.sync()))
    if getattr(emu, "_linkplan", None) == rnd:
        emu.w8(emu.sym("gLinkContestFlags"), LINK_CONTEST_FLAG_IS_LINK)
        print("linkplan round %d: gLinkContestFlags = %d @%d" % (rnd, emu.r8(emu.sym("gLinkContestFlags")), emu.sync()))


def _shot_hook(emu, name):
    p = _shot_orig(emu, name)
    _apply(emu, name)
    return p


rc._shot = _shot_hook


@script_op("effplan")
def _op_effplan(emu, f, path):
    plan = {}
    for spec in f[1:]:
        r, ids = spec.split(":")
        plan[int(r)] = [None if x == "-" else int(x) for x in ids.split(",")]
    emu._effplan = plan
    print("effplan %s" % plan)


@script_op("linkplan")
def _op_linkplan(emu, f, path):
    emu._linkplan = int(f[1])
    print("linkplan round %d" % emu._linkplan)


@script_op("pokeblocks")
def _op_pokeblocks(emu, f, path):
    args = f[1:]
    fill = 0
    if len(args) >= 2 and args[-2] == "fill":
        fill = int(args[-1])
        args = args[:-2]
    blocks = []
    for spec in args:
        c, fl = spec.split(":")
        vals = [int(x) for x in fl.split(",")]
        if len(vals) != 6:
            raise HnsError("pokeblocks: %s needs 6 values" % spec)
        blocks.append(bytes([int(c)] + vals + [0]))
    while len(blocks) < fill:
        blocks.append(blocks[-1])
    if len(blocks) > POKEBLOCKS:
        raise HnsError("pokeblocks: %d blocks, the case holds %d" % (len(blocks), POKEBLOCKS))
    base = emu.sb1() + SB1_POKEBLOCKS
    for i in range(POKEBLOCKS):
        b = blocks[i] if i < len(blocks) else bytes(8)
        emu.w32(base + i * 8, int.from_bytes(b[:4], "little"))
        emu.w32(base + i * 8 + 4, int.from_bytes(b[4:], "little"))
    if emu.read(base, 8 * len(blocks)) != b"".join(blocks):
        raise HnsError("pokeblocks: did not read back")
    print("pokeblocks: %d written @%d" % (len(blocks), emu.sync()))


@script_op("monsheen")
def _op_monsheen(emu, f, path):
    slot, val = int(f[1]), int(f[2], 0)
    addr = sumvar._mon_addr(emu, slot)
    raw = bytearray(emu.read(addr, sumvar.MON_SIZE))
    pers, key, sec = sumvar._decrypt(raw)
    if sumvar._checksum(sec) != int.from_bytes(raw[28:30], "little"):
        raise HnsError("monsheen: slot %d checksum does not match before the edit" % slot)
    s2 = sumvar.SUBOFF[2][pers % 24] * sumvar.SUB
    sec[s2 + SUB2_SHEEN] = val & 0xFF
    csum = sumvar._checksum(sec)
    for i in range(0, len(sec), 4):
        emu.w32(addr + sumvar.SECURE + i, int.from_bytes(sec[i:i + 4], "little") ^ key)
    emu.w16(addr + 28, csum)
    if not sumvar.mon_fields(emu, slot)["checksum_ok"]:
        raise HnsError("monsheen: slot %d checksum wrong after the edit" % slot)
    print("monsheen slot%d = %d @%d" % (slot, val, emu.sync()))


@script_op("pw16")
def _op_pw16(emu, f, path):
    ptr = emu.r32(emu.sym(f[1]))
    if not 0x02000000 <= ptr < 0x03008000:
        raise HnsError("pw16: %s = %08X is not a RAM pointer" % (f[1], ptr))
    off, val = int(f[2], 16), int(f[3], 16)
    emu.w16(ptr + off, val)
    print("pw16 %s(%08X)+%X = %X -> %X @%d" % (f[1], ptr, off, val, emu.r16(ptr + off), emu.sync()))


@script_op("clearpocket")
def _op_clearpocket(emu, f, path):
    pocket = int(f[1]) if f[1].isdigit() else emu.const(f[1])
    bp = emu.sym("gBagPockets") + 8 * pocket
    slots, cap = emu.r32(bp), emu.r16(bp + 4) & 0x3FF
    key = emu.r32(emu.r32(emu.sym("gSaveBlock2Ptr")) + r9c.SB2_ENCKEY) & 0xFFFF
    for i in range(cap):
        emu.w16(slots + 4 * i, 0)
        emu.w16(slots + 4 * i + 2, key)
    print("clearpocket %s: %d slot(s) @%d" % (f[1], cap, emu.sync()))


@script_op("nick12")
def _op_nick12(emu, f, path):
    import bffops
    text = f[2] if "sRtlCharClass" in emu.elf.byname else f[3]
    raw = bffops.encode(text)
    if len(raw) > 12:
        raise HnsError("nick12: %r is %d bytes, at most 12" % (text, len(raw)))
    raw = raw + b"\xff" * (12 - len(raw))
    slot = int(f[1])
    addr = sumvar._mon_addr(emu, slot)
    for i in range(10):
        emu.w8(addr + 8 + i, raw[i])
    mon = bytearray(emu.read(addr, sumvar.MON_SIZE))
    pers, key, sec = sumvar._decrypt(mon)
    if sumvar._checksum(sec) != int.from_bytes(mon[28:30], "little"):
        raise HnsError("nick12: slot %d checksum does not match before the edit" % slot)
    s0 = sumvar._sub(pers, 0)
    w4 = int.from_bytes(sec[s0 + 4:s0 + 8], "little")
    w4 = (w4 & ~(0xFF << 21)) | (raw[10] << 21)
    sec[s0 + 4:s0 + 8] = w4.to_bytes(4, "little")
    w10 = int.from_bytes(sec[s0 + 10:s0 + 12], "little")
    w10 = (w10 & ~(0xFF << 6)) | (raw[11] << 6)
    sec[s0 + 10:s0 + 12] = w10.to_bytes(2, "little")
    csum = sumvar._checksum(sec)
    for i in range(0, len(sec), 4):
        emu.w32(addr + sumvar.SECURE + i, int.from_bytes(sec[i:i + 4], "little") ^ key)
    emu.w16(addr + 28, csum)
    if not sumvar.mon_fields(emu, slot)["checksum_ok"]:
        raise HnsError("nick12: slot %d checksum wrong after the edit" % slot)
    print("nick12 slot%d = %s (%s) @%d" % (slot, text, raw.hex(), emu.sync()))


if __name__ == "__main__":
    sys.argv[0] = hns.__file__
    sys.exit(hns.main())
