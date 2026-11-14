#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Save-ladder helpers for hns.py: event scripts in RAM, start-menu actions, leaving a
Pokemon Center. Registered as extra script ops through hns.script_op, so hns.py itself is
not modified; run scripts that use them through this file:

    ladder.py run SCRIPT OUTDIR [--save SAV] [--save-out SAV]   same as `hns.py run`

Extra script commands:
    event FILE.inc [MAX] [KEYS]   assemble FILE (an event script body, written like a map's
                                  scripts.inc) with the ROM's own macros (evasm.py), run it in
                                  the global script context, wait until it has ended and
                                  the player is controllable. KEYS are tapped every 30 frames
                                  meanwhile (for scripts that show messages).
    rungoto LABEL [MAX] [KEYS]    run one of the ROM's own scripts (`goto LABEL`), e.g. a
                                  town's first-visit "flagheap" trigger that ends in `end`.
    startmenu ACTION              START unless the menu is open, cursor to ACTION, A. ACTION:
                                  src/start_menu.c:58 (0 POKEDEX, 1 POKEMON, 2 BAG,
                                  3 POKENAV, 4 PLAYER, 5 SAVE, 6 OPTION, 7 EXIT).
    leavecenter [MAX]             walk DOWN out of the Pokemon Center the player stands in
                                  (as the 2.0.x upgrade procedure requires) and wait until
                                  controllable on the map outside.
    walk DIR STEPS                walk STEPS tiles in DIR, one tile per tap, waiting for
                                  each step to finish; stops early if the player cannot
                                  move (prints where it stopped).
    expectvar VAR VALUE           stop unless the save-block var has VALUE (names allowed)
    eventstart FILE.inc           start an event script and return at once (for a script that
                                  ends in a cutscene, e.g. the Hall of Fame and credits)
    playtime HOURS MINUTES        set the play clock (trainer card, CONTINUE screen)
