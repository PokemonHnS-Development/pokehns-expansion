Route29_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route29_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route29_OnTransition: 
	callnative SetTimeBasedEncounters
	end

Route29_Trigger_Monview::
	special SpawnCameraObject
	applymovement2 OBJ_EVENT_ID_CAMERA, Common_Movement_WalkUp1 
	waitmovement 0
	applymovement2 OBJ_EVENT_ID_CAMERA, Common_Movement_WalkUp1
	waitmovement 0
	applymovement2 OBJ_EVENT_ID_CAMERA, Common_Movement_WalkUp1
	waitmovement 0
	applymovement2 OBJ_EVENT_ID_CAMERA, Common_Movement_WalkUp1
	waitmovement 0
	message Route29_Text_PressAorB
	waitbuttonpress
	closemessage
	applymovement2 OBJ_EVENT_ID_CAMERA, Common_Movement_WalkDown1
	waitmovement 0
	applymovement2 OBJ_EVENT_ID_CAMERA, Common_Movement_WalkDown1
	waitmovement 0
	applymovement2 OBJ_EVENT_ID_CAMERA, Common_Movement_WalkDown1
	waitmovement 0
	applymovement2 OBJ_EVENT_ID_CAMERA, Common_Movement_WalkDown1
	waitmovement 0
	special RemoveCameraObject
	applymovement2 OBJ_EVENT_ID_PLAYER, Common_Movement_WalkDown1
	waitmovement 0
	end

Route29_Text_PressAorB:
	.string "לחיצה על A או B תפסיק את הצפייה.$"

Route29_EventScript_OldMan::
	lock
	faceplayer
	goto_if_set FLAG_ADVENTURE_STARTED, Route29_EventScript_OldMan2
	msgbox Route29_Text_OldMan1, MSGBOX_DEFAULT
	closemessage
	release
	end

Route29_EventScript_OldMan2::
	msgbox Route29_Text_OldMan2, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route29_EventScript_OldMan_Tutorial
	waitmessage
	msgbox Route29_Text_OldManDeclined, MSGBOX_DEFAULT
	closemessage
	release
	end

Route29_EventScript_OldMan_Tutorial::
	msgbox Route29_Text_OldManExplanation, MSGBOX_DEFAULT
	closemessage
	release
	end

Route29_EventScript_Lass::
	lock
	faceplayer
	msgbox Route29_Text_Lass, MSGBOX_DEFAULT
	closemessage
	release
	end

Route29_EventScript_Youngster::
	lock
	faceplayer
	msgbox Route29_Text_Youngster, MSGBOX_DEFAULT
	closemessage
	release
	end


Route29_EventScript_Tuscany::
	lock
	faceplayer
	goto_if_set FLAG_GOT_SILK_SCARF, Route29_EventScript_TuscanyCompleted
	msgbox Route29_Text_MeetTuscany, MSGBOX_DEFAULT
	closemessage
	multichoice 20, 0, MULTI_DAYS_OF_WEEK, FALSE
	switch VAR_RESULT
	case 0, Route29_EventScript_TuscanyNope
	case 1, Route29_EventScript_TuscanyNope
	case 2, Route29_EventScript_TuscanyYes
	case 3, Route29_EventScript_TuscanyNope
	case 4, Route29_EventScript_TuscanyNope
	case 5, Route29_EventScript_TuscanyNope
	case 6, Route29_EventScript_TuscanyNope
	case 7 Route29_EventScript_TuscanyCancel
	case MULTI_B_PRESSED, Route29_EventScript_TuscanyCancel
	closemessage
	release
	end
Route29_EventScript_TuscanyYes::
	msgbox Route29_Text_TuscanyGivesGift, MSGBOX_DEFAULT
	giveitem ITEM_SILK_SCARF
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_GOT_SILK_SCARF
	msgbox Route29_Text_TuscanyGaveGift, MSGBOX_DEFAULT
	closemessage
	release
	end
Route29_EventScript_TuscanyNope::
	msgbox Route29_Text_TuscanyNope, MSGBOX_DEFAULT
	closemessage
	release
	end
Route29_EventScript_TuscanyCancel::
	closemessage
	release
	end
Route29_EventScript_TuscanyCompleted::
	msgbox Route29_Text_TuscanyTuesday, MSGBOX_DEFAULT
	closemessage
	release
	end



Route29_EventScript_Girl::
	lock
	faceplayer
	msgbox Route29_Text_Girl, MSGBOX_DEFAULT
	closemessage
	release
	end

