UlaUla_Forest_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, UlaUla_Forest_hns_MapScripts_MAP_SCRIPT_ON_TRANSITION
	.byte 0

UlaUla_Forest_hns_MapScripts_MAP_SCRIPT_ON_TRANSITION:
	gettimeofday
	compare VAR_0x8000, TIME_MORNING
	goto_if_eq UlaUla_Forest_hns_MapScripts_MAP_SCRIPT_ON_TRANSITION_1
	compare VAR_0x8000, TIME_DAY
	goto_if_eq UlaUla_Forest_hns_MapScripts_MAP_SCRIPT_ON_TRANSITION_1
	setvar VAR_OBJ_GFX_ID_1, OBJ_EVENT_GFX_SPECIES ( PRIMEAPE )
	clearflag FLAG_ULAULA_TOTEM_DAY
	return

UlaUla_Forest_hns_MapScripts_MAP_SCRIPT_ON_TRANSITION_1:
	setvar VAR_OBJ_GFX_ID_1, OBJ_EVENT_GFX_SPECIES ( TANGROWTH )
	setflag FLAG_ULAULA_TOTEM_DAY
	return


Alola_Ulaula_Forest_FindItem1::
	finditem ITEM_MAX_REVIVE, 1
	end


Alola_Ulaula_TotemBattle_Trigger::
	goto_if_unset FLAG_TRIGGERED_ULAULA_TOTEM, Alola_Ulaula_TotemBattle_Trigger_1
	end

Alola_Ulaula_TotemBattle_Trigger_1:
	goto_if_set FLAG_CAUGHT_ALL_AKALA, Alola_Ulaula_TotemBattle_Trigger_7
Alola_Ulaula_TotemBattle_Trigger_5:
	end

Alola_Ulaula_TotemBattle_Trigger_4:
	lock
	delay 30
	setvar VAR_0x8004, 2
	setvar VAR_0x8005, 6
	setvar VAR_0x8006, 4
	setvar VAR_0x8007, 4
	special ShakeCamera
	waitstate
	fadescreenswapbuffers FADE_TO_BLACK
	delay 30
	clearflag FLAG_HIDE_ULAULA_TOTEM
	gettimeofday
	compare VAR_0x8000, TIME_MORNING
	goto_if_eq Alola_Ulaula_TotemBattle_Trigger_14
	compare VAR_0x8000, TIME_DAY
	goto_if_eq Alola_Ulaula_TotemBattle_Trigger_14
	playmoncry SPECIES_PRIMEAPE, 0
	setvar VAR_OBJ_GFX_ID_1, OBJ_EVENT_GFX_SPECIES ( PRIMEAPE )
	clearflag FLAG_ULAULA_TOTEM_DAY
	addobject Ulaula_Totem
	waitmoncry
Alola_Ulaula_TotemBattle_Trigger_13:
	special DrawWholeMapView
	delay 30
	fadescreenswapbuffers FADE_FROM_BLACK
	delay 30
	gettimeofday
	compare VAR_0x8000, TIME_MORNING
	goto_if_eq Alola_Ulaula_TotemBattle_Trigger_20
	compare VAR_0x8000, TIME_DAY
	goto_if_eq Alola_Ulaula_TotemBattle_Trigger_20
	playmoncry SPECIES_PRIMEAPE, 0
	applymovement Ulaula_Totem, Alola_Ulaula_TotemBattle_Trigger_Movement_0
	waitmovement 0
	waitmoncry
Alola_Ulaula_TotemBattle_Trigger_19:
	setflag FLAG_TRIGGERED_ULAULA_TOTEM
	release
	end

Alola_Ulaula_TotemBattle_Trigger_6:
	goto_if_set FLAG_CAUGHT_ALL_PONI, Alola_Ulaula_TotemBattle_Trigger_10
	goto Alola_Ulaula_TotemBattle_Trigger_5

Alola_Ulaula_TotemBattle_Trigger_7:
	goto_if_set FLAG_CAUGHT_ALL_ULAULA, Alola_Ulaula_TotemBattle_Trigger_6
	goto Alola_Ulaula_TotemBattle_Trigger_5

Alola_Ulaula_TotemBattle_Trigger_10:
	goto_if_set FLAG_CAUGHT_ALL_MELEMELE, Alola_Ulaula_TotemBattle_Trigger_4
	goto Alola_Ulaula_TotemBattle_Trigger_5

