.set LOCALID_SEAFOAMGROUDON, 1

SeafoamIslands_SecretCave_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, HoennSeek_EventScript_GroudonCaveOnTransition @ Hoenn & Seek 2.0 part 36
	.byte 0

SeafoamIslands_SecretCave_EventScript_Groudon::
	lock
	faceplayer
	playmoncry SPECIES_GROUDON, CRY_MODE_ENCOUNTER
	waitmoncry
	seteventmon SPECIES_GROUDON, 70
	special BattleSetup_StartLegendaryBattle
waitstate
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, SeafoamIslands_SecretCave_EventScript_GroudonRan
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_SEAFOAMGROUDON
	setflag FLAG_HIDE_GROUDON
	fadescreenswapbuffers FADE_FROM_BLACK
	release
	end

SeafoamIslands_SecretCave_EventScript_GroudonRan::
	release
	end
