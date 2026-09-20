UlaulaIsle_hns_MapScripts::
	.byte 0

Alola_Ulaula_FindItem1::
	finditem ITEM_FRIEND_BALL, 1
	end


Alola_Ulaula_FindItem2::
	finditem ITEM_PROTEIN, 1
	end


Alola_Ulaula_MtLanikalaSign::
	lock
	msgbox Alola_Ulaula_MtLanikalaSign_Text_0
	release
	end


Alola_Ulaula_UlaulaSign::
	lock
	msgbox Alola_Ulaula_UlaulaSign_Text_0
	release
	end


Alola_Ulaula_TapuBulu_Flyover::
	goto_if_set FLAG_FLYOVER_TAPU_BULU, Alola_Ulaula_TapuBulu_Flyover_2
	release
	end

Alola_Ulaula_TapuBulu_Flyover_2:
	addobject Ulaula_Flyover_Tapu
	playse SE_M_FLY
	applymovement Ulaula_Flyover_Tapu, Alola_Ulaula_TapuBulu_Flyover_Movement_0
	waitmovement 0
	removeobject Ulaula_Flyover_Tapu
	clearflag FLAG_FLYOVER_TAPU_BULU
	clearflag FLAG_HIDE_TAPU_BULU
	release
	end


Alola_Ulaula_Phant_outside::
	lock
	faceplayer
	hidefollower
	msgbox Alola_Ulaula_Phant_outside_Text_0, MSGBOX_AUTOCLOSE
	getplayerxy VAR_TEMP_0, VAR_TEMP_1
	compare VAR_TEMP_0, 35
	goto_if_eq Alola_Ulaula_Phant_outside_3
Alola_Ulaula_Phant_outside_1:
	compare VAR_TEMP_0, 36
	goto_if_eq Alola_Ulaula_Phant_outside_8
Alola_Ulaula_Phant_outside_6:
	compare VAR_TEMP_0, 37
	goto_if_eq Alola_Ulaula_Phant_outside_13
Alola_Ulaula_Phant_outside_11:
	compare VAR_TEMP_0, 36
	goto_if_eq Alola_Ulaula_Phant_outside_18
Alola_Ulaula_Phant_outside_16:
	playse SE_LEDGE
	waitse
	playse SE_LEDGE
	waitse
	msgbox Alola_Ulaula_Phant_outside_Text_1, MSGBOX_AUTOCLOSE
	getplayerxy VAR_TEMP_0, VAR_TEMP_1
	compare VAR_TEMP_0, 35
	goto_if_eq Alola_Ulaula_Phant_outside_23
Alola_Ulaula_Phant_outside_22:
	applymovement Phant_Outside, Alola_Ulaula_Phant_outside_Movement_6
	waitmovement 0
	playmoncry SPECIES_NOIVERN, 0
	applymovement Phant_Noivern_Outside, Alola_Ulaula_Phant_outside_Movement_5
	waitmovement 0
	removeobject Phant_Noivern_Outside
	removeobject Phant_Outside
	setflag FLAG_HIDE_PHANT_OUTSIDE
	clearflag FLAG_HIDE_PHANT_INSIDE
	release
	end

Alola_Ulaula_Phant_outside_2:
	applymovement Phant_Outside, Alola_Ulaula_Phant_outside_Movement_0
	goto Alola_Ulaula_Phant_outside_1

Alola_Ulaula_Phant_outside_3:
	compare VAR_TEMP_1, 46
	goto_if_eq Alola_Ulaula_Phant_outside_2
	goto Alola_Ulaula_Phant_outside_1

Alola_Ulaula_Phant_outside_7:
	applymovement Phant_Outside, Alola_Ulaula_Phant_outside_Movement_1
	goto Alola_Ulaula_Phant_outside_6

Alola_Ulaula_Phant_outside_8:
	compare VAR_TEMP_1, 47
	goto_if_eq Alola_Ulaula_Phant_outside_7
	goto Alola_Ulaula_Phant_outside_6

Alola_Ulaula_Phant_outside_12:
	applymovement Phant_Outside, Alola_Ulaula_Phant_outside_Movement_2
	goto Alola_Ulaula_Phant_outside_11

Alola_Ulaula_Phant_outside_13:
	compare VAR_TEMP_1, 46
	goto_if_eq Alola_Ulaula_Phant_outside_12
	goto Alola_Ulaula_Phant_outside_11

