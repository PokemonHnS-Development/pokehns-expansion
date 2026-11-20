DragonsDen_Shrine_hns_MapScripts::
	@map_script MAP_SCRIPT_ON_FRAME_TABLE, DragonsDen_Shrine_OnFrame
	.byte 0

DragonsDen_Shrine_OnFrame::
	map_script_2 VAR_BLACKTHORN_CITY_STATE, 2, DragonsDen_Shrine_Trigger_ElderQuizTop
	.2byte 0

DragonsDen_Shrine_EventScript_Elder::
	lock
	faceplayer
	goto_if_ge VAR_BLACKTHORN_CITY_STATE, 4, DragonsDen_Shrine_EventScript_ElderChooseDratini
	msgbox DragonsDen_Shrine_Text_ComeAgain, MSGBOX_DEFAULT
	release
	end

DragonsDen_Shrine_Trigger_ElderQuizLeft::
	lock
	applymovement2 OBJ_EVENT_ID_PLAYER, DragonsDen_Shrine_Movement_PlayerWalkToElderLeft
	applymovement2 OBJ_EVENT_ID_FOLLOWER, DragonsDen_Shrine_Movement_MonWalkToElderLeft
	waitmovement OBJ_EVENT_ID_FOLLOWER
	waitmovement OBJ_EVENT_ID_PLAYER
	delay 10
	lockall
	goto DragonsDen_Shrine_EventScript_ElderOfferQuiz

DragonsDen_Shrine_Trigger_ElderQuizTop::
	lock
	applymovement2 OBJ_EVENT_ID_PLAYER, DragonsDen_Shrine_Movement_PlayerWalkToElderTop
	applymovement2 OBJ_EVENT_ID_FOLLOWER, DragonsDen_Shrine_Movement_PlayerWalkToElderTop
	waitmovement OBJ_EVENT_ID_FOLLOWER
	waitmovement OBJ_EVENT_ID_PLAYER
	delay 10
	lockall
	goto DragonsDen_Shrine_EventScript_ElderOfferQuiz

DragonsDen_Shrine_Trigger_ElderQuizRight::
	lock
	applymovement2 OBJ_EVENT_ID_PLAYER, DragonsDen_Shrine_Movement_PlayerWalkToElderRight
	applymovement2 OBJ_EVENT_ID_FOLLOWER, DragonsDen_Shrine_Movement_MonWalkToElderRight
	waitmovement OBJ_EVENT_ID_FOLLOWER
	waitmovement OBJ_EVENT_ID_PLAYER
	delay 10
	lockall
	goto DragonsDen_Shrine_EventScript_ElderOfferQuiz


DragonsDen_Shrine_Movement_PlayerWalkToElderLeft:
	walk_up
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

DragonsDen_Shrine_Movement_MonWalkToElderLeft:
	walk_left
	walk_up
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

DragonsDen_Shrine_Movement_PlayerWalkToElderTop:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

DragonsDen_Shrine_Movement_PlayerWalkToElderRight:
	walk_up
	walk_left
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end
DragonsDen_Shrine_Movement_MonWalkToElderRight:
	walk_right
	walk_up
	walk_left
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

DragonsDen_Shrine_EventScript_ElderOfferQuiz::
	msgbox DragonsDen_Shrine_Text_ElderGreeting, MSGBOX_DEFAULT
	setvar VAR_DRAGONS_DEN_QUIZ, 0
	goto DragonsDen_Shrine_EventScript_ElderQuiz1

DragonsDen_Shrine_EventScript_ElderQuiz1::
	message DragonsDen_Shrine_Text_Question1
	multichoice 20, 6, MULTI_ELDERQUIIZ1, FALSE 
	switch VAR_RESULT
	case 0, DragonsDen_Shrine_EventScript_ElderQuiz1Correct
	case 2, DragonsDen_Shrine_EventScript_ElderQuiz1Correct
	case MULTI_B_PRESSED, DragonsDen_Shrine_EventScript_ElderQuiz1
	call DragonsDen_Shrine_EventScript_ElderWrong
	goto DragonsDen_Shrine_EventScript_ElderQuiz1

