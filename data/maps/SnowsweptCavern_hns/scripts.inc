SnowsweptCavern_hns_MapScripts::
    map_script MAP_SCRIPT_ON_TRANSITION, SnowsweptCavern_hns_OnTransition
    .byte 0

SnowsweptCavern_hns_OnTransition::
    goto_if_ge VAR_SINJOH_STORYLINE, 3, SnowsweptCavern_hns_SetBoulderLocation
    end

SnowsweptCavern_hns_SetBoulderLocation::
    setobjectxyperm LOCALID_SNOWSWEPT_CAVERN_BOULDER, 38, 56
    end

Snowswept_Cavern_Eventscript_Machamp::
	lock
	faceplayer
	playmoncry SPECIES_MACHAMP, CRY_MODE_ENCOUNTER
    msgbox Snowswept_Text_Machamp_Cry, MSGBOX_AUTOCLOSE
	waitmoncry
    goto_if_ge VAR_SINJOH_STORYLINE, 3, Snowswept_Cavern_Eventscript_Machamp_AfterBoulder
	setwildbattle SPECIES_MACHAMP, 60
    setflag FLAG_NO_WILD_CATCHING
	setflag FLAG_NO_SHINY
	dowildbattle
    clearflag FLAG_NO_WILD_CATCHING
	clearflag FLAG_NO_SHINY
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, Snowswept_Cavern_Eventscript_Machamp_Ran

    playmoncry SPECIES_MACHAMP, CRY_MODE_ENCOUNTER
	applymovement2 LOCALID_SNOWSWEPT_CAVERN_MACHAMP, Snowswept_Machamp_Movement
    waitmovement 0
    
    setvar VAR_0x8004, 2  @ vertical pan
    setvar VAR_0x8005, 2  @ horizontal pan
    setvar VAR_0x8006, 20  @ num shakes
    setvar VAR_0x8007, 4  @ shake delay
    special ShakeCamera
    waitstate
    applymovement LOCALID_SNOWSWEPT_CAVERN_BOULDER, Snowswept_Cavern_Movement_Boulder
    playse SE_M_STRENGTH
    delay 5
    playse SE_M_STRENGTH
    delay 5
    playse SE_M_STRENGTH
    delay 5
    waitmovement 0
    playse SE_BANG

    setobjectxyperm LOCALID_SNOWSWEPT_CAVERN_BOULDER, 38, 56
    setvar VAR_SINJOH_STORYLINE, 3
	release
	end

Snowswept_Cavern_Eventscript_Machamp_Ran::
    turnobject LOCALID_SNOWSWEPT_CAVERN_MACHAMP, DIR_SOUTH
	release
	end

Snowswept_Cavern_Eventscript_Machamp_AfterBoulder::
    turnobject LOCALID_SNOWSWEPT_CAVERN_MACHAMP, DIR_SOUTH
	release
	end

Snowswept_Text_Machamp_Cry:
    .string "Mahh!!$"

Snowswept_Machamp_Movement:
    jump_in_place_down
    walk_in_place_fast_down
    walk_in_place_fast_down
    step_end

Snowswept_Cavern_Movement_Boulder:
    walk_fast_down
    walk_fast_down
    walk_fast_down
    walk_fast_down
    walk_fast_down
    walk_fast_down
    step_end

Snowswept_EventScript_Item_IcyRock::
    finditem ITEM_ICY_ROCK
    end

Snowswept_EventScript_Item_UltraBall::
    finditem ITEM_ULTRA_BALL
    end

