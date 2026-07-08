Route50_hns_MapScripts::
    map_script MAP_SCRIPT_ON_TRANSITION, Route50_hns_OnTransition
	.byte 0

Route50_hns_OnTransition::
    goto_if_unset FLAG_NOBLES_UNLOCKED, Route50_Hide_Noble
	end

Route50_Hide_Noble::
    removeobject LOCALID_NOBLE_KLEAVOR
	removeobject LOCALID_NOBLE_SNEASLER
	release
	end


Route50_EventScript_Noble_Kleavor_Trigger::
    goto_if_set FLAG_NOBLES_UNLOCKED, Route50_EventScript_Kleavor
	end

Route50_EventScript_Noble_Sneasler_Trigger::
    goto_if_set FLAG_NOBLES_UNLOCKED, Route50_EventScript_Sneasler
	end



Route50_EventScript_Kleavor::
	lock
	addobject LOCALID_NOBLE_KLEAVOR
	applymovement LOCALID_NOBLE_KLEAVOR, Route50_Kleavor_Movement
	delay 110
	playse SE_BIKE_HOP
	waitmovement
	setwildbossbattle species=SPECIES_KLEAVOR, level=80, item=ITEM_SCOPE_LENS, move1_1=MOVE_STONE_AXE, move1_2=MOVE_CROSS_POISON, move1_3=MOVE_LUNGE move1_4=MOVE_FOCUS_ENERGY
	waitse
	playmoncry SPECIES_KLEAVOR, CRY_MODE_ENCOUNTER
	msgbox Route50_Text_KleavorCry MSGBOX_DEFAULT
	waitmessage
	waitmoncry
	delay 10
	waitbuttonpress
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	settotemboost B_POSITION_OPPONENT_LEFT, 1, 2, 0, 0, 2, 0
	playbgm MUS_HG_VS_SUICUNE, 0
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, Route50_EventScript_DefeatedKleavor
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, Route50_EventScript_RanFromKleavor
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, Route50_EventScript_RanFromKleavor
	setflag FLAG_FOUGHT_NOBLE_KLEAVOR
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_NOBLE_KLEAVOR
	fadescreen FADE_FROM_BLACK
    DELAY 30
	playse SE_PIN
	applymovement LOCALID_PLAYER, Common_Movement_QuestionMark
	msgbox Route50_Text_InsectPlate MSGBOX_DEFAULT
	giveitem ITEM_INSECT_PLATE, 1
	addvar VAR_PLATECOUNTER, 1
	addvar VAR_NOBLECOUNTER, 1
	addvar VAR_NOBLE_KLEAVOR_TRIGGER, 1
	closemessage
	release
	end

Route50_EventScript_DefeatedKleavor::
	setflag FLAG_FOUGHT_NOBLE_KLEAVOR
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_NOBLE_KLEAVOR
	fadescreen FADE_FROM_BLACK
    delay 30
	playse SE_PIN
	applymovement LOCALID_PLAYER, Common_Movement_QuestionMark
	msgbox Route50_Text_InsectPlate MSGBOX_DEFAULT
	giveitem ITEM_INSECT_PLATE, 1
	addvar VAR_PLATECOUNTER, 1
	addvar VAR_NOBLECOUNTER, 1
	addvar VAR_NOBLE_KLEAVOR_TRIGGER, 1
	closemessage
	release
	end

Route50_EventScript_RanFromKleavor::
	setvar VAR_0x8004, SPECIES_KLEAVOR
	end

Route50_Text_KleavorCry:
    .string "Scrraahh!!$"

Route50_Text_InsectPlate:
    .string "It seems KLEAVOR left something behind..$"

Route50_Kleavor_Movement:
    walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_down
	walk_left
	jump_down
	face_down
	step_end

Route50_EventScript_Sneasler::
	lock
	addobject LOCALID_NOBLE_SNEASLER
	applymovement LOCALID_NOBLE_SNEASLER, Route50_Sneasler_Movement
	delay 60
	playse SE_BIKE_HOP
	waitmovement
	setwildbossbattle species=SPECIES_SNEASLER, level=80, item=ITEM_RAZOR_CLAW, move1_1=MOVE_DIRE_CLAW, move1_2=MOVE_ROCK_SLIDE, move1_3=MOVE_BRICK_BREAK move1_4=MOVE_LASH_OUT
	waitse
	playmoncry SPECIES_SNEASLER, CRY_MODE_ENCOUNTER
	msgbox Route50_Text_SneaslerCry MSGBOX_DEFAULT
	waitmessage
	waitmoncry
	delay 10
	waitbuttonpress
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	settotemboost B_POSITION_OPPONENT_LEFT, 1, 0, 2, 0, 0, 0
	playbgm MUS_HG_VS_SUICUNE, 0
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, Route50_EventScript_DefeatedSneasler
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, Route50_EventScript_RanFromSneasler
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, Route50_EventScript_RanFromSneasler
	setflag FLAG_FOUGHT_NOBLE_SNEASLER
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_NOBLE_SNEASLER
	fadescreen FADE_FROM_BLACK
    DELAY 30
	playse SE_PIN
	applymovement LOCALID_PLAYER, Common_Movement_QuestionMark
	msgbox Route50_Text_ToxicPlate MSGBOX_DEFAULT
	giveitem ITEM_TOXIC_PLATE, 1
	addvar VAR_PLATECOUNTER, 1
	addvar VAR_NOBLECOUNTER, 1
	addvar VAR_NOBLE_SNEASLER_TRIGGER, 1
	closemessage
	release
	end

Route50_EventScript_DefeatedSneasler::
	setflag FLAG_FOUGHT_NOBLE_SNEASLER
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_NOBLE_SNEASLER
	fadescreen FADE_FROM_BLACK
    delay 30
	playse SE_PIN
	applymovement LOCALID_PLAYER, Common_Movement_QuestionMark
	msgbox Route50_Text_ToxicPlate MSGBOX_DEFAULT
	giveitem ITEM_TOXIC_PLATE, 1
	addvar VAR_PLATECOUNTER, 1
	addvar VAR_NOBLECOUNTER, 1
	addvar VAR_NOBLE_SNEASLER_TRIGGER, 1
	closemessage
	end

Route50_EventScript_RanFromSneasler::
	setvar VAR_0x8004, SPECIES_SNEASLER
	end

Route50_Text_SneaslerCry:
    .string "Wrrhehe!!$"

Route50_Text_ToxicPlate:
    .string "It seems SNEASLER left something behind..$"

Route50_Sneasler_Movement:
    walk_down
	walk_down
	walk_down
	walk_down
	jump_down
	face_down
	step_end