CeruleanCity_Gym_Frlg_MapScripts::
	.byte 0

CeruleanCity_Gym_EventScript_Misty::
	famechecker FAMECHECKER_MISTY, FCPICKSTATE_COLORED, UpdatePickStateFromSpecialVar8005
	trainerbattle_single TRAINER_LEADER_MISTY, CeruleanCity_Gym_Text_MistyIntro, CeruleanCity_Gym_Text_MistyDefeat, CeruleanCity_Gym_EventScript_MistyDefeated, NO_MUSIC
	goto_if_unset FLAG_GOT_TM03_FROM_MISTY, CeruleanCity_Gym_EventScript_GiveTM03
	msgbox CeruleanCity_Gym_Text_ExplainTM03
	release
	end

CeruleanCity_Gym_EventScript_MistyDefeated::
	famechecker FAMECHECKER_MISTY, 1
	setflag FLAG_DEFEATED_MISTY
	setflag FLAG_BADGE02_GET
	setrespawn HEAL_LOCATION_CERULEAN_CITY
	set_gym_trainers_frlg 2
	goto CeruleanCity_Gym_EventScript_GiveTM03
	end

CeruleanCity_Gym_EventScript_GiveTM03::
	msgbox CeruleanCity_Gym_Text_ExplainCascadeBadge
	checkitemspace ITEM_TM03
	goto_if_eq VAR_RESULT, FALSE, CeruleanCity_Gym_EventScript_NoRoomForTM03
	giveitem_msg CeruleanCity_Gym_Text_ReceivedTM03FromMisty, ITEM_TM03
	setflag FLAG_GOT_TM03_FROM_MISTY
	msgbox CeruleanCity_Gym_Text_ExplainTM03
	release
	end

CeruleanCity_Gym_EventScript_NoRoomForTM03::
	msgbox CeruleanCity_Gym_Text_BetterMakeRoomForThis
	release
	end

CeruleanCity_Gym_EventScript_Diana::
	trainerbattle_single TRAINER_PICNICKER_DIANA, CeruleanCity_Gym_Text_DianaIntro, CeruleanCity_Gym_Text_DianaDefeat
	msgbox CeruleanCity_Gym_Text_DianaPostBattle, MSGBOX_AUTOCLOSE
	end

CeruleanCity_Gym_EventScript_Luis::
	trainerbattle_single TRAINER_SWIMMER_MALE_LUIS, CeruleanCity_Gym_Text_LuisIntro, CeruleanCity_Gym_Text_LuisDefeat
	famechecker FAMECHECKER_MISTY, 2
	msgbox CeruleanCity_Gym_Text_LuisPostBattle, MSGBOX_AUTOCLOSE
	end

CeruleanCity_Gym_EventScript_GymGuy::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_MISTY, CeruleanCity_Gym_EventScript_GymGuyPostVictory
	msgbox CeruleanCity_Gym_Text_GymGuyAdvice
	release
	end

CeruleanCity_Gym_EventScript_GymGuyPostVictory::
	msgbox CeruleanCity_Gym_Text_WeMakePrettyGoodTeam
	release
	end

CeruleanCity_Gym_EventScript_GymStatue::
	lockall
	goto_if_set FLAG_BADGE02_GET, CeruleanCity_Gym_EventScript_GymStatuePostVictory
	msgbox CeruleanCity_Gym_Text_GymStatue
	releaseall
	end

CeruleanCity_Gym_EventScript_GymStatuePostVictory::
	msgbox CeruleanCity_Gym_Text_GymStatuePlayerWon
	releaseall
	end

CeruleanCity_Gym_Text_MistyIntro::
	.string "היי, אתה חדש כאן!\p"
	.string "רק מאמנים עם גישה ברורה\n"
	.string "לפוקימונים יכולים להיות מקצוענים.\p"
	.string "מה הגישה שלך כשאתה\n"
	.string "תופס ומאמן פוקימונים?\p"
	.string "הגישה שלי היא מתקפה כוללת\n"
	.string "עם פוקימונים מסוג מים!{PLAY_BGM}{MUS_RG_ENCOUNTER_GYM_LEADER}$"

