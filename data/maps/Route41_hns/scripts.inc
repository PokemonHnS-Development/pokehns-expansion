Route41_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route41_MapScript_OnTransition
	.byte 0

Route41_MapScript_OnTransition::
	goto_if_eq VAR_COMPLETED_LUGIA, 4, Route41_MapScript_DoNothing
	goto_if_ge VAR_OLIVINE_CITY_STATE, 5, OlivineCity_MapScript_ClearWeather
	end

Route41_MapScript_DoNothing::
	end

Route41_EventScript_Charlie::
	trainerbattle_single TRAINER_CHARLIE_HNS, Route41_Text_SwimmermCharlieSeen, Route41_Text_SwimmermCharlieBeaten
	msgbox Route41_Text_SwimmermCharlieAfter, MSGBOX_AUTOCLOSE
	end

Route41_Text_SwimmermCharlieSeen:
	.string "המים חמימים כאן.\n"
	.string "אני רפוי וגמיש.\p"
	.string "בטח, אני אתמודד איתך!$"

Route41_Text_SwimmermCharlieBeaten:
	.string "אוי! נהייתי מקומט כמו צימוק!$"

Route41_Text_SwimmermCharlieAfter:
	.string "לא מרגיע פשוט לצוף\n"
	.string "ככה?$"

Route41_EventScript_George::
	trainerbattle_single TRAINER_GEORGE_HNS, Route41_Text_SwimmermGeorgeSeen, Route41_Text_SwimmermGeorgeBeaten
	msgbox Route41_Text_SwimmermGeorgeAfter, MSGBOX_AUTOCLOSE
	end

Route41_Text_SwimmermGeorgeSeen:
	.string "אני קצת עייף.\n"
	.string "אם אנצח, תשאיל לי את הפוקימון שלך.$"

Route41_Text_SwimmermGeorgeBeaten:
	.string "מתנשף, מתנשף…$"

Route41_Text_SwimmermGeorgeAfter:
	.string "סיאנווד כל כך רחוקה.\p"
	.string "אבל גם הדרך חזרה לאוליבין\n"
	.string "לא קלה.\p"
	.string "מה אני אמור לעשות?$"

Route41_EventScript_Berke::
	trainerbattle_single TRAINER_BERKE_HNS, Route41_Text_SwimmermBerkeSeen, Route41_Text_SwimmermBerkeBeaten
	msgbox Route41_Text_SwimmermBerkeAfter, MSGBOX_AUTOCLOSE
	end

Route41_Text_SwimmermBerkeSeen:
	.string "רואה את האיים האלה שחסומים\n"
	.string "במערבולות?\p"
	.string "חייב להיות שם סוד!$"

Route41_Text_SwimmermBerkeBeaten:
	.string "מה הסוד של הכוח שלך?$"

Route41_Text_SwimmermBerkeAfter:
	.string "זה היה לילה חשוך וסוער…\p"
	.string "ראיתי פוקימון ענק עף\n"
	.string "מהאיים.\p"
	.string "הוא פיזר נוצות\n"
	.string "מכנפי הכסף שלו.$"

Route41_EventScript_Kirk::
	trainerbattle_single TRAINER_KIRK_HNS, Route41_Text_SwimmermKirkSeen, Route41_Text_SwimmermKirkBeaten
	msgbox Route41_Text_SwimmermKirkAfter, MSGBOX_AUTOCLOSE
	end

Route41_Text_SwimmermKirkSeen:
	.string "הגלים פראיים כאן.\p"
	.string "הם מעייפים אותך\n"
	.string "בזמן השחייה.$"

Route41_Text_SwimmermKirkBeaten:
	.string "אני גמור!$"

Route41_Text_SwimmermKirkAfter:
	.string "הזרמים לא נותנים לי\n"
	.string "להגיע לאי ההוא.$"

Route41_EventScript_Mathew::
	trainerbattle_single TRAINER_MATHEW_HNS, Route41_Text_SwimmermMathewSeen, Route41_Text_SwimmermMathewBeaten
	msgbox Route41_Text_SwimmermMathewAfter, MSGBOX_AUTOCLOSE
	end

