MauvilleCity_PokemonCenter_1F_EventScript_MauvilleOldMan::
	special Script_GetCurrentMauvilleMan
	switch VAR_RESULT
	case MAUVILLE_MAN_BARD, MauvilleCity_PokemonCenter_1F_EventScript_Bard
	case MAUVILLE_MAN_HIPSTER, MauvilleCity_PokemonCenter_1F_EventScript_Hipster
	case MAUVILLE_MAN_TRADER, MauvilleCity_PokemonCenter_1F_EventScript_Trader
	case MAUVILLE_MAN_STORYTELLER, MauvilleCity_PokemonCenter_1F_EventScript_Storyteller
	case MAUVILLE_MAN_GIDDY, MauvilleCity_PokemonCenter_1F_EventScript_Giddy
	end

@ Bard
MauvilleCity_PokemonCenter_1F_EventScript_Bard::
	lock
	faceplayer
	msgbox MauvilleCity_PokemonCenter_1F_Text_WouldYouLikeToHearMySong, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, MauvilleCity_PokemonCenter_1F_EventScript_PlaySong
	goto_if_eq VAR_RESULT, NO, MauvilleCity_PokemonCenter_1F_EventScript_DeclineSong
	end

MauvilleCity_PokemonCenter_1F_EventScript_PlaySong::
	setvar VAR_0x8004, FALSE  @ Play his current song
	special PlayBardSong
	delay 60
	special HasBardSongBeenChanged
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_PokemonCenter_1F_EventScript_AskToWriteLyrics
	msgbox MauvilleCity_PokemonCenter_1F_Text_WishICouldPlaySongForOthers, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_DeclineSong::
	msgbox MauvilleCity_PokemonCenter_1F_Text_BardFeelingTheBlues1, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_AskToWriteLyrics::
	msgbox MauvilleCity_PokemonCenter_1F_Text_WouldYouLikeToWriteSomeLyrics, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, MauvilleCity_PokemonCenter_1F_EventScript_WriteLyrics
	goto_if_eq VAR_RESULT, NO, MauvilleCity_PokemonCenter_1F_EventScript_DeclineWritingLyrics
	end

MauvilleCity_PokemonCenter_1F_EventScript_WriteLyrics::
	setvar VAR_0x8004, EASY_CHAT_TYPE_BARD_SONG
	call Common_ShowEasyChatScreen
	lock
	faceplayer
	goto_if_eq VAR_RESULT, 0, MauvilleCity_PokemonCenter_1F_EventScript_DeclineWritingLyrics
	msgbox MauvilleCity_PokemonCenter_1F_Text_LetMeSingItForYou, MSGBOX_DEFAULT
	setvar VAR_0x8004, TRUE  @ Play the new song
	special PlayBardSong
	delay 60
	msgbox MauvilleCity_PokemonCenter_1F_Text_ThatHowYouWantedSongToGo, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MauvilleCity_PokemonCenter_1F_EventScript_WriteLyrics
	special SaveBardSongLyrics
	msgbox MauvilleCity_PokemonCenter_1F_Text_IllSingThisSongForAWhile, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_DeclineWritingLyrics::
	msgbox MauvilleCity_PokemonCenter_1F_Text_BardFeelingTheBlues2, MSGBOX_DEFAULT
	release
	end

@ Hipster
MauvilleCity_PokemonCenter_1F_EventScript_Hipster::
	lock
	faceplayer
	setflag FLAG_UNLOCKED_TRENDY_SAYINGS
	msgbox MauvilleCity_PokemonCenter_1F_Text_TeachWhatsHipAndHappening, MSGBOX_DEFAULT
	special HasHipsterTaughtWord
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_PokemonCenter_1F_EventScript_TryTeachWord
	msgbox MauvilleCity_PokemonCenter_1F_Text_IAlreadyTaughtYou, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_TryTeachWord::
	special HipsterTryTeachWord
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_PokemonCenter_1F_EventScript_TeachWord
	msgbox MauvilleCity_PokemonCenter_1F_Text_IveGotNothingNewToTeach, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_TeachWord::
	msgbox MauvilleCity_PokemonCenter_1F_Text_HaveYouHeardOfWord, MSGBOX_DEFAULT
	special SetHipsterTaughtWord
	release
	end

@ Trader
MauvilleCity_PokemonCenter_1F_Text_WantToTradeDecor:
	.string "Hi, I'm the TRADER.\n"
	.string "Want to trade decorations with me?$"

MauvilleCity_PokemonCenter_1F_Text_TraderFeelingTheBlues:
	.string "Oh…\n"
	.string "You've left me feeling the blues…$"

MauvilleCity_PokemonCenter_1F_Text_WeveAlreadyTraded:
	.string "But we've traded decorations already,\n"
	.string "you and I.$"

MauvilleCity_PokemonCenter_1F_Text_PickADecorItem:
	.string "If you see any decorative item that\n"
	.string "you want of mine, speak up.$"

MauvilleCity_PokemonCenter_1F_Text_YouDontWantAnything:
	.string "You don't want anything?\n"
	.string "I feel unwanted…$"

MauvilleCity_PokemonCenter_1F_Text_OnceBelongedToPlayerDoYouWantIt:
	.string "That decorative item once belonged\n"
	.string "to {STR_VAR_1}.\p"
	.string "Do you want it?$"

MauvilleCity_PokemonCenter_1F_Text_YouDontHaveAnyDecor:
	.string "Uh… Wait a second. You don't have a\n"
	.string "single piece of decoration!$"

MauvilleCity_PokemonCenter_1F_Text_PickTheDecorToTrade:
	.string "Okay, pick the decoration that you'll\n"
	.string "trade to me.$"

MauvilleCity_PokemonCenter_1F_Text_YouDontWantToTrade:
	.string "You won't trade with me?\n"
	.string "I feel unwanted…$"

