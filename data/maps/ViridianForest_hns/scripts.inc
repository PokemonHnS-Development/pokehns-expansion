ViridianForest_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, ViridianForest_hns_OnTransition
	.byte 0

ViridianForest_hns_OnTransition::
	goto_if_ge VAR_VIRIDIAN_FOREST_PICHU, 1, ViridianForest_hns_NoOp
	specialvar VAR_RESULT, CheckCelebi
	goto_if_eq VAR_RESULT, TRUE, ViridianForest_EventScript_SetPichu
	end

ViridianForest_hns_NoOp::
	end

ViridianForest_EventScript_SetPichu::
	clearflag FLAG_HIDE_VIRIDIAN_FOREST_SPIKY_EARED_PICHU1
	setvar VAR_VIRIDIAN_FOREST_PICHU, 1
	end

ViridianForest_EventScript_Bugsy::
	lock
	faceplayer
	msgbox ViridianForest_Text_Bugsy, MSGBOX_DEFAULT
	closemessage
	fadescreenswapbuffers FADE_TO_BLACK
	setflag FLAG_HIDE_VIRIDIAN_BUGSY
	removeobject LOCALID_VIRIDIAN_BUGSY
	fadescreenswapbuffers FADE_FROM_BLACK
	clearflag FLAG_HIDE_DOJO_BUGSY
	release
	end

ViridianForest_Text_Bugsy:
	.string "BUGSY: I came to KANTO to look for\n"
	.string "BUG-TYPE POKéMON, so I can become\l"
	.string "a stronger BUG-TYPE POKéMON\l"
	.string "TRAINER!\p"
    .string "If you're ready for another match,\n"
    .string "I'll be at the DOJO in SAFFRON!$"

ViridianForest_TriggerScript_Pichu1::
	lock
	turnobject LOCALID_VIRIDIAN_FOREST_PICHU1, DIR_NORTH
	playse SE_PIN
	applymovement2 LOCALID_VIRIDIAN_FOREST_PICHU1, Common_Movement_ExclamationMark
	delay 60
	applymovement2 LOCALID_VIRIDIAN_FOREST_PICHU1, ViridianForest_Movement_Pichu1_GoDown
	delay 60
	playse SE_LEDGE
	waitmovement 0
	removeobject LOCALID_VIRIDIAN_FOREST_PICHU1
	setvar VAR_VIRIDIAN_FOREST_PICHU, 2
	clearflag FLAG_HIDE_VIRIDIAN_FOREST_SPIKY_EARED_PICHU2
	release
	end

ViridianForest_Movement_Pichu1_GoDown:
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_down
	walk_fast_down
	jump_2_down
	step_end

ViridianForest_TriggerScript_Pichu2_West::
	lock
	turnobject LOCALID_VIRIDIAN_FOREST_PICHU2, DIR_WEST
	playse SE_PIN
	applymovement2 LOCALID_VIRIDIAN_FOREST_PICHU2, Common_Movement_ExclamationMark
	delay 60
	applymovement2 LOCALID_VIRIDIAN_FOREST_PICHU2, ViridianForest_Movement_Pichu2_GoUp
	waitmovement 0
	removeobject LOCALID_VIRIDIAN_FOREST_PICHU2
	setvar VAR_VIRIDIAN_FOREST_PICHU, 3
	clearflag FLAG_HIDE_VIRIDIAN_FOREST_SPIKY_EARED_PICHU3
	release
	end

ViridianForest_TriggerScript_Pichu2_South::
	lock
	turnobject LOCALID_VIRIDIAN_FOREST_PICHU2, DIR_SOUTH
	playse SE_PIN
	applymovement2 LOCALID_VIRIDIAN_FOREST_PICHU2, Common_Movement_ExclamationMark
	delay 60
	applymovement2 LOCALID_VIRIDIAN_FOREST_PICHU2, ViridianForest_Movement_Pichu2_GoUp
	waitmovement 0
	removeobject LOCALID_VIRIDIAN_FOREST_PICHU2
	setvar VAR_VIRIDIAN_FOREST_PICHU, 3
	clearflag FLAG_HIDE_VIRIDIAN_FOREST_SPIKY_EARED_PICHU3
	release
	end

