GoldenrodCity_UndergroundSwitches_hns_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, GoldenrodUnderground1_OnLoad
	.byte 0

GoldenrodUnderground1_OnLoad::
	setvar VAR_TEMP_0, 0
	call_if_set FLAG_COMPLETED_SWITCHES, GoldenrodUnderground1_ClearTheWay
	clearflag FLAG_GOLDENROD_SWITCH_1
	clearflag FLAG_GOLDENROD_SWITCH_2
	clearflag FLAG_GOLDENROD_SWITCH_3
	clearflag FLAG_GOLDENROD_SWITCH_ORDER
	end

GoldenrodUnderground1_ClearTheWay::
	call GoldenrodCity_UndergroundSwitches_EventScript_CreateWall1
	call GoldenrodCity_UndergroundSwitches_EventScript_RemoveWall2
	call GoldenrodCity_UndergroundSwitches_EventScript_RemoveWall3
	call GoldenrodCity_UndergroundSwitches_EventScript_CreateWall4
	call GoldenrodCity_UndergroundSwitches_EventScript_RemoveWall5
	call GoldenrodCity_UndergroundSwitches_EventScript_CreateWall6
	return

@ Added an antisoft lock, using wall panels
@ Added more anti softlock 

GoldenrodCity_UndergroundSwitches_InDoorAntiLock::
	lock
	msgbox GoldenrodCity_UndergroundSwitches_EventScript_AntiSoftLock_Text, MSGBOX_YESNO
	closemessage
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_NoOp
	warp MAP_GOLDENROD_CITY_UNDERGROUND_SWITCHES_HNS, 2, 25, 5
	waitstate
	release
	end

GoldenrodCity_UndergroundSwitches_InDoorAntiLock2::
	lock
	setvar VAR_TEMP_0, 1
	release
	end

GoldenrodCity_UndergroundSwitches_EventScript_AntiSoftLock::
	lock
	msgbox GoldenrodCity_UndergroundSwitches_EventScript_AntiSoftLock_Text, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE, GoldenrodCity_UndergroundSwitches_EventScript_AntiSoftLock_TP
	closemessage
	release
	end

GoldenrodCity_UndergroundSwitches_EventScript_AntiSoftLock_TP::
	warp MAP_GOLDENROD_CITY_UNDERGROUND_SWITCHES_HNS, 2, 25, 5
	waitstate
	release
	end

GoldenrodCity_UndergroundSwitches_EventScript_AntiSoftLock_Text::
	.string "ייתכן שנתקעת.\p"
	.string "לחזור לכניסה\n"
	.string "ולאפס את המתגים?$"

@ 3->2->1

@==============================================================================================================================================
GoldenrodCity_UndergroundSwitches_EventScript_Panel1::
	lock
	goto_if_unset FLAG_GOLDENROD_SWITCH_1, GoldenrodCity_UndergroundSwitches_EventScript_Panel1Activate @lock all
	clearflag FLAG_GOLDENROD_SWITCH_1
	playse SE_BANG
	msgbox GoldenrodUnderground_Text_Switch1Off, MSGBOX_DEFAULT
	closemessage
	call GoldenrodCity_UndergroundSwitches_EventScript_CreateWall1
	call GoldenrodCity_UndergroundSwitches_EventScript_CreateWall2
	call GoldenrodCity_UndergroundSwitches_EventScript_CreateWall3
	call GoldenrodCity_UndergroundSwitches_EventScript_CreateWall4
	call GoldenrodCity_UndergroundSwitches_EventScript_CreateWall5
	call GoldenrodCity_UndergroundSwitches_EventScript_CreateWall6
	special DrawWholeMapView
	waitse
	release
	end

GoldenrodCity_UndergroundSwitches_EventScript_Panel1Activate:: @unlock basic
	setflag FLAG_GOLDENROD_SWITCH_1
	goto_if_set FLAG_GOLDENROD_SWITCH_ORDER, GoldenrodCity_UndergroundSwitches_EventScript_Panel1ActivateCorrect
	clearflag FLAG_GOLDENROD_SWITCH_ORDER
	playse SE_BANG
	msgbox GoldenrodUnderground_Text_Switch1, MSGBOX_DEFAULT
	closemessage
	call GoldenrodCity_UndergroundSwitches_EventScript_RemoveWall1
	call GoldenrodCity_UndergroundSwitches_EventScript_RemoveWall2
	call GoldenrodCity_UndergroundSwitches_EventScript_RemoveWall3
	call GoldenrodCity_UndergroundSwitches_EventScript_CreateWall4	
	call GoldenrodCity_UndergroundSwitches_EventScript_CreateWall5
	call GoldenrodCity_UndergroundSwitches_EventScript_CreateWall6	
	special DrawWholeMapView
	waitse
	release
	end


