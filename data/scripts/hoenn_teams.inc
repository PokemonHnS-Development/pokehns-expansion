@ Hoenn & Seek (part 16a): Team Aqua and Team Magma quests, the Maxie + Archie
@ double at the Mt. Pyre summit, Norman's call, and Brendan & May.
@ Design: claude/hns-hoenn-aqua-magma-quests.md (claude.ai Project "Pokemon").
@
@ Trainer IDs (Emerald names reused; teams in data/hoenn/trainer_parties.party):
@   TRAINER_ARCHIE / TRAINER_MAXIE_MT_CHIMNEY        leaders, after their quests
@   TRAINER_MATT / TRAINER_SHELLY_WEATHER_INSTITUTE / TRAINER_TABITHA_MAGMA_HIDEOUT   admins
@   TRAINER_MAXIE_MOSSDEEP + TRAINER_SHELLY_SEAFLOOR_CAVERN (renamed ARCHIE)        the double
@   TRAINER_BRENDAN_LILYCOVE_MUDKIP + TRAINER_MAY_LILYCOVE_MUDKIP                   Brendan & May
@ Every battle here is repeatable: the trainer flags are cleared before each one.

@ ---------------------------------------------------------------- Team Aqua: "Signal from the Deep"

HoennSeek_EventScript_Matt::
	lock
	faceplayer
	goto_if_set FLAG_HOENN_AQUA_DONE, HoennSeek_EventScript_MattChallenge
	goto_if_set FLAG_HOENN_AQUA_QUEST, HoennSeek_EventScript_MattRemind
	msgbox HoennSeek_Text_MattQuest, MSGBOX_DEFAULT
	setflag FLAG_HOENN_AQUA_QUEST
	clearflag FLAG_ITEM_ABANDONED_SHIP_HIDDEN_FLOOR_ROOM_2_SCANNER
	release
	end
HoennSeek_EventScript_MattRemind::
	checkitem ITEM_SCANNER
	goto_if_eq VAR_RESULT, TRUE, HoennSeek_EventScript_MattHasScanner
	msgbox HoennSeek_Text_MattRemind, MSGBOX_DEFAULT
	release
	end
HoennSeek_EventScript_MattHasScanner::
	msgbox HoennSeek_Text_MattHasScanner, MSGBOX_DEFAULT
	release
	end
HoennSeek_EventScript_MattChallenge::
	msgbox HoennSeek_Text_MattChallenge, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, HoennSeek_EventScript_TeamsDecline
	cleartrainerflag TRAINER_MATT
	trainerbattle_no_intro TRAINER_MATT, HoennSeek_Text_MattDefeat
	msgbox HoennSeek_Text_MattAfter, MSGBOX_DEFAULT
	release
	end

HoennSeek_EventScript_Shelly::
	lock
	faceplayer
	goto_if_unset FLAG_HOENN_AQUA_DONE, HoennSeek_EventScript_ShellyIntro
	msgbox HoennSeek_Text_ShellyChallenge, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, HoennSeek_EventScript_TeamsDecline
	cleartrainerflag TRAINER_SHELLY_WEATHER_INSTITUTE
	trainerbattle_no_intro TRAINER_SHELLY_WEATHER_INSTITUTE, HoennSeek_Text_ShellyDefeat
	msgbox HoennSeek_Text_ShellyAfter, MSGBOX_DEFAULT
	release
	end
HoennSeek_EventScript_ShellyIntro::
	msgbox HoennSeek_Text_ShellyIntro, MSGBOX_DEFAULT
	release
	end

HoennSeek_EventScript_Archie::
	lock
	faceplayer
	goto_if_set FLAG_HOENN_AQUA_DONE, HoennSeek_EventScript_ArchieAfter
	checkitem ITEM_SCANNER
	goto_if_eq VAR_RESULT, TRUE, HoennSeek_EventScript_ArchieScanner
	goto_if_set FLAG_HOENN_AQUA_QUEST, HoennSeek_EventScript_ArchieWaiting
	msgbox HoennSeek_Text_ArchieIntro, MSGBOX_DEFAULT
	release
	end
