Route34_DayCare_hns_MapScripts::
	.byte 0

Route34_DayCare_Bookshelf1::
	lock
	msgbox Route34_DayCare_Text_Bookshelf1, MSGBOX_AUTOCLOSE
	helpwindow HELP_DAYCARE1_WINDOW
	release
	end

Route34_DayCare_Bookshelf2::
	lock
	msgbox Route34_DayCare_Text_Bookshelf2, MSGBOX_AUTOCLOSE
	helpwindow HELP_DAYCARE2_WINDOW
	release
	end

Route34_DayCare_Bookshelf3::
	lock
	msgbox Route34_DayCare_Text_Bookshelf3, MSGBOX_AUTOCLOSE
	helpwindow HELP_DAYCARE3_WINDOW
	release
	end

Route34_DayCare_Bookshelf4::
	lock
	msgbox Route34_DayCare_Text_Bookshelf4, MSGBOX_AUTOCLOSE
	helpwindow HELP_DAYCARE4_WINDOW
	release
	end

Route34_DayCare_Text_Bookshelf1:
	.string "אנציקלופדיה של פוקימונים תינוקות!\p"
	.string "כרך 1: הכול על יכולות$"

Route34_DayCare_Text_Bookshelf2:
	.string "אנציקלופדיה של פוקימונים תינוקות!\p"
	.string "כרך 2: סוגים טיפוסיים$"

Route34_DayCare_Text_Bookshelf3:
	.string "אנציקלופדיה של פוקימונים תינוקות!\p"
	.string "כרך 3: קריאות התינוקות$"

Route34_DayCare_Text_Bookshelf4:
	.string "אנציקלופדיה של פוקימונים תינוקות!\p"
	.string "כרך 4: פעולות מקסימות$"

Route34_DayCare_EventScript_Clerk::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_ODD_EGG, Route34_DayCare_EventScript_ClerkAfter
	msgbox Route34_DayCare_Text_ClerkBefore, MSGBOX_DEFAULT
	specialvar VAR_0x8004, GetMaxPartySize @ tx_randomizer_and_challenges
	getpartysize
	goto_if_eq VAR_RESULT, VAR_0x8004, Route34_DayCare_EventScript_ClerkPartyFull
	msgbox Route34_DayCare_Text_ClerkQuestion, MSGBOX_DEFAULT
	closemessage
	setvar VAR_0x8004, EASY_CHAT_TYPE_INTERVIEW
	setvar VAR_0x8005, 0
	call Common_ShowEasyChatScreen
	lock
	faceplayer
	switch VAR_RESULT
	case 0, Route34_DayCare_EventScript_ClerkRejection
	case 1, Route34_DayCare_EventScript_GivePichu
	case 2, Route34_DayCare_EventScript_GiveCleffa
	case 3, Route34_DayCare_EventScript_GiveIgglybuff
	case 4, Route34_DayCare_EventScript_GiveTyrogue
	case 5, Route34_DayCare_EventScript_GiveSmoochum
	case 6, Route34_DayCare_EventScript_GiveElekid
	case 7, Route34_DayCare_EventScript_GiveMagby
	case 8, Route34_DayCare_EventScript_GiveMantyke
	case 9, Route34_DayCare_EventScript_GiveBonsly
	case 10, Route34_DayCare_EventScript_GiveHappiny
	case 11, Route34_DayCare_EventScript_GiveMimeJr
	closemessage
	release
	end

Route34_DayCare_EventScript_GivePichu::
	giveoddegg 1
	goto Route34_DayCare_EventScript_Clerk_GaveEgg

Route34_DayCare_EventScript_GiveCleffa::
	giveoddegg 2
	goto Route34_DayCare_EventScript_Clerk_GaveEgg

Route34_DayCare_EventScript_GiveIgglybuff::
	giveoddegg 3
	goto Route34_DayCare_EventScript_Clerk_GaveEgg

Route34_DayCare_EventScript_GiveTyrogue::
	giveoddegg 4
	goto Route34_DayCare_EventScript_Clerk_GaveEgg

Route34_DayCare_EventScript_GiveSmoochum::
	giveoddegg 5
	goto Route34_DayCare_EventScript_Clerk_GaveEgg

Route34_DayCare_EventScript_GiveElekid::
	giveoddegg 6
	goto Route34_DayCare_EventScript_Clerk_GaveEgg

Route34_DayCare_EventScript_GiveMagby::
	giveoddegg 7
	goto Route34_DayCare_EventScript_Clerk_GaveEgg

