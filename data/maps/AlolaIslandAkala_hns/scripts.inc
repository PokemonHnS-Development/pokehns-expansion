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
# 51 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	release
	end


Alola_Ulaula_UlaulaSign::
# 56 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	lock
# 57 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	msgbox Alola_Ulaula_UlaulaSign_Text_0
# 58 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	release
	end


Alola_Ulaula_TapuBulu_Flyover::
# 63 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	goto_if_set FLAG_FLYOVER_TAPU_BULU, Alola_Ulaula_TapuBulu_Flyover_2
# 76 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	release
	end

Alola_Ulaula_TapuBulu_Flyover_2:
# 65 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	addobject Ulaula_Flyover_Tapu
# 66 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	playse SE_M_FLY
# 67 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	applymovement Ulaula_Flyover_Tapu, Alola_Ulaula_TapuBulu_Flyover_Movement_0
# 68 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	waitmovement 0
# 69 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	removeobject Ulaula_Flyover_Tapu
# 70 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	clearflag FLAG_FLYOVER_TAPU_BULU
# 71 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	clearflag FLAG_HIDE_TAPU_BULU
# 72 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	release
	end


Alola_Ulaula_Phant_outside::
# 81 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	lock
# 82 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	faceplayer
# 83 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	hidefollower
# 84 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	msgbox Alola_Ulaula_Phant_outside_Text_0, MSGBOX_AUTOCLOSE
# 96 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	getplayerxy VAR_TEMP_0, VAR_TEMP_1
# 97 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	compare VAR_TEMP_0, 35
	goto_if_eq Alola_Ulaula_Phant_outside_3
Alola_Ulaula_Phant_outside_1:
# 101 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	compare VAR_TEMP_0, 36
	goto_if_eq Alola_Ulaula_Phant_outside_8
Alola_Ulaula_Phant_outside_6:
# 105 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	compare VAR_TEMP_0, 37
	goto_if_eq Alola_Ulaula_Phant_outside_13
Alola_Ulaula_Phant_outside_11:
# 109 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	compare VAR_TEMP_0, 36
	goto_if_eq Alola_Ulaula_Phant_outside_18
Alola_Ulaula_Phant_outside_16:
# 113 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	playse SE_LEDGE
# 114 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	waitse
# 115 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	playse SE_LEDGE
# 116 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	waitse
# 117 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	msgbox Alola_Ulaula_Phant_outside_Text_1, MSGBOX_AUTOCLOSE
# 120 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	getplayerxy VAR_TEMP_0, VAR_TEMP_1
# 121 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	compare VAR_TEMP_0, 35
	goto_if_eq Alola_Ulaula_Phant_outside_23
Alola_Ulaula_Phant_outside_22:
# 137 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	applymovement Phant_Outside, Alola_Ulaula_Phant_outside_Movement_6
# 138 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	waitmovement 0
# 139 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	playmoncry SPECIES_NOIVERN, 0
# 140 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	applymovement Phant_Noivern_Outside, Alola_Ulaula_Phant_outside_Movement_5
# 141 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	waitmovement 0
# 142 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	removeobject Phant_Noivern_Outside
# 143 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	removeobject Phant_Outside
# 144 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	setflag FLAG_HIDE_PHANT_OUTSIDE
# 145 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	clearflag FLAG_HIDE_PHANT_INSIDE
# 146 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	release
	end

Alola_Ulaula_Phant_outside_2:
# 99 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	applymovement Phant_Outside, Alola_Ulaula_Phant_outside_Movement_0
	goto Alola_Ulaula_Phant_outside_1

Alola_Ulaula_Phant_outside_3:
# 97 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	compare VAR_TEMP_1, 46
	goto_if_eq Alola_Ulaula_Phant_outside_2
	goto Alola_Ulaula_Phant_outside_1

Alola_Ulaula_Phant_outside_7:
# 103 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	applymovement Phant_Outside, Alola_Ulaula_Phant_outside_Movement_1
	goto Alola_Ulaula_Phant_outside_6

Alola_Ulaula_Phant_outside_8:
# 101 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	compare VAR_TEMP_1, 47
	goto_if_eq Alola_Ulaula_Phant_outside_7
	goto Alola_Ulaula_Phant_outside_6

Alola_Ulaula_Phant_outside_12:
# 107 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	applymovement Phant_Outside, Alola_Ulaula_Phant_outside_Movement_2
	goto Alola_Ulaula_Phant_outside_11

Alola_Ulaula_Phant_outside_13:
# 105 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	compare VAR_TEMP_1, 46
	goto_if_eq Alola_Ulaula_Phant_outside_12
	goto Alola_Ulaula_Phant_outside_11

Alola_Ulaula_Phant_outside_17:
# 111 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	applymovement Phant_Outside, Alola_Ulaula_Phant_outside_Movement_3
	goto Alola_Ulaula_Phant_outside_16

