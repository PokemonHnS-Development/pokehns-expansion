#!/usr/bin/env python3
"""svc.py (hns.py + textwatch/scenewatch/burst/scrollshots/scrollmem) plus ops for the
field puzzle / berry / lottery screens:

    probe                       print puzzle flags, lottery vars, TID, party/box OT ids
    settid HEX16                set the low 16 bits of the player's trainer id (SB2+0x0A)
    berry ID FIELD VAL          poke struct BerryTree (include/global.berry.h:72-89) in SB1
                                berryTrees[ID] (SB1+0x1DBC, 8 bytes each); FIELD is
                                berry|stage|yield|minutes
    berryshow ID                print berryTrees[ID]
    clearberries                empty the Berries pocket
    zeromon SLOT                zero gPlayerParty[SLOT] so a givemon fills it
    scrollbag PREFIX [MAX]      snap the bag list row by row to its end
    dialog PREFIX [MAX] [KEY]   shoot every finished text page until the player is free
    expectvar VAR VALUE         stop unless VAR holds VALUE

Usage: r2ops.py <hns.py args>, e.g. with this folder as --tours:
    HNS_SAVES=... HNS_SRC=<tree of the ROM> python3 r2ops.py tour ROM OUT --tours DIR [--clip] --only RE
Tours here: r2_puzzle_kabuto, r2_puzzle_others, r2_berry, r2_lottery (start saves/r2fpb_postgame.sav,
a copy of ladder6_postgame.sav).
"""
import os
import sys
HERE = os.path.dirname(os.path.abspath(__file__))
EMU = os.path.abspath(os.path.join(HERE, "..", ".."))
sys.path.insert(0, os.path.join(EMU, "scripts", "r1_npc_services"))     # svc.py
sys.path.insert(0, EMU)
import hns                      # noqa: E402
import svc                      # noqa: E402,F401  (registers its ops)
from hns import script_op, HnsError   # noqa: E402

SB1_BERRY_TREES = 0x1DBC        # SB1.vars 0x1ABC + 0x200 vars + 0x100 gameStats (global.h comments are stale)
BOXMON_SIZE = 0x50
MON_SIZE = 0x64


def tree_addr(emu, i):
    return emu.sb1() + SB1_BERRY_TREES + 8 * i


def tree_read(emu, i):
    b = emu.read(tree_addr(emu, i), 8)
    return dict(berry=b[0] & 0x7F, stage=b[1] & 7, minutes=(b[2] | b[3] << 8) & 0x3FFF,
                yield_=b[4] & 0x1F, stop=(b[1] >> 7) & 1, raw=b.hex())


@script_op("berryshow")
def _op_berryshow(emu, f, path):
    i = emu.const(f[1]) if not f[1].isdigit() else int(f[1])
    print("berry tree %d: %s" % (i, tree_read(emu, i)))


@script_op("berry")
def _op_berry(emu, f, path):
    i = emu.const(f[1]) if not f[1].isdigit() else int(f[1])
    field, val = f[2], int(f[3], 0)
    a = tree_addr(emu, i)
    b = bytearray(emu.read(a, 8))
    if field == "berry":
        b[0] = (b[0] & 0x80) | (val & 0x7F)
    elif field == "stage":
        b[1] = (b[1] & ~7 & 0xFF) | (val & 7)
    elif field == "yield":
        b[4] = (b[4] & 0xE0) | (val & 0x1F)
    elif field == "minutes":
        m = (b[2] | b[3] << 8) & 0xC000 | (val & 0x3FFF)
        b[2], b[3] = m & 0xFF, m >> 8
    else:
        raise HnsError("berry: unknown field %s" % field)
    for k in range(8):
        emu.w8(a + k, b[k])
    print("berry tree %d %s=%d -> %s" % (i, field, val, tree_read(emu, i)))


@script_op("settid")
def _op_settid(emu, f, path):
    a = emu.sb2() + hns.OFF["SB2.playerTrainerId"]
    old = emu.r16(a)
    emu.w16(a, int(f[1], 16))
    print("player TID %05d -> %05d" % (old, emu.r16(a)))


@script_op("scrollbag")
def _op_scrollbag(emu, f, path):
    """scrollbag PREFIX [MAX]: snap PREFIX_01, press DOWN, snap ... until the bag list position
    of the current pocket (gBagPosition.cursorPosition/scrollPosition[pocket], include/item_menu.h:
    59-67, 6 pockets) stops changing (the last row)."""
    prefix, mx = f[1], int(f[2]) if len(f) > 2 else 80
    bp = emu.sym("gBagPosition")
    n = 0
    while n < mx:
        emu.wait_quiet(900)
        emu.frames(2)
        n += 1
        svc._shot(emu, "%s_%02d" % (prefix, n))
        pk = emu.r8(bp + 5)
        before = (emu.r16(bp + 8 + 2 * pk), emu.r16(bp + 20 + 2 * pk))
        emu.tap("DOWN", 6)
        emu.wait_quiet(900)
        if (emu.r16(bp + 8 + 2 * pk), emu.r16(bp + 20 + 2 * pk)) == before:
            break
    print("scrollbag %s: %d shot(s) @%d" % (prefix, n, emu.sync()))


@script_op("expectvar")
def _op_expectvar(emu, f, path):
    """expectvar VAR VALUE: stop unless the save-block var VAR (a VAR_* name) holds VALUE."""
    got = emu.get_var(emu.const(f[1]))
    if got != int(f[2], 0):
        raise HnsError("expectvar %s: %d, wanted %s" % (f[1], got, f[2]))
    print("expectvar %s = %d ok" % (f[1], got))


