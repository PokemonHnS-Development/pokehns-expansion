GoldenrodCity_House1_hns_MapScripts::
	.byte 0

GoldenrodCity_NameRatersHouse_EventScript_ToggleShinies::
	lock
	msgbox GoldenrodCity_NameRatersHouse_Text_AskToggleShinies, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, GoldenrodCity_NameRatersHouse_EventScript_ToggleShiniesRefused
	@special ToggleShinyColors
	msgbox GoldenrodCity_NameRatersHouse_Text_ToggleShinies, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_NameRatersHouse_EventScript_ToggleShiniesRefused::
	release
	end

GoldenrodCity_NameRatersHouse_Text_AskToggleShinies:
	.string "Would you like to toggle the Unique\n"
	.string "Shiny Colors setting?$"

GoldenrodCity_NameRatersHouse_Text_ToggleShinies:
	.string "Shiny Colors Toggled!\p"
	.string "View your setting at the CHALLENGE\n"
	.string "VIEWER at any PC.$"

GoldenrodCity_NameRatersHouse_EventScript_RenameRival::
	msgbox GoldenrodCity_NameRatersHouse_Text_RenameRival, MSGBOX_DEFAULT
	closemessage
	special NameRival
	waitstate
	end

GoldenrodCity_NameRatersHouse_Text_RenameRival:
	.string "אלה החדשות…\p"
	.string "המשטרה מחפשת\n"
	.string "את הנער אדום השיער הזה!\p"
	.string "אתה יודע איך קוראים לו?$"

GoldenrodCity_NameRatersHouse_EventScript_NameRater::
	lock
	faceplayer
	msgbox GoldenrodCity_NameRatersHouse_Text_PleasedToRateMonNickname, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, GoldenrodCity_NameRatersHouse_EventScript_ChooseMonToRate
	goto_if_eq VAR_RESULT, NO, GoldenrodCity_NameRatersHouse_EventScript_DeclineNameRate
	end

GoldenrodCity_NameRatersHouse_EventScript_ChooseMonToRate::
	msgbox GoldenrodCity_NameRatersHouse_Text_CritiqueWhichMonNickname, MSGBOX_DEFAULT
	special ChoosePartyMon
	waitstate
	lock
	goto_if_ne VAR_0x8004, PARTY_NOTHING_CHOSEN, GoldenrodCity_NameRatersHouse_EventScript_RateMonNickname
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, GoldenrodCity_NameRatersHouse_EventScript_DeclineNameRate
	end

GoldenrodCity_NameRatersHouse_EventScript_DeclineNameRate::
	msgbox GoldenrodCity_NameRatersHouse_Text_DoVisitAgain, MSGBOX_DEFAULT
	release
	end

GoldenrodCity_NameRatersHouse_EventScript_RateMonNickname::
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
	goto_if_eq VAR_RESULT, SPECIES_EGG, GoldenrodCity_NameRatersHouse_EventScript_CantRateEgg
	special BufferMonNickname
	@special IsMonOTIDNotPlayers
	@goto_if_eq VAR_RESULT, TRUE, GoldenrodCity_NameRatersHouse_EventScript_PlayerNotMonsOT
	@specialvar VAR_RESULT, MonOTNameNotPlayer
	special BufferMonNickname
	@goto_if_eq VAR_RESULT, TRUE, GoldenrodCity_NameRatersHouse_EventScript_PlayerNotMonsOT
	msgbox GoldenrodCity_NameRatersHouse_Text_FineNameSuggestBetterOne, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, GoldenrodCity_NameRatersHouse_EventScript_ChangeNickname
	goto_if_eq VAR_RESULT, NO, GoldenrodCity_NameRatersHouse_EventScript_DeclineNameRate
	end

GoldenrodCity_NameRatersHouse_EventScript_CantRateEgg::
	msgbox GoldenrodCity_NameRatersHouse_Text_ThatIsMerelyAnEgg, MSGBOX_DEFAULT
	release
	end

GoldenrodCity_NameRatersHouse_EventScript_PlayerNotMonsOT::
	msgbox GoldenrodCity_NameRatersHouse_Text_MagnificentName, MSGBOX_DEFAULT
	release
	end

GoldenrodCity_NameRatersHouse_EventScript_ChangeNickname::
	msgbox GoldenrodCity_NameRatersHouse_Text_WhatShallNewNameBe, MSGBOX_DEFAULT
	call Common_EventScript_NameReceivedPartyMon
	specialvar VAR_RESULT, TryPutNameRaterShowOnTheAir
	special BufferMonNickname
	goto_if_eq VAR_RESULT, TRUE, GoldenrodCity_NameRatersHouse_EventScript_NewNameDifferent
	msgbox GoldenrodCity_NameRatersHouse_Text_NameNoDifferentYetSuperior, MSGBOX_DEFAULT
	release
	end

GoldenrodCity_NameRatersHouse_EventScript_NewNameDifferent::
	msgbox GoldenrodCity_NameRatersHouse_Text_MonShallBeKnownAsName, MSGBOX_DEFAULT
	release
	end

GoldenrodCity_NameRatersHouse_Text_PleasedToRateMonNickname:
	.string "שלום, שלום! אני בוחן השמות!\n"
	.string "אני מגיד עתידות לפי שמות!\p"
	.string "אשמח לדרג את הכינוי\n"
	.string "של הפוקימון שלך.$"

GoldenrodCity_NameRatersHouse_Text_CritiqueWhichMonNickname:
	.string "את הכינוי של איזה פוקימון\n"
	.string "תרצה שאבחן?$"

GoldenrodCity_NameRatersHouse_Text_FineNameSuggestBetterOne:
	.string "הממ… {STR_VAR_1}, נכון?\n"
	.string "זה שם נאה למדי שהענקת לו.\p"
	.string "אבל! מה תאמר אם אציע\n"
	.string "שם קצת יותר טוב?$"

GoldenrodCity_NameRatersHouse_Text_WhatShallNewNameBe:
	.string "אה, יופי. אז מה יהיה\n"
	.string "הכינוי החדש?$"

GoldenrodCity_NameRatersHouse_Text_MonShallBeKnownAsName:
	.string "סיימתי! מעכשיו הפוקימון הזה\n"
	.string "ייקרא בשם {STR_VAR_1}!\p"
	.string "זה שם טוב יותר מהקודם!\n"
	.string "איזה מזל יש לך!$"

GoldenrodCity_NameRatersHouse_Text_DoVisitAgain:
	.string "אני מבין.\n"
	.string "אשמח לביקור נוסף.$"

GoldenrodCity_NameRatersHouse_Text_NameNoDifferentYetSuperior:
	.string "סיימתי! מעכשיו הפוקימון הזה\n"
	.string "ייקרא בשם {STR_VAR_1}!\p"
	.string "זה נראה בדיוק כמו קודם,\n"
	.string "ובכל זאת, זה טוב בהרבה!\p"
	.string "איזה מזל יש לך!$"

GoldenrodCity_NameRatersHouse_Text_MagnificentName:
	.string "Hmmm… {STR_VAR_1} it is!\p"
	.string "This is a magnificent nickname!\n"
	.string "It is impeccably beyond reproach!\p"
	.string "You'll do well to cherish your\n"
	.string "{STR_VAR_1} now and beyond.$"

GoldenrodCity_NameRatersHouse_Text_ThatIsMerelyAnEgg:
	.string "נו, נו.\n"
	.string "זו בסך הכול ביצה!$"


