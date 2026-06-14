AlolaIslandRight_hns_MapScripts::
	.byte 0


Alola_Akala_BattleSandygast::
# 4 "data/maps/AlolaIslandRight_hns/scripts.pory"
	lock
# 5 "data/maps/AlolaIslandRight_hns/scripts.pory"
	faceplayer
# 6 "data/maps/AlolaIslandRight_hns/scripts.pory"
	playmoncry SPECIES_SANDYGAST, 0
# 7 "data/maps/AlolaIslandRight_hns/scripts.pory"
	msgbox Alola_Akala_BattleSandygast_Text_0, MSGBOX_AUTOCLOSE
# 8 "data/maps/AlolaIslandRight_hns/scripts.pory"
	waitmoncry
# 9 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setwildbattle SPECIES_SANDYGAST, 45
# 10 "data/maps/AlolaIslandRight_hns/scripts.pory"
	dowildbattle
# 11 "data/maps/AlolaIslandRight_hns/scripts.pory"
	specialvar VAR_RESULT, GetBattleOutcome
# 12 "data/maps/AlolaIslandRight_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_CAUGHT
	goto_if_eq Alola_Akala_BattleSandygast_2
# 18 "data/maps/AlolaIslandRight_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq Alola_Akala_BattleSandygast_3
# 25 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end

# 28 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end

Alola_Akala_BattleSandygast_2:
# 13 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setflag FLAG_CAUGHT_SANDYGAST2
# 14 "data/maps/AlolaIslandRight_hns/scripts.pory"
	removeobject Alola_Akala_Sandygast
# 15 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end

Alola_Akala_BattleSandygast_3:
# 19 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setflag FLAG_CAUGHT_SANDYGAST2
# 20 "data/maps/AlolaIslandRight_hns/scripts.pory"
	removeobject Alola_Akala_Sandygast
# 21 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end


Alola_Akala_Island_FindItem1::
# 33 "data/maps/AlolaIslandRight_hns/scripts.pory"
	finditem ITEM_PROTEIN, 1
	end


Alola_Akala_Island_FindItem2::
# 38 "data/maps/AlolaIslandRight_hns/scripts.pory"
	finditem ITEM_IRON, 1
	end


Alola_Akala_Island_Finditem3::
# 43 "data/maps/AlolaIslandRight_hns/scripts.pory"
	finditem ITEM_ZINC, 1
	end


Alola_Akala_Sign::
# 48 "data/maps/AlolaIslandRight_hns/scripts.pory"
	lock
# 49 "data/maps/AlolaIslandRight_hns/scripts.pory"
	msgbox Alola_Akala_Sign_Text_0
# 50 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end


Alola_Akala_House_Sign::
# 55 "data/maps/AlolaIslandRight_hns/scripts.pory"
	lock
# 56 "data/maps/AlolaIslandRight_hns/scripts.pory"
	msgbox Alola_Akala_House_Sign_Text_0
# 60 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end


Alola_Akala_Pikipek::
# 65 "data/maps/AlolaIslandRight_hns/scripts.pory"
	lock
# 66 "data/maps/AlolaIslandRight_hns/scripts.pory"
	faceplayer
# 67 "data/maps/AlolaIslandRight_hns/scripts.pory"
	playmoncry SPECIES_PIKIPEK, 0
# 68 "data/maps/AlolaIslandRight_hns/scripts.pory"
	msgbox Alola_Akala_Pikipek_Text_0, MSGBOX_AUTOCLOSE
# 69 "data/maps/AlolaIslandRight_hns/scripts.pory"
	waitmoncry
# 70 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end


Alola_Akala_OldManOnBench::
# 75 "data/maps/AlolaIslandRight_hns/scripts.pory"
	lock
# 76 "data/maps/AlolaIslandRight_hns/scripts.pory"
	faceplayer
# 77 "data/maps/AlolaIslandRight_hns/scripts.pory"
	msgbox Alola_Akala_OldManOnBench_Text_0, MSGBOX_AUTOCLOSE
# 82 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end


Alola_Akala_TotemBattle_Trigger::
# 87 "data/maps/AlolaIslandRight_hns/scripts.pory"
	goto_if_unset FLAG_TRIGGERED_AKALA_TOTEM, Alola_Akala_TotemBattle_Trigger_1
	end

