ViridianCity_House_Frlg_MapScripts::
	.byte 0

ViridianCity_House_EventScript_BaldingMan::
	msgbox ViridianCity_House_Text_NicknamingIsFun, MSGBOX_NPC
	end

ViridianCity_House_EventScript_LittleGirl::
	msgbox ViridianCity_House_Text_MyDaddyLovesMonsToo, MSGBOX_NPC
	end

ViridianCity_House_EventScript_Speary::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_SPEAROW, CRY_MODE_NORMAL
	msgbox ViridianCity_House_Text_Speary
	waitmoncry
	release
	end

ViridianCity_House_EventScript_NicknameSign::
	msgbox ViridianCity_House_Text_SpearowNameSpeary, MSGBOX_SIGN
	end

ViridianCity_House_Text_NicknamingIsFun::
	.string "Poner apodos es divertido,\n"
	.string "pero no es tan fácil de hacer.\p"
	.string "Los nombres ingeniosos son geniales,\n"
	.string "pero los simples se recuerdan mejor.$"

ViridianCity_House_Text_MyDaddyLovesMonsToo::
	.string "A mi papi también le gustan POKéMON.$"

ViridianCity_House_Text_Speary::
	.string "SPEARY: Tetweet!$"

ViridianCity_House_Text_SpearowNameSpeary::
	.string "SPEAROW\n"
	.string "Nombre: SPEARY$"

