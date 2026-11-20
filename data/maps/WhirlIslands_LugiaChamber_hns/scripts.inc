WhirlIslands_LugiaChamber_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, WhirlIslands_LugiaChamber_OnTransition
	.byte 0

WhirlIslands_LugiaChamber_OnTransition:
	goto_if_eq VAR_COMPLETED_LUGIA, 2, WhirlIslands_LugiaChamber_MapScript_LugiaStory
	goto_if_eq VAR_COMPLETED_LUGIA, 3, WhirlIslands_LugiaChamber_MapScript_LugiaPostStoryGone
	goto_if_eq VAR_COMPLETED_LUGIA, 4, WhirlIslands_LugiaChamber_MapScript_LugiaPostStoryEncounter
	end

WhirlIslands_LugiaChamber_MapScript_LugiaStory::
	clearflag FLAG_HIDE_LUGIA
	end

WhirlIslands_LugiaChamber_MapScript_LugiaPostStoryGone::
	setflag FLAG_HIDE_WHIRL_ISLANDS_KIMONO_GIRLS
	setflag FLAG_HIDE_LUGIA
	end

WhirlIslands_LugiaChamber_MapScript_LugiaPostStoryEncounter::
	setflag FLAG_HIDE_WHIRL_ISLANDS_KIMONO_GIRLS
	clearflag FLAG_HIDE_LUGIA
	setobjectxyperm LOCALID_LUGIA, 29, 12
	end

