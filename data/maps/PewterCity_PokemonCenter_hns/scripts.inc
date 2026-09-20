PewterCity_PokemonCenter_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, PewterCity_PokemonCenter_OnTransition
	.byte 0

PewterCity_PokemonCenter_OnTransition::
	setrespawn HEAL_LOCATION_PEWTER_CITY_HNS
	end

PewterCity_PokemonCenter_EventScript_Teacher::
	msgbox PewterCity_PokemonCenter1F_Text_Teacher, MSGBOX_NPC
	end

PewterCity_PokemonCenter_EventScript_BugCatcher::
	msgbox PewterCity_PokemonCenter1F_Text_BugCatcher, MSGBOX_NPC
	end

PewterCity_PokemonCenter1F_Text_Teacher:
	.string "…Sí, el GIMNASIO de ISLA CRESPO\nya no existe.\pMe quedé muy\nsorprendido.\p…¿Sí? Estoy al teléfono.\n¡Vete!$"

PewterCity_PokemonCenter1F_Text_Jigglypuff:
	.string "JIGGLYPUFF: Puu pupuu.$"

PewterCity_PokemonCenter_EventScript_Mondo::
	lock
	faceplayer
	goto_if_set FLAG_PEWTER_NPC_TRADE_COMPLETED, PewterCity_PokemonCenter_EventScript_TradeCompleted
	ingame_trade INGAME_TRADE_HAUNTER, PewterCity_PokemonCenter_Text_WantToTrade, PewterCity_PokemonCenter_EventScript_DeclineTrade, PewterCity_PokemonCenter_EventScript_NotRequestedMon, PewterCity_PokemonCenter_Text_TakeCare
	setflag FLAG_PEWTER_NPC_TRADE_COMPLETED
	release
	end

PewterCity_PokemonCenter_EventScript_DeclineTrade::
	msgbox PewterCity_PokemonCenter_Text_DeclineTrade, MSGBOX_DEFAULT
	release
	end

PewterCity_PokemonCenter_EventScript_NotRequestedMon::
	bufferspeciesname STR_VAR_1, VAR_0x8009
	msgbox PewterCity_PokemonCenter_Text_NotRequestedMon, MSGBOX_DEFAULT
	release
	end

PewterCity_PokemonCenter_EventScript_TradeCompleted::
	msgbox PewterCity_PokemonCenter_Text_TradeCompleted, MSGBOX_DEFAULT
	release
	end

PewterCity_PokemonCenter_Text_WantToTrade:
	.string "He viajado por todas partes buscando\n"
	.string "un buen {STR_VAR_1}.\p"
	.string "¿Cambiarías uno por mi\n"
	.string "{STR_VAR_2}?$"

PewterCity_PokemonCenter_Text_TakeCare:
	.string "¡Muchas gracias!\n"
	.string "¡Cuida mucho a mi {STR_VAR_1}!$"

PewterCity_PokemonCenter_Text_DeclineTrade:
	.string "¿No? Qué mal…\n"
	.string "Creo que te gustaría mi HAUNTER.$"

PewterCity_PokemonCenter_Text_NotRequestedMon:
	.string "Hmm, eso no es un {STR_VAR_1}.\n"
	.string "Eso no es lo que estoy buscando.$"

PewterCity_PokemonCenter_Text_TradeCompleted:
	.string "¿Cómo te trata ese HAUNTER?\n"
	.string "¡Es un verdadero bromista!$"

PewterCity_PokemonCenter1F_Text_BugCatcher:
	.string "La mayoría de POKéMON se duermen si\n"
	.string "oyen cantar a un JIGGLYPUFF.\p"
	.string "Hay varios movimientos que solo se\n"
	.string "usan mientras el POKéMON duerme.$"
