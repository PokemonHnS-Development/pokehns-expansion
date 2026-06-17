UlaUla_Forest_hns_MapScripts::
# 2 "data/maps/UlaUla_Forest_hns/scripts.pory"
	map_script MAP_SCRIPT_ON_TRANSITION, UlaUla_Forest_hns_MapScripts_MAP_SCRIPT_ON_TRANSITION
	.byte 0

UlaUla_Forest_hns_MapScripts_MAP_SCRIPT_ON_TRANSITION:
# 3 "data/maps/UlaUla_Forest_hns/scripts.pory"
	gettimeofday
# 4 "data/maps/UlaUla_Forest_hns/scripts.pory"
	compare VAR_0x8000, TIME_MORNING
	goto_if_eq UlaUla_Forest_hns_MapScripts_MAP_SCRIPT_ON_TRANSITION_1
# 4 "data/maps/UlaUla_Forest_hns/scripts.pory"
	compare VAR_0x8000, TIME_DAY
	goto_if_eq UlaUla_Forest_hns_MapScripts_MAP_SCRIPT_ON_TRANSITION_1
# 11 "data/maps/UlaUla_Forest_hns/scripts.pory"
	setvar VAR_OBJ_GFX_ID_1, OBJ_EVENT_GFX_SPECIES ( GENGAR )
# 12 "data/maps/UlaUla_Forest_hns/scripts.pory"
	clearflag FLAG_ULAULA_TOTEM_DAY
	return

UlaUla_Forest_hns_MapScripts_MAP_SCRIPT_ON_TRANSITION_1:
# 6 "data/maps/UlaUla_Forest_hns/scripts.pory"
	setvar VAR_OBJ_GFX_ID_1, OBJ_EVENT_GFX_SPECIES ( VESPIQUEN )
# 7 "data/maps/UlaUla_Forest_hns/scripts.pory"
	setflag FLAG_ULAULA_TOTEM_DAY
	return


Alola_Ulaula_Forest_FindItem1::
# 18 "data/maps/UlaUla_Forest_hns/scripts.pory"
	finditem ITEM_MAX_REVIVE, 1
	end


Alola_Ulaula_TotemBattle_Trigger::
# 23 "data/maps/UlaUla_Forest_hns/scripts.pory"
	goto_if_unset FLAG_TRIGGERED_ULAULA_TOTEM, Alola_Ulaula_TotemBattle_Trigger_1
	end

Alola_Ulaula_TotemBattle_Trigger_1:
# 25 "data/maps/UlaUla_Forest_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_AKALA, Alola_Ulaula_TotemBattle_Trigger_7
Alola_Ulaula_TotemBattle_Trigger_5:
	end

Alola_Ulaula_TotemBattle_Trigger_4:
# 27 "data/maps/UlaUla_Forest_hns/scripts.pory"
	lock
# 28 "data/maps/UlaUla_Forest_hns/scripts.pory"
	delay 30
# 29 "data/maps/UlaUla_Forest_hns/scripts.pory"
	setvar VAR_0x8004, 2
# 30 "data/maps/UlaUla_Forest_hns/scripts.pory"
	setvar VAR_0x8005, 6
# 31 "data/maps/UlaUla_Forest_hns/scripts.pory"
	setvar VAR_0x8006, 4
# 32 "data/maps/UlaUla_Forest_hns/scripts.pory"
	setvar VAR_0x8007, 4
# 33 "data/maps/UlaUla_Forest_hns/scripts.pory"
	special ShakeCamera
# 34 "data/maps/UlaUla_Forest_hns/scripts.pory"
	waitstate
# 35 "data/maps/UlaUla_Forest_hns/scripts.pory"
	fadescreenswapbuffers FADE_TO_BLACK
# 36 "data/maps/UlaUla_Forest_hns/scripts.pory"
	delay 30
# 37 "data/maps/UlaUla_Forest_hns/scripts.pory"
	clearflag FLAG_HIDE_ULAULA_TOTEM
# 38 "data/maps/UlaUla_Forest_hns/scripts.pory"
	gettimeofday
# 39 "data/maps/UlaUla_Forest_hns/scripts.pory"
	compare VAR_0x8000, TIME_MORNING
	goto_if_eq Alola_Ulaula_TotemBattle_Trigger_14
