#!/usr/bin/env python3
"""Write the r11 gym tours (tours/r11_leaders/g_*.txt): for every H&S gym, from the save a player
has after that gym's badge, the gym statue, the gym guide and the leader, each talked to
once more after the badge (the script's post-badge branch). Leader, guide and statue tiles are
the object_events / bg_events of data/maps/<Gym>/map.json; local ids are 1-based indexes.

    gen_tours.py SRC_TREE OUT_DIR
"""
import json
import os
import sys

# (tour, map dir, save, leader script suffix, extra setup line or None)
GYMS = [
    ("gj1_violet", "VioletCity_Gym_hns", "ladder4_league", "Falkner"),
    ("gj2_azalea", "AzaleaTown_Gym_hns", "ladder4_league", "Bugsy"),
    ("gj3_goldenrod", "GoldenrodCity_Gym_hns", "ladder4_league", "Whitney"),
    ("gj4_ecruteak", "EcruteakCity_Gym_hns", "ladder4_league", "Morty"),
    ("gj5_cianwood", "CianwoodGym_hns", "ladder4_league", "Chuck"),
    ("gj6_olivine", "OlivineCity_Gym_hns", "ladder4_league", "Jasmine"),
    ("gj7_mahogany", "MahoganyTown_Gym_hns", "ladder4_league", "Pryce"),
    ("gj8_blackthorn", "BlackthornCity_Gym_hns", "ladder4_league", "Clair"),
    ("gk1_pewter", "PewterCity_Gym_hns", "ladder6_postgame", "Brock"),
    ("gk2_cerulean", "CeruleanCity_Gym_hns", "ladder6_postgame", "Misty"),
    ("gk3_vermilion", "VermilionCity_Gym_hns", "ladder6_postgame", "Surge"),
    ("gk4_celadon", "CeladonCity_Gym_hns", "ladder6_postgame", "Erika"),
    ("gk5_fuchsia", "FuchsiaCity_Gym_hns", "ladder6_postgame", "_EventScript_Janine"),
    ("gk6_saffron", "SaffronCity_Gym_hns", "ladder6_postgame", "Sabrina"),
    ("gk7_seafoam", "SeafoamIslands_Gym_hns", "ladder6_postgame", "Blaine"),
    ("gk8_viridian", "ViridianCity_Gym_hns", "ladder6_postgame", "Blue"),
]


def main(src, out):
    for tour, mapdir, save, leader in GYMS:
        m = json.load(open(os.path.join(src, "data", "maps", mapdir, "map.json")))
        mapid = m["id"]
        objs = m["object_events"]
        lead = [(i + 1, o) for i, o in enumerate(objs) if o["script"].endswith(leader)]
        guide = [(i + 1, o) for i, o in enumerate(objs) if "GYM_GUY" in o["graphics_id"]]
        statues = [b for b in m["bg_events"] if "Statue" in (b.get("script") or "")]
        lid, lo = lead[0]
        p = tour.split("_")[0]
        lines = [
            "# r11 (gen_tours.py): %s after its badge, on %s. Statue %s, guide %s, leader %s (%s)."
            % (mapid, save, statues[0]["script"], guide[0][1]["script"] if guide else "none",
               lo["script"], "data/maps/%s/scripts.inc" % mapdir),
            "start saves/%s.sav" % save,
            "include _base.txt",
        ]
        s = statues[0]
        lines += ["warpto %s %d %d" % (mapid, s["x"], s["y"] + 1), "face UP", "snap %s_room" % p,
                  "talkdir %s_statue UP" % p]
        if guide:
            gid, go = guide[0]
            lines += ["approach %d" % gid, "tap A 4", "drive %s_guide" % p]
            if "Seafom" in go["script"]:          # GymGuideWin, then GymGuideWin2 (FLAG_TEMP_2)
                lines += ["approach %d" % gid, "tap A 4", "drive %s_guide2" % p]
        lines += ["warpto %s %d %d" % (mapid, lo["x"], lo["y"] + 1), "face UP",
                  "snap %s_leader_room" % p, "talkdir %s_leader UP" % p,
                  "talkdir %s_leader_again UP" % p]
        with open(os.path.join(out, tour + ".txt"), "w") as fh:
            fh.write("\n".join(lines) + "\n")
        print("wrote %s.txt (leader %d at %d,%d)" % (tour, lid, lo["x"], lo["y"]))


if __name__ == "__main__":
    main(sys.argv[1], sys.argv[2])