HoennSeek_EventScript_ArchieWaiting::
	msgbox HoennSeek_Text_ArchieWaiting, MSGBOX_DEFAULT
	release
	end
HoennSeek_EventScript_ArchieScanner::
	msgbox HoennSeek_Text_ArchieScanner, MSGBOX_DEFAULT
	setvar VAR_0x8004, ITEM_SCANNER
	call Common_EventScript_PlayerHandedOverTheItem
	removeitem ITEM_SCANNER
	msgbox HoennSeek_Text_ArchieBattle, MSGBOX_DEFAULT
	cleartrainerflag TRAINER_ARCHIE
	trainerbattle_no_intro TRAINER_ARCHIE, HoennSeek_Text_ArchieDefeat
	msgbox HoennSeek_Text_ArchieReward, MSGBOX_DEFAULT
	giveitem ITEM_DAMP_ROCK
	giveitem ITEM_DIVE_BALL, 5
	setflag FLAG_HOENN_AQUA_DONE
	call HoennSeek_EventScript_TeamsCheckBoth
	release
	end
HoennSeek_EventScript_ArchieAfter::
	call HoennSeek_EventScript_TeamsLeaderHint
	msgbox HoennSeek_Text_ArchieChallenge, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, HoennSeek_EventScript_TeamsDecline
	cleartrainerflag TRAINER_ARCHIE
	trainerbattle_no_intro TRAINER_ARCHIE, HoennSeek_Text_ArchieDefeat
	msgbox HoennSeek_Text_ArchieRematchAfter, MSGBOX_DEFAULT
	release
	end

@ ---------------------------------------------------------------- Team Magma: "Runaway Torkoal"

HoennSeek_EventScript_Tabitha::
	lock
	faceplayer
	goto_if_set FLAG_HOENN_MAGMA_DONE, HoennSeek_EventScript_TabithaChallenge
	goto_if_set FLAG_HOENN_MAGMA_REPORT, HoennSeek_EventScript_TabithaRemind
	goto_if_set FLAG_HOENN_TORKOAL_FOUND, HoennSeek_EventScript_TabithaTorkoalBack
	goto_if_set FLAG_HOENN_MAGMA_QUEST, HoennSeek_EventScript_TabithaWaiting
	msgbox HoennSeek_Text_TabithaQuest, MSGBOX_DEFAULT
	setflag FLAG_HOENN_MAGMA_QUEST
	release
	end
HoennSeek_EventScript_TabithaWaiting::
	msgbox HoennSeek_Text_TabithaWaiting, MSGBOX_DEFAULT
	release
	end
HoennSeek_EventScript_TabithaTorkoalBack::
	msgbox HoennSeek_Text_TabithaTorkoalBack, MSGBOX_DEFAULT
	setflag FLAG_HOENN_MAGMA_REPORT
	release
	end
HoennSeek_EventScript_TabithaRemind::
	msgbox HoennSeek_Text_TabithaRemind, MSGBOX_DEFAULT
	release
	end
HoennSeek_EventScript_TabithaChallenge::
	msgbox HoennSeek_Text_TabithaChallenge, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, HoennSeek_EventScript_TeamsDecline
	cleartrainerflag TRAINER_TABITHA_MAGMA_HIDEOUT
	trainerbattle_no_intro TRAINER_TABITHA_MAGMA_HIDEOUT, HoennSeek_Text_TabithaDefeat
	msgbox HoennSeek_Text_TabithaAfter, MSGBOX_DEFAULT
	release
	end

