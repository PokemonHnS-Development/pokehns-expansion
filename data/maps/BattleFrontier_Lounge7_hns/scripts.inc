BattleFrontier_Lounge7_hns_MapScripts::
	.byte 0

@special ChooseMonForMoveTutor
BattleFrontier_Lounge7_EventScript_LeftMoveTutor_hns::
	lock
	faceplayer
	setvar VAR_TEMP_C, SCROLL_MULTI_BF_MOVE_TUTOR_1
	goto_if_set FLAG_MET_FRONTIER_BEAUTY_MOVE_TUTOR, BattleFrontier_Lounge7_EventScript_AlreadyMetLeftTutor_hns
	msgbox BattleFrontier_Lounge7_Text_LeftTutorIntro_hns, MSGBOX_DEFAULT
	setflag FLAG_MET_FRONTIER_BEAUTY_MOVE_TUTOR
	goto BattleFrontier_Lounge7_EventScript_ChooseLeftTutorMove_hns
	end

BattleFrontier_Lounge7_EventScript_AlreadyMetLeftTutor_hns::
	msgbox BattleFrontier_Lounge7_Text_LeftTutorWelcomeBack_hns, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge7_EventScript_ChooseLeftTutorMove_hns
	end

BattleFrontier_Lounge7_EventScript_ChooseLeftTutorMove_hns::
	message BattleFrontier_Lounge7_Text_TeachWhichMove_hns
	waitmessage
	special ShowBattlePointsWindow
	setvar VAR_TEMP_FRONTIER_TUTOR_ID, 0
	setvar VAR_0x8004, SCROLL_MULTI_BF_MOVE_TUTOR_1
	setvar VAR_0x8006, 0
	special ShowScrollableMultichoice
	waitstate
	copyvar VAR_TEMP_FRONTIER_TUTOR_SELECTION, VAR_RESULT
	switch VAR_RESULT
	case 0, BattleFrontier_Lounge7_EventScript_Softboiled_hns
	case 1, BattleFrontier_Lounge7_EventScript_SeismicToss_hns
	case 2, BattleFrontier_Lounge7_EventScript_DreamEater_hns
	case 3, BattleFrontier_Lounge7_EventScript_MegaPunch_hns
	case 4, BattleFrontier_Lounge7_EventScript_MegaKick_hns
	case 5, BattleFrontier_Lounge7_EventScript_BodySlam_hns
	case 6, BattleFrontier_Lounge7_EventScript_RockSlide_hns
	case 7, BattleFrontier_Lounge7_EventScript_Counter_hns
	case 8, BattleFrontier_Lounge7_EventScript_ThunderWave_hns
	case 9, BattleFrontier_Lounge7_EventScript_SwordsDance_hns
	case 10, BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect_hns_hns
	case MULTI_B_PRESSED, BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect_hns_hns
	end

BattleFrontier_Lounge7_EventScript_ChooseNewLeftTutorMove_hns::
	message BattleFrontier_Lounge7_Text_TeachWhichMove_hns
	waitmessage
	setvar VAR_TEMP_FRONTIER_TUTOR_ID, 0
	setvar VAR_0x8004, SCROLL_MULTI_BF_MOVE_TUTOR_1
	setvar VAR_0x8006, 1
	special ShowScrollableMultichoice
	waitstate
	copyvar VAR_TEMP_FRONTIER_TUTOR_SELECTION, VAR_RESULT
	switch VAR_RESULT
	case 0, BattleFrontier_Lounge7_EventScript_Softboiled_hns
	case 1, BattleFrontier_Lounge7_EventScript_SeismicToss_hns
	case 2, BattleFrontier_Lounge7_EventScript_DreamEater_hns
	case 3, BattleFrontier_Lounge7_EventScript_MegaPunch_hns
	case 4, BattleFrontier_Lounge7_EventScript_MegaKick_hns
	case 5, BattleFrontier_Lounge7_EventScript_BodySlam_hns
	case 6, BattleFrontier_Lounge7_EventScript_RockSlide_hns
	case 7, BattleFrontier_Lounge7_EventScript_Counter_hns
	case 8, BattleFrontier_Lounge7_EventScript_ThunderWave_hns
	case 9, BattleFrontier_Lounge7_EventScript_SwordsDance_hns
	case 10, BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect_hns_hns
	case MULTI_B_PRESSED, BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect_hns_hns
	end

