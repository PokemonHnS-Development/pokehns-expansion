#!/usr/bin/env python3
"""Dump the tables the summary / relearner sweep shows, read from a built ROM and its ELF:
moves (name, description, PP, power, accuracy, contest effect and category), contest effects
(description, appeal, jam), abilities (name, description, first species/abilityNum that has it),
items (name, pocket, hold effect), natures (name, up/down stat).

    r6data.py ROM TREE OUT.json

TREE gives the charmap (charmap.txt) used to decode the strings. Strides are checked against
the symbol sizes (gMovesInfo 68, gAbilitiesInfo 28, gItemsInfo 44, gNaturesInfo 20,
gContestEffects 12, gSpeciesInfo 0x10C; struct MoveInfo include/move.h, AbilityInfo
include/pokemon.h:542, ItemInfo include/item.h:67, NatureInfo include/pokemon.h:603,
ContestEffect include/contest_effect.h:5).
"""
import json
import os
import struct
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(HERE, "..", ".."))          # tools/hebrew/emu
sys.path.insert(0, os.path.join(HERE, "..", "..", ".."))    # tools/hebrew
import hns  # noqa: E402
import textwidth as tw  # noqa: E402

ROMBASE = 0x08000000


def main():
    rom_path, tree, out = sys.argv[1:4]
    elf = hns.Elf(os.path.splitext(rom_path)[0] + ".elf")
    rom = open(rom_path, "rb").read()
    cm = tw.Charmap(os.path.join(tree, "charmap.txt"))

    def rd(addr, n):
        o = addr - ROMBASE
        return rom[o:o + n]

    def u32(addr):
        return struct.unpack("<I", rd(addr, 4))[0]

    def cstr(addr):
        if not (ROMBASE <= addr < ROMBASE + len(rom)):
            return None, b""
        o = addr - ROMBASE
        e = rom.index(b"\xff", o)
        raw = rom[o:e]
        return cm.decode(raw + b"\xff"), raw

    def table(name, stride):
        base, size = elf.sym(name), elf.size(name)
        assert size % stride == 0, (name, size, stride)
        return base, size // stride

    data = {}
    base, n = table("gMovesInfo", 68)
    moves = []
    for i in range(n):
        a = base + 68 * i
        rec = rd(a, 68)
        name, nraw = cstr(u32(a))
        desc, draw = cstr(u32(a + 4))
        moves.append(dict(id=i, name=name, name_hex=nraw.hex(), desc=desc, desc_hex=draw.hex(),
                          effect=struct.unpack_from("<H", rec, 8)[0],
                          contestEffect=rec[44], contestCategory=rec[45]))
    data["moves"] = moves

    base, n = table("gContestEffects", 12)
    data["contest_effects"] = []
    for i in range(n):
        a = base + 12 * i
        rec = rd(a, 12)
        desc, draw = cstr(u32(a + 4))
        data["contest_effects"].append(dict(id=i, effectType=rec[0], appeal=rec[1], jam=rec[2], desc=desc,
                                            desc_hex=draw.hex()))

    base, n = table("gAbilitiesInfo", 28)
    abil = []
    for i in range(n):
        a = base + 28 * i
        nm = rd(a, 17)
        nm = nm[:nm.index(b"\xff")] if b"\xff" in nm else nm
        desc, draw = cstr(u32(a + 20))
        abil.append(dict(id=i, name=cm.decode(nm + b"\xff"), name_hex=nm.hex(), desc=desc, desc_hex=draw.hex()))
    data["abilities"] = abil

    base, n = table("gSpeciesInfo", 0x10C)
    first = {}
    for sp in range(n):
        a = base + 0x10C * sp
        ab = struct.unpack("<3H", rd(a + 0x18, 6))
        for k, x in enumerate(ab):
            if x and x not in first:
                first[x] = (sp, k)
    for d in abil:
        d["species_abilityNum"] = first.get(d["id"])
    data["n_species"] = n

    base, n = table("gItemsInfo", 44)
    items = []
    for i in range(n):
        a = base + 44 * i
        rec = rd(a, 44)
        name, nraw = cstr(u32(a + 20))
        items.append(dict(id=i, name=name, name_hex=nraw.hex(), holdEffect=rec[28], importance=rec[30] & 3,
                          pocket=rec[30] >> 3, price=struct.unpack_from("<I", rec, 0)[0]))
    data["items"] = items

    base, n = table("gNaturesInfo", 20)
    nat = []
    for i in range(n):
        a = base + 20 * i
        name, nraw = cstr(u32(a))
        nat.append(dict(id=i, name=name, name_hex=nraw.hex()))
    data["natures"] = nat
    json.dump(data, open(out, "w"), ensure_ascii=False, indent=0)
    print("moves %d, contest effects %d, abilities %d, items %d, natures %d -> %s" % (
        len(moves), len(data["contest_effects"]), len(abil), len(items), len(nat), out))


if __name__ == "__main__":
    main()
