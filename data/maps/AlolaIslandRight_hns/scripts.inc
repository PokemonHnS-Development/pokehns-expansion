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
	finditem ITEM_POTION, 1
	end


Alola_Akala_Island_FindItem2::
# 38 "data/maps/AlolaIslandRight_hns/scripts.pory"
	finditem ITEM_ANTIDOTE, 1
	end


Alola_Akala_Island_Finditem3::
# 43 "data/maps/AlolaIslandRight_hns/scripts.pory"
	finditem ITEM_ORAN_BERRY, 1
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


Alola_Akala_TotemBattle_Trigger::
# 72 "data/maps/AlolaIslandRight_hns/scripts.pory"
	goto_if_unset FLAG_TRIGGERED_AKALA_TOTEM, Alola_Akala_TotemBattle_Trigger_1
	end

Alola_Akala_TotemBattle_Trigger_1:
# 74 "data/maps/AlolaIslandRight_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_AKALA, Alola_Akala_TotemBattle_Trigger_7
Alola_Akala_TotemBattle_Trigger_5:
	end

Alola_Akala_TotemBattle_Trigger_4:
# 76 "data/maps/AlolaIslandRight_hns/scripts.pory"
	lock
# 77 "data/maps/AlolaIslandRight_hns/scripts.pory"
	delay 30
# 78 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setvar VAR_0x8004, 2
# 79 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setvar VAR_0x8005, 6
# 80 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setvar VAR_0x8006, 4
# 81 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setvar VAR_0x8007, 4
# 82 "data/maps/AlolaIslandRight_hns/scripts.pory"
	special ShakeCamera
# 83 "data/maps/AlolaIslandRight_hns/scripts.pory"
	waitstate
# 84 "data/maps/AlolaIslandRight_hns/scripts.pory"
	fadescreenswapbuffers FADE_TO_BLACK
# 85 "data/maps/AlolaIslandRight_hns/scripts.pory"
	delay 30
# 86 "data/maps/AlolaIslandRight_hns/scripts.pory"
	clearflag FLAG_HIDE_AKALA_TOTEM
# 87 "data/maps/AlolaIslandRight_hns/scripts.pory"
	gettimeofday
# 88 "data/maps/AlolaIslandRight_hns/scripts.pory"
	compare VAR_0x8000, TIME_MORNING
	goto_if_eq Alola_Akala_TotemBattle_Trigger_14
# 88 "data/maps/AlolaIslandRight_hns/scripts.pory"
	compare VAR_0x8000, TIME_DAY
	goto_if_eq Alola_Akala_TotemBattle_Trigger_14
# 97 "data/maps/AlolaIslandRight_hns/scripts.pory"
	playmoncry SPECIES_SALAZZLE, 0
# 98 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setvar VAR_OBJ_GFX_ID_1, OBJ_EVENT_GFX_SPECIES ( SALAZZLE )
# 99 "data/maps/AlolaIslandRight_hns/scripts.pory"
	addobject Akala_Totem
# 100 "data/maps/AlolaIslandRight_hns/scripts.pory"
	waitmoncry
Alola_Akala_TotemBattle_Trigger_13:
# 102 "data/maps/AlolaIslandRight_hns/scripts.pory"
	special DrawWholeMapView
# 103 "data/maps/AlolaIslandRight_hns/scripts.pory"
	delay 30
# 104 "data/maps/AlolaIslandRight_hns/scripts.pory"
	fadescreenswapbuffers FADE_FROM_BLACK
# 105 "data/maps/AlolaIslandRight_hns/scripts.pory"
	delay 30
# 106 "data/maps/AlolaIslandRight_hns/scripts.pory"
	gettimeofday
# 107 "data/maps/AlolaIslandRight_hns/scripts.pory"
	compare VAR_0x8000, TIME_MORNING
	goto_if_eq Alola_Akala_TotemBattle_Trigger_20
# 107 "data/maps/AlolaIslandRight_hns/scripts.pory"
	compare VAR_0x8000, TIME_DAY
	goto_if_eq Alola_Akala_TotemBattle_Trigger_20
# 116 "data/maps/AlolaIslandRight_hns/scripts.pory"
	playmoncry SPECIES_SALAZZLE, 0
# 117 "data/maps/AlolaIslandRight_hns/scripts.pory"
	applymovement Akala_Totem, Alola_Akala_TotemBattle_Trigger_Movement_0
# 118 "data/maps/AlolaIslandRight_hns/scripts.pory"
	waitmovement 0
# 119 "data/maps/AlolaIslandRight_hns/scripts.pory"
	waitmoncry
Alola_Akala_TotemBattle_Trigger_19:
# 121 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setflag FLAG_TRIGGERED_AKALA_TOTEM
# 122 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end

