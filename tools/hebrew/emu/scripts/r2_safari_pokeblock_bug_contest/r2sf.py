#!/usr/bin/env python3
"""hns.py plus the tour ops the r2sf_* tours (Safari Zone, Pokeblocks, Berry Blender, Bug-Catching
Contest) use. Run:  r2sf.py tour ROM OUT --tours <this folder> [--clip] [--only RE]

From the r1 services set (scripts/r1_npc_services/svc.py):
    textwatch PREFIX UNTILCB2 [MAX] [KEY]   shots whenever a text printer finishes or waits for a key
    burst PREFIX COUNT EVERY                COUNT shots EVERY frames apart, identical frames dropped
    scenewatch PREFIX UNTILCB2 MAX Y0 Y1 [KEY] [KEYEVERY]   shots when rows Y0..Y1 change and settle
    scrollshots PREFIX KEY [MAX] [IDLE]     press KEY and shoot until the screen stops changing
    scrollmem PREFIX KEY HEXADDR [MAX] [WIDTH]
Added here:
    warpraw MAP X Y          warp without waiting for the player to be free (ON_FRAME scenes)
    startmenux ACTIONID [nopress]   start menu by numeric MENU_ACTION_* (8 Safari RETIRE, 15 contest RETIRE)
    ss NAME / sl NAME        savestate to / from OUTDIR/NAME.ss
    loc                      print map and position
    playwhile PREFIX CB2 MAX SHOTEVERY KEY KEYEVERY [MAXSHOTS]
    blendplay PREFIX MAX SHOTEVERY [MAXSHOTS] [best|good|none]   play the Berry Blender
    bagseek ITEM [MAX]       move the bag cursor onto ITEM in the open pocket
    bagpocket N              switch the open bag to pocket N
    waitwarp [MAX]           wait for a map load (CB2_DoChangeMap/LoadMap/LoadMap2), then the overworld
"""
import os, sys
sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", ".."))  # tools/hebrew/emu
import hns
from hns import script_op, HnsError, _arg


def _shot(emu, name):
    emu.shot(name)
    emu.shots = getattr(emu, "shots", []) + [name]
    return os.path.join(emu.outdir, name + ".png")


@script_op("textwatch")
def _op_textwatch(emu, f, path):
    prefix, until = f[1], emu.sym(f[2])
    maxf = _arg(f, 3, 3000)
    key = f[4] if len(f) > 4 else "A"
    n, waited, prev = 0, 0, "idle"
    last = None
    while waited < maxf:
        if emu.cb2() == until:
            break
        st = emu.text_state()
        if (prev == "busy" and st != "busy") or st == "key":
            emu.frames(3)
            n += 1
            p = _shot(emu, "%s_%02d" % (prefix, n))
            data = open(p, "rb").read() if os.path.exists(p) else None
            if data is not None and data == last:
                os.remove(p); n -= 1
            last = data
            if st == "key" and key != "-":
                emu.tap(key, 0)
                emu.wait_until(lambda: emu.text_state() != "key", 120, "text to take the key", step=1)
            st = emu.text_state()
        prev = st
        emu.frames(2)
        waited += 2
    print("textwatch %s: %d shot(s), %d frames, callback2 %s @%d" % (prefix, n, waited, emu.cb2_name(), emu.sync()))


@script_op("burst")
def _op_burst(emu, f, path):
    prefix, count, every = f[1], int(f[2]), int(f[3])
    last, n = None, 0
    for i in range(count):
        emu.frames(every)
        n += 1
        p = _shot(emu, "%s_%02d" % (prefix, n))
        emu.sync()
        data = open(p, "rb").read()
        if data == last:
            os.remove(p); n -= 1
        last = data
    print("burst %s: %d distinct @%d" % (prefix, n, emu.sync()))


