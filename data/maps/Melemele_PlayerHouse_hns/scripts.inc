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
# 84 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_AKALA, Alola_Melemele_SamsonOakVilla_Dialogue_16
Alola_Melemele_SamsonOakVilla_Dialogue_14:
# 180 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_9
# 187 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	dynmultichoice 20, 4, TRUE, 4, 0, DYN_MULTICHOICE_CB_NONE, Alola_Melemele_SamsonOakVilla_Dialogue_Text_10, Alola_Melemele_SamsonOakVilla_Dialogue_Text_11, Alola_Melemele_SamsonOakVilla_Dialogue_Text_12, Alola_Melemele_SamsonOakVilla_Dialogue_Text_13, Alola_Melemele_SamsonOakVilla_Dialogue_Text_14
# 188 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq Alola_Melemele_SamsonOakVilla_Dialogue_31
# 302 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	compare VAR_RESULT, 1
	goto_if_eq Alola_Melemele_SamsonOakVilla_Dialogue_32
# 411 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	compare VAR_RESULT, 2
	goto_if_eq Alola_Melemele_SamsonOakVilla_Dialogue_33
# 532 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	compare VAR_RESULT, 3
	goto_if_eq Alola_Melemele_SamsonOakVilla_Dialogue_34
# 650 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_32, MSGBOX_AUTOCLOSE
# 654 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	release
	end

Alola_Melemele_SamsonOakVilla_Dialogue_1:
# 48 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	compare VAR_ALOLA_STATE, 3
	goto_if_eq Alola_Melemele_SamsonOakVilla_Dialogue_10
# 68 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_1, MSGBOX_AUTOCLOSE
# 77 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
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
# 61 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	setvar VAR_ALOLA_STATE, 4
# 62 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	clearflag FLAG_HIDE_PHANT_OUTSIDE
# 63 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	release
	end

Alola_Melemele_SamsonOakVilla_Dialogue_13:
# 86 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	goto_if_set FLAG_DEFEATED_MELEMELE_TOTEM, Alola_Melemele_SamsonOakVilla_Dialogue_25
Alola_Melemele_SamsonOakVilla_Dialogue_23:
# 165 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_8, MSGBOX_AUTOCLOSE
# 174 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	release
	end

Alola_Melemele_SamsonOakVilla_Dialogue_15:
# 84 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_PONI, Alola_Melemele_SamsonOakVilla_Dialogue_19
	goto Alola_Melemele_SamsonOakVilla_Dialogue_14

Alola_Melemele_SamsonOakVilla_Dialogue_16:
# 84 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_ULAULA, Alola_Melemele_SamsonOakVilla_Dialogue_15
	goto Alola_Melemele_SamsonOakVilla_Dialogue_14

Alola_Melemele_SamsonOakVilla_Dialogue_19:
# 84 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_MELEMELE, Alola_Melemele_SamsonOakVilla_Dialogue_13
	goto Alola_Melemele_SamsonOakVilla_Dialogue_14

Alola_Melemele_SamsonOakVilla_Dialogue_22:
# 88 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	goto_if_set FLAG_DEFEATED_SAMSON_OAK, Alola_Melemele_SamsonOakVilla_Dialogue_40
# 104 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_2, MSGBOX_YESNO
# 115 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	compare VAR_RESULT, YES
	goto_if_eq Alola_Melemele_SamsonOakVilla_Dialogue_55
# 152 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_7, MSGBOX_AUTOCLOSE
# 157 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	release
	end

Alola_Melemele_SamsonOakVilla_Dialogue_24:
# 86 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	goto_if_set FLAG_DEFEATED_ULAULA_TOTEM, Alola_Melemele_SamsonOakVilla_Dialogue_28
	goto Alola_Melemele_SamsonOakVilla_Dialogue_23

Alola_Melemele_SamsonOakVilla_Dialogue_25:
# 86 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	goto_if_set FLAG_DEFEATED_AKALA_TOTEM, Alola_Melemele_SamsonOakVilla_Dialogue_24
	goto Alola_Melemele_SamsonOakVilla_Dialogue_23