Route34_DayCare_EventScript_GiveMantyke::
	giveoddegg 8
	goto Route34_DayCare_EventScript_Clerk_GaveEgg

Route34_DayCare_EventScript_GiveBonsly::
	giveoddegg 9
	goto Route34_DayCare_EventScript_Clerk_GaveEgg

Route34_DayCare_EventScript_GiveHappiny::
	giveoddegg 10
	goto Route34_DayCare_EventScript_Clerk_GaveEgg

Route34_DayCare_EventScript_GiveMimeJr::
	giveoddegg 11
	goto Route34_DayCare_EventScript_Clerk_GaveEgg

Route34_DayCare_EventScript_Clerk_GaveEgg::
	msgbox Route34_DayCare_Text_TakeCare, MSGBOX_DEFAULT
	closemessage
	delay 30
	setflag FLAG_RECEIVED_ODD_EGG
	playfanfare MUS_RG_OBTAIN_KEY_ITEM
	message Route34_DayCare_Text_ReceivedOddEgg
	waitfanfare
	closemessage
	release
	end

Route34_DayCare_EventScript_ClerkPartyFull::
	msgbox Route34_DayCare_Text_ClerkNoRoom, MSGBOX_DEFAULT
	closemessage
	release
	end

Route34_DayCare_EventScript_ClerkRejection::
	msgbox Route34_DayCare_Text_Rejection, MSGBOX_DEFAULT
	closemessage
	release
	end

Route34_DayCare_EventScript_ClerkAfter::
	msgbox Route34_DayCare_Text_ClerkAfter, MSGBOX_DEFAULT
	closemessage
	release
	end

Route34_DayCare_Text_ClerkBefore:
	.string "אני הבן של הזוג ממעון היום.\p"
	.string "ביצה מוזרה נמצאה אצל פוקימון\n"
	.string "של מאמן, אבל לא רצו אותה…\p"
	.string "הייתי מציע אותה לך… אבל איך\n"
	.string "אדע שתטפל בה היטב?$"

Route34_DayCare_Text_ClerkNoRoom:
	.string "נראה שבכל מקרה אין לך\n"
	.string "מקום לעוד פוקימון.$"

Route34_DayCare_Text_ClerkQuestion:
	.string "ענה לי על השאלה הבאה.\n"
	.string "מה דעתך על הביצה המוזרה הזו?$"

Route34_DayCare_Text_Rejection:
	.string "הממ, נראה לי שהביצה הזו לא בשבילך.\p"
	.string "זה יהיה חוסר אחריות לתת ביצה יקרה כזו\n"
	.string "למי שלא קרא מספיק על פוקימונים תינוקות!$"

Route34_DayCare_Text_ReceivedOddEgg:
	.string "{PLAYER} קיבל את הביצה המוזרה.$"

Route34_DayCare_Text_TakeCare:
	.string "ידעתי שאתה המאמן המתאים\n"
	.string "למשימה. תטפל בה היטב!$"

Route34_DayCare_Text_ClerkAfter:
	.string "אנחנו רואים פה הרבה\n"
	.string "ביצים כאלה.\p"
	.string "אבל משהו בביצה ההיא\n"
	.string "היה שונה.$"

Route34_DayCare_EventScript_Ditto::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_DITTO, CRY_MODE_NORMAL
	msgbox Route34_DayCare_Text_Ditto, MSGBOX_DEFAULT
	waitmoncry
	release
	end

Route34_DayCare_Text_Ditto:
	.string "דיטו: טו!$"

Route34_EventScript_DaycareMan::
	lock
	faceplayer
	specialvar VAR_RESULT, IsPartyLimitChallengeActive @ tx_randomizer_and_challenges
	goto_if_eq VAR_RESULT, TRUE, Route34_DayCare_EventScript_ClosedForChallenge
	special GetDaycareMonNicknames
	specialvar VAR_RESULT, GetDaycareState
	goto_if_eq VAR_RESULT, DAYCARE_EGG_WAITING, Route34_EventScript_DaycareEggWaiting
	goto_if_eq VAR_RESULT, DAYCARE_ONE_MON, Route34_EventScript_CheckOnOneMon
	goto_if_eq VAR_RESULT, DAYCARE_TWO_MONS, Route34_EventScript_CheckOnTwoMons
	msgbox Route34_Text_SeeWifeIfYoudLikeMeToRaiseMon, MSGBOX_DEFAULT
	release
	end

