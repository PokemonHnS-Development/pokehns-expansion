CeladonCity_Gym_hns_MapScripts::
	.byte 0


CeladonCity_Gym_EventScript_Erika::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_CELADON_GYM, CeladonCity_Gym_EventScript_Erika_Defeated
	msgbox CeladonCity_Gym_Text_ErikaBeforeBattle, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_ERIKA_HNS, CeladonCity_Gym_Text_ErikaBeaten
	message CeladonCity_Gym_Text_PlayerReceivedRainbowBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox CeladonCity_Gym_Text_Erika_GiveTM, MSGBOX_DEFAULT
	giveitem ITEM_TM_GIGA_DRAIN
	msgbox CeladonCity_Gym_Text_Erika_ExplainTM, MSGBOX_DEFAULT
	setflag FLAG_BADGE12_GET
	setflag FLAG_DEFEATED_CELADON_GYM
	addvar VAR_NUM_BADGES, 1
	setvar VAR_0x8008, 12
	call Common_EventScript_SetGymTrainers_hns
	clearflag FLAG_HIDE_FOUNTAIN_ERIKA
	closemessage
	release
	end

CeladonCity_Gym_EventScript_Erika_Defeated::
	msgbox CeladonCity_Gym_Text_ErikaAfterBattle, MSGBOX_DEFAULT
	closemessage
	release
	end

CeladonCity_Gym_Text_ErikaBeforeBattle:
	.string "אריקה: שלום… מזג אוויר נהדר,\n"
	.string "נכון? כל כך נעים…\p"
	.string "…אני חוששת שאני עלולה להירדם…\p"
	.string "שמי אריקה. אני מנהיגת\n"
	.string "מכון סלדון.\p"
	.string "…אה? הגעת עד לכאן מג'וטו?\n"
	.string "כמה נחמד…\p"
	.string "אה. סליחה, לא הבנתי\n"
	.string "שרצית לאתגר אותי.\p"
	.string "טוב מאוד, אבל אני לא אפסיד.$"

CeladonCity_Gym_Text_ErikaBeaten:
	.string "אריקה: הו! אני מודה בתבוסה…\p"
	.string "אתה חזק להפליא…\p"
	.string "אעניק לך את תג קשת…$"

CeladonCity_Gym_Text_PlayerReceivedRainbowBadge:
	.string "{PLAYER} קיבל את תג קשת.$"

CeladonCity_Gym_Text_Erika_GiveTM:
	.string "אריקה: זה היה קרב מקסים.\p"
	.string "קיבלתי השראה. בבקשה,\n"
	.string "אני רוצה שהמ”מ הזה יהיה שלך.$"

CeladonCity_Gym_Text_Erika_ExplainTM:
	.string "זה המהלך יניקת ענק.\p"
	.string "זה מהלך נפלא: חצי מהנזק שהוא\n"
	.string "גורם נשאב ומרפא את הפוקימון שלך.\p"
	.string "בבקשה, השתמש בו אם תרצה…$"

CeladonCity_Gym_Text_ErikaAfterBattle:
	.string "אריקה: הפסד משאיר טעם מר…\p"
	.string "אבל הידיעה שיש מאמנים חזקים\n"
	.string "דוחפת אותי להשתפר…$"

CeladonCity_Gym_Text_ErikaRematch:
	.string "ERIKA: Oh, hello.\p"
	.string "What a surprise, KANTO CHAMPION!\p"
	.string "It's so lovely to see you again.\p"
	.string "Your journey must have been so\n"
	.string "exciting.\p"
	.string "Even champions enjoy a challenge.\p"
	.string "Want to have a rematch with me?$"

CeladonCity_Gym_Text_ErikaRematchDefeat:
	.string "ERIKA: Losing still leaves a\n"
	.string "bitter aftertaste…\p"
	.string "But knowing that there are strong\n"
	.string "trainers spurs me to do better…$"

CeladonCity_Gym_EventScript_Michelle::
	trainerbattle_single TRAINER_MICHELLE_HNS, CeladonCity_Gym_Text_LassMichelleSeen, CeladonCity_Gym_Text_LassMichelleBeaten
	msgbox CeladonCity_Gym_Text_LassMichelleAfter, MSGBOX_AUTOCLOSE
	end

CeladonCity_Gym_Text_LassMichelleSeen:
	.string "אתה חושב שמכון לבנות בלבד\n"
	.string "זה דבר נדיר?$"

CeladonCity_Gym_Text_LassMichelleBeaten:
	.string "אוף, איכס!$"

