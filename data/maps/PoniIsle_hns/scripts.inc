PoniIsle_hns_MapScripts::
	.byte 0


Alola_Poni_BattleExeggutor::
	lock
	faceplayer
	setflag FLAG_BATTLED_EXEGGUTOR
	playmoncry SPECIES_EXEGGUTOR_ALOLA, 0
	msgbox Alola_Poni_BattleExeggutor_Text_0, MSGBOX_AUTOCLOSE
	waitmoncry
	setwildbattle SPECIES_EXEGGUTOR_ALOLA, 45
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	compare VAR_RESULT, B_OUTCOME_CAUGHT
	goto_if_eq Alola_Poni_BattleExeggutor_2
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq Alola_Poni_BattleExeggutor_3
	release
	end

	release
	end

Alola_Poni_BattleExeggutor_2:
	setflag FLAG_HIDE_EXEGGUTOR_ALOLA
	removeobject Alola_Poni_Exeggutor
	release
	end

Alola_Poni_BattleExeggutor_3:
	setflag FLAG_HIDE_EXEGGUTOR_ALOLA
	removeobject Alola_Poni_Exeggutor
	release
	end


Alola_Poni_Island_Sign::
	lock
	msgbox Alola_Poni_Island_Sign_Text_0
	release
	end


Alola_Poni_TotemBattle_Trigger::
	goto_if_unset FLAG_TRIGGERED_PONI_TOTEM, Alola_Poni_TotemBattle_Trigger_1
	end

Alola_Poni_TotemBattle_Trigger_1:
	goto_if_set FLAG_CAUGHT_ALL_AKALA, Alola_Poni_TotemBattle_Trigger_7
Alola_Poni_TotemBattle_Trigger_5:
	end

Alola_Poni_TotemBattle_Trigger_4:
	lock
	delay 30
	setvar VAR_0x8004, 2
	setvar VAR_0x8005, 6
	setvar VAR_0x8006, 4
	setvar VAR_0x8007, 4
	special ShakeCamera
	waitstate
	fadescreenswapbuffers FADE_TO_BLACK
	delay 30
	clearflag FLAG_HIDE_PONI_TOTEM
	playmoncry SPECIES_ELECTIVIRE, 0
	addobject Poni_Totem
	waitmoncry
	delay 30
	fadescreenswapbuffers FADE_FROM_BLACK
	delay 30
	playmoncry SPECIES_ELECTIVIRE, 0
	applymovement Poni_Totem, Alola_Poni_TotemBattle_Trigger_Movement_0
	waitmovement 0
	waitmoncry
	setflag FLAG_TRIGGERED_PONI_TOTEM
	release
	end

Alola_Poni_TotemBattle_Trigger_6:
	goto_if_set FLAG_CAUGHT_ALL_PONI, Alola_Poni_TotemBattle_Trigger_10
	goto Alola_Poni_TotemBattle_Trigger_5

Alola_Poni_TotemBattle_Trigger_7:
	goto_if_set FLAG_CAUGHT_ALL_ULAULA, Alola_Poni_TotemBattle_Trigger_6
	goto Alola_Poni_TotemBattle_Trigger_5

Alola_Poni_TotemBattle_Trigger_10:
	goto_if_set FLAG_CAUGHT_ALL_MELEMELE, Alola_Poni_TotemBattle_Trigger_4
	goto Alola_Poni_TotemBattle_Trigger_5


Alola_Poni_TotemBattle::
	lock
	faceplayer
	playmoncry SPECIES_ELECTIVIRE, 0
	msgbox Alola_Poni_TotemBattle_Text_0, MSGBOX_AUTOCLOSE
	waitmoncry
	setwildbattle SPECIES_ELECTABUZZ, 60, ITEM_NONE, SPECIES_ELECTIVIRE, 60, ITEM_OCCA_BERRY
	settotemboost B_POSITION_OPPONENT_RIGHT, 1, 1, 1, 1, 1, 1
	setflag FLAG_NO_WILD_CATCHING
	setflag FLAG_NO_WILD_RUNNING
	setflag FLAG_SMART_WILD_AI
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq Alola_Poni_TotemBattle_2
	compare VAR_RESULT, B_OUTCOME_LOST
	goto_if_eq Alola_Poni_TotemBattle_4
	return

