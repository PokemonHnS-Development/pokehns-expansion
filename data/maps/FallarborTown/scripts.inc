FallarborTown_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, FallarborTown_OnTransition
	.byte 0

FallarborTown_OnTransition:
	setflag FLAG_VISITED_FALLARBOR_TOWN
	setvar VAR_CONTEST_HALL_STATE, 0
	clearflag FLAG_CONTEST_SKETCH_CREATED
	end

FallarborTown_EventScript_ExpertM::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_EVIL_TEAM_MT_CHIMNEY, FallarborTown_EventScript_ExpertMNormal
	msgbox FallarborTown_Text_ShadyCharactersCozmosHome, MSGBOX_DEFAULT
	release
	end

FallarborTown_EventScript_ExpertMNormal::
	msgbox FallarborTown_Text_RegionKnownForMeteors, MSGBOX_DEFAULT
	release
	end

FallarborTown_EventScript_Girl::
	msgbox FallarborTown_Text_MyPreciousAzurill, MSGBOX_NPC
	end

FallarborTown_EventScript_Gentleman::
	msgbox FallarborTown_Text_HaveYouChallengedFlannery, MSGBOX_NPC
	end

FallarborTown_EventScript_Azurill::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_AZURILL, CRY_MODE_NORMAL
	msgbox FallarborTown_Text_Azurill, MSGBOX_DEFAULT
	waitmoncry
	release
	end

FallarborTown_EventScript_BattleTentSign::
	msgbox FallarborTown_Text_BattleTentSign, MSGBOX_SIGN
	end

FallarborTown_EventScript_TownSign::
	msgbox FallarborTown_Text_TownSign, MSGBOX_SIGN
	end

FallarborTown_EventScript_MoveTutorSign::
	msgbox FallarborTown_Text_MoveTutorSign, MSGBOX_SIGN
	end

FallarborTown_Text_ShadyCharactersCozmosHome:
	.string "Algo está pasando,\n"
	.string "¡y no me gusta nada!\p"
	.string "He visto tipos sospechosos entrar\n"
	.string "y salir de casa del PROF. COZMO...$"

FallarborTown_Text_RegionKnownForMeteors:
	.string "Esta región es famosa por los\n"
	.string "meteoritos desde hace tiempo.\p"
	.string "Dicen que METEOR FALLS se formó\n"
	.string "por un meteorito hace mucho.$"

FallarborTown_Text_MyPreciousAzurill:
	.string "¡Mira! ¡Echa un vistazo!\n"
	.string "¡Este es mi querido AZURILL!\p"
	.string "¡Es brillante, suave y esponjoso!$"

FallarborTown_Text_Azurill:
	.string "AZURILL: Rooreelooo.$"

FallarborTown_Text_HaveYouChallengedFlannery:
	.string "¿Ya desafiaste a FLANNERY,\n"
	.string "¿el LÍDER del GIMNASIO LAVARIDGE?\p"
	.string "El abuelo de la chica era famoso.\n"
	.string "Fue uno de los cuatro ELITE FOUR en la\l"
	.string "LIGA POKéMON en algún momento.\p"
	.string "No me sorprendería que FLANNERY\n"
	.string "se vuelva una gran ENTRENADORA por\l"
	.string "sí misma.$"

FallarborTown_Text_BattleTentSign:
	.string "TIENDA BATALLA FALLARBOR\n"
	.string "¡Que se reúnan los mejores equipos!$"

FallarborTown_Text_TownSign:
	.string "PUEBLO FALLARBOR\n"
	.string "Comunidad agrícola con jardines.$"

FallarborTown_Text_MoveTutorSign:
	.string "CASA DEL TUTOR DE MOVIMIENTOS\n"
	.string "“Se enseñaron nuevos movimientos.”$"

