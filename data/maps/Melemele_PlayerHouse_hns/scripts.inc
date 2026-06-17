Melemele_PlayerHouse_hns_MapScripts::
# 2 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Melemele_PlayerHouse_hns_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE
	.byte 0

Melemele_PlayerHouse_hns_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE:
# 2 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	map_script_2 VAR_ALOLA_STATE, 1, Alola_Melemele_SamsonOakVillaIntro_Trigger
	.2byte 0


Alola_Melemele_SamsonOakVillaIntro_Trigger::
# 6 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	lock
# 7 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	playse SE_PIN
# 8 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	applymovement SamsonOakVilla, Alola_Melemele_SamsonOakVillaIntro_Trigger_Movement_0
# 9 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	waitmovement 0
# 10 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVillaIntro_Trigger_Text_0
# 11 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	applymovement SamsonOakVilla, Alola_Melemele_SamsonOakVillaIntro_Trigger_Movement_1
# 12 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	waitmovement 0
# 13 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVillaIntro_Trigger_Text_1, MSGBOX_AUTOCLOSE
# 22 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	applymovement SamsonOakVilla, Alola_Melemele_SamsonOakVillaIntro_Trigger_Movement_2
# 23 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	waitmovement 0
# 24 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVillaIntro_Trigger_Text_2, MSGBOX_AUTOCLOSE
# 36 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	applymovement SamsonOakVilla, Alola_Melemele_SamsonOakVillaIntro_Trigger_Movement_3
# 37 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	waitmovement 0
# 38 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	setvar VAR_ALOLA_STATE, 2
# 39 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	release
	end


Alola_Melemele_SamsonOakVilla_Dialogue::
# 44 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	lock
# 45 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	faceplayer
# 46 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	goto_if_set FLAG_BATTLED_TAPU_KOKO, Alola_Melemele_SamsonOakVilla_Dialogue_4
Alola_Melemele_SamsonOakVilla_Dialogue_2:
# 89 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_AKALA, Alola_Melemele_SamsonOakVilla_Dialogue_16
Alola_Melemele_SamsonOakVilla_Dialogue_14:
# 185 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_10
# 192 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	dynmultichoice 20, 4, FALSE, 4, 0, DYN_MULTICHOICE_CB_NONE, Alola_Melemele_SamsonOakVilla_Dialogue_Text_11, Alola_Melemele_SamsonOakVilla_Dialogue_Text_12, Alola_Melemele_SamsonOakVilla_Dialogue_Text_13, Alola_Melemele_SamsonOakVilla_Dialogue_Text_14, Alola_Melemele_SamsonOakVilla_Dialogue_Text_15
# 193 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq Alola_Melemele_SamsonOakVilla_Dialogue_31
# 312 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	compare VAR_RESULT, 1
	goto_if_eq Alola_Melemele_SamsonOakVilla_Dialogue_32
# 426 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	compare VAR_RESULT, 2
	goto_if_eq Alola_Melemele_SamsonOakVilla_Dialogue_33
# 553 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	compare VAR_RESULT, 3
	goto_if_eq Alola_Melemele_SamsonOakVilla_Dialogue_34
# 677 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_34, MSGBOX_AUTOCLOSE
# 681 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	release
	end

Alola_Melemele_SamsonOakVilla_Dialogue_1:
# 48 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	compare VAR_ALOLA_STATE, 3
	goto_if_eq Alola_Melemele_SamsonOakVilla_Dialogue_10
# 73 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_2, MSGBOX_AUTOCLOSE
# 82 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	release
	end

Alola_Melemele_SamsonOakVilla_Dialogue_3:
# 46 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	goto_if_set FLAG_BATTLED_TAPU_BULU, Alola_Melemele_SamsonOakVilla_Dialogue_7
	goto Alola_Melemele_SamsonOakVilla_Dialogue_2

Alola_Melemele_SamsonOakVilla_Dialogue_4:
# 46 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	goto_if_set FLAG_BATTLED_TAPU_LELE, Alola_Melemele_SamsonOakVilla_Dialogue_3
	goto Alola_Melemele_SamsonOakVilla_Dialogue_2

Alola_Melemele_SamsonOakVilla_Dialogue_7:
# 46 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	goto_if_set FLAG_BATTLED_TAPU_FINI, Alola_Melemele_SamsonOakVilla_Dialogue_1
	goto Alola_Melemele_SamsonOakVilla_Dialogue_2

Alola_Melemele_SamsonOakVilla_Dialogue_10:
# 50 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVillaIntro_Trigger_Text_0, MSGBOX_AUTOCLOSE
# 51 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	playse SE_PIN
# 52 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	applymovement SamsonOakVilla, Alola_Melemele_SamsonOakVilla_Dialogue_Movement_0
# 53 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	waitmovement 0
# 54 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_0, MSGBOX_AUTOCLOSE
# 63 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	giveitem ITEM_BEAST_BALL
# 64 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_1, MSGBOX_AUTOCLOSE
# 66 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	setvar VAR_ALOLA_STATE, 4
# 67 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	clearflag FLAG_HIDE_PHANT_OUTSIDE
# 68 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	release
	end

