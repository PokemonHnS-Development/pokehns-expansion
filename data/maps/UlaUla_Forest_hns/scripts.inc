UlaUla_Forest_hns_MapScripts::
	.byte 0


Alola_Ulaula_Forest_FindItem1::
# 4 "data/maps/UlaUla_Forest_hns/scripts.pory"
	finditem ITEM_MAX_REVIVE, 1
	end


Alola_Ulaula_TotemBattle_Trigger::
# 9 "data/maps/UlaUla_Forest_hns/scripts.pory"
	goto_if_unset FLAG_TRIGGERED_ULAULA_TOTEM, Alola_Ulaula_TotemBattle_Trigger_1
	end

Alola_Ulaula_TotemBattle_Trigger_1:
# 11 "data/maps/UlaUla_Forest_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_AKALA, Alola_Ulaula_TotemBattle_Trigger_7
Alola_Ulaula_TotemBattle_Trigger_5:
	end

Alola_Ulaula_TotemBattle_Trigger_4:
# 13 "data/maps/UlaUla_Forest_hns/scripts.pory"
	lock
# 14 "data/maps/UlaUla_Forest_hns/scripts.pory"
	delay 30
# 15 "data/maps/UlaUla_Forest_hns/scripts.pory"
	setvar VAR_0x8004, 2
# 16 "data/maps/UlaUla_Forest_hns/scripts.pory"
	setvar VAR_0x8005, 6
# 17 "data/maps/UlaUla_Forest_hns/scripts.pory"
	setvar VAR_0x8006, 4
# 18 "data/maps/UlaUla_Forest_hns/scripts.pory"
	setvar VAR_0x8007, 4
# 19 "data/maps/UlaUla_Forest_hns/scripts.pory"
	special ShakeCamera
# 20 "data/maps/UlaUla_Forest_hns/scripts.pory"
	waitstate
# 21 "data/maps/UlaUla_Forest_hns/scripts.pory"
	fadescreenswapbuffers FADE_TO_BLACK
# 22 "data/maps/UlaUla_Forest_hns/scripts.pory"
	delay 30
# 23 "data/maps/UlaUla_Forest_hns/scripts.pory"
	clearflag FLAG_HIDE_ULAULA_TOTEM
# 24 "data/maps/UlaUla_Forest_hns/scripts.pory"
	gettimeofday
# 25 "data/maps/UlaUla_Forest_hns/scripts.pory"
	compare VAR_0x8000, TIME_MORNING
	goto_if_eq Alola_Ulaula_TotemBattle_Trigger_14
# 25 "data/maps/UlaUla_Forest_hns/scripts.pory"
	compare VAR_0x8000, TIME_DAY
	goto_if_eq Alola_Ulaula_TotemBattle_Trigger_14
# 34 "data/maps/UlaUla_Forest_hns/scripts.pory"
	playmoncry SPECIES_MIMIKYU, 0
# 35 "data/maps/UlaUla_Forest_hns/scripts.pory"
	setvar VAR_OBJ_GFX_ID_1, OBJ_EVENT_GFX_SPECIES ( MIMIKYU )
# 36 "data/maps/UlaUla_Forest_hns/scripts.pory"
	addobject Ulaula_Totem
# 37 "data/maps/UlaUla_Forest_hns/scripts.pory"
	waitmoncry
Alola_Ulaula_TotemBattle_Trigger_13:
# 39 "data/maps/UlaUla_Forest_hns/scripts.pory"
	special DrawWholeMapView
# 40 "data/maps/UlaUla_Forest_hns/scripts.pory"
	delay 30
# 41 "data/maps/UlaUla_Forest_hns/scripts.pory"
	fadescreenswapbuffers FADE_FROM_BLACK
# 42 "data/maps/UlaUla_Forest_hns/scripts.pory"
	delay 30
# 43 "data/maps/UlaUla_Forest_hns/scripts.pory"
	gettimeofday
# 44 "data/maps/UlaUla_Forest_hns/scripts.pory"
	compare VAR_0x8000, TIME_MORNING
	goto_if_eq Alola_Ulaula_TotemBattle_Trigger_20
