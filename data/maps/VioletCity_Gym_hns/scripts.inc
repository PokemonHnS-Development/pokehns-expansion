VioletCity_Gym_hns_MapScripts::
	.byte 0

VioletCity_Gym_EventScript_GymGuy::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_VIOLET_GYM, VioletCity_Gym_EventScript_GymGuy2
	msgbox VioletGym_Text_GymGuide_Intro, MSGBOX_DEFAULT
	closemessage
	release
	end
	
VioletCity_Gym_EventScript_GymGuy2::
	msgbox VioletGym_Text_GymGuide_Win, MSGBOX_DEFAULT
	release
	end	

VioletCity_Gym_EventScript_Rod::
	trainerbattle_single TRAINER_ROD_HNS, VioletGym_Text_BirdKeeperRod_Seen, VioletGym_Text_BirdKeeperRod_Beaten
	msgbox VioletGym_Text_BirdKeeperRod_After, MSGBOX_AUTOCLOSE
	end

VioletCity_Gym_EventScript_Abe::
	trainerbattle_single TRAINER_ABE_HNS, VioletGym_Text_BirdKeeperAbe_Seen, VioletGym_Text_BirdKeeperAbe_Beaten
	msgbox VioletGym_Text_BirdKeeperAbe_After, MSGBOX_AUTOCLOSE
	end

VioletCity_Gym_EventScript_Falkner::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_VIOLET_GYM, VioletCity_Gym_EventScript_Falkner_Defeated
	msgbox VioletGym_Text_Falkner_Intro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_FALKNER_1_HNS, VioletGym_Text_Falkner_WinLoss
	message VioletGym_Text_ReceivedZephyrBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox VioletGym_Text_Falkner_BadgeExplain, MSGBOX_DEFAULT
	setflag FLAG_BADGE01_GET
	setflag FLAG_DEFEATED_VIOLET_GYM
	addvar VAR_NUM_BADGES, 1
	setvar VAR_0x8008, 1
	call Common_EventScript_SetGymTrainers_hns
	giveitem ITEM_TM_ROOST
	msgbox VioletGym_Text_Falkner_TMExplain, MSGBOX_DEFAULT
	setvar VAR_VIOLET_CITY_STATE, 3
	setrespawn HEAL_LOCATION_VIOLET_CITY_HNS
	closemessage
	release
	end

VioletCity_Gym_EventScript_Falkner_Defeated::
	msgbox VioletGym_Text_Falkner_AfterFight, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletGym_Text_Falkner_Intro:
	.string "אני פלקנר, מנהיג מכון הפוקימון\n"
	.string "של העיר ויולט!\p"
	.string "אומרים שאפשר לקצץ את הכנפיים\n"
	.string "של פוקימונים מסוג תעופה\p"
	.string "בעזרת מכת חשמל… אני לא אסכים\n"
	.string "לעלבון כזה כלפי פוקימוני ציפורים!\p"
	.string "אני אראה לך את הכוח האמיתי\n"
	.string "של פוקימוני הציפורים המופלאים!$"

VioletGym_Text_Falkner_WinLoss:
	.string "…לעזאזל! פוקימוני הציפורים\n"
	.string "היקרים של אבא שלי…\p"
	.string "נו, טוב. הנה, זה בשבילך.\p"
	.string "זה תג משב, התג הרשמי\n"
	.string "של ליגת הפוקימון.$"

VioletGym_Text_ReceivedZephyrBadge:
	.string "{PLAYER} קיבל את תג משב.$"

VioletGym_Text_Falkner_BadgeExplain:
	.string "תג משב מעלה את\n"
	.string "כוח ההתקפה של פוקימונים.\p"
	.string "הוא גם מאפשר לפוקימונים שיכולים\n"
	.string "ללמוד הבזק להשתמש בו בכל זמן.\p"
	.string "הנה, גם זה בשבילך.$"