Alola_Ulaula_Phant_outside_17:
	applymovement Phant_Outside, Alola_Ulaula_Phant_outside_Movement_3
	goto Alola_Ulaula_Phant_outside_16

Alola_Ulaula_Phant_outside_18:
	compare VAR_TEMP_1, 45
	goto_if_eq Alola_Ulaula_Phant_outside_17
	goto Alola_Ulaula_Phant_outside_16

Alola_Ulaula_Phant_outside_21:
	applymovement Phant_Outside, Alola_Ulaula_Phant_outside_Movement_4
	waitmovement 0
	playmoncry SPECIES_NOIVERN, 0
	applymovement Phant_Noivern_Outside, Alola_Ulaula_Phant_outside_Movement_5
	waitmovement 0
	removeobject Phant_Noivern_Outside
	removeobject Phant_Outside
	setflag FLAG_HIDE_PHANT_OUTSIDE
	clearflag FLAG_HIDE_PHANT_INSIDE
	release
	end

Alola_Ulaula_Phant_outside_23:
	compare VAR_TEMP_1, 46
	goto_if_eq Alola_Ulaula_Phant_outside_21
	goto Alola_Ulaula_Phant_outside_22


Alola_Ulaula_TrainerBattlePicnicker::
	trainerbattle_single TRAINER_ULAULA_PICNICKER_HNS, Alola_Ulaula_TrainerBattlePicnicker_Text_0, Alola_Ulaula_TrainerBattlePicnicker_Text_1
	msgbox Alola_Ulaula_TrainerBattlePicnicker_Text_2, MSGBOX_AUTOCLOSE
	release
	end


Alola_Ulaula_TrainerBattleYoungster::
	trainerbattle_single TRAINER_ULAULA_YOUNGSTER_HNS, Alola_Ulaula_TrainerBattleYoungster_Text_0, Alola_Ulaula_TrainerBattleYoungster_Text_1
	msgbox Alola_Ulaula_TrainerBattleYoungster_Text_2, MSGBOX_AUTOCLOSE
	release
	end


Alola_Ulaula_TrainerBattleHiker::
	trainerbattle_single TRAINER_ULAULA_HIKER_HNS, Alola_Ulaula_TrainerBattleHiker_Text_0, Alola_Ulaula_TrainerBattleHiker_Text_1
	msgbox Alola_Ulaula_TrainerBattleHiker_Text_2, MSGBOX_AUTOCLOSE
	release
	end


Alola_Ulaula_TrainerBattleCooltrainer::
	trainerbattle_single TRAINER_ULAULA_COOLTRAINER_HNS, Alola_Ulaula_TrainerBattleCooltrainer_Text_0, Alola_Ulaula_TrainerBattleCooltrainer_Text_1
	msgbox Alola_Ulaula_TrainerBattleCooltrainer_Text_2, MSGBOX_AUTOCLOSE
	release
	end


Alola_Ulaula_LassNPC::
	lock
	faceplayer
	msgbox Alola_Ulaula_LassNPC_Text_0, MSGBOX_AUTOCLOSE
	release
	end


Alola_Ulaula_Bench_Heal_Right::
	specialvar VAR_RESULT, GetPlayerFacingDirection
	compare VAR_RESULT, DIR_EAST
	goto_if_eq Alola_Ulaula_Bench_Heal_Skip
	goto Alola_Ulaula_Bench_Heal

Alola_Ulaula_Bench_Heal_Left::
	specialvar VAR_RESULT, GetPlayerFacingDirection
	compare VAR_RESULT, DIR_WEST
	goto_if_eq Alola_Ulaula_Bench_Heal_Skip
	goto Alola_Ulaula_Bench_Heal

Alola_Ulaula_Bench_Heal_Skip:
	end

Alola_Ulaula_Bench_Heal:
	lock
	faceplayer
	msgbox Alola_Ulaula_Bench_Heal_Text_0, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq Alola_Ulaula_Bench_Heal_2
Alola_Ulaula_Bench_Heal_1:
	callnative UpdateFollowingPokemon
	release
	end

