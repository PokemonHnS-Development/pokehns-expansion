RocketHideout_B3F_hns_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, RocketHideout_B3F_OnFrame
	map_script MAP_SCRIPT_ON_LOAD, RocketHideout_B3F_OnLoad
	.byte 0

RocketHideout_B3F_OnLoad::
	call_if_set FLAG_HIDE_ROCKETHIDEOUT3_GATE, RocketHideout_B3F_HideGate
	call_if_eq VAR_ROCKET_PASSWORD, 2, RocketHideout_B3F_HidePetrel
	end
	
RocketHideout_B3F_HideGate::
	setmetatile 11, 11, 0x378, FALSE
	setmetatile 11, 12, 0x380, FALSE
	setmetatile 12, 11, 0x379, FALSE
	setmetatile 12, 12, 0x379, FALSE
	setmetatile 13, 11, 0x379, FALSE
	setmetatile 13, 12, 0x379, FALSE
	return
RocketHideout_B3F_HidePetrel::
	setflag FLAG_HIDE_ROCKETHIDEOUT3_PETREL
	clearflag FLAG_HIDE_ROCKETHIDEOUT3_GIOVANNI
	return

RocketHideout_B3F_OnFrame::
	map_script_2 VAR_MAHOGANY_TOWN_STATE, 6, RocketHideout_B3F_EventScript_LancePassword
	.2byte 0

RocketHideout_B3F_EventScript_LancePassword::
	lock
	delay 55
	playse SE_PIN
	applymovement LOCALID_ROCKETHIDEOUT3_LANCE, Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_ROCKETHIDEOUT3_LANCE
	applymovement LOCALID_ROCKETHIDEOUT3_LANCE, Common_Movement_WalkRight1
	msgbox RocketHideout_B3F_Text_LanceGetPassword, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ROCKETHIDEOUT3_LANCE, RocketHideout_B3F_Movement_LanceLeave
	applymovement LOCALID_ROCKETHIDEOUT3_DRAGONITE, RocketHideout_B3F_Movement_DragoniteLeave
	waitmovement LOCALID_ROCKETHIDEOUT3_LANCE
	waitmovement LOCALID_ROCKETHIDEOUT3_DRAGONITE
	setflag FLAG_HIDE_ROCKETHIDEOUT3_LANCE_DRAGONITE
	removeobject LOCALID_ROCKETHIDEOUT3_DRAGONITE
	removeobject LOCALID_ROCKETHIDEOUT3_LANCE
	setvar VAR_MAHOGANY_TOWN_STATE, 7
	release
	end

RocketHideout_B3F_Movement_LanceLeave:
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	delay_2
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

RocketHideout_B3F_Movement_DragoniteLeave:
	delay_16
	delay_16
	delay_16
	delay_16
	delay_8
	delay_8
	delay_8
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

RocketHideout_B3F_Text_LanceGetPassword:
    .string "לאנס: צריך שתי סיסמאות\n"
    .string "כדי להיכנס למגורי הבוס.\p"
    .string "את הסיסמאות האלה יודעים\n"
    .string "רק כמה אנשי רוקט.\p"
    .string "איש הרוקט ההוא היה נחמד מאוד\n"
    .string "וסיפר לי את זה.\p"
    .string "{PLAYER}, הולכים להשיג\n"
    .string "את הסיסמאות.$"

RocketHideout_B3F_EventScript_RocketKO::
	lock
	faceplayer
	msgbox RocketHideout_B3F_Text_B3FRocket, MSGBOX_DEFAULT
	release
	end

RocketHideout_B3F_Text_B3FRocket:
    .string "אררגג… הבחור עם הגלימה\n"
    .string "חזק בטירוף…$"


