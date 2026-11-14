GoldenrodCity_hns_MapScripts::
	.byte 0

GoldenrodCity_EventScript_Trigger:: @flagheap
	call_if_unset FLAG_SHOWN_ELM_TOGEPI, GoldenrodCity_Elm_Togepi_Call
	setflag FLAG_VISITED_GOLDENROD_CITY
	setflag FLAG_HIDE_GOLDENROD_ROCKETS
	setflag FLAG_HIDE_GOLDENROD_BILL
	setflag FLAG_HIDE_GOLDENROD_UNDERGROUND_KIMONO
	setflag FLAG_HIDE_GOLDENROD_UNDERGROUND_SILVER
	setflag FLAG_HIDE_ROCKET_GOLDENROD_RADIOTOWER_1
	setflag FLAG_HIDE_GOLDENROD_RADIOTOWER_PETREL
	setflag FLAG_HIDE_GOLDENROD_RADIOTOWER_DIRECTOR_2
	
	clearflag FLAG_HIDE_GOLDENROD_BEAUTY
	clearflag FLAG_HIDE_GOLDENROD_ROCKET_SCOUT
	clearflag FLAG_HIDE_GOLDENROD_NPCS
	clearflag FLAG_GOT_RETURN
	clearflag FLAG_GOT_FRUSTRATION
	clearflag FLAG_RECEIVED_BIKE
	clearflag FLAG_RECEIVED_SQUIRTBOTTLE
	clearflag FLAG_GOT_EEVEE
	clearflag FLAG_SYS_PC_BILL
	clearflag FLAG_RETURNED_MACHINE_PART
	clearflag FLAG_UNLOCKED_GOLDENROD_UNDERGROUND_DOOR
	clearflag FLAG_GOLDENROD_MACHOKE_1
	clearflag FLAG_GOLDENROD_MACHOKE_2
	clearflag FLAG_GOLDENROD_MACHOKE_3
	clearflag FLAG_COMPLETED_SWITCHES
	clearflag FLAG_ENABLE_RADIO
	clearflag FLAG_KANTO_RADIO_GOT
	clearflag FLAG_GOLDENROD_NPC_TRADE_COMPLETED
	clearflag FLAG_GOT_SUNNY_DAY
	clearflag FLAG_HIDE_RADIOTOWER_GATE
	clearflag FLAG_HIDE_GOLDENROD_RADIOTOWER_DIRECTOR
	clearflag FLAG_GOT_MARY_BRIGHT_POWDER
	clearflag FLAG_GOT_QUICK_CLAW
	clearflag FLAG_GOT_MAGNET

	setvar VAR_BUG_CONTEST_STATE, 0
	setvar VAR_KENYA, 0
	setvar VAR_LUGIA_OR_HOOH, 0
	setvar VAR_TRAIN, 0
	setvar VAR_ELEVATOR, 0
	setvar VAR_GOLDENROD_CITY_STATE, 1
	release
	end

GoldenrodCity_Trigger_Music::
	goto_if_lt VAR_GOLDENROD_CITY_STATE, 6, GoldenrodCity_Trigger_MusicNotYet
	goto_if_ge VAR_GOLDENROD_CITY_STATE, 11, GoldenrodCity_Trigger_MusicNotYet
	fadenewbgm MUS_HG_ROCKET_TAKEOVER
	special ShowMapNamePopup
	setvar VAR_TEMP_0, 1 
	end

GoldenrodCity_Trigger_Music2::
	goto_if_lt VAR_GOLDENROD_CITY_STATE, 6, GoldenrodCity_Trigger_MusicNotYet
	goto_if_ge VAR_GOLDENROD_CITY_STATE, 11, GoldenrodCity_Trigger_MusicNotYet
	fadedefaultbgm
	special ShowMapNamePopup
	setvar VAR_TEMP_0, 1
	end

GoldenrodCity_Trigger_MusicNotYet::
	special ShowMapNamePopup
	setvar VAR_TEMP_0, 1
	end

