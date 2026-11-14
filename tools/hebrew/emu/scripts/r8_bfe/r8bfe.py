#!/usr/bin/env python3
"""hns.py plus the ops of the r8 bag and field edge-state tours (tours/r8_bfe): a bag pocket set to
a chosen list and the pocket order dumped after a sort.

    r8bfe.py tour ROM OUTDIR --tours <tools/hebrew/emu>/tours/r8_bfe [--clip] [--only RE]

Ops:
  setpocket POCKET ITEM[:QTY] ...   pocket POCKET (POCKET_* name or number) holds exactly these
                                    items in this order (QTY default 1), every other slot empty
  dumpbag NAME POCKET               write OUTDIR/<tour>/NAME.json: the pocket's slots in order
                                    [[itemId, qty], ...] (empty slots dropped)
"""
import json
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(HERE, "..", ".."))                      # tools/hebrew/emu
import hns  # noqa: E402
from hns import script_op, HnsError  # noqa: E402

# enum Pocket with I_COMBINE_BAG_POCKETS TRUE (include/constants/item.h)
POCKETS = {"POCKET_ITEMS": 0, "POCKET_MEDICINE": 1, "POCKET_POKE_BALLS": 2, "POCKET_TM_HM": 3,
           "POCKET_BERRIES": 4, "POCKET_KEY_ITEMS": 5}


def _pocket(emu, name):
    pocket = POCKETS[name] if name in POCKETS else int(name, 0)
    base = emu.sym("gBagPockets") + 8 * pocket          # struct BagPocket {ItemSlot *; u16 capacity:10, id:6}
    slots = emu.r32(base)
    cap = emu.r16(base + 4) & 0x3FF
    key = emu.r32(emu.r32(emu.sym("gSaveBlock2Ptr")) + 0xAC) & 0xFFFF   # SaveBlock2.encryptionKey
    return slots, cap, key


@script_op("setpocket")
def _op_setpocket(emu, f, path):
    slots, cap, key = _pocket(emu, f[1])
    want = []
    for spec in f[2:]:
        name, _, qty = spec.partition(":")
        want.append((emu.const(name), int(qty or "1")))
    if len(want) > cap:
        raise HnsError("setpocket %s: %d items, capacity %d" % (f[1], len(want), cap))
    for i in range(cap):
        item, qty = want[i] if i < len(want) else (0, 0)
        emu.w16(slots + 4 * i, item)
        emu.w16(slots + 4 * i + 2, (qty ^ key) & 0xFFFF)
    print("setpocket %s: %d item(s), capacity %d" % (f[1], len(want), cap))


@script_op("dumpbag")
def _op_dumpbag(emu, f, path):
    slots, cap, key = _pocket(emu, f[2])
    raw = emu.read(slots, 4 * cap)
    out = []
    for i in range(cap):
        item = raw[4 * i] | raw[4 * i + 1] << 8
        qty = (raw[4 * i + 2] | raw[4 * i + 3] << 8) ^ key
        if item:
            out.append([item, qty])
    dest = os.path.join(emu.outdir, f[1] + ".json")
    json.dump({"pocket": f[2], "slots": out}, open(dest, "w"))
    print("dumpbag %s: %d item(s) -> %s" % (f[2], len(out), dest))


if __name__ == "__main__":
    sys.argv[0] = hns.__file__
    sys.exit(hns.main())
