VioletCity_TrainerSchool_hns_MapScripts::
	.byte 0

VioletCity_TrainerSchool_EventScript_Earl::
	lock
	faceplayer
	msgbox VioletCity_TrainerSchool_Text_EarlIntro, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_TrainerSchool_EventScript_Teacher::
	lock
	faceplayer
	msgbox VioletCity_TrainerSchool_Text_Teacher, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_TrainerSchool_EventScript_Boy1::
	lock
	faceplayer
	msgbox VioletCity_TrainerSchool_Text_GameboyKid1, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_TrainerSchool_EventScript_Boy2::
	lock
	faceplayer
	msgbox VioletCity_TrainerSchool_Text_GameboyKid2, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_TrainerSchool_EventScript_Kid::
	lock
	faceplayer
	msgbox VioletCity_TrainerSchool_Text_Youngster1, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_TrainerSchool_EventScript_Girl::
	lock
	faceplayer
	msgbox VioletCity_TrainerSchool_Text_Youngster2, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_TrainerSchool_EventScript_Twin::
	msgbox VioletCity_TrainerSchool_Text_Twin, MSGBOX_NPC
	end

VioletCity_TrainerSchool_EventScript_BlackBoard::
	lock
	msgbox VioletCity_TrainerSchool_Text_Blackboard, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_TrainerSchool_Text_Twin:
	.string "אני לא ילדת GBA, אבל אני\n"
	.string "מתה על משחקי פוקימון!\p"
	.string "במשחקים הישנים היה צריך להילחם בהמון\n"
	.string "פוקימונים פראיים כדי לצבור מספיק ניסיון.\p"
	.string "אבל במשחקים החדשים, חולק הניסיון גורם\n"
	.string "לפוקימונים שלך לעלות רמה מהר מדי.\p"
	.string "במשחק הזה, חולק הניסיון מאוזן כך\n"
	.string "שהפוקימונים יהיו בדיוק ברמה הנכונה.\p"
	.string "או קצת מעליה, תלוי בכמות הקרבות.\p"
	.string "לחוויה מסורתית כמו בדורות 1-4,\n"
	.string "כדאי לכבות את חולק הניסיון.\p"
	.string "לחוויה מודרנית, כדאי\n"
	.string "להפעיל את חולק הניסיון.\p"
	.string "הבחירה איך לשחק בידיים שלך!$"

VioletCity_TrainerSchool_Text_EarlIntro:
	.string "ארל אני!\p"
	.string "נפלאים הפוקימונים, כן!\p"
	.string "אותך אלמד אני להיות מאמן טוב יותר!$"

VioletCity_TrainerSchool_Text_Teacher:
	.string "יש פוקימונים שמתחילים חלשים וצריכים\n"
	.string "הרבה יותר ניסיון מאחרים כדי להתחזק.\p"
	.string "למשל, לרביטר חלש למדי, אבל בסוף\n"
	.string "הוא יהפוך לטירניטר אדיר.\p"
	.string "המחיר: הרבה מאוד נקודות ניסיון.\p"
	.string "רק המאמנים המסורים ביותר\n"
	.string "צריכים לנסות לאמן פוקימון כזה.$"

VioletCity_TrainerSchool_Text_TeachHowToWin:
	.string "Good! Teach you, I will!\p"
	.string "In battle, POKéMON top on list\n"
	.string "jump out first!\p"
	.string "Change order in list, make\n"
	.string "battle easy, maybe!\p"
	.string "More from me you want to hear?$"

VioletCity_TrainerSchool_Text_TeachMore:
	.string "So, want to know how to raise\n"
	.string "POKéMON well?$"

VioletCity_TrainerSchool_Text_TeachRaiseWell:
	.string "Fine! Teach you, I will!\p"
	.string "If POKéMON come out in battle\n"
	.string "even briefly, some EXP. Points\p"
	.string "it gets.\n"
	.string "At top of list put weak POKéMON\p"
	.string "Switch in battle quick!\n"
	.string "This way, weak POKéMON strong\p"
	.string "become!$"

VioletCity_TrainerSchool_Text_NoMoreToTeach:
	.string "Oh! Smart student you are!\n"
	.string "Nothing more do I teach!\p"
	.string "If you want more, talk to\n"
	.string "pupils!$"

VioletCity_TrainerSchool_Text_Youngster1:
	.string "פוקימונים שפעם חשבו שהם מתפתחים רק\n"
	.string "בהחלפה יכולים להתפתח גם בעליית רמה.\p"
	.string "מאצ'וק וגרבלר מתפתחים ברמה 38,\n"
	.string "וקדברה והאנטר מתפתחים ברמה 42.\p"
	.string "התגלה גם שפריטים כמו ציפוי מתכת\n"
	.string "גורמים לפוקימונים מסוימים להתפתח\p"
	.string "כשהם מחזיקים בהם ועולים רמה.$"

VioletCity_TrainerSchool_Text_GameboyKid1:
	.string "אפשר לראות בשטח את הפוקימונים\n"
	.string "הבולטים שחיים באזור!\p"
	.string "אבל כדאי לבדוק את הדרכים\n"
	.string "גם ביום וגם בלילה!$"

VioletCity_TrainerSchool_Text_GameboyKid2:
	.string "הפירות באזור ג'וטו טובים\n"
	.string "לריפוי ולהכנת כדורים.\p"
	.string "הפירות בקאנטו טובים\n"
	.string "להורדת הנתונים של פוקימון.\p"
	.string "הדוג'ו בקאנטו עוזר לפוקימונים\n"
	.string "לשכלל כל נתון בנפרד.$"

VioletCity_TrainerSchool_Text_Youngster2:
	.string "כדאי לדעת: היריבים משתמשים עכשיו\n"
	.string "בקבוצות עם כיסוי סוגים טוב יותר,\p"
	.string "אז המסע שלפניך יהיה מאתגר הרבה יותר.$"

VioletCity_TrainerSchool_Text_Blackboard:
	.string "על הלוח מתוארים\n"
	.string "מהלכי מ”נ של פוקימונים.\p"
	.string "אחרי שמ”נ נפתח, אין צורך ללמד\n"
	.string "אותו לפוקימון כדי להשתמש בו.$"

VioletCity_TrainerSchool_Text_Notebook:
	.string "It's this kid's notebook…\p"
	.string "Catch POKéMON using POKé BALLS.\p"
	.string "Up to six can be in your party.\p"
	.string "Keep reading?$"

VioletCity_TrainerSchool_Text_Notebook1:
	.string "Before throwing a POKé BALL,\n"
	.string "weaken the target first.\p"
	.string "A poisoned or burned POKéMON\n"
	.string "is easier to catch.\p"
	.string "Keep reading?$"

VioletCity_TrainerSchool_Text_Notebook2:
	.string "Some moves may cause confusion.\p"
	.string "Confusion may make a POKéMON\n"
	.string "attack itself.\p"
	.string "Leaving battle clears up any\n"
	.string "confusion.\p"
	.string "Keep reading?$"

VioletCity_TrainerSchool_Text_Notebook3:
	.string "People who catch and use\n"
	.string "POKéMON in battle are POKéMON\n"
	.string "trainers.\p"
	.string "They are expected to visit\n"
	.string "POKéMON GYMS and defeat other\n"
	.string "trainers.\p"
	.string "The next page is… Blank!\p"
	.string "Boy: E-he-he…\p"
	.string "I haven't written anymore…$"

VioletCity_TrainerSchool_Text_StickerMachine:
	.string "This super machine prints data\n"
	.string "out as stickers!$"
