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
	.string "אני אוסף פוקימונים!\n"
	.string "יש לך {STR_VAR_1}?\p"
	.string "רוצה להחליף אותו\n"
	.string "ב{STR_VAR_2} שלי?$"

VioletCity_House1_Text_MonYouTakeCare:
	.string "יש! השגתי {STR_VAR_1}!\p"
	.string "{STR_VAR_2}, תשמור על עצמך!$"

VioletCity_House1_Text_ThisIsntAMon:
	.string "אה, לא, לא נראה לי.\n"
	.string "זה לא {STR_VAR_1}.$"

VioletCity_House1_Text_YouWontTradeMe:
	.string "לא רוצה להחליף? אוף…$"

VioletCity_House1_Text_After:
	.string "היי, מה שלום האוניקס שהיה פעם שלי?$"

VioletCity_House1_Text_PokefanM:
	.string "פוקימון שמקבלים בהחלפה גדל מהר.\p"
	.string "אבל בלי תג המכון המתאים,\n"
	.string "הוא עלול לא לציית לך.$"
