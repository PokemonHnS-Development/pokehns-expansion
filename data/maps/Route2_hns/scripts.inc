Route2_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route2_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route2_OnTransition: 
	callnative SetTimeBasedEncounters
	end

Route2_EventScript_Sign::
	msgbox Route2_Text_Sign, MSGBOX_SIGN
	end

Route2_EventScript_CaveSign::
	msgbox Route2_Text_DiglettsCaveSign, MSGBOX_SIGN
	end

Route2_EventScript_Carbos::
    finditem ITEM_CARBOS
    end

Route2_EventScript_Nugget::
    finditem ITEM_NUGGET
    end

Route2_Text_RobRegister:
	.string "בוא נחליף מספרים!$"

Route2_Text_RobRematchIntro:
	.string "תפסתי עוד יותר חרקים!\n"
	.string "תראה אותם!$"

Route2_Text_RobRematchDefeat:
	.string "אני צריך חרקים טובים יותר!$"

Route2_Text_RobPostRematch:
	.string "תפסתי כל חרק ביער וירידיאן.\n"
	.string "יש איפשהו יער טוב יותר?$"

Route2_Text_BugCatcherRob_Seen:
	.string "פוקימוני החרק שלי קשוחים.\n"
	.string "תתכונן להפסיד!$"

Route2_Text_BugCatcherRob_Beaten:
	.string "הובסתי לגמרי…$"

Route2_Text_BugCatcherRob_AfterBattle:
	.string "אני הולך לחפש פוקימוני חרק\n"
	.string "חזקים יותר.$"

Route2_Text_BugCatcherEd_Seen:
	.string "אם הולכים בדשא גבוה עם מכנסיים\n"
	.string "קצרים, מקבלים שריטות וחתכים?$"

Route2_Text_BugCatcherEd_Beaten:
	.string "איי, איי, איי!$"

Route2_Text_BugCatcherEd_AfterBattle:
	.string "הם ממש צורבים כשנכנסים\n"
	.string "לאמבטיה.$"

Route2_Text_BugCatcherDoug_Seen:
	.string "למה בנות לא אוהבות פוקימוני חרק?$"

Route2_Text_BugCatcherDoug_Beaten:
	.string "לא טוב!$"

Route2_Text_BugCatcherDoug_AfterBattle:
	.string "פוקימוני חרק נמעכים כמו בובות\n"
	.string "פרווה כשלוחצים להם על הבטן.\p"
	.string "אני אוהב את התחושה!$"

Route2_Text_Sign:
	.string "דרך 2\p"
	.string "העיר וירידיאן - העיר פיוטר$"

Route2_Text_DiglettsCaveSign:
	.string "מערת דיגלט$"

