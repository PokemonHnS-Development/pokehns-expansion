SafariZone_EventScript_OutOfBallsMidBattle::
#if IS_FRLG
	setvar VAR_MAP_SCENE_FUCHSIA_CITY_SAFARI_ZONE_ENTRANCE, 3
#elif IS_HNS
	setvar VAR_SAFARI_ZONE_STATE, 1
#else
	setvar VAR_SAFARI_ZONE_STATE, 1
#endif
	special ExitSafariMode
#if IS_FRLG
	setwarp MAP_FUCHSIA_CITY_SAFARI_ZONE_ENTRANCE, 4, 1
#elif IS_HNS
	goto_if_set FLAG_IN_KANTO_SAFARI_ZONE, SafariZone_EventScript_ExitKantoMidBattle
	setwarp MAP_SAFARI_ZONE_GATE_SAFARI_ZONE_ENTRANCE_HNS, 9, 3
#else
	setwarp MAP_ROUTE121_SAFARI_ZONE_ENTRANCE, 2, 5
#endif
	end

SafariZone_EventScript_ExitKantoMidBattle::
	clearflag FLAG_IN_KANTO_SAFARI_ZONE
	setwarp MAP_FUCHSIA_CITY_SAFARI_ZONE_ENTRANCE_HNS, 5, 6
	end

SafariZone_EventScript_Exit::
#if IS_FRLG
	setvar VAR_MAP_SCENE_FUCHSIA_CITY_SAFARI_ZONE_ENTRANCE, 1
#elif IS_HNS
	setvar VAR_SAFARI_ZONE_STATE, 1
#else
	setvar VAR_SAFARI_ZONE_STATE, 1
#endif
	special ExitSafariMode
#if IS_FRLG
	warp MAP_FUCHSIA_CITY_SAFARI_ZONE_ENTRANCE, 4, 1
#elif IS_HNS
	goto_if_set FLAG_IN_KANTO_SAFARI_ZONE, SafariZone_EventScript_ExitKanto
	warp MAP_SAFARI_ZONE_GATE_SAFARI_ZONE_ENTRANCE_HNS, 9, 3
#else
	warp MAP_ROUTE121_SAFARI_ZONE_ENTRANCE, 2, 5
#endif
	waitstate
	end

SafariZone_EventScript_ExitKanto::
	clearflag FLAG_IN_KANTO_SAFARI_ZONE
	warp MAP_FUCHSIA_CITY_SAFARI_ZONE_ENTRANCE_HNS, 5, 6
	waitstate
	end

SafariZone_EventScript_RetirePrompt::
	lockall
	msgbox SafariZone_Text_WouldYouLikeToExit, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, SafariZone_EventScript_Retire
	releaseall
	end

SafariZone_EventScript_Retire::
	goto SafariZone_EventScript_Exit

SafariZone_EventScript_TimesUp::
	lockall
	playse SE_DING_DONG
	message SafariZone_Text_TimesUp
	waitmessage
	waitbuttonpress
	releaseall
	goto SafariZone_EventScript_Exit

SafariZone_EventScript_OutOfBalls::
	lockall
	playse SE_DING_DONG
	message SafariZone_Text_OutOfBalls
	waitmessage
	waitbuttonpress
	releaseall
	goto SafariZone_EventScript_Exit

EventScript_PokeBlockFeeder::
	lockall
	special GetPokeblockFeederInFront
	goto_if_ne VAR_RESULT, 0xFFFF, SafariZone_EventScript_PokeblockPresent
	msgbox SafariZone_Text_PlacePokeblockOnFeeder, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, SafariZone_EventScript_ChoosePokeblock
	releaseall
	end

SafariZone_EventScript_ChoosePokeblock::
	fadescreen FADE_TO_BLACK
	special OpenPokeblockCaseOnFeeder
	waitstate
	goto_if_ne VAR_RESULT, 0xFFFF, SafariZone_EventScript_PokeblockPlaced
#ifdef BUGFIX
	releaseall  @ Only gets called from EventScript_PokeBlockFeeder which uses lockall.
#endif
	end

SafariZone_EventScript_PokeblockPlaced::
	message SafariZone_Text_PokeblockWasPlaced
	waitmessage
	waitbuttonpress
	releaseall
	end

SafariZone_EventScript_PokeblockPresent::
	message SafariZone_Text_PokeblockStillHere
	waitmessage
	waitbuttonpress
	releaseall
	end

SafariZone_EventScript_PokeblockGone::
	lockall
	message SafariZone_Text_PokeblockGone
	waitmessage
	waitbuttonpress
	releaseall
	end

SafariZone_Text_PokeblockGone:
	.string "{STR_VAR_1}\n"
	.string "נאכל כולו!$"

SafariZone_Text_WouldYouLikeToExit:
	.string "תרצה לצאת מאזור הספארי\n"
	.string "עכשיו?$"

