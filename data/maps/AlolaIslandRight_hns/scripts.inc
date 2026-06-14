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
# 57 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end


Alola_Akala_Pikipek::
# 62 "data/maps/AlolaIslandRight_hns/scripts.pory"
	lock
# 63 "data/maps/AlolaIslandRight_hns/scripts.pory"
	faceplayer
# 64 "data/maps/AlolaIslandRight_hns/scripts.pory"
	playmoncry SPECIES_PIKIPEK, 0
# 65 "data/maps/AlolaIslandRight_hns/scripts.pory"
	msgbox Alola_Akala_Pikipek_Text_0, MSGBOX_AUTOCLOSE
# 66 "data/maps/AlolaIslandRight_hns/scripts.pory"
	waitmoncry
# 67 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end


Alola_Akala_OldManOnBench::
# 72 "data/maps/AlolaIslandRight_hns/scripts.pory"
	lock
# 73 "data/maps/AlolaIslandRight_hns/scripts.pory"
	faceplayer
# 74 "data/maps/AlolaIslandRight_hns/scripts.pory"
	msgbox Alola_Akala_OldManOnBench_Text_0, MSGBOX_AUTOCLOSE
# 79 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end


Alola_Akala_TotemBattle_Trigger::
# 84 "data/maps/AlolaIslandRight_hns/scripts.pory"
	goto_if_unset FLAG_TRIGGERED_AKALA_TOTEM, Alola_Akala_TotemBattle_Trigger_1
	end

Alola_Akala_TotemBattle_Trigger_1:
# 86 "data/maps/AlolaIslandRight_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_AKALA, Alola_Akala_TotemBattle_Trigger_7
Alola_Akala_TotemBattle_Trigger_5:
	end

Alola_Akala_TotemBattle_Trigger_4:
# 88 "data/maps/AlolaIslandRight_hns/scripts.pory"
	lock
# 89 "data/maps/AlolaIslandRight_hns/scripts.pory"
	delay 30
# 90 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setvar VAR_0x8004, 2
# 91 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setvar VAR_0x8005, 6
# 92 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setvar VAR_0x8006, 4
# 93 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setvar VAR_0x8007, 4
# 94 "data/maps/AlolaIslandRight_hns/scripts.pory"
	special ShakeCamera
# 95 "data/maps/AlolaIslandRight_hns/scripts.pory"
	waitstate
# 96 "data/maps/AlolaIslandRight_hns/scripts.pory"
	fadescreenswapbuffers FADE_TO_BLACK
# 97 "data/maps/AlolaIslandRight_hns/scripts.pory"
	delay 30
# 98 "data/maps/AlolaIslandRight_hns/scripts.pory"
	clearflag FLAG_HIDE_AKALA_TOTEM
# 99 "data/maps/AlolaIslandRight_hns/scripts.pory"
	gettimeofday
# 100 "data/maps/AlolaIslandRight_hns/scripts.pory"
	compare VAR_0x8000, TIME_MORNING
	goto_if_eq Alola_Akala_TotemBattle_Trigger_14
# 100 "data/maps/AlolaIslandRight_hns/scripts.pory"
	compare VAR_0x8000, TIME_DAY
	goto_if_eq Alola_Akala_TotemBattle_Trigger_14
# 109 "data/maps/AlolaIslandRight_hns/scripts.pory"
	playmoncry SPECIES_SALAZZLE, 0
# 110 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setvar VAR_OBJ_GFX_ID_1, OBJ_EVENT_GFX_SPECIES ( SALAZZLE )
# 111 "data/maps/AlolaIslandRight_hns/scripts.pory"
	addobject Akala_Totem
# 112 "data/maps/AlolaIslandRight_hns/scripts.pory"
	waitmoncry
Alola_Akala_TotemBattle_Trigger_13:
# 114 "data/maps/AlolaIslandRight_hns/scripts.pory"
	special DrawWholeMapView
# 115 "data/maps/AlolaIslandRight_hns/scripts.pory"
	delay 30
# 116 "data/maps/AlolaIslandRight_hns/scripts.pory"
	fadescreenswapbuffers FADE_FROM_BLACK
# 117 "data/maps/AlolaIslandRight_hns/scripts.pory"
	delay 30
# 118 "data/maps/AlolaIslandRight_hns/scripts.pory"
	gettimeofday
