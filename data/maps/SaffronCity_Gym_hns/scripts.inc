SaffronCity_Gym_hns_MapScripts::
	.byte 0

SaffronCity_Gym_EventScript_GymGuy::
	goto_if_set FLAG_DEFEATED_SAFFRON_GYM, SaffronCity_Gym_EventScript_GymGuy2
	msgbox SaffronCity_Gym_Text_GymGuideIntro, MSGBOX_NPC
	end

SaffronCity_Gym_EventScript_GymGuy2::
	msgbox SaffronCity_Gym_Text_GymGuideWin, MSGBOX_NPC
	end

SaffronCity_Gym_EventScript_Rebecca::
	trainerbattle_single TRAINER_REBECCA_HNS, SaffronCity_Gym_Text_MediumRebeccaSeen, SaffronCity_Gym_Text_MediumRebeccaBeaten
	msgbox SaffronCity_Gym_Text_MediumRebeccaAfter, MSGBOX_AUTOCLOSE
	end

SaffronCity_Gym_EventScript_Franklin::
	trainerbattle_single TRAINER_FRANKLIN_HNS, SaffronCity_Gym_Text_PsychicFranklinSeen, SaffronCity_Gym_Text_PsychicFranklinBeaten
	msgbox SaffronCity_Gym_Text_PsychicFranklinAfter, MSGBOX_AUTOCLOSE
	end

SaffronCity_Gym_EventScript_Doris::
	trainerbattle_single TRAINER_DORIS_HNS, SaffronCity_Gym_Text_MediumDorisSeen, SaffronCity_Gym_Text_MediumDorisBeaten
	msgbox SaffronCity_Gym_Text_MediumDorisAfter, MSGBOX_AUTOCLOSE
	end

SaffronCity_Gym_EventScript_Jared::
	trainerbattle_single TRAINER_JARED_HNS, SaffronCity_Gym_Text_PsychicJaredSeen, SaffronCity_Gym_Text_PsychicJaredBeaten
	msgbox SaffronCity_Gym_Text_PsychicJaredAfter, MSGBOX_AUTOCLOSE
	end

SaffronCity_Gym_EventScript_Sabrina::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_SAFFRON_GYM, SaffronCity_Gym_EventScript_Sabrina_Defeated
	msgbox SaffronCity_Gym_Text_SabrinaIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_SABRINA_HNS, SaffronCity_Gym_Text_SabrinaWinLoss
	message SaffronCity_Gym_Text_ReceivedMarshBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox SaffronCity_Gym_Text_MarshBadgeInfo, MSGBOX_DEFAULT
	msgbox SaffronCity_Gym_Text_Sabrina_GiveTM, MSGBOX_DEFAULT
	giveitem ITEM_TM_SKILL_SWAP
	msgbox SaffronCity_Gym_Text_Sabrina_ExplainTM, MSGBOX_DEFAULT
	setflag FLAG_BADGE13_GET
	setflag FLAG_DEFEATED_SAFFRON_GYM
	addvar VAR_NUM_BADGES, 1
	setvar VAR_0x8008, 13
	call Common_EventScript_SetGymTrainers_hns
	closemessage
	clearflag FLAG_HIDE_OLIVINE_SABRINA
	release
	end

SaffronCity_Gym_EventScript_Sabrina_Defeated::
	msgbox SaffronCity_Gym_Text_SabrinaPostBattle, MSGBOX_DEFAULT
	closemessage
	release
	end

SaffronCity_Gym_Text_SabrinaIntro:
	.string "סברינה: ידעתי שתבוא…\p"
	.string "לפני שלוש שנים ראיתי בחזון\n"
	.string "את הגעתך.\p"
	.string "אתה בא בשביל התג שלי.\p"
	.string "אני לא נהנית מקרבות, אבל חובתי כמנהיגה\n"
	.string "להעניק תגים לכל מי שהוכיח שהוא ראוי.\p"
	.string "מכיוון שזה רצונך, אראה לך\n"
	.string "את הכוחות העל-חושיים שלי!$"

SaffronCity_Gym_Text_SabrinaWinLoss:
	.string "סברינה: הכוח שלך…\p"
	.string "הוא עולה בהרבה על מה שחזיתי…\p"
	.string "אולי אי אפשר לחזות עד הסוף\n"
	.string "את מה שצופן העתיד…\p"
	.string "בסדר, ניצחת. הרווחת ביושר\n"
	.string "את תג ביצה.$"

SaffronCity_Gym_Text_ReceivedMarshBadge:
	.string "{PLAYER} קיבל את תג ביצה.$"

SaffronCity_Gym_Text_MarshBadgeInfo:
	.string "סברינה: תג ביצה מעורר\n"
	.string "את כוחותיך התת-מודעים…\p"
	.string "אף שלא חזיתי במדויק את כוחך,\n"
	.string "דבר אחד אני יודעת בוודאות.\p"
	.string "אתה תהיה אלוף מפורסם ואהוב!$"

