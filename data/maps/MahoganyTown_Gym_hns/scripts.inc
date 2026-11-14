MahoganyTown_Gym_hns_MapScripts::
	.byte 0


MahoganyTown_Gym_EventScript_Statue::
	lock
	goto_if_set FLAG_DEFEATED_MAHOGANY_TOWN_GYM,  MahoganyTown_Gym_EventScript_Statue2
	msgbox MahoganyTown_Gym_Text_GymStatue, MSGBOX_DEFAULT
	closemessage
	release
	end

MahoganyTown_Gym_EventScript_Statue2::
	msgbox MahoganyTown_Gym_Text_GymStatueCertified, MSGBOX_DEFAULT
	closemessage
	release
	end

MahoganyTown_Gym_Text_GymStatue:
	.string "מכון הפוקימון של העיירה מהגוני$"

MahoganyTown_Gym_Text_GymStatueCertified:
	.string "מכון הפוקימון של העיירה מהגוני\p"
	.string "המאמנים המוסמכים של פרייס:\n"
	.string "{PLAYER}$"


MahoganyTown_GymEventScript_GymGuy::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_MAHOGANY_TOWN_GYM, MahoganyTown_Gym_EventScript_GymGuy2
	msgbox MahoganyTown_Gym_Text_Guide, MSGBOX_DEFAULT
	closemessage
	release
	end
	
MahoganyTown_Gym_EventScript_GymGuy2::
	msgbox MahoganyTown_Gym_Text_GuideWin, MSGBOX_DEFAULT
	release
	end	

MahoganyTown_Gym_EventScript_Ronald::
	trainerbattle_single TRAINER_RONALD_HNS, MahoganyTown_Gym_Text_BoarderRonaldSeen, MahoganyTown_Gym_Text_BoarderRonaldBeaten
	msgbox MahoganyTown_Gym_Text_BoarderRonaldAfter, MSGBOX_AUTOCLOSE
	end

MahoganyTown_Gym_EventScript_Brad::
	trainerbattle_single TRAINER_BRAD_HNS, MahoganyTown_Gym_Text_BoarderBradSeen, MahoganyTown_Gym_Text_BoarderBradBeaten
	msgbox MahoganyTown_Gym_Text_BoarderBradAfter, MSGBOX_AUTOCLOSE
	end

MahoganyTown_Gym_EventScript_Douglas::
	trainerbattle_single TRAINER_DOUGLAS_HNS, MahoganyTown_Gym_Text_BoarderDouglasSeen, MahoganyTown_Gym_Text_BoarderDouglasBeaten
	msgbox MahoganyTown_Gym_Text_BoarderDouglasAfter, MSGBOX_AUTOCLOSE
	end

MahoganyTown_Gym_EventScript_Roxanne::
	trainerbattle_single TRAINER_ROXANNE_HNS, MahoganyTown_Gym_Text_SkierRoxanneSeen, MahoganyTown_Gym_Text_SkierRoxanneBeaten
	msgbox MahoganyTown_Gym_Text_SkierRoxanneAfter, MSGBOX_AUTOCLOSE
	end

MahoganyTown_Gym_EventScript_Clarissa::
	trainerbattle_single TRAINER_CLARISSA_HNS, MahoganyTown_Gym_Text_SkierClarissaSeen, MahoganyTown_Gym_Text_SkierClarissaBeaten
	msgbox MahoganyTown_Gym_Text_SkierClarissaAfter, MSGBOX_AUTOCLOSE
	end

MahoganyTown_Gym_EventScript_Pryce::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_MAHOGANY_TOWN_GYM, MahoganyTown_Gym_EventScript_Pryce_Defeated
	msgbox MahoganyTown_Gym_Text_PryceIntro, MSGBOX_DEFAULT
	goto_if_set FLAG_DEFEATED_OLIVINE_CITY_GYM, MahoganyTown_Gym_EventScript_OlivineCheckCianwood
	goto_if_set FLAG_DEFEATED_CIANWOOD_GYM, MahoganyTown_Gym_EventScript_CianwoodCheckOlivine
	goto MahoganyTown_Gym_EventScript_Pryce_Battle1