Alola_Ulaula_Bench_Heal_2:
	fadescreenswapbuffers FADE_TO_BLACK
	special HealPlayerParty
	closemessage
	playfanfare MUS_HEAL
	waitfanfare
	applymovement LOCALID_PLAYER, Alola_Ulaula_Bench_Heal_Movement_0
	waitmovement 0
	fadescreenswapbuffers FADE_FROM_BLACK
	goto Alola_Ulaula_Bench_Heal_1


Alola_Ulaula_TapuBulu_Flyover_Movement_0:
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
	walk_faster_up
	step_end

Alola_Ulaula_Phant_outside_Movement_0:
	jump_in_place_left
	jump_in_place_left
	step_end

Alola_Ulaula_Phant_outside_Movement_1:
	jump_in_place_down
	jump_in_place_down
	step_end

Alola_Ulaula_Phant_outside_Movement_2:
	jump_in_place_right
	jump_in_place_right
	step_end

Alola_Ulaula_Phant_outside_Movement_3:
	jump_in_place_up
	jump_in_place_up
	step_end

Alola_Ulaula_Phant_outside_Movement_4:
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_left
	walk_left
	step_end

Alola_Ulaula_Phant_outside_Movement_5:
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

Alola_Ulaula_Phant_outside_Movement_6:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	step_end

Alola_Ulaula_Bench_Heal_Movement_0:
	face_down
	step_end

Alola_Ulaula_BattlePalossand_Text_0:
	.string "Shuck!$"

Alola_Ulaula_MtLanikalaSign_Text_0:
	.string "This mountain is affectionately\n"
	.string "referred to as MT. LANIKALA by the\l"
	.string "locals, as it is the tallest mountain\l"
	.string "en las ISLAS ALOLA.\p"
	.string "The real name of this mountain has been\n"
	.string "lost to time.$"

Alola_Ulaula_UlaulaSign_Text_0:
	.string "ISLA ULA'ULA$"

Alola_Ulaula_Phant_outside_Text_0:
	.string "Hello there, {PLAYER}!\p"
	.string "I'm the developer who built this\n"
	.string "section of the game!\p"
	.string "I hope you enjoyed this taste of ALOLA.\p"
	.string "I'm working on a full demake of the\n"
	.string "region called ULTRA ECLIPSE.$"

Alola_Ulaula_Phant_outside_Text_1:
	.string "Please come visit me at my house at\n"
	.string "the top of this isle.\l"
	.string "I'll make it worth your while!$"

Alola_Ulaula_TrainerBattlePicnicker_Text_0:
	.string "Surprise!\nI was in the trees!$"

Alola_Ulaula_TrainerBattlePicnicker_Text_1:
	.string "Back into hiding I go…$"

Alola_Ulaula_TrainerBattlePicnicker_Text_2:
	.string "I thought I saw something red flying\n"
	.string "through the sky.\p"
	.string "Could it have been a POKéMON?$"

Alola_Ulaula_TrainerBattleYoungster_Text_0:
	.string "Hey, I'm going to be the first to climb\nMT. LANIKALA!$"

Alola_Ulaula_TrainerBattleYoungster_Text_1:
	.string "It's not even the real MT. LANIKALA…$"

Alola_Ulaula_TrainerBattleYoungster_Text_2:
	.string "Mi papá nunca me dijo el nombre real\n"
	.string "de esta montaña.\p"
	.string "Siempre la llamamos MT. LANIKALA.$"

Alola_Ulaula_TrainerBattleHiker_Text_0:
	.string "¡Debes ser fuerte para aguantar este\nterreno tan difícil!$"

Alola_Ulaula_TrainerBattleHiker_Text_1:
	.string "Uff,\ndebí entrenar más...$"

Alola_Ulaula_TrainerBattleHiker_Text_2:
	.string "¡ISLA ULA'ULA es la mejor para andar!\p"
	.string "Los locales llaman a esta montaña\n"
	.string "MT. LANIKALA, ¡pues es la más alta de\l"
	.string "las ISLAS ALOLA!$"

Alola_Ulaula_TrainerBattleCooltrainer_Text_0:
	.string "¡Esta cueva huele fatal!\n¡Luchemos para que me distraiga!$"

Alola_Ulaula_TrainerBattleCooltrainer_Text_1:
	.string "Debí traer un ambientador...$"

Alola_Ulaula_TrainerBattleCooltrainer_Text_2:
	.string "Tápate la nariz si piensas\n"
	.string "entrar en esa cueva.$"