Alola_Ulaula_Phant_outside_18:
# 109 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	compare VAR_TEMP_1, 45
	goto_if_eq Alola_Ulaula_Phant_outside_17
	goto Alola_Ulaula_Phant_outside_16

Alola_Ulaula_Phant_outside_21:
# 123 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	applymovement Phant_Outside, Alola_Ulaula_Phant_outside_Movement_4
# 124 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	waitmovement 0
# 125 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	playmoncry SPECIES_NOIVERN, 0
# 126 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	applymovement Phant_Noivern_Outside, Alola_Ulaula_Phant_outside_Movement_5
# 127 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	waitmovement 0
# 128 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	removeobject Phant_Noivern_Outside
# 129 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	removeobject Phant_Outside
# 130 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	setflag FLAG_HIDE_PHANT_OUTSIDE
# 131 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	clearflag FLAG_HIDE_PHANT_INSIDE
# 132 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	release
	end

Alola_Ulaula_Phant_outside_23:
# 121 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	compare VAR_TEMP_1, 46
	goto_if_eq Alola_Ulaula_Phant_outside_21
	goto Alola_Ulaula_Phant_outside_22


Alola_Ulaula_TrainerBattlePicnicker::
# 153 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	trainerbattle_single TRAINER_ULAULA_PICNICKER_HNS, Alola_Ulaula_TrainerBattlePicnicker_Text_0, Alola_Ulaula_TrainerBattlePicnicker_Text_1
# 154 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	msgbox Alola_Ulaula_TrainerBattlePicnicker_Text_2, MSGBOX_AUTOCLOSE
# 158 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	release
	end


Alola_Ulaula_TrainerBattleYoungster::
# 163 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	trainerbattle_single TRAINER_ULAULA_YOUNGSTER_HNS, Alola_Ulaula_TrainerBattleYoungster_Text_0, Alola_Ulaula_TrainerBattleYoungster_Text_1
# 164 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	msgbox Alola_Ulaula_TrainerBattleYoungster_Text_2, MSGBOX_AUTOCLOSE
# 168 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	release
	end


Alola_Ulaula_TrainerBattleHiker::
# 173 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	trainerbattle_single TRAINER_ULAULA_HIKER_HNS, Alola_Ulaula_TrainerBattleHiker_Text_0, Alola_Ulaula_TrainerBattleHiker_Text_1
# 174 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	msgbox Alola_Ulaula_TrainerBattleHiker_Text_2, MSGBOX_AUTOCLOSE
# 179 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	release
	end


Alola_Ulaula_TrainerBattleCooltrainer::
# 184 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	trainerbattle_single TRAINER_ULAULA_COOLTRAINER_HNS, Alola_Ulaula_TrainerBattleCooltrainer_Text_0, Alola_Ulaula_TrainerBattleCooltrainer_Text_1
# 185 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	msgbox Alola_Ulaula_TrainerBattleCooltrainer_Text_2, MSGBOX_AUTOCLOSE
# 187 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	release
	end


Alola_Ulaula_LassNPC::
# 192 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	lock
# 193 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	faceplayer
# 194 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	msgbox Alola_Ulaula_LassNPC_Text_0, MSGBOX_AUTOCLOSE
# 199 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	release
	end


# 67 "data/maps/AlolaIslandAkala_hns/scripts.pory"
Alola_Ulaula_TapuBulu_Flyover_Movement_0:
# 67 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_faster_up
# 67 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_faster_up
# 67 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_faster_up
# 67 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_faster_up
# 67 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_faster_up
# 67 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_faster_up
# 67 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_faster_up
# 67 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_faster_up
# 67 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_faster_up
# 67 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_faster_up
# 67 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_faster_up
# 67 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_faster_up
# 67 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_faster_up
# 67 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_faster_up
	step_end

# 99 "data/maps/AlolaIslandAkala_hns/scripts.pory"
Alola_Ulaula_Phant_outside_Movement_0:
# 99 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	jump_in_place_left
# 99 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	jump_in_place_left
	step_end

# 103 "data/maps/AlolaIslandAkala_hns/scripts.pory"
Alola_Ulaula_Phant_outside_Movement_1:
# 103 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	jump_in_place_down
# 103 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	jump_in_place_down
	step_end

# 107 "data/maps/AlolaIslandAkala_hns/scripts.pory"
Alola_Ulaula_Phant_outside_Movement_2:
# 107 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	jump_in_place_right
# 107 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	jump_in_place_right
	step_end

# 111 "data/maps/AlolaIslandAkala_hns/scripts.pory"
Alola_Ulaula_Phant_outside_Movement_3:
# 111 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	jump_in_place_up
# 111 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	jump_in_place_up
	step_end

