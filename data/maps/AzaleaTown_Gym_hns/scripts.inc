AzaleaTown_Gym_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, AzaleaTown_Gym_OnTransition
	.byte 0

AzaleaTown_Gym_OnTransition::
	setflag FLAG_HIDE_AZALEA_ARIADOS_LEFT
	setflag FLAG_HIDE_AZALEA_ARIADOS_MID
	setflag FLAG_HIDE_AZALEA_ARIADOS_RIGHT
	end

@ 1-8->5,  5-9->1
AzaleaTown_Gym_EventScript_Trigger_1::
	lock
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	clearflag FLAG_HIDE_AZALEA_ARIADOS_LEFT
	addobject LOCALID_AZALEA_ARIADOS_LEFT1
	SetObjectSubpriority OBJ_EVENT_ID_PLAYER, MAP_AZALEA_TOWN_GYM_HNS, 0
	applymovement LOCALID_AZALEA_ARIADOS_LEFT1, AzaleaTown_Gym_Movement_Ariados_Down
	waitmovement 0
	turnobject LOCALID_AZALEA_ARIADOS_LEFT1, DIR_NORTH
	delay 30
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_JumpUp1
	playse SE_LEDGE
	waitmovement 0
	waitmovement 0
	applymovement LOCALID_AZALEA_ARIADOS_LEFT1, AzaleaTown_Gym_Movement_Ariados_Up
	applymovement OBJ_EVENT_ID_PLAYER, AzaleaTown_Gym_Movement_Player_Up
	waitmovement 0
	waitmovement 0
	@turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	applymovement LOCALID_AZALEA_ARIADOS_LEFT1, AzaleaTown_Gym_Movement_Ariados_Right
	applymovement OBJ_EVENT_ID_PLAYER, AzaleaTown_Gym_Movement_Player_Right
	waitmovement 0
	waitmovement 0
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	applymovement LOCALID_AZALEA_ARIADOS_LEFT1, AzaleaTown_Gym_Movement_Ariados_Up
	applymovement OBJ_EVENT_ID_PLAYER, AzaleaTown_Gym_Movement_Player_Up
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_JumpUp1
	waitmovement 0
	applymovement LOCALID_AZALEA_ARIADOS_LEFT1, AzaleaTown_Gym_Movement_Ariados_Down
	waitmovement 0
	setflag FLAG_HIDE_AZALEA_ARIADOS_LEFT
	removeobject LOCALID_AZALEA_ARIADOS_LEFT1
	resetobjectsubpriority OBJ_EVENT_ID_PLAYER, MAP_AZALEA_TOWN_GYM_HNS
	release
	end

AzaleaTown_Gym_EventScript_Trigger_5::
	lock
	turnobject OBJ_EVENT_ID_PLAYER, DIR_SOUTH
	clearflag FLAG_HIDE_AZALEA_ARIADOS_MID
	addobject LOCALID_AZALEA_ARIADOS_MID1
	SetObjectSubpriority OBJ_EVENT_ID_PLAYER, MAP_AZALEA_TOWN_GYM_HNS, 0
	applymovement LOCALID_AZALEA_ARIADOS_MID1, AzaleaTown_Gym_Movement_Ariados_Up
	waitmovement 0
	turnobject LOCALID_AZALEA_ARIADOS_MID1, DIR_SOUTH
	delay 30
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_JumpDown1
	playse SE_LEDGE
	waitmovement 0
	waitmovement 0
	applymovement LOCALID_AZALEA_ARIADOS_MID1, AzaleaTown_Gym_Movement_Ariados_Down
	delay 3
	applymovement OBJ_EVENT_ID_PLAYER, AzaleaTown_Gym_Movement_Player_Down
	waitmovement 0
	waitmovement 0
	@turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	applymovement LOCALID_AZALEA_ARIADOS_MID1, AzaleaTown_Gym_Movement_Ariados_Left
	applymovement OBJ_EVENT_ID_PLAYER, AzaleaTown_Gym_Movement_Player_Left
	waitmovement 0
	waitmovement 0
	turnobject OBJ_EVENT_ID_PLAYER, DIR_SOUTH
	applymovement LOCALID_AZALEA_ARIADOS_MID1, AzaleaTown_Gym_Movement_Ariados_Down
	delay 3
	applymovement OBJ_EVENT_ID_PLAYER, AzaleaTown_Gym_Movement_Player_Down
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_JumpDown1
	playse SE_LEDGE
	waitmovement 0
	applymovement LOCALID_AZALEA_ARIADOS_MID1, AzaleaTown_Gym_Movement_Ariados_Up
	waitmovement 0
	setflag FLAG_HIDE_AZALEA_ARIADOS_MID
	removeobject LOCALID_AZALEA_ARIADOS_MID1
	resetobjectsubpriority OBJ_EVENT_ID_PLAYER, MAP_AZALEA_TOWN_GYM_HNS
	release
	end