Alola_Akala_TotemBattle_Trigger_6:
# 74 "data/maps/AlolaIslandRight_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_PONI, Alola_Akala_TotemBattle_Trigger_10
	goto Alola_Akala_TotemBattle_Trigger_5

Alola_Akala_TotemBattle_Trigger_7:
# 74 "data/maps/AlolaIslandRight_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_ULAULA, Alola_Akala_TotemBattle_Trigger_6
	goto Alola_Akala_TotemBattle_Trigger_5

Alola_Akala_TotemBattle_Trigger_10:
# 74 "data/maps/AlolaIslandRight_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_MELEMELE, Alola_Akala_TotemBattle_Trigger_4
	goto Alola_Akala_TotemBattle_Trigger_5

Alola_Akala_TotemBattle_Trigger_14:
# 90 "data/maps/AlolaIslandRight_hns/scripts.pory"
	playmoncry SPECIES_ARAQUANID, 0
# 91 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setvar VAR_OBJ_GFX_ID_1, OBJ_EVENT_GFX_SPECIES ( ARAQUANID )
# 92 "data/maps/AlolaIslandRight_hns/scripts.pory"
	addobject Akala_Totem
# 93 "data/maps/AlolaIslandRight_hns/scripts.pory"
	waitmoncry
	goto Alola_Akala_TotemBattle_Trigger_13

Alola_Akala_TotemBattle_Trigger_20:
# 109 "data/maps/AlolaIslandRight_hns/scripts.pory"
	playmoncry SPECIES_ARAQUANID, 0
# 110 "data/maps/AlolaIslandRight_hns/scripts.pory"
	applymovement Akala_Totem, Alola_Akala_TotemBattle_Trigger_Movement_0
# 111 "data/maps/AlolaIslandRight_hns/scripts.pory"
	waitmovement 0
# 112 "data/maps/AlolaIslandRight_hns/scripts.pory"
	waitmoncry
	goto Alola_Akala_TotemBattle_Trigger_19


Alola_Akala_TotemBattle::
# 137 "data/maps/AlolaIslandRight_hns/scripts.pory"
	lock
# 138 "data/maps/AlolaIslandRight_hns/scripts.pory"
	faceplayer
# 139 "data/maps/AlolaIslandRight_hns/scripts.pory"
	gettimeofday
# 140 "data/maps/AlolaIslandRight_hns/scripts.pory"
	compare VAR_0x8000, TIME_MORNING
	goto_if_eq Alola_Akala_TotemBattle_1
# 140 "data/maps/AlolaIslandRight_hns/scripts.pory"
	compare VAR_0x8000, TIME_DAY
	goto_if_eq Alola_Akala_TotemBattle_1
# 168 "data/maps/AlolaIslandRight_hns/scripts.pory"
	playmoncry SPECIES_SALAZZLE, 0
# 169 "data/maps/AlolaIslandRight_hns/scripts.pory"
	msgbox Alola_Akala_TotemBattle_Text_0, MSGBOX_AUTOCLOSE
# 170 "data/maps/AlolaIslandRight_hns/scripts.pory"
	waitmoncry
# 171 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setwildbattle SPECIES_SALANDIT, 60, ITEM_NONE, SPECIES_SALAZZLE_TOTEM, 60, ITEM_PETAYA_BERRY
# 172 "data/maps/AlolaIslandRight_hns/scripts.pory"
	settotemboost B_POSITION_OPPONENT_RIGHT, 0, 0, 0, 0, 1
# 173 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setflag FLAG_NO_WILD_CATCHING
# 174 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setflag FLAG_NO_WILD_RUNNING
# 175 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setflag FLAG_SMART_WILD_AI
# 176 "data/maps/AlolaIslandRight_hns/scripts.pory"
	dowildbattle
# 177 "data/maps/AlolaIslandRight_hns/scripts.pory"
	specialvar VAR_RESULT, GetBattleOutcome
# 178 "data/maps/AlolaIslandRight_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq Alola_Akala_TotemBattle_9
# 191 "data/maps/AlolaIslandRight_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_LOST
	goto_if_eq Alola_Akala_TotemBattle_11
	return

Alola_Akala_TotemBattle_1:
# 142 "data/maps/AlolaIslandRight_hns/scripts.pory"
	playmoncry SPECIES_ARAQUANID, 0
# 143 "data/maps/AlolaIslandRight_hns/scripts.pory"
	msgbox Alola_Akala_TotemBattle_Text_0, MSGBOX_AUTOCLOSE
# 144 "data/maps/AlolaIslandRight_hns/scripts.pory"
	waitmoncry
# 146 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setwildbattle SPECIES_DEWPIDER, 60, ITEM_NONE, SPECIES_ARAQUANID_TOTEM, 60, ITEM_SITRUS_BERRY
# 147 "data/maps/AlolaIslandRight_hns/scripts.pory"
	settotemboost B_POSITION_OPPONENT_RIGHT, 0, 0, 0, 0, 1