"""
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
import hns            # noqa: E402
import evasm          # noqa: E402
from hns import HnsError, script_op   # noqa: E402

# struct ScriptContext (include/script.h:9-22) with the build's -mabi=apcs-gnu: stackDepth
# +0, mode +1, comparisonResult +2, bitfield byte +3, nativePtr +4, scriptPtr +8,
# stack[20] +0xC, cmdTable +0x5C, cmdTableEnd +0x60, data[4] +0x64; size 0x74, which is
# the ELF size of sGlobalScriptContext. cmdTable is checked live before every run.
CTX_SIZE = 0x74
CTX_SCRIPTPTR = 0x08
CTX_CMDTABLE = 0x5C
CONTEXT_RUNNING, CONTEXT_SHUTDOWN = 0, 2       # src/script.c:27-31
SCRIPT_MODE_BYTECODE = 1                      # src/script.c:21-25


def run_event(emu, path_or_text, maxframes=20000, keys=None, name=None, wait=True):
    """Assemble an event script and start it the way ScriptContext_SetupScript does
    (src/script.c:281-289): InitScriptContext state, mode BYTECODE, scriptPtr, field
    controls locked, status CONTEXT_RUNNING. CB1_Overworld runs it from the next frame.
    Waits until the context is shut down and the player is controllable. Returns frames."""
    if os.path.exists(path_or_text):
        body = open(path_or_text, encoding="utf-8").read()
        name = name or os.path.basename(path_or_text)
    else:
        body = path_or_text
    addr = emu.sym(evasm.RAM_BUFFER)
    incdirs = [os.path.dirname(os.path.abspath(path_or_text))] if os.path.exists(path_or_text) else []
    # macros and constants from the tree of the ROM under test (HNS_SRC overrides), as hns.py does
    data, _ = evasm.assemble(body, addr, emu.elf.path, src=hns.src_dir(emu.elf), name=name or "inline",
                             incdirs=incdirs)
    if len(data) > emu.elf.size(evasm.RAM_BUFFER):
        raise HnsError("event script is %d bytes, %s holds %d"
                       % (len(data), evasm.RAM_BUFFER, emu.elf.size(evasm.RAM_BUFFER)))
    if not emu.controllable():
        raise HnsError("event: player is not controllable (callback2 %s)" % emu.cb2_name())
    padded = data + b"\x00" * (-len(data) % 4)
    for i in range(0, len(padded), 4):
        emu.w32(addr + i, int.from_bytes(padded[i:i + 4], "little"))
    if emu.read(addr, len(data)) != data:
        raise HnsError("event: script bytes did not read back")
    ctx = emu.sym("sGlobalScriptContext")
    if emu.elf.size("sGlobalScriptContext") != CTX_SIZE:
        raise HnsError("sizeof(struct ScriptContext) changed; re-measure ladder.py's offsets")
    if emu.r32(ctx + CTX_CMDTABLE) != emu.sym("gScriptCmdTable"):
        raise HnsError("event: the global script context has no command table")
    emu.w32(ctx + 0, SCRIPT_MODE_BYTECODE << 8)    # stackDepth 0, mode, comparisonResult 0, bits 0
    emu.w32(ctx + 4, 0)                            # nativePtr
    emu.w32(ctx + CTX_SCRIPTPTR, addr)
    emu.w8(emu.sym("sLockFieldControls"), 1)
    status = emu.sym("sGlobalScriptContextStatus")
    emu.w8(status, CONTEXT_RUNNING)
    waited = 0
    emu.frames(2)
    if not wait:
        return 0
    while True:
        if emu.r8(status) == CONTEXT_SHUTDOWN and emu.controllable():
            break
        if waited > maxframes:
            raise HnsError("event script still running after %d frames (callback2 %s, scriptPtr %s)"
                           % (maxframes, emu.cb2_name(), emu.elf.where(emu.r32(ctx + CTX_SCRIPTPTR))))
        if keys and waited % 30 < 4:
            emu.frames(3, keys)
            emu.frames(1)
        else:
            emu.frames(4)
        waited += 4
    return waited


def start_menu_action(emu, action):
    emu.open_start_menu()
    n = emu.r8(emu.sym("sNumStartMenuActions"))
    acts = list(emu.read(emu.sym("sCurrentStartMenuActions"), n))
    if action not in acts:
        raise HnsError("start menu has no action %d: %s" % (action, acts))
    want = acts.index(action)
    cursor = emu.sym("sStartMenuCursorPos")
    emu.frames(6)                     # the menu reads input a few frames after it is drawn
    for _ in range(2 * n):
        cur = emu.r8(cursor)
        if cur == want:
            break
        emu.tap("DOWN", 6)            # the list wraps (the old code relied on that too)
    if emu.r8(cursor) != want:
        raise HnsError("start menu cursor did not reach action %d" % action)
    emu.tap("A", 0)
    return acts


T_NOT_MOVING = 0                              # include/global.fieldmap.h:409-414


def player_settled(emu):
    """The player avatar finished its step: gPlayerAvatar.tileTransitionState (+3) is
    T_NOT_MOVING (src/field_player_avatar.c:1217-1232). SB1.pos alone is not enough: the
    camera (field_camera.c CameraMove) moves it at the START of a step, and a key pressed
    before the step ends is lost."""
    return emu.r8(emu.sym("gPlayerAvatar") + 3) == T_NOT_MOVING


def step(emu, direction, maxframes=40):
    """One tile in DIRECTION (or through the warp in front of the player). Returns the new
    (group, num, x, y) once the step has finished and the player is controllable, or None
    if the player did not move (blocked) within MAXFRAMES."""
    (g, n, _, _, _), (x, y) = emu.location()
    for attempt in range(2):
        # facing DIRECTION already: an 8-frame press starts a step. Facing elsewhere: the
        # press may only turn the player in place, so press once more.
        emu.frames(8, direction)
        emu.frames(4)
        if emu.location()[1] != (x, y) or not emu.in_overworld() or not player_settled(emu) \
                or not emu.controllable():
            break
        emu.frames(12)
    waited = 8
    while waited < maxframes:
        if not emu.in_overworld():            # a warp is loading the next map
            emu.wait32(emu.CB2, emu.sym("CB2_Overworld"), 600)
            emu.wait_controllable(1200)
            (g2, n2, _, _, _), (x2, y2) = emu.location()
            return g2, n2, x2, y2
        (g2, n2, _, _, _), (x2, y2) = emu.location()
        if (g2, n2, x2, y2) != (g, n, x, y) and emu.controllable() and player_settled(emu):
            emu.frames(2)
            return g2, n2, x2, y2
        emu.frames(2)
        waited += 2
    (g2, n2, _, _, _), (x2, y2) = emu.location()
    return (g2, n2, x2, y2) if (g2, n2, x2, y2) != (g, n, x, y) else None


def leave_center(emu, maxsteps=12):
    (g, n, _, _, _), _ = emu.location()
    for _ in range(maxsteps):
        r = step(emu, "DOWN", 120)
        if r is None:
            raise HnsError("leavecenter: blocked inside %d.%d" % (g, n))
        if (r[0], r[1]) != (g, n):
            if not emu.wait_controllable(1200, "B"):
                raise HnsError("leavecenter: not controllable after leaving (callback2 %s)" % emu.cb2_name())
            return r
    raise HnsError("leavecenter: still in %d.%d after %d steps" % (g, n, maxsteps))


@script_op("event")
def _op_event(emu, f, path):
    p = os.path.join(os.path.dirname(os.path.abspath(path)), f[1])
    w = run_event(emu, p, int(f[2]) if len(f) > 2 else 20000, f[3] if len(f) > 3 else None)
    print("event %s done in %d frames @%d" % (f[1], w, emu.sync()))


@script_op("eventstart")
def _op_eventstart(emu, f, path):
    """eventstart FILE.inc: like `event`, but return as soon as the script is running, for a
    script that hands over to a cutscene that never gives control back (the Hall of Fame)."""
    p = os.path.join(os.path.dirname(os.path.abspath(path)), f[1])
    run_event(emu, p, wait=False)
    print("eventstart %s @%d" % (f[1], emu.sync()))


@script_op("rungoto")
def _op_rungoto(emu, f, path):
    """rungoto LABEL [MAX] [KEYS]: run the ROM's own script LABEL (`goto LABEL` from RAM)."""
    w = run_event(emu, "\tgoto %s\n" % f[1], int(f[2]) if len(f) > 2 else 20000,
                  f[3] if len(f) > 3 else None, name="goto_" + f[1])
    print("rungoto %s done in %d frames @%d" % (f[1], w, emu.sync()))