Alola_Melemele_SamsonOakVilla_Dialogue_13:
# 91 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	goto_if_set FLAG_DEFEATED_MELEMELE_TOTEM, Alola_Melemele_SamsonOakVilla_Dialogue_25
Alola_Melemele_SamsonOakVilla_Dialogue_23:
# 170 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_9, MSGBOX_AUTOCLOSE
# 179 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	release
	end

Alola_Melemele_SamsonOakVilla_Dialogue_15:
# 89 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_PONI, Alola_Melemele_SamsonOakVilla_Dialogue_19
	goto Alola_Melemele_SamsonOakVilla_Dialogue_14

Alola_Melemele_SamsonOakVilla_Dialogue_16:
# 89 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_ULAULA, Alola_Melemele_SamsonOakVilla_Dialogue_15
	goto Alola_Melemele_SamsonOakVilla_Dialogue_14

Alola_Melemele_SamsonOakVilla_Dialogue_19:
# 89 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_MELEMELE, Alola_Melemele_SamsonOakVilla_Dialogue_13
	goto Alola_Melemele_SamsonOakVilla_Dialogue_14

Alola_Melemele_SamsonOakVilla_Dialogue_22:
# 93 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	goto_if_set FLAG_DEFEATED_SAMSON_OAK, Alola_Melemele_SamsonOakVilla_Dialogue_40
# 109 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_3, MSGBOX_YESNO
# 120 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	compare VAR_RESULT, YES
	goto_if_eq Alola_Melemele_SamsonOakVilla_Dialogue_55
# 157 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_8, MSGBOX_AUTOCLOSE
# 162 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	release
	end

Alola_Melemele_SamsonOakVilla_Dialogue_24:
# 91 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	goto_if_set FLAG_DEFEATED_ULAULA_TOTEM, Alola_Melemele_SamsonOakVilla_Dialogue_28
	goto Alola_Melemele_SamsonOakVilla_Dialogue_23

Alola_Melemele_SamsonOakVilla_Dialogue_25:
# 91 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	goto_if_set FLAG_DEFEATED_AKALA_TOTEM, Alola_Melemele_SamsonOakVilla_Dialogue_24
	goto Alola_Melemele_SamsonOakVilla_Dialogue_23

Alola_Melemele_SamsonOakVilla_Dialogue_28:
# 91 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	goto_if_set FLAG_DEFEATED_PONI_TOTEM, Alola_Melemele_SamsonOakVilla_Dialogue_22
	goto Alola_Melemele_SamsonOakVilla_Dialogue_23

Alola_Melemele_SamsonOakVilla_Dialogue_31:
# 195 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	getcaughtmon SPECIES_MEOWTH_ALOLA
# 196 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	compare VAR_RESULT, 1
	goto_if_eq Alola_Melemele_SamsonOakVilla_Dialogue_44
Alola_Melemele_SamsonOakVilla_Dialogue_43:
# 296 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_23, MSGBOX_AUTOCLOSE
# 309 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	release
	end

Alola_Melemele_SamsonOakVilla_Dialogue_32:
# 313 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	getcaughtmon SPECIES_MAROWAK_ALOLA
# 314 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	compare VAR_RESULT, 1
	goto_if_eq Alola_Melemele_SamsonOakVilla_Dialogue_47
Alola_Melemele_SamsonOakVilla_Dialogue_46:
# 410 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_27, MSGBOX_AUTOCLOSE
# 423 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	release
	end

Alola_Melemele_SamsonOakVilla_Dialogue_33:
# 427 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	getcaughtmon SPECIES_VULPIX_ALOLA
# 428 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	compare VAR_RESULT, 1
	goto_if_eq Alola_Melemele_SamsonOakVilla_Dialogue_50
Alola_Melemele_SamsonOakVilla_Dialogue_49:
# 536 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_30, MSGBOX_AUTOCLOSE
# 550 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	release
	end

Alola_Melemele_SamsonOakVilla_Dialogue_34:
# 554 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	getcaughtmon SPECIES_RAICHU_ALOLA
# 555 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	compare VAR_RESULT, 1
	goto_if_eq Alola_Melemele_SamsonOakVilla_Dialogue_53
Alola_Melemele_SamsonOakVilla_Dialogue_52:
# 659 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_33, MSGBOX_AUTOCLOSE
# 673 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	release
	end

Alola_Melemele_SamsonOakVilla_Dialogue_40:
# 95 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_2, MSGBOX_AUTOCLOSE
# 104 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	release
	end

Alola_Melemele_SamsonOakVilla_Dialogue_44:
# 198 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	getcaughtmon SPECIES_PERSIAN_ALOLA
# 199 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	compare VAR_RESULT, 1
	goto_if_eq Alola_Melemele_SamsonOakVilla_Dialogue_58
	goto Alola_Melemele_SamsonOakVilla_Dialogue_43

