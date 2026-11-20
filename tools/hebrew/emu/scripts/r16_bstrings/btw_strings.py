#!/usr/bin/env python3
"""btw_strings.py ROM OUTDIR [--ids A-B,C,...] [--setup FILE] [--save SAV] [--clip]

The round-2 battle-string driver, used for the round-16 battle-string sweep. E (tools/hebrew/emu)
defaults to this script's ../..; HNS_SRC names the tree the ROM was built from. Save:
ladder6_postgame.sav (HNS_SAVES), SETUP tools/hebrew/emu/tours/_btw_strings_wild.txt or
_btw_strings_trainer.txt.

Shows battle strings (gBattleStringsTable, STRINGID_*) one at a time in a live wild battle and
takes one screenshot per page, from a battle script written into RAM:

    printstring ID ; waitmessage 1 ; HOLD: goto HOLD

The battle is set up by SETUP (an hns.py script: wild battle, FIGHT, a move), then the driver
waits until gBattleMainFunc == RunBattleScriptCommands (src/battle_main.c) with no controller
busy, takes a savestate there, and for every ID:
  - sets the placeholders the string reads (gBattlerAttacker 0, gBattlerTarget/gEffectBattler/
    gBattleScripting.battler 1, gLastUsedItem, gLastUsedAbility, gCurrentMove, gChosenMove,
    gBattleTextBuff1-3 per string; BtlController_EmitPrintString copies them,
    src/battle_controllers.c:997-1027),
  - points gBattlescriptCurrInstr at the RAM script,
  - snaps every page that waits for A (pressing A), then the last page once the script sits
    on HOLD (the controller has finished printing: Cmd_waitmessage waits for
    gBattleControllerExecFlags == 0).
A hang (no HOLD within MAXF frames) or a crash reloads the savestate and goes on.
Opcodes are looked up in the ROM's gBattleScriptingCommandsTable, so the same driver runs on
the Hebrew and the English build. Output: OUTDIR/sNNN_NAME[_vK]_PP.png, OUTDIR/results.json and,
on a clip build, OUTDIR/clip.json (cliptour reporter: glyphs drawn outside their window).
"""
import argparse
import json
import os
import re
import sys

