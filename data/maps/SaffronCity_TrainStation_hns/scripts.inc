SaffronCity_TrainStation_hns_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, SaffronStation_OnFrame
	.byte 0

SaffronStation_OnFrame::
	map_script_2 VAR_TRAIN, 1, SaffronStation_EventScript_ExitTrain
	.2byte 0

SaffronStation_EventScript_Nerd::
	goto_if_set FLAG_RETURNED_MACHINE_PART, SaffronStation_EventScript_Nerd2
	msgbox SaffronMagnetTrainStation_Text_GymGuide, MSGBOX_NPC
	end
SaffronStation_EventScript_Nerd2::
	msgbox SaffronMagnetTrainStation_Text_GymGuide_ReturnedPart, MSGBOX_NPC
	end
SaffronStation_EventScript_Lass::
	msgbox SaffronMagnetTrainStation_Text_Lass, MSGBOX_NPC
	end
SaffronStation_EventScript_Teacher::
	msgbox SaffronMagnetTrainStation_Text_Teacher, MSGBOX_NPC
	end

SaffronStation_EventScript_Attendant::
	lock
	faceplayer
	goto_if_unset FLAG_RETURNED_MACHINE_PART, SaffronStation_EventScript_AttendantTrainNotRunning
	checkitem ITEM_PASS
	goto_if_eq VAR_RESULT, TRUE, SaffronStation_EventScript_BoardTrain
	goto_if_set FLAG_RETURNED_MACHINE_PART, SaffronStation_EventScript_Attendant2
	msgbox SaffronMagnetTrainStation_Text_OfficerNoRailPass, MSGBOX_DEFAULT
	closemessage
	release
	end

SaffronStation_EventScript_AttendantTrainNotRunning::
	msgbox SaffronMagnetTrainStation_Text_Officer_TrainNotOperating, MSGBOX_DEFAULT
	closemessage
	release
	end

SaffronStation_EventScript_Attendant2::
	msgbox SaffronMagnetTrainStation_Text_OfficerNoRailPass, MSGBOX_DEFAULT
	closemessage
	release
	end

SaffronStation_EventScript_BoardTrain::
	msgbox SaffronMagnetTrainStation_Text_OfficerRightThisWay, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SAFFRON_STATION_ATTENDANT, SaffronStation_Movement_Attendant_Move_Up
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, SaffronStation_Movement_WalktoTrain
	waitmovement 0
	special SpawnCameraObject
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkUp1
	waitmovement 0
	playse SE_EXIT
	waitse
	fadescreen FADE_TO_BLACK
	
	applymovement OBJ_EVENT_ID_CAMERA, SaffronStation_Movement_CameraPanUp
	waitmovement 0
	applymovement OBJ_EVENT_ID_CAMERA, SaffronStation_Movement_CameraPanRight
	waitmovement 0
	delay 60

	applymovement LOCALID_SAFFRON_STATION_TRAIN SaffronStation_Movement_SlideLeft
	applymovement OBJ_EVENT_ID_CAMERA, SaffronStation_Movement_SlideLeft
	playbgm MUS_HG_MAGNET_TRAIN, FALSE
	fadescreen FADE_FROM_BLACK
	playse SE_TRUCK_MOVE
	delay 220
	playse SE_TRUCK_STOP
	applymovement LOCALID_SAFFRON_STATION_TRAIN SaffronStation_Movement_SlideLeft
	applymovement OBJ_EVENT_ID_CAMERA, SaffronStation_Movement_SlideLeft
	fadescreen FADE_TO_BLACK
	waitse
	special RemoveCameraObject
	setvar VAR_TRAIN, 1
	delay 60
	warp MAP_GOLDENROD_CITY_TRAIN_STATION_HNS, 19, 16
	waitstate
	delay 60
	end

SaffronStation_EventScript_ExitTrain::
	lock
	applymovement LOCALID_SAFFRON_STATION_ATTENDANT, SaffronStation_Movement_Attendant_Move_Up
	applymovement OBJ_EVENT_ID_PLAYER, SaffronStation_Movement_ExitTrain
	waitmovement 0
	waitmovement 0
	setvar VAR_TRAIN, 0
	applymovement LOCALID_SAFFRON_STATION_ATTENDANT, SaffronStation_Movement_Attendant_Move_Down
	waitmovement 0
	release
	end


SaffronStation_Movement_ExitTrain:
	walk_down
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	step_end

SaffronStation_Movement_Attendant_Move_Up:
	face_up
	walk_up
	walk_left
	face_right
	step_end

SaffronStation_Movement_Attendant_Move_Down:
	walk_right
	walk_down
	step_end

SaffronStation_Movement_WalktoTrain:
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	step_end

SaffronStation_Movement_CameraPanUp:
	slide_up
	slide_up
	slide_up
	slide_up
	slide_up
	slide_up
	slide_up
	slide_up
	slide_up
	slide_up
	slide_up
	step_end

SaffronStation_Movement_CameraPanRight:
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right	
	step_end

SaffronStation_Movement_SlideLeft:
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	step_end

SaffronMagnetTrainStation_Text_OfficerTrainHasntComeIn:
    .string "The train hasn't come in…\p"
    .string "I know! I'll carry the passengers\n"
    .string "on my back!\p"
    .string "That won't work.$"

SaffronMagnetTrainStation_Text_OfficerComingAboard:
    .string "We'll soon depart for GOLDENROD.\p"
    .string "Are you coming aboard?$"

SaffronMagnetTrainStation_Text_OfficerRightThisWay:
    .string "אפשר לראות את כרטיס הרכבת\n"
    .string "שלך, בבקשה?\p"
    .string "בסדר. מכאן, בבקשה.$"

SaffronMagnetTrainStation_Text_OfficerNoRailPass:
    .string "מצטער. אין לך כרטיס רכבת.$"

SaffronMagnetTrainStation_Text_OfficerHopeToSeeYouAgain:
    .string "We hope to see you again!$"

SaffronMagnetTrainStation_Text_OfficerArrivedInSaffron:
    .string "We have arrived in SAFFRON.\p"
    .string "We hope to see you again.$"

@=============================================================================================================================

SaffronMagnetTrainStation_Text_Officer_TrainNotOperating:
	.string "מצטער, אבל הרכבת המגנטית\n"
	.string "לא פועלת כרגע.$"

SaffronMagnetTrainStation_Text_GymGuide:
	.string "הרכבת המגנטית היא רכבת חדישה\n"
	.string "במיוחד, שמשתמשת בחשמל ובמגנטים\p"
	.string "כדי להגיע למהירות מדהימה.\p"
	.string "אבל אם אין חשמל…$"

SaffronMagnetTrainStation_Text_GymGuide_ReturnedPart:
	.string "פיו…\p"
	.string "כמה פעמים כבר נסעתי הלוך ושוב\n"
	.string "בין קאנטו לג'וטו?$"

SaffronMagnetTrainStation_Text_Teacher:
	.string "לפני שבנו את תחנת הרכבת\n"
	.string "המגנטית, עמד כאן בית.\p"
	.string "פעם גרה בו ילדה קטנה\n"
	.string "שקראו לה ”חקיינית”.$"

SaffronMagnetTrainStation_Text_Lass:
	.string "היי. יש לך כרטיס רכבת?\n"
	.string "לי יש.\p"
	.string "כל תושבי סאפרון שנוסעים ברכבת\n"
	.string "המגנטית מחזיקים כרטיס רכבת.$"
