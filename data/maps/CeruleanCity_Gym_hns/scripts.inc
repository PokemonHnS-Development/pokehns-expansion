CeruleanCity_Gym_hns_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, CeruleanCity_Gym_OnFrame
	.byte 0

CeruleanCity_Gym_OnFrame::
	map_script_2 VAR_KANTO_ROCKET_STORY_STATE, 2,  CeruleanCity_Gym_EventScript_RocketGrunt
	map_script_2 VAR_TEMP_0, 0,  CeruleanCity_Gym_EventScript_TryMachinePart
	.2byte 0

CeruleanCity_Gym_EventScript_RocketGrunt::
	lock
	applymovement LOCALID_CERULEAN_GYM_ROCKET, CeruleanCity_Gym_Movement_GruntBumpPlayer
	delay 20
	playse SE_BANG
	waitmovement 0
	
	msgbox CeruleanGym_Text_GruntIntro, MSGBOX_DEFAULT
	closemessage
	playse SE_PIN
	applymovement LOCALID_CERULEAN_GYM_ROCKET, Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_CERULEAN_GYM_ROCKET
	applymovement LOCALID_CERULEAN_GYM_ROCKET, CeruleanCity_Gym_Movement_GruntWalkBack
	waitmovement 0
	msgbox CeruleanGym_Text_GruntBigMistake, MSGBOX_DEFAULT
	applymovement LOCALID_CERULEAN_GYM_ROCKET, CeruleanCity_Gym_Movement_GruntWalkToPlayerAgain
	waitmovement 0
	msgbox CeruleanGym_Text_GruntBye, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, CeruleanCity_Gym_Movement_PlayerSlide
	delay 10
	applymovement LOCALID_CERULEAN_GYM_ROCKET, CeruleanCity_Gym_Movement_GruntLeave
	waitmovement 0
	fadescreenswapbuffers FADE_TO_BLACK
	playse SE_EXIT
	setflag FLAG_HIDE_CERULEAN_GYM_ROCKET
	removeobject LOCALID_CERULEAN_GYM_ROCKET
	fadescreenswapbuffers FADE_FROM_BLACK
	clearflag FLAG_HIDE_CERULEAN_CAPE_ROCKET
	setvar VAR_KANTO_ROCKET_STORY_STATE, 3
	release
	end

CeruleanCity_Gym_EventScript_TryMachinePart::
	goto_if_eq VAR_KANTO_ROCKET_STORY_STATE, 5, CeruleanCity_Gym_EventScript_MachinePart
	setvar VAR_TEMP_0, 1
	end

CeruleanCity_Gym_EventScript_MachinePart::
	special SpawnCameraObject
	applymovement OBJ_EVENT_ID_CAMERA, CeruleanCity_Movement_CameraPanUp
	waitmovement 0
	delay 30
	setvar VAR_0x8004, 5  @ x
	setvar VAR_0x8005, 13  @ y
	playse SE_PIN
	call Route110_TrickHouseEntrance_EventScript_DoHidingSpotSparkle
	delay 55
	applymovement OBJ_EVENT_ID_CAMERA, CeruleanCity_Movement_CameraPanDown
	waitmovement 0
	special RemoveCameraObject
	setvar VAR_TEMP_0, 1
	end

CeruleanCity_Gym_EventScript_MachinePartItem::
	goto_if_lt VAR_KANTO_ROCKET_STORY_STATE, 5, CeruleanCity_Gym_EventScript_DoNothing
	goto_if_ge VAR_KANTO_ROCKET_STORY_STATE, 6, CeruleanCity_Gym_EventScript_DoNothing
	finditem ITEM_MACHINE_PART
	setvar VAR_KANTO_ROCKET_STORY_STATE, 6
	setflag FLAG_HIDDEN_ITEM_MACHINE_PART
	end

CeruleanCity_Gym_EventScript_DoNothing::
	end

CeruleanCity_Movement_CameraPanUp:
	walk_up
	walk_up
	walk_up
	step_end

CeruleanCity_Movement_CameraPanDown:
	walk_down
	walk_down
	walk_down
	step_end

CeruleanCity_Gym_Movement_GruntBumpPlayer:
	walk_fast_down
	walk_fast_down
	walk_in_place_fast_down
	lock_facing_direction
	jump_up
	unlock_facing_direction
	delay_16
	walk_down
	step_end

CeruleanCity_Gym_Movement_GruntWalkBack:
	lock_facing_direction
	walk_slow_up
	walk_slow_up
	unlock_facing_direction
	step_end

CeruleanCity_Gym_Movement_GruntWalkToPlayerAgain:
	walk_down
	walk_down
	step_end

