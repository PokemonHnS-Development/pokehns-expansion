VioletCity_House1_hns_MapScripts::
	.byte 0

VioletCity_House1_EventScript_Kyle::
	lock
	faceplayer
	msgbox VioletCity_House1_Text_PokefanM, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_House1_EventScript_Rudy::
	lock
	faceplayer
	goto_if_set FLAG_VIOLET_NPC_TRADE_COMPLETED, VioletCity_House1_EventScript_TradeCompleted
	ingame_trade INGAME_TRADE_ONIX, VioletCity_House1_Text_YouWillTradeWontYou, VioletCity_House1_EventScript_DeclineTrade, VioletCity_House1_EventScript_NotRequestedMon, VioletCity_House1_Text_MonYouTakeCare
	setflag FLAG_VIOLET_NPC_TRADE_COMPLETED
	release
	end

VioletCity_House1_EventScript_DeclineTrade::
	msgbox VioletCity_House1_Text_YouWontTradeMe, MSGBOX_DEFAULT
	release
	end

VioletCity_House1_EventScript_NotRequestedMon::
	bufferspeciesname STR_VAR_1, VAR_0x8009
	msgbox VioletCity_House1_Text_ThisIsntAMon, MSGBOX_DEFAULT
	release
	end

VioletCity_House1_EventScript_TradeCompleted::
	msgbox VioletCity_House1_Text_After, MSGBOX_DEFAULT
	release
	end

VioletCity_House1_Text_YouWillTradeWontYou:
	.string "¡Colecciono POKéMON!\n"
	.string "¿Tienes un {STR_VAR_1}?\p"
	.string "¿Quieres cambiarlo por mi\n"
	.string "{STR_VAR_2}?$"

VioletCity_House1_Text_MonYouTakeCare:
	.string "¡Súper! ¡Ya tengo un {STR_VAR_1}!\p"
	.string "{STR_VAR_2}, ¡cuídate mucho!$"

VioletCity_House1_Text_ThisIsntAMon:
	.string "Eh, no, no creo que sea así.\n"
	.string "Eso no es un {STR_VAR_1}.$"

VioletCity_House1_Text_YouWontTradeMe:
	.string "¿No quieres intercambiar? Ohh...$"

VioletCity_House1_Text_After:
	.string "Hi, how's my old ONIX doing?$"

VioletCity_House1_Text_PokefanM:
	.string "Un POKéMON obtenido por intercambio\n"
	.string "crece rápidamente.\p"
	.string "Pero si no tienes la MEDALLA de\n"
	.string "GIMNASIO correcta, puede desobedecer.$"
