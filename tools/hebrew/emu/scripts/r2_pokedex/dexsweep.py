#!/usr/bin/env python3
"""Pokedex Plus (src/pokedex_plus_hgss.c) page sweep over every entry of the national list.

    dexsweep.py pages ROM OUT --save SAV [--clip] [--start P] [--count N] [--block B]
                [--units imperial|metric] [--no-forms]
        For list positions P .. P+N-1 (0-based, national mode, numerical order), in blocks of B
        entries, one runner per block (OUT/bNNN/): INFO, AREA, STATS, STATS after A (the toggle),
        EVO, FORMS (START on EVO), the forms cursor, CRY, SIZE. For an entry with forms, A on each
        form opens that form's INFO, AREA, STATS (+A), EVO and FORMS pages. A seen-only entry
        has INFO and AREA only (RIGHT on AREA is refused, src/pokedex_area_screen.c:917-921).
        --first-form K: for the entry at --start, visit its forms from K on (a fresh runner, to
        resume after a crash in the middle of an entry's forms).
    dexsweep.py info ROM OUT --save SAV [--clip] [--units imperial|metric]
        INFO pages only, DOWN from the first entry to the last (one runner).
    dexsweep.py moves ROM OUT --save SAV --plan PLAN.json [--clip]
        PLAN: [{"pos": P, "moves": [i, ...]}, ...]: on entry P's STATS page, move the cursor to
        each move index i (UP/DOWN) and shoot the battle info and, after A, the contest info.
    dexsweep.py movescan ROM OUT --save SAV [--clip] [--start P] [--count N]
        Every move of every entry's STATS page; a battle shot at the first occurrence of each
        (move name, egg/level/TM kind), a contest shot (after A) at the first occurrence of each
        contest description; writes OUT/moveplan.json for `moves --plan` on the other ROM.

Each shot is named POS_DEXNUM_NAME_PAGE (POS 1-based); OUT/bNNN/manifest.json records per entry
the dex number, form species, number of forms, moves and evolutions read from sPokedexView.
Struct offsets (OFF below) were measured with offsetof() against both trees
(probe: hns-tools/scratch/screens/r2_pokedex_every_species_and_form/probe/dexprobe.sh); the
Hebrew struct adds sEvoScreenData.linePitch, which falls in padding (same offsets).
Env: HNS_RUNNER, HNS_SRC (constants), as for hns.py.
"""
import argparse
import json
import os
import re
import shutil
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
EMU = os.path.abspath(os.path.join(HERE, "..", ".."))
sys.path.insert(0, EMU)
sys.path.insert(0, os.path.dirname(EMU))
import hns  # noqa: E402
import ladder  # noqa: E402

# English tree (no TEXT_RTL): measured with offsetof() (see the docstring).
OFF_EN = {"PV.pokemonListCount": 1936, "PV.selectedPokemon": 1938, "PV.dexMode": 1942,
          "PV.dexOrder": 1946, "PV.moveSelected": 1964, "PV.movesTotal": 1966,
          "PV.numEggMoves": 1972, "PV.numLevelUpMoves": 1973, "PV.numTeachableMoves": 1974,
          "PV.evo.fromEvoPage": 2012, "PV.evo.numAllEvolutions": 2013, "PV.evo.targetSpecies": 2014,
          "PV.evo.numSeen": 2034, "PV.evo.menuPos": 2045, "PV.forms.numForms": 2088,
          "PV.forms.formIds": 2090, "PV.forms.inSubmenu": 2150, "PV.forms.menuPos": 2151,
          "PV.formSpecies": 2156, "PV.currentPage": 2194, "PV.menuIsOpen": 2199, "PV.menuY": 2202,
          "SB2.pokedex": 24, "SB3.challengeSettings": 16}
