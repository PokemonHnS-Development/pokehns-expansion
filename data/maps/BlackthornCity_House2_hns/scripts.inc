BlackthornCity_House2_hns_MapScripts::
	.byte 0

BlackthornCity_House2_EventScript_Emy::
	lock
	faceplayer
	goto_if_set FLAG_BLACKTHORN_NPC_TRADE_COMPLETED, BlackthornCity_House2_EventScript_TradeCompleted
	ingame_trade INGAME_TRADE_MR_MIME, BlackthornCity_House2_Text_YouWillTradeWontYou, BlackthornCity_House2_EventScript_DeclineTrade, BlackthornCity_House2_EventScript_NotRequestedMon, BlackthornCity_House2_Text_MonYouTakeCare
	setflag FLAG_BLACKTHORN_NPC_TRADE_COMPLETED
	release
	end

BlackthornCity_House2_EventScript_DeclineTrade::
	msgbox BlackthornCity_House2_Text_YouWontTradeMe, MSGBOX_DEFAULT
	release
	end

BlackthornCity_House2_EventScript_NotRequestedMon::
	bufferspeciesname STR_VAR_1, VAR_0x8009
	msgbox BlackthornCity_House2_Text_ThisIsntAMon, MSGBOX_DEFAULT
	release
	end

BlackthornCity_House2_EventScript_TradeCompleted::
	msgbox BlackthornCity_House2_Text_After, MSGBOX_DEFAULT
	release
	end

BlackthornCity_House2_Text_YouWillTradeWontYou:
	.string "אני אוספת פוקימונים!\n"
	.string "יש לך {STR_VAR_1}?\p"
	.string "רוצה להחליף אותו\n"
	.string "ב{STR_VAR_2} שלי?$"

BlackthornCity_House2_Text_MonYouTakeCare:
	.string "יש! קיבלתי {STR_VAR_1}!\p"
	.string "{STR_VAR_2}, תשמור על עצמך!$"

BlackthornCity_House2_Text_ThisIsntAMon:
	.string "אה, לא, אני לא חושבת.\n"
	.string "זה לא {STR_VAR_1}.$"

BlackthornCity_House2_Text_YouWontTradeMe:
	.string "לא רוצה להחליף? אוף…$"

BlackthornCity_House2_Text_After:
	.string "היי, מה שלומו של מר. מיים\n"
	.string "שהיה פעם שלי?$"
