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
# 49 "data/maps/UlaUla_House_hns/scripts.pory"
	msgbox Alola_Ulaula_House_Phant_Text_7, MSGBOX_AUTOCLOSE
# 55 "data/maps/UlaUla_House_hns/scripts.pory"
	release
	end

Alola_Ulaula_House_Phant_1:
# 8 "data/maps/UlaUla_House_hns/scripts.pory"
	msgbox Alola_Ulaula_House_Phant_Text_0, MSGBOX_YESNO
# 13 "data/maps/UlaUla_House_hns/scripts.pory"
	compare VAR_RESULT, YES
	goto_if_eq Alola_Ulaula_House_Phant_4
# 41 "data/maps/UlaUla_House_hns/scripts.pory"
	msgbox Alola_Ulaula_House_Phant_Text_6, MSGBOX_AUTOCLOSE
# 43 "data/maps/UlaUla_House_hns/scripts.pory"
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
	applymovement Phantonomy, Alola_Ulaula_House_Phant_Movement_0
# 24 "data/maps/UlaUla_House_hns/scripts.pory"
	waitmovement 0
# 25 "data/maps/UlaUla_House_hns/scripts.pory"
	giveegg SPECIES_NOIBAT
# 26 "data/maps/UlaUla_House_hns/scripts.pory"
	playfanfare MUS_HG_OBTAIN_EGG
# 27 "data/maps/UlaUla_House_hns/scripts.pory"
	msgbox Alola_Ulaula_House_Phant_Text_4
# 28 "data/maps/UlaUla_House_hns/scripts.pory"
	waitfanfare
# 29 "data/maps/UlaUla_House_hns/scripts.pory"
	applymovement Phantonomy, Alola_Ulaula_House_Phant_Movement_1
# 30 "data/maps/UlaUla_House_hns/scripts.pory"
	playse SE_LEDGE
# 31 "data/maps/UlaUla_House_hns/scripts.pory"
	waitse
# 32 "data/maps/UlaUla_House_hns/scripts.pory"
	playse SE_LEDGE
# 33 "data/maps/UlaUla_House_hns/scripts.pory"
	waitse
# 34 "data/maps/UlaUla_House_hns/scripts.pory"
	msgbox Alola_Ulaula_House_Phant_Text_5, MSGBOX_AUTOCLOSE
# 36 "data/maps/UlaUla_House_hns/scripts.pory"
	release
	end


Alola_Ulaula_House_Noivern::
# 61 "data/maps/UlaUla_House_hns/scripts.pory"
	lock
# 62 "data/maps/UlaUla_House_hns/scripts.pory"
	faceplayer
# 63 "data/maps/UlaUla_House_hns/scripts.pory"
	playmoncry SPECIES_NOIVERN, 0
# 64 "data/maps/UlaUla_House_hns/scripts.pory"
	msgbox Alola_Ulaula_House_Noivern_Text_0, MSGBOX_AUTOCLOSE
# 65 "data/maps/UlaUla_House_hns/scripts.pory"
	waitmoncry
# 66 "data/maps/UlaUla_House_hns/scripts.pory"
	release
	end


Alola_Ulaula_House_Typholosion::
# 71 "data/maps/UlaUla_House_hns/scripts.pory"
	lock
# 72 "data/maps/UlaUla_House_hns/scripts.pory"
	faceplayer
# 73 "data/maps/UlaUla_House_hns/scripts.pory"
	playmoncry SPECIES_TYPHLOSION_HISUI, 0
# 74 "data/maps/UlaUla_House_hns/scripts.pory"
	msgbox Alola_Ulaula_House_Typholosion_Text_0
# 75 "data/maps/UlaUla_House_hns/scripts.pory"
	waitmoncry
# 76 "data/maps/UlaUla_House_hns/scripts.pory"
	release
	end


# 23 "data/maps/UlaUla_House_hns/scripts.pory"
Alola_Ulaula_House_Phant_Movement_0:
# 23 "data/maps/UlaUla_House_hns/scripts.pory"
	walk_in_place_down
# 23 "data/maps/UlaUla_House_hns/scripts.pory"
	walk_in_place_down
	step_end

# 29 "data/maps/UlaUla_House_hns/scripts.pory"
Alola_Ulaula_House_Phant_Movement_1:
# 29 "data/maps/UlaUla_House_hns/scripts.pory"
	jump_in_place_down
# 29 "data/maps/UlaUla_House_hns/scripts.pory"
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
# 27 "data/maps/UlaUla_House_hns/scripts.pory"
	.string "You received an Egg from Phantonomy!$"

Alola_Ulaula_House_Phant_Text_5:
# 34 "data/maps/UlaUla_House_hns/scripts.pory"
	.string "That Egg contains my favorite Pokémon.\n"
	.string "Please, take good care of it…$"

Alola_Ulaula_House_Phant_Text_6:
# 41 "data/maps/UlaUla_House_hns/scripts.pory"
	.string "No worries, {PLAYER}.\n"
	.string "Come back when you're ready…$"

Alola_Ulaula_House_Phant_Text_7:
# 49 "data/maps/UlaUla_House_hns/scripts.pory"
	.string "I hope you enjoyed this taste of Alola.\p"
	.string "Look forward to my full demake of\n"
	.string "the region in my own upcoming project{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.\p"
	.string "Ultra Eclipse!$"

Alola_Ulaula_House_Noivern_Text_0:
# 64 "data/maps/UlaUla_House_hns/scripts.pory"
	.string "Scree!$"

Alola_Ulaula_House_Typholosion_Text_0:
# 74 "data/maps/UlaUla_House_hns/scripts.pory"
	.string "Graa!$"
