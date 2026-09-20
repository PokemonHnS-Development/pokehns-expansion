GoldenrodCity_House2_hns_MapScripts::
	.byte 0

GoldenrodCity_House2_EventScript_Man::
	faceplayer
	lock
	msgbox GoldenrodPPSpeechHouse_Text_Man, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_House2_EventScript_Woman::
	faceplayer
	lock
	msgbox GoldenrodPPSpeechHouse_Text_Lass, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodPPSpeechHouse_Text_Man:
    .string "Una vez, mientras luchaba, mi\n"
    .string "El POKéMON no pudo hacer nada.\p"
    .string "Los PUNTOS DE PODER, o PP, de sus\n"
    .string "movimientos se habían agotado.$"

GoldenrodPPSpeechHouse_Text_Lass:
    .string "A veces, un POKéMON sano puede\n"
    .string "ser incapaz de usar sus movimientos.\p"
    .string "Si pasa, cúralo en un\n"
    .string "CENTRO POKéMON o usa un objeto.$"
