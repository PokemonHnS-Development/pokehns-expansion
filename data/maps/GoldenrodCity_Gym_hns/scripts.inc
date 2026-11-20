GoldenrodCity_Gym_hns_MapScripts::
	.byte 0
@Carrie, Bridget, Victoria, Samantha, gym guy


GoldenrodCity_Gym_EventScript_Carrie::
	trainerbattle_single TRAINER_CARRIE_HNS, GoldenrodCity_Gym_Text_LassCarrieSeen, GoldenrodCity_Gym_Text_LassCarrieBeaten
	msgbox GoldenrodCity_Gym_Text_LassCarrieAfter, MSGBOX_AUTOCLOSE
	end

GoldenrodCity_Gym_EventScript_Bridget::
	trainerbattle_single TRAINER_BRIDGET_HNS, GoldenrodCity_Gym_Text_LassBridgetSeen, GoldenrodCity_Gym_Text_LassBridgetBeaten
	msgbox GoldenrodCity_Gym_Text_LassBridgetAfter, MSGBOX_AUTOCLOSE
	end

GoldenrodCity_Gym_EventScript_Victoria::
	trainerbattle_single TRAINER_VICTORIA_HNS, GoldenrodCity_Gym_Text_BeautyVictoriaSeen, GoldenrodCity_Gym_Text_BeautyVictoriaBeaten
	msgbox GoldenrodCity_Gym_Text_BeautyVictoriaAfter, MSGBOX_AUTOCLOSE
	end

GoldenrodCity_Gym_EventScript_Samantha::
	trainerbattle_single TRAINER_SAMANTHA_HNS, GoldenrodCity_Gym_Text_BeautySamanthaSeen, GoldenrodCity_Gym_Text_BeautySamanthaBeaten
	msgbox GoldenrodCity_Gym_Text_BeautySamanthaAfter, MSGBOX_AUTOCLOSE
	end

GoldenrodCity_Gym_EventScript_Gym_Guy::
	lock
	faceplayer
	goto_if_set FLAG_BADGE03_GET, GoldenrodCity_Gym_EventScript_Gym_Guy_After
	msgbox GoldenrodCity_Gym_Text_GymGuide, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_Gym_EventScript_Gym_Guy_After::
	msgbox GoldenrodCity_Gym_Text_GymGuideWin, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_Gym_EventScript_Whitney::
	lock
	faceplayer
	goto_if_eq VAR_GOLDENROD_CITY_STATE, 3, GoldenrodCity_Gym_EventScript_WhitneyCrying
	goto_if_eq VAR_GOLDENROD_CITY_STATE, 4, GoldenrodCity_Gym_EventScript_WhitneyBadge
	goto_if_set FLAG_DEFEATED_GOLDENROD_CITY_GYM, GoldenrodCity_Gym_EventScript_WhitneyDefeated
	msgbox GoldenrodCity_Gym_Text_WhitneyBefore, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_WHITNEY_1_HNS, GoldenrodCity_Gym_Text_WhitneyShouldntBeSoSerious
	msgbox GoldenrodCity_Gym_Text_WhitneyYouMeanie, MSGBOX_DEFAULT
	setvar VAR_GOLDENROD_CITY_STATE, 3
	closemessage
	release
	end

GoldenrodCity_Gym_EventScript_WhitneyCrying::
	lock
	faceplayer
	msgbox GoldenrodCity_Gym_Text_WhitneyYouMeanie, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_Gym_EventScript_WhitneyBadge::
	lock
	faceplayer
	msgbox GoldenrodCity_Gym_Text_WhitneyWhatDoYouWant, MSGBOX_DEFAULT
	closemessage
	message GoldenrodCity_Gym_Text_PlayerReceivedPlainBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox GoldenrodCity_Gym_Text_WhitneyPlainBadge, MSGBOX_DEFAULT
	setflag FLAG_BADGE03_GET
	setflag FLAG_DEFEATED_GOLDENROD_CITY_GYM
	addvar VAR_NUM_BADGES, 1
	setvar VAR_0x8008, 3
	call Common_EventScript_SetGymTrainers_hns
	giveitem ITEM_TM_ATTRACT
	msgbox GoldenrodCity_Gym_Text_WhitneyAttract, MSGBOX_DEFAULT
	setvar VAR_GOLDENROD_CITY_STATE, 5
	closemessage
	release
	end

