#!/usr/bin/env python3
"""hns.py plus the ops of the r6 item tours (tours/r6_items): field item pickups, hidden items and
the Std_ObtainItem gift windows. Every op records a failure in OUTDIR/r6items.json and goes on with
the next event, so one blocked ball does not end a tour of thirty.

    r6items.py tour ROM OUTDIR --tours <tools/hebrew/emu>/tours/r6_items [--clip] [--only RE]

Ops:
  pick PREFIX FLAG MAP X Y DIR [MAXPAGES]   clear FLAG ('-' for none), warp to (X,Y) on MAP, turn the
                                            player toward DIR (turnobject: a d-pad tap would walk onto
                                            a free tile), press A and photograph every page
                                            (PREFIX_01 ...). Item balls and hidden items alike.
  gift PREFIX ITEM [QTY]                    run `giveitem ITEM, QTY` (Std_ObtainItem) and photograph
                                            its pages; the windows an NPC gift shows after its own lines.
  fillpocket POCKET ITEM                    every slot of bag pocket POCKET becomes ITEM x999, so
                                            checkitemspace/additem fail for ITEM (the bag-full branch).
"""
import json
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(HERE, "..", ".."))                      # tools/hebrew/emu
import hns  # noqa: E402
from hns import script_op, HnsError  # noqa: E402

# enum Pocket with I_COMBINE_BAG_POCKETS TRUE (include/constants/item.h:6-17); the constant resolver
# does not see this enum.
POCKETS = {"POCKET_ITEMS": 0, "POCKET_MEDICINE": 1, "POCKET_POKE_BALLS": 2, "POCKET_TM_HM": 3,
           "POCKET_BERRIES": 4, "POCKET_KEY_ITEMS": 5}
DIRS = {"UP": "DIR_NORTH", "DOWN": "DIR_SOUTH", "LEFT": "DIR_WEST", "RIGHT": "DIR_EAST"}


def _record(emu, prefix, status, detail=""):
    path = os.path.join(emu.outdir, "r6items.json")
    try:
        data = json.load(open(path))
    except (OSError, ValueError):
        data = {}
    data[prefix] = dict(status=status, detail=detail[:300], frame=emu.sync())
    with open(path, "w") as fh:
        json.dump(data, fh, indent=1)


def _recover(emu):
    """Close whatever a failed event left open: B until the player is free in the overworld."""
    for _ in range(12):
        if emu.controllable():
            return True
        emu.tap("B", 20)
        emu.wait_quiet(300)
    return emu.wait_controllable(600, "B")


def _talk(emu, prefix, maxpages, first):
    n, how = emu.talk(prefix, maxpages, first)
    emu.shots = getattr(emu, "shots", []) + ["%s_%02d" % (prefix, i + 1) for i in range(n)]
    return n, how


@script_op("pick")
def _op_pick(emu, f, path):
    prefix, flag, mapname, x, y, d = f[1:7]
    maxpages = int(f[7]) if len(f) > 7 else 6
    try:
        if flag != "-":
            emu.set_flag(emu.const(flag), False)
        g, n = hns.map_lookup(emu.elf, mapname)
        emu.warp(g, n, int(x, 0), int(y, 0))
        hns.event_run(emu, hns.event_body("turnobject OBJ_EVENT_ID_PLAYER, %s; end" % DIRS[d]), "r6_turn")
        emu.frames(4)
        npages, how = _talk(emu, prefix, maxpages, "A")
        if npages == 0:
            raise HnsError("no text (ended %s)" % how)
        if how != "free":
            _recover(emu)
        print("pick %s: %d page(s), ended %s @%d" % (prefix, npages, how, emu.sync()))
        _record(emu, prefix, "OK", "%d pages, ended %s" % (npages, how))
    except HnsError as e:
        print("pick %s: FAILED %s" % (prefix, e))
        try:
            emu.shot("_fail_" + prefix)
        except HnsError:
            pass
        _record(emu, prefix, "FAILED", str(e))
        if not _recover(emu):
            raise


@script_op("gift")
def _op_gift(emu, f, path):
    prefix, item = f[1], f[2]
    qty = f[3] if len(f) > 3 else "1"
    try:
        hns.event_start(emu, hns.event_body("giveitem %s, %s; end" % (item, qty)), "r6_gift")
        npages, how = _talk(emu, prefix, 6, "-")
        if npages == 0:
            raise HnsError("no text (ended %s)" % how)
        if how != "free":
            _recover(emu)
        print("gift %s: %d page(s), ended %s @%d" % (prefix, npages, how, emu.sync()))
        _record(emu, prefix, "OK", "%d pages, ended %s" % (npages, how))
    except HnsError as e:
        print("gift %s: FAILED %s" % (prefix, e))
        _record(emu, prefix, "FAILED", str(e))
        if not _recover(emu):
            raise


@script_op("fillpocket")
def _op_fillpocket(emu, f, path):
    pocket, item = POCKETS.get(f[1]) if f[1] in POCKETS else int(f[1], 0), emu.const(f[2])
    base = emu.sym("gBagPockets") + 8 * pocket          # struct BagPocket {ItemSlot *; u16 capacity:10, id:6}
    slots = emu.r32(base)
    cap = emu.r16(base + 4) & 0x3FF
    key = emu.r32(emu.r32(emu.sym("gSaveBlock2Ptr")) + 0xAC)   # SaveBlock2.encryptionKey
    for i in range(cap):
        emu.w16(slots + 4 * i, item)
        emu.w16(slots + 4 * i + 2, (999 ^ key) & 0xFFFF)
    print("fillpocket %s: %d slots of %s x999" % (f[1], cap, f[2]))


if __name__ == "__main__":
    sys.argv[0] = hns.__file__
    sys.exit(hns.main())
