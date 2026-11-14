Route30_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route30_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Route30_OnFrame
	.byte 0

Route30_OnTransition: 
	callnative SetTimeBasedEncounters
	end

Route30_OnFrame::
	map_script_2 VAR_CHERRYGROVE_CITY_STATE, 2, Route30_EventScript_ElmCall_Trigger
	.2byte 0
	
Route30_EventScript_Boy::
	lock
	faceplayer
	goto_if_set FLAG_ADVENTURE_STARTED, Route30_EventScript_Boy2
	msgbox Route30_Text_YoungsterDirectionsToMrPokemon, MSGBOX_DEFAULT
	closemessage
	release
	end

Route30_EventScript_Boy2::
	lock
	faceplayer
	msgbox Route30_Text_YoungsterEveryoneIsBattling, MSGBOX_DEFAULT
	closemessage
	release
	end

Route30_EventScript_Girl::
	lock
	faceplayer
	msgbox Route30_Text_CooltrainerF, MSGBOX_DEFAULT
	closemessage
	release
	end

Route30_EventScript_Youngster_Joey_Fighting::
	lock
	msgbox Route30_Text_UseTackle, 	MSGBOX_AUTOCLOSE
	waitmessage
	playse SE_PIN
	applymovement LOCALID_ROUTE_30_JOEY, Common_Movement_QuestionMark
	delay 55
	waitmovement LOCALID_ROUTE_30_JOEY
	faceplayer
	msgbox Route30_Text_ThisIsABigBattle, MSGBOX_AUTOCLOSE
	waitmessage
	turnobject LOCALID_ROUTE_30_JOEY DIR_NORTH
	release
	end


Route30_EventScript_Youngster_Joey::
	trainerbattle_single TRAINER_JOEY_HNS, Route30_Text_YoungsterJoey1Seen, Route30_Text_YoungsterJoey1Beaten, Route30_EventScript_RegisterJoey
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route30_EventScript_RematchJoey
	msgbox Route30_Text_YoungsterJoey1After, MSGBOX_AUTOCLOSE
	end

Route30_EventScript_RegisterJoey::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route30_Text_JoeyRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_JOEY_HNS
	release
	end

Route30_EventScript_RematchJoey::
	trainerbattle_rematch TRAINER_JOEY_HNS, Route30_Text_JoeyRematchIntro, Route30_Text_JoeyRematchDefeat
	msgbox Route30_Text_JoeyPostRematch, MSGBOX_AUTOCLOSE
	end

Route30_EventScript_Youngster_Mikey::
	trainerbattle_single TRAINER_MIKEY_HNS, Route30_Text_YoungsterMikeySeen, Route30_Text_YoungsterMikeyBeaten
	msgbox Route30_Text_YoungsterMikeyAfter, MSGBOX_AUTOCLOSE
	end
	
Route30_EventScript_Bugcatcher_Don::
	trainerbattle_single TRAINER_DON_HNS, Route30_Text_BugCatcherDonSeen, Route30_Text_BugCatcherDonBeaten
	msgbox Route30_Text_BugCatcherDonAfter, MSGBOX_AUTOCLOSE
	end

Route30_EventScript_ElmCall_Trigger::
	lock
	setspeaker Route30_Text_ElmName
	pokenavcall Route30_Text_Elm_Disaster
	waitmessage
	delay 30
	setvar VAR_CHERRYGROVE_CITY_STATE, 3
	release
	end

Route30_EventScript_Sign::
	lock
	msgbox Route30_Text_Sign, MSGBOX_SIGN
	closemessage
	release
	end

Route30_EventScript_TrainerTips::
	lock
	msgbox Route30_Text_TrainerTips, MSGBOX_SIGN
	closemessage
	release
	end	

Route30_EventScript_Poliwag::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_POLIWAG, CRY_MODE_NORMAL
	msgbox Route30_Text_Poliwag, MSGBOX_DEFAULT
	waitmoncry
	release
	end

Route30_EventScript_Mailbox::
	msgbox Route30_Text_Mailbox, MSGBOX_SIGN
	end

Route30_Text_Mailbox:
	.string "הבית של מר פוקימון$"

Route30_Text_UseTackle:
	.string "קדימה, רטטה!\p"
	.string "התנפלות!$"

Route30_Text_ThisIsABigBattle:
	.string "מה? זה קרב חשוב!\n"
	.string "עזוב אותי בשקט!$"

Route30_Text_YoungsterJoey1Seen:
	.string "הרגע הפסדתי, אז אני מנסה\n"
	.string "למצוא עוד פוקימונים.\p"
	.string "רגע! אתה נראה חלש! קדימה,\n"
	.string "בוא נילחם!$"

