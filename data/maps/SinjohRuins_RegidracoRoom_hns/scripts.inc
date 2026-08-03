SinjohRuins_RegidracoRoom_hns_MapScripts::
	.byte 0

SinjohRuins_RegidragoRoom_EventScript_Regidrago::
	lock
	faceplayer
	playmoncry SPECIES_REGIDRAGO, CRY_MODE_ENCOUNTER
	msgbox SinjohRuins_RegidragoRoom_Text_Regidrago
	delay 40
	waitmoncry
	seteventmon SPECIES_REGIDRAGO, 80
	special BattleSetup_StartLegendaryBattle
	waitstate
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, SinjohRuins_RegidragoRoom_EventScript_RegidragoRan
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_SINJOHRUINS_REGIDRAGO
	setflag FLAG_HIDE_SINJOHRUINS_REGIDRAGO
	fadescreenswapbuffers FADE_FROM_BLACK
	release
	end

SinjohRuins_RegidragoRoom_EventScript_RegidragoRan::
	release
	end

SinjohRuins_RegidragoRoom_Text_Regidrago:
	.string "REGIDRAGO: Drago!.$"

