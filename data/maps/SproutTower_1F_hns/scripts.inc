SproutTower_1F_hns_MapScripts::
	.byte 0

SproutTower_1F_EventScript_SageChow::
	trainerbattle_single TRAINER_CHOW_HNS, SproutTower_Text_SageChow_Seen, SproutTower_Text_SageChow_Beaten
	msgbox SproutTower_Text_SageChow_AfterBattle, MSGBOX_AUTOCLOSE
	end

SproutTower_1F_EventScript_Sage1::
	lock
	faceplayer
	msgbox SproutTower_Text_1F_Sage1, MSGBOX_DEFAULT
	closemessage
	release
	end

SproutTower_1F_EventScript_Sage2::
	lock
	faceplayer
	msgbox SproutTower_Text_1F_Sage2, MSGBOX_DEFAULT
	closemessage
	release
	end

SproutTower_1F_EventScript_Granny::
	lock
	faceplayer
	msgbox SproutTower_Text_1F_Granny, MSGBOX_DEFAULT
	closemessage
	release
	end

SproutTower_1F_EventScript_Teacher::
	lock
	faceplayer
	msgbox SproutTower_Text_1F_Teacher, MSGBOX_DEFAULT
	closemessage
	release
	end

SproutTower_1F_EventScript_ItemParalyzeHeal::
	finditem ITEM_PARALYZE_HEAL
	end

SproutTower_Text_SageChow_Seen:
	.string "אנחנו שומרים על המגדל הזה.\p"
	.string "כאן אנחנו מביעים הכרת תודה\n"
	.string "כאות כבוד לכל הפוקימונים.$"

SproutTower_Text_SageChow_Beaten:
	.string "ת-תודה לך!$"

SproutTower_Text_SageChow_AfterBattle:
	.string "כל היצורים החיים מתקיימים יחד\n"
	.string "בזכות שיתוף פעולה.\p"
	.string "עלינו תמיד להיות אסירי תודה על כך.$"

SproutTower_Text_1F_Sage1:
	.string "רק מי שיגיע לראש המגדל יקבל מ”נ.$"

SproutTower_Text_1F_Sage2:
	.string "מגדל הנבט נבנה לפני זמן רב\n"
	.string "כמקום לאימון פוקימונים.$"

SproutTower_Text_1F_Granny:
	.string "בלספראוט שגובהו יותר מ-100 רגל…\p"
	.string "אומרים שהוא הפך\n"
	.string "לעמוד המרכזי שכאן.$"

SproutTower_Text_1F_Teacher:
	.string "רואה איך העמוד רועד?\p"
	.string "אנשים מתאמנים בקומות העליונות.$"

SproutTower_Text_1F_Statue:
	.string "A POKéMON statue…\p"
	.string "It looks very distinguished.$"
