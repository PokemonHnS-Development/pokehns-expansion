#!/usr/bin/env python3
"""Ops for the r14 fix_a tours (tours/r14_fix_a/*.txt): the opponents' and the partner's withdraw
lines in a Battle Tower multi battle, and every Frontier results window with multi-digit records.
On top of r13fd.py (the Frontier ops: drive / drivex / pick / saveyes / bwin2 / fids / ptalk /
waitmap / bfrecords / tstate ...), plus the withdraw trigger of r11wd.py, copied here so the
Frontier ops are not mixed with the field-trainer ops r11wd.py loads.
Run:  r14a.py tour ROM OUT --tours <emu>/tours/r14_fix_a [--clip] [--only RE]

    aiswitch [TURNS] [all]  make the AI switch in the next battle through its own switching path:
                            on the first battle_walk of the battle (the intro, before the AI picks
                            its turn-1 action), gDynamicAiSwitchFunc (src/battle_ai_main.c, the
                            hook the `setdynamicswitchaifunc` script command sets) is pointed at
                            BattlerIsOpponent (`all`: BattlerHasAi, which also takes the in-game
                            partner). ShouldSwitch then returns TRUE for every such battler that
                            has a Pokemon to switch to (src/battle_ai_switch.c), so the turn
                            prints the withdraw line (STRINGID_RETURNMON, src/battle_message.c)
                            and the send-out line. The hook is cleared at the start of
                            battle_walk number TURNS+1 (default 1: only the turn-1 decision
                            switches); FreeRestoreBattleData clears it when the battle ends.
    wdlog                   print gBattleTypeFlags, opponentA/B and the hook (for the run log).
"""
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(HERE, "..", "r13_frontier_doubles"))
import r13fd  # noqa: E402,F401  (registers hns + the r2/r3/r4/r5/r7/r11/r13 Frontier ops)
import hns  # noqa: E402
from hns import script_op  # noqa: E402

_orig_walk = hns.battle_walk


def _walk(emu, prefix, *a, **k):
    arm = getattr(emu, "_r14_arm", None)
    if arm is not None and emu.cb2() == emu.sym("BattleMainCB2"):
        arm["calls"] += 1
        hook = emu.sym("gDynamicAiSwitchFunc")
        if arm["calls"] == 1:
            emu.w32(hook, emu.sym(arm["func"]) | 1)
            print("  aiswitch: gDynamicAiSwitchFunc = %s" % arm["func"])
        elif arm["calls"] == arm["turns"] + 1:
            emu.w32(hook, 0)
            emu._r14_arm = None
            print("  aiswitch: hook cleared")
    return _orig_walk(emu, prefix, *a, **k)


hns.battle_walk = _walk


@script_op("aiswitch")
def _op_aiswitch(emu, f, path):
    turns = 1
    func = "BattlerIsOpponent"
    for x in f[1:]:
        if x == "all":
            func = "BattlerHasAi"
        else:
            turns = int(x)
    emu._r14_arm = {"turns": turns, "func": func, "calls": 0}
    print("aiswitch armed: %s for %d turn(s)" % (func, turns))


@script_op("wdlog")
def _op_wdlog(emu, f, path):
    tbp = emu.sym("gTrainerBattleParameter")
    # packed struct (include/battle_setup.h): opponentA at +2, opponentB at +17 (unaligned)
    opp_b = emu.r8(tbp + 17) | emu.r8(tbp + 18) << 8
    print("wdlog: flags %08x opponentA %d opponentB %d hook %08x" % (
        emu.r32(emu.sym("gBattleTypeFlags")), emu.r16(tbp + 2), opp_b,
        emu.r32(emu.sym("gDynamicAiSwitchFunc"))))


if __name__ == "__main__":
    sys.argv[0] = hns.__file__
    sys.exit(hns.main())
