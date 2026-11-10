#!/usr/bin/env python3
"""dbgmenu.py ROM OUTDIR --setup FILE --save SAV [--clip] [--only info,party,switch] [--party-pages K,K]

The battle debug menu's AI pages with every hold-effect name (src/battle_debug.c sHoldEffectNames,
printed by GetHoldEffectName) and the AI's "switching to" line. E (tools/hebrew/emu) is this script's
../..; HNS_SRC names the tree the ROM was built from. Run from a work dir outside the worktree, with
HNS_MAX_FRAMES set. Save: ladder1_newgame.sav (HNS_SAVES); SETUP: tools/hebrew/emu/tours/
_btw_dbg_trainer.txt (Youngster Mikey, two foes, stopped at the action menu).

The menu opens with SELECT at the action menu (DEBUG_BATTLE_MENU, src/battle_controller_player.c).
Main list rows (src/battle_debug.c): 12 AI points, 13 AI info, 14 AI party.
  switch  row 12 with gAiLogicData->shouldSwitch bit 1 set and mostSuitableMonId[1] = 1 (the foe's
          second Pokemon): PutMovesPointsText prints the red "switching to <species>" line.
  info    row 13 once per hold effect: gAiLogicData->holdEffects[0] (the player battler) is set
          before the page opens; PutAiInfoText prints it with FONT_SMALL at x 83.
  party   row 14, six hold effects per page: gAiPartyData->mons[side][0..5].heldEffect and
          count[side] = 6 for both sides; PutAiPartyText prints the first 7 bytes of each name with
          FONT_SMALL_NARROW in 41 px columns (opened once as is first: its first drawing is
          garbled in both builds). --party-pages K,K draws only those pages (effects 6K+1 .. 6K+6).
Each page is shot, and closed, only once the DMA3 queue has no pending copy (src/dma3_manager.c
sDma3Requests): every string is printed at speed 0, which queues a copy of the whole window, and
the queue moves at most 40 KiB a frame, so a six-Pokemon party page reaches the screen about 22
frames after its task starts. Closed earlier, the page clears its tilemap under copies still
queued, and the next page comes up blank.
Struct offsets (tools/hebrew/emu/probe style probe, the Hebrew and English trees agree):
AiLogicData holdEffects +0x10 (u8 each), mostSuitableMonId +0x378, shouldSwitch bits 0-3 of
+0x3C5; AiPartyData mons +0 (AiPartyMon 0x1C bytes, heldEffect +4), count +0x150.
Output: OUTDIR/*.png, OUTDIR/dbgmenu.json (shot -> hold effects shown), clip.json with --clip.
"""
import argparse
import json
import os
import re
import shutil
import sys

