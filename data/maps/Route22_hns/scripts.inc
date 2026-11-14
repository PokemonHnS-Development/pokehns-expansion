Route22_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route22_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route22_OnTransition: 
	callnative SetTimeBasedEncounters
	end

Route22_EventScript_Sign::
	msgbox Route22_Text_VictoryRoadEntranceSign, MSGBOX_NPC
	end

Route22_Text_VictoryRoadEntranceSign:
	.string "ליגת הפוקימון\p"
	.string "הכניסה לדרך הניצחון$"

Route22_EventScript_ResetActivation::
	setvar VAR_TEMP_0, 0
	end

Route22_EventScript_DoNothing::
	setvar VAR_TEMP_0, 1
	end

Route22_EventScript_TriggerBottom::
	goto_if_ne VAR_ROUTE22_GIOVANNI_STATE, 0, Route22_EventScript_DoNothing
	specialvar VAR_RESULT, CheckCelebi
	goto_if_eq VAR_RESULT, FALSE, Route22_EventScript_DoNothing
	goto Route22_EventScript_Scene
	
Route22_EventScript_TriggerTop::
	goto_if_ne VAR_ROUTE22_GIOVANNI_STATE, 0, Route22_EventScript_DoNothing
	specialvar VAR_RESULT, CheckCelebi
	goto_if_eq VAR_RESULT, FALSE, Route22_EventScript_DoNothing
	goto Route22_EventScript_Scene

Route22_EventScript_TriggerMid::
	goto_if_ne VAR_ROUTE22_GIOVANNI_STATE, 0, Route22_EventScript_DoNothing
	specialvar VAR_RESULT, CheckCelebi
	goto_if_eq VAR_RESULT, FALSE, Route22_EventScript_DoNothing
	goto Route22_EventScript_Scene

