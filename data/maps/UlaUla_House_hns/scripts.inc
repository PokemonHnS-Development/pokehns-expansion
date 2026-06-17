UlaUla_House_hns_MapScripts::
	.byte 0


Alola_Ulaula_House_Phant::
# 4 "data/maps/UlaUla_House_hns/scripts.pory"
	lock
# 5 "data/maps/UlaUla_House_hns/scripts.pory"
	faceplayer
# 6 "data/maps/UlaUla_House_hns/scripts.pory"
	compare VAR_ALOLA_STATE, 4
	goto_if_eq Alola_Ulaula_House_Phant_1
# 80 "data/maps/UlaUla_House_hns/scripts.pory"
	msgbox Alola_Ulaula_House_Phant_Text_7, MSGBOX_AUTOCLOSE
# 86 "data/maps/UlaUla_House_hns/scripts.pory"
	release
	end

Alola_Ulaula_House_Phant_1:
# 8 "data/maps/UlaUla_House_hns/scripts.pory"
	msgbox Alola_Ulaula_House_Phant_Text_0, MSGBOX_YESNO
# 13 "data/maps/UlaUla_House_hns/scripts.pory"
	compare VAR_RESULT, YES
	goto_if_eq Alola_Ulaula_House_Phant_4
# 72 "data/maps/UlaUla_House_hns/scripts.pory"
	msgbox Alola_Ulaula_House_Phant_Text_6, MSGBOX_AUTOCLOSE
# 74 "data/maps/UlaUla_House_hns/scripts.pory"
	release
	end

Alola_Ulaula_House_Phant_4:
# 15 "data/maps/UlaUla_House_hns/scripts.pory"
	msgbox Alola_Ulaula_House_Phant_Text_1, MSGBOX_AUTOCLOSE
# 17 "data/maps/UlaUla_House_hns/scripts.pory"
	trainerbattle_no_intro TRAINER_PHANTONOMY_HNS, Alola_Ulaula_House_Phant_Text_2
# 18 "data/maps/UlaUla_House_hns/scripts.pory"
	special HealPlayerParty
# 19 "data/maps/UlaUla_House_hns/scripts.pory"
	setvar VAR_ALOLA_STATE, 5
# 20 "data/maps/UlaUla_House_hns/scripts.pory"
	msgbox Alola_Ulaula_House_Phant_Text_3
# 23 "data/maps/UlaUla_House_hns/scripts.pory"
	getplayerxy VAR_TEMP_1, VAR_TEMP_2
# 24 "data/maps/UlaUla_House_hns/scripts.pory"
	compare VAR_TEMP_1, 8
	goto_if_eq Alola_Ulaula_House_Phant_9
Alola_Ulaula_House_Phant_7:
# 30 "data/maps/UlaUla_House_hns/scripts.pory"
	compare VAR_TEMP_1, 9
	goto_if_eq Alola_Ulaula_House_Phant_14
Alola_Ulaula_House_Phant_12:
# 36 "data/maps/UlaUla_House_hns/scripts.pory"
	compare VAR_TEMP_1, 8
	goto_if_eq Alola_Ulaula_House_Phant_19
Alola_Ulaula_House_Phant_17:
# 42 "data/maps/UlaUla_House_hns/scripts.pory"
	giveegg SPECIES_NOIBAT
# 43 "data/maps/UlaUla_House_hns/scripts.pory"
	playfanfare MUS_HG_OBTAIN_EGG
# 44 "data/maps/UlaUla_House_hns/scripts.pory"
	msgbox Alola_Ulaula_House_Phant_Text_4
# 45 "data/maps/UlaUla_House_hns/scripts.pory"
	waitfanfare
# 46 "data/maps/UlaUla_House_hns/scripts.pory"
	compare VAR_TEMP_1, 8
	goto_if_eq Alola_Ulaula_House_Phant_24
Alola_Ulaula_House_Phant_22:
# 51 "data/maps/UlaUla_House_hns/scripts.pory"
	compare VAR_TEMP_1, 9
	goto_if_eq Alola_Ulaula_House_Phant_29
Alola_Ulaula_House_Phant_27:
# 56 "data/maps/UlaUla_House_hns/scripts.pory"
	compare VAR_TEMP_1, 8
	goto_if_eq Alola_Ulaula_House_Phant_34
Alola_Ulaula_House_Phant_32:
# 61 "data/maps/UlaUla_House_hns/scripts.pory"
	playse SE_LEDGE
# 62 "data/maps/UlaUla_House_hns/scripts.pory"
	waitse
# 63 "data/maps/UlaUla_House_hns/scripts.pory"
	playse SE_LEDGE
# 64 "data/maps/UlaUla_House_hns/scripts.pory"
	waitse
# 65 "data/maps/UlaUla_House_hns/scripts.pory"
	msgbox Alola_Ulaula_House_Phant_Text_5, MSGBOX_AUTOCLOSE
