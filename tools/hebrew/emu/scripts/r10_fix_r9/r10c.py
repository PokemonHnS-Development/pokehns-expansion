#!/usr/bin/env python3
"""rc5.py (scripts/r5_contests: the r2/r5 contest ops) plus the ops of the round-9 contest tours, copied for
the round-10 fix proofs (tours/r10_fix_r9; the round-9 originals are tours/r9_contests in rc12):

    setopps [keepgfx] A B C
                     copy gContestOpponents[A], [B], [C] (src/data/contest_opponents.h) over
                     gContestMons[0..2] (struct ContestPokemon, include/contest.h:88-115), so
                     the hall entry lines, the four name boxes of the appeal screen, the appeal
                     lines and the results screen show these opponents. Run it after
                     TryEnterContestMon (src/contest_util.c, which calls SetContestants) and
                     before SetContestTrainerGfxIds (the lobby walk to the hall), e.g. while
                     the receptionist's 'entry No. 4' message waits for a key. With keepgfx
                     the slot keeps its trainerGfxId (offset 23), so the hall objects stay the
                     ones SetContestants picked and only the names, species and moves change.
                     On a string-report build each slot is registered as a RAM copy of its
                     opponent (strcov.map_ram), so the names are logged at their ROM address.
    fullpocket POCKET ITEM [QTY]
                     fill every slot of gBagPockets[POCKET] with ITEM x QTY (the op of
                     scripts/r5_npcsvc/npcsvc.py), so giveitem of that pocket fails (bag full)
    oppnames         print the four contestants' trainer names and nicknames (raw bytes)
    pcwatch N PREFIX step one frame at a time for N frames; after each frame print the PC when
                     it is outside BIOS/ROM/RAM and stop; a shot PREFIX_NNN every frame of the last
                     16 (kept in a ring, so the frames before a crash are on disk)
    trysoft OP ...   run another op and report a TourTimeout instead of ending the tour
                     (debugging: run fieldwatch for a fixed time, then crashwatch)

Run:  r10c.py tour ROM OUT --tours tools/hebrew/emu/tours/r10_fix_r9 [--clip] [--only RE]
"""
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(HERE, "..", ".."))                       # tools/hebrew/emu
sys.path.insert(0, os.path.join(HERE, "..", "..", ".."))                 # tools/hebrew
sys.path.insert(0, os.path.join(HERE, "..", "r5_contests"))
import hns  # noqa: E402
import strcov  # noqa: E402
import rc5  # noqa: E402,F401  (registers rc.py, hilltent_ops and the r5 contest ops)
from hns import script_op, HnsError, TourTimeout  # noqa: E402

CONTESTANT_COUNT = 4
NICK_OFF, NICK_LEN, TRAINER_OFF, TRAINER_LEN = 2, 13, 15, 8   # u16 species; nickname[12+1]; trainerName[7+1]
GFX_OFF = 23                                                    # u8 trainerGfxId


def _mon_size(emu):
    return emu.elf.size("gContestMons") // CONTESTANT_COUNT


@script_op("setopps")
def _op_setopps(emu, f, path):
    size = _mon_size(emu)
    nopp = emu.elf.size("gContestOpponents") // size
    src0, dst0 = emu.sym("gContestOpponents"), emu.sym("gContestMons")
    keepgfx = len(f) > 1 and f[1] == "keepgfx"
    ids = [int(x) for x in f[2 if keepgfx else 1:]]
    if len(ids) > CONTESTANT_COUNT - 1:
        raise HnsError("setopps: at most 3 opponents (contestant 3 is the player)")
    for slot, oid in enumerate(ids):
        if not 0 <= oid < nopp:
            raise HnsError("setopps: opponent %d out of range (0..%d)" % (oid, nopp - 1))
        data = emu.read(src0 + oid * size, size)
        data = data + b"\0" * (-len(data) % 4)
        dst = dst0 + slot * size
        if keepgfx:
            data = data[:GFX_OFF] + emu.read(dst + GFX_OFF, 1) + data[GFX_OFF + 1:]
        for k in range(0, len(data), 4):
            emu.w32(dst + k, int.from_bytes(data[k:k + 4], "little"))
        if emu.read(dst, size) != data[:size]:
            raise HnsError("setopps: slot %d did not read back" % slot)
        strcov.map_ram(emu, dst, src0 + oid * size, size)          # as SetContestants does
    print("setopps %s%s (struct %d bytes, %d opponents) @%d" % ("keepgfx " if keepgfx else "", " ".join(map(str, ids)), size, nopp, emu.sync()))


