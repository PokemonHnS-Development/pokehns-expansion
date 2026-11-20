Route42_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route42_MapScript_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route42_MapScript_OnTransition::
	call_if_set FLAG_HIDE_ROUTE42_SUICUNE, Route42_MapScript_HideTrigger
	callnative SetTimeBasedEncounters
	end

Route42_MapScript_HideTrigger::
	setvar VAR_TEMP_0, 1
	return

Route42_EventScript_Suicune_Trigger::
	lock
	playmoncry SPECIES_SUICUNE, CRY_MODE_NORMAL
	applymovement LOCALID_ROUTE42_SUICUNE, Route42_Movement_Suicune1
	playse SE_LEDGE
	waitse
	playse SE_LEDGE
	waitse
	waitmovement 0
	waitmoncry
	playse SE_PIN
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement LOCALID_ROUTE42_SUICUNE, Route42_Movement_Suicune2
	playse SE_LEDGE
	delay 30
	playse SE_LEDGE
	delay 30
	playse SE_LEDGE
	delay 30
	playse SE_LEDGE
	delay 30
	waitmovement 0

	playmoncry SPECIES_SUICUNE, CRY_MODE_NORMAL
	applymovement LOCALID_ROUTE42_SUICUNE, Route42_Movement_Suicune3
	applymovement OBJ_EVENT_ID_PLAYER, Route42_Movement_Player
	playse SE_LEDGE
	delay 60
	playse SE_LEDGE
	delay 30
	playse SE_LEDGE
	delay 30
	playse SE_LEDGE
	delay 30
	playse SE_LEDGE
	delay 30
	playse SE_LEDGE
	waitmovement LOCALID_ROUTE42_SUICUNE
	waitmovement 0
	delay 60
	removeobject LOCALID_ROUTE42_SUICUNE
	setflag FLAG_HIDE_ROUTE42_SUICUNE
	clearflag FLAG_HIDE_ROUTE42_EUSINE
	addobject LOCALID_ROUTE42_EUSINE
	playse SE_EXIT
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	applymovement LOCALID_ROUTE42_EUSINE, Route42_Movement_Eusine1
	waitmovement 0
	msgbox Route42_Text_EusineAdmireSuicune, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_ROUTE42_EUSINE, DIR_WEST
	msgbox Route42_Text_EusineJealous, MSGBOX_DEFAULT
	turnobject LOCALID_ROUTE42_EUSINE, DIR_EAST
	msgbox Route42_Text_EusineWontGiveUp, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ROUTE42_EUSINE, Route42_Movement_Eusine2
	waitmovement 0
	setflag FLAG_HIDE_ROUTE42_EUSINE
	removeobject LOCALID_ROUTE42_EUSINE
	setvar VAR_TEMP_0, 1
	call_if_eq VAR_SUICUNE_ENCOUNTERS, 2, Route42_EventScript_DoneJohtoSuicune
	release
	end

Route42_EventScript_DoneJohtoSuicune::
	setvar VAR_SUICUNE_ENCOUNTERS, 3
	return

Route42_Movement_Suicune1:
	jump_in_place_right_left
	jump_in_place_right_left
	step_end

Route42_Movement_Suicune2:
	jump_2_left
	jump_2_left
	jump_2_left
	jump_2_up
	step_end

Route42_Movement_Suicune3:
	jump_in_place_up
	delay_2
	face_up
	jump_2_up
	jump_2_right
	jump_2_right
	jump_2_right
	jump_2_right
	jump_2_right
	step_end

Route42_Movement_Player:
	lock_facing_direction
	delay_2
	jump_2_up
	unlock_facing_direction
	step_end

Route42_Movement_Eusine1:
	walk_down
	walk_down
	walk_left
	face_right
	step_end

Route42_Movement_Eusine2:
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

Route42_Text_EusineAdmireSuicune:
	.string "יוסין: סואיקון…\n"
	.string "כמה הוא אמיץ!\p"
	.string "כמה הוא מרענן!\n"
	.string "כמה הוא יפה!\p"
	.string "וכמה מהר הוא נע!$"

Route42_Text_EusineJealous:
	.string "{PLAYER}!\p"
	.string "נראה שאתה מסתובב\n"
	.string "במקומות שבהם סואיקון מופיע.\p"
	.string "טוב, זה בסדר. הרצון שלי לחפש\n"
	.string "את סואיקון גדול בהרבה משלך…\p"
	.string "סבא שלי היה… די שקוע\n"
	.string "במיתוסים.\p"
	.string "שמעתי ממנו כל כך הרבה\n"
	.string "סיפורים על סואיקון.$"

Route42_Text_EusineWontGiveUp:
	.string "סואיקון… לא אפסיק לעקוב אחריך\n"
	.string "עד שאגלה מה אתה מחפש…\p"
	.string "שמעת אותי!$"


Route42_EventScript_Tully::
	trainerbattle_single TRAINER_TULLY_HNS, Route42_Text_FisherTullySeen, Route42_Text_FisherTullyBeaten, Route42_EventScript_RegisterTully
	goto_if_set FLAG_TULLY_HAS_ITEM_HNS, Route42_EventScript_TullyGiveItem
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route42_EventScript_RematchTully
	msgbox Route42_Text_FisherTullyAfter, MSGBOX_AUTOCLOSE
	end

Route42_EventScript_RegisterTully::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route42_Text_TullyRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_TULLY_HNS
	release
	end

