#!/usr/bin/env python3
"""Write the r3_marts tours (tours/m*.txt): every mart list no earlier tour opened, scrolled row by
row with its description, plus the buy flows (SOLD OUT, an important TM, Premier Ball bonus, not
enough money, no room, space full) and the EXPENSIVE challenge (x5 / x10 / x50).

    python3 gen.py            rewrite tours/

Each tour starts from saves/ladder6_postgame_copy.sav (HNS_SAVES), CONTINUEs, adds money to
MAX_MONEY (include/money.h:4), warps next to the clerk and starts the clerk's own script from RAM.
The mart lists and clerk labels are in data/maps/<map>/scripts.inc; the badge list ('pokemart 0')
is sShopInventory_EightBadges (src/shop.c:546-567, 16 badges).
"""
import os

HERE = os.path.dirname(os.path.abspath(__file__))
OUT = os.path.join(HERE, "tours")

# key: (map, x, y, script) - x, y = a tile in front of the clerk (map.json object_events)
MARTS = {
    "gr2": ("MAP_GOLDENROD_CITY_DEPARTMENT_STORE_2F_HNS", 14, 13, "goto GoldenrodDeptStore2_EventScript_Clerk"),
    "gr3": ("MAP_GOLDENROD_CITY_DEPARTMENT_STORE_3F_HNS", 15, 7, "goto GoldenrodDeptStore3_EventScript_Clerk"),
    "gr4": ("MAP_GOLDENROD_CITY_DEPARTMENT_STORE_4F_HNS", 24, 13, "goto GoldenrodDeptStore4_EventScript_Clerk"),
    "gr5": ("MAP_GOLDENROD_CITY_DEPARTMENT_STORE_5F_HNS", 17, 13, "goto GoldenrodDeptStore5_EventScript_Clerk"),
    "cel3": ("MAP_CELADON_CITY_DEPARTMENT_STORE_3F_HNS", 6, 10, "goto CeladonDept3_EventScript_Clerk"),
    "flower": ("MAP_GOLDENROD_CITY_FLOWER_SHOP_HNS", 8, 6, "goto GoldenrodCity_FlowerShop_EventScript_MintClerk"),
    "mahog": ("MAP_MAHOGANY_TOWN_SHOP_HNS", 2, 7, "lock; faceplayer; goto MahoganyTown_Shop_EventScript_GrannyShop"),
    "mtmoon": ("MAP_MT_MOON_SHOP_HNS", 2, 6, "goto MtMoon_Shop_EventScript_Clerk"),
    "safinc": ("MAP_SAFARI_ZONE_GATE_HNS", 11, 23, "goto SafariZoneGate_EventScript_IncenseClerk"),
    "safincf": ("MAP_SAFARI_ZONE_GATE_HNS", 11, 23, "goto SafariZoneGate_EventScript_IncenseClerkFinite"),
    "safvit": ("MAP_SAFARI_ZONE_GATE_HNS", 20, 23, "goto SafariZoneGate_EventScript_VitaminGuru"),
    "sjtravel": ("MAP_NEW_SINJOH_HNS", 40, 12, "goto NewSinjoh_Script_TravelMart"),
    "sjcafe": ("MAP_NEW_SINJOH_HOUSE4_HNS", 16, 9, "goto NewSinjoh_Cafe_Script_Sister"),
    "alola": ("MAP_MELEMELE_HOUSE_2_HNS", 5, 11, "goto Alola_Pokemart_EventScript_Clerk"),
    "bfmart": ("MAP_BATTLE_FRONTIER_MART_HNS", 3, 5, "goto BattleFrontier_Mart_EventScript_Clerk_hns"),
    "thbasic": ("MAP_TRAINER_HILL_ENTRANCE_HNS", 14, 11, "goto TrainerHill_Entrance_hns_EventScript_Clerk"),
    "thbadge": ("MAP_TRAINER_HILL_ENTRANCE_HNS", 12, 11, "goto TrainerHill_Entrance_hns_EventScript_Clerk2"),
    "violet": ("MAP_VIOLET_CITY_MART_HNS", 2, 5, "goto VioletCity_Mart_EventScript_Clerk"),
}

