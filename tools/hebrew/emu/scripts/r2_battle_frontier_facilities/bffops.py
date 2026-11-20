#!/usr/bin/env python3
"""Ops for the round-2 Battle Frontier facility tours (bf_*.txt in this folder), on top of
r3bf.py (drive / pick / vars and the r2 ops).
Run:  bff.py tour ROM OUT --tours <this folder> [--clip] [--only RE]

    sb2w16 HEXOFF V [V ...]   write u16 values (decimal) from gSaveBlock2Ptr+OFF on
    sb2w32 HEXOFF V           write one u32 (decimal or 0x..) at gSaveBlock2Ptr+OFF
    sb2str HEXOFF MAXLEN TEXT write TEXT (charmap-encoded, '_' = space, FF-terminated and
                              FF-padded to MAXLEN bytes) at gSaveBlock2Ptr+OFF
    bfrecords                 fill every facility's streak records, the Ranking Hall 1P/2P
                              records and the Battle Points with distinct multi-digit values
                              (offsets measured with offsetof() on this tree: see FRONTIER)
"""
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(HERE, "..", ".."))                                # tools/hebrew/emu
sys.path.insert(0, os.path.join(HERE, "..", "r3_frontier"))
sys.path.insert(0, os.path.join(HERE, "..", "r2_safari_pokeblock_bug_contest"))
sys.path.insert(0, os.path.join(HERE, "..", "..", ".."))                           # tools/hebrew
import hns  # noqa: E402
import r3bf  # noqa: E402,F401  (registers drive / pick / vars and the r2 ops)
from hns import script_op, HnsError, _arg  # noqa: E402

# offsetof(struct SaveBlock2, ...) measured with an offsetof() probe compiled against
# include/global.h of the release tree and of English 2.0.6 (the same in both).
FRONTIER = {
    "hallRecords1P": 0x21C, "hallRecords2P": 0x57C, "RankingHall1P.size": 0x10, "RankingHall2P.size": 0x1C,
    "winStreakActiveFlags": 0xCDC, "towerWinStreaks": 0xCE0, "towerRecordWinStreaks": 0xCF0,
    "domeWinStreaks": 0xD0C, "domeRecordWinStreaks": 0xD14, "domeTotalChampionships": 0xD1C,
    "palaceWinStreaks": 0xDC8, "palaceRecordWinStreaks": 0xDD0,
    "arenaWinStreaks": 0xDDA, "arenaRecordStreaks": 0xDDE,
    "factoryWinStreaks": 0xDE2, "factoryRecordWinStreaks": 0xDEA,
    "factoryRentsCount": 0xDF2, "factoryRecordRentsCount": 0xDFA,
    "pikeWinStreaks": 0xE04, "pikeRecordStreaks": 0xE08, "pikeTotalStreaks": 0xE0C,
    "pyramidWinStreaks": 0xE1A, "pyramidRecordStreaks": 0xE1E,
    "battlePoints": 0xEB8, "cardBattlePoints": 0xEBA, "curChallengeBattleNum": 0xCB2,
}

_CHARMAP = None


def charmap():
    global _CHARMAP
    if _CHARMAP is None:
        import textwidth as tw
        # always the Hebrew charmap (tools/hebrew's tree): the same bytes go into the save on
        # both ROMs, and Latin letters have the same codes in both
        _CHARMAP = tw.Charmap(os.path.join(tw.FONTS_TREE, "charmap.txt"))
    return _CHARMAP


def encode(text):
    cm = charmap()
    out = b""
    for ch in text.replace("_", " "):
        if ch not in cm.chars:
            raise HnsError("sb2str: %r is not in the charmap" % ch)
        out += cm.chars[ch]
    return out


def sb2_w16s(emu, off, vals):
    base = emu.sb2()
    for i, v in enumerate(vals):
        emu.w16(base + off + 2 * i, v)


@script_op("sb2w16")
def _op_sb2w16(emu, f, path):
    sb2_w16s(emu, int(f[1], 16), [int(v, 0) for v in f[2:]])


@script_op("sb2w32")
def _op_sb2w32(emu, f, path):
    emu.w32(emu.sb2() + int(f[1], 16), int(f[2], 0))