CeruleanCity_Gym_Movement_PlayerSlide:
	lock_facing_direction
	walk_fast_right
	unlock_facing_direction
	step_end

CeruleanCity_Gym_Movement_GruntLeave:
	walk_fast_down
	walk_in_place_fast_down
	step_end

CeruleanCity_Gym_EventScript_Statue::
	lockall
	goto_if_set FLAG_BADGE10_GET, CeruleanCity_Gym_EventScript_GymStatuePostVictory
	msgbox CeruleanCity_Gym_Text_GymStatue
	releaseall
	end

CeruleanCity_Gym_EventScript_StatueDuringRocket::
	msgbox CeruleanGym_Text_Note, MSGBOX_SIGN
	end 

CeruleanCity_Gym_EventScript_GymStatuePostVictory::
	msgbox CeruleanCity_Gym_Text_GymStatuePlayerWon
	releaseall
	end

CeruleanGym_EventScript_Diana::
	trainerbattle_single TRAINER_DIANA_HNS, CeruleanGym_Text_SwimmerfDianaSeen, CeruleanGym_Text_SwimmerfDianaBeaten
	msgbox CeruleanGym_Text_SwimmerfDianaAfter, MSGBOX_AUTOCLOSE
	end

CeruleanGym_EventScript_Briana::
	trainerbattle_single TRAINER_BRIANA_HNS, CeruleanGym_Text_SwimmerfBrianaSeen, CeruleanGym_Text_SwimmerfBrianaBeaten
	msgbox CeruleanGym_Text_SwimmerfBrianaAfter, MSGBOX_AUTOCLOSE
	end

CeruleanGym_EventScript_Parker::
	trainerbattle_single TRAINER_PARKER_HNS, CeruleanGym_Text_SwimmermParkerSeen, CeruleanGym_Text_SwimmermParkerBeaten
	msgbox CeruleanGym_Text_SwimmermParkerAfter, MSGBOX_AUTOCLOSE
	end

CeruleanCity_Gym_EventScript_GymGuy::
	goto_if_set FLAG_DEFEATED_CERULEAN_GYM, CeruleanCity_Gym_EventScript_GymGuyAfter
	msgbox CeruleanGym_Text_GuideIntro, MSGBOX_NPC
	end

CeruleanCity_Gym_EventScript_GymGuyAfter::
	msgbox CeruleanGym_Text_GuideWin, MSGBOX_NPC
	end

CeruleanCity_Gym_Text_GymStatue::
    .string "מכון הפוקימון של סרוליאן\n"
    .string "מנהיגה: מיסטי\p"
    .string "מאמנים מנצחים:\n"
    .string "בלו, רד$"

CeruleanCity_Gym_Text_GymStatuePlayerWon::
    .string "מכון הפוקימון של סרוליאן\n"
    .string "מנהיגה: מיסטי\p"
    .string "מאמנים מנצחים:\n"
    .string "בלו, רד, {PLAYER}$"

CeruleanGym_Text_Note:
	.string "Sorry, I'll be out for a while.\n"
	.string "MISTY, GYM LEADER\p"
	.string "Since MISTY's out, we'll be away\n"
	.string "too.\l"
	.string "GYM TRAINERS$"


CeruleanCity_Gym_EventScript_Misty::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_CERULEAN_GYM, CeruleanCity_Gym_EventScript_Misty_Defeated
	msgbox CeruleanGym_Text_MistyIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_MISTY_HNS, CeruleanGym_Text_MistyWinLoss
	message CeruleanGym_Text_ReceivedBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	setflag FLAG_BADGE10_GET
	setflag FLAG_DEFEATED_CERULEAN_GYM
	addvar VAR_NUM_BADGES, 1
	setvar VAR_0x8008, 10
	call Common_EventScript_SetGymTrainers_hns
	msgbox CeruleanGym_Text_Misty_GiveTM, MSGBOX_DEFAULT
	giveitem ITEM_TM_WATER_PULSE
	msgbox CeruleanGym_Text_Misty_ExplainTM, MSGBOX_DEFAULT
	clearflag FLAG_HIDE_CAPE_MISTY
	call_if_eq VAR_SUICUNE_ENCOUNTERS, 5, CeruleanCity_Gym_SetSuicuneScene
	closemessage
	release
	end

CeruleanCity_Gym_SetSuicuneScene::
	setvar VAR_SUICUNE_ENCOUNTERS, 6
	clearflag FLAG_HIDE_ROUTE25_SUICUNE
	return

CeruleanCity_Gym_EventScript_Misty_Defeated::
	msgbox CeruleanGym_Text_MistyFightDone, MSGBOX_DEFAULT
	closemessage
	release
	end

