#!/usr/bin/env python3
"""svc.py (hns.py + textwatch/scenewatch/burst/scrollshots/scrollmem) plus ops for the overworld
field UI screens (follower talk, fishing, spray menu, field poison, wall clock, phone list):

    setbit HEXADDR BIT 0|1        read-modify-write one bit of a byte (SaveBlock3 challenge
                                  settings: `setbit @SB3+10@ 4 1` turns the fishing minigame on,
                                  `setbit @SB3+2C@ 1 0` turns survive-poison off; offsets read
                                  from the ldrb/lsls in Fishing_GotBite and DoPoisonFieldEffect)
    w16c HEXADDR CONST            write a C constant (ITEM_*, SPECIES_*) as u16, e.g. the SELECT
                                  item gSaveBlock1Ptr->registeredItem at SB1+0x49A (literal in
                                  UseRegisteredKeyItemOnField)
    fishwatch PREFIX hook|miss [MAX]
                                  after SELECT starts Task_Fishing: shot PREFIX_dotsNN each time a
                                  dot is added (tNumDots, data[2]), PREFIX_bite when a bite waits
                                  for A (tStep FISHING_WAIT_FOR_A = 8; A is pressed for `hook`,
                                  not for `miss`), and PREFIX_<outcome> when the result text waits
                                  for a key: hook (FISHING_START_ENCOUNTER), nibble
                                  (FISHING_NOT_EVEN_NIBBLE), gotaway (FISHING_GOT_AWAY).
                                  Prints the outcome; the battle of a hook is left to the tour.
    forcecall [MAXSTEPS]          make the next steps start a registered trainer's call: before each
                                  step set sMatchCallState.minutes = 0 and stepCounter = 29
                                  (struct MatchCallState, src/match_call.c:97-103; TryStartMatchCall
                                  :1384-1411 then only rolls CheckMatchCallChance, 30%), walk
                                  LEFT/RIGHT, stop once ExecuteMatchCall runs
    expectvar VAR VALUE           stop unless the var holds VALUE
    showvar VAR...                print vars (debugging)

Usage: ofui.py <hns.py args>, e.g.
    HNS_SAVES=... HNS_SRC=<tree of the ROM> python3 ofui.py tour ROM OUT --tours THIS_DIR --only RE [--clip]
"""
import os
import sys
HERE = os.path.dirname(os.path.abspath(__file__))
EMU = os.path.abspath(os.path.join(HERE, "..", ".."))
sys.path.insert(0, os.path.join(EMU, "scripts", "r1_npc_services"))     # svc.py
sys.path.insert(0, EMU)
import hns                      # noqa: E402
import svc                      # noqa: E402,F401  (registers its ops)
from hns import script_op, HnsError, TourTimeout, _arg   # noqa: E402

# enum in src/fishing.c:90-109
FISH_SHOW_DOTS, FISH_WAIT_FOR_A, FISH_MON_ON_HOOK, FISH_START_ENCOUNTER = 4, 8, 11, 12
FISH_NOT_EVEN_NIBBLE, FISH_GOT_AWAY, FISH_NO_MON, FISH_PUT_ROD_AWAY, FISH_END_NO_MON = 13, 14, 15, 16, 17


def _shot(emu, name):
    emu.shot(name)
    emu.shots = getattr(emu, "shots", []) + [name]


@script_op("setbit")
def _op_setbit(emu, f, path):
    addr, bit, val = int(f[1], 16), int(f[2]), int(f[3])
    old = emu.r8(addr)
    new = (old | (1 << bit)) if val else (old & ~(1 << bit))
    emu.w8(addr, new)
    print("setbit %08X.%d = %d (%02X -> %02X)" % (addr, bit, val, old, emu.r8(addr)))


@script_op("w16c")
def _op_w16c(emu, f, path):
    addr, val = int(f[1], 16), emu.const(f[2])
    emu.w16(addr, val)
    print("w16c %08X = %s (%d)" % (addr, f[2], val))


@script_op("expectvar")
def _op_expectvar(emu, f, path):
    got = emu.get_var(emu.const(f[1]))
    if got != emu.const(f[2]):
        raise HnsError("expectvar %s: %d, wanted %s" % (f[1], got, f[2]))
    print("expectvar %s = %d ok" % (f[1], got))


@script_op("showvar")
def _op_showvar(emu, f, path):
    print("showvar " + " ".join("%s=%d" % (v, emu.get_var(emu.const(v))) for v in f[1:]))


@script_op("forcecall")
def _op_forcecall(emu, f, path):
    maxsteps = _arg(f, 1, 40)
    st = emu.sym("sMatchCallState")
    for i in range(maxsteps):
        emu.w32(st, 0)
        emu.w8(st + 6, 29)
        d = "LEFT" if i % 2 == 0 else "RIGHT"
        emu.frames(10, d)
        for _ in range(40):
            emu.frames(2)
            if emu.task_active("ExecuteMatchCall"):
                print("forcecall: call after %d step(s), trainer %d @%d" % (i + 1, emu.r16(st + 4), emu.sync()))
                return
        emu.wait_controllable(300)
    raise TourTimeout("forcecall: no call after %d steps" % maxsteps)


def _fish(emu):
    d = emu.task_data("Task_Fishing")
    return d[0] if d else None


@script_op("fishwatch")
def _op_fishwatch(emu, f, path):
    prefix, mode, maxf = f[1], f[2], _arg(f, 3, 3000)
    emu.wait_until(lambda: _fish(emu) is not None, 120, "Task_Fishing to start", step=1)
    dots, waited, bites, outcome = -1, 0, 0, None
    while waited < maxf:
        d = _fish(emu)
        if d is None:
            outcome = outcome or "ended"
            break
        step, ndots = d[0], d[2]
        if step == FISH_SHOW_DOTS and ndots != dots and ndots > 0:
            emu.frames(2)
            dots = ndots
            _shot(emu, "%s_r%d_dots%02d" % (prefix, bites, ndots))
            continue
        if step == FISH_WAIT_FOR_A:
            bites += 1
            emu.frames(2)
            _shot(emu, "%s_r%d_bite" % (prefix, bites))
            dots = -1
            if mode == "hook":
                emu.tap("A", 0)
            emu.wait_until(lambda: _fish(emu) is None or _fish(emu)[0] != FISH_WAIT_FOR_A, 120,
                           "the bite to resolve", step=1)
            continue
        if step in (FISH_START_ENCOUNTER, FISH_NO_MON, FISH_PUT_ROD_AWAY, FISH_END_NO_MON):
            name = "hook" if step == FISH_START_ENCOUNTER else ("gotaway" if bites else "nibble")
            emu.wait_until(emu.wants_key, 600, "the fishing result text", step=1)
            emu.frames(2)
            _shot(emu, "%s_%s" % (prefix, name))
            outcome = name
            emu.tap("A", 0)
            break
        emu.frames(1)
        waited += 1
    print("fishwatch %s %s: outcome %s, %d bite(s) @%d" % (prefix, mode, outcome, bites, emu.sync()))


if __name__ == "__main__":
    sys.argv[0] = hns.__file__
    sys.exit(hns.main())
