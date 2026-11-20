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
	.string "בו-הא-הא-הא!\p"
	.string "עכשיו אי אפשר לנחש את זה,\n"
	.string "אבל פעם הייתי מאמנת קשוחה.\p"
	.string "היה לי מוניטין של היפהפייה\n"
	.string "הכי קשוחה בסביבה, אני אומרת לך!\p"
	.string "… … … … … …\p"
	.string "מה עכשיו?\n"
	.string "אתה לא מאמין לי.\p"
	.string "אני לא כמו הרברבנית ההיא שם.\n"
	.string "לי באמת יש כישרון!\p"
	.string "אני אוכיח לך.\p"
	.string "אני יכולה ללמד את הפוקימונים שלך\n"
	.string "מהלכים מיוחדים, ובכל זאת חמודים.\p"
	.string "אבל השיעורים שלי לא בחינם. מה דעתך\n"
	.string "לשלם על המהלכים בקצת נקודות קרב?$"

BattleFrontier_Lounge7_Text_LeftTutorWelcomeBack_hns:
	.string "בו-הא-הא-הא!\p"
	.string "חזרת ללמוד מהלכי פוקימון מיוחדים,\n"
	.string "ובכל זאת חמודים?$"

BattleFrontier_Lounge7_Text_TeachWhichMove_hns:
	.string "טוב, טוב, הנה!\n"
	.string "איזה מהלך ללמד?$"

BattleFrontier_Lounge7_Text_MoveWillBeXBattlePoints_hns:
	.string "המהלך {STR_VAR_1}, כן? זה יעלה\n"
	.string "{STR_VAR_2} נקודות קרב, בסדר?$"

BattleFrontier_Lounge7_Text_TeachMoveToWhichMon_hns:
	.string "טוב, טוב, עכשיו צריך לבחור\n"
	.string "לאיזה פוקימון ללמד את המהלך.$"

BattleFrontier_Lounge7_Text_HaventGotEnoughPoints_hns:
	.string "מה זה…\n"
	.string "אין לך מספיק נקודות קרב!$"

BattleFrontier_Lounge7_Text_IllTakeBattlePoints_hns:
	.string "נו, ראית איזה כישרון יש לי?\n"
	.string "אקח את נקודות הקרב שלך, תודה!$"

BattleFrontier_Lounge7_Text_YouDontWantTo_hns:
	.string "מה?\n"
	.string "אתה לא רוצה…\p"
	.string "אם אתה רוצה לראות את הכישרון שלי,\n"
	.string "בוא אליי מתי שתרצה!$"

BattleFrontier_Lounge7_Text_RightTutorIntro_hns:
	.string "אי-הי-הי-הי!\p"
	.string "אני יודעת שקשה לראות את זה עכשיו,\n"
	.string "אבל פעם הייתי מאמנת פנטסטית.\p"
	.string "היה לי מוניטין של השחיינית הכי\n"
	.string "בלתי מנוצחת בסביבה, אני אומרת לך!\p"
	.string "… … … … … …\p"
	.string "מה קרה?\n"
	.string "אתה לא מאמין לי.\p"
	.string "אני לא כמו הליצנית ההיא שם.\n"
	.string "לי באמת יש ניסיון!\p"
	.string "אני יכולה להוכיח לך.\p"
	.string "אני יכולה ללמד את הפוקימונים שלך\n"
	.string "מהלכים חזקים, ובכל זאת יפים.\p"
	.string "אבל השיעורים שלי לא בחינם. מה דעתך\n"
	.string "לשלם על המהלכים בקצת נקודות קרב?$"

BattleFrontier_Lounge7_Text_RightTutorWelcomeBack_hns:
	.string "אי-הי-הי-הי!\p"
	.string "באת ללמוד מהלכי פוקימון חזקים,\n"
	.string "ובכל זאת יפים?$"

BattleFrontier_Lounge7_Text_ThinkLadiesDontGetAlong_hns:
	.string "הגברות האלה משמיצות זו את זו,\n"
	.string "אז בטח נראה לך שהן לא מסתדרות.\p"
	.string "אבל אם זה היה נכון, הן לא היו\n"
	.string "נשארות כאן ביחד, נכון?$"

BattleFrontier_Lounge7_Text_LadiesWereStrongAndBeautiful_hns:
	.string "כשהייתי רק צעיר קטנטן,\n"
	.string "הגברות האלה היו חזקות ויפות.\p"
	.string "כולנו, המאמנים, הערצנו אותן.\p"
	.string "גם היום, הגיל לא הקהה את\n"
	.string "היכולות שלהן.\p"
	.string "למעשה, מהלכי הפוקימונים שלהן\n"
	.string "רק השתכללו עוד יותר.\p"
	.string "אבל… משום מה, אני לא יכול\n"
	.string "שלא להרגיש את זה…\p"
	.string "הזמן כל כך אכזר…$"

