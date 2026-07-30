SinjohRuins_ArceusRoom_hns_MapScripts::
	map_script 	MAP_SCRIPT_ON_TRANSITION, SinjohRuins_ArceusRoom_OnTransition
	.byte 0

SinjohRuins_ArceusRoom_OnTransition::
	call_if_eq VAR_SINJOH_STORYLINE, 11, SinjohRuins_ArceusRoom_MoveArceus
	end
	
SinjohRuins_ArceusRoom_MoveArceus::
	setobjectxyperm LOCALID_SINJOHRUINS_ARCEUSROOM_ARCEUS, 18, 18
	return

SinjohRuins_ArceusRoom_Trigger::
	lock
	playse SE_M_DETECT
	dofieldeffectsparkle 18, 24, 0
	waitfieldeffect FLDEFF_SPARKLE
	playse SE_PIN
    applymovement2 LOCALID_PLAYER, Common_Movement_ExclamationMark
    delay 60
    msgbox SinjohRuins_Lab_Text_PlayFlute, MSGBOX_YESNO
	closemessage
    goto_if_eq VAR_RESULT, FALSE, SinjohRuins_Lab_EventScript_NoOp

	playbgm MUS_DP_AZURE_FLUTE, TRUE
	applymovement2 LOCALID_PLAYER, SinjohRuins_ArceusRoom_Movement_WalkSlowUp
	waitmovement 0
	setvar VAR_RESULT, 3
	playse SE_ORB
	special DoOrbEffect

	delay 200
	applymovement2 LOCALID_PLAYER, SinjohRuins_ArceusRoom_Movement_Dance
	applymovement2 OBJ_EVENT_ID_FOLLOWER, SinjohRuins_ArceusRoom_Movement_Dance
	delay 400
	waitmovement 0
	waitmovement OBJ_EVENT_ID_FOLLOWER
	special FadeOutOrbEffect

	setweather WEATHER_SUNNY
	doweather
    playse SE_THUNDER
	delay 80
	setvar VAR_0x8004, 1  @ vertical pan
    setvar VAR_0x8005, 1  @ horizontal pan
    setvar VAR_0x8006, 15  @ num shakes
    setvar VAR_0x8007, 6  @ shake delay
    special ShakeCamera
    waitstate
	delay 80
	playse SE_THUNDER
	fadescreen FADE_TO_WHITE
	addobject LOCALID_SINJOHRUINS_ARCEUSROOM_ARCEUS

	playse SE_THUNDER
	applymovement2 LOCALID_SINJOHRUINS_ARCEUSROOM_ARCEUS, SinjohRuins_ArceusRoom_Movement_ArceusWalkDown
	fadescreen FADE_FROM_WHITE
    playmoncry SPECIES_ARCEUS, 0
	delay 20
	waitmovement LOCALID_SINJOHRUINS_ARCEUSROOM_ARCEUS
	setvar VAR_0x8004, 0  @ vertical pan
    setvar VAR_0x8005, 1  @ horizontal pan
    setvar VAR_0x8006, 6  @ num shakes
    setvar VAR_0x8007, 2  @ shake delay
    special ShakeCamera
    waitstate
	waitmoncry
	playfanfare MUS_AWAKEN_LEGEND
	delay 8
	playse SE_PIN
	applymovement LOCALID_PLAYER, Common_Movement_ExclamationMark
	waitmovement 0
	setweather WEATHER_NONE
	doweather
	applymovement2 LOCALID_SINJOHRUINS_ARCEUSROOM_ARCEUS, SinjohRuins_ArceusRoom_Movement_ArceusLooksAround
	playmoncry SPECIES_ARCEUS, 0
	waitmovement 0
	playmoncry SPECIES_ARCEUS, 0
	waitmoncry
	fadedefaultbgm
	setobjectxyperm LOCALID_SINJOHRUINS_ARCEUSROOM_ARCEUS, 18, 18
	setvar VAR_SINJOH_STORYLINE, 11
	release
	end

SinjohRuins_ArceusRoom_Movement_ArceusLooksAround:
	walk_in_place_down
	delay_16
	delay_16
	delay_16
	delay_16
	walk_in_place_left
	delay_16
	delay_16
	delay_16
	delay_16
	walk_in_place_right
	delay_16
	delay_16
	delay_16
	delay_16
	walk_in_place_down
	walk_in_place_fast_down
	step_end

SinjohRuins_ArceusRoom_Movement_Dance:
	face_right
	delay_8
	face_up
	delay_8
	face_left
	delay_8
	face_down
	delay_8
	face_right
	delay_8
	face_up
	delay_8
	face_left
	delay_8
	face_down
	delay_8
	face_right
	delay_8
	face_up
	face_left
	delay_8
	face_down
	delay_8
	face_right
	delay_8
	face_up
	delay_8
	face_left
	delay_8
	face_down
	delay_8
	face_right
	delay_8
	face_up
	face_left
	delay_8
	face_down
	delay_8
	face_right
	delay_8
	face_up
	delay_8
	face_left
	delay_8
	face_down
	delay_8
	face_right
	delay_8
	face_up
	face_left
	delay_8
	face_down
	delay_8
	face_right
	delay_8
	face_up
	delay_8
	face_left
	delay_8
	face_down
	delay_8
	face_right
	delay_8
	face_up
	delay_8
	face_left
	delay_8
	face_down
	delay_8
	face_right
	delay_8
	face_up
	delay_8
	face_left
	delay_8
	face_down
	delay_8
	face_right
	delay_8
	face_up
	face_left
	delay_8
	face_down
	delay_8
	face_right
	delay_8
	face_up
	delay_8
	face_left
	delay_8
	face_down
	delay_8
	face_right
	delay_8
	face_up
	face_left
	delay_8
	face_down
	delay_8
	face_right
	delay_8
	face_up
	delay_8
	face_left
	delay_8
	face_down
	delay_8
	face_right
	delay_8
	face_up
	face_left
	delay_8
	face_down
	delay_8
	face_right
	delay_8
	face_up
	delay_8
	face_left
	delay_8
	face_down
	delay_8
	face_right
	delay_8
	face_up
	step_end

SinjohRuins_ArceusRoom_Movement_ArceusWalkDown:
	slide_down
	slide_down
	slide_down
	slide_down
	slide_down
	slide_down
	slide_down
	step_end

SinjohRuins_ArceusRoom_Movement_WalkSlowUp:
	walk_slow_up
	walk_slow_up
	walk_slow_up
	walk_slow_up
	step_end

	
