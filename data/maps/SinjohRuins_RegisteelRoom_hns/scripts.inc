SinjohRuins_RegisteelRoom_hns_MapScripts::
	.byte 0

SinjohRuins_EventScript_Registeel::
    lock
	faceplayer
	waitse
	playmoncry SPECIES_REGISTEEL, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setwildbattle SPECIES_REGISTEEL, 80, ITEM_NONE
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special StartRegiBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, SinjohRuins_EventScript_DefeatedRegisteel
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, SinjohRuins_EventScript_RanFromRegisteel
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, SinjohRuins_EventScript_RanFromRegisteel
	setflag FLAG_SINJOHRUINS_REGICE
	release
	end

SinjohRuins_EventScript_DefeatedRegisteel::
	setflag FLAG_SINJOHRUINS_REGISTEEL
	goto Common_EventScript_RemoveStaticPokemon
	release
	end

SinjohRuins_EventScript_RanFromRegisteel::
	setvar VAR_0x8004, SPECIES_REGISTEEL
	goto Common_EventScript_LegendaryFlewAway
	end

