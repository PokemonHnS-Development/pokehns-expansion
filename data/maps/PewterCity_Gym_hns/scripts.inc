PewterCity_Gym_hns_MapScripts::
	.byte 0



PewterCity_Gym_EventScript_Jerry::
	trainerbattle_single TRAINER_JERRY_HNS, PewterCity_Gym_Text_CamperJerry_Seen, PewterCity_Gym_Text_CamperJerry_Beaten
	msgbox PewterCity_Gym_Text_CamperJerry_AfterBattle, MSGBOX_AUTOCLOSE
	end

PewterCity_Gym_EventScript_Brock::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_PEWTER_GYM, PewterCity_Gym_EventScript_Brock_Defeated
	msgbox PewterCity_Gym_Text_Brock_Intro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_BROCK_HNS, PewterCity_Gym_Text_Brock_WinLoss
	message PewterCity_Gym_Text_ReceivedBoulderBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox PewterCity_Gym_Text_Brock_GiveTM, MSGBOX_DEFAULT
	giveitem ITEM_TM_ROCK_SLIDE
	msgbox PewterCity_Gym_Text_Brock_ExplainTM, MSGBOX_DEFAULT
	setflag FLAG_BADGE09_GET
	setflag FLAG_DEFEATED_PEWTER_GYM
	addvar VAR_NUM_BADGES, 1
	setvar VAR_0x8008, 9
	call Common_EventScript_SetGymTrainers_hns
	clearflag FLAG_HIDE_DIGLETT_BROCK
	closemessage
	release
	end

PewterCity_Gym_EventScript_Brock_Defeated::
	goto_if_unset FLAG_HIDE_DOJO_BROCK, PewterCity_Gym_EventScript_Brock_Trade
	msgbox PewterCity_Gym_Text_Brock_FightDone, MSGBOX_DEFAULT
	closemessage
	release
	end


PewterCity_Gym_Text_Brock_Intro:
	.string "ברוק: וואו, לא כל יום מגיע\n"
	.string "אלינו מתמודד מג'וטו.\p"
	.string "אני ברוק, מנהיג המכון של פיוטר.\p"
	.string "אני מומחה לפוקימונים מסוג סלע.\p"
	.string "הפוקימונים שלי חסינים לרוב ההתקפות\n"
	.string "הפיזיות. יהיה לך קשה לפגוע בהם בכלל.\p"
	.string "קדימה!$"

PewterCity_Gym_Text_Brock_WinLoss:
	.string "ברוק: ההתקפות החזקות של הפוקימונים\n"
	.string "שלך התגברו על ההגנה שלי, הקשה כסלע…\p"
	.string "אתה חזק יותר משציפיתי…\p"
	.string "קדימה - קח את התג הזה.$"

PewterCity_Gym_Text_ReceivedBoulderBadge:
	.string "{PLAYER} קיבל את תג סלע.$"

PewterCity_Gym_Text_Brock_GiveTM:
	.string "הנה, קח איתך את המ”מ הזה.$"

PewterCity_Gym_Text_Brock_ExplainTM:
	.string "הוא מכיל את מפולת סלע.\p"
	.string "הוא מפיל סלעים על היריבים, עם\n"
	.string "סיכוי לגרום להם להירתע.\p"
	.string "אפשר להשתמש בו כדי לעצור אותם\n"
	.string "על המקום.$"

PewterCity_Gym_Text_Brock_BoulderBadge:
	.string "BROCK: {PLAYER}, thanks. I enjoyed\n"
	.string "battling you, even though I am a bit\l"
	.string "upset.\p"
	.string "That BOULDERBADGE will make your\n"
	.string "POKéMON even more powerful.$"

PewterCity_Gym_Text_Brock_FightDone:
	.string "ברוק: העולם ענק. יש עוד\n"
	.string "הרבה מאמנים חזקים כמוך.\p"
	.string "חכה ותראה. גם אני הולך\n"
	.string "להיות הרבה יותר חזק.$"

PewterCity_Gym_Text_CamperJerry_Seen:
	.string "המאמנים במכון הזה משתמשים\n"
	.string "בפוקימונים מסוג סלע.\p"
	.string "לסוג סלע יש הגנה גבוהה.\p"
	.string "הקרבות עלולים להימשך הרבה זמן.\n"
	.string "אתה מוכן לזה?$"

PewterCity_Gym_Text_CamperJerry_Beaten:
	.string "אני חייב לנצח בקרבות האלה…$"

PewterCity_Gym_Text_CamperJerry_AfterBattle:
	.string "היי, אתה! המאמן מג'וטו!\p"
	.string "ברוק קשוח. הוא יעניש אותך\n"
	.string "אם לא תתייחס אליו ברצינות.$"

