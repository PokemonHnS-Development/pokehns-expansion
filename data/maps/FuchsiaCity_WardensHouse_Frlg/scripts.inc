FuchsiaCity_WardensHouse_Frlg_MapScripts::
	.byte 0

FuchsiaCity_WardensHouse_EventScript_Warden::
	lock
	faceplayer
	goto_if_set FLAG_GOT_HM04, FuchsiaCity_WardensHouse_EventScript_ExplainStrength
	goto_if_set FLAG_HIDE_SAFARI_ZONE_WEST_GOLD_TEETH, FuchsiaCity_WardensHouse_EventScript_GiveGoldTeeth
	msgbox FuchsiaCity_WardensHouse_Text_HifFuffHefifoo, MSGBOX_YESNO
	call_if_eq VAR_RESULT, YES, FuchsiaCity_WardensHouse_EventScript_WardenYes
	call_if_eq VAR_RESULT, NO, FuchsiaCity_WardensHouse_EventScript_WardenNo
	release
	end

FuchsiaCity_WardensHouse_EventScript_GiveGoldTeeth::
	textcolor NPC_TEXT_COLOR_NEUTRAL
	playfanfare MUS_OBTAIN_TMHM
	message FuchsiaCity_WardensHouse_Text_GaveGoldTeethToWarden
	waitmessage
	waitfanfare
	msgbox FuchsiaCity_WardensHouse_Text_WardenPoppedInHisTeeth
	call EventScript_RestorePrevTextColor
	checkplayergender
	call_if_eq VAR_RESULT, MALE, FuchsiaCity_WardensHouse_EventScript_WardenThanksMale
	call_if_eq VAR_RESULT, FEMALE, FuchsiaCity_WardensHouse_EventScript_WardenThanksFemale
	giveitem_msg FuchsiaCity_WardensHouse_Text_ReceivedHM04FromWarden, ITEM_HM04
	setflag FLAG_GOT_HM04
	removeitem ITEM_GOLD_TEETH
	release
	end

FuchsiaCity_WardensHouse_EventScript_WardenThanksMale::
	msgbox FuchsiaCity_WardensHouse_Text_ThanksSonGiveYouSomething
	return

FuchsiaCity_WardensHouse_EventScript_WardenThanksFemale::
	msgbox FuchsiaCity_WardensHouse_Text_ThanksLassieGiveYouSomething
	return

FuchsiaCity_WardensHouse_EventScript_WardenYes::
	msgbox FuchsiaCity_WardensHouse_Text_AhHowheeHoHoo
	return

FuchsiaCity_WardensHouse_EventScript_WardenNo::
	msgbox FuchsiaCity_WardensHouse_Text_HeOhayHeHaHoo
	return

FuchsiaCity_WardensHouse_EventScript_ExplainStrength::
	msgbox FuchsiaCity_WardensHouse_Text_ExplainStrength
	release
	end

FuchsiaCity_WardensHouse_EventScript_DisplaySign1::
	msgbox FuchsiaCity_WardensHouse_Text_MonPhotosFossilsOnDisplay, MSGBOX_SIGN
	end

FuchsiaCity_WardensHouse_EventScript_DisplaySign2::
	msgbox FuchsiaCity_WardensHouse_Text_OldMonMerchandiseOnDisplay, MSGBOX_SIGN
	end

FuchsiaCity_WardensHouse_Text_HifFuffHefifoo::
	.string "ALCAIDE: ¡Ñif fuf fefiñó!\p"
	.string "Ña lof ña feef ee ñafaji ño.\n"
	.string "¡Ñeff ñee fwee!$"

FuchsiaCity_WardensHouse_Text_AhHowheeHoHoo::
	.string "¡Ña jowee ño ñoo!\n"
	.string "¡Eef ee ñafaji ño!$"

FuchsiaCity_WardensHouse_Text_HeOhayHeHaHoo::
	.string "¿Ña?\n"
	.string "¡E ohay je ja ju i jaje!$"

FuchsiaCity_WardensHouse_Text_GaveGoldTeethToWarden::
	.string "{PLAYER} entregó los DIENTES\n"
	.string "DE ORO al ALCAIDE.$"

FuchsiaCity_WardensHouse_Text_WardenPoppedInHisTeeth::
	.string "¡El GUARDA se puso los dientes!$"

FuchsiaCity_WardensHouse_Text_ThanksSonGiveYouSomething::
	.string "ALCAIDE: ¡Gracias, hijo!\n"
	.string "¡Salvaste mi vida!\p"
	.string "Nadie entendía ni una\n"
	.string "de lo que dije, ¡ni uno!\p"
	.string "Me daba vergüenza mostrar\n"
	.string "la cara, ¡ni en la OFICINA!\p"
	.string "Déjame darte algo por tu\n"
	.string "problemas.$"

FuchsiaCity_WardensHouse_Text_ThanksLassieGiveYouSomething::
	.string "WARDEN: ¡Gracias, muchacha!\n"
	.string "¡Salvaste mi vida!\p"
	.string "Nadie entendía ni una\n"
	.string "de lo que dije, ¡ni uno!\p"
	.string "Me daba vergüenza mostrar\n"
	.string "la cara, ¡ni en la OFICINA!\p"
	.string "Déjame darte algo por tu\n"
	.string "problemas.$"

FuchsiaCity_WardensHouse_Text_ReceivedHM04FromWarden::
	.string "{PLAYER} recibió la MO04\n"
	.string "del ALCAIDE.$"

FuchsiaCity_WardensHouse_Text_ExplainStrength::
	.string "ALCAIDE: Dentro de la MO04\n"
	.string "STRENGTH.\p"
	.string "Permite a los POKéMON mover rocas\n"
	.string "encontrarás...\p"
	.string "Ah sí, ¿encontraste el SECRETO\n"
	.string "CASA en la ZONA SAFARI?$"

@ Unused
FuchsiaCity_WardensHouse_Text_YouHaveTooMuchStuff::
	.string "¡Pero bueno! ¡Tu BOLSA\n"
	.string "¡está llena!$"

FuchsiaCity_WardensHouse_Text_MonPhotosFossilsOnDisplay::
	.string "Fotos y fósiles de POKéMON están\n"
	.string "en exhibición.$"

FuchsiaCity_WardensHouse_Text_OldMonMerchandiseOnDisplay::
	.string "Artículos antiguos de POKéMON están\n"
	.string "en exhibición.$"