@ 2-9->6,  6-10->2
AzaleaTown_Gym_EventScript_Trigger_2::
	lock
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	clearflag FLAG_HIDE_AZALEA_ARIADOS_MID
	addobject LOCALID_AZALEA_ARIADOS_MID1
	SetObjectSubpriority OBJ_EVENT_ID_PLAYER, MAP_AZALEA_TOWN_GYM_HNS, 0
	applymovement LOCALID_AZALEA_ARIADOS_MID1, AzaleaTown_Gym_Movement_Ariados_Down
	waitmovement 0
	turnobject LOCALID_AZALEA_ARIADOS_MID1, DIR_NORTH
	delay 30
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_JumpUp1
	playse SE_LEDGE
	waitmovement 0
	waitmovement 0
	applymovement LOCALID_AZALEA_ARIADOS_MID1, AzaleaTown_Gym_Movement_Ariados_Up
	applymovement OBJ_EVENT_ID_PLAYER, AzaleaTown_Gym_Movement_Player_Up
	waitmovement 0
	waitmovement 0
	@turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	applymovement LOCALID_AZALEA_ARIADOS_MID1, AzaleaTown_Gym_Movement_Ariados_Right
	applymovement OBJ_EVENT_ID_PLAYER, AzaleaTown_Gym_Movement_Player_Right
	waitmovement 0
	waitmovement 0
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	applymovement LOCALID_AZALEA_ARIADOS_MID1, AzaleaTown_Gym_Movement_Ariados_Up
	applymovement OBJ_EVENT_ID_PLAYER, AzaleaTown_Gym_Movement_Player_Up
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_JumpUp1
	playse SE_LEDGE
	waitmovement 0
	applymovement LOCALID_AZALEA_ARIADOS_MID1, AzaleaTown_Gym_Movement_Ariados_Down
	waitmovement 0
	setflag FLAG_HIDE_AZALEA_ARIADOS_MID
	removeobject LOCALID_AZALEA_ARIADOS_MID1
	resetobjectsubpriority OBJ_EVENT_ID_PLAYER, MAP_AZALEA_TOWN_GYM_HNS
	release
	end

AzaleaTown_Gym_EventScript_Trigger_6::
	lock
	turnobject OBJ_EVENT_ID_PLAYER, DIR_SOUTH
	clearflag FLAG_HIDE_AZALEA_ARIADOS_RIGHT
	addobject LOCALID_AZALEA_ARIADOS_RIGHT1
	SetObjectSubpriority OBJ_EVENT_ID_PLAYER, MAP_AZALEA_TOWN_GYM_HNS, 0
	applymovement LOCALID_AZALEA_ARIADOS_RIGHT1, AzaleaTown_Gym_Movement_Ariados_Up
	waitmovement 0
	turnobject LOCALID_AZALEA_ARIADOS_RIGHT1, DIR_SOUTH
	delay 30
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_JumpDown1
	playse SE_LEDGE
	waitmovement 0
	waitmovement 0
	applymovement LOCALID_AZALEA_ARIADOS_RIGHT1, AzaleaTown_Gym_Movement_Ariados_Down
	delay 3
	applymovement OBJ_EVENT_ID_PLAYER, AzaleaTown_Gym_Movement_Player_Down
	waitmovement 0
	waitmovement 0
	@turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	applymovement LOCALID_AZALEA_ARIADOS_RIGHT1, AzaleaTown_Gym_Movement_Ariados_Left
	applymovement OBJ_EVENT_ID_PLAYER, AzaleaTown_Gym_Movement_Player_Left
	waitmovement 0
	waitmovement 0
	turnobject OBJ_EVENT_ID_PLAYER, DIR_SOUTH
	applymovement LOCALID_AZALEA_ARIADOS_RIGHT1, AzaleaTown_Gym_Movement_Ariados_Down
	delay 3
	applymovement OBJ_EVENT_ID_PLAYER, AzaleaTown_Gym_Movement_Player_Down
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_JumpDown1
	playse SE_LEDGE
	waitmovement 0
	applymovement LOCALID_AZALEA_ARIADOS_RIGHT1, AzaleaTown_Gym_Movement_Ariados_Up
	waitmovement 0
	setflag FLAG_HIDE_AZALEA_ARIADOS_RIGHT
	removeobject LOCALID_AZALEA_ARIADOS_RIGHT1
	resetobjectsubpriority OBJ_EVENT_ID_PLAYER, MAP_AZALEA_TOWN_GYM_HNS
	release
	end

