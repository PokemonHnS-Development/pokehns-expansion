SSAnne_1F_Room3_Frlg_MapScripts::
	.byte 0

SSAnne_1F_Room3_EventScript_LittleGirl::
	msgbox SSAnne_1F_Room3_Text_AlwaysTravelWithWigglytuff, MSGBOX_NPC
	end

SSAnne_1F_Room3_EventScript_BaldingMan::
	msgbox SSAnne_1F_Room3_Text_CruiseIsElegantAndCozy, MSGBOX_NPC
	end

SSAnne_1F_Room3_EventScript_Wigglytuff::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_WIGGLYTUFF, CRY_MODE_NORMAL
	msgbox SSAnne_1F_Room3_Text_Wigglytuff
	waitmoncry
	release
	end

SSAnne_1F_Room3_Text_CruiseIsElegantAndCozy::
	.string "Un crucero mundial es tan elegante\n"
	.string "cozy!$"

SSAnne_1F_Room3_Text_AlwaysTravelWithWigglytuff::
	.string "que siempre viajo con WIGGLYTUFF.\n"
	.string "Nunca salgo sin él.$"

SSAnne_1F_Room3_Text_Wigglytuff::
	.string "WIGGLYTUFF: Puup pupuu!$"