Alola_Ulaula_TotemBattle_Trigger_14:
	playmoncry SPECIES_TANGROWTH, 0
	setvar VAR_OBJ_GFX_ID_1, OBJ_EVENT_GFX_SPECIES ( TANGROWTH )
	setflag FLAG_ULAULA_TOTEM_DAY
	addobject Ulaula_Totem
	waitmoncry
	goto Alola_Ulaula_TotemBattle_Trigger_13

Alola_Ulaula_TotemBattle_Trigger_20:
	playmoncry SPECIES_TANGROWTH, 0
	applymovement Ulaula_Totem, Alola_Ulaula_TotemBattle_Trigger_Movement_0
	waitmovement 0
	waitmoncry
	goto Alola_Ulaula_TotemBattle_Trigger_19


Alola_Ulaula_TotemBattle::
	lock
	faceplayer
	goto_if_set FLAG_ULAULA_TOTEM_DAY, Alola_Ulaula_TotemBattle_1
	playmoncry SPECIES_PRIMEAPE, 0
	msgbox Alola_Ulaula_TotemBattle_Text_2, MSGBOX_AUTOCLOSE
	waitmoncry
	setwildbattle SPECIES_MANKEY, 60, ITEM_NONE, SPECIES_PRIMEAPE, 60, ITEM_LUM_BERRY
	settotemboost B_POSITION_OPPONENT_RIGHT, 1, 1, 1, 1, 1, 1
	setflag FLAG_NO_WILD_CATCHING
	setflag FLAG_NO_WILD_RUNNING
	setflag FLAG_SMART_WILD_AI
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq Alola_Ulaula_TotemBattle_8
	compare VAR_RESULT, B_OUTCOME_LOST
	goto_if_eq Alola_Ulaula_TotemBattle_12
	return

Alola_Ulaula_TotemBattle_1:
	playmoncry SPECIES_TANGROWTH, 0
	msgbox Alola_Ulaula_TotemBattle_Text_0, MSGBOX_AUTOCLOSE
	waitmoncry
	setwildbattle SPECIES_TANGELA, 60, ITEM_NONE, SPECIES_TANGROWTH, 60, ITEM_OCCA_BERRY
	settotemboost B_POSITION_OPPONENT_RIGHT, 1, 1, 1, 1, 1, 1
	setflag FLAG_NO_WILD_CATCHING
	setflag FLAG_NO_WILD_RUNNING
	setflag FLAG_SMART_WILD_AI
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq Alola_Ulaula_TotemBattle_5
	compare VAR_RESULT, B_OUTCOME_LOST
	goto_if_eq Alola_Ulaula_TotemBattle_10
	return

Alola_Ulaula_TotemBattle_5:
	setflag FLAG_HIDE_ULAULA_TOTEM
	setflag FLAG_DEFEATED_ULAULA_TOTEM
	removeobject Ulaula_Totem
	msgbox Alola_Ulaula_TotemBattle_Text_1, MSGBOX_AUTOCLOSE
	clearflag FLAG_NO_WILD_CATCHING
	clearflag FLAG_NO_WILD_RUNNING
	clearflag FLAG_SMART_WILD_AI
	release
	end

Alola_Ulaula_TotemBattle_8:
	setflag FLAG_HIDE_ULAULA_TOTEM
	setflag FLAG_DEFEATED_ULAULA_TOTEM
	removeobject Ulaula_Totem
	msgbox Alola_Ulaula_TotemBattle_Text_3, MSGBOX_AUTOCLOSE
	clearflag FLAG_NO_WILD_CATCHING
	clearflag FLAG_NO_WILD_RUNNING
	clearflag FLAG_SMART_WILD_AI
	release
	end

Alola_Ulaula_TotemBattle_10:
	clearflag FLAG_NO_WILD_CATCHING
	clearflag FLAG_NO_WILD_RUNNING
	clearflag FLAG_SMART_WILD_AI
	release
	end

Alola_Ulaula_TotemBattle_12:
	clearflag FLAG_NO_WILD_CATCHING
	clearflag FLAG_NO_WILD_RUNNING
	clearflag FLAG_SMART_WILD_AI
	release
	end


Alola_Ulaula_Totem_sign::
	lock
	goto_if_set FLAG_BATTLED_TAPU_FINI, Alola_Ulaula_Totem_sign_5
Alola_Ulaula_Totem_sign_3:
	msgbox Alola_Ulaula_Totem_sign_Text_6, MSGBOX_AUTOCLOSE
	release
	end