BattleFrontier_Lounge7_Text_SoftboiledDesc_hns::
	.string "Recovers up to\n"
	.string "half the user's\n"
	.string "maximum HP.$"

BattleFrontier_Lounge7_Text_SeismicTossDesc_hns::
	.string "Inflicts damage\n"
	.string "identical to the\n"
	.string "user's level.$"

BattleFrontier_Lounge7_Text_DreamEaterDesc_hns::
	.string "Recovers half the\n"
	.string "damage inflicted\n"
	.string "on a sleeping foe.$"

BattleFrontier_Lounge7_Text_MegaPunchDesc_hns::
	.string "A strong punch\n"
	.string "thrown with\n"
	.string "incredible power.$"

BattleFrontier_Lounge7_Text_MegaKickDesc_hns::
	.string "An extremely\n"
	.string "powerful kick with\n"
	.string "intense force.$"

BattleFrontier_Lounge7_Text_BodySlamDesc_hns::
	.string "A full-body slam\n"
	.string "that may cause\n"
	.string "paralysis.$"

BattleFrontier_Lounge7_Text_RockSlideDesc_hns::
	.string "Large boulders\n"
	.string "are hurled. May\n"
	.string "cause flinching.$"

BattleFrontier_Lounge7_Text_CounterDesc_hns::
	.string "Retaliates any\n"
	.string "physical hit with\n"
	.string "double the power.$"

BattleFrontier_Lounge7_Text_ThunderWaveDesc_hns::
	.string "A weak jolt of\n"
	.string "electricity that\n"
	.string "paralyzes the foe.$"

BattleFrontier_Lounge7_Text_SwordsDanceDesc_hns::
	.string "A fighting dance\n"
	.string "that sharply\n"
	.string "raises ATTACK.$"

BattleFrontier_Lounge7_Text_DefenseCurlDesc_hns::
	.string "Curls up to con-\n"
	.string "ceal weak spots\n"
	.string "and raise DEFENSE.$"

BattleFrontier_Lounge7_Text_SnoreDesc_hns::
	.string "A loud attack\n"
	.string "that can be used\n"
	.string "only while asleep.$"

BattleFrontier_Lounge7_Text_MudSlapDesc_hns::
	.string "Hurls mud in the\n"
	.string "foe's face to re-\n"
	.string "duce its accuracy.$"

BattleFrontier_Lounge7_Text_SwiftDesc_hns::
	.string "Sprays star-\n"
	.string "shaped rays\n"
	.string "that never miss.$"

BattleFrontier_Lounge7_Text_IcyWindDesc_hns::
	.string "A chilling attack\n"
	.string "that lowers the\n"
	.string "foe's SPEED.$"

BattleFrontier_Lounge7_Text_EndureDesc_hns::
	.string "Endures any at-\n"
	.string "tack for 1 turn,\n"
	.string "leaving 1HP.$"

BattleFrontier_Lounge7_Text_PsychUpDesc_hns::
	.string "Copies the foe's\n"
	.string "effect(s) and\n"
	.string "gives to the user.$"

BattleFrontier_Lounge7_Text_IcePunchDesc_hns::
	.string "An icy punch\n"
	.string "that may\n"
	.string "freeze the foe.$"

BattleFrontier_Lounge7_Text_ThunderPunchDesc_hns::
	.string "An electrified\n"
	.string "punch that may\n"
	.string "paralyze the foe.$"

BattleFrontier_Lounge7_Text_FirePunchDesc_hns::
	.string "A fiery punch\n"
	.string "that may burn\n"
	.string "the foe.$"


BattleFrontier_Lounge7_Text_ElementalTutorIntro::
	.string "זזזזזז…\p"
	.string "מה, איך, מה?\p"
	.string "אה, סליחה, נמנמתי קצת.\p"
	.string "אני מורה היסודות.\p"
	.string "יש לי את הכוח ללמד פוקימוני עשב,\n"
	.string "אש ומים את המהלכים החזקים ביותר.\p"
	.string "באת ללמוד כוח עצום שכזה?$"

BattleFrontier_Lounge7_Text_ElementalTutorWelcomeBack:
	.string "זזזזזז…\p"
	.string "מה, איך, מה, מי?\p"
	.string "אה, באת ללמוד את הכוח\n"
	.string "של המהלכים החזקים ביותר שלי?$"

BattleFrontier_Lounge7_Text_TeachWhichMoveElemental::
	.string "איזה מהלך לדעתך מתאים\n"
	.string "לפוקימון שלך?$"

BattleFrontier_Lounge7_Text_StrongElementalMoveDesc::
	.string "חזק, אך המשתמש\n"
	.string "מושבת לתור אחד.$"