DragonsDen_Shrine_EventScript_ElderQuiz1Correct::
	msgbox DragonsDen_Shrine_Text_RightAnswer, MSGBOX_DEFAULT
	goto DragonsDen_Shrine_EventScript_ElderQuiz2

DragonsDen_Shrine_EventScript_ElderQuiz2::
	message DragonsDen_Shrine_Text_Question2
	multichoice 20, 6, MULTI_ELDERQUIIZ2, FALSE 
	switch VAR_RESULT
	case 0, DragonsDen_Shrine_EventScript_ElderQuiz2Correct
	case 1, DragonsDen_Shrine_EventScript_ElderQuiz2Correct
	case MULTI_B_PRESSED, DragonsDen_Shrine_EventScript_ElderQuiz2
	call DragonsDen_Shrine_EventScript_ElderWrong
	goto DragonsDen_Shrine_EventScript_ElderQuiz2

DragonsDen_Shrine_EventScript_ElderQuiz2Correct::
	msgbox DragonsDen_Shrine_Text_RightAnswer, MSGBOX_DEFAULT
	goto DragonsDen_Shrine_EventScript_ElderQuiz3

DragonsDen_Shrine_EventScript_ElderQuiz3::
	message DragonsDen_Shrine_Text_Question3
	multichoice 20, 6, MULTI_ELDERQUIIZ3, FALSE 
	switch VAR_RESULT
	case 1, DragonsDen_Shrine_EventScript_ElderQuiz3Correct
	case 2, DragonsDen_Shrine_EventScript_ElderQuiz3Correct
	case MULTI_B_PRESSED, DragonsDen_Shrine_EventScript_ElderQuiz3
	call DragonsDen_Shrine_EventScript_ElderWrong
	goto DragonsDen_Shrine_EventScript_ElderQuiz3

DragonsDen_Shrine_EventScript_ElderQuiz3Correct::
	msgbox DragonsDen_Shrine_Text_RightAnswer, MSGBOX_DEFAULT
	goto DragonsDen_Shrine_EventScript_ElderQuiz4

DragonsDen_Shrine_EventScript_ElderQuiz4::
	message DragonsDen_Shrine_Text_Question4
	multichoice 20, 6, MULTI_ELDERQUIIZ4, FALSE 
	switch VAR_RESULT
	case 0, DragonsDen_Shrine_EventScript_ElderQuiz4Correct
	case 2, DragonsDen_Shrine_EventScript_ElderQuiz4Correct
	case MULTI_B_PRESSED, DragonsDen_Shrine_EventScript_ElderQuiz4
	call DragonsDen_Shrine_EventScript_ElderWrong
	goto DragonsDen_Shrine_EventScript_ElderQuiz4

DragonsDen_Shrine_EventScript_ElderQuiz4Correct::
	msgbox DragonsDen_Shrine_Text_RightAnswer, MSGBOX_DEFAULT
	goto DragonsDen_Shrine_EventScript_ElderQuiz5

DragonsDen_Shrine_EventScript_ElderQuiz5::
	message DragonsDen_Shrine_Text_Question5
	multichoice 20, 6, MULTI_ELDERQUIIZ5, FALSE 
	switch VAR_RESULT
	case 2, DragonsDen_Shrine_EventScript_ElderQuizFinish
	case MULTI_B_PRESSED, DragonsDen_Shrine_EventScript_ElderQuiz5
	call DragonsDen_Shrine_EventScript_ElderWrong
	goto DragonsDen_Shrine_EventScript_ElderQuiz5

DragonsDen_Shrine_EventScript_ElderWrong::
	msgbox DragonsDen_Shrine_Text_WrongAnswer1, MSGBOX_DEFAULT
	addvar VAR_DRAGONS_DEN_QUIZ, 1
	return

DragonsDen_Shrine_EventScript_ElderQuizFinish::
	msgbox DragonsDen_Shrine_Text_RightAnswer, MSGBOX_DEFAULT
	delay 20
	msgbox DragonsDen_Shrine_Text_PassedTest, MSGBOX_DEFAULT
	closemessage
	goto DragonsDen_Shrine_EventScript_ClairEnter