Alola_Ulaula_Totem_sign_2:
	msgbox Alola_Ulaula_Totem_sign_Text_0
	dynmultichoice 20, 4, FALSE, 4, 0, DYN_MULTICHOICE_CB_NONE, Alola_Ulaula_Totem_sign_Text_1, Alola_Ulaula_Totem_sign_Text_2, Alola_Ulaula_Totem_sign_Text_3, Alola_Ulaula_Totem_sign_Text_4, Alola_Ulaula_Totem_sign_Text_5
	compare VAR_RESULT, 0
	goto_if_eq Alola_Ulaula_Totem_sign_12
	compare VAR_RESULT, 1
	goto_if_eq Alola_Ulaula_Totem_sign_15
	compare VAR_RESULT, 2
	goto_if_eq Alola_Ulaula_Totem_sign_18
	compare VAR_RESULT, 3
	goto_if_eq Alola_Ulaula_Totem_sign_20
	release
	end

Alola_Ulaula_Totem_sign_4:
	goto_if_set FLAG_BATTLED_TAPU_BULU, Alola_Ulaula_Totem_sign_8
	goto Alola_Ulaula_Totem_sign_3

Alola_Ulaula_Totem_sign_5:
	goto_if_set FLAG_BATTLED_TAPU_KOKO, Alola_Ulaula_Totem_sign_4
	goto Alola_Ulaula_Totem_sign_3

Alola_Ulaula_Totem_sign_8:
	goto_if_set FLAG_BATTLED_TAPU_LELE, Alola_Ulaula_Totem_sign_2
	goto Alola_Ulaula_Totem_sign_3

Alola_Ulaula_Totem_sign_12:
	warp MAP_MELEMELE_ISLE_HNS, 34, 26
	waitstate
	end

Alola_Ulaula_Totem_sign_15:
	warp MAP_AKALA_ISLE_HNS, 9, 10
	waitstate
	end

Alola_Ulaula_Totem_sign_18:
	warp MAP_ULA_ULA_FOREST_HNS, 16, 5
	waitstate
	end

Alola_Ulaula_Totem_sign_20:
	warp MAP_PONI_ISLE_HNS, 13, 8
	waitstate
	end


Alola_Ulaula_BattleVsTapuBulu::
	lock
	faceplayer
	playmoncry SPECIES_TAPU_BULU, CRY_MODE_ENCOUNTER
	msgbox Alola_Ulaula_BattleVsTapuBulu_Text_0
	waitmoncry
	seteventmon SPECIES_TAPU_BULU, 60
	special BattleSetup_StartLegendaryBattle
	waitstate
	specialvar VAR_RESULT, GetBattleOutcome
	compare VAR_RESULT, B_OUTCOME_CAUGHT
	goto_if_eq Alola_Ulaula_BattleVsTapuBulu_2
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq Alola_Ulaula_BattleVsTapuBulu_3
	release
	end

	release
	end

Alola_Ulaula_BattleVsTapuBulu_2:
	setflag FLAG_HIDE_TAPU_BULU
	setflag FLAG_BATTLED_TAPU_BULU
	removeobject Ulaula_Tapu
	release
	end

Alola_Ulaula_BattleVsTapuBulu_3:
	setflag FLAG_HIDE_TAPU_BULU
	setflag FLAG_BATTLED_TAPU_BULU
	removeobject Ulaula_Tapu
	release
	end


Alola_Ulaula_TotemBattle_Trigger_Movement_0:
	walk_in_place_down
	walk_in_place_down
	step_end

Alola_Ulaula_TotemBattle_Text_0:
	.string "Graah!$"

Alola_Ulaula_TotemBattle_Text_1:
	.string "Totem Tangrowth was defeated!\n"
	.string "It scampered off somewhere…$"

Alola_Ulaula_TotemBattle_Text_2:
	.string "Graah!$"

Alola_Ulaula_TotemBattle_Text_3:
	.string "Totem Primeape was defeated!\n"
	.string "It scampered off somewhere…$"

Alola_Ulaula_Totem_sign_Text_0:
	.string "The totem is emanating a strong\n"
	.string "energy…\p"
	.string "Touch the totem to teleport to another\n"
	.string "Isle?$"

Alola_Ulaula_Totem_sign_Text_1:
	.string "Melemele Isle$"

Alola_Ulaula_Totem_sign_Text_2:
	.string "Akala Isle$"

Alola_Ulaula_Totem_sign_Text_3:
	.string "Ula'ula Isle$"

Alola_Ulaula_Totem_sign_Text_4:
	.string "Poni Isle$"

Alola_Ulaula_Totem_sign_Text_5:
	.string "Cancel$"

Alola_Ulaula_Totem_sign_Text_6:
	.string "A strange totem stands here,\n"
	.string "power is emanating from it…$"

Alola_Ulaula_BattleVsTapuBulu_Text_0:
	.string "Bu-Bulu!$"
