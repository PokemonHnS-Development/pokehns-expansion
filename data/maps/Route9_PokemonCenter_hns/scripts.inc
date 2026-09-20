Route9_PokemonCenter_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route9_PokemonCenter_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

Route9_PokemonCenter_OnTransition::
	setflag FLAG_VISITED_ROUTE10
	setrespawn HEAL_LOCATION_ROUTE10_HNS
	end

Route9_PokemonCenter_EventScript_Engineer1::
	msgbox Route9_PokemonCenter_Text_Engineer1, MSGBOX_NPC
	end

Route9_PokemonCenter_EventScript_Engineer2::
	msgbox Route9_PokemonCenter_Text_Engineer2, MSGBOX_NPC
	end

Route9_PokemonCenter_Text_Engineer1:
	.string "A veces los ingenieros venimos aquí\n"
	.string "en el descanso. O solo para huir\l"
	.string "de nuestro GERENTE.\p"
	.string "Ese tipo está loco.$"

Route9_PokemonCenter_Text_Engineer2:
	.string "La CENTRAL ELÉCTRICA es remota, así\n"
	.string "que viajo lejos por trabajo.$"