GoldenrodCity_UndergroundSwitches_EventScript_Panel1ActivateCorrect:: @unlock the right path
	playse SE_CLICK
	setflag FLAG_COMPLETED_SWITCHES
	msgbox GoldenrodUnderground_Text_Switch1, MSGBOX_DEFAULT
	closemessage
	call GoldenrodCity_UndergroundSwitches_EventScript_CreateWall1
	call GoldenrodCity_UndergroundSwitches_EventScript_RemoveWall2
	call GoldenrodCity_UndergroundSwitches_EventScript_RemoveWall3
	call GoldenrodCity_UndergroundSwitches_EventScript_CreateWall4
	call GoldenrodCity_UndergroundSwitches_EventScript_RemoveWall5
	call GoldenrodCity_UndergroundSwitches_EventScript_CreateWall6
	special DrawWholeMapView
	waitse
	release
	end
@==============================================================================================================================================
GoldenrodCity_UndergroundSwitches_EventScript_Panel2:: @lock all
	lock
	goto_if_unset FLAG_GOLDENROD_SWITCH_2, GoldenrodCity_UndergroundSwitches_EventScript_Panel2Activate
	clearflag FLAG_GOLDENROD_SWITCH_2
	clearflag FLAG_GOLDENROD_SWITCH_ORDER
	playse SE_BANG
	msgbox GoldenrodUnderground_Text_Switch2Off, MSGBOX_DEFAULT
	closemessage
	call GoldenrodCity_UndergroundSwitches_EventScript_CreateWall1
	call GoldenrodCity_UndergroundSwitches_EventScript_CreateWall2
	call GoldenrodCity_UndergroundSwitches_EventScript_CreateWall3
	call GoldenrodCity_UndergroundSwitches_EventScript_CreateWall4
	call GoldenrodCity_UndergroundSwitches_EventScript_CreateWall5
	call GoldenrodCity_UndergroundSwitches_EventScript_CreateWall6
	special DrawWholeMapView
	waitse
	release
	end

GoldenrodCity_UndergroundSwitches_EventScript_Panel2Activate:: @unlock basic
	setflag FLAG_GOLDENROD_SWITCH_2
	goto_if_set FLAG_GOLDENROD_SWITCH_1, GoldenrodCity_UndergroundSwitches_EventScript_Panel2ActivateWrong
	goto_if_set FLAG_GOLDENROD_SWITCH_3, GoldenrodCity_UndergroundSwitches_EventScript_Panel2ActivateCorrect
	playse SE_BANG
	msgbox GoldenrodUnderground_Text_Switch2, MSGBOX_DEFAULT
	closemessage
	call GoldenrodCity_UndergroundSwitches_EventScript_RemoveWall1
	call GoldenrodCity_UndergroundSwitches_EventScript_RemoveWall2
	call GoldenrodCity_UndergroundSwitches_EventScript_RemoveWall3
	call GoldenrodCity_UndergroundSwitches_EventScript_CreateWall4	
	call GoldenrodCity_UndergroundSwitches_EventScript_CreateWall5
	call GoldenrodCity_UndergroundSwitches_EventScript_CreateWall6	
	special DrawWholeMapView
	waitse
	release
	end

GoldenrodCity_UndergroundSwitches_EventScript_Panel2ActivateWrong:: @unlock basic
	clearflag FLAG_GOLDENROD_SWITCH_ORDER
	playse SE_BANG
	msgbox GoldenrodUnderground_Text_Switch2, MSGBOX_DEFAULT
	closemessage
	call GoldenrodCity_UndergroundSwitches_EventScript_RemoveWall1
	call GoldenrodCity_UndergroundSwitches_EventScript_RemoveWall2
	call GoldenrodCity_UndergroundSwitches_EventScript_RemoveWall3
	call GoldenrodCity_UndergroundSwitches_EventScript_CreateWall4	
	call GoldenrodCity_UndergroundSwitches_EventScript_CreateWall5
	call GoldenrodCity_UndergroundSwitches_EventScript_CreateWall6	
	special DrawWholeMapView
	waitse
	release
	end