# 119 "data/maps/AlolaIslandRight_hns/scripts.pory"
	compare VAR_0x8000, TIME_MORNING
	goto_if_eq Alola_Akala_TotemBattle_Trigger_20
# 119 "data/maps/AlolaIslandRight_hns/scripts.pory"
	compare VAR_0x8000, TIME_DAY
	goto_if_eq Alola_Akala_TotemBattle_Trigger_20
# 128 "data/maps/AlolaIslandRight_hns/scripts.pory"
	playmoncry SPECIES_SALAZZLE, 0
# 129 "data/maps/AlolaIslandRight_hns/scripts.pory"
	applymovement Akala_Totem, Alola_Akala_TotemBattle_Trigger_Movement_0
# 130 "data/maps/AlolaIslandRight_hns/scripts.pory"
	waitmovement 0
# 131 "data/maps/AlolaIslandRight_hns/scripts.pory"
	waitmoncry
Alola_Akala_TotemBattle_Trigger_19:
# 133 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setflag FLAG_TRIGGERED_AKALA_TOTEM
# 134 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end

Alola_Akala_TotemBattle_Trigger_6:
# 86 "data/maps/AlolaIslandRight_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_PONI, Alola_Akala_TotemBattle_Trigger_10
	goto Alola_Akala_TotemBattle_Trigger_5

Alola_Akala_TotemBattle_Trigger_7:
# 86 "data/maps/AlolaIslandRight_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_ULAULA, Alola_Akala_TotemBattle_Trigger_6
	goto Alola_Akala_TotemBattle_Trigger_5

Alola_Akala_TotemBattle_Trigger_10:
# 86 "data/maps/AlolaIslandRight_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_MELEMELE, Alola_Akala_TotemBattle_Trigger_4
	goto Alola_Akala_TotemBattle_Trigger_5

Alola_Akala_TotemBattle_Trigger_14:
# 102 "data/maps/AlolaIslandRight_hns/scripts.pory"
	playmoncry SPECIES_ARAQUANID, 0
# 103 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setvar VAR_OBJ_GFX_ID_1, OBJ_EVENT_GFX_SPECIES ( ARAQUANID )
# 104 "data/maps/AlolaIslandRight_hns/scripts.pory"
	addobject Akala_Totem
# 105 "data/maps/AlolaIslandRight_hns/scripts.pory"
	waitmoncry
	goto Alola_Akala_TotemBattle_Trigger_13

Alola_Akala_TotemBattle_Trigger_20:
# 121 "data/maps/AlolaIslandRight_hns/scripts.pory"
	playmoncry SPECIES_ARAQUANID, 0
# 122 "data/maps/AlolaIslandRight_hns/scripts.pory"
	applymovement Akala_Totem, Alola_Akala_TotemBattle_Trigger_Movement_0
# 123 "data/maps/AlolaIslandRight_hns/scripts.pory"
	waitmovement 0
# 124 "data/maps/AlolaIslandRight_hns/scripts.pory"
	waitmoncry
	goto Alola_Akala_TotemBattle_Trigger_19


Alola_Akala_TotemBattle::
# 149 "data/maps/AlolaIslandRight_hns/scripts.pory"
	lock
# 150 "data/maps/AlolaIslandRight_hns/scripts.pory"
	faceplayer
# 151 "data/maps/AlolaIslandRight_hns/scripts.pory"
	gettimeofday
# 152 "data/maps/AlolaIslandRight_hns/scripts.pory"
	compare VAR_0x8000, TIME_MORNING
	goto_if_eq Alola_Akala_TotemBattle_1
# 152 "data/maps/AlolaIslandRight_hns/scripts.pory"
	compare VAR_0x8000, TIME_DAY
	goto_if_eq Alola_Akala_TotemBattle_1
# 180 "data/maps/AlolaIslandRight_hns/scripts.pory"
	playmoncry SPECIES_SALAZZLE, 0
# 181 "data/maps/AlolaIslandRight_hns/scripts.pory"
	msgbox Alola_Akala_TotemBattle_Text_0, MSGBOX_AUTOCLOSE
# 182 "data/maps/AlolaIslandRight_hns/scripts.pory"
	waitmoncry
# 183 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setwildbattle SPECIES_SALANDIT, 60, ITEM_NONE, SPECIES_SALAZZLE_TOTEM, 60, ITEM_PETAYA_BERRY
# 184 "data/maps/AlolaIslandRight_hns/scripts.pory"
	settotemboost B_POSITION_OPPONENT_RIGHT, 0, 0, 0, 0, 1
