#!/usr/bin/env python3
"""Write the r10 travel tours (tours/r10_bridges/*.txt) from the lists below.

  t_<map>.txt   a town or city: pop-up, every sign, NPC and furniture on the street, then every
                building (houses, shops, Pokemon Center), once each
  r_<map>.txt   a route: the same; the bridges are routes (Route 12, 24, 26, 36, 45, 47, 50 ...)
  g_<map>.txt   a gate between routes and towns, a station or a port: guards, signs, furniture

Johto maps start from ladder 4 (after the League), Kanto, the islands and the post-game maps from
ladder 6. Run from anywhere:  python3 gen_tours.py
"""
import os

HERE = os.path.dirname(os.path.abspath(__file__))
OUT = os.path.join(HERE, "..", "..", "tours", "r10_bridges")

JOHTO_TOWNS = ["NEW_BARK_TOWN", "CHERRYGROVE_CITY", "VIOLET_CITY", "AZALEA_TOWN", "GOLDENROD_CITY",
               "ECRUTEAK_CITY", "OLIVINE_CITY", "CIANWOOD_CITY", "MAHOGANYTOWN", "LAKE_OF_RAGE",
               "BLACKTHORN_CITY"]
KANTO_TOWNS = ["PALLET_TOWN", "VIRIDIAN_CITY", "PEWTER_CITY", "CERULEAN_CITY", "VERMILION_CITY",
               "LAVENDER_TOWN", "CELADON_CITY", "SAFFRON_CITY", "FUCHSIA_CITY", "CINNABAR_ISLAND",
               "INDIGO_PLATEAU", "MT_SILVER_OUTSIDE"]
POSTGAME_TOWNS = ["NEW_SINJOH", "MELEMELE_ISLE", "AKALA_ISLE", "ULAULA_ISLE", "PONI_ISLE"]
JOHTO_ROUTES = ["ROUTE%d" % n for n in range(29, 47)] + ["ROUTE26", "ROUTE27", "ROUTE28"]
KANTO_ROUTES = ["ROUTE%d" % n for n in range(1, 26) if n != 26] + ["ROUTE26NORTH"] + \
               ["ROUTE%d" % n for n in range(47, 51)]
JOHTO_GATES = ["GATE_AZALEA_TOWN_ILEX_FOREST", "GATE_ECRUTEAK_CITY_ROUTE38", "GATE_ECRUTEAK_CITY_ROUTE42",
               "GATE_GOLDENROD_CITY_ROUTE35", "GATE_ILEX_FOREST_ROUTE34", "GATE_MAHOGANY_TOWN_ROUTE43",
               "GATE_NATIONAL_PARK", "GATE_ROUTE29_ROUTE46", "GATE_ROUTE31_VIOLET_CITY", "GATE_ROUTE43",
               "GATE_RUINS_OF_ALPH_ROUTE32", "GATE_RUINS_OF_ALPH_ROUTE36", "GATE_ROUTE40_TRAINER_HILL_COURTYARD",
               "GOLDENROD_CITY_TRAIN_STATION", "OLIVINE_CITY_PORT_INSIDE", "OLIVINE_CITY_PORT_OUTSIDE",
               "CLIFF_EDGE_GATE"]
KANTO_GATES = ["GATE_CELADON_CITY_ROUTE16", "GATE_FUCHSIA_CITY_ROUTE18", "GATE_ROUTE2_VIRIDIAN_FOREST",
               "GATE_ROUTE2", "GATE_SAFFRON_CITY_ROUTE5", "GATE_SAFFRON_CITY_ROUTE6", "GATE_SAFFRON_CITY_ROUTE7",
               "GATE_SAFFRON_CITY_ROUTE8", "GATE_VIRIDIAN_FOREST_ROUTE2", "FUCHSIA_CITY_ROUTE15_GATE",
               "FUCHSIA_ROUTE19GATE", "RECEPTION_GATE", "ROUTE5_TUNNEL_ENTRANCE", "ROUTE6_TUNNEL_ENTRANCE",
               "ROUTE7_TUNNEL_ENTRANCE", "ROUTE8_TUNNEL_ENTRANCE", "SAFARI_ZONE_GATE",
               "SAFFRON_CITY_TRAIN_STATION", "VERMILION_CITY_PORT_INSIDE", "VERMILION_CITY_PORT_OUTSIDE",
               "ROUTE10_POWER_PLANT_ENTRANCE"]


def write(name, save, mapname, op):
    with open(os.path.join(OUT, name + ".txt"), "w") as fh:
        fh.write("# r10 travel (gen_tours.py): %s on %s\n" % (mapname, save))
        fh.write("start saves/%s.sav\ninclude _base.txt\nvisit MAP_%s_HNS\n%s\n" % (save, mapname, op))


def main():
    os.makedirs(OUT, exist_ok=True)
    n = 0
    for lst, save, kind, op in ((JOHTO_TOWNS, "tr_l4", "t", "town"), (KANTO_TOWNS, "tr_l6", "t", "town"),
                                (POSTGAME_TOWNS, "tr_l6", "t", "town"), (JOHTO_ROUTES, "tr_l4", "r", "town"),
                                (KANTO_ROUTES, "tr_l6", "r", "town"), (JOHTO_GATES, "tr_l4", "g", "area"),
                                (KANTO_GATES, "tr_l6", "g", "area")):
        for m in lst:
            write("%s_%s" % (kind, m.lower()), save, m, op)
            n += 1
    print("%d tours in %s" % (n, os.path.normpath(OUT)))


if __name__ == "__main__":
    main()
