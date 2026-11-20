Route38_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route38_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route38_OnTransition: 
	callnative SetTimeBasedEncounters
	end

Route38_EventScript_Toby::
	trainerbattle_single TRAINER_TOBY_HNS, Route38_Text_BirdKeeperTobySeen, Route38_Text_BirdKeeperTobyBeaten
	msgbox Route38_Text_BirdKeeperTobyAfter, MSGBOX_AUTOCLOSE
	end

Route38_EventScript_Chad::
	trainerbattle_single TRAINER_CHAD_HNS, Route38_Text_SchoolboyChad1Seen, Route38_Text_SchoolboyChad1Beaten, Route38_EventScript_RegisterChad
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route38_EventScript_RematchChad
	msgbox Route38_Text_SchoolboyChadAfter, MSGBOX_AUTOCLOSE
	end

Route38_EventScript_RegisterChad::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route38_Text_ChadRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_CHAD_HNS
	release
	end

Route38_EventScript_RematchChad::
	trainerbattle_rematch TRAINER_CHAD_HNS, Route38_Text_ChadRematchIntro, Route38_Text_ChadRematchDefeat
	msgbox Route38_Text_ChadPostRematch, MSGBOX_AUTOCLOSE
	end

Route38_EventScript_Dana::
	trainerbattle_single TRAINER_DANA_HNS, Route38_Text_LassDana1Seen, Route38_Text_LassDana1Beaten, Route38_EventScript_RegisterDana
	goto_if_set FLAG_DANA_HAS_ITEM_HNS, Route38_EventScript_DanaGiveItem
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route38_EventScript_RematchDana
	msgbox Route38_Text_LassDanaAfter, MSGBOX_AUTOCLOSE
	end

Route38_EventScript_RegisterDana::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route38_Text_DanaRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_DANA_HNS
	release
	end

Route38_EventScript_RematchDana::
	trainerbattle_rematch TRAINER_DANA_HNS, Route38_Text_DanaRematchIntro, Route38_Text_DanaRematchDefeat
	msgbox Route38_Text_DanaPostRematch, MSGBOX_AUTOCLOSE
	end

Route38_EventScript_DanaGiveItem::
	msgbox Route38_Text_DanaHasItem, MSGBOX_DEFAULT
	giveitem VAR_DANA_ITEM_HNS
	goto_if_eq VAR_RESULT, FALSE, Route38_EventScript_DanaNoRoom
	clearflag FLAG_DANA_HAS_ITEM_HNS
	msgbox Route38_Text_DanaGaveItem, MSGBOX_AUTOCLOSE
	end

Route38_EventScript_DanaNoRoom::
	msgbox Route38_Text_DanaNoRoom, MSGBOX_AUTOCLOSE
	end

Route38_EventScript_Valerie::
	trainerbattle_single TRAINER_VALERIE_HNS, Route38_Text_BeautyValerieSeen, Route38_Text_BeautyValerieBeaten
	msgbox Route38_Text_BeautyValerieAfter, MSGBOX_AUTOCLOSE
	end

Route38_EventScript_Harry::
	trainerbattle_single TRAINER_HARRY_HNS, Route38_Text_SailorHarrySeen, Route38_Text_SailorHarryBeaten
	msgbox Route38_Text_SailorHarryAfter, MSGBOX_AUTOCLOSE
	end

Route38_EventScript_Olivia::
	trainerbattle_single TRAINER_OLIVIA_HNS, Route38_Text_BeautyOliviaSeen, Route38_Text_BeautyOliviaBeaten
	msgbox Route38_Text_BeautyOliviaAfter, MSGBOX_AUTOCLOSE
	end

Route38_EventScript_Sign1::
	lock
	msgbox Route38_Text_Sign, MSGBOX_SIGN
	closemessage
	release
	end

Route38_EventScript_Sign2::
	lock
	msgbox Route38_Text_WaterSign, MSGBOX_SIGN
	closemessage
	release
	end

Route38_EventScript_Item_LaxIncense::
	finditem ITEM_LAX_INCENSE
	end

Route38_Text_BirdKeeperTobySeen:
	.string "המריאו גבוה אל השמיים,\n"
	.string "פוקימוני הציפורים האהובים שלי!$"

Route38_Text_BirdKeeperTobyBeaten:
	.string "בא לי פשוט לעוף מפה עכשיו.$"

Route38_Text_BirdKeeperTobyAfter:
	.string "אני מתכנן להתאמן בעיר סיאנווד כדי\n"
	.string "ללמד את הפוקימונים שלי תעופה.$"

Route38_Text_SchoolboyChad1Seen:
	.string "אני רוצה לנסות משהו שלמדתי היום.$"

Route38_Text_SchoolboyChad1Beaten:
	.string "כנראה שלא למדתי מספיק.$"