def sb2_str(emu, off, maxlen, text):
    b = encode(text)[:maxlen - 1] + b"\xff"
    b = b + b"\xff" * (maxlen - len(b))
    base = emu.sb2()
    for i, c in enumerate(b):
        emu.w8(base + off + i, c)


@script_op("sb2str")
def _op_sb2str(emu, f, path):
    sb2_str(emu, int(f[1], 16), int(f[2]), " ".join(f[3:]))


# Ranking Hall names: Latin (record mixing with an English game) and Hebrew (another Hebrew game)
HALL_NAMES = ["RED", "קרן", "BLUE"]


@script_op("bfrecords")
def _op_bfrecords(emu, f, path):
    F = FRONTIER
    # [mode][lvl] arrays: Lv.50 first. Streaks with 1-4 digits, so digit order shows.
    sb2_w16s(emu, F["towerWinStreaks"], [7, 1234, 56, 0, 21, 9999, 3, 100])
    sb2_w16s(emu, F["towerRecordWinStreaks"], [49, 2345, 68, 5, 35, 9999, 12, 101])
    sb2_w16s(emu, F["domeWinStreaks"], [2, 13, 4, 0])
    sb2_w16s(emu, F["domeRecordWinStreaks"], [5, 27, 9, 1])
    sb2_w16s(emu, F["domeTotalChampionships"], [3, 145, 1, 0])
    sb2_w16s(emu, F["palaceWinStreaks"], [8, 321, 14, 0])
    sb2_w16s(emu, F["palaceRecordWinStreaks"], [42, 654, 28, 2])
    sb2_w16s(emu, F["arenaWinStreaks"], [6, 87])
    sb2_w16s(emu, F["arenaRecordStreaks"], [28, 910])
    sb2_w16s(emu, F["factoryWinStreaks"], [11, 222, 4, 0])
    sb2_w16s(emu, F["factoryRecordWinStreaks"], [21, 333, 8, 1])
    sb2_w16s(emu, F["factoryRentsCount"], [15, 444, 2, 0])
    sb2_w16s(emu, F["factoryRecordRentsCount"], [31, 555, 6, 3])
    sb2_w16s(emu, F["pikeWinStreaks"], [9, 76])
    sb2_w16s(emu, F["pikeRecordStreaks"], [14, 140])
    sb2_w16s(emu, F["pikeTotalStreaks"], [2, 17])
    sb2_w16s(emu, F["pyramidWinStreaks"], [3, 21])
    sb2_w16s(emu, F["pyramidRecordStreaks"], [7, 35])
    # Lv.50 streaks are "current", Open Level ones "previous"
    emu.w32(emu.sb2() + F["winStreakActiveFlags"], 0x01555555)
    sb2_w16s(emu, F["battlePoints"], [1234])
    # Ranking Hall 1P: [9 facilities][2 lvl modes][3 records] of {id[4], winStreak, name[8], language, pad}
    base1 = F["hallRecords1P"]
    for fac in range(9):
        for lvl in range(2):
            for k in range(3):
                off = base1 + ((fac * 2 + lvl) * 3 + k) * F["RankingHall1P.size"]
                streak = [8000, 300, 20][k] + fac * 7 + lvl
                sb2_w16s(emu, off + 0, [0x1111 * (k + 1), 0x2222])
                sb2_w16s(emu, off + 4, [streak])
                sb2_str(emu, off + 6, 8, HALL_NAMES[k])
                emu.w8(emu.sb2() + off + 0xE, 2)          # LANGUAGE_ENGLISH
    # Ranking Hall 2P: [2 lvl modes][3 records] of {id1[4], id2[4], winStreak, name1[8], name2[8], language, pad}
    base2 = F["hallRecords2P"]
    for lvl in range(2):
        for k in range(3):
            off = base2 + (lvl * 3 + k) * F["RankingHall2P.size"]
            sb2_w16s(emu, off + 0, [0x3333, 0x4444, 0x5555, 0x6666])
            sb2_w16s(emu, off + 8, [[900, 45, 6][k] + lvl])
            sb2_str(emu, off + 0xA, 8, HALL_NAMES[k])
            sb2_str(emu, off + 0x12, 8, HALL_NAMES[(k + 1) % 3])
            emu.w8(emu.sb2() + off + 0x1A, 2)
    print("bfrecords ok @%d" % emu.sync())