Alola_Melemele_SamsonOakVilla_Dialogue_28:
# 86 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	goto_if_set FLAG_DEFEATED_PONI_TOTEM, Alola_Melemele_SamsonOakVilla_Dialogue_22
	goto Alola_Melemele_SamsonOakVilla_Dialogue_23

Alola_Melemele_SamsonOakVilla_Dialogue_31:
# 190 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	getcaughtmon SPECIES_MEOWTH_ALOLA
# 191 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	compare VAR_RESULT, 1
	goto_if_eq Alola_Melemele_SamsonOakVilla_Dialogue_44
Alola_Melemele_SamsonOakVilla_Dialogue_43:
# 291 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_22, MSGBOX_AUTOCLOSE
# 299 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	release
	end

Alola_Melemele_SamsonOakVilla_Dialogue_32:
# 303 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	getcaughtmon SPECIES_MAROWAK_ALOLA
# 304 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	compare VAR_RESULT, 1
	goto_if_eq Alola_Melemele_SamsonOakVilla_Dialogue_47
Alola_Melemele_SamsonOakVilla_Dialogue_46:
# 400 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_25, MSGBOX_AUTOCLOSE
# 408 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	release
	end

Alola_Melemele_SamsonOakVilla_Dialogue_33:
# 412 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	getcaughtmon SPECIES_VULPIX_ALOLA
# 413 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	compare VAR_RESULT, 1
	goto_if_eq Alola_Melemele_SamsonOakVilla_Dialogue_50
Alola_Melemele_SamsonOakVilla_Dialogue_49:
# 521 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_28, MSGBOX_AUTOCLOSE
# 529 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	release
	end

Alola_Melemele_SamsonOakVilla_Dialogue_34:
# 533 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	getcaughtmon SPECIES_RAICHU_ALOLA
# 534 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	compare VAR_RESULT, 1
	goto_if_eq Alola_Melemele_SamsonOakVilla_Dialogue_53
Alola_Melemele_SamsonOakVilla_Dialogue_52:
# 638 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_31, MSGBOX_AUTOCLOSE
# 646 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	release
	end

Alola_Melemele_SamsonOakVilla_Dialogue_40:
# 90 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_1, MSGBOX_AUTOCLOSE
# 99 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	release
	end

Alola_Melemele_SamsonOakVilla_Dialogue_44:
# 193 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	getcaughtmon SPECIES_PERSIAN_ALOLA
# 194 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	compare VAR_RESULT, 1
	goto_if_eq Alola_Melemele_SamsonOakVilla_Dialogue_58
	goto Alola_Melemele_SamsonOakVilla_Dialogue_43

Alola_Melemele_SamsonOakVilla_Dialogue_47:
# 306 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	getcaughtmon SPECIES_DIGLETT_ALOLA
# 307 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	compare VAR_RESULT, 1
	goto_if_eq Alola_Melemele_SamsonOakVilla_Dialogue_60
	goto Alola_Melemele_SamsonOakVilla_Dialogue_46

Alola_Melemele_SamsonOakVilla_Dialogue_50:
# 415 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	getcaughtmon SPECIES_NINETALES_ALOLA
# 416 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	compare VAR_RESULT, 1
	goto_if_eq Alola_Melemele_SamsonOakVilla_Dialogue_62
	goto Alola_Melemele_SamsonOakVilla_Dialogue_49

Alola_Melemele_SamsonOakVilla_Dialogue_53:
# 536 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	getcaughtmon SPECIES_GEODUDE_ALOLA
# 537 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	compare VAR_RESULT, 1
	goto_if_eq Alola_Melemele_SamsonOakVilla_Dialogue_64
	goto Alola_Melemele_SamsonOakVilla_Dialogue_52