SB2_ENCKEY = 0xAC


@script_op("fullpocket")
def _op_fullpocket(emu, f, path):
    pocket, item = emu.const(f[1]), emu.const(f[2])
    qty = int(f[3]) if len(f) > 3 else 999
    bp = emu.sym("gBagPockets") + 8 * pocket
    slots, cap = emu.r32(bp), emu.r16(bp + 4) & 0x3FF
    key = emu.r32(emu.r32(emu.sym("gSaveBlock2Ptr")) + SB2_ENCKEY) & 0xFFFF
    for i in range(cap):
        emu.w16(slots + 4 * i, item)
        emu.w16(slots + 4 * i + 2, qty ^ key)
    if emu.r16(slots + 4 * (cap - 1)) != item:
        raise HnsError("fullpocket: the last slot did not read back")
    emu.fullpocket_last = slots + 4 * (cap - 1)
    print("fullpocket %s: %d slot(s) of %s x%d @%d" % (f[1], cap, f[2], qty, emu.sync()))


@script_op("freeslot")
def _op_freeslot(emu, f, path):
    """freeslot: empty the last slot fullpocket filled (item 0, quantity 0 = the key), so the next
    giveitem fits."""
    key = emu.r32(emu.r32(emu.sym("gSaveBlock2Ptr")) + SB2_ENCKEY) & 0xFFFF
    emu.w16(emu.fullpocket_last, 0)
    emu.w16(emu.fullpocket_last + 2, key)
    print("freeslot %08X @%d" % (emu.fullpocket_last, emu.sync()))


@script_op("oppnames")
def _op_oppnames(emu, f, path):
    size = _mon_size(emu)
    base = emu.sym("gContestMons")
    for i in range(CONTESTANT_COUNT):
        b = emu.read(base + i * size, size)
        nick = b[NICK_OFF:NICK_OFF + NICK_LEN].split(b"\xff")[0].hex()
        tr = b[TRAINER_OFF:TRAINER_OFF + TRAINER_LEN].split(b"\xff")[0].hex()
        print("contestant %d: trainer %s nickname %s" % (i, tr, nick))


@script_op("pcwatch")
def _op_pcwatch(emu, f, path):
    n, prefix = int(f[1]), f[2]
    ring = []
    for i in range(n):
        emu.frames(1)
        pc = emu.pc()
        name = "%s_%03d" % (prefix, i % 16)
        emu.shot(name)
        ring.append((i, emu.sync(), pc, emu.cb2_name(), [t[2] for t in emu.tasks()]))
        ring = ring[-16:]
        if not (pc < 0x4000 or 0x02000000 <= pc < 0x02040000 or 0x03000000 <= pc < 0x03008000
                or 0x08000000 <= pc < 0x0A000000):
            for r in ring:
                print("pcwatch +%d @%d pc=%08X %s %s" % (r[0], r[1], r[2], r[3], r[4]))
            print("pcwatch: PC %08X (%s) after %d frames" % (pc, emu.elf.where(pc & ~0x02000000), i + 1))
            return
    print("pcwatch: %d frames, PC stayed in BIOS/ROM/RAM" % n)


@script_op("trysoft")
def _op_trysoft(emu, f, path):
    try:
        hns.SCRIPT_OPS[f[1]](emu, f[1:], path)
    except TourTimeout as e:
        print("trysoft %s: %s" % (f[1], e))


if __name__ == "__main__":
    sys.argv[0] = hns.__file__
    sys.exit(hns.main())
