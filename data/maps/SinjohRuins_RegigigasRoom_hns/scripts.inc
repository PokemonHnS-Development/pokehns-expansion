SinjohRuins_RegigigasRoom_hns_MapScripts::
	.byte 0

SinjohRuins_EventScript_Regigigas::
    lock
	faceplayer
	waitse
	playmoncry SPECIES_REGIGIGAS, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, 1  @ vertical pan
    setvar VAR_0x8005, 1  @ horizontal pan
    setvar VAR_0x8006, 15  @ num shakes
    setvar VAR_0x8007, 6  @ shake delay
    special ShakeCamera
    waitstate
	delay 10
	setwildbattle SPECIES_REGIGIGAS, 100, ITEM_NONE
	settotemboost B_POSITION_OPPONENT_LEFT, 2, 2, 0, 0, 2, 0, 0
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special StartRegiBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, SinjohRuins_EventScript_DefeatedRegigigas
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, SinjohRuins_EventScript_RanFromRegigigas
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, SinjohRuins_EventScript_RanFromRegigigas
	setflag FLAG_SINJOHRUINS_REGIGIGAS
	release
	end

SinjohRuins_EventScript_DefeatedRegigigas::
	setflag FLAG_SINJOHRUINS_REGIGIGAS
	goto Common_EventScript_RemoveStaticPokemon
	release
	end

SinjohRuins_EventScript_RanFromRegigigas::
	setvar VAR_0x8004, SPECIES_REGIGIGAS
	goto Common_EventScript_LegendaryFlewAway
	end