RocketHideout_B3F_Trigger_MurkrowStairs::
	lock
	applymovement LOCALID_ROCKETHIDEOUT3_MURKROWSTAIRS, RocketHideout_B3F_Movement_MurkrowStairs1
	waitmovement 0
	playmoncry SPECIES_MURKROW, CRY_MODE_NORMAL
	msgbox RocketHideout_B3F_Text_MurkrowSpeak1, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ROCKETHIDEOUT3_MURKROWSTAIRS, RocketHideout_B3F_Movement_MurkrowStairs2
	waitmovement 0
	setflag FLAG_HIDE_ROCKETHIDEOUT3_MURKROWSTAIRS
	removeobject LOCALID_ROCKETHIDEOUT3_MURKROWSTAIRS
	clearflag FLAG_HIDE_ROCKETHIDEOUT2_MURKROWGATE
	setvar VAR_MAHOGANY_TOWN_STATE, 11
	release
	end

RocketHideout_B3F_Movement_MurkrowStairs1:
	jump_in_place_right
	jump_in_place_right
	step_end

RocketHideout_B3F_Movement_MurkrowStairs2:
	jump_in_place_right
	walk_fast_down
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end

RocketHideout_B3F_Trigger_Silver::
	lock
	clearflag FLAG_HIDE_ROCKETHIDEOUT3_SILVER
	addobject LOCALID_ROCKETHIDEOUT3_SILVER
	playbgm MUS_HG_ENCOUNTER_RIVAL, FALSE
	applymovement LOCALID_ROCKETHIDEOUT3_SILVER, RocketHideout_B3F_Movement_SilverEnter
	waitmovement 0
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	msgbox RocketHideout_B3F_Text_Rival, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ROCKETHIDEOUT3_SILVER, RocketHideout_B3F_Movement_SilverLeave
	waitmovement 0
	setflag FLAG_HIDE_ROCKETHIDEOUT3_SILVER
	removeobject LOCALID_ROCKETHIDEOUT3_SILVER
	setvar VAR_MAHOGANY_TOWN_STATE, 8
	fadedefaultbgm
	release
	end

RocketHideout_B3F_Movement_SilverEnter:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

RocketHideout_B3F_Movement_SilverLeave:
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
	step_end

RocketHideout_B3F_EventScript_Door::
	lock
	goto_if_set FLAG_HIDE_ROCKETHIDEOUT3_GATE, RocketHideout_B3F_EventScript_DoorIsOpen
	goto_if_eq VAR_ROCKET_PASSWORD, 2, RocketHideout_B3F_EventScript_OpenDoor
	msgbox RocketHideout_B3F_Text_B3FLockedDoorNeedsPassword, MSGBOX_DEFAULT
	closemessage
	release
	end

RocketHideout_B3F_EventScript_OpenDoor::
	msgbox RocketHideout_B3F_Text_B3FLockedDoorOpenSesame, MSGBOX_DEFAULT
	closemessage
	playse SE_CLICK
	setmetatile 11, 11, 0x378, FALSE
	setmetatile 11, 12, 0x380, FALSE
	setmetatile 12, 11, 0x379, FALSE
	setmetatile 12, 12, 0x379, FALSE
	setmetatile 13, 11, 0x379, FALSE
	setmetatile 13, 12, 0x379, FALSE
	special DrawWholeMapView
	setflag FLAG_HIDE_ROCKETHIDEOUT3_GATE
	release
	end

RocketHideout_B3F_EventScript_DoorIsOpen::
	end

RocketHideout_B3F_EventScript_GruntF5::
	trainerbattle_single TRAINER_GRUNT_29_HNS, RocketHideout_B3F_Text_GruntF5Seen, RocketHideout_B3F_Text_GruntF5Beaten
	msgbox RocketHideout_B3F_Text_GruntF5After, MSGBOX_NPC
	goto_if_unset FLAG_GOT_PASSWORD_FROM_GRUNTF, RocketHideout_B3F_EventScript_IncrementPasswordGruntF
	end

RocketHideout_B3F_EventScript_IncrementPasswordGruntF::
	addvar VAR_ROCKET_PASSWORD, 1
	setflag FLAG_GOT_PASSWORD_FROM_GRUNTF
	end

