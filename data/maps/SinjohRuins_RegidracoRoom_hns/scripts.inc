SinjohRuins_RegidracoRoom_hns_MapScripts::
	.byte 0

SinjohRuins_EventScript_Regidrago::
    lock
	faceplayer
	waitse
	playmoncry SPECIES_REGIDRAGO, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setwildbattle SPECIES_REGIDRAGO, 80, ITEM_NONE
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special StartRegiBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, SinjohRuins_EventScript_DefeatedRegidrago
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, SinjohRuins_EventScript_RanFromRegidrago
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, SinjohRuins_EventScript_RanFromRegidrago
	setflag FLAG_SINJOHRUINS_REGIDRAGO
	release
	end

SinjohRuins_EventScript_DefeatedRegidrago::
	setflag FLAG_SINJOHRUINS_REGIDRAGO
	goto Common_EventScript_RemoveStaticPokemon
	playse SE_PIN
	applymovement LOCALID_PLAYER, Common_Movement_QuestionMark
	msgbox SinjohRuins_Text_DracoPlate
	giveitem ITEM_DRACO_PLATE, 1
	addvar VAR_PLATECOUNTER, 1
	release
	end

SinjohRuins_EventScript_RanFromRegidrago::
	setvar VAR_0x8004, SPECIES_REGIDRAGO
	goto Common_EventScript_LegendaryFlewAway
	end

SinjohRuins_Text_DracoPlate:
    .string "It seems REGIDRAGO left something behind..$"