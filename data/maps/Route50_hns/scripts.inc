Route50_hns_MapScripts::
	.byte 0

Route50_EventScript_BlackBelt1::
	msgbox Route50_Text_BlackBelt1, MSGBOX_NPC
	end

Route50_Text_BlackBelt1::
	.string "The body must be hardened\n"
    .string "and the mind strengthened\l"
    .string "in the harshest of conditions!$"

Route50_EventScript_BlackBelt2::
	msgbox Route50_Text_BlackBelt2, MSGBOX_NPC
	end

Route50_Text_BlackBelt2::
    .string "Phew!\p"
    .string "I'm not as hardcore as he is.\p"
	.string "There's really not much else\n"
    .string "to do here but train.$"
  

Route50_EventScript_Wessel::
	msgbox Route50_Text_WesselBefore, MSGBOX_NPC
	end

Route50_Text_WesselBefore::
	.string "Incredible, A VOLTORB!\p"
    .string "But it appears to be made\n"
    .string "of... Wood?\p"
    .string "My hypothesis that this route\n"
    .string "would contain many steel types\l"
    .string "is disproven yet again.\p"
    .string "But why else would I have found\n"
    .string "this STEEL PLATE here?\p"
    .string "I must collect more data!$"

Route50_EventScript_Finley::
	msgbox Route50_Text_FinleyBefore, MSGBOX_NPC
	end

Route50_Text_FinleyBefore::
	.string "How are the villagers treating\n"
    .string "you?\p"
    .string "They can be very unwelcoming to\n"
    .string "strangers.\p"
    .string "But meeting new people is one\n"
    .string "of life's greatest joys.\p"
    .string "One day, I hope to meet CHAMPION\n"
    .string "LANCE.\p"
    .string "He is a legendary dragon tamer,\n"
    .string "much like myself.\l"
    .string "Who am I?\p"
    .string "Well, I am FINLEY, keeper of the\n"
    .string "DRACO PLATE.$"

Route50_EventScript_Item_ULtraBall::
    finditem ITEM_ULTRA_BALL
    end

Route50_EventScript_Item_Big_Nugget::
    finditem ITEM_BIG_NUGGET
    end
