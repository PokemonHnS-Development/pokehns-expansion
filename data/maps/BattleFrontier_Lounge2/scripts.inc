BattleFrontier_Lounge2_MapScripts::
	.byte 0

@ This NPC gives hints about a random facility or battle mode.
@ For battle modes he gives generic advice
@ For facilities, depending on how far the player has progressed he will say either
@    The name of the Frontier Brain there
@    The type and description of the 3 pokemon they use in their silver battle
@    The type and description of the 3 pokemon they use in their gold battle
BattleFrontier_Lounge2_EventScript_FrontierManiac::
	lock
	faceplayer
	goto_if_set FLAG_MET_BATTLE_FRONTIER_MANIAC, BattleFrontier_Lounge2_EventScript_AlreadyMetManiac
	setflag FLAG_MET_BATTLE_FRONTIER_MANIAC
	msgbox BattleFrontier_Lounge2_Text_FrontierManiacIntro, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge2_EventScript_GiveAdvice
	end

BattleFrontier_Lounge2_EventScript_AlreadyMetManiac::
	msgbox BattleFrontier_Lounge2_Text_SwingByForTheLatestWord, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge2_EventScript_GiveAdvice
	end

BattleFrontier_Lounge2_EventScript_GiveAdvice::
	call_if_eq VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_TOWER_SINGLES, BattleFrontier_Lounge2_EventScript_BufferSingle
	call_if_eq VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_TOWER_DOUBLES, BattleFrontier_Lounge2_EventScript_BufferDouble
	call_if_eq VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_TOWER_MULTIS, BattleFrontier_Lounge2_EventScript_BufferMulti
	call_if_eq VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_TOWER_LINK, BattleFrontier_Lounge2_EventScript_BufferMultiLink
	call_if_eq VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_DOME, BattleFrontier_Lounge2_EventScript_BufferBattleDome
	call_if_eq VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_FACTORY, BattleFrontier_Lounge2_EventScript_BufferBattleFactory
	call_if_eq VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_PALACE, BattleFrontier_Lounge2_EventScript_BufferBattlePalace
	call_if_eq VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_ARENA, BattleFrontier_Lounge2_EventScript_BufferBattleArena
	call_if_eq VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_PIKE, BattleFrontier_Lounge2_EventScript_BufferBattlePike
	call_if_eq VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_PYRAMID, BattleFrontier_Lounge2_EventScript_BufferBattlePyramid
@ <= FRONTIER_MANIAC_TOWER_LINK is any Battle Tower mode
	call_if_le VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_TOWER_LINK, BattleFrontier_Lounge2_EventScript_BattleTowerNews
@ >= FRONTIER_MANIAC_DOME is any facility other than Battle Tower
	call_if_ge VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_DOME, BattleFrontier_Lounge2_EventScript_FacilityNews
	special ShowFrontierManiacMessage
	waitmessage
	waitbuttonpress
	release
	end

BattleFrontier_Lounge2_EventScript_BattleTowerNews::
	msgbox BattleFrontier_Lounge2_Text_BattleTowerIsHottest, MSGBOX_DEFAULT
	return

BattleFrontier_Lounge2_EventScript_FacilityNews::
	msgbox BattleFrontier_Lounge2_Text_FacilityIsHottest, MSGBOX_DEFAULT
	return

BattleFrontier_Lounge2_EventScript_BufferSingle::
	bufferstdstring STR_VAR_1, STDSTRING_SINGLE
	return

BattleFrontier_Lounge2_EventScript_BufferDouble::
	bufferstdstring STR_VAR_1, STDSTRING_DOUBLE
	return

BattleFrontier_Lounge2_EventScript_BufferMulti::
	bufferstdstring STR_VAR_1, STDSTRING_MULTI
	return

BattleFrontier_Lounge2_EventScript_BufferMultiLink::
	bufferstdstring STR_VAR_1, STDSTRING_MULTI_LINK
	return

BattleFrontier_Lounge2_EventScript_BufferBattleDome::
	bufferstdstring STR_VAR_1, STDSTRING_BATTLE_DOME
	return

BattleFrontier_Lounge2_EventScript_BufferBattleFactory::
	bufferstdstring STR_VAR_1, STDSTRING_BATTLE_FACTORY
	return

BattleFrontier_Lounge2_EventScript_BufferBattlePalace::
	bufferstdstring STR_VAR_1, STDSTRING_BATTLE_PALACE
	return

BattleFrontier_Lounge2_EventScript_BufferBattleArena::
	bufferstdstring STR_VAR_1, STDSTRING_BATTLE_ARENA
	return

BattleFrontier_Lounge2_EventScript_BufferBattlePike::
	bufferstdstring STR_VAR_1, STDSTRING_BATTLE_PIKE
	return

