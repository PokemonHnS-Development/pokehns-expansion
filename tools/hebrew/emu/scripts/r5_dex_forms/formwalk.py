#!/usr/bin/env python3
"""Pokedex Plus FORMS page walk: every list entry that has forms, every cursor position.

    formwalk.py scan ROM OUT --save SAV [--start P] [--count N]
        For list positions P .. P+N-1 (0-based, national mode, numerical order): INFO -> AREA ->
        STATS -> EVO -> START (FORMS), read sFormScreenData.numForms, B back to the list. Writes
        OUT/scan.json {pos: [dexNum, name, numForms]} (no screenshots).
    formwalk.py walk ROM OUT --save SAV --pos P[,P...] [--clip] [--no-pages]
        For each list position: the entry's INFO, AREA, STATS (+A), EVO; FORMS out of the cursor
        (button hints sText_FORMS_Buttons_PE); A (hints _Submenu_PE) and the cursor at every
        position 1..numForms stepped with RIGHT; on lists of 7 or more forms, UP from the last
        position to 1 and DOWN from 1 to the last, a shot per step; B out of the cursor. Then A on
        each form: that form's INFO, AREA, STATS (+A), EVO and FORMS (dexsweep.Dex.form), unless
        --no-pages. One runner per position (OUT/pNNN/). --first-form K (one --pos): only the
        form pages from form K on (to --last-form L), in OUT/pNNN_fromKK/ (to resume after a reset).

Shots: POS_DEXNUM_NAME_6forms_cNN (RIGHT walk), _6forms_upNN / _6forms_dnNN (UP / DOWN walk),
_6forms_out_after_b, and the form pages POS_DEXNUM_NAME_fKK_FORMSPECIES_<page>.
Env: HNS_RUNNER, HNS_SRC (constants), as for hns.py; the struct offsets are dexsweep's.
"""
import argparse
import json
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(HERE, "..", "r2_pokedex"))
import dexsweep  # noqa: E402
from dexsweep import hns  # noqa: E402


class FormDex(dexsweep.Dex):
    def menu_pos(self):
        return self.pv8("PV.forms.menuPos")

    def cursor_step(self, key):
        self.key(key, 4)
        self.emu.frames(4)
        return self.menu_pos()

    def cursor_walk(self, prefix, nf):
        """On the FORMS page, out of the cursor. Returns the positions seen per direction."""
        seen = {"right": [], "up": [], "down": []}
        self.snap(prefix + "_6forms_out")
        self.key("A")
        self.emu.wait_quiet(300)
        self.emu.frames(4)
        pos = self.menu_pos()
        if pos != 1:
            raise hns.HnsError("forms cursor opened at %d" % pos)
        self.snap("%s_6forms_c%02d" % (prefix, 1))
        seen["right"].append(1)
        for k in range(2, nf + 1):
            pos = self.cursor_step("RIGHT")
            if pos != k:
                raise hns.HnsError("RIGHT: forms cursor at %d, wanted %d" % (pos, k))
            self.snap("%s_6forms_c%02d" % (prefix, k))
            seen["right"].append(k)
        pos = self.cursor_step("RIGHT")                 # clamped at the last form
        seen["right_clamp"] = pos
        if nf >= 7:
            while True:
                before = pos
                pos = self.cursor_step("UP")
                self.snap("%s_6forms_up%02d" % (prefix, pos))
                seen["up"].append(pos)
                if pos == 1 or pos == before:
                    break
            while True:
                before = pos
                pos = self.cursor_step("DOWN")
                if pos == before:
                    break
                self.snap("%s_6forms_dn%02d" % (prefix, pos))
                seen["down"].append(pos)
        pos = self.cursor_step("LEFT")
        seen["left_after"] = pos
        self.key("B")
        self.emu.wait_quiet(300)
        self.emu.frames(4)
        self.snap(prefix + "_6forms_out_after_b")
        return seen

    def form(self, pos, k, nf):
        """dexsweep.Dex.form without its cursor shots (the walk has every position)."""
        emu = self.emu
        prefix = self.tag(pos)
        self.info_to_evo(prefix, shoot=False)
        self.evo_to_forms(prefix, shoot=False)
        self.key("A")
        emu.wait_quiet(300)
        for _ in range(k - 1):
            self.key("RIGHT", 4)
        emu.frames(4)
        if self.menu_pos() != k:
            raise hns.HnsError("forms cursor at %d, wanted %d" % (self.menu_pos(), k))
        self.key("A")
        self.wait("Task_HandleInfoScreenInput")
        fs = self.pv16("PV.formSpecies")
        fname = self.spn.get(fs, "BASE") if fs else "BASE"
        fp = "%s_f%02d_%s" % (prefix, k, fname)
        self.snap(fp + "_1info")
        rec = {"k": k, "formSpecies": fs, "formName": fname}
        rec.update(self.info_to_evo(fp))
        n2, ids2 = self.evo_to_forms(fp)
        rec["numForms"] = n2
        self.key("B")                                   # FORMS -> list
        self.wait("Task_HandlePokedexInput")
        emu.frames(16)
        self.list_to_info()
        return rec

    def walk_entry(self, pos, pages=True, first_form=1, last_form=0):
        prefix = self.tag(pos)
        if first_form > 1:                              # resume: only the form pages from K on
            nf = 0
            self.info_to_evo(prefix, shoot=False)
            nf, ids = self.evo_to_forms(prefix, shoot=False)
            self.key("B")
            self.wait("Task_HandlePokedexInput")
            self.emu.frames(16)
            self.list_to_info()
            first = len(self.shots)
            rec = {"pos": pos + 1, "numForms": nf, "resumedAt": first_form,
                   "forms": [self.form(pos, k, nf) for k in range(first_form, min(nf, last_form or nf) + 1)]}
            rec["shots"] = self.shots[first:]
            self.manifest[prefix + "_from%02d" % first_form] = rec
            return
        rec = {"pos": pos + 1, "dexNum": self.dexnum(), "name": self.name(self.dexnum())}
        first = len(self.shots)
        self.snap(prefix + "_1info")
        rec.update(self.info_to_evo(prefix))
        nf, ids = self.evo_to_forms(prefix, shoot=False)
        rec["numForms"], rec["formIds"] = nf, ids
        if nf:
            rec["cursor"] = self.cursor_walk(prefix, nf)
        else:
            self.snap(prefix + "_6forms_none")
            self.key("A")
            self.emu.wait_quiet(300)
            self.snap(prefix + "_6forms_none_after_a")
        self.key("B")                                   # FORMS -> list
        self.wait("Task_HandlePokedexInput")
        self.emu.frames(16)
        if nf and pages:
            self.list_to_info()
            rec["forms"] = [self.form(pos, k, nf) for k in range(1, nf + 1)]
            self.key("B")
            self.wait("Task_HandlePokedexInput")
            self.emu.frames(16)
        rec["shots"] = self.shots[first:]
        self.manifest[prefix] = rec


