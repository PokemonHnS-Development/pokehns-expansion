ViridianCity_PokemonCenter_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, ViridianCity_PokemonCenter_OnTransition
	.byte 0

ViridianCity_PokemonCenter_OnTransition::
	setrespawn HEAL_LOCATION_VIRIDIAN_CITY_HNS
	end

ViridianCity_PokemonCenter_EventScript_CooltrainerM::
	goto_if_set FLAG_HIDE_CINNABAR_BLUE, VirianCity_EventScript_GymGrampsBlue
	msgbox ViridianCity_PokemonCenter_Text_1FCooltrainerM, MSGBOX_NPC
	end

ViridianCity_PokemonCenter_EventScript_CooltrainerMBlue::
	msgbox ViridianCity_PokemonCenter_Text_1FCooltrainerM_BlueReturned, MSGBOX_NPC
	end

ViridianCity_PokemonCenter_EventScript_CooltrainerF::
	msgbox ViridianCity_PokemonCenter_Text_1FCooltrainerF, MSGBOX_NPC
	end

ViridianCity_PokemonCenter_EventScript_BugCatcher::
	msgbox ViridianCity_PokemonCenter_Text_1FBugCatcher, MSGBOX_NPC
	end

ViridianCity_PokemonCenter_Text_1FCooltrainerM:
	.string "¿Dónde rayos estará el LÍDER del\n"
	.string "GIMNASIO de VERIDIAN? ¡Quiero retarlo!$"

ViridianCity_PokemonCenter_Text_1FCooltrainerM_BlueReturned:
	.string "No hay ENTRENADORES en el\n"
	.string "GIMNASIO de VERIDIAN.\p"
	.string "El LÍDER dice que su política es\n"
	.string "ganar sin tener subordinados.$"

ViridianCity_PokemonCenter_Text_1FCooltrainerF:
	.string "Oí que el GIMNASIO de CANNON\n"
	.string "desapareció.\p"
	.string "Me pregunto qué pasó con BLAINE,\n"
	.string "el LÍDER de GIMNASIO.$"

ViridianCity_PokemonCenter_Text_1FBugCatcher:
	.string "My dream is to become a GYM LEADER.$"
