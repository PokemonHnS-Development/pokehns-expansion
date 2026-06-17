AlolaIslandRight_hns_MapScripts::
# 2 "data/maps/AlolaIslandRight_hns/scripts.pory"
	map_script MAP_SCRIPT_ON_TRANSITION, AlolaIslandRight_hns_MapScripts_MAP_SCRIPT_ON_TRANSITION
	.byte 0

AlolaIslandRight_hns_MapScripts_MAP_SCRIPT_ON_TRANSITION:
# 3 "data/maps/AlolaIslandRight_hns/scripts.pory"
	gettimeofday
# 4 "data/maps/AlolaIslandRight_hns/scripts.pory"
	compare VAR_0x8000, TIME_MORNING
	goto_if_eq AlolaIslandRight_hns_MapScripts_MAP_SCRIPT_ON_TRANSITION_1
# 4 "data/maps/AlolaIslandRight_hns/scripts.pory"
	compare VAR_0x8000, TIME_DAY
	goto_if_eq AlolaIslandRight_hns_MapScripts_MAP_SCRIPT_ON_TRANSITION_1
# 11 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setvar VAR_OBJ_GFX_ID_1, OBJ_EVENT_GFX_SPECIES ( SALAMENCE )
# 12 "data/maps/AlolaIslandRight_hns/scripts.pory"
	clearflag FLAG_AKALA_TOTEM_DAY
	return

AlolaIslandRight_hns_MapScripts_MAP_SCRIPT_ON_TRANSITION_1:
# 6 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setvar VAR_OBJ_GFX_ID_1, OBJ_EVENT_GFX_SPECIES ( MAGMORTAR )
# 7 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setflag FLAG_AKALA_TOTEM_DAY
	return


Alola_Akala_BattleSandygast::
# 18 "data/maps/AlolaIslandRight_hns/scripts.pory"
	lock
# 19 "data/maps/AlolaIslandRight_hns/scripts.pory"
	faceplayer
# 20 "data/maps/AlolaIslandRight_hns/scripts.pory"
	playmoncry SPECIES_CORSOLA, 0
# 21 "data/maps/AlolaIslandRight_hns/scripts.pory"
	msgbox Alola_Akala_BattleSandygast_Text_0, MSGBOX_AUTOCLOSE
# 22 "data/maps/AlolaIslandRight_hns/scripts.pory"
	waitmoncry
# 23 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setwildbattle SPECIES_CORSOLA, 45
# 24 "data/maps/AlolaIslandRight_hns/scripts.pory"
	dowildbattle
# 25 "data/maps/AlolaIslandRight_hns/scripts.pory"
	specialvar VAR_RESULT, GetBattleOutcome
# 26 "data/maps/AlolaIslandRight_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_CAUGHT
	goto_if_eq Alola_Akala_BattleSandygast_2
# 32 "data/maps/AlolaIslandRight_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq Alola_Akala_BattleSandygast_3
# 39 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end

# 42 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end

Alola_Akala_BattleSandygast_2:
# 27 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setflag FLAG_CAUGHT_SANDYGAST2
# 28 "data/maps/AlolaIslandRight_hns/scripts.pory"
	removeobject Alola_Akala_Sandygast
# 29 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end

Alola_Akala_BattleSandygast_3:
# 33 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setflag FLAG_CAUGHT_SANDYGAST2
# 34 "data/maps/AlolaIslandRight_hns/scripts.pory"
	removeobject Alola_Akala_Sandygast
# 35 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end


Alola_Akala_Island_FindItem1::
# 47 "data/maps/AlolaIslandRight_hns/scripts.pory"
	finditem ITEM_PROTEIN, 1
	end


Alola_Akala_Island_FindItem2::
# 52 "data/maps/AlolaIslandRight_hns/scripts.pory"
	finditem ITEM_IRON, 1
	end


Alola_Akala_Island_Finditem3::
# 57 "data/maps/AlolaIslandRight_hns/scripts.pory"
	finditem ITEM_ZINC, 1
	end


Alola_Akala_Sign::
# 62 "data/maps/AlolaIslandRight_hns/scripts.pory"
	lock
# 63 "data/maps/AlolaIslandRight_hns/scripts.pory"
	msgbox Alola_Akala_Sign_Text_0
# 64 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end


Alola_Akala_House_Sign::
# 69 "data/maps/AlolaIslandRight_hns/scripts.pory"
	lock
# 70 "data/maps/AlolaIslandRight_hns/scripts.pory"
	msgbox Alola_Akala_House_Sign_Text_0
# 74 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end


Alola_Akala_Pikipek::
# 79 "data/maps/AlolaIslandRight_hns/scripts.pory"
	lock
