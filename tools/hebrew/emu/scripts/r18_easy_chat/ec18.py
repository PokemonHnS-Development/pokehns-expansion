#!/usr/bin/env python3
"""Driver for the Easy Chat tours of the Hebrew keyboard and the mirrored screen (ec18_*.txt in this
folder, and tours/r18_easychat): hns.py plus the Easy Chat and r2/r3 ops of hwec.py, and these ops:

    heapstat LABEL      walk the heap (src/malloc.c: blocks from sHeapStart, struct MemBlock in
                        include/malloc.h) and print the allocated and free bytes, the largest free
                        block and whether every header has MALLOC_SYSTEM_ID; HnsError on a broken
                        chain
    eckeys PREFIX       keyboard in alphabet mode: find each row's last key by moving to the next
                        column until the cursor leaves the keys, then move onto every key in
                        reading order and shot it (PREFIX_RC); prints the last column of each row
    ecabclists PREFIX [MAX]
                        keyboard in alphabet mode: find each row's last key as eckeys does, then open
                        every key's word list and page it to its end (eclist PREFIX_RC, at most MAX
                        pages, default 80); prints each list's word count and the longest list
    ecdir next|prev [N] tap the key that moves an Easy Chat cursor to the next (prev) column, N times
                        (LEFT and RIGHT are swapped on a tree with mirrored columns, as in hwec.py)
    eggcheck SLOT SPECIES
                        stop unless gPlayerParty[SLOT] is an egg (BoxPokemon.isEgg) of SPECIES: the
                        growth substruct is decrypted with personality ^ otId at the position
                        sSubstructOffsets gives it (src/pokemon.c GetSubstruct); species is its low
                        11 bits (struct PokemonSubstruct0, include/pokemon.h)

Run:  ec18.py tour ROM OUT --tours tools/hebrew/emu/scripts/r18_easy_chat [--clip] [--only RE]
      ec18.py tour ROM OUT --tours tools/hebrew/emu/tours/r18_easychat [--clip] [--only RE]
Env:  HNS_SRC=<the tree the ROM was built from> (constants, and whether the columns are mirrored),
      HNS_SAVES=hns-tools/emu/saves_all (ladder6_postgame.sav).
"""
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
SCRIPTS = os.path.dirname(HERE)
sys.path.insert(0, os.path.dirname(SCRIPTS))                                     # tools/hebrew/emu
sys.path.insert(0, os.path.join(SCRIPTS, "r2_help_windows_and_easy_chat"))
import hns  # noqa: E402
import hwec  # noqa: E402  (Easy Chat ops; r3bf, r2sf)
from hns import script_op, HnsError  # noqa: E402

MALLOC_SYSTEM_ID = 0xA3A3
HEADER = 16


def heap_blocks(emu):
    start = emu.r32(emu.sym("sHeapStart"))
    blocks, b = [], start
    for _ in range(4096):
        w0 = emu.r16(b)
        magic = emu.r16(b + 2)
        size = emu.r32(b + 4) & 0x3FFFF
        nxt = emu.r32(b + 12)
        blocks.append((b, bool(w0 & 1), size, magic == MALLOC_SYSTEM_ID))
        if nxt == start:
            return blocks
        if not 0x02000000 <= nxt < 0x02040000:
            raise HnsError("heapstat: block %08X points to %08X" % (b, nxt))
        b = nxt
    raise HnsError("heapstat: more than 4096 blocks")


@script_op("heapstat")
def _op_heapstat(emu, f, path):
    blocks = heap_blocks(emu)
    used = sum(s for _, a, s, _ in blocks if a)
    free = [s for _, a, s, _ in blocks if not a]
    bad = [b for b, _, _, ok in blocks if not ok]
    if bad:
        raise HnsError("heapstat: bad magic at %s" % ", ".join("%08X" % b for b in bad))
    wd = emu.r32(emu.sym("sWordData")) if f[1:] else 0
    wd_size = next((s for b, a, s, _ in blocks if a and b + HEADER == wd), None)
    print("heapstat %s: %d blocks, %d allocated, %d bytes allocated, %d free, largest free %d, "
          "sWordData %08X (%s bytes) @%d" % (f[1] if len(f) > 1 else "-", len(blocks), sum(1 for b in blocks if b[1]),
                                             used, sum(free), max(free) if free else 0, wd,
                                             wd_size, emu.sync()))


