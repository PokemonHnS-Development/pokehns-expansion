GoldenrodCity_RadioTower_1F_hns_MapScripts::
	.byte 0

RadioTower1F_EventScript_Grunt::
	lock
	faceplayer
	msgbox RadioTower1F_Text_GruntM3Seen, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_GRUNT_2_HNS,  RadioTower1F_Text_GruntM3Beaten
	msgbox RadioTower1F_Text_GruntM3After, MSGBOX_AUTOCLOSE
	turnobject LOCALID_GOLDENROD_RADIOTOWER_GRUNT, DIR_EAST
	applymovement2 LOCALID_GOLDENROD_RADIOTOWER_GRUNT, RadioTower1F_Movement_Rocket
	waitmovement 0
	playse SE_EXIT
	removeobject LOCALID_GOLDENROD_RADIOTOWER_GRUNT
	setflag FLAG_HIDE_ROCKET_GOLDENROD_RADIOTOWER_1
	release
	end

RadioTower1F_Movement_Rocket::
	walk_in_place_right
	step_end

RadioTower1F_EventScript_Lass::
	lock
	faceplayer
	msgbox RadioTower1F_Text_Lass, MSGBOX_DEFAULT
	closemessage
	release
	end

RadioTower1F_EventScript_Youngster::
	lock
	faceplayer
	msgbox RadioTower1F_Text_Youngster, MSGBOX_DEFAULT
	closemessage
	release
	end

RadioTower1F_EventScript_Whitney::
	lock
	faceplayer
	msgbox RadioTower1F_Text_Whitney1, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_GOLDENROD_RADIOTOWER_WHITNEY, DIR_SOUTH
	release
	end

RadioTower1F_Text_Whitney1::
	.string "ויטני: היי!\p"
	.string "קוראים לי ויטני!\p"
	.string "שמעתי על החידון שבו אפשר\n"
	.string "לזכות בכרטיס רדיו, אז באתי לקבל אחד…\p"
	.string "אבל החידון הזה כל כך קשה!$"

RadioTower1F_Text_Whitney2::
	.string "ויטני: וואו, הצלחת!\p"
	.string "הייתי בטוחה שהתשובה לשאלה השלישית\n"
	.string "היא בלוטים! אופס!\p"
	.string "הגיע הזמן לחזור למכון!$"

RadioTower1F_EventScript_Reception::
	lock
	faceplayer
	msgbox RadioTower1F_Text_ReceptionistWelcome, MSGBOX_DEFAULT
	goto_if_unset FLAG_ENABLE_RADIO, RadioTower1F_EventScript_ReceptionOfferQuiz
	msgbox RadioTower1F_Text_ReceptionistNoTours, MSGBOX_DEFAULT
	closemessage
	release
	end

RadioTower1F_EventScript_ReceptionOfferQuiz::
	msgbox RadioTower1F_Text_RadioCardWomanOfferQuiz, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE, RadioTower1F_EventScript_ReceptionQuiz1
	msgbox RadioTower1F_Text_DeclineQuiz, MSGBOX_DEFAULT
	closemessage
	release
	end

RadioTower1F_EventScript_ReceptionQuiz1::
	msgbox RadioTower1F_Text_QuizQuestion1, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE, RadioTower1F_EventScript_ReceptionQuiz2
	msgbox RadioTower1F_Text_WrongAnswer, MSGBOX_DEFAULT
	closemessage
	release
	end

RadioTower1F_EventScript_ReceptionQuiz2::
	msgbox RadioTower1F_Text_QuizQuestion2, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE, RadioTower1F_EventScript_ReceptionQuiz3
	msgbox RadioTower1F_Text_WrongAnswer, MSGBOX_DEFAULT
	closemessage
	release
	end

RadioTower1F_EventScript_ReceptionQuiz3::
	msgbox RadioTower1F_Text_QuizQuestion3, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, RadioTower1F_EventScript_ReceptionQuiz4
	msgbox RadioTower1F_Text_WrongAnswer, MSGBOX_DEFAULT
	closemessage
	release
	end

RadioTower1F_EventScript_ReceptionQuiz4::
	msgbox RadioTower1F_Text_QuizQuestion4, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE, RadioTower1F_EventScript_ReceptionQuiz5
	msgbox RadioTower1F_Text_WrongAnswer, MSGBOX_DEFAULT
	closemessage
	release
	end

