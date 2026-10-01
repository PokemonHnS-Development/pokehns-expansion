SSAnne_Deck_Frlg_MapScripts::
	.byte 0

SSAnne_Deck_EventScript_Youngster::
	msgbox SSAnne_Deck_Text_ShipDepartingSoon, MSGBOX_NPC
	end

SSAnne_Deck_EventScript_BaldingMan::
	msgbox SSAnne_Deck_Text_FeelSeasick, MSGBOX_NPC
	end

SSAnne_Deck_EventScript_Sailor::
	msgbox SSAnne_Deck_Text_ScrubbingDecksHardWork, MSGBOX_NPC
	end

SSAnne_Deck_EventScript_Edmond::
	trainerbattle_single TRAINER_SAILOR_EDMOND, SSAnne_Deck_Text_EdmondIntro, SSAnne_Deck_Text_EdmondDefeat
	msgbox SSAnne_Deck_Text_EdmondPostBattle, MSGBOX_AUTOCLOSE
	end

SSAnne_Deck_EventScript_Trevor::
	trainerbattle_single TRAINER_SAILOR_TREVOR, SSAnne_Deck_Text_TrevorIntro, SSAnne_Deck_Text_TrevorDefeat
	msgbox SSAnne_Deck_Text_TrevorPostBattle, MSGBOX_AUTOCLOSE
	end

SSAnne_Deck_Text_ShipDepartingSoon::
	.string "La fiesta terminó.\n"
	.string "El barco partirá pronto.$"

SSAnne_Deck_Text_ScrubbingDecksHardWork::
	.string "¡Uff!\n"
	.string "¡Fregar cubiertas es duro!$"

SSAnne_Deck_Text_FeelSeasick::
	.string "Uf... me siento mal...\p"
	.string "Me dio mareo, así que salí\n"
	.string "a tomar aire...$"

SSAnne_Deck_Text_EdmondIntro::
	.string "¡Hola, amigo!\p"
	.string "¡Bailemos un ratito!$"

SSAnne_Deck_Text_EdmondDefeat::
	.string "¡Eres impresionante!$"

SSAnne_Deck_Text_EdmondPostBattle::
	.string "¿Cuántos tipos de POKéMON\n"
	.string "piensan que hay en este gran mundo?$"

SSAnne_Deck_Text_TrevorIntro::
	.string "¡Hola, marinero!\n"
	.string "¿Tienes mareo?$"

SSAnne_Deck_Text_TrevorDefeat::
	.string "¡Solo fui descuidado!$"

SSAnne_Deck_Text_TrevorPostBattle::
	.string "Mi papá dijo que hay 100 tipos de\n"
	.string "POKéMON. Creo que hay más.$"

