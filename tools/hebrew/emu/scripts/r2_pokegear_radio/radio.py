#!/usr/bin/env python3
"""hns.py plus the ops the PokeGear radio tours (radio_*.txt) use.
Run:  radio.py tour ROM OUT --tours <this folder> [--clip] [--only RE] [--rtc UNIX]

The radio (src/pokenav_radio.c) prints one line every RADIO_SCROLL_DELAY (90) frames into a
two-line window; the previous line scrolls up. Station content is built when the dial lands on
a frequency (GenerateStationContent) and, for Oak's POKEMON Talk, again at the end of every
segment (GenerateOPTSegment: intro, 5 POKEMON segments, the POKEMON Channel interlude, a report).

struct Pokenav_Radio (src/pokenav_radio.c:92-109, natural alignment): callback +0, tuningPos +4,
tuneDelay +8, currentStation +9, scrollTimer +10 (u16), currentLine +12, numLines +13,
needsScroll +14, optSegmentCounter +15, optPhase +16, currentMusic +18 (u16), lines[15] +20,
lineBuffers[8][40] +80.

Added here:
    gearradio                 open the PokeGear from the field (START > POKEGEAR) and enter RADIO:
                              the main-menu cursor is moved by reading Pokenav_Menu.currMenuItem
                              (+4; src/pokenav_menu_handler.c:8-16) until it is POKENAV_MENUITEM_RADIO
    radiocycle PREFIX [MAX] [SEEDS]
                              one shot per radio line (PREFIX_NN) from the line on screen now until
                              the station's lines wrap to line 0 (or MAX shots). Oak's Talk never
                              wraps (a new segment is generated instead), so it stops at MAX.
                              SEEDS (comma-separated 32-hex-digit RNG states): the RNG is pinned to
                              the next seed before every generated segment, so two ROMs show the same
                              random content. Every shot's lines are logged to OUT/<tour>/lines.json.
    radiostate                print the radio struct and the decoded lines
    radiolines I PTRSYM...    point lines[I], lines[I+1], ... at ROM strings by symbol (e.g. a whole
                              sOPT_Report_* block) - used to put every report on screen
    radiojump LINE [PHASE] [SEG]
                              set currentLine (and optPhase / optSegmentCounter) and let the next
                              scroll happen in 2 frames
    radiocat BUF LINE PIECE...
                              compose PIECEs (ROM string symbols, or SPACE / PERIOD / COMMA / EXCL)
                              into lineBuffers[BUF] with StringCopy/StringAppend semantics and point
                              lines[LINE] at it (the way GenerateOPTSegment builds its lines)
    radionum N                set numLines
    radiotunepin POS NUM SEEDS
                              tune away and back to POS with the RNG pinned to each seed in turn,
                              until the generated station has NUM lines (the Lucky Channel's
                              optional 'drag' lines, Places & People's random length); the seed
                              that worked is printed, and both ROMs then show the same content
    gearclose                 B out of the radio and the PokeGear, close the start menu (the
                              station keeps playing on the field: VAR_TEMP_RADIO_MUSIC)
    clockinfo                 print the RTC, SaveBlock2.localTimeOffset (+0x98) and gLocalTime
    clockshift DAYS HOURS     move the game clock: localTimeOffset.days -= DAYS, .hours -= HOURS
                              (gLocalTime = RTC - offset, src/rtc.c:290-320), then print clockinfo
    dexonly NATDEX...         clear every caught flag (SaveBlock1.dexCaught, +0x3A7F, the literal in
                              GetSetPokedexFlag) and set only these national dex numbers, so the
                              Pokedex Show (which picks among caught species) has to pick one of them
"""
import json
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(HERE, "..", ".."))                      # tools/hebrew/emu
sys.path.insert(0, os.path.join(HERE, "..", "..", ".."))                # tools/hebrew
sys.path.insert(0, os.path.join(HERE, "..", "r2_safari_pokeblock_bug_contest"))
import hns  # noqa: E402
import r2sf  # noqa: E402,F401  (loc, warpraw, ss, sl, ...)
from hns import script_op, HnsError, TourTimeout, _arg  # noqa: E402

R_TUNING, R_STATION, R_TIMER, R_LINE, R_NUM, R_SEG, R_PHASE, R_LINES, R_BUFS = 4, 9, 10, 12, 13, 15, 16, 20, 80
MAX_LINES, NBUF, BUFSZ = 15, 8, 40
MENUITEM_RADIO = 4                      # include/pokenav.h:160-168 (IS_HNS)
STATIONS = ["NONE", "POKEMON_TALK", "POKEDEX_SHOW", "POKEMON_MUSIC", "LUCKY_CHANNEL",
            "BUENAS_PASSWORD", "UNOWN", "PLACES_AND_PEOPLE", "LETS_ALL_SING", "POKE_FLUTE",
            "EVOLUTION", "ROCKET", "HOENN_SOUND"]
