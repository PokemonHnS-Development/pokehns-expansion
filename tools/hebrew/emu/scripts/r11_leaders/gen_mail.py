#!/usr/bin/env python3
"""Write the r11 mail tours (tours/r11_leaders/m*.txt and zz_make_mail_en.txt).

zz_make_mail_en (run on the ENGLISH ROM only): from ladder 6, TROPIC MAIL written by GOLD and
DREAM MAIL written by KRISTEN, both sent to the PC, the game saved: its battery is the
English-ROM sender save (saves_screens/r11/leaders_mail/mail_en_base.sav).

m1_mailbox (both ROMs, from mail_en_base.sav): Kenya's Retro Mail (sender written by
src/scrcmd.c:1468 with StringCopy, so not padded to 6 letters) taken to the PC, then seven mails
given from the bag (each opens the Easy Chat MAIL screen: its frame is shot once, the words are
out of scope), each READ from the party and sent to the PC, by players named with 1, 2, 3, 4, 5,
6 and 7 Hebrew letters (Latin of the same lengths on the English ROM). Then two more designs
read from the party, the second TAKE hitting the full mailbox. Then the PC MAILBOX: the list,
each row, each mail's 'what to do with X's mail?' + options and its READ, MOVE TO BAG (NO), GIVE
TO POKeMON (to Kenya, slot 1), CANCEL.

    gen_mail.py OUT_DIR
"""
import os
import sys

# (item, Hebrew name, Latin twin of the same length)
PLAYER_MAILS = [
    ("ITEM_ORANGE_MAIL", "ש", "S"),
    ("ITEM_HARBOR_MAIL", "דן", "DN"),
    ("ITEM_GLITTER_MAIL", "רון", "RON"),
    ("ITEM_MECH_MAIL", "נועה", "NOAH"),
    ("ITEM_WOOD_MAIL", "אביבה", "AVIVA"),
    ("ITEM_WAVE_MAIL", "מיכאלה", "MICHAL"),
    ("ITEM_BEAD_MAIL", "אלכסנדר", "ALEXAND"),
]
EXTRA_MAILS = [("ITEM_SHADOW_MAIL", "בן_דוד", "BEN_DAV"), ("ITEM_FAB_MAIL", "GOLD", "GOLD")]
ALL_ITEMS = [m[0] for m in PLAYER_MAILS + EXTRA_MAILS] + ["ITEM_TROPIC_MAIL", "ITEM_DREAM_MAIL"]


def give_and_read(p, item, first):
    """Bag > mail > GIVE > slot 0 > Easy Chat (one word, OK, YES) > held; party > MAIL > READ."""
    s = lambda name: ["snap %s_%s" % (p, name)] if first else []   # noqa: E731
    out = ["w32 @gMenuCallback@ 0", "startmenu BAG", "waitcb2x CB2_BagMenuRun 600",
           "waittaskx Task_BagMenu_HandleInput 600", "bagpocket 0", "bagseek %s" % item, "waitquiet"]
    out += s("bag") + ["tap A 4", "waitquiet"] + s("context")
    out += ["tap ROWNEXT 4", "waitquiet"] + s("context_give")
    out += ["tap A 4", "waitcb2x CB2_UpdatePartyMenu 900", "waittaskx Task_HandleChooseMonInput 600",
            "waitquiet"] + s("give_party")
    out += ["tap A 4", "waitcb2x CB2_EasyChatScreen 900", "ecwait"] + s("ec_frame")
    out += ["ecputword 0 0 EC_GROUP_GREETINGS EC_WORD_THANK_YOU", "ecbutton 2", "ec A"] + s("ec_confirm")
    out += ["tap A 0", "waitcb2x CB2_UpdatePartyMenu 1200", "60 -", "waitquiet", "snap %s_given" % p,
            "tap A 4", "waitcb2x CB2_BagMenuRun 900", "waittaskx Task_BagMenu_HandleInput 900", "waitquiet",
            "tap B 4", "waitcb2x CB2_Overworld 900", "waitctl 900 B", "30 -"]
    out += party_read(p, 0, first)
    return out


def party_read(p, slot, first):
    s = lambda name: ["snap %s_%s" % (p, name)] if first else []   # noqa: E731
    out = ["w32 @gMenuCallback@ 0", "startmenu POKEMON", "waitcb2x CB2_UpdatePartyMenu 600",
           "waittaskx Task_HandleChooseMonInput 600", "waitquiet"]
    if slot:
        out += ["seek 8 @gPartyMenu+9@ %d DOWN" % slot]
    out += s("party") + ["tap A 4", "waittaskx Task_HandleSelectionMenuInput 600", "waitquiet",
                         "partyact 7"] + s("actions_mail")
    out += ["tap A 4", "waittaskx Task_HandleSelectionMenuInput 600", "waitquiet", "partyact 9"] + s("mailmenu")
    out += ["tap A 4", "waitcb2x CB2_MailRead 900", "waitquiet", "snap %s_read" % p,
            "tap A 4", "waitcb2x CB2_UpdatePartyMenu 900", "waittaskx Task_HandleSelectionMenuInput 900",
            "waitquiet"]
    return out