Alola_Akala_TotemBattle_Trigger_1:
# 89 "data/maps/AlolaIslandRight_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_AKALA, Alola_Akala_TotemBattle_Trigger_7
Alola_Akala_TotemBattle_Trigger_5:
	end

Alola_Akala_TotemBattle_Trigger_4:
# 91 "data/maps/AlolaIslandRight_hns/scripts.pory"
	lock
# 92 "data/maps/AlolaIslandRight_hns/scripts.pory"
	delay 30
# 93 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setvar VAR_0x8004, 2
# 94 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setvar VAR_0x8005, 6
# 95 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setvar VAR_0x8006, 4
# 96 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setvar VAR_0x8007, 4
# 97 "data/maps/AlolaIslandRight_hns/scripts.pory"
	special ShakeCamera
# 98 "data/maps/AlolaIslandRight_hns/scripts.pory"
	waitstate
# 99 "data/maps/AlolaIslandRight_hns/scripts.pory"
	fadescreenswapbuffers FADE_TO_BLACK
# 100 "data/maps/AlolaIslandRight_hns/scripts.pory"
	delay 30
# 101 "data/maps/AlolaIslandRight_hns/scripts.pory"
	clearflag FLAG_HIDE_AKALA_TOTEM
# 102 "data/maps/AlolaIslandRight_hns/scripts.pory"
	gettimeofday
# 103 "data/maps/AlolaIslandRight_hns/scripts.pory"
	compare VAR_0x8000, TIME_MORNING
	goto_if_eq Alola_Akala_TotemBattle_Trigger_14
# 103 "data/maps/AlolaIslandRight_hns/scripts.pory"
	compare VAR_0x8000, TIME_DAY
	goto_if_eq Alola_Akala_TotemBattle_Trigger_14
# 112 "data/maps/AlolaIslandRight_hns/scripts.pory"
	playmoncry SPECIES_SALAZZLE, 0
# 113 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setvar VAR_OBJ_GFX_ID_1, OBJ_EVENT_GFX_SPECIES ( SALAZZLE )
# 114 "data/maps/AlolaIslandRight_hns/scripts.pory"
	addobject Akala_Totem
# 115 "data/maps/AlolaIslandRight_hns/scripts.pory"
	waitmoncry
Alola_Akala_TotemBattle_Trigger_13:
# 117 "data/maps/AlolaIslandRight_hns/scripts.pory"
	special DrawWholeMapView
# 118 "data/maps/AlolaIslandRight_hns/scripts.pory"
	delay 30
# 119 "data/maps/AlolaIslandRight_hns/scripts.pory"
	fadescreenswapbuffers FADE_FROM_BLACK
# 120 "data/maps/AlolaIslandRight_hns/scripts.pory"
	delay 30
# 121 "data/maps/AlolaIslandRight_hns/scripts.pory"
	gettimeofday
# 122 "data/maps/AlolaIslandRight_hns/scripts.pory"
	compare VAR_0x8000, TIME_MORNING
	goto_if_eq Alola_Akala_TotemBattle_Trigger_20
# 122 "data/maps/AlolaIslandRight_hns/scripts.pory"
	compare VAR_0x8000, TIME_DAY
	goto_if_eq Alola_Akala_TotemBattle_Trigger_20
# 131 "data/maps/AlolaIslandRight_hns/scripts.pory"
	playmoncry SPECIES_SALAZZLE, 0
# 132 "data/maps/AlolaIslandRight_hns/scripts.pory"
	applymovement Akala_Totem, Alola_Akala_TotemBattle_Trigger_Movement_0
# 133 "data/maps/AlolaIslandRight_hns/scripts.pory"
	waitmovement 0
# 134 "data/maps/AlolaIslandRight_hns/scripts.pory"
	waitmoncry
Alola_Akala_TotemBattle_Trigger_19:
# 136 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setflag FLAG_TRIGGERED_AKALA_TOTEM
# 137 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end

Alola_Akala_TotemBattle_Trigger_6:
# 89 "data/maps/AlolaIslandRight_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_PONI, Alola_Akala_TotemBattle_Trigger_10
	goto Alola_Akala_TotemBattle_Trigger_5

