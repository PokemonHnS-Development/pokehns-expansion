#!/usr/bin/env python3
"""hns.py plus the ops the r6 gift Pokemon / egg / fossil revival tours use (tours/r6_gifts/*.txt):
everything scripts/r6_league/r6league.py registers (through r5leg.py: bwin, bcatch, scene, stepto,
approach, closeall, pick, ss / sl, objs ...; sceneto, pickd, periodic), scripts/r5_npcsvc/npcsvc.py
(fillboxes, restoreboxes, and through r5lat.py: fieldwatch, partyinfo, flags), plus:

    partylimit N            the party-limit challenge: GetMaxPartySize() = 6 - N
                            (challengeSettings.tx_Challenges_PartyLimit, bits 4-6 of the byte at
                            gSaveBlock3Ptr + 0x16, as IsPartyLimitChallengeActive reads it in both
                            the Hebrew and the English ELF)
    dropitem ITEM           remove every ITEM from the bag (removeitem 1 until checkitem is FALSE),
                            so a fossil chooser does not open when the tour wants one fossil only
    itemcount ITEM...       print 1 or 0 for each ITEM: does the bag hold one (checkitem, read-only)

Run:  r6gifts.py tour ROM OUT --tours <emu>/tours/r6_gifts [--clip] [--only RE]
"""
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
EMU = os.path.dirname(os.path.dirname(HERE))
sys.path.insert(0, EMU)
sys.path.insert(0, os.path.join(EMU, "scripts", "r6_league"))
sys.path.insert(0, os.path.join(EMU, "scripts", "r5_npcsvc"))
import hns  # noqa: E402
import r6league  # noqa: E402,F401  (r5leg + sceneto / pickd / periodic)
import r5leg  # noqa: E402
import npcsvc  # noqa: E402,F401  (fillboxes / restoreboxes; r5lat fieldwatch / partyinfo / flags)
from hns import script_op, HnsError  # noqa: E402

hns.SCRIPT_OPS["warpto"] = r5leg._HNS_WARPTO      # MAP_* names, whatever the imports above set

SB3_PARTYLIMIT, PARTYLIMIT_SHIFT, PARTYLIMIT_MASK = 0x16, 4, 0x70


@script_op("partylimit")
def _op_partylimit(emu, f, path):
    n = int(f[1])
    if not 0 <= n <= 5:
        raise HnsError("partylimit: N must be 0..5")
    a = emu.r32(emu.sym("gSaveBlock3Ptr")) + SB3_PARTYLIMIT
    v = (emu.r8(a) & ~PARTYLIMIT_MASK & 0xFF) | (n << PARTYLIMIT_SHIFT)
    emu.w8(a, v)
    if (emu.r8(a) & PARTYLIMIT_MASK) >> PARTYLIMIT_SHIFT != n:
        raise HnsError("partylimit: the byte did not read back")
    print("partylimit %d: max party %d @%d" % (n, 6 - n, emu.sync()))


def _has(emu, item):
    hns.event_run(emu, "setvar VAR_RESULT, 0\ncheckitem %s\ncopyvar VAR_TEMP_F, VAR_RESULT\nend\n" % item,
                  "has")
    return emu.get_var(emu.const("VAR_TEMP_F"))


@script_op("dropitem")
def _op_dropitem(emu, f, path):
    item = f[1]
    n = 0
    while _has(emu, item):
        hns.event_run(emu, "removeitem %s\nend\n" % item, "drop")
        n += 1
        if n > 999:
            raise HnsError("dropitem: %s does not go away" % item)
    print("dropitem %s: %d removed @%d" % (item, n, emu.sync()))


@script_op("itemcount")
def _op_itemcount(emu, f, path):
    print("itemcount " + " ".join("%s=%d" % (it, _has(emu, it)) for it in f[1:]))


if __name__ == "__main__":
    sys.argv[0] = hns.__file__
    sys.exit(hns.main())
