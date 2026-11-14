#!/usr/bin/env python3
"""Pokedex INFO page category (gSpeciesInfo[].categoryName) of the species the r16 coverage had not
seen (category_species.json next to this file). None of them is in the 482-entry obtainable list
(CreatePokedexList, src/pokedex_plus_hgss.c:2572-2610); in play their category appears on the
caught-Pokemon Pokedex page after a first catch (randomizer GEN SCOPE Gen 1-9), which prints with the
same PrintMonInfo (src/pokedex_plus_hgss.c:4713-4770). Stand-in: on the INFO page of list entry 0
(owned), sPokedexView->formSpecies is set to the target species and RIGHT, LEFT redraws INFO
(NationalPokedexNumToSpeciesHGSS returns formSpecies, :5009-5018): name, category, size and entry of
the target in the real INFO window, under entry 0's number. Uses the Dex class of
scripts/r2_pokedex/dexsweep.py (page waits, struct offsets per language).

    dexcat.py ROM OUT --save SAV [--clip]

Shots OUT/cat_NN_SPECIES_info.png (NN the index in category_species.json).
Run from a work dir with HNS_SRC = the ROM's tree; save r2dex_all.sav (HNS_SAVES=hns-tools/emu/saves_all).
HNS_STRCOV works as for any hns.Emu session.
"""
import argparse
import json
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
EMU = os.path.dirname(os.path.dirname(HERE))
sys.path.insert(0, os.path.join(EMU, "scripts", "r2_pokedex"))
sys.path.insert(0, EMU)
import dexsweep  # noqa: E402
import hns  # noqa: E402


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("rom")
    ap.add_argument("out")
    ap.add_argument("--save", required=True)
    ap.add_argument("--clip", action="store_true")
    a = ap.parse_args()
    targets = json.load(open(os.path.join(HERE, "category_species.json")))
    src = dexsweep.src_tree()
    emu = dexsweep.boot(a.rom, a.out, a.save, a.clip)
    dex = dexsweep.Dex(emu, src, a.out)
    status, done, missing = "OK", [], []
    try:
        dex.open_dex(None)
        dex.list_goto(0)
        dex.list_to_info()
        fsp = dex.pv() + dexsweep.OFF["PV.formSpecies"]
        for k, t in enumerate(targets):
            want = emu.const(t["species"])
            emu.w16(fsp, want)
            dex.key("RIGHT")
            dex.wait_area()
            dex.key("LEFT")
            dex.wait("Task_HandleInfoScreenInput")
            got = emu.r16(fsp)
            dex.snap("cat_%02d_%s_info" % (k, t["species"][len("SPECIES_"):]))
            if got != want:
                missing.append(t["species"])
                print("%s: formSpecies %d after the redraw, wanted %d" % (t["species"], got, want))
            else:
                done.append(t["species"])
        emu.w16(fsp, 0)
    except hns.HnsError as e:
        status = "ERROR: %s" % str(e).splitlines()[0]
        try:
            emu.shot("_error")
        except hns.HnsError:
            pass
    res = dexsweep.finish(emu, dex, a.out, status)
    res.update(done=len(done), missing=missing)
    with open(os.path.join(a.out, "dexcat.json"), "w") as fh:
        json.dump(res, fh, indent=1)
    print(res)


if __name__ == "__main__":
    main()
