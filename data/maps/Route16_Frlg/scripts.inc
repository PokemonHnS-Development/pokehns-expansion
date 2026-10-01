Route16_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, Route16_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, Route16_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, Route16_OnWarp
	.byte 0

Route16_OnResume::
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, Route16_EventScript_RemoveSnorlax
	end

Route16_EventScript_RemoveSnorlax::
	removeobject VAR_LAST_TALKED
	return

Route16_OnTransition::
	call_if_eq VAR_MAP_SCENE_ROUTE16, 1, Route16_OnTransitionCyclingRoad
	end

Route16_OnTransitionCyclingRoad::
	setflag FLAG_SYS_ON_CYCLING_ROAD
	return

Route16_OnWarp::
	map_script_2 VAR_MAP_SCENE_ROUTE16, 1, Route16_OnWarpCyclingRoad
	.2byte 0

Route16_OnWarpCyclingRoad::
	special ForcePlayerOntoBike
	end

Route16_EventScript_Snorlax::
	lock
	faceplayer
	goto_if_unset FLAG_GOT_POKE_FLUTE, Route16_EventScript_SnorlaxNoPokeFlute
	msgbox Text_WantToUsePokeFlute, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Route16_EventScript_DontUsePokeFlute
	call EventScript_AwakenSnorlax
	setwildbattle SPECIES_SNORLAX, 30
	waitse
	playmoncry SPECIES_SNORLAX, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setflag FLAG_HIDE_ROUTE_16_SNORLAX
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	dowildbattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, Route16_EventScript_FoughtSnorlax
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, Route16_EventScript_FoughtSnorlax
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, Route16_EventScript_FoughtSnorlax
	release
	end

Route16_EventScript_DontUsePokeFlute::
	release
	end

Route16_EventScript_FoughtSnorlax::
	msgbox Text_SnorlaxReturnedToMountains
	release
	end

Route16_EventScript_SnorlaxNoPokeFlute::
	msgbox Route16_Text_MonSprawledOutInSlumber
	release
	end

Route16_EventScript_CyclingRoadSign::
	msgbox Route16_Text_CyclingRoadSign, MSGBOX_SIGN
	end

Route16_EventScript_RouteSign::
	msgbox Route16_Text_RouteSign, MSGBOX_SIGN
	end

Route16_Text_LaoIntro::
	.string "¿Qué quieres?$"

Route16_Text_LaoDefeat::
	.string "¡No te atrevas a reír!$"

Route16_Text_LaoPostBattle::
	.string "Nos gusta quedarnos aquí.\n"
	.string "¿Qué te importa?$"

Route16_Text_KojiIntro::
	.string "¡Linda BICICLETA!\n"
	.string "¡Entrega eso!$"

Route16_Text_KojiDefeat::
	.string "¡KO!$"

Route16_Text_KojiPostBattle::
	.string "¡Olvídalo, quién quiere tu BICICLETA!$"

Route16_Text_LukeIntro::
	.string "¡Ven a jugar, ratoncito!$"

Route16_Text_LukeDefeat::
	.string "¡Rata maldita!$"

Route16_Text_LukePostBattle::
	.string "¡Odio perder!\n"
	.string "¡Fuera de mi vista!$"

Route16_Text_HideoIntro::
	.string "¡Oye, me empujaste!$"

Route16_Text_HideoDefeat::
	.string "¡Kabum!$"

Route16_Text_HideoPostBattle::
	.string "Siempre estaremos por aquí\n"
	.string "aunque no te guste.\p"
	.string "Puedes desviarte a AZULONA\n"
	.string "desde FUUCSIA por la costa.$"

Route16_Text_CamronIntro::
	.string "¡Tengo hambre y estoy de mal humor!\n"
	.string "¡Necesito un saco de boxeo!$"

Route16_Text_CamronDefeat::
	.string "¡Mal, mal, mal!$"

Route16_Text_CamronPostBattle::
	.string "Si voy a tener POKéMON, que\n"
	.string "igual pueden ser feroces.\p"
	.string "Los usaría para dejar a mis\n"
	.string "en pedazos.$"

Route16_Text_RubenIntro::
	.string "¡Hola!\n"
	.string "¡Vamos a divertirnos bien!$"

Route16_Text_RubenDefeat::
	.string "¡No me hagas enojarte!$"

Route16_Text_RubenPostBattle::
	.string "Me divierto molestando a la gente\n"
	.string "con mis apestosos POKéMON.\p"
	.string "Son geniales para asustar.\n"
	.string "Y además muerden.$"

Route16_Text_MonSprawledOutInSlumber::
	.string "Un POKéMON está tumbado en\n"
	.string "un sueño profundo y placentero.$"

Route16_Text_CyclingRoadSign::
	.string "¡Disfruta la pendiente!\n"
	.string "RUTA CICLISTA$"

Route16_Text_RouteSign::
	.string "RUTA 16\n"
	.string "CIUDAD CELADON - CIUDAD FUXIA$"

Route16_Text_JedIntro::
	.string "límites.\n"
	.string "demostramos!$"

Route16_Text_JedDefeat::
	.string "JED: ¡Oh, no!\n"
	.string "¡Mi amor me vio como un perdedor!$"

Route16_Text_JedPostBattle::
	.string "JED: Escucha, LEA.\n"
	.string "Debes fijarte menos en mí.$"

Route16_Text_JedNotEnoughMons::
	.string "JED: ¿Solo tienes un POKéMON?\n"
	.string "¿No hay amor en tu corazón?$"

Route16_Text_LeaIntro::
	.string "LEA: A veces, la intensidad de\n"
	.string "nuestro amor me asusta.$"

Route16_Text_LeaDefeat::
	.string "LEA: ¡Ohh! Pero JED se ve genial\n"
	.string "¡incluso en una derrota!$"

Route16_Text_LeaPostBattle::
	.string "LEA: Jeje, lo siento.\n"
	.string "JED es muy genial.$"

Route16_Text_LeaNotEnoughMons::
	.string "LEA: Oh, no tienes dos\n"
	.string "POKéMON contigo?\p"
	.string "¿No te sientes solo, o\n"
	.string "tu POKéMON?$"
