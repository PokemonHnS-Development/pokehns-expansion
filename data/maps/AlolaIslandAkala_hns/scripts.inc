AlolaIslandAkala_hns_MapScripts::
	.byte 0


Alola_Ulaula_BattlePalossand::
# 4 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	lock
# 5 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	faceplayer
# 6 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	playmoncry SPECIES_PALOSSAND, 0
# 7 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	msgbox Alola_Ulaula_BattlePalossand_Text_0, MSGBOX_AUTOCLOSE
# 8 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	waitmoncry
# 9 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	setwildbattle SPECIES_PALOSSAND, 45
# 10 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	dowildbattle
# 11 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	specialvar VAR_RESULT, GetBattleOutcome
# 12 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_CAUGHT
	goto_if_eq Alola_Ulaula_BattlePalossand_2
# 18 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq Alola_Ulaula_BattlePalossand_3
# 25 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	release
	end

# 28 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	release
	end

Alola_Ulaula_BattlePalossand_2:
# 13 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	setflag FLAG_CAUGHT_PALOSSAND
# 14 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	removeobject Alola_Ulaula_Palossand
# 15 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	release
	end

Alola_Ulaula_BattlePalossand_3:
# 19 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	setflag FLAG_CAUGHT_PALOSSAND
# 20 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	removeobject Alola_Ulaula_Palossand
# 21 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	release
	end


Alola_Ulaula_FindItem1::
# 33 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	finditem ITEM_FRIEND_BALL, 1
	end


Alola_Ulaula_FindItem2::
# 38 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	finditem ITEM_PROTEIN, 1
	end


Alola_Ulaula_MtLanikalaSign::
# 43 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	lock
# 44 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	msgbox Alola_Ulaula_MtLanikalaSign_Text_0
# 45 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	release
	end


Alola_Ulaula_UlaulaSign::
# 50 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	lock
# 51 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	msgbox Alola_Ulaula_UlaulaSign_Text_0
# 52 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	release
	end


Alola_Ulaula_TapuBulu_Flyover::
# 57 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	goto_if_set FLAG_FLYOVER_TAPU_BULU, Alola_Ulaula_TapuBulu_Flyover_2
# 70 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	release
	end

Alola_Ulaula_TapuBulu_Flyover_2:
# 59 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	addobject Ulaula_Flyover_Tapu
# 60 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	playse SE_M_FLY
# 61 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	applymovement Ulaula_Flyover_Tapu, Alola_Ulaula_TapuBulu_Flyover_Movement_0
# 62 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	waitmovement 0
# 63 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	removeobject Ulaula_Flyover_Tapu
# 64 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	clearflag FLAG_FLYOVER_TAPU_BULU
# 65 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	clearflag FLAG_HIDE_TAPU_BULU
# 66 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	release
	end


Alola_Ulaula_Phant_outside::
# 75 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	lock
# 76 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	faceplayer
# 77 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	hidefollower
# 78 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	msgbox Alola_Ulaula_Phant_outside_Text_0, MSGBOX_AUTOCLOSE
# 90 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	getplayerxy VAR_TEMP_0, VAR_TEMP_1
# 91 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	compare VAR_TEMP_0, 35
	goto_if_eq Alola_Ulaula_Phant_outside_3
Alola_Ulaula_Phant_outside_1:
# 95 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	compare VAR_TEMP_0, 36
	goto_if_eq Alola_Ulaula_Phant_outside_8
Alola_Ulaula_Phant_outside_6:
# 99 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	compare VAR_TEMP_0, 37
	goto_if_eq Alola_Ulaula_Phant_outside_13
Alola_Ulaula_Phant_outside_11:
# 103 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	compare VAR_TEMP_0, 36
	goto_if_eq Alola_Ulaula_Phant_outside_18
