#!/usr/bin/env python3
"""Driver for the late-game play tours (tours/r28_align/pl*.txt): the post-game travel ops of
scripts/r10_postgame/r10pg.py (arrive, visit, converse, talkobj, sign, wild, hofwatch, periodicx and
every op module it loads) plus:

    signpick X Y PREFIX pick=R,R   read one sign as `sign` does, taking row R of each menu in turn
                                   (a rules board's topic list)

converse here also handles two screens the post-game reaches: a Frontier party pick (B asks to
cancel the challenge; the YES/NO is shot and answered YES) and the Easy Chat screen (shot, the word
group keyboard, the exit prompt, YES).

Run:  play_late.py tour ROM OUT --tours tools/hebrew/emu/tours/r28_align --only '^pl(0|1[0-7]|18_contest_lobby|19|20)' [--clip]
      (the contest tours pl18_contest and pl18_long: scripts/r16_contests/con16.py tour ROM OUT
      --tours tools/hebrew/emu/tours/r28_align --only '^pl18_(contest|long)$')
Env:  HNS_SRC=<the tree the ROM was built from>, HNS_SAVES=<saves with ladder6_postgame.sav>,
      HNS_MAX_FRAMES set. Pair the two runs by text page with align.py, then textalign.py tours.
"""
import os
import sys

EMU = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path.insert(0, EMU)
sys.path.insert(0, os.path.join(EMU, "scripts", "r10_postgame"))
import hns  # noqa: E402
import r10pg  # noqa: E402  (arrive, visit, converse, talkobj, sign, ...)
import hilltent_ops as ho  # noqa: E402
from hns import script_op  # noqa: E402


_ORIG_CONVERSE = r10pg.converse


def _party_cancel(emu, sh):
    """A party screen reading input (a Frontier party pick): shot it, B (which asks 'cancel the
    challenge?' there), shot the YES/NO, take YES. A party screen that B closes is left at once."""
    emu.wait_quiet(300)
    emu.frames(2)
    sh("party")
    emu.tap("B", 10)
    yn = "Task_HandleCancelChooseMonYesNoInput"
    for _ in range(90):
        if emu.cb2() != emu.sym("CB2_UpdatePartyMenu") or emu.task_active(yn):
            break
        emu.frames(4)
    if emu.cb2() == emu.sym("CB2_UpdatePartyMenu") and emu.task_active(yn):
        emu.wait_quiet(120)
        emu.frames(2)
        sh("party_yesno")
        emu.tap("A", 30)            # the cursor starts on YES: cancel the challenge


def _ec_wait(emu, mx=900):
    emu.wait_until(lambda: any(d[0] == 1 for d in emu.task_data("Task_EasyChatScreen")), mx,
                   "Task_EasyChatScreen to read input", step=1)
    emu.wait_quiet(mx)
    emu.frames(2)


def _ec_leave(emu, sh):
    """The Easy Chat screen reads input: shot it, A (the word group keyboard of the first slot),
    shot, B back; B (the exit prompt), shot, YES."""
    _ec_wait(emu)
    sh("ec")
    emu.tap("A", 0)
    emu.frames(2)
    _ec_wait(emu)
    sh("ec_kb")
    emu.tap("B", 0)
    emu.frames(2)
    _ec_wait(emu)
    emu.tap("B", 0)
    emu.frames(2)
    _ec_wait(emu)
    sh("ec_quit")
    emu.tap("UP", 6)
    emu.tap("A", 10)
    emu.wait_until(lambda: emu.cb2() != emu.sym("CB2_EasyChatScreen"), 900, "leaving Easy Chat")


def converse(emu, prefix, yes=False, maxf=60000, picks=None):
    """r10pg.converse, but a party screen that reads input is cancelled (_party_cancel) instead of
    being pressed B forever. Runs the original in slices: whenever it would sit on a party screen
    the screen is handled here and the original is entered again with the same shooter prefix."""
    party = emu.sym("CB2_UpdatePartyMenu")
    names_all = []
    sh = r10pg.Shooter(emu, prefix)
    orig_tap = emu.tap

    ecs = emu.sym("CB2_EasyChatScreen")

    class _Party(Exception):
        pass

    class _Ec(Exception):
        pass

    def tap(keys, idle=20):
        if keys == "B" and emu.cb2() == party and emu.task_active("Task_HandleChooseMonInput"):
            raise _Party()
        if keys == "B" and emu.cb2() == ecs:
            raise _Ec()
        return orig_tap(keys, idle)

    rounds = 0
    pk = list(picks or [])
    while True:
        rounds += 1
        emu.tap = tap
        try:
            end, names = _ORIG_CONVERSE(emu, "%s%s" % (prefix, "" if rounds == 1 else "_r%d" % rounds), yes, maxf, pk)
            return end, names_all + names
        except _Party:
            what = _party_cancel
        except _Ec:
            what = _ec_leave
        finally:
            emu.tap = orig_tap
        if rounds > 4:
            raise hns.HnsError("converse %s: party or Easy Chat screen again" % prefix)
        sh.prefix = prefix + "_r%d" % rounds
        what(emu, sh)
        names_all += sh.names


r10pg.converse = converse


def read_sign_picks(emu, sx, sy, prefix, picks):
    w, h, coll, behavior = ho.map_grid(emu)
    for (t, face) in [((sx, sy + 1), "UP"), ((sx + 1, sy), "LEFT"), ((sx - 1, sy), "RIGHT"), ((sx, sy - 1), "DOWN")]:
        if not (0 <= t[0] < w and 0 <= t[1] < h) or coll(*t):
            continue
        if emu.location()[1] != t:
            if r10pg._route(emu, t) is None or r10pg._walk(emu, t) != "reached":
                g, n, _, _, _ = r10pg.here(emu)
                try:
                    emu.warp(g, n, t[0], t[1])
                except hns.HnsError:
                    continue
        if r10pg._face_a(emu, face):
            return r10pg.converse(emu, prefix, picks=list(picks))[0]
    return "unreachable"


@script_op("signpick")
def _op_signpick(emu, f, path):
    sx, sy, prefix = int(f[1]), int(f[2]), f[3]
    picks = [int(x) for o in f[4:] if o.startswith("pick=") for x in o[5:].split(",")]
    how = read_sign_picks(emu, sx, sy, prefix, picks)
    print("signpick %d,%d %s: %s @%d" % (sx, sy, picks, how, emu.sync()))


if __name__ == "__main__":
    sys.argv[0] = hns.__file__
    sys.exit(hns.main())
