AzaleaTown_KurtsHouse_hns_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, AzaleaTown_KurtsHouse_OnFrame
	map_script MAP_SCRIPT_ON_TRANSITION, AzaleaTown_KurtsHouse_OnTransition
	.byte 0

AzaleaTown_KurtsHouse_OnTransition::
	goto_if_eq VAR_AZALEA_TOWN_STATE, 3, AzaleaTown_KurtsHouse_EventScript_ReturnFromWellSetup
	end

AzaleaTown_KurtsHouse_OnFrame::
	map_script_2 VAR_AZALEA_TOWN_STATE, 3, AzaleaTown_KurtsHouse_EventScript_ReturnFromWell
	.2byte 0

AzaleaTown_KurtsHouse_EventScript_KurtBefore::
	lock
	faceplayer
	msgbox KurtsHouse_Text_KurtMakingBallsMustWait, MSGBOX_DEFAULT
	closemessage
	goto_if_eq VAR_FACING, DIR_NORTH, AzaleaTown_KurtsHouse_EventScript_PlayerMove
	applymovement LOCALID_AZALEA_TOWN_KURT_BEFORE, AzaleaTown_KurtsHouse_Movement_KurtWalkDown
	waitmovement 0
	playse SE_EXIT
	removeobject LOCALID_AZALEA_TOWN_KURT_BEFORE
	setflag FLAG_HIDE_KURT_1
	setflag FLAG_HIDE_AZALEA_TOWN_WELL_ROCKET
	setvar VAR_AZALEA_TOWN_STATE, 2
	release
	end

AzaleaTown_KurtsHouse_EventScript_PlayerMove::
	applymovement OBJ_EVENT_ID_PLAYER, AzaleaTown_KurtsHouse_Movement_Player
	waitmovement 0
	applymovement LOCALID_AZALEA_TOWN_KURT_BEFORE, AzaleaTown_KurtsHouse_Movement_KurtWalkDown
	waitmovement 0
	playse SE_EXIT
	removeobject LOCALID_AZALEA_TOWN_KURT_BEFORE
	setflag FLAG_HIDE_KURT_1
	setflag FLAG_HIDE_AZALEA_TOWN_WELL_ROCKET
	release
	end

AzaleaTown_KurtsHouse_EventScript_Girl::
	lock
	faceplayer
	goto_if_unset FLAG_HIDE_KURT_2, AzaleaTown_KurtsHouse_EventScript_Girl2
	goto_if_set FLAG_HIDE_KURT_1, AzaleaTown_KurtsHouse_EventScript_Girl3
	msgbox KurtsHouse_Text_GranddaughterSlowpokeGone, MSGBOX_DEFAULT
	release
	end

AzaleaTown_KurtsHouse_EventScript_Girl2::
	goto_if_eq VAR_AZALEA_TOWN_STATE, 3, AzaleaTown_KurtsHouse_EventScript_Girl4
	goto_if_eq VAR_AZALEA_TOWN_STATE, 4, AzaleaTown_KurtsHouse_EventScript_Girl4
	goto_if_eq VAR_AZALEA_TOWN_STATE, 5, AzaleaTown_KurtsHouse_EventScript_Girl4
	goto_if_eq VAR_AZALEA_TOWN_STATE, 6, AzaleaTown_KurtsHouse_EventScript_Girl4
	goto_if_eq VAR_AZALEA_TOWN_STATE, 8, AzaleaTown_KurtsHouse_EventScript_Girl5
	goto_if_eq VAR_AZALEA_TOWN_STATE, 9, AzaleaTown_KurtsHouse_EventScript_Girl5

	msgbox KurtsHouse_Text_GranddaughterDad, MSGBOX_DEFAULT
	closemessage
	release
	end

AzaleaTown_KurtsHouse_EventScript_Girl3::
	msgbox KurtsHouse_Text_GranddaughterLonely, MSGBOX_DEFAULT
	closemessage
	release
	end

AzaleaTown_KurtsHouse_EventScript_Girl4::
	msgbox KurtsHouse_Text_GranddaughterSlowpokeBack, MSGBOX_DEFAULT
	closemessage
	release
	end	

AzaleaTown_KurtsHouse_EventScript_Girl5::
	msgbox KurtsHouse_Text_GranddaughterSound, MSGBOX_DEFAULT
	closemessage
	release
	end	

AzaleaTown_KurtsHouse_EventScript_ReturnFromWellSetup::
	setobjectmovementtype LOCALID_AZALEA_TOWN_KURT, MOVEMENT_TYPE_FACE_DOWN
	end

