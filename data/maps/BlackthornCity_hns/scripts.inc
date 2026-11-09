BlackthornCity_hns_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BlackthornCity_OnFrame
	map_script MAP_SCRIPT_ON_LOAD, BlackthornCity_OnLoad
	map_script MAP_SCRIPT_ON_TRANSITION, BlackthornCity_EventScript_CityEnter
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

BlackthornCity_OnLoad::
	goto_if_unset FLAG_BADGE05_GET, BlackThornCity_EventScript_MoveGymBoy
	goto_if_unset FLAG_BADGE06_GET, BlackThornCity_EventScript_MoveGymBoy
	goto_if_unset FLAG_BADGE07_GET, BlackThornCity_EventScript_MoveGymBoy
	end

BlackThornCity_EventScript_MoveGymBoy::
	setobjectxyperm LOCALID_BLACKTHORN_BOY, 24, 27
	end

BlackthornCity_OnFrame::
	map_script_2 VAR_BLACKTHORN_CITY_STATE, 4, BlackthornCity_EventScript_Call
	.2byte 0

BlackthornCity_EventScript_CityEnter:: 
	setflag FLAG_VISITED_BLACKTHORN_CITY
	callnative SetTimeBasedEncounters
	end

BlackthornCity_EventScript_Call::
	lock
	setspeaker BlackthornCity_Text_ElmName
	pokenavcall BlackthornCity_Text_ElmCall
	waitmessage
	delay 30
	setvar VAR_BLACKTHORN_CITY_STATE, 5
	setvar VAR_NEWBARKTOWN_LABSTATE, 7
	release
	end

BlackthornCity_Text_ElmName:
	.string "פרופ' אלם$"

BlackthornCity_Text_BaobaCall:
	.string "הפקח באובה: {PLAYER}!\p"
	.string "מדבר הפקח באובה.\p"
	.string "אני מתקשר לספר לך\n"
	.string "שאזור הספארי התרחב!\p"
	.string "נשמח לביקור שלך!$"

BlackthornCity_Text_ElmCall:
	.string "פרופ' אלם: הלו, {PLAYER}?\p"
	.string "יש לי כאן משהו בשבילך.\n"
	.string "תוכל לקפוץ אליי למעבדה?\p"
	.string "נתראה!$"

BlackThornCity_EventScript_Sage::
	lock
	faceplayer
	goto_if_eq VAR_BLACKTHORN_CITY_STATE, 1, BlackThornCity_EventScript_SageRefuse
	msgbox BlackthornGrampsGrantsEntryText, MSGBOX_DEFAULT
	closemessage
	release
	end

BlackThornCity_EventScript_SageRefuse::
	msgbox BlackthornGrampsRefusesEntryText, MSGBOX_DEFAULT
	closemessage
	release
	end

BlackThornCity_Trigger_Sage::
	lock
	turnobject LOCALID_BLACKTHORN_SAGE, DIR_EAST
	msgbox BlackthornGrampsRefusesEntryText, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER Common_Movement_WalkDown1
	waitmovement 0
	turnobject LOCALID_BLACKTHORN_SAGE, DIR_SOUTH
	release
	end

BlackthornCity_EventScript_GymBoy::
	lock
	faceplayer
	goto_if_unset FLAG_BADGE05_GET, BlackThornCity_EventScript_GymBoyNotReady
	goto_if_unset FLAG_BADGE06_GET, BlackThornCity_EventScript_GymBoyNotReady
	goto_if_unset FLAG_BADGE07_GET, BlackThornCity_EventScript_GymBoyNotReady
	goto_if_eq VAR_BLACKTHORN_CITY_STATE, 1, BlackThornCity_EventScript_GymBoyBefore
	msgbox BlackthornCity_Text_ClairIsBeaten, MSGBOX_DEFAULT
	closemessage
	release
	end	

BlackThornCity_EventScript_GymBoyNotReady::
	msgbox BlackthornCity_Text_ClairNotReady, MSGBOX_DEFAULT
	closemessage
	release
	end

BlackThornCity_EventScript_GymBoyBefore::
	msgbox BlackthornCity_Text_ClairIsIn, MSGBOX_DEFAULT
	closemessage
	release
	end	

BlackthornCity_EventScript_BlackBelt::
	msgbox BlackBeltText_VoicesInMyHead, MSGBOX_NPC
	end

BlackthornCity_EventScript_CoolTrainerF::
	msgbox BlackthornCooltrainerF1Text, MSGBOX_NPC
	end

BlackthornCity_EventScript_Youngster::
	msgbox BlackthornYoungsterText, MSGBOX_NPC
	end

BlackthornCity_EventScript_CoolTrainerF2::
	msgbox BlackthornCooltrainerF2Text, MSGBOX_NPC
	end

BlackthornCity_EventScript_CitySign::
	msgbox BlackthornCitySignText, MSGBOX_SIGN
	end

BlackthornCity_EventScript_GymSign::
	msgbox BlackthornGymSignText, MSGBOX_SIGN
	end

BlackthornCity_EventScript_MoveHouseSign::
	msgbox BlackthornCity_Text_MoveDeletersHouseSign, MSGBOX_SIGN
	end

