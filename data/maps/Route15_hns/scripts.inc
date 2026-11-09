Route15_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route15_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route15_OnTransition:
	callnative SetTimeBasedEncounters
	end

Route15_EventScript_Colette::
	trainerbattle_single TRAINER_COLETTE_HNS, Route15_Text_TeacherColetteSeen, Route15_Text_TeacherColetteBeaten
	msgbox Route15_Text_TeacherColetteAfterBattle, MSGBOX_AUTOCLOSE
	end

Route15_EventScript_Hillary::
	trainerbattle_single TRAINER_HILLARY_HNS, Route15_Text_TeacherHillarySeen, Route15_Text_TeacherHillaryBeaten, Route15_EventScript_RegisterHillary
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route15_EventScript_RematchHillary
	msgbox Route15_Text_TeacherHillaryAfterBattle, MSGBOX_AUTOCLOSE
	end

Route15_EventScript_RegisterHillary::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route15_Text_HillaryRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_HILLARY_HNS
	release
	end

Route15_EventScript_RematchHillary::
	trainerbattle_rematch TRAINER_HILLARY_HNS, Route15_Text_HillaryRematchIntro, Route15_Text_HillaryRematchDefeat
	msgbox Route15_Text_HillaryPostRematch, MSGBOX_AUTOCLOSE
	goto_if_defeated TRAINER_HILLARY_2_HNS, Route15_EventScript_RematchHillaryTryGiveItem
	end

Route15_EventScript_RematchHillaryTryGiveItem::
	checkitem ITEM_TM_ENERGY_BALL
	goto_if_eq VAR_RESULT, TRUE, Common_EventScript_NoOp
	giveitem ITEM_TM_ENERGY_BALL
	closemessage
	end

Route15_EventScript_Kipp::
	trainerbattle_single TRAINER_KIPP_HNS, Route15_Text_SchoolboyKippSeen, Route15_Text_SchoolboyKippBeaten
	msgbox Route15_Text_SchoolboyKippAfterBattle, MSGBOX_AUTOCLOSE
	end

Route15_EventScript_Tommy::
	trainerbattle_single TRAINER_TOMMY_HNS, Route15_Text_SchoolboyTommySeen, Route15_Text_SchoolboyTommyBeaten
	msgbox Route15_Text_SchoolboyTommyAfterBattle, MSGBOX_AUTOCLOSE
	end

Route15_EventScript_Johnny::
	trainerbattle_single TRAINER_JOHNNY_HNS, Route15_Text_SchoolboyJohnnySeen, Route15_Text_SchoolboyJohnnyBeaten
	msgbox Route15_Text_SchoolboyJohnnyAfterBattle, MSGBOX_AUTOCLOSE
	end

Route15_EventScript_Billy::
	trainerbattle_single TRAINER_BILLY_HNS, Route15_Text_SchoolboyBillySeen, Route15_Text_SchoolboyBillyBeaten, Route15_EventScript_RegisterBilly
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route15_EventScript_RematchBilly
	msgbox Route15_Text_SchoolboyBillyAfterBattle, MSGBOX_AUTOCLOSE
	end

Route15_EventScript_RegisterBilly::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route15_Text_BillyRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_BILLY_HNS
	release
	end

Route15_EventScript_RematchBilly::
	trainerbattle_rematch TRAINER_BILLY_HNS, Route15_Text_BillyRematchIntro, Route15_Text_BillyRematchDefeat
	msgbox Route15_Text_BillyPostRematch, MSGBOX_AUTOCLOSE
	goto_if_defeated TRAINER_BILLY_2_HNS, Route15_EventScript_RematchBillyTryGiveItem
	end

Route15_EventScript_RematchBillyTryGiveItem::
	checkitem ITEM_TM_FACADE
	goto_if_eq VAR_RESULT, TRUE, Common_EventScript_NoOp
	giveitem ITEM_TM_FACADE
	closemessage
	end

