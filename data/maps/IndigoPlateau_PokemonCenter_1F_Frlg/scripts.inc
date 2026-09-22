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
	.string "Yo!\n"
	.string "¡Un futuro campeón!\p"
	.string "At the POKéMON LEAGUE, you will\n"
	.string "face the ELITE FOUR all in a row.\p"
	.string "Si pierdes, tienes que empezar\n"
	.string "over again!\p"
	.string "¡Es ahora!\n"
	.string "¡Ve a por ello!$"

IndigoPlateau_PokemonCenter_1F_Text_FaceEliteFourGoodLuck::
	.string "De aquí en adelante, te\n"
	.string "ELITE FOUR one by one.\p"
	.string "Si ganas, se abre una puerta\n"
	.string "next TRAINER. Good luck!$"

IndigoPlateau_PokemonCenter_1F_Text_LoreleiIsAbsentClosedForTimeBeing::
	.string "Lo siento mucho, pero has\n"
	.string "your time coming here.\p"
	.string "LORELEI of the ELITE FOUR is\n"
	.string "absent, you see.\p"
	.string "As a result, the POKéMON LEAGUE is\n"
	.string "cerrado por el momento.$"

IndigoPlateau_PokemonCenter_1F_Text_AgathaWhuppedUs::
	.string "AGATHA's GHOST-type POKéMON are\n"
	.string "espantosos en dureza.\p"
	.string "I took my FIGHTING-type POKéMON\n"
	.string "y los subió al máximo.\p"
	.string "I went at AGATHA feeling pretty\n"
	.string "confiados, pero nos venció.\p"
	.string "Esa anciana también tiene un\n"
	.string "también es impulsiva.\p"
	.string "No hace falta casi nada para\n"
	.string "que esa señora empiece a gritar.$"

IndigoPlateau_PokemonCenter_1F_Text_LancesCousinGymLeaderFarAway::
	.string "Quizá ser del ALTO MANDO\n"
	.string "va en la sangre.\p"
	.string "Por lo que oí, LANCE tiene\n"
	.string "un primo que es LÍDER de GIMNASIO\l"
	.string "un lugar muy lejano.$"

