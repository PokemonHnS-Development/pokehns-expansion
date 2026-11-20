NewSinjoh_House3_hns_MapScripts::
    map_script MAP_SCRIPT_ON_FRAME_TABLE, NewSinjoh_House3_OnFrame
    map_script MAP_SCRIPT_ON_LOAD, NewSinjoh_House3_OnTransition
    .byte 0


NewSinjoh_House3_OnTransition::
    call_if_ge VAR_NOBLE_TYPHLOSION, 2, NewSinjoh_House3_AddStairs
    end

NewSinjoh_House3_AddStairs::
    setmetatile 38, 13, 0x015, TRUE
	setmetatile 38, 14, 0x005, TRUE
	setmetatile 38, 15, 0x00D, TRUE
	setmetatile 39, 14, 0x006, TRUE
	setmetatile 39, 15, 0x00E, TRUE
	setmetatile 40, 14, 0x007, FALSE
	setmetatile 40, 15, 0x00F, FALSE
    return

NewSinjoh_House3_OnFrame:
    map_script_2 VAR_TEMP_0, 0, NewSinjoh_HauntedHouse_EventScript_Enter
	.2byte 0

NewSinjoh_HauntedHouse_EventScript_Enter::
    setvar VAR_TEMP_0, 1
    goto_if_eq VAR_NOBLE_TYPHLOSION, 1, NewSinjoh_HauntedHouse_EventScript_StartScary
    goto_if_eq VAR_NOBLE_TYPHLOSION, 0, NewSinjoh_HauntedHouse_EventScript_TooEarly
    end

NewSinjoh_HauntedHouse_EventScript_TooEarly::
    msgbox NewSinjoh_HauntedHouse_Text_TooEarlyNoReaction, MSGBOX_AUTOCLOSE
    release
    end

NewSinjoh_HauntedHouse_Text_TooEarlyNoReaction:
    .string "מורגשת כאן נוכחות מוזרה…\p"
    .string "אבל אין שום תגובה.$"

NewSinjoh_HauntedHouse_EventScript_StartScary::
    msgbox NewSinjoh_HauntedHouse_Text_StartScary, MSGBOX_AUTOCLOSE
    playse SE_M_DETECT
    getplayerxy VAR_TEMP_1, VAR_TEMP_2
	dofieldeffectsparkle VAR_TEMP_1, VAR_TEMP_2, 0
	waitfieldeffect FLDEFF_SPARKLE
    playse SE_PIN
    applymovement2 LOCALID_PLAYER, Common_Movement_ExclamationMark
    delay 55
    waitmovement LOCALID_PLAYER
    msgbox SinjohRuins_Lab_Text_PlayFlute, MSGBOX_YESNO
    closemessage
    goto_if_eq VAR_RESULT, FALSE, SinjohRuins_Lab_EventScript_NoOp
    playbgm MUS_DP_AZURE_FLUTE, FALSE
    delay 200
    fadedefaultbgm    
    special SpawnCameraObject
    applymovement OBJ_EVENT_ID_CAMERA, NewSinjoh_House3_Movement_CameraPanLeft
    waitmovement 0
    setvar VAR_0x8004, 2  @ vertical pan
    setvar VAR_0x8005, 2  @ horizontal pan
    setvar VAR_0x8006, 20  @ num shakes
    setvar VAR_0x8007, 4  @ shake delay
    special ShakeCamera
    waitstate
    call NewSinjoh_House3_AddStairs
    special DrawWholeMapView
    playse SE_CLICK
    applymovement2 OBJ_EVENT_ID_CAMERA, NewSinjoh_House3_Movement_CameraPanRight
    waitmovement 0
    special RemoveCameraObject
    addobject LOCALID_NEWSINJOH_HOUSE3_NOBLE_TYPHLOSION
    clearflag FLAG_HIDE_NEWSINJOH_HOUSE3_NOBLE_TYPHLOSION
    setvar VAR_NOBLE_TYPHLOSION, 2
    release
    end

NewSinjoh_House3_EventScript_NobleTyphlosion::
	lock
	faceplayer
	playmoncry SPECIES_TYPHLOSION_HISUI, CRY_MODE_ENCOUNTER
	waitmoncry
	setwildbossbattle species=SPECIES_TYPHLOSION_HISUI, level=80, item=ITEM_SPOOKY_PLATE, move1_1=MOVE_INFERNAL_PARADE, move1_2=MOVE_LAVA_PLUME, move1_3=MOVE_CONFUSE_RAY move1_4=MOVE_SOLAR_BEAM
	settotemboost B_POSITION_OPPONENT_LEFT, 0, 2, 0, 1, 2, 0
	setflag FLAG_NO_WILD_CATCHING
	setflag FLAG_NO_WILD_RUNNING
	setflag FLAG_SMART_WILD_AI
	setflag FLAG_NO_SHINY
    dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, NewSinjoh_House3_EventScript_NobleTyphlosionRan
    bufferspeciesname STR_VAR_1, SPECIES_TYPHLOSION_HISUI
    msgbox SinjohRuins_Lab_Text_DropedItem, MSGBOX_DEFAULT
    giveitem ITEM_SPOOKY_PLATE
    addvar VAR_PLATECOUNTER, 1
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_NEWSINJOH_HOUSE3_NOBLE_TYPHLOSION
	setflag FLAG_HIDE_NEWSINJOH_HOUSE3_NOBLE_TYPHLOSION
	fadescreenswapbuffers FADE_FROM_BLACK
    call_if_eq VAR_PLATECOUNTER, 3, SinjohRuins_Lab_EventScript_3Plates
    call_if_eq VAR_PLATECOUNTER, 6, SinjohRuins_Lab_EventScript_6Plates
    call_if_eq VAR_PLATECOUNTER, 9, SinjohRuins_Lab_EventScript_9Plates
    call_if_eq VAR_PLATECOUNTER, 12, SinjohRuins_Lab_EventScript_12Plates
    call_if_eq VAR_PLATECOUNTER, 15, SinjohRuins_Lab_EventScript_15Plates
    call_if_eq VAR_PLATECOUNTER, 16, SinjohRuins_Lab_EventScript_16Plates
	clearflag FLAG_NO_WILD_CATCHING
	clearflag FLAG_NO_WILD_RUNNING
	clearflag FLAG_SMART_WILD_AI
	clearflag FLAG_NO_SHINY
	release
	end

