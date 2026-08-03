SinjohRuins_RegirockRoom_hns_MapScripts::
	.byte 0

SinjohRuins_RegirockRoom_EventScript_Regirock::
	lock
	faceplayer
	playmoncry SPECIES_REGIROCK, CRY_MODE_ENCOUNTER
	msgbox SinjohRuins_RegirockRoom_Text_Regirock
	delay 40
	waitmoncry
	seteventmon SPECIES_REGIROCK, 80
	special BattleSetup_StartLegendaryBattle
	waitstate
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, SinjohRuins_RegirockRoom_EventScript_RegirockRan
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_SINJOHRUINS_REGIROCK
	setflag FLAG_HIDE_SINJOHRUINS_REGIROCK
	fadescreenswapbuffers FADE_FROM_BLACK
	release
	end

SinjohRuins_RegirockRoom_EventScript_RegirockRan::
	release
	end

SinjohRuins_RegirockRoom_Text_Regirock:
	.string "REGIROCK: RegiROCK!$"