def take_to_pc(p, first, full=False):
    """Still in the party's action menu after READ: MAIL > TAKE > send to PC? YES."""
    s = lambda name: ["snap %s_%s" % (p, name)] if first else []   # noqa: E731
    out = ["partyact 7", "tap A 4", "waittaskx Task_HandleSelectionMenuInput 600", "waitquiet",
           "partyact 8", "tap A 4", "waittaskx Task_HandleSendMailToPCYesNoInput 600", "waitquiet"]
    out += s("sendpc") + ["tap A 4", "waitkey 600", "snap %s_%s" % (p, "full" if full else "sent"),
                          "tap A 4", "waittaskx Task_HandleChooseMonInput 600", "waitquiet"]
    if full:
        out += ["snap %s_full_after" % p]
    out += ["tap B 4", "waitcb2x CB2_Overworld 900", "waitctl 900 B", "30 -"]
    return out


def mailbox(p, n):
    out = ["# the PC MAILBOX (src/player_pc.c, list src/menu_specialized.c:248-261)",
           "evstart lockall; special PlayerPC; waitstate; releaseall; end",
           "waittaskx PlayerPCProcessMenuInput 900", "waitquiet", "snap %s_pc_menu" % p,
           "press DOWN", "snap %s_pc_menu_mailbox" % p, "tap A 4",
           "waittaskx Mailbox_ProcessInput 900", "waitquiet", "snap %s_list_00" % p]
    for k in range(1, n + 1):                         # every row, the CANCEL row last
        out += ["press DOWN", "snap %s_list_%02d" % (p, k)]
    out += ["press UP"] * n + ["waitquiet", "snap %s_list_top" % p]
    for k in range(n):
        out += ["# mail %d" % k, "tap A 4", "waittaskx Mailbox_MailOptionsProcessInput 900", "waitquiet",
                "snap %s_m%02d_opts" % (p, k), "tap A 4", "waitcb2x CB2_MailRead 900", "waitquiet",
                "snap %s_m%02d_read" % (p, k), "tap A 4", "waittaskx Mailbox_ProcessInput 900", "waitquiet",
                "snap %s_m%02d_back" % (p, k)]
        if k < n - 1:
            out += ["press DOWN"]
    # options of the last mail: each row, MOVE TO BAG (NO), GIVE TO POKeMON (slot 0), CANCEL
    out += ["tap A 4", "waittaskx Mailbox_MailOptionsProcessInput 900", "waitquiet",
            "seek 8 @menu:sMenu+2@ 1 DOWN", "snap %s_opt_tobag" % p,
            "seek 8 @menu:sMenu+2@ 2 DOWN", "snap %s_opt_give" % p,
            "seek 8 @menu:sMenu+2@ 3 DOWN", "snap %s_opt_cancel" % p,
            "tap A 4", "waittaskx Mailbox_ProcessInput 900", "waitquiet", "snap %s_after_cancel" % p,
            "tap A 4", "waittaskx Mailbox_MailOptionsProcessInput 900", "waitquiet",
            "seek 8 @menu:sMenu+2@ 1 DOWN", "tap A 4", "waittaskx Mailbox_HandleConfirmMoveToBag 900",
            "waitquiet", "snap %s_tobag_prompt" % p, "tap DOWN 4", "waitquiet", "snap %s_tobag_no_sel" % p,
            "tap A 4", "waittaskx Mailbox_ProcessInput 900", "waitquiet", "snap %s_tobag_no" % p,
            "tap A 4", "waittaskx Mailbox_MailOptionsProcessInput 900", "waitquiet",
            "seek 8 @menu:sMenu+2@ 2 DOWN", "tap A 4", "waitcb2x CB2_UpdatePartyMenu 900",
            "waittaskx Task_HandleChooseMonInput 600", "waitquiet", "snap %s_give_party" % p,
            "seek 8 @gPartyMenu+9@ 1 DOWN", "tap A 4", "60 -", "waitquiet", "snap %s_given" % p, "tap A 4", "120 -", "waitquiet",
            "snap %s_after_give" % p, "tap B 4", "waittaskx PlayerPCProcessMenuInput 900", "waitquiet",
            "snap %s_pc_menu_end" % p, "tap B 4", "waitctl 900 B"]
    return out