Alola_Akala_TotemBattle_Trigger_7:
# 89 "data/maps/AlolaIslandRight_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_ULAULA, Alola_Akala_TotemBattle_Trigger_6
	goto Alola_Akala_TotemBattle_Trigger_5

Alola_Akala_TotemBattle_Trigger_10:
# 89 "data/maps/AlolaIslandRight_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_MELEMELE, Alola_Akala_TotemBattle_Trigger_4
	goto Alola_Akala_TotemBattle_Trigger_5

Alola_Akala_TotemBattle_Trigger_14:
# 105 "data/maps/AlolaIslandRight_hns/scripts.pory"
	playmoncry SPECIES_ARAQUANID, 0
# 106 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setvar VAR_OBJ_GFX_ID_1, OBJ_EVENT_GFX_SPECIES ( ARAQUANID )
# 107 "data/maps/AlolaIslandRight_hns/scripts.pory"
	addobject Akala_Totem
# 108 "data/maps/AlolaIslandRight_hns/scripts.pory"
	waitmoncry
	goto Alola_Akala_TotemBattle_Trigger_13

Alola_Akala_TotemBattle_Trigger_20:
# 124 "data/maps/AlolaIslandRight_hns/scripts.pory"
	playmoncry SPECIES_ARAQUANID, 0
# 125 "data/maps/AlolaIslandRight_hns/scripts.pory"
	applymovement Akala_Totem, Alola_Akala_TotemBattle_Trigger_Movement_0
# 126 "data/maps/AlolaIslandRight_hns/scripts.pory"
	waitmovement 0
# 127 "data/maps/AlolaIslandRight_hns/scripts.pory"
	waitmoncry
	goto Alola_Akala_TotemBattle_Trigger_19


Alola_Akala_TotemBattle::
# 152 "data/maps/AlolaIslandRight_hns/scripts.pory"
	lock
# 153 "data/maps/AlolaIslandRight_hns/scripts.pory"
	faceplayer
# 154 "data/maps/AlolaIslandRight_hns/scripts.pory"
	gettimeofday
# 155 "data/maps/AlolaIslandRight_hns/scripts.pory"
	compare VAR_0x8000, TIME_MORNING
	goto_if_eq Alola_Akala_TotemBattle_1
# 155 "data/maps/AlolaIslandRight_hns/scripts.pory"
	compare VAR_0x8000, TIME_DAY
	goto_if_eq Alola_Akala_TotemBattle_1
# 183 "data/maps/AlolaIslandRight_hns/scripts.pory"
	playmoncry SPECIES_SALAZZLE, 0
# 184 "data/maps/AlolaIslandRight_hns/scripts.pory"
	msgbox Alola_Akala_TotemBattle_Text_0, MSGBOX_AUTOCLOSE
# 185 "data/maps/AlolaIslandRight_hns/scripts.pory"
	waitmoncry
# 186 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setwildbattle SPECIES_SALANDIT, 60, ITEM_NONE, SPECIES_SALAZZLE_TOTEM, 60, ITEM_PETAYA_BERRY
# 187 "data/maps/AlolaIslandRight_hns/scripts.pory"
	settotemboost B_POSITION_OPPONENT_RIGHT, 0, 0, 0, 0, 1
# 188 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setflag FLAG_NO_WILD_CATCHING
# 189 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setflag FLAG_NO_WILD_RUNNING
# 190 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setflag FLAG_SMART_WILD_AI
# 191 "data/maps/AlolaIslandRight_hns/scripts.pory"
	dowildbattle
# 192 "data/maps/AlolaIslandRight_hns/scripts.pory"
	specialvar VAR_RESULT, GetBattleOutcome
# 193 "data/maps/AlolaIslandRight_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq Alola_Akala_TotemBattle_9
# 206 "data/maps/AlolaIslandRight_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_LOST
	goto_if_eq Alola_Akala_TotemBattle_11
	return

Alola_Akala_TotemBattle_1:
# 157 "data/maps/AlolaIslandRight_hns/scripts.pory"
	playmoncry SPECIES_ARAQUANID, 0
# 158 "data/maps/AlolaIslandRight_hns/scripts.pory"
	msgbox Alola_Akala_TotemBattle_Text_0, MSGBOX_AUTOCLOSE