@script_op("saveyes")
def _op_saveyes(emu, f, path):
    """saveyes [PREFIX] [MAX]: a script save (special SaveGame -> SaveGameTask) is on screen:
    answer YES to "Save the game?" (and to an overwrite question) with A, until the task ends.
    With PREFIX, the first question is shot as PREFIX_01."""
    prefix = f[1] if len(f) > 1 and f[1] != "-" else None
    limit = _arg(f, 2, 2400)
    emu.wait_until(lambda: emu.task_active("SaveGameTask"), 300, "SaveGameTask", step=2)
    n, waited, shot = 0, 0, False
    while emu.task_active("SaveGameTask"):
        if waited >= limit:
            raise hns.TourTimeout("saveyes: SaveGameTask still running after %d frames" % limit)
        emu.wait_quiet(300)
        if prefix and not shot:
            emu.frames(2)
            emu.shot("%s_01" % prefix)
            emu.shots = getattr(emu, "shots", []) + ["%s_01" % prefix]
            shot = True
        emu.tap("A", 30)
        n += 1
        waited += 40
    emu.wait_quiet(300)
    print("saveyes: %d press(es) @%d" % (n, emu.sync()))


def _bfrom(emu, name):
    return hns.BATTLE_ACTIONS[name]


@script_op("bwin", "blose")
def _op_bwin(emu, f, path):
    """bwin PREFIX [MAXTURNS] [keephp]: win the battle on screen. Every turn: battle_walk
    (PREFIX_tNN_MM shots), then at the action menu (unless keephp) set the foes' battlers to
    1 HP, refill the player's battler and make its first move Ice Shard (always hits first;
    gBattleMons only, BattlePokemon offsets measured with offsetof(): moves 0x0C, pp 0x25,
    hp 0x2A, maxHP 0x2E), then FIGHT with move 0 (a target prompt gets A). `blose` instead sets
    the player's battler to 1 HP and its first move to Splash, and the foes to full HP, so
    the player loses. A fainted Pokemon is
    replaced by the first party slot that can battle. Returns once the field runs again
    (Task_WeatherMain) or callback2 leaves the battle."""
    prefix = f[1]
    maxturns = _arg(f, 2, 40)
    keephp = len(f) > 3 and f[3] == "keephp"
    bcb2 = emu.sym("BattleMainCB2")
    bm = emu.sym("gBattleMons")
    lose = f[0] == "blose"
    shard = emu.const("MOVE_SPLASH" if lose else "MOVE_ICE_SHARD")
    for turn in range(maxturns):
        if emu.cb2() != bcb2 and emu.task_active("Task_WeatherMain"):
            break
        n, end = hns.battle_walk(emu, "%s_t%02d" % (prefix, turn), (), 60, 6000,
                                 stop_tasks=("Task_WeatherMain",))
        print("  bwin turn %d: %d page(s), %s" % (turn, n, end))
        if end.startswith("task:Task_WeatherMain") or end == "free":
            break
        if end.startswith("input:HandleInputChooseAction"):
            b = 2 if end.endswith("#2") else 0
            if not keephp:
                for bb in ((1, 3) if emu.r8(emu.sym("gBattlersCount")) > 2 else (1,)):
                    if emu.r16(bm + 0x88 * bb + 0x2A):
                        emu.w16(bm + 0x88 * bb + 0x2A, emu.r16(bm + 0x88 * bb + 0x2E) if lose else 1)
                emu.w16(bm + 0x88 * b + 0x2A, 1 if lose else emu.r16(bm + 0x88 * b + 0x2E))
                emu.w16(bm + 0x88 * b + 0x0C, shard)
                if emu.r8(bm + 0x88 * b + 0x25) == 0:
                    emu.w8(bm + 0x88 * b + 0x25, 10)
            hns.wait_battle_input(emu, "HandleInputChooseAction", battler=b)
            hns.battle_cursor(emu, "gActionSelectionCursor", 0, battler=b)
            emu.tap("A", 4)
            hns.wait_battle_input(emu, "HandleInputChooseMove", battler=b)
            hns.battle_cursor(emu, "gMoveSelectionCursor", 0, battler=b)
            emu.tap("A", 4)
        elif end.startswith("input:"):
            emu.tap("A", 4)
        elif end.startswith("task:Task_HandleChooseMonInput"):
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
        elif end.startswith("prompt:"):
            emu.tap("B", 4)
        else:
            emu.tap("A", 4)
    else:
        raise hns.TourTimeout("bwin %s: still in battle after %d turns" % (prefix, maxturns))
    print("bwin %s ok @%d" % (prefix, emu.sync()))