WhirlIslands_LugiaChamber_EventScript_TalkToKimono::
	lockall
	playbgm MUS_HG_KIMONO_GIRL_DANCE, FALSE
	msgbox WhirlIslands_LugiaChamber_Text_Kimono_Opening, MSGBOX_DEFAULT
	closemessage

	applymovement LOCALID_KIMONO_MID, WhirlIslands_LugiaChamber_Movement_Kimono_Step_Aside
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, WhirlIslands_LugiaChamber_Walk_To_Center
	waitmovement 0
	applymovement LOCALID_KIMONO_MID, WhirlIslands_LugiaChamber_Movement_Kimono_Step_In
	applymovement LOCALID_KIMONO_1, WhirlIslands_LugiaChamber_Movement_Kimono_Step_Start_Left
	applymovement LOCALID_KIMONO_4, WhirlIslands_LugiaChamber_Movement_Kimono_Step_Start_Right
	waitmovement 5
	playse SE_M_PETAL_DANCE
	applymovement LOCALID_KIMONO_MID, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Mid
	waitmovement 0
	playse SE_M_PETAL_DANCE
	applymovement LOCALID_KIMONO_1, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Mid
	applymovement LOCALID_KIMONO_2, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Mid
	applymovement LOCALID_KIMONO_3, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Mid
	applymovement LOCALID_KIMONO_4, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Mid
	applymovement LOCALID_KIMONO_MID, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Mid	
	waitmovement 0
	playse SE_M_PETAL_DANCE
	setweather WEATHER_FOG_HORIZONTAL
	doweather
	@ 1
	applymovement LOCALID_KIMONO_1, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Shift_Down
	applymovement LOCALID_KIMONO_2, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Shift_Right
	applymovement LOCALID_KIMONO_3, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Shift_Up
	applymovement LOCALID_KIMONO_4, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Shift_Left
	waitmovement LOCALID_KIMONO_4
	delay 30
	applymovement LOCALID_KIMONO_1, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Mid
	applymovement LOCALID_KIMONO_2, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Mid
	applymovement LOCALID_KIMONO_3, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Mid
	applymovement LOCALID_KIMONO_4, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Mid
	applymovement LOCALID_KIMONO_MID, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Mid
	waitmovement 0
	playse SE_M_PETAL_DANCE
	@ 2
	applymovement LOCALID_KIMONO_1, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Shift_Down
	applymovement LOCALID_KIMONO_2, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Shift_Far_Right
	applymovement LOCALID_KIMONO_3, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Shift_Up
	applymovement LOCALID_KIMONO_4, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Shift_Far_Left
	waitmovement LOCALID_KIMONO_4
	delay 30
	applymovement LOCALID_KIMONO_1, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Mid
	applymovement LOCALID_KIMONO_2, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Mid
	applymovement LOCALID_KIMONO_3, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Mid
	applymovement LOCALID_KIMONO_4, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Mid
	applymovement LOCALID_KIMONO_MID, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Mid
	waitmovement 0
	playse SE_M_PETAL_DANCE
	@ 3
	applymovement LOCALID_KIMONO_1, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Shift_Right
	applymovement LOCALID_KIMONO_2, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Shift_Up
	applymovement LOCALID_KIMONO_3, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Shift_Left
	applymovement LOCALID_KIMONO_4, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Shift_Down
	waitmovement LOCALID_KIMONO_3
	delay 30
	applymovement LOCALID_KIMONO_1, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Mid
	applymovement LOCALID_KIMONO_2, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Mid
	applymovement LOCALID_KIMONO_3, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Mid
	applymovement LOCALID_KIMONO_4, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Mid
	applymovement LOCALID_KIMONO_MID, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Mid
	waitmovement 0
	playse SE_M_PETAL_DANCE
	@ 4
	applymovement LOCALID_KIMONO_1, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Shift_Far_Right
	applymovement LOCALID_KIMONO_2, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Shift_Up
	applymovement LOCALID_KIMONO_3, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Shift_Far_Left
	applymovement LOCALID_KIMONO_4, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Shift_Down
	waitmovement LOCALID_KIMONO_3
	delay 30
	applymovement LOCALID_KIMONO_1, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Mid
	applymovement LOCALID_KIMONO_2, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Mid
	applymovement LOCALID_KIMONO_3, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Mid
	applymovement LOCALID_KIMONO_4, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Mid
	applymovement LOCALID_KIMONO_MID, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Mid
	waitmovement 0
	playse SE_M_PETAL_DANCE
	@ 5
	applymovement LOCALID_KIMONO_1, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Shift_Left_Up
	applymovement LOCALID_KIMONO_4, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Shift_Right_Up
	applymovement LOCALID_KIMONO_MID, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Step_Up
	waitmovement LOCALID_KIMONO_1
	delay 30
	applymovement LOCALID_KIMONO_1, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Mid
	applymovement LOCALID_KIMONO_2, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Mid
	applymovement LOCALID_KIMONO_3, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Mid
	applymovement LOCALID_KIMONO_4, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Mid
	applymovement LOCALID_KIMONO_MID, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Mid
	waitmovement 0
	playse SE_M_PETAL_DANCE
	waitse
	setobjectxyperm LOCALID_KIMONO_1, 27, 18
	setobjectxyperm LOCALID_KIMONO_2, 28, 19
	setobjectxyperm LOCALID_KIMONO_MID, 29, 20
	setobjectxyperm LOCALID_KIMONO_4, 30, 19
	setobjectxyperm LOCALID_KIMONO_3, 31, 18
	setobjectmovementtype LOCALID_KIMONO_1, MOVEMENT_TYPE_FACE_UP
	setobjectmovementtype LOCALID_KIMONO_2, MOVEMENT_TYPE_FACE_UP
	setobjectmovementtype LOCALID_KIMONO_3, MOVEMENT_TYPE_FACE_UP
	setobjectmovementtype LOCALID_KIMONO_4, MOVEMENT_TYPE_FACE_UP
	setobjectmovementtype LOCALID_KIMONO_MID, MOVEMENT_TYPE_FACE_UP
	setvar VAR_TEMP_1, 1
	special SpawnCameraObject
	setvar VAR_0x8004, 3  @ num loops
	setvar VAR_0x8005, 35 @ delay
	special LoopWingFlapSE
	applymovement LOCALID_LUGIA, WhirlIslands_LugiaChamber_Movement_LugiaAppear
	applymovement OBJ_EVENT_ID_CAMERA, WhirlIslands_LugiaChamber_Movement_CameraPanUp
	waitmovement 0
	delay 50
	@ setweather WEATHER_NONE
	@ doweather
	waitse
	playmoncry SPECIES_LUGIA, CRY_MODE_ENCOUNTER
	delay 30
	waitmoncry
	delay 60
	setvar VAR_0x8004, 3  @ num loops
	setvar VAR_0x8005, 35 @ delay
	special LoopWingFlapSE
	applymovement LOCALID_LUGIA, WhirlIslands_LugiaChamber_Movement_LugiaApproach
	waitmovement 0
	applymovement OBJ_EVENT_ID_CAMERA, WhirlIslands_LugiaChamber_Movement_CameraPanDown
	waitmovement 0
	special RemoveCameraObject
	applymovement LOCALID_KIMONO_MID, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Look_Up
	applymovement LOCALID_KIMONO_1, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Look_Up
	applymovement LOCALID_KIMONO_2, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Look_Up
	applymovement LOCALID_KIMONO_3, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Look_Up
	applymovement LOCALID_KIMONO_4, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Look_Up
	waitmovement 0
	msgbox WhirlIslands_LugiaChamber_Text_Kimono_Closing1, MSGBOX_DEFAULT
	waitmessage
	setobjectxyperm LOCALID_LUGIA, 29, 12

	
	closemessage
	releaseall
	end