PewterCity_Gym_Text_Guide:
	.string "יו! אלוף לעתיד! אתה ממש סלע!\p"
	.string "אתה נלחם במנהיגי המכונים של\n"
	.string "קאנטו?\p"
	.string "הם אנשים חזקים ומסורים, בדיוק\n"
	.string "כמו מנהיגי המכונים של ג'וטו.$"

PewterCity_Gym_Text_Guide_Win:
	.string "יו! אלוף לעתיד! המכון הזה\n"
	.string "לא עשה לך הרבה בעיות.\p"
	.string "הדרך שבה לקחת פיקוד ממש עוררה\n"
	.string "השראה. אני אומר את זה ברצינות.$"

PewterCity_Gym_EventScript_GymGuy::
	goto_if_set FLAG_DEFEATED_PEWTER_GYM, PewterCity_Gym_EventScript_GymGuyAfter
	msgbox PewterCity_Gym_Text_Guide, MSGBOX_NPC
	end

PewterCity_Gym_EventScript_GymGuyAfter::
	msgbox PewterCity_Gym_Text_Guide_Win, MSGBOX_NPC
	end


PewterCity_Gym_EventScript_GymStatue::
	lockall
	goto_if_set FLAG_BADGE09_GET, PewterCity_Gym_EventScript_GymStatuePostVictory
	msgbox PewterCity_Gym_Text_GymStatue
	releaseall
	end

PewterCity_Gym_EventScript_GymStatuePostVictory::
	msgbox PewterCity_Gym_Text_GymStatuePlayerWon
	releaseall
	end

PewterCity_Gym_Text_GymStatue::
    .string "מכון הפוקימון של פיוטר\n"
    .string "מנהיג: ברוק\p"
    .string "מאמנים מנצחים:\n"
    .string "בלו, רד$"

PewterCity_Gym_Text_GymStatuePlayerWon::
    .string "מכון הפוקימון של פיוטר\n"
    .string "מנהיג: ברוק\p"
    .string "מאמנים מנצחים:\n"
    .string "בלו, רד, {PLAYER}$"

PewterCity_Gym_EventScript_Brock_Trade::
	goto_if_set FLAG_PEWTER_GYM_NPC_TRADE_COMPLETED, PewterCity_Gym_EventScript_BrockTradeCompleted
	ingame_trade INGAME_TRADE_BONSLY, PewterCity_Gym_Text_BrockWantToTrade, PewterCity_Gym_EventScript_BrockDeclineTrade, PewterCity_Gym_EventScript_BrockNotRequestedMon, PewterCity_Gym_Text_BrockTakeCare
	setflag FLAG_PEWTER_GYM_NPC_TRADE_COMPLETED
	release
	end

PewterCity_Gym_EventScript_BrockDeclineTrade::
	msgbox PewterCity_Gym_Text_BrockDeclineTrade, MSGBOX_DEFAULT
	release
	end

PewterCity_Gym_EventScript_BrockNotRequestedMon::
	bufferspeciesname STR_VAR_1, VAR_0x8009
	msgbox PewterCity_Gym_Text_BrockNotRequestedMon, MSGBOX_DEFAULT
	release
	end

PewterCity_Gym_EventScript_BrockTradeCompleted::
	msgbox PewterCity_Gym_Text_BrockTradeCompleted, MSGBOX_DEFAULT
	release
	end

PewterCity_Gym_Text_BrockWantToTrade:
	.string "ברוק: היי, {PLAYER}.\p"
	.string "מצאתי את הבונסליי הקטן הזה\n"
	.string "כשהתאמנתי בהרים.\p"
	.string "הוא חמוד, אבל אני חושב שהוא\n"
	.string "צריך מאמן מסוג אחר.\p"
	.string "תסכים לתת לי {STR_VAR_1}\n"
	.string "בתמורה ל{STR_VAR_2} שלי?$"

PewterCity_Gym_Text_BrockTakeCare:
	.string "ברוק: תודה! תשמור היטב על\n"
	.string "וודי בשבילי!$"

PewterCity_Gym_Text_BrockDeclineTrade:
	.string "ברוק: לא? זה בסדר.\n"
	.string "וודי ואני נמשיך להתאמן.$"

PewterCity_Gym_Text_BrockNotRequestedMon:
	.string "ברוק: זה לא {STR_VAR_1}.\n"
	.string "זה לא מה שאני מחפש.$"

PewterCity_Gym_Text_BrockTradeCompleted:
	.string "ברוק: מה שלום וודי?\n"
	.string "בונסליי קשוחים יותר ממה שהם נראים!$"