MauvilleCity_PokemonCenter_1F_Text_YouveNoRoomForThis:
	.string "You've got all the {STR_VAR_2}S that can\n"
	.string "be stored. You've no room for this.$"

MauvilleCity_PokemonCenter_1F_Text_SoWellTradeTheseDecor:
	.string "Okay, so we'll trade my {STR_VAR_3}\n"
	.string "for your {STR_VAR_2}?$"

MauvilleCity_PokemonCenter_1F_Text_ThatDecorIsInUse:
	.string "That piece of decoration is in use.\n"
	.string "You can't trade it.$"

MauvilleCity_PokemonCenter_1F_Text_SendDecorToYourPC:
	.string "Then we'll trade!\n"
	.string "I'll send my decoration to your PC.$"

MauvilleCity_PokemonCenter_1F_Text_CantTradeThatOne:
	.string "Oops! Sorry! That's a really rare\n"
	.string "piece of decoration.\l"
	.string "I can't trade that one away!\p"
	.string "Can I interest you in something else?$"

MauvilleCity_PokemonCenter_1F_EventScript_Trader::
	lock
	faceplayer
	msgbox MauvilleCity_PokemonCenter_1F_Text_WantToTradeDecor, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MauvilleCity_PokemonCenter_1F_EventScript_DeclineTrade
	special GetTraderTradedFlag
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_PokemonCenter_1F_EventScript_AlreadyTraded
	message MauvilleCity_PokemonCenter_1F_Text_PickADecorItem
	waitmessage
	goto MauvilleCity_PokemonCenter_1F_EventScript_PickDecorToReceive
	end

MauvilleCity_PokemonCenter_1F_EventScript_DeclineTrade::
	msgbox MauvilleCity_PokemonCenter_1F_Text_TraderFeelingTheBlues, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_AlreadyTraded::
	msgbox MauvilleCity_PokemonCenter_1F_Text_WeveAlreadyTraded, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_PickDecorToReceive::
	special TraderMenuGetDecoration
	waitstate
	goto_if_eq VAR_0x8004, 0, MauvilleCity_PokemonCenter_1F_EventScript_CancelPickDecor
	goto_if_eq VAR_0x8004, 0xFFFF, MauvilleCity_PokemonCenter_1F_EventScript_InvalidDecor
	msgbox MauvilleCity_PokemonCenter_1F_Text_OnceBelongedToPlayerDoYouWantIt, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MauvilleCity_PokemonCenter_1F_EventScript_PickDifferentDecor
	special DoesPlayerHaveNoDecorations
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_PokemonCenter_1F_EventScript_DontHaveAnyDecor
	goto MauvilleCity_PokemonCenter_1F_EventScript_PickDecorToGive
	end

MauvilleCity_PokemonCenter_1F_EventScript_CancelPickDecor::
	msgbox MauvilleCity_PokemonCenter_1F_Text_YouDontWantAnything, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_InvalidDecor::
	message MauvilleCity_PokemonCenter_1F_Text_CantTradeThatOne
	waitmessage
	goto MauvilleCity_PokemonCenter_1F_EventScript_PickDecorToReceive
	end

MauvilleCity_PokemonCenter_1F_EventScript_PickDifferentDecor::
	message MauvilleCity_PokemonCenter_1F_Text_PickADecorItem
	waitmessage
	goto MauvilleCity_PokemonCenter_1F_EventScript_PickDecorToReceive
	end

MauvilleCity_PokemonCenter_1F_EventScript_DontHaveAnyDecor::
	msgbox MauvilleCity_PokemonCenter_1F_Text_YouDontHaveAnyDecor, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_PickDecorToGive::
	msgbox MauvilleCity_PokemonCenter_1F_Text_PickTheDecorToTrade, MSGBOX_DEFAULT
	special TraderShowDecorationMenu
	waitstate
	goto_if_eq VAR_0x8006, 0, MauvilleCity_PokemonCenter_1F_EventScript_CancelGiveDecor
	goto_if_eq VAR_0x8006, 0xFFFF, MauvilleCity_PokemonCenter_1F_EventScript_DecorInUse
	special IsDecorationCategoryFull
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_PokemonCenter_1F_EventScript_NoRoomForDecor
	msgbox MauvilleCity_PokemonCenter_1F_Text_SoWellTradeTheseDecor, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MauvilleCity_PokemonCenter_1F_EventScript_PickDecorToGive
	special TraderDoDecorationTrade
	msgbox MauvilleCity_PokemonCenter_1F_Text_SendDecorToYourPC, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_CancelGiveDecor::
	msgbox MauvilleCity_PokemonCenter_1F_Text_YouDontWantToTrade, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_DecorInUse::
	msgbox MauvilleCity_PokemonCenter_1F_Text_ThatDecorIsInUse, MSGBOX_DEFAULT
	goto MauvilleCity_PokemonCenter_1F_EventScript_PickDecorToGive
	end

MauvilleCity_PokemonCenter_1F_EventScript_NoRoomForDecor::
	msgbox MauvilleCity_PokemonCenter_1F_Text_YouveNoRoomForThis, MSGBOX_DEFAULT
	release
	end

@ Storyteller
MauvilleCity_PokemonCenter_1F_Text_WillYouHearMyTale:
	.string "I'm the STORYTELLER.\n"
	.string "I'll tell you tales of legendary\l"
	.string "TRAINERS.\p"
	.string "Will you hear my tale?$"

MauvilleCity_PokemonCenter_1F_Text_StorytellerFeelingTheBlues:
	.string "Oh…\n"
	.string "You've left me feeling the blues…$"

MauvilleCity_PokemonCenter_1F_Text_WhichTaleToTell:
	.string "I know of these legends.\n"
	.string "Which tale will you have me tell?$"

MauvilleCity_PokemonCenter_1F_Text_IKnowNoTales:
	.string "But, I know of no legendary TRAINERS.\n"
	.string "Hence, I know no tales.\p"
	.string "Where does one find a TRAINER worthy\n"
	.string "of a legendary tale?$"

