Route37_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route37_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route37_OnTransition: 
	callnative SetTimeBasedEncounters
	end



Route37_EventScript_TwinAnn::
	trainerbattle_double TRAINER_ANN_AND_ANNE_HNS, Route37_Text_TwinsAnnAndAnne1_Seen, Route37_Text_TwinsAnnAndAnne1_Beaten, Route104_Text_GinaNotEnoughMons
	special GetPlayerBigGuyGirlString
	msgbox Route37_Text_TwinsAnnAndAnne1_After, MSGBOX_DEFAULT
	release
	end
	
Route37_EventScript_TwinAnne::
	trainerbattle_double TRAINER_ANN_AND_ANNE_HNS, Route37_Text_TwinsAnnAndAnne2_Seen, Route37_Text_TwinsAnnAndAnne2_Beaten, Route104_Text_GinaNotEnoughMons
	special GetPlayerBigGuyGirlString
	msgbox Route37_Text_TwinsAnnAndAnne2_After, MSGBOX_DEFAULT
	release
	end

Route37_EventScript_Greg::
	trainerbattle_single TRAINER_GREG_HNS, Route37_Text_PsychicGreg_Seen, Route37_Text_PsychicGreg_Beaten
	msgbox Route37_Text_PsychicGreg_After, MSGBOX_AUTOCLOSE
	end


Route37_EventScript_Sunny::
	lock
	faceplayer
	goto_if_set FLAG_GOT_MAGNET, Route37_EventScript_SunnyCompleted
	msgbox Route37_Text_Sunny_Meet, MSGBOX_DEFAULT
	closemessage
	multichoice 20, 0, MULTI_DAYS_OF_WEEK, FALSE
	switch VAR_RESULT
	case 0, Route37_EventScript_SunnyYes
	case 1, Route37_EventScript_SunnyNope
	case 2, Route37_EventScript_SunnyNope
	case 3, Route37_EventScript_SunnyNope
	case 4, Route37_EventScript_SunnyNope
	case 5, Route37_EventScript_SunnyNope
	case 6, Route37_EventScript_SunnyNope
	case 7 Route37_EventScript_SunnyCancel
	case MULTI_B_PRESSED, Route37_EventScript_SunnyCancel
	closemessage
	release
	end
Route37_EventScript_SunnyYes::
	msgbox Route37_Text_Sunny_GiveGift2, MSGBOX_DEFAULT
	giveitem ITEM_MAGNET
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_GOT_MAGNET
	msgbox Route37_Text_Sunny_GaveGift, MSGBOX_DEFAULT
	closemessage
	release
	end
Route37_EventScript_SunnyNope::
	msgbox Route29_Text_TuscanyNope, MSGBOX_DEFAULT
	closemessage
	release
	end
Route37_EventScript_SunnyCancel::
	closemessage
	release
	end
Route37_EventScript_SunnyCompleted::
	msgbox Route37_Text_Sunny_Sunday, MSGBOX_DEFAULT
	closemessage
	release
	end

Route37_EventScript_Sign::
	lock
	msgbox Route37_Text_Sign, MSGBOX_SIGN
	closemessage
	release
	end

Route37_Text_TwinsAnnAndAnne1_Seen:
	.string "אן: אן ואני צוות אחד!$"

Route37_Text_TwinsAnnAndAnne1_Beaten:
	.string "אן ואן: ממם…\n"
	.string "קצת חזק מדי.$"

Route37_Text_TwinsAnnAndAnne1_After:
	.string "אן: אני יודעת מה אחותי\n"
	.string "והפוקימונים שלי חושבים.$"

Route37_Text_TwinsAnnAndAnne2_Seen:
	.string "אן: אן ואני צוות אחד!$"

Route37_Text_TwinsAnnAndAnne2_Beaten:
	.string "אן ואן: ממם…\n"
	.string "קצת חזק מדי.$"

Route37_Text_TwinsAnnAndAnne2_After:
	.string "אן: אנחנו מרגישות בדיוק\n"
	.string "כמו הפוקימונים שלנו.$"

Route37_Text_PsychicGreg_Seen:
	.string "פוקימונים לא יכולים לעשות כלום\n"
	.string "כשהם ישנים.\p"
	.string "אני אראה לך כמה זה מפחיד!$"

Route37_Text_PsychicGreg_Beaten:
	.string "הפסדתי. זה די עצוב…$"

Route37_Text_PsychicGreg_After:
	.string "להרדים פוקימונים או לשתק אותם -\n"
	.string "אלה טכניקות קרב טובות.$"

Route37_Text_Sunny_Meet:
	.string "סאני: היי!\p"
	.string "אני סאני, ממשפחת ימי השבוע!\p"
	.string "אם תנחש מה היום האהוב עליי,\n"
	.string "אתן לך פרס.$"

Route37_Text_Sunny_GiveGift1:
	.string "I was told to give you this if I saw\n"
	.string "you!$"

Route37_Text_Sunny_GiveGift2:
	.string "אמרו לי לתת לך את זה\n"
	.string "אם אראה אותך!$"

Route37_Text_Sunny_GaveGift:
	.string "סאני: הדבר הזה…\p"
	.string "אממ…\p"
	.string "… מה זה היה בעצם…\p"
	.string "…\p"
	.string "אה! עכשיו אני נזכר!\p"
	.string "כדאי שפוקימון שיודע מהלכים\n"
	.string "חשמליים יחזיק בזה.\p"
	.string "אחותי מוניקה אמרה שזה מחזק\n"
	.string "מהלכים חשמליים!$"

Route37_Text_Sunny_Sunday:
	.string "סאני: לאחים ולאחיות שלי קוראים\n"
	.string "מוניקה, טוסקני, ווסלי,\p"
	.string "וגם ארתור, פרידה וסנטוס.\n"
	.string "כולם יותר גדולים ממני!$"

Route37_Text_Sunny_NotSunday:
	.string "SUNNY: Isn't today Sunday?\n"
	.string "Um… I forgot!$"

Route37_Text_Sign:
	.string "דרך 37\n"
	.string "העיר אקרוטיק בהמשך$"
