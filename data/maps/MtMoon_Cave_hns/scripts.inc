MtMoon_Cave_hns_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, MtMoon_Cave_MapScript_OnFrame
	map_script MAP_SCRIPT_ON_TRANSITION, MtMoon_Cave_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

MtMoon_Cave_OnTransition: 
	callnative SetTimeBasedEncounters
	end


MtMoon_Cave_MapScript_OnFrame::
	map_script_2 VAR_PEWTER_CITY_STATE, 0, MtMoon_Cave_EventScript_Silver
	map_script_2 VAR_PEWTER_CITY_STATE, 1, MtMoon_Cave_EventScript_Silver
	.2byte 0

MtMoon_Cave_EventScript_Sign::
	msgbox MtMoon_Cave_Text_Sign, MSGBOX_SIGN
	end

MtMoon_Cave_EventScript_Silver::
	lock
	playbgm MUS_HG_ENCOUNTER_RIVAL, FALSE
	playse SE_PIN
	applymovement2 LOCALID_MTMOON_SILVER, Common_Movement_ExclamationMark
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	delay 60
	applymovement2 LOCALID_MTMOON_SILVER MtMoon_Cave_Movement_WalkToPlayer
	applymovement2 OBJ_EVENT_ID_PLAYER Common_Movement_WalkRight1
	waitmovement LOCALID_MTMOON_SILVER
	waitmovement OBJ_EVENT_ID_PLAYER
	msgbox MtMoon_Cave_Text_Rival_Before, MSGBOX_DEFAULT
	goto_if_eq VAR_STARTER_MON, 0, MtMoon_Cave_EventScript_Silver_Battle_Cyndaquil
	goto_if_eq VAR_STARTER_MON, 1, MtMoon_Cave_EventScript_Silver_Battle_Totodile
	goto_if_eq VAR_STARTER_MON, 2, MtMoon_Cave_EventScript_Silver_Battle_Chikorita
	release
	end

MtMoon_Cave_EventScript_Silver_Battle_Cyndaquil::
	trainerbattle_no_intro TRAINER_RIVAL_CYNDAQUIL_6_HNS, MtMoon_Cave_Text_Rival_Win
	goto MtMoon_Cave_EventScript_SilverAfterBattle

MtMoon_Cave_EventScript_Silver_Battle_Totodile::
	trainerbattle_no_intro TRAINER_RIVAL_TOTODILE_6_HNS, MtMoon_Cave_Text_Rival_Win
	goto MtMoon_Cave_EventScript_SilverAfterBattle

MtMoon_Cave_EventScript_Silver_Battle_Chikorita::
	trainerbattle_no_intro TRAINER_RIVAL_CHIKORITA_6_HNS, MtMoon_Cave_Text_Rival_Win
	goto MtMoon_Cave_EventScript_SilverAfterBattle

MtMoon_Cave_EventScript_SilverAfterBattle::
	playbgm MUS_HG_RIVAL_EXIT, FALSE
	msgbox MtMoon_Cave_Text_Rival_After, MSGBOX_DEFAULT
	closemessage
	applymovement2 LOCALID_MTMOON_SILVER, MtMoon_Cave_Movement_SilverLeave
	waitmovement 0
	removeobject LOCALID_MTMOON_SILVER
	setflag FLAG_HIDE_MTMOON_SILVER
	clearflag FLAG_HIDE_INDIGO_PLATEAU_SILVER
	setvar VAR_PEWTER_CITY_STATE, 2
	fadedefaultbgm
	release
	end

MtMoon_Cave_Movement_WalkToPlayer:
	walk_left
	walk_left
	walk_left
	step_end

MtMoon_Cave_Movement_SilverLeave:
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	step_end

MtMoon_Cave_Text_Rival_Before:
	.string "…………\p"
	.string "עבר הרבה זמן, {PLAYER}.\p"
	.string "…מאז שהפסדתי לך, חשבתי על מה\n"
	.string "שחסר לי עם הפוקימונים שלי…\p"
	.string "ומצאנו תשובה.\p"
	.string "{PLAYER}, עכשיו אנחנו נראה לך!$"

MtMoon_Cave_Text_Rival_Win:
	.string "…………\p"
	.string "חשבתי שגידלתי את הפוקימונים שלי\n"
	.string "כך שיהיו הכי טובים שאפשר…\p"
	.string "…אבל זה עדיין לא הספיק…$"

MtMoon_Cave_Text_Rival_After:
	.string "…………\p"
	.string "…ניצחת ביושר.\p"
	.string "אני מודה בזה. אבל זה לא הסוף.\p"
	.string "אני הולך להיות מאמן הפוקימונים\n"
	.string "הגדול ביותר אי פעם.\p"
	.string "כי החבר'ה האלה עומדים לצידי.\p"
	.string "…תקשיב, {PLAYER}.\p"
	.string "יום אחד אוכיח כמה אני טוב\n"
	.string "בכך שאנצח אותך.$"

MtMoon_Cave_Text_Rival_Loss:
	.string "..................................\p"
	.string "I've repaid my debt to you.\p"
	.string "With my POKéMON, I'm going to beat the\n"
	.string "CHAMPION and become the world's greatest\n"
	.string "trainer.$"

MtMoon_Cave_Text_Sign:
	.string "<- כיכר הר הירח$"
