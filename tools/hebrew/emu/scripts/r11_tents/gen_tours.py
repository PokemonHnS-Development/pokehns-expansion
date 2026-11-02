#!/usr/bin/env python3
"""Write the r11 Battle Tent roster tours (tours/r11_tents/r11t_*.txt).

  r11t_slateport.txt   Slateport tent (Factory rules): lobby, save, three rentals, then for every
                       trainer 0-29 of gSlateportBattleTentTrainers: reload the state taken after the
                       rental, pin TRAINER_BATTLE_PARAM.opponentA (tentpin), the battle room up to
                       the battle, the battle (intro, send-outs, defeat line), the room after it.
  r11t_verdanturf.txt  Verdanturf tent (Palace rules), same per trainer (the state is taken after
                       the challenge save; the Pokemon pick their own moves: tentwin -> bpalace).
  r11t_fallarbor.txt   Fallarbor tent (Arena rules), same, plus two lost battles (the trainer with
                       the widest class + name and the one with the longest name) for the
                       referee's 'the winner is <name>' line (fallarbortent_getopponentname).
Run:  python3 gen_tours.py      (paths are relative to this file)
"""
import os

HERE = os.path.dirname(os.path.abspath(__file__))
OUT = os.path.join(HERE, "..", "..", "tours", "r11_tents")

HEAD = """start saves/r11/tents_withdraw/tent_base.sav
include ../../scripts/continue.txt
"""

ENTER3 = "include ../../scripts/r2_battle_frontier_facilities/_bf_enter3.txt"

LOBBY = {
    "slateport": """warptoloose MAP_SLATEPORT_CITY_BATTLE_TENT_LOBBY_HNS 6 6
waitnotask Task_MapNamePopUpWindow 600
face UP
snap sl_lobby
tap A 0
drive sl_in menu
pick 0
drive sl_save menu 10
pick 0
saveyes
fastbattles off
drive sl_go cb2:CB2_SelectScreen 30 9000
waitquiet
60 -
snap sl_rent_01
tap A 30
tap DOWN 10
tap A 40
tap RIGHT 20
tap A 30
tap DOWN 10
tap A 40
tap RIGHT 20
tap A 30
tap DOWN 10
tap A 40
snap sl_rent_confirm
tap A 40
waitcb2x CB2_Overworld 3000
tstate save go""",
    "verdanturf": """warptoloose MAP_VERDANTURF_TOWN_BATTLE_TENT_LOBBY_HNS 6 6
waitnotask Task_MapNamePopUpWindow 600
face UP
snap ve_lobby
tap A 0
drive ve_in menu
pick 0
drive ve_sel task:Task_HandleChooseMonInput 20
%s
drive ve_save menu 10
pick 0
saveyes
fastbattles off
tstate save go""" % ENTER3,
    "fallarbor": """warptoloose MAP_FALLARBOR_TOWN_BATTLE_TENT_LOBBY_HNS 6 6
waitnotask Task_MapNamePopUpWindow 600
face UP
snap fa_lobby
tap A 0
drive fa_in menu
pick 0
drive fa_sel task:Task_HandleChooseMonInput 20
%s
drive fa_save menu 10
pick 0
saveyes
fastbattles off
tstate save go""" % ENTER3,
}
LETTER = {"slateport": "s", "verdanturf": "v", "fallarbor": "f"}
LOSSES = {"fallarbor": [1, 9]}      # RUIN MANIAC JAVIER (widest), CAMPER JAMESON (7 letters)


def battle(p, tid, first):
    out = []
    if not first:
        out.append("tstate load go")
    out += ["tentpin %d" % tid,
            "drivex %s_in battle 30 9000" % p,
            "tentlog %s_in" % p,
            "oppname",
            "tentwin %s_b" % p,
            "drivex %s_after menu 30 9000" % p,
            "unpin"]
    return out


def lost(p, tid):
    return ["tstate load go",
            "tentpin %d" % tid,
            "drivex %s_in battle 30 9000" % p,
            "tentlog %s_in" % p,
            "blose %s_b" % p,
            "drivex %s_after free 30 12000" % p,
            "unpin"]


def main():
    os.makedirs(OUT, exist_ok=True)
    for tent in ("slateport", "verdanturf", "fallarbor"):
        lines = ["# r11 tents: %s Battle Tent, trainers 0-29 (src/data/battle_frontier/battle_tent.h), "
                 "one pinned battle each from the state taken after entering" % tent.capitalize(),
                 HEAD + LOBBY[tent]]
        for tid in range(30):
            lines.append("# trainer %d" % tid)
            lines += battle("%s%02d" % (LETTER[tent], tid), tid, tid == 0)
        for tid in LOSSES.get(tent, []):
            lines.append("# trainer %d, lost" % tid)
            lines += lost("%s%02d_lost" % (LETTER[tent], tid), tid)
        with open(os.path.join(OUT, "r11t_%s.txt" % tent), "w") as fh:
            fh.write("\n".join(lines) + "\n")
    print("wrote", sorted(os.listdir(OUT)))


if __name__ == "__main__":
    main()
