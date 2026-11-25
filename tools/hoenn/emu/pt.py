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
DEC = _charmap()

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
        w = self.read_words(state, 0x030041C0, 1)[0]  # gSaveBlock1Ptr
        w3 = self.read_words(state, 0x03000178, 1)[0]  # gSaveBlock3Ptr
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
        return sb1 + self.FLAGS_SB1 + flag // 8, 1 << (flag % 8)

    def _var_addr(self, var, sb1, sb3):
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

    def getflag(self, state, flag):
        sb1, sb3 = self.ptrs(state); a, m = self._flag_addr(flag, sb1, sb3)
        return bool(int(self.run([f"loadstate {state}", f"r8 {a:x}"])[0].split(": ")[1], 16) & m)

    def getvar(self, state, var):
        sb1, sb3 = self.ptrs(state)
        return int(self.run([f"loadstate {state}", f"r16 {self._var_addr(var, sb1, sb3):x}"])[0].split(": ")[1], 16)

    # ------------------------------------------------ actions
    def menu(self, state_in, state_out):
        """Close whatever is open and open the debug menu (needed before warp())."""
        self.run([f"loadstate {state_in}"] + ["press B 4", "wait 30"] * 6 + ["wait 30", "press R+START 6", "wait 60", f"savestate {state_out}"])
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

    def fight(self, state_in, state_out, rounds=60, shots=None, every=10):
        """Auto-win the current battle: foe battlers get HP 1 and Atk/SpA 1, then A is mashed.
        Returns (texts, still_in_battle)."""
        bm, main = self.s("gBattleMons"), self.s("gMain")
        cmds = [f"loadstate {state_in}"]
        for i in range(rounds):
            for b in (1, 3):
                base = bm + 136 * b
                cmds += [f"w16 {base + 42:x} 1", f"w16 {base + 2:x} 1", f"w16 {base + 8:x} 1"]  # hp, attack, spAttack
            cmds += ["press A 4", "wait 40"] + self.text_cmds(32)
            if shots and i % every == 0: cmds.append(f"shot {shots}_{i // every + 1}.png")
        cmds += [f"r8 {main + 0x439:x}", f"savestate {state_out}"]
        out = self.run(cmds)
        vals = [int(l.split(": ")[1], 16) for l in out]
        texts = []
        for i in range(rounds):
            t, bt = self.parse_text(vals[i * 64:(i + 1) * 64], 32)
            for x in (bt, t):
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
