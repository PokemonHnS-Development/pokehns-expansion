@ Hoenn & Seek (part 11+): story items with new givers in the post-Emerald Hoenn.
@ See claude/hns-hoenn-world-details.md ("Story items: who gives them now").

@ ---------------------------------------------------------------- Flannery: Go-Goggles
@ Called from LavaridgeTown_Gym_1F_EventScript_FlanneryDefeated (Emerald's rival used to bring them).
HoennSeek_EventScript_FlanneryGoGoggles::
	goto_if_set FLAG_RECEIVED_GO_GOGGLES, HoennSeek_EventScript_FlanneryGoGogglesEnd
	msgbox HoennSeek_Text_FlanneryGoGoggles, MSGBOX_DEFAULT
	giveitem ITEM_GO_GOGGLES
	setflag FLAG_RECEIVED_GO_GOGGLES
	msgbox HoennSeek_Text_FlanneryGoGogglesExplain, MSGBOX_DEFAULT
HoennSeek_EventScript_FlanneryGoGogglesEnd::
	return

@ ---------------------------------------------------------------- Wattson: Basement Key, then TM Thunderbolt
@ Called from MauvilleCity_Gym_EventScript_WattsonDefeated.
HoennSeek_EventScript_WattsonBasementKey::
	goto_if_set FLAG_GOT_BASEMENT_KEY_FROM_WATTSON, HoennSeek_EventScript_WattsonBasementKeyEnd
	msgbox MauvilleCity_Text_WattsonNeedFavorTakeKey, MSGBOX_DEFAULT
	giveitem ITEM_BASEMENT_KEY
	setflag FLAG_GOT_BASEMENT_KEY_FROM_WATTSON
	msgbox MauvilleCity_Text_WattsonWontBeChallenge, MSGBOX_DEFAULT
HoennSeek_EventScript_WattsonBasementKeyEnd::
	return

@ After the New Mauville generator is off, gym Wattson gives the reward his outdoor self used to.
HoennSeek_EventScript_WattsonThunderbolt::
	msgbox MauvilleCity_Text_WattsonThanksTakeTM, MSGBOX_DEFAULT
	giveitem ITEM_TM_THUNDERBOLT
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_GOT_TM_THUNDERBOLT_FROM_WATTSON
	msgbox MauvilleCity_Text_WattsonYoungTakeCharge, MSGBOX_DEFAULT
	release
	end

@ ---------------------------------------------------------------- Mr. Stone (Devon Corp 3F)
@ HnS already gives the Exp. Share at new game, so his thank-you gift is a Lucky Egg.
@ FLAG_RECEIVED_EXP_SHARE (Hoenn-owned) records that he gave it.
HoennSeek_EventScript_MrStone::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_EXP_SHARE, HoennSeek_EventScript_MrStoneAfterGift
	msgbox HoennSeek_Text_MrStoneWelcome, MSGBOX_DEFAULT
	giveitem ITEM_LUCKY_EGG
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_EXP_SHARE
	msgbox HoennSeek_Text_MrStoneFieldTest, MSGBOX_DEFAULT
	goto HoennSeek_EventScript_MrStoneEnd
HoennSeek_EventScript_MrStoneAfterGift::
	msgbox HoennSeek_Text_MrStoneAfterGift, MSGBOX_DEFAULT
HoennSeek_EventScript_MrStoneEnd::
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

@ ---------------------------------------------------------------- Text

HoennSeek_Text_FlanneryGoGoggles:
	.string "FLANNERY: Oh, and one more thing!\p"
	.string "If you're heading into the desert on\n"
	.string "ROUTE 111, you'll want these.$"

HoennSeek_Text_FlanneryGoGogglesExplain:
	.string "FLANNERY: With those GO-GOGGLES on,\n"
	.string "the sandstorm won't stop you.\p"
	.string "Go see what's hiding out there!$"

HoennSeek_Text_MrStoneWelcome:
	.string "MR. STONE: Ah, a TRAINER from far\n"
	.string "away! Welcome to DEVON.\p"
	.string "A few years ago, some of HOENN's young\n"
	.string "TRAINERS helped us through a great\l"
	.string "deal of trouble.\p"
	.string "I never could thank them enough.\n"
	.string "So please, take this instead!$"

HoennSeek_Text_MrStoneFieldTest:
	.string "MR. STONE: That LUCKY EGG will help\n"
	.string "your POKéMON grow faster.\p"
	.string "Oh, and if you pass through ROUTE 120,\n"
	.string "say hello to our field tester.\p"
	.string "We're trying out a new DEVON SCOPE\n"
	.string "out there. It's quite something!$"

HoennSeek_Text_MrStoneAfterGift:
	.string "MR. STONE: My son, STEVEN? He's off\n"
	.string "somewhere digging up rare stones, no\l"
	.string "doubt.\p"
	.string "He was always that way, even as a boy.$"

@ Steven's house, Mossdeep (part 12): the Beldum ball now holds a stone from
@ Steven's collection. Metagrossite once the player has a Mega Ring, otherwise
@ a Shiny Stone; decided when it's picked up.
HoennSeek_EventScript_StevensStone::
	lockall
	msgbox HoennSeek_Text_StevensStoneNote, MSGBOX_DEFAULT
	checkitem ITEM_MEGA_RING
	goto_if_eq VAR_RESULT, TRUE, HoennSeek_EventScript_StevensStoneMega
	giveitem ITEM_SHINY_STONE
	goto HoennSeek_EventScript_StevensStoneGot

HoennSeek_EventScript_StevensStoneMega::
	giveitem ITEM_METAGROSSITE
HoennSeek_EventScript_StevensStoneGot::
	goto_if_eq VAR_RESULT, FALSE, HoennSeek_EventScript_StevensStoneBagFull
	removeobject LOCALID_STEVENS_HOUSE_BALL
	setflag FLAG_HIDE_MOSSDEEP_CITY_STEVENS_HOUSE_BELDUM_POKEBALL
	releaseall
	end

HoennSeek_EventScript_StevensStoneBagFull::
	msgbox gText_TooBadBagIsFull, MSGBOX_DEFAULT
	releaseall
	end

HoennSeek_Text_StevensStoneNote:
	.string "There's a note tucked under the\n"
	.string "POKé BALL.\p"
	.string "“One of my favorite finds. Take it\n"
	.string "with you, whoever you are. --STEVEN”$"
