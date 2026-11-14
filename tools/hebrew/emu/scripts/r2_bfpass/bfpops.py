#!/usr/bin/env python3
"""Ops for the Frontier Pass / BP shop / remaining-facility tours (bfp_*.txt in this folder), on
top of bffops.py (sb2w16, bfrecords, saveyes, bwin, blose, drivex) and r3bf.py (drive, pick).
Run:  bfpops.py tour ROM OUT --tours <this folder> [--clip] [--only RE]

    passarea NAME     move the Frontier Pass cursor (a sprite moved by held D-pad keys) onto a
                      cursor area (MAP CARD RECORD CANCEL POINTS EARNED TOWER DOME PALACE ARENA
                      FACTORY PIKE PYRAMID): the sprite is put 2 px left of the area's centre
                      (sPassAreasLayout, src/frontier_pass.c:352) and RIGHT is held one frame,
                      so Task_HandleFrontierPassInput recomputes the area and prints its text.
    gamestat NAME N   set a game stat (GAME_STAT_*) to N (SetGameStat XORs with the save key).
"""
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(HERE, "..", ".."))                                # tools/hebrew/emu
sys.path.insert(0, os.path.join(HERE, "..", "r2_battle_frontier_facilities"))
sys.path.insert(0, os.path.join(HERE, "..", "r3_frontier"))
sys.path.insert(0, os.path.join(HERE, "..", "r2_safari_pokeblock_bug_contest"))
import hns  # noqa: E402
import bffops  # noqa: E402,F401  (registers sb2w16 / bwin / drivex and the r3 ops)
from hns import script_op, HnsError  # noqa: E402

# centre (x, y) of each cursor area = sPassAreasLayout {yStart, yEnd, xStart, xEnd}
PASS_AREAS = {
    "MAP": (176, 52), "CARD": (176, 108), "RECORD": (64, 91), "CANCEL": (196, 8),
    "POINTS": (64, 121), "EARNED": (64, 36),
    "TOWER": (28, 58), "DOME": (40, 74), "PALACE": (52, 58), "ARENA": (64, 74),
    "FACTORY": (76, 58), "PIKE": (88, 74), "PYRAMID": (100, 58),
}
# offsetof(struct SaveBlock1, gameStats): measured live on the release build and on English 2.0.6
# (an `incrementgamestat GAME_STAT_LINK_BATTLE_WINS` changed SB1+0x1D18 = 0x1CBC + 23 * 4); it is
# vars (0x1ABC, hns.OFF) + VARS_COUNT (0x100) * 2.
GAMESTATS_OFF = 0x1CBC
SPRITE_X = 0x20      # struct Sprite: s16 x, y at 0x20 / 0x22 (include/sprite.h)


@script_op("passarea")
def _op_passarea(emu, f, path):
    cx, cy = PASS_AREAS[f[1].upper()]
    gfx = emu.r32(emu.sym("sPassGfx"))
    if not gfx:
        raise HnsError("passarea: the Frontier Pass is not open")
    spr = emu.r32(gfx)                      # FrontierPassGfx.cursorSprite
    # GetCursorAreaFromCoords(sprite.x - 5, sprite.y + 5)
    emu.w16(spr + SPRITE_X, (cx + 5 - 2) & 0xFFFF)
    emu.w16(spr + SPRITE_X + 2, (cy - 5) & 0xFFFF)
    emu.frames(1, "RIGHT")
    emu.frames(4)
    emu.wait_quiet(300)
    print("passarea %s @%d" % (f[1], emu.sync()))


def game_stat(emu, name):
    """GAME_STAT_* from include/constants/game_stat.h of the tree under test (emu.const's
    header list does not include it)."""
    import re
    try:
        return int(name, 0)
    except ValueError:
        pass
    src = hns.src_dir(emu.elf)
    for line in open(os.path.join(src, "include", "constants", "game_stat.h")):
        m = re.match(r"#define\s+(\w+)\s+(\d+)", line)
        if m and m.group(1) == name:
            return int(m.group(2))
    raise HnsError("gamestat: %s not in include/constants/game_stat.h" % name)


@script_op("gamestat")
def _op_gamestat(emu, f, path):
    stat = game_stat(emu, f[1])
    val = int(f[2], 0)
    key = emu.r32(emu.sb2() + hns.OFF["SB2.encryptionKey"])
    emu.w32(emu.sb1() + GAMESTATS_OFF + 4 * stat, val ^ key)
    print("gamestat %s = %d @%d" % (f[1], val, emu.sync()))




