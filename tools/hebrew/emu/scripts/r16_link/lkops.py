#!/usr/bin/env python3
"""hns.py plus the r14 link ops (scripts/r14_link/r14link.py: linkplayers, orw32, fieldwatch, setcb2, ...)
and one op for the link battle records window, for the round-16 link tours (tours/r16_link/*.txt).

    linkrecord SLOT NAME WINS LOSSES DRAWS
                            write one entry of gSaveBlock1Ptr->linkBattleRecords (struct LinkBattleRecord:
                            name[8] +0, trainerId +8, wins +0xA, losses +0xC, draws +0xE, 0x10 bytes;
                            the records at SaveBlock1 +0x3870, languages[] at +0x50 from there: measured
                            with offsetof() on the Hebrew and the English tree). NAME may be 'he:...,en:...'
                            (LK_LANG picks); the language byte is set to 2 (LANGUAGE_ENGLISH, the game
                            language of both builds).
    endlink OUTCOME         end a battle the way a cable battle ends: gBattleOutcome = OUTCOME (1 won, 2 lost,
                            3 drew), then gBattleMainFunc = SetLinkBattleEndCallbacks (src/battle_controller_
                            player.c; static, address from the ELF), so the next BattleMainCB1 runs it: with no
                            link (gReceivedRemoteLinkPlayers 0) it restores callback1, frees the window
                            buffers and sets callback2 = CB2_InitEndLinkBattle (src/battle_main.c), the VS
                            screen with the outcome words.

Run:  lkops.py tour ROM OUT --tours <emu>/tours/r16_link [--clip] [--only RE]
Env:  HNS_SRC (the tree the ROM was built from: charmap for the names), LK_LANG=he|en, HNS_MAX_FRAMES.
"""
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(HERE, "..", "r14_link"))
import r14link  # noqa: E402  (registers hns + the r14 link ops)
import hns  # noqa: E402
from hns import script_op  # noqa: E402

SB1_LINK_RECORDS = 0x3870
REC_SIZE, REC_LANG = 0x10, 0x50


@script_op("linkrecord")
def _op_linkrecord(emu, f, path):
    slot = int(f[1])
    name = r14link._name_bytes(r14link._pick(f[2]), 7)
    base = emu.sb1() + SB1_LINK_RECORDS
    rec = bytearray(REC_SIZE)
    rec[0:8] = name[:8]
    rec[8:10] = (0x1234 + slot).to_bytes(2, "little")
    for k, v in enumerate(f[3:6]):
        rec[0xA + 2 * k:0xC + 2 * k] = int(v).to_bytes(2, "little")
    r14link._write(emu, base + REC_SIZE * slot, bytes(rec))
    emu.w8(base + REC_LANG + slot, 2)
    print("linkrecord %d: %s %s @%d" % (slot, r14link._pick(f[2]), " ".join(f[3:6]), emu.sync()))


@script_op("endlink")
def _op_endlink(emu, f, path):
    emu.w8(emu.sym("gBattleOutcome"), int(f[1]))
    emu.w32(emu.sym("gBattleMainFunc"), emu.sym("SetLinkBattleEndCallbacks"))
    print("endlink %s @%d" % (f[1], emu.sync()))


if __name__ == "__main__":
    sys.argv[0] = hns.__file__
    sys.exit(hns.main())