Alola_Poni_TotemBattle_2:
	setflag FLAG_HIDE_PONI_TOTEM
	setflag FLAG_DEFEATED_PONI_TOTEM
	removeobject Poni_Totem
	msgbox Alola_Poni_TotemBattle_Text_1, MSGBOX_AUTOCLOSE
	clearflag FLAG_NO_WILD_CATCHING
	clearflag FLAG_NO_WILD_RUNNING
	clearflag FLAG_SMART_WILD_AI
	release
	end

Alola_Poni_TotemBattle_4:
	clearflag FLAG_NO_WILD_CATCHING
	clearflag FLAG_NO_WILD_RUNNING
	clearflag FLAG_SMART_WILD_AI
	release
	end


Alola_Poni_Totem_sign::
	lock
	goto_if_set FLAG_BATTLED_TAPU_FINI, Alola_Poni_Totem_sign_5
Alola_Poni_Totem_sign_3:
	msgbox Alola_Poni_Totem_sign_Text_5, MSGBOX_AUTOCLOSE
	release
	end

Alola_Poni_Totem_sign_2:
	msgbox Alola_Poni_Totem_sign_Text_0
	dynmultichoice 20, 4, FALSE, 4, 0, DYN_MULTICHOICE_CB_NONE, Alola_Poni_Totem_sign_Text_1, Alola_Poni_Totem_sign_Text_2, Alola_Poni_Totem_sign_Text_3, Alola_Poni_Island_Sign_Text_0, Alola_Poni_Totem_sign_Text_4
	compare VAR_RESULT, 0
	goto_if_eq Alola_Poni_Totem_sign_12
	compare VAR_RESULT, 1
	goto_if_eq Alola_Poni_Totem_sign_15
	compare VAR_RESULT, 2
	goto_if_eq Alola_Poni_Totem_sign_18
	compare VAR_RESULT, 3
	goto_if_eq Alola_Poni_Totem_sign_20
	release
	end

Alola_Poni_Totem_sign_4:
	goto_if_set FLAG_BATTLED_TAPU_BULU, Alola_Poni_Totem_sign_8
	goto Alola_Poni_Totem_sign_3

Alola_Poni_Totem_sign_5:
	goto_if_set FLAG_BATTLED_TAPU_KOKO, Alola_Poni_Totem_sign_4
	goto Alola_Poni_Totem_sign_3

Alola_Poni_Totem_sign_8:
	goto_if_set FLAG_BATTLED_TAPU_LELE, Alola_Poni_Totem_sign_2
	goto Alola_Poni_Totem_sign_3

Alola_Poni_Totem_sign_12:
	warp MAP_MELEMELE_ISLE_HNS, 34, 26
	waitstate
	end

Alola_Poni_Totem_sign_15:
	warp MAP_AKALA_ISLE_HNS, 9, 10
	waitstate
	end

Alola_Poni_Totem_sign_18:
	warp MAP_ULA_ULA_FOREST_HNS, 16, 5
	waitstate
	end

Alola_Poni_Totem_sign_20:
	warp MAP_PONI_ISLE_HNS, 13, 8
	waitstate
	end


Alola_Poni_TapuFini_Flyover::
	goto_if_set FLAG_FLYOVER_TAPU_FINI, Alola_Poni_TapuFini_Flyover_2
	release
	end

Alola_Poni_TapuFini_Flyover_2:
	addobject Poni_Flyover_Tapu
	playse SE_M_FLY
	applymovement Poni_Flyover_Tapu, Alola_Poni_TapuFini_Flyover_Movement_0
	waitmovement 0
	removeobject Poni_Flyover_Tapu
	clearflag FLAG_FLYOVER_TAPU_FINI
	clearflag FLAG_HIDE_TAPU_FINI
	release
	end


Alola_Poni_BattleVsTapuFini::
	lock
	faceplayer
	playmoncry SPECIES_TAPU_FINI, CRY_MODE_ENCOUNTER
	msgbox Alola_Poni_BattleVsTapuFini_Text_0
	waitmoncry
	seteventmon SPECIES_TAPU_FINI, 60
	special BattleSetup_StartLegendaryBattle
	waitstate
	specialvar VAR_RESULT, GetBattleOutcome
	compare VAR_RESULT, B_OUTCOME_CAUGHT
	goto_if_eq Alola_Poni_BattleVsTapuFini_2
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq Alola_Poni_BattleVsTapuFini_3
	release
	end

	release
	end

Alola_Poni_BattleVsTapuFini_2:
	setflag FLAG_HIDE_TAPU_FINI
	setflag FLAG_BATTLED_TAPU_FINI
	removeobject Poni_Tapu
	release
	end

