#!/usr/bin/env python3
"""FILE:sym lookups for an ELF that has no linker map next to it.

hns.Elf resolves a static symbol qualified by its object file ("menu:sMenu") through the .map
next to the ELF. The rc14 clip build (release/rc14/pokehns-clip.elf) ships without
pokehns-clip.map, so such a lookup matches nothing. This fallback resolves the name in the
sibling non-clip build of the same commit (pokehns.elf + pokehns.map in the same folder) and
takes the clip ELF's symbol of the same name at the same address and size, or else the one of
the same rank among the same-named symbols when the count and size agree. RAM statics keep
their addresses between the two builds (menu:sMenu is 0203378c in both); anything else fails
as before."""
import os

import hns
from hns import HnsError

_orig_rec = hns.Elf._rec


def _rec(self, name):
    try:
        return _orig_rec(self, name)
    except HnsError:
        if ":" not in name:
            raise
        if os.path.exists(os.path.splitext(self.path)[0] + ".map"):
            raise
        d = os.path.dirname(self.path)
        sib = os.path.join(d, "pokehns.elf")
        if os.path.abspath(sib) == os.path.abspath(self.path) or not (
                os.path.exists(sib) and os.path.exists(os.path.join(d, "pokehns.map"))):
            raise
        if getattr(self, "_r11_sib", None) is None:
            self._r11_sib = hns.Elf(sib)
        rec = self._r11_sib._rec(name)
        nm = name.split(":", 1)[1]
        mine = sorted(self.byname.get(nm, []))
        same = [r for r in mine if r[0] == rec[0] and r[1] == rec[1]]
        if len(same) == 1:
            return same[0]
        theirs = sorted(self._r11_sib.byname.get(nm, []))
        if len(mine) == len(theirs):
            i = theirs.index(rec)
            if mine[i][1] == rec[1]:
                return mine[i]
        raise


hns.Elf._rec = _rec
