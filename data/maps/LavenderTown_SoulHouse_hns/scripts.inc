LavenderTown_SoulHouse_hns_MapScripts::
	.byte 0

LavenderTownSoulHouse_EventScript_MrFuji::
	msgbox MrFuji_Text_Main, MSGBOX_NPC
	end
LavenderTownSoulHouse_EventScript_Lass::
	msgbox SoulHouse_Text_Lass, MSGBOX_NPC
	end
LavenderTownSoulHouse_EventScript_Teacher::
	msgbox SoulHouse_Text_Teacher, MSGBOX_NPC
	end
LavenderTownSoulHouse_EventScript_Granny::
	msgbox SoulHouse_Text_Granny, MSGBOX_NPC
	end

MrFuji_Text_Main:
	.string "מר פוג'י: ברוך הבא.\p"
	.string "הממ… נראה שאתה מגדל את\n"
	.string "הפוקימונים שלך בטוב לב ובאהבה.\p"
	.string "חובבי פוקימונים באים לכאן לחלוק\n"
	.string "כבוד לפוקימונים שהלכו לעולמם.\p"
	.string "אנא, התפלל לעילוי נשמתם של\n"
	.string "הפוקימונים שהלכו לעולמם.\p"
	.string "אני בטוח שזה ישמח אותם.$"

SoulHouse_Text_Teacher:
	.string "יש כאן עוד קברים של פוקימונים,\n"
	.string "אני חושב.\p"
	.string "יש הרבה חדרים שרק מר פוג'י\n"
	.string "רשאי להיכנס אליהם.$"

SoulHouse_Text_Lass:
	.string "באתי עם אמא שלי לבקר\n"
	.string "בקברים של פוקימונים…$"

SoulHouse_Text_Granny:
	.string "הפוקימונים שחיו איתי…\p"
	.string "אהבתי אותם כמו את\n"
	.string "הנכדים שלי…$"
