Route1_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route1_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route1_OnTransition: 
	callnative SetTimeBasedEncounters
	end

Route1_EventScript_SchoolboyDanny::
	trainerbattle_single TRAINER_DANNY_HNS, Route1_Text_SchoolboyDanny_Seen, Route1_Text_SchoolboyDanny_Beaten
	msgbox Route1_Text_SchoolboyDanny_AfterBattle, MSGBOX_AUTOCLOSE
	end

Route1_EventScript_Quinn::
	trainerbattle_single TRAINER_QUINN_HNS, Route1_Text_CooltrainerFQuinn_Seen, Route1_Text_CooltrainerFQuinn_Beaten
	msgbox Route1_Text_CooltrainerFQuinn_AfterBattle, MSGBOX_AUTOCLOSE
	end

Route1_EventScript_Sign::
	msgbox Route1_Text_Sign, MSGBOX_SIGN
	end

Route1_Text_SchoolboyDanny_Seen:
	.string "כשמאמנים נפגשים,\n"
	.string "הדבר הראשון שעושים זה להילחם.$"

Route1_Text_SchoolboyDanny_Beaten:
	.string "אוי… יש לי מאזן שלילי…$"

Route1_Text_SchoolboyDanny_AfterBattle:
	.string "אצל מאמנים, זה מובן מאליו\n"
	.string "שנילחם בכל פעם שניפגש.$"

Route1_Text_CooltrainerFQuinn_Seen:
	.string "היי, אתה! רוצה קרב?$"

Route1_Text_CooltrainerFQuinn_Beaten:
	.string "הובסתי לגמרי…$"

Route1_Text_CooltrainerFQuinn_AfterBattle:
	.string "אתה חזק.\p"
	.string "ברור שהתאמנת קשה.$"

Route1_Text_Sign:
	.string "דרך 1\p"
	.string "העיירה פאלט - העיר וירידיאן$"