@ 3-10->4,  4-8->3
AzaleaTown_Gym_EventScript_Trigger_3::
	lock
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	clearflag FLAG_HIDE_AZALEA_ARIADOS_RIGHT
	addobject LOCALID_AZALEA_ARIADOS_RIGHT1
	SetObjectSubpriority OBJ_EVENT_ID_PLAYER, MAP_AZALEA_TOWN_GYM_HNS, 0
	applymovement LOCALID_AZALEA_ARIADOS_RIGHT1, AzaleaTown_Gym_Movement_Ariados_Down
	waitmovement 0
	turnobject LOCALID_AZALEA_ARIADOS_RIGHT1, DIR_NORTH
	delay 30
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_JumpUp1
	playse SE_LEDGE
	waitmovement 0
	waitmovement 0
	applymovement LOCALID_AZALEA_ARIADOS_RIGHT1, AzaleaTown_Gym_Movement_Ariados_Up
	applymovement OBJ_EVENT_ID_PLAYER, AzaleaTown_Gym_Movement_Player_Up
	waitmovement 0
	waitmovement 0
	@turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	applymovement LOCALID_AZALEA_ARIADOS_RIGHT1, AzaleaTown_Gym_Movement_Ariados_Left
	applymovement OBJ_EVENT_ID_PLAYER, AzaleaTown_Gym_Movement_Player_Left
	waitmovement 0
	waitmovement 0
	applymovement LOCALID_AZALEA_ARIADOS_RIGHT1, AzaleaTown_Gym_Movement_Ariados_Left
	applymovement OBJ_EVENT_ID_PLAYER, AzaleaTown_Gym_Movement_Player_Left
	waitmovement 0
	waitmovement 0
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	applymovement LOCALID_AZALEA_ARIADOS_RIGHT1, AzaleaTown_Gym_Movement_Ariados_Up
	applymovement OBJ_EVENT_ID_PLAYER, AzaleaTown_Gym_Movement_Player_Up
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_JumpUp1
	playse SE_LEDGE
	waitmovement 0
	applymovement LOCALID_AZALEA_ARIADOS_RIGHT1, AzaleaTown_Gym_Movement_Ariados_Down
	waitmovement 0
	setflag FLAG_HIDE_AZALEA_ARIADOS_RIGHT
	removeobject LOCALID_AZALEA_ARIADOS_RIGHT1
	resetobjectsubpriority OBJ_EVENT_ID_PLAYER, MAP_AZALEA_TOWN_GYM_HNS
	release
	end

AzaleaTown_Gym_EventScript_Trigger_4::
	lock
	turnobject OBJ_EVENT_ID_PLAYER, DIR_SOUTH
	clearflag FLAG_HIDE_AZALEA_ARIADOS_LEFT
	addobject LOCALID_AZALEA_ARIADOS_LEFT1
	SetObjectSubpriority OBJ_EVENT_ID_PLAYER, MAP_AZALEA_TOWN_GYM_HNS, 0
	applymovement LOCALID_AZALEA_ARIADOS_LEFT1, AzaleaTown_Gym_Movement_Ariados_Up
	waitmovement 0
	turnobject LOCALID_AZALEA_ARIADOS_LEFT1, DIR_SOUTH
	delay 30
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_JumpDown1
	playse SE_LEDGE
	waitmovement 0
	waitmovement 0
	applymovement LOCALID_AZALEA_ARIADOS_LEFT1, AzaleaTown_Gym_Movement_Ariados_Down
	delay 3
	applymovement OBJ_EVENT_ID_PLAYER, AzaleaTown_Gym_Movement_Player_Down
	waitmovement 0
	waitmovement 0
	@turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	applymovement LOCALID_AZALEA_ARIADOS_LEFT1, AzaleaTown_Gym_Movement_Ariados_Right
	applymovement OBJ_EVENT_ID_PLAYER, AzaleaTown_Gym_Movement_Player_Right
	waitmovement 0
	waitmovement 0
	applymovement LOCALID_AZALEA_ARIADOS_LEFT1, AzaleaTown_Gym_Movement_Ariados_Right
	applymovement OBJ_EVENT_ID_PLAYER, AzaleaTown_Gym_Movement_Player_Right
	waitmovement 0
	waitmovement 0
	turnobject OBJ_EVENT_ID_PLAYER, DIR_SOUTH
	applymovement LOCALID_AZALEA_ARIADOS_LEFT1, AzaleaTown_Gym_Movement_Ariados_Down
	delay 3
	applymovement OBJ_EVENT_ID_PLAYER, AzaleaTown_Gym_Movement_Player_Down
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_JumpDown1
	playse SE_LEDGE
	waitmovement 0
	applymovement LOCALID_AZALEA_ARIADOS_LEFT1, AzaleaTown_Gym_Movement_Ariados_Up
	waitmovement 0
	setflag FLAG_HIDE_AZALEA_ARIADOS_LEFT
	removeobject LOCALID_AZALEA_ARIADOS_LEFT1
	resetobjectsubpriority OBJ_EVENT_ID_PLAYER, MAP_AZALEA_TOWN_GYM_HNS
	release
	end

