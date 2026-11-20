Route11_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route11_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route11_OnTransition:
	callnative SetTimeBasedEncounters
	end

Route11_EventScript_Owen::
	trainerbattle_single TRAINER_OWEN_HNS, Route11_Text_YoungsterOwenSeen, Route11_Text_YoungsterOwenBeaten
	msgbox Route11_Text_YoungsterOwenAfterBattle, MSGBOX_AUTOCLOSE
	end

Route11_EventScript_Jason::
	trainerbattle_single TRAINER_JASON_HNS, Route11_Text_YoungsterJasonSeen, Route11_Text_YoungsterJasonBeaten
	msgbox Route11_Text_YoungsterJasonAfterBattle, MSGBOX_AUTOCLOSE
	end

Route11_EventScript_Herman::
	trainerbattle_single TRAINER_HERMAN_HNS, Route11_Text_PsychicHermanSeen, Route11_Text_PsychicHermanBeaten
	msgbox Route11_Text_PsychicHermanAfterBattle, MSGBOX_AUTOCLOSE
	end

Route11_EventScript_Fidel::
	trainerbattle_single TRAINER_FIDEL_HNS, Route11_Text_PsychicFidelSeen, Route11_Text_PsychicFidelBeaten
	msgbox Route11_Text_PsychicFidelAfterBattle, MSGBOX_AUTOCLOSE
	end

Route11_EventScript_Engineer::
	msgbox Route11_Text_Engineer, MSGBOX_NPC
	end

Route11_EventScript_Item_Grass_Knot::
    finditem ITEM_TM_GRASS_KNOT
    end

Route11_Text_Engineer:
	.string "ראיתי פוקימון מוזר מטפס על העצים,\n"
	.string "אבל הוא לא נראה כמו מאנקי…$"

Route11_Text_YoungsterOwenSeen:
	.string "אין רמאויות בקרבות פוקימונים.\p"
	.string "בוא נשמור על משחק הוגן!$"

Route11_Text_YoungsterOwenBeaten:
	.string "מה? איך זה קרה?$"

Route11_Text_YoungsterOwenAfterBattle:
	.string "נלחמתי בהגינות ובכבוד.\p"
	.string "אני לא מתחרט על זה בכלל.$"

Route11_Text_YoungsterJasonSeen:
	.string "זה קצת מגרד ומדגדג כשאני\n"
	.string "הולך עם מכנסיים קצרים בדשא.$"

Route11_Text_YoungsterJasonBeaten:
	.string "איי-יאאה! ריסקו אותי!$"

Route11_Text_YoungsterJasonAfterBattle:
	.string "אני הולך לתפוס עוד פוקימונים\n"
	.string "בדשא.$"

Route11_Text_PsychicHermanSeen:
	.string "…$"

Route11_Text_PsychicHermanBeaten:
	.string "…$"

Route11_Text_PsychicHermanAfterBattle:
	.string "…\p"
	.string "הפסדתי כשהעיניים שלי היו עצומות…$"

Route11_Text_PsychicFidelSeen:
	.string "אני רואה את זה…\p"
	.string "את כל מה שיש לראות בך…$"

Route11_Text_PsychicFidelBeaten:
	.string "לא חזיתי את העוצמה שלך…$"

Route11_Text_PsychicFidelAfterBattle:
	.string "כוחה של אמונה…\p"
	.string "הכוח שלך נובע מהאמונה\n"
	.string "בפוקימונים שלך.$"

Route11_Text_Sign:
	.string "ROUTE 11$"

