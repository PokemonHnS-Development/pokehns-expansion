#!/usr/bin/env python3
"""hns.py plus the ops the r6 Kanto / post-League story tours use (tours/r6_story_kanto/*.txt):
everything from scripts/r6_league/r6league.py, plus

    objfreeze LOCALID [MAX]  wait until the object with that local id stands still on a tile (no
                             single movement active), then set its frozen bit (struct ObjectEvent
                             byte 1 bit 0, include/global.fieldmap.h), so a walking NPC can be
                             approached and talked to; the script's release unfreezes it again

    followers on|off         the FOLLOWERS option (ChallengeSettings.followerEnable, byte 0 bit 0 of
                             SaveBlock3.challengeSettings, include/global.h:256; 1 = off; the
                             large-follower bit 1 is cleared with it), read by
                             UpdateFollowingPokemon (src/event_object_movement.c); the follower
                             appears on the next map load

Run:  r6story.py tour ROM OUT --tours <emu>/tours/r6_story_kanto [--clip] [--only RE]
"""
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(HERE, "..", "r6_league"))
import r6league  # noqa: E402,F401  (r5 legend ops + sceneto, periodic, bwinwith, bitem, pickd)
import hns  # noqa: E402
from hns import script_op, _arg, HnsError  # noqa: E402

OBJ_SIZE = 0x24   # sizeof(struct ObjectEvent): localId +8, currentCoords +0x10, previousCoords +0x14


def _slot(emu, lid):
    base = emu.sym("gObjectEvents")
    for i in range(16):
        a = base + i * OBJ_SIZE
        b = emu.read(a, OBJ_SIZE)
        if b[0] & 1 and not b[2] & 1 and b[8] == lid:
            return a, b
    return None, None


@script_op("objfreeze")
def _op_objfreeze(emu, f, path):
    lid = int(f[1], 0)
    for t in range(_arg(f, 2, 600)):
        a, b = _slot(emu, lid)
        if a is None:
            raise HnsError("objfreeze: no object %d" % lid)
        still = not (b[0] & 2) and b[0x10:0x14] == b[0x14:0x18]
        if still:
            emu.w8(a + 1, b[1] | 1)
            x = int.from_bytes(b[0x10:0x12], "little", signed=True) - 7
            y = int.from_bytes(b[0x12:0x14], "little", signed=True) - 7
            print("objfreeze %d: frozen at (%d,%d) @%d" % (lid, x, y, emu.sync()))
            return
        emu.frames(1)
    raise HnsError("objfreeze: object %d never stood still" % lid)


@script_op("followers")
def _op_followers(emu, f, path):
    addr = emu.r32(emu.sym("gSaveBlock3Ptr")) + hns.BATTLE_OFF["SaveBlock3.challengeSettings"]
    v = emu.r8(addr)
    emu.w8(addr, (v & ~3) if f[1].lower() == "on" else (v | 1))
    print("followers %s (byte %02X -> %02X)" % (f[1], v, emu.r8(addr)))


if __name__ == "__main__":
    sys.argv[0] = hns.__file__
    sys.exit(hns.main())