# 39 "data/maps/UlaUla_Forest_hns/scripts.pory"
	compare VAR_0x8000, TIME_DAY
	goto_if_eq Alola_Ulaula_TotemBattle_Trigger_14
# 49 "data/maps/UlaUla_Forest_hns/scripts.pory"
	playmoncry SPECIES_GENGAR, 0
# 50 "data/maps/UlaUla_Forest_hns/scripts.pory"
	setvar VAR_OBJ_GFX_ID_1, OBJ_EVENT_GFX_SPECIES ( GENGAR )
# 51 "data/maps/UlaUla_Forest_hns/scripts.pory"
	clearflag FLAG_ULAULA_TOTEM_DAY
# 52 "data/maps/UlaUla_Forest_hns/scripts.pory"
	addobject Ulaula_Totem
# 53 "data/maps/UlaUla_Forest_hns/scripts.pory"
	waitmoncry
Alola_Ulaula_TotemBattle_Trigger_13:
# 55 "data/maps/UlaUla_Forest_hns/scripts.pory"
	special DrawWholeMapView
# 56 "data/maps/UlaUla_Forest_hns/scripts.pory"
	delay 30
# 57 "data/maps/UlaUla_Forest_hns/scripts.pory"
	fadescreenswapbuffers FADE_FROM_BLACK
# 58 "data/maps/UlaUla_Forest_hns/scripts.pory"
	delay 30
# 59 "data/maps/UlaUla_Forest_hns/scripts.pory"
	gettimeofday
# 60 "data/maps/UlaUla_Forest_hns/scripts.pory"
	compare VAR_0x8000, TIME_MORNING
	goto_if_eq Alola_Ulaula_TotemBattle_Trigger_20
# 60 "data/maps/UlaUla_Forest_hns/scripts.pory"
	compare VAR_0x8000, TIME_DAY
	goto_if_eq Alola_Ulaula_TotemBattle_Trigger_20
# 69 "data/maps/UlaUla_Forest_hns/scripts.pory"
	playmoncry SPECIES_GENGAR, 0
# 70 "data/maps/UlaUla_Forest_hns/scripts.pory"
	applymovement Ulaula_Totem, Alola_Ulaula_TotemBattle_Trigger_Movement_0
# 71 "data/maps/UlaUla_Forest_hns/scripts.pory"
	waitmovement 0
# 72 "data/maps/UlaUla_Forest_hns/scripts.pory"
	waitmoncry
Alola_Ulaula_TotemBattle_Trigger_19:
# 74 "data/maps/UlaUla_Forest_hns/scripts.pory"
	setflag FLAG_TRIGGERED_ULAULA_TOTEM
# 75 "data/maps/UlaUla_Forest_hns/scripts.pory"
	release
	end

Alola_Ulaula_TotemBattle_Trigger_6:
# 25 "data/maps/UlaUla_Forest_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_PONI, Alola_Ulaula_TotemBattle_Trigger_10
	goto Alola_Ulaula_TotemBattle_Trigger_5

Alola_Ulaula_TotemBattle_Trigger_7:
# 25 "data/maps/UlaUla_Forest_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_ULAULA, Alola_Ulaula_TotemBattle_Trigger_6
	goto Alola_Ulaula_TotemBattle_Trigger_5

Alola_Ulaula_TotemBattle_Trigger_10:
# 25 "data/maps/UlaUla_Forest_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_MELEMELE, Alola_Ulaula_TotemBattle_Trigger_4
	goto Alola_Ulaula_TotemBattle_Trigger_5

Alola_Ulaula_TotemBattle_Trigger_14:
# 41 "data/maps/UlaUla_Forest_hns/scripts.pory"
	playmoncry SPECIES_VESPIQUEN, 0
# 42 "data/maps/UlaUla_Forest_hns/scripts.pory"
	setvar VAR_OBJ_GFX_ID_1, OBJ_EVENT_GFX_SPECIES ( VESPIQUEN )
# 43 "data/maps/UlaUla_Forest_hns/scripts.pory"
	setflag FLAG_ULAULA_TOTEM_DAY
# 44 "data/maps/UlaUla_Forest_hns/scripts.pory"
	addobject Ulaula_Totem
# 45 "data/maps/UlaUla_Forest_hns/scripts.pory"
	waitmoncry
	goto Alola_Ulaula_TotemBattle_Trigger_13

Alola_Ulaula_TotemBattle_Trigger_20:
# 62 "data/maps/UlaUla_Forest_hns/scripts.pory"
	playmoncry SPECIES_VESPIQUEN, 0
