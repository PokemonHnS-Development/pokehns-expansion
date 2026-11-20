Melemele_PlayerHouse_hns_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Melemele_PlayerHouse_hns_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE
	.byte 0

Melemele_PlayerHouse_hns_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE:
	map_script_2 VAR_ALOLA_STATE, 1, Alola_Melemele_SamsonOakVillaIntro_Trigger
	.2byte 0


Alola_Melemele_SamsonOakVillaIntro_Trigger::
	lock
	playse SE_PIN
	applymovement SamsonOakVilla, Alola_Melemele_SamsonOakVillaIntro_Trigger_Movement_0
	waitmovement 0
	msgbox Alola_Melemele_SamsonOakVillaIntro_Trigger_Text_0
	applymovement SamsonOakVilla, Alola_Melemele_SamsonOakVillaIntro_Trigger_Movement_1
	waitmovement 0
	msgbox Alola_Melemele_SamsonOakVillaIntro_Trigger_Text_1, MSGBOX_AUTOCLOSE
	applymovement SamsonOakVilla, Alola_Melemele_SamsonOakVillaIntro_Trigger_Movement_2
	waitmovement 0
	msgbox Alola_Melemele_SamsonOakVillaIntro_Trigger_Text_2, MSGBOX_AUTOCLOSE
	applymovement SamsonOakVilla, Alola_Melemele_SamsonOakVillaIntro_Trigger_Movement_3
	waitmovement 0
	setvar VAR_ALOLA_STATE, 2
	release
	end


Alola_Melemele_SamsonOakVilla_Dialogue::
	lock
	faceplayer
	goto_if_set FLAG_BATTLED_TAPU_KOKO, Alola_Melemele_SamsonOakVilla_Dialogue_4
Alola_Melemele_SamsonOakVilla_Dialogue_2:
	goto_if_set FLAG_CAUGHT_ALL_AKALA, Alola_Melemele_SamsonOakVilla_Dialogue_16
Alola_Melemele_SamsonOakVilla_Dialogue_14:
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_10
	dynmultichoice 20, 4, FALSE, 4, 0, DYN_MULTICHOICE_CB_NONE, Alola_Melemele_SamsonOakVilla_Dialogue_Text_11, Alola_Melemele_SamsonOakVilla_Dialogue_Text_12, Alola_Melemele_SamsonOakVilla_Dialogue_Text_13, Alola_Melemele_SamsonOakVilla_Dialogue_Text_14, Alola_Melemele_SamsonOakVilla_Dialogue_Text_15
	compare VAR_RESULT, 0
	goto_if_eq Alola_Melemele_SamsonOakVilla_Dialogue_31
	compare VAR_RESULT, 1
	goto_if_eq Alola_Melemele_SamsonOakVilla_Dialogue_32
	compare VAR_RESULT, 2
	goto_if_eq Alola_Melemele_SamsonOakVilla_Dialogue_33
	compare VAR_RESULT, 3
	goto_if_eq Alola_Melemele_SamsonOakVilla_Dialogue_53
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_34, MSGBOX_AUTOCLOSE
	release
	end

Alola_Melemele_SamsonOakVilla_Dialogue_1:
	compare VAR_ALOLA_STATE, 3
	goto_if_eq Alola_Melemele_SamsonOakVilla_Dialogue_10
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_2, MSGBOX_AUTOCLOSE
	release
	end

Alola_Melemele_SamsonOakVilla_Dialogue_3:
	goto_if_set FLAG_BATTLED_TAPU_BULU, Alola_Melemele_SamsonOakVilla_Dialogue_7
	goto Alola_Melemele_SamsonOakVilla_Dialogue_2

Alola_Melemele_SamsonOakVilla_Dialogue_4:
	goto_if_set FLAG_BATTLED_TAPU_LELE, Alola_Melemele_SamsonOakVilla_Dialogue_3
	goto Alola_Melemele_SamsonOakVilla_Dialogue_2

Alola_Melemele_SamsonOakVilla_Dialogue_7:
	goto_if_set FLAG_BATTLED_TAPU_FINI, Alola_Melemele_SamsonOakVilla_Dialogue_1
	goto Alola_Melemele_SamsonOakVilla_Dialogue_2

Alola_Melemele_SamsonOakVilla_Dialogue_10:
	msgbox Alola_Melemele_SamsonOakVillaIntro_Trigger_Text_0, MSGBOX_AUTOCLOSE
	playse SE_PIN
	applymovement SamsonOakVilla, Alola_Melemele_SamsonOakVilla_Dialogue_Movement_0
	waitmovement 0
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_0, MSGBOX_AUTOCLOSE
	giveitem ITEM_BEAST_BALL
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_1, MSGBOX_AUTOCLOSE
	setvar VAR_ALOLA_STATE, 4
	clearflag FLAG_HIDE_PHANT_OUTSIDE
	release
	end

Alola_Melemele_SamsonOakVilla_Dialogue_13:
	goto_if_set FLAG_DEFEATED_MELEMELE_TOTEM, Alola_Melemele_SamsonOakVilla_Dialogue_25
