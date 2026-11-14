#!/usr/bin/env python3
"""rc.py (the r2 contest ops) plus the Trainer Hill walk ops (walkto, talkto, objs, grid) and
ops for the round-5 contest tours (tours/r5_contests):

    contestplay5 PREFIX [MOVES] [MAX]
                 contestplay (rc.py) with three changes:
                 - MOVES[round] is the absolute move-list index: the cursor
                   (struct Contest.playerMoveChoice, +0) stays where the last round left it
                   (src/contest.c:1604, 1649-1666), so rc.py's "DOWN MOVES[round] times from the
                   top" picks a different move from round 2 on;
                 - a turn the player cannot appeal in (after a "can't appeal next turn" move, or
                   after a "no more appeals" move): A at the prompt goes straight to
                   Task_SelectedMove (src/contest.c:1551-1567), so there is no move list; the shot
                   PREFIX_rR_02_skipped is taken and MOVES[round] is skipped;
                 - a message that is followed at once by the next one (no idle frame in between,
                   e.g. gText_MonCantAppealNextTurn, src/contest.c:2122-2137) is shot as
                   PREFIX_rR_SS_hold_... when the printer first reaches a {PAUSE} (RENDER_STATE_PAUSE,
                   include/text.h:47-53): every contest message ends with {PAUSE 0x0F} x4, so the
                   whole message is on screen then
    applause N   set the excitement level (struct Contest.applauseLevel, +0x13,
                 include/contest.h:138-170) of the running contest
    talknpc LOCALID PREFIX [TRIES]
                 talkto that tries the other sides of an object (a stage desk in front of a judge)
                 and follows a wandering one; the follower Pokemon is not planned around
    readsign X Y PREFIX
                 walk next to the bg sign at (X, Y), face it, A, walk the text
    crashwatch N / burstwatch PREFIX CB2 EVERY MAX KEY KEYEVERY FROMFRAME
                 debugging: print callbacks and task funcs frame by frame (burstwatch keeps
                 burstuntil's timing, so a crash that depends on when A is pressed reproduces)
Run:  rc5.py tour ROM OUT --tours tools/hebrew/emu/tours/r5_contests [--clip] [--only RE]
"""
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(HERE, "..", ".."))                       # tools/hebrew/emu
sys.path.insert(0, os.path.join(HERE, "..", "r2_pokegear_ribbons_contests"))
sys.path.insert(0, os.path.join(HERE, "..", "r2_hill_tents"))
import hns  # noqa: E402
import rc  # noqa: E402  (registers the r2/r3 ops and the contest ops)
import hilltent_ops  # noqa: E402,F401  (walkto, talkto, objs, grid)
from hns import script_op, HnsError, TourTimeout, _arg  # noqa: E402

CONTEST_APPLAUSE_LEVEL = 0x13
CONTEST_PLAYER_MOVE_CHOICE = 0x00
RENDER_STATE_PAUSE = 6
OBJ_EVENT_ID_FOLLOWER = 0xFE

# The player walks through the follower Pokemon (they swap places), so the walk ops must not plan
# around it (it can wall the player in next to a stage desk).
_objects_all = hilltent_ops.objects
hilltent_ops.objects = lambda emu: [o for o in _objects_all(emu) if o[0] != OBJ_EVENT_ID_FOLLOWER]


def _tasks(emu):
    return [t[2].split(":")[-1] for t in emu.tasks()]


@script_op("applause")
def _op_applause(emu, f, path):
    contest = emu.r32(emu.r32(emu.sym("gContestResources")))
    old = emu.r8(contest + CONTEST_APPLAUSE_LEVEL)
    emu.w8(contest + CONTEST_APPLAUSE_LEVEL, int(f[1]))
    print("applause %d -> %s @%d" % (old, f[1], emu.sync()))


