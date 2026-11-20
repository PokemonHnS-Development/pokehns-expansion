GoldenrodCity_DepartmentStore_6F_hns_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, GoldenrodDeptElevator_OnFrame
	.byte 0

GoldenrodDeptStore6_EventScript_Whitney::
	lock
	faceplayer
	msgbox GoldenrodDeptStore6_Text_Whitney, MSGBOX_DEFAULT
	closemessage
	fadescreenswapbuffers FADE_TO_BLACK
	setflag FLAG_HIDE_DEPTSTORE_WHITNEY
	removeobject LOCALID_STORE_WHITNEY
	fadescreenswapbuffers FADE_FROM_BLACK
	clearflag FLAG_HIDE_DOJO_WHITNEY
	release
	end

GoldenrodDeptStore6_Text_Whitney:
	.string "{PLAYER}! איזו הפתעה לראות אותך כאן!\p"
	.string "באתי לקנות משהו בשביל\n"
	.string "המילטנק שלי.\p"
	.string "אם אתה רוצה עוד קרב, בוא\n"
	.string "לדוג'ו הלחימה!$"

GoldenrodCity_DepartmentStore_6F_EventScript_Jose::
	lock
	faceplayer
	goto_if_set FLAG_GOLDENROD_NPC_TRADE_COMPLETED, GoldenrodCity_DepartmentStore_6F_EventScript_TradeCompleted
	ingame_trade INGAME_TRADE_MACHOP, GoldenrodCity_DepartmentStore_6F_Text_YouWillTradeWontYou, GoldenrodCity_DepartmentStore_6F_EventScript_DeclineTrade, GoldenrodCity_DepartmentStore_6F_EventScript_NotRequestedMon, GoldenrodCity_DepartmentStore_6F_Text_MonYouTakeCare
	setflag FLAG_GOLDENROD_NPC_TRADE_COMPLETED
	release
	end

GoldenrodCity_DepartmentStore_6F_EventScript_DeclineTrade::
	msgbox GoldenrodCity_DepartmentStore_6F_Text_YouWontTradeMe, MSGBOX_DEFAULT
	release
	end

GoldenrodCity_DepartmentStore_6F_EventScript_NotRequestedMon::
	bufferspeciesname STR_VAR_1, VAR_0x8009
	msgbox GoldenrodCity_DepartmentStore_6F_Text_ThisIsntAMon, MSGBOX_DEFAULT
	release
	end

GoldenrodCity_DepartmentStore_6F_EventScript_TradeCompleted::
	msgbox GoldenrodCity_DepartmentStore_6F_Text_After, MSGBOX_DEFAULT
	release
	end

GoldenrodCity_DepartmentStore_6F_Text_YouWillTradeWontYou:
	.string "אני אוסף פוקימונים!\n"
	.string "יש לך {STR_VAR_1}?\p"
	.string "רוצה להחליף אותו תמורת\n"
	.string "ה{STR_VAR_2} שלי?$"

GoldenrodCity_DepartmentStore_6F_Text_MonYouTakeCare:
	.string "יש! השגתי לעצמי {STR_VAR_1}!\p"
	.string "{STR_VAR_2}, תשמור על עצמך!$"

GoldenrodCity_DepartmentStore_6F_Text_ThisIsntAMon:
	.string "אה, לא, לא נראה לי.\n"
	.string "זה לא {STR_VAR_1}.$"

GoldenrodCity_DepartmentStore_6F_Text_YouWontTradeMe:
	.string "אתה לא רוצה להחליף? אוף…$"

GoldenrodCity_DepartmentStore_6F_Text_After:
	.string "היי, מה שלום המאצ'ופ הישן שלי?$"


GoldenrodDeptStore6_EventScript_Lass::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_6FLass, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore6_EventScript_Nerd::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_6FSuperNerd, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore6_EventScript_Sign::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_6FDirectory, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore_Text_6FLass:
    .string "אתה מאזין לערוץ המזל?\p"
    .string "אומרים שכדי לזכות, צריך להחליף\n"
    .string "פוקימונים עם כמה שיותר אנשים.\p"
    .string "ככה מקבלים מספרי זיהוי שונים.\p"
    .string "אבל היום כבר אי אפשר להחליף\n"
    .string "בקלות כמו פעם.$"

GoldenrodDeptStore_Text_6FSuperNerd:
    .string "אם אתה עייף, נסה את המשקאות\n"
    .string "של מכונת הממכר.\p"
    .string "גם הפוקימונים שלך יאהבו אותם.$"

GoldenrodDeptStore_Text_6FDirectory:
    .string "הפסקה מהקניות!\p"
    .string "ק6: כיכר השלווה$"
