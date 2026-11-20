CeladonCity_DepartmentStore_5F_hns_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, CeladonDeptElevator_OnFrame
	.byte 0

CeladonDeptStore5_EventScript_Receptionist::
	lock
	faceplayer
	goto_if_set FLAG_GOT_FRUSTRATION, CeladonDeptStore5_EventScript_Receptionist_Already
	msgbox CeladonDeptStore_Text_5FReceptionistOhYourMon, MSGBOX_DEFAULT
	closemessage
	specialvar VAR_RESULT, GetLeadMonFriendshipScore
	goto_if_lt VAR_RESULT, FRIENDSHIP_50_TO_99, CeladonDeptStore5_EventScript_Receptionist_GiveFrustration
	msgbox CeladonDeptStore_Text_5FReceptionistPutInSomeMoreEffort, MSGBOX_DEFAULT
	closemessage
	release
	end

CeladonDeptStore5_EventScript_Receptionist_GiveFrustration::
	giveitem ITEM_TM_FRUSTRATION
	setflag FLAG_GOT_FRUSTRATION
	msgbox CeladonDeptStore_Text_5FReceptionistItLooksEvilHowAboutThisTM, MSGBOX_DEFAULT
	closemessage
	release
	end

CeladonDeptStore5_EventScript_Receptionist_Already::
	msgbox CeladonDeptStore_Text_5FReceptionistWait, MSGBOX_DEFAULT
	closemessage
	release
	end

CeladonDeptStore_Text_5FReceptionistOhYourMon:
    .string "שלום. הו, הפוקימון שלך…$"

CeladonDeptStore_Text_5FReceptionistWait:
    .string "רגע, כבר נתתי לך את המ”מ הזה!$"

CeladonDeptStore_Text_5FReceptionistPutInSomeMoreEffort:
	.string "הממ…\n"
	.string "זה לא רע, אבל זה גם לא טוב.\p"
	.string "אתה, בתור המאמן, צריך להשקיע\n"
	.string "קצת יותר מאמץ.$"

CeladonDeptStore_Text_5FReceptionistItLooksEvilHowAboutThisTM:
    .string "הוא נראה מרושע. מה דעתך על\n"
    .string "המ”מ הזה בשבילו?$"

CeladonDept5_EventScript_Gent::
	msgbox CeladonDeptStore5F_Text_Gentleman, MSGBOX_NPC
	end
CeladonDept5_EventScript_Sailor::
	msgbox CeladonDeptStore5F_Text_Sailor, MSGBOX_NPC
	end
CeladonDept5_EventScript_Teacher::
	msgbox CeladonDeptStore5F_Text_Teacher, MSGBOX_NPC
	end
CeladonDept5_EventScript_Directory::
	msgbox CeladonDeptStore5F_Text_Directory, MSGBOX_SIGN
	end

CeladonDeptStore5_EventScript_Falkner::
	lock
	faceplayer
	msgbox CeladonDeptStore5_Text_Falkner, MSGBOX_DEFAULT
	closemessage
	fadescreenswapbuffers FADE_TO_BLACK
	setflag FLAG_HIDE_CELADON_FALKNER
	removeobject LOCALID_CELADON_FALKNER
	fadescreenswapbuffers FADE_FROM_BLACK
	clearflag FLAG_HIDE_DOJO_FALKNER
	release
	end

CeladonDeptStore5_Text_Falkner:
	.string "{PLAYER}. לא ציפיתי לראות\n"
	.string "אותך כאן.\p"
	.string "אני קונה ציוד\n"
	.string "לפוקימוני הציפורים שלי.\p"
	.string "אם תרצה להתמודד איתי שוב, אהיה\n"
	.string "בדוג'ו שבעיר סאפרון.$"

CeladonDeptStore5F_Text_Gentleman:
	.string "אני רוצה לקנות פריטים שמעלים\n"
	.string "את הנתונים של פוקימונים,\p"
	.string "אבל אין לי מספיק כסף…$"

CeladonDeptStore5F_Text_Sailor:
	.string "אני רוצה הגדלת נ”כ, כדי להעלות\n"
	.string "את הנ”כ של מהלכים.\p"
	.string "אבל אי אפשר לקנות אותה…$"

CeladonDeptStore5F_Text_Teacher:
	.string "פוקימונים שמחים כשמשתמשים\n"
	.string "עליהם בפריטים.\p"
	.string "אבל יש פריטים שהם שונאים…$"

CeladonDeptStore5F_Text_Directory:
	.string "ק5: בית מרקחת$"