@script_op("scenewatch")
def _op_scenewatch(emu, f, path):
    """scenewatch PREFIX UNTILCB2 MAX Y0 Y1 [KEY] [KEYEVERY]: sample the screen every 6 frames
    until callback2 == UNTILCB2; keep a shot PREFIX_NN when rows Y0..Y1 changed from the last
    kept shot and are stable over two samples (a message drawn at once, not through a text
    printer). Taps KEY every KEYEVERY frames ('-' = never)."""
    prefix, until, maxf, y0, y1 = f[1], emu.sym(f[2]), int(f[3]), int(f[4]), int(f[5])
    key = f[6] if len(f) > 6 else "-"
    kev = int(f[7]) if len(f) > 7 else 90
    tmp = "_scan"
    kept, prev, n, waited = None, None, 0, 0
    while waited < maxf and emu.cb2() != until:
        emu.frames(6)
        waited += 6
        if key != "-" and waited % kev < 6:
            emu.tap(key, 0)
        emu.expect_after("shot %s" % tmp, r"^shot %s @" % tmp)
        pth = os.path.join(emu.outdir, tmp + ".png")
        w, h, rows = hns.read_png_rgb(pth)
        reg = b"".join(rows[y0:y1])
        if reg == prev and reg != kept:
            n += 1
            os.replace(pth, os.path.join(emu.outdir, "%s_%02d.png" % (prefix, n)))
            emu.shots = getattr(emu, "shots", []) + ["%s_%02d" % (prefix, n)]
            if getattr(emu, "clip", None):
                emu.clip.poll("%s_%02d" % (prefix, n))
            kept = reg
        prev = reg
    tp = os.path.join(emu.outdir, tmp + ".png")
    if os.path.exists(tp):
        os.remove(tp)
    print("scenewatch %s: %d shot(s), %d frames, callback2 %s @%d" % (prefix, n, waited, emu.cb2_name(), emu.sync()))


@script_op("scrollshots")
def _op_scrollshots(emu, f, path):
    """scrollshots PREFIX KEY [MAX] [IDLE]: snap PREFIX_01, then press KEY and snap again until
    the screen stops changing (the end of a list) or MAX shots; the repeated last shot is dropped."""
    prefix, key, mx, idle = f[1], f[2], _arg(f, 3, 60), _arg(f, 4, 4)
    n, last = 0, None
    while n < mx:
        emu.wait_quiet(900)
        emu.frames(2)
        n += 1
        p = _shot(emu, "%s_%02d" % (prefix, n))
        data = open(p, "rb").read()
        if data == last:
            os.remove(p); n -= 1
            emu.shots = emu.shots[:-1]
            break
        last = data
        emu.tap(key, idle)
    print("scrollshots %s: %d shot(s) @%d" % (prefix, n, emu.sync()))


@script_op("scrollmem")
def _op_scrollmem(emu, f, path):
    """scrollmem PREFIX KEY HEXADDR [MAX] [WIDTH]: snap PREFIX_01, press KEY, snap ... while the
    WIDTH-bit value at ADDR (a list cursor/scroll state) keeps changing; stops at the list end."""
    prefix, key, addr, mx = f[1], f[2], int(f[3], 16), _arg(f, 4, 80)
    width = _arg(f, 5, 32)
    rd = {8: emu.r8, 16: emu.r16, 32: emu.r32}[width]
    n = 0
    while n < mx:
        emu.wait_quiet(900)
        emu.frames(2)
        n += 1
        _shot(emu, "%s_%02d" % (prefix, n))
        before = rd(addr)
        emu.tap(key, 6)
        emu.wait_quiet(900)
        if rd(addr) == before:
            break
    print("scrollmem %s: %d shot(s) @%d" % (prefix, n, emu.sync()))


@script_op("warpraw")
def _op_warpraw(emu, f, path):
    """warpraw MAP X Y: like warpto, but returns once the map is loaded (CB2_Overworld), without
    waiting for the player to be free: for maps whose ON_FRAME script starts a scene at once."""
    g, n = hns.map_lookup(emu.elf, f[1])
    if not emu.in_overworld():
        raise HnsError("warpraw: not in the overworld (%s)" % emu.cb2_name())
    x, y = int(f[2], 0), int(f[3], 0)
    sb1 = emu.sb1()
    pos, loc = sb1 + hns.OFF["SB1.pos"], sb1 + hns.OFF["SB1.location"]
    emu.w16(pos, x); emu.w16(pos + 2, y)
    emu.w8(loc, g); emu.w8(loc + 1, n); emu.w8(loc + 2, 0xFF)
    emu.w16(loc + 4, x); emu.w16(loc + 6, y)
    emu.w32(emu.CB2, emu.sym("CB2_LoadMap"))
    if not emu.wait32(emu.CB2, emu.sym("CB2_Overworld"), 600):
        raise HnsError("warpraw: map load did not finish (%s)" % emu.cb2_name())
    print("warpraw %s (%d.%d) %d %d @%d" % (f[1], g, n, x, y, emu.sync()))