PHASES = ["INTRO", "POKEMON", "INTERLUDE", "REPORT"]

_CHARMAPS = {}


def charmap(emu):
    import textwidth as tw
    path = os.path.join(hns.src_dir(emu.elf), "charmap.txt")
    if path not in _CHARMAPS:
        _CHARMAPS[path] = tw.Charmap(path)
    return _CHARMAPS[path]


def radio_ptr(emu):
    return hns.pokenav_substruct(emu, "HandleRadioInput")


def read_str(emu, addr, n=80):
    return charmap(emu).decode(emu.read(addr, n))


def radio_state(emu, decode=True):
    p = radio_ptr(emu)
    raw = emu.read(p, R_BUFS)
    st = dict(tuning=int.from_bytes(raw[4:8], "little", signed=True), station=STATIONS[raw[R_STATION]],
              timer=raw[R_TIMER] | raw[R_TIMER + 1] << 8, line=raw[R_LINE], num=raw[R_NUM],
              seg=raw[R_SEG], phase=PHASES[raw[R_PHASE]] if raw[R_PHASE] < 4 else raw[R_PHASE])
    ptrs = [int.from_bytes(raw[R_LINES + 4 * i:R_LINES + 4 * i + 4], "little") for i in range(MAX_LINES)]
    st["ptrs"] = ptrs[:st["num"]]
    if decode:
        st["text"] = [read_str(emu, a) if a else "" for a in st["ptrs"]]
        st["src"] = [emu.elf.where(a) if a < 0x02000000 or a >= 0x08000000 else
                     ("lineBuffers[%d]" % ((a - p - R_BUFS) // BUFSZ) if p + R_BUFS <= a < p + R_BUFS + NBUF * BUFSZ
                      else "%08X" % a) for a in st["ptrs"]]
    return p, st


def _shot(emu, name):
    emu.frames(2)
    emu.shot(name)
    return os.path.join(emu.outdir, name + ".png")


def _log_lines(emu, name, st):
    path = os.path.join(emu.outdir, "lines.json")
    data = {}
    if os.path.exists(path):
        try:
            data = json.load(open(path, encoding="utf-8"))
        except ValueError:
            data = {}
    cur = st["line"]
    data[name] = dict(station=st["station"], tuning=st["tuning"], phase=st["phase"], seg=st["seg"],
                      line=cur, num=st["num"],
                      shown=st["text"][cur] if cur < len(st["text"]) else None,
                      above=(st["text"][cur - 1] if 0 < cur <= len(st["text"]) else None),
                      src=st["src"][cur] if cur < len(st["src"]) else None)
    json.dump(data, open(path, "w", encoding="utf-8"), ensure_ascii=False, indent=1)


@script_op("gearradio")
def _op_gearradio(emu, f, path):
    if emu.controllable():           # gMenuCallback keeps HandleStartMenuInput after the menu closes
        emu.open_start_menu()
        emu.frames(12)
        emu.wait_quiet(300)
    emu.start_menu_cursor("POKEGEAR")
    emu.wait_cb2("CB2_Pokenav", 600)
    emu.wait_until(lambda: hns.pokenav_idle(emu), 900, "the Pokegear main menu", step=2)
    res = emu.r32(emu.sym("gPokenavResources"))
    want = emu.sym("HandleMainMenuInput")
    menu = None
    raw = emu.read(res, 0x80)
    for off in range(0, 0x80, 4):
        p = int.from_bytes(raw[off:off + 4], "little")
        if 0x02000000 <= p < 0x02040000 and emu.r32(p + 12) == want:
            menu = p
    if menu is None:
        raise HnsError("gearradio: no Pokenav_Menu with callback HandleMainMenuInput")
    for _ in range(8):
        if emu.r16(menu + 4) == MENUITEM_RADIO:
            break
        emu.tap("DOWN", 0)
        emu.wait_until(lambda: hns.pokenav_idle(emu), 600, "the Pokegear cursor", step=2)
    else:
        raise HnsError("gearradio: the main menu has no RADIO entry (menuType %d)" % emu.r16(menu))
    emu.tap("A", 0)
    emu.frames(4)
    emu.wait_until(lambda: hns.pokenav_idle(emu), 900, "the radio to open", step=2)
    emu.wait_quiet(300)
    radio_ptr(emu)
    print("gearradio ok @%d" % emu.sync())


@script_op("radiostate")
def _op_radiostate(emu, f, path):
    p, st = radio_state(emu)
    print("radiostate @%08X %s" % (p, json.dumps(st, ensure_ascii=False)))


@script_op("clockinfo")
def _op_clockinfo(emu, f, path):
    rtc = emu.read(emu.sym("sRtc"), 8)
    off = emu.read(emu.sb2() + 0x98, 5)
    lt = emu.read(emu.sym("gLocalTime"), 5)
    s16 = lambda b: int.from_bytes(b, "little", signed=True)
    s8 = lambda v: v - 256 if v > 127 else v
    print("clockinfo rtc(bcd) %s | offset days %d h %d m %d s %d | local days %d h %d m %d s %d | gTimeOfDay %d"
          % (" ".join("%02X" % b for b in rtc), s16(off[0:2]), s8(off[2]), s8(off[3]), s8(off[4]),
             s16(lt[0:2]), s8(lt[2]), s8(lt[3]), s8(lt[4]), emu.r8(emu.sym("gTimeOfDay"))))


@script_op("radiocycle")
def _op_radiocycle(emu, f, path):
    prefix = f[1]
    maxshots = _arg(f, 2, 40)
    seeds = [s for s in f[3].split(",") if s] if len(f) > 3 else []
    emu.wait_until(lambda: hns.pokenav_idle(emu), 600, "the radio", step=2)
    p, st = radio_state(emu)
    if st["num"] == 0:
        name = "%s_00" % prefix
        _shot(emu, name)
        _log_lines(emu, name, st)
        print("radiocycle %s: station %s has no lines @%d" % (prefix, st["station"], emu.sync()))
        return
    is_opt = st["station"] == "POKEMON_TALK"
    n = 0
    seed_i = 0

    def key(s):
        return (s["line"], s["phase"], s["seg"], s["num"], tuple(s["ptrs"][:1]))

    if is_opt and seeds:
        hns.pin_rng(emu, seeds[seed_i % len(seeds)])
    name = "%s_%02d" % (prefix, n)
    _shot(emu, name)
    _log_lines(emu, name, st)
    last = key(st)
    first_line = st["line"]
    while n + 1 < maxshots:
        # the next line comes RADIO_SCROLL_DELAY frames after the last one (the interlude waits 4x)
        timer = emu.r16(p + R_TIMER)
        if timer > 4:
            emu.frames(timer - 3)
        waited = 0
        while True:
            emu.frames(1)
            waited += 1
            raw = emu.read(p, R_LINES + 4)
            s = dict(line=raw[R_LINE], phase=PHASES[raw[R_PHASE]] if raw[R_PHASE] < 4 else raw[R_PHASE],
                     seg=raw[R_SEG], num=raw[R_NUM], ptrs=[int.from_bytes(raw[R_LINES:R_LINES + 4], "little")])
            if key(s) != last:
                break
            if waited > 600:
                raise TourTimeout("radiocycle: no new line in 600 frames")
        emu.wait_until(lambda: hns.pokenav_idle(emu), 600, "the radio to scroll", step=1)
        p, st = radio_state(emu)
        new_segment = st["line"] == 0
        if not is_opt and st["line"] == first_line:
            break                            # wrapped: every line has been shot
        if is_opt and new_segment and seeds:
            seed_i += 1
            hns.pin_rng(emu, seeds[seed_i % len(seeds)])
        n += 1
        name = "%s_%02d" % (prefix, n)
        _shot(emu, name)
        _log_lines(emu, name, st)
        last = key(st)
    if is_opt and seeds:
        hns.unpin_rng(emu)
    print("radiocycle %s: %d shot(s), station %s @%d" % (prefix, n + 1, st["station"], emu.sync()))


@script_op("radiolines")
def _op_radiolines(emu, f, path):
    p = radio_ptr(emu)
    i = int(f[1])
    for k, name in enumerate(f[2:]):
        emu.w32(p + R_LINES + 4 * (i + k), emu.sym(name))
    num = max(emu.r8(p + R_NUM), i + len(f) - 2)
    emu.w8(p + R_NUM, num)
    print("radiolines %d..%d numLines %d" % (i, i + len(f) - 3, num))


@script_op("radiojump")
def _op_radiojump(emu, f, path):
    p = radio_ptr(emu)
    emu.w8(p + R_LINE, int(f[1]))
    if len(f) > 2:
        emu.w8(p + R_PHASE, PHASES.index(f[2]) if f[2] in PHASES else int(f[2]))
    if len(f) > 3:
        emu.w8(p + R_SEG, int(f[3]))
    emu.w16(p + R_TIMER, 1)
    emu.frames(3)                     # the scroll happens on the next frame
    emu.wait_until(lambda: hns.pokenav_idle(emu), 600, "the radio to scroll", step=1)
    print("radiojump line %s -> %d @%d" % (f[1], emu.r8(p + R_LINE), emu.sync()))


@script_op("radiotunepin")
def _op_radiotunepin(emu, f, path):
    pos, want = int(f[1]), int(f[2])
    seeds = [x for x in f[3].split(",") if x]
    p = radio_ptr(emu)
    for seed in seeds:
        hns._op_radiotune(emu, ["radiotune", str(pos - 1 if pos > 0 else pos + 1)], path)
        hns.pin_rng(emu, seed)
        hns._op_radiotune(emu, ["radiotune", str(pos)], path)
        hns.unpin_rng(emu)
        num = emu.r8(p + R_NUM)
        if want < 0 or num == want:
            print("radiotunepin %d: seed %s -> %d lines" % (pos, seed, num))
            return
        print("radiotunepin %d: seed %s gave %d lines (want %d)" % (pos, seed, num, want))
    raise HnsError("radiotunepin %d: no seed gave %d lines" % (pos, want))


@script_op("gearclose")
def _op_gearclose(emu, f, path):
    emu.tap("B", 0)
    emu.frames(4)
    emu.wait_until(lambda: hns.pokenav_idle(emu), 900, "the Pokegear main menu", step=2)
    emu.tap("B", 0)
    if not emu.wait32(emu.CB2, emu.sym("CB2_Overworld"), 900):
        raise HnsError("gearclose: not back in the field (%s)" % emu.cb2_name())
    emu.wait_until(lambda: emu.r32(emu.sym("gMenuCallback")) == emu.sym("HandleStartMenuInput"), 600,
                   "the start menu", step=2)
    emu.tap("B", 4)
    emu.wait_controllable(600)
    print("gearclose ok @%d" % emu.sync())


LITERALS = {"SPACE": " ", "PERIOD": ".", "COMMA": ",", "EXCL": "!"}
SB1_DEX_CAUGHT, DEX_FLAG_BYTES = 0x3A7F, 0xBF


@script_op("radiocat")
def _op_radiocat(emu, f, path):
    p = radio_ptr(emu)
    bi, li = int(f[1]), int(f[2])
    cm = charmap(emu)
    data = b""
    for piece in f[3:]:
        if piece in LITERALS:
            data += bytes(cm.chars[LITERALS[piece]])
        else:
            a = emu.sym(piece)
            raw = emu.read(a, 64)
            data += raw[:raw.index(0xFF)]
    data += b"\xff"
    if len(data) > BUFSZ:
        raise HnsError("radiocat: %d bytes > %d" % (len(data), BUFSZ))
    buf = p + R_BUFS + bi * BUFSZ
    for k in range(0, len(data)):
        emu.w8(buf + k, data[k])
    emu.w32(p + R_LINES + 4 * li, buf)
    print("radiocat buf %d -> lines[%d] = %s" % (bi, li, cm.decode(data)))


@script_op("radionum")
def _op_radionum(emu, f, path):
    emu.w8(radio_ptr(emu) + R_NUM, int(f[1]))


@script_op("clockshift")
def _op_clockshift(emu, f, path):
    a = emu.sb2() + 0x98
    off = emu.read(a, 3)
    days = int.from_bytes(off[0:2], "little", signed=True) - int(f[1])
    hours = (off[2] - 256 if off[2] > 127 else off[2]) - int(f[2])
    emu.w16(a, days & 0xFFFF)
    emu.w8(a + 2, hours & 0xFF)
    emu.frames(2)
    _op_clockinfo(emu, ["clockinfo"], path)


@script_op("dexonly")
def _op_dexonly(emu, f, path):
    base = emu.sb1() + SB1_DEX_CAUGHT
    for k in range(DEX_FLAG_BYTES):
        emu.w8(base + k, 0)
    for nat in f[1:]:
        n = int(nat, 0) - 1
        emu.w8(base + n // 8, emu.r8(base + n // 8) | (1 << (n % 8)))
    print("dexonly %s" % " ".join(f[1:]))


if __name__ == "__main__":
    sys.argv[0] = hns.__file__
    sys.exit(hns.main())