# Hebrew tree (TEXT_RTL, include/config/text.h:20): sEvoScreenData.linePitch (u8 after the u32
# arrowSpriteDist[10]) moves sFormScreenData and everything after it 4 bytes on.
OFF_HE = dict(OFF_EN)
for _k in ("PV.forms.numForms", "PV.forms.formIds", "PV.forms.inSubmenu", "PV.forms.menuPos",
           "PV.formSpecies", "PV.currentPage", "PV.menuIsOpen", "PV.menuY"):
    OFF_HE[_k] += 4
OFF = OFF_EN
DEX_MODE_NATIONAL = 1                    # include/constants/pokedex.h:2496-2499
UNIT_BIT = 0x40                          # ChallengeSettings.unitSystem, byte 0 bit 6 (include/global.h:262); 1 = imperial
T = "pokedex_plus_hgss:"
CONTINUE = os.path.join(EMU, "scripts", "continue.txt")


def load_names(src):
    nat = []
    text = open(os.path.join(src, "include", "constants", "pokedex.h"), encoding="utf-8").read()
    body = text[text.index("enum NationalDexOrder"):]
    body = body[:body.index("};")]
    nat = [n for n in re.findall(r"\bNATIONAL_DEX_([A-Z0-9_]+)", body) if n != "NONE"]
    sp = {}
    for m in re.finditer(r"^#define SPECIES_([A-Z0-9_]+)\s+(\d+)\s*$",
                         open(os.path.join(src, "include", "constants", "species.h")).read(), re.M):
        sp.setdefault(int(m.group(2)), m.group(1))
    return nat, sp