Route38_Text_SchoolboyChadAfter:
	.string "יש לי כל כך הרבה מבחנים,\n"
	.string "שאין לי הרבה זמן לפוקימונים.\p"
	.string "אז כשכבר יוצא לי לשחק, אני ממש מתרכז.$"

Route38_Text_ChadRegister:
	.string "יש לי כל כך הרבה מבחנים,\n"
	.string "שאין לי הרבה זמן לפוקימונים.\p"
	.string "אז כשכבר יוצא לי לשחק, אני ממש מתרכז.$"

Route38_Text_ChadRematchIntro:
	.string "אני רוצה לנסות משהו שלמדתי היום.$"

Route38_Text_ChadRematchDefeat:
	.string "כנראה שלא למדתי מספיק.$"

Route38_Text_ChadPostRematch:
	.string "יש לי כל כך הרבה מבחנים,\n"
	.string "שאין לי הרבה זמן לפוקימונים.\p"
	.string "אז כשכבר יוצא לי לשחק, אני ממש מתרכז.$"

Route38_Text_LassDana1Seen:
	.string "נראה שיש לך כישרון לפוקימונים.\p"
	.string "אם כן, מה דעתך לתת לי כמה עצות?$"

Route38_Text_LassDana1Beaten:
	.string "הבנתי. אז ככה אפשר להילחם.$"

Route38_Text_LassDanaAfter:
	.string "אני יודעת משהו טוב!\p"
	.string "החלב של חוות מומו\n"
	.string "מפורסם בזכות הטעם שלו.$"

Route38_Text_BeautyValerieSeen:
	.string "היי! איזה מאמן חמוד אתה!\p"
	.string "אפשר לראות את הפוקימונים שלך?$"

Route38_Text_BeautyValerieBeaten:
	.string "אני שמחה שזכיתי לראות\n"
	.string "את הפוקימונים שלך!$"

Route38_Text_BeautyValerieAfter:
	.string "כשאני רואה פוקימונים,\n"
	.string "זה מרגיע לי את העצבים.$"

Route38_Text_SailorHarrySeen:
	.string "הייתי מעבר לים, אז אני\n"
	.string "מכיר כל מיני פוקימונים!$"

Route38_Text_SailorHarryBeaten:
	.string "הכישרון שלך ברמה עולמית!$"

Route38_Text_SailorHarryAfter:
	.string "כל מיני אנשים ברחבי העולם\n"
	.string "חיים באושר עם פוקימונים.$"

Route38_Text_BeautyOliviaSeen:
	.string "נכון שאני והפוקימונים שלי יפים?$"

Route38_Text_BeautyOliviaBeaten:
	.string "אנחנו שותים חלב מומו כל יום.$"

Route38_Text_BeautyOliviaAfter:
	.string "חלב מומו טוב ליופי ולבריאות,\p"
	.string "אבל זה לא נוח שמוכרים\n"
	.string "רק בקבוק אחד בכל פעם.$"

Route38_Text_Sign:
	.string "דרך 38\p"
	.string "העיר אוליבין - העיר אקרוטיק$"

Route38_Text_TrainerTips:
	.string "TRAINER TIPS\p"
	.string "If a POKéMON is trying to\n"
	.string "evolve, you can stop it.\p"
	.string "Press the B Button during\n"
	.string "evolution to cancel it.\p"
	.string "That startles the POKéMON\n"
	.string "and stops its evolution.$"


Route38_Text_WaterSign:
	.string "אסור לשחות או לדוג.\n"
	.string "המים לחקלאות בלבד.\p"
	.string "- מועצת אקרוטיק$"

Route38_Text_DanaRegister:
	.string "אני יודעת משהו טוב!\p"
	.string "החלב של חוות מומו\n"
	.string "מפורסם בזכות הטעם שלו.$"

Route38_Text_DanaRematchIntro:
	.string "נראה שיש לך כישרון לפוקימונים.\p"
	.string "אם כן, מה דעתך לתת לי כמה עצות?$"

Route38_Text_DanaRematchDefeat:
	.string "הבנתי. אז ככה אפשר להילחם.$"

Route38_Text_DanaPostRematch:
	.string "אני יודעת משהו טוב!\p"
	.string "החלב של חוות מומו\n"
	.string "מפורסם בזכות הטעם שלו.$"

Route38_Text_DanaHasItem:
	.string "היי! מצאתי משהו מעניין!\p"
	.string "הנה, זה בשבילך!$"

Route38_Text_DanaGaveItem:
	.string "אודיע לך אם אמצא עוד משהו!$"

Route38_Text_DanaNoRoom:
	.string "הממ, התיק שלך מלא.\p"
	.string "תחזור כשיהיה לך מקום.$"