@ 7-11->10,  10-11->7
AzaleaTown_Gym_EventScript_Trigger_7::
	lock
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	clearflag FLAG_HIDE_AZALEA_ARIADOS_LEFT
	addobject LOCALID_AZALEA_ARIADOS_LEFT2
	SetObjectSubpriority OBJ_EVENT_ID_PLAYER, MAP_AZALEA_TOWN_GYM_HNS, 0
	applymovement LOCALID_AZALEA_ARIADOS_LEFT2, AzaleaTown_Gym_Movement_Ariados_Down
	waitmovement 0
	turnobject LOCALID_AZALEA_ARIADOS_LEFT2, DIR_NORTH
	delay 30
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_JumpUp1
	playse SE_LEDGE
	waitmovement 0
	waitmovement 0
	applymovement LOCALID_AZALEA_ARIADOS_LEFT2, AzaleaTown_Gym_Movement_Ariados_Up
	applymovement OBJ_EVENT_ID_PLAYER, AzaleaTown_Gym_Movement_Player_Up
	waitmovement 0
	waitmovement 0
	applymovement LOCALID_AZALEA_ARIADOS_LEFT2, AzaleaTown_Gym_Movement_Ariados_Up
	applymovement OBJ_EVENT_ID_PLAYER, AzaleaTown_Gym_Movement_Player_Up
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_JumpUp1
	playse SE_LEDGE
	waitmovement 0
	applymovement LOCALID_AZALEA_ARIADOS_LEFT2, AzaleaTown_Gym_Movement_Ariados_Down
	waitmovement 0
	setflag FLAG_HIDE_AZALEA_ARIADOS_LEFT
	removeobject LOCALID_AZALEA_ARIADOS_LEFT2
	resetobjectsubpriority OBJ_EVENT_ID_PLAYER, MAP_AZALEA_TOWN_GYM_HNS
	release
	end

AzaleaTown_Gym_EventScript_Trigger_10::
	lock
	turnobject OBJ_EVENT_ID_PLAYER, DIR_SOUTH
	clearflag FLAG_HIDE_AZALEA_ARIADOS_LEFT
	addobject LOCALID_AZALEA_ARIADOS_LEFT2
	SetObjectSubpriority OBJ_EVENT_ID_PLAYER, MAP_AZALEA_TOWN_GYM_HNS, 0
	applymovement LOCALID_AZALEA_ARIADOS_LEFT2, AzaleaTown_Gym_Movement_Ariados_Up
	waitmovement 0
	turnobject LOCALID_AZALEA_ARIADOS_LEFT2, DIR_SOUTH
	delay 30
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_JumpDown1
	playse SE_LEDGE
	waitmovement 0
	waitmovement 0
	applymovement LOCALID_AZALEA_ARIADOS_LEFT2, AzaleaTown_Gym_Movement_Ariados_Down
	delay 3
	applymovement OBJ_EVENT_ID_PLAYER, AzaleaTown_Gym_Movement_Player_Down
	waitmovement 0
	waitmovement 0
	applymovement LOCALID_AZALEA_ARIADOS_LEFT2, AzaleaTown_Gym_Movement_Ariados_Down
	delay 3
	applymovement OBJ_EVENT_ID_PLAYER, AzaleaTown_Gym_Movement_Player_Down
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_JumpDown1
	playse SE_LEDGE
	waitmovement 0
	applymovement LOCALID_AZALEA_ARIADOS_LEFT2, AzaleaTown_Gym_Movement_Ariados_Up
	waitmovement 0
	setflag FLAG_HIDE_AZALEA_ARIADOS_LEFT
	removeobject LOCALID_AZALEA_ARIADOS_LEFT2
	resetobjectsubpriority OBJ_EVENT_ID_PLAYER, MAP_AZALEA_TOWN_GYM_HNS
	release
	end


@ 8-12->12,  12-13->8
AzaleaTown_Gym_EventScript_Trigger_8::
	lock
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	clearflag FLAG_HIDE_AZALEA_ARIADOS_MID
	addobject LOCALID_AZALEA_ARIADOS_MID2
	SetObjectSubpriority OBJ_EVENT_ID_PLAYER, MAP_AZALEA_TOWN_GYM_HNS, 0
	applymovement LOCALID_AZALEA_ARIADOS_MID2, AzaleaTown_Gym_Movement_Ariados_Down
	waitmovement 0
	turnobject LOCALID_AZALEA_ARIADOS_MID2, DIR_NORTH
	delay 30
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_JumpUp1
	playse SE_LEDGE
	waitmovement 0
	waitmovement 0
	applymovement LOCALID_AZALEA_ARIADOS_MID2, AzaleaTown_Gym_Movement_Ariados_Up
	applymovement OBJ_EVENT_ID_PLAYER, AzaleaTown_Gym_Movement_Player_Up
	waitmovement 0
	waitmovement 0
	@turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	applymovement LOCALID_AZALEA_ARIADOS_MID2, AzaleaTown_Gym_Movement_Ariados_Right
	applymovement OBJ_EVENT_ID_PLAYER, AzaleaTown_Gym_Movement_Player_Right
	waitmovement 0
	waitmovement 0
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	applymovement LOCALID_AZALEA_ARIADOS_MID2, AzaleaTown_Gym_Movement_Ariados_Up
	applymovement OBJ_EVENT_ID_PLAYER, AzaleaTown_Gym_Movement_Player_Up
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_JumpUp1
	playse SE_LEDGE
	waitmovement 0
	applymovement LOCALID_AZALEA_ARIADOS_MID2, AzaleaTown_Gym_Movement_Ariados_Down
	waitmovement 0
	setflag FLAG_HIDE_AZALEA_ARIADOS_MID
	removeobject LOCALID_AZALEA_ARIADOS_MID2
	resetobjectsubpriority OBJ_EVENT_ID_PLAYER, MAP_AZALEA_TOWN_GYM_HNS
	release
	end