# 185 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setflag FLAG_NO_WILD_CATCHING
# 186 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setflag FLAG_NO_WILD_RUNNING
# 187 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setflag FLAG_SMART_WILD_AI
# 188 "data/maps/AlolaIslandRight_hns/scripts.pory"
	dowildbattle
# 189 "data/maps/AlolaIslandRight_hns/scripts.pory"
	specialvar VAR_RESULT, GetBattleOutcome
# 190 "data/maps/AlolaIslandRight_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq Alola_Akala_TotemBattle_9
# 203 "data/maps/AlolaIslandRight_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_LOST
	goto_if_eq Alola_Akala_TotemBattle_11
	return

Alola_Akala_TotemBattle_1:
# 154 "data/maps/AlolaIslandRight_hns/scripts.pory"
	playmoncry SPECIES_ARAQUANID, 0
# 155 "data/maps/AlolaIslandRight_hns/scripts.pory"
	msgbox Alola_Akala_TotemBattle_Text_0, MSGBOX_AUTOCLOSE
# 156 "data/maps/AlolaIslandRight_hns/scripts.pory"
	waitmoncry
# 158 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setwildbattle SPECIES_DEWPIDER, 60, ITEM_NONE, SPECIES_ARAQUANID_TOTEM, 60, ITEM_SITRUS_BERRY
# 159 "data/maps/AlolaIslandRight_hns/scripts.pory"
	settotemboost B_POSITION_OPPONENT_RIGHT, 0, 0, 0, 0, 1
# 160 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setflag FLAG_NO_WILD_CATCHING
# 161 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setflag FLAG_NO_WILD_RUNNING
# 162 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setflag FLAG_SMART_WILD_AI
# 163 "data/maps/AlolaIslandRight_hns/scripts.pory"
	dowildbattle
# 164 "data/maps/AlolaIslandRight_hns/scripts.pory"
	specialvar VAR_RESULT, GetBattleOutcome
# 165 "data/maps/AlolaIslandRight_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq Alola_Akala_TotemBattle_6
	return

Alola_Akala_TotemBattle_6:
# 166 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setflag FLAG_HIDE_AKALA_TOTEM
# 167 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setflag FLAG_DEFEATED_AKALA_TOTEM
# 168 "data/maps/AlolaIslandRight_hns/scripts.pory"
	removeobject Akala_Totem
# 169 "data/maps/AlolaIslandRight_hns/scripts.pory"
	msgbox Alola_Akala_TotemBattle_Text_1, MSGBOX_AUTOCLOSE
# 171 "data/maps/AlolaIslandRight_hns/scripts.pory"
	clearflag FLAG_NO_WILD_CATCHING
# 172 "data/maps/AlolaIslandRight_hns/scripts.pory"
	clearflag FLAG_NO_WILD_RUNNING
# 173 "data/maps/AlolaIslandRight_hns/scripts.pory"
	clearflag FLAG_SMART_WILD_AI
# 174 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end

Alola_Akala_TotemBattle_9:
# 192 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setflag FLAG_HIDE_AKALA_TOTEM
# 193 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setflag FLAG_DEFEATED_AKALA_TOTEM
# 194 "data/maps/AlolaIslandRight_hns/scripts.pory"
	removeobject Akala_Totem
# 195 "data/maps/AlolaIslandRight_hns/scripts.pory"
	msgbox Alola_Akala_TotemBattle_Text_2, MSGBOX_AUTOCLOSE
# 197 "data/maps/AlolaIslandRight_hns/scripts.pory"
	clearflag FLAG_NO_WILD_CATCHING
# 198 "data/maps/AlolaIslandRight_hns/scripts.pory"
	clearflag FLAG_NO_WILD_RUNNING
# 199 "data/maps/AlolaIslandRight_hns/scripts.pory"
	clearflag FLAG_SMART_WILD_AI
# 200 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end

Alola_Akala_TotemBattle_11:
# 204 "data/maps/AlolaIslandRight_hns/scripts.pory"
	clearflag FLAG_NO_WILD_CATCHING
# 205 "data/maps/AlolaIslandRight_hns/scripts.pory"
	clearflag FLAG_NO_WILD_RUNNING
# 206 "data/maps/AlolaIslandRight_hns/scripts.pory"
	clearflag FLAG_SMART_WILD_AI