RadioTower1F_EventScript_ReceptionQuiz5::
	msgbox RadioTower1F_Text_QuizQuestion5, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, RadioTower1F_EventScript_ReceptionGiveRadio
	msgbox RadioTower1F_Text_WrongAnswer, MSGBOX_DEFAULT
	closemessage
	release
	end

RadioTower1F_EventScript_ReceptionGiveRadio::
	msgbox RadioTower1F_Text_QuizWin, MSGBOX_DEFAULT
	closemessage
	playfanfare MUS_RG_OBTAIN_KEY_ITEM
	msgbox RadioTower1F_Text_PokegearRadio, MSGBOX_AUTOCLOSE
	waitfanfare
	msgbox RadioTower1F_Text_TuneIn, MSGBOX_DEFAULT
	closemessage
	playse SE_PIN
	applymovement LOCALID_GOLDENROD_RADIOTOWER_WHITNEY, Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_GOLDENROD_RADIOTOWER_WHITNEY
	turnobject LOCALID_GOLDENROD_RADIOTOWER_WHITNEY, DIR_EAST
	delay 20
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	msgbox RadioTower1F_Text_Whitney2, MSGBOX_DEFAULT
	closemessage
	applymovement2 LOCALID_GOLDENROD_RADIOTOWER_WHITNEY, GoldenrodCity_RadioTower_4F_Movement_WhitneyLeave
	waitmovement 0
	playse SE_EXIT
	removeobject LOCALID_GOLDENROD_RADIOTOWER_WHITNEY
	setflag FLAG_ENABLE_RADIO
	setflag FLAG_HIDE_GOLDENROD_BEAUTY
	setvar VAR_GOLDENROD_CITY_STATE, 2
	release
	end

GoldenrodCity_RadioTower_4F_Movement_WhitneyLeave:
	face_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_in_place_down
	step_end

GoldenrodCity_RadioTower_1F_EventScript_Sign::
	lock
	msgbox RadioTower1F_Text_Directory, MSGBOX_SIGN
	closemessage
	release
	end

RadioTower1F_Text_ReceptionistWelcome:
    .string "ברוכים הבאים!$"

RadioTower1F_Text_ReceptionistNoTours:
    .string "שלום. מצטערת, אבל היום\n"
    .string "אין לנו סיורים.$"

RadioTower1F_Text_RadioCardWomanOfferQuiz:
    .string "יש לנו עכשיו מבצע חידון מיוחד.\p"
    .string "מי שעונה נכון על חמש שאלות\n"
    .string "זוכה בכרטיס רדיו לפוקיגיר.\p"
    .string "בעזרתו תוכלו, אתה והפוקימונים שלך,\n"
    .string "להשמיע מוזיקה בכל זמן ובכל מקום.\p"
    .string "תרצה להשתתף בחידון?$"

RadioTower1F_Text_QuizQuestion1:
    .string "שאלה 1:\p"
    .string "האם יש פוקימון שמופיע רק\n"
    .string "בשעות היום?$"

RadioTower1F_Text_QuizQuestion2:
    .string "נכון!\n"
    .string "שאלה 2:\p"
    .string "האם הטענה הזו נכונה?\p"
    .string "אי אפשר לקנות פירות בחנות פוקימון.$"

RadioTower1F_Text_QuizQuestion3:
    .string "בול!\n"
    .string "שאלה 3:\p"
    .string "האם קורט, יוצר הפוכדורים,\n"
    .string "משתמש בבלוטים כחומרי גלם?$"

RadioTower1F_Text_QuizQuestion4:
    .string "עד כאן הכול טוב!\n"
    .string "שאלה 4:\p"
    .string "האם פלקנר הוא מנהיג מכון ויולט\n"
    .string "שמשתמש בפוקימוני ציפורים?$"

RadioTower1F_Text_QuizQuestion5:
    .string "וואו! שוב צדקת!\n"
    .string "הנה השאלה האחרונה:\p"
    .string "האם על הגלגלים במכונות המזל של\n"
    .string "משחקיית גולדנרוד יש צ'רמנדר?$"

