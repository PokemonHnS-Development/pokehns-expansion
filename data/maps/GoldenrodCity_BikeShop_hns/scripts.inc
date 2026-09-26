GoldenrodCity_BikeShop_hns_MapScripts::
	.byte 0

GoldenrodCity_BikeShop_EventScript_Clerk::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_BIKE, GoldenrodCity_BikeShop_EventScript_Clerk_BikeReceived
	msgbox GoldenrodCity_BikeShop_Text_ClerkIntro, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE, GoldenrodCity_BikeShop_EventScript_Clerk_BikeAgreed
	msgbox GoldenrodCity_BikeShop_Text_Refused, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_BikeShop_EventScript_Clerk_BikeAgreed::
	msgbox GoldenrodCity_BikeShop_Text_ClerkAgreed, MSGBOX_DEFAULT
	giveitem ITEM_BICYCLE
	setflag FLAG_RECEIVED_BIKE
	closemessage
	release
	end

GoldenrodCity_BikeShop_EventScript_Clerk_BikeReceived::
	msgbox GoldenrodCity_BikeShop_Text_Mainshop, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_BikeShop_EventScript_Clerk2::
	lock
	faceplayer
	msgbox GoldenrodCity_BikeShop_Text_Clerk2, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_BikeShop_EventScript_Bike::
	lock
	msgbox GoldenrodCity_BikeShop_Text_Bicycle, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_BikeShop_Text_Clerk2:
	.string "Usar la BICICLETA es tan simple como\n"
	.string "presionar un botón si la\l"
	.string "REGISTRAS desde la MOCHILA.\p"
	.string "Si necesitas ir más rápido,\n"
	.string "¡primero debes detenerte!\p"
	.string "Puede parecer un consejo\n"
	.string "extraño, pero solo puedes cambiar\l"
	.string "marchas en la BICICLETA parado.\p"
	.string "Presiona R cuando estés parado\n"
	.string "y la próxima vez que pedalees,\l"
	.string "¡alcanzarás mayor velocidad!$"

GoldenrodCity_BikeShop_Text_ClerkIntro:
    .string "...suspiro... Me mudé aquí, pero no\n"
    .string "vender mis BICICLETAS. ¿Por qué?\p"
    .string "¿Podrías usar una BICICLETA y\n"
    .string "hacer publicidad por mí?$"

GoldenrodCity_BikeShop_Text_ClerkAgreed:
    .string "¿En serio? ¡Genial!\p"
    .string "Dame tu nombre y teléfono,\n"
    .string "y te prestaré una BICICLETA.$"

GoldenrodCity_BikeShop_Text_BorrowedBicycle:
    .string "{PLAYER} tomó prestada una BICICLETA.$"

GoldenrodCity_BikeShop_Text_Mainshop:
	.string "El negocio ha estado difícil\n"
	.string "desde que nos mudamos de KANTO.\l"
	.string "¡Agradecemos tu ayuda!\p"
	.string "¿Puedes lucir nuestra tecnología\n"
	.string "patentada de cambio de marchas?\p"
	.string "Es tan simple como presionar R al\n"
	.string "estar detenido en tu BICICLETA.\p"
	.string "¡Cuidado! ¡Así irás más rápido!$"

GoldenrodCity_BikeShop_Text_Refused:
    .string "...suspiro... Oh, la amabilidad de\n"
    .string "la gente...$"

GoldenrodCity_BikeShop_Text_JustReleasedCompact:
    .string "¡Recién lanzadas!\p"
    .string "¡BICICLETAS compactas de primera!$"

GoldenrodCity_BikeShop_Text_Bicycle:
    .string "¡Es una BICICLETA nueva y brillante!$"
