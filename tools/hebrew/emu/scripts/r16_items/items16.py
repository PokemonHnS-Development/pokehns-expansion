#!/usr/bin/env python3
"""Driver for the round-16 item tours (tours/r16_items): hns.py plus the r10 backpack ops
(scripts/r10_backpack/r10bp.py: pcfill, pcrows, bagpos, bagto, ...; with them the r4 bag ops
fillpocket, bagopen, bagclose and the r8 setpocket) plus:

    pclist FILE                 the item list of the next pcfillc / obtainrows: a JSON list of
                                {"const": "ITEM_X", ...} next to the tour
    pcfillc START COUNT [QTY]   PC item storage (gSaveBlock1Ptr->pcItems, SB1+0x49C, 50 plain
                                ItemSlots) = list items START..START+COUNT-1, QTY each (default 2),
                                every other slot empty. Writes OUT/pcfillc_START.json.
    pcset CONST QTY [CONST QTY ...]
                                PC item storage = exactly these slots (none: an empty PC).
    pcwrows PREFIX [MAX]        in the open WITHDRAW list: per row A (quantity 2: the 'how many'
                                prompt, src/player_pc.c ItemStorage_DoItemAction, with the plural
                                fitted by WrapFontIdToFit into ITEMPC_WIN_MESSAGE - 6 px), a shot
                                PREFIX_NNN_CONST (NNN the item's index in the pclist), B, DOWN,
                                until the CANCEL row (PREFIX_cancel_START). Rows go to
                                OUT/pcrows.jsonl. (The prompt's gStringVar1/gStringVar4 are
                                overwritten by the quantity window, so the fit font is not readable
                                here; see var1font.)
    var1font LABEL              log the font WrapFontIdToFit put in front of gStringVar1 (the
                                EXT_CTRL_CODE_FONT prefix, else FONT_NORMAL) into OUT/var1font.jsonl:
                                use it on a screen that keeps gStringVar1 (the toss confirmation,
                                'Withdrew N X.').
    obtainrows START COUNT PREFIX [QTY]
                                for list items START..START+COUNT-1: the event script
                                'giveitem VAR_0x8004, QTY; removeitem VAR_0x8004, QTY; end'
                                (assembled once, gSpecialVar_0x8004 = the item): a shot of
                                'Obtained N X!' while the fanfare plays (PREFIX_NNN_CONST_a) and
                                of the put-away line (PREFIX_NNN_CONST_b), then A. An item that
                                did not fit the bag (additem FALSE, no message) is logged as
                                'noroom' in OUT/obtain.jsonl.

Run (from a work dir; HNS_SRC = the tree the ROM was built from, HNS_SAVES = hns-tools/emu/saves_all):
    items16.py tour ROM OUT --tours tools/hebrew/emu/tours/r16_items [--clip] --only '^it_'
Saves: menuA_base.sav (Cherrygrove Center, every pocket filled), ladder1_newgame.sav (bedroom).
The ct_* tour of the same folder runs with scripts/r5_legends/r5leg.py (bcatch); dexcat.py next to
this file is a driver of its own (category stand-in on the Pokedex INFO page).
"""
import json
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
EMU = os.path.dirname(os.path.dirname(HERE))
sys.path.insert(0, os.path.join(EMU, "scripts", "r10_backpack"))
sys.path.insert(0, EMU)
import r10bp  # noqa: E402,F401  (pcfill, pcrows, bag ops, setpocket)
import bag  # noqa: E402
import hns  # noqa: E402
from hns import script_op, HnsError, TourTimeout, _arg  # noqa: E402

PC_OFF, PC_COUNT = r10bp.PC_OFF, r10bp.PC_COUNT
EXT_CTRL_CODE_BEGIN, EXT_CTRL_CODE_FONT = 0xFC, 0x06        # include/constants/characters.h
FONT_NORMAL = 1                                             # include/text.h enum
FONTS = {0: "FONT_SMALL", 1: "FONT_NORMAL", 2: "FONT_SHORT", 7: "FONT_NARROW", 8: "FONT_SMALL_NARROW",
         10: "FONT_NARROWER", 11: "FONT_SMALL_NARROWER", 12: "FONT_SHORT_NARROW", 13: "FONT_SHORT_NARROWER"}


