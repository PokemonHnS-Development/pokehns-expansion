NationalPark_Normal_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, NationalPark_Normal_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

NationalPark_Normal_OnTransition: 
	callnative SetTimeBasedEncounters
	end

NationalPark_Normal_EventScript_Lass::
	lock
	faceplayer
	msgbox NationalPark_Normal_Text_Lass, MSGBOX_DEFAULT
	closemessage
	release
	end

NationalPark_Normal_EventScript_Youngster1::
	lock
	faceplayer
	msgbox NationalPark_Normal_Text_Youngster1, MSGBOX_DEFAULT
	closemessage
	release
	end

NationalPark_Normal_EventScript_Youngster2::
	lock
	faceplayer
	msgbox NationalPark_Normal_Text_Youngster2, MSGBOX_DEFAULT
	closemessage
	release
	end

NationalPark_Normal_EventScript_Teacher2::
	lock
	faceplayer
	msgbox NationalPark_Normal_Text_Teacher2, MSGBOX_DEFAULT
	closemessage
	call Common_EventScript_OutOfCenterPartyHeal
	release
	end

NationalPark_Normal_EventScript_TeacherQuickclaw::
	lock
	faceplayer
	goto_if_set FLAG_GOT_QUICK_CLAW, NationalPark_Normal_EventScript_TeacherQuickclaw2
	msgbox NationalPark_Normal_Text_Teacher1, MSGBOX_DEFAULT
	giveitem ITEM_QUICK_CLAW
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_BagIsFull
	setflag FLAG_GOT_QUICK_CLAW
NationalPark_Normal_EventScript_TeacherQuickclaw2::
	msgbox NationalPark_Normal_Text_Teacher1_QuickClaw, MSGBOX_DEFAULT
	closemessage
	release
	end

NationalPark_Normal_EventScript_Persian::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_PERSIAN, CRY_MODE_NORMAL
	msgbox NationalPark_Normal_Text_Persian, MSGBOX_DEFAULT
	waitmoncry
	release
	end



NationalPark_Normal_Text_Lass:
	.string "תראה! תסתכל על התיק שלי!\p"
	.string "הדפסתי את האהובים עליי מהפוקדקס\n"
	.string "והדבקתי אותם על התיק שלי.$"

NationalPark_Normal_Text_PokefanF:
	.string "This is MAIL I got from my daughter.\n"
	.string "It cheers me up.$"

NationalPark_Normal_Text_Teacher1:
	.string "שימו לב, בבקשה!\p"
	.string "…אופס, אני חייבת להפסיק לחשוב\n"
	.string "כמו מורה כל הזמן.\p"
	.string "אתה בטח מאמן פוקימונים.\p"
	.string "מכיוון שאתה מתאמץ כל כך,\n"
	.string "אני רוצה לתת לך את זה.$"

NationalPark_Normal_Text_Teacher1_QuickClaw:
	.string "כדאי לתת לפוקימון להחזיק\n"
	.string "את הטופר המהיר.\p"
	.string "לפעמים הוא יתקוף ראשון\n"
	.string "בקרב.$"

NationalPark_Normal_Text_Youngster1:
	.string "אני משחק במדבקות שהדפסתי\n"
	.string "מהפוקדקס שלי.$"

NationalPark_Normal_Text_Youngster2:
	.string "אם אנצח, אקבל את מדבקת הפוקדקס\n"
	.string "של הבחור השני.$"

NationalPark_Normal_Text_Teacher2:
	.string "אני מטיילת בפארק,\n"
	.string "אבל אף פעם לא נכנסת לעשב.\p"
	.string "מאמנים תמיד רוצים להילחם…\p"
	.string "בטח השתתפת בהרבה קרבות.\n"
	.string "אני ארפא לך את הפוקימונים.$"

NationalPark_Normal_Text_Persian:
	.string "פרסיאן: פופושאא!$"

