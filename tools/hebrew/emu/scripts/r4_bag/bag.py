#!/usr/bin/env python3
"""hns.py plus tour ops for walking every row of every bag pocket (src/item_menu.c).

    fillpocket POCKET QTY START COUNT
                        empty bag pocket POCKET (ITEMS, MEDICINE, POKE_BALLS, TM_HM, BERRIES,
                        KEY_ITEMS) and fill it with items START..START+COUNT-1 of that pocket's item
                        list, QTY each. The list is every item id whose gItemsInfo[].pocket is
                        POCKET, in id order, read from the ROM under test (so it is the same list the
                        debug Fill uses, src/debug.c:3879). Slots are written the way
                        BagPocket_SetSlotDataGeneric does (src/item.c:79): itemId, quantity XOR
                        gSaveBlock2Ptr->encryptionKey. Writes OUT/fill_POCKET_START.json.
    bagopen POCKET [ROW]
                        gBagPosition.pocket = POCKET, cursor/scroll so that ROW is selected
                        (default 0), then START > BAG and wait for the list input task.
    bagrows PREFIX MODE [MAX]
                        one screenshot per row of the open pocket, DOWN until the cursor stops
                        (the CLOSE BAG row is last). Shots are PREFIX_NNN_ITEMCONST, NNN being the
                        item's index in the whole pocket list (fillpocket START + row), and
                        PREFIX_close_START for the CLOSE BAG row. MODE:
                          list   the row only
                          ctx    also A (context menu; on TM_HM the move panel), shot _ctx, B
                          key    ctx, and for ItemUseOutOfBattle_CannotUse items also USE, shot
                                 _use (the "Dad's advice" message), A
    tagrun PREFIX       from the BERRIES list on row 0: A > CHECK TAG, a shot of the tag, then DOWN
                        on the tag screen (TryChangeDisplayedBerry, src/berry_tag_screen.c:588)
                        with a shot per berry until it stops; B back to the bag.
    setunits 0|1        gSaveBlock3Ptr->challengeSettings.unitSystem (include/global.h:262; bit 6
                        of SB3+0x10, offsetof measured for r3_marts): 0 metric, 1 imperial
                        (src/berry_tag_screen.c:431).
    expectunits 0|1     stop unless unitSystem has that value

Usage: bag.py <hns.py args>   (e.g. bag.py tour ROM OUT --tours DIR --only RE --clip)
"""
import json
import os
import struct
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
EMU = os.path.dirname(os.path.dirname(HERE))
sys.path.insert(0, EMU)
import hns  # noqa: E402
from hns import script_op, HnsError, TourTimeout, _arg  # noqa: E402

POCKETS = ["ITEMS", "MEDICINE", "POKE_BALLS", "TM_HM", "BERRIES", "KEY_ITEMS"]
SB2_ENCKEY = 0xAC
SB3_UNITS = 0x10          # first byte of challengeSettings; unitSystem is bit 6
UNITS_BIT = 6
# struct BagPosition (include/item_menu.h:59): exitCallback, location, pocket, pocketSwitchArrowPos,
# cursorPosition[6], scrollPosition[6]
BP_POCKET, BP_CURSOR, BP_SCROLL = 5, 8, 0x14
SHOWN = 8                 # gBagMenu->numShownItems for a full pocket


def _rom_items(emu):
    """[(id, const, pocket index, fieldUse symbol)] from gItemsInfo in the ROM file (struct
    ItemInfo, include/item.h:67: 44 bytes; pocket = bits 3-7 of byte 0x1E)."""
    cache = getattr(emu, "_items", None)
    if cache:
        return cache
    names = {}
    vals, cur = {}, -1
    import re
    src = hns.src_dir(emu.elf)
    for line in open(os.path.join(src, "include", "constants", "items.h"), encoding="utf-8"):
        m = re.match(r"\s+((?:ITEM_|FIRST_|ITEMS_COUNT)\w*)\s*(?:=\s*([^,/]+))?,", line)
        if not m:
            continue
        n, e = m.group(1), m.group(2)
        if n == "ITEM_FIELD_ARROW":
            continue
        if n == "ITEMS_COUNT":
            vals[n] = cur + 1
            continue
        if e is None:
            cur += 1
        else:
            cur = eval(re.sub(r"(?:ITEM|FIRST)_\w+", lambda mm: str(vals[mm.group(0)]), e.strip()))
        vals[n] = cur
        if not n.startswith("FIRST_"):
            names.setdefault(cur, n)
    count = vals["ITEMS_COUNT"]
    base, size = emu.elf.sym("gItemsInfo"), emu.elf.size("gItemsInfo")
    if size != count * 44:
        raise HnsError("gItemsInfo is %d bytes for %d items; struct ItemInfo changed" % (size, count))
    data = open(emu.rom, "rb").read()[base - 0x08000000: base - 0x08000000 + size]
    out = []
    for i in range(count):
        fuse = struct.unpack_from("<I", data, i * 44 + 8)[0]
        out.append((i, names.get(i, "ITEM_%d" % i), data[i * 44 + 0x1E] >> 3, emu.elf.where(fuse & ~1)))
    emu._items = out
    return out