GoldenrodCity_UndergroundSwitches_EventScript_Panel2ActivateCorrect:: @unlock item2
	setflag FLAG_GOLDENROD_SWITCH_ORDER
	playse SE_CLICK
	msgbox GoldenrodUnderground_Text_Switch2, MSGBOX_DEFAULT
	closemessage
	call GoldenrodCity_UndergroundSwitches_EventScript_CreateWall1
	call GoldenrodCity_UndergroundSwitches_EventScript_RemoveWall2
	call GoldenrodCity_UndergroundSwitches_EventScript_RemoveWall3
	call GoldenrodCity_UndergroundSwitches_EventScript_CreateWall4	
	call GoldenrodCity_UndergroundSwitches_EventScript_CreateWall5
	call GoldenrodCity_UndergroundSwitches_EventScript_CreateWall6	
	special DrawWholeMapView
	waitse
	release
	end


@==============================================================================================================================================
GoldenrodCity_UndergroundSwitches_EventScript_Panel3:: @lock all
	lock
	goto_if_unset FLAG_GOLDENROD_SWITCH_3, GoldenrodCity_UndergroundSwitches_EventScript_Panel3Activate
	clearflag FLAG_GOLDENROD_SWITCH_3
	clearflag FLAG_GOLDENROD_SWITCH_ORDER
	playse SE_BANG
	msgbox GoldenrodUnderground_Text_Switch3Off, MSGBOX_DEFAULT
	closemessage
	call GoldenrodCity_UndergroundSwitches_EventScript_CreateWall1
	call GoldenrodCity_UndergroundSwitches_EventScript_CreateWall2
	call GoldenrodCity_UndergroundSwitches_EventScript_CreateWall3
	call GoldenrodCity_UndergroundSwitches_EventScript_CreateWall4
	call GoldenrodCity_UndergroundSwitches_EventScript_CreateWall5
	call GoldenrodCity_UndergroundSwitches_EventScript_CreateWall6
	special DrawWholeMapView
	waitse
	release
	end

GoldenrodCity_UndergroundSwitches_EventScript_Panel3Activate:: @unlock item 1
	setflag FLAG_GOLDENROD_SWITCH_3
	clearflag FLAG_GOLDENROD_SWITCH_ORDER
	playse SE_CLICK
	msgbox GoldenrodUnderground_Text_Switch3, MSGBOX_DEFAULT
	closemessage
	call GoldenrodCity_UndergroundSwitches_EventScript_RemoveWall1
	call GoldenrodCity_UndergroundSwitches_EventScript_RemoveWall4
	call GoldenrodCity_UndergroundSwitches_EventScript_CreateWall2
	call GoldenrodCity_UndergroundSwitches_EventScript_CreateWall3
	call GoldenrodCity_UndergroundSwitches_EventScript_CreateWall5
	call GoldenrodCity_UndergroundSwitches_EventScript_CreateWall6
	special DrawWholeMapView
	waitse
	release
	end

@==============================================================================================================================================

GoldenrodCity_UndergroundSwitches_EventScript_CreateWall1::
	setmetatile 5, 7, 0x399, FALSE
	setmetatile 6, 7, 0x39A, FALSE
	setmetatile 7, 7, 0x39B, FALSE

	setmetatile 5, 8, 0x3A1, FALSE
	setmetatile 6, 8, 0x3A2, FALSE
	setmetatile 7, 8, 0x3A3, FALSE
	return

GoldenrodCity_UndergroundSwitches_EventScript_CreateWall2::
	setmetatile 14, 7, 0x399, FALSE
	setmetatile 15, 7, 0x39A, FALSE
	setmetatile 16, 7, 0x39B, FALSE

	setmetatile 14, 8, 0x3A1, FALSE
	setmetatile 15, 8, 0x3A2, FALSE
	setmetatile 16, 8, 0x3A3, FALSE
	return