class Dex:
    def __init__(self, emu, src, outdir):
        self.emu = emu
        self.outdir = outdir
        global OFF
        OFF = OFF_HE if "sRtlCharClass" in emu.elf.byname else OFF_EN
        self.pvp = emu.sym("sPokedexView")
        self.itp = emu.sym("sPokedexListItem")
        self.nat, self.spn = load_names(src)
        self.manifest = {}
        self.shots = []
        self.tasks = {}

    # ---- memory
    def pv(self):
        return self.emu.r32(self.pvp)

    def pv16(self, k):
        return self.emu.r16(self.pv() + OFF[k])

    def pv8(self, k):
        return self.emu.r8(self.pv() + OFF[k])

    def dexnum(self):
        p = self.emu.r32(self.itp)
        return self.emu.r16(p) if p else 0

    def owned(self):
        p = self.emu.r32(self.itp)
        return bool(self.emu.r16(p + 2) & 2) if p else False

    def sel(self):
        return self.pv16("PV.selectedPokemon")

    def list_entry(self, i):
        b = self.emu.read(self.pv() + 4 * i, 4)
        return b[0] | b[1] << 8, bool(b[2] & 1), bool(b[2] & 2)

    def name(self, dexnum):
        return self.nat[dexnum - 1] if 0 < dexnum <= len(self.nat) else "D%d" % dexnum

    # ---- waits
    def task(self, name):
        if name not in self.tasks:
            try:
                self.tasks[name] = self.emu.sym(T + name)
            except hns.HnsError:
                self.tasks[name] = self.emu.sym(name)
        return self.tasks[name]

    def active(self, name):
        want = self.task(name)
        return any(f == want for _, f, _ in self.emu.tasks())

    def wait(self, name, cond=None, maxf=1200, what=None):
        want = self.task(name)

        def ok():
            if not any(f == want for _, f, _ in self.emu.tasks()):
                return False
            return cond() if cond else True
        self.emu.wait_until(ok, maxf, what or name, step=2)
        self.emu.wait_quiet(600)

    def wait_area(self, maxf=1200):
        def ok():
            d = self.emu.task_data("Task_HandlePokedexAreaScreenInput")
            return bool(d) and d[0][0] == 1
        self.emu.wait_until(ok, maxf, "the AREA page reading input", step=2)
        self.emu.wait_quiet(600)

    def snap(self, name):
        self.emu.frames(2)
        self.emu.snap(name)
        self.shots.append(name)

    def key(self, k, idle=2):
        self.emu.tap(k, idle)

    # ---- setup
    def open_dex(self, units):
        emu = self.emu
        sb2 = emu.sb2()
        emu.w8(sb2 + OFF["SB2.pokedex"] + 1, DEX_MODE_NATIONAL)
        emu.w8(sb2 + OFF["SB2.pokedex"] + 0, 0)                    # ORDER_NUMERICAL
        if units:
            sb3 = emu.sb3()
            b = emu.r8(sb3 + OFF["SB3.challengeSettings"])
            emu.w8(sb3 + OFF["SB3.challengeSettings"], (b | UNIT_BIT) if units == "imperial" else (b & ~UNIT_BIT))
        ladder.start_menu_action(emu, 0)
        if not emu.wait_cb2("CB2_Pokedex", 900):
            raise hns.HnsError("the Pokedex did not open (callback2 %s)" % emu.cb2_name())
        self.wait("Task_HandlePokedexInput", maxf=900)
        emu.frames(16)

    def list_goto(self, pos):
        for _ in range(2000):
            cur = self.sel()
            if cur == pos:
                break
            if pos - cur >= 7:
                self.key("RIGHT", 2)
            elif pos > cur:
                self.key("DOWN", 2)
            elif cur - pos >= 7:
                self.key("LEFT", 2)
            else:
                self.key("UP", 2)
            self.wait("Task_HandlePokedexInput", maxf=300)
        if self.sel() != pos:
            raise hns.HnsError("list cursor at %d, wanted %d" % (self.sel(), pos))
        self.emu.frames(16)

    def list_to_info(self):
        self.key("A", 2)
        self.wait("Task_HandleInfoScreenInput", maxf=900)

    # ---- one entry
    def tag(self, pos, extra=""):
        d = self.dexnum()
        return "%03d_%04d_%s%s" % (pos + 1, d, self.name(d), extra)

    def info_to_evo(self, prefix, shoot=True):
        """INFO -> AREA -> STATS (+A) -> EVO, shooting each page (shoot=False: just go)."""
        self.key("RIGHT")
        self.wait_area()
        if shoot:
            self.snap(prefix + "_2area")
        self.key("RIGHT")
        self.wait("Task_HandleStatsScreenInput")
        rec = {"movesTotal": self.pv16("PV.movesTotal"), "egg": self.pv8("PV.numEggMoves"),
               "lvl": self.pv8("PV.numLevelUpMoves"), "tm": self.pv16("PV.numTeachableMoves")}
        if shoot:
            self.snap(prefix + "_3stats")
            self.key("A")
            self.emu.wait_quiet(300)
            self.snap(prefix + "_4stats_toggle")
        self.key("RIGHT")
        self.wait("Task_HandleEvolutionScreenInput")
        n = self.pv8("PV.evo.numAllEvolutions")
        tgt = self.emu.read(self.pv() + OFF["PV.evo.targetSpecies"], 20)
        rec["evos"] = [self.spn.get(tgt[2 * i] | tgt[2 * i + 1] << 8, "?") for i in range(min(n, 10))]
        if shoot:
            self.snap(prefix + "_5evo")
        return rec

    def evo_to_forms(self, prefix, shoot=True):
        self.key("START")
        self.wait("Task_HandleFormsScreenInput")
        n = self.pv8("PV.forms.numForms")
        ids = self.emu.read(self.pv() + OFF["PV.forms.formIds"], 60)
        ids = [ids[2 * i] | ids[2 * i + 1] << 8 for i in range(1, n + 1)]
        if shoot:
            self.snap(prefix + "_6forms")
        return n, ids

    def entry(self, pos, forms=True, first_form=1):
        emu = self.emu
        d = self.dexnum()
        prefix = self.tag(pos)
        rec = {"pos": pos + 1, "dexNum": d, "name": self.name(d), "owned": self.owned(), "shots": []}
        first = len(self.shots)
        self.snap(prefix + "_1info")
        if not rec["owned"]:
            self.key("RIGHT")
            self.wait_area()
            self.snap(prefix + "_2area")
            self.key("LEFT")
            self.wait("Task_HandleInfoScreenInput")
            rec["shots"] = self.shots[first:]
            self.manifest[prefix] = rec
            return
        rec.update(self.info_to_evo(prefix))
        nf, ids = self.evo_to_forms(prefix)
        rec["numForms"], rec["formIds"] = nf, ids
        if nf:
            self.key("A")
            emu.wait_quiet(300)
            emu.frames(4)
            self.snap(prefix + "_6forms_cursor01")
            self.key("B")
            emu.wait_quiet(300)
        self.key("START")
        self.wait("Task_HandleEvolutionScreenInput")
        self.key("RIGHT")
        self.wait("Task_HandleCryScreenInput")
        emu.frames(30)
        self.snap(prefix + "_7cry")
        self.key("RIGHT")
        self.wait("Task_HandleSizeScreenInput")
        self.snap(prefix + "_8size")
        self.key("B")
        self.wait("Task_HandleInfoScreenInput")
        if nf and forms:
            rec["forms"] = []
            for k in range(first_form, nf + 1):
                rec["forms"].append(self.form(pos, k, nf))
            # back on INFO(pos) via the list
        rec["shots"] = self.shots[first:]
        self.manifest[prefix] = rec

    def form(self, pos, k, nf):
        """From INFO(pos): EVO -> FORMS -> cursor to form k -> A -> that form's pages -> B (list)
        -> A (INFO(pos) again)."""
        emu = self.emu
        prefix = self.tag(pos)
        self.info_to_evo(prefix, shoot=False)
        self.evo_to_forms(prefix, shoot=False)
        self.key("A")
        emu.wait_quiet(300)
        for _ in range(k - 1):
            self.key("RIGHT", 4)
        emu.frames(4)
        if self.pv8("PV.forms.menuPos") != k:
            raise hns.HnsError("forms cursor at %d, wanted %d" % (self.pv8("PV.forms.menuPos"), k))
        if k > 1 and (k in (2, 7, 8, nf) or k % 7 == 0):
            self.snap("%s_6forms_cursor%02d" % (prefix, k))
        self.key("A")
        self.wait("Task_HandleInfoScreenInput", cond=lambda: self.pv16("PV.formSpecies") != 0 or True)
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

    def next_info(self):
        before = self.dexnum()
        self.key("DOWN")
        self.wait("Task_HandleInfoScreenInput", cond=lambda: self.dexnum() != before)

    def save_manifest(self):
        with open(os.path.join(self.outdir, "manifest.json"), "w") as fh:
            json.dump(self.manifest, fh, indent=1, ensure_ascii=False)