MauvilleCity_PokemonCenter_1F_Text_YouDidStatXTimes:
	.string "What's that?!\n"
	.string "You… You…\p"
	.string "{STR_VAR_2}\n"
	.string "{STR_VAR_1} time(s)?!\p"
	.string "That is indeed magnificent!\n"
	.string "It's the birth of a new legend!$"

MauvilleCity_PokemonCenter_1F_Text_CouldThereBeOtherLegends:
	.string "It gets me thinking, could there be\n"
	.string "other TRAINERS with more impressive\l"
	.string "legends awaiting discovery?$"

MauvilleCity_PokemonCenter_1F_Text_HaveYouAnyLegendaryTales:
	.string "Are you a TRAINER?\p"
	.string "Then tell me, have you any tales that\n"
	.string "are even remotely legendary?$"

@ Unused
MauvilleCity_PokemonCenter_1F_Text_HearAnotherLegendaryTale:
	.string "Incidentally… Would you care to hear\n"
	.string "another legendary tale?$"

MauvilleCity_PokemonCenter_1F_Text_NotWorthyOfLegend:
	.string "Hmm…\n"
	.string "I'm not satisfied…\p"
	.string "I wish you would bring me news worthy\n"
	.string "of being called a legend.$"

MauvilleCity_PokemonCenter_1F_Text_IWishMorePeopleWereInterested:
	.string "I wish more people would be interested\n"
	.string "in hearing my epic tales of legendary\l"
	.string "TRAINERS.$"

MauvilleCity_PokemonCenter_1F_Text_SavedGameTitle::
	.string "המאמן שמרבה לשמור$"

MauvilleCity_PokemonCenter_1F_Text_SavedGameAction::
	.string "שמרת את המשחק$"

MauvilleCity_PokemonCenter_1F_Text_SavedGameStory::
	.string "זהו סיפורו של מאמן\n"
	.string "בשם {STR_VAR_3}.\p"
	.string "המאמן הזה שמר את המשחק\n"
	.string "{STR_VAR_1} פעמים!\p"
	.string "מאמן זהיר יותר מ{STR_VAR_3}\n"
	.string "פשוט אי אפשר למצוא!$"

MauvilleCity_PokemonCenter_1F_Text_TrendsStartedTitle::
	.string "המאמן מוביל הטרנדים$"

MauvilleCity_PokemonCenter_1F_Text_TrendsStartedAction::
	.string "התחלת טרנדים$"

MauvilleCity_PokemonCenter_1F_Text_TrendsStartedStory::
	.string "זהו סיפורו של מאמן\n"
	.string "בשם {STR_VAR_3}.\p"
	.string "המאמן הזה התחיל טרנדים חדשים\n"
	.string "{STR_VAR_1} פעמים!\p"
	.string "{STR_VAR_3} מכתיב את הטרנדים\n"
	.string "בכל אזור הואן!$"

MauvilleCity_PokemonCenter_1F_Text_BerriesPlantedTitle::
	.string "המאמן שותל הפירות$"

MauvilleCity_PokemonCenter_1F_Text_BerriesPlantedAction::
	.string "שתלת פירות$"

MauvilleCity_PokemonCenter_1F_Text_BerriesPlantedStory::
	.string "זהו סיפורו של מאמן\n"
	.string "בשם {STR_VAR_3}.\p"
	.string "המאמן הזה שתל פירות\n"
	.string "{STR_VAR_1} פעמים!\p"
	.string "{STR_VAR_3} הוא חובב פירות\n"
	.string "אגדי!$"

MauvilleCity_PokemonCenter_1F_Text_BikeTradesTitle::
	.string "המאמן חובב האופניים$"

MauvilleCity_PokemonCenter_1F_Text_BikeTradesAction::
	.string "החלפת אופניים$"

MauvilleCity_PokemonCenter_1F_Text_BikeTradesStory::
	.string "זהו סיפורו של מאמן\n"
	.string "בשם {STR_VAR_3}.\p"
	.string "המאמן הזה החליף אופניים\n"
	.string "{STR_VAR_1} פעמים!\p"
	.string "{STR_VAR_3} בטח אוהב אופניים\n"
	.string "באהבה עמוקה ולוהטת!$"

MauvilleCity_PokemonCenter_1F_Text_InterviewsTitle::
	.string "המאמן המרואיין$"

MauvilleCity_PokemonCenter_1F_Text_InterviewsAction::
	.string "התראיינת$"

MauvilleCity_PokemonCenter_1F_Text_InterviewsStory::
	.string "זהו סיפורו של מאמן\n"
	.string "בשם {STR_VAR_3}.\p"
	.string "המאמן הזה התראיין\n"
	.string "{STR_VAR_1} פעמים!\p"
	.string "{STR_VAR_3} בטח מאמן\n"
	.string "שמושך הרבה תשומת לב!$"

MauvilleCity_PokemonCenter_1F_Text_TrainerBattlesTitle::
	.string "המאמן חובב הקרבות$"

MauvilleCity_PokemonCenter_1F_Text_TrainerBattlesAction::
	.string "השתתפת בקרבות$"

MauvilleCity_PokemonCenter_1F_Text_TrainerBattlesStory::
	.string "זהו סיפורו של מאמן\n"
	.string "בשם {STR_VAR_3}.\p"
	.string "המאמן הזה נלחם\n"
	.string "{STR_VAR_1} פעמים!\p"
	.string "{STR_VAR_3} בטח מאמן שלעולם\n"
	.string "לא מוותר על הזדמנות לקרב!$"

MauvilleCity_PokemonCenter_1F_Text_PokemonCaughtTitle::
	.string "המאמן לוכד הפוקימונים$"

MauvilleCity_PokemonCenter_1F_Text_PokemonCaughtAction::
	.string "תפסת פוקימונים$"

