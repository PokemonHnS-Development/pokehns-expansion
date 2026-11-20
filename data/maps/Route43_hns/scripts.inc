Route43_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route43_MapScript_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route43_MapScript_OnTransition::
	call_if_set FLAG_HIDE_ROUTE42_SUICUNE, Route42_MapScript_HideTrigger
	callnative SetTimeBasedEncounters
	end

Route43_EventScript_Ben::
	trainerbattle_single TRAINER_BEN_HNS, Route43_Text_PokemaniacBenSeen, Route43_Text_PokemaniacBenBeaten
	msgbox Route43_Text_PokemaniacBenAfter, MSGBOX_AUTOCLOSE
	end

Route43_EventScript_Brent::
	trainerbattle_single TRAINER_BRENT_HNS, Route43_Text_PokemaniacBrentSeen, Route43_Text_PokemaniacBrentBeaten, Route43_EventScript_RegisterBrent
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route43_EventScript_RematchBrent
	msgbox Route43_Text_PokemaniacBrentAfter, MSGBOX_AUTOCLOSE
	end

Route43_EventScript_RegisterBrent::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route43_Text_BrentRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_BRENT_HNS
	release
	end

Route43_EventScript_RematchBrent::
	trainerbattle_rematch TRAINER_BRENT_HNS, Route43_Text_BrentRematchIntro, Route43_Text_BrentRematchDefeat
	msgbox Route43_Text_BrentPostRematch, MSGBOX_AUTOCLOSE
	end

Route43_EventScript_Ron::
	trainerbattle_single TRAINER_RON_HNS, Route43_Text_PokemaniacRonSeen, Route43_Text_PokemaniacRonBeaten
	msgbox Route43_Text_PokemaniacRonAfter, MSGBOX_AUTOCLOSE
	end

Route43_EventScript_Marvin::
	trainerbattle_single TRAINER_MARVIN_HNS, Route43_Text_FisherMarvinSeen, Route43_Text_FisherMarvinBeaten
	msgbox Route43_Text_FisherMarvinAfter, MSGBOX_AUTOCLOSE
	end
	
Route43_EventScript_Spencer::
	trainerbattle_single TRAINER_SPENCER_HNS, Route43_Text_CamperSpencerSeen, Route43_Text_CamperSpencerBeaten
	msgbox Route43_Text_CamperSpencerAfter, MSGBOX_AUTOCLOSE
	end

Route43_EventScript_Tiffany::
	trainerbattle_single TRAINER_TIFFANY_HNS, Route43_Text_PicnickerTiffanySeen, Route43_Text_PicnickerTiffanyBeaten, Route43_EventScript_RegisterTiffany
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route43_EventScript_RematchTiffany
	msgbox Route43_Text_PicnickerTiffanyWantsPicnic, MSGBOX_AUTOCLOSE
	end

Route43_EventScript_RegisterTiffany::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route43_Text_TiffanyRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_TIFFANY_HNS
	release
	end

Route43_EventScript_RematchTiffany::
	trainerbattle_rematch TRAINER_TIFFANY_HNS, Route43_Text_TiffanyRematchIntro, Route43_Text_TiffanyRematchDefeat
	msgbox Route43_Text_TiffanyPostRematch, MSGBOX_AUTOCLOSE
	end

Route43_EventScript_Sign1::
	msgbox Route43_Sign2, MSGBOX_SIGN
	end

Route43_EventScript_Sign2::
	msgbox Route43_TrainerTips, MSGBOX_SIGN
	end

Route43_EventScript_Item_Max_Ether::
	finditem ITEM_MAX_ETHER
	end

Route43_Text_PokemaniacBenSeen:
    .string "אני אוהב פוקימונים!\p"
    .string "בגלל זה התחלתי - ובגלל זה\n"
    .string "אמשיך לאסוף פוקימונים!$"

Route43_Text_PokemaniacBenBeaten:
    .string "איך יכולת לעשות לי את זה?$"

Route43_Text_PokemaniacBenAfter:
    .string "מה עוד אני אוהב חוץ\n"
    .string "מפוקימונים?\p"
    .string "את מרי מהרדיו. בטח היא\n"
    .string "חמודה!$"

Route43_Text_PokemaniacBrentSeen:
    .string "היי! יש לך פוקימונים\n"
    .string "נדירים?$"

Route43_Text_PokemaniacBrentBeaten:
    .string "אוי, הפוקימונים המסכנים שלי!\n"
    .string "יקיריי!$"

