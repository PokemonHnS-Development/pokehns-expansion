AzaleaTown_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, AzaleaTown_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, AzaleaTown_OnFrame
	.byte 0

AzaleaTown_OnTransition::
	goto_if_eq VAR_AZALEA_TOWN_STATE, 5, AzaleaTown_MapScript_Hide_Silver
	end
	
AzaleaTown_OnFrame::
	map_script_2 VAR_AZALEA_TOWN_STATE, 8, AzaleaTown_EventScript_GSBall
	.2byte 0

AzaleaTown_MapScript_Hide_Silver:
	setflag FLAG_HIDE_AZALEA_TOWN_SILVER
	removeobject LOCALID_AZALEA_TOWN_SILVER
	end

AzaleaTown_EventScript_Trigger:: @flagheap
	setflag FLAG_VISITED_AZALEA_TOWN
	setflag FLAG_HIDE_AZALEA_TOWN_SLOWPOKE
	setflag FLAG_HIDE_AZALEA_TOWN_SILVER
	setflag FLAG_HIDE_KURT_2
	setflag FLAG_HIDE_ILEX_FOREST_APPRENTICE
	setflag FLAG_HIDE_ILEX_FOREST_MASTER
	setflag FLAG_HIDE_ILEX_FOREST_FARFETCHD_4
	setflag FLAG_HIDE_ILEX_FOREST_FARFETCHD_3
	setflag FLAG_HIDE_ILEX_FOREST_FARFETCHD_2
	setflag FLAG_HIDE_ILEX_FOREST_FARFETCHD_1
	setflag FLAG_HIDE_CELEBI
	setflag FLAG_HIDE_ILEX_FOREST_KURT
	setflag FLAG_HIDE_AZALEA_TOWN_KURT
	setflag FLAG_HIDE_AZALEA_ARIADOS_LEFT
	setflag FLAG_HIDE_AZALEA_ARIADOS_MID
	setflag FLAG_HIDE_AZALEA_ARIADOS_RIGHT
	

	clearflag FLAG_HIDE_ILEX_FOREST_KIMONO
	clearflag FLAG_ITEM_SLOWPOKE_WELL_RAIN_DANCE
	clearflag FLAG_HIDE_AZALEA_TOWN_ROCKETS
	clearflag FLAG_HIDE_AZALEA_TOWN_WELL_ROCKET
	clearflag FLAG_HIDE_KURT_1
	clearflag FLAG_GOT_CHARCOAL
	clearflag FLAG_HIDE_AZALEA_TOWN_FARFETCHD
	clearflag FLAG_HIDE_AZALEA_TOWN_CUT_MASTER
	clearflag FLAG_MOVE_TUTOR_TAUGHT_HEADBUTT

	removeitem ITEM_HM_SURF
	setvar VAR_AZALEA_TOWN_STATE, 1
	end

AzaleaTown_EventScript_Rocket1::
	lock
	faceplayer
	msgbox AzaleaTown_Text_Rocket1, MSGBOX_DEFAULT
	closemessage
	release
	end

AzaleaTown_EventScript_Rocket2::
	lock
	faceplayer
	msgbox AzaleaTown_Text_Rocket2, MSGBOX_DEFAULT
	closemessage
	release
	end

AzaleaTown_EventScript_Gramps::
	lock
	faceplayer
	goto_if_set FLAG_HIDE_AZALEA_TOWN_ROCKETS, AzaleaTown_EventScript_Gramps2
	msgbox AzaleaTown_Text_GrampsBefore, MSGBOX_DEFAULT
	closemessage
	release
	end

AzaleaTown_EventScript_Gramps2::
	msgbox AzaleaTown_Text_GrampsAfter, MSGBOX_DEFAULT
	closemessage
	release
	end

AzaleaTown_EventScript_Lass::
	lock
	faceplayer
	msgbox AzaleaTown_Text_Teacher, MSGBOX_DEFAULT
	closemessage
	release
	end

AzaleaTown_EventScript_Youngster::
	lock
	faceplayer
	msgbox AzaleaTown_Text_Youngster, MSGBOX_DEFAULT
	closemessage
	release
	end

