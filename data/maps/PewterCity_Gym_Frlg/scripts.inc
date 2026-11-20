PewterCity_Gym_Frlg_MapScripts::
	.byte 0

PewterCity_Gym_EventScript_Brock::
	famechecker FAMECHECKER_BROCK, FCPICKSTATE_COLORED, UpdatePickStateFromSpecialVar8005
	trainerbattle_single TRAINER_LEADER_BROCK, PewterCity_Gym_Text_BrockIntro, PewterCity_Gym_Text_BrockDefeat, PewterCity_Gym_EventScript_DefeatedBrock, NO_MUSIC
	goto_if_unset FLAG_GOT_TM39_FROM_BROCK, PewterCity_Gym_EventScript_GiveTM39
	msgbox PewterCity_Gym_Text_BrockPostBattle
	release
	end

PewterCity_Gym_EventScript_DefeatedBrock::
	famechecker FAMECHECKER_BROCK, 1
	setflag FLAG_DEFEATED_BROCK
	setflag FLAG_BADGE01_GET
	setvar VAR_MAP_SCENE_PEWTER_CITY, 1
	setflag FLAG_HIDE_PEWTER_CITY_GYM_GUIDE
	clearflag FLAG_HIDE_PEWTER_CITY_RUNNING_SHOES_GUY
	set_gym_trainers_frlg 1
	goto PewterCity_Gym_EventScript_GiveTM39
	end

PewterCity_Gym_EventScript_GiveTM39::
	msgbox PewterCity_Gym_Text_TakeThisWithYou
	checkitemspace ITEM_TM39
	goto_if_eq VAR_RESULT, FALSE, PewterCity_Gym_EventScript_NoRoomForTM39
	giveitem_msg PewterCity_Gym_Text_ReceivedTM39FromBrock, ITEM_TM39
	setflag FLAG_GOT_TM39_FROM_BROCK
	msgbox PewterCity_Gym_Text_ExplainTM39
	release
	end

PewterCity_Gym_EventScript_NoRoomForTM39::
	msgbox PewterCity_Gym_Text_DontHaveRoomForThis
	release
	end

PewterCity_Gym_EventScript_Liam::
	trainerbattle_single TRAINER_CAMPER_LIAM, PewterCity_Gym_Text_LiamIntro, PewterCity_Gym_Text_LiamDefeat
	msgbox PewterCity_Gym_Text_LiamPostBattle, MSGBOX_AUTOCLOSE
	end

PewterCity_Gym_EventScript_GymGuy::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_BROCK, PewterCity_Gym_EventScript_GymGuyPostVictory
	msgbox PewterCity_Gym_Text_LetMeTakeYouToTheTop, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, PewterCity_Gym_EventScript_GymGuyTakeMeToTop
	goto_if_eq VAR_RESULT, NO, PewterCity_Gym_EventScript_GymGuyDontTakeMeToTop
	end

PewterCity_Gym_EventScript_GymGuyPostVictory::
	msgbox PewterCity_Gym_Text_YoureChampMaterial
	release
	end

PewterCity_Gym_EventScript_GymGuyTakeMeToTop::
	msgbox PewterCity_Gym_Text_LetsGetHappening
	goto PewterCity_Gym_EventScript_GymGuyAdvice
	end

PewterCity_Gym_EventScript_GymGuyDontTakeMeToTop::
	msgbox PewterCity_Gym_Text_ItsFreeLetsGetHappening
	goto PewterCity_Gym_EventScript_GymGuyAdvice
	end

PewterCity_Gym_EventScript_GymGuyAdvice::
	msgbox PewterCity_Gym_Text_TryDifferentPartyOrders
	release
	end

PewterCity_Gym_EventScript_GymStatue::
	lockall
	goto_if_set FLAG_BADGE01_GET, PewterCity_Gym_EventScript_GymStatuePostVictory
	msgbox PewterCity_Gym_Text_GymStatue
	releaseall
	end

PewterCity_Gym_EventScript_GymStatuePostVictory::
	msgbox PewterCity_Gym_Text_GymStatuePlayerWon
	releaseall
	end

PewterCity_Gym_Text_BrockIntro::
	.string "אז הגעת. אני ברוק.\n"
	.string "אני מנהיג המכון של פיוטר.\p"
	.string "כוח הרצון שלי, קשה כסלע, ניכר\n"
	.string "אפילו בפוקימונים שלי.\p"
	.string "כל הפוקימונים שלי קשים כסלע,\n"
	.string "ויש להם נחישות של ברזל.\p"
	.string "נכון - כל הפוקימונים שלי\n"
	.string "מסוג סלע!\p"
	.string "פוהאהא! אתה בא לאתגר אותי\n"
	.string "למרות שאתה יודע שתפסיד?\p"
	.string "זה כבוד המאמנים שדוחף אותך\n"
	.string "לאתגר אותי.\p"
	.string "טוב מאוד!\n"
	.string "הראה לי את המיטב שלך!{PLAY_BGM}{MUS_RG_ENCOUNTER_GYM_LEADER}$"

