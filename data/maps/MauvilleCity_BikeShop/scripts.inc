MauvilleCity_BikeShop_MapScripts::
	.byte 0

MauvilleCity_BikeShop_EventScript_Rydel::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_BIKE, MauvilleCity_BikeShop_EventScript_AskSwitchBikes
	goto_if_set FLAG_DECLINED_BIKE, MauvilleCity_BikeShop_EventScript_SkipGreeting
	msgbox MauvilleCity_BikeShop_Text_RydelGreeting, MSGBOX_DEFAULT
	msgbox MauvilleCity_BikeShop_Text_DidYouComeFromFarAway, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, MauvilleCity_BikeShop_EventScript_YesFar
	goto_if_eq VAR_RESULT, NO, MauvilleCity_BikeShop_EventScript_NotFar
	end

MauvilleCity_BikeShop_EventScript_SkipGreeting::
	msgbox MauvilleCity_BikeShop_Text_DidYouComeFromFarAway, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, MauvilleCity_BikeShop_EventScript_YesFar
	goto_if_eq VAR_RESULT, NO, MauvilleCity_BikeShop_EventScript_NotFar
	end

MauvilleCity_BikeShop_EventScript_ChooseBike::
	message MauvilleCity_BikeShop_Text_ExplainBikesChooseWhichOne
	waitmessage
	multichoice 21, 8, MULTI_BIKE, TRUE
	switch VAR_RESULT
	case 0, MauvilleCity_BikeShop_EventScript_GetMachBike
	case 1, MauvilleCity_BikeShop_EventScript_GetAcroBike
	end

MauvilleCity_BikeShop_EventScript_NotFar::
	setflag FLAG_DECLINED_BIKE
	msgbox MauvilleCity_BikeShop_Text_GuessYouDontNeedBike, MSGBOX_DEFAULT
	release
	end

MauvilleCity_BikeShop_EventScript_YesFar::
	setflag FLAG_RECEIVED_BIKE
	goto MauvilleCity_BikeShop_EventScript_ChooseBike
	end

MauvilleCity_BikeShop_EventScript_GetMachBike::
	msgbox MauvilleCity_BikeShop_Text_ChoseMachBike, MSGBOX_DEFAULT
	giveitem ITEM_MACH_BIKE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	goto MauvilleCity_BikeShop_EventScript_ComeBackToSwitchBikes
	end

MauvilleCity_BikeShop_EventScript_GetAcroBike::
	msgbox MauvilleCity_BikeShop_Text_ChoseAcroBike, MSGBOX_DEFAULT
	giveitem ITEM_ACRO_BIKE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	goto MauvilleCity_BikeShop_EventScript_ComeBackToSwitchBikes
	end

MauvilleCity_BikeShop_EventScript_ComeBackToSwitchBikes::
	msgbox MauvilleCity_BikeShop_Text_ComeBackToSwitchBikes, MSGBOX_DEFAULT
	special SwapRegisteredBike
	release
	end

MauvilleCity_BikeShop_EventScript_AskSwitchBikes::
	msgbox MauvilleCity_BikeShop_Text_WantToSwitchBikes, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, MauvilleCity_BikeShop_EventScript_SwitchBikes
	goto_if_eq VAR_RESULT, NO, MauvilleCity_BikeShop_EventScript_KeepBike
	end

@ If the player does not have a bike on them Rydel assumes its stored in the PC
MauvilleCity_BikeShop_EventScript_SwitchBikes::
	msgbox MauvilleCity_BikeShop_Text_IllSwitchBikes, MSGBOX_DEFAULT
	checkitem ITEM_ACRO_BIKE
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_BikeShop_EventScript_SwitchAcroForMach
	checkitem ITEM_MACH_BIKE
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_BikeShop_EventScript_SwitchMachForAcro
	msgbox MauvilleCity_BikeShop_Text_OhYourBikeIsInPC, MSGBOX_DEFAULT
	release
	end

