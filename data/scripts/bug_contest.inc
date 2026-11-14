BugContest_EventScript_Start::
	end

BugContest_EventScript_WhiteOut::
	lockall
	delay 200
	msgbox BugContest_Text_WhiteOut, MSGBOX_DEFAULT
	closemessage
	goto BugContest_EventScript_End
	end

BugContest_EventScript_TimesUp::
	lockall
	playse SE_DING_DONG
	msgbox BugContest_Text_TimesUp, MSGBOX_DEFAULT
	closemessage
	waitse
	getpartysize
	goto_if_eq VAR_RESULT, 1, BugContest_EventScript_Didntcatch
	fadescreen FADE_TO_BLACK
	setvar VAR_BUG_CONTEST_STATE, 3

	msgbox BugContest_Text_Judging0, MSGBOX_DEFAULT
	closemessage
	BugContest_EventScript_TimesUp2::
	special ChoosePartyMon
	waitstate
	copyvar VAR_0x800A, VAR_0x8004
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, BugContest_EventScript_WrongChoiceMon
	goto_if_eq VAR_0x8004, 0, BugContest_EventScript_WrongChoiceMon
	fadescreen FADE_TO_BLACK
	warp MAP_NATIONAL_PARK_BUG_CONTEST_HNS, 5
	waitstate
	delay 90
	end

BugContest_EventScript_WrongChoiceMon::
	msgbox BugContest_Text_WrongChoiceMon, MSGBOX_DEFAULT
	goto BugContest_EventScript_TimesUp2
	end

BugContestEventScript_Judging::
	msgbox BugContest_Text_Judging1, MSGBOX_DEFAULT
	closemessage
	special JudgeBugContestMon
	call_if_eq VAR_RESULT, 1, BugContest_EventScript_First
	call_if_eq VAR_RESULT, 2, BugContest_EventScript_Second
	call_if_eq VAR_RESULT, 3, BugContest_EventScript_Third
	special TransferBugContestMon
	delay 20
	giveitem VAR_0x8005
	msgbox BugContest_Text_TransferAndReturn, MSGBOX_DEFAULT
	playse SE_SUCCESS
	waitse
	msgbox BugContest_Text_TakePartInFuture, MSGBOX_DEFAULT
	closemessage
	goto BugContest_EventScript_End
	end

BugContest_EventScript_Didntcatch::
	msgbox BugContest_Text_DidntCatch, MSGBOX_DEFAULT
	playse SE_SUCCESS
	closemessage
	fadescreen FADE_TO_BLACK
	goto BugContest_EventScript_End
	end

BugContest_EventScript_First::
	msgbox BugContest_Text_First1, MSGBOX_DEFAULT
	playfanfare MUS_HG_BUG_CONTEST_3RD_PLACE
	waitfanfare
	msgbox BugContest_Text_First2, MSGBOX_DEFAULT
	playfanfare MUS_HG_BUG_CONTEST_2ND_PLACE
	waitfanfare
	msgbox BugContest_Text_First3, MSGBOX_DEFAULT
	playfanfare MUS_HG_BUG_CONTEST_1ST_PLACE
	waitfanfare
	closemessage
	return

BugContest_EventScript_Second::
	msgbox BugContest_Text_Second1, MSGBOX_DEFAULT
	playfanfare MUS_HG_BUG_CONTEST_3RD_PLACE
	waitfanfare
	msgbox BugContest_Text_Second2, MSGBOX_DEFAULT
	playfanfare MUS_HG_BUG_CONTEST_2ND_PLACE
	waitfanfare
	msgbox BugContest_Text_Second3, MSGBOX_DEFAULT
	playfanfare MUS_HG_BUG_CONTEST_1ST_PLACE
	waitfanfare
	closemessage
	return

BugContest_EventScript_Third::
	msgbox BugContest_Text_Third1, MSGBOX_DEFAULT
	playfanfare MUS_HG_BUG_CONTEST_3RD_PLACE
	waitfanfare
	msgbox BugContest_Text_Third2, MSGBOX_DEFAULT
	playfanfare MUS_HG_BUG_CONTEST_2ND_PLACE
	waitfanfare
	msgbox BugContest_Text_Third3, MSGBOX_DEFAULT
	playfanfare MUS_HG_BUG_CONTEST_1ST_PLACE
	waitfanfare
	closemessage
	return