@script_op("contestplay5")
def _op_contestplay5(emu, f, path):
    prefix = f[1]
    moves = f[2] if len(f) > 2 else "01230"
    maxf = _arg(f, 3, 40000)
    contest_cb2s = set()
    for n in ("CB2_ContestMain", "CB2_StartContest"):
        try:
            contest_cb2s.add(emu.sym(n))
        except HnsError:
            pass
    n, seq, cur, waited, rnd = 0, 0, 0, 0, 0
    held = False
    last_data = None
    prev_state, prev_text = None, "idle"

    def shoot(tag, dedupe=False):
        nonlocal n, seq, last_data
        n += 1
        seq += 1
        name = "%s_r%d_%02d_%s" % (prefix, cur, seq, tag)
        p = rc._shot(emu, name)
        data, same = rc._same_as(p, last_data)
        if same and dedupe:
            os.remove(p)
            emu.shots = emu.shots[:-1]
            n -= 1
            seq -= 1
            return False
        last_data = data
        return True

    while waited < maxf:
        if emu.cb2() not in contest_cb2s:
            break
        tasks = _tasks(emu)
        st = emu.text_state()
        main = next((t for t in tasks if t in rc.CONTEST_MAIN_TASKS), None)
        if main == "Task_TryShowMoveSelectScreen" and st != "busy":
            emu.frames(4)
            cur, seq = rnd + 1, 0
            shoot("prompt")
            emu.tap("A", 4)
            emu.wait_until(lambda: "Task_HandleMoveSelectInput" in _tasks(emu)
                           or "Task_TryShowMoveSelectScreen" not in _tasks(emu), 300,
                           "the move list or the skipped turn", step=1)
            if "Task_HandleMoveSelectInput" in _tasks(emu):
                emu.frames(6)
                for k in range(4):
                    shoot("move%d" % k)
                    emu.tap("DOWN", 4)
                    emu.frames(6)
                want = int(moves[rnd % len(moves)])
                choice = emu.r32(emu.sym("gContestResources"))
                choice = emu.r32(choice) + CONTEST_PLAYER_MOVE_CHOICE
                for k in range(8):
                    if emu.r8(choice) == want:
                        break
                    emu.tap("DOWN", 4)
                    emu.frames(6)
                if emu.r8(choice) != want:
                    raise HnsError("contestplay5: move cursor at %d, wanted %d" % (emu.r8(choice), want))
                shoot("pick")
                emu.tap("A", 4)
            else:
                emu.frames(2)
                shoot("skipped")
            rnd += 1
            prev_state = None
            waited += 60
            continue
        if st == "key":
            emu.frames(2)
            shoot("key_" + (main or "none").replace("Task_", "")[:24])
            emu.tap("A", 0)
            emu.wait_until(lambda: emu.text_state() != "key", 90, "the text to take the key", step=1)
            prev_state, prev_text = main, emu.text_state()
            waited += 10
            continue
        paused = any(a and ps == RENDER_STATE_PAUSE for _, ps, a, _ in emu.text_printers())
        if prev_text == "busy" and st != "busy":
            emu.frames(2)
            shoot("text_" + (main or "none").replace("Task_", "")[:22])
            held = False
        elif main != prev_state:
            emu.frames(2)
            shoot((main or "none").replace("Task_", "")[:28], dedupe=True)
        elif paused and not held:
            shoot("hold_" + (main or "none").replace("Task_", "")[:22], dedupe=True)
            held = True
        if not paused:
            held = False      # the next {PAUSE} (or the next message) gets its own shot; identical ones are dropped
        prev_state, prev_text = main, st
        emu.frames(3)
        waited += 3
    print("contestplay5 %s: %d shot(s), %d rounds, callback2 %s @%d" % (prefix, n, rnd, emu.cb2_name(), emu.sync()))
    if waited >= maxf:
        raise TourTimeout("contestplay5: still in the contest after %d frames" % maxf)


@script_op("talknpc")
def _op_talknpc(emu, f, path):
    """talknpc LOCALID PREFIX [TRIES]: talkto (hilltent_ops) that copes with a wandering object and
    with a desk in front of it: walk to the nearest free tile next to it, face it, A, walk the
    dialogue to a free player; when no text appears (a desk between, or it walked away), try the
    next tile next to it, from where it is now (TRIES, default 8)."""
    lid, prefix, tries = int(f[1], 0), f[2], _arg(f, 3, 8)
    ho = hilltent_ops
    failed = set()
    for attempt in range(tries):
        obj = [o for o in ho.objects(emu) if o[0] == lid]
        if not obj:
            raise HnsError("talknpc: no object %d (%s)" % (lid, ho.objects(emu)))
        _, ox, oy = obj[0]
        adj = {(ox, oy + 1): "UP", (ox, oy - 1): "DOWN", (ox + 1, oy): "LEFT", (ox - 1, oy): "RIGHT"}
        _, pos = emu.location()
        if pos not in adj or (pos, (ox, oy)) in failed:
            w, h, coll, behavior = ho.map_grid(emu)
            others = {(o[1], o[2]) for o in ho.objects(emu)}
            best = None
            for t in adj:
                if coll(*t) or t in others or (t, (ox, oy)) in failed:
                    continue
                r = ho.bfs(w, h, coll, pos, t, others, ho.ledge_map(emu, w, h, behavior),
                           ho.slide_map(emu, w, h, behavior), ho.ice_set(emu, w, h, behavior))
                if r is not None and (best is None or len(r) < len(best[1])):
                    best = (t, r)
            if best is None:
                emu.frames(30)
                continue
            try:
                ho._op_walkto(emu, ["walkto", str(best[0][0]), str(best[0][1])], path)
            except HnsError as e:
                print("   talknpc %d: %s" % (lid, e))
                emu.frames(30)
                continue
        _, pos = emu.location()
        obj = [o for o in ho.objects(emu) if o[0] == lid]
        if not obj:
            continue
        _, ox, oy = obj[0]
        adj = {(ox, oy + 1): "UP", (ox, oy - 1): "DOWN", (ox + 1, oy): "LEFT", (ox - 1, oy): "RIGHT"}
        if pos not in adj:
            continue
        emu.frames(2, adj[pos])
        emu.frames(14)
        emu.tap("A", 4)
        n, end = ho.dialogue(emu, prefix, "free", 60)
        if n > 0:
            print("talknpc %d %s: %d page(s) from %s, attempt %d @%d" % (lid, prefix, n, pos, attempt + 1, emu.sync()))
            return
        failed.add((pos, (ox, oy)))
    raise HnsError("talknpc: could not talk to object %d" % lid)