Alola_Melemele_SamsonOakVilla_Dialogue_23:
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_9, MSGBOX_AUTOCLOSE
	release
	end

Alola_Melemele_SamsonOakVilla_Dialogue_15:
	goto_if_set FLAG_CAUGHT_ALL_PONI, Alola_Melemele_SamsonOakVilla_Dialogue_19
	goto Alola_Melemele_SamsonOakVilla_Dialogue_14

Alola_Melemele_SamsonOakVilla_Dialogue_16:
	goto_if_set FLAG_CAUGHT_ALL_ULAULA, Alola_Melemele_SamsonOakVilla_Dialogue_15
	goto Alola_Melemele_SamsonOakVilla_Dialogue_14

Alola_Melemele_SamsonOakVilla_Dialogue_19:
	goto_if_set FLAG_CAUGHT_ALL_MELEMELE, Alola_Melemele_SamsonOakVilla_Dialogue_13
	goto Alola_Melemele_SamsonOakVilla_Dialogue_14

Alola_Melemele_SamsonOakVilla_Dialogue_22:
	goto_if_set FLAG_DEFEATED_SAMSON_OAK, Alola_Melemele_SamsonOakVilla_Dialogue_40
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_3, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq Alola_Melemele_SamsonOakVilla_Dialogue_55
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_8, MSGBOX_AUTOCLOSE
	release
	end

Alola_Melemele_SamsonOakVilla_Dialogue_24:
	goto_if_set FLAG_DEFEATED_ULAULA_TOTEM, Alola_Melemele_SamsonOakVilla_Dialogue_28
	goto Alola_Melemele_SamsonOakVilla_Dialogue_23

Alola_Melemele_SamsonOakVilla_Dialogue_25:
	goto_if_set FLAG_DEFEATED_AKALA_TOTEM, Alola_Melemele_SamsonOakVilla_Dialogue_24
	goto Alola_Melemele_SamsonOakVilla_Dialogue_23

Alola_Melemele_SamsonOakVilla_Dialogue_28:
	goto_if_set FLAG_DEFEATED_PONI_TOTEM, Alola_Melemele_SamsonOakVilla_Dialogue_22
	goto Alola_Melemele_SamsonOakVilla_Dialogue_23

Alola_Melemele_SamsonOakVilla_Dialogue_31:
	getcaughtmon SPECIES_MEOWTH_ALOLA
	compare VAR_RESULT, 1
	goto_if_eq Alola_Melemele_SamsonOakVilla_Dialogue_44
Alola_Melemele_SamsonOakVilla_Dialogue_43:
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_23, MSGBOX_AUTOCLOSE
	release
	end

Alola_Melemele_SamsonOakVilla_Dialogue_32:
	getcaughtmon SPECIES_MAROWAK_ALOLA
	compare VAR_RESULT, 1
	goto_if_eq Alola_Melemele_SamsonOakVilla_Dialogue_47
Alola_Melemele_SamsonOakVilla_Dialogue_46:
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_27, MSGBOX_AUTOCLOSE
	release
	end

Alola_Melemele_SamsonOakVilla_Dialogue_33:
	getcaughtmon SPECIES_VULPIX_ALOLA
	compare VAR_RESULT, 1
	goto_if_eq Alola_Melemele_SamsonOakVilla_Dialogue_50
Alola_Melemele_SamsonOakVilla_Dialogue_49:
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_30, MSGBOX_AUTOCLOSE
	release
	end

Alola_Melemele_SamsonOakVilla_Dialogue_34:
	getcaughtmon SPECIES_RAICHU_ALOLA
	compare VAR_RESULT, 1
	goto_if_eq Alola_Melemele_SamsonOakVilla_Dialogue_68
	goto Alola_Melemele_SamsonOakVilla_Dialogue_46
	end

Alola_Melemele_SamsonOakVilla_Dialogue_52:
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_33, MSGBOX_AUTOCLOSE
	release
	end

Alola_Melemele_SamsonOakVilla_Dialogue_40:
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_2, MSGBOX_AUTOCLOSE
	release
	end

Alola_Melemele_SamsonOakVilla_Dialogue_44:
	getcaughtmon SPECIES_PERSIAN_ALOLA
	compare VAR_RESULT, 1
	goto_if_eq Alola_Melemele_SamsonOakVilla_Dialogue_58
	goto Alola_Melemele_SamsonOakVilla_Dialogue_43

Alola_Melemele_SamsonOakVilla_Dialogue_47:
	getcaughtmon SPECIES_DIGLETT_ALOLA
	compare VAR_RESULT, 1
	goto_if_eq Alola_Melemele_SamsonOakVilla_Dialogue_60
	goto Alola_Melemele_SamsonOakVilla_Dialogue_46

Alola_Melemele_SamsonOakVilla_Dialogue_50:
	getcaughtmon SPECIES_NINETALES_ALOLA
	compare VAR_RESULT, 1
	goto_if_eq Alola_Melemele_SamsonOakVilla_Dialogue_62
	goto Alola_Melemele_SamsonOakVilla_Dialogue_49

