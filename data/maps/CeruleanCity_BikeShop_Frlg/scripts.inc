CeruleanCity_BikeShop_Frlg_MapScripts::
	.byte 0

CeruleanCity_BikeShop_EventScript_Clerk::
	lock
	faceplayer
	goto_if_set FLAG_GOT_BICYCLE, CeruleanCity_BikeShop_EventScript_AlreadyGotBicycle
	goto_if_set FLAG_GOT_BIKE_VOUCHER, CeruleanCity_BikeShop_EventScript_ExchangeBikeVoucher
	showmoneybox 0, 0
	message CeruleanCity_BikeShop_Text_WelcomeToBikeShop
	waitmessage
	multichoice 11, 0, MULTI_BIKE_SHOP, FALSE
	hidemoneybox
	showmoneybox 0, 0
	switch VAR_RESULT
	case 0, CeruleanCity_BikeShop_EventScript_TryPurchaseBicycle
	case 1, CeruleanCity_BikeShop_EventScript_ClerkGoodbye
	case 127, CeruleanCity_BikeShop_EventScript_ClerkGoodbye
	end

@ The Bicycle price / players money is never actually checked
CeruleanCity_BikeShop_EventScript_TryPurchaseBicycle::
	msgbox CeruleanCity_BikeShop_Text_SorryYouCantAffordIt
	goto CeruleanCity_BikeShop_EventScript_ClerkGoodbye
	end

CeruleanCity_BikeShop_EventScript_ClerkGoodbye::
	msgbox CeruleanCity_BikeShop_Text_ThankYouComeAgain
	hidemoneybox
	release
	end

CeruleanCity_BikeShop_EventScript_ExchangeBikeVoucher::
	msgbox CeruleanCity_BikeShop_Text_OhBikeVoucherHereYouGo
	msgreceiveditem CeruleanCity_BikeShop_Text_ExchangedVoucherForBicycle, ITEM_BICYCLE, 1, MUS_RG_OBTAIN_KEY_ITEM
	setflag FLAG_GOT_BICYCLE
	additem ITEM_BICYCLE
	removeitem ITEM_BIKE_VOUCHER
	msgbox CeruleanCity_BikeShop_Text_ThankYouComeAgain
	release
	end

CeruleanCity_BikeShop_EventScript_AlreadyGotBicycle::
	msgbox CeruleanCity_BikeShop_Text_HowDoYouLikeNewBicycle
	release
	end

@ Unused
CeruleanCity_BikeShop_EventScript_NoRoomForBicycle::
	msgbox CeruleanCity_BikeShop_Text_MakeRoomForBicycle
	release
	end

CeruleanCity_BikeShop_EventScript_Woman::
	msgbox CeruleanCity_BikeShop_Text_CityBikeGoodEnoughForMe, MSGBOX_NPC
	end

CeruleanCity_BikeShop_EventScript_Youngster::
	lock
	faceplayer
	goto_if_set FLAG_GOT_BICYCLE, CeruleanCity_BikeShop_EventScript_YoungsterHaveBike
	msgbox CeruleanCity_BikeShop_Text_BikesCoolButExpensive
	release
	end

CeruleanCity_BikeShop_EventScript_YoungsterHaveBike::
	msgbox CeruleanCity_BikeShop_Text_WowYourBikeIsCool
	release
	end

CeruleanCity_BikeShop_EventScript_Bicycle::
	msgbox CeruleanCity_BikeShop_Text_ShinyNewBicycle, MSGBOX_SIGN
	end

CeruleanCity_BikeShop_Text_WelcomeToBikeShop::
	.string "Hi!\n"
	.string "Bienvenidos a nuestra TIENDA DE BICICLETAS.\p"
	.string "¿Tenemos justo la BICI para\n"
	.string "eres!$"

CeruleanCity_BikeShop_Text_SorryYouCantAffordIt::
	.string "¡Lo siento!\n"
	.string "¡No te alcanza el dinero!$"

CeruleanCity_BikeShop_Text_OhBikeVoucherHereYouGo::
	.string "Oh, eso es...\p"
	.string "¡UN VALE BICI!\p"
	.string "¡Está bien!\n"
	.string "¡Toma!$"

CeruleanCity_BikeShop_Text_ExchangedVoucherForBicycle::
	.string "{PLAYER} cambió el\n"
	.string "BIKE VOUCHER for a BICYCLE.$"

CeruleanCity_BikeShop_Text_ThankYouComeAgain::
	.string "¡Gracias!\n"
	.string "Come back again sometime!$"

CeruleanCity_BikeShop_Text_HowDoYouLikeNewBicycle::
	.string "¿Qué te parece tu nueva BICICLETA?\n"
	.string "¿Te gusta cómo anda?\p"
	.string "Puedes sacarlo en la RUTA CICLISTA\n"
	.string "¡por la RUTA y hasta en cuevas!$"

CeruleanCity_BikeShop_Text_MakeRoomForBicycle::
	.string "Más te vale hacer espacio para tu\n"
	.string "BICYCLE!$"

CeruleanCity_BikeShop_Text_CityBikeGoodEnoughForMe::
	.string "Una bici común de ciudad es\nsuficiente"
	.string "para mí.\p"
	.string "Después de todo, no puedes poner una\n"
	.string "canasta en una bicicleta de montaña.$"

CeruleanCity_BikeShop_Text_BikesCoolButExpensive::
	.string "Estas bicis son geniales, pero no\n"
	.string "way expensive!$"

CeruleanCity_BikeShop_Text_WowYourBikeIsCool::
	.string "Wow.\n"
	.string "¡Tu BICI es muy genial!$"

@ Unused
CeruleanCity_BikeShop_Text_GermanFoldableBicyleFinallyOnMarket::
	.string "ついに　はつばい！\p"
	.string "ドイツ　せい　さいこうきゅう\n"
	.string "おりたたみ　じてんしゃ！$"

CeruleanCity_BikeShop_Text_ShinyNewBicycle::
	.string "¡Una BICICLETA nueva y brillante!$"