# 63 "data/maps/UlaUla_Forest_hns/scripts.pory"
	applymovement Ulaula_Totem, Alola_Ulaula_TotemBattle_Trigger_Movement_0
# 64 "data/maps/UlaUla_Forest_hns/scripts.pory"
	waitmovement 0
# 65 "data/maps/UlaUla_Forest_hns/scripts.pory"
	waitmoncry
	goto Alola_Ulaula_TotemBattle_Trigger_19


Alola_Ulaula_TotemBattle::
# 90 "data/maps/UlaUla_Forest_hns/scripts.pory"
	lock
# 91 "data/maps/UlaUla_Forest_hns/scripts.pory"
	faceplayer
# 92 "data/maps/UlaUla_Forest_hns/scripts.pory"
	goto_if_set FLAG_ULAULA_TOTEM_DAY, Alola_Ulaula_TotemBattle_1
# 127 "data/maps/UlaUla_Forest_hns/scripts.pory"
	playmoncry SPECIES_GENGAR, 0
# 128 "data/maps/UlaUla_Forest_hns/scripts.pory"
	msgbox Alola_Ulaula_TotemBattle_Text_2, MSGBOX_AUTOCLOSE
# 129 "data/maps/UlaUla_Forest_hns/scripts.pory"
	waitmoncry
# 130 "data/maps/UlaUla_Forest_hns/scripts.pory"
	setwildbattle SPECIES_HAUNTER, 60, ITEM_NONE, SPECIES_GENGAR, 60, ITEM_LUM_BERRY
# 131 "data/maps/UlaUla_Forest_hns/scripts.pory"
	settotemboost B_POSITION_OPPONENT_RIGHT, 1, 1, 1, 1, 1, 1
# 132 "data/maps/UlaUla_Forest_hns/scripts.pory"
	setflag FLAG_NO_WILD_CATCHING
# 133 "data/maps/UlaUla_Forest_hns/scripts.pory"
	setflag FLAG_NO_WILD_RUNNING
# 134 "data/maps/UlaUla_Forest_hns/scripts.pory"
	setflag FLAG_SMART_WILD_AI
# 135 "data/maps/UlaUla_Forest_hns/scripts.pory"
	dowildbattle
# 136 "data/maps/UlaUla_Forest_hns/scripts.pory"
	specialvar VAR_RESULT, GetBattleOutcome
# 137 "data/maps/UlaUla_Forest_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq Alola_Ulaula_TotemBattle_8
# 150 "data/maps/UlaUla_Forest_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_LOST
	goto_if_eq Alola_Ulaula_TotemBattle_12
	return

Alola_Ulaula_TotemBattle_1:
# 94 "data/maps/UlaUla_Forest_hns/scripts.pory"
	playmoncry SPECIES_VESPIQUEN, 0
# 95 "data/maps/UlaUla_Forest_hns/scripts.pory"
	msgbox Alola_Ulaula_TotemBattle_Text_0, MSGBOX_AUTOCLOSE
# 96 "data/maps/UlaUla_Forest_hns/scripts.pory"
	waitmoncry
# 98 "data/maps/UlaUla_Forest_hns/scripts.pory"
	setwildbattle SPECIES_COMBEE, 60, ITEM_NONE, SPECIES_VESPIQUEN, 60, ITEM_OCCA_BERRY
# 99 "data/maps/UlaUla_Forest_hns/scripts.pory"
	settotemboost B_POSITION_OPPONENT_RIGHT, 1, 1, 1, 1, 1, 1
# 100 "data/maps/UlaUla_Forest_hns/scripts.pory"
	setflag FLAG_NO_WILD_CATCHING
# 101 "data/maps/UlaUla_Forest_hns/scripts.pory"
	setflag FLAG_NO_WILD_RUNNING
# 102 "data/maps/UlaUla_Forest_hns/scripts.pory"
	setflag FLAG_SMART_WILD_AI
# 103 "data/maps/UlaUla_Forest_hns/scripts.pory"
	dowildbattle
# 104 "data/maps/UlaUla_Forest_hns/scripts.pory"
	specialvar VAR_RESULT, GetBattleOutcome
# 105 "data/maps/UlaUla_Forest_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq Alola_Ulaula_TotemBattle_5
# 117 "data/maps/UlaUla_Forest_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_LOST
	goto_if_eq Alola_Ulaula_TotemBattle_10
	return

