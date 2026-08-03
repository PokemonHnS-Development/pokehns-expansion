SinjohRuins_RegielekiRoom_hns_MapScripts::
	.byte 0

SinjohRuins_RegielekiRoom_EventScript_Regieleki::
	lock
	faceplayer
	playmoncry SPECIES_REGIELEKI, CRY_MODE_ENCOUNTER
	msgbox SinjohRuins_RegielekiRoom_Text_Regieleki
	delay 40
	waitmoncry
	seteventmon SPECIES_REGIELEKI, 80
	special BattleSetup_StartLegendaryBattle
	waitstate
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, SinjohRuins_RegielekiRoom_EventScript_RegielekiRan
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_SINJOHRUINS_REGIELEKI
	setflag FLAG_HIDE_SINJOHRUINS_REGIELEKI
	fadescreenswapbuffers FADE_FROM_BLACK
	release
	end

SinjohRuins_RegielekiRoom_EventScript_RegielekiRan::
	release
	end

SinjohRuins_RegielekiRoom_Text_Regieleki:
	.string "REGIELEKI: LekiLeki!.$"
