FuchsiaCity_House2_hns_MapScripts::
	.byte 0

FuchsiaCity_House2_EventScript_Granddaughter::	
	goto_if_set FLAG_TEMP_1, FuchsiaCity_House2_EventScript_Granddaughter2
	msgbox FuchsiaCity_House2_Text_WardensGranddaughter1, MSGBOX_NPC
	setflag FLAG_TEMP_1
	end

FuchsiaCity_House2_EventScript_Granddaughter2::
	msgbox FuchsiaCity_House2_Text_WardensGranddaughter2, MSGBOX_NPC
	end

FuchsiaCity_House2_EventScript_Photo::
	msgbox FuchsiaCity_House2_Text_WardenPhoto, MSGBOX_NPC
	end

FuchsiaCity_House2_Text_WardensGranddaughter1:
	.string "Mi abuelo es el GUARDABOSQUES\n"
	.string "de la ZONA SAFARI.\p"
	.string "Al menos lo era...\p"
	.string "Decidió irse de vacaciones y\n"
	.string "se fue al extranjero solo.\p"
	.string "Dejó de dirigir la ZONA SAFARI\n"
	.string "POKéMON así.$"

FuchsiaCity_House2_Text_WardensGranddaughter2:
	.string "Muchos se decepcionaron de que\n"
	.string "la ZONA SAFARI cerrara, pero el\l"
	.string "abuelo es muy terco...$"

FuchsiaCity_House2_Text_WardenPhoto:
	.string "Es la foto de un anciano sonriente\n"
	.string "rodeado de POKéMON.$"

FuchsiaCity_House2_Text_SafariZonePhoto:
	.string "Es la foto de una gran llanura\n"
	.string "con POKéMON raros jugando en él.$"