Alola_Ulaula_TotemBattle_5:
# 106 "data/maps/UlaUla_Forest_hns/scripts.pory"
	setflag FLAG_HIDE_ULAULA_TOTEM
# 107 "data/maps/UlaUla_Forest_hns/scripts.pory"
	setflag FLAG_DEFEATED_ULAULA_TOTEM
# 108 "data/maps/UlaUla_Forest_hns/scripts.pory"
	removeobject Ulaula_Totem
# 109 "data/maps/UlaUla_Forest_hns/scripts.pory"
	msgbox Alola_Ulaula_TotemBattle_Text_1, MSGBOX_AUTOCLOSE
# 111 "data/maps/UlaUla_Forest_hns/scripts.pory"
	clearflag FLAG_NO_WILD_CATCHING
# 112 "data/maps/UlaUla_Forest_hns/scripts.pory"
	clearflag FLAG_NO_WILD_RUNNING
# 113 "data/maps/UlaUla_Forest_hns/scripts.pory"
	clearflag FLAG_SMART_WILD_AI
# 114 "data/maps/UlaUla_Forest_hns/scripts.pory"
	release
	end

Alola_Ulaula_TotemBattle_8:
# 139 "data/maps/UlaUla_Forest_hns/scripts.pory"
	setflag FLAG_HIDE_ULAULA_TOTEM
# 140 "data/maps/UlaUla_Forest_hns/scripts.pory"
	setflag FLAG_DEFEATED_ULAULA_TOTEM
# 141 "data/maps/UlaUla_Forest_hns/scripts.pory"
	removeobject Ulaula_Totem
# 142 "data/maps/UlaUla_Forest_hns/scripts.pory"
	msgbox Alola_Ulaula_TotemBattle_Text_3, MSGBOX_AUTOCLOSE
# 144 "data/maps/UlaUla_Forest_hns/scripts.pory"
	clearflag FLAG_NO_WILD_CATCHING
# 145 "data/maps/UlaUla_Forest_hns/scripts.pory"
	clearflag FLAG_NO_WILD_RUNNING
# 146 "data/maps/UlaUla_Forest_hns/scripts.pory"
	clearflag FLAG_SMART_WILD_AI
# 147 "data/maps/UlaUla_Forest_hns/scripts.pory"
	release
	end

Alola_Ulaula_TotemBattle_10:
# 118 "data/maps/UlaUla_Forest_hns/scripts.pory"
	clearflag FLAG_NO_WILD_CATCHING
# 119 "data/maps/UlaUla_Forest_hns/scripts.pory"
	clearflag FLAG_NO_WILD_RUNNING
# 120 "data/maps/UlaUla_Forest_hns/scripts.pory"
	clearflag FLAG_SMART_WILD_AI
# 121 "data/maps/UlaUla_Forest_hns/scripts.pory"
	release
	end

Alola_Ulaula_TotemBattle_12:
# 151 "data/maps/UlaUla_Forest_hns/scripts.pory"
	clearflag FLAG_NO_WILD_CATCHING
# 152 "data/maps/UlaUla_Forest_hns/scripts.pory"
	clearflag FLAG_NO_WILD_RUNNING
# 153 "data/maps/UlaUla_Forest_hns/scripts.pory"
	clearflag FLAG_SMART_WILD_AI
# 154 "data/maps/UlaUla_Forest_hns/scripts.pory"
	release
	end


Alola_Ulaula_Totem_sign::
# 162 "data/maps/UlaUla_Forest_hns/scripts.pory"
	lock
# 163 "data/maps/UlaUla_Forest_hns/scripts.pory"
	goto_if_set FLAG_BATTLED_TAPU_FINI, Alola_Ulaula_Totem_sign_5
Alola_Ulaula_Totem_sign_3:
# 204 "data/maps/UlaUla_Forest_hns/scripts.pory"
	msgbox Alola_Ulaula_Totem_sign_Text_6, MSGBOX_AUTOCLOSE
# 207 "data/maps/UlaUla_Forest_hns/scripts.pory"
	release
	end

Alola_Ulaula_Totem_sign_2:
# 165 "data/maps/UlaUla_Forest_hns/scripts.pory"
	msgbox Alola_Ulaula_Totem_sign_Text_0
