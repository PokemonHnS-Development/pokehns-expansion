SinjohRuins_hns_MapScripts::
    map_script MAP_SCRIPT_ON_FRAME_TABLE, SinjohRuins_OnFrame
    map_script 	MAP_SCRIPT_ON_TRANSITION, SinjohRuins_hns_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, SinjohRuins_hns_OnLoad
	.byte 0

SinjohRuins_OnFrame::
	map_script_2 VAR_SINJOH_STORYLINE, 8, SinjohRuins_StairsScene
	.2byte 0

SinjohRuins_hns_OnTransition::
    call_if_eq VAR_SINJOH_STORYLINE, 9, SinjohRuins_StevenLanding
    call_if_eq VAR_SINJOH_STORYLINE, 10, SinjohRuins_StevenLanding
    call_if_eq VAR_SINJOH_STORYLINE, 11, SinjohRuins_StevenLanding
    call_if_eq VAR_SINJOH_STORYLINE, 12, SinjohRuins_StevenLanding
    callnative SetTimeBasedEncounters
	end

SinjohRuins_StevenLanding::
    setobjectxyperm LOCALID_SINJOHRUINS_STEVEN, 24, 31
    setobjectmovementtype LOCALID_SINJOHRUINS_STEVEN, MOVEMENT_TYPE_FACE_UP
    return

SinjohRuins_hns_OnLoad::
    call_if_ge VAR_PLATECOUNTER, 3, SinjohRuins_OpenRegirock
    call_if_ge VAR_PLATECOUNTER, 6, SinjohRuins_OpenRegice
    call_if_ge VAR_PLATECOUNTER, 9, SinjohRuins_OpenRegisteel
    call_if_ge VAR_PLATECOUNTER, 12, SinjohRuins_OpenRegieleki
    call_if_ge VAR_PLATECOUNTER, 15, SinjohRuins_OpenRegidrago
    call_if_ge VAR_PLATECOUNTER, 17, SinjohRuins_OpenArceus
    end

SinjohRuins_OpenRegirock::
    setmetatile 9, 44, 0x378, FALSE
    setmetatile 8, 44, 0x0BE, TRUE
    return
SinjohRuins_OpenRegice::
    setmetatile 7, 48, 0x370, FALSE
    setmetatile 6, 48, 0x0BE, TRUE
    return
SinjohRuins_OpenRegisteel::
    setmetatile 8, 54, 0x370, FALSE
    setmetatile 7, 54, 0x0BE, TRUE
    return
SinjohRuins_OpenRegieleki::
    setmetatile 38, 44, 0x371, FALSE
    setmetatile 39, 44, 0x0BD, TRUE
    return
SinjohRuins_OpenRegidrago::
    setmetatile 37, 49, 0x371, FALSE
    setmetatile 38, 49, 0x0BD, TRUE
    return

SinjohRuins_OpenArceus::
    @left stairs
    setmetatile 17, 32, 0x089, FALSE
    setmetatile 17, 33, 0x089, FALSE
    setmetatile 17, 34, 0x089, FALSE
    setmetatile 17, 35, 0x089, FALSE
    setmetatile 17, 36, 0x089, FALSE
    setmetatile 18, 32, 0x091, FALSE
    setmetatile 18, 33, 0x091, FALSE
    setmetatile 18, 34, 0x091, FALSE
    setmetatile 18, 35, 0x091, FALSE
    setmetatile 18, 36, 0x091, FALSE
    setmetatile 19, 32, 0x091, FALSE
    setmetatile 19, 33, 0x091, FALSE
    setmetatile 19, 34, 0x091, FALSE
    setmetatile 19, 35, 0x091, FALSE
    setmetatile 19, 36, 0x091, FALSE
    @right stairs
    setmetatile 29, 32, 0x089, FALSE
    setmetatile 29, 33, 0x089, FALSE
    setmetatile 29, 34, 0x089, FALSE
    setmetatile 29, 35, 0x089, FALSE
    setmetatile 29, 36, 0x089, FALSE
    setmetatile 30, 32, 0x091, FALSE
    setmetatile 30, 33, 0x091, FALSE
    setmetatile 30, 34, 0x091, FALSE
    setmetatile 30, 35, 0x091, FALSE
    setmetatile 30, 36, 0x091, FALSE
    setmetatile 31, 32, 0x091, FALSE
    setmetatile 31, 33, 0x091, FALSE
    setmetatile 31, 34, 0x091, FALSE
    setmetatile 31, 35, 0x091, FALSE
    setmetatile 31, 36, 0x091, FALSE
    return

