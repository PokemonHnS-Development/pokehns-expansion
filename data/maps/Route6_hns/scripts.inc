Route6_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route6_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route6_OnTransition:
	callnative SetTimeBasedEncounters
	end

Route6_EventScript_Rex::
	trainerbattle_single TRAINER_REX_HNS, PokefanM_Text_RexSeen, PokefanM_Text_RexBeaten
	msgbox PokefanM_Text_RexAfter, MSGBOX_AUTOCLOSE
	end

Route6_EventScript_Allan::
	trainerbattle_single TRAINER_ALLAN_HNS, PokefanM_Text_AllanSeen, PokefanM_Text_AllanBeaten
	msgbox PokefanM_Text_AllanAfter, MSGBOX_AUTOCLOSE
	end

Route6_EventScript_Pokefan::
	msgbox Route6_Text_PokefanM, MSGBOX_NPC
	end

Route6_EventScript_Sign::
	msgbox Route6_Text_UndergroundPathSign, MSGBOX_SIGN
	end

Route6_EventScript_Item_Silver_Wind::
    finditem ITEM_TM_SILVER_WIND
    end

Route6_Text_PokefanM:
	.string "הדרך סגורה עד שהבעיה\n"
	.string "במפעל החשמל תיפתר.$"

Route6_Text_UndergroundPathSign:
	.string "מעבר תת-קרקעי\p"
	.string "העיר סרוליאן - העיר ורמיליון$"

PokefanM_Text_RexSeen:
	.string "הסטנטלר שלי הוא הכי חמוד\n"
	.string "בעולם.$"

PokefanM_Text_RexBeaten:
	.string "הסטנטלר שלי!$"

PokefanM_Text_RexAfter:
	.string "תראה כמה מקסים הסטנטלר שלי!\p"
	.string "הוא לא חמוד מספיק כדי\n"
	.string "להמיס לך את הלב?$"

PokefanM_Text_AllanSeen:
	.string "הגרנבול שלי הוא הכי חמוד\n"
	.string "בעולם.$"

PokefanM_Text_AllanBeaten:
	.string "הגרנבול שלי!$"

PokefanM_Text_AllanAfter:
	.string "תראה כמה מקסים הגרנבול שלי!\p"
	.string "הוא לא חמוד מספיק כדי\n"
	.string "להמיס לך את הלב?$"