Alola_Melemele_SamsonOakVilla_Dialogue_53:
	getcaughtmon SPECIES_GEODUDE_ALOLA
	compare VAR_RESULT, 1
	goto_if_eq Alola_Melemele_SamsonOakVilla_Dialogue_64
	goto Alola_Melemele_SamsonOakVilla_Dialogue_52

Alola_Melemele_SamsonOakVilla_Dialogue_55:
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_4
	trainerbattle_no_intro TRAINER_SAMSON_OAK_HNS, Alola_Melemele_SamsonOakVilla_Dialogue_Text_5
	special GivePartyMonMarineRibbon
	special HealPlayerParty
	setflag FLAG_DEFEATED_SAMSON_OAK
	setflag FLAG_FLYOVER_TAPU_KOKO
	setflag FLAG_FLYOVER_TAPU_LELE
	setflag FLAG_FLYOVER_TAPU_BULU
	setflag FLAG_FLYOVER_TAPU_FINI
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_6, MSGBOX_AUTOCLOSE
	playse SE_PIN
	applymovement SamsonOakVilla, Alola_Melemele_SamsonOakVilla_Dialogue_Movement_0
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_7, MSGBOX_AUTOCLOSE
	setvar VAR_ALOLA_STATE, 3
	release
	end

Alola_Melemele_SamsonOakVilla_Dialogue_58:
	getcaughtmon SPECIES_RATTATA_ALOLA
	compare VAR_RESULT, 1
	goto_if_eq Alola_Melemele_SamsonOakVilla_Dialogue_66
	goto Alola_Melemele_SamsonOakVilla_Dialogue_43

Alola_Melemele_SamsonOakVilla_Dialogue_60:
	getcaughtmon SPECIES_DUGTRIO_ALOLA
	compare VAR_RESULT, 1
	goto_if_eq Alola_Melemele_SamsonOakVilla_Dialogue_34
	goto Alola_Melemele_SamsonOakVilla_Dialogue_46

Alola_Melemele_SamsonOakVilla_Dialogue_62:
	getcaughtmon SPECIES_SANDSHREW_ALOLA
	compare VAR_RESULT, 1
	goto_if_eq Alola_Melemele_SamsonOakVilla_Dialogue_70
	goto Alola_Melemele_SamsonOakVilla_Dialogue_49

Alola_Melemele_SamsonOakVilla_Dialogue_64:
	getcaughtmon SPECIES_GRAVELER_ALOLA
	compare VAR_RESULT, 1
	goto_if_eq Alola_Melemele_SamsonOakVilla_Dialogue_72
	goto Alola_Melemele_SamsonOakVilla_Dialogue_52

Alola_Melemele_SamsonOakVilla_Dialogue_66:
	getcaughtmon SPECIES_RATICATE_ALOLA
	compare VAR_RESULT, 1
	goto_if_eq Alola_Melemele_SamsonOakVilla_Dialogue_74
	goto Alola_Melemele_SamsonOakVilla_Dialogue_43

Alola_Melemele_SamsonOakVilla_Dialogue_68:
	goto_if_unset FLAG_CAUGHT_ALL_AKALA, Alola_Melemele_SamsonOakVilla_Dialogue_76
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_26, MSGBOX_AUTOCLOSE
	release
	end

Alola_Melemele_SamsonOakVilla_Dialogue_70:
	getcaughtmon SPECIES_SANDSLASH_ALOLA
	compare VAR_RESULT, 1
	goto_if_eq Alola_Melemele_SamsonOakVilla_Dialogue_79
	goto Alola_Melemele_SamsonOakVilla_Dialogue_49

Alola_Melemele_SamsonOakVilla_Dialogue_72:
	getcaughtmon SPECIES_GOLEM_ALOLA
	compare VAR_RESULT, 1
	goto_if_eq Alola_Melemele_SamsonOakVilla_Dialogue_81
	goto Alola_Melemele_SamsonOakVilla_Dialogue_52

Alola_Melemele_SamsonOakVilla_Dialogue_74:
	goto_if_unset FLAG_CAUGHT_ALL_MELEMELE, Alola_Melemele_SamsonOakVilla_Dialogue_83
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_22, MSGBOX_AUTOCLOSE
	release
	end

Alola_Melemele_SamsonOakVilla_Dialogue_76:
	goto_if_set FLAG_CAUGHT_ALL_MELEMELE, Alola_Melemele_SamsonOakVilla_Dialogue_86
	goto_if_set FLAG_CAUGHT_ALL_ULAULA, Alola_Melemele_SamsonOakVilla_Dialogue_86
	goto_if_set FLAG_CAUGHT_ALL_PONI, Alola_Melemele_SamsonOakVilla_Dialogue_86
	setflag FLAG_CAUGHT_ALL_AKALA
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_16, MSGBOX_AUTOCLOSE
	playse SE_PIN
	applymovement SamsonOakVilla, Alola_Melemele_SamsonOakVilla_Dialogue_Movement_0
	waitmovement 0
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_17
	playfanfare MUS_HG_OBTAIN_EGG
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_24
	waitfanfare
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_21
	release
	end

