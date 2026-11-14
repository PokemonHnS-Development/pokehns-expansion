.set FOUND_FIRST_SWITCH, FLAG_TEMP_1
.set SWITCH1_ID,         VAR_0x8004
.set SWITCH2_ID,         VAR_0x8005
.set TRASH_CAN_ID,       VAR_0x8008

.set CHECK_VISITOR_STATE, 6
.set TYPE, VAR_0x8003
.set ARGUMENT, VAR_0x8004

VermilionCity_Gym_hns_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, VermilionCity_Gym_OnLoad
	map_script MAP_SCRIPT_ON_TRANSITION, VermilionCity_Gym_OnTransition
	.byte 0

VermilionCity_Gym_OnLoad::
	call_if_set FOUND_FIRST_SWITCH, VermilionCity_Gym_EventScript_SetOneBeamOff
	call_if_set FLAG_FOUND_BOTH_VERMILION_GYM_SWITCHES, VermilionCity_Gym_EventScript_SetBeamsOff
	end

VermilionCity_Gym_EventScript_SetOneBeamOff::
	setmetatile 3, 6, METATILE_VermilionGym_Beam_Node_TopLeft_HalfOn, 1
	setmetatile 4, 6, METATILE_VermilionGym_Beam_Node_TopLeft_Edge_HalfOn, 1
	setmetatile 5, 6, METATILE_VermilionGym_Beam_MidTop_HalfOn, 1
	setmetatile 6, 6, METATILE_VermilionGym_Beam_Node_TopRight_Edge_HalfOn, 1
	setmetatile 7, 6, METATILE_VermilionGym_Beam_Node_TopRight_HalfOn, 1
	setmetatile 3, 7, METATILE_VermilionGym_Beam_Node_BottomLeft_HalfOn, 1
	setmetatile 4, 7, METATILE_VermilionGym_Beam_Node_BottomLeft_Edge_HalfOn, 1
	setmetatile 5, 7, METATILE_VermilionGym_Beam_MidBottom_HalfOn, 1
	setmetatile 6, 7, METATILE_VermilionGym_Beam_Node_BottomRight_Edge_HalfOn, 1
	setmetatile 7, 7, METATILE_VermilionGym_Beam_Node_BottomRight_HalfOn, 1
	return

VermilionCity_Gym_EventScript_SetBeamsOff::
	setmetatile 3, 6, METATILE_VermilionGym_Beam_Node_TopLeft_Off, 1
	setmetatile 4, 6, METATILE_VermilionGym_Beam_Node_TopLeft_Edge_Off, 0
	setmetatile 5, 6, METATILE_VermilionGym_Floor, 0
	setmetatile 6, 6, METATILE_VermilionGym_Beam_Node_TopRight_Edge_Off, 0
	setmetatile 7, 6, METATILE_VermilionGym_Beam_Node_TopRight_Off, 1
	setmetatile 3, 7, METATILE_VermilionGym_Beam_Node_BottomLeft_Off, 1
	setmetatile 4, 7, METATILE_VermilionGym_Beam_Node_BottomLeft_Edge_Off, 0
	setmetatile 5, 7, METATILE_VermilionGym_Floor, 0
	setmetatile 6, 7, METATILE_VermilionGym_Beam_Node_BottomRight_Edge_Off, 0
	setmetatile 7, 7, METATILE_VermilionGym_Beam_Node_BottomRight_Off, 1
	return

VermilionCity_Gym_OnTransition::
	call VermilionCity_Gym_EventScript_InitTrashCans
	end

VermilionCity_Gym_EventScript_InitTrashCans::
	goto_if_set FLAG_FOUND_BOTH_VERMILION_GYM_SWITCHES, VermilionCity_Gym_EventScript_Return
	special SetVermilionTrashCans
	copyvar VAR_TEMP_0, SWITCH1_ID
	copyvar VAR_TEMP_1, SWITCH2_ID
	return

VermilionCity_Gym_EventScript_Return::
	end

VermilionCity_Gym_EventScript_TrashCan1::
	lockall
	setvar TRASH_CAN_ID, 1
	goto VermilionCity_Gym_EventScript_TrashCan
	end