E = os.environ.get("E", os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", ".."))
sys.path.insert(0, E)
sys.path.insert(0, os.path.dirname(E))
import hns  # noqa: E402

AI_HOLD = 0x10
AI_SUITABLE = 0x378
AI_FLAGS_SWITCH = 0x3C5
PARTY_MON, PARTY_MON_HELD, PARTY_COUNT = 0x1C, 4, 0x150
DMA_REQUEST, DMA_REQUEST_SIZE = 16, 8   # struct Dma3Request: src, dest, u16 size (0 = free), mode, value
PAGE_FRAMES, SETTLE_FRAMES = 8, 240


def hold_effects(src):
    body = open(os.path.join(src, "include/constants/hold_effects.h"), encoding="utf-8").read()
    body = body[body.index("enum __attribute__((packed)) HoldEffect"):]
    body = body[body.index("{") + 1:body.index("};")]
    out = []
    for line in body.splitlines():
        line = line.split("//")[0].strip().rstrip(",")
        if line:
            if "=" in line:
                raise SystemExit("explicit enum value not handled: " + line)
            out.append(line)
    return out


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("rom")
    ap.add_argument("out")
    ap.add_argument("--setup", required=True)
    ap.add_argument("--save", required=True)
    ap.add_argument("--clip", action="store_true")
    ap.add_argument("--only", default="switch,info,party")
    ap.add_argument("--party-pages", default="", help="the six-effect party pages to draw (k numbers, default all)")
    a = ap.parse_args()
    rom = os.path.abspath(a.rom)
    out = os.path.abspath(a.out)
    os.makedirs(out, exist_ok=True)
    src = os.environ.get("HNS_SRC") or os.path.dirname(rom)
    names = hold_effects(src)
    count = names.index("HOLD_EFFECT_COUNT")
    effects = list(range(1, count))
    cur = os.path.join(out, "cur.sav")
    shutil.copyfile(a.save, cur)
    elf = hns.Elf(os.path.splitext(rom)[0] + ".elf")
    e = hns.Emu(rom, elf, out, cur)
    if a.clip:
        import cliptour
        cliptour.install(e, out, echo=False)
    shown = {}
    only = set(a.only.split(","))

    def press(k, n=1):
        for _ in range(n):
            e.tap(k, 4)
            e.wait_quiet(600)

    def menu():
        if not e.wait_task("Task_DebugMenuProcessInput", 240):
            raise hns.HnsError("debug menu list did not come back")

    dma = e.sym("sDma3Requests")
    dma_len = e.elf.size("sDma3Requests")

    def dma_pending():
        raw = e.read(dma, dma_len)
        return sum(1 for i in range(DMA_REQUEST_SIZE, dma_len, DMA_REQUEST) if raw[i] | raw[i + 1])

    def settle(what):
        waited = 0
        while dma_pending():
            if waited >= SETTLE_FRAMES:
                raise hns.HnsError("%s: the DMA3 queue still holds copies after %d frames" % (what, waited))
            e.frames(2)
            waited += 2

    def view(task, shot, rows):
        press("A")
        if not e.wait_task(task, 240):
            raise hns.HnsError("%s did not start" % task)
        e.frames(PAGE_FRAMES)           # the page queues its copies in the first frames of its task
        settle(shot)
        e.snap(shot)
        shown[shot] = rows
        settle(shot)
        press("B")
        menu()

    try:
        e.run_script(a.setup)
        e.tap("SELECT", 4)
        if not e.wait_task("Task_DebugMenuProcessInput", 900):
            raise hns.HnsError("debug menu did not open")
        e.snap("dbg_main")
        press("DOWN", 12)
        ai = e.r32(e.sym("gAiLogicData"))
        party = e.r32(e.sym("gAiPartyData"))
        if "switch" in only:
            view("Task_ShowAiPoints", "dbg_p12_points_asis", [])
            e.w8(ai + AI_FLAGS_SWITCH, e.r8(ai + AI_FLAGS_SWITCH) | 0x02)
            e.w8(ai + AI_SUITABLE + 1, 1)
            view("Task_ShowAiPoints", "dbg_p12_points_switch", ["shouldSwitch battler 1 -> slot 1"])
            e.w8(ai + AI_FLAGS_SWITCH, e.r8(ai + AI_FLAGS_SWITCH) & ~0x02)
        press("DOWN")
        if "info" in only:
            old = e.r8(ai + AI_HOLD)
            for h in effects:
                e.w8(ai + AI_HOLD, h)
                view("Task_ShowAiKnowledge", "dbg_p13_info_h%03d" % h, [names[h]])
            e.w8(ai + AI_HOLD, old)
        press("DOWN")
        if "party" in only:
            # the first opening of the page draws over the AI-info page left in the window (both
            # builds), so it is opened once as is before the pokes
            view("Task_ShowAiParty", "dbg_p14_party_asis", [])
            pages = {int(x) for x in a.party_pages.split(",") if x}
            for k in range(0, len(effects), 6):
                if pages and k // 6 not in pages:
                    continue
                grp = effects[k:k + 6]
                for side in (0, 1):
                    for i in range(6):
                        h = grp[i] if i < len(grp) else 0
                        e.w8(party + (side * 6 + i) * PARTY_MON + PARTY_MON_HELD, h)
                    e.w8(party + PARTY_COUNT + side, len(grp))
                view("Task_ShowAiParty", "dbg_p14_party_k%02d" % (k // 6), [names[h] for h in grp])
        e.snap("dbg_end")
    finally:
        json.dump(shown, open(os.path.join(out, "dbgmenu.json"), "w"), indent=1)
        e.close()


if __name__ == "__main__":
    main()