Alola_Melemele_SamsonOakVilla_Dialogue_79:
	getcaughtmon SPECIES_GRIMER_ALOLA
	compare VAR_RESULT, 1
	goto_if_eq Alola_Melemele_SamsonOakVilla_Dialogue_93
	goto Alola_Melemele_SamsonOakVilla_Dialogue_49

Alola_Melemele_SamsonOakVilla_Dialogue_81:
	getcaughtmon SPECIES_EXEGGUTOR_ALOLA
	compare VAR_RESULT, 1
	goto_if_eq Alola_Melemele_SamsonOakVilla_Dialogue_95
	goto Alola_Melemele_SamsonOakVilla_Dialogue_52

Alola_Melemele_SamsonOakVilla_Dialogue_83:
	goto_if_set FLAG_CAUGHT_ALL_AKALA, Alola_Melemele_SamsonOakVilla_Dialogue_97
	goto_if_set FLAG_CAUGHT_ALL_ULAULA, Alola_Melemele_SamsonOakVilla_Dialogue_97
	goto_if_set FLAG_CAUGHT_ALL_PONI, Alola_Melemele_SamsonOakVilla_Dialogue_97
	setflag FLAG_CAUGHT_ALL_MELEMELE
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_16, MSGBOX_AUTOCLOSE
	playse SE_PIN
	applymovement SamsonOakVilla, Alola_Melemele_SamsonOakVilla_Dialogue_Movement_0
	waitmovement 0
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_17
	playfanfare MUS_HG_OBTAIN_EGG
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_18
	waitfanfare
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_21, MSGBOX_AUTOCLOSE
	release
	end

Alola_Melemele_SamsonOakVilla_Dialogue_86:
	setflag FLAG_CAUGHT_ALL_AKALA
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_16, MSGBOX_AUTOCLOSE
	playse SE_PIN
	applymovement SamsonOakVilla, Alola_Melemele_SamsonOakVilla_Dialogue_Movement_0
	waitmovement 0
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_17
	playfanfare MUS_HG_OBTAIN_EGG
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_24
	waitfanfare
	goto_if_set FLAG_CAUGHT_ALL_AKALA, Alola_Melemele_SamsonOakVilla_Dialogue_107
Alola_Melemele_SamsonOakVilla_Dialogue_105:
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_21
	release
	end

Alola_Melemele_SamsonOakVilla_Dialogue_93:
	getcaughtmon SPECIES_MUK_ALOLA
	compare VAR_RESULT, 1
	goto_if_eq Alola_Melemele_SamsonOakVilla_Dialogue_113
	goto Alola_Melemele_SamsonOakVilla_Dialogue_49

Alola_Melemele_SamsonOakVilla_Dialogue_95:
	goto_if_unset FLAG_CAUGHT_ALL_PONI, Alola_Melemele_SamsonOakVilla_Dialogue_115
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_32, MSGBOX_AUTOCLOSE
	release
	end

Alola_Melemele_SamsonOakVilla_Dialogue_97:
	setflag FLAG_CAUGHT_ALL_MELEMELE
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_16, MSGBOX_AUTOCLOSE
	playse SE_PIN
	applymovement SamsonOakVilla, Alola_Melemele_SamsonOakVilla_Dialogue_Movement_0
	waitmovement 0
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_17
	playfanfare MUS_HG_OBTAIN_EGG
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_18
	waitfanfare
	goto_if_set FLAG_CAUGHT_ALL_AKALA, Alola_Melemele_SamsonOakVilla_Dialogue_121
Alola_Melemele_SamsonOakVilla_Dialogue_119:
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_21, MSGBOX_AUTOCLOSE
	release
	end

Alola_Melemele_SamsonOakVilla_Dialogue_104:
	playfanfare MUS_HG_BUG_CONTEST_1ST_PLACE
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_19, MSGBOX_AUTOCLOSE
	waitfanfare
	playse SE_PIN
	applymovement SamsonOakVilla, Alola_Melemele_SamsonOakVilla_Dialogue_Movement_0
	waitmovement 0
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_25
	release
	end

Alola_Melemele_SamsonOakVilla_Dialogue_106:
	goto_if_set FLAG_CAUGHT_ALL_PONI, Alola_Melemele_SamsonOakVilla_Dialogue_110
	goto Alola_Melemele_SamsonOakVilla_Dialogue_105

Alola_Melemele_SamsonOakVilla_Dialogue_107:
	goto_if_set FLAG_CAUGHT_ALL_ULAULA, Alola_Melemele_SamsonOakVilla_Dialogue_106
	goto Alola_Melemele_SamsonOakVilla_Dialogue_105

