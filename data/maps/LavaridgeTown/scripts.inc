LavaridgeTown_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, LavaridgeTown_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, LavaridgeTown_OnFrame
	.byte 0

LavaridgeTown_OnTransition:
	setflag FLAG_VISITED_LAVARIDGE_TOWN
	call_if_set FLAG_WHITEOUT_TO_LAVARIDGE, LavaridgeTown_EventScript_ClearLavaridgeWhiteOut
	call_if_set FLAG_DEFEATED_EVIL_TEAM_MT_CHIMNEY, LavaridgeTown_EventScript_ShowMtChimneyTrainers
	call Common_EventScript_SetupRivalGfxId
	call Common_EventScript_SetupRivalOnBikeGfxId
	call_if_eq VAR_LAVARIDGE_TOWN_STATE, 1, LavaridgeTown_EventScript_CheckSetRivalPos
	call_if_eq VAR_LAVARIDGE_TOWN_STATE, 1, LavaridgeTown_EventScript_HideMapNamePopup
	end

LavaridgeTown_EventScript_ClearLavaridgeWhiteOut::
	clearflag FLAG_WHITEOUT_TO_LAVARIDGE
	return

LavaridgeTown_EventScript_CheckSetRivalPos::
	getplayerxy VAR_0x8004, VAR_0x8005
	goto_if_eq VAR_0x8004, 9, LavaridgeTown_EventScript_SetRivalPos
	return

LavaridgeTown_EventScript_SetRivalPos::
	setobjectxyperm LOCALID_LAVARIDGE_RIVAL, 11, 9
	setobjectxyperm LOCALID_LAVARIDGE_RIVAL_ON_BIKE, 9, 8
	setobjectmovementtype LOCALID_LAVARIDGE_RIVAL_ON_BIKE, MOVEMENT_TYPE_FACE_UP
	clearflag FLAG_HIDE_LAVARIDGE_TOWN_RIVAL
	return

LavaridgeTown_EventScript_ShowMtChimneyTrainers::
	clearflag FLAG_HIDE_MT_CHIMNEY_TRAINERS
	return

LavaridgeTown_EventScript_HideMapNamePopup::
	setflag FLAG_HIDE_MAP_NAME_POPUP
	return

LavaridgeTown_OnFrame:
	map_script_2 VAR_LAVARIDGE_TOWN_STATE, 1, LavaridgeTown_EventScript_RivalGiveGoGoggles
	.2byte 0

LavaridgeTown_EventScript_RivalGiveGoGoggles::
	lockall
	getplayerxy VAR_0x8008, VAR_0x8009
	call_if_eq VAR_0x8008, 9, LavaridgeTown_EventScript_RivalNoticePlayer
	call_if_ne VAR_0x8008, 9, LavaridgeTown_EventScript_RivalExitHerbShop
	delay 20
	checkplayergender
	call_if_eq VAR_RESULT, MALE, LavaridgeTown_EventScript_PlayMayMusic
	call_if_eq VAR_RESULT, FEMALE, LavaridgeTown_EventScript_PlayBrendanMusic
	call_if_eq VAR_0x8008, 9, LavaridgeTown_EventScript_RivalApproachPlayer1
	call_if_ne VAR_0x8008, 9, LavaridgeTown_EventScript_RivalApproachPlayer2
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, LavaridgeTown_EventScript_MayGiveGoGoggles
	goto_if_eq VAR_RESULT, FEMALE, LavaridgeTown_EventScript_BrendanGiveGoGoggles
	end

LavaridgeTown_EventScript_MayGiveGoGoggles::
	msgbox LavaridgeTown_Text_MayNiceBadgesTakeThis, MSGBOX_DEFAULT
	giveitem ITEM_GO_GOGGLES
	setflag FLAG_RECEIVED_GO_GOGGLES
	msgbox LavaridgeTown_Text_MayExplainGoGogglesChallengeDad, MSGBOX_DEFAULT
	goto LavaridgeTown_EventScript_RivalExit
	end

LavaridgeTown_EventScript_BrendanGiveGoGoggles::
	msgbox LavaridgeTown_Text_BrendanNiceBadgesTakeThis, MSGBOX_DEFAULT
	giveitem ITEM_GO_GOGGLES
	setflag FLAG_RECEIVED_GO_GOGGLES
	msgbox LavaridgeTown_Text_BrendanExplainGoGogglesChallengeDad, MSGBOX_DEFAULT
	goto LavaridgeTown_EventScript_RivalExit
	end

