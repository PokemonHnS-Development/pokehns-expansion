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
	.string "המקומיים מכנים את ההר הזה בחיבה בשם\n"
	.string "הר לניקאלה, כי הוא הגבוה באיי אלולה.\p"
	.string "שמו האמיתי של ההר הזה\n"
	.string "נשכח עם השנים.$"

Alola_Ulaula_UlaulaSign_Text_0:
	.string "האי אולאולה$"

Alola_Ulaula_Phant_outside_Text_0:
	.string "שלום לך, {PLAYER}!\p"
	.string "אני המפתח שבנה\n"
	.string "את החלק הזה של המשחק!\p"
	.string "מקווה שנהנית מהטעימה הזו מאלולה.\p"
	.string "אני עובד על גרסת רטרו מלאה של\n"
	.string "האזור, שנקראת אולטרה אקליפס.$"

Alola_Ulaula_Phant_outside_Text_1:
	.string "בבקשה, בוא לבקר אותי בבית שלי\n"
	.string "בראש האי הזה. זה ישתלם לך!$"

Alola_Ulaula_TrainerBattlePicnicker_Text_0:
	.string "הפתעה!\n"
	.string "הייתי בין העצים!$"

Alola_Ulaula_TrainerBattlePicnicker_Text_1:
	.string "חוזרת למחבוא…$"

Alola_Ulaula_TrainerBattlePicnicker_Text_2:
	.string "נדמה לי שראיתי משהו אדום\n"
	.string "עף בשמיים.\p"
	.string "אולי זה היה פוקימון?$"

Alola_Ulaula_TrainerBattleYoungster_Text_0:
	.string "היי, אני אהיה הראשון שיטפס\n"
	.string "על הר לניקאלה!$"

Alola_Ulaula_TrainerBattleYoungster_Text_1:
	.string "זה אפילו לא הר לניקאלה האמיתי…$"

Alola_Ulaula_TrainerBattleYoungster_Text_2:
	.string "אבא שלי אף פעם לא אמר לי\n"
	.string "מה השם האמיתי של ההר הזה.\p"
	.string "תמיד פשוט קראנו לו הר לניקאלה.$"

Alola_Ulaula_TrainerBattleHiker_Text_0:
	.string "צריך להיות קשוח כדי להתמודד\n"
	.string "עם השטח הקשה הזה!$"

Alola_Ulaula_TrainerBattleHiker_Text_1:
	.string "אוף,\n"
	.string "הייתי צריך להתאמן קשה יותר…$"

Alola_Ulaula_TrainerBattleHiker_Text_2:
	.string "באי אולאולה הטיולים הכי טובים!\p"
	.string "המקומיים קוראים להר הזה הר לניקאלה,\n"
	.string "כי הוא הגבוה ביותר באיי אלולה!$"

Alola_Ulaula_TrainerBattleCooltrainer_Text_0:
	.string "המערה הזאת מסריחה נורא!\n"
	.string "בוא נילחם, שאשכח קצת מהריח!$"

Alola_Ulaula_TrainerBattleCooltrainer_Text_1:
	.string "הייתי צריכה להביא מטהר אוויר…$"

Alola_Ulaula_TrainerBattleCooltrainer_Text_2:
	.string "אם מתכננים להיכנס למערה הזאת,\n"
	.string "כדאי לסתום את האף.$"

Alola_Ulaula_LassNPC_Text_0:
	.string "הים ליד האיים באמת\n"
	.string "עוצר נשימה.\p"
	.string "הייתי יכולה לשבת כאן כל היום\n"
	.string "ופשוט להסתכל על הגלים.$"

Alola_Ulaula_Bench_Heal_Text_0:
	.string "לנוח קצת על הספסל הזה?$"

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
	.string "אררג!\n"
	.string "אאח!\p"
	.string "אתה!\p"
	.string "האחרים שלחו אותך לכאן?\n"
	.string "הם סיפרו לך שאני אמן מהלכי הפוקימונים?\p"
	.string "........................\p"
	.string "אני יכול לאמן את הפוקימונים שלך\n"
	.string "בדרכי האיים, אבל קודם כול, תשלום קטן.\p"
	.string "המחיר הוא 5 קשקשי לב.\p"
	.string "יש לך אותם?$"