E = os.environ.get("E", os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", ".."))   # tools/hebrew/emu
sys.path.insert(0, E)
sys.path.insert(0, os.path.dirname(E))
import hns  # noqa: E402

BS_BUF_OFF = 0xC00                       # into gRfuAPIBuffer (3684 bytes); the event script uses the start
OFF_BS_BATTLER = 0x17                     # struct BattleScripting: battler (probe, both trees)
OFF_BS_STATCHANGER = 0x1A
OFF_BMON_ABILITY = 0x20                   # struct BattlePokemon (0x88 bytes)
BMON_SIZE = 0x88
STAT = dict(HP=0, ATK=1, DEF=2, SPEED=3, SPATK=4, SPDEF=5, ACC=6, EVASION=7)


def ids_from_header(src):
    names = []
    body = open(os.path.join(src, "include/constants/battle_string_ids.h"), encoding="utf-8").read()
    body = body[body.index("enum StringID"):]
    body = body[body.index("{") + 1:body.index("};")]
    for line in body.splitlines():
        line = line.split("//")[0].strip().rstrip(",")
        if not line:
            continue
        if "=" in line:
            raise SystemExit("explicit enum value not handled: " + line)
        names.append(line)
    return {n: i for i, n in enumerate(names)}


_ENUMS = {}


def const(emu, name):
    """C constant: ABILITY_* and TYPE_* from their enums (explicit '= N' values), the rest through
    hns.resolve_const (which does not include constants/abilities.h)."""
    src = hns.src_dir(emu.elf)
    if src not in _ENUMS:
        d = {}
        for f in ("include/constants/abilities.h", "include/constants/pokemon.h"):
            for k, v in re.findall(r"^\s*((?:ABILITY|TYPE)_\w+)\s*=\s*(\d+)", open(os.path.join(src, f), encoding="utf-8").read(), re.M):
                d[k] = int(v)
        _ENUMS[src] = d
    if name in _ENUMS[src]:
        return _ENUMS[src][name]
    return emu.const(name)


class Ctx(object):
    """The placeholder values one string is shown with (see buffers())."""

    def __init__(self, emu, ids):
        self.emu, self.ids = emu, ids
        self.c = lambda name: const(emu, name)

    def buf(self, kind, *a):
        c = self.c
        if kind == "empty":
            return [0xFF]
        if kind == "stat":
            return [0xFD, 5, a[0], 0xFF]
        if kind == "str":
            sid = self.ids[a[0]]
            return [0xFD, 0, sid & 0xFF, sid >> 8, 0xFF]
        if kind == "move":
            m = c(a[0])
            return [0xFD, 2, m & 0xFF, m >> 8, 0xFF]
        if kind == "item":
            m = c(a[0])
            return [0xFD, 10, m & 0xFF, m >> 8, 0xFF]
        if kind == "ability":
            m = c(a[0])
            return [0xFD, 9, m & 0xFF, m >> 8, 0xFF]
        if kind == "species":
            m = c(a[0])
            return [0xFD, 6, m & 0xFF, m >> 8, 0xFF]
        if kind == "type":
            return [0xFD, 3, c(a[0]), 0xFF]
        if kind == "nick":           # battler, party slot
            return [0xFD, 7, a[0], a[1], 0xFF]
        if kind == "nickp":          # with the "wild"/"foe" prefix
            return [0xFD, 4, a[0], a[1], 0xFF]
        if kind == "byte":           # maxDigits, value
            return [0xFD, 1, 1, a[0], a[1], 0xFF]
        if kind == "hword":
            return [0xFD, 1, 2, a[0], a[1] & 0xFF, a[1] >> 8, 0xFF]
        if kind == "word":
            v = a[1]
            return [0xFD, 1, 4, a[0], v & 0xFF, (v >> 8) & 0xFF, (v >> 16) & 0xFF, v >> 24, 0xFF]
        if kind == "status":         # gStatusConditionString_*Jpn: 8 raw bytes, mapped by TryGetStatusString
            return list(self.emu.read(self.emu.sym("gStatusConditionString_%sJpn" % a[0]), 8))
        raise ValueError(kind)


def variants(name):
    """[(suffix, {buffers + overrides})] for one STRINGID name. Buffers follow how the engine fills
    them for that string (English text in pokehns-en/src/battle_message.c)."""
    up = ("ROSE",)
    v = []
    rose = name in ("STRINGID_ATTACKERSSTATROSE", "STRINGID_DEFENDERSSTATROSE", "STRINGID_SCRIPTINGSTATROSE",
                    "STRINGID_USINGITEMSTATOFPKMNROSE", "STRINGID_TARGETABILITYSTATRAISE",
                    "STRINGID_ATTACKERABILITYSTATRAISE", "STRINGID_SCRIPTINGABILITYSTATRAISE")
    fell = name in ("STRINGID_ATTACKERSSTATFELL", "STRINGID_DEFENDERSSTATFELL", "STRINGID_USINGITEMSTATOFPKMNFELL",
                    "STRINGID_TARGETABILITYSTATLOWER")
    if rose:
        for sfx, st, s in (("v1", "ATK", "STRINGID_EMPTYSTRING3"), ("v2", "SPATK", "STRINGID_STATSHARPLY"),
                           ("v3", "EVASION", "STRINGID_DRASTICALLY")):
            v.append((sfx, dict(b1=("stat", STAT[st]), b2=("str", s), statchanger=0x10 | STAT[st])))
        return v
    if fell:
        for sfx, st, s in (("v1", "ATK", "STRINGID_EMPTYSTRING3"), ("v2", "SPDEF", "STRINGID_STATHARSHLY"),
                           ("v3", "ACC", "STRINGID_SEVERELY")):
            v.append((sfx, dict(b1=("stat", STAT[st]), b2=("str", s), statchanger=0x80 | 0x10 | STAT[st])))
        return v
    if name in ("STRINGID_STATSWONTINCREASE", "STRINGID_TARGETSTATWONTGOHIGHER", "STRINGID_TARGETSSTATWASMAXEDOUT",
                "STRINGID_STATWASHEIGHTENED", "STRINGID_PKMNSXPREVENTSYLOSS", "STRINGID_ABILITYWEAKENEDSURROUNDINGMONSSTAT"):
        return [("v1", dict(b1=("stat", STAT["SPATK"]), statchanger=0x10 | STAT["SPATK"])),
                ("v2", dict(b1=("stat", STAT["EVASION"]), statchanger=0x10 | STAT["EVASION"]))]
    if name == "STRINGID_STATSWONTDECREASE":
        return [("v1", dict(b1=("stat", STAT["SPDEF"]), statchanger=0x80 | 0x10 | STAT["SPDEF"])),
                ("v2", dict(b1=("stat", STAT["ACC"]), statchanger=0x80 | 0x10 | STAT["ACC"]))]
    if name == "STRINGID_HITXTIMES":
        return [("v1", dict(b1=("byte", 1, 2))), ("v2", dict(b1=("byte", 2, 10)))]
    if name == "STRINGID_PKMNGAINEDEXP":
        return [("v1", dict(b1=("nick", 0, 0), b2=("str", "STRINGID_EMPTYSTRING4"), b3=("hword", 5, 1234))),
                ("v2", dict(b1=("nick", 0, 0), b2=("str", "STRINGID_ABOOSTED"), b3=("hword", 5, 1234)))]
    if name == "STRINGID_PKMNGREWTOLV":
        return [("", dict(b1=("nick", 0, 0), b2=("byte", 3, 51)))]
    if name in ("STRINGID_PKMNLEARNEDMOVE", "STRINGID_TRYTOLEARNMOVE1", "STRINGID_TRYTOLEARNMOVE2",
                "STRINGID_TRYTOLEARNMOVE3", "STRINGID_PKMNFORGOTMOVE", "STRINGID_STOPLEARNINGMOVE",
                "STRINGID_DIDNOTLEARNMOVE"):
        return [("", dict(b1=("nick", 0, 0), b2=("move", "MOVE_ICICLE_CRASH")))]
    if name in ("STRINGID_PLAYERGOTMONEY", "STRINGID_PLAYERWHITEOUT2_WILD", "STRINGID_PLAYERWHITEOUT2_TRAINER",
                "STRINGID_PLAYERPICKEDUPMONEY"):
        return [("v1", dict(b1=("word", 7, 240))), ("v2", dict(b1=("word", 7, 12480)))]
    if name in ("STRINGID_PKMNMADESLEEP", "STRINGID_PKMNPOISONEDBY", "STRINGID_PKMNBURNEDBY",
                "STRINGID_PKMNFROZENBY", "STRINGID_PKMNWASPARALYZEDBY"):
        ab = {"STRINGID_PKMNMADESLEEP": "ABILITY_EFFECT_SPORE", "STRINGID_PKMNPOISONEDBY": "ABILITY_POISON_POINT",
              "STRINGID_PKMNBURNEDBY": "ABILITY_FLAME_BODY", "STRINGID_PKMNFROZENBY": "ABILITY_FLAME_BODY",
              "STRINGID_PKMNWASPARALYZEDBY": "ABILITY_STATIC"}[name]
        return [("", dict(b1=("ability", ab)))]
    if name in ("STRINGID_PKMNCHANGEDTYPE", "STRINGID_PKMNCHANGEDTYPEWITH", "STRINGID_TARGETCHANGEDTYPE",
                "STRINGID_PROTEANTYPECHANGE", "STRINGID_THIRDTYPEADDED", "STRINGID_BATTLERTYPECHANGEDTO",
                "STRINGID_ATTACKERLOSTITSTYPE", "STRINGID_PKMNTERASTALLIZEDINTO"):
        return [("", dict(b1=("type", "TYPE_PSYCHIC")))]
    if name in ("STRINGID_PKMNHURTBY", "STRINGID_PKMNFREEDFROM", "STRINGID_PKMNGOTFREE"):
        return [("v1", dict(b1=("move", "MOVE_WRAP"))), ("v2", dict(b1=("move", "MOVE_FIRE_SPIN")))]
    if name in ("STRINGID_PKMNSTOCKPILED",):
        return [("", dict(b1=("byte", 1, 3)))]
    if name in ("STRINGID_PKMNPERISHCOUNTFELL",):
        return [("", dict(b1=("byte", 1, 2)))]
    if name in ("STRINGID_MAGNITUDESTRENGTH",):
        return [("", dict(b1=("byte", 2, 10)))]
    if name in ("STRINGID_PKMNTRANSFORMEDINTO", "STRINGID_MEGAEVOEVOLVED"):
        return [("", dict(b1=("species", "SPECIES_STARAPTOR")))]
    if name in ("STRINGID_PKMNREDUCEDPP",):
        return [("", dict(b1=("move", "MOVE_FLAMETHROWER"), b2=("byte", 1, 4)))]
    if name in ("STRINGID_PKMNTOOKATTACK",):
        return [("", dict(b1=("move", "MOVE_FUTURE_SIGHT")))]
    if name in ("STRINGID_PKMNATTACK", "STRINGID_PKMNWISHCAMETRUE", "STRINGID_PKMNREVIVEDREADYTOFIGHT",
                "STRINGID_ITEMRESTOREDSPECIESHEALTH", "STRINGID_ITEMCUREDSPECIESSTATUS",
                "STRINGID_ITEMRESTOREDSPECIESPP", "STRINGID_WILDPKMNFLED"):
        return [("", dict(b1=("nick", 1, 0)))]
    if name == "STRINGID_PKMNTRACED":
        return [("", dict(b1=("nickp", 1, 0), b2=("ability", "ABILITY_INTIMIDATE")))]
    if name == "STRINGID_ENEMYABOUTTOSWITCHPKMN":
        return [("", dict(b2=("nick", 1, 0)))]
    if name in ("STRINGID_PKMNCURIOUSABOUTX", "STRINGID_PKMNENTHRALLEDBYX", "STRINGID_PKMNIGNOREDX"):
        return [("", dict(b1=("item", "ITEM_POKEBLOCK_CASE")))]
    if name in ("STRINGID_PKMNSITEMCUREDPROBLEM", "STRINGID_PKMNSXCUREDYPROBLEM", "STRINGID_PKMNSXCUREDITSYPROBLEM"):
        return [("v1", dict(b1=("status", "Paralysis"), item="ITEM_LUM_BERRY")),
                ("v2", dict(b1=("status", "Confusion"), item="ITEM_LUM_BERRY"))]
    if name in ("STRINGID_PKMNSITEMRESTOREDPP",):
        return [("", dict(b1=("move", "MOVE_ICICLE_CRASH"), item="ITEM_LEPPA_BERRY"))]
    if name in ("STRINGID_PKMNOBTAINEDX", "STRINGID_PKMNOBTAINEDX2", "STRINGID_PKMNOBTAINEDXYOBTAINEDZ",
                "STRINGID_ABOUTTOUSEPOLTERGEIST", "STRINGID_PKMNHURTSWITH"):
        return [("", dict(b1=("item", "ITEM_ROCKY_HELMET"), b2=("item", "ITEM_LEFTOVERS")))]
    if name in ("STRINGID_CANACTFASTERTHANKSTO",):
        return [("", dict(b1=("item", "ITEM_QUICK_CLAW")))]
    if name in ("STRINGID_PKMNSXWOREOFF",):
        return [("", dict(b1=("move", "MOVE_LIGHT_SCREEN")))]
    if name in ("STRINGID_BUFFERENDS",):
        return [("", dict(b1=("move", "MOVE_TAUNT")))]
    if name in ("STRINGID_TARGETISHURTBYSALTCURE",):
        return [("", dict(b1=("move", "MOVE_SALT_CURE")))]
    if name in ("STRINGID_ATTACKERSWITCHEDSTATWITHTARGET",):
        return [("", dict(b1=("str", "STRINGID_STATSWONTINCREASE2")))]
    if name in ("STRINGID_PKMNMOVEWASDISABLED", "STRINGID_PKMNSKETCHEDMOVE", "STRINGID_PKMNLOSTPPGRUDGE",
                "STRINGID_CURSEDBODYDISABLED", "STRINGID_FOREWARNACTIVATES", "STRINGID_CURRENTMOVECANTSELECT",
                "STRINGID_PKMNLEARNEDMOVE2"):
        return [("", dict(b1=("move", "MOVE_ICICLE_CRASH")))]
    return [("", {})]


def find_opcode(emu, table, fn):
    try:
        wants = {emu.sym(fn)}
    except hns.HnsError as ex:           # a name two objects define (e.g. Cmd_goto): try each address
        wants = {int(x, 16) for x in re.findall(r":([0-9A-F]{8})", str(ex))}
        if not wants:
            raise
    for i in range(0, len(table), 4):
        if int.from_bytes(table[i:i + 4], "little") in wants:
            return i // 4
    raise hns.HnsError("%s not in gBattleScriptingCommandsTable" % fn)


class Sweep(object):
    def __init__(self, a):
        self.a = a
        self.rom = os.path.abspath(a.rom)
        self.elf = hns.Elf(os.path.splitext(self.rom)[0] + ".elf")
        self.out = os.path.abspath(a.out)
        os.makedirs(self.out, exist_ok=True)
        self.src = os.environ.get("HNS_SRC") or os.path.dirname(self.rom)
        self.ids = ids_from_header(self.src)
        self.names = {v: k for k, v in self.ids.items()}
        self.state = os.path.join(self.out, "_hold.ss")
        self.results = {}
        rp = os.path.join(self.out, "results.json")
        if a.resume and os.path.exists(rp):
            self.results = json.load(open(rp))
        self.emu = None

    def boot(self, fresh):
        if self.emu:
            try:
                self.emu.close()
            except Exception:
                pass
        save = None
        if fresh:
            save = os.path.join(self.out, "cur.sav")
            import shutil
            shutil.copyfile(self.a.save, save)
        self.emu = hns.Emu(self.rom, self.elf, self.out, save)
        if self.a.clip:
            sys.path.insert(0, os.path.dirname(E))
            import cliptour
            self.emu.clip = cliptour.install(self.emu, self.out, echo=False)
            # keep earlier shots' records in clip.json across restarts
            old = os.path.join(self.out, "clip_all.json")
            self._clipall = json.load(open(old)) if os.path.exists(old) else {}
        e = self.emu
        if fresh:
            e.run_script(self.a.setup)
            # the move's battle script is running and no controller is busy
            # a move's script runs from RunTurnActionsFunctions with gCurrentActionFuncId ==
            # B_ACTION_EXEC_SCRIPT (HandleAction_RunBattleScript); other scripts from
            # RunBattleScriptCommands(_PopCallbacksStack) (src/battle_util.c:1357-1370)
            ok = {e.sym("RunBattleScriptCommands"), e.sym("RunBattleScriptCommands_PopCallbacksStack")}
            rtaf = e.sym("RunTurnActionsFunctions")
            exec_script = 10   # B_ACTION_EXEC_SCRIPT, include/battle.h:49

            def ready():
                f = e.r32(e.sym("gBattleMainFunc"))
                if e.r32(e.sym("gBattleControllerExecFlags")) != 0:
                    return False
                return f in ok or (f == rtaf and e.r8(e.sym("gCurrentActionFuncId")) == exec_script)
            e.wait_until(ready, 1200, "a battle script to run", step=1)
            print("hijack at %s, instr %s" % (e.elf.where(e.r32(e.sym("gBattleMainFunc"))),
                                              e.elf.where(e.r32(e.sym("gBattlescriptCurrInstr")))))
            e.expect_after("ss %s" % self.state, r"^STATE ss .* ok")
        else:
            e.expect_after("sl %s" % self.state, r"^STATE sl .* ok")
        tab = e.read(e.sym("gBattleScriptingCommandsTable"), e.elf.size("gBattleScriptingCommandsTable"))
        self.op_print = find_opcode(e, tab, "Cmd_printstring")
        self.op_wait = find_opcode(e, tab, "Cmd_waitmessage")
        self.op_goto = find_opcode(e, tab, "Cmd_goto")
        self.op_native = find_opcode(e, tab, "Cmd_callnative")
        self.buf = e.sym("gRfuAPIBuffer") + BS_BUF_OFF
        self.ctx = Ctx(e, self.ids)

    def set_context(self, name, cfg):
        e = self.emu
        c = lambda n: const(e, n)
        e.w8(e.sym("gBattlerAttacker"), cfg.get("atk", 0))
        e.w8(e.sym("gBattlerTarget"), 1)
        e.w8(e.sym("gEffectBattler"), 1)
        e.w8(e.sym("gBattlerAbility"), 1)
        e.w8(e.sym("gPotentialItemEffectBattler"), 1)
        e.w8(e.sym("gBattleScripting") + OFF_BS_BATTLER, cfg.get("scr", 1))
        e.w8(e.sym("gBattleScripting") + OFF_BS_STATCHANGER, cfg.get("statchanger", 0x10 | STAT["ATK"]))
        e.w16(e.sym("gLastUsedItem"), c(cfg.get("item", "ITEM_SITRUS_BERRY")))
        e.w16(e.sym("gLastUsedAbility"), c(cfg.get("lastability", "ABILITY_LEVITATE")))
        e.w16(e.sym("gCurrentMove"), c(cfg.get("move", "MOVE_ICICLE_CRASH")))
        e.w16(e.sym("gChosenMove"), c(cfg.get("move", "MOVE_ICICLE_CRASH")))
        bm = e.sym("gBattleMons")
        e.w16(bm + OFF_BMON_ABILITY, c("ABILITY_SNOW_CLOAK"))
        e.w16(bm + BMON_SIZE + OFF_BMON_ABILITY, c("ABILITY_INTIMIDATE"))
        # MULTISTRING_CHOOSER (gBattleCommunication[5]) picks the up/down string PrepareStringBattle
        # swaps to; 0 = attacker
        e.w8(e.sym("gBattleCommunication") + 5, 0)
        defaults = {"b1": ("move", "MOVE_ICICLE_CRASH"), "b2": ("move", "MOVE_FLAMETHROWER"), "b3": ("move", "MOVE_ICICLE_CRASH")}
        for k, sym in (("b1", "gBattleTextBuff1"), ("b2", "gBattleTextBuff2"), ("b3", "gBattleTextBuff3")):
            data = self.ctx.buf(*cfg.get(k, defaults[k]))
            for i, b in enumerate(data):
                e.w8(e.sym(sym) + i, b)

    def show(self, sid, sfx, cfg, maxf=2400):
        e = self.emu
        name = self.names[sid]
        tag = "s%03d_%s%s" % (sid, name[len("STRINGID_"):], ("_" + sfx) if sfx else "")
        self.set_context(name, cfg)
        hold = self.buf + 6
        code = bytes([self.op_print, sid & 0xFF, sid >> 8, self.op_wait, 1, 0, self.op_goto]) + hold.to_bytes(4, "little")
        code += b"\0" * (-len(code) % 4)
        for i in range(0, len(code), 4):
            e.w32(self.buf + i, int.from_bytes(code[i:i + 4], "little"))
        instr = e.sym("gBattlescriptCurrInstr")
        e.w32(instr, self.buf)
        shots, waited, page = [], 0, 0
        last_box = None
        while True:
            e.frames(2)
            waited += 2
            st = e.text_state()
            if st == "key":
                page += 1
                p = "%s_%02d" % (tag, page)
                e.frames(2)
                e.shot(p)
                shots.append(p)
                last_box = hns.message_box(e)
                e.tap("A", 2)
                waited = 0
                continue
            if st == "idle" and e.r32(instr) == hold and e.r32(e.sym("gBattleControllerExecFlags")) == 0:
                break
            if waited > maxf:
                return tag, "HANG", shots
        box = hns.message_box(e)
        if box is not None and box != last_box:
            page += 1
            p = "%s_%02d" % (tag, page)
            e.frames(2)
            e.shot(p)
            shots.append(p)
        return tag, "OK", shots

    def popup(self, battler, ability, maxf=600):
        """Ability pop-up for BATTLER showing ABILITY: callnative BS_ShowAbilityPopup (reads
        gBattlerAbility and gBattleMons[].ability, src/battle_script_commands.c BS_ShowAbilityPopup),
        snap once it has slid in, then BS_DestroyAbilityPopup."""
        e = self.emu
        tag = "p%d_%s" % (battler, ability[len("ABILITY_"):])
        e.w8(e.sym("gBattlerAbility"), battler)
        e.w16(e.sym("gBattleMons") + BMON_SIZE * battler + OFF_BMON_ABILITY, const(e, ability))
        hold = self.buf + 5
        code = bytes([self.op_native]) + e.sym("BS_ShowAbilityPopup").to_bytes(4, "little") + \
            bytes([self.op_goto]) + hold.to_bytes(4, "little")
        code += b"\0" * (-len(code) % 4)
        for i in range(0, len(code), 4):
            e.w32(self.buf + i, int.from_bytes(code[i:i + 4], "little"))
        e.w32(e.sym("gBattlescriptCurrInstr"), self.buf)
        e.wait_until(lambda: hns.ability_popups(e), maxf, "pop-up %s" % tag, step=2)
        e.frames(4)
        e.shot(tag)
        hold2 = self.buf + 0x20 + 5
        code = bytes([self.op_native]) + e.sym("BS_DestroyAbilityPopup").to_bytes(4, "little") + \
            bytes([self.op_goto]) + hold2.to_bytes(4, "little")
        code += b"\0" * (-len(code) % 4)
        for i in range(0, len(code), 4):
            e.w32(self.buf + 0x20 + i, int.from_bytes(code[i:i + 4], "little"))
        e.w32(e.sym("gBattlescriptCurrInstr"), self.buf + 0x20)
        want = e.sym("Task_FreeAbilityPopUpGfx")
        e.wait_until(lambda: all(f != want for _, f, _ in e.tasks()), maxf, "pop-up gone", step=4)
        e.frames(4)
        return tag

    def run_popups(self, abilities):
        self.boot(True)
        res = {}
        for ab in abilities:
            for b in (1, 0):
                try:
                    tag = self.popup(b, ab)
                    clip = [dict(r, str="%08X" % r["str"]) for r in self.emu.clip.shots.get(tag, [])] if self.a.clip else []
                    res[tag] = dict(status="OK", clip=clip)
                    print("OK    %s%s" % (tag, (" CLIP %d" % len(clip)) if clip else ""))
                except hns.HnsError as ex:
                    res["p%d_%s" % (b, ab)] = dict(status="FAIL", detail=str(ex)[:200])
                    print("FAIL  p%d_%s %s" % (b, ab, str(ex)[:120]))
                    self.boot(False)
        json.dump(res, open(os.path.join(self.out, "popups.json"), "w"), indent=1, ensure_ascii=False)
        self.emu.close()

    def run(self, todo):
        self.boot(True)
        for sid in todo:
            name = self.names[sid]
            vs = self.vfile.get(name) if getattr(self, "vfile", None) and name in self.vfile else variants(name)
            for sfx, cfg in vs:
                cfg = {k: tuple(v) if isinstance(v, list) else v for k, v in cfg.items()}
                key = "%d%s" % (sid, sfx)
                if key in self.results:
                    continue
                try:
                    tag, st, shots = self.show(sid, sfx, cfg)
                except hns.HnsError as ex:
                    tag, st, shots = "s%03d_%s" % (sid, name), "CRASH", []
                    print("CRASH %s: %s" % (tag, str(ex).splitlines()[0]))
                    self.results[key] = dict(tag=tag, status=st, shots=shots, clip=[])
                    self.save()
                    self.boot(False)
                    continue
                clip = []
                if self.a.clip:
                    for s in shots:
                        clip += [dict(r, str="%08X" % r["str"]) for r in self.emu.clip.shots.get(s, [])]
                self.results[key] = dict(tag=tag, status=st, shots=shots, clip=clip)
                print("%-5s %-60s %d page(s)%s" % (st, tag, len(shots), (" CLIP %d" % len(clip)) if clip else ""))
                sys.stdout.flush()
                if st != "OK":
                    self.save()
                    self.boot(False)
                elif len(self.results) % 25 == 0:
                    self.save()
        self.save()
        self.emu.close()

    def save(self):
        json.dump(self.results, open(os.path.join(self.out, "results.json"), "w"), indent=1, ensure_ascii=False)


def parse_ids(spec, n):
    if not spec:
        return list(range(1, n))
    out = []
    for part in spec.split(","):
        if "-" in part:
            a, b = part.split("-")
            out += list(range(int(a), int(b) + 1))
        else:
            out.append(int(part))
    return out


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("rom")
    ap.add_argument("out")
    ap.add_argument("--ids", default=None, help="e.g. 1-100,250 (default: every ID but 0)")
    ap.add_argument("--setup", required=True)
    ap.add_argument("--save", required=True)
    ap.add_argument("--clip", action="store_true")
    ap.add_argument("--resume", action="store_true")
    ap.add_argument("--variants", default=None, help="JSON {STRINGID_X: [[sfx, cfg], ...]} replacing the built-in variants")
    ap.add_argument("--popups", default=None, help="comma-separated ABILITY_* names: ability pop-up mode")
    a = ap.parse_args()
    s = Sweep(a)
    s.vfile = json.load(open(a.variants)) if a.variants else None
    if a.popups:
        s.run_popups(a.popups.split(","))
        return
    count = s.ids["STRINGID_COUNT"]
    s.run([i for i in parse_ids(a.ids, count) if i < count])


if __name__ == "__main__":
    main()