@ The station's Torkoal, on the Fiery Path. Its object flag is FLAG_HOENN_TORKOAL_FOUND.
@ It can't be caught: FLAG_NO_WILD_CATCHING is set for the battle.
HoennSeek_EventScript_StationTorkoal::
	lock
	faceplayer
	playmoncry SPECIES_TORKOAL, CRY_MODE_NORMAL
	waitmoncry
	goto_if_unset FLAG_HOENN_MAGMA_QUEST, HoennSeek_EventScript_TorkoalNotYet
	msgbox HoennSeek_Text_TorkoalAgitated, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_NO_WILD_CATCHING
	setvar VAR_0x8004, SPECIES_TORKOAL
	special HoennSetupScaledWildBattle
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	dowildbattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	clearflag FLAG_NO_WILD_CATCHING
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_WON, HoennSeek_EventScript_TorkoalStillAgitated
	msgbox HoennSeek_Text_TorkoalCalm, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	removeobject VAR_LAST_TALKED
	fadescreen FADE_FROM_BLACK
	msgbox HoennSeek_Text_TorkoalFollows, MSGBOX_DEFAULT
	release
	end
HoennSeek_EventScript_TorkoalNotYet::
	msgbox HoennSeek_Text_TorkoalNotYet, MSGBOX_DEFAULT
	release
	end
HoennSeek_EventScript_TorkoalStillAgitated::
	msgbox HoennSeek_Text_TorkoalStillAgitated, MSGBOX_DEFAULT
	release
	end

HoennSeek_EventScript_Maxie::
	lock
	faceplayer
	goto_if_set FLAG_HOENN_MAGMA_DONE, HoennSeek_EventScript_MaxieAfter
	goto_if_set FLAG_HOENN_MAGMA_REPORT, HoennSeek_EventScript_MaxieReport
	goto_if_set FLAG_HOENN_MAGMA_QUEST, HoennSeek_EventScript_MaxieWaiting
	msgbox HoennSeek_Text_MaxieIntro, MSGBOX_DEFAULT
	release
	end
HoennSeek_EventScript_MaxieWaiting::
	msgbox HoennSeek_Text_MaxieWaiting, MSGBOX_DEFAULT
	release
	end
HoennSeek_EventScript_MaxieReport::
	msgbox HoennSeek_Text_MaxieReport, MSGBOX_DEFAULT
	cleartrainerflag TRAINER_MAXIE_MT_CHIMNEY
	trainerbattle_no_intro TRAINER_MAXIE_MT_CHIMNEY, HoennSeek_Text_MaxieDefeat
	msgbox HoennSeek_Text_MaxieReward, MSGBOX_DEFAULT
	giveitem ITEM_HEAT_ROCK
	giveitem ITEM_LAVA_COOKIE, 3
	setflag FLAG_HOENN_MAGMA_DONE
	call HoennSeek_EventScript_TeamsCheckBoth
	release
	end
HoennSeek_EventScript_MaxieAfter::
	call HoennSeek_EventScript_TeamsLeaderHint
	msgbox HoennSeek_Text_MaxieChallenge, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, HoennSeek_EventScript_TeamsDecline
	cleartrainerflag TRAINER_MAXIE_MT_CHIMNEY
	trainerbattle_no_intro TRAINER_MAXIE_MT_CHIMNEY, HoennSeek_Text_MaxieDefeat
	msgbox HoennSeek_Text_MaxieRematchAfter, MSGBOX_DEFAULT
	release
	end

@ ---------------------------------------------------------------- shared

HoennSeek_EventScript_TeamsDecline::
	msgbox HoennSeek_Text_TeamsDecline, MSGBOX_DEFAULT
	release
	end

@ After the second quest, both leaders head for the Mt. Pyre summit.
HoennSeek_EventScript_TeamsCheckBoth::
	goto_if_unset FLAG_HOENN_AQUA_DONE, HoennSeek_EventScript_TeamsOtherHint
	goto_if_unset FLAG_HOENN_MAGMA_DONE, HoennSeek_EventScript_TeamsOtherHint
	clearflag FLAG_HOENN_HIDE_SUMMIT_LEADERS
	msgbox HoennSeek_Text_TeamsMeetAtPyre, MSGBOX_DEFAULT
	return
HoennSeek_EventScript_TeamsOtherHint::
	msgbox HoennSeek_Text_TeamsOtherAsked, MSGBOX_DEFAULT
	return

