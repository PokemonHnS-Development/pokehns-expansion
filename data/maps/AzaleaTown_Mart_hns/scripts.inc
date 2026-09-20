AzaleaTown_Mart_hns_MapScripts::
	.byte 0

AzaleaTown_Mart_EventScriptCooltrainerM::
	lock
	faceplayer
	msgbox AzaleaMart_Text_CooltrainerM, MSGBOX_DEFAULT
	closemessage
	release
	end

AzaleaTown_Mart_EventScriptBugCatcher::
	lock
	faceplayer
	msgbox AzaleaMart_Text_BugCatcher, MSGBOX_DEFAULT
	closemessage
	release
	end

AzaleaMart_Text_CooltrainerM:
	.string "¿Puedes comprar una GREAT BALL?\n"
	.string "Solo puedo comprar POKé BALLS.\p"
	.string "Oí que hay más objetos\n"
	.string "disponibles para comprar cuando\l"
	.string "ganas MEDALLAS de GIMNASIO!\p"
	.string "Desearía que KURT me hiciera\n"
	.string "algunas de sus BALLS custom.$"

AzaleaMart_Text_BugCatcher:
	.string "Una GREAT BALL es mejor para\n"
	.string "capturar POKéMON que una POKé BALL.\p"
	.string "Pero las de KURT podrían ser mejor\n"
	.string "veces.$"

