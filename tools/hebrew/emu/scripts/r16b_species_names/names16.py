#!/usr/bin/env python3
"""Species and ability names of the Pokemon outside the Heart & Soul Pokedex: hns.py plus the ops
and the tour generator of tours/r16b_species_names/.

Run (from a work dir outside the worktree; HNS_MAX_FRAMES limits each runner process):

    names16.py tour ROM OUT --tours <E>/tours/r16b_species_names [--only RE] [--clip]

with HNS_SRC = the tree the ROM was built from (constants for the event scripts) and HNS_SAVES
holding ladder6_postgame.sav. The tours only write RAM: party Pokemon through `createmon`, the
storage panel through the real DEPOSIT screen, wild battles through `setwildbattle`/`dowildbattle`.

Ops (on top of hns.py, ladder.py, sumvar.py's sumwait/sumkey and pcs.py's pcwait/pcgoto):

    rzabil on|off       the New Game challenge option RANDOM ABILITIES
                        (gSaveBlock3Ptr->challengeSettings.tx_Random_Abilities, bit 7 of byte 4 of the
                        bitfield, include/global.h ChallengeSettings) set or cleared in RAM
    rzopt NAME on|off   another randomizer option bit (RZ_BITS: wild, legendaries, abilities, static,
                        starter, genscope13; genscope13 off = GEN SCOPE all gens)
    rzseed              print the randomizer seed (GetTrainerId(playerTrainerId), RANDOMIZER_SEED_IS_TRAINER_ID)

Generator:

    names16.py gen TARGETS.json TOURDIR       write the tours from the target list
    names16.py rzsearch SEED [ABILITY_X ...]  species whose slot-0 ability RandomizeAbility turns into
                                              ABILITY_X under SEED (src/randomizer.c RandomizeAbility,
                                              RandomizerRandSeed, include/random.h _SFC32_Next_Stream)

TARGETS.json (tours/r16b_species_names/species_targets.json):
    {"species": [{"id", "const", "he", "en", ...}], "wide": [CONST, ...],
     "abil_loads": [{"rz": bool, "slots": [[CONST, ABILITY_X], ...], "battles": [[LEAD, WILD], ...]}]}

Tours:
    sn_LNNN      6 species (createmon, level 100): party menu, summary INFO of every slot, one wild
                 battle (the second widest name as the wild Pokemon, the widest as slot 0 so it is
                 in the player's healthbox and the send-out line), RUN
    sn_wideN     the widest names (and the other audit.py FIT names): party, the PC DEPOSIT panel of
                 every slot, and one wild battle per name with that name on both sides (male where the
                 species can be male: the gender symbol counts in the healthbox's 55 px)
    sn_abil_N    summary INFO ability window: RANDOM ABILITIES on, species whose slot-0 roll is the
                 target ability (rzsearch with the ladder6_postgame seed 0xDE9B5CDD), then real
                 battles whose send-out shows the weather / As One / Embody Aspect pop-ups. The
                 Calyrex riders and the Ogerpon Tera forms are compiled out (P_FUSION_FORMS,
                 P_TERA_FORMS FALSE), so these abilities show only through RANDOM ABILITIES.
    sn_reach     (written by hand) RANDOM STATIC POKEMON on and GEN SCOPE all gens, twelve scripted
                 wild battles with the RNG free: which species the real randomizer rolls

`gen` rewrites the generated tours and index.json; it does not delete tours it no longer writes.
"""
import json
import os
import re
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
EMU = os.path.dirname(os.path.dirname(HERE))
sys.path.insert(0, EMU)
sys.path.insert(0, os.path.join(EMU, "scripts", "r2_summary_info_page_variants"))
sys.path.insert(0, os.path.join(EMU, "scripts", "r2_pc_storage"))
import hns  # noqa: E402
import ladder  # noqa: E402,F401  (ev, evstart, startmenu)
import sumvar  # noqa: E402,F401  (sumwait, sumkey)
import pcs  # noqa: E402,F401  (pcwait, pcgoto)
from hns import script_op  # noqa: E402