# 67 "data/maps/UlaUla_House_hns/scripts.pory"
	release
	end

Alola_Ulaula_House_Phant_8:
# 26 "data/maps/UlaUla_House_hns/scripts.pory"
	applymovement Phantonomy, Alola_Ulaula_House_Phant_Movement_0
# 27 "data/maps/UlaUla_House_hns/scripts.pory"
	waitmovement 0
# 28 "data/maps/UlaUla_House_hns/scripts.pory"
	delay 30
	goto Alola_Ulaula_House_Phant_7

Alola_Ulaula_House_Phant_9:
# 24 "data/maps/UlaUla_House_hns/scripts.pory"
	compare VAR_TEMP_2, 10
	goto_if_eq Alola_Ulaula_House_Phant_8
	goto Alola_Ulaula_House_Phant_7

Alola_Ulaula_House_Phant_13:
# 32 "data/maps/UlaUla_House_hns/scripts.pory"
	applymovement Phantonomy, Alola_Ulaula_House_Phant_Movement_1
# 33 "data/maps/UlaUla_House_hns/scripts.pory"
	waitmovement 0
# 34 "data/maps/UlaUla_House_hns/scripts.pory"
	delay 30
	goto Alola_Ulaula_House_Phant_12

Alola_Ulaula_House_Phant_14:
# 30 "data/maps/UlaUla_House_hns/scripts.pory"
	compare VAR_TEMP_2, 9
	goto_if_eq Alola_Ulaula_House_Phant_13
	goto Alola_Ulaula_House_Phant_12

Alola_Ulaula_House_Phant_18:
# 38 "data/maps/UlaUla_House_hns/scripts.pory"
	applymovement Phantonomy, Alola_Ulaula_House_Phant_Movement_2
# 39 "data/maps/UlaUla_House_hns/scripts.pory"
	waitmovement 0
# 40 "data/maps/UlaUla_House_hns/scripts.pory"
	delay 30
	goto Alola_Ulaula_House_Phant_17

Alola_Ulaula_House_Phant_19:
# 36 "data/maps/UlaUla_House_hns/scripts.pory"
	compare VAR_TEMP_2, 8
	goto_if_eq Alola_Ulaula_House_Phant_18
	goto Alola_Ulaula_House_Phant_17

Alola_Ulaula_House_Phant_23:
# 48 "data/maps/UlaUla_House_hns/scripts.pory"
	applymovement Phantonomy, Alola_Ulaula_House_Phant_Movement_3
# 49 "data/maps/UlaUla_House_hns/scripts.pory"
	waitmovement 0
	goto Alola_Ulaula_House_Phant_22

Alola_Ulaula_House_Phant_24:
# 46 "data/maps/UlaUla_House_hns/scripts.pory"
	compare VAR_TEMP_2, 10
	goto_if_eq Alola_Ulaula_House_Phant_23
	goto Alola_Ulaula_House_Phant_22

Alola_Ulaula_House_Phant_28:
# 53 "data/maps/UlaUla_House_hns/scripts.pory"
	applymovement Phantonomy, Alola_Ulaula_House_Phant_Movement_4
# 54 "data/maps/UlaUla_House_hns/scripts.pory"
	waitmovement 0
	goto Alola_Ulaula_House_Phant_27

Alola_Ulaula_House_Phant_29:
# 51 "data/maps/UlaUla_House_hns/scripts.pory"
	compare VAR_TEMP_2, 9
	goto_if_eq Alola_Ulaula_House_Phant_28
	goto Alola_Ulaula_House_Phant_27

Alola_Ulaula_House_Phant_33:
# 58 "data/maps/UlaUla_House_hns/scripts.pory"
	applymovement Phantonomy, Alola_Ulaula_House_Phant_Movement_5
# 59 "data/maps/UlaUla_House_hns/scripts.pory"
	waitmovement 0
	goto Alola_Ulaula_House_Phant_32

Alola_Ulaula_House_Phant_34:
# 56 "data/maps/UlaUla_House_hns/scripts.pory"
	compare VAR_TEMP_2, 8
	goto_if_eq Alola_Ulaula_House_Phant_33
	goto Alola_Ulaula_House_Phant_32


Alola_Ulaula_House_Noivern::
# 92 "data/maps/UlaUla_House_hns/scripts.pory"
	lock
# 93 "data/maps/UlaUla_House_hns/scripts.pory"
	faceplayer
# 94 "data/maps/UlaUla_House_hns/scripts.pory"
	playmoncry SPECIES_NOIVERN, 0
# 95 "data/maps/UlaUla_House_hns/scripts.pory"
	msgbox Alola_Ulaula_House_Noivern_Text_0, MSGBOX_AUTOCLOSE
# 96 "data/maps/UlaUla_House_hns/scripts.pory"
	waitmoncry
# 97 "data/maps/UlaUla_House_hns/scripts.pory"
	release
	end