CeruleanGym_Text_GruntIntro:
	.string "אופס! אני כל כך סליחה!\n"
	.string "אתה לא נפגע, אוקיי?\p"
	.string "אני מאוד עסוק. אין זמן לדבר עם אתה.\n"
	.string "לא טוב בשביל אני אם מישהו רואה.$"

CeruleanGym_Text_GruntBigMistake:
	.string "אוי לא! אתה כבר רואה אני!\n"
	.string "אני עושה טעות גדולה!$"

CeruleanGym_Text_GruntBye:
	.string "היי, אתה! לשכוח שאתה רואה אני,\n"
	.string "אוקיי?\p"
	.string "אתה לא רואה, לא שומע,\n"
	.string "לא יודע כלום,\p"
	.string "אוקיי? ביי, ילד! כלום!\p"
	.string "ביי-ביי, יאללה ביי!$"

CeruleanGym_Text_Note1:
	.string "Sorry, I'll be out for a while.\n"
	.string "MISTY, GYM LEADER\p"
	.string "Since MISTY's out, we'll be away\n"
	.string "too. GYM TRAINERS$"

CeruleanGym_Text_MistyIntro:
	.string "מיסטי: חיכיתי לך, נודניק!\p"
	.string "אולי יש לך הרבה תגי מכון\n"
	.string "מג'וטו, אבל כדאי שלא תזלזל בי.\p"
	.string "הפוקימונים שלי מסוג מים\n"
	.string "קשוחים!$"

CeruleanGym_Text_MistyWinLoss:
	.string "מיסטי: אתה באמת טוב…\p"
	.string "אני מודה שאתה מיומן…\p"
	.string "הנה. זה תג מפל.$"

CeruleanGym_Text_ReceivedBadge:
	.string "{PLAYER} קיבל את תג מפל.$"

CeruleanGym_Text_MistyFightDone:
	.string "מיסטי: יש הרבה מאמנים חזקים\n"
	.string "בג'וטו? כמוך, אני מתכוונת.\p"
	.string "יום אחד אני אצא למסע,\n"
	.string "כדי להילחם במאמנים מיומנים.$"

CeruleanGym_Text_MistyRematch:
	.string "MISTY: Wow, you're the KANTO\n"
	.string "CHAMPION now!\p"
	.string "That's amazing! You've come a\n"
	.string "long way, {PLAYER}.\p"
	.string "But I'm not backing down.\p"
	.string "Want to have a rematch with me?$"

CeruleanGym_Text_MistyRematchDefeat:
	.string "MISTY: You really are good…$"

CeruleanGym_Text_SwimmerfDianaSeen:
	.string "סליחה שלא הייתי כאן.\n"
	.string "קדימה, נתחיל!$"

CeruleanGym_Text_SwimmerfDianaBeaten:
	.string "אני מוותרת! אתה המנצח!$"

CeruleanGym_Text_SwimmerfDianaAfter:
	.string "אני אשחה לי בשקט.$"

CeruleanGym_Text_SwimmerfBrianaSeen:
	.string "אל תיתן לשחייה האלגנטית שלי\n"
	.string "להלחיץ אותך.$"

CeruleanGym_Text_SwimmerfBrianaBeaten:
	.string "אוו, חיסלת אותי בשלווה כזאת…$"

CeruleanGym_Text_SwimmerfBrianaAfter:
	.string "אל תהיה שחצן מדי בגלל\n"
	.string "שניצחת אותי.\p"
	.string "מיסטי תמחץ אותך\n"
	.string "אם תהיה שאנן.$"

CeruleanGym_Text_SwimmermParkerSeen:
	.string "גלוב…\p"
	.string "אני ראשון! בוא תתפוס אותי!$"

CeruleanGym_Text_SwimmermParkerBeaten:
	.string "זה לא ייתכן…$"

CeruleanGym_Text_SwimmermParkerAfter:
	.string "מיסטי השתפרה מאוד\n"
	.string "בשנים האחרונות.\p"
	.string "אל תוריד את המשמר,\n"
	.string "אחרת תימחץ!$"

CeruleanGym_Text_GuideIntro:
	.string "יו! אלוף לעתיד!\p"
	.string "מיסטי לא הייתה כאן, אז גם אני\n"
	.string "יצאתי לבלות קצת. חה-חה-חה.$"

CeruleanGym_Text_GuideWin:
	.string "הו, הראית לי כמה אתה קשוח.\p"
	.string "כמו תמיד, זה היה קרב אדיר וחצי!$"

CeruleanGym_Text_Misty_GiveTM:
	.string "הנה, קח גם את זה.$"

CeruleanGym_Text_Misty_ExplainTM:
	.string "זה המ”מ של דופק מים.\p"
	.string "הוא גורם נזק, ולפעמים\n"
	.string "גם גורם לבלבול!$"