@ Leaders' later lines: point at the summit until the double is won.
HoennSeek_EventScript_TeamsLeaderHint::
	goto_if_set FLAG_HOENN_TEAMS_DOUBLE_WON, HoennSeek_EventScript_TeamsHintNone
	goto_if_set FLAG_HOENN_HIDE_SUMMIT_LEADERS, HoennSeek_EventScript_TeamsHintOther
	msgbox HoennSeek_Text_TeamsMeetAtPyre, MSGBOX_DEFAULT
	return
HoennSeek_EventScript_TeamsHintOther::
	msgbox HoennSeek_Text_TeamsOtherAsked, MSGBOX_DEFAULT
HoennSeek_EventScript_TeamsHintNone::
	return

@ ---------------------------------------------------------------- Mt. Pyre summit: the double

HoennSeek_EventScript_SummitLeaders::
	lock
	faceplayer
	goto_if_set FLAG_HOENN_TEAMS_DOUBLE_WON, HoennSeek_EventScript_SummitRematch
	msgbox HoennSeek_Text_SummitScene, MSGBOX_DEFAULT
	msgbox HoennSeek_Text_SummitChallenge, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, HoennSeek_EventScript_TeamsDecline
	call HoennSeek_EventScript_SummitBattle
	msgbox HoennSeek_Text_SummitAfter, MSGBOX_DEFAULT
	setflag FLAG_HOENN_TEAMS_DOUBLE_WON
	release
	end
HoennSeek_EventScript_SummitRematch::
	msgbox HoennSeek_Text_SummitRematch, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, HoennSeek_EventScript_TeamsDecline
	call HoennSeek_EventScript_SummitBattle
	msgbox HoennSeek_Text_SummitRematchAfter, MSGBOX_DEFAULT
	release
	end
HoennSeek_EventScript_SummitBattle::
	cleartrainerflag TRAINER_MAXIE_MOSSDEEP
	cleartrainerflag TRAINER_SHELLY_SEAFLOOR_CAVERN
	trainerbattle_two_trainers TRAINER_MAXIE_MOSSDEEP, HoennSeek_Text_SummitMaxieDefeat, TRAINER_SHELLY_SEAFLOOR_CAVERN, HoennSeek_Text_SummitArchieDefeat
	return

@ Part 16d: May calls after the first Hall of Fame (HoennSeek_EventScript_BMBackCall, hoenn_phone.inc).

@ ---------------------------------------------------------------- Brendan & May

@ First meeting: both wait outside in Littleroot (flag FLAG_HOENN_HIDE_BM_OUTSIDE).
HoennSeek_EventScript_RivalsOutside::
	lock
	faceplayer
	msgbox HoennSeek_Text_RivalsIntro, MSGBOX_DEFAULT
	msgbox HoennSeek_Text_RivalsReady, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, HoennSeek_EventScript_RivalsLater
	msgbox HoennSeek_Text_RivalsGo, MSGBOX_DEFAULT
	call HoennSeek_EventScript_RivalsBattle
	msgbox HoennSeek_Text_RivalsAfter, MSGBOX_DEFAULT
	setflag FLAG_HOENN_BEAT_BM
	call HoennSeek_EventScript_RivalsEggs
	msgbox HoennSeek_Text_RivalsGoingHome, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_LITTLEROOT_BRENDAN
	removeobject LOCALID_LITTLEROOT_MAY
	clearflag FLAG_HOENN_HIDE_BM_HOME
	fadescreen FADE_FROM_BLACK
	release
	end
HoennSeek_EventScript_RivalsLater::
	msgbox HoennSeek_Text_RivalsLater, MSGBOX_DEFAULT
	release
	end

HoennSeek_EventScript_RivalsBattle::
	cleartrainerflag TRAINER_BRENDAN_LILYCOVE_MUDKIP
	cleartrainerflag TRAINER_MAY_LILYCOVE_MUDKIP
	trainerbattle_two_trainers TRAINER_BRENDAN_LILYCOVE_MUDKIP, HoennSeek_Text_BrendanDefeat, TRAINER_MAY_LILYCOVE_MUDKIP, HoennSeek_Text_MayDefeat
	return

