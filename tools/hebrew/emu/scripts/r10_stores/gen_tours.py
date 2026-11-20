#!/usr/bin/env python3
"""Write the r10 store tours (tours/r10_stores/*.txt): every shop a player can use, walked to and
talked to on foot, with the BUY list scrolled to its end (each row's description), the price of
every row asked for (quantity window with the total, the price question with YES/NO, sold-out
rows), the purchase flows (Premier Ball bonus, not enough money, no room, the 7-digit money box),
the SELL flow (every pocket, quantity and price, YES/NO, sold, can't-sell items), the badge-count
stock of the shared mart list (normal and Pokemon Center challenge), and the other sellers
(vending machines, Game Corner counters, BP exchange counters, Kurt, NPC sellers).

    python3 gen_tours.py            rewrite ../../tours/r10_stores/[a-z]*.txt (keeps _base.txt)

The shop list comes from shops.py (every map object whose script reaches pokemart / a Create*Shop
special / a money box), checked by hand against data/maps/*_hns/map.json. Every tour starts from
saves/st_l6.sav (a copy of ladder6_postgame: 16 badges, P351300, post-game).
"""
import os

HERE = os.path.dirname(os.path.abspath(__file__))
OUT = os.path.normpath(os.path.join(HERE, "..", "..", "tours", "r10_stores"))

HEAD = "start saves/st_l6.sav\ninclude _base.txt\n"

