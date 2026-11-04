#!/usr/bin/env python3
"""Driver for the round-16 field-odds tours (tours/r16_field_odds) and the Emerald-leak stand-ins
(tours/r16_emerald_leak/ems2_*.txt): hns.py with the r2/r3 field ops (r3bf.py: pick, drive, ...;
hilltent_ops.py: dlg, walkto, talkto), the boot/title ops (r2_boot_title_save/bts.py: regionwatch,
setcb2, ...), the party ops (r2_summary_info_page_variants/sumvar.py: monset, sumwait, sumkey), the
decoration ops (r3_bedroom_decoration/decor.py) and FILE:sym lookups for a clip ELF without a linker
map (r11_tents/r11sym.py), plus:

    monotid SLOT OTID     give gPlayerParty[SLOT] another original trainer id: the four substructs are
                          encrypted with personality ^ otId (src/pokemon.c EncryptBoxMon), so they are
                          re-keyed; the checksum covers the decrypted data and stays valid
    partyfree SLOT        make SLOT the first empty party slot: gPlayerPartyCount = SLOT and the
                          struct Pokemon of SLOT..5 zeroed (a gift then lands in SLOT)
    wsym8|wsym16|wsym32 SYMBOL[+HEX] VAL
                          write VAL at SYMBOL (+offset); VAL is a number or a C constant from HNS_SRC
    snapq NAME [MAX]      wait until the text printers are idle and the screen holds still, then snap
    pocketset POCKET ITEM[:QTY] ...
                          empty bag pocket POCKET (bag.py POCKETS) and put exactly these items in it, in
                          this order (slots written as bag.py fillpocket does: itemId, qty ^ encryptionKey)
    decorput SLOT DECOR   write DECOR into slot SLOT of the doll inventory (gDecorationInventories[0].items,
                          the only category H&S has: DECORCAT_COUNT 1, include/decoration.h:43-49)
    showsym8|showsym16|showsym32 SYMBOL[+HEX]
                          print the value at SYMBOL (e.g. gSpecialVar_Result after a script command)
    sethealloc MAP_X X Y  gSaveBlock1Ptr->lastHealLocation = MAP_X (group, num from HNS_SRC), warp id
                          WARP_ID_NONE, X, Y (struct WarpData at SB1+0x20: the saveVersion u16 H&S put
                          before pos moves every field of include/global.h:1205 by 4)
    partyexit [MAX]       leave the party menu for the field: B until callback2 is CB2_Overworld, then B
                          until the player can walk (the start menu the game reopens); clears the stale
                          gMenuCallback so the next 'startmenu' opens the menu again

Run:  odds16.py tour ROM OUT --tours tools/hebrew/emu/tours/r16_field_odds [--clip] [--only RE]
with HNS_SRC = the ROM's tree and HNS_SAVES = hns-tools/emu/saves_all; HNS_MAX_FRAMES caps a tour.
The flash-not-detected tour (fo_flash.txt) needs a ROM copy whose IdentifyFlash returns 1
(noflash.py writes one next to a link to the ELF).
"""
import os
import re
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
SCRIPTS = os.path.dirname(HERE)
sys.path.insert(0, os.path.dirname(SCRIPTS))                      # tools/hebrew/emu
for d in ("r3_frontier", "r2_hill_tents", "r2_boot_title_save", "r2_summary_info_page_variants",
          "r3_bedroom_decoration", "r11_tents", "r2_battle_frontier_facilities", "r4_bag"):
    sys.path.insert(0, os.path.join(SCRIPTS, d))
import hns  # noqa: E402
import r11sym  # noqa: E402,F401
import r3bf  # noqa: E402,F401  (hns + r2sf + r3bf ops)
import hilltent_ops  # noqa: E402,F401  (dlg, walkto, talkto)
import bffops  # noqa: E402,F401  (saveyes, drivex)
import bts  # noqa: E402,F401  (regionwatch, setcb2, softreset, pinsym, ptrpoke)
import sumvar  # noqa: E402,F401  (monset, sumwait, sumkey)
import decor  # noqa: E402,F401  (decorprobe, decorwait)
import bag  # noqa: E402  (fillpocket, bagopen, bagrows)
from hns import script_op, HnsError, _arg  # noqa: E402

MON_SIZE = 0x64
SECURE, SECURE_LEN = 0x20, 48


def const_value(emu, tok):
    """A number (0x.. or decimal), or a #define or an enum entry with an explicit value from HNS_SRC's
    include/constants."""
    try:
        return int(tok, 0)
    except ValueError:
        pass
    cache = getattr(emu, "_odds_consts", None)
    if cache is None:
        cache = emu._odds_consts = {}
    if tok in cache:
        return cache[tok]
    src = hns.src_dir(emu.elf)
    pat = re.compile(r"\s*(?:#define\s+%s\s+\(?\s*|%s\s*=\s*)(0x[0-9A-Fa-f]+|\d+)\b" % (re.escape(tok), re.escape(tok)))
    for root in ("include/constants",):
        for dirpath, _, files in os.walk(os.path.join(src, root)):
            for fn in files:
                if not fn.endswith(".h"):
                    continue
                for line in open(os.path.join(dirpath, fn), errors="replace"):
                    m = pat.match(line)
                    if m:
                        cache[tok] = int(m.group(1), 0)
                        return cache[tok]
    raise HnsError("constant %s not found under %s/include/constants" % (tok, src))


