IndigoPlateau_PokemonCenter_1F_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, IndigoPlateau_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

IndigoPlateau_PokemonCenter_1F_OnTransition::
	setrespawn HEAL_LOCATION_INDIGO_PLATEAU
	specialvar VAR_RESULT, IsNationalPokedexEnabled
	call_if_eq VAR_RESULT, TRUE, IndigoPlateau_PokemonCenter_1F_EventScript_CheckBlockDoor
	end

IndigoPlateau_PokemonCenter_1F_EventScript_CheckBlockDoor::
	goto_if_set FLAG_IS_CHAMPION, Common_EventScript_NopReturn
	setobjectxyperm LOCALID_LEAGUE_DOOR_GUARD, 4, 2
	return

IndigoPlateau_PokemonCenter_1F_EventScript_DoorGuard::
	lock
	faceplayer
	specialvar VAR_RESULT, IsNationalPokedexEnabled
	goto_if_eq VAR_RESULT, TRUE, IndigoPlateau_PokemonCenter_1F_EventScript_CheckSeviiIslandComplete
	msgbox IndigoPlateau_PokemonCenter_1F_Text_FaceEliteFourGoodLuck
	release
	end

IndigoPlateau_PokemonCenter_1F_EventScript_CheckSeviiIslandComplete::
	goto_if_set FLAG_IS_CHAMPION, IndigoPlateau_PokemonCenter_1F_EventScript_SeviiIslandComplete
	msgbox IndigoPlateau_PokemonCenter_1F_Text_LoreleiIsAbsentClosedForTimeBeing
	release
	end

IndigoPlateau_PokemonCenter_1F_EventScript_SeviiIslandComplete::
	msgbox IndigoPlateau_PokemonCenter_1F_Text_FaceEliteFourGoodLuck
	release
	end

IndigoPlateau_PokemonCenter_1F_EventScript_GymGuy::
	msgbox IndigoPlateau_PokemonCenter_1F_Text_GymGuyAdvice, MSGBOX_NPC
	end

IndigoPlateau_PokemonCenter_1F_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart IndigoPlateau_PokemonCenter_1F_Items
	msgbox gText_PleaseComeAgain
	release
	end

	.align 2
IndigoPlateau_PokemonCenter_1F_Items::
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_FULL_RESTORE
	.2byte ITEM_MAX_POTION
	.2byte ITEM_REVIVE
	.2byte ITEM_FULL_HEAL
	.2byte ITEM_MAX_REPEL
	.2byte ITEM_NONE
	release
	end

IndigoPlateau_PokemonCenter_1F_EventScript_Nurse::
	lock
	faceplayer
	call EventScript_PkmnCenterNurse_Frlg
	release
	end

IndigoPlateau_PokemonCenter_1F_Text_GymGuyAdvice::
	.string "¡Ey!\n"
	.string "¡Un futuro campeón!\p"
	.string "En la LIGA POKéMON te enfrentarás\n"
	.string "al ALTO MANDO uno tras otro.\p"
	.string "Si pierdes, tienes que empezar\n"
	.string "¡desde el principio!\p"
	.string "¡Es ahora!\n"
	.string "¡Ve a por ello!$"

IndigoPlateau_PokemonCenter_1F_Text_FaceEliteFourGoodLuck::
	.string "De aquí en adelante, te\n"
	.string "enfrentarás al ALTO MANDO uno a uno.\p"
	.string "Si ganas, se abre una puerta\n"
	.string "al siguiente ENTRENADOR. ¡Buena suerte!$"

IndigoPlateau_PokemonCenter_1F_Text_LoreleiIsAbsentClosedForTimeBeing::
	.string "Lo siento mucho, pero has\n"
	.string "perdido el tiempo viniendo aquí.\p"
	.string "LORELEI del ALTO MANDO está\n"
	.string "ausente, como ves.\p"
	.string "Por eso, la LIGA POKéMON está\n"
	.string "cerrada por el momento.$"

IndigoPlateau_PokemonCenter_1F_Text_AgathaWhuppedUs::
	.string "Los POKéMON de tipo FANTASMA de AGATHA\n"
	.string "son espantosamente duros.\p"
	.string "Entrené a mis POKéMON de tipo LUCHA\n"
	.string "y los subí al máximo.\p"
	.string "Fui contra AGATHA sintiéndome muy\n"
	.string "confiado, pero nos venció.\p"
	.string "Esa anciana también tiene un\n"
	.string "genio muy impulsivo.\p"
	.string "No hace falta casi nada para\n"
	.string "que esa señora empiece a gritar.$"

IndigoPlateau_PokemonCenter_1F_Text_LancesCousinGymLeaderFarAway::
	.string "Quizá ser del ALTO MANDO\n"
	.string "va en la sangre.\p"
	.string "Por lo que oí, LANCE tiene\n"
	.string "un primo que es LÍDER de GIMNASIO\l"
	.string "un lugar muy lejano.$"