VermilionCity_Gym_EventScript_TrashCan2::
	lockall
	setvar TRASH_CAN_ID, 2
	goto VermilionCity_Gym_EventScript_TrashCan
	end

VermilionCity_Gym_EventScript_TrashCan3::
	lockall
	setvar TRASH_CAN_ID, 3
	goto VermilionCity_Gym_EventScript_TrashCan
	end

VermilionCity_Gym_EventScript_TrashCan4::
	lockall
	setvar TRASH_CAN_ID, 4
	goto VermilionCity_Gym_EventScript_TrashCan
	end

VermilionCity_Gym_EventScript_TrashCan5::
	lockall
	setvar TRASH_CAN_ID, 5
	goto VermilionCity_Gym_EventScript_TrashCan
	end

VermilionCity_Gym_EventScript_TrashCan6::
	lockall
	setvar TRASH_CAN_ID, 6
	goto VermilionCity_Gym_EventScript_TrashCan
	end

VermilionCity_Gym_EventScript_TrashCan7::
	lockall
	setvar TRASH_CAN_ID, 7
	goto VermilionCity_Gym_EventScript_TrashCan
	end

VermilionCity_Gym_EventScript_TrashCan8::
	lockall
	setvar TRASH_CAN_ID, 8
	goto VermilionCity_Gym_EventScript_TrashCan
	end

VermilionCity_Gym_EventScript_TrashCan9::
	lockall
	setvar TRASH_CAN_ID, 9
	goto VermilionCity_Gym_EventScript_TrashCan
	end

VermilionCity_Gym_EventScript_TrashCan10::
	lockall
	setvar TRASH_CAN_ID, 10
	goto VermilionCity_Gym_EventScript_TrashCan
	end

VermilionCity_Gym_EventScript_TrashCan11::
	lockall
	setvar TRASH_CAN_ID, 11
	goto VermilionCity_Gym_EventScript_TrashCan
	end

VermilionCity_Gym_EventScript_TrashCan12::
	lockall
	setvar TRASH_CAN_ID, 12
	goto VermilionCity_Gym_EventScript_TrashCan
	end

VermilionCity_Gym_EventScript_TrashCan13::
	lockall
	setvar TRASH_CAN_ID, 13
	goto VermilionCity_Gym_EventScript_TrashCan
	end

VermilionCity_Gym_EventScript_TrashCan14::
	lockall
	setvar TRASH_CAN_ID, 14
	goto VermilionCity_Gym_EventScript_TrashCan
	end

VermilionCity_Gym_EventScript_TrashCan15::
	lockall
	setvar TRASH_CAN_ID, 15
	goto VermilionCity_Gym_EventScript_TrashCan
	end

VermilionCity_Gym_EventScript_TrashCan::
	copyvar SWITCH1_ID, VAR_TEMP_0
	copyvar SWITCH2_ID, VAR_TEMP_1
	goto_if_set FLAG_FOUND_BOTH_VERMILION_GYM_SWITCHES, VermilionCity_Gym_EventScript_LocksAlreadyOpen
	goto_if_set FOUND_FIRST_SWITCH, VermilionCity_Gym_EventScript_TrySwitchTwo
	goto_if_eq SWITCH1_ID, TRASH_CAN_ID, VermilionCity_Gym_EventScript_FoundSwitchOne
	msgbox VermilionCity_Gym_Text_NopeOnlyTrashHere
	releaseall
	end

VermilionCity_Gym_EventScript_FoundSwitchOne::
	msgbox VermilionCity_Gym_Text_SwitchUnderTrashFirstLockOpened
	playse SE_PIN
	waitse
	call VermilionCity_Gym_EventScript_SetOneBeamOff
	special DrawWholeMapView
	setflag FOUND_FIRST_SWITCH
	releaseall
	end