HEAD = """start saves/ladder6_postgame_copy.sav
include ../../continue.txt
ev addmoney 9999999; end
"""


def open_mart(p, key, pre="", money=None):
    m, x, y, scr = MARTS[key]
    s = ""
    if money is not None:
        s += "setmoney %d\n" % money
    s += """warptoloose {m} {x} {y}
evstart {scr}
talk {p}_welcome 10 - Task_ShopMenu
waittaskx Task_ShopMenu 600
waitquiet
snap {p}_menu
tap A 0
waitcb2x CB2_BuyMenu 900
waittaskx Task_BuyMenu 900
waitquiet
""".format(m=m, x=x, y=y, scr=scr, p=p)
    return pre + s


def close_mart(p):
    return """press B
waitcb2x CB2_Overworld 900
waittaskx Task_ShopMenu 900
waitquiet
press B
talk {p}_bye 10 -
waitctl 900
""".format(p=p)


def reopen_buy():
    """From the shop menu after a B in the list: BUY again."""
    return """waitcb2x CB2_Overworld 900
waittaskx Task_ShopMenu 900
waitquiet
tap A 0
waitcb2x CB2_BuyMenu 900
waittaskx Task_BuyMenu 900
waitquiet
"""


def pick(p, row):
    """Cursor to ROW, A, and snap the message that follows (it waits for a key or goes on to
    the quantity window / YES-NO)."""
    return "listgo %d\ntap A 0\nsnap %s\n" % (row, p)


def qty(p, ups=0, max_=False):
    """In the quantity window: snap x1, optionally UP n times, or DOWN once (1 wraps to the max)."""
    s = "waittaskx Task_BuyHowManyDialogueHandleInput 600\nsnap %s_x1\n" % p
    for _ in range(ups):
        s += "press UP 2\n"
    if ups:
        s += "snap %s_x%d\n" % (p, ups + 1)
    if max_:
        s += "press DOWN 2\nsnap %s_xmax\n" % p
    return s


def confirm(p, yes=True):
    """A on the quantity window (or nothing, for an important item), snap the price line with
    YES/NO, then YES (A) or NO (B)."""
    s = "waittaskx Task_CallYesOrNoCallback 600\nwaitquiet\n10 -\nsnap %s_yesno\n" % p
    if yes:
        s += "tap A 0\nsnap %s_thanks\n" % p
    else:
        s += "tap B 0\nwaittaskx Task_BuyMenu 600\nwaitquiet\n"
    return s


def ack(p):
    """A on a message that waits for a key; snap the next screen (a Premier Ball line or the list)."""
    return "tap A 0\nsnap %s\n" % p


def back_to_list():
    return "waittaskx Task_BuyMenu 600\nwaitquiet\n"


def write(name, body, comment):
    with open(os.path.join(OUT, name + ".txt"), "w") as fh:
        fh.write("# " + comment.replace("\n", "\n# ") + "\n" + body)


def list_tour(n, key, comment, extra="", money=None):
    p = "%s_%s" % (n, key)
    body = HEAD + open_mart(p, key, money=money) + "listshots %s\n" % p + extra + close_mart(p)
    write(p, body, comment)


