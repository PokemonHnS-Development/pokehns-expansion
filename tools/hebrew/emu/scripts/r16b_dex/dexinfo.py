#!/usr/bin/env python3
"""Pokedex INFO and EVO pages of species outside the 482-entry obtainable list (plan track dex_text).

These species never appear in the Pokedex list (CreatePokedexList, src/pokedex_plus_hgss.c:2572-2610).
In play their category and entry show on the caught-Pokemon Pokedex page after a first catch
(randomizer GEN SCOPE Gen 1-9: Cmd_displaydexinfo -> PrintMonInfo, src/pokedex_plus_hgss.c:4435,
4713-4770). Stand-in: on the INFO page of list entry 0 (owned), write the target species into
sPokedexView->formSpecies and its national number into the list item's dexNum, then RIGHT, LEFT
redraws INFO (NationalPokedexNumToSpeciesHGSS returns formSpecies, :5009-5018). PrintMonInfo then
prints the target's name, category, size and entry in the real INFO window, and No. 000 as the
caught page does (NationalToObtainableOrder of an out-of-dex number). The EVO page is the same poke,
then RIGHT three times (AREA, STATS, EVO).

    dexinfo.py info ROM OUT --save SAV [--clip] [--start N] [--count N] [--block B]
        Targets from dex_targets.json next to this file (field n = shot number, risk order).
        One runner per block of B targets (OUT/info/bNNN/ holds run.log, manifest, clip.json);
        shots OUT/info/NNN_SPECIES.png. A species the build disables (baseHP 0) is skipped and
        listed in the manifest: the game cannot hold it (IsSpeciesEnabled, src/pokemon.c:9407).
    dexinfo.py evo ROM OUT --save SAV [--clip] [--species SPECIES_A,SPECIES_B] [--tag evo]
        The EVO page of each species in EVO_TARGETS below (or --species): shots
        OUT/TAG/eNN_SPECIES.png.

Uses the Dex class and struct offsets of scripts/r2_pokedex/dexsweep.py (OFF_HE / OFF_EN by build).
Run from a work dir (RAM dumps land in the cwd) with HNS_SRC = the ROM's tree, HNS_RUNNER, and
HNS_MAX_FRAMES; save r2dex_all.sav (HNS_SAVES). HNS_STRCOV works as for any hns.Emu session.
"""
import argparse
import json
import os
import re
import shutil
import subprocess
import sys
import tempfile

HERE = os.path.dirname(os.path.abspath(__file__))
EMU = os.path.dirname(os.path.dirname(HERE))
sys.path.insert(0, os.path.join(EMU, "scripts", "r2_pokedex"))
sys.path.insert(0, EMU)
import dexsweep  # noqa: E402
import hns  # noqa: E402

# Species whose EVO page prints the evolution-method fragments of the track (the method each
# shows): Milcery (spin directions, sweet, evening), Rockruff Own Tempo (evening), Karrablast and
# Shelmet (trade partner), Sliggoo and Hisuian Sliggoo (weather: rain, fog), Toxel (amped and
# low-key natures), white-striped Basculin (recoil damage), Galarian Yamask (script trigger and
# current damage), Bisharp (defeat N holding), Pawmo, Bramblin and Rellor (steps), Tandemaus
# (level in battle), Kubfu (script trigger).
EVO_TARGETS = ["SPECIES_MILCERY", "SPECIES_ROCKRUFF_OWN_TEMPO", "SPECIES_KARRABLAST", "SPECIES_SHELMET",
               "SPECIES_SLIGGOO", "SPECIES_SLIGGOO_HISUI", "SPECIES_TOXEL", "SPECIES_BASCULIN_WHITE_STRIPED",
               "SPECIES_YAMASK_GALAR", "SPECIES_BISHARP", "SPECIES_PAWMO", "SPECIES_BRAMBLIN",
               "SPECIES_RELLOR", "SPECIES_TANDEMAUS", "SPECIES_KUBFU"]
STEP = 6                        # frames between game-state polls while a page loads