LavaridgeTown_EventScript_RivalExit::
	closemessage
	removeobject LOCALID_LAVARIDGE_RIVAL
	addobject LOCALID_LAVARIDGE_RIVAL_ON_BIKE
	delay 30
	call_if_eq VAR_0x8008, 9, LavaridgeTown_EventScript_RivalExit1
	call_if_ne VAR_0x8008, 9, LavaridgeTown_EventScript_RivalExit2
	removeobject LOCALID_LAVARIDGE_RIVAL_ON_BIKE
	setvar VAR_LAVARIDGE_TOWN_STATE, 2
	clearflag FLAG_HIDE_MAP_NAME_POPUP
	savebgm MUS_DUMMY
	fadedefaultbgm
	releaseall
	end

LavaridgeTown_EventScript_PlayMayMusic::
	playbgm MUS_ENCOUNTER_MAY, TRUE
	return

LavaridgeTown_EventScript_PlayBrendanMusic::
	playbgm MUS_ENCOUNTER_BRENDAN, TRUE
	return

LavaridgeTown_EventScript_RivalNoticePlayer::
	applymovement LOCALID_LAVARIDGE_RIVAL, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_LAVARIDGE_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_LAVARIDGE_RIVAL, Common_Movement_Delay48
	waitmovement 0
	return

LavaridgeTown_EventScript_RivalExitHerbShop::
	opendoor 12, 15
	waitdooranim
	addobject LOCALID_LAVARIDGE_RIVAL
	applymovement LOCALID_LAVARIDGE_RIVAL, LavaridgeTown_Movement_RivalExitHerbShop
	waitmovement 0
	closedoor 12, 15
	waitdooranim
	applymovement LOCALID_LAVARIDGE_RIVAL, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_LAVARIDGE_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_LAVARIDGE_RIVAL, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	return

LavaridgeTown_EventScript_RivalApproachPlayer1::
	applymovement LOCALID_LAVARIDGE_RIVAL, LavaridgeTown_Movement_RivalApproachPlayer1
	waitmovement 0
	return

LavaridgeTown_EventScript_RivalApproachPlayer2::
	applymovement LOCALID_LAVARIDGE_RIVAL, LavaridgeTown_Movement_RivalApproachPlayer2
	waitmovement 0
	return

LavaridgeTown_EventScript_RivalExit1::
	applymovement LOCALID_PLAYER, LavaridgeTown_Movement_PlayerWatchRivalExit
	applymovement LOCALID_LAVARIDGE_RIVAL_ON_BIKE, LavaridgeTown_Movement_RivalExit1
	waitmovement 0
	return

LavaridgeTown_EventScript_RivalExit2::
	applymovement LOCALID_LAVARIDGE_RIVAL_ON_BIKE, LavaridgeTown_Movement_RivalExit2
	waitmovement 0
	return

LavaridgeTown_Movement_RivalExit2:
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

LavaridgeTown_Movement_PlayerWatchRivalExit:
	delay_16
	delay_8
	walk_in_place_faster_right
	step_end

LavaridgeTown_Movement_RivalExit1:
	walk_fast_down
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

LavaridgeTown_Movement_RivalApproachPlayer2:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

LavaridgeTown_Movement_RivalApproachPlayer1:
	walk_left
	walk_left
	walk_up
	step_end

LavaridgeTown_Movement_RivalExitHerbShop:
	walk_down
	step_end

LavaridgeTown_EventScript_HotSpringsTrigger::
	specialvar VAR_RESULT, GetPlayerFacingDirection
	goto_if_eq VAR_RESULT, DIR_SOUTH, LavaridgeTown_EventScript_EnteredHotSprings
	end

LavaridgeTown_EventScript_EnteredHotSprings::
	incrementgamestat GAME_STAT_ENTERED_HOT_SPRINGS
	end

LavaridgeTown_EventScript_ExpertM::
	msgbox LavaridgeTown_Text_HotSpringsNeverRunDry, MSGBOX_NPC
	end

LavaridgeTown_EventScript_OldMan::
	msgbox LavaridgeTown_Text_PokemonNippedBackside, MSGBOX_SIGN
	end

LavaridgeTown_EventScript_Twin::
	msgbox LavaridgeTown_Text_BatheInHotSpringsEveryDay, MSGBOX_NPC
	end

