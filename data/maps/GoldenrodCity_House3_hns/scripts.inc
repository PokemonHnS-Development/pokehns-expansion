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
    .string "Sigo perdiendo batallas y mis\n"
    .string "POKéMON terminan debilitados…\p"
    .string "Tal vez por eso a mis POKéMON no\n"
    .string "les gusto mucho…$"

GoldenrodHappinessRater_Text_Twin:
    .string "Cuando uso un objeto en mi POKéMON,\n"
    .string "¡se pone muy feliz!$"
