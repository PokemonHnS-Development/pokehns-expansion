#!/usr/bin/env python3
"""hns.py plus ops for the Pokemon Storage System screens (src/pokemon_storage_system.c):

    boxprobe [BOX ...]           print the party and the boxes (default: every box with a Pokemon):
                                 species, held item, moves, egg flag, decrypted from the BoxPokemon
                                 substructs (include/pokemon.h:129-160, src/pokemon.c:4350)
    pcwait [MAX]                 run until Task_PokeStorageMain reads input (sStorage->state ==
                                 MSTATE_HANDLE_INPUT, src/pokemon_storage_system.c:2287) and the
                                 screen is quiet
    pcgoto AREA POS [MAX]        move the storage cursor with the D-pad until sCursorArea == AREA
                                 and sCursorPosition == POS (AREA: box, party, title, buttons or a
                                 number; box positions 0-29 row by row, party 0-5 and 6 = CANCEL,
                                 buttons 0 = PARTY POKeMON, 1 = CLOSE BOX)
    pcfield NAME VALUE           find the u16 field of *sStorage that holds VALUE now (scan of the
                                 first 0x3000 bytes); NAME remembers its offset for pcpoke
    pcpoke NAME VALUE            write VALUE (a number or an ITEM_* / SPECIES_* constant) to the
                                 remembered field
    bagcursor POCKET ITEM        before the bag opens: set gBagPosition.cursorPosition/scrollPosition
                                 [POCKET] (+8 / +20, 6 pockets: gBagPosition is 32 bytes) so the list
                                 opens on ITEM, found in gBagPockets[POCKET] (struct BagPocket, 8 bytes:
                                 itemSlots pointer, capacity)
Usage: pcs.py <hns.py args>   (e.g. pcs.py tour ROM OUT --tours DIR --only RE --clip)
"""
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
EMU = os.path.dirname(os.path.dirname(HERE))
sys.path.insert(0, EMU)
import hns  # noqa: E402
from hns import script_op, HnsError, TourTimeout, _arg  # noqa: E402

BOXMON_SIZE, MON_SIZE, BOXES, IN_BOX = 0x50, 0x64, 14, 30
SECURE, SUB = 32, 12
# sSubstructOffsets (src/pokemon.c:4350): slot of substruct type T for personality % 24
SUBOFF = [
    [0, 0, 0, 0, 0, 0, 1, 1, 2, 3, 2, 3, 1, 1, 2, 3, 2, 3, 1, 1, 2, 3, 2, 3],
    [1, 1, 2, 3, 2, 3, 0, 0, 0, 0, 0, 0, 2, 3, 1, 1, 3, 2, 2, 3, 1, 1, 3, 2],
]
AREAS = {"box": 0, "party": 1, "title": 2, "buttons": 3}


def decode_boxmon(raw):
    pers = int.from_bytes(raw[0:4], "little")
    otid = int.from_bytes(raw[4:8], "little")
    flags = raw[19]
    if not flags & 2:
        return None
    key = pers ^ otid
    sec = bytearray(raw[SECURE:SECURE + 4 * SUB])
    for i in range(0, len(sec), 4):
        w = int.from_bytes(sec[i:i + 4], "little") ^ key
        sec[i:i + 4] = w.to_bytes(4, "little")

    def sub(t):
        o = SUBOFF[t][pers % 24] * SUB
        return sec[o:o + SUB]
    g, a = sub(0), sub(1)
    species = int.from_bytes(g[0:2], "little") & 0x7FF
    item = int.from_bytes(g[2:4], "little") & 0x3FF
    moves = [int.from_bytes(a[2 * i:2 * i + 2], "little") & 0x7FF for i in range(4)]
    return {"species": species, "item": item, "moves": moves, "egg": bool(flags & 4)}