Route34_EventScript_DaycareEggWaiting::
	msgbox Route34_Text_DoYouWantEgg, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route34_EventScript_DaycareAcceptEgg
	msgbox Route34_Text_IWillKeepDoYouWantIt, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route34_EventScript_DaycareAcceptEgg
	msgbox Route34_Text_IllKeepIt, MSGBOX_DEFAULT
	clearflag FLAG_PENDING_DAYCARE_EGG
	special RejectEggFromDayCare
	release
	end

Route34_EventScript_DaycareAcceptEgg::
	specialvar VAR_0x8004, GetMaxPartySize @ tx_randomizer_and_challenges
	specialvar VAR_RESULT, CalculatePlayerPartyCount
	goto_if_ne VAR_RESULT, VAR_0x8004, Route34_EventScript_DaycareReceiveEgg
	msgbox Route34_Text_YouHaveNoRoomForIt, MSGBOX_DEFAULT
	release
	end

Route34_EventScript_DaycareReceiveEgg::
	message Route34_Text_ReceivedEgg
	playfanfare MUS_HG_OBTAIN_EGG
	waitfanfare
	waitbuttonpress
	msgbox Route34_Text_TakeGoodCareOfIt, MSGBOX_DEFAULT
	special GiveEggFromDaycare
	clearflag FLAG_PENDING_DAYCARE_EGG
	release
	end

Route34_EventScript_CheckMonReceivedMail::
	specialvar VAR_RESULT, CheckDaycareMonReceivedMail
	call_if_eq VAR_RESULT, 1, Route34_EventScript_MonReceivedMail
	return

Route34_EventScript_MonReceivedMail::
	msgbox Route34_Text_FriendlyWithOtherTrainersMon, MSGBOX_DEFAULT
	return

Route34_EventScript_CheckOnOneMon::
	special GetDaycareMonNicknames
	msgbox Route34_Text_YourMonIsDoingFine, MSGBOX_DEFAULT
	setvar VAR_0x8004, 0
	call Route34_EventScript_CheckMonReceivedMail
	release
	end

Route34_EventScript_CheckOnTwoMons::
	special GetDaycareMonNicknames
	msgbox Route34_Text_YourMonsAreDoingFine, MSGBOX_DEFAULT
	special SetDaycareCompatibilityString
	special ShowFieldMessageStringVar4
	waitmessage
	waitbuttonpress
	setvar VAR_0x8004, 0
	call Route34_EventScript_CheckMonReceivedMail
	setvar VAR_0x8004, 1
	call Route34_EventScript_CheckMonReceivedMail
	release
	end

Route34_DayCare_EventScript_DaycareWoman::
	lock
	faceplayer
	specialvar VAR_RESULT, IsPartyLimitChallengeActive @ tx_randomizer_and_challenges
	goto_if_eq VAR_RESULT, TRUE, Route34_DayCare_EventScript_ClosedForChallenge
	specialvar VAR_RESULT, GetDaycareState
	goto_if_eq VAR_RESULT, DAYCARE_EGG_WAITING, Route34_DayCare_EventScript_EggWaiting
	goto_if_eq VAR_RESULT, DAYCARE_ONE_MON, Route34_DayCare_EventScript_OneMonInDaycare
	goto_if_eq VAR_RESULT, DAYCARE_TWO_MONS, Route34_DayCare_EventScript_TwoMonsInDaycare
	msgbox Route34_DayCare_Text_WouldYouLikeUsToRaiseAMon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route34_DayCare_EventScript_GiveMonToRaise
	msgbox Route34_DayCare_Text_FineThenComeAgain, MSGBOX_DEFAULT
	release
	end

Route34_DayCare_EventScript_GiveMonToRaise::
	specialvar VAR_RESULT, CountPartyNonEggMons
	goto_if_eq VAR_RESULT, 1, Route34_DayCare_EventScript_OnlyOneMon
	specialvar VAR_RESULT, CountPartyAliveNonEggMons
	goto_if_eq VAR_RESULT, 2, Route34_DayCare_EventScript_OnlyTwoAliveMons
	msgbox Route34_DayCare_Text_WhichMonShouldWeRaise, MSGBOX_DEFAULT
	fadescreen FADE_TO_BLACK
	special ChooseSendDaycareMon
	waitstate
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, Route34_DayCare_EventScript_ComeAgain
	specialvar VAR_RESULT, CountPartyAliveNonEggMons_IgnoreVar0x8004Slot
	goto_if_eq VAR_RESULT, 0, Route34_DayCare_EventScript_OnlyOneAliveMon
	specialvar VAR_0x8005, GetSelectedMonNicknameAndSpecies
	waitse
	playmoncry VAR_0x8005, CRY_MODE_NORMAL
	msgbox Route34_DayCare_Text_WellRaiseYourMon, MSGBOX_DEFAULT
	waitmoncry
	special StoreSelectedPokemonInDaycare
	callnative UpdateFollowingPokemon
	incrementgamestat GAME_STAT_USED_DAYCARE
	specialvar VAR_RESULT, GetDaycareState
	goto_if_eq VAR_RESULT, DAYCARE_ONE_MON, Route34_DayCare_EventScript_CanRaiseOneMore
	release
	end