SinjohRuins_StairsScene::
    lock
    setvar VAR_0x8004, 2  @ vertical pan
	setvar VAR_0x8005, 2  @ horizontal pan
	setvar VAR_0x8006, 40  @ num shakes
	setvar VAR_0x8007, 3  @ shake delay
	special ShakeCamera
    applymovement LOCALID_PLAYER, SinjohRuins_Movement_PlayerWalkRight
    opendoor 14, 52
	waitdooranim
    addobject LOCALID_SINJOHRUINS_STEVEN
    clearflag FLAG_HIDE_SINJOHRUINS_STEVEN
    applymovement LOCALID_SINJOHRUINS_STEVEN, Common_Movement_WalkDown1
    waitmovement LOCALID_SINJOHRUINS_STEVEN
    applymovement LOCALID_SINJOHRUINS_STEVEN, SinjohRuins_Movement_StevenWalkRight
    waitmovement 0
    closedoor 14, 52
	waitdooranim
    setvar VAR_0x8004, 2  @ vertical pan
	setvar VAR_0x8005, 2  @ horizontal pan
	setvar VAR_0x8006, 40  @ num shakes
	setvar VAR_0x8007, 3  @ shake delay
	special ShakeCamera
	waitstate
    waitmovement LOCALID_SINJOHRUINS_STEVEN
    waitmovement 0
    setvar VAR_0x8004, 2  @ vertical pan
	setvar VAR_0x8005, 2  @ horizontal pan
	setvar VAR_0x8006, 40  @ num shakes
	setvar VAR_0x8007, 3  @ shake delay
	special ShakeCamera
	waitstate
    special SpawnCameraObject
    applymovement OBJ_EVENT_ID_CAMERA, SinjohRuins_Movement_CameraPanUp
    waitmovement 0
    setvar VAR_0x8004, 2  @ vertical pan
	setvar VAR_0x8005, 2  @ horizontal pan
	setvar VAR_0x8006, 40  @ num shakes
	setvar VAR_0x8007, 3  @ shake delay
	special ShakeCamera
    setobjectxyperm LOCALID_SINJOHRUINS_STEVEN, 19, 52
    setobjectmovementtype LOCALID_SINJOHRUINS_STEVEN, MOVEMENT_TYPE_FACE_UP
    call SinjohRuins_OpenArceus
    special DrawWholeMapView
    delay 60
    applymovement OBJ_EVENT_ID_CAMERA, SinjohRuins_Movement_CameraPanDown
    waitmovement 0
    special RemoveCameraObject
    msgbox SinjohRuins_Text_StevenGotoStairs1, MSGBOX_AUTOCLOSE
    turnobject LOCALID_SINJOHRUINS_STEVEN, DIR_EAST
    delay 10
    turnobject LOCALID_PLAYER, DIR_WEST
    msgbox SinjohRuins_Text_StevenGotoStairs2, MSGBOX_AUTOCLOSE
    setvar VAR_SINJOH_STORYLINE, 9
    setvar VAR_PLATECOUNTER, 17
    applymovement LOCALID_SINJOHRUINS_STEVEN, SinjohRuins_Movement_StevenGoesToStairs
    waitmovement 0
    removeobject LOCALID_SINJOHRUINS_STEVEN
    setobjectxyperm LOCALID_SINJOHRUINS_STEVEN, 24, 31
    setobjectmovementtype LOCALID_SINJOHRUINS_STEVEN, MOVEMENT_TYPE_FACE_UP
    addobject LOCALID_SINJOHRUINS_STEVEN
    clearflag FLAG_HIDE_SINJOHRUINS_STEVEN
    setflag FLAG_HIDE_SINJOHRUINS_LAB_STEVEN
    setvar VAR_SINJOH_STORYLINE, 9
    release
    end

SinjohRuins_Text_StevenGotoStairs1:
    .string "STEVEN: This could only mean one thing.$"

SinjohRuins_Text_StevenGotoStairs2:
    .string "{PLAYER}. We were able to decipher\n"
    .string "the rest of the glyphs...\p"
    .string "If the translation is right, \n"
    .string "the POKéMON at the top of that\l"
    .string "staircase is the most powerful\l"
    .string "being in the universe.\p"
    .string "And it is my duty as former\n"
    .string "CHAMPION of the HOENN LEAGUE\l"
    .string "to make sure you are strong\l"
    .string "enough to face it.\p"
    .string "Meet me at that landing\n"
    .string "when you are ready.$"

SinjohRuins_Movement_StevenGoesToStairs:
    walk_up
    walk_up
    walk_up
    walk_up
    walk_up
    walk_right
    walk_diag_southeast
    walk_diag_southeast
    walk_up
    walk_up
    walk_up
    walk_up
    walk_up
    walk_up
    step_end

