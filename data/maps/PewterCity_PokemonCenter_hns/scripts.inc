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
	.string "…Sí, ISLA CANELA ya no tiene GIMNASIO.\p
Me sorprendió mucho.\p
…¿Sí? Estoy al teléfono. ¡Vete!$"

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
	.string "He viajado por todas partes\n
buscando un buen {STR_VAR_1}.\p
¿Me cambiarías uno por mi\n
{STR_VAR_2}?$"

PewterCity_PokemonCenter_Text_TakeCare:
	.string "¡Muchas gracias!\n"
	.string "¡Cuida mucho a mi {STR_VAR_1}!$"

PewterCity_PokemonCenter_Text_DeclineTrade:
	.string "¿No? Qué lástima…\n
Creo que te gustaría mi HAUNTER.$"

PewterCity_PokemonCenter_Text_NotRequestedMon:
	.string "Mmm, eso no es un {STR_VAR_1}.\n
Eso no es lo que busco.$"

PewterCity_PokemonCenter_Text_TradeCompleted:
	.string "¿Qué tal te trata ese HAUNTER?\n
¡Es un verdadero travieso!$"

PewterCity_PokemonCenter1F_Text_BugCatcher:
	.string "La mayoría de POKéMON se duermen si\n"
	.string "oyen cantar a un JIGGLYPUFF.\p"
	.string "Hay varios movimientos que solo se\n"
	.string "usan mientras el POKéMON duerme.$"
