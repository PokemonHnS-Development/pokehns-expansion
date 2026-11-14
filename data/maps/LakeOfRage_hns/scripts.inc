LakeOfRage_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, LakeOfRage_OnTransition
	.byte 0

LakeOfRage_OnTransition::
	setflag FLAG_VISITED_LAKE_OF_RAGE
	call_if_lt VAR_MAHOGANY_TOWN_STATE, 2, LakeOfRage_EventScript_HideLois
	goto_if_lt VAR_MAHOGANY_TOWN_STATE, 14, LakeOfRage_EventScript_SetHighTide
	special UpdateShoalTideFlag
	goto_if_set FLAG_SYS_LAKE_OF_RAGE_TIDE, LakeOfRage_EventScript_SetHighTide
	goto LakeOfRage_EventScript_SetLowTide

LakeOfRage_EventScript_SetLowTide::
	setweather WEATHER_NONE
	setmaplayoutindex LAYOUT_LAKE_OF_RAGE_LOW_TIDE_HNS
	end

LakeOfRage_EventScript_SetHighTide::
	setmaplayoutindex LAYOUT_LAKE_OF_RAGE_HNS
	goto_if_lt VAR_MAHOGANY_TOWN_STATE, 14, LakeOfRage_EventScript_ThunderStorm
	random 2
	goto_if_eq VAR_RESULT, 1, LakeOfRage_EventScript_ThunderStorm
	end

LakeOfRage_EventScript_HideLois::
	setflag FLAG_TEMP_1
	return

LakeOfRage_EventScript_ThunderStorm::
	setweather WEATHER_RAIN_THUNDERSTORM
	end

LakeOfRage_EventScript_Pryce::
    lock
    faceplayer
    msgbox LakeOfRage_Text_Pryce, MSGBOX_DEFAULT
    closemessage
    fadescreenswapbuffers FADE_TO_BLACK
    setflag FLAG_HIDE_LAKE_PRYCE
    removeobject LOCALID_LAKE_PRYCE
    fadescreenswapbuffers FADE_FROM_BLACK
    clearflag FLAG_HIDE_DOJO_PRYCE
    release
    end

LakeOfRage_Text_Pryce:
    .string "{PLAYER}.\p"
    .string "גם כאן, הקור מחדד אותי.\p"
    .string "אם תרצה להילחם שוב, בוא\n"
    .string "לדוג'ו הלחימה.$"

LakeOfRage_EventScript_Gramps::
	goto_if_ge VAR_MAHOGANY_TOWN_STATE, 14, LakeOfRage_EventScript_Gramps2
	msgbox LakeOfRage_Text_Gramps, MSGBOX_NPC
	end

LakeOfRage_EventScript_Gramps2::
	msgbox LakeOfRage_Text_GrampsCleared, MSGBOX_NPC
	end
LakeOfRage_EventScript_Lass::
	msgbox LakeOfRage_Text_CooltrainerF, MSGBOX_NPC
	end

LakeOfRage_EventScript_Nerd::
	msgbox LakeOfRage_Text_SuperNerd, MSGBOX_NPC
	end

LakeOfRage_EventScript_Andre::
	trainerbattle_single TRAINER_ANDRE_HNS, LakeOfRage_Text_FisherAndreSeen, LakeOfRage_Text_FisherAndreBeaten
	msgbox LakeOfRage_Text_FisherAndreAfter, MSGBOX_AUTOCLOSE
	end

LakeOfRage_EventScript_Raymond::
	trainerbattle_single TRAINER_RAYMOND_HNS, LakeOfRage_Text_FisherRaymondSeen, LakeOfRage_Text_FisherRaymondBeaten
	msgbox LakeOfRage_Text_FisherRaymondAfter, MSGBOX_AUTOCLOSE
	end

LakeOfRage_EventScript_Aaron::
	trainerbattle_single TRAINER_AARON_HNS, LakeOfRage_Text_CooltrainermAaronSeen, LakeOfRage_Text_CooltrainermAaronBeaten
	msgbox LakeOfRage_Text_CooltrainermAaronAfter, MSGBOX_AUTOCLOSE
	end

LakeOfRage_EventScript_Lois::
	trainerbattle_single TRAINER_LOIS_HNS, LakeOfRage_Text_CooltrainerfLoisSeen, LakeOfRage_Text_CooltrainerfLoisBeaten
	msgbox LakeOfRage_Text_CooltrainerfLoisAfter, MSGBOX_AUTOCLOSE
	end