AzaleaTown_Gym_EventScript_Trigger_12::
	lock
	turnobject OBJ_EVENT_ID_PLAYER, DIR_SOUTH
	clearflag FLAG_HIDE_AZALEA_ARIADOS_RIGHT
	addobject LOCALID_AZALEA_ARIADOS_RIGHT2
	SetObjectSubpriority OBJ_EVENT_ID_PLAYER, MAP_AZALEA_TOWN_GYM_HNS, 0
	applymovement LOCALID_AZALEA_ARIADOS_RIGHT2, AzaleaTown_Gym_Movement_Ariados_Up
	waitmovement 0
	turnobject LOCALID_AZALEA_ARIADOS_RIGHT2, DIR_SOUTH
	delay 30
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_JumpDown1
	playse SE_LEDGE
	waitmovement 0
	waitmovement 0
	applymovement LOCALID_AZALEA_ARIADOS_RIGHT2, AzaleaTown_Gym_Movement_Ariados_Down
	delay 3
	applymovement OBJ_EVENT_ID_PLAYER, AzaleaTown_Gym_Movement_Player_Down
	waitmovement 0
	waitmovement 0
	@turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	applymovement LOCALID_AZALEA_ARIADOS_RIGHT2, AzaleaTown_Gym_Movement_Ariados_Left
	applymovement OBJ_EVENT_ID_PLAYER, AzaleaTown_Gym_Movement_Player_Left
	waitmovement 0
	waitmovement 0
	turnobject OBJ_EVENT_ID_PLAYER, DIR_SOUTH
	applymovement LOCALID_AZALEA_ARIADOS_RIGHT2, AzaleaTown_Gym_Movement_Ariados_Down
	delay 3
	applymovement OBJ_EVENT_ID_PLAYER, AzaleaTown_Gym_Movement_Player_Down
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_JumpDown1
	playse SE_LEDGE
	waitmovement 0
	applymovement LOCALID_AZALEA_ARIADOS_RIGHT2, AzaleaTown_Gym_Movement_Ariados_Up
	waitmovement 0
	setflag FLAG_HIDE_AZALEA_ARIADOS_RIGHT
	removeobject LOCALID_AZALEA_ARIADOS_RIGHT2
	resetobjectsubpriority OBJ_EVENT_ID_PLAYER, MAP_AZALEA_TOWN_GYM_HNS
	release
	end

@ 9-13->11,  11-12->9
AzaleaTown_Gym_EventScript_Trigger_9::
	lock
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	clearflag FLAG_HIDE_AZALEA_ARIADOS_RIGHT
	addobject LOCALID_AZALEA_ARIADOS_RIGHT2
	SetObjectSubpriority OBJ_EVENT_ID_PLAYER, MAP_AZALEA_TOWN_GYM_HNS, 0
	applymovement LOCALID_AZALEA_ARIADOS_RIGHT2, AzaleaTown_Gym_Movement_Ariados_Down
	waitmovement 0
	turnobject LOCALID_AZALEA_ARIADOS_RIGHT2, DIR_NORTH
	delay 30
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_JumpUp1
	playse SE_LEDGE
	waitmovement 0
	waitmovement 0
	applymovement LOCALID_AZALEA_ARIADOS_RIGHT2, AzaleaTown_Gym_Movement_Ariados_Up
	applymovement OBJ_EVENT_ID_PLAYER, AzaleaTown_Gym_Movement_Player_Up
	waitmovement 0
	waitmovement 0
	@turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	applymovement LOCALID_AZALEA_ARIADOS_RIGHT2, AzaleaTown_Gym_Movement_Ariados_Left
	applymovement OBJ_EVENT_ID_PLAYER, AzaleaTown_Gym_Movement_Player_Left
	waitmovement 0
	waitmovement 0
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	applymovement LOCALID_AZALEA_ARIADOS_RIGHT2, AzaleaTown_Gym_Movement_Ariados_Up
	applymovement OBJ_EVENT_ID_PLAYER, AzaleaTown_Gym_Movement_Player_Up
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_JumpUp1
	playse SE_LEDGE
	waitmovement 0
	applymovement LOCALID_AZALEA_ARIADOS_RIGHT2, AzaleaTown_Gym_Movement_Ariados_Down
	waitmovement 0
	setflag FLAG_HIDE_AZALEA_ARIADOS_RIGHT
	removeobject LOCALID_AZALEA_ARIADOS_RIGHT2
	resetobjectsubpriority OBJ_EVENT_ID_PLAYER, MAP_AZALEA_TOWN_GYM_HNS
	release
	end