SafariZone_Text_TimesUp:
	.string "דינג-דונג! הזמן נגמר!\n"
	.string "משחק הספארי שלך הסתיים.$"

SafariZone_Text_OutOfBalls:
	.string "נגמרו לך כדורי הספארי.\n"
	.string "משחק הספארי שלך הסתיים.$"

SafariZone_Text_PlacePokeblockOnFeeder:
	.string "תרצה להניח פוקיבלוק\n"
	.string "במתקן ההאכלה לפוקיבלוקים?$"

SafariZone_Text_PokeblockStillHere:
	.string "{STR_VAR_1} שהשארת\n"
	.string "קודם עדיין כאן.$"

SafariZone_Text_PokeblockWasPlaced:
	.string "{STR_VAR_1} הונח\n"
	.string "במתקן ההאכלה לפוקיבלוקים.$"

Route121_SafariZoneEntrance_Text_WelcomeToSafariZone:
	.string "ברוכים הבאים לאזור הספארי!\p"
	.string "כאן אפשר לראות סוגים רבים של\n"
	.string "פוקימונים שנדירים בחבל הארץ הזה.\p"
	.string "ותראו אותם במצבם הפראי,\n"
	.string "בבתי הגידול הטבעיים שלהם.\p"
	.string "ויותר מזה, פתחנו את השערים\n"
	.string "בפני מאמני פוקימונים.\p"
	.string "כולם מוזמנים לתפוס פוקימונים\n"
	.string "ולשמור אותם!\p"
	.string "היכנסו ותיהנו באזור הספארי!$"

Route121_SafariZoneEntrance_Text_WelcomeFirstTime:
	.string "ברוכים הבאים לאזור הספארי!\n"
	.string "זו הפעם הראשונה שלך כאן?$"

Route121_SafariZoneEntrance_Text_ComeInAndEnjoy:
	.string "היכנסו ותיהנו באזור הספארי!$"

Route121_SafariZoneEntrance_Text_FirstTimeInfo:
	.string "כשנכנסים לאזור הספארי, מקבלים\n"
	.string "30 כדורי ספארי לתפיסת פוקימונים.\p"
	.string "משחק הספארי נגמר כשנגמרים\n"
	.string "כדורי הספארי, או אחרי 500 צעדים.\p"
	.string "היכנסו ותיהנו באזור הספארי!$"

Route121_SafariZoneEntrance_Text_WouldYouLikeToPlay:
	.string "ברוכים הבאים לאזור הספארי!\p"
	.string "תופסים כמה שרוצים, רק ¥500!\n"
	.string "תרצה לשחק במשחק הספארי?$"

Route121_SafariZoneEntrance_Text_PlayAnotherTime:
	.string "בסדר.\n"
	.string "מוזמנים לשחק בפעם אחרת!$"

Route121_SafariZoneEntrance_Text_NotEnoughMoney:
	.string "אין לך מספיק כסף.\n"
	.string "סליחה.$"

Route121_SafariZoneEntrance_Text_ThatWillBe500Please:
	.string "זה יהיה ¥500, בבקשה.$"

Route121_SafariZoneEntrance_Text_HereAreYourSafariBalls:
	.string "הנה כדורי הספארי שלך.$"

Route121_SafariZoneEntrance_Text_Received30SafariBalls:
	.string "{PLAYER} קיבל 30 כדורי ספארי.$"

Route121_SafariZoneEntrance_Text_PleaseEnjoyYourself:
	.string "נודיע לך כשהמשחק שלך\n"
	.string "ייגמר.\p"
	.string "עד אז, שיהיה לך כיף!\n"
	.string "לדרך, אל ההרפתקה הפראית!$"

Route121_SafariZoneEntrance_Text_PCIsFull:
	.string "סליחה!\n"
	.string "תיבת המחשב שלך מלאה.$"

Route121_SafariZoneEntrance_Text_YouNeedPokeblockCase:
	.string "סליחה!\n"
	.string "נראה שאין לך קופסת פוקיבלוק.\p"
	.string "משחק הספארי יהיה מוצלח\n"
	.string "הרבה יותר עם פוקיבלוקים.\p"
	.string "נא לחזור עם קופסת פוקיבלוק.\p"
	.string "אפשר לקבל קופסת פוקיבלוק\n"
#if IS_HNS
	.string "מהילד ההוא שם.$"
#else
	.string "מאולם התחרויות בליליקוב.$"
#endif

SafariZone_South_Text_StillHaveTimeExit:
	.string "You still have time left. Would you like\n"
	.string "to exit the SAFARI ZONE now?$"

SafariZone_South_Text_EnjoyTheRestOfYourAdventure:
	.string "Please enjoy the rest of your wild\n"
	.string "adventure!$"

