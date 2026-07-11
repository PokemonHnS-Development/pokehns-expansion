SinjohRuins_hns_MapScripts::
    map_script 	MAP_SCRIPT_ON_TRANSITION, SinjohRuins_hns_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, SinjohRuins_hns_OnLoad
	.byte 0

SinjohRuins_hns_OnTransition::
    setflag FLAG_SINJOHRUINS_STEVENSTONE
	setflag FLAG_SINJOHRUINS_STEVENSTONE2
	setvar VAR_SINJOHRUINS_ARCEUS_STAIRS, 0
	end

SinjohRuins_hns_OnLoad::
    call_if_set FLAG_SINJOHRUINS_ARCEUS_STAIRS, SinjohRuins_Arceus_Stairs
    end


SinjohRuins_EventScripts_StevenStone_WalksYou_Top::
    lock
    delay 8
	opendoor 11, 58
	waitdooranim
	delay 10
	addobject LOCALID_SINJOH_STEVENSTONE
	applymovement LOCALID_SINJOH_STEVENSTONE, SinjohRuins_StevenStone_Movement_ExitHouse
	waitmovement 0
	closedoor 11, 58
	waitdooranim
	delay 10
	playse SE_PIN
	applymovement LOCALID_SINJOH_STEVENSTONE, Common_Movement_ExclamationMark
	waitmovement
	delay 10
	playbgm MUS_ENCOUNTER_CHAMPION, FALSE
	applymovement LOCALID_SINJOH_STEVENSTONE, SinjohRuins_StevenStone_Movement_WalksToPlayerTop
	waitmovement
	delay 8
	msgbox SinjohRuins_Text_StevenSaysHello MSGBOX_DEFAULT
	closemessage
	playse SE_PIN
	applymovement LOCALID_SINJOH_STEVENSTONE, Common_Movement_ExclamationMark
	waitmovement
	delay 8
	applymovement LOCALID_HOUSE1_STEVENSTONE, SinjohRuins_Movement_StevenWaddles
	waitmovement
	msgbox SinjohRuins_Text_StevenContinues MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SINJOH_STEVENSTONE, SinjohRuins_StevenStone_Player_ToBase_Top
	applymovement LOCALID_PLAYER, SinjohRuins_Player_Movement_Follows_StevenStone_Top
	waitmovement 0
	waitmovement 0
	opendoor 4, 55
	waitdooranim
	delay 10
	applymovement LOCALID_SINJOH_STEVENSTONE, SinjohRuins_Steven_Movement_WalksInside
	applymovement LOCALID_PLAYER, SinjohRuins_Movement_PlayerWalksInside
	waitmovement 0
	waitmovement 0
	setvar VAR_SINJOHRUINS_STEVENMET, 1
	removeobject LOCALID_SINJOH_STEVENSTONE
	hideplayer
	closedoor 4, 55
	waitdooranim
	delay 10
	fadedefaultbgm
	warp MAP_SINJOH_RUINS_HOUSE1_HNS, WARP_ID_SINJOH_LAB
	waitstate
	releaseall
	end

SinjohRuins_EventScripts_StevenStone_WalksYou_Bottom::
    lock
    delay 8
	opendoor 11, 58
	waitdooranim
	delay 10
	addobject LOCALID_SINJOH_STEVENSTONE
	applymovement LOCALID_SINJOH_STEVENSTONE, SinjohRuins_StevenStone_Movement_ExitHouse
	waitmovement 0
	closedoor 11, 58
	waitdooranim
	delay 10
	playse SE_PIN
	applymovement LOCALID_SINJOH_STEVENSTONE, Common_Movement_ExclamationMark
	waitmovement
	delay 10
	playbgm MUS_ENCOUNTER_CHAMPION, FALSE
	applymovement LOCALID_SINJOH_STEVENSTONE, SinjohRuins_StevenStone_Movement_WalksToPlayerBottom
	waitmovement
	delay 8
	msgbox SinjohRuins_Text_StevenSaysHello MSGBOX_DEFAULT
	closemessage
	playse SE_PIN
	applymovement LOCALID_SINJOH_STEVENSTONE, Common_Movement_ExclamationMark
	waitmovement
	delay 8
	applymovement LOCALID_HOUSE1_STEVENSTONE, SinjohRuins_Movement_StevenWaddles
	waitmovement
	msgbox SinjohRuins_Text_StevenContinues MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SINJOH_STEVENSTONE, SinjohRuins_StevenStone_Player_ToBase_Bottom
	applymovement LOCALID_PLAYER, SinjohRuins_Player_Movement_Follows_StevenStone_Bottom
	waitmovement 0
	waitmovement 0
	opendoor 4, 55
	waitdooranim
	delay 10
	applymovement LOCALID_SINJOH_STEVENSTONE, SinjohRuins_Steven_Movement_WalksInside
	applymovement LOCALID_PLAYER, SinjohRuins_Movement_PlayerWalksInside
	waitmovement 0
	waitmovement 0
	setvar VAR_SINJOHRUINS_STEVENMET, 1
	removeobject LOCALID_SINJOH_STEVENSTONE
	hideplayer
	closedoor 4, 55
	waitdooranim
	delay 20
	fadedefaultbgm
	warp MAP_SINJOH_RUINS_HOUSE1_HNS, WARP_ID_SINJOH_LAB
	waitstate
	releaseall
	end