Alola_Melemele_SamsonOakVilla_Dialogue_55:
# 117 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_3
# 119 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	trainerbattle_no_intro TRAINER_SAMSON_OAK_HNS, Alola_Melemele_SamsonOakVilla_Dialogue_Text_4
# 120 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	special HealPlayerParty
# 121 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	setflag FLAG_DEFEATED_SAMSON_OAK
# 122 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	setflag FLAG_FLYOVER_TAPU_KOKO
# 123 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	setflag FLAG_FLYOVER_TAPU_LELE
# 124 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	setflag FLAG_FLYOVER_TAPU_BULU
# 125 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	setflag FLAG_FLYOVER_TAPU_FINI
# 126 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_5, MSGBOX_AUTOCLOSE
# 142 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	playse SE_PIN
# 143 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	applymovement SamsonOakVilla, Alola_Melemele_SamsonOakVilla_Dialogue_Movement_0
# 144 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_6, MSGBOX_AUTOCLOSE
# 146 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	setvar VAR_ALOLA_STATE, 3
# 147 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	release
	end

Alola_Melemele_SamsonOakVilla_Dialogue_58:
# 196 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	getcaughtmon SPECIES_RATTATA_ALOLA
# 197 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	compare VAR_RESULT, 1
	goto_if_eq Alola_Melemele_SamsonOakVilla_Dialogue_66
	goto Alola_Melemele_SamsonOakVilla_Dialogue_43

Alola_Melemele_SamsonOakVilla_Dialogue_60:
# 309 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	getcaughtmon SPECIES_DUGTRIO_ALOLA
# 310 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	compare VAR_RESULT, 1
	goto_if_eq Alola_Melemele_SamsonOakVilla_Dialogue_68
	goto Alola_Melemele_SamsonOakVilla_Dialogue_46

Alola_Melemele_SamsonOakVilla_Dialogue_62:
# 418 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	getcaughtmon SPECIES_SANDSHREW_ALOLA
# 419 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	compare VAR_RESULT, 1
	goto_if_eq Alola_Melemele_SamsonOakVilla_Dialogue_70
	goto Alola_Melemele_SamsonOakVilla_Dialogue_49

Alola_Melemele_SamsonOakVilla_Dialogue_64:
# 539 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	getcaughtmon SPECIES_GRAVELER_ALOLA
# 540 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	compare VAR_RESULT, 1
	goto_if_eq Alola_Melemele_SamsonOakVilla_Dialogue_72
	goto Alola_Melemele_SamsonOakVilla_Dialogue_52

Alola_Melemele_SamsonOakVilla_Dialogue_66:
# 199 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	getcaughtmon SPECIES_RATICATE_ALOLA
# 200 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	compare VAR_RESULT, 1
	goto_if_eq Alola_Melemele_SamsonOakVilla_Dialogue_74
	goto Alola_Melemele_SamsonOakVilla_Dialogue_43

Alola_Melemele_SamsonOakVilla_Dialogue_68:
# 312 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	goto_if_unset FLAG_CAUGHT_ALL_AKALA, Alola_Melemele_SamsonOakVilla_Dialogue_76
# 387 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_24, MSGBOX_AUTOCLOSE
# 394 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	release
	end

Alola_Melemele_SamsonOakVilla_Dialogue_70:
# 421 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	getcaughtmon SPECIES_SANDSLASH_ALOLA
# 422 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	compare VAR_RESULT, 1
	goto_if_eq Alola_Melemele_SamsonOakVilla_Dialogue_79
	goto Alola_Melemele_SamsonOakVilla_Dialogue_49

Alola_Melemele_SamsonOakVilla_Dialogue_72:
# 542 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	getcaughtmon SPECIES_GOLEM_ALOLA
# 543 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	compare VAR_RESULT, 1
	goto_if_eq Alola_Melemele_SamsonOakVilla_Dialogue_81
	goto Alola_Melemele_SamsonOakVilla_Dialogue_52

Alola_Melemele_SamsonOakVilla_Dialogue_74:
# 202 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	goto_if_unset FLAG_CAUGHT_ALL_MELEMELE, Alola_Melemele_SamsonOakVilla_Dialogue_83
# 277 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_21, MSGBOX_AUTOCLOSE
# 284 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	release
	end

