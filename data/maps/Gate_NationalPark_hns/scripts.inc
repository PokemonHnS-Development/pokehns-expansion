Gate_NationalPark_hns_MapScripts::
	.byte 0

Gate_NationalPark_EventScript_Attendant::
	lockall
	faceplayer
	goto_if_set FLAG_DAILY_BUG_CONTEST_COMPLETED, Gate_NationalPark_EventScript_AttendantAlreadyPlayed
	msgbox Route35NationalParkGate_Text_OfficerAskToParticipate, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE, Gate_NationalPark_EventScript_AttendantStart
	msgbox Route35NationalParkGate_Text_TakePartInFuture, MSGBOX_DEFAULT
	releaseall
	end

Gate_NationalPark_EventScript_AttendantStart::
	playbgm MUS_HG_BUG_CONTEST_PREP, FALSE
	msgbox Route35NationalParkGate_Text_OfficerAskToUseFirstMon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, Gate_NationalPark_EventScript_AttendantCancel
	getpartysize
	call_if_eq VAR_RESULT, 1, Gate_NationalPark_EventScript_OnlyOneMon
	msgbox Route35NationalParkGate_Text_OfficerHoldYourMon, MSGBOX_DEFAULT
	closemessage
	special SavePlayerParty
	remove5mons
	goto_if_eq VAR_RESULT, MON_CANT_GIVE, Gate_NationalPark_EventScript_AttendantFaint
	playfanfare MUS_OBTAIN_ITEM
	message Route35NationalParkGate_Text_MonLeftWithHelper
	waitfanfare
	closemessage
	msgbox Route35NationalParkGate_Text_OfficerGiveSportBalls, MSGBOX_DEFAULT
	closemessage
	giveitem ITEM_SPORT_BALL, 30
	closemessage
	msgbox Route35NationalParkGate_Text_OfficerExplainRules, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_FACING, DIR_WEST, Gate_NationalPark_EventScript_AttendantEnterTop
	call_if_eq VAR_FACING, DIR_NORTH, Gate_NationalPark_EventScript_AttendantEnterBot
	playse SE_EXIT
	clearflag FLAG_HIDE_BUG_CONTEST_ATTENDANT_SIDE
	special EnterBugContestMode
	setflag FLAG_DISABLE_EXP_GAIN
	setvar VAR_BUG_CONTEST_STATE, 1
	warp MAP_NATIONAL_PARK_BUG_CONTEST_HNS, 1
	waitstate
	end

Gate_NationalPark_EventScript_OnlyOneMon::
	special SavePlayerParty
	msgbox Route35NationalParkGate_Text_OfficerGiveSportBalls, MSGBOX_DEFAULT
	closemessage
	giveitem ITEM_SPORT_BALL, 30
	closemessage
	msgbox Route35NationalParkGate_Text_OfficerExplainRules, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_FACING, DIR_WEST, Gate_NationalPark_EventScript_AttendantEnterTop
	call_if_eq VAR_FACING, DIR_NORTH, Gate_NationalPark_EventScript_AttendantEnterBot
	playse SE_EXIT
	clearflag FLAG_HIDE_BUG_CONTEST_ATTENDANT_SIDE
	special EnterBugContestMode
	setflag FLAG_DISABLE_EXP_GAIN
	setvar VAR_BUG_CONTEST_STATE, 1
	warp MAP_NATIONAL_PARK_BUG_CONTEST_HNS, 1
	waitstate
	end

Gate_NationalPark_EventScript_AttendantEnterTop::
	applymovement OBJ_EVENT_ID_PLAYER, Gate_NationalPark_Movement_Player_EnterParkTop
	waitmovement 0
	return

Gate_NationalPark_EventScript_AttendantEnterBot::
	applymovement OBJ_EVENT_ID_PLAYER, Gate_NationalPark_Movement_Player_EnterParkBot
	waitmovement 0
	return


Gate_NationalPark_EventScript_AttendantFaint::	
	msgbox Route35NationalParkGate_Text_FirstMonCantBattle, MSGBOX_DEFAULT
	closemessage
	fadedefaultbgm
	release
	end	

Gate_NationalPark_EventScript_AttendantCancel::	
	msgbox Route35NationalParkGate_Text_TakePartInFuture, MSGBOX_DEFAULT
	closemessage
	fadedefaultbgm
	release
	end

Gate_NationalPark_EventScript_AttendantAlreadyPlayed::
	msgbox Route35NationalParkGate_Text_ContestIsOver, MSGBOX_DEFAULT
	closemessage
	release
	end

Gate_NationalPark_Movement_Player_EnterParkTop:
	walk_down
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	step_end

Gate_NationalPark_Movement_Player_EnterParkBot:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	step_end