SinjohRuins_StevenStone_Movement_ExitHouse:
    walk_down
	step_end

SinjohRuins_StevenStone_Movement_WalksToPlayerTop:
    walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	step_end

SinjohRuins_StevenStone_Player_ToBase_Top:
    walk_left
	walk_left
    walk_left
	walk_left
	walk_up
	walk_up
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	walk_up
	step_end

SinjohRuins_Player_Movement_Follows_StevenStone_Top:
    walk_left
	walk_left
    walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	step_end

SinjohRuins_StevenStone_Movement_WalksToPlayerBottom:
    walk_down
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	step_end

SinjohRuins_StevenStone_Player_ToBase_Bottom:
    walk_left
	walk_left
    walk_left
	walk_left
	walk_up
	walk_up
	walk_up
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	walk_up
	step_end

SinjohRuins_Player_Movement_Follows_StevenStone_Bottom:
    walk_left
	walk_left
    walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	walk_up
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	step_end

SinjohRuins_Steven_Movement_WalksInside:
    walk_up
	step_end

SinjohRuins_Movement_PlayerWalksInside:
    walk_up
	walk_up
	step_end

SinjohRuins_Text_StevenSaysHello:
    .string "Your eyes....\n"
	.string "I remember your eyes, you still have\l"
	.string "that same twinkle as when we first met.\p"
	.string "What are you doing all the way out here?$"

SinjohRuins_Movement_StevenWaddles:
    walk_in_place_right
	walk_in_place_right
	step_end

SinjohRuins_Text_StevenContinues:
    .string "That flute you have there!\n"
	.string "You must be here for the same\l"
	.string "reason I am.\p"
	.string "Come with me, there is much to\n"
	.string "discuss, but let's do it\l"
	.string "somewhere a bit warmer.$"

SinjohRuins_EventScript_StevenToArceus_Left::
   lock
    addobject LOCALID_STEVENSTONE_2
	applymovement LOCALID_STEVENSTONE_2, SinjohRuins_StevenWalksUpCliff_Movement_Left
	waitmovement 0
	applymovement LOCALID_PLAYER, SinjohRuins_PlayerFaceDown_Movement
	waitmovement 0
	msgbox SinjohRuins_StevenAsksIfReady_Text MSGBOX_DEFAULT
	applymovement LOCALID_PLAYER, SinjohRuins_PlayerWaddles_Movement
	waitmovement 0
	msgbox SinjohRuins_Steven_TellsPlayerToGoAhead_Text MSGBOX_DEFAULT
	closemessage
	playse SE_THUNDER
	delay 40
	setvar VAR_0x8004, 1  @ vertical pan
    setvar VAR_0x8005, 1  @ horizontal pan
    setvar VAR_0x8006, 15  @ num shakes
    setvar VAR_0x8007, 6  @ shake delay
    special ShakeCamera
    waitstate
	fadescreen FADE_TO_WHITE
	call_if_unset FLAG_SINJOHRUINS_ARCEUS_STAIRS, SinjohRuins_Arceus_Stairs
    fadescreen FADE_FROM_WHITE
	delay 30
	playse SE_PIN
	applymovement LOCALID_STEVENSTONE_2, Common_Movement_ExclamationMark
	waitmovement 0
	delay 8
	applymovement LOCALID_STEVENSTONE_2, SinjohRuins_Steven2_RunsUp_Left_Movement
	applymovement LOCALID_PLAYER, SinjohRuins_PlayerFacesNorth_Movement
	waitmovement 8
	waitmovement 8
	msgbox SinjohRuins_StevenSeesStairs_Text MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_STEVENSTONE_2, SinjohRuins_StevenStairs_Left
	applymovement LOCALID_PLAYER, SinjohRuins_PlayerFollowStevenToStairs_Movement_Left
	waitmovement 0
	waitmovement 0
	delay 40
	msgbox SinjohRuins_StevenGoesOnAhead_Text MSGBOX_AUTOCLOSE
	applymovement LOCALID_STEVENSTONE_2, SinjohRuins_StevenGoesUp_Movement
	waitmovement 0
	removeobject LOCALID_STEVENSTONE_2
	setflag FLAG_SINJOHRUINS_ARCEUS_STAIRS
	addvar VAR_PLATECOUNTER, 1
	release
	end

