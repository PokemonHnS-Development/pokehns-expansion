OlivineCity_House3_hns_MapScripts::
	.byte 0

OlivineCityHouse3_EventScriptFishingGuru::
	lock
	faceplayer
	checkitem ITEM_GOOD_ROD
	goto_if_eq VAR_RESULT, TRUE, OlivineCityHouse3_EventScriptFishingGuru2
	msgbox OlivineCity_Text_OfferGoodRod, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, OlivineCityHouse3_EventScriptFishingGuruRefused
	msgbox OlivineCity_Text_GiveGoodRod, MSGBOX_DEFAULT
	giveitem ITEM_GOOD_ROD
	msgbox OlivineCity_Text_GaveGoodRod, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCityHouse3_EventScriptFishingGuru2::
	msgbox OlivineCity_Text_HaveGoodRod, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCityHouse3_EventScriptFishingGuruRefused::
	msgbox OlivineCity_Text_DontWantGoodRod, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_Text_OfferGoodRod:
	.string "אוליבין שוכנת על הים!\p"
	.string "ואם היא על הים, בטוח\n"
	.string "שיש פה דגים!\p"
	.string "אני דג כאן כבר 30 שנה.\p"
	.string "רוצה לעמוד מול הים\n"
	.string "ולנסות את כוחך בדיג?$"

OlivineCity_Text_GiveGoodRod:
	.string "אה, חה חה! נולד לנו\n"
	.string "דייג חדש!$"

OlivineCity_Text_GaveGoodRod:
	.string "דגים יש לא רק בים, הם נמצאים\n"
	.string "בכל מקום שיש בו מים.\p"
	.string "דרך אגב, הפוקדקס שלך מציג\n"
	.string "קבוצות דיג של פוקימונים.\p"
	.string "במקומות שונים אפשר למצוא\n"
	.string "סוגי דגים דומים.$"

OlivineCity_Text_DontWantGoodRod:
	.string "מההה? אתה לא אוהב לדוג?!\n"
	.string "זה בלתי נתפס!$"

OlivineCity_Text_HaveGoodRod:
	.string "מה נשמע?\n"
	.string "תפסת את הדג הגדול?$"