@ Treecko from Brendan, Torchic from May, once. Needs two free party slots.
HoennSeek_EventScript_RivalsEggs::
	goto_if_set FLAG_HOENN_BM_EGGS, HoennSeek_EventScript_RivalsEggsDone
	getpartysize
	goto_if_gt VAR_RESULT, 4, HoennSeek_EventScript_RivalsEggsNoRoom
	msgbox HoennSeek_Text_RivalsEggs, MSGBOX_DEFAULT
	giveegg SPECIES_TREECKO
	playfanfare MUS_OBTAIN_ITEM
	message HoennSeek_Text_ReceivedTreeckoEgg
	waitfanfare
	waitmessage
	giveegg SPECIES_TORCHIC
	playfanfare MUS_OBTAIN_ITEM
	message HoennSeek_Text_ReceivedTorchicEgg
	waitfanfare
	waitmessage
	setflag FLAG_HOENN_BM_EGGS
	msgbox HoennSeek_Text_RivalsEggsAfter, MSGBOX_DEFAULT
HoennSeek_EventScript_RivalsEggsDone::
	return
HoennSeek_EventScript_RivalsEggsNoRoom::
	msgbox HoennSeek_Text_RivalsEggsNoRoom, MSGBOX_DEFAULT
	return

@ Later: each at home (flag FLAG_HOENN_HIDE_BM_HOME). Rematches are doubles.
HoennSeek_EventScript_BrendanHome::
	lock
	faceplayer
	call HoennSeek_EventScript_RivalsEggs
	msgbox HoennSeek_Text_BrendanHome, MSGBOX_YESNO
	goto HoennSeek_EventScript_RivalsRematch
HoennSeek_EventScript_MayHome::
	lock
	faceplayer
	call HoennSeek_EventScript_RivalsEggs
	msgbox HoennSeek_Text_MayHome, MSGBOX_YESNO
HoennSeek_EventScript_RivalsRematch::
	goto_if_eq VAR_RESULT, NO, HoennSeek_EventScript_RivalsLater
	call HoennSeek_EventScript_RivalsBattle
	msgbox HoennSeek_Text_RivalsRematchAfter, MSGBOX_DEFAULT
	release
	end

@ ---------------------------------------------------------------- text: Aqua

HoennSeek_Text_MattQuest:
	.string "MATT: Hey! You're the JOHTO champ,\n"
	.string "right? Bwahahaha! Perfect timing!\p"
	.string "TEAM AQUA does sea rescues now.\n"
	.string "But our sub's sonar got fried in\l"
	.string "the last storm.\p"
	.string "CAPT. STERN says the old SCANNER on\n"
	.string "the ABANDONED SHIP could replace it.\p"
	.string "It's on the ship's flooded floor.\n"
	.string "You'll have to DIVE for it.\p"
	.string "Bring it to the boss, ARCHIE, at our\n"
	.string "base in LILYCOVE. Thanks, champ!$"

HoennSeek_Text_MattRemind:
	.string "MATT: The ABANDONED SHIP's off\n"
	.string "ROUTE 108. DIVE down on the inside\l"
	.string "to reach the flooded rooms!$"

HoennSeek_Text_MattHasScanner:
	.string "MATT: You found the SCANNER!\n"
	.string "Take it to ARCHIE in LILYCOVE!$"

HoennSeek_Text_MattChallenge:
	.string "MATT: Bwahahaha! Our sub's pinging\n"
	.string "like new, thanks to you!\p"
	.string "Now, how about a battle to blow\n"
	.string "off some steam?$"

HoennSeek_Text_MattDefeat:
	.string "Bwahahaha! Totally swamped!$"

HoennSeek_Text_MattAfter:
	.string "MATT: You're as tough as the boss\n"
	.string "said! Come back anytime!$"

HoennSeek_Text_ShellyIntro:
	.string "SHELLY: Ahahaha! Surprised? I help\n"
	.string "the WEATHER INSTITUTE now.\p"
	.string "Yes, the same place we once\n"
	.string "raided. Funny how things change.\p"
	.string "MATT at SLATEPORT's harbor could\n"
	.string "use a hand, if you're looking for\l"
	.string "something to do.$"

