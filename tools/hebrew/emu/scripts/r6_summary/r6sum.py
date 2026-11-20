#!/usr/bin/env python3
"""hns.py plus the ops of the summary / move relearner text sweep (tours/r6_summary/), and the
generator of those tours.

Ops (on top of sumvar.py's sumwait / sumkey / monprobe / monset and ladder.py's event ops):

    monmint SLOT NATURE       give gPlayerParty[SLOT] the hidden (mint) nature NATURE: the plain
                              byte BoxPokemon+18 keeps language:3 and hiddenNatureModifier:5, and
                              the hidden nature is personality%25 ^ modifier (src/pokemon.c:4927-4931)
    relpoke ID,ID,...         with the move relearner open (CB2_MoveRelearnerMain, idle), replace
                              its list by these moves + CANCEL: sMoveRelearnerStruct->menuItems
                              (+0x8C, 8 bytes each, 61 entries), numMenuChoices (+0x274),
                              numToShowAtOnce (+0x275), the list task's ListMenuTemplate bitfield
                              (task data +12: totalItems:12, maxShowed:12) and
                              gMultiuseListMenuTemplate. Rows already on screen keep their old names
                              until they scroll out and back in; the description windows follow
                              the cursor (MoveRelearnerCursorCallback, src/menu_specialized.c:860).
    relwalk PREFIX N          snap PREFIX_000, tap DOWN, ... N rows, then UP back to row 0 and
                              snap PREFIX_top (every row redrawn by then)

Generator:

    r6sum.py gen DATA_HE.json TOURDIR       write the tours (ids only; both ROMs share them)

Usage of the ops: r6sum.py tour ROM OUT --tours <TOURDIR> [--only RE] [--clip]
"""
import json
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(HERE, "..", ".."))                       # tools/hebrew/emu
sys.path.insert(0, os.path.join(HERE, "..", "r2_summary_info_page_variants"))
sys.path.insert(0, os.path.join(HERE, "..", "r1_npc_services"))
import hns  # noqa: E402
import ladder  # noqa: E402,F401  (ev, evstart, startmenu)
import sumvar  # noqa: E402,F401  (sumwait, sumkey, monprobe, monset)
from hns import script_op, HnsError, _arg  # noqa: E402

MON_SIZE = 0x64
REL_ITEMS, REL_NUM = 0x8C, 0x274
MOVE_STRIDE = 68


@script_op("monmint")
def _op_monmint(emu, f, path):
    slot, mint = int(f[1]), int(f[2], 0)
    addr = emu.sym("gPlayerParty") + MON_SIZE * slot
    pers = emu.r32(addr)
    b = emu.r8(addr + 18)
    mod = (pers % 25) ^ mint
    emu.w8(addr + 18, (b & 7) | (mod << 3))
    print("monmint slot%d nature %d -> hidden %d (byte18 %02X -> %02X)" % (slot, pers % 25, mint, b,
                                                                           emu.r8(addr + 18)))


def _bits(emu, addr, total, shown):
    w = emu.r32(addr)
    w = (w & ~0xFFFFFF) | (total & 0xFFF) | ((shown & 0xFFF) << 12)
    emu.w32(addr, w)


