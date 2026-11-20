Route25_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route25_MapScript_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route25_MapScript_OnTransition::
	callnative SetTimeBasedEncounters
	goto_if_eq VAR_SUICUNE_ENCOUNTERS, 7, Route25_EventScript_SetSuicuneSceneMid
	end

Route25_EventScript_SetSuicuneSceneMid::
	setobjectxyperm LOCALID_ROUTE25_EUSINE, 98, 14
	end

Route25_EventScript_MistyRematch::
    lock
    faceplayer
    msgbox Route25_Text_Misty, MSGBOX_DEFAULT
    closemessage
    fadescreenswapbuffers FADE_TO_BLACK
    setflag FLAG_HIDE_CAPE_MISTY
    removeobject LOCALID_CAPE_MISTY
    fadescreenswapbuffers FADE_FROM_BLACK
    clearflag FLAG_HIDE_DOJO_MISTY
    release
    end

Route25_Text_Misty:
    .string "מיסטי: אני אוהבת את השקיעה כאן!\p"
    .string "היא נותנת לי אומץ להמשיך,\n"
    .string "אתה יודע?\p"
    .string "טוב!\p"
    .string "אם אתה מוכן להירטב באמת,\n"
    .string "בוא לפגוש אותי בדוג'ו הלחימה!$"

Route25_EventScript_Dudley::
	trainerbattle_single TRAINER_DUDLEY_HNS, Route25_Text_SchoolboyDudleySeen, Route25_Text_SchoolboyDudleyBeaten
	msgbox Route25_Text_SchoolboyDudleyAfter, MSGBOX_AUTOCLOSE
	end

Route25_EventScript_Ellen::
	trainerbattle_single TRAINER_ELLEN_HNS, Route25_Text_LassEllenSeen, Route25_Text_LassEllenBeaten
	msgbox Route25_Text_LassEllenAfter, MSGBOX_AUTOCLOSE
	end

Route25_EventScript_Joe::
	trainerbattle_single TRAINER_JOE_HNS, Route25_Text_SchoolboyJoeSeen, Route25_Text_SchoolboyJoeBeaten
	msgbox Route25_Text_SchoolboyJoeAfter, MSGBOX_AUTOCLOSE
	end

Route25_EventScript_Laura::
	trainerbattle_single TRAINER_LAURA_HNS, Route25_Text_LassLauraSeen, Route25_Text_LassLauraBeaten
	msgbox Route25_Text_LassLauraAfter, MSGBOX_AUTOCLOSE
	end

Route25_EventScript_Lloyd::
	trainerbattle_single TRAINER_LLOYD_HNS, Route25_Text_CamperLloydSeen, Route25_Text_CamperLloydBeaten
	msgbox Route25_Text_CamperLloydAfter, MSGBOX_AUTOCLOSE
	end

Route25_EventScript_Shannon::
	trainerbattle_single TRAINER_SHANNON_HNS, Route25_Text_LassShannonSeen, Route25_Text_LassShannonBeaten
	msgbox Route25_Text_LassShannonAfter, MSGBOX_AUTOCLOSE
	end

Route25_EventScript_Pat::
	trainerbattle_single TRAINER_PAT_HNS, Route25_Text_SupernerdPatSeen, Route25_Text_SupernerdPatBeaten
	msgbox Route25_Text_SupernerdPatAfter, MSGBOX_AUTOCLOSE
	end

Route25_EventScript_Kevin::
	lock
	faceplayer
	goto_if_set FLAG_ROUTE25_GOT_NUGGET, Route25_EventScript_KevinAfter
	msgbox Route25_Text_CooltrainerKevinNugget, MSGBOX_DEFAULT
	giveitem ITEM_BIG_NUGGET
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_ROUTE25_GOT_NUGGET
	msgbox Route25_Text_CooltrainerKevinSeen, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_KEVIN_HNS, Route25_Text_CooltrainerKevinBeaten
	msgbox Route25_Text_CooltrainerKevinAfter, MSGBOX_DEFAULT
	closemessage
	release
	end
Route25_EventScript_KevinAfter::
	msgbox Route25_Text_CooltrainerKevinAfter, MSGBOX_NPC
	end

Route25_EventScript_BillsHouseSign::
	msgbox Route25_Text_BillsHouseSign, MSGBOX_SIGN
	end

