GoldenrodCity_House3_hns_MapScripts::
	.byte 0

GoldenrodCity_House3_EventScript_PokefanM::
	lock
	faceplayer
	msgbox GoldenrodHappinessRater_Text_PokefanM, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_House3_EventScript_Twin::
	lock
	faceplayer
	msgbox GoldenrodHappinessRater_Text_Twin, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodHappinessRater_Text_PokefanM:
    .string "אני כל הזמן מפסיד בקרבות,\n"
    .string "והפוקימונים שלי מתעלפים…\p"
    .string "אולי בגלל זה הפוקימונים שלי\n"
    .string "לא כל כך אוהבים אותי…$"

GoldenrodHappinessRater_Text_Twin:
    .string "כשאני משתמשת בפריט על הפוקימון שלי,\n"
    .string "הוא נראה ממש שמח!$"