@script_op("startmenux")
def _op_startmenux(emu, f, path):
    """startmenux ACTIONID [nopress]: startmenu by the numeric MENU_ACTION_* id (src/start_menu.c:58),
    e.g. 8 RETIRE_SAFARI, 15 RETIRE_BUG_CONTEST."""
    if emu.controllable():           # gMenuCallback keeps HandleStartMenuInput after the menu closes
        emu.open_start_menu()
        emu.frames(12)
        emu.wait_quiet(300)
    emu.start_menu_cursor(int(f[1], 0), press=not (len(f) > 2 and f[2] == "nopress"))


@script_op("ss")
def _op_ss(emu, f, path):
    """ss NAME: savestate to OUTDIR/NAME.ss."""
    p = os.path.join(emu.outdir, f[1] + ".ss")
    emu.send("ss %s" % p)
    print("ss %s @%d" % (p, emu.sync()))


@script_op("sl")
def _op_sl(emu, f, path):
    """sl NAME: load the savestate OUTDIR/NAME.ss."""
    p = os.path.join(emu.outdir, f[1] + ".ss")
    emu.send("sl %s" % p)
    emu._bw_box = None
    print("sl %s @%d" % (p, emu.sync()))


@script_op("loc")
def _op_loc(emu, f, path):
    """loc: print the player's map and position."""
    print("loc %s @%d" % (emu.location(), emu.sync()))


@script_op("playwhile")
def _op_playwhile(emu, f, path):
    """playwhile PREFIX CB2 MAX SHOTEVERY KEY KEYEVERY [MAXSHOTS]: while callback2 == CB2 (e.g. the
    Berry Blender game, CB2_PlayBlender), tap KEY every KEYEVERY frames and keep a shot every
    SHOTEVERY frames (at most MAXSHOTS, default 12)."""
    prefix, cb, maxf, se, key, ke = f[1], emu.sym(f[2]), int(f[3]), int(f[4]), f[5], int(f[6])
    maxshots = _arg(f, 7, 12)
    waited, n = 0, 0
    while emu.cb2() == cb and waited < maxf:
        emu.frames(1)
        waited += 1
        if key != "-" and waited % ke == 0:
            emu.tap(key, 0)
            waited += 3
        if waited % se == 0 and n < maxshots:
            n += 1
            _shot(emu, "%s_%02d" % (prefix, n))
            if getattr(emu, "clip", None):
                pass
    print("playwhile %s: %d shot(s), %d frames, callback2 %s @%d" % (prefix, n, waited, emu.cb2_name(), emu.sync()))


# struct BerryBlender (src/berry_blender.c:143-194), offsets by the struct's own alignment rules:
# arrowPos u16 @74, speed s16 @76, gameEndState u8 @99, playerIdToArrowId u16[4] @150,
# progressBarValue u16 @278.
BB_ARROWPOS, BB_ARROWID, BB_PROGRESS = 74, 150, 278


@script_op("blendplay")
def _op_blendplay(emu, f, path):
    """blendplay PREFIX MAX SHOTEVERY [MAXSHOTS] [MODE]: play the Berry Blender while callback2 is
    CB2_PlayBlender: press A when the arrow is in the player's BEST window (GetArrowProximity,
    src/berry_blender.c:1514; MODE 'good' presses at the start of the GOOD window, 'none'
    never), keep a shot every SHOTEVERY frames."""
    prefix, maxf, se = f[1], int(f[2]), int(f[3])
    maxshots = _arg(f, 4, 12)
    mode = f[5] if len(f) > 5 else "best"
    cb = emu.sym("CB2_PlayBlender")
    bb = emu.r32(emu.sym("sBerryBlender"))
    starts = emu.read(emu.sym("sArrowHitRangeStart"), 4)
    arrow = emu.r16(bb + BB_ARROWID)
    start = starts[arrow]
    lo, hi = (start + 20, start + 28) if mode == "best" else (start, start + 20)
    waited, n, nextshot, inwin, presses = 0, 0, se, False, 0
    while emu.cb2() == cb and waited < maxf:
        pos = emu.r16(bb + BB_ARROWPOS) // 256 + 24
        now = lo <= pos < hi
        if now and not inwin and mode != "none":
            emu.frames(1, "A")
            presses += 1
        else:
            emu.frames(1)
        inwin = now
        waited += 1
        if waited >= nextshot and n < maxshots:
            n += 1
            nextshot += se
            _shot(emu, "%s_%02d" % (prefix, n))
    print("blendplay %s: %d shot(s), %d presses, %d frames, progress %d, callback2 %s @%d"
          % (prefix, n, presses, waited, emu.r16(bb + BB_PROGRESS) if emu.cb2() == cb else -1, emu.cb2_name(), emu.sync()))