def pocket_list(emu, pocket):
    p = POCKETS.index(pocket)
    return [it for it in _rom_items(emu)[1:] if it[2] == p]


def _bagpos(emu):
    return emu.sym("gBagPosition")


def list_pos(emu):
    bp = _bagpos(emu)
    p = emu.r8(bp + BP_POCKET)
    return emu.r16(bp + BP_CURSOR + 2 * p) + emu.r16(bp + BP_SCROLL + 2 * p)


def slot_item(emu, row):
    """(id, const, fieldUse) of the item in bag slot ROW of the open pocket (the bag sorts the TM and
    berry pockets by index when it opens, src/item_menu.c:1211, so the slot, not the fill order, names
    the row), or None past the last item."""
    fill = emu.fill
    p = POCKETS.index(fill["pocket"])
    slots = emu.r32(emu.sym("gBagPockets") + 8 * p)
    iid = emu.r16(slots + 4 * row)
    if not iid:
        return None
    it = _rom_items(emu)[iid]
    return iid, it[1], it[3]


def _tm_items(emu):
    """Item ids in gTMHMItemMoveIds (struct TmHmIndexKey {itemId, moveId}, include/item.h:96) with a move."""
    base, size = emu.elf.sym("gTMHMItemMoveIds"), emu.elf.size("gTMHMItemMoveIds")
    data = open(emu.rom, "rb").read()[base - 0x08000000: base - 0x08000000 + size]
    return {struct.unpack_from("<HH", data, i)[0] for i in range(0, size, 4) if struct.unpack_from("<HH", data, i)[1]}


def _shot(emu, name):
    emu.wait_quiet(900)
    emu.frames(2)
    emu.shot(name)
    emu.shots = getattr(emu, "shots", []) + [name]


@script_op("fillpocket")
def _op_fillpocket(emu, f, path):
    pocket, qty, start, count = f[1], int(f[2], 0), int(f[3], 0), int(f[4], 0)
    p = POCKETS.index(pocket)
    allp = pocket_list(emu, pocket)
    if pocket == "TM_HM":                         # only machines with a move, as the debug Fill
        tms = _tm_items(emu)                      # (src/debug.c:3905)
        allp = [it for it in allp if it[0] in tms]
    items = allp[start:start + count]
    bp = emu.sym("gBagPockets") + 8 * p           # struct BagPocket: itemSlots, capacity:10, id:6
    slots = emu.r32(bp)
    cap = emu.r16(bp + 4) & 0x3FF
    if len(items) > cap:
        raise HnsError("fillpocket %s: %d items, capacity %d" % (pocket, len(items), cap))
    key = emu.r32(emu.r32(emu.sym("gSaveBlock2Ptr")) + SB2_ENCKEY) & 0xFFFF
    for i in range(cap):
        iid = items[i][0] if i < len(items) else 0
        emu.w16(slots + 4 * i, iid)
        emu.w16(slots + 4 * i + 2, (qty if iid else 0) ^ key)
    got = emu.read(slots, 4 * len(items))
    for i, it in enumerate(items):
        if got[4 * i] | got[4 * i + 1] << 8 != it[0]:
            raise HnsError("fillpocket %s: slot %d did not read back" % (pocket, i))
    with open(os.path.join(emu.outdir, "fill_%s_%03d.json" % (pocket, start)), "w") as fh:
        json.dump([dict(index=start + i, id=it[0], const=it[1], fieldUse=it[3]) for i, it in enumerate(items)],
                  fh, indent=0)
    emu.fill = dict(pocket=pocket, start=start, items=items)
    print("fillpocket %s %d..%d (%d of %d, capacity %d) @%d"
          % (pocket, start, start + len(items) - 1, len(items), len(pocket_list(emu, pocket)), cap, emu.sync()))


