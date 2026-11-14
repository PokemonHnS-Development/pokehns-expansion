Route31_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route31_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route31_OnTransition: 
	callnative SetTimeBasedEncounters
	end

Route31_EventScript_Bugcatcher_Wade::
	trainerbattle_single TRAINER_WADE_HNS, Route31_Text_BugCatcherWade1_Seen, Route31_Text_BugCatcherWade1_Beaten, Route31_EventScript_RegisterWade
	goto_if_set FLAG_WADE_HAS_ITEM_HNS, Route31_EventScript_WadeGiveItem
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route31_EventScript_RematchWade
	msgbox Route31_Text_BugCatcherWade1_After, MSGBOX_AUTOCLOSE
	end

Route31_EventScript_RegisterWade::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route31_Text_WadeRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_WADE_HNS
	release
	end

Route31_EventScript_RematchWade::
	trainerbattle_rematch TRAINER_WADE_HNS, Route31_Text_WadeRematchIntro, Route31_Text_WadeRematchDefeat
	msgbox Route31_Text_WadePostRematch, MSGBOX_AUTOCLOSE
	end

Route31_EventScript_WadeGiveItem::
	msgbox Route31_Text_WadeHasItem, MSGBOX_DEFAULT
	giveitem VAR_WADE_ITEM_HNS
	goto_if_eq VAR_RESULT, FALSE, Route31_EventScript_WadeNoRoom
	clearflag FLAG_WADE_HAS_ITEM_HNS
	msgbox Route31_Text_WadeGaveItem, MSGBOX_AUTOCLOSE
	end

Route31_EventScript_WadeNoRoom::
	msgbox Route31_Text_WadeNoRoom, MSGBOX_AUTOCLOSE
	end

Route31_EventScript_Youngster::
	lock
	faceplayer
	msgbox Route31_Text_CooltrainerM, MSGBOX_DEFAULT
	closemessage
	release
	end

Route31_EventScript_SleepyMan::
	lock
	faceplayer
	goto_if_eq VAR_KENYA, 1, Route31_EventScript_SleepyMan_AskForKenya
	msgbox Route31_Text_SleepyMan, MSGBOX_DEFAULT
	closemessage
	release
	end

Route31_EventScript_SleepyMan_AskForKenya::
	msgbox Route31_Text_SleepyManGotMail, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE, Route31_EventScript_SleepyMan_GiveKenya
	msgbox Route31_Text_SleepyManFail, MSGBOX_DEFAULT
	closemessage
	release
	end

Route31_EventScript_SleepyMan_GiveKenya::
	removenamedmon 1
	goto_if_eq VAR_RESULT, MON_CANT_GIVE, Route31_EventScript_SleepyMan_Fail
	msgbox Route31_Text_HandOverMailMon, MSGBOX_DEFAULT
	delay 55
	callnative UpdateFollowingPokemon
	msgbox Route31_Text_ReadingMail, MSGBOX_DEFAULT
	giveitem ITEM_TM_REST
	msgbox Route31_Text_DescribeRest, MSGBOX_DEFAULT
	closemessage
	setvar VAR_KENYA, 2
	release
	end

Route31_EventScript_SleepyMan_Fail::
	msgbox Route31_Text_SleepyManFail, MSGBOX_DEFAULT
	release
	end


Route31_EventScript_Boy::
	lock
	faceplayer
	msgbox Route31_Text_Youngster, MSGBOX_DEFAULT
	closemessage
	release
	end

Route31_EventScript_DarkCaveSign::
	lock
	msgbox Route31_Text_DarkCaveSign, MSGBOX_SIGN
	closemessage
	release
	end

Route31_EventScript_Sign::
	lock
	msgbox Route31_Text_Sign, MSGBOX_SIGN
	closemessage
	release
	end

Route31_EventScript_ItemPokeBall::
	finditem ITEM_POKE_BALL
	end

Route31_EventScript_ItemAntidote::
	finditem ITEM_ANTIDOTE
	end

Route31_Text_CooltrainerM:
	.string "המערה החשוכה…\p"
	.string "אם פוקימון היה יכול להאיר\n"
	.string "אותה, הייתי חוקר אותה.$"

Route31_Text_BugCatcherWade1_Seen:
	.string "תפסתי המון פוקימונים.\n"
	.string "בוא נילחם!$"