def resolve_all(src, names):
    """SPECIES_* and NATIONAL_DEX_* values for many names in one compile (hns.resolve_const does
    one compile per name)."""
    d = tempfile.mkdtemp(prefix="dexinfo")
    try:
        c = os.path.join(d, "k.c")
        with open(c, "w") as fh:
            fh.write('#include "gba/types.h"\n#include "constants/global.h"\n'
                     '#include "constants/species.h"\n#include "constants/pokedex.h"\n'
                     'const unsigned int gK[] = {\n%s\n};\n' % ",\n".join("(unsigned int)(%s)" % n for n in names))
        dk = os.environ.get("DEVKITARM", "/opt/devkitpro/devkitARM")
        r = subprocess.run([os.path.join(dk, "bin", "arm-none-eabi-gcc"), "-iquote", os.path.join(src, "include"),
                            "-Wno-trigraphs", "-DMODERN=1", "-DTESTING=0", "-DPOKEMON_HNS", "-std=gnu17",
                            "-mthumb", "-mabi=apcs-gnu", "-O2", "-c", c, "-o", os.path.join(d, "k.o")],
                           capture_output=True, text=True)
        if r.returncode:
            raise SystemExit("constants did not compile against %s: %s" % (src, r.stderr[-800:]))
        subprocess.run([os.path.join(dk, "bin", "arm-none-eabi-objcopy"), "-O", "binary", "-j", ".rodata",
                        os.path.join(d, "k.o"), os.path.join(d, "k.bin")], check=True)
        raw = open(os.path.join(d, "k.bin"), "rb").read()
    finally:
        shutil.rmtree(d, ignore_errors=True)
    return {n: int.from_bytes(raw[4 * i:4 * i + 4], "little") for i, n in enumerate(names)}


def natdex_name(species, natnames):
    """NATIONAL_DEX_X for SPECIES_X[_FORM]: the longest national name that is the species name or
    a prefix of it followed by '_'."""
    s = species[len("SPECIES_"):]
    best = None
    for n in natnames:
        if s == n or s.startswith(n + "_"):
            if best is None or len(n) > len(best):
                best = n
    if best is None:
        raise SystemExit("no national dex name for %s" % species)
    return "NATIONAL_DEX_" + best