# 159 "data/maps/AlolaIslandRight_hns/scripts.pory"
	waitmoncry
# 161 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setwildbattle SPECIES_DEWPIDER, 60, ITEM_NONE, SPECIES_ARAQUANID_TOTEM, 60, ITEM_SITRUS_BERRY
# 162 "data/maps/AlolaIslandRight_hns/scripts.pory"
	settotemboost B_POSITION_OPPONENT_RIGHT, 0, 0, 0, 0, 1
# 163 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setflag FLAG_NO_WILD_CATCHING
# 164 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setflag FLAG_NO_WILD_RUNNING
# 165 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setflag FLAG_SMART_WILD_AI
# 166 "data/maps/AlolaIslandRight_hns/scripts.pory"
	dowildbattle
# 167 "data/maps/AlolaIslandRight_hns/scripts.pory"
	specialvar VAR_RESULT, GetBattleOutcome
# 168 "data/maps/AlolaIslandRight_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq Alola_Akala_TotemBattle_6
	return

Alola_Akala_TotemBattle_6:
# 169 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setflag FLAG_HIDE_AKALA_TOTEM
# 170 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setflag FLAG_DEFEATED_AKALA_TOTEM
# 171 "data/maps/AlolaIslandRight_hns/scripts.pory"
	removeobject Akala_Totem
# 172 "data/maps/AlolaIslandRight_hns/scripts.pory"
	msgbox Alola_Akala_TotemBattle_Text_1, MSGBOX_AUTOCLOSE
# 174 "data/maps/AlolaIslandRight_hns/scripts.pory"
	clearflag FLAG_NO_WILD_CATCHING
# 175 "data/maps/AlolaIslandRight_hns/scripts.pory"
	clearflag FLAG_NO_WILD_RUNNING
# 176 "data/maps/AlolaIslandRight_hns/scripts.pory"
	clearflag FLAG_SMART_WILD_AI
# 177 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end

Alola_Akala_TotemBattle_9:
# 195 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setflag FLAG_HIDE_AKALA_TOTEM
# 196 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setflag FLAG_DEFEATED_AKALA_TOTEM
# 197 "data/maps/AlolaIslandRight_hns/scripts.pory"
	removeobject Akala_Totem
# 198 "data/maps/AlolaIslandRight_hns/scripts.pory"
	msgbox Alola_Akala_TotemBattle_Text_2, MSGBOX_AUTOCLOSE
# 200 "data/maps/AlolaIslandRight_hns/scripts.pory"
	clearflag FLAG_NO_WILD_CATCHING
# 201 "data/maps/AlolaIslandRight_hns/scripts.pory"
	clearflag FLAG_NO_WILD_RUNNING
# 202 "data/maps/AlolaIslandRight_hns/scripts.pory"
	clearflag FLAG_SMART_WILD_AI
# 203 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end

Alola_Akala_TotemBattle_11:
# 207 "data/maps/AlolaIslandRight_hns/scripts.pory"
	clearflag FLAG_NO_WILD_CATCHING
# 208 "data/maps/AlolaIslandRight_hns/scripts.pory"
	clearflag FLAG_NO_WILD_RUNNING
# 209 "data/maps/AlolaIslandRight_hns/scripts.pory"
	clearflag FLAG_SMART_WILD_AI
# 210 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end


Alola_Akala_Totem_sign::
# 217 "data/maps/AlolaIslandRight_hns/scripts.pory"
	lock
# 218 "data/maps/AlolaIslandRight_hns/scripts.pory"
	msgbox Alola_Akala_Totem_sign_Text_0, MSGBOX_AUTOCLOSE
# 220 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end


Alola_Akala_TapuLele_Flyover::
# 225 "data/maps/AlolaIslandRight_hns/scripts.pory"
	goto_if_set FLAG_FLYOVER_TAPU_LELE, Alola_Akala_TapuLele_Flyover_2
# 238 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end

Alola_Akala_TapuLele_Flyover_2:
# 227 "data/maps/AlolaIslandRight_hns/scripts.pory"
	addobject Akala_Flyover_Tapu
# 228 "data/maps/AlolaIslandRight_hns/scripts.pory"
	playse SE_M_FLY