Route30_Text_YoungsterJoey1Beaten:
	.string "אוי! שוב הפסדתי!\n"
	.string "אוף, נו!$"

Route30_Text_YoungsterJoey1After:
	.string "אני צריך עוד פוקימונים\n"
	.string "כדי להילחם טוב יותר?\p"
	.string "לא! אני נשאר עם הפוקימון\n"
	.string "הזה, לא משנה מה!$"

Route30_Text_YoungsterMikeySeen:
	.string "אתה מאמן פוקימונים,\n"
	.string "נכון?\p"
	.string "אז אתה חייב להילחם!$"

Route30_Text_YoungsterMikeyBeaten:
	.string "מוזר.\n"
	.string "בפעם הקודמת ניצחתי.$"

Route30_Text_YoungsterMikeyAfter:
	.string "להיות מאמן טוב זה\n"
	.string "ממש קשה.\p"
	.string "אני אתמודד מול אנשים\n"
	.string "אחרים כדי להשתפר.$"

Route30_Text_BugCatcherDonSeen:
	.string "במקום פוקימון חרק,\n"
	.string "מצאתי מאמן!$"

Route30_Text_BugCatcherDonBeaten:
	.string "ארג! אתה חזק מדי!$"

Route30_Text_BugCatcherDonAfter:
	.string "נגמרו לי הפוכדורים\n"
	.string "בזמן שתפסתי פוקימונים.\p"
	.string "הייתי צריך לקנות עוד…$"

Route30_Text_YoungsterDirectionsToMrPokemon:
	.string "הבית של מר פוקימון?\n"
	.string "הוא קצת יותר קדימה.$"

Route30_Text_YoungsterEveryoneIsBattling:
	.string "כולם נהנים\n"
	.string "להילחם!\p"
	.string "כדאי גם לך!$"

Route30_Text_CooltrainerF:
	.string "אני לא מאמנת.\p"
	.string "אבל אם מסתכלים למאמן בעיניים,\n"
	.string "כדאי להתכונן לקרב.$"

Route30_Text_Sign:
	.string "דרך 30\p"
	.string "העיר ויולט - העיר צ'ריגרוב$"

Route30_Text_MrPokemonsHouseDirectionsSign:
	.string "MR. POKéMON'S HOUSE\n"
	.string "STRAIGHT AHEAD!$"

Route30_Text_MrPokemonsHouseSign:
	.string "MR. POKéMON'S HOUSE$"

Route30_Text_TrainerTips:
	.string "טיפים למאמנים\p"
	.string "אסור לגנוב פוקימונים של\n"
	.string "אנשים אחרים!\p"
	.string "יש לזרוק פוכדורים\n"
	.string "רק על פוקימונים פראיים!$"

Route30_Text_JoeyRegister:
	.string "אתה די טוב!\p"
	.string "הרטטה שלי להוט לקרב,\n"
	.string "כמו תמיד.\p"
	.string "הוא היחיד שיש לי.\n"
	.string "אני אהפוך איתו למאמן גדול!\p"
	.string "בוא נילחם שוב מתישהו!$"

Route30_Text_JoeyRematchIntro:
	.string "הבטחתי שהפעם יהיה אחרת!\n"
	.string "בוא נילחם!$"

Route30_Text_JoeyRematchDefeat:
	.string "אוי! שוב הפסדתי!\n"
	.string "אוף, נו!$"

Route30_Text_JoeyPostRematch:
	.string "אני בודק את המהלכים של הרטטה\n"
	.string "שלי ומתכנן כמה אסטרטגיות.\p"
	.string "כשאמציא אחת טובה,\n"
	.string "בוא נילחם!$"

Route30_Text_YoungsterJoeyGiveHPUp:
	.string "I lost again…\n"
	.string "Gee, you're tough!\p"
	.string "Oh yeah, I almost forgot that\n"
	.string "I had to give you this.\p"
	.string "Use it to get even tougher,\n"
	.string "OK?\p"
	.string "I'm going to get tougher too.$"

Route30_Text_ElmName:
	.string "פרופ' אלם$"

Route30_Text_Elm_Disaster:
	.string "פרופ' אלם: ה-הלו? {PLAYER}?\n"
	.string "זה אסון!\p"
	.string "אה, אממ, זה פשוט נורא!\p"
	.string "מה אני אעשה? זה…\n"
	.string "אוי, לא…\p"
	.string "בבקשה, תחזור לכאן מיד!$"


Route30_Text_Poliwag:
	.string "פוליוואג: וואג וואאג!$"