# 207 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end


Alola_Akala_Totem_sign::
# 214 "data/maps/AlolaIslandRight_hns/scripts.pory"
	lock
# 215 "data/maps/AlolaIslandRight_hns/scripts.pory"
	msgbox Alola_Akala_Totem_sign_Text_0, MSGBOX_AUTOCLOSE
# 217 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end


Alola_Akala_TapuLele_Flyover::
# 222 "data/maps/AlolaIslandRight_hns/scripts.pory"
	goto_if_set FLAG_FLYOVER_TAPU_LELE, Alola_Akala_TapuLele_Flyover_2
# 235 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end

Alola_Akala_TapuLele_Flyover_2:
# 224 "data/maps/AlolaIslandRight_hns/scripts.pory"
	addobject Akala_Flyover_Tapu
# 225 "data/maps/AlolaIslandRight_hns/scripts.pory"
	playse SE_M_FLY
# 226 "data/maps/AlolaIslandRight_hns/scripts.pory"
	applymovement Akala_Flyover_Tapu, Alola_Akala_TapuLele_Flyover_Movement_0
# 227 "data/maps/AlolaIslandRight_hns/scripts.pory"
	waitmovement 0
# 228 "data/maps/AlolaIslandRight_hns/scripts.pory"
	removeobject Akala_Flyover_Tapu
# 229 "data/maps/AlolaIslandRight_hns/scripts.pory"
	clearflag FLAG_FLYOVER_TAPU_LELE
# 230 "data/maps/AlolaIslandRight_hns/scripts.pory"
	clearflag FLAG_HIDE_TAPU_LELE
# 231 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end


Alola_Akala_BattleVsTapuLele::
# 240 "data/maps/AlolaIslandRight_hns/scripts.pory"
	lock
# 241 "data/maps/AlolaIslandRight_hns/scripts.pory"
	faceplayer
# 242 "data/maps/AlolaIslandRight_hns/scripts.pory"
	playmoncry SPECIES_TAPU_LELE, 0
# 243 "data/maps/AlolaIslandRight_hns/scripts.pory"
	applymovement Akala_Tapu, Alola_Akala_TotemBattle_Trigger_Movement_0
# 244 "data/maps/AlolaIslandRight_hns/scripts.pory"
	msgbox Alola_Akala_BattleVsTapuLele_Text_0
# 245 "data/maps/AlolaIslandRight_hns/scripts.pory"
	waitmovement 0
# 246 "data/maps/AlolaIslandRight_hns/scripts.pory"
	waitmoncry
# 247 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setwildbattle SPECIES_TAPU_LELE, 60
# 248 "data/maps/AlolaIslandRight_hns/scripts.pory"
	dowildbattle
# 249 "data/maps/AlolaIslandRight_hns/scripts.pory"
	specialvar VAR_RESULT, GetBattleOutcome
# 250 "data/maps/AlolaIslandRight_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_CAUGHT
	goto_if_eq Alola_Akala_BattleVsTapuLele_2
# 257 "data/maps/AlolaIslandRight_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq Alola_Akala_BattleVsTapuLele_3
# 265 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end

# 268 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end

Alola_Akala_BattleVsTapuLele_2:
# 251 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setflag FLAG_HIDE_TAPU_LELE
# 252 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setflag FLAG_BATTLED_TAPU_LELE
# 253 "data/maps/AlolaIslandRight_hns/scripts.pory"
	removeobject Akala_Tapu
# 254 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end

Alola_Akala_BattleVsTapuLele_3:
# 258 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setflag FLAG_HIDE_TAPU_LELE
# 259 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setflag FLAG_BATTLED_TAPU_LELE
# 260 "data/maps/AlolaIslandRight_hns/scripts.pory"
	removeobject Akala_Tapu
# 261 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end


Alola_Akala_TrainerBattleHiker::
# 273 "data/maps/AlolaIslandRight_hns/scripts.pory"
	trainerbattle_single TRAINER_AKALA_HIKER_HNS, Alola_Akala_TrainerBattleHiker_Text_0, Alola_Akala_TrainerBattleHiker_Text_1
# 274 "data/maps/AlolaIslandRight_hns/scripts.pory"
	msgbox Alola_Akala_TrainerBattleHiker_Text_2, MSGBOX_AUTOCLOSE
# 276 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end


