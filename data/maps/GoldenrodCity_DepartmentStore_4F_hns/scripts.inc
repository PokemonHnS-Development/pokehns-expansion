GoldenrodCity_DepartmentStore_4F_hns_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, GoldenrodDeptElevator_OnFrame
	.byte 0

GoldenrodDeptStore4_EventScript_Cooltrainer::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_4FCooltrainerM, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore4_EventScript_BugCatcher::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_4FBugCatcher, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore4_EventScript_GBAKid::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_4FGameboyKid, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore4_EventScript_Sign::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_4FDirectory, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore_Text_4FCooltrainerM:
    .string "היי. אני אוהב פוקימונים חזקים.\p"
    .string "אני מאכיל אותם בחלבון כדי להגביר\n"
    .string "את ההתקפה שלהם.$"

GoldenrodDeptStore_Text_4FBugCatcher:
    .string "ברזל מגביר את ההגנה של\n"
    .string "הפוקימון שלך.$"

GoldenrodDeptStore_Text_4FGameboyKid:
    .string "היו שמועות שחלק מהפוקימונים\n"
    .string "מתפתחים רק בהחלפה בכבל קישור.\p"
    .string "פפף…\p"
    .string "איזה מידע שגוי.\p"
    .string "אני מכיר כמה מהפוקימונים האלה:\n"
    .string "מאצ'וק, קדברה, האנטר ו… אה, גרבלר.\p"
    .string "אבל כולם מתפתחים בעליית רמה.$"

GoldenrodDeptStore4_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart GoldenrodDeptStore4_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
GoldenrodDeptStore4_Pokemart:
	.2byte ITEM_PROTEIN
	.2byte ITEM_CALCIUM
	.2byte ITEM_IRON
	.2byte ITEM_ZINC
	.2byte ITEM_CARBOS
	.2byte ITEM_HP_UP
	pokemartlistend

GoldenrodDeptStore_Text_4FDirectory:
    .string "נחזק לך את הפוקימונים!\p"
    .string "ק4: ארון התרופות$"
