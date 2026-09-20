GoldenrodCity_House1_hns_MapScripts::
	.byte 0

GoldenrodCity_NameRatersHouse_EventScript_ToggleShinies::
	lock
	msgbox GoldenrodCity_NameRatersHouse_Text_AskToggleShinies, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, GoldenrodCity_NameRatersHouse_EventScript_ToggleShiniesRefused
	@special ToggleShinyColors
	msgbox GoldenrodCity_NameRatersHouse_Text_ToggleShinies, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_NameRatersHouse_EventScript_ToggleShiniesRefused::
	release
	end

GoldenrodCity_NameRatersHouse_Text_AskToggleShinies:
	.string "¿Quieres cambiar el ajuste de\n"
	.string "Colores Shiny Únicos?$"

GoldenrodCity_NameRatersHouse_Text_ToggleShinies:
	.string "¡Colores Shiny cambiados!\p"
	.string "Mira el ajuste en el VISOR de\n"
	.string "DESAFÍOS en cualquier PC.$"

GoldenrodCity_NameRatersHouse_EventScript_RenameRival::
	msgbox GoldenrodCity_NameRatersHouse_Text_RenameRival, MSGBOX_DEFAULT
	closemessage
	special NameRival
	waitstate
	end

GoldenrodCity_NameRatersHouse_Text_RenameRival:
	.string "Son las noticias...\p"
	.string "¡La POLICÍA busca a este\n"
	.string "CHICO PELIRROJO!\p"
	.string "¿SABES tú cómo se llama?$"

GoldenrodCity_NameRatersHouse_EventScript_NameRater::
	lock
	faceplayer
	msgbox GoldenrodCity_NameRatersHouse_Text_PleasedToRateMonNickname, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, GoldenrodCity_NameRatersHouse_EventScript_ChooseMonToRate
	goto_if_eq VAR_RESULT, NO, GoldenrodCity_NameRatersHouse_EventScript_DeclineNameRate
	end

GoldenrodCity_NameRatersHouse_EventScript_ChooseMonToRate::
	msgbox GoldenrodCity_NameRatersHouse_Text_CritiqueWhichMonNickname, MSGBOX_DEFAULT
	special ChoosePartyMon
	waitstate
	lock
	goto_if_ne VAR_0x8004, PARTY_NOTHING_CHOSEN, GoldenrodCity_NameRatersHouse_EventScript_RateMonNickname
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, GoldenrodCity_NameRatersHouse_EventScript_DeclineNameRate
	end

GoldenrodCity_NameRatersHouse_EventScript_DeclineNameRate::
	msgbox GoldenrodCity_NameRatersHouse_Text_DoVisitAgain, MSGBOX_DEFAULT
	release
	end

GoldenrodCity_NameRatersHouse_EventScript_RateMonNickname::
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
	goto_if_eq VAR_RESULT, SPECIES_EGG, GoldenrodCity_NameRatersHouse_EventScript_CantRateEgg
	special BufferMonNickname
	@special IsMonOTIDNotPlayers
	@goto_if_eq VAR_RESULT, TRUE, GoldenrodCity_NameRatersHouse_EventScript_PlayerNotMonsOT
	@specialvar VAR_RESULT, MonOTNameNotPlayer
	special BufferMonNickname
	@goto_if_eq VAR_RESULT, TRUE, GoldenrodCity_NameRatersHouse_EventScript_PlayerNotMonsOT
	msgbox GoldenrodCity_NameRatersHouse_Text_FineNameSuggestBetterOne, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, GoldenrodCity_NameRatersHouse_EventScript_ChangeNickname
	goto_if_eq VAR_RESULT, NO, GoldenrodCity_NameRatersHouse_EventScript_DeclineNameRate
	end

GoldenrodCity_NameRatersHouse_EventScript_CantRateEgg::
	msgbox GoldenrodCity_NameRatersHouse_Text_ThatIsMerelyAnEgg, MSGBOX_DEFAULT
	release
	end

GoldenrodCity_NameRatersHouse_EventScript_PlayerNotMonsOT::
	msgbox GoldenrodCity_NameRatersHouse_Text_MagnificentName, MSGBOX_DEFAULT
	release
	end

GoldenrodCity_NameRatersHouse_EventScript_ChangeNickname::
	msgbox GoldenrodCity_NameRatersHouse_Text_WhatShallNewNameBe, MSGBOX_DEFAULT
	call Common_EventScript_NameReceivedPartyMon
	specialvar VAR_RESULT, TryPutNameRaterShowOnTheAir
	special BufferMonNickname
	goto_if_eq VAR_RESULT, TRUE, GoldenrodCity_NameRatersHouse_EventScript_NewNameDifferent
	msgbox GoldenrodCity_NameRatersHouse_Text_NameNoDifferentYetSuperior, MSGBOX_DEFAULT
	release
	end

GoldenrodCity_NameRatersHouse_EventScript_NewNameDifferent::
	msgbox GoldenrodCity_NameRatersHouse_Text_MonShallBeKnownAsName, MSGBOX_DEFAULT
	release
	end

GoldenrodCity_NameRatersHouse_Text_PleasedToRateMonNickname:
	.string "¡Hola, hola! ¡Soy el NOMBRADOR!\n"
	.string "¡Soy el adivino de los nombres!\p"
	.string "Será un placer ponerle nombre a\n"
	.string "Apodo del POKéMON.$"

GoldenrodCity_NameRatersHouse_Text_CritiqueWhichMonNickname:
	.string "¿El apodo de qué POKéMON\n"
	.string "debo criticar?$"

GoldenrodCity_NameRatersHouse_Text_FineNameSuggestBetterOne:
	.string "Hmmm... {STR_VAR_1}, ¿eh? Es un\n"
	.string "nombre muy bueno el que le diste.\p"
	.string "¡Pero! ¿Qué dices si te\n"
	.string "sugiero un nombre un poco mejor?$"

GoldenrodCity_NameRatersHouse_Text_WhatShallNewNameBe:
	.string "Ah, bien. Entonces, ¿cuál será el\n"
	.string "nuevo apodo?$"

GoldenrodCity_NameRatersHouse_Text_MonShallBeKnownAsName:
	.string "¡Listo! De ahora en adelante,\n"
	.string "¡este POKéMON se llamará {STR_VAR_1}!\p"
	.string "¡Es un nombre mejor que el anterior!\n"
	.string "¡Qué suerte tienes!$"

GoldenrodCity_NameRatersHouse_Text_DoVisitAgain:
	.string "Ya veo.\n"
	.string "Vuelve a visitarnos.$"

GoldenrodCity_NameRatersHouse_Text_NameNoDifferentYetSuperior:
	.string "¡Listo! De ahora en adelante,\n"
	.string "¡este POKéMON se llamará {STR_VAR_1}!\p"
	.string "No se ve distinto a antes,\n"
	.string "¡y aun así, es muy superior!\p"
	.string "¡Qué suerte tienes!$"

GoldenrodCity_NameRatersHouse_Text_MagnificentName:
	.string "Hmmm... ¡{STR_VAR_1} es!\p"
	.string "¡Es un apodo magnífico!\n"
	.string "¡Es impecable y perfecto!\p"
	.string "Haz bien en querer mucho a tu\n"
	.string "{STR_VAR_1} ahora y siempre.$"

GoldenrodCity_NameRatersHouse_Text_ThatIsMerelyAnEgg:
	.string "Ya, ya.\n"
	.string "¡Eso es solo un HUEVO!$"