@script_op("drivex")
def _op_drivex(emu, f, path):
    """drivex PREFIX TARGET [MAXPAGES] [MAXFRAMES]: r3bf `drive` (one shot per text page, then A,
    until TARGET: free | menu | battle | cb2:SYM | task:SYM), plus a shot whenever a text printer
    finishes a message that does not wait for a key (a fanfare line such as "received the
    Symbol" or "obtained N BP"). Any choice menu stops it ('menu' or not)."""
    prefix, target = f[1], f[2]
    maxpages = _arg(f, 3, 60)
    maxframes = _arg(f, 4, 6000)
    ow = emu.sym("CB2_Overworld")
    bcb2 = emu.sym("BattleMainCB2")
    want_cb2 = emu.sym(target[4:]) if target.startswith("cb2:") else None
    want_task = target[5:] if target.startswith("task:") else None
    n, idle, prev = 0, 0, "idle"
    last_box = hns.message_box(emu) if emu.cb2() in (ow, bcb2) else None

    def shoot():
        nonlocal n
        n += 1
        r3bf._shot(emu, "%s_%02d" % (prefix, n))

    def reached():
        cb = emu.cb2()
        if want_cb2 is not None:
            return cb == want_cb2
        if want_task is not None:
            return emu.task_active(want_task)
        if target == "battle":
            return cb == bcb2
        if target == "free":
            return emu.controllable()
        return False

    while True:
        if reached():
            if target == "free":
                emu.frames(8)
                if not emu.controllable():
                    continue
            print("drivex %s: %d shot(s), reached %s @%d" % (prefix, n, target, emu.sync()))
            return
        if idle >= maxframes:
            raise hns.TourTimeout("drivex %s: stuck %d frames after %d shot(s) (callback2 %s, tasks %s)"
                                  % (prefix, idle, n, emu.cb2_name(), [t[2] for t in emu.tasks()]))
        if n >= maxpages:
            raise HnsError("drivex %s: %d shots and no %s" % (prefix, n, target))
        cb = emu.cb2()
        if cb == ow and emu.tasks_named(emu.MENU_TASKS):
            emu.wait_menu_ready()
            emu.frames(2)
            shoot()
            print("drivex %s: %d shot(s), menu %s @%d" % (prefix, n, emu.tasks_named(emu.MENU_TASKS)[0], emu.sync()))
            if target == "menu":
                return
            raise HnsError("drivex %s: unexpected menu" % prefix)
        st = emu.text_state()
        if st == "busy" or emu.fading():
            prev = "busy" if st == "busy" else prev
            emu.frames(2)
            idle += 2
            continue
        if emu.wants_key():
            emu.wait_quiet(600)
            box = hns.message_box(emu) if cb in (ow, bcb2) else None
            if box is None or box != last_box:
                shoot()
            last_box = box
            emu.tap("A", 0)
            emu.wait_until(lambda: not emu.wants_key(), 90, "the text to take the key", step=1)
            idle, prev = 0, "idle"
            continue
        if prev == "busy":                      # a printer finished a line that waits for no key
            emu.frames(4)
            box = hns.message_box(emu) if cb in (ow, bcb2) else None
            if box is not None and box != last_box:
                shoot()
                last_box = box
        prev = st
        emu.frames(2)
        idle += 2


if __name__ == "__main__":
    sys.argv[0] = hns.__file__
    sys.exit(hns.main())