def _jsonl(emu, name, rec):
    with open(os.path.join(emu.outdir, name), "a") as fh:
        fh.write(json.dumps(rec, ensure_ascii=False) + "\n")


@script_op("pclist")
def _op_pclist(emu, f, path):
    src = os.path.join(os.path.dirname(os.path.abspath(path)), f[1])
    emu.itemlist = json.load(open(src, encoding="utf-8"))
    print("pclist %s: %d items" % (f[1], len(emu.itemlist)))


def _write_pc(emu, slots):
    base = emu.sb1() + PC_OFF
    for i in range(PC_COUNT):
        iid, qty = slots[i] if i < len(slots) else (0, 0)
        emu.w16(base + 4 * i, iid)
        emu.w16(base + 4 * i + 2, qty if iid else 0)
    got = emu.read(base, 4 * max(1, len(slots)))
    for i, (iid, _) in enumerate(slots):
        if got[4 * i] | got[4 * i + 1] << 8 != iid:
            raise HnsError("PC slot %d did not read back" % i)


@script_op("pcfillc")
def _op_pcfillc(emu, f, path):
    start, count, qty = int(f[1], 0), int(f[2], 0), _arg(f, 3, 2)
    items = emu.itemlist[start:start + count]
    if len(items) > PC_COUNT:
        raise HnsError("pcfillc: %d items, 50 slots" % len(items))
    ids = [emu.const(it["const"]) for it in items]
    _write_pc(emu, [(i, qty) for i in ids])
    rows = [dict(index=start + k, id=ids[k], const=it["const"], string_id=it.get("id")) for k, it in enumerate(items)]
    with open(os.path.join(emu.outdir, "pcfillc_%03d.json" % start), "w") as fh:
        json.dump(rows, fh, indent=0)
    emu.pcfillc = dict(start=start, rows=rows)
    print("pcfillc %d..%d (%d) qty %d @%d" % (start, start + len(items) - 1, len(items), qty, emu.sync()))


@script_op("pcset")
def _op_pcset(emu, f, path):
    slots = [(emu.const(f[i]), int(f[i + 1], 0)) for i in range(1, len(f) - 1, 2)]
    _write_pc(emu, slots)
    print("pcset %s @%d" % (slots, emu.sync()))


def _task_on(emu, name):
    want = emu.sym(name)
    return any(fn == want for _, fn, _ in emu.tasks())


def _font_of(buf):
    if len(buf) >= 3 and buf[0] == EXT_CTRL_CODE_BEGIN and buf[1] == EXT_CTRL_CODE_FONT:
        return buf[2]
    return FONT_NORMAL


@script_op("pcwrows")
def _op_pcwrows(emu, f, path):
    prefix, mx = f[1], _arg(f, 2, 60)
    fill = getattr(emu, "pcfillc", None)
    if not fill:
        raise HnsError("pcwrows: no pcfillc before it")
    byid = {r["id"]: r for r in fill["rows"]}
    n = 0
    while n < mx:
        row = r10bp.pc_pos(emu)
        iid = emu.r16(emu.sb1() + PC_OFF + 4 * row) if row < PC_COUNT else 0
        if not iid:
            bag._shot(emu, "%s_cancel_%03d" % (prefix, fill["start"]))
            break
        r = byid.get(iid, dict(index=999, const="ITEM_%d" % iid, string_id=None))
        name = "%s_%03d_%s" % (prefix, r["index"], r["const"])
        emu.tap("A", 4)
        emu.wait_until(lambda: _task_on(emu, "ItemStorage_HandleQuantityRolling"), 120, "the how-many prompt")
        emu.wait_quiet(600)
        bag._shot(emu, name)
        _jsonl(emu, "pcrows.jsonl", dict(shot=name, const=r["const"], string_id=r["string_id"]))
        emu.tap("B", 4)
        emu.wait_until(lambda: _task_on(emu, "ItemStorage_ProcessInput"), 120, "the PC list after B")
        emu.wait_quiet(600)
        n += 1
        before = row
        emu.tap("DOWN", 4)
        try:
            emu.wait_until(lambda: r10bp.pc_pos(emu) != before, 40, "the PC cursor to move")
        except TourTimeout:
            break
        emu.wait_quiet(900)
        if r10bp.pc_pos(emu) < before:
            break
    print("pcwrows %s: %d row(s) @%d" % (prefix, n, emu.sync()))


