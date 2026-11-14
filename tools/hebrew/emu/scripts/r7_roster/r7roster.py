#!/usr/bin/env python3
"""Ops for the r7 Frontier trainer roster tours (tours/r7_roster/*.txt), on top of bfpops.py
(r2/r3 Frontier ops: drive, drivex, pick, saveyes, sb2w16, bwin ...).
Run:  r7roster.py tour ROM OUT --tours <emu>/tours/r7_roster [--clip] [--only RE]

    dometrainers ID...      write gSaveBlock2Ptr->frontier.domeTrainers[1..] (bitfield
                            trainerId:10, isEliminated:1, eliminatedAt:2, forfeited:3,
                            include/global.h:531-537; 4 bytes per entry under -mabi=apcs-gnu)
                            with these trainer ids, upper bits 0. Slot 0 (the player) is left
                            alone. Offset and stride were measured with probe/offsets.c against
                            both trees.
    domecards PREFIX        on the interactive tourney tree (Task_HandleTourneyTreeInput in
                            STATE_GET_INPUT, cursor on tree position 0): A opens the info card of
                            position 0, then DOWN steps through positions 1..15 (each card slides
                            in; Task_GetInfoCardInput, src/battle_dome.c:3776); a shot per card
                            (PREFIX_pNN), then B back to the tree. Writes one JSON line per card to
                            OUTDIR/<tour>/cards.jsonl (position, tourney slot, trainer id).
    domelist PREFIX         log the 16 tourney slots (trainer ids) to cards.jsonl, for the tree shot.
    oppname                 print TRAINER_BATTLE_PARAM.opponentA.
    frontierswitch          during a Frontier trainer battle, at the player's action menu: run
                            until the faint script reaches the BATTLE_TYPE_FRONTIER check in
                            BattleScript_FaintedMonTryChoose (data/battle_scripts_1.s:4048) and let
                            that one check fall through, so the 'about to send out' line
                            (STRINGID_ENEMYABOUTTOSWITCHPKMN) prints with the Frontier trainer's
                            class and name. A Frontier battle never shows this line in the game.
"""
import json
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(HERE, "..", ".."))                                # tools/hebrew/emu
sys.path.insert(0, os.path.join(HERE, "..", "r2_bfpass"))
import hns  # noqa: E402
import bfpops  # noqa: E402,F401  (registers the r2/r3 Frontier ops)
from hns import script_op, HnsError, TourTimeout, _arg  # noqa: E402

DOME_TRAINERS = 0xD24       # offsetof(struct SaveBlock2, frontier.domeTrainers), probe/offsets.c
DOME_STRIDE = 4             # sizeof(struct BattleDomeTrainer): -mabi=apcs-gnu pads it to 4
                            # (domeMonIds follows at 0xD64 = 0xD24 + 16 * 4)
STATE_GET_INPUT = 2         # Task_HandleTourneyTreeInput / Task_HandleInfoCardInput
TREE_IDS = [0, 8, 12, 4, 7, 15, 11, 3, 2, 10, 14, 6, 5, 13, 9, 1]   # sTourneyTreeTrainerIds


def _jsonl(emu, rec):
    out = os.path.join(emu.outdir, "cards.jsonl")
    with open(out, "a") as fh:
        fh.write(json.dumps(rec) + "\n")


def _slots(emu):
    base = emu.sb2() + DOME_TRAINERS
    return [emu.r16(base + DOME_STRIDE * i) & 0x3FF for i in range(16)]


@script_op("dometrainers")
def _op_dometrainers(emu, f, path):
    ids = [int(x, 0) for x in f[1:]]
    if len(ids) > 15:
        raise HnsError("dometrainers: at most 15 ids (slots 1..15)")
    base = emu.sb2() + DOME_TRAINERS
    for i, tid in enumerate(ids):
        emu.w16(base + DOME_STRIDE * (i + 1), tid & 0x3FF)
    print("dometrainers %s -> %s" % (ids, _slots(emu)))


@script_op("domelist")
def _op_domelist(emu, f, path):
    _jsonl(emu, {"shot": f[1], "slots": _slots(emu)})


