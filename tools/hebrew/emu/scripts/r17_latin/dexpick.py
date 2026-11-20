#!/usr/bin/env python3
"""Pokedex INFO pages of chosen species, through the INFO stand-in of scripts/r16b_dex/dexinfo.py,
and the INFO page of a form reached through the game's own forms list.

    dexpick.py info ROM OUT --save SAV --species SPECIES_A,SPECIES_B [--clip]
        dexinfo.py info for these species only, in one runner: shots OUT/info/NNN_SPECIES.png
        (NNN = the position in --species); OUT/info/b000/ holds run.log, manifest.json, clip.json.
    dexpick.py form ROM OUT --save SAV --base SPECIES_X --form K [--clip]
        The stand-in INFO page of the base species, then AREA, STATS, EVO, START (the forms list,
        Task_HandleEvolutionScreenInput, src/pokedex_plus_hgss.c:6563-6571), the cursor on form K
        and A. A sets formSpecies the way the game does, GetFormSpeciesId of the list item's
        species and the form id (:7640-7650), and the INFO page of that form is drawn. Shots in
        OUT/form/: base_info, forms, forms_cursor, form_info.

The species of the r17 Latin-to-Hebrew Pokedex entries have no list entry of their own (except
Hisuian Typhlosion, which scripts/r2_pokedex/dexsweep.py info reaches in the list). In play their
entries show on the caught-Pokemon page after a first catch; Eternamax Eternatus shows on the
forms list of a caught Eternatus. Run from a work dir with HNS_SRC = the ROM's tree, HNS_RUNNER
and HNS_MAX_FRAMES, as for dexinfo.py; save r2dex_all.sav.
"""
import argparse
import json
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
EMU = os.path.dirname(os.path.dirname(HERE))
sys.path.insert(0, os.path.join(EMU, "scripts", "r16b_dex"))
sys.path.insert(0, os.path.join(EMU, "scripts", "r2_pokedex"))
sys.path.insert(0, EMU)
import dexinfo  # noqa: E402
import dexsweep  # noqa: E402
import hns  # noqa: E402


def cmd_info(a):
    species = a.species.split(",")
    dexinfo.load_targets = lambda: [{"n": i, "species": s} for i, s in enumerate(species)]
    a.start, a.count, a.block = 0, len(species), len(species)
    dexinfo.cmd_info(a)


def cmd_form(a):
    src = dexsweep.src_tree()
    vals = dexinfo.values_for(src, [a.base])
    sp, nat, natname = vals[a.base]
    out = os.path.join(a.out, "form")
    emu = dex = None
    status, rec = "OK", {"base": a.base, "value": sp, "natdex": natname, "natnum": nat, "form": a.form}
    try:
        emu, dex = dexinfo.session(a.rom, out, a.save, a.clip)
        dex.poke(sp, nat)
        dex.redraw_info()
        dex.snap("base_info")
        dex.info_to_evo_page()
        dex.key("START")
        dex.wait("Task_HandleFormsScreenInput")
        n = dex.pv8("PV.forms.numForms")
        rec["numForms"] = n
        if a.form > n:
            raise hns.HnsError("%s has %d form(s), wanted form %d" % (a.base, n, a.form))
        dex.snap("forms")
        dex.key("A")
        emu.wait_quiet(300)
        for _ in range(a.form - 1):
            dex.key("RIGHT", 4)
        emu.frames(4)
        if dex.pv8("PV.forms.menuPos") != a.form:
            raise hns.HnsError("forms cursor at %d, wanted %d" % (dex.pv8("PV.forms.menuPos"), a.form))
        dex.snap("forms_cursor")
        dex.key("A")
        dex.wait("Task_HandleInfoScreenInput")
        fs = emu.r16(dex.pv() + dexsweep.OFF["PV.formSpecies"])
        rec["formSpecies"] = fs
        rec["formName"] = dex.spn.get(fs, "BASE") if fs else "BASE"
        dex.snap("form_info")
        dex.manifest["form"] = rec
    except hns.HnsError as e:
        status = "ERROR: %s" % str(e).splitlines()[0]
        if emu:
            try:
                emu.shot("_error")
            except hns.HnsError:
                pass
    res = dexsweep.finish(emu, dex, out, status) if dex else {"status": status}
    res.update(rec)
    with open(os.path.join(a.out, "form_report.json"), "w") as fh:
        json.dump(res, fh, indent=1)
    print(res)


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("cmd", choices=["info", "form"])
    ap.add_argument("rom")
    ap.add_argument("out")
    ap.add_argument("--save", required=True)
    ap.add_argument("--clip", action="store_true")
    ap.add_argument("--species", help="info: comma-separated SPECIES_*")
    ap.add_argument("--base", help="form: the base species (SPECIES_*)")
    ap.add_argument("--form", type=int, default=1, help="form: the form's position in the forms list (1 = first after the base)")
    a = ap.parse_args()
    a.rom = os.path.abspath(a.rom)
    a.out = os.path.abspath(a.out)
    if a.cmd == "info" and not a.species:
        ap.error("info needs --species")
    if a.cmd == "form" and not a.base:
        ap.error("form needs --base")
    {"info": cmd_info, "form": cmd_form}[a.cmd](a)


if __name__ == "__main__":
    main()
