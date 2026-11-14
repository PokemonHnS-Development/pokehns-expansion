#!/usr/bin/env python3
"""hns.py plus the ops the r4 battle-option tours use (OPTIONS > BATTLE rows 4-7: the Gen 4
battle UI, the last-used-ball prompt, the quick run type and its intro hint).
Run:  r4opt.py tour ROM OUT --tours <this folder> [--clip] [--only RE]
      r4opt.py run SCRIPT OUT --save SRC.sav --save-out DST.sav   (a save with options set)

    opt FIELD=VAL [FIELD=VAL ...]       write ChallengeSettings bitfields in gSaveblock3
    optexpect FIELD=VAL [...]           fail unless the bitfields hold these values
    optshow                             print every known bitfield
    nick SLOT HE_TEXT EN_TEXT           write a nickname (up to 10 letters, '_' = space) into
                                        gPlayerParty[SLOT] (BoxPokemon.nickname, offset 8, outside
                                        the encrypted substructs): HE_TEXT on a TEXT_RTL build,
                                        EN_TEXT otherwise. A 10-letter name needs a species whose
                                        own name has exactly 10 letters (nickname11 is then EOS,
                                        src/pokemon.c:4523-4540, 5051-5056): HITMONCHAN in both.
    holdshots PREFIX KEYS COUNT EVERY   hold KEYS (runner syntax, e.g. Lb+Rb) for COUNT x EVERY
                                        frames, a shot PREFIX_NN after every EVERY frames; a shot
                                        identical to the one before it is dropped (the quick-run
                                        check reads the held keys while the result text prints)
    pressnext / pressprev               press the key that moves an option row to its next /
                                        previous choice: LEFT / RIGHT on a TEXT_RTL build (a
                                        mirrored row lists its choices right to left,
                                        src/option_menu.c:944-958), RIGHT / LEFT otherwise
FIELDs (struct ChallengeSettings, include/global.h:253-275; u8 bitfields packed from bit 0):
    fastIntro fastBattle optionStyle lrToRun ballPrompt newBackgrounds newBattleUI
    genOneRecharge musicOnOff runType(3 bits)
Values are the option-menu choice indexes (src/option_menu.c:1105-1112): newBattleUI 1 = Gen 4,
ballPrompt 1 = window off, lrToRun 1 = hint off, runType 0 none / 1 L+R+A / 2 B->A / 3 B.
"""
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(HERE, "..", ".."))                                # tools/hebrew/emu
sys.path.insert(0, os.path.join(HERE, "..", "r2_rival_names"))
sys.path.insert(0, os.path.join(HERE, "..", "r2_battle_frontier_facilities"))
sys.path.insert(0, os.path.join(HERE, "..", "r3_frontier"))
sys.path.insert(0, os.path.join(HERE, "..", "r2_safari_pokeblock_bug_contest"))
sys.path.insert(0, os.path.join(HERE, "..", "..", ".."))                           # tools/hebrew
import hns  # noqa: E402
import rivalops  # noqa: E402,F401  (registers the r2/r3 ops: bwin, ss/sl, drive, ...)
from hns import script_op, HnsError  # noqa: E402

# (byte, bit, width) inside struct ChallengeSettings
FIELDS = {
    "fastIntro": (0, 7, 1),
    "fastBattle": (1, 0, 1),
    "optionStyle": (1, 1, 1),
    "lrToRun": (1, 2, 1),
    "ballPrompt": (1, 3, 1),
    "newBackgrounds": (1, 4, 1),
    "newBattleUI": (1, 5, 1),
    "genOneRecharge": (1, 6, 1),
    "musicOnOff": (1, 7, 1),
    "runType": (2, 0, 3),
}


def cs_addr(emu):
    return emu.r32(emu.sym("gSaveBlock3Ptr")) + hns.BATTLE_OFF["SaveBlock3.challengeSettings"]


def get_field(emu, name):
    byte, bit, width = FIELDS[name]
    return (emu.r8(cs_addr(emu) + byte) >> bit) & ((1 << width) - 1)


def set_field(emu, name, val):
    byte, bit, width = FIELDS[name]
    a = cs_addr(emu) + byte
    mask = ((1 << width) - 1) << bit
    emu.w8(a, (emu.r8(a) & ~mask) | ((val << bit) & mask))


def pairs(f):
    out = []
    for kv in f[1:]:
        k, v = kv.split("=")
        if k not in FIELDS:
            raise HnsError("opt: unknown field %s (known: %s)" % (k, ", ".join(FIELDS)))
        out.append((k, int(v, 0)))
    return out


def show(emu):
    raw = emu.read(cs_addr(emu), 3)
    return "bytes %s: %s" % (raw.hex() if isinstance(raw, (bytes, bytearray)) else raw,
                             " ".join("%s=%d" % (k, get_field(emu, k)) for k in FIELDS))


@script_op("opt")
def _op_opt(emu, f, path):
    for k, v in pairs(f):
        set_field(emu, k, v)
    print("opt %s -> %s" % (" ".join(f[1:]), show(emu)))


@script_op("optexpect")
def _op_optexpect(emu, f, path):
    bad = [(k, v, get_field(emu, k)) for k, v in pairs(f) if get_field(emu, k) != v]
    if bad:
        raise HnsError("optexpect: %s (%s)" % (", ".join("%s=%d not %d" % (k, g, v) for k, v, g in bad), show(emu)))
    print("optexpect %s ok" % " ".join(f[1:]))


@script_op("optshow")
def _op_optshow(emu, f, path):
    print("optshow " + show(emu))


def rtl(emu):
    return "sRtlCharClass" in emu.elf.byname


@script_op("nick")
def _op_nick(emu, f, path):
    import bffops
    text = f[2] if rtl(emu) else f[3]
    raw = bffops.encode(text)
    if len(raw) > 10:
        raise HnsError("nick: %r is %d bytes, at most 10" % (text, len(raw)))
    raw = raw + b"\xff" * (10 - len(raw))
    addr = emu.sym("gPlayerParty") + int(f[1]) * 0x64 + 8
    for i, b in enumerate(raw):
        emu.w8(addr + i, b)
    try:
        import textwidth as tw
        w = tw.TextModel().width(text.replace("_", " "), "FONT_SMALL")
    except Exception:
        w = "?"
    print("nick %s = %s (%s, FONT_SMALL %s px)" % (f[1], text, raw.hex(), w))


@script_op("holdshots")
def _op_holdshots(emu, f, path):
    prefix, keys, count, every = f[1], f[2], int(f[3]), int(f[4])
    prev, n = None, 0
    for _ in range(count):
        emu.frames(every, keys)
        name = "%s_%02d" % (prefix, n + 1)
        p = emu.shot(name)
        data = open(p, "rb").read()
        if data == prev:
            os.remove(p)
            continue
        prev = data
        n += 1
        emu.shots = getattr(emu, "shots", []) + [name]
    print("holdshots %s %s: %d shot(s) @%d" % (prefix, keys, n, emu.sync()))


@script_op("pressnext", "pressprev")
def _op_pressnext(emu, f, path):
    nxt = f[0] == "pressnext"
    key = ("LEFT" if nxt else "RIGHT") if rtl(emu) else ("RIGHT" if nxt else "LEFT")
    emu.tap(key, 4)
    emu.wait_quiet(900)
    print("%s = %s" % (f[0], key))


if __name__ == "__main__":
    sys.argv[0] = hns.__file__
    sys.exit(hns.main())