Route42_EventScript_RematchTully::
	trainerbattle_rematch TRAINER_TULLY_HNS, Route42_Text_TullyRematchIntro, Route42_Text_TullyRematchDefeat
	msgbox Route42_Text_TullyPostRematch, MSGBOX_AUTOCLOSE
	end

Route42_EventScript_TullyGiveItem::
	msgbox Route42_Text_TullyHasItem, MSGBOX_DEFAULT
	giveitem VAR_TULLY_ITEM_HNS
	goto_if_eq VAR_RESULT, FALSE, Route42_EventScript_TullyNoRoom
	clearflag FLAG_TULLY_HAS_ITEM_HNS
	msgbox Route42_Text_TullyGaveItem, MSGBOX_AUTOCLOSE
	end

Route42_EventScript_TullyNoRoom::
	msgbox Route42_Text_TullyNoRoom, MSGBOX_AUTOCLOSE
	end

Route42_EventScript_Ben::
	trainerbattle_single TRAINER_BENJAMIN_HNS, Route42_Text_HikerBenjaminSeen, Route42_Text_HikerBenjaminBeaten
	msgbox Route42_Text_HikerBenjaminAfter, MSGBOX_AUTOCLOSE
	end

Route42_EventScript_Shane::
	trainerbattle_single TRAINER_SHANE_HNS, Route42_Text_PokemaniacShaneSeen, Route42_Text_PokemaniacShaneBeaten
	msgbox Route42_Text_PokemaniacShaneAfter, MSGBOX_AUTOCLOSE
	end

Route42_EventScript_Sign::
	lock
	msgbox Route42_Text_Sign1, MSGBOX_SIGN
	closemessage
	release
	end

Route42_EventScript_MortarSign::
	lock
	msgbox Route42_Text_MtMortarSign1, MSGBOX_SIGN
	closemessage
	release
	end

Route42_EventScript_Item_SuperPotion::
	finditem ITEM_SUPER_POTION
	end
Route42_EventScript_Item_Shadow_Claw::
    finditem ITEM_TM_SHADOW_CLAW
    end
Route42_EventScript_Item_UltraBall::
	finditem ITEM_ULTRA_BALL
	end

Route42_Text_FisherTullySeen:
	.string "אני אדגים לך את הכוח\n"
	.string "של הפוקימונים שתפסתי!$"

Route42_Text_FisherTullyBeaten:
	.string "מה? זה לא בסדר.\n"
	.string "אני לא מאמין!$"

Route42_Text_FisherTullyAfter:
	.string "אני רוצה להיות אלוף המאמנים\n"
	.string "עם הפוקימונים שתפסתי בעצמי.\p"
	.string "זה הדבר הכי טוב בדיג!$"

Route42_Text_HikerBenjaminSeen:
	.string "אה, כמה טוב להיות בחוץ!\n"
	.string "אני מרגיש כל כך חופשי!$"

Route42_Text_HikerBenjaminBeaten:
	.string "גאהאהא! זה היה קרב\n"
	.string "טוב!$"

Route42_Text_HikerBenjaminAfter:
	.string "הפסד נראה חסר חשיבות\n"
	.string "כשמביטים אל השמיים הגדולים!$"

Route42_Text_PokemaniacShaneSeen:
	.string "היי!\p"
	.string "זה המקום הסודי שלי!\n"
	.string "הסתלק מפה, זר שכמוך!$"

Route42_Text_PokemaniacShaneBeaten:
	.string "הייתי צריך להשתמש\n"
	.string "באבן הירח שלי…$"

Route42_Text_PokemaniacShaneAfter:
	.string "אתה ממלא פוקדקס?\p"
	.string "וואו, אתה בטח מכיר כמה\n"
	.string "פוקימונים די נדירים!\p"
	.string "אפשר בבקשה לראות אותו?\n"
	.string "בבקשה?$"

Route42_Text_Sign1:
	.string "דרך 42\p"
	.string "העיר אקרוטיק - העיירה מהגוני$"

Route42_Text_MtMortarSign1:
	.string "הר המכתש\p"
	.string "בפנים: מערה עם מפל$"

Route42_Text_TullyRegister:
	.string "אני רוצה להיות אלוף המאמנים\n"
	.string "עם הפוקימונים שתפסתי בעצמי.\p"
	.string "זה הדבר הכי טוב בדיג!$"

Route42_Text_TullyRematchIntro:
	.string "אני אדגים לך את הכוח\n"
	.string "של הפוקימונים שתפסתי!$"

Route42_Text_TullyRematchDefeat:
	.string "מה? זה לא בסדר.\n"
	.string "אני לא מאמין!$"

Route42_Text_TullyPostRematch:
	.string "אני רוצה להיות אלוף המאמנים\n"
	.string "עם הפוקימונים שתפסתי בעצמי.\p"
	.string "זה הדבר הכי טוב בדיג!$"

Route42_Text_TullyHasItem:
	.string "היי! מצאתי משהו\n"
	.string "בזמן שדגתי!\p"
	.string "הנה, זה בשבילך!$"

Route42_Text_TullyGaveItem:
	.string "אודיע לך אם אעלה\n"
	.string "בחכה עוד משהו!$"

Route42_Text_TullyNoRoom:
	.string "הממ, התיק שלך מלא.\p"
	.string "תחזור כשיהיה לך מקום.$"
