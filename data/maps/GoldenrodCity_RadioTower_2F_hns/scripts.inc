GoldenrodCity_RadioTower_2F_hns_MapScripts::
	.byte 0

GoldenrodRaidoTower2_EventScript_Grunt3::
	trainerbattle_single TRAINER_GRUNT_3_HNS, GoldenrodCity_RadioTower_2F_Text_GruntM4Seen, GoldenrodCity_RadioTower_2F_Text_GruntM4Beaten
	msgbox GoldenrodCity_RadioTower_2F_Text_GruntM4After, MSGBOX_AUTOCLOSE
	end
GoldenrodRaidoTower2_EventScript_Grunt4::
	trainerbattle_single TRAINER_GRUNT_4_HNS, GoldenrodCity_RadioTower_2F_Text_GruntM5Seen, GoldenrodCity_RadioTower_2F_Text_GruntM5Beaten
	msgbox GoldenrodCity_RadioTower_2F_Text_GruntM5After, MSGBOX_AUTOCLOSE
	end
GoldenrodRaidoTower2_EventScript_Grunt5::
	trainerbattle_single TRAINER_GRUNT_5_HNS, GoldenrodCity_RadioTower_2F_Text_GruntM6Seen, GoldenrodCity_RadioTower_2F_Text_GruntM6Beaten
	msgbox GoldenrodCity_RadioTower_2F_Text_GruntM6After, MSGBOX_AUTOCLOSE
	end
GoldenrodRaidoTower2_EventScript_GruntF2::
	trainerbattle_single TRAINER_GRUNT_26_HNS, GoldenrodCity_RadioTower_2F_Text_GruntF2Seen, GoldenrodCity_RadioTower_2F_Text_GruntF2Beaten
	msgbox GoldenrodCity_RadioTower_2F_Text_GruntF2After, MSGBOX_AUTOCLOSE
	end

GoldenrodCity_RadioTower_2F_EventScript_Sign1::
	lock
	msgbox GoldenrodCity_RadioTower_2F_Text_SalesSign, MSGBOX_SIGN
	closemessage
	release
	end

GoldenrodCity_RadioTower_2F_EventScript_Sign2::
	lock
	msgbox GoldenrodCity_RadioTower_2F_Text_OakTalkSign, MSGBOX_SIGN
	closemessage
	release
	end

GoldenrodCity_RadioTower_2F_EventScript_Boy::
	lock
	faceplayer
	msgbox GoldenrodCity_RadioTower_2F_Text_SuperNerd, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_RadioTower_2F_EventScript_Policeman::
	lock
	faceplayer
	msgbox GoldenrodCity_RadioTower_2F_Text_Policeman, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_RadioTower_2F_EventScript_Buena::
	lock
	faceplayer
	goto_if_eq VAR_GOLDENROD_CITY_STATE, 6, GoldenrodCity_RadioTower_2F_EventScript_BuenaRocket
	goto_if_eq VAR_GOLDENROD_CITY_STATE, 7, GoldenrodCity_RadioTower_2F_EventScript_BuenaRocket
	goto_if_eq VAR_GOLDENROD_CITY_STATE, 8, GoldenrodCity_RadioTower_2F_EventScript_BuenaRocket
	goto_if_eq VAR_GOLDENROD_CITY_STATE, 9, GoldenrodCity_RadioTower_2F_EventScript_BuenaRocket
	goto_if_set FLAG_DAILY_BUENAS_PASSWORD_GUESSED, GoldenrodCity_RadioTower_2F_EventScript_BuenaAlreadyPlayed
	goto_if_unset FLAG_DAILY_BUENAS_PASSWORD, GoldenrodCity_RadioTower_2F_EventScript_BuenaNoShow
	msgbox GoldenrodCity_RadioTower_2F_Text_BuenaAskPassword, MSGBOX_DEFAULT
	special Special_BuenaPasswordShowMultichoice
	waitstate
	compare VAR_RESULT, 127
	goto_if_eq GoldenrodCity_RadioTower_2F_EventScript_BuenaCancelled
	special Special_BuenaCheckAnswer
	compare VAR_RESULT, TRUE
	goto_if_eq GoldenrodCity_RadioTower_2F_EventScript_BuenaCorrect
	setflag FLAG_DAILY_BUENAS_PASSWORD_GUESSED
	msgbox GoldenrodCity_RadioTower_2F_Text_BuenaWrong, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_RadioTower_2F_EventScript_BuenaCorrect::
	special Special_BuenaRollReward
	copyvar VAR_0x8004, VAR_RESULT
	checkitemspace VAR_0x8004, 1
	compare VAR_RESULT, FALSE
	goto_if_eq GoldenrodCity_RadioTower_2F_EventScript_BuenaBagFull
	giveitem VAR_0x8004, 1
	setflag FLAG_DAILY_BUENAS_PASSWORD_GUESSED
	msgbox GoldenrodCity_RadioTower_2F_Text_BuenaCorrect, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_RadioTower_2F_EventScript_BuenaBagFull::
	msgbox GoldenrodCity_RadioTower_2F_Text_BuenaBagFull, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_RadioTower_2F_EventScript_BuenaCancelled::
	msgbox GoldenrodCity_RadioTower_2F_Text_BuenaComeBack, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_RadioTower_2F_EventScript_BuenaAlreadyPlayed::
	msgbox GoldenrodCity_RadioTower_2F_Text_BuenaAlreadyPlayed, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_RadioTower_2F_EventScript_BuenaNoShow::
	msgbox GoldenrodCity_RadioTower_2F_Text_BuenaShowPromo, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_RadioTower_2F_EventScript_BuenaRocket::
	msgbox RadioTower2FBuenaPasswordIsHelpText, MSGBOX_DEFAULT
	closemessage
	release
	end


