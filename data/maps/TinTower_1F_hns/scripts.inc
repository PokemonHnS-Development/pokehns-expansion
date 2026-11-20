TinTower_1F_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, TinTower_OnTransition
	.byte 0

TinTower_OnTransition::
	setescapewarp MAP_BELLCHIME_TRAIL_HNS, 35, 42
	end

TinTower_1F_EventScript_SageA::
	lock
	faceplayer
	goto_if_eq VAR_ECRUTEAK_CITY_STATE, 11, TinTower_1F_EventScript_SageA_Hooh
	msgbox TinTower_1F_Sage4_Text2, MSGBOX_DEFAULT
	closemessage
	release
	end

TinTower_1F_EventScript_SageA_Hooh::
	msgbox TinTower_1F_Sage4_Text1, MSGBOX_DEFAULT
	closemessage
	release
	end

TinTower_1F_EventScript_SageB::
	lock
	faceplayer
	goto_if_eq VAR_ECRUTEAK_CITY_STATE, 11, TinTower_1F_EventScript_SageB_Hooh
	msgbox TinTower_1F_Sage2_Text, MSGBOX_DEFAULT
	closemessage
	release
	end

TinTower_1F_EventScript_SageB_Hooh::
	msgbox TinTower_1F_Sage1_Text, MSGBOX_DEFAULT
	closemessage
	release
	end

TinTower_1F_EventScript_SageC::
	lock
	faceplayer
	goto_if_eq VAR_ECRUTEAK_CITY_STATE, 11, TinTower_1F_EventScript_SageC_Hooh
	msgbox TinTower_1F_Sage6_Text2, MSGBOX_DEFAULT
	closemessage
	release
	end

TinTower_1F_EventScript_SageC_Hooh::
	msgbox TinTower_1F_Sage3_Text, MSGBOX_DEFAULT
	closemessage
	release
	end


TinTower_1F_Sage1_Text:
	.string "לפי האגדה, כשנשמות הפוקימונים\n"
	.string "ובני האדם מתאחדות,\p"
	.string "יורד מן השמיים\n"
	.string "פוקימון בצבעי הקשת…\p"
	.string "האם ייתכן שהפוקימונים האגדיים\n"
	.string "בוחנים אותנו, בני האדם?$"

TinTower_1F_Sage2_Text:
	.string "כשמגדל הפליז נשרף, אומרים ששלושה\n"
	.string "פוקימונים חסרי שם נספו. זה היה טרגי.\p"
	.string "אולם…\p"
	.string "פוקימון בצבעי הקשת…\n"
	.string "במילים אחרות…\p"
	.string "הו-הו ירד מן השמיים והעניק\n"
	.string "חיים חדשים לשלושת הפוקימונים.\p"
	.string "הם…\n"
	.string "סואיקון, אנטיי ורייקו.\p"
	.string "כך אומרים.$"

TinTower_1F_Sage3_Text:
	.string "אומרים ששני המגדלים נבנו כדי לטפח\n"
	.string "ידידות ותקווה בין פוקימונים לבני אדם.\p"
	.string "זה היה לפני 700 שנה, אבל\n"
	.string "האידיאל הזה חשוב עד היום.$"

TinTower_1F_Sage4_Text1:
	.string "נראה שהו-הו ירד\n"
	.string "אל המגדל הזה, מגדל הבדיל!$"

TinTower_1F_Sage4_Text2:
	.string "אומרים שהפוקימונים האגדיים\n"
	.string "מגלמים שלושה כוחות…\p"
	.string "הברק שפגע במגדל.\n"
	.string "האש ששרפה את המגדל.\p"
	.string "והגשם שכיבה את האש…$"

TinTower_1F_Sage6_Text2:
	.string "מבין הפוקימונים האגדיים, אומרים\n"
	.string "שסואיקון הוא הקרוב ביותר להו-הו.\p"
	.string "שמעתי שאולי יש קשר גם\n"
	.string "לפוקימונים הידועים בשם אנון.\p"
	.string "הפוקימון אנון ודאי חולק\n"
	.string "קשר של שיתוף פעולה עם סואיקון.$"

TinTower_1F_EusineHoOh_Text:
	.string "I knew it.\p"
	.string "I knew you'd get to see the POKéMON\n"
	.string "of rainbow colors, <PLAYER>.\p"
	.string "It happened just as I envisioned.\n"
	.string "My research isn't bad, I might say.\p"
	.string "I'm going to keep studying POKéMON\n"
	.string "to become a famous POKéMANIAC!$"

TinTower_1F_EusineSuicune_Text:
	.string "EUSINE: Awesome! Too awesome, even!\n"
	.string "I've never seen a battle that great.\p"
	.string "That was truly inspiring to see.\n"
	.string "SUICUNE was tough, but you were even\p"
	.string "more incredible, <PLAYER>.\n"
	.string "I heard SUICUNE's mystic power\p"
	.string "summons a rainbow-colored POKéMON.\n"
	.string "Maybe, just maybe, what went on today\p"
	.string "will cause that POKéMON to appear.\n"
	.string "I'm going to study the legends more.\p"
	.string "Thanks for showing me that fantastic\n"
	.string "battle.\p"
	.string "Later, <PLAYER>!$"