MauvilleCity_BikeShop_EventScript_KeepBike::
	msgbox MauvilleCity_BikeShop_Text_HappyYouLikeIt, MSGBOX_DEFAULT
	release
	end

MauvilleCity_BikeShop_EventScript_SwitchAcroForMach::
	incrementgamestat GAME_STAT_TRADED_BIKES
	msgbox MauvilleCity_BikeShop_Text_ExchangedAcroForMach, MSGBOX_DEFAULT
	removeitem ITEM_ACRO_BIKE
	giveitem ITEM_MACH_BIKE
	goto MauvilleCity_BikeShop_EventScript_ComeBackToSwitchBikes
	end

MauvilleCity_BikeShop_EventScript_SwitchMachForAcro::
	incrementgamestat GAME_STAT_TRADED_BIKES
	msgbox MauvilleCity_BikeShop_Text_ExchangedMachForAcro, MSGBOX_DEFAULT
	removeitem ITEM_MACH_BIKE
	giveitem ITEM_ACRO_BIKE
	goto MauvilleCity_BikeShop_EventScript_ComeBackToSwitchBikes
	end

MauvilleCity_BikeShop_EventScript_Assistant::
	msgbox MauvilleCity_BikeShop_Text_HandbooksAreInBack, MSGBOX_NPC
	end

MauvilleCity_BikeShop_EventScript_MachBikeHandbook::
	message MauvilleCity_BikeShop_Text_MachHandbookWhichPage
	waitmessage
	goto MauvilleCity_BikeShop_EventScript_ChooseMachHandbookPage
	end

MauvilleCity_BikeShop_EventScript_ChooseMachHandbookPage::
	multichoice 0, 0, MULTI_MACH_BIKE_INFO, FALSE
	switch VAR_RESULT
	case 0, MauvilleCity_BikeShop_EventScript_HowToRide
	case 1, MauvilleCity_BikeShop_EventScript_HowToTurn
	case 2, MauvilleCity_BikeShop_EventScript_SandySlopes
	case 3, MauvilleCity_BikeShop_EventScript_ExitMachHandbook
	case MULTI_B_PRESSED, MauvilleCity_BikeShop_EventScript_ExitMachHandbook
	end

MauvilleCity_BikeShop_EventScript_HowToRide::
	message MauvilleCity_BikeShop_Text_HowToRideMachBike
	waitmessage
	goto MauvilleCity_BikeShop_EventScript_ChooseMachHandbookPage
	end

MauvilleCity_BikeShop_EventScript_HowToTurn::
	message MauvilleCity_BikeShop_Text_HowToTurnMachBike
	waitmessage
	goto MauvilleCity_BikeShop_EventScript_ChooseMachHandbookPage
	end

MauvilleCity_BikeShop_EventScript_SandySlopes::
	message MauvilleCity_BikeShop_Text_SandySlopes
	waitmessage
	goto MauvilleCity_BikeShop_EventScript_ChooseMachHandbookPage
	end

MauvilleCity_BikeShop_EventScript_ExitMachHandbook::
	release
	end

MauvilleCity_BikeShop_EventScript_AcroBikeHandbook::
	message MauvilleCity_BikeShop_Text_AcroHandbookWhichPage
	waitmessage
	goto MauvilleCity_BikeShop_EventScript_ChooseAcroHandbookPage
	end

MauvilleCity_BikeShop_EventScript_ChooseAcroHandbookPage::
	multichoice 0, 0, MULTI_ACRO_BIKE_INFO, FALSE
	switch VAR_RESULT
	case 0, MauvilleCity_BikeShop_EventScript_Wheelies
	case 1, MauvilleCity_BikeShop_EventScript_BunnyHops
	case 2, MauvilleCity_BikeShop_EventScript_Jumps
	case 3, MauvilleCity_BikeShop_EventScript_ExitAcroHandbook
	case MULTI_B_PRESSED, MauvilleCity_BikeShop_EventScript_ExitAcroHandbook
	end