AzaleaTown_Gym_EventScript_Trigger_11::
	lock
	turnobject OBJ_EVENT_ID_PLAYER, DIR_SOUTH
	clearflag FLAG_HIDE_AZALEA_ARIADOS_MID
	addobject LOCALID_AZALEA_ARIADOS_MID2
	SetObjectSubpriority OBJ_EVENT_ID_PLAYER, MAP_AZALEA_TOWN_GYM_HNS, 0
	applymovement LOCALID_AZALEA_ARIADOS_MID2, AzaleaTown_Gym_Movement_Ariados_Up
	waitmovement 0
	turnobject LOCALID_AZALEA_ARIADOS_MID2, DIR_SOUTH
	delay 30
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_JumpDown1
	playse SE_LEDGE
	waitmovement 0
	waitmovement 0
	applymovement LOCALID_AZALEA_ARIADOS_MID2, AzaleaTown_Gym_Movement_Ariados_Down
	delay 3
	applymovement OBJ_EVENT_ID_PLAYER, AzaleaTown_Gym_Movement_Player_Down
	waitmovement 0
	waitmovement 0
	@turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	applymovement LOCALID_AZALEA_ARIADOS_MID2, AzaleaTown_Gym_Movement_Ariados_Right
	applymovement OBJ_EVENT_ID_PLAYER, AzaleaTown_Gym_Movement_Player_Right
	waitmovement 0
	waitmovement 0
	turnobject OBJ_EVENT_ID_PLAYER, DIR_SOUTH
	applymovement LOCALID_AZALEA_ARIADOS_MID2, AzaleaTown_Gym_Movement_Ariados_Down
	delay 3
	applymovement OBJ_EVENT_ID_PLAYER, AzaleaTown_Gym_Movement_Player_Down
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_JumpDown1
	playse SE_LEDGE
	waitmovement 0
	applymovement LOCALID_AZALEA_ARIADOS_MID2, AzaleaTown_Gym_Movement_Ariados_Up
	waitmovement 0
	setflag FLAG_HIDE_AZALEA_ARIADOS_MID
	removeobject LOCALID_AZALEA_ARIADOS_MID2
	resetobjectsubpriority OBJ_EVENT_ID_PLAYER, MAP_AZALEA_TOWN_GYM_HNS
	release
	end

AzaleaTown_Gym_EventScript_GymGuy::
	lock
	faceplayer
	goto_if_set FLAG_BADGE02_GET, AzaleaTown_Gym_EventScript_GymGuy2
	msgbox AzaleaTown_Gym_Text_GymGuide, MSGBOX_DEFAULT
	closemessage
	release
	end

AzaleaTown_Gym_EventScript_GymGuy2::
	msgbox AzaleaTown_Gym_Text_GymGuideWin, MSGBOX_DEFAULT
	closemessage
	release
	end

AzaleaTown_Gym_EventScript_Al::
	trainerbattle_single TRAINER_AL_HNS, AzaleaTown_Gym_Text_BugCatcherAlSeen, AzaleaTown_Gym_Text_BugCatcherAlBeaten
	msgbox AzaleaTown_Gym_Text_BugCatcherAlAfter, MSGBOX_AUTOCLOSE
	end

AzaleaTown_Gym_EventScript_Josh::
	trainerbattle_single TRAINER_JOSH_HNS, AzaleaTown_Gym_Text_BugCatcherJoshSeen, AzaleaTown_Gym_Text_BugCatcherJoshBeaten
	msgbox AzaleaTown_Gym_Text_BugCatcherJoshAfter, MSGBOX_AUTOCLOSE
	end

AzaleaTown_Gym_EventScript_Benny::
	trainerbattle_single TRAINER_BENNY_HNS, AzaleaTown_Gym_Text_BugCatcherBennySeen, AzaleaTown_Gym_Text_BugCatcherBennyBeaten
	msgbox AzaleaTown_Gym_Text_BugCatcherBennyAfter, MSGBOX_AUTOCLOSE
	end

AzaleaTown_Gym_EventScript_Amy::
	trainerbattle_double TRAINER_AMY_AND_MAY_HNS, AzaleaTown_Gym_Text_TwinsAmyMay1Seen, AzaleaTown_Gym_Text_TwinsAmyMay1Beaten, Route104_Text_GinaNotEnoughMons
	special GetPlayerBigGuyGirlString
	msgbox AzaleaTown_Gym_Text_TwinsAmyMay1After, MSGBOX_DEFAULT
	release
	end
	
AzaleaTown_Gym_EventScript_May::
	trainerbattle_double TRAINER_AMY_AND_MAY_HNS, AzaleaTown_Gym_Text_TwinsAmyMay2Seen, AzaleaTown_Gym_Text_TwinsAmyMay2Beaten, Route104_Text_GinaNotEnoughMons
	special GetPlayerBigGuyGirlString
	msgbox AzaleaTown_Gym_Text_TwinsAmyMay2After, MSGBOX_DEFAULT
	release
	end

