#!/usr/bin/env python3
"""hns.py plus the ops the r11 gym-leader-after-badge and PC mailbox tours use
(tours/r11_leaders/*.txt): everything from scripts/r10_bridges/r10travel.py (visit, signs, npcs,
drive, walkto, approach, scene, yesno, bwin ...) and the Easy Chat / party ops of
scripts/r2_help_windows_and_easy_chat/hwec.py (ecwait, ec, ecputword, ecbutton, partyact ...),
plus:

    pstate NAME ...         print flags (FLAG_*) and vars (VAR_*) of the live save
    setname TEXT            gSaveBlock2Ptr->playerName <- TEXT (Hebrew or Latin, `_` = space,
                            at most 7 letters), encoded with the tree's charmap.txt: the name a
                            player typed on the naming screen, so mail given afterwards carries it
    mails                   print the 16 gSaveBlock1Ptr->mail slots (item, sender, words)
    talkdir PREFIX DIR      face DIR, A, then `drive PREFIX` (r10travel: one shot per page,
                            B on a menu, the player free at the end)

Run:  r11lm.py tour ROM OUT --tours <emu>/tours/r11_leaders [--clip] [--only RE]
"""
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(HERE, "..", "r2_help_windows_and_easy_chat"))
sys.path.insert(0, os.path.join(HERE, "..", "r10_bridges"))
import hwec  # noqa: E402,F401  (Easy Chat + partyact + r2/r3 ops)
import r10travel  # noqa: E402,F401  (r6story / r6league / r5leg / r10 travel ops; its drive wins)
import hns  # noqa: E402
from hns import script_op, HnsError  # noqa: E402

TOOLS = os.path.normpath(os.path.join(HERE, "..", "..", ".."))
sys.path.insert(0, TOOLS)
import textwidth as tw  # noqa: E402

PLAYER_NAME_LENGTH = 7
MAIL_COUNT = 16
MAIL_SIZE = 36            # struct Mail (include/global.h): words[9], playerName[8], trainerId[4], species, itemId


def charmap(emu):
    cm = getattr(emu, "_r11_cm", None)
    if cm is None:
        cm = emu._r11_cm = tw.Charmap(os.path.join(hns.src_dir(emu.elf), "charmap.txt"))
    return cm


def encode(emu, text):
    cm = charmap(emu)
    out = b""
    for ch in text.replace("_", " "):
        if ch not in cm.chars:
            raise HnsError("setname: %r is not in charmap.txt" % ch)
        out += cm.chars[ch]
    return out


@script_op("pstate")
def _op_pstate(emu, f, path):
    vals = []
    for name in f[1:]:
        if name.startswith("VAR_"):
            vals.append("%s=%d" % (name, emu.get_var(emu.const(name))))
        else:
            vals.append("%s=%d" % (name, int(emu.get_flag(emu.const(name)))))
    print("pstate " + " ".join(vals))


@script_op("setname")
def _op_setname(emu, f, path):
    """setname TEXT [ALT]: ALT (a Latin name of the same length) is used on a ROM whose
    charmap.txt has no Hebrew letters (the English twin run)."""
    name = f[1]
    try:
        raw = encode(emu, name)
    except HnsError:
        if len(f) < 3:
            raise
        name = f[2]
        raw = encode(emu, name)
    f = [f[0], name]
    if len(raw) > PLAYER_NAME_LENGTH:
        raise HnsError("setname: %r is %d bytes" % (f[1], len(raw)))
    buf = raw + b"\xff" * (PLAYER_NAME_LENGTH + 1 - len(raw))
    base = emu.sb2() + hns.OFF["SB2.playerName"]
    for i, b in enumerate(buf):
        emu.w8(base + i, b)
    print("setname %s (%d letters) @%d" % (f[1], len(raw), emu.sync()))


def _mail_base(emu):
    """gSaveBlock1Ptr->mail: located by its layout (16 slots of 36 bytes whose itemId is 0 or a
    mail item), searched over the whole SaveBlock1 (include/global.h gives 0x2BE0 before the H&S fields)."""
    sb1 = emu.sb1()
    first = emu.const("ITEM_ORANGE_MAIL")
    last = emu.const("ITEM_RETRO_MAIL")
    blob = emu.read(sb1, 0x3D90)
    best = None
    for off in range(0, 0x3D90 - MAIL_COUNT * MAIL_SIZE, 4):
        ok, used = True, 0
        for i in range(MAIL_COUNT):
            s = off + i * MAIL_SIZE
            item = int.from_bytes(blob[s + 32:s + 34], "little")
            if item == 0:
                continue
            if not first <= item <= last:
                ok = False
                break
            used += 1
        if ok and used:
            names = [blob[off + i * MAIL_SIZE + 18:off + i * MAIL_SIZE + 26] for i in range(MAIL_COUNT)
                     if int.from_bytes(blob[off + i * MAIL_SIZE + 32:off + i * MAIL_SIZE + 34], "little")]
            if not all(0xFF in n for n in names):
                ok = False
        if ok and used and (best is None or used > best[1]):
            best = (off, used)
    if best is None:
        raise HnsError("mails: no mail array found (no mail in the save?)")
    return sb1 + best[0]


@script_op("mails")
def _op_mails(emu, f, path):
    cm = charmap(emu)
    base = _mail_base(emu)
    for i in range(MAIL_COUNT):
        raw = emu.read(base + i * MAIL_SIZE, MAIL_SIZE)
        item = int.from_bytes(raw[32:34], "little")
        if not item:
            continue
        name = cm.decode(raw[18:26])
        words = [int.from_bytes(raw[k:k + 2], "little") for k in range(0, 18, 2)]
        print("mail %2d item %d sender %r (%s) words %s" % (i, item, name, raw[18:26].hex(), words))
    print("mails @%d (base %08X)" % (emu.sync(), base))


@script_op("talkdir")
def _op_talkdir(emu, f, path):
    hns.SCRIPT_OPS["face"](emu, ["face", f[2]], path)
    emu.frames(6)
    emu.tap("A", 4)
    hns.SCRIPT_OPS["drive"](emu, ["drive", f[1]] + f[3:], path)


# ---------------------------------------------------------------------------- FILE:symbol on the clip ELF
# A static symbol is qualified by its object file through the linker map next to the ELF
# (hns.Elf.objfile). The clip build's ELF has no map, the normal build's (same tree, same link
# order) has one: a FILE:NAME on the clip ELF takes the record with the same rank by address.
_REC = hns.Elf._rec


def _rec_via_sibling(self, name):
    try:
        return _REC(self, name)
    except HnsError:
        if ":" not in name or os.path.exists(os.path.splitext(self.path)[0] + ".map"):
            raise
        sib_path = os.path.join(os.path.dirname(self.path), "pokehns.elf")
        if not os.path.exists(sib_path) or os.path.abspath(sib_path) == os.path.abspath(self.path):
            raise
        sib = getattr(self, "_r11_sibling", None)
        if sib is None:
            sib = self._r11_sibling = hns.Elf(sib_path)
        want = _REC(sib, name)
        bare = name.split(":", 1)[1]
        mine = sorted(self.byname.get(bare, []))
        theirs = sorted(sib.byname.get(bare, []))
        if len(mine) != len(theirs):
            raise
        return mine[theirs.index(want)]


hns.Elf._rec = _rec_via_sibling


if __name__ == "__main__":
    sys.argv[0] = hns.__file__
    sys.exit(hns.main())
