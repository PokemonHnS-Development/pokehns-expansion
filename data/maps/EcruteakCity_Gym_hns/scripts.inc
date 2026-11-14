EcruteakCity_Gym_hns_MapScripts::
	.byte 0

EcruteakCity_Gym_EventScript_GymGuy::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_ECRUTEAK_CITY_GYM, EcruteakCity_Gym_EventScript_GymGuy2
	msgbox EcruteakCity_GymGuideText, MSGBOX_DEFAULT
	closemessage
	release
	end
	
EcruteakCity_Gym_EventScript_GymGuy2::
	msgbox EcruteakCity_GymGuideWinText, MSGBOX_DEFAULT
	release
	end	

EcruteakCity_Gym_EventScript_Jeffrey::
	trainerbattle_single TRAINER_JEFFREY_HNS, SageJeffreySeenText, SageJeffreyBeatenText
	msgbox SageJeffreyAfterBattleText, MSGBOX_AUTOCLOSE
	end
EcruteakCity_Gym_EventScript_Ping::
	trainerbattle_single TRAINER_PING_HNS, SagePingSeenText, SagePingBeatenText
	msgbox SagePingAfterBattleText, MSGBOX_AUTOCLOSE
	end

EcruteakCity_Gym_EventScript_Martha::
	trainerbattle_single TRAINER_MARTHA_HNS, MediumMarthaSeenText, MediumMarthaBeatenText
	msgbox MediumMarthaAfterBattleText, MSGBOX_AUTOCLOSE
	end

EcruteakCity_Gym_EventScript_Grace::
	trainerbattle_single TRAINER_GRACE_HNS, MediumGraceSeenText, MediumGraceBeatenText
	msgbox MediumGraceAfterBattleText, MSGBOX_AUTOCLOSE
	end

EcruteakCity_Gym_EventScript_Morty::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_ECRUTEAK_CITY_GYM, EcruteakCity_Gym_EventScript_Morty_Defeated
	msgbox MortyIntroText, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_MORTY_1_HNS, MortyWinLossText
	message Text_ReceivedFogBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox MortyText_FogBadgeSpeech, MSGBOX_DEFAULT
	setflag FLAG_BADGE04_GET
	setflag FLAG_DEFEATED_ECRUTEAK_CITY_GYM
	addvar VAR_NUM_BADGES, 1
	setvar VAR_0x8008, 4
	call Common_EventScript_SetGymTrainers_hns
	giveitem ITEM_TM_SHADOW_BALL
	msgbox MortyText_ShadowBallSpeech, MSGBOX_DEFAULT
	setvar VAR_ECRUTEAK_CITY_STATE, 4
	closemessage
	release
	end

EcruteakCity_Gym_EventScript_Morty_Defeated::
	msgbox MortyFightDoneText, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_Gym_EventScript_Statue::
	lock
	goto_if_set FLAG_DEFEATED_ECRUTEAK_CITY_GYM, EcruteakCity_Gym_EventScript_Statue2
	msgbox EcruteakCity_Gym_Text_GymStatue, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_Gym_EventScript_Statue2::
	msgbox EcruteakCity_Gym_Text_GymStatueCertified, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_Gym_Text_GymStatue:
	.string "מכון הפוקימון של העיר אקרוטיק$"

EcruteakCity_Gym_Text_GymStatueCertified:
	.string "מכון הפוקימון של העיר אקרוטיק\p"
	.string "המאמנים המוסמכים של מורטי:\n"
	.string "{PLAYER}$"

MortyIntroText:
	.string "טוב שבאת.\p"
	.string "כאן באקרוטיק, הפוקימונים תמיד\n"
	.string "זכו להערצה.\p"
	.string "אומרים שפוקימון בצבעי הקשת\n"
	.string "ירד ויופיע לפני מאמן אמיתי.\p"
	.string "האמנתי לאגדה הזאת, אז\n"
	.string "התאמנתי כאן בסתר.\p"
	.string "בזכות זה, אני יכול עכשיו לראות\n"
	.string "מה שאחרים לא רואים.\p"
	.string "רק עוד קצת…\p"
	.string "עוד קצת, ואוכל לראות עתיד שבו\n"
	.string "אני פוגש את הפוקימון בצבעי הקשת.\p"
	.string "אתה תעזור לי להגיע\n"
	.string "לרמה הזאת!$"

MortyWinLossText:
	.string "אני עדיין לא מספיק טוב…\p"
	.string "בסדר. התג הזה שלך.$"

Text_ReceivedFogBadge:
	.string "{PLAYER} קיבל את תג ערפל.$"

MortyText_FogBadgeSpeech:
	.string "עם תג ערפל, פוקימונים עד\n"
	.string "רמה 50 יצייתו לך.\p"
	.string "בנוסף, כל פוקימון שיודע גלישה\n"
	.string "יוכל להשתמש בה בכל זמן.\p"
	.string "אני רוצה לתת לך גם את זה.$"

MortyText_ShadowBallSpeech:
	.string "זה כדור צל. הוא גורם נזק\n"
	.string "ועשוי להוריד את ההגנה המיוחדת.\p"
	.string "אפשר להשתמש בו אם הוא מתאים לך.$"

MortyFightDoneText:
	.string "אני מבין…\p"
	.string "המסע שלך לקח אותך\n"
	.string "למקומות רחוקים.\p"
	.string "ראית יותר ממה שאני\n"
	.string "ראיתי אי פעם.\p"
	.string "אני מקנא בך על כך…$"

MortyRematchText:
	.string "Ah, the JOHTO CHAMPION!\n"
	.string "Good of you to come.\p"
	.string "You've shown strength and skill,\n"
	.string "but have you grown since we\l"
	.string "last battled?\p"
	.string "I've trained with my GHOST-type\n"
	.string "POKéMON ever since.\p"
	.string "Let's see if you can overcome\n"
	.string "the shadows again.\p"
	.string "Want to have a rematch?$"

Morty_RematchDefeatText:
	.string "I'm not good enough yet...\p"
	.string "You've witnessed more than I\n"
	.string "ever have.\p"
	.string "I envy you for that...$"

SageJeffreySeenText:
	.string "את האביב ביליתי עם\n"
	.string "הפוקימונים שלי.\p"
	.string "אחר כך קיץ, סתיו וחורף…\p"
	.string "ואז שוב הגיע האביב.\n"
	.string "אנחנו ביחד כבר הרבה זמן.$"

SageJeffreyBeatenText:
	.string "ניצחונות והפסדים - הכרתי\n"
	.string "את שניהם.$"

SageJeffreyAfterBattleText:
	.string "מאיפה הגיעו הפוקימונים?$"

SagePingSeenText:
	.string "תצליח לגרום נזק כלשהו\n"
	.string "לפוקימונים שלנו?$"

SagePingBeatenText:
	.string "אה! כל הכבוד!$"

SagePingAfterBattleText:
	.string "אנחנו משתמשים בפוקימונים מסוג רפאים.\p"
	.string "שום התקפה מסוג רגיל לא יכולה\n"
	.string "לפגוע בהם!$"

MediumMarthaSeenText:
	.string "אני אנצח!$"

MediumMarthaBeatenText:
	.string "אני… אני… הפסדתי!$"

MediumMarthaAfterBattleText:
	.string "מי שהכי רוצה לנצח\n"
	.string "הוא זה שינצח!$"

MediumGraceSeenText:
	.string "המסדרונות החשוכים שלנו מבלבלים אותך?\n"
	.string "מי שרוצה רמז, צריך לנצח אותי!$"

MediumGraceBeatenText:
	.string "מ-מה?$"

MediumGraceAfterBattleText:
	.string "טוב. אגלה לך את הסוד\n"
	.string "של הצללים.\p"
	.string "השביל נמצא ממש מול\n"
	.string "העיניים שלך!$"

EcruteakCity_GymGuideText:
	.string "היי, אלוף! כבר כמעט\n"
	.string "הגעת לחצי הדרך!\p"
	.string "המאמנים כאן משתמשים בפוקימונים\n"
	.string "מסוג רפאים ומסוג אפל.\p"
	.string "מורטי אמנם מומחה לסוג רפאים, אבל\n"
	.string "כדאי להיזהר מהצבי המיסטי שלו.\p"
	.string "אומרים שהוא גורם לסיוטים\n"
	.string "מוזרים…$"

EcruteakCity_GymGuideWinText:
	.string "פיו, {PLAYER}. עשית עבודה מצוינת!\p"
	.string "אני התכווצתי בפינה\n"
	.string "מרוב אימה!$"

EcruteakCity_GymClosedText:
	.string "MORTY, the GYM LEADER, is\n"
	.string "absent.\p"
	.string "Sorry, but you'll have to\n"
	.string "leave.\p"
	.string "Hohohoho.$"
