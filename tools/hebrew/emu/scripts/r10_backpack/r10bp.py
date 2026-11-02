#!/usr/bin/env python3
"""hns.py plus the r4 bag ops (scripts/r4_bag/bag.py: fillpocket, bagopen, bagrows, tagrun, bagclose,
partyslot, setunits, expectunits) plus the ops of the r10 backpack tours (tours/r10_backpack):

    pcfill START COUNT [QTY]   PC item storage (gSaveBlock1Ptr->pcItems, SB1+0x49C, 50 slots, plain
                               quantities) = items START..START+COUNT-1 of the whole list (every
                               pocket in pocket order, each pocket's list as fillpocket builds it),
                               every other slot empty. Writes OUT/pcfill_START.json.
    pcrows PREFIX [MAX]        in the open PC WITHDRAW/TOSS list: a shot per row (PREFIX_NNN_CONST,
                               NNN the item's index in the whole list), DOWN until the cursor stops
                               (the CANCEL row is last: PREFIX_cancel_START).
    pocketcycle PREFIX         in the open bag: a shot of every pocket going RIGHT (wrapping), a shot
                               mid-switch (the slide), then LEFT back to the first pocket.
    bagrowsn PREFIX N          N rows of the open pocket from its cursor (shots like bagrows list).
    bagpos POCKET ROW          set gBagPosition (pocket, cursor, scroll) so the next bag opens there,
                               without opening it (the battle and party bags keep the last pocket).
    bagwait                    wait for CB2_BagMenuRun, the bag list input task and a quiet screen.
    bagback                    B out of a bag list opened from battle; wait for the action menu.
    bagto ROW                  DOWN/UP in the open bag list until the cursor is on ROW.
    btill TASK [MAX]           tap B (20 frames apart) until TASK is an active task, then wait quiet.
    setpocket / dumpbag        from scripts/r8_bfe/r8bfe.py (a pocket set to a chosen list).

The r4 lists are filtered here: ITEM_UNUSED_BERRY_1..3 (dummy ids, "????????" / a second SITRUS
BERRY) are left out, and fillpocket TM_HM already keeps only machines with a move.

Usage: r10bp.py tour ROM OUT --tours <emu>/tours/r10_backpack [--clip] [--only RE]
"""
import json
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
EMU = os.path.dirname(os.path.dirname(HERE))
sys.path.insert(0, os.path.join(EMU, "scripts", "r4_bag"))
sys.path.insert(0, EMU)
import bag  # noqa: E402  (registers the r4 bag ops)
sys.path.insert(0, os.path.join(EMU, "scripts", "r8_bfe"))
import r8bfe  # noqa: E402,F401  (setpocket, dumpbag)
import hns  # noqa: E402
from hns import script_op, HnsError, TourTimeout, _arg  # noqa: E402

# The rc12 clip build has no .map next to its ELF, so FILE:NAME statics (berry_tag_screen:Task_HandleInput)
# do not resolve. Its code below the clip-report additions sits at the same addresses as the plain build
# (DoBerryTagScreen, CB2_BerryTagScreen and the three Task_HandleInput statics were compared with nm), so
# fall back to the plain build's pokehns.map in the same folder.
_orig_objfile = hns.Elf.objfile


def _objfile(self, addr):
    if self._ranges is None and not os.path.exists(os.path.splitext(self.path)[0] + ".map"):
        alt = os.path.join(os.path.dirname(self.path), "pokehns.map")
        if os.path.exists(alt):
            real = self.path
            self.path = os.path.join(os.path.dirname(real), "pokehns.elf")
            try:
                return _orig_objfile(self, addr)
            finally:
                self.path = real
    return _orig_objfile(self, addr)


hns.Elf.objfile = _objfile

SKIP = {"ITEM_UNUSED_BERRY_1", "ITEM_UNUSED_BERRY_2", "ITEM_UNUSED_BERRY_3"}
_orig_pocket_list = bag.pocket_list


def pocket_list(emu, pocket):
    out = [it for it in _orig_pocket_list(emu, pocket) if it[1] not in SKIP]
    if pocket == "TM_HM":
        tms = bag._tm_items(emu)
        out = [it for it in out if it[0] in tms]
    return out


