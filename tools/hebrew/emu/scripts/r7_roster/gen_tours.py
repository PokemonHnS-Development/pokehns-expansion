#!/usr/bin/env python3
"""Write the r7 roster tours (tours/r7_roster/*.txt).

  r7r_dome_N.txt    Battle Dome: the 320 Frontier trainers (ids 0-319) written 15 at a time into
                    domeTrainers[1..15]; per batch the tourney tree and the info card of every slot.
  r7r_tower_N.txt   Battle Tower singles: one battle per listed trainer id (opponentA pinned before
                    tower_setopponent), intro, send-outs and the win line; WIDE ids also force the
                    'about to send out' line (bwinsw).
Run:  python3 gen_tours.py      (paths are relative to this file)
"""
import os

HERE = os.path.dirname(os.path.abspath(__file__))
OUT = os.path.join(HERE, "..", "..", "tours", "r7_roster")

# ids 315-319 plus the widest names (FONT_SHORT with letterSpacing 2, the tree's printer)
FILL = [97, 52, 96, 188, 9, 254, 2, 197, 285, 186]
BATCHES = [list(range(15 * b, 15 * b + 15)) for b in range(21)] + [list(range(315, 320)) + FILL]
DOME_TOURS = [range(0, 6), range(6, 12), range(12, 17), range(17, 22)]

# the widest class+name of each facility class (textwidth.py, FONT_NORMAL)
CLASS_REPS = [2, 3, 7, 9, 14, 16, 204, 207, 25, 179, 30, 33, 37, 40, 43, 46, 50, 52, 55, 57, 185,
              64, 66, 71, 74, 188, 191, 83, 194, 197, 264, 266, 95, 97, 98, 106, 109, 242, 243,
              247, 121, 254, 255, 131, 261, 140, 227, 147, 231, 152, 300, 301, 302, 303, 304, 305,
              306, 307, 308, 309, 310, 311, 312, 313, 314, 315, 316, 317, 318, 319]
WIDE = [152, 185, 191]          # widest class+name overall: forced 'about to send out' line
TOWER_TOURS = 7

HEAD = """start saves/r7/r7_roster_base.sav
include ../../scripts/continue.txt
"""

DOME_ENTER = """ev setflag FLAG_SYS_FRONTIER_PASS; setvar VAR_HAS_ENTERED_BATTLE_FRONTIER, 1; end
warptoloose MAP_BATTLE_FRONTIER_BATTLE_DOME_LOBBY_HNS 5 11
waitnotask Task_MapNamePopUpWindow 600
face UP
tap A 0
drive dt_in menu
pick 0
drive dt_lv menu
pick 0
drive dt_sel task:Task_HandleChooseMonInput 20
include ../../scripts/r2_battle_frontier_facilities/_bf_enter3.txt
drive dt_save menu 10
pick 0
saveyes
drivex dt_go menu 30 9000
"""

TOWER_ENTER = """ev setflag FLAG_SYS_FRONTIER_PASS; setvar VAR_HAS_ENTERED_BATTLE_FRONTIER, 1; end
warptoloose MAP_BATTLE_FRONTIER_BATTLE_TOWER_LOBBY_HNS 6 6
waitnotask Task_MapNamePopUpWindow 600
face UP
tap A 0
drive tw_in menu
pick 0
drive tw_lv menu
pick 0
drive tw_sel task:Task_HandleChooseMonInput 20
include ../../scripts/r2_battle_frontier_facilities/_bf_enter3.txt
drive tw_save menu 10
pick 0
saveyes
fastbattles off
"""


def pinline(tid):
    return "pin @gTrainerBattleParameter+2@ %02X%02X" % (tid & 0xFF, tid >> 8)


def dome(n, batches):
    out = ["# r7 roster: Battle Dome tourney tree and info cards, batches %d-%d" % (batches[0], batches[-1]),
           HEAD + DOME_ENTER.rstrip()]
    for b in batches:
        ids = BATCHES[b]
        out.append("# batch %d: ids %s" % (b, " ".join(map(str, ids))))
        out.append("dometrainers " + " ".join(map(str, ids)))
        out.append("pick 1")
        out.append("drivex b%02d_msg cb2:CB2_TourneyTree 10 3000" % b)
        out.append("waittaskdata Task_HandleTourneyTreeInput 0 2 900")
        out.append("waitquiet")
        out.append("domelist b%02d_tree" % b)
        out.append("snap b%02d_tree" % b)
        out.append("domecards b%02d_card %d" % (b, 0 if b == batches[0] else 1))
        out.append("tap B 0")
        out.append("drivex b%02d_back menu 10 3000" % b)
    return "\n".join(out) + "\n"


def tower(n, ids):
    out = ["# r7 roster: Battle Tower singles intros, send-outs and win lines for trainer ids %s"
           % " ".join(map(str, ids)), HEAD + TOWER_ENTER.rstrip()]
    for i, tid in enumerate(ids):
        p = "k%03d" % tid
        if i:
            out.append("unpin")
            out.append("sb2w16 CE0 1")
            out.append("sb2w16 CB2 1")
        out.append(pinline(tid))
        if i:
            out.append("pick 0")
        out.append("drivex %s_in battle 30 9000" % p)
        out.append("oppname")
        out.append(("bwinsw %s_b" if tid in WIDE else "bwinr %s_b") % p)
        out.append("drivex %s_after menu 30 9000" % p)
    out.append("unpin")
    return "\n".join(out) + "\n"


def main():
    os.makedirs(OUT, exist_ok=True)
    for n, rng in enumerate(DOME_TOURS):
        with open(os.path.join(OUT, "r7r_dome_%d.txt" % n), "w") as fh:
            fh.write(dome(n, list(rng)))
    ids = WIDE + [t for t in CLASS_REPS if t not in WIDE]
    per = -(-len(ids) // TOWER_TOURS)
    for n in range(TOWER_TOURS):
        part = ids[n * per:(n + 1) * per]
        if part:
            with open(os.path.join(OUT, "r7r_tower_%d.txt" % n), "w") as fh:
                fh.write(tower(n, part))
    print("wrote", sorted(os.listdir(OUT)))


if __name__ == "__main__":
    main()
