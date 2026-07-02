AkalaIsle_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, AkalaIsle_hns_MapScripts_MAP_SCRIPT_ON_TRANSITION
	.byte 0

AkalaIsle_hns_MapScripts_MAP_SCRIPT_ON_TRANSITION:
	gettimeofday
	compare VAR_0x8000, TIME_MORNING
	goto_if_eq AkalaIsle_hns_MapScripts_MAP_SCRIPT_ON_TRANSITION_1
	compare VAR_0x8000, TIME_DAY
	goto_if_eq AkalaIsle_hns_MapScripts_MAP_SCRIPT_ON_TRANSITION_1
	setvar VAR_OBJ_GFX_ID_1, OBJ_EVENT_GFX_SPECIES ( PROBOPASS )
	clearflag FLAG_AKALA_TOTEM_DAY
	return

AkalaIsle_hns_MapScripts_MAP_SCRIPT_ON_TRANSITION_1:
	setvar VAR_OBJ_GFX_ID_1, OBJ_EVENT_GFX_SPECIES ( MAGMORTAR )
	setflag FLAG_AKALA_TOTEM_DAY
	return


Alola_Akala_Island_FindItem1::
	finditem ITEM_PROTEIN, 1
	end


Alola_Akala_Island_FindItem2::
	finditem ITEM_IRON, 1
	end


Alola_Akala_Island_Finditem3::
	finditem ITEM_ZINC, 1
	end


Alola_Akala_Sign::
	lock
	msgbox Alola_Akala_Sign_Text_0
	release
	end


Alola_Akala_House_Sign::
	lock
	msgbox Alola_Akala_House_Sign_Text_0
	release
	end


Alola_Akala_Natu::
	lock
	faceplayer
	playmoncry SPECIES_NATU, 0
	msgbox Alola_Akala_Natu_Text_0, MSGBOX_AUTOCLOSE
	waitmoncry
	release
	end


Alola_Akala_OldManOnBench::
	lock
	faceplayer
	msgbox Alola_Akala_OldManOnBench_Text_0, MSGBOX_AUTOCLOSE
	release
	end


Alola_Akala_TotemBattle_Trigger::
	goto_if_unset FLAG_TRIGGERED_AKALA_TOTEM, Alola_Akala_TotemBattle_Trigger_1
	end

Alola_Akala_TotemBattle_Trigger_1:
	goto_if_set FLAG_CAUGHT_ALL_AKALA, Alola_Akala_TotemBattle_Trigger_7
Alola_Akala_TotemBattle_Trigger_5:
	end

Alola_Akala_TotemBattle_Trigger_4:
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
	clearflag FLAG_HIDE_AKALA_TOTEM
	gettimeofday
	compare VAR_0x8000, TIME_MORNING
	goto_if_eq Alola_Akala_TotemBattle_Trigger_14
	compare VAR_0x8000, TIME_DAY
	goto_if_eq Alola_Akala_TotemBattle_Trigger_14
	playmoncry SPECIES_PROBOPASS, 0
	setvar VAR_OBJ_GFX_ID_1, OBJ_EVENT_GFX_SPECIES ( PROBOPASS )
	clearflag FLAG_AKALA_TOTEM_DAY
	addobject Akala_Totem
	waitmoncry
Alola_Akala_TotemBattle_Trigger_13:
	special DrawWholeMapView
	delay 30
	fadescreenswapbuffers FADE_FROM_BLACK
	delay 30
	gettimeofday
	compare VAR_0x8000, TIME_MORNING
	goto_if_eq Alola_Akala_TotemBattle_Trigger_20
	compare VAR_0x8000, TIME_DAY
	goto_if_eq Alola_Akala_TotemBattle_Trigger_20
	playmoncry SPECIES_PROBOPASS, 0
	applymovement Akala_Totem, Alola_Akala_TotemBattle_Trigger_Movement_0
	waitmovement 0
	waitmoncry
Alola_Akala_TotemBattle_Trigger_19:
	setflag FLAG_TRIGGERED_AKALA_TOTEM
	release
	end