Alola_Ulaula_Text_MoveTutorPaid:
	.string "אשתי מתה על הדברים האלה.\p"
	.string "מעכשיו, השירותים שלי\n"
	.string "עומדים לרשותך.$"

Alola_Ulaula_Text_MoveTutorNoScales:
	.string "חמישה קשקשי לב.\n"
	.string "לא ארבעה.\p"
	.string "כדאי לנסות לנפץ סלעים.\n"
	.string "עם הפוקימונים שלך, או עם האגרופים!$"

Alola_Ulaula_Text_MoveTutorChoose:
	.string "איזה מהלך תרצה?$"

Alola_Ulaula_Text_MoveTutorConfirm:
	.string "ללמד את המהלך {STR_VAR_1}?$"

Alola_Ulaula_Text_MoveTutorWhichMon:
	.string "איזה פוקימון ילמד אותו?$"

Alola_Ulaula_Text_MoveTutorDone:
	.string "מצוין!\p"
	.string "הפוקימון שלך נושא עכשיו\n"
	.string "את הידע של האיים.$"

Alola_Ulaula_Text_MoveTutorComeBack:
	.string "האיים לא הולכים לשום מקום.\n"
	.string "אפשר לחזור מתי שרוצים.$"

Alola_Ulaula_Text_TutorMove_Acrobatics:
	.string "אקרובטיקה$"

Alola_Ulaula_Text_TutorMove_AuroraVeil:
	.string "צעיף זוהר$"

Alola_Ulaula_Text_TutorMove_BrutalSwing:
	.string "תנופה אכזרית$"

Alola_Ulaula_Text_TutorMove_Bulldoze:
	.string "דחפור$"

Alola_Ulaula_Text_TutorMove_Confide:
	.string "שיתוף סוד$"

Alola_Ulaula_Text_TutorMove_DazzlingGleam:
	.string "בוהק מסנוור$"

Alola_Ulaula_Text_TutorMove_DragonTail:
	.string "זנב דרקון$"

Alola_Ulaula_Text_TutorMove_EchoedVoice:
	.string "קול מהדהד$"

Alola_Ulaula_Text_TutorMove_FlameCharge:
	.string "שעטת להבה$"

Alola_Ulaula_Text_TutorMove_FrostBreath:
	.string "נשימת כפור$"

Alola_Ulaula_Text_TutorMove_Infestation:
	.string "מכת מזיקים$"

Alola_Ulaula_Text_TutorMove_LeechLife:
	.string "התעלקות$"

Alola_Ulaula_Text_TutorMove_LowSweep:
	.string "טאטוא נמוך$"

Alola_Ulaula_Text_TutorMove_Psyshock:
	.string "הלם על-חושי$"

Alola_Ulaula_Text_TutorMove_Quash:
	.string "דיכוי$"

Alola_Ulaula_Text_TutorMove_Round:
	.string "שירת סבב$"

Alola_Ulaula_Text_TutorMove_Scald:
	.string "מים רותחים$"

Alola_Ulaula_Text_TutorMove_SkyDrop:
	.string "השלכה משמים$"

Alola_Ulaula_Text_TutorMove_SludgeWave:
	.string "גל רפש$"

Alola_Ulaula_Text_TutorMove_SmackDown:
	.string "מכה לקרקע$"

Alola_Ulaula_Text_TutorMove_SmartStrike:
	.string "מכה מחוכמת$"

Alola_Ulaula_Text_TutorMove_Snarl:
	.string "נביחה$"

Alola_Ulaula_Text_TutorMove_Venoshock:
	.string "הלם ארס$"

Alola_Ulaula_Text_TutorMove_VoltSwitch:
	.string "החלפת וולט$"

Alola_Ulaula_Text_TutorMove_WildCharge:
	.string "שעטה פראית$"

Alola_Ulaula_Text_TutorMove_WorkUp:
	.string "גיוס כוחות$"

Alola_Ulaula_Text_TutorMove_Cancel:
	.string "ביטול$"