GoldenrodCity_RadioTower_2F_EventScript_Teacher::
	lock
	faceplayer
	goto_if_eq VAR_GOLDENROD_CITY_STATE, 6, GoldenrodCity_RadioTower_2F_EventScript_Teacher2
	goto_if_eq VAR_GOLDENROD_CITY_STATE, 7, GoldenrodCity_RadioTower_2F_EventScript_Teacher2 
	goto_if_eq VAR_GOLDENROD_CITY_STATE, 8, GoldenrodCity_RadioTower_2F_EventScript_Teacher2 
	goto_if_eq VAR_GOLDENROD_CITY_STATE, 9, GoldenrodCity_RadioTower_2F_EventScript_Teacher2 
	msgbox GoldenrodCity_RadioTower_2F_Text_Teacher, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_RadioTower_2F_EventScript_Teacher2::
	msgbox GoldenrodCity_RadioTower_2F_Text_TeacherRockets, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_RadioTower_2F_EventScript_Jigglypuff::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_JIGGLYPUFF, CRY_MODE_NORMAL
	msgbox GoldenrodCity_RadioTower_2F_Text_Jigglypuff, MSGBOX_DEFAULT
	waitmoncry
	release
	end

RadioTower2FBuenaPasswordIsHelpText:
	.string "בואנה: מה? הסיסמה של היום?\n"
	.string "”הצילו”, כמובן!$"

GoldenrodCity_RadioTower_2F_Text_SuperNerd:
	.string "אפשר להאזין לרדיו בכל מקום.\n"
	.string "כדאי להקשיב!$"

GoldenrodCity_RadioTower_2F_Text_Policeman:
	.string "מכאן והלאה הכניסה\n"
	.string "מוגבלת.$"

GoldenrodCity_RadioTower_2F_Text_Teacher:
	.string "שירי ערש ברדיו עלולים\n"
	.string "להרדים פוקימונים.$"

GoldenrodCity_RadioTower_2F_Text_TeacherRockets:
	.string "למה שירצו להשתלט על\n"
	.string "מגדל הרדיו?$"

GoldenrodCity_RadioTower_2F_Text_Jigglypuff:
	.string "ג'יגליפאף: ג'יגלי…$"

GoldenrodCity_RadioTower_2F_Text_BlackBelt1:
	.string "Sorry. Authorized personnel only\n"
	.string "beyond this point.\p"
	.string "It wasn't that way before.\p"
	.string "There's something wrong with the\n"
	.string "DIRECTOR…$"

GoldenrodCity_RadioTower_2F_Text_BlackBelt2:
	.string "Feel free to look around anywhere.\p"
	.string "The DIRECTOR is nice again, just\n"
	.string "as he was before.$"