bag.pocket_list = pocket_list


def all_items(emu):
    out = []
    for p in bag.POCKETS:
        out += pocket_list(emu, p)
    return out


PC_OFF, PC_COUNT = 0x49C, 50
PAGE = "gPlayerPCItemPageInfo"          # struct PlayerPCItemPageStruct: u16 cursorPos, u16 itemsAbove


@script_op("pcfill")
def _op_pcfill(emu, f, path):
    start, count = int(f[1], 0), int(f[2], 0)
    qty = _arg(f, 3, 999)
    items = all_items(emu)[start:start + count]
    if len(items) > PC_COUNT:
        raise HnsError("pcfill: %d items, 50 slots" % len(items))
    base = emu.sb1() + PC_OFF
    for i in range(PC_COUNT):
        iid = items[i][0] if i < len(items) else 0
        emu.w16(base + 4 * i, iid)
        emu.w16(base + 4 * i + 2, qty if iid else 0)
    got = emu.read(base, 4 * len(items))
    for i, it in enumerate(items):
        if got[4 * i] | got[4 * i + 1] << 8 != it[0]:
            raise HnsError("pcfill: slot %d did not read back" % i)
    with open(os.path.join(emu.outdir, "pcfill_%03d.json" % start), "w") as fh:
        json.dump([dict(index=start + i, id=it[0], const=it[1]) for i, it in enumerate(items)], fh, indent=0)
    emu.pcfill = dict(start=start, items=items)
    print("pcfill %d..%d (%d of %d) @%d" % (start, start + len(items) - 1, len(items), len(all_items(emu)), emu.sync()))


def pc_pos(emu):
    a = emu.sym(PAGE)
    return emu.r16(a) + emu.r16(a + 2)


@script_op("pcrows")
def _op_pcrows(emu, f, path):
    prefix, mx = f[1], _arg(f, 2, 60)
    fill = getattr(emu, "pcfill", None)
    if not fill:
        raise HnsError("pcrows: no pcfill before it")
    start = fill["start"]
    consts = {it[0]: it[1] for it in all_items(emu)}
    index = {it[0]: start + i for i, it in enumerate(fill["items"])}
    n = 0
    while n < mx:
        row = pc_pos(emu)
        iid = emu.r16(emu.sb1() + PC_OFF + 4 * row) if row < PC_COUNT else 0
        if iid:
            name = "%s_%03d_%s" % (prefix, index.get(iid, 999), consts.get(iid, "ITEM_%d" % iid))
        else:
            name = "%s_cancel_%03d" % (prefix, start)
        bag._shot(emu, name)
        n += 1
        before = row
        emu.tap("DOWN", 4)
        try:
            emu.wait_until(lambda: pc_pos(emu) != before, 40, "the PC cursor to move")
        except TourTimeout:
            break
        emu.wait_quiet(900)
        if pc_pos(emu) < before:              # wrapped from CANCEL to the top: back to CANCEL
            emu.tap("UP", 4)
            emu.wait_until(lambda: pc_pos(emu) == before, 40, "the PC cursor to wrap back")
            emu.wait_quiet(900)
            break
    print("pcrows %s: %d row(s), last row %d @%d" % (prefix, n, pc_pos(emu), emu.sync()))


@script_op("pocketcycle")
def _op_pocketcycle(emu, f, path):
    prefix = f[1]
    bp = emu.sym("gBagPosition") + bag.BP_POCKET
    want = emu.sym("Task_BagMenu_HandleInput")
    first = emu.r8(bp)
    seen = []
    for step in range(8):
        p = emu.r8(bp)
        bag._shot(emu, "%s_r%d_%s" % (prefix, step, bag.POCKETS[p] if p < 6 else p))
        seen.append(p)
        emu.tap("RIGHT", 0)
        emu.frames(3)
        emu.shot("%s_r%d_slide" % (prefix, step))
        emu.wait_until(lambda: any(fn == want for _, fn, _ in emu.tasks()), 300, "the bag list after a switch")
        emu.wait_quiet(600)
        if emu.r8(bp) == first:
            break
    for step in range(8):
        emu.tap("LEFT", 4)
        emu.wait_until(lambda: any(fn == want for _, fn, _ in emu.tasks()), 300, "the bag list after a switch")
        emu.wait_quiet(600)
        p = emu.r8(bp)
        bag._shot(emu, "%s_l%d_%s" % (prefix, step, bag.POCKETS[p] if p < 6 else p))
        if p == first:
            break
    print("pocketcycle %s: pockets %s @%d" % (prefix, seen, emu.sync()))