Route25_Trigger_MistyRight::
	lock
	turnobject LOCALID_ROUTE25_MISTY, DIR_SOUTH
	delay 40
	turnobject LOCALID_ROUTE25_MAN, DIR_SOUTH
	playse SE_PIN
	applymovement2 LOCALID_ROUTE25_MAN, Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_ROUTE25_MAN
	applymovement2 LOCALID_ROUTE25_MAN, Route25_Movement_ManLeaveRight
	waitmovement 0
	applymovement2 LOCALID_ROUTE25_MISTY, Route25_Movement_MistyWalkToPlayerRight
	waitmovement 0
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	goto Route25_EventScript_Misty
Route25_Trigger_MistyLeft::
	lock
	turnobject LOCALID_ROUTE25_MISTY, DIR_SOUTH
	delay 40
	turnobject LOCALID_ROUTE25_MAN, DIR_SOUTH
	playse SE_PIN
	applymovement2 LOCALID_ROUTE25_MAN, Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_ROUTE25_MAN
	applymovement2 LOCALID_ROUTE25_MAN, Route25_Movement_ManLeaveLeft
	waitmovement 0
	applymovement2 LOCALID_ROUTE25_MISTY, Route25_Movement_MistyWalkToPlayerLeft
	waitmovement 0
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	goto Route25_EventScript_Misty
Route25_EventScript_Misty::
	msgbox Route25_Text_MistyDate, MSGBOX_DEFAULT
	closemessage
	applymovement2 LOCALID_ROUTE25_MISTY, Route25_Movement_MistyLeave
	waitmovement 0
	removeobject LOCALID_ROUTE25_MISTY
	removeobject LOCALID_ROUTE25_MAN
	setflag FLAG_HIDE_ROUTE25_MISTY
	clearflag FLAG_HIDE_CERULEAN_GYM_TRAINERS
	setflag FLAG_HIDE_CERULEAN_GYM_POKEMON
	setvar VAR_CERULEAN_CITY_STATE, 3
	release
	end

Route25_Trigger_SuicuneLeft::
	lock
	playse SE_PIN
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
	waitmovement OBJ_EVENT_ID_PLAYER
	playmoncry SPECIES_SUICUNE, CRY_MODE_NORMAL
	applymovement LOCALID_ROUTE25_SUICUNE, Route25_Movement_Suicune1
	playse SE_LEDGE
	waitse
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkRight1
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Route25_Movement_WalkToSuicune
	waitmovement 0
	goto Route25_EventScript_SuicuneMerge
Route25_Trigger_SuicuneRight::
	lock
	playse SE_PIN
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
	waitmovement OBJ_EVENT_ID_PLAYER
	playmoncry SPECIES_SUICUNE, CRY_MODE_NORMAL
	applymovement LOCALID_ROUTE25_SUICUNE, Route25_Movement_Suicune1
	playse SE_LEDGE
	waitse
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Route25_Movement_WalkToSuicune
	waitmovement 0
	goto Route25_EventScript_SuicuneMerge
Route25_EventScript_SuicuneMerge::
	clearflag FLAG_HIDE_ROUTE25_EUSINE
	addobject LOCALID_ROUTE25_EUSINE
	applymovement LOCALID_ROUTE25_EUSINE, Route25_Movement_EusineEnter
	waitmovement 0
	turnobject OBJ_EVENT_ID_PLAYER, DIR_SOUTH
	msgbox Route25_Text_Eusine1, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ROUTE25_EUSINE, Route25_Movement_EusineSide
	waitmovement 0
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	msgbox Route25_Text_Eusine2, MSGBOX_DEFAULT
	closemessage
	setvar VAR_SUICUNE_ENCOUNTERS, 7
	release
	end
	
Route25_Trigger_SuicuneRightRight::
	lock
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkLeft1
	waitmovement 0
	goto Route25_Trigger_SuicuneRight
Route25_Trigger_SuicuneLeftLeft::
	lock
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkRight1
	waitmovement 0
	goto Route25_Trigger_SuicuneLeft

Route25_Text_Eusine1:
	.string "יוסין: הוף, הוף…\n"
	.string "אני… לא משתווה לך.\p"
	.string "…כפי שחזיתי.\n"
	.string "…………\p"
	.string "… קדימה.\p"
	.string "מאז שפגשתי אותך\n"
	.string "במגדל השרוף בעיר אקרוטיק,\p"
	.string "איכשהו ידעתי שסואיקון\n"
	.string "יבחר בך.$"

