NewBarkTown_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, NewBarkTown_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, NewBarkTown_OnFrame
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

NewBarkTown_OnFrame::
	map_script_2 VAR_NEWBARK_TOWN_STATE, 6, NewBarkTown_EventScript_ElmCallAfterLeague
	.2byte 0

NewBarkTown_EventScript_ElmCallAfterLeague::
	lock
	setspeaker NewBarkTown_Text_ElmName
	pokenavcall BlackthornCity_Text_ElmCall
	waitmessage
	delay 30
	setvar VAR_NEWBARK_TOWN_STATE, 7
	setvar VAR_NEWBARKTOWN_LABSTATE, 10
	release
	end

NewBarkTown_Text_ElmName:
	.string "פרופ' אלם$"

NewBarkTown_OnTransition::
	goto_if_eq VAR_NEWBARK_TOWN_STATE, 2, NewBarkTown_Set_TalkToElm
	goto_if_eq VAR_NEWBARK_TOWN_STATE, 4, NewBarkTown_Set_TalkToMom
	end

NewBarkTown_Set_TalkToElm::
	clearflag FLAG_HIDE_SILVER_NEWBARKTOWN
	setobjectxyperm LOCALID_LASS, 0, 11
	callnative SetTimeBasedEncounters
	end

NewBarkTown_Set_TalkToMom::
	setobjectxyperm LOCALID_LASS, 0, 11
	callnative SetTimeBasedEncounters
	end

NewBarkTown_EventScript_LabSign::
	msgbox NewBarkTown_Text_LabSign, MSGBOX_SIGN
	end

NewBarkTown_EventScript_TownSign::
	msgbox NewBarkTown_Text_Sign, MSGBOX_SIGN
	closemessage
	end


NewBarkTown_EventScript_Lass::
	lock
	faceplayer
	goto_if_eq VAR_NEWBARK_TOWN_STATE, 2, NewBarkTown_EventScript_LassState2
	goto_if_eq VAR_NEWBARK_TOWN_STATE, 3, NewBarkTown_EventScript_LassState3
	goto_if_eq VAR_NEWBARK_TOWN_STATE, 4, NewBarkTown_EventScript_LassState4
	msgbox NewBarkTown_Text_LassState5, MSGBOX_DEFAULT
	closemessage
	release
	end
	
NewBarkTown_EventScript_LassState2::
	playse SE_PIN
	applymovement LOCALID_LASS, Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_LASS
	faceplayer
	waitmovement 0
	msgbox NewBarkTown_Text_LassState2, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_EventScript_LassState3::
	msgbox NewBarkTown_Text_LassState3, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_EventScript_LassState4::
	playse SE_PIN
	applymovement LOCALID_LASS, Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_LASS
	faceplayer
	waitmovement 0
	msgbox NewBarkTown_Text_LassState4, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_EventScript_Wooper::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_WOOPER, CRY_MODE_NORMAL
	msgbox NewBarkTown_Text_Wooper, MSGBOX_DEFAULT
	waitmoncry
	release
	end

NewBarkTown_EventScript_LeaveTrigger::
	lock
	call_if_eq VAR_NEWBARK_TOWN_STATE, 2, NewBarkTown_EventScript_LeaveTriggersState2
	call_if_eq VAR_NEWBARK_TOWN_STATE, 4, NewBarkTown_EventScript_LeaveTriggersState4
	applymovement OBJ_EVENT_ID_PLAYER, OldaleTown_Movement_PlayerStepBack
	waitmovement 0
	release
	end

NewBarkTown_EventScript_LeaveTriggersState2::
	playse SE_PIN
	applymovement LOCALID_LASS, Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_LASS
	applymovement LOCALID_LASS, NewBarkTown_Movement_FaceDown
	waitmovement 0
	msgbox NewBarkTown_Text_LassState2, MSGBOX_DEFAULT
	closemessage
	return

NewBarkTown_EventScript_LeaveTriggersState4::
	playse SE_PIN
	applymovement LOCALID_LASS, Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_LASS
	applymovement LOCALID_LASS, NewBarkTown_Movement_FaceDown
	waitmovement 0
	msgbox NewBarkTown_Text_LassState4, MSGBOX_DEFAULT
	closemessage
	return 