@script_op("bagopen")
def _op_bagopen(emu, f, path):
    p = POCKETS.index(f[1])
    row = _arg(f, 2, 0)
    bp = _bagpos(emu)
    scroll = max(0, row - (SHOWN - 1)) if row >= SHOWN else 0
    emu.w8(bp + BP_POCKET, p)
    emu.w16(bp + BP_CURSOR + 2 * p, row - scroll)
    emu.w16(bp + BP_SCROLL + 2 * p, scroll)
    emu.start_menu_cursor("BAG")
    if not emu.wait32(emu.CB2, emu.sym("CB2_BagMenuRun"), 900):
        raise TourTimeout("bagopen: no CB2_BagMenuRun (callback2 %s)" % emu.cb2_name())
    want = emu.sym("Task_BagMenu_HandleInput")
    emu.wait_until(lambda: any(fn == want for _, fn, _ in emu.tasks()), 900, "bag input task")
    emu.wait_quiet(900)
    if list_pos(emu) != row:
        raise HnsError("bagopen %s %d: cursor at %d" % (f[1], row, list_pos(emu)))
    print("bagopen %s row %d @%d" % (f[1], row, emu.sync()))


def _wait_task(emu, names, maxf=900, what=None):
    want = {emu.sym(n): n for n in names}
    found = []

    def cond():
        found[:] = [want[fn] for _, fn, _ in emu.tasks() if fn in want]
        return bool(found)
    emu.wait_until(cond, maxf, what or "/".join(names))
    return found[0]


def _back_to_list(emu):
    _wait_task(emu, ["Task_BagMenu_HandleInput"], 900)
    emu.wait_quiet(900)


def _after_message(emu, base):
    """A through a message until the bag list takes input again; a shot of every further page."""
    want = emu.sym("Task_BagMenu_HandleInput")
    for page in range(2, 8):
        emu.wait_until(lambda: emu.wants_key() or any(fn == want for _, fn, _ in emu.tasks()), 900,
                       "the bag list or the next page")
        if any(fn == want for _, fn, _ in emu.tasks()):
            break
        _shot(emu, "%s%d" % (base, page))
        emu.tap("A", 4)
    _back_to_list(emu)


CTX_TASKS = ["Task_ItemContext_MultipleRows", "Task_ItemContext_SingleRow"]


@script_op("bagrows")
def _op_bagrows(emu, f, path):
    prefix, mode, mx = f[1], f[2], _arg(f, 3, 400)
    fill = getattr(emu, "fill", None)
    if not fill:
        raise HnsError("bagrows: no fillpocket before it")
    items, start = fill["items"], fill["start"]
    n = 0
    while n < mx:
        row = list_pos(emu)
        si = slot_item(emu, row) if row < len(items) else None
        if si:
            iid, const, fuse = si
            base = "%s_%03d_%s" % (prefix, start + row, const)
        else:
            iid, base = None, "%s_close_%03d" % (prefix, start)
        _shot(emu, base)
        n += 1
        if iid is not None and mode in ("ctx", "key"):
            emu.tap("A", 4)
            _wait_task(emu, CTX_TASKS, 300)
            _shot(emu, base + "_ctx")
            if mode == "key" and fuse == "ItemUseOutOfBattle_CannotUse":
                emu.tap("A", 4)                       # USE (the top left entry)
                emu.wait_until(emu.wants_key, 900, "the cannot-use message")
                _shot(emu, base + "_use")
                emu.tap("A", 4)
                _after_message(emu, base + "_use")
            else:
                emu.tap("B", 4)
                _back_to_list(emu)
        before = row
        emu.tap("DOWN", 4)
        try:
            emu.wait_until(lambda: list_pos(emu) != before, 40, "the bag cursor to move")
        except TourTimeout:
            break
        emu.wait_quiet(900)
        if list_pos(emu) < before:            # the list wrapped from CLOSE BAG to the top
            emu.tap("UP", 4)
            emu.wait_until(lambda: list_pos(emu) == before, 40, "the bag cursor to wrap back")
            emu.wait_quiet(900)
            break
    print("bagrows %s: %d row(s), last row %d @%d" % (prefix, n, list_pos(emu), emu.sync()))