MauvilleCity_PokemonCenter_1F_Text_PokemonCaughtStory::
	.string "זהו סיפורו של מאמן\n"
	.string "בשם {STR_VAR_3}.\p"
	.string "המאמן הזה תפס\n"
	.string "{STR_VAR_1} פוקימונים!\p"
	.string "{STR_VAR_3} הוא לוכד אגדי\n"
	.string "של פוקימונים פראיים!$"

MauvilleCity_PokemonCenter_1F_Text_FishingPokemonCaughtTitle::
	.string "המאמן הדייג$"

MauvilleCity_PokemonCenter_1F_Text_FishingPokemonCaughtAction::
	.string "תפסת פוקימונים בחכה$"

MauvilleCity_PokemonCenter_1F_Text_FishingPokemonCaughtStory::
	.string "זהו סיפורו של מאמן\n"
	.string "בשם {STR_VAR_3}.\p"
	.string "המאמן הזה תפס\n"
	.string "{STR_VAR_1} פוקימונים בזמן דיג!\p"
	.string "{STR_VAR_3} הוא מומחה דיג\n"
	.string "אגדי!$"

MauvilleCity_PokemonCenter_1F_Text_EggsHatchedTitle::
	.string "המאמן מחמם הביצים$"

MauvilleCity_PokemonCenter_1F_Text_EggsHatchedAction::
	.string "בקעו לך ביצים$"

MauvilleCity_PokemonCenter_1F_Text_EggsHatchedStory::
	.string "זהו סיפורו של מאמן\n"
	.string "בשם {STR_VAR_3}.\p"
	.string "אצל המאמן הזה בקעו\n"
	.string "{STR_VAR_1} פוקימונים מביצים!\p"
	.string "{STR_VAR_3} הוא מחמם ביצים\n"
	.string "אגדי!$"

MauvilleCity_PokemonCenter_1F_Text_PokemonEvolvedTitle::
	.string "המאמן מומחה ההתפתחות$"

MauvilleCity_PokemonCenter_1F_Text_PokemonEvolvedAction::
	.string "הפוקימונים שלך התפתחו$"

MauvilleCity_PokemonCenter_1F_Text_PokemonEvolvedStory::
	.string "זהו סיפורו של מאמן\n"
	.string "בשם {STR_VAR_3}.\p"
	.string "המאמן הזה גרם\n"
	.string "ל-{STR_VAR_1} פוקימונים להתפתח!\p"
	.string "{STR_VAR_3} הוא המומחה העליון\n"
	.string "להתפתחות פוקימונים!$"

MauvilleCity_PokemonCenter_1F_Text_UsedPokemonCenterTitle::
	.string "המאמן חובב מרכזי הפוקימון$"

MauvilleCity_PokemonCenter_1F_Text_UsedPokemonCenterAction::
	.string "השתמשת במרכזי פוקימון$"

MauvilleCity_PokemonCenter_1F_Text_UsedPokemonCenterStory::
	.string "זהו סיפורו של מאמן\n"
	.string "בשם {STR_VAR_3}.\p"
	.string "המאמן הזה ריפא פוקימונים\n"
	.string "{STR_VAR_1} פעמים במרכזי פוקימון!\p"
	.string "אין מי שאוהב את מרכזי הפוקימון\n"
	.string "יותר מ{STR_VAR_3}!$"

MauvilleCity_PokemonCenter_1F_Text_RestedAtHomeTitle::
	.string "המאמן הביתי$"

MauvilleCity_PokemonCenter_1F_Text_RestedAtHomeAction::
	.string "נתת לפוקימונים לנוח בבית$"

MauvilleCity_PokemonCenter_1F_Text_RestedAtHomeStory::
	.string "זהו סיפורו של מאמן\n"
	.string "בשם {STR_VAR_3}.\p"
	.string "המאמן הזה ריפא פוקימונים\n"
	.string "{STR_VAR_1} פעמים בבית!\p"
	.string "אין אף אחד ביתי יותר\n"
	.string "מ{STR_VAR_3}!$"

MauvilleCity_PokemonCenter_1F_Text_SafariGamesTitle::
	.string "המאמן חובב הספארי$"

MauvilleCity_PokemonCenter_1F_Text_SafariGamesAction::
	.string "נכנסת לאזור הספארי$"

MauvilleCity_PokemonCenter_1F_Text_SafariGamesStory::
	.string "זהו סיפורו של מאמן\n"
	.string "בשם {STR_VAR_3}.\p"
	.string "המאמן הזה נכנס לאזור הספארי\n"
	.string "{STR_VAR_1} פעמים!\p"
	.string "{STR_VAR_3} הוא מאמן שהצד הפראי\n"
	.string "שלו בטח מתגלה באזור הספארי!$"

MauvilleCity_PokemonCenter_1F_Text_UsedCutTitle::
	.string "המאמן שחותך בטירוף$"

MauvilleCity_PokemonCenter_1F_Text_UsedCutAction::
	.string "השתמשת בחיתוך$"

MauvilleCity_PokemonCenter_1F_Text_UsedCutStory::
	.string "זהו סיפורו של מאמן\n"
	.string "בשם {STR_VAR_3}.\p"
	.string "המאמן הזה השתמש בחיתוך\n"
	.string "{STR_VAR_1} פעמים!\p"
	.string "{STR_VAR_3} בטח מאמן\n"
	.string "שפשוט אוהב לחתוך!$"

MauvilleCity_PokemonCenter_1F_Text_UsedRockSmashTitle::
	.string "המאמן מנפץ הסלעים$"

MauvilleCity_PokemonCenter_1F_Text_UsedRockSmashAction::
	.string "ניפצת סלעים$"

MauvilleCity_PokemonCenter_1F_Text_UsedRockSmashStory::
	.string "זהו סיפורו של מאמן\n"
	.string "בשם {STR_VAR_3}.\p"
	.string "המאמן הזה השתמש בניפוץ סלע\n"
	.string "{STR_VAR_1} פעמים!\p"
	.string "{STR_VAR_3} בטח מאמן שלא\n"
	.string "משאיר אבן על אבן!$"