GoldenrodCity_UndergroundSwitches_EventScript_CreateWall3::
	setmetatile 23, 7, 0x399, FALSE
	setmetatile 24, 7, 0x39A, FALSE
	setmetatile 25, 7, 0x39B, FALSE

	setmetatile 23, 8, 0x3A1, FALSE
	setmetatile 24, 8, 0x3A2, FALSE
	setmetatile 25, 8, 0x3A3, FALSE
	return

GoldenrodCity_UndergroundSwitches_EventScript_CreateWall4::
	setmetatile 5, 11, 0x399, FALSE
	setmetatile 6, 11, 0x39A, FALSE
	setmetatile 7, 11, 0x39B, FALSE

	setmetatile 5, 12, 0x3A1, FALSE
	setmetatile 6, 12, 0x3A2, FALSE
	setmetatile 7, 12, 0x3A3, FALSE
	return

GoldenrodCity_UndergroundSwitches_EventScript_CreateWall5::
	setmetatile 14, 11, 0x399, FALSE
	setmetatile 15, 11, 0x39A, FALSE
	setmetatile 16, 11, 0x39B, FALSE

	setmetatile 14, 12, 0x3A1, FALSE
	setmetatile 15, 12, 0x3A2, FALSE
	setmetatile 16, 12, 0x3A3, FALSE
	return

GoldenrodCity_UndergroundSwitches_EventScript_CreateWall6::
	setmetatile 23, 11, 0x399, FALSE
	setmetatile 24, 11, 0x39A, FALSE
	setmetatile 25, 11, 0x39B, FALSE

	setmetatile 23, 12, 0x3A1, FALSE
	setmetatile 24, 12, 0x3A2, FALSE
	setmetatile 25, 12, 0x3A3, FALSE
	return
@======================================================================================================================

GoldenrodCity_UndergroundSwitches_EventScript_RemoveWall1::
	setmetatile 5, 7, 0x378, FALSE
	setmetatile 6, 7, 0x379, FALSE
	setmetatile 7, 7, 0x37A, FALSE
	
	setmetatile 5, 8, 0x380, FALSE
	setmetatile 6, 8, 0x381, FALSE
	setmetatile 7, 8, 0x382, FALSE
	return

GoldenrodCity_UndergroundSwitches_EventScript_RemoveWall2::
	setmetatile 14, 7, 0x378, FALSE
	setmetatile 15, 7, 0x379, FALSE
	setmetatile 16, 7, 0x37A, FALSE
	
	setmetatile 14, 8, 0x380, FALSE
	setmetatile 15, 8, 0x381, FALSE
	setmetatile 16, 8, 0x382, FALSE
	return

GoldenrodCity_UndergroundSwitches_EventScript_RemoveWall3::
	setmetatile 23, 7, 0x378, FALSE
	setmetatile 24, 7, 0x379, FALSE
	setmetatile 25, 7, 0x37A, FALSE
	
	setmetatile 23, 8, 0x380, FALSE
	setmetatile 24, 8, 0x381, FALSE
	setmetatile 25, 8, 0x382, FALSE
	return

GoldenrodCity_UndergroundSwitches_EventScript_RemoveWall4::
	setmetatile 5, 11, 0x378, FALSE
	setmetatile 6, 11, 0x379, FALSE
	setmetatile 7, 11, 0x37A, FALSE
	
	setmetatile 5, 12, 0x380, FALSE
	setmetatile 6, 12, 0x381, FALSE
	setmetatile 7, 12, 0x382, FALSE
	return

GoldenrodCity_UndergroundSwitches_EventScript_RemoveWall5::
	setmetatile 14, 11, 0x378, FALSE
	setmetatile 15, 11, 0x379, FALSE
	setmetatile 16, 11, 0x37A, FALSE
	
	setmetatile 14, 12, 0x380, FALSE
	setmetatile 15, 12, 0x381, FALSE
	setmetatile 16, 12, 0x382, FALSE
	return

GoldenrodCity_UndergroundSwitches_EventScript_RemoveWall6::
	setmetatile 23, 11, 0x378, FALSE
	setmetatile 24, 11, 0x379, FALSE
	setmetatile 25, 11, 0x37A, FALSE
	
	setmetatile 23, 12, 0x380, FALSE
	setmetatile 24, 12, 0x381, FALSE
	setmetatile 25, 12, 0x382, FALSE
	return

