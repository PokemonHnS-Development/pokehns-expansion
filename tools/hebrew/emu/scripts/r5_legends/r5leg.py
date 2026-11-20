#!/usr/bin/env python3
"""hns.py plus the ops the r5 legendary / roamer / totem tours use (tours/r5_legends/*.txt).
On top of rivalops.py (bwin / blose / drivex / drive / pick / ss / sl and the r2-r3 ops),
rc.py (fieldwatch) and r4misc.py (dexopen / dexgoto / dexinfo / dexarea / dexback).
Run:  r5leg.py tour ROM OUT --tours <emu>/tours/r5_legends [--clip] [--only RE]

Added here:
    bcatch PREFIX [BALL]    at the action menu: BAG, the POKE BALLS pocket, BALL (default
                            ITEM_MASTER_BALL), USE; then walk the throw, the caught-Pokemon dex
                            page (A), the nickname prompt (B = NO) and anything after it, one
                            shot per page (PREFIX_..), until the player is free again
    bsplash PREFIX [MAXTURNS]
                            at each action menu make the player's battler use Splash (move 0,
                            full HP) so the foe gets its turn; walk until the field runs again.
                            For a roamer, which flees on its first turn (AI_FLAG_ROAMING,
                            src/battle_ai_main.c:230-231)
    roamers                 print gSaveBlock1Ptr->roamer[] (species, level, hp, active, table)
                            and sRoamerLocation
    roamhere IDX|SPECIES    move roamer IDX (or the active roamer of SPECIES) to the player's current
                            map (sRoamerLocation, src/roamer.c:31); fails unless it is active
    stepto DIR [N]          walk N tiles, stopping once a trigger takes the player over
    roambattle PREFIX [TRIES]
                            start the encounter the way the field does once a land encounter
                            passed WildEncounterCheck: `callnative TryStartRoamerEncounter` (1 in 4,
                            src/roamer.c:469-480) until gEncounteredRoamerIndex is set, then
                            `callnative BattleSetup_StartRoamerBattle` (src/battle_setup.c:448)
    scene PREFIX [MAX] [EVERY]
                            rc.py fieldwatch until the first of: a battle has started
                            (BattleMainCB2), the player is free, a script menu reads input (shot,
                            then returns). Prints which one.
    approach LOCALID        walk next to that object and face it (objs prints the objects)
    closeall [MAX]          B every 30 frames until the player is free
    dexfind NATNUM          Pokedex list cursor to the entry with that national number
    fixwarp MAP X Y         hns.py's warpto (MAP_* name), kept under its own name because the
                            ladder.py import inside r4misc.py replaces `warpto` with GROUP NUM X Y
"""
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
EMU = os.path.join(HERE, "..", "..")
sys.path.insert(0, EMU)                                                           # tools/hebrew/emu
sys.path.insert(0, os.path.join(HERE, "..", "r2_rival_names"))
sys.path.insert(0, os.path.join(HERE, "..", "r2_battle_frontier_facilities"))
sys.path.insert(0, os.path.join(HERE, "..", "r3_frontier"))
sys.path.insert(0, os.path.join(HERE, "..", "r2_safari_pokeblock_bug_contest"))
sys.path.insert(0, os.path.join(HERE, "..", "r2_pokegear_ribbons_contests"))
sys.path.insert(0, os.path.join(HERE, "..", "r4_misc"))
sys.path.insert(0, os.path.join(EMU, ".."))                                       # tools/hebrew
import hns  # noqa: E402
_HNS_WARPTO = hns.SCRIPT_OPS["warpto"]
import rivalops  # noqa: E402,F401  (bwin / drivex / drive / pick / ss / sl ...)
import rc  # noqa: E402,F401  (fieldwatch)
import r4misc  # noqa: E402,F401  (dex ops; imports ladder.py: event / eventstart / warpto GROUP NUM)
sys.path.insert(0, os.path.join(HERE, "..", "r2_hill_tents"))
import hilltent_ops  # noqa: E402  (walkto / objs / talkto)
from hns import script_op, HnsError, _arg  # noqa: E402

hns.SCRIPT_OPS["warpto"] = _HNS_WARPTO           # MAP_* names, as the other tours use it
script_op("fixwarp")(_HNS_WARPTO)

POCKET_BALLS = 2                                 # gBagPosition.pocket of POKE BALLS (tours/battle_catch.txt)


def _shot(emu, name):
    emu.frames(2)
    emu.shot(name)
    emu.shots = getattr(emu, "shots", []) + [name]