NewBarkTown_EventScript_FatMan::
	lock
	faceplayer
	goto_if_eq VAR_NEWBARK_TOWN_STATE, 2, NewBarkTown_EventScript_FatManState2
	msgbox NewBarkTown_Text_FatManState3, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_EventScript_FatManState2::
	msgbox NewBarkTown_Text_FatManState2, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_EventScript_Silver::
	lock
	msgbox NewBarkTown_Text_Silver1, MSGBOX_DEFAULT
	delay 60
	playse SE_PIN
	applymovement LOCALID_SILVER, Common_Movement_ExclamationMark
	faceplayer
	waitmovement 0
	msgbox NewBarkTown_Text_Silver2, MSGBOX_DEFAULT
	playse SE_BANG
	applymovement LOCALID_SILVER, NewBarkTown_Movement_SilverPushesPlayer
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Movement_PlayerPushedBySilver
	waitmovement 0
	applymovement LOCALID_SILVER, Common_Movement_FaceOriginalDirection
	waitmovement 0
	waitmovement 0
	release
	end


NewBarkTown_EventScript_Door::
	msgbox NewBarkTown_Text_Door, MSGBOX_SIGN
	end

NewBarkTown_EventScript_TestMan1::
	givebp 4
	msgbox BattleFrontier_Text_ObtainedXBattlePoints, MSGBOX_GETPOINTS
	end

NewBarkTown_EventScript_TestMan2::
	setvar VAR_NEWBARK_TOWN_STATE, 4
	setflag FLAG_HIDE_MOMS_FRIEND
	setflag FLAG_ADVENTURE_STARTED
	setflag FLAG_START_NUZLOCKE
	setflag FLAG_HIDE_SILVER_NEWBARKTOWN
	end

NewBarkTown_EventScript_TestMan3::
	setvar VAR_NEWBARK_TOWN_STATE, 5
	
	clearflag FLAG_COMPLETED_AERODACTYL_PUZZLE
	clearflag FLAG_COMPLETED_HOOH_PUZZLE
	clearflag FLAG_COMPLETED_KABUTO_PUZZLE
	clearflag FLAG_COMPLETED_OMANYTE_PUZZLE
	end

NewBarkTown_Movement_SilverPushesPlayer:
	walk_fast_left
	walk_fast_left
	walk_fast_down
	face_down
	lock_facing_direction
	unlock_facing_direction
	walk_fast_up
	walk_fast_right
	walk_fast_right
	step_end


NewBarkTown_Movement_PlayerPushedBySilver:
	walk_fast_left
	face_up
	walk_fast_down
	face_up
	lock_facing_direction
	jump_2_down
	unlock_facing_direction
	face_down
	step_end

	


NewBarkTown_Movement_FaceDown:
	face_down
	step_end

NewBarkTown_Text_LabSign:
	.string "המעבדה של פרופ' אלם$"

NewBarkTown_Text_Door:
	.string "הדלת נעולה.$"

NewBarkTown_Text_Wooper:
	.string "וופר: ווווווופ.$"

NewBarkTown_Text_FatManState2:
	.string "וואו, הפוקיגיר שלך מרשים!\n"
	.string "אמא שלך קנתה לך אותו?$"

NewBarkTown_Text_FatManState3:
	.string "יו, {PLAYER}!\p"
	.string "שמעתי שפרופ' אלם גילה\n"
	.string "כמה פוקימונים חדשים.$"

NewBarkTown_Text_LassState2:
	.string "רגע, {PLAYER}!\p"
	.string "מסוכן לצאת\n"
	.string "בלי פוקימון!\p"
	.string "בדרך לעיר הבאה, פוקימונים\n"
	.string "פראיים קופצים מתוך הדשא.$"

NewBarkTown_Text_LassState3:
	.string "אוי! הפוקימון שלך מקסים!\n"
	.string "הלוואי שהיה לי אחד!$"

NewBarkTown_Text_LassState4:
	.string "היי, {PLAYER}! שוב יוצא לדרך?\p"
	.string "כדאי לספר לאמא שלך\n"
	.string "שאתה יוצא.$"

NewBarkTown_Text_LassState5:
	.string "תתקשר לאמא שלך בפוקיגיר\n"
	.string "כדי לספר לה מה שלומך.$\p"

NewBarkTown_Text_Silver1:
	.string ". . .\p"
	.string "אז זו מעבדת הפוקימונים\n"
	.string "המפורסמת של אלם…$"

NewBarkTown_Text_Silver2:
	.string "…מה אתה בוהה בי?$"

NewBarkTown_Text_Sign:
	.string "העיירה ניו בארק\p"
	.string "העיירה שבה נושבות\n"
	.string "רוחות של התחלה חדשה$"

NewBarkTown_EventScript_PlayersHouseMailbox::
	msgbox NewBarkTown_Text_PlayersHouse, MSGBOX_SIGN
	end

NewBarkTown_EventScript_ElmsHouseMailbox::
	msgbox NewBarkTown_Text_ElmsHouse, MSGBOX_SIGN
	end

NewBarkTown_Text_PlayersHouse:
	.string "הבית של {PLAYER}$"

NewBarkTown_Text_ElmsHouse:
	.string "הבית של פרופ' אלם$"

