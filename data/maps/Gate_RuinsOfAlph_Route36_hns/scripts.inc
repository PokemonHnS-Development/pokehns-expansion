Gate_RuinsOfAlph_Route36_hns_MapScripts::
	.byte 0

Gate_RuinsOfAlph_Route36_EventScript_Officer::
	lock
	faceplayer
	msgbox Gate_RuinsOfAlph_Route36_Text_Officer, MSGBOX_DEFAULT
	closemessage
	release
	end

Gate_RuinsOfAlph_Route36_EventScript_PokefanM::
	lock
	faceplayer
	msgbox Gate_RuinsOfAlph_Route36_Text_PokefanM, MSGBOX_DEFAULT
	closemessage
	release
	end

Gate_RuinsOfAlph_Route36_EventScript_Youngster::
	lock
	faceplayer
	msgbox Gate_RuinsOfAlph_Route36_Text_Youngster, MSGBOX_DEFAULT
	closemessage
	release
	end

Gate_RuinsOfAlph_Route36_Text_Officer:
	.string "חורבות אלף\p"
	.string "אתר תיירות להתבוננות ולמגע\p"
	.string "נסו להזיז את לוחות האבן!$"

Gate_RuinsOfAlph_Route36_Text_PokefanM:
	.string "באת לחקור את החורבות?\p"
	.string "אני רואה כאן מדען לעתיד.$"

Gate_RuinsOfAlph_Route36_Text_Youngster:
	.string "יש ציורים על לוחות אבן.\p"
	.string "ניסיתי להזיז אותם.\n"
	.string "מעניין מה הם.$"
