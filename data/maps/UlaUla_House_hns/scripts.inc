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
# 42 "data/maps/UlaUla_House_hns/scripts.pory"
	msgbox Alola_Ulaula_House_Phant_Text_7, MSGBOX_AUTOCLOSE
# 48 "data/maps/UlaUla_House_hns/scripts.pory"
	release
	end

Alola_Ulaula_House_Phant_1:
# 8 "data/maps/UlaUla_House_hns/scripts.pory"
	msgbox Alola_Ulaula_House_Phant_Text_0, MSGBOX_YESNO
# 13 "data/maps/UlaUla_House_hns/scripts.pory"
	compare VAR_RESULT, YES
	goto_if_eq Alola_Ulaula_House_Phant_4
# 34 "data/maps/UlaUla_House_hns/scripts.pory"
	msgbox Alola_Ulaula_House_Phant_Text_6, MSGBOX_AUTOCLOSE
# 36 "data/maps/UlaUla_House_hns/scripts.pory"
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
	msgbox Alola_Ulaula_House_Phant_Text_3, MSGBOX_AUTOCLOSE
# 23 "data/maps/UlaUla_House_hns/scripts.pory"
	giveegg SPECIES_NOIBAT
# 24 "data/maps/UlaUla_House_hns/scripts.pory"
	playfanfare MUS_HG_OBTAIN_EGG
# 25 "data/maps/UlaUla_House_hns/scripts.pory"
	msgbox Alola_Ulaula_House_Phant_Text_4, MSGBOX_AUTOCLOSE
# 26 "data/maps/UlaUla_House_hns/scripts.pory"
	waitfanfare
# 27 "data/maps/UlaUla_House_hns/scripts.pory"
	msgbox Alola_Ulaula_House_Phant_Text_5, MSGBOX_AUTOCLOSE
# 29 "data/maps/UlaUla_House_hns/scripts.pory"
	release
	end


Alola_Ulaula_House_Noivern::
# 54 "data/maps/UlaUla_House_hns/scripts.pory"
	lock
# 55 "data/maps/UlaUla_House_hns/scripts.pory"
	faceplayer
# 56 "data/maps/UlaUla_House_hns/scripts.pory"
	playmoncry SPECIES_NOIVERN, 0
# 57 "data/maps/UlaUla_House_hns/scripts.pory"
	msgbox Alola_Ulaula_House_Noivern_Text_0, MSGBOX_AUTOCLOSE
# 58 "data/maps/UlaUla_House_hns/scripts.pory"
	waitmoncry
# 59 "data/maps/UlaUla_House_hns/scripts.pory"
	release
	end


Alola_Ulaula_House_Typholosion::
# 64 "data/maps/UlaUla_House_hns/scripts.pory"
	lock
# 65 "data/maps/UlaUla_House_hns/scripts.pory"
	faceplayer
# 66 "data/maps/UlaUla_House_hns/scripts.pory"
	playmoncry SPECIES_TYPHLOSION_HISUI, 0
# 67 "data/maps/UlaUla_House_hns/scripts.pory"
	msgbox Alola_Ulaula_House_Typholosion_Text_0
# 68 "data/maps/UlaUla_House_hns/scripts.pory"
	waitmoncry
# 69 "data/maps/UlaUla_House_hns/scripts.pory"
	release
	end


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
# 25 "data/maps/UlaUla_House_hns/scripts.pory"
	.string "You received an Egg from Phantonomy!$"

Alola_Ulaula_House_Phant_Text_5:
# 27 "data/maps/UlaUla_House_hns/scripts.pory"
	.string "That Egg contains my favorite Pokémon.\n"
	.string "Please, take good care of it…$"

Alola_Ulaula_House_Phant_Text_6:
# 34 "data/maps/UlaUla_House_hns/scripts.pory"
	.string "No worries, {PLAYER}.\n"
	.string "Come back when you're ready…$"

Alola_Ulaula_House_Phant_Text_7:
# 42 "data/maps/UlaUla_House_hns/scripts.pory"
	.string "I hope you enjoyed this taste of Alola.\p"
	.string "Look forward to my full demake of\n"
	.string "the region in my own upcoming project{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.\p"
	.string "Ultra Eclipse.$"

Alola_Ulaula_House_Noivern_Text_0:
# 57 "data/maps/UlaUla_House_hns/scripts.pory"
	.string "Scree!$"

Alola_Ulaula_House_Typholosion_Text_0:
# 67 "data/maps/UlaUla_House_hns/scripts.pory"
	.string "Graa!$"
