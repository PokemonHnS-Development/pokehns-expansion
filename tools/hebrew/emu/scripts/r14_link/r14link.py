#!/usr/bin/env python3
"""hns.py plus the ops the r14 link-screen tours (tours/r14_link/*.txt) use. The link screens need a
second GBA; these tours drive their real scripts and callbacks on one emulator and fake the partner
in RAM.

Imported ops: scripts/r5_npcsvc/npcsvc.py (fieldwatch, pick, partyinfo, ... through r5lat / rc /
tutor / sumvar / bffops) and scripts/r2_boot_title_save/bts.py (setcb2, burst, taskpoke, ptrpoke,
ptrpin, pinsym, ...; its textwatch replaces rc's) and scripts/r11_tents/r11sym.py (FILE:sym
lookups such as menu:sMenu on the clip ELF through the sibling pokehns.elf/.map).

Run:  r14link.py tour ROM OUT --tours <emu>/tours/r14_link [--clip] [--only RE]
"""
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
EMU = os.path.dirname(os.path.dirname(HERE))
sys.path.insert(0, EMU)
sys.path.insert(0, os.path.join(EMU, "scripts", "r5_npcsvc"))
sys.path.insert(0, os.path.join(EMU, "scripts", "r2_boot_title_save"))
sys.path.insert(0, os.path.join(EMU, "scripts", "r11_tents"))
import hns  # noqa: E402
import npcsvc  # noqa: E402,F401
import bts  # noqa: E402,F401
import r11sym  # noqa: E402,F401  (FILE:sym lookups for the clip ELF, which has no .map next to it)

from hns import script_op, HnsError, _arg  # noqa: E402

# ---------------------------------------------------------------------------- the faked link partner
PARTY_BYTES, MON_SIZE = 600, 100
BOX_OTNAME, NAME_LEN = 20, 7          # struct BoxPokemon.otName (include/pokemon.h:255-268), PLAYER_NAME_LENGTH
LP_SIZE = 0x1C                        # struct LinkPlayer (include/link.h:169-182)
_CHARMAP = {}


def _lang():
    return os.environ.get("LK_LANG", "en")


def _pick(arg):
    """'he:דנה,en:DANA' -> the text for LK_LANG (a plain string is used as is)."""
    if ":" not in arg:
        return arg
    d = dict(x.split(":", 1) for x in arg.split(","))
    return d.get(_lang(), d.get("en"))


def encode(text):
    """Game bytes of TEXT through charmap.txt in HNS_SRC (single characters only)."""
    if not _CHARMAP:
        src = os.environ.get("HNS_SRC")
        if not src:
            raise HnsError("encode: HNS_SRC is not set")
        for line in open(os.path.join(src, "charmap.txt"), encoding="utf-8"):
            line = line.split("@", 1)[0].strip()
            if len(line) >= 3 and line[0] == "'" and line[2] == "'" and "=" in line:
                vals = line.split("=", 1)[1].split()
                if len(vals) == 1 and line[1] not in _CHARMAP:
                    _CHARMAP[line[1]] = int(vals[0], 16)
    try:
        return bytes(_CHARMAP[c] for c in text)
    except KeyError as e:
        raise HnsError("encode: %r is not in the charmap" % e.args[0])


def _name_bytes(text, n):
    b = encode(text)[:n]
    return b + b"\xff" * (n + 1 - len(b))


def _write(emu, addr, data):
    for i in range(0, len(data) - len(data) % 4, 4):
        emu.w32(addr + i, int.from_bytes(data[i:i + 4], "little"))
    for i in range(len(data) - len(data) % 4, len(data)):
        emu.w8(addr + i, data[i])


@script_op("stashparty")
def _op_stashparty(emu, f, path):
    """stashparty NAME: keep a copy of gPlayerParty and its count under NAME."""
    st = emu.__dict__.setdefault("party_stash", {})
    st[f[1]] = (bytearray(emu.read(emu.sym("gPlayerParty"), PARTY_BYTES)), emu.r8(emu.sym("gPlayerPartyCount")))
    print("stashparty %s: %d mon(s)" % (f[1], st[f[1]][1]))


@script_op("otname")
def _op_otname(emu, f, path):
    """otname NAME TEXT: set the OT name (unencrypted header, outside the checksum) of every Pokemon in the
    stashed party NAME. TEXT may be 'he:...,en:...'."""
    data, n = emu.party_stash[f[1]]
    nm = _name_bytes(_pick(f[2]), NAME_LEN)[:NAME_LEN]
    for i in range(n):
        o = i * MON_SIZE + BOX_OTNAME
        data[o:o + NAME_LEN] = nm
    print("otname %s: %s" % (f[1], _pick(f[2])))


@script_op("loadparty")
def _op_loadparty(emu, f, path):
    """loadparty NAME player|enemy: write the stashed party into gPlayerParty (and gPlayerPartyCount) or
    gEnemyParty."""
    data, n = emu.party_stash[f[1]]
    if f[2] == "player":
        _write(emu, emu.sym("gPlayerParty"), bytes(data))
        emu.w8(emu.sym("gPlayerPartyCount"), n)
    else:
        _write(emu, emu.sym("gEnemyParty"), bytes(data))
    print("loadparty %s -> %s (%d mon(s)) @%d" % (f[1], f[2], n, emu.sync()))


