Route28_House_hns_MapScripts::
	.byte 0

Route28House_EventScript_Celebrity::
	lock
	faceplayer
	goto_if_set FLAG_GOT_TM_STEEL_WING, Route28House_EventScript_CelebrityAfter
	msgbox Route28House_Text_Celebrity1, MSGBOX_NPC
	giveitem ITEM_TM_STEEL_WING
	setflag FLAG_GOT_TM_STEEL_WING
Route28House_EventScript_CelebrityAfter::
	msgbox Route28House_Text_Celebrity2, MSGBOX_NPC
	release
	end

Route28House_Text_Celebrity1:
	.string "אוי ואבוי. מצאת אותי.\p"
	.string "בבקשה, אל תספר לאף אחד עליי.\p"
	.string "אתן לך את זה אם תשמור\n"
	.string "על הסוד שלי. בבקשה?$"

Route28House_Text_Celebrity2:
	.string "לא קל להיות כוכבת-על.\p"
	.string "לכל מקום שאני הולכת,\n"
	.string "אנשים רודפים אחריי.\p"
	.string "אני רק רוצה שיעזבו אותי בשקט…$"

Route28House_Text_Fearow:
	.string "FEAROW: Feero!$"