Alola_Melemele_SamsonOakVilla_Dialogue_76:
# 314 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_MELEMELE, Alola_Melemele_SamsonOakVilla_Dialogue_86
# 314 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_ULAULA, Alola_Melemele_SamsonOakVilla_Dialogue_86
# 314 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_PONI, Alola_Melemele_SamsonOakVilla_Dialogue_86
# 369 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	setflag FLAG_CAUGHT_ALL_AKALA
# 370 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_15, MSGBOX_AUTOCLOSE
# 371 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	playse SE_PIN
# 372 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	applymovement SamsonOakVilla, Alola_Melemele_SamsonOakVilla_Dialogue_Movement_0
# 373 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	waitmovement 0
# 374 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_16
# 375 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	playfanfare MUS_HG_OBTAIN_EGG
# 376 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_23
# 378 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	waitfanfare
# 379 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_20
# 381 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	release
	end

Alola_Melemele_SamsonOakVilla_Dialogue_79:
# 424 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	getcaughtmon SPECIES_GRIMER_ALOLA
# 425 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	compare VAR_RESULT, 1
	goto_if_eq Alola_Melemele_SamsonOakVilla_Dialogue_93
	goto Alola_Melemele_SamsonOakVilla_Dialogue_49

Alola_Melemele_SamsonOakVilla_Dialogue_81:
# 545 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	getcaughtmon SPECIES_EXEGGUTOR_ALOLA
# 546 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	compare VAR_RESULT, 1
	goto_if_eq Alola_Melemele_SamsonOakVilla_Dialogue_95
	goto Alola_Melemele_SamsonOakVilla_Dialogue_52

Alola_Melemele_SamsonOakVilla_Dialogue_83:
# 204 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_AKALA, Alola_Melemele_SamsonOakVilla_Dialogue_97
# 204 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_ULAULA, Alola_Melemele_SamsonOakVilla_Dialogue_97
# 204 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_PONI, Alola_Melemele_SamsonOakVilla_Dialogue_97
# 259 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	setflag FLAG_CAUGHT_ALL_MELEMELE
# 260 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_15, MSGBOX_AUTOCLOSE
# 261 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	playse SE_PIN
# 262 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	applymovement SamsonOakVilla, Alola_Melemele_SamsonOakVilla_Dialogue_Movement_0
# 263 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	waitmovement 0
# 264 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_16
# 265 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	playfanfare MUS_HG_OBTAIN_EGG
# 266 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_17
# 268 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	waitfanfare
# 269 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_20, MSGBOX_AUTOCLOSE
# 271 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	release
	end

Alola_Melemele_SamsonOakVilla_Dialogue_86:
# 316 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	setflag FLAG_CAUGHT_ALL_AKALA
# 317 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_15, MSGBOX_AUTOCLOSE
# 318 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	playse SE_PIN
# 319 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	applymovement SamsonOakVilla, Alola_Melemele_SamsonOakVilla_Dialogue_Movement_0
# 320 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	waitmovement 0
# 321 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_16
# 322 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	playfanfare MUS_HG_OBTAIN_EGG
# 323 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_23
# 325 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	waitfanfare
# 326 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_AKALA, Alola_Melemele_SamsonOakVilla_Dialogue_107
Alola_Melemele_SamsonOakVilla_Dialogue_105:
# 361 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_20
# 363 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	release
	end

Alola_Melemele_SamsonOakVilla_Dialogue_93:
# 427 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	getcaughtmon SPECIES_MUK_ALOLA
# 428 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	compare VAR_RESULT, 1
	goto_if_eq Alola_Melemele_SamsonOakVilla_Dialogue_113
	goto Alola_Melemele_SamsonOakVilla_Dialogue_49

Alola_Melemele_SamsonOakVilla_Dialogue_95:
# 548 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	goto_if_unset FLAG_CAUGHT_ALL_PONI, Alola_Melemele_SamsonOakVilla_Dialogue_115
# 623 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_30, MSGBOX_AUTOCLOSE
# 630 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	release
	end

Alola_Melemele_SamsonOakVilla_Dialogue_97:
# 206 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	setflag FLAG_CAUGHT_ALL_MELEMELE
# 207 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_15, MSGBOX_AUTOCLOSE
# 208 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	playse SE_PIN
# 209 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	applymovement SamsonOakVilla, Alola_Melemele_SamsonOakVilla_Dialogue_Movement_0
# 210 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	waitmovement 0
# 211 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_16
# 212 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	playfanfare MUS_HG_OBTAIN_EGG
# 213 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_17
# 215 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	waitfanfare
# 216 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_AKALA, Alola_Melemele_SamsonOakVilla_Dialogue_121
Alola_Melemele_SamsonOakVilla_Dialogue_119:
# 251 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_20, MSGBOX_AUTOCLOSE
# 253 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	release
	end

