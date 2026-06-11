UlaUla_Forest_hns_MapScripts::
	.byte 0


Alola_Ulaula_Forest_FindItem1::
# 4 "data/maps/UlaUla_Forest_hns/scripts.pory"
	finditem ITEM_POTION, 1
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
	msgbox Alola_Ulaula_TotemBattle_Text_0, MSGBOX_AUTOCLOSE
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
	msgbox Alola_Ulaula_TotemBattle_Text_2, MSGBOX_AUTOCLOSE
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
	msgbox Alola_Ulaula_Totem_sign_Text_0, MSGBOX_AUTOCLOSE
# 150 "data/maps/UlaUla_Forest_hns/scripts.pory"
	release
	end


Alola_Ulaula_BattleVsTapuBulu::
# 155 "data/maps/UlaUla_Forest_hns/scripts.pory"
	lock
# 156 "data/maps/UlaUla_Forest_hns/scripts.pory"
	faceplayer
# 157 "data/maps/UlaUla_Forest_hns/scripts.pory"
	playmoncry SPECIES_TAPU_BULU, 0
# 158 "data/maps/UlaUla_Forest_hns/scripts.pory"
	applymovement Ulaula_Tapu, Alola_Ulaula_TotemBattle_Trigger_Movement_0
# 159 "data/maps/UlaUla_Forest_hns/scripts.pory"
	msgbox Alola_Ulaula_BattleVsTapuBulu_Text_0
# 160 "data/maps/UlaUla_Forest_hns/scripts.pory"
	waitmovement 0
# 161 "data/maps/UlaUla_Forest_hns/scripts.pory"
	waitmoncry
# 162 "data/maps/UlaUla_Forest_hns/scripts.pory"
	setwildbattle SPECIES_TAPU_BULU, 60
# 163 "data/maps/UlaUla_Forest_hns/scripts.pory"
	dowildbattle
# 164 "data/maps/UlaUla_Forest_hns/scripts.pory"
	specialvar VAR_RESULT, GetBattleOutcome
# 165 "data/maps/UlaUla_Forest_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_CAUGHT
	goto_if_eq Alola_Ulaula_BattleVsTapuBulu_2
# 172 "data/maps/UlaUla_Forest_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq Alola_Ulaula_BattleVsTapuBulu_3
# 180 "data/maps/UlaUla_Forest_hns/scripts.pory"
	release
	end

# 183 "data/maps/UlaUla_Forest_hns/scripts.pory"
	release
	end

Alola_Ulaula_BattleVsTapuBulu_2:
# 166 "data/maps/UlaUla_Forest_hns/scripts.pory"
	setflag FLAG_HIDE_TAPU_BULU
# 167 "data/maps/UlaUla_Forest_hns/scripts.pory"
	setflag FLAG_BATTLED_TAPU_BULU
# 168 "data/maps/UlaUla_Forest_hns/scripts.pory"
	removeobject Ulaula_Tapu
# 169 "data/maps/UlaUla_Forest_hns/scripts.pory"
	release
	end

Alola_Ulaula_BattleVsTapuBulu_3:
# 173 "data/maps/UlaUla_Forest_hns/scripts.pory"
	setflag FLAG_HIDE_TAPU_BULU
# 174 "data/maps/UlaUla_Forest_hns/scripts.pory"
	setflag FLAG_BATTLED_TAPU_BULU
# 175 "data/maps/UlaUla_Forest_hns/scripts.pory"
	removeobject Ulaula_Tapu
# 176 "data/maps/UlaUla_Forest_hns/scripts.pory"
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
	.string "Thhhh!$"

Alola_Ulaula_TotemBattle_Text_1:
# 94 "data/maps/UlaUla_Forest_hns/scripts.pory"
	.string "Totem Vikavolt was defeated!\n"
	.string "It scampered off somewhere…$"

Alola_Ulaula_TotemBattle_Text_2:
# 127 "data/maps/UlaUla_Forest_hns/scripts.pory"
	.string "Totem Mimikyu was defeated!\n"
	.string "It scampered off somewhere…$"

Alola_Ulaula_Totem_sign_Text_0:
# 148 "data/maps/UlaUla_Forest_hns/scripts.pory"
	.string "A strange totem stands here,\n"
	.string "power is emanating from it…$"

Alola_Ulaula_BattleVsTapuBulu_Text_0:
# 159 "data/maps/UlaUla_Forest_hns/scripts.pory"
	.string "Graah!$"