WhirlIslands_LugiaChamber_EventScript_Lugia::
	lockall
	goto_if_eq VAR_COMPLETED_LUGIA, 4, WhirlIslands_LugiaChamber_EventScript_LugiaPostgame
	waitse
	playmoncry SPECIES_LUGIA, CRY_MODE_ENCOUNTER
	delay 30
	waitmoncry
	playbgm MUS_HG_VS_LUGIA, 0
	seteventmon SPECIES_LUGIA, 50
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	setvar VAR_LAST_TALKED, LOCALID_LUGIA
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, WhirlIslands_LugiaChamber_EventScript_RanFromLugia
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, WhirlIslands_LugiaChamber_EventScript_RanFromLugia
	call_if_eq VAR_RESULT, B_OUTCOME_WON, WhirlIslands_LugiaChamber_EventScript_LugiaFlewAway
	call_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, WhirlIslands_LugiaChamber_EventScript_CaughtLugia
	setflag FLAG_HIDE_WHIRL_ISLANDS_KIMONO_GIRLS
	applymovement LOCALID_KIMONO_MID, WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Shift_Right2
	waitmovement 0
	clearflag FLAG_HIDE_ECRUTEAK_CITY_THEATER_KIMONOS
	clearflag FLAG_HIDE_ECRUTEAK_CITY_THEATER_ZUKI
	clearflag FLAG_HIDE_ECRUTEAK_CITY_THEATER_NPCS
	setvar VAR_ECRUTEAK_CITY_THEATER, 8
	setvar VAR_COMPLETED_LUGIA, 3
	releaseall
	end

WhirlIslands_LugiaChamber_EventScript_LugiaPostgame::
	playmoncry SPECIES_LUGIA, CRY_MODE_ENCOUNTER
	delay 30
	waitmoncry
	playbgm MUS_HG_VS_LUGIA, 0
	seteventmon SPECIES_LUGIA, 70
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	setvar VAR_LAST_TALKED, LOCALID_LUGIA
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, WhirlIslands_LugiaChamber_EventScript_RanFromLugia
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, WhirlIslands_LugiaChamber_EventScript_RanFromLugia
	call_if_eq VAR_RESULT, B_OUTCOME_WON, WhirlIslands_LugiaChamber_EventScript_LugiaFlewAway
	call_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, WhirlIslands_LugiaChamber_EventScript_CaughtLugia
	setvar VAR_COMPLETED_LUGIA, 3
	releaseall
	end

WhirlIslands_LugiaChamber_EventScript_LugiaFlewAway::
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_LUGIA
	setweather WEATHER_NONE
	doweather
	setflag FLAG_HIDE_LUGIA
	fadescreenswapbuffers FADE_FROM_BLACK
	bufferspeciesname STR_VAR_1, SPECIES_LUGIA
	msgbox gText_LegendaryFlewAway, MSGBOX_DEFAULT
	return

WhirlIslands_LugiaChamber_EventScript_CaughtLugia::
	setflag FLAG_CAUGHT_LUGIA
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_LUGIA
	setweather WEATHER_NONE
	doweather
	setflag FLAG_HIDE_LUGIA
	fadescreenswapbuffers FADE_FROM_BLACK
	return

WhirlIslands_LugiaChamber_EventScript_RanFromLugia::
	releaseall
	end

WhirlIslands_LugiaChamber_EventScript_Zuki::
	goto_if_eq VAR_COMPLETED_LUGIA, 3, WhirlIslands_LugiaChamber_EventScript_ZukiAfter
	msgbox WhirlIslands_LugiaChamber_Text_Zuki_Before, MSGBOX_NPC
	end
WhirlIslands_LugiaChamber_EventScript_ZukiAfter::
	goto_if_unset FLAG_CAUGHT_LUGIA, WhirlIslands_LugiaChamber_EventScript_ZukiAfterNotCaught
	msgbox WhirlIslands_LugiaChamber_Text_Kimono_AfterCaught, MSGBOX_NPC
	end