HoennSeek_Text_ShellyChallenge:
	.string "SHELLY: Ahahaha! So you're the one\n"
	.string "who fixed our sonar.\p"
	.string "I'd love to see that strength up\n"
	.string "close. Battle me?$"

HoennSeek_Text_ShellyDefeat:
	.string "Ahahaha! Simply sublime!$"

HoennSeek_Text_ShellyAfter:
	.string "SHELLY: The forecast says clear\n"
	.string "skies. For you, anyway.$"

HoennSeek_Text_ArchieIntro:
	.string "ARCHIE: Welcome to TEAM AQUA's base!\p"
	.string "We used to dream of flooding the\n"
	.string "world. Now we pull people out of\l"
	.string "the water. Better line of work.\p"
	.string "If you want to help, MATT is at\n"
	.string "SLATEPORT's harbor.$"

HoennSeek_Text_ArchieWaiting:
	.string "ARCHIE: MATT sent you after the\n"
	.string "SCANNER? Good on you.\p"
	.string "The ABANDONED SHIP is off ROUTE 108.\n"
	.string "Mind the flooded floor!$"

HoennSeek_Text_ArchieScanner:
	.string "ARCHIE: Is that the SCANNER?\n"
	.string "Fwahahaha! You actually found it!$"

HoennSeek_Text_ArchieBattle:
	.string "ARCHIE: That sub saves lives,\n"
	.string "and now it can hear again.\p"
	.string "A sailor's thanks deserves a\n"
	.string "sailor's welcome. Let's battle!$"

HoennSeek_Text_ArchieDefeat:
	.string "Fwahahaha! Like riding a tidal wave!$"

HoennSeek_Text_ArchieReward:
	.string "ARCHIE: Take these. A DAMP ROCK keeps\n"
	.string "the rain falling longer.\p"
	.string "And DIVE BALLS, for the sea's\n"
	.string "shyer residents.$"

HoennSeek_Text_ArchieChallenge:
	.string "ARCHIE: Back for another round,\n"
	.string "champ? The sea's always ready.$"

HoennSeek_Text_ArchieRematchAfter:
	.string "ARCHIE: Fwahahaha! Johto grows\n"
	.string "them tough!$"

@ ---------------------------------------------------------------- text: Magma

HoennSeek_Text_TabithaQuest:
	.string "TABITHA: Hehehe! A visitor at our\n"
	.string "geothermal research station!\p"
	.string "Listen, we've got a problem.\n"
	.string "Our TORKOAL reads the vent\l"
	.string "temperatures for us.\p"
	.string "It wandered off chasing heat, and\n"
	.string "I think it went into the FIERY PATH.\p"
	.string "It gets cranky when it's hot. Could\n"
	.string "you bring it back?$"

HoennSeek_Text_TabithaWaiting:
	.string "TABITHA: TORKOAL loves the FIERY\n"
	.string "PATH. Check past the boulders!$"

HoennSeek_Text_TabithaTorkoalBack:
	.string "TABITHA: TORKOAL! There you are!\n"
	.string "Hehehe! Thanks, really.\p"
	.string "The vent readings are back. MAXIE\n"
	.string "is up on MT. CHIMNEY's summit.\p"
	.string "Could you take him the report?\n"
	.string "He'll want to meet you anyway.$"

HoennSeek_Text_TabithaRemind:
	.string "TABITHA: MAXIE's at the top of\n"
	.string "MT. CHIMNEY. Take the cable car!$"

HoennSeek_Text_TabithaChallenge:
	.string "TABITHA: Hehehe! TORKOAL hasn't\n"
	.string "wandered off since.\p"
	.string "How about a battle, for old times'\n"
	.string "sake? Well, new times.$"

HoennSeek_Text_TabithaDefeat:
	.string "Hehehe… Overheated!$"

HoennSeek_Text_TabithaAfter:
	.string "TABITHA: You're stronger than any\n"
	.string "volcano reading I've ever taken.$"