AzaleaTown_Gym_EventScript_Bugsy::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_AZALEA_TOWN_GYM, AzaleaTown_Gym_EventScript_Bugsy_Defeated
	msgbox AzaleaTown_Gym_Text_BugsyIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_BUGSY_1_HNS, AzaleaTown_Gym_Text_BugsyBeaten
	message AzaleaTown_Gym_Text_ReceivedHiveBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox AzaleaTown_Gym_Text_HiveBadgeSpeech, MSGBOX_DEFAULT
	setflag FLAG_BADGE02_GET
	setflag FLAG_DEFEATED_AZALEA_TOWN_GYM
	addvar VAR_NUM_BADGES, 1
	setvar VAR_0x8008, 2
	call Common_EventScript_SetGymTrainers_hns
	giveitem ITEM_TM_U_TURN
	msgbox AzaleaTown_Gym_Text_FuryCutterSpeech, MSGBOX_DEFAULT
	setvar VAR_AZALEA_TOWN_STATE, 5
	closemessage
	setflag FLAG_HIDE_AZALEA_TOWN_FARFETCHD
	setflag FLAG_GET_HEADBUTT
	clearflag FLAG_HIDE_ILEX_FOREST_APPRENTICE
	clearflag FLAG_HIDE_ILEX_FOREST_FARFETCHD_1
	release
	end

AzaleaTown_Gym_EventScript_Bugsy_Defeated::
	msgbox AzaleaTown_Gym_Text_BugsyAdvice, MSGBOX_DEFAULT
	closemessage
	release
	end

AzaleaTown_Gym_Movement_Ariados_Down:
	delay_8
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end

AzaleaTown_Gym_Movement_Ariados_Up:
	delay_8
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

AzaleaTown_Gym_Movement_Ariados_Right:
	lock_facing_direction
	delay_8
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	unlock_facing_direction
	step_end

AzaleaTown_Gym_Movement_Ariados_Left:
	lock_facing_direction
	delay_8
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	unlock_facing_direction
	step_end

AzaleaTown_Gym_Movement_Player_Down:
	lock_anim
	delay_8
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	unlock_anim
	unlock_facing_direction
	step_end

AzaleaTown_Gym_Movement_Player_Up:
	lock_anim
	delay_8
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	unlock_anim
	unlock_facing_direction
	step_end

AzaleaTown_Gym_Movement_Player_Right:
	lock_facing_direction
	lock_anim
	delay_8
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	unlock_anim
	unlock_facing_direction
	step_end

AzaleaTown_Gym_Movement_Player_Left:
	lock_facing_direction
	lock_anim
	delay_8
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	unlock_anim
	unlock_facing_direction
	step_end

AzaleaTown_Gym_EventScript_Statue::
	lock
	goto_if_set FLAG_DEFEATED_AZALEA_TOWN_GYM, AzaleaTown_Gym_EventScript_Statue2
	msgbox AzaleaTown_Gym_Text_GymStatue, MSGBOX_DEFAULT
	closemessage
	release
	end

AzaleaTown_Gym_EventScript_Statue2::
	msgbox AzaleaTown_Gym_Text_GymStatueCertified, MSGBOX_DEFAULT
	closemessage
	release
	end

AzaleaTown_Gym_Text_GymStatue:
	.string "AZALEA POKéMON GYM$"

AzaleaTown_Gym_Text_GymStatueCertified:
	.string "GIMNASIO POKéMON DE AZALEA\p"
	.string "ENTRENADORES DE BUGSY:\n"
	.string "{PLAYER}$"

AzaleaTown_Gym_Text_BugsyIntro:
	.string "¡Soy BUGSY!\p"
	.string "Nunca pierdo cuando se trata\n"
	.string "de POKéMON bicho.\p"
	.string "¡Mi estudio me hará la autoridad\n"
	.string "en POKéMON bicho!\p"
	.string "¡Déjame demostrar todo lo que\n"
	.string "he aprendido en mis estudios!$"

AzaleaTown_Gym_Text_BugsyBeaten:
	.string "¡Vaya, increíble! Eres un\n"
	.string "¡experto en POKéMON!\p"
	.string "Mi investigación aún no\n"
	.string "está completa.\p"
	.string "Bien, ganaste. Toma esta\n"
	.string "MEDALLA.$"

AzaleaTown_Gym_Text_ReceivedHiveBadge:
	.string "{PLAYER} received HIVEBADGE.$"

AzaleaTown_Gym_Text_HiveBadgeSpeech:
	.string "¿Conoces los beneficios de la\n"
	.string "MEDALLA COLMENA?\p"
	.string "Si la tienes, los POKéMON\n"
	.string "hasta el nv. 30 te obedecerán,\l"
	.string "incluso los intercambiados.\p"
	.string "Los POKéMON que sepan CORTE\n"
	.string "podrán usarlo fuera de combate.\p"
	.string "Toma, también quiero que\n"
	.string "tengas esto.$"

AzaleaTown_Gym_Text_FuryCutterSpeech:
	.string "La MT89 contiene IDA Y VUELTA.\p"
	.string "IDA Y VUELTA hace daño y\n"
	.string "permite cambiar tu POKéMON en el\l"
	.string "mismo turno!\p"
	.string "¿No es genial?\n"
	.string "¡Yo lo descubrí!$"