VioletGym_Text_Falkner_TMExplain:
	.string "בעזרת מ”מ, פוקימון לומד מיד\n"
	.string "מהלך חדש.\p"
	.string "המ”מ הזה מכיל את מנוחת כנף.\p"
	.string "הוא מחזיר לפוקימון שלך עד חצי\n"
	.string "מהנ”ח המרבי שלו.\p"
	.string "במילים אחרות, הוא מרפא את\n"
	.string "הפוקימון שלך.$"

VioletGym_Text_Falkner_AfterFight:
	.string "בערים ובעיירות שבהמשך הדרך\n"
	.string "יש מכוני פוקימון.\p"
	.string "כדאי לך לבחון את הכישורים שלך\n"
	.string "במכונים האלה.\p"
	.string "ואני אתאמן קשה יותר כדי להיות\n"
	.string "אמן הציפורים הגדול ביותר!$"

VioletGym_Text_Falkner_Rematch:
	.string "Congratulations on defeating\n"
	.string "the ELITE 4!\p"
	.string "I've been training my\n"
	.string "FLYING-type POKéMON even harder.\p"
	.string "Think you can take on the power\n"
	.string "of the skies again?$"

VioletGym_Text_Falkner_RematchLoss:
	.string "Wow… You beat me again.\p"
	.string "I'm going to train harder to\n"
	.string "become the greatest bird master!$"

VioletGym_Text_BirdKeeperRod_Seen:
	.string "מילת המפתח היא אומץ!\p"
	.string "כולם כאן מתאמנים יומם ולילה כדי\n"
	.string "להפוך לאמנים של פוקימוני ציפורים.\p"
	.string "קדימה!$"

VioletGym_Text_BirdKeeperRod_Beaten:
	.string "אאאאח!$"

VioletGym_Text_BirdKeeperRod_After:
	.string "פלקנר מיומן באמת!\p"
	.string "אל תתרברב רק כי ניצחת אותי!$"

VioletGym_Text_BirdKeeperAbe_Seen:
	.string "נראה אם יש לך מה שצריך\n"
	.string "כדי להתמודד מול פלקנר!$"

VioletGym_Text_BirdKeeperAbe_Beaten:
	.string "זה לא יכול להיות!$"

VioletGym_Text_BirdKeeperAbe_After:
	.string "זה פתטי, להפסיד לאיזה מאמן טירון…$"

VioletGym_Text_GymGuide_Intro:
	.string "היי! מה קורה? אני לא מאמן,\n"
	.string "אבל אני יכול לתת כמה עצות!\p"
	.string "תאמין לי! אם מאמינים,\n"
	.string "חלום האליפות יכול להתגשם.\p"
	.string "אתה מאמין? אז תקשיב.\p"
	.string "הקלף המנצח של פלקנר הוא ינשוף\n"
	.string "חסון שאוהב לאכול פירות.\p"
	.string "הוא לא החזק ביותר,\n"
	.string "אבל הוא יכול לספוג הרבה מכות.\p"
	.string "אפשר לפגוע בו במהלכים מסוג חשמל\n"
	.string "וסלע, אבל צריך להיזהר מסטירת בוץ!\p"
	.string "אם צריך עוד עזרה, כדאי לבקר\n"
	.string "באקדמיית הפוקימון.\p"
	.string "התלמידים שם באמת יודעים\n"
	.string "על מה הם מדברים!$"

VioletGym_Text_GymGuide_Win:
	.string "קרב יפה! תמשיך ככה,\n"
	.string "ותהיה האלוף תוך זמן קצר!$"

VioletCity_Gym_EventScript_Statue::
	lock
	goto_if_set FLAG_DEFEATED_VIOLET_GYM, VioletCity_Gym_EventScript_Statue2
	msgbox VioletCity_Gym_Text_GymStatue, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_Gym_EventScript_Statue2::
	msgbox VioletCity_Gym_Text_GymStatueCertified, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_Gym_Text_GymStatue:
	.string "מכון הפוקימון של העיר ויולט$"

VioletCity_Gym_Text_GymStatueCertified:
	.string "מכון הפוקימון של העיר ויולט\p"
	.string "המאמנים המוסמכים של פלקנר:\n"
	.string "{PLAYER}$"