MauvilleCity_PokemonCenter_1F_Text_MovedBasesTitle::
	.string "המאמן שאוהב לעבור דירה$"

MauvilleCity_PokemonCenter_1F_Text_MovedBasesAction::
	.string "העברת את הבסיס הסודי$"

MauvilleCity_PokemonCenter_1F_Text_MovedBasesStory::
	.string "זהו סיפורו של מאמן\n"
	.string "בשם {STR_VAR_3}.\p"
	.string "המאמן הזה העביר את הבסיס הסודי\n"
	.string "{STR_VAR_1} פעמים!\p"
	.string "{STR_VAR_3} הוא מאמן שאוהב\n"
	.string "לעבור דירה לעיתים קרובות!$"

MauvilleCity_PokemonCenter_1F_Text_UsedSplashTitle::
	.string "המאמן חובב השכשוך$"

MauvilleCity_PokemonCenter_1F_Text_UsedSplashAction::
	.string "השתמשת בשכשוך$"

MauvilleCity_PokemonCenter_1F_Text_UsedSplashStory::
	.string "זהו סיפורו של מאמן\n"
	.string "בשם {STR_VAR_3}.\p"
	.string "המאמן הזה השתמש בשכשוך\n"
	.string "{STR_VAR_1} פעמים!\p"
	.string "{STR_VAR_3} הוא מאמן שבטח\n"
	.string "אוהב להשתכשך במים!$"

MauvilleCity_PokemonCenter_1F_Text_UsedStruggleTitle::
	.string "המאמן העיקש$"

MauvilleCity_PokemonCenter_1F_Text_UsedStruggleAction::
	.string "נאלצת להשתמש במאבק$"

MauvilleCity_PokemonCenter_1F_Text_UsedStruggleStory::
	.string "זהו סיפורו של מאמן\n"
	.string "בשם {STR_VAR_3}.\p"
	.string "המאמן הזה נאלץ להסתמך על מאבק\n"
	.string "{STR_VAR_1} פעמים!\p"
	.string "{STR_VAR_3} הוא מאמן עיקש\n"
	.string "שלעולם לא נכנע לקשיים!$"

MauvilleCity_PokemonCenter_1F_Text_SlotJackpotsTitle::
	.string "אלוף מכונות המזל$"

MauvilleCity_PokemonCenter_1F_Text_SlotJackpotsAction::
	.string "זכית בקופה הגדולה במכונות המזל$"

MauvilleCity_PokemonCenter_1F_Text_SlotJackpotsStory::
	.string "זהו סיפורו של מאמן\n"
	.string "בשם {STR_VAR_3}.\p"
	.string "המאמן הזה זכה בקופה הגדולה\n"
	.string "במכונות המזל {STR_VAR_1} פעמים.\p"
	.string "{STR_VAR_3} הוא מאמן שהמזל\n"
	.string "האיר לו פנים במכונות המזל!$"

MauvilleCity_PokemonCenter_1F_Text_RouletteWinsTitle::
	.string "אלוף הרולטה$"

MauvilleCity_PokemonCenter_1F_Text_RouletteWinsAction::
	.string "ניצחת ברולטה ברצף$"

MauvilleCity_PokemonCenter_1F_Text_RouletteWinsStory::
	.string "זהו סיפורו של מאמן\n"
	.string "בשם {STR_VAR_3}.\p"
	.string "המאמן הזה ניצח ברולטה\n"
	.string "{STR_VAR_1} פעמים ברציפות.\p"
	.string "ל{STR_VAR_3} היה מזל כשהכדור\n"
	.string "קיפץ ברולטה!$"

MauvilleCity_PokemonCenter_1F_Text_BattleTowerChallengesTitle::
	.string "המתמודד במגדל הקרב$"

MauvilleCity_PokemonCenter_1F_Text_BattleTowerChallengesAction::
	.string "ניגשת לאתגר מגדל הקרב$"

MauvilleCity_PokemonCenter_1F_Text_BattleTowerChallengesStory::
	.string "זהו סיפורו של מאמן\n"
	.string "בשם {STR_VAR_3}.\p"
	.string "המאמן הזה ניגש לאתגר מגדל הקרב\n"
	.string "{STR_VAR_1} פעמים!\p"
	.string "{STR_VAR_3} הוא מאמן ששואף\n"
	.string "למצוינות במגדל הקרב!$"

MauvilleCity_PokemonCenter_1F_Text_MadePokeblocksTitle::
	.string "המאמן חובב הערבול$"

MauvilleCity_PokemonCenter_1F_Text_MadePokeblocksAction::
	.string "הכנת פוקיבלוקים$"

MauvilleCity_PokemonCenter_1F_Text_MadePokeblocksStory::
	.string "זהו סיפורו של מאמן\n"
	.string "בשם {STR_VAR_3}.\p"
	.string "המאמן הזה הכין פוקיבלוקים\n"
	.string "{STR_VAR_1} פעמים!\p"
	.string "אין מי שמשתמש במערבל הפירות\n"
	.string "טוב יותר מ{STR_VAR_3}!$"

MauvilleCity_PokemonCenter_1F_Text_EnteredContestsTitle::
	.string "המאמן חובב התחרויות$"

MauvilleCity_PokemonCenter_1F_Text_EnteredContestsAction::
	.string "השתתפת בתחרויות$"

MauvilleCity_PokemonCenter_1F_Text_EnteredContestsStory::
	.string "זהו סיפורו של מאמן\n"
	.string "בשם {STR_VAR_3}.\p"
	.string "המאמן הזה השתתף בתחרויות\n"
	.string "{STR_VAR_1} פעמים!\p"
	.string "{STR_VAR_3} בטח אוהב להשוויץ\n"
	.string "בפוקימונים שלו מול אחרים!$"

MauvilleCity_PokemonCenter_1F_Text_WonContestsTitle::
	.string "אמן התחרויות$"