# 80 "data/maps/AlolaIslandRight_hns/scripts.pory"
	faceplayer
# 81 "data/maps/AlolaIslandRight_hns/scripts.pory"
	playmoncry SPECIES_CHATOT, 0
# 82 "data/maps/AlolaIslandRight_hns/scripts.pory"
	msgbox Alola_Akala_Pikipek_Text_0, MSGBOX_AUTOCLOSE
# 83 "data/maps/AlolaIslandRight_hns/scripts.pory"
	waitmoncry
# 84 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end


Alola_Akala_OldManOnBench::
# 89 "data/maps/AlolaIslandRight_hns/scripts.pory"
	lock
# 90 "data/maps/AlolaIslandRight_hns/scripts.pory"
	faceplayer
# 91 "data/maps/AlolaIslandRight_hns/scripts.pory"
	msgbox Alola_Akala_OldManOnBench_Text_0, MSGBOX_AUTOCLOSE
# 96 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end


Alola_Akala_TotemBattle_Trigger::
# 101 "data/maps/AlolaIslandRight_hns/scripts.pory"
	goto_if_unset FLAG_TRIGGERED_AKALA_TOTEM, Alola_Akala_TotemBattle_Trigger_1
	end

Alola_Akala_TotemBattle_Trigger_1:
# 103 "data/maps/AlolaIslandRight_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_AKALA, Alola_Akala_TotemBattle_Trigger_7
Alola_Akala_TotemBattle_Trigger_5:
	end

Alola_Akala_TotemBattle_Trigger_4:
# 105 "data/maps/AlolaIslandRight_hns/scripts.pory"
	lock
# 106 "data/maps/AlolaIslandRight_hns/scripts.pory"
	delay 30
# 107 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setvar VAR_0x8004, 2
# 108 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setvar VAR_0x8005, 6
# 109 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setvar VAR_0x8006, 4
# 110 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setvar VAR_0x8007, 4
# 111 "data/maps/AlolaIslandRight_hns/scripts.pory"
	special ShakeCamera
# 112 "data/maps/AlolaIslandRight_hns/scripts.pory"
	waitstate
# 113 "data/maps/AlolaIslandRight_hns/scripts.pory"
	fadescreenswapbuffers FADE_TO_BLACK
# 114 "data/maps/AlolaIslandRight_hns/scripts.pory"
	delay 30
# 115 "data/maps/AlolaIslandRight_hns/scripts.pory"
	clearflag FLAG_HIDE_AKALA_TOTEM
# 116 "data/maps/AlolaIslandRight_hns/scripts.pory"
	gettimeofday
# 117 "data/maps/AlolaIslandRight_hns/scripts.pory"
	compare VAR_0x8000, TIME_MORNING
	goto_if_eq Alola_Akala_TotemBattle_Trigger_14
# 117 "data/maps/AlolaIslandRight_hns/scripts.pory"
	compare VAR_0x8000, TIME_DAY
	goto_if_eq Alola_Akala_TotemBattle_Trigger_14
# 127 "data/maps/AlolaIslandRight_hns/scripts.pory"
	playmoncry SPECIES_SALAMENCE, 0
# 128 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setvar VAR_OBJ_GFX_ID_1, OBJ_EVENT_GFX_SPECIES ( SALAMENCE )
# 129 "data/maps/AlolaIslandRight_hns/scripts.pory"
	clearflag FLAG_AKALA_TOTEM_DAY
# 130 "data/maps/AlolaIslandRight_hns/scripts.pory"
	addobject Akala_Totem
# 131 "data/maps/AlolaIslandRight_hns/scripts.pory"
	waitmoncry
Alola_Akala_TotemBattle_Trigger_13:
# 133 "data/maps/AlolaIslandRight_hns/scripts.pory"
	special DrawWholeMapView
# 134 "data/maps/AlolaIslandRight_hns/scripts.pory"
	delay 30
# 135 "data/maps/AlolaIslandRight_hns/scripts.pory"
	fadescreenswapbuffers FADE_FROM_BLACK
# 136 "data/maps/AlolaIslandRight_hns/scripts.pory"
	delay 30
# 137 "data/maps/AlolaIslandRight_hns/scripts.pory"
	gettimeofday
# 138 "data/maps/AlolaIslandRight_hns/scripts.pory"
	compare VAR_0x8000, TIME_MORNING
	goto_if_eq Alola_Akala_TotemBattle_Trigger_20
# 138 "data/maps/AlolaIslandRight_hns/scripts.pory"
	compare VAR_0x8000, TIME_DAY
	goto_if_eq Alola_Akala_TotemBattle_Trigger_20