# 44 "data/maps/UlaUla_Forest_hns/scripts.pory"
	compare VAR_0x8000, TIME_DAY
	goto_if_eq Alola_Ulaula_TotemBattle_Trigger_20
# 53 "data/maps/UlaUla_Forest_hns/scripts.pory"
	playmoncry SPECIES_MIMIKYU, 0
# 54 "data/maps/UlaUla_Forest_hns/scripts.pory"
	applymovement Ulaula_Totem, Alola_Ulaula_TotemBattle_Trigger_Movement_0
# 55 "data/maps/UlaUla_Forest_hns/scripts.pory"
	waitmovement 0
# 56 "data/maps/UlaUla_Forest_hns/scripts.pory"
	waitmoncry
Alola_Ulaula_TotemBattle_Trigger_19:
# 58 "data/maps/UlaUla_Forest_hns/scripts.pory"
	setflag FLAG_TRIGGERED_ULAULA_TOTEM
# 59 "data/maps/UlaUla_Forest_hns/scripts.pory"
	release
	end

Alola_Ulaula_TotemBattle_Trigger_6:
# 11 "data/maps/UlaUla_Forest_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_PONI, Alola_Ulaula_TotemBattle_Trigger_10
	goto Alola_Ulaula_TotemBattle_Trigger_5

Alola_Ulaula_TotemBattle_Trigger_7:
# 11 "data/maps/UlaUla_Forest_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_ULAULA, Alola_Ulaula_TotemBattle_Trigger_6
	goto Alola_Ulaula_TotemBattle_Trigger_5

Alola_Ulaula_TotemBattle_Trigger_10:
# 11 "data/maps/UlaUla_Forest_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_MELEMELE, Alola_Ulaula_TotemBattle_Trigger_4
	goto Alola_Ulaula_TotemBattle_Trigger_5

Alola_Ulaula_TotemBattle_Trigger_14:
# 27 "data/maps/UlaUla_Forest_hns/scripts.pory"
	playmoncry SPECIES_VIKAVOLT, 0
# 28 "data/maps/UlaUla_Forest_hns/scripts.pory"
	setvar VAR_OBJ_GFX_ID_1, OBJ_EVENT_GFX_SPECIES ( VIKAVOLT )
# 29 "data/maps/UlaUla_Forest_hns/scripts.pory"
	addobject Ulaula_Totem
# 30 "data/maps/UlaUla_Forest_hns/scripts.pory"
	waitmoncry
	goto Alola_Ulaula_TotemBattle_Trigger_13

Alola_Ulaula_TotemBattle_Trigger_20:
# 46 "data/maps/UlaUla_Forest_hns/scripts.pory"
	playmoncry SPECIES_VIKAVOLT, 0
# 47 "data/maps/UlaUla_Forest_hns/scripts.pory"
	applymovement Ulaula_Totem, Alola_Ulaula_TotemBattle_Trigger_Movement_0
# 48 "data/maps/UlaUla_Forest_hns/scripts.pory"
	waitmovement 0
# 49 "data/maps/UlaUla_Forest_hns/scripts.pory"
	waitmoncry
	goto Alola_Ulaula_TotemBattle_Trigger_19


Alola_Ulaula_TotemBattle::
# 74 "data/maps/UlaUla_Forest_hns/scripts.pory"
	lock
# 75 "data/maps/UlaUla_Forest_hns/scripts.pory"
	faceplayer
# 76 "data/maps/UlaUla_Forest_hns/scripts.pory"
	gettimeofday
# 77 "data/maps/UlaUla_Forest_hns/scripts.pory"
	compare VAR_0x8000, TIME_MORNING
	goto_if_eq Alola_Ulaula_TotemBattle_1
# 77 "data/maps/UlaUla_Forest_hns/scripts.pory"
	compare VAR_0x8000, TIME_DAY
	goto_if_eq Alola_Ulaula_TotemBattle_1
# 112 "data/maps/UlaUla_Forest_hns/scripts.pory"
	playmoncry SPECIES_MIMIKYU, 0