HoennSeek_Text_TorkoalNotYet:
	.string "A TORKOAL is puffing smoke here.\n"
	.string "It looks lost… and very hot.$"

HoennSeek_Text_TorkoalAgitated:
	.string "It's TEAM MAGMA's TORKOAL!\p"
	.string "It's too worked up to come quietly!$"

HoennSeek_Text_TorkoalStillAgitated:
	.string "TORKOAL is still puffing angrily.$"

HoennSeek_Text_TorkoalCalm:
	.string "TORKOAL let out a long, tired puff\n"
	.string "of smoke. It's calm now.$"

HoennSeek_Text_TorkoalFollows:
	.string "{PLAYER} led TORKOAL back toward the\n"
	.string "research station.$"

HoennSeek_Text_MaxieIntro:
	.string "MAXIE: Ah, the TRAINER from JOHTO.\p"
	.string "TEAM MAGMA studies volcanoes now,\n"
	.string "instead of trying to grow them.\p"
	.string "TABITHA runs our station in the old\n"
	.string "hideout. I hear she needs help.$"

HoennSeek_Text_MaxieWaiting:
	.string "MAXIE: TABITHA's TORKOAL ran off?\n"
	.string "Fufufu… it does love the heat.$"

HoennSeek_Text_MaxieReport:
	.string "MAXIE: TABITHA's vent report.\n"
	.string "And TORKOAL is home. Thank you.\p"
	.string "Fufufu… These readings make me\n"
	.string "curious about one more thing.\p"
	.string "How hot does a JOHTO CHAMPION's\n"
	.string "battle run? Allow me to measure!$"

HoennSeek_Text_MaxieDefeat:
	.string "Fufufu… Off the scale!$"

HoennSeek_Text_MaxieReward:
	.string "MAXIE: A HEAT ROCK, to make the sun\n"
	.string "shine longer. And LAVA COOKIES,\l"
	.string "a local specialty.$"

HoennSeek_Text_MaxieChallenge:
	.string "MAXIE: PROF. BIRCH was up here this\n"
	.string "morning. We compare vent readings.\p"
	.string "He wouldn't stop talking about you.\n"
	.string "I could use a reading myself.\l"
	.string "Shall we?$"

HoennSeek_Text_MaxieRematchAfter:
	.string "MAXIE: Consistent results.\n"
	.string "A scientist appreciates that.$"

@ ---------------------------------------------------------------- text: shared + summit

HoennSeek_Text_TeamsDecline:
	.string "Another time, then.$"

HoennSeek_Text_TeamsOtherAsked:
	.string "By the way, the other team's\n"
	.string "leader was asking about you.\p"
	.string "Old rivals keep an eye on each\n"
	.string "other, I suppose.$"

HoennSeek_Text_TeamsMeetAtPyre:
	.string "MAXIE and ARCHIE want to meet you\n"
	.string "together, at the MT. PYRE summit.\p"
	.string "That's where the orbs are kept.\n"
	.string "It seems fitting.$"

HoennSeek_Text_SummitScene:
	.string "MAXIE: Here, of all places…\n"
	.string "We nearly scorched HOENN.\p"
	.string "ARCHIE: And I nearly drowned it.\n"
	.string "Fwahahaha… not my finest hour.\p"
	.string "MAXIE: JOHTO had TEAM ROCKET try to\n"
	.string "come back. They failed.\p"
	.string "ARCHIE: We didn't come back. We\n"
	.string "changed. There's a difference.\p"
	.string "MAXIE: You helped both our teams.\n"
	.string "So let us settle this…\p"
	.string "ARCHIE: …together, this time!$"

HoennSeek_Text_SummitChallenge:
	.string "MAXIE and ARCHIE want to battle\n"
	.string "you together. Accept?$"

HoennSeek_Text_SummitMaxieDefeat:
	.string "MAXIE: The sun sets on us both…$"

HoennSeek_Text_SummitArchieDefeat:
	.string "ARCHIE: Washed out! Fwahahaha!$"

