@ Hoenn & Seek (part 8): Oak's TIDAL TICKET, the Vermilion <-> Hoenn ferry,
@ and the Mt. Silver gate (opens once Brendan & May are beaten, part 16a).

@ ---------------------------------------------------------------- Oak (PalletTown_Lab_hns)

@ Called when Oak sees all 16 badges. Replaces HnS's "Mt. Silver is open".
HoennSeek_EventScript_OakGivesTicket::
	msgbox HoennSeek_Text_OakTicket, MSGBOX_DEFAULT
	giveitem ITEM_TIDAL_TICKET
	msgbox HoennSeek_Text_OakTicketExplain, MSGBOX_DEFAULT
	return

@ Called on later visits, before Oak's Pokédex check.
HoennSeek_EventScript_OakHoennStatus::
	goto_if_set FLAG_HOENN_BEAT_BM, HoennSeek_EventScript_OakSilverOpen
	msgbox HoennSeek_Text_OakGoToHoenn, MSGBOX_DEFAULT
	return

HoennSeek_EventScript_OakSilverOpen::
	goto_if_defeated TRAINER_RED_HNS, HoennSeek_EventScript_OakRedBeaten
	msgbox HoennSeek_Text_OakSilverOpen, MSGBOX_DEFAULT
	return

@ Part 16d: after Red, Oak has already told Birch and Norman (May's call says so).
HoennSeek_EventScript_OakRedBeaten::
	msgbox HoennSeek_Text_OakRedBeaten, MSGBOX_DEFAULT
	return

@ ---------------------------------------------------------------- Vermilion port (HnS)

@ HnS's destination menu plus SLATEPORT CITY. Seven entries don't fit HnS's fixed
@ multichoice above the text box, so this one scrolls (6 rows visible).
HoennSeek_EventScript_VermilionDestinations::
	message VermilionPort_Text_WhereSail
	waitmessage
	dynmultichoice 20, 0, FALSE, 6, 0, DYN_MULTICHOICE_CB_NONE, gText_Olivine, gText_SouthernIsland, gText_BirthIsland, gText_FarawayIsland, gText_BattleFrontier, gText_SlateportCity, gText_Exit
	switch VAR_RESULT
	case 0, VermilionPort_EventScript_ChoseOlivine
	case 1, VermilionPort_EventScript_ChoseSouthernIsland
	case 2, VermilionPort_EventScript_ChoseBirthIsland
	case 3, VermilionPort_EventScript_ChoseFarawayIsland
	case 4, VermilionPort_EventScript_ChoseBattleFrontier
	case 5, VermilionPort_EventScript_ChoseSlateport
	goto VermilionPort_EventScript_Sailor_Refused
	end

VermilionPort_EventScript_ChoseSlateport::
	closemessage
	delay 20
	checkitem ITEM_TIDAL_TICKET
	bufferitemname STR_VAR_1, ITEM_TIDAL_TICKET
	goto_if_eq VAR_RESULT, FALSE, VermilionPort_EventScript_Sailor_NoCredentials
	call VermilionPort_EventScript_EnterShip
	warpsilent MAP_SLATEPORT_CITY_HARBOR, 8, 11
	waitstate
	release
	end

@ ---------------------------------------------------------------- Slateport / Lilycove harbors (Emerald)

HoennSeek_EventScript_SlateportFerry::
	lock
	faceplayer
	message HoennSeek_Text_FerryWhereTo
	waitmessage
	dynmultichoice 17, 4, FALSE, 4, 0, DYN_MULTICHOICE_CB_NONE, HoennSeek_Text_DestVermilion, HoennSeek_Text_DestLilycove, HoennSeek_Text_DestFrontier, HoennSeek_Text_DestCancel
	switch VAR_RESULT
	case 0, HoennSeek_EventScript_SlateportToVermilion
	case 1, HoennSeek_EventScript_SlateportToLilycove
	case 2, HoennSeek_EventScript_SlateportToFrontier
	goto HoennSeek_EventScript_FerryCancel
	end

HoennSeek_EventScript_SlateportToVermilion::
	call SlateportCity_Harbor_EventScript_BoardFerry
	warp MAP_VERMILION_CITY_PORT_INSIDE_HNS, 8, 9
	waitstate
	release
	end

HoennSeek_EventScript_SlateportToLilycove::
	call SlateportCity_Harbor_EventScript_BoardFerry
	warp MAP_LILYCOVE_CITY_HARBOR, 8, 11
	waitstate
	release
	end

HoennSeek_EventScript_SlateportToFrontier::
	call SlateportCity_Harbor_EventScript_BoardFerry
	warp MAP_BATTLE_FRONTIER_OUTSIDE_WEST_HNS, 20, 67
	waitstate
	release
	end

HoennSeek_EventScript_LilycoveFerry::
	lock
	faceplayer
	message HoennSeek_Text_FerryWhereTo
	waitmessage
	dynmultichoice 17, 4, FALSE, 4, 0, DYN_MULTICHOICE_CB_NONE, HoennSeek_Text_DestVermilion, HoennSeek_Text_DestSlateport, HoennSeek_Text_DestFrontier, HoennSeek_Text_DestCancel
	switch VAR_RESULT
	case 0, HoennSeek_EventScript_LilycoveToVermilion
	case 1, HoennSeek_EventScript_LilycoveToSlateport
	case 2, HoennSeek_EventScript_LilycoveToFrontier
	goto HoennSeek_EventScript_FerryCancel
	end

HoennSeek_EventScript_LilycoveToVermilion::
	call LilycoveCity_Harbor_EventScript_BoardFerry
	warp MAP_VERMILION_CITY_PORT_INSIDE_HNS, 8, 9
	waitstate
	release
	end

HoennSeek_EventScript_LilycoveToSlateport::
	call LilycoveCity_Harbor_EventScript_BoardFerry
	warp MAP_SLATEPORT_CITY_HARBOR, 8, 11
	waitstate
	release
	end

HoennSeek_EventScript_LilycoveToFrontier::
	call LilycoveCity_Harbor_EventScript_BoardFerry
	warp MAP_BATTLE_FRONTIER_OUTSIDE_WEST_HNS, 20, 67
	waitstate
	release
	end

HoennSeek_EventScript_FerryCancel::
	msgbox SlateportCity_Harbor_Text_SailAnotherTime, MSGBOX_DEFAULT
	release
	end

@ ---------------------------------------------------------------- Mt. Silver gate (ReceptionGate_hns)

HoennSeek_EventScript_SilverGateOnTransition::
	goto_if_unset FLAG_HOENN_BEAT_BM, HoennSeek_EventScript_SilverGateEnd
	setflag FLAG_INDIGOJUNCTION_HIDE_SILVER_GUARD
	setflag FLAG_HOENN_SILVER_GATE_OPEN
	goto_if_ne VAR_ROUTE28_SCIENTIST, 0, HoennSeek_EventScript_SilverGateEnd
	setvar VAR_ROUTE28_SCIENTIST, 1
HoennSeek_EventScript_SilverGateEnd::
	end

HoennSeek_EventScript_SilverGuard::
	goto_if_set FLAG_HOENN_BEAT_BM, HoennSeek_EventScript_SilverGuardOpen
	msgbox HoennSeek_Text_SilverGuardClosed, MSGBOX_NPC
	end

HoennSeek_EventScript_SilverGuardOpen::
	msgbox VictoryRoadGate_Text_LeftBlackBelt, MSGBOX_NPC
	end

@ ---------------------------------------------------------------- Text

HoennSeek_Text_OakTicket:
	.string "OAK: Wow! That's excellent!\p"
	.string "You collected the BADGES of GYMS\n"
	.string "in KANTO. Well done!\p"
	.string "I was right in my assessment of\n"
	.string "you.\p"
	.string "MT.SILVER is off limits to all but\n"
	.string "the very strongest trainers.\p"
	.string "Before I make an exception, I'd\n"
	.string "like you to see more of the world.\p"
	.string "My friend PROF. BIRCH studies\n"
	.string "POKéMON far to the south, in HOENN.\p"
	.string "Here, take this with you.$"

HoennSeek_Text_OakTicketExplain:
	.string "OAK: The S.S. TIDAL sails from\n"
	.string "VERMILION CITY to SLATEPORT CITY.\p"
	.string "One of BIRCH's aides will meet you\n"
	.string "at the harbor. BIRCH has something\l"
	.string "for you, too.\p"
	.string "HOENN has a LEAGUE of its own, and\n"
	.string "its CHAMPION is a man named WALLACE.\p"
	.string "Prove yourself in HOENN, and I'll\n"
	.string "see that MT.SILVER is opened for you.$"

HoennSeek_Text_OakGoToHoenn:
	.string "OAK: Show your TIDAL TICKET at the\n"
	.string "VERMILION CITY port, and the S.S.\l"
	.string "TIDAL will take you to HOENN.\p"
	.string "Prove yourself in HOENN, and\n"
	.string "MT.SILVER will be open.\p"
	.string "BIRCH and I talk every week, so\n"
	.string "I'll hear how you're doing!$"

HoennSeek_Text_OakRedBeaten:
	.string "OAK: You beat RED! I phoned BIRCH\n"
	.string "and NORMAN the moment I heard.\p"
	.string "Their kids will be calling you\n"
	.string "any minute now, I'm sure!$"

HoennSeek_Text_OakSilverOpen:
	.string "OAK: You beat BRENDAN and MAY, the\n"
	.string "pair who took on RED himself!\p"
	.string "As promised, MT.SILVER is open to\n"
	.string "you. Go up to INDIGO PLATEAU, and\l"
	.string "you can reach it from there.$"

HoennSeek_Text_FerryWhereTo:
	.string "Welcome aboard the S.S. TIDAL!\n"
	.string "Where would you like to sail?$"

HoennSeek_Text_DestVermilion:
	.string "VERMILION CITY$"

HoennSeek_Text_DestSlateport:
	.string "SLATEPORT CITY$"

HoennSeek_Text_DestLilycove:
	.string "LILYCOVE CITY$"

HoennSeek_Text_DestFrontier:
	.string "BATTLE FRONTIER$"

HoennSeek_Text_DestCancel:
	.string "CANCEL$"

HoennSeek_Text_SilverGuardClosed:
	.string "This way leads to MT.SILVER, but\n"
	.string "it's off limits.\p"
	.string "PROF. OAK says only a trainer who\n"
	.string "has beaten HOENN's strongest pair\l"
	.string "may go through.$"