LakeOfRage_EventScript_Gyarados::
	lock
	faceplayer
	msgbox LakeOfRage_Text_GyaradosCry, MSGBOX_DEFAULT
	waitse
	playmoncry SPECIES_GYARADOS, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setwildbattleshiny SPECIES_GYARADOS, 30
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, LakeOfRage_EventScript_Defeated_Gyarados
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, LakeOfRage_EventScript_Ran_Gyarados
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, LakeOfRage_EventScript_Ran_Gyarados
LakeOfRage_EventScript_Defeated_Gyarados::
	setflag FLAG_HIDE_LAKE_OF_RAGE_GYARADOS
	clearflag FLAG_TEMP_1
	removeobject LOCALID_LAKEOFRAGE_GYARADOS
	clearflag FLAG_HIDE_LAKE_OF_RAGE_LANCE
	addobject LOCALID_LAKEOFRAGE_LANCE
	giveitem ITEM_RED_SCALE
	setobjectxyperm LOCALID_LAKEOFRAGE_OLDMAN, 32, 38
	setvar VAR_MAHOGANY_TOWN_STATE, 2
	release
	end

LakeOfRage_EventScript_Ran_Gyarados::
	release
	end

LakeOfRage_EventScript_Item_Full_Restore::
	finditem ITEM_FULL_RESTORE
	end
LakeOfRage_EventScript_Item_Secret_Power::
    finditem ITEM_TM_SECRET_POWER
    end
LakeOfRage_EventScript_Item_Red_Flute::
	finditem ITEM_RED_FLUTE
	end

LakeOfRage_EventScript_Dragonite::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_DRAGONITE, CRY_MODE_NORMAL
	msgbox LakeOfRage_Text_Dragonite, MSGBOX_DEFAULT
	waitmoncry
	turnobject LOCALID_LAKEOFRAGE_DRAGONITE, DIR_WEST
	release
	end

LakeOfRage_EventScript_Lance::
	lock
	goto_if_eq VAR_MAHOGANY_TOWN_STATE, 3, LakeOfRage_EventScript_Lance_Return
	msgbox LakeOfRage_Text_LanceForcedToEvolve, MSGBOX_DEFAULT
	closemessage
	delay 20
	faceplayer
	turnobject LOCALID_LAKEOFRAGE_OLDMAN, DIR_WEST
	msgbox LakeOfRage_Text_LanceIntro2, MSGBOX_DEFAULT
	setvar VAR_MAHOGANY_TOWN_STATE, 3
	msgbox LakeOfRage_Text_LanceIntro3, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, LakeOfRage_EventScript_LancDeclined
LakeOfRage_EventScript_LanceAccept::
	lock
	msgbox LakeOfRage_Text_LanceRadioSignal, MSGBOX_DEFAULT
	closemessage
	goto_if_eq VAR_FACING, DIR_NORTH, LakeOfRage_EventScript_LanceDragoniteLeaveNorth
	applymovement LOCALID_LAKEOFRAGE_LANCE, LakeOfRage_Movement_LanceLeave
	applymovement LOCALID_LAKEOFRAGE_DRAGONITE, LakeOfRage_Movement_DragoniteLeave
	waitmovement LOCALID_LAKEOFRAGE_LANCE
	waitmovement LOCALID_LAKEOFRAGE_DRAGONITE
LakeOfRage_EventScript_EndScene::
	setflag FLAG_HIDE_LAKE_OF_RAGE_LANCE
	removeobject LOCALID_LAKEOFRAGE_LANCE
	removeobject LOCALID_LAKEOFRAGE_DRAGONITE
	setvar VAR_MAHOGANY_TOWN_STATE, 4
	clearflag FLAG_HIDE_MAHOGANY_TOWN_SHOP_NPCS
	release
	end

LakeOfRage_EventScript_Lance_Return::
	lock
	faceplayer
	msgbox LakeOfRage_Text_LanceAskHelp, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE, LakeOfRage_EventScript_LanceAccept
	goto_if_eq VAR_RESULT, FALSE, LakeOfRage_EventScript_LancDeclined

LakeOfRage_EventScript_LancDeclined::
	msgbox LakeOfRage_Text_LanceRefused, MSGBOX_DEFAULT
	closemessage
	release
	end


