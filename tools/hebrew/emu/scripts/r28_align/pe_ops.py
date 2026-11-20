#!/usr/bin/env python3
"""hns.py plus the story-tour ops of scripts/r6_story_johto/r6story.py (scene, walkto, approach,
yesno, stepto, bwin ...) plus the ops the early-game play tours (tours/r28_align/pe*.txt) use:

    talkw LOCALID PREFIX [MAXPAGES] [TRIES]
                            approach the object and talk to it (hns.py talk), trying again
                            when it walked away before A was pressed (wandering NPCs)
    fight PREFIX SLOT [MAXTURNS]
                            fight the battle on screen with move SLOT every turn, as a player
                            would (no HP or move pokes): bwalk each turn (PREFIX_tNN_MM), a
                            shot of the action menu (PREFIX_tNN_act) and of the move menu
                            (PREFIX_tNN_fight); a yes/no prompt is shot (PREFIX_tNN_prompt)
                            and answered with B; ends when the player is free again.
    walkw X Y [FACE]        walkto, trying again (after 40 frames) while a wandering NPC blocks
                            every path
    walkfight X Y PREFIX [SLOT]
                            walkto X Y; whenever a script takes the player over on the way (a
                            trainer's sight, a coord trigger), walk its scene (PREFIX_kN_pre),
                            fight a battle it starts with move SLOT (default 0, PREFIX_kN) and walk
                            the scene after it (PREFIX_kN_post), then walk on
    scenea PREFIX [ROUNDS] [MAXF]
                            `scene`, but when nothing new happens for MAXF frames (default 600; a
                            PokeGear call's last page waits for A without a key-waiting printer)
                            shoot the screen (PREFIX_rN_wait) and press A, up to ROUNDS times
    pocket N                in the open bag, LEFT / RIGHT until gBagPosition.pocket (+5) is N,
                            waiting for the pocket switch to finish after each key
Run:  pe_ops.py tour ROM OUT --tours <emu>/tours/r28_align --only '^pe' [--clip]
      (set HNS_SRC to the ROM's source tree: the ELF of a release folder has no data/maps or include/)
"""
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
for _d in (os.path.join(HERE, "scripts", "r6_story_johto"),       # next to tools/hebrew/emu/
           os.path.join(HERE, "..", "r6_story_johto")):            # in tools/hebrew/emu/scripts/<dir>/
    if os.path.isdir(_d):
        sys.path.insert(0, _d)
import r6story  # noqa: E402,F401  (registers the story-tour ops on top of hns.py)
import hns  # noqa: E402
import hilltent_ops  # noqa: E402
from hns import script_op, HnsError, _arg  # noqa: E402

_APPROACH = hns.SCRIPT_OPS["approach"]

# The following Pokemon (object local id 254, OW_FOLLOWERS) walks behind the player and gives
# way: it is not an obstacle for walkto's path search.
_OBJECTS = hilltent_ops.objects
hilltent_ops.objects = lambda emu: [o for o in _OBJECTS(emu) if o[0] != 254]


def _shot(emu, name):
    emu.frames(2)
    emu.shot(name)
    emu.shots = getattr(emu, "shots", []) + [name]


@script_op("talkw")
def _op_talkw(emu, f, path):
    lid, prefix = f[1], f[2]
    maxpages, tries = _arg(f, 3, 40), _arg(f, 4, 8)
    for t in range(tries):
        try:
            _APPROACH(emu, ["approach", lid], path)
        except HnsError as e:
            print("talkw %s: %s" % (lid, e))
            emu.frames(30)
            continue
        n, how = emu.talk(prefix, maxpages, "A", ())
        if n:
            emu.shots = getattr(emu, "shots", []) + ["%s_%02d" % (prefix, i + 1) for i in range(n)]
            print("talkw %s %s: %d page(s), ended %s, try %d @%d" % (lid, prefix, n, how, t + 1, emu.sync()))
            return
        emu.frames(20)
    raise HnsError("talkw %s: no text after %d tries" % (lid, tries))


