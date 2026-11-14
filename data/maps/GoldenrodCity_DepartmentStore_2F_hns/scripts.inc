GoldenrodCity_DepartmentStore_2F_hns_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, GoldenrodDeptElevator_OnFrame
	.byte 0

GoldenrodDeptStore2_EventScript_Youngster::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_2FYoungster, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore2_EventScript_CooltrainerF::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_2FCooltrainerF, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore2_EventScript_Gent::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_2FGentleman, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore2_EventScript_Sign::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_2FDirectory, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore_Text_2FYoungster:
    .string "הפוקיגיר יכול לשמור עד 100\n"
    .string "מספרי טלפון.\p"
    .string "קשה להחליט אילו מספרים\n"
    .string "לשמור.$"

GoldenrodDeptStore_Text_2FCooltrainerF:
    .string "את האברה שלי קיבלתי במשחקייה.\p"
    .string "עכשיו הוא השותף הכי טוב שלי.$"

GoldenrodDeptStore_Text_2FGentleman:
    .string "הכלבו הזה גורם לי להבין\n"
    .string "שגולדנרוד היא עיר גדולה.\p"
    .string "אין מבחר כזה בשום מקום אחר.$"

GoldenrodDeptStore2_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart GoldenrodDeptStore2_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
GoldenrodDeptStore2_Pokemart:
	.2byte ITEM_POKE_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_FIRE_STONE
	.2byte ITEM_WATER_STONE
	.2byte ITEM_THUNDER_STONE
	.2byte ITEM_POTION
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_HYPER_POTION
	.2byte ITEM_MAX_POTION
	.2byte ITEM_REVIVE
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_BURN_HEAL
	.2byte ITEM_ICE_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_FULL_HEAL
	.2byte ITEM_ESCAPE_ROPE
	.2byte ITEM_REPEL
	.2byte ITEM_SUPER_REPEL
	.2byte ITEM_MAX_REPEL
	pokemartlistend

GoldenrodDeptStore_EventScript_VendingMachine::
	lockall
	message GoldenrodDeptStore_Text_WhichDrinkWouldYouLike
	waitmessage
	showmoneybox 0, 0
	goto GoldenrodDeptStore_EventScript_ChooseDrink
	end

GoldenrodDeptStore_EventScript_ChooseDrink::
	multichoice 16, 0, MULTI_VENDING_MACHINE, FALSE
	copyvar VAR_TEMP_1, VAR_RESULT
	switch VAR_TEMP_1
	case 0, GoldenrodDeptStore_EventScript_FreshWater
	case 1, GoldenrodDeptStore_EventScript_SodaPop
	case 2, GoldenrodDeptStore_EventScript_Lemonade
	msgbox GoldenrodDeptStore_Text_DecidedAgainstBuyingDrink, MSGBOX_DEFAULT
	goto GoldenrodDeptStore_EventScript_ExitVendingMachine
	end

GoldenrodDeptStore_EventScript_FreshWater::
	setvar VAR_TEMP_0, ITEM_FRESH_WATER
	goto GoldenrodDeptStore_EventScript_TryBuyDrink
	end

GoldenrodDeptStore_EventScript_SodaPop::
	setvar VAR_TEMP_0, ITEM_SODA_POP
	goto GoldenrodDeptStore_EventScript_TryBuyDrink
	end

GoldenrodDeptStore_EventScript_Lemonade::
	setvar VAR_TEMP_0, ITEM_LEMONADE
	goto GoldenrodDeptStore_EventScript_TryBuyDrink
	end

GoldenrodDeptStore_EventScript_CheckMoneyFreshWater::
	checkmoney 200
	return

GoldenrodDeptStore_EventScript_CheckMoneySodaPop::
	checkmoney 300
	return

GoldenrodDeptStore_EventScript_CheckMoneyLemonade::
	checkmoney 350
	return

GoldenrodDeptStore_EventScript_RemoveMoneyFreshWater::
	removemoney 200
	return

GoldenrodDeptStore_EventScript_RemoveMoneySodaPop::
	removemoney 300
	return

GoldenrodDeptStore_EventScript_RemoveMoneyLemonade::
	removemoney 350
	return