LavaridgeTown_EventScript_HotSpringsOldWoman1::
	msgbox LavaridgeTown_Text_IfPokemonInHotSprings, MSGBOX_NPC
	end

LavaridgeTown_EventScript_HotSpringsOldWoman2::
	msgbox LavaridgeTown_Text_HotSpringsClaims, MSGBOX_NPC
	end

LavaridgeTown_EventScript_ExpertF::
	msgbox LavaridgeTown_Text_OhYouLikeHotSprings, MSGBOX_NPC
	end

LavaridgeTown_EventScript_EggWoman::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_LAVARIDGE_EGG, LavaridgeTown_EventScript_ReceivedEgg
	msgbox LavaridgeTown_Text_HaveEggWillYouTakeIt, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, LavaridgeTown_EventScript_DeclineEgg
	getpartysize
	goto_if_eq VAR_RESULT, PARTY_SIZE, LavaridgeTown_EventScript_NoRoomForEgg
	msgbox LavaridgeTown_Text_HopeYoullWalkPlentyWithEgg, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_LAVARIDGE_EGG
	playfanfare MUS_OBTAIN_ITEM
	message LavaridgeTown_Text_ReceivedTheEgg
	waitfanfare
	giveegg SPECIES_WYNAUT
	release
	end

LavaridgeTown_EventScript_ReceivedEgg::
	msgbox LavaridgeTown_Text_EverySoOftenEggFoundAtDayCare, MSGBOX_DEFAULT
	release
	end

LavaridgeTown_EventScript_NoRoomForEgg::
	msgbox LavaridgeTown_Text_NoRoomForThisEgg, MSGBOX_DEFAULT
	release
	end

LavaridgeTown_EventScript_DeclineEgg::
	msgbox LavaridgeTown_Text_AsYouWishThen, MSGBOX_DEFAULT
	release
	end

LavaridgeTown_EventScript_TownSign::
	msgbox LavaridgeTown_Text_TownSign, MSGBOX_SIGN
	end

LavaridgeTown_EventScript_GymSign::
	msgbox LavaridgeTown_Text_GymSign, MSGBOX_SIGN
	end

LavaridgeTown_EventScript_HerbShopSign::
	msgbox LavaridgeTown_Text_HerbShopSign, MSGBOX_SIGN
	end

LavaridgeTown_Text_MayNiceBadgesTakeThis:
	.string "MAY: {PLAYER}{KUN}, ¡cuánto tiempo!\p"
	.string "Oh, mientras yo visitaba las\n"
	.string "aguas termales, conseguiste la\p"
	.string "MEDALLA DEL GIMNASIO LAVARIDGE.\n"
	.string "Debes haber atrapado\l"
	.string "buenos POKéMON...\p"
	.string "No, creo que los entrenaste tú.\n"
	.string "tengas esto.$"

LavaridgeTown_Text_MayExplainGoGogglesChallengeDad:
	.string "Supongo que estaría bien que...\n"
	.string "MAY: Con esas GO-GOGGLES, no\l"
	.string "tendrás problemas en el desierto\p"
	.string "Pero, vaya, {PLAYER}{KUN}...\n"
	.string "Retar a los GIMNASIOS...\p"
	.string "Te esfuerzas mucho porque no\n"
	.string "quieres perder contra mí, ¡apuesto!\p"
	.string "{PLAYER}{KUN}, creo que debería\n"
	.string "retar a tu papá en el GIMNASIO de\p"
	.string "PETALBURG. ¡Nos vemos!$"

LavaridgeTown_Text_BrendanNiceBadgesTakeThis:
	.string "BRENDAN: {PLAYER}, hola, ha pasado tiempo.\n"
	.string "¿Cómo va todo?\p"
	.string "Hmm...\n"
	.string "Es una buena colección de MEDALLAS.\p"
	.string "Muy bien, entonces.\n"
	.string "Toma esto, te servirá.$"

LavaridgeTown_Text_BrendanExplainGoGogglesChallengeDad:
	.string "BRENDAN: Guárdalo si piensas ir al\n"
	.string "desierto que está cerca de la\l"
	.string "RUTA 111.\p"
	.string "Debe haber algunos POKéMON que\n"
	.string "viven solo en el desierto.\l"
	.string "Podrías buscar algunos por aquí.\p"
	.string "En cuanto a mí...\n"
	.string "Pienso retar a NORMAN,\l"
	.string "el LÍDER del GIMNASIO de PETALBURG.\p"
	.string "A diferencia tuya, {PLAYER}, tu papá\n"
	.string "parece ser muy fuerte.\p"
	.string "¡Nos vemos luego!$"