CeladonCity_Gym_Text_LassMichelleAfter:
	.string "פשוט הייתי רשלנית, זה הכל!$"


CeladonCity_Gym_EventScript_Tanya::
	trainerbattle_single TRAINER_TANYA_HNS, CeladonCity_Gym_Text_PicnickerTanyaSeen, CeladonCity_Gym_Text_PicnickerTanyaBeaten
	msgbox CeladonCity_Gym_Text_PicnickerTanyaAfter, MSGBOX_AUTOCLOSE
	end

CeladonCity_Gym_Text_PicnickerTanyaSeen:
	.string "אה, קרב? זה קצת מפחיד,\n"
	.string "אבל בסדר!$"

CeladonCity_Gym_Text_PicnickerTanyaBeaten:
	.string "אה, זהו?$"

CeladonCity_Gym_Text_PicnickerTanyaAfter:
	.string "אה, תראה כמה תגים יש לך.\n"
	.string "אין פלא שלא הצלחתי לנצח!$"

CeladonCity_Gym_EventScript_Julia::
	trainerbattle_single TRAINER_JULIA_HNS, CeladonCity_Gym_Text_BeautyJuliaSeen, CeladonCity_Gym_Text_BeautyJuliaBeaten
	msgbox CeladonCity_Gym_Text_BeautyJuliaAfter, MSGBOX_AUTOCLOSE
	end

CeladonCity_Gym_Text_BeautyJuliaSeen:
	.string "הסתכלת על הפרחים האלה\n"
	.string "או עליי?$"

CeladonCity_Gym_Text_BeautyJuliaBeaten:
	.string "כמה מעצבן!$"

CeladonCity_Gym_Text_BeautyJuliaAfter:
	.string "איך אני הופכת\n"
	.string "לגברת מעודנת כמו אריקה?$"

CeladonCity_Gym_EventScript_Jo::
	trainerbattle_double TRAINER_JO_AND_ZOE_HNS, CeladonCity_Gym_Text_TwinsJoAndZoe1Seen, CeladonCity_Gym_Text_TwinsJoAndZoe1Beaten, Route104_Text_GinaNotEnoughMons
	special GetPlayerBigGuyGirlString
	msgbox CeladonCity_Gym_Text_TwinsJoAndZoe1After, MSGBOX_AUTOCLOSE
	end

CeladonCity_Gym_EventScript_Zoe::
	trainerbattle_double TRAINER_JO_AND_ZOE_HNS, CeladonCity_Gym_Text_TwinsJoAndZoe2Seen, CeladonCity_Gym_Text_TwinsJoAndZoe2Beaten, Route104_Text_GinaNotEnoughMons
	msgbox CeladonCity_Gym_Text_TwinsJoAndZoe2After, MSGBOX_AUTOCLOSE
	end

CeladonCity_Gym_Text_TwinsJoAndZoe1Seen:
	.string "נראה לך מהלכי פוקימון\n"
	.string "שאריקה לימדה אותנו!$"

CeladonCity_Gym_Text_TwinsJoAndZoe1Beaten:
	.string "אוי… הפסדנו…$"

CeladonCity_Gym_Text_TwinsJoAndZoe1After:
	.string "אריקה תנקום בך בשבילנו!$"

CeladonCity_Gym_Text_TwinsJoAndZoe2Seen:
	.string "אנחנו נגן על אריקה!$"

CeladonCity_Gym_Text_TwinsJoAndZoe2Beaten:
	.string "לא הצלחנו לנצח…$"

CeladonCity_Gym_Text_TwinsJoAndZoe2After:
	.string "אריקה הרבה, הרבה יותר חזקה!$"

CeladonCity_Gym_EventScript_GymStatue::
	lockall
	goto_if_set FLAG_BADGE12_GET, CeladonCity_Gym_EventScript_GymStatuePostVictory
	msgbox CeladonCity_Gym_Text_GymStatue
	releaseall
	end

CeladonCity_Gym_EventScript_GymStatuePostVictory::
	msgbox CeladonCity_Gym_Text_GymStatuePlayerWon
	releaseall
	end

CeladonCity_Gym_Text_GymStatue::
    .string "מכון הפוקימון של סלדון\n"
    .string "מנהיגה: אריקה\p"
    .string "מאמנים מנצחים:\n"
    .string "בלו, רד$"

CeladonCity_Gym_Text_GymStatuePlayerWon::
    .string "מכון הפוקימון של סלדון\n"
    .string "מנהיגה: אריקה\p"
    .string "מאמנים מנצחים:\n"
    .string "בלו, רד, {PLAYER}$"