HoennSeek_Text_SummitAfter:
	.string "ARCHIE: Even as partners, our\n"
	.string "weather kept fighting!\p"
	.string "MAXIE: Fufufu. Just like the two\n"
	.string "we once woke.\p"
	.string "MAXIE: We traced GROUDON and KYOGRE\n"
	.string "to the SEAFOAM waters in KANTO.\p"
	.string "ARCHIE: They're resting there.\n"
	.string "Maybe someday they'll come home.\p"
	.string "MAXIE: The old man here keeps the\n"
	.string "ORBS. Talk to him.\p"
	.string "MAXIE: Come back whenever you like.\n"
	.string "We'll be here.$"

HoennSeek_Text_SummitRematch:
	.string "MAXIE: Back for another test?\n"
	.string "ARCHIE: We're always ready!$"

HoennSeek_Text_SummitRematchAfter:
	.string "ARCHIE: Same result! Fwahahaha!\n"
	.string "MAXIE: …Remarkable.$"

@ ---------------------------------------------------------------- text: Brendan & May

HoennSeek_Text_RivalsIntro:
	.string "MAY: You're {PLAYER}! Dad told us\n"
	.string "everything! The JOHTO champion!\p"
	.string "BRENDAN: And you beat WALLACE.\n"
	.string "Not bad.\p"
	.string "MAY: We went to KANTO to challenge\n"
	.string "RED on MT. SILVER… and we lost.\p"
	.string "BRENDAN: We beat the LEAGUE years\n"
	.string "ago, but neither of us wanted the\l"
	.string "title. We just like battling.\p"
	.string "MAY: So! Show us what you've got.\n"
	.string "Both of us. At once!$"

HoennSeek_Text_RivalsReady:
	.string "Battle BRENDAN and MAY together?$"

HoennSeek_Text_RivalsGo:
	.string "BRENDAN: Here we go!\n"
	.string "MAY: Don't hold back!$"

HoennSeek_Text_BrendanDefeat:
	.string "BRENDAN: …Yeah. You're the real deal.$"

HoennSeek_Text_MayDefeat:
	.string "MAY: Wow! Just wow!$"

HoennSeek_Text_RivalsAfter:
	.string "MAY: Maybe you can beat RED!\p"
	.string "BRENDAN: Tell PROF. OAK you beat\n"
	.string "us. He'll let you up MT. SILVER.$"

HoennSeek_Text_RivalsEggs:
	.string "MAY: Oh! And take these. Our\n"
	.string "partners' eggs!$"

HoennSeek_Text_ReceivedTreeckoEgg:
	.string "{PLAYER} received an EGG\n"
	.string "from BRENDAN!$"

HoennSeek_Text_ReceivedTorchicEgg:
	.string "{PLAYER} received an EGG from MAY!$"

HoennSeek_Text_RivalsEggsAfter:
	.string "BRENDAN: A TREECKO, from\n"
	.string "my SCEPTILE.\p"
	.string "MAY: And a TORCHIC, from my\n"
	.string "BLAZIKEN! Raise them well!$"

HoennSeek_Text_RivalsEggsNoRoom:
	.string "MAY: We have EGGS for you, but\n"
	.string "your party's full!\p"
	.string "Make room for two, then come see\n"
	.string "us at home!$"

HoennSeek_Text_RivalsGoingHome:
	.string "BRENDAN: We'll be home for a while.\n"
	.string "Come by for a rematch anytime.\p"
	.string "MAY: Doubles only! See you!$"

HoennSeek_Text_RivalsLater:
	.string "MAY: Okay! We'll be around.$"

HoennSeek_Text_BrendanHome:
	.string "BRENDAN: Hey, {PLAYER}. Up for a\n"
	.string "rematch? I'll get MAY.$"

HoennSeek_Text_MayHome:
	.string "MAY: {PLAYER}! Rematch? I'll call\n"
	.string "BRENDAN over!$"

HoennSeek_Text_RivalsRematchAfter:
	.string "MAY: We'll beat you one day!\n"
	.string "BRENDAN: …Maybe.$"
