#!/usr/bin/env python3
"""Show every move in the battle fight menu: the four move-name slots, the PP / type window with
its effectiveness marker, and the START move-info window.

  fight_moves.py ROM OUTDIR [--save S] [--clip] [--first N] [--last N] [--no-rotate]
                 [--moves MOVE_A,MOVE_B,...]

One wild battle (tours/_bfm_base.txt: Smeargle Lv50 vs Geodude Lv10 on Route 30) stays open
the whole run. Before each FIGHT the four moves to show are written into gBattleMons[0].moves
and .pp (current PP = the move's base PP, so the PP window reads NN/NN); src/battle_main.c:
4451-4471 copies them into the CONTROLLER_CHOOSEMOVE buffer every time FIGHT is chosen, so B
and FIGHT again shows the next four. Moves 1..MOVES_COUNT-1 are shown (the Z- and Max-moves
cannot be chosen), four per group:

  gNNN_cS   cursor on slot S (0-3): the four names and the PP / type / effectiveness of slot S
  gNNN_iS   the START window of slot S (category, power, accuracy, description)
  gNNN_rR   the same four moves rotated by R (1-3), so every name is drawn in every slot

With --moves only the listed moves are shown, four per group in the order given (the last group
is filled up with the first listed moves); --first/--last then count these groups.

A last group shows low current PP (1-digit, the PP colours). OUTDIR/manifest.json maps each
screenshot to its moves; OUTDIR/moves.json lists every move as the ROM holds it (name and
description bytes decoded with the tree's charmap, type, category, power, accuracy, PP).
With --clip (an RTL_CLIP_REPORT build) OUTDIR/clip.json holds the clip records per screenshot.

Environment as for hns.py (HNS_RUNNER, HNS_SRC = the ROM's source tree, HNS_SAVES).
"""
import argparse
import json
import os
import re
import struct
import sys
import time

HERE = os.path.dirname(os.path.abspath(__file__))
EMU = os.path.dirname(HERE)
sys.path.insert(0, EMU)
sys.path.insert(0, os.path.dirname(EMU))
import hns  # noqa: E402
import textwidth as tw  # noqa: E402

MOVE_INFO_SIZE = 68                       # sizeof(struct MoveInfo), include/move.h:75
MI_PP = 14                                # u8 pp
BM_SIZE, BM_MOVES, BM_PP = 0x88, 0x0C, 0x25   # struct BattlePokemon: u16 moves[4], u8 pp[4]
LOW_PP = [1, 0, 9, 2]                     # current PP of the four moves of the PP group


def move_ids(src):
    """{id: MOVE_NAME} for 1..MOVES_COUNT-1, from include/constants/moves.h of SRC."""
    vals, out, nxt = {}, {}, 0
    text = open(os.path.join(src, "include", "constants", "moves.h"), encoding="utf-8").read()
    body = text[text.index("enum __attribute__((packed)) Move"):]
    body = body[:body.index("};")]
    for line in body.split("\n"):
        line = line.split("//", 1)[0].strip().rstrip(",")
        m = re.match(r"^([A-Z0-9_]+)(?:\s*=\s*(\w+))?$", line)
        if not m:
            continue
        name, val = m.group(1), m.group(2)
        if val is None:
            v = nxt
        elif val.isdigit():
            v = int(val)
        else:
            v = vals[val]
            if name.startswith("MOVE_") and val.startswith("MOVE_"):
                vals[name] = v          # an alias (pre-Gen VI name)
                continue
        vals[name] = v
        nxt = v + 1
        if name.startswith("MOVE_") and name != "MOVE_NONE":
            out.setdefault(v, name)
    count = vals["MOVES_COUNT"]
    return {k: v for k, v in sorted(out.items()) if 0 < k < count}


def read_moves(rom_path, elf, src):
    rom = open(rom_path, "rb").read()
    cm = tw.Charmap(os.path.join(src, "charmap.txt"))
    base = elf.sym("gMovesInfo") - 0x08000000

    def cstr(ptr):
        off = ptr - 0x08000000
        end = rom.index(b"\xff", off)
        return rom[off:end]

    out = {}
    for mid, const in move_ids(src).items():
        e = rom[base + MOVE_INFO_SIZE * mid:base + MOVE_INFO_SIZE * (mid + 1)]
        name_p, desc_p = struct.unpack_from("<II", e, 0)
        w10, w12 = struct.unpack_from("<HH", e, 10)
        name, desc = cstr(name_p), cstr(desc_p)
        out[mid] = dict(id=mid, const=const, name=cm.decode(name), name_hex=name.hex(),
                        desc=cm.decode(desc), desc_hex=desc.hex(), type=w10 & 0x1F,
                        category=(w10 >> 5) & 3, power=w10 >> 7, accuracy=w12 & 0x7F,
                        pp=e[MI_PP])
    return out


def set_moves(emu, moves, pps):
    bm = emu.sym("gBattleMons")
    emu.send("w32 %08X %08X" % (bm + BM_MOVES, moves[0] | moves[1] << 16))
    emu.send("w32 %08X %08X" % (bm + BM_MOVES + 4, moves[2] | moves[3] << 16))
    for i, p in enumerate(pps):
        emu.w8(bm + BM_PP + i, p)


def open_fight(emu):
    emu.wait_battle_input("HandleInputChooseAction")
    hns.battle_cursor(emu, "gActionSelectionCursor", 0)
    emu.tap("A", 4)
    emu.wait_battle_input("HandleInputChooseMove")


def close_fight(emu):
    emu.tap("B", 4)
    emu.wait_battle_input("HandleInputChooseAction")


def cursor(emu, slot):
    hns.battle_cursor(emu, "gMoveSelectionCursor", slot)
    emu.wait_quiet()


