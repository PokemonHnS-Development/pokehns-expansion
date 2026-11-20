Route12_House_hns_MapScripts::
	.byte 0

Route12_House_EventScript_SuperRod::
	lock
	faceplayer
	goto_if_set FLAG_GOT_SUPER_ROD, Route12_House_EventScript_SuperRodGot
	msgbox Route12_House_Text_OfferSuperRod, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, Route12_House_EventScript_SuperRodRefused
	msgbox Route12_House_Text_GiveSuperRod, MSGBOX_DEFAULT
	giveitem ITEM_SUPER_ROD
	msgbox Route12_House_Text_GaveSuperRod, MSGBOX_DEFAULT
	setflag FLAG_GOT_SUPER_ROD
	closemessage
	release
	end

Route12_House_EventScript_SuperRodRefused::
	msgbox Route12_House_Text_DontWantSuperRod, MSGBOX_DEFAULT
	closemessage
	release
	end

Route12_House_EventScript_SuperRodGot::
	msgbox Route12_House_Text_GaveSuperRod, MSGBOX_NPC
	release
	end

Route12_House_Text_OfferSuperRod:
	.string "אני האח הצעיר של גורו הדיג.\p"
	.string "אני רואה שאתה אוהב לדוג.\p"
	.string "אין לי שום ספק בכלל!\p"
	.string "נו? אני יודע שאני צודק.$"

Route12_House_Text_GiveSuperRod:
	.string "כן, כן. בדיוק כמו שחשבתי!\p"
	.string "הנה, חובב דיג! קח את זה -\n"
	.string "זו חכת על.$"

Route12_House_Text_GaveSuperRod:
	.string "כדאי לנסות לדוג בכל מקום\n"
	.string "שיש בו מים.\p"
	.string "חשוב לזכור - אפשר לתפוס\n"
	.string "פוקימונים שונים בחכות שונות.$"

Route12_House_Text_DontWantSuperRod:
	.string "מה? העיניים שלי הטעו אותי?$"

