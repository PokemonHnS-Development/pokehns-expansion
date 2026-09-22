SaffronCity_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SaffronCity_EventScript_CityEnter
	.byte 0

SaffronCity_EventScript_CityEnter::
	setflag FLAG_VISITED_SAFFRON_CITY
	end

SaffronCity_Text_BaobaName:
	.string "BAOBA$"

SaffronCity_Text_Baoba:
	.string "GUARDABAOBA: ¡{PLAYER}!\p"
	.string "Soy el GUARDABAOBA.\p"
	.string "Llamo para decirte que la\n"
	.string "¡ZONA SAFARI se expandió otra vez!\p"
	.string "¡Al fin mi ZONA SAFARI es\n"
	.string "exactamente como la soñé!\p"
	.string "Recuerdas dónde está, ¿verdad?\p"
	.string "¡Al oeste de CIUDAD ORQUIDEA!\n"
	.string "¡Nos vemos pronto!$"

SaffronCity_EventScript_Lass1A::
	goto_if_set FLAG_RETURNED_MACHINE_PART, SaffronCity_EventScript_Lass1B
	msgbox SaffronCity_Text_Lass1, MSGBOX_NPC
	end

SaffronCity_EventScript_Lass1B::
	msgbox SaffronCity_Text_Lass1_ReturnedPart, MSGBOX_NPC
	end

SaffronCity_EventScript_Lass2::
	msgbox SaffronCity_Text_Lass2, MSGBOX_NPC
	end

SaffronCity_EventScript_PokefanM::
	goto_if_set FLAG_RETURNED_MACHINE_PART, SaffronCity_EventScript_PokefanM2
	msgbox SaffronCity_Text_PokefanM, MSGBOX_NPC
	end

SaffronCity_EventScript_PokefanM2::
	msgbox SaffronCity_Text_PokefanM_ReturnedPart, MSGBOX_NPC
	end

SaffronCity_EventScript_CooltrainerM::
	msgbox SaffronCity_Text_CooltrainerM, MSGBOX_NPC
	end

SaffronCity_EventScript_CooltrainerF::
	msgbox SaffronCity_Text_CooltrainerF, MSGBOX_NPC
	end

SaffronCity_EventScript_Fisher::
	goto_if_set FLAG_RETURNED_MACHINE_PART, SaffronCity_EventScript_Fisher2
	msgbox SaffronCity_Text_Fisher, MSGBOX_NPC
	end

SaffronCity_EventScript_Fisher2::
	msgbox SaffronCity_Text_Fisher_ReturnedPart, MSGBOX_NPC
	end

SaffronCity_EventScript_Youngster1::
	msgbox SaffronCity_Text_Youngster1, MSGBOX_NPC
	end

SaffronCity_EventScript_Youngster2::
	msgbox SaffronCity_Text_Youngster2, MSGBOX_NPC
	end
SaffronCity_EventScript_CitySign::
	msgbox SaffronCity_Text_Sign, MSGBOX_SIGN
	end

SaffronCity_EventScript_GymSign::
	msgbox SaffronCity_Text_GymSign, MSGBOX_SIGN
	end

SaffronCity_EventScript_DojoSign::
	msgbox SaffronCity_Text_FightingDojoSign, MSGBOX_SIGN
	end

SaffronCity_EventScript_SilphCoSign::
	msgbox SaffronCity_Text_SilphCoSign, MSGBOX_SIGN
	end

SaffronCity_EventScript_MrPsychicSign::
	msgbox SaffronCity_Text_MrPsychicHouseSign, MSGBOX_SIGN
	end

SaffronCity_EventScript_MagnetTrainSign::
	msgbox SaffronCity_Text_MagnetTrainStationSign, MSGBOX_SIGN
	end

SaffronCity_EventScript_Elli::
	msgbox SaffronCity_Text_Elli, MSGBOX_NPC
	end

SaffronCity_Text_Elli:
	.string "I love VULPIX! :D$"

SaffronCity_Text_Lass1:
	.string "Aquí vive una niña experta\nen imitar a la gente.\pIncluso imita a las personas\ncon las que conversa. Es confuso.$"

SaffronCity_Text_Lass1_ReturnedPart:
	.string "La chica IMITADORA se veía triste.\p"
	.string "Dijo que perdió su MUÑECA\n"
	.string "POKé favorita: CLEFAIRY.$"

SaffronCity_Text_PokefanM:
	.string "¿Vienes de JOHTO?\pPuedes volver a casa si el\nMAGNET TRAIN funciona.$"

SaffronCity_Text_PokefanM_ReturnedPart:
	.string "¿Vienes de JOHTO?\pPuedes volver a casa\nsubiendo al MAGNET TRAIN.$"

SaffronCity_Text_CooltrainerM:
	.string "Fui al GIMNASIO con ganas de\npelear contra entrenadores…\pResulta que entré al GIMNASIO\nabandonado de al lado.\pVaya, estaba muy avergonzado.$"

SaffronCity_Text_CooltrainerF:
	.string "Esta es SILPH CO., famosa por\n"
	.string "sus productos de POKéMON.\p"
	.string "Antes, el TEAM ROCKET quería\n"
	.string "la empresa por esa razón.$"

SaffronCity_Text_Fisher:
	.string "Masticando... Masticando...\p"
	.string "Oigo que hay graves problemas\n"
	.string "en la CENTRAL ELÉCTRICA.\p"
	.string "Masticando... Masticando...$"

SaffronCity_Text_Fisher_ReturnedPart:
	.string "Masticando... Masticando...\p"
	.string "Oigo que hubo graves problemas en\n"
	.string "la CENTRAL ELÉCTRICA.\p"
	.string "Masticando... ¡Ah, estoy lleno!$"

SaffronCity_Text_Youngster1:
	.string "Entrar en un callejón por primera\n"
	.string "me pone algo ansioso.$"

SaffronCity_Text_Youngster2:
	.string "Hay un lugar llamado SALÓN de\n"
	.string "CONCURSOS en VIRIDIAN donde se\l"
	.string "reúnen ENTRENADORES de todo lado.$"

SaffronCity_Text_Lass2:
	.string "Nuestra ciudad salió en un\n"
	.string "programa de radio.\p"
	.string "Es lindo oír elogios sobre tu\n"
	.string "ciudad, pero también da un poco\l"
	.string "de vergüenza.$"

SaffronCity_Text_Sign:
	.string "CIUDAD AZAFRÁN\p"
	.string "Brillante, Dorada Tierra Comercial$"

SaffronCity_Text_GymSign:
	.string "CIUDAD AZAFRÁN\n"
	.string "GIMNASIO POKéMON\l"
	.string "LÍDER: SABRINA\p"
	.string "¡El maestro de los POKéMON Psíquicos!$"

SaffronCity_Text_FightingDojoSign:
	.string "¡Bienvenidos todos!\n"
	.string "DOJO DE LUCHA$"

SaffronCity_Text_SilphCoSign:
	.string "SILPH CO.\n"
	.string "EDIFICIO DE OFICINAS$"

SaffronCity_Text_MrPsychicHouseSign:
	.string "DEL SR. PSÍQUICO\n"
	.string "LAVANDA$"

SaffronCity_Text_MagnetTrainStationSign:
	.string "CIUDAD AZAFRÁN\n"
	.string "ESTACIÓN DEL TREN MAGNÉTICO$"
