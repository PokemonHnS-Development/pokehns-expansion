ViridianCity_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, ViridianCity_OnTransition
	.byte 0

ViridianCity_OnTransition::
	setworldmapflag FLAG_WORLD_MAP_VIRIDIAN_CITY
	call_if_eq VAR_MAP_SCENE_VIRIDIAN_CITY_OLD_MAN, 0, ViridianCity_EventScript_SetOldManBlockingRoad
	call_if_eq VAR_MAP_SCENE_VIRIDIAN_CITY_OLD_MAN, 1, ViridianCity_EventScript_SetOldManStandingByRoad
	call_if_ge VAR_MAP_SCENE_VIRIDIAN_CITY_OLD_MAN, 2, ViridianCity_EventScript_SetOldManNormal
	call_if_eq VAR_MAP_SCENE_VIRIDIAN_CITY_GYM_DOOR, 0, ViridianCity_EventScript_TryUnlockGym
	end

ViridianCity_EventScript_SetOldManNormal::
	setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_OLD_MAN_1
	return

ViridianCity_EventScript_SetOldManStandingByRoad::
	setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_OLD_MAN_1
	setobjectxyperm LOCALID_TUTORIAL_MAN, 21, 8
	setobjectmovementtype LOCALID_TUTORIAL_MAN, MOVEMENT_TYPE_LOOK_AROUND
	return

ViridianCity_EventScript_SetOldManBlockingRoad::
	setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_OLD_MAN_LYING_DOWN
	setobjectxyperm LOCALID_TUTORIAL_MAN, 21, 11
	setobjectmovementtype LOCALID_TUTORIAL_MAN, MOVEMENT_TYPE_FACE_DOWN
	return

ViridianCity_EventScript_TryUnlockGym::
	goto_if_unset FLAG_BADGE02_GET, Common_EventScript_NopReturn
	goto_if_unset FLAG_BADGE03_GET, Common_EventScript_NopReturn
	goto_if_unset FLAG_BADGE04_GET, Common_EventScript_NopReturn
	goto_if_unset FLAG_BADGE05_GET, Common_EventScript_NopReturn
	goto_if_unset FLAG_BADGE06_GET, Common_EventScript_NopReturn
	goto_if_unset FLAG_BADGE07_GET, Common_EventScript_NopReturn
	setvar VAR_MAP_SCENE_VIRIDIAN_CITY_GYM_DOOR, 1
	return

ViridianCity_EventScript_GymDoorLocked::
	lockall
	textcolor NPC_TEXT_COLOR_NEUTRAL
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	delay 20
	msgbox ViridianCity_Text_GymDoorsAreLocked
	closemessage
	applymovement LOCALID_PLAYER, ViridianCity_Movement_JumpDownLedge
	waitmovement 0
	releaseall
	end

ViridianCity_Movement_JumpDownLedge::
	jump_2_down
	step_end

ViridianCity_EventScript_CitySign::
	msgbox ViridianCity_Text_CitySign, MSGBOX_SIGN
	end

ViridianCity_EventScript_TrainerTips1::
	msgbox ViridianCity_Text_CatchMonsForEasierBattles, MSGBOX_SIGN
	end

ViridianCity_EventScript_TrainerTips2::
	msgbox ViridianCity_Text_MovesLimitedByPP, MSGBOX_SIGN
	end

ViridianCity_EventScript_GymSign::
	msgbox ViridianCity_Text_GymSign, MSGBOX_SIGN
	end

ViridianCity_EventScript_GymDoor::
	msgbox ViridianCity_Text_GymDoorsAreLocked, MSGBOX_SIGN
	end

ViridianCity_EventScript_Boy::
	msgbox ViridianCity_Text_CanCarryMonsAnywhere, MSGBOX_NPC
	end

@ Other old man, not the tutorial old man
ViridianCity_EventScript_OldMan::
	lock
	faceplayer
	goto_if_eq VAR_MAP_SCENE_VIRIDIAN_CITY_GYM_DOOR, 1, ViridianCity_EventScript_OldManGymLeaderReturned
	msgbox ViridianCity_Text_GymClosedWonderWhoLeaderIs
	closemessage
	applymovement LOCALID_VIRIDIAN_OLD_MAN, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

ViridianCity_EventScript_OldManGymLeaderReturned::
	msgbox ViridianCity_Text_ViridiansGymLeaderReturned
	release
	end

ViridianCity_EventScript_TutorialOldMan::
	lock
	faceplayer
	goto_if_set FLAG_BADGE01_GET, ViridianCity_EventScript_AskIfTeachyTVHelpful
	goto_if_ge VAR_MAP_SCENE_VIRIDIAN_CITY_OLD_MAN, 2, ViridianCity_EventScript_TutorialCompleted
	goto_if_eq VAR_MAP_SCENE_VIRIDIAN_CITY_OLD_MAN, 1, ViridianCity_EventScript_TutorialStart
	goto_if_eq VAR_MAP_SCENE_VIRIDIAN_CITY_OLD_MAN, 0, ViridianCity_EventScript_TutorialNotReady
	end