AzaleaTown_KurtsHouse_EventScript_ReturnFromWell::
	lock
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	msgbox KurtsHouse_Text_KurtHonoredToMakeBalls, MSGBOX_DEFAULT
	giveitem ITEM_FAST_BALL
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_BagIsFull
	msgbox KurtsHouse_Text_KurtBallsFromApricorns, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_AZALEA_TOWN_KURT, DIR_NORTH
	setvar VAR_AZALEA_TOWN_STATE, 4
	release
	end

AzaleaTown_KurtsHouse_EventScript_KurtCheckGSBall::
	checkitem ITEM_GS_BALL
	goto_if_eq VAR_RESULT, TRUE, AzaleaTown_KurtsHouse_EventScript_KurtGsBall
	return

AzaleaTown_KurtsHouse_EventScript_Kurt::
	lock
	faceplayer
	goto_if_eq VAR_AZALEA_TOWN_STATE, 8, AzaleaTown_KurtsHouse_EventScript_KurtGsBall2
	goto_if_eq VAR_AZALEA_TOWN_STATE, 9, AzaleaTown_KurtsHouse_EventScript_KurtGsBall3
	msgbox KurtsHouse_Text_KurtAskYouHaveAnApricorn, MSGBOX_DEFAULT
	closemessage
	call_if_unset FLAG_CAUGHT_CELEBI, AzaleaTown_KurtsHouse_EventScript_KurtCheckGSBall
AzaleaTown_KurtsHouse_EventScript_Kurt2::
	special CreateKurtBallShop
	waitstate
	goto_if_eq VAR_RESULT, FALSE, AzaleaTown_KurtsHouse_EventScript_KurtCancel
	playse SE_BANG
	applymovement LOCALID_AZALEA_TOWN_KURT, AzaleaTownKurt_Movement_Making_Ball
	waitmovement 0
	playse SE_BANG
	applymovement LOCALID_AZALEA_TOWN_KURT, AzaleaTownKurt_Movement_Making_Ball
	waitmovement 0
	call_if_eq VAR_FACING, DIR_EAST, AzaleaTown_KurtsHouse_EventScript_TurnWest
	call_if_eq VAR_FACING, DIR_WEST, AzaleaTown_KurtsHouse_EventScript_TurnEast
	call_if_eq VAR_FACING, DIR_NORTH, AzaleaTown_KurtsHouse_EventScript_TurnSouth
	goto_if_eq VAR_0x8005, 1, AzaleaTown_KurtsHouse_EventScript_SingularBall
	bufferitemname STR_VAR_1, VAR_0x8004
	buffernumberstring STR_VAR_2, VAR_0x8005
	msgbox KurtsHouse_Text_KurtFinishedPlural, MSGBOX_DEFAULT
	message KurtsHouse_Text_KurtObtainedPlural
	waitmessage
	playfanfare MUS_OBTAIN_ITEM
	waitfanfare
	additem VAR_0x8004, VAR_0x8005
	msgbox KurtsHouse_Text_KurtTurnedOutGreat, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_AZALEA_TOWN_KURT, DIR_NORTH
	release
	end

AzaleaTown_KurtsHouse_EventScript_TurnSouth::
	turnobject LOCALID_AZALEA_TOWN_KURT, DIR_SOUTH
	return
AzaleaTown_KurtsHouse_EventScript_TurnWest::
	turnobject LOCALID_AZALEA_TOWN_KURT, DIR_WEST
	return
AzaleaTown_KurtsHouse_EventScript_TurnEast::
	turnobject LOCALID_AZALEA_TOWN_KURT, DIR_EAST
	return


AzaleaTown_KurtsHouse_EventScript_SingularBall::
	bufferitemname STR_VAR_1, VAR_0x8004
	msgbox KurtsHouse_Text_KurtFinishedSingular, MSGBOX_DEFAULT
	message KurtsHouse_Text_KurtObtainedSingular
	waitmessage
	playfanfare MUS_OBTAIN_ITEM
	waitfanfare
	additem VAR_0x8004, VAR_0x8005
	msgbox KurtsHouse_Text_KurtTurnedOutGreat, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_AZALEA_TOWN_KURT, DIR_NORTH
	release
	end

AzaleaTown_KurtsHouse_EventScript_KurtCancel::
	closemessage
	turnobject LOCALID_AZALEA_TOWN_KURT, DIR_NORTH
	release
	end

