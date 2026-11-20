LakeOfRage_House1_hns_MapScripts::
	.byte 0

LakeOfRage_House1_EventScript_HiddenPowerGuy::
	lock
	faceplayer
	goto_if_set FLAG_GOT_HIDDEN_POWER, LakeOfRage_House1_EventScript_HiddenPowerGuyAfter
	msgbox HiddenPowerGuy_Text_Intro, MSGBOX_DEFAULT
	giveitem ITEM_TM_HIDDEN_POWER
	msgbox HiddenPowerGuy_Text_Explanation, MSGBOX_DEFAULT
	setflag FLAG_GOT_HIDDEN_POWER
	closemessage
	release
	end

LakeOfRage_House1_EventScript_HiddenPowerGuyAfter::
	msgbox HiddenPowerGuy_Text_Meditating, MSGBOX_DEFAULT
	closemessage
	release
	end

HiddenPowerGuy_Text_Intro:
    .string "…תעית הרחק…\p"
    .string "כאן עסקתי במדיטציה. בתוכי\n"
    .string "התעורר כוח חדש.\p"
    .string "אחלוק את הכוח שלי עם\n"
    .string "הפוקימונים שלך. קח את זה, ילדי.$"

HiddenPowerGuy_Text_Explanation:
    .string "רואה? זהו כוח נסתר!\p"
    .string "הוא מוציא את הכוח שבפוקימון\n"
    .string "לצורך התקפה.\p"
    .string "זכור זאת: הסוג והעוצמה שלו\n"
    .string "תלויים בפוקימון שמשתמש בו.$"

HiddenPowerGuy_Text_Meditating:
    .string "אני שקוע במדיטציה…$"