# (tour, map, clerk x, clerk y, ask every row?, comment); the mart clerk's object event position
MARTS = [
    ("m01_cherrygrove", "MAP_CHERRYGROVE_CITY_MART_HNS", 2, 3, False, "Cherrygrove_Pokemart_EventScript_Clerk: badge list ('pokemart 0')"),
    ("m02_violet", "MAP_VIOLET_CITY_MART_HNS", 2, 3, True, "VioletCity_Mart_EventScript_Clerk: badge list, 16 badges = the 8-badge list"),
    ("m03_azalea", "MAP_AZALEA_TOWN_MART_HNS", 2, 3, False, "shared Cherrygrove clerk"),
    ("m04_ecruteak", "MAP_ECRUTEAK_CITY_MART_HNS", 2, 3, False, "shared Cherrygrove clerk"),
    ("m05_olivine", "MAP_OLIVINE_CITY_MART_HNS", 2, 3, False, "shared Cherrygrove clerk"),
    ("m06_blackthorn", "MAP_BLACKTHORN_CITY_MART_HNS", 2, 3, False, "shared Cherrygrove clerk"),
    ("m07_viridian", "MAP_VIRIDIAN_CITY_MART_HNS", 2, 3, False, "shared Cherrygrove clerk"),
    ("m08_pewter", "MAP_PEWTER_CITY_MART_HNS", 2, 3, False, "shared Cherrygrove clerk"),
    ("m09_cerulean", "MAP_CERULEAN_CITY_MART_HNS", 2, 3, False, "shared Cherrygrove clerk"),
    ("m10_vermilion", "MAP_VERMILION_CITY_MART_HNS", 2, 3, False, "shared Cherrygrove clerk"),
    ("m11_lavender", "MAP_LAVENDER_TOWN_MART_HNS", 2, 3, False, "shared Cherrygrove clerk"),
    ("m12_saffron", "MAP_SAFFRON_CITY_MART_HNS", 2, 3, False, "shared Cherrygrove clerk"),
    ("m13_fuchsia", "MAP_FUCHSIA_CITY_MART_HNS", 2, 3, False, "shared Cherrygrove clerk"),
    ("m14_cel2", "MAP_CELADON_CITY_DEPARTMENT_STORE_2F_HNS", 12, 11, False, "Celadon 2F: VioletCity_Mart_EventScript_Clerk (badge list)"),
    ("m15_cel3", "MAP_CELADON_CITY_DEPARTMENT_STORE_3F_HNS", 6, 8, True, "Celadon 3F TMs (CeladonDept3_Pokemart)"),
    ("m16_cel4", "MAP_CELADON_CITY_DEPARTMENT_STORE_4F_HNS", 3, 13, True, "Celadon 4F vitamins (LilycoveCity_DepartmentStore_3F_Pokemart_Vitamins)"),
    ("m17_gr2", "MAP_GOLDENROD_CITY_DEPARTMENT_STORE_2F_HNS", 14, 11, True, "Goldenrod 2F (GoldenrodDeptStore2_Pokemart)"),
    ("m18_gr3", "MAP_GOLDENROD_CITY_DEPARTMENT_STORE_3F_HNS", 15, 5, True, "Goldenrod 3F X items"),
    ("m19_gr4", "MAP_GOLDENROD_CITY_DEPARTMENT_STORE_4F_HNS", 24, 11, True, "Goldenrod 4F vitamins"),
    ("m20_gr5", "MAP_GOLDENROD_CITY_DEPARTMENT_STORE_5F_HNS", 17, 11, True, "Goldenrod 5F TMs (owned TMs read SOLD OUT)"),
    ("m21_flower", "MAP_GOLDENROD_CITY_FLOWER_SHOP_HNS", 8, 4, True, "Goldenrod Flower Shop mints"),
    ("m22_herb", "MAP_GOLDENROD_CITY_UNDERGROUND_TUNNEL_HNS", 6, 24, True, "Goldenrod Underground herb shop (LavaridgeTown_HerbShop_EventScript_Clerk)"),
    ("m23_mahogany", "MAP_MAHOGANY_TOWN_SHOP_HNS", 2, 5, True, "Mahogany shop granny (VAR_MAHOGANY_TOWN_STATE >= 14)"),
    ("m24_mtmoon", "MAP_MT_MOON_SHOP_HNS", 2, 4, True, "Mt. Moon gift shop"),
    ("m25_safinc", "MAP_SAFARI_ZONE_GATE_HNS", 11, 21, True, "Safari Zone Gate incense clerk"),
    ("m26_safvit", "MAP_SAFARI_ZONE_GATE_HNS", 20, 21, True, "Safari Zone Gate vitamin guru"),
    ("m27_sjtravel", "MAP_NEW_SINJOH_HNS", 40, 10, True, "New Sinjoh travel shop"),
    ("m28_sjcafe", "MAP_NEW_SINJOH_HOUSE4_HNS", 16, 7, True, "New Sinjoh cafe"),
    ("m29_alola", "MAP_MELEMELE_HOUSE_2_HNS", 5, 9, True, "Melemele (Alola) shop"),
    ("m30_bfmart", "MAP_BATTLE_FRONTIER_MART_HNS", 1, 3, True, "Battle Frontier Mart"),
    ("m31_thbasic", "MAP_TRAINER_HILL_ENTRANCE_HNS", 14, 9, True, "Trainer Hill entrance, basic list"),
    ("m32_thbadge", "MAP_TRAINER_HILL_ENTRANCE_HNS", 12, 9, False, "Trainer Hill entrance, badge list ('pokemart 0')"),
    ("m33_indigo", "MAP_INDIGO_PLATEAU_POKEMON_CENTER_HNS", 10, 10, True, "Indigo Plateau Pokemon Center mart (BattleFrontier_Mart_Pokemart)"),
]