Route43_Text_PokemaniacBrentAfter:
    .string "הייתי שמח שיהיה לי\n"
    .string "ולו פוקימון נדיר אחד.$"

Route43_Text_BrentRegister:
    .string "הייתי שמח שיהיה לי\n"
    .string "ולו פוקימון נדיר אחד.$"

Route43_Text_BrentRematchIntro:
    .string "היי! יש לך פוקימונים\n"
    .string "נדירים?$"

Route43_Text_BrentRematchDefeat:
    .string "אוי, הפוקימונים המסכנים שלי!\n"
    .string "יקיריי!$"

Route43_Text_BrentPostRematch:
    .string "הייתי שמח שיהיה לי\n"
    .string "ולו פוקימון נדיר אחד.$"

Route43_Text_PokemaniacRonSeen:
    .string "אתה מאמין?\p"
    .string "איזה בחור בשם {RIVAL} צחק\n"
    .string "על הפוקימונים שלי!\p"
    .string "לעזאזל! הפוקימונים שלי מעולים!$"

Route43_Text_PokemaniacRonBeaten:
    .string "הנידוקינג שלי הסתדר לא רע בכלל!$"

Route43_Text_PokemaniacRonAfter:
    .string "זה בסדר שאנשים אוהבים\n"
    .string "סוגים שונים של פוקימונים.\p"
    .string "בפוקימונים לא הכול זה\n"
    .string "להחזיק את החזק ביותר.$"

Route43_Text_FisherMarvinSeen:
    .string "אני בתקופה רעה.\p"
    .string "אולי זה הציוד שלי.\p"
    .string "נילחם קצת, לשם שינוי!$"

Route43_Text_FisherMarvinBeaten:
    .string "הפסדתי, אבל בכל זאת\n"
    .string "אני מרגיש יותר טוב.$"

Route43_Text_FisherMarvinAfter:
    .string "כדור הפיתיון של קורט הוא הכי טוב\n"
    .string "לתפיסת פוקימונים שעלו בחכה.\p"
    .string "הוא יעיל הרבה יותר\n"
    .string "מאולטרה בול.$"

Route43_Text_CamperSpencerSeen:
    .string "אני יכול לעשות כל כך הרבה\n"
    .string "עם הפוקימונים שלי - כיף חיים!$"

Route43_Text_CamperSpencerBeaten:
    .string "להפסיד זה בכלל לא כיף…$"

Route43_Text_CamperSpencerAfter:
    .string "מה קורה באגם הזעם?\p"
    .string "תכננו לעשות שם קמפינג.$"

Route43_Text_PicnickerTiffanySeen:
    .string "גם אתה בדרך לאגם הזעם?\p"
    .string "נשחק קצת ביחד!$"

Route43_Text_PicnickerTiffanyBeaten:
    .string "שיחקתי יותר מדי!$"

Route43_Text_PicnickerTiffanyWantsPicnic:
    .string "אני עושה פיקניק עם פוקימונים.\p"
    .string "אולי תצטרף אלינו?$"

Route43_Text_TiffanyRegister:
    .string "אני עושה פיקניק עם פוקימונים.\p"
    .string "אולי תצטרף אלינו?$"

Route43_Text_TiffanyRematchIntro:
    .string "גם אתה בדרך לאגם הזעם?\p"
    .string "נשחק קצת ביחד!$"

Route43_Text_TiffanyRematchDefeat:
    .string "שיחקתי יותר מדי!$"

Route43_Text_TiffanyPostRematch:
    .string "אני עושה פיקניק עם פוקימונים.\p"
    .string "אולי תצטרף אלינו?$"

Route43_Sign1:
    .string "ROUTE 43\p"
    .string "LAKE OF RAGE - MAHOGANY TOWN$"

Route43_Sign2:
    .string "דרך 43\p"
    .string "אגם הזעם - העיירה מהגוני$"

Route43_TrainerTips:
    .string "טיפים למאמנים\p"
    .string "לכל הפוקימונים יש יתרונות\n"
    .string "וחסרונות לפי הסוגים שלהם.\p"
    .string "אם הסוגים שונים, פוקימון ברמה\n"
    .string "גבוהה יותר עלול להפסיד בקרב.\p"
    .string "כדאי ללמוד אילו סוגים חזקים\n"
    .string "וחלשים מול הסוג של הפוקימון שלך.$"