Alola_Melemele_SamsonOakVilla_Dialogue_110:
	goto_if_set FLAG_CAUGHT_ALL_MELEMELE, Alola_Melemele_SamsonOakVilla_Dialogue_104
	goto Alola_Melemele_SamsonOakVilla_Dialogue_105

Alola_Melemele_SamsonOakVilla_Dialogue_113:
	goto_if_unset FLAG_CAUGHT_ALL_ULAULA, Alola_Melemele_SamsonOakVilla_Dialogue_127
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_29, MSGBOX_AUTOCLOSE
	release
	end

Alola_Melemele_SamsonOakVilla_Dialogue_115:
	goto_if_set FLAG_CAUGHT_ALL_MELEMELE, Alola_Melemele_SamsonOakVilla_Dialogue_130
	goto_if_set FLAG_CAUGHT_ALL_AKALA, Alola_Melemele_SamsonOakVilla_Dialogue_130
	goto_if_set FLAG_CAUGHT_ALL_ULAULA, Alola_Melemele_SamsonOakVilla_Dialogue_130
	setflag FLAG_CAUGHT_ALL_PONI
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_16, MSGBOX_AUTOCLOSE
	playse SE_PIN
	applymovement SamsonOakVilla, Alola_Melemele_SamsonOakVilla_Dialogue_Movement_0
	waitmovement 0
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_17
	playfanfare MUS_HG_OBTAIN_EGG
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_31
	waitfanfare
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_21, MSGBOX_AUTOCLOSE
	release
	end

Alola_Melemele_SamsonOakVilla_Dialogue_118:
	playfanfare MUS_HG_BUG_CONTEST_1ST_PLACE
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_19, MSGBOX_AUTOCLOSE
	waitfanfare
	playse SE_PIN
	applymovement SamsonOakVilla, Alola_Melemele_SamsonOakVilla_Dialogue_Movement_0
	waitmovement 0
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_20, MSGBOX_AUTOCLOSE
	release
	end

Alola_Melemele_SamsonOakVilla_Dialogue_120:
	goto_if_set FLAG_CAUGHT_ALL_PONI, Alola_Melemele_SamsonOakVilla_Dialogue_124
	goto Alola_Melemele_SamsonOakVilla_Dialogue_119

Alola_Melemele_SamsonOakVilla_Dialogue_121:
	goto_if_set FLAG_CAUGHT_ALL_ULAULA, Alola_Melemele_SamsonOakVilla_Dialogue_120
	goto Alola_Melemele_SamsonOakVilla_Dialogue_119

Alola_Melemele_SamsonOakVilla_Dialogue_124:
	goto_if_set FLAG_CAUGHT_ALL_MELEMELE, Alola_Melemele_SamsonOakVilla_Dialogue_118
	goto Alola_Melemele_SamsonOakVilla_Dialogue_119

Alola_Melemele_SamsonOakVilla_Dialogue_127:
	goto_if_set FLAG_CAUGHT_ALL_MELEMELE, Alola_Melemele_SamsonOakVilla_Dialogue_137
	goto_if_set FLAG_CAUGHT_ALL_AKALA, Alola_Melemele_SamsonOakVilla_Dialogue_137
	goto_if_set FLAG_CAUGHT_ALL_PONI, Alola_Melemele_SamsonOakVilla_Dialogue_137
	setflag FLAG_CAUGHT_ALL_ULAULA
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_16, MSGBOX_AUTOCLOSE
	playse SE_PIN
	applymovement SamsonOakVilla, Alola_Melemele_SamsonOakVilla_Dialogue_Movement_0
	waitmovement 0
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_17
	playfanfare MUS_HG_OBTAIN_EGG
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_28
	waitfanfare
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_21, MSGBOX_AUTOCLOSE
	release
	end

Alola_Melemele_SamsonOakVilla_Dialogue_130:
	setflag FLAG_CAUGHT_ALL_PONI
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_16, MSGBOX_AUTOCLOSE
	playse SE_PIN
	applymovement SamsonOakVilla, Alola_Melemele_SamsonOakVilla_Dialogue_Movement_0
	waitmovement 0
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_17
	playfanfare MUS_HG_OBTAIN_EGG
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_31
	waitfanfare
	goto_if_set FLAG_CAUGHT_ALL_AKALA, Alola_Melemele_SamsonOakVilla_Dialogue_147
Alola_Melemele_SamsonOakVilla_Dialogue_145:
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_21, MSGBOX_AUTOCLOSE
	release
	end

Alola_Melemele_SamsonOakVilla_Dialogue_137:
	setflag FLAG_CAUGHT_ALL_ULAULA
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_16, MSGBOX_AUTOCLOSE
	playse SE_PIN
	applymovement SamsonOakVilla, Alola_Melemele_SamsonOakVilla_Dialogue_Movement_0
	waitmovement 0
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_17
	playfanfare MUS_HG_OBTAIN_EGG
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_28
	waitfanfare
	goto_if_set FLAG_CAUGHT_ALL_AKALA, Alola_Melemele_SamsonOakVilla_Dialogue_156