Route22_EventScript_Scene::
	lock
	applymovement2 OBJ_EVENT_ID_FOLLOWER, Route22_Movement_CelebiBegin
	playse SE_LEDGE
	waitse
	playse SE_LEDGE
	waitse
	waitmovement 0
	playse SE_PIN
	applymovement2 OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
	waitmovement OBJ_EVENT_ID_PLAYER
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	playse SE_PIN
	applymovement2 OBJ_EVENT_ID_PLAYER, Common_Movement_QuestionMark
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement2 OBJ_EVENT_ID_FOLLOWER, Route22_Movement_CelebiSpin1
	playse SE_LEDGE
	waitse
	playse SE_LEDGE
	waitse
	playse SE_LEDGE
	waitse
	playse SE_LEDGE
	waitmovement 0
	fadescreenswapbuffers FADE_TO_WHITE
	playse SE_M_TELEPORT
	waitse
	delay 60
	playse SE_M_TELEPORT
	waitse
	clearflag FLAG_HIDE_ROUTE22_GIOVANNI_SILVER
	addobject LOCALID_ROUTE22_GIOVANNI
	addobject LOCALID_ROUTE22_SILVER
	waitse
	playbgm MUS_HG_ROUTE3, FALSE
	fadescreenswapbuffers FADE_FROM_WHITE
	delay 50
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	special SpawnCameraObject
	applymovement2 OBJ_EVENT_ID_CAMERA, Route22_Movement_CameraPanLeft
	waitmovement 0
	delay 30
	applymovement2 LOCALID_ROUTE22_SILVER, Common_Movement_WalkLeft1
	waitmovement 0
	msgbox Route22_Text_Silver1, MSGBOX_DEFAULT
	closemessage
	delay 30
	applymovement2 LOCALID_ROUTE22_GIOVANNI, Route22_Movement_WalkInPlaceRight
	waitmovement 0
	msgbox Route22_Text_Giovanni1, MSGBOX_DEFAULT
	closemessage
	delay 30
	applymovement2 LOCALID_ROUTE22_SILVER, Route22_Movement_WalkInPlaceLeft
	waitmovement 0
	msgbox Route22_Text_Silver2, MSGBOX_DEFAULT
	closemessage
	delay 30
	applymovement2 LOCALID_ROUTE22_GIOVANNI, Route22_Movement_WalkInPlaceRight
	waitmovement 0
	msgbox Route22_Text_Giovanni2, MSGBOX_DEFAULT
	closemessage
	delay 10
	applymovement2 LOCALID_ROUTE22_SILVER, Common_Movement_WalkLeft1
	waitmovement 0
	msgbox Route22_Text_Silver3, MSGBOX_DEFAULT
	closemessage
	delay 30
	applymovement2 LOCALID_ROUTE22_GIOVANNI, Route22_Movement_WalkInPlaceLeft
	waitmovement 0
	msgbox Route22_Text_Giovanni3, MSGBOX_DEFAULT
	closemessage
	delay 30
	applymovement2 LOCALID_ROUTE22_GIOVANNI, Route22_Movement_GiovanniLeave
	waitmovement 0
	msgbox Route22_Text_Silver4, MSGBOX_DEFAULT
	closemessage
	delay 30
	applymovement2 LOCALID_ROUTE22_SILVER, Common_Movement_WalkLeft1
	waitmovement 0
	msgbox Route22_Text_Silver5, MSGBOX_DEFAULT
	closemessage
	delay 20
	playbgm MUS_HG_ENCOUNTER_RIVAL, FALSE
	applymovement2 LOCALID_ROUTE22_SILVER, Route22_Movement_SilverStartLeave
	applymovement2 OBJ_EVENT_ID_CAMERA, Route22_Movement_CameraPanRight
	waitmovement LOCALID_ROUTE22_SILVER
	waitmovement OBJ_EVENT_ID_CAMERA
	special RemoveCameraObject
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	playse SE_PIN
	applymovement2 LOCALID_ROUTE22_SILVER, Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_ROUTE22_SILVER
	msgbox Route22_Text_Silver6, MSGBOX_DEFAULT
	closemessage
	applymovement2 LOCALID_ROUTE22_SILVER, Common_Movement_WalkRight1
	applymovement2 OBJ_EVENT_ID_PLAYER, Route22_Movement_PlayerPushed
	applymovement2 OBJ_EVENT_ID_FOLLOWER, Route22_Movement_CelebiPush
	playse SE_LEDGE
	waitmovement LOCALID_ROUTE22_SILVER
	waitmovement OBJ_EVENT_ID_PLAYER
	waitmovement OBJ_EVENT_ID_FOLLOWER
	waitse
	applymovement2 LOCALID_ROUTE22_SILVER, Route22_Movement_SilverFinishLeave
	waitmovement 0
	setflag FLAG_HIDE_ROUTE22_GIOVANNI_SILVER
	removeobject LOCALID_ROUTE22_SILVER
	removeobject LOCALID_ROUTE22_GIOVANNI

	applymovement2 OBJ_EVENT_ID_FOLLOWER, Route22_Movement_CelebiBegin
	playse SE_LEDGE
	waitse
	playse SE_LEDGE
	waitse
	waitmovement 0
	playse SE_PIN
	applymovement2 OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
	waitmovement OBJ_EVENT_ID_PLAYER
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	delay 20
	playse SE_PIN
	applymovement2 OBJ_EVENT_ID_PLAYER, Common_Movement_QuestionMark
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement2 OBJ_EVENT_ID_FOLLOWER, Route22_Movement_CelebiSpin1
	playse SE_LEDGE
	waitse
	playse SE_LEDGE
	waitse
	@playse SE_M_PETAL_DANCE
	@delay 10
	playse SE_LEDGE
	waitse
	playse SE_LEDGE
	waitmovement 0
	fadescreenswapbuffers FADE_TO_WHITE
	playse SE_M_TELEPORT
	waitse
	delay 60
	playse SE_M_TELEPORT
	waitse
	fadedefaultbgm
	fadescreenswapbuffers FADE_FROM_WHITE
	setvar VAR_ROUTE22_GIOVANNI_STATE, 2
	setvar VAR_TEMP_0, 2
	release
	end