Alola_Melemele_SamsonOakVilla_Dialogue_47:
# 316 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	getcaughtmon SPECIES_DIGLETT_ALOLA
# 317 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	compare VAR_RESULT, 1
	goto_if_eq Alola_Melemele_SamsonOakVilla_Dialogue_60
	goto Alola_Melemele_SamsonOakVilla_Dialogue_46

Alola_Melemele_SamsonOakVilla_Dialogue_50:
# 430 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	getcaughtmon SPECIES_NINETALES_ALOLA
# 431 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	compare VAR_RESULT, 1
	goto_if_eq Alola_Melemele_SamsonOakVilla_Dialogue_62
	goto Alola_Melemele_SamsonOakVilla_Dialogue_49

Alola_Melemele_SamsonOakVilla_Dialogue_53:
# 557 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	getcaughtmon SPECIES_GEODUDE_ALOLA
# 558 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	compare VAR_RESULT, 1
	goto_if_eq Alola_Melemele_SamsonOakVilla_Dialogue_64
	goto Alola_Melemele_SamsonOakVilla_Dialogue_52

Alola_Melemele_SamsonOakVilla_Dialogue_55:
# 122 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_4
# 124 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	trainerbattle_no_intro TRAINER_SAMSON_OAK_HNS, Alola_Melemele_SamsonOakVilla_Dialogue_Text_5
# 125 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	special HealPlayerParty
# 126 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	setflag FLAG_DEFEATED_SAMSON_OAK
# 127 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	setflag FLAG_FLYOVER_TAPU_KOKO
# 128 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	setflag FLAG_FLYOVER_TAPU_LELE
# 129 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	setflag FLAG_FLYOVER_TAPU_BULU
# 130 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	setflag FLAG_FLYOVER_TAPU_FINI
# 131 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_6, MSGBOX_AUTOCLOSE
# 147 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	playse SE_PIN
# 148 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	applymovement SamsonOakVilla, Alola_Melemele_SamsonOakVilla_Dialogue_Movement_0
# 149 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_7, MSGBOX_AUTOCLOSE
# 151 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	setvar VAR_ALOLA_STATE, 3
# 152 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	release
	end

Alola_Melemele_SamsonOakVilla_Dialogue_58:
# 201 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	getcaughtmon SPECIES_RATTATA_ALOLA
# 202 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	compare VAR_RESULT, 1
	goto_if_eq Alola_Melemele_SamsonOakVilla_Dialogue_66
	goto Alola_Melemele_SamsonOakVilla_Dialogue_43

Alola_Melemele_SamsonOakVilla_Dialogue_60:
# 319 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	getcaughtmon SPECIES_DUGTRIO_ALOLA
# 320 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	compare VAR_RESULT, 1
	goto_if_eq Alola_Melemele_SamsonOakVilla_Dialogue_68
	goto Alola_Melemele_SamsonOakVilla_Dialogue_46

Alola_Melemele_SamsonOakVilla_Dialogue_62:
# 433 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	getcaughtmon SPECIES_SANDSHREW_ALOLA
# 434 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	compare VAR_RESULT, 1
	goto_if_eq Alola_Melemele_SamsonOakVilla_Dialogue_70
	goto Alola_Melemele_SamsonOakVilla_Dialogue_49

Alola_Melemele_SamsonOakVilla_Dialogue_64:
# 560 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	getcaughtmon SPECIES_GRAVELER_ALOLA
# 561 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	compare VAR_RESULT, 1
	goto_if_eq Alola_Melemele_SamsonOakVilla_Dialogue_72
	goto Alola_Melemele_SamsonOakVilla_Dialogue_52

Alola_Melemele_SamsonOakVilla_Dialogue_66:
# 204 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	getcaughtmon SPECIES_RATICATE_ALOLA
# 205 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	compare VAR_RESULT, 1
	goto_if_eq Alola_Melemele_SamsonOakVilla_Dialogue_74
	goto Alola_Melemele_SamsonOakVilla_Dialogue_43

Alola_Melemele_SamsonOakVilla_Dialogue_68:
# 322 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	goto_if_unset FLAG_CAUGHT_ALL_AKALA, Alola_Melemele_SamsonOakVilla_Dialogue_76
# 397 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_26, MSGBOX_AUTOCLOSE
# 404 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	release
	end

Alola_Melemele_SamsonOakVilla_Dialogue_70:
# 436 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	getcaughtmon SPECIES_SANDSLASH_ALOLA
# 437 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	compare VAR_RESULT, 1
	goto_if_eq Alola_Melemele_SamsonOakVilla_Dialogue_79
	goto Alola_Melemele_SamsonOakVilla_Dialogue_49

Alola_Melemele_SamsonOakVilla_Dialogue_72:
# 563 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	getcaughtmon SPECIES_GOLEM_ALOLA
# 564 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	compare VAR_RESULT, 1
	goto_if_eq Alola_Melemele_SamsonOakVilla_Dialogue_81
	goto Alola_Melemele_SamsonOakVilla_Dialogue_52

