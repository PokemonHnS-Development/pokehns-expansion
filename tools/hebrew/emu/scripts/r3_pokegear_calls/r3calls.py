#!/usr/bin/env python3
"""hns.py + the r1 field-UI ops (ofui.py: forcecall, svc.py) + ops for the r3 PokeGear call tours:
every H&S trainer call text in the field call box and in the PokeGear CALL window, the
close-by message, Prof. Elm's Pokedex rating and Mom's gift calls.

    r3calls.py tour ROM OUT --tours <this folder> [--only RE] [--clip]
    r3calls.py gen SRC_TREE              (re)write the generated tours in this folder

Which text a trainer call shows (SelectMatchCallMessage, src/match_call.c:1802-1830):
Battle when gSaveBlock1Ptr->trainerRematches[rematchIdx] != 0, FoundItem when the trainer's
FLAG_<NAME>_HAS_ITEM_HNS is set, otherwise generalTexts[Random() % numGeneralTexts]; then
STR_VAR_3 = the species of a random member of the trainer's party. The ops below make the
choice deterministic: they set the rematch byte and item flag for the text kind wanted, then
save a state just before the message is chosen and retry from it with fresh gRngValue words
until gStringVar4 holds the wanted label (identified by expanding every candidate label from
the ROM and comparing). For texts with {STR_VAR_3} they keep the attempt whose species name
is the widest (pixel width from tools/hebrew/textwidth.py when it loads, else byte length).

Ops:
    mcclear                 clear every trainer's registered flag (TRAINER_REGISTERED_FLAGS_START+i,
                            i < REMATCH_SPECIAL_TRAINER_START), rematch byte and HAS_ITEM flag
    mcreg NAME|all          register one trainer (Joey, Wade, ...) or all 40 (flag only, no message)
    mcfield NAME KIND PREFIX [MAXTRY]
                            field call: force calls (forcecall) until NAME calls, choose KIND
                            (General1..3, Battle, FoundItem[:N] = gift item N), shot every page
                            (PREFIX_NN), PREFIX_last, then B until the player is free
    mclistopen              START > POKEGEAR > CALL, the list on screen, cursor row 0
    mclistrow N|NAME        move the list cursor to row N, or to trainer NAME's row
    mclist NAME KIND PREFIX [MAXTRY]
                            from the list: cursor to NAME, A (CALL/CANCEL box, shot PREFIX_opts
                            once per trainer), A on CALL, choose KIND as above, pages, PREFIX_last,
                            A back to the list
    mcelm PREFIX            cursor to row 0 (Prof. Elm), A, A on CALL, pages, PREFIX_last, A
    mcnearby NAME PREFIX    cursor to NAME, A, A: the close-by message (no text choice involved)
    mcrow N PREFIX          cursor to row N (a special contact), A, A, pages, PREFIX_last, A
    dexset johto|obt SEEN CAUGHT
                            clear dexSeen/dexCaught and mark the first SEEN entries of the Johto
                            (sJohtoToNationalOrder) or obtainable (sObtainableToNationalOrder) list
                            seen and the first CAUGHT of them caught
    natdex 0|1              national dex off/on (FLAG_SYS_NATIONAL_DEX)
    mcexpect LABEL          stop unless the last identified text is LABEL
    mcjson                  write OUT/mc.json (every call: label, species, attempts, pages)

SaveBlock1 offsets come from literal pools and are checked against the ELF before use:
trainerRematches at +0x10E8 (SetRematchIdForTrainer), dexSeen +0x39C0 / dexCaught +0x3A7F
(GetSetPokedexFlag).
"""
import json
import os
import random
import re
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
EMU = os.path.abspath(os.path.join(HERE, "..", ".."))
sys.path.insert(0, os.path.join(EMU, "scripts", "r1_overworld_field_ui"))
sys.path.insert(0, EMU)
sys.path.insert(0, os.path.dirname(EMU))          # tools/hebrew (textwidth)
import hns                      # noqa: E402
import ofui                     # noqa: E402,F401  (forcecall + svc ops)
from hns import script_op, HnsError, TourTimeout, _arg   # noqa: E402