Route15_EventScript_Sign::
	msgbox Route15_Text_Sign, MSGBOX_SIGN
	end

Route15_EventScript_PPup::
	finditem ITEM_PP_UP
	end

Route15_Text_TeacherColetteSeen:
	.string "שכחת משהו?$"

Route15_Text_TeacherColetteBeaten:
	.string "אאאאה!$"

Route15_Text_TeacherColetteAfterBattle:
	.string "לפני שהפכתי למורה,\n"
	.string "הייתי שוכחת המון דברים.$"

Route15_Text_TeacherHillarySeen:
	.string "בימים שמשיים, נראה לי שהילדים מעדיפים\n"
	.string "לשחק בחצר בית הספר ולא ללמוד בכיתה.$"

Route15_Text_TeacherHillaryBeaten:
	.string "לא רציתי להפסיד…$"

Route15_Text_TeacherHillaryAfterBattle:
	.string "ללמוד זה חשוב,\n"
	.string "אבל פעילות גופנית חיונית לא פחות.$"

Route15_Text_HillaryRegister:
	.string "לימדת אותי לקח!\n"
	.string "אפשר לקבל את המספר שלך?$"

Route15_Text_HillaryRematchIntro:
	.string "הפעם אני אלמד אותך שיעור!$"

Route15_Text_HillaryRematchDefeat:
	.string "חוזרים לנקודת ההתחלה…$"

Route15_Text_HillaryPostRematch:
	.string "ללמד פוקימונים זה בדיוק כמו\n"
	.string "ללמד ילדים. סבלנות!$"

Route15_Text_SchoolboyKippSeen:
	.string "רגע. אני צריך להתקשר לאמא שלי.$"

Route15_Text_SchoolboyKippBeaten:
	.string "סליחה, אמא! הפסדתי!$"

Route15_Text_SchoolboyKippAfterBattle:
	.string "אמא שלי כל כך דואגת לי,\n"
	.string "שאני צריך להתקשר אליה כל הזמן.$"

Route15_Text_SchoolboyTommySeen:
	.string "בוא נילחם. אני לא אפסיד!$"

Route15_Text_SchoolboyTommyBeaten:
	.string "שכחתי להכין שיעורי בית!$"

Route15_Text_SchoolboyTommyAfterBattle:
	.string "סאיונרה! הרגע למדתי את זה\n"
	.string "בשיעור יפנית.$"

Route15_Text_SchoolboyJohnnySeen:
	.string "אנחנו בסיור למגדל הרדיו של לבנדר\n"
	.string "במסגרת לימודי החברה.$"

Route15_Text_SchoolboyJohnnyBeaten:
	.string "יש לך כוח מטורף!$"

Route15_Text_SchoolboyJohnnyAfterBattle:
	.string "נמאס לי ללכת. אני חייב\n"
	.string "לעשות הפסקה.$"

Route15_Text_SchoolboyBillySeen:
	.string "השיעור האהוב עליי הוא התעמלות!$"

Route15_Text_SchoolboyBillyBeaten:
	.string "אוי, לא! איך הפסדתי?$"

Route15_Text_SchoolboyBillyAfterBattle:
	.string "אם פוקימונים היו מקצוע\n"
	.string "בבית הספר, הייתי הכי טוב!$"

Route15_Text_BillyRegister:
	.string "הייתי צריך להקשיב יותר בשיעור.\n"
	.string "אפשר לקבל את המספר שלך?$"

Route15_Text_BillyRematchIntro:
	.string "ישבתי על הספרים בלי הפסקה!\n"
	.string "עכשיו אראה לך מה למדתי!$"

Route15_Text_BillyRematchDefeat:
	.string "אני צריך ללמוד עוד…$"

Route15_Text_BillyPostRematch:
	.string "ידע מהספרים זה לא הכול.\n"
	.string "אני צריך גם ניסיון בקרבות!$"

Route15_Text_Sign:
	.string "דרך 15\p"
	.string "העיר פושיה - העיירה לבנדר$"

