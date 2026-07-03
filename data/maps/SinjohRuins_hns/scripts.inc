SinjohRuins_hns_MapScripts::
    map_script 	MAP_SCRIPT_ON_TRANSITION, SinjohRuins_hns_OnTransition
	.byte 0

SinjohRuins_hns_OnTransition::
    setflag FLAG_SINJOHRUINS_STEVENSTONE
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