# 113 "data/maps/UlaUla_Forest_hns/scripts.pory"
	msgbox Alola_Ulaula_TotemBattle_Text_2, MSGBOX_AUTOCLOSE
# 114 "data/maps/UlaUla_Forest_hns/scripts.pory"
	waitmoncry
# 115 "data/maps/UlaUla_Forest_hns/scripts.pory"
	setwildbattle SPECIES_SKARMORY, 60, ITEM_NONE, SPECIES_MIMIKYU_TOTEM, 60, ITEM_LUM_BERRY
# 116 "data/maps/UlaUla_Forest_hns/scripts.pory"
	settotemboost B_POSITION_OPPONENT_RIGHT, 1, 1, 1, 1, 1, 1
# 117 "data/maps/UlaUla_Forest_hns/scripts.pory"
	setflag FLAG_NO_WILD_CATCHING
# 118 "data/maps/UlaUla_Forest_hns/scripts.pory"
	setflag FLAG_NO_WILD_RUNNING
# 119 "data/maps/UlaUla_Forest_hns/scripts.pory"
	setflag FLAG_SMART_WILD_AI
# 120 "data/maps/UlaUla_Forest_hns/scripts.pory"
	dowildbattle
# 121 "data/maps/UlaUla_Forest_hns/scripts.pory"
	specialvar VAR_RESULT, GetBattleOutcome
# 122 "data/maps/UlaUla_Forest_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq Alola_Ulaula_TotemBattle_10
# 135 "data/maps/UlaUla_Forest_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_LOST
	goto_if_eq Alola_Ulaula_TotemBattle_14
	return

Alola_Ulaula_TotemBattle_1:
# 79 "data/maps/UlaUla_Forest_hns/scripts.pory"
	playmoncry SPECIES_VIKAVOLT, 0
# 80 "data/maps/UlaUla_Forest_hns/scripts.pory"
	msgbox Alola_Ulaula_TotemBattle_Text_0, MSGBOX_AUTOCLOSE
# 81 "data/maps/UlaUla_Forest_hns/scripts.pory"
	waitmoncry
# 83 "data/maps/UlaUla_Forest_hns/scripts.pory"
	setwildbattle SPECIES_CHARJABUG, 60, ITEM_NONE, SPECIES_VIKAVOLT_TOTEM, 60, ITEM_OCCA_BERRY
# 84 "data/maps/UlaUla_Forest_hns/scripts.pory"
	settotemboost B_POSITION_OPPONENT_RIGHT, 1, 1, 1, 1, 1, 1
# 85 "data/maps/UlaUla_Forest_hns/scripts.pory"
	setflag FLAG_NO_WILD_CATCHING
# 86 "data/maps/UlaUla_Forest_hns/scripts.pory"
	setflag FLAG_NO_WILD_RUNNING
# 87 "data/maps/UlaUla_Forest_hns/scripts.pory"
	setflag FLAG_SMART_WILD_AI
# 88 "data/maps/UlaUla_Forest_hns/scripts.pory"
	dowildbattle
# 89 "data/maps/UlaUla_Forest_hns/scripts.pory"
	specialvar VAR_RESULT, GetBattleOutcome
# 90 "data/maps/UlaUla_Forest_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq Alola_Ulaula_TotemBattle_7
# 102 "data/maps/UlaUla_Forest_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_LOST
	goto_if_eq Alola_Ulaula_TotemBattle_12
	return

Alola_Ulaula_TotemBattle_7:
# 91 "data/maps/UlaUla_Forest_hns/scripts.pory"
	setflag FLAG_HIDE_ULAULA_TOTEM
# 92 "data/maps/UlaUla_Forest_hns/scripts.pory"
	setflag FLAG_DEFEATED_ULAULA_TOTEM
# 93 "data/maps/UlaUla_Forest_hns/scripts.pory"
	removeobject Ulaula_Totem
# 94 "data/maps/UlaUla_Forest_hns/scripts.pory"
	msgbox Alola_Ulaula_TotemBattle_Text_1, MSGBOX_AUTOCLOSE
# 96 "data/maps/UlaUla_Forest_hns/scripts.pory"
	clearflag FLAG_NO_WILD_CATCHING