Alola_Akala_TotemBattle_Trigger_6:
	goto_if_set FLAG_CAUGHT_ALL_PONI, Alola_Akala_TotemBattle_Trigger_10
	goto Alola_Akala_TotemBattle_Trigger_5

Alola_Akala_TotemBattle_Trigger_7:
	goto_if_set FLAG_CAUGHT_ALL_ULAULA, Alola_Akala_TotemBattle_Trigger_6
	goto Alola_Akala_TotemBattle_Trigger_5

Alola_Akala_TotemBattle_Trigger_10:
	goto_if_set FLAG_CAUGHT_ALL_MELEMELE, Alola_Akala_TotemBattle_Trigger_4
	goto Alola_Akala_TotemBattle_Trigger_5

Alola_Akala_TotemBattle_Trigger_14:
	playmoncry SPECIES_MAGMORTAR, 0
	setvar VAR_OBJ_GFX_ID_1, OBJ_EVENT_GFX_SPECIES ( MAGMORTAR )
	setflag FLAG_AKALA_TOTEM_DAY
	addobject Akala_Totem
	waitmoncry
	goto Alola_Akala_TotemBattle_Trigger_13

Alola_Akala_TotemBattle_Trigger_20:
	playmoncry SPECIES_MAGMORTAR, 0
	applymovement Akala_Totem, Alola_Akala_TotemBattle_Trigger_Movement_0
	waitmovement 0
	waitmoncry
	goto Alola_Akala_TotemBattle_Trigger_19


Alola_Akala_TotemBattle::
	lock
	faceplayer
	goto_if_set FLAG_AKALA_TOTEM_DAY, Alola_Akala_TotemBattle_1
	playmoncry SPECIES_PROBOPASS, 0
	msgbox Alola_Akala_TotemBattle_Text_2, MSGBOX_AUTOCLOSE
	waitmoncry
	setwildbattle SPECIES_NOSEPASS, 60, ITEM_NONE, SPECIES_PROBOPASS, 60, ITEM_PETAYA_BERRY
	settotemboost B_POSITION_OPPONENT_RIGHT, 1, 1, 1, 1, 1, 1
	setflag FLAG_NO_WILD_CATCHING
	setflag FLAG_NO_WILD_RUNNING
	setflag FLAG_SMART_WILD_AI
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq Alola_Akala_TotemBattle_7
	compare VAR_RESULT, B_OUTCOME_LOST
	goto_if_eq Alola_Akala_TotemBattle_9
	return

Alola_Akala_TotemBattle_1:
	playmoncry SPECIES_MAGMORTAR, 0
	msgbox Alola_Akala_TotemBattle_Text_0, MSGBOX_AUTOCLOSE
	waitmoncry
	setwildbattle SPECIES_MAGMAR, 60, ITEM_NONE, SPECIES_MAGMORTAR, 60, ITEM_SITRUS_BERRY
	settotemboost B_POSITION_OPPONENT_RIGHT, 1, 1, 1, 1, 1, 1
	setflag FLAG_NO_WILD_CATCHING
	setflag FLAG_NO_WILD_RUNNING
	setflag FLAG_SMART_WILD_AI
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq Alola_Akala_TotemBattle_4
	return

Alola_Akala_TotemBattle_4:
	setflag FLAG_HIDE_AKALA_TOTEM
	setflag FLAG_DEFEATED_AKALA_TOTEM
	removeobject Akala_Totem
	msgbox Alola_Akala_TotemBattle_Text_1, MSGBOX_AUTOCLOSE
	clearflag FLAG_NO_WILD_CATCHING
	clearflag FLAG_NO_WILD_RUNNING
	clearflag FLAG_SMART_WILD_AI
	release
	end

Alola_Akala_TotemBattle_7:
	setflag FLAG_HIDE_AKALA_TOTEM
	setflag FLAG_DEFEATED_AKALA_TOTEM
	removeobject Akala_Totem
	msgbox Alola_Akala_TotemBattle_Text_3, MSGBOX_AUTOCLOSE
	clearflag FLAG_NO_WILD_CATCHING
	clearflag FLAG_NO_WILD_RUNNING
	clearflag FLAG_SMART_WILD_AI
	release
	end

