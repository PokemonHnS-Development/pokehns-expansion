MysteryGiftScript_OldSeaMap::
	setvaddress MysteryGiftScript_OldSeaMap
	lock
	faceplayer
	vgoto_if_set FLAG_RECEIVED_OLD_SEA_MAP, OldSeaMap_Obtained
	vgoto_if_set FLAG_CAUGHT_MEW, OldSeaMap_Obtained
	checkitem ITEM_OLD_SEA_MAP
	vgoto_if_eq VAR_RESULT, TRUE, OldSeaMap_Obtained
	vmessage sText_MysteryGiftOldSeaMapForYou
	waitmessage
	waitbuttonpress
	checkitemspace ITEM_OLD_SEA_MAP
	vgoto_if_eq VAR_RESULT, FALSE, OldSeaMap_NoBagSpace
	giveitem ITEM_OLD_SEA_MAP
	setflag FLAG_ENABLE_SHIP_FARAWAY_ISLAND
	setflag FLAG_RECEIVED_OLD_SEA_MAP
	vmessage sText_MysteryGiftOldSeaMapUseAtPort
	waitmessage
	waitbuttonpress
	release
	end

OldSeaMap_NoBagSpace:
	vmessage sText_MysteryGiftOldSeaMapBagFull
	waitmessage
	waitbuttonpress
	release
	end

OldSeaMap_Obtained:
	vmessage sText_MysteryGiftOldSeaMapThankYou
	waitmessage
	waitbuttonpress
	release
	end

sText_MysteryGiftOldSeaMapForYou:
	.string "Gracias por usar el sistema de\n"
	.string "REGALO MISTERIOSO.\p"
	.string "Déjame confirmar... ¿eres {PLAYER}?\p"
	.string "Recibimos este VIEJO MAPA MARINO\n"
	.string "dirigido a ti.$"

sText_MysteryGiftOldSeaMapUseAtPort:
	.string "Parece que sirve para el\n
puerto de CIUDAD CALAGUA.\p
¿Y si lo pruebas para ver\n
de qué se trata?$"

sText_MysteryGiftOldSeaMapThankYou:
	.string "Gracias por usar el sistema\n
de REGALO MISTERIOSO.$"

sText_MysteryGiftOldSeaMapBagFull:
	.string "Ah, lo siento, {PLAYER}.\n
Se llenó tu BOLSILLO DE OBJETOS CLAVE.\p
Guarda algo en tu PC,\n
y luego vuelve por esto.$"
