EcruteakCity_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, EcruteakCity_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

EcruteakCity_OnTransition::
	callnative SetTimeBasedEncounters
	end

EcruteakCity_Test_Lugia::
	setvar VAR_LUGIA_OR_HOOH, 1
	end
EcruteakCity_Test_League::
	setvar VAR_COMPLETED_HO_OH, 4
	setvar VAR_COMPLETED_LUGIA, 4
	end


EcruteakCity_EventScript_Trigger::
	@flagheap
	clearflag FLAG_RELEASED_BEASTS
	clearflag FLAG_AMPHAROS_HEALED
	clearflag FLAG_HIDE_ECRUTEAK_BILL
	clearflag FLAG_DEFEATED_HO_OH
	clearflag FLAG_CAUGHT_HO_OH
	clearflag FLAG_DEFEATED_LUGIA
	clearflag FLAG_CAUGHT_LUGIA
	clearflag FLAG_HIDE_ECRUTEAK_ROCKET
	clearflag FLAG_HIDE_BURNED_TOWER_NPCS  
	clearflag FLAG_HIDE_BURNED_TOWER_BEASTS
	clearflag FLAG_HIDE_BURNED_TOWER_B1F_EUSINE
	clearflag FLAG_HIDE_ECRUTEAK_CITY_SAGE
	clearflag FLAG_CAUGHT_ENTEI
	clearflag FLAG_CAUGHT_RAIKOU
	clearflag FLAG_GOT_TM_SNATCH
	clearflag FLAG_HIDE_ROUTE42_SUICUNE
	clearflag FLAG_GOT_TYROGUE
	clearflag FLAG_BEAT_KIYO
	clearflag FLAG_ENABLE_BAOBA_MATCH_CALL
	clearflag FLAG_HIDE_ECRUTEAK_CITY_THEATER_NPCS
	clearflag FLAG_HIDE_ECRUTEAK_CITY_THEATER_ZUKI
	clearflag FLAG_HIDE_TINTOWER_GUARD
	clearflag FLAG_HIDE_WHIRL_ISLANDS_TENTACRUEL
	clearflag FLAG_HIDE_LUGIA
	clearflag FLAG_HIDE_HO_OH

	setflag FLAG_VISITED_ECRUTEAK_CITY
	setflag FLAG_HIDE_ROUTE42_EUSINE

	setflag FLAG_HIDE_TIN_TOWER_KIMONO_GIRLS
	setflag FLAG_HIDE_WHIRL_ISLANDS_KIMONO_GIRLS
	setflag FLAG_HIDE_ECRUTEAK_CITY_THEATER_KIMONOS
	setflag FLAG_HIDE_ROUTE39_SHADOW
	setflag FLAG_HIDE_ECRUTEAK_SILVER
	setvar VAR_COMPLETED_HO_OH, 0
	setvar VAR_COMPLETED_LUGIA, 0
	setvar VAR_ECRUTEAK_CITY_THEATER, 0 
	setvar VAR_ECRUTEAK_CITY_STATE, 1
	end

EcruteakCity_Trigger_Silver::
	lockall
	opendoor 39, 40
	waitdooranim
	delay 10
	clearflag FLAG_HIDE_ECRUTEAK_SILVER
	addobject LOCALID_ECRUTEK_SILVER
	playbgm MUS_HG_ENCOUNTER_RIVAL, FALSE
	playse SE_BANG
	applymovement LOCALID_ECRUTEK_SILVER, EcruteakCity_Movement_Silver1
	applymovement OBJ_EVENT_ID_PLAYER, EcruteakCity_Movement_Silver1
	message EcruteakCity_Text_Silver1
	
	waitmovement OBJ_EVENT_ID_PLAYER
	waitmovement LOCALID_ECRUTEK_SILVER
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	closedoor 39, 40
	waitdooranim
	msgbox EcruteakCity_Text_Silver2, MSGBOX_DEFAULT
	closemessage
	playse SE_PIN
	applymovement LOCALID_ECRUTEK_SILVER, Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_ECRUTEK_SILVER
	turnobject LOCALID_ECRUTEK_SILVER, DIR_SOUTH
	msgbox EcruteakCity_Text_Silver3, MSGBOX_DEFAULT
	closemessage

	applymovement LOCALID_ECRUTEK_SILVER, EcruteakCity_Movement_Silver2
	waitmovement LOCALID_ECRUTEK_SILVER


	setflag FLAG_HIDE_ECRUTEAK_SILVER
	removeobject LOCALID_ECRUTEK_SILVER
	fadedefaultbgm

	setvar VAR_ECRUTEAK_CITY_THEATER, 5
	releaseall
	end

