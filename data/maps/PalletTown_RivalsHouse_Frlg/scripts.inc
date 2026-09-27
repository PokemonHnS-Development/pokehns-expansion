.equ RECEIVED_TOWN_MAP, VAR_TEMP_1

PalletTown_RivalsHouse_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, PalletTown_RivalsHouse_OnTransition
	.byte 0

PalletTown_RivalsHouse_OnTransition::
	call_if_lt VAR_MAP_SCENE_PALLET_TOWN_RIVALS_HOUSE, 2, PalletTown_RivalsHouse_EventScript_MoveDaisyToTable
	call_if_ge VAR_MAP_SCENE_PALLET_TOWN_RIVALS_HOUSE, 2, PalletTown_RivalsHouse_EventScript_AlreadyReceivedTownMap
	end

PalletTown_RivalsHouse_EventScript_MoveDaisyToTable::
	setobjectmovementtype LOCALID_DAISY, MOVEMENT_TYPE_FACE_RIGHT
	setobjectxyperm LOCALID_DAISY, 5, 4
	return

PalletTown_RivalsHouse_EventScript_AlreadyReceivedTownMap::
	setvar RECEIVED_TOWN_MAP, TRUE
	return

PalletTown_RivalsHouse_EventScript_Daisy::
	lock
	faceplayer
	famechecker FAMECHECKER_DAISY, FCPICKSTATE_COLORED, UpdatePickStateFromSpecialVar8005
	goto_if_set FLAG_SYS_GAME_CLEAR, PalletTown_RivalsHouse_EventScript_GroomMon
	goto_if_eq RECEIVED_TOWN_MAP, TRUE, PalletTown_RivalsHouse_EventScript_PleaseGiveMonsRest
	goto_if_eq VAR_MAP_SCENE_PALLET_TOWN_RIVALS_HOUSE, 2, PalletTown_RivalsHouse_EventScript_ExplainTownMap
	goto_if_eq VAR_MAP_SCENE_PALLET_TOWN_RIVALS_HOUSE, 1, PalletTown_RivalsHouse_EventScript_GiveTownMap
	goto_if_ge VAR_MAP_SCENE_PALLET_TOWN_PROFESSOR_OAKS_LAB, 1, PalletTown_RivalsHouse_EventScript_HeardBattledRival
	msgbox PalletTown_RivalsHouse_Text_HiBrothersAtLab
	closemessage
	applymovement LOCALID_DAISY, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

PalletTown_RivalsHouse_EventScript_HeardBattledRival::
	msgbox PalletTown_RivalsHouse_Text_HeardYouBattledRival
	release
	end

PalletTown_RivalsHouse_EventScript_GroomMon::
	goto_if_lt VAR_MASSAGE_COOLDOWN_STEP_COUNTER, 500, PalletTown_RivalsHouse_EventScript_RateMonFriendship
	msgbox PalletTown_RivalsHouse_Text_LikeMeToGroomMon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, PalletTown_RivalsHouse_EventScript_DeclineGrooming
	msgbox PalletTown_RivalsHouse_Text_GroomWhichOne
	special ChoosePartyMon
	waitstate
	lock
	faceplayer
	goto_if_ge VAR_0x8004, PARTY_SIZE, PalletTown_RivalsHouse_EventScript_DeclineGrooming
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
	goto_if_eq VAR_RESULT, SPECIES_EGG, PalletTown_RivalsHouse_EventScript_CantGroomEgg
	msgbox PalletTown_RivalsHouse_Text_LookingNiceInNoTime
	closemessage
	fadescreen FADE_TO_BLACK
	playfanfare MUS_HEAL
	waitfanfare
	special DaisyMassageServices
	fadescreen FADE_FROM_BLACK
	special BufferMonNickname
	msgbox PalletTown_RivalsHouse_Text_ThereYouGoAllDone
	release
	end

PalletTown_RivalsHouse_EventScript_CantGroomEgg::
	msgbox PalletTown_RivalsHouse_Text_CantGroomAnEgg
	release
	end

PalletTown_RivalsHouse_EventScript_DeclineGrooming::
	msgbox PalletTown_RivalsHouse_Text_DontNeedAnyGrooming
	release
	end

PalletTown_RivalsHouse_EventScript_RateMonFriendship::
	msgbox PalletTown_RivalsHouse_Text_MayISeeFirstMon
	specialvar VAR_RESULT, GetLeadMonFriendship
	switch VAR_RESULT
	case 0, PalletTown_RivalsHouse_EventScript_MonFriendshipLowest
	case 1, PalletTown_RivalsHouse_EventScript_MonFriendshipLower
	case 2, PalletTown_RivalsHouse_EventScript_MonFriendshipLow
	case 3, PalletTown_RivalsHouse_EventScript_MonFriendshipMid
	case 4, PalletTown_RivalsHouse_EventScript_MonFriendshipHigh
	case 5, PalletTown_RivalsHouse_EventScript_MonFriendshipHigher
	case 6, PalletTown_RivalsHouse_EventScript_MonFriendshipHighest
	end