SinjohRuins_Movement_CameraPanDown:
    walk_down
    walk_down
    walk_down
    walk_down
    walk_down
    walk_down
    walk_down
    walk_down
    walk_down
    walk_down
    walk_down
    walk_down
    walk_down
    walk_diag_southwest
    walk_diag_southwest
    walk_diag_southwest
    walk_diag_southwest
    step_end

SinjohRuins_Movement_CameraPanUp:
    walk_diag_northeast
    walk_diag_northeast
    walk_diag_northeast
    walk_diag_northeast
    walk_up
    walk_up
    walk_up
    walk_up
    walk_up
    walk_up
    walk_up
    walk_up
    walk_up
    walk_up
    walk_up
    walk_up
    walk_up
    step_end

SinjohRuins_Movement_StevenWalkRight:
    walk_fast_right
    walk_fast_right
    walk_fast_right
    walk_fast_right
    walk_up
    step_end

SinjohRuins_Movement_PlayerWalkRight:
    walk_fast_right
    walk_fast_right
    walk_fast_right
    walk_fast_right
    walk_fast_right
    walk_fast_right
    walk_up
    step_end
SinjohRuins_EventScript_TriggerStevenBattleRight::
    lock
    turnobject LOCALID_SINJOHRUINS_STEVEN, DIR_EAST
    msgbox SinjohRuins_Text_StevenReadytoBattle, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, FALSE, SinjohRuins_EventScript_TriggerPlayerLeaveRight
    call SinjohRuins_EventScript_StevenBattle
    setvar VAR_SINJOH_STORYLINE, 10
    release
    end
SinjohRuins_EventScript_TriggerPlayerLeaveRight::
    closemessage
    applymovement LOCALID_PLAYER, Common_Movement_WalkRight1
    waitmovement 0
    release
    end
SinjohRuins_EventScript_TriggerStevenBattleLeft::
    lock
    turnobject LOCALID_SINJOHRUINS_STEVEN, DIR_WEST
    msgbox SinjohRuins_Text_StevenReadytoBattle, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, FALSE, SinjohRuins_EventScript_TriggerPlayerLeaveLeft
    call SinjohRuins_EventScript_StevenBattle
    setvar VAR_SINJOH_STORYLINE, 10
    release
    end
SinjohRuins_EventScript_TriggerPlayerLeaveLeft::
    closemessage
    applymovement LOCALID_PLAYER, Common_Movement_WalkLeft1
    waitmovement 0
    release
    end 

SinjohRuins_Movement_StevenLeaveRight:
    walk_left
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
    step_end

SinjohRuins_Movement_StevenLeaveLeft:
    walk_right
    walk_right
    walk_right
    walk_right
    walk_right
    walk_right
    walk_down
    walk_down
    walk_down
    walk_down
    walk_down
    walk_down
    step_end

SinjohRuins_EventScript_StevenBattle::
    msgbox SinjohRuins_Text_ChallengeSteven, MSGBOX_AUTOCLOSE
    trainerbattle_no_intro TRAINER_STEVEN_HNS, SinjohRuins_Text_StevenDefeat
    msgbox SinjohRuins_Text_StevenAfterBattle, MSGBOX_AUTOCLOSE
    giveitem ITEM_STONE_PLATE
    msgbox SinjohRuins_Text_StevenAfterPlate, MSGBOX_AUTOCLOSE
    return

SinjohRuins_Text_StevenAfterPlate:
    .string "STEVEN: Good luck, {PLAYER}\p"
    .string "Go on, I'm right behind you.$"

SinjohRuins_Text_StevenAfterBattle:
	.string "STEVEN: To think, another trainer \n"
	.string "would defeat me like this.\p"
    .string "Incredible.\p"
	.string "Take this, it's the final plate.$"

SinjohRuins_Text_StevenReadytoBattle:
    .string "STEVEN: {PLAYER}.\p"
    .string "Ever since I first saw the\n"
    .string "determination in your eyes,\l"
    .string "I felt it would lead to this.\p"
    .string "I will test the bond between you\n"
    .string "and your POKéMON.\p"
    .string "Are you ready?$"

SinjohRuins_Text_ChallengeSteven:
	.string "Okay, {PLAYER}{KUN}, if you're going to mount\n"
	.string "a serious challenge, expect the worst!$"

SinjohRuins_Text_StevenDefeat:
	.string "You...\n"
	.string "You are ready.$"

SinjohRuins_EventScript_Steven::
    msgbox SinjohRuins_Text_StevenAfterPlate, MSGBOX_NPC
    end

SinjohRuins_EventScript_Sign::
    msgbox SinjohRuins_Text_Sign, MSGBOX_SIGN
    end

SinjohRuins_Text_Sign:
    .string "SINJOH RUINS$"

