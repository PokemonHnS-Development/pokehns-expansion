EcruteakCity_SageOffice1_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, EcruteakCity_SageOffice1_OnTransition
	.byte 0

EcruteakCity_SageOffice1_OnTransition::
	goto_if_set FLAG_HIDE_TINTOWER_GUARD, EcruteakCity_SageOffice1_EventScript_SageAside
	end

EcruteakCity_SageOffice1_EventScript_SageAside::
	setobjectxyperm LOCALID_SAGEOFFICE_SAGE, 15, 2
	end

EcruteakCity_SageOffice1_EventScript_Sign::
	msgbox EcruteakCity_SageOffice1_Text_Sign, MSGBOX_SIGN
	end

EcruteakCity_SageOffice1_Text_Sign:
	.string "פעמון הבדיל מצלצל בבהירות\n"
	.string "למי שחוסה תחת כנף המגדל.$"

EcruteakCity_SageOffice2_EventScript_SageA::
	lock
	faceplayer
	goto_if_set FLAG_HIDE_TINTOWER_GUARD, EcruteakCity_SageOffice2_EventScript_SageA4
	checkitem ITEM_CLEAR_BELL
	goto_if_eq VAR_RESULT, TRUE, EcruteakCity_SageOffice2_EventScript_SageA2
	msgbox EcruteakTinTowerEntrance_Text_SageNoBadge, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_SageOffice2_EventScript_SageA2::
	msgbox EcruteakTinTowerEntrance_Text_SageHearsClearBell1, MSGBOX_DEFAULT
	waitmessage
	playse SE_M_PETAL_DANCE
	waitse
	playse SE_PIN
	applymovement LOCALID_SAGEOFFICE_SAGE, Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_SAGEOFFICE_SAGE
	msgbox EcruteakTinTowerEntrance_Text_SageHearsClearBell2, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SAGEOFFICE_SAGE, EcruteakCity_SageOffice2_Movement_StandAside
	waitmovement 0
	setobjectxyperm LOCALID_SAGEOFFICE_SAGE, 15, 2
	setflag FLAG_HIDE_TINTOWER_GUARD
	release
	end

EcruteakCity_SageOffice2_EventScript_SageA3::
	msgbox EcruteakTinTowerEntrance_Text_SagePleaseDoGoOn, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_SageOffice2_EventScript_SageA4::
	msgbox EcruteakTinTowerEntrance_Text_SageDone, MSGBOX_DEFAULT
	closemessage
	release
	end
	
EcruteakCity_SageOffice2_EventScript_SageB::
	lock
	faceplayer
	goto_if_eq VAR_ECRUTEAK_CITY_STATE, 10, EcruteakCity_SageOffice2_EventScript_B2
	goto_if_eq VAR_ECRUTEAK_CITY_STATE, 11, EcruteakCity_SageOffice2_EventScript_B2
	msgbox EcruteakTinTowerEntrance_Text_WanderingSage, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_SageOffice2_EventScript_B2::
	msgbox EcruteakTinTowerEntrance_Text_WanderingSageClearBell, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_SageOffice2_EventScript_SageC::
	lock
	faceplayer
	msgbox EcruteakTinTowerEntrance_Text_Gramps, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_SageOffice2_Movement_StandAside:
	walk_left
	face_down
	step_end

EcruteakTinTowerEntrance_Text_SageNoBadge:
	.string "הכניסה למגדל הבדיל אסורה\n"
	.string "על מי שאינו ראוי.\p"
	.string "מצטער, אבל עליך לעזוב.$"

EcruteakTinTowerEntrance_Text_SageWithBadge:
	.string "TIN TOWER is off limits to anyone\n"
	.string "without ECRUTEAK GYM's BADGE.\p"
	.string "Ah!\p"
	.string "ECRUTEAK's GYM BADGE! Please, go\n"
	.string "right through.$"

EcruteakTinTowerEntrance_Text_SageNoClearBell:
	.string "A momentous event has occurred.\p"
	.string "I beg your pardon, but I must ask\n"
	.string "you to leave.\p"
	.string "…What soothes the soul…\p"
	.string "The WISE TRIO say things that are\n"
	.string "so very difficult to understand…$"

EcruteakTinTowerEntrance_Text_SageHearsClearBell1:
	.string "התרחש אירוע היסטורי.\p"
	.string "אני מתנצל, אבל עליי לבקש\n"
	.string "ממך לעזוב.\p"
	.string "…………$"
EcruteakTinTowerEntrance_Text_SageHearsClearBell2:
	.string "אה!\p"
	.string "הצליל של הפעמון הצלול!\p"
	.string "זה… זה נשגב!\p"
	.string "מעולם לא שמעתי צליל\n"
	.string "כל כך יפה!\p"
	.string "צלצול הפעמון מעיד על\n"
	.string "נשמתו של מי שנושא אותו.\p"
	.string "אתה…\p"
	.string "ייתכן שתצליח לעבור את\n"
	.string "מגדל הבדיל.\p"
	.string "בבקשה, המשך פנימה.$"

EcruteakTinTowerEntrance_Text_SagePleaseDoGoOn:
	.string "Please, do go on.$"

EcruteakTinTowerEntrance_Text_SageDone:
	.string "צלצול הפעמון מעיד על\n"
	.string "נשמתו של מי שנושא אותו.\p"
	.string "אתה…\n"
	.string "באמת ראוי.$"

EcruteakTinTowerEntrance_Text_WanderingSage:
	.string "מגדל הבדיל שלפנינו הוא מגדל בן\n"
	.string "תשע קומות, בעל יופי אלוהי.\p"
	.string "הוא מרגיע את נפשו של כל\n"
	.string "מי שרואה אותו.$"

EcruteakTinTowerEntrance_Text_WanderingSageClearBell:
	.string "מגדל הבדיל רעד! כנראה שפוקימון\n"
	.string "חזר לפסגה!$"

EcruteakTinTowerEntrance_Text_Gramps:
	.string "שני מגדלים… שני פוקימונים…\p"
	.string "אבל כשאחד מהם נשרף,\n"
	.string "שני הפוקימונים עפו ולא שבו עוד.$"
