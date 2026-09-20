OlivineCity_Cafe_hns_MapScripts::
	.byte 0

OlivineCity_Cafe_EventScript_Jasmine::
	lock
	faceplayer
	msgbox OlivineCity_Cafe_Text_Jasmine, MSGBOX_DEFAULT
	closemessage
	fadescreenswapbuffers FADE_TO_BLACK
	setflag FLAG_HIDE_CAFE_JASMINE
	removeobject LOCALID_CAFE_JASMINE
	fadescreenswapbuffers FADE_FROM_BLACK
	clearflag FLAG_HIDE_DOJO_JASMINE
	release
	end

OlivineCity_Cafe_Text_Jasmine:
	.string "Oh... Hola, {PLAYER}.\p"
	.string "Estos platos que tengo enfrente\n"
	.string "no son todos míos...\p"
	.string "Uh...\p"
	.string "En realidad, la persona que estuvo\n"
	.string "aquí antes que yo comió mucho...\p"
	.string "Si quieres luchar otra vez,\n"
	.string "visítame en el DOJO DE LUCHA\l"
	.string "de CIUDAD AZAFRÁN.$"

OlivineCity_EventScript_SailorA::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_HM_STRENGTH, OlivineCity_EventScript_SailorA2
	msgbox OlivineCity_Text_CafeSailorStrength, MSGBOX_DEFAULT
	giveitem ITEM_HM_STRENGTH
	setflag FLAG_RECEIVED_HM_STRENGTH
OlivineCity_EventScript_SailorA2::
	msgbox OlivineCity_Text_CafeSailorGotStrength, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_EventScript_Cook::
	lock
	faceplayer
	msgbox OlivineCity_Text_CafeFishingGuru, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_EventScript_SailorB::
	lock
	faceplayer
	msgbox OlivineCity_Text_CafeSailor, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_Text_CafeSailorStrength:
	.string "¡Ja! Tus POKéMON parecen\n"
	.string "muy debiluchos!\p"
	.string "No tienen el poder para\n"
	.string "mover rocas del camino.\p"
	.string "Toma, usa esto y enséñales\n"
	.string "¡FUERZA!$"

OlivineCity_Text_CafeSailorGotStrength:
	.string "¡En el mar, lo único en lo que\n"
	.string "puedes confiar es en ti mismo!\p"
	.string "¡Estoy orgulloso de mi cuerpo!\n"
	.string "¡Deberías entrenar como yo!$"

OlivineCity_Text_CafeFishingGuru:
	.string "El menú del CAFÉ OLIVO está lleno\n"
	.string "de platos fuertes para\l"
	.string "¡MARINEROS fuertes como yo!$"

OlivineCity_Text_CafeSailor:
	.string "Cada vez que llego a este pueblo,\n"
	.string "siempre visito el CAFÉ OLIVO.\p"
	.string "Todo en el menú me hace\n"
	.string "me siento fuerte. ¡No dejo de comer!$"

