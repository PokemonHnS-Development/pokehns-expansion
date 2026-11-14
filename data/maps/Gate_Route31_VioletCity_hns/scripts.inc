Gate_Route31_VioletCity_hns_MapScripts::
	.byte 0

Gate_Route31_VioletCity_EventScript_Policeman::
	lock
	faceplayer
	msgbox Gate_Route31_VioletCity_Text_Policeman, MSGBOX_DEFAULT
	closemessage
	release
	end

Gate_Route31_VioletCity_EventScript_CooltrainerF::
	lock
	faceplayer
	msgbox Gate_Route31_VioletCity_Text_CooltrainerF, MSGBOX_DEFAULT
	closemessage
	release
	end

Gate_Route31_VioletCity_Text_Policeman:
	.string "שלום! ביקרת כבר\n"
	.string "במגדל הנבט?$"

Gate_Route31_VioletCity_Text_CooltrainerF:
	.string "ראיתי בחוץ את הפוקימון\n"
	.string "הכי חמוד שיש.\p"
	.string "הוא נראה ממש כמו פיקאצ'ו!$"
