#!/usr/bin/env python3
"""Write the r2 script-menu tours (mNN_*.txt) next to this file.

Each menu is drawn by a RAM event script at the x,y of its call site, after the message that call
site shows, on the call site's own map. The tour then snaps every row of a multichoice (seek on
menu.c's sMenu.cursorPos), or every row of a list menu (dynmultichoice, ShowScrollableMultichoice)
with svc.py's scrollshots, and closes it with B (A on the last row when B is ignored).

    gen.py [SRC]      SRC: the source tree whose data/maps gives each map's landing tile
                      (default ../pokehns-release)
Run the tours with svc.py (hns.py + scrollshots), e.g.
    svc.py tour ROM OUT --tours <this dir> --only '^m01_'
"""
import json
import os
import re
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
SRC = sys.argv[1] if len(sys.argv) > 1 else "../pokehns-release"
SAVE = "saves/r2menus_postgame.sav"

MC, DYN, SCROLL = "mc", "dyn", "scroll"
TASK = {MC: "Task_HandleMultichoiceInput", DYN: "Task_HandleScrollingMultichoiceInput",
        SCROLL: "field_specials:ScrollableMultichoice_ProcessInput"}


def landing(mapdir, at=None):
    """MAP_ID, x, y: AT if given, else the map's first warp tile (warptoloose accepts the
    tile the door moves the player to)."""
    j = json.load(open(os.path.join(SRC, "data/maps", mapdir, "map.json")))
    if at:
        return j["id"], at[0], at[1]
    w = j["warp_events"][0]
    return j["id"], w["x"], w["y"]


def srcline(rel, lineno, want):
    """The statement at RELPATH:LINENO (1-based), checked to contain WANT."""
    line = open(os.path.join(SRC, rel), encoding="utf-8").read().split("\n")[lineno - 1].strip()
    if want not in line:
        raise SystemExit("%s:%d does not hold %s: %s" % (rel, lineno, want, line))
    return line


_LISTS = None


def addr(label):
    """A script label as a number the tour resolves from the ELF when it runs (0x@LABEL@):
    evasm links against the ELF's global symbols only, and map texts are local labels."""
    return "0x@%s@" % label


def dyn_line(line):
    """dynmultichoice L, T, IGN, MAX, ROW, CB, LABEL...: the labels as 0x@LABEL@."""
    op, rest = line.split(None, 1)
    args = [a.strip() for a in rest.split(",")]
    return op + " " + ", ".join(args[:6] + [addr(a) for a in args[6:]])


def mc_rows(mid):
    """Rows of multichoice MID, counted in src/data/script_menu.h (sMultichoiceLists)."""
    global _LISTS
    if _LISTS is None:
        t = open(os.path.join(SRC, "src/data/script_menu.h"), encoding="utf-8").read()
        bodies = {m.group(1): len(re.findall(r"^\s*\{", m.group(2), re.M))
                  for m in re.finditer(r"MenuAction (s?MultichoiceList_\w+)\[\]\s*=\s*\{(.*?)\n\};", t, re.S)}
        _LISTS = {m.group(1): bodies[m.group(2)]
                  for m in re.finditer(r"\[(MULTI_\w+)\]\s*=\s*MULTICHOICE\((\w+)\)", t) if m.group(2) in bodies}
    return _LISTS[mid]


def mc(name, mapdir, x, y, mid, rows=None, msg=None, ign=False, pre=(), post=(), at=None, site=""):
    got = mc_rows(mid)
    if rows is not None and rows != got:
        print("note: %s %s has %d rows in the source (gen.py said %d)" % (name, mid, got, rows))
    rows = got
    return dict(name=name, kind=MC, map=landing(mapdir, at), rows=rows, ign=ign, site=site,
                pre=list(pre) + (["message %s" % addr(msg), "waitmessage"] if msg else []),
                menu="multichoice %d, %d, %s, %s" % (x, y, mid, "TRUE" if ign else "FALSE"),
                post=list(post))


def dyn(name, mapdir, rel, lineno, rows, msg=None, at=None):
    return dict(name=name, kind=DYN, map=landing(mapdir, at), rows=rows, ign=False,
                site="%s:%d" % (rel, lineno),
                pre=(["message %s" % addr(msg), "waitmessage"] if msg else []),
                menu=dyn_line(srcline(rel, lineno, "dynmultichoice")), post=[])