@script_op("relpoke")
def _op_relpoke(emu, f, path):
    ids = [int(x) for x in f[1].split(",") if x]
    if not 0 < len(ids) <= 60:
        raise HnsError("relpoke: 1..60 moves, got %d" % len(ids))
    st = emu.r32(emu.sym("move_relearner:sMoveRelearnerStruct"))
    if not st:
        raise HnsError("relpoke: the move relearner is not open")
    moves = emu.sym("gMovesInfo")
    # layout check: menuItems[0] holds the name pointer of movesToLearn[0] (+0x12, u16)
    first = emu.r16(st + 0x12)
    if emu.r32(st + REL_ITEMS) != emu.r32(moves + MOVE_STRIDE * first) or emu.r32(st + REL_ITEMS + 4) != first:
        raw = emu.read(st, 0x300)
        for o in range(0, 0x300, 32):
            print("%03X %s" % (o, raw[o:o + 32].hex()))
        print("first", first, "name ptr %08X" % emu.r32(moves + MOVE_STRIDE * first))
        raise HnsError("relpoke: sMoveRelearnerStruct layout does not match (menuItems at +0x%X)" % REL_ITEMS)
    n_old = emu.r8(st + REL_NUM)
    cancel = emu.r32(st + REL_ITEMS + 8 * (n_old - 1))
    for i, m in enumerate(ids):
        emu.w32(st + REL_ITEMS + 8 * i, emu.r32(moves + MOVE_STRIDE * m))
        emu.w32(st + REL_ITEMS + 8 * i + 4, m)
        emu.w16(st + 0x12 + 2 * i, m)
    n = len(ids) + 1
    emu.w32(st + REL_ITEMS + 8 * len(ids), cancel)
    emu.w32(st + REL_ITEMS + 8 * len(ids) + 4, 0xFFFFFFFE)
    emu.w8(st + REL_NUM, n)
    emu.w8(st + REL_NUM + 1, min(6, n))
    task = emu.r8(st + REL_NUM + 2)
    tdata = emu.sym("gTasks") + 40 * task + 8
    if emu.r32(tdata) != st + REL_ITEMS:
        raise HnsError("relpoke: list task %d does not point at menuItems" % task)
    _bits(emu, tdata + 12, n, min(6, n))
    _bits(emu, emu.sym("gMultiuseListMenuTemplate") + 12, n, min(6, n))
    print("relpoke %d moves (was %d rows), list task %d @%d" % (len(ids), n_old, task, emu.sync()))


@script_op("relname")
def _op_relname(emu, f, path):
    """relname ROW SYMBOL[+OFF]: point relearner list row ROW's name at another string (a clip
    self-test: a string wider than the 72-px list must show up in the clip report)."""
    st = emu.r32(emu.sym("move_relearner:sMoveRelearnerStruct"))
    sym, _, off = f[2].partition("+")
    addr = emu.sym(sym) + (int(off, 0) if off else 0)
    emu.w32(st + REL_ITEMS + 8 * int(f[1]), addr)
    print("relname row %s -> %s (%08X)" % (f[1], f[2], addr))


@script_op("relwalk")
def _op_relwalk(emu, f, path):
    prefix, n = f[1], int(f[2])
    for i in range(n):
        if i:
            emu.tap("DOWN", 4)
            emu.wait_quiet(300)
        emu.frames(2)
        emu.snap("%s_%03d" % (prefix, i))
    for i in range(n - 1):
        emu.tap("UP", 4)
        emu.wait_quiet(300)
    emu.frames(2)
    emu.snap("%s_top" % prefix)
    print("relwalk %s %d rows @%d" % (prefix, n, emu.sync()))


# ---------------------------------------------------------------------------- generator

FULL_PER_TOUR, ITEM_PER_TOUR = 5, 10
# Z-moves and Max moves start at MOVES_COUNT (include/constants/moves.h:910-914); createmon refuses
# them (assertf "invalid move", src/script_pokemon_util.c) and no summary or relearner lists them.
MOVES_COUNT = 848
# callnative ..., requests_effects=1 stores func + ROM_SIZE (asm/macros/event.inc:268-275), a ROM
# mirror address the game calls as is. hnsrun reports a PC there as CRASH when a frame ends inside
# the native (ScrCmd_createmon), so these RAM scripts store the plain address.
EV = "ev .set ROM_SIZE, 0; "


def _sum_open():
    return "include ../../scripts/r2_summary_info_page_variants/_sum_open.txt"


def _sum_close():
    return "include ../../scripts/r2_summary_info_page_variants/_sum_close.txt"


def _header(what):
    return ["# %s" % what,
            "# Generated by scripts/r6_summary/r6sum.py gen; run with r6sum.py tour ROM OUT --tours <here>",
            "start saves/ladder6_postgame.sav",
            "include ../../scripts/continue.txt", ""]


def _createmon(slot, sp, item, nature, abil, moves):
    s = "createmon 0, %d, %d, 100, item=%d, nature=%d, abilityNum=%d" % (slot, sp, item, nature, abil)
    for k, m in enumerate(moves):
        s += ", move%d=%d" % (k + 1, m)
    return s


def _moverows(tag, contest):
    win = "Task_SlideAppealJamWindow" if contest else "Task_SlidePowerAccWindow"
    out = ["tap A 4", "waittaskx Task_HandleInput_MoveSelect 300", "waitnotask %s 120" % win, "waitquiet",
           "snap %s_1" % tag]
    for r in (2, 3, 4):
        out += ["tap DOWN 4", "waitquiet", "snap %s_%d" % (tag, r)]
    out += ["tap B 4", "sumwait"]
    return out