@script_op("dialog")
def _op_dialog(emu, f, path):
    """dialog PREFIX [MAX] [KEY]: like svc.py textwatch, but ends when the player is free again
    (or MAX frames). Shoots PREFIX_NN whenever a text printer has just finished (pages that do
    not wait for a key too) and whenever a box waits for a key, then taps KEY (default A)."""
    prefix, maxf = f[1], int(f[2]) if len(f) > 2 else 3000
    key = f[3] if len(f) > 3 else "A"
    n, waited, prev, last = 0, 0, "idle", None
    free_for = 0
    while waited < maxf:
        st = emu.text_state()
        wk = emu.wants_key()
        if (prev == "busy" and st != "busy") or wk:
            emu.frames(3)
            n += 1
            p = svc._shot(emu, "%s_%02d" % (prefix, n))
            data = open(p, "rb").read() if os.path.exists(p) else None
            if data is not None and data == last:
                os.remove(p)
                emu.shots = emu.shots[:-1]
                n -= 1
            last = data
            if wk and key != "-":
                emu.tap(key, 0)
                emu.wait_until(lambda: not emu.wants_key(), 120, "text to take the key", step=1)
            st = emu.text_state()
        prev = st
        if st == "idle" and emu.controllable():
            free_for += 2
            if free_for > 20:
                break
        else:
            free_for = 0
        emu.frames(2)
        waited += 2
    print("dialog %s: %d shot(s), %d frames @%d" % (prefix, n, waited, emu.sync()))


@script_op("clearberries")
def _op_clearberries(emu, f, path):
    """clearberries: empty the Berries pocket (every slot of gBagPockets[POCKET_BERRIES=4] set to
    0; struct BagPocket {ItemSlot *itemSlots; u16 capacity:10, id:6}, include/item.h:89-94).
    The slot size is measured from the gap to the next array (medicine, include/global.h:1174-1188)."""
    bp = emu.sym("gBagPockets")
    ber, med = emu.r32(bp + 4 * 8), emu.r32(bp + 1 * 8)      # POCKET_MEDICINE = 1
    cap = emu.r16(bp + 4 * 8 + 4) & 0x3FF
    size = (med - ber) // cap
    if size not in (4, 8) or (med - ber) % cap:
        raise HnsError("clearberries: berries %08X medicine %08X capacity %d" % (ber, med, cap))
    for k in range(0, cap * size, 4):
        emu.w32(ber + k, 0)
    print("clearberries: %d slots of %d bytes at %08X" % (cap, size, ber))


@script_op("zeromon")
def _op_zeromon(emu, f, path):
    """zeromon SLOT: ZeroMonData on gPlayerParty[SLOT] (all 100 bytes 0 = SPECIES_NONE), so a
    later givemon fills that slot instead of going to the PC."""
    a = emu.sym("gPlayerParty") + MON_SIZE * int(f[1])
    for k in range(0, MON_SIZE, 4):
        emu.w32(a + k, 0)
    print("zeromon %s" % f[1])


@script_op("probe")
def _op_probe(emu, f, path):
    out = []
    for fl in ("FLAG_COMPLETED_KABUTO_PUZZLE", "FLAG_COMPLETED_OMANYTE_PUZZLE",
               "FLAG_COMPLETED_AERODACTYL_PUZZLE", "FLAG_COMPLETED_HOOH_PUZZLE",
               "FLAG_KABUTO_BROUGHT", "FLAG_OMANYTE_BROUGHT", "FLAG_AERODACTYL_BROUGHT",
               "FLAG_HOOH_BROUGHT", "FLAG_DAILY_PICKED_LOTO_TICKET", "FLAG_HIDE_GOLDENROD_NPCS",
               "FLAG_SYS_POKEDEX_GET"):
        try:
            out.append("%s=%d" % (fl, emu.get_flag(emu.const(fl))))
        except Exception as e:      # noqa: BLE001
            out.append("%s=? (%s)" % (fl, e))
    for v in ("VAR_POKELOT_RND1", "VAR_POKELOT_RND2", "VAR_POKELOT_PRIZE_ITEM",
              "VAR_POKELOT_PRIZE_PLACE", "VAR_RUINSOFALPH_STATE"):
        try:
            out.append("%s=%d" % (v, emu.get_var(emu.const(v))))
        except Exception as e:      # noqa: BLE001
            out.append("%s=? (%s)" % (v, e))
    tid = emu.r32(emu.sb2() + hns.OFF["SB2.playerTrainerId"])
    out.append("TID=%05d SID=%05d" % (tid & 0xFFFF, tid >> 16))
    party = emu.sym("gPlayerParty")
    n = emu.r8(emu.sym("gPlayerPartyCount"))
    for i in range(n):
        a = party + MON_SIZE * i
        out.append("party%d otid=%05d flags=%02x lvl=%d" % (i, emu.r32(a + 4) & 0xFFFF, emu.r8(a + 19), emu.r8(a + 0x54)))
    st = emu.r32(emu.sym("gPokemonStoragePtr"))
    cnt, ots = 0, {}
    for b in range(14):
        for s in range(30):
            a = st + 4 + (b * 30 + s) * BOXMON_SIZE
            fl = emu.r8(a + 19)
            if fl & 2 and not fl & 4:
                cnt += 1
                o = emu.r32(a + 4) & 0xFFFF
                ots.setdefault(o, []).append((b, s))
    out.append("box mons=%d otids=%s" % (cnt, {k: (len(v), v[0]) for k, v in ots.items()}))
    for line in out:
        print("probe: " + line)
    emu.log.extend("probe: " + line for line in out)


if __name__ == "__main__":
    sys.argv[0] = hns.__file__
    sys.exit(hns.main())
