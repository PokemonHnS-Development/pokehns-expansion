#!/usr/bin/env python3
"""Driver for the round-16 Battle Frontier tours (tours/r16_frontier): the field-odds ops
(scripts/r16_field_odds/odds16.py: wsym8/16/32, snapq, pocketset, partyexit, showsym, sethealloc, monotid,
partyfree and every op module it loads), the Frontier Pass ops (scripts/r2_bfpass/bfpops.py: passarea,
gamestat; fixops.py: pyrfill, pyrseek), the r13 Dome ops (scripts/r13_dome_doubles/r13dd.py: dstate,
domesync, domeinfo, domecards, drivemap, ...), the r5 Factory ops (scripts/r5_factory/r5fops.py) and
the radio ops (scripts/r2_pokegear_radio/radio.py: dexonly),
plus:

    ptror8 PTRSYM OFF MASK       OR MASK (hex) into the byte at *PTRSYM + OFF (a bit of a heap struct whose
                                 pointer is a global, e.g. sPassData's hasBattleRecord)
    ptrw16 PTRSYM OFF VAL        write the u16 VAL at *PTRSYM + OFF
    domeplayer MON MOVES EVS NATURE
                                 the player's Dome party data the info card reads
                                 (gSaveBlock2Ptr->frontier.domePlayerPartyData[MON], struct DomeMonData:
                                 u16 moves[4], u8 evs[6], u8 nature; SB2+DOME_PARTY): MOVES is
                                 MOVE_A,MOVE_B,MOVE_C,MOVE_D, EVS hp,atk,def,spe,spa,spd (numbers),
                                 NATURE a NATURE_* constant
    domeplayershow               print the three DomeMonData records
    playername HE EN             write the player's name (SB2+0, 7 characters + EOS): HE when HNS_SRC's
                                 charmap.txt has Hebrew letters, else EN (a worst case for {STR_VAR_1})
    domeslot SLOT TRAINER        DOME_TRAINERS[SLOT].trainerId = TRAINER (a number or TRAINER_FRONTIER_BRAIN)
    domeresult SLOT ELIM AT FORFEIT
                                 DOME_TRAINERS[SLOT] isEliminated / eliminatedAt / forfeited bits

Run:  front16.py tour ROM OUT --tours tools/hebrew/emu/tours/r16_frontier [--clip] [--only RE]
with HNS_SRC = the ROM's tree, HNS_SAVES = hns-tools/emu/saves_all, HNS_MAX_FRAMES set. The Frontier
Brain lines run through scripts/r16_battle_sweep/bsweep.py with the _fb_brain_F_S.txt setups (see
fb_brain_names.txt).
"""
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
SCRIPTS = os.path.dirname(HERE)
sys.path.insert(0, os.path.dirname(SCRIPTS))                      # tools/hebrew/emu
for d in ("r16_field_odds", "r2_bfpass", "r13_dome_doubles", "r5_factory", "r2_pokegear_radio"):
    sys.path.insert(0, os.path.join(SCRIPTS, d))
import hns  # noqa: E402
import odds16  # noqa: E402  (field-odds ops and their modules)
import bfpops  # noqa: E402,F401  (passarea, gamestat)
import fixops  # noqa: E402,F401  (pyrfill, pyrseek, menupos)
import r13dd  # noqa: E402,F401  (dstate, domesync, domeinfo, domecards, ...)
import r5fops  # noqa: E402,F401  (evdrive, snapat, frontierinfo, ...)
import radio  # noqa: E402,F401  (dexonly: clear the Pokedex caught flags)
from hns import script_op, HnsError, _arg  # noqa: E402

DOME_TRAINERS = r13dd.DOME_TRAINERS          # SB2 + 0xD24, u32 each: trainerId:10 isEliminated:1 eliminatedAt:2 forfeited:3
DOME_PARTY = 0xEFC        # frontier.domePlayerPartyData (include/global.h:626; the SB2 comments match the
                          # measured domeTrainers 0xD24 of r13dd), struct DomeMonData = 16 bytes (enum Move is packed)