Route22_Movement_PlayerPushed:
	lock_facing_direction
	jump_up
	unlock_facing_direction
	step_end

Route22_EventScript_PlayerFaceSouth::
	turnobject OBJ_EVENT_ID_PLAYER, DIR_SOUTH
	return

Route22_EventScript_PlayerFaceWest::
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	return
	
Route22_EventScript_PlayerFaceNorth::
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	return
	
Route22_EventScript_PlayerFaceEast::
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	return
	
Route22_Movement_CameraPanLeft:
	walk_up
	walk_left
	walk_left
	step_end

Route22_Movement_CameraPanRight:
	walk_down
	walk_right
	walk_right
	step_end

Route22_Movement_WalkInPlaceLeft:
	walk_in_place_left
	step_end

Route22_Movement_WalkInPlaceRight:
	walk_in_place_right
	step_end

Route22_Movement_GiovanniLeave:
	walk_left
	walk_left
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

Route22_Movement_SilverStartLeave:
	walk_fast_down
	jump_2_down
	walk_fast_down
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

Route22_Movement_SilverFinishLeave:
	walk_fast_right
	walk_fast_right
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

Route22_Movement_CelebiBegin:
	jump_in_place_left
	jump_in_place_left
	step_end

Route22_Movement_CelebiSpin1:
	jump_in_place_left
	jump_in_place_left
	jump_in_place_left
	jump_in_place_left
	step_end

Route22_Movement_CelebiPush:
	walk_up
	face_down
	walk_in_place_down
	step_end


Route22_Text_Silver1:
	.string "{RIVAL}: אמרת לי…\n"
	.string "שאתה מספר אחת בכל העולם!\p"
	.string "אתה מתכוון לוותר?\p"
	.string "מה אתה הולך לעשות עכשיו?$"

Route22_Text_Giovanni1:
	.string "…………\p"
	.string "ג'ובאני: אדם חייב להודות\n"
	.string "בתבוסתו לפני שיוכל להמשיך הלאה…\p"
	.string "אמשיך לבד… בינתיים…\p"
	.string "כדי שיום אחד אקים\n"
	.string "ארגון חזק יותר!$"

Route22_Text_Silver2:
	.string "{RIVAL}: במה בדיוק היית\n"
	.string "מספר אחת?\p"
	.string "אספת כל כך הרבה אנשים רק\n"
	.string "כדי להפסיד לסתם ילד!$"

Route22_Text_Giovanni2:
	.string "ג'ובאני: כשמאחדים את הפוטנציאל\n"
	.string "של רבים, יוצרים כוח עצום…\p"
	.string "זו מהותו של ארגון…\n"
	.string "זה כוחו של ארגון.\p"
	.string "נכשלתי… בניצול הפוטנציאל\n"
	.string "של הכפופים לי…!\p"
	.string "אבל יום אחד עוד תראה אותי\n"
	.string "ואת צוות רוקט שלי קמים לתחייה!$"

Route22_Text_Silver3:
	.string "{RIVAL}: אני לא מבין אותך!\p"
	.string "אין שום היגיון במה שאתה אומר!$"

Route22_Text_Giovanni3:
	.string "…………\p"
	.string "ג'ובאני: יום אחד\n"
	.string "אתה תבין.$"

Route22_Text_Silver4:
	.string "{RIVAL}: אני לא רוצה\n"
	.string "להבין אותך!\p"
	.string "לעולם לא אהפוך למישהו\n"
	.string "כמוך.\p"
	.string "פחדן כשאתה לבד, ועריץ\n"
	.string "כשאתה מול פחדנים אחרים!\p"
	.string "אני אהיה חזק!\p"
	.string "אני אהיה גבר חזק יותר,\n"
	.string "בכוחות עצמי!$"

Route22_Text_Silver5:
	.string "בכוחות עצמי!$"

Route22_Text_Silver6:
	.string "{RIVAL}: … מה אתה בוהה בי?$"

