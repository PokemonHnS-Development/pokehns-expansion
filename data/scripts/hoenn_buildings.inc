@ Hoenn & Seek 2.0 (parts 8b-11): hand-written scripts for opened buildings (shops, the rater).
@ The buildings, their NPCs and every text live in data/hoenn/buildings.json;
@ tools/hoenn/gen_hoenn_buildings.py writes each map's scripts.inc, where an NPC
@ with "script" jumps here and texts are named <Map>_Text_<Key>.

@ ---- Olivine City: retired captain (friendship rater) -----------------------
@ Rates the lead Pokémon's friendship (Emerald's GetLeadMonFriendshipScore, 0-6).
HoennSeek_EventScript_OlivineCaptain::
	lock
	faceplayer
	bufferleadmonspeciesname STR_VAR_1
	msgbox OlivineCity_CaptainsHouse_hoenn_Text_RateIntro, MSGBOX_DEFAULT
	specialvar VAR_RESULT, GetLeadMonFriendshipScore
	switch VAR_RESULT
	case FRIENDSHIP_NONE, HoennSeek_EventScript_OlivineCaptain0
	case FRIENDSHIP_1_TO_49, HoennSeek_EventScript_OlivineCaptain1
	case FRIENDSHIP_50_TO_99, HoennSeek_EventScript_OlivineCaptain2
	case FRIENDSHIP_100_TO_149, HoennSeek_EventScript_OlivineCaptain3
	case FRIENDSHIP_150_TO_199, HoennSeek_EventScript_OlivineCaptain4
	case FRIENDSHIP_200_TO_254, HoennSeek_EventScript_OlivineCaptain5
	msgbox OlivineCity_CaptainsHouse_hoenn_Text_Rate6, MSGBOX_DEFAULT
	release
	end

HoennSeek_EventScript_OlivineCaptain0::
	msgbox OlivineCity_CaptainsHouse_hoenn_Text_Rate0, MSGBOX_DEFAULT
	release
	end

HoennSeek_EventScript_OlivineCaptain1::
	msgbox OlivineCity_CaptainsHouse_hoenn_Text_Rate1, MSGBOX_DEFAULT
	release
	end

HoennSeek_EventScript_OlivineCaptain2::
	msgbox OlivineCity_CaptainsHouse_hoenn_Text_Rate2, MSGBOX_DEFAULT
	release
	end

HoennSeek_EventScript_OlivineCaptain3::
	msgbox OlivineCity_CaptainsHouse_hoenn_Text_Rate3, MSGBOX_DEFAULT
	release
	end

HoennSeek_EventScript_OlivineCaptain4::
	msgbox OlivineCity_CaptainsHouse_hoenn_Text_Rate4, MSGBOX_DEFAULT
	release
	end

HoennSeek_EventScript_OlivineCaptain5::
	msgbox OlivineCity_CaptainsHouse_hoenn_Text_Rate5, MSGBOX_DEFAULT
	release
	end

@ ---- Olivine City: fishing tackle shop ----------------------------------------
HoennSeek_EventScript_OlivineTackleShop::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart HoennSeek_OlivineTackleShop_Items
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
HoennSeek_OlivineTackleShop_Items:
	.2byte ITEM_NET_BALL
	.2byte ITEM_DIVE_BALL
	.2byte ITEM_LURE_BALL
	.2byte ITEM_REPEL
	.2byte ITEM_SUPER_REPEL
	.2byte ITEM_MAX_REPEL
	pokemartlistend

@ The lighthouse keeper's wife's daily find is a generated daily_gift (buildings.json).

@ ---- Melemele Island: surf shop (part 11) --------------------------------------
HoennSeek_EventScript_MelemeleSurfShop::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart HoennSeek_MelemeleSurfShop_Items
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
HoennSeek_MelemeleSurfShop_Items:
	.2byte ITEM_DIVE_BALL
	.2byte ITEM_NET_BALL
	.2byte ITEM_SEA_INCENSE
	.2byte ITEM_WAVE_INCENSE
	.2byte ITEM_MYSTIC_WATER
	pokemartlistend