NewSinjoh_House3_EventScript_NobleTyphlosionRan::
	clearflag FLAG_NO_WILD_CATCHING
	clearflag FLAG_NO_WILD_RUNNING
	clearflag FLAG_SMART_WILD_AI
	clearflag FLAG_NO_SHINY
	release
	end

NewSinjoh_House3_Movement_CameraPanLeft:
    walk_left
    walk_left
    walk_left
    walk_left
    walk_left
    step_end

NewSinjoh_House3_Movement_CameraPanRight:
    walk_right
    walk_right
    walk_right
    walk_right
    walk_right
    step_end

NewSinjoh_HauntedHouse_Text_StartScary:
    .string "מורגשת כאן נוכחות מוזרה…\p"
    .string "האם מישהו צופה בך?$"

NewSinjoh_HauntedHouse_EventScript_Log1::
    msgbox NewSinjoh_HauntedHouse_Text_Log1, MSGBOX_SIGN
    end

NewSinjoh_HauntedHouse_EventScript_Log2::
    msgbox NewSinjoh_HauntedHouse_Text_Log2, MSGBOX_SIGN
    end

NewSinjoh_HauntedHouse_EventScript_Log3::
    msgbox NewSinjoh_HauntedHouse_Text_Log3, MSGBOX_SIGN
    end

NewSinjoh_HauntedHouse_Text_Log1:
  	.string "יומן מחקר 9, מיום 20 בספטמבר 1975\p"
  	.string "הימים מתקצרים עכשיו\n"
  	.string "והרוח נעשית עזה.\p"
  	.string "תושבי הכפר קיבלו אותי בחום רב.\p"
  	.string "הם מרשים לי לגור כאן\n"
  	.string "בבקתה הזאת במשך החורף.\p"
  	.string "נראה שפעם גרה כאן משפחה.\n"
  	.string "המשפחה שלי עולה במחשבותיי תכופות.\p"
  	.string "אולי באביב יהיה לי האומץ\n"
  	.string "לחזור אליהם.$"

NewSinjoh_HauntedHouse_Text_Log2:
    .string "יומן מחקר 10, מיום 20 באוקטובר 1975\p"
    .string "המחשבות שלי נעשו קודרות.\p"
    .string "אולי זה בגלל חילופי העונות.\p"
    .string "תושבי הכפר ממשיכים לקבל אותי\n"
    .string "כאילו הייתי חלק מהם.\p"
    .string "אבל רגשות האשם שלי מונעים ממני\n"
    .string "להשיב להם באותה מידה.\p"
    .string "בזמן האחרון כמעט לא יצאתי מהבקתה.\p"
    .string "וכשהמשפחה שלי עולה בזיכרוני…\n"
    .string "הפנים שלהם השתנו…\p"
    .string "אני רואה רק את פני הפוקימונים\n"
    .string "שאבדו בחורבות…\p"
    .string "לפעמים נדמה לי שהפוקימונים\n"
    .string "כאן איתי.\p"
    .string "אני רואה אותם בהשתקפויות,\n"
    .string "המבט שלהם נעוץ בי.\p"
    .string "באביב יהיה טוב יותר.$"

NewSinjoh_HauntedHouse_Text_Log3:
    .string "יומן מחקר 10, מיום 1 בנובמבר 1975\p"
    .string "אני לא לבד כאן.\n"
    .string "אולי מעולם לא הייתי לבד.\p"
    .string "הפוקימונים איתי…\p"
    .string "הם כועסים עליי, נדמה לי.\p"
    .string "חפצים מושלכים, דלתות נטרקות.\p"
    .string "ארגזים כבדים חוסמים את דלת הכניסה.\p"
    .string "אבל האמת היא שיכולתי לעזוב\n"
    .string "אם רק הייתי רוצה.\p"
    .string "לא נשאר לי שום דבר אחר עכשיו.\p"
    .string "כבר כתבתי על משפחה, אבל המשפחה\n"
    .string "היחידה שבזיכרוני היא הפוקימונים…\p"
    .string "האוכל שלי אוזל,\n"
    .string "אבל רגשות האשם גוברים על הרעב.\p"
    .string "נדמה לי שאשאר כאן עוד זמן מה…$"
  