BugContest_EventScript_End::
	special HealPlayerParty
	special LoadPlayerParty
	special ExitBugContestMode
	clearflag FLAG_DISABLE_EXP_GAIN
	setvar VAR_BUG_CONTEST_STATE, 0
	special RemoveSportBalls
	goto_if_eq VAR_TEMP_1, 1, BugContest_EventScript_SideEnd
	warp MAP_GATE_NATIONAL_PARK_HNS, 7, 2
	waitstate
	releaseall
	end

BugContest_EventScript_SideEnd::
	warp MAP_GATE_NATIONAL_PARK_HNS, 35, 7
	waitstate
	releaseall
	end

BugContest_Text_Judging0::
	.string "התחרות הסתיימה. נא לבחור את הפוקימון\n"
	.string "שברצונך לשמור ולהגיש לשיפוט.$"

BugContest_Text_Judging1::
	.string "עכשיו נשפוט את הפוקימונים\n"
	.string "שתפסתם.\p"
	.string "………………………\n"
	.string "………………………\p"
	.string "בחרנו את הזוכים!\n"
	.string "אתם מוכנים?$"

BugContest_Text_WrongChoiceMon:
	.string "נא לבחור את הפוקימון שברצונך\n"
	.string "לשמור ולהגיש לשיפוט.$"

BugContest_Text_DidntCatch:
	.string "אוי לא! לא תפסת אף פוקימון.\n"
	.string "הודחת מהתחרות.\p"
	.string "הפוקימונים שלך יוחזרו אליך עכשיו.$"

BugContest_Text_TimesUp:
	.string "דינג-דונג! הזמן נגמר!$"

BugContest_Text_WhiteOut:
	.string "{PLAYER} נשאר בלי פוקימונים כשירים.\n"
	.string "{PLAYER} הודח מהתחרות.$"

BugContest_Text_First1:
	.string "במקום השלישי: מאמנת-העל בלינדה,\n"
	.string "שתפסה בטרפרי מפרפר!$"
BugContest_Text_First2:
	.string "במקום השני: לוכד החרקים שון,\n"
	.string "שתפס פינסיר מתפתל!$"
BugContest_Text_First3:
	.string "הזוכה בתחרות לכידת החרקים\n"
	.string "הוא…\p"
	.string "{PLAYER}, שתפס\n"
	.string "{STR_VAR_1} ענק!$"

BugContest_Text_Second1:
	.string "במקום השלישי: מאמנת-העל בלינדה,\n"
	.string "שתפסה בטרפרי מפרפר!$"
BugContest_Text_Second2:
	.string "במקום השני: {PLAYER},\n"
	.string "שתפס {STR_VAR_1} מתפתל!$"
BugContest_Text_Second3:
	.string "הזוכה בתחרות לכידת החרקים\n"
	.string "הוא…\p"
	.string "לוכד החרקים שון, שתפס\n"
	.string "פינסיר ענק!$"

BugContest_Text_Third1:
	.string "במקום השלישי: {PLAYER},\n"
	.string "שתפס {STR_VAR_1} מפרפר!$"
BugContest_Text_Third2:
	.string "במקום השני: מאמנת-העל בלינדה,\n"
	.string "שתפסה בטרפרי מתפתל!$"
BugContest_Text_Third3:
	.string "הזוכה בתחרות לכידת החרקים\n"
	.string "הוא…\p"
	.string "לוכד החרקים שון, שתפס\n"
	.string "פינסיר ענק!$"

BugContest_Text_TakePartInFuture:
	.string "תודה על ההשתתפות!\n"
	.string "נשמח לראות אותך בתחרויות הבאות.$"

BugContest_Text_TransferAndReturn:
	.string "פוקימון החרק שבחרת יישלח למחשב,\n"
	.string "והפוקימונים שלך יוחזרו אליך.$"
