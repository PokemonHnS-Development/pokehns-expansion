#!/usr/bin/env python3
"""hns.py plus the r2/r3 tour ops (scripts/r3_frontier/r3bf.py: drive, pick, vars; and through it
scripts/r2_safari_pokeblock_bug_contest/r2sf.py: textwatch, burst, scenewatch, scrollshots, warpraw,
ss/sl, loc, ...) and the ops the rc_* tours (PokeGear RIBBONS, contests, the contest lobby) use.
Run:  rc.py tour ROM OUT --tours <this folder> [--clip] [--only RE]

Added here:
    boxclone PARTYIDX BOX SLOT   copy party mon PARTYIDX's BoxPokemon (the first 80 bytes of the
                                 100-byte struct Pokemon, encryption included) into the empty PC
                                 slot BOX/SLOT (struct PokemonStorage: currentBox u8, boxes at +4,
                                 include/pokemon_storage_system.h:20-27), so the RIBBONS list holds
                                 box mons too
    giftribbon SLOT ID           gSaveBlock1Ptr->giftRibbons[SLOT] = ID (SaveBlock1 +0x38C8, read
                                 from GiveGiftRibbonToParty's literal pool, src/pokemon_size_record.c:264);
                                 the summary prints gGiftRibbonDescriptionPointers[ID-1]
    navshot PREFIX KEY [MAX]     press KEY in the PokeGear, waitnav, shot PREFIX_NN; repeat until the
                                 screen stops changing (MAX shots)
    contestplay PREFIX [MOVES]   play the contest appeal screen (CB2_ContestMain, src/contest.c) until
                                 callback2 leaves it: a shot whenever a text printer finishes or the
                                 main task changes state; at the move list a shot of every move
                                 (DOWN), then the move MOVES[round] (a digit string, default 0123 0)
    contestresults PREFIX [MAX]  the results screen (CB2_ShowContestResults, src/contest_util.c):
                                 a shot every 10 frames while something changes, A when the
                                 task waits for a key, until callback2 leaves it
    paint PREFIX                 the contest painting (CB2_ContestPainting): shots until it fades out
    w16s SYM IDX VAL             write s16 VAL to SYM[IDX] (e.g. gContestMonRound1Points)
"""
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(HERE, "..", ".."))                      # tools/hebrew/emu
sys.path.insert(0, os.path.join(HERE, "..", "r3_frontier"))
import hns  # noqa: E402
import r3bf  # noqa: E402,F401  (registers the r2 and r3 ops)
from hns import script_op, HnsError, TourTimeout, _arg  # noqa: E402

BOXMON_SIZE, PARTYMON_SIZE = 80, 100
STORAGE_BOXES, IN_BOX = 4, 30
SB1_GIFT_RIBBONS = 0x38C8


def _shot(emu, name):
    emu.frames(1)
    emu.shot(name)
    emu.shots = getattr(emu, "shots", []) + [name]
    return os.path.join(emu.outdir, name + ".png")


def _same_as(p, last):
    data = open(p, "rb").read() if os.path.exists(p) else None
    return data, (data is not None and data == last)


@script_op("boxclone")
def _op_boxclone(emu, f, path):
    i, box, slot = int(f[1]), int(f[2]), int(f[3])
    src = emu.sym("gPlayerParty") + PARTYMON_SIZE * i
    storage = emu.r32(emu.sym("gPokemonStoragePtr"))
    dst = storage + STORAGE_BOXES + (box * IN_BOX + slot) * BOXMON_SIZE
    if any(emu.read(dst, BOXMON_SIZE)):
        raise HnsError("boxclone: box %d slot %d is not empty" % (box, slot))
    data = emu.read(src, BOXMON_SIZE)
    for k in range(0, BOXMON_SIZE, 4):
        emu.w32(dst + k, int.from_bytes(data[k:k + 4], "little"))
    if emu.read(dst, BOXMON_SIZE) != data:
        raise HnsError("boxclone: bytes did not read back")
    print("boxclone party %d -> box %d slot %d @%d" % (i, box, slot, emu.sync()))


@script_op("giftribbon")
def _op_giftribbon(emu, f, path):
    slot, rid = int(f[1]), emu.const(f[2])
    emu.w8(emu.sb1() + SB1_GIFT_RIBBONS + slot, rid)
    print("giftribbon %d = %d" % (slot, rid))


