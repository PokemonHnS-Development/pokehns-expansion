BattleFrontier_Lounge6_MapScripts::
	.byte 0

BattleFrontier_Lounge6_EventScript_Trader::
	lock
	faceplayer
	goto_if_set FLAG_BATTLE_FRONTIER_TRADE_DONE, BattleFrontier_Lounge6_EventScript_TradeCompleted
	ingame_trade INGAME_TRADE_MEOWTH, BattleFrontier_Lounge6_Text_WouldYouLikeToTrade, BattleFrontier_Lounge6_EventScript_DeclineTrade, BattleFrontier_Lounge6_EventScript_NotRequestedMon, BattleFrontier_Lounge6_Text_PromiseIllBeGoodToIt
	setflag FLAG_BATTLE_FRONTIER_TRADE_DONE
	release
	end

BattleFrontier_Lounge6_EventScript_DeclineTrade::
	msgbox BattleFrontier_Lounge6_Text_WellThatsFineToo, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge6_EventScript_NotRequestedMon::
	bufferspeciesname STR_VAR_1, VAR_0x8009
	msgbox BattleFrontier_Lounge6_Text_DontTradeForAnythingButMon, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge6_EventScript_TradeCompleted::
	msgbox BattleFrontier_Lounge6_Text_SkittySoMuchCuterThanImagined, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge6_Text_WouldYouLikeToTrade:
	.string "Mi POKéMON es un {STR_VAR_2}.\n"
	.string "¿Lo conoces?\l"
	.string "Es muy lindo y agradable.\p"
	.string "A este pequeño lo cambiaría con\n"
	.string "orgullo!\p"
	.string "¿Quieres cambiar un {STR_VAR_1}\n"
	.string "por mi {STR_VAR_2}?$"

BattleFrontier_Lounge6_Text_PromiseIllBeGoodToIt:
	.string "¡Oh, es adorable!\n"
	.string "¡Gracias!\l"
	.string "¡Prometo que lo cuidaré bien!\p"
	.string "¡Oh! ¡Espero que cuides bien de\n"
	.string "mi {STR_VAR_2} también!$"

BattleFrontier_Lounge6_Text_DontTradeForAnythingButMon:
	.string "¡Oh, lo siento!\n"
	.string "No pienso cambiar nada\l"
	.string "que no sea un {STR_VAR_1}.$"

BattleFrontier_Lounge6_Text_WellThatsFineToo:
	.string "Oh, ¿no quieres?\n"
	.string "Bueno, eso también está bien.\l"
	.string "Por favor, visítanos de nuevo.$"

BattleFrontier_Lounge6_Text_SkittySoMuchCuterThanImagined:
	.string "¡Jeje!\n"
	.string "Un SKITTY es mucho más lindo de lo\l"
	.string "que imaginé. ¡Estoy feliz!$"
