BurnedTower_B1F_hns_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE,BurnedTower_B1F_OnFrame
	map_script MAP_SCRIPT_ON_TRANSITION, BurnedTower_B1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

BurnedTower_B1F_OnTransition: 
	callnative SetTimeBasedEncounters
	end

BurnedTower_B1F_OnFrame::
	map_script_2 VAR_ECRUTEAK_CITY_STATE, 3, BurnedTower_B1F_EventScript_ReleaseBeasts
	.2byte 0

BurnedTower_B1F_EventScript_ReleaseBeasts::
	lock
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	delay 60
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	delay 60
	playse SE_PIN
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	delay 60

	playmoncry SPECIES_ENTEI, CRY_MODE_NORMAL
	applymovement LOCALID_BURNEDTOWER_ENTEI, BurnedTower_B1F_Movement_AwakenBeasts
	playse SE_LEDGE
	waitse
	playse SE_LEDGE
	waitse
	playse SE_LEDGE
	waitse
	waitmovement 0

	playmoncry SPECIES_RAIKOU, CRY_MODE_NORMAL
	applymovement LOCALID_BURNEDTOWER_RAIKOU, BurnedTower_B1F_Movement_AwakenBeasts
	playse SE_LEDGE
	waitse
	playse SE_LEDGE
	waitse
	playse SE_LEDGE
	waitse
	waitmovement 0

	playmoncry SPECIES_SUICUNE, CRY_MODE_NORMAL
	applymovement LOCALID_BURNEDTOWER_SUICUNE, BurnedTower_B1F_Movement_AwakenBeasts
	playse SE_LEDGE
	waitse
	playse SE_LEDGE
	waitse
	playse SE_LEDGE
	waitse
	waitmovement 0

	
	applymovement LOCALID_BURNEDTOWER_ENTEI, BurnedTower_B1F_Movement_EnteiLeave
	playse SE_LEDGE
	delay 30
	playse SE_LEDGE
	delay 30
	playse SE_LEDGE
	delay 30
	playse SE_LEDGE
	delay 30
	playse SE_LEDGE
	delay 30
	waitmovement 0

	applymovement LOCALID_BURNEDTOWER_RAIKOU, BurnedTower_B1F_Movement_RaikouLeave
	playse SE_LEDGE
	delay 30
	playse SE_LEDGE
	delay 30
	playse SE_LEDGE
	delay 30
	playse SE_LEDGE
	delay 30
	playse SE_LEDGE
	delay 30
	waitmovement 0

	applymovement LOCALID_BURNEDTOWER_SUICUNE, BurnedTower_B1F_Movement_SuicuneLeave
	delay 30
	playse SE_LEDGE
	delay 30
	playmoncry SPECIES_SUICUNE, CRY_MODE_NORMAL
	waitse
	playse SE_LEDGE
	delay 30
	playse SE_LEDGE
	delay 30
	playse SE_LEDGE
	delay 30
	playse SE_LEDGE
	delay 30
	playse SE_LEDGE
	waitmovement 0
	
	setflag FLAG_HIDE_BURNED_TOWER_BEASTS
	removeobject LOCALID_BURNEDTOWER_ENTEI
	removeobject LOCALID_BURNEDTOWER_RAIKOU
	removeobject LOCALID_BURNEDTOWER_SUICUNE
	delay 55

	playse SE_EXIT
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	applymovement LOCALID_BURNEDTOWER2_EUSINE, BurnedTower_B1F_Movement_EusineEnter
	waitmovement 0
	msgbox BurnedTowerB1FEusineText, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BURNEDTOWER2_EUSINE, BurnedTower_B1F_Movement_EusineLeave
	waitmovement 0
	playse SE_EXIT
	setflag FLAG_HIDE_BURNED_TOWER_B1F_EUSINE
	removeobject LOCALID_BURNEDTOWER2_EUSINE
	setflag FLAG_HIDE_BURNED_TOWER_NPCS
	setflag FLAG_HIDE_ECRUTEAK_CITY_SAGE
	special InitRoamer
	setflag FLAG_RELEASED_BEASTS
	setvar VAR_ECRUTEAK_CITY_STATE, 4
	release
	end

BurnedTower_B1F_Movement_AwakenBeasts:
	jump_in_place_down
	jump_in_place_down
	jump_in_place_down
	step_end

BurnedTower_B1F_Movement_EnteiLeave:
	jump_down
	jump_2_right
	jump_2_right
	jump_2_right
	jump_2_right
	step_end

BurnedTower_B1F_Movement_RaikouLeave:
	jump_down
	jump_2_left
	jump_2_left
	jump_2_left
	jump_2_left
	step_end

BurnedTower_B1F_Movement_SuicuneLeave:
	jump_2_down
	delay_8
	jump_in_place_right_left
	jump_in_place_right_left
	jump_left
	jump_2_down
	jump_2_down
	jump_2_down
	step_end

BurnedTower_B1F_Movement_EusineEnter:
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end

BurnedTower_B1F_Movement_EusineLeave:
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

BurnedTowerB1FEusineText:
	.string "יוסין: אני בהלם!\p"
	.string "סואיקון חלף על פניי כהבזק,\n"
	.string "ממש מול העיניים שלי!\p"
	.string "עשר שנים רדפתי אחרי סואיקון,\n"
	.string "וסוף סוף זכיתי לראות אותו.\p"
	.string "אני ממש מוצף רגשות!\p"
	.string "{PLAYER}, את כל זה אני חייב לך!\p"
	.string "תודה לך!\p"
	.string "שמעתי שהפוקימונים האגדיים של\n"
	.string "אקרוטיק בוחנים בני אדם נבחרים.\p"
	.string "הם עושים זאת בכך שהם\n"
	.string "מניחים להם להתקרב.\p"
	.string "אני הולך לעקוב אחרי סואיקון.\p"
	.string "{PLAYER}, עוד ניפגש!\p"
	.string "להתראות!$"


BurnedTower_B1F_EventScript_Item_Taunt::
	finditem ITEM_TM_TAUNT
	end

BurnedTower_B1F_EventScript_Item_UltraBall::
	finditem ITEM_ULTRA_BALL
	end