# struct Pokenav_RibbonsSummaryList (src/pokenav_ribbons_summary.c:45-57) with apcs-gnu alignment:
# unused1[8] +0, monList +8, selectedPos u16 +12, normalRibbonLastRowStart +14, numNormalRibbons +16,
# numGiftRibbons +18, ribbonIds[25] +20, giftRibbonIds[7] +120, unused2 +148, callback +152.
RSL_SELPOS, RSL_NNORMAL, RSL_NGIFT, RSL_CALLBACK = 12, 16, 18, 152
GIFT_RIBBON_START_POS = 27            # RIBBONS_PER_ROW * (1 + FIRST_GIFT_RIBBON / RIBBONS_PER_ROW)


def ribbon_list(emu):
    res = emu.r32(emu.sym("gPokenavResources"))
    want = {emu.sym("RibbonsSummaryHandleInput"), emu.sym("HandleExpandedRibbonInput")}
    raw = emu.read(res, 0x80)
    for off in range(0, 0x80, 4):
        p = int.from_bytes(raw[off:off + 4], "little")
        if 0x02000000 <= p < 0x02040000 and emu.r32(p + RSL_CALLBACK) in want:
            return p
    raise HnsError("no Pokenav_RibbonsSummaryList (is the ribbon summary open?)")


def _nav_wait(emu):
    emu.wait_until(lambda: hns.pokenav_idle(emu), 900, "the Pokegear to read input", step=2)
    emu.wait_quiet(600)


@script_op("ribbonwalk")
def _op_ribbonwalk(emu, f, path):
    """ribbonwalk PREFIX: in the expanded ribbon view, visit every ribbon of the shown mon in a
    snake (each row both ways, then DOWN), one shot per new position (selectedPos read live)."""
    prefix = f[1]
    lst = ribbon_list(emu)
    pos = lambda: emu.r16(lst + RSL_SELPOS)
    seen, n = set(), 0

    def keep():
        nonlocal n
        p = pos()
        if p in seen:
            return
        seen.add(p)
        n += 1
        _shot(emu, "%s_%02d_pos%02d" % (prefix, n, p))

    _nav_wait(emu)
    keep()
    order = ("RIGHT", "LEFT")
    for row in range(8):
        for d in order:
            for _ in range(10):
                before = pos()
                emu.tap(d, 4)
                _nav_wait(emu)
                if pos() == before:
                    break
                keep()
        before = pos()
        emu.tap("DOWN", 4)
        _nav_wait(emu)
        if pos() == before:
            break
        keep()
        order = order[::-1]
    print("ribbonwalk %s: %d ribbon(s) %s (normal %d, gift %d) @%d" % (
        prefix, n, sorted(seen), emu.r16(lst + RSL_NNORMAL), emu.r16(lst + RSL_NGIFT), emu.sync()))


@script_op("giftcycle")
def _op_giftcycle(emu, f, path):
    """giftcycle PREFIX FROM TO: in the expanded view, go to the first gift ribbon (DOWN, then LEFT),
    then for ID in FROM..TO set giftRibbons[0] = ID and step RIGHT and back LEFT, so the name and
    description are printed again; one shot per ID (PREFIX_IDNN)."""
    prefix, lo, hi = f[1], int(f[2]), int(f[3])
    lst = ribbon_list(emu)
    pos = lambda: emu.r16(lst + RSL_SELPOS)
    for _ in range(6):
        if pos() >= GIFT_RIBBON_START_POS:
            break
        emu.tap("DOWN", 4)
        _nav_wait(emu)
    for _ in range(10):
        if pos() == GIFT_RIBBON_START_POS:
            break
        emu.tap("LEFT", 4)
        _nav_wait(emu)
    if pos() != GIFT_RIBBON_START_POS:
        raise HnsError("giftcycle: cursor at %d, not on the first gift ribbon" % pos())
    gift = emu.sb1() + SB1_GIFT_RIBBONS
    old = emu.r8(gift)
    for rid in range(lo, hi + 1):
        emu.w8(gift, rid)
        emu.tap("RIGHT", 4)
        _nav_wait(emu)
        emu.tap("LEFT", 4)
        _nav_wait(emu)
        _shot(emu, "%s_id%02d" % (prefix, rid))
    emu.w8(gift, old)
    print("giftcycle %s %d..%d @%d" % (prefix, lo, hi, emu.sync()))


