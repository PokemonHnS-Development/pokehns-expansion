PalletTown_RedsHouse_2F_hns_MapScripts::
	.byte 0

PalletTown_RedsHouse_2F_EventScript_NES::
	msgbox RedsHouse_Text_NES, MSGBOX_SIGN
	end

PalletTown_RedsHouse_2F_EventScript_PC::
	msgbox RedsHouse_Text_PC, MSGBOX_SIGN
	end

RedsHouse_Text_NES:
	.string "{PLAYER} שיחק בקונסולת ה-NES.\p"
	.string "כדאי לזוז - אין זמן לבזבז!$"

RedsHouse_Text_PC:
	.string "נראה שלא השתמשו בו\n"
	.string "כבר הרבה זמן…$"