def scroll(name, mapdir, sid, rows, msg, bp=False, at=None, site=""):
    pre = ["message %s" % addr(msg), "waitmessage"]
    post = []
    if bp:
        pre.append("special ShowBattlePointsWindow")
        post = ["special CloseBattleFrontierTutorWindow", "special CloseBattlePointsWindow"]
    pre += ["setvar VAR_0x8004, %s" % sid, "setvar VAR_0x8006, 0"]
    return dict(name=name, kind=SCROLL, map=landing(mapdir, at), rows=rows, ign=False, site=site,
                pre=pre, menu="special ShowScrollableMultichoice; waitstate", post=post)


M = "data/maps/%s/scripts.inc"
TOURS = {
    "m01_johto": [
        mc("elev7", "GoldenrodCity_DepartmentStoreElevator_hns", 20, 0, "MULTI_7FLOORS", 8, at=(2, 3),
           site="GoldenrodCity_DepartmentStoreElevator_hns:44"),
        mc("elev5", "GoldenrodCity_DepartmentStoreElevator_hns", 20, 0, "MULTI_5FLOORS", 6, at=(2, 3),
           site="GoldenrodCity_DepartmentStoreElevator_hns:178"),
        mc("vending", "GoldenrodCity_DepartmentStore_2F_hns", 16, 0, "MULTI_VENDING_MACHINE", 4,
           pre=["message " + addr("GoldenrodDeptStore_Text_WhichDrinkWouldYouLike"), "waitmessage", "showmoneybox 0, 0"],
           post=["hidemoneybox"],
           site="GoldenrodCity_DepartmentStore_2F_hns:91-96"),
        mc("days", "Route29_hns", 20, 0, "MULTI_DAYS_OF_WEEK", 8, site="Route29_hns:86"),
        mc("elder1", "DragonsDen_Shrine_hns", 20, 6, "MULTI_ELDERQUIIZ1", 3,
           msg="DragonsDen_Shrine_Text_Question1", site="DragonsDen_Shrine_hns:102"),
        mc("elder2", "DragonsDen_Shrine_hns", 20, 6, "MULTI_ELDERQUIIZ2", 3,
           msg="DragonsDen_Shrine_Text_Question2", site="DragonsDen_Shrine_hns:116"),
        mc("elder3", "DragonsDen_Shrine_hns", 20, 6, "MULTI_ELDERQUIIZ3", 3,
           msg="DragonsDen_Shrine_Text_Question3", site="DragonsDen_Shrine_hns:130"),
        mc("elder4", "DragonsDen_Shrine_hns", 20, 6, "MULTI_ELDERQUIIZ4", 3,
           msg="DragonsDen_Shrine_Text_Question4", site="DragonsDen_Shrine_hns:144"),
        mc("elder5", "DragonsDen_Shrine_hns", 20, 6, "MULTI_ELDERQUIIZ5", 3,
           msg="DragonsDen_Shrine_Text_Question5", site="DragonsDen_Shrine_hns:158"),
        mc("goldsilver", "Route39_hns", 20, 8, "MULTI_GOLDSILVER", 2,
           msg="Route39_Text_ChooseLegend", site="Route39_hns:45"),
        mc("fossil", "RuinsOfAlph_Lab_hns", 17, 0, "MULTI_FOSSIL_HNS", 4,
           msg="RuinsOfAlph_Lab_Text_TwoFossilsPickOne", site="RuinsOfAlph_Lab_hns:564"),
        mc("olivine", "OlivineCity_PortInside_hns", 20, 0, "MULTI_OLIVINE_HARBOR", 4,
           msg="OlivinePort_Text_WhereSail", site="OlivineCity_PortInside_hns:121"),
        mc("vermilion", "VermilionCity_PortInside_hns", 20, 0, "MULTI_VERMILION_HARBOR", 4,
           msg="VermilionPort_Text_WhereSail", site="VermilionCity_PortInside_hns:41"),
        mc("lati_verm", "VermilionCity_hns", 20, 8, "MULTI_TV_LATI", 2, ign=True,
           msg="VermilionCity_Text_StevenIntro", site="VermilionCity_hns:482"),
        mc("lati_house", "NewBarkTown_PlayersHouse_1F_hns", 22, 8, "MULTI_TV_LATI", 2, ign=True,
           msg="PlayersHouse_1F_Text_WhatColorDidTheySay", site="data/scripts/players_house.inc:492"),
        mc("hoenn", "SaffronCity_SilphCo_hns", 20, 0, "MULTI_HOENN_STARTERS", 3,
           msg="SaffronCity_SilphCo_Text_Steven2", site="SaffronCity_SilphCo_hns:18"),
        mc("link", "GoldenrodCity_PokemonCenter_hns", 0, 0, "MULTI_LINK_SERVICES_HNS", 3,
           msg="GoldenrodCity_PokemonCenter_LinkNpc_Text_Intro", site="GoldenrodCity_PokemonCenter_hns:39"),
        mc("linkbattle", "GoldenrodCity_PokemonCenter_hns", 0, 0, "MULTI_BATTLE_MODE_HNS", 3,
           msg="GoldenrodCity_PokemonCenter_LinkNpc_Text_BattleMode",
           pre=["showhelpwindow HELP_TRADE_WINDOW", "waitbuttonpress", "hidehelpwindow", "closemessage"],
           site="GoldenrodCity_PokemonCenter_hns:79-81"),
    ],
    "m02_dyn": [
        dict(dyn("bills", "Route25_BillsHouse_hns", M % "Route25_BillsHouse_hns", 17, 16),
             pre=["showhelpwindow HELP_TELEPORTER_WINDOW", "waitbuttonpress", "hidehelpwindow", "closemessage",
                  "message " + addr("Route25_BillsHouse_Text_Teleporter"), "waitmessage"]),
        dyn("hotsprings", "NewSinjoh_HotSprings_hns", M % "NewSinjoh_HotSprings_hns", 126, 15,
            msg="NewSinjoh_HotSprings_Text_PLATutorChoose"),
        dyn("ulaula_tutor", "UlaulaIsle_hns", M % "UlaulaIsle_hns", 402, 27,
            msg="Alola_Ulaula_Text_MoveTutorChoose"),
        dyn("totem_akala", "AkalaIsle_hns", M % "AkalaIsle_hns", 258, 5, msg="Alola_Akala_Totem_sign_Text_0"),
        dyn("totem_melemele", "MelemeleIsle_hns", M % "MelemeleIsle_hns", 390, 5,
            msg="Alola_Melemele_Totem_sign_Text_0"),
        dyn("totem_poni", "PoniIsle_hns", M % "PoniIsle_hns", 176, 5, msg="Alola_Poni_Totem_sign_Text_0"),
        dyn("totem_ulaula", "UlaUla_Forest_hns", M % "UlaUla_Forest_hns", 229, 5,
            msg="Alola_Ulaula_Totem_sign_Text_0"),
        dyn("samson", "Melemele_PlayerHouse_hns", M % "Melemele_PlayerHouse_hns", 37, 5,
            msg="Alola_Melemele_SamsonOakVilla_Dialogue_Text_10"),
    ],
    "m03_scroll": [
        scroll("tutor1", "BattleFrontier_Lounge7_hns", "SCROLL_MULTI_BF_MOVE_TUTOR_1", 11,
               "BattleFrontier_Lounge7_Text_TeachWhichMove_hns", bp=True, site="BattleFrontier_Lounge7_hns:20-29"),
        scroll("tutor2", "BattleFrontier_Lounge7_hns", "SCROLL_MULTI_BF_MOVE_TUTOR_2", 11,
               "BattleFrontier_Lounge7_Text_TeachWhichMove_hns", bp=True, site="BattleFrontier_Lounge7_hns:144-151"),
        scroll("tutor3", "BattleFrontier_Lounge7_hns", "SCROLL_MULTI_BF_MOVE_TUTOR_3", 4,
               "BattleFrontier_Lounge7_Text_TeachWhichMoveElemental", bp=True, site="BattleFrontier_Lounge7_hns:324-331"),
        scroll("reception", "BattleFrontier_ReceptionGate_hns", "SCROLL_MULTI_BF_RECEPTIONIST", 10,
               "BattleFrontier_ReceptionGate_Text_LearnAboutWhich2_hns", site="BattleFrontier_ReceptionGate_hns:138-143"),
        scroll("tentrules", "VerdanturfTown_BattleTentLobby_hns", "SCROLL_MULTI_BATTLE_TENT_RULES", 7,
               "BattleFrontier_BattlePalaceLobby_Text_ReadWhichHeading", site="VerdanturfTown_BattleTentLobby_hns:280-285"),
    ],
    "m04_frontier": [
        mc("challengeinfo", "BattleFrontier_BattleTowerLobby_hns", 17, 6, "MULTI_CHALLENGEINFO", 3,
           msg="BattleFrontier_BattleTowerLobby_Text_TakeSinglesChallenge_hns",
           site="BattleFrontier_BattleTowerLobby_hns:178"),
        mc("levelmode", "BattleFrontier_BattleTowerLobby_hns", 17, 6, "MULTI_LEVEL_MODE", 3,
           msg="BattleFrontier_BattleTowerLobby_Text_WhichLevelMode_hns",
           site="BattleFrontier_BattleTowerLobby_hns:189"),
        mc("goon_rec_rest", "BattleFrontier_BattleTowerLobby_hns", 19, 4, "MULTI_GO_ON_RECORD_REST_RETIRE", 4,
           ign=True, msg="BattleFrontier_BattleTowerBattleRoom_Text_ReadyFor2ndOpponent_hns",
           site="BattleFrontier_BattleTowerBattleRoom_hns:77"),
        mc("goon_rest", "BattleFrontier_BattleTowerLobby_hns", 20, 6, "MULTI_GO_ON_REST_RETIRE", 3,
           ign=True, msg="BattleFrontier_BattleTowerBattleRoom_Text_ReadyFor2ndOpponent_hns",
           site="BattleFrontier_BattleTowerBattleRoom_hns:86"),
        mc("goon_rec_retire", "BattleFrontier_BattleTowerLobby_hns", 19, 6, "MULTI_GO_ON_RECORD_RETIRE", 3,
           ign=True, msg="BattleFrontier_BattleTowerBattleRoom_Text_ReadyFor2ndOpponent_hns",
           site="BattleFrontier_BattleTowerMultiBattleRoom_hns:312"),
        mc("goon_retire", "BattleFrontier_BattleTowerLobby_hns", 20, 8, "MULTI_GO_ON_RETIRE", 2,
           ign=True, msg="BattleFrontier_BattleTowerBattleRoom_Text_ReadyFor2ndOpponent_hns",
           site="BattleFrontier_BattleTowerMultiBattleRoom_hns:321"),
        mc("tent_goon_rest", "VerdanturfTown_BattleTentLobby_hns", 20, 6, "MULTI_GO_ON_REST_RETIRE", 3,
           ign=True, msg="BattleFrontier_BattlePalaceBattleRoom_Text_PreparedFor2ndOpponent",
           site="VerdanturfTown_BattleTentBattleRoom_hns:83"),
        mc("tourney_rec", "BattleFrontier_BattleDomeLobby_hns", 16, 0, "MULTI_TOURNEY_WITH_RECORD", 6,
           ign=True, msg="BattleFrontier_BattleDomePreBattleRoom_Text_ReadyForRound1_hns",
           site="BattleFrontier_BattleDomePreBattleRoom_hns:33"),
        mc("tourney_norec", "BattleFrontier_BattleDomeLobby_hns", 16, 2, "MULTI_TOURNEY_NO_RECORD", 5,
           ign=True, msg="BattleFrontier_BattleDomePreBattleRoom_Text_ReadyForRound1_hns",
           site="BattleFrontier_BattleDomePreBattleRoom_hns:44"),
        mc("rules_frontier", "BattleFrontier_ReceptionGate_hns", 15, 0, "MULTI_FRONTIER_RULES", 6,
           msg="BattleFrontier_ReceptionGate_Text_LearnAboutWhat_hns", site="BattleFrontier_ReceptionGate_hns:219"),
        mc("passinfo", "BattleFrontier_ReceptionGate_hns", 16, 4, "MULTI_FRONTIER_PASS_INFO", 4,
           msg="BattleFrontier_ReceptionGate_Text_LearnAboutWhich1_hns", site="BattleFrontier_ReceptionGate_hns:270"),
        mc("rules_tower", "BattleFrontier_BattleTowerLobby_hns", 17, 2, "MULTI_BATTLE_TOWER_RULES", 5,
           msg="BattleFrontier_BattleTowerLobby_Text_ReadWhichHeading_hns", site="BattleFrontier_BattleTowerLobby_hns:902"),
        mc("feelings", "BattleFrontier_BattleTowerLobby_hns", 16, 4, "MULTI_BATTLE_TOWER_FEELINGS", 2,
           msg="BattleFrontier_BattleTowerLobby_Text_DescribeFeelingsAboutBattleTower_hns",
           site="BattleFrontier_BattleTowerLobby_hns:439"),
        mc("rules_dome", "BattleFrontier_BattleDomeLobby_hns", 17, 4, "MULTI_BATTLE_DOME_RULES", 4,
           msg="BattleFrontier_BattleDomeLobby_Text_ReadWhichHeading_hns", site="BattleFrontier_BattleDomeLobby_hns:412"),
        mc("rules_palace", "BattleFrontier_BattlePalaceLobby_hns", 16, 0, "MULTI_BATTLE_PALACE_RULES", 6,
           msg="BattleFrontier_BattlePalaceLobby_Text_ReadWhichHeading_hns", site="BattleFrontier_BattlePalaceLobby_hns:341"),
        mc("rules_arena", "BattleFrontier_BattleArenaLobby_hns", 17, 2, "MULTI_BATTLE_ARENA_RULES", 5,
           msg="BattleFrontier_BattleArenaLobby_Text_ReadWhichHeading_hns", site="BattleFrontier_BattleArenaLobby_hns:326"),
        mc("rules_factory", "BattleFrontier_BattleFactoryLobby_hns", 17, 0, "MULTI_BATTLE_FACTORY_RULES", 6,
           msg="BattleFrontier_BattleFactoryLobby_Text_ReadWhichHeading_hns", site="BattleFrontier_BattleFactoryLobby_hns:285"),
        mc("rules_pike", "BattleFrontier_BattlePikeLobby_hns", 16, 4, "MULTI_BATTLE_PIKE_RULES", 4,
           msg="BattleFrontier_BattlePikeLobby_Text_ReadWhichHeading_hns", site="BattleFrontier_BattlePikeLobby_hns:241"),
        mc("rules_pyramid", "BattleFrontier_BattlePyramidLobby_hns", 15, 2, "MULTI_BATTLE_PYRAMID_RULES", 5,
           msg="BattleFrontier_BattlePyramidLobby_Text_ReadWhichHeading_hns", site="BattleFrontier_BattlePyramidLobby_hns:498"),
        mc("rules_slateport", "SlateportCity_BattleTentLobby_hns", 17, 0, "MULTI_SLATEPORT_TENT_RULES", 5,
           msg="BattleFrontier_BattleFactoryLobby_Text_ReadWhichHeading", site="SlateportCity_BattleTentLobby_hns:245"),
        mc("rules_fallarbor", "FallarborTown_BattleTentLobby_hns", 17, 0, "MULTI_FALLARBOR_TENT_RULES", 4,
           msg="BattleFrontier_BattleArenaLobby_Text_ReadWhichHeading", site="FallarborTown_BattleTentLobby_hns:267"),
        mc("tagmatch", "TrainerHill_Entrance_hns", 13, 2, "MULTI_TAG_MATCH_TYPE", 5,
           msg="TrainerHill_Entrance_hns_Text_LikeToChallengeTrainers", site="TrainerHill_Entrance_hns:156"),
        mc("brag_hof", "BattleFrontier_BattleTowerLobby_hns", 15, 8, "MULTI_HOF_QUIT", 2,
           site="data/scripts/trainer_card_frlg.inc:114"),
        mc("brag_eggs", "BattleFrontier_BattleTowerLobby_hns", 16, 8, "MULTI_EGGS_QUIT", 2,
           site="data/scripts/trainer_card_frlg.inc:122"),
        mc("brag_vict", "BattleFrontier_BattleTowerLobby_hns", 15, 8, "MULTI_VICTORIES_QUIT", 2,
           site="data/scripts/trainer_card_frlg.inc:130"),
        mc("brag_hof_eggs", "BattleFrontier_BattleTowerLobby_hns", 15, 6, "MULTI_HOF_EGGS_QUIT", 3,
           site="data/scripts/trainer_card_frlg.inc:138"),
        mc("brag_hof_vict", "BattleFrontier_BattleTowerLobby_hns", 15, 6, "MULTI_HOF_VICTORIES_QUIT", 3,
           site="data/scripts/trainer_card_frlg.inc:147"),
        mc("brag_eggs_vict", "BattleFrontier_BattleTowerLobby_hns", 15, 6, "MULTI_EGGS_VICTORIES_QUIT", 3,
           site="data/scripts/trainer_card_frlg.inc:156"),
        mc("brag_all", "BattleFrontier_BattleTowerLobby_hns", 15, 5, "MULTI_HOF_EGGS_VICTORIES_QUIT", 4,
           site="data/scripts/trainer_card_frlg.inc:165"),
    ],
    "m06_extra": [
        mc("enterinfo", "LilycoveCity_ContestLobby_hns", 0, 0, "MULTI_ENTERINFO",
           msg="LilycoveCity_ContestLobby_Text_EnterContest1", site="data/scripts/contest_hall.inc:63"),
        mc("enterinfo_link", "LilycoveCity_ContestLobby_hns", 0, 0, "MULTI_ENTERINFO",
           msg="LilycoveCity_ContestLobby_Text_EnterContest3", site="LilycoveCity_ContestLobby_hns:617"),
        mc("linkcontest_mode", "LilycoveCity_ContestLobby_hns", 0, 0, "MULTI_LINK_CONTEST_MODE",
           msg="LilycoveCity_ContestLobby_Text_WhichContestMode", site="LilycoveCity_ContestLobby_hns:633"),
        mc("linkcontest_info", "LilycoveCity_ContestLobby_hns", 0, 0, "MULTI_LINK_CONTEST_INFO",
           msg="LilycoveCity_ContestLobby_Text_WhichTopic2", site="LilycoveCity_ContestLobby_hns:666"),
        mc("linkleader", "LilycoveCity_ContestLobby_hns", 16, 6, "MULTI_LINK_LEADER",
           msg="LilycoveCity_ContestLobby_Text_PleaseDecideLinkLeader", site="LilycoveCity_ContestLobby_hns:840"),
        mc("gambler_bet", "BattleFrontier_Lounge3_hns", 20, 4, "MULTI_FRONTIER_GAMBLER_BET",
           msg="BattleFrontier_Lounge3_Text_HowMuchCanYouSpot_hns", pre=[], post=["special CloseBattlePointsWindow"],
           site="BattleFrontier_Lounge3_hns:28-34"),
        mc("pyramid_items", "BattleFrontier_BattlePyramidLobby_hns", 17, 6, "MULTI_FRONTIER_ITEM_CHOOSE",
           msg="BattleFrontier_BattlePyramidLobby_Text_BagCannotHoldPickItemsToKeep_hns",
           site="BattleFrontier_BattlePyramidLobby_hns:445"),
        mc("yesnoinfo_hill", "TrainerHill_Entrance_hns", 15, 6, "MULTI_YESNOINFO",
           msg="TrainerHill_Entrance_hns_Text_LikeToChallengeTrainers", site="TrainerHill_Entrance_hns:142"),
    ],
    "m05_contest": [
        mc("contest_info", "LilycoveCity_ContestLobby_hns", 0, 0, "MULTI_CONTEST_INFO", 5,
           msg="LilycoveCity_ContestLobby_Text_WhichTopic1", site="data/scripts/contest_hall.inc:74"),
        mc("contest_rank", "LilycoveCity_ContestLobby_hns", 0, 0, "MULTI_CONTEST_RANK", 5,
           msg="LilycoveCity_ContestLobby_Text_EnterWhichRank", site="data/scripts/contest_hall.inc:118"),
        mc("contest_type", "LilycoveCity_ContestLobby_hns", 0, 0, "MULTI_CONTEST_TYPE", 6,
           msg="LilycoveCity_ContestLobby_Text_EnterWhichContest1", site="data/scripts/contest_hall.inc:153"),
        mc("contest_type_link", "LilycoveCity_ContestLobby_hns", 0, 0, "MULTI_CONTEST_TYPE", 6,
           msg="LilycoveCity_ContestLobby_Text_EnterWhichContest3", site="LilycoveCity_ContestLobby_hns:655"),
        mc("satisfaction", "BattleFrontier_BattleTowerLobby_hns", 20, 8, "MULTI_SATISFACTION", 2, ign=True,
           msg="BattleFrontier_BattleTowerLobby_Text_HowDidBattleTowerTurnOut", site="data/scripts/interview.inc:252"),
        mc("profile", "GoldenrodCity_PokemonCenter_hns", 17, 6, "MULTI_YESNOINFO_2", 3,
           msg="ProfileMan_Text_MayISeeYourProfile", site="data/scripts/profile_man.inc:11"),
        mc("register", "GoldenrodCity_PokemonCenter_hns", 0, 0, "MULTI_REGISTER_MENU", 4,
           msg="SecretBase_Text_WhatWouldYouLikeToDo", site="data/scripts/shared_secret_base.inc:100"),
    ],
}