@script_op("bagseek")
def _op_bagseek(emu, f, path):
    """bagseek ITEM [MAXPRESSES]: in the open bag, on the current pocket (gBagPosition.pocket), press
    DOWN until the cursor is on ITEM. Reads gBagPockets[pocket].itemSlots (include/item.h:88-93; a slot
    is enum Item itemId + u16 quantity) and gBagPosition.cursorPosition/scrollPosition (u16[6] at
    +8 / +20, include/item_menu.h:59-67)."""
    item = emu.const(f[1])
    bp = emu.sym("gBagPosition")
    pocket = emu.r8(bp + 5)
    slots = emu.r32(emu.sym("gBagPockets") + 8 * pocket)
    raw = emu.read(slots, 8 * 64)
    stride = 8 if all(raw[i * 8 + 2:i * 8 + 4] == b"\0\0" for i in range(4)) else 4
    idx = None
    for i in range(len(raw) // stride):
        v = int.from_bytes(raw[i * stride:i * stride + 2], "little")
        if v == item:
            idx = i
            break
    if idx is None:
        raise HnsError("bagseek: %s not in pocket %d" % (f[1], pocket))
    for _ in range(_arg(f, 2, 80)):
        cur = emu.r16(bp + 8 + 2 * pocket) + emu.r16(bp + 20 + 2 * pocket)
        if cur == idx:
            print("bagseek %s: pocket %d slot %d (stride %d) @%d" % (f[1], pocket, idx, stride, emu.sync()))
            return
        emu.tap("DOWN" if cur < idx else "UP", 4)
        emu.wait_quiet(600)
    raise HnsError("bagseek: cursor did not reach slot %d" % idx)


@script_op("bagpocket")
def _op_bagpocket(emu, f, path):
    """bagpocket N: in the open bag, press RIGHT (waiting for each pocket switch to finish) until
    gBagPosition.pocket == N."""
    want = int(f[1])
    bp = emu.sym("gBagPosition")
    for _ in range(8):
        emu.wait_quiet(600)
        emu.wait_until(lambda: emu.task_active("Task_BagMenu_HandleInput"), 600, "the bag to read input")
        emu.frames(4)
        if emu.r8(bp + 5) == want:
            print("bagpocket %d ok @%d" % (want, emu.sync()))
            return
        emu.tap("RIGHT", 4)
        emu.frames(20)
    raise HnsError("bagpocket: pocket stayed %d" % emu.r8(bp + 5))


@script_op("waitwarp")
def _op_waitwarp(emu, f, path):
    """waitwarp [MAX]: run until callback2 leaves CB2_Overworld (a warp started), then until it is
    CB2_Overworld again."""
    mx = _arg(f, 1, 1200)
    ow = emu.sym("CB2_Overworld")
    loads = set()
    for n in ("CB2_DoChangeMap", "CB2_LoadMap", "CB2_LoadMap2"):
        try:
            loads.add(emu.sym(n))
        except HnsError:
            pass
    emu.wait_until(lambda: emu.cb2() in loads, mx, "a map load", step=1)
    emu.wait_until(lambda: emu.cb2() == ow, mx, "the warp to end", step=2)
    print("waitwarp ok @%d" % emu.sync())


if __name__ == "__main__":
    sys.argv[0] = hns.__file__
    sys.exit(hns.main())