MahoganyTown_Gym_EventScript_PryceVictory::
	message MahoganyTown_Gym_Text_ReceivedBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox MahoganyTown_Gym_Text_GlacierBadgeSpeech, MSGBOX_DEFAULT
	setflag FLAG_BADGE07_GET
	setflag FLAG_DEFEATED_MAHOGANY_TOWN_GYM
    addvar VAR_NUM_BADGES, 1
	setvar VAR_0x8008, 7
	call Common_EventScript_SetGymTrainers_hns
	giveitem ITEM_TM_HAIL
	msgbox MahoganyTown_Gym_Text_HailSpeech, MSGBOX_DEFAULT
	setvar VAR_MAHOGANY_TOWN_STATE, 15
    setrespawn HEAL_LOCATION_MAHOGANY_TOWN_HNS
    call_if_eq VAR_NUM_BADGES, 7, MahoganyTown_Gym_EventScript_SetupElmRocketCall
	closemessage
	release
	end

MahoganyTown_Gym_EventScript_SetupElmRocketCall::
    setvar VAR_TRIGGER_ELM_ROCKET_CALL, 1
    return

MahoganyTown_Gym_EventScript_OlivineCheckCianwood::
	goto_if_set FLAG_DEFEATED_CIANWOOD_GYM, MahoganyTown_Gym_EventScript_Pryce_Battle3
	goto MahoganyTown_Gym_EventScript_Pryce_Battle2

MahoganyTown_Gym_EventScript_CianwoodCheckOlivine::
	goto_if_set FLAG_DEFEATED_OLIVINE_CITY_GYM, MahoganyTown_Gym_EventScript_Pryce_Battle3
	goto MahoganyTown_Gym_EventScript_Pryce_Battle2
	
MahoganyTown_Gym_EventScript_Pryce_Battle1::
	trainerbattle_no_intro TRAINER_PRYCE_1_HNS, MahoganyTown_Gym_Text_PryceImpressed
	goto MahoganyTown_Gym_EventScript_PryceVictory

MahoganyTown_Gym_EventScript_Pryce_Battle2::
	trainerbattle_no_intro TRAINER_PRYCE_1_2_HNS, MahoganyTown_Gym_Text_PryceImpressed
	goto MahoganyTown_Gym_EventScript_PryceVictory

MahoganyTown_Gym_EventScript_Pryce_Battle3::
	trainerbattle_no_intro TRAINER_PRYCE_1_3_HNS, MahoganyTown_Gym_Text_PryceImpressed
	goto MahoganyTown_Gym_EventScript_PryceVictory

MahoganyTown_Gym_EventScript_Pryce_Defeated::
	msgbox MahoganyTown_Gym_Text_CherishPokemon, MSGBOX_DEFAULT
	closemessage
	release
	end

MahoganyTown_Gym_Text_PryceIntro:
    .string "לפוקימונים יש חוויות רבות\n"
    .string "בחייהם, בדיוק כמו לנו.\p"
    .string "גם אני ראיתי וסבלתי הרבה בחיי.\p"
    .string "מכיוון שאני מבוגר ממך, הרשה לי\n"
    .string "להראות לך למה אני מתכוון.\p"
    .string "אני חי לצד פוקימונים עוד\n"
    .string "מלפני שנולדת.\p"
    .string "אני לא מפסיד בקלות.\p"
    .string "אני, פרייס, מאמן החורף,\n"
    .string "אראה לך את כוחי!$"

MahoganyTown_Gym_Text_PryceImpressed:
    .string "אה, הכישרון שלך מרשים אותי.\p"
    .string "עם רצון חזק כמו שלך, אני יודע\n"
    .string "שתתגבר על כל מכשולי החיים.\p"
    .string "התג הזה מגיע לך בצדק!$"

MahoganyTown_Gym_Text_ReceivedBadge:
    .string "{PLAYER} קיבל את תג קרחון.$"

MahoganyTown_Gym_Text_GlacierBadgeSpeech:
    .string "התג הזה מעלה את ההתקפה\n"
    .string "המיוחדת של פוקימונים.\p"
    .string "הוא גם מאפשר לפוקימונים שלך להשתמש\n"
    .string "במערבולת לחציית מערבולות אמיתיות.\p"
    .string "וזה… זו מתנה ממני!$"

MahoganyTown_Gym_Text_HailSpeech:
    .string "המ”מ הזה מכיל את ברד.\p"
    .string "הוא גורם נזק בכל תור\n"
    .string "במשך 5 תורים.\p"
    .string "הוא ממחיש את חומרת\n"
    .string "החורף.$"