def main(out):
    gives = "; ".join("additem %s, 1" % i for i in ALL_ITEMS)
    party = ("ev callnative ZeroPlayerPartyMons; givemon SPECIES_TYPHLOSION, 60; "
             "special CalculatePlayerPartyCount; %s; end" % gives)

    # --- the English-ROM sender save
    lines = ["# r11 (gen_mail.py): ENGLISH ROM ONLY. Makes saves_screens/r11/leaders_mail/mail_en_base.sav:",
             "# two mails written on the English ROM (TROPIC by GOLD, DREAM by KRISTEN) stored in the PC.",
             "start saves/ladder6_postgame.sav", "include _base.txt", party]
    lines += give_and_read("en1", "ITEM_TROPIC_MAIL", True) + take_to_pc("en1", True)
    lines += ["setname KRISTEN"] + give_and_read("en2", "ITEM_DREAM_MAIL", False) + take_to_pc("en2", False)
    lines += ["setname GOLD", "mails", "savegame overwrite", "keepsave mail_en"]
    open(os.path.join(out, "zz_make_mail_en.txt"), "w").write("\n".join(lines) + "\n")

    # --- the mailbox tour
    lines = ["# r11 (gen_mail.py): mail given from the bag, read, sent to the PC, and the PC MAILBOX, with",
             "# short / long Hebrew senders (Latin twins on the English ROM), Kenya's unpadded sender and",
             "# two mails written on the English ROM (mail_en_base.sav).",
             "start saves/mail_en_base.sav", "include _base.txt",
             "ev callnative ZeroPlayerPartyMons; givemon SPECIES_TYPHLOSION, 60; special CalculatePlayerPartyCount; "
             "%s; setvar VAR_KENYA, 0; end" % "; ".join("additem %s, 1" % m[0] for m in PLAYER_MAILS + EXTRA_MAILS),
             "mails",
             "# Kenya (Route 35 gate officer Randy, Gate_GoldenrodCity_Route35_hns/scripts.inc:4-30)",
             "warpto MAP_GATE_GOLDENROD_CITY_ROUTE35_HNS 3 6", "face UP", "tap A 4", "scene ky_offer 6000",
             "pickd 0", "scene ky_yes 12000", "snap ky_free"]
    lines += party_read("ky", 1, True) + take_to_pc("ky", True)
    for k, (item, he, en) in enumerate(PLAYER_MAILS):
        p = "p%d_%s" % (k + 1, item[5:-5].lower())
        lines += ["# mail from a player named %s / %s (%s)" % (he, en, item), "setname %s %s" % (he, en)]
        lines += give_and_read(p, item, k == 0) + take_to_pc(p, k == 0)
    for k, (item, he, en) in enumerate(EXTRA_MAILS):
        p = "x%d_%s" % (k + 1, item[5:-5].lower())
        lines += ["# %s from %s / %s: read from the party%s" % (item, he, en, "" if k == 0 else ", then TAKE into the full mailbox"),
                  "setname %s %s" % (he, en)]
        lines += give_and_read(p, item, False)
        if k == len(EXTRA_MAILS) - 1:
            lines += take_to_pc(p, False, full=True)
        else:
            lines += ["tap B 4", "waittaskx Task_HandleChooseMonInput 600", "tap B 4", "waitcb2x CB2_Overworld 900",
                      "waitctl 900 B", "# take it back to the bag so the next one can be given",
                      "w32 @gMenuCallback@ 0", "startmenu POKEMON", "waitcb2x CB2_UpdatePartyMenu 600",
                      "waittaskx Task_HandleChooseMonInput 600", "waitquiet", "tap A 4",
                      "waittaskx Task_HandleSelectionMenuInput 600", "waitquiet", "partyact 7", "tap A 4",
                      "waittaskx Task_HandleSelectionMenuInput 600", "waitquiet", "partyact 8", "tap A 4",
                      "waittaskx Task_HandleSendMailToPCYesNoInput 600", "waitquiet", "tap DOWN 4", "tap A 4",
                      "waittaskx Task_HandleLoseMailMessageYesNoInput 600", "waitquiet", "tap A 4", "waitkey 600",
                      "snap %s_taken_lost" % p, "tap A 4", "waittaskx Task_HandleChooseMonInput 600", "waitquiet",
                      "tap B 4", "waitcb2x CB2_Overworld 900", "waitctl 900 B", "30 -"]
    lines += ["mails"] + mailbox("mb", 10)
    open(os.path.join(out, "m1_mailbox.txt"), "w").write("\n".join(lines) + "\n")
    print("wrote zz_make_mail_en.txt, m1_mailbox.txt")


if __name__ == "__main__":
    main(sys.argv[1])