LakeOfRage_EventScript_LanceDragoniteLeaveNorth::
	applymovement LOCALID_LAKEOFRAGE_LANCE, LakeOfRage_Movement_LanceLeaveNorth
	applymovement LOCALID_LAKEOFRAGE_DRAGONITE, LakeOfRage_Movement_DragoniteLeaveNorth
	waitmovement LOCALID_LAKEOFRAGE_LANCE
	waitmovement LOCALID_LAKEOFRAGE_DRAGONITE
	goto LakeOfRage_EventScript_EndScene

LakeOfRage_Movement_LanceLeaveNorth:
	walk_left
	walk_down
	delay_8
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

LakeOfRage_Movement_DragoniteLeaveNorth:
	delay_16
	delay_16
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

LakeOfRage_Movement_LanceLeave:
	walk_down
	delay_8
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

LakeOfRage_Movement_DragoniteLeave:
	delay_16
	delay_16
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

LakeOfRage_Text_Dragonite:
	.string "דרגונייט: גיאפוהה!$"

LakeOfRage_Text_LanceForcedToEvolve:
    .string "האגם הזה מלא בגרידוס,\n"
    .string "ואין בו שום דבר אחר…\p"
    .string "אז מכריחים את המג'יקארפ\n"
    .string "להתפתח…$"

LakeOfRage_Text_LanceIntro1:
    .string "Did you come here because of\n"
    .string "the rumors?\p"
    .string "You're {PLAYER}? I'm LANCE, a\n"
    .string "trainer like you.$"

LakeOfRage_Text_LanceIntro2:
    .string "האיש הזה סיפר לי על\n"
    .string "כמה שמועות.\p"
    .string "אז באנו לבדוק את העניין…$"

LakeOfRage_Text_LanceIntro3:
    .string "ראיתי איך נלחמת קודם,\n"
    .string "{PLAYER}.\p"
    .string "ברור לי שאתה מאמן\n"
    .string "מיומן במיוחד.\p"
    .string "אם לא אכפת לך, תוכל לעזור\n"
    .string "לנו לחקור?$"

LakeOfRage_Text_LanceRadioSignal:
    .string "לאנס: מצוין!\p"
    .string "נראה שמכריחים את המג'יקארפ\n"
    .string "של האגם להתפתח.\p"
    .string "הסיבה היא שידור רדיו מסתורי\n"
    .string "שמגיע מהעיירה מהגוני.\p"
    .string "נחכה לך, {PLAYER}.$"

LakeOfRage_Text_LanceRefused:
    .string "אה… טוב, אם תשנה את דעתך,\n"
    .string "אנא, עזור לנו.$"

LakeOfRage_Text_LanceAskHelp:
    .string "לאנס: הממ? אתה מתכוון לעזור לנו?$"

LakeOfRage_Text_GyaradosCry:
    .string "גרידוס: גיאשאא!$"

LakeOfRage_Text_Gramps:
    .string "הגרידוס כועסים!\p"
    .string "זה סימן רע!$"

LakeOfRage_Text_GrampsCleared:
    .string "חה חה! המג'יקארפ עולים בחכה!$"

LakeOfRage_Text_SuperNerd:
    .string "שמעתי שהאגם הזה נוצר בידי\n"
    .string "גרידוס שהשתוללו.\p"
    .string "מעניין אם יש קשר בין זה\n"
    .string "להופעה ההמונית שלהם עכשיו?$"

LakeOfRage_Text_CooltrainerF:
    .string "העיניים שלי הטעו אותי? ראיתי\n"
    .string "גרידוס אדום באגם…\p"
    .string "אבל חשבתי שגרידוס הם\n"
    .string "בדרך כלל כחולים?$"


LakeOfRage_Text_FisherAndreSeen:
    .string "אני רוצה להילחם עם הפוקימון\n"
    .string "שתפסתי הרגע!$"

LakeOfRage_Text_FisherAndreBeaten:
    .string "אולי אני דייג מומחה, אבל\n"
    .string "כמאמן פוקימונים אני גרוע…$"

LakeOfRage_Text_FisherAndreAfter:
    .string "כדייג אני לא אפסיד! אני תופס\n"
    .string "פוקימונים כל היום.$"


LakeOfRage_Text_FisherRaymondSeen:
    .string "לא משנה מה אני עושה, אני תמיד\n"
    .string "תופס את אותם הפוקימונים…$"

LakeOfRage_Text_FisherRaymondBeaten:
    .string "חוט הדיג שלי הסתבך לגמרי…$"

LakeOfRage_Text_FisherRaymondAfter:
    .string "למה אני לא מצליח לתפוס\n"
    .string "אף פוקימון טוב?$"

