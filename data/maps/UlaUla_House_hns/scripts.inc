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
# 63 "data/maps/UlaUla_House_hns/scripts.pory"
	msgbox Alola_Ulaula_House_Phant_Text_7, MSGBOX_AUTOCLOSE
# 69 "data/maps/UlaUla_House_hns/scripts.pory"
	release
	end

Alola_Ulaula_House_Phant_1:
# 8 "data/maps/UlaUla_House_hns/scripts.pory"
	msgbox Alola_Ulaula_House_Phant_Text_0, MSGBOX_YESNO
# 13 "data/maps/UlaUla_House_hns/scripts.pory"
	compare VAR_RESULT, YES
	goto_if_eq Alola_Ulaula_House_Phant_4
# 55 "data/maps/UlaUla_House_hns/scripts.pory"
	msgbox Alola_Ulaula_House_Phant_Text_6, MSGBOX_AUTOCLOSE
# 57 "data/maps/UlaUla_House_hns/scripts.pory"
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
# 29 "data/maps/UlaUla_House_hns/scripts.pory"
	compare VAR_TEMP_1, 9
	goto_if_eq Alola_Ulaula_House_Phant_14
Alola_Ulaula_House_Phant_12:
# 34 "data/maps/UlaUla_House_hns/scripts.pory"
	compare VAR_TEMP_1, 8
	goto_if_eq Alola_Ulaula_House_Phant_19
Alola_Ulaula_House_Phant_17:
# 39 "data/maps/UlaUla_House_hns/scripts.pory"
	giveegg SPECIES_NOIBAT
# 40 "data/maps/UlaUla_House_hns/scripts.pory"
	playfanfare MUS_HG_OBTAIN_EGG
# 41 "data/maps/UlaUla_House_hns/scripts.pory"
	msgbox Alola_Ulaula_House_Phant_Text_4
# 42 "data/maps/UlaUla_House_hns/scripts.pory"
	waitfanfare
# 43 "data/maps/UlaUla_House_hns/scripts.pory"
	applymovement Phantonomy, Alola_Ulaula_House_Phant_Movement_3
# 44 "data/maps/UlaUla_House_hns/scripts.pory"
	playse SE_LEDGE
# 45 "data/maps/UlaUla_House_hns/scripts.pory"
	waitse
# 46 "data/maps/UlaUla_House_hns/scripts.pory"
	playse SE_LEDGE
# 47 "data/maps/UlaUla_House_hns/scripts.pory"
	waitse
# 48 "data/maps/UlaUla_House_hns/scripts.pory"
	msgbox Alola_Ulaula_House_Phant_Text_5, MSGBOX_AUTOCLOSE
# 50 "data/maps/UlaUla_House_hns/scripts.pory"
	release
	end

Alola_Ulaula_House_Phant_8:
# 26 "data/maps/UlaUla_House_hns/scripts.pory"
	applymovement Phantonomy, Alola_Ulaula_House_Phant_Movement_0
# 27 "data/maps/UlaUla_House_hns/scripts.pory"
	waitmovement 0
	goto Alola_Ulaula_House_Phant_7

Alola_Ulaula_House_Phant_9:
# 24 "data/maps/UlaUla_House_hns/scripts.pory"
	compare VAR_TEMP_2, 10
	goto_if_eq Alola_Ulaula_House_Phant_8
	goto Alola_Ulaula_House_Phant_7

Alola_Ulaula_House_Phant_13:
# 31 "data/maps/UlaUla_House_hns/scripts.pory"
	applymovement Phantonomy, Alola_Ulaula_House_Phant_Movement_1
# 32 "data/maps/UlaUla_House_hns/scripts.pory"
	waitmovement 0
	goto Alola_Ulaula_House_Phant_12

Alola_Ulaula_House_Phant_14:
# 29 "data/maps/UlaUla_House_hns/scripts.pory"
	compare VAR_TEMP_2, 9
	goto_if_eq Alola_Ulaula_House_Phant_13
	goto Alola_Ulaula_House_Phant_12

Alola_Ulaula_House_Phant_18:
# 36 "data/maps/UlaUla_House_hns/scripts.pory"
	applymovement Phantonomy, Alola_Ulaula_House_Phant_Movement_2
# 37 "data/maps/UlaUla_House_hns/scripts.pory"
	waitmovement 0
	goto Alola_Ulaula_House_Phant_17

