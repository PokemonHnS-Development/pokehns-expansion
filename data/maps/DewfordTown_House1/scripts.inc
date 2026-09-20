DewfordTown_House1_MapScripts::
	.byte 0

DewfordTown_House1_EventScript_Man::
	msgbox DewfordTown_House1_Text_LotToBeSaidForLivingOnIsland, MSGBOX_NPC
	end

DewfordTown_House1_EventScript_Woman::
	msgbox DewfordTown_House1_Text_LifeGoesSlowlyOnIsland, MSGBOX_NPC
	end

DewfordTown_House1_EventScript_Zigzagoon::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_ZIGZAGOON, CRY_MODE_NORMAL
	msgbox DewfordTown_House1_Text_Zigzagoon, MSGBOX_DEFAULT
	waitmoncry
	release
	end

DewfordTown_House1_Text_LotToBeSaidForLivingOnIsland:
	.string "Vivir en una isla pequeña como esta\n"
	.string "en armonía con los POKéMON y la\l"
	.string "familia tiene mucho valor.$"

DewfordTown_House1_Text_LifeGoesSlowlyOnIsland:
	.string "Dejé el puerto de CIUDAD FONDOPORT\n"
	.string "cuando me casé con mi esposo aquí.\p"
	.string "La vida pasa lento en esta islita.\n"
	.string "Pero estar rodeada del hermoso mar\l"
	.string "también es una gran felicidad.$"

DewfordTown_House1_Text_Zigzagoon:
	.string "ZIGZAGOON: Guguuh!$"

