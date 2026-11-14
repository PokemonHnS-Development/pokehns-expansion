#!/usr/bin/env python3
"""Ops for the Hebrew-born identity tours (tours/r5_heid): a Hebrew player name, the default
Hebrew box names and a box renamed on the naming screen. On top of rivalops.py (setname,
nametype, bffops/r3bf ops), pcs.py (pcwait, pcgoto, boxprobe) and ladder.py (playtime, event).
Run:  heidops.py tour ROM OUT --tours tools/hebrew/emu/tours/r5_heid [--clip] [--only RE]

    setplayer HE EN          write HE (TEXT_RTL build) or EN (English build) into
                             gSaveBlock2Ptr->playerName (+0), EOS-terminated and FF-padded to 8;
                             '_' stands for a space
    setot SLOT [SLOT ...]    copy the player's name (7 bytes) into gPlayerParty[SLOT]'s otName
                             (struct BoxPokemon +0x14, outside the encrypted substructs, so the
                             checksum is unchanged): the party reads as caught by this player
    boxnames                 print every box name (gPokemonStoragePtr->boxNames, +0x8344)
    nameclear PREFIX         on a naming screen, press B until the entry is empty; one shot
                             (PREFIX) at the end
    nametext PREFIX HE EN    type HE / EN key by key on the naming screen, switching keyboard
                             pages with SELECT and moving the cursor by the position the cursor
                             sprite really has; checks the entry after every key and takes a
                             shot per key (PREFIX_N)
"""
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
EMU = os.path.join(HERE, "..", "..")
sys.path.insert(0, EMU)
sys.path.insert(0, os.path.join(HERE, "..", "r2_rival_names"))
sys.path.insert(0, os.path.join(HERE, "..", "r2_pc_storage"))
import hns  # noqa: E402

import rivalops  # noqa: E402,F401  (setname, nametype, bwin, drivex, pick, ...)
import pcs  # noqa: E402,F401  (pcwait, pcgoto, boxprobe)
import bffops  # noqa: E402
import r3bf  # noqa: E402
from hns import script_op, HnsError  # noqa: E402

SB2_NAME_LEN = 8
OT_OFF, OT_LEN = 0x14, 7
MON_SIZE = 0x64
BOXNAMES_OFF, BOXNAME_SIZE, BOXES = 0x8344, 9, 14

# struct NamingScreenData (src/naming_screen.c:160-189): textBuffer +0x1800, state +0x1E10,
# windows[5], 5 u16, bgToReveal, bgToHide, then currentPage +0x1E22 and cursorSpriteId +0x1E23.
NS_TEXTBUF, NS_PAGE, NS_CURSOR = 0x1800, 0x1E22, 0x1E23
SPRITE_SIZE, SPRITE_DATA = 0x44, 0x2E
# Keyboard pages (KBPAGE_*): 0 symbols, 1 first letter page, 2 second letter page.
SYMBOLS = ["01234   ", "56789   ", "!?♂♀/-  ", "…“”‘'   "]
PAGES_HE = {1: rivalops.HE_ROWS, 2: ["ABCDEF .", "GHIJKL ,", "MNOPQRS ", "TUVWXYZ "], 0: SYMBOLS}
PAGES_EN = {1: ["ABCDEF .", "GHIJKL ,", "MNOPQRS ", "TUVWXYZ "],
            2: ["abcdef .", "ghijkl ,", "mnopqrs ", "tuvwxyz "], 0: SYMBOLS}
COLS = {0: 6, 1: 8, 2: 8}


def pick(emu, f, i):
    return f[i if rivalops.rtl(emu) else i + 1]


def decode(emu, bs):
    cm = bffops.charmap()
    rev = {}
    for k, v in cm.chars.items():
        if len(v) == 1 and len(k) == 1:
            rev.setdefault(v, k)
            if "א" <= k <= "ת" or k.isascii():
                rev[v] = k
    out = ""
    for b in bs:
        if b == 0xFF:
            break
        out += rev.get(bytes([b]), "<%02X>" % b)
    return out


@script_op("setplayer")
def _op_setplayer(emu, f, path):
    name = pick(emu, f, 1)
    data = (bffops.encode(name) + b"\xff" * SB2_NAME_LEN)[:SB2_NAME_LEN]
    base = emu.sb2()
    for i, b in enumerate(data):
        emu.w8(base + i, b)
    print("setplayer %r (%s)" % (name, data.hex()))