DragonsDen_Shrine_Text_ElderGreeting:
    .string "הממ… טוב לראות אותך כאן.\p"
    .string "אין צורך להסביר למה באת.\n"
    .string "קלייר שלחה אותך, נכון?\p"
    .string "היא לא קלה, הנערה הזאת…\n"
    .string "מצטער, אבל עליי לבחון אותך.\p"
    .string "אל דאגה, רק תצטרך לענות\n"
    .string "על כמה שאלות. מוכן?$"

DragonsDen_Shrine_Text_Question1:
    .string "מה הפוקימונים בשבילך?$"

DragonsDen_Shrine_Text_Question2:
    .string "מה עוזר לך לנצח בקרבות?$"

DragonsDen_Shrine_Text_Question3:
    .string "באיזה סוג של מאמן היית\n"
    .string "רוצה להילחם?$"

DragonsDen_Shrine_Text_Question4:
    .string "מה הכי חשוב בגידול\n"
    .string "פוקימונים?$"

DragonsDen_Shrine_Text_Question5:
    .string "פוקימונים חזקים. פוקימונים חלשים.\n"
    .string "מה חשוב יותר?$"

DragonsDen_Shrine_Text_WrongAnswer1:
    .string "הא? לא ממש הבנתי…$"

DragonsDen_Shrine_Text_WrongAnswer2:
    .string "What was it you said?$"

DragonsDen_Shrine_Text_RightAnswer:
    .string "אה, אני מבין…$"

DragonsDen_Shrine_Text_PassedTest:
    .string "הממ… אני מבין…\p"
    .string "אכפת לך מאוד מפוקימונים.\p"
    .string "ראוי לשבח.\p"
    .string "האמונה הזאת היא מה שחשוב!\p"
    .string "{PLAYER}, אל תאבד את האמונה הזאת.\p"
    .string "היא תעמוד לך בליגת הפוקימון.$"

DragonsDen_Shrine_EventScript_ClairEnter::
	clearflag FLAG_HIDE_DRAGONS_DEN_SHRINE_CLAIR
	addobject LOCALID_DRAGONSDEN3_CLAIR
	playbgm MUS_HG_CLAIR, FALSE
	playse SE_DOOR
	delay 40
	playse SE_PIN
	applymovement2 OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
	turnobject OBJ_EVENT_ID_PLAYER, DIR_SOUTH
	delay 20
	turnobject OBJ_EVENT_ID_FOLLOWER, DIR_SOUTH
	applymovement2 LOCALID_DRAGONSDEN3_CLAIR, DragonsDen_Shrine_Movement_ClairEnter
	waitmovement 0
	turnobject LOCALID_DRAGONSDEN3_ELDER, DIR_WEST	
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	turnobject OBJ_EVENT_ID_FOLLOWER, DIR_NORTH
	msgbox DragonsDen_Shrine_Text_ClairYouPassed, MSGBOX_DEFAULT
	applymovement2 LOCALID_DRAGONSDEN3_CLAIR, DragonsDen_Shrine_Movement_ClairBackup1
	waitmovement 0
	msgbox DragonsDen_Shrine_Text_ClairThatCantBe, MSGBOX_DEFAULT
	applymovement2 LOCALID_DRAGONSDEN3_CLAIR, DragonsDen_Shrine_Movement_ClairBackup2
	waitmovement 0
	msgbox DragonsDen_Shrine_Text_ClairYoureLying, MSGBOX_DEFAULT
	applymovement2 LOCALID_DRAGONSDEN3_ELDER, DragonsDen_Shrine_Movement_ElderWalkToClair
	waitmovement 0
	turnobject LOCALID_DRAGONSDEN3_CLAIR, DIR_NORTH
	msgbox DragonsDen_Shrine_Text_MustIInformLance, MSGBOX_DEFAULT
	playse SE_PIN
	applymovement2 LOCALID_DRAGONSDEN3_CLAIR, Common_Movement_ExclamationMark
	msgbox DragonsDen_Shrine_Text_IUnderstand, MSGBOX_DEFAULT
	applymovement2 LOCALID_DRAGONSDEN3_CLAIR, DragonsDen_Shrine_Movement_ClairReturnToPlayer
	waitmovement 0
	msgbox DragonsDen_Shrine_Text_HereRisingBadge, MSGBOX_DEFAULT

	message DragonsDen_Shrine_Text_PlayerReceivedRisingBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox DragonsDen_Shrine_Text_RisingBadgeExplanation, MSGBOX_DEFAULT
	setflag FLAG_BADGE08_GET
	addvar VAR_NUM_BADGES, 1

	applymovement2 LOCALID_DRAGONSDEN3_ELDER, DragonsDen_Shrine_Movement_ElderReturnToPlayer
	waitmovement 0
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	turnobject LOCALID_DRAGONSDEN3_CLAIR, DIR_NORTH
	msgbox DragonsDen_Shrine_Text_ElderScoldsClair, MSGBOX_DEFAULT
	closemessage
	delay 20
	msgbox DragonsDen_Shrine_Text_Speechless, MSGBOX_DEFAULT
	closemessage
	applymovement2 LOCALID_DRAGONSDEN3_CLAIR, DragonsDen_Shrine_Movement_ClairLeave
	waitmovement 0
	playse SE_EXIT
	fadedefaultbgm
	setflag FLAG_HIDE_DRAGONS_DEN_SHRINE_CLAIR
	removeobject LOCALID_DRAGONSDEN3_CLAIR
	clearflag FLAG_HIDE_DRAGONS_DEN_CAVERN_CLAIR
	setvar VAR_BLACKTHORN_CITY_STATE, 3
	release
	end