# 147 "data/maps/AlolaIslandRight_hns/scripts.pory"
	playmoncry SPECIES_SALAMENCE, 0
# 148 "data/maps/AlolaIslandRight_hns/scripts.pory"
	applymovement Akala_Totem, Alola_Akala_TotemBattle_Trigger_Movement_0
# 149 "data/maps/AlolaIslandRight_hns/scripts.pory"
	waitmovement 0
# 150 "data/maps/AlolaIslandRight_hns/scripts.pory"
	waitmoncry
Alola_Akala_TotemBattle_Trigger_19:
# 152 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setflag FLAG_TRIGGERED_AKALA_TOTEM
# 153 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end

Alola_Akala_TotemBattle_Trigger_6:
# 103 "data/maps/AlolaIslandRight_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_PONI, Alola_Akala_TotemBattle_Trigger_10
	goto Alola_Akala_TotemBattle_Trigger_5

Alola_Akala_TotemBattle_Trigger_7:
# 103 "data/maps/AlolaIslandRight_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_ULAULA, Alola_Akala_TotemBattle_Trigger_6
	goto Alola_Akala_TotemBattle_Trigger_5

Alola_Akala_TotemBattle_Trigger_10:
# 103 "data/maps/AlolaIslandRight_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_MELEMELE, Alola_Akala_TotemBattle_Trigger_4
	goto Alola_Akala_TotemBattle_Trigger_5

Alola_Akala_TotemBattle_Trigger_14:
# 119 "data/maps/AlolaIslandRight_hns/scripts.pory"
	playmoncry SPECIES_MAGMORTAR, 0
# 120 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setvar VAR_OBJ_GFX_ID_1, OBJ_EVENT_GFX_SPECIES ( MAGMORTAR )
# 121 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setflag FLAG_AKALA_TOTEM_DAY
# 122 "data/maps/AlolaIslandRight_hns/scripts.pory"
	addobject Akala_Totem
# 123 "data/maps/AlolaIslandRight_hns/scripts.pory"
	waitmoncry
	goto Alola_Akala_TotemBattle_Trigger_13

Alola_Akala_TotemBattle_Trigger_20:
# 140 "data/maps/AlolaIslandRight_hns/scripts.pory"
	playmoncry SPECIES_MAGMORTAR, 0
# 141 "data/maps/AlolaIslandRight_hns/scripts.pory"
	applymovement Akala_Totem, Alola_Akala_TotemBattle_Trigger_Movement_0
# 142 "data/maps/AlolaIslandRight_hns/scripts.pory"
	waitmovement 0
# 143 "data/maps/AlolaIslandRight_hns/scripts.pory"
	waitmoncry
	goto Alola_Akala_TotemBattle_Trigger_19


Alola_Akala_TotemBattle::
# 168 "data/maps/AlolaIslandRight_hns/scripts.pory"
	lock
# 169 "data/maps/AlolaIslandRight_hns/scripts.pory"
	faceplayer
# 170 "data/maps/AlolaIslandRight_hns/scripts.pory"
	goto_if_set FLAG_AKALA_TOTEM_DAY, Alola_Akala_TotemBattle_1
# 198 "data/maps/AlolaIslandRight_hns/scripts.pory"
	playmoncry SPECIES_SALAMENCE, 0
# 199 "data/maps/AlolaIslandRight_hns/scripts.pory"
	msgbox Alola_Akala_TotemBattle_Text_2, MSGBOX_AUTOCLOSE
# 200 "data/maps/AlolaIslandRight_hns/scripts.pory"
	waitmoncry
# 201 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setwildbattle SPECIES_SHELGON, 60, ITEM_NONE, SPECIES_SALAMENCE, 60, ITEM_PETAYA_BERRY
# 202 "data/maps/AlolaIslandRight_hns/scripts.pory"
	settotemboost B_POSITION_OPPONENT_RIGHT, 1, 1, 1, 1, 1, 1
# 203 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setflag FLAG_NO_WILD_CATCHING
# 204 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setflag FLAG_NO_WILD_RUNNING
# 205 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setflag FLAG_SMART_WILD_AI
# 206 "data/maps/AlolaIslandRight_hns/scripts.pory"
	dowildbattle
# 207 "data/maps/AlolaIslandRight_hns/scripts.pory"
	specialvar VAR_RESULT, GetBattleOutcome
# 208 "data/maps/AlolaIslandRight_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq Alola_Akala_TotemBattle_7
# 221 "data/maps/AlolaIslandRight_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_LOST
	goto_if_eq Alola_Akala_TotemBattle_9
	return

Alola_Akala_TotemBattle_1:
# 172 "data/maps/AlolaIslandRight_hns/scripts.pory"
	playmoncry SPECIES_MAGMORTAR, 0