Route34_DayCare_EventScript_ComeAgain::
	msgbox Route34_DayCare_Text_ComeAgain, MSGBOX_DEFAULT
	release
	end

Route34_DayCare_EventScript_CanRaiseOneMore::
	msgbox Route34_DayCare_Text_WeCanRaiseOneMore, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route34_DayCare_EventScript_GiveMonToRaise
	goto Route34_DayCare_EventScript_ComeAgain
	end

Route34_DayCare_EventScript_ClosedForChallenge::
	msgbox Route34_DayCare_Text_ClosedForChallenge, MSGBOX_DEFAULT
	release
	end

Route34_DayCare_Text_ClosedForChallenge:
	.string "מצטערים, בזמן אתגר הגבלת קבוצה\n"
	.string "לא נוכל לשמור על הפוקימונים שלך!$"

Route34_DayCare_EventScript_OnlyOneMon::
	msgbox Route34_DayCare_Text_YouHaveJustOneMon, MSGBOX_DEFAULT
	release
	end

Route34_DayCare_EventScript_OnlyOneAliveMon::
	msgbox Route34_DayCare_Text_WhatWillYouBattleWith, MSGBOX_DEFAULT
	release
	end

Route34_DayCare_EventScript_OnlyTwoAliveMons::
	msgbox Route34_DayCare_Text_YoullBeLeftWithJustOne, MSGBOX_DEFAULT
	release
	end

Route34_DayCare_EventScript_EggWaiting::
	msgbox Route34_DayCare_Text_HusbandWasLookingForYou, MSGBOX_DEFAULT
	release
	end

Route34_DayCare_EventScript_YourMonHasGrownXLevels::
	msgbox Route34_DayCare_Text_YourMonHasGrownXLevels, MSGBOX_DEFAULT
	return

Route34_DayCare_EventScript_DisplayLevelsGained::
	specialvar VAR_RESULT, GetNumLevelsGainedFromDaycare
	call_if_ne VAR_RESULT, 0, Route34_DayCare_EventScript_YourMonHasGrownXLevels
	return

Route34_DayCare_EventScript_OneMonInDaycare::
	msgbox Route34_DayCare_Text_GoodToSeeYou, MSGBOX_DEFAULT
	setvar VAR_0x8004, 0
	call Route34_DayCare_EventScript_DisplayLevelsGained
	msgbox Route34_DayCare_Text_WeCanRaiseOneMore, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route34_DayCare_EventScript_GiveMonToRaise
	msgbox Route34_DayCare_Text_TakeYourMonBack, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route34_DayCare_EventScript_TryRetrieveMon
	goto Route34_DayCare_EventScript_ComeAgain
	end

Route34_DayCare_EventScript_TryRetrieveMon::
	specialvar VAR_0x8004, GetMaxPartySize @ tx_randomizer_and_challenges
	specialvar VAR_RESULT, CalculatePlayerPartyCount
	goto_if_eq VAR_RESULT, VAR_0x8004, Route34_DayCare_EventScript_NoRoom
	specialvar VAR_RESULT, GetDaycareState
	setvar VAR_0x8004, 0
	goto_if_eq VAR_RESULT, DAYCARE_ONE_MON, Route34_DayCare_EventScript_CostPrompt
	special ShowDaycareLevelMenu
	waitstate
	copyvar VAR_0x8004, VAR_RESULT
	goto_if_eq VAR_RESULT, DAYCARE_EXITED_LEVEL_MENU, Route34_DayCare_EventScript_ComeAgain
	goto Route34_DayCare_EventScript_CostPrompt
	end

Route34_DayCare_EventScript_CostPrompt::
	special GetDaycareCost
	msgbox Route34_DayCare_Text_ItWillCostX, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route34_DayCare_EventScript_CheckEnoughMoney
	goto Route34_DayCare_EventScript_ComeAgain
	end

