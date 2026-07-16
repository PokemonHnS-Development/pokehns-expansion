SinjohRuins_RegirockRoom_hns_MapScripts::
	.byte 0

SinjohRuins_EventScript_Regirock::
    lock
	faceplayer
	waitse
	playmoncry SPECIES_REGIROCK, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setwildbattle SPECIES_REGIROCK, 80, ITEM_NONE
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special StartRegiBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, SinjohRuins_EventScript_DefeatedRegirock
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, SinjohRuins_EventScript_RanFromRegirock
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, SinjohRuins_EventScript_RanFromRegirock
	setflag FLAG_SINJOHRUINS_REGIROCK
	release
	end

SinjohRuins_EventScript_DefeatedRegirock::
	setflag FLAG_SINJOHRUINS_REGIROCK
	goto Common_EventScript_RemoveStaticPokemon
	playse SE_PIN
	applymovement LOCALID_PLAYER, Common_Movement_QuestionMark
	msgbox SinjohRuins_Text_StonePlate MSGBOX_DEFAULT
	giveitem ITEM_STONE_PLATE, 1
	addvar VAR_PLATECOUNTER, 1
	release
	end

SinjohRuins_EventScript_RanFromRegirock::
	setvar VAR_0x8004, SPECIES_REGIROCK
	goto Common_EventScript_LegendaryFlewAway
	end

SinjohRuins_Text_StonePlate:
    .string "It seems REGIROCK left something behind..$"