SB1_REMATCHES = 0x10E8
SB1_DEX_SEEN = 0x39C0
SB1_DEX_CAUGHT = 0x3A7F
DEX_REGION = 0xBF
EOS = 0xFF
RNG_WORDS = 4
TASK_STATE_PRINT_INTRO = 4      # sMatchCallTaskFuncs (src/match_call.c): LoadGfx, DrawWindow,
TASK_STATE_PRINT_MESSAGE = 5    # ReadyIntro, SlideWindowIn, PrintIntro, PrintMessage, ...
MARKER = 0x5A5AA5A5
MC_CALLBACKS = ("CB2_HandleMatchCallInput", "CB2_HandleMatchCallOptionsInput",
                "CB2_HandleCheckPageInput", "CB2_HandleCallExitInput")


# ---------------------------------------------------------------- source / ROM data

def trainer_table(src):
    """sHnsMatchCallTrainers (src/match_call.c): [(Name, TRAINER_X, nGeneral, item flag, item var,
    [items])] in table order."""
    text = open(os.path.join(src, "src", "match_call.c"), encoding="utf-8").read()
    lists = {m.group(1): re.findall(r"ITEM_\w+", m.group(2))
             for m in re.finditer(r"static const u16 (s\w+GiftItems)\[\] = \{([^}]*)\}", text)}
    body = text[text.index("sHnsMatchCallTrainers[] ="):]
    body = body[:body.index("};")]
    out = []
    for m in re.finditer(r"HNS_MC_(ENTRY|ITEM)([23])\((\w+),\s*(TRAINER_\w+)(?:,\s*(FLAG_\w+),\s*(VAR_\w+),\s*(\w+))?\)", body):
        kind, n, name, tr, flag, var, items = m.groups()
        out.append(dict(name=name, trainer=tr, ngen=int(n), flag=flag, var=var,
                        items=lists.get(items, []) if items else []))
    return out


def kinds_of(t):
    k = ["General%d" % (i + 1) for i in range(t["ngen"])] + ["Battle"]
    if t["flag"]:
        k += ["FoundItem:0"]           # the call text names no item (data/text/match_call_hns.inc)
    return k


class Data:
    """ROM bytes, trainer table, rematch table, labels, for one Emu."""

    def __init__(self, emu):
        self.emu = emu
        self.rom = open(emu.rom, "rb").read()
        self.src = hns.src_dir(emu.elf)
        self.trainers = trainer_table(self.src)
        self.by_name = {t["name"].lower(): t for t in self.trainers}
        self.check_offsets()
        tab = emu.sym("gRematchTable")
        self.n_rematch = emu.elf.size("gRematchTable") // 16
        self.rematch = []
        for i in range(self.n_rematch):
            b = self.romread(tab + 16 * i, 16)
            # struct RematchTrainer: u16 trainerIds[REMATCHES_COUNT = 5], mapGroup, mapNum, pad
            self.rematch.append((int.from_bytes(b[0:2], "little"), int.from_bytes(b[10:12], "little"),
                                 int.from_bytes(b[12:14], "little"),
                                 [int.from_bytes(b[2 * j:2 * j + 2], "little") for j in range(5)]))
        for t in self.trainers:
            t["id"] = emu.const(t["trainer"])
            t["idx"] = next((i for i, r in enumerate(self.rematch) if r[0] == t["id"]), None)
            if t["idx"] is None:
                raise HnsError("%s is not in gRematchTable" % t["trainer"])
            t["map"] = self.rematch[t["idx"]][1:3]
            t["parties"] = [x for x in self.rematch[t["idx"]][3] if x]
        self.labels = {}
        for t in self.trainers:
            for k in ["General%d" % (i + 1) for i in range(t["ngen"])] + ["Battle"] + (["FoundItem"] if t["flag"] else []):
                lab = "MatchCall_HNS_%s_%s" % (t["name"], k)
                self.labels[lab] = self.cstr(emu.sym(lab))
        self.special_start = emu.const("REMATCH_SPECIAL_TRAINER_START")
        self.reg_start = emu.const("TRAINER_REGISTERED_FLAGS_START")
        self.model = None
        try:
            import textwidth
            self.model = textwidth.TextModel(tree=self.src)
        except Exception as e:                      # the English tree has no Hebrew drafts etc.
            sys.stderr.write("r3calls: textwidth unavailable (%s), species ranked by bytes\n" % e)

    def romread(self, addr, n):
        o = addr - 0x08000000
        return self.rom[o:o + n]

    def cstr(self, addr, limit=2000):
        o = addr - 0x08000000
        e = self.rom.index(bytes([EOS]), o, o + limit)
        return self.rom[o:e]

    def check_offsets(self):
        def lit(fn, want):
            a = self.emu.sym(fn) & ~1
            b = self.romread(a, 0x80)
            words = {int.from_bytes(b[i:i + 4], "little") for i in range(0, len(b) - 3, 2)}
            if want not in words:
                raise HnsError("%s no longer holds the literal %#x: re-measure the SaveBlock1 offsets" % (fn, want))
        lit("SetRematchIdForTrainer.constprop.0" if self._has("SetRematchIdForTrainer.constprop.0")
            else "SetRematchIdForTrainer", SB1_REMATCHES)
        lit("GetSetPokedexFlag", SB1_DEX_CAUGHT)

    def _has(self, name):
        try:
            self.emu.sym(name)
            return True
        except HnsError:
            return False

    def trainer(self, name):
        t = self.by_name.get(name.lower())
        if not t:
            raise HnsError("no H&S match call trainer %s" % name)
        return t

    def width(self, raw):
        if self.model is not None:
            try:
                return self.model.width(self.model.decode(raw))
            except Exception:
                pass
        return len(raw) * 6

    def decode(self, raw):
        if self.model is not None:
            try:
                return self.model.decode(raw)
            except Exception:
                pass
        return raw.hex()