PalletTown_RivalsHouse_EventScript_MonFriendshipLowest::
	msgbox PalletTown_RivalsHouse_Text_WhyWouldMonHateYouSoMuch
	release
	end

PalletTown_RivalsHouse_EventScript_MonFriendshipLower::
	msgbox PalletTown_RivalsHouse_Text_DontLikeWayItGlaresAtYou
	release
	end

PalletTown_RivalsHouse_EventScript_MonFriendshipLow::
	msgbox PalletTown_RivalsHouse_Text_NotFamiliarWithYouYet
	release
	end

PalletTown_RivalsHouse_EventScript_MonFriendshipMid::
	msgbox PalletTown_RivalsHouse_Text_ItsWarmingUpToYou
	release
	end

PalletTown_RivalsHouse_EventScript_MonFriendshipHigh::
	msgbox PalletTown_RivalsHouse_Text_ItsQuiteFriendly
	release
	end

PalletTown_RivalsHouse_EventScript_MonFriendshipHigher::
	msgbox PalletTown_RivalsHouse_Text_ItLooksVeryHappy
	release
	end

PalletTown_RivalsHouse_EventScript_MonFriendshipHighest::
	msgbox PalletTown_RivalsHouse_Text_CouldntLoveYouMore
	release
	end

PalletTown_RivalsHouse_EventScript_PleaseGiveMonsRest::
	msgbox PalletTown_RivalsHouse_Text_PleaseGiveMonsRest
	release
	end

PalletTown_RivalsHouse_EventScript_GiveTownMap::
	msgbox PalletTown_RivalsHouse_Text_ErrandForGrandpaThisWillHelp
	closemessage
	checkitemspace ITEM_TOWN_MAP
	goto_if_eq VAR_RESULT, FALSE, PalletTown_RivalsHouse_EventScript_NoRoomForTownMap
	applymovement LOCALID_DAISY, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	removeobject LOCALID_TOWN_MAP
	setvar VAR_MAP_SCENE_PALLET_TOWN_RIVALS_HOUSE, 2
	delay 15
	applymovement LOCALID_DAISY, Common_Movement_FacePlayer
	waitmovement 0
	delay 12
	giveitem_msg PalletTown_RivalsHouse_Text_ReceivedTownMapFromDaisy, ITEM_TOWN_MAP, 1, MUS_RG_OBTAIN_KEY_ITEM
	release
	end

PalletTown_RivalsHouse_EventScript_NoRoomForTownMap::
	msgbox PalletTown_RivalsHouse_Text_DontHaveSpaceForThis
	release
	end

PalletTown_RivalsHouse_EventScript_ExplainTownMap::
	msgbox PalletTown_RivalsHouse_Text_ExplainTownMap
	release
	end

PalletTown_RivalsHouse_EventScript_TownMap::
	msgbox PalletTown_RivalsHouse_Text_ItsBigMapOfKanto, MSGBOX_NPC
	end

PalletTown_RivalsHouse_EventScript_Bookshelf::
	msgbox PalletTown_RivalsHouse_Text_ShelvesCrammedFullOfBooks, MSGBOX_SIGN
	end

PalletTown_RivalsHouse_EventScript_Picture::
	msgbox PalletTown_RivalsHouse_Text_LovelyAndSweetClefairy, MSGBOX_SIGN
	end

PalletTown_RivalsHouse_Text_HiBrothersAtLab::
	.string "DAISY: ¡Hola, {PLAYER}!\p"
	.string "Mi hermano, {RIVAL}, está en el\n"
	.string "LAB. del abuelo.$"

PalletTown_RivalsHouse_Text_HeardYouBattledRival::
	.string "DAISY: {PLAYER}, supe que tuviste\n"
	.string "una batalla contra {RIVAL}.\p"
	.string "¡Me habría gustado verla!$"

PalletTown_RivalsHouse_Text_ErrandForGrandpaThisWillHelp::
	.string "¿El abuelo te pidió hacerle\n"
	.string "un recado?\p"
	.string "Vaya, qué perezoso es.\n"
	.string "Toma, esto te ayudará.$"

PalletTown_RivalsHouse_Text_ReceivedTownMapFromDaisy::
	.string "{PLAYER} recibió un MAPA\n"
	.string "de DAISY.$"

PalletTown_RivalsHouse_Text_DontHaveSpaceForThis::
	.string "No tienes espacio para esto en\n"
	.string "tu BOLSA.$"