RadioTower1F_Text_QuizWin:
    .string "בינגו! צדקת!\n"
    .string "כל הכבוד!\p"
    .string "הנה הפרס שלך: כרטיס רדיו!$"

RadioTower1F_Text_PokegearRadio:
    .string "הפוקיגיר של {PLAYER} יכול\n"
    .string "עכשיו לשמש גם כרדיו!$"

RadioTower1F_Text_TuneIn:
    .string "נשמח שתאזין לתוכניות הרדיו שלנו.$"

RadioTower1F_Text_WrongAnswer:
    .string "אוי, חבל.\n"
    .string "מצטערת, אבל טעית.\p"
    .string "אפשר לנסות שוב!$"

RadioTower1F_Text_DeclineQuiz:
    .string "אה. הבנתי. אם תשנה את דעתך,\n"
    .string "אפשר לפנות אליי.$"

RadioTower1F_Text_Lass:
    .string "בן הוא די-ג'יי נהדר.\p"
    .string "הקול המתוק שלו ממיס אותי!$"

RadioTower1F_Text_Youngster:
    .string "אני אוהב את מרי מ”שיחות פוקימון”.\p"
    .string "אבל אני מכיר רק את הקול שלה.$"

RadioTower1F_Text_GruntM3Seen:
    .string "סוף סוף השתלטנו על\n"
    .string "מגדל הרדיו!\p"
    .string "עכשיו כולם יחוו את האימה\n"
    .string "האמיתית של צוות רוקט!\p"
    .string "אנחנו נראה לך כמה אנחנו מפחידים!$"

RadioTower1F_Text_GruntM3Beaten:
    .string "חזק מדי! סליחה, בוס…$"

RadioTower1F_Text_GruntM3After:
    .string "אתה חזק מדי.\p"
    .string "התוכנית שלנו עלולה להיהרס.\n"
    .string "אני חייב להזהיר את האחרים…$"

RadioTower1F_Text_Directory:
    .string "קומה 1: קבלה\n"
    .string "קומה 2: מכירות\p"
    .string "קומה 3: משאבי אנוש\n"
    .string "קומה 4: הפקה\p"
    .string "קומה 5: לשכת מנהל התחנה$"

RadioTower1F_Text_GotRadio:
	.string "{PLAYER} got the RADIO CARD\n"
	.string "for the POKéGEAR!$"

GoldenrodCity_RadioTower_1F_EventScript_LotteryClerk::
	lock
	faceplayer
	dotimebasedevents
	goto_if_ne VAR_POKELOT_PRIZE_ITEM, ITEM_NONE, GoldenrodCity_RadioTower_1F_EventScript_GivePrizeFromEarlier
	goto_if_set FLAG_DAILY_PICKED_LOTO_TICKET, GoldenrodCity_RadioTower_1F_EventScript_ComeBackTomorrow
	msgbox GoldenrodCity_RadioTower_1F_Text_LotteryCornerDrawTicket, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, GoldenrodCity_RadioTower_1F_EventScript_PleaseVisitAgain
	setflag FLAG_DAILY_PICKED_LOTO_TICKET
	message GoldenrodCity_RadioTower_1F_Text_PleasePickTicket
	waitmessage
	special RetrieveLotteryNumber
	copyvar VAR_0x8008, VAR_RESULT
	special BufferLottoTicketNumber
	msgbox GoldenrodCity_RadioTower_1F_Text_TicketNumberIsXPleaseWait, MSGBOX_DEFAULT
	applymovement 4, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	playse SE_PC_ON
	special PickLotteryCornerTicket
	applymovement 4, Common_Movement_FacePlayer
	waitmovement 0
	goto_if_eq VAR_0x8004, 0, GoldenrodCity_RadioTower_1F_EventScript_NoMatch
	incrementgamestat GAME_STAT_WON_POKEMON_LOTTERY
	call_if_eq VAR_0x8006, 0, GoldenrodCity_RadioTower_1F_EventScript_TicketMatchPartyMon
	call_if_eq VAR_0x8006, 1, GoldenrodCity_RadioTower_1F_EventScript_TicketMatchPCMon
	bufferitemname STR_VAR_1, VAR_0x8005
	call_if_eq VAR_0x8004, 1, GoldenrodCity_RadioTower_1F_EventScript_TwoDigitMatch
	call_if_eq VAR_0x8004, 2, GoldenrodCity_RadioTower_1F_EventScript_ThreeDigitMatch
	call_if_eq VAR_0x8004, 3, GoldenrodCity_RadioTower_1F_EventScript_FourDigitMatch
	call_if_eq VAR_0x8004, 4, GoldenrodCity_RadioTower_1F_EventScript_FullMatch
	giveitem VAR_0x8005
	goto_if_eq VAR_RESULT, FALSE, GoldenrodCity_RadioTower_1F_EventScript_RecordPrizeNoRoom
	special TryPutLotteryWinnerReportOnAir
	goto GoldenrodCity_RadioTower_1F_EventScript_PleaseVisitAgain2
	end

