GoldenrodCity_UndergroundEntrance_hns_MapScripts::
	.byte 0


GoldenrodUnderground_EventScript_SuperNerd::
	lock
	faceplayer
	msgbox GoldenrodUnderground1_Text_SuperNerd, MSGBOX_DEFAULT
	closemessage
	lock
	release
	end

GoldenrodUnderground_EventScript_Teacher::
	lock
	faceplayer
	msgbox GoldenrodUnderground1_Text_Teacher, MSGBOX_DEFAULT
	closemessage
	lock
	release
	end

GoldenrodUnderground1_Text_SuperNerd:
	.string "הזמינו אותי לקרב בקומה למטה.\p"
	.string "קשוח שם למטה.\n"
	.string "כדאי לך להיזהר.$"


GoldenrodUnderground1_Text_Teacher:
	.string "יש כמה חנויות למטה…\n"
	.string "אבל יש שם גם מאמנים.\p"
	.string "אני מפחדת לרדת לשם.$"