def _walk_to_free(emu, prefix, maxsteps=40):
    """battle_walk until free; answers prompts with B (NO), A on the caught-mon dex page and on
    any other input state, shooting each screen that wants a decision."""
    for step in range(maxsteps):
        n, end = hns.battle_walk(emu, "%s_w%02d" % (prefix, step), (), 60, 8000)
        print("  %s walk %d: %d page(s), %s" % (prefix, step, n, end))
        if end == "free":
            return
        _shot(emu, "%s_w%02d_stop" % (prefix, step))
        if end.startswith("prompt:"):
            emu.tap("B", 4)
        elif end.startswith("task:Task_HandleCaughtMonPageInput"):
            emu.wait_quiet(300)
            emu.tap("A", 4)
        elif end.startswith("task:naming_screen"):
            emu.tap("START", 4)
            emu.wait_quiet(300)
            emu.tap("A", 4)
        else:
            emu.tap("A", 4)
        emu.wait_quiet(300)
    raise HnsError("%s: not free after %d steps" % (prefix, maxsteps))


@script_op("bcatch")
def _op_bcatch(emu, f, path):
    prefix = f[1]
    ball = f[2] if len(f) > 2 else "ITEM_MASTER_BALL"
    hns.wait_battle_input(emu, "HandleInputChooseAction")
    hns.battle_cursor(emu, "gActionSelectionCursor", hns.BATTLE_ACTIONS["BAG"])
    emu.tap("A", 4)
    emu.wait_until(lambda: emu.cb2() == emu.sym("CB2_BagMenuRun"), 900, "the bag", step=2)
    hns.SCRIPT_OPS["bagpocket"](emu, ["bagpocket", str(POCKET_BALLS)], path)
    hns.SCRIPT_OPS["bagseek"](emu, ["bagseek", ball], path)
    emu.wait_quiet(300)
    _shot(emu, prefix + "_bag")
    emu.tap("A", 4)                              # USE / CANCEL
    emu.wait_quiet(300)
    _shot(emu, prefix + "_use")
    emu.tap("A", 4)                              # USE: the throw
    emu.wait_until(lambda: emu.cb2() == emu.sym("BattleMainCB2"), 900, "the battle again", step=2)
    _walk_to_free(emu, prefix)
    print("bcatch %s ok @%d" % (prefix, emu.sync()))


@script_op("bsplash")
def _op_bsplash(emu, f, path):
    prefix = f[1]
    maxturns = _arg(f, 2, 10)
    bm = emu.sym("gBattleMons")
    splash = emu.const("MOVE_SPLASH")
    for turn in range(maxturns):
        n, end = hns.battle_walk(emu, "%s_t%02d" % (prefix, turn), (), 60, 8000,
                                 stop_tasks=("Task_WeatherMain",))
        print("  bsplash turn %d: %d page(s), %s" % (turn, n, end))
        if end == "free" or end.startswith("task:Task_WeatherMain"):
            break
        if end.startswith("input:HandleInputChooseAction"):
            b = 2 if end.endswith("#2") else 0
            emu.w16(bm + 0x88 * b + 0x2A, emu.r16(bm + 0x88 * b + 0x2E))
            emu.w16(bm + 0x88 * b + 0x0C, splash)
            if emu.r8(bm + 0x88 * b + 0x25) == 0:
                emu.w8(bm + 0x88 * b + 0x25, 10)
            _shot(emu, "%s_t%02d_menu" % (prefix, turn))
            hns.wait_battle_input(emu, "HandleInputChooseAction", battler=b)
            hns.battle_cursor(emu, "gActionSelectionCursor", 0, battler=b)
            emu.tap("A", 4)
            hns.wait_battle_input(emu, "HandleInputChooseMove", battler=b)
            hns.battle_cursor(emu, "gMoveSelectionCursor", 0, battler=b)
            emu.tap("A", 4)
        elif end.startswith("prompt:"):
            emu.tap("B", 4)
        else:
            emu.tap("A", 4)
    else:
        raise HnsError("bsplash %s: still in battle after %d turns" % (prefix, maxturns))
    print("bsplash %s ok @%d" % (prefix, emu.sync()))


ROAMER_OFF, ROAMER_SIZE, ROAMER_COUNT = 0x38FC, 0x1C, 4
# gSaveBlock1Ptr->roamer[]: IsRoamerAt reads roamer[i].active at SB1 + 0x390F + i * 0x1C (its literal
# pool, the same in the release and the English ELF), active is at +0x13 in struct Roamer
# (include/global.h:780-798), so roamer[] starts at SB1 + 0x38FC. ROAMER_COUNT is 4 on H&S
# (include/constants/global.h:115).


