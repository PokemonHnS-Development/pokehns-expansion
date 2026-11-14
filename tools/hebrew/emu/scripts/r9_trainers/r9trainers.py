#!/usr/bin/env python3
"""r6trainers.py plus one op for the r9 field-trainer reruns: an opponent item use in a field
trainer battle (none of the field trainers carries battle items, so the item line
STRINGID_TRAINER1USEDITEM never shows in their battles on its own).

    itemuse ITEM [SLEEP]    for the next `trainer` op only: before the first turn of its first
                            battle, give the AI one ITEM (gBattleHistory->trainerItems[0], itemsNo 1)
                            and put the left foe to sleep for SLEEP turns (default 3), so the AI
                            cures it with the item (ShouldUseItem, EFFECT_ITEM_CURE_STATUS) and the
                            battle prints '<class> <name>: שימוש ב<item>!'.

Offsets (both ROMs, read from BattleAI_SetupItems: trainerItems at +72, itemsNo at +80,
sizeof 0x5C; BattlePokemon.status1 at +0x50, size 0x88).
Run:  r9trainers.py tour ROM OUT --tours <emu>/tours/r9_trainers [--clip] [--only RE]
"""
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(HERE, "..", "r6_trainers"))
import r6trainers  # noqa: E402  (registers hns + r5/r6 ops)
import hns  # noqa: E402
from hns import script_op  # noqa: E402

HIST_ITEMS = 72
HIST_NO = 80
BMON_SIZE = 0x88
BMON_STATUS1 = 0x50

_orig_walk = hns.battle_walk
MON_STATUS = 0x50       # struct Pokemon.status (Pokemon.hp 0x56 - 6), size 0x64


def _apply(emu, item, sleep):
    """The AI decides at the start of each turn, before the player's prompt, so the item and the
    sleep go in before the first turn: the history (set up in SetUpBattleVarsAndBirchZigzagoon),
    the first enemy party slot (copied into gBattleMons at the send-out) and gBattleMons[1]."""
    hist = emu.r32(emu.sym("gBattleHistory"))
    emu.w16(hist + HIST_ITEMS, item)
    emu.w8(hist + HIST_NO, 1)
    emu.w32(emu.sym("gEnemyParty") + MON_STATUS, sleep)
    bm = emu.sym("gBattleMons") + BMON_SIZE * 1
    if emu.r16(bm):
        emu.w32(bm + BMON_STATUS1, sleep)
    print("  itemuse: item %d, foe status %d (hist 0x%08x)" % (item, sleep, hist))


def _walk(emu, prefix, *a, **k):
    want = getattr(emu, "_r9_item", None)
    if want:
        _apply(emu, *want)
        emu._r9_item = None
    return _orig_walk(emu, prefix, *a, **k)


hns.battle_walk = _walk


@script_op("itemuse")
def _op_itemuse(emu, f, path):
    item = emu.const(f[1])
    sleep = int(f[2]) if len(f) > 2 else 3
    emu._r9_item = (item, sleep)


if __name__ == "__main__":
    sys.argv[0] = hns.__file__
    sys.exit(hns.main())
