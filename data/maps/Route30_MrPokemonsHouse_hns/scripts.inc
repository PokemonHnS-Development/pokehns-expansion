Route30_MrPokemonsHouse_hns_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, MrPokemonHouse_OnFrame
	.byte 0

MrPokemonHouse_OnFrame::
	map_script_2 VAR_CHERRYGROVE_CITY_STATE, 1, MrPokemonHouse_EventScript_GiveEgg
	.2byte 0

MrPokemonHouse_EventScript_GiveEgg::
	lock
	playse SE_PIN
	applymovement LOCALID_MRPOKEMON, Common_Movement_ExclamationMark	
	delay 55
	waitmovement LOCALID_MRPOKEMON
	turnobject LOCALID_MRPOKEMON, DIR_SOUTH
	msgbox MrPokemonHouse_Text_Intro1, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, MrPokemonHouse_Movement_MeetMrPokemon
	waitmovement 0
	msgbox MrPokemonHouse_Text_Intro2, MSGBOX_DEFAULT

	giveitem ITEM_MYSTERY_EGG

	msgbox MrPokemonHouse_Text_Intro3, MSGBOX_DEFAULT
	msgbox MrPokemonHouse_Text_Intro4, MSGBOX_DEFAULT
	turnobject LOCALID_ROUTE30_OAK, DIR_WEST
	msgbox MrPokemonHouse_Text_Intro5, MSGBOX_DEFAULT
	closemessage
	playbgm MUS_HG_OAK, FALSE
	applymovement LOCALID_ROUTE30_OAK, MrPokemonHouse_Movement_OakToPlayer
	waitmovement 0 
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	msgbox MrPokemonHouse_Text_OakIntro, MSGBOX_DEFAULT
	

	playfanfare MUS_OBTAIN_ITEM
	message MrPokemonHouse_Text_GetDex
	waitfanfare

	
	msgbox MrPokemonHouse_Text_OakParting, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ROUTE30_OAK, MrPokemonHouse_Movement_OakLeave
	waitmovement 0
	playse SE_EXIT
	removeobject LOCALID_ROUTE30_OAK
	setflag FLAG_DELIVERED_EGG
	turnobject OBJ_EVENT_ID_PLAYER DIR_NORTH
	fadedefaultbgm
	msgbox MrPokemonHouse_Text_Heal, MSGBOX_DEFAULT
	call Common_EventScript_OutOfCenterPartyHeal
	msgbox MrPokemonHouse_Text_DependingOnYou, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_MRPOKEMON, MrPokemonHouse_Movement_MrPokemon_Leave
	waitmovement 0
	removeobject LOCALID_MRPOKEMON
	clearflag FLAG_HIDE_MRPOKEMON
	addobject LOCALID_MRPOKEMON2
	
	setvar VAR_NEWBARKTOWN_LABSTATE, 4
	setflag FLAG_HIDE_SILVER_NEWBARKTOWN
	setflag FLAG_SYS_POKEDEX_GET
	checkrandomizer
	call_if_eq VAR_RESULT, TRUE, MrPokemonHouse_EventScript_GiveNatDexRandomizer
	clearflag FLAG_HIDE_LAB_POLICEMAN
	setvar VAR_CHERRYGROVE_CITY_STATE, 2
	setrespawn HEAL_LOCATION_CHERRYGROVE_CITY_HNS
	clearflag FLAG_HIDE_SILVER_CHERRYGROVE
	setflag FLAG_HIDE_GUIDE_GENT_CHERRYGROVE
	clearflag FLAG_HIDE_CHERRYGROVE_GUIDE_GENT_HOUSE
	release
	end

MrPokemonHouse_EventScript_GiveNatDexRandomizer::
	setflag FLAG_SYS_NATIONAL_DEX
	special EnableNationalPokedex
	return

MrPokemonHouse_EventScript_MrPokemon::
	lock
	faceplayer
	checkitem ITEM_RED_SCALE
	goto_if_eq VAR_RESULT, TRUE, MrPokemonHouse_EventScript_MrPokemon_RedScale
	msgbox MrPokemonHouse_Text_AlwaysNewDiscoveries, MSGBOX_DEFAULT
	closemessage
	release
	end

MrPokemonHouse_EventScript_MrPokemon_RedScale::
	msgbox MrPokemonHouse_Text_GimmeTheScale, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE, MrPokemonHouse_EventScript_MrPokemon_RedScale_Accepted
	msgbox MrPokemonHouse_Text_Disappointed, MSGBOX_DEFAULT
	closemessage
	release
	end	

MrPokemonHouse_EventScript_MrPokemon_RedScale_Accepted::
	removeitem ITEM_RED_SCALE
	giveitem ITEM_EXP_SHARE_SMALL
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	release
	end


MrPokemonHouse_EventScript_Computer::
	lock
	msgbox MrPokemonHouse_Text_BrokenComputer, MSGBOX_SIGN
	release
	end

MrPokemonHouse_EventScript_Magazine::
	lock
	msgbox MrPokemonHouse_Text_ForeignMagazines, MSGBOX_SIGN
	release
	end

MrPokemonHouse_EventScript_Coins::
	lock
	msgbox MrPokemonHouse_Text_StrangeCoins, MSGBOX_SIGN
	release
	end

MrPokemonHouse_Movement_MeetMrPokemon:
	walk_up
	walk_up
	walk_right
	walk_right
	face_up
	step_end

MrPokemonHouse_Movement_OakToPlayer:
	walk_down
	face_left
	step_end