Alola_Melemele_SamsonOakVilla_Dialogue_154:
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_21, MSGBOX_AUTOCLOSE
	release
	end

Alola_Melemele_SamsonOakVilla_Dialogue_144:
	playfanfare MUS_HG_BUG_CONTEST_1ST_PLACE
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_19, MSGBOX_AUTOCLOSE
	waitfanfare
	playse SE_PIN
	applymovement SamsonOakVilla, Alola_Melemele_SamsonOakVilla_Dialogue_Movement_0
	waitmovement 0
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_25, MSGBOX_AUTOCLOSE
	release
	end

Alola_Melemele_SamsonOakVilla_Dialogue_146:
	goto_if_set FLAG_CAUGHT_ALL_PONI, Alola_Melemele_SamsonOakVilla_Dialogue_150
	goto Alola_Melemele_SamsonOakVilla_Dialogue_145

Alola_Melemele_SamsonOakVilla_Dialogue_147:
	goto_if_set FLAG_CAUGHT_ALL_ULAULA, Alola_Melemele_SamsonOakVilla_Dialogue_146
	goto Alola_Melemele_SamsonOakVilla_Dialogue_145

Alola_Melemele_SamsonOakVilla_Dialogue_150:
	goto_if_set FLAG_CAUGHT_ALL_MELEMELE, Alola_Melemele_SamsonOakVilla_Dialogue_144
	goto Alola_Melemele_SamsonOakVilla_Dialogue_145

Alola_Melemele_SamsonOakVilla_Dialogue_153:
	playfanfare MUS_HG_BUG_CONTEST_1ST_PLACE
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_19, MSGBOX_AUTOCLOSE
	waitfanfare
	playse SE_PIN
	applymovement SamsonOakVilla, Alola_Melemele_SamsonOakVilla_Dialogue_Movement_0
	waitmovement 0
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_25, MSGBOX_AUTOCLOSE
	release
	end

Alola_Melemele_SamsonOakVilla_Dialogue_155:
	goto_if_set FLAG_CAUGHT_ALL_PONI, Alola_Melemele_SamsonOakVilla_Dialogue_159
	goto Alola_Melemele_SamsonOakVilla_Dialogue_154

Alola_Melemele_SamsonOakVilla_Dialogue_156:
	goto_if_set FLAG_CAUGHT_ALL_ULAULA, Alola_Melemele_SamsonOakVilla_Dialogue_155
	goto Alola_Melemele_SamsonOakVilla_Dialogue_154

Alola_Melemele_SamsonOakVilla_Dialogue_159:
	goto_if_set FLAG_CAUGHT_ALL_MELEMELE, Alola_Melemele_SamsonOakVilla_Dialogue_153
	goto Alola_Melemele_SamsonOakVilla_Dialogue_154


Alola_Melemele_SamsonOakVillaIntro_Trigger_Movement_0:
	emote_exclamation_mark
	face_down
	step_end

Alola_Melemele_SamsonOakVillaIntro_Trigger_Movement_1:
	walk_down
	walk_left
	face_down
	step_end

Alola_Melemele_SamsonOakVillaIntro_Trigger_Movement_2:
	walk_in_place_down
	walk_in_place_down
	step_end

Alola_Melemele_SamsonOakVillaIntro_Trigger_Movement_3:
	walk_right
	walk_up
	face_right
	step_end

Alola_Melemele_SamsonOakVilla_Dialogue_Movement_0:
	emote_exclamation_mark
	step_end

Alola_Melemele_SamsonOakVillaIntro_Trigger_Text_0:
	.string "אלולה, {PLAYER}!$"

Alola_Melemele_SamsonOakVillaIntro_Trigger_Text_1:
	.string "אני שמח שהגעת!\n"
	.string "ברוכים הבאים לווילה שלי!\p"
	.string "אני שוהה כאן בזמן שאני חוקר את הדמיון\n"
	.string "בין איי אלולה לאזור אלולה.\p"
	.string "אני מתעניין במיוחד\n"
	.string "בתופעה של ”זנים אזוריים”.$"