Alola_Ulaula_House_Typholosion::
# 102 "data/maps/UlaUla_House_hns/scripts.pory"
	lock
# 103 "data/maps/UlaUla_House_hns/scripts.pory"
	faceplayer
# 104 "data/maps/UlaUla_House_hns/scripts.pory"
	playmoncry SPECIES_TYPHLOSION_HISUI, 0
# 105 "data/maps/UlaUla_House_hns/scripts.pory"
	msgbox Alola_Ulaula_House_Typholosion_Text_0
# 106 "data/maps/UlaUla_House_hns/scripts.pory"
	waitmoncry
# 107 "data/maps/UlaUla_House_hns/scripts.pory"
	release
	end


# 26 "data/maps/UlaUla_House_hns/scripts.pory"
Alola_Ulaula_House_Phant_Movement_0:
# 26 "data/maps/UlaUla_House_hns/scripts.pory"
	walk_in_place_down
# 26 "data/maps/UlaUla_House_hns/scripts.pory"
	walk_in_place_down
	step_end

# 32 "data/maps/UlaUla_House_hns/scripts.pory"
Alola_Ulaula_House_Phant_Movement_1:
# 32 "data/maps/UlaUla_House_hns/scripts.pory"
	walk_in_place_right
# 32 "data/maps/UlaUla_House_hns/scripts.pory"
	walk_in_place_right
	step_end

# 38 "data/maps/UlaUla_House_hns/scripts.pory"
Alola_Ulaula_House_Phant_Movement_2:
# 38 "data/maps/UlaUla_House_hns/scripts.pory"
	walk_in_place_up
# 38 "data/maps/UlaUla_House_hns/scripts.pory"
	walk_in_place_up
	step_end

# 48 "data/maps/UlaUla_House_hns/scripts.pory"
Alola_Ulaula_House_Phant_Movement_3:
# 48 "data/maps/UlaUla_House_hns/scripts.pory"
	jump_in_place_down
# 48 "data/maps/UlaUla_House_hns/scripts.pory"
	jump_in_place_down
	step_end

# 53 "data/maps/UlaUla_House_hns/scripts.pory"
Alola_Ulaula_House_Phant_Movement_4:
# 53 "data/maps/UlaUla_House_hns/scripts.pory"
	jump_in_place_right
# 53 "data/maps/UlaUla_House_hns/scripts.pory"
	jump_in_place_right
	step_end

# 58 "data/maps/UlaUla_House_hns/scripts.pory"
Alola_Ulaula_House_Phant_Movement_5:
# 58 "data/maps/UlaUla_House_hns/scripts.pory"
	jump_in_place_up
# 58 "data/maps/UlaUla_House_hns/scripts.pory"
	jump_in_place_up
	step_end

Alola_Ulaula_House_Phant_Text_0:
# 8 "data/maps/UlaUla_House_hns/scripts.pory"
	.string "Welcome, {PLAYER}.\p"
	.string "Thanks again for playing.\p"
	.string "Are you ready to face me in battle?$"

Alola_Ulaula_House_Phant_Text_1:
# 15 "data/maps/UlaUla_House_hns/scripts.pory"
	.string "I hope you're prepared…\n"
	.string "good luck.$"

Alola_Ulaula_House_Phant_Text_2:
# 17 "data/maps/UlaUla_House_hns/scripts.pory"
	.string "Congratulations, {PLAYER}!$"

Alola_Ulaula_House_Phant_Text_3:
# 20 "data/maps/UlaUla_House_hns/scripts.pory"
	.string "That was an incredible battle.\p"
	.string "I think you've earned this.$"

Alola_Ulaula_House_Phant_Text_4:
# 44 "data/maps/UlaUla_House_hns/scripts.pory"
	.string "You received an Egg from Phantonomy!$"

Alola_Ulaula_House_Phant_Text_5:
# 65 "data/maps/UlaUla_House_hns/scripts.pory"
	.string "That Egg contains my favorite Pokémon.\n"
	.string "Please, take good care of it…$"

Alola_Ulaula_House_Phant_Text_6:
# 72 "data/maps/UlaUla_House_hns/scripts.pory"
	.string "No worries, {PLAYER}.\n"
	.string "Come back when you're ready…$"

Alola_Ulaula_House_Phant_Text_7:
# 80 "data/maps/UlaUla_House_hns/scripts.pory"
	.string "I hope you enjoyed this taste of Alola.\p"
	.string "Look forward to my full demake of\n"
	.string "the region in my own upcoming project{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.\p"
	.string "Ultra Eclipse!$"

Alola_Ulaula_House_Noivern_Text_0:
# 95 "data/maps/UlaUla_House_hns/scripts.pory"
	.string "Scree!$"

Alola_Ulaula_House_Typholosion_Text_0:
# 105 "data/maps/UlaUla_House_hns/scripts.pory"
	.string "Graa!$"
