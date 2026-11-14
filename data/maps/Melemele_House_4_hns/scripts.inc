Melemele_House_4_hns_MapScripts::
	.byte 0


Melemele_House4_Man::
	lock
	faceplayer
	msgbox Melemele_House4_Man_Text_0, MSGBOX_AUTOCLOSE
	release
	end


Melemele_House4_Woman::
	lock
	faceplayer
	msgbox Melemele_House4_Woman_Text_0, MSGBOX_AUTOCLOSE
	release
	end


Melemele_House4_Man_Text_0:
	.string "אנחנו בחופשה באיי אלולה!\p"
	.string "זה בדיוק כמו אזור אלולה,\n"
	.string "רק קרוב יותר לקאנטו!\p"
	.string "חסכתי המון בהוצאות הנסיעה!$"

Melemele_House4_Woman_Text_0:
	.string "החבר שלי אמר לי שאנחנו נוסעים\n"
	.string "לאלולה…\p"
	.string "הנחתי שהכוונה לאזור אלולה, ולא\n"
	.string "לאיים הקטנים שמול חופי קאנטו.$"