AzaleaTown_KurtsHouse_EventScript_KurtGsBall::
	msgbox KurtsHouse_Text_KurtWhatIsThat, MSGBOX_DEFAULT
	closemessage
	removeitem ITEM_GS_BALL
	playse SE_BANG
	applymovement LOCALID_AZALEA_TOWN_KURT, AzaleaTownKurt_Movement_Making_Ball
	waitmovement 0
	playse SE_BANG
	applymovement LOCALID_AZALEA_TOWN_KURT, AzaleaTownKurt_Movement_Making_Ball
	waitmovement 0
	faceplayer
	msgbox KurtsHouse_Text_KurtThisBallStartedToShake, MSGBOX_DEFAULT
	closemessage
	playse SE_M_PETAL_DANCE
	waitse
	playse SE_PIN
	applymovement LOCALID_AZALEA_TOWN_KURT, Common_Movement_ExclamationMark
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
	waitmovement OBJ_EVENT_ID_PLAYER
	waitse
	playse SE_M_PETAL_DANCE
	waitse
	applymovement LOCALID_AZALEA_TOWN_KURT, AzaleaTownKurt_Movement_Look_Around
	applymovement OBJ_EVENT_ID_PLAYER, AzaleaTownKurt_Movement_Look_Around
	waitmovement 0
	waitmovement 0
AzaleaTown_KurtsHouse_EventScript_KurtGsBall2::
	msgbox KurtsHouse_Text_Kurt_Whatwasthat, MSGBOX_DEFAULT
	setvar VAR_AZALEA_TOWN_STATE, 8
	closemessage
	release
	end

AzaleaTown_KurtsHouse_EventScript_KurtGsBall3::
	msgbox KurtsHouse_Text_Forest, MSGBOX_DEFAULT
	closemessage
	delay 30
	msgbox KurtsHouse_Text_BallAnyway, MSGBOX_DEFAULT
	closemessage
	goto AzaleaTown_KurtsHouse_EventScript_Kurt2
	release
	end
KurtsHouse_Text_BallAnyway:
	.string "בכל מקרה, להכין לך כמה כדורים?$"

AzaleaTown_KurtsHouse_EventScript_OakPhoto::
	msgbox KurtsHouse_Text_OakPhoto, MSGBOX_SIGN
	closemessage
	end

AzaleaTown_KurtsHouse_EventScript_CelebiStatue::
	msgbox KurtsHouse_Text_CelebiStatue, MSGBOX_SIGN
	closemessage
	end

AzaleaTownKurt_Movement_Look_Around:
	face_left
	delay_8
	face_right
	delay_8
	face_up
	delay_8
	face_down
	delay_8
	face_left
	step_end

AzaleaTownKurt_Movement_Making_Ball:
	face_up
	walk_in_place_fast_up
	delay_8
	walk_in_place_fast_up
	delay_8
	walk_in_place_fast_up
	step_end

AzaleaTown_KurtsHouse_Movement_Player:
	face_right
	lock_facing_direction
	walk_left
	unlock_facing_direction
	step_end

AzaleaTown_KurtsHouse_Movement_KurtWalkDown:
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end

KurtsHouse_Text_KurtGetStarted:
	.string "KURT: I'll get started right now!$"

KurtsHouse_Text_KurtMakingBallsMustWait:
	.string "הממ? מי אתה?\p"
	.string "{PLAYER}, אה? אתה רוצה\n"
	.string "שאכין לך כמה כדורים?\p"
	.string "סליחה, אבל זה יצטרך לחכות.\p"
	.string "אתה מכיר את צוות רוקט? אה, לא חשוב.\p"
	.string "אספר לך בכל זאת.\p"
	.string "צוות רוקט זו כנופיה מרושעת שמשתמשת\n"
	.string "בפוקימונים לעבודה המלוכלכת שלה.\p"
	.string "כביכול, הם התפרקו לפני שלוש שנים.\p"
	.string "בכל אופן, הם בבאר, וחותכים\n"
	.string "זנבות סלופוק כדי למכור אותם!\p"
	.string "אז אני הולך ללמד אותם לקח כואב!\p"
	.string "החזיקו מעמד, סלופוק! קורט הזקן בדרך!$"