WhirlIslands_LugiaChamber_EventScript_ZukiAfterNotCaught::
	msgbox WhirlIslands_LugiaChamber_Text_Kimono_AfterNotCaught, MSGBOX_NPC
	end

WhirlIslands_LugiaChamber_EventScript_Naoko::
	goto_if_eq VAR_COMPLETED_LUGIA, 3, WhirlIslands_LugiaChamber_EventScript_NaokoAfter
	msgbox WhirlIslands_LugiaChamber_Text_Naoko_Before, MSGBOX_NPC
	end
WhirlIslands_LugiaChamber_EventScript_NaokoAfter::
	msgbox WhirlIslands_LugiaChamber_Text_Kimono_After, MSGBOX_NPC
	end

WhirlIslands_LugiaChamber_EventScript_Miki::
	goto_if_eq VAR_COMPLETED_LUGIA, 3, WhirlIslands_LugiaChamber_EventScript_MikiAfter
	msgbox WhirlIslands_LugiaChamber_Text_Miki_Before, MSGBOX_NPC
	end
WhirlIslands_LugiaChamber_EventScript_MikiAfter::
	msgbox WhirlIslands_LugiaChamber_Text_Kimono_After, MSGBOX_NPC
	end

WhirlIslands_LugiaChamber_EventScript_Sayo::
	goto_if_eq VAR_COMPLETED_LUGIA, 3, WhirlIslands_LugiaChamber_EventScript_SayoAfter
	msgbox WhirlIslands_LugiaChamber_Text_Sayo_Before, MSGBOX_NPC
	end
WhirlIslands_LugiaChamber_EventScript_SayoAfter::
	msgbox WhirlIslands_LugiaChamber_Text_Kimono_After, MSGBOX_NPC
	end

WhirlIslands_LugiaChamber_EventScript_Kuni::
	goto_if_eq VAR_COMPLETED_LUGIA, 3, WhirlIslands_LugiaChamber_EventScript_KuniAfter
	msgbox WhirlIslands_LugiaChamber_Text_Kuni_Before, MSGBOX_NPC
	end
WhirlIslands_LugiaChamber_EventScript_KuniAfter::
	msgbox WhirlIslands_LugiaChamber_Text_Kimono_After, MSGBOX_NPC
	end

WhirlIslands_LugiaChamber_Text_Kimono_AfterNotCaught:
	.string "לא רק שגרמת ללוגיה להופיע,\n"
	.string "אלא גם הבסת אותו…\p"
	.string "אין לנו עוד מה לומר.\n"
	.string "שמור על עצמך במסע שלך…$"

WhirlIslands_LugiaChamber_Text_Kimono_AfterCaught:
	.string "לא רק שגרמת ללוגיה להופיע,\n"
	.string "אלא גם תפסת אותו…\p"
	.string "אין לנו עוד מה לומר.\n"
	.string "שמור על עצמך במסע שלך…$"

WhirlIslands_LugiaChamber_Movement_CameraPanUp:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

WhirlIslands_LugiaChamber_Movement_CameraPanDown:
	delay_16
	delay_16
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

WhirlIslands_LugiaChamber_Movement_LugiaApproach:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_in_place_down
	delay_16
	delay_16
	step_end

WhirlIslands_LugiaChamber_Movement_LugiaAppear:
	delay_16
	delay_16
	walk_in_place_down
	walk_in_place_down
	walk_in_place_down
	walk_in_place_down
	step_end


WhirlIslands_LugiaChamber_Movement_Kimono_Step_Aside:
	face_right
	delay_16
	walk_right
	delay_16
	face_left
	step_end

WhirlIslands_LugiaChamber_Walk_To_Center:
	walk_up
	walk_up
	walk_up
	delay_16
	face_down
	step_end

WhirlIslands_LugiaChamber_Movement_Kimono_Step_In:
	walk_left
	delay_16
	face_down
	step_end

WhirlIslands_LugiaChamber_Movement_Kimono_Step_Start_Left:
	face_right
	delay_16
	face_up
	delay_16
	walk_up
	walk_up
	delay_16
	face_left
	delay_16
	walk_left
	delay_16
	face_down
	step_end