MrPokemonHouse_Movement_OakLeave:
	walk_down
	walk_left
	walk_left
	walk_left
	walk_down
	walk_in_place_down
	step_end

MrPokemonHouse_Movement_MrPokemon_Leave:
	walk_up
	walk_left
	walk_left
	step_end

MrPokemonHouse_Text_Intro1:
	.string "שלום, שלום! אתה בטח\n"
	.string "{PLAYER}.\p"
	.string "פרופ' אלם אמר שתבוא\n"
	.string "לבקר.$"

MrPokemonHouse_Text_Intro2:
	.string "את זה אני רוצה שפרופ' אלם\n"
	.string "יבדוק.$"

MrPokemonHouse_Text_GotEgg:
	.string "{PLAYER} received MYSTERY EGG.$"

MrPokemonHouse_Text_Intro3:
	.string "אני מכיר זוג שמפעיל\n"
	.string "מעון יום לפוקימונים.\p"
	.string "הם נתנו לי את הביצה הזאת.\p"
	.string "הסתקרנתי, אז שלחתי\n"
	.string "אימייל לפרופ' אלם.\p"
	.string "בתחום התפתחות הפוקימונים,\n"
	.string "פרופ' אלם הוא הסמכות.$"


MrPokemonHouse_Text_Intro4:
	.string "אפילו פרופ' אוק, שנמצא כאן,\n"
	.string "מכיר בזה.$"

MrPokemonHouse_Text_Intro5:
	.string "אם ההשערה שלי נכונה,\n"
	.string "פרופ' אלם יידע.$"

MrPokemonHouse_Text_Heal:
	.string "אתה חוזר לפרופ' אלם?\p"
	.string "הנה. הפוקימונים שלך צריכים\n"
	.string "קצת מנוחה.$"

MrPokemonHouse_Text_DependingOnYou:
	.string "אני סומך עליך!$"

MrPokemonHouse_Text_AlwaysNewDiscoveries:
	.string "החיים נפלאים!\n"
	.string "תמיד יש תגליות חדשות לגלות.$"

MrPokemonHouse_Text_OakIntro:
	.string "אוק: אהה! אז אתה {PLAYER}!\p"
	.string "אני אוק! חוקר פוקימונים.\p"
	.string "בדיוק ביקרתי את חברי הוותיק,\n"
	.string "מר פוקימון.\p"
	.string "שמעתי שאתה בשליחות בשביל\n"
	.string "פרופ' אלם, אז חיכיתי כאן.\p"
	.string "הו! מה זה? פוקימון נדיר!\p"
	.string "בוא נראה…\n"
	.string "הממ, הבנתי!\p"
	.string "אני מבין למה פרופ' אלם נתן\n"
	.string "לך פוקימון לשליחות הזאת.\p"
	.string "לחוקרים כמו פרופ' אלם וכמוני,\n"
	.string "פוקימונים הם החברים שלנו.\p"
	.string "הוא ראה שתתייחס לפוקימונים\n"
	.string "שלך באהבה ובאכפתיות.\p"
	.string "…אה!\p"
	.string "אתה נראה אמין. מה דעתך\n"
	.string "לעזור לי?\p"
	.string "רואה? זו הגרסה החדשה ביותר\n"
	.string "של הפוקדקס.\p"
	.string "הוא מתעד אוטומטית מידע על\n"
	.string "פוקימונים שראית או תפסת.\p"
	.string "זו אנציקלופדיה חדשנית!\p"
	.string "הוא מראה איפה הם חיים, איך\n"
	.string "הם מתפתחים ומה המהלכים שלהם.$"

MrPokemonHouse_Text_GetDex:
	.string "{PLAYER} קיבל את הפוקדקס!$"

MrPokemonHouse_Text_OakParting:
	.string "צא לפגוש הרבה מיני פוקימונים\n"
	.string "והשלם את הפוקדקס!\p"
	.string "אבל נשארתי יותר מדי זמן.\p"
	.string "אני צריך להגיע לגולדנרוד\n"
	.string "לתוכנית הרדיו הקבועה שלי.\p"
	.string "{PLAYER}, אני סומך עליך!$"

MrPokemonHouse_Text_GimmeTheScale:
	.string "הממ? הקשקש הזה! מה זה?\n"
	.string "של גרידוס אדום?\p"
	.string "זה נדיר! אני… אני רוצה אותו…\p"
	.string "{PLAYER}, תסכים להחליף\n"
	.string "אותו?\p"
	.string "אני יכול להציע את חולק הניסיון\n"
	.string "הקטן הזה, שקיבלתי מפרופ' אוק.$"

MrPokemonHouse_Text_Disappointed:
	.string "זה מאכזב.\n"
	.string "מדובר בפריט נדיר מאוד.$"

MrPokemonHouse_Text_ExpShare:
	.string "I also have a special item\n"
	.string "for you.$"

MrPokemonHouse_Text_ForeignMagazines:
	.string "זה עמוס במגזינים מחו”ל.\p"
	.string "אי אפשר אפילו לקרוא\n"
	.string "את הכותרות שלהם…$"

MrPokemonHouse_Text_BrokenComputer:
	.string "It's a big computer.\n"
	.string "Hmm. It's broken.$"

MrPokemonHouse_Text_StrangeCoins:
	.string "ערימה שלמה של מטבעות מוזרים!\p"
	.string "אולי הם ממדינה אחרת…$"

MrPokemonHouse_Text_GotExpShare:
	.string "{PLAYER} received EXP. SHARE!$"