# 173 "data/maps/AlolaIslandRight_hns/scripts.pory"
	msgbox Alola_Akala_TotemBattle_Text_0, MSGBOX_AUTOCLOSE
# 174 "data/maps/AlolaIslandRight_hns/scripts.pory"
	waitmoncry
# 176 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setwildbattle SPECIES_MAGMAR, 60, ITEM_NONE, SPECIES_MAGMORTAR, 60, ITEM_SITRUS_BERRY
# 177 "data/maps/AlolaIslandRight_hns/scripts.pory"
	settotemboost B_POSITION_OPPONENT_RIGHT, 1, 1, 1, 1, 1, 1
# 178 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setflag FLAG_NO_WILD_CATCHING
# 179 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setflag FLAG_NO_WILD_RUNNING
# 180 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setflag FLAG_SMART_WILD_AI
# 181 "data/maps/AlolaIslandRight_hns/scripts.pory"
	dowildbattle
# 182 "data/maps/AlolaIslandRight_hns/scripts.pory"
	specialvar VAR_RESULT, GetBattleOutcome
# 183 "data/maps/AlolaIslandRight_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq Alola_Akala_TotemBattle_4
	return

Alola_Akala_TotemBattle_4:
# 184 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setflag FLAG_HIDE_AKALA_TOTEM
# 185 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setflag FLAG_DEFEATED_AKALA_TOTEM
# 186 "data/maps/AlolaIslandRight_hns/scripts.pory"
	removeobject Akala_Totem
# 187 "data/maps/AlolaIslandRight_hns/scripts.pory"
	msgbox Alola_Akala_TotemBattle_Text_1, MSGBOX_AUTOCLOSE
# 189 "data/maps/AlolaIslandRight_hns/scripts.pory"
	clearflag FLAG_NO_WILD_CATCHING
# 190 "data/maps/AlolaIslandRight_hns/scripts.pory"
	clearflag FLAG_NO_WILD_RUNNING
# 191 "data/maps/AlolaIslandRight_hns/scripts.pory"
	clearflag FLAG_SMART_WILD_AI
# 192 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end

Alola_Akala_TotemBattle_7:
# 210 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setflag FLAG_HIDE_AKALA_TOTEM
# 211 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setflag FLAG_DEFEATED_AKALA_TOTEM
# 212 "data/maps/AlolaIslandRight_hns/scripts.pory"
	removeobject Akala_Totem
# 213 "data/maps/AlolaIslandRight_hns/scripts.pory"
	msgbox Alola_Akala_TotemBattle_Text_3, MSGBOX_AUTOCLOSE
# 215 "data/maps/AlolaIslandRight_hns/scripts.pory"
	clearflag FLAG_NO_WILD_CATCHING
# 216 "data/maps/AlolaIslandRight_hns/scripts.pory"
	clearflag FLAG_NO_WILD_RUNNING
# 217 "data/maps/AlolaIslandRight_hns/scripts.pory"
	clearflag FLAG_SMART_WILD_AI
# 218 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end

Alola_Akala_TotemBattle_9:
# 222 "data/maps/AlolaIslandRight_hns/scripts.pory"
	clearflag FLAG_NO_WILD_CATCHING
# 223 "data/maps/AlolaIslandRight_hns/scripts.pory"
	clearflag FLAG_NO_WILD_RUNNING
# 224 "data/maps/AlolaIslandRight_hns/scripts.pory"
	clearflag FLAG_SMART_WILD_AI
# 225 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end


Alola_Akala_Totem_sign::
# 232 "data/maps/AlolaIslandRight_hns/scripts.pory"
	lock
# 233 "data/maps/AlolaIslandRight_hns/scripts.pory"
	goto_if_set FLAG_BATTLED_TAPU_FINI, Alola_Akala_Totem_sign_5
Alola_Akala_Totem_sign_3:
# 274 "data/maps/AlolaIslandRight_hns/scripts.pory"
	msgbox Alola_Akala_Totem_sign_Text_5, MSGBOX_AUTOCLOSE
# 277 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end

Alola_Akala_Totem_sign_2:
# 235 "data/maps/AlolaIslandRight_hns/scripts.pory"
	msgbox Alola_Akala_Totem_sign_Text_0
# 240 "data/maps/AlolaIslandRight_hns/scripts.pory"
	dynmultichoice 20, 4, FALSE, 4, 0, DYN_MULTICHOICE_CB_NONE, Alola_Akala_Totem_sign_Text_1, Alola_Akala_Sign_Text_0, Alola_Akala_Totem_sign_Text_2, Alola_Akala_Totem_sign_Text_3, Alola_Akala_Totem_sign_Text_4