GoldenrodCity_Elm_Togepi_Call::
	lock
	setspeaker GoldenrodCity_Text_ElmName
	pokenavcall GoldenrodCity_Text_ElmCall
	waitmessage
	delay 30
	release
	return

GoldenrodCity_EventScript_PokefanM::
	lock
	faceplayer
	msgbox GoldenrodCity_Text_PokefanM, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_EventScript_Youngster::
	msgbox GoldenrodCity_Text_Youngster1, MSGBOX_NPC
	end

GoldenrodCity_EventScript_Youngster2::
	msgbox GoldenrodCity_Text_Youngster2, MSGBOX_NPC
	end

GoldenrodCity_EventScript_CooltrainerF::
	lock
	faceplayer
	goto_if_set FLAG_HIDE_GOLDENROD_ROCKET_SCOUT, GoldenrodCity_EventScript_CooltrainerFCleared
	msgbox GoldenrodCity_Text_CooltrainerF1, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_EventScript_CooltrainerFCleared::
	msgbox GoldenrodCity_Text_CooltrainerF1_Cleared, MSGBOX_NPC
	end

GoldenrodCity_EventScript_Lass::
	lock
	faceplayer
	msgbox GoldenrodCity_Text_Lass, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_EventScript_Gramps::
	lock
	faceplayer
	msgbox GoldenrodCity_Text_Gramps, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_EventScript_NameRaterSign::
	msgbox GoldenrodCity_Text_NameRaterSign, MSGBOX_SIGN
	end

GoldenrodCity_EventScript_RocketScout::
	lock
	msgbox GoldenrodCity_Text_RocketScout1, MSGBOX_DEFAULT
	closemessage
	PLAYSE SE_PIN
	applymovement LOCALID_GOLDENROD_ROCKET_SCOUT, Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_GOLDENROD_ROCKET_SCOUT
	faceplayer
	msgbox GoldenrodCity_Text_RocketScout2, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_GOLDENROD_ROCKET_SCOUT, DIR_NORTH
	release
	end

GoldenrodCity_EventScript_Rocket1::
	lock
	faceplayer
	msgbox GoldenrodCity_Text_Rocket1, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_EventScript_Rocket2::
	lock
	faceplayer
	msgbox GoldenrodCity_Text_Rocket2, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_EventScript_Rocket3::
	lock
	faceplayer
	msgbox GoldenrodCity_Text_Rocket3, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_EventScript_Rocket4::
	lock
	faceplayer
	msgbox GoldenrodCity_Text_Rocket4, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_EventScript_Rocket5::
	lock
	faceplayer
	msgbox GoldenrodCity_Text_Rocket5, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_EventScript_Rocket6::
	lock
	faceplayer
	msgbox GoldenrodCity_Text_Rocket6, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_EventScript_Woman::
	lock
	faceplayer
	msgbox GoldenrodCity_Text_Woman, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_EventScript_Hiker::
	lock
	faceplayer
	goto_if_set FLAG_DAY_POKEMON, GoldenrodCity_EventScript_Hiker2
	msgbox GoldenrodCity_Text_HikerDay, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_EventScript_Hiker2::
	msgbox GoldenrodCity_Text_HikerNight, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_EventScript_Snubbull::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_SNUBBULL, CRY_MODE_NORMAL
	msgbox GoldenrodCity_Text_Snubbull, MSGBOX_DEFAULT
	waitmoncry
	release
	end

GoldenrodCity_EventScript_Mime::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_MR_MIME, CRY_MODE_NORMAL
	msgbox GoldenrodCity_Text_MrMime, MSGBOX_DEFAULT
	waitmoncry
	release
	end

GoldenrodCity_EventScript_SignUnderground::
	lock
	msgbox GoldenrodCity_Text_UndergroundSouthSign, MSGBOX_SIGN
	closemessage
	release
	end
GoldenrodCity_EventScript_SignDept::
	lock
	msgbox GoldenrodCity_Text_DeptStoreSign, MSGBOX_SIGN
	closemessage
	release
	end
GoldenrodCity_EventScript_SignBike::
	lock
	msgbox GoldenrodCity_Text_BikeShopSign, MSGBOX_SIGN
	closemessage
	release
	end