BattleFrontier_Lounge7_EventScript_Softboiled_hns::
	setvar VAR_0x8008, 16
	setvar VAR_0x8005, MOVE_SOFT_BOILED
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection_hns
	end

BattleFrontier_Lounge7_EventScript_SeismicToss_hns::
	setvar VAR_0x8008, 24
	setvar VAR_0x8005, MOVE_SEISMIC_TOSS
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection_hns
	end

BattleFrontier_Lounge7_EventScript_DreamEater_hns::
	setvar VAR_0x8008, 24
	setvar VAR_0x8005, MOVE_DREAM_EATER
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection_hns
	end

BattleFrontier_Lounge7_EventScript_MegaPunch_hns::
	setvar VAR_0x8008, 24
	setvar VAR_0x8005, MOVE_MEGA_PUNCH
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection_hns
	end

BattleFrontier_Lounge7_EventScript_MegaKick_hns::
	setvar VAR_0x8008, 48
	setvar VAR_0x8005, MOVE_MEGA_KICK
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection_hns
	end

BattleFrontier_Lounge7_EventScript_BodySlam_hns::
	setvar VAR_0x8008, 48
	setvar VAR_0x8005, MOVE_BODY_SLAM
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection_hns
	end

BattleFrontier_Lounge7_EventScript_RockSlide_hns::
	setvar VAR_0x8008, 48
	setvar VAR_0x8005, MOVE_ROCK_SLIDE
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection_hns
	end

BattleFrontier_Lounge7_EventScript_Counter_hns::
	setvar VAR_0x8008, 48
	setvar VAR_0x8005, MOVE_COUNTER
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection_hns
	end

BattleFrontier_Lounge7_EventScript_ThunderWave_hns::
	setvar VAR_0x8008, 48
	setvar VAR_0x8005, MOVE_THUNDER_WAVE
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection_hns
	end

BattleFrontier_Lounge7_EventScript_SwordsDance_hns::
	setvar VAR_0x8008, 48
	setvar VAR_0x8005, MOVE_SWORDS_DANCE
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection_hns
	end

BattleFrontier_Lounge7_EventScript_RightMoveTutor_hns::
	lock
	faceplayer
	setvar VAR_TEMP_C, SCROLL_MULTI_BF_MOVE_TUTOR_2
	goto_if_set FLAG_MET_FRONTIER_SWIMMER_MOVE_TUTOR, BattleFrontier_Lounge7_EventScript_AlreadyMetRightTutor_hns
	msgbox BattleFrontier_Lounge7_Text_RightTutorIntro_hns, MSGBOX_DEFAULT
	setflag FLAG_MET_FRONTIER_SWIMMER_MOVE_TUTOR
	goto BattleFrontier_Lounge7_EventScript_ChooseRightTutorMove_hns
	end

BattleFrontier_Lounge7_EventScript_AlreadyMetRightTutor_hns::
	msgbox BattleFrontier_Lounge7_Text_RightTutorWelcomeBack_hns, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge7_EventScript_ChooseRightTutorMove_hns
	end

BattleFrontier_Lounge7_EventScript_ChooseRightTutorMove_hns::
	message BattleFrontier_Lounge7_Text_TeachWhichMove_hns
	waitmessage
	special ShowBattlePointsWindow
	setvar VAR_TEMP_FRONTIER_TUTOR_ID, 1
	setvar VAR_0x8004, SCROLL_MULTI_BF_MOVE_TUTOR_2
	setvar VAR_0x8006, 0
	special ShowScrollableMultichoice
	waitstate
	copyvar VAR_TEMP_FRONTIER_TUTOR_SELECTION, VAR_RESULT
	switch VAR_RESULT
	case 0, BattleFrontier_Lounge7_EventScript_DefenseCurl_hns
	case 1, BattleFrontier_Lounge7_EventScript_Snore_hns
	case 2, BattleFrontier_Lounge7_EventScript_MudSlap_hns
	case 3, BattleFrontier_Lounge7_EventScript_Swift_hns
	case 4, BattleFrontier_Lounge7_EventScript_IcyWind_hns
	case 5, BattleFrontier_Lounge7_EventScript_Endure_hns
	case 6, BattleFrontier_Lounge7_EventScript_PsychUp_hns
	case 7, BattleFrontier_Lounge7_EventScript_IcePunch_hns
	case 8, BattleFrontier_Lounge7_EventScript_ThunderPunch_hns
	case 9, BattleFrontier_Lounge7_EventScript_FirePunch_hns
	case 10, BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect_hns_hns
	case MULTI_B_PRESSED, BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect_hns_hns
	end