AzaleaTown_EventScript_Slowpoke::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_NORMAL
	msgbox AzaleaTown_Text_Slowpoke1, MSGBOX_DEFAULT
	waitmoncry
	release
	end


AzaleaTown_EventScript_GymSign::
	lock
	msgbox AzaleaTown_Text_GymSign, MSGBOX_SIGN
	closemessage
	release
	end

AzaleaTown_EventScript_KurtSign::
	lock
	msgbox AzaleaTown_Text_KurtsHouseSign, MSGBOX_SIGN
	closemessage
	release
	end

AzaleaTown_EventScript_KilnSign::
	lock
	msgbox AzaleaTown_Text_CharcoalKilnSign, MSGBOX_SIGN
	closemessage
	release
	end

AzaleaTown_EventScript_IlexSign::
	lock
	msgbox AzaleaTown_Text_IlexForestSign, MSGBOX_SIGN
	closemessage
	release
	end

AzaleaTown_EventScript_WellSign::
	lock
	msgbox AzaleaTown_Text_SlowpokeWellSign, MSGBOX_SIGN
	closemessage
	release
	end

AzaleaTown_EventScript_AzaleaSign::
	lock
	msgbox AzaleaTown_Text_Sign, MSGBOX_SIGN
	closemessage
	release
	end

AzaleaTown_EventScript_SilverTriggerTop::
	lock
	clearflag FLAG_HIDE_AZALEA_TOWN_SILVER
	addobject LOCALID_AZALEA_TOWN_SILVER
	playbgm MUS_HG_ENCOUNTER_RIVAL, FALSE
	applymovement LOCALID_AZALEA_TOWN_SILVER, AzaleaTown_Movement_Silver_EnterTop
	waitmovement 0
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	msgbox AzaleaTown_Text_RivalBefore, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_STARTER_MON, 0, AzaleaTown_Silver_Battle_Cyndaquil
	call_if_eq VAR_STARTER_MON, 1, AzaleaTown_Silver_Battle_Totodile
	call_if_eq VAR_STARTER_MON, 2, AzaleaTown_Silver_Battle_Chikorita
	msgbox AzaleaTown_Text_RivalAfter, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, AzaleaTown_Movement_Player_LeaveTop
	waitmovement 0
	applymovement LOCALID_AZALEA_TOWN_SILVER, AzaleaTown_Movement_Silver_LeaveTop
	waitmovement 0
	playse SE_EXIT
	setflag FLAG_HIDE_AZALEA_TOWN_SILVER
	removeobject LOCALID_AZALEA_TOWN_SILVER
	setvar VAR_AZALEA_TOWN_STATE, 6
	fadedefaultbgm
	release
	end

AzaleaTown_EventScript_SilverTriggerBot::
	lock
	clearflag FLAG_HIDE_AZALEA_TOWN_SILVER
	addobject LOCALID_AZALEA_TOWN_SILVER
	playbgm MUS_HG_ENCOUNTER_RIVAL, FALSE
	applymovement LOCALID_AZALEA_TOWN_SILVER, AzaleaTown_Movement_Silver_EnterBot
	waitmovement 0
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	msgbox AzaleaTown_Text_RivalBefore, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_STARTER_MON, 0, AzaleaTown_Silver_Battle_Cyndaquil
	call_if_eq VAR_STARTER_MON, 1, AzaleaTown_Silver_Battle_Totodile
	call_if_eq VAR_STARTER_MON, 2, AzaleaTown_Silver_Battle_Chikorita
	playbgm MUS_HG_RIVAL_EXIT, FALSE
	msgbox AzaleaTown_Text_RivalAfter, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, AzaleaTown_Movement_Player_LeaveBot
	waitmovement 0
	applymovement LOCALID_AZALEA_TOWN_SILVER, AzaleaTown_Movement_Silver_LeaveBot
	waitmovement 0
	playse SE_EXIT
	setflag FLAG_HIDE_AZALEA_TOWN_SILVER
	removeobject LOCALID_AZALEA_TOWN_SILVER
	setvar VAR_AZALEA_TOWN_STATE, 6
	fadedefaultbgm
	release
	end