def _roamer(emu, i):
    b = emu.sb1() + ROAMER_OFF + ROAMER_SIZE * i
    raw = emu.read(b, ROAMER_SIZE)
    return dict(species=raw[8] | raw[9] << 8, hp=raw[10] | raw[11] << 8, level=raw[12],
                active=raw[0x13], table=raw[0x16])


@script_op("roamers")
def _op_roamers(emu, f, path):
    loc = emu.sym("sRoamerLocation")
    raw = emu.read(loc, 2 * ROAMER_COUNT)
    names = {}
    for i in range(ROAMER_COUNT):
        r = _roamer(emu, i)
        names[i] = emu.elf.const_name(r["species"], "SPECIES_") if hasattr(emu.elf, "const_name") else r["species"]
        print("roamer %d: species %s level %d hp %d active %d table %d at (%d,%d)"
              % (i, names[i], r["level"], r["hp"], r["active"], r["table"], raw[2 * i], raw[2 * i + 1]))
    print("roamers: gEncounteredRoamerIndex %d @%d" % (emu.r8(emu.sym("gEncounteredRoamerIndex")), emu.sync()))


@script_op("roamhere")
def _op_roamhere(emu, f, path):
    """roamhere IDX|SPECIES: IDX, or the active roamer whose species is SPECIES (SPECIES_* name)."""
    (g, n, _, _, _), _ = emu.location()
    loc = emu.sym("sRoamerLocation")
    if f[1].isdigit():
        idx = int(f[1])
    else:
        want = emu.const(f[1])
        hits = [i for i in range(ROAMER_COUNT) if _roamer(emu, i)["active"] and _roamer(emu, i)["species"] == want]
        if not hits:
            raise HnsError("roamhere: no active roamer is %s" % f[1])
        idx = hits[0]
    if not _roamer(emu, idx)["active"]:
        raise HnsError("roamhere: roamer %d is not active" % idx)
    for i in range(ROAMER_COUNT):                 # only this roamer on this map
        if i != idx and emu.r8(loc + 2 * i) == g and emu.r8(loc + 2 * i + 1) == n:
            emu.w8(loc + 2 * i + 1, 0xFF)
    emu.w8(loc + 2 * idx, g)
    emu.w8(loc + 2 * idx + 1, n)
    print("roamhere %s: sRoamerLocation[%d] = (%d, %d) @%d" % (f[1], idx, emu.r8(loc + 2 * idx),
                                                               emu.r8(loc + 2 * idx + 1), emu.sync()))


@script_op("stepto")
def _op_stepto(emu, f, path):
    """stepto DIR [N]: hold DIR for one tile (16 frames) N times (default 1), stopping as soon as
    the player is no longer controllable (a coord trigger or a warp took over)."""
    n = _arg(f, 2, 1)
    for i in range(n):
        if not emu.controllable():
            break
        emu.frames(16, f[1])
        emu.frames(6)
    print("stepto %s %d: at %s, controllable %s @%d" % (f[1], n, emu.location()[1], emu.controllable(), emu.sync()))


@script_op("roambattle")
def _op_roambattle(emu, f, path):
    prefix = f[1]
    tries = _arg(f, 2, 40)
    idx = emu.sym("gEncounteredRoamerIndex")
    for t in range(tries):
        emu.w8(idx, 0xFF)
        hns.event_run(emu, "callnative TryStartRoamerEncounter\nend\n", "roamtry")
        got = emu.r8(idx)
        if got != 0xFF:
            print("roambattle %s: roamer %d after %d tries @%d" % (prefix, got, t + 1, emu.sync()))
            break
        emu.frames(7)
    else:
        raise HnsError("roambattle: no roamer encounter in %d tries (is one active on this map?)" % tries)
    hns.event_start(emu, "callnative BattleSetup_StartRoamerBattle\nend\n", "roamstart")
    print("roambattle %s: started @%d" % (prefix, emu.sync()))


def _press_until_taken(emu, tries=6):
    """A on a page that waits for a key; a one-glyph page ('…') printed right after the previous
    press may miss a 0-frame tap, so press again (held 4 frames) until the page takes it."""
    emu.tap("A", 0)
    for t in range(tries):
        for _ in range(45):
            if not emu.wants_key():
                return
            emu.frames(2)
        emu.tap("A", 4)
    raise hns.TourTimeout("the text did not take the key after %d presses" % (tries + 1))


@script_op("closeall")
def _op_closeall(emu, f, path):
    """closeall [MAX]: press B every 30 frames until the player can walk (closes the Pokedex, the
    start menu and so on)."""
    for i in range(_arg(f, 1, 20)):
        if emu.controllable():
            emu.frames(8)
            if emu.controllable():
                print("closeall: free after %d press(es) @%d" % (i, emu.sync()))
                return
        emu.tap("B", 4)
        emu.frames(30)
    raise HnsError("closeall: still not free (callback2 %s)" % emu.cb2_name())