Alola_Melemele_SamsonOakVilla_Dialogue_104:
# 328 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	playfanfare MUS_HG_BUG_CONTEST_1ST_PLACE
# 329 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_18, MSGBOX_AUTOCLOSE
# 335 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	waitfanfare
# 336 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	playse SE_PIN
# 337 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	applymovement SamsonOakVilla, Alola_Melemele_SamsonOakVilla_Dialogue_Movement_0
# 338 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	waitmovement 0
# 339 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_19
# 356 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	release
	end

Alola_Melemele_SamsonOakVilla_Dialogue_106:
# 326 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_PONI, Alola_Melemele_SamsonOakVilla_Dialogue_110
	goto Alola_Melemele_SamsonOakVilla_Dialogue_105

Alola_Melemele_SamsonOakVilla_Dialogue_107:
# 326 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_ULAULA, Alola_Melemele_SamsonOakVilla_Dialogue_106
	goto Alola_Melemele_SamsonOakVilla_Dialogue_105

Alola_Melemele_SamsonOakVilla_Dialogue_110:
# 326 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_MELEMELE, Alola_Melemele_SamsonOakVilla_Dialogue_104
	goto Alola_Melemele_SamsonOakVilla_Dialogue_105

Alola_Melemele_SamsonOakVilla_Dialogue_113:
# 430 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	goto_if_unset FLAG_CAUGHT_ALL_ULAULA, Alola_Melemele_SamsonOakVilla_Dialogue_127
# 505 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_27, MSGBOX_AUTOCLOSE
# 512 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	release
	end

Alola_Melemele_SamsonOakVilla_Dialogue_115:
# 550 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_MELEMELE, Alola_Melemele_SamsonOakVilla_Dialogue_130
# 550 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_AKALA, Alola_Melemele_SamsonOakVilla_Dialogue_130
# 550 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_ULAULA, Alola_Melemele_SamsonOakVilla_Dialogue_130
# 605 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	setflag FLAG_CAUGHT_ALL_PONI
# 606 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_15, MSGBOX_AUTOCLOSE
# 607 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	playse SE_PIN
# 608 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	applymovement SamsonOakVilla, Alola_Melemele_SamsonOakVilla_Dialogue_Movement_0
# 609 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	waitmovement 0
# 610 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_16
# 611 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	playfanfare MUS_HG_OBTAIN_EGG
# 612 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_29
# 614 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	waitfanfare
# 615 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_20, MSGBOX_AUTOCLOSE
# 617 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	release
	end

Alola_Melemele_SamsonOakVilla_Dialogue_118:
# 218 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	playfanfare MUS_HG_BUG_CONTEST_1ST_PLACE
# 219 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_18, MSGBOX_AUTOCLOSE
# 225 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	waitfanfare
# 226 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	playse SE_PIN
# 227 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	applymovement SamsonOakVilla, Alola_Melemele_SamsonOakVilla_Dialogue_Movement_0
# 228 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	waitmovement 0
# 229 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_19, MSGBOX_AUTOCLOSE
# 246 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	release
	end

Alola_Melemele_SamsonOakVilla_Dialogue_120:
# 216 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_PONI, Alola_Melemele_SamsonOakVilla_Dialogue_124
	goto Alola_Melemele_SamsonOakVilla_Dialogue_119

Alola_Melemele_SamsonOakVilla_Dialogue_121:
# 216 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_ULAULA, Alola_Melemele_SamsonOakVilla_Dialogue_120
	goto Alola_Melemele_SamsonOakVilla_Dialogue_119

Alola_Melemele_SamsonOakVilla_Dialogue_124:
# 216 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_MELEMELE, Alola_Melemele_SamsonOakVilla_Dialogue_118
	goto Alola_Melemele_SamsonOakVilla_Dialogue_119

