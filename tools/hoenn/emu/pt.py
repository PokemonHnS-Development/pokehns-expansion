#!/usr/bin/env python3
"""Playtest driver for the libmgba harness (Hoenn & Seek, part 20).

Wraps ./harness so a playtest can be scripted from Python:
  - every dialogue box is read back as text from gStringVar4 /
    gDisplayedStringBattle, so a session can be logged without screenshots;
  - battles can be auto-won (the foe's Atk/SpA are set to 1 and its HP to 1 every
    few frames, then A is mashed);
  - flags and vars (HnS and Hoenn ranges) can be set in any savestate;
  - the current map is read from gMapHeader.mapScripts (reverse symbol lookup).

Run from the harness directory (where ./harness lives). ROM and ELF must match.
    import pt; e = pt.Emu("p19.gba", "p19.elf")
State files are plain mGBA savestates; every helper takes a state in and writes
a state out, so a playtest is a chain of states that can be resumed anywhere.
"""
import json, os, re, subprocess, sys

ROOT = os.path.normpath(os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "..", ".."))
EMU = os.path.dirname(os.path.abspath(__file__))

# ---------------------------------------------------------------- charmap
def _charmap():
    dec = {}
    for line in open(os.path.join(ROOT, "charmap.txt"), encoding="utf-8"):
        m = re.match(r"^'(.)'\s*=\s*([0-9A-Fa-f]{2})\s*(@.*)?$", line.strip())
        if m and int(m.group(2), 16) not in dec:
            dec[int(m.group(2), 16)] = m.group(1)
    return dec
DEC = _charmap(); DEC[0x39] = " "

def decode(bs):
    out, i = [], 0
    while i < len(bs):
        b = bs[i]
        if b == 0xFF: break
        if b == 0xFE: out.append(" ")
        elif b in (0xFA, 0xFB): out.append(" | ")
        elif b == 0xFD: out.append("{VAR}"); i += 1
        elif b == 0xFC:  # ext ctrl code + arg(s)
            code = bs[i + 1] if i + 1 < len(bs) else 0
            i += 2 if code in (0x09, 0x0A, 0x0F, 0x15, 0x16, 0x17, 0x18) else 3
            continue
        else: out.append(DEC.get(b, "?"))
        i += 1
    return re.sub(r"\s+", " ", "".join(out)).strip()