# 241 "data/maps/AlolaIslandRight_hns/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq Alola_Akala_Totem_sign_12
# 247 "data/maps/AlolaIslandRight_hns/scripts.pory"
	compare VAR_RESULT, 1
	goto_if_eq Alola_Akala_Totem_sign_15
# 253 "data/maps/AlolaIslandRight_hns/scripts.pory"
	compare VAR_RESULT, 2
	goto_if_eq Alola_Akala_Totem_sign_18
# 259 "data/maps/AlolaIslandRight_hns/scripts.pory"
	compare VAR_RESULT, 3
	goto_if_eq Alola_Akala_Totem_sign_20
# 267 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end

Alola_Akala_Totem_sign_4:
# 233 "data/maps/AlolaIslandRight_hns/scripts.pory"
	goto_if_set FLAG_BATTLED_TAPU_BULU, Alola_Akala_Totem_sign_8
	goto Alola_Akala_Totem_sign_3

Alola_Akala_Totem_sign_5:
# 233 "data/maps/AlolaIslandRight_hns/scripts.pory"
	goto_if_set FLAG_BATTLED_TAPU_KOKO, Alola_Akala_Totem_sign_4
	goto Alola_Akala_Totem_sign_3

Alola_Akala_Totem_sign_8:
# 233 "data/maps/AlolaIslandRight_hns/scripts.pory"
	goto_if_set FLAG_BATTLED_TAPU_LELE, Alola_Akala_Totem_sign_2
	goto Alola_Akala_Totem_sign_3

Alola_Akala_Totem_sign_12:
# 243 "data/maps/AlolaIslandRight_hns/scripts.pory"
	warp MAP_ALOLA_ISLAND_MELEMELE_HNS, 34, 26
# 244 "data/maps/AlolaIslandRight_hns/scripts.pory"
	waitstate
	end

Alola_Akala_Totem_sign_15:
# 249 "data/maps/AlolaIslandRight_hns/scripts.pory"
	warp MAP_ALOLA_ISLAND_RIGHT_HNS, 9, 10
# 250 "data/maps/AlolaIslandRight_hns/scripts.pory"
	waitstate
	end

Alola_Akala_Totem_sign_18:
# 255 "data/maps/AlolaIslandRight_hns/scripts.pory"
	warp MAP_ULA_ULA_FOREST_HNS, 16, 5
# 256 "data/maps/AlolaIslandRight_hns/scripts.pory"
	waitstate
	end

Alola_Akala_Totem_sign_20:
# 261 "data/maps/AlolaIslandRight_hns/scripts.pory"
	warp MAP_ALOLA_ISLAND_HNS, 13, 8
# 262 "data/maps/AlolaIslandRight_hns/scripts.pory"
	waitstate
	end


Alola_Akala_TapuLele_Flyover::
# 282 "data/maps/AlolaIslandRight_hns/scripts.pory"
	goto_if_set FLAG_FLYOVER_TAPU_LELE, Alola_Akala_TapuLele_Flyover_2
# 295 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end

Alola_Akala_TapuLele_Flyover_2:
# 284 "data/maps/AlolaIslandRight_hns/scripts.pory"
	addobject Akala_Flyover_Tapu
# 285 "data/maps/AlolaIslandRight_hns/scripts.pory"
	playse SE_M_FLY
# 286 "data/maps/AlolaIslandRight_hns/scripts.pory"
	applymovement Akala_Flyover_Tapu, Alola_Akala_TapuLele_Flyover_Movement_0
# 287 "data/maps/AlolaIslandRight_hns/scripts.pory"
	waitmovement 0
# 288 "data/maps/AlolaIslandRight_hns/scripts.pory"
	removeobject Akala_Flyover_Tapu
# 289 "data/maps/AlolaIslandRight_hns/scripts.pory"
	clearflag FLAG_FLYOVER_TAPU_LELE
# 290 "data/maps/AlolaIslandRight_hns/scripts.pory"
	clearflag FLAG_HIDE_TAPU_LELE
# 291 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end


Alola_Akala_BattleVsTapuLele::
# 300 "data/maps/AlolaIslandRight_hns/scripts.pory"
	lock
# 301 "data/maps/AlolaIslandRight_hns/scripts.pory"
	faceplayer
# 302 "data/maps/AlolaIslandRight_hns/scripts.pory"
	playmoncry SPECIES_TAPU_LELE, CRY_MODE_ENCOUNTER
# 303 "data/maps/AlolaIslandRight_hns/scripts.pory"
	msgbox Alola_Akala_BattleVsTapuLele_Text_0