Route29_EventScript_Boy::
	lock
	faceplayer
	goto_if_set FLAG_NIGHT_POKEMON, Route29_EventScript_Boy2
	msgbox Route29_Text_Boy_WaitingForDay, MSGBOX_DEFAULT
	closemessage
	release
	end

Route29_EventScript_Boy2::
	msgbox Route29_Text_Boy_WaitingForNight, MSGBOX_DEFAULT
	closemessage
	release
	end

Route29_EventScript_Sign::
	lock
	msgbox Route29_Text_Sign1, MSGBOX_SIGN
	closemessage
	release
	end

Route29_EventScript_ItemPotion::
	finditem ITEM_POTION
	end

Route29_Text_OldMan1:
	.string "פוקימונים מתחבאים בדשא.\n"
	.string "מי יודע מתי הם יקפצו החוצה…$"

Route29_Text_OldMan2:
	.string "ראיתי אותך כאן כמה פעמים.\n"
	.string "כמה פוקימונים כבר תפסת?\p"
	.string "תרצה שאסביר לך\n"
	.string "איך תופסים פוקימונים?$"

Route29_Text_OldManExplanation:
	.string "קל יותר לתפוס פוקימונים\n"
	.string "אם מחלישים אותם קודם.\p"
	.string "אחר כך זורקים עליהם כדור מהתיק!\n"
	.string "כל כדור יתאים.\p"
	.string "אם רוצים ללמוד עוד,\n"
	.string "כדאי ללכת לאקדמיה בעיר ויולט!\p"
	.string "התלמידים שם יודעים הרבה\n"
	.string "על פוקימונים.$"

Route29_Text_OldManDeclined:
	.string "אה. טוב, בסדר.\p"
	.string "כדאי לחפש בכל דרך כדי למצוא\n"
	.string "מגוון פוקימונים.\p"
	.string "הפוקדקס שלך גם מראה איפה\n"
	.string "אפשר למצוא אותם!\p"
	.string "אם רוצים ללמוד עוד,\n"
	.string "כדאי ללכת לאקדמיה בעיר ויולט!\p"
	.string "התלמידים יודעים\n"
	.string "הרבה על פוקימונים.$"

Route29_Text_Youngster:
	.string "יו. מה שלום הפוקימונים שלך?\p"
	.string "אם הם חלשים ולא מוכנים\n"
	.string "לקרב, עדיף להתרחק מהדשא.$"

Route29_Text_Lass:
	.string "רואה את מדרגות הסלע?\n"
	.string "מפחיד לקפוץ מהן.\p"
	.string "אבל ככה אפשר להגיע לניו בארק\n"
	.string "בלי ללכת דרך הדשא.$"

Route29_Text_Girl:
	.string "רציתי לעשות הפסקה,\n"
	.string "אז שמרתי את ההתקדמות שלי.$"

Route29_Text_Boy_WaitingForDay:
	.string "אני מחכה לפוקימונים שמופיעים\n"
	.string "רק מאוחר יותר ביום.$"

Route29_Text_Boy_WaitingForNight:
	.string "אני מחכה לפוקימונים\n"
	.string "שמופיעים רק בלילה.$"

Route29_Text_MeetTuscany:
	.string "טוסקני: נדמה לי שזו\n"
	.string "הפעם הראשונה שאנחנו נפגשים?\p"
	.string "שמי טוסקני, ממשפחת ימי השבוע.\p"
	.string "אם תנחש מה היום האהוב עליי,\n"
	.string "אתן לך פרס.$"

Route29_Text_TuscanyNope:
	.string "לא בדיוק!$"

Route29_Text_TuscanyGivesGift:
	.string "כן! לכבוד היכרותנו, אנא קבל\n"
	.string "את המתנה הזאת: צעיף משי.$"

Route29_Text_TuscanyGaveGift:
	.string "טוסקני: האם לא תסכים\n"
	.string "שהוא מקסים ביותר?\p"
	.string "הוא מחזק מהלכים\n"
	.string "מסוג רגיל.\p"
	.string "אין לי ספק שהוא יועיל לך.$"

Route29_Text_TuscanyTuesday:
	.string "טוסקני: פגשת את מוניקה,\n"
	.string "אחותי הגדולה?\p"
	.string "או את אחי הקטן, ווסלי?\p"
	.string "במשפחה שלנו שבעה ילדים,\n"
	.string "ואני מספר שלוש.$"

Route29_Text_Sign1:
	.string "דרך 29\p"
	.string "העיר צ'ריגרוב - העיירה ניו בארק$"

