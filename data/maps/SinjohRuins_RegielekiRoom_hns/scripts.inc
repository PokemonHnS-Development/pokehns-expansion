SinjohRuins_RegielekiRoom_hns_MapScripts::
	.byte 0

SinjohRuins_EventScript_Regieleki::
    lock
	faceplayer
	waitse
	playmoncry SPECIES_REGIELEKI, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setwildbattle SPECIES_REGIELEKI, 80, ITEM_NONE
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special StartRegiBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, SinjohRuins_EventScript_DefeatedRegieleki
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, SinjohRuins_EventScript_RanFromRegieleki
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, SinjohRuins_EventScript_RanFromRegieleki
	setflag FLAG_SINJOHRUINS_REGIELEKI
	release
	end

SinjohRuins_EventScript_DefeatedRegieleki::
	setflag FLAG_SINJOHRUINS_REGIELEKI
	goto Common_EventScript_RemoveStaticPokemon
	release
	end

SinjohRuins_EventScript_RanFromRegieleki::
	setvar VAR_0x8004, SPECIES_REGIELEKI
	goto Common_EventScript_LegendaryFlewAway
	end