Gate_NationalPark_EventScript_BAttendant::
	lockall
	faceplayer
	goto_if_set FLAG_DAILY_BUG_CONTEST_COMPLETED, Gate_NationalPark_EventScript_AttendantAlreadyPlayed
	msgbox Route35NationalParkGate_Text_OfficerAskToParticipate, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE, Gate_NationalPark_EventScript_BAttendantStart
	msgbox Route35NationalParkGate_Text_TakePartInFuture, MSGBOX_DEFAULT
	releaseall
	end

Gate_NationalPark_EventScript_BAttendantStart::
	playbgm MUS_HG_BUG_CONTEST_PREP, FALSE
	msgbox Route35NationalParkGate_Text_OfficerAskToUseFirstMon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, Gate_NationalPark_EventScript_AttendantCancel
	getpartysize
	call_if_eq VAR_RESULT, 1, Gate_NationalPark_EventScript_OnlyOneMonB
	msgbox Route35NationalParkGate_Text_OfficerHoldYourMon, MSGBOX_DEFAULT
	closemessage
	special SavePlayerParty
	remove5mons
	goto_if_eq VAR_RESULT, MON_CANT_GIVE, Gate_NationalPark_EventScript_AttendantFaint
	playfanfare MUS_OBTAIN_ITEM
	message Route35NationalParkGate_Text_MonLeftWithHelper
	waitfanfare
	closemessage
	msgbox Route35NationalParkGate_Text_OfficerGiveSportBalls, MSGBOX_DEFAULT
	closemessage
	giveitem ITEM_SPORT_BALL, 30
	closemessage
	msgbox Route35NationalParkGate_Text_OfficerExplainRules, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_FACING, DIR_EAST, Gate_NationalPark_EventScript_AttendantBEnterTop
	call_if_eq VAR_FACING, DIR_NORTH, Gate_NationalPark_EventScript_AttendantBEnterBot
	playse SE_EXIT
	special EnterBugContestMode
	setflag FLAG_DISABLE_EXP_GAIN
	setflag FLAG_HIDE_BUG_CONTEST_ATTENDANT_SIDE
	setvar VAR_BUG_CONTEST_STATE, 5
	warp MAP_NATIONAL_PARK_BUG_CONTEST_HNS, 40, 19
	waitstate
	end

Gate_NationalPark_EventScript_OnlyOneMonB::
	special SavePlayerParty
	msgbox Route35NationalParkGate_Text_OfficerGiveSportBalls, MSGBOX_DEFAULT
	closemessage
	giveitem ITEM_SPORT_BALL, 30
	closemessage
	msgbox Route35NationalParkGate_Text_OfficerExplainRules, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_FACING, DIR_EAST, Gate_NationalPark_EventScript_AttendantBEnterTop
	call_if_eq VAR_FACING, DIR_NORTH, Gate_NationalPark_EventScript_AttendantBEnterBot
	playse SE_EXIT
	special EnterBugContestMode
	setflag FLAG_DISABLE_EXP_GAIN
	setflag FLAG_HIDE_BUG_CONTEST_ATTENDANT_SIDE
	setvar VAR_BUG_CONTEST_STATE, 5
	warp MAP_NATIONAL_PARK_BUG_CONTEST_HNS, 40, 19
	waitstate
	end

Gate_NationalPark_EventScript_AttendantBEnterTop::
	applymovement OBJ_EVENT_ID_PLAYER, Gate_NationalPark_Movement_Player_EnterParkTopB
	waitmovement 0
	return

Gate_NationalPark_EventScript_AttendantBEnterBot::
	applymovement OBJ_EVENT_ID_PLAYER, Gate_NationalPark_Movement_Player_EnterParkBotB
	waitmovement 0
	return

Gate_NationalPark_Movement_Player_EnterParkTopB:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_in_place_left
	step_end

Gate_NationalPark_Movement_Player_EnterParkBotB:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_in_place_left
	step_end

Route35NationalParkGate_Text_OfficerAskToParticipate:
	.string "שלום, מאמן! היום מתקיימת\n"
	.string "תחרות לכידת החרקים.\p"
	.string "החוקים פשוטים.\p"
	.string "בעזרת אחד מהפוקימונים שלך, צריך\n"
	.string "לתפוס פוקימון חרק לשיפוט.\p"
	.string "רוצה לנסות?$"

Route35NationalParkGate_Text_OfficerGiveSportBalls:
	.string "נקודות הניסיון שהפוקימון שלך יצבור\n"
	.string "במהלך התחרות יבוטלו כשתצא.\p"
	.string "הנה כדורי התחרות שלך.$"

Route35NationalParkGate_Text_ReceivedSportBalls:
	.string "{PLAYER} received SPORT BALLS.$"