def data(emu):
    d = getattr(emu, "_r3data", None)
    if d is None:
        d = emu._r3data = Data(emu)
        emu._r3log = []
    return d


def expand(raw, subs):
    """StringExpandPlaceholders for the placeholders the call texts use (FD xx -> subs[xx])."""
    out, i = bytearray(), 0
    while i < len(raw):
        c = raw[i]
        if c == 0xFD and i + 1 < len(raw) and raw[i + 1] in subs:
            out += subs[raw[i + 1]]
            i += 2
            continue
        out.append(c)
        i += 1
    return bytes(out)


def ram_cstr(emu, addr, n=1000):
    b = emu.read(addr, n)
    return b[:b.index(EOS)] if EOS in b else b


def identify(emu, labels):
    """(best label, exact?, gStringVar4 bytes, gStringVar3 bytes)."""
    d = data(emu)
    s4 = ram_cstr(emu, emu.sym("gStringVar4"))
    s3 = ram_cstr(emu, emu.sym("gStringVar3"), 32)
    player = ram_cstr(emu, emu.sb2(), 8)
    subs = {0x01: player, 0x04: s3, 0x05: b"",
            0x02: ram_cstr(emu, emu.sym("gStringVar1"), 32), 0x03: ram_cstr(emu, emu.sym("gStringVar2"), 32)}
    best, score, exact = None, -1, False
    for lab in labels:
        exp = expand(d.labels[lab], subs)
        n = 0
        for a, b in zip(exp, s4):
            if a != b:
                break
            n += 1
        if exp == s4:
            return lab, True, s4, s3
        if n > score:
            best, score = lab, n
    return best, exact, s4, s3


# ---------------------------------------------------------------- state helpers

def rematch_addr(emu, idx):
    return emu.sb1() + SB1_REMATCHES + idx


def prep(emu, t, kind):
    """Rematch byte and item flag/var for KIND (General*, Battle, FoundItem[:N])."""
    emu.w8(rematch_addr(emu, t["idx"]), 1 if kind == "Battle" else 0)
    if t["flag"]:
        on = kind.startswith("FoundItem")
        emu.set_flag(emu.const(t["flag"]), on)
        if on:
            n = int(kind.split(":")[1]) if ":" in kind else 0
            emu.set_var(emu.const(t["var"]), emu.const(t["items"][n]))


def want_label(t, kind):
    return "MatchCall_HNS_%s_%s" % (t["name"], kind.split(":")[0])


def all_labels_of(d, t):
    return [l for l in d.labels if l.startswith("MatchCall_HNS_%s_" % t["name"])]


