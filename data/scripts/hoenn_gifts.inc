@ Hoenn & Seek (part 19): Hoenn NPCs whose key item you already got in Johto or
@ Kanto (Old/Good/Super Rod, Coin Case). Instead of a second copy, they hand
@ over something useful. Hooked in with a checkitem before each Emerald gift.

HoennSeek_EventScript_HaveOldRod::
	msgbox HoennSeek_Text_HaveOldRod, MSGBOX_DEFAULT
	giveitem ITEM_NET_BALL, 5
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_OLD_ROD
	msgbox DewfordTown_Text_ThrowInFishingAdvice, MSGBOX_DEFAULT
	release
	end

HoennSeek_EventScript_HaveGoodRod::
	msgbox HoennSeek_Text_HaveGoodRod, MSGBOX_DEFAULT
	giveitem ITEM_LURE_BALL, 5
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_GOOD_ROD
	msgbox Route118_Text_TryYourLuckFishing, MSGBOX_DEFAULT
	release
	end

HoennSeek_EventScript_HaveSuperRod::
	msgbox HoennSeek_Text_HaveSuperRod, MSGBOX_DEFAULT
	giveitem ITEM_DIVE_BALL, 5
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_SUPER_ROD
	release
	end

HoennSeek_EventScript_HaveCoinCase::
	msgbox HoennSeek_Text_HaveCoinCase, MSGBOX_DEFAULT
	removeitem ITEM_HARBOR_MAIL
	addcoins 300
	playfanfare MUS_OBTAIN_ITEM
	message HoennSeek_Text_Got300Coins
	waitfanfare
	waitmessage
	setflag FLAG_RECEIVED_COIN_CASE
	goto MauvilleCity_House2_EventScript_ReceivedCoinCase

HoennSeek_Text_HaveOldRod:
	.string "Hm? You've already got an OLD ROD?\n"
	.string "A JOHTO one! Well, I'll be.\p"
	.string "Then take these instead. A NET BALL\n"
	.string "works wonders on anything you hook.$"

HoennSeek_Text_HaveGoodRod:
	.string "Wait… You've got a GOOD ROD already!\p"
	.string "Identical minds, identical rods!\n"
	.string "Then these are for you instead.\p"
	.string "LURE BALLS are made for POKéMON\n"
	.string "you fish up.$"

HoennSeek_Text_HaveSuperRod:
	.string "Oh, you already have a SUPER ROD!\n"
	.string "Then you know what's down there.\p"
	.string "Take these DIVE BALLS for whatever\n"
	.string "you find under the sea instead.$"

HoennSeek_Text_HaveCoinCase:
	.string "Oh, you already have a COIN CASE?\n"
	.string "From the JOHTO GAME CORNER, I bet.\p"
	.string "Then I'll pay for the MAIL in COINS.\n"
	.string "Here you go!$"

HoennSeek_Text_Got300Coins:
	.string "{PLAYER} received 300 COINS.$"
