#!/usr/bin/env python3
"""Ops for the rival-naming tours (rv_*.txt in this folder): the police scene in Elm's lab, the
rival naming screen, the Name Rater's TV, a rival battle and Red at Mt. Silver with a typed
rival name. On top of bffops.py (bwin / drivex / sb2str), r3bf.py (drive / pick / vars) and the
r2 ops. Run:  rivalops.py tour ROM OUT --tours <this folder> [--clip] [--only RE]

    namecur COL ROW         the naming-screen cursor position the next `nametype` starts from
                            (visual column 0 = left, row 0 = top). A fresh naming screen starts
                            on alef (7 0) on a TEXT_RTL build, on A (0 0) on English.
    namehome                namecur 7 0 on a TEXT_RTL build, 0 0 otherwise
    nameprefill WHICH       write NAMES[WHICH] into the naming screen's text buffer (a name that
                            mixes Hebrew, Latin and digits); the next `nametype` key redraws it
    nametype PREFIX WHICH   type the name WHICH (rival / player, see NAMES: Hebrew on a
                            TEXT_RTL build, Latin otherwise) key by key from the tracked cursor,
                            checking sNamingScreen->textBuffer after every key, one shot per
                            letter (PREFIX_N). A full name moves the cursor to OK by itself.
    rivalname               print gSaveBlock2Ptr->rivalName and the player's name
    bwintera PREFIX MAXTURNS SPECIES[,SPECIES] [HOLD]
                            bwin, plus a shot of every action menu (PREFIX_tNN_menu). While the
                            foe in battle is one of SPECIES and has been held fewer than HOLD
                            (default 2) turns, the foe keeps its HP and the player's battler
                            has Splash as its only move at full HP, so the AI gets a turn and
                            sees no KO threat (it may Terastallize, src/battle_ai_util.c:5490+).
    partyswap A B           swap two player party slots (to choose the lead)
    enemyfaint SLOT [SLOT ...]   set gEnemyParty[SLOT].hp to 0 (in battle), so the AI can only
                            send out the slots left
"""
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(HERE, "..", ".."))                                # tools/hebrew/emu
sys.path.insert(0, os.path.join(HERE, "..", "r2_battle_frontier_facilities"))
sys.path.insert(0, os.path.join(HERE, "..", "r3_frontier"))
sys.path.insert(0, os.path.join(HERE, "..", "r2_safari_pokeblock_bug_contest"))
sys.path.insert(0, os.path.join(HERE, "..", "..", ".."))                           # tools/hebrew
import hns  # noqa: E402
import bffops  # noqa: E402,F401  (registers bwin / drivex / sb2str and the r3/r2 ops)
import r3bf  # noqa: E402
from hns import script_op, HnsError, _arg  # noqa: E402

# Names typed on the naming screen. Hebrew: seven letters that are all 7 px wide in the
# normal font (the widest a 7-letter name can be, 49 px); Latin: seven capitals (6 px each).
NAMES = {
    "rival": ("אבשמחתם", "MAXWELL"),
    "tv": ("סילבריה", "SILVERS"),
    "player": ("שמשבחתם", "KENNETH"),
    "mixpre": ("אב12CD", "AB12CD"),     # written into the buffer by nameprefill
    "mixlast": ("ג", "G"),              # then typed, so the screen redraws the whole name
}

# offsetof(struct SaveBlock2, rivalName): 0xF2C, found on both ROMs by `rivalname rival` after
# the police scene wrote the typed name (playerName is at +0).
SB2_RIVAL_OFF = 0xF2C

# Key positions (visual column, row) on the first keyboard page.
# Hebrew page (tours/naming_player.txt:3-6):
#   row 0: . ז ו ה ד ג ב א    row 1: , נ מ ל כ י ט ח
#   row 2: - ש ר ק צ פ ע ס    row 3: ' _ ץ ף ן ם ך ת
HE_ROWS = [".זוהדגבא", ",נמלכיטח", "-שרקצפעס", "'_ץףןםךת"]
# English upper-case page (pokehns-en src/naming_screen.c:305-310)
EN_ROWS = ["ABCDEF .", "GHIJKL ,", "MNOPQRS ", "TUVWXYZ "]

# struct NamingScreenData (src/naming_screen.c:160-189): textBuffer after three 0x800 tilemaps,
# state at +0x1E10 (hns.NAMING_STATE_OFF).
NAMING_TEXTBUF = 0x1800
SB2_RIVALNAME = None


def rtl(emu):
    return "sRtlCharClass" in emu.elf.byname


def naming_ptr(emu):
    try:
        return emu.r32(emu.sym("sNamingScreen"))
    except HnsError:
        return emu.r32(emu.sym("naming_screen:sNamingScreen"))