def check_slots(emu, moves, pps):
    bm = emu.sym("gBattleMons")
    got = struct.unpack("<4H", emu.read(bm + BM_MOVES, 8))
    if list(got) != list(moves):
        raise hns.HnsError("gBattleMons[0].moves is %s, wrote %s" % (got, moves))


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("rom")
    ap.add_argument("outdir")
    ap.add_argument("--save", default=None, help="default: HNS_SAVES/ladder1_newgame.sav (a copy is used)")
    ap.add_argument("--clip", action="store_true")
    ap.add_argument("--first", type=int, default=0, help="first group")
    ap.add_argument("--last", type=int, default=None, help="last group (inclusive)")
    ap.add_argument("--no-rotate", action="store_true")
    ap.add_argument("--no-info", action="store_true")
    ap.add_argument("--moves", default=None, help="comma-separated MOVE_* names: show only these")
    a = ap.parse_args()

    src = os.environ.get("HNS_SRC") or os.path.dirname(os.path.abspath(a.rom))
    elf = hns.Elf(os.path.splitext(a.rom)[0] + ".elf")
    os.makedirs(a.outdir, exist_ok=True)
    moves = read_moves(a.rom, elf, src)
    with open(os.path.join(a.outdir, "moves.json"), "w", encoding="utf-8") as fh:
        json.dump(moves, fh, ensure_ascii=False, indent=1)
    ids = sorted(moves)
    shown = ids
    if a.moves:
        by_const = {m["const"]: mid for mid, m in moves.items()}
        missing = [c for c in a.moves.split(",") if c not in by_const]
        if missing:
            raise SystemExit("not in %s: %s" % (src, ", ".join(missing)))
        shown = [by_const[c] for c in a.moves.split(",")]
    groups = [shown[i:i + 4] for i in range(0, len(shown), 4)]
    while len(groups[-1]) < 4:
        groups[-1].append(shown[len(groups[-1]) % len(shown)] if a.moves else ids[0])
    # The PP group: 1-digit current PP against 1- and 2-digit maxima (PP colours of
    # GetCurrentPpToMaxPpState, src/battle_message.c:4059)
    pp_group = [m for m in ids if moves[m]["pp"] == 5][:1] + [m for m in ids if moves[m]["pp"] == 10][:1] + \
               [m for m in ids if moves[m]["pp"] == 40][:1] + [m for m in ids if moves[m]["pp"] == 15][:1]
    last = len(groups) - 1 if a.last is None else min(a.last, len(groups) - 1)

    save = a.save or os.path.join(os.environ.get("HNS_SAVES", ""), "ladder1_newgame.sav")
    emu = hns.Emu(a.rom, elf, a.outdir, hns.prepare_save(save, a.outdir, False))
    rep = None
    if a.clip:
        rep = hns.clip_hook(emu, a.outdir)
    manifest = {}
    mpath = os.path.join(a.outdir, "manifest.json")
    if os.path.exists(mpath):
        manifest = json.load(open(mpath))
    t0 = time.time()
    rc = 0
    try:
        emu.run_script(os.path.join(EMU, "tours", "_bfm_base.txt"))
        todo = [(gi, groups[gi], None) for gi in range(a.first, last + 1)]
        if a.last is None and not a.moves:
            todo.append(("pp", pp_group, LOW_PP))
        for gi, g, low in todo:
            tag = "g%03d" % gi if isinstance(gi, int) else "g_" + gi
            pps = [moves[m]["pp"] for m in g] if low is None else list(low)
            set_moves(emu, g, pps)
            open_fight(emu)
            check_slots(emu, g, pps)
            for s in range(4):
                cursor(emu, s)
                emu.frames(2)
                name = "%s_c%d" % (tag, s)
                emu.shot(name)
                manifest[name] = dict(kind="cursor", slots=g, pp=pps, cursor=s)
                if not a.no_info:
                    emu.tap("START", 4)
                    emu.wait_quiet()
                    emu.frames(2)
                    name = "%s_i%d" % (tag, s)
                    emu.shot(name)
                    manifest[name] = dict(kind="info", slots=g, pp=pps, cursor=s)
                    emu.tap("START", 4)
                    emu.wait_quiet()
            close_fight(emu)
            if not a.no_rotate and low is None:
                for r in range(1, 4):
                    rg = [g[(k - r) % 4] for k in range(4)]   # move g[k] in slot (k + r) % 4
                    rp = [moves[m]["pp"] for m in rg]
                    set_moves(emu, rg, rp)
                    open_fight(emu)
                    cursor(emu, 0)
                    emu.frames(2)
                    name = "%s_r%d" % (tag, r)
                    emu.shot(name)
                    manifest[name] = dict(kind="rotation", slots=rg, pp=rp, cursor=0)
                    close_fight(emu)
            with open(mpath, "w") as fh:
                json.dump(manifest, fh, indent=0)
            print("%s %s %.0fs @%d" % (tag, [moves[m]["const"] for m in g], time.time() - t0, emu.sync()))
            sys.stdout.flush()
    except hns.HnsError as e:
        print("ERROR: %s" % e)
        try:
            emu.shot("_error")
        except hns.HnsError:
            pass
        rc = 1
    finally:
        emu.close()
        with open(os.path.join(a.outdir, "run.log"), "w") as fh:
            fh.write("\n".join(emu.log) + "\n")
        with open(mpath, "w") as fh:
            json.dump(manifest, fh, indent=0)
    if rep:
        print("clip total: %d glyph(s), %d lost" % (rep.total(), rep.lost))
    print("%d screenshots, %.0fs" % (len(manifest), time.time() - t0))
    return rc


if __name__ == "__main__":
    sys.exit(main())