# 123 "data/maps/AlolaIslandAkala_hns/scripts.pory"
Alola_Ulaula_Phant_outside_Movement_4:
# 123 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_down
# 123 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_left
# 123 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_left
# 123 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_left
# 123 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_left
# 123 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_left
# 123 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_left
# 123 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_left
# 123 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_left
# 123 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_up
# 123 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_up
# 123 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_up
# 123 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_up
# 123 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_up
# 123 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_up
# 123 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_up
# 123 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_left
# 123 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_left
	step_end

# 126 "data/maps/AlolaIslandAkala_hns/scripts.pory"
Alola_Ulaula_Phant_outside_Movement_5:
# 126 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_fast_left
# 126 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_fast_left
# 126 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_fast_left
# 126 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_fast_left
# 126 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_fast_left
# 126 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_fast_left
# 126 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_fast_left
# 126 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_fast_left
# 126 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_fast_up
# 126 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_fast_up
# 126 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_fast_up
# 126 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_fast_up
# 126 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_fast_up
# 126 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_fast_up
# 126 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_fast_up
	step_end

# 137 "data/maps/AlolaIslandAkala_hns/scripts.pory"
Alola_Ulaula_Phant_outside_Movement_6:
# 137 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_left
# 137 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_left
# 137 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_left
# 137 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_left
# 137 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_left
# 137 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_left
# 137 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_left
# 137 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_left
# 137 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_up
# 137 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	walk_up
	step_end

Alola_Ulaula_BattlePalossand_Text_0:
# 7 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	.string "Gaaah!$"

Alola_Ulaula_MtLanikalaSign_Text_0:
# 44 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	.string "This mountain is affectionately\n"
	.string "referred to as Mt. Lanikala by the\l"
	.string "locals, as it is the tallest mountain\l"
	.string "on the Alola Isles.\p"
	.string "The real name of this mountain has been\n"
	.string "lost to time.$"

Alola_Ulaula_UlaulaSign_Text_0:
# 57 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	.string "Ula'ula Isle$"

Alola_Ulaula_Phant_outside_Text_0:
# 84 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	.string "Hello there, {PLAYER}!\n"
	.string "I'm Phantonomy.\p"
	.string "I'm the developer who built this\n"
	.string "section of the postgame!\p"
	.string "I hope you enjoyed this taste of Alola.\p"
	.string "Look forward to my full demake of\n"
	.string "the region in my own upcoming project{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.\p"
	.string "Ultra Eclipse!$"

Alola_Ulaula_Phant_outside_Text_1:
# 117 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	.string "Please come visit me at my house at\n"
	.string "the top of this Isle for a battle…\l"
	.string "I'll make it worth your while!$"

Alola_Ulaula_TrainerBattlePicnicker_Text_0:
# 153 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	.string "Surprise!\nI was in the trees!$"

Alola_Ulaula_TrainerBattlePicnicker_Text_1:
# 153 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	.string "Back into hiding I go…$"

Alola_Ulaula_TrainerBattlePicnicker_Text_2:
# 154 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	.string "I thought I saw something red flying\n"
	.string "through the sky.\p"
	.string "Could it have been a Pokémon?$"

Alola_Ulaula_TrainerBattleYoungster_Text_0:
# 163 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	.string "Hey, I'm going to be the first to climb\nMt. Lanikala!$"

Alola_Ulaula_TrainerBattleYoungster_Text_1:
# 163 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	.string "It's not even the real Mt. Lanikala…$"

Alola_Ulaula_TrainerBattleYoungster_Text_2:
# 164 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	.string "My dad never told me the real name of\n"
	.string "this mountain.\p"
	.string "We've always just called it Mt. Lanikala.$"

Alola_Ulaula_TrainerBattleHiker_Text_0:
# 173 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	.string "You must be tough to handle this\nrough terrain!$"

Alola_Ulaula_TrainerBattleHiker_Text_1:
# 173 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	.string "Oof,\nI should've trained harder…$"

Alola_Ulaula_TrainerBattleHiker_Text_2:
# 174 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	.string "Ula'ula Isle has the best hiking!\p"
	.string "The locals refer to this mountain as\n"
	.string "Mt. Lanikala, as it is the tallest on\l"
	.string "the Alola Isles!$"

Alola_Ulaula_TrainerBattleCooltrainer_Text_0:
# 184 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	.string "This cave smells terrible!\n Let's battle to get my mind off of it!$"

Alola_Ulaula_TrainerBattleCooltrainer_Text_1:
# 184 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	.string "Should've brought some air freshener…$"

Alola_Ulaula_TrainerBattleCooltrainer_Text_2:
# 185 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	.string "You should plug your nose if you plan\n"
	.string "on going in that cave.$"

Alola_Ulaula_LassNPC_Text_0:
# 194 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	.string "The sea by the Isles is truly\n"
	.string "breathtaking.\p"
	.string "I could sit here all day and just\n"
	.string "watch the waves.$"
