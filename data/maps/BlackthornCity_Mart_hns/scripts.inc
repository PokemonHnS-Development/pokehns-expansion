BlackthornCity_Mart_hns_MapScripts::
	.byte 0

BlackthornMart_EventScript_CoolTrainerM::
	msgbox BlackthornMart_Text_CooltrainerM, MSGBOX_NPC
	end

BlackthornMart_EventScript_BlackBelt::
	msgbox BlackthornMart_Text_BlackBelt, MSGBOX_NPC
	end

BlackthornMart_Text_CooltrainerM:
	.string "No puedes comprar MAX REVIVIR,\n"
	.string "pero cura todo a un POKéMON.\p"
	.string "Cuidado: no restaura los PP,\n"
	.string "los PUNTOS DE PODER de los ataques.$"

BlackthornMart_Text_BlackBelt:
	.string "MAX REPELENTE aleja a los\n"
	.string "POKéMON débiles.\p"
	.string "Es el que más dura de todos los\n"
	.string "sprays REPELENTE.$"