Alola_Melemele_SamsonOakVilla_Dialogue_74:
# 207 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	goto_if_unset FLAG_CAUGHT_ALL_MELEMELE, Alola_Melemele_SamsonOakVilla_Dialogue_83
# 282 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_22, MSGBOX_AUTOCLOSE
# 289 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	release
	end

Alola_Melemele_SamsonOakVilla_Dialogue_76:
# 324 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_MELEMELE, Alola_Melemele_SamsonOakVilla_Dialogue_86
# 324 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_ULAULA, Alola_Melemele_SamsonOakVilla_Dialogue_86
# 324 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_PONI, Alola_Melemele_SamsonOakVilla_Dialogue_86
# 379 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	setflag FLAG_CAUGHT_ALL_AKALA
# 380 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_16, MSGBOX_AUTOCLOSE
# 381 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	playse SE_PIN
# 382 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	applymovement SamsonOakVilla, Alola_Melemele_SamsonOakVilla_Dialogue_Movement_0
# 383 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	waitmovement 0
# 384 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_17
# 385 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	playfanfare MUS_HG_OBTAIN_EGG
# 386 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_24
# 388 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	waitfanfare
# 389 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_21
# 391 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	release
	end

Alola_Melemele_SamsonOakVilla_Dialogue_79:
# 439 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	getcaughtmon SPECIES_GRIMER_ALOLA
# 440 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	compare VAR_RESULT, 1
	goto_if_eq Alola_Melemele_SamsonOakVilla_Dialogue_93
	goto Alola_Melemele_SamsonOakVilla_Dialogue_49

Alola_Melemele_SamsonOakVilla_Dialogue_81:
# 566 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	getcaughtmon SPECIES_EXEGGUTOR_ALOLA
# 567 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	compare VAR_RESULT, 1
	goto_if_eq Alola_Melemele_SamsonOakVilla_Dialogue_95
	goto Alola_Melemele_SamsonOakVilla_Dialogue_52

Alola_Melemele_SamsonOakVilla_Dialogue_83:
# 209 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_AKALA, Alola_Melemele_SamsonOakVilla_Dialogue_97
# 209 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_ULAULA, Alola_Melemele_SamsonOakVilla_Dialogue_97
# 209 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_PONI, Alola_Melemele_SamsonOakVilla_Dialogue_97
# 264 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	setflag FLAG_CAUGHT_ALL_MELEMELE
# 265 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_16, MSGBOX_AUTOCLOSE
# 266 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	playse SE_PIN
# 267 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	applymovement SamsonOakVilla, Alola_Melemele_SamsonOakVilla_Dialogue_Movement_0
# 268 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	waitmovement 0
# 269 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_17
# 270 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	playfanfare MUS_HG_OBTAIN_EGG
# 271 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_18
# 273 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	waitfanfare
# 274 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_21, MSGBOX_AUTOCLOSE
# 276 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	release
	end

Alola_Melemele_SamsonOakVilla_Dialogue_86:
# 326 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	setflag FLAG_CAUGHT_ALL_AKALA
# 327 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_16, MSGBOX_AUTOCLOSE
# 328 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	playse SE_PIN
# 329 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	applymovement SamsonOakVilla, Alola_Melemele_SamsonOakVilla_Dialogue_Movement_0
# 330 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	waitmovement 0
# 331 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_17
# 332 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	playfanfare MUS_HG_OBTAIN_EGG
# 333 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_24
# 335 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	waitfanfare
# 336 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_AKALA, Alola_Melemele_SamsonOakVilla_Dialogue_107
Alola_Melemele_SamsonOakVilla_Dialogue_105:
# 371 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_21
# 373 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	release
	end

Alola_Melemele_SamsonOakVilla_Dialogue_93:
# 442 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	getcaughtmon SPECIES_MUK_ALOLA
# 443 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	compare VAR_RESULT, 1
	goto_if_eq Alola_Melemele_SamsonOakVilla_Dialogue_113
	goto Alola_Melemele_SamsonOakVilla_Dialogue_49

Alola_Melemele_SamsonOakVilla_Dialogue_95:
# 569 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	goto_if_unset FLAG_CAUGHT_ALL_PONI, Alola_Melemele_SamsonOakVilla_Dialogue_115
# 644 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_32, MSGBOX_AUTOCLOSE
# 651 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	release
	end

Alola_Melemele_SamsonOakVilla_Dialogue_97:
# 211 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	setflag FLAG_CAUGHT_ALL_MELEMELE
# 212 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_16, MSGBOX_AUTOCLOSE
# 213 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	playse SE_PIN
# 214 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	applymovement SamsonOakVilla, Alola_Melemele_SamsonOakVilla_Dialogue_Movement_0
# 215 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	waitmovement 0
# 216 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_17
# 217 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	playfanfare MUS_HG_OBTAIN_EGG
# 218 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_18
# 220 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	waitfanfare
# 221 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_AKALA, Alola_Melemele_SamsonOakVilla_Dialogue_121
Alola_Melemele_SamsonOakVilla_Dialogue_119:
# 256 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_21, MSGBOX_AUTOCLOSE
# 258 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	release
	end