Alola_Akala_TotemBattle_9:
	clearflag FLAG_NO_WILD_CATCHING
	clearflag FLAG_NO_WILD_RUNNING
	clearflag FLAG_SMART_WILD_AI
	release
	end


Alola_Akala_Totem_sign::
	lock
	goto_if_set FLAG_BATTLED_TAPU_FINI, Alola_Akala_Totem_sign_5
Alola_Akala_Totem_sign_3:
	msgbox Alola_Akala_Totem_sign_Text_5, MSGBOX_AUTOCLOSE
	release
	end

Alola_Akala_Totem_sign_2:
	msgbox Alola_Akala_Totem_sign_Text_0
	dynmultichoice 20, 4, FALSE, 4, 0, DYN_MULTICHOICE_CB_NONE, Alola_Akala_Totem_sign_Text_1, Alola_Akala_Sign_Text_0, Alola_Akala_Totem_sign_Text_2, Alola_Akala_Totem_sign_Text_3, Alola_Akala_Totem_sign_Text_4
	compare VAR_RESULT, 0
	goto_if_eq Alola_Akala_Totem_sign_12
	compare VAR_RESULT, 1
	goto_if_eq Alola_Akala_Totem_sign_15
	compare VAR_RESULT, 2
	goto_if_eq Alola_Akala_Totem_sign_18
	compare VAR_RESULT, 3
	goto_if_eq Alola_Akala_Totem_sign_20
	release
	end

Alola_Akala_Totem_sign_4:
	goto_if_set FLAG_BATTLED_TAPU_BULU, Alola_Akala_Totem_sign_8
	goto Alola_Akala_Totem_sign_3

Alola_Akala_Totem_sign_5:
	goto_if_set FLAG_BATTLED_TAPU_KOKO, Alola_Akala_Totem_sign_4
	goto Alola_Akala_Totem_sign_3

Alola_Akala_Totem_sign_8:
	goto_if_set FLAG_BATTLED_TAPU_LELE, Alola_Akala_Totem_sign_2
	goto Alola_Akala_Totem_sign_3

Alola_Akala_Totem_sign_12:
	warp MAP_MELEMELE_ISLE_HNS, 34, 26
	waitstate
	end

Alola_Akala_Totem_sign_15:
	warp MAP_AKALA_ISLE_HNS, 9, 10
	waitstate
	end

Alola_Akala_Totem_sign_18:
	warp MAP_ULA_ULA_FOREST_HNS, 16, 5
	waitstate
	end

Alola_Akala_Totem_sign_20:
	warp MAP_PONI_ISLE_HNS, 13, 8
	waitstate
	end


Alola_Akala_TapuLele_Flyover::
	goto_if_set FLAG_FLYOVER_TAPU_LELE, Alola_Akala_TapuLele_Flyover_2
	release
	end

Alola_Akala_TapuLele_Flyover_2:
	addobject Akala_Flyover_Tapu
	playse SE_M_FLY
	applymovement Akala_Flyover_Tapu, Alola_Akala_TapuLele_Flyover_Movement_0
	waitmovement 0
	removeobject Akala_Flyover_Tapu
	clearflag FLAG_FLYOVER_TAPU_LELE
	clearflag FLAG_HIDE_TAPU_LELE
	release
	end


Alola_Akala_BattleVsTapuLele::
	lock
	faceplayer
	playmoncry SPECIES_TAPU_LELE, CRY_MODE_ENCOUNTER
	msgbox Alola_Akala_BattleVsTapuLele_Text_0
	waitmoncry
	seteventmon SPECIES_TAPU_LELE, 60
	special BattleSetup_StartLegendaryBattle
	waitstate
	specialvar VAR_RESULT, GetBattleOutcome
	compare VAR_RESULT, B_OUTCOME_CAUGHT
	goto_if_eq Alola_Akala_BattleVsTapuLele_2
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq Alola_Akala_BattleVsTapuLele_3
	release
	end

	release
	end

Alola_Akala_BattleVsTapuLele_2:
	setflag FLAG_HIDE_TAPU_LELE
	setflag FLAG_BATTLED_TAPU_LELE
	removeobject Akala_Tapu
	release
	end

