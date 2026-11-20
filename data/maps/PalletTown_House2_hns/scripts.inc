PalletTown_House2_hns_MapScripts::
	.byte 0

PalletTown_House2_EventScript_Daisy::
	lock
	faceplayer
	goto_if_unset FLAG_HIDE_CINNABAR_BLUE, PalletTown_House2_EventScript_Blue
	goto_if_unset FLAG_DAILY_DAISY_GROOMED, PalletTown_House2_EventScript_DaisyGrooming
	msgbox PalletTown_House2_Text_AlreadyGroomed, MSGBOX_DEFAULT
	closemessage
	release
	end

PalletTown_House2_EventScript_Blue::
	msgbox PalletTown_House2_Text_Hello, MSGBOX_DEFAULT
	closemessage
	release
	end

PalletTown_House2_EventScript_DaisyDeclineGrooming::
	msgbox PalletTown_House2_Text_Refused, MSGBOX_DEFAULT
	closemessage
	release
	end
PalletTown_House2_EventScript_Egg::
	msgbox PalletTown_House2_Text_CantGroomEgg, MSGBOX_DEFAULT
	closemessage
	release
	end

PalletTown_House2_EventScript_DaisyGrooming::
	msgbox PalletTown_House2_Text_OfferGrooming, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, PalletTown_House2_EventScript_DaisyDeclineGrooming
	msgbox PalletTown_House2_Text_WhichMon, MSGBOX_DEFAULT
	special ChoosePartyMon
	waitstate
	lock
	faceplayer
	bufferpartymonnick STR_VAR_1, VAR_0x8004
	goto_if_ge VAR_0x8004, PARTY_SIZE, PalletTown_House2_EventScript_DaisyDeclineGrooming
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
	goto_if_eq VAR_RESULT, SPECIES_EGG, PalletTown_House2_EventScript_Egg
	goto_if_eq VAR_RESULT, FALSE, PalletTown_House2_EventScript_DaisyDeclineGrooming
	
	msgbox PalletTown_House2_Text_Alright
	closemessage
	fadescreen FADE_TO_BLACK
	playfanfare MUS_HEAL
	waitfanfare
	special HaircutBrother1
	fadescreen FADE_FROM_BLACK
	special BufferMonNickname
	msgbox PalletTown_House2_Text_AllDone
	setflag FLAG_DAILY_DAISY_GROOMED
	release
	end

PalletTown_House2_Text_Hello:
	.string "דייזי: היי! אחי הקטן הוא מנהיג\n"
	.string "המכון בעיר וירידיאן.\p"
	.string "אבל הוא יוצא מהעיר לעתים כל כך\n"
	.string "קרובות, שזה גורם בעיות למאמנים.$"

PalletTown_House2_Text_OfferGrooming:
	.string "דייזי: היי! הגעת בזמן טוב.\n"
	.string "אני עומדת לשתות תה.\p"
	.string "תרצה להצטרף אליי?\p"
	.string "אוי, הפוקימונים שלך קצת מלוכלכים.\p"
	.string "תרצה שאטפח אחד מהם?$"

PalletTown_House2_Text_WhichMon:
	.string "דייזי: את מי מהם לטפח?$"

PalletTown_House2_Text_Alright:
	.string "דייזי: בסדר, אני אדאג שהוא ייראה\n"
	.string "נהדר תוך רגע.$"

PalletTown_House2_Text_AllDone:
	.string "דייזי: הנה! סיימתי.\p"
	.string "רואה? {STR_VAR_1} נראה נהדר,\n"
	.string "נכון?\p"
	.string "זה פוקימון כל כך חמוד.$"

PalletTown_House2_Text_AlreadyGroomed:
	.string "דייזי: אני תמיד שותה תה\n"
	.string "בשעה הזאת. בוא להצטרף אליי.$"

PalletTown_House2_Text_Refused:
	.string "דייזי: לא רוצה שאטפח\n"
	.string "אחד מהם?\p"
	.string "בסדר, אז רק נשתה תה.$"

PalletTown_House2_Text_CantGroomEgg:
	.string "דייזי: אוי, סליחה. אני באמת\n"
	.string "לא יכולה לטפח ביצה.$"
