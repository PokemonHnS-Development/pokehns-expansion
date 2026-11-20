#!/usr/bin/env python3
"""hns.py plus the ops the field NPC service tours (tours/r5_npcsvc/*.txt) use: everything
scripts/r5_latin/r5lat.py registers (fieldwatch, pick, drive, monset, setmoney, approachnpc, partyinfo,
flags, vars, bagseek, bagpocket, ...), plus:

    fullpocket POCKET ITEM [QTY]   fill every slot of gBagPockets[POCKET] (a POCKET_* constant or its
                                   number) with ITEM x QTY (default 999), so AddBagItem finds no room
                                   for any item of that pocket (the bag-full paths). struct BagPocket is
                                   {struct ItemSlot *itemSlots; u16 capacity:10, id:6} (8 bytes,
                                   include/item.h:88-104); a slot is u16 itemId + u16 quantity XOR the
                                   low half of gSaveBlock2Ptr->encryptionKey.
    fillboxes PARTYIDX             copy party mon PARTYIDX's BoxPokemon (its first 80 bytes, encryption
                                   included) into every empty PC slot (struct PokemonStorage: currentBox
                                   u8, then boxes[TOTAL_BOXES_COUNT=14][30] at +4,
                                   include/pokemon_storage_system.h:20-27), keeping a copy of the boxes
                                   first, so ScriptCheckFreePokemonStorageSpace is FALSE (PC full)
    restoreboxes                   write that copy back
    expectmoney N                  (mart.py) stop unless the money is N
    bwin PREFIX [MAXTURNS]         (bffops.py) win the battle on screen

Run:  npcsvc.py tour ROM OUT --tours <emu>/tours/r5_npcsvc [--clip] [--only RE] [--rtc SECONDS]
"""
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
EMU = os.path.dirname(os.path.dirname(HERE))
sys.path.insert(0, EMU)
sys.path.insert(0, os.path.join(EMU, "scripts", "r5_latin"))
import hns  # noqa: E402
import r5lat  # noqa: E402,F401  (registers the r2-r5 ops)
sys.path.insert(0, os.path.join(EMU, "scripts", "r2_battle_frontier_facilities"))
import bffops  # noqa: E402,F401  (bwin / blose: win or lose the battle on screen)

from hns import script_op, HnsError, _arg  # noqa: E402

SB2_ENCKEY = 0xAC


@script_op("fullpocket")
def _op_fullpocket(emu, f, path):
    pocket, item = emu.const(f[1]), emu.const(f[2])
    qty = _arg(f, 3, 999)
    bp = emu.sym("gBagPockets") + 8 * pocket
    slots, cap = emu.r32(bp), emu.r16(bp + 4) & 0x3FF
    key = emu.r32(emu.r32(emu.sym("gSaveBlock2Ptr")) + SB2_ENCKEY) & 0xFFFF
    for i in range(cap):
        emu.w16(slots + 4 * i, item)
        emu.w16(slots + 4 * i + 2, qty ^ key)
    if emu.r16(slots + 4 * (cap - 1)) != item:
        raise HnsError("fullpocket: the last slot did not read back")
    print("fullpocket %s: %d slot(s) of %s x%d @%d" % (f[1], cap, f[2], qty, emu.sync()))


BOXMON_SIZE, PARTYMON_SIZE, STORAGE_BOXES, BOX_SLOTS = 80, 100, 4, 14 * 30


@script_op("fillboxes")
def _op_fillboxes(emu, f, path):
    src = emu.read(emu.sym("gPlayerParty") + PARTYMON_SIZE * int(f[1]), BOXMON_SIZE)
    base = emu.r32(emu.sym("gPokemonStoragePtr")) + STORAGE_BOXES
    emu.boxes_backup = emu.read(base, BOXMON_SIZE * BOX_SLOTS)
    words = [int.from_bytes(src[k:k + 4], "little") for k in range(0, BOXMON_SIZE, 4)]
    n = 0
    for i in range(BOX_SLOTS):
        if any(emu.boxes_backup[i * BOXMON_SIZE:(i + 1) * BOXMON_SIZE]):
            continue
        for k, w in enumerate(words):
            emu.w32(base + i * BOXMON_SIZE + 4 * k, w)
        n += 1
    print("fillboxes: %d empty slot(s) filled @%d" % (n, emu.sync()))


@script_op("restoreboxes")
def _op_restoreboxes(emu, f, path):
    data = emu.boxes_backup
    base = emu.r32(emu.sym("gPokemonStoragePtr")) + STORAGE_BOXES
    cur = emu.read(base, len(data))
    n = 0
    for k in range(0, len(data), 4):
        if cur[k:k + 4] != data[k:k + 4]:
            emu.w32(base + k, int.from_bytes(data[k:k + 4], "little"))
            n += 1
    if emu.read(base, len(data)) != data:
        raise HnsError("restoreboxes: the boxes did not read back")
    print("restoreboxes: %d word(s) written @%d" % (n, emu.sync()))


if __name__ == "__main__":
    sys.argv[0] = hns.__file__
    sys.exit(hns.main())