Alola_Melemele_SamsonOakVillaIntro_Trigger_Text_2:
	.string "אתה נראה מוכשר למדי.\p"
	.string "אתה מתאים בדיוק לעזור לי\n"
	.string "בסקר של איי אלולה!\p"
	.string "גלה את כל מה שיש לאיים להציע,\n"
	.string "ואם תמצא פוקימונים מוכרים\p"
	.string "שדומים לאלה שבקאנטו…\n"
	.string "חזור ותראה לי את הפוקדקס שלך!\p"
	.string "אני אחכה כאן בסבלנות לשמוע\n"
	.string "על ההתקדמות שלך!$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_0:
	.string "וואו!\n"
	.string "ראית את האלים השומרים!\p"
	.string "עבודה מדהימה, {PLAYER}.\p"
	.string "מצאתי את זה כשהסתובבתי פה ושם.\p"
	.string "אני לא לגמרי בטוח למה זה משמש,\n"
	.string "אבל כדאי שתיקח את זה.$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_1:
	.string "איי אלולה בטח באמת מיוחדים\n"
	.string "אם השומרים עצמם ביקרו בהם!$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_2:
	.string "תודה על העזרה במחקר שלי,\n"
	.string "{PLAYER}!\p"
	.string "בזכותך אנחנו מבינים את איי אלולה\n"
	.string "הרבה יותר טוב!\p"
	.string "אני מקווה שתמשיך לחקור את האיים\n"
	.string "ולגלות את כל הסודות שהם מסתירים!$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_3:
	.string "אלולה, {PLAYER}!\p"
	.string "אז הצלחת להביס את כל\n"
	.string "פוקימוני הטוטם באיים, מה?\p"
	.string "זה הישג לא קטן!\p"
	.string "עבר מספיק זמן…\p"
	.string "נראה לי שהגיע הזמן לקרב בינינו,\n"
	.string "אתה מסכים?$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_4:
	.string "מצוין!\n"
	.string "אני לא אקל עליך!$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_5:
	.string "מדהים, {PLAYER}!$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_6:
	.string "וואו, {PLAYER}!\n"
	.string "אתה באמת מאמן חזק!\p"
	.string "הוכחת שאתה ראוי לשמוע סוד\n"
	.string "ששמרתי לעצמי על האיים האלה…\p"
	.string "אני לא היחיד ששם לב לדמיון המדהים\n"
	.string "בין איי אלולה לאזור אלולה…\p"
	.string "נראה שהטאפו, האלים השומרים,\n"
	.string "מבקרים באיים בעצמם.\p"
	.string "אם תראה אותם עפים מעל האיים,\n"
	.string "לך אל הטוטמים…\p"
	.string "ייתכן שהם מחכים לך שם!$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_7:
	.string "למה אתה מחכה, {PLAYER}?\n"
	.string "קדימה, צא לחקור!$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_8:
	.string "אין בעיה, {PLAYER}!\p"
	.string "קח את הזמן ותתכונן לקרב,\n"
	.string "ותחזור כשתהיה מוכן!$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_9:
	.string "אלולה, {PLAYER}!\p"
	.string "אז מצאת את כל זני אלולה באיים,\n"
	.string "אבל כבר הבסת את כל פוקימוני הטוטם?\p"
	.string "כדאי לחפש עמוד מוזר בכל אי.\n"
	.string "פוקימון הטוטם יהיה שם וישמור עליו!$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_10:
	.string "שלום שוב, {PLAYER}!\p"
	.string "איך מתקדם המחקר שלך\n"
	.string "על איי אלולה?\p"
	.string "תרצה לספר לי על ההתקדמות שלך\n"
	.string "באי מסוים?$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_11:
	.string "האי מלמלה$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_12:
	.string "האי אקאלה$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_13:
	.string "האי אולאולה$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_14:
	.string "האי פוני$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_15:
	.string "לא כרגע.$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_16:
	.string "בוא נציץ בפוקדקס שלך{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_17:
	.string "וואו, {PLAYER}!$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_18:
	.string "מצאת את כל זני אלולה\n"
	.string "שחיים באי מלמלה!$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_19:
	.string "ונראה שמצאת את כל זני אלולה\n"
	.string "גם באיים האחרים!\p"
	.string "זה מדהים, {PLAYER}!\p"
	.string "אתה צריך להיות גאה מאוד בעצמך!$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_20:
	.string "עזרת לי לאשר שכל זני אלולה\n"
	.string "נמצאים באיי אלולה!\p"
	.string "אשמח שתעזור לי בעוד\n"
	.string "דבר אחד…\p"
	.string "תוכל לחקור בשבילי את פוקימוני הטוטם,\n"
	.string "שלפי השמועה שומרים על טוטם בכל אי?\p"
	.string "אבל זהירות! אומרים שפוקימוני הטוטם\n"
	.string "חזקים בהרבה מבני מינם הרגילים…\p"
	.string "אי אפשר לדעת מי עשוי לצפות בך\n"
	.string "כדי לבדוק אם אתה יריב ראוי!$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_21:
	.string "המשך לחקור את האיים האחרים\n"
	.string "ודווח לי על ההתקדמות שלך!$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_22:
	.string "נראה שכבר מצאת את כל\n"
	.string "זני אלולה באי מלמלה!\p"
	.string "עבודה מצוינת!\p"
	.string "המשך לחקור את האיים האחרים\n"
	.string "ודווח לי על ההתקדמות שלך!$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_23:
	.string "בוא נציץ בפוקדקס שלך{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.\p"
	.string "נראה שעוד לא מצאת את כל\n"
	.string "זני אלולה באי מלמלה.\p"
	.string "שמעתי שבאי מלמלה יש {COLOR RED}4 {COLOR DARK_GRAY}זני\n"
	.string "אלולה שמחכים שתמצא אותם…\p"
	.string "{COLOR RED}רטטה{COLOR DARK_GRAY}, {COLOR RED}רטיקייט{COLOR DARK_GRAY}, {COLOR RED}מיאו{COLOR DARK_GRAY}\n"
	.string "ו{COLOR RED}פרסיאן{COLOR DARK_GRAY}.\p"
	.string "המשך לחפש, ותחזור כשתתפוס\n"
	.string "את כולם!$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_24:
	.string "מצאת את כל זני אלולה\n"
	.string "שחיים באי אקאלה!$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_25:
	.string "עכשיו, אחרי שעזרת לי לאשר שכל\n"
	.string "זני אלולה נמצאים באיי אלולה…\p"
	.string "אשמח שתעזור לי בעוד\n"
	.string "דבר אחד…\p"
	.string "תוכל לחקור בשבילי את פוקימוני הטוטם,\n"
	.string "שלפי השמועה שומרים על טוטם בכל אי?\p"
	.string "אבל זהירות! אומרים שפוקימוני הטוטם\n"
	.string "חזקים בהרבה מבני מינם הרגילים…\p"
	.string "אי אפשר לדעת מי עשוי לצפות בך\n"
	.string "כדי לבדוק אם אתה יריב ראוי!$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_26:
	.string "נראה שכבר מצאת את כל\n"
	.string "זני אלולה באי אקאלה!\p"
	.string "עבודה מצוינת!\p"
	.string "המשך לחקור את האיים האחרים\n"
	.string "ודווח לי על ההתקדמות שלך!$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_27:
	.string "בוא נציץ בפוקדקס שלך{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.\p"
	.string "נראה שעוד לא מצאת את כל\n"
	.string "זני אלולה באי אקאלה.\p"
	.string "שמעתי שבאי אקאלה יש {COLOR RED}4 {COLOR DARK_GRAY}זני\n"
	.string "אלולה שמחכים שתמצא אותם…\p"
	.string "{COLOR RED}ראיצ'ו{COLOR DARK_GRAY}, {COLOR RED}מארוואק{COLOR DARK_GRAY}, {COLOR RED}דיגלט{COLOR DARK_GRAY}\n"
	.string "ו{COLOR RED}דאגטריו{COLOR DARK_GRAY}.\p"
	.string "המשך לחפש, ותחזור כשתתפוס\n"
	.string "את כולם!$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_28:
	.string "מצאת את כל זני אלולה\n"
	.string "שחיים באי אולאולה!$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_29:
	.string "נראה שכבר מצאת את כל\n"
	.string "זני אלולה באי אולאולה!\p"
	.string "עבודה מצוינת!\p"
	.string "המשך לחקור את האיים האחרים\n"
	.string "ודווח לי על ההתקדמות שלך!$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_30:
	.string "בוא נציץ בפוקדקס שלך{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.\p"
	.string "נראה שעוד לא מצאת את כל\n"
	.string "זני אלולה באי אולאולה.\p"
	.string "שמעתי שבאי אולאולה יש {COLOR RED}6 {COLOR DARK_GRAY}זני\n"
	.string "אלולה שמחכים שתמצא אותם…\p"
	.string "{COLOR RED}וולפיקס{COLOR DARK_GRAY}, {COLOR RED}ניינטיילס{COLOR DARK_GRAY}, {COLOR RED}סנדשרו{COLOR DARK_GRAY},\n"
	.string "{COLOR RED}סנדסלאש{COLOR DARK_GRAY}, {COLOR RED}גריימר{COLOR DARK_GRAY} ו{COLOR RED}מאק{COLOR DARK_GRAY}.\p"
	.string "המשך לחפש, ותחזור כשתתפוס\n"
	.string "את כולם!$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_31:
	.string "מצאת את כל זני אלולה\n"
	.string "שחיים באי פוני!$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_32:
	.string "נראה שכבר מצאת את כל\n"
	.string "זני אלולה באי פוני!\p"
	.string "עבודה מצוינת!\p"
	.string "המשך לחקור את האיים האחרים\n"
	.string "ודווח לי על ההתקדמות שלך!$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_33:
	.string "בוא נציץ בפוקדקס שלך{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.\p"
	.string "נראה שעוד לא מצאת את כל\n"
	.string "זני אלולה באי פוני.\p"
	.string "שמעתי שבאי פוני יש {COLOR RED}4 {COLOR DARK_GRAY}זני\n"
	.string "אלולה שמחכים שתמצא אותם…\p"
	.string "{COLOR RED}ג'יאודוד{COLOR DARK_GRAY}, {COLOR RED}גרבלר{COLOR DARK_GRAY}, {COLOR RED}גולם{COLOR DARK_GRAY}\n"
	.string "ו{COLOR RED}אקזגקיוטר{COLOR DARK_GRAY}.\p"
	.string "המשך לחפש, ותחזור כשתתפוס\n"
	.string "את כולם!$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_34:
	.string "אין בעיה, {PLAYER}!\p"
	.string "חזור כשתרצה לשתף אותי\n"
	.string "בממצאים שלך על איי אלולה!$"