MauvilleCity_BikeShop_EventScript_Wheelies::
	message MauvilleCity_BikeShop_Text_Wheelies
	waitmessage
	goto MauvilleCity_BikeShop_EventScript_ChooseAcroHandbookPage
	end

MauvilleCity_BikeShop_EventScript_BunnyHops::
	message MauvilleCity_BikeShop_Text_BunnyHops
	waitmessage
	goto MauvilleCity_BikeShop_EventScript_ChooseAcroHandbookPage
	end

MauvilleCity_BikeShop_EventScript_Jumps::
	message MauvilleCity_BikeShop_Text_Jumps
	waitmessage
	goto MauvilleCity_BikeShop_EventScript_ChooseAcroHandbookPage
	end

MauvilleCity_BikeShop_EventScript_ExitAcroHandbook::
	release
	end

MauvilleCity_BikeShop_Text_RydelGreeting:
	.string "Vaya, vaya, ¿qué tenemos aquí?\n"
	.string "¡Un cliente muy energético!\p"
	.string "¿Yo? Puedes llamarme RYDEL.\n"
	.string "Soy el dueño de esta tienda.$"

MauvilleCity_BikeShop_Text_DidYouComeFromFarAway:
	.string "RYDEL: Tus ZAPATOS DE CORRER…\n"
	.string "Están terriblemente sucios.\p"
	.string "¿Vienes de muy lejos?$"

MauvilleCity_BikeShop_Text_GuessYouDontNeedBike:
	.string "RYDEL: ¿Ah, sí?\p"
	.string "Entonces, supongo que no necesitas\n"
	.string "ninguna de mis BICICLETAS.$"

MauvilleCity_BikeShop_Text_ExplainBikesChooseWhichOne:
	.string "RYDEL: Hm, hm… … … … …\p"
	.string "Dices que viniste hasta aquí\n"
	.string "desde PUEBLO RAÍZ?\p"
	.string "¡Cielos!\n"
	.string "¡Eso está ridículamente lejos!\p"
	.string "Si tuvieras una de mis BICICLETAS,\n"
	.string "podrías ir a cualquier lugar y\l"
	.string "sentir la brisa del viento!\p"
	.string "¡Se me ocurre algo!\n"
	.string "¡Te daré una BICICLETA!\p"
	.string "¡Ah, espera un segundo!\p"
	.string "Olvidé decirte que existen\n"
	.string "dos tipos de BICICLETAS!\p"
	.string "Están la MACH BIKE y\n"
	.string "¡la ACRO BIKE!\p"
	.string "La MACH BIKE es para ciclistas que\n"
	.string "¡quieren sentir el viento!\p"
	.string "¡Y la ACRO BIKE es para quienes\n"
	.string "prefieren paseos técnicos!\p"
	.string "Soy un encanto, así que puedes\n"
	.string "¡llevarte la que más te guste!\p"
	.string "¿Cuál vas a elegir?$"

MauvilleCity_BikeShop_Text_ChoseMachBike:
	.string "{PLAYER} chose the MACH BIKE.$"

MauvilleCity_BikeShop_Text_ChoseAcroBike:
	.string "{PLAYER} eligió la ACRO BIKE.$"

MauvilleCity_BikeShop_Text_ComeBackToSwitchBikes:
	.string "RYDEL: ¡Si quieres cambiar de\n"
	.string "BIKE, solo ven a verme!$"

MauvilleCity_BikeShop_Text_WantToSwitchBikes:
	.string "RYDEL: ¿Oh? ¿Estás pensando en\n"
	.string "cambiar de BICICLETA?$"

MauvilleCity_BikeShop_Text_IllSwitchBikes:
	.string "RYDEL: ¡Está bien, no hay problema!\n"
	.string "¡Cambiaré la BICICLETA por ti!$"

MauvilleCity_BikeShop_Text_ExchangedMachForAcro:
	.string "{PLAYER} cambió la MACH BIKE\n"
	.string "por una ACRO BIKE.$"