DragonsDen_Shrine_Movement_ClairEnter:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	face_right
	step_end

DragonsDen_Shrine_Movement_ClairBackup1:
	lock_facing_direction
	walk_fast_left
	unlock_facing_direction
	step_end

DragonsDen_Shrine_Movement_ClairBackup2:
	lock_facing_direction
	walk_slow_left
	unlock_facing_direction
	step_end

DragonsDen_Shrine_Movement_ElderWalkToClair:
	walk_left
	walk_left
	walk_left
	face_down
	step_end

DragonsDen_Shrine_Movement_ClairReturnToPlayer:
	walk_right
	walk_right
	step_end

DragonsDen_Shrine_Movement_ElderReturnToPlayer:
	walk_slow_right
	walk_slow_right
	walk_slow_right
	face_down
	step_end

DragonsDen_Shrine_Movement_ClairLeave:
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_right
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end

DragonsDen_Shrine_Text_ClairYouPassed:
    .string "נו, איך הלך?\p"
    .string "אני מניחה שאין טעם לשאול.\n"
    .string "נכשלת, נכון?\p"
    .string "…………\p"
    .string "…מה? עברת?$"

DragonsDen_Shrine_Text_ClairThatCantBe:
    .string "זה לא יכול להיות!$"

DragonsDen_Shrine_Text_ClairYoureLying:
    .string "אתה משקר!\p"
    .string "אפילו אני עוד לא קיבלתי אישור!$"

DragonsDen_Shrine_Text_MustIInformLance:
    .string "קלייר!\p"
    .string "הילד הזה ללא רבב,\n"
    .string "גם במיומנות וגם ברוח!\p"
    .string "הודי בתבוסה והעניקי לו\n"
    .string "את תג נסיקה!\p"
    .string "…או שעליי לדווח על כך ללאנס?$"

DragonsDen_Shrine_Text_IUnderstand:
    .string "א-אני מבינה…$"

DragonsDen_Shrine_Text_HereRisingBadge:
    .string "הנה, זה תג נסיקה…\p"
    .string "נו, מהר! קח אותו!$"

DragonsDen_Shrine_Text_PlayerReceivedRisingBadge:
    .string "{PLAYER} קיבל את תג נסיקה.$"

DragonsDen_Shrine_Text_RisingBadgeExplanation:
    .string "תג נסיקה יאפשר לפוקימונים שלך\n"
    .string "להשתמש במהלך לטיפוס על מפלים.\p"
    .string "בנוסף, כל הפוקימונים יכירו בך כמאמן\n"
    .string "ויצייתו לכל פקודה שלך בלי עוררין.$"

DragonsDen_Shrine_Text_ElderScoldsClair:
    .string "קלייר…\p"
    .string "הרהרי במה שחסר לך\n"
    .string "ויש לילד הזה.$"

