#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Drive the headless Heart & Soul runner (hnsrun) with live memory access.

    hns.py [--rom ROM] [--elf ELF] run SCRIPT OUTDIR [--save SAV] [--keep-save]
    hns.py [--rom ROM] [--elf ELF] warp OUTDIR GROUP NUM X Y --save SAV [--then SCRIPT]
    hns.py [--elf ELF] sym NAME...          print a symbol's address (Thumb bit included)
    hns.py [--elf ELF] where HEXADDR...     nearest symbol at or below an address
    hns.py [--elf ELF] map PATTERN          MAP_* constants matching PATTERN -> group, num
    hns.py offsets                          struct offsets this file pokes
    hns.py selfcheck [--save SAV]           check those offsets against the ELF and a live game
    hns.py [--elf ELF] render SCRIPT        expand includes + static @SYMBOL@s for bare hnsrun
    hns.py tour ROM OUTDIR [--only RE] [--reuse-saves]   run the screen tours in emu/tours
                                            (OK / CRASH / TIMEOUT / ERROR per tour,
                                            OUTDIR/tour_report.json)
    hns.py tourdiff OUTDIR1 OUTDIR2         compare two tour runs screenshot by screenshot
    hns.py sheet OUT.png PNG|DIR... [--cols N]   tile screenshots into a contact sheet

ROM and ELF default to the build in HNS_TREE (HNS_ROM / HNS_ELF override them;
--rom X alone implies the ELF next to it). Every address is resolved from the ELF at run
time, so a rebuild needs no edits here. The struct offsets below cannot come from the
ELF (it carries no DWARF for C code); they were measured with an offsetof() probe
compiled against include/ (probe/measure.sh) and `selfcheck` verifies them on a
live game.

hnsrun is driven interactively: each script line is sent when the previous one has
finished, so anything that depends on game state is evaluated at that moment. That is
what makes @SB1@ safe: the save block MOVES on every map load and battle
(src/load_save.c:79 SetSaveBlocksPointers adds Random() to the base), so it is re-read
from gSaveBlock1Ptr immediately before each line that uses it.