Route31_Text_BugCatcherWade1_Beaten:
	.string "אוףףף…$"

Route31_Text_BugCatcherWade1_After:
	.string "אפשר לתפוס פוקימונים גם\n"
	.string "כשיש איתך כבר שישה.\p"
	.string "אם תתפוס עוד אחד, הוא יישלח\n"
	.string "אוטומטית לתיבה שלך.$"

Route31_Text_SleepyMan:
	.string "… הממממ… מה?\p"
	.string "הלכתי היום יותר מדי בחיפוש\n"
	.string "אחרי פוקימונים.\p"
	.string "הרגליים כואבות לי ואני עייף…\p"
	.string "אם הייתי פוקימון פראי,\n"
	.string "היה קל לתפוס אותי…\p"
	.string "…זזזז…$"

Route31_Text_SleepyManGotMail:
	.string "…זזזז… מה?\p"
	.string "מה זה? יש לך דואר\n"
	.string "בשבילי?$"

Route31_Text_SleepyManFail:
	.string "…זזזז…$"

Route31_Text_HandOverMailMon:
	.string "{PLAYER} מסר את הפוקימון\n"
	.string "שמחזיק את הדואר.$"

Route31_Text_ReadingMail:
	.string "בוא נראה…\p"
	.string "תודה שהבאת לי את זה.\p"
	.string "החבר שלי בחור טוב,\n"
	.string "וגם אתה נהדר!\p"
	.string "גם אני רוצה לעשות משהו\n"
	.string "טוב בתמורה!\p"
	.string "אני יודע! אני רוצה\n"
	.string "לתת לך את זה!$"

Route31_Text_DescribeRest:
	.string "…זזז…\p"
	.string "…אממ… מנוחה!\p"
	.string "הביטוי ”מנוחה להחלמה מהירה”\n"
	.string "התקצר ל”מנוחה”, מבין?\p"
	.string "זה מהלך שמאפשר לישון\n"
	.string "ולהחזיר קצת נ”ח.$"

Route31_Text_WrongMail:
	.string "This MAIL isn't for me.$"

Route31_Text_MissingMail:
	.string "Why is this POKéMON so special?\p"
	.string "It doesn't have any MAIL.$"

Route31_Text_DeclinedToHandOverMail:
	.string "What? You don't want\n"
	.string "anything?$"

Route31_Text_CantTakeLastMon:
	.string "If I take that POKéMON from\n"
	.string "you,\p"
	.string "what are you going to use in\n"
	.string "battle?$"

Route31_Text_Youngster:
	.string "מצאתי פוקימון טוב\n"
	.string "במערה החשוכה.\p"
	.string "אני הולך לאמן אותו כדי\n"
	.string "להתמודד מול פלקנר.\p"
	.string "הוא המנהיג של המכון\n"
	.string "בעיר ויולט.$"

Route31_Text_Sign:
	.string "דרך 31\p"
	.string "העיר ויולט - העיר צ'ריגרוב$"

Route31_Text_WadeRegister:
	.string "אתה מדהים! אני מחבב אותך!\p"
	.string "אני מחפש פוקימונים כאן\n"
	.string "כל יום.\p"
	.string "כשאני בעשב, אני מוצא\n"
	.string "כל מיני פירות.\p"
	.string "אם תרצה, אחלוק\n"
	.string "איתך כמה.$"

Route31_Text_WadeRematchIntro:
	.string "חיכיתי לך.\n"
	.string "בוא נילחם!$"

Route31_Text_WadeRematchDefeat:
	.string "אוףףף…$"

Route31_Text_WadePostRematch:
	.string "תשמע ממני ברגע שאמצא\n"
	.string "משהו שאולי תאהב.$"

Route31_Text_WadeHasItem:
	.string "היי! חיפשתי אותך!\p"
	.string "מצאתי משהו\n"
	.string "כשהייתי בעשב.\p"
	.string "הנה, זה בשבילך!$"

Route31_Text_WadeGaveItem:
	.string "אודיע לך אם אמצא\n"
	.string "עוד משהו!$"

Route31_Text_WadeNoRoom:
	.string "הממ, נראה שהתיק שלך\n"
	.string "מלא.\p"
	.string "תחזור כשיהיה לך מקום!$"

Route31_Text_DarkCaveSign:
	.string "המערה החשוכה$"