MauvilleCity_PokemonCenter_1F_Text_WonContestsAction::
	.string "ניצחת בתחרויות$"

MauvilleCity_PokemonCenter_1F_Text_WonContestsStory::
	.string "זהו סיפורו של מאמן\n"
	.string "בשם {STR_VAR_3}.\p"
	.string "המאמן הזה ניצח בתחרויות\n"
	.string "{STR_VAR_1} פעמים!\p"
	.string "{STR_VAR_3} בטח אמן תחרויות\n"
	.string "מדהים!$"

MauvilleCity_PokemonCenter_1F_Text_TimesShoppedTitle::
	.string "הקונה המאושר$"

MauvilleCity_PokemonCenter_1F_Text_TimesShoppedAction::
	.string "עשית קניות$"

MauvilleCity_PokemonCenter_1F_Text_TimesShoppedStory::
	.string "זהו סיפורו של מאמן\n"
	.string "בשם {STR_VAR_3}.\p"
	.string "המאמן הזה קנה פריטים בחנויות\n"
	.string "{STR_VAR_1} פעמים!\p"
	.string "{STR_VAR_3} בטח אחד מאלה\n"
	.string "שנולדו לעשות קניות.$"

MauvilleCity_PokemonCenter_1F_Text_UsedItemFinderTitle::
	.string "המאמן מוצא הפריטים$"

MauvilleCity_PokemonCenter_1F_Text_UsedItemFinderAction::
	.string "השתמשת בגלאי פריטים$"

MauvilleCity_PokemonCenter_1F_Text_UsedItemFinderStory::
	.string "זהו סיפורו של מאמן\n"
	.string "בשם {STR_VAR_3}.\p"
	.string "המאמן הזה השתמש בגלאי פריטים\n"
	.string "{STR_VAR_1} פעמים!\p"
	.string "{STR_VAR_3} בטח נהנה לסרוק\n"
	.string "את הקרקע בחיפוש אחר פריטים נסתרים!$"

MauvilleCity_PokemonCenter_1F_Text_TimesRainedTitle::
	.string "המאמן ספוג הגשם$"

MauvilleCity_PokemonCenter_1F_Text_TimesRainedAction::
	.string "נרטבת בגשם$"

MauvilleCity_PokemonCenter_1F_Text_TimesRainedStory::
	.string "זהו סיפורו של מאמן\n"
	.string "בשם {STR_VAR_3}.\p"
	.string "המאמן הזה נרטב בגשם\n"
	.string "{STR_VAR_1} פעמים!\p"
	.string "הכריזמה של {STR_VAR_3} בטח\n"
	.string "מושכת אפילו גשם!$"

MauvilleCity_PokemonCenter_1F_Text_CheckedPokedexTitle::
	.string "קורא הפוקדקס הנלהב$"

MauvilleCity_PokemonCenter_1F_Text_CheckedPokedexAction::
	.string "עיינת בפוקדקס$"

MauvilleCity_PokemonCenter_1F_Text_CheckedPokedexStory::
	.string "זהו סיפורו של מאמן\n"
	.string "בשם {STR_VAR_3}.\p"
	.string "המאמן הזה עיין בפוקדקס\n"
	.string "{STR_VAR_1} פעמים!\p"
	.string "{STR_VAR_3} בטח אוהב לבחון\n"
	.string "פוקימונים בפוקדקס!$"

MauvilleCity_PokemonCenter_1F_Text_ReceivedRibbonsTitle::
	.string "אספן הסרטים$"

MauvilleCity_PokemonCenter_1F_Text_ReceivedRibbonsAction::
	.string "קיבלת סרטים$"

MauvilleCity_PokemonCenter_1F_Text_ReceivedRibbonsStory::
	.string "זהו סיפורו של מאמן\n"
	.string "בשם {STR_VAR_3}.\p"
	.string "המאמן הזה קיבל סרטים\n"
	.string "{STR_VAR_1} פעמים!\p"
	.string "{STR_VAR_3} בטח מאמן\n"
	.string "שאוהב לאסוף סרטים!$"

MauvilleCity_PokemonCenter_1F_Text_LedgesJumpedTitle::
	.string "המאמן קופץ מדרגות הסלע$"

MauvilleCity_PokemonCenter_1F_Text_LedgesJumpedAction::
	.string "קפצת ממדרגות סלע$"

MauvilleCity_PokemonCenter_1F_Text_LedgesJumpedStory::
	.string "זהו סיפורו של מאמן\n"
	.string "בשם {STR_VAR_3}.\p"
	.string "המאמן הזה קפץ ממדרגות סלע\n"
	.string "{STR_VAR_1} פעמים!\p"
	.string "אם יש מדרגת סלע לקפוץ ממנה,\n"
	.string "{STR_VAR_3} לא יכול לעמוד בפיתוי!$"

MauvilleCity_PokemonCenter_1F_Text_TVWatchedTitle::
	.string "צופה הטלוויזיה האגדי$"

MauvilleCity_PokemonCenter_1F_Text_TVWatchedAction::
	.string "צפית בטלוויזיה$"

MauvilleCity_PokemonCenter_1F_Text_TVWatchedStory::
	.string "זהו סיפורו של מאמן\n"
	.string "בשם {STR_VAR_3}.\p"
	.string "המאמן הזה צפה בטלוויזיה\n"
	.string "{STR_VAR_1} פעמים!\p"
	.string "{STR_VAR_3} בטח אוהב\n"
	.string "לצפות בטלוויזיה!$"

MauvilleCity_PokemonCenter_1F_Text_CheckedClockTitle::
	.string "המאמן המודע לזמן$"

MauvilleCity_PokemonCenter_1F_Text_CheckedClockAction::
	.string "בדקת את השעה$"

