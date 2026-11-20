SproutTower_2F_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SproutTower_2F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

SproutTower_2F_OnTransition: 
	callnative SetTimeBasedEncounters
	end

SproutTower_2F_EventScript_SageNico::
	trainerbattle_single TRAINER_NICO_HNS, SproutTower_Text_SageNico_Seen, SproutTower_Text_SageNico_Beaten
	msgbox SproutTower_Text_SageNico_AfterBattle, MSGBOX_AUTOCLOSE
	end

SproutTower_2F_EventScript_SageEdmond::
	trainerbattle_single TRAINER_EDMOND_HNS, SproutTower_Text_SageEdmond_Seen, SproutTower_Text_SageEdmond_Beaten
	msgbox SproutTower_Text_SageEdmond_AfterBattle, MSGBOX_AUTOCLOSE
	end

SproutTower_2F_EventScript_Statue::
	lock
	msgbox SproutTower_Text_2F_Statue, MSGBOX_AUTOCLOSE
	release
	end

SproutTower_2F_EventScript_Xdefend::
	finditem ITEM_X_DEFEND
	end

SproutTower_Text_SageNico_Seen:
	.string "גם אם נילחם בכל הכוח,\n"
	.string "המגדל יישאר איתן.$"

SproutTower_Text_SageNico_Beaten:
	.string "נלחמתי בכל כוחי, אבל אני חלש מדי.$"

SproutTower_Text_SageNico_AfterBattle:
	.string "העמוד הגמיש מגן על המגדל,\n"
	.string "אפילו מפני רעידות אדמה.$"

SproutTower_Text_SageEdmond_Seen:
	.string "…להתנודד כמו עלים ברוח…$"

SproutTower_Text_SageEdmond_Beaten:
	.string "אוי, אני חלש!$"

SproutTower_Text_SageEdmond_AfterBattle:
	.string "ניסיתי לחקות בקרב את התנועות\n"
	.string "העדינות של בלספראוט…\p"
	.string "אבל לא התאמנתי מספיק.$"

SproutTower_Text_2F_Statue:
	.string "פסל של פוקימון…\p"
	.string "הוא נראה מכובד מאוד.$"
