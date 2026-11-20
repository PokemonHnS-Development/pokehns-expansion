Route26_House1_hns_MapScripts::
	.byte 0

Route26_House1_EventScript_HealWoman::
	lock
	faceplayer
	msgbox Route26_Text_HealHouseRest, MSGBOX_DEFAULT
	closemessage
	call Common_EventScript_OutOfCenterPartyHeal
	msgbox Route26_Text_HealHouseKeepAtIt, MSGBOX_DEFAULT
	release
	end


Route26_Text_HealHouseRest:
    .string "הפוקימונים שלך נראים קצת עייפים.\p"
    .string "כדאי לתת להם לנוח קצת.$"

Route26_Text_HealHouseKeepAtIt:
    .string "הנה!\p"
    .string "הפוקימונים שלך נראים מצוין!\p"
    .string "תמשיך ככה!$"