GoldenrodCity_EventScript_SignTrain::
	lock
	msgbox GoldenrodCity_Text_StationSign, MSGBOX_SIGN
	closemessage
	release
	end
GoldenrodCity_EventScript_SignGym::
	lock
	msgbox GoldenrodCity_Text_GymSign, MSGBOX_SIGN
	closemessage
	release
	end
GoldenrodCity_EventScript_SignFlower::
	lock
	msgbox GoldenrodCity_Text_FlowerShopSign, MSGBOX_SIGN
	closemessage
	release
	end
GoldenrodCity_EventScript_SignRadio::
	lock
	msgbox GoldenrodCity_Text_RadioTowerSign, MSGBOX_SIGN
	closemessage
	release
	end
GoldenrodCity_EventScript_SignGameCorner::
	lock
	msgbox GoldenrodCity_Text_GameCornerSign, MSGBOX_SIGN
	closemessage
	release
	end

GoldenrodCity_EventScript_Beauty::
	lock
	faceplayer
	msgbox GoldenrodCity_Text_Beauty, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_Text_Beauty:
	.string "זה מכון גולדנרוד!\p"
	.string "המנהיגה שלנו, ויטני, לא כאן כרגע.\n"
	.string "אולי היא במגדל הרדיו.$"

GoldenrodCity_Text_Woman:
	.string "פעם התאמנתי במכון של ויטני,\n"
	.string "אבל כל הבכי שלה עשה לי כאב ראש.$"

GoldenrodCity_Text_HikerDay:
	.string "כשנכנסתי למשחקייה היה לילה…\n"
	.string "כמה זמן הייתי שם?!$"

GoldenrodCity_Text_HikerNight:
	.string "כשנכנסתי למשחקייה היה יום…\n"
	.string "כמה זמן הייתי שם?!$"

GoldenrodCity_Text_Snubbull:
	.string "סנאבול: סנאאאבוווול!$"

GoldenrodCity_Text_MrMime:
	.string "............................$"

GoldenrodCity_Text_ElmName:
	.string "פרופ' אלם$"

GoldenrodCity_Text_ElmCall:
	.string "פרופ' אלם: הלו, {PLAYER}?\n"
	.string "הביצה כבר בקעה?\p"
	.string "כשהיא תבקע, אל תשכח להביא את\n"
	.string "הפוקימון למעבדה! אני חייב לראותו!$"

GoldenrodCity_Text_PokefanM:
	.string "בנו את מגדל הרדיו החדש\n"
	.string "במקום הישן והחורק.$"

GoldenrodCity_Text_Youngster1:
	.string "אני יודע שיש חנות אופניים חדשה,\n"
	.string "אבל אני לא מוצא אותה בשום מקום.$"

GoldenrodCity_Text_CooltrainerF1:
	.string "האיש ההוא בשחור התחפש\n"
	.string "לחבר בצוות רוקט?\p"
	.string "כמה מגוחך!$"

GoldenrodCity_Text_CooltrainerF1_Cleared:
	.string "האיש ההוא בשחור באמת היה\n"
	.string "חבר בצוות רוקט? אני לא מאמינה!$"

GoldenrodCity_Text_CooltrainerF2:
	.string "The RADIO TOWER in GOLDENROD CITY\n"
	.string "is quite the landmark.\p"
	.string "They're running a campaign now.\p"
	.string "They'll give you a shiny new\n"
	.string "RADIO if you can pass their quiz.$"

GoldenrodCity_Text_CooltrainerF2_GotCard:
	.string "Oh, your POKéGEAR already works\n"
	.string "as a radio!$"

GoldenrodCity_Text_Youngster2:
	.string "הי-הי-הי-הי…\p"
	.string "הסתבכתי כי שיחקתי\n"
	.string "במרתף של הכלבו.$"

GoldenrodCity_Text_Lass:
	.string "האיש שבפנים מדרג\n"
	.string "את הכינויים של הפוקימונים שלך.\p"
	.string "הוא אפילו יכול לשנות אותם.$"