# BP counters: (tour, map, x, y, ask every row?, comment)
BP = [
    ("p01_bf_decor1", "MAP_BATTLE_FRONTIER_EXCHANGE_SERVICE_CORNER_HNS", 4, 4, True, "CreateBPDecorShop1"),
    ("p02_bf_decor2", "MAP_BATTLE_FRONTIER_EXCHANGE_SERVICE_CORNER_HNS", 5, 5, True, "CreateBPDecorShop2"),
    ("p03_bf_balls", "MAP_BATTLE_FRONTIER_EXCHANGE_SERVICE_CORNER_HNS", 7, 5, True, "CreateBPPokeBallShop"),
    ("p04_bf_vitamins", "MAP_BATTLE_FRONTIER_EXCHANGE_SERVICE_CORNER_HNS", 9, 5, True, "CreateBPVitaminShop"),
    ("p05_bf_hold1", "MAP_BATTLE_FRONTIER_EXCHANGE_SERVICE_CORNER_HNS", 10, 4, True, "CreateBPHoldItemShop"),
    ("p06_bf_hold2", "MAP_BATTLE_FRONTIER_EXCHANGE_SERVICE_CORNER_HNS", 10, 3, True, "CreateBPHoldItemShop2"),
    ("p07_bf_power", "MAP_BATTLE_FRONTIER_EXCHANGE_SERVICE_CORNER_HNS", 4, 3, True, "CreateBPPowerShop"),
    ("p11_vip_decor1", "MAP_SAFFRON_CITY_FIGHTING_DOJO_VIP_HNS", 10, 5, False, "CreateBPDecorShop1"),
    ("p12_vip_decor2", "MAP_SAFFRON_CITY_FIGHTING_DOJO_VIP_HNS", 7, 5, False, "CreateBPDecorShop2"),
    ("p13_vip_balls", "MAP_SAFFRON_CITY_FIGHTING_DOJO_VIP_HNS", 36, 5, False, "CreateBPPokeBallShop"),
    ("p14_vip_vitamins", "MAP_SAFFRON_CITY_FIGHTING_DOJO_VIP_HNS", 24, 5, False, "CreateBPVitaminShop"),
    ("p15_vip_hold1", "MAP_SAFFRON_CITY_FIGHTING_DOJO_VIP_HNS", 30, 5, False, "CreateBPHoldItemShop"),
    ("p16_vip_hold2", "MAP_SAFFRON_CITY_FIGHTING_DOJO_VIP_HNS", 33, 5, False, "CreateBPHoldItemShop2"),
    ("p17_vip_power", "MAP_SAFFRON_CITY_FIGHTING_DOJO_VIP_HNS", 20, 5, False, "CreateBPPowerShop"),
    ("p21_th_vitamins", "MAP_TRAINER_HILL_COURTYARD_HNS", 15, 29, False, "TrainerHill_Courtyard vitamin clerk"),
    ("p22_th_hold", "MAP_TRAINER_HILL_COURTYARD_HNS", 16, 29, False, "TrainerHill_Courtyard hold item clerk"),
]

# vending machines: (tour, map, x, y of one machine sign, full flows?)
VENDING = [
    ("v01_gr2", "MAP_GOLDENROD_CITY_DEPARTMENT_STORE_2F_HNS", 12, 5, True),
    ("v02_gr4", "MAP_GOLDENROD_CITY_DEPARTMENT_STORE_4F_HNS", 13, 5, False),
    ("v03_gr6", "MAP_GOLDENROD_CITY_DEPARTMENT_STORE_6F_HNS", 13, 5, False),
    ("v04_gr7", "MAP_GOLDENROD_CITY_DEPARTMENT_STORE_7F_HNS", 11, 5, False),
    ("v05_gr7n", "MAP_GOLDENROD_CITY_DEPARTMENT_STORE_7FNIGHT_HNS", 11, 5, False),
    ("v06_celroof", "MAP_CELADON_CITY_DEPARTMENT_STORE_ROOF_DAY_HNS", 10, 3, True),
    ("v07_celroofn", "MAP_CELADON_CITY_DEPARTMENT_STORE_ROOF_NIGHT_HNS", 11, 3, False),
]


def write(name, body, comment):
    with open(os.path.join(OUT, name + ".txt"), "w") as fh:
        fh.write("# " + comment.replace("\n", "\n# ") + "\n" + body)


def shop_visit(p, mapid, x, y, each, pre=""):
    s = pre + "visit %s\nclerk %d %d %s_hi\nbuyopen %s_buy\nlistshots %s_list\n" % (mapid, x, y, p, p, p)
    if each:
        s += "buyeach %s_ask\n" % p
    s += "buyclose %s_menu\nshopquit %s_bye\n" % (p, p)
    return s