BattleFrontier_Lounge2_EventScript_BufferBattlePyramid::
	bufferstdstring STR_VAR_1, STDSTRING_BATTLE_PYRAMID
	return

BattleFrontier_Lounge2_EventScript_Maniac1::
	lock
	msgbox BattleFrontier_Lounge2_Text_NewsGatheringPower, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge2_EventScript_Maniac2::
	lock
	msgbox BattleFrontier_Lounge2_Text_AmazingPowersOfObservation, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge2_EventScript_Maniac3::
	lock
	msgbox BattleFrontier_Lounge2_Text_AmazingPowerOfPersuasion, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge2_EventScript_TriathleteF::
	msgbox BattleFrontier_Lounge2_Text_ThisPlaceIsScaringMe, MSGBOX_NPC
	end

BattleFrontier_Lounge2_Text_FrontierManiacIntro::
	.string "Howdy! When it comes to news about\n"
	.string "the BATTLE FRONTIER, I'm no. 1.\p"
	.string "You can think of me as\n"
	.string "the FRONTIER MANIAC.\p"
	.string "Just checking, but you are a TRAINER,\n"
	.string "isn't that right?\p"
	.string "I'll happily share the hottest news\n"
	.string "I gathered about the BATTLE FRONTIER.$"

BattleFrontier_Lounge2_Text_SwingByForTheLatestWord::
	.string "Howdy! Did you swing by to grill me\n"
	.string "about the latest word? Oh, all right!$"

@ Unused
BattleFrontier_Lounge2_Text_MyInformationsBeenUsefulRight::
	.string "Well? Well? Well?\p"
	.string "I'm sure my information's been\n"
	.string "seriously useful to you, right?$"

BattleFrontier_Lounge2_Text_FacilityIsHottest::
	.string "Let's see now…\p"
	.string "It sounds like the {STR_VAR_1}\n"
	.string "is the hottest place going.$"

BattleFrontier_Lounge2_Text_BattleTowerIsHottest::
	.string "Let's see now…\p"
	.string "It sounds like BATTLE TOWER\n"
	.string "{STR_VAR_1} is the hottest.$"

BattleFrontier_Lounge2_Text_SalonMaidenIsThere::
	.string "בטוח שלא ידעת את זה!\p"
	.string "אחת מהמאמנים המובילים שסקוט\n"
	.string "מכנה ”מוחות החזית” נמצאת שם.\p"
	.string "מאמנת מסתורית שנקראת עלמת הסלון\n"
	.string "היא זו שמנהלת את המקום.$"

BattleFrontier_Lounge2_Text_SalonMaidenSilverMons::
	.string "כבר התמודדת מול עלמת הסלון?\p"
	.string "כשהיא בוחנת את היריב שלה, כנראה\n"
	.string "שהיא משתמשת בפוקימונים האלה:\p"
	.string "פוקימון פסי מסוג על-חושי,\n"
	.string "פוקימון הר געש מסוג אש,\p"
	.string "ופוקימון ישנוני מסוג רגיל.$"

BattleFrontier_Lounge2_Text_SalonMaidenGoldMons::
	.string "כבר התמודדת מול עלמת הסלון\n"
	.string "כשהיא רצינית?\p"
	.string "כשהיא נלחמת במלוא הכוח, כנראה\n"
	.string "שהיא משתמשת בפוקימונים האלה:\p"
	.string "פוקימון איאון מסוג דרקון ועל-חושי,\n"
	.string "פוקימון רעם מסוג חשמל,\p"
	.string "ופוקימון ישנוני מסוג רגיל.$"

BattleFrontier_Lounge2_Text_DomeAceIsThere::
	.string "בטוח שלא ידעת את זה!\p"
	.string "אחד המאמנים המובילים שסקוט\n"
	.string "מכנה ”מוחות החזית” נמצא שם.\p"
	.string "מאמן ראוותני שנקרא אס הכיפה\n"
	.string "הוא זה שמנהל את המקום.$"

BattleFrontier_Lounge2_Text_DomeAceSilverMons::
	.string "כבר התמודדת מול אס הכיפה?\p"
	.string "כשהוא לא לוקח את היריב ברצינות,\n"
	.string "הוא משתמש בשלושת הפוקימונים האלה:\p"
	.string "פוקימון דרקון מסוג דרקון ותעופה,\n"
	.string "פוקימון דג בוץ מסוג מים ואדמה,\p"
	.string "ופוקימון להבה מסוג אש ותעופה.$"

BattleFrontier_Lounge2_Text_DomeAceGoldMons::
	.string "כבר התמודדת מול אס הכיפה\n"
	.string "כשהוא רציני?\p"
	.string "כשהוא מפגין את האסטרטגיה שלו,\n"
	.string "הוא משתמש בשלושת הפוקימונים האלה:\p"
	.string "פוקימון איאון מסוג דרקון ותעופה,\n"
	.string "פוקימון דג בוץ מסוג מים ואדמה,\p"
	.string "ופוקימון רגל ברזל מסוג פלדה ועל-חושי.$"