def choose(emu, t, kind, maxtry, where):
    """The intro page ("……" in the field, the calling dots in the Pokegear) waits for A and
    gStringVar4 holds MARKER; the message is chosen on the A press. Saves a state, then
    retries from it (fresh gRngValue words, A) until the wanted label is chosen (and, when it
    has {STR_VAR_3}, the widest species seen in up to 6 hits / MAXTRY attempts). Returns a record."""
    d = data(emu)
    s4 = emu.sym("gStringVar4")
    rng = emu.sym("gRngValue")
    ssf = os.path.join(emu.outdir, "_choose.ss")
    want = want_label(t, kind)
    has_sv3 = b"\xfd\x04" in d.labels[want]
    labels = all_labels_of(d, t)
    emu.send("ss %s" % ssf)
    emu.sync()
    seen, hits, best = {}, 0, None
    rnd = random.Random(hash((t["name"], kind, where)) & 0xFFFFFFFF)
    tries = 0
    first_unseeded = True
    while tries < maxtry:
        tries += 1
        emu.send("sl %s" % ssf)
        words = None
        if not first_unseeded:
            words = [rnd.getrandbits(32) for _ in range(RNG_WORDS)]
            for i, w in enumerate(words):
                emu.w32(rng + 4 * i, w)
        first_unseeded = False
        emu.tap("A", 0)
        emu.wait_until(lambda: emu.r32(s4) != MARKER, 120, "the call message to be chosen", step=1)
        lab, exact, raw4, raw3 = identify(emu, labels)
        seen[lab] = seen.get(lab, 0) + 1
        if lab == want and exact:
            hits += 1
            w = d.width(raw3) if has_sv3 else 0
            if best is None or w > best[0]:
                best = (w, words, raw3)
            if not has_sv3 or hits >= 6:
                break
    if best is None:
        raise HnsError("%s %s: %s never chosen in %d attempt(s) (saw %s)" % (where, t["name"], want, tries, seen))
    # replay the chosen attempt
    emu.send("sl %s" % ssf)
    if best[1] is not None:
        for i, w in enumerate(best[1]):
            emu.w32(rng + 4 * i, w)
    emu.tap("A", 0)
    emu.wait_until(lambda: emu.r32(s4) != MARKER, 120, "the call message to be chosen", step=1)
    lab, exact, raw4, raw3 = identify(emu, labels)
    if lab != want or not exact or (has_sv3 and raw3 != best[2]):
        raise HnsError("%s %s: replay chose %s (wanted %s)" % (where, t["name"], lab, want))
    try:
        os.remove(ssf)
    except OSError:
        pass
    rec = dict(where=where, trainer=t["name"], kind=kind, label=want, attempts=tries,
               species=d.decode(raw3) if has_sv3 else None, species_width=best[0] if has_sv3 else None,
               seen=seen)
    emu._r3last = want
    print("choose %s %s %s: %s after %d attempt(s)%s @%d" % (where, t["name"], kind, want, tries,
          (", STR_VAR_3 %s (%d px)" % (rec["species"], best[0])) if has_sv3 else "", emu.sync()))
    return rec


def once(emu, name):
    done = getattr(emu, "_once", set())
    if name not in done:
        emu.frames(2)
        shot(emu, name)
        done.add(name)
        emu._once = done


def log_rec(emu, rec):
    emu._r3log.append(rec)
    with open(os.path.join(emu.outdir, "mc.json"), "w") as fh:
        json.dump(emu._r3log, fh, ensure_ascii=False, indent=1)


def shot(emu, name):
    emu.frames(2)
    emu.shot(name)
    emu.shots = getattr(emu, "shots", []) + [name]


# ---------------------------------------------------------------- ops

@script_op("mcclear")
def _op_mcclear(emu, f, path):
    d = data(emu)
    for i in range(d.special_start):
        emu.set_flag(d.reg_start + i, False)
        emu.w8(rematch_addr(emu, i), 0)
    for t in d.trainers:
        if t["flag"]:
            emu.set_flag(emu.const(t["flag"]), False)
    print("mcclear: %d registered flags, rematch bytes and %d item flags cleared @%d"
          % (d.special_start, sum(1 for t in d.trainers if t["flag"]), emu.sync()))


@script_op("mcbeat")
def _op_mcbeat(emu, f, path):
    """mcbeat all|NAME...: mark every rematch party of the trainer(s) beaten (TRAINER_FLAGS_START +
    trainerIds[1..4]), so STR_VAR_3 comes from the last party (GetLastBeatenRematchTrainerId,
    src/battle_setup.c:2303-2320)."""
    d = data(emu)
    start = emu.const("TRAINER_FLAGS_START")
    ts = d.trainers if f[1] == "all" else [d.trainer(n) for n in f[1:]]
    for t in ts:
        for tid in t["parties"][1:]:
            emu.set_flag(start + tid, True)
    print("mcbeat: %d trainer(s), last parties %s @%d" % (len(ts), [t["parties"][-1] for t in ts], emu.sync()))