MahoganyTown_Gym_Text_CherishPokemon:
    .string "כשהקרח והשלג נמסים,\n"
    .string "האביב מגיע.\p"
    .string "אתה והפוקימונים שלך תהיו\n"
    .string "יחד עוד שנים רבות.\p"
    .string "הוקירו את הזמן שלכם יחד!$"

MahoganyTown_Gym_Text_PryceRematch:
    .string "Ah, JOHTO CHAMPION!\p"
    .string "Your skills are indeed\n"
    .string "remarkable.\p"
    .string "I am impressed.\p"
    .string "But even now, there is much to\n"
    .string "learn from each other.\p"
    .string "I, PRYCE--the winter trainer--\n"
    .string "still have a few tricks left.\p"
    .string "Want to have a rematch with me?$"

MahoganyTown_Gym_Text_PryceRematchDefeat:
    .string "Ah, yet again I'm impressed by\n"
    .string "your prowess.\p"
    .string "With your strong will, I know you\n"
    .string "will overcome all life's obstacles.$"

MahoganyTown_Gym_Text_Guide:
    .string "פרייס הוא ותיק שמאמן פוקימונים\n"
    .string "כבר בערך 50 שנה.\p"
    .string "יש לו הרכב פוקימונים חזק\n"
    .string "שיכול להתמודד עם כל מה שתביא נגדו.\p"
    .string "אש היא נקודת פתיחה טובה,\n"
    .string "אבל כדאי להיזהר מהגשם!$"

MahoganyTown_Gym_Text_GuideWin:
    .string "פרייס הוא משהו, אבל אתה\n"
    .string "משהו אחר לגמרי!\p"
    .string "זה היה קרב לוהט שגישר\n"
    .string "על פער הדורות!$"

MahoganyTown_Gym_Text_BoarderRonaldSeen:
    .string "אקפיא את הפוקימונים שלך,\n"
    .string "כך שלא תוכל לעשות כלום!$"

MahoganyTown_Gym_Text_BoarderRonaldBeaten:
    .string "אוף. לא יכולתי לעשות כלום.$"

MahoganyTown_Gym_Text_BoarderRonaldAfter:
    .string "נראה לי שיש מהלך שפוקימון יכול\n"
    .string "להשתמש בו גם כשהוא קפוא.$"

MahoganyTown_Gym_Text_BoarderBradSeen:
    .string "הרצפה במכון הזה חלקה.\p"
    .string "כיף, נכון?\p"
    .string "אבל היי, אנחנו לא כאן\n"
    .string "בשביל משחקים!$"

MahoganyTown_Gym_Text_BoarderBradBeaten:
    .string "אתה רואה כמה אנחנו רציניים?$"

MahoganyTown_Gym_Text_BoarderBradAfter:
    .string "המכון הזה נהדר. אני אוהב לגלוש\n"
    .string "על סנובורד עם הפוקימונים שלי!$"

MahoganyTown_Gym_Text_BoarderDouglasSeen:
    .string "אני יודע את הסוד של פרייס.$"

MahoganyTown_Gym_Text_BoarderDouglasBeaten:
    .string "טוב. אגלה לך את הסוד של פרייס.$"

MahoganyTown_Gym_Text_BoarderDouglasAfter:
    .string "הסוד מאחורי הכוח של פרייס…\p"
    .string "הוא עושה מדיטציה מתחת למפל\n"
    .string "כל יום, כדי לחזק את נפשו ואת גופו.$"

MahoganyTown_Gym_Text_SkierRoxanneSeen:
    .string "כדי להגיע לפרייס, מנהיג המכון שלנו,\n"
    .string "צריך לחשוב לפני שמחליקים.$"

MahoganyTown_Gym_Text_SkierRoxanneBeaten:
    .string "בסקי לא הייתי מפסידה לך!$"

MahoganyTown_Gym_Text_SkierRoxanneAfter:
    .string "מי שלא מחליק בדיוק\n"
    .string "לא יגיע רחוק במכון הזה.$"

MahoganyTown_Gym_Text_SkierClarissaSeen:
    .string "תראה את הפנייה המקבילה שלי!$"

MahoganyTown_Gym_Text_SkierClarissaBeaten:
    .string "לא! בגללך נפלתי!$"

MahoganyTown_Gym_Text_SkierClarissaAfter:
    .string "לא הייתי צריכה להתרברב\n"
    .string "בגלישת הסקי שלי…$"

