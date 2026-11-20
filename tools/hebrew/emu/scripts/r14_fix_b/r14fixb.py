#!/usr/bin/env python3
"""hns.py plus the ops the r14 fix_b tours use: everything scripts/r5_known/r5known.py loads (the
Pokedex ops of scripts/r4_misc/r4misc.py, the storage ops of scripts/r2_pc_storage/pcs.py, the
ladder.py event ops), the summary ops of scripts/r2_summary_info_page_variants/sumvar.py, the
option ops of scripts/r4_battle_options/r4opt.py (opt, optexpect), and:

    nick12 SLOT TEXT [EN] write a nickname of up to 12 characters ('_' = space) into
                          gPlayerParty[SLOT]: characters 1-10 into BoxPokemon.nickname (offset 8,
                          plain), 11 and 12 into PokemonSubstruct0.nickname11 / nickname12
                          (include/pokemon.h:129-142, encrypted: decrypt, edit, fix the checksum,
                          encrypt). A shorter name gets EOS in both, so GetMonData returns exactly
                          TEXT (src/pokemon.c:4514-4540). On a build without TEXT_RTL the
                          optional EN is written instead; without EN the slot keeps its name.

    mapwarp MAP X Y       hns.py's own warpto by map constant (ladder.py's warpto, loaded here,
                          takes GROUP NUM X Y)
    menupick ACTION       hns.py's own startmenu (ladder.py, loaded here, replaces it with its
                          own): pick POKEDEX, POKEMON, BAG, ... in a start menu that is already
                          open (as after leaving the Pokedex), or open it first

    r14fixb.py tour ROM OUTDIR --tours <this folder>/tours [--clip] [--only RE]
"""
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(HERE, "..", ".."))                                # tools/hebrew/emu
sys.path.insert(0, os.path.join(HERE, "..", "r5_known"))
sys.path.insert(0, os.path.join(HERE, "..", "r2_summary_info_page_variants"))
sys.path.insert(0, os.path.join(HERE, "..", "r2_battle_frontier_facilities"))
sys.path.insert(0, os.path.join(HERE, "..", "r4_battle_options"))
sys.path.insert(0, os.path.join(HERE, "..", "..", ".."))                           # tools/hebrew
import hns  # noqa: E402
import r5known  # noqa: E402,F401  (dex, storage and ladder ops)
import sumvar  # noqa: E402,F401  (sumwait, sumkey, monprobe, monset)
import r4opt  # noqa: E402,F401  (opt, optexpect: the Gen 4 battle UI)
from hns import script_op, HnsError  # noqa: E402

EOS = 0xFF


@script_op("nick12")
def _op_nick12(emu, f, path):
    import bffops
    slot, text = int(f[1]), f[2]
    if "sRtlCharClass" not in emu.elf.byname:
        if len(f) < 4:
            print("nick12 %d: English build, name kept" % slot)
            return
        text = f[3]
    raw = bffops.encode(text)
    if len(raw) > 12:
        raise HnsError("nick12: %r is %d bytes, at most 12" % (text, len(raw)))
    full = raw + bytes([EOS]) * (12 - len(raw))
    addr = sumvar._mon_addr(emu, slot)
    mon = bytearray(emu.read(addr, sumvar.MON_SIZE))
    if not mon[19] & 2:
        raise HnsError("nick12: party slot %d is empty" % slot)
    pers, key, sec = sumvar._decrypt(mon)
    if sumvar._checksum(sec) != int.from_bytes(mon[28:30], "little"):
        raise HnsError("nick12: slot %d checksum does not match before the edit" % slot)
    s0 = sumvar._sub(pers, 0)
    w4 = int.from_bytes(sec[s0 + 4:s0 + 8], "little")
    w4 = (w4 & ~(0xFF << 21)) | (full[10] << 21)
    sec[s0 + 4:s0 + 8] = w4.to_bytes(4, "little")
    w10 = int.from_bytes(sec[s0 + 10:s0 + 12], "little")
    w10 = (w10 & ~(0xFF << 6)) | (full[11] << 6)
    sec[s0 + 10:s0 + 12] = w10.to_bytes(2, "little")
    csum = sumvar._checksum(sec)
    for i in range(0, len(sec), 4):
        w = int.from_bytes(sec[i:i + 4], "little") ^ key
        emu.w32(addr + sumvar.SECURE + i, w)
    emu.w16(addr + 28, csum)
    for i in range(10):
        emu.w8(addr + 8 + i, full[i])
    if not sumvar.mon_fields(emu, slot)["checksum_ok"]:
        raise HnsError("nick12: slot %d checksum wrong after the edit" % slot)
    line = "nick12 %d = %s (%s)" % (slot, text, raw.hex())
    print(line)
    emu.log.append(line)


script_op("mapwarp")(hns._op_warpto)


@script_op("menupick")
def _op_menupick(emu, f, path):
    emu.start_menu_cursor(f[1], press=True)
    print("menupick %s @%d" % (f[1], emu.sync()))


if __name__ == "__main__":
    sys.argv[0] = hns.__file__
    sys.exit(hns.main())