def _wait_state(emu, task, what, maxframes=900):
    emu.wait_until(lambda: any(d[0] == STATE_GET_INPUT for d in emu.task_data(task)), maxframes,
                   what, step=2)


@script_op("domecards")
def _op_domecards(emu, f, path):
    prefix = f[1]
    first = _arg(f, 2, 0)
    tree = "Task_HandleTourneyTreeInput"
    card = "Task_HandleInfoCardInput"
    _wait_state(emu, tree, "the tourney tree's input state")
    d = emu.task_data(tree)[0]
    if d[1] != 0:
        raise HnsError("domecards: the tree cursor is on %d, not 0" % d[1])
    slots = _slots(emu)
    emu.tap("A", 4)
    _wait_state(emu, card, "the info card's input state")
    for pos in range(16):
        if pos:
            emu.tap("DOWN", 4)
            emu.wait_until(lambda: any(x[0] == STATE_GET_INPUT for x in emu.task_data(card)), 900,
                           "the next info card", step=2)
        emu.wait_quiet(300)
        name = "%s_p%02d" % (prefix, pos)
        tpos = emu.task_data(tree)[0][1]
        tid = TREE_IDS[tpos]
        if pos >= first:
            emu.snap(name)
            emu.shots = getattr(emu, "shots", []) + [name]
            _jsonl(emu, {"shot": name, "position": tpos, "slot": tid, "trainer": slots[tid]})
    emu.tap("B", 4)
    _wait_state(emu, tree, "the tourney tree after the card")
    emu.wait_quiet(300)
    print("domecards %s ok @%d" % (prefix, emu.sync()))


@script_op("oppname")
def _op_oppname(emu, f, path):
    print("opponentA = %d" % emu.r16(emu.sym("gTrainerBattleParameter") + 2))


MOVES_BY_TURN = ("MOVE_ICE_SHARD", "MOVE_BULLET_PUNCH", "MOVE_SHADOW_SNEAK")


@script_op("bwinr")
def _op_bwinr(emu, f, path):
    """bwinr PREFIX [MAXTURNS]: bffops `bwin` (foes at 1 HP every turn, the player's battler
    refilled, move 0 chosen), but move 0 cycles Ice Shard / Bullet Punch / Shadow Sneak by turn
    (all priority moves), so a disabled move or Wonder Guard cannot stall the battle."""
    prefix = f[1]
    maxturns = _arg(f, 2, 40)
    bm = emu.sym("gBattleMons")
    for turn in range(maxturns):
        if emu.cb2() != emu.sym("BattleMainCB2") and emu.task_active("Task_WeatherMain"):
            break
        n, end = hns.battle_walk(emu, "%s_t%02d" % (prefix, turn), (), 60, 6000,
                                 stop_tasks=("Task_WeatherMain",))
        print("  bwinr turn %d: %d page(s), %s" % (turn, n, end))
        if end.startswith("task:Task_WeatherMain") or end == "free":
            break
        if end.startswith("input:HandleInputChooseAction"):
            for bb in ((1, 3) if emu.r8(emu.sym("gBattlersCount")) > 2 else (1,)):
                if emu.r16(bm + 0x88 * bb + 0x2A):
                    emu.w16(bm + 0x88 * bb + 0x2A, 1)
            emu.w16(bm + 0x2A, emu.r16(bm + 0x2E))
            emu.w16(bm + 0x0C, emu.const(MOVES_BY_TURN[turn % len(MOVES_BY_TURN)]))
            if emu.r8(bm + 0x25) == 0:
                emu.w8(bm + 0x25, 10)
            hns.wait_battle_input(emu, "HandleInputChooseAction", battler=0)
            hns.battle_cursor(emu, "gActionSelectionCursor", 0, battler=0)
            emu.tap("A", 4)
            hns.wait_battle_input(emu, "HandleInputChooseMove", battler=0)
            hns.battle_cursor(emu, "gMoveSelectionCursor", 0, battler=0)
            emu.tap("A", 4)
        elif end.startswith("prompt:"):
            emu.tap("B", 4)
        elif end.startswith("task:Task_HandleChooseMonInput"):
            # the player's battler fainted: send out the first party slot that can battle
            pm = emu.sym("gPartyMenu") + 9
            party = emu.sym("gPlayerParty")
            ok = [i for i in range(emu.r8(emu.sym("gPlayerPartyCount")))
                  if emu.r16(party + 0x64 * i + hns.BATTLE_OFF["Pokemon.hp"])]
            slot = ok[0] if ok else 1
            emu.wait_quiet(300)
            for _ in range(8):
                if emu.r8(pm) == slot:
                    break
                emu.tap("DOWN", 4)
                emu.wait_quiet(300)
            emu.tap("A", 4)
            emu.wait_until(lambda: emu.task_active("Task_HandleSelectionMenuInput"), 120,
                           "the party menu's action list", step=1)
            emu.wait_quiet(300)
            emu.tap("A", 4)
            emu.wait_quiet(300)
        else:
            emu.tap("A", 4)
    else:
        raise TourTimeout("bwinr %s: still in battle after %d turns" % (prefix, maxturns))
    print("bwinr %s ok @%d" % (prefix, emu.sync()))