GoldenrodCity_RadioTower_1F_EventScript_TicketMatchPartyMon::
	msgbox GoldenrodCity_RadioTower_1F_Text_TicketMatchesPartyMon, MSGBOX_DEFAULT
	return

GoldenrodCity_RadioTower_1F_EventScript_TicketMatchPCMon::
	msgbox GoldenrodCity_RadioTower_1F_Text_TicketMatchesPCMon, MSGBOX_DEFAULT
	return

GoldenrodCity_RadioTower_1F_EventScript_ComeBackTomorrow::
	msgbox GoldenrodCity_RadioTower_1F_Text_ComeBackTomorrow, MSGBOX_DEFAULT
	release
	end

GoldenrodCity_RadioTower_1F_EventScript_PleaseVisitAgain::
	msgbox GoldenrodCity_RadioTower_1F_Text_PleaseVisitAgain, MSGBOX_DEFAULT
	release
	end

GoldenrodCity_RadioTower_1F_EventScript_NoMatch::
	msgbox GoldenrodCity_RadioTower_1F_Text_NoNumbersMatched, MSGBOX_DEFAULT
	goto GoldenrodCity_RadioTower_1F_EventScript_PleaseVisitAgain2
	end

GoldenrodCity_RadioTower_1F_EventScript_PleaseVisitAgain2::
	msgbox GoldenrodCity_RadioTower_1F_Text_PleaseVisitAgain2, MSGBOX_DEFAULT
	release
	end

GoldenrodCity_RadioTower_1F_EventScript_TwoDigitMatch::
	msgbox GoldenrodCity_RadioTower_1F_Text_TwoDigitsMatched, MSGBOX_DEFAULT
	return

GoldenrodCity_RadioTower_1F_EventScript_ThreeDigitMatch::
	msgbox GoldenrodCity_RadioTower_1F_Text_ThreeDigitsMatched, MSGBOX_DEFAULT
	return

GoldenrodCity_RadioTower_1F_EventScript_FourDigitMatch::
	msgbox GoldenrodCity_RadioTower_1F_Text_FourDigitsMatched, MSGBOX_DEFAULT
	return

GoldenrodCity_RadioTower_1F_EventScript_FullMatch::
	msgbox GoldenrodCity_RadioTower_1F_Text_AllFiveDigitsMatched, MSGBOX_DEFAULT
	return

GoldenrodCity_RadioTower_1F_EventScript_RecordPrizeNoRoom::
	copyvar VAR_POKELOT_PRIZE_PLACE, VAR_0x8004
	copyvar VAR_POKELOT_PRIZE_ITEM, VAR_0x8005
	goto GoldenrodCity_RadioTower_1F_EventScript_NoRoomForPrize
	end

GoldenrodCity_RadioTower_1F_EventScript_NoRoomForPrize::
	msgbox GoldenrodCity_RadioTower_1F_Text_NoRoomForThis, MSGBOX_DEFAULT
	release
	end

GoldenrodCity_RadioTower_1F_EventScript_GivePrizeFromEarlier::
	msgbox GoldenrodCity_RadioTower_1F_Text_PrizeWeveBeenHolding, MSGBOX_DEFAULT
	giveitem VAR_POKELOT_PRIZE_ITEM
	goto_if_eq VAR_RESULT, FALSE, GoldenrodCity_RadioTower_1F_EventScript_NoRoomForPrize
	copyvar VAR_0x8004, VAR_POKELOT_PRIZE_PLACE
	copyvar VAR_0x8005, VAR_POKELOT_PRIZE_ITEM
	special TryPutLotteryWinnerReportOnAir
	setvar VAR_POKELOT_PRIZE_ITEM, ITEM_NONE
	setvar VAR_POKELOT_PRIZE_PLACE, 0
	release
	end