# 97 "data/maps/UlaUla_Forest_hns/scripts.pory"
	clearflag FLAG_NO_WILD_RUNNING
# 98 "data/maps/UlaUla_Forest_hns/scripts.pory"
	clearflag FLAG_SMART_WILD_AI
# 99 "data/maps/UlaUla_Forest_hns/scripts.pory"
	release
	end

Alola_Ulaula_TotemBattle_10:
# 124 "data/maps/UlaUla_Forest_hns/scripts.pory"
	setflag FLAG_HIDE_ULAULA_TOTEM
# 125 "data/maps/UlaUla_Forest_hns/scripts.pory"
	setflag FLAG_DEFEATED_ULAULA_TOTEM
# 126 "data/maps/UlaUla_Forest_hns/scripts.pory"
	removeobject Ulaula_Totem
# 127 "data/maps/UlaUla_Forest_hns/scripts.pory"
	msgbox Alola_Ulaula_TotemBattle_Text_3, MSGBOX_AUTOCLOSE
# 129 "data/maps/UlaUla_Forest_hns/scripts.pory"
	clearflag FLAG_NO_WILD_CATCHING
# 130 "data/maps/UlaUla_Forest_hns/scripts.pory"
	clearflag FLAG_NO_WILD_RUNNING
# 131 "data/maps/UlaUla_Forest_hns/scripts.pory"
	clearflag FLAG_SMART_WILD_AI
# 132 "data/maps/UlaUla_Forest_hns/scripts.pory"
	release
	end

Alola_Ulaula_TotemBattle_12:
# 103 "data/maps/UlaUla_Forest_hns/scripts.pory"
	clearflag FLAG_NO_WILD_CATCHING
# 104 "data/maps/UlaUla_Forest_hns/scripts.pory"
	clearflag FLAG_NO_WILD_RUNNING
# 105 "data/maps/UlaUla_Forest_hns/scripts.pory"
	clearflag FLAG_SMART_WILD_AI
# 106 "data/maps/UlaUla_Forest_hns/scripts.pory"
	release
	end

Alola_Ulaula_TotemBattle_14:
# 136 "data/maps/UlaUla_Forest_hns/scripts.pory"
	clearflag FLAG_NO_WILD_CATCHING
# 137 "data/maps/UlaUla_Forest_hns/scripts.pory"
	clearflag FLAG_NO_WILD_RUNNING
# 138 "data/maps/UlaUla_Forest_hns/scripts.pory"
	clearflag FLAG_SMART_WILD_AI
# 139 "data/maps/UlaUla_Forest_hns/scripts.pory"
	release
	end


Alola_Ulaula_Totem_sign::
# 147 "data/maps/UlaUla_Forest_hns/scripts.pory"
	lock
# 148 "data/maps/UlaUla_Forest_hns/scripts.pory"
	goto_if_set FLAG_BATTLED_TAPU_FINI, Alola_Ulaula_Totem_sign_5
Alola_Ulaula_Totem_sign_3:
# 189 "data/maps/UlaUla_Forest_hns/scripts.pory"
	msgbox Alola_Ulaula_Totem_sign_Text_6, MSGBOX_AUTOCLOSE
# 192 "data/maps/UlaUla_Forest_hns/scripts.pory"
	release
	end

Alola_Ulaula_Totem_sign_2:
# 150 "data/maps/UlaUla_Forest_hns/scripts.pory"
	msgbox Alola_Ulaula_Totem_sign_Text_0
# 155 "data/maps/UlaUla_Forest_hns/scripts.pory"
	dynmultichoice 20, 4, FALSE, 4, 0, DYN_MULTICHOICE_CB_NONE, Alola_Ulaula_Totem_sign_Text_1, Alola_Ulaula_Totem_sign_Text_2, Alola_Ulaula_Totem_sign_Text_3, Alola_Ulaula_Totem_sign_Text_4, Alola_Ulaula_Totem_sign_Text_5
# 156 "data/maps/UlaUla_Forest_hns/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq Alola_Ulaula_Totem_sign_12
# 162 "data/maps/UlaUla_Forest_hns/scripts.pory"
	compare VAR_RESULT, 1
	goto_if_eq Alola_Ulaula_Totem_sign_15
