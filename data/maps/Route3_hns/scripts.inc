Route3_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route3_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route3_OnTransition: 
	callnative SetTimeBasedEncounters
	end

Route3_EventScript_Otis::
	trainerbattle_single TRAINER_OTIS_HNS, Route3_Text_FirebreatherOtis_Seen, Route3_Text_FirebreatherOtis_Beaten
	msgbox Route3_Text_FirebreatherOtis_AfterBattle, MSGBOX_AUTOCLOSE
	end

Route3_EventScript_Warren::
	trainerbattle_single TRAINER_WARREN_HNS, Route3_Text_YoungsterWarren_Seen, Route3_Text_YoungsterWarren_Beaten
	msgbox Route3_Text_YoungsterWarren_AfterBattle, MSGBOX_AUTOCLOSE
	end

Route3_EventScript_Jimmy::
	trainerbattle_single TRAINER_JIMMY_HNS, Route3_Text_YoungsterJimmy_Seen, Route3_Text_YoungsterJimmy_Beaten
	msgbox Route3_Text_YoungsterJimmy_AfterBattle, MSGBOX_AUTOCLOSE
	end

Route3_EventScript_Burt::
	trainerbattle_single TRAINER_BURT_HNS, Route3_Text_FirebreatherBurt_Seen, Route3_Text_FirebreatherBurt_Beaten
	msgbox Route3_Text_FirebreatherBurt_AfterBattle, MSGBOX_AUTOCLOSE
	end

Route3_EventScript_Sign::
	msgbox Route3_Text_MtMoonSquareSign, MSGBOX_SIGN
	end

Route3_Text_FirebreatherOtis_Seen:
	.string "אה! מזג האוויר נהדר כתמיד.$"

Route3_Text_FirebreatherOtis_Beaten:
	.string "יש שמש, אבל אני רטוב לגמרי…$"

Route3_Text_FirebreatherOtis_AfterBattle:
	.string "כשיורד גשם, קשה להצית\n"
	.string "את האש…$"

Route3_Text_YoungsterWarren_Seen:
	.string "הממ… אני לא יודע מה לעשות…$"

Route3_Text_YoungsterWarren_Beaten:
	.string "ידעתי שאפסיד…$"

Route3_Text_YoungsterWarren_AfterBattle:
	.string "נראית חזק.\p"
	.string "פחדתי להתמודד איתך…$"

Route3_Text_YoungsterJimmy_Seen:
	.string "אני יכול לרוץ כמו הרוח!$"

Route3_Text_YoungsterJimmy_Beaten:
	.string "עפתי עם הרוח!$"

Route3_Text_YoungsterJimmy_AfterBattle:
	.string "אני לובש מכנסיים קצרים כל השנה.\p"
	.string "זאת מדיניות האופנה שלי.$"

Route3_Text_FirebreatherBurt_Seen:
	.string "קרבו, קרבו, בואו לראות!$"

Route3_Text_FirebreatherBurt_Beaten:
	.string "איי! זה חם!$"

Route3_Text_FirebreatherBurt_AfterBattle:
	.string "יורק האש הגדול ביותר בקאנטו,\n"
	.string "זה אני.\p"
	.string "אבל לא המאמן הכי טוב…$"

Route3_Text_MtMoonSquareSign:
	.string "כיכר הר הירח\p"
	.string "פשוט עולים במדרגות.$"