Route41_Text_SwimmermMathewSeen:
	.string "אתה מחפש את הסודות\n"
	.string "של איי המערבולת?$"

Route41_Text_SwimmermMathewBeaten:
	.string "אוו, יש לך סיבולת מעולה!$"

Route41_Text_SwimmermMathewAfter:
	.string "סוד על איי המערבולת…\p"
	.string "בפנים חושך מוחלט!$"

Route41_EventScript_Kaylee::
	trainerbattle_single TRAINER_KAYLEE_HNS, Route41_Text_SwimmerfKayleeSeen, Route41_Text_SwimmerfKayleeBeaten
	msgbox Route41_Text_SwimmerfKayleeAfter, MSGBOX_AUTOCLOSE
	end

Route41_Text_SwimmerfKayleeSeen:
	.string "אני בדרך לאיי המערבולת.\p"
	.string "אני הולכת לחקור עם חברים.$"

Route41_Text_SwimmerfKayleeBeaten:
	.string "ככה עושים את זה?$"

Route41_Text_SwimmerfKayleeAfter:
	.string "אומרים שיש פוקימון גדול עמוק\n"
	.string "מתחת לאיי המערבולת.\p"
	.string "מעניין מה זה יכול להיות?$"

Route41_EventScript_Susie::
	trainerbattle_single TRAINER_SUSIE_HNS, Route41_Text_SwimmerfSusieSeen, Route41_Text_SwimmerfSusieBeaten
	msgbox Route41_Text_SwimmerfSusieAfter, MSGBOX_AUTOCLOSE
	end

Route41_Text_SwimmerfSusieSeen:
	.string "אתה נראה כל כך אלגנטי\n"
	.string "כשאתה רוכב על הפוקימון שלך.$"

Route41_Text_SwimmerfSusieBeaten:
	.string "אני הרוסה…$"

Route41_Text_SwimmerfSusieAfter:
	.string "לא היה שיר להיט על\n"
	.string "ילד שרוכב על לפרס?$"

Route41_EventScript_Denise::
	trainerbattle_single TRAINER_DENISE_HNS, Route41_Text_SwimmerfDeniseSeen, Route41_Text_SwimmerfDeniseBeaten
	msgbox Route41_Text_SwimmerfDeniseAfter, MSGBOX_AUTOCLOSE
	end

Route41_Text_SwimmerfDeniseSeen:
	.string "מזג האוויר כל כך יפה,\n"
	.string "אני ממש בעננים!$"

Route41_Text_SwimmerfDeniseBeaten:
	.string "אוהה!$"

Route41_Text_SwimmerfDeniseAfter:
	.string "כוויות שמש הן הכי גרועות לעור.\p"
	.string "אבל אני לא משתמשת בקרם הגנה.\p"
	.string "אני לא אזהם את המים.$"

Route41_EventScript_Kara::
	trainerbattle_single TRAINER_KARA_HNS, Route41_Text_SwimmerfKaraSeen, Route41_Text_SwimmerfKaraBeaten
	msgbox Route41_Text_SwimmerfKaraAfter, MSGBOX_AUTOCLOSE
	end

Route41_Text_SwimmerfKaraSeen:
	.string "אם צריך לנוח,\n"
	.string "פשוט דורכים במים.\p"
	.string "ככה הנשימה חוזרת,\n"
	.string "ואפשר להמשיך בכל הכוח.$"

Route41_Text_SwimmerfKaraBeaten:
	.string "או! יש לך יותר אנרגיה ממני.$"

Route41_Text_SwimmerfKaraAfter:
	.string "שמעתי שאגות מעומק\n"
	.string "האיים.$"

Route41_EventScript_Wendy::
	trainerbattle_single TRAINER_WENDY_HNS, Route41_Text_SwimmerfWendySeen, Route41_Text_SwimmerfWendyBeaten
	msgbox Route41_Text_SwimmerfWendyAfter, MSGBOX_AUTOCLOSE
	end

Route41_Text_SwimmerfWendySeen:
	.string "בלילה, סטאריו מתקבצים\n"
	.string "ליד פני המים.$"

Route41_Text_SwimmerfWendyBeaten:
	.string "אוי ואבוי…$"