# 170 "data/maps/UlaUla_Forest_hns/scripts.pory"
	dynmultichoice 20, 4, FALSE, 4, 0, DYN_MULTICHOICE_CB_NONE, Alola_Ulaula_Totem_sign_Text_1, Alola_Ulaula_Totem_sign_Text_2, Alola_Ulaula_Totem_sign_Text_3, Alola_Ulaula_Totem_sign_Text_4, Alola_Ulaula_Totem_sign_Text_5
# 171 "data/maps/UlaUla_Forest_hns/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq Alola_Ulaula_Totem_sign_12
# 177 "data/maps/UlaUla_Forest_hns/scripts.pory"
	compare VAR_RESULT, 1
	goto_if_eq Alola_Ulaula_Totem_sign_15
# 183 "data/maps/UlaUla_Forest_hns/scripts.pory"
	compare VAR_RESULT, 2
	goto_if_eq Alola_Ulaula_Totem_sign_18
# 189 "data/maps/UlaUla_Forest_hns/scripts.pory"
	compare VAR_RESULT, 3
	goto_if_eq Alola_Ulaula_Totem_sign_20
# 197 "data/maps/UlaUla_Forest_hns/scripts.pory"
	release
	end

Alola_Ulaula_Totem_sign_4:
# 163 "data/maps/UlaUla_Forest_hns/scripts.pory"
	goto_if_set FLAG_BATTLED_TAPU_BULU, Alola_Ulaula_Totem_sign_8
	goto Alola_Ulaula_Totem_sign_3

Alola_Ulaula_Totem_sign_5:
# 163 "data/maps/UlaUla_Forest_hns/scripts.pory"
	goto_if_set FLAG_BATTLED_TAPU_KOKO, Alola_Ulaula_Totem_sign_4
	goto Alola_Ulaula_Totem_sign_3

Alola_Ulaula_Totem_sign_8:
# 163 "data/maps/UlaUla_Forest_hns/scripts.pory"
	goto_if_set FLAG_BATTLED_TAPU_LELE, Alola_Ulaula_Totem_sign_2
	goto Alola_Ulaula_Totem_sign_3

Alola_Ulaula_Totem_sign_12:
# 173 "data/maps/UlaUla_Forest_hns/scripts.pory"
	warp MAP_ALOLA_ISLAND_MELEMELE_HNS, 34, 26
# 174 "data/maps/UlaUla_Forest_hns/scripts.pory"
	waitstate
	end

Alola_Ulaula_Totem_sign_15:
# 179 "data/maps/UlaUla_Forest_hns/scripts.pory"
	warp MAP_ALOLA_ISLAND_RIGHT_HNS, 9, 10
# 180 "data/maps/UlaUla_Forest_hns/scripts.pory"
	waitstate
	end

Alola_Ulaula_Totem_sign_18:
# 185 "data/maps/UlaUla_Forest_hns/scripts.pory"
	warp MAP_ULA_ULA_FOREST_HNS, 16, 5
# 186 "data/maps/UlaUla_Forest_hns/scripts.pory"
	waitstate
	end

Alola_Ulaula_Totem_sign_20:
# 191 "data/maps/UlaUla_Forest_hns/scripts.pory"
	warp MAP_ALOLA_ISLAND_HNS, 13, 8
# 192 "data/maps/UlaUla_Forest_hns/scripts.pory"
	waitstate
	end


Alola_Ulaula_BattleVsTapuBulu::
# 212 "data/maps/UlaUla_Forest_hns/scripts.pory"
	lock
# 213 "data/maps/UlaUla_Forest_hns/scripts.pory"
	faceplayer
# 214 "data/maps/UlaUla_Forest_hns/scripts.pory"
	playmoncry SPECIES_TAPU_BULU, CRY_MODE_ENCOUNTER
# 215 "data/maps/UlaUla_Forest_hns/scripts.pory"
	msgbox Alola_Ulaula_BattleVsTapuBulu_Text_0
# 216 "data/maps/UlaUla_Forest_hns/scripts.pory"
	waitmoncry
# 217 "data/maps/UlaUla_Forest_hns/scripts.pory"
	seteventmon SPECIES_TAPU_BULU, 60
# 218 "data/maps/UlaUla_Forest_hns/scripts.pory"
	special BattleSetup_StartLegendaryBattle
# 219 "data/maps/UlaUla_Forest_hns/scripts.pory"
	waitstate