EcruteakCity_Movement_Silver1:
	delay_16
	lock_facing_direction
	walk_down
	unlock_facing_direction
	step_end

EcruteakCity_Movement_Silver2:
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

EcruteakCity_Text_Silver1:
	.string "טראח!!$"

EcruteakCity_Text_Silver2:
	.string "{RIVAL}: איך…? איך זה ייתכן?\n"
	.string "איך אני יכול להפסיד לסתם נערות קימונו…?$"

EcruteakCity_Text_Silver3:
	.string "{RIVAL}: הסתכלת עליי, {PLAYER}…\p"
	.string "כן, זה נכון!\p"
	.string "לא חשבתי שלנצח חמש נערות קימונו\n"
	.string "יהיה כל כך קשה…\p"
	.string "ריסקו אותי לגמרי…\p"
	.string "…\p"
	.string "בטח באת לכאן מאותה סיבה, נכון?\p"
	.string "אל תתחיל להשוויץ רק בגלל\n"
	.string "שניצחת את צוות רוקט!\p"
	.string "נערות הקימונו האלה חזקות בטירוף.\p"
	.string "נראה אם תצליח לנצח אותן.\p"
	.string "אבל אני לא חוזר לשם,\n"
	.string "אין לי חשק לראות אותך מנצח.$"

EcruteakCity_EventScript_Gramps::
	lock
	faceplayer
	msgbox EcruteakCity_Text_Gramps1, MSGBOX_DEFAULT
	closemessage
	release
	end
		
EcruteakCity_EventScript_Lass::
	lock
	faceplayer
	msgbox EcruteakCity_Text_Lass1, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_EventScript_Girl::
	lock
	faceplayer
	goto_if_set FLAG_RELEASED_BEASTS, EcruteakCity_EventScript_Girl2
	msgbox EcruteakCity_Text_Lass2, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_EventScript_Girl2::
	msgbox EcruteakCity_Text_Lass2_ReleasedBeasts, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_EventScrip_Man::
	lock
	faceplayer
	goto_if_set FLAG_AMPHAROS_HEALED, EcruteakCity_EventScrip_Man2
	msgbox EcruteakCity_Text_Fisher, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_EventScrip_Man2::
	msgbox EcruteakCity_Text_Fisher_JasmineReturned, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_EventScript_Youngster::
	lock
	faceplayer
	msgbox EcruteakCity_Text_Youngster, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_EventScript_SageRight::
	lock
	faceplayer
	msgbox EcruteakCity_Text_Gramps2, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_EventScript_SageTower::
	lock
	faceplayer
	msgbox EcruteakCity_Text_Gramps3, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_EventScript_SageGym::
	lock
	faceplayer
	msgbox EcruteakCity_Text_SageGym, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_EventScript_TheaterSign::
	lock
	msgbox EcruteakCity_Text_DanceTheaterSign, MSGBOX_SIGN
	closemessage
	release
	end	

EcruteakCity_EventScript_OfficeSign::
	lock
	msgbox EcruteakCity_Text_OfficeSign, MSGBOX_SIGN
	closemessage
	release
	end	

EcruteakCity_EventScript_BurnedSign::
	lock
	msgbox EcruteakCity_Text_BurnedTowerSign, MSGBOX_SIGN
	closemessage
	release
	end	

EcruteakCity_EventScript_CitySign::
	lock
	msgbox EcruteakCity_Text_Sign, MSGBOX_SIGN
	closemessage
	release
	end	

EcruteakCity_EventScript_GymSign::
	lock
	msgbox EcruteakCity_Text_GymSign, MSGBOX_SIGN
	closemessage
	release
	end

EcruteakCity_EventScript_Eevee::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_EEVEE, CRY_MODE_NORMAL
	msgbox EcruteakCity_Text_Eevee, MSGBOX_DEFAULT
	waitmoncry
	release
	end

EcruteakCity_EventScript_Vulpix::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_VULPIX, CRY_MODE_NORMAL
	msgbox EcruteakCity_Text_Vulpix, MSGBOX_DEFAULT
	waitmoncry
	release
	end