Alola_Melemele_SamsonOakVilla_Dialogue_104:
# 338 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	playfanfare MUS_HG_BUG_CONTEST_1ST_PLACE
# 339 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_19, MSGBOX_AUTOCLOSE
# 345 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	waitfanfare
# 346 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	playse SE_PIN
# 347 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	applymovement SamsonOakVilla, Alola_Melemele_SamsonOakVilla_Dialogue_Movement_0
# 348 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	waitmovement 0
# 349 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_25
# 366 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	release
	end

Alola_Melemele_SamsonOakVilla_Dialogue_106:
# 336 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_PONI, Alola_Melemele_SamsonOakVilla_Dialogue_110
	goto Alola_Melemele_SamsonOakVilla_Dialogue_105

Alola_Melemele_SamsonOakVilla_Dialogue_107:
# 336 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_ULAULA, Alola_Melemele_SamsonOakVilla_Dialogue_106
	goto Alola_Melemele_SamsonOakVilla_Dialogue_105

Alola_Melemele_SamsonOakVilla_Dialogue_110:
# 336 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_MELEMELE, Alola_Melemele_SamsonOakVilla_Dialogue_104
	goto Alola_Melemele_SamsonOakVilla_Dialogue_105

Alola_Melemele_SamsonOakVilla_Dialogue_113:
# 445 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	goto_if_unset FLAG_CAUGHT_ALL_ULAULA, Alola_Melemele_SamsonOakVilla_Dialogue_127
# 520 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_29, MSGBOX_AUTOCLOSE
# 527 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	release
	end

Alola_Melemele_SamsonOakVilla_Dialogue_115:
# 571 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_MELEMELE, Alola_Melemele_SamsonOakVilla_Dialogue_130
# 571 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_AKALA, Alola_Melemele_SamsonOakVilla_Dialogue_130
# 571 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_ULAULA, Alola_Melemele_SamsonOakVilla_Dialogue_130
# 626 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	setflag FLAG_CAUGHT_ALL_PONI
# 627 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_16, MSGBOX_AUTOCLOSE
# 628 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	playse SE_PIN
# 629 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	applymovement SamsonOakVilla, Alola_Melemele_SamsonOakVilla_Dialogue_Movement_0
# 630 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	waitmovement 0
# 631 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_17
# 632 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	playfanfare MUS_HG_OBTAIN_EGG
# 633 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_31
# 635 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	waitfanfare
# 636 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_21, MSGBOX_AUTOCLOSE
# 638 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	release
	end

Alola_Melemele_SamsonOakVilla_Dialogue_118:
# 223 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	playfanfare MUS_HG_BUG_CONTEST_1ST_PLACE
# 224 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_19, MSGBOX_AUTOCLOSE
# 230 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	waitfanfare
# 231 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	playse SE_PIN
# 232 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	applymovement SamsonOakVilla, Alola_Melemele_SamsonOakVilla_Dialogue_Movement_0
# 233 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	waitmovement 0
# 234 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_20, MSGBOX_AUTOCLOSE
# 251 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	release
	end

Alola_Melemele_SamsonOakVilla_Dialogue_120:
# 221 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_PONI, Alola_Melemele_SamsonOakVilla_Dialogue_124
	goto Alola_Melemele_SamsonOakVilla_Dialogue_119

Alola_Melemele_SamsonOakVilla_Dialogue_121:
# 221 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_ULAULA, Alola_Melemele_SamsonOakVilla_Dialogue_120
	goto Alola_Melemele_SamsonOakVilla_Dialogue_119

Alola_Melemele_SamsonOakVilla_Dialogue_124:
# 221 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_MELEMELE, Alola_Melemele_SamsonOakVilla_Dialogue_118
	goto Alola_Melemele_SamsonOakVilla_Dialogue_119

Alola_Melemele_SamsonOakVilla_Dialogue_127:
# 447 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_MELEMELE, Alola_Melemele_SamsonOakVilla_Dialogue_137
# 447 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_AKALA, Alola_Melemele_SamsonOakVilla_Dialogue_137
# 447 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_PONI, Alola_Melemele_SamsonOakVilla_Dialogue_137
# 502 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	setflag FLAG_CAUGHT_ALL_ULAULA
# 503 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_16, MSGBOX_AUTOCLOSE
# 504 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	playse SE_PIN
# 505 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	applymovement SamsonOakVilla, Alola_Melemele_SamsonOakVilla_Dialogue_Movement_0
# 506 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	waitmovement 0
# 507 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_17
# 508 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	playfanfare MUS_HG_OBTAIN_EGG
# 509 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_28
# 511 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	waitfanfare
# 512 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_21, MSGBOX_AUTOCLOSE
# 514 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	release
	end