GoldenrodCity_UndergroundSwitches_EventScript_SilverTriggerTop::
	lock
	playse SE_EXIT
	waitse
	playse SE_PIN
	playbgm MUS_HG_ENCOUNTER_RIVAL, FALSE
	@clearflag FLAG_HIDE_GOLDENROD_UNDERGROUND_SILVER
	addobject LOCALID_GOLDENROD_UNDERGROUND_SILVER
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
	applymovement LOCALID_GOLDENROD_UNDERGROUND_SILVER, GoldenrodCity_UndergroundSwitches_Movement_SilverEnterTop
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkRight1
	waitmovement 0
	waitmovement 0
	msgbox GoldenrodUnderground_Text_SilverBefore, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_STARTER_MON, 0, GoldenrodCity_UndergroundSwitches_EventScript_Cyndaquil
	call_if_eq VAR_STARTER_MON, 1, GoldenrodCity_UndergroundSwitches_EventScript_Totodile
	call_if_eq VAR_STARTER_MON, 2, GoldenrodCity_UndergroundSwitches_EventScript_Chikorita
	playbgm MUS_HG_RIVAL_EXIT, FALSE
	msgbox GoldenrodUnderground_Text_SilverAfter, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GOLDENROD_UNDERGROUND_SILVER, GoldenrodCity_UndergroundSwitches_Movement_SilverLeaveTop
	waitmovement 0
	playse SE_EXIT
	setflag FLAG_HIDE_GOLDENROD_UNDERGROUND_SILVER
	removeobject LOCALID_GOLDENROD_UNDERGROUND_SILVER
	fadedefaultbgm
	setvar VAR_GOLDENROD_CITY_STATE, 9
	release
	end


GoldenrodCity_UndergroundSwitches_EventScript_SilverTriggerBot::
	lock
	playse SE_EXIT
	waitse
	playse SE_PIN
	playbgm MUS_HG_ENCOUNTER_RIVAL, FALSE
	clearflag FLAG_HIDE_GOLDENROD_UNDERGROUND_SILVER
	addobject LOCALID_GOLDENROD_UNDERGROUND_SILVER
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
	applymovement LOCALID_GOLDENROD_UNDERGROUND_SILVER, GoldenrodCity_UndergroundSwitches_Movement_SilverEnterBot
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkRight1
	waitmovement 0
	waitmovement 0
	msgbox GoldenrodUnderground_Text_SilverBefore, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_STARTER_MON, 0, GoldenrodCity_UndergroundSwitches_EventScript_Cyndaquil
	call_if_eq VAR_STARTER_MON, 1, GoldenrodCity_UndergroundSwitches_EventScript_Totodile
	call_if_eq VAR_STARTER_MON, 2, GoldenrodCity_UndergroundSwitches_EventScript_Chikorita
	playbgm MUS_HG_RIVAL_EXIT, FALSE
	msgbox GoldenrodUnderground_Text_SilverAfter, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GOLDENROD_UNDERGROUND_SILVER, GoldenrodCity_UndergroundSwitches_Movement_SilverLeaveBot
	waitmovement 0
	playse SE_EXIT
	setflag FLAG_HIDE_GOLDENROD_UNDERGROUND_SILVER
	removeobject LOCALID_GOLDENROD_UNDERGROUND_SILVER
	fadedefaultbgm
	setvar VAR_GOLDENROD_CITY_STATE, 9
	release
	end

GoldenrodCity_UndergroundSwitches_EventScript_Cyndaquil::
	trainerbattle_no_intro TRAINER_RIVAL_CYNDAQUIL_4_HNS, GoldenrodUnderground_Text_SilverWin
	return

GoldenrodCity_UndergroundSwitches_EventScript_Totodile::
	trainerbattle_no_intro TRAINER_RIVAL_TOTODILE_4_HNS, GoldenrodUnderground_Text_SilverWin
	return

GoldenrodCity_UndergroundSwitches_EventScript_Chikorita::
	trainerbattle_no_intro TRAINER_RIVAL_CHIKORITA_4_HNS, GoldenrodUnderground_Text_SilverWin
	return



GoldenrodCity_UndergroundSwitches_Movement_SilverEnterTop:
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

GoldenrodCity_UndergroundSwitches_Movement_SilverLeaveTop:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	face_right
	step_end


GoldenrodCity_UndergroundSwitches_Movement_SilverEnterBot:
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