class Dex(dexsweep.Dex):
    """dexsweep's Dex with sparser polling (STEP frames) while a page loads."""

    def wait(self, name, cond=None, maxf=1200, what=None):
        want = self.task(name)

        def ok():
            if not any(f == want for _, f, _ in self.emu.tasks()):
                return False
            return cond() if cond else True
        self.emu.wait_until(ok, maxf, what or name, step=STEP)
        self.emu.wait_quiet(600, step=STEP // 2)

    def wait_area(self, maxf=1200):
        def ok():
            d = self.emu.task_data("Task_HandlePokedexAreaScreenInput")
            return bool(d) and d[0][0] == 1
        self.emu.wait_until(ok, maxf, "the AREA page reading input", step=STEP)
        self.emu.wait_quiet(600, step=STEP // 2)

    def poke(self, species, natnum):
        """formSpecies and the current list item's dexNum (its seen/owned bits stay)."""
        self.emu.w16(self.pv() + dexsweep.OFF["PV.formSpecies"], species)
        self.emu.w16(self.emu.r32(self.itp), natnum)

    def redraw_info(self):
        self.key("RIGHT")
        self.wait_area()
        self.key("LEFT")
        self.wait("Task_HandleInfoScreenInput")

    def info_to_evo_page(self):
        self.key("RIGHT")
        self.wait_area()
        self.key("RIGHT")
        self.wait("Task_HandleStatsScreenInput")
        self.key("RIGHT")
        self.wait("Task_HandleEvolutionScreenInput")

    def evo_page_to_info(self):
        self.key("LEFT")
        self.wait("Task_HandleStatsScreenInput")
        self.key("LEFT")
        self.wait_area()
        self.key("LEFT")
        self.wait("Task_HandleInfoScreenInput")


def session(rom, out, save, clip):
    emu = dexsweep.boot(rom, out, save, clip)
    dex = Dex(emu, dexsweep.src_tree(), out)
    dex.open_dex(None)
    count = dex.pv16("PV.pokemonListCount")
    dex.list_goto(0)
    dex.list_to_info()
    if not dex.owned():
        raise hns.HnsError("list entry 0 is not owned in this save")
    print("list has %d entries; entry 0 is No. %d" % (count, dex.dexnum()))
    return emu, dex


def load_targets():
    return json.load(open(os.path.join(HERE, "dex_targets.json"), encoding="utf-8"))


def values_for(src, species_names):
    nat, _ = dexsweep.load_names(src)
    natnames = {s: natdex_name(s, nat) for s in species_names}
    vals = resolve_all(src, sorted(set(species_names) | set(natnames.values()) | {"NUM_SPECIES"}))
    out = {s: (vals[s], vals[natnames[s]], natnames[s]) for s in species_names}
    out["NUM_SPECIES"] = vals["NUM_SPECIES"]
    return out


def enabled(emu, num_species, species):
    """IsSpeciesEnabled (src/pokemon.c:9407-9411): gSpeciesInfo[species].baseHP > 0. A disabled
    species on the INFO page stops the game in SanitizeSpeciesId's assert (src/pokemon.c:9399)."""
    base = emu.sym("gSpeciesInfo")
    elem = emu.elf.size("gSpeciesInfo") // (num_species + 1)
    return emu.r8(base + species * elem) > 0


def cmd_info(a):
    src = dexsweep.src_tree()
    targets = load_targets()[a.start:a.start + a.count]
    vals = values_for(src, [t["species"] for t in targets])
    shots = os.path.join(a.out, "info")
    os.makedirs(shots, exist_ok=True)
    report = {}
    for b0 in range(0, len(targets), a.block):
        block = targets[b0:b0 + a.block]
        bdir = os.path.join(shots, "b%03d" % block[0]["n"])
        status, done, bad = "OK", [], []
        emu = dex = None
        try:
            emu, dex = session(a.rom, bdir, a.save, a.clip)
            fsp = dex.pv() + dexsweep.OFF["PV.formSpecies"]
            for t in block:
                sp, nat, natname = vals[t["species"]]
                if not enabled(emu, vals["NUM_SPECIES"], sp):
                    dex.manifest["%03d_disabled" % t["n"]] = {"n": t["n"], "species": t["species"], "disabled": True}
                    print("%s is disabled in this build (baseHP 0): skipped" % t["species"])
                    continue
                dex.poke(sp, nat)
                dex.redraw_info()
                got, gotnat = emu.r16(fsp), dex.dexnum()
                name = "%03d_%s" % (t["n"], t["species"][len("SPECIES_"):])
                dex.snap(name)
                shutil.move(os.path.join(bdir, name + ".png"), os.path.join(shots, name + ".png"))
                rec = {"n": t["n"], "species": t["species"], "value": sp, "natdex": natname, "natnum": nat,
                       "formSpecies": got, "dexNum": gotnat, "shot": name}
                dex.manifest[name] = rec
                (done if got == sp and gotnat == nat else bad).append(t["species"])
        except hns.HnsError as e:
            status = "ERROR: %s" % str(e).splitlines()[0]
            if emu:
                try:
                    emu.shot("_error")
                except hns.HnsError:
                    pass
        res = dexsweep.finish(emu, dex, bdir, status) if dex else {"status": status}
        res.update(done=len(done), bad=bad)
        report["b%03d" % block[0]["n"]] = res
        print("block %d-%d %s" % (block[0]["n"], block[-1]["n"], res))
        sys.stdout.flush()
        with open(os.path.join(a.out, "info_report_%d_%d.json" % (a.start, a.start + a.count)), "w") as fh:
            json.dump(report, fh, indent=1)
        if status != "OK":
            break


def cmd_evo(a):
    src = dexsweep.src_tree()
    targets = a.species.split(",") if a.species else EVO_TARGETS
    vals = values_for(src, targets)
    shots = os.path.join(a.out, a.tag)
    emu, dex = None, None
    status, done = "OK", []
    try:
        emu, dex = session(a.rom, shots, a.save, a.clip)
        for k, s in enumerate(targets):
            sp, nat, natname = vals[s]
            dex.poke(sp, nat)
            dex.info_to_evo_page()
            name = "e%02d_%s" % (k, s[len("SPECIES_"):])
            n = dex.pv8("PV.evo.numAllEvolutions")
            dex.snap(name)
            dex.manifest[name] = {"species": s, "value": sp, "natdex": natname,
                                  "formSpecies": emu.r16(dex.pv() + dexsweep.OFF["PV.formSpecies"]),
                                  "numAllEvolutions": n}
            done.append(s)
            dex.evo_page_to_info()
    except hns.HnsError as e:
        status = "ERROR: %s" % str(e).splitlines()[0]
        if emu:
            try:
                emu.shot("_error")
            except hns.HnsError:
                pass
    res = dexsweep.finish(emu, dex, shots, status) if dex else {"status": status}
    res.update(done=len(done))
    with open(os.path.join(a.out, "%s_report.json" % a.tag), "w") as fh:
        json.dump(res, fh, indent=1)
    print(res)


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("cmd", choices=["info", "evo"])
    ap.add_argument("rom")
    ap.add_argument("out")
    ap.add_argument("--save", required=True)
    ap.add_argument("--clip", action="store_true")
    ap.add_argument("--start", type=int, default=0)
    ap.add_argument("--count", type=int, default=100000)
    ap.add_argument("--block", type=int, default=120)
    ap.add_argument("--species", help="evo: comma-separated SPECIES_* instead of EVO_TARGETS")
    ap.add_argument("--tag", default="evo", help="evo: output folder name")
    a = ap.parse_args()
    a.rom = os.path.abspath(a.rom)
    a.out = os.path.abspath(a.out)
    {"info": cmd_info, "evo": cmd_evo}[a.cmd](a)


if __name__ == "__main__":
    main()