# 304 "data/maps/AlolaIslandRight_hns/scripts.pory"
	waitmoncry
# 305 "data/maps/AlolaIslandRight_hns/scripts.pory"
	seteventmon SPECIES_TAPU_LELE, 60
# 306 "data/maps/AlolaIslandRight_hns/scripts.pory"
	special BattleSetup_StartLegendaryBattle
# 307 "data/maps/AlolaIslandRight_hns/scripts.pory"
	waitstate
# 308 "data/maps/AlolaIslandRight_hns/scripts.pory"
	specialvar VAR_RESULT, GetBattleOutcome
# 309 "data/maps/AlolaIslandRight_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_CAUGHT
	goto_if_eq Alola_Akala_BattleVsTapuLele_2
# 316 "data/maps/AlolaIslandRight_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq Alola_Akala_BattleVsTapuLele_3
# 324 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end

# 327 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end

Alola_Akala_BattleVsTapuLele_2:
# 310 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setflag FLAG_HIDE_TAPU_LELE
# 311 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setflag FLAG_BATTLED_TAPU_LELE
# 312 "data/maps/AlolaIslandRight_hns/scripts.pory"
	removeobject Akala_Tapu
# 313 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end

Alola_Akala_BattleVsTapuLele_3:
# 317 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setflag FLAG_HIDE_TAPU_LELE
# 318 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setflag FLAG_BATTLED_TAPU_LELE
# 319 "data/maps/AlolaIslandRight_hns/scripts.pory"
	removeobject Akala_Tapu
# 320 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end


Alola_Akala_TrainerBattleHiker::
# 332 "data/maps/AlolaIslandRight_hns/scripts.pory"
	trainerbattle_single TRAINER_AKALA_HIKER_HNS, Alola_Akala_TrainerBattleHiker_Text_0, Alola_Akala_TrainerBattleHiker_Text_1
# 333 "data/maps/AlolaIslandRight_hns/scripts.pory"
	msgbox Alola_Akala_TrainerBattleHiker_Text_2, MSGBOX_AUTOCLOSE
# 335 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end


Alola_Akala_TrainerBattlePicnicker::
# 340 "data/maps/AlolaIslandRight_hns/scripts.pory"
	trainerbattle_single TRAINER_AKALA_PICNICKER_HNS, Alola_Akala_TrainerBattlePicnicker_Text_0, Alola_Akala_TrainerBattlePicnicker_Text_1
# 341 "data/maps/AlolaIslandRight_hns/scripts.pory"
	msgbox Alola_Akala_TrainerBattlePicnicker_Text_2, MSGBOX_AUTOCLOSE
# 343 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end


Alola_Akala_TrainerBattleCamper::
# 348 "data/maps/AlolaIslandRight_hns/scripts.pory"
	trainerbattle_single TRAINER_AKALA_CAMPER_HNS, Alola_Akala_TrainerBattleCamper_Text_0, Alola_Akala_TrainerBattleCamper_Text_1
# 349 "data/maps/AlolaIslandRight_hns/scripts.pory"
	msgbox Alola_Akala_TrainerBattleCamper_Text_2, MSGBOX_AUTOCLOSE
# 351 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end


Alola_Akala_TrainerBattleSwimmerLand::
# 356 "data/maps/AlolaIslandRight_hns/scripts.pory"
	trainerbattle_single TRAINER_AKALA_SWIMMER_2_HNS, Alola_Akala_TrainerBattleSwimmerLand_Text_0, Alola_Akala_TrainerBattleSwimmerLand_Text_1
# 357 "data/maps/AlolaIslandRight_hns/scripts.pory"
	msgbox Alola_Akala_TrainerBattleSwimmerLand_Text_2, MSGBOX_AUTOCLOSE
# 359 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end


Alola_Akala_TrainerBattleSwimmerWater::
# 364 "data/maps/AlolaIslandRight_hns/scripts.pory"
	trainerbattle_single TRAINER_AKALA_SWIMMER_1_HNS, Alola_Akala_TrainerBattleSwimmerWater_Text_0, Alola_Akala_TrainerBattleSwimmerWater_Text_1
# 365 "data/maps/AlolaIslandRight_hns/scripts.pory"
	msgbox Alola_Akala_TrainerBattleSwimmerWater_Text_2, MSGBOX_AUTOCLOSE
# 367 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end


Alola_Akala_TrainerBattleSwimmerWaterM::
# 372 "data/maps/AlolaIslandRight_hns/scripts.pory"
	trainerbattle_single TRAINER_AKALA_SWIMMER_3_HNS, Alola_Akala_TrainerBattleSwimmerWaterM_Text_0, Alola_Akala_TrainerBattleSwimmerWaterM_Text_1
