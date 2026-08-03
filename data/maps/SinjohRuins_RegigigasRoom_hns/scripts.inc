SinjohRuins_RegigigasRoom_hns_MapScripts::
	.byte 0

SinjohRuins_RegigigasRoom_EventScript_Regigigas::
	lock
	faceplayer
	playmoncry SPECIES_REGIGIGAS, CRY_MODE_ENCOUNTER
	msgbox SinjohRuins_RegigigasRoom_Text_Regigigas
	delay 40
	waitmoncry
	seteventmon SPECIES_REGIGIGAS, 80
	special BattleSetup_StartLegendaryBattle
	waitstate
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, SinjohRuins_RegigigasRoom_EventScript_RegigigasRan
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_SINJOHRUINS_REGIGIGAS
	setflag FLAG_HIDE_SINJOHRUINS_REGIGIGAS
	fadescreenswapbuffers FADE_FROM_BLACK
	release
	end

SinjohRuins_RegigigasRoom_EventScript_RegigigasRan::
	release
	end

SinjohRuins_RegigigasRoom_Text_Regigigas:
	.string "REGIGIGAS: GiiiiiiG!$"