Alola_Melemele_SamsonOakVilla_Dialogue_127:
# 432 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_MELEMELE, Alola_Melemele_SamsonOakVilla_Dialogue_137
# 432 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_AKALA, Alola_Melemele_SamsonOakVilla_Dialogue_137
# 432 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_PONI, Alola_Melemele_SamsonOakVilla_Dialogue_137
# 487 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	setflag FLAG_CAUGHT_ALL_ULAULA
# 488 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_15, MSGBOX_AUTOCLOSE
# 489 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	playse SE_PIN
# 490 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	applymovement SamsonOakVilla, Alola_Melemele_SamsonOakVilla_Dialogue_Movement_0
# 491 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	waitmovement 0
# 492 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_16
# 493 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	playfanfare MUS_HG_OBTAIN_EGG
# 494 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_26
# 496 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	waitfanfare
# 497 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_20, MSGBOX_AUTOCLOSE
# 499 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	release
	end

Alola_Melemele_SamsonOakVilla_Dialogue_130:
# 552 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	setflag FLAG_CAUGHT_ALL_PONI
# 553 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_15, MSGBOX_AUTOCLOSE
# 554 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	playse SE_PIN
# 555 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	applymovement SamsonOakVilla, Alola_Melemele_SamsonOakVilla_Dialogue_Movement_0
# 556 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	waitmovement 0
# 557 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_16
# 558 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	playfanfare MUS_HG_OBTAIN_EGG
# 559 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_29
# 561 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	waitfanfare
# 562 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_AKALA, Alola_Melemele_SamsonOakVilla_Dialogue_147
Alola_Melemele_SamsonOakVilla_Dialogue_145:
# 597 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_20, MSGBOX_AUTOCLOSE
# 599 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	release
	end

Alola_Melemele_SamsonOakVilla_Dialogue_137:
# 434 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	setflag FLAG_CAUGHT_ALL_ULAULA
# 435 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_15, MSGBOX_AUTOCLOSE
# 436 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	playse SE_PIN
# 437 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	applymovement SamsonOakVilla, Alola_Melemele_SamsonOakVilla_Dialogue_Movement_0
# 438 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	waitmovement 0
# 439 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_16
# 440 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	playfanfare MUS_HG_OBTAIN_EGG
# 441 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_26
# 443 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	waitfanfare
# 444 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_AKALA, Alola_Melemele_SamsonOakVilla_Dialogue_156
Alola_Melemele_SamsonOakVilla_Dialogue_154:
# 479 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_20, MSGBOX_AUTOCLOSE
# 481 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	release
	end

Alola_Melemele_SamsonOakVilla_Dialogue_144:
# 564 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	playfanfare MUS_HG_BUG_CONTEST_1ST_PLACE
# 565 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_18, MSGBOX_AUTOCLOSE
# 571 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	waitfanfare
# 572 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	playse SE_PIN
# 573 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	applymovement SamsonOakVilla, Alola_Melemele_SamsonOakVilla_Dialogue_Movement_0
# 574 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	waitmovement 0
# 575 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_19, MSGBOX_AUTOCLOSE
# 592 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	release
	end

Alola_Melemele_SamsonOakVilla_Dialogue_146:
# 562 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_PONI, Alola_Melemele_SamsonOakVilla_Dialogue_150
	goto Alola_Melemele_SamsonOakVilla_Dialogue_145

Alola_Melemele_SamsonOakVilla_Dialogue_147:
# 562 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_ULAULA, Alola_Melemele_SamsonOakVilla_Dialogue_146
	goto Alola_Melemele_SamsonOakVilla_Dialogue_145

Alola_Melemele_SamsonOakVilla_Dialogue_150:
# 562 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_MELEMELE, Alola_Melemele_SamsonOakVilla_Dialogue_144
	goto Alola_Melemele_SamsonOakVilla_Dialogue_145

Alola_Melemele_SamsonOakVilla_Dialogue_153:
# 446 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	playfanfare MUS_HG_BUG_CONTEST_1ST_PLACE
# 447 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_18, MSGBOX_AUTOCLOSE
# 453 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	waitfanfare
# 454 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	playse SE_PIN
# 455 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	applymovement SamsonOakVilla, Alola_Melemele_SamsonOakVilla_Dialogue_Movement_0
# 456 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	waitmovement 0
# 457 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_19, MSGBOX_AUTOCLOSE
# 474 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	release
	end