Alola_Ulaula_Phant_outside_16:
# 107 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	playse SE_LEDGE
# 108 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	waitse
# 109 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	playse SE_LEDGE
# 110 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	waitse
# 111 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	msgbox Alola_Ulaula_Phant_outside_Text_1, MSGBOX_AUTOCLOSE
# 114 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	getplayerxy VAR_TEMP_0, VAR_TEMP_1
# 115 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	compare VAR_TEMP_0, 35
	goto_if_eq Alola_Ulaula_Phant_outside_23
Alola_Ulaula_Phant_outside_22:
# 131 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	applymovement Phant_Outside, Alola_Ulaula_Phant_outside_Movement_6
# 132 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	waitmovement 0
# 133 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	playmoncry SPECIES_NOIVERN, 0
# 134 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	applymovement Phant_Noivern_Outside, Alola_Ulaula_Phant_outside_Movement_5
# 135 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	waitmovement 0
# 136 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	removeobject Phant_Noivern_Outside
# 137 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	removeobject Phant_Outside
# 138 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	setflag FLAG_HIDE_PHANT_OUTSIDE
# 139 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	clearflag FLAG_HIDE_PHANT_INSIDE
# 140 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	release
	end

Alola_Ulaula_Phant_outside_2:
# 93 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	applymovement Phant_Outside, Alola_Ulaula_Phant_outside_Movement_0
	goto Alola_Ulaula_Phant_outside_1

Alola_Ulaula_Phant_outside_3:
# 91 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	compare VAR_TEMP_1, 46
	goto_if_eq Alola_Ulaula_Phant_outside_2
	goto Alola_Ulaula_Phant_outside_1

Alola_Ulaula_Phant_outside_7:
# 97 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	applymovement Phant_Outside, Alola_Ulaula_Phant_outside_Movement_1
	goto Alola_Ulaula_Phant_outside_6

Alola_Ulaula_Phant_outside_8:
# 95 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	compare VAR_TEMP_1, 47
	goto_if_eq Alola_Ulaula_Phant_outside_7
	goto Alola_Ulaula_Phant_outside_6

Alola_Ulaula_Phant_outside_12:
# 101 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	applymovement Phant_Outside, Alola_Ulaula_Phant_outside_Movement_2
	goto Alola_Ulaula_Phant_outside_11

Alola_Ulaula_Phant_outside_13:
# 99 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	compare VAR_TEMP_1, 46
	goto_if_eq Alola_Ulaula_Phant_outside_12
	goto Alola_Ulaula_Phant_outside_11

Alola_Ulaula_Phant_outside_17:
# 105 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	applymovement Phant_Outside, Alola_Ulaula_Phant_outside_Movement_3
	goto Alola_Ulaula_Phant_outside_16

Alola_Ulaula_Phant_outside_18:
# 103 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	compare VAR_TEMP_1, 45
	goto_if_eq Alola_Ulaula_Phant_outside_17
	goto Alola_Ulaula_Phant_outside_16

Alola_Ulaula_Phant_outside_21:
# 117 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	applymovement Phant_Outside, Alola_Ulaula_Phant_outside_Movement_4
# 118 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	waitmovement 0
# 119 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	playmoncry SPECIES_NOIVERN, 0
# 120 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	applymovement Phant_Noivern_Outside, Alola_Ulaula_Phant_outside_Movement_5
# 121 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	waitmovement 0
# 122 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	removeobject Phant_Noivern_Outside
# 123 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	removeobject Phant_Outside
# 124 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	setflag FLAG_HIDE_PHANT_OUTSIDE
# 125 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	clearflag FLAG_HIDE_PHANT_INSIDE
# 126 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	release
	end

Alola_Ulaula_Phant_outside_23:
# 115 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	compare VAR_TEMP_1, 46
	goto_if_eq Alola_Ulaula_Phant_outside_21
	goto Alola_Ulaula_Phant_outside_22


Alola_Ulaula_TrainerBattlePicnicker::
# 147 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	trainerbattle_single TRAINER_ULAULA_PICNICKER_HNS, Alola_Ulaula_TrainerBattlePicnicker_Text_0, Alola_Ulaula_TrainerBattlePicnicker_Text_1
# 148 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	msgbox Alola_Ulaula_TrainerBattlePicnicker_Text_2, MSGBOX_AUTOCLOSE
# 152 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	release
	end