@script_op("mcreg")
def _op_mcreg(emu, f, path):
    d = data(emu)
    ts = d.trainers if f[1] == "all" else [d.trainer(n) for n in f[1:]]
    for t in ts:
        emu.set_flag(d.reg_start + t["idx"], True)
    print("mcreg: %s @%d" % (",".join(t["name"] for t in ts), emu.sync()))


@script_op("mcinfo")
def _op_mcinfo(emu, f, path):
    d = data(emu)
    (g, n, _, _, _), (x, y) = emu.location()
    mh = emu.sym("gMapHeader")
    reg = [t["name"] for t in d.trainers if emu.get_flag(d.reg_start + t["idx"])]
    rem = [t["name"] for t in d.trainers if emu.r8(rematch_addr(emu, t["idx"]))]
    items = [t["name"] for t in d.trainers if t["flag"] and emu.get_flag(emu.const(t["flag"]))]
    print("mcinfo: map %d.%d (%d,%d) mapsec %d type %d; FLAG_HAS_MATCH_CALL %d; registered %s; rematch %s; items %s"
          % (g, n, x, y, emu.r8(mh + 0x14), emu.r8(mh + 0x17), emu.get_flag(emu.const("FLAG_HAS_MATCH_CALL")),
             reg, rem, items))
    for t in d.trainers:
        print("  %-8s %-22s idx %3d map %d.%d ngen %d items %s" % (t["name"], t["trainer"], t["idx"],
              t["map"][0], t["map"][1], t["ngen"], t["items"]))


def wait_call_task(emu, maxsteps):
    """forcecall's stepping (ofui.py), returning as soon as ExecuteMatchCall runs."""
    st = emu.sym("sMatchCallState")
    for i in range(maxsteps):
        emu.w32(st, 0)
        emu.w8(st + 6, 29)
        emu.frames(10, "LEFT" if i % 2 == 0 else "RIGHT")
        for _ in range(40):
            emu.frames(2)
            if emu.task_data("ExecuteMatchCall"):
                return emu.r16(st + 4)
        emu.wait_controllable(300)
    raise TourTimeout("no call after %d steps" % maxsteps)


@script_op("mcfield")
def _op_mcfield(emu, f, path):
    d = data(emu)
    t, kind, prefix = d.trainer(f[1]), f[2], f[3]
    maxtry = _arg(f, 4, 40)
    prep(emu, t, kind)
    who = wait_call_task(emu, 80)
    if who != t["id"]:
        raise HnsError("mcfield: trainer %d called, wanted %s (%d)" % (who, t["trainer"], t["id"]))
    s4 = emu.sym("gStringVar4")
    emu.w32(s4, MARKER)
    st0 = emu.task_data("ExecuteMatchCall")[0][0]
    if st0 > TASK_STATE_PRINT_INTRO:
        raise HnsError("mcfield: the call task was already in state %d" % st0)
    emu.wait_until(emu.wants_key, 600, "the call intro to wait for A", step=1)
    once(emu, "f_intro")
    rec = choose(emu, t, kind, maxtry, "field")
    pages = hns.text_pages(emu, prefix, 40)
    emu.wait_quiet(600)
    shot(emu, prefix + "_last")
    rec.update(prefix=prefix, pages=pages)
    log_rec(emu, rec)
    emu.wait_controllable(900, "B")
    print("mcfield %s %s: %d page(s) @%d" % (t["name"], kind, pages, emu.sync()))


def mc_substruct(emu):
    res = emu.r32(emu.sym("gPokenavResources"))
    cbs = set()
    for c in MC_CALLBACKS:
        try:
            cbs.add(emu.sym(c))
        except HnsError:
            pass
    raw = emu.read(res, 0x80)
    for off in range(0, 0x80, 4):
        p = int.from_bytes(raw[off:off + 4], "little")
        if 0x02000000 <= p < 0x02040000 and emu.r32(p + 0x18) in cbs:
            return p
    raise HnsError("no match call substruct (callback at +0x18) in gPokenavResources")


