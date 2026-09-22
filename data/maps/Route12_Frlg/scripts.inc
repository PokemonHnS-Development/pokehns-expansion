Route12_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, Route12_OnResume
	.byte 0

Route12_OnResume::
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, Route12_EventScript_TryRemoveSnorlax
	end

Route12_EventScript_TryRemoveSnorlax::
	removeobject VAR_LAST_TALKED
	return

Route12_EventScript_Snorlax::
	lock
	faceplayer
	goto_if_unset FLAG_GOT_POKE_FLUTE, Route12_EventScript_SnorlaxNoPokeFlute
	msgbox Text_WantToUsePokeFlute, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Route12_EventScript_DontUsePokeFlute
	call EventScript_AwakenSnorlax
	setwildbattle SPECIES_SNORLAX, 30
	waitse
	playmoncry SPECIES_SNORLAX, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setflag FLAG_HIDE_ROUTE_12_SNORLAX
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	setflag FLAG_WOKE_UP_ROUTE_12_SNORLAX
	dowildbattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, Route12_EventScript_FoughtSnorlax
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, Route12_EventScript_FoughtSnorlax
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, Route12_EventScript_FoughtSnorlax
	release
	end

Route12_EventScript_DontUsePokeFlute::
	release
	end

Route12_EventScript_FoughtSnorlax::
	msgbox Text_SnorlaxReturnedToMountains
	release
	end

Route12_EventScript_SnorlaxNoPokeFlute::
	msgbox Route12_Text_MonSprawledOutInSlumber
	release
	end

Route12_EventScript_RouteSign::
	msgbox Route12_Text_RouteSign, MSGBOX_SIGN
	end

Route12_EventScript_FishingSign::
	msgbox Route12_Text_SportfishingArea, MSGBOX_SIGN
	end

Route12_Text_MonSprawledOutInSlumber::
	.string "A POKéMON is sprawled out in\n"
	.string "un sueño profundo y cómodo.$"

Text_SnorlaxWokeUp::
	.string "SNORLAX woke up!\p"
	.string "¡Atacó con furia enojada!$"

Text_SnorlaxReturnedToMountains::
	.string "SNORLAX calmed down.\n"
	.string "Bostezó muy fuerte…\l"
	.string "Y volvió a las montañas.$"

Text_WantToUsePokeFlute::
	.string "Want to use the POKé FLUTE?$"

Text_PlayedPokeFlute::
	.string "{PLAYER} played the POKé FLUTE.$"

Route12_Text_NedIntro::
	.string "¡Sí!\n"
	.string "¡Pican aquí!$"

Route12_Text_NedDefeat::
	.string "¡Tch!\n"
	.string "Solo uno pequeño…$"

Route12_Text_NedPostBattle::
	.string "¡Espera!\n"
	.string "¡Mi línea se atascó!$"

Route12_Text_ChipIntro::
	.string "Ten paciencia.\n"
	.string "Pescar es cuestión de paciencia.$"

Route12_Text_ChipDefeat::
	.string "¡Ese se escapó!$"

Route12_Text_ChipPostBattle::
	.string "Con una CAÑA mejor, podría pescar\n"
	.string "better POKéMON…$"

Route12_Text_JustinIntro::
	.string "Busco una PIEDRA LUNAR.\n"
	.string "¿Tú has encontrado una?$"

Route12_Text_JustinDefeat::
	.string "Oww!$"

Route12_Text_JustinPostBattle::
	.string "I could have made my POKéMON\n"
	.string "evolucionar con una PIEDRA LUNAR.\p"
	.string "Seguro habría ganado entonces.$"

Route12_Text_LucaIntro::
	.string "La electricidad es mi especialidad.\p"
	.string "No sé nada sobre los POKéMON\n"
	.string "del mar, sin embargo.$"

Route12_Text_LucaDefeat::
	.string "Unplugged!$"

Route12_Text_LucaPostBattle::
	.string "El agua conduce electricidad, así\n"
	.string "should zap sea POKéMON.$"

Route12_Text_HankIntro::
	.string "The FISHING FOOL versus POKéMON\n"
	.string "KID!$"

Route12_Text_HankDefeat::
	.string "Touch too much!$"

Route12_Text_HankPostBattle::
	.string "Supongo que uno es bueno en\n"
	.string "lo que le gusta.\p"
	.string "Well, you beat me at POKéMON,\n"
	.string "pero no me ganas pescando.$"

Route12_Text_ElliotIntro::
	.string "Amo pescar, no me malinterpretes.\p"
	.string "Pero sería mejor si también\ntuviera más"
	.string "work.$"

Route12_Text_ElliotDefeat::
	.string "No es fácil…$"

Route12_Text_ElliotPostBattle::
	.string "Está bien.\n"
	.string "Perder ya no me molesta.$"

Route12_Text_AndrewIntro::
	.string "¿Qué estás pescando?\p"
	.string "Nunca se sabe lo que se puede\n"
	.string "catch!$"

Route12_Text_AndrewDefeat::
	.string "¡Lo perdí!$"

Route12_Text_AndrewPostBattle::
	.string "¿Qué, MAGIKARP?\p"
	.string "Los atrapo todo el tiempo, claro.\n"
	.string "Pero son bien débiles.$"

Route12_Text_RouteSign::
	.string "ROUTE 12 \n"
	.string "Norte a LAVANDA$"

Route12_Text_SportfishingArea::
	.string "SPORTFISHING AREA$"

Route12_Text_JesIntro::
	.string "JES: Si gano, voy a\n"
	.string "proponerle matrimonio a GIA.$"

Route12_Text_JesDefeat::
	.string "JES: Oh, por favor, ¿por qué no\n"
	.string "nos dejaron ganar?$"

Route12_Text_JesPostBattle::
	.string "JES: Oh, GIA, perdóname,\n"
	.string "¡mi amor!$"

Route12_Text_JesNotEnoughMons::
	.string "JES: GIA y yo seremos\n"
	.string "together forever.\p"
	.string "No lucharemos a menos que\n"
	.string "two POKéMON of your own.$"

Route12_Text_GiaIntro::
	.string "GIA: Hey, JES…\p"
	.string "¡Si ganamos, te casarás conmigo!$"

Route12_Text_GiaDefeat::
	.string "GIA: Oh, but why?$"

Route12_Text_GiaPostBattle::
	.string "GIA: ¡JES, tonto!\n"
	.string "¡Lo arruinaste!$"

Route12_Text_GiaNotEnoughMons::
	.string "GIA: No soporto pelear\n"
	.string "sin mi JES.\p"
	.string "Don't you have one more POKéMON?$"