@script_op("tapstate")
def _op_tapstate(emu, f, path):
    """tapstate TASK IDX VAL KEY [MAX]: TASK reads input while data[IDX] == VAL (a screen state
    machine such as Task_HandleInfoCardInput, state 2). Tap KEY, wait until the state leaves VAL
    (up to 30 frames; a key the screen ignores leaves it there), then until it is VAL again and
    the screen has settled."""
    task, idx, val, key = f[1], int(f[2]), emu.const(f[3]), f[4]
    limit = hns._arg(f, 5, 900)
    st = lambda: [d[idx] for d in emu.task_data(task)]
    emu.wait_until(lambda: val in st(), limit, "%s data[%d] == %d" % (task, idx, val), step=2)
    emu.wait_quiet(300)
    emu.tap(key, 0)
    left = False
    for _ in range(15):
        emu.frames(2)
        if val not in st():
            left = True
            break
    emu.wait_until(lambda: val in st(), limit, "%s data[%d] == %d" % (task, idx, val), step=2)
    emu.wait_quiet(600)
    print("tapstate %s %s (%s) @%d" % (task, key, "moved" if left else "no change", emu.sync()))


@script_op("bstall")
def _op_bstall(emu, f, path):
    """bstall PREFIX TURNS [MOVE]: let a battle run TURNS turns without a KO, for the Battle
    Arena judgment after three turns and the Battle Palace turns. Every turn: battle_walk
    (PREFIX_tNN_MM shots); at the player's action menu its battler is refilled to full HP and its
    first move becomes MOVE (default MOVE_SPLASH, which does nothing), and so do all four of the
    foe's moves (the AI can only pick MOVE), then FIGHT with move 0. In
    the Battle Palace the player picks no move (no action menu appears): the walk simply goes on.
    Same BattlePokemon offsets as bffops.bwin. Returns at the action menu after TURNS turns, or
    when the battle ends. `bstall PREFIX TURNS MOVE FRAMES EVERY` instead returns FRAMES frames
    after the last action, with a shot (PREFIX_burst_NNN) every EVERY frames in between: the
    Arena judgment screen is drawn while no message waits for a key."""
    prefix = f[1]
    turns = int(f[2])
    move = emu.const(f[3] if len(f) > 3 else "MOVE_SPLASH")
    burst = (int(f[4]), int(f[5])) if len(f) > 5 else None
    bcb2 = emu.sym("BattleMainCB2")
    bm = emu.sym("gBattleMons")
    done = 0
    for turn in range(turns * 3 + 6):
        if emu.cb2() != bcb2 and emu.task_active("Task_WeatherMain"):
            break
        n, end = hns.battle_walk(emu, "%s_t%02d" % (prefix, turn), (), 60, 9000,
                                 stop_tasks=("Task_WeatherMain",))
        print("  bstall turn %d: %d page(s), %s" % (turn, n, end))
        if end.startswith("task:Task_WeatherMain") or end == "free":
            break
        if end.startswith("input:HandleInputChooseAction"):
            if done >= turns:
                break
            b = 2 if end.endswith("#2") else 0
            emu.w16(bm + 0x88 * b + 0x2A, emu.r16(bm + 0x88 * b + 0x2E))
            emu.w16(bm + 0x88 * b + 0x0C, move)
            # the foe gets MOVE in all four slots, so nothing faints before the judgment
            for bb in ((1, 3) if emu.r8(emu.sym("gBattlersCount")) > 2 else (1,)):
                for i in range(4):
                    emu.w16(bm + 0x88 * bb + 0x0C + 2 * i, move)
                    if emu.r8(bm + 0x88 * bb + 0x25 + i) == 0:
                        emu.w8(bm + 0x88 * bb + 0x25 + i, 10)
            if emu.r8(bm + 0x88 * b + 0x25) == 0:
                emu.w8(bm + 0x88 * b + 0x25, 10)
            hns.wait_battle_input(emu, "HandleInputChooseAction", battler=b)
            hns.battle_cursor(emu, "gActionSelectionCursor", 0, battler=b)
            emu.tap("A", 4)
            hns.wait_battle_input(emu, "HandleInputChooseMove", battler=b)
            hns.battle_cursor(emu, "gMoveSelectionCursor", 0, battler=b)
            emu.tap("A", 4)
            done += 1
            if done == turns and burst:
                # the turn that ends in the Arena judgment: a shot every EVERY frames, a frame
                # that looks like the previous shot is dropped
                last, k = None, 0
                for _ in range(burst[0] // burst[1]):
                    emu.frames(burst[1])
                    name = "%s_burst_%03d" % (prefix, k + 1)
                    p = emu.shot(name)
                    data = open(p, "rb").read() if p and os.path.exists(p) else None
                    if data is not None and data == last:
                        os.remove(p)
                        continue
                    last = data
                    k += 1
                    emu.shots = getattr(emu, "shots", []) + [name]
                    if getattr(emu, "clip", None):
                        try:
                            emu.clip.poll(name)
                        except Exception:
                            pass
                print("  bstall burst: %d shot(s)" % k)
                break
        elif end.startswith("input:"):
            emu.tap("A", 4)
        elif end.startswith("prompt:"):
            emu.tap("B", 4)
        else:
            emu.tap("A", 4)
    print("bstall %s: %d turn(s) chosen @%d" % (prefix, done, emu.sync()))


def choose_alive(emu):
    """The battle party menu asks for a replacement: put the cursor on the first party slot
    that can battle, press A, then A on its first action (SHIFT/SEND OUT), as bffops.bwin does."""
    p = emu.sym("gPartyMenu") + 9
    party = emu.sym("gPlayerParty")
    ok = [i for i in range(emu.r8(emu.sym("gPlayerPartyCount")))
          if emu.r16(party + 0x64 * i + hns.BATTLE_OFF["Pokemon.hp"])]
    slot = ok[0] if ok else 1
    emu.wait_quiet(300)
    for _ in range(8):
        if emu.r8(p) == slot:
            break
        emu.tap("DOWN", 4)
        emu.wait_quiet(300)
    emu.tap("A", 4)
    emu.wait_until(lambda: emu.task_active("Task_HandleSelectionMenuInput"), 120,
                   "the party menu's action list", step=1)
    emu.wait_quiet(300)
    emu.tap("A", 4)
    emu.wait_quiet(300)
    print("    switch: slot %d" % slot)


@script_op("bpalace")
def _op_bpalace(emu, f, path):
    """bpalace PREFIX PAGES: a Battle Palace (or Verdanturf Tent) battle, where the Pokemon pick
    their own moves and no action menu appears. The first PAGES messages are walked as they come
    (PREFIX_cNN_MM shots: the Palace turn messages), then every foe battler is set to 1 HP and the
    player's to full, chunk by chunk, until the battle ends or the field runs again."""
    prefix, pages = f[1], int(f[2])
    bcb2 = emu.sym("BattleMainCB2")
    bm = emu.sym("gBattleMons")
    total = 0
    for chunk in range(40):
        if emu.cb2() != bcb2 and emu.task_active("Task_WeatherMain"):
            break
        n, end = hns.battle_walk(emu, "%s_c%02d" % (prefix, chunk), (), 12, 12000,
                                 stop_tasks=("Task_WeatherMain",))
        total += n
        print("  bpalace chunk %d: %d page(s), %s" % (chunk, n, end))
        if end.startswith("task:Task_WeatherMain") or end == "free":
            break
        if total >= pages and emu.cb2() == bcb2:
            for bb in ((1, 3) if emu.r8(emu.sym("gBattlersCount")) > 2 else (1,)):
                if emu.r16(bm + 0x88 * bb + 0x2A) > 1:
                    emu.w16(bm + 0x88 * bb + 0x2A, 1)
            for b in ((0, 2) if emu.r8(emu.sym("gBattlersCount")) > 2 else (0,)):
                if emu.r16(bm + 0x88 * b + 0x2A):
                    emu.w16(bm + 0x88 * b + 0x2A, emu.r16(bm + 0x88 * b + 0x2E))
        if end.startswith("task:Task_HandleChooseMonInput"):
            choose_alive(emu)
        elif end.startswith("input:") or end.startswith("prompt:"):
            emu.tap("A" if end.startswith("input:") else "B", 4)
    print("bpalace %s: %d page(s) @%d" % (prefix, total, emu.sync()))


if __name__ == "__main__":
    sys.argv[0] = hns.__file__
    sys.exit(hns.main())
