PalletTown_RedsHouse_1F_hns_MapScripts::
	.byte 0

PalletTown_RedsHouse_1F_EventScript_Mom::
	lock
	faceplayer
	goto_if_ge VAR_TEMP_0, 1, PalletTown_RedsHouse_1F_EventScript_MomAfter
	msgbox RedsHouse_Text_Mom1, MSGBOX_DEFAULT
	closemessage
	setvar VAR_TEMP_0, 1
	release
	end

PalletTown_RedsHouse_1F_EventScript_MomAfter::
	msgbox RedsHouse_Text_Mom2, MSGBOX_DEFAULT
	closemessage
	release
	end

PalletTown_RedsHouse_1F_EventScript_TV::
	msgbox RedsHouse_Text_TV, MSGBOX_SIGN
	end

RedsHouse_Text_Mom1:
	.string "היי!\p"
	.string "רד לא בבית כבר הרבה זמן.\p"
	.string "הוא גם לא התקשר, אז אין לי מושג\n"
	.string "איפה הוא או מה הוא עושה.\p"
	.string "אומרים שאין חדשות - חדשות טובות,\n"
	.string "אבל אני בכל זאת דואגת לו.$"

RedsHouse_Text_Mom2:
	.string "אני דואגת שרד ייפגע או יחלה,\n"
	.string "אבל ככה זה עם בנים.\p"
	.string "אני גאה בו שהוא עושה את מה\n"
	.string "שהוא רוצה לעשות.$"

RedsHouse_Text_TV:
	.string "יש פה תוכניות שלא משודרות\n"
	.string "בג'וטו…$"
