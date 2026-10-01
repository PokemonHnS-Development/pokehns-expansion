LavenderTown_House1_hns_MapScripts::
	.byte 0

LavenderTown_House1_EventScript_Girl::
	msgbox LavenderTown_House1_Text_Girl, MSGBOX_NPC
	end

LavenderTown_House1_EventScript_Guy::
	msgbox LavenderTown_House1_Text_Guy, MSGBOX_NPC
	end

LavenderTown_House1_EventScript_Marowak::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_MAROWAK, CRY_MODE_NORMAL
	msgbox LavenderTown_House1_Text_Marowak, MSGBOX_DEFAULT
	waitmoncry
	msgbox LavenderTown_House1_Text_Marowak2, MSGBOX_DEFAULT
	closemessage
	release
	end

LavenderTown_House1_Text_Girl:
	.string "¿Puedes creerlo?\p"
	.string "Hay gente que se aburre de\n"
	.string "cuidar a los POKéMON.\p"
	.string "EL ABUELO acoge a POKéMON pobres\n"
	.string "y sin hogar y los cuida.$"
LavenderTown_House1_Text_Guy:
	.string "EL SR. FUJI vive aquí, pero\n"
	.string "no está ahora. Debería estar en la\l"
	.string "CASA DEL ALMA.$"
LavenderTown_House1_Text_Marowak:
	.string ".............................$"

LavenderTown_House1_Text_Marowak2:
	.string "El MAROWAK está tranquilo, aunque\n"
	.string "parece estar muy feliz.$"