VermilionCity_Gym_EventScript_TrySwitchTwo::
	goto_if_eq SWITCH2_ID, TRASH_CAN_ID, VermilionCity_Gym_EventScript_FoundSwitchTwo
	msgbox VermilionCity_Gym_Text_OnlyTrashLocksWereReset
	clearflag FOUND_FIRST_SWITCH
	special SetVermilionTrashCans
	copyvar VAR_TEMP_0, SWITCH1_ID
	copyvar VAR_TEMP_1, SWITCH2_ID
	call VermilionCity_Gym_EventScript_SetBeamsOn
	special DrawWholeMapView
	releaseall
	end

VermilionCity_Gym_EventScript_FoundSwitchTwo::
	msgbox VermilionCity_Gym_Text_SecondLockOpened
	closemessage
	call VermilionCity_Gym_EventScript_SetBeamsOff
	special DrawWholeMapView
	playse SE_UNLOCK
	waitse
	setflag FLAG_FOUND_BOTH_VERMILION_GYM_SWITCHES
	releaseall
	end

VermilionCity_Gym_EventScript_LocksAlreadyOpen::
	msgbox VermilionCity_Gym_Text_NopeOnlyTrashHere
	releaseall
	end

VermilionCity_Gym_EventScript_SetBeamsOn::
	setmetatile 3, 6, METATILE_VermilionGym_Beam_Node_TopLeft_On, 1
	setmetatile 4, 6, METATILE_VermilionGym_Beam_Node_TopLeft_Edge_On, 1
	setmetatile 5, 6, METATILE_VermilionGym_Beam_MidTop, 1
	setmetatile 6, 6, METATILE_VermilionGym_Beam_Node_TopRight_Edge_On, 1
	setmetatile 7, 6, METATILE_VermilionGym_Beam_Node_TopRight_On, 1
	setmetatile 3, 7, METATILE_VermilionGym_Beam_Node_BottomLeft_On, 1
	setmetatile 4, 7, METATILE_VermilionGym_Beam_Node_BottomLeft_Edge_On, 1
	setmetatile 5, 7, METATILE_VermilionGym_Beam_MidBottom, 1
	setmetatile 6, 7, METATILE_VermilionGym_Beam_Node_BottomRight_Edge_On, 1
	setmetatile 7, 7, METATILE_VermilionGym_Beam_Node_BottomRight_On, 1
	return

VermilionCity_Gym_EventScript_GymGuy::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_VERMILION_GYM, VermilionCity_Gym_EventScript_GymGuyPostVictory
	msgbox VermilionCity_Gym_Text_GymGuyAdvice
	release
	end

VermilionCity_Gym_EventScript_GymGuyPostVictory::
	msgbox VermilionCity_Gym_Text_GymGuyPostVictory
	release
	end

VermilionCity_Gym_EventScript_GymStatue::
	lockall
	goto_if_set FLAG_BADGE11_GET, VermilionCity_Gym_EventScript_GymStatuePostVictory
	msgbox VermilionCity_Gym_Text_GymStatue
	releaseall
	end

VermilionCity_Gym_EventScript_GymStatuePostVictory::
	msgbox VermilionCity_Gym_Text_GymStatuePlayerWon
	releaseall
	end

VermilionCity_Gym_EventScript_Gregory::
	trainerbattle_single TRAINER_GREGORY_HNS, VermilionGym_Text_GentlemanGregorySeen, VermilionGym_Text_GentlemanGregoryBeaten
	msgbox VermilionGym_Text_GentlemanGregoryAfter, MSGBOX_AUTOCLOSE
	end

VermilionCity_Gym_EventScript_Vincent::
	trainerbattle_single TRAINER_VINCENT_HNS, VermilionGym_Text_GuitaristVincentSeen, VermilionGym_Text_GuitaristVincentBeaten
	msgbox VermilionGym_Text_GuitaristVincentAfter, MSGBOX_AUTOCLOSE
	end

VermilionCity_Gym_EventScript_Horton::
	trainerbattle_single TRAINER_HORTON_HNS, VermilionGym_Text_JugglerHortonSeen, VermilionGym_Text_JugglerHortonBeaten
	msgbox VermilionGym_Text_JugglerHortonAfter, MSGBOX_AUTOCLOSE
	end