MauvilleCity_BikeShop_Text_ExchangedAcroForMach:
	.string "{PLAYER} cambió la ACRO BIKE\n"
	.string "por una MACH BIKE.$"

MauvilleCity_BikeShop_Text_HappyYouLikeIt:
	.string "RYDEL: ¡Bien, bien!\n"
	.string "¡Me alegra que te guste!$"

MauvilleCity_BikeShop_Text_OhYourBikeIsInPC:
	.string "¿Oh? ¿Qué pasó con esa BICICLETA?\n"
	.string "que te di?\p"
	.string "Ah, ya veo, la guardaste en el PC.\p"
	.string "Bueno, sácalo del PC,\n"
	.string "¡y con gusto lo cambiaré!\p"
	.string "¡Que el viento siempre te acompañe\n"
	.string "en tu aventura!$"

MauvilleCity_BikeShop_Text_HandbooksAreInBack:
	.string "Aprendo sobre BICICLETAS mientras\n"
	.string "trabajo aquí.\p"
	.string "Si necesitas consejos para usar tu\n"
	.string "BICICLETA, hay manuales en\l"
	.string "la parte de atrás.$"

MauvilleCity_BikeShop_Text_MachHandbookWhichPage:
	.string "Es un manual de la MACH BIKE.\p"
	.string "¿Qué página quieres leer?$"

MauvilleCity_BikeShop_Text_HowToRideMachBike:
	.string "Una BICICLETA se mueve hacia donde\n"
	.string "se presiona el Control Pad +.\p"
	.string "Acelerará una vez que ruede.\p"
	.string "Para parar, suelta el Control Pad +.\n"
	.string "La BIKE frenará hasta detenerse.\p"
	.string "¿Quieres leer otra página?$"

MauvilleCity_BikeShop_Text_HowToTurnMachBike:
	.string "La MACH BIKE es veloz, pero no\n"
	.string "puede frenar muy rápido.\p"
	.string "Es algo difícil tomar\n"
	.string "una curva.\p"
	.string "Suelta el Control Pad + un poco\n"
	.string "antes de la curva para frenar.\p"
	.string "¿Quieres leer otra página?$"

MauvilleCity_BikeShop_Text_SandySlopes:
	.string "Hay pequeñas pendientes de arena\n"
	.string "por toda la región de HOENN.\p"
	.string "La arena suelta y quebradiza hace\n"
	.string "imposible subir normalmente.\p"
	.string "Pero con una MACH BIKE, puedes\n"
	.string "subir rápido una pendiente de arena.\p"
	.string "¿Quieres leer otra página?$"

MauvilleCity_BikeShop_Text_AcroHandbookWhichPage:
	.string "Es un manual sobre la ACRO BIKE.\p"
	.string "¿Qué página quieres leer?$"

MauvilleCity_BikeShop_Text_Wheelies:
	.string "Pulsa el Botón B al conducir,\n"
	.string "y la rueda delantera se elevará.\p"
	.string "Puedes moverte con la rueda\n"
	.string "arriba usando el Control Pad +.\p"
	.string "Esta técnica se llama wheelie.\p"
	.string "¿Quieres leer otra página?$"

MauvilleCity_BikeShop_Text_BunnyHops:
	.string "Manteniendo pulsado el Botón B,\n"
	.string "tu BICICLETA puede saltar en el sitio.\p"
	.string "Esta técnica se llama bunny hop.\p"
	.string "También puedes saltar mientras vas.\p"
	.string "¿Quieres leer otra página?$"

MauvilleCity_BikeShop_Text_Jumps:
	.string "Pulsa el Botón B y el Control +\n"
	.string "al mismo tiempo para saltar.\p"
	.string "Pulsa el Control + hacia un lado\n"
	.string "para saltar lateralmente.\p"
	.string "Pulsa hacia atrás para que la\n"
	.string "BICICLETA cambie de rumbo al saltar.\p"
	.string "¿Quieres leer otra página?$"