@script_op("tagrun")
def _op_tagrun(emu, f, path):
    prefix = f[1]
    fill = getattr(emu, "fill", None)
    if not fill or fill["pocket"] != "BERRIES":
        raise HnsError("tagrun: fillpocket BERRIES first")
    items, start = fill["items"], fill["start"]
    emu.tap("A", 4)
    _wait_task(emu, CTX_TASKS, 300)
    emu.wait_quiet(300)
    emu.tap("DOWN", 4)
    emu.tap("DOWN", 4)
    emu.wait_quiet(300)
    emu.tap("A", 4)                                   # CHECK TAG
    if not emu.wait32(emu.CB2, emu.sym("CB2_BerryTagScreen"), 900):
        raise TourTimeout("tagrun: no CB2_BerryTagScreen (callback2 %s)" % emu.cb2_name())
    inp = "berry_tag_screen:Task_HandleInput"
    n = 0
    while True:
        _wait_task(emu, [inp], 900)
        emu.wait_quiet(900)
        emu.frames(20)
        row = list_pos(emu)
        si = slot_item(emu, row)
        _shot(emu, "%s_%03d_%s" % (prefix, start + row, si[1] if si else "row%d" % row))
        n += 1
        emu.tap("DOWN", 4)
        try:
            emu.wait_until(lambda: list_pos(emu) != row, 30, "the berry tag to change")
        except TourTimeout:
            break
    emu.tap("B", 4)
    if not emu.wait32(emu.CB2, emu.sym("CB2_BagMenuRun"), 900):
        raise TourTimeout("tagrun: did not return to the bag")
    _back_to_list(emu)
    print("tagrun %s: %d tag(s), stopped on row %d @%d" % (prefix, n, list_pos(emu), emu.sync()))


@script_op("bagclose")
def _op_bagclose(emu, f, path):
    """bagclose: B out of the bag list, wait until the start menu is back."""
    emu.tap("B", 4)
    if not emu.wait32(emu.CB2, emu.sym("CB2_Overworld"), 900):
        raise TourTimeout("bagclose: no CB2_Overworld (callback2 %s)" % emu.cb2_name())
    if not emu.wait32(emu.sym("gMenuCallback"), emu.sym("HandleStartMenuInput"), 600):
        raise TourTimeout("bagclose: the start menu did not come back")
    emu.frames(4)
    print("bagclose @%d" % emu.sync())


@script_op("partyslot")
def _op_partyslot(emu, f, path):
    """partyslot N: DOWN in the party menu until gPartyMenu.slotId == N (struct PartyMenu,
    include/party_menu.h:9: exitCallback, task, a bitfield byte, then s8 slotId at +9)."""
    want = int(f[1])
    a = emu.sym("gPartyMenu") + 9
    for _ in range(12):
        if emu.r8(a) == want:
            break
        emu.tap("DOWN", 6)
        emu.wait_quiet(300)
    if emu.r8(a) != want:
        raise HnsError("partyslot %d: cursor on %d" % (want, emu.r8(a)))
    print("partyslot %d ok @%d" % (want, emu.sync()))


def _units_addr(emu):
    return emu.r32(emu.sym("gSaveBlock3Ptr")) + SB3_UNITS


@script_op("setunits")
def _op_setunits(emu, f, path):
    a = _units_addr(emu)
    old = emu.r8(a)
    emu.w8(a, (old & ~(1 << UNITS_BIT)) | ((int(f[1]) & 1) << UNITS_BIT))
    print("setunits %s: byte %08X %02X -> %02X" % (f[1], a, old, emu.r8(a)))


@script_op("expectunits")
def _op_expectunits(emu, f, path):
    v = (emu.r8(_units_addr(emu)) >> UNITS_BIT) & 1
    if v != int(f[1]):
        raise HnsError("expectunits %s: unitSystem is %d" % (f[1], v))
    print("expectunits %s ok" % f[1])


if __name__ == "__main__":
    sys.argv[0] = hns.__file__
    sys.exit(hns.main())