Alola_Akala_BattleVsTapuLele_3:
	setflag FLAG_HIDE_TAPU_LELE
	setflag FLAG_BATTLED_TAPU_LELE
	removeobject Akala_Tapu
	release
	end


Alola_Akala_TrainerBattleHiker::
	trainerbattle_single TRAINER_AKALA_HIKER_HNS, Alola_Akala_TrainerBattleHiker_Text_0, Alola_Akala_TrainerBattleHiker_Text_1
	msgbox Alola_Akala_TrainerBattleHiker_Text_2, MSGBOX_AUTOCLOSE
	release
	end


Alola_Akala_TrainerBattlePicnicker::
	trainerbattle_single TRAINER_AKALA_PICNICKER_HNS, Alola_Akala_TrainerBattlePicnicker_Text_0, Alola_Akala_TrainerBattlePicnicker_Text_1
	msgbox Alola_Akala_TrainerBattlePicnicker_Text_2, MSGBOX_AUTOCLOSE
	release
	end


Alola_Akala_TrainerBattleCamper::
	trainerbattle_single TRAINER_AKALA_CAMPER_HNS, Alola_Akala_TrainerBattleCamper_Text_0, Alola_Akala_TrainerBattleCamper_Text_1
	msgbox Alola_Akala_TrainerBattleCamper_Text_2, MSGBOX_AUTOCLOSE
	release
	end


Alola_Akala_TrainerBattleSwimmerLand::
	trainerbattle_single TRAINER_AKALA_SWIMMER_2_HNS, Alola_Akala_TrainerBattleSwimmerLand_Text_0, Alola_Akala_TrainerBattleSwimmerLand_Text_1
	msgbox Alola_Akala_TrainerBattleSwimmerLand_Text_2, MSGBOX_AUTOCLOSE
	release
	end


Alola_Akala_TrainerBattleSwimmerWater::
	trainerbattle_single TRAINER_AKALA_SWIMMER_1_HNS, Alola_Akala_TrainerBattleSwimmerWater_Text_0, Alola_Akala_TrainerBattleSwimmerWater_Text_1
	msgbox Alola_Akala_TrainerBattleSwimmerWater_Text_2, MSGBOX_AUTOCLOSE
	release
	end


Alola_Akala_TrainerBattleSwimmerWaterM::
	trainerbattle_single TRAINER_AKALA_SWIMMER_3_HNS, Alola_Akala_TrainerBattleSwimmerWaterM_Text_0, Alola_Akala_TrainerBattleSwimmerWaterM_Text_1
	msgbox Alola_Akala_TrainerBattleSwimmerWaterM_Text_2, MSGBOX_AUTOCLOSE
	release
	end


Alola_Akala_Bench_Heal::
	lock
	faceplayer
	msgbox Alola_Akala_Bench_Heal_Text_0, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq Alola_Akala_Bench_Heal_2
Alola_Akala_Bench_Heal_1:
	release
	end

Alola_Akala_Bench_Heal_2:
	fadescreenswapbuffers FADE_TO_BLACK
	special HealPlayerParty
	closemessage
	playfanfare MUS_HEAL
	waitfanfare
	applymovement LOCALID_PLAYER, Alola_Akala_Bench_Heal_Movement_0
	waitmovement 0
	fadescreenswapbuffers FADE_FROM_BLACK
	goto Alola_Akala_Bench_Heal_1


Alola_Akala_TotemBattle_Trigger_Movement_0:
	walk_in_place_down
	walk_in_place_down
	step_end

Alola_Akala_TapuLele_Flyover_Movement_0:
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	step_end

Alola_Akala_Bench_Heal_Movement_0:
	face_down
	step_end

Alola_Akala_BattleSandygast_Text_0:
	.string "Coorr!$"

Alola_Akala_Sign_Text_0:
	.string "Akala Isle$"

Alola_Akala_House_Sign_Text_0:
	.string "The Akala Villa.\p"
	.string "A place for visitors to stay while\n"
	.string "on Akala Isle.$"

Alola_Akala_Natu_Text_0:
	.string "NATU: TUUUUU!$"

Alola_Akala_OldManOnBench_Text_0:
	.string "Ah the weather is so nice today,\n"
	.string "isn't it?\p"
	.string "I was just feeding the NATU and this\n"
	.string "one decided to join me on my bench!$"

