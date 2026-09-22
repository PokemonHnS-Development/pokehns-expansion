FiveIsland_PokemonCenter_1F_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, FiveIsland_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

FiveIsland_PokemonCenter_1F_OnTransition::
	setrespawn HEAL_LOCATION_FIVE_ISLAND
	end

FiveIsland_PokemonCenter_1F_EventScript_Nurse::
	lock
	faceplayer
	call EventScript_PkmnCenterNurse_Frlg
	release
	end

FiveIsland_PokemonCenter_1F_EventScript_Chef::
	msgbox FiveIsland_PokemonCenter_1F_Text_OnMyWayToPrepareMeal, MSGBOX_NPC
	end

FiveIsland_PokemonCenter_1F_EventScript_CooltrainerF::
	msgbox FiveIsland_PokemonCenter_1F_Text_YoureOnQuestToCatchEveryMon, MSGBOX_NPC
	end

FiveIsland_PokemonCenter_1F_Text_OnMyWayToPrepareMeal::
	.string "Voy de camino a preparar una comida\n"
	.string "para cierta persona de alta sociedad.$"

FiveIsland_PokemonCenter_1F_Text_YoureOnQuestToCatchEveryMon::
	.string "Estás en una misión para atrapar a todos\n"
	.string "single kind of POKéMON?\p"
	.string "…Qué increíble. Avísame si\n"
	.string "atrapas uno fuerte!$"