def list_entries(emu):
    p = mc_substruct(emu)
    n = emu.r16(p + 0xA)
    raw = emu.read(p + 0x1C, 4 * n)
    return [(raw[4 * i], raw[4 * i + 1], int.from_bytes(raw[4 * i + 2:4 * i + 4], "little")) for i in range(n)]


def waitnav(emu):
    emu.wait_until(lambda: hns.pokenav_idle(emu), 900, "the Pokegear to read input", step=2)
    emu.wait_quiet(600)


@script_op("mclistopen")
def _op_mclistopen(emu, f, path):
    if emu.controllable():
        # gMenuCallback can still hold HandleStartMenuInput from an earlier menu. Clearing it
        # changes nothing: open_start_menu also reads the menu task, and the game sets the
        # pointer before it calls it
        emu.w32(emu.sym("gMenuCallback"), 0)
        emu.open_start_menu()
    emu.start_menu_cursor("POKEGEAR")
    if not emu.wait_cb2("CB2_Pokenav", 600):
        raise TourTimeout("mclistopen: the Pokegear did not open")
    waitnav(emu)
    emu.tap("DOWN", 0)
    waitnav(emu)
    emu.tap("DOWN", 0)
    waitnav(emu)
    emu.tap("A", 0)
    waitnav(emu)
    emu._row = 0
    ents = list_entries(emu)
    print("mclistopen: %d entries, %d special @%d" % (len(ents), sum(1 for e in ents if e[0]), emu.sync()))


def goto_row(emu, row):
    cur = getattr(emu, "_row", 0)
    while cur != row:
        emu.tap("DOWN" if row > cur else "UP", 0)
        waitnav(emu)
        cur += 1 if row > cur else -1
    emu._row = cur


def trainer_row(emu, t):
    for i, (special, _, hid) in enumerate(list_entries(emu)):
        if not special and hid == t["idx"]:
            return i
    raise HnsError("%s is not in the CALL list" % t["name"])


@script_op("mclistrow")
def _op_mclistrow(emu, f, path):
    d = data(emu)
    row = int(f[1]) if f[1].isdigit() else trainer_row(emu, d.trainer(f[1]))
    goto_row(emu, row)
    print("mclistrow %s -> %d @%d" % (f[1], row, emu.sync()))


def press_call(emu, prefix=None):
    """A on the selected row (CALL / CANCEL box), A on CALL."""
    emu.tap("A", 0)
    waitnav(emu)
    if prefix:
        shot(emu, prefix)
    emu.tap("A", 0)


@script_op("mclist")
def _op_mclist(emu, f, path):
    d = data(emu)
    t, kind, prefix = d.trainer(f[1]), f[2], f[3]
    maxtry = _arg(f, 4, 40)
    goto_row(emu, trainer_row(emu, t))
    prep(emu, t, kind)
    s4 = emu.sym("gStringVar4")
    emu.w32(s4, MARKER)
    opts = getattr(emu, "_opts_shot", set())
    press_call(emu, None if t["name"] in opts else prefix + "_opts")
    opts.add(t["name"])
    emu._opts_shot = opts
    emu.wait_until(emu.wants_key, 1200, "the calling dots to wait for A", step=1)
    once(emu, "l_dots")
    rec = choose(emu, t, kind, maxtry, "list")
    pages = hns.text_pages(emu, prefix, 40)
    emu.wait_quiet(600)
    shot(emu, prefix + "_last")
    rec.update(prefix=prefix, pages=pages)
    log_rec(emu, rec)
    emu.tap("A", 0)
    waitnav(emu)
    print("mclist %s %s: %d page(s) @%d" % (t["name"], kind, pages, emu.sync()))


RATING_PREFIXES = ("gJohtoDexRatingText_", "gNationalDexRatingText_", "gBirchDexRatingText_",
                   "gElmDexRatingText_")