@script_op("fight")
def _op_fight(emu, f, path):
    prefix, slot = f[1], int(f[2])
    maxturns = _arg(f, 3, 30)
    for turn in range(maxturns):
        n, end = hns.battle_walk(emu, "%s_t%02d" % (prefix, turn), (), 60, 8000)
        print("  fight turn %d: %d page(s), %s" % (turn, n, end))
        if end == "free":
            print("fight %s: over after %d turn(s) @%d" % (prefix, turn, emu.sync()))
            return
        if end.startswith("input:HandleInputChooseAction"):
            hns.wait_battle_input(emu, "HandleInputChooseAction")
            _shot(emu, "%s_t%02d_act" % (prefix, turn))
            hns.battle_cursor(emu, "gActionSelectionCursor", 0)
            emu.tap("A", 4)
            hns.wait_battle_input(emu, "HandleInputChooseMove")
            hns.battle_cursor(emu, "gMoveSelectionCursor", slot)
            emu.wait_quiet(300)
            _shot(emu, "%s_t%02d_fight" % (prefix, turn))
            emu.tap("A", 4)
            continue
        if end.startswith("prompt:") or end.startswith("input:PlayerHandleYesNoInput"):
            _shot(emu, "%s_t%02d_prompt" % (prefix, turn))
            emu.tap("B", 4)
            continue
        if end.startswith("input:"):
            _shot(emu, "%s_t%02d_input" % (prefix, turn))
            emu.tap("A", 4)
            continue
        if end.startswith("task:"):
            _shot(emu, "%s_t%02d_task" % (prefix, turn))
            emu.tap("B", 4)
            continue
        raise HnsError("fight %s: stopped at %s" % (prefix, end))
    raise HnsError("fight %s: not over after %d turns" % (prefix, maxturns))


@script_op("walkw")
def _op_walkw(emu, f, path):
    for t in range(10):
        try:
            hilltent_ops._op_walkto(emu, f, path)
            return
        except HnsError as e:
            if "no path" not in str(e) and "occupied" not in str(e):
                raise
            print("walkw: %s; waiting" % e)
            emu.frames(40)
    raise HnsError("walkw %s %s: still blocked" % (f[1], f[2]))


@script_op("walkfight")
def _op_walkfight(emu, f, path):
    x, y, prefix = f[1], f[2], f[3]
    slot = _arg(f, 4, 0)
    scene = hns.SCRIPT_OPS["scene"]
    for k in range(8):
        emu._walk_end = "reached"
        _op_walkw(emu, ["walkw", x, y], path)
        if emu._walk_end != "taken":
            print("walkfight %s %s: reached after %d interruption(s) @%d" % (x, y, k, emu.sync()))
            return
        scene(emu, ["scene", "%s_k%d_pre" % (prefix, k), "30000"], path)
        if hns.in_battle(emu):
            hns.pin_rng(emu)
            _op_fight(emu, ["fight", "%s_k%d" % (prefix, k), str(slot)], path)
            hns.unpin_rng(emu)
            scene(emu, ["scene", "%s_k%d_post" % (prefix, k), "30000"], path)
    raise HnsError("walkfight %s %s: taken over too often" % (x, y))


@script_op("scenea")
def _op_scenea(emu, f, path):
    prefix = f[1]
    rounds, maxf = _arg(f, 2, 4), _arg(f, 3, 600)
    scene = hns.SCRIPT_OPS["scene"]
    for r in range(rounds):
        try:
            scene(emu, ["scene", "%s_r%d" % (prefix, r), str(maxf)], path)
            return
        except hns.TourTimeout:
            _shot(emu, "%s_r%d_wait" % (prefix, r))
            emu.tap("A", 4)
    raise HnsError("scenea %s: still running after %d rounds" % (prefix, rounds))


@script_op("pocket")
def _op_pocket(emu, f, path):
    want = int(f[1])
    addr = emu.sym("gBagPosition") + 5
    for _ in range(12):
        cur = emu.r8(addr)
        if cur == want:
            break
        emu.tap("RIGHT" if want > cur else "LEFT", 4)
        emu.wait_until(lambda: emu.r8(addr) != cur, 120, "the pocket to change", step=2)
        emu.wait_until(lambda: emu.task_active("Task_BagMenu_HandleInput"), 240, "the bag to read input", step=2)
        emu.wait_quiet(300)
    if emu.r8(addr) != want:
        raise HnsError("pocket: stayed %d, wanted %d" % (emu.r8(addr), want))
    emu.wait_quiet(300)
    emu.frames(8)
    print("pocket %d ok @%d" % (want, emu.sync()))


if __name__ == "__main__":
    sys.argv[0] = hns.__file__
    sys.exit(hns.main())