# 229 "data/maps/AlolaIslandRight_hns/scripts.pory"
	applymovement Akala_Flyover_Tapu, Alola_Akala_TapuLele_Flyover_Movement_0
# 230 "data/maps/AlolaIslandRight_hns/scripts.pory"
	waitmovement 0
# 231 "data/maps/AlolaIslandRight_hns/scripts.pory"
	removeobject Akala_Flyover_Tapu
# 232 "data/maps/AlolaIslandRight_hns/scripts.pory"
	clearflag FLAG_FLYOVER_TAPU_LELE
# 233 "data/maps/AlolaIslandRight_hns/scripts.pory"
	clearflag FLAG_HIDE_TAPU_LELE
# 234 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end


Alola_Akala_BattleVsTapuLele::
# 243 "data/maps/AlolaIslandRight_hns/scripts.pory"
	lock
# 244 "data/maps/AlolaIslandRight_hns/scripts.pory"
	faceplayer
# 245 "data/maps/AlolaIslandRight_hns/scripts.pory"
	playmoncry SPECIES_TAPU_LELE, 0
# 246 "data/maps/AlolaIslandRight_hns/scripts.pory"
	applymovement Akala_Tapu, Alola_Akala_TotemBattle_Trigger_Movement_0
# 247 "data/maps/AlolaIslandRight_hns/scripts.pory"
	msgbox Alola_Akala_BattleVsTapuLele_Text_0
# 248 "data/maps/AlolaIslandRight_hns/scripts.pory"
	waitmovement 0
# 249 "data/maps/AlolaIslandRight_hns/scripts.pory"
	waitmoncry
# 250 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setwildbattle SPECIES_TAPU_LELE, 60
# 251 "data/maps/AlolaIslandRight_hns/scripts.pory"
	dowildbattle
# 252 "data/maps/AlolaIslandRight_hns/scripts.pory"
	specialvar VAR_RESULT, GetBattleOutcome
# 253 "data/maps/AlolaIslandRight_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_CAUGHT
	goto_if_eq Alola_Akala_BattleVsTapuLele_2
# 260 "data/maps/AlolaIslandRight_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq Alola_Akala_BattleVsTapuLele_3
# 268 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end

# 271 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end

Alola_Akala_BattleVsTapuLele_2:
# 254 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setflag FLAG_HIDE_TAPU_LELE
# 255 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setflag FLAG_BATTLED_TAPU_LELE
# 256 "data/maps/AlolaIslandRight_hns/scripts.pory"
	removeobject Akala_Tapu
# 257 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end

Alola_Akala_BattleVsTapuLele_3:
# 261 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setflag FLAG_HIDE_TAPU_LELE
# 262 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setflag FLAG_BATTLED_TAPU_LELE
# 263 "data/maps/AlolaIslandRight_hns/scripts.pory"
	removeobject Akala_Tapu
# 264 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end


Alola_Akala_TrainerBattleHiker::
# 276 "data/maps/AlolaIslandRight_hns/scripts.pory"
	trainerbattle_single TRAINER_AKALA_HIKER_HNS, Alola_Akala_TrainerBattleHiker_Text_0, Alola_Akala_TrainerBattleHiker_Text_1
# 277 "data/maps/AlolaIslandRight_hns/scripts.pory"
	msgbox Alola_Akala_TrainerBattleHiker_Text_2, MSGBOX_AUTOCLOSE
# 279 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end


Alola_Akala_TrainerBattlePicnicker::
# 284 "data/maps/AlolaIslandRight_hns/scripts.pory"
	trainerbattle_single TRAINER_AKALA_PICNICKER_HNS, Alola_Akala_TrainerBattlePicnicker_Text_0, Alola_Akala_TrainerBattlePicnicker_Text_1
# 285 "data/maps/AlolaIslandRight_hns/scripts.pory"
	msgbox Alola_Akala_TrainerBattlePicnicker_Text_2, MSGBOX_AUTOCLOSE
# 287 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end


Alola_Akala_TrainerBattleCamper::
# 292 "data/maps/AlolaIslandRight_hns/scripts.pory"
	trainerbattle_single TRAINER_AKALA_CAMPER_HNS, Alola_Akala_TrainerBattleCamper_Text_0, Alola_Akala_TrainerBattleCamper_Text_1