@script_op("eckeys")
def _op_eckeys(emu, f, path):
    prefix = f[1]
    lasts = []
    for row in range(4):
        # the last reachable column of the row: move right (next) until the cursor leaves the keys
        hwec._op_ecletter(emu, ["ecletter", str(row), "0"], path)
        col = 0
        while True:
            hwec.ec_tap(emu, hwec._next_col(emu))
            c = hwec._get(emu, "keyboardColumn")
            if c == -1 or c <= col:
                break
            col = c
        lasts.append(col)
        for c in range(col + 1):
            hwec._op_ecletter(emu, ["ecletter", str(row), str(c)], path)
            hwec._shot(emu, "%s_%d%d" % (prefix, row, c))
    print("eckeys %s: last column per row %s @%d" % (prefix, lasts, emu.sync()))


def last_columns(emu, path):
    """The last reachable column of each alphabet keyboard row (as eckeys finds them)."""
    lasts = []
    for row in range(4):
        hwec._op_ecletter(emu, ["ecletter", str(row), "0"], path)
        col = 0
        while True:
            hwec.ec_tap(emu, hwec._next_col(emu))
            c = hwec._get(emu, "keyboardColumn")
            if c == -1 or c <= col:
                break
            col = c
        lasts.append(col)
    return lasts


@script_op("ecabclists")
def _op_ecabclists(emu, f, path):
    prefix, mx = f[1], hns._arg(f, 2, 80)
    lasts = last_columns(emu, path)
    counts = {}
    for row, last in enumerate(lasts):
        for col in range(last + 1):
            hwec._op_ecletter(emu, ["ecletter", str(row), str(col)], path)
            hwec.ec_tap(emu, "A")
            if hwec._get(emu, "inputState") != 3:
                raise HnsError("ecabclists: key %d,%d opened no word list (state %s)"
                               % (row, col, hwec.INPUTSTATES[hwec._get(emu, "inputState")]))
            hwec._op_eclist(emu, ["eclist", "%s_%d%d" % (prefix, row, col), str(mx)], path)
            counts["%d%d" % (row, col)] = len(hwec.ec_words(emu))
            hwec.ec_tap(emu, "B")
    longest = max(counts, key=lambda k: counts[k])
    print("ecabclists %s: last column per row %s, words per key %s, longest %s (%d) @%d"
          % (prefix, lasts, counts, longest, counts[longest], emu.sync()))


@script_op("ecdir")
def _op_ecdir(emu, f, path):
    key = hwec._next_col(emu) if f[1] == "next" else hwec._prev_col(emu)
    for _ in range(hns._arg(f, 2, 1)):
        hwec.ec_tap(emu, key)
    print("ecdir %s (%s) x%d: state %s @%d" % (f[1], key, hns._arg(f, 2, 1),
                                                hwec.INPUTSTATES[hwec._get(emu, "inputState")], emu.sync()))


MON_SIZE, BOX_FLAGS, BOX_SECURE = 0x64, 0x13, 0x20      # struct Pokemon, struct BoxPokemon


@script_op("eggcheck")
def _op_eggcheck(emu, f, path):
    slot, want = int(f[1]), emu.const(f[2])
    raw = emu.read(emu.sym("gPlayerParty") + MON_SIZE * slot, 0x50)
    pers = int.from_bytes(raw[0:4], "little")
    key = pers ^ int.from_bytes(raw[4:8], "little")
    g = BOX_SECURE + emu.read(emu.sym("sSubstructOffsets"), 24)[pers % 24] * 12
    species = (int.from_bytes(raw[g:g + 4], "little") ^ key) & 0x7FF
    is_egg, bad = bool(raw[BOX_FLAGS] & 4), bool(raw[BOX_FLAGS] & 1)
    if species != want or not is_egg or bad:
        raise HnsError("eggcheck: slot %d holds species %d (egg %s, bad egg %s), wanted an egg of %s (%d)"
                       % (slot, species, is_egg, bad, f[2], want))
    print("eggcheck %d: an egg of %s (%d) ok @%d" % (slot, f[2], want, emu.sync()))


if __name__ == "__main__":
    sys.argv[0] = hns.__file__
    sys.exit(hns.main())