def keymap(emu):
    rows = HE_ROWS if rtl(emu) else EN_ROWS
    out = {}
    for r, row in enumerate(rows):
        for c, ch in enumerate(row):
            out.setdefault(ch, (c, r))
    return out


def wait_naming(emu, maxf=600):
    def ready():
        p = naming_ptr(emu)
        return p and emu.r8(p + hns.NAMING_STATE_OFF) == hns.NAMING_HANDLE_INPUT
    emu.wait_until(ready, maxf, "the naming screen to read input", step=2)
    emu.wait_quiet(600)


@script_op("nameprefill")
def _op_nameprefill(emu, f, path):
    """nameprefill WHICH: write NAMES[WHICH] into sNamingScreen->textBuffer (EOS-padded), for
    names that mix keyboard pages; the next typed key redraws the entry with it."""
    data = bffops.encode(NAMES[f[1]][0 if rtl(emu) else 1])
    base = naming_ptr(emu) + NAMING_TEXTBUF
    for i, b in enumerate((data + b"\xff" * 16)[:16]):
        emu.w8(base + i, b)
    print("nameprefill %s" % f[1])


@script_op("namecur")
def _op_namecur(emu, f, path):
    emu._ncur = (int(f[1]), int(f[2]))


@script_op("namehome")
def _op_namehome(emu, f, path):
    emu._ncur = (7, 0) if rtl(emu) else (0, 0)


@script_op("nametype")
def _op_nametype(emu, f, path):
    prefix, which = f[1], f[2]
    name = NAMES[which][0 if rtl(emu) else 1]
    km = keymap(emu)
    want = bffops.encode(name)
    c, r = getattr(emu, "_ncur", (7, 0) if rtl(emu) else (0, 0))
    start = bytes(emu.read(naming_ptr(emu) + NAMING_TEXTBUF, 16)).find(b"\xff")
    for i, ch in enumerate(name):
        tc, tr = km[ch]
        while r != tr:
            emu.tap("DOWN" if tr > r else "UP", 4)
            emu.wait_quiet(300)
            r += 1 if tr > r else -1
        while c != tc:
            emu.tap("RIGHT" if tc > c else "LEFT", 4)
            emu.wait_quiet(300)
            c += 1 if tc > c else -1
        emu.tap("A", 4)
        wait_naming(emu)
        p = naming_ptr(emu)
        buf = emu.read(p + NAMING_TEXTBUF, 16)
        if bytes(buf[start:start + i + 1]) != want[:i + 1]:
            raise HnsError("nametype %s: after %r the buffer is %s, wanted %s"
                           % (which, ch, bytes(buf[:start + i + 1]).hex(), want[:i + 1].hex()))
        r3bf._shot(emu, "%s_%d" % (prefix, i + 1))
    emu._ncur = (c, r)
    print("nametype %s %r ok @%d" % (which, name, emu.sync()))


def sb2_rivalname_off(emu):
    # gSaveBlock2Ptr->rivalName: offsetof(struct SaveBlock2, rivalName), found by looking for
    # the name NameRival just wrote. Measured once per run from the live save block.
    return getattr(emu, "_rival_off", None)


@script_op("rivalname")
def _op_rivalname(emu, f, path):
    sb2 = emu.sb2()
    cm = bffops.charmap()
    rev = {}
    for k, v in cm.chars.items():
        if len(v) == 1 and (v not in rev or k.isascii() or "\u05d0" <= k <= "\u05ea"):
            if v in rev and ("\u05d0" <= rev[v] <= "\u05ea" or rev[v].isascii()):
                continue
            rev[v] = k
    player = emu.read(sb2, 8)
    def dec(bs):
        out = ""
        for b in bs:
            if b == 0xFF:
                break
            out += rev.get(bytes([b]), "<%02X>" % b)
        return out
    blob = emu.read(sb2, 0x1000)
    print("rivalname: player %r" % dec(player))
    off = getattr(emu, "_rival_off", None)
    if len(f) > 1:
        want = bffops.encode(NAMES[f[1]][0 if rtl(emu) else 1] if f[1] in NAMES else f[1])
        pos = bytes(blob).find(want + b"\xff")
        if pos < 0:
            raise HnsError("rivalname: %r is not in SaveBlock2" % f[1])
        emu._rival_off = off = pos
    if off is not None:
        print("rivalname: SB2+0x%X %r" % (off, dec(blob[off:off + 8])))


@script_op("setname")
def _op_setname(emu, f, path):
    """setname rival|player WHICH: write NAMES[WHICH] (Hebrew on a TEXT_RTL build, Latin
    otherwise) into gSaveBlock2Ptr->rivalName / playerName, EOS-terminated, FF-padded to 8."""
    off = SB2_RIVAL_OFF if f[1] == "rival" else 0
    data = bffops.encode(NAMES[f[2]][0 if rtl(emu) else 1])
    data = (data + b"\xff" * 8)[:8]
    base = emu.sb2() + off
    for i, b in enumerate(data):
        emu.w8(base + i, b)
    print("setname %s %s" % (f[1], f[2]))