Alola_Akala_TrainerBattlePicnicker::
# 281 "data/maps/AlolaIslandRight_hns/scripts.pory"
	trainerbattle_single TRAINER_AKALA_PICNICKER_HNS, Alola_Akala_TrainerBattlePicnicker_Text_0, Alola_Akala_TrainerBattlePicnicker_Text_1
# 282 "data/maps/AlolaIslandRight_hns/scripts.pory"
	msgbox Alola_Akala_TrainerBattlePicnicker_Text_2, MSGBOX_AUTOCLOSE
# 284 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end


Alola_Akala_TrainerBattleCamper::
# 289 "data/maps/AlolaIslandRight_hns/scripts.pory"
	trainerbattle_single TRAINER_AKALA_CAMPER_HNS, Alola_Akala_TrainerBattleCamper_Text_0, Alola_Akala_TrainerBattleCamper_Text_1
# 290 "data/maps/AlolaIslandRight_hns/scripts.pory"
	msgbox Alola_Akala_TrainerBattleCamper_Text_2, MSGBOX_AUTOCLOSE
# 292 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end


Alola_Akala_TrainerBattleSwimmerLand::
# 297 "data/maps/AlolaIslandRight_hns/scripts.pory"
	trainerbattle_single TRAINER_AKALA_SWIMMER_2_HNS, Alola_Akala_TrainerBattleSwimmerLand_Text_0, Alola_Akala_TrainerBattleSwimmerLand_Text_1
# 298 "data/maps/AlolaIslandRight_hns/scripts.pory"
	msgbox Alola_Akala_TrainerBattleSwimmerLand_Text_2, MSGBOX_AUTOCLOSE
# 300 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end


Alola_Akala_TrainerBattleSwimmerWater::
# 305 "data/maps/AlolaIslandRight_hns/scripts.pory"
	trainerbattle_single TRAINER_AKALA_SWIMMER_1_HNS, Alola_Akala_TrainerBattleSwimmerWater_Text_0, Alola_Akala_TrainerBattleSwimmerWater_Text_1
# 306 "data/maps/AlolaIslandRight_hns/scripts.pory"
	msgbox Alola_Akala_TrainerBattleSwimmerWater_Text_2, MSGBOX_AUTOCLOSE
# 308 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end


Alola_Akala_TrainerBattleSwimmerWaterM::
# 313 "data/maps/AlolaIslandRight_hns/scripts.pory"
	trainerbattle_single TRAINER_AKALA_SWIMMER_3_HNS, Alola_Akala_TrainerBattleSwimmerWaterM_Text_0, Alola_Akala_TrainerBattleSwimmerWaterM_Text_1
# 314 "data/maps/AlolaIslandRight_hns/scripts.pory"
	msgbox Alola_Akala_TrainerBattleSwimmerWaterM_Text_2, MSGBOX_AUTOCLOSE
# 317 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end


# 122 "data/maps/AlolaIslandRight_hns/scripts.pory"
Alola_Akala_TotemBattle_Trigger_Movement_0:
# 122 "data/maps/AlolaIslandRight_hns/scripts.pory"
	walk_in_place_down
# 122 "data/maps/AlolaIslandRight_hns/scripts.pory"
	walk_in_place_down
	step_end

# 226 "data/maps/AlolaIslandRight_hns/scripts.pory"
Alola_Akala_TapuLele_Flyover_Movement_0:
# 226 "data/maps/AlolaIslandRight_hns/scripts.pory"
	walk_faster_left
# 226 "data/maps/AlolaIslandRight_hns/scripts.pory"
	walk_faster_left
# 226 "data/maps/AlolaIslandRight_hns/scripts.pory"
	walk_faster_left
# 226 "data/maps/AlolaIslandRight_hns/scripts.pory"
	walk_faster_left
# 226 "data/maps/AlolaIslandRight_hns/scripts.pory"
	walk_faster_left
# 226 "data/maps/AlolaIslandRight_hns/scripts.pory"
	walk_faster_left
# 226 "data/maps/AlolaIslandRight_hns/scripts.pory"
	walk_faster_left
# 226 "data/maps/AlolaIslandRight_hns/scripts.pory"
	walk_faster_left
# 226 "data/maps/AlolaIslandRight_hns/scripts.pory"
	walk_faster_left
# 226 "data/maps/AlolaIslandRight_hns/scripts.pory"
	walk_faster_left