GoldenrodCity_UndergroundSwitches_Movement_SilverLeaveBot:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	face_right
	step_end	

GoldenrodCity_UndergroundSwitches_EventScript_Grunt10::
    trainerbattle_single TRAINER_GRUNT_10_HNS, GoldenrodUnderground_Text_GruntM11Seen, GoldenrodUnderground_Text_GruntM11Beaten
	msgbox GoldenrodUnderground_Text_GruntM11After, MSGBOX_AUTOCLOSE
	end

GoldenrodCity_UndergroundSwitches_EventScript_Grunt20::
    trainerbattle_single TRAINER_GRUNT_20_HNS, GoldenrodUnderground_Text_GruntM25Seen, GoldenrodUnderground_Text_GruntM25Beaten
	msgbox GoldenrodUnderground_Text_GruntM25After, MSGBOX_AUTOCLOSE
	end

GoldenrodCity_UndergroundSwitches_EventScript_Duncan::
    trainerbattle_single TRAINER_DUNCAN_HNS, GoldenrodUnderground_Text_BurglarDuncanSeen, GoldenrodUnderground_Text_BurglarDuncanBeaten
	msgbox GoldenrodUnderground_Text_BurglarDuncanAfter, MSGBOX_AUTOCLOSE
	end

GoldenrodCity_UndergroundSwitches_EventScript_Eddie::
    trainerbattle_single TRAINER_EDDIE_HNS, GoldenrodUnderground_Text_BurglarEddieSeen, GoldenrodUnderground_Text_BurglarEddieBeaten
	msgbox GoldenrodUnderground_Text_BurglarEddieAfter, MSGBOX_AUTOCLOSE
	end

GoldenrodCity_UndergroundSwitches_EventScript_Grunt11::
    trainerbattle_single TRAINER_GRUNT_11_HNS, GoldenrodUnderground_Text_GruntM13Seen, GoldenrodUnderground_Text_GruntM13Beaten
	msgbox GoldenrodUnderground_Text_GruntM13After, MSGBOX_AUTOCLOSE
	end

GoldenrodCity_UndergroundSwitches_EventScript_Grunt27::
    trainerbattle_single TRAINER_GRUNT_27_HNS, GoldenrodUnderground_Text_GruntF3Seen, GoldenrodUnderground_Text_GruntF3Beaten
	msgbox GoldenrodUnderground_Text_GruntF3After, MSGBOX_AUTOCLOSE
	end

GoldenrodCity_UndergroundSwitches_EventScript_Item_Revive::
	finditem ITEM_MAX_REVIVE
	end

GoldenrodCity_UndergroundSwitches_EventScript_Item_MaxPotion::
	finditem ITEM_MAX_POTION
	end

GoldenrodCity_UndergroundSwitches_EventScript_Item_SmokeBall::
	finditem ITEM_SMOKE_BALL
	end

GoldenrodUnderground_Text_SilverBefore:
    .string "עצור!\p"
    .string "ראיתי אותך, אז עקבתי אחריך.\p"
    .string "אני לא צריך שתסתובב לי בין\n"
    .string "הרגליים כשאני מטפל בצוות רוקט.\p"
    .string "…רגע אחד. כבר ניצחת אותי פעם,\n"
    .string "נכון?\p"
    .string "זה היה סתם מזל.\p"
    .string "אימנתי את הפוקימונים שלי, ועכשיו\n"
    .string "אני אסגור איתך חשבון!$"

GoldenrodUnderground_Text_SilverWin:
    .string "…למה… למה אני מפסיד?\p"
    .string "אספתי את הפוקימונים הכי קשוחים.\p"
    .string "לא הורדתי את הרגל מהגז.\p"
    .string "אז למה אני מפסיד?$"

GoldenrodUnderground_Text_SilverAfter:
    .string "…אני לא מבין…\p"
    .string "מה שהבחור הזה, לאנס, אמר - זה נכון?\p"
    .string "שאני לא מתייחס לפוקימונים כמו שצריך?\p"
    .string "אהבה…\p"
    .string "אמון…\p"
    .string "זה באמת מה שחסר לי?\p"
    .string "זה מה שמונע ממני לנצח?\p"
    .string "אני… אני פשוט לא מבין.\p"
    .string "אבל זה לא ייגמר כאן.\p"
    .string "לא עכשיו. לא בגלל זה.\p"
    .string "אני לא אוותר על החלום שלי להיות\n"
    .string "מאמן הפוקימונים הטוב בעולם!$"