Alola_Akala_TotemBattle_Text_0:
	.string "Mortaar!$"

Alola_Akala_TotemBattle_Text_1:
	.string "Totem Magmortar was defeated!\n"
	.string "It scampered off somewhere…$"

Alola_Akala_TotemBattle_Text_2:
	.string "Salaa!$"

Alola_Akala_TotemBattle_Text_3:
	.string "Totem Probopass was defeated!\n"
	.string "It scampered off somewhere…$"

Alola_Akala_Totem_sign_Text_0:
	.string "The totem is emanating a strong\n"
	.string "energy…\p"
	.string "Touch the totem to teleport to another\n"
	.string "Isle?$"

Alola_Akala_Totem_sign_Text_1:
	.string "Melemele Isle$"

Alola_Akala_Totem_sign_Text_2:
	.string "Ula'ula Isle$"

Alola_Akala_Totem_sign_Text_3:
	.string "Poni Isle$"

Alola_Akala_Totem_sign_Text_4:
	.string "Cancel$"

Alola_Akala_Totem_sign_Text_5:
	.string "A strange totem stands here,\n"
	.string "power is emanating from it…$"

Alola_Akala_BattleVsTapuLele_Text_0:
	.string "Le-Lele!$"

Alola_Akala_TrainerBattleHiker_Text_0:
	.string "I came to the Isles to hike the\nmountains!$"

Alola_Akala_TrainerBattleHiker_Text_1:
	.string "And down I tumble…$"

Alola_Akala_TrainerBattleHiker_Text_2:
	.string "Akala Isle has the best hiking!\n"
	.string "It's got lush forests and rugged trails!$"

Alola_Akala_TrainerBattlePicnicker_Text_0:
	.string "Ha! Didn't see me, did you?$"

Alola_Akala_TrainerBattlePicnicker_Text_1:
	.string "I guess the element of surprise isn't\nalways super effective…$"

Alola_Akala_TrainerBattlePicnicker_Text_2:
	.string "It's so lush on Akala Isle,\n"
	.string "I can easily hide in the trees!$"

Alola_Akala_TrainerBattleCamper_Text_0:
	.string "I want to be the first to prove myself\nto the Totem Pokémon!$"

Alola_Akala_TrainerBattleCamper_Text_1:
	.string "Drat,\nthat's not going to help my case.$"

Alola_Akala_TrainerBattleCamper_Text_2:
	.string "There's a weird Totem further ahead but\n"
	.string "I haven't seen a Totem Pokémon.$"

Alola_Akala_TrainerBattleSwimmerLand_Text_0:
	.string "Hey! No shoes on the beach!$"

Alola_Akala_TrainerBattleSwimmerLand_Text_1:
	.string "Ouch,\nwhere's a lifeguard when you need one…$"

Alola_Akala_TrainerBattleSwimmerLand_Text_2:
	.string "Akala Isle has the best beaches!\n"
	.string "It's got soft sand and clear waters!$"

Alola_Akala_TrainerBattleSwimmerWater_Text_0:
	.string "Out of my way!\nI'm swimming laps!$"

Alola_Akala_TrainerBattleSwimmerWater_Text_1:
	.string "Not the break I was looking for…$"

Alola_Akala_TrainerBattleSwimmerWater_Text_2:
	.string "Ula'ula Isle has the best beaches!\n"
	.string "Ignore anyone who says otherwise!$"

Alola_Akala_TrainerBattleSwimmerWaterM_Text_0:
	.string "Hah!\nYou need to ride a Pokémon to surf?$"

Alola_Akala_TrainerBattleSwimmerWaterM_Text_1:
	.string "If I hadn't swam myself\nmaybe I would've had the energy to win…$"

Alola_Akala_TrainerBattleSwimmerWaterM_Text_2:
	.string "The current out here is strong!\n"
	.string "A Pokémon must be really powerful to\l"
	.string "migrate all the way out to the Isles!$"

Alola_Akala_Bench_Heal_Text_0:
	.string "Would you like to take a rest on this\n"
	.string "bench?$"