VermilionCity_Gym_EventScript_Surge::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_VERMILION_GYM, VermilionCity_Gym_EventScript_Surge_Defeated
	msgbox VermilionGym_Text_LtSurgeIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_LTSURGE_HNS, VermilionGym_Text_LtSurgeWinLoss
	message VermilionGym_Text_ReceivedThunderBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox VermilionGym_Text_ThunderBadgeInfo, MSGBOX_DEFAULT
	setflag FLAG_BADGE11_GET
	setflag FLAG_DEFEATED_VERMILION_GYM
	addvar VAR_NUM_BADGES, 1
	setvar VAR_0x8008, 11
	call Common_EventScript_SetGymTrainers_hns
	checkitem ITEM_TM_SHOCK_WAVE
	call_if_eq VAR_RESULT, TRUE, VermilionCity_Gym_EventScript_GiveThunderstone
	call_if_eq VAR_RESULT, FALSE, VermilionCity_Gym_EventScript_GiveTM
	clearflag FLAG_HIDE_PLANT_SURGE
	closemessage
	release
	end

VermilionCity_Gym_EventScript_GiveThunderstone::
	msgbox VermilionGym_Text_LtSurgeThunderstone, MSGBOX_DEFAULT
	giveitem ITEM_THUNDER_STONE
	return

VermilionCity_Gym_EventScript_GiveTM::
	msgbox VermilionGym_Text_LtSurge_GiveTM, MSGBOX_DEFAULT
	giveitem ITEM_TM_SHOCK_WAVE
	msgbox VermilionGym_Text_LtSurge_ExplainTM, MSGBOX_DEFAULT
	return

VermilionCity_Gym_EventScript_Surge_Defeated::
	msgbox VermilionGym_Text_LtSurgePostBattle, MSGBOX_DEFAULT
	closemessage
	release
	end

VermilionGym_Text_LtSurgeIntro:
	.string "סרג': היי, זאטוט!\p"
	.string "אני חייב לתת לך קרדיט. אולי זה לא\n"
	.string "הכי חכם לאתגר אותי, אבל זה דורש אומץ!\p"
	.string "כשזה נוגע לפוקימונים\n"
	.string "חשמליים, אני מספר אחת!\p"
	.string "אף פעם לא הפסדתי\n"
	.string "בשדה הקרב.\p"
	.string "אחשמל אותך בדיוק כמו שעשיתי\n"
	.string "לאויבים שלי במלחמה!$"

VermilionGym_Text_LtSurgeWinLoss:
	.string "סרג': אררר! אתה חזק!\p"
	.string "אוקיי, ילד. מגיע לך תג רעם!$"

VermilionGym_Text_ReceivedThunderBadge:
	.string "{PLAYER} קיבל את תג רעם.$"

VermilionGym_Text_ThunderBadgeInfo:
	.string "סרג': תג רעם מגביר את\n"
	.string "המהירות של פוקימונים.\p"
	.string "זו ההוכחה שניצחת\n"
	.string "אותי.\p"
	.string "תענוד אותו בגאווה, שמעת?$"

VermilionGym_Text_LtSurge_GiveTM:
	.string "וקח גם את המ”מ הזה. הוא שירת\n"
	.string "אותי היטב במלחמה!$"

VermilionGym_Text_LtSurge_ExplainTM:
	.string "זה גל הלם.\p"
	.string "מהלך מדויק עד כדי הלם,\n"
	.string "שפוגע בכל פעם!$"

VermilionGym_Text_LtSurgeThunderstone:
	.string "וקח גם את האבן הזאת. יש בה\n"
	.string "כוח ברק אמיתי!$"


VermilionGym_Text_LtSurgePostBattle:
	.string "סרג': היי, ילד! עדיין נלחם\n"
	.string "ומתאמץ?\p"
	.string "אני והפוקימונים שלי ממשיכים במרץ!$"

VermilionGym_Text_SurgeRematch:
	.string "SURGE: So, you're now KANTO\n"
	.string "CHAMPION!\p"
	.string "Impressive work, kid!\n"
	.string "But don't think I'm done!\p"
	.string "How about we have a go again?$"