@script_op("bwinsw")
def _op_bwinsw(emu, f, path):
    """bwinsw PREFIX: bwin, but the first KO goes through frontierswitch, so the 'about to send
    out' line and its yes/no prompt show (the prompt is answered NO by bwin)."""
    import bffops
    prefix = f[1]
    bm = emu.sym("gBattleMons")
    n, end = hns.battle_walk(emu, "%s_t00" % prefix, (), 60, 6000, stop_tasks=("Task_WeatherMain",))
    print("  bwinsw intro: %d page(s), %s" % (n, end))
    if not end.startswith("input:HandleInputChooseAction"):
        raise HnsError("bwinsw: no action menu after the intro (%s)" % end)
    emu.w16(bm + 0x88 * 1 + 0x2A, 1)
    emu.w16(bm + 0x2A, emu.r16(bm + 0x2E))
    emu.w16(bm + 0x0C, emu.const("MOVE_ICE_SHARD"))
    if emu.r8(bm + 0x25) == 0:
        emu.w8(bm + 0x25, 10)
    hns.wait_battle_input(emu, "HandleInputChooseAction", battler=0)
    hns.battle_cursor(emu, "gActionSelectionCursor", 0, battler=0)
    emu.tap("A", 4)
    hns.wait_battle_input(emu, "HandleInputChooseMove", battler=0)
    hns.battle_cursor(emu, "gMoveSelectionCursor", 0, battler=0)
    emu.tap("A", 4)
    _op_frontierswitch(emu, ["frontierswitch"], path)
    _op_bwinr(emu, ["bwinr", prefix + "_r"], path)


@script_op("frontierswitch")
def _op_frontierswitch(emu, f, path):
    label = emu.sym("BattleScript_FaintedMonTryChoose")
    # openpartyscreen (6) + switchhandleorder (3) + 3 x jumpifword (14): the FRONTIER check
    addr = label + 6 + 3 + 14 * 3
    btf = emu.sym("gBattleTypeFlags")
    raw = emu.read(addr, 14)
    if int.from_bytes(raw[2:6], "little") != btf:
        raise HnsError("frontierswitch: no jumpifword on gBattleTypeFlags at %08x (%s)"
                       % (addr, raw.hex()))
    mask = int.from_bytes(raw[6:10], "little")
    cur = emu.sym("gBattlescriptCurrInstr")
    # A every 30 frames: the 'fainted' line waits for a key
    if not emu.wait32(cur, addr, _arg(f, 1, 6000), keys="A"):
        raise TourTimeout("frontierswitch: the faint script never reached the Frontier check")
    flags = emu.r32(btf)
    emu.w32(btf, flags & ~mask)
    emu.frames(1)
    emu.w32(btf, flags)
    print("frontierswitch: check skipped (pc %08x) @%d" % (emu.r32(cur), emu.sync()))


if __name__ == "__main__":
    sys.argv[0] = hns.__file__
    sys.exit(hns.main())