Alola_Melemele_SamsonOakVilla_Dialogue_155:
# 444 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_PONI, Alola_Melemele_SamsonOakVilla_Dialogue_159
	goto Alola_Melemele_SamsonOakVilla_Dialogue_154

Alola_Melemele_SamsonOakVilla_Dialogue_156:
# 444 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_ULAULA, Alola_Melemele_SamsonOakVilla_Dialogue_155
	goto Alola_Melemele_SamsonOakVilla_Dialogue_154

Alola_Melemele_SamsonOakVilla_Dialogue_159:
# 444 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
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
	.string "Welcome to my Villa!\p"
	.string "I'm staying here while I research the\n"
	.string "Alola Isles for their similarity to\l"
	.string "the Alola Region.\p"
	.string "I'm particularly interested in the\n"
	.string "phenomenon of “Regional Variants”.$"

Alola_Melemele_SamsonOakVillaIntro_Trigger_Text_2:
# 24 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	.string "You seem quite capable.\p"
	.string "You'd be perfect to help with my survey\n"
	.string "of the Alola Isles!\p"
	.string "Explore all the Isles have to offer,\n"
	.string "and if you find any familiar Pokémon\l"
	.string "that resemble those from Kanto…\l"
	.string "come back and show me your PokéDex!\p"
	.string "I'll be here patiently waiting to hear\n"
	.string "about your progress!$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_0:
# 54 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	.string "Wow!\n"
	.string "You saw the Guardian Dieties!\p"
	.string "Incredible work, {PLAYER}.\p"
	.string "The Alola Isles must truly be special if\n"
	.string "the Guardians themselves visited!$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_1:
# 68 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	.string "Thanks for your help with my research,\n"
	.string "{PLAYER}!\p"
	.string "Our understanding of the Alola Isles\n"
	.string "has greatly improved thanks to you!\p"
	.string "I hope you continue to explore the\n"
	.string "Isles to find all the secrets that\l"
	.string "they hold!$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_2:
# 104 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	.string "Alola {PLAYER}!\p"
	.string "So you managed to defeat all of the\n"
	.string "Totem Pokémon on the Isles, did you?\p"
	.string "That's quite an accomplishment!\p"
	.string "It's been long enough…\p"
	.string "I think it's about time we had a battle,\n"
	.string "don't you?$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_3:
# 117 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	.string "Great!\n"
	.string "I won't be taking it easy on you!$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_4:
# 119 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	.string "Incredible, {PLAYER}!$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_5:
# 126 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	.string "Wow, {PLAYER}!\n"
	.string "You really are a powerful Trainer!\p"
	.string "You've proven worthy of a secret\n"
	.string "I've been keeping about these Isles…\p"
	.string "I'm not the only one who's noticed a\n"
	.string "striking resemblance between the Alola\l"
	.string "Isles and the Alola Region…\p"
	.string "It seems the Tapu Guardians themselves\n"
	.string "have been visiting the Isles.\p"
	.string "If you see them fly over the Isles, head\n"
	.string "to the Totem Pillars… They may be there \l"
	.string "waiting for you!$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_6:
# 144 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	.string "What are you waiting for, {PLAYER}?\n"
	.string "Go out there and explore!$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_7:
# 152 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	.string "No worries, {PLAYER}!\p"
	.string "Take your time to prepare for the\n"
	.string "battle, and come back when you're\l"
	.string "ready!$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_8:
# 165 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	.string "Alola {PLAYER}!\p"
	.string "So you've found all the Alolan variants\n"
	.string "on the Isles, but have you defeated all\l"
	.string "the Totem Pokémon yet?\p"
	.string "You should look for a strange pillar on\n"
	.string "each Isle, the Totem Pokémon will be\l"
	.string "guarding it!$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_9:
# 180 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	.string "Hello again, {PLAYER}!\p"
	.string "How's your research on the Alola Isles\n"
	.string "coming along?\p"
	.string "Would you like to share your progress\n"
	.string "about a specific Isle with me?$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_10:
# 187 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	.string "Melemele Isle$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_11:
# 187 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	.string "Akala Isle$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_12:
# 187 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	.string "Ula'ula Isle$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_13:
# 187 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	.string "Poni Isle$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_14:
# 187 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	.string "Not right now.$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_15:
# 207 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	.string "Let me take a look at your PokéDex{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_16:
# 211 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	.string "Wow, {PLAYER}!$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_17:
# 213 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	.string "You found all the Alolan variants living\n"
	.string "on Melemele Isle!$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_18:
# 219 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	.string "And it looks like you've found all the\n"
	.string "Alolan variants on the other Isles too!\p"
	.string "That's amazing, {PLAYER}!\p"
	.string "You should be very proud of yourself!$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_19:
# 229 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	.string "Now that you've helped me validate that\n"
	.string "all of the Alolan variants are present\l"
	.string "on the Alola Isles.\p"
	.string "I'd like you to help me with one more\n"
	.string "thing…\p"
	.string "Could you help me investigate the Totem\n"
	.string "Pokémon that are said to be guarding\l"
	.string "the Totem Pillars on each Isle?\p"
	.string "But beware! These Totem Pokémon are\n"
	.string "said to be much stronger than their\l"
	.string "normal counterparts…\p"
	.string "You never know who might be watching\n"
	.string "to see if you are a worthy opponent!$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_20:
# 251 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	.string "Keep exploring the other Isles and\n"
	.string "report your progress to me!$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_21:
# 277 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	.string "It seems you've already found all the\n"
	.string "Alolan variants on Melemele Isle!\p"
	.string "Great job!\p"
	.string "Keep exploring the other Isles and\n"
	.string "report your progress to me!$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_22:
# 291 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	.string "Let me take a look at your PokéDex{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.\p"
	.string "It seems you haven't quite found all of\n"
	.string "the Alolan variants on Melemele Isle\l"
	.string "just yet.\p"
	.string "Keep on searching and come back when\n"
	.string "you've caught them all!$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_23:
# 323 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	.string "You found all the Alolan variants living\n"
	.string "on Akala Isle!$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_24:
# 387 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	.string "It seems you've already found all the\n"
	.string "Alolan variants on Akala Isle!\p"
	.string "Great job!\p"
	.string "Keep exploring the other Isles and\n"
	.string "report your progress to me!$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_25:
# 400 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	.string "Let me take a look at your PokéDex{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.\p"
	.string "It seems you haven't quite found all of\n"
	.string "the Alolan variants on Akala Isle\l"
	.string "just yet.\p"
	.string "Keep on searching and come back when\n"
	.string "you've caught them all!$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_26:
# 441 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	.string "You found all the Alolan variants living\n"
	.string "on Ula'ula Isle!$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_27:
# 505 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	.string "It seems you've already found all the\n"
	.string "Alolan variants on Ula'ula Isle!\p"
	.string "Great job!\p"
	.string "Keep exploring the other Isles and\n"
	.string "report your progress to me!$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_28:
# 521 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	.string "Let me take a look at your PokéDex{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.\p"
	.string "It seems you haven't quite found all of\n"
	.string "the Alolan variants on Ula'ula Isle\l"
	.string "just yet.\p"
	.string "Keep on searching and come back when\n"
	.string "you've caught them all!$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_29:
# 559 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	.string "You found all the Alolan variants living\n"
	.string "on Poni Isle!$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_30:
# 623 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	.string "It seems you've already found all the\n"
	.string "Alolan variants on Poni Isle!\p"
	.string "Great job!\p"
	.string "Keep exploring the other Isles and\n"
	.string "report your progress to me!$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_31:
# 638 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	.string "Let me take a look at your PokéDex{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.\p"
	.string "It seems you haven't quite found all of\n"
	.string "the Alolan variants on Poni Isle\l"
	.string "just yet.\p"
	.string "Keep on searching and come back when\n"
	.string "you've caught them all!$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_32:
# 650 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	.string "No worries, {PLAYER}!\p"
	.string "Come back when you'd like to share your\n"
	.string "findings about the Alola Isles!$"