GoldenrodCity_Gym_EventScript_WhitneyDefeated::
	lock
	faceplayer
	msgbox GoldenrodCity_Gym_Text_WhitneyGoodCry, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_Gym_EventScript_Trigger::	
	turnobject LOCALID_GOLDENROD_CITY_GYM_BRIDGET DIR_WEST
	msgbox GoldenrodCity_Gym_Text_BridgetWhitneyCries, MSGBOX_DEFAULT
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkUp1
	waitmovement 0
	setvar VAR_GOLDENROD_CITY_STATE, 4
	closemessage
	release
	end


GoldenrodCity_Gym_EventScript_Statue::
	lock
	goto_if_set FLAG_DEFEATED_GOLDENROD_CITY_GYM, GoldenrodCity_Gym_EventScript_Statue2
	msgbox GoldenrodCity_Gym_Text_GymStatue, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_Gym_EventScript_Statue2::
	msgbox GoldenrodCity_Gym_Text_GymStatueCertified, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_Gym_Text_GymStatue:
	.string "מכון הפוקימון של העיר גולדנרוד$"

GoldenrodCity_Gym_Text_GymStatueCertified:
	.string "מכון הפוקימון של העיר גולדנרוד\p"
	.string "המאמנים המוסמכים של ויטני:\n"
	.string "{PLAYER}$"

GoldenrodCity_Gym_Text_WhitneyBefore:
    .string "היי! אני ויטני!\p"
    .string "כולם התלהבו מפוקימונים, אז גם\n"
    .string "אני נכנסתי לזה!\p"
    .string "פוקימונים הם סופר-חמודים!\p"
    .string "אתה רוצה להילחם? אני מזהירה\n"
    .string "אותך: אני טובה!$"

GoldenrodCity_Gym_Text_WhitneyShouldntBeSoSerious:
    .string "יבבה…\p"
    .string "…ואאאאאאה! אתה רשע!\p"
    .string "אל תהיה כל כך רציני! אתה…\n"
    .string "אתה ילד קטן, זה מה שאתה!$"

GoldenrodCity_Gym_Text_WhitneyYouMeanie:
    .string "ואאאאה!\p"
    .string "ואאאאה!\p"
    .string "…סניף, היק… …רשע אחד!$"

GoldenrodCity_Gym_Text_WhitneyWhatDoYouWant:
    .string "…סניף…\p"
    .string "מה? מה אתה רוצה? תג?\p"
    .string "אה, נכון. שכחתי. הנה\n"
    .string "תג מישור.$"

GoldenrodCity_Gym_Text_PlayerReceivedPlainBadge:
    .string "{PLAYER} קיבל את תג מישור.$"

GoldenrodCity_Gym_Text_WhitneyPlainBadge:
    .string "תג מישור מאפשר לפוקימונים שלך\n"
    .string "להשתמש במהלך עוצמה מחוץ לקרב.\p"
    .string "הוא גם מגביר את ההגנה של\n"
    .string "הפוקימונים שלך.\p"
    .string "אה, ואתה יכול לקבל גם את זה!$"

GoldenrodCity_Gym_Text_WhitneyAttract:
    .string "זה המהלך משיכה! הוא מנצל עד הסוף\n"
    .string "את הקסם של הפוקימון.\p"
    .string "נכון שהוא פשוט מושלם\n"
    .string "בשביל חמודה כמוני?$"

GoldenrodCity_Gym_Text_WhitneyGoodCry:
    .string "אח, זה היה בכי טוב!$"

