ViridianCity_Gym_hns_MapScripts::
	.byte 0

ViridianCity_Gym_EventScript_Blue::
	lock
	faceplayer
	goto_if_unset FLAG_HIDE_DOJO_BLUE, ViridianCity_Gym_EventScript_BlueAtDojo
	goto_if_set FLAG_DEFEATED_VIRIDIAN_GYM, ViridianCity_Gym_EventScript_BlueGotoDojo
	goto_if_set FLAG_DEFEATED_VIRIDIAN_GYM, ViridianCity_Gym_EventScript_Blue_Defeated
	msgbox ViridianCity_Gym_Text_LeaderBlue_Before, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_BLUE_HNS, ViridianCity_Gym_Text_LeaderBlue_Win
	message ViridianCity_Gym_Text_ReceivedEarthBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox ViridianCity_Gym_Text_LeaderBlue_After, MSGBOX_DEFAULT
	msgbox ViridianCity_Gym_Text_LeaderBlue_GiveTM, MSGBOX_DEFAULT
	giveitem ITEM_TM_TRICK_ROOM
	msgbox ViridianCity_Gym_Text_LeaderBlue_ExplainTM, MSGBOX_DEFAULT
	setflag FLAG_BADGE16_GET
	setflag FLAG_DEFEATED_VIRIDIAN_GYM
	addvar VAR_NUM_BADGES, 1
	setvar VAR_0x8008, 16
	call Common_EventScript_SetGymTrainers_hns
	closemessage
	setflag FLAG_HIDE_LEAGUE_BLACKBELT
	setflag FLAG_HIDE_SEAFOAM_BLAINE
	clearflag FLAG_HIDE_CINNABAR_BLAINE
	setvar VAR_OAK_MT_SILVER_CALL, 1
	release
	end

ViridianCity_Gym_EventScript_Blue_Defeated::
	msgbox ViridianCity_Gym_Text_LeaderBlue_Epilogue, MSGBOX_DEFAULT
	closemessage
	release
	end

ViridianCity_Gym_EventScript_BlueGotoDojo::
	msgbox ViridianCity_Gym_Text_BlueGotoDojo, MSGBOX_DEFAULT
	closemessage
	clearflag FLAG_HIDE_DOJO_BLUE
	release
	end

ViridianCity_Gym_Text_BlueGotoDojo:
	.string "בלו: כבר חזרת לעוד?\p"
	.string "אם אתה רוצה עוד הזדמנות נגדי,\n"
	.string "בוא לדוג'ו הלחימה!$"

ViridianCity_Gym_EventScript_BlueAtDojo::
	msgbox ViridianCity_Gym_Text_LeaderBlue_Epilogue, MSGBOX_DEFAULT
	closemessage
	release
	end

ViridianCity_Gym_Text_LeaderBlue_Before:
	.string "בלו: יו! סוף סוף הגעת, מה?\p"
	.string "בסיננבר לא היה לי מצב רוח,\p"
	.string "אבל עכשיו אני מוכן להילחם בך.\p"
	.string "…\p"
	.string "אתה אומר לי שכבשת את כל\n"
	.string "המכונים בג'וטו?\p"
	.string "הה! אז המכונים של ג'וטו בטח\n"
	.string "ממש עלובים.\p"
	.string "היי, אל תדאג.\p"
	.string "אני אדע אם אתה טוב או לא\n"
	.string "כשאלחם בך עכשיו.\p"
	.string "מוכן, אלוף ג'וטו?$"

ViridianCity_Gym_Text_LeaderBlue_Win:
	.string "בלו: מה?\p"
	.string "איך לעזאזל הפסדתי לך?\p"
	.string "…\p"
	.string "אוף, נו טוב… הנה, קח את זה.\n"
	.string "זה תג אדמה.$"

ViridianCity_Gym_Text_ReceivedEarthBadge:
	.string "{PLAYER} קיבל את תג אדמה.$"

ViridianCity_Gym_Text_LeaderBlue_After:
	.string "בלו: …\p"
	.string "נו טוב, טעיתי. אתה באמת תותח.\n"
	.string "אתה מאמן טוב.\p"
	.string "אבל יום אחד אני אנצח אותך.\p"
	.string "אל תשכח את זה!$"

ViridianCity_Gym_Text_LeaderBlue_GiveTM:
	.string "קח את זה איתך.$"

ViridianCity_Gym_Text_LeaderBlue_ExplainTM:
	.string "זה חדר תעלולים.\p"
	.string "כל הפוקימונים בקרב משנים מהירות.\n"
	.string "האיטי פועל ראשון. המהיר - אחרון.\p"
	.string "אפשר להשתמש בו כדי להפוך קרב\n"
	.string "על פיו.$"

ViridianCity_Gym_Text_LeaderBlue_Epilogue:
	.string "בלו: תקשיב לי.\p"
	.string "שלא תעז להפסיד עד שאני אנצח\n"
	.string "אותך. הבנת?$"


ViridianCity_Gym_EventScript_GymGuy::
	goto_if_set FLAG_DEFEATED_VIRIDIAN_GYM, ViridianCity_Gym_EventScript_GymGuyAfter
	msgbox ViridianCity_Gym_Text_Guide, MSGBOX_NPC
	end

ViridianCity_Gym_EventScript_GymGuyAfter::
	msgbox ViridianCity_Gym_Text_Guide_Win, MSGBOX_NPC
	end

ViridianCity_Gym_Text_Guide:
	.string "יו, אלוף לעתיד!\p"
	.string "מה נשמע? נראה שהולך לך\n"
	.string "מצוין.\p"
	.string "מנהיג המכון הוא בחור שנלחם\n"
	.string "באלוף לפני שלוש שנים.\p"
	.string "הוא לא טרף קל.\p"
	.string "תן את כל מה שיש לך!$"

ViridianCity_Gym_Text_Guide_Win:
	.string "וואו, אתה באמת קשוח…\p"
	.string "איזה קרב מעורר השראה!\n"
	.string "זה הביא לי דמעות לעיניים.$"


ViridianCity_Gym_EventScript_GymStatue::
	lockall
	goto_if_set FLAG_BADGE16_GET, ViridianCity_Gym_EventScript_GymStatuePostVictory
	msgbox ViridianCity_Gym_Text_GymStatue
	releaseall
	end

ViridianCity_Gym_EventScript_GymStatuePostVictory::
	msgbox ViridianCity_Gym_Text_GymStatuePlayerWon
	releaseall
	end

ViridianCity_Gym_Text_GymStatue::
    .string "מכון הפוקימון של וירידיאן\n"
    .string "מנהיג: בלו\p"
    .string "מאמנים מנצחים:\n"
    .string "בלו, רד$"

ViridianCity_Gym_Text_GymStatuePlayerWon::
    .string "מכון הפוקימון של וירידיאן\n"
    .string "מנהיג: בלו\p"
    .string "מאמנים מנצחים:\n"
    .string "בלו, רד, {PLAYER}$"

