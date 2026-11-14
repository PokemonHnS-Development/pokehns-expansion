Route39_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route39_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route39_OnTransition: 
	callnative SetTimeBasedEncounters
	end

Route39_EventScript_Item_TM::
	finditem ITEM_TM_DRAIN_PUNCH
	end

Route39_EventScript_Item_Nugget::
	finditem ITEM_BIG_NUGGET
	end

Route39_EventScript_LegendaryTrigger::
	lock
	clearflag FLAG_HIDE_ROUTE39_SHADOW
	addobject LOCALID_R39_SHADOW
	playse SE_M_RAZOR_WIND
	applymovement LOCALID_R39_SHADOW, Route39_Movement_ShadowSlideDown
	waitmovement 0
	setflag FLAG_HIDE_ROUTE39_SHADOW
	removeobject LOCALID_R39_SHADOW
	playse SE_PIN
	applymovement LOCALID_R39_BAOBA, Common_Movement_QuestionMark
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_QuestionMark
	turnobject LOCALID_R39_BAOBA DIR_SOUTH
	turnobject OBJ_EVENT_ID_PLAYER DIR_SOUTH
	delay 60

	getplayerxy VAR_TEMP_0, VAR_TEMP_1

	call_if_eq VAR_TEMP_1, 20, Route39_EventScript_BaobaMovement1
	call_if_eq VAR_TEMP_1, 21, Route39_EventScript_BaobaMovement2
	call_if_eq VAR_TEMP_1, 22, Route39_EventScript_BaobaMovement3
	call_if_eq VAR_TEMP_1, 23, Route39_EventScript_BaobaMovement4

	turnobject LOCALID_R39_BAOBA DIR_EAST
	turnobject OBJ_EVENT_ID_PLAYER DIR_WEST
Route39_EventScript_ChooseLegend::
	msgbox Route39_Text_ChooseLegend, MSGBOX_DEFAULT
	multichoice 20, 8, MULTI_GOLDSILVER, FALSE
	switch VAR_RESULT
	case 0, Route39_EventScript_LegendaryTriggerGold
	case 1, Route39_EventScript_LegendaryTriggerSilver
	case MULTI_B_PRESSED, Route39_EventScript_ChooseLegend
	release
	end

Route39_EventScript_BaobaMovement1::
	applymovement LOCALID_R39_BAOBA, Route39_Movement_Baoba1
	waitmovement 0
	return
Route39_EventScript_BaobaMovement2::
	applymovement LOCALID_R39_BAOBA, Route39_Movement_Baoba2
	waitmovement 0
	return
Route39_EventScript_BaobaMovement3::
	applymovement LOCALID_R39_BAOBA, Route39_Movement_Baoba3
	waitmovement 0
	return
Route39_EventScript_BaobaMovement4::
	applymovement LOCALID_R39_BAOBA, Route39_Movement_Baoba4
	waitmovement 0
	return

Route39_Movement_Baoba1:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	step_end
Route39_Movement_Baoba2:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	step_end
Route39_Movement_Baoba3:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	step_end
Route39_Movement_Baoba4:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	step_end

Route39_EventScript_LegendaryTriggerGold::
	setvar VAR_LUGIA_OR_HOOH, 2
	goto Route39_EventScript_BaobaIntro

Route39_EventScript_LegendaryTriggerSilver::
	setvar VAR_LUGIA_OR_HOOH, 1
	goto Route39_EventScript_BaobaIntro

Route39_EventScript_BaobaIntro::
	msgbox Route39_Text_BaobaIntro, MSGBOX_DEFAULT
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox Route39_Text_Registered, MSGBOX_DEFAULT
	waitfanfare
	msgbox Route39_Text_WillCall, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_R39_BAOBA, Route39_Movement_BaobaLeave
	waitmovement 0
	setflag FLAG_ENABLE_BAOBA_MATCH_CALL
	removeobject LOCALID_R39_BAOBA
	release
	end

Route39_Text_ChooseLegend::
	.string "באובה: אלוהים אדירים! הצל הזה\n"
	.string "היה של פוקימון?\p"
	.string "הספקת לראות אותו טוב?\n"
	.string "לא הבחנתי באיזה צבע הוא היה…$"