BattleFrontier_Lounge7_EventScript_ChooseNewRightTutorMove_hns::
	message BattleFrontier_Lounge7_Text_TeachWhichMove_hns
	waitmessage
	setvar VAR_TEMP_FRONTIER_TUTOR_ID, 1
	setvar VAR_0x8004, SCROLL_MULTI_BF_MOVE_TUTOR_2
	setvar VAR_0x8006, 1
	special ShowScrollableMultichoice
	waitstate
	copyvar VAR_TEMP_FRONTIER_TUTOR_SELECTION, VAR_RESULT
	switch VAR_RESULT
	case 0, BattleFrontier_Lounge7_EventScript_DefenseCurl_hns
	case 1, BattleFrontier_Lounge7_EventScript_Snore_hns
	case 2, BattleFrontier_Lounge7_EventScript_MudSlap_hns
	case 3, BattleFrontier_Lounge7_EventScript_Swift_hns
	case 4, BattleFrontier_Lounge7_EventScript_IcyWind_hns
	case 5, BattleFrontier_Lounge7_EventScript_Endure_hns
	case 6, BattleFrontier_Lounge7_EventScript_PsychUp_hns
	case 7, BattleFrontier_Lounge7_EventScript_IcePunch_hns
	case 8, BattleFrontier_Lounge7_EventScript_ThunderPunch_hns
	case 9, BattleFrontier_Lounge7_EventScript_FirePunch_hns
	case 10, BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect_hns_hns
	case MULTI_B_PRESSED, BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect_hns_hns
	end

BattleFrontier_Lounge7_EventScript_DefenseCurl_hns::
	setvar VAR_0x8008, 16
	setvar VAR_0x8005, MOVE_DEFENSE_CURL
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection_hns
	end

BattleFrontier_Lounge7_EventScript_Snore_hns::
	setvar VAR_0x8008, 24
	setvar VAR_0x8005, MOVE_SNORE
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection_hns
	end

BattleFrontier_Lounge7_EventScript_MudSlap_hns::
	setvar VAR_0x8008, 24
	setvar VAR_0x8005, MOVE_MUD_SLAP
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection_hns
	end

BattleFrontier_Lounge7_EventScript_Swift_hns::
	setvar VAR_0x8008, 24
	setvar VAR_0x8005, MOVE_SWIFT
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection_hns
	end

BattleFrontier_Lounge7_EventScript_IcyWind_hns::
	setvar VAR_0x8008, 24
	setvar VAR_0x8005, MOVE_ICY_WIND
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection_hns
	end

BattleFrontier_Lounge7_EventScript_Endure_hns::
	setvar VAR_0x8008, 48
	setvar VAR_0x8005, MOVE_ENDURE
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection_hns
	end

BattleFrontier_Lounge7_EventScript_PsychUp_hns::
	setvar VAR_0x8008, 48
	setvar VAR_0x8005, MOVE_PSYCH_UP
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection_hns
	end

BattleFrontier_Lounge7_EventScript_IcePunch_hns::
	setvar VAR_0x8008, 48
	setvar VAR_0x8005, MOVE_ICE_PUNCH
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection_hns
	end

BattleFrontier_Lounge7_EventScript_ThunderPunch_hns::
	setvar VAR_0x8008, 48
	setvar VAR_0x8005, MOVE_THUNDER_PUNCH
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection_hns
	end

BattleFrontier_Lounge7_EventScript_FirePunch_hns::
	setvar VAR_0x8008, 48
	setvar VAR_0x8005, MOVE_FIRE_PUNCH
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection_hns
	end

BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect_hns_hns::
	special CloseBattleFrontierTutorWindow
	special CloseBattlePointsWindow
	msgbox BattleFrontier_Lounge7_Text_YouDontWantTo_hns, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge7_EventScript_CancelChooseMon_hns_hns::
	msgbox BattleFrontier_Lounge7_Text_YouDontWantTo_hns, MSGBOX_DEFAULT
	release
	end

@ VAR_0x8008 is the price
@ VAR_TEMP_C is the scroll multichoice ID
@ VAR_TEMP_FRONTIER_TUTOR_SELECTION is the move selection
@ VAR_TEMP_FRONTIER_TUTOR_ID is which move tutor was spoken to
BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection_hns::
	special BufferBattleFrontierTutorMoveName
	buffernumberstring STR_VAR_2, VAR_0x8008
	msgbox BattleFrontier_Lounge7_Text_MoveWillBeXBattlePoints_hns, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_Lounge7_EventScript_ChooseNewMove_hns
	specialvar VAR_TEMP_1, GetFrontierBattlePoints
	goto_if_ge VAR_TEMP_1, VAR_0x8008, BattleFrontier_Lounge7_EventScript_TeachTutorMove_hns
	msgbox BattleFrontier_Lounge7_Text_HaventGotEnoughPoints_hns, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge7_EventScript_ChooseNewMove_hns
	end


BattleFrontier_Lounge7_EventScript_TeachTutorMove_hns::
	msgbox BattleFrontier_Lounge7_Text_TeachMoveToWhichMon_hns, MSGBOX_DEFAULT
	fadescreen FADE_TO_BLACK
	special CloseBattlePointsWindow
	special CloseBattleFrontierTutorWindow
	chooseboxmon SELECT_PC_MON_MOVE_TUTOR
	waitstate
	goto_if_eq VAR_RESULT, FALSE, BattleFrontier_Lounge7_EventScript_CancelChooseMon_hns_hns
	msgbox BattleFrontier_Lounge7_Text_IllTakeBattlePoints_hns, MSGBOX_DEFAULT
	copyvar VAR_0x8004, VAR_0x8008
	special TakeFrontierBattlePoints
	release
	end

BattleFrontier_Lounge7_EventScript_ChooseNewMove_hns::
	goto_if_eq VAR_TEMP_FRONTIER_TUTOR_ID, 0, BattleFrontier_Lounge7_EventScript_ChooseNewLeftTutorMove_hns
	goto_if_eq VAR_TEMP_FRONTIER_TUTOR_ID, 2, BattleFrontier_Lounge7_EventScript_ChooseNewElementalTutorMove
	goto BattleFrontier_Lounge7_EventScript_ChooseNewRightTutorMove_hns
	end

BattleFrontier_Lounge7_EventScript_Sailor_hns::
	msgbox BattleFrontier_Lounge7_Text_ThinkLadiesDontGetAlong_hns, MSGBOX_NPC
	end

BattleFrontier_Lounge7_EventScript_Gentleman_hns::
	msgbox BattleFrontier_Lounge7_Text_LadiesWereStrongAndBeautiful_hns, MSGBOX_NPC
	end

BattleFrontier_Lounge7_EventScript_ElementalMoveTutor::
	lock
	faceplayer
	setvar VAR_TEMP_C, SCROLL_MULTI_BF_MOVE_TUTOR_3
	goto_if_set FLAG_MET_FRONTIER_ELEMENTAL_MOVE_TUTOR, BattleFrontier_Lounge7_EventScript_AlreadyMetElementalTutor
	msgbox BattleFrontier_Lounge7_Text_ElementalTutorIntro, MSGBOX_DEFAULT
	setflag FLAG_MET_FRONTIER_ELEMENTAL_MOVE_TUTOR
	goto BattleFrontier_Lounge7_EventScript_ChooseElementalTutorMove
	end

BattleFrontier_Lounge7_EventScript_AlreadyMetElementalTutor::
	msgbox BattleFrontier_Lounge7_Text_ElementalTutorWelcomeBack, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge7_EventScript_ChooseElementalTutorMove
	end