BattleFrontier_Lounge2_Text_FactoryHeadIsThere::
	.string "בטוח שלא ידעת את זה!\p"
	.string "אחד המאמנים המובילים שסקוט\n"
	.string "מכנה ”מוחות החזית” נמצא שם.\p"
	.string "מאמן משונה שנקרא ראש המפעל\n"
	.string "הוא זה שמנהל את המקום.$"

BattleFrontier_Lounge2_Text_FactoryHeadSilverMons::
	.string "כבר התמודדת מול ראש המפעל?\p"
	.string "רגע, תן לי לחשוב… כשהוא יוצא לקרב,\n"
	.string "הוא פשוט מקבל שלושה פוקימונים שכורים.\p"
	.string "הוא נלחם בערך באותם תנאים\n"
	.string "כמוך.$"

BattleFrontier_Lounge2_Text_FactoryHeadGoldMons::
	.string "כבר התמודדת מול ראש המפעל\n"
	.string "כשהוא רציני?\p"
	.string "גם כשהוא יוצא לקרב ברצינות,\n"
	.string "הוא מקבל שלושה פוקימונים שכורים.\p"
	.string "הוא נלחם כמעט בדיוק\n"
	.string "באותם תנאים כמוך.$"

BattleFrontier_Lounge2_Text_PikeQueenIsThere::
	.string "בטוח שלא ידעת את זה!\p"
	.string "אחת מהמאמנים המובילים שסקוט\n"
	.string "מכנה ”מוחות החזית” נמצאת שם.\p"
	.string "מאמנת מפחידה שנקראת מלכת השביל\n"
	.string "היא זו שמנהלת את המקום.$"

BattleFrontier_Lounge2_Text_PikeQueenSilverMons::
	.string "כבר התמודדת מול מלכת השביל?\p"
	.string "אומרים שכשמצב הרוח שלה טוב,\n"
	.string "היא משתמשת בשלושת הפוקימונים האלה:\p"
	.string "פוקימון נחש ניבים מסוג רעל,\n"
	.string "פוקימון עובש מסוג חרק וסלע,\p"
	.string "ופוקימון עדין מסוג מים.$"

BattleFrontier_Lounge2_Text_PikeQueenGoldMons::
	.string "כבר התמודדת מול מלכת השביל\n"
	.string "כשהיא רצינית?\p"
	.string "אומרים שכשהיא ממש מעוצבנת,\n"
	.string "היא משתמשת בשלושת הפוקימונים האלה:\p"
	.string "פוקימון נחש ניבים מסוג רעל,\n"
	.string "פוקימון נחש ברזל מסוג פלדה ואדמה,\p"
	.string "ופוקימון אכזרי מסוג מים ותעופה.$"

BattleFrontier_Lounge2_Text_ArenaTycoonIsThere::
	.string "בטוח שלא ידעת את זה!\p"
	.string "אחת מהמאמנים המובילים שסקוט\n"
	.string "מכנה ”מוחות החזית” נמצאת שם.\p"
	.string "מאמנת חמודה שנקראת גבירת הזירה\n"
	.string "היא זו שמנהלת את המקום.$"

BattleFrontier_Lounge2_Text_ArenaTycoonSilverMons::
	.string "כבר התמודדת מול גבירת הזירה?\p"
	.string "כשהיא בודקת מה היריב שווה,\n"
	.string "שמעתי שהיא משתמשת בפוקימונים האלה:\p"
	.string "פוקימון קרן יחידה מסוג חרק וקרב,\n"
	.string "פוקימון אור ירח מסוג אפל,\p"
	.string "ופוקימון נשל מסוג חרק ורפאים.$"

BattleFrontier_Lounge2_Text_ArenaTycoonGoldMons::
	.string "כבר התמודדת מול גבירת הזירה\n"
	.string "כשהיא רצינית?\p"
	.string "כשהיא נלחמת ברצינות גמורה,\n"
	.string "שמעתי שהיא משתמשת בפוקימונים האלה:\p"
	.string "פוקימון אור ירח מסוג אפל,\n"
	.string "פוקימון צל מסוג רפאים ורעל,\p"
	.string "ופוקימון פטרייה מסוג עשב וקרב.$"

BattleFrontier_Lounge2_Text_PalaceMavenIsThere::
	.string "בטוח שלא ידעת את זה!\p"
	.string "אחד המאמנים המובילים שסקוט\n"
	.string "מכנה ”מוחות החזית” נמצא שם.\p"
	.string "מאמן מאיים שנקרא אשף הארמון\n"
	.string "הוא זה שמנהל את המקום.$"

