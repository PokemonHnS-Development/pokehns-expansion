#!/usr/bin/env python3
"""Ops for the Battle Tower multi battle tour with an NPC partner (bt_multi_*.txt in this
folder), on top of bffops.py (sb2w16, saveyes, bwin, drivex) and r3bf.py (drive, pick, ss, sl).
Run:  r4ops.py tour ROM OUT --tours <this folder> [--clip] [--only RE]

    fids START V [V ...]
        write frontier.trainerIds[START..] (u16, SaveBlock2+0xCB4; offsetof() measured on the
        release tree and on English 2.0.6, the same in both)
    ptalk PREFIX K TRAINER MON1 MON2
        the player stands next to partner candidate K (local id K+2) and faces it. Pokes
        trainerIds[K] = TRAINER and its two Pokemon ([8+2K], [9+2K]) = MON1, MON2 (frontier mon
        ids), presses A and shoots every page of the intro, the first Pokemon and the second
        Pokemon with the YES/NO (PREFIX_NN). Then, from a savestate taken at the YES/NO: YES,
        every page of the accept line (PREFIX_acc_NN), back to the savestate, NO, every page of
        the reject line (PREFIX_rej_NN), until the player is free again.
    waitmap NAME MAP [MAX]
        run until the player is on MAP in the overworld with no fade, then shoot NAME
"""
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(HERE, "..", ".."))                                # tools/hebrew/emu
sys.path.insert(0, os.path.join(HERE, "..", "r2_battle_frontier_facilities"))
sys.path.insert(0, os.path.join(HERE, "..", "r3_frontier"))
sys.path.insert(0, os.path.join(HERE, "..", "r2_safari_pokeblock_bug_contest"))
import hns  # noqa: E402
import bffops  # noqa: E402,F401  (registers sb2w16 / saveyes / bwin / drivex, and r3bf's ops)
import r3bf  # noqa: E402
from hns import script_op, HnsError, SCRIPT_OPS, _arg  # noqa: E402

TRAINER_IDS = 0xCB4


@script_op("fids")
def _op_fids(emu, f, path):
    base = emu.sb2() + TRAINER_IDS
    start = int(f[1], 0)
    for i, v in enumerate(f[2:]):
        emu.w16(base + 2 * (start + i), int(v, 0))
    print("fids %d: %s @%d" % (start, " ".join(f[2:]), emu.sync()))


def _pages(emu, prefix, maxpages=6, first_wait=300):
    """Shoot each page that waits for a key, then A; stop when no page comes within the wait."""
    n = 0
    wait = first_wait
    while n < maxpages:
        try:
            emu.wait_until(lambda: emu.wants_key(), wait, "a text page", step=2)
        except HnsError:
            break
        emu.wait_quiet(300)
        n += 1
        r3bf._shot(emu, "%s_%02d" % (prefix, n))
        emu.tap("A", 0)
        emu.wait_until(lambda: not emu.wants_key(), 90, "the text to take the key", step=1)
        wait = 90
    return n


@script_op("ptalk")
def _op_ptalk(emu, f, path):
    prefix = f[1]
    k, tid, m1, m2 = (int(x, 0) for x in f[2:6])
    base = emu.sb2() + TRAINER_IDS
    emu.w16(base + 2 * k, tid)
    emu.w16(base + 2 * (8 + 2 * k), m1)
    emu.w16(base + 2 * (9 + 2 * k), m2)
    emu.tap("A", 0)
    SCRIPT_OPS["drive"](emu, ["drive", prefix, "menu", "10"], path)
    state = os.path.join(emu.outdir, "_ptalk.ss")
    emu.send("ss %s" % state)
    emu.sync()
    SCRIPT_OPS["pick"](emu, ["pick", "0"], path)
    na = _pages(emu, prefix + "_acc", 4)
    emu.send("sl %s" % state)
    emu._bw_box = None
    emu.sync()
    SCRIPT_OPS["pick"](emu, ["pick", "1"], path)
    nr = _pages(emu, prefix + "_rej", 4)
    emu.wait_until(lambda: emu.controllable(), 600, "the player to be free", step=2)
    print("ptalk %s: class trainer %d, accept %d page(s), reject %d page(s) @%d"
          % (prefix, tid, na, nr, emu.sync()))


# struct Apprentice (include/global.h:430), offsetof() measured on both trees: SaveBlock2+0xDC,
# 0x44 each; byte 0 = id:5 | lvlMode:2, numQuestions +1, number +2, party[3] +4 (struct
# ApprenticeMon, 0xC: species +0, moves[4] +2, item +0xA), playerName[8] +0x38, language +0x3F.
APPRENTICES, APPRENTICE_SIZE = 0xDC, 0x44
TRAINER_RECORD_MIXING_APPRENTICE = 325          # FRONTIER_TRAINERS_COUNT 320 + BATTLE_TOWER_RECORD_COUNT 5


@script_op("apprentice")
def _op_apprentice(emu, f, path):
    """apprentice SLOT ID NUMBER NAME [SPECIES MOVE]...: fill apprentices[SLOT] (a record-mixed
    Apprentice: gApprentices[ID], Lv.50, NUMBER, trained by NAME, '_' = space, Latin or Hebrew,
    language English) with up to three Pokemon, and set gFrontierTempParty[0..1] = 0, 1 (the
    party slots the partner messages name, set by GetApprenticeMultiPartnerParty on a real load)."""
    slot, aid, number = int(f[1]), int(f[2]), int(f[3])
    base = emu.sb2() + APPRENTICES + APPRENTICE_SIZE * slot
    emu.w8(base, (aid & 0x1F) | (1 << 5))
    emu.w8(base + 1, 5)
    emu.w8(base + 2, number)
    mons = f[5:]
    for i in range(3):
        sp = emu.const(mons[2 * i]) if 2 * i < len(mons) else 0
        mv = emu.const(mons[2 * i + 1]) if 2 * i + 1 < len(mons) else 0
        emu.w16(base + 4 + 0xC * i, sp)
        emu.w16(base + 4 + 0xC * i + 2, mv)
        for j in range(1, 4):
            emu.w16(base + 4 + 0xC * i + 2 + 2 * j, 0)
    name = (bffops.encode(f[4]) + b"\xff" * 7)[:7]          # playerName[PLAYER_NAME_LENGTH]
    for i, c in enumerate(name):
        emu.w8(base + 0x38 + i, c)
    emu.w8(base + 0x3F, 2)
    tmp = emu.sym("gFrontierTempParty")
    emu.w16(tmp, 0)
    emu.w16(tmp + 2, 1)
    print("apprentice %d: id %d no. %d %s @%d" % (slot, aid, number, f[4], emu.sync()))


@script_op("waitmap")
def _op_waitmap(emu, f, path):
    name, mapname = f[1], f[2]
    mx = _arg(f, 3, 3000)
    g, n = hns.map_lookup(emu.elf, mapname)
    ow = emu.sym("CB2_Overworld")

    def there():
        (lg, ln, _, _, _), _pos = emu.location()
        return lg == g and ln == n and emu.cb2() == ow and not emu.fading()
    emu.wait_until(there, mx, "map %s" % mapname, step=2)
    emu.frames(8)
    r3bf._shot(emu, name)
    print("waitmap %s: %s @%d" % (name, mapname, emu.sync()))


if __name__ == "__main__":
    sys.argv[0] = hns.__file__
    sys.exit(hns.main())