Route39_Text_BaobaIntro::
	.string "כמה מוזר…\p"
	.string "…אוהו! מה שאתה מחזיק זה…\n"
	.string "מה שקוראים לו… פוקדקס!\p"
	.string "לא ראיתי כזה כבר שנים.\p"
	.string "קוראים לי באובה! פעם ניהלתי\n"
	.string "אזור ספארי בעיר פושיה.\p"
	.string "אבל הוא התיישן מול כל\n"
	.string "אפשרויות הבידור החדשות.\p"
	.string "החלטתי לנסוע לחו”ל כדי ללמוד\n"
	.string "את הטכנולוגיה החדשה ביותר\p"
	.string "ולפתוח אזור ספארי חדיש\n"
	.string "בסיאנווד.\p"
	.string "אולי זה לא סתם צירוף מקרים\n"
	.string "שאנחנו משוחחים.\p"
	.string "מה דעתך שנחליף מספרים\n"
	.string "בפוקיגיר?\p"
	.string "כשאזור הספארי ייפתח, אתקשר\n"
	.string "אליך לפני כל אחד אחר!$"

Route39_Text_Registered:
	.string "{PLAYER} רשם את באובה\n"
	.string "בפוקיגיר!$"


Route39_Text_WillCall:
	.string "באובה: אודיע לך\n"
	.string "בפוקיגיר בקרוב!$"

Route39_Movement_BaobaLeave:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

Route39_Movement_ShadowSlideDown:
	slide_down
	slide_down
	slide_down
	slide_down
	slide_down
	slide_down
	slide_down
	slide_down
	slide_down
	slide_down
	slide_down
	slide_down
	slide_down
	slide_down
	slide_down
	slide_down
	slide_down
	slide_down
	slide_down
	slide_down
	step_end

Route39_EventScript_Woman::
	lock
	faceplayer
	msgbox Route39_Text_Woman, MSGBOX_DEFAULT
	closemessage
	release
	end

Route39_Text_Woman:
	.string "הצל הזה… אולי זה היה\n"
	.string "פידג'י ענק?$"

Route39_EventScript_Miltank::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_MILTANK, CRY_MODE_NORMAL
	msgbox Route39_Text_Miltank, MSGBOX_DEFAULT
	waitmoncry
	release
	end

Route39_Text_Miltank:
	.string "מילטנק: מווו!$"

Route39_EventScript_Eugene::
	trainerbattle_single TRAINER_EUGENE_HNS, Route39_Text_SailorEugeneSeen, Route39_Text_SailorEugeneBeaten
	msgbox Route39_Text_SailorEugeneAfter, MSGBOX_AUTOCLOSE
	end

Route39_Text_SailorEugeneSeen:
	.string "בדיוק חזרתי לאוליבין.\p"
	.string "אז מה דעתך על קרב פוקימונים?$"

Route39_Text_SailorEugeneBeaten:
	.string "אוואאארג!$"

Route39_Text_SailorEugeneAfter:
	.string "את הפוקימונים שלי תפסתי\n"
	.string "וגידלתי מעבר לים.\p"
	.string "הם החברים שלי\n"
	.string "בהפלגות הארוכות.$"

Route39_EventScript_Derek::
	trainerbattle_single TRAINER_DEREK_HNS, Route39_Text_PokefanMDerekSeen, Route39_Text_PokefanMDerekBeaten, Route39_EventScript_RegisterDerek
	goto_if_set FLAG_DEREK_HAS_ITEM_HNS, Route39_EventScript_DerekGiveItem
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route39_EventScript_RematchDerek
	msgbox Route39_Text_PokefanMDerekAfter, MSGBOX_AUTOCLOSE
	end

Route39_EventScript_RematchDerek::
	trainerbattle_rematch TRAINER_DEREK_HNS, Route39_Text_PokefanMDerekSeen, Route39_Text_PokefanMDerekBeaten
	msgbox Route39_Text_PokefanMDerekAfter, MSGBOX_AUTOCLOSE
	end

Route39_EventScript_RegisterDerek::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route39_Text_DerekRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_DEREK_HNS
	release
	end

Route39_EventScript_DerekGiveItem::
	msgbox Route39_Text_DerekHasItem, MSGBOX_DEFAULT
	giveitem VAR_DEREK_ITEM_HNS
	goto_if_eq VAR_RESULT, FALSE, Route39_EventScript_DerekNoRoom
	clearflag FLAG_DEREK_HAS_ITEM_HNS
	msgbox Route39_Text_DerekGaveItem, MSGBOX_AUTOCLOSE
	end

Route39_EventScript_DerekNoRoom::
	msgbox Route39_Text_DerekNoRoom, MSGBOX_AUTOCLOSE
	end

Route39_Text_PokefanMDerekSeen:
	.string "זה זמן טוב להשוויץ\n"
	.string "בפיקאצ'ו שלי!$"

Route39_Text_PokefanMDerekBeaten:
	.string "לא היה לי זמן להשוויץ\n"
	.string "בפיקאצ'ו…$"

Route39_Text_PokefanMDerekAfter:
	.string "אני לא מקשיב\n"
	.string "להתרברבויות שלך!\p"
	.string "לנו הפוקיפאנים יש מדיניות:\n"
	.string "לא מקשיבים להתרברבויות!$"