Route34_DayCare_EventScript_CheckEnoughMoney::
	specialvar VAR_RESULT, IsEnoughForCostInVar0x8005
	goto_if_eq VAR_RESULT, 1, Route34_DayCare_EventScript_RetrieveMon
	msgbox Route34_DayCare_Text_NotEnoughMoney, MSGBOX_DEFAULT
	release
	end

Route34_DayCare_EventScript_RetrieveMon::
	@applymovement LOCALID_DAYCARE_LADY, Route34_DayCare_Movement_RetrieveDaycareMon
	@waitmovement 0
	specialvar VAR_RESULT, TakePokemonFromDaycare
	special SubtractMoneyFromVar0x8005
	playse SE_SHOP
	msgbox Route34_DayCare_Text_HeresYourMon, MSGBOX_DEFAULT
	waitse
	playmoncry VAR_RESULT, CRY_MODE_NORMAL
	msgbox Route34_DayCare_Text_TookBackMon, MSGBOX_DEFAULT
	waitmoncry
	specialvar VAR_RESULT, GetDaycareState
	goto_if_eq VAR_RESULT, DAYCARE_ONE_MON, Route34_DayCare_EventScript_AskRetrieveOtherMon
	goto Route34_DayCare_EventScript_ComeAgain
	end

Route34_DayCare_EventScript_AskRetrieveOtherMon::
	msgbox Route34_DayCare_Text_TakeOtherOneBackToo, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route34_DayCare_EventScript_TryRetrieveMon
	goto Route34_DayCare_EventScript_ComeAgain
	end

Route34_DayCare_EventScript_NoRoom::
	msgbox Route34_DayCare_Text_YourTeamIsFull, MSGBOX_DEFAULT
	release
	end

Route34_DayCare_Movement_RetrieveDaycareMon:
	delay_16
	delay_16
	face_left
	delay_16
	delay_16
	face_right
	delay_16
	delay_16
	face_up
	walk_slow_up
	set_invisible
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	face_down
	set_visible
	walk_slow_down
	step_end

@ Unused. Possibly a commented script, or a typo end added to the above Movement script
Route34_DayCare_EventScript_UnusedEnd::
	end

Route34_DayCare_EventScript_TwoMonsInDaycare::
	msgbox Route34_DayCare_Text_GoodToSeeYou, MSGBOX_DEFAULT
	setvar VAR_0x8004, 0
	call Route34_DayCare_EventScript_DisplayLevelsGained
	setvar VAR_0x8004, 1
	call Route34_DayCare_EventScript_DisplayLevelsGained
	msgbox Route34_DayCare_Text_TakeYourMonBack, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route34_DayCare_EventScript_TryRetrieveMon
	msgbox Route34_DayCare_Text_ComeAgain, MSGBOX_DEFAULT
	release
	end

Route34_Text_SeeWifeIfYoudLikeMeToRaiseMon:
	.string "אני האיש ממעון היום.\p"
	.string "אני עוזר לטפל בפוקימונים\n"
	.string "היקרים של מאמנים.\p"
	.string "אם תרצה שאגדל את הפוקימון\n"
	.string "שלך, דבר עם אשתי.$"

Route34_Text_DoYouWantEgg:
	.string "אה, זה אתה!\p"
	.string "גידלנו את הפוקימונים שלך,\n"
	.string "ואוי, כמה שהופתענו!\p"
	.string "לפוקימון שלך הייתה ביצה!\p"
	.string "אנחנו לא יודעים מאיפה היא הגיעה,\n"
	.string "אבל היא הייתה אצל הפוקימון שלך.\p"
	.string "אתה רוצה אותה, נכון?$"

Route34_Text_YourMonIsDoingFine:
	.string "אה, זה אתה! טוב לראות אותך.\n"
	.string "{STR_VAR_1} שלך במצב מצוין.$"

Route34_Text_IllKeepIt:
	.string "טוב, אז אשמור אותה.\n"
	.string "תודה!$"

Route34_Text_YouHaveNoRoomForIt:
	.string "אין לך מקום בשבילה…\n"
	.string "תחזור כשתפנה מקום.$"

Route34_Text_ReceivedEgg:
	.string "{PLAYER} קיבל את הביצה\n"
	.string "מהאיש ממעון היום.$"

Route34_Text_TakeGoodCareOfIt:
	.string "תטפל בה היטב.$"