LavaridgeTown_Text_HaveEggWillYouTakeIt:
	.string "Tengo aquí un HUEVO.\p"
	.string "Esperaba que naciera al cubrirlo con\n"
	.string "arena caliente en las termas.\l"
	.string "Pero eso no parece ser suficiente...\p"
	.string "He oído que sería mejor si se\n"
	.string "mantuviera junto a POKéMON y\l"
	.string "se llevara consigo.\p"
	.string "Eres ENTRENADOR, ¿verdad?\n"
	.string "Tus POKéMON irradian vitalidad.\p"
	.string "Entonces, ¿qué dices?\n"
	.string "¿Llevarás este HUEVO para que nazca?$"

LavaridgeTown_Text_HopeYoullWalkPlentyWithEgg:
	.string "¡Bien! ¡Espero que camines mucho\n"
	.string "con este HUEVO!$"

LavaridgeTown_Text_ReceivedTheEgg:
	.string "{PLAYER} recibió el HUEVO.$"

LavaridgeTown_Text_NoRoomForThisEgg:
	.string "¿Oh? Tienes demasiados POKéMON.\n"
	.string "No hay sitio para este HUEVO...$"

LavaridgeTown_Text_AsYouWishThen:
	.string "Como quieras, entonces...\p"
	.string "Si cambias de opinión sobre\n"
	.string "eclosionar este HUEVO, estaré aquí.$"

LavaridgeTown_Text_EverySoOftenEggFoundAtDayCare:
	.string "De vez en cuando, hallan un HUEVO en\n"
	.string "la GUARDERÍA POKéMON.\p"
	.string "O al menos eso dice el rumor.$"

LavaridgeTown_Text_HotSpringsNeverRunDry:
	.string "Sacamos el agua caliente que queramos,\n"
	.string "y las fuentes nunca se agotan.\p"
	.string "¿No es mágico?\p"
	.string "Estas fuentes aparecen cerca de\n"
	.string "volcanes activos. El agua bajo tierra\l"
	.string "se calienta con magma y brota\l"
	.string "como aguas termales.$"

LavaridgeTown_Text_PokemonNippedBackside:
	.string "Estar enterrado en esta arena...\n"
	.string "Suspiro...\p"
	.string "Es tan cálido y celestial...\p"
	.string "¡¿Eh?! ¡Gyaah! ¡Ay!\p"
	.string "¡Un POKéMON me mordió atrás!$"

LavaridgeTown_Text_OhYouLikeHotSprings:
	.string "Oh, ¿te gustan las termales?\p"
	.string "Es sorprendente para alguien tan\n"
	.string "joven como tú.$"

LavaridgeTown_Text_BatheInHotSpringsEveryDay:
	.string "Me baño en las termales cada día.\p"
	.string "Quiero ser una LÍDER de GIMNASIO\n"
	.string "bella y fuerte como FLANNERY.$"

LavaridgeTown_Text_IfPokemonInHotSprings:
	.string "Si la gente pone POKéMON en termales,\n"
	.string "podría ser muy extraño.\p"
	.string "Podría ser un baño eléctrico, o\n"
	.string "de burbujas, ¡o hasta de lava!$"

LavaridgeTown_Text_HotSpringsClaims:
	.string "Dicen que estas aguas termales\n"
	.string "calman la tensión nerviosa,\l"
	.string "alivian dolores musculares, resuelven\l"
	.string "problemas románticos y atraen\l"
	.string "el dinero...$"

LavaridgeTown_Text_TownSign:
	.string "PUEBLO LAVARIDGE\p"
	.string "“AGUAS TERMALES DEL POKéMON CENTER\n"
	.string "¡Un lugar excelente para relajarse!”$"

LavaridgeTown_Text_GymSign:
	.string "GIMNASIO POKéMON de PUEBLO LAVARIDGE\n"
	.string "LÍDER: FLANNERY\l"
	.string "“¡Una pasión ardiente que quema!”$"

LavaridgeTown_Text_HerbShopSign:
	.string "TIENDA DE HIERBAS POKéMON\n"
	.string "“¡Sabor amargo, mejor cura!”$"

