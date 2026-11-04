#!/usr/bin/env python3
"""Driver for the Easy Chat tours of the Hebrew keyboard and the mirrored screen (ec18_*.txt in this
folder): hns.py plus the Easy Chat and r2/r3 ops of hwec.py, and two ops of its own.

    heapstat LABEL      walk the heap (src/malloc.c: blocks from sHeapStart, struct MemBlock in
                        include/malloc.h) and print the allocated and free bytes, the largest free
                        block and whether every header has MALLOC_SYSTEM_ID; HnsError on a broken
                        chain
    eckeys PREFIX       keyboard in alphabet mode: find each row's last key by moving to the next
                        column until the cursor leaves the keys, then move onto every key in
                        reading order and shot it (PREFIX_RC); prints the last column of each row

Run:  ec18.py tour ROM OUT --tours tools/hebrew/emu/scripts/r18_easy_chat [--clip] [--only RE]
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


if __name__ == "__main__":
    sys.argv[0] = hns.__file__
    sys.exit(hns.main())