GoldenrodDeptStore_EventScript_TryBuyDrink::
	call_if_eq VAR_TEMP_1, 0, GoldenrodDeptStore_EventScript_CheckMoneyFreshWater
	call_if_eq VAR_TEMP_1, 1, GoldenrodDeptStore_EventScript_CheckMoneySodaPop
	call_if_eq VAR_TEMP_1, 2, GoldenrodDeptStore_EventScript_CheckMoneyLemonade
	goto_if_eq VAR_RESULT, FALSE, GoldenrodDeptStore_EventScript_NotEnoughMoney
	checkitemspace VAR_TEMP_0
	goto_if_eq VAR_RESULT, FALSE, GoldenrodDeptStore_EventScript_NoRoomForDrink
	call_if_eq VAR_TEMP_1, 0, GoldenrodDeptStore_EventScript_RemoveMoneyFreshWater
	call_if_eq VAR_TEMP_1, 1, GoldenrodDeptStore_EventScript_RemoveMoneySodaPop
	call_if_eq VAR_TEMP_1, 2, GoldenrodDeptStore_EventScript_RemoveMoneyLemonade
	updatemoneybox
	bufferitemname STR_VAR_1, VAR_TEMP_0
	playse SE_VEND
	msgbox GoldenrodDeptStore_Text_DrinkClankedDown, MSGBOX_DEFAULT
	additem VAR_TEMP_0
	bufferitemname STR_VAR_2, VAR_TEMP_0
	bufferstdstring STR_VAR_3, STDSTRING_MEDICINE
	msgbox gText_PutItemInPocket, MSGBOX_DEFAULT
	random 64
	goto_if_ne VAR_RESULT, 0, GoldenrodDeptStore_EventScript_ChooseNewDrink
	checkitemspace VAR_TEMP_0
	goto_if_eq VAR_RESULT, FALSE, GoldenrodDeptStore_EventScript_NoRoomForDrink
	playse SE_VEND
	msgbox GoldenrodDeptStore_Text_ExtraDrinkClankedDown, MSGBOX_DEFAULT
	additem VAR_TEMP_0
	bufferitemname STR_VAR_2, VAR_TEMP_0
	bufferstdstring STR_VAR_3, STDSTRING_MEDICINE
	msgbox gText_PutItemInPocket, MSGBOX_DEFAULT
	random 64
	goto_if_ne VAR_RESULT, 0, GoldenrodDeptStore_EventScript_ChooseNewDrink
	checkitemspace VAR_TEMP_0
	goto_if_eq VAR_RESULT, 0, GoldenrodDeptStore_EventScript_NoRoomForDrink
	playse SE_VEND
	msgbox GoldenrodDeptStore_Text_ExtraDrinkClankedDown, MSGBOX_DEFAULT
	additem VAR_TEMP_0
	bufferitemname STR_VAR_2, VAR_TEMP_0
	bufferstdstring STR_VAR_3, STDSTRING_MEDICINE
	msgbox gText_PutItemInPocket, MSGBOX_DEFAULT
	goto GoldenrodDeptStore_EventScript_ChooseNewDrink
	end

GoldenrodDeptStore_EventScript_ChooseNewDrink::
	message GoldenrodDeptStore_Text_WhichDrinkWouldYouLike
	waitmessage
	goto GoldenrodDeptStore_EventScript_ChooseDrink
	end

GoldenrodDeptStore_EventScript_NotEnoughMoney::
	msgbox GoldenrodDeptStore_Text_NotEnoughMoney, MSGBOX_DEFAULT
	goto GoldenrodDeptStore_EventScript_ExitVendingMachine
	end

GoldenrodDeptStore_EventScript_NoRoomForDrink::
	msgbox gText_TheBagIsFull, MSGBOX_DEFAULT
	goto GoldenrodDeptStore_EventScript_ExitVendingMachine
	end

GoldenrodDeptStore_EventScript_ExitVendingMachine::
	hidemoneybox
	releaseall
	end

GoldenrodDeptStore_Text_WhichDrinkWouldYouLike:
	.string "זו מכונת ממכר.\n"
	.string "איזה משקה תרצה?$"

GoldenrodDeptStore_Text_DrinkClankedDown:
	.string "קלאנג!\p"
	.string "נפלה פחית {STR_VAR_1}.$"

GoldenrodDeptStore_Text_ExtraDrinkClankedDown:
	.string "קלאנג!\p"
	.string "יש! נפלה עוד פחית\n"
	.string "{STR_VAR_1}!$"

GoldenrodDeptStore_Text_NotEnoughMoney:
	.string "אין מספיק כסף…$"

GoldenrodDeptStore_Text_DecidedAgainstBuyingDrink:
	.string "החלטת לא לקנות משקה.$"

GoldenrodDeptStore_Text_2FDirectory:
    .string "השותף שלך לדרך\p"
    .string "ק2: שוק המאמנים$"