def rating_labels(emu):
    """The rating texts gStringVar4 holds after an Elm call, in buffer order."""
    d = data(emu)
    s4 = ram_cstr(emu, emu.sym("gStringVar4"))
    subs = {0x01: ram_cstr(emu, emu.sb2(), 8), 0x05: b"",     # {KUN} expands to nothing
            0x02: ram_cstr(emu, emu.sym("gStringVar1"), 32), 0x03: ram_cstr(emu, emu.sym("gStringVar2"), 32)}
    found = []
    for name in emu.elf.byname:
        if name.startswith(RATING_PREFIXES):
            exp = expand(d.cstr(emu.sym(name)), subs)
            pos = s4.find(exp) if exp else -1
            if pos >= 0:
                found.append((pos, name))
    # a label that is a substring of a longer one found at the same place is dropped
    found.sort()
    return [n for _, n in found], s4


@script_op("mcelm")
def _op_mcelm(emu, f, path):
    prefix = f[1]
    want = f[2:]
    goto_row(emu, 0)
    press_call(emu)
    pages = hns.text_pages(emu, prefix, 40)
    emu.wait_quiet(600)
    shot(emu, prefix + "_last")
    labs, s4 = rating_labels(emu)
    d = data(emu)
    rec = dict(where="list", trainer="Elm", prefix=prefix, pages=pages, labels=labs,
               sv1=d.decode(ram_cstr(emu, emu.sym("gStringVar1"), 8)),
               sv2=d.decode(ram_cstr(emu, emu.sym("gStringVar2"), 8)))
    log_rec(emu, rec)
    emu.tap("A", 0)
    waitnav(emu)
    print("mcelm %s: %d page(s), %s, STR_VAR_1 %s STR_VAR_2 %s @%d" % (prefix, pages, labs, rec["sv1"], rec["sv2"], emu.sync()))
    missing = [w for w in want if w not in labs]
    if missing:
        raise HnsError("mcelm %s: %s not shown (shown: %s)" % (prefix, missing, labs))


@script_op("mcrow")
def _op_mcrow(emu, f, path):
    """mcrow N PREFIX: call the contact on list row N (a special contact: Mom, Baoba, ...)."""
    row, prefix = int(f[1]), f[2]
    goto_row(emu, row)
    press_call(emu, prefix + "_opts")
    pages = hns.text_pages(emu, prefix, 40)
    emu.wait_quiet(600)
    shot(emu, prefix + "_last")
    log_rec(emu, dict(where="list", trainer="row%d" % row, prefix=prefix, pages=pages,
                      text=data(emu).decode(ram_cstr(emu, emu.sym("gStringVar4")))))
    emu.tap("A", 0)
    waitnav(emu)
    print("mcrow %d %s: %d page(s) @%d" % (row, prefix, pages, emu.sync()))


@script_op("mcflags")
def _op_mcflags(emu, f, path):
    print("mcflags " + " ".join("%s=%d" % (n, emu.get_flag(emu.const(n))) for n in f[1:]))


@script_op("mclistclose")
def _op_mclistclose(emu, f, path):
    """B out of the CALL list and the Pokegear until the player can walk."""
    for _ in range(6):
        if emu.controllable():
            break
        if emu.cb2() == emu.sym("CB2_Pokenav") and hns.pokenav_idle(emu):
            emu.tap("B", 0)
        emu.frames(30)
    emu.wait_controllable(1200)
    print("mclistclose @%d" % emu.sync())


@script_op("mcnearby")
def _op_mcnearby(emu, f, path):
    d = data(emu)
    t, prefix = d.trainer(f[1]), f[2]
    goto_row(emu, trainer_row(emu, t))
    emu.w8(rematch_addr(emu, t["idx"]), 0)
    press_call(emu, prefix + "_opts")
    pages = hns.text_pages(emu, prefix, 10)
    emu.wait_quiet(600)
    shot(emu, prefix + "_last")
    log_rec(emu, dict(where="list", trainer=t["name"], kind="nearby", prefix=prefix, pages=pages))
    emu.tap("A", 0)
    waitnav(emu)
    print("mcnearby %s: %d page(s) @%d" % (t["name"], pages, emu.sync()))