# ---------------------------------------------------------------- emulator
class Emu:
    FLAGS_SB1, VARS_SB1, HOENN_FLAGS_SB3, HOENN_VARS_SB3 = 0x198C, 0x1ABC, 0x32, 0x132
    # 2.0 event flags (0x2000-0x23FF) and vars (0x7080-0x70FF), after the 1.0
    # arrays in SaveBlock3. src/hoenn_flags.c asserts these offsets at build time.
    HOENN_EVENT_FLAGS_SB3, HOENN_EVENT_VARS_SB3 = 0x232, 0x2B2

    def __init__(self, rom, elf, cwd=None):
        self.rom, self.elf, self.cwd = rom, elf, cwd or os.getcwd()
        out = subprocess.run(["arm-none-eabi-nm", elf], capture_output=True, text=True, check=True).stdout
        self.syms, self.addr2sym = {}, {}
        for l in out.splitlines():
            p = l.split()
            if len(p) == 3:
                a = int(p[0], 16); self.syms[p[2]] = a; self.addr2sym.setdefault(a, p[2])
        self.log = []

    def s(self, name): return self.syms[name]

    def run(self, lines, timeout=600):
        r = subprocess.run(["./harness", self.rom], input="\n".join(lines) + "\n", capture_output=True,
                           text=True, cwd=self.cwd, timeout=timeout)
        return [l for l in r.stdout.splitlines() if ": " in l and re.match(r"^[0-9a-f]{8}: ", l)]

    # ------------------------------------------------ reading
    def read_words(self, state, addr, n):
        out = self.run([f"loadstate {state}"] + [f"r32 {addr + 4 * k:x}" for k in range(n)])
        return [int(l.split(": ")[1], 16) for l in out]

    @staticmethod
    def _bytes(words):
        bs = bytearray()
        for w in words: bs += w.to_bytes(4, "little")
        return bytes(bs)

    def text_cmds(self, nwords=128):
        a, b = self.s("gStringVar4"), self.s("gDisplayedStringBattle")
        return [f"r32 {a + 4 * k:x}" for k in range(nwords)] + [f"r32 {b + 4 * k:x}" for k in range(nwords)]

    def parse_text(self, vals, nwords=128):
        return decode(self._bytes(vals[:nwords])), decode(self._bytes(vals[nwords:2 * nwords]))

    def ptrs(self, state):
        w = self.read_words(state, self.s("gSaveBlock1Ptr"), 1)[0]  # by symbol: IWRAM moves when code changes
        w3 = self.read_words(state, self.s("gSaveBlock3Ptr"), 1)[0]
        return w, w3

    def where(self, state):
        """(map name, x, y, in_battle)"""
        hdr, obj, main = self.s("gMapHeader"), self.s("gObjectEvents"), self.s("gMain")
        out = self.run([f"loadstate {state}", f"r32 {hdr + 8:x}", f"r32 {obj + 16:x}", f"r8 {main + 0x439:x}"])
        ms = int(out[0].split(": ")[1], 16); xy = int(out[1].split(": ")[1], 16)
        name = self.addr2sym.get(ms, hex(ms)).replace("_MapScripts", "")
        x, y = (xy & 0xFFFF) - 7, ((xy >> 16) & 0xFFFF) - 7
        return name, x, y, bool(int(out[2].split(": ")[1], 16) & 2)

    # ------------------------------------------------ flags / vars
    def _flag_addr(self, flag, sb1, sb3):
        if 0x1800 <= flag < 0x2000:
            o = flag - 0x1800; return sb3 + self.HOENN_FLAGS_SB3 + o // 8, 1 << (o % 8)
        if 0x2000 <= flag < 0x2400:
            o = flag - 0x2000; return sb3 + self.HOENN_EVENT_FLAGS_SB3 + o // 8, 1 << (o % 8)
        return sb1 + self.FLAGS_SB1 + flag // 8, 1 << (flag % 8)

    def _var_addr(self, var, sb1, sb3):
        if 0x7080 <= var < 0x7100: return sb3 + self.HOENN_EVENT_VARS_SB3 + (var - 0x7080) * 2
        if var >= 0x7000: return sb3 + self.HOENN_VARS_SB3 + (var - 0x7000) * 2
        return sb1 + self.VARS_SB1 + (var - 0x4000) * 2

    def poke(self, state_in, state_out, flags_on=(), flags_off=(), vars_=None):
        sb1, sb3 = self.ptrs(state_in)
        addrs = sorted({self._flag_addr(f, sb1, sb3)[0] for f in list(flags_on) + list(flags_off)})
        cur = dict(zip(addrs, [int(l.split(": ")[1], 16) for l in
                               self.run([f"loadstate {state_in}"] + [f"r8 {a:x}" for a in addrs])])) if addrs else {}
        for f in flags_on: a, m = self._flag_addr(f, sb1, sb3); cur[a] |= m
        for f in flags_off: a, m = self._flag_addr(f, sb1, sb3); cur[a] &= ~m
        cmds = [f"loadstate {state_in}"] + [f"w8 {a:x} {v}" for a, v in cur.items()]
        for var, val in (vars_ or {}).items(): cmds.append(f"w16 {self._var_addr(var, sb1, sb3):x} {val}")
        self.run(cmds + ["wait 2", f"savestate {state_out}"])
        return state_out

    def callback2(self, state):
        a = self.read_words(state, self.s("gMain") + 4, 1)[0] & ~1
        return self.addr2sym.get(a, hex(a))

    def unstick_party(self, state):
        """If a forced 'Choose a POKéMON' party screen is open, move down until a mon can go out."""
        for k in range(12):
            cb = self.callback2(state)
            if cb in ("BattleMainCB2", "CB2_Overworld"): return
            if cb == "CB2_UpdatePartyMenu":  # close any submenu, next slot, SEND OUT
                self.steps(state, state, [("B", 2), ("wait", 20), ("DOWN", 2), ("wait", 20), ("A", 4), ("wait", 30), ("A", 4), ("wait", 90)])
            else:  # summary screen or similar: back out
                self.steps(state, state, [("B", 4), ("wait", 60)])

    def heal(self, state_in, state_out):
        """Full HP and no status for the whole party (HP/status aren't encrypted)."""
        p = self.s("gPlayerParty")
        vals = [int(l.split(": ")[1], 16) for l in self.run([f"loadstate {state_in}"] + [f"r16 {p + 100 * i + 88:x}" for i in range(6)])]
        cmds = [f"loadstate {state_in}"]
        for i, mx in enumerate(vals):
            if mx: cmds += [f"w16 {p + 100 * i + 86:x} {mx}", f"w32 {p + 100 * i + 80:x} 0"]
        self.run(cmds + ["wait 2", f"savestate {state_out}"])
        return state_out

    def set_battle_style(self, state_in, state_out):
        """Battle style SET (no 'switch Pokémon?' prompt): bit 1 of SaveBlock2 byte +21."""
        sb2 = self._sb2(state_in)
        v = int(self.run([f"loadstate {state_in}", f"r8 {sb2 + 21:x}"])[0].split(": ")[1], 16)
        self.run([f"loadstate {state_in}", f"w8 {sb2 + 21:x} {v | 2}", "wait 2", f"savestate {state_out}"])
        return state_out

    def getflag(self, state, flag):
        sb1, sb3 = self.ptrs(state); a, m = self._flag_addr(flag, sb1, sb3)
        return bool(int(self.run([f"loadstate {state}", f"r8 {a:x}"])[0].split(": ")[1], 16) & m)

    def getvar(self, state, var):
        sb1, sb3 = self.ptrs(state)
        return int(self.run([f"loadstate {state}", f"r16 {self._var_addr(var, sb1, sb3):x}"])[0].split(": ")[1], 16)

    # ------------------------------------------------ time and weather (2.0 part 2)
    # The same changes the debug menu's "H&S time & weather…" makes, done through
    # memory so a test can jump straight to a weekday, hour, week or weather stage.
    # They take effect on the next time check: warp (go()) or walk a few steps.
    # Offsets are asserted in src/hoenn_time.c; vars are in constants/hoenn_events.h.
    VAR_WEEKDAY_OFFSET, VAR_WEEK_SEEN = 0x7080, 0x7081
    SB1_WEATHER_STAGE, SB2_TIME_OFFSET = 0x33, 0x98
    WEEKDAYS = ["SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"]

    def _sb2(self, state):
        return self.read_words(state, self.s("gSaveBlock2Ptr"), 1)[0]

    def clock(self, state):
        """The game's view of the time: {days, hour, minute, weekday, offset, week, week_seen, stage}.
        gLocalTime is refreshed on every time check, so read it after a few frames in the overworld."""
        lt = self.s("gLocalTime")
        sb1, sb3 = self.ptrs(state)
        out = self.run([f"loadstate {state}", f"r16 {lt:x}", f"r8 {lt + 2:x}", f"r8 {lt + 3:x}",
                        f"r16 {self._var_addr(self.VAR_WEEKDAY_OFFSET, sb1, sb3):x}",
                        f"r16 {self._var_addr(self.VAR_WEEK_SEEN, sb1, sb3):x}",
                        f"r8 {sb1 + self.SB1_WEATHER_STAGE:x}"])
        v = [int(l.split(": ")[1], 16) for l in out]
        days = v[0] - 0x10000 if v[0] & 0x8000 else v[0]
        offset = v[3] % 7
        wd = (6 + max(days, 0) + offset) % 7  # day 0 is a Saturday (src/hoenn_time.c)
        week = (max(days, 0) + (6 + offset) % 7) // 7  # weeks start on Sunday
        return {"days": days, "hour": v[1], "minute": v[2], "weekday": self.WEEKDAYS[wd], "offset": offset,
                "week": week, "week_seen": v[4], "stage": v[5]}

    def start_clock(self, state_in, state_out):
        """Debug saves (mkbase.sh) skip New Bark's wall clock, so FLAG_SYS_CLOCK_SET
        is off and no daily/weekly reset ever runs. state_in must have the debug
        menu open: this answers YES to the "H&S time & weather…" clock prompt."""
        keys = ["A", "DOWN", "DOWN", "DOWN", "DOWN", "DOWN", "A"]
        self.run([f"loadstate {state_in}"] + sum([[f"press {k} 4", "wait 20"] for k in keys], []) +
                 ["wait 90", "press A 4", "wait 90", "press B 4", "wait 40", f"savestate {state_out}"])
        return state_out

    def _shift_time(self, state_in, state_out, seconds):
        """Move local time forward by `seconds` (negative: back) by changing
        SaveBlock2's localTimeOffset (local = RTC - offset), kept normalized."""
        sb2 = self._sb2(state_in) + self.SB2_TIME_OFFSET
        out = self.run([f"loadstate {state_in}", f"r16 {sb2:x}", f"r8 {sb2 + 2:x}", f"r8 {sb2 + 3:x}", f"r8 {sb2 + 4:x}"])
        d, h, m, sec = [int(l.split(": ")[1], 16) for l in out]
        sx = lambda x, bits: x - (1 << bits) if x & (1 << (bits - 1)) else x
        total = sx(d, 16) * 86400 + sx(h, 8) * 3600 + sx(m, 8) * 60 + sx(sec, 8) - seconds
        d, rest = divmod(total, 86400); h, rest = divmod(rest, 3600); m, sec = divmod(rest, 60)
        self.run([f"loadstate {state_in}", f"w16 {sb2:x} {d & 0xFFFF}", f"w8 {sb2 + 2:x} {h}",
                  f"w8 {sb2 + 3:x} {m}", f"w8 {sb2 + 4:x} {sec}", "wait 2", f"savestate {state_out}"])
        return state_out

    def set_hour(self, state_in, state_out, hour):
        """Same day, `hour`:00."""
        c = self.clock(state_in)
        return self._shift_time(state_in, state_out, (hour - c["hour"]) * 3600 - c["minute"] * 60)

    def next_week(self, state_in, state_out):
        """Midnight at the start of next week: the next time check runs the daily
        update for the skipped days and resets the weekly flags."""
        c = self.clock(state_in)
        days = 7 - self.WEEKDAYS.index(c["weekday"])
        return self._shift_time(state_in, state_out, days * 86400 - c["hour"] * 3600 - c["minute"] * 60)

    def set_weekday(self, state_in, state_out, day):
        """Make today `day` ('MON' or 0-6, Sunday = 0) through the weekday offset,
        like HoennSetWeekday: no new week (VAR_HOENN_WEEK_SEEN is set to this week)."""
        day = self.WEEKDAYS.index(day) if isinstance(day, str) else day
        c = self.clock(state_in)
        base = (6 + max(c["days"], 0)) % 7
        offset = (day - base) % 7
        week = (max(c["days"], 0) + (6 + offset) % 7) // 7
        return self.poke(state_in, state_out, vars_={self.VAR_WEEKDAY_OFFSET: offset, self.VAR_WEEK_SEEN: week + 1})

    def set_weather_stage(self, state_in, state_out, stage):
        """Emerald's 4-day weather cycle stage (0-3; 2 is the special-weather day).
        Warp afterwards to see the weather change."""
        sb1, _ = self.ptrs(state_in)
        self.run([f"loadstate {state_in}", f"w8 {sb1 + self.SB1_WEATHER_STAGE:x} {stage % 4}", "wait 2", f"savestate {state_out}"])
        return state_out

    # ------------------------------------------------ actions
    def menu(self, state_in, state_out):
        """Close whatever is open and open the debug menu (needed before warp())."""
        self.run([f"loadstate {state_in}"] + ["press B 4", "wait 40"] * 14 + ["wait 30", "press R+START 6", "wait 60", f"savestate {state_out}"])
        return state_out

    def warp(self, state_in, group, num, x, y, state_out):
        """state_in must have the debug menu open (see menu())."""
        tmp = state_out.replace(".ss", "")
        script = subprocess.run(["python3", os.path.join(EMU, "warp.py"), state_in, str(group), str(num), tmp,
                                 "--xy", str(x), str(y), "--elf", self.elf], capture_output=True, text=True, check=True).stdout
        self.run(script.splitlines())
        os.replace(os.path.join(self.cwd, tmp + ".ss"), os.path.join(self.cwd, state_out)) if tmp + ".ss" != state_out else None
        return state_out

    def go(self, state_in, group, num, x, y, state_out):
        return self.warp(self.menu(state_in, "_menu.ss"), group, num, x, y, state_out)

    def steps(self, state_in, state_out, keys, shot_prefix=None, gap=20):
        """keys: list like ["UP", "UP", ("A", 4), ("wait", 60), ("shot", "x.png")]."""
        cmds = [f"loadstate {state_in}"]
        for k in keys:
            if isinstance(k, tuple) and k[0] == "wait": cmds.append(f"wait {k[1]}")
            elif isinstance(k, tuple) and k[0] == "shot": cmds.append(f"shot {k[1]}")
            elif isinstance(k, tuple): cmds += [f"press {k[0]} {k[1]}", f"wait {gap}"]
            else: cmds += [f"press {k} 16" if k in ("UP", "DOWN", "LEFT", "RIGHT") else f"press {k} 4", f"wait {gap}"]
        self.run(cmds + [f"savestate {state_out}"])
        return state_out

    def walk(self, state_in, state_out, path):
        """path: 'UUURRD' etc. One tile per letter (16-frame holds)."""
        m = {"U": "UP", "D": "DOWN", "L": "LEFT", "R": "RIGHT"}
        return self.steps(state_in, state_out, [m[c] for c in path], gap=2)

    def walk_read(self, state_in, state_out, path, shots=None, after=8):
        """Walk a path ('LRLR…'), reading dialogue every 2 steps, then press B `after`
        times (finishes a phone call that started). Returns texts."""
        m = {"U": "UP", "D": "DOWN", "L": "LEFT", "R": "RIGHT"}
        cmds = [f"loadstate {state_in}", f"w8 {self.s('gStringVar4'):x} 255"]
        nreads = 0
        for i, c in enumerate(path):
            cmds += [f"press {m[c]} 16", "wait 2"]
            if i % 2: cmds += self.text_cmds(); nreads += 1
        for k in range(after):
            cmds += ["press B 4", "wait 110"] + self.text_cmds(); nreads += 1
            if shots: cmds.append(f"shot {shots}_{k + 1}.png")
        cmds.append(f"savestate {state_out}")
        vals = [int(l.split(": ")[1], 16) for l in self.run(cmds)]
        texts = []
        for i in range(nreads):
            t, bt = self.parse_text(vals[i * 256:(i + 1) * 256])
            if t and (not texts or texts[-1] != t): texts.append(t)
        return texts

    def talk(self, state_in, state_out, face=None, presses=12, wait=110, shots=None, keys=None):
        """Face a direction (optional), then press A `presses` times (or the given key list),
        reading the dialogue box after each. Returns the distinct texts in order.
        shots: filename prefix -> a screenshot after every press (prefix_N.png)."""
        cmds = [f"loadstate {state_in}", f"w8 {self.s('gStringVar4'):x} 255", f"w8 {self.s('gDisplayedStringBattle'):x} 255"]
        if face: cmds += [f"press {face} 2", "wait 20"]
        keys = keys or ["A"] * presses
        for i, k in enumerate(keys):
            cmds += [f"press {k} 4", f"wait {wait}"] + self.text_cmds()
            if shots: cmds.append(f"shot {shots}_{i + 1}.png")
        cmds.append(f"savestate {state_out}")
        out = self.run(cmds)
        vals = [int(l.split(": ")[1], 16) for l in out]
        texts, n = [], 256
        for i in range(len(keys)):
            t, bt = self.parse_text(vals[i * n:(i + 1) * n])
            for x in (t, bt):
                if x and (not texts or texts[-1] != x) and x not in texts[-3:]: texts.append(x)
        self.log.append((state_in, texts))
        return texts

    def fight(self, state_in, state_out, rounds=60, shots=None, every=10, hp=None):
        """Auto-win the current battle: foe battlers get HP 1 and Atk/SpA 1, then A is mashed.
        Returns (texts, still_in_battle)."""
        bm, main = self.s("gBattleMons"), self.s("gMain")
        cmds = [f"loadstate {state_in}"]
        for i in range(rounds):
            for b in (1, 3):  # foes: Atk/SpA 1 (and HP if hp is given)
                base = bm + 136 * b
                cmds += [f"w16 {base + 2:x} 1", f"w16 {base + 8:x} 1"] + ([f"w16 {base + 42:x} {hp}"] if hp is not None else [])
            for b in (0, 2):  # us: Atk/SpA/Spe 999
                base = bm + 136 * b
                cmds += [f"w16 {base + 2:x} 999", f"w16 {base + 6:x} 999", f"w16 {base + 8:x} 999"]
                cmds += [f"w8 {base + 37 + m:x} 20" for m in range(4)]  # PP never runs out
            if i % 2 == 0:  # pick a move explicitly: FIGHT, then rotate through moves 1-3
                extra = [[], ["RIGHT"], ["DOWN"], ["DOWN", "RIGHT"]][(i // 2) % 4]
                cmds += ["press UP 2", "wait 3", "press LEFT 2", "wait 3", "press A 4", "wait 20",
                         "press UP 2", "wait 3", "press LEFT 2", "wait 3"] + sum([[f"press {k} 2", "wait 3"] for k in extra], [])
            cmds += ["press A 4", "wait 40"] + self.text_cmds(32)
            if shots and i % every == 0: cmds.append(f"shot {shots}_{i // every + 1}.png")
        cmds += [f"r8 {main + 0x439:x}", f"savestate {state_out}"]
        out = self.run(cmds)
        vals = [int(l.split(": ")[1], 16) for l in out]
        texts = []
        for i in range(rounds):
            t, bt = self.parse_text(vals[i * 64:(i + 1) * 64], 32)
            for x in (bt,):
                if x and (not texts or texts[-1] != x) and x not in texts[-4:]: texts.append(x)
        return texts, bool(vals[-1] & 2)

DIRS = {"UP": (0, -1), "DOWN": (0, 1), "LEFT": (-1, 0), "RIGHT": (1, 0)}
FACE_FROM = {(0, 1): "UP", (0, -1): "DOWN", (1, 0): "LEFT", (-1, 0): "RIGHT"}  # offset of player from NPC -> key to face it

_grids = {}
def grid(map_name):
    """Rows of mapinfo.py's ASCII map: '.' walkable, '#' blocked, '~' water, 'w' warp, 'o' object."""
    if map_name not in _grids:
        out = subprocess.run(["python3", os.path.join(EMU, "mapinfo.py"), map_name], capture_output=True, text=True).stdout
        rows = [l[4:] for l in out.splitlines()[2:] if re.match(r"^\s*\d+ ", l)]
        _grids[map_name] = rows
    return _grids[map_name]

def spots_next_to(map_name, x, y):
    """Tiles next to (x,y) the player can stand on, with the key that faces (x,y)."""
    g, res = grid(map_name), []
    for (dx, dy), key in FACE_FROM.items():
        px, py = x + dx, y + dy
        if 0 <= py < len(g) and 0 <= px < len(g[py]) and g[py][px] in ".~":
            res.append((px, py, key))
    return res

def resolve(*names):
    sys.path.insert(0, os.path.join(ROOT, "tools", "hoenn"))
    from resolve_consts import resolve as r
    return r(list(names))

def map_id(name):
    """MAP_* constant name -> (group, num) from include/constants/map_groups.h."""
    t = open(os.path.join(ROOT, "include/constants/map_groups.h")).read()
    m = re.search(r"\b" + name + r"\s*=\s*\((\d+) \| \((\d+) << 8\)\)", t)
    return int(m.group(2)), int(m.group(1))

def talk_to(e, state_in, map_name, match, state_out, presses=12, shots=None, group_num=None):
    """Warp next to the first object whose script contains `match` and talk to it.
    Tries each free side (wandering NPCs move). Returns texts."""
    obj = next(o for o in objects(map_name) if match in str(o[4]))
    g, n = group_num or map_of(map_name)
    for px, py, key in spots_next_to(map_name, obj[2], obj[3]):
        s = e.go(state_in, g, n, px, py, "_talk_w.ss")
        t = e.talk(s, state_out, face=key, presses=presses, shots=shots)
        if t: return t
    return []

def map_of(map_name):
    """Map folder name -> (group, num)."""
    return map_id(json.load(open(os.path.join(ROOT, f"data/maps/{map_name}/map.json")))["id"])

def objects(map_name):
    d = json.load(open(os.path.join(ROOT, f"data/maps/{map_name}/map.json")))
    return [(o.get("local_id"), o["graphics_id"], o["x"], o["y"], o["script"], o.get("flag"), o.get("movement_type"))
            for o in d.get("object_events") or []]

def explore(e, state, map_name, prefix, presses=10, skip=(), only=None, signs=True):
    """Talk to every visible NPC (and read every sign) on a map. Returns
    [(kind, script, (x, y), texts, shot)] — shot is the screenshot after the first A."""
    objs = objects(map_name)
    flags = sorted({o[5] for o in objs if o[5] and o[5] != "0"})
    vals = dict(zip(flags, [None] * len(flags)))
    if flags:
        r = resolve(*flags)
        vals = {k: (v if isinstance(v, int) else None) for k, v in r.items()}
    g, n = map_of(map_name)
    out = []
    targets = [("npc", o[4], o[2], o[3], o[5]) for o in objs if o[4] not in ("0x0", "0") ]
    if signs:
        md = json.load(open(os.path.join(ROOT, f"data/maps/{map_name}/map.json")))
        targets += [("sign", b["script"], b["x"], b["y"], None) for b in md.get("bg_events") or [] if b.get("type") == "sign"]
    for i, (kind, script, x, y, flag) in enumerate(targets):
        if script in skip or (only and not any(k in script for k in only)): continue
        if flag and vals.get(flag) is not None and e.getflag(state, vals[flag]): continue
        texts, shot = [], f"{prefix}_{i:02d}"
        for px, py, key in (spots_next_to(map_name, x, y) if kind == "npc" else
                            [(x, y + 1, "UP"), (x - 1, y, "RIGHT"), (x + 1, y, "LEFT"), (x, y - 1, "DOWN")]):
            try:
                s = e.go(state, g, n, px, py, "_exp_w.ss")
            except Exception:
                continue
            nm, cx, cy, _ = e.where(s)
            if (cx, cy) != (px, py): continue
            cmds_keys = ["A"] + ["B"] * (presses - 1)
            texts = e.talk(s, "_exp_t.ss", face=key, keys=cmds_keys, wait=100, shots=shot)
            if texts: break
        out.append((kind, script, (x, y), texts, f"{shot}_1.png"))
    return out

def resolve_map(names):
    return resolve(*names)

def trainers(map_name):
    d = json.load(open(os.path.join(ROOT, f"data/maps/{map_name}/map.json")))
    return [(o["x"], o["y"], o["script"], o.get("flag")) for o in d.get("object_events") or []
            if o.get("trainer_type", "TRAINER_TYPE_NONE") != "TRAINER_TYPE_NONE"]

def battle_npc(e, state_in, map_name, x, y, state_out, pre=6, post=10, shots=None):
    """Talk to the NPC at (x,y) until a battle starts, auto-win it, then clear the
    after-battle text with B (B also answers NO). Returns (texts, won_or_None)."""
    g, n = map_of(map_name)
    texts = []
    for px, py, key in spots_next_to(map_name, x, y):
        s = e.go(e.heal(state_in, "_bn_h.ss"), g, n, px, py, "_bn_w.ss")
        if e.where(s)[1:3] != (px, py): continue
        t = e.talk(s, "_bn_t.ss", face=key, keys=["A"] * pre, wait=90, shots=shots and shots + "_pre")
        texts += t
        if e.where("_bn_t.ss")[3]:
            ft, still = e.fight("_bn_t.ss", "_bn_f.ss", rounds=12, shots=shots and shots + "_b", every=4)
            texts += ft
            for k in range(40):  # short chunks, so A-mashing stops soon after the battle ends
                if not still: break
                e.unstick_party("_bn_f.ss")
                ft, still = e.fight("_bn_f.ss", "_bn_f.ss", rounds=12, shots=shots and f"{shots}_b{k}", every=6)
                texts += ft
            t2 = e.talk("_bn_f.ss", state_out, keys=["B"] * post, wait=100, shots=shots and shots + "_post")
            texts += t2
            return texts, not still
        if t:
            os.replace(os.path.join(e.cwd, "_bn_t.ss"), os.path.join(e.cwd, state_out))
            return texts, None
    return texts, None

def bfs_path(map_name, start, goal):
    """Shortest walk ('UDLR' string) over '.' tiles from start to goal, or None."""
    from collections import deque
    g = grid(map_name)
    W = {"U": (0, -1), "D": (0, 1), "L": (-1, 0), "R": (1, 0)}
    prev = {start: None}; q = deque([start])
    while q:
        c = q.popleft()
        if c == goal: break
        for k, (dx, dy) in W.items():
            n = (c[0] + dx, c[1] + dy)
            if n in prev or not (0 <= n[1] < len(g) and 0 <= n[0] < len(g[n[1]])): continue
            if g[n[1]][n[0]] != "." and n != goal: continue
            prev[n] = (c, k); q.append(n)
    if goal not in prev: return None
    path, c = [], goal
    while prev[c]: c, k = prev[c]; path.append(k)
    return "".join(reversed(path))

def explore_fast(e, state, map_name, prefix, presses=9, signs=False, entry=None):
    """Like explore(), but warps once and walks (BFS) to each NPC: ~5x faster."""
    objs = objects(map_name)
    flags = sorted({o[5] for o in objs if o[5] and o[5] != "0"})
    vals = {}
    if flags:
        vals = {k: v for k, v in resolve(*flags).items() if isinstance(v, int)}
    g, n = map_of(map_name)
    rows = grid(map_name)
    # entry tile: the requested one, else the walkable tile closest to the first warp
    md = json.load(open(os.path.join(ROOT, f"data/maps/{map_name}/map.json")))
    if not entry:
        wx, wy = (md["warp_events"][0]["x"], md["warp_events"][0]["y"]) if md.get("warp_events") else (len(rows[0]) // 2, len(rows) // 2)
        cands = [(abs(x - wx) + abs(y - wy), x, y) for y in range(len(rows)) for x in range(len(rows[y])) if rows[y][x] == "."]
        entry = min(cands)[1:]
    base = e.go(state, g, n, entry[0], entry[1], "_xf_entry.ss")
    nm, ex, ey, _ = e.where(base)
    out = []
    targets = [("npc", o[4], o[2], o[3], o[5]) for o in objs if o[4] not in ("0x0", "0")]
    if signs:
        targets += [("sign", b["script"], b["x"], b["y"], None) for b in md.get("bg_events") or [] if b.get("type") == "sign"]
    hidden = set()
    for kind, script, x, y, flag in targets:
        if flag in vals and e.getflag(base, vals[flag]): hidden.add((x, y))
    m = {"U": "UP", "D": "DOWN", "L": "LEFT", "R": "RIGHT"}
    for i, (kind, script, x, y, flag) in enumerate(targets):
        if (x, y) in hidden and kind == "npc": continue
        texts, shot = [], f"{prefix}_{i:02d}"
        for px, py, key in spots_next_to(map_name, x, y) if kind == "npc" else [(x, y + 1, "UP")]:
            p = bfs_path(map_name, (ex, ey), (px, py))
            if p is None: continue
            cmds = [f"loadstate {base}", f"w8 {e.s('gStringVar4'):x} 255"]
            for c in p: cmds += [f"press {m[c]} 16", "wait 2"]
            cmds += [f"press {key} 2", "wait 20"]
            keys = ["A"] + ["B"] * (presses - 1)
            for j, k in enumerate(keys):
                cmds += [f"press {k} 4", "wait 100"] + e.text_cmds()
                if j == 0: cmds.append(f"shot {shot}_1.png")
            vals_ = [int(l.split(": ")[1], 16) for l in e.run(cmds)]
            texts = []
            for j in range(len(keys)):
                t, bt = e.parse_text(vals_[j * 256:(j + 1) * 256])
                if t and t not in texts: texts.append(t)
            if texts: break
        out.append((kind, script, (x, y), texts, f"{shot}_1.png"))
    return out
