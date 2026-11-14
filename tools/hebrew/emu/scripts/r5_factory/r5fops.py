#!/usr/bin/env python3
"""Ops for the round-5 Battle Factory tours (tours/r5_factory/*.txt), on top of bffops.py
(sb2w16 / sb2w32 / saveyes / bwin / blose / drivex) and r3bf.py (drive / pick, and r2sf's ss / sl).
Run:  r5fops.py tour ROM OUT --tours tools/hebrew/emu/tours/r5_factory [--clip] [--only RE]

    approachnpc LOCALID       wait until the (wandering) NPC LOCALID stands still, freeze it there,
                              walk the player to the tile below it and face UP
    waitmap NAME MAP [MAX]    run until the player is on MAP in the overworld with no fade, shoot NAME
    evdrive PREFIX TARGET STATEMENT; ...
                              start an event script (evstart) and walk its text like `drivex`
                              until TARGET (free | menu | battle | cb2:SYM | task:SYM)
    snapat NAME FRAMES        run FRAMES frames, then shoot NAME (a scene with no text, e.g. a walk-in)
    setflagx FLAG 0|1         set or clear a save-block flag by name
    frontierinfo              print the Factory streaks, battle number and challenge status
"""
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(HERE, "..", ".."))                                # tools/hebrew/emu
sys.path.insert(0, os.path.join(HERE, "..", "r2_battle_frontier_facilities"))
sys.path.insert(0, os.path.join(HERE, "..", "r3_frontier"))
sys.path.insert(0, os.path.join(HERE, "..", "r2_safari_pokeblock_bug_contest"))
import hns  # noqa: E402
import bffops  # noqa: E402,F401  (registers sb2w16 / saveyes / bwin / drivex, and r3bf's ops)
import r3bf  # noqa: E402
from hns import script_op, HnsError, SCRIPT_OPS, _arg  # noqa: E402

OBJ_SIZE = 0x24            # struct ObjectEvent, gObjectEvents[16]
MAP_OFFSET = 7


def _npc(emu, lid):
    (g, m, _, _, _), _ = emu.location()
    base = emu.sym("gObjectEvents")
    for i in range(16):
        a = base + i * OBJ_SIZE
        if emu.r8(a) & 1 and emu.r8(a + 8) == lid and emu.r8(a + 9) == m and emu.r8(a + 10) == g:
            return a
    raise HnsError("no object %d on map %d.%d" % (lid, g, m))


@script_op("approachnpc")
def _op_approachnpc(emu, f, path):
    lid = int(f[1], 0)
    a = _npc(emu, lid)
    still = lambda: (not emu.r8(a) & 2 and emu.r16(a + 0x10) == emu.r16(a + 0x14)
                     and emu.r16(a + 0x12) == emu.r16(a + 0x16))
    emu.wait_until(still, 600, "NPC %d to stand still" % lid, step=1)
    emu.w8(a + 1, emu.r8(a + 1) | 1)
    nx, ny = emu.r16(a + 0x10) - MAP_OFFSET, emu.r16(a + 0x12) - MAP_OFFSET
    tx, ty = nx, ny + 1
    for _ in range(30):
        _, (x, y) = emu.location()
        if (x, y) == (tx, ty):
            break
        if x != tx and y == ny:
            d = "DOWN"
        elif x != tx:
            d = "RIGHT" if x < tx else "LEFT"
        else:
            d = "DOWN" if y < ty else "UP"
        r = hns.go_step(emu, d)
        if r != "step":
            raise HnsError("approachnpc %d: blocked going %s at (%d,%d), NPC at (%d,%d)" % (lid, d, x, y, nx, ny))
    _, (x, y) = emu.location()
    if (x, y) != (tx, ty):
        raise HnsError("approachnpc %d: player at (%d,%d), wanted (%d,%d)" % (lid, x, y, tx, ty))
    emu.frames(2, "UP")
    emu.frames(14)
    print("approachnpc %d: NPC at (%d,%d), player below @%d" % (lid, nx, ny, emu.sync()))