@script_op("readsign")
def _op_readsign(emu, f, path):
    """readsign X Y PREFIX: walk below the sign at (X, Y) (or next to it), face it, A, dialogue."""
    sx, sy, prefix = int(f[1]), int(f[2]), f[3]
    ho = hilltent_ops
    w, h, coll, behavior = ho.map_grid(emu)
    for (tx, ty), face in (((sx, sy + 1), "UP"), ((sx + 1, sy), "LEFT"), ((sx - 1, sy), "RIGHT"),
                           ((sx, sy - 1), "DOWN")):
        if coll(tx, ty):
            continue
        ho._op_walkto(emu, ["walkto", str(tx), str(ty)], path)
        if emu.location()[1] != (tx, ty):
            continue
        emu.frames(2, face)
        emu.frames(14)
        emu.tap("A", 4)
        n, end = ho.dialogue(emu, prefix, "free", 60)
        if n == 0:
            raise HnsError("readsign %d,%d: no text" % (sx, sy))
        return
    raise HnsError("readsign %d,%d: no free tile next to it" % (sx, sy))


@script_op("crashwatch")
def _op_crashwatch(emu, f, path):
    """crashwatch N: step N frames one at a time; before each frame print gMain.callback1/2, the
    VBlank/HBlank callbacks, the active task funcs and any sprite callback outside ROM, whenever
    one of them changed (to find the pointer a crash jumps through)."""
    n = int(f[1])
    gmain = emu.sym("gMain")
    spr = emu.sym("gSprites")
    ssize = emu.elf.size("gSprites") // 65 if emu.elf.size("gSprites") % 65 == 0 else 0x44
    last = None
    for i in range(n):
        cb1, cb2, vbl, hbl = emu.r32(gmain), emu.r32(gmain + 4), emu.r32(gmain + 0xC), emu.r32(gmain + 0x10)
        tasks = [(t, "%08X" % fn, nm) for t, fn, nm in emu.tasks()]
        bad = []
        for k in range(64):
            b = emu.read(spr + ssize * k, 0x20)
            cb = int.from_bytes(b[0x1C:0x20], "little")
            flags = emu.r16(spr + ssize * k + 0x3E)
            if flags & 1 and not (0x08000000 <= cb < 0x0A000000):
                bad.append((k, "%08X" % cb))
        state = (cb1, cb2, vbl, hbl, tuple(tasks), tuple(bad))
        if state != last:
            print("crashwatch +%d @%d cb1=%s cb2=%s vbl=%s hbl=%s tasks=%s badsprites=%s" % (
                i, emu.sync(), emu.elf.where(cb1), emu.elf.where(cb2), emu.elf.where(vbl), emu.elf.where(hbl), tasks, bad))
            last = state
        emu.frames(1)


def _cw_state(emu):
    gmain = emu.sym("gMain")
    cb1, cb2, vbl = emu.r32(gmain), emu.r32(gmain + 4), emu.r32(gmain + 0xC)
    tasks = tuple((t, "%08X" % fn, nm) for t, fn, nm in emu.tasks())
    return (emu.elf.where(cb1), emu.elf.where(cb2), emu.elf.where(vbl), tasks)


@script_op("burstwatch")
def _op_burstwatch(emu, f, path):
    """burstwatch PREFIX CB2 EVERY MAX KEY KEYEVERY FROMFRAME: burstuntil (rc.py) with the same
    timing, which also prints callbacks and task funcs every frame once the frame counter passes
    FROMFRAME (to see what runs just before a crash)."""
    prefix, cb, every, maxf = f[1], emu.sym(f[2]), int(f[3]), int(f[4])
    key, kev, start = f[5], int(f[6]), int(f[7])
    n, waited, last, lastst = 0, 0, None, None

    def step(k):
        nonlocal lastst
        for _ in range(k):
            if emu.sync() >= start:
                st = _cw_state(emu)
                if st != lastst:
                    print("burstwatch @%d %s" % (emu.sync(), st))
                    lastst = st
            emu.frames(1)

    while emu.cb2() == cb and waited < maxf:
        step(every)
        waited += every
        if emu.cb2() != cb:
            break
        n += 1
        p = rc._shot(emu, "%s_%03d" % (prefix, n))
        data, same = rc._same_as(p, last)
        if same:
            os.remove(p)
            emu.shots = emu.shots[:-1]
            n -= 1
        last = data
        if key != "-" and kev and waited % kev < every:
            print("burstwatch tap %s @%d" % (key, emu.sync()))
            emu.tap(key, 0)
    print("burstwatch %s: %d shot(s), %d frames, callback2 %s @%d" % (prefix, n, waited, emu.cb2_name(), emu.sync()))


if __name__ == "__main__":
    sys.argv[0] = hns.__file__
    sys.exit(hns.main())