AzaleaTown_Silver_Battle_Cyndaquil::
	trainerbattle_no_intro TRAINER_RIVAL_CYNDAQUIL_2_HNS, AzaleaTown_Text_RivalWin
	return

AzaleaTown_Silver_Battle_Totodile::
	trainerbattle_no_intro TRAINER_RIVAL_TOTODILE_2_HNS, AzaleaTown_Text_RivalWin
	return

AzaleaTown_Silver_Battle_Chikorita::
	trainerbattle_no_intro TRAINER_RIVAL_CHIKORITA_2_HNS, AzaleaTown_Text_RivalWin
	return


AzaleaTown_EventScript_GSBall::
	lock
	applymovement OBJ_EVENT_ID_PLAYER, AzaleaTown_Movement_PlayerGSBall
	waitmovement 0
	clearflag FLAG_HIDE_AZALEA_TOWN_KURT
	addobject LOCALID_AZALEA_TOWN_KURT_GS
	opendoor 19, 11
	waitdooranim
	waitmovement 0
	closedoor 19, 11
	waitdooranim
	applymovement LOCALID_AZALEA_TOWN_KURT_GS, AzaleaTown_Movement_Kurt2
	playse SE_M_PETAL_DANCE
	waitmovement 0
	msgbox AzaleaTown_Text_Kurt1, MSGBOX_DEFAULT
	closemessage
	playse SE_M_PETAL_DANCE
	msgbox AzaleaTown_Text_Kurt2, MSGBOX_DEFAULT
	giveitem ITEM_GS_BALL
	waitse
	playse SE_M_PETAL_DANCE
	turnobject LOCALID_AZALEA_TOWN_KURT_GS, DIR_WEST
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	playse SE_M_PETAL_DANCE
	waitse
	turnobject LOCALID_AZALEA_TOWN_KURT_GS, DIR_SOUTH
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	msgbox AzaleaTown_Text_Kurt3, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_AZALEA_TOWN_KURT_GS, AzaleaTown_Movement_KurtLeave
	delay 60
	opendoor 19, 11
	waitdooranim
	waitmovement 0
	setflag FLAG_HIDE_AZALEA_TOWN_KURT
	removeobject LOCALID_AZALEA_TOWN_KURT_GS
	closedoor 19, 11
	waitdooranim
	setvar VAR_AZALEA_TOWN_STATE, 9
	release
	end

AzaleaTown_Movement_Silver_EnterTop:
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end

AzaleaTown_Movement_Silver_EnterBot:
	walk_fast_down
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end

AzaleaTown_Movement_Silver_LeaveTop:
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end

AzaleaTown_Movement_Silver_LeaveBot:
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_up
	walk_fast_left
	step_end

AzaleaTown_Movement_Player_LeaveTop:
	lock_facing_direction
	walk_fast_down
	unlock_facing_direction
	face_up
	step_end

AzaleaTown_Movement_Player_LeaveBot:
	lock_facing_direction
	walk_fast_up
	unlock_facing_direction
	face_down
	step_end

AzaleaTown_Movement_Kurt1:
	walk_down
	step_end

AzaleaTown_Movement_Kurt2:
	walk_down
	walk_down
	walk_down
	face_right
	delay_8
	face_left
	delay_8
	face_down
	step_end

AzaleaTown_Movement_PlayerGSBall:
	walk_down
	walk_down
	walk_down
	face_left
	delay_16
	face_right
	delay_8
	face_up
	step_end

AzaleaTown_Movement_KurtLeave:
	walk_up
	walk_up
	walk_up
	step_end

AzaleaTown_Text_RivalBefore:
	.string "…תגיד לי משהו.\p"
	.string "זה נכון שצוות רוקט חזר?\p"
	.string "מה? ניצחת אותם? הא! תפסיק לשקר.\p"
	.string "אתה לא צוחק? אז בוא נראה כמה אתה טוב.$"