# 293 "data/maps/AlolaIslandRight_hns/scripts.pory"
	msgbox Alola_Akala_TrainerBattleCamper_Text_2, MSGBOX_AUTOCLOSE
# 295 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end


Alola_Akala_TrainerBattleSwimmerLand::
# 300 "data/maps/AlolaIslandRight_hns/scripts.pory"
	trainerbattle_single TRAINER_AKALA_SWIMMER_2_HNS, Alola_Akala_TrainerBattleSwimmerLand_Text_0, Alola_Akala_TrainerBattleSwimmerLand_Text_1
# 301 "data/maps/AlolaIslandRight_hns/scripts.pory"
	msgbox Alola_Akala_TrainerBattleSwimmerLand_Text_2, MSGBOX_AUTOCLOSE
# 303 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end


Alola_Akala_TrainerBattleSwimmerWater::
# 308 "data/maps/AlolaIslandRight_hns/scripts.pory"
	trainerbattle_single TRAINER_AKALA_SWIMMER_1_HNS, Alola_Akala_TrainerBattleSwimmerWater_Text_0, Alola_Akala_TrainerBattleSwimmerWater_Text_1
# 309 "data/maps/AlolaIslandRight_hns/scripts.pory"
	msgbox Alola_Akala_TrainerBattleSwimmerWater_Text_2, MSGBOX_AUTOCLOSE
# 311 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end


Alola_Akala_TrainerBattleSwimmerWaterM::
# 316 "data/maps/AlolaIslandRight_hns/scripts.pory"
	trainerbattle_single TRAINER_AKALA_SWIMMER_3_HNS, Alola_Akala_TrainerBattleSwimmerWaterM_Text_0, Alola_Akala_TrainerBattleSwimmerWaterM_Text_1
# 317 "data/maps/AlolaIslandRight_hns/scripts.pory"
	msgbox Alola_Akala_TrainerBattleSwimmerWaterM_Text_2, MSGBOX_AUTOCLOSE
# 320 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end


# 125 "data/maps/AlolaIslandRight_hns/scripts.pory"
Alola_Akala_TotemBattle_Trigger_Movement_0:
# 125 "data/maps/AlolaIslandRight_hns/scripts.pory"
	walk_in_place_down
# 125 "data/maps/AlolaIslandRight_hns/scripts.pory"
	walk_in_place_down
	step_end

# 229 "data/maps/AlolaIslandRight_hns/scripts.pory"
Alola_Akala_TapuLele_Flyover_Movement_0:
# 229 "data/maps/AlolaIslandRight_hns/scripts.pory"
	walk_faster_left
# 229 "data/maps/AlolaIslandRight_hns/scripts.pory"
	walk_faster_left
# 229 "data/maps/AlolaIslandRight_hns/scripts.pory"
	walk_faster_left
# 229 "data/maps/AlolaIslandRight_hns/scripts.pory"
	walk_faster_left
# 229 "data/maps/AlolaIslandRight_hns/scripts.pory"
	walk_faster_left
# 229 "data/maps/AlolaIslandRight_hns/scripts.pory"
	walk_faster_left
# 229 "data/maps/AlolaIslandRight_hns/scripts.pory"
	walk_faster_left
# 229 "data/maps/AlolaIslandRight_hns/scripts.pory"
	walk_faster_left
# 229 "data/maps/AlolaIslandRight_hns/scripts.pory"
	walk_faster_left
# 229 "data/maps/AlolaIslandRight_hns/scripts.pory"
	walk_faster_left
# 229 "data/maps/AlolaIslandRight_hns/scripts.pory"
	walk_faster_left
# 229 "data/maps/AlolaIslandRight_hns/scripts.pory"
	walk_faster_left
# 229 "data/maps/AlolaIslandRight_hns/scripts.pory"
	walk_faster_left
# 229 "data/maps/AlolaIslandRight_hns/scripts.pory"
	walk_faster_left
# 229 "data/maps/AlolaIslandRight_hns/scripts.pory"
	walk_faster_left
# 229 "data/maps/AlolaIslandRight_hns/scripts.pory"
	walk_faster_left
