GoldenrodCity_DepartmentStore_3F_hns_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, GoldenrodDeptElevator_OnFrame
	.byte 0

GoldenrodDeptStore3_EventScript_Nerd::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_3FSuperNerd, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore3_EventScript_Sign::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_3FDirectory, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore3_EventScript_Rocker::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_3FRocker, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore_Text_3FSuperNerd:
    .string "אני, אני, אני ממש חסרת סבלנות!\p"
    .string "אני משתמשת במהירות X בקרב כדי\n"
    .string "להאיץ את הפוקימון שלי.$"

GoldenrodDeptStore_Text_3FRocker:
    .string "היי! כשאתה נלחם, אתה משתמש\n"
    .string "ב”מיוחד X”?\p"
    .string "זה מעולה. זה ממש מקפיץ את\n"
    .string "ההתקפה המיוחדת!$"

GoldenrodDeptStore3_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart GoldenrodDeptStore3_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
GoldenrodDeptStore3_Pokemart:
	.2byte ITEM_X_SPEED
	.2byte ITEM_X_SP_ATK
	.2byte ITEM_X_ATTACK
	.2byte ITEM_X_DEFENSE
	.2byte ITEM_DIRE_HIT
	.2byte ITEM_GUARD_SPEC
	.2byte ITEM_X_ACCURACY
	pokemartlistend

GoldenrodDeptStore_Text_3FDirectory:
    .string "למחפשי הניצחון\p"
    .string "ק3: ציוד קרב$"