AzaleaTown_Text_RivalWin:
	.string "…המפף! פוקימונים חסרי תועלת!\p"
	.string "תקשיב לי. ניצחת רק כי\n"
	.string "הפוקימונים שלי היו חלשים.$"

AzaleaTown_Text_RivalAfter:
	.string "אני שונא חלשים.\p"
	.string "פוקימונים, מאמנים. לא משנה מי או מה.\p"
	.string "אני אהיה חזק ואמחק את החלשים.\p"
	.string "זה נכון גם לגבי צוות רוקט.\p"
	.string "בקבוצה הם עושים את עצמם\n"
	.string "גדולים וקשוחים.\p"
	.string "אבל לבד, הם חלשים. אני שונא את כולם.\p"
	.string "אל תעמוד לי בדרך.\n"
	.string "חלשלוש כמוך רק מסיח את דעתי.$"

AzaleaTown_Text_RivalLoss:
	.string "…Humph! I knew you were lying.$"

AzaleaTown_Text_Rocket1:
	.string "מסוכן להיכנס לשם,\n"
	.string "אז אני עומד על המשמר.\p"
	.string "נכון שאני שומרוני טוב?$"

AzaleaTown_Text_Rocket2:
	.string "שמעת על זנב סלופוק?\n"
	.string "אומרים שהוא טעים!\p"
	.string "נכון שאתה שמח שסיפרתי לך?$"

AzaleaTown_Text_GrampsBefore:
	.string "הסלופוק נעלמו מהעיירה…\p"
	.string "שמעתי שמוכרים את הזנבות שלהם איפשהו.$"

AzaleaTown_Text_GrampsAfter:
	.string "הסלופוק חזרו.\p"
	.string "כמו שאני מכיר אותם,\n"
	.string "אולי הם סתם התבטלו איפשהו.$"

AzaleaTown_Text_Teacher:
	.string "באת לבקש מקורט\n"
	.string "להכין לך כמה כדורים?\p"
	.string "הרבה אנשים באים בדיוק בשביל זה.$"

AzaleaTown_Text_Youngster:
	.string "אם חוצים את אזייליה,\n"
	.string "מגיעים ליער אילקס.\p"
	.string "אבל העצים הדקים האלה\n"
	.string "חוסמים את המעבר לגמרי.\p"
	.string "הפוקימון של איש הפחם יכול\n"
	.string "לכרות עצים בעזרת חיתוך.$"

AzaleaTown_Text_Slowpoke1:
	.string "סלופוק:..........\p"
	.string "...............פיהוק?$"

AzaleaTown_Text_Kurt1:
	.string "יער אילקס סוער!\p"
	.string "מה קורה שם?$"

AzaleaTown_Text_Kurt2:
	.string "{PLAYER}, הנה, אני מחזיר לך את כדור GS!$"

AzaleaTown_Text_Kurt3:
	.string "תוכל ללכת לבדוק למה\n"
	.string "יער אילקס כל כך סוער?$"

AzaleaTown_Text_Sign:
	.string "העיירה אזייליה\p"
	.string "כאן אנשים ופוקימונים חיים\n"
	.string "בהרמוניה שמחה.$"

AzaleaTown_Text_KurtsHouseSign:
	.string "הבית של קורט$"

AzaleaTown_Text_GymSign:
	.string "העיירה אזייליה\n"
	.string "מכון הפוקימון\p"
	.string "מנהיג: באגסי\p"
	.string "האנציקלופדיה המהלכת\n"
	.string "של פוקימוני חרק$"

AzaleaTown_Text_SlowpokeWellSign:
	.string "באר סלופוק\p"
	.string "ידועה גם בשם באר מביאת הגשם.\p"
	.string "המקומיים מאמינים שפיהוק\n"
	.string "של סלופוק מזמן גשם.\p"
	.string "לפי הרשומות, פיהוק של סלופוק\n"
	.string "סיים בצורת לפני 400 שנה.$"

AzaleaTown_Text_CharcoalKilnSign:
	.string "כבשן הפחם$"

AzaleaTown_Text_IlexForestSign:
	.string "יער אילקס\p"
	.string "הכניסה דרך השער.$"