VermilionGym_Text_SurgeRematchDefeat:
	.string "SURGE: Arrrgh! You're still just\n"
	.string "as strong!$"

VermilionGym_Text_GentlemanGregorySeen:
	.string "באת לנצח את סמל סרג'?\p"
	.string "לא אם זה תלוי בי!$"

VermilionGym_Text_GentlemanGregoryBeaten:
	.string "סליחה שאכזבתי אותך,\n"
	.string "סמל סרג', המפקד!$"

VermilionGym_Text_GentlemanGregoryAfter:
	.string "כשעוד הייתי בצבא,\n"
	.string "סמל סרג' הציל את חיי.$"

VermilionGym_Text_GuitaristVincentSeen:
	.string "סמל סרג' זיהה את הפוטנציאל שלי\n"
	.string "עם פוקימונים חשמליים.\p"
	.string "נראה לך שתנצח אותי?$"

VermilionGym_Text_GuitaristVincentBeaten:
	.string "אוו, איזה הלם!$"

VermilionGym_Text_GuitaristVincentAfter:
	.string "אמא אמרה לי לא לעזוב את\n"
	.string "העבודה הקבועה שלי,\p"
	.string "אבל מה אני אמור לעשות\n"
	.string "כשגם שם אני לא מצליח?$"

VermilionGym_Text_JugglerHortonSeen:
	.string "אני הולך להפיל אותך!\n"
	.string "תתכונן לקבל הלם!$"

VermilionGym_Text_JugglerHortonBeaten:
	.string "גוואאה! הכריעו אותי…$"

VermilionGym_Text_JugglerHortonAfter:
	.string "אל תתלהב יותר מדי מזה\n"
	.string "שניצחת אותי…\p"
	.string "סמל סרג' קשוח.$"

VermilionCity_Gym_Text_GymGuyAdvice::
    .string "יו!\n"
    .string "אלוף לעתיד!\p"
    .string "לסמל סרג' יש כינוי.\p"
    .string "אנשים קוראים לו\n"
    .string "האמריקאי החשמלי!\p"
    .string "הוא מומחה לפוקימונים\n"
    .string "חשמליים.\p"
    .string "פוקימונים מסוג תעופה/מים\n"
    .string "חלשים מול סוג חשמל.\p"
    .string "כדאי להיזהר גם משיתוק.\p"
    .string "סמל סרג' זהיר מאוד.\p"
    .string "הוא נעל את עצמו בפנים, אז לא\n"
    .string "יהיה קל להגיע אליו.$"

VermilionCity_Gym_Text_GymGuyPostVictory::
	.string "וואו! זה היה קרב מחשמל!\p"
	.string "זה ממש הלחיץ אותי.$"

VermilionCity_Gym_Text_GymStatue::
    .string "מכון הפוקימון של ורמיליון\n"
    .string "מנהיג: סמל סרג'\p"
    .string "מאמנים מנצחים:\n"
    .string "בלו, רד$"


VermilionCity_Gym_Text_GymStatuePlayerWon::
    .string "מכון הפוקימון של ורמיליון\n"
    .string "מנהיג: סמל סרג'\p"
    .string "מאמנים מנצחים:\n"
    .string "בלו, רד, {PLAYER}$"

VermilionCity_Gym_Text_NopeOnlyTrashHere::
    .string "כלום!\n"
    .string "יש כאן רק זבל.$"

VermilionCity_Gym_Text_SwitchUnderTrashFirstLockOpened::
    .string "היי! יש מתג מתחת לזבל!\n"
    .string "נדליק אותו!\p"
    .string "המנעול החשמלי הראשון נפתח!$"

VermilionCity_Gym_Text_SecondLockOpened::
    .string "המנעול החשמלי השני נפתח!\n"
    .string "הדלת הממונעת נפתחה!$"

VermilionCity_Gym_Text_OnlyTrashLocksWereReset::
    .string "כלום!\n"
    .string "יש כאן רק זבל.\p"
    .string "היי!\n"
    .string "המנעולים החשמליים התאפסו!$"