Alola_Melemele_SamsonOakVilla_Dialogue_130:
# 573 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	setflag FLAG_CAUGHT_ALL_PONI
# 574 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_16, MSGBOX_AUTOCLOSE
# 575 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	playse SE_PIN
# 576 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	applymovement SamsonOakVilla, Alola_Melemele_SamsonOakVilla_Dialogue_Movement_0
# 577 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	waitmovement 0
# 578 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_17
# 579 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	playfanfare MUS_HG_OBTAIN_EGG
# 580 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_31
# 582 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	waitfanfare
# 583 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_AKALA, Alola_Melemele_SamsonOakVilla_Dialogue_147
Alola_Melemele_SamsonOakVilla_Dialogue_145:
# 618 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_21, MSGBOX_AUTOCLOSE
# 620 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	release
	end

Alola_Melemele_SamsonOakVilla_Dialogue_137:
# 449 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	setflag FLAG_CAUGHT_ALL_ULAULA
# 450 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_16, MSGBOX_AUTOCLOSE
# 451 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	playse SE_PIN
# 452 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	applymovement SamsonOakVilla, Alola_Melemele_SamsonOakVilla_Dialogue_Movement_0
# 453 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	waitmovement 0
# 454 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_17
# 455 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	playfanfare MUS_HG_OBTAIN_EGG
# 456 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_28
# 458 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	waitfanfare
# 459 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_AKALA, Alola_Melemele_SamsonOakVilla_Dialogue_156
Alola_Melemele_SamsonOakVilla_Dialogue_154:
# 494 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_21, MSGBOX_AUTOCLOSE
# 496 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	release
	end

Alola_Melemele_SamsonOakVilla_Dialogue_144:
# 585 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	playfanfare MUS_HG_BUG_CONTEST_1ST_PLACE
# 586 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_19, MSGBOX_AUTOCLOSE
# 592 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	waitfanfare
# 593 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	playse SE_PIN
# 594 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	applymovement SamsonOakVilla, Alola_Melemele_SamsonOakVilla_Dialogue_Movement_0
# 595 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	waitmovement 0
# 596 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_25, MSGBOX_AUTOCLOSE
# 613 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	release
	end

Alola_Melemele_SamsonOakVilla_Dialogue_146:
# 583 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_PONI, Alola_Melemele_SamsonOakVilla_Dialogue_150
	goto Alola_Melemele_SamsonOakVilla_Dialogue_145

Alola_Melemele_SamsonOakVilla_Dialogue_147:
# 583 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_ULAULA, Alola_Melemele_SamsonOakVilla_Dialogue_146
	goto Alola_Melemele_SamsonOakVilla_Dialogue_145

Alola_Melemele_SamsonOakVilla_Dialogue_150:
# 583 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_MELEMELE, Alola_Melemele_SamsonOakVilla_Dialogue_144
	goto Alola_Melemele_SamsonOakVilla_Dialogue_145

Alola_Melemele_SamsonOakVilla_Dialogue_153:
# 461 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	playfanfare MUS_HG_BUG_CONTEST_1ST_PLACE
# 462 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_19, MSGBOX_AUTOCLOSE
# 468 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	waitfanfare
# 469 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	playse SE_PIN
# 470 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	applymovement SamsonOakVilla, Alola_Melemele_SamsonOakVilla_Dialogue_Movement_0
# 471 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	waitmovement 0
# 472 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_25, MSGBOX_AUTOCLOSE
# 489 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	release
	end

Alola_Melemele_SamsonOakVilla_Dialogue_155:
# 459 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_PONI, Alola_Melemele_SamsonOakVilla_Dialogue_159
	goto Alola_Melemele_SamsonOakVilla_Dialogue_154

Alola_Melemele_SamsonOakVilla_Dialogue_156:
# 459 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_ULAULA, Alola_Melemele_SamsonOakVilla_Dialogue_155
	goto Alola_Melemele_SamsonOakVilla_Dialogue_154

Alola_Melemele_SamsonOakVilla_Dialogue_159:
# 459 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_MELEMELE, Alola_Melemele_SamsonOakVilla_Dialogue_153
	goto Alola_Melemele_SamsonOakVilla_Dialogue_154


# 8 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
Alola_Melemele_SamsonOakVillaIntro_Trigger_Movement_0:
# 8 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	emote_exclamation_mark
# 8 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	face_down
	step_end

# 11 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
Alola_Melemele_SamsonOakVillaIntro_Trigger_Movement_1:
# 11 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	walk_down
# 11 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	walk_left
# 11 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	face_down
	step_end

# 22 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
Alola_Melemele_SamsonOakVillaIntro_Trigger_Movement_2:
# 22 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	walk_in_place_down
# 22 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	walk_in_place_down
	step_end

# 36 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
Alola_Melemele_SamsonOakVillaIntro_Trigger_Movement_3:
# 36 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	walk_right
# 36 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	walk_up
# 36 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	face_right
	step_end

# 52 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
Alola_Melemele_SamsonOakVilla_Dialogue_Movement_0:
# 52 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	emote_exclamation_mark
	step_end

Alola_Melemele_SamsonOakVillaIntro_Trigger_Text_0:
# 10 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	.string "Alola, {PLAYER}!$"

Alola_Melemele_SamsonOakVillaIntro_Trigger_Text_1:
# 13 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	.string "I'm glad you're here!\n"
	.string "Welcome to my villa!\p"
	.string "I'm staying here while I research the\n"
	.string "Alola Isles for their similarity to\l"
	.string "the Alola Region.\p"
	.string "I'm particularly interested in the\n"
	.string "phenomenon of “regional variants”.$"

