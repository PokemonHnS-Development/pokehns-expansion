Route50_House1_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route50_House1_hns_OnTransition
	.byte 0


Route50_House1_hns_OnTransition::
	end

Route50_House1_EventScript_AddLily3::
    setobjectxyperm LOCALID_LILY1, 20, 8
	end

Route50_EventScript_Lily1::
    lock
	goto_if_eq VAR_PLATECOUNTER, 17, Route50_EventScript_Lily2
	msgbox Route50_House1_ShesAsleep_Text MSGBOX_DEFAULT
	release
	end

Route50_House1_ShesAsleep_Text:
    .string "She appears to be in a deep sleep..\p"
	.string "Better leave her alone and\n"
	.string "and come back later.$"

Route50_EventScript_Lily2::
    faceplayer
	goto_if_set FLAG_ROUTE50_LILY_GIFT, Route50_EventScript_Gift_Gotten
	msgbox Route50_House1_HelloThere_Text MSGBOX_DEFAULT
	msgbox Route50_GiftText, MSGBOX_DEFAULT
	giveitem ITEM_BLACK_FLUTE, 1
	giveitem ITEM_WHITE_FLUTE, 1
	compare VAR_RESULT, 0
	goto_if_eq Route50_EventScript_BagMightBeFull
	setflag FLAG_ROUTE50_LILY_GIFT
	msgbox Route50_Lily_Hint_Text MSGBOX_DEFAULT
	release
	end

Route50_EventScript_BagMightBeFull::
	msgbox Route50_Text_BagIsFull, MSGBOX_DEFAULT
	release
	end

Route50_Text_BagIsFull:
	.string "Your BAG looks pretty packed there.\n"
	.string "Could you please make some\l"
	.string "space first?\p"
    .string "I'd really like to give this to you..$"

Route50_House1_HelloThere_Text:
    .string "Hello there, Who might you be?\p"
	.string "Ah! Your name is {PLAYER}?\n"
	.string "I heard about you from Mr.Steven!\p"
	.string "He was just here checking up on me\n"
	.string "not long ago and he told me all about\l"
	.string "your adventures together!$"

Route50_GiftText:
    .string "Here {PLAYER}, I want to\n"
	.string "Give these to you..!\p"

Route50_Lily_Hint_Text:
    .string "Like how you helped balanced\n"
	.string "the odds in humanities favor,\l"
	.string "I hope these help balance your\l"
	.string "travels in the wild..!$"

Route50_EventScript_Gift_Gotten::
	msgbox Route50_HelloAgainPlayer_Text MSGBOX_DEFAULT
	release
	end

Route50_HelloAgainPlayer_Text:
    .string "I hope these help you like\n"
	.string "like they helped me..$"

Route50_EventScript_Sailor::
    lock
	faceplayer
    goto_if_eq VAR_PLATECOUNTER, 17, Route50_EventScript_Sailor2
    msgbox Route50_Sailor_ShesAsleep_Text MSGBOX_DEFAULT
	release
	end

Route50_Sailor_ShesAsleep_Text:
    .string "After those nerds in the ruins\n"
	.string "opened up that big building,\l"
	.string "my poor baby girl has fallen ill..\p"
	.string "I hope they figure out what\n"
	.string "happened soon...$"

Route50_EventScript_Sailor2::
    msgbox Route50_Sailor_ShesBetter_Text MSGBOX_DEFAULT
	release
	end

Route50_Sailor_ShesBetter_Text:
    .string "{PLAYER}! I heard it all from that\n"
	.string "Visitin' Champion, in a way\l"
	.string "you helped my daughter didn't you?\p"
	.string "Thank you {PLAYER}, thank you.$"