DragonsDen_Shrine_Text_Speechless:
    .string "..................................$"

DragonsDen_Shrine_Text_ComeAgain:
    .string "אתה מוזמן לשוב, אם תחפוץ בכך.$"

DragonsDen_Shrine_Text_SilverIsInTraining:
    .string "A boy close to your age is in\n"
    .string "training here.\p"
    .string "He is much like CLAIR when she was\n"
    .string "younger. It is a little worrisome…$"

DragonsDen_Shrine_EventScript_Elder2::
	msgbox DragonsDen_Shrine_Text_Elder2, MSGBOX_NPC
	end

DragonsDen_Shrine_EventScript_Elder3::
	msgbox DragonsDen_Shrine_Text_Elder3, MSGBOX_NPC
	end

DragonsDen_Shrine_Text_Elder2:
    .string "עבר זמן רב מאז שמאמן זכה\n"
    .string "בהכרה הנדירה של המאסטר שלנו.\p"
    .string "למעשה, האחרון שזכה בה\n"
    .string "היה המאסטר לאנס.$"

DragonsDen_Shrine_Text_Elder3:
    .string "אתה מכיר את המאסטר הצעיר לאנס?\p"
    .string "הוא נראה בדיוק כמו המאסטר\n"
    .string "שלנו כשהיה צעיר.\p"
    .string "זה בדם שלהם.$"

DragonsDen_Shrine_EventScript_ElderChooseDratini::
	goto_if_eq VAR_DRAGONS_DEN_QUIZ, 0, DragonsDen_Shrine_EventScript_ElderGiveSpecialDratini
	goto DragonsDen_Shrine_EventScript_ElderGiveBasicDratini

DragonsDen_Shrine_EventScript_ElderGiveBasicDratini::
	goto_if_set FLAG_GOT_DRATINI, DragonsDen_Shrine_EventScript_ElderAlreadyGotDratini
	msgbox DragonsDen_Shrine_Text_TakeThisDratini, MSGBOX_DEFAULT

	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_DRATINI
	bufferspeciesname STR_VAR_1, SPECIES_DRATINI
	givemon SPECIES_DRATINI, 15
	call Common_EventScript_GiftMon

	msgbox DragonsDen_Shrine_Text_SymbolicDragon, MSGBOX_DEFAULT
	setflag FLAG_GOT_DRATINI
	release
	end

DragonsDen_Shrine_EventScript_ElderGiveSpecialDratini::
	goto_if_set FLAG_GOT_DRATINI, DragonsDen_Shrine_EventScript_ElderAlreadyGotDratini
	msgbox DragonsDen_Shrine_Text_TakeThisDratini, MSGBOX_DEFAULT

	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_DRATINI
	bufferspeciesname STR_VAR_1, SPECIES_DRATINI
	givenamedmon 4
	call Common_EventScript_GiftMonNamed

	msgbox DragonsDen_Shrine_Text_SymbolicDragon, MSGBOX_DEFAULT
	setflag FLAG_GOT_DRATINI
	release
	end

DragonsDen_Shrine_EventScript_ElderAlreadyGotDratini::
	msgbox DragonsDen_Shrine_Text_ClairsGrandfather, MSGBOX_DEFAULT
	release
	end

DragonsDen_Shrine_Text_TakeThisDratini:
    .string "הממ… טוב לראות אותך כאן.\p"
    .string "הגעת בעיתוי מבורך.\p"
    .string "יש לי משהו בשבילך.\p"
    .string "קח את הדרטיני הזה כהוכחה\n"
    .string "לכך שהכרתי בערכך.$"

DragonsDen_Shrine_Text_SymbolicDragon:
    .string "פוקימוני דרקון הם הסמל\n"
    .string "של השבט שלנו.\p"
    .string "הוכחת שאפשר להפקיד\n"
    .string "בידיך אחד מהם.$"

DragonsDen_Shrine_Text_ClairsGrandfather:
    .string "נראה שקלייר למדה ממך\n"
    .string "שיעור יקר מפז.\p"
    .string "כסבא שלה, אני מודה לך.$"
