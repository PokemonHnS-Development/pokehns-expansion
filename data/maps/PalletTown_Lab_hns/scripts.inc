PalletTown_Lab_hns_MapScripts::
	.byte 0

PalletTown_Lab_EventScript_Oak::
	lock
	faceplayer
	call_if_unset FLAG_SYS_NATIONAL_DEX, PalletTown_Lab_EventScript_OakGiveNatDex_ForPlaytesters
	goto_if_eq VAR_PALLETTOWN_LABSTATE, 1, PalletTown_Lab_EventScript_OakBadgeCheck
	goto_if_eq VAR_PALLETTOWN_LABSTATE, 2, PalletTown_Lab_EventScript_OakDex
	msgbox PalletTown_Lab_Text_OakWelcomeKanto, MSGBOX_DEFAULT
	msgbox PalletTown_Lab_Text_OakLabGoodbye, MSGBOX_DEFAULT
	setvar VAR_PALLETTOWN_LABSTATE, 1
	goto_if_ge VAR_NUM_BADGES, 16, PalletTown_Lab_EventScript_OakBadgeCheck
	closemessage
	release
	end

PalletTown_Lab_EventScript_OakGiveNatDex_ForPlaytesters::
	setflag FLAG_SYS_NATIONAL_DEX
	special EnableNationalPokedex
	return

PalletTown_Lab_EventScript_OakBadgeCheck::
	goto_if_ge VAR_NUM_BADGES, 16, PalletTown_Lab_EventScript_Oak16Badges
	goto_if_ge VAR_NUM_BADGES, 9, PalletTown_Lab_EventScript_Oak9Badges
	msgbox PalletTown_Lab_Text_OakNoKantoBadges, MSGBOX_DEFAULT
	closemessage
	release
	end

PalletTown_Lab_EventScript_Oak16Badges::
	msgbox PalletTown_Lab_Text_OakOpenMtSilver, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_INDIGOJUNCTION_HIDE_SILVER_GUARD
	setvar VAR_ROUTE28_SCIENTIST, 1
	setvar VAR_PALLETTOWN_LABSTATE, 2
	call_if_unset FLAG_IS_KANTO_CHAMPION, PalletTown_Lab_EventScript_OakKantoLeague
	release
	end

PalletTown_Lab_EventScript_OakKantoLeague::
	msgbox PalletTown_Lab_Text_OakOpenIndigoPlateau, MSGBOX_DEFAULT
	closemessage
	return

PalletTown_Lab_EventScript_Oak9Badges::
	msgbox PalletTown_Lab_Text_OakYesKantoBadges, MSGBOX_DEFAULT
	closemessage
	release
	end

PalletTown_Lab_EventScript_OakDex::
	msgbox PalletTown_Lab_Text_OakLabDexCheck, MSGBOX_DEFAULT
	closemessage
	release
	end

PalletTown_Lab_EventScript_Assistant1::
	msgbox PalletTown_Lab_Text_OaksAssistant1, MSGBOX_NPC
	end

PalletTown_Lab_EventScript_Assistant2::
	msgbox PalletTown_Lab_Text_OaksAssistant2, MSGBOX_NPC
	end

PalletTown_Lab_EventScript_Assistant3::
	msgbox PalletTown_Lab_Text_OaksAssistant3, MSGBOX_NPC
	end

PalletTown_Lab_EventScript_PC::
	msgbox PalletTown_Lab_Text_OaksLabPC, MSGBOX_SIGN
	end

PalletTown_Lab_Text_OakLabDexCheck:
	.string "איך מתקדם הפוקדקס שלך?$"

PalletTown_Lab_Text_OakWelcomeKanto:
	.string "אוק: אה, {PLAYER}! יפה מצדך\n"
	.string "שבאת את כל הדרך עד לקאנטו.\p"
	.string "מה דעתך על המאמנים כאן?\n"
	.string "די קשוחים, אה?$"

PalletTown_Lab_Text_OakLabGoodbye:
	.string "אם תהיה באזור, אני מקווה\n"
	.string "שתבוא לבקר שוב.$"

PalletTown_Lab_Text_OakOpenMtSilver:
	.string "אוק: וואו! זה מצוין!\p"
	.string "אספת את התגים של המכונים\n"
	.string "בקאנטו. כל הכבוד!\p"
	.string "צדקתי בהערכה שלי לגביך.\p"
	.string "אתה יודע מה, {PLAYER}? אדאג לסידורים\n"
	.string "כדי שתוכל להגיע להר הכסף.\p"
	.string "הר הכסף הוא הר גדול שבו\n"
	.string "חיים פוקימונים פראיים רבים.\p"
	.string "הוא מסוכן מדי למאמן הממוצע,\n"
	.string "ולכן הכניסה אליו אסורה.\p"
	.string "אבל במקרה שלך, {PLAYER},\n"
	.string "נוכל לעשות חריגה.\p"
	.string "עלה לרמת אינדיגו. משם\n"
	.string "אפשר להגיע להר הכסף.$"

PalletTown_Lab_Text_OakOpenIndigoPlateau:
	.string "אה, ואם כבר מדברים על רמת\n"
	.string "אינדיגו, עכשיו כשהשגת 16 תגים,\p"
	.string "ליגת קאנטו תהיה מוכנה לקבל\n"
	.string "שוב את האתגר שלך.\p"
	.string "אבל דע לך, לאנס והרביעייה העילית\n"
	.string "שלו לא יוותרו לך הפעם.\p"
	.string "בהצלחה, {PLAYER}!$"

PalletTown_Lab_Text_OakNoKantoBadges:
	.string "אוק: הממ? אתה לא אוסף\n"
	.string "את תגי המכונים של קאנטו?\p"
	.string "מנהיגי המכונים בקאנטו קשוחים\n"
	.string "כמו כל אלה שנלחמת בהם בג'וטו.\p"
	.string "אני ממליץ לך לאתגר אותם.$"

PalletTown_Lab_Text_OakYesKantoBadges:
	.string "אוק: אה, אתה אוסף את תגי\n"
	.string "המכונים של קאנטו.\p"
	.string "אני מתאר לעצמי שזה קשה, אבל\n"
	.string "הניסיון בטוח יעזור לך.\p"
	.string "בוא אליי כשתשיג את כולם.\p"
	.string "תהיה לי מתנה בשבילך.\p"
	.string "תמשיך להתאמץ, {PLAYER}!$"

PalletTown_Lab_Text_OaksAssistant1:
	.string "תוכנית הרדיו ”שיחות פוקימון” של\n"
	.string "הפרופסור לא משודרת כאן בקאנטו.\p"
	.string "חבל - הייתי שמחה לשמוע אותה.$"

PalletTown_Lab_Text_OaksAssistant2:
	.string "בזכות העבודה שלך על הפוקדקס,\n"
	.string "המחקר של הפרופסור מתקדם מצוין.$"

PalletTown_Lab_Text_OaksAssistant3:
	.string "אל תגלה לאף אחד, אבל ”שיחות פוקימון\n"
	.string "עם פרופ' אוק” היא לא שידור חי.$"

PalletTown_Lab_Text_OaksLabPC:
	.string "יש הודעת דוא”ל במחשב.\p"
	.string "…\p"
	.string "פרופ' אוק, איך מתקדם\n"
	.string "המחקר שלך?\p"
	.string "אני עדיין עובד במרץ.\p"
	.string "שמעתי שמועות ש{PLAYER}\n"
	.string "צובר מוניטין לא קטן.\p"
	.string "אני שמח מאוד לשמוע את זה.\p"
	.string "אלם מהעיירה ניו בארק 8-)$"