EcruteakCity_EventScript_Item_RareCandy::
	finditem ITEM_RARE_CANDY
	end

EcruteakCity_Text_Eevee:
	.string "איווי: וייי!$"

EcruteakCity_Text_Vulpix:
	.string "וולפיקס: ווללל פיקס!$"


EcruteakCity_Text_UnusedMissingDaughter:
	.string "Oh, no. Oh, no…\p"
	.string "My daughter is missing.\p"
	.string "No… She couldn't have gone to the\n"
	.string "BURNED TOWER.\p"
	.string "I told her not to go near it…\p"
	.string "People seem to disappear there…\p"
	.string "Oh, what should I do…?$"

EcruteakCity_Text_Gramps1:
	.string "פעם היו באקרוטיק שני מגדלים:\n"
	.string "אחד במזרח ואחד במערב.$"

EcruteakCity_Text_Gramps2:
	.string "אה, ילד. למדת לרקוד כמו נערות הקימונו?\p"
	.string "שמעתי שאם תלך לתיאטרון המחול שלהן,\n"
	.string "זקן מוזר אחד ייתן לך משהו נחמד.$"

EcruteakCity_Text_Lass1:
	.string "אני הולכת להתאמן בתיאטרון המחול.\n"
	.string "רוצה להצטרף אליי?$"

EcruteakCity_Text_Lass2:
	.string "המגדל שעמד פה פעם…\p"
	.string "סבתא שלי סיפרה לי שפעם\n"
	.string "הוא היה הרבה יותר גבוה.\p"
	.string "שמעתי שעכשיו יש בו רוחות רפאים.$"

EcruteakCity_Text_Lass2_ReleasedBeasts:
	.string "שלושה פוקימונים גדולים ברחו\n"
	.string "לכיוונים שונים. מי הם היו?$"

EcruteakCity_Text_Fisher:
	.string "שמעתי שמועה על מגדלור אוליבין.\p"
	.string "הפוקימון שמשמש כאור של\n"
	.string "המגדלור חלה. נשמע שהם בצרה.$"

EcruteakCity_Text_Fisher_JasmineReturned:
	.string "הפוקימון במגדלור אוליבין החלים.\p"
	.string "סירות יכולות שוב לצאת לים בבטחה בלילה.$"

EcruteakCity_Text_Youngster:
	.string "שמעתי שפוקימונים משתוללים\n"
	.string "באגם הזעם. הייתי רוצה לראות את זה.$"

EcruteakCity_Text_Gramps3:
	.string "בעבר הרחוק…\p"
	.string "המגדל הזה נשרף באש. שלושה\n"
	.string "פוקימונים חסרי שם נספו בתוכו.\p"
	.string "פוקימון בצבעי הקשת ירד\n"
	.string "מהשמיים והחזיר אותם לחיים…\p"
	.string "זאת אגדה שמנהיגי מכון אקרוטיק\n"
	.string "מעבירים מדור לדור.\p"
	.string "אני?\p"
	.string "הייתי מאמן פעם, לפני הרבה שנים. הוהוהו!$"

EcruteakCity_Text_SageGym:
	.string "מנהיג המכון, מורטי, לא נמצא כאן כרגע.\n"
	.string "אולי תמצא אותו במגדל השרוף.$"

EcruteakCity_Text_Sign:
	.string "העיר אקרוטיק\n"
	.string "עיר היסטורית\p"
	.string "שבה העבר פוגש את ההווה$"

EcruteakCity_Text_TinTowerSign:
	.string "TIN TOWER\p"
	.string "A legendary POKéMON is said to\n"
	.string "roost here.$"

EcruteakCity_Text_OfficeSign:
	.string "עמדת מחסום למגדל הבדיל\p"
	.string "הכניסה אסורה למי שאינו ראוי.$"

EcruteakCity_Text_GymSign:
	.string "מכון הפוקימון של העיר אקרוטיק\n"
	.string "מנהיג: מורטי\p"
	.string "חוזה העתיד המיסטי$"

EcruteakCity_Text_DanceTheaterSign:
	.string "תיאטרון המחול של אקרוטיק$"

EcruteakCity_Text_BurnedTowerSign:
	.string "המגדל השרוף\p"
	.string "המגדל נהרס בשריפה מסתורית.\p"
	.string "נא להתרחק, המקום אינו בטוח.$"