GoldenrodCity_RadioTower_1F_Text_LotteryCornerDrawTicket:
	.string "זו פינת הגרלת הפוקימון.\p"
	.string "אם מספר הכרטיס תואם למספר המזהה של\n"
	.string "אחד הפוקימונים שלך, תקבל מתנה נהדרת.\p"
	.string "תרצה לשלוף כרטיס לוטו פוקימון?$"

GoldenrodCity_RadioTower_1F_Text_ComeBackTomorrow:
	.string "נא לחזור מחר.$"

GoldenrodCity_RadioTower_1F_Text_PleaseVisitAgain:
	.string "נשמח לראותך שוב.$"

GoldenrodCity_RadioTower_1F_Text_PleasePickTicket:
	.string "נא לשלוף כרטיס לוטו.\n"
	.string "…{PAUSE 0x0F}{PAUSE 0x0F}{PAUSE 0x0F}{PAUSE 0x0F}…{PAUSE 0x0F}{PAUSE 0x0F}{PAUSE 0x0F}{PAUSE 0x0F}…{PAUSE 0x0F}{PAUSE 0x0F}{PAUSE 0x0F}{PAUSE 0x0F}$"

GoldenrodCity_RadioTower_1F_Text_TicketNumberIsXPleaseWait:
	.string "מספר כרטיס הלוטו: {STR_VAR_1}.\p"
	.string "אבדוק אם המספר תואם למספר המזהה\n"
	.string "של אחד הפוקימונים שלך. רק רגע, בבקשה.$"

GoldenrodCity_RadioTower_1F_Text_TicketMatchesPartyMon:
	.string "מזל טוב!\p"
	.string "המספר המזהה של {STR_VAR_1}\n"
	.string "שבצוות שלך תואם למספר הכרטיס!$"

GoldenrodCity_RadioTower_1F_Text_TicketMatchesPCMon:
	.string "מזל טוב!\p"
	.string "המספר המזהה של {STR_VAR_1}\n"
	.string "שבמחשב שלך תואם למספר הכרטיס!$"

GoldenrodCity_RadioTower_1F_Text_NoNumbersMatched:
	.string "מצטער.\n"
	.string "אף אחד מהמספרים לא תאם.$"

GoldenrodCity_RadioTower_1F_Text_TwoDigitsMatched:
	.string "שתי ספרות תואמות, אז זכית\n"
	.string "בפרס השלישי! זכית ב{STR_VAR_1}!$"

GoldenrodCity_RadioTower_1F_Text_ThreeDigitsMatched:
	.string "שלוש ספרות תואמות, אז זכית\n"
	.string "בפרס השני! זכית ב{STR_VAR_1}!$"

GoldenrodCity_RadioTower_1F_Text_FourDigitsMatched:
	.string "ארבע ספרות תואמות, אז זכית\n"
	.string "בפרס הראשון! זכית ב{STR_VAR_1}!$"

GoldenrodCity_RadioTower_1F_Text_AllFiveDigitsMatched:
	.string "לא ייאמן, כל חמש הספרות\n"
	.string "תואמות!\p"
	.string "זכית בפרס הגדול!\n"
	.string "זכית ב{STR_VAR_1}!$"

GoldenrodCity_RadioTower_1F_Text_NoRoomForThis:
	.string "אה?\n"
	.string "נראה שאין לך מקום לזה.\p"
	.string "נא לפנות מקום בתיק\n"
	.string "ולהודיע לי.$"

GoldenrodCity_RadioTower_1F_Text_PrizeWeveBeenHolding:
	.string "{PLAYER}?\n"
	.string "כן, חיכיתי לך.\p"
	.string "הנה הפרס ששמרנו בשבילך.$"

GoldenrodCity_RadioTower_1F_Text_PleaseVisitAgain2:
	.string "נשמח לראותך שוב.$"


