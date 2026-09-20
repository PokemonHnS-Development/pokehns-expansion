Route119_House_MapScripts::
	.byte 0

Route119_House_EventScript_Woman::
	msgbox Route119_House_Text_RumorAboutCaveOfOrigin, MSGBOX_NPC
	end

Route119_House_EventScript_Wingull::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_WINGULL, CRY_MODE_NORMAL
	msgbox Route119_House_Text_Wingull, MSGBOX_DEFAULT
	waitmoncry
	release
	end

Route119_House_Text_RumorAboutCaveOfOrigin:
	.string "Oí hablar de una cueva llamada la\n"
	.string "CUEVA DEL ORIGEN.\p"
	.string "Dicen que allí reviven los espíritus\n"
	.string "de los POKéMON. ¿Será que algo así\l"
	.string "podría pasar de verdad?$"

Route119_House_Text_Wingull:
	.string "WINGULL: Pihyoh!$"