ViridianCity_EventScript_AskIfTeachyTVHelpful::
	msgbox ViridianCity_Text_HowsTeachyTVHelping, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, ViridianCity_EventScript_TeachyTVNotHelpful
	msgbox ViridianCity_Text_MyGrandsonOnTheShow
	release
	end

ViridianCity_EventScript_TeachyTVNotHelpful::
	msgbox ViridianCity_Text_TooBusyForTeachyTV
	release
	end

ViridianCity_EventScript_TutorialCompleted::
	msgbox ViridianCity_Text_WeakenMonsFirstToCatch
	release
	end

ViridianCity_EventScript_TutorialStart::
	call ViridianCity_EventScript_DoTutorialBattle
	release
	end

@ Unused
ViridianCity_EventScript_WatchToLearnBasics::
	msgbox ViridianCity_Text_WatchThatToLearnBasics
	release
	end

@ Unused. Starts battle after the post battle text, which is odd.
ViridianCity_EventScript_TutorialUnused::
	msgbox ViridianCity_Text_ThatWasEducationalTakeThis
	special StartOldManTutorialBattle
	waitstate
	release
	end

ViridianCity_EventScript_TutorialNotReady::
	msgbox ViridianCity_Text_ThisIsPrivateProperty
	closemessage
	release
	end

ViridianCity_EventScript_Youngster::
	lock
	faceplayer
	msgbox ViridianCity_Text_WantToKnowAboutCaterpillarMons, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, ViridianCity_EventScript_YoungsterExplainCaterpillars
	goto_if_eq VAR_RESULT, NO, ViridianCity_EventScript_YoungsterDeclineExplanation
	end

ViridianCity_EventScript_YoungsterExplainCaterpillars::
	msgbox ViridianCity_Text_ExplainCaterpieWeedle
	release
	end

ViridianCity_EventScript_YoungsterDeclineExplanation::
	msgbox ViridianCity_Text_OhOkayThen
	release
	end

ViridianCity_EventScript_Woman::
	lock
	faceplayer
	goto_if_eq VAR_MAP_SCENE_VIRIDIAN_CITY_OLD_MAN, 0, ViridianCity_EventScript_WomanRoadBlocked
	msgbox ViridianCity_Text_GoShoppingInPewterOccasionally
	release
	end

ViridianCity_EventScript_WomanRoadBlocked::
	msgbox ViridianCity_Text_GrandpaHasntHadCoffeeYet
	closemessage
	applymovement LOCALID_VIRIDIAN_WOMAN, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

ViridianCity_EventScript_DreamEaterTutor::
	goto EventScript_DreamEaterTutor
	end

ViridianCity_EventScript_RoadBlocked::
	lockall
	textcolor NPC_TEXT_COLOR_MALE
	msgbox ViridianCity_Text_ThisIsPrivateProperty
	closemessage
	applymovement LOCALID_PLAYER, ViridianCity_Movement_WalkDown
	waitmovement 0
	releaseall
	end

ViridianCity_Movement_WalkDown::
	walk_down
	step_end

ViridianCity_EventScript_TutorialTriggerLeft::
	lockall
	textcolor NPC_TEXT_COLOR_MALE
	applymovement LOCALID_TUTORIAL_MAN, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	call ViridianCity_EventScript_DoTutorialBattle
	release
	end

ViridianCity_EventScript_TutorialTriggerRight::
	lockall
	textcolor NPC_TEXT_COLOR_MALE
	applymovement LOCALID_TUTORIAL_MAN, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	call ViridianCity_EventScript_DoTutorialBattle
	release
	end

ViridianCity_EventScript_DoTutorialBattle::
	msgbox ViridianCity_Text_ShowYouHowToCatchMons
	closemessage
	special StartOldManTutorialBattle
	waitstate
	lock
	faceplayer
	msgbox ViridianCity_Text_ThatWasEducationalTakeThis
	setvar VAR_MAP_SCENE_VIRIDIAN_CITY_OLD_MAN, 2
	giveitem ITEM_TEACHY_TV
	msgbox ViridianCity_Text_WatchThatToLearnBasics
	return

ViridianCity_Text_CanCarryMonsAnywhere::
	.string "Those POKé BALLS at your waist!\n"
	.string "You have POKéMON, don't you?\p"
	.string "Es genial que puedas llevar y\n"
	.string "use POKéMON anytime, anywhere.$"

ViridianCity_Text_GymClosedWonderWhoLeaderIs::
	.string "This POKéMON GYM is always closed.\p"
	.string "¿Quién será el LÍDER?$"

ViridianCity_Text_ViridiansGymLeaderReturned::
	.string "VIRIDIAN GYM's LEADER returned!$"

