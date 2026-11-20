#!/usr/bin/env python3
"""Ops for the r11 withdraw tours (tours/r11_withdraw/*.txt), on top of r9trainers.py
(r6trainers: tbase, trainer MAP LOCAL; r6league / r5leg: bwin, scene, ...).
Run:  r11wd.py tour ROM OUT --tours <emu>/tours/r11_withdraw [--clip] [--only RE]

    aiswitch [TURNS] [all]  make the AI switch in the next battle, through its own switching path:
                            on the first battle_walk of the battle (the intro, before the AI picks
                            its turn-1 action), gDynamicAiSwitchFunc (src/battle_ai_main.c:54, the
                            hook the `setdynamicswitchaifunc` script command sets) is pointed at
                            BattlerIsOpponent (src/battle_controllers.c:78; `all`: BattlerHasAi,
                            which also takes the in-game partner). ShouldSwitch then returns TRUE
                            for every opponent that has a Pokemon to switch to
                            (src/battle_ai_switch.c:1333), ComputeBattlerDecisions sets its
                            shouldSwitch bit (src/battle_ai_main.c:406) and AI_TrySwitchOrUseItem
                            sends B_ACTION_SWITCH (:457), so the turn prints the withdraw line
                            (STRINGID_RETURNMON, src/battle_message.c:2532-2606) and the send-out
                            line. The hook is cleared at the start of battle_walk number TURNS+1
                            (default 1: only the turn-1 decision switches); FreeRestoreBattleData
                            clears it anyway when the battle ends (src/battle_main.c:1892).
    foehp PCT [BATTLER]     gBattleMons[BATTLER] (default 1) HP to PCT % of its max HP (at least 1),
                            for the player's come-back / go lines (hpthresholds2 / hpthresholds,
                            src/battle_script_commands.c:6981-7027).
    wdlog                   print gBattleTypeFlags, opponentA and the hook (for the run log).
"""
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(HERE, "..", "r9_trainers"))
sys.path.insert(0, os.path.join(HERE, "..", "r11_tents"))
import r9trainers  # noqa: E402,F401  (registers hns + r5/r6/r9 trainer ops)
import hns  # noqa: E402
import r11sym  # noqa: E402,F401  (FILE:sym lookups without a linker map)
from hns import script_op  # noqa: E402

BMON = 0x88
HP, MAXHP = 0x2A, 0x2E

_orig_walk = hns.battle_walk


def _walk(emu, prefix, *a, **k):
    arm = getattr(emu, "_r11_arm", None)
    if arm is not None and emu.cb2() == emu.sym("BattleMainCB2"):
        arm["calls"] += 1
        hook = emu.sym("gDynamicAiSwitchFunc")
        if arm["calls"] == 1:
            emu.w32(hook, emu.sym(arm["func"]) | 1)
            print("  aiswitch: gDynamicAiSwitchFunc = %s" % arm["func"])
        elif arm["calls"] == arm["turns"] + 1:
            emu.w32(hook, 0)
            emu._r11_arm = None
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
    emu._r11_arm = {"turns": turns, "func": func, "calls": 0}
    print("aiswitch armed: %s for %d turn(s)" % (func, turns))


@script_op("foehp")
def _op_foehp(emu, f, path):
    pct = int(f[1])
    b = int(f[2]) if len(f) > 2 else 1
    bm = emu.sym("gBattleMons") + BMON * b
    mx = emu.r16(bm + MAXHP)
    hp = max(1, mx * pct // 100)
    emu.w16(bm + HP, hp)
    print("foehp battler %d: %d/%d (%d%%)" % (b, hp, mx, pct))


@script_op("wdlog")
def _op_wdlog(emu, f, path):
    tbp = emu.sym("gTrainerBattleParameter")
    print("wdlog: flags %08x opponentA %d hook %08x" % (
        emu.r32(emu.sym("gBattleTypeFlags")), emu.r16(tbp + 2),
        emu.r32(emu.sym("gDynamicAiSwitchFunc"))))


if __name__ == "__main__":
    sys.argv[0] = hns.__file__
    sys.exit(hns.main())