def _names(emu, prefix):
    if not hasattr(emu, "_pcs_names"):
        emu._pcs_names = {}
    if prefix not in emu._pcs_names:
        src = os.environ.get("HNS_SRC") or os.path.dirname(emu.elf.path)
        files = {"SPECIES_": "include/constants/species.h", "ITEM_": "include/constants/items.h",
                 "MOVE_": "include/constants/moves.h"}
        rev = {}
        import re
        for line in open(os.path.join(src, files[prefix]), errors="replace"):
            m = re.match(r"\s*#define\s+(%s\w+)\s+(\d+)\b" % prefix, line) or \
                re.match(r"\s*(%s\w+)\s*=\s*(\d+)\s*,?" % prefix, line)
            if m:
                rev.setdefault(int(m.group(2)), m.group(1))
        emu._pcs_names[prefix] = rev
    return emu._pcs_names[prefix]


def _fmt(emu, d):
    sp, it, mv = _names(emu, "SPECIES_"), _names(emu, "ITEM_"), _names(emu, "MOVE_")
    return "%s%s item=%s moves=%s" % (
        sp.get(d["species"], d["species"]), " (egg)" if d["egg"] else "",
        it.get(d["item"], d["item"]), ",".join(str(mv.get(m, m)) for m in d["moves"] if m))


@script_op("boxprobe")
def _op_boxprobe(emu, f, path):
    out = []
    party = emu.sym("gPlayerParty")
    for i in range(6):
        d = decode_boxmon(emu.read(party + MON_SIZE * i, BOXMON_SIZE))
        if d:
            out.append("party%d %s" % (i, _fmt(emu, d)))
    st = emu.r32(emu.sym("gPokemonStoragePtr"))
    want = [int(x) for x in f[1:]] or list(range(BOXES))
    for b in want:
        raw = emu.read(st + 4 + b * IN_BOX * BOXMON_SIZE, IN_BOX * BOXMON_SIZE)
        mons = [(s, decode_boxmon(raw[s * BOXMON_SIZE:(s + 1) * BOXMON_SIZE])) for s in range(IN_BOX)]
        mons = [(s, d) for s, d in mons if d]
        if mons or f[1:]:
            out.append("box%d: %d" % (b + 1, len(mons)))
        for s, d in mons:
            out.append("  box%d[%d] %s" % (b + 1, s, _fmt(emu, d)))
    for line in out:
        print("boxprobe: " + line)
    emu.log.extend("boxprobe: " + line for line in out)


def _storage(emu):
    p = emu.r32(emu.sym("pokemon_storage_system:sStorage"))
    if not p:
        raise HnsError("the storage system is not running (sStorage is NULL)")
    return p


def _idle(emu):
    p = emu.r32(emu.sym("pokemon_storage_system:sStorage"))
    want = emu.sym("Task_PokeStorageMain")
    return p != 0 and emu.r8(p) == 0 and any(fn == want for _, fn, _ in emu.tasks())


@script_op("pcwait")
def _op_pcwait(emu, f, path):
    emu.wait_until(lambda: _idle(emu), _arg(f, 1, 900), "Task_PokeStorageMain to read input", step=2)
    emu.wait_quiet(600)
    emu.frames(4)
    print("pcwait ok @%d" % emu.sync())