def boot(rom, outdir, save, clip):
    os.makedirs(outdir, exist_ok=True)
    cur = os.path.join(outdir, "cur.sav")
    shutil.copyfile(save, cur)
    emu = hns.Emu(rom, None, outdir, cur)
    if clip:
        import cliptour
        cliptour.install(emu, outdir, echo=False)
    emu.run_script(CONTINUE)
    return emu


def finish(emu, dex, outdir, status):
    dex.save_manifest()
    rc = emu.close()
    with open(os.path.join(outdir, "run.log"), "w") as fh:
        fh.write("\n".join(emu.log) + "\n")
    clipped = emu.clip.total() if getattr(emu, "clip", None) else None
    return {"status": status, "shots": len(dex.shots), "clipped": clipped, "rc": rc}


def src_tree():
    s = os.environ.get("HNS_SRC")
    if not s:
        raise SystemExit("set HNS_SRC to the source tree of the ROM")
    return s


def cmd_pages(a):
    src = src_tree()
    report = {}
    end = a.start + a.count
    for b0 in range(a.start, end, a.block):
        b1 = min(b0 + a.block, end)
        out = os.path.join(a.out, "b%03d" % b0)
        emu = boot(a.rom, out, a.save, a.clip)
        dex = Dex(emu, src, out)
        status = "OK"
        try:
            dex.open_dex(a.units)
            count = dex.pv16("PV.pokemonListCount")
            b1 = min(b1, count)
            if b0 >= b1:
                status = "EMPTY (list has %d entries)" % count
                raise StopIteration
            dex.list_goto(b0)
            dex.list_to_info()
            for pos in range(b0, b1):
                if dex.sel() != pos:
                    raise hns.HnsError("at list position %d, wanted %d" % (dex.sel(), pos))
                dex.entry(pos, forms=not a.no_forms, first_form=a.first_form if pos == a.start else 1)
                if pos + 1 < b1:
                    dex.next_info()
        except StopIteration:
            pass
        except hns.HnsError as e:
            status = "ERROR: %s" % str(e).splitlines()[0]
            try:
                emu.shot("_error")
            except hns.HnsError:
                pass
        report["b%03d" % b0] = finish(emu, dex, out, status)
        if status.startswith("EMPTY"):
            shutil.rmtree(out, ignore_errors=True)
            break
        print("b%03d %s" % (b0, report["b%03d" % b0]))
        sys.stdout.flush()
    with open(os.path.join(a.out, "report_%d_%d.json" % (a.start, end)), "w") as fh:
        json.dump(report, fh, indent=1)