Route25_Text_Eusine2:
	.string "תסתכל עליו!\p"
	.string "סואיקון מחכה לך!\p"
	.string "הוא חיכה לקרב עם מאמן ראוי,\n"
	.string "שבידיו יוכל להפקיד את עצמו.$"

Route25_Text_Eusine3:
	.string "{PLAYER}…\n"
	.string "שניכם באמת מדהימים…\p"
	.string "מעולם לא ראיתי קרב\n"
	.string "כל כך עוצמתי!\p"
	.string "אין לי חרטות…\p"
	.string "היה שלום, סואיקון!\n"
	.string "היה שלום… {PLAYER}!$"

Route25_EventScript_Eusine::
	msgbox Route25_Text_Eusine2, MSGBOX_NPC
	end

Route25_EventScript_Suicune::
	lock
	faceplayer
	playmoncry SPECIES_SUICUNE, CRY_MODE_NORMAL
	applymovement LOCALID_ROUTE25_SUICUNE, Route25_Movement_Suicune1
	playse SE_LEDGE
	waitse
	waitmovement 0
	playmoncry SPECIES_SUICUNE, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	seteventmon SPECIES_SUICUNE, 50
	special BattleSetup_StartLegendaryBattle
	waitstate
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, Route25_EventScript_SuicuneRan
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_ROUTE25_SUICUNE
	setflag FLAG_HIDE_ROUTE25_SUICUNE
	fadescreenswapbuffers FADE_FROM_BLACK
	goto_if_ge VAR_SUICUNE_ENCOUNTERS, 8, Route25_EventScript_SuicunePostGame
	getplayerxy VAR_TEMP_0, VAR_TEMP_1
	call_if_eq VAR_TEMP_0, 99, Route25_AdjustPlayer
	call_if_eq VAR_TEMP_0, 100, Route25_AdjustPlayerTwice
	turnobject OBJ_EVENT_ID_PLAYER, DIR_SOUTH
	turnobject LOCALID_ROUTE25_EUSINE, DIR_NORTH
	msgbox Route25_Text_Eusine3, MSGBOX_DEFAULT
	closemessage
	applymovement2 LOCALID_ROUTE25_EUSINE, Route25_Movement_EusineLeave
	waitmovement 0
	removeobject LOCALID_ROUTE25_EUSINE
	setflag FLAG_HIDE_ROUTE25_EUSINE
	clearflag FLAG_HIDE_CELADON_EUSINE
	setvar VAR_SUICUNE_ENCOUNTERS, 8
	release
	end

Route25_EventScript_SuicuneRan::
	release
	end

Route25_AdjustPlayer::
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkLeft1
	waitmovement 0
	return

Route25_AdjustPlayerTwice::
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkLeft1
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkLeft1
	waitmovement 0
	return

Route25_EventScript_SuicunePostGame::
	release
	end

Route25_Movement_EusineLeave:
	walk_down
	walk_down
	walk_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end

Route25_Movement_EusineSide:
	walk_slow_left
	walk_slow_up
	step_end

Route25_Movement_EusineEnter:
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_up
	walk_slow_up
	step_end

Route25_Movement_Suicune1:
	jump_in_place_down
	step_end

Route25_Movement_WalkToSuicune:
	walk_up
	walk_up
	step_end

Route25_Movement_MistyLeave:
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

Route25_Movement_ManLeaveRight:
	walk_fast_left
	walk_fast_left
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end
Route25_Movement_ManLeaveLeft:
	walk_fast_left
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end

Route25_Movement_MistyWalkToPlayerRight:
	walk_fast_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	face_right
	step_end
Route25_Movement_MistyWalkToPlayerLeft:
	walk_fast_left
	walk_down
	walk_down
	walk_down
	walk_down
	face_left
	step_end

Route25_Text_MistyDate:
	.string "מיסטי: אוף! למה היית חייב\n"
	.string "להופיע ולהפריע לנו דווקא עכשיו?\p"
	.string "אתה יודע איך קוראים\n"
	.string "לאנשים כמוך?\p"
	.string "נודניקים! שמעת נכון,\n"
	.string "נודניק!\p"
	.string "…\p"
	.string "…אה? התגים האלה שלך…\n"
	.string "אלה תגי מכון של ג'וטו?\p"
	.string "אם יש לך שמונה, אתה בטח\n"
	.string "טוב.\p"
	.string "אז בסדר. בוא למכון סרוליאן.\p"
	.string "אשמח להתמודד מולך.\p"
	.string "אני מיסטי, מנהיגת המכון\n"
	.string "בסרוליאן.$"