@script_op("partyclear")
def _op_partyclear(emu, f, path):
    """partyclear IDX: zero party slot IDX (100 bytes) so `givemon` fills it; the party count is
    recalculated by the next givemon (CalculatePlayerPartyCount)."""
    base = emu.sym("gPlayerParty") + PARTYMON_SIZE * int(f[1])
    for k in range(0, PARTYMON_SIZE, 4):
        emu.w32(base + k, 0)
    print("partyclear %s" % f[1])


@script_op("w16s")
def _op_w16s(emu, f, path):
    addr = emu.sym(f[1]) + 2 * int(f[2])
    emu.w16(addr, int(f[3], 0) & 0xFFFF)
    print("w16s %s[%s] = %s" % (f[1], f[2], f[3]))


@script_op("navshot")
def _op_navshot(emu, f, path):
    prefix, key, mx = f[1], f[2], _arg(f, 3, 30)
    n, last = 0, None
    while n < mx:
        emu.wait_until(lambda: hns.pokenav_idle(emu), 900, "the Pokegear to read input", step=2)
        emu.wait_quiet(600)
        n += 1
        p = _shot(emu, "%s_%02d" % (prefix, n))
        data, same = _same_as(p, last)
        if same:
            os.remove(p)
            emu.shots = emu.shots[:-1]
            n -= 1
            break
        last = data
        emu.tap(key, 4)
    print("navshot %s: %d shot(s) @%d" % (prefix, n, emu.sync()))


# the contest's main task runs these in turn (src/contest.c:48-92, 122, 2678)
CONTEST_MAIN_TASKS = {
    "Task_StartContestWaitFade", "Task_TryStartLinkContest", "Task_CommunicateMonIdxs",
    "Task_EndCommunicateMonIdxs", "Task_ReadyStartLinkContest", "Task_WaitToRaiseCurtainAtStart",
    "Task_RaiseCurtainAtStart", "Task_DisplayAppealNumberText", "Task_TryShowMoveSelectScreen",
    "Task_ShowMoveSelectScreen", "Task_HandleMoveSelectInput", "Task_SelectedMove",
    "Task_EndCommunicateMoveSelections", "Task_HideMoveSelectScreen", "Task_HideApplauseMeterForAppealStart",
    "Task_WaitHideApplauseMeterForAppealStart", "Task_AppealSetup", "Task_DoAppeals", "Task_EndWaitForLink",
    "Task_FinishRoundOfAppeals", "Task_ReadyUpdateHeartSliders", "Task_UpdateHeartSliders",
    "Task_WaitForHeartSliders", "Task_RestorePlttBufferUnfaded", "Task_WaitPrintRoundResult",
    "Task_PrintRoundResultText", "Task_ReUpdateHeartSliders", "Task_WaitForHeartSlidersAgain",
    "Task_DropCurtainAtRoundEnd", "Task_TryStartNextRoundOfAppeals", "Task_StartNewRoundOfAppeals",
    "Task_EndAppeals", "Task_WaitForOutOfTimeMsg", "Task_DropCurtainAtAppealsEnd",
    "Task_TryCommunicateFinalStandings", "Task_CommunicateFinalStandings",
    "Task_EndCommunicateFinalStandings", "Task_ContestReturnToField", "Task_StartDropCurtainAtRoundEnd",
    "Task_UpdateContestantBoxOrder",
}


def _task_funcs(emu):
    return [t[2] for t in emu.tasks()]