BattleFrontier_Lounge7_EventScript_ChooseElementalTutorMove::
	message BattleFrontier_Lounge7_Text_TeachWhichMoveElemental
	waitmessage
	special ShowBattlePointsWindow
	setvar VAR_TEMP_FRONTIER_TUTOR_ID, 2
	setvar VAR_0x8004, SCROLL_MULTI_BF_MOVE_TUTOR_3
	setvar VAR_0x8006, 0
	special ShowScrollableMultichoice
	waitstate
	copyvar VAR_TEMP_FRONTIER_TUTOR_SELECTION, VAR_RESULT
	switch VAR_RESULT
	case 0, BattleFrontier_Lounge7_EventScript_FrenzyPlant
	case 1, BattleFrontier_Lounge7_EventScript_BlastBurn
	case 2, BattleFrontier_Lounge7_EventScript_HydroCannon
	case 3, BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect_hns
	case MULTI_B_PRESSED, BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect_hns
	end

BattleFrontier_Lounge7_EventScript_ChooseNewElementalTutorMove::
	message BattleFrontier_Lounge7_Text_TeachWhichMoveElemental
	waitmessage
	setvar VAR_TEMP_FRONTIER_TUTOR_ID, 2
	setvar VAR_0x8004, SCROLL_MULTI_BF_MOVE_TUTOR_3
	setvar VAR_0x8006, 1
	special ShowScrollableMultichoice
	waitstate
	copyvar VAR_TEMP_FRONTIER_TUTOR_SELECTION, VAR_RESULT
	switch VAR_RESULT
	case 0, BattleFrontier_Lounge7_EventScript_FrenzyPlant
	case 1, BattleFrontier_Lounge7_EventScript_BlastBurn
	case 2, BattleFrontier_Lounge7_EventScript_HydroCannon
	case 3, BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect_hns
	case MULTI_B_PRESSED, BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect_hns
	end

BattleFrontier_Lounge7_EventScript_FrenzyPlant::
	setvar VAR_0x8008, 64
	setvar VAR_0x8005, MOVE_FRENZY_PLANT
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection_hns
	end

BattleFrontier_Lounge7_EventScript_BlastBurn::
	setvar VAR_0x8008, 64
	setvar VAR_0x8005, MOVE_BLAST_BURN
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection_hns
	end

BattleFrontier_Lounge7_EventScript_HydroCannon::
	setvar VAR_0x8008, 64
	setvar VAR_0x8005, MOVE_HYDRO_CANNON
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection_hns
	end

BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect_hns::
	special CloseBattleFrontierTutorWindow
	special CloseBattlePointsWindow
	msgbox BattleFrontier_Lounge7_Text_YouDontWantTo, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge7_EventScript_CancelChooseMon_hns::
	msgbox BattleFrontier_Lounge7_Text_YouDontWantTo, MSGBOX_DEFAULT
	release
	end


BattleFrontier_Lounge7_Text_LeftTutorIntro_hns:
	.string "¡Buhahaha!\p"
	.string "No lo notarías ahora,\n"
	.string "¡pero yo era una ENTRENADORA dura!\p"
	.string "Tenía fama de ser la BEAUTY\n"
	.string "más fuerte de todas, ¡te lo digo!\p"
	.string "... ... ... ... ... ...\p"
	.string "¿Qué pasa ahora?\n"
	.string "No me crees.\p"
	.string "No soy como esa fanfarrona de\n"
	.string "allá. ¡Yo sí tengo talento!\p"
	.string "Déjame demostrártelo.\n"
	.string "Puedo enseñar a tu POKéMON movimientos\l"
	.string "especiales y lindos a la vez.\p"
	.string "Pero mis clases no son gratis.\n"
	.string "¿Qué tal si pagas los ataques que\l"
	.string "enseño con unos Puntos de Batalla?$"

BattleFrontier_Lounge7_Text_LeftTutorWelcomeBack_hns:
	.string "¡Buhahaha!\p"
	.string "¿Vuelves para aprender ataques\n"
	.string "especiales y lindos para POKéMON?$"

BattleFrontier_Lounge7_Text_TeachWhichMove_hns:
	.string "¡Bien, bien, mira aquí!\n"
	.string "¿Qué movimiento debería enseñar?$"