Alola_Melemele_SamsonOakVillaIntro_Trigger_Text_2:
# 24 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	.string "You seem quite capable.\p"
	.string "You'd be perfect to help with my survey\n"
	.string "of the Alola Isles!\p"
	.string "Explore all the Isles have to offer,\n"
	.string "and if you find any familiar Pokémon\l"
	.string "that resemble those from Kanto…\l"
	.string "come back and show me your Pokédex!\p"
	.string "I'll be here patiently waiting to hear\n"
	.string "about your progress!$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_0:
# 54 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	.string "Wow!\n"
	.string "You saw the Guardian Dieties!\p"
	.string "Incredible work, {PLAYER}.\p"
	.string "I found this while wandering about.\p"
	.string "I'm not entirely sure what it's for,\n"
	.string "but you should take it.$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_1:
# 64 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	.string "The Alola Isles must truly be special if\n"
	.string "the Guardians themselves visited!$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_2:
# 73 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	.string "Thanks for your help with my research,\n"
	.string "{PLAYER}!\p"
	.string "Our understanding of the Alola Isles\n"
	.string "has greatly improved thanks to you!\p"
	.string "I hope you continue to explore the\n"
	.string "Isles to find all the secrets that\l"
	.string "they hold!$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_3:
# 109 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	.string "Alola {PLAYER}!\p"
	.string "So you managed to defeat all of the\n"
	.string "Totem Pokémon on the Isles, did you?\p"
	.string "That's quite an accomplishment!\p"
	.string "It's been long enough…\p"
	.string "I think it's about time we had a battle,\n"
	.string "don't you?$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_4:
# 122 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	.string "Great!\n"
	.string "I won't be taking it easy on you!$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_5:
# 124 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	.string "Incredible, {PLAYER}!$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_6:
# 131 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	.string "Wow, {PLAYER}!\n"
	.string "You really are a powerful Trainer!\p"
	.string "You've proven worthy of a secret\n"
	.string "I've been keeping about these isles…\p"
	.string "I'm not the only one who's noticed a\n"
	.string "striking resemblance between the Alola\l"
	.string "Isles and the Alola Region…\p"
	.string "It seems the Tapu Guardians themselves\n"
	.string "have been visiting the Isles.\p"
	.string "If you see them fly over the Isles, head\n"
	.string "to the totems… They may be there \l"
	.string "waiting for you!$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_7:
# 149 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	.string "What are you waiting for, {PLAYER}?\n"
	.string "Go out there and explore!$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_8:
# 157 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	.string "No worries, {PLAYER}!\p"
	.string "Take your time to prepare for the\n"
	.string "battle, and come back when you're\l"
	.string "ready!$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_9:
# 170 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	.string "Alola {PLAYER}!\p"
	.string "So you've found all the Alolan variants\n"
	.string "on the Isles, but have you defeated all\l"
	.string "the Totem Pokémon yet?\p"
	.string "You should look for a strange pillar on\n"
	.string "each isle, the Totem Pokémon will be\l"
	.string "guarding it!$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_10:
# 185 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	.string "Hello again, {PLAYER}!\p"
	.string "How's your research on the Alola Isles\n"
	.string "coming along?\p"
	.string "Would you like to share your progress\n"
	.string "about a specific isle with me?$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_11:
# 192 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	.string "Melemele Isle$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_12:
# 192 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	.string "Akala Isle$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_13:
# 192 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	.string "Ula'ula Isle$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_14:
# 192 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	.string "Poni Isle$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_15:
# 192 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	.string "Not right now.$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_16:
# 212 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	.string "Let me take a look at your Pokédex{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_17:
# 216 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	.string "Wow, {PLAYER}!$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_18:
# 218 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	.string "You found all the Alolan variants living\n"
	.string "on Melemele Isle!$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_19:
# 224 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	.string "And it looks like you've found all the\n"
	.string "Alolan variants on the other isles too!\p"
	.string "That's amazing, {PLAYER}!\p"
	.string "You should be very proud of yourself!$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_20:
# 234 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	.string "You've helped me validate that all\n"
	.string "of the Alolan variants are present on\l"
	.string "the Alola Isles!\p"
	.string "I'd like you to help me with one more\n"
	.string "thing…\p"
	.string "Could you help me investigate the Totem\n"
	.string "Pokémon that are said to be guarding\l"
	.string "the totems on each isle?\p"
	.string "But beware! These Totem Pokémon are\n"
	.string "said to be much stronger than their\l"
	.string "normal counterparts…\p"
	.string "You never know who might be watching\n"
	.string "to see if you are a worthy opponent!$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_21:
# 256 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	.string "Keep exploring the other isles and\n"
	.string "report your progress to me!$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_22:
# 282 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	.string "It seems you've already found all the\n"
	.string "Alolan variants on Melemele Isle!\p"
	.string "Great job!\p"
	.string "Keep exploring the other isles and\n"
	.string "report your progress to me!$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_23:
