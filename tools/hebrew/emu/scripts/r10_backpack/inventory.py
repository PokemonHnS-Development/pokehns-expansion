#!/usr/bin/env python3
"""inventory.py ROM SRC OUT.json : every item id of the ROM with its pocket, name, plural, description
(decoded with SRC/charmap.txt) and field-use function, read from gItemsInfo (struct ItemInfo,
include/item.h:67, 44 bytes; pocket = bits 3-7 of byte 0x1E)."""
import json
import os
import struct
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
EMU = os.path.dirname(os.path.dirname(HERE))
sys.path.insert(0, EMU)
sys.path.insert(0, os.path.dirname(EMU))
import hns  # noqa: E402
import textwidth as tw  # noqa: E402

POCKETS = ["ITEMS", "MEDICINE", "POKE_BALLS", "TM_HM", "BERRIES", "KEY_ITEMS", "DUMMY"]


def main():
    rom, src, out = sys.argv[1:4]
    elf = hns.Elf(os.path.splitext(rom)[0] + ".elf")
    data = open(rom, "rb").read()
    cm = tw.Charmap(os.path.join(src, "charmap.txt"))

    def rd(addr, n):
        o = addr - 0x08000000
        return data[o:o + n]

    def s(addr):
        if not addr or not (0x08000000 <= addr < 0x0A000000):
            return None
        raw = rd(addr, 400)
        return cm.decode(raw[:raw.index(0xFF) + 1] if 0xFF in raw else raw)

    import re
    names, vals, cur = {}, {}, -1
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
        cur = cur + 1 if e is None else eval(re.sub(r"(?:ITEM|FIRST)_\w+", lambda mm: str(vals[mm.group(0)]), e.strip()))
        vals[n] = cur
        if not n.startswith("FIRST_"):
            names.setdefault(cur, n)
    base, size = elf.sym("gItemsInfo"), elf.size("gItemsInfo")
    count = vals["ITEMS_COUNT"]
    assert size == count * 44, (size, count)
    tb, ts = elf.sym("gTMHMItemMoveIds"), elf.size("gTMHMItemMoveIds")
    tmraw = rd(tb, ts)
    tms = {struct.unpack_from("<HH", tmraw, i)[0]: struct.unpack_from("<HH", tmraw, i)[1] for i in range(0, ts, 4)}
    raw = rd(base, size)
    items = []
    for i in range(count):
        price, sec, fuse, desc, eff, name, plural = struct.unpack_from("<IHxxIIIII", raw, i * 44)
        b = raw[i * 44 + 0x1E]
        items.append(dict(id=i, const=names.get(i, "ITEM_%d" % i), pocket=POCKETS[min(b >> 3, 6)],
                          importance=b & 3, name=s(name), plural=s(plural), desc=s(desc),
                          fieldUse=elf.where(fuse & ~1) if fuse else None, price=price,
                          tm_move=tms.get(i), icon=struct.unpack_from("<I", raw, i * 44 + 36)[0]))
    json.dump(items, open(out, "w"), ensure_ascii=False, indent=0)
    from collections import Counter
    print(Counter(it["pocket"] for it in items[1:]))


if __name__ == "__main__":
    main()