# 220 "data/maps/UlaUla_Forest_hns/scripts.pory"
	specialvar VAR_RESULT, GetBattleOutcome
# 221 "data/maps/UlaUla_Forest_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_CAUGHT
	goto_if_eq Alola_Ulaula_BattleVsTapuBulu_2
# 228 "data/maps/UlaUla_Forest_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq Alola_Ulaula_BattleVsTapuBulu_3
# 236 "data/maps/UlaUla_Forest_hns/scripts.pory"
	release
	end

# 239 "data/maps/UlaUla_Forest_hns/scripts.pory"
	release
	end

Alola_Ulaula_BattleVsTapuBulu_2:
# 222 "data/maps/UlaUla_Forest_hns/scripts.pory"
	setflag FLAG_HIDE_TAPU_BULU
# 223 "data/maps/UlaUla_Forest_hns/scripts.pory"
	setflag FLAG_BATTLED_TAPU_BULU
# 224 "data/maps/UlaUla_Forest_hns/scripts.pory"
	removeobject Ulaula_Tapu
# 225 "data/maps/UlaUla_Forest_hns/scripts.pory"
	release
	end

Alola_Ulaula_BattleVsTapuBulu_3:
# 229 "data/maps/UlaUla_Forest_hns/scripts.pory"
	setflag FLAG_HIDE_TAPU_BULU
# 230 "data/maps/UlaUla_Forest_hns/scripts.pory"
	setflag FLAG_BATTLED_TAPU_BULU
# 231 "data/maps/UlaUla_Forest_hns/scripts.pory"
	removeobject Ulaula_Tapu
# 232 "data/maps/UlaUla_Forest_hns/scripts.pory"
	release
	end


# 63 "data/maps/UlaUla_Forest_hns/scripts.pory"
Alola_Ulaula_TotemBattle_Trigger_Movement_0:
# 63 "data/maps/UlaUla_Forest_hns/scripts.pory"
	walk_in_place_down
# 63 "data/maps/UlaUla_Forest_hns/scripts.pory"
	walk_in_place_down
	step_end

Alola_Ulaula_TotemBattle_Text_0:
# 95 "data/maps/UlaUla_Forest_hns/scripts.pory"
	.string "Bee-beep!$"

Alola_Ulaula_TotemBattle_Text_1:
# 109 "data/maps/UlaUla_Forest_hns/scripts.pory"
	.string "Totem Vespiquen was defeated!\n"
	.string "It scampered off somewhere…$"

Alola_Ulaula_TotemBattle_Text_2:
# 128 "data/maps/UlaUla_Forest_hns/scripts.pory"
	.string "Graah!$"

Alola_Ulaula_TotemBattle_Text_3:
# 142 "data/maps/UlaUla_Forest_hns/scripts.pory"
	.string "Totem Gengar was defeated!\n"
	.string "It scampered off somewhere…$"

Alola_Ulaula_Totem_sign_Text_0:
# 165 "data/maps/UlaUla_Forest_hns/scripts.pory"
	.string "The totem is emanating a strong\n"
	.string "energy…\p"
	.string "Touch the totem to teleport to another\n"
	.string "Isle?$"

Alola_Ulaula_Totem_sign_Text_1:
# 170 "data/maps/UlaUla_Forest_hns/scripts.pory"
	.string "Melemele Isle$"

Alola_Ulaula_Totem_sign_Text_2:
# 170 "data/maps/UlaUla_Forest_hns/scripts.pory"
	.string "Akala Isle$"

Alola_Ulaula_Totem_sign_Text_3:
# 170 "data/maps/UlaUla_Forest_hns/scripts.pory"
	.string "Ula'ula Isle$"

Alola_Ulaula_Totem_sign_Text_4:
# 170 "data/maps/UlaUla_Forest_hns/scripts.pory"
	.string "Poni Isle$"

Alola_Ulaula_Totem_sign_Text_5:
# 170 "data/maps/UlaUla_Forest_hns/scripts.pory"
	.string "Cancel$"

Alola_Ulaula_Totem_sign_Text_6:
# 204 "data/maps/UlaUla_Forest_hns/scripts.pory"
	.string "A strange totem stands here,\n"
	.string "power is emanating from it…$"

Alola_Ulaula_BattleVsTapuBulu_Text_0:
# 215 "data/maps/UlaUla_Forest_hns/scripts.pory"
	.string "Bu-Bulu!$"