@script_op("bagrowsn")
def _op_bagrowsn(emu, f, path):
    prefix, n = f[1], int(f[2])
    fill = emu.fill
    for k in range(n):
        row = bag.list_pos(emu)
        si = bag.slot_item(emu, row) if row < len(fill["items"]) else None
        bag._shot(emu, "%s_%03d_%s" % (prefix, fill["start"] + row, si[1]) if si else "%s_close_%03d" % (prefix, fill["start"]))
        if k == n - 1:
            break
        before = row
        emu.tap("DOWN", 4)
        try:
            emu.wait_until(lambda: bag.list_pos(emu) != before, 40, "the bag cursor to move")
        except TourTimeout:
            break
        emu.wait_quiet(900)


@script_op("bagpos")
def _op_bagpos(emu, f, path):
    p = bag.POCKETS.index(f[1])
    row = _arg(f, 2, 0)
    bp = emu.sym("gBagPosition")
    scroll = max(0, row - (bag.SHOWN - 1)) if row >= bag.SHOWN else 0
    emu.w8(bp + bag.BP_POCKET, p)
    emu.w16(bp + bag.BP_CURSOR + 2 * p, row - scroll)
    emu.w16(bp + bag.BP_SCROLL + 2 * p, scroll)
    print("bagpos %s %d" % (f[1], row))


@script_op("bagwait")
def _op_bagwait(emu, f, path):
    if not emu.wait32(emu.CB2, emu.sym("CB2_BagMenuRun"), 900):
        raise TourTimeout("bagwait: no CB2_BagMenuRun (callback2 %s)" % emu.cb2_name())
    want = emu.sym("Task_BagMenu_HandleInput")
    emu.wait_until(lambda: any(fn == want for _, fn, _ in emu.tasks()), 900, "bag input task")
    emu.wait_quiet(900)
    print("bagwait: pocket %d row %d @%d" % (emu.r8(emu.sym("gBagPosition") + bag.BP_POCKET), bag.list_pos(emu), emu.sync()))


@script_op("bagback")
def _op_bagback(emu, f, path):
    emu.tap("B", 4)
    bmain = emu.sym("BattleMainCB2")
    emu.wait_until(lambda: emu.cb2() == bmain, 900, "the battle after the bag")
    hns.wait_battle_input(emu, "HandleInputChooseAction", 1200)
    print("bagback @%d" % emu.sync())


@script_op("bagto")
def _op_bagto(emu, f, path):
    want = int(f[1])
    for _ in range(300):
        cur = bag.list_pos(emu)
        if cur == want:
            break
        emu.tap("DOWN" if cur < want else "UP", 4)
        emu.wait_until(lambda: bag.list_pos(emu) != cur, 40, "the bag cursor to move")
        emu.wait_quiet(600)
    if bag.list_pos(emu) != want:
        raise HnsError("bagto %d: cursor on %d" % (want, bag.list_pos(emu)))
    print("bagto %d @%d" % (want, emu.sync()))


@script_op("btill")
def _op_btill(emu, f, path):
    want = emu.sym(f[1])
    for _ in range(_arg(f, 2, 8)):
        if any(fn == want for _, fn, _ in emu.tasks()):
            break
        emu.tap("B", 20)
    if not any(fn == want for _, fn, _ in emu.tasks()):
        raise TourTimeout("btill %s: not reached" % f[1])
    emu.wait_quiet(600)
    print("btill %s @%d" % (f[1], emu.sync()))


if __name__ == "__main__":
    sys.argv[0] = hns.__file__
    sys.exit(hns.main())