def cmd_scan(a):
    src = dexsweep.src_tree()
    out = a.out
    emu = dexsweep.boot(a.rom, out, a.save, False)
    dex = FormDex(emu, src, out)
    res, status = {}, "OK"
    try:
        dex.open_dex(None)
        count = dex.pv16("PV.pokemonListCount")
        res["_count"] = count
        for pos in range(a.start, min(count, a.start + a.count)):
            dex.list_goto(pos)
            dex.list_to_info()
            dex.info_to_evo("", shoot=False)
            nf, ids = dex.evo_to_forms("", shoot=False)
            res[pos] = [dex.dexnum(), dex.name(dex.dexnum()), nf]
            if nf:
                print("pos %d %s: %d forms" % (pos, dex.name(dex.dexnum()), nf))
                sys.stdout.flush()
            dex.key("B")
            dex.wait("Task_HandlePokedexInput")
            emu.frames(16)
    except hns.HnsError as e:
        status = "ERROR: %s" % str(e).splitlines()[0]
        emu.shot("_error")
    res["_status"] = status
    with open(os.path.join(out, "scan.json"), "w") as fh:
        json.dump(res, fh, indent=0)
    print(dexsweep.finish(emu, dex, out, status))


def cmd_walk(a):
    src = dexsweep.src_tree()
    report = {}
    for pos in [int(p) for p in a.pos.split(",")]:
        out = os.path.join(a.out, "p%03d" % pos + ("_from%02d" % a.first_form if a.first_form > 1 else ""))
        emu = dexsweep.boot(a.rom, out, a.save, a.clip)
        dex = FormDex(emu, src, out)
        status = "OK"
        try:
            dex.open_dex(None)
            dex.list_goto(pos)
            dex.list_to_info()
            dex.walk_entry(pos, pages=not a.no_pages, first_form=a.first_form, last_form=a.last_form)
        except hns.HnsError as e:
            status = "ERROR: %s" % str(e).splitlines()[0]
            try:
                emu.shot("_error")
            except hns.HnsError:
                pass
        report["p%03d" % pos] = dexsweep.finish(emu, dex, out, status)
        print("p%03d %s" % (pos, report["p%03d" % pos]))
        sys.stdout.flush()
    with open(os.path.join(a.out, "report_%s.json" % a.pos.replace(",", "_")[:60]), "w") as fh:
        json.dump(report, fh, indent=1)


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("cmd", choices=["scan", "walk"])
    ap.add_argument("rom")
    ap.add_argument("out")
    ap.add_argument("--save", required=True)
    ap.add_argument("--clip", action="store_true")
    ap.add_argument("--start", type=int, default=0)
    ap.add_argument("--count", type=int, default=10000)
    ap.add_argument("--pos", default="")
    ap.add_argument("--no-pages", action="store_true")
    ap.add_argument("--last-form", type=int, default=0,
                    help="with --first-form: stop after this form (a fresh runner per form)")
    ap.add_argument("--first-form", type=int, default=1,
                    help="resume after a crash: only the form pages from this form on (one --pos)")
    a = ap.parse_args()
    a.rom = os.path.abspath(a.rom)
    a.out = os.path.abspath(a.out)
    {"scan": cmd_scan, "walk": cmd_walk}[a.cmd](a)


if __name__ == "__main__":
    main()