@script_op("approachright")
def _op_approachright(emu, f, path):
    """approachright LOCALID: like approachnpc, but the player walks to the tile right of the NPC
    (x first, then y; y first if that is blocked) and faces LEFT (an NPC on a bottom row)."""
    lid = int(f[1], 0)
    a = _npc(emu, lid)
    still = lambda: (not emu.r8(a) & 2 and emu.r16(a + 0x10) == emu.r16(a + 0x14)
                     and emu.r16(a + 0x12) == emu.r16(a + 0x16))
    emu.wait_until(still, 600, "NPC %d to stand still" % lid, step=1)
    emu.w8(a + 1, emu.r8(a + 1) | 1)
    nx, ny = emu.r16(a + 0x10) - MAP_OFFSET, emu.r16(a + 0x12) - MAP_OFFSET
    tx, ty = nx + 1, ny
    for order in ("xy", "yx"):
        for _ in range(30):
            _, (x, y) = emu.location()
            if (x, y) == (tx, ty):
                break
            if (order == "xy" and x != tx) or (order == "yx" and y == ty):
                d = "RIGHT" if x < tx else "LEFT"
            else:
                d = "DOWN" if y < ty else "UP"
            if hns.go_step(emu, d) != "step":
                break
        if emu.location()[1] == (tx, ty):
            break
    _, (x, y) = emu.location()
    if (x, y) != (tx, ty):
        raise HnsError("approachright %d: player at (%d,%d), wanted (%d,%d)" % (lid, x, y, tx, ty))
    emu.frames(2, "LEFT")
    emu.frames(14)
    print("approachright %d: NPC at (%d,%d), player right of it @%d" % (lid, nx, ny, emu.sync()))


@script_op("waitmap")
def _op_waitmap(emu, f, path):
    name, mapname = f[1], f[2]
    mx = _arg(f, 3, 3000)
    g, n = hns.map_lookup(emu.elf, mapname)
    ow = emu.sym("CB2_Overworld")

    def there():
        (lg, ln, _, _, _), _pos = emu.location()
        return lg == g and ln == n and emu.cb2() == ow and not emu.fading()
    emu.wait_until(there, mx, "map %s" % mapname, step=2)
    emu.frames(8)
    if name != "-":
        r3bf._shot(emu, name)
    print("waitmap %s: %s @%d" % (name, mapname, emu.sync()))


@script_op("evdrive")
def _op_evdrive(emu, f, path):
    prefix, target = f[1], f[2]
    body = hns.event_body(" ".join(f[3:]), path)
    hns.event_start(emu, body, "evdrive_" + prefix)
    SCRIPT_OPS["drivex"](emu, ["drivex", prefix, target, "30", "6000"], path)


@script_op("driveleave")
def _op_driveleave(emu, f, path):
    """driveleave PREFIX [MAX]: walk field text like `drivex` (a shot per page and per line that
    waits for no key) until callback2 leaves CB2_Overworld for good (a soft reset)."""
    prefix = f[1]
    mx = _arg(f, 2, 3000)
    ow = emu.sym("CB2_Overworld")
    n, waited, prev, last = 0, 0, "idle", None
    while waited < mx:
        if emu.cb2() != ow:
            print("driveleave %s: %d shot(s), left the overworld (%s) @%d" % (prefix, n, emu.cb2_name(), emu.sync()))
            return
        st = emu.text_state()
        if st == "busy":
            prev = "busy"
        elif emu.wants_key() or prev == "busy":
            emu.frames(4)
            box = hns.message_box(emu)
            if box is not None and box != last:
                n += 1
                r3bf._shot(emu, "%s_%02d" % (prefix, n))
                last = box
            if emu.wants_key():
                emu.tap("A", 0)
                emu.wait_until(lambda: not emu.wants_key(), 90, "the text to take the key", step=1)
            prev = "idle"
        emu.frames(2)
        waited += 2
    raise hns.TourTimeout("driveleave %s: still in the overworld after %d frames" % (prefix, mx))


@script_op("snapat")
def _op_snapat(emu, f, path):
    emu.frames(int(f[2]))
    r3bf._shot(emu, f[1])
    print("snapat %s @%d" % (f[1], emu.sync()))


@script_op("setflagx")
def _op_setflagx(emu, f, path):
    emu.set_flag(emu.const(f[1]), f[2] != "0")
    print("setflagx %s %s @%d" % (f[1], f[2], emu.sync()))


@script_op("frontierinfo")
def _op_frontierinfo(emu, f, path):
    F = bffops.FRONTIER
    b = emu.sb2()
    print("frontierinfo streaks %s records %s rents %s active %08X battleNum %d BP %d @%d" % (
        [emu.r16(b + F["factoryWinStreaks"] + 2 * i) for i in range(4)],
        [emu.r16(b + F["factoryRecordWinStreaks"] + 2 * i) for i in range(4)],
        [emu.r16(b + F["factoryRentsCount"] + 2 * i) for i in range(4)],
        emu.r32(b + F["winStreakActiveFlags"]), emu.r16(b + F["curChallengeBattleNum"]),
        emu.r16(b + F["battlePoints"]), emu.sync()))


if __name__ == "__main__":
    sys.argv[0] = hns.__file__
    sys.exit(hns.main())