GoldenrodCity_RadioTower_2F_Text_GruntM4Seen:
	.string "לפני שלוש שנים צוות רוקט\n"
	.string "נאלץ להתפרק.\p"
	.string "אבל כאן אנחנו חוזרים בגדול!$"

GoldenrodCity_RadioTower_2F_Text_GruntM4Beaten:
	.string "גוואה! אל תתחכם!$"

GoldenrodCity_RadioTower_2F_Text_GruntM4After:
	.string "לא ניתן לך להרוס את התוכניות\n"
	.string "שלנו לחזור בגדול!$"

GoldenrodCity_RadioTower_2F_Text_GruntM5Seen:
	.string "אנחנו צוות רוקט,\n"
	.string "מנצלי הפוקימונים!\p"
	.string "אנחנו אוהבים להיות רעים! מפחד?$"

GoldenrodCity_RadioTower_2F_Text_GruntM5Beaten:
	.string "אתה חושב שאתה גיבור?$"

GoldenrodCity_RadioTower_2F_Text_GruntM5After:
	.string "אנחנו לא תמיד רעים. אנחנו פשוט\n"
	.string "עושים מה שבא לנו.$"

GoldenrodCity_RadioTower_2F_Text_GruntM6Seen:
	.string "היי, היי! אל תעמוד לנו בדרך!$"

GoldenrodCity_RadioTower_2F_Text_GruntM6Beaten:
	.string "ארגגג. אני מוותר.$"

GoldenrodCity_RadioTower_2F_Text_GruntM6After:
	.string "המנהלים שלנו מנסים להשתלט\n"
	.string "על המקום הזה.\p"
	.string "יש להם איזו תוכנית גדולה.\n"
	.string "מעניין מה היא?$"

GoldenrodCity_RadioTower_2F_Text_GruntF2Seen:
	.string "חה-חה-חה!\p"
	.string "כמה משעמם. היה קל מדי\n"
	.string "להשתלט על המקום הזה!\p"
	.string "קדימה, תשעשע אותי!$"

GoldenrodCity_RadioTower_2F_Text_GruntF2Beaten:
	.string "מ-מי אתה?$"

GoldenrodCity_RadioTower_2F_Text_GruntF2After:
	.string "ניצחת אותי, ואני לא אשכח\n"
	.string "את זה!$"

GoldenrodCity_RadioTower_2F_Text_BuenaShowPromo:
	.string "בואנה: תאזינו לתוכנית\n"
	.string "הסיסמה שלי!\p"
	.string "הקשיבו כדי לגלות את\n"
	.string "הסיסמה של היום!$"

GoldenrodCity_RadioTower_2F_Text_BuenaAskPassword:
	.string "בואנה: היי!\p"
	.string "נו, אתה יודע מה הסיסמה\n"
	.string "של היום?\p"
	.string "אוקיי! אז איזו מהן?$"

GoldenrodCity_RadioTower_2F_Text_BuenaCorrect:
	.string "בואנה: צדקת!\p"
	.string "הנה, {STR_VAR_1}\n"
	.string "בתור הפרס שלך!$"

GoldenrodCity_RadioTower_2F_Text_BuenaWrong:
	.string "בואנה: בזזט! חבל!\p"
	.string "אפשר לנסות שוב מחר!$"

GoldenrodCity_RadioTower_2F_Text_BuenaComeBack:
	.string "בואנה: אין ניחוש?\n"
	.string "תחזור כשתהיה מוכן!$"

GoldenrodCity_RadioTower_2F_Text_BuenaAlreadyPlayed:
	.string "בואנה: כבר ניחשת את הסיסמה של היום!\p"
	.string "תאזין שוב מחר!$"

GoldenrodCity_RadioTower_2F_Text_BuenaBagFull:
	.string "בואנה: צדקת, אבל\n"
	.string "התיק שלך מלא!\p"
	.string "תפנה קצת מקום ותבוא\n"
	.string "לדבר איתי שוב!$"

GoldenrodCity_RadioTower_2F_Text_SalesSign:
	.string "קומה 2: מכירות$"

GoldenrodCity_RadioTower_2F_Text_OakTalkSign:
	.string "שיחות פוקימון עם פרופ' אוק\p"
	.string "התוכנית הכי לוהטת בשידור!$"

GoldenrodCity_RadioTower_2F_Text_PokemonRadioSign:
	.string "Anywhere, Anytime POKéMON Radio$"