@script_op("monotid")
def _op_monotid(emu, f, path):
    slot, new = int(f[1], 0), int(f[2], 0) & 0xFFFFFFFF
    base = emu.sym("gPlayerParty") + MON_SIZE * slot
    raw = emu.read(base, 8)
    pers = int.from_bytes(raw[0:4], "little")
    old = int.from_bytes(raw[4:8], "little")
    sec = emu.read(base + SECURE, SECURE_LEN)
    delta = (pers ^ old) ^ (pers ^ new)
    out = bytearray()
    for i in range(0, SECURE_LEN, 4):
        w = int.from_bytes(sec[i:i + 4], "little") ^ delta
        out += w.to_bytes(4, "little")
    emu.w32(base + 4, new)
    for i in range(0, SECURE_LEN, 4):
        emu.w32(base + SECURE + i, int.from_bytes(out[i:i + 4], "little"))
    print("monotid %d: %d -> %d" % (slot, old, new))


@script_op("partyfree")
def _op_partyfree(emu, f, path):
    slot = int(f[1], 0)
    party = emu.sym("gPlayerParty")
    for s in range(slot, 6):
        for off in range(0, MON_SIZE, 4):
            emu.w32(party + MON_SIZE * s + off, 0)
    emu.w8(emu.sym("gPlayerPartyCount"), slot)
    print("partyfree %d" % slot)


def _symaddr(emu, tok):
    m = re.match(r"([A-Za-z_:][\w:]*)([+-]0x[0-9A-Fa-f]+|[+-][0-9A-Fa-f]+)?$", tok)
    if not m:
        raise HnsError("bad symbol %s" % tok)
    addr = emu.sym(m.group(1))
    if m.group(2):
        addr += int(m.group(2)[0] + "0x" + m.group(2)[1:].replace("0x", ""), 16)
    return addr


@script_op("wsym8", "wsym16", "wsym32")
def _op_wsym(emu, f, path):
    addr = _symaddr(emu, f[1])
    val = const_value(emu, f[2])
    {"wsym8": emu.w8, "wsym16": emu.w16, "wsym32": emu.w32}[f[0]](addr, val)
    print("%s %s (%08X) = %#x" % (f[0], f[1], addr, val))


@script_op("snapq")
def _op_snapq(emu, f, path):
    emu.wait_quiet(_arg(f, 2, 600))
    emu.frames(2)
    emu.shot(f[1])
    emu.shots = getattr(emu, "shots", []) + [f[1]]
    print("snap %s @%d" % (f[1], emu.sync()))


@script_op("pocketset")
def _op_pocketset(emu, f, path):
    pocket = f[1]
    p = bag.POCKETS.index(pocket)
    items = []
    for tok in f[2:]:
        name, _, q = tok.partition(":")
        items.append((const_value(emu, name), int(q or "1", 0)))
    bp = emu.sym("gBagPockets") + 8 * p
    slots = emu.r32(bp)
    cap = emu.r16(bp + 4) & 0x3FF
    key = emu.r32(emu.r32(emu.sym("gSaveBlock2Ptr")) + bag.SB2_ENCKEY) & 0xFFFF
    for i in range(cap):
        iid, q = items[i] if i < len(items) else (0, 0)
        emu.w16(slots + 4 * i, iid)
        emu.w16(slots + 4 * i + 2, q ^ key)
    print("pocketset %s: %s (capacity %d)" % (pocket, items, cap))


@script_op("decorput")
def _op_decorput(emu, f, path):
    slot, decor = int(f[1], 0), const_value(emu, f[2])
    inv = emu.sym("gDecorationInventories")
    items, size = emu.r32(inv), emu.r8(inv + 4)
    if slot >= size:
        raise HnsError("decorput: slot %d past the doll inventory (%d)" % (slot, size))
    emu.w8(items + slot, decor)
    print("decorput %d = %s (%d)" % (slot, f[2], decor))


@script_op("showsym8", "showsym16", "showsym32")
def _op_showsym(emu, f, path):
    addr = _symaddr(emu, f[1])
    v = {"showsym8": emu.r8, "showsym16": emu.r16, "showsym32": emu.r32}[f[0]](addr)
    print("%s %s = %d (%#x)" % (f[0], f[1], v, v))


SB1_LAST_HEAL = 0x20


@script_op("sethealloc")
def _op_sethealloc(emu, f, path):
    g, n = hns.map_lookup(emu.elf, f[1])
    x, y = int(f[2], 0), int(f[3], 0)
    a = emu.sb1() + SB1_LAST_HEAL
    emu.w8(a, g)
    emu.w8(a + 1, n)
    emu.w8(a + 2, 0xFF)
    emu.w16(a + 4, x)
    emu.w16(a + 6, y)
    print("sethealloc %s (%d.%d) %d,%d: %s" % (f[1], g, n, x, y, emu.read(a, 8).hex()))


@script_op("partyexit")
def _op_partyexit(emu, f, path):
    mx = _arg(f, 1, 900)
    ow = emu.sym("CB2_Overworld")
    for i in range(8):
        if emu.cb2() == ow:
            break
        emu.wait_quiet(300)
        emu.tap("B", 6)
        emu.frames(30)
    emu.wait_until(lambda: emu.cb2() == ow, mx, "the field after the party menu", step=8)
    for i in range(8):
        emu.frames(40)
        if emu.controllable():
            emu.frames(8)
            if emu.controllable():
                break
        emu.tap("B", 6)
    if not emu.controllable():
        raise HnsError("partyexit: not free (callback2 %s)" % emu.cb2_name())
    emu.w32(emu.sym("gMenuCallback"), 0)
    print("partyexit: free @%d" % emu.sync())


if __name__ == "__main__":
    sys.argv[0] = hns.__file__
    sys.exit(hns.main())
