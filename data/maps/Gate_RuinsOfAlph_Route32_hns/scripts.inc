Gate_RuinsOfAlph_Route32_hns_MapScripts::
	.byte 0


Gate_RuinsOfAlph_Route32_EventScript_PokefanM::
	lock
	faceplayer
	msgbox Gate_RuinsOfAlph_Route32_Text_PokefanM, MSGBOX_DEFAULT
	closemessage
	release
	end

Gate_RuinsOfAlph_Route32_EventScript_Youngster::
	lock
	faceplayer
	msgbox Gate_RuinsOfAlph_Route32_Text_Youngster, MSGBOX_DEFAULT
	closemessage
	release
	end

Gate_RuinsOfAlph_Route32_Text_PokefanM:
	.string "You're studying the RUINS?\n"
	.string "I see a scientist in the making.$"

Gate_RuinsOfAlph_Route32_Text_Youngster:
	.string "יש ציורים על לוחות אבן.\p"
	.string "ניסיתי להזיז אותם.\n"
	.string "מעניין מה הם.$"