# 229 "data/maps/AlolaIslandRight_hns/scripts.pory"
	walk_faster_left
	step_end

Alola_Akala_BattleSandygast_Text_0:
# 7 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "Gaaah!$"

Alola_Akala_Sign_Text_0:
# 49 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "Akala Isle$"

Alola_Akala_House_Sign_Text_0:
# 56 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "The Akala Villa.\p"
	.string "A place for visitors to stay while\n"
	.string "on Akala Isle.$"

Alola_Akala_Pikipek_Text_0:
# 68 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "Pek!$"

Alola_Akala_OldManOnBench_Text_0:
# 77 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "Ah the weather is so nice today,\n"
	.string "isn't it?\p"
	.string "I was just feeding the Pikipek and this\n"
	.string "one decided to join me on my bench!$"

Alola_Akala_TotemBattle_Text_0:
# 158 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "Thhhh!$"

Alola_Akala_TotemBattle_Text_1:
# 172 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "Totem Araquanid was defeated!\n"
	.string "It scampered off somewhere…$"

Alola_Akala_TotemBattle_Text_2:
# 198 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "Totem Salazzle was defeated!\n"
	.string "It scampered off somewhere…$"

Alola_Akala_Totem_sign_Text_0:
# 218 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "A strange totem stands here,\n"
	.string "power is emanating from it…$"

Alola_Akala_BattleVsTapuLele_Text_0:
# 247 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "Graah!$"

Alola_Akala_TrainerBattleHiker_Text_0:
# 276 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "I came to the Isles to hike the\nmountains!$"

Alola_Akala_TrainerBattleHiker_Text_1:
# 276 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "And down I tumble…$"

Alola_Akala_TrainerBattleHiker_Text_2:
# 277 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "Akala Isle has the best hiking!\n"
	.string "It's got lush forests and rugged trails!$"

Alola_Akala_TrainerBattlePicnicker_Text_0:
# 284 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "Ha! Didn't see me, did you?$"

Alola_Akala_TrainerBattlePicnicker_Text_1:
# 284 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "I guess the element of surprise isn't\nalways super effective…$"

Alola_Akala_TrainerBattlePicnicker_Text_2:
# 285 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "It's so lush on Akala Isle,\n"
	.string "I can easily hide in the trees!$"

Alola_Akala_TrainerBattleCamper_Text_0:
# 292 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "I want to be the first to prove myself\nto the Totem Pokémon!$"

Alola_Akala_TrainerBattleCamper_Text_1:
# 292 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "Drat,\nthat's not going to help my case.$"

Alola_Akala_TrainerBattleCamper_Text_2:
# 293 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "There's a weird Totem further ahead but\n"
	.string "I haven't seen a Totem Pokémon.$"

Alola_Akala_TrainerBattleSwimmerLand_Text_0:
# 300 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "Hey! No shoes on the beach!$"

Alola_Akala_TrainerBattleSwimmerLand_Text_1:
# 300 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "Ouch,\nwhere's a lifeguard when you need one…$"

Alola_Akala_TrainerBattleSwimmerLand_Text_2:
# 301 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "Akala Isle has the best beaches!\n"
	.string "It's got soft sand and clear waters!$"

Alola_Akala_TrainerBattleSwimmerWater_Text_0:
# 308 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "Out of my way!\nI'm swimming laps!$"

Alola_Akala_TrainerBattleSwimmerWater_Text_1:
# 308 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "Not the break I was looking for…$"

Alola_Akala_TrainerBattleSwimmerWater_Text_2:
# 309 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "Ula'ula Isle has the best beaches!\n"
	.string "Ignore anyone who says otherwise!$"

Alola_Akala_TrainerBattleSwimmerWaterM_Text_0:
# 316 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "Hah!\nYou need to ride a Pokémon to surf?$"

Alola_Akala_TrainerBattleSwimmerWaterM_Text_1:
# 316 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "If I hadn't swam myself\nmaybe I would've had the energy to win…$"

Alola_Akala_TrainerBattleSwimmerWaterM_Text_2:
# 317 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "The current out here is strong!\n"
	.string "A Pokémon must be really powerful to\l"
	.string "migrate all the way out to the Isles!$"