Route34_Text_FriendlyWithOtherTrainersMon:
	.string "דרך אגב, לגבי {STR_VAR_1} שלך…\p"
	.string "נראה שהוא התיידד עם הפוקימון\n"
	.string "של {STR_VAR_2}, {STR_VAR_3}.\p"
	.string "אולי אפילו ראיתי אותו\n"
	.string "מקבל דואר.$"

@ Unused
Route34_Text_SeeWifeIfYouWantToPickUpMon:
	.string "If you want to pick up your POKéMON,\n"
	.string "have a word with my wife.$"

Route34_Text_YourMonsAreDoingFine:
	.string "אה, זה אתה! {STR_VAR_1} שלך\n"
	.string "ו{STR_VAR_2} במצב מצוין.$"

Route34_Text_IWillKeepDoYouWantIt:
	.string "אני באמת אשמור אותה.\n"
	.string "אתה כן רוצה אותה, נכון?$"

Route34_DayCare_Text_WouldYouLikeUsToRaiseAMon:
	.string "אני הגברת ממעון היום.\p"
	.string "אנחנו יכולים לגדל\n"
	.string "פוקימונים בשבילך.\p"
	.string "תרצה שנגדל אחד?$"

Route34_DayCare_Text_WhichMonShouldWeRaise:
	.string "איזה פוקימון לגדל\n"
	.string "בשבילך?$"

Route34_DayCare_Text_WellRaiseYourMon:
	.string "בסדר, נגדל את {STR_VAR_1} שלך\n"
	.string "לזמן מה.\p"
	.string "תחזור לקחת אותו מאוחר יותר.$"

Route34_DayCare_Text_WeCanRaiseOneMore:
	.string "נוכל לגדל שניים מהפוקימונים שלך.\n"
	.string "תרצה שנגדל עוד אחד?$"

Route34_DayCare_Text_HusbandWasLookingForYou:
	.string "בעלי חיפש אותך.$"

Route34_DayCare_Text_FineThenComeAgain:
	.string "אה, טוב, בסדר.\n"
	.string "בוא שוב.$"

Route34_DayCare_Text_NotEnoughMoney:
	.string "אין לך מספיק כסף…$"

Route34_DayCare_Text_TakeOtherOneBackToo:
	.string "תיקח בחזרה גם\n"
	.string "את השני?$"

Route34_DayCare_Text_ComeAgain:
	.string "בסדר.\n"
	.string "בוא שוב.$"

Route34_DayCare_Text_GoodToSeeYou:
	.string "אה, זה אתה! טוב לראות אותך.\n"
	.string "אצלנו לפוקימונים תמיד טוב!$"

Route34_DayCare_Text_YourMonHasGrownXLevels:
	.string "{STR_VAR_1} שלך עלה\n"
	.string "במספר רמות: {STR_VAR_2}.$"

Route34_DayCare_Text_YourTeamIsFull:
	.string "קבוצת הפוקימונים שלך מלאה.\n"
	.string "פנה מקום, ואז בוא אליי.$"

@ Unused
Route34_DayCare_Text_TakeBackWhichMon:
	.string "Which POKéMON will you take back?$"

Route34_DayCare_Text_ItWillCostX:
	.string "אם תרצה את {STR_VAR_1} שלך בחזרה,\n"
	.string "זה יעלה ¥{STR_VAR_2}.$"

Route34_DayCare_Text_HeresYourMon:
	.string "מצוין!\n"
	.string "הנה הפוקימון שלך.$"

Route34_DayCare_Text_TookBackMon:
	.string "{PLAYER} לקח את {STR_VAR_1}\n"
	.string "בחזרה מהגברת ממעון היום.$"

Route34_DayCare_Text_YouHaveJustOneMon:
	.string "הו? אבל יש לך רק\n"
	.string "פוקימון אחד.\p"
	.string "בוא בפעם אחרת.$"

Route34_DayCare_Text_TakeYourMonBack:
	.string "תרצה לקחת בחזרה פוקימון שלך?$"

Route34_DayCare_Text_WhatWillYouBattleWith:
	.string "אם תשאיר אצלי את הפוקימון\n"
	.string "הזה, עם מה תילחם?\p"
	.string "בוא בפעם אחרת.$"

Route34_DayCare_Text_YoullBeLeftWithJustOne:
	.string "מה?\n"
	.string "נו, נו.\p"
	.string "אם תשאיר אצלי את הפוקימון\n"
	.string "הזה, יישאר לך רק אחד.\p"
	.string "לדעתי, עדיף שתתפוס\n"
	.string "עוד כמה.$"