PalletTown_RivalsHouse_Text_ExplainTownMap::
	.string "Con el MAPA puedes ver dónde\n"
	.string "estás o consultar aquí\l"
	.string "los nombres de lugares.$"

PalletTown_RivalsHouse_Text_PleaseGiveMonsRest::
	.string "DAISY: Como las personas, los POKéMON\n"
	.string "son seres vivos.\p"
	.string "Cuando se cansen, dales\n"
	.string "un descanso.$"

PalletTown_RivalsHouse_Text_ItsBigMapOfKanto::
	.string "Es un gran mapa de la región KANTO.\n"
	.string "¡Esto sí que será útil!$"

PalletTown_RivalsHouse_Text_ShelvesCrammedFullOfBooks::
	.string "Los estantes están repletos de\n"
	.string "libros sobre POKéMON.$"

PalletTown_RivalsHouse_Text_LikeMeToGroomMon::
	.string "DAISY: ¡Hola, {PLAYER}!\n"
	.string "Qué buen momento.\p"
	.string "Estoy por tomar un té.\n"
	.string "¿Te gustaría acompañarme?\p"
	.string "Oh, pero mira.\n"
	.string "Tus POKéMON están algo sucios.\p"
	.string "¿Quieres que limpie a alguno?$"

PalletTown_RivalsHouse_Text_DontNeedAnyGrooming::
	.string "¿No quieres que les haga el arreglo?\n"
	.string "Bueno, tomaremos solo el té.$"

PalletTown_RivalsHouse_Text_GroomWhichOne::
	.string "¿A cuál le hago el arreglo?$"

PalletTown_RivalsHouse_Text_LookingNiceInNoTime::
	.string "DAISY: Bien, lo dejaré\n"
	.string "bien en un abrir y cerrar de ojos.$"

PalletTown_RivalsHouse_Text_ThereYouGoAllDone::
#ifdef BUGFIX @ The localizers missed what should be a textcolor change in the localizations.
	.string "{COLOR DARK_GRAY}{STR_VAR_1} parece soñar feliz...\p"
	.string "{COLOR RED}DAISY: ¡Listo, ya está!\n"
#else @ In the JP games, gender-based text used a different font instead of different colors.
	.string "{FONT_NORMAL}{STR_VAR_1} parece soñar feliz...\p"
	.string "{FONT_FEMALE}DAISY: ¡Listo, ya está!\n"
#endif
	.string "¿Ves? ¿No se ve lindo?\p"
	.string "Jejeje...\n"
	.string "Es un POKéMON muy lindo.$"

PalletTown_RivalsHouse_Text_CantGroomAnEgg::
	.string "Oh, lo siento. Sinceramente no puedo\n"
	.string "arreglar un HUEVO.$"

PalletTown_RivalsHouse_Text_MayISeeFirstMon::
	.string "DAISY: Tus POKéMON aprenden a quererte\n"
	.string "si los crías con cariño.\p"
	.string "Por ejemplo, {PLAYER}, ¿puedo ver\n"
	.string "a tu primer POKéMON?$"

PalletTown_RivalsHouse_Text_CouldntLoveYouMore::
	.string "No podría quererte\n"
	.string "más de lo que ya lo hace.\p"
	.string "Tu POKéMON es feliz más allá\n"
	.string "de las palabras.$"

PalletTown_RivalsHouse_Text_ItLooksVeryHappy::
	.string "Se le ve muy feliz.\p"
	.string "Ojalá {RIVAL} pudiera ver esto y\n"
	.string "aprender algo de ti.$"

PalletTown_RivalsHouse_Text_ItsQuiteFriendly::
	.string "Es bastante amistoso contigo.\n"
	.string "¡Sigue tratándolo bien!$"

PalletTown_RivalsHouse_Text_ItsWarmingUpToYou::
	.string "Está empezando a encariñarse.\n"
	.string "La confianza debe estar creciendo.$"

PalletTown_RivalsHouse_Text_NotFamiliarWithYouYet::
	.string "Su familiaridad contigo aún no\n"
	.string "está completa.\p"
	.string "Los POKéMON son desconfiados cuando\n"
	.string "los consigues por primera vez.$"

PalletTown_RivalsHouse_Text_DontLikeWayItGlaresAtYou::
	.string "{PLAYER}, no me gusta cómo te\n"
	.string "mira con recelo.\p"
	.string "¿Podrías intentar ser más amable\n"
	.string "con él?$"

PalletTown_RivalsHouse_Text_WhyWouldMonHateYouSoMuch::
	.string "...Esto no me resulta fácil\n"
	.string "decirlo, pero...\p"
	.string "¿Hay alguna razón por la que tu\n"
	.string "POKéMON te odiaría tanto?$"

PalletTown_RivalsHouse_Text_LovelyAndSweetClefairy::
	.string "“La dulce y bella\n"
	.string "CLEFAIRY”$"

