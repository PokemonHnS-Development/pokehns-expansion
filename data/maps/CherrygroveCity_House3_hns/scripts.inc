CherrygroveCity_House3_hns_MapScripts::
	.byte 0

CherrygroveCity_House3_EventScript_Boy::
	lock
	faceplayer
	msgbox CherrygroveCity_EvolutionHouse_Text_Youngster, MSGBOX_DEFAULT
	closemessage
	release
	end

CherrygroveCity_House3_EventScript_Girl::
	lock
	faceplayer
	msgbox CherrygroveCity_EvolutionHouse_Text_Lass, MSGBOX_DEFAULT
	closemessage
	release
	end

CherrygroveCity_EvolutionHouse_Text_Youngster:
	.string "פוקימונים צוברים ניסיון\n"
	.string "בקרב ומשנים את צורתם.$"

CherrygroveCity_EvolutionHouse_Text_Lass:
	.string "פוקימונים משתנים?\p"
	.string "הייתי בהלם אם אחד מהם\n"
	.string "היה עושה את זה!$"
