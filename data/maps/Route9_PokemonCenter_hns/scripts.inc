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
	.string "לפעמים אנחנו המהנדסים באים לכאן\n"
	.string "בהפסקה, או סתם כדי לברוח מהמנהל.\p"
	.string "הבחור הזה משוגע.$"

Route9_PokemonCenter_Text_Engineer2:
	.string "מפעל החשמל מרוחק מאוד, אז\n"
	.string "אני נוסע רחוק לעבודה.$"
