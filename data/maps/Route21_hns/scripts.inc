Route21_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route21_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route21_OnTransition:
	callnative SetTimeBasedEncounters
	end

Route21_EventScript_Seth::
	trainerbattle_single TRAINER_SETH_HNS, Route21_Text_SwimmermSethSeen, Route21_Text_SwimmermSethBeaten
	msgbox Route21_Text_SwimmermSethAfterBattle, MSGBOX_AUTOCLOSE
	end

Route21_EventScript_Nikki::
	trainerbattle_single TRAINER_NIKKI_HNS, Route21_Text_SwimmerfNikkiSeen, Route21_Text_SwimmerfNikkiBeaten
	msgbox Route21_Text_SwimmerfNikkiAfterBattle, MSGBOX_AUTOCLOSE
	end

Route21_EventScript_Arnold::
	trainerbattle_single TRAINER_ARNOLD_HNS, Route21_Text_FisherArnoldSeen, Route21_Text_FisherArnoldBeaten
	msgbox Route21_Text_FisherArnoldAfterBattle, MSGBOX_AUTOCLOSE
	end

Route21_Text_SwimmermSethSeen:
	.string "יבשה באופק! חייב להמשיך!$"

Route21_Text_SwimmermSethBeaten:
	.string "גלוג…$"

Route21_Text_SwimmermSethAfterBattle:
	.string "היה איזה בחור יהיר\n"
	.string "ליד הר הגעש של סיננבר.$"

Route21_Text_SwimmerfNikkiSeen:
	.string "אם אני מנצחת, אתה חייב לעזור לי\n"
	.string "למרוח קרם שיזוף!$"

Route21_Text_SwimmerfNikkiBeaten:
	.string "אני חוששת מכוויות שמש…$"

Route21_Text_SwimmerfNikkiAfterBattle:
	.string "אני צריכה להיזהר מכתמים בעור\n"
	.string "בגלל השמש.$"

Route21_Text_FisherArnoldSeen:
	.string "משעמם לי לדוג. בוא נילחם!$"

Route21_Text_FisherArnoldBeaten:
	.string "כישלון מוחלט…$"

Route21_Text_FisherArnoldAfterBattle:
	.string "אני פשוט אחזור לדוג…$"