Alola_Ulaula_House_Phant_19:
# 34 "data/maps/UlaUla_House_hns/scripts.pory"
	compare VAR_TEMP_2, 8
	goto_if_eq Alola_Ulaula_House_Phant_18
	goto Alola_Ulaula_House_Phant_17


Alola_Ulaula_House_Noivern::
# 75 "data/maps/UlaUla_House_hns/scripts.pory"
	lock
# 76 "data/maps/UlaUla_House_hns/scripts.pory"
	faceplayer
# 77 "data/maps/UlaUla_House_hns/scripts.pory"
	playmoncry SPECIES_NOIVERN, 0
# 78 "data/maps/UlaUla_House_hns/scripts.pory"
	msgbox Alola_Ulaula_House_Noivern_Text_0, MSGBOX_AUTOCLOSE
# 79 "data/maps/UlaUla_House_hns/scripts.pory"
	waitmoncry
# 80 "data/maps/UlaUla_House_hns/scripts.pory"
	release
	end


Alola_Ulaula_House_Typholosion::
# 85 "data/maps/UlaUla_House_hns/scripts.pory"
	lock
# 86 "data/maps/UlaUla_House_hns/scripts.pory"
	faceplayer
# 87 "data/maps/UlaUla_House_hns/scripts.pory"
	playmoncry SPECIES_TYPHLOSION_HISUI, 0
# 88 "data/maps/UlaUla_House_hns/scripts.pory"
	msgbox Alola_Ulaula_House_Typholosion_Text_0
# 89 "data/maps/UlaUla_House_hns/scripts.pory"
	waitmoncry
# 90 "data/maps/UlaUla_House_hns/scripts.pory"
	release
	end


# 26 "data/maps/UlaUla_House_hns/scripts.pory"
Alola_Ulaula_House_Phant_Movement_0:
# 26 "data/maps/UlaUla_House_hns/scripts.pory"
	walk_in_place_down
# 26 "data/maps/UlaUla_House_hns/scripts.pory"
	walk_in_place_down
	step_end

# 31 "data/maps/UlaUla_House_hns/scripts.pory"
Alola_Ulaula_House_Phant_Movement_1:
# 31 "data/maps/UlaUla_House_hns/scripts.pory"
	walk_in_place_right
# 31 "data/maps/UlaUla_House_hns/scripts.pory"
	walk_in_place_right
	step_end

# 36 "data/maps/UlaUla_House_hns/scripts.pory"
Alola_Ulaula_House_Phant_Movement_2:
# 36 "data/maps/UlaUla_House_hns/scripts.pory"
	walk_in_place_up
# 36 "data/maps/UlaUla_House_hns/scripts.pory"
	walk_in_place_up
	step_end

# 43 "data/maps/UlaUla_House_hns/scripts.pory"
Alola_Ulaula_House_Phant_Movement_3:
# 43 "data/maps/UlaUla_House_hns/scripts.pory"
	jump_in_place_down
# 43 "data/maps/UlaUla_House_hns/scripts.pory"
	jump_in_place_down
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
# 41 "data/maps/UlaUla_House_hns/scripts.pory"
	.string "You received an Egg from Phantonomy!$"

Alola_Ulaula_House_Phant_Text_5:
# 48 "data/maps/UlaUla_House_hns/scripts.pory"
	.string "That Egg contains my favorite Pokémon.\n"
	.string "Please, take good care of it…$"

Alola_Ulaula_House_Phant_Text_6:
# 55 "data/maps/UlaUla_House_hns/scripts.pory"
	.string "No worries, {PLAYER}.\n"
	.string "Come back when you're ready…$"

Alola_Ulaula_House_Phant_Text_7:
# 63 "data/maps/UlaUla_House_hns/scripts.pory"
	.string "I hope you enjoyed this taste of Alola.\p"
	.string "Look forward to my full demake of\n"
	.string "the region in my own upcoming project{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.\p"
	.string "Ultra Eclipse!$"

Alola_Ulaula_House_Noivern_Text_0:
# 78 "data/maps/UlaUla_House_hns/scripts.pory"
	.string "Scree!$"

Alola_Ulaula_House_Typholosion_Text_0:
# 88 "data/maps/UlaUla_House_hns/scripts.pory"
	.string "Graa!$"