BattleFrontier_Lounge7_Text_MoveWillBeXBattlePoints_hns:
	.string "El ataque {STR_VAR_1}, ¿verdad?\n"
	.string "Serán {STR_VAR_2} Puntos de Batalla.$"

BattleFrontier_Lounge7_Text_TeachMoveToWhichMon_hns:
	.string "Bien, bien, ahora elige al POKéMON\n"
	.string "al que debo enseñarle el ataque.$"

BattleFrontier_Lounge7_Text_HaventGotEnoughPoints_hns:
	.string "Pero qué...\n"
	.string "You haven't got enough Battle Points!$"

BattleFrontier_Lounge7_Text_IllTakeBattlePoints_hns:
	.string "¿Ves lo hábil que soy ahora?\n"
	.string "¡Me llevo tus Puntos de Batalla!$"

BattleFrontier_Lounge7_Text_YouDontWantTo_hns:
	.string "¿Qué es eso?\n"
	.string "No querrás...\p"
	.string "Si quieres ver lo hábil que soy,\n"
	.string "¡ven a verme cuando quieras!$"

BattleFrontier_Lounge7_Text_RightTutorIntro_hns:
	.string "¡Ihihihi!\p"
	.string "Sé que es difícil verlo ahora, pero\n"
	.string "fui un ENTRENADOR fantástico.\p"
	.string "Tenía fama de ser el NADADOR más\n"
	.string "¡un NADADOR invencible, te digo!\p"
	.string "... ... ... ... ... ...\p"
	.string "¿Qué pasa?\n"
	.string "No me crees.\p"
	.string "No soy como esa mujer tan tonta de\n"
	.string "allá. ¡Yo sí tengo experiencia!\p"
	.string "Puedo demostrártelo.\n"
	.string "Puedo enseñar a tu POKéMON pasos\l"
	.string "fuertes y a la vez hermosos.\p"
	.string "Pero mis clases no son gratis.\n"
	.string "¿Qué tal si pagas los ataques que\l"
	.string "enseño con unos Puntos de Batalla?$"

BattleFrontier_Lounge7_Text_RightTutorWelcomeBack_hns:
	.string "¡Ihihihi!\p"
	.string "¿Vienes a aprender pasos de POKéMON\n"
	.string "fuertes y hermosos?$"

BattleFrontier_Lounge7_Text_ThinkLadiesDontGetAlong_hns:
	.string "Esas damas se critican tanto que\n"
	.string "seguro piensas que no se llevan\l"
	.string "bien entre ellas.\p"
	.string "Pero si fuera cierto, no estarían\n"
	.string "aquí juntas, ¿verdad?$"

BattleFrontier_Lounge7_Text_LadiesWereStrongAndBeautiful_hns:
	.string "Cuando yo era un pequeño YOUNGSTER,\n"
	.string "esas damas eran fuertes y bellas.\p"
	.string "Eran ídolos entre los TRAINERS.\p"
	.string "Incluso ahora, la edad no ha mermado\n"
	.string "sus habilidades.\p"
	.string "De hecho, los movimientos de sus\n"
	.string "POKéMON son aún más pulidos.\p"
	.string "Pero... por alguna razón, no puedo\n"
	.string "evitar sentir esto...\p"
	.string "El tiempo es tan cruel...$"

BattleFrontier_Lounge7_Text_SoftboiledDesc_hns::
	.string "Recupera hasta\n"
	.string "la mitad de los\n"
	.string "PS máximos.$"

BattleFrontier_Lounge7_Text_SeismicTossDesc_hns::
	.string "Inflige un daño\n"
	.string "idéntico al\n"
	.string "nivel del usuario.$"

BattleFrontier_Lounge7_Text_DreamEaterDesc_hns::
	.string "Recupera la mitad del\n"
	.string "daño infligido\n"
	.string "a un rival dormido.$"

BattleFrontier_Lounge7_Text_MegaPunchDesc_hns::
	.string "Un golpe fuerte\n"
	.string "lanzado con un\n"
	.string "poder increíble.$"