BlackthornCity_EventScript_DragonsDenSign::
	msgbox BlackthornCity_Text_DragonDenSign, MSGBOX_SIGN
	end

BlackthornCity_EventScript_Santos::
	lock
	faceplayer
	goto_if_set FLAG_GOT_SPELL_TAG, BlackthornCity_EventScript_SantosCompleted
	msgbox BlackthornCity_MeetSantosText, MSGBOX_DEFAULT
	closemessage
	multichoice 20, 0, MULTI_DAYS_OF_WEEK, FALSE
	switch VAR_RESULT
	case 0, BlackthornCity_EventScript_SantosNope
	case 1, BlackthornCity_EventScript_SantosNope
	case 2, BlackthornCity_EventScript_SantosNope
	case 3, BlackthornCity_EventScript_SantosNope
	case 4, BlackthornCity_EventScript_SantosNope
	case 5, BlackthornCity_EventScript_SantosNope
	case 6, BlackthornCity_EventScript_SantosYes
	case 7 BlackthornCity_EventScript_SantosCancel
	case MULTI_B_PRESSED, BlackthornCity_EventScript_SantosCancel
	closemessage
	release
	end
BlackthornCity_EventScript_SantosYes::
	msgbox BlackthornCity_SantosGivesGiftText, MSGBOX_DEFAULT
	giveitem ITEM_SPELL_TAG
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_GOT_SPELL_TAG
	msgbox BlackthornCity_SantosGaveGiftText, MSGBOX_DEFAULT
	closemessage
	release
	end
BlackthornCity_EventScript_SantosNope::
	msgbox BlackthornCity_SantosNopeText, MSGBOX_DEFAULT
	closemessage
	release
	end
BlackthornCity_EventScript_SantosCancel::
	closemessage
	release
	end
BlackthornCity_EventScript_SantosCompleted::
	msgbox BlackthornCity_SantosSaturdayText, MSGBOX_DEFAULT
	closemessage
	release
	end


BlackthornCity_Text_ClairNotReady:
	.string "קלייר, מנהיגת המכון שלנו,\n"
	.string "עוקבת אחרי ההתקדמות שלך.\p"
	.string "אבל היא נלחמת רק במאמנים\n"
	.string "שכבר יש להם 7 תגים.$"

BlackthornCity_Text_ClairIsIn:
	.string "קלייר, מנהיגת המכון שלנו,\n"
	.string "מחכה לך.\p"
	.string "אבל למאמן מן השורה\n"
	.string "אין שום סיכוי לנצח.$"

BlackthornCity_Text_ClairIsBeaten:
	.string "ניצחת את קלייר?\p"
	.string "זה מדהים!\p"
	.string "אף פעם לא שמעתי שהיא הפסידה\n"
	.string "למישהו חוץ מלאנס.$"

BlackthornGrampsRefusesEntryText:
	.string "לא. רק מאמנים נבחרים רשאים\n"
	.string "להתאמן כאן.\p"
	.string "נא לעזוב.$"

BlackthornGrampsGrantsEntryText:
	.string "אם קלייר מרשה, גם סבא שלה,\n"
	.string "המאסטר שלנו, ירשה.\p"
	.string "מותר לך להיכנס.$"

BlackBeltText_VoicesInMyHead:
	.string "אוווו! קולות בתוך הראש שלי!\p"
	.string "מה? אני מקשיב לרדיו שלי!$"

BlackthornCooltrainerF1Text:
	.string "באת כדי שהפוקימונים שלך\n"
	.string "ייזכרו בכמה מהלכים?$"

BlackthornYoungsterText:
	.string "כל מאסטרי הדרקונים באים\n"
	.string "מהעיר בלקתורן.$"

BlackthornCity_MeetSantosText:
	.string "סנטוס: …\p"
	.string "אני סנטוס ממשפחת ימי השבוע.\p"
	.string "נסה לנחש.$"

BlackthornCity_SantosGivesGiftText:
	.string "זה בשבילך…$"

BlackthornCity_SantosGaveGiftText:
	.string "סנטוס: …\p"
	.string "קמע רוח…\p"
	.string "מהלכים מסוג רפאים מתחזקים…\p"
	.string "הוא יפחיד אותך…$"

BlackthornCity_SantosSaturdayText:
	.string "סנטוס: …\p"
	.string "נתראה שוב בשבת אחרת…\p"
	.string "לא יהיו לי עוד מתנות…$"

BlackthornCity_SantosNopeText:
	.string "סנטוס: לא.$"

BlackthornCooltrainerF2Text:
	.string "וואו, עברת דרך שביל הקרח?\p"
	.string "אתה בטח מאמן תותח!$"

BlackthornCitySignText:
	.string "העיר בלקתורן\p"
	.string "מפלט שקט בהרים$"

BlackthornGymSignText:
	.string "מכון הפוקימון של העיר בלקתורן\n"
	.string "מנהיגה: קלייר\p"
	.string "המאלפת המבורכת של פוקימוני דרקון$"

BlackthornCity_Text_MoveDeletersHouseSign:
	.string "בית אחי המהלכים$"

BlackthornCity_Text_DragonDenSign:
	.string "מאורת הדרקון בהמשך$"

