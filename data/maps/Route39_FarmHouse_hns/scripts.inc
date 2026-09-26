Route39_FarmHouse_hns_MapScripts::
	.byte 0


Route39House_EventScript_FarmerF::
	lock
	faceplayer
	goto_if_eq VAR_ROUTE39_BARN, 5, Route39House_EventScript_FarmerFAfter
	msgbox Route39_Text_FarmerFInTrouble, MSGBOX_DEFAULT
	closemessage
	release
	end

Route39House_EventScript_FarmerFAfter::
	goto_if_set FLAG_GOT_TM_SNATCH, Route39House_EventScript_FarmerFAfterTM
	msgbox Route39_Text_FarmerFHealedMiltank, MSGBOX_DEFAULT
	giveitem ITEM_TM_SNATCH
	msgbox Route39_Text_FarmerFSnatchSpeech, MSGBOX_DEFAULT
	closemessage 
	setflag FLAG_GOT_TM_SNATCH
	release
	end

Route39House_EventScript_FarmerFAfterTM::
	msgbox Route39_Text_FarmerFSnatchSpeech, MSGBOX_DEFAULT
	closemessage
	release
	end

Route39_FarmHouse_EventScript_FarmerM::
	lock
	faceplayer
	goto_if_lt VAR_ROUTE39_BARN, 5, Route39_FarmHouse_EventScript_FarmerM_Sick
	showmoneybox 0, 0
	msgbox Route39_Text_FarmerMBuyMilk, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE, Route39_FarmHouse_EventScript_FarmerMBuyMilk
	msgbox Route39_Text_FarmerMNoSale, MSGBOX_DEFAULT
	hidemoneybox
	closemessage
	end

Route39_FarmHouse_EventScript_FarmerMBuyMilk::
	checkmoney 500, 0
	goto_if_eq VAR_RESULT, FALSE, Route39_FarmHouse_EventScript_FarmerM_NotEnough
	additem ITEM_MOOMOO_MILK
	goto_if_eq VAR_RESULT, FALSE, Route39_FarmHouse_EventScript_FarmerM_BagFull
	removemoney 500
	updatemoneybox 0
	msgbox Route39FarmHouse_Text_WouldYouLikeAnother, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE, Route39_FarmHouse_EventScript_FarmerMBuyMilk

	
	msgbox Route39_Text_FarmerMGotMilk, MSGBOX_DEFAULT
	closemessage
	playse MUS_OBTAIN_ITEM
	msgbox Route39_Text_GotMilk, MSGBOX_DEFAULT
	closemessage
	hidemoneybox
	release
	end

Route39_FarmHouse_EventScript_FarmerM_Sick::
	msgbox Route39_Text_FarmerMSickCow, MSGBOX_DEFAULT
	closemessage
	release
	end

Route39_FarmHouse_EventScript_FarmerM_BagFull::
	msgbox Route39_Text_FarmerMNoRoom, MSGBOX_DEFAULT
	hidemoneybox
	closemessage
	release
	end

Route39_FarmHouse_EventScript_FarmerM_NotEnough::
	msgbox Route39_Text_FarmerMNoMoney, MSGBOX_DEFAULT
	closemessage
	hidemoneybox
	release
	end

Route39_Text_FarmerMSickCow:
	.string "Mi MILTANK ya no me da\nleche.\pEsta GRANJA tiene leche famosa.\pCasi todos quieren probarla.\pMe dará un montón de leche si\nle doy muchas BAYAS,\lsupongo.$"

Route39_Text_FarmerMBuyMilk:
	.string "¿Quieres mi LECHE MU-MU?\p"
	.string "Es mi mayor orgullo.\p"
	.string "¡Dásela a POKéMON para curar PS!\p"
	.string "Te la daré por solo\n"
	.string "¥500.$"

Route39_Text_FarmerMGotMilk:
	.string "¡Aquí tiene!\n"
	.string "¡Bebe y disfruta!$"

Route39_Text_FarmerMNoMoney:
	.string "Lo siento.\n"
	.string "¡Sin dinero no hay venta!$"

Route39_Text_FarmerMNoRoom:
	.string "Diría que tu MOCHILA está llena.$"

Route39_Text_FarmerMNoSale:
	.string "¿No lo quieres?\n"
	.string "¡Vuelve pronto, ¿eh?$"

Route39FarmHouse_Text_WouldYouLikeAnother:
	.string "¿Qué tal otra?$"

Route39_Text_GotMilk:
	.string "{PLAYER} obtuvo LECHE MOOMOO.$"

Route39_Text_FarmerMMilking:
	.string "Mejor voy a ordeñar.$"

Route39_Text_FarmerFInTrouble:
	.string "Nuestra leche llega hasta\nKANTO.\pAsí que si nuestro MILTANK\nno nos da leche, es un problema.$"

Route39_Text_FarmerFHealedMiltank:
	.string "Arreglaste a nuestro MILTANK, cariño.\nAhora vuelve a dar LECHE MOOMOO.\pAquí tienes algo por tu molestia.$"

Route39_Text_FarmerFSnatchSpeech:
	.string "Eso es un SNATCH.\p"
	.string "Es un movimiento astuto que\n"
	.string "permite a un POKéMON robar el\l"
	.string "movimiento rival antes de usarlo.\p"
	.string "Si varios POKéMON usan\n"
	.string "ARREBATO, solo el más lento\l"
	.string "logrará robar el movimiento.\p"
	.string "Úsalo con maña. El tiempo lo es\n"
	.string "todo.$"