AzaleaTown_Gym_Text_BugsyAdvice:
	.string "Hay POKéMON bicho en lo profundo.\n"
	.string "muchos misterios por explorar.\p"
	.string "Estudia bien a tus favoritos.$"

AzaleaTown_Gym_Text_BugsyRematch:
	.string "¡Vaya, ya eres el CAMPEÓN DE JOHTO!\p"
	.string "¡Tus habilidades son increíbles!\p"
	.string "He estado ocupado con mi estudio.\p"
	.string "Estoy listo para mostrarte mis\n"
	.string "hallazgos.\p"
	.string "¿Quieres otra revancha conmigo?$"

AzaleaTown_Gym_Text_BugsyRematchDefeat:
	.string "Vaya, debes ser un experto entrenador.\n"
	.string "Mi investigación no está completa...$"

AzaleaTown_Gym_Text_BugCatcherBennySeen:
	.string "Los POKéMON bicho evolucionan pronto.\n"
	.string "Así se vuelven fuertes más rápido.$"

AzaleaTown_Gym_Text_BugCatcherBennyBeaten:
	.string "Just evolving isn't enough!$"

AzaleaTown_Gym_Text_BugCatcherBennyAfter:
	.string "Los POKéMON se vuelven más fuertes\n"
	.string "si evolucionan. ¡De verdad!$"

AzaleaTown_Gym_Text_BugCatcherAlSeen:
	.string "¡Los POKéMON bicho son geniales!\n"
	.string "¡Te lo demostraré!$"

AzaleaTown_Gym_Text_BugCatcherAlBeaten:
	.string "You proved how tough you are…$"

AzaleaTown_Gym_Text_BugCatcherAlAfter:
	.string "Son geniales, pero a la mayoría\n"
	.string "de chicas no les gustan los\p"
	.string "POKéMON bicho. No sé por qué…$"

AzaleaTown_Gym_Text_BugCatcherJoshSeen:
	.string "¿Salvaste a todos los SLOWPOKE?\n"
	.string "¡Uff, eres muy fuerte!\p"
	.string "¡Pero mis POKéMON adultos\n"
	.string "también son muy fuertes!$"

AzaleaTown_Gym_Text_BugCatcherJoshBeaten:
	.string "Urrgggh!$"

AzaleaTown_Gym_Text_BugCatcherJoshAfter:
	.string "Supongo que debería enseñarles\n"
	.string "mejores movimientos…$"

AzaleaTown_Gym_Text_TwinsAmyMay1Seen:
	.string "AMY: ¡Hola! ¿Vas a retar\n"
	.string "al LÍDER? ¡No puede ser!$"

AzaleaTown_Gym_Text_TwinsAmyMay1Beaten:
	.string "AMY y MAY: ¡Vaya, qué\n"
	.string "sorpresa!$"

AzaleaTown_Gym_Text_TwinsAmyMay1After:
	.string "AMY: ¡Eres muy fuerte!\p"
	.string "¡Pero BUGSY lo es aún más!\n"
	.string "¡El CUT de su SCYTHER casi\l"
	.string "siempre es un golpe crítico!$"

AzaleaTown_Gym_Text_TwinsAmyMay2Seen:
	.string "MAY: ¿Quieres ver el\n"
	.string "¿LÍDER? ¡Buena suerte!\p"
	.string "¡BUGSY es muy fuerte!\n"
	.string "El CUT de su SCYTHER siempre\l"
	.string "¡parece dar crítico!$"

AzaleaTown_Gym_Text_TwinsAmyMay2Beaten:
	.string "AMY y MAY: ¡Vaya, qué\n"
	.string "sorpresa!$"

AzaleaTown_Gym_Text_TwinsAmyMay2After:
	.string "MAY: ¡Perdieron los bichos!\n"
	.string "Oh, qué lástima.\p"
	.string "¡Pero BUGSY no perderá!\p"
	.string "Su PINECO acaba rápido con\n"
	.string "¡los POKéMON de ROCA!$"

AzaleaTown_Gym_Text_GymGuide:
	.string "¡Hola, retador!\p"
	.string "BUGSY es joven, pero sus conocimientos\n"
	.string "sobre POKéMON bicho son reales.\p"
	.string "Será una batalla difícil\n"
	.string "sin mis consejos.\p"
	.string "Veamos... el POKéMON bolsa de\n"
	.string "BUGSY conoce un movimiento que\l"
	.string "cubre su debilidad al tipo ROCA.\p"
	.string "¡Ah, y no olvides los molestos\n"
	.string "golpes críticos! ¡Buena suerte!$"

AzaleaTown_Gym_Text_GymGuideWin:
	.string "¡Bien hecho! Fue una gran\n"
	.string "choque de jóvenes talentos.\p"
	.string "¡Con gente como tú, el\n"
	.string "futuro de POKéMON es brillante!$"