SB3_CHALLENGE = 0x10            # offsetof(struct SaveBlock3, challengeSettings) (hns.py BATTLE_OFF)
RZ_ABIL_BYTE, RZ_ABIL_BIT = 4, 7
SB2_TRAINER_ID = 0x0A           # struct SaveBlock2 playerTrainerId (include/global.h)
REASON_ABILITIES = 9            # enum RandomizerReason (include/randomizer.h)
RANDOMIZER_STREAM = 17
M32 = 0xFFFFFFFF


@script_op("rzabil")
def _op_rzabil(emu, f, path):
    addr = emu.r32(emu.sym("gSaveBlock3Ptr")) + SB3_CHALLENGE + RZ_ABIL_BYTE
    v = emu.r8(addr)
    on = f[1].lower() == "on"
    emu.w8(addr, (v | (1 << RZ_ABIL_BIT)) if on else (v & ~(1 << RZ_ABIL_BIT)))
    print("rzabil %s: byte %02X -> %02X" % (f[1], v, emu.r8(addr)))


# (byte, bit) of the randomizer bitfield in ChallengeSettings (include/global.h; byte 4 starts at
# tx_Random_Chaos, after the 3 option bytes and autoRun)
RZ_BITS = {"wild": (4, 1), "legendaries": (4, 4), "abilities": (4, 7), "static": (5, 5), "starter": (5, 6),
           "genscope13": (5, 7)}


@script_op("rzopt")
def _op_rzopt(emu, f, path):
    """rzopt NAME on|off: set a New Game randomizer option in RAM (RZ_BITS; genscope13 off = all gens)."""
    byte, bit = RZ_BITS[f[1]]
    addr = emu.r32(emu.sym("gSaveBlock3Ptr")) + SB3_CHALLENGE + byte
    v = emu.r8(addr)
    emu.w8(addr, (v | (1 << bit)) if f[2].lower() == "on" else (v & ~(1 << bit)))
    print("rzopt %s %s: byte %d %02X -> %02X" % (f[1], f[2], byte, v, emu.r8(addr)))


@script_op("rzseed")
def _op_rzseed(emu, f, path):
    sb2 = emu.r32(emu.sym("gSaveBlock2Ptr"))
    # playerTrainerId is not word-aligned (+0x0A): read it byte by byte (GetTrainerId, src/new_game.c)
    tid = sum(emu.r8(sb2 + SB2_TRAINER_ID + i) << (8 * i) for i in range(4))
    print("rzseed %08X" % tid)


# ---------------------------------------------------------------------------- randomizer model

def _sfc32(st):
    a, b, c, ctr = st
    res = (a + b + ctr) & M32
    ctr = (ctr + RANDOMIZER_STREAM) & M32
    a = b ^ (b >> 9)
    b = (c * 9) & M32
    c = (res + (((c << 21) | (c >> 11)) & M32)) & M32
    return res, (a, b, c, ctr)


def _next_range(st, rng):
    p = rng - 1
    for s in (1, 2, 4, 8, 16):
        p |= p >> s
    mask = p
    while True:
        r, st = _sfc32(st)
        r &= mask
        if r < rng:
            return r, st


def roll_ability(seed, species, whitelist, illegal, ability_num=0):
    st = ((seed + REASON_ABILITIES) & M32, seed ^ species, ((species << 8) | ability_num) & M32, RANDOMIZER_STREAM)
    for _ in range(10):
        _, st = _sfc32(st)
    while True:
        i, st = _next_range(st, len(whitelist))
        if whitelist[i] not in illegal:
            return whitelist[i]


def _src():
    return os.environ.get("HNS_SRC") or os.path.join(EMU, "..", "..", "..")