@script_op("scene")
def _op_scene(emu, f, path):
    prefix = f[1]
    maxf, every = _arg(f, 2, 30000), _arg(f, 3, 0)
    ow = emu.sym("CB2_Overworld")
    bcb2 = emu.sym("BattleMainCB2")
    n, k, waited, since, prev = 0, 0, 0, 0, "idle"
    last = [None]

    def shoot(periodic=False):
        nonlocal n, k, since
        since = 0
        if periodic:
            k += 1
            name = "%s_%03d_p%02d" % (prefix, n, k)
        else:
            n += 1
            k = 0
            name = "%s_%03d" % (prefix, n)
        p = rc._shot(emu, name)
        data, same = rc._same_as(p, last[0])
        if same and periodic:
            os.remove(p)
            emu.shots = emu.shots[:-1]
            k -= 1
            return
        last[0] = data

    while waited < maxf:
        cb = emu.cb2()
        if cb == bcb2:
            print("scene %s: %d shot(s), battle @%d" % (prefix, n, emu.sync()))
            return
        if emu.controllable():
            emu.frames(8)
            if emu.controllable():
                print("scene %s: %d shot(s), free @%d" % (prefix, n, emu.sync()))
                return
            continue
        if cb == ow and emu.tasks_named(emu.MENU_TASKS):
            emu.wait_menu_ready()
            emu.frames(2)
            shoot()
            print("scene %s: %d shot(s), menu %s @%d" % (prefix, n, emu.tasks_named(emu.MENU_TASKS)[0], emu.sync()))
            return
        st = emu.text_state()
        if emu.wants_key():
            emu.wait_quiet(600)
            emu.frames(2)
            shoot()
            _press_until_taken(emu)
            prev = emu.text_state()
            waited += 10
            continue
        if prev == "busy" and st != "busy":
            emu.frames(2)
            shoot()
        elif every and since >= every and st != "busy" and not emu.fading():
            shoot(periodic=True)
        prev = st
        emu.frames(2)
        waited += 2
        since += 2
    raise hns.TourTimeout("scene %s: no battle / free / menu after %d frames (callback2 %s)"
                          % (prefix, maxf, emu.cb2_name()))


@script_op("dexfind")
def _op_dexfind(emu, f, path):
    """dexfind NATNUM: in the open Pokedex list, move the cursor to the entry whose national number
    is NATNUM (PV list entries: u16 dexNum at +0, src/pokedex.c struct PokedexListItem)."""
    d = r4misc._dex(emu)
    want = int(f[1])
    count = d.pv16("PV.pokemonListCount")
    pos = [i for i in range(count) if d.list_entry(i)[0] == want]
    if not pos:
        raise HnsError("dexfind: #%d is not in the list (%d entries)" % (want, count))
    d.list_goto(pos[0])
    print("dexfind %d: list position %d, #%d %s @%d" % (want, pos[0], d.dexnum(), d.name(d.dexnum()), emu.sync()))


@script_op("approach")
def _op_approach(emu, f, path):
    """approach LOCALID: walk to a free tile next to the object with that local id (hilltent_ops
    walkto over the live collision grid) and face it; no key press."""
    lid = int(f[1], 0)
    obj = [o for o in hilltent_ops.objects(emu) if o[0] == lid]
    if not obj:
        raise HnsError("approach: no object %d (%s)" % (lid, hilltent_ops.objects(emu)))
    _, ox, oy = obj[0]
    adj = {(ox, oy + 1): "UP", (ox, oy - 1): "DOWN", (ox + 1, oy): "LEFT", (ox - 1, oy): "RIGHT"}
    _, pos = emu.location()
    if pos not in adj:
        for t in sorted(adj, key=lambda t: abs(t[0] - pos[0]) + abs(t[1] - pos[1])):
            try:
                hilltent_ops._op_walkto(emu, ["walkto", str(t[0]), str(t[1])], path)
            except HnsError as e:
                print("approach: %s" % e)
                continue
            _, pos = emu.location()
            if pos in adj:
                break
    _, pos = emu.location()
    if pos not in adj:
        raise HnsError("approach: could not get next to object %d at %s (at %s)" % (lid, (ox, oy), pos))
    emu.frames(2, adj[pos])
    emu.frames(14)
    print("approach %d: at %s facing %s @%d" % (lid, pos, adj[pos], emu.sync()))


if __name__ == "__main__":
    sys.argv[0] = hns.__file__
    sys.exit(hns.main())