SinjohRuins_EventScript_StevenToArceus_Right::
    lock
    addobject LOCALID_STEVENSTONE_2
	applymovement LOCALID_STEVENSTONE_2, SinjohRuins_StevenWalksUpCliff_Movement_Right
	waitmovement 0
	applymovement LOCALID_PLAYER, SinjohRuins_PlayerFaceDown_Movement
	waitmovement 0
	msgbox SinjohRuins_StevenAsksIfReady_Text MSGBOX_DEFAULT
	applymovement LOCALID_PLAYER, SinjohRuins_PlayerWaddles_Movement
	waitmovement 0
	msgbox SinjohRuins_Steven_TellsPlayerToGoAhead_Text MSGBOX_DEFAULT
	closemessage
	playse SE_THUNDER
	delay 40
	setvar VAR_0x8004, 1  @ vertical pan
    setvar VAR_0x8005, 1  @ horizontal pan
    setvar VAR_0x8006, 15  @ num shakes
    setvar VAR_0x8007, 6  @ shake delay
    special ShakeCamera
    waitstate
	fadescreen FADE_TO_WHITE
	call_if_unset FLAG_SINJOHRUINS_ARCEUS_STAIRS, SinjohRuins_Arceus_Stairs
    fadescreen FADE_FROM_WHITE
	delay 30
	playse SE_PIN
	applymovement LOCALID_STEVENSTONE_2, Common_Movement_ExclamationMark
	waitmovement 0
	delay 8
	applymovement LOCALID_STEVENSTONE_2, SinjohRuins_Steven2_RunsUp_Right_Movement
	applymovement LOCALID_PLAYER, SinjohRuins_PlayerFacesNorth_Movement
	waitmovement 8
	waitmovement 8
	msgbox SinjohRuins_StevenSeesStairs_Text MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_STEVENSTONE_2, SinjohRuins_StevenStairs_Right
	applymovement LOCALID_PLAYER, SinjohRuins_PlayerFollowStevenToStairs_Movement_Right
	waitmovement 0
	waitmovement 0
	delay 40
	msgbox SinjohRuins_StevenGoesOnAhead_Text MSGBOX_AUTOCLOSE
	applymovement LOCALID_STEVENSTONE_2, SinjohRuins_StevenGoesUp_Movement
	waitmovement 0
	removeobject LOCALID_STEVENSTONE_2
	setflag FLAG_SINJOHRUINS_ARCEUS_STAIRS
	addvar VAR_PLATECOUNTER, 1
	release
	end

SinjohRuins_StevenWalksUpCliff_Movement_Left:
    walk_right
	walk_right
	walk_right
	walk_right
	walk_right
    walk_right
	walk_diag_northeast
    walk_diag_northeast
	walk_right
    face_up
	step_end


SinjohRuins_StevenWalksUpCliff_Movement_Right:
    walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_diag_northeast
    walk_diag_northeast
	walk_right
	walk_right
	walk_right
    face_up
	step_end

SinjohRuins_PlayerFaceDown_Movement:
    face_down
	step_end

SinjohRuins_PlayerFacesNorth_Movement:
    face_left
	delay_8
	face_up
	step_end


