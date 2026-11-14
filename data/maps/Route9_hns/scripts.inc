Route9_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route9_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route9_OnTransition: 
	callnative SetTimeBasedEncounters
	end

Route9_EventScript_Dean::
	trainerbattle_single TRAINER_DEAN_HNS, Route9_Text_CamperDeanSeen, Route9_Text_CamperDeanBeaten
	msgbox Route9_Text_CamperDeanAfter, MSGBOX_AUTOCLOSE
	end

Route9_EventScript_Heidi::
	trainerbattle_single TRAINER_HEIDI_HNS, Route9_Text_PicnickerHeidiSeen, Route9_Text_PicnickerHeidiBeaten
	msgbox Route9_Text_PicnickerHeidiAfter, MSGBOX_AUTOCLOSE
	end

Route9_EventScript_Edna::
	trainerbattle_single TRAINER_EDNA_HNS, Route9_Text_PicnickerEdnaSeen, Route9_Text_PicnickerEdnaBeaten
	msgbox Route9_Text_PicnickerEdnaAfter, MSGBOX_AUTOCLOSE
	end

Route9_EventScript_Sid::
	trainerbattle_single TRAINER_SID_HNS, Route9_Text_CamperSidSeen, Route9_Text_CamperSidBeaten
	msgbox Route9_Text_CamperSidAfter, MSGBOX_AUTOCLOSE
	end

Route9_EventScript_Tim::
	trainerbattle_single TRAINER_TIM_HNS, Route9_Text_HikerTimSeen, Route9_Text_HikerTimBeaten
	msgbox Route9_Text_HikerTimAfter, MSGBOX_AUTOCLOSE
	end

Route9_EventScript_Sidney::
	trainerbattle_single TRAINER_SIDNEY_HNS, Route9_Text_HikerSidneySeen, Route9_Text_HikerSidneyBeaten
	msgbox Route9_Text_HikerSidneyAfter, MSGBOX_AUTOCLOSE
	end

Route9_EventScript_Sign::
	msgbox Route9_Text_Sign, MSGBOX_SIGN
	end

Route9_EventScript_Item_Flash_Cannon::
    finditem ITEM_TM_FLASH_CANNON
    end

Route9_Text_CamperDeanSeen:
	.string "באתי לחקור את מערת האבן.$"

Route9_Text_CamperDeanBeaten:
	.string "וואו! מסוכן, אחי.$"

Route9_Text_CamperDeanAfter:
	.string "הפוקימונים שלי נפצעו עוד לפני\n"
	.string "שנכנסנו למערת האבן.\p"
	.string "כדאי שאקח אותם מיד\n"
	.string "למרכז פוקימון.$"

Route9_Text_PicnickerHeidiSeen:
	.string "היית פעם בפיקניק?\p"
	.string "זה כל כך כיף!$"

Route9_Text_PicnickerHeidiBeaten:
	.string "אוווו!$"

Route9_Text_PicnickerHeidiAfter:
	.string "אנחנו אופים המון מטעמים\n"
	.string "ומחלקים אותם לכולם.\p"
	.string "הם טעימים!$"

Route9_Text_CamperSidSeen:
	.string "היי, אתה! אל תלכלך!$"

Route9_Text_CamperSidBeaten:
	.string "רק הערתי…$"

Route9_Text_CamperSidAfter:
	.string "סליחה. לא לכלכת.\n"
	.string "זאת הייתה טעות שלי.$"

Route9_Text_PicnickerEdnaSeen:
	.string "אסור לאנשים להשאיר\n"
	.string "אחריהם לכלוך.$"

Route9_Text_PicnickerEdnaBeaten:
	.string "אוף… הפסדתי…$"

Route9_Text_PicnickerEdnaAfter:
	.string "חיסכון באנרגיה חשוב, אבל\n"
	.string "הסביבה חיונית עוד יותר.$"

Route9_Text_HikerTimSeen:
	.string "היא תבוא מסביב להר הכסף\n"
	.string "כשהיא תבוא…\p"
	.string "הר הכסף נמצא בג'וטו, נכון?$"

Route9_Text_HikerTimBeaten:
	.string "הייתי עסוק מדי בשירה…$"

Route9_Text_HikerTimAfter:
	.string "קרבות הם עניין של ריכוז.$"

Route9_Text_HikerSidneySeen:
	.string "אגלה לך סוד.\p"
	.string "אבל קודם, נילחם!$"

Route9_Text_HikerSidneyBeaten:
	.string "אוף, לא! הפסדתי…$"

Route9_Text_HikerSidneyAfter:
	.string "מפעל החשמל נמצא מעבר\n"
	.string "לנהר קטן.$"

Route9_Text_Sign:
	.string "ROUTE 9\p"
	.string "CERULEAN CITY - ROCK TUNNEL$"