SafariZone_South_Text_ExitEarlyThankYouForPlaying:
	.string "בסדר.\p"
	.string "אקח בחזרה את כדורי הספארי\n"
	.string "שנשארו לך.\p"
	.string "תודה ששיחקת.\n"
	.string "נשמח לראות אותך שוב.$"

SafariZone_South_Text_GoodLuck:
	.string "Good luck!\p"
	.string "If you need anything, don't hesitate\n"
	.string "to tell me, please!$"

SafariZone_South_Text_Boy:
	.string "Did you know?\p"
	.string "If you put a {POKEBLOCK} in that square box,\n"
	.string "POKéMON gather around.$"

SafariZone_South_Text_Man:
	.string "I want to keep going deeper, but I\n"
	.string "forgot to bring a BIKE.\p"
	.string "Something tells me that rare POKéMON\n"
	.string "live in the outlying areas.$"

SafariZone_Southwest_Text_Woman:
	.string "Sometimes, when I toss a {POKEBLOCK} at \n"
	.string "POKéMON, it gets ignored.\p"
	.string "Do POKéMON have likes and dislikes\n"
	.string "about what they eat?$"

SafariZone_Northwest_Text_Man:
	.string "Gasp… Gasp…\n"
	.string "I…made it out here…but…\p"
	.string "I'm exhausted… I don't have the\n"
	.string "energy to catch POKéMON…$"

SafariZone_North_Text_Fisherman:
	.string "I'm on a mission to find WATER POKéMON\n"
	.string "you don't see in HOENN.\p"
	.string "Do you have any idea where the lake is?$"

SafariZone_North_Text_Man:
	.string "I'm going to catch a lot of rare POKéMON\n"
	.string "here and trade them with my friends!$"

SafariZone_South_Text_Youngster:
	.string "I put a {POKEBLOCK} on the {POKEBLOCK} FEEDER.\n"
	.string "But it seems to have disappeared.\p"
	.string "I guess POKéMON must have eaten it\n"
	.string "without me noticing.$"

Route121_SafariZoneEntrance_Text_TrainerTip:
	.string "SAFARI ZONE TRAINER TIP!\p"
	.string "Throw {POKEBLOCK}S at wild POKéMON to make\n"
	.string "them less likely to flee.$"

SafariZone_Southwest_Text_RestHouseSign:
	.string "“Relieve your tired feet.”\n"
	.string "REST HOUSE$"

SafariZone_RestHouse_Text_Youngster:
	.string "I don't have any {POKEBLOCK}S, but I caught\n"
	.string "a good number of POKéMON.\p"
	.string "You can improve your chances of making\n"
	.string "a catch by getting closer to them\l"
	.string "before throwing a SAFARI BALL.$"

SafariZone_RestHouse_Text_PsychicM:
	.string "If you use {POKEBLOCK}S, wild POKéMON won't\n"
	.string "be so quick to run away.\p"
	.string "It's not much use to give {POKEBLOCK}S to\n"
	.string "POKéMON that don't flee easily.$"

SafariZone_RestHouse_Text_FatMan:
	.string "If you put a {POKEBLOCK} on the FEEDER,\n"
	.string "POKéMON are attracted to it.\p"
	.string "I think POKéMON with the same sort of\n"
	.string "nature are drawn by a certain {POKEBLOCK}.$"

SafariZone_South_Text_AreaOffLimits1:
	.string "This area is still under construction.\n"
	.string "It's off-limits, sorry!$"

SafariZone_Southeast_Text_ExpansionIsFinished:
	.string "The SAFARI ZONE's expansion project\n"
	.string "is finished now.\p"
	.string "We hope you will enjoy the new area.$"

SafariZone_South_Text_AreaOffLimits2:
	.string "This area is still under construction.\n"
	.string "It's off-limits, sorry!$"

SafariZone_Southeast_Text_LittleGirl:
	.string "Wow! Whee! I haven't seen any of\n"
	.string "these POKéMON before!$"

SafariZone_Southeast_Text_FatMan:
	.string "The POKéMON in this area are all\n"
	.string "new to me.\p"
	.string "And I'm allowed to catch these rare\n"
	.string "POKéMON! Too cool!$"

SafariZone_Southeast_Text_RichBoy:
	.string "The POKéMON around here seem to be\n"
	.string "from somewhere other than HOENN.$"

SafariZone_Northeast_Text_Boy:
	.string "I only have a couple SAFARI BALLS left.\p"
	.string "I'm having a hard time trying to\n"
	.string "decide what I should catch.$"

SafariZone_Northeast_Text_Woman:
	.string "I heard that you can see PIKACHU here.\n"
	.string "Where might one be?$"

SafariZone_Northeast_Text_Girl:
	.string "Oh, boo!\n"
	.string "I can't seem to catch anything!\p"
	.string "I'll end up wasting the admission\n"
	.string "price if I don't catch something!$"