Route35NationalParkGate_Text_OfficerExplainRules:
	.string "מי שתופס את פוקימון החרק החזק\n"
	.string "ביותר הוא המנצח.\p"
	.string "כשנגמרים לך כדורי התחרות,\n"
	.string "סיימת.\p"
	.string "אפשר לתפוס עד 5 פוקימונים. רק\n"
	.string "האחרון שנתפס יישאר וישתתף בתחרות.\p"
	.string "צא ותפוס את פוקימון החרק החזק\n"
	.string "ביותר שתמצא!$"

Route35NationalParkGate_Text_OfficerAskToUseFirstMon:
	.string "אם יש לך כמה פוקימונים, תצטרך\n"
	.string "להשתמש בראשון שבקבוצה שלך.\p"
	.string "זה בסדר מבחינתך?$"

Route35NationalParkGate_Text_OfficerHoldYourMon:
	.string "בסדר, נשמור את שאר הפוקימונים\n"
	.string "שלך בזמן התחרות.$"

Route35NationalParkGate_Text_MonLeftWithHelper:
	.string "הפוקימונים של {PLAYER} הופקדו\n"
	.string "אצל עוזר התחרות.$"

Route35NationalParkGate_Text_ChooseMonAndComeBack:
	.string "Please choose the POKéMON to be used\n"
	.string "in the Contest, then come see me.$"

Route35NationalParkGate_Text_TakePartInFuture:
	.string "בסדר. אנחנו מקווים שתשתתף בעתיד.$"

Route35NationalParkGate_Text_FirstMonCantBattle:
	.string "אוי… הפוקימון הראשון בקבוצה\n"
	.string "שלך לא יכול להילחם.\p"
	.string "בבקשה החלף אותו בפוקימון שבו\n"
	.string "תרצה להשתמש, ואז בוא אליי.$"

Route35NationalParkGate_Text_MakeRoom:
	.string "Uh-oh… Both your party and your\n"
	.string "PC BOX are full.\p"
	.string "You have no room to put the bug\n"
	.string "POKéMON you catch.\p"
	.string "Please make room in your party or\n"
	.string "your PC BOX, then come see me.$"

Route35NationalParkGate_Text_EggAsFirstMon:
	.string "Uh-oh… You have an EGG as the first\n"
	.string "POKéMON in your party.\p"
	.string "Please switch it with the POKéMON\n"
	.string "you want to use, then come see me.$"

Route35NationalParkGate_Text_ContestIsOver:
	.string "התחרות של היום הסתיימה. אנחנו\n"
	.string "מקווים שתשתתף בעתיד.$"

Route35NationalParkGate_EventScript_Policeman::
	lock
	faceplayer
	msgbox Route35NationalParkGate_Text_WeHoldContests, MSGBOX_DEFAULT
	closemessage
	release
	end

Route35NationalParkGate_EventScript_BC1::
	lock
	faceplayer
	msgbox Route35NationalParkGate_Text_YoungsterWonders, MSGBOX_DEFAULT
	closemessage
	release
	end

Route35NationalParkGate_EventScript_BC2::
	lock
	faceplayer
	msgbox Route35NationalParkGate_Text_BC2, MSGBOX_DEFAULT
	closemessage
	release
	end

Route35NationalParkGate_EventScript_Rocker::
	lock
	faceplayer
	msgbox Route35NationalParkGate_Text_Rocker, MSGBOX_DEFAULT
	closemessage
	release
	end

Route35NationalParkGate_EventScript_Beauty::
	lock
	faceplayer
	msgbox Route35NationalParkGate_Text_Beauty, MSGBOX_DEFAULT
	closemessage
	release
	end

Route35NationalParkGate_Text_Rocker:
	.string "אני אוהב פוקימוני ציפור! אתמול\n"
	.string "בלילה מצאתי בפארק ציפור מסוג אפל!$"

Route35NationalParkGate_Text_BC2:
	.string "תפסתי סייטר ענקי!$"

Route35NationalParkGate_Text_Beauty:
	.string "הוא תמיד מנצח בתחרויות האלה!$"

Route35NationalParkGate_Text_WeHoldContests:
	.string "אנחנו עורכים תחרויות בפארק\n"
	.string "באופן קבוע. כדאי לך לנסות.$"

Route35NationalParkGate_Text_YoungsterWonders:
	.string "מתי תהיה תחרות לכידת החרקים הבאה?$"

Route35NationalParkGate_Text_ContestExplanation:
	.string "The Bug-Catching Contest is held on\n"
	.string "Tuesday, Thursday and Saturday.\p"
	.string "Not only do you earn a prize just\n"
	.string "for participating,\p"
	.string "you also get to keep the bug POKéMON\n"
	.string "you may have at the end of the contest.$"
