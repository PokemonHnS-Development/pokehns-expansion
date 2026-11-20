OlivineCity_Cafe_hns_MapScripts::
	.byte 0

OlivineCity_Cafe_EventScript_Jasmine::
	lock
	faceplayer
	msgbox OlivineCity_Cafe_Text_Jasmine, MSGBOX_DEFAULT
	closemessage
	fadescreenswapbuffers FADE_TO_BLACK
	setflag FLAG_HIDE_CAFE_JASMINE
	removeobject LOCALID_CAFE_JASMINE
	fadescreenswapbuffers FADE_FROM_BLACK
	clearflag FLAG_HIDE_DOJO_JASMINE
	release
	end

OlivineCity_Cafe_Text_Jasmine:
	.string "אה… שלום, {PLAYER}.\p"
	.string "הצלחות שמולי\n"
	.string "הן לא כולן שלי…\p"
	.string "אה…\p"
	.string "בעצם, מי שישב כאן\n"
	.string "לפניי אכל הרבה…\p"
	.string "אם תרצה להילחם שוב, אשמח\n"
	.string "שתבוא לדוג'ו הלחימה בעיר סאפרון.$"

OlivineCity_EventScript_SailorA::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_HM_STRENGTH, OlivineCity_EventScript_SailorA2
	msgbox OlivineCity_Text_CafeSailorStrength, MSGBOX_DEFAULT
	giveitem ITEM_HM_STRENGTH
	setflag FLAG_RECEIVED_HM_STRENGTH
OlivineCity_EventScript_SailorA2::
	msgbox OlivineCity_Text_CafeSailorGotStrength, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_EventScript_Cook::
	lock
	faceplayer
	msgbox OlivineCity_Text_CafeFishingGuru, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_EventScript_SailorB::
	lock
	faceplayer
	msgbox OlivineCity_Text_CafeSailor, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_Text_CafeSailorStrength:
	.string "הא! הפוקימונים שלך נראים\n"
	.string "ממש קלי משקל!\p"
	.string "אין להם כוח\n"
	.string "להזיז סלעים הצידה.\p"
	.string "הנה, תשתמש בזה ותלמד אותם\n"
	.string "עוצמה!$"

OlivineCity_Text_CafeSailorGotStrength:
	.string "בים, אפשר לסמוך רק\n"
	.string "על עצמך!\p"
	.string "אני כל כך גאה בגוף השרירי שלי!\n"
	.string "כדאי לך להתאמן כמוני!$"

OlivineCity_Text_CafeFishingGuru:
	.string "בתפריט של קפה אוליבין יש המון\n"
	.string "אוכל משביע למלחים שריריים כמוני!$"

OlivineCity_Text_CafeSailor:
	.string "בכל פעם שאני מגיע לעיר הזאת,\n"
	.string "אני תמיד מבקר בקפה אוליבין.\p"
	.string "כל מה שבתפריט גורם לי להרגיש\n"
	.string "חזק יותר. אני לא מפסיק לאכול!$"