BattleFrontier_Lounge2_Text_PalaceMavenSilverMons::
	.string "כבר התמודדת מול אשף הארמון?\p"
	.string "כשהוא בוחן את רוח היריב, אומרים\n"
	.string "שהוא משתמש בפוקימונים האלה:\p"
	.string "פוקימון עטלף מסוג רעל ותעופה,\n"
	.string "פוקימון עצלן מסוג רגיל,\p"
	.string "ופוקימון הסעה מסוג מים וקרח.$"

BattleFrontier_Lounge2_Text_PalaceMavenGoldMons::
	.string "כבר התמודדת מול אשף הארמון\n"
	.string "כשהוא רציני?\p"
	.string "כשהוא נכנס לקרב בכל הכוח, אומרים\n"
	.string "שהוא משתמש בפוקימונים האלה:\p"
	.string "פוקימון אגדי מסוג אש,\n"
	.string "פוקימון עצלן מסוג רגיל,\p"
	.string "ופוקימון זוהר מסוג מים.$"

BattleFrontier_Lounge2_Text_PyramidKingIsThere::
	.string "בטוח שלא ידעת את זה!\p"
	.string "אחד המאמנים המובילים שסקוט\n"
	.string "מכנה ”מוחות החזית” נמצא שם.\p"
	.string "מאמן לוהט שנקרא מלך הפירמידה\n"
	.string "הוא זה שמנהל את המקום.$"

BattleFrontier_Lounge2_Text_PyramidKingSilverMons::
	.string "כבר התמודדת מול מלך הפירמידה?\p"
	.string "כשהוא בודק את כוחו של היריב,\n"
	.string "כנראה שהוא משתמש בפוקימונים האלה:\p"
	.string "פוקימון פסגת סלע מסוג סלע,\n"
	.string "פוקימון קרחון מסוג קרח,\p"
	.string "ופוקימון ברזל מסוג פלדה.$"

BattleFrontier_Lounge2_Text_PyramidKingGoldMons::
	.string "כבר התמודדת מול מלך הפירמידה\n"
	.string "כשהוא רציני?\p"
	.string "כשהוא בוער מרוב כוח, כנראה\n"
	.string "שהוא משתמש בפוקימונים האלה:\p"
	.string "פוקימון קפוא מסוג קרח ותעופה,\n"
	.string "פוקימון חשמלי מסוג חשמל ותעופה,\p"
	.string "ופוקימון להבה מסוג אש ותעופה.$"

BattleFrontier_Lounge2_Text_DoubleBattleAdvice1::
	.string "נכון, יש כמה מקומות שבהם\n"
	.string "אפשר להשתתף בקרבות כפולים.\p"
	.string "אבל חדרי קרב כפול במגדל הקרב\n"
	.string "הם, כאילו, הבסיס!\p"
	.string "שם כדאי ללמוד איך מתנהלים קרבות\n"
	.string "כפולים כאן בחזית הקרב.$"

BattleFrontier_Lounge2_Text_DoubleBattleAdvice2::
	.string "כדאי להיזהר בקרבות כאן.\p"
	.string "שמעתי שיש מאמנים שפיתחו אסטרטגיות\n"
	.string "במיוחד לקרבות כפולים.$"

BattleFrontier_Lounge2_Text_DoubleBattleAdvice3::
	.string "ברגע שתרגיש בטוח ובנוח בקרבות\n"
	.string "הכפולים כאן, כדאי לחשוב על אתגר\p"
	.string "במקומות אחרים שמציעים קרבות כפולים.$"

BattleFrontier_Lounge2_Text_MultiBattleAdvice::
	.string "כל מיני מאמנים מתאספים\n"
	.string "בסלון הקרב.\p"
	.string "רק תחשוב - אולי תיתקל בחברים או\n"
	.string "במעריצים שלך! כדאי להסתכל היטב!$"

BattleFrontier_Lounge2_Text_LinkMultiBattleAdvice::
	.string "אם יש איתך חבר, כדאי ללכת\n"
	.string "לחדר קרב מרובה בקישור.\p"
	.string "אם משחקים עם חבר חזק,\n"
	.string "אפשר לצפות ליריבים קשוחים!$"

BattleFrontier_Lounge2_Text_NewsGatheringPower::
	.string "What amazing news-gathering power!\n"
	.string "My mentor's like none other!$"

BattleFrontier_Lounge2_Text_AmazingPowersOfObservation::
	.string "What amazing powers of observation!\n"
	.string "My mentor's like none other!$"

BattleFrontier_Lounge2_Text_AmazingPowerOfPersuasion::
	.string "What amazing power of persuasion!\n"
	.string "My mentor's like none other!$"

BattleFrontier_Lounge2_Text_ThisPlaceIsScaringMe::
	.string "…What is this place?\n"
	.string "It's scaring me…$"