CeruleanCity_Gym_Text_ExplainTM03::
	.string "מ”מ 03 מלמד את דופק מים.\p"
	.string "כדאי להשתמש בו על פוקימון ימי!$"

CeruleanCity_Gym_Text_ExplainCascadeBadge::
	.string "תג מפל גורם לכל הפוקימונים\n"
	.string "עד רמה 30 לציית.\p"
	.string "זה כולל אפילו פוקימונים זרים\n"
	.string "שקיבלת בהחלפות.\p"
	.string "ויש עוד. עכשיו אפשר להשתמש\n"
	.string "בחיתוך בכל זמן, גם מחוץ לקרב.\p"
	.string "בעזרת חיתוך אפשר לכרות עצים\n"
	.string "קטנים ולפתוח שבילים חדשים.\p"
	.string "ואתה יכול לקבל גם את\n"
	.string "המ”מ האהוב עליי.$"

CeruleanCity_Gym_Text_ReceivedTM03FromMisty::
	.string "{PLAYER} קיבל את מ”מ 03\n"
	.string "ממיסטי.$"

CeruleanCity_Gym_Text_BetterMakeRoomForThis::
	.string "כדאי לך לפנות לזה מקום!$"

CeruleanCity_Gym_Text_MistyDefeat::
	.string "וואו!\n"
	.string "אתה חזק מדי!\p"
	.string "נו, טוב!\p"
	.string "קח את תג מפל כהוכחה\n"
	.string "שניצחת אותי.$"

CeruleanCity_Gym_Text_DianaIntro::
	.string "What? You?\n"
	.string "I'm more than good enough for you!\p"
	.string "MISTY won't have to be bothered.$"

CeruleanCity_Gym_Text_DianaDefeat::
	.string "You overwhelmed me!$"

CeruleanCity_Gym_Text_DianaPostBattle::
	.string "You have to face other TRAINERS\n"
	.string "to see how good you really are.$"

CeruleanCity_Gym_Text_LuisIntro::
	.string "Splash!\p"
	.string "I'm first up!\n"
	.string "Let's do it!$"

CeruleanCity_Gym_Text_LuisDefeat::
	.string "That can't be!$"

CeruleanCity_Gym_Text_LuisPostBattle::
	.string "MISTY is a TRAINER who's going to\n"
	.string "keep improving.\p"
	.string "She won't lose to someone like you!$"

CeruleanCity_Gym_Text_GymGuyAdvice::
	.string "יו!\n"
	.string "אלוף לעתיד!\p"
	.string "אני אתן לך עצה!\p"
	.string "המנהיגה, מיסטי, היא מקצוענית\n"
	.string "שמשתמשת בפוקימונים מסוג מים.\p"
	.string "אפשר לייבש להם את כל המים\n"
	.string "עם פוקימונים מסוג עשב.\p"
	.string "או שאפשר להשתמש בפוקימונים\n"
	.string "מסוג חשמל ולחשמל אותם!$"

CeruleanCity_Gym_Text_WeMakePrettyGoodTeam::
	.string "ניצחת את מיסטי!\n"
	.string "נו, מה אמרתי לך?\p"
	.string "אתה ואני, ילד, אנחנו צוות\n"
	.string "מוצלח לגמרי!$"

CeruleanCity_Gym_Text_GymStatue::
	.string "מכון הפוקימון של סרוליאן\n"
	.string "מנהיגה: מיסטי\p"
	.string "מאמנים מנצחים:\n"
	.string "{RIVAL}$"

CeruleanCity_Gym_Text_GymStatuePlayerWon::
	.string "מכון הפוקימון של סרוליאן\n"
	.string "מנהיגה: מיסטי\p"
	.string "מאמנים מנצחים:\n"
	.string "{RIVAL}, {PLAYER}$"