Route39_EventScript_Ruth::
	trainerbattle_single TRAINER_RUTH_HNS, Route39_Text_PokefanFRuthSeen, Route39_Text_PokefanFRuthBeaten
	msgbox Route39_Text_PokefanFRuthAfter, MSGBOX_AUTOCLOSE
	end

Route39_Text_PokefanFRuthSeen:
	.string "איזה פוקימונים מתוקים.\p"
	.string "בוא נציג את הפוקימונים שלנו\n"
	.string "יחד, באותו הזמן.$"

Route39_Text_PokefanFRuthBeaten:
	.string "לא אכפת לי להפסיד.$"

Route39_Text_PokefanFRuthAfter:
	.string "שמעת על\n"
	.string "פוקימונים תינוקות?\p"
	.string "אני בטוחה שהם פשוט מקסימים!$"

Route39_EventScript_Norman::
	trainerbattle_single TRAINER_NORMAN_HNS, Route39_Text_PsychicNormanSeen, Route39_Text_PsychicNormanBeaten
	msgbox Route39_Text_PsychicNormanAfter, MSGBOX_AUTOCLOSE
	end

Route39_Text_PsychicNormanSeen:
	.string "בוא נראה מה\n"
	.string "הפוקימונים שלך מסוגלים לעשות.$"

Route39_Text_PsychicNormanBeaten:
	.string "או, לפוקימונים שלך\n"
	.string "יש פוטנציאל.$"

Route39_Text_PsychicNormanAfter:
	.string "אתה יודע שלפוקימונים\n"
	.string "יש יכולות שונות?\p"
	.string "גם אצל אנשים זה ככה.\n"
	.string "לכל אחד יש פוטנציאל שונה.$"

Route39_EventScript_Jamie::
	trainerbattle_single TRAINER_JAMIE_HNS, Route39_Text_PokefanFJaimeSeen, Route39_Text_PokefanFJaimeBeaten
	msgbox Route39_Text_PokefanFJaimeAfter, MSGBOX_AUTOCLOSE
	end

Route39_Text_PokefanFJaimeSeen:
	.string "הגעת בדיוק בזמן הנכון.\p"
	.string "בוא נילחם.$"

Route39_Text_PokefanFJaimeBeaten:
	.string "אוי, כמה מאכזב…$"

Route39_Text_PokefanFJaimeAfter:
	.string "פגשתי את אמבריאון בלילה,\n"
	.string "ממש כאן בדרך 39.\p"
	.string "אני לא בטוחה למה, אבל נראה\n"
	.string "שהוא אוהב כשאני מאמנת אותו כאן.\p"
	.string "נראה שהאימונים כאן הופכים אותו\n"
	.string "לידידותי יותר מבכל מקום אחר.$"

Route39_EventScript_Sign1::
	lock
	msgbox Route39_Text_Sign, MSGBOX_SIGN
	closemessage
	release
	end

Route39_Text_Sign:
	.string "דרך 39\p"
	.string "העיר אוליבין - העיר אקרוטיק$"

Route39_EventScript_Sign2::
	lock
	msgbox Route39_Text_MoomooFarmSign, MSGBOX_SIGN
	closemessage
	release
	end

Route39_Text_MoomooFarmSign:
	.string "חוות מומו\p"
	.string "תיהנו מהחלב הטרי והטעים שלנו$"

Route39_EventScript_Sign3::
	lock
	msgbox Route39_Text_TrainerTips, MSGBOX_SIGN
	closemessage
	release
	end

Route39_Text_TrainerTips:
	.string "טיפים למאמנים\p"
	.string "אפשר להשתמש בנגיחה על עצים\n"
	.string "כדי להפיל מהם פוקימונים.\p"
	.string "כל מיני פוקימונים\n"
	.string "נופלים מהעצים.\p"
	.string "כדאי להשתמש בנגיחה על כל עץ\n"
	.string "שרואים!$"

Route39_Text_DerekRegister:
	.string "אני לא מקשיב\n"
	.string "להתרברבויות שלך!\p"
	.string "לנו הפוקיפאנים יש מדיניות:\n"
	.string "לא מקשיבים להתרברבויות!$"

Route39_Text_DerekHasItem:
	.string "היי! השוויצתי בפיקאצ'ו שלי\n"
	.string "ומצאתי משהו.\p"
	.string "הנה, זה בשבילך!$"

Route39_Text_DerekGaveItem:
	.string "פיקאצ'ו הוא הכי טוב!\n"
	.string "אתה לא מסכים?$"

Route39_Text_DerekNoRoom:
	.string "הממ, התיק שלך מלא.\p"
	.string "תחזור כשיהיה לך מקום.$"