Script language = hnsrun's (see hnsrun.c), plus:
    @NAME@  @NAME+HEX@  @NAME-HEX@  an ELF symbol (functions keep their Thumb bit)
    @SB1@ @SB2@ @SB3@ (+/-HEX)      live gSaveBlock1Ptr / 2Ptr / 3Ptr values
    @CB1@ @CB2@                     &gMain.callback1 / &gMain.callback2
    @LOC@ @POS@                     &gSaveBlock1Ptr->location / ->pos (live)
    FILE:NAME                       a static that several files define, e.g.
                                    @title_screen:MainCB2@ (file = object in the .map)
    ROWNEXT ROWPREV                 key names: the key that moves an options / challenge
                                    menu value row to its next / previous value, or a
                                    2x2 item context grid to its next / previous column
                                    (RIGHT / LEFT, swapped on a TEXT_RTL build, see
                                    Emu.rowkeys)
    include FILE                    splice another script (path relative to this one)
    ifsym SYMBOL ... endif          run the lines between only when the ELF defines SYMBOL
                                    (a step that only one build has, e.g. a yes/no that
                                    a config option compiles in)
    waitcb2 SYMBOL [MAX] [KEYS]     run until gMain.callback2 == SYMBOL (KEYS tapped
                                    every 30 frames meanwhile, like hnsrun's wait32)
    waittask SYMBOL [MAX] [KEYS]    run until a task with func SYMBOL is active (gTasks)
    waitctl [MAX] [KEYS]            run until the player can walk (see Emu.controllable)
    expect8|16|32 HEXADDR HEXVAL    stop with an error unless memory matches
    expectflag FLAG 0|1             stop unless the save-block flag has that value
    expectloc GROUP NUM [X Y]       stop unless the player is there
    warp GROUP NUM X Y              warp from the overworld (see Emu.warp)
    savegame [overwrite]            START > SAVE > YES, wait until the menu closes
    debugmenu                       R+START, wait for the debug menu (scripts/debug_demo.txt)
    setflag FLAG / clearflag FLAG   flip a bit in gSaveBlock1Ptr->flags (live)
    setvar VARID HEXVAL             write gSaveBlock1Ptr->vars[VARID - 0x4000]
    echo TEXT                       print TEXT (for logs)
Tour commands (registered with @script_op; each waits on game state, never on text
length; see the docstrings below):
    start SAVE | keepsave NAME | snap NAME | press KEY | talk PREFIX [N] [KEY] [STOPTASK..]
    pages PREFIX | waitquiet | waitkey | waitptr VAR FUNC | waitpmem W PTR OFF VAL |
    waitmem W ADDR VAL | waittaskx T | waitnotask T | waittaskdata T IDX VAL | waitcb2x CB |
    seek W ADDR VAL KEY | go DIR [N] | face DIR | warpto MAP X Y | startmenu ACTION |
    dbg I.. | givemon/giveegg/giveitem | waitnav | radiotune POS | radioline N | showtasks
Battle tour commands (part B; section "battle tours" below):
    ev SCRIPT;.. | evstart SCRIPT;.. | pinrng [HEX] | unpinrng | fastbattles on|off |
    waitbattle | bwalk PREFIX [EXPECT] | baction ACTION | bmove SLOT | waitbinput FUNC |
    expectbcmd CMD | sethp SIDE SLOT HP | waitnaming | waitnotfree
Jumping to a screen (FireRed's screen.py) is one line: w32 @CB2@ @CB2_InitTitleScreen@
Numbers in hnsrun lines are hex; in the extra commands GROUP/NUM/X/Y/FLAG accept 0x.. or
decimal.
"""
import argparse
import json
import os
import queue
import re
import shutil
import subprocess
import sys
import threading

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.dirname(HERE))
import paths  # noqa: E402

HNSRUN = paths.RUNNER
DEFAULT_ROM = paths.ROM
DEVKITARM = os.environ.get("DEVKITARM", "/opt/devkitpro/devkitARM")
READELF = os.path.join(DEVKITARM, "bin", "arm-none-eabi-readelf")

# Struct offsets (bytes). Measured with offsetof() against include/global.h and
# include/main.h at Release-v2.0.6 using the build's own flags (-mabi=apcs-gnu, which
# aligns every struct to 4). NOTE the comments in include/global.h are stale for
# SaveBlock1: Heart & Soul inserted `u16 saveVersion` before `pos`, so pos is at 4,
# not 0, and location at 8, not 4.
OFF = {
    "Main.callback1": 0x00,
    "Main.callback2": 0x04,
    "Main.savedCallback": 0x08,
    "Main.heldKeys": 0x2C,
    "Main.newKeys": 0x2E,
    "Main.state": 0x438,
    "SB1.saveVersion": 0x00,
    "SB1.pos": 0x04,              # struct Coords16 {s16 x, y}
    "SB1.location": 0x08,         # struct WarpData {s8 group, num, warpId; pad; s16 x, y}
    "SB1.continueGameWarp": 0x10,
    "SB1.mapLayoutId": 0x36,
    "SB1.playerPartyCount": 0x238,
    "SB1.playerParty": 0x23C,     # struct Pokemon[6], 0x64 each
    "SB1.money": 0x494,
    "SB1.flags": 0x198C,
    "SB1.vars": 0x1ABC,           # u16 vars[], index = VAR_x - 0x4000
    "SB2.playerName": 0x00,
    "SB2.playerGender": 0x08,
    "SB2.playerTrainerId": 0x0A,
    "SB2.encryptionKey": 0xAC,
    "TextPrinter.nextPrinter": 0x2C,   # printers are a heap-allocated list (sFirstTextPrinter)
    "MapHeader.mapLayoutId": 0x12,     # include/global.fieldmap.h:241
    # tour helpers (part A). TextPrinter.state / .bits measured with probe/offsets.c;
    # .bits is the byte holding fontId:4, hasPrintBeenSpedUp:1, japanese:1, active:1 (bit 6),
    # isInUse:1 (include/text.h:113-138).
    "TextPrinter.windowId": 0x08,
    "TextPrinter.bits": 0x23,
    "TextPrinter.state": 0x24,
    # struct PaletteFadeControl (include/palette.h:57): three words, then a bitfield word
    # whose bit 31 is `active` (9+6+5+5+6 bits before it), i.e. byte 0xF bit 7.
    "PaletteFade.activeByte": 0x0F,
    # struct ScriptContext (include/script.h:9): stackDepth, mode, comparisonResult,
    # bitfield byte, then nativePtr.
    "ScriptContext.mode": 0x01,
    "ScriptContext.nativePtr": 0x04,
}
# Sizes the offsets above were measured against. selfcheck compares them with the ELF's
# object sizes (gSaveblockN is the struct plus 128 bytes of relocation slack,
# SaveBlock1ASLR in include/global.h); a mismatch means the layout changed: re-measure.
SIZES = {"SaveBlock1": 0x3D90, "SaveBlock2": 0xF34, "Main": 0x43C, "Task": 0x28}
SAVEBLOCK_MOVE_RANGE = 128           # src/load_save.c:24


class HnsError(Exception):
    pass


class TourTimeout(HnsError):
    """A wait on game state ran out of frames (reported as TIMEOUT by `hns.py tour`)."""
    pass


# ---------------------------------------------------------------------------- ELF

class Elf:
    def __init__(self, path):
        self.path = path
        self.byname = {}     # name -> [(value, size, type, bind)]
        self._sorted = None
        out = subprocess.run([READELF, "-sW", path], capture_output=True, text=True, check=True).stdout
        for line in out.splitlines():
            f = line.split()
            if len(f) < 8 or not f[0].endswith(":") or f[3] not in ("FUNC", "OBJECT", "NOTYPE"):
                continue
            name = f[7]
            if name.startswith("$") or name.startswith("."):
                continue
            try:
                val, size = int(f[1], 16), int(f[2], 0)
            except ValueError:
                continue
            self.byname.setdefault(name, []).append((val, size, f[3], f[4]))
        self._ranges = None
        # The Hebrew engine (TEXT_RTL, src/text.c) adds 4 bytes of right-to-left state before
        # TextPrinter.nextPrinter. Its class table is a symbol only that build has.
        if "sRtlCharClass" in self.byname:
            OFF["TextPrinter.nextPrinter"] = 0x30

    def objfile(self, addr):
        """Object file whose section contains ADDR, from the linker map next to the ELF
        (static symbols share names across files and the ELF only says <stdin>)."""
        import bisect
        if self._ranges is None:
            self._ranges = []
            mp = os.path.splitext(self.path)[0] + ".map"
            if os.path.exists(mp):
                rx = re.compile(r"^ \.\S+\s+0x([0-9a-f]+)\s+0x([0-9a-f]+)\s+(\S+\.o)\s*$")
                pend = None
                for line in open(mp, errors="replace"):
                    m = rx.match(line)
                    if not m and pend is not None:
                        m = re.match(r"^\s+0x([0-9a-f]+)\s+0x([0-9a-f]+)\s+(\S+\.o)\s*$", line)
                    pend = line if re.match(r"^ \.\S+\s*$", line) else None
                    if m:
                        a, n = int(m.group(1), 16), int(m.group(2), 16)
                        if a and n:
                            self._ranges.append((a, a + n, m.group(3)))
                self._ranges.sort()
            self._rkeys = [r[0] for r in self._ranges]
        i = bisect.bisect_right(self._rkeys, addr & ~1) - 1
        if i >= 0 and addr & ~1 < self._ranges[i][1]:
            return self._ranges[i][2]
        return None

    def _rec(self, name):
        if ":" in name:                       # "challenge_menu:MainCB2" picks one static
            obj, name = name.split(":", 1)
            obj = os.path.splitext(os.path.basename(obj))[0]
            recs = [r for r in self.byname.get(name, [])
                    if os.path.splitext(os.path.basename(self.objfile(r[0]) or ""))[0] == obj]
            if len(recs) != 1:
                raise HnsError("%s:%s matches %d symbols" % (obj, name, len(recs)))
            return recs[0]
        recs = self.byname.get(name)
        if not recs:
            raise HnsError("symbol not found in %s: %s" % (self.path, name))
        glob = [r for r in recs if r[3] == "GLOBAL"]
        if glob:
            return glob[0]
        if len({r[0] for r in recs}) > 1:
            raise HnsError("symbol %s is ambiguous, qualify it as FILE:%s: %s" % (name, name, ", ".join(
                "%s:%08X" % (os.path.splitext(os.path.basename(self.objfile(r[0]) or "?"))[0], r[0]) for r in recs)))
        return recs[0]

    def sym(self, name):
        return self._rec(name)[0]

    def size(self, name):
        return self._rec(name)[1]

    def where(self, addr):
        import bisect
        addr = rom_unmirror(addr)            # the ELF names a ROM mirror address by its ROM address
        if self._sorted is None:
            self._sorted = sorted((r[0] & ~1, n, r[1]) for n, recs in self.byname.items()
                                  for r in recs if r[2] in ("FUNC", "OBJECT"))
            self._keys = [s[0] for s in self._sorted]
        i = bisect.bisect_right(self._keys, addr & ~1) - 1
        if i < 0:
            return "?"
        base, name, size = self._sorted[i]
        off = (addr & ~1) - base
        tag = "" if size == 0 or off < size else " (past end)"
        if len(self.byname.get(name, ())) > 1:
            name = "%s:%s" % (os.path.splitext(os.path.basename(self.objfile(base) or "?"))[0], name)
        return ("%s+0x%X%s" % (name, off, tag)) if off else name + tag


def map_constants(src_dir):
    """MAP_* -> (group, num), computed exactly as tools/mapjson numbers them:
    group = index in group_order, num = index inside the group, no filtering."""
    groups_path = os.path.join(src_dir, "data", "maps", "map_groups.json")
    groups = json.load(open(groups_path))
    out = {}
    for g, gname in enumerate(groups["group_order"]):
        for n, mname in enumerate(groups[gname]):
            with open(os.path.join(src_dir, "data", "maps", mname, "map.json")) as f:
                mid = json.load(f)["id"]
            out[mid] = (g, n)
    return out


# ---------------------------------------------------------------------------- runner

class RunLog(list):
    """The runner's output kept for run.log and error messages. Bounded, so a tour that
    crashes into a loop of memory dumps cannot fill RAM: long lines are cut and only the
    newest lines are kept."""
    MAX_LINES = 100000
    MAX_CHARS = 2000

    def append(self, line):
        if len(line) > self.MAX_CHARS:
            line = "%s ...[%d chars]" % (line[:self.MAX_CHARS], len(line))
        super().append(line)
        if len(self) > self.MAX_LINES:
            del self[:len(self) - self.MAX_LINES // 2]


FRAME_AT = re.compile(r" @(\d+)$")          # the runner's frame count after 'shot', 'pc' and 'wait32'


def command_frames(line):
    """The most frames the runner steps for one command line (hnsrun.c): '<frames> <keys>',
    'tap <keys> [idle]' (3 held + idle, default 20) and 'wait32 ADDR VAL MAXFRAMES [keys]'.
    HNS_MAX_FRAMES adds these up and resets the sum to the runner's own count on every answer
    that carries it, so a wait that ends early is not charged its whole MAXFRAMES."""
    m = re.match(r"(\d+)\s+\S", line)
    if m:
        return int(m.group(1))
    m = re.match(r"tap\s+\S+(?:\s+(\d+))?\s*$", line)
    if m:
        return 3 + int(m.group(1) or 20)
    m = re.match(r"wait32\s+\S+\s+\S+\s+(\d+)", line)
    return int(m.group(1)) if m else 0


class Emu:
    """One live hnsrun process. Every method returns after the runner has executed it."""

    def __init__(self, rom=None, elf=None, outdir=".", save=None, rtc=None, echo=False):
        self.rom = rom or DEFAULT_ROM
        self.elf = elf if isinstance(elf, Elf) else Elf(elf or os.path.splitext(self.rom)[0] + ".elf")
        self.outdir = os.path.abspath(outdir)
        os.makedirs(self.outdir, exist_ok=True)
        self.echo = echo
        self.log = RunLog()
        self.max_frames = int(os.environ.get("HNS_MAX_FRAMES") or 0)
        self.frames_asked = 0
        env = dict(os.environ)
        if rtc is not None:
            env["HNS_RTC"] = str(rtc)
        if not os.path.exists(HNSRUN):
            raise HnsError("no runner at %s: build emu/hnsrun.c (emu/README.md) or set HNS_RUNNER" % HNSRUN)
        argv = [HNSRUN, self.rom, self.outdir] + ([os.path.abspath(save)] if save else [])
        self.p = subprocess.Popen(argv, stdin=subprocess.PIPE, stdout=subprocess.PIPE,
                                  stderr=subprocess.STDOUT, text=True, bufsize=1, env=env,
                                  errors="replace")
        self.q = queue.Queue()
        self.t = threading.Thread(target=self._reader, daemon=True)
        self.t.start()
        self.expect(r"^OK: booted")
        self.gMain = self.elf.sym("gMain")
        self.CB1 = self.gMain + OFF["Main.callback1"]
        self.CB2 = self.gMain + OFF["Main.callback2"]
        if os.environ.get("HNS_STRCOV") and "gRtlStringSet" in self.elf.byname:
            strings_hook(self, os.environ["HNS_STRCOV"])

    # -- plumbing
    LOG_RUN_MAX = 1000
    INVALID_CODE = ("Illegal opcode", "Jumped to invalid address")
    INVALID_TAG = " (invalid code)"

    def _dropped(self, n, bad):
        return "LOG ... %d more log lines in a row dropped%s" % (n, self.INVALID_TAG if bad else "")

    def _reader(self):
        """Queue the runner's lines. A crashed game can make mGBA log millions of lines ('Illegal
        opcode', 'Jumped to invalid address') during one command, faster than they are read off the
        queue: after LOG_RUN_MAX log lines in a row the rest of the run is only counted. Such a run
        about invalid code ends the tour as a CRASH (expect), as the PC may stay in the BIOS, which
        the runner's own PC check accepts."""
        run = dropped = 0
        bad = False
        for line in self.p.stdout:
            line = line.rstrip("\n")
            if line.startswith("LOG["):
                run += 1
                if run > self.LOG_RUN_MAX:
                    dropped += 1
                    if not bad:
                        bad = any(s in line for s in self.INVALID_CODE)
                    continue
            else:
                if dropped:
                    self.q.put(self._dropped(dropped, bad))
                run = dropped = 0
                bad = False
            self.q.put(line)
        if dropped:
            self.q.put(self._dropped(dropped, bad))
        self.q.put(None)

    def expect(self, pattern, timeout=600):
        rx = re.compile(pattern)
        while True:
            try:
                line = self.q.get(timeout=timeout)
            except queue.Empty:
                raise HnsError("runner did not answer /%s/ within %ss" % (pattern, timeout))
            if line is None:
                raise HnsError("runner exited while waiting for /%s/; last lines:\n  %s"
                               % (pattern, "\n  ".join(self.log[-8:])))
            self.log.append(line)
            if self.echo:
                sys.stderr.write(line + "\n")
            if line.startswith("CRASH"):
                raise HnsError(line)
            if line.startswith("LOG ... ") and line.endswith(self.INVALID_TAG):
                raise HnsError("CRASH: the CPU runs invalid code (%s)" % line)
            if line.startswith(("shot ", "PC ", "WAIT ")):
                f = FRAME_AT.search(line)
                if f:                       # every command sent so far has run: the real count
                    self.frames_asked = int(f.group(1))
            m = rx.search(line)
            if m:
                return m

    def send(self, line):
        if self.p.poll() is not None:
            raise HnsError("runner is not running (exit %s)" % self.p.returncode)
        n = command_frames(line) if self.max_frames else 0
        if n and self.frames_asked + n > self.max_frames:
            raise TourTimeout("frame limit: '%s' would pass HNS_MAX_FRAMES=%d (%d frames asked so far)"
                              % (line, self.max_frames, self.frames_asked))
        self.frames_asked += n
        self.p.stdin.write(line + "\n")
        self.p.stdin.flush()

    def sync(self):
        """Barrier: returns once every earlier command has run. Returns the frame count."""
        m = self.expect_after("pc", r"^PC ([0-9A-F]{8}) @(\d+)")
        return int(m.group(2))

    def expect_after(self, line, pattern):
        self.send(line)
        return self.expect(pattern)

    # -- runner commands
    def frames(self, n, keys="-"):
        self.send("%d %s" % (n, keys))

    def tap(self, keys, idle=20):
        self.send("tap %s %d" % (keys, idle))

    def shot(self, name):
        self.expect_after("shot %s" % name, r"^shot %s @" % re.escape(name))
        return os.path.join(self.outdir, name + ".png")

    def read(self, addr, n):
        m = self.expect_after("read %08X %d" % (addr, n), r"^MEM %08X:((?: [0-9A-F]{2})*)" % addr)
        return bytes(int(x, 16) for x in m.group(1).split())

    def r32(self, addr):
        m = self.expect_after("r32 %08X" % addr, r"^R32 %08X = ([0-9A-F]{8})" % addr)
        return int(m.group(1), 16)

    def r16(self, addr):
        b = self.read(addr, 2)
        return b[0] | b[1] << 8

    def r8(self, addr):
        return self.read(addr, 1)[0]

    def w(self, width, addr, val):
        self.expect_after("w%d %08X %X" % (width, addr, val), r"^POKE w%d %08X" % (width, addr))

    def w8(self, addr, val):
        self.w(8, addr, val & 0xFF)

    def w16(self, addr, val):
        self.w(16, addr, val & 0xFFFF)

    def w32(self, addr, val):
        self.w(32, addr, val & 0xFFFFFFFF)

    def wait32(self, addr, val, maxframes=600, keys=None):
        m = self.expect_after("wait32 %08X %08X %d%s" % (addr, val, maxframes, " " + keys if keys else ""),
                              r"^WAIT (ok|TIMEOUT) %08X" % addr)
        return m.group(1) == "ok"

    def pc(self):
        return int(self.expect_after("pc", r"^PC ([0-9A-F]{8})").group(1), 16)

    def close(self):
        if self.p.poll() is None:
            try:
                self.send("quit")
                self.p.stdin.close()
            except (BrokenPipeError, HnsError):
                pass
            self.p.wait(timeout=60)
        self.t.join(timeout=5)
        while True:
            try:
                line = self.q.get_nowait()
            except queue.Empty:
                break
            if line is not None:
                self.log.append(line)
        return self.p.returncode

    # -- game-level helpers
    def sym(self, name):
        return self.elf.sym(name)

    def cb2(self):
        return self.r32(self.CB2)

    def tasks(self):
        """Active tasks as [(taskId, func address, func name)] from gTasks (struct Task:
        func, isActive, prev, next, priority, s16 data[16]; include/task.h:13)."""
        base = self.sym("gTasks")
        stride = self.elf.size("gTasks") // 16
        raw = self.read(base, stride * 16)
        out = []
        for i in range(16):
            b = raw[i * stride:(i + 1) * stride]
            func = b[0] | b[1] << 8 | b[2] << 16 | b[3] << 24
            if b[4]:
                out.append((i, func, self.elf.where(func)))
        return out

    def task_active(self, name):
        want = self.sym(name)
        return any(f == want for _, f, _ in self.tasks())

    def wait_task(self, name, maxframes=600, keys=None, step=4):
        """Run until a task whose func is NAME is active. With KEYS, tap them every 30
        frames, like wait32. Polls every STEP frames."""
        want = self.sym(name)
        waited = 0
        while waited <= maxframes:
            if any(f == want for _, f, _ in self.tasks()):
                return True
            if keys and waited % 30 < step:
                self.frames(3, keys)
                self.frames(step - 3 if step > 3 else 0)
            else:
                self.frames(step)
            waited += step
        return False

    def cb2_name(self):
        return self.elf.where(self.cb2())

    def wait_cb2(self, name, maxframes=600, keys=None):
        return self.wait32(self.CB2, self.sym(name), maxframes, keys)

    def sb1(self):
        return self.r32(self.sym("gSaveBlock1Ptr"))

    def sb2(self):
        return self.r32(self.sym("gSaveBlock2Ptr"))

    def sb3(self):
        return self.r32(self.sym("gSaveBlock3Ptr"))

    def location(self):
        """(group, num, warpId, x, y) of gSaveBlock1Ptr->location, plus pos (x, y)."""
        sb1 = self.sb1()
        b = self.read(sb1 + OFF["SB1.pos"], 12)
        s16 = lambda lo, hi: ((hi << 8 | lo) ^ 0x8000) - 0x8000
        s8 = lambda v: (v ^ 0x80) - 0x80
        pos = (s16(b[0], b[1]), s16(b[2], b[3]))
        loc = (s8(b[4]), s8(b[5]), s8(b[6]), s16(b[8], b[9]), s16(b[10], b[11]))
        return loc, pos

    def in_overworld(self):
        return self.cb2() == self.sym("CB2_Overworld")

    def controllable(self):
        """True when the player can walk: callback2 is CB2_Overworld, callback1 is
        CB1_Overworld, no script is running (sGlobalScriptContextStatus == CONTEXT_SHUTDOWN,
        src/script.c:28) and field controls are not locked (sLockFieldControls)."""
        return (self.cb2() == self.sym("CB2_Overworld")
                and self.r32(self.CB1) == self.sym("CB1_Overworld")
                and self.r8(self.sym("sGlobalScriptContextStatus")) == 2
                and self.r8(self.sym("sLockFieldControls")) == 0)

    def wait_controllable(self, maxframes=1200, keys=None, step=4, settle=8):
        """Run until controllable() has held for SETTLE consecutive frames. With KEYS,
        tap them every 30 frames meanwhile (e.g. "B" to close leftover text)."""
        waited, good = 0, 0
        while waited <= maxframes:
            if self.controllable():
                good += step
                if good >= settle:
                    return True
            else:
                good = 0
                if keys and waited % 30 < step:
                    self.frames(3, keys)
                    if step > 3:
                        self.frames(step - 3)
                    waited += step
                    continue
            self.frames(step)
            waited += step
        return False

    def warp(self, group, num, x, y, settle=30):
        """Warp from the overworld by rewriting the destination in the save block and
        re-entering the map loader, the same path a door uses after ApplyCurrentWarp().

        CB2_LoadMap (src/overworld.c:2049) -> CB2_DoChangeMap -> CB2_LoadMap2 ->
        LoadMapInStepsLocal: case 0 loads the header from gSaveBlock1Ptr->location, case 1
        MOVES the save blocks, case 3 places the player at gSaveBlock1Ptr->pos. So both
        ->location and ->pos must be set, and gSaveBlock1Ptr must be re-read afterwards.
        Returns (sb1_before, sb1_after)."""
        if not self.in_overworld():
            raise HnsError("warp: not in the overworld (callback2 = %s)" % self.cb2_name())
        before = self.sb1()
        pos = before + OFF["SB1.pos"]
        loc = before + OFF["SB1.location"]
        self.w16(pos, x)
        self.w16(pos + 2, y)
        self.w8(loc + 0, group)
        self.w8(loc + 1, num)
        self.w8(loc + 2, 0xFF)          # WARP_ID_NONE: use x/y
        self.w16(loc + 4, x)
        self.w16(loc + 6, y)
        self.w32(self.CB2, self.sym("CB2_LoadMap"))
        if not self.wait32(self.CB2, self.sym("CB2_Overworld"), 600):
            raise HnsError("warp: map load did not return to CB2_Overworld (at %s)" % self.cb2_name())
        if not self.wait_controllable(settle + 600):
            # an ON_FRAME/ON_TRANSITION map script (a cutscene) holds the player; that may
            # be the screen you wanted, so warn instead of failing
            sys.stderr.write("hns: warp %d.%d: arrived, but a script still holds the player\n"
                             % (group, num))
        self.frames(settle)
        after = self.sb1()
        (g, n, _, _, _), (px, py) = self.location()
        if (g, n, px, py) != (group, num, x, y):
            raise HnsError("warp: landed at %d.%d (%d,%d), wanted %d.%d (%d,%d)"
                           % (g, n, px, py, group, num, x, y))
        return before, after

    def poll(self, cond, maxframes, step=2, what="condition"):
        """Advance STEP frames at a time until cond() is true; HnsError on timeout."""
        waited = 0
        while not cond():
            if waited >= maxframes:
                raise HnsError("timed out after %d frames waiting for %s (callback2 %s, tasks %s)"
                               % (maxframes, what, self.cb2_name(), [t[2] for t in self.tasks()]))
            self.frames(step)
            waited += step
        return waited

    MENU_ACTION_SAVE = 5        # enum in src/start_menu.c:58 (POKEDEX, POKEMON, BAG, POKENAV, PLAYER, SAVE)

    def start_menu_ready(self):
        """True when the start menu is drawn and reads input: a Task_ShowStartMenu task is
        in its input state (data[0] == 1) and gMenuCallback is HandleStartMenuInput
        (src/start_menu.c:694-712). gMenuCallback alone does not tell: closing the menu
        with B or START ends the task (:767-772) and nothing clears the pointer, so it
        still names HandleStartMenuInput on the field afterwards, on every map."""
        return (self.r32(self.sym("gMenuCallback")) == self.sym("HandleStartMenuInput")
                and any(d[0] == 1 for d in self.task_data("Task_ShowStartMenu")))

    def open_start_menu(self, maxframes=600):
        """Make the start menu ready for input (start_menu_ready). A menu that is open is
        used as it is; one the game is drawing again is waited for (a screen opened from
        the menu returns through CB2_ReturnToFieldWithOpenMenu, src/overworld.c:2147-2152,
        which reopens it with the player locked); otherwise START from a controllable
        overworld."""
        if self.start_menu_ready():
            return
        if not self.controllable():
            self.poll(lambda: self.start_menu_ready() or self.controllable(), maxframes,
                      what="the start menu or a controllable player")
            if self.start_menu_ready():
                return
        self.tap("START", 0)
        self.poll(self.start_menu_ready, 120, what="start menu")

    def start_menu_seek(self, want, n, what):
        """Press DOWN until sStartMenuCursorPos == WANT, checking after every press (the
        menu wraps). A press the menu did not take (it can drop one right after it
        reopens) is simply repeated."""
        pos = self.sym("sStartMenuCursorPos")
        for _ in range(3 * n):
            if self.r8(pos) == want:
                return
            self.tap("DOWN", 4)
        if self.r8(pos) != want:
            raise HnsError("start menu cursor did not reach %s (at %d)" % (what, self.r8(pos)))

    def save_game(self, overwrite_different=False):
        """In-game save from the start menu: SAVE -> "Would you like to save the game?" YES.
        Heart & Soul skips the "already a saved file" prompt (src/start_menu.c:1222, IS_HNS);
        the "different save file" prompt (new game over an old save, default NO) only
        appears after a NEW GAME on a non-empty .sav and raises unless overwrite_different."""
        self.open_start_menu()
        n = self.r8(self.sym("sNumStartMenuActions"))
        acts = list(self.read(self.sym("sCurrentStartMenuActions"), n))
        if self.MENU_ACTION_SAVE not in acts:
            raise HnsError("start menu has no SAVE entry: %s" % acts)
        self.start_menu_seek(acts.index(self.MENU_ACTION_SAVE), n, "SAVE")
        self.tap("A", 0)
        cbaddr = self.sym("sSaveDialogCallback")
        cb = lambda: self.r32(cbaddr)
        self.poll(lambda: cb() == self.sym("SaveConfirmInputCallback"), 300, what="save YES/NO")
        self.frames(4)
        self.tap("A", 0)                                    # YES
        ok, err = self.sym("SaveReturnSuccessCallback"), (self.sym("SaveErrorCallback"),
                                                         self.sym("SaveReturnErrorCallback"))
        over = self.sym("SaveOverwriteInputCallback")
        waited = 0
        while cb() != ok:
            c = cb()
            if c in err:
                raise HnsError("the game reported a save error")
            if c == over:
                if not overwrite_different:
                    raise HnsError("save: 'different save file' prompt; pass overwrite_different")
                self.tap("UP", 4)
                self.tap("A", 0)
            if waited > 1200:
                raise HnsError("save did not finish (dialog at %s)" % self.elf.where(c))
            self.frames(4)
            waited += 4
        if not self.wait_controllable(600):
            raise HnsError("save: the menu did not close")

    def open_debug_menu(self):
        """Hold R, press START (include/config/debug.h: DEBUG_OVERWORLD_HELD_KEYS R_BUTTON,
        trigger pressedStartButton; src/field_control_avatar.c:165). Returns when
        DebugTask_HandleMenuInput_General runs. The cursor always starts on the first item,
        every list WRAPS (UP from the top reaches the last item), and B from a submenu
        returns to the main list with the cursor reset to the top."""
        if not self.controllable():
            raise HnsError("debug menu: player is not controllable (callback2 %s)" % self.cb2_name())
        self.frames(10, "R")
        self.frames(3, "R+START")
        self.frames(2)
        self.poll(lambda: self.task_active("DebugTask_HandleMenuInput_General"), 60, what="debug menu")
        self.frames(10)

    def debug_number(self, start, target, digits):
        """Key presses that turn a debug numeric field from START to TARGET.
        Debug_HandleInput_Numeric (src/debug.c:960): UP/DOWN add/subtract 10^digit, the
        digit starts at 0 (ones), RIGHT moves to the next HIGHER digit, LEFT back down."""
        keys, delta = [], target - start
        mag = abs(delta)
        sign = "UP" if delta >= 0 else "DOWN"
        place = 0
        for d in range(digits):
            n = (mag // 10 ** d) % 10
            if n:
                keys += ["RIGHT"] * (d - place)
                place = d
                keys += [sign] * n
        if mag >= 10 ** digits:
            raise HnsError("debug_number: %d does not fit in %d digits" % (target, digits))
        return keys

    def keys(self, seq, idle=6):
        for k in seq:
            self.tap(k, idle)

    def flag_addr(self, flag):
        return self.sb1() + OFF["SB1.flags"] + (flag >> 3), 1 << (flag & 7)

    def set_flag(self, flag, on=True):
        addr, bit = self.flag_addr(flag)
        v = self.r8(addr)
        self.w8(addr, (v | bit) if on else (v & ~bit))

    def get_flag(self, flag):
        addr, bit = self.flag_addr(flag)
        return bool(self.r8(addr) & bit)

    def set_var(self, var, val):
        self.w16(self.sb1() + OFF["SB1.vars"] + 2 * (var - 0x4000), val)

    def get_var(self, var):
        return self.r16(self.sb1() + OFF["SB1.vars"] + 2 * (var - 0x4000))

    # -- tour helpers (part A) -------------------------------------
    # Every wait here is on game state, so a tour survives text of another length.
    # Frame counts appear only as idle time after a key tap.

    # RENDER_STATE_WAIT / _CLEAR / _SCROLL_START: the printer is parked until A or B
    # (include/text.h:46-54; src/text.c:1619-1641). Any other state is still drawing.
    TEXT_KEY_STATES = (1, 2, 3)

    def const(self, name):
        """Value of a C constant (FLAG_*, VAR_*, SPECIES_*, ITEM_*, MOVE_*, ...) or a number.
        Constants are compiled from the source tree next to the ELF (HNS_SRC overrides),
        because the item list is an enum and the flags are nested #defines."""
        return resolve_const(self.elf, name)

    def text_printers(self):
        """[(addr, state, active, windowId)] for the heap-allocated printer list
        (sFirstTextPrinter, src/text.c:59; finished printers are freed, src/text.c:2710)."""
        out, seen = [], set()
        p = self.r32(self.sym("sFirstTextPrinter"))
        while p and p not in seen and len(out) < 64:
            seen.add(p)
            b = self.read(p, 0x30)
            out.append((p, b[OFF["TextPrinter.state"]], (b[OFF["TextPrinter.bits"]] >> 6) & 1,
                        b[OFF["TextPrinter.windowId"]]))
            p = int.from_bytes(b[OFF["TextPrinter.nextPrinter"]:OFF["TextPrinter.nextPrinter"] + 4], "little")
        return out

    def text_state(self):
        """'busy' while any active printer is still drawing, 'key' when every active
        printer waits for A/B (a \\p or \\l page break), 'idle' when none is active."""
        act = [s for _, s, a, _ in self.text_printers() if a]
        if not act:
            return "idle"
        return "key" if all(s in self.TEXT_KEY_STATES for s in act) else "busy"

    def fading(self):
        return bool(self.r8(self.sym("gPaletteFade") + OFF["PaletteFade.activeByte"]) & 0x80)

    def script_waits_for_key(self):
        """The field script sits in `waitbuttonpress` (native WaitForAorBPress,
        src/scrcmd.c:2406), e.g. at the end of every msgbox."""
        ctx = self.sym("sGlobalScriptContext")
        return (self.r8(ctx + OFF["ScriptContext.mode"]) == 2
                and self.r32(ctx + OFF["ScriptContext.nativePtr"]) == self.sym("WaitForAorBPress"))

    def wants_key(self):
        """A text box is complete and waits for A/B."""
        return self.text_state() == "key" or self.script_waits_for_key()

    def wait_until(self, cond, maxframes, what, step=2):
        """Like poll(), but a timeout is a TourTimeout. Returns the frames waited."""
        waited = 0
        while not cond():
            if waited >= maxframes:
                raise TourTimeout("timed out after %d frames waiting for %s (callback2 %s, tasks %s)"
                                  % (maxframes, what, self.cb2_name(), [t[2] for t in self.tasks()]))
            self.frames(step)
            waited += step
        return waited

    def wait_quiet(self, maxframes=900, stable=4, step=2):
        """Run until no palette fade runs and no text printer is drawing, held for STABLE
        frames. Text parked on a page break counts as quiet (it waits for a key)."""
        waited, good = 0, 0
        while True:
            ts = self.text_state()
            if ts == "busy":
                self.saw_busy_text = True     # read by talk(): a message was drawn
            if not self.fading() and ts != "busy":
                good += step
                if good >= stable:
                    return waited
            else:
                good = 0
            if waited >= maxframes:
                raise TourTimeout("timed out after %d frames waiting for the screen to settle "
                                  "(fade %s, text %s, callback2 %s)"
                                  % (maxframes, self.fading(), self.text_state(), self.cb2_name()))
            self.frames(step)
            waited += step

    def snap(self, name, maxframes=900):
        """Settle (wait_quiet), give the window copy a frame to reach VRAM, screenshot."""
        self.wait_quiet(maxframes)
        self.frames(2)
        return self.shot(name)

    def tasks_named(self, names):
        """Active task funcs among NAMES (names that this ELF lacks are ignored)."""
        want = {}
        for n in names:
            try:
                want[self.sym(n)] = n
            except HnsError:
                pass
        return [want[f] for _, f, _ in self.tasks() if f in want]

    def task_data(self, name):
        """data[16] (s16) of every active task running NAME (struct Task: func, isActive,
        prev, next, priority, then s16 data[16] at +8; include/task.h:13)."""
        want = self.sym(name)
        base = self.sym("gTasks")
        stride = self.elf.size("gTasks") // 16
        raw = self.read(base, stride * 16)
        out = []
        for i in range(16):
            b = raw[i * stride:(i + 1) * stride]
            if b[4] and int.from_bytes(b[0:4], "little") == want:
                out.append([int.from_bytes(b[8 + 2 * j:10 + 2 * j], "little", signed=True) for j in range(16)])
        return out

    # Input tasks a field script leaves on screen when its dialogue ends in a choice.
    MENU_TASKS = ["script_menu:Task_HandleYesNoInput", "script_menu:Task_HandleMultichoiceInput",
                  "script_menu:Task_HandleScrollingMultichoiceInput",
                  "script_menu:Task_HandleMultichoiceGridInput", "Task_HandleYesNoInput",
                  "Task_HandleMultichoiceInput", "Task_HandleScrollingMultichoiceInput"]

    def wait_menu_ready(self, maxframes=120):
        """A field script's choice menu ignores keys for its first frames: YES/NO counts
        data[2] (tRight) up to 5 (src/script_menu.c:655-661), multichoice menus count
        sProcessInputDelay down and wait out palette fades (src/script_menu.c:587-600).
        Run until the menu on screen reads input."""
        def ready():
            for d in self.task_data("Task_HandleYesNoInput") if self.task_active("Task_HandleYesNoInput") else []:
                if d[2] < 5:
                    return False
            if self.tasks_named(["Task_HandleMultichoiceInput", "Task_HandleMultichoiceGridInput",
                                 "Task_HandleScrollingMultichoiceInput"]):
                try:
                    if self.r8(self.sym("script_menu:sProcessInputDelay")):
                        return False
                except HnsError:
                    pass
                if self.fading():
                    return False
            return True
        self.wait_until(ready, maxframes, "the choice menu to read input", step=1)

    def talk(self, prefix, maxpages=40, first_key="A", stop_tasks=(), maxframes=3000):
        """Dialogue walker. Taps FIRST_KEY (A = talk to what the player faces), then for each
        page: wait for the text to settle, screenshot PREFIX_NN, press A. Stops (after a
        last screenshot) when a choice menu appears (MENU_TASKS + STOP_TASKS), and stops
        without one when the player is free again or another screen took over callback2.
        A is pressed only while a text box waits for it, never blind.
        Returns (pages, how) with how in 'free', 'menu:<task>', 'screen:<callback2>'."""
        if first_key and first_key != "-":
            self.tap(first_key, 0)
        stops = list(self.MENU_TASKS) + list(stop_tasks)
        ow = self.sym("CB2_Overworld")
        n, idle = 0, 0
        while True:
            self.saw_busy_text = False
            self.wait_quiet(maxframes)
            menus = self.tasks_named(stops)
            if menus:
                self.wait_menu_ready()
                self.frames(2)
                n += 1
                self.shot("%s_%02d" % (prefix, n))
                return n, "menu:" + menus[0]
            if self.wants_key():
                self.frames(2)
                n += 1
                self.shot("%s_%02d" % (prefix, n))
                if n >= maxpages:
                    return n, "maxpages"
                self.tap("A", 0)
                idle = 0
                continue
            if self.saw_busy_text:
                # a `message` the script does not wait on (it goes on with a movement or
                # an animation, e.g. the nurse's "I'll take your POKeMON")
                self.frames(2)
                n += 1
                self.shot("%s_%02d" % (prefix, n))
                idle = 0
                continue
            if self.cb2() != ow:
                return n, "screen:" + self.cb2_name()
            if self.controllable():
                self.frames(8)
                if self.controllable():
                    return n, "free"
            if idle >= maxframes:
                raise TourTimeout("talk %s: no text box, menu or free player after %d frames "
                                  "(callback2 %s, tasks %s)" % (prefix, idle, self.cb2_name(),
                                                                [t[2] for t in self.tasks()]))
            self.frames(4)
            idle += 4

    START_MENU_ACTIONS = {"POKEDEX": 0, "POKEMON": 1, "BAG": 2, "POKENAV": 3, "POKEGEAR": 3,
                          "PLAYER": 4, "SAVE": 5, "OPTION": 6, "EXIT": 7, "DEXNAV": 14}

    def start_menu_cursor(self, action, press=True):
        """Open the start menu (if it is not ready, see open_start_menu) and move its cursor
        to ACTION (a name in START_MENU_ACTIONS; enum in src/start_menu.c:58) by reading
        sCurrentStartMenuActions, so the entry order of this save does not matter. With
        PRESS, also press A."""
        want_act = self.START_MENU_ACTIONS[action] if isinstance(action, str) else action
        self.open_start_menu()
        n = self.r8(self.sym("sNumStartMenuActions"))
        acts = list(self.read(self.sym("sCurrentStartMenuActions"), n))
        if want_act not in acts:
            raise HnsError("start menu has no entry %s: %s" % (action, acts))
        self.start_menu_seek(acts.index(want_act), n, action)
        if press:
            self.tap("A", 0)

    def debug_select(self, *path):
        """R+START, then walk PATH: in each list press DOWN index times (every list opens
        on its first item) and A. Main list: 0 Utilities, 1 PC/Bag, 2 Party, 3 Give X,
        4 Player, 5 Scripts, 6 Trainers, 7 Flags & Vars, 8 Sound, 9 ROM Info."""
        self.open_debug_menu()
        for i in path:
            for _ in range(i):
                self.tap("DOWN", 6)
            self.tap("A", 12)

    def debug_enter(self, start, target, digits):
        self.keys(self.debug_number(start, target, digits), 6)

    def give_mon(self, species, level):
        """Give X > Pokemon (Basic): species field (4 digits, starts at 1), level field
        (3 digits, starts at 1). Checks that the party grew."""
        before = self.r8(self.sym("gPlayerPartyCount"))
        self.debug_select(3, 1)
        self.debug_enter(1, species, 4)
        self.tap("A", 12)
        self.debug_enter(1, level, 3)
        self.tap("A", 30)
        if not self.wait_controllable(600):
            raise TourTimeout("give_mon: the debug menu did not close")
        if self.r8(self.sym("gPlayerPartyCount")) != before + 1:
            raise HnsError("give_mon %d: party count stayed %d" % (species, before))

    def give_egg(self, species):
        """Give X > Give Egg: species field, A gives the egg (ScriptGiveEgg)."""
        before = self.r8(self.sym("gPlayerPartyCount"))
        self.debug_select(3, 3)
        self.debug_enter(1, species, 4)
        self.tap("A", 30)
        if not self.wait_controllable(600):
            raise TourTimeout("give_egg: the debug menu did not close")
        if self.r8(self.sym("gPlayerPartyCount")) != before + 1:
            raise HnsError("give_egg %d: party count stayed %d" % (species, before))

    def give_item(self, item, qty):
        """Give X > Give item XYZ: id field (4 digits, starts at 1), quantity (3 digits)."""
        self.debug_select(3, 0)
        self.debug_enter(1, item, 4)
        self.tap("A", 12)
        self.debug_enter(1, qty, 3)
        self.tap("A", 30)
        if not self.wait_controllable(600):
            raise TourTimeout("give_item: the debug menu did not close")

    # -- scripts
    MARK = re.compile(r"@((?:[A-Za-z0-9_]+:)?[A-Za-z_][A-Za-z0-9_]*)([+-][0-9A-Fa-f]+)?@")

    def _resolve(self, name):
        if name == "SB1":
            return self.sb1()
        if name == "SB2":
            return self.sb2()
        if name == "SB3":
            return self.sb3()
        if name == "CB1":
            return self.CB1
        if name == "CB2":
            return self.CB2
        if name == "LOC":
            return self.sb1() + OFF["SB1.location"]
        if name == "POS":
            return self.sb1() + OFF["SB1.pos"]
        return self.sym(name)

    def subst(self, line):
        def rep(m):
            v = self._resolve(m.group(1))
            if m.group(2):
                v += int(m.group(2), 16)
            return "%08X" % (v & 0xFFFFFFFF)
        return self.MARK.sub(rep, line)

    # ROWNEXT / ROWPREV: the key that moves a value row of the options or challenge menu to its
    # next / previous value. A TEXT_RTL build lists the values right to left, so there LEFT is
    # next (src/option_menu.c, src/challenge_menu.c ProcessLeftRight). The same holds for the
    # second column of a mirrored 2x2 item context grid (GIVE, REGISTER, CHECK TAG; src/item_menu.c
    # Task_ItemContext_MultipleRows). One tour then picks the same values, with the same shot
    # names, on the English and the Hebrew ROM.
    ROWKEY = re.compile(r"\bROW(NEXT|PREV)\b")

    def rowkeys(self, line):
        rtl = "sRtlCharClass" in self.elf.byname
        keys = {"NEXT": "LEFT" if rtl else "RIGHT", "PREV": "RIGHT" if rtl else "LEFT"}
        return self.ROWKEY.sub(lambda m: keys[m.group(1)], line)

    def run_script(self, path, stop_on_timeout=True):
        base = os.path.dirname(os.path.abspath(path))
        skip = []                                # one entry per open ifsym block: True = skip it
        for raw in open(path, encoding="utf-8"):
            line = raw.split("#", 1)[0].strip()
            if not line:
                continue
            f = line.split()
            op = f[0]
            if op == "ifsym":
                if len(f) != 2:
                    raise HnsError("%s: ifsym takes one symbol: %s" % (path, line))
                skip.append(f[1] not in self.elf.byname)
                continue
            if op == "endif":
                if not skip:
                    raise HnsError("%s: endif without ifsym" % path)
                skip.pop()
                continue
            if any(skip):
                continue
            if op == "include":
                self.run_script(os.path.join(base, f[1]), stop_on_timeout)
                continue
            if op == "echo":
                sys.stdout.write(line[5:] + "\n")
                continue
            line = self.rowkeys(self.subst(line))
            f = line.split()
            if op in SCRIPT_OPS:                 # ops registered with @script_op below
                SCRIPT_OPS[op](self, f, path)
                continue
            if op == "waitcb2":
                ok = self.wait32(self.CB2, self.sym(f[1]), int(f[2]) if len(f) > 2 else 600,
                                 f[3] if len(f) > 3 else None)
                print("waitcb2 %s %s @%d" % (f[1], "ok" if ok else "TIMEOUT (at %s)" % self.cb2_name(), self.sync()))
                if not ok and stop_on_timeout:
                    raise HnsError("waitcb2 %s timed out in %s" % (f[1], path))
            elif op == "wait32":
                ok = self.wait32(int(f[1], 16), int(f[2], 16), int(f[3]) if len(f) > 3 else 600,
                                 f[4] if len(f) > 4 else None)
                print("wait32 %s %s" % (" ".join(f[1:3]), "ok" if ok else "TIMEOUT"))
                if not ok and stop_on_timeout:
                    raise HnsError("%s timed out in %s" % (line, path))
            elif op == "waittask":
                ok = self.wait_task(f[1], int(f[2]) if len(f) > 2 else 600, f[3] if len(f) > 3 else None)
                print("waittask %s %s @%d" % (f[1], "ok" if ok else "TIMEOUT", self.sync()))
                if not ok and stop_on_timeout:
                    raise HnsError("waittask %s timed out in %s; active: %s"
                                   % (f[1], path, [t[2] for t in self.tasks()]))
            elif op == "waitctl":
                ok = self.wait_controllable(int(f[1]) if len(f) > 1 else 1200, f[2] if len(f) > 2 else None)
                print("waitctl %s @%d" % ("ok" if ok else "TIMEOUT", self.sync()))
                if not ok and stop_on_timeout:
                    raise HnsError("waitctl timed out in %s (callback2 %s)" % (path, self.cb2_name()))
            elif op in ("expect8", "expect16", "expect32"):
                width = int(op[6:])
                got = {8: self.r8, 16: self.r16, 32: self.r32}[width](int(f[1], 16))
                if got != int(f[2], 16):
                    raise HnsError("%s %s: got %X (%s)" % (op, f[1], got, self.elf.where(got)))
                print("%s %s = %X ok" % (op, f[1], got))
            elif op == "expectflag":
                got = self.get_flag(self.const(f[1]))
                if got != bool(int(f[2])):
                    raise HnsError("expectflag %s: flag is %d" % (f[1], got))
                print("expectflag %s = %d ok" % (f[1], got))
            elif op == "expectloc":
                (g, n, _, _, _), (x, y) = self.location()
                want = [int(v, 0) for v in f[1:]]
                if [g, n, x, y][:len(want)] != want:
                    raise HnsError("expectloc: at %d.%d (%d,%d), wanted %s" % (g, n, x, y, f[1:]))
                print("expectloc %d.%d (%d,%d) ok" % (g, n, x, y))
            elif op == "warp":
                b, a = self.warp(*(int(x, 0) for x in f[1:5]))
                print("warp %s: SaveBlock1 %08X -> %08X" % (" ".join(f[1:5]), b, a))
            elif op == "savegame":
                self.save_game(len(f) > 1 and f[1] == "overwrite")
                print("savegame ok @%d" % self.sync())
            elif op == "debugmenu":
                self.open_debug_menu()
            elif op in ("setflag", "clearflag"):
                self.set_flag(self.const(f[1]), op == "setflag")     # FLAG_* names work too
            elif op == "setvar":
                self.set_var(self.const(f[1]), int(f[2], 16))
            elif op == "shot":
                print("shot %s @%d" % (f[1], self.sync()))
                self.shot(f[1])
            elif op in ("read", "r32", "pc"):
                self.send(line)
                m = self.expect(r"^(MEM|R32|PC) ")
                print(m.string)
            elif op in ("w8", "w16", "w32"):
                self.w(int(op[1:]), int(f[1], 16), int(f[2], 16))
            else:
                self.send(line)      # frames, tap, ss, sl
        if skip:
            raise HnsError("%s: ifsym without endif" % path)
        self.sync()


# ---------------------------------------------------------------------------- script ops
# Extra script commands live in this registry so that both tour authors can add their own
# without touching each other's code: decorate a function (emu, fields, path) with
# @script_op("name"). fields[0] is the op; @SYMBOL@ markers are already resolved.

SCRIPT_OPS = {}


def script_op(*names):
    def deco(fn):
        for n in names:
            SCRIPT_OPS[n] = fn
        return fn
    return deco


def _arg(f, i, default=None, conv=int):
    return conv(f[i]) if len(f) > i else default


@script_op("start")
def _op_start(emu, f, path):
    """start SAVE: tour header, read by `hns.py tour` before the runner starts (no-op here)."""


@script_op("keepsave")
def _op_keepsave(emu, f, path):
    """keepsave NAME: after the tour, `hns.py tour` copies the battery to OUTDIR/_saves/NAME.sav
    for tours that say `start save:NAME`. Put it after a `savegame`."""
    emu.keep_saves = getattr(emu, "keep_saves", []) + [f[1]]


@script_op("waitptr")
def _op_waitptr(emu, f, path):
    """waitptr VARSYM FUNCSYM [MAX]: run until the pointer variable VARSYM holds FUNCSYM,
    e.g. waitptr gMenuCallback HandleStartMenuInput."""
    var, want = emu.sym(f[1]), emu.sym(f[2])
    emu.wait_until(lambda: emu.r32(var) == want, _arg(f, 3, 600), "%s == %s" % (f[1], f[2]))
    print("waitptr %s == %s ok @%d" % (f[1], f[2], emu.sync()))


@script_op("waitmem")
def _op_waitmem(emu, f, path):
    """waitmem 8|16|32 HEXADDR HEXVAL [MAX]: run until memory holds VAL (use @SYM+OFF@)."""
    width, addr, val = int(f[1]), int(f[2], 16), int(f[3], 16)
    rd = {8: emu.r8, 16: emu.r16, 32: emu.r32}[width]
    emu.wait_until(lambda: rd(addr) == val, _arg(f, 4, 600), "%s == %s" % (f[2], f[3]))
    print("waitmem %s = %s ok @%d" % (f[2], f[3], emu.sync()))


@script_op("waitnotask")
def _op_waitnotask(emu, f, path):
    """waitnotask FUNC [MAX]: run until no task runs FUNC."""
    want = emu.sym(f[1])
    emu.wait_until(lambda: all(fn != want for _, fn, _ in emu.tasks()), _arg(f, 2, 600),
                   "task %s to end" % f[1], step=4)
    print("waitnotask %s ok @%d" % (f[1], emu.sync()))


@script_op("waittaskx")
def _op_waittaskx(emu, f, path):
    """waittaskx FUNC [MAX]: like waittask, but a timeout is a TourTimeout (no key taps)."""
    want = emu.sym(f[1])
    emu.wait_until(lambda: any(fn == want for _, fn, _ in emu.tasks()), _arg(f, 2, 600),
                   "task %s" % f[1], step=2)
    print("waittaskx %s ok @%d" % (f[1], emu.sync()))


@script_op("waittaskdata")
def _op_waittaskdata(emu, f, path):
    """waittaskdata FUNC IDX VAL [MAX]: run until a task running FUNC has data[IDX] == VAL
    (e.g. a screen's input state)."""
    idx, val = int(f[2]), emu.const(f[3])
    emu.wait_until(lambda: any(d[idx] == val for d in emu.task_data(f[1])), _arg(f, 4, 600),
                   "task %s data[%d] == %d" % (f[1], idx, val), step=2)
    print("waittaskdata %s[%d] == %d ok @%d" % (f[1], idx, val, emu.sync()))


@script_op("waitcb2x")
def _op_waitcb2x(emu, f, path):
    """waitcb2x SYMBOL [MAX]: like waitcb2, but without key taps and with a TourTimeout."""
    if not emu.wait32(emu.CB2, emu.sym(f[1]), _arg(f, 2, 600)):
        raise TourTimeout("waitcb2x %s timed out (callback2 %s)" % (f[1], emu.cb2_name()))
    print("waitcb2x %s ok @%d" % (f[1], emu.sync()))


@script_op("waitquiet")
def _op_waitquiet(emu, f, path):
    """waitquiet [MAX]: no fade and no text printer drawing (see Emu.wait_quiet)."""
    n = emu.wait_quiet(_arg(f, 1, 900))
    print("waitquiet ok after %d @%d" % (n, emu.sync()))


@script_op("waitkey")
def _op_waitkey(emu, f, path):
    """waitkey [MAX]: run until a text box is complete and waits for A/B."""
    emu.wait_until(emu.wants_key, _arg(f, 1, 1200), "a text box waiting for A", step=2)
    print("waitkey ok @%d" % emu.sync())


@script_op("snap")
def _op_snap(emu, f, path):
    """snap NAME [MAX]: waitquiet, then shot NAME."""
    print("snap %s @%d" % (f[1], emu.sync()))
    emu.snap(f[1], _arg(f, 2, 900))
    emu.shots = getattr(emu, "shots", []) + [f[1]]


@script_op("press")
def _op_press(emu, f, path):
    """press KEY [IDLE]: tap KEY, idle (default 4) frames, then waitquiet."""
    emu.tap(f[1], _arg(f, 2, 4))
    emu.wait_quiet(900)


@script_op("talk")
def _op_talk(emu, f, path):
    """talk PREFIX [MAXPAGES] [FIRSTKEY] [STOPTASK...]: walk a dialogue, one shot per page
    (PREFIX_01, ...). FIRSTKEY defaults to A (talk to / read what the player faces);
    '-' presses nothing first. Ends at a choice menu, a free player or a new screen."""
    n, how = emu.talk(f[1], _arg(f, 2, 40), f[3] if len(f) > 3 else "A", f[4:])
    print("talk %s: %d page(s), ended %s @%d" % (f[1], n, how, emu.sync()))
    if n == 0:
        raise HnsError("talk %s: no text appeared (nothing to talk to? ended %s)" % (f[1], how))
    emu.shots = getattr(emu, "shots", []) + ["%s_%02d" % (f[1], i + 1) for i in range(n)]


@script_op("expecttask")
def _op_expecttask(emu, f, path):
    """expecttask TASK: stop unless TASK is an active task (e.g. after talk)."""
    if not emu.task_active(f[1]):
        raise HnsError("expecttask: %s is not running; tasks %s" % (f[1], [t[2] for t in emu.tasks()]))


@script_op("expectcb2")
def _op_expectcb2(emu, f, path):
    """expectcb2 SYMBOL: stop unless gMain.callback2 is SYMBOL."""
    if emu.cb2() != emu.sym(f[1]):
        raise HnsError("expectcb2 %s: callback2 is %s" % (f[1], emu.cb2_name()))


@script_op("startmenu")
def _op_startmenu(emu, f, path):
    """startmenu ACTION [nopress]: open the start menu and pick POKEDEX, POKEMON, BAG,
    POKEGEAR, PLAYER, SAVE, OPTION or EXIT by its action id, not its position."""
    emu.start_menu_cursor(f[1], press=not (len(f) > 2 and f[2] == "nopress"))


@script_op("dbg")
def _op_dbg(emu, f, path):
    """dbg I [J ...]: open the debug menu and pick item I, then J in the submenu, ..."""
    emu.debug_select(*(int(x) for x in f[1:]))


@script_op("dbgnum")
def _op_dbgnum(emu, f, path):
    """dbgnum START TARGET DIGITS: key presses for a debug number field."""
    emu.debug_enter(emu.const(f[1]), emu.const(f[2]), int(f[3]))


@script_op("givemon")
def _op_givemon(emu, f, path):
    """givemon SPECIES LEVEL: debug Give X > Pokemon (Basic). SPECIES_* names work."""
    emu.give_mon(emu.const(f[1]), emu.const(f[2]))
    print("givemon %s %s ok (party %d)" % (f[1], f[2], emu.r8(emu.sym("gPlayerPartyCount"))))


@script_op("giveegg")
def _op_giveegg(emu, f, path):
    """giveegg SPECIES: debug Give X > Give Egg."""
    emu.give_egg(emu.const(f[1]))
    print("giveegg %s ok (party %d)" % (f[1], emu.r8(emu.sym("gPlayerPartyCount"))))


@script_op("giveitem")
def _op_giveitem(emu, f, path):
    """giveitem ITEM QTY: debug Give X > Give item XYZ. ITEM_* names work."""
    emu.give_item(emu.const(f[1]), emu.const(f[2]))
    print("giveitem %s %s ok" % (f[1], f[2]))


@script_op("warpto")
def _op_warpto(emu, f, path):
    """warpto MAP_NAME X Y: warp by map constant (numbers from data/maps/map_groups.json)."""
    g, n = map_lookup(emu.elf, f[1])
    b, a = emu.warp(g, n, int(f[2], 0), int(f[3], 0))
    print("warpto %s (%d.%d) %s %s: SaveBlock1 %08X -> %08X" % (f[1], g, n, f[2], f[3], b, a))


@script_op("warptoloose")
def _op_warptoloose(emu, f, path):
    """warptoloose MAP_NAME X Y: like warpto, but a landing tile next to X,Y (a door moves the
    player off its warp tile) is fine as long as the map is the one asked for."""
    g, n = map_lookup(emu.elf, f[1])
    try:
        emu.warp(g, n, int(f[2], 0), int(f[3], 0))
    except HnsError as e:
        if "landed at" not in str(e):
            raise
        print("warptoloose %s: %s" % (f[1], e))
    print("warptoloose %s (%d.%d)" % (f[1], g, n))


@script_op("face")
def _op_face(emu, f, path):
    """face DIR: turn the player toward UP/DOWN/LEFT/RIGHT without walking (a 2-frame tap
    turns in place; the player then needs a few frames before input is read again)."""
    emu.frames(2, f[1])
    emu.frames(14)


@script_op("showtasks")
def _op_showtasks(emu, f, path):
    """showtasks: print callback2, the active tasks and the text printer state (debugging)."""
    print("showtasks @%d: callback2 %s, tasks %s, text %s, fade %s"
          % (emu.sync(), emu.cb2_name(), [t[2] for t in emu.tasks()], emu.text_state(), emu.fading()))


@script_op("seek")
def _op_seek(emu, f, path):
    """seek 8|16|32 HEXADDR VAL KEY [MAXPRESSES]: tap KEY (then wait for the screen to
    settle) until memory at ADDR equals VAL, e.g. a menu's cursor variable:
    `seek 8 @gPartyMenu+9@ 4 DOWN` (VAL may be a C constant)."""
    width, addr, val = int(f[1]), int(f[2], 16), emu.const(f[3])
    rd = {8: emu.r8, 16: emu.r16, 32: emu.r32}[width]
    mask = (1 << width) - 1
    for _ in range(_arg(f, 5, 40)):
        if rd(addr) == val & mask:
            print("seek %s == %s ok @%d" % (f[2], f[3], emu.sync()))
            return
        emu.tap(f[4], 4)
        emu.wait_quiet(600)
    if rd(addr) != val & mask:
        raise TourTimeout("seek: %s stayed %X after %s x%d (wanted %s)" % (f[2], rd(addr), f[4], _arg(f, 5, 40), f[3]))


@script_op("waitpmem")
def _op_waitpmem(emu, f, path):
    """waitpmem 8|16|32 PTRSYM HEXOFF VAL [MAX]: run until the field at OFF inside the
    struct that pointer variable PTRSYM points to holds VAL (a heap-allocated screen
    state, e.g. `waitpmem 8 trainer_card:sData 0 10`, or a callback by name,
    `waitpmem 32 region_map:sFlyMap 0 CB_HandleFlyMapInput`). A null pointer never matches."""
    width, ptr, off = int(f[1]), emu.sym(f[2]), int(f[3], 16)
    try:                                  # VAL: a number, a symbol (a callback) or a C constant
        val = int(f[4], 0)
    except ValueError:
        try:
            val = emu.sym(f[4])
        except HnsError:
            val = emu.const(f[4])
    rd = {8: emu.r8, 16: emu.r16, 32: emu.r32}[width]

    def ok():
        p = emu.r32(ptr)
        return p != 0 and rd(p + off) == val & ((1 << width) - 1)
    emu.wait_until(ok, _arg(f, 5, 600), "*%s+%s == %s" % (f[2], f[3], f[4]), step=2)
    print("waitpmem %s+%s == %s ok @%d" % (f[2], f[3], f[4], emu.sync()))


def avatar_settled(emu):
    """gPlayerAvatar.tileTransitionState (+3) is T_NOT_MOVING (include/global.fieldmap.h:409,
    422): the step has ended. SB1.pos changes at the START of a step."""
    return emu.r8(emu.sym("gPlayerAvatar") + 3) == 0


def go_step(emu, direction, maxframes=600):
    """One tile toward DIRECTION, or through the door/warp there. Returns 'step', 'warp'
    (another map loaded; waits until the player can walk, tapping nothing) or None
    when blocked. A press while facing elsewhere may only turn the player, so it presses
    twice at most."""
    (g, n, _, _, _), (x, y) = emu.location()
    for _ in range(2):
        emu.frames(8, direction)
        emu.frames(4)
        if (emu.location()[1] != (x, y) or not emu.in_overworld() or not avatar_settled(emu)
                or not emu.controllable()):
            break
        emu.frames(12)
    waited = 0
    while waited < maxframes:
        if not emu.in_overworld():
            if not emu.wait32(emu.CB2, emu.sym("CB2_Overworld"), 900):
                raise TourTimeout("go: the next map did not load (callback2 %s)" % emu.cb2_name())
            if not emu.wait_controllable(1200):
                raise TourTimeout("go: not controllable after the warp")
            return "warp"
        (g2, n2, _, _, _), (x2, y2) = emu.location()
        if (g2, n2) != (g, n):
            emu.wait_controllable(1200)
            return "warp"
        if (x2, y2) != (x, y) and emu.controllable() and avatar_settled(emu):
            return "step"
        if (x2, y2) == (x, y) and waited >= 24 and emu.controllable() and avatar_settled(emu):
            return None                   # did not move: blocked
        emu.frames(2)
        waited += 2
    return None


@script_op("go")
def _op_go(emu, f, path):
    """go DIR [N]: walk N tiles (default 1); stops early with a message after a warp
    (door, stairs) or when blocked. `go DOWN 9` walks out of a Pokemon Center."""
    n = _arg(f, 2, 1)
    for i in range(n):
        r = go_step(emu, f[1])
        if r != "step":
            break
    (g, m, _, _, _), (x, y) = emu.location()
    print("go %s %d: %s after %d step(s), at %d.%d (%d,%d) @%d"
          % (f[1], n, r or "blocked", i + 1, g, m, x, y, emu.sync()))


def text_pages(emu, prefix, maxpages=30, key="A", settle=10):
    """Screenshot every page of the message on screen (any screen, not only the field):
    wait until the text waits for a key, shot PREFIX_NN, press KEY; stop once no text
    waits for a key for SETTLE frames after the screen settled. Returns the page count."""
    n = 0
    while n < maxpages:
        emu.wait_quiet(1200, stable=settle)
        if not emu.wants_key():
            break
        emu.frames(2)
        n += 1
        emu.shot("%s_%02d" % (prefix, n))
        emu.shots = getattr(emu, "shots", []) + ["%s_%02d" % (prefix, n)]
        emu.tap(key, 0)
        # the key is read on the next frame; wait until the box no longer waits for it
        emu.wait_until(lambda: not emu.wants_key(), 60, "the text to take the key", step=1)
    return n


@script_op("pages")
def _op_pages(emu, f, path):
    """pages PREFIX [MAXPAGES] [KEY]: one shot per text page (PREFIX_01, ...) on any screen,
    pressing KEY (default A) after each; ends when no text waits for a key."""
    n = text_pages(emu, f[1], _arg(f, 2, 30), f[3] if len(f) > 3 else "A")
    print("pages %s: %d page(s) @%d" % (f[1], n, emu.sync()))


def pokenav_idle(emu):
    """The PokeNav/Pokegear (src/pokenav.c) reads input: Task_Pokenav is in state 3 and
    no looped task (Task_RunLoopedTask: page loads, slides) is running."""
    st = emu.task_data("Task_Pokenav")
    return (bool(st) and st[0][0] == 3 and not emu.tasks_named(["Task_RunLoopedTask"])
            and not emu.fading())


def pokenav_substruct(emu, first_word_sym):
    """The PokeNav substruct whose first word is FIRST_WORD_SYM (e.g. the radio's
    `callback = HandleRadioInput`, src/pokenav_radio.c:922). Scans the pointer table in
    *gPokenavResources (src/pokenav.c:17-25), so no enum index or offset is hard-coded."""
    res = emu.r32(emu.sym("gPokenavResources"))
    want = emu.sym(first_word_sym)
    raw = emu.read(res, 0x80)
    for off in range(0, 0x80, 4):
        p = int.from_bytes(raw[off:off + 4], "little")
        if 0x02000000 <= p < 0x02040000 and emu.r32(p) == want:
            return p
    raise HnsError("no PokeNav substruct starts with %s" % first_word_sym)


@script_op("radiotune")
def _op_radiotune(emu, f, path):
    """radiotune POS [MAXFRAMES]: hold RIGHT/LEFT on the Pokegear radio until
    Pokenav_Radio.tuningPos (+4, s32; src/pokenav_radio.c:94) is POS (0..63; stations at
    5, 13, 22, 25, 32, 41, 50, 57, 61, 63, src/pokenav_radio.c:152), release, waitnav."""
    want = emu.const(f[1])
    radio = pokenav_substruct(emu, "HandleRadioInput")
    pos = lambda: int.from_bytes(emu.read(radio + 4, 4), "little", signed=True)
    waited, limit = 0, _arg(f, 2, 600)
    while pos() != want:
        if waited >= limit:
            raise TourTimeout("radiotune: tuning stuck at %d (wanted %d)" % (pos(), want))
        emu.frames(1, "RIGHT" if pos() < want else "LEFT")
        waited += 1
    emu.frames(2)
    emu.wait_until(lambda: pokenav_idle(emu), 600, "the radio to tune", step=2)
    print("radiotune %d ok @%d" % (want, emu.sync()))


@script_op("radioline")
def _op_radioline(emu, f, path):
    """radioline N [MAXFRAMES]: wait until the radio shows line N of the station's text
    (Pokenav_Radio.currentLine, u8 at +12; lines scroll on a fixed timer,
    RADIO_SCROLL_DELAY, not on text length), then waitnav."""
    want = int(f[1])
    radio = pokenav_substruct(emu, "HandleRadioInput")
    emu.wait_until(lambda: emu.r8(radio + 12) == want, _arg(f, 2, 1200),
                   "radio line %d (numLines %d)" % (want, emu.r8(radio + 13)), step=1)
    emu.wait_until(lambda: pokenav_idle(emu), 600, "the radio to scroll", step=2)
    print("radioline %d ok @%d" % (want, emu.sync()))


@script_op("waitnav")
def _op_waitnav(emu, f, path):
    """waitnav [MAX]: run until the Pokegear (PokeNav) is idle and reads input (pokenav_idle),
    and the screen has settled."""
    emu.wait_until(lambda: pokenav_idle(emu), _arg(f, 1, 900), "the Pokegear to read input", step=2)
    emu.wait_quiet(600)
    print("waitnav ok @%d" % emu.sync())


# -- constants and maps, resolved from the source tree of the build under test

_CONST_CACHE = {}
_MAP_CACHE = {}


def src_dir(elf):
    return os.environ.get("HNS_SRC") or os.path.dirname(os.path.abspath(elf.path))


def resolve_const(elf, name):
    """A number (0x.. or decimal) or a C constant compiled against SRC/include."""
    try:
        return int(name, 0)
    except ValueError:
        pass
    src = src_dir(elf)
    key = (src, name)
    if key in _CONST_CACHE:
        return _CONST_CACHE[key]
    import tempfile
    d = tempfile.mkdtemp(prefix="hnsconst")
    try:
        c = os.path.join(d, "k.c")
        with open(c, "w") as fh:
            fh.write('#include "gba/types.h"\n#include "constants/global.h"\n'
                     '#include "constants/flags.h"\n#include "constants/vars.h"\n'
                     '#include "constants/species.h"\n#include "constants/items.h"\n'
                     '#include "constants/moves.h"\n'
                     'const unsigned int gK[] = { (unsigned int)(%s) };\n' % name)
        gcc = os.path.join(DEVKITARM, "bin", "arm-none-eabi-gcc")
        r = subprocess.run([gcc, "-iquote", os.path.join(src, "include"), "-Wno-trigraphs",
                            "-DMODERN=1", "-DTESTING=0", "-DPOKEMON_HNS", "-std=gnu17", "-mthumb",
                            "-mabi=apcs-gnu", "-O2", "-c", c, "-o", os.path.join(d, "k.o")],
                           capture_output=True, text=True)
        if r.returncode:
            raise HnsError("constant %s not found in %s/include: %s" % (name, src, r.stderr.strip()[-300:]))
        subprocess.run([os.path.join(DEVKITARM, "bin", "arm-none-eabi-objcopy"), "-O", "binary",
                        "-j", ".rodata", os.path.join(d, "k.o"), os.path.join(d, "k.bin")], check=True)
        v = int.from_bytes(open(os.path.join(d, "k.bin"), "rb").read()[:4], "little")
    finally:
        shutil.rmtree(d, ignore_errors=True)
    _CONST_CACHE[key] = v
    return v


def map_lookup(elf, name):
    src = src_dir(elf)
    if src not in _MAP_CACHE:
        _MAP_CACHE[src] = map_constants(src)
    if name not in _MAP_CACHE[src]:
        raise HnsError("map %s not in %s/data/maps" % (name, src))
    return _MAP_CACHE[src][name]


# ---------------------------------------------------------------------------- battle tours
# Part B (tours/battle_*.txt): battles and the screens around them.
# Every wait is on game state: the player's battle controller function, the battle script
# command being run, text printers and palette fades. Frame counts appear only as idle time
# after a key tap, so a tour survives text of another length.
#
# Struct offsets used below were measured with an offsetof() probe against include/ (the
# same method as probe/offsets.c); battle_check() compares the struct sizes with the ELF's
# object sizes before the first battle op, so a layout change fails loudly.
BATTLE_OFF = {
    "Pokemon.hp": 0x56,                       # struct Pokemon (include/pokemon.h), size 0x64
    "BattlePokemon.hp": 0x2A,                 # struct BattlePokemon (include/battle.h), size 0x88
    "BattleScripting.drawlvlupboxState": 0x1E,  # struct BattleScripting, size 0x3C
    "BattleScripting.learnMoveState": 0x1F,
    "SaveBlock3.challengeSettings": 0x10,     # struct SaveBlock3 (include/global.h:343), size 0x34
    "ChallengeSettings.fastBattle": (1, 0),   # (byte, bit) of the u8:1 bitfield (include/global.h:264)
    "Sprite.callback": 0x1C,                  # struct Sprite (include/sprite.h), size 0x44
    "Sprite.data": 0x2E,                      # s16 data[8]
    "Sprite.inUse": (0x3E, 0),
}
# ELF object sizes those offsets imply (gWindows: 32 x struct Window of 12 bytes).
BATTLE_SIZES = {"gPlayerParty": 6 * 0x64, "gEnemyParty": 6 * 0x64, "gBattleMons": 4 * 0x88,
                "gBattleScripting": 0x3C, "gSaveblock3": 0x34, "gSprites": 65 * 0x44,
                "gWindows": 32 * 12}

# A fixed SFC32 state for gRngValue (src/random.c:8). AdvanceRandom() steps it every VBlank
# (src/main.c:383), so without a pin every damage roll, critical hit, accuracy check, wild
# Pokemon's nature/IVs and AI choice depends on how many frames the text took. `hnsrun pin`
# rewrites it before every frame: results then depend only on the code path.
RNG_PIN = "B979379E157C4A7FBB49D09411000000"

# The player's battle controller (gBattlerControllerFuncs[0], src/battle_controller_player.c)
# sits in one of these while it reads input.
BATTLE_INPUT_FUNCS = ("HandleInputChooseAction", "HandleInputChooseMove", "HandleInputChooseTarget",
                      "HandleInputShowTargets", "HandleInputShowEntireFieldTargets",
                      "PlayerHandleYesNoInput", "HandleMoveSwitching")
# Battle script commands that wait for a yes/no answer (src/battle_script_commands.c:
# Cmd_yesnobox, Cmd_yesnoboxlearnmove, Cmd_yesnoboxstoplearningmove, Cmd_trygivecaughtmonnick,
# Cmd_givecaughtmon). Cmd_drawlvlupbox waits for any key in its states 6 and 8 (the two pages
# of the level-up stats window, src/battle_script_commands.c:6684-6702).
BATTLE_PROMPT_CMDS = ("Cmd_yesnobox", "Cmd_yesnoboxlearnmove", "Cmd_yesnoboxstoplearningmove",
                      "Cmd_trygivecaughtmonnick", "Cmd_givecaughtmon")
LVLUP_KEY_STATES = (6, 8)
# Screens that read input outside the battle loop: walking stops when one of these tasks
# runs (substring match on the task's function name).
SCREEN_INPUT_TASKS = ("Task_HandleChooseMonInput", "Task_HandleSelectionMenuInput",
                      "Task_BagMenu_HandleInput", "Task_HandleReplaceMoveInput",
                      "Task_HandleCaughtMonPageInput", "naming_screen:Task_HandleInput")


def battle_check(emu):
    if getattr(emu, "_battle_checked", False):
        return
    for name, size in BATTLE_SIZES.items():
        if emu.elf.size(name) != size:
            raise HnsError("%s is %d bytes, BATTLE_OFF was measured for %d: re-measure" % (name, emu.elf.size(name), size))
    emu._battle_checked = True


def pin_rng(emu, hexbytes=None):
    emu.expect_after("pin %08X %s" % (emu.sym("gRngValue"), hexbytes or RNG_PIN), r"^PIN ")


def unpin_rng(emu):
    emu.expect_after("unpin %08X" % emu.sym("gRngValue"), r"^UNPIN ")


def event_body(text, path=None):
    """A one-line event script ('a; b; c', ';' is the assembler's statement separator) or,
    for 'file NAME.inc', that file next to the tour."""
    f = text.split()
    if len(f) == 2 and f[0] == "file":
        return open(os.path.join(os.path.dirname(os.path.abspath(path or ".")), f[1]), encoding="utf-8").read()
    return text.replace(";", "\n") + "\n"


def event_start(emu, body, name="event"):
    """Assemble BODY (event-script source) with the build's own macros (evasm.py) into
    gRfuAPIBuffer and start it in the global script context, as ScriptContext_SetupScript
    does (src/script.c:281-289; same layout checks as ladder.py). Returns at once, so it
    suits scripts that start a battle (dowildbattle waits until the battle is over)."""
    if HERE not in sys.path:
        sys.path.insert(0, HERE)
    import evasm
    addr = emu.sym(evasm.RAM_BUFFER)
    data, _ = evasm.assemble(body, addr, emu.elf.path, src=src_dir(emu.elf), name=name)
    if len(data) > emu.elf.size(evasm.RAM_BUFFER):
        raise HnsError("event %s: %d bytes do not fit %s" % (name, len(data), evasm.RAM_BUFFER))
    if not emu.controllable():
        raise HnsError("event %s: the player is not controllable (callback2 %s)" % (name, emu.cb2_name()))
    ctx = emu.sym("sGlobalScriptContext")
    if emu.elf.size("sGlobalScriptContext") != 0x74 or emu.r32(ctx + 0x5C) != emu.sym("gScriptCmdTable"):
        raise HnsError("event: struct ScriptContext changed (see ladder.py CTX_*)")
    padded = data + b"\0" * (-len(data) % 4)
    for i in range(0, len(padded), 4):
        emu.w32(addr + i, int.from_bytes(padded[i:i + 4], "little"))
    emu.w32(ctx + 0, 1 << 8)                 # stackDepth 0, mode SCRIPT_MODE_BYTECODE
    emu.w32(ctx + 4, 0)                      # nativePtr
    emu.w32(ctx + 8, addr)                   # scriptPtr
    emu.w8(emu.sym("sLockFieldControls"), 1)
    emu.w8(emu.sym("sGlobalScriptContextStatus"), 0)     # CONTEXT_RUNNING
    emu.frames(1)


def event_run(emu, body, name="event", maxframes=3000):
    """event_start, then wait until the script has ended and the player is free."""
    event_start(emu, body, name)
    status = emu.sym("sGlobalScriptContextStatus")
    emu.wait_until(lambda: emu.r8(status) == 2 and emu.controllable(), maxframes,
                   "event %s to end" % name, step=4)


def in_battle(emu):
    return emu.cb2() == emu.sym("BattleMainCB2")


def battle_ctrl(emu, battler=0):
    """Function name of gBattlerControllerFuncs[BATTLER] (no FILE: prefix)."""
    return emu.elf.where(emu.r32(emu.sym("gBattlerControllerFuncs") + 4 * battler)).split(":")[-1]


def battle_cmd(emu):
    """Name of the battle script command at gBattlescriptCurrInstr (a callnative shows the
    native function it calls, e.g. BS_...)."""
    ip = emu.r32(emu.sym("gBattlescriptCurrInstr"))
    if not ip:
        return "?"
    b = emu.read(ip, 5)
    name = emu.elf.where(emu.r32(emu.sym("gBattleScriptingCommandsTable") + 4 * b[0]))
    if name.startswith("Cmd_callnative"):
        name = emu.elf.where(int.from_bytes(b[1:5], "little"))
    return name.split(":")[-1]


def battle_state(emu):
    gs = emu.sym("gBattleScripting")
    return (emu.r32(emu.sym("gBattlescriptCurrInstr")), emu.read(emu.sym("gBattleCommunication"), 2),
            emu.read(gs + BATTLE_OFF["BattleScripting.drawlvlupboxState"], 2), battle_ctrl(emu))


def battle_where(emu):
    """Short description of where the game is, for logs and errors."""
    s = "callback2 %s" % emu.cb2_name()
    if in_battle(emu):
        s += ", controller %s, command %s" % (battle_ctrl(emu), battle_cmd(emu))
    return s + ", tasks %s" % [t[2] for t in emu.tasks()]


def mem_crc(emu, addr, n):
    """(CRC-32, all bytes equal) of N bytes at ADDR, from hnsrun's `crc` command (an older
    hnsrun without it answers WARN: then the bytes are read and hashed here)."""
    import zlib
    m = emu.expect_after("crc %08X %d" % (addr, n), r"^(CRC %08X \d+ ([0-9A-F]{8}) ([01])|WARN)" % addr)
    if m.group(2):
        return int(m.group(2), 16), m.group(3) == "1"
    data = emu.read(addr, n)
    return zlib.crc32(data), len(set(data)) <= 1


def ability_popups(emu, tasks=None):
    """[(spriteId, battler)] of ability pop-ups that have slid in and wait (main sprite in
    APU_STATE_IDLE: sState = data[0] == 1, sIsMain = data[5], sBattlerId = data[4];
    src/battle_interface.c:2612-2624,2887-2930). Read only while Task_FreeAbilityPopUpGfx
    runs (it exists while any pop-up does); TASKS is emu.tasks() if the caller has it."""
    want = emu.sym("Task_FreeAbilityPopUpGfx")
    if not any(f == want for _, f, _ in (tasks if tasks is not None else emu.tasks())):
        return []
    cb, size = emu.sym("SpriteCb_AbilityPopUp"), 0x44
    raw = emu.read(emu.sym("gSprites"), emu.elf.size("gSprites"))
    cbo, do = BATTLE_OFF["Sprite.callback"], BATTLE_OFF["Sprite.data"]
    byte, bit = BATTLE_OFF["Sprite.inUse"]
    out = []
    for i in range(len(raw) // size):
        b = raw[i * size:(i + 1) * size]
        if not (b[byte] >> bit) & 1 or int.from_bytes(b[cbo:cbo + 4], "little") != cb:
            continue
        d = [int.from_bytes(b[do + 2 * j:do + 2 + 2 * j], "little", signed=True) for j in range(8)]
        if d[5] and d[0] == 1:
            out.append((i, d[4]))
    return out


def message_box(emu):
    """CRC of window 0's pixel buffer (gWindows[0].tileData; struct Window = WindowTemplate
    (8 bytes: bg, left, top, width, height, palette, u16 baseBlock) + tileData, include/
    window.h:27-49), or None when the window is missing or blank (one fill colour).
    Window 0 is B_WIN_MSG in battles and the evolution scene (left 2, top 15, 26x4 tiles,
    src/battle_bg.c:159-167) and the message box on the field (top 15, 27x4, src/menu.c:80-90);
    a window 0 that is not a box at the bottom of the screen (e.g. a Pokedex page shown
    during the battle) is ignored. Comparing pixels instead of strings catches every message
    whatever its source."""
    hdr = emu.read(emu.sym("gWindows"), 12)
    ptr = int.from_bytes(hdr[8:12], "little")
    if not ptr or not hdr[3] or not hdr[4] or hdr[2] < 14 or hdr[4] > 6:
        return None
    crc, uniform = mem_crc(emu, ptr, hdr[3] * hdr[4] * 32)
    return None if uniform else crc


# Screens whose window 0 is a message box (other screens number their windows differently).
MESSAGE_SCREENS = ("BattleMainCB2", "CB2_EvolutionSceneUpdate", "CB2_Overworld")


def battle_walk(emu, prefix, expect=(), maxpages=60, maxframes=3000, stop_tasks=()):
    """Walk through battle (and field) text, one screenshot PREFIX_NN per page:
      - a text box that waits for A (a printer parked on a page break, a field
        `waitbuttonpress`) or a page of the level-up stats window: shot, then A;
      - a message that does not wait for A: shot once it is fully printed and the screen is
        quiet (it stays up while Cmd_waitmessage pauses or the move animation plays; see
        fastbattles). A message is new when the pixels of the message box changed since the
        last shot (or since the previous walk ended, when the player chose an action);
      - an ability pop-up once it has slid in.
    Stops at the first state that wants a decision:
      input:FUNC     the player's controller reads input (action menu, move menu, yes/no)
      prompt:CMD     a battle-script yes/no (learn a move, nickname, switch, ...)
      task:FUNC      a screen outside the battle reads input (party menu, bag, summary,
                     naming screen, caught-Pokemon dex page; SCREEN_INPUT_TASKS + STOP_TASKS)
      free           the player can walk again
    EXPECT (substrings) must match the end state, or the walk fails. A is pressed only
    while something waits for it, never blind (B would cancel an evolution).
    Returns (pages, end)."""
    battle_check(emu)
    n, idle = 0, 0
    bcb2 = emu.sym("BattleMainCB2")
    msg_cb2 = set()
    for name in MESSAGE_SCREENS:
        try:
            msg_cb2.add(emu.sym(name))
        except HnsError:
            pass
    stops = tuple(SCREEN_INPUT_TASKS) + tuple(stop_tasks)
    keystates = emu.TEXT_KEY_STATES
    # On a slower build the first message may already be up when the walk starts, so the
    # baseline is the box as the previous walk left it.
    last = getattr(emu, "_bw_box", None)
    if last is None:
        last = message_box(emu)
    popped = set()

    def shoot(kind, press):
        nonlocal n, idle, last
        emu.frames(1 if kind == "popup" else 2)
        name = "%s_%02d" % (prefix, n + 1)
        path = emu.shot(name)
        if kind != "popup":
            last = message_box(emu) if emu.cb2() in msg_cb2 else last
        idle = 0
        _, _, rows = read_png_rgb(path)
        if len(set(rows)) == 1 and len(set(rows[0][i:i + 3] for i in range(0, len(rows[0]), 3))) == 1:
            os.remove(path)                       # one colour (a screen faded to black): not a page
            print("  %-5s (blank screen skipped; %s)" % (kind, battle_where(emu)))
        else:
            n += 1
            emu.shots = getattr(emu, "shots", []) + [name]
            print("  %-5s %s (%s)" % (kind, name, battle_where(emu)))
        if press:
            emu.tap("A", 0)

    def done(end):
        emu._bw_box = message_box(emu) if emu.cb2() in msg_cb2 else None
        if expect and not any(e in end for e in expect):
            raise HnsError("%s: walked %d page(s) and stopped at %s, expected %s (%s)"
                           % (prefix, n, end, " or ".join(expect), battle_where(emu)))
        return n, end

    while True:
        if n >= maxpages:
            return done("maxpages")
        if idle >= maxframes:
            raise TourTimeout("%s: nothing to press for %d frames after %d page(s) (%s)"
                              % (prefix, idle, n, battle_where(emu)))
        tasks = emu.tasks()
        pops = ability_popups(emu, tasks)
        fresh = [p for p in pops if p not in popped]
        popped = set(p for p in popped if p in pops) | set(fresh)
        if fresh:                                # an ability pop-up is fully shown
            shoot("popup", False)
            continue
        drawing = [w for _, s, a, w in emu.text_printers() if a and s not in keystates]
        if drawing or emu.fading():
            emu.frames(2)
            idle += 2
            continue
        wants = emu.wants_key()
        if not wants:
            hit = [t for _, _, t in tasks for s in stops if s in t]
            if hit:
                emu.frames(2)
                return done("task:" + hit[0])
        cb2 = emu.cb2()
        if wants:
            if cb2 in msg_cb2 and message_box(emu) == last:
                emu.tap("A", 0)                   # this page was already shot as a message
                idle = 0
            else:
                shoot("text", True)
            continue
        battle = cb2 == bcb2
        if battle:
            # battler 2 is the player's second Pokemon in a double battle (gBattlersCount 4);
            # its stops are reported as input:FUNC#2
            for b in ((0, 2) if emu.r8(emu.sym("gBattlersCount")) > 2 else (0,)):
                c = battle_ctrl(emu, b)
                if c in BATTLE_INPUT_FUNCS:
                    emu.frames(2)
                    return done("input:" + c + ("#%d" % b if b else ""))
        if cb2 in msg_cb2:
            box = message_box(emu)
            if box is not None and box != last:
                shoot("msg", False)
                continue
        if battle:
            cmd = battle_cmd(emu)
            if cmd == "Cmd_drawlvlupbox" or cmd in BATTLE_PROMPT_CMDS:
                s0 = battle_state(emu)
                emu.frames(8)
                idle += 8
                if battle_state(emu) == s0 and not emu.fading() and battle_cmd(emu) == cmd:
                    if cmd != "Cmd_drawlvlupbox":
                        return done("prompt:" + cmd)
                    if s0[2][0] in LVLUP_KEY_STATES:
                        shoot("lvlup", True)
                continue
        elif emu.controllable() and emu.r8(emu.sym("gPlayerAvatar") + 3) == 0:
            emu.frames(8)                         # tileTransitionState T_NOT_MOVING: the step is over
            if emu.controllable():
                return done("free")
        emu.frames(2)
        idle += 2


def wait_battle_input(emu, func, maxframes=1200, battler=0):
    """Run until the player's controller (BATTLER 0, or 2 for the second Pokemon in a double
    battle) is FUNC (e.g. HandleInputChooseAction) and the screen is quiet."""
    battle_check(emu)
    emu.wait_until(lambda: in_battle(emu) and battle_ctrl(emu, battler) == func, maxframes,
                   "battle controller %s of battler %d" % (func, battler))
    emu.wait_quiet(maxframes)
    emu.frames(2)


def set_party_hp(emu, side, slot, hp):
    """Poke the plain (unencrypted) hp field of gPlayerParty/gEnemyParty[SLOT] and, during a
    battle, of the matching gBattleMons entry (side player = battler 0, enemy = battler 1;
    singles only)."""
    battle_check(emu)
    party = emu.sym("gPlayerParty" if side == "player" else "gEnemyParty")
    emu.w16(party + 0x64 * slot + BATTLE_OFF["Pokemon.hp"], hp)
    if in_battle(emu) and slot == 0:
        battler = 0 if side == "player" else 1
        emu.w16(emu.sym("gBattleMons") + 0x88 * battler + BATTLE_OFF["BattlePokemon.hp"], hp)


for _n, _f in (("pin_rng", pin_rng), ("unpin_rng", unpin_rng), ("event_start", event_start),
               ("event_run", event_run), ("in_battle", in_battle), ("battle_ctrl", battle_ctrl),
               ("battle_cmd", battle_cmd), ("battle_walk", battle_walk),
               ("wait_battle_input", wait_battle_input), ("set_party_hp", set_party_hp)):
    setattr(Emu, _n, _f)


@script_op("pinrng")
def _op_pinrng(emu, f, path):
    """pinrng [HEX32]: pin gRngValue (16 bytes, default RNG_PIN) before every frame."""
    pin_rng(emu, f[1] if len(f) > 1 else None)
    print("pinrng %s @%d" % (f[1] if len(f) > 1 else RNG_PIN, emu.sync()))


@script_op("unpinrng")
def _op_unpinrng(emu, f, path):
    unpin_rng(emu)


@script_op("ev")
def _op_ev(emu, f, path):
    """ev STATEMENT; STATEMENT; ...   or   ev file NAME.inc
    Run an event script (the ROM's own script language and constants, assembled by evasm.py)
    and wait until it has ended and the player is free. E.g.
        ev givemon SPECIES_CYNDAQUIL, 12, move1=MOVE_EMBER; setflag FLAG_BADGE01_GET; end"""
    body = event_body(" ".join(f[1:]), path)
    event_run(emu, body, "ev_" + os.path.splitext(os.path.basename(path))[0])
    print("ev ok @%d" % emu.sync())


@script_op("evstart")
def _op_evstart(emu, f, path):
    """evstart STATEMENT; ...: start an event script and return at once (for dowildbattle)."""
    event_start(emu, event_body(" ".join(f[1:]), path), "evs_" + os.path.splitext(os.path.basename(path))[0])
    print("evstart @%d" % emu.sync())


@script_op("waitbattle")
def _op_waitbattle(emu, f, path):
    """waitbattle [MAX]: run until callback2 is BattleMainCB2 (the battle has been set up)."""
    emu.wait_until(lambda: in_battle(emu), _arg(f, 1, 1200), "the battle to start", step=4)
    print("waitbattle ok @%d" % emu.sync())


@script_op("bwalk")
def _op_bwalk(emu, f, path):
    """bwalk PREFIX [EXPECT|EXPECT...] [MAXPAGES]: battle_walk (one shot per page that waits for
    A, PREFIX_01, ...) until a decision is needed. EXPECT is one or more '|'-separated
    substrings of the end state, e.g. input:HandleInputChooseAction, prompt:Cmd_yesnobox,
    task:Task_HandleChooseMonInput, free."""
    expect = tuple(f[2].split("|")) if len(f) > 2 else ()
    n, end = battle_walk(emu, f[1], expect, _arg(f, 3, 60))
    print("bwalk %s: %d page(s), ended %s @%d" % (f[1], n, end, emu.sync()))


@script_op("waitbinput")
def _op_waitbinput(emu, f, path):
    """waitbinput FUNC [MAX]: run until the player's battle controller is FUNC and quiet."""
    wait_battle_input(emu, f[1], _arg(f, 2, 1200))
    print("waitbinput %s ok @%d" % (f[1], emu.sync()))


@script_op("waitbinputb")
def _op_waitbinputb(emu, f, path):
    """waitbinputb BATTLER FUNC [MAX]: waitbinput for another player battler (2: the second
    Pokemon in a double battle)."""
    wait_battle_input(emu, f[2], _arg(f, 3, 1200), int(f[1]))
    print("waitbinputb %s %s ok @%d" % (f[1], f[2], emu.sync()))


@script_op("bactionb")
def _op_bactionb(emu, f, path):
    """bactionb BATTLER FIGHT|BAG|POKEMON|RUN [nopress]: baction for another player battler."""
    b = int(f[1])
    wait_battle_input(emu, "HandleInputChooseAction", battler=b)
    battle_cursor(emu, "gActionSelectionCursor", BATTLE_ACTIONS[f[2].upper()], battler=b)
    if not (len(f) > 3 and f[3] == "nopress"):
        emu.tap("A", 4)


@script_op("bmoveb")
def _op_bmoveb(emu, f, path):
    """bmoveb BATTLER SLOT [nopress]: bmove for another player battler."""
    b = int(f[1])
    wait_battle_input(emu, "HandleInputChooseMove", battler=b)
    battle_cursor(emu, "gMoveSelectionCursor", int(f[2]), battler=b)
    if not (len(f) > 3 and f[3] == "nopress"):
        emu.tap("A", 4)


@script_op("expectbcmd")
def _op_expectbcmd(emu, f, path):
    """expectbcmd CMD: stop unless the battle script is at command CMD."""
    if battle_cmd(emu) != f[1]:
        raise HnsError("expectbcmd %s: at %s" % (f[1], battle_where(emu)))


@script_op("sethp")
def _op_sethp(emu, f, path):
    """sethp player|enemy SLOT HP: poke a party Pokemon's current HP (see set_party_hp)."""
    set_party_hp(emu, f[1], int(f[2]), int(f[3], 0))
    print("sethp %s %s = %s" % (f[1], f[2], f[3]))


BATTLE_ACTIONS = {"FIGHT": 0, "BAG": 1, "POKEMON": 2, "RUN": 3}


def battle_cursor(emu, var, target, maxkeys=4, battler=0):
    """Move a 2x2 battle menu cursor (bit 0 = column, bit 1 = row, as in
    HandleInputChooseAction / HandleInputChooseMove) at VAR[BATTLER] to TARGET."""
    addr = emu.sym(var) + battler
    for _ in range(maxkeys):
        cur = emu.r8(addr)
        if cur == target:
            return
        if (cur ^ target) & 1:
            emu.tap("RIGHT" if target & 1 else "LEFT", 4)
        elif (cur ^ target) & 2:
            emu.tap("DOWN" if target & 2 else "UP", 4)
    if emu.r8(addr) != target:
        raise HnsError("%s stayed at %d, wanted %d (%s)" % (var, emu.r8(addr), target, battle_where(emu)))


@script_op("baction")
def _op_baction(emu, f, path):
    """baction FIGHT|BAG|POKEMON|RUN [nopress]: move the action-menu cursor
    (gActionSelectionCursor) there and press A."""
    wait_battle_input(emu, "HandleInputChooseAction")
    battle_cursor(emu, "gActionSelectionCursor", BATTLE_ACTIONS[f[1].upper()])
    if not (len(f) > 2 and f[2] == "nopress"):
        emu.tap("A", 4)


@script_op("bmove")
def _op_bmove(emu, f, path):
    """bmove SLOT [nopress]: in the move menu, move the cursor (gMoveSelectionCursor) to move
    SLOT (0-3, top-left first) and press A."""
    wait_battle_input(emu, "HandleInputChooseMove")
    battle_cursor(emu, "gMoveSelectionCursor", int(f[1]))
    if not (len(f) > 2 and f[2] == "nopress"):
        emu.tap("A", 4)


def set_fast_battles(emu, on):
    """The FAST BATTLES option (OPTIONS > BATTLE; ChallengeSettings.fastBattle, 0 = ON). OFF
    keeps every battle message on screen for its waitmessage time, which battle_walk needs
    to photograph messages that do not wait for A."""
    battle_check(emu)
    byte, bit = BATTLE_OFF["ChallengeSettings.fastBattle"]
    addr = emu.r32(emu.sym("gSaveBlock3Ptr")) + BATTLE_OFF["SaveBlock3.challengeSettings"] + byte
    v = emu.r8(addr)
    emu.w8(addr, (v & ~(1 << bit)) if on else (v | (1 << bit)))


@script_op("fastbattles")
def _op_fastbattles(emu, f, path):
    """fastbattles on|off: set the FAST BATTLES option (see set_fast_battles)."""
    set_fast_battles(emu, f[1].lower() == "on")
    print("fastbattles %s" % f[1])


@script_op("waitnotfree")
def _op_waitnotfree(emu, f, path):
    """waitnotfree [MAX]: run until the player is no longer free (a script took over, e.g. a
    trainer who spotted the player)."""
    emu.wait_until(lambda: not emu.controllable(), _arg(f, 1, 600), "a script to take over", step=2)
    print("waitnotfree ok @%d" % emu.sync())


# struct NamingScreenData (src/naming_screen.c:160): three u8[0x800] tilemap buffers,
# u8 textBuffer[16], u8 tileBuffer[0x600], then u8 state -> offset 0x1E10. The states of
# Task_NamingScreen (src/naming_screen.c:127-139): FADE_IN 0, WAIT_FADE_IN 1, HANDLE_INPUT 2,
# MOVE_TO_OK_BUTTON 3, START_PAGE_SWAP 4, WAIT_PAGE_SWAP 5, PRESSED_OK 6, ...
NAMING_STATE_OFF, NAMING_HANDLE_INPUT = 0x1E10, 2


@script_op("waitnaming")
def _op_waitnaming(emu, f, path):
    """waitnaming [MAX]: run until the naming screen reads input again (after it faded in,
    or after a keyboard page swap), then until the screen is quiet."""
    try:
        ptr = emu.sym("sNamingScreen")
    except HnsError:
        ptr = emu.sym("naming_screen:sNamingScreen")

    def ready():
        p = emu.r32(ptr)
        return p and emu.r8(p + NAMING_STATE_OFF) == NAMING_HANDLE_INPUT
    emu.wait_until(ready, _arg(f, 1, 600), "the naming screen to read input", step=2)
    emu.wait_quiet(600)
    print("waitnaming ok @%d" % emu.sync())


# ---------------------------------------------------------------------------- tours
# A tour is a script in emu/tours/ whose first command is `start SAVE`:
#   start saves/ladder1_newgame.sav   a ladder save in HNS_SAVES (another relative path is
#                                     relative to emu/, an absolute one is used as is)
#   start save:NAME                   the battery another tour exported with `keepsave NAME`
#                                     in this OUTDIR (that tour runs first if needed)
#   start empty                       an empty battery (for NEW GAME)
# Files whose name starts with '_' are includes, not tours.

TOURS_DIR = os.path.join(HERE, "tours")


def resolve_save(path):
    """The file a tour's `start` names: saves/NAME is NAME in the save ladder (HNS_SAVES)."""
    if os.path.isabs(path):
        return path
    if path.startswith("saves/"):
        if not paths.SAVES:
            raise HnsError("start %s: the save ladder is not set (HNS_SAVES)" % path)
        return os.path.join(paths.SAVES, path[len("saves/"):])
    return os.path.join(HERE, path)


def tour_start(path):
    for raw in open(path, encoding="utf-8"):
        line = raw.split("#", 1)[0].strip()
        if not line:
            continue
        f = line.split()
        if f[0] != "start" or len(f) < 2:
            raise HnsError("%s: the first command must be 'start SAVE'" % path)
        return f[1]
    raise HnsError("%s: empty tour" % path)


def tour_exports(path):
    out = []
    for raw in open(path, encoding="utf-8"):
        f = raw.split("#", 1)[0].split()
        if len(f) >= 2 and f[0] == "keepsave":
            out.append(f[1])
    return out


# Memory regions (address >> 24). The game runs code from the BIOS, EWRAM, IWRAM, the ROM and the
# ROM's wait-state mirrors (0A-0B wait state 1, 0C-0D wait state 2). The mirrors are normal: the
# script command table stores every command that requests effects as its address plus ROM_SIZE
# (data/script_cmd_table.inc), and RunScriptCommand calls it there (src/script.c). The ELF names
# ROM addresses only, so a mirror address is named by the ROM address it mirrors.
ROM_REGIONS = (0x08, 0x09)
ROM_MIRROR_REGIONS = (0x0A, 0x0B, 0x0C, 0x0D)
CODE_REGIONS = (0x00, 0x02, 0x03) + ROM_REGIONS + ROM_MIRROR_REGIONS   # hnsrun.c pcIsSane
SYMBOL_REGIONS = (0x02, 0x03) + ROM_REGIONS + ROM_MIRROR_REGIONS       # where the ELF has symbols


def rom_unmirror(addr):
    """ADDR folded from a ROM wait-state mirror (0x0A000000-0x0DFFFFFF) onto the ROM
    (0x08000000-0x09FFFFFF); any other address unchanged."""
    if (addr >> 24) in ROM_MIRROR_REGIONS:
        return 0x08000000 | (addr & 0x01FFFFFF)
    return addr


def pc_is_sane(pc):
    """PC check for CRASH: code runs from BIOS (0x00), EWRAM/IWRAM (0x02/0x03), ROM (0x08/0x09)
    or the ROM's wait-state mirrors (0x0A-0x0D, CODE_REGIONS). Anything else means the game
    jumped through a bad pointer (hnsrun stops by itself when its 60-frame check reads such a PC:
    pcIsSane in hnsrun.c, the same regions). A release build has no assert screen."""
    return (pc >> 24) in CODE_REGIONS


def clip_hook(emu, outdir):
    """`tour --clip`: report the RTL clip log after every screenshot (tools/hebrew/cliptour.py)."""
    sys.path.insert(0, os.path.dirname(HERE))
    import cliptour
    try:
        return cliptour.install(emu, outdir)
    except RuntimeError as e:
        raise HnsError(str(e))


def strings_hook(emu, logdir):
    """HNS_STRCOV=LOGDIR or `tour --strings LOGDIR`: log the ROM strings an RTL_STRING_REPORT build
    copied or printed, after every screenshot (tools/hebrew/strcov.py)."""
    sys.path.insert(0, os.path.dirname(HERE))
    import strcov
    if getattr(emu, "strcov", None) is not None:
        return emu.strcov
    try:
        return strcov.install(emu, os.path.abspath(logdir))
    except RuntimeError as e:
        raise HnsError(str(e))


def clip_count(emu):
    rep = getattr(emu, "clip", None)
    return rep.total() if rep else None


def run_tours(rom, elf, outdir, only=None, rtc=None, verbose=False, reuse_saves=False,
              tours_dir=TOURS_DIR, clip=False):
    import glob
    import time
    outdir = os.path.abspath(outdir)
    os.makedirs(os.path.join(outdir, "_saves"), exist_ok=True)
    allt = {os.path.splitext(os.path.basename(p))[0]: p
            for p in sorted(glob.glob(os.path.join(tours_dir, "*.txt")))
            if not os.path.basename(p).startswith("_")}
    producers = {}
    for name, p in allt.items():
        for s in tour_exports(p):
            producers[s] = name
    selected = [n for n in allt if not only or re.search(only, n)]
    results, order = {}, []

    def run_one(name, why=""):
        if name in results:
            return results[name]
        path = allt[name]
        start = tour_start(path)
        save_src = None
        if start.startswith("save:"):
            sname = start[5:]
            spath = os.path.join(outdir, "_saves", sname + ".sav")
            if not (reuse_saves and os.path.exists(spath)):
                if sname not in producers:
                    raise HnsError("%s: no tour exports save:%s" % (name, sname))
                dep = run_one(producers[sname], "needed by " + name)
                if dep["status"] != "OK":
                    results[name] = dict(status="SKIPPED", detail="dependency %s %s" % (producers[sname], dep["status"]),
                                         shots=0, frames=0, secs=0.0, why=why)
                    order.append(name)
                    return results[name]
            save_src = spath
        elif start != "empty":
            save_src = resolve_save(start)
            if not os.path.exists(save_src):
                raise HnsError("%s: start save %s does not exist" % (name, save_src))
        tdir = os.path.join(outdir, name)
        os.makedirs(tdir, exist_ok=True)
        for old in glob.glob(os.path.join(tdir, "*.png")):
            os.remove(old)
        cur = os.path.join(tdir, "cur.sav")
        if os.path.exists(cur):
            os.remove(cur)
        if save_src:
            shutil.copyfile(save_src, cur)
        t0 = time.time()
        status, detail, frames = "OK", "", 0
        emu = Emu(rom, elf, tdir, cur, rtc, verbose)
        try:
            if clip:
                clip_hook(emu, tdir)
            emu.run_script(path)
            frames = emu.sync()
            pc = emu.pc()
            where = elf.where(pc)
            if not pc_is_sane(pc):
                status, detail = "CRASH", "pc=%08X (%s) at the end" % (pc, where)
        except HnsError as e:
            msg = str(e)
            if msg.startswith("CRASH") or "runner exited" in msg:
                status, detail = "CRASH", msg.splitlines()[0]
            elif isinstance(e, TourTimeout) or "timed out" in msg or "TIMEOUT" in msg or "did not" in msg:
                status, detail = "TIMEOUT", msg
            else:
                status, detail = "ERROR", msg
            if status != "CRASH":
                try:                       # a game stuck on its crash/assert screen
                    pc = emu.pc()
                    if not pc_is_sane(pc):
                        status, detail = "CRASH", "pc=%08X (%s): %s" % (pc, elf.where(pc), msg)
                    emu.shot("_" + status.lower())      # what the screen showed when it stopped
                except HnsError:
                    pass
        finally:
            rc = emu.close()
            with open(os.path.join(tdir, "run.log"), "w") as fh:
                fh.write("\n".join(emu.log) + "\n")
        if rc == 3 and status != "CRASH":
            status, detail = "CRASH", next((l for l in emu.log if l.startswith("CRASH")), "runner exit 3")
        if status == "OK":
            for s in getattr(emu, "keep_saves", []):
                shutil.copyfile(cur, os.path.join(outdir, "_saves", s + ".sav"))
        shots = sorted(os.path.basename(p) for p in glob.glob(os.path.join(tdir, "*.png"))
                       if not os.path.basename(p).startswith("_"))
        res = dict(status=status, detail=detail, shots=len(shots), frames=frames,
                   secs=round(time.time() - t0, 1), why=why,
                   shot_names=[os.path.splitext(x)[0] for x in shots])
        if clip:
            res["clipped"] = clip_count(emu)
        results[name] = res
        order.append(name)
        print("%-28s %-8s %3d shots %7d frames %6.1fs %s%s" % (
            name, status, len(shots), frames, res["secs"], ("(" + why + ") ") if why else "",
            detail.splitlines()[0][:160] if detail else ""))
        sys.stdout.flush()
        return res

    for n in selected:
        try:
            run_one(n)
        except HnsError as e:
            results[n] = dict(status="ERROR", detail=str(e), shots=0, frames=0, secs=0.0, why="")
            order.append(n)
            print("%-28s ERROR    %s" % (n, e))
    with open(os.path.join(outdir, "tour_report.json"), "w") as fh:
        json.dump({"rom": os.path.abspath(rom), "tours": {n: results[n] for n in order}}, fh, indent=1)
    bad = [n for n in order if results[n]["status"] != "OK"]
    print("%d tour(s): %d OK, %d not OK%s" % (len(order), len(order) - len(bad), len(bad),
                                              (" (" + ", ".join(bad) + ")") if bad else ""))
    return 1 if bad else 0


def read_png_rgb(path):
    """(w, h, rows) for the PNGs hnsrun writes (8-bit RGB, filter 0, one IDAT)."""
    import struct
    import zlib
    data = open(path, "rb").read()
    pos, idat, w, h = 8, b"", 0, 0
    while pos < len(data):
        n, typ = struct.unpack(">I4s", data[pos:pos + 8])
        body = data[pos + 8:pos + 8 + n]
        if typ == b"IHDR":
            w, h = struct.unpack(">II", body[:8])
        elif typ == b"IDAT":
            idat += body
        pos += 12 + n
    raw = zlib.decompress(idat)
    stride = 1 + w * 3
    return w, h, [raw[y * stride + 1:(y + 1) * stride] for y in range(h)]


def write_png_rgb(path, w, h, rows):
    import struct
    import zlib
    def chunk(t, d):
        return struct.pack(">I", len(d)) + t + d + struct.pack(">I", zlib.crc32(t + d) & 0xFFFFFFFF)
    raw = b"".join(b"\0" + r for r in rows)
    with open(path, "wb") as fh:
        fh.write(b"\x89PNG\r\n\x1a\n" + chunk(b"IHDR", struct.pack(">IIBBBBB", w, h, 8, 2, 0, 0, 0))
                 + chunk(b"IDAT", zlib.compress(raw, 6)) + chunk(b"IEND", b""))


def contact_sheet(pngs, out, cols=4, gap=4):
    """Tile 240x160 screenshots into one PNG (row-major, in the order given)."""
    imgs = [read_png_rgb(p) for p in pngs]
    if not imgs:
        raise HnsError("contact sheet: no images")
    w, h = imgs[0][0], imgs[0][1]
    rows_n = (len(imgs) + cols - 1) // cols
    W, H = cols * w + (cols - 1) * gap, rows_n * h + (rows_n - 1) * gap
    blank = b"\x40\x40\x40"
    canvas = [bytearray(blank * W) for _ in range(H)]
    for i, (iw, ih, rows) in enumerate(imgs):
        x0, y0 = (i % cols) * (w + gap), (i // cols) * (h + gap)
        for y in range(min(ih, h)):
            canvas[y0 + y][x0 * 3:(x0 + min(iw, w)) * 3] = rows[y][:min(iw, w) * 3]
    write_png_rgb(out, W, H, [bytes(r) for r in canvas])
    return out


def tour_diff(a, b):
    """Compare the screenshots of two tour OUTDIRs byte for byte."""
    import glob
    fa = {os.path.relpath(p, a) for p in glob.glob(os.path.join(a, "*", "*.png"))}
    fb = {os.path.relpath(p, b) for p in glob.glob(os.path.join(b, "*", "*.png"))}
    same, diff = 0, []
    for p in sorted(fa & fb):
        if open(os.path.join(a, p), "rb").read() == open(os.path.join(b, p), "rb").read():
            same += 1
        else:
            diff.append(p)
    for p in diff:
        print("DIFF   %s" % p)
    for p in sorted(fa - fb):
        print("ONLY1  %s" % p)
    for p in sorted(fb - fa):
        print("ONLY2  %s" % p)
    print("%d identical, %d differ, %d only in %s, %d only in %s"
          % (same, len(diff), len(fa - fb), a, len(fb - fa), b))
    return 0 if not diff and fa == fb else 1


# ---------------------------------------------------------------------------- render

LIVE = ("SB1", "SB2", "SB3", "LOC", "POS")
EXTENSIONS = ("include", "echo", "waitcb2", "waittask", "waitctl", "expect8", "expect16",
              "expect32", "expectflag", "expectloc", "warp", "savegame", "debugmenu",
              "setflag", "clearflag", "setvar", "ifsym", "endif")


def render(path, elf, out):
    """Expand includes and static @SYMBOL@ markers into a script bare hnsrun can read.
    Fails on anything that needs the live game (@SB1@, waittask, warp, ...)."""
    gmain = elf.sym("gMain")
    fixed = {"CB1": gmain + OFF["Main.callback1"], "CB2": gmain + OFF["Main.callback2"]}
    base = os.path.dirname(os.path.abspath(path))
    for n, raw in enumerate(open(path, encoding="utf-8"), 1):
        line = raw.rstrip("\n")
        code = line.split("#", 1)[0].strip()
        if not code:
            out.write(line + "\n")
            continue
        op = code.split()[0]
        if op == "include":
            render(os.path.join(base, code.split()[1]), elf, out)
            continue
        if op in EXTENSIONS or op in SCRIPT_OPS:
            raise HnsError("%s:%d: '%s' needs hns.py run (not plain hnsrun)" % (path, n, op))
        def rep(m):
            name = m.group(1)
            if name in LIVE:
                raise HnsError("%s:%d: @%s@ is read live; use hns.py run" % (path, n, name))
            v = fixed[name] if name in fixed else elf.sym(name)
            if m.group(2):
                v += int(m.group(2), 16)
            return "%08X" % (v & 0xFFFFFFFF)
        out.write(Emu.MARK.sub(rep, code) + "\n")


# ---------------------------------------------------------------------------- checks

def selfcheck(rom, elf, save, outdir=None):
    """Static: struct sizes in the ELF still match the ones OFF was measured against.
    Live: boot SAVE with scripts/continue.txt and check that what OFF points at is sane."""
    bad = 0
    def check(ok, msg):
        nonlocal bad
        print("%s  %s" % ("ok  " if ok else "FAIL", msg))
        bad += not ok
    check(elf.size("gSaveblock1") - SAVEBLOCK_MOVE_RANGE == SIZES["SaveBlock1"],
          "sizeof(SaveBlock1) = 0x%X (measured 0x%X)" % (elf.size("gSaveblock1") - SAVEBLOCK_MOVE_RANGE, SIZES["SaveBlock1"]))
    check(elf.size("gSaveblock2") - SAVEBLOCK_MOVE_RANGE == SIZES["SaveBlock2"],
          "sizeof(SaveBlock2) = 0x%X (measured 0x%X)" % (elf.size("gSaveblock2") - SAVEBLOCK_MOVE_RANGE, SIZES["SaveBlock2"]))
    check(elf.size("gMain") == SIZES["Main"], "sizeof(struct Main) = 0x%X" % elf.size("gMain"))
    check(elf.size("gTasks") == 16 * SIZES["Task"], "sizeof(gTasks) = 0x%X" % elf.size("gTasks"))
    if not save or not os.path.exists(save):
        print("no save, skipping the live checks")
        return 1 if bad else 0
    outdir = outdir or os.path.join(paths.WORK, "selfcheck")
    emu = Emu(rom, elf, outdir, prepare_save(save, outdir, False))
    try:
        emu.run_script(os.path.join(HERE, "scripts", "continue.txt"))
        sb1, base = emu.sb1(), emu.sym("gSaveblock1")
        check(0 <= sb1 - base < SAVEBLOCK_MOVE_RANGE and (sb1 - base) % 4 == 0,
              "gSaveBlock1Ptr %08X = gSaveblock1 + 0x%X" % (sb1, sb1 - base))
        sb2 = emu.sb2()
        check(sb2 - emu.sym("gSaveblock2") == sb1 - base, "gSaveBlock2Ptr moved by the same offset")
        hdr = emu.sym("gMapHeader")
        lid = emu.r16(sb1 + OFF["SB1.mapLayoutId"])
        check(lid == emu.r16(hdr + OFF["MapHeader.mapLayoutId"]) and lid != 0,
              "SB1.mapLayoutId (%d) == gMapHeader.mapLayoutId" % lid)
        layout = emu.r32(hdr)
        w, h = emu.r32(layout), emu.r32(layout + 4)
        (g, n, _, _, _), (x, y) = emu.location()
        check(0 <= x < w and 0 <= y < h, "SB1.pos (%d,%d) inside the %dx%d map %d.%d" % (x, y, w, h, g, n))
        name = emu.read(sb2 + OFF["SB2.playerName"], 8)
        check(0xFF in name and name.index(0xFF) > 0, "SB2.playerName is terminated: %s" % name.hex())
        emu.shot("selfcheck")
    finally:
        emu.close()
    print("%d check(s) failed" % bad if bad else "all checks passed")
    return 1 if bad else 0


# ---------------------------------------------------------------------------- CLI

def prepare_save(src, outdir, keep):
    """Run on a copy so an in-game save never overwrites the ladder save."""
    if not src:
        return None
    if keep:
        return src
    dst = os.path.join(os.path.abspath(outdir), "cur.sav")
    os.makedirs(outdir, exist_ok=True)
    if os.path.exists(src):
        shutil.copyfile(src, dst)
    elif os.path.exists(dst):
        os.remove(dst)
    return dst


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--rom", default=None)
    ap.add_argument("--elf", default=None)
    ap.add_argument("--rtc", default=None, help="HNS_RTC unix seconds")
    ap.add_argument("-v", "--verbose", action="store_true", help="echo runner output")
    sub = ap.add_subparsers(dest="cmd", required=True)
    p = sub.add_parser("run"); p.add_argument("script"); p.add_argument("outdir")
    p.add_argument("--save", help="battery save to boot with (copied to OUTDIR/cur.sav; "
                                  "a path that does not exist means an empty save)")
    p.add_argument("--keep-save", action="store_true",
                   help="write to SAVE itself instead of OUTDIR/cur.sav")
    p.add_argument("--save-out", help="after a clean run, copy the resulting .sav here")
    p = sub.add_parser("warp"); p.add_argument("outdir")
    for a in ("group", "num", "x", "y"):
        p.add_argument(a, type=lambda s: int(s, 0))
    p.add_argument("--save", required=True); p.add_argument("--then")
    p.add_argument("--boot", default=os.path.join(HERE, "scripts", "continue.txt"))
    p = sub.add_parser("selfcheck"); p.add_argument("--outdir", default=None)
    p.add_argument("--save", default=paths.save("ladder1_newgame.sav"))
    p = sub.add_parser("render"); p.add_argument("script")
    p = sub.add_parser("tour", help="run the screen tours in emu/tours (see run_tours)")
    p.add_argument("tour_rom"); p.add_argument("outdir")
    p.add_argument("--only", default=None, help="regex on tour names")
    p.add_argument("--reuse-saves", action="store_true",
                   help="use OUTDIR/_saves/NAME.sav from an earlier run instead of re-running its producer")
    p.add_argument("--tours", default=TOURS_DIR, help="tour directory")
    p.add_argument("--clip", action="store_true",
                   help="RTL_CLIP_REPORT build: report glyphs drawn outside their window per screenshot "
                        "(tools/hebrew/cliptour.py; OUTDIR/TOUR/clip.json)")
    p.add_argument("--strings", metavar="LOGDIR",
                   help="RTL_STRING_REPORT build: log the ROM strings copied or printed per screenshot "
                        "(tools/hebrew/strcov.py; LOGDIR/*.jsonl; same as HNS_STRCOV=LOGDIR)")
    p = sub.add_parser("tourdiff", help="compare the screenshots of two tour OUTDIRs")
    p.add_argument("a"); p.add_argument("b")
    p = sub.add_parser("sheet", help="tile screenshots into one PNG (a contact sheet)")
    p.add_argument("out"); p.add_argument("pngs", nargs="+"); p.add_argument("--cols", type=int, default=4)
    p = sub.add_parser("sym"); p.add_argument("names", nargs="+")
    p = sub.add_parser("where"); p.add_argument("addrs", nargs="+")
    p = sub.add_parser("map"); p.add_argument("pattern")
    sub.add_parser("offsets")
    args = ap.parse_args()

    rom = args.rom or DEFAULT_ROM
    elf_path = args.elf or os.environ.get("HNS_ELF") if not args.rom else (args.elf or os.path.splitext(rom)[0] + ".elf")
    elf_path = elf_path or os.path.splitext(rom)[0] + ".elf"

    try:
        if args.cmd == "offsets":
            for k, v in OFF.items():
                print("%-28s 0x%X" % (k, v))
            return 0
        if args.cmd == "tourdiff":
            return tour_diff(args.a, args.b)
        if args.cmd == "sheet":
            pngs = []
            for p in args.pngs:
                pngs += sorted((os.path.join(p, x) for x in os.listdir(p)
                                if x.endswith(".png") and not x.startswith(("_", "ct0"))),
                               key=os.path.getmtime) if os.path.isdir(p) else [p]
            for i, p in enumerate(pngs):
                print("%2d %s" % (i, os.path.basename(p)))
            contact_sheet(pngs, args.out, args.cols)
            return 0
        if args.cmd == "tour":
            rom = args.tour_rom
            elf_path = args.elf or os.path.splitext(rom)[0] + ".elf"
            if args.strings:
                if "gRtlStringSet" not in Elf(elf_path).byname:
                    raise HnsError("%s is not an RTL_STRING_REPORT build (make hns RTL_STRING_REPORT=1)" % elf_path)
                os.environ["HNS_STRCOV"] = os.path.abspath(args.strings)
            return run_tours(rom, Elf(elf_path), args.outdir, args.only, args.rtc, args.verbose,
                             args.reuse_saves, args.tours, args.clip)
        elf = Elf(elf_path)
        if args.cmd == "sym":
            for n in args.names:
                print("%-32s %08X  size %d" % (n, elf.sym(n), elf.size(n)))
            return 0
        if args.cmd == "selfcheck":
            return selfcheck(rom, elf, args.save, args.outdir)
        if args.cmd == "render":
            render(args.script, elf, sys.stdout)
            return 0
        if args.cmd == "where":
            for a in args.addrs:
                print("%08X  %s" % (int(a, 16), elf.where(int(a, 16))))
            return 0
        if args.cmd == "map":
            src = os.environ.get("HNS_SRC") or os.path.dirname(os.path.abspath(elf_path))
            rx = re.compile(args.pattern, re.I)
            for k, (g, n) in map_constants(src).items():
                if rx.search(k):
                    print("%-48s group %3d  num %3d" % (k, g, n))
            return 0
        if args.cmd == "run":
            save = prepare_save(args.save, args.outdir, args.keep_save)
            if args.save_out and not save:
                save = prepare_save(os.path.join(args.outdir, "cur.sav"), args.outdir, False)
            emu = Emu(rom, elf, args.outdir, save, args.rtc, args.verbose)
            try:
                emu.run_script(args.script)
            finally:
                rc = emu.close()
                with open(os.path.join(emu.outdir, "run.log"), "w") as f:
                    f.write("\n".join(emu.log) + "\n")
            if rc == 0 and args.save_out:
                # hnsrun flushes the battery save when the core is torn down (core->deinit)
                shutil.copyfile(save, args.save_out)
                print("save written: %s (%d bytes)" % (args.save_out, os.path.getsize(args.save_out)))
            return rc
        if args.cmd == "warp":
            save = prepare_save(args.save, args.outdir, False)
            emu = Emu(rom, elf, args.outdir, save, args.rtc, args.verbose)
            try:
                emu.run_script(args.boot)
                b, a = emu.warp(args.group, args.num, args.x, args.y)
                print("warp %d.%d (%d,%d): SaveBlock1 %08X -> %08X" % (args.group, args.num, args.x, args.y, b, a))
                emu.shot("warp")
                if args.then:
                    emu.run_script(args.then)
            finally:
                rc = emu.close()
                with open(os.path.join(emu.outdir, "run.log"), "w") as f:
                    f.write("\n".join(emu.log) + "\n")
            return rc
    except HnsError as e:
        sys.stderr.write("hns: %s\n" % e)
        return 1


if __name__ == "__main__":
    sys.exit(main())