SaffronCity_Gym_Text_Sabrina_GiveTM:
	.string "הנה, קח גם את זה.$"

SaffronCity_Gym_Text_Sabrina_ExplainTM:
	.string "הוא מכיל את חילוף יכולת.\p"
	.string "הוא יכול לקחת מהיריבים\n"
	.string "את היכולות שלהם ולתת להם את שלך.\p"
	.string "השתמש בו בתבונה…$"

SaffronCity_Gym_Text_SabrinaPostBattle:
	.string "סברינה: אהבתך לפוקימונים שלך\n"
	.string "גברה על כוחי העל-חושי…\p"
	.string "כוח האהבה, לדעתי, הוא\n"
	.string "גם סוג של כוח על-חושי…$"

SaffronCity_Gym_Text_SabrinaRematch:
	.string "SABRINA: Ah, the KANTO CHAMPION.\p"
	.string "I sensed your return.\p"
	.string "Your power has grown immensely.\p"
	.string "Even now, I feel your aura.\p"
	.string "Want to have a rematch with me?$"

SaffronCity_Gym_Text_SabrinaRematchDefeat:
	.string "SABRINA: Your love for your\n"
	.string "POKéMON again overwhelmed my\l"
	.string "psychic power…$"

SaffronCity_Gym_Text_MediumRebeccaSeen:
	.string "הכוח של כל מי שהבסת\n"
	.string "עובר אליי!$"

SaffronCity_Gym_Text_MediumRebeccaBeaten:
	.string "חזק… חזק מדי…$"

SaffronCity_Gym_Text_MediumRebeccaAfter:
	.string "מה מקור הכוח שלך?$"

SaffronCity_Gym_Text_PsychicFranklinSeen:
	.string "כוח על-חושי הוא הכוח\n"
	.string "של הנשמה שלך.$"

SaffronCity_Gym_Text_PsychicFranklinBeaten:
	.string "בנשמה שלך יש יותר כוח\n"
	.string "מאשר בשלי!$"

SaffronCity_Gym_Text_PsychicFranklinAfter:
	.string "חיזקת את הנשמה שלך, לא רק\n"
	.string "את היכולות שלך.$"

SaffronCity_Gym_Text_MediumDorisSeen:
	.string "פופופופו… אני רואה את זה בבירור.\p"
	.string "אני רואה לתוך הנשמה שלך!$"

SaffronCity_Gym_Text_MediumDorisBeaten:
	.string "קראתי אותך, ובכל זאת הפסדתי…$"

SaffronCity_Gym_Text_MediumDorisAfter:
	.string "אוף! שכחתי שחזיתי\n"
	.string "שאפסיד לך.$"

SaffronCity_Gym_Text_PsychicJaredSeen:
	.string "דוג'ו הלחימה הסמוך היה פעם\n"
	.string "המכון של העיר הזאת.$"

SaffronCity_Gym_Text_PsychicJaredBeaten:
	.string "לא היה לי סיכוי…$"

SaffronCity_Gym_Text_PsychicJaredAfter:
	.string "סברינה בדיוק ריסקה את מלך הקראטה,\n"
	.string "המאסטר של דוג'ו הלחימה.$"

SaffronCity_Gym_Text_GymGuideIntro:
	.string "יו, אלוף לעתיד!\p"
	.string "מאמן מיומן כמוך לא צריך שיסבירו\n"
	.string "לו איך להתמודד עם פוקימונים\l"
	.string "מסוג על-חושי, נכון?\p"
	.string "אני מצפה ממך לדברים גדולים!\p"
	.string "בהצלחה!$"

SaffronCity_Gym_Text_GymGuideWin:
	.string "זה היה עוד קרב פנטסטי!$"

SaffronCity_Gym_EventScript_GymStatue::
	lockall
	goto_if_set FLAG_BADGE13_GET, SaffronCity_Gym_EventScript_GymStatuePostVictory
	msgbox SaffronCity_Gym_Text_GymStatue
	releaseall
	end

SaffronCity_Gym_EventScript_GymStatuePostVictory::
	msgbox SaffronCity_Gym_Text_GymStatuePlayerWon
	releaseall
	end


SaffronCity_Gym_Text_GymStatue::
    .string "מכון הפוקימון של סאפרון\n"
    .string "מנהיגה: סברינה\p"
    .string "מאמנים מנצחים:\n"
    .string "בלו, רד$"

SaffronCity_Gym_Text_GymStatuePlayerWon::
    .string "מכון הפוקימון של סאפרון\n"
    .string "מנהיגה: סברינה\p"
    .string "מאמנים מנצחים:\n"
    .string "בלו, רד, {PLAYER}$"