# 226 "data/maps/AlolaIslandRight_hns/scripts.pory"
	walk_faster_left
# 226 "data/maps/AlolaIslandRight_hns/scripts.pory"
	walk_faster_left
# 226 "data/maps/AlolaIslandRight_hns/scripts.pory"
	walk_faster_left
# 226 "data/maps/AlolaIslandRight_hns/scripts.pory"
	walk_faster_left
# 226 "data/maps/AlolaIslandRight_hns/scripts.pory"
	walk_faster_left
# 226 "data/maps/AlolaIslandRight_hns/scripts.pory"
	walk_faster_left
# 226 "data/maps/AlolaIslandRight_hns/scripts.pory"
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
	.string "???'s House$"

Alola_Akala_Pikipek_Text_0:
# 65 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "Pek!$"

Alola_Akala_OldManOnBench_Text_0:
# 74 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "Ah the weather is so nice today,\n"
	.string "doesn't it?\p"
	.string "I was just feeding the Pikipek and this\n"
	.string "one decided to join me on my bench!$"

Alola_Akala_TotemBattle_Text_0:
# 155 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "Thhhh!$"

Alola_Akala_TotemBattle_Text_1:
# 169 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "Totem Araquanid was defeated!\n"
	.string "It scampered off somewhere…$"

Alola_Akala_TotemBattle_Text_2:
# 195 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "Totem Salazzle was defeated!\n"
	.string "It scampered off somewhere…$"

Alola_Akala_Totem_sign_Text_0:
# 215 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "A strange totem stands here,\n"
	.string "power is emanating from it…$"

Alola_Akala_BattleVsTapuLele_Text_0:
# 244 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "Graah!$"

Alola_Akala_TrainerBattleHiker_Text_0:
# 273 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "I came to the Isles to hike the\nmountains!$"

Alola_Akala_TrainerBattleHiker_Text_1:
# 273 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "And down I tumble…$"

Alola_Akala_TrainerBattleHiker_Text_2:
# 274 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "Akala Isle has the best hiking!\n"
	.string "It's got lush forests and rugged trails!$"

Alola_Akala_TrainerBattlePicnicker_Text_0:
# 281 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "Ha! Didn't see me, did you?$"

Alola_Akala_TrainerBattlePicnicker_Text_1:
# 281 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "I guess the element of surprise isn't\nalways super effective…$"

Alola_Akala_TrainerBattlePicnicker_Text_2:
# 282 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "It's so lush on Akala Isle,\n"
	.string "I can easily hide in the trees!$"

Alola_Akala_TrainerBattleCamper_Text_0:
# 289 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "I want to be the first to prove myself\nto the Totem Pokémon!$"

Alola_Akala_TrainerBattleCamper_Text_1:
# 289 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "Drat,\nthat's not going to help my case.$"

Alola_Akala_TrainerBattleCamper_Text_2:
# 290 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "There's a weird Totem further ahead but\n"
	.string "I haven't seen a Totem Pokémon.$"

Alola_Akala_TrainerBattleSwimmerLand_Text_0:
# 297 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "Hey! No shoes on the beach!$"

Alola_Akala_TrainerBattleSwimmerLand_Text_1:
# 297 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "Ouch,\n where's a lifeguard when you need one…$"

Alola_Akala_TrainerBattleSwimmerLand_Text_2:
# 298 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "Akala Isle has the best beaches!\n"
	.string "It's got soft sand and clear waters!$"

Alola_Akala_TrainerBattleSwimmerWater_Text_0:
# 305 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "Out of my way!\nI'm swimming laps!$"

Alola_Akala_TrainerBattleSwimmerWater_Text_1:
# 305 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "Not the break I was looking for…$"

Alola_Akala_TrainerBattleSwimmerWater_Text_2:
# 306 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "Ula'ula Isle has the best beaches!\n"
	.string "Ignore anyone who says otherwise!$"

Alola_Akala_TrainerBattleSwimmerWaterM_Text_0:
# 313 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "Hah!\nYou need to ride a Pokémon to surf?$"

Alola_Akala_TrainerBattleSwimmerWaterM_Text_1:
# 313 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "If I hadn't swam myself\n maybe I would've had the energy to win…$"

Alola_Akala_TrainerBattleSwimmerWaterM_Text_2:
# 314 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "The current out here is strong!\n"
	.string "A Pokémon must be really powerful to\l"
	.string "migrate all the way out to the Isles!$"
