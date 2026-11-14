Route40_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route40_MapScript_OnTransition
	.byte 0

Route40_MapScript_OnTransition::
	callnative SetTimeBasedEncounters
	goto_if_ge VAR_OLIVINE_CITY_STATE, 5, Route40_MapScript_ClearWeather
	end

Route40_MapScript_ClearWeather::
	setweather WEATHER_NONE
	end

Route40_EventScript_Simon::
	trainerbattle_single TRAINER_SIMON_HNS, Route40_Text_SwimmermSimonSeen, Route40_Text_SwimmermSimonBeaten
	msgbox Route40_Text_SwimmermSimonAfter, MSGBOX_AUTOCLOSE
	end

Route40_Text_SwimmermSimonSeen:
	.string "צריך להתחמם לפני\n"
	.string "שנכנסים למים.\p"
	.string "זה בסיסי.$"

Route40_Text_SwimmermSimonBeaten:
	.string "בסדר! די! אני נכנע!$"

Route40_Text_SwimmermSimonAfter:
	.string "העיר סיאנווד די\n"
	.string "רחוקה מכאן.$"

Route40_EventScript_Randall::
	trainerbattle_single TRAINER_RANDALL_HNS, Route40_Text_SwimmermRandallSeen, Route40_Text_SwimmermRandallBeaten
	msgbox Route40_Text_SwimmermRandallAfter, MSGBOX_AUTOCLOSE
	end

Route40_Text_SwimmermRandallSeen:
	.string "היי, אתה צעיר וחטוב!\p"
	.string "אל תרכב על הפוקימון שלך!\n"
	.string "תשחה!$"

Route40_Text_SwimmermRandallBeaten:
	.string "אוי-אוי. הפסדתי…$"

Route40_Text_SwimmermRandallAfter:
	.string "שחייה מפעילה את כל\n"
	.string "הגוף. זה בריא.$"

Route40_EventScript_Elaine::
	trainerbattle_single TRAINER_ELAINE_HNS, Route40_Text_SwimmerfElaineSeen, Route40_Text_SwimmerfElaineBeaten
	msgbox Route40_Text_SwimmerfElaineAfter, MSGBOX_AUTOCLOSE
	end

Route40_Text_SwimmerfElaineSeen:
	.string "אתה בדרך לסיאנווד?\p"
	.string "מה דעתך על קרב קצר\n"
	.string "קודם?$"

Route40_Text_SwimmerfElaineBeaten:
	.string "את הקרב הזה הפסדתי!$"

Route40_Text_SwimmerfElaineAfter:
	.string "הייתי אומרת שאני שוחה\n"
	.string "טוב ממך. כן!$"

Route40_EventScript_Paula::
	trainerbattle_single TRAINER_PAULA_HNS, Route40_Text_SwimmerfPaulaSeen, Route40_Text_SwimmerfPaulaBeaten
	msgbox Route40_Text_SwimmerfPaulaAfter, MSGBOX_AUTOCLOSE
	end

Route40_Text_SwimmerfPaulaSeen:
	.string "אני לא צריכה גלגל ים.\p"
	.string "אני נאחזת בפוקימון ים!$"

Route40_Text_SwimmerfPaulaBeaten:
	.string "אוי, מסתובב לי הראש!$"

Route40_Text_SwimmerfPaulaAfter:
	.string "כשאני צפה ככה,\n"
	.string "הגלים סוחפים אותי איתם.$"

Route40_EventScript_Woman1::
	lock
	faceplayer
	msgbox Route40_Text_Lass1, MSGBOX_DEFAULT
	closemessage
	release
	end

Route40_Text_Lass1:
	.string "אמנם אי אפשר לראות אותה מכאן,\n"
	.string "אבל סיאנווד נמצאת מעבר לים.$"

Route40_EventScript_Woman2::
	lock
	faceplayer
	msgbox Route40_Text_Lass2, MSGBOX_DEFAULT
	closemessage
	release
	end

Route40_Text_Lass2:
	.string "I came to OLIVINE by ship to see\n"
	.string "the sights and soak up the\l"
	.string "atmosphere.\p"
	.string "Being a port, it feels so\n"
	.string "different from a big city.$"

Route40_EventScript_Youngster::
	lock
	faceplayer
	msgbox Route40_Text_StandingYoungster, MSGBOX_DEFAULT
	closemessage
	release
	end

Route40_Text_StandingYoungster:
	.string "היית כבר בגבעת המאמנים?\p"
	.string "נראה לי שהרבה מאמנים קשוחים\n"
	.string "כבר התאספו שם.\p"
	.string "אבל עם כל כך הרבה תגים,\n"
	.string "לא אמור להיות לך קשה בכלל.$"

Route40_Text_Monica:
	.string "מוניקה: שמחה להכיר.\n"
	.string "אני מוניקה ממשפחת ימי השבוע.\p"
	.string "בטוח שלא תצליח לנחש מה\n"
	.string "היום האהוב עליי בשבוע!$"

Route40_Text_MonicaGivesGift:
	.string "נכון מאוד!\p"
	.string "לאות ידידות,\n"
	.string "יש לי מתנה בשבילך!$"

Route40_Text_MonicaGaveGift:
	.string "מוניקה: זה פריט שמגביר את הכוח\n"
	.string "של מהלכים מסוג תעופה.\p"
	.string "כדאי לתת את הפריט הזה\n"
	.string "לפוקימון ציפור.$"

Route40_Text_MonicaMonday:
	.string "מוניקה: האחים והאחיות שלי\n"
	.string "מפוזרים בכל מקום.\p"
	.string "נסה למצוא את כולם!$"

Route40_Text_MonicaNotMonday:
	.string "MONICA: I don't think today\n"
	.string "is Monday. How sad…$"

Route40_Text_MonicaNope:
	.string "לא היום הזה.$"

Rotue40_EventScript_Monica::
	lock
	faceplayer
	goto_if_set FLAG_GOT_SHARP_BEAK, Rotue40_EventScript_MonicaCompleted
	msgbox Route40_Text_Monica, MSGBOX_DEFAULT
	closemessage
	multichoice 20, 0, MULTI_DAYS_OF_WEEK, FALSE
	switch VAR_RESULT
	case 0, Rotue40_EventScript_MonicaNope
	case 1, Rotue40_EventScript_MonicaYes
	case 2, Rotue40_EventScript_MonicaNope
	case 3, Rotue40_EventScript_MonicaNope
	case 4, Rotue40_EventScript_MonicaNope
	case 5, Rotue40_EventScript_MonicaNope
	case 6, Rotue40_EventScript_MonicaNope
	case 7 Rotue40_EventScript_MonicaCancel
	case MULTI_B_PRESSED, Rotue40_EventScript_MonicaCancel
	closemessage
	release
	end
Rotue40_EventScript_MonicaYes::
	msgbox Route40_Text_MonicaGivesGift, MSGBOX_DEFAULT
	giveitem ITEM_SHARP_BEAK
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_GOT_SHARP_BEAK
	msgbox Route40_Text_MonicaGaveGift, MSGBOX_DEFAULT
	closemessage
	release
	end
Rotue40_EventScript_MonicaNope::
	msgbox Route40_Text_MonicaNope, MSGBOX_DEFAULT
	closemessage
	release
	end
Rotue40_EventScript_MonicaCancel::
	closemessage
	release
	end
Rotue40_EventScript_MonicaCompleted::
	msgbox Route40_Text_MonicaMonday, MSGBOX_DEFAULT
	closemessage
	release
	end