def load_rz_tables(src):
    body = open(os.path.join(src, "include/constants/abilities.h"), encoding="utf-8").read()
    body = body[body.index("enum"):]
    body = body[body.index("{") + 1:body.index("};")]
    num, cur = {}, -1
    for item in re.sub(r"//[^\n]*", "", body).split(","):
        item = item.strip()
        if not item:
            continue
        name, _, val = item.partition("=")
        name, val = name.strip(), val.strip()
        cur = (int(val, 0) if val[:1].isdigit() else num[val]) if val else cur + 1
        num[name] = cur
    wl = open(os.path.join(src, "src/data/randomizer/ability_whitelist.h"), encoding="utf-8").read()
    wl = wl[wl.index("sRandomizerAbilityWhitelist[]"):]
    wl = wl[wl.index("{") + 1:wl.index("};")]
    whitelist = [num[n] for n in re.findall(r"\b(ABILITY_\w+)\b", wl)]
    illegal = {num["ABILITY_NONE"], num["ABILITY_WONDER_GUARD"]}
    sp = {}
    for line in open(os.path.join(src, "include/constants/species.h"), encoding="utf-8"):
        m = re.match(r"#define (SPECIES_\w+)\s+(\d+)\b", line)
        if m:
            sp[m.group(1)] = int(m.group(2))
    return num, whitelist, illegal, sp


def rzsearch(seed, wanted, src=None, lo=1, hi=1025):
    num, whitelist, illegal, sp = load_rz_tables(src or _src())
    inv = {}
    for k, v in sp.items():
        inv.setdefault(v, k)
    out = {}
    for name in wanted:
        target = num[name]
        out[name] = [inv[s] for s in range(lo, hi + 1) if s in inv
                     and roll_ability(seed, s, whitelist, illegal) == target]
    return out


# ---------------------------------------------------------------------------- generator

EV = "ev .set ROM_SIZE, 0; "
EVS = "evstart .set ROM_SIZE, 0; "
PER_LOAD = 6
WILD_LEVEL = 5


def _header(what):
    return ["# %s" % what,
            "# Generated by scripts/r16b_species_names/names16.py gen; run with names16.py tour ROM OUT --tours <here>",
            "start saves/ladder6_postgame.sav",
            "include ../../scripts/continue.txt",
            "fastbattles off",
            "pinrng                     # same personalities, genders and natures on every ROM", ""]


def _party(consts, gender=None):
    """gender: None or {CONST: MON_MALE|None} (createmon loops forever on a gender the species
    cannot have, so genderless species get none)."""
    def g(c):
        return ", gender=%s" % gender[c] if gender and gender.get(c) else ""
    return EV + "; ".join("createmon 0, %d, %s, 100%s" % (s, c, g(c)) for s, c in enumerate(consts)) + \
        "; special CalculatePlayerPartyCount; end"


def _party_and_summary(tag, n):
    L = ["include _sn_party_open.txt", "snap %s_party" % tag,
         "include _sn_party_to_summary.txt"]
    for s in range(n):
        L.append("snap %s_s%d_info" % (tag, s))
        if s < n - 1:
            L.append("sumkey DOWN")
    L.append("include ../../scripts/r2_summary_info_page_variants/_sum_close.txt")
    return L


def _wild(tag, wild, gender=None, extra=""):
    g = (", gender=%s" % gender if gender else "") + extra
    return [EVS + "setwildbattle %s, %d; createmon 1, 0, %s, %d%s; dowildbattle; end" % (wild, WILD_LEVEL, wild, WILD_LEVEL, g),
            "waitbattle",
            "bwalk %s_bt input:HandleInputChooseAction" % tag,
            "snap %s_bt_action" % tag,
            "baction RUN",
            "bwalk %s_run free" % tag]


def _pc(tag, n):
    return ["include _sn_pc_deposit.txt",
            "snap %s_pc_s0" % tag] + sum((["pcgoto party %d" % s, "waitquiet", "snap %s_pc_s%d" % (tag, s)]
                                          for s in range(1, n)), []) + ["include _sn_pc_close.txt"]