PewterCity_Gym_Text_BrockDefeat::
	.string "לא לקחתי אותך ברצינות, ולכן\n"
	.string "הפסדתי.\p"
	.string "כהוכחה לניצחונך, אני מעניק לך\n"
	.string "את זה…\p"
	.string "את תג הסלע הרשמי של\n"
	.string "ליגת הפוקימון.\p"
	.string "{FONT_NORMAL}{PLAYER} קיבל את תג הסלע\n"
	.string "מברוק!{PAUSE_MUSIC}{PLAY_BGM}{MUS_OBTAIN_BADGE}{PAUSE 0xFE}{PAUSE 0x56}{RESUME_MUSIC}\p"
	.string "{FONT_MALE}עצם ההחזקה בתג הסלע הופכת\n"
	.string "את הפוקימונים שלך לחזקים יותר.\p"
	.string "התג גם מאפשר להשתמש במהלך\n"
	.string "הבזק מחוץ לקרב.\p"
	.string "כמובן, פוקימון חייב לדעת את המהלך\n"
	.string "הבזק כדי להשתמש בו.$"

PewterCity_Gym_Text_TakeThisWithYou::
	.string "רגע!\n"
	.string "קח את זה איתך.$"

PewterCity_Gym_Text_ReceivedTM39FromBrock::
	.string "{PLAYER} קיבל את מ”מ 39\n"
	.string "מברוק.$"

PewterCity_Gym_Text_ExplainTM39::
	.string "מ”מ, מכונת מהלך, מכיל טכניקה\n"
	.string "לפוקימונים.\p"
	.string "שימוש במ”מ מלמד פוקימון את\n"
	.string "המהלך שהוא מכיל.\p"
	.string "כל מ”מ טוב לשימוש אחד בלבד.\p"
	.string "לכן, כשמשתמשים באחד, כדאי\n"
	.string "לבחור את הפוקימון בקפידה.\p"
	.string "בכל אופן…\n"
	.string "מ”מ 39 מכיל את קבר סלע.\p"
	.string "הוא משליך סלעים על היריב\n"
	.string "ומוריד את המהירות שלו.$"

PewterCity_Gym_Text_BrockPostBattle::
	.string "יש כל מיני מאמנים בעולם\n"
	.string "הענק שלנו.\p"
	.string "נראה שיש לך כישרון רב\n"
	.string "כמאמן פוקימונים.\p"
	.string "אז תרשה לי להציע משהו.\p"
	.string "לך למכון בסרוליאן ותבחן\n"
	.string "את היכולות שלך.$"

PewterCity_Gym_Text_DontHaveRoomForThis::
	.string "אין לך מקום לזה.$"

PewterCity_Gym_Text_LiamIntro::
	.string "Stop right there, kid!\p"
	.string "You're ten thousand light-years \n"
	.string "from facing BROCK!$"

PewterCity_Gym_Text_LiamDefeat::
	.string "Darn!\p"
	.string "Light-years isn't time…\n"
	.string "It measures distance!$"

PewterCity_Gym_Text_LiamPostBattle::
	.string "You're pretty hot.\n"
	.string "…But not as hot as BROCK!$"

PewterCity_Gym_Text_LetMeTakeYouToTheTop::
	.string "היי!\n"
	.string "רוצה לחלום בגדול?\p"
	.string "אתה מעז לחלום להיות\n"
	.string "אלוף הפוקימונים?\p"
	.string "אני לא מאמן, אבל אני יכול לייעץ\n"
	.string "לך איך לנצח.\p"
	.string "תן לי לקחת אותך לפסגה!$"

PewterCity_Gym_Text_LetsGetHappening::
	.string "בסדר גמור!\n"
	.string "בוא נצא לדרך!$"

PewterCity_Gym_Text_TryDifferentPartyOrders::
	.string "הפוקימון שיוצא ראשון לקרב הוא זה\n"
	.string "שבצד שמאל של רשימת הפוקימונים.\p"
	.string "שינוי סדר הפוקימונים יכול\n"
	.string "לתת לך יתרון.\p"
	.string "נסה סדרים שונים שיתאימו\n"
	.string "לקבוצה של היריב.$"

PewterCity_Gym_Text_ItsFreeLetsGetHappening::
	.string "זה שירות חינמי!\n"
	.string "בוא נצא לדרך!$"

PewterCity_Gym_Text_YoureChampMaterial::
	.string "בדיוק כמו שחשבתי!\n"
	.string "יש בך חומר של אלוף פוקימונים!$"

PewterCity_Gym_Text_GymStatue::
	.string "מכון הפוקימון של פיוטר\n"
	.string "מנהיג: ברוק\p"
	.string "מאמנים מנצחים:\n"
	.string "{RIVAL}$"

PewterCity_Gym_Text_GymStatuePlayerWon::
	.string "מכון הפוקימון של פיוטר\n"
	.string "מנהיג: ברוק\p"
	.string "מאמנים מנצחים:\n"
	.string "{RIVAL}, {PLAYER}$"

