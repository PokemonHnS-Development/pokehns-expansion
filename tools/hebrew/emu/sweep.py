#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Show every live script text label in the field message box on a real ROM and report
the ones that clip, crash, hang or misbehave.

    sweep.py run ROM OUTDIR [--save SAV] [label selection] [--shots none|clip|all]
                 [--restart-every N] [--resume]
    sweep.py report OUTDIR                 rebuild OUTDIR/sweep.json + report.txt from results.jsonl
    sweep.py selftest ROM OUTDIR [--label L] prove the clip detector end to end: patch one label's
                                           first line break into a space in a COPY of the ROM and
                                           check that the sweep reports CLIP there and not on the
                                           unpatched ROM (needs a clip build)

ROM is a build with its ELF next to it (--elf overrides). Labels, constants and macros come
from the source tree next to the ELF (--src or HNS_SRC override). For clip detection the ROM
must be a clip build (`make hns RTL_CLIP_REPORT=1` -> pokehns-clip.gba); any other build is
still checked for CRASH / HANG / ABNORMAL, and its CLIP column reads n/a.

Label selection (default: every live script text label in HNS_UNITS/*/*.json (--units), kind
'script', in unit-file order; '#2' variants of one label are one label):
    --label NAME (repeatable) | --labels-file FILE (one label per line, '#' comments)
    --match RE (label) | --file RE (source file) | --batch RE (unit file name, e.g. B03 or B03_02)
    --translated (the unit file has a Hebrew text) | --hebrew-only (the string in THIS ROM has
    Hebrew letters; run only) | --sample N [--seed S]
    --offset N | --limit N
With no --label or --labels-file and no unit files, run, list and selftest exit 2.

How one label runs:
  1. Once per run: boot with the save, CONTINUE, walk out if the save stands in a Pokemon
     Center, wait for the map-name pop-up to go, set text speed INSTANT, fill STR_VAR_1..3
     (--strvars), write a tiny event script into gRfuAPIBuffer and save a state (_base.ss).
  2. Per label: load that state, point the script's `message` at the label, start the global
     script context (as ScriptContext_SetupScript does) and let hnsrun's wait32 tap A every 30
     frames until the script's last command writes a sentinel byte:
         nop; nop; lockall; message LABEL; waitmessage; waitbuttonpress; closemessage;
         releaseall; setptr 0x5A, SENTINEL; end
     Then read the clip log (gRtlClipCount/gRtlClipLog), gStringVar4 (the expanded text the
     box drew), gMain's callbacks, the script status and the PC, all in one pipelined batch.
  3. Status: CRASH (PC outside BIOS/RAM/ROM, or the runner died), HANG (no sentinel within the
     frame budget), ABNORMAL (sentinel set but not controllable afterwards, callbacks changed,
     expanded text overflows gStringVar4), CLIP (glyphs drawn outside their window), OK, SKIP
     (no symbol in this ELF, not a .string, no terminator). Warnings: a page with a 3rd row.
  4. The emulator is restarted (from _base.ss) every --restart-every labels and after every
     CRASH / HANG / ABNORMAL. results.jsonl is appended per label, so --resume continues.
"""
import argparse
import datetime
import glob
import hashlib
import json
import os
import random
import re
import shutil
import struct
import sys
import time

HERE = os.path.dirname(os.path.abspath(__file__))
TOOLS = os.path.dirname(HERE)
sys.path.insert(0, HERE)
sys.path.insert(0, TOOLS)
import hns                       # noqa: E402
from hns import HnsError         # noqa: E402
import paths                     # noqa: E402

UNITS_DIR = paths.UNITS
DEFAULT_SAVE = paths.save("ladder4_league.sav")
DEFAULT_STRVARS = ("bufferspeciesname STR_VAR_1, SPECIES_TYPHLOSION; "
                   "bufferspeciesname STR_VAR_2, SPECIES_FERALIGATR; "
                   "bufferspeciesname STR_VAR_3, SPECIES_MEGANIUM")
PLACEHOLDER_PTR = 0x08FEDCB8          # assembled into the template, patched per label
SENTINEL_VALUE = 0x5A
SENTINEL_OFF = 0x80                   # sentinel word: gRfuAPIBuffer + 0x80 (after the script)
TAP_PERIOD = 30                       # hnsrun wait32 taps its keys for 3 frames every 30
FIELD_ROWS = 2                        # the field message box holds two rows of FONT_NORMAL

EOS, NEWLINE, PLACEHOLDER, CTRL, PROMPT_CLEAR, PROMPT_SCROLL = 0xFF, 0xFE, 0xFD, 0xFC, 0xFB, 0xFA
EXTRA_SYMBOL, KEYPAD_ICON, DYNAMIC = 0xF9, 0xF8, 0xF7
CTRL_PAUSE, CTRL_PAUSE_UNTIL_PRESS = 0x08, 0x09
STATUS_ORDER = ("CRASH", "HANG", "ABNORMAL", "CLIP", "OK", "SKIP")
# what the clipped line holds in the label itself, most actionable first (Sweeper.source_line)
CLIP_KINDS = ("translated", "translated+placeholder", "untranslated+placeholder", "untranslated")


def tw():
    import textwidth
    return textwidth


# ---------------------------------------------------------------------------- labels

def load_units(units_dir=UNITS_DIR):
    """Live script text labels from the unit files, in file order:
    [{label, files, batch, translated}]; 'X#2' variants fold into X."""
    out, idx = [], {}
    for path in sorted(glob.glob(os.path.join(units_dir, "*", "*.json"))):
        d = json.load(open(path, encoding="utf-8"))
        items = d if isinstance(d, list) else d.get("units", [])
        batch = os.path.splitext(os.path.basename(path))[0]
        for u in items:
            if not isinstance(u, dict) or u.get("kind") != "script" or not u.get("live"):
                continue
            label = u["key"].split("#")[0]
            if label not in idx:
                idx[label] = dict(label=label, files=[], batch=batch, translated=False)
                out.append(idx[label])
            e = idx[label]
            if u["file"] not in e["files"]:
                e["files"].append(u["file"])
            e["translated"] = e["translated"] or bool(re.search("[\u05d0-\u05ea]", u.get("he") or ""))
    return out


def no_units(a):
    """No --label or --labels-file and no unit files to take labels from: a setup error, exit 2.
    (A filter that matches nothing in existing units is not one; that selection is just empty.)"""
    sys.stderr.write("sweep: no script units in %s (make_chunks.py writes them there; "
                     "--units or HNS_UNITS points elsewhere)\n" % a.units)
    raise SystemExit(2)


def select_labels(a):
    units = load_units(a.units)
    by = {u["label"]: u for u in units}
    explicit = list(a.label or [])
    if a.labels_file:
        for raw in open(a.labels_file, encoding="utf-8"):
            s = raw.split("#", 1)[0].strip()
            if s:
                explicit.append(s.split()[0])          # `sweep.py list` output works too
    if explicit:
        sel = [by.get(n, dict(label=n, files=[], batch="", translated=False)) for n in explicit]
    else:
        if not units:
            no_units(a)
        sel = units
    if a.match:
        sel = [u for u in sel if re.search(a.match, u["label"])]
    if a.file:
        sel = [u for u in sel if any(re.search(a.file, f) for f in u["files"])]
    if a.batch:
        sel = [u for u in sel if re.search(a.batch, u["batch"])]
    if a.translated:
        sel = [u for u in sel if u["translated"]]
    if a.sample and a.sample < len(sel):
        keep = set(id(u) for u in random.Random(a.seed).sample(sel, a.sample))
        sel = [u for u in sel if id(u) in keep]
    if a.offset:
        sel = sel[a.offset:]
    if a.limit:
        sel = sel[:a.limit]
    return sel


# ---------------------------------------------------------------------------- the build

class Target(object):
    """ROM bytes, ELF symbols, charmap and the source tree of one build."""

    def __init__(self, rom, elf=None, src=None, charmap=None):
        self.rom = os.path.abspath(rom)
        self.elf_path = os.path.abspath(elf or os.path.splitext(self.rom)[0] + ".elf")
        self.src = os.path.abspath(src or os.environ.get("HNS_SRC") or os.path.dirname(self.elf_path))
        os.environ["HNS_SRC"] = self.src           # hns.resolve_const / map_lookup / event_start
        self.elf = hns.Elf(self.elf_path)
        with open(self.rom, "rb") as fh:
            self.rom_bytes = fh.read()
        self.sha1 = hashlib.sha1(self.rom_bytes).hexdigest()
        cm = charmap or os.path.join(self.src, "charmap.txt")
        self.charmap = tw().Charmap(cm)
        self.clip = "gRtlClipLog" in self.elf.byname and "gRtlClipCount" in self.elf.byname
        self._directives = {}

    def rom_sha1_now(self):
        h = hashlib.sha1()
        with open(self.rom, "rb") as fh:
            for chunk in iter(lambda: fh.read(1 << 20), b""):
                h.update(chunk)
        return h.hexdigest()

    def label_addr(self, label):
        recs = self.elf.byname.get(label)
        if not recs:
            return None
        addrs = sorted({r[0] for r in recs})
        return addrs[0] if len(addrs) == 1 else addrs

    def rom_string(self, addr, limit=4096):
        off = addr - 0x08000000
        if off < 0 or off >= len(self.rom_bytes):
            return None
        end = self.rom_bytes.find(bytes([EOS]), off, off + limit)
        return None if end < 0 else self.rom_bytes[off:end + 1]

    def directive(self, label, files):
        """First assembler directive after `label:` in its source file(s): '.string',
        '.braille', ... or None when the label is not found there."""
        for f in files:
            path = os.path.join(self.src, f)
            if path not in self._directives:
                self._directives[path] = self._scan(path)
            d = self._directives[path].get(label)
            if d:
                return d
        return None

    @staticmethod
    def _scan(path):
        out = {}
        if not os.path.exists(path):
            return out
        pending = []
        for raw in open(path, encoding="utf-8", errors="replace"):
            line = raw.split("@", 1)[0].strip() if not raw.lstrip().startswith(".string") else raw.strip()
            if not line or line.startswith("//") or line.startswith("#"):
                continue
            m = re.match(r"^([A-Za-z_][A-Za-z0-9_]*)::?\s*(.*)$", line)
            if m:
                pending.append(m.group(1))
                line = m.group(2).strip()
                if not line:
                    continue
            if re.match(r"^\.(if|ifdef|ifndef|else|elseif|endif)\b", line):
                continue
            word = line.split()[0]
            for lab in pending:
                out.setdefault(lab, word)
            pending = []
        return out


def iter_tokens(data):
    """(offset, kind, value) over an encoded string, skipping control-code arguments:
    kind is 'eos', 'n', 'l', 'p', 'ctrl' (value = code, args), 'ph', 'glyph'."""
    i, n = 0, len(data)
    args_of = tw().CTRL_ARGS
    while i < n:
        b = data[i]
        if b == EOS:
            yield i, "eos", None
            return
        if b == NEWLINE:
            yield i, "n", None
            i += 1
        elif b == PROMPT_SCROLL:
            yield i, "l", None
            i += 1
        elif b == PROMPT_CLEAR:
            yield i, "p", None
            i += 1
        elif b == CTRL and i + 1 < n:
            code = data[i + 1]
            k = args_of.get(code, 0)
            yield i, "ctrl", (code, bytes(data[i + 2:i + 2 + k]))
            i += 2 + k
        elif b in (PLACEHOLDER, KEYPAD_ICON, EXTRA_SYMBOL, DYNAMIC) and i + 1 < n:
            yield i, "ph" if b == PLACEHOLDER else "glyph", data[i + 1]
            i += 2
        else:
            yield i, "glyph", b
            i += 1


def key_presses(data):
    """A/B presses a string needs: one per \\p, \\l and {PAUSE_UNTIL_PRESS}; plus the pause
    frames of {PAUSE n}."""
    keys, pause = 0, 0
    for _, kind, v in iter_tokens(data):
        if kind in ("p", "l"):
            keys += 1
        elif kind == "ctrl" and v[0] == CTRL_PAUSE_UNTIL_PRESS:
            keys += 1
        elif kind == "ctrl" and v[0] == CTRL_PAUSE and v[1]:
            pause += v[1][0]
    return keys, pause


def count_pages(data):
    """Boxes the reader sees: stretches between \\p / \\l that draw something."""
    n, drawn = 0, False
    for _, kind, _ in iter_tokens(data):
        if kind in ("glyph", "ph"):
            drawn = True
        elif kind in ("p", "l", "eos"):
            n += drawn
            drawn = False
    return n + drawn


def page_rows(data):
    """[(offset, page, row)] for every token, and the pages whose row count passes FIELD_ROWS.
    \\n moves down a row, \\l scrolls (same row), \\p starts a new page."""
    pos, over = [], []
    page, row = 1, 1
    for off, kind, _ in iter_tokens(data):
        pos.append((off, page, row))
        if kind == "n":
            row += 1
            if row > FIELD_ROWS and (page, row) not in over:
                over.append((page, row))
        elif kind == "p":
            page, row = page + 1, 1
    return pos, over


def text_lines(data):
    """Token lists of each line of DATA (split at \\n, \\l and \\p): [[(off, kind, value)]]."""
    lines = [[]]
    for tok in iter_tokens(data):
        if tok[1] in ("n", "l", "p"):
            lines.append([])
        elif tok[1] != "eos":
            lines[-1].append(tok)
    return lines


def line_of(data, off):
    """Index of the line (as text_lines counts them) that holds offset OFF."""
    n = 0
    for o, kind, _ in iter_tokens(data):
        if o >= off:
            break
        if kind in ("n", "l", "p"):
            n += 1
    return n


def where_in_text(pos, off):
    page, row = 1, 1
    for o, p, r in pos:
        if o > off:
            break
        page, row = p, r
    return page, row


# ---------------------------------------------------------------------------- the runner

class Sweeper(object):
    def __init__(self, target, outdir, save, strvars, text_speed="instant", echo=False,
                 leave_center="auto", max_frames=None):
        self.t = target
        self.outdir = os.path.abspath(outdir)
        self.work = os.path.join(self.outdir, "_work")
        self.shotdir = os.path.join(self.outdir, "shots")
        os.makedirs(self.work, exist_ok=True)
        self.save_src = save
        self.strvars = strvars
        self.text_speed = text_speed
        self.echo = echo
        self.leave_center = leave_center
        self.max_frames = max_frames
        self.faults = {}
        self.player_name = None
        self.strvar_plain = None
        self.emu = None
        self.base_state = os.path.join(self.work, "_base.ss")
        self.boots = 0
        e = self.t.elf
        self.buf = e.sym("gRfuAPIBuffer")
        self.ctx = e.sym("sGlobalScriptContext")
        self.status = e.sym("sGlobalScriptContextStatus")
        self.lock = e.sym("sLockFieldControls")
        self.sv4 = e.sym("gStringVar4")
        self.sv4_size = e.size("gStringVar4")
        self.gmain = e.sym("gMain")
        self.cb1_ow, self.cb2_ow = e.sym("CB1_Overworld"), e.sym("CB2_Overworld")
        self.sentinel = self.buf + SENTINEL_OFF
        if self.t.clip:
            self.clip_log, self.clip_count = e.sym("gRtlClipLog"), e.sym("gRtlClipCount")
            self.clip_lo = min(self.clip_log, self.clip_count)
            self.clip_len = max(self.clip_log + 16 * 12, self.clip_count + 4) - self.clip_lo

    # -- paths hnsrun can take (its command parser keeps 127 characters)
    def _short(self, path):
        rel = os.path.relpath(path)
        p = rel if len(rel) < len(path) else path
        if len(p) > 120:
            raise HnsError("path too long for hnsrun (%d chars): %s; use a shorter OUTDIR" % (len(p), p))
        return p

    # -- boot
    def _start_runner(self):
        cur = os.path.join(self.work, "cur.sav")
        if self.save_src:
            shutil.copyfile(self.save_src, cur)
        self.emu = hns.Emu(self.t.rom, self.t.elf, self.work, cur if self.save_src else None, None, self.echo)
        self.boots += 1

    def boot(self):
        """Cold boot -> CONTINUE -> controllable outside -> settings -> template -> _base.ss."""
        self._start_runner()
        emu = self.emu
        if not emu.wait_cb2("CB2_MainMenu", 4000, "START"):
            raise HnsError("boot: main menu not reached (callback2 %s)" % emu.cb2_name())
        if not emu.wait_task("Task_HandleMainMenuInput", 600):
            raise HnsError("boot: main menu does not read input")
        emu.tap("A", 30)
        if not emu.wait_cb2("CB2_Overworld", 1200):
            raise HnsError("boot: CONTINUE did not reach the overworld (callback2 %s)" % emu.cb2_name())
        if not emu.wait_controllable(1200, "B"):
            raise HnsError("boot: not controllable after CONTINUE (callback2 %s)" % emu.cb2_name())
        (g, n, _, _, _), _ = emu.location()
        name = self.map_name(g, n)
        self.start_map = "%s (%d.%d)" % (name, g, n)
        if self.leave_center == "yes" or (self.leave_center == "auto" and "POKEMON_CENTER" in name):
            import ladder
            g2, n2, x2, y2 = ladder.leave_center(emu)
            self.start_map = "%s (%d.%d) at (%d,%d), walked out of %s" % (
                self.map_name(g2, n2), g2, n2, x2, y2, name)
        try:
            popup = emu.sym("Task_MapNamePopUpWindow")
        except HnsError:
            popup = None
        waited = 0
        while popup and waited < 900 and any(f == popup for _, f, _ in emu.tasks()):
            emu.frames(10)
            waited += 10
        if not emu.wait_controllable(1200, "B"):
            raise HnsError("boot: not controllable outside (callback2 %s)" % emu.cb2_name())
        sb2 = emu.sb2()
        v = emu.r16(sb2 + 0x14)                  # SaveBlock2.optionsTextSpeed:3 (include/global.h)
        self.save_text_speed = v & 7
        if self.text_speed == "instant":
            emu.w16(sb2 + 0x14, (v & ~7) | 3)    # OPTIONS_TEXT_SPEED_INSTANT
        if self.player_name:
            enc = encode_plain(self.t.charmap, self.player_name)
            if len(enc) > 7:
                raise HnsError("--player: %d bytes, the name holds 7" % len(enc))
            for i, b in enumerate(enc + bytes([EOS])):
                emu.w8(sb2 + i, b)
        if self.strvars and self.strvars.lower() != "none":
            hns.event_run(emu, hns.event_body(self.strvars) + "\tend\n", "sweep_strvars", 600)
        for name, text in zip(("gStringVar1", "gStringVar2", "gStringVar3"), self.strvar_plain or ()):
            enc = encode_plain(self.t.charmap, text) + bytes([EOS])
            for i, b in enumerate(enc[:self.t.elf.size(name)]):
                emu.w8(emu.sym(name) + i, b)
        self.strvar_text = [self.decode(emu.read(emu.sym(s), 64)).rstrip("$") for s in
                            ("gStringVar1", "gStringVar2", "gStringVar3")]
        self.player = self.decode(emu.read(emu.sb2(), 8)).rstrip("$")
        # the event script, assembled once with the build's own macros
        import evasm
        body = ("\tnop\n\tnop\n\tlockall\n\tmessage 0x%08X\n\twaitmessage\n\twaitbuttonpress\n"
                "\tclosemessage\n\treleaseall\n\tsetptr 0x%X, 0x%08X\n\tend\n"
                % (PLACEHOLDER_PTR, SENTINEL_VALUE, self.sentinel))
        data, _ = evasm.assemble(body, self.buf, self.t.elf_path, src=self.t.src, name="sweep_message")
        k = data.find(struct.pack("<I", PLACEHOLDER_PTR))
        if k < 0 or k % 4 or len(data) > SENTINEL_OFF:
            raise HnsError("sweep template: placeholder at %d, %d bytes" % (k, len(data)))
        self.operand = self.buf + k
        self.sentinel_operand = self.buf + data.find(struct.pack("<I", self.sentinel))
        padded = data + b"\0" * (-len(data) % 4)
        for i in range(0, len(padded), 4):
            emu.w32(self.buf + i, int.from_bytes(padded[i:i + 4], "little"))
        emu.w32(self.sentinel, 0)
        emu.frames(4)
        if not emu.controllable():
            raise HnsError("boot: not controllable before the base state")
        emu.expect_after("ss %s" % self._short(self.base_state), r"^STATE ss .* (ok|FAIL)")
        self.base_clip = emu.r32(self.clip_count) if self.t.clip else None
        self.base_frame = emu.sync()

    def restart(self):
        if self.emu:
            try:
                self.emu.close()
            except Exception:
                pass
        if self.t.rom_sha1_now() != self.t.sha1:
            raise HnsError("the ROM changed on disk during the sweep (%s)" % self.t.rom)
        self._start_runner()

    def close(self):
        if self.emu:
            try:
                self.emu.close()
            except Exception:
                pass
            self.emu = None

    def map_name(self, g, n):
        if not hasattr(self, "_maps"):
            self._maps = {v: k for k, v in hns.map_constants(self.t.src).items()}
        return self._maps.get((g, n), "?")

    def decode(self, data, stop=True):
        return self.t.charmap.decode(bytes(data), stop_at_eos=stop)

    # -- one label
    def precheck(self, lab):
        """A SKIP result, or None when the label is a string this build has."""
        addr = self.t.label_addr(lab["label"])
        if addr is None:
            return dict(status="SKIP", detail="no symbol in this ELF (not assembled into this build)")
        if isinstance(addr, list):
            return dict(status="SKIP", detail="ambiguous symbol: %s" % ", ".join("%08X" % x for x in addr))
        if addr >> 24 not in (0x08, 0x09):
            return dict(status="SKIP", detail="symbol at %08X is not in ROM" % addr, addr="%08X" % addr)
        d = self.t.directive(lab["label"], lab.get("files") or [])
        if d == ".braille":
            return dict(status="SKIP", detail="braille text (.braille)", addr="%08X" % addr)
        if d is not None and d != ".string":
            return dict(status="SKIP", detail="not text: the label is followed by %s" % d, addr="%08X" % addr)
        raw = self.t.rom_string(addr)
        if raw is None:
            return dict(status="SKIP", detail="no string terminator within 4096 bytes", addr="%08X" % addr)
        lab["addr"], lab["raw"] = addr, raw
        return None

    def budget(self, raw):
        if self.max_frames:
            return self.max_frames
        keys, pause = key_presses(raw)
        return 600 + 2 * TAP_PERIOD * (keys + 2) + pause * 2

    def _arm(self, addr):
        return ["sl %s" % self._short(self.base_state),
                "w32 %08X %08X" % (self.operand, addr),
                "w32 %08X 100" % self.ctx,                       # stackDepth 0, mode BYTECODE
                "w32 %08X 0" % (self.ctx + 4),                   # nativePtr
                "w32 %08X %08X" % (self.ctx + 8, self.buf),      # scriptPtr
                "w8 %08X FF" % self.sv4,                         # empty: proves `message` expanded the text
                "w8 %08X 1" % self.lock,
                "w8 %08X 0" % self.status]                       # CONTEXT_RUNNING

    def _fault(self, label):
        """--fault KIND:LABEL, to prove the CRASH/HANG paths: 'crash' points gMain.callback2
        at 0C000001 (open bus; hnsrun stops on the PC), 'hang' points the template's sentinel
        write elsewhere so the script ends but the sentinel never comes."""
        kind = self.faults.get(label)
        if kind == "crash":
            return ["w32 %08X 0C000001" % (self.gmain + hns.OFF["Main.callback2"])]
        if kind == "hang":
            return ["w32 %08X %08X" % (self.sentinel_operand, self.sentinel + 4)]
        return []

    def _send(self, lines):
        e = self.emu
        if e.p.poll() is not None:
            raise HnsError("runner is not running (exit %s)" % e.p.returncode)
        e.p.stdin.write("\n".join(lines) + "\n")
        e.p.stdin.flush()

    @staticmethod
    def _mem(m):
        return bytes(int(x, 16) for x in m.group(1).split())

    def run_fast(self, lab):
        """One label with no screenshots: one pipelined batch of runner commands."""
        e = self.emu
        frames = self.budget(lab["raw"])
        cmds = self._arm(lab["addr"]) + self._fault(lab["label"]) + [
            "wait32 %08X %08X %d A" % (self.sentinel, SENTINEL_VALUE, frames),
            "read %08X 8" % self.gmain,
            "read %08X 2" % self.status,
            "read %08X %d" % (self.sv4, self.sv4_size)]
        if self.t.clip:
            cmds.append("read %08X %d" % (self.clip_lo, self.clip_len))
        cmds.append("pc")
        self._send(cmds)
        m = e.expect(r"^STATE sl \S+ (ok|FAIL)")
        if m.group(1) != "ok":
            raise HnsError("loading the base state failed")
        w = e.expect(r"^WAIT (ok|TIMEOUT) %08X(?: after (\d+))?" % self.sentinel)
        gm = self._mem(e.expect(r"^MEM %08X:((?: [0-9A-F]{2})*)" % self.gmain))
        st = self._mem(e.expect(r"^MEM %08X:((?: [0-9A-F]{2})*)" % self.status))
        sv4 = self._mem(e.expect(r"^MEM %08X:((?: [0-9A-F]{2})*)" % self.sv4))
        clip = self._mem(e.expect(r"^MEM %08X:((?: [0-9A-F]{2})*)" % self.clip_lo)) if self.t.clip else None
        pc = int(e.expect(r"^PC ([0-9A-F]{8})").group(1), 16)
        del e.log[:-40]
        res = dict(frames=int(w.group(2)) if w.group(2) else frames)
        return self.classify(lab, res, w.group(1) == "ok", gm, st, sv4, clip, pc)

    def classify(self, lab, res, done, gm, st, sv4, clip, pc):
        cb1, cb2 = struct.unpack("<II", gm)
        problems, warnings = [], []
        end = sv4.find(bytes([EOS]))
        text_bytes = sv4 if end < 0 else sv4[:end + 1]
        res["len"] = len(text_bytes) - (0 if end < 0 else 1)
        res["keys"], _ = key_presses(text_bytes)
        res["pages"] = count_pages(text_bytes)
        if not hns.pc_is_sane(pc):
            res.update(status="CRASH", detail="pc=%08X (%s) after the message" % (pc, self.t.elf.where(pc)))
            return res
        if not done:
            res.update(status="HANG", detail="the script did not finish within %d frames" % res["frames"])
            return res
        if res["len"] == 0 and any(k in ("glyph", "ph") for _, k, _ in iter_tokens(lab["raw"])):
            problems.append("the message box never took the text (gStringVar4 still empty)")
        if end < 0:
            problems.append("expanded text has no terminator within gStringVar4 (%d bytes): it overflowed"
                            % self.sv4_size)
        if (cb1, cb2) != (self.cb1_ow, self.cb2_ow):
            problems.append("callbacks after the message: callback1 %s, callback2 %s"
                            % (self.t.elf.where(cb1), self.t.elf.where(cb2)))
        if st[0] != 2 or st[1] != 0:
            problems.append("not controllable after the message (script status %d, field controls lock %d)"
                            % (st[0], st[1]))
        pos, over = page_rows(text_bytes)
        heb = any(k == "glyph" and v in self.t.charmap.hebrew_bytes for _, k, v in iter_tokens(lab["raw"]))
        for page, row in over:
            warnings.append("page %d has a row %d: the field box holds %d rows (%s)"
                            % (page, row, FIELD_ROWS, "translated" if heb else "no Hebrew in the label"))
        if warnings:
            res["warnings"] = warnings
        recs = []
        if clip is not None:
            import cliptour
            count = struct.unpack_from("<I", clip, self.clip_count - self.clip_lo)[0]
            log = clip[self.clip_log - self.clip_lo:self.clip_log - self.clip_lo + 16 * 12]
            delta = count - self.base_clip
            if delta < 0:
                problems.append("gRtlClipCount went down (%d -> %d)" % (self.base_clip, count))
                delta = 0
            res["clips"] = delta
            if delta:
                parsed, lost = cliptour.parse_records(log, count, self.base_clip)
                res["clip_lost"] = lost
                mem = cliptour.MemImage()
                mem.blocks.append((0x08000000, self.t.rom_bytes))
                mem.add(self.sv4, sv4)
                for r in parsed:
                    rec = dict(seq=r["seq"], window=r["windowId"], font=r["fontId"], x=r["x"],
                               currentX=r["currentX"], physX=r["physX"], glyphWidth=r["glyphWidth"],
                               windowWidth=r["windowWidth"], str="%08X" % r["str"],
                               edge="left" if r["physX"] < 0 else "right")
                    if self.sv4 < r["str"] <= self.sv4 + self.sv4_size:
                        d = cliptour.decode_clip(mem.read, r["str"], self.t.charmap, self.sv4)
                        rec["glyph"] = d["glyph"]
                        page, row = where_in_text(pos, r["str"] - 1 - self.sv4)
                        rec["page"], rec["row"] = page, row
                        rec["line_text"] = self.line_with_mark(text_bytes, r["str"] - self.sv4)
                        rec["line"] = line_of(text_bytes, r["str"] - 1 - self.sv4)
                        rec.update(self.source_line(lab["raw"], rec["line"]))
                    else:
                        rec["glyph"] = None
                        rec["where"] = self.t.elf.where(r["str"])
                    recs.append(rec)
                res["clip_records"] = recs
        if problems:
            res.update(status="ABNORMAL", detail="; ".join(problems))
        elif recs or res.get("clips"):
            kinds = [r.get("kind") for r in recs]
            res["clip_kind"] = next((k for k in CLIP_KINDS if k in kinds), None)
            res.update(status="CLIP", detail=self.clip_summary(res))
        else:
            res.update(status="OK", detail="")
        if res["status"] != "OK" or warnings:
            res["text"] = self.decode(text_bytes, stop=True)
        return res

    def source_line(self, raw, n):
        """What the label's own line N holds in the ROM: Hebrew letters or only Latin, and which
        placeholders, so a clip can be told apart as translated / placeholder / untranslated."""
        lines = text_lines(raw)
        if n >= len(lines):
            return dict(kind=None)
        toks = lines[n]
        heb = any(k == "glyph" and v in self.t.charmap.hebrew_bytes for _, k, v in toks)
        phs = [self.decode(bytes([PLACEHOLDER, v]), False) for _, k, v in toks if k == "ph"]
        kind = ("translated" if heb else "untranslated") + ("+placeholder" if phs else "")
        return dict(kind=kind, placeholders=phs) if phs else dict(kind=kind)

    def line_with_mark(self, data, after):
        """The row of DATA holding the glyph that ends at offset AFTER, decoded, glyph in ⟦⟧."""
        g = after - 1
        if g >= 1 and data[g - 1] == EXTRA_SYMBOL:
            g -= 1
        starts = [0] + [off + 1 for off, kind, _ in iter_tokens(data) if kind in ("n", "l", "p") and off < g]
        s = starts[-1]
        e = s
        for off, kind, _ in iter_tokens(data):
            if off >= g and kind in ("n", "l", "p", "eos"):
                e = off
                break
        else:
            e = len(data)
        return self.decode(data[s:g], False) + "⟦" + self.decode(data[g:after], False) + "⟧" + \
            self.decode(data[after:e], False)

    @staticmethod
    def clip_summary(res):
        rows = {}
        for r in res.get("clip_records", []):
            rows.setdefault(r.get("line"), []).append(r)
        parts = []
        for _, rs in sorted(rows.items(), key=lambda kv: -1 if kv[0] is None else kv[0]):
            r = rs[0]
            worst = min(rs, key=lambda x: x["physX"]) if r["edge"] == "left" else max(rs, key=lambda x: x["physX"])
            parts.append("page %s row %s (%s%s): %d glyph(s) past the %s edge, up to %d px (window %d px, win %d)"
                         % (r.get("page"), r.get("row"), r.get("kind"),
                            " " + " ".join(r["placeholders"]) if r.get("placeholders") else "",
                            len(rs), r["edge"],
                            -worst["physX"] if r["edge"] == "left" else worst["physX"] + worst["glyphWidth"] - worst["windowWidth"],
                            r["windowWidth"], r["window"]))
        s = "%d glyph(s) outside the window" % res.get("clips", 0)
        if res.get("clip_lost"):
            s += " (%d not recorded: the 16-entry ring overflowed)" % res["clip_lost"]
        return s + ("; " + "; ".join(parts) if parts else "")

    def run_shots(self, lab, prefix):
        """One label with a screenshot per page, driven from Python (slower). Returns
        [{png, clips}] per page; the caller runs run_fast for the verdict."""
        e = self.emu
        os.makedirs(self.shotdir, exist_ok=True)
        self._send(self._arm(lab["addr"]))
        e.expect(r"^STATE sl \S+ ok")
        e.sync()
        pages, last = [], (e.r32(self.clip_count) if self.t.clip else 0)
        budget = self.budget(lab["raw"])
        waited = 0

        def done():
            return e.read(self.sentinel, 1)[0] == SENTINEL_VALUE

        def look():
            # what changes when the box takes a key: its pixels and the printer's position
            # (with INSTANT text the next page is already waiting again a frame later)
            prs = e.text_printers()
            return hns.message_box(e), tuple(e.r32(p) for p, _, _, _ in prs)

        while not done():
            if waited > budget:
                raise HnsError("no sentinel after %d frames" % waited)
            if not e.wants_key():
                e.frames(2)
                waited += 2
                continue
            e.frames(2)
            before = look()
            if before[0] is not None:
                name = "%s_%02d" % (prefix, len(pages) + 1)
                # emu.shot writes to the runner's outdir (_work); move it next to the others
                src = e.shot(name)
                dst = os.path.join(self.shotdir, name + ".png")
                os.replace(src, dst)
                now = e.r32(self.clip_count) if self.t.clip else 0
                pages.append(dict(png=os.path.relpath(dst, self.outdir), clips=now - last))
                last = now
            e.tap("A", 0)
            for _ in range(60):
                if done() or look() != before:
                    break
                e.frames(1)
            waited += 8
        del e.log[:-40]
        return pages

    def diagnose(self, prefix):
        """What the game is doing after a HANG/ABNORMAL (best effort)."""
        e = self.emu
        out = {}
        try:
            out["callback2"] = e.cb2_name()
            out["tasks"] = [t[2] for t in e.tasks()]
            out["text"] = e.text_state()
            mode = e.r8(self.ctx + 1)
            out["script"] = "mode %d native %s at %s" % (mode, self.t.elf.where(e.r32(self.ctx + 4)),
                                                         self.t.elf.where(e.r32(self.ctx + 8)))
            os.makedirs(self.shotdir, exist_ok=True)
            src = e.shot(prefix)
            dst = os.path.join(self.shotdir, prefix + ".png")
            os.replace(src, dst)
            out["png"] = os.path.relpath(dst, self.outdir)
        except Exception as ex:          # the runner may be gone
            out["error"] = str(ex).splitlines()[0][:200]
        return out


def encode_plain(charmap, text):
    """Plain text (no {codes}) -> bytes with the build's charmap."""
    out = bytearray()
    for ch in text:
        if ch not in charmap.chars:
            raise HnsError("character %r is not in %s" % (ch, charmap.path))
        out += charmap.chars[ch]
    return bytes(out)


def shot_name(label):
    return re.sub(r"[^A-Za-z0-9_]", "_", label)[:100]


# ---------------------------------------------------------------------------- driver

def run(a):
    t0 = time.time()
    target = Target(a.rom, a.elf, a.src, a.charmap)
    outdir = os.path.abspath(a.outdir)
    os.makedirs(outdir, exist_ok=True)
    labels = select_labels(a)
    if getattr(a, "hebrew_only", False):
        def rom_hebrew(u):
            addr = target.label_addr(u["label"])
            raw = target.rom_string(addr) if isinstance(addr, int) else None
            return bool(raw) and any(k == "glyph" and v in target.charmap.hebrew_bytes for _, k, v in iter_tokens(raw))
        labels = [u for u in labels if rom_hebrew(u)]
    results_path = os.path.join(outdir, "results.jsonl")
    meta_path = os.path.join(outdir, "meta.json")
    done = {}
    if a.resume and os.path.exists(results_path):
        old = json.load(open(meta_path)) if os.path.exists(meta_path) else {}
        if old.get("rom_sha1") and old["rom_sha1"] != target.sha1 and not a.force:
            raise SystemExit("--resume: %s holds results for another ROM (sha1 %s); --force to mix"
                             % (outdir, old["rom_sha1"][:12]))
        for raw in open(results_path, encoding="utf-8"):
            try:
                r = json.loads(raw)
            except ValueError:
                continue                  # a line cut by an interrupted run
            done[r["label"]] = r
    elif os.path.exists(results_path):
        os.remove(results_path)
    todo = [u for u in labels if u["label"] not in done]
    print("sweep: %s (%s, %s), %d label(s) selected, %d to run%s"
          % (target.rom, "clip build" if target.clip else "no clip log", target.sha1[:12], len(labels),
             len(todo), (", %d already in results.jsonl" % (len(labels) - len(todo))) if done else ""))
    sys.stdout.flush()
    sw = Sweeper(target, outdir, a.save, a.strvars, a.text_speed, a.echo, a.leave_center, a.max_frames)
    sw.player_name = a.player
    sw.strvar_plain = a.strvar_text.split("|") if a.strvar_text else None
    for f in a.fault or []:
        kind, _, lab = f.partition(":")
        if kind not in ("crash", "hang") or not lab:
            raise SystemExit("--fault KIND:LABEL with KIND crash or hang")
        sw.faults[lab] = kind
    meta = dict(rom=target.rom, elf=target.elf_path, src=target.src, rom_sha1=target.sha1,
                clip_build=target.clip, save=os.path.abspath(a.save) if a.save else None,
                selection=" ".join(sys.argv[2:]), selected=len(labels),
                started=datetime.datetime.now().isoformat(timespec="seconds"))
    out = open(results_path, "a", encoding="utf-8")
    counts = {}
    n_run, since_boot = 0, 0
    t_run = time.time()
    try:
        try:
            sw.boot()
        except HnsError as ex:
            sw.close()
            raise SystemExit("sweep: could not reach the base state: %s" % ex)
        meta.update(start_map=sw.start_map, text_speed=a.text_speed, save_text_speed=sw.save_text_speed,
                    strvars=sw.strvar_text, player=sw.player, base_frame=sw.base_frame,
                    boot_secs=round(time.time() - t_run, 1))
        json.dump(meta, open(meta_path, "w"), indent=1, ensure_ascii=False)
        print("base state: %s, player %s, STR_VAR_1..3 = %s, text speed %s (save had %d), %.1fs"
              % (sw.start_map, sw.player, " / ".join(sw.strvar_text), a.text_speed, sw.save_text_speed,
                 time.time() - t_run))
        t_run = time.time()
        for lab in todo:
            ts = time.time()
            res = dict(label=lab["label"], files=lab.get("files", []))
            skip = sw.precheck(lab)
            if skip:
                res.update(skip)
            else:
                res["addr"] = "%08X" % lab["addr"]
                if sw.emu is None or since_boot >= a.restart_every:
                    sw.restart()
                    since_boot = 0
                since_boot += 1
                try:
                    res.update(sw.run_fast(lab))
                except HnsError as ex:
                    msg = str(ex).splitlines()[0]
                    pc = None
                    m = re.search(r"pc=([0-9A-F]{8})", msg)
                    if m:
                        pc = int(m.group(1), 16)
                    if msg.startswith("CRASH") or "runner exited" in msg or "not running" in msg:
                        res.update(status="CRASH", detail=msg + (" (%s)" % target.elf.where(pc)
                                                                 if pc and pc >> 24 in (2, 3, 8, 9) else ""))
                    elif "did not answer" in msg:
                        res.update(status="HANG", detail="the runner stopped answering: " + msg)
                    else:
                        res.update(status="ABNORMAL", detail="harness error: " + msg)
                if res["status"] in ("HANG", "ABNORMAL"):
                    res["diagnosis"] = sw.diagnose(shot_name(lab["label"]) + "_" + res["status"].lower())
                want_shots = a.shots == "all" or (a.shots == "clip" and res["status"] in ("CLIP", "ABNORMAL"))
                if res["status"] in ("CRASH", "HANG", "ABNORMAL"):
                    sw.close()                       # restart before the next label
                elif want_shots:
                    try:
                        res["shots"] = sw.run_shots(lab, shot_name(lab["label"]))
                    except HnsError as ex:
                        res["shots_error"] = str(ex).splitlines()[0][:200]
                        sw.close()
            res["secs"] = round(time.time() - ts, 3)
            out.write(json.dumps(res, ensure_ascii=False) + "\n")
            out.flush()
            n_run += 1
            counts[res["status"]] = counts.get(res["status"], 0) + 1
            if res["status"] not in ("OK", "SKIP") or a.verbose:
                print("%-8s %-58s %s" % (res["status"], lab["label"], (res.get("detail") or "")[:160]))
            if n_run % a.progress == 0:
                el = time.time() - t_run
                print("[%d/%d] %.1f labels/s, %s" % (n_run, len(todo), n_run / el if el else 0,
                                                     ", ".join("%s %d" % kv for kv in sorted(counts.items()))))
            sys.stdout.flush()
    except KeyboardInterrupt:
        print("interrupted; rerun with --resume to continue")
    finally:
        out.close()
        sw.close()
    el = time.time() - t_run
    meta.update(finished=datetime.datetime.now().isoformat(timespec="seconds"),
                run_secs=round(el, 1), labels_run=n_run, emulator_starts=sw.boots,
                labels_per_sec=round(n_run / el, 2) if el else None, total_secs=round(time.time() - t0, 1))
    old_meta = json.load(open(meta_path)) if os.path.exists(meta_path) else {}
    old_meta.update(meta)
    json.dump(old_meta, open(meta_path, "w"), indent=1, ensure_ascii=False)
    summary = build_report(outdir, [u["label"] for u in labels])
    print("%d label(s) this run in %.1fs (%.1f/s, %d emulator start(s)); totals: %s"
          % (n_run, el, n_run / el if el else 0, sw.boots,
             ", ".join("%s %d" % (k, summary.get(k, 0)) for k in STATUS_ORDER if summary.get(k))))
    print("report: %s" % os.path.join(outdir, "report.txt"))
    bad = sum(summary.get(k, 0) for k in ("CRASH", "HANG", "ABNORMAL", "CLIP"))
    return 1 if bad else 0


def build_report(outdir, order=None):
    meta_path = os.path.join(outdir, "meta.json")
    meta = json.load(open(meta_path)) if os.path.exists(meta_path) else {}
    res = {}
    for raw in open(os.path.join(outdir, "results.jsonl"), encoding="utf-8"):
        try:
            r = json.loads(raw)
        except ValueError:
            continue
        res[r["label"]] = r
    if order:
        known = set(order)
        rows = [res[l] for l in order if l in res] + [r for l, r in res.items() if l not in known]
    else:
        rows = list(res.values())
    summary = {}
    for r in rows:
        summary[r["status"]] = summary.get(r["status"], 0) + 1
    warn = [r for r in rows if r.get("warnings")]
    summary["warnings"] = len(warn)
    for r in rows:
        if r["status"] == "CLIP":
            k = "CLIP_%s" % (r.get("clip_kind") or "unknown")
            summary[k] = summary.get(k, 0) + 1
    ran = [r for r in rows if r["status"] != "SKIP"]
    secs = sum(r.get("secs", 0) for r in ran)
    with open(os.path.join(outdir, "sweep.json"), "w", encoding="utf-8") as fh:
        json.dump(dict(meta=meta, summary=summary, results=rows), fh, ensure_ascii=False, indent=1)
    L = []
    L.append("Text sweep: %s" % meta.get("rom"))
    L.append("  ELF %s, sha1 %s, %s" % (meta.get("elf"), (meta.get("rom_sha1") or "")[:12],
                                         "clip build" if meta.get("clip_build") else
                                         "NOT a clip build: CLIP cannot be detected"))
    L.append("  save %s; start %s; player %s; STR_VAR_1..3 = %s; text speed %s"
             % (meta.get("save"), meta.get("start_map"), meta.get("player"),
                " / ".join(meta.get("strvars") or []), meta.get("text_speed")))
    L.append("  selection: %s (%d label(s))" % (meta.get("selection"), meta.get("selected", len(rows))))
    L.append("  %d label(s) in results: %s; %d with warnings" % (
        len(rows), ", ".join("%s %d" % (k, summary[k]) for k in STATUS_ORDER if summary.get(k)), len(warn)))
    if summary.get("CLIP"):
        L.append("  CLIP by line kind: %s" % ", ".join("%s %d" % (k[5:], v) for k, v in sorted(summary.items())
                                                      if k.startswith("CLIP_")))
    if ran:
        L.append("  %.1f s of label time for %d run label(s): %.3f s per label" % (secs, len(ran), secs / len(ran)))
    sections = [("CRASH", None, ""), ("HANG", None, ""), ("ABNORMAL", None, ""),
                ("CLIP", "translated", "a Hebrew line with no placeholder: the text is too wide"),
                ("CLIP", "translated+placeholder", "a Hebrew line with placeholders: check with real values "
                 "(--strvars/--player)"),
                ("CLIP", "untranslated+placeholder", "no Hebrew on the line (not translated yet), placeholders"),
                ("CLIP", "untranslated", "no Hebrew on the line (not translated yet): English drawn by the RTL "
                 "renderer"),
                ("CLIP", None, "")]
    for st, kind, why in sections:
        sel = [r for r in rows if r["status"] == st and (st != "CLIP" or r.get("clip_kind") == kind)]
        if not sel:
            continue
        L.append("")
        L.append("== %s%s (%d) ==%s" % (st, " " + kind if kind else "", len(sel), "  " + why if why else ""))
        for r in sel:
            L.append("%s  [%s]" % (r["label"], ", ".join(r.get("files") or [])))
            L.append("    %s" % r.get("detail", ""))
            if st == "CLIP":
                seen = set()
                for c in r.get("clip_records", []):
                    if c.get("line") in seen:
                        continue
                    seen.add(c.get("line"))
                    L.append("    p%s r%s glyph %s: %s" % (c.get("page"), c.get("row"), c.get("glyph"),
                                                          c.get("line_text") or c.get("where")))
            elif r.get("text"):
                L.append("    text: %s" % r["text"][:300])
            if r.get("diagnosis"):
                L.append("    diagnosis: %s" % json.dumps(r["diagnosis"], ensure_ascii=False))
            for s in r.get("shots") or []:
                L.append("    shot %s (clips %d)" % (s["png"], s["clips"]))
    if warn:
        L.append("")
        L.append("== warnings (%d) ==" % len(warn))
        for r in warn:
            L.append("%s  [%s] %s" % (r["label"], ", ".join(r.get("files") or []), "; ".join(r["warnings"])))
            if r.get("text"):
                L.append("    text: %s" % r["text"][:300])
    skips = {}
    for r in rows:
        if r["status"] == "SKIP":
            skips.setdefault(r["detail"], []).append(r["label"])
    if skips:
        L.append("")
        L.append("== SKIP (%d) ==" % sum(len(v) for v in skips.values()))
        for why, labs in sorted(skips.items(), key=lambda kv: -len(kv[1])):
            L.append("%d: %s" % (len(labs), why))
            L.append("    " + " ".join(labs[:60]) + (" ..." if len(labs) > 60 else ""))
    with open(os.path.join(outdir, "report.txt"), "w", encoding="utf-8") as fh:
        fh.write("\n".join(L) + "\n")
    return summary


# ---------------------------------------------------------------------------- selftest

def selftest(a):
    """Patch the first row break of one translated label into a space in a copy of the ROM, so
    its first two rows become one row that cannot fit, and sweep that label on both ROMs."""
    target = Target(a.rom, a.elf, a.src, a.charmap)
    if not target.clip:
        raise SystemExit("selftest needs a clip build (make hns RTL_CLIP_REPORT=1)")
    outdir = os.path.abspath(a.outdir)
    os.makedirs(outdir, exist_ok=True)
    units = {u["label"]: u for u in load_units(a.units)}
    if not a.label and not units:
        no_units(a)
    # the loop below keeps only labels whose string in this ROM has Hebrew letters
    cands = list(a.label) if a.label else [u["label"] for u in units.values()]
    pick = None
    for lab in cands:
        addr = target.label_addr(lab)
        if not isinstance(addr, int):
            continue
        raw = target.rom_string(addr)
        if not raw:
            continue
        toks = list(iter_tokens(raw))
        nl = [off for off, kind, _ in toks if kind == "n"]
        if not nl or not any(k == "glyph" and v in target.charmap.hebrew_bytes for _, k, v in toks):
            continue
        # glyphs on the two rows the patch joins: from the page start to the page end
        start = max([o for o, k, _ in toks if k in ("l", "p") and o < nl[0]] or [-1])
        end = min([o for o, k, _ in toks if k in ("l", "p", "eos") and o > nl[0]] or [len(raw)])
        glyphs = sum(1 for off, kind, _ in toks if kind == "glyph" and start < off < end)
        if glyphs >= 48 or a.label:
            pick = (lab, addr, nl[0], raw)
            break
    if not pick:
        raise SystemExit("selftest: no label with Hebrew letters and a long enough two-row page")
    lab, addr, nloff, raw = pick
    patched = os.path.join(outdir, "selftest_patched.gba")
    data = bytearray(target.rom_bytes)
    data[addr - 0x08000000 + nloff] = 0x00            # '\n' -> ' '
    open(patched, "wb").write(bytes(data))
    print("selftest label %s at %08X: row break at +%d -> space" % (lab, addr, nloff))
    print("  original: %s" % target.charmap.decode(raw))
    print("  patched : %s" % target.charmap.decode(bytes(data[addr - 0x08000000:addr - 0x08000000 + len(raw)])))
    verdict = {}
    for name, rom in (("original", target.rom), ("patched", patched)):
        sub = argparse.Namespace(**vars(a))
        sub.rom, sub.elf = rom, target.elf_path
        sub.outdir = os.path.join(outdir, name)
        sub.label, sub.labels_file, sub.match, sub.file, sub.batch = [lab], None, None, None, None
        sub.translated, sub.sample, sub.offset, sub.limit, sub.resume = False, 0, 0, 0, False
        sub.shots = "clip"
        run(sub)
        r = json.loads(open(os.path.join(sub.outdir, "results.jsonl"), encoding="utf-8").readline())
        verdict[name] = r
        print("  %-8s -> %s %s" % (name, r["status"], r.get("detail", "")))
    os.remove(patched)                                 # 32 MB, and rebuilt in a second by rerunning
    ok = verdict["original"]["status"] == "OK" and verdict["patched"]["status"] == "CLIP"
    print("selftest %s" % ("PASS" if ok else "FAIL"))
    json.dump(dict(label=lab, addr="%08X" % addr, patched_offset=nloff, verdict=verdict,
                   result="PASS" if ok else "FAIL"),
              open(os.path.join(outdir, "selftest.json"), "w"), ensure_ascii=False, indent=1)
    return 0 if ok else 1


# ---------------------------------------------------------------------------- CLI

def add_common(p):
    p.add_argument("rom")
    p.add_argument("outdir")
    p.add_argument("--elf")
    p.add_argument("--src", help="source tree for macros/constants/labels (default: the ELF's dir, or HNS_SRC)")
    p.add_argument("--charmap", help="charmap.txt (default: SRC/charmap.txt)")
    p.add_argument("--save", default=DEFAULT_SAVE)
    p.add_argument("--units", default=UNITS_DIR)
    p.add_argument("--strvars", default=DEFAULT_STRVARS,
                   help="event-script lines (';'-separated) run once to fill STR_VAR_1..3; 'none' keeps the save's")
    p.add_argument("--strvar-text", metavar="A|B|C",
                   help="plain text written into STR_VAR_1|2|3 after --strvars (e.g. long names for a stress run)")
    p.add_argument("--text-speed", choices=("instant", "save"), default="instant")
    p.add_argument("--player", help="player name for {PLAYER} (plain text, up to 7 bytes; default: the save's)")
    p.add_argument("--fault", action="append", metavar="KIND:LABEL",
                   help="test the harness: make LABEL 'crash' (callback2 -> 0C000001) or 'hang' (no sentinel)")
    p.add_argument("--leave-center", choices=("auto", "yes", "no"), default="auto")
    p.add_argument("--shots", choices=("none", "clip", "all"), default="clip",
                   help="screenshot every page: never, for CLIP/ABNORMAL labels (default), or always")
    p.add_argument("--restart-every", type=int, default=500)
    p.add_argument("--max-frames", type=int, default=None, help="per-label frame budget (default from the text)")
    p.add_argument("--progress", type=int, default=250)
    p.add_argument("--verbose", action="store_true", help="print every label, not only the bad ones")
    p.add_argument("--echo", action="store_true", help="echo the runner transcript (very noisy)")
    p.add_argument("--force", action="store_true")


def add_selection(p):
    p.add_argument("--label", action="append")
    p.add_argument("--labels-file")
    p.add_argument("--match")
    p.add_argument("--file")
    p.add_argument("--batch")
    p.add_argument("--translated", action="store_true", help="units with a Hebrew text (applied to the build or not)")
    p.add_argument("--hebrew-only", action="store_true", help="labels whose string in THIS ROM has Hebrew letters")
    p.add_argument("--sample", type=int, default=0)
    p.add_argument("--seed", type=int, default=1)
    p.add_argument("--offset", type=int, default=0)
    p.add_argument("--limit", type=int, default=0)
    p.add_argument("--resume", action="store_true")


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest="cmd")
    p = sub.add_parser("run", help="sweep labels")
    add_common(p)
    add_selection(p)
    p = sub.add_parser("report", help="rebuild sweep.json and report.txt from results.jsonl")
    p.add_argument("outdir")
    p = sub.add_parser("selftest", help="prove the clip detector on a patched copy of a clip ROM")
    add_common(p)
    add_selection(p)
    p = sub.add_parser("list", help="print the selected labels")
    p.add_argument("--units", default=UNITS_DIR)
    add_selection(p)
    a = ap.parse_args(argv)
    if a.cmd in ("run", "selftest") and not a.save:
        ap.error("no save to boot: pass --save or set HNS_SAVES (ladder4_league.sav is used from there)")
    if a.cmd == "run":
        return run(a)
    if a.cmd == "report":
        s = build_report(os.path.abspath(a.outdir))
        print(json.dumps(s))
        return 0
    if a.cmd == "selftest":
        return selftest(a)
    if a.cmd == "list":
        for u in select_labels(a):
            print("%s\t%s" % (u["label"], ",".join(u["files"])))
        return 0
    ap.print_help()
    return 2


if __name__ == "__main__":
    sys.exit(main())
