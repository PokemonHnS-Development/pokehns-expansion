UlaUla_House_hns_MapScripts::
	.byte 0


Alola_Ulaula_House_Phant::
	lock
	faceplayer
	compare VAR_ALOLA_STATE, 4
	goto_if_eq Alola_Ulaula_House_Phant_1
	msgbox Alola_Ulaula_House_Phant_Text_7, MSGBOX_AUTOCLOSE
	release
	end

Alola_Ulaula_House_Phant_1:
	msgbox Alola_Ulaula_House_Phant_Text_0, MSGBOX_AUTOCLOSE
	setvar VAR_ALOLA_STATE, 5
	getplayerxy VAR_TEMP_1, VAR_TEMP_2
	compare VAR_TEMP_1, 8
	goto_if_eq Alola_Ulaula_House_Phant_9
Alola_Ulaula_House_Phant_7:
	compare VAR_TEMP_1, 9
	goto_if_eq Alola_Ulaula_House_Phant_14
Alola_Ulaula_House_Phant_12:
	compare VAR_TEMP_1, 8
	goto_if_eq Alola_Ulaula_House_Phant_19
Alola_Ulaula_House_Phant_17:
	playse SE_LEDGE
	waitse
	playse SE_LEDGE
	waitse
	msgbox Alola_Ulaula_House_Phant_Text_3
	compare VAR_TEMP_1, 8
	goto_if_eq Alola_Ulaula_House_Phant_24
Alola_Ulaula_House_Phant_22:
	compare VAR_TEMP_1, 9
	goto_if_eq Alola_Ulaula_House_Phant_29
Alola_Ulaula_House_Phant_27:
	compare VAR_TEMP_1, 8
	goto_if_eq Alola_Ulaula_House_Phant_34
Alola_Ulaula_House_Phant_32:
	giveegg SPECIES_NOIBAT
	playfanfare MUS_HG_OBTAIN_EGG
	msgbox Alola_Ulaula_House_Phant_Text_4
	waitfanfare
	msgbox Alola_Ulaula_House_Phant_Text_5, MSGBOX_AUTOCLOSE
	release
	end

Alola_Ulaula_House_Phant_8:
	applymovement Phantonomy, Alola_Ulaula_House_Phant_Movement_0
	goto Alola_Ulaula_House_Phant_7

Alola_Ulaula_House_Phant_9:
	compare VAR_TEMP_2, 10
	goto_if_eq Alola_Ulaula_House_Phant_8
	goto Alola_Ulaula_House_Phant_7

Alola_Ulaula_House_Phant_13:
	applymovement Phantonomy, Alola_Ulaula_House_Phant_Movement_1
	goto Alola_Ulaula_House_Phant_12

Alola_Ulaula_House_Phant_14:
	compare VAR_TEMP_2, 9
	goto_if_eq Alola_Ulaula_House_Phant_13
	goto Alola_Ulaula_House_Phant_12

Alola_Ulaula_House_Phant_18:
	applymovement Phantonomy, Alola_Ulaula_House_Phant_Movement_2
	goto Alola_Ulaula_House_Phant_17

Alola_Ulaula_House_Phant_19:
	compare VAR_TEMP_2, 8
	goto_if_eq Alola_Ulaula_House_Phant_18
	goto Alola_Ulaula_House_Phant_17

Alola_Ulaula_House_Phant_23:
	applymovement Phantonomy, Alola_Ulaula_House_Phant_Movement_3
	waitmovement 0
	delay 30
	goto Alola_Ulaula_House_Phant_22

Alola_Ulaula_House_Phant_24:
	compare VAR_TEMP_2, 10
	goto_if_eq Alola_Ulaula_House_Phant_23
	goto Alola_Ulaula_House_Phant_22

Alola_Ulaula_House_Phant_28:
	applymovement Phantonomy, Alola_Ulaula_House_Phant_Movement_4
	waitmovement 0
	delay 30
	goto Alola_Ulaula_House_Phant_27

Alola_Ulaula_House_Phant_29:
	compare VAR_TEMP_2, 9
	goto_if_eq Alola_Ulaula_House_Phant_28
	goto Alola_Ulaula_House_Phant_27

Alola_Ulaula_House_Phant_33:
	applymovement Phantonomy, Alola_Ulaula_House_Phant_Movement_5
	waitmovement 0
	delay 30
	goto Alola_Ulaula_House_Phant_32

Alola_Ulaula_House_Phant_34:
	compare VAR_TEMP_2, 8
	goto_if_eq Alola_Ulaula_House_Phant_33
	goto Alola_Ulaula_House_Phant_32


Alola_Ulaula_House_Noivern::
	lock
	faceplayer
	playmoncry SPECIES_NOIVERN, 0
	msgbox Alola_Ulaula_House_Noivern_Text_0, MSGBOX_AUTOCLOSE
	waitmoncry
	release
	end


Alola_Ulaula_House_Typholosion::
	lock
	faceplayer
	playmoncry SPECIES_TYPHLOSION_HISUI, 0
	msgbox Alola_Ulaula_House_Typholosion_Text_0
	waitmoncry
	release
	end


Alola_Ulaula_House_Phant_Movement_0:
	jump_in_place_down
	jump_in_place_down
	step_end

Alola_Ulaula_House_Phant_Movement_1:
	jump_in_place_right
	jump_in_place_right
	step_end

Alola_Ulaula_House_Phant_Movement_2:
	jump_in_place_up
	jump_in_place_up
	step_end

Alola_Ulaula_House_Phant_Movement_3:
	walk_in_place_down
	walk_in_place_down
	step_end

Alola_Ulaula_House_Phant_Movement_4:
	walk_in_place_right
	walk_in_place_right
	step_end

Alola_Ulaula_House_Phant_Movement_5:
	walk_in_place_up
	walk_in_place_up
	step_end

Alola_Ulaula_House_Phant_Text_0:
	.string "Welcome, {PLAYER}.\p"
	.string "Thanks again for playing!$"

Alola_Ulaula_House_Phant_Text_1:
	.string "I hope you're prepared…\n"
	.string "good luck.$"

Alola_Ulaula_House_Phant_Text_2:
	.string "Congratulations, {PLAYER}!$"

Alola_Ulaula_House_Phant_Text_3:
	.string "I think you've earned this.$"

Alola_Ulaula_House_Phant_Text_4:
	.string "You received an Egg from PHANTONOMY!$"

Alola_Ulaula_House_Phant_Text_5:
	.string "That Egg contains my favorite Pokémon.\p"
	.string "Please, take good care of it…$"

Alola_Ulaula_House_Phant_Text_6:
	.string "No worries, {PLAYER}.\n"
	.string "Come back when you're ready…$"

Alola_Ulaula_House_Phant_Text_7:
	.string "I hope you enjoyed this taste of Alola.\p"
	.string "I'm working on a full demake of the\n"
	.string "region called ULTRA ECLIPSE.$"

Alola_Ulaula_House_Noivern_Text_0:
	.string "Scree!$"

Alola_Ulaula_House_Typholosion_Text_0:
	.string "Graa!$"
