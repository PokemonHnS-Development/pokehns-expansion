Route2_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route2_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route2_OnTransition: 
	callnative SetTimeBasedEncounters
	end

Route2_EventScript_Sign::
	msgbox Route2_Text_Sign, MSGBOX_SIGN
	end

Route2_EventScript_CaveSign::
	msgbox Route2_Text_DiglettsCaveSign, MSGBOX_SIGN
	end

Route2_EventScript_Carbos::
    finditem ITEM_CARBOS
    end

Route2_EventScript_Nugget::
    finditem ITEM_NUGGET
    end

Route2_Text_RobRegister:
	.string "¡Dame tu número!$"

Route2_Text_RobRematchIntro:
	.string "¡Atrapé aún más bichos!\n"
	.string "¡Échales un vistazo!$"

Route2_Text_RobRematchDefeat:
	.string "¡Necesito mejores bichos!$"

Route2_Text_RobPostRematch:
	.string "Atrapé todo bicho de VIRIDIAN.\n"
	.string "¿Habrá un mejor BOSQUE en algún lado?$"

Route2_Text_BugCatcherRob_Seen:
	.string "Mis POKéMON bicho son duros. Prepárate\n"
	.string "para perder!$"

Route2_Text_BugCatcherRob_Beaten:
	.string "I was whipped…$"

Route2_Text_BugCatcherRob_AfterBattle:
	.string "Buscaré bichos más fuertes\n"
	.string "POKéMON.$"

Route2_Text_BugCatcherEd_Seen:
	.string "Si caminas por hierba alta en\n"
	.string "shorts, ¿te haces cortes y raspones?$"

Route2_Text_BugCatcherEd_Beaten:
	.string "Ouch, ouch, ouch!$"

Route2_Text_BugCatcherEd_AfterBattle:
	.string "¡Arderán mucho al ponerte un\n"
	.string "baño.$"

Route2_Text_BugCatcherDoug_Seen:
	.string "Why don't girls like bug POKéMON?$"

Route2_Text_BugCatcherDoug_Beaten:
	.string "No good!$"

Route2_Text_BugCatcherDoug_AfterBattle:
	.string "Los POKéMON bicho son como peluches\n"
	.string "cuando les aprietas la panza.\p"
	.string "¡Me encanta cómo se sienten!$"

Route2_Text_Sign:
	.string "RUTA 2\p"
	.string "CIUDAD VERIDIAN - CIUDAD PLATEADA$"

Route2_Text_DiglettsCaveSign:
	.string "DIGLETT'S CAVE$"

