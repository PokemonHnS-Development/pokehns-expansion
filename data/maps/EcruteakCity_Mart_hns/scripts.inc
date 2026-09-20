EcruteakCity_Mart_hns_MapScripts::
	.byte 0

EcruteakCity_Mart_EventScript_Nerd::
	lock
	faceplayer
	msgbox EcruteakMart_Text_SuperNerd, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_Mart_EventScript_Granny::
	lock
	faceplayer
	msgbox EcruteakMart_Text_Granny, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakMart_Text_SuperNerd:
	.string "Mi EEVEE evolucionó a ESPEON.\p"
	.string "Pero el EEVEE de mi amigo se volvió\n"
	.string "un UMBREON.\p"
	.string "Me pregunto por qué. Ambos criamos\n"
	.string "a nuestros EEVEE igual...$"

EcruteakMart_Text_Granny:
	.string "Si usas REVIVIR, un POKéMON que\n"
	.string "esté debilitado despertará.$"