# 148 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setflag FLAG_NO_WILD_CATCHING
# 149 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setflag FLAG_NO_WILD_RUNNING
# 150 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setflag FLAG_SMART_WILD_AI
# 151 "data/maps/AlolaIslandRight_hns/scripts.pory"
	dowildbattle
# 152 "data/maps/AlolaIslandRight_hns/scripts.pory"
	specialvar VAR_RESULT, GetBattleOutcome
# 153 "data/maps/AlolaIslandRight_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq Alola_Akala_TotemBattle_6
	return

Alola_Akala_TotemBattle_6:
# 154 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setflag FLAG_HIDE_AKALA_TOTEM
# 155 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setflag FLAG_DEFEATED_AKALA_TOTEM
# 156 "data/maps/AlolaIslandRight_hns/scripts.pory"
	removeobject Akala_Totem
# 157 "data/maps/AlolaIslandRight_hns/scripts.pory"
	msgbox Alola_Akala_TotemBattle_Text_1, MSGBOX_AUTOCLOSE
# 159 "data/maps/AlolaIslandRight_hns/scripts.pory"
	clearflag FLAG_NO_WILD_CATCHING
# 160 "data/maps/AlolaIslandRight_hns/scripts.pory"
	clearflag FLAG_NO_WILD_RUNNING
# 161 "data/maps/AlolaIslandRight_hns/scripts.pory"
	clearflag FLAG_SMART_WILD_AI
# 162 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end

Alola_Akala_TotemBattle_9:
# 180 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setflag FLAG_HIDE_AKALA_TOTEM
# 181 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setflag FLAG_DEFEATED_AKALA_TOTEM
# 182 "data/maps/AlolaIslandRight_hns/scripts.pory"
	removeobject Akala_Totem
# 183 "data/maps/AlolaIslandRight_hns/scripts.pory"
	msgbox Alola_Akala_TotemBattle_Text_2, MSGBOX_AUTOCLOSE
# 185 "data/maps/AlolaIslandRight_hns/scripts.pory"
	clearflag FLAG_NO_WILD_CATCHING
# 186 "data/maps/AlolaIslandRight_hns/scripts.pory"
	clearflag FLAG_NO_WILD_RUNNING
# 187 "data/maps/AlolaIslandRight_hns/scripts.pory"
	clearflag FLAG_SMART_WILD_AI
# 188 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end

Alola_Akala_TotemBattle_11:
# 192 "data/maps/AlolaIslandRight_hns/scripts.pory"
	clearflag FLAG_NO_WILD_CATCHING
# 193 "data/maps/AlolaIslandRight_hns/scripts.pory"
	clearflag FLAG_NO_WILD_RUNNING
# 194 "data/maps/AlolaIslandRight_hns/scripts.pory"
	clearflag FLAG_SMART_WILD_AI
# 195 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end


Alola_Akala_Totem_sign::
# 202 "data/maps/AlolaIslandRight_hns/scripts.pory"
	lock
# 203 "data/maps/AlolaIslandRight_hns/scripts.pory"
	msgbox Alola_Akala_Totem_sign_Text_0, MSGBOX_AUTOCLOSE
# 205 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end


Alola_Akala_TapuLele_Flyover::
# 210 "data/maps/AlolaIslandRight_hns/scripts.pory"
	goto_if_set FLAG_FLYOVER_TAPU_LELE, Alola_Akala_TapuLele_Flyover_2
# 223 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end

Alola_Akala_TapuLele_Flyover_2:
# 212 "data/maps/AlolaIslandRight_hns/scripts.pory"
	addobject Akala_Flyover_Tapu
# 213 "data/maps/AlolaIslandRight_hns/scripts.pory"
	playse SE_M_FLY
# 214 "data/maps/AlolaIslandRight_hns/scripts.pory"
	applymovement Akala_Flyover_Tapu, Alola_Akala_TapuLele_Flyover_Movement_0
# 215 "data/maps/AlolaIslandRight_hns/scripts.pory"
	waitmovement 0
# 216 "data/maps/AlolaIslandRight_hns/scripts.pory"
	removeobject Akala_Flyover_Tapu
# 217 "data/maps/AlolaIslandRight_hns/scripts.pory"
	clearflag FLAG_FLYOVER_TAPU_LELE
# 218 "data/maps/AlolaIslandRight_hns/scripts.pory"
	clearflag FLAG_HIDE_TAPU_LELE
# 219 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end


Alola_Akala_BattleVsTapuLele::
# 228 "data/maps/AlolaIslandRight_hns/scripts.pory"
	lock
# 229 "data/maps/AlolaIslandRight_hns/scripts.pory"
	faceplayer