Alola_Ulaula_LassNPC_Text_0:
	.string "El mar junto a las ISLAS es\n"
	.string "impresionante.\p"
	.string "Podría estar aquí todo el día\n"
	.string "viendo las olas.$"

Alola_Ulaula_Bench_Heal_Text_0:
	.string "¿Te gustaría descansar un poco en\n"
	.string "este banco?$"

Alola_Ulaula_EventScript_MoveTutor::
	lock
	faceplayer
	goto_if_set FLAG_ULAULA_MOVE_TUTOR_PAID, Alola_Ulaula_EventScript_MoveTutorMenu
	msgbox Alola_Ulaula_Text_MoveTutorIntro, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Alola_Ulaula_EventScript_MoveTutorDecline
	checkitem ITEM_HEART_SCALE, 5
	goto_if_eq VAR_RESULT, FALSE, Alola_Ulaula_EventScript_MoveTutorNoScales
	removeitem ITEM_HEART_SCALE, 5
	setflag FLAG_ULAULA_MOVE_TUTOR_PAID
	msgbox Alola_Ulaula_Text_MoveTutorPaid, MSGBOX_DEFAULT

Alola_Ulaula_EventScript_MoveTutorMenu::
	message Alola_Ulaula_Text_MoveTutorChoose
	waitmessage
	dynmultichoice 0, 0, FALSE, 6, 0, DYN_MULTICHOICE_CB_NONE, Alola_Ulaula_Text_TutorMove_Acrobatics, Alola_Ulaula_Text_TutorMove_AuroraVeil, Alola_Ulaula_Text_TutorMove_BrutalSwing, Alola_Ulaula_Text_TutorMove_Bulldoze, Alola_Ulaula_Text_TutorMove_Confide, Alola_Ulaula_Text_TutorMove_DazzlingGleam, Alola_Ulaula_Text_TutorMove_DragonTail, Alola_Ulaula_Text_TutorMove_EchoedVoice, Alola_Ulaula_Text_TutorMove_FlameCharge, Alola_Ulaula_Text_TutorMove_FrostBreath, Alola_Ulaula_Text_TutorMove_Infestation, Alola_Ulaula_Text_TutorMove_LeechLife, Alola_Ulaula_Text_TutorMove_LowSweep, Alola_Ulaula_Text_TutorMove_Psyshock, Alola_Ulaula_Text_TutorMove_Quash, Alola_Ulaula_Text_TutorMove_Round, Alola_Ulaula_Text_TutorMove_Scald, Alola_Ulaula_Text_TutorMove_SkyDrop, Alola_Ulaula_Text_TutorMove_SludgeWave, Alola_Ulaula_Text_TutorMove_SmackDown, Alola_Ulaula_Text_TutorMove_SmartStrike, Alola_Ulaula_Text_TutorMove_Snarl, Alola_Ulaula_Text_TutorMove_Venoshock, Alola_Ulaula_Text_TutorMove_VoltSwitch, Alola_Ulaula_Text_TutorMove_WildCharge, Alola_Ulaula_Text_TutorMove_WorkUp, Alola_Ulaula_Text_TutorMove_Cancel
	switch VAR_RESULT
	case 0, Alola_Ulaula_EventScript_TutorTeach_Acrobatics
	case 1, Alola_Ulaula_EventScript_TutorTeach_AuroraVeil
	case 2, Alola_Ulaula_EventScript_TutorTeach_BrutalSwing
	case 3, Alola_Ulaula_EventScript_TutorTeach_Bulldoze
	case 4, Alola_Ulaula_EventScript_TutorTeach_Confide
	case 5, Alola_Ulaula_EventScript_TutorTeach_DazzlingGleam
	case 6, Alola_Ulaula_EventScript_TutorTeach_DragonTail
	case 7, Alola_Ulaula_EventScript_TutorTeach_EchoedVoice
	case 8, Alola_Ulaula_EventScript_TutorTeach_FlameCharge
	case 9, Alola_Ulaula_EventScript_TutorTeach_FrostBreath
	case 10, Alola_Ulaula_EventScript_TutorTeach_Infestation
	case 11, Alola_Ulaula_EventScript_TutorTeach_LeechLife
	case 12, Alola_Ulaula_EventScript_TutorTeach_LowSweep
	case 13, Alola_Ulaula_EventScript_TutorTeach_Psyshock
	case 14, Alola_Ulaula_EventScript_TutorTeach_Quash
	case 15, Alola_Ulaula_EventScript_TutorTeach_Round
	case 16, Alola_Ulaula_EventScript_TutorTeach_Scald
	case 17, Alola_Ulaula_EventScript_TutorTeach_SkyDrop
	case 18, Alola_Ulaula_EventScript_TutorTeach_SludgeWave
	case 19, Alola_Ulaula_EventScript_TutorTeach_SmackDown
	case 20, Alola_Ulaula_EventScript_TutorTeach_SmartStrike
	case 21, Alola_Ulaula_EventScript_TutorTeach_Snarl
	case 22, Alola_Ulaula_EventScript_TutorTeach_Venoshock
	case 23, Alola_Ulaula_EventScript_TutorTeach_VoltSwitch
	case 24, Alola_Ulaula_EventScript_TutorTeach_WildCharge
	case 25, Alola_Ulaula_EventScript_TutorTeach_WorkUp
	case 26, Alola_Ulaula_EventScript_MoveTutorDecline
	case MULTI_B_PRESSED, Alola_Ulaula_EventScript_MoveTutorDecline
	end

