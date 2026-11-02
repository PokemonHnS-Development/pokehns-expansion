#!/usr/bin/env python3
"""Ops for the r13 Frontier doubles tours (tours/r13_frontier_doubles/*.txt): the Battle Palace
double battles, Battle Tower doubles and multis with a lobby partner, Battle Factory doubles.
On top of r11tent.py (tstate, r7roster's bwinr / oppname, the r2/r3 Frontier ops drive / drivex /
pick / saveyes / bwin / blose / bpalace / bstall, r2sf's ss / sl, and r11sym's FILE:sym lookups
for a clip ELF without a linker map), r4ops.py (fids, ptalk, apprentice) and r5fops.py
(approachnpc, waitmap, snapat, driveleave, frontierinfo).
Run:  r13fd.py tour ROM OUT --tours <emu>/tours/r13_frontier_doubles [--clip] [--only RE]

struct BattlePokemon (include/pokemon.h:337), size 0x88: moves[4] 0x0C, pp[4] 0x25, hp 0x2A,
maxHP 0x2E (hns.BATTLE_OFF / bffops, measured with offsetof()), personality 0x4C (counted from
those: item 0x30, nickname[13] 0x32, ppBonuses 0x3F, otName[8] 0x40, experience 0x48; checked
live by `bmons`, which prints it next to the party's personality).

    palpins N0 N1 N2 N3     pin (hnsrun `pin`, rewritten before every frame) the four battlers'
                            moves to SPLASH x4 and their personality to nature Nb (0..24,
                            include/constants/pokemon.h NATURE_*), so nobody takes damage and
                            each battler's Palace lines follow a known nature (src/pokemon.c
                            gNaturesInfo .battlePalaceFlavorText: HARDY 0 eager for more,
                            LONELY 1 glint in the eyes, BRAVE 2 getting into position,
                            LAX 9 growling deeply). Splash is a TARGET_USER move (defense group,
                            src/battle_gfx_sfx_util.c:372), so a nature that picks attack or
                            support finds no move of that group and half the time prints
                            'seems incapable of using its power' (B_MSG_INCAPABLE_OF_POWER).
    palunpin                drop every pin
    bhalfall                set every live battler's hp to maxHP / 2: at the end of the turn
                            BattleTurnPassed runs BattleScript_PalacePrintFlavorText
                            (src/battle_main.c:4232, BS_PalaceFlavorText :13858) and each
                            battler at or under half hp prints its nature's flavor line once
    bsetmoves B MOVE...     write moves (MOVE_x names) into battler B's slots 0.. with 10 pp
    palwalk PREFIX PAGES    walk a Palace battle's messages (PREFIX_cNN_MM, as bpalace) for at
                            least PAGES pages without touching hp; stops early when it ends
    bmons                   print each battler's species, hp/maxHP, personality, nature and moves,
                            and the party's personalities (to check the 0x4C offset)
    palwin PREFIX           win a Palace battle without a KO on the player's side: one intro page
                            (PREFIX_i_01), then before every turn the foes get SPLASH x4 and
                            1 hp, the player's battlers full hp and four priority attacks
                            (Ice Shard, Bullet Punch, Shadow Sneak, Aqua Jet), then 12-page
                            chunks (PREFIX_cNN_MM) until the field runs again
    bwin2 PREFIX [MAXTURNS] win a double battle with an action menu (Tower, Factory, multis) and
                            no KO on the player's side: at each of the player's action menus
                            (battler 0 or 2) every live foe (1, 3) gets 1 hp and SPLASH x4, both
                            player battlers full hp, the choosing battler's move 0 becomes Ice
                            Shard (priority; a target prompt gets A); then FIGHT, move 0. In a
                            multi battle the partner (battler 2) is the AI's, so only battler 0
                            chooses. Shots PREFIX_tNN_MM as bffops.bwin.
    bwalk1 PREFIX           battle_walk exactly one page (PREFIX_01)
    snapq NAME              wait until the screen is quiet, then snap
"""
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(HERE, "..", "r11_tents"))
sys.path.insert(0, os.path.join(HERE, "..", "r4_battle_tower_multi_npc_partner"))
sys.path.insert(0, os.path.join(HERE, "..", "r5_factory"))
sys.path.insert(0, os.path.join(HERE, "..", "r2_bfpass"))
sys.path.insert(0, os.path.join(HERE, "..", ".."))                                # tools/hebrew/emu
import r11tent  # noqa: E402,F401  (r7roster + bfpops + bffops + r3bf + r2sf + r11sym)
import r4ops  # noqa: E402,F401  (fids, ptalk, apprentice, waitmap)
import r5fops  # noqa: E402,F401  (approachnpc, waitmap, snapat, driveleave, frontierinfo)
import bfpops  # noqa: E402
import r3bf  # noqa: E402
import hns  # noqa: E402
from hns import script_op, HnsError, TourTimeout, _arg  # noqa: E402