@script_op("contestplay")
def _op_contestplay(emu, f, path):
    prefix = f[1]
    moves = f[2] if len(f) > 2 else "01230"
    maxf = _arg(f, 3, 40000)
    contest_cb2s = set()
    for n in ("CB2_ContestMain", "CB2_StartContest"):
        try:
            contest_cb2s.add(emu.sym(n))
        except HnsError:
            pass
    # shots are PREFIX_rR_SS_TAG: R the appeal round being played (0 = the curtain before the
    # first one), SS a counter inside the round; text and key events are never dropped, so the
    # same event has the same name on every ROM
    n, seq, cur, waited, rnd = 0, 0, 0, 0, 0
    last_data = None
    prev_state, prev_text = None, "idle"

    def shoot(tag, dedupe=False):
        nonlocal n, seq, last_data
        n += 1
        seq += 1
        name = "%s_r%d_%02d_%s" % (prefix, cur, seq, tag)
        p = _shot(emu, name)
        data, same = _same_as(p, last_data)
        if same and dedupe:
            os.remove(p)
            emu.shots = emu.shots[:-1]
            n -= 1
            seq -= 1
            return False
        last_data = data
        return True

    while waited < maxf:
        cb = emu.cb2()
        if cb not in contest_cb2s:
            break
        tasks = [t.split(":")[-1] for t in _task_funcs(emu)]
        st = emu.text_state()
        main = next((t for t in tasks if t in CONTEST_MAIN_TASKS), None)
        if main == "Task_TryShowMoveSelectScreen" and st != "busy":
            emu.frames(4)
            cur, seq = rnd + 1, 0
            shoot("prompt")
            emu.tap("A", 4)
            emu.wait_until(lambda: any(t.endswith("Task_HandleMoveSelectInput") for t in _task_funcs(emu)), 300,
                           "the move list", step=1)
            emu.frames(6)
            # every move of the list, the description window changes with the cursor
            for k in range(4):
                shoot("move%d" % k)
                emu.tap("DOWN", 4)
                emu.frames(6)
            want = int(moves[rnd % len(moves)])
            for k in range(want):
                emu.tap("DOWN", 4)
                emu.frames(6)
            shoot("pick")
            emu.tap("A", 4)
            rnd += 1
            prev_state = None
            waited += 60
            continue
        if st == "key":                      # {PAUSE_UNTIL_PRESS} (the round result lines)
            emu.frames(2)
            shoot("key_" + (main or "none").replace("Task_", "")[:24])
            emu.tap("A", 0)
            emu.wait_until(lambda: emu.text_state() != "key", 90, "the text to take the key", step=1)
            prev_state, prev_text = main, emu.text_state()
            waited += 10
            continue
        if prev_text == "busy" and st != "busy":
            emu.frames(2)
            shoot("text_" + (main or "none").replace("Task_", "")[:22])
        elif main != prev_state:
            emu.frames(2)
            shoot((main or "none").replace("Task_", "")[:28], dedupe=True)
        prev_state, prev_text = main, st
        emu.frames(3)
        waited += 3
    print("contestplay %s: %d shot(s), %d rounds, callback2 %s @%d" % (prefix, n, rnd, emu.cb2_name(), emu.sync()))
    if waited >= maxf:
        raise TourTimeout("contestplay: still in the contest after %d frames" % maxf)