# 168 "data/maps/UlaUla_Forest_hns/scripts.pory"
	compare VAR_RESULT, 2
	goto_if_eq Alola_Ulaula_Totem_sign_18
# 174 "data/maps/UlaUla_Forest_hns/scripts.pory"
	compare VAR_RESULT, 3
	goto_if_eq Alola_Ulaula_Totem_sign_20
# 182 "data/maps/UlaUla_Forest_hns/scripts.pory"
	release
	end

Alola_Ulaula_Totem_sign_4:
# 148 "data/maps/UlaUla_Forest_hns/scripts.pory"
	goto_if_set FLAG_BATTLED_TAPU_BULU, Alola_Ulaula_Totem_sign_8
	goto Alola_Ulaula_Totem_sign_3

Alola_Ulaula_Totem_sign_5:
# 148 "data/maps/UlaUla_Forest_hns/scripts.pory"
	goto_if_set FLAG_BATTLED_TAPU_KOKO, Alola_Ulaula_Totem_sign_4
	goto Alola_Ulaula_Totem_sign_3

Alola_Ulaula_Totem_sign_8:
# 148 "data/maps/UlaUla_Forest_hns/scripts.pory"
	goto_if_set FLAG_BATTLED_TAPU_LELE, Alola_Ulaula_Totem_sign_2
	goto Alola_Ulaula_Totem_sign_3

Alola_Ulaula_Totem_sign_12:
# 158 "data/maps/UlaUla_Forest_hns/scripts.pory"
	warp MAP_ALOLA_ISLAND_MELEMELE_HNS, 34, 26
# 159 "data/maps/UlaUla_Forest_hns/scripts.pory"
	waitstate
	end

Alola_Ulaula_Totem_sign_15:
# 164 "data/maps/UlaUla_Forest_hns/scripts.pory"
	warp MAP_ALOLA_ISLAND_RIGHT_HNS, 9, 10
# 165 "data/maps/UlaUla_Forest_hns/scripts.pory"
	waitstate
	end

Alola_Ulaula_Totem_sign_18:
# 170 "data/maps/UlaUla_Forest_hns/scripts.pory"
	warp MAP_ULA_ULA_FOREST_HNS, 16, 5
# 171 "data/maps/UlaUla_Forest_hns/scripts.pory"
	waitstate
	end

Alola_Ulaula_Totem_sign_20:
# 176 "data/maps/UlaUla_Forest_hns/scripts.pory"
	warp MAP_ALOLA_ISLAND_HNS, 13, 8
# 177 "data/maps/UlaUla_Forest_hns/scripts.pory"
	waitstate
	end


Alola_Ulaula_BattleVsTapuBulu::
# 197 "data/maps/UlaUla_Forest_hns/scripts.pory"
	lock
# 198 "data/maps/UlaUla_Forest_hns/scripts.pory"
	faceplayer
# 199 "data/maps/UlaUla_Forest_hns/scripts.pory"
	playmoncry SPECIES_TAPU_BULU, CRY_MODE_ENCOUNTER
# 200 "data/maps/UlaUla_Forest_hns/scripts.pory"
	msgbox Alola_Ulaula_BattleVsTapuBulu_Text_0
# 201 "data/maps/UlaUla_Forest_hns/scripts.pory"
	waitmoncry
# 202 "data/maps/UlaUla_Forest_hns/scripts.pory"
	seteventmon SPECIES_TAPU_BULU, 60
# 203 "data/maps/UlaUla_Forest_hns/scripts.pory"
	special BattleSetup_StartLegendaryBattle
# 204 "data/maps/UlaUla_Forest_hns/scripts.pory"
	waitstate
# 205 "data/maps/UlaUla_Forest_hns/scripts.pory"
	specialvar VAR_RESULT, GetBattleOutcome
# 206 "data/maps/UlaUla_Forest_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_CAUGHT
	goto_if_eq Alola_Ulaula_BattleVsTapuBulu_2
