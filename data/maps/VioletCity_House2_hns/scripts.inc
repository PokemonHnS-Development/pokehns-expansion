VioletCity_House2_hns_MapScripts::
	.byte 0

VioletCity_House2_EventScript_Lass::
	lock
	faceplayer
	msgbox VioletCity_NicknameHouse_Text_Lass, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_House2_EventScript_Teacher::
	lock
	faceplayer
	msgbox VioletCity_NicknameHouse_Text_Teacher, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_House2_EventScript_Pidgey::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_PIDGEY, CRY_MODE_NORMAL
	msgbox VioletCity_NicknameHouse_Text_Bird, MSGBOX_DEFAULT
	waitmoncry
	release
	end

VioletCity_NicknameHouse_Text_Teacher:
	.string "היא משתמשת בשמות של\n"
	.string "המאכלים האהובים עליה.\p"
	.string "בכינויים שהיא נותנת לפוקימונים\n"
	.string "שלה, אני מתכוונת.$"

VioletCity_NicknameHouse_Text_Lass:
	.string "אני קוראת לפידג'י שלי תות!$"

VioletCity_NicknameHouse_Text_Bird:
	.string "תות: פיג'י!$"
