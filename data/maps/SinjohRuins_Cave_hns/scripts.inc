SinjohRuins_Cave_hns_MapScripts::
	.byte 0

SinjohRuins_Cave_EventScript_Ursaluna::
	lock
	faceplayer
	setwildbattle SPECIES_URSALUNA, 80
	waitsewaitwait
	playmoncry SPECIES_URSALUNA, CRY_MODE_ENCOUNTER
	msgbox Text_Grrwowl MSGBOX_DEFAULT
	waitmessage
	waitmoncry
	delay 10
	waitbuttonpress
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	settotemboost B_POSITION_OPPONENT_LEFT, 0, 2, 0, 2, 0
	playbgm MUS_HG_VS_SUICUNE, 0
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, SinjohRuins_Cave_EventScript_DefeatedUrsaluna
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, SinjohRuins_Cave_EventScript_RanFromUrsaluna
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, SinjohRuins_Cave_EventScript_RanFromUrsaluna
	setflag FLAG_FOUGHT_NOBLE_URSALUNA
	removeobject LOCALID_NOBLE_URSALUNA
	addvar VAR_NOBLECOUNTER, 1
	release
	end

SinjohRuins_Cave_EventScript_DefeatedUrsaluna::
	setflag FLAG_FOUGHT_NOBLE_URSALUNA
	removeobject LOCALID_NOBLE_URSALUNA
	end

SinjohRuins_Cave_EventScript_RanFromUrsaluna::
	setvar VAR_0x8004, SPECIES_URSALUNA
	end

Text_Grrwowl:
    .string "GRRRR!!$"