RocketHideout_B3F_EventScript_Eto::
	trainerbattle_single TRAINER_ETO_2_HNS, RocketHideout_B3F_Text_GruntM28Seen, RocketHideout_B3F_Text_GruntM28Beaten
	msgbox RocketHideout_B3F_Text_GruntM28After, MSGBOX_NPC
	goto_if_unset FLAG_GOT_PASSWORD_FROM_ETO, RocketHideout_B3F_EventScript_IncrementPasswordEto
	end

RocketHideout_B3F_EventScript_IncrementPasswordEto::
	addvar VAR_ROCKET_PASSWORD, 1
	setflag FLAG_GOT_PASSWORD_FROM_ETO
	end

RocketHideout_B3F_EventScript_Ross::
	trainerbattle_single TRAINER_ROSS_HNS, RocketHideout_B3F_Text_ScientistRossSeen, RocketHideout_B3F_Text_ScientistRossBeaten
	msgbox RocketHideout_B3F_Text_ScientistRossAfter, MSGBOX_AUTOCLOSE
	end

RocketHideout_B3F_EventScript_Mitch::
	trainerbattle_single TRAINER_MITCH_HNS, RocketHideout_B3F_Text_ScientistMitchSeen, RocketHideout_B3F_Text_ScientistMitchBeaten
	msgbox RocketHideout_B3F_Text_ScientistMitchAfter, MSGBOX_AUTOCLOSE
	end

RocketHideout_B3F_EventScript_Item_IceHeal::
	finditem ITEM_ICE_HEAL
	end

RocketHideout_B3F_EventScript_Item_Protein::
	finditem ITEM_PROTEIN
	end

RocketHideout_B3F_EventScript_Item_FullHeal::
	finditem ITEM_FULL_HEAL
	end

RocketHideout_B3F_EventScript_Item_GuardSpec::
	finditem ITEM_GUARD_SPEC
	end

RocketHideout_B3F_EventScript_Item_HyperPotion::
	finditem ITEM_HYPER_POTION
	end

RocketHideout_B3F_Text_B3FLockedDoorNeedsPassword:
    .string "הדלת סגורה…\p"
    .string "צריך שתי סיסמאות כדי לפתוח אותה.$"

RocketHideout_B3F_Text_B3FLockedDoorOpenSesame:
    .string "הדלת סגורה…\p"
    .string "{PLAYER} הקיש את שתי הסיסמאות.\p"
    .string "הדלת נפתחה!$"

RocketHideout_B3F_Text_Rival:
    .string "…\p"
    .string "לא אמרתי לך שאני הולך\n"
    .string "להשמיד את צוות רוקט?\p"
    .string "…תגיד לי, מי היה הבחור עם\n"
    .string "הגלימה שהשתמש בפוקימוני דרקון?\p"
    .string "לפוקימונים שלי לא היה שום סיכוי.\p"
    .string "מה שהוא אמר מטריד\n"
    .string "אותי…\p"
    .string "הוא אמר לי שאני לא אוהב את\n"
    .string "הפוקימונים שלי ולא סומך עליהם מספיק.\p"
    .string "זו לא אשמתי שהקבוצה שלי\n"
    .string "כל כך חסרת תועלת.\p"
    .string "אני זועם שהפסדתי\n"
    .string "ליפה נפש כמוהו.\p"
    .string "אבל זה גורם לי לפקפק בעצמי.\p"
    .string "אני עושה משהו\n"
    .string "לא נכון?\p"
    .string "יכול להיות שהאהבה היא שהפכה\n"
    .string "את הקבוצה שלו לחזקה כל כך?$"

@=======[PETREL]==============================================================================================================================

RocketHideout_B3F_EventScript_Giovanni::
	lock
	faceplayer
	msgbox RocketHideout_B3F_Text_PetrelIntro, MSGBOX_DEFAULT
	playse SE_PIN
	applymovement LOCALID_ROCKETHIDEOUT3_GIOVANNI, Common_Movement_QuestionMark
	delay 55
	waitmovement LOCALID_ROCKETHIDEOUT3_GIOVANNI
	msgbox RocketHideout_B3F_Text_PetrelDisbelief, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ROCKETHIDEOUT3_GIOVANNI, RocketHideout_B3F_Movement_Spin
	waitmovement 0
	setflag FLAG_HIDE_ROCKETHIDEOUT3_GIOVANNI
	removeobject LOCALID_ROCKETHIDEOUT3_GIOVANNI
	clearflag FLAG_HIDE_ROCKETHIDEOUT3_PETREL
	addobject LOCALID_ROCKETHIDEOUT3_PETREL
	applymovement LOCALID_ROCKETHIDEOUT3_PETREL, RocketHideout_B3F_Movement_Spin2
	waitmovement 0
	call_if_eq VAR_FACING, DIR_EAST, RocketHideout_B3F_EventScript_FacingEast
	call_if_eq VAR_FACING, DIR_WEST, RocketHideout_B3F_EventScript_FacingWest
	msgbox RocketHideout_B3F_Text_PetrelReveal, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_PETREL_1_HNS, RocketHideout_B3F_Text_PetrelBeaten
	msgbox RocketHideout_B3F_Text_PetrelAfterBattle, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_FACING, DIR_EAST, RocketHideout_B3F_EventScript_LeaveEast
	call_if_eq VAR_FACING, DIR_WEST, RocketHideout_B3F_EventScript_LeaveWest
	call_if_eq VAR_FACING, DIR_NORTH, RocketHideout_B3F_EventScript_LeaveEast
	setflag FLAG_HIDE_ROCKETHIDEOUT3_PETREL
	playse SE_EXIT
	removeobject LOCALID_ROCKETHIDEOUT3_PETREL
	
	applymovement LOCALID_ROCKETHIDEOUT3_MURKROW, RocketHideout_B3F_Movement_Murkrow1

	delay 120

	call_if_eq VAR_FACING, DIR_EAST, RocketHideout_B3F_EventScript_FacingEastMurkrow
	call_if_eq VAR_FACING, DIR_WEST, RocketHideout_B3F_EventScript_FacingWestMurkrow

	turnobject OBJ_EVENT_ID_PLAYER, DIR_SOUTH
	waitmovement LOCALID_ROCKETHIDEOUT3_MURKROW
	playmoncry SPECIES_MURKROW, CRY_MODE_NORMAL
	msgbox RocketHideout_B3F_Text_MurkrowSpeak1, MSGBOX_DEFAULT
	msgbox RocketHideout_B3F_Text_MurkrowMimic, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ROCKETHIDEOUT3_MURKROW, RocketHideout_B3F_Movement_Murkrow2
	waitmovement LOCALID_ROCKETHIDEOUT3_MURKROW

	setflag FLAG_HIDE_ROCKETHIDEOUT3_MURKROW
	playse SE_EXIT
	removeobject LOCALID_ROCKETHIDEOUT3_MURKROW
	clearflag FLAG_HIDE_ROCKETHIDEOUT2_MURKROWSTAIRS
	setflag FLAG_HIDE_ROCKETHIDEOUT2_MURKROWGATE
	setflag FLAG_HIDE_ROCKETHIDEOUT3_MURKROWSTAIRS
	setflag FLAG_HIDE_ROCKETHIDEOUT2_ARIANA_AND_GRUNT
	setvar VAR_ROCKET_PASSWORD, 3
	setvar VAR_MAHOGANY_TOWN_STATE, 9
	release
	end

RocketHideout_B3F_EventScript_FacingEastMurkrow::
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkRight1
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkDown1
	waitmovement OBJ_EVENT_ID_PLAYER
	return

RocketHideout_B3F_EventScript_FacingWestMurkrow::
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkLeft1
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkDown1
	waitmovement OBJ_EVENT_ID_PLAYER
	return

RocketHideout_B3F_EventScript_FacingEast::
	turnobject LOCALID_ROCKETHIDEOUT3_PETREL, DIR_WEST
	return

RocketHideout_B3F_EventScript_FacingWest::
	turnobject LOCALID_ROCKETHIDEOUT3_PETREL, DIR_EAST
	return

RocketHideout_B3F_EventScript_FacingNorth::
	turnobject LOCALID_ROCKETHIDEOUT3_PETREL, DIR_SOUTH
	return

RocketHideout_B3F_EventScript_LeaveEast::
	applymovement LOCALID_ROCKETHIDEOUT3_PETREL, RocketHideout_B3F_Movement_LeaveEast
	waitmovement 0
	return

RocketHideout_B3F_EventScript_LeaveWest::
	applymovement LOCALID_ROCKETHIDEOUT3_PETREL, RocketHideout_B3F_Movement_LeaveWest
	waitmovement 0
	return

RocketHideout_B3F_Movement_Murkrow1:
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	jump_in_place_right
	jump_in_place_left
	jump_in_place_down
	jump_in_place_up
	jump_in_place_up
	jump_in_place_up
	jump_in_place_up
	step_end

RocketHideout_B3F_Movement_Murkrow2:
	jump_in_place_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
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
	walk_faster_right
	walk_faster_right
	step_end

RocketHideout_B3F_Movement_LeaveEast:
	lock_facing_direction
	walk_slow_right
	unlock_facing_direction
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
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
	walk_fast_right
	walk_fast_right
	step_end
RocketHideout_B3F_Movement_LeaveWest:
	lock_facing_direction
	walk_slow_left
	walk_slow_left
	unlock_facing_direction
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
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
	walk_fast_right
	walk_fast_right
	step_end

RocketHideout_B3F_Movement_Spin:
	face_right
	delay_8
	face_up
	delay_8
	face_left
	delay_8
	face_down
	delay_8
	face_right
	delay_4
	face_up
	delay_4
	face_left
	delay_4
	face_down
	delay_4
	face_right
	delay_2
	face_up
	delay_2
	face_left
	delay_2
	face_down
	step_end

RocketHideout_B3F_Movement_Spin2:
	face_right
	delay_2
	face_up
	delay_2
	face_left
	delay_2
	face_down
	step_end

RocketHideout_B3F_Text_PetrelIntro:
    .string "מוהאהאהא, חיכינו לך.\n"
    .string "אז אתה {PLAYER}…\p"
    .string "אני? אתה לא יודע מי אני?\n"
    .string "זה אני, ג'ובאני.\p"
    .string "ג'ובאני המלכותי בכבודו ובעצמו!\n"
    .string "וואהאהאהא!$"

RocketHideout_B3F_Text_PetrelDisbelief:
    .string "…מה? אני לא נשמע\n"
    .string "בכלל כמו ג'ובאני?\p"
    .string "אני אפילו לא נראה כמו ג'ובאני?\n"
    .string "איך ייתכן? התאמצתי כל כך לחקות אותו!$"

RocketHideout_B3F_Text_PetrelReveal:
    .string "פטרל: אני מנהל בצוות רוקט!\p"
    .string "בטח אתה מנסה להתגנב\n"
    .string "לחדר משדר הרדיו.\p"
    .string "ובכן, זה לא יקרה. החדר\n"
    .string "מוגן בסיסמה מיוחדת.\p"
    .string "הסיסמה היא ”יחי ג'ובאני”.\n"
    .string "מופתע לשמוע את זה ממני?\p"
    .string "אבל לדעת את הסיסמה\n"
    .string "לא יעזור לך.\p"
    .string "הדלת לא תיפתח אם לא אגיד\n"
    .string "את הסיסמה. היא מגיבה רק לקול שלי.$"

RocketHideout_B3F_Text_PetrelBeaten:
    .string "אני… לא הצלחתי לעשות כלום…\p"
    .string "ג'ובאני, בבקשה סלח לי…$"

