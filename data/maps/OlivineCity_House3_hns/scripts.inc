OlivineCity_House3_hns_MapScripts::
	.byte 0

OlivineCityHouse3_EventScriptFishingGuru::
	lock
	faceplayer
	checkitem ITEM_GOOD_ROD
	goto_if_eq VAR_RESULT, TRUE, OlivineCityHouse3_EventScriptFishingGuru2
	msgbox OlivineCity_Text_OfferGoodRod, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, OlivineCityHouse3_EventScriptFishingGuruRefused
	msgbox OlivineCity_Text_GiveGoodRod, MSGBOX_DEFAULT
	giveitem ITEM_GOOD_ROD
	msgbox OlivineCity_Text_GaveGoodRod, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCityHouse3_EventScriptFishingGuru2::
	msgbox OlivineCity_Text_HaveGoodRod, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCityHouse3_EventScriptFishingGuruRefused::
	msgbox OlivineCity_Text_DontWantGoodRod, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_Text_OfferGoodRod:
	.string "¡CIUDAD OLIVO está en el mar!\p"
	.string "Y si está en el mar, ¡seguro\n"
	.string "que hay muchos peces!\p"
	.string "He pescado aquí por 30 años.\p"
	.string "¿Te gustaría mirar el mar\n"
	.string "y probar tu suerte pescando?$"

OlivineCity_Text_GiveGoodRod:
	.string "¡Ah, jajaja! ¡Tenemos a un\n"
	.string "nuevo pescador en potencia!$"

OlivineCity_Text_GaveGoodRod:
	.string "Los peces no solo están en el\n"
	.string "mar; están en cualquier lugar\l"
	.string "donde haya agua.\p"
	.string "Por cierto, tu POKéDEX muestra\n"
	.string "grupos de pesca de POKéMON.\p"
	.string "Distintos puntos pueden tener\n"
	.string "tipos de peces similares.$"

OlivineCity_Text_DontWantGoodRod:
	.string "¿Quééé? ¡¿No te gusta pescar?!\n"
	.string "¡Eso es incomprensible!$"

OlivineCity_Text_HaveGoodRod:
	.string "¿Cómo va todo?\n"
	.string "¿Atrapaste al pez grande?$"