DOME_MON_SIZE = 16


@script_op("domeplayer")
def _op_domeplayer(emu, f, path):
    mon = int(f[1], 0)
    moves = [odds16.const_value(emu, m) for m in f[2].split(",")]
    evs = [int(x, 0) for x in f[3].split(",")]
    nature = odds16.const_value(emu, f[4])
    a = emu.sb2() + DOME_PARTY + DOME_MON_SIZE * mon
    for i, m in enumerate(moves):
        emu.w16(a + 2 * i, m)
    for i, e in enumerate(evs):
        emu.w8(a + 8 + i, e)
    emu.w8(a + 14, nature)
    print("domeplayer %d: %s" % (mon, emu.read(a, 16).hex()))


@script_op("domeplayershow")
def _op_domeplayershow(emu, f, path):
    for mon in range(3):
        a = emu.sb2() + DOME_PARTY + DOME_MON_SIZE * mon
        print("domeplayer %d: %s" % (mon, emu.read(a, 16).hex()))


@script_op("ptror8")
def _op_ptror8(emu, f, path):
    p = emu.r32(emu.sym(f[1]))
    if not p:
        raise HnsError("ptror8: %s is NULL" % f[1])
    a = p + int(f[2], 16)
    v = emu.r8(a) | int(f[3], 16)
    emu.w8(a, v)
    print("ptror8 %s+%s = %#x" % (f[1], f[2], v))


@script_op("ptrw16")
def _op_ptrw16(emu, f, path):
    p = emu.r32(emu.sym(f[1]))
    if not p:
        raise HnsError("ptrw16: %s is NULL" % f[1])
    emu.w16(p + int(f[2], 16), odds16.const_value(emu, f[3]))
    print("ptrw16 %s+%s = %s" % (f[1], f[2], f[3]))


_CHARMAP = {}


def encode(src, text):
    """Game bytes of TEXT through SRC/charmap.txt (single characters only; as r16_battle_sweep/bsweep.py)."""
    cm = _CHARMAP.get(src)
    if cm is None:
        cm = {}
        for line in open(os.path.join(src, "charmap.txt"), encoding="utf-8"):
            line = line.split("@", 1)[0].strip()
            if len(line) >= 3 and line[0] == "'" and line[2] == "'" and "=" in line:
                vals = line.split("=", 1)[1].split()
                if len(vals) == 1 and line[1] not in cm:
                    cm[line[1]] = int(vals[0], 16)
        _CHARMAP[src] = cm
    return bytes(cm[c] for c in text)


@script_op("playername")
def _op_playername(emu, f, path):
    src = hns.src_dir(emu.elf)
    try:
        b = encode(src, f[1])
        which = "he"
    except KeyError:
        b = encode(src, f[2])
        which = "en"
    b = (b[:7] + b"\xff" * 8)[:8]
    for i, x in enumerate(b):
        emu.w8(emu.sb2() + i, x)
    print("playername (%s): %s" % (which, b.hex()))


@script_op("domeslot")
def _op_domeslot(emu, f, path):
    slot = int(f[1], 0)
    tid = 330 if f[2] == "TRAINER_FRONTIER_BRAIN" else odds16.const_value(emu, f[2])
    a = emu.sb2() + DOME_TRAINERS + 4 * slot
    v = emu.r32(a)
    emu.w32(a, (v & ~0x3FF) | (tid & 0x3FF))
    print("domeslot %d: trainerId %d (was %d)" % (slot, tid, v & 0x3FF))


@script_op("domeresult")
def _op_domeresult(emu, f, path):
    slot, elim, at, forf = (int(x, 0) for x in f[1:5])
    a = emu.sb2() + DOME_TRAINERS + 4 * slot
    v = emu.r32(a) & 0x3FF
    v |= (elim & 1) << 10 | (at & 3) << 11 | (forf & 7) << 13
    emu.w32(a, (emu.r32(a) & ~0xFFFF) | v)
    print("domeresult %d: %#06x" % (slot, v))


if __name__ == "__main__":
    sys.argv[0] = hns.__file__
    sys.exit(hns.main())