# 213 "data/maps/UlaUla_Forest_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq Alola_Ulaula_BattleVsTapuBulu_3
# 221 "data/maps/UlaUla_Forest_hns/scripts.pory"
	release
	end

# 224 "data/maps/UlaUla_Forest_hns/scripts.pory"
	release
	end

Alola_Ulaula_BattleVsTapuBulu_2:
# 207 "data/maps/UlaUla_Forest_hns/scripts.pory"
	setflag FLAG_HIDE_TAPU_BULU
# 208 "data/maps/UlaUla_Forest_hns/scripts.pory"
	setflag FLAG_BATTLED_TAPU_BULU
# 209 "data/maps/UlaUla_Forest_hns/scripts.pory"
	removeobject Ulaula_Tapu
# 210 "data/maps/UlaUla_Forest_hns/scripts.pory"
	release
	end

Alola_Ulaula_BattleVsTapuBulu_3:
# 214 "data/maps/UlaUla_Forest_hns/scripts.pory"
	setflag FLAG_HIDE_TAPU_BULU
# 215 "data/maps/UlaUla_Forest_hns/scripts.pory"
	setflag FLAG_BATTLED_TAPU_BULU
# 216 "data/maps/UlaUla_Forest_hns/scripts.pory"
	removeobject Ulaula_Tapu
# 217 "data/maps/UlaUla_Forest_hns/scripts.pory"
	release
	end


# 47 "data/maps/UlaUla_Forest_hns/scripts.pory"
Alola_Ulaula_TotemBattle_Trigger_Movement_0:
# 47 "data/maps/UlaUla_Forest_hns/scripts.pory"
	walk_in_place_down
# 47 "data/maps/UlaUla_Forest_hns/scripts.pory"
	walk_in_place_down
	step_end

Alola_Ulaula_TotemBattle_Text_0:
# 80 "data/maps/UlaUla_Forest_hns/scripts.pory"
	.string "Bee-beep!$"

Alola_Ulaula_TotemBattle_Text_1:
# 94 "data/maps/UlaUla_Forest_hns/scripts.pory"
	.string "Totem Vikavolt was defeated!\n"
	.string "It scampered off somewhere…$"

Alola_Ulaula_TotemBattle_Text_2:
# 113 "data/maps/UlaUla_Forest_hns/scripts.pory"
	.string "Ssee-mee?!$"

Alola_Ulaula_TotemBattle_Text_3:
# 127 "data/maps/UlaUla_Forest_hns/scripts.pory"
	.string "Totem Mimikyu was defeated!\n"
	.string "It scampered off somewhere…$"

Alola_Ulaula_Totem_sign_Text_0:
# 150 "data/maps/UlaUla_Forest_hns/scripts.pory"
	.string "The totem is emanating a strong\n"
	.string "energy…\p"
	.string "Touch the totem to teleport to another\n"
	.string "Isle?$"

Alola_Ulaula_Totem_sign_Text_1:
# 155 "data/maps/UlaUla_Forest_hns/scripts.pory"
	.string "Melemele Isle$"

Alola_Ulaula_Totem_sign_Text_2:
# 155 "data/maps/UlaUla_Forest_hns/scripts.pory"
	.string "Akala Isle$"

Alola_Ulaula_Totem_sign_Text_3:
# 155 "data/maps/UlaUla_Forest_hns/scripts.pory"
	.string "Ula'ula Isle$"

Alola_Ulaula_Totem_sign_Text_4:
# 155 "data/maps/UlaUla_Forest_hns/scripts.pory"
	.string "Poni Isle$"

Alola_Ulaula_Totem_sign_Text_5:
# 155 "data/maps/UlaUla_Forest_hns/scripts.pory"
	.string "Cancel$"

Alola_Ulaula_Totem_sign_Text_6:
# 189 "data/maps/UlaUla_Forest_hns/scripts.pory"
	.string "A strange totem stands here,\n"
	.string "power is emanating from it…$"

Alola_Ulaula_BattleVsTapuBulu_Text_0:
# 200 "data/maps/UlaUla_Forest_hns/scripts.pory"
	.string "Bu-Bulu!$"