Alola_Ulaula_EventScript_TutorTeach_Acrobatics::
	setvar VAR_0x8005, MOVE_ACROBATICS
	goto Alola_Ulaula_EventScript_MoveTutorTeachMove
	end

Alola_Ulaula_EventScript_TutorTeach_AuroraVeil::
	setvar VAR_0x8005, MOVE_AURORA_VEIL
	goto Alola_Ulaula_EventScript_MoveTutorTeachMove
	end

Alola_Ulaula_EventScript_TutorTeach_BrutalSwing::
	setvar VAR_0x8005, MOVE_BRUTAL_SWING
	goto Alola_Ulaula_EventScript_MoveTutorTeachMove
	end

Alola_Ulaula_EventScript_TutorTeach_Bulldoze::
	setvar VAR_0x8005, MOVE_BULLDOZE
	goto Alola_Ulaula_EventScript_MoveTutorTeachMove
	end

Alola_Ulaula_EventScript_TutorTeach_Confide::
	setvar VAR_0x8005, MOVE_CONFIDE
	goto Alola_Ulaula_EventScript_MoveTutorTeachMove
	end

Alola_Ulaula_EventScript_TutorTeach_DazzlingGleam::
	setvar VAR_0x8005, MOVE_DAZZLING_GLEAM
	goto Alola_Ulaula_EventScript_MoveTutorTeachMove
	end

Alola_Ulaula_EventScript_TutorTeach_DragonTail::
	setvar VAR_0x8005, MOVE_DRAGON_TAIL
	goto Alola_Ulaula_EventScript_MoveTutorTeachMove
	end

Alola_Ulaula_EventScript_TutorTeach_EchoedVoice::
	setvar VAR_0x8005, MOVE_ECHOED_VOICE
	goto Alola_Ulaula_EventScript_MoveTutorTeachMove
	end

Alola_Ulaula_EventScript_TutorTeach_FlameCharge::
	setvar VAR_0x8005, MOVE_FLAME_CHARGE
	goto Alola_Ulaula_EventScript_MoveTutorTeachMove
	end

Alola_Ulaula_EventScript_TutorTeach_FrostBreath::
	setvar VAR_0x8005, MOVE_FROST_BREATH
	goto Alola_Ulaula_EventScript_MoveTutorTeachMove
	end

Alola_Ulaula_EventScript_TutorTeach_Infestation::
	setvar VAR_0x8005, MOVE_INFESTATION
	goto Alola_Ulaula_EventScript_MoveTutorTeachMove
	end

Alola_Ulaula_EventScript_TutorTeach_LeechLife::
	setvar VAR_0x8005, MOVE_LEECH_LIFE
	goto Alola_Ulaula_EventScript_MoveTutorTeachMove
	end

Alola_Ulaula_EventScript_TutorTeach_LowSweep::
	setvar VAR_0x8005, MOVE_LOW_SWEEP
	goto Alola_Ulaula_EventScript_MoveTutorTeachMove
	end

Alola_Ulaula_EventScript_TutorTeach_Psyshock::
	setvar VAR_0x8005, MOVE_PSYSHOCK
	goto Alola_Ulaula_EventScript_MoveTutorTeachMove
	end

