PacifidlogTown_House3_MapScripts::
	.byte 0

PacifidlogTown_House3_EventScript_Trader::
	lock
	faceplayer
	goto_if_set FLAG_PACIFIDLOG_NPC_TRADE_COMPLETED, PacifidlogTown_House3_EventScript_TradeCompleted
	ingame_trade INGAME_TRADE_HORSEA, PacifidlogTown_House3_Text_WillingToTradeIt, PacifidlogTown_House3_EventScript_DeclineTrade, PacifidlogTown_House3_EventScript_NotRequestedMon, PacifidlogTown_House3_Text_ItsSubtlyDifferentThankYou
	setflag FLAG_PACIFIDLOG_NPC_TRADE_COMPLETED
	release
	end

PacifidlogTown_House3_EventScript_DeclineTrade::
	msgbox PacifidlogTown_House3_Text_NotDesperateOrAnything, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_House3_EventScript_NotRequestedMon::
	bufferspeciesname STR_VAR_1, VAR_0x8009
	msgbox PacifidlogTown_House3_Text_WontAcceptAnyLessThanRealMon, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_House3_EventScript_TradeCompleted::
	msgbox PacifidlogTown_House3_Text_ReallyWantedToGetBagon, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_House3_EventScript_Girl::
	msgbox PacifidlogTown_House3_Text_IsThatAPokedex, MSGBOX_NPC
	end

PacifidlogTown_House3_Text_WillingToTradeIt:
	.string "¡Mira este {STR_VAR_2}!\p"
	.string "Es el {STR_VAR_2} que atrapé\n"
	.string "ayer para celebrar mi cumple!\p"
	.string "¡Oh, veo que lo quieres!\n"
	.string "¡Después de todo, no tiene precio!\p"
	.string "Te propongo algo. Podría estar\n"
	.string "dispuesto a cambiarlo por un {STR_VAR_1}.$"

PacifidlogTown_House3_Text_ItsSubtlyDifferentThankYou:
	.string "¿Oh, así que esto es un {STR_VAR_1}?\p"
	.string "Es algo parecido a un {STR_VAR_2},\n"
	.string "pero es sutilmente diferente.\p"
	.string "Thank you!$"

PacifidlogTown_House3_Text_WontAcceptAnyLessThanRealMon:
	.string "¡No, no, no! ¡No aceptaré nada\n"
	.string "que no sea un {STR_VAR_1} real!$"

PacifidlogTown_House3_Text_NotDesperateOrAnything:
	.string "Oh, ¿entonces no vas a seguir\n"
	.string "con esto?\p"
	.string "Está bien. No estoy desesperado por\n"
	.string "hacer un intercambio ni nada.$"

PacifidlogTown_House3_Text_ReallyWantedToGetBagon:
	.string "Sé que podría buscar uno\n"
	.string "por mi cuenta, pero...\p"
	.string "Pero quería un BAGON que otro\n"
	.string "ENTRENADOR hubiera atrapado...$"

PacifidlogTown_House3_Text_IsThatAPokedex:
	.string "¿Eso es una POKéDEX?\p"
	.string "¿Has podido conocer a muchos\n"
	.string "con los POKéMON?\p"
	.string "Desearía ser como tú.$"

