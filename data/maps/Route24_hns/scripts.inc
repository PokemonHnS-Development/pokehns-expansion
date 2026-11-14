Route24_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route24_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route24_OnTransition:
	call_if_eq VAR_KANTO_ROCKET_STORY_STATE, 4, Route24_MapScript_SetRocketScene
	callnative SetTimeBasedEncounters
	end

Route24_MapScript_SetRocketScene:
	setobjectxyperm LOCALID_ROUTE24_GRUNT, 16, 8
	setobjectxyperm LOCALID_ROUTE24_WOMAN, 16, 9
	setobjectmovementtype LOCALID_ROUTE24_GRUNT, MOVEMENT_TYPE_FACE_LEFT
	setobjectmovementtype LOCALID_ROUTE24_WOMAN, MOVEMENT_TYPE_FACE_UP
	setobjectmovementtype LOCALID_ROUTE24_MAN, MOVEMENT_TYPE_FACE_DOWN
	return

Route24_EventScript_Woman::
	goto_if_eq VAR_KANTO_ROCKET_STORY_STATE, 4, Route24_EventScript_WomanRocket
	goto_if_eq VAR_KANTO_ROCKET_STORY_STATE, 5, Route24_EventScript_WomanAfterRocket
	msgbox Route24_Text_Woman, MSGBOX_NPC
	end

Route24_EventScript_WomanRocket::
	msgbox Route24_Text_WomanRocket, MSGBOX_NPC
	end

Route24_EventScript_WomanAfterRocket::
	msgbox Route24_Text_WomanAfterRocket, MSGBOX_NPC
	end

Route24_EventScript_Man::
	goto_if_eq VAR_KANTO_ROCKET_STORY_STATE, 4, Route24_EventScript_ManRocket
		goto_if_eq VAR_KANTO_ROCKET_STORY_STATE, 5, Route24_EventScript_ManAfterRocket
	msgbox Route24_Text_Man, MSGBOX_NPC
	end

Route24_EventScript_ManRocket::
	msgbox Route24_Text_ManRocket, MSGBOX_NPC
	end

Route24_EventScript_ManAfterRocket::
	msgbox Route24_Text_ManAfterRocket, MSGBOX_NPC
	end

Route24_Trigger_GruntScene::
	lock
	playse SE_PIN
	applymovement2 LOCALID_ROUTE24_GRUNT Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_ROUTE24_GRUNT
	applymovement2 LOCALID_ROUTE24_GRUNT, Route24_Movement_GruntHide
	delay 10
	applymovement2 LOCALID_ROUTE24_WOMAN, Route24_Movement_WomanMove
	waitmovement 0
	turnobject LOCALID_ROUTE24_MAN, DIR_SOUTH
	setvar VAR_KANTO_ROCKET_STORY_STATE, 4
	call Route24_MapScript_SetRocketScene
	release
	end

Route24_Movement_GruntHide:
	walk_fast_left
	walk_fast_left
	step_end

Route24_Movement_WomanMove:
	lock_facing_direction
	walk_fast_down
	unlock_facing_direction
	face_up
	step_end

Route24_EventScript_Grunt::
	lock
	faceplayer
	msgbox Route24_Text_RocketSeen, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_GRUNT_31_HNS, Route24_Text_RocketBeaten
	msgbox Route24_Text_RocketAfter, MSGBOX_DEFAULT
	closemessage
	playse SE_PIN
	applymovement2 LOCALID_ROUTE24_GRUNT, Common_Movement_QuestionMark
	delay 55
	waitmovement LOCALID_ROUTE24_GRUNT
	msgbox Route24_Text_RocketDisappears, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Route24_Movement_PlayerSlide
	delay 20
	applymovement LOCALID_ROUTE24_GRUNT, Route24_Movement_GruntLeave
	waitmovement LOCALID_ROUTE24_GRUNT
	setflag FLAG_HIDE_CERULEAN_CAPE_ROCKET
	removeobject LOCALID_ROUTE24_GRUNT
	setvar VAR_KANTO_ROCKET_STORY_STATE, 5
	clearflag FLAG_HIDDEN_ITEM_MACHINE_PART
	release
	end

Route24_Movement_PlayerSlide:
	delay_16
	lock_facing_direction
	walk_fast_up
	unlock_facing_direction
	face_down
	step_end

Route24_Movement_GruntLeave:
	walk_fast_right
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end

Route24_Text_RocketSeen:
	.string "היי, ילד! אני להיות חבר\n"
	.string "צוות רוקט, סוג של בחור!\p"
	.string "בא ממדינה אחרת, מאמן מספר\n"
	.string "אחת, אני!\p"
	.string "חשבתי אני, אם לעצור אנרגיה,\n"
	.string "להיות פאניקה גדולה לאנשים פה!\p"
	.string "סוד זה המשימה שלי, אז לספר\n"
	.string "לך אני לא!\p"
	.string "אבל! אם לנצח אתה נגד אני,\n"
	.string "גבר להיות אני ולספר לך סוד שלי.\p"
	.string "היי, ילד! להתחיל קרב אנחנו!$"

Route24_Text_RocketBeaten:
	.string "איייייה! לא, לא, לא, להאמין\n"
	.string "אני לא יכול!\p"
	.string "חזק מאוד להיות אתה! שווה\n"
	.string "לך אני לא!$"

Route24_Text_RocketAfter:
	.string "אוקיי. לספר לך הסוד שלי אני?\p"
	.string "חלק מכונה לגנוב אני, להחביא\n"
	.string "אותו אני במכון של הסרוליאן.\p"
	.string "בתוך מים לשים אותו אני. לחפש\n"
	.string "במים במרכז של המכון אתה.\p"
	.string "אבל לשכוח אותי אתה לא!\p"
	.string "לנצח אותך בטוח\n"
	.string "צוות רוקט.\p"
	.string "לבוא מג'וטו הם, החברים שלי,\n"
	.string "כן. לעשות נקמה הם.$"

Route24_Text_RocketDisappears:
	.string "…\p"
	.string "מה להגיד אתה? צוות רוקט ביי-ביי\n"
	.string "הלך? מפורק הוא, אומר אתה?\p"
	.string "אוי, לא! מה לעשות אני מעכשיו\n"
	.string "והלאה, אני?$"



Route24_Text_Woman:
	.string "נכון שהנוף מקסים?$"
Route24_Text_Man:
	.string "הייתי יכול להישאר כאן כל היום.$"

Route24_Text_WomanRocket:
	.string "אף אחד לא דוחף אותי!$"
Route24_Text_ManRocket:
	.string "אף אחד לא דוחף את החברה שלי!$"

Route24_Text_WomanAfterRocket:
	.string "מה זה היה בכלל?$"
Route24_Text_ManAfterRocket:
	.string "זה היה מישהו מצוות רוקט?$"