@script_op("linkplayers")
def _op_linkplayers(emu, f, path):
    """linkplayers PARTNER [GENDER] [PARTNER2 GENDER2 PARTNER3 GENDER3]: fill gLinkPlayers as a cable link
    would: [0] the player (name, gender, trainer id from the save), [1..] the partners (TEXT may be
    'he:...,en:...'), id = the battler/multiplayer index, version 3 (Emerald), language from LK_LANG."""
    base = emu.sym("gLinkPlayers")
    sb2 = emu.r32(emu.sym("gSaveBlock2Ptr"))
    pname = emu.read(sb2, NAME_LEN + 1)
    pgender = emu.r8(sb2 + 8)
    tid = emu.r32(sb2 + 0xA)
    lang = 2   # LANGUAGE_ENGLISH (include/constants/global.h); the Hebrew build keeps GAME_LANGUAGE
    people = [(pname, pgender, tid)]
    rest = f[1:]
    k = 0
    while k < len(rest):
        nm = _name_bytes(_pick(rest[k]), NAME_LEN)
        g = int(rest[k + 1]) if k + 1 < len(rest) else 0
        people.append((nm, g, 0x12345678 + k))
        k += 2
    for i, (nm, g, t) in enumerate(people):
        rec = bytearray(LP_SIZE)
        rec[0:2] = (0x4003).to_bytes(2, "little")      # VERSION_EMERALD
        rec[4:8] = t.to_bytes(4, "little")
        rec[8:16] = nm[:8].ljust(8, b"\xff")
        rec[0x10] = 0x11                                  # national dex + cleared game
        rec[0x12] = 0x11
        rec[0x13] = g
        rec[0x18:0x1A] = i.to_bytes(2, "little")
        rec[0x1A:0x1C] = lang.to_bytes(2, "little")
        _write(emu, base + i * LP_SIZE, bytes(rec))
    print("linkplayers: %d player(s) @%d" % (len(people), emu.sync()))


@script_op("ptrread")
def _op_ptrread(emu, f, path):
    """ptrread PTRSYM HEXOFF N: print N bytes of the heap struct PTRSYM points to."""
    base = emu.r32(emu.sym(f[1]))
    b = emu.read(base + int(f[2], 16), int(f[3]))
    print("ptrread %s+%s: %s @%d" % (f[1], f[2], b.hex(" "), emu.sync()))


@script_op("orw32", "andnotw32")
def _op_orw32(emu, f, path):
    """orw32 SYM HEXMASK / andnotw32 SYM HEXMASK: set / clear bits of a u32 variable (gBattleTypeFlags)."""
    a = emu.sym(f[1])
    v = emu.r32(a)
    m = int(f[2], 16)
    nv = (v | m) if f[0] == "orw32" else (v & ~m)
    emu.w32(a, nv)
    print("%s %s: %08X -> %08X @%d" % (f[0], f[1], v, nv & 0xFFFFFFFF, emu.sync()))


@script_op("waitword")
def _op_waitword(emu, f, path):
    """waitword SYM TARGETSYM [MAX]: run frame by frame until the u32 at SYM equals TARGETSYM's address
    (a battle script label in gBattlescriptCurrInstr, a callback in a pointer variable)."""
    a, want = emu.sym(f[1]), emu.sym(f[2])
    emu.wait_until(lambda: emu.r32(a) == want, _arg(f, 3, 3000), "%s == %s" % (f[1], f[2]), step=1)
    print("waitword %s == %s ok @%d" % (f[1], f[2], emu.sync()))


@script_op("waitnz")
def _op_waitnz(emu, f, path):
    """waitnz SYM [MAX] [KEY]: run frame by frame until the byte at SYM is not 0, tapping KEY (default A)
    every 30 frames meanwhile (pages that wait for a key)."""
    a, maxf = emu.sym(f[1]), _arg(f, 2, 3000)
    key = f[3] if len(f) > 3 else "A"
    n = 0
    while emu.r8(a) == 0:
        if n >= maxf:
            raise hns.TourTimeout("waitnz %s: still 0 after %d frames" % (f[1], maxf))
        if n % 30 == 15 and key != "-":
            emu.send("1 %s" % key)
        else:
            emu.frames(1)
        n += 1
    print("waitnz %s = %d @%d" % (f[1], emu.r8(a), emu.sync()))


@script_op("waittext")
def _op_waittext(emu, f, path):
    """waittext [MAX]: run frame by frame until a text printer is drawing or waits for a key."""
    emu.wait_until(lambda: emu.text_state() in ("busy", "key"), _arg(f, 1, 600), "a text printer", step=1)
    print("waittext ok (%s) @%d" % (emu.text_state(), emu.sync()))


@script_op("waitstate")
def _op_waitstate(emu, f, path):
    """waitstate N|N,M,.. [MAX]: run frame by frame until gMain.state is one of the values (decimal)."""
    want = {int(x) for x in f[1].split(",")}
    a = emu.sym("gMain") + hns.OFF["Main.state"]
    emu.wait_until(lambda: emu.r8(a) in want, _arg(f, 2, 600), "gMain.state in %s" % f[1], step=1)
    print("waitstate %s ok (%d) @%d" % (f[1], emu.r8(a), emu.sync()))


if __name__ == "__main__":
    sys.argv[0] = hns.__file__
    sys.exit(hns.main())