Alola_Ulaula_EventScript_TutorTeach_Quash::
	setvar VAR_0x8005, MOVE_QUASH
	goto Alola_Ulaula_EventScript_MoveTutorTeachMove
	end

Alola_Ulaula_EventScript_TutorTeach_Round::
	setvar VAR_0x8005, MOVE_ROUND
	goto Alola_Ulaula_EventScript_MoveTutorTeachMove
	end

Alola_Ulaula_EventScript_TutorTeach_Scald::
	setvar VAR_0x8005, MOVE_SCALD
	goto Alola_Ulaula_EventScript_MoveTutorTeachMove
	end

Alola_Ulaula_EventScript_TutorTeach_SkyDrop::
	setvar VAR_0x8005, MOVE_SKY_DROP
	goto Alola_Ulaula_EventScript_MoveTutorTeachMove
	end

Alola_Ulaula_EventScript_TutorTeach_SludgeWave::
	setvar VAR_0x8005, MOVE_SLUDGE_WAVE
	goto Alola_Ulaula_EventScript_MoveTutorTeachMove
	end

Alola_Ulaula_EventScript_TutorTeach_SmackDown::
	setvar VAR_0x8005, MOVE_SMACK_DOWN
	goto Alola_Ulaula_EventScript_MoveTutorTeachMove
	end

Alola_Ulaula_EventScript_TutorTeach_SmartStrike::
	setvar VAR_0x8005, MOVE_SMART_STRIKE
	goto Alola_Ulaula_EventScript_MoveTutorTeachMove
	end

Alola_Ulaula_EventScript_TutorTeach_Snarl::
	setvar VAR_0x8005, MOVE_SNARL
	goto Alola_Ulaula_EventScript_MoveTutorTeachMove
	end

Alola_Ulaula_EventScript_TutorTeach_Venoshock::
	setvar VAR_0x8005, MOVE_VENOSHOCK
	goto Alola_Ulaula_EventScript_MoveTutorTeachMove
	end

Alola_Ulaula_EventScript_TutorTeach_VoltSwitch::
	setvar VAR_0x8005, MOVE_VOLT_SWITCH
	goto Alola_Ulaula_EventScript_MoveTutorTeachMove
	end

Alola_Ulaula_EventScript_TutorTeach_WildCharge::
	setvar VAR_0x8005, MOVE_WILD_CHARGE
	goto Alola_Ulaula_EventScript_MoveTutorTeachMove
	end

Alola_Ulaula_EventScript_TutorTeach_WorkUp::
	setvar VAR_0x8005, MOVE_WORK_UP
	goto Alola_Ulaula_EventScript_MoveTutorTeachMove
	end

Alola_Ulaula_EventScript_MoveTutorTeachMove::
	buffermovename STR_VAR_1, VAR_0x8005
	msgbox Alola_Ulaula_Text_MoveTutorConfirm, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Alola_Ulaula_EventScript_MoveTutorMenu
	msgbox Alola_Ulaula_Text_MoveTutorWhichMon, MSGBOX_DEFAULT
	fadescreen FADE_TO_BLACK
	chooseboxmon SELECT_PC_MON_MOVE_TUTOR
	waitstate
	goto_if_eq VAR_RESULT, FALSE, Alola_Ulaula_EventScript_MoveTutorCancelMon
	msgbox Alola_Ulaula_Text_MoveTutorDone, MSGBOX_DEFAULT
	release
	end

Alola_Ulaula_EventScript_MoveTutorCancelMon::
	msgbox Alola_Ulaula_Text_MoveTutorComeBack, MSGBOX_DEFAULT
	release
	end

Alola_Ulaula_EventScript_MoveTutorDecline::
	msgbox Alola_Ulaula_Text_MoveTutorComeBack, MSGBOX_DEFAULT
	release
	end

Alola_Ulaula_EventScript_MoveTutorNoScales::
	msgbox Alola_Ulaula_Text_MoveTutorNoScales, MSGBOX_DEFAULT
	release
	end

Alola_Ulaula_Text_MoveTutorIntro:
	.string "¡URGH!\n"
	.string "¡AGH!\p"
	.string "¡TÚ!\p"
	.string "¿Los otros te enviaron aquí?\n"
	.string "¿Te dijeron que soy el\l"
	.string "maestro de movimientos POKéMON?\p"
	.string "........................\p"
	.string "Puedo entrenar a tus POKéMON en\n"
	.string "las artes de las ISLAS, pero\l"
	.string "cobro una pequeña tarifa.\p"
	.string "El precio son 5 ESCAMAS CORAZÓN.\p"
	.string "¿Las tienes?$"

