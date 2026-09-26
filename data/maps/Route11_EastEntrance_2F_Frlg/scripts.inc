.equ REQUIRED_CAUGHT_MONS, 30

Route11_EastEntrance_2F_Frlg_MapScripts::
	.byte 0

Route11_EastEntrance_2F_EventScript_LeftBinoculars::
	lockall
	goto_if_set FLAG_WOKE_UP_ROUTE_12_SNORLAX, Route11_EastEntrance_2F_EventScript_LeftBinocularsSnorlaxGone
	msgbox Route11_EastEntrance_2F_Text_BigMonAsleepOnRoad
	releaseall
	end

Route11_EastEntrance_2F_EventScript_LeftBinocularsSnorlaxGone::
	msgbox Route11_EastEntrance_2F_Text_WhatABreathtakingView
	releaseall
	end

Route11_EastEntrance_2F_EventScript_RightBinoculars::
	msgbox Route11_EastEntrance_2F_Text_RockTunnelGoodRouteToLavender, MSGBOX_SIGN
	end

Route11_EastEntrance_2F_EventScript_Turner::
	lock
	faceplayer
	setvar VAR_0x8008, INGAME_TRADE_NIDORINOA
	call EventScript_GetInGameTradeSpeciesInfo
	goto_if_set FLAG_DID_NINA_TRADE, Route11_EastEntrance_2F_EventScript_AlreadyTraded
	msgbox Trade_Text_LookingForMonWannaTradeForMon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Route11_EastEntrance_2F_EventScript_DeclineTrade
	call EventScript_ChooseMonForInGameTrade
	goto_if_ge VAR_0x8004, PARTY_SIZE, Route11_EastEntrance_2F_EventScript_DeclineTrade
	call EventScript_GetInGameTradeSpecies
	goto_if_ne VAR_RESULT, VAR_0x8009, Route11_EastEntrance_2F_EventScript_NotRequestedMon
	call EventScript_DoInGameTrade
	msgbox Trade_Text_HeyThanks
	setflag FLAG_DID_NINA_TRADE
	release
	end

Route11_EastEntrance_2F_EventScript_DeclineTrade::
	msgbox Trade_Text_AwwOhWell
	release
	end

Route11_EastEntrance_2F_EventScript_NotRequestedMon::
	bufferspeciesname STR_VAR_1, VAR_0x8009
	msgbox Trade_Text_WhatThatsNoMon
	release
	end

Route11_EastEntrance_2F_EventScript_AlreadyTraded::
	msgbox Trade_Text_IsntMyOldMonGreat
	release
	end

Route11_EastEntrance_2F_EventScript_Aide::
	lock
	faceplayer
	call Route11_EastEntrance_2F_EventScript_GetAideRequestInfo
	goto_if_set FLAG_GOT_ITEMFINDER, Route11_EastEntrance_2F_EventScript_AlreadyGotItemfinder
	msgbox Route11_EastEntrance_2F_Text_GiveItemfinderIfCaught30, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Aide_EventScript_DeclineCheckMons
	setvar VAR_0x8004, 0
	specialvar VAR_RESULT, GetFrlgPokedexCount
	buffernumberstring STR_VAR_3, VAR_0x8006
	call Route11_EastEntrance_2F_EventScript_GetAideRequestInfo
	goto_if_lt VAR_0x8006, REQUIRED_CAUGHT_MONS, Aide_EventScript_HaventCaughtEnough
	msgbox Route11_EastEntrance_2F_Text_GreatHereYouGo
	checkitemspace ITEM_ITEMFINDER
	goto_if_eq VAR_RESULT, FALSE, Aide_EventScript_NoRoomForItem
	giveitem_msg Route11_EastEntrance_2F_Text_ReceivedItemfinderFromAide, ITEM_ITEMFINDER
	setflag FLAG_GOT_ITEMFINDER
	msgbox Route11_EastEntrance_2F_Text_ExplainItemfinder
	release
	end

Route11_EastEntrance_2F_EventScript_AlreadyGotItemfinder::
	msgbox Route11_EastEntrance_2F_Text_ExplainItemfinder
	release
	end

Route11_EastEntrance_2F_EventScript_GetAideRequestInfo::
	buffernumberstring STR_VAR_1, REQUIRED_CAUGHT_MONS
	bufferitemname STR_VAR_2, ITEM_ITEMFINDER
	return

Route11_EastEntrance_2F_Text_GiveItemfinderIfCaught30::
	.string "¡Hola! ¿Me recuerdas?\n"
	.string "Soy uno de los AYUDANTES del PROF. OAK.\p"
	.string "Si tu POKéDEX tiene datos completos\n"
	.string "de {STR_VAR_1} especies, debo darte\l"
	.string "una recompensa.\p"
	.string "El PROF. OAK me confió el\n"
	.string "{STR_VAR_2} para ti.\p"
	.string "Bueno, {PLAYER}, déjame preguntarte.\p"
	.string "¿Has reunido datos de al menos\n"
	.string "¿las {STR_VAR_1} clases de POKéMON?$"

Route11_EastEntrance_2F_Text_GreatHereYouGo::
	.string "¡Genial! Has atrapado o tenido\n"
	.string "{STR_VAR_3} tipos de POKéMON!\p"
	.string "¡Felicidades!\n"
	.string "¡Toma esto!$"

Route11_EastEntrance_2F_Text_ReceivedItemfinderFromAide::
	.string "{PLAYER} recibió el {STR_VAR_2}\n"
	.string "del AYUDANTE.$"

Route11_EastEntrance_2F_Text_ExplainItemfinder::
	.string "Hay objetos en el suelo que\n"
	.string "pueden estar ocultos a la vista.\p"
	.string "Usa el BUSCAOBJETOS para detectar\n"
	.string "objetos ocultos cerca de ti.\p"
	.string "La máquina es algo limitada.\n"
	.string "No puede ubicar el objeto.\p"
	.string "Solo muestra la dirección\n"
	.string "donde está el objeto.\p"
	.string "Úsala para orientarte, luego\n"
	.string "busca a mano en la zona sospechosa.$"

Route11_EastEntrance_2F_Text_BigMonAsleepOnRoad::
	.string "Veamos qué tienen los\n"
	.string "prismáticos...\p"
	.string "¡Un gran POKéMON duerme en el camino!$"

Route11_EastEntrance_2F_Text_WhatABreathtakingView::
	.string "Veamos qué tienen los\n"
	.string "prismáticos...\p"
	.string "¡Qué vista tan impresionante!$"

Route11_EastEntrance_2F_Text_RockTunnelGoodRouteToLavender::
	.string "Veamos qué tienen los\n"
	.string "prismáticos...\p"
	.string "Para llegar a PUEBLO LAVANDA,\n"
	.string "CERULEAN CITY...\p"
	.string "parece buena opción ir por el\n"
	.string "camino a seguir.$"