# 373 "data/maps/AlolaIslandRight_hns/scripts.pory"
	msgbox Alola_Akala_TrainerBattleSwimmerWaterM_Text_2, MSGBOX_AUTOCLOSE
# 376 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end


Alola_Akala_Bench_Heal::
# 380 "data/maps/AlolaIslandRight_hns/scripts.pory"
	lock
# 381 "data/maps/AlolaIslandRight_hns/scripts.pory"
	faceplayer
# 382 "data/maps/AlolaIslandRight_hns/scripts.pory"
	msgbox Alola_Akala_Bench_Heal_Text_0, MSGBOX_YESNO
# 384 "data/maps/AlolaIslandRight_hns/scripts.pory"
	compare VAR_RESULT, YES
	goto_if_eq Alola_Akala_Bench_Heal_2
Alola_Akala_Bench_Heal_1:
# 394 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end

Alola_Akala_Bench_Heal_2:
# 385 "data/maps/AlolaIslandRight_hns/scripts.pory"
	fadescreenswapbuffers FADE_TO_BLACK
# 386 "data/maps/AlolaIslandRight_hns/scripts.pory"
	special HealPlayerParty
# 387 "data/maps/AlolaIslandRight_hns/scripts.pory"
	closemessage
# 388 "data/maps/AlolaIslandRight_hns/scripts.pory"
	playfanfare MUS_HEAL
# 389 "data/maps/AlolaIslandRight_hns/scripts.pory"
	waitfanfare
# 390 "data/maps/AlolaIslandRight_hns/scripts.pory"
	applymovement LOCALID_PLAYER, Alola_Akala_Bench_Heal_Movement_0
# 391 "data/maps/AlolaIslandRight_hns/scripts.pory"
	waitmovement 0
# 392 "data/maps/AlolaIslandRight_hns/scripts.pory"
	fadescreenswapbuffers FADE_FROM_BLACK
	goto Alola_Akala_Bench_Heal_1


# 141 "data/maps/AlolaIslandRight_hns/scripts.pory"
Alola_Akala_TotemBattle_Trigger_Movement_0:
# 141 "data/maps/AlolaIslandRight_hns/scripts.pory"
	walk_in_place_down
# 141 "data/maps/AlolaIslandRight_hns/scripts.pory"
	walk_in_place_down
	step_end

# 286 "data/maps/AlolaIslandRight_hns/scripts.pory"
Alola_Akala_TapuLele_Flyover_Movement_0:
# 286 "data/maps/AlolaIslandRight_hns/scripts.pory"
	walk_faster_left
# 286 "data/maps/AlolaIslandRight_hns/scripts.pory"
	walk_faster_left
# 286 "data/maps/AlolaIslandRight_hns/scripts.pory"
	walk_faster_left
# 286 "data/maps/AlolaIslandRight_hns/scripts.pory"
	walk_faster_left
# 286 "data/maps/AlolaIslandRight_hns/scripts.pory"
	walk_faster_left
# 286 "data/maps/AlolaIslandRight_hns/scripts.pory"
	walk_faster_left
# 286 "data/maps/AlolaIslandRight_hns/scripts.pory"
	walk_faster_left
# 286 "data/maps/AlolaIslandRight_hns/scripts.pory"
	walk_faster_left
# 286 "data/maps/AlolaIslandRight_hns/scripts.pory"
	walk_faster_left
# 286 "data/maps/AlolaIslandRight_hns/scripts.pory"
	walk_faster_left
# 286 "data/maps/AlolaIslandRight_hns/scripts.pory"
	walk_faster_left
# 286 "data/maps/AlolaIslandRight_hns/scripts.pory"
	walk_faster_left
# 286 "data/maps/AlolaIslandRight_hns/scripts.pory"
	walk_faster_left
# 286 "data/maps/AlolaIslandRight_hns/scripts.pory"
	walk_faster_left
# 286 "data/maps/AlolaIslandRight_hns/scripts.pory"
	walk_faster_left
# 286 "data/maps/AlolaIslandRight_hns/scripts.pory"
	walk_faster_left
# 286 "data/maps/AlolaIslandRight_hns/scripts.pory"
	walk_faster_left
	step_end

# 390 "data/maps/AlolaIslandRight_hns/scripts.pory"
Alola_Akala_Bench_Heal_Movement_0:
# 390 "data/maps/AlolaIslandRight_hns/scripts.pory"
	face_down
	step_end

Alola_Akala_BattleSandygast_Text_0:
# 21 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "Coorr!$"

Alola_Akala_Sign_Text_0:
# 63 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "Akala Isle$"