def cmd_info(a):
    src = src_tree()
    out = a.out
    emu = boot(a.rom, out, a.save, a.clip)
    dex = Dex(emu, src, out)
    status = "OK"
    try:
        dex.open_dex(a.units)
        count = dex.pv16("PV.pokemonListCount")
        dex.list_goto(a.start)
        dex.list_to_info()
        pos = a.start
        while True:
            d = dex.dexnum()
            nm = dex.tag(pos, "_1info")
            dex.snap(nm)
            dex.manifest[nm] = {"pos": pos + 1, "dexNum": d, "name": dex.name(d), "owned": dex.owned()}
            if pos + 1 >= count:
                break
            dex.next_info()
            pos = dex.sel()
    except hns.HnsError as e:
        status = "ERROR: %s" % str(e).splitlines()[0]
        emu.shot("_error")
    print(finish(emu, dex, out, status))


def cmd_moves(a):
    src = src_tree()
    plan = json.load(open(a.plan))
    out = a.out
    emu = boot(a.rom, out, a.save, a.clip)
    dex = Dex(emu, src, out)
    status = "OK"
    try:
        dex.open_dex(a.units)
        for item in plan:
            pos = item["pos"]
            dex.list_goto(pos)
            dex.list_to_info()
            prefix = dex.tag(pos)
            dex.key("RIGHT")
            dex.wait_area()
            dex.key("RIGHT")
            dex.wait("Task_HandleStatsScreenInput")
            total = dex.pv16("PV.movesTotal")
            negg, nlvl = dex.pv8("PV.numEggMoves"), dex.pv8("PV.numLevelUpMoves")
            for toggle in (0, 1):
                for i in item["moves"]:
                    if i >= total:
                        continue
                    for _ in range(400):
                        cur = dex.pv16("PV.moveSelected")
                        if cur == i:
                            break
                        dex.key("DOWN" if cur < i else "UP", 2)
                        emu.frames(2)
                    kind = "egg" if i < negg else ("level" if i < negg + nlvl else "tm")
                    dex.snap("%s_m%03d_%s_%s" % (prefix, i, kind, "contest" if toggle else "battle"))
                    dex.manifest.setdefault(prefix, {"pos": pos + 1, "movesTotal": total, "moves": []})["moves"].append(i)
                if toggle == 0:
                    dex.key("A")
                    emu.wait_quiet(300)
            dex.key("B")
            dex.wait("Task_HandlePokedexInput")
            emu.frames(16)
    except hns.HnsError as e:
        status = "ERROR: %s" % str(e).splitlines()[0]
        emu.shot("_error")
    print(finish(emu, dex, out, status))


def read_str(emu, sym, n=64):
    b = emu.read(emu.sym(sym), n)
    return b.split(b"\xff")[0].hex()


