#!/usr/bin/env python3
"""Driver for the round-16 Pokegear tours (tours/r16_pokegear): radio.py (radio ops), rc.py (RIBBONS:
navshot, ribbonwalk, partyclear, ...), r3calls.py (phone list: mcclear, mcreg, mclistopen,
mclistrow, ...) and the party helpers of sumvar.py, plus:

    ribbonset SLOT MASK [clear]
                 OR MASK (hex) into the ribbon word of gPlayerParty[SLOT] (struct PokemonSubstruct3,
                 +8: coolRibbon:3 .. toughRibbon:3 = bits 0-14, championRibbon 15, winningRibbon 16,
                 victoryRibbon 17, artistRibbon 18, effortRibbon 19, ...; include/pokemon.h:183-218),
                 or clear those bits with 'clear'; decrypt, edit, fix the checksum, encrypt
    pw32 PTRSYM OFF VAL
                 write the u32 VAL at *PTRSYM + OFF (a field of a heap struct whose pointer is a
                 global, e.g. gPokenavResources)
    mcmapsec ROW MAPSEC
                 with the phone list open: set the map section of list entry ROW
                 (struct Pokenav_MatchCallMenu.matchCallEntries[ROW].mapSec, +28 + 4*ROW + 1,
                 src/pokenav_match_call_list.c:17-29; the struct is
                 gPokenavResources->substructPtrs[POKENAV_SUBSTRUCT_MATCH_CALL_MAIN], include/pokenav.h:72-80),
                 a stand-in for an entry whose map section is MAPSEC_NONE; the location window
                 (PrintMatchCallLocation, src/pokenav_match_call_gfx.c:1055-1068) reprints it when the
                 cursor moves onto that row

Run:  gear16.py tour ROM OUT --tours tools/hebrew/emu/tours/r16_pokegear [--clip] [--only RE]
Saves: HNS_SAVES=hns-tools/emu/saves_all for ladder*/menuA_base; the phone CHECK tour starts from
saves/r3_calls/base.sav, so it runs with HNS_SAVES=hns-tools/emu/saves_screens.
"""
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
SCRIPTS = os.path.dirname(HERE)
sys.path.insert(0, os.path.dirname(SCRIPTS))                                # tools/hebrew/emu
for d in ("r2_pokegear_radio", "r2_pokegear_ribbons_contests", "r3_pokegear_calls",
          "r2_summary_info_page_variants"):
    sys.path.insert(0, os.path.join(SCRIPTS, d))
import hns  # noqa: E402
import radio  # noqa: E402,F401  (radio ops; r2sf)
import rc  # noqa: E402,F401  (ribbons and contest ops; r3bf)
import r3calls  # noqa: E402,F401  (phone list ops)
import sumvar  # noqa: E402
from hns import script_op, HnsError  # noqa: E402

RIBBON_WORD = 8


@script_op("ribbonset")
def _op_ribbonset(emu, f, path):
    slot, mask = int(f[1]), int(f[2], 16)
    clear = len(f) > 3 and f[3] == "clear"
    addr = sumvar._mon_addr(emu, slot)
    raw = bytearray(emu.read(addr, sumvar.MON_SIZE))
    if not raw[19] & 2:
        raise HnsError("ribbonset: party slot %d is empty" % slot)
    pers, key, sec = sumvar._decrypt(raw)
    if sumvar._checksum(sec) != int.from_bytes(raw[28:30], "little"):
        raise HnsError("ribbonset: slot %d checksum does not match before the edit" % slot)
    s3 = sumvar._sub(pers, 3) + RIBBON_WORD
    w = int.from_bytes(sec[s3:s3 + 4], "little")
    w = (w & ~mask) if clear else (w | mask)
    sec[s3:s3 + 4] = (w & 0xFFFFFFFF).to_bytes(4, "little")
    csum = sumvar._checksum(sec)
    for i in range(0, len(sec), 4):
        emu.w32(addr + sumvar.SECURE + i, int.from_bytes(sec[i:i + 4], "little") ^ key)
    emu.w16(addr + 28, csum)
    if not sumvar.mon_fields(emu, slot)["checksum_ok"]:
        raise HnsError("ribbonset: slot %d checksum wrong after the edit" % slot)
    print("ribbonset slot%d word=%08X @%d" % (slot, w & 0xFFFFFFFF, emu.sync()))


@script_op("pw32")
def _op_pw32(emu, f, path):
    ptr = emu.r32(emu.sym(f[1]))
    if not 0x02000000 <= ptr < 0x03008000:
        raise HnsError("pw32: %s = %08X is not a RAM pointer" % (f[1], ptr))
    off, val = int(f[2], 16), int(f[3], 16)
    emu.w32(ptr + off, val)
    print("pw32 %s(%08X)+%X = %X @%d" % (f[1], ptr, off, val, emu.sync()))


PNR_SUBSTRUCTS, SUBSTRUCT_MATCH_CALL_MAIN = 16, 5
MC_ENTRIES, MC_ENTRY_SIZE = 28, 4


@script_op("mcmapsec")
def _op_mcmapsec(emu, f, path):
    row = int(f[1])
    sec = int(f[2], 0) if f[2][0].isdigit() else emu.const(f[2])
    res = emu.r32(emu.sym("gPokenavResources"))
    st = emu.r32(res + PNR_SUBSTRUCTS + 4 * SUBSTRUCT_MATCH_CALL_MAIN)
    if not 0x02000000 <= st < 0x02040000:
        raise HnsError("mcmapsec: no match call state (%08X)" % st)
    num = emu.r16(st + 10)
    if not 0 <= row < num:
        raise HnsError("mcmapsec: row %d, %d entries" % (row, num))
    a = st + MC_ENTRIES + MC_ENTRY_SIZE * row + 1
    old = emu.r8(a)
    emu.w8(a, sec)
    print("mcmapsec row %d: %d -> %d (%d entries) @%d" % (row, old, emu.r8(a), num, emu.sync()))


if __name__ == "__main__":
    sys.argv[0] = hns.__file__
    sys.exit(hns.main())