def gen(data_path, tourdir):
    d = json.load(open(data_path))
    assert d["moves"][MOVES_COUNT - 1]["name"] and len(d["moves"]) > MOVES_COUNT
    moves = [m for m in d["moves"][1:MOVES_COUNT]]
    # one move per used contest effect first, so the first loads show every contest description
    rep, seen = [], set()
    for m in moves:
        if m["contestEffect"] not in seen:
            seen.add(m["contestEffect"])
            rep.append(m["id"])
    order = rep + [m["id"] for m in moves if m["id"] not in rep]
    abil = [(a["species_abilityNum"][0], a["species_abilityNum"][1], a["id"])
            for a in d["abilities"] if a["id"] and a["species_abilityNum"]]
    items = [i["id"] for i in d["items"] if i["name"] and not i["name"].startswith("????")]
    loads = []
    ai = ii = mi = 0
    li = 0
    while ai < len(abil) or mi < len(order):
        slots = []
        for s in range(6):
            sp, an, aid = abil[ai % len(abil)]
            ai += 1
            mv = order[mi:mi + 4]
            mi += len(mv)
            if not mv:
                mv = [1]
            it = items[ii % len(items)]
            ii += 1
            slots.append(dict(sp=sp, an=an, aid=aid, item=it, nature=(li * 6 + s) % 25, moves=mv))
        loads.append(slots)
        li += 1
    index = {"full": [], "items": [], "relearner": []}
    os.makedirs(tourdir, exist_ok=True)
    # -- full loads: INFO, SKILLS, BATTLE MOVES (A + 4 rows), CONTEST MOVES (page; A + 4 rows in loads 1-2)
    for t0 in range(0, len(loads), FULL_PER_TOUR):
        tname = "r6sum_full_%02d" % (t0 // FULL_PER_TOUR + 1)
        L = _header("Summary INFO / SKILLS / BATTLE MOVES / CONTEST MOVES, loads %d-%d of %d" % (
            t0 + 1, min(t0 + FULL_PER_TOUR, len(loads)), len(loads)))
        for li in range(t0, min(t0 + FULL_PER_TOUR, len(loads))):
            slots = loads[li]
            L.append("# ---- load %d" % (li + 1))
            L.append(EV + "; ".join(_createmon(s, x["sp"], x["item"], x["nature"], x["an"], x["moves"])
                                       for s, x in enumerate(slots)) + "; special CalculatePlayerPartyCount; end")
            L.append(_sum_open())
            contest_rows = li < 2
            for s, x in enumerate(slots):
                tag = "L%03d_s%d" % (li + 1, s)
                index["full"].append(dict(tour=tname, tag=tag, **x))
                fwd = s % 2 == 0
                pages = ["info", "skills", "battle", "contest"] if fwd else ["contest", "battle", "skills", "info"]
                for pi, pg in enumerate(pages):
                    if pi:
                        L.append("sumkey %s" % ("RIGHT" if fwd else "LEFT"))
                    if pg in ("info", "skills"):
                        L.append("snap %s_%s" % (tag, pg))
                    elif pg == "battle":
                        L += _moverows(tag + "_bm", False)
                    else:
                        L.append("snap %s_contest" % tag)
                        if contest_rows:
                            L += _moverows(tag + "_cm", True)
                if s < 5:
                    L.append("sumkey DOWN")
            L.append(_sum_close())
            if li == 0:
                L += ["savegame", "keepsave r6_sum_party"]
        open(os.path.join(tourdir, tname + ".txt"), "w").write("\n".join(L) + "\n")
    # -- item-only loads: SKILLS held item (the first 25 slots also carry a mint nature; INFO memo)
    used = len(loads) * 6
    rest = items[used:] if used < len(items) else []
    iloads = [rest[i:i + 6] for i in range(0, len(rest), 6)]
    sp_cycle = [a[0] for a in abil]
    k = 0
    for t0 in range(0, len(iloads), ITEM_PER_TOUR):
        tname = "r6sum_items_%02d" % (t0 // ITEM_PER_TOUR + 1)
        L = _header("Summary SKILLS held-item row, item loads %d-%d of %d" % (
            t0 + 1, min(t0 + ITEM_PER_TOUR, len(iloads)), len(iloads)))
        for li in range(t0, min(t0 + ITEM_PER_TOUR, len(iloads))):
            its = iloads[li]
            mons = []
            for s, it in enumerate(its):
                nat = (li * 6 + s) % 25
                mons.append(_createmon(s, sp_cycle[k % len(sp_cycle)], it, nat, 0, [1]))
                k += 1
            L.append("# ---- item load %d" % (li + 1))
            L.append(EV + "; ".join(mons) + "; special CalculatePlayerPartyCount; end")
            mint = li < 5
            if mint:
                for s in range(len(its)):
                    nat = (li * 6 + s) % 25
                    L.append("monmint %d %d" % (s, (nat + 12) % 25))
            L.append(_sum_open())
            if not mint:
                L.append("sumkey RIGHT")
            for s, it in enumerate(its):
                tag = "I%03d_s%d" % (li + 1, s)
                index["items"].append(dict(tour=tname, tag=tag, item=it, nature=(li * 6 + s) % 25,
                                           mint=((li * 6 + s) % 25 + 12) % 25 if mint else None))
                if mint:
                    L += ["snap %s_info" % tag, "sumkey RIGHT", "snap %s_skills" % tag, "sumkey LEFT"]
                else:
                    L.append("snap %s_skills" % tag)
                if s < len(its) - 1:
                    L.append("sumkey DOWN")
            # party may have fewer than 6 when the list ends: slots beyond are the old party
            L.append(_sum_close())
        open(os.path.join(tourdir, tname + ".txt"), "w").write("\n".join(L) + "\n")
    # -- relearner: battle mode, every move; contest mode, one move per used contest effect
    ids = [m["id"] for m in moves]
    chunks = [ids[i:i + 60] for i in range(0, len(ids), 60)]
    rel_open = [EV + "createmon 0, 0, SPECIES_MEW, 100; special CalculatePlayerPartyCount; end",
                "evstart setvar VAR_0x8004, 0; special TeachMoveRelearnerMove; waitstate; release; end",
                "waitcb2x CB2_MoveRelearnerMain 900",
                "waitpmem 8 move_relearner:sMoveRelearnerStruct 0 4 900",
                "waitquiet"]
    rel_close = ["press B", "waitpmem 8 move_relearner:sMoveRelearnerStruct 0 13 300", "press A",
                 "waitcb2x CB2_Overworld 900", "waitctl 900 B"]
    per = 4
    for t0 in range(0, len(chunks), per):
        tname = "r6sum_rel_%02d" % (t0 // per + 1)
        L = _header("Move relearner, battle mode, every move: list, description, type, PP, power, accuracy")
        for ci in range(t0, min(t0 + per, len(chunks))):
            ch = chunks[ci]
            L += ["# ---- relearner session %d: moves %d-%d" % (ci + 1, ch[0], ch[-1])] + rel_open
            L += ["snap R%02d_orig" % (ci + 1), "relpoke " + ",".join(map(str, ch)),
                  "relwalk R%02d %d" % (ci + 1, len(ch))] + rel_close
            index["relearner"].append(dict(tour=tname, prefix="R%02d" % (ci + 1), moves=ch, mode="battle"))
        open(os.path.join(tourdir, tname + ".txt"), "w").write("\n".join(L) + "\n")
    L = _header("Move relearner, contest mode: one move per used contest effect (description, hearts)")
    L += rel_open + ["relpoke " + ",".join(map(str, rep)), "press RIGHT",
                     "waitpmem 8 move_relearner:sMoveRelearnerStruct 0 6 300", "waitquiet",
                     "relwalk RC %d" % len(rep), "press LEFT",
                     "waitpmem 8 move_relearner:sMoveRelearnerStruct 0 4 300"] + rel_close
    index["relearner"].append(dict(tour="r6sum_relc", prefix="RC", moves=rep, mode="contest"))
    open(os.path.join(tourdir, "r6sum_relc.txt"), "w").write("\n".join(L) + "\n")
    json.dump(index, open(os.path.join(tourdir, "index.json"), "w"), indent=0)
    print("full loads %d, item loads %d, relearner sessions %d (+1 contest) -> %s" % (
        len(loads), len(iloads), len(chunks), tourdir))


if __name__ == "__main__":
    if len(sys.argv) > 1 and sys.argv[1] == "gen":
        gen(sys.argv[2], sys.argv[3])
        sys.exit(0)
    sys.argv[0] = hns.__file__
    sys.exit(hns.main())
