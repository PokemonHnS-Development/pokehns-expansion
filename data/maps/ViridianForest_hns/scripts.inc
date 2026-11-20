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

ViridianForest_EventScript_Rob::
	trainerbattle_single TRAINER_ROB_HNS, Route2_Text_BugCatcherRob_Seen, Route2_Text_BugCatcherRob_Beaten, ViridianForest_EventScript_RegisterRob
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, ViridianForest_EventScript_RematchRob
	msgbox Route2_Text_BugCatcherRob_AfterBattle, MSGBOX_AUTOCLOSE
	end

ViridianForest_EventScript_RegisterRob::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route2_Text_RobRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_ROB_HNS
	release
	end

ViridianForest_EventScript_RematchRob::
	trainerbattle_rematch TRAINER_ROB_HNS, Route2_Text_RobRematchIntro, Route2_Text_RobRematchDefeat
	msgbox Route2_Text_RobPostRematch, MSGBOX_AUTOCLOSE
	goto_if_defeated TRAINER_ROB_2_HNS, ViridianForest_EventScript_RematchRobTryGiveItem
	end

ViridianForest_EventScript_RematchRobTryGiveItem::
	checkitem ITEM_TM_X_SCISSOR
	goto_if_eq VAR_RESULT, TRUE, Common_EventScript_NoOp
	giveitem ITEM_TM_X_SCISSOR
	closemessage
	end

ViridianForest_EventScript_Ed::
	trainerbattle_single TRAINER_ED_HNS, Route2_Text_BugCatcherEd_Seen, Route2_Text_BugCatcherEd_Beaten
	msgbox Route2_Text_BugCatcherEd_AfterBattle, MSGBOX_AUTOCLOSE
	end

ViridianForest_EventScript_Doug::
	trainerbattle_single TRAINER_DOUG_HNS, Route2_Text_BugCatcherDoug_Seen, Route2_Text_BugCatcherDoug_Beaten
	msgbox Route2_Text_BugCatcherDoug_AfterBattle, MSGBOX_AUTOCLOSE
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
	.string "באגסי: באתי לקאנטו לחפש\n"
	.string "פוקימונים מסוג חרק,\p"
	.string "כדי להפוך למאמן חזק יותר\n"
	.string "של פוקימונים מסוג חרק!\p"
	.string "אם אתה מוכן לעוד קרב,\n"
	.string "אהיה בדוג'ו בסאפרון!$"

ViridianForest_TriggerScript_Pichu1::
	lock
	turnobject LOCALID_VIRIDIAN_FOREST_PICHU1, DIR_NORTH
	playse SE_PIN
	applymovement2 LOCALID_VIRIDIAN_FOREST_PICHU1, Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_VIRIDIAN_FOREST_PICHU1
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
	delay 55
	waitmovement LOCALID_VIRIDIAN_FOREST_PICHU2
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
	delay 55
	waitmovement LOCALID_VIRIDIAN_FOREST_PICHU2
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
	delay 55
	waitmovement LOCALID_VIRIDIAN_FOREST_PICHU2
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
	delay 55
	waitmovement LOCALID_VIRIDIAN_FOREST_PICHU3
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
	delay 55
	waitmovement LOCALID_VIRIDIAN_FOREST_PICHU3
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