def cmd_movescan(a):
    """Every move of every entry's STATS page (UP/DOWN); a shot at the first occurrence of each
    (move name, kind) pair, kind = egg / level / tm-or-tutor (the item box differs), and a
    contest shot (after A) at the first occurrence of each contest description. Writes
    OUT/moveplan.json for the English twin (`moves --plan`)."""
    src = src_tree()
    out = a.out
    emu = boot(a.rom, out, a.save, a.clip)
    dex = Dex(emu, src, out)
    seen, seen_contest, plan = set(), set(), []
    status = "OK"
    try:
        dex.open_dex(a.units)
        count = dex.pv16("PV.pokemonListCount")
        for pos in range(a.start, min(count, a.start + a.count)):
            dex.list_goto(pos)
            dex.list_to_info()
            if not dex.owned():
                dex.key("B")
                dex.wait("Task_HandlePokedexInput")
                emu.frames(16)
                continue
            prefix = dex.tag(pos)
            dex.key("RIGHT")
            dex.wait_area()
            dex.key("RIGHT")
            dex.wait("Task_HandleStatsScreenInput")
            total = dex.pv16("PV.movesTotal")
            negg, nlvl = dex.pv8("PV.numEggMoves"), dex.pv8("PV.numLevelUpMoves")
            idxs = []
            for i in range(total):
                if i:
                    dex.key("DOWN", 2)
                    for _ in range(30):
                        if dex.pv16("PV.moveSelected") == i:
                            break
                        emu.frames(1)
                kind = "egg" if i < negg else ("level" if i < negg + nlvl else "tm")
                key = (read_str(emu, "gStringVar3"), kind)
                if key in seen:
                    continue
                seen.add(key)
                idxs.append(i)
                dex.snap("%s_m%03d_%s_battle" % (prefix, i, kind))
                dex.key("A")
                emu.wait_quiet(300)
                ck = read_str(emu, "gStringVar4", 200)
                if ck not in seen_contest:
                    seen_contest.add(ck)
                    dex.snap("%s_m%03d_%s_contest" % (prefix, i, kind))
                dex.key("A")
                emu.wait_quiet(300)
            if idxs:
                plan.append({"pos": pos, "moves": idxs, "name": prefix})
            dex.manifest[prefix] = {"pos": pos + 1, "movesTotal": total, "egg": negg, "level": nlvl, "snapped": idxs}
            dex.key("B")
            dex.wait("Task_HandlePokedexInput")
            emu.frames(16)
            print("%s: %d moves, %d new, %d keys so far" % (prefix, total, len(idxs), len(seen)))
            sys.stdout.flush()
    except hns.HnsError as e:
        status = "ERROR: %s" % str(e).splitlines()[0]
        emu.shot("_error")
    with open(os.path.join(out, "moveplan.json"), "w") as fh:
        json.dump(plan, fh, indent=0)
    print(finish(emu, dex, out, status))


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("cmd", choices=["pages", "info", "moves", "movescan"])
    ap.add_argument("rom")
    ap.add_argument("out")
    ap.add_argument("--save", required=True)
    ap.add_argument("--clip", action="store_true")
    ap.add_argument("--start", type=int, default=0)
    ap.add_argument("--count", type=int, default=10000)
    ap.add_argument("--block", type=int, default=50)
    ap.add_argument("--units", choices=["imperial", "metric"], default=None)
    ap.add_argument("--no-forms", action="store_true")
    ap.add_argument("--first-form", type=int, default=1,
                    help="for the entry at --start, visit forms from this one on (resume after a crash)")
    ap.add_argument("--plan")
    a = ap.parse_args()
    a.rom = os.path.abspath(a.rom)
    a.out = os.path.abspath(a.out)
    {"pages": cmd_pages, "info": cmd_info, "moves": cmd_moves, "movescan": cmd_movescan}[a.cmd](a)


if __name__ == "__main__":
    main()