@script_op("pcgoto")
def _op_pcgoto(emu, f, path):
    area = AREAS[f[1]] if f[1] in AREAS else int(f[1], 0)
    pos = int(f[2], 0)
    a_sym, p_sym = emu.sym("sCursorArea"), emu.sym("sCursorPosition")
    for _ in range(_arg(f, 3, 30)):
        ca, cp = emu.r8(a_sym), emu.r8(p_sym)
        if (ca, cp) == (area, pos):
            print("pcgoto %s %d ok @%d" % (f[1], pos, emu.sync()))
            return
        if area == 0 and ca == 0:
            key = "UP" if cp // 6 > pos // 6 else "DOWN" if cp // 6 < pos // 6 else \
                  "LEFT" if cp > pos else "RIGHT"
        elif area == 0 and ca == 2:
            key = "DOWN"
        elif area == 0 and ca == 3:
            key = "UP"
        elif area == 0 and ca == 1:
            key = "RIGHT"
        elif area == 1 and ca == 1:
            # party pane: slot 0 on the left, 1-5 in the right column, 6 = CANCEL;
            # UP/DOWN step through 0..6 (RIGHT from 1-5 would close the pane)
            key = "UP" if cp > pos else "DOWN"
        elif area == 2:
            key = "DOWN" if ca == 3 else "UP"
        elif area == 3 and ca == 2:
            key = "UP"
        elif area == 3 and ca == 0:
            key = "DOWN"
        elif area == 3 and ca == 3:
            key = "LEFT" if cp > pos else "RIGHT"
        else:
            raise HnsError("pcgoto: no path from area %d to %d" % (ca, area))
        emu.tap(key, 4)
        emu.wait_until(lambda: _idle(emu), 300, "the cursor to stop", step=2)
    raise TourTimeout("pcgoto: cursor at area %d pos %d, wanted %d %d"
                      % (emu.r8(a_sym), emu.r8(p_sym), area, pos))


@script_op("pcfield")
def _op_pcfield(emu, f, path):
    val = emu.const(f[2]) if not f[2][0].isdigit() else int(f[2], 0)
    p = _storage(emu)
    raw = emu.read(p, 0x3000)
    hits = [o for o in range(0, len(raw) - 1, 2) if int.from_bytes(raw[o:o + 2], "little") == val]
    prev = getattr(emu, "_pcs_fields", {}).get(f[1])
    if isinstance(prev, list):
        hits = [o for o in hits if o in prev]
    emu._pcs_fields = getattr(emu, "_pcs_fields", {})
    emu._pcs_fields[f[1]] = hits if len(hits) != 1 else hits[0]
    print("pcfield %s = %s: offsets %s" % (f[1], f[2], ["%X" % o for o in hits][:20]))


@script_op("pcpoke")
def _op_pcpoke(emu, f, path):
    off = emu._pcs_fields.get(f[1])
    if not isinstance(off, int):
        raise HnsError("pcpoke: field %s is not resolved to one offset (%s)" % (f[1], off))
    val = emu.const(f[2]) if not f[2][0].isdigit() else int(f[2], 0)
    emu.w16(_storage(emu) + off, val)
    print("pcpoke %s (+%X) = %s @%d" % (f[1], off, f[2], emu.sync()))


@script_op("bagcursor")
def _op_bagcursor(emu, f, path):
    pocket = int(f[1], 0)
    item = emu.const(f[2]) if not f[2][0].isdigit() else int(f[2], 0)
    bp = emu.sym("gBagPockets") + 8 * pocket
    slots, cap = emu.r32(bp), emu.r16(bp + 4)
    ids = [emu.r16(slots + 4 * i) for i in range(cap)]
    if item not in ids:
        names = _names(emu, "ITEM_")
        print("bagcursor: pocket %d holds %s" % (pocket, ",".join(str(names.get(x, x)) for x in ids if x)))
        raise HnsError("bagcursor: %s not in pocket %d" % (f[2], pocket))
    idx = ids.index(item)
    n = sum(1 for x in ids if x)
    scroll = max(0, min(idx - 2, n + 1 - 8))
    pos = emu.sym("gBagPosition")
    emu.w16(pos + 8 + 2 * pocket, idx - scroll)
    emu.w16(pos + 20 + 2 * pocket, scroll)
    emu.w8(pos + 5, pocket)
    print("bagcursor %s: index %d of %d (cursor %d, scroll %d) @%d" % (f[2], idx, n, idx - scroll, scroll, emu.sync()))


if __name__ == "__main__":
    sys.argv[0] = hns.__file__
    sys.exit(hns.main())
