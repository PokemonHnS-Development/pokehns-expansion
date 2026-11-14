CliffEdgeGate_hns_MapScripts::
	.byte 0

CliffEdgeGate_EventScript_Woman::
	lock
	faceplayer
	msgbox CliffEdgeGate_Text_IntroOpen, MSGBOX_DEFAULT
	closemessage
	release
	end

CliffEdgeGate_EventScript_Picnicker::
	lock
	faceplayer
	msgbox CliffEdgeGate_Text_Expectations, MSGBOX_DEFAULT
	closemessage
	release
	end

CliffEdgeGate_Text_IntroOpen:
	.string "ידעת? ממש מעבר לפינה נמצא\n"
	.string "אזור הספארי.\p"
	.string "זה ממש כיף! רואים שם המון סוגים\n"
	.string "של פוקימונים, ותופסים כמה שרוצים!\p"
	.string "אין שום סיבה לא ללכת, נכון?\n"
	.string "ממש מעבר לפינה.$"

CliffEdgeGate_Text_Expectations:
	.string "אני מבין שכולם מחכים לזה\n"
	.string "בקוצר רוח.\p"
	.string "אבל הגברת בקבלה נראית\n"
	.string "קצת דרמטית מדי…\p"
	.string "לא כדאי לבנות ציפיות גבוהות מדי!$"

CliffEdgeGate_EventScript_CaveSign::
	lock
	msgbox CliffEdgeGate_Text_SignOpen, MSGBOX_SIGN
	closemessage
	release
	end

CliffEdgeGate_Text_SignOpen:
	.string "הכול מרגש!\n"
	.string "חקרו ומצאו פוקימונים פראיים!\p"
	.string "אזור הספארי של הפקח באובה\n"
	.string "פתוח ופועל!$"