GoldenrodCity_Text_Gramps:
	.string "אוף! העיר הזאת כל כך גדולה,\n"
	.string "אני לא מוצא כאן שום דבר.$"

GoldenrodCity_Text_RocketScout1:
	.string "אז זה מגדל הרדיו…$"

GoldenrodCity_Text_RocketScout2:
	.string "מה אתה רוצה, נודניק?\n"
	.string "תסתלק כבר!$"

GoldenrodCity_Text_Rocket1:
	.string "אל תעמוד בדרך!\n"
	.string "עוף מפה, ילד!$"

GoldenrodCity_Text_Rocket2:
	.string "להשתלט על מגדל הרדיו…\p"
	.string "מה? זה לא עניינך!$"

GoldenrodCity_Text_Rocket3:
	.string "פוקימונים? הם סתם כלים\n"
	.string "שבעזרתם אנחנו עושים כסף!$"

GoldenrodCity_Text_Rocket4:
	.string "החלום שלנו יתגשם בקרוב…\p"
	.string "זה היה מאבק ארוך וקשה…$"

GoldenrodCity_Text_Rocket5:
	.string "היי, פרחח! אין לך מה לחפש כאן!\n"
	.string "תתנדף כבר!$"

GoldenrodCity_Text_Rocket6:
	.string "בוא לטעום את האימה\n"
	.string "של צוות רוקט!$"

GoldenrodCity_Text_StationSign:
	.string "תחנת הרכבת של העיר גולדנרוד$"

GoldenrodCity_Text_RadioTowerSign:
	.string "מגדל הרדיו של העיר גולדנרוד$"

GoldenrodCity_Text_DeptStoreSign:
	.string "מבחר מלא של מוצרי פוקימון!\p"
	.string "הכלבו של העיר גולדנרוד$"

GoldenrodCity_Text_GymSign:
	.string "מכון הפוקימון של העיר גולדנרוד\n"
	.string "מנהיגה: ויטני\p"
	.string "הנערה היפה להפליא!$"

GoldenrodCity_Text_CitySign:
	.string "GOLDENROD CITY\p"
	.string "The Festive City of Opulent Charm$"

GoldenrodCity_Text_BikeShopSign:
	.string "העולם הוא שביל אופניים!\n"
	.string "חנות אופניים$"

GoldenrodCity_Text_GameCornerSign:
	.string "מגרש המשחקים שלך!\p"
	.string "המשחקייה של העיר גולדנרוד$"

GoldenrodCity_Text_NameRaterSign:
	.string "בוחן השמות\p"
	.string "דירוג כינויים של פוקימונים$"

GoldenrodCity_Text_UndergroundNorthSign:
	.string "UNDERGROUND ENTRANCE$"

GoldenrodCity_Text_UndergroundSouthSign:
	.string "כניסה למעבר התת-קרקעי$"


GoldenrodCity_Text_FlowerShopSign:
	.string "חנות הפרחים - יופי בפריחה$"

GoldenrodCity_Text_MoveTutorAsk:
	.string "I can teach your POKéMON some\n"
	.string "amazing moves!\p"
	.string "Should I teach one?$"

GoldenrodCity_Text_MoveTutorCost:
	.string "It'll cost you 1000 coins.\n"
	.string "Okay?$"

GoldenrodCity_Text_MoveTutorDecline:
	.string "Aww… But these moves are great!$"

GoldenrodCity_Text_MoveTutorWhich:
	.string "Wahahah! You won't regret it!\p"
	.string "Which move should I teach?$"

GoldenrodCity_Text_MoveTutorNoCash:
	.string "Too bad. Guess I'll need to\n"
	.string "get some cash from home…$"

GoldenrodCity_Text_MoveTutorUnderstand:
	.string "If you understand this move,\n"
	.string "you've made it as a trainer.$"

GoldenrodCity_Text_MoveTutorFarewell:
	.string "Wahahah! Farewell, kid!$"

GoldenrodCity_Text_MoveTutorBut:
	.string "B-but…$"

GoldenrodCity_Text_MoveTutorNotEnoughCoins:
	.string "…You don't have enough coins…$"