Route41_Text_SwimmerfWendyAfter:
	.string "להקות הסטאריו נדלקות\n"
	.string "באותו הזמן.\p"
	.string "זה כל כך יפה שזה מפחיד.$"

Route41_EventScript_Tentacruel1::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_TENTACRUEL, CRY_MODE_NORMAL
	goto_if_ge VAR_TEMP_0, 2, Route41_EventScript_TentacruelAttack1
	msgbox Route41_Text_Tentacruel, MSGBOX_DEFAULT
	waitmoncry
	addvar VAR_TEMP_0, 1
	release
	end
Route41_EventScript_TentacruelAttack1::
	msgbox Route41_Text_TentacruelAttack, MSGBOX_DEFAULT
	waitmessage
	setflag FLAG_NO_WILD_CATCHING
	setflag FLAG_NO_SHINY
	setwildbattle SPECIES_TENTACRUEL, 100, ITEM_NONE
	dowildbattle
	closemessage
	clearflag FLAG_NO_WILD_CATCHING
	clearflag FLAG_NO_SHINY
	playse SE_USE_ITEM
	msgbox Route41_Text_TentacruelHeal, MSGBOX_DEFAULT
	setvar VAR_TEMP_0, 0
	closemessage
	release
	end

Route41_EventScript_Tentacruel2::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_TENTACRUEL, CRY_MODE_NORMAL
	goto_if_ge VAR_TEMP_1, 2, Route41_EventScript_TentacruelAttack2
	msgbox Route41_Text_Tentacruel, MSGBOX_DEFAULT
	waitmoncry
	addvar VAR_TEMP_1, 1
	release
	end
Route41_EventScript_TentacruelAttack2::
	msgbox Route41_Text_TentacruelAttack, MSGBOX_DEFAULT
	waitmessage
	setwildbattle SPECIES_TENTACRUEL, 100, ITEM_NONE
	dowildbattle
	closemessage
	playse SE_USE_ITEM
	msgbox Route41_Text_TentacruelHeal, MSGBOX_DEFAULT
	setvar VAR_TEMP_1, 0
	closemessage
	release
	end

Route41_EventScript_Tentacruel3::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_TENTACRUEL, CRY_MODE_NORMAL
	goto_if_ge VAR_TEMP_2, 2, Route41_EventScript_TentacruelAttack3
	msgbox Route41_Text_Tentacruel, MSGBOX_DEFAULT
	waitmoncry
	addvar VAR_TEMP_2, 1
	release
	end
Route41_EventScript_TentacruelAttack3::
	msgbox Route41_Text_TentacruelAttack, MSGBOX_DEFAULT
	waitmessage
	setwildbattle SPECIES_TENTACRUEL, 100, ITEM_NONE
	dowildbattle
	closemessage
	playse SE_USE_ITEM
	msgbox Route41_Text_TentacruelHeal, MSGBOX_DEFAULT
	setvar VAR_TEMP_2, 0
	closemessage
	release
	end

Route41_EventScript_Tentacruel4::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_TENTACRUEL, CRY_MODE_NORMAL
	goto_if_ge VAR_TEMP_3, 2, Route41_EventScript_TentacruelAttack4
	msgbox Route41_Text_Tentacruel, MSGBOX_DEFAULT
	waitmoncry
	addvar VAR_TEMP_3, 1
	release
	end
Route41_EventScript_TentacruelAttack4::
	msgbox Route41_Text_TentacruelAttack, MSGBOX_DEFAULT
	waitmessage
	setwildbattle SPECIES_TENTACRUEL, 100, ITEM_NONE
	dowildbattle
	closemessage
	playse SE_USE_ITEM
	msgbox Route41_Text_TentacruelHeal, MSGBOX_DEFAULT
	setvar VAR_TEMP_3, 0
	closemessage
	release
	end

Route41_Text_Tentacruel:
	.string "טנטקרול: קרוווו…$"

Route41_Text_TentacruelAttack:
	.string "טנטקרול: קרווווווו!$"

Route41_Text_TentacruelHeal:
	.string "הטנטקרול השתמש בהחלמה!\n"
	.string "הוא החלים לגמרי!$"