# 296 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	.string "Let me take a look at your Pokédex{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.\p"
	.string "It seems you haven't quite found all of\n"
	.string "the Alolan variants on Melemele Isle\l"
	.string "just yet.\p"
	.string "I've heard Melemele Isle has {COLOR RED}4 {COLOR DARK_GRAY}Alolan\n"
	.string "variants for you to find…\p"
	.string "{COLOR RED}Rattata{COLOR DARK_GRAY}, {COLOR RED}Raticate{COLOR DARK_GRAY}, {COLOR RED}Meowth{COLOR DARK_GRAY}, and {COLOR RED}Persian{COLOR DARK_GRAY}.\p"
	.string "Keep on searching and come back when\n"
	.string "you've caught them all!$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_24:
# 333 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	.string "You found all the Alolan variants living\n"
	.string "on Akala Isle!$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_25:
# 349 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	.string "Now that you've helped me validate that\n"
	.string "all of the Alolan variants are present\l"
	.string "on the Alola Isles.\p"
	.string "I'd like you to help me with one more\n"
	.string "thing…\p"
	.string "Could you help me investigate the Totem\n"
	.string "Pokémon that are said to be guarding\l"
	.string "the totems on each isle?\p"
	.string "But beware! These Totem Pokémon are\n"
	.string "said to be much stronger than their\l"
	.string "normal counterparts…\p"
	.string "You never know who might be watching\n"
	.string "to see if you are a worthy opponent!$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_26:
# 397 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	.string "It seems you've already found all the\n"
	.string "Alolan variants on Akala Isle!\p"
	.string "Great job!\p"
	.string "Keep exploring the other isles and\n"
	.string "report your progress to me!$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_27:
# 410 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	.string "Let me take a look at your Pokédex{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.\p"
	.string "It seems you haven't quite found all of\n"
	.string "the Alolan variants on Akala Isle\l"
	.string "just yet.\p"
	.string "I've heard Akala Isle has {COLOR RED}3 {COLOR DARK_GRAY}Alolan\n"
	.string "variants for you to find…\p"
	.string "{COLOR RED}Marowak{COLOR DARK_GRAY}, {COLOR RED}Diglett{COLOR DARK_GRAY}, and {COLOR RED}Dugtrio{COLOR DARK_GRAY}.\p"
	.string "Keep on searching and come back when\n"
	.string "you've caught them all!$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_28:
# 456 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	.string "You found all the Alolan variants living\n"
	.string "on Ula'ula Isle!$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_29:
# 520 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	.string "It seems you've already found all the\n"
	.string "Alolan variants on Ula'ula Isle!\p"
	.string "Great job!\p"
	.string "Keep exploring the other isles and\n"
	.string "report your progress to me!$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_30:
# 536 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	.string "Let me take a look at your Pokédex{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.\p"
	.string "It seems you haven't quite found all of\n"
	.string "the Alolan variants on Ula'ula Isle\l"
	.string "just yet.\p"
	.string "I've heard Ula'ula Isle has {COLOR RED}6 {COLOR DARK_GRAY}Alolan\n"
	.string "variants for you to find…\p"
	.string "{COLOR RED}Vulpix{COLOR DARK_GRAY}, {COLOR RED}Ninetales{COLOR DARK_GRAY}, {COLOR RED}Sandshrew{COLOR DARK_GRAY}, {COLOR RED}Sandslash{COLOR DARK_GRAY},\n"
	.string "{COLOR RED}Grimer{COLOR DARK_GRAY}, and {COLOR RED}Muk{COLOR DARK_GRAY}.\p"
	.string "Keep on searching and come back when\n"
	.string "you've caught them all!$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_31:
# 580 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	.string "You found all the Alolan variants living\n"
	.string "on Poni Isle!$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_32:
# 644 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	.string "It seems you've already found all the\n"
	.string "Alolan variants on Poni Isle!\p"
	.string "Great job!\p"
	.string "Keep exploring the other isles and\n"
	.string "report your progress to me!$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_33:
# 659 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	.string "Let me take a look at your Pokédex{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.\p"
	.string "It seems you haven't quite found all of\n"
	.string "the Alolan variants on Poni Isle\l"
	.string "just yet.\p"
	.string "I've heard Poni Isle has {COLOR RED}5 {COLOR DARK_GRAY}Alolan\n"
	.string "variants for you to find…\p"
	.string "{COLOR RED}Raichu{COLOR DARK_GRAY}, {COLOR RED}Geodude{COLOR DARK_GRAY}, {COLOR RED}Graveler{COLOR DARK_GRAY}, {COLOR RED}Golem{COLOR DARK_GRAY},\n"
	.string "and {COLOR RED}Exeggutor{COLOR DARK_GRAY}.\p"
	.string "Keep on searching and come back when\n"
	.string "you've caught them all!$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_34:
# 677 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	.string "No worries, {PLAYER}!\p"
	.string "Come back when you'd like to share your\n"
	.string "findings about the Alola Isles!$"