Route25_Text_SchoolboyDudleySeen:
	.string "נצח את כל ששת המאמנים שלנו\n"
	.string "ותזכה בפרס מדהים!\p"
	.string "חושב שיש לך מה שצריך?$"

Route25_Text_SchoolboyDudleyBeaten:
	.string "וואו! יופי של קרב.$"

Route25_Text_SchoolboyDudleyAfter:
	.string "עשיתי כמיטב יכולתי.\n"
	.string "אין לי חרטות.$"

Route25_Text_LassEllenSeen:
	.string "אני השנייה.\n"
	.string "עכשיו זה רציני!$"

Route25_Text_LassEllenBeaten:
	.string "איך יכולתי להפסיד?$"

Route25_Text_LassEllenAfter:
	.string "עשיתי כמיטב יכולתי.\n"
	.string "אין לי חרטות.$"

Route25_Text_SchoolboyJoeSeen:
	.string "הנה מספר 3!\n"
	.string "אני לא אהיה קל.$"

Route25_Text_SchoolboyJoeBeaten:
	.string "איי! נמחצתי לגמרי!$"

Route25_Text_SchoolboyJoeAfter:
	.string "עשיתי כמיטב יכולתי.\n"
	.string "אין לי חרטות.$"

Route25_Text_LassLauraSeen:
	.string "אני מספר 4!\n"
	.string "מתחיל להתעייף?$"

Route25_Text_LassLauraBeaten:
	.string "גם אני הפסדתי…$"

Route25_Text_LassLauraAfter:
	.string "עשיתי כמיטב יכולתי.\n"
	.string "אין לי חרטות.$"

Route25_Text_CamperLloydSeen:
	.string "אוקיי! אני מספר 5.\n"
	.string "אני אמחץ אותך!$"

Route25_Text_CamperLloydBeaten:
	.string "וואו! זה יותר מדי.$"

Route25_Text_CamperLloydAfter:
	.string "עשיתי כמיטב יכולתי.\n"
	.string "אין לי חרטות.$"

Route25_Text_LassShannonSeen:
	.string "אני האחרונה בתור, אבל תאמין לי,\n"
	.string "אני קשוחה!$"

Route25_Text_LassShannonBeaten:
	.string "אתה צוחק עליי.$"

Route25_Text_LassShannonAfter:
	.string "עשיתי כמיטב יכולתי.\n"
	.string "אין לי חרטות.$"

Route25_Text_SupernerdPatSeen:
	.string "מופופופו…\p"
	.string "אין לי שום קשר לשישיית\n"
	.string "המאמנים.\p"
	.string "חיכיתי כאן כדי לנצח אותך\n"
	.string "כשתהיה סחוט מכל הקרבות.$"

Route25_Text_SupernerdPatBeaten:
	.string "אתה בכלל לא עייף?$"

Route25_Text_SupernerdPatAfter:
	.string "סליחה… אני לא ארמה\n"
	.string "יותר…$"

Route25_Text_CooltrainerKevinNugget:
	.string "נאלצת להתמודד עם קרב נוסף\n"
	.string "שלא ציפית לו, ובכל זאת ניצחת.\p"
	.string "כמו שהובטח, זכית בפרס.$"

Route25_Text_CooltrainerKevinSeen:
	.string "אבל אחרי שראיתי איך אתה נלחם,\n"
	.string "אני רוצה לראות איך אני אסתדר.\p"
	.string "מה אתה אומר? תן לי להתמודד\n"
	.string "מולך.$"

Route25_Text_CooltrainerKevinBeaten:
	.string "מעולם לא היה לי קרב\n"
	.string "כל כך טוב!$"

Route25_Text_CooltrainerKevinAfter:
	.string "זה היה קרב נהדר!\p"
	.string "אתה והפוקימונים שלך באמת\n"
	.string "יוצאים מן הכלל!$"

Route25_Text_BillsHouseSign:
	.string "קוטג' ימי\n"
	.string "הבית של ביל$"