@script_op("setot")
def _op_setot(emu, f, path):
    name = emu.read(emu.sb2(), OT_LEN)
    party = emu.sym("gPlayerParty")
    for s in f[1:]:
        base = party + MON_SIZE * int(s) + OT_OFF
        for i, b in enumerate(name):
            emu.w8(base + i, b)
    print("setot %s = %r" % (" ".join(f[1:]), decode(emu, name)))


@script_op("boxnames")
def _op_boxnames(emu, f, path):
    st = emu.r32(emu.sym("gPokemonStoragePtr"))
    names = []
    for b in range(BOXES):
        raw = emu.read(st + BOXNAMES_OFF + b * BOXNAME_SIZE, BOXNAME_SIZE)
        names.append("%d=%r" % (b + 1, decode(emu, raw)))
    line = "boxnames: current %d; %s" % (emu.r8(st) + 1, " ".join(names))
    print(line)
    emu.log.append(line)


def _ns(emu):
    return rivalops.naming_ptr(emu)


def _cursor(emu):
    p = _ns(emu)
    sid = emu.r8(p + NS_CURSOR)
    spr = emu.sym("gSprites") + SPRITE_SIZE * sid
    x = emu.r16(spr + SPRITE_DATA)
    y = emu.r16(spr + SPRITE_DATA + 2)
    return (x - 0x10000 if x & 0x8000 else x), (y - 0x10000 if y & 0x8000 else y)


def _entry(emu):
    return bytes(emu.read(_ns(emu) + NS_TEXTBUF, 16))


@script_op("nameclear")
def _op_nameclear(emu, f, path):
    for _ in range(20):
        if _entry(emu)[0] == 0xFF:
            break
        emu.tap("B", 4)
        rivalops.wait_naming(emu)
    else:
        raise HnsError("nameclear: the entry is still %s" % _entry(emu).hex())
    r3bf._shot(emu, f[1])
    print("nameclear ok @%d" % emu.sync())


@script_op("nametext")
def _op_nametext(emu, f, path):
    prefix = f[1]
    text = pick(emu, f, 2).replace("_", " ")
    pages = PAGES_HE if rivalops.rtl(emu) else PAGES_EN
    start = _entry(emu).find(b"\xff")
    want = bffops.encode(text)
    for i, ch in enumerate(text):
        page = emu.r8(_ns(emu) + NS_PAGE)
        spots = [(pg, c, r) for pg, rows in pages.items() for r, row in enumerate(rows)
                 for c, k in enumerate(row) if k == ch and c < COLS[pg]]
        if not spots:
            raise HnsError("nametext: %r is on no keyboard page" % ch)
        spots.sort(key=lambda s: s[0] != page)
        tp, tc, tr = spots[0]
        for _ in range(4):
            if emu.r8(_ns(emu) + NS_PAGE) == tp:
                break
            emu.tap("SELECT", 4)
            rivalops.wait_naming(emu)
        else:
            raise HnsError("nametext: cannot reach keyboard page %d" % tp)
        for _ in range(40):
            c, r = _cursor(emu)
            if (c, r) == (tc, tr):
                break
            if c >= COLS[tp]:
                key = "LEFT"
            elif r != tr:
                key = "DOWN" if tr > r else "UP"
            else:
                key = "RIGHT" if tc > c else "LEFT"
            emu.tap(key, 4)
            emu.wait_quiet(300)
        else:
            raise HnsError("nametext: cursor stuck at %r, wanted %r" % (_cursor(emu), (tc, tr)))
        emu.tap("A", 4)
        rivalops.wait_naming(emu)
        buf = _entry(emu)
        if buf[start:start + i + 1] != want[:i + 1]:
            raise HnsError("nametext: after %r the entry is %s, wanted %s"
                           % (ch, buf[:start + i + 1].hex(), want[:i + 1].hex()))
        r3bf._shot(emu, "%s_%d" % (prefix, i + 1))
    print("nametext %r ok @%d" % (text, emu.sync()))


if __name__ == "__main__":
    sys.argv[0] = hns.__file__
    sys.exit(hns.main())
