#!/usr/bin/env python3
"""hns.py plus party-Pokemon ops for the summary-screen variant tours (sv_*.txt in this folder).

    monprobe [SLOT ...]          print each party slot: species, egg flag, friendship (egg cycles),
                                 pokerus, met location / level / game, OT gender and name bytes,
                                 hidden-nature modifier, status word and HP
    monset SLOT FIELD=VAL ...    change fields of gPlayerParty[SLOT]: friendship, pokerus, metloc,
                                 metlevel, metgame, otgender (encrypted substructs: decrypt,
                                 edit, fix the checksum, encrypt), ot0 (otName[0], plain byte).
                                 VAL is a number (0x.. or decimal) or a C constant (MAPSEC_*)
    sumwait [MAX]                run until the summary screen reads input (Task_HandleInput of
                                 pokemon_summary_screen.c is active, no page-print task left) and
                                 the screen is quiet
    sumkey KEY [N]               tap KEY N times on the summary screen, sumwait after each

struct BoxPokemon / PokemonSubstruct0-3: include/pokemon.h:128-282 (same in the English 2.0.6
tree). Encryption: EncryptBoxMon / CalculateBoxMonChecksum, src/pokemon.c:3704-3712, 4332-4362.
Usage: sumvar.py <hns.py args>   (e.g. sumvar.py tour ROM OUT --tours DIR --only RE --clip)
"""
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.dirname(os.path.dirname(HERE)))          # tools/hebrew/emu
import hns  # noqa: E402
from hns import script_op, HnsError, _arg  # noqa: E402

MON_SIZE, SECURE, SUB = 0x64, 32, 12
# sSubstructOffsets (src/pokemon.c:4350-4356): slot of substruct type T for personality % 24
SUBOFF = [
    [0, 0, 0, 0, 0, 0, 1, 1, 2, 3, 2, 3, 1, 1, 2, 3, 2, 3, 1, 1, 2, 3, 2, 3],
    [1, 1, 2, 3, 2, 3, 0, 0, 0, 0, 0, 0, 2, 3, 1, 1, 3, 2, 2, 3, 1, 1, 3, 2],
    [2, 3, 1, 1, 3, 2, 2, 3, 1, 1, 3, 2, 0, 0, 0, 0, 0, 0, 3, 2, 3, 2, 1, 1],
    [3, 2, 3, 2, 1, 1, 3, 2, 3, 2, 1, 1, 3, 2, 3, 2, 1, 1, 0, 0, 0, 0, 0, 0],
]


def _mon_addr(emu, slot):
    return emu.sym("gPlayerParty") + MON_SIZE * slot


def _decrypt(raw):
    pers = int.from_bytes(raw[0:4], "little")
    otid = int.from_bytes(raw[4:8], "little")
    key = pers ^ otid
    sec = bytearray(raw[SECURE:SECURE + 4 * SUB])
    for i in range(0, len(sec), 4):
        w = int.from_bytes(sec[i:i + 4], "little") ^ key
        sec[i:i + 4] = w.to_bytes(4, "little")
    return pers, key, sec


def _sub(pers, t):
    return SUBOFF[t][pers % 24] * SUB


def _checksum(sec):
    s = 0
    for i in range(0, len(sec), 4):
        w = int.from_bytes(sec[i:i + 4], "little")
        s += w + (w >> 16)
    return s & 0xFFFF


def mon_fields(emu, slot):
    raw = emu.read(_mon_addr(emu, slot), MON_SIZE)
    pers, key, sec = _decrypt(raw)
    s0, s3 = _sub(pers, 0), _sub(pers, 3)
    w3 = int.from_bytes(sec[s3 + 2:s3 + 4], "little")
    return dict(
        species=int.from_bytes(sec[s0:s0 + 2], "little") & 0x7FF,
        hasSpecies=bool(raw[19] & 2), egg=bool(raw[19] & 4),
        friendship=sec[s0 + 9], pokerus=sec[s3], metloc=sec[s3 + 1],
        metlevel=w3 & 0x7F, metgame=(w3 >> 7) & 0xF, otgender=(w3 >> 15) & 1,
        otname=raw[20:27].hex(), hiddenNatureMod=raw[18] >> 3,
        status=int.from_bytes(raw[0x50:0x54], "little"), hp=int.from_bytes(raw[0x56:0x58], "little"),
        checksum_ok=_checksum(sec) == int.from_bytes(raw[28:30], "little"))


@script_op("monprobe")
def _op_monprobe(emu, f, path):
    slots = [int(x) for x in f[1:]] or list(range(6))
    for s in slots:
        d = mon_fields(emu, s)
        if not d["hasSpecies"]:
            line = "monprobe slot%d: empty" % s
        else:
            line = "monprobe slot%d: " % s + " ".join("%s=%s" % kv for kv in d.items() if kv[0] != "hasSpecies")
        print(line)
        emu.log.append(line)