MauvilleCity_PokemonCenter_1F_Text_CheckedClockStory::
	.string "זהו סיפורו של מאמן\n"
	.string "בשם {STR_VAR_3}.\p"
	.string "המאמן הזה בדק את השעה\n"
	.string "{STR_VAR_1} פעמים!\p"
	.string "{STR_VAR_3} בטח מאמן דייקן\n"
	.string "שתמיד מודע לזמן.$"

MauvilleCity_PokemonCenter_1F_Text_WonLotteryTitle::
	.string "אשף הגרלת הפוקימון$"

MauvilleCity_PokemonCenter_1F_Text_WonLotteryAction::
	.string "זכית בהגרלות הפוקימון$"

MauvilleCity_PokemonCenter_1F_Text_WonLotteryStory::
	.string "זהו סיפורו של מאמן\n"
	.string "בשם {STR_VAR_3}.\p"
	.string "המאמן הזה זכה בהגרלות הפוקימון\n"
	.string "{STR_VAR_1} פעמים!\p"
	.string "ל{STR_VAR_3} בטח יש הרבה חברים\n"
	.string "שמחליפים איתו פוקימונים!$"

MauvilleCity_PokemonCenter_1F_Text_UsedDaycareTitle::
	.string "הלקוח הקבוע של מעון היום$"

MauvilleCity_PokemonCenter_1F_Text_UsedDaycareAction::
	.string "השארת פוקימונים במעון היום$"

MauvilleCity_PokemonCenter_1F_Text_UsedDaycareStory::
	.string "זהו סיפורו של מאמן\n"
	.string "בשם {STR_VAR_3}.\p"
	.string "המאמן הזה השאיר פוקימונים\n"
	.string "במעון היום {STR_VAR_1} פעמים!\p"
	.string "{STR_VAR_3} בטח מאמן שאפתני\n"
	.string "שמגדל פוקימונים בנחישות!$"

MauvilleCity_PokemonCenter_1F_Text_RodeCableCarTitle::
	.string "המאמן חובב הרכבל$"

MauvilleCity_PokemonCenter_1F_Text_RodeCableCarAction::
	.string "נסעת ברכבל$"

MauvilleCity_PokemonCenter_1F_Text_RodeCableCarStory::
	.string "זהו סיפורו של מאמן\n"
	.string "בשם {STR_VAR_3}.\p"
	.string "המאמן הזה נסע ברכבל\n"
	.string "{STR_VAR_1} פעמים!\p"
	.string "{STR_VAR_3} בטח מאמן עסוק\n"
	.string "שכל הזמן עולה ויורד!$"

MauvilleCity_PokemonCenter_1F_Text_HotSpringsTitle::
	.string "המאמן חובב המעיינות החמים$"

MauvilleCity_PokemonCenter_1F_Text_HotSpringsAction::
	.string "רחצת במעיינות חמים$"

MauvilleCity_PokemonCenter_1F_Text_HotSpringsStory::
	.string "זהו סיפורו של מאמן\n"
	.string "בשם {STR_VAR_3}.\p"
	.string "המאמן הזה רחץ במעיינות חמים\n"
	.string "{STR_VAR_1} פעמים!\p"
	.string "{STR_VAR_3} בטח מאמן\n"
	.string "עם עור חלק כמו של תינוק!$"


MauvilleCity_PokemonCenter_1F_EventScript_Storyteller::
	lock
	faceplayer
	setvar VAR_0x8008, 0
	setvar VAR_0x8009, 0
	setvar VAR_0x800A, 0
	setvar VAR_0x800B, 0
	msgbox MauvilleCity_PokemonCenter_1F_Text_WillYouHearMyTale, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MauvilleCity_PokemonCenter_1F_EventScript_DeclineStoryteller
	specialvar VAR_RESULT, StorytellerGetFreeStorySlot
	goto_if_eq VAR_RESULT, 0, MauvilleCity_PokemonCenter_1F_EventScript_KnowNoTales
	message MauvilleCity_PokemonCenter_1F_Text_WhichTaleToTell
	waitmessage
	special StorytellerStoryListMenu
	waitstate
	goto_if_eq VAR_RESULT, 0, MauvilleCity_PokemonCenter_1F_EventScript_CancelStorySelection
	setvar VAR_0x8008, 1
	special Script_StorytellerDisplayStory
	waitmessage
	waitbuttonpress
	specialvar VAR_RESULT, StorytellerUpdateStat
	goto_if_eq VAR_RESULT, 0, MauvilleCity_PokemonCenter_1F_EventScript_AreThereOtherTales
	goto MauvilleCity_PokemonCenter_1F_EventScript_TellPlayersTale

MauvilleCity_PokemonCenter_1F_EventScript_CancelStorySelection::
	goto MauvilleCity_PokemonCenter_1F_EventScript_DeclineStoryteller
	end

MauvilleCity_PokemonCenter_1F_EventScript_AreThereOtherTales::
	msgbox MauvilleCity_PokemonCenter_1F_Text_CouldThereBeOtherLegends, MSGBOX_DEFAULT
	specialvar VAR_RESULT, HasStorytellerAlreadyRecorded
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_PokemonCenter_1F_EventScript_StorytellerEnd
	goto MauvilleCity_PokemonCenter_1F_EventScript_DoYouHaveAnyTales

MauvilleCity_PokemonCenter_1F_EventScript_KnowNoTales::
	msgbox MauvilleCity_PokemonCenter_1F_Text_IKnowNoTales, MSGBOX_DEFAULT
MauvilleCity_PokemonCenter_1F_EventScript_DoYouHaveAnyTales::
	msgbox MauvilleCity_PokemonCenter_1F_Text_HaveYouAnyLegendaryTales, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MauvilleCity_PokemonCenter_1F_EventScript_DeclineStoryteller
	specialvar VAR_RESULT, Script_StorytellerInitializeRandomStat
	goto_if_eq VAR_RESULT, 1, MauvilleCity_PokemonCenter_1F_EventScript_TellPlayersTale
	msgbox MauvilleCity_PokemonCenter_1F_Text_NotWorthyOfLegend, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_TellPlayersTale::
	msgbox MauvilleCity_PokemonCenter_1F_Text_YouDidStatXTimes, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_DeclineStoryteller::
	msgbox MauvilleCity_PokemonCenter_1F_Text_StorytellerFeelingTheBlues, MSGBOX_DEFAULT
	release
	end