ViridianForest_Movement_Pichu2_GoUp:
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

ViridianForest_TriggerScript_Pichu2_North::
	lock
	turnobject LOCALID_VIRIDIAN_FOREST_PICHU2, DIR_NORTH
	playse SE_PIN
	applymovement2 LOCALID_VIRIDIAN_FOREST_PICHU2, Common_Movement_ExclamationMark
	delay 60
	applymovement2 LOCALID_VIRIDIAN_FOREST_PICHU2, ViridianForest_Movement_Pichu2_GoDown
	waitmovement 0
	clearflag FLAG_HIDE_VIRIDIAN_FOREST_SPIKY_EARED_PICHU
	addobject LOCALID_VIRIDIAN_FOREST_PICHU
	removeobject LOCALID_VIRIDIAN_FOREST_PICHU2
	setvar VAR_VIRIDIAN_FOREST_PICHU, 4
	release
	end

ViridianForest_Movement_Pichu2_GoDown:
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	face_down
	step_end

ViridianForest_TriggerScript_Pichu3_West::
	lock
	turnobject LOCALID_VIRIDIAN_FOREST_PICHU3, DIR_WEST
	playse SE_PIN
	applymovement2 LOCALID_VIRIDIAN_FOREST_PICHU3, Common_Movement_ExclamationMark
	delay 60
	applymovement2 LOCALID_VIRIDIAN_FOREST_PICHU3, ViridianForest_Movement_Pichu2_GoRight
	waitmovement 0
	removeobject LOCALID_VIRIDIAN_FOREST_PICHU3
	setvar VAR_VIRIDIAN_FOREST_PICHU, 2
	clearflag FLAG_HIDE_VIRIDIAN_FOREST_SPIKY_EARED_PICHU2
	release
	end

ViridianForest_Movement_Pichu2_GoRight:
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

ViridianForest_TriggerScript_Pichu3_East::
	lock
	turnobject LOCALID_VIRIDIAN_FOREST_PICHU3, DIR_EAST
	playse SE_PIN
	applymovement2 LOCALID_VIRIDIAN_FOREST_PICHU3, Common_Movement_ExclamationMark
	delay 60
	applymovement2 LOCALID_VIRIDIAN_FOREST_PICHU3, ViridianForest_Movement_Pichu3_GoLeft
	waitmovement 0
	removeobject LOCALID_VIRIDIAN_FOREST_PICHU3
	setvar VAR_VIRIDIAN_FOREST_PICHU, 2
	clearflag FLAG_HIDE_VIRIDIAN_FOREST_SPIKY_EARED_PICHU2
	release
	end

ViridianForest_Movement_Pichu3_GoLeft:
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end

ViridianForest_EventScript_SpikyEaredPichu::
	lock
	faceplayer
	playmoncry SPECIES_PICHU_SPIKY_EARED, CRY_MODE_ENCOUNTER
	waitmoncry
	setwildbattle SPECIES_PICHU_SPIKY_EARED, 35
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, ViridianForest_EventScript_SpikyEaredPichuRan
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_VIRIDIAN_FOREST_PICHU
	setflag FLAG_HIDE_VIRIDIAN_FOREST_SPIKY_EARED_PICHU
	fadescreenswapbuffers FADE_FROM_BLACK
	release
	end

ViridianForest_EventScript_SpikyEaredPichuRan::
	release
	end

ViridianForest_EventScript_Item_Psych_Up::
    finditem ITEM_TM_PSYCH_UP
    end

ViridianForest_EventScript_MaxPotion::
    finditem ITEM_MAX_POTION
    end

ViridianForest_EventScript_Elixir::
    finditem ITEM_ELIXIR
    end

ViridianForest_EventScript_Revive::
    finditem ITEM_REVIVE
    end

ViridianForest_EventScript_FullRestore::
    finditem ITEM_FULL_RESTORE
    end

ViridianForest_EventScript_MaxEther::
    finditem ITEM_MAX_ETHER
    end

ViridianForest_EventScript_FullHeal::
    finditem ITEM_FULL_HEAL
    end