LakeOfRage_Text_CooltrainermAaronSeen:
    .string "כשמאמן רואה מאמן אחר,\n"
    .string "הוא חייב להזמין אותו לקרב.\p"
    .string "זה הגורל שלנו.$"

LakeOfRage_Text_CooltrainermAaronBeaten:
    .string "פיו… קרב טוב.$"

LakeOfRage_Text_CooltrainermAaronAfter:
    .string "פוקימונים והמאמן שלהם נעשים\n"
    .string "חזקים בזכות קרבות בלי הפסקה.$"

LakeOfRage_Text_CooltrainerfLoisSeen:
    .string "מה קרה לגרידוס האדום?\p"
    .string "הוא נעלם?\p"
    .string "אוף. באתי לכאן לחינם?\p"
    .string "יש לי רעיון: בוא נילחם!$"

LakeOfRage_Text_CooltrainerfLoisBeaten:
    .string "כל הכבוד!$"

LakeOfRage_Text_CooltrainerfLoisAfter:
    .string "עכשיו כשאני חושבת על זה, ראיתי\n"
    .string "פעם בטרפרי ורוד.$"



LakeOfRage_EventScript_Wesley::
	lock
	faceplayer
	goto_if_set FLAG_GOT_BLACK_BELT, LakeOfRage_EventScript_WesleyCompleted
	msgbox LakeOfRage_Text_MeetWesley, MSGBOX_DEFAULT
	closemessage
	multichoice 20, 0, MULTI_DAYS_OF_WEEK, FALSE
	switch VAR_RESULT
	case 0, LakeOfRage_EventScript_WesleyNope
	case 1, LakeOfRage_EventScript_WesleyNope
	case 2, LakeOfRage_EventScript_WesleyNope
	case 3, LakeOfRage_EventScript_WesleyYes
	case 4, LakeOfRage_EventScript_WesleyNope
	case 5, LakeOfRage_EventScript_WesleyNope
	case 6, LakeOfRage_EventScript_WesleyNope
	case 7 LakeOfRage_EventScript_WesleyCancel
	case MULTI_B_PRESSED, LakeOfRage_EventScript_WesleyCancel
	closemessage
	release
	end
LakeOfRage_EventScript_WesleyYes::
	msgbox LakeOfRage_Text_WesleyGivesGift, MSGBOX_DEFAULT
	giveitem ITEM_BLACK_BELT
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_GOT_BLACK_BELT
	msgbox LakeOfRage_Text_WesleyGaveGift, MSGBOX_DEFAULT
	closemessage
	release
	end
LakeOfRage_EventScript_WesleyNope::
	msgbox LakeOfRage_Text_WesleyNotWednesday, MSGBOX_DEFAULT
	closemessage
	release
	end
LakeOfRage_EventScript_WesleyCancel::
	closemessage
	release
	end
LakeOfRage_EventScript_WesleyCompleted::
	msgbox LakeOfRage_Text_WesleyWednesday, MSGBOX_DEFAULT
	closemessage
	release
	end

LakeOfRage_Text_MeetWesley:
    .string "ווסלי: ובכן, מה שלומך?\p"
    .string "אני ממשפחת ימי השבוע!\n"
    .string "תוכל לנחש מה היום האהוב עליי?$"

LakeOfRage_Text_WesleyGivesGift:
    .string "נעים להכיר. בבקשה, הנה\n"
    .string "מזכרת בשבילך.$"

LakeOfRage_Text_WesleyGaveGift:
    .string "ווסלי: החגורה השחורה מגבירה את\n"
    .string "כוחם של מהלכים מסוג קרב.$"

LakeOfRage_Text_WesleyWednesday:
    .string "ווסלי: אם מצאת אותי, בטח כבר\n"
    .string "פגשת את האחים והאחיות שלי.\p"
    .string "או שפשוט היה לך מזל?$"

LakeOfRage_Text_WesleyNotWednesday:
    .string "ווסלי: לא בדיוק…$"

LakeOfRage_EventScript_Sign1::
	msgbox LakeOfRage_Text_Sign, MSGBOX_SIGN
	end

LakeOfRage_EventScript_Sign2::
	msgbox LakeOfRage_Text_FishingGuruSign, MSGBOX_SIGN
	end

LakeOfRage_Text_Sign:
    .string "אגם הזעם,\n"
    .string "הידוע גם בשם אגם הגרידוס.$"

LakeOfRage_Text_FishingGuruSign:
    .string "הבית של גורו הדיג$"