def main():
    os.makedirs(OUT, exist_ok=True)
    for old in os.listdir(OUT):
        if old.endswith(".txt") and not old.startswith("_"):
            os.remove(os.path.join(OUT, old))

    # ---- every mart: walk in, talk to the clerk, list, every row asked for, leave
    for name, mapid, x, y, each, cm in MARTS:
        write(name, HEAD + shop_visit(name[:3], mapid, x, y, each), "%s (%s)." % (cm, mapid))
    write("m34_safincf", HEAD + "ev setflag FLAG_FINITE_TMS; end\n"
          + shop_visit("m34", "MAP_SAFARI_ZONE_GATE_HNS", 11, 21, True),
          "Safari Zone Gate incense clerk with FLAG_FINITE_TMS (SafariZoneGate_EventScript_IncenseClerkFinite).")

    # ---- the badge list as the badge count rises (src/shop.c SetShopItemsForSale: 0..8 badges,
    # 8+ = the 8-badge list), normal and under the Pokemon Center challenge
    body = HEAD + "visit MAP_VIOLET_CITY_MART_HNS\n"
    for n in range(0, 9):
        q = "b%d" % n
        body += "setbadges %d\nclerk 2 3 %s_hi\nbuyopen %s_buy\nlistshots %s_list\nbuyclose %s_menu\nshopquit %s_bye\n" % (
            n, q, q, q, q, q)
    write("b01_badges", body, "Violet Mart badge list ('pokemart 0') with 0..8 badges.")
    body = HEAD + "setpcchallenge 1\nvisit MAP_VIOLET_CITY_MART_HNS\n"
    for n in range(0, 9):
        q = "c%d" % n
        body += "setbadges %d\nclerk 2 3 %s_hi\nbuyopen %s_buy\nlistshots %s_list\n" % (n, q, q, q)
        if n == 8:
            body += "buyeach %s_ask\n" % q
        body += "buyclose %s_menu\nshopquit %s_bye\n" % (q, q)
    write("b02_pcchallenge", body, "Violet Mart badge list under the Pokemon Center challenge (sShopInventories_PC) with 0..8 badges.")
    write("b03_cherry_early", HEAD + "ev setvar VAR_NEWBARK_TOWN_STATE, 4; end\n"
          + shop_visit("b03", "MAP_CHERRYGROVE_CITY_MART_HNS", 2, 3, True),
          "Cherrygrove Mart before VAR_NEWBARK_TOWN_STATE 5: Cherrygrove_Pokemart_Pokemart (POTION, ANTIDOTE).")

    # ---- buy flows (Violet Mart, 8-badge list: 0 POKE BALL, 1 GREAT BALL, 2 ULTRA BALL, 7 FULL RESTORE)
    body = HEAD + "visit MAP_VIOLET_CITY_MART_HNS\nclerk 2 3 f1_hi\nbuyopen f1_buy\n"
    body += "buy f1_pb10 0 9 YES\nbuy f1_pb20 0 19 YES\nbuy f1_gb10 1 9 YES\nbuy f1_ub30 2 29 YES\nbuy f1_pb9 0 8 YES\n"
    body += "buy f1_pot2 3 1 YES\nbuymax f1_frmax 7 NO\nbuyclose f1_menu\nshopquit f1_bye\n"
    body += "setmoney 9999999\nclerk 2 3 f2_hi\nbuyopen f2_buy\nbuymax f2_frmax 7 YES\nbuyclose f2_menu\nshopquit f2_bye\n"
    body += "setmoney 150\nclerk 2 3 f3_hi\nbuyopen f3_buy\nbuy f3_pb 0 0 YES\nbuy f3_gb 1 0 YES\nbuy f3_fr 7 0 YES\nbuyclose f3_menu\nshopquit f3_bye\n"
    body += ("setmoney 351300\nfillfull POCKET_POKE_BALLS ITEM_MASTER_BALL 999\nfillfull POCKET_MEDICINE ITEM_MAX_ELIXIR 999\n"
             "clerk 2 3 f4_hi\nbuyopen f4_buy\nbuy f4_pb 0 0 YES\nbuy f4_pot 3 0 YES\nbuyclose f4_menu\nshopquit f4_bye\n")
    write("f01_buyflows", body, "Violet Mart buy flows: 10/20 POKE BALL (1/2 Premier Balls), 10 GREAT BALL and 30 ULTRA BALL\n"
          "(I_PREMIER_BALL_BONUS GEN_LATEST: any ball), 9 (no bonus), 2 POTION, FULL RESTORE at the max quantity\n"
          "(NO, then YES with P9999999), not enough money (P150), no room (balls and medicine pockets full).")

    # ---- sell flows
    body = HEAD + ("setpocket POCKET_ITEMS ITEM_NUGGET:3 ITEM_BIG_NUGGET:1 ITEM_TINY_MUSHROOM:12 ITEM_STAR_PIECE:2 "
                   "ITEM_EXP_SHARE:1 ITEM_HEART_SCALE:5 ITEM_RARE_BONE:1\n")
    body += "visit MAP_VIOLET_CITY_MART_HNS\nclerk 2 3 s1_hi\n"
    body += "sellopen s1_bag POCKET_ITEMS\nsellpockets s1_pk\nsellclose s1_menu\n"
    body += "sellopen s2_bag POCKET_ITEMS ITEM_NUGGET\nsell s2 1 YES\nsellclose s2_menu\n"
    body += "sellopen s3_bag POCKET_ITEMS ITEM_BIG_NUGGET\nsell s3 0 NO\nsellclose s3_menu\n"
    body += "sellopen s4_bag POCKET_ITEMS ITEM_TINY_MUSHROOM\nsell s4 11 YES\nsellclose s4_menu\n"
    body += "sellopen s5_bag POCKET_ITEMS ITEM_EXP_SHARE\nsell s5 0 YES\nsellclose s5_menu\n"
    body += "sellopen s6_bag POCKET_KEY_ITEMS\nsell s6 0 YES\nsellclose s6_menu\n"
    body += "sellopen s7_bag POCKET_TM_HM\nsell s7 0 YES\nsellclose s7_menu\n"
    body += "sellopen s8_bag POCKET_BERRIES\nsell s8 0 YES\nsellclose s8_menu\n"
    body += "sellopen s9_bag POCKET_POKE_BALLS\nsell s9 4 NO\nsellclose s9_menu\n"
    body += "sellopen s10_bag POCKET_MEDICINE\nsell s10 0 YES\nsellclose s10_menu\n"
    body += "setmoney 9999000\nsellopen s11_bag POCKET_ITEMS ITEM_STAR_PIECE\nsell s11 1 YES\nsellclose s11_menu\n"
    body += "shopquit s_bye\n"
    write("f02_sellflows", body, "Violet Mart SELL: every pocket in sell mode; NUGGET x2 YES, BIG NUGGET NO, TINY MUSHROOM x12 YES,\n"
          "EXP SHARE (held item), a key item and a TM (can't sell: price 0 or important,\n"
          "src/item_menu.c Task_ItemContext_Sell), a berry, POKE BALL x5 NO, a medicine, and with P9999000 a\n"
          "STAR PIECE (the money box near the cap).")

    # ---- BP counters
    for name, mapid, x, y, each, cm in BP:
        p = name[:3]
        pre = "setbp 9999\n"
        s = HEAD + pre + "visit %s\nclerk %d %d %s_hi\nbuywait %s_buy\nlistshots %s_list\n" % (mapid, x, y, p, p, p)
        if each:
            s += "buyeach %s_ask\nbuy %s_b0 0 1 YES\n" % (p, p)
            s += "setbp 0\nbuy %s_nobp 1 0 YES\n" % p
        s += "press B\nchat %s_bye\n" % p
        write(name, s, "%s (%s)%s." % (cm, mapid, ": every row asked, one purchase, not enough BP" if each else ""))

    # ---- Kurt (MART_TYPE_KURT: apricorn berries pay for the balls)
    body = HEAD + ("setpocket POCKET_BERRIES ITEM_PECHA_BERRY:3 ITEM_RAWST_BERRY:1 ITEM_CHERI_BERRY:5 ITEM_ORAN_BERRY:2 "
                   "ITEM_CHESTO_BERRY:1 ITEM_PERSIM_BERRY:4\n")
    body += "visit MAP_AZALEA_TOWN_KURTS_HOUSE_HNS\nclerk 15 3 k_hi\nbuywait k_buy\nlistshots k_list\nbuyeach k_ask\n"
    body += "press B\nchat k_end\n"
    write("k01_kurt", body, "Kurt's apricorn ball shop (CreateKurtBallShop): list, every row asked (ASPEAR missing = 'no apricorn').")

    # ---- vending machines (GoldenrodDeptStore_EventScript_VendingMachine, the Celadon roof
    # LilycoveCity_DepartmentStoreRooftop_EventScript_VendingMachine)
    for name, mapid, x, y, full in VENDING:
        p = name[:3]
        s = HEAD + "visit %s\nsignat %d %d UP %s_hi\nchat %s_fw A B\n" % (mapid, x, y, p, p)
        if full:
            s += "signat %d %d UP %s_hi2\nchat %s_sp d1 d2 B\n" % (x, y, p, p)
            s += "setmoney 100\nsignat %d %d UP %s_poor\nchat %s_poor2 d2\n" % (x, y, p, p)
            s += "setmoney 351300\nfillfull POCKET_MEDICINE ITEM_MAX_ELIXIR 999\nsignat %d %d UP %s_full\nchat %s_full2 A\n" % (x, y, p, p)
        write(name, s, "Vending machine on %s: money box + MULTI_VENDING_MACHINE, a drink bought%s." % (
            mapid, "; every drink, not enough money, bag full" if full else ""))
    # the 1/64 extra drink line, shown from RAM with the machine's own text
    write("v08_extra", HEAD + "visit MAP_GOLDENROD_CITY_DEPARTMENT_STORE_2F_HNS 12 6\n"
          "evtexts ITEM_SODA_POP GoldenrodDeptStore_EventScript_TryBuyDrink:1 GoldenrodDeptStore_EventScript_TryBuyDrink:3 "
          "LilycoveCity_DepartmentStoreRooftop_EventScript_TryBuyDrink:1 LilycoveCity_DepartmentStoreRooftop_EventScript_TryBuyDrink:3\n"
          "chat v08_x\n",
          "The extra-drink lines (random 64 == 0): the machines' own texts (1st and 3rd msgbox of each TryBuyDrink,\n"
          "read from the ROM) shown from an event script in RAM, Goldenrod then Celadon.")

    # ---- Game Corner counters
    for name, mapid in (("g01_gr", "MAP_GOLDENROD_CITY_GAME_CORNER_HNS"), ("g02_cel", "MAP_CELADON_CITY_GAME_CORNER_HNS")):
        p = name[:3]
        s = HEAD + "ev additem ITEM_COIN_CASE; end\nsetcoins 9000\nvisit %s\n" % mapid
        s += "clerk 3 2 %s_coin\nchat %s_c50 A\n" % (p, p)
        s += "clerk 3 2 %s_coinb\nchat %s_c500 d1\n" % (p, p)
        s += "clerk 16 2 %s_mon\nchat %s_mon1 A B\n" % (p, p)
        s += "clerk 18 2 %s_tm\nchat %s_tm1 A A\n" % (p, p)
        s += "clerk 18 2 %s_tmb\nchat %s_tm2 d3 B\n" % (p, p)
        s += "setcoins 10\nclerk 16 2 %s_monp\nchat %s_mon2 A A\n" % (p, p)
        write(name, s, "Game Corner on %s: coins clerk (buy 50 / 500), prize Pokemon menu, TM prize menu, buy,\nnot enough coins." % mapid)

    # ---- NPC sellers (money box + YES/NO)
    write("n01_ragecandy", HEAD + "visit MAP_MAHOGANYTOWN_HNS 31 11\nclerk 30 11 n01_hi\nchat n01_x\n",
          "Mahogany Rage Candy Bar merchant (MahoganyTown_EventScript_Merchant) in the post-game state (VAR_MAHOGANY_TOWN_STATE\n"
          "17: MerchantAfter); the selling branches were toured in r6.")
    write("n02_moomoo", HEAD + "visit MAP_ROUTE39_FARM_HOUSE_HNS\nclerk 4 4 n02_hi\nchat n02_yes A B\nclerk 4 4 n02_hi2\nchat n02_no B\n",
          "Route 39 farm house milk (Route39_FarmHouse_EventScript_FarmerM): YES, another? NO; then NO.")
    write("n02b_moomoo_sale", HEAD + "ev setvar VAR_ROUTE39_BARN, 5; end\nvisit MAP_ROUTE39_FARM_HOUSE_HNS\n"
          "clerk 4 4 n02b_hi\nchat n02b_yes A A B\nclerk 4 4 n02b_hi2\nchat n02b_no B\n"
          "setmoney 100\nclerk 4 4 n02b_poor\nchat n02b_poor2 A\n",
          "Route 39 farm house milk with VAR_ROUTE39_BARN 5 (the cow healed): YES, another YES, another NO; NO; not enough\n"
          "money (P100).")
    write("n03_sinjohmilk", HEAD + "visit MAP_NEW_SINJOH_HNS 40 14\nclerk 40 13 n03_hi\nchat n03_yes A B\n",
          "New Sinjoh milk man (NewSinjoh_MilkMan_EventScript_Seller): YES, then NO.")
    write("n04_safari_upgrade", HEAD + "visit MAP_FUCHSIA_CITY_SAFARI_ZONE_ENTRANCE_HNS\n"
          "ev setvar VAR_KANTO_SAFARI_ZONE_PROGRESS, 1; end\nclerk 2 10 n04_l1\nchat n04_l1y A\n"
          "clerk 2 10 n04_l2\nchat n04_l2y A\nclerk 2 10 n04_l2b\nchat n04_l2n B\n"
          "setmoney 9999999\nev setvar VAR_KANTO_SAFARI_ZONE_PROGRESS, 3; end\nclerk 2 10 n04_l3\nchat n04_l3y A\n"
          "clerk 2 10 n04_max\nchat n04_max2\n",
          "Fuchsia Safari Zone upgrade man (FuchsiaCity_SafariZoneEntrance_UpgradeGuy): level 1 YES (P200,000), level 2\n"
          "not enough money, level 2 NO, level 3 YES (P400,000), max level.")
    write("n05_haircut", HEAD + "visit MAP_GOLDENROD_CITY_UNDERGROUND_TUNNEL_HNS\nclerk 6 20 n05_old\nchat n05_old2 B\n"
          "",
          "Goldenrod Underground haircut brothers (GoldenrodUnderground_EventScript_Brother_Haircut1/2): the offer with the\n"
          "money box, NO (the YES branch opens the party menu; toured in r6). The younger brother is out at night only:\n"
          "n07_haircut_night, run with --rtc 1767304800 (22:00).")
    write("n07_haircut_night", HEAD + "visit MAP_GOLDENROD_CITY_UNDERGROUND_TUNNEL_HNS\nclerk 6 16 n07_young\nchat n07_young2 B\n",
          "Goldenrod Underground younger haircut brother (FLAG_NIGHT_POKEMON object, out at night): offer, NO.\n"
          "Run with --rtc 1767304800 (2026-01-01 22:00 UTC).")
    write("n06_bikeshops", HEAD + "visit MAP_GOLDENROD_CITY_BIKE_SHOP_HNS\nnpcs\nvisit MAP_CERULEAN_CITY_BIKE_SHOP_HNS\nnpcs\n",
          "Bike shops (Goldenrod, Cerulean): every NPC (no shop list; the Goldenrod clerk lends the BICYCLE).")


if __name__ == "__main__":
    main()
