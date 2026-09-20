FortreeCity_House5_MapScripts::
	.byte 0

FortreeCity_House5_EventScript_PokefanF::
	msgbox FortreeCity_House5_Text_TreeHousesAreGreat, MSGBOX_NPC
	end

FortreeCity_House5_EventScript_Man::
	msgbox FortreeCity_House5_Text_AdaptedToNature, MSGBOX_NPC
	end

FortreeCity_House5_EventScript_Zigzagoon::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_ZIGZAGOON, CRY_MODE_NORMAL
	msgbox FortreeCity_House5_Text_Zigzagoon, MSGBOX_DEFAULT
	waitmoncry
	release
	end

FortreeCity_House5_Text_TreeHousesAreGreat:
	.string "¡Qué geniales casas de ARBOLEDA!\pCreo\nque es el mejor pueblo para\nvivir junto a los POKéMON.$"

FortreeCity_House5_Text_AdaptedToNature:
	.string "POKéMON y personas se adaptaron a\n"
	.string "la naturaleza para sobrevivir.\p"
	.string "No hay necesidad de obligar a la\n"
	.string "naturaleza a adaptarse a nosotros.$"

FortreeCity_House5_Text_Zigzagoon:
	.string "ZIGZAGOON: Bufuu!$"