def warp_raw(emu, group, num, x, y):
    """Emu.warp without waiting for control or checking the position: for maps whose
    ON_FRAME script takes over at once (the Hall of Fame cutscene)."""
    if not emu.in_overworld():
        raise HnsError("warpto: not in the overworld (callback2 = %s)" % emu.cb2_name())
    sb1 = emu.sb1()
    pos, loc = sb1 + hns.OFF["SB1.pos"], sb1 + hns.OFF["SB1.location"]
    emu.w16(pos, x)
    emu.w16(pos + 2, y)
    emu.w8(loc + 0, group)
    emu.w8(loc + 1, num)
    emu.w8(loc + 2, 0xFF)
    emu.w16(loc + 4, x)
    emu.w16(loc + 6, y)
    emu.w32(emu.CB2, emu.sym("CB2_LoadMap"))
    if not emu.wait32(emu.CB2, emu.sym("CB2_Overworld"), 600):
        raise HnsError("warpto: map load did not return to CB2_Overworld (at %s)" % emu.cb2_name())


@script_op("warpto")
def _op_warpto(emu, f, path):
    """warpto GROUP NUM X Y: poke-warp and return as soon as the map is loaded."""
    warp_raw(emu, *(int(v, 0) for v in f[1:5]))
    print("warpto %s @%d" % (" ".join(f[1:5]), emu.sync()))


@script_op("startmenu")
def _op_startmenu(emu, f, path):
    a = f[1]
    acts = start_menu_action(emu, emu.START_MENU_ACTIONS[a] if a in emu.START_MENU_ACTIONS else int(a, 0))
    print("startmenu %s (menu %s) @%d" % (f[1], acts, emu.sync()))


@script_op("leavecenter")
def _op_leavecenter(emu, f, path):
    r = leave_center(emu, int(f[1]) if len(f) > 1 else 12)
    print("leavecenter: now at %d.%d (%d,%d) @%d" % (r + (emu.sync(),)))


@script_op("walk")
def _op_walk(emu, f, path):
    d, n = f[1], int(f[2])
    for i in range(n):
        r = step(emu, d)
        if r is None:
            (g, m, _, _, _), (x, y) = emu.location()
            print("walk %s: blocked after %d of %d steps at %d.%d (%d,%d)" % (d, i, n, g, m, x, y))
            break
        if not emu.controllable():
            emu.wait_controllable(600, "B")
    (g, m, _, _, _), (x, y) = emu.location()
    print("walk %s %d: at %d.%d (%d,%d) @%d" % (d, n, g, m, x, y, emu.sync()))


SB2_PLAYTIME = 0x0E      # struct SaveBlock2: u16 playTimeHours +0x0E, u8 minutes +0x10,
                         # seconds +0x11, vblanks +0x12 (include/global.h:674-683)


@script_op("playtime")
def _op_playtime(emu, f, path):
    """playtime HOURS MINUTES: set the play clock the trainer card and CONTINUE show (a
    debug-made save otherwise reads 0:00). The clock keeps running from there."""
    h, m = int(f[1]), int(f[2])
    sb2 = emu.sb2()
    before = emu.read(sb2 + SB2_PLAYTIME, 4)
    if before[0] | before[1] << 8 > 999 or before[2] > 59 or before[3] > 59:
        raise HnsError("playtime: SB2+0x%X does not look like a play clock: %s" % (SB2_PLAYTIME, before.hex()))
    emu.w16(sb2 + SB2_PLAYTIME, h)
    emu.w8(sb2 + SB2_PLAYTIME + 2, m)
    emu.w8(sb2 + SB2_PLAYTIME + 3, 0)
    print("playtime %d:%02d (was %d:%02d:%02d)" % (h, m, before[0] | before[1] << 8, before[2], before[3]))


@script_op("expectvar")
def _op_expectvar(emu, f, path):
    var = emu.const(f[1]) if hasattr(emu, "const") else int(f[1], 0)
    got = emu.get_var(var)
    if got != int(f[2], 0):
        raise HnsError("expectvar %s: %d, wanted %s" % (f[1], got, f[2]))
    print("expectvar %s = %d ok" % (f[1], got))


if __name__ == "__main__":
    sys.exit(hns.main())
