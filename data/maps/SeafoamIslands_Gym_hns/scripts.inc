SeafoamIslands_Gym_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SeafoamIslands_Gym_OnTransition
	.byte 0

SeafoamIslands_Gym_OnTransition: 
	setflag FLAG_TEMP_1
	end

SeafoamIslands_Gym_EventScript_Blaine::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_CINNABAR_ISLAND_GYM, SeafoamIslands_Gym_EventScript_Blaine_Defeated
	msgbox SeafoamIslands_Gym_Text_BlaineIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_BLAINE_HNS, SeafoamIslands_Gym_Text_BlaineWinLoss
	message SeafoamIslands_Gym_Text_ReceivedVolcanoBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox SeafoamIslands_Gym_Text_Blaine_GiveTM, MSGBOX_DEFAULT
	giveitem ITEM_TM_OVERHEAT
	msgbox SeafoamIslands_Gym_Text_Blaine_ExplainTM, MSGBOX_DEFAULT
	setflag FLAG_BADGE15_GET
	setflag FLAG_DEFEATED_CINNABAR_ISLAND_GYM
	addvar VAR_NUM_BADGES, 1
	setvar VAR_0x8008, 15
	clearflag FLAG_HIDE_SEAFOAM_GYMGUY
	call Common_EventScript_SetGymTrainers_hns
	closemessage
	release
	end

SeafoamIslands_Gym_EventScript_Blaine_Defeated::
	msgbox SeafoamIslands_Gym_Text_BlaineAfterBattle, MSGBOX_DEFAULT
	closemessage
	release
	end

SeafomIslands2_EventScript_GymGuide::
	goto_if_set FLAG_TEMP_2, SeafomIslands2_EventScript_GymGuide2
	msgbox SeafoamIslands_Gym_Text_GymGuideWin, MSGBOX_NPC
	setflag FLAG_TEMP_2
	end
SeafomIslands2_EventScript_GymGuide2::
	msgbox SeafoamIslands_Gym_Text_GymGuideWin2, MSGBOX_NPC
	end

SeafoamIslands_Gym_EventScript_GymStatue::
	lockall
	goto_if_set FLAG_BADGE15_GET, SeafoamIslands_Gym_EventScript_GymStatuePostVictory
	msgbox SeafoamIslands_Gym_Text_GymStatue
	releaseall
	end

SeafoamIslands_Gym_EventScript_GymStatuePostVictory::
	msgbox SeafoamIslands_Gym_Text_GymStatuePlayerWon
	releaseall
	end

SeafoamIslands_Gym_Text_GymStatue::
    .string "מכון הפוקימון של סיננבר\n"
    .string "מנהיג: בליין\p"
    .string "מאמנים מנצחים:\n"
    .string "בלו, רד$"

SeafoamIslands_Gym_Text_GymStatuePlayerWon::
    .string "מכון הפוקימון של סיננבר\n"
    .string "מנהיג: בליין\p"
    .string "מאמנים מנצחים:\n"
    .string "בלו, רד, {PLAYER}$"

SeafoamIslands_Gym_Text_Blaine_GiveTM:
	.string "קח גם את זה!$"

SeafoamIslands_Gym_Text_Blaine_ExplainTM:
	.string "המ”מ הזה מכיל את המהלך\n"
	.string "המדהים חום יתר!\p"
	.string "החום העצום חורך את היריבים,\n"
	.string "אבל אז הכוח שלך יורד.\p"
	.string "אני מקווה שליריב הבא שלך תהיה\n"
	.string "עוד תרופה לכוויות! וואההה!$"

SeafoamIslands_Gym_Text_BlaineIntro:
	.string "בליין: וואההה!\p"
	.string "המכון שלי בסיננבר עלה באש.\p"
	.string "אני והפוקימונים יורקי האש שלי\n"
	.string "נשארנו בלי בית בגלל הר הגעש.\p"
	.string "וואההה!\p"
	.string "אבל חזרתי לעניינים כמנהיג מכון,\n"
	.string "כאן במערה הזאת.\p"
	.string "אם תנצח אותי, אתן לך תג.\p"
	.string "הה! כדאי שתהיה לך\n"
	.string "תרופה לכוויות!$"

SeafoamIslands_Gym_Text_BlaineWinLoss:
	.string "בליין: מדהים. האש שלי כבתה…\p"
	.string "הרווחת את תג הר געש!$"

SeafoamIslands_Gym_Text_ReceivedVolcanoBadge:
	.string "{PLAYER} קיבל את תג הר געש.$"

SeafoamIslands_Gym_Text_BlaineAfterBattle:
	.string "בליין: הפעם אמנם הפסדתי, אבל\n"
	.string "בפעם הבאה אני אנצח.\p"
	.string "כשאבנה מחדש את מכון סיננבר,\n"
	.string "נצטרך לערוך קרב חוזר.$"

SeafoamIslands_Gym_Text_BlaineFightDone:
	.string "BLAINE: My fire POKéMON will be\n"
	.string "even stronger.\p"
	.string "Just you watch!$"

SeafoamIslands_Gym_Text_BlaineRematch:
	.string "BLAINE: Whoa!\p"
	.string "I see you've become the KANTO\n"
	.string "CHAMPION!\p"
	.string "That's blazing!\p"
	.string "Your skills are top-notch.\p"
	.string "I'm always up for a battle.\p"
	.string "Want to have a rematch with me?$"

SeafoamIslands_Gym_Text_BlaineRematchDefeat:
	.string "BLAINE: Your skills are truly fiery!\p"
	.string "You've burned right through my\n"
	.string "defenses.$"

SeafoamIslands_Gym_Text_GymGuideWin:
	.string "יו!\p"
	.string "… מה? זה כבר נגמר?\p"
	.string "סליחה, סליחה!\p"
	.string "מכון סיננבר נעלם, אז לא ידעתי\n"
	.string "איפה למצוא אותך.\p"
	.string "אבל היי, אתה חזק מספיק גם\n"
	.string "בלי העצות שלי. ידעתי שתנצח!$"

SeafoamIslands_Gym_Text_GymGuideWin2:
	.string "מכון פוקימון יכול להיות בכל מקום,\n"
	.string "כל עוד מנהיג המכון נמצא שם.\p"
	.string "אין צורך בבניין.$"
