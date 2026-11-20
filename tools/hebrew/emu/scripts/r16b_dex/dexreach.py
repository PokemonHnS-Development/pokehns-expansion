#!/usr/bin/env python3
"""Reach check for the out-of-dex Pokedex text: a real New Game with the randomizer on (GEN SCOPE
Gen 1-9) rolls species outside the 482-entry obtainable list, and catching one shows its Pokedex
page (tours/r16b_dex/dx_reach_*.txt).

hns.py plus the r10 post-game ops (scripts/r10_postgame/r10pg.py, which brings the r5/r6 ops:
bcatch, bwalk helpers) and sumvar.py (monprobe). Added here:

    wildfind PREFIX [TRIES] [MAXSTEPS]
        walk to the nearest wild-encounter tile of the current map and pace on it until a wild
        battle starts (the r10 'wild' walk), walk the intro to the action menu (PREFIX_tN_..),
        read the foe's species (gBattleMons[1].species, +0) and look its national number up in
        sObtainableToNationalOrder (src/pokemon.c:944). An out-of-dex species ends the op at the
        action menu (the tour goes on, e.g. with bcatch); an obtainable one is fled from (RUN)
        and the next encounter is tried, up to TRIES (default 8).
    obtainable SLOT...
        print the species of party SLOTs and whether each is in the obtainable list.

Run: dexreach.py tour ROM OUT --tours tools/hebrew/emu/tours/r16b_dex --only '^dx_reach' [--clip]
from a work dir, with HNS_SRC = the ROM's tree, HNS_RUNNER, HNS_SAVES and HNS_MAX_FRAMES.
"""
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
EMU = os.path.dirname(os.path.dirname(HERE))
sys.path.insert(0, EMU)
sys.path.insert(0, os.path.join(EMU, "scripts", "r10_postgame"))
sys.path.insert(0, os.path.join(EMU, "scripts", "r2_summary_info_page_variants"))
sys.path.insert(0, HERE)
import hns  # noqa: E402
import r10pg  # noqa: E402  (wild walk helpers; registers the r5/r6/r10 ops)
import sumvar  # noqa: E402  (monprobe, mon_fields)
import dexinfo  # noqa: E402  (natdex_name, resolve_all)
import dexsweep  # noqa: E402  (load_names)
from hns import script_op, HnsError, _arg  # noqa: E402

OBTAINABLE_DEX_COUNT = 482


def _obtainable(emu):
    if not hasattr(emu, "_dx_obtainable"):
        raw = emu.read(emu.sym("sObtainableToNationalOrder"), 2 * OBTAINABLE_DEX_COUNT)
        emu._dx_obtainable = {raw[2 * i] | raw[2 * i + 1] << 8 for i in range(OBTAINABLE_DEX_COUNT)}
    return emu._dx_obtainable


def _judge(emu, species):
    """(SPECIES_NAME, national number, in the obtainable list)."""
    src = hns.src_dir(emu.elf)
    nat, sp = dexsweep.load_names(src)
    name = "SPECIES_" + sp.get(species, "UNKNOWN_%d" % species)
    nn = dexinfo.natdex_name(name, nat)
    num = dexinfo.resolve_all(src, [nn])[nn]
    return name, num, num in _obtainable(emu)


def _report(emu, what, species):
    name, num, inside = _judge(emu, species)
    line = "%s: %s (%d), national %d, %s" % (what, name, species, num,
                                             "in the obtainable dex" if inside else "OUT OF THE DEX")
    print(line)
    emu.log.append(line)
    return inside


def _pace_until_battle(emu, maxsteps):
    """r10pg._wild's walk: nearest reachable pair of encounter tiles, pace until a battle."""
    ho = r10pg.ho
    w, h, coll, behavior = ho.map_grid(emu)
    pos = emu.location()[1]
    others = {(o[1], o[2]) for o in ho.objects(emu)}
    enc = {(x, y) for y in range(h) for x in range(w)
           if behavior(x, y) in r10pg.ENCOUNTER_MB and not coll(x, y) and (x, y) not in others}
    tiles = sorted((t for t in enc if any((t[0] + dx, t[1] + dy) in enc
                                          for dx, dy in ((1, 0), (-1, 0), (0, 1), (0, -1)))),
                   key=lambda t: abs(t[0] - pos[0]) + abs(t[1] - pos[1]))
    start = pos if pos in tiles else None
    for t in tiles[:40]:
        if start:
            break
        if r10pg._route(emu, t) is not None and r10pg._walk(emu, t) == "reached":
            start = t
    if start is None:
        raise HnsError("wildfind: no reachable encounter tile")
    x, y = start
    pair = None
    for d, (dx, dy) in (("LEFT", (-1, 0)), ("RIGHT", (1, 0)), ("UP", (0, -1)), ("DOWN", (0, 1))):
        t = (x + dx, y + dy)
        if t in enc:
            pair = (d, {"LEFT": "RIGHT", "RIGHT": "LEFT", "UP": "DOWN", "DOWN": "UP"}[d])
            break
    if pair is None:
        raise HnsError("wildfind: no second encounter tile next to %s" % (start,))
    bcb2 = emu.sym("BattleMainCB2")
    r10pg.repel(emu, 0)
    steps = 0
    while steps < maxsteps:
        for d in pair:
            emu.frames(16, d)
            steps += 1
            for _ in range(10):
                if emu.cb2() == bcb2 or emu.controllable():
                    break
                emu.frames(6)
            if not emu.controllable():
                break
        if not emu.controllable():
            break
    if emu.cb2() != bcb2:
        emu.wait_until(lambda: emu.cb2() == bcb2 or emu.controllable(), 600, "the battle", step=6)
    if emu.cb2() != bcb2:
        raise HnsError("wildfind: no encounter in %d steps" % steps)
    return steps


@script_op("wildfind")
def _op_wildfind(emu, f, path):
    prefix, tries, maxsteps = f[1], _arg(f, 2, 8), _arg(f, 3, 400)
    for k in range(tries):
        steps = _pace_until_battle(emu, maxsteps)
        p = "%s_t%d" % (prefix, k)
        n, end = hns.battle_walk(emu, p, (), 30, 6000)
        species = emu.r16(emu.sym("gBattleMons") + 0x88)
        inside = _report(emu, "wildfind %s after %d step(s)" % (p, steps), species)
        if not end.startswith("input:HandleInputChooseAction"):
            raise HnsError("wildfind: the intro ended at %s" % end)
        if not inside:
            return
        hns.battle_cursor(emu, "gActionSelectionCursor", 3)
        emu.tap("A", 4)
        hns.battle_walk(emu, p + "_run", (), 20, 6000)
        emu.wait_controllable(2400)
    raise HnsError("wildfind: %d encounters, all in the obtainable dex" % tries)


@script_op("obtainable")
def _op_obtainable(emu, f, path):
    for s in [int(x) for x in f[1:]] or [0]:
        d = sumvar.mon_fields(emu, s)
        if not d["hasSpecies"]:
            print("obtainable slot%d: empty" % s)
            continue
        _report(emu, "obtainable slot%d" % s, d["species"])


if __name__ == "__main__":
    sys.argv[0] = hns.__file__
    sys.exit(hns.main())