@ Unused
MauvilleCity_PokemonCenter_1F_EventScript_WaitingForRecordMix::
	msgbox MauvilleCity_PokemonCenter_1F_Text_IWishMorePeopleWereInterested, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_StorytellerEnd::
	release
	end

@ Giddy
MauvilleCity_PokemonCenter_1F_Text_HearMyStory:
	.string "I'm GIDDY!\n"
	.string "I have a scintillating story for you!\p"
	.string "Would you like to hear my story?$"

MauvilleCity_PokemonCenter_1F_Text_GiddyFeelingTheBlues:
	.string "Oh…\n"
	.string "You've left me feeling the blues…$"

MauvilleCity_PokemonCenter_1F_Text_AlsoIWasThinking:
	.string "Also, I was thinking…$"

MauvilleCity_PokemonCenter_1F_Text_WeShouldChatAgain:
	.string "That's about it, I think…\p"
	.string "We should chat again!\n"
	.string "Bye-bye!$"

MauvilleCity_PokemonCenter_1F_EventScript_Giddy::
	lock
	faceplayer
	msgbox MauvilleCity_PokemonCenter_1F_Text_HearMyStory, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, MauvilleCity_PokemonCenter_1F_EventScript_TryTellTale
	goto_if_eq VAR_RESULT, NO, MauvilleCity_PokemonCenter_1F_EventScript_DeclineGiddy
	end

MauvilleCity_PokemonCenter_1F_EventScript_TryTellTale::
	special GiddyShouldTellAnotherTale
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_PokemonCenter_1F_EventScript_GiddyTellTale
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_PokemonCenter_1F_EventScript_ToldEnoughTales
	end

MauvilleCity_PokemonCenter_1F_EventScript_TryTellNewTale::
	special GiddyShouldTellAnotherTale
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_PokemonCenter_1F_EventScript_GiddyStartNewTale
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_PokemonCenter_1F_EventScript_ToldEnoughTales
	end

MauvilleCity_PokemonCenter_1F_EventScript_GiddyStartNewTale::
	msgbox MauvilleCity_PokemonCenter_1F_Text_AlsoIWasThinking, MSGBOX_DEFAULT
	goto MauvilleCity_PokemonCenter_1F_EventScript_GiddyTellTale
	end

@ Giddy will continue to tell stories regardless of whether yes or no is selected below.
@ Each story there is a 10% chance it will be his last. Otherwise he will stop at 10 stories.
MauvilleCity_PokemonCenter_1F_EventScript_GiddyTellTale::
	special GenerateGiddyLine
	special ShowFieldMessageStringVar4
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, YES, MauvilleCity_PokemonCenter_1F_EventScript_TryTellNewTale
	goto_if_eq VAR_RESULT, NO, MauvilleCity_PokemonCenter_1F_EventScript_TryTellNewTale
	end

MauvilleCity_PokemonCenter_1F_EventScript_DeclineGiddy::
	msgbox MauvilleCity_PokemonCenter_1F_Text_GiddyFeelingTheBlues, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_ToldEnoughTales::
	msgbox MauvilleCity_PokemonCenter_1F_Text_WeShouldChatAgain, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_Text_WouldYouLikeToHearMySong:
	.string "Hi, I'm the BARD.\n"
	.string "Would you like to hear my song?$"

MauvilleCity_PokemonCenter_1F_Text_BardFeelingTheBlues1:
	.string "Oh…\n"
	.string "You've left me feeling the blues…$"

MauvilleCity_PokemonCenter_1F_Text_WishICouldPlaySongForOthers:
	.string "Oh, what a moving song…\n"
	.string "I wish I could play it for others…$"

MauvilleCity_PokemonCenter_1F_Text_WouldYouLikeToWriteSomeLyrics:
	.string "So?\n"
	.string "How do you like my song?\p"
	.string "But I'm none too happy about\n"
	.string "the lyrics.\p"
	.string "How would you like to write some\n"
	.string "new lyrics for me?$"

MauvilleCity_PokemonCenter_1F_Text_BardFeelingTheBlues2:
	.string "Oh…\n"
	.string "You've left me feeling the blues…$"

MauvilleCity_PokemonCenter_1F_Text_LetMeSingItForYou:
	.string "Thank you kindly!\n"
	.string "Let me sing it for you.$"

MauvilleCity_PokemonCenter_1F_Text_ThatHowYouWantedSongToGo:
	.string "Was that how you wanted your song\n"
	.string "to go?$"

MauvilleCity_PokemonCenter_1F_Text_IllSingThisSongForAWhile:
	.string "Okay! That's it, then.\n"
	.string "I'll sing this song for a while.$"

MauvilleCity_PokemonCenter_1F_Text_TeachWhatsHipAndHappening:
	.string "Hey, yo! They call me the HIPSTER.\n"
	.string "I'll teach you what's hip and happening.$"

MauvilleCity_PokemonCenter_1F_Text_IAlreadyTaughtYou:
	.string "But, hey, I taught you what's hip and\n"
	.string "happening already.\p"
	.string "I'd like to spread the good word to\n"
	.string "other folks.$"

MauvilleCity_PokemonCenter_1F_Text_IveGotNothingNewToTeach:
	.string "But, hey, you already know a lot about\n"
	.string "what's hip and happening.\p"
	.string "I've got nothing new to teach you!$"

MauvilleCity_PokemonCenter_1F_Text_HaveYouHeardOfWord:
	.string "Hey, have you heard about\n"
	.string "“{STR_VAR_1}”?\p"
	.string "What's it mean? Well…\n"
	.string "Ask your daddy or mommy, okay?$"