GoldenrodCity_Gym_Text_WhitneyRematch:
    .string "Hi! It's you!\p"
    .string "Wow, JOHTO CHAMPION now?\p"
    .string "You really are amazing!\p"
    .string "I want to see how strong you are.\p"
    .string "Want to have a rematch with me?$"

GoldenrodCity_Gym_Text_WhitneyRematchDefeat:
    .string "Waaaaah!\p"
    .string "Waaaaah!\p"
    .string "…Snivel, hic… …You meanie!$"

GoldenrodCity_Gym_Text_LassCarrieSeen:
    .string "שהמראה החמוד של הפוקימונים שלי\n"
    .string "לא יטעה אותך.\p"
    .string "הם יכולים להביס אותך!$"

GoldenrodCity_Gym_Text_LassCarrieBeaten:
    .string "אוף… חשבתי שאתה חלש…$"

GoldenrodCity_Gym_Text_LassCarrieAfter:
    .string "הפוקימונים שלי חושבים שאני חמודה?$"

GoldenrodCity_Gym_Text_LassBridgetSeen:
    .string "אני אוהבת פוקימונים חמודים יותר\n"
    .string "מפוקימונים חזקים.\p"
    .string "אבל יש לי פוקימונים חזקים וחמודים!$"

GoldenrodCity_Gym_Text_LassBridgetBeaten:
    .string "אוי, לא, לא, לא!$"

GoldenrodCity_Gym_Text_LassBridgetAfter:
    .string "אני מנסה לנצח את ויטני, אבל…\n"
    .string "זה מדכא.\p"
    .string "אני בסדר! אם אפסיד, פשוט אתאמץ\n"
    .string "יותר בפעם הבאה!$"

GoldenrodCity_Gym_Text_BridgetWhitneyCries:
    .string "אוי, לא. גרמת לויטני לבכות.\p"
    .string "זה בסדר. היא תפסיק עוד מעט. היא\n"
    .string "תמיד בוכה כשהיא מפסידה.$"

GoldenrodCity_Gym_Text_BeautyVictoriaSeen:
    .string "אוי, איזה מאמן קטן וחמוד!\p"
    .string "אתה מוצא חן בעיניי, אבל לא אוותר לך!$"

GoldenrodCity_Gym_Text_BeautyVictoriaBeaten:
    .string "בוא נראה… אופס, זה נגמר?$"

GoldenrodCity_Gym_Text_BeautyVictoriaAfter:
    .string "וואו, אתה בטח טוב אם ניצחת אותי!\n"
    .string "תמשיך ככה!$"

GoldenrodCity_Gym_Text_BeautySamanthaSeen:
    .string "תן את כל מה שיש לך, אחרת\n"
    .string "אני אביס אותך!$"

GoldenrodCity_Gym_Text_BeautySamanthaBeaten:
    .string "לא! אוי, מיאו, אני כל כך מצטערת!$"

GoldenrodCity_Gym_Text_BeautySamanthaAfter:
    .string "לימדתי את מיאו מהלכים נגד\n"
    .string "כל סוג…$"

GoldenrodCity_Gym_Text_GymGuide:
    .string "יו! אלוף לעתיד!\p"
    .string "המכון הזה הוא הבית של ויטני,\n"
    .string "המומחית לפוקימונים מסוג רגיל.\p"
    .string "צריך להיזהר מהקבוצה החמודה שלה.\p"
    .string "לחלק מהפוקימונים כאן יש גם את\n"
    .string "הסוג פיה, שהתגלה לאחרונה.\p"
    .string "אם צריך פוקימון מסוג קרב או רעל,\n"
    .string "כדאי לבדוק בדרך 34.$"

GoldenrodCity_Gym_Text_GymGuideWin:
    .string "ניצחת? מעולה! הייתי עסוק בלהתפעל\n"
    .string "מהגברות כאן.$"

