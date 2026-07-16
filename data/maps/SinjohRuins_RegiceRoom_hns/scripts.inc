SinjohRuins_RegiceRoom_hns_MapScripts::
	.byte 0

SinjohRuins_EventScript_Regice::
    lock
	faceplayer
	waitse
	playmoncry SPECIES_REGICE, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setwildbattle SPECIES_REGICE, 80, ITEM_NONE
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special StartRegiBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, SinjohRuins_EventScript_DefeatedRegice
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, SinjohRuins_EventScript_RanFromRegice
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, SinjohRuins_EventScript_RanFromRegice
	setflag FLAG_SINJOHRUINS_REGICE
	release
	end

SinjohRuins_EventScript_DefeatedRegice::
	setflag FLAG_SINJOHRUINS_REGICE
	goto Common_EventScript_RemoveStaticPokemon
	release
	end

SinjohRuins_EventScript_RanFromRegice::
	setvar VAR_0x8004, SPECIES_REGICE
	goto Common_EventScript_LegendaryFlewAway
	end
