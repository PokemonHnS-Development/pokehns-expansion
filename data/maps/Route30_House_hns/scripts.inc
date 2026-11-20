Route30_House_hns_MapScripts::
	.byte 0

Route30_House_EventScript_BaldMan::
	lock
	faceplayer
	goto_if_set FLAG_GOT_BERRY_ROUTE_30_HOUSE, Route30_House_EventScript_BaldMan2
	msgbox Route30_BerryHouse_Text_MonEatBerries, MSGBOX_DEFAULT
	giveitem ITEM_CHERI_BERRY
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	closemessage
	setflag FLAG_GOT_BERRY_ROUTE_30_HOUSE
Route30_House_EventScript_BaldMan2::
	msgbox Route30_BerryHouse_Text_CheckTrees, MSGBOX_DEFAULT
	closemessage
	release
	end

Route30_BerryHouse_Text_MonEatBerries:
	.string "אם תלך בשביל הזה צפונה,\n"
	.string "תגיע לבית של מר פוקימון.\p"
	.string "אבל לפני שתלך, הרשה לי\n"
	.string "לספר לך על פירות!\p"
	.string "פוקימונים נעשים בריאים יותר\n"
	.string "כשהם אוכלים פירות.\p"
	.string "הם יכולים אפילו לאכול בקרב\n"
	.string "פירות שהם מחזיקים.\p"
	.string "בנוסף, קורט בעיירה אזייליה\n"
	.string "יכול להפוך פירות לכדורים.\p"
	.string "הנה. אתן לך אחד!$"

Route30_BerryHouse_Text_CheckTrees:
	.string "כדאי לחפש פירות על עצים.\n"
	.string "הם צומחים מחדש אחרי כמה שעות.$"