KurtsHouse_Text_KurtHonoredToMakeBalls:
	.string "קורט: היי, {PLAYER}!\p"
	.string "התנהגת כמו גיבור אמיתי בבאר.\p"
	.string "אני אוהב את הסגנון שלך!\p"
	.string "זה יהיה לי לכבוד להכין\n"
	.string "כדורים למאמן כמוך.\p"
	.string "זה כל מה שיש לי כרגע,\n"
	.string "אבל הנה, זה בשבילך.$"

KurtsHouse_Text_KurtBallsFromApricorns:
	.string "קורט: אני מכין כדורים מפירות.\p"
	.string "אפשר לאסוף אותם מעצים\n"
	.string "ולהביא אותם אליי.\p"
	.string "אני אכין מהם פוכדורים.$"

KurtsHouse_Text_KurtAskYouHaveAnApricorn:
	.string "קורט: יש לך פירות בשבילי?\p"
	.string "יופי! אהפוך אותם לפוכדורים.$"

KurtsHouse_Text_KurtThatsALetdown:
	.string "KURT: I don't see any {STR_VAR_1}s!$"

KurtsHouse_Text_KurtFinishedPlural:
	.string "קורט: {PLAYER}!\n"
	.string "הכדורים מוכנים: {STR_VAR_1}. הנה!$"

KurtsHouse_Text_KurtObtainedPlural:
	.string "{PLAYER} קיבל {STR_VAR_2}\n"
	.string "יחידות של {STR_VAR_1}!$"

KurtsHouse_Text_KurtFinishedSingular:
	.string "קורט: {PLAYER}!\n"
	.string "הכדור מוכן: {STR_VAR_1}. הנה!$"

KurtsHouse_Text_KurtObtainedSingular:
	.string "{PLAYER} קיבל את\n"
	.string "{STR_VAR_1}!$"

KurtsHouse_Text_KurtTurnedOutGreat:
	.string "קורט: זה יצא מצוין.\p"
	.string "כדאי לנסות לתפוס איתו פוקימונים.$"

KurtsHouse_Text_KurtWhatIsThat:
	.string "מ-מה זה?\p"
	.string "אף פעם לא ראיתי כזה.\p"
	.string "זה נראה כמו פוכדור,\n"
	.string "אבל כנראה שזה משהו אחר.\p"
	.string "אבדוק את זה בשבילך.$"

KurtsHouse_Text_KurtImCheckingItNow:
	.string "I'm checking it now.$"

KurtsHouse_Text_KurtAhHaISee:
	.string "Ah-ha! I see! So…$"

KurtsHouse_Text_KurtThisBallStartedToShake:
	.string "{PLAYER}!\p"
	.string "הכדור הזה התחיל לרעוד\n"
	.string "בזמן שבדקתי אותו.\p"
	.string "חייב להיות בו משהו מיוחד!$"

KurtsHouse_Text_Kurt_Whatwasthat:
	.string "מה היה הקול הזה?!\p"
	.string "בוא נצא החוצה לבדוק!$"

KurtsHouse_Text_GranddaughterSlowpokeGone:
	.string "הסלופוק נעלמו…\n"
	.string "אנשים רעים לקחו אותם?$"

KurtsHouse_Text_GranddaughterLonely:
	.string "סבא יצא… אני כל כך בודדה…$"

KurtsHouse_Text_GranddaughterSlowpokeBack:
	.string "הסלופוק שאבא שלי נתן לי חזר!\p"
	.string "גם הזנב שלו צומח מחדש!$"

KurtsHouse_Text_GranddaughterDad:
	.string "אבא עובד בחברת סילף,\n"
	.string "ושם הוא חוקר פוכדורים.\p"
	.string "אני צריכה להישאר בבית\n"
	.string "עם סבא וסלופוק.$"

KurtsHouse_Text_GranddaughterHelp:
	.string "I get to help Grandpa now!\p"
	.string "We'll make good BALLS\n"
	.string "for you, so please wait!$"

KurtsHouse_Text_GranddaughterFun:
	.string "It's fun to make BALLS!$"

KurtsHouse_Text_GranddaughterSound:
	.string "הקול הזה הגיע\n"
	.string "מיער אילקס????$"

KurtsHouse_Text_Forest:
	.string "כבר בדקת את יער אילקס?\n"
	.string "נשמע שהוא מאוד סוער.$"

KurtsHouse_Text_Slowpoke:
	.string "SLOWPOKE: … Yawn?$"

KurtsHouse_Text_OakPhoto:
	.string "…פרופ' אוק בצעירותו?$"

KurtsHouse_Text_CelebiStatue:
	.string "זה פסל של מגן היער.$"