Alola_Ulaula_TrainerBattleYoungster::
# 157 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	trainerbattle_single TRAINER_ULAULA_YOUNGSTER_HNS, Alola_Ulaula_TrainerBattleYoungster_Text_0, Alola_Ulaula_TrainerBattleYoungster_Text_1
# 158 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	msgbox Alola_Ulaula_TrainerBattleYoungster_Text_2, MSGBOX_AUTOCLOSE
# 162 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	release
	end


Alola_Ulaula_TrainerBattleHiker::
# 167 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	trainerbattle_single TRAINER_ULAULA_HIKER_HNS, Alola_Ulaula_TrainerBattleHiker_Text_0, Alola_Ulaula_TrainerBattleHiker_Text_1
# 168 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	msgbox Alola_Ulaula_TrainerBattleHiker_Text_2, MSGBOX_AUTOCLOSE
# 173 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	release
	end


Alola_Ulaula_TrainerBattleCooltrainer::
# 178 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	trainerbattle_single TRAINER_ULAULA_COOLTRAINER_HNS, Alola_Ulaula_TrainerBattleCooltrainer_Text_0, Alola_Ulaula_TrainerBattleCooltrainer_Text_1
# 179 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	msgbox Alola_Ulaula_TrainerBattleCooltrainer_Text_2, MSGBOX_AUTOCLOSE
# 181 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	release
	end


Alola_Ulaula_LassNPC::
# 186 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	lock
# 187 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	faceplayer
# 188 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	msgbox Alola_Ulaula_LassNPC_Text_0, MSGBOX_AUTOCLOSE
# 193 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	release
	end


# 61 "data/maps/AlolaIslandAkala_hns/scripts.pory"
Alola_Ulaula_TapuBulu_Flyover_Movement_0:
# 61 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_faster_up
# 61 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_faster_up
# 61 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_faster_up
# 61 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_faster_up
# 61 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_faster_up
# 61 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_faster_up
# 61 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_faster_up
# 61 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_faster_up
# 61 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_faster_up
# 61 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_faster_up
# 61 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_faster_up
# 61 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_faster_up
# 61 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_faster_up
# 61 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_faster_up
	step_end

# 93 "data/maps/AlolaIslandAkala_hns/scripts.pory"
Alola_Ulaula_Phant_outside_Movement_0:
# 93 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	jump_in_place_left
# 93 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	jump_in_place_left
	step_end

# 97 "data/maps/AlolaIslandAkala_hns/scripts.pory"
Alola_Ulaula_Phant_outside_Movement_1:
# 97 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	jump_in_place_down
# 97 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	jump_in_place_down
	step_end

# 101 "data/maps/AlolaIslandAkala_hns/scripts.pory"
Alola_Ulaula_Phant_outside_Movement_2:
# 101 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	jump_in_place_right
# 101 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	jump_in_place_right
	step_end

# 105 "data/maps/AlolaIslandAkala_hns/scripts.pory"
Alola_Ulaula_Phant_outside_Movement_3:
# 105 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	jump_in_place_up
# 105 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	jump_in_place_up
	step_end

# 117 "data/maps/AlolaIslandAkala_hns/scripts.pory"
Alola_Ulaula_Phant_outside_Movement_4:
# 117 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_down
# 117 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_left
# 117 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_left
# 117 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_left
# 117 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_left
# 117 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_left
# 117 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_left
# 117 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_left
# 117 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_left
# 117 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_up
# 117 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_up
# 117 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_up
# 117 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_up
# 117 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_up
# 117 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_up
# 117 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_up
# 117 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_left
# 117 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_left
	step_end