Alola_Akala_House_Sign_Text_0:
# 70 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "The Akala Villa.\p"
	.string "A place for visitors to stay while\n"
	.string "on Akala Isle.$"

Alola_Akala_Pikipek_Text_0:
# 82 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "Chaaatot!$"

Alola_Akala_OldManOnBench_Text_0:
# 91 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "Ah the weather is so nice today,\n"
	.string "isn't it?\p"
	.string "I was just feeding the Chatot and this\n"
	.string "one decided to join me on my bench!$"

Alola_Akala_TotemBattle_Text_0:
# 173 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "Mortaar!$"

Alola_Akala_TotemBattle_Text_1:
# 187 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "Totem Magmortar was defeated!\n"
	.string "It scampered off somewhere…$"

Alola_Akala_TotemBattle_Text_2:
# 199 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "Salaa!$"

Alola_Akala_TotemBattle_Text_3:
# 213 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "Totem Salamence was defeated!\n"
	.string "It scampered off somewhere…$"

Alola_Akala_Totem_sign_Text_0:
# 235 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "The totem is emanating a strong\n"
	.string "energy…\p"
	.string "Touch the totem to teleport to another\n"
	.string "Isle?$"

Alola_Akala_Totem_sign_Text_1:
# 240 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "Melemele Isle$"

Alola_Akala_Totem_sign_Text_2:
# 240 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "Ula'ula Isle$"

Alola_Akala_Totem_sign_Text_3:
# 240 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "Poni Isle$"

Alola_Akala_Totem_sign_Text_4:
# 240 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "Cancel$"

Alola_Akala_Totem_sign_Text_5:
# 274 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "A strange totem stands here,\n"
	.string "power is emanating from it…$"

Alola_Akala_BattleVsTapuLele_Text_0:
# 303 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "Le-Lele!$"

Alola_Akala_TrainerBattleHiker_Text_0:
# 332 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "I came to the Isles to hike the\nmountains!$"

Alola_Akala_TrainerBattleHiker_Text_1:
# 332 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "And down I tumble…$"

Alola_Akala_TrainerBattleHiker_Text_2:
# 333 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "Akala Isle has the best hiking!\n"
	.string "It's got lush forests and rugged trails!$"

Alola_Akala_TrainerBattlePicnicker_Text_0:
# 340 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "Ha! Didn't see me, did you?$"

Alola_Akala_TrainerBattlePicnicker_Text_1:
# 340 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "I guess the element of surprise isn't\nalways super effective…$"

Alola_Akala_TrainerBattlePicnicker_Text_2:
# 341 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "It's so lush on Akala Isle,\n"
	.string "I can easily hide in the trees!$"

Alola_Akala_TrainerBattleCamper_Text_0:
# 348 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "I want to be the first to prove myself\nto the Totem Pokémon!$"

Alola_Akala_TrainerBattleCamper_Text_1:
# 348 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "Drat,\nthat's not going to help my case.$"

Alola_Akala_TrainerBattleCamper_Text_2:
# 349 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "There's a weird Totem further ahead but\n"
	.string "I haven't seen a Totem Pokémon.$"

Alola_Akala_TrainerBattleSwimmerLand_Text_0:
# 356 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "Hey! No shoes on the beach!$"

Alola_Akala_TrainerBattleSwimmerLand_Text_1:
# 356 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "Ouch,\nwhere's a lifeguard when you need one…$"

Alola_Akala_TrainerBattleSwimmerLand_Text_2:
# 357 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "Akala Isle has the best beaches!\n"
	.string "It's got soft sand and clear waters!$"

Alola_Akala_TrainerBattleSwimmerWater_Text_0:
# 364 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "Out of my way!\nI'm swimming laps!$"

Alola_Akala_TrainerBattleSwimmerWater_Text_1:
# 364 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "Not the break I was looking for…$"

Alola_Akala_TrainerBattleSwimmerWater_Text_2:
# 365 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "Ula'ula Isle has the best beaches!\n"
	.string "Ignore anyone who says otherwise!$"

Alola_Akala_TrainerBattleSwimmerWaterM_Text_0:
# 372 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "Hah!\nYou need to ride a Pokémon to surf?$"

Alola_Akala_TrainerBattleSwimmerWaterM_Text_1:
# 372 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "If I hadn't swam myself\nmaybe I would've had the energy to win…$"

Alola_Akala_TrainerBattleSwimmerWaterM_Text_2:
# 373 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "The current out here is strong!\n"
	.string "A Pokémon must be really powerful to\l"
	.string "migrate all the way out to the Isles!$"

Alola_Akala_Bench_Heal_Text_0:
# 382 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "Would you like to take a rest on this\n"
	.string "bench?$"
