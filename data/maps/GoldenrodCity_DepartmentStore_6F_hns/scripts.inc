GoldenrodCity_DepartmentStore_6F_hns_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, GoldenrodDeptElevator_OnFrame
	.byte 0

GoldenrodDeptStore6_EventScript_Whitney::
	lock
	faceplayer
	msgbox GoldenrodDeptStore6_Text_Whitney, MSGBOX_DEFAULT
	closemessage
	fadescreenswapbuffers FADE_TO_BLACK
	setflag FLAG_HIDE_DEPTSTORE_WHITNEY
	removeobject LOCALID_STORE_WHITNEY
	fadescreenswapbuffers FADE_FROM_BLACK
	clearflag FLAG_HIDE_DOJO_WHITNEY
	release
	end

GoldenrodDeptStore6_Text_Whitney:
	.string "¡{PLAYER}! ¡Qué sorpresa verte!\p"
	.string "Estoy buscando algo para\n"
	.string "mi MILTANK.\p"
	.string "Si quieres otra batalla, ve al\n"
	.string "¡DOJO DE LUCHA!$"

GoldenrodCity_DepartmentStore_6F_EventScript_Jose::
	lock
	faceplayer
	goto_if_set FLAG_GOLDENROD_NPC_TRADE_COMPLETED, GoldenrodCity_DepartmentStore_6F_EventScript_TradeCompleted
	ingame_trade INGAME_TRADE_MACHOP, GoldenrodCity_DepartmentStore_6F_Text_YouWillTradeWontYou, GoldenrodCity_DepartmentStore_6F_EventScript_DeclineTrade, GoldenrodCity_DepartmentStore_6F_EventScript_NotRequestedMon, GoldenrodCity_DepartmentStore_6F_Text_MonYouTakeCare
	setflag FLAG_GOLDENROD_NPC_TRADE_COMPLETED
	release
	end

GoldenrodCity_DepartmentStore_6F_EventScript_DeclineTrade::
	msgbox GoldenrodCity_DepartmentStore_6F_Text_YouWontTradeMe, MSGBOX_DEFAULT
	release
	end

GoldenrodCity_DepartmentStore_6F_EventScript_NotRequestedMon::
	bufferspeciesname STR_VAR_1, VAR_0x8009
	msgbox GoldenrodCity_DepartmentStore_6F_Text_ThisIsntAMon, MSGBOX_DEFAULT
	release
	end

GoldenrodCity_DepartmentStore_6F_EventScript_TradeCompleted::
	msgbox GoldenrodCity_DepartmentStore_6F_Text_After, MSGBOX_DEFAULT
	release
	end

GoldenrodCity_DepartmentStore_6F_Text_YouWillTradeWontYou:
	.string "¡Colecciono POKéMON!\n"
	.string "¿Tienes un {STR_VAR_1}?\p"
	.string "¿Quieres cambiarlo por mi\n"
	.string "{STR_VAR_2}?$"

GoldenrodCity_DepartmentStore_6F_Text_MonYouTakeCare:
	.string "¡Súper! ¡Ya tengo un {STR_VAR_1}!\p"
	.string "{STR_VAR_2}, ¡cuídate mucho!$"

GoldenrodCity_DepartmentStore_6F_Text_ThisIsntAMon:
	.string "Eh, no, no creo que sea así.\n"
	.string "Eso no es un {STR_VAR_1}.$"

GoldenrodCity_DepartmentStore_6F_Text_YouWontTradeMe:
	.string "You don't want to trade? Aww...$"

GoldenrodCity_DepartmentStore_6F_Text_After:
	.string "Hi, how's my old MACHOP doing?$"


GoldenrodDeptStore6_EventScript_Lass::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_6FLass, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore6_EventScript_Nerd::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_6FSuperNerd, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore6_EventScript_Sign::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_6FDirectory, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore_Text_6FLass:
    .string "¿Escuchas LUCKY CHANNEL?\p"
    .string "Dicen que para ganar,\n"
	.string "debes intercambiar POKéMON con\l"
    .string "mucha gente para obtener\l"
    .string "distintos números de ID.\p"
	.string "Sin embargo, intercambiar no es tan\n"
	.string "disponible como antes.$"

GoldenrodDeptStore_Text_6FSuperNerd:
    .string "Si estás cansado, prueba las\n"
    .string "bebidas de la máquina.\p"
    .string "Tus POKéMON también las amarán.$"

GoldenrodDeptStore_Text_6FDirectory:
    .string "¡Tómate un respiro de las compras!\p"
    .string "6F PLAZA TRANQUILA$"
