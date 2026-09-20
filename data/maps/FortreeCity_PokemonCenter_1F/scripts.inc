FortreeCity_PokemonCenter_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, FortreeCity_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

FortreeCity_PokemonCenter_1F_OnTransition:
	setrespawn HEAL_LOCATION_FORTREE_CITY
	end

FortreeCity_PokemonCenter_1F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_FORTREE_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

FortreeCity_PokemonCenter_1F_EventScript_Gentleman::
	msgbox FortreeCity_PokemonCenter_1F_Text_GoToSafariZone, MSGBOX_NPC
	end

FortreeCity_PokemonCenter_1F_EventScript_Man::
	msgbox FortreeCity_PokemonCenter_1F_Text_RecordCornerIsNeat, MSGBOX_NPC
	end

FortreeCity_PokemonCenter_1F_EventScript_Boy::
	msgbox FortreeCity_PokemonCenter_1F_Text_DoYouKnowAboutPokenav, MSGBOX_NPC
	end

FortreeCity_PokemonCenter_1F_Text_GoToSafariZone:
	.string "Escucha, chico, ¿estás trabajando\n"
	.string "en una POKéDEX?\p"
	.string "Hmm... Ve a la ZONA SAFARI.\n"
	.string "Esa es mi sugerencia.$"

FortreeCity_PokemonCenter_1F_Text_RecordCornerIsNeat:
	.string "¿Has hecho algo en el\n"
	.string "RINCÓN DE RÉCORDS?\p"
	.string "Es genial. Mezcla y compara\n"
	.string "los récords de los ENTRENADORES.\p"
	.string "No sé muy bien cómo funciona,\n"
	.string "¡pero es genial y emocionante!$"

FortreeCity_PokemonCenter_1F_Text_DoYouKnowAboutPokenav:
	.string "¡Vaya, tienes un POKéNAV!\n"
	.string "¡Y es igualito al mío!\p"
	.string "¿Conoces el sistema de\n"
	.string "LLAMADA DE COMBATE del POKéNAV?\p"
	.string "Úsalo para chatear con\n"
	.string "ENTRENADORES registrados.\p"
	.string "También muestra qué ENTRENADORES\n"
	.string "quieren una revancha contigo.\p"
	.string "¡Es genial! Los de DEVON\n"
	.string "¡sí que saben lo que hacen!$"