def _val(emu, v):
    try:
        return int(v, 0)
    except ValueError:
        return emu.const(v)


@script_op("monset")
def _op_monset(emu, f, path):
    slot = int(f[1])
    addr = _mon_addr(emu, slot)
    raw = bytearray(emu.read(addr, MON_SIZE))
    if not raw[19] & 2:
        raise HnsError("monset: party slot %d is empty" % slot)
    pers, key, sec = _decrypt(raw)
    s0, s3 = _sub(pers, 0), _sub(pers, 3)
    if _checksum(sec) != int.from_bytes(raw[28:30], "little"):
        raise HnsError("monset: slot %d checksum does not match before the edit (layout?)" % slot)
    plain = {}
    for kv in f[2:]:
        name, v = kv.split("=", 1)
        v = _val(emu, v)
        w3 = int.from_bytes(sec[s3 + 2:s3 + 4], "little")
        if name == "friendship":
            sec[s0 + 9] = v & 0xFF
        elif name == "pokerus":
            sec[s3] = v & 0xFF
        elif name == "metloc":
            sec[s3 + 1] = v & 0xFF
        elif name == "metlevel":
            w3 = (w3 & ~0x7F) | (v & 0x7F)
        elif name == "metgame":
            w3 = (w3 & ~(0xF << 7)) | ((v & 0xF) << 7)
        elif name == "otgender":
            w3 = (w3 & 0x7FFF) | ((v & 1) << 15)
        elif name == "ot0":
            plain[20] = v & 0xFF
            continue
        else:
            raise HnsError("monset: unknown field %s" % name)
        sec[s3 + 2:s3 + 4] = w3.to_bytes(2, "little")
    csum = _checksum(sec)
    enc = bytearray(sec)
    for i in range(0, len(enc), 4):
        w = int.from_bytes(enc[i:i + 4], "little") ^ key
        enc[i:i + 4] = w.to_bytes(4, "little")
    for i in range(0, len(enc), 4):
        emu.w32(addr + SECURE + i, int.from_bytes(enc[i:i + 4], "little"))
    emu.w16(addr + 28, csum)
    for off, b in plain.items():
        emu.w8(addr + off, b)
    d = mon_fields(emu, slot)
    if not d["checksum_ok"]:
        raise HnsError("monset: slot %d checksum wrong after the edit" % slot)
    line = "monset slot%d %s -> %s" % (slot, " ".join(f[2:]), d)
    print(line)
    emu.log.append(line)


def _sum_idle(emu):
    want = emu.sym("pokemon_summary_screen:Task_HandleInput")
    busy = set()
    for n in ("Task_PrintInfoPage", "Task_PrintSkillsPage", "Task_PrintBattleMoves",
              "Task_PrintContestMoves", "Task_ChangeSummaryMon", "Task_ChangeSummaryPage"):
        try:
            busy.add(emu.sym(n))
        except HnsError:
            pass
    fns = [fn for _, fn, _ in emu.tasks()]
    return want in fns and not any(fn in busy for fn in fns)


def sum_wait(emu, mx=900):
    emu.wait_until(lambda: _sum_idle(emu), mx, "the summary screen to read input", step=2)
    emu.wait_quiet(mx)
    emu.frames(4)


@script_op("sumwait")
def _op_sumwait(emu, f, path):
    sum_wait(emu, _arg(f, 1, 900))
    print("sumwait ok @%d" % emu.sync())


@script_op("setbits8")
def _op_setbits8(emu, f, path):
    """setbits8 HEXADDR SETMASK [CLEARMASK]: byte at ADDR |= SET, &= ~CLEAR (a bitfield option,
    e.g. the shiny-colours challenge option, SaveBlock3+0x2D bit 2)."""
    addr, setm = int(f[1], 16), int(f[2], 0)
    clr = int(f[3], 0) if len(f) > 3 else 0
    old = emu.r8(addr)
    emu.w8(addr, (old | setm) & ~clr & 0xFF)
    print("setbits8 %08X: %02X -> %02X" % (addr, old, emu.r8(addr)))


@script_op("sumkey")
def _op_sumkey(emu, f, path):
    for _ in range(_arg(f, 2, 1)):
        emu.tap(f[1], 4)
        sum_wait(emu)
    print("sumkey %s x%d ok @%d" % (f[1], _arg(f, 2, 1), emu.sync()))


if __name__ == "__main__":
    sys.argv[0] = hns.__file__
    sys.exit(hns.main())
