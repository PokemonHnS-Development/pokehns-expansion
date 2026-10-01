BattleFrontier_Lounge6_hns_MapScripts::
	.byte 0

BattleFrontier_Lounge6_EventScript_Trader_hns::
	lock
	faceplayer
	goto_if_set FLAG_BATTLE_FRONTIER_TRADE_DONE, BattleFrontier_Lounge6_EventScript_TradeCompleted_hns
	ingame_trade INGAME_TRADE_MEOWTH, BattleFrontier_Lounge6_Text_WouldYouLikeToTrade_hns, BattleFrontier_Lounge6_EventScript_DeclineTrade_hns, BattleFrontier_Lounge6_EventScript_NotRequestedMon_hns, BattleFrontier_Lounge6_Text_PromiseIllBeGoodToIt_hns
	setflag FLAG_BATTLE_FRONTIER_TRADE_DONE
	release
	end

BattleFrontier_Lounge6_EventScript_DeclineTrade_hns::
	msgbox BattleFrontier_Lounge6_Text_WellThatsFineToo_hns, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge6_EventScript_NotRequestedMon_hns::
	bufferspeciesname STR_VAR_1, VAR_0x8009
	msgbox BattleFrontier_Lounge6_Text_DontTradeForAnythingButMon_hns, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge6_EventScript_TradeCompleted_hns::
	msgbox BattleFrontier_Lounge6_Text_SkittySoMuchCuterThanImagined_hns, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge6_Text_WouldYouLikeToTrade_hns:
	.string "Mi POKéMON es un {STR_VAR_2}.\n"
	.string "¿Lo conoces?\l"
	.string "Es muy lindo y agradable.\p"
	.string "A este pequeño lo cambiaría con\n"
	.string "orgullo!\p"
	.string "¿Quieres cambiar un {STR_VAR_1}\n"
	.string "por mi {STR_VAR_2}?$"

BattleFrontier_Lounge6_Text_PromiseIllBeGoodToIt_hns:
	.string "¡Oh, es adorable!\n"
	.string "¡Gracias!\l"
	.string "¡Prometo que lo cuidaré bien!\p"
	.string "¡Oh! ¡Espero que cuides bien de\n"
	.string "mi {STR_VAR_2} también!$"

BattleFrontier_Lounge6_Text_DontTradeForAnythingButMon_hns:
	.string "¡Oh, lo siento!\n"
	.string "No pienso cambiar nada\l"
	.string "que no sea un {STR_VAR_1}.$"

BattleFrontier_Lounge6_Text_WellThatsFineToo_hns:
	.string "Oh, ¿no quieres?\n"
	.string "Bueno, eso también está bien.\l"
	.string "Por favor, visítanos de nuevo.$"

BattleFrontier_Lounge6_Text_SkittySoMuchCuterThanImagined_hns:
	.string "¡Jeje!\n"
	.string "Un SKITTY es mucho más lindo de lo\l"
	.string "que imaginé. ¡Estoy feliz!$"