# the gambler shows the BP window after his message (BattleFrontier_Lounge3_hns:28-29)
def _fix_gambler():
    for it in TOURS["m06_extra"]:
        if it["name"] == "gambler_bet":
            it["pre"].append("special ShowBattlePointsWindow")


_fix_gambler()


def tour_text(tname, items):
    out = ["# r2 script menus: %s (generated by gen.py; edit gen.py, not this file)" % tname,
           "# Each menu: a RAM script at the call site's x,y with that site's message; every row snapped."
           "\n# Battle-room menus are drawn in their facility's lobby (the battle rooms run map scripts on entry).",
           "start %s" % SAVE, "include ../continue.txt",
           "# the save has never entered the Frontier: skip the Reception Gate's first-visit scene",
           "ev setvar VAR_HAS_ENTERED_BATTLE_FRONTIER, 1; end"]
    cur = None
    for it in items:
        mid, x, y = it["map"]
        out.append("")
        out.append("# %s  (%s)" % (it["name"], it["site"]))
        if cur != (mid, x, y):
            out.append("warptoloose %s %d %d" % (mid, x, y))
            # let the map-name pop-up finish: while it slides out it scrolls the window layer,
            # and a menu opened then is drawn shifted up (both ROMs)
            out.append("waitnotask map_name_popup:Task_MapNamePopUpWindow 600")
            cur = (mid, x, y)
        body = ["lockall"] + it["pre"] + [it["menu"]] + it["post"] + ["closemessage", "releaseall", "end"]
        out.append("evstart " + "; ".join(body))
        if any(p.startswith("showhelpwindow") for p in it["pre"]):
            out.append("waitmem 32 @sGlobalScriptContext+4@ @WaitForAorBPress@ 300   # waitbuttonpress under the help window")
            out.append("snap %s_help" % it["name"])
            out.append("tap A 0")
        # message pages (A on each) until the menu's task runs; shots NAME_m_NN
        out.append("talk %s_m 40 - %s" % (it["name"], TASK[it["kind"]]))
        if it["kind"] == MC:
            out.append("snap %s_r1" % it["name"])
            for r in range(1, it["rows"]):
                out.append("seek 8 @menu:sMenu+2@ %d DOWN" % r)
                out.append("snap %s_r%d" % (it["name"], r + 1))
            out.append("tap %s 0" % ("A" if it["ign"] else "B"))
        else:
            # one shot per row (these lists wrap at the end, so MAX = the row count)
            out.append("scrollshots %s_r DOWN %d 8" % (it["name"], it["rows"]))
            out.append("tap B 0")
        out.append("waitctl 900")
    return "\n".join(out) + "\n"


if __name__ == "__main__":
    for tname, items in TOURS.items():
        p = os.path.join(HERE, tname + ".txt")
        with open(p, "w") as fh:
            fh.write(tour_text(tname, items))
        print("wrote %s (%d menus)" % (p, len(items)))