# 230 "data/maps/AlolaIslandRight_hns/scripts.pory"
	playmoncry SPECIES_TAPU_LELE, 0
# 231 "data/maps/AlolaIslandRight_hns/scripts.pory"
	applymovement Akala_Tapu, Alola_Akala_TotemBattle_Trigger_Movement_0
# 232 "data/maps/AlolaIslandRight_hns/scripts.pory"
	msgbox Alola_Akala_BattleVsTapuLele_Text_0
# 233 "data/maps/AlolaIslandRight_hns/scripts.pory"
	waitmovement 0
# 234 "data/maps/AlolaIslandRight_hns/scripts.pory"
	waitmoncry
# 235 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setwildbattle SPECIES_TAPU_LELE, 60
# 236 "data/maps/AlolaIslandRight_hns/scripts.pory"
	dowildbattle
# 237 "data/maps/AlolaIslandRight_hns/scripts.pory"
	specialvar VAR_RESULT, GetBattleOutcome
# 238 "data/maps/AlolaIslandRight_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_CAUGHT
	goto_if_eq Alola_Akala_BattleVsTapuLele_2
# 245 "data/maps/AlolaIslandRight_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq Alola_Akala_BattleVsTapuLele_3
# 253 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end

# 256 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end

Alola_Akala_BattleVsTapuLele_2:
# 239 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setflag FLAG_HIDE_TAPU_LELE
# 240 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setflag FLAG_BATTLED_TAPU_LELE
# 241 "data/maps/AlolaIslandRight_hns/scripts.pory"
	removeobject Akala_Tapu
# 242 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end

Alola_Akala_BattleVsTapuLele_3:
# 246 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setflag FLAG_HIDE_TAPU_LELE
# 247 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setflag FLAG_BATTLED_TAPU_LELE
# 248 "data/maps/AlolaIslandRight_hns/scripts.pory"
	removeobject Akala_Tapu
# 249 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end


# 110 "data/maps/AlolaIslandRight_hns/scripts.pory"
Alola_Akala_TotemBattle_Trigger_Movement_0:
# 110 "data/maps/AlolaIslandRight_hns/scripts.pory"
	walk_in_place_down
# 110 "data/maps/AlolaIslandRight_hns/scripts.pory"
	walk_in_place_down
	step_end

# 214 "data/maps/AlolaIslandRight_hns/scripts.pory"
Alola_Akala_TapuLele_Flyover_Movement_0:
# 214 "data/maps/AlolaIslandRight_hns/scripts.pory"
	walk_faster_left
# 214 "data/maps/AlolaIslandRight_hns/scripts.pory"
	walk_faster_left
# 214 "data/maps/AlolaIslandRight_hns/scripts.pory"
	walk_faster_left
# 214 "data/maps/AlolaIslandRight_hns/scripts.pory"
	walk_faster_left
# 214 "data/maps/AlolaIslandRight_hns/scripts.pory"
	walk_faster_left
# 214 "data/maps/AlolaIslandRight_hns/scripts.pory"
	walk_faster_left
# 214 "data/maps/AlolaIslandRight_hns/scripts.pory"
	walk_faster_left
# 214 "data/maps/AlolaIslandRight_hns/scripts.pory"
	walk_faster_left
# 214 "data/maps/AlolaIslandRight_hns/scripts.pory"
	walk_faster_left
# 214 "data/maps/AlolaIslandRight_hns/scripts.pory"
	walk_faster_left
# 214 "data/maps/AlolaIslandRight_hns/scripts.pory"
	walk_faster_left
# 214 "data/maps/AlolaIslandRight_hns/scripts.pory"
	walk_faster_left
# 214 "data/maps/AlolaIslandRight_hns/scripts.pory"
	walk_faster_left
# 214 "data/maps/AlolaIslandRight_hns/scripts.pory"
	walk_faster_left
# 214 "data/maps/AlolaIslandRight_hns/scripts.pory"
	walk_faster_left
# 214 "data/maps/AlolaIslandRight_hns/scripts.pory"
	walk_faster_left
# 214 "data/maps/AlolaIslandRight_hns/scripts.pory"
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

Alola_Akala_TotemBattle_Text_0:
# 143 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "Thhhh!$"

Alola_Akala_TotemBattle_Text_1:
# 157 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "Totem Araquanid was defeated!\n"
	.string "It scampered off somewhere…$"

Alola_Akala_TotemBattle_Text_2:
# 183 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "Totem Salazzle was defeated!\n"
	.string "It scampered off somewhere…$"

Alola_Akala_Totem_sign_Text_0:
# 203 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "A strange totem stands here,\n"
	.string "power is emanating from it…$"

Alola_Akala_BattleVsTapuLele_Text_0:
# 232 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "Graah!$"
