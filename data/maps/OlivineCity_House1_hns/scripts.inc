OlivineCity_House1_hns_MapScripts::
	.byte 0

OlivineCity_House1_EventScript_Tim::
	lock
	faceplayer
	goto_if_set FLAG_OLIVINE_NPC_TRADE_COMPLETED, OlivineCity_House1_EventScript_TradeCompleted
	ingame_trade INGAME_TRADE_VOLTORB, OlivineCity_House1_Text_YouWillTradeWontYou, OlivineCity_House1_EventScript_DeclineTrade, OlivineCity_House1_EventScript_NotRequestedMon, OlivineCity_House1_Text_MonYouTakeCare
	setflag FLAG_OLIVINE_NPC_TRADE_COMPLETED
	release
	end

OlivineCity_House1_EventScript_DeclineTrade::
	msgbox OlivineCity_House1_Text_YouWontTradeMe, MSGBOX_DEFAULT
	release
	end

OlivineCity_House1_EventScript_NotRequestedMon::
	bufferspeciesname STR_VAR_1, VAR_0x8009
	msgbox OlivineCity_House1_Text_ThisIsntAMon, MSGBOX_DEFAULT
	release
	end

OlivineCity_House1_EventScript_TradeCompleted::
	msgbox OlivineCity_House1_Text_After, MSGBOX_DEFAULT
	release
	end

OlivineCity_House1_Text_YouWillTradeWontYou:
	.string "אני אוסף פוקימונים!\n"
	.string "יש לך {STR_VAR_1}?\p"
	.string "רוצה להחליף אותו\n"
	.string "ב{STR_VAR_2} שלי?$"

OlivineCity_House1_Text_MonYouTakeCare:
	.string "יש! השגתי {STR_VAR_1}!\p"
	.string "{STR_VAR_2}, תשמור על עצמך!$"

OlivineCity_House1_Text_ThisIsntAMon:
	.string "אה, לא, אני לא חושב.\n"
	.string "זה לא {STR_VAR_1}.$"

OlivineCity_House1_Text_YouWontTradeMe:
	.string "לא רוצה להחליף? אוף…$"

OlivineCity_House1_Text_After:
	.string "היי, מה שלום הוולטורב הישן שלי?$"
