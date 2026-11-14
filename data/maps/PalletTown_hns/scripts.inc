PalletTown_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, PalletTown_EventScript_CityEnter
	.byte 0

PalletTown_EventScript_CityEnter::
	setflag FLAG_VISITED_PALLET_TOWN
	end

PalletTown_EventScript_Woman::
	msgbox PalletTown_Text_Teacher, MSGBOX_NPC
	end
PalletTown_EventScript_Fatman::
	msgbox PalletTown_Text_Fisher, MSGBOX_NPC
	end
PalletTown_EventScript_TownSign::
	msgbox PalletTown_Text_Sign, MSGBOX_SIGN
	end	
PalletTown_EventScript_RedsHouseSign::
	msgbox PalletTown_Text_RedsHouseSign, MSGBOX_SIGN
	end
PalletTown_EventScript_BluesHouseSign::
	msgbox PalletTown_Text_BluesHouseSign, MSGBOX_SIGN
	end	
PalletTown_EventScript_OaksLabSign::
	msgbox PalletTown_Text_OaksLabSign, MSGBOX_SIGN
	end	

PalletTown_Text_Teacher:
	.string "גם אני מגדלת פוקימונים.\p"
	.string "הם משמשים לי שומרי ראש\n"
	.string "פרטיים.$"

PalletTown_Text_Fisher:
	.string "הטכנולוגיה מדהימה!\p"
	.string "היום אפשר להחליף פוקימונים\n"
	.string "דרך הזמן, כמו דוא”ל.$"

PalletTown_Text_Sign:
	.string "העיירה פאלט\p"
	.string "פינה שלווה של שלום\n"
	.string "וטוהר$"

PalletTown_Text_RedsHouseSign:
	.string "RED'S HOUSE$"

PalletTown_Text_OaksLabSign:
	.string "מעבדת מחקר הפוקימונים\n"
	.string "של אוק$"

PalletTown_Text_BluesHouseSign:
	.string "BLUE'S HOUSE$"