@script_op("var1font")
def _op_var1font(emu, f, path):
    raw = emu.read(emu.sym("gStringVar1"), 64)
    font = _font_of(raw)
    end = raw.find(b"\xff")
    rec = dict(label=f[1], font=font, font_name=FONTS.get(font, str(font)), var1=raw[:end if end >= 0 else 64].hex())
    _jsonl(emu, "var1font.jsonl", rec)
    print("var1font %s: %s @%d" % (f[1], rec["font_name"], emu.sync()))


def _event_cached(emu, key, body):
    """hns.event_start with the assembled bytes kept per session (one evasm run per script)."""
    import evasm
    cache = emu.__dict__.setdefault("_ev_cache", {})
    addr = emu.sym(evasm.RAM_BUFFER)
    if key not in cache:
        data, _ = evasm.assemble(body, addr, emu.elf.path, src=hns.src_dir(emu.elf), name=key)
        if len(data) > emu.elf.size(evasm.RAM_BUFFER):
            raise HnsError("event %s: %d bytes do not fit" % (key, len(data)))
        cache[key] = data + b"\0" * (-len(data) % 4)
    if not emu.controllable():
        raise HnsError("event %s: the player is not controllable (callback2 %s)" % (key, emu.cb2_name()))
    ctx = emu.sym("sGlobalScriptContext")
    if emu.elf.size("sGlobalScriptContext") != 0x74 or emu.r32(ctx + 0x5C) != emu.sym("gScriptCmdTable"):
        raise HnsError("event: struct ScriptContext changed (see ladder.py CTX_*)")
    padded = cache[key]
    for i in range(0, len(padded), 4):
        emu.w32(addr + i, int.from_bytes(padded[i:i + 4], "little"))
    emu.w32(ctx + 0, 1 << 8)
    emu.w32(ctx + 4, 0)
    emu.w32(ctx + 8, addr)
    emu.w8(emu.sym("sLockFieldControls"), 1)
    emu.w8(emu.sym("sGlobalScriptContextStatus"), 0)
    emu.frames(1)


@script_op("obtainrows")
def _op_obtainrows(emu, f, path):
    start, count, prefix, qty = int(f[1], 0), int(f[2], 0), f[3], _arg(f, 4, 2)
    body = "giveitem VAR_0x8004, %d\nremoveitem VAR_0x8004, %d\nend\n" % (qty, qty)
    v4, v7 = emu.sym("gSpecialVar_0x8004"), emu.sym("gSpecialVar_0x8007")
    status = emu.sym("sGlobalScriptContextStatus")
    done = 0
    for k, it in enumerate(emu.itemlist[start:start + count]):
        idx = start + k
        iid = emu.const(it["const"])
        name = "%s_%03d_%s" % (prefix, idx, it["const"])
        emu.w16(v4, iid)
        _event_cached(emu, "obtain%d" % qty, body)
        emu.frames(30)
        emu.wait_quiet(600)
        rec = dict(index=idx, const=it["const"], string_id=it.get("id"))
        if emu.r16(v7) != 1:
            rec["result"] = "noroom"
        else:
            emu.frames(2)
            emu.shot(name + "_a")
            emu.wait_until(emu.wants_key, 900, "the put-away line")
            emu.snap(name + "_b")
            emu.tap("A", 4)
            rec["result"] = "ok"
        emu.wait_until(lambda: emu.r8(status) == 2 and emu.controllable(), 600, "the obtain script to end", step=4)
        _jsonl(emu, "obtain.jsonl", rec)
        done += 1
    print("obtainrows %s %d..%d: %d @%d" % (prefix, start, start + count - 1, done, emu.sync()))


if __name__ == "__main__":
    sys.argv[0] = hns.__file__
    sys.exit(hns.main())