Alola_Ulaula_Text_MoveTutorPaid:
	.string "A mi esposa le encantan estas cosas.\p"
	.string "Desde ahora, mis servicios\n"
	.string "están a tu disposición.$"

Alola_Ulaula_Text_MoveTutorNoScales:
	.string "Cinco ESCAMAS CORAZÓN.\n"
	.string "No cuatro.\p"
	.string "Intenta romper rocas.\n"
	.string "¡Con tu POKéMON o con tus puños!$"

Alola_Ulaula_Text_MoveTutorChoose:
	.string "¿Qué movimiento quieres?$"

Alola_Ulaula_Text_MoveTutorConfirm:
	.string "¿Quieres aprender {STR_VAR_1}?$"

Alola_Ulaula_Text_MoveTutorWhichMon:
	.string "¿Qué POKéMON debe aprenderlo?$"

Alola_Ulaula_Text_MoveTutorDone:
	.string "¡EXCELENTE!\p"
	.string "Tu POKéMON posee el conocimiento\n"
	.string "de las ISLAS.$"

Alola_Ulaula_Text_MoveTutorComeBack:
	.string "Las ISLAS no se moverán.\n"
	.string "Vuelve cuando quieras.$"

Alola_Ulaula_Text_TutorMove_Acrobatics:
	.string "ACROBACIA$"

Alola_Ulaula_Text_TutorMove_AuroraVeil:
	.string "VELO AURORA$"

Alola_Ulaula_Text_TutorMove_BrutalSwing:
	.string "GOLPE BRUTAL$"

Alola_Ulaula_Text_TutorMove_Bulldoze:
	.string "BULLDOZE$"

Alola_Ulaula_Text_TutorMove_Confide:
	.string "CONFIDENZA$"

Alola_Ulaula_Text_TutorMove_DazzlingGleam:
	.string "DAZZLING GLEAM$"

Alola_Ulaula_Text_TutorMove_DragonTail:
	.string "DRAGON TAIL$"

Alola_Ulaula_Text_TutorMove_EchoedVoice:
	.string "ECHOED VOICE$"

Alola_Ulaula_Text_TutorMove_FlameCharge:
	.string "FLAME CHARGE$"

Alola_Ulaula_Text_TutorMove_FrostBreath:
	.string "FROST BREATH$"

Alola_Ulaula_Text_TutorMove_Infestation:
	.string "INFESTATION$"

Alola_Ulaula_Text_TutorMove_LeechLife:
	.string "LEECH LIFE$"

Alola_Ulaula_Text_TutorMove_LowSweep:
	.string "LOW SWEEP$"

Alola_Ulaula_Text_TutorMove_Psyshock:
	.string "PSYSHOCK$"

Alola_Ulaula_Text_TutorMove_Quash:
	.string "QUASH$"

Alola_Ulaula_Text_TutorMove_Round:
	.string "ROUND$"

Alola_Ulaula_Text_TutorMove_Scald:
	.string "SCALD$"

Alola_Ulaula_Text_TutorMove_SkyDrop:
	.string "SKY DROP$"

Alola_Ulaula_Text_TutorMove_SludgeWave:
	.string "OLA DE LODO$"

Alola_Ulaula_Text_TutorMove_SmackDown:
	.string "GOLPE CARGA$"

Alola_Ulaula_Text_TutorMove_SmartStrike:
	.string "GOLPE INTELIGENTE$"

Alola_Ulaula_Text_TutorMove_Snarl:
	.string "GRUÑIDO$"

Alola_Ulaula_Text_TutorMove_Venoshock:
	.string "VENENOCHOQUE$"

Alola_Ulaula_Text_TutorMove_VoltSwitch:
	.string "CAMBIO VOLTAJE$"

Alola_Ulaula_Text_TutorMove_WildCharge:
	.string "CARGA SALVAJE$"

Alola_Ulaula_Text_TutorMove_WorkUp:
	.string "MAXIMIZAR$"

Alola_Ulaula_Text_TutorMove_Cancel:
	.string "CANCEL$"