@script_op("fieldwatch")
def _op_fieldwatch(emu, f, path):
    """fieldwatch PREFIX TARGET [MAX] [EVERY]: run a field scene (messages with and without a key
    wait, movements, warps) until TARGET (free | menu | cb2:SYM | task:SYM). A shot when a text
    printer finishes, when a message waits for a key (then A), and every EVERY frames (default 0 =
    never) while nothing prints; identical consecutive shots are dropped. Any script menu on the
    way (unless TARGET is menu) is shot and ends the watch with an error."""
    prefix, target = f[1], f[2]
    maxf, every = _arg(f, 3, 20000), _arg(f, 4, 0)
    want_cb2 = emu.sym(target[4:]) if target.startswith("cb2:") else None
    want_task = target[5:] if target.startswith("task:") else None
    ow = emu.sym("CB2_Overworld")
    # message shots are numbered PREFIX_NNN (the same on every ROM: one per message event);
    # periodic shots PREFIX_NNN_pKK (KK-th since message NNN; their count depends on timing)
    n, k, waited, since, last, prev = 0, 0, 0, 0, None, "idle"

    def shoot(periodic=False):
        nonlocal n, k, last, since
        since = 0
        if periodic:
            k += 1
            name = "%s_%03d_p%02d" % (prefix, n, k)
        else:
            n += 1
            k = 0
            name = "%s_%03d" % (prefix, n)
        p = _shot(emu, name)
        data, same = _same_as(p, last)
        if same and periodic:
            os.remove(p)
            emu.shots = emu.shots[:-1]
            k -= 1
            return
        last = data

    def reached():
        cb = emu.cb2()
        if want_cb2 is not None:
            return cb == want_cb2
        if want_task is not None:
            return emu.task_active(want_task)
        if target == "free":
            return emu.controllable()
        return False

    while waited < maxf:
        if reached():
            if target == "free":
                emu.frames(8)
                if not emu.controllable():
                    continue
            print("fieldwatch %s: %d shot(s), reached %s @%d" % (prefix, n, target, emu.sync()))
            return
        if emu.cb2() == ow and emu.tasks_named(emu.MENU_TASKS):
            emu.wait_menu_ready()
            emu.frames(2)
            shoot()
            if target == "menu":
                print("fieldwatch %s: %d shot(s), menu %s @%d" % (prefix, n, emu.tasks_named(emu.MENU_TASKS)[0], emu.sync()))
                return
            raise HnsError("fieldwatch %s: unexpected menu %s" % (prefix, emu.tasks_named(emu.MENU_TASKS)[0]))
        st = emu.text_state()
        if emu.wants_key():
            emu.wait_quiet(600)
            emu.frames(2)
            shoot()
            emu.tap("A", 0)
            emu.wait_until(lambda: not emu.wants_key(), 90, "the text to take the key", step=1)
            prev = emu.text_state()
            waited += 10
            continue
        if prev == "busy" and st != "busy":
            emu.frames(2)
            shoot()
        elif every and since >= every and st != "busy" and not emu.fading():
            shoot(periodic=True)
        prev = st
        emu.frames(2)
        waited += 2
        since += 2
    raise TourTimeout("fieldwatch %s: no %s after %d frames (callback2 %s, tasks %s)"
                      % (prefix, target, maxf, emu.cb2_name(), _task_funcs(emu)))


@script_op("copyrom")
def _op_copyrom(emu, f, path):
    """copyrom SRCSYM DST LEN: copy LEN bytes from the ROM object SRCSYM to RAM at DST (hex, or
    sb1+HEX inside SaveBlock1), e.g. the ROM's default contest winners (gDefaultContestWinners)
    into gSaveBlock1Ptr->contestWinners (SB1+0x35B0, from ClearContestWinnerPicsInContestHall's
    literal pool, src/contest.c:5636-5641)."""
    src, ln = emu.sym(f[1]), int(f[3], 0)
    dst = emu.sb1() + int(f[2][4:], 16) if f[2].startswith("sb1+") else int(f[2], 16)
    data = emu.read(src, ln)
    data = data + b"\0" * (-len(data) % 4)
    for k in range(0, len(data), 4):
        emu.w32(dst + k, int.from_bytes(data[k:k + 4], "little"))
    print("copyrom %s -> %08X (%d bytes)" % (f[1], dst, ln))


@script_op("burstuntil")
def _op_burstuntil(emu, f, path):
    """burstuntil PREFIX CB2 EVERY MAX [KEY] [KEYEVERY]: while callback2 == CB2, a shot every EVERY
    frames (identical shots dropped); tap KEY every KEYEVERY frames ('-' never)."""
    prefix, cb, every, maxf = f[1], emu.sym(f[2]), int(f[3]), int(f[4])
    key = f[5] if len(f) > 5 else "-"
    kev = int(f[6]) if len(f) > 6 else 0
    n, waited, last = 0, 0, None
    while emu.cb2() == cb and waited < maxf:
        emu.frames(every)
        waited += every
        if emu.cb2() != cb:
            break
        n += 1
        p = _shot(emu, "%s_%03d" % (prefix, n))
        data, same = _same_as(p, last)
        if same:
            os.remove(p)
            emu.shots = emu.shots[:-1]
            n -= 1
        last = data
        if key != "-" and kev and waited % kev < every:
            emu.tap(key, 0)
    print("burstuntil %s: %d shot(s), %d frames, callback2 %s @%d" % (prefix, n, waited, emu.cb2_name(), emu.sync()))


if __name__ == "__main__":
    sys.argv[0] = hns.__file__
    sys.exit(hns.main())
