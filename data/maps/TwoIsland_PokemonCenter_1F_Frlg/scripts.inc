TwoIsland_PokemonCenter_1F_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, TwoIsland_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

TwoIsland_PokemonCenter_1F_OnTransition::
	setrespawn HEAL_LOCATION_TWO_ISLAND
	end

TwoIsland_PokemonCenter_1F_EventScript_Nurse::
	lock
	faceplayer
	call EventScript_PkmnCenterNurse_Frlg
	release
	end

TwoIsland_PokemonCenter_1F_EventScript_GBAKid::
	msgbox TwoIsland_PokemonCenter_1F_Text_HaveYouVisitedGameCorner, MSGBOX_NPC
	end

TwoIsland_PokemonCenter_1F_EventScript_BugCatcher::
	msgbox TwoIsland_PokemonCenter_1F_Text_OldLadyLivesOutOnCape, MSGBOX_NPC
	end

TwoIsland_PokemonCenter_1F_Text_HaveYouVisitedGameCorner::
	.string "¿Ya visitaste la SALA DE JUEGOS?\n"
	.string "JEFE DE FÁBRICA?\p"
	.string "No es bueno ir solo.\n"
	.string "Debes llevar a un amigo contigo.$"

TwoIsland_PokemonCenter_1F_Text_OldLadyLivesOutOnCape::
	.string "No vive mucha gente ahí\n"
	.string "TWO ISLAND.\p"
	.string "Hay una anciana que vive\n"
	.string "en el cabo.\p"
	.string "Ha vivido ahí desde no sé\n"
	.string "cuándo.$"