@script_op("enemyfaint")
def _op_enemyfaint(emu, f, path):
    party = emu.sym("gEnemyParty")
    for s in f[1:]:
        emu.w16(party + 0x64 * int(s) + hns.BATTLE_OFF["Pokemon.hp"], 0)
    print("enemyfaint %s" % " ".join(f[1:]))


@script_op("partyswap")
def _op_partyswap(emu, f, path):
    """partyswap A B: swap gPlayerParty[A] and [B] (whole 0x64-byte structs, in the field)."""
    a, b = int(f[1]), int(f[2])
    party = emu.sym("gPlayerParty")
    da, db = emu.read(party + 0x64 * a, 0x64), emu.read(party + 0x64 * b, 0x64)
    for base, data in ((party + 0x64 * a, db), (party + 0x64 * b, da)):
        for i in range(0, 0x64, 4):
            emu.w32(base + i, int.from_bytes(data[i:i + 4], "little"))
    print("partyswap %d %d" % (a, b))


@script_op("bwintera")
def _op_bwintera(emu, f, path):
    prefix = f[1]
    maxturns = _arg(f, 2, 40)
    watch = set(emu.const(s) for s in f[3].split(",")) if len(f) > 3 else set()
    hold = _arg(f, 4, 2)
    held = {}
    bcb2 = emu.sym("BattleMainCB2")
    bm = emu.sym("gBattleMons")
    shard = emu.const("MOVE_ICE_SHARD")
    splash = emu.const("MOVE_SPLASH")
    for turn in range(maxturns):
        if emu.cb2() != bcb2 and emu.task_active("Task_WeatherMain"):
            break
        n, end = hns.battle_walk(emu, "%s_t%02d" % (prefix, turn), (), 60, 6000,
                                 stop_tasks=("Task_WeatherMain",))
        print("  bwintera turn %d: %d page(s), %s" % (turn, n, end))
        if end.startswith("task:Task_WeatherMain") or end == "free":
            break
        if end.startswith("input:HandleInputChooseAction"):
            foe = emu.r16(bm + 0x88 * 1)
            hns.wait_battle_input(emu, "HandleInputChooseAction")
            r3bf._shot(emu, "%s_t%02d_menu" % (prefix, turn))
            keep = foe in watch and held.get(foe, 0) < hold
            if keep:
                held[foe] = held.get(foe, 0) + 1
                print("    hold foe species %d (turn %d of %d)" % (foe, held[foe], hold))
            elif emu.r16(bm + 0x88 * 1 + 0x2A):
                emu.w16(bm + 0x88 * 1 + 0x2A, 1)
            emu.w16(bm + 0x2A, emu.r16(bm + 0x2E))
            emu.w16(bm + 0x0C, splash if keep else shard)
            if keep:                  # no move the AI could count as a KO threat after a Tera
                for k in (1, 2, 3):
                    emu.w16(bm + 0x0C + 2 * k, 0)
            if emu.r8(bm + 0x25) == 0:
                emu.w8(bm + 0x25, 10)
            hns.battle_cursor(emu, "gActionSelectionCursor", 0)
            emu.tap("A", 4)
            hns.wait_battle_input(emu, "HandleInputChooseMove")
            hns.battle_cursor(emu, "gMoveSelectionCursor", 0)
            emu.tap("A", 4)
        elif end.startswith("input:"):
            emu.tap("A", 4)
        elif end.startswith("task:Task_HandleChooseMonInput"):
            p = emu.sym("gPartyMenu") + 9
            party = emu.sym("gPlayerParty")
            ok = [i for i in range(emu.r8(emu.sym("gPlayerPartyCount")))
                  if emu.r16(party + 0x64 * i + hns.BATTLE_OFF["Pokemon.hp"])]
            slot = ok[0] if ok else 1
            emu.wait_quiet(300)
            for _ in range(8):
                if emu.r8(p) == slot:
                    break
                emu.tap("DOWN", 4)
                emu.wait_quiet(300)
            emu.tap("A", 4)
            emu.wait_until(lambda: emu.task_active("Task_HandleSelectionMenuInput"), 120,
                           "the party menu's action list", step=1)
            emu.wait_quiet(300)
            emu.tap("A", 4)
            emu.wait_quiet(300)
            print("    switch: slot %d" % slot)
        elif end.startswith("prompt:"):
            emu.tap("B", 4)
        else:
            emu.tap("A", 4)
    else:
        raise hns.TourTimeout("bwintera %s: still in battle after %d turns" % (prefix, maxturns))
    print("bwintera %s ok @%d" % (prefix, emu.sync()))


if __name__ == "__main__":
    sys.argv[0] = hns.__file__
    sys.exit(hns.main())