def gen(targets_path, tourdir):
    d = json.load(open(targets_path, encoding="utf-8"))
    os.makedirs(tourdir, exist_ok=True)
    index = {"loads": [], "wide": [], "abilities": []}
    sp = d["species"]
    # loads of 6 in source order; slot 0 = the widest FONT_SMALL name of the load (player healthbox,
    # send-out line), the wild Pokemon = the second widest
    for li in range(0, len(sp), PER_LOAD):
        load = sp[li:li + PER_LOAD]
        order = sorted(range(len(load)), key=lambda i: -load[i]["w"]["FONT_SMALL"])
        slots = [load[order[0]]] + [x for i, x in enumerate(load) if i != order[0]]
        wild = load[order[1]] if len(load) > 1 else load[order[0]]
        tag = "L%03d" % (li // PER_LOAD + 1)
        tname = "sn_%s" % tag
        L = _header("Species names, load %s: %s" % (tag, " ".join(x["const"] for x in slots)))
        L.append(_party([x["const"] for x in slots]))
        L += _party_and_summary(tag, len(slots))
        L += _wild(tag, wild["const"])
        open(os.path.join(tourdir, tname + ".txt"), "w").write("\n".join(L) + "\n")
        index["loads"].append(dict(tour=tname, tag=tag, slots=[x["const"] for x in slots],
                                   ids=[x["id"] for x in slots], wild=wild["const"], lead=slots[0]["const"]))
    # the widest names: party, PC panel, both healthboxes per name
    wide = d["wide"]
    for wi in range(0, len(wide), PER_LOAD):
        load = wide[wi:wi + PER_LOAD]
        tag = "W%d" % (wi // PER_LOAD + 1)
        tname = "sn_wide%d" % (wi // PER_LOAD + 1)
        L = _header("Widest species names %s: %s" % (tag, " ".join(load)))
        gmap = d.get("wide_gender", {})
        L.append(_party(load, gmap))
        L += _party_and_summary(tag, len(load))
        L += _pc(tag, len(load))
        for k, c in enumerate(load):
            t = "%s_%d_%s" % (tag, k, c[len("SPECIES_"):])
            g = ", gender=%s" % gmap[c] if gmap.get(c) else ""
            L.append(EV + "createmon 0, 0, %s, 100%s; end" % (c, g))
            L += _wild(t, c, gmap.get(c))
        open(os.path.join(tourdir, tname + ".txt"), "w").write("\n".join(L) + "\n")
        index["wide"].append(dict(tour=tname, tag=tag, slots=load))
    # abilities on the summary INFO page, then real battles whose send-out shows a pop-up
    for n, ld in enumerate(d["abil_loads"], 1):
        tag = "A%d" % n
        tname = "sn_abil_%d" % n
        rz = ld["rz"]
        slots = ld["slots"]
        L = _header("Ability window %s (RANDOM ABILITIES %s): %s" % (
            tag, "on" if rz else "off", " ".join("%s=%s" % (c, a) for c, a in slots)))
        L.append("rzseed")
        L.append("rzabil %s" % ("on" if rz else "off"))
        L.append(EV + "; ".join("createmon 0, %d, %s, 100, abilityNum=0" % (s, c)
                                for s, (c, a) in enumerate(slots)) + "; special CalculatePlayerPartyCount; end")
        L += _party_and_summary(tag, len(slots))
        for k, (lead, wild) in enumerate(ld.get("battles", [])):
            t = "%s_b%d" % (tag, k + 1)
            L.append(EV + "createmon 0, 0, %s, 100, abilityNum=0; end" % lead)
            L += _wild(t, wild, extra=", abilityNum=0")
        if rz:
            L.append("rzabil off")
        open(os.path.join(tourdir, tname + ".txt"), "w").write("\n".join(L) + "\n")
        index["abilities"].append(dict(tour=tname, tag=tag, rz=rz, slots=slots, battles=ld.get("battles", [])))
    n = len(d["abil_loads"])
    json.dump(index, open(os.path.join(tourdir, "index.json"), "w"), indent=1)
    print("loads %d, wide %d, ability tours %d -> %s" % (len(index["loads"]), len(index["wide"]), n, tourdir))


if __name__ == "__main__":
    if len(sys.argv) > 1 and sys.argv[1] == "gen":
        gen(sys.argv[2], sys.argv[3])
        sys.exit(0)
    if len(sys.argv) > 1 and sys.argv[1] == "rzsearch":
        res = rzsearch(int(sys.argv[2], 0), sys.argv[3:])
        for k, v in res.items():
            print(k, " ".join(v))
        sys.exit(0)
    sys.argv[0] = hns.__file__
    sys.exit(hns.main())