GoldenrodUnderground_Text_SilverLoss:
    .string "Humph. This is my real power, wimp.\p"
    .string "I'll make TEAM ROCKET history.\p"
    .string "And I'm going to grind that LANCE\n"
    .string "under my heels.$"

GoldenrodUnderground_Text_GruntM11Seen:
    .string "פותחים תריס אחד, ואחר נסגר.\p"
    .string "מתערב שלא תצליח להגיע לאן שאתה רוצה!$"

GoldenrodUnderground_Text_GruntM11Beaten:
    .string "אוף! ההססנות שלי הפילה אותי!$"

GoldenrodUnderground_Text_GruntM11After:
    .string "גם אני מבולבל… על המתג שבקצה\n"
    .string "צריך ללחוץ ראשון, אבל…$"

GoldenrodUnderground_Text_GruntM25Seen:
    .string "קוואהאהא!\p"
    .string "התריסים מבלבלים אותך, מה?\p"
    .string "אגלה לך סוד אם תצליח\n"
    .string "לנצח אותי!$"

GoldenrodUnderground_Text_GruntM25Beaten:
    .string "אוווו… פישלתי.$"

GoldenrodUnderground_Text_GruntM25After:
    .string "טוב. רמז!\p"
    .string "צריך לשנות את סדר הלחיצה על המתגים.\p"
    .string "ככה ישתנה האופן שבו התריסים\n"
    .string "נפתחים ונסגרים.$"

GoldenrodUnderground_Text_BurglarDuncanSeen:
    .string "תביא את כל מה ששווה משהו!$"

GoldenrodUnderground_Text_BurglarDuncanBeaten:
    .string "רחמים!$"

GoldenrodUnderground_Text_BurglarDuncanAfter:
    .string "לגנוב ולמכור! זה הבסיס של\n"
    .string "הפשע, ילד!$"

GoldenrodUnderground_Text_BurglarEddieSeen:
    .string "הם נטשו את הפרויקט הזה לפני\n"
    .string "שסיימו אותו.\p"
    .string "אני מחפש שלל שנשאר מאחור.$"

GoldenrodUnderground_Text_BurglarEddieBeaten:
    .string "זה כבר מוגזם!$"

GoldenrodUnderground_Text_BurglarEddieAfter:
    .string "המחסן התת-קרקעי?\p"
    .string "מה יש לך לחפש שם?\p"
    .string "אין שם למטה כלום.$"

GoldenrodUnderground_Text_GruntM13Seen:
    .string "לא אכפת לי אם הלכת לאיבוד.\p"
    .string "אם הגעת לכאן, אתה לא\n"
    .string "יותר מקורבן!$"

GoldenrodUnderground_Text_GruntM13Beaten:
    .string "אח! מה, חושב שאתה מגניב, הא?$"

GoldenrodUnderground_Text_GruntM13After:
    .string "בטח יש לך קרח בוורידים אם אתה\n"
    .string "מעז לזלזל בצוות רוקט.$"

GoldenrodUnderground_Text_GruntF3Seen:
    .string "הלכת לאיבוד? לא, אין מצב.\p"
    .string "אין לך את המבט המפוחד הזה.\p"
    .string "אני אתן לך סיבה טובה\n"
    .string "לפחד!$"

GoldenrodUnderground_Text_GruntF3Beaten:
    .string "איך יכולת?$"

GoldenrodUnderground_Text_GruntF3After:
    .string "לך לאן שבא לך! לך לאיבוד!\n"
    .string "ממש לא אכפת לי!$"

GoldenrodUnderground_Text_Switch1:
    .string "מתג 1 הופעל.$"

GoldenrodUnderground_Text_Switch2:
    .string "מתג 2 הופעל.$"

GoldenrodUnderground_Text_Switch3:
    .string "מתג 3 הופעל.$"

GoldenrodUnderground_Text_Switch1Off:
    .string "מתג 1 כובה.$"

GoldenrodUnderground_Text_Switch2Off:
    .string "מתג 2 כובה.$"

GoldenrodUnderground_Text_Switch3Off:
    .string "מתג 3 כובה.$"