BM_SIZE, BM_MOVES, BM_PP, BM_HP, BM_MAXHP, BM_PERS = 0x88, 0x0C, 0x25, 0x2A, 0x2E, 0x4C


def _bm(emu, b, off=0):
    return emu.sym("gBattleMons") + BM_SIZE * b + off


def _nbattlers(emu):
    return 4 if emu.r8(emu.sym("gBattlersCount")) > 2 else 2


@script_op("palpins")
def _op_palpins(emu, f, path):
    nat = [int(x, 0) for x in f[1:5]]
    splash = emu.const("MOVE_SPLASH")
    mv = (splash & 0xFF, splash >> 8) * 4
    for b in range(4):
        emu.send("pin %08x %s" % (_bm(emu, b, BM_MOVES), "".join("%02x" % x for x in mv)))
        emu.send("pin %08x %s" % (_bm(emu, b, BM_PERS), (nat[b]).to_bytes(4, "little").hex()))
    print("palpins natures %s @%d" % (nat, emu.sync()))


@script_op("palunpin")
def _op_palunpin(emu, f, path):
    emu.send("unpin")
    print("palunpin @%d" % emu.sync())


@script_op("bhalfall")
def _op_bhalfall(emu, f, path):
    out = []
    for b in range(_nbattlers(emu)):
        hp, mx = emu.r16(_bm(emu, b, BM_HP)), emu.r16(_bm(emu, b, BM_MAXHP))
        if hp:
            emu.w16(_bm(emu, b, BM_HP), max(1, mx // 2))
            out.append("%d:%d/%d" % (b, max(1, mx // 2), mx))
    print("bhalfall %s @%d" % (" ".join(out), emu.sync()))


@script_op("bsetmoves")
def _op_bsetmoves(emu, f, path):
    b = int(f[1])
    for i, m in enumerate(f[2:6]):
        emu.w16(_bm(emu, b, BM_MOVES + 2 * i), emu.const(m))
        emu.w8(_bm(emu, b, BM_PP + i), 10)
    print("bsetmoves %d %s @%d" % (b, " ".join(f[2:]), emu.sync()))


@script_op("bmons")
def _op_bmons(emu, f, path):
    for b in range(_nbattlers(emu)):
        a = _bm(emu, b)
        p = emu.r32(a + BM_PERS)
        print("  battler %d: species %d hp %d/%d pers %08x (nature %d) moves %s pp %s" % (
            b, emu.r16(a), emu.r16(a + BM_HP), emu.r16(a + BM_MAXHP), p, p % 25,
            [emu.r16(a + BM_MOVES + 2 * i) for i in range(4)],
            [emu.r8(a + BM_PP + i) for i in range(4)]))
    party = emu.sym("gPlayerParty")
    print("  party personalities %s" % ["%08x" % emu.r32(party + 0x64 * i) for i in range(6)])
    enemy = emu.sym("gEnemyParty")
    print("  enemy personalities %s @%d" % (["%08x" % emu.r32(enemy + 0x64 * i) for i in range(6)], emu.sync()))


@script_op("palwalk")
def _op_palwalk(emu, f, path):
    prefix, pages = f[1], int(f[2])
    bcb2 = emu.sym("BattleMainCB2")
    total = 0
    for chunk in range(40):
        if total >= pages:
            break
        if emu.cb2() != bcb2 and emu.task_active("Task_WeatherMain"):
            break
        n, end = hns.battle_walk(emu, "%s_c%02d" % (prefix, chunk), (), min(12, pages - total), 12000,
                                 stop_tasks=("Task_WeatherMain",))
        total += n
        print("  palwalk chunk %d: %d page(s), %s" % (chunk, n, end))
        if end.startswith("task:Task_WeatherMain") or end == "free":
            break
        if end.startswith("task:Task_HandleChooseMonInput"):
            bfpops.choose_alive(emu)
        elif end.startswith("input:") or end.startswith("prompt:"):
            emu.tap("A" if end.startswith("input:") else "B", 4)
    print("palwalk %s: %d page(s) @%d" % (prefix, total, emu.sync()))


WIN_MOVES = ("MOVE_ICE_SHARD", "MOVE_BULLET_PUNCH", "MOVE_SHADOW_SNEAK", "MOVE_AQUA_JET")


def _palwin_poke(emu):
    splash = emu.const("MOVE_SPLASH")
    nb = _nbattlers(emu)
    for b in range(nb):
        if not emu.r16(_bm(emu, b, BM_HP)):
            continue
        if b & 1:
            emu.w16(_bm(emu, b, BM_HP), 1)
            for i in range(4):
                emu.w16(_bm(emu, b, BM_MOVES + 2 * i), splash)
                emu.w8(_bm(emu, b, BM_PP + i), 10)
        else:
            emu.w16(_bm(emu, b, BM_HP), emu.r16(_bm(emu, b, BM_MAXHP)))
            for i, m in enumerate(WIN_MOVES):
                emu.w16(_bm(emu, b, BM_MOVES + 2 * i), emu.const(m))
                emu.w8(_bm(emu, b, BM_PP + i), 10)


@script_op("palwin")
def _op_palwin(emu, f, path):
    prefix = f[1]
    bcb2 = emu.sym("BattleMainCB2")
    n, end = hns.battle_walk(emu, prefix + "_i", (), 1, 6000, stop_tasks=("Task_WeatherMain",))
    total = n
    for chunk in range(40):
        if emu.cb2() != bcb2 and emu.task_active("Task_WeatherMain"):
            break
        if emu.cb2() == bcb2:
            _palwin_poke(emu)
        n, end = hns.battle_walk(emu, "%s_c%02d" % (prefix, chunk), (), 12, 12000,
                                 stop_tasks=("Task_WeatherMain",))
        total += n
        print("  palwin chunk %d: %d page(s), %s" % (chunk, n, end))
        if end.startswith("task:Task_WeatherMain") or end == "free":
            break
        if end.startswith("task:Task_HandleChooseMonInput"):
            raise HnsError("palwin %s: a player Pokemon fainted" % prefix)
        elif end.startswith("input:") or end.startswith("prompt:"):
            emu.tap("A" if end.startswith("input:") else "B", 4)
    else:
        raise TourTimeout("palwin %s: still in battle after 40 chunks" % prefix)
    print("palwin %s: %d page(s) @%d" % (prefix, total, emu.sync()))


def _replace_doubles(emu):
    """The battle party menu asks for a replacement in a double battle: menu slots 0 and 1 are
    the Pokemon on the field, so try slots 2..5 in turn (SHIFT), dismissing a refusal ('has no
    energy left'), until the menu closes."""
    p = emu.sym("gPartyMenu") + 9
    for slot in (2, 3, 4, 5):
        emu.wait_quiet(300)
        for _ in range(8):
            if emu.r8(p) == slot:
                break
            emu.tap("DOWN", 4)
            emu.wait_quiet(300)
        emu.tap("A", 4)
        try:
            emu.wait_until(lambda: emu.task_active("Task_HandleSelectionMenuInput"), 120,
                           "the party menu's action list", step=1)
        except HnsError:
            continue
        emu.wait_quiet(300)
        emu.tap("A", 4)
        emu.frames(30)
        emu.wait_quiet(300)
        if not emu.task_active("Task_HandleChooseMonInput") and not emu.task_active("Task_PrintAndWaitForText"):
            print("    replace: slot %d" % slot)
            return
        for _ in range(4):
            if emu.task_active("Task_HandleChooseMonInput") and not emu.task_active("Task_PrintAndWaitForText"):
                break
            emu.tap("A", 4)
            emu.wait_quiet(300)
    raise HnsError("replace: no party slot could be sent out")


@script_op("bwin2")
def _op_bwin2(emu, f, path):
    prefix = f[1]
    maxturns = _arg(f, 2, 40)
    bcb2 = emu.sym("BattleMainCB2")
    splash = emu.const("MOVE_SPLASH")
    shard = emu.const("MOVE_ICE_SHARD")
    for turn in range(maxturns):
        if emu.cb2() != bcb2 and emu.task_active("Task_WeatherMain"):
            break
        n, end = hns.battle_walk(emu, "%s_t%02d" % (prefix, turn), (), 60, 6000,
                                 stop_tasks=("Task_WeatherMain",))
        print("  bwin2 turn %d: %d page(s), %s" % (turn, n, end))
        if end.startswith("task:Task_WeatherMain") or end == "free":
            break
        if end.startswith("input:HandleInputChooseAction"):
            b = 2 if end.endswith("#2") else 0
            for bb in range(_nbattlers(emu)):
                if not emu.r16(_bm(emu, bb, BM_HP)):
                    continue
                if bb & 1:
                    emu.w16(_bm(emu, bb, BM_HP), 1)
                    for i in range(4):
                        emu.w16(_bm(emu, bb, BM_MOVES + 2 * i), splash)
                        emu.w8(_bm(emu, bb, BM_PP + i), 10)
                else:
                    emu.w16(_bm(emu, bb, BM_HP), emu.r16(_bm(emu, bb, BM_MAXHP)))
            emu.w16(_bm(emu, b, BM_MOVES), shard)
            if emu.r8(_bm(emu, b, BM_PP)) == 0:
                emu.w8(_bm(emu, b, BM_PP), 10)
            hns.wait_battle_input(emu, "HandleInputChooseAction", battler=b)
            hns.battle_cursor(emu, "gActionSelectionCursor", 0, battler=b)
            emu.tap("A", 4)
            hns.wait_battle_input(emu, "HandleInputChooseMove", battler=b)
            hns.battle_cursor(emu, "gMoveSelectionCursor", 0, battler=b)
            emu.tap("A", 4)
        elif end.startswith("input:"):
            emu.tap("A", 4)
        elif end.startswith("prompt:"):
            emu.tap("B", 4)
        elif end.startswith("task:Task_HandleChooseMonInput"):
            _replace_doubles(emu)
        else:
            emu.tap("A", 4)
    else:
        raise TourTimeout("bwin2 %s: still in battle after %d turns" % (prefix, maxturns))
    print("bwin2 %s ok @%d" % (prefix, emu.sync()))


@script_op("bfoe1")
def _op_bfoe1(emu, f, path):
    """bfoe1: every live foe gets 1 hp and SPLASH x4, the player's battlers full hp."""
    splash = emu.const("MOVE_SPLASH")
    for bb in range(_nbattlers(emu)):
        if not emu.r16(_bm(emu, bb, BM_HP)):
            continue
        if bb & 1:
            emu.w16(_bm(emu, bb, BM_HP), 1)
            for i in range(4):
                emu.w16(_bm(emu, bb, BM_MOVES + 2 * i), splash)
                emu.w8(_bm(emu, bb, BM_PP + i), 10)
        else:
            emu.w16(_bm(emu, bb, BM_HP), emu.r16(_bm(emu, bb, BM_MAXHP)))
    print("bfoe1 @%d" % emu.sync())


@script_op("bwalk1")
def _op_bwalk1(emu, f, path):
    n, end = hns.battle_walk(emu, f[1], (), 1, 6000, stop_tasks=("Task_WeatherMain",))
    print("bwalk1 %s: %d page(s), %s @%d" % (f[1], n, end, emu.sync()))


@script_op("snapq")
def _op_snapq(emu, f, path):
    emu.wait_quiet(600)
    r3bf._shot(emu, f[1])


if __name__ == "__main__":
    sys.argv[0] = hns.__file__
    sys.exit(hns.main())