def main():
    os.makedirs(OUT, exist_ok=True)
    for old in os.listdir(OUT):
        if old.endswith(".txt"):
            os.remove(os.path.join(OUT, old))
    # ---- saves for later runs (copied to saves_screens/r3_marts by hand): money at MAX_MONEY, and the
    # EXPENSIVE challenge at x5 / x10 / x50 written into gSaveBlock3Ptr->challengeSettings
    for name, lvl in (("base", 0), ("x5", 1), ("x10", 2), ("x50", 3)):
        body = HEAD + ("setexpensive %d\n" % lvl if lvl else "") + "savegame\nkeepsave r3m_%s\n" % name
        write("m00_save_%s" % name, body, "Save r3m_%s: ladder6_postgame + P9999999%s, saved in place." % (
            name, " + EXPENSIVE level %d" % lvl if lvl else ""))
    p = "m99_load_x50"
    body = ("start saves/r3m_x50.sav\ninclude ../../continue.txt\n" + open_mart(p, "flower") + "listshots %s 3\n" % p
            + close_mart(p))
    write(p, body, "Reload check: the x50 save keeps the setting (mints read P?00000 after CONTINUE).")

    list_tour("m01", "gr3", "Goldenrod Dept. Store 3F, X items (GoldenrodCity_DepartmentStore_3F_hns/scripts.inc:40-60).")
    list_tour("m02", "gr4", "Goldenrod Dept. Store 4F, vitamins (GoldenrodCity_DepartmentStore_4F_hns/scripts.inc:55-72).")
    list_tour("m03", "gr5", "Goldenrod Dept. Store 5F, TMs (GoldenrodCity_DepartmentStore_5F_hns/scripts.inc:97-120).\n"
              "Owned TMs read SOLD OUT (infinite TMs: GetItemImportance, src/item.c:881-886; src/shop.c:1364-1370).")
    list_tour("m04", "cel3", "Celadon Dept. Store 3F, TMs (CeladonCity_DepartmentStore_3F_hns/scripts.inc:17-40).")
    list_tour("m05", "flower", "Goldenrod Flower Shop mints, P20000 each (GoldenrodCity_FlowerShop_hns/scripts.inc:5-50).")
    list_tour("m06", "mahog", "Mahogany shop, evolution items (MahoganyTown_Shop_hns/scripts.inc:196-227); the granny\n"
              "sells only after VAR_MAHOGANY_TOWN_STATE >= 14, so the shop part runs directly.")
    list_tour("m07", "mtmoon", "Mt. Moon gift shop (MtMoon_Shop_hns/scripts.inc:8-28).")
    list_tour("m08", "safinc", "Safari Zone Gate incense clerk, infinite-TM branch (SafariZoneGate_hns/scripts.inc:104-121).")
    list_tour("m09", "safincf", "Safari Zone Gate incense clerk, FLAG_FINITE_TMS branch with two TMs (SafariZoneGate_hns/scripts.inc:124-142).")
    list_tour("m10", "safvit", "Safari Zone Gate vitamin guru (SafariZoneGate_hns/scripts.inc:144-163).")
    list_tour("m11", "sjtravel", "New Sinjoh travel shop (NewSinjoh_hns/scripts.inc:131-158).")
    list_tour("m12", "sjcafe", "New Sinjoh cafe (NewSinjoh_House4_hns/scripts.inc:4-34).")
    list_tour("m13", "alola", "Melemele (Alola) shop (Melemele_House_2_hns/scripts.inc:5-23).")
    list_tour("m14", "bfmart", "Battle Frontier Mart (BattleFrontier_Mart_hns/scripts.inc:4-29).")
    list_tour("m15", "thbasic", "Trainer Hill entrance, basic list (TrainerHill_Entrance_hns/scripts.inc:250-283).")
    list_tour("m16", "thbadge", "Trainer Hill entrance, badge list ('pokemart 0', src/shop.c:546-567).")
    list_tour("m17", "violet", "Violet Mart, badge list with all badges ('pokemart 0', src/shop.c:546-567).")

    # ---- buy flows (src/shop.c Task_BuyMenu .. BuyMenuTryMakePurchase)
    p = "m20_tmbuy"
    body = (HEAD + "ev additem ITEM_TM_PROTECT; additem ITEM_TM_HYPER_BEAM; additem ITEM_TM_THUNDER; end\n"
            + open_mart(p, "gr5") + "listshots %s\n" % p
            + pick(p + "_soldout", 1) + ack(p + "_soldout_back")
            + pick(p + "_tm16", 0) + confirm(p + "_tm16") + ack(p + "_tm16_back")
            + pick(p + "_tm33", 2) + confirm(p + "_tm33", yes=False) + "snap %s_tm33_no\n" % p
            + "listshots %s_after\n" % p + close_mart(p))
    write(p, body, "Goldenrod 5F with three TMs owned: SOLD OUT rows (src/shop.c:1364-1370), 'that item is sold out'\n"
          "(src/shop.c:1793), and a TM not owned = an important item: no quantity window, 'You wanted X?\n"
          "That'll be N' with YES/NO (src/shop.c:1843-1850), YES, then NO on another TM.")
    p = "m21_tmcel"
    body = (HEAD + "ev additem ITEM_TM_SAFEGUARD; additem ITEM_TM_DARK_PULSE; additem ITEM_TM_ENDURE; end\n"
            + open_mart(p, "cel3") + "listshots %s\n" % p
            + pick(p + "_soldout", 9) + ack(p + "_soldout_back") + close_mart(p))
    write(p, body, "Celadon 3F with three TMs owned (SOLD OUT on rows 0, 5 and 9).")
    p = "m22_balls"
    body = (HEAD + open_mart(p, "violet")
            + pick(p + "_pb", 0) + qty(p + "_pb", ups=9) + "tap A 0\n" + confirm(p + "_pb10") + ack(p + "_pb10_premier") + "tap A 0\n" + back_to_list()
            + "snap %s_pb10_list\n" % p
            + pick(p + "_pb20", 0) + qty(p + "_pb20", ups=19) + "tap A 0\n" + confirm(p + "_pb20") + ack(p + "_pb20_premier") + "tap A 0\n" + back_to_list()
            + pick(p + "_pbmax", 0) + qty(p + "_pbmax", max_=True) + "tap B 0\n" + back_to_list()
            + pick(p + "_fr", 7) + qty(p + "_fr", max_=True) + "tap A 0\n" + confirm(p + "_frmax", yes=False)
            + pick(p + "_pb9", 0) + qty(p + "_pb9", ups=8) + "tap A 0\n" + confirm(p + "_pb9") + ack(p + "_pb9_nobonus")
            + back_to_list() + close_mart(p))
    write(p, body, "Violet Mart: 10 Poke Balls (one Premier Ball, src/shop.c:2105-2118 gText_ThrowInPremierBall), 20 (two,\n"
          "gText_ThrowInPremierBalls), 9 (no bonus), the quantity window at x1 / x10 / x20 / max, and Full Restore\n"
          "at the max quantity (999 x P3000 = a 7-digit total) answered NO.")
    p = "m23_nomoney"
    body = (HEAD + "setmoney 50\n" + open_mart(p, "violet") + pick(p + "_pb", 0) + ack(p + "_back")
            + pick(p + "_fr", 7) + ack(p + "_fr_back") + close_mart(p))
    write(p, body, "Violet Mart with P50: 'You don't have enough money' (src/shop.c:1838) on a P100 and a P3000 item.")
    p = "m24_noroom"
    body = (HEAD + "ev file fill_balls.inc\n" + open_mart(p, "violet") + pick(p + "_pb", 0) + qty(p + "_pb")
            + "tap A 0\n" + confirm(p + "_pb") + ack(p + "_back") + close_mart(p))
    write(p, body, "Violet Mart with the Poke Ball pocket full: 'You have no more room for this item' (src/shop.c:2000-2012).")
    p = "m25_decorfull"
    body = (HEAD + "setbp 9999\nev file fill_dolls.inc\n"
            + "evstart special CreateBPDecorShop1; waitstate; release; end\n"
            + "waitcb2x CB2_BuyMenu 900\nwaittaskx Task_BuyMenu 900\nwaitquiet\n"
            + "listshots %s\n" % p
            + pick(p + "_poster", 0) + confirm(p + "_poster") + ack(p + "_poster_back")
            + pick(p + "_doll", 2) + confirm(p + "_doll") + ack(p + "_doll_back")
            + "press B\nwaitcb2x CB2_Overworld 900\nwaitctl 900\n")
    write(p, body, "Frontier Exchange BP decor shop 1 (CreateBPDecorShop1) with the 40 doll slots full: 'The space for X is\n"
          "full' (src/shop.c:2027-2035) for a poster and a doll, after 'You wanted X? That'll be N BP'.")

    p = "m26_poster"
    body = (HEAD + "setbp 9999\n"
            + "evstart special CreateBPDecorShop1; waitstate; release; end\n"
            + "waitcb2x CB2_BuyMenu 900\nwaittaskx Task_BuyMenu 900\nwaitquiet\n"
            + pick(p + "_poster", 0) + confirm(p + "_poster") + ack(p + "_poster_back")
            + pick(p + "_cushion", 1) + confirm(p + "_cushion") + ack(p + "_cushion_back")
            + pick(p + "_doll", 2) + confirm(p + "_doll") + ack(p + "_doll_back")
            + "press B\nwaitcb2x CB2_Overworld 900\nwaitctl 900\n")
    write(p, body, "BP decor shop 1 with an empty doll inventory: KISS POSTER and KISS CUSHION are categories H&S never sets\n"
          "up (src/decoration_inventory.c:14-17 sets only DECORCAT_DOLL), so DecorationAdd fails for them; the doll\n"
          "is bought.")

    p = "m27_finite"
    body = (HEAD + "setinfinitetms 0\nev setflag FLAG_FINITE_TMS; additem ITEM_TM_HIDDEN_POWER; end\n"
            + open_mart(p, "safinc") + "listshots %s\n" % p
            + pick(p + "_tm43", 1) + qty(p + "_tm43", ups=1) + "tap A 0\n" + confirm(p + "_tm43") + ack(p + "_tm43_back")
            + back_to_list() + close_mart(p))
    write(p, body, "Infinite TMs OFF (tx_Mode_InfiniteTMs = 0) and FLAG_FINITE_TMS: the Safari incense clerk's TM branch\n"
          "(SafariZoneGate_hns/scripts.inc:104-105), a TM is then an ordinary item: price, not SOLD OUT, even when\n"
          "owned, and the quantity window (gText_Var1CertainlyHowMany2, src/shop.c:1851-1854).")

    # ---- EXPENSIVE challenge: GetItemPrice x5 / x10 / x50 (src/item.c:837-842)
    for n, (lvl, fac) in enumerate(((1, 5), (2, 10), (3, 50))):
        p = "m3%d_x%d" % (n, fac)
        pre = HEAD + "setexpensive %d\nev additem ITEM_TM_PROTECT; end\n" % lvl
        body = pre
        for key in ("flower", "bfmart", "gr2", "gr5", "mahog"):
            q = "%s_%s" % (p, key)
            body += open_mart(q, key, money=9999999) + "listshots %s\n" % q
            if fac == 50 and key == "flower":
                body += (pick(q + "_mint", 0) + qty(q + "_mint", max_=True) + "tap A 0\n" + confirm(q + "_mint")
                         + ack(q + "_mint_back") + back_to_list())
            if fac == 50 and key == "bfmart":
                body += pick(q + "_fr", 3) + qty(q + "_fr", max_=True) + "tap A 0\n" + confirm(q + "_fr") + ack(q + "_fr_back") + back_to_list()
            if fac == 50 and key == "gr5":
                body += pick(q + "_tm16", 0) + confirm(q + "_tm16") + ack(q + "_tm16_back") + back_to_list()
            body += close_mart(q)
        if fac == 50:
            q = p + "_poor"
            body += "setmoney 500000\n" + open_mart(q, "flower") + pick(q + "_mint", 0) + ack(q + "_back") + close_mart(q)
        write(p, body, "EXPENSIVE x%d (tx_Challenges_Expensive = %d): Flower Shop mints, Frontier Mart, Goldenrod 2F and 5F,\n"
              "Mahogany. The list price goes through ConvertIntToDecimalStringN(.., 6) (src/shop.c:1350-1356).%s"
              % (fac, lvl, "\nAt x50 also: a mint bought at the max quantity (P1000000 each), Full Restore x max (P150000\n"
                 "each), a TM (P500000), and with P500000 left 'not enough money' on a mint." if fac == 50 else ""))


if __name__ == "__main__":
    main()