# 120 "data/maps/AlolaIslandAkala_hns/scripts.pory"
Alola_Ulaula_Phant_outside_Movement_5:
# 120 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_fast_left
# 120 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_fast_left
# 120 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_fast_left
# 120 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_fast_left
# 120 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_fast_left
# 120 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_fast_left
# 120 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_fast_left
# 120 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_fast_left
# 120 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_fast_up
# 120 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_fast_up
# 120 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_fast_up
# 120 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_fast_up
# 120 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_fast_up
# 120 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_fast_up
# 120 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_fast_up
	step_end

# 131 "data/maps/AlolaIslandAkala_hns/scripts.pory"
Alola_Ulaula_Phant_outside_Movement_6:
# 131 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_left
# 131 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_left
# 131 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_left
# 131 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_left
# 131 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_left
# 131 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_left
# 131 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_left
# 131 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_left
# 131 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_up
# 131 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_up
	step_end

Alola_Ulaula_BattlePalossand_Text_0:
# 7 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	.string "Gaaah!$"

Alola_Ulaula_MtLanikalaSign_Text_0:
# 44 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	.string "Mt. Lanakila$"

Alola_Ulaula_UlaulaSign_Text_0:
# 51 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	.string "Ula'ula Isle$"

Alola_Ulaula_Phant_outside_Text_0:
# 78 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	.string "Hello there, {PLAYER}!\n"
	.string "I'm Phantonomy.\p"
	.string "I'm the developer who built this\n"
	.string "section of the postgame!\p"
	.string "I hope you enjoyed this taste of Alola.\p"
	.string "Look forward to my full demake of\n"
	.string "the region in my own upcoming project{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.\p"
	.string "Ultra Eclipse!$"

Alola_Ulaula_Phant_outside_Text_1:
# 111 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	.string "Please come visit me at my house at\n"
	.string "the top of this Isle for a battle…\l"
	.string "I'll make it worth your while!$"

Alola_Ulaula_TrainerBattlePicnicker_Text_0:
# 147 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	.string "Surprise!\nI was in the trees!$"

Alola_Ulaula_TrainerBattlePicnicker_Text_1:
# 147 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	.string "Back into hiding I go…$"

Alola_Ulaula_TrainerBattlePicnicker_Text_2:
# 148 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	.string "I thought I saw something red flying\n"
	.string "through the sky.\p"
	.string "Could it have been a Pokémon?$"

Alola_Ulaula_TrainerBattleYoungster_Text_0:
# 157 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	.string "Hey, I'm going to be the first to climb\nMt. Lanikala!$"

Alola_Ulaula_TrainerBattleYoungster_Text_1:
# 157 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	.string "It's not even the real Mt. Lanikala…$"

Alola_Ulaula_TrainerBattleYoungster_Text_2:
# 158 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	.string "My dad never told me the real name of\n"
	.string "this mountain.\p"
	.string "We've always just called it Mt. Lanikala.$"

Alola_Ulaula_TrainerBattleHiker_Text_0:
# 167 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	.string "You must be tough to handle this\nrough terrain!$"

Alola_Ulaula_TrainerBattleHiker_Text_1:
# 167 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	.string "Oof,\nI should've trained harder…$"

Alola_Ulaula_TrainerBattleHiker_Text_2:
# 168 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	.string "Ula'ula Isle has the best hiking!\p"
	.string "The locals refer to this mountain as\n"
	.string "Mt. Lanikala, as it is the tallest on\l"
	.string "the Alola Isles!$"

Alola_Ulaula_TrainerBattleCooltrainer_Text_0:
# 178 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	.string "This cave smells terrible!\n Let's battle to get my mind off of it!$"

Alola_Ulaula_TrainerBattleCooltrainer_Text_1:
# 178 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	.string "Should've brought some air freshener…$"

Alola_Ulaula_TrainerBattleCooltrainer_Text_2:
# 179 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	.string "You should plug your nose if you plan\n"
	.string "on going in that cave.$"

Alola_Ulaula_LassNPC_Text_0:
# 188 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	.string "The sea by the Isles is truly\n"
	.string "breathtaking.\p"
	.string "I could sit here all day and just\n"
	.string "watch the waves.$"