NationalPark_Normal_EventScript_Jack::
	trainerbattle_single TRAINER_JACK_HNS, NationalPark_Normal_Text_SchoolboyJack1_Seen, NationalPark_Normal_Text_SchoolboyJack1_Beaten, NationalPark_Normal_EventScript_RegisterJack
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, NationalPark_Normal_EventScript_RematchJack
	msgbox NationalPark_Normal_Text_SchoolboyJack_After, MSGBOX_AUTOCLOSE
	end

NationalPark_Normal_EventScript_RegisterJack::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox NationalPark_Normal_Text_JackRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_JACK_HNS
	release
	end

NationalPark_Normal_EventScript_RematchJack::
	trainerbattle_rematch TRAINER_JACK_HNS, NationalPark_Normal_Text_JackRematchIntro, NationalPark_Normal_Text_JackRematchDefeat
	msgbox NationalPark_Normal_Text_JackPostRematch, MSGBOX_AUTOCLOSE
	end

NationalPark_Normal_EventScript_Beverly::
	trainerbattle_single TRAINER_BEVERLY_HNS, NationalPark_Normal_Text_PokefanFBeverly1_Seen, NationalPark_Normal_Text_PokefanFBeverly1_Beaten, NationalPark_Normal_EventScript_RegisterBeverly
	goto_if_set FLAG_BEVERLY_HAS_ITEM_HNS, NationalPark_Normal_EventScript_BeverlyGiveItem
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, NationalPark_Normal_EventScript_RematchBeverly
	msgbox NationalPark_Normal_Text_PokefanFBeverly_After, MSGBOX_AUTOCLOSE
	end

NationalPark_Normal_EventScript_RematchBeverly::
	trainerbattle_rematch TRAINER_BEVERLY_HNS, NationalPark_Normal_Text_PokefanFBeverly1_Seen, NationalPark_Normal_Text_PokefanFBeverly1_Beaten
	msgbox NationalPark_Normal_Text_PokefanFBeverly_After, MSGBOX_AUTOCLOSE
	end

NationalPark_Normal_EventScript_RegisterBeverly::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox NationalPark_Normal_Text_BeverlyRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_BEVERLY_HNS
	release
	end

NationalPark_Normal_EventScript_BeverlyGiveItem::
	msgbox NationalPark_Normal_Text_BeverlyHasItem, MSGBOX_DEFAULT
	giveitem VAR_BEVERLY_ITEM_HNS
	goto_if_eq VAR_RESULT, FALSE, NationalPark_Normal_EventScript_BeverlyNoRoom
	clearflag FLAG_BEVERLY_HAS_ITEM_HNS
	msgbox NationalPark_Normal_Text_BeverlyGaveItem, MSGBOX_AUTOCLOSE
	end

NationalPark_Normal_EventScript_BeverlyNoRoom::
	msgbox NationalPark_Normal_Text_BeverlyNoRoom, MSGBOX_AUTOCLOSE
	end

NationalPark_Normal_EventScript_William::
	trainerbattle_single TRAINER_WILLIAM_HNS, NationalPark_Normal_Text_PokefanmWilliam_Seen, NationalPark_Normal_Text_PokefanmWilliam_Beaten
	msgbox NationalPark_Normal_Text_PokefanmWilliam_After, MSGBOX_AUTOCLOSE
	end

NationalPark_Normal_EventScript_Krise::
	trainerbattle_single TRAINER_KRISE_HNS, NationalPark_Normal_Text_LassKrise_Seen, NationalPark_Normal_Text_LassKrise_Beaten
	msgbox NationalPark_Normal_Text_LassKrise_After, MSGBOX_AUTOCLOSE
	end

NationalPark_Normal_EventScript_TM_Dig::
	finditem ITEM_TM_DIG
	end

NationalPark_Normal_EventScript_Item_Soothe_Bell::
	finditem ITEM_SOOTHE_BELL
	end

NationalPark_Normal_Text_SchoolboyJack1_Seen:
	.string "עולם הפוקימונים עמוק.\p"
	.string "יש עוד הרבה דברים\n"
	.string "שאנחנו לא יודעים.\p"
	.string "אבל אני יודע יותר ממך!$"

NationalPark_Normal_Text_SchoolboyJack1_Beaten:
	.string "מ-מ-מה?$"