@script_op("dexset")
def _op_dexset(emu, f, path):
    which, seen, caught = f[1], int(f[2]), int(f[3])
    name = "sJohtoToNationalOrder" if which == "johto" else "sObtainableToNationalOrder"
    tab = emu.sym(name)
    n = emu.elf.size(name) // 4          # enum NationalDexOrder[]: 4-byte entries (no -fshort-enums)
    d = data(emu)
    raw = d.romread(tab, 4 * n)
    nat = [int.from_bytes(raw[4 * i:4 * i + 4], "little") for i in range(n)]
    sb1 = emu.sb1()
    sbits, cbits = bytearray(DEX_REGION), bytearray(DEX_REGION)
    for i, num in enumerate(nat[:seen]):
        if num:
            sbits[(num - 1) >> 3] |= 1 << ((num - 1) & 7)
            if i < caught:
                cbits[(num - 1) >> 3] |= 1 << ((num - 1) & 7)
    for base, bits in ((SB1_DEX_SEEN, sbits), (SB1_DEX_CAUGHT, cbits)):
        for i in range(DEX_REGION):
            emu.w8(sb1 + base + i, bits[i])
    print("dexset %s: %d seen, %d caught (of %d) @%d" % (which, seen, caught, n, emu.sync()))


@script_op("natdex")
def _op_natdex(emu, f, path):
    emu.set_flag(emu.const("FLAG_SYS_NATIONAL_DEX"), f[1] == "1")
    print("natdex %s @%d" % (f[1], emu.sync()))


@script_op("mcexpect")
def _op_mcexpect(emu, f, path):
    if getattr(emu, "_r3last", None) != f[1]:
        raise HnsError("mcexpect: last text %s, wanted %s" % (getattr(emu, "_r3last", None), f[1]))


# ---------------------------------------------------------------- tour generator

def gen(src):
    ts = trainer_table(src)
    groups = [ts[i:i + 10] for i in range(0, len(ts), 10)]
    head = ["start saves/r3_calls/base.sav",
            "include ../continue.txt",
            "warpto MAP_CHERRYGROVE_CITY_HNS 25 9     # a city: no trainer's own map section",
            "waitctl 600"]
    written = []
    for gi, g in enumerate(groups):
        tag = "abcd"[gi]
        out = ["# Generated by r3calls.py gen: field calls, trainers %s." % ", ".join(t["name"] for t in g)] + head
        for t in g:
            out += ["mcclear", "mcreg %s" % t["name"]]
            for k in kinds_of(t):
                out.append("mcfield %s %s f_%s_%s" % (t["name"], k, t["name"].lower(), k.lower().replace(":", "")))
        name = "r3c_field_%s.txt" % tag
        open(os.path.join(HERE, name), "w").write("\n".join(out) + "\n")
        written.append(name)
        out = ["# Generated by r3calls.py gen: PokeGear CALL list calls, trainers %s." % ", ".join(t["name"] for t in g)] + head
        out += ["mcclear", "mcreg all", "mclistopen", "snap l_list_top"]
        for t in g:
            for k in kinds_of(t):
                out.append("mclist %s %s l_%s_%s" % (t["name"], k, t["name"].lower(), k.lower().replace(":", "")))
        name = "r3c_list_%s.txt" % tag
        open(os.path.join(HERE, name), "w").write("\n".join(out) + "\n")
        written.append(name)
    # STR_VAR_3 from the last rematch party: only the general texts that hold {STR_VAR_3}
    txt = open(os.path.join(src, "data", "text", "match_call_hns.inc"), encoding="utf-8").read()
    for gi, g in enumerate(groups):
        tag = "abcd"[gi]
        out = ["# Generated by r3calls.py gen: field calls with STR_VAR_3 from the trainers' last rematch",
               "# party (mcbeat all), trainers %s." % ", ".join(t["name"] for t in g)] + head + ["mcbeat all"]
        for t in g:
            ks = []
            for k in kinds_of(t):
                lab = "MatchCall_HNS_%s_%s::" % (t["name"], k.split(":")[0])
                body = txt[txt.index(lab):].split("$", 1)[0]
                if "{STR_VAR_3}" in body:
                    ks.append(k)
            if not ks:
                continue
            out += ["mcclear", "mcreg %s" % t["name"]]
            out += ["mcfield %s %s x_%s_%s" % (t["name"], k, t["name"].lower(), k.lower()) for k in ks]
        name = "r3c_fieldx_%s.txt" % tag
        open(os.path.join(HERE, name), "w").write("\n".join(out) + "\n")
        written.append(name)
    print("wrote", written)


if __name__ == "__main__":
    if len(sys.argv) > 1 and sys.argv[1] == "gen":
        gen(sys.argv[2])
        sys.exit(0)
    sys.argv[0] = hns.__file__
    sys.exit(hns.main())