SinjohRuins_PlayerWaddles_Movement:
    walk_in_place_down
	step_end

SinjohRuins_Steven2_RunsUp_Left_Movement:
    jump_in_place_up
	delay_8
	walk_fast_right
	walk_up
	step_end

SinjohRuins_Steven2_RunsUp_Right_Movement:
    jump_in_place_up
	delay_8
	walk_fast_left
	walk_up
	step_end


SinjohRuins_StevenStairs_Left:
    walk_down
    walk_left
	walk_left
	walk_diag_southwest
	walk_diag_southwest
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	walk_up
    walk_left
	walk_left
	walk_left
	walk_left
	walk_left
    walk_up
	walk_up
    walk_left
	walk_left
	walk_left
	walk_left
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
	walk_up
	walk_diag_southeast
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_up
	walk_right
	walk_right
	walk_right
	walk_up
	delay_8
	face_left
	step_end

SinjohRuins_StevenStairs_Right:
    walk_down
    walk_left
	walk_left
	walk_diag_southwest
	walk_diag_southwest
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	walk_up
    walk_left
	walk_left
	walk_left
	walk_left
    walk_up
	walk_up
    walk_left
	walk_left
	walk_left
	walk_left
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
	walk_up
	walk_diag_southeast
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_up
	walk_right
	walk_right
	walk_right
	walk_up
	delay_8
	face_left
	step_end




SinjohRuins_PlayerFacesSteven_Movement:
    face_down
	step_end

SinjohRuins_StevenAsksIfReady_Text:
    .string "{PLAYER}, now that we've collected\n"
	.string "all of the nessisary plates..\l"
	.string "I belive it's time for us\l"
	.string "to end this shared adventure\l"
	.string "of ours, don't you agree?$"

SinjohRuins_Steven_TellsPlayerToGoAhead_Text:
    .string "Alright then, it's time for the\n"
	.string "fun to begin!\p"
	.string "Give that flute you've been carrying\n"
	.string "a good play for the both of us!$"

SinjohRuins_StevenSeesStairs_Text:
    .string "Did you see that {PLAYER}?!\p"
    .string "What ever is up there must be\n"
	.string "inviting us to join them.$"

SinjohRuins_StevenGoesOnAhead_Text:
	.string "I'll head up first to make sure\n"
	.string "it's safe, you follow when ready.$"

SinjohRuins_EventScript_ApplyStairs::
    call_if_set FLAG_SINJOHRUINS_ARCEUS_STAIRS, SinjohRuins_Arceus_Stairs
	end

SinjohRuins_Arceus_Stairs::
	setmetatile 10, 37, 0x089, FALSE
	setmetatile 10, 38, 0x089, FALSE
	setmetatile 10, 39, 0x089, FALSE
	setmetatile 10, 40, 0x089, FALSE
	setmetatile 10, 41, 0x089, FALSE
	setmetatile 10, 42, 0x089, FALSE
	setmetatile 11, 37, 0x091, FALSE
	setmetatile 11, 38, 0x091, FALSE
	setmetatile 11, 39, 0x091, FALSE
	setmetatile 11, 40, 0x091, FALSE
	setmetatile 11, 41, 0x091, FALSE
	setmetatile 11, 42, 0x091, FALSE
	return

SinjohRuins_PlayerFollowStevenToStairs_Movement_Right:
    walk_left
	walk_down
	walk_left
	walk_diag_southwest
	walk_diag_southwest
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
    walk_up
	walk_left
	walk_left
	walk_left
	walk_left
    walk_up
	walk_up
    walk_left
	walk_left
	walk_left
	walk_left
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
	walk_up
	walk_diag_southeast
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_up
	walk_right
	walk_right
	walk_up
	face_up
	delay_8
	face_right
	step_end

SinjohRuins_PlayerFollowStevenToStairs_Movement_Left:
    delay_16
	delay_16
	walk_down
	walk_left
	walk_diag_southwest
	walk_diag_southwest
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
    walk_up
	walk_left
	walk_left
	walk_left
	walk_left
    walk_left
	walk_up
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
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
	walk_up
	walk_diag_southeast
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_up
	walk_right
	walk_right
	walk_up
	face_up
	delay_8
	face_right
	step_end




SinjohRuins_StevenGoesUp_Movement:
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