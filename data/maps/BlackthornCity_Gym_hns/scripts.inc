BlackthornCity_Gym_hns_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, BlackthornGym_OnLoad
	.byte 0

BlackthornGym_OnLoad::
	call_if_eq VAR_BLACKTHORN_GYM_STATE, 1, BlackthornGym_MapScript_Var1
	call_if_eq VAR_BLACKTHORN_GYM_STATE, 2, BlackthornGym_MapScript_Var2
	call_if_eq VAR_BLACKTHORN_GYM_STATE, 3, BlackthornGym_MapScript_Var3
	call_if_eq VAR_BLACKTHORN_GYM_STATE, 4, BlackthornGym_MapScript_Var4
	end

BlackthornGym_MapScript_Var1::
	call BlackthornGym_MapScript_BuildBridge1
	end

BlackthornGym_MapScript_Var2::
	call BlackthornGym_MapScript_BuildBridge1
	call BlackthornGym_MapScript_BuildBridge2
	end

BlackthornGym_MapScript_Var3::
	call BlackthornGym_MapScript_BuildBridge1
	call BlackthornGym_MapScript_BuildBridge2
	call BlackthornGym_MapScript_BuildBridge3
	end

BlackthornGym_MapScript_Var4::
	call BlackthornGym_MapScript_BuildBridge1
	call BlackthornGym_MapScript_BuildBridge2
	call BlackthornGym_MapScript_BuildBridge3
	call BlackthornGym_MapScript_BuildBridge4
	end

BlackthornGym_TriggerBridge1::
	call BlackthornGym_MapScript_BuildBridge1
	playse SE_BANG
	special DrawWholeMapView
	setvar VAR_BLACKTHORN_GYM_STATE, 1
	end

BlackthornGym_MapScript_BuildBridge1::
	setmetatile 19, 47, 0x35A, FALSE
	setmetatile 19, 48, 0x35A, FALSE
	setmetatile 19, 49, 0x35A, FALSE
	setmetatile 19, 50, 0x35A, FALSE
	setmetatile 19, 51, 0x35A, FALSE
	setmetatile 19, 52, 0x35A, FALSE
	setmetatile 19, 53, 0x35A, FALSE
	setmetatile 19, 54, 0x35A, FALSE
	setmetatile 20, 47, 0x35A, FALSE
	setmetatile 20, 48, 0x35A, FALSE
	setmetatile 20, 49, 0x35A, FALSE
	setmetatile 20, 50, 0x35A, FALSE
	setmetatile 20, 51, 0x35A, FALSE
	setmetatile 20, 52, 0x35A, FALSE
	setmetatile 20, 53, 0x35A, FALSE
	setmetatile 20, 54, 0x35A, FALSE
	setmetatile 21, 47, 0x35A, FALSE
	setmetatile 21, 48, 0x35A, FALSE
	setmetatile 21, 49, 0x35A, FALSE
	setmetatile 21, 50, 0x35A, FALSE
	setmetatile 21, 51, 0x35A, FALSE
	setmetatile 21, 52, 0x35A, FALSE
	setmetatile 21, 53, 0x35A, FALSE
	setmetatile 21, 54, 0x35A, FALSE
	return

BlackthornGym_TriggerBridge2::
	call BlackthornGym_MapScript_BuildBridge2
	playse SE_BANG
	special DrawWholeMapView
	setvar VAR_BLACKTHORN_GYM_STATE, 2
	end

BlackthornGym_MapScript_BuildBridge2::
	setmetatile 17, 35, 0x35A, FALSE
	setmetatile 17, 36, 0x35A, FALSE
	setmetatile 17, 37, 0x35A, FALSE
	setmetatile 17, 38, 0x35A, FALSE
	setmetatile 17, 39, 0x35A, FALSE
	setmetatile 17, 40, 0x35A, FALSE
	setmetatile 18, 35, 0x35A, FALSE
	setmetatile 18, 36, 0x35A, FALSE
	setmetatile 18, 37, 0x35A, FALSE
	setmetatile 18, 38, 0x35A, FALSE
	setmetatile 18, 39, 0x35A, FALSE
	setmetatile 18, 40, 0x35A, FALSE
	setmetatile 19, 35, 0x35A, FALSE
	setmetatile 19, 36, 0x35A, FALSE
	setmetatile 19, 37, 0x35A, FALSE
	setmetatile 19, 38, 0x35A, FALSE
	setmetatile 19, 39, 0x35A, FALSE
	setmetatile 19, 40, 0x35A, FALSE
	setmetatile 20, 32, 0x359, FALSE
	setmetatile 21, 32, 0x359, FALSE
	setmetatile 22, 32, 0x359, FALSE
	setmetatile 20, 35, 0x361, TRUE
	setmetatile 21, 35, 0x361, TRUE
	setmetatile 22, 35, 0x361, TRUE
	setmetatile 20, 33, 0x35A, FALSE
	setmetatile 20, 34, 0x35A, FALSE
	setmetatile 21, 33, 0x35A, FALSE
	setmetatile 21, 34, 0x35A, FALSE
	setmetatile 22, 33, 0x35A, FALSE
	setmetatile 22, 34, 0x35A, FALSE
	return

BlackthornGym_TriggerBridge3::
	call BlackthornGym_MapScript_BuildBridge3
	playse SE_BANG
	special DrawWholeMapView
	setvar VAR_BLACKTHORN_GYM_STATE, 3
	end

BlackthornGym_MapScript_BuildBridge3::
	setmetatile 17, 26, 0x359, FALSE
	setmetatile 18, 26, 0x359, FALSE
	setmetatile 19, 26, 0x359, FALSE
	setmetatile 20, 26, 0x359, FALSE
	setmetatile 21, 26, 0x359, FALSE
	setmetatile 22, 26, 0x359, FALSE
	setmetatile 23, 26, 0x359, FALSE

	setmetatile 17, 29, 0x361, TRUE
	setmetatile 18, 29, 0x361, TRUE
	setmetatile 19, 29, 0x361, TRUE
	setmetatile 20, 29, 0x361, TRUE
	setmetatile 21, 29, 0x361, TRUE
	setmetatile 22, 29, 0x361, TRUE
	setmetatile 23, 29, 0x361, TRUE

	setmetatile 17, 27, 0x35A, FALSE
	setmetatile 17, 28, 0x35A, FALSE
	setmetatile 18, 27, 0x35A, FALSE
	setmetatile 18, 28, 0x35A, FALSE
	setmetatile 19, 27, 0x35A, FALSE
	setmetatile 19, 28, 0x35A, FALSE
	setmetatile 20, 27, 0x35A, FALSE
	setmetatile 20, 28, 0x35A, FALSE
	setmetatile 21, 27, 0x35A, FALSE
	setmetatile 21, 28, 0x35A, FALSE
	setmetatile 22, 27, 0x35A, FALSE
	setmetatile 22, 28, 0x35A, FALSE
	setmetatile 23, 27, 0x35A, FALSE
	setmetatile 23, 28, 0x35A, FALSE
	return	

BlackthornGym_TriggerBridge4::
	call BlackthornGym_MapScript_BuildBridge4
	playse SE_BANG
	special DrawWholeMapView
	setvar VAR_BLACKTHORN_GYM_STATE, 4
	end

BlackthornGym_MapScript_BuildBridge4::
	setmetatile 19, 11, 0x35A, FALSE
	setmetatile 19, 12, 0x35A, FALSE
	setmetatile 19, 13, 0x35A, FALSE
	setmetatile 19, 14, 0x35A, FALSE
	setmetatile 19, 15, 0x35A, FALSE
	setmetatile 20, 11, 0x35A, FALSE
	setmetatile 20, 12, 0x35A, FALSE
	setmetatile 20, 13, 0x35A, FALSE
	setmetatile 20, 14, 0x35A, FALSE
	setmetatile 20, 15, 0x35A, FALSE
	setmetatile 21, 11, 0x35A, FALSE
	setmetatile 21, 12, 0x35A, FALSE
	setmetatile 21, 13, 0x35A, FALSE
	setmetatile 21, 14, 0x35A, FALSE
	setmetatile 21, 15, 0x35A, FALSE
	return


BlackthornGym_EventScript_Cody::
	trainerbattle_single TRAINER_CODY_HNS, BlackthornGym_Text_CooltrainermCodySeenText, BlackthornGym_Text_CooltrainermCodyBeatenText
	msgbox BlackthornGym_Text_CooltrainermCodyAfterBattleText, MSGBOX_AUTOCLOSE
	end

BlackthornGym_EventScript_Fran::
	trainerbattle_single TRAINER_FRAN_HNS, BlackthornGym_Text_CooltrainerfFranSeenText, BlackthornGym_Text_CooltrainerfFranBeatenText
	msgbox BlackthornGym_Text_CooltrainerfFranAfterBattleText, MSGBOX_AUTOCLOSE
	end

BlackthornGym_EventScript_Paul::
	trainerbattle_single TRAINER_PAUL_HNS, BlackthornGym_Text_CooltrainermPaulSeenText, BlackthornGym_Text_CooltrainermPaulBeatenText
	msgbox BlackthornGym_Text_CooltrainermPaulAfterBattleText, MSGBOX_AUTOCLOSE
	end

BlackthornGym_EventScript_Mike::
	trainerbattle_single TRAINER_MIKE_HNS, BlackthornGym_Text_CooltrainermMikeSeenText, BlackthornGym_Text_CooltrainermMikeBeatenText
	msgbox BlackthornGym_Text_CooltrainermMikeAfterBattleText, MSGBOX_AUTOCLOSE
	end

BlackthornGym_EventScript_Lola::
	trainerbattle_single TRAINER_LOLA_HNS, BlackthornGym_Text_CooltrainerfLolaSeenText, BlackthornGym_Text_CooltrainerfLolaBeatenText
	msgbox BlackthornGym_Text_CooltrainerfLolaAfterBattleText, MSGBOX_AUTOCLOSE
	end


BlackthornGym_EventScript_Clair::
	lock
	faceplayer
	goto_if_set FLAG_IS_CHAMPION, BlackthornGym_EventScript_ClairAfterLeague
	goto_if_ge VAR_BLACKTHORN_CITY_STATE, 4, BlackthornGym_EventScript_Clair_Defeated
	goto_if_eq VAR_BLACKTHORN_CITY_STATE, 2, BlackthornGym_EventScript_ClairDuringChallenge
	msgbox BlackthornGym_Text_ClairIntroText, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_CLAIR_1_HNS, BlackthornGym_Text_ClairWinText
	msgbox BlackthornGym_Text_ClairText_GoToDragonsDen, MSGBOX_DEFAULT
	setflag FLAG_DEFEATED_BLACKTHORN_GYM
	setvar VAR_0x8008, 8
	call Common_EventScript_SetGymTrainers_hns
	setvar VAR_BLACKTHORN_CITY_STATE, 2
	closemessage
	release
	end

BlackthornGym_EventScript_ClairDuringChallenge::
	msgbox BlackthornGym_Text_ClairText_TooMuchToExpect, MSGBOX_DEFAULT
	closemessage
	release
	end

BlackthornGym_EventScript_Clair_Defeated::
	msgbox BlackthornGym_Text_ClairText_League, MSGBOX_DEFAULT
	closemessage
	release
	end

BlackthornGym_EventScript_ClairAfterLeague::
	msgbox BlackthornGym_Text_ClairAfterLeague, MSGBOX_DEFAULT
	closemessage
	release
	end

BlackthornGym_Text_ClairIntroText:
    .string "אני קלייר.\p"
    .string "אמנית הדרקונים הטובה בעולם.\p"
    .string "אני מסוגלת להתמודד אפילו מול\n"
    .string "הרביעייה העילית של ליגת הפוקימון.\p"
    .string "אתה עדיין רוצה להילחם בי?\p"
    .string "…בסדר. קדימה!\p"
    .string "בתור מנהיגת מכון, אשתמש בכל\n"
    .string "הכוח שלי נגד כל יריב!$"

BlackthornGym_Text_ClairWinText:
    .string "הפסדתי?\p"
    .string "אני לא מאמינה. זו בטח\n"
    .string "טעות…$"

BlackthornGym_Text_ClairText_GoToDragonsDen:
    .string "אני לא מוכנה להודות בזה.\p"
    .string "אולי הפסדתי, אבל אתה עדיין\n"
    .string "לא מוכן לליגת הפוקימון.\p"
    .string "יש לי רעיון. כדאי שתעבור את\n"
    .string "האתגר של משתמשי הדרקונים.\p"
    .string "מאחורי המכון הזה יש מקום\n"
    .string "שנקרא מאורת הדרקון.\p"
    .string "במרכזו יש מקדש קטן.\n"
    .string "לך לשם.\p"
    .string "אם תוכיח שזנחת את האידיאלים\n"
    .string "העצלניים שלך,\p"
    .string "אכיר בך כמאמן שראוי לתג מכון!$"

BlackthornGym_Text_ClairText_TooMuchToExpect:
    .string "מה קרה?\p"
    .string "אני מצפה ממך ליותר מדי?$"

BlackthornGym_Text_ClairText_YouKeptMeWaiting:
    .string "You've kept me waiting!\p"
    .string "Here! Take this!$"

BlackthornGym_Text_ClairText_DescribeTM:
    .string "That contains DRAGON CLAW.\p"
    .string "You can figure out what it does.$"

BlackthornGym_Text_ClairText_League:
    .string "מה קרה?\p"
    .string "אתה לא בדרך\n"
    .string "לליגת הפוקימון?\p"
    .string "אתה לא יודע איפה היא?\p"
    .string "מכאן, לך לעיירה ניו בארק.\p"
    .string "משם, השתמש בגלישה כדי לשוט\n"
    .string "מזרחה. הדרך לשם קשה מאוד.\p"
    .string "שלא תעז להפסיד\n"
    .string "בליגת הפוקימון!\p"
    .string "אם תפסיד, ארגיש עוד יותר רע\n"
    .string "על זה שהפסדתי לך!\p"
    .string "תן את כל מה שיש לך.$"

BlackthornGym_Text_ClairAfterLeague:
    .string "עשית את זה, אה?\p"
    .string "עכשיו אתה האלוף של ג'וטו.$"

BlackthornGym_Text_ClairRematchText:
    .string "You did it, huh?\p"
    .string "You are now the JOHTO CHAMP.\p"
    .string "You've proven your strength but can\n"
    .string "you handle me again?\p"
    .string "As a Dragon Master, I won't hold\n"
    .string "back.\p"
    .string "Not this time.\p"
    .string "Want to have a rematch with me?$"

BlackthornGym_Text_ClairRematchDefeatText:
    .string "I lost?\p"
    .string "Again?\p"
    .string "I don't believe it. There must be\n"
    .string "some mistake…$"

BlackthornGym_Text_CooltrainermCodySeenText:
    .string "הרגע קיבלתי אישור להשתמש\n"
    .string "בפוקימונים מסוג דרקון!$"

BlackthornGym_Text_CooltrainermCodyBeatenText:
    .string "אוף! אילו רק היה לי דרגונייט!$"

BlackthornGym_Text_CooltrainermCodyAfterBattleText:
    .string "בשבט הדרקונים שלנו מותר להשתמש\n"
    .string "בפוקימוני דרקון רק באישור המאסטר.$"

BlackthornGym_Text_CooltrainerfFranSeenText:
    .string "אני לא יכולה לתת למאמן אלמוני\n"
    .string "לעבור על פניי!\p"
    .string "קלייר תתפוצץ מכעס אם אעשה את זה!$"

BlackthornGym_Text_CooltrainerfFranBeatenText:
    .string "אוי… הפסדתי…$"

BlackthornGym_Text_CooltrainerfFranAfterBattleText:
    .string "אוי ואבוי… קלייר תכעס…$"

BlackthornGym_Text_CooltrainermPaulSeenText:
    .string "הקרב הראשון שלך נגד דרקונים?\p"
    .string "אני אראה לך כמה הם קשוחים!$"

BlackthornGym_Text_CooltrainermPaulBeatenText:
    .string "פוקימוני הדרקון שלי הפסידו?$"

BlackthornGym_Text_CooltrainermPaulAfterBattleText:
    .string "לאנס אמר לך שהוא רוצה\n"
    .string "לראות אותך שוב?\p"
    .string "אין סיכוי!$"

BlackthornGym_Text_CooltrainermMikeSeenText:
    .string "הסיכוי שלי להפסיד? אפילו לא\n"
    .string "אחוז אחד!$"

BlackthornGym_Text_CooltrainermMikeBeatenText:
    .string "מוזר.$"

BlackthornGym_Text_CooltrainermMikeAfterBattleText:
    .string "עכשיו אני מכיר את החולשות שלי.\p"
    .string "תודה שהראית לי!$"

BlackthornGym_Text_CooltrainerfLolaSeenText:
    .string "דרקונים הם פוקימונים קדושים.\p"
    .string "הם מלאים באנרגיית חיים.\p"
    .string "אם לא תהיה רציני, לא\n"
    .string "תצליח לנצח אותם.$"

BlackthornGym_Text_CooltrainerfLolaBeatenText:
    .string "כל הכבוד!$"

BlackthornGym_Text_CooltrainerfLolaAfterBattleText:
    .string "דרקונים חלשים מול מהלכים\n"
    .string "מסוג דרקון.$"

BlackthornGym_EventScript_GymGuy::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_BLACKTHORN_GYM, BlackthornGym_EventScript_GymGuy2
	msgbox BlackthornGym_Text_GuideText, MSGBOX_DEFAULT
	closemessage
	release
	end
	
BlackthornGym_EventScript_GymGuy2::
	goto_if_set FLAG_BADGE08_GET, BlackthornGym_EventScript_GymGuy3
	msgbox BlackthornGym_Text_GuideGotoDragonsDen, MSGBOX_DEFAULT
	release
	end

BlackthornGym_EventScript_GymGuy3::
	msgbox BlackthornGym_Text_GuideWinText, MSGBOX_DEFAULT
	release
	end	

BlackthornGym_Text_GuideText:
    .string "יו! אלוף לעתיד!\p"
    .string "זה היה מסע ארוך, אבל\n"
    .string "כמעט סיימנו! סמוך עליי!\p"
    .string "קלייר אמנם מעריצה את\n"
    .string "אמן הדרקונים, לאנס,\p"
    .string "אבל היא יצרה לעצמה זהות משלה,\n"
    .string "עם קבוצה של דרקונים מהים.\p"
    .string "דרקונים אמורים להיות חלשים\n"
    .string "מול מהלכים מסוג קרח,\p"
    .string "אבל כדי לנצח תצטרך גם מהלכים\n"
    .string "משלך מסוג דרקון או מסוג פיה.$אתה יכול!$"

BlackthornGym_Text_GuideGotoDragonsDen:
	.string "היית נהדר כשניצחת את קלייר!\p"
	.string "אבל היא קצת לא יודעת\n"
	.string "להפסיד.\p"
	.string "נשמע שתצטרך ללכת למאורת הדרקון\n"
	.string "אם אתה רוצה את תג המכון!$"

BlackthornGym_Text_GuideWinText:
    .string "היית נהדר כשניצחת את קלייר!\p"
    .string "כל מה שנשאר זה האתגר\n"
    .string "של ליגת הפוקימון.\p"
    .string "אתה בדרך להפוך\n"
    .string "לאלוף הפוקימון!$"


BlackthornGym_EventScript_Statue::
	lock
	goto_if_set FLAG_BADGE08_GET, BlackthornGym_EventScript_Statue2
	msgbox BlackthornGym_Text_GymStatue, MSGBOX_DEFAULT
	closemessage
	release
	end

BlackthornGym_EventScript_Statue2::
	msgbox BlackthornGym_Text_GymStatueCertified, MSGBOX_DEFAULT
	closemessage
	release
	end

BlackthornGym_Text_GymStatue:
	.string "מכון הפוקימון של העיר בלקתורן$"

BlackthornGym_Text_GymStatueCertified:
	.string "מכון הפוקימון של העיר בלקתורן\p"
	.string "המאמנים המוסמכים של קלייר:\n"
	.string "{PLAYER}$"