WhirlIslands_LugiaChamber_Movement_Kimono_Step_Start_Right:
	face_right
	delay_16
	face_up
	delay_16
	walk_up
	walk_up
	delay_16
	face_right
	delay_16
	walk_right
	delay_16
	face_down
	step_end

WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Mid:
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
	delay_8
	delay_8
	delay_8
	delay_8
	delay_16
	face_down
	delay_8
	face_right
	delay_8
	face_up
	delay_8
	face_left
	delay_8
	face_down
	delay_16
	step_end

WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Shift_Down:
	face_down
	delay_8
	walk_down
	delay_8
	face_down
	delay_16
	step_end

WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Shift_Right:
	face_right
	delay_8
	walk_right
	delay_8
	face_down
	delay_16
	step_end

WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Shift_Up:
	face_right
	delay_8
	face_up
	delay_8
	walk_up
	delay_8
	face_down
	delay_16
	step_end

WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Shift_Left:
	face_right
	delay_8
	face_up
	delay_8
	face_left
	delay_8
	walk_left
	delay_8
	face_down
	delay_16
	step_end

WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Shift_Far_Right:
	face_right
	delay_8
	walk_right
	walk_right
	walk_right
	face_down
	delay_16
	step_end

WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Shift_Far_Left:
	face_right
	delay_8
	face_up
	delay_8
	face_left
	delay_8
	walk_left
	walk_left
	walk_left
	face_down
	delay_16
	step_end

WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Shift_Left_Up:
	face_right
	delay_8
	face_up
	delay_8
	face_left
	delay_8
	walk_left
	delay_8
	face_up
	delay_8
	walk_up
	delay_8
	face_left
	delay_8
	face_down
	delay_16
	step_end

WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Shift_Right_Up:
	face_right
	delay_8
	walk_right
	delay_8
	face_up
	delay_8
	walk_up
	delay_8
	face_right
	delay_8
	face_down
	delay_16
	step_end

WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Look_Up:
	face_right
	delay_8
	face_up
	delay_16
	step_end

WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Step_Up:
	face_right
	delay_8
	face_up
	delay_8
	walk_up
	delay_8
	face_left
	delay_8
	face_down
	delay_16
	step_end

WhirlIslands_LugiaChamber_Movement_Kimono_Dance_Shift_Right2:
	face_right
	delay_8
	walk_right
	delay_8
	face_down
	delay_16
	face_left
	step_end

WhirlIslands_LugiaChamber_Text_Zuki_Before::
	.string "זוקי: לך, התייצב מול לוגיה. $"
WhirlIslands_LugiaChamber_Text_Naoko_Before::
	.string "נאוקו: לך, התייצב מול לוגיה. $"
WhirlIslands_LugiaChamber_Text_Miki_Before::
	.string "מיקי: לך, התייצב מול לוגיה. $"
WhirlIslands_LugiaChamber_Text_Sayo_Before::
	.string "סאיו: לך, התייצב מול לוגיה. $"
WhirlIslands_LugiaChamber_Text_Kuni_Before::
	.string "קוני: לך, התייצב מול לוגיה. $"

WhirlIslands_LugiaChamber_Text_Kimono_Opening::
	.string "נערת קימונו: נכון מאוד.\n"
	.string "כאן אנחנו מקבלות את פני לוגיה.\p"
	.string "כשהריקוד שתרגלנו ימים רבים\n"
	.string "יתאחד עם צליל פעמון הגאות\p"
	.string "שהפקדנו בידיך, אז לוגיה ייצא שוב\n"
	.string "ממעמקי אגן המפל. $"

WhirlIslands_LugiaChamber_Text_Kimono_Closing1::
	.string "זה אכן לוגיה…\n"
	.string "שומר האיים האלה מימי קדם…\p"
	.string "רבים כל כך ניסו שוב ושוב,\n"
	.string "ורק נכשלו…\p"
	.string "{PLAYER}, ליבך, בהרמוניה מלאה עם\n"
	.string "פעמון הגאות, גרם לו סוף סוף להופיע…\p"
	.string "{PLAYER}, אתה לא מבין?\p"
	.string "לוגיה… הוא ודאי חיכה כל הזמן הזה\n"
	.string "למישהו כמוך.\p"
	.string "אתה לא מסכים? $"

WhirlIslands_LugiaChamber_Text_Kimono_After::
	.string "נערת קימונו: הוכחת את עצמך\n"
	.string "היום, {PLAYER}.$"