Alola_Poni_BattleVsTapuFini_3:
	setflag FLAG_HIDE_TAPU_FINI
	setflag FLAG_BATTLED_TAPU_FINI
	removeobject Poni_Tapu
	release
	end


Alola_Poni_TrainerBattleSwimmer1::
	trainerbattle_single TRAINER_PONI_SWIMMER_1_HNS, Alola_Poni_TrainerBattleSwimmer1_Text_0, Alola_Poni_TrainerBattleSwimmer1_Text_1
	msgbox Alola_Poni_TrainerBattleSwimmer1_Text_2, MSGBOX_AUTOCLOSE
	release
	end


Alola_Poni_TrainerBattleSwimmer2::
	trainerbattle_single TRAINER_PONI_SWIMMER_2_HNS, Alola_Poni_TrainerBattleSwimmer2_Text_0, Alola_Poni_TrainerBattleSwimmer2_Text_1
	msgbox Alola_Poni_TrainerBattleSwimmer2_Text_2, MSGBOX_AUTOCLOSE
	release
	end


Alola_Poni_NPC_girl::
	lock
	faceplayer
	msgbox Alola_Poni_NPC_girl_Text_0, MSGBOX_AUTOCLOSE
	release
	end


Alola_Poni_Bench_Heal::
	lock
	faceplayer
	msgbox Alola_Poni_Bench_Heal_Text_0, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq Alola_Poni_Bench_Heal_2
Alola_Poni_Bench_Heal_1:
	release
	end

Alola_Poni_Bench_Heal_2:
	fadescreenswapbuffers FADE_TO_BLACK
	special HealPlayerParty
	closemessage
	playfanfare MUS_HEAL
	waitfanfare
	applymovement LOCALID_PLAYER, Alola_Poni_Bench_Heal_Movement_0
	waitmovement 0
	fadescreenswapbuffers FADE_FROM_BLACK
	goto Alola_Poni_Bench_Heal_1


Alola_Poni_FindItem1::
	finditem ITEM_ICE_STONE, 1
	end


Alola_Poni_TotemBattle_Trigger_Movement_0:
	walk_in_place_down
	walk_in_place_down
	step_end

Alola_Poni_TapuFini_Flyover_Movement_0:
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	step_end

Alola_Poni_Bench_Heal_Movement_0:
	face_down
	step_end

Alola_Poni_BattleExeggutor_Text_0:
	.string "Gaah-aah!$"

Alola_Poni_Island_Sign_Text_0:
	.string "Poni Isle$"

Alola_Poni_TotemBattle_Text_0:
	.string "Buzz!!$"

Alola_Poni_TotemBattle_Text_1:
	.string "Totem Tropius was defeated!\n"
	.string "It scampered off somewhere…$"

Alola_Poni_Totem_sign_Text_0:
	.string "The totem is emanating a strong\n"
	.string "energy…\p"
	.string "Touch the totem to teleport to another\n"
	.string "Isle?$"

Alola_Poni_Totem_sign_Text_1:
	.string "Melemele Isle$"

Alola_Poni_Totem_sign_Text_2:
	.string "Akala Isle$"

Alola_Poni_Totem_sign_Text_3:
	.string "Ula'ula Isle$"

Alola_Poni_Totem_sign_Text_4:
	.string "Cancel$"

Alola_Poni_Totem_sign_Text_5:
	.string "A strange totem stands here,\n"
	.string "power is emanating from it…$"

Alola_Poni_BattleVsTapuFini_Text_0:
	.string "Fiiin!$"

Alola_Poni_TrainerBattleSwimmer1_Text_0:
	.string "Warmer water, no problem!$"

Alola_Poni_TrainerBattleSwimmer1_Text_1:
	.string "Gah, I forgot my sunscreen…$"

Alola_Poni_TrainerBattleSwimmer1_Text_2:
	.string "I've swam into so many cool Pokémon!\n"
	.string "It must be something in the water.$"

Alola_Poni_TrainerBattleSwimmer2_Text_0:
	.string "Hey, don't block my current!$"

Alola_Poni_TrainerBattleSwimmer2_Text_1:
	.string "Ugh, fine,\njust let me swim…$"

Alola_Poni_TrainerBattleSwimmer2_Text_2:
	.string "The current is great for tubing.\n"
	.string "I don't think I'll tube anywhere else!$"

Alola_Poni_NPC_girl_Text_0:
	.string "Poni Isle is my favorite.\n"
	.string "The wilderness just speaks for itself!$"

Alola_Poni_Bench_Heal_Text_0:
	.string "Would you like to take a rest on this\n"
	.string "bench?$"