ViridianCity_Text_WantToKnowAboutCaterpillarMons::
	.string "¿Quieres saber sobre los dos\n"
	.string "kinds of caterpillar POKéMON?$"

ViridianCity_Text_OhOkayThen::
	.string "Oh, okay then!$"

ViridianCity_Text_ExplainCaterpieWeedle::
	.string "CATERPIE no tiene veneno,\n"
	.string "pero WEEDLE sí.\p"
	.string "Watch that your POKéMON aren't\n"
	.string "stabbed by WEEDLE's POISON STING.$"

ViridianCity_Text_GrandpaHasntHadCoffeeYet::
	.string "Oh, Grandpa!\n"
	.string "¡No seas tan cruel!\p"
	.string "I'm so sorry.\n"
	.string "Aún no ha tomado su café.$"

ViridianCity_Text_GoShoppingInPewterOccasionally::
	.string "Voy de compras a CIUDAD\n"
	.string "occasionally.\p"
	.string "Tengo que tomar el sendero\n"
	.string "sinuoso del BOSQUE VERDE.$"

ViridianCity_Text_ThisIsPrivateProperty::
	.string "Te prohibo totalmente\n"
	.string "pasar por aquí!\p"
	.string "¡Esta es propiedad privada!$"

ViridianCity_Text_ShowYouHowToCatchMons::
	.string "Bueno, ya me tomé mi café, y\n"
	.string "¡eso es lo que necesito para irme!\p"
	.string "Hm?\n"
	.string "What is that red box you have?\p"
	.string "Ah, así que estás trabajando\n"
	.string "POKéDEX.\p"
	.string "Entonces déjame darte unas\npalabras de"
	.string "advice.\p"
	.string "Whenever you catch a POKéMON,\n"
	.string "the POKéDEX automatically updates\l"
	.string "its data.\p"
	.string "...No sabes cómo atrapar\n"
	.string "un POKéMON?\p"
	.string "Supongo que será mejor\nmostrártelo"
	.string "then!$"

ViridianCity_Text_ThatWasEducationalTakeThis::
	.string "¡Listo! Ahora dime, eso fue\n"
	.string "instructivo, ¿verdad?\p"
	.string "Y aquí, toma esto también.$"

ViridianCity_Text_WatchThatToLearnBasics::
	.string "Si hay algo que no entiendas,\n"
	.string "mira eso.\p"
	.string "Te enseñará lo básico\n"
	.string "of being a POKéMON TRAINER.$"

ViridianCity_Text_WeakenMonsFirstToCatch::
	.string "Bueno, ya me tomé mi café, y\n"
	.string "¡eso es lo que necesito para irme!\p"
	.string "Pero lo hice demasiado fuerte.\n"
	.string "Me dio dolor de cabeza...\p"
	.string "Por cierto, ¿ya estás llenando\n"
	.string "POKéDEX?\p"
	.string "Al principio, enfócate en debilitar\n"
	.string "POKéMON before trying to catch it.$"

ViridianCity_Text_HowsTeachyTVHelping::
	.string "Bueno, ya me tomé mi café, y\n"
	.string "¡eso es lo que necesito para irme!\p"
	.string "Pero lo hice demasiado fuerte.\n"
	.string "Me dio dolor de cabeza...\p"
	.string "Por cierto, ¿mi vieja TV\n"
	.string "¿Te ayudo?$"

ViridianCity_Text_MyGrandsonOnTheShow::
	.string "Wahaha!\n"
	.string "¡Es mi nieto en el programa!\p"
	.string "Como es él quien da las\n"
	.string "clases, seguro aprenderás.$"

ViridianCity_Text_TooBusyForTeachyTV::
	.string "Hm... Estás tan ocupado que no\n"
	.string "tienes tiempo para TV ENSEÑA...\p"
	.string "El tiempo es dinero, y ninguno\n"
	.string "se gastarán mal...$"

ViridianCity_Text_CitySign::
	.string "VIRIDIAN CITY \n"
	.string "El Paraíso Eternamente Verde$"

ViridianCity_Text_CatchMonsForEasierBattles::
	.string "CONSEJOS DE ENTRENADOR\p"
	.string "Catch POKéMON and expand your\n"
	.string "collection.\p"
	.string "Cuanto más tengas, más fácil\n"
	.string "es batallar.$"

ViridianCity_Text_MovesLimitedByPP::
	.string "CONSEJOS DE ENTRENADOR\p"
	.string "The battle moves of POKéMON are\n"
	.string "limitados por sus PUNTOS DE PODER, PP.\p"
	.string "Para reponer PP, descansa a tu\n"
	.string "POKéMON at a POKéMON CENTER.$"

ViridianCity_Text_GymSign::
	.string "VIRIDIAN CITY POKéMON GYM$"

ViridianCity_Text_GymDoorsAreLocked::
	.string "VIRIDIAN GYM's doors are locked...$"