RocketHideout_B3F_Text_PetrelAfterBattle:
    .string "פטרל: מאז שפירק את צוות רוקט\n"
    .string "לפני שלוש שנים, ג'ובאני שלנו נעדר.\p"
    .string "אבל אנחנו בטוחים שהוא מחכה\n"
    .string "לרגע הנכון לתחייה שלנו… וואהאהאהא!\p"
    .string "ההפסד לך לא משנה את העובדה שאתה\n"
    .string "לא יכול להיכנס לחדר משדר הרדיו!\p"
    .string "צריך את הקול שלי כדי לפתוח אותו!$"

RocketHideout_B3F_EventScript_Murkrow::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_MURKROW, CRY_MODE_NORMAL
	msgbox RocketHideout_B3F_Text_MurkrowSpeak1, MSGBOX_DEFAULT
	waitmoncry
	release
	end

RocketHideout_B3F_Text_MurkrowSpeak1:
    .string "מרקרואו: יחי ג'ובאני.$"

RocketHideout_B3F_Text_MurkrowMimic:
    .string "מרקרואו מחקה\n"
    .string "את הקול של פטרל!\p"
    .string "אולי אפשר…!?$"

RocketHideout_B3F_Text_Murkrow:
    .string "מרקרואו: הסיסמה היא…\p"
    .string "יחי ג'ובאני.$"

RocketHideout_B3F_Text_GruntF5Seen:
    .string "אם אני יודעת את הסיסמה?\p"
    .string "אולי.\p"
    .string "אבל שום חלשלוש לא יקבל\n"
    .string "אותה ממני!$"

RocketHideout_B3F_Text_GruntF5Beaten:
    .string "טוב. די. אני אגיד לך.$"

RocketHideout_B3F_Text_GruntF5After:
    .string "הסיסמה לחדר של הבוס\n"
    .string "היא זנב סלופוק.\p"
    .string "אבל היא חסרת תועלת\n"
    .string "בלי שתי הסיסמאות.$"

RocketHideout_B3F_Text_GruntM28Seen:
    .string "חה-חה-חה!\p"
    .string "אני זוכר אותך מהבאר!\p"
    .string "אתה שוב מאתגר אותי?\p"
    .string "הא! אתה משוגע, אבל יש לך\n"
    .string "אומץ!\p"
    .string "אני מזהיר אותך, השתפרתי!\p"
    .string "אם תנצח אותי, אגיד לך\n"
    .string "סיסמה לחדר של הבוס!$"

RocketHideout_B3F_Text_GruntM28Beaten:
    .string "חה-חה-חה! אתה טוב!$"

RocketHideout_B3F_Text_GruntM28After:
    .string "חה-חה-חה!\p"
    .string "הסיסמה לחדר של הבוס…\p"
    .string "אה…, נדמה לי שזה זנב רטיקייט.$"

RocketHideout_B3F_Text_ScientistRossSeen:
    .string "פעם עבדתי בחברת סילף, אבל עכשיו\n"
    .string "אני מנהל מחקר בשביל צוות רוקט.\p"
    .string "ילד חטטן כמוך\n"
    .string "צריך לקבל עונש.$"

RocketHideout_B3F_Text_ScientistRossBeaten:
    .string "טעות טקטית קטנה עלתה לי ביוקר…$"

RocketHideout_B3F_Text_ScientistRossAfter:
    .string "אות רדיו שמשגע\n"
    .string "פוקימונים…\p"
    .string "הניסוי שלי הוא הצלחה\n"
    .string "מוחלטת.\p"
    .string "הקידום שלי מובטח. ההפסד הזה\n"
    .string "לא אומר שום דבר.$"

RocketHideout_B3F_Text_ScientistMitchSeen:
    .string "לא אכפת לי שהניסוי שלנו\n"
    .string "פוגע בפוקימונים.$"

RocketHideout_B3F_Text_ScientistMitchBeaten:
    .string "הצד החזק שלי הוא חשיבה,\n"
    .string "לא קרבות.$"

RocketHideout_B3F_Text_ScientistMitchAfter:
    .string "אם נגביר את העוצמה של אות הרדיו\n"
    .string "שלנו כדי לשדר בכל הארץ…\p"
    .string "עצם המחשבה מרגשת אותי!$"
