PetalburgCity_WallysHouse_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, PetalburgCity_WallysHouse_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, PetalburgCity_WallysHouse_OnWarp
	.byte 0

PetalburgCity_WallysHouse_OnWarp:
	map_script_2 VAR_PETALBURG_CITY_STATE, 4, PetalburgCity_WallysHouse_EventScript_PlayerWallysDadFaceEachOther
	.2byte 0

PetalburgCity_WallysHouse_EventScript_PlayerWallysDadFaceEachOther::
	turnobject LOCALID_PLAYER, DIR_EAST
	turnobject LOCALID_WALLYS_HOUSE_WALLYS_DAD, DIR_WEST
	end

PetalburgCity_WallysHouse_OnFrame:
	map_script_2 VAR_PETALBURG_CITY_STATE, 4, PetalburgCity_WallysHouse_EventScript_GiveHMSurf
	.2byte 0

PetalburgCity_WallysHouse_EventScript_GiveHMSurf::
	lockall
	msgbox PetalburgCity_WallysHouse_Text_PleaseExcuseUs, MSGBOX_DEFAULT
	giveitem ITEM_HM_SURF
	setflag FLAG_RECEIVED_HM_SURF
	msgbox PetalburgCity_WallysHouse_Text_SurfGoAllSortsOfPlaces, MSGBOX_DEFAULT
	setvar VAR_PETALBURG_CITY_STATE, 5
	releaseall
	end

PetalburgCity_WallysHouse_EventScript_WallysDad::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_WALLY_VICTORY_ROAD, PetalburgCity_WallysHouse_EventScript_DefeatedWallyInVictoryRoad
	goto_if_set FLAG_RECEIVED_HM_SURF, PetalburgCity_WallysHouse_EventScript_ReceievedHMSurf
	goto_if_set FLAG_THANKED_FOR_PLAYING_WITH_WALLY, PetalburgCity_WallysHouse_EventScript_PlayedWithWally
	msgbox PetalburgCity_WallysHouse_Text_ThanksForPlayingWithWally, MSGBOX_DEFAULT
	setflag FLAG_THANKED_FOR_PLAYING_WITH_WALLY
	release
	end

PetalburgCity_WallysHouse_EventScript_ReceievedHMSurf::
	msgbox PetalburgCity_WallysHouse_Text_WallyIsComingHomeSoon, MSGBOX_DEFAULT
	release
	end

PetalburgCity_WallysHouse_EventScript_DefeatedWallyInVictoryRoad::
	msgbox PetalburgCity_WallysHouse_Text_YouMetWallyInEverGrandeCity, MSGBOX_DEFAULT
	release
	end

PetalburgCity_WallysHouse_EventScript_PlayedWithWally::
	msgbox PetalburgCity_WallysHouse_Text_WonderHowWallyIsDoing, MSGBOX_DEFAULT
	release
	end

PetalburgCity_WallysHouse_EventScript_WallysMom::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_HM_SURF, PetalburgCity_WallysHouse_EventScript_ReceivedHMSurf
	msgbox PetalburgCity_WallysHouse_Text_WallyWasReallyHappy, MSGBOX_DEFAULT
	release
	end

PetalburgCity_WallysHouse_EventScript_ReceivedHMSurf::
	msgbox PetalburgCity_WallysHouse_Text_WallyLeftWithoutTelling, MSGBOX_DEFAULT
	release
	end

PetalburgCity_WallysHouse_Text_ThanksForPlayingWithWally:
	.string "Tú eres...\n"
	.string "Ah, debes ser {PLAYER}{KUN}, ¿no?\p"
	.string "Gracias por jugar con WALLY hace\n"
	.string "un momento.\p"
	.string "Ha sido débil y enfermizo desde\n"
	.string "que era un bebé.\p"
	.string "Lo enviamos con mis parientes a\n"
	.string "PUEBLO VERDANTE por un tiempo.\p"
	.string "El aire es mucho más limpio allá\n"
	.string "que aquí.\p"
	.string "¿Qué dices? ¿Dónde está WALLY?\n"
	.string "Nuestro WALLY ya se ha ido.\p"
	.string "Me pregunto dónde estará\n"
	.string "en este momento?$"

PetalburgCity_WallysHouse_Text_WonderHowWallyIsDoing:
	.string "¿Cómo estará nuestro WALLY?$"

PetalburgCity_WallysHouse_Text_PleaseExcuseUs:
	.string "{PLAYER}{KUN}! Perdónanos por\n"
	.string "traerte así hasta aquí.\p"
	.string "Pero WALLY ha mejorado mucho\n"
	.string "desde que fue a PUEBLO VERDANTE.\p"
	.string "¡Te lo debemos todo a ti!\p"
	.string "Cuando WALLY salió del pueblo,\n"
	.string "que atrape un POKéMON, ¿verdad?\p"
	.string "Creo que eso animó mucho a WALLY.\n"
	.string "estén felices.\p"
	.string "De hecho, no solo a WALLY.\n"
	.string "A mí, su padre, también me hizo feliz.\p"
	.string "Feliz de que haya ganado a un gran\n"
	.string "amigo como tú.\p"
	.string "Esto no es un soborno ni nada, pero\n"
	.string "realmente quiero que tengas esto.$"

PetalburgCity_WallysHouse_Text_SurfGoAllSortsOfPlaces:
	.string "Si tu POKéMON sabe SURF, podrás\n"
	.string "ir a todo tipo de lugares.$"

PetalburgCity_WallysHouse_Text_WallyIsComingHomeSoon:
	.string "WALLY volverá pronto a casa.\n"
	.string "Tengo muchas ganas de que pase.$"

PetalburgCity_WallysHouse_Text_YouMetWallyInEverGrandeCity:
	.string "¿Ah? ¿Te encontraste a WALLY en\n"
	.string "CIUDAD VERIDIANO?\p"
	.string "Oh, {PLAYER}{KUN}, no seas tonto.\p"
	.string "Puede que esté sano, pero él\n"
	.string "no puede ir a un lugar tan lejano\l"
	.string "como ese él solo.$"

PetalburgCity_WallysHouse_Text_WallyWasReallyHappy:
	.string "WALLY estaba muy feliz al decirnos\n"
	.string "que atrapó un POKéMON.\p"
	.string "Hacía siglos que no lo veía\n"
	.string "sonreír así.$"

PetalburgCity_WallysHouse_Text_WallyLeftWithoutTelling:
	.string "Quiero que guardes este secreto\n"
	.string "ante mi esposo...\p"
	.string "Pero nuestro WALLY dejó PUEBLO VERDE\n"
	.string "sin decirle nada a nadie.\p"
	.string "Ya sabes, WALLY es débil, pero\n"
	.string "Tiene una voluntad sorprendente.\p"
	.string "Estoy segura de que volverá a\n"
	.string "estar a salvo algún día!$"

