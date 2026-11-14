#!/usr/bin/env python3
"""hns.py plus ladder.py plus the ops the r3 max-number tours use (trainer card, save info, CONTINUE,
mart and Mom's savings at their largest values).

    r3num.py run SCRIPT OUTDIR [--save SAV] [--save-out SAV]
    r3num.py tour ROM OUTDIR --tours <this folder> [--clip] [--only RE]

Added here (offsets measured with offsetof() against include/global.h of the 0.2 tree, -mabi=apcs-gnu:
SaveBlock1.money 0x494 (matches hns.OFF), .momSavings 0x3D88 (MomSavingsData: u32 momsMoney +0,
u16 normalGiftFlags +4, u8 isSavingMoney +6, u8 isInitialized +7), .gameStats 0x1CBC (u32[64]);
SaveBlock2.encryptionKey 0xAC, .playTimeHours 0xE):
    gamestat ID VALUE      write gSaveBlock1Ptr->gameStats[ID] = VALUE ^ encryptionKey, as SetGameStat
                           does (src/overworld.c:547-551). ID is a number or a GAME_STAT_* name.
    hofdebut H M S         gamestat GAME_STAT_FIRST_HOF_PLAY_TIME (H << 16 | M << 8 | S); stops unless
                           GAME_STAT_ENTERED_HOF is already set (the card prints the debut only then,
                           src/trainer_card.c:771-773)
    momsavings N           gSaveBlock1Ptr->momSavings.momsMoney = N, isInitialized = TRUE (else
                           Mom_EnsureInitialized clears it, src/mom_savings.c:76-87)
    numstate               print money, Mom's balance, play time and the stats the card reads
From r3bf.py / r2sf.py: drive PREFIX TARGET, pick N, ss/sl, warpraw, ...
    snapcolon PREFIX       two shots 62 frames apart (the trainer card's time colon blinks every 61
                           frames, src/trainer_card.c:1757-1765), PREFIX_a and PREFIX_b
"""
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(HERE, "..", ".."))                                # tools/hebrew/emu
import hns     # noqa: E402
import ladder  # noqa: E402,F401  (registers event, eventstart, rungoto, playtime, ...)
sys.path.insert(0, os.path.join(HERE, "..", "r3_frontier"))
import r3bf    # noqa: E402,F401  (drive, pick, and the r2 service ops: ss, sl, warpraw, ...)
from hns import script_op, HnsError  # noqa: E402

SB1_MONEY = 0x494
SB1_MOM = 0x3D88
SB1_STATS = 0x1CBC
SB2_KEY = 0xAC
SB2_PLAYTIME = 0x0E
STATS = {"SAVED_GAME": 0, "FIRST_HOF_PLAY_TIME": 1, "ENTERED_HOF": 10, "POKEMON_TRADES": 21,
         "LINK_BATTLE_WINS": 23, "LINK_BATTLE_LOSSES": 24, "LINK_BATTLE_DRAWS": 25,
         "POKEBLOCKS_WITH_FRIENDS": 34, "WON_LINK_CONTEST": 35}


def _stat_id(s):
    s = s.replace("GAME_STAT_", "")
    return STATS[s] if s in STATS else int(s, 0)


def get_stat(emu, i):
    return emu.r32(emu.sb1() + SB1_STATS + 4 * i) ^ emu.r32(emu.sb2() + SB2_KEY)


def set_stat(emu, i, v):
    key = emu.r32(emu.sb2() + SB2_KEY)
    emu.w32(emu.sb1() + SB1_STATS + 4 * i, (v ^ key) & 0xFFFFFFFF)
    got = get_stat(emu, i)
    if got != v:
        raise HnsError("gamestat %d: wrote %d, reads %d" % (i, v, got))


@script_op("gamestat")
def _op_gamestat(emu, f, path):
    i, v = _stat_id(f[1]), int(f[2], 0)
    before = get_stat(emu, i)
    set_stat(emu, i, v)
    print("gamestat %d: %d -> %d" % (i, before, v))


@script_op("hofdebut")
def _op_hofdebut(emu, f, path):
    h, m, s = (int(x) for x in f[1:4])
    if not get_stat(emu, STATS["ENTERED_HOF"]):
        raise HnsError("hofdebut: GAME_STAT_ENTERED_HOF is 0 (not a champion save)")
    before = get_stat(emu, 1)
    set_stat(emu, 1, h << 16 | m << 8 | s)
    print("hofdebut %d:%02d:%02d (was %d:%02d:%02d)" % (h, m, s, before >> 16, (before >> 8) & 0xFF, before & 0xFF))


@script_op("momsavings")
def _op_momsavings(emu, f, path):
    n = int(f[1], 0)
    a = emu.sb1() + SB1_MOM
    before = emu.read(a, 8)
    emu.w32(a, n)
    emu.w8(a + 7, 1)
    print("momsavings %d (was %d, flags %s)" % (n, int.from_bytes(before[:4], "little"), before[4:].hex()))


@script_op("numstate")
def _op_numstate(emu, f, path):
    sb1, sb2 = emu.sb1(), emu.sb2()
    key = emu.r32(sb2 + SB2_KEY)
    money = emu.r32(sb1 + SB1_MONEY) ^ key
    mom = emu.read(sb1 + SB1_MOM, 8)
    pt = emu.read(sb2 + SB2_PLAYTIME, 4)
    hof = get_stat(emu, 1)
    print("numstate: money %d, mom %d (saving %d, init %d), playtime %d:%02d:%02d, hof debut %d:%02d:%02d, "
          "entered hof %d, link W/L %d/%d, trades %d, pokeblocks w/ friends %d, link contests %d" % (
              money, int.from_bytes(mom[:4], "little"), mom[6], mom[7], pt[0] | pt[1] << 8, pt[2], pt[3],
              hof >> 16, (hof >> 8) & 0xFF, hof & 0xFF, get_stat(emu, 10), get_stat(emu, 23), get_stat(emu, 24),
              get_stat(emu, 21), get_stat(emu, 34), get_stat(emu, 35)))


@script_op("snapcolon")
def _op_snapcolon(emu, f, path):
    emu.frames(2)
    emu.shot(f[1] + "_a")
    emu.frames(62)
    emu.shot(f[1] + "_b")
    print("snapcolon %s @%d" % (f[1], emu.sync()))


if __name__ == "__main__":
    sys.exit(hns.main())