NationalPark_Normal_Text_SchoolboyJack_After:
	.string "יש הרבה מה ללמוד.\p"
	.string "למשל…\p"
	.string "יש 92 סוגים של מ”מ.\p"
	.string "פוקימונים שהתקבלו בהחלפה\n"
	.string "עולים רמה מהר יותר.$"

NationalPark_Normal_Text_JackRegister:
	.string "יש הרבה מה ללמוד.\p"
	.string "למשל…\p"
	.string "יש 92 סוגים של מ”מ.\p"
	.string "פוקימונים שהתקבלו בהחלפה\n"
	.string "עולים רמה מהר יותר.$"

NationalPark_Normal_Text_JackRematchIntro:
	.string "למדתי הרבה מאז\n"
	.string "הקרב האחרון שלנו! קדימה!$"

NationalPark_Normal_Text_JackRematchDefeat:
	.string "מ-מ-מה?$"

NationalPark_Normal_Text_JackPostRematch:
	.string "יש הרבה מה ללמוד.\p"
	.string "למשל…\p"
	.string "יש 92 סוגים של מ”מ.\p"
	.string "פוקימונים שהתקבלו בהחלפה\n"
	.string "עולים רמה מהר יותר.$"

NationalPark_Normal_Text_PokefanFBeverly1_Seen:
	.string "הפוקימונים שלי פשוט מקסימים.\p"
	.string "אספר לך כמה אני גאה\n"
	.string "במותקים שלי.$"

NationalPark_Normal_Text_PokefanFBeverly1_Beaten:
	.string "בגאווה אני מנצחת אותך, אבל…$"

NationalPark_Normal_Text_PokefanFBeverly_After:
	.string "אני חייבת לומר,\n"
	.string "גם הפוקימונים שלך די חמודים.$"

NationalPark_Normal_Text_PokefanmWilliam_Seen:
	.string "אנחנו מעריצים את הפוקימונים שלנו,\n"
	.string "גם אם הם לא אוהבים אותנו.\p"
	.string "זה כל העניין בלהיות פוקיפאן.$"

NationalPark_Normal_Text_PokefanmWilliam_Beaten:
	.string "ה-הפוקימונים שלי!$"

NationalPark_Normal_Text_PokefanmWilliam_After:
	.string "הפסדתי בקרב, אבל הפוקימונים שלי\n"
	.string "זוכים בפרס על היותם הכי מקסימים.$"

NationalPark_Normal_Text_LassKrise_Seen:
	.string "הלו? למה אתה בוהה בי?\p"
	.string "אה, קרב?$"

NationalPark_Normal_Text_LassKrise_Beaten:
	.string "…הממ…$"

NationalPark_Normal_Text_LassKrise_After:
	.string "חשבתי שאתה בוהה בי\n"
	.string "כי אני חמודה!$"

NationalPark_Normal_Text_Sign_RelaxationSquare:
	.string "RELAXATION SQUARE\n"
	.string "NATIONAL PARK$"

NationalPark_Normal_Text_Sign_BattleNotice:
	.string "What is this notice?\p"
	.string "Please battle only in the grass.\p"
	.string "NATIONAL PARK WARDEN'S OFFICE$"

NationalPark_Normal_Text_TrainerTips:
	.string "TRAINER TIPS\p"
	.string "Print out MAIL by opening it then\n"
	.string "pressing START.$"

NationalPark_Normal_Text_BeverlyRegister:
	.string "אני חייבת לומר,\n"
	.string "גם הפוקימונים שלך די חמודים.$"

NationalPark_Normal_Text_BeverlyHasItem:
	.string "אה, שלום! יש לי משהו\n"
	.string "בשבילך.\p"
	.string "בבקשה, קבל את זה\n"
	.string "כאות הוקרה ממני!$"

NationalPark_Normal_Text_BeverlyGaveItem:
	.string "אני והפוקימונים המתוקים שלי\n"
	.string "נעודד אותך!$"

NationalPark_Normal_Text_BeverlyNoRoom:
	.string "הממ, התיק שלך מלא.\p"
	.string "תחזור כשיהיה לך מקום.$"
