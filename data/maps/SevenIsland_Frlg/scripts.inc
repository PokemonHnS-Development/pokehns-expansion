SevenIsland_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SevenIsland_OnTransition
	.byte 0

SevenIsland_OnTransition::
	setworldmapflag FLAG_WORLD_MAP_SEVEN_ISLAND
	end

SevenIsland_EventScript_IslandSign::
	msgbox SevenIsland_Text_IslandSign, MSGBOX_SIGN
	end

SevenIsland_EventScript_OldWoman::
	msgbox SevenIsland_Text_IslandsMadeInSevenDays, MSGBOX_NPC
	end

SevenIsland_EventScript_Scientist::
	msgbox SevenIsland_Text_IslandVirtuallyUntouched, MSGBOX_NPC
	end

Text_SwordsDanceTeach::
	.string "Poca gente viene por aquí.\p"
	.string "If I train here, I'm convinced that\n"
	.string "me haré cada vez más fuerte.\p"
	.string "Sí, cada vez más fuerte...\p"
	.string "¿Cómo te gustaría aprender un\n"
	.string "movimiento así? Es DANZA ESPADA.$"

Text_SwordsDanceDeclined::
	.string "Bueno, también está bien.$"

Text_SwordsDanceWhichMon::
	.string "All right, pick which POKéMON\n"
	.string "Debería enseñárselo.$"

Text_SwordsDanceTaught::
	.string "Si tan solo pudiéramos seguir\n"
	.string "cada vez más fuerte, ¿eh?$"

SevenIsland_Text_IslandSign::
	.string "SEVEN ISLAND\n"
	.string "Isla del Infinito$"

SevenIsland_Text_IslandsMadeInSevenDays::
	.string "Estas islas se llaman las ISLAS\n"
	.string "SEVII porque son siete.\p"
	.string "...O al menos eso dicen los\n"
	.string "people believe.\p"
	.string "La verdad es que estas islas\n"
	.string "llevan ese nombre porque dicen\l"
	.string "que fueron creadas en 7 días.$"

SevenIsland_Text_IslandVirtuallyUntouched::
	.string "Esta isla se ha dejado casi\n"
	.string "intacta en su estado natural.\p"
	.string "Podría ser un poco difícil\n"
	.string "caminar por ahí por eso.$"