BattleFrontier_Lounge7_Text_MegaKickDesc_hns::
	.string "Una patada\n"
	.string "extremadamente fuerte\n"
	.string "fuerza intensa.$"

BattleFrontier_Lounge7_Text_BodySlamDesc_hns::
	.string "Un placaje total\n"
	.string "que puede causar\n"
	.string "parálisis.$"

BattleFrontier_Lounge7_Text_RockSlideDesc_hns::
	.string "Lanza rocas\n"
	.string "grandes. Puede\n"
	.string "causar retroceso.$"

BattleFrontier_Lounge7_Text_CounterDesc_hns::
	.string "Responde a un\n"
	.string "golpe físico con\n"
	.string "el doble de poder.$"

BattleFrontier_Lounge7_Text_ThunderWaveDesc_hns::
	.string "Una descarga\n"
	.string "eléctrica débil\n"
	.string "paraliza al rival.$"

BattleFrontier_Lounge7_Text_SwordsDanceDesc_hns::
	.string "Una danza de lucha\n"
	.string "que aumenta\n"
	.string "mucho el ATAQUE.$"

BattleFrontier_Lounge7_Text_DefenseCurlDesc_hns::
	.string "Se encoge para\n"
	.string "ocultar puntos débiles\n"
	.string "y subir la DEFENSA.$"

BattleFrontier_Lounge7_Text_SnoreDesc_hns::
	.string "Un fuerte ataque\n"
	.string "que solo puede usarse\n"
	.string "mientras duerme.$"

BattleFrontier_Lounge7_Text_MudSlapDesc_hns::
	.string "Lanza lodo a la\n"
	.string "cara del rival para\n"
	.string "reduce su precisión.$"

BattleFrontier_Lounge7_Text_SwiftDesc_hns::
	.string "Lanza rayos en\n"
	.string "forma de estrella\n"
	.string "que nunca fallan.$"

BattleFrontier_Lounge7_Text_IcyWindDesc_hns::
	.string "Ataque gélido que\n"
	.string "reduce la\n"
	.string "VELOCIDAD rival.$"

BattleFrontier_Lounge7_Text_EndureDesc_hns::
	.string "Resiste cualquier\n"
	.string "ataque por 1 turno,\n"
	.string "dejando 1 PS.$"

BattleFrontier_Lounge7_Text_PsychUpDesc_hns::
	.string "Copia el efecto o\n"
	.string "efectos del rival y\n"
	.string "se le da al usuario.$"

BattleFrontier_Lounge7_Text_IcePunchDesc_hns::
	.string "Un puñetazo gélido\n"
	.string "que puede\n"
	.string "congelar al rival.$"

BattleFrontier_Lounge7_Text_ThunderPunchDesc_hns::
	.string "Un puñetazo\n"
	.string "eléctrico que puede\n"
	.string "paralizar al rival.$"

BattleFrontier_Lounge7_Text_FirePunchDesc_hns::
	.string "Un puñetazo ígneo\n"
	.string "que puede quemar\n"
	.string "al rival.$"


BattleFrontier_Lounge7_Text_ElementalTutorIntro::
	.string "Zzzzzz...\p"
	.string "Qué, cómo, qué?\p"
	.string "Oh, perdón, estaba dormitando.\p"
	.string "Soy el TUTOR ELEMENTAL.\p"
	.string "Tengo el poder de enseñar los\n"
	.string "movimientos más fuertes a POKéMON\l"
	.string "de tipo PLANTA, FUEGO y AGUA.\p"
	.string "¿Viniste a aprender un poder\n"
	.string "tan fuerte?$"

BattleFrontier_Lounge7_Text_ElementalTutorWelcomeBack:
	.string "Zzzzzz...\p"
	.string "Qué, cómo, qué, quién?\p"
	.string "Oh, ¿viniste a aprender el poder\n"
	.string "de mis movimientos más fuertes?$"

BattleFrontier_Lounge7_Text_TeachWhichMoveElemental::
	.string "¿Qué movimiento crees que es el\n"
	.string "ideal para tu POKéMON?$"

BattleFrontier_Lounge7_Text_StrongElementalMoveDesc::
	.string "Es poderoso, pero\n"
	.string "deja al usuario\n"
	.string "inmóvil un turno.$"

