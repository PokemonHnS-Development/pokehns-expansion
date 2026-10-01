RustboroCity_House1_MapScripts::
	.byte 0

RustboroCity_House1_EventScript_Trader::
	lock
	faceplayer
	goto_if_set FLAG_RUSTBORO_NPC_TRADE_COMPLETED, RustboroCity_House1_EventScript_TradeCompleted
	ingame_trade INGAME_TRADE_SEEDOT, RustboroCity_House1_Text_IllTradeIfYouWant, RustboroCity_House1_EventScript_DeclineTrade, RustboroCity_House1_EventScript_NotRequestedMon, RustboroCity_House1_Text_PleaseBeGoodToMyPokemon
	setflag FLAG_RUSTBORO_NPC_TRADE_COMPLETED
	release
	end

RustboroCity_House1_EventScript_DeclineTrade::
	msgbox RustboroCity_House1_Text_YouDontWantToThatsOkay, MSGBOX_DEFAULT
	release
	end

RustboroCity_House1_EventScript_NotRequestedMon::
	bufferspeciesname STR_VAR_1, VAR_0x8009
	msgbox RustboroCity_House1_Text_DoesntLookLikeMonToMe, MSGBOX_DEFAULT
	release
	end

RustboroCity_House1_EventScript_TradeCompleted::
	msgbox RustboroCity_House1_Text_AnyPokemonCanBeCute, MSGBOX_DEFAULT
	release
	end

RustboroCity_House1_EventScript_Hiker::
	msgbox RustboroCity_House1_Text_AllSortsOfPlaces, MSGBOX_NPC
	end

RustboroCity_House1_Text_IllTradeIfYouWant:
	.string "¿Eh? ¿Mi POKéMON es lindo?\n"
	.string "Claro, ya lo sabía.\p"
	.string "Pero si de verdad quieres, estoy\n"
	.string "dispuesto a cambiártelo.\p"
	.string "Te cambio mi {STR_VAR_2} por\n"
	.string "un {STR_VAR_1} si quieres.$"

RustboroCity_House1_Text_PleaseBeGoodToMyPokemon:
	.string "Eheheh...\n"
	.string "Por favor, cuida bien a mi POKéMON.$"

RustboroCity_House1_Text_DoesntLookLikeMonToMe:
	.string "¿Eh? Eso no se parece en nada a\n"
	.string "un {STR_VAR_1} para mí.$"

RustboroCity_House1_Text_YouDontWantToThatsOkay:
	.string "Oh, si no quieres, no pasa nada.\n"
	.string "Pero mi POKéMON es lindo, ¿sabes?$"

RustboroCity_House1_Text_AnyPokemonCanBeCute:
	.string "Cualquier POKéMON es lindo si lo\n"
	.string "con cuidado y amabilidad.$"

RustboroCity_House1_Text_AllSortsOfPlaces:
	.string "En todo tipo de lugares, hay de todo\n"
	.string "tipo de POKéMON y personas.\p"
	.string "Eso me fascina, así que voy a todo\n"
	.string "tipo de lugares.$"

