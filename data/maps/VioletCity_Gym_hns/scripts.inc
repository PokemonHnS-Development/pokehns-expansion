VioletCity_Gym_hns_MapScripts::
	.byte 0

VioletCity_Gym_EventScript_GymGuy::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_VIOLET_GYM, VioletCity_Gym_EventScript_GymGuy2
	msgbox VioletGym_Text_GymGuide_Intro, MSGBOX_DEFAULT
	closemessage
	release
	end
	
VioletCity_Gym_EventScript_GymGuy2::
	msgbox VioletGym_Text_GymGuide_Win, MSGBOX_DEFAULT
	release
	end	

VioletCity_Gym_EventScript_Rod::
	trainerbattle_single TRAINER_ROD_HNS, VioletGym_Text_BirdKeeperRod_Seen, VioletGym_Text_BirdKeeperRod_Beaten
	msgbox VioletGym_Text_BirdKeeperRod_After, MSGBOX_AUTOCLOSE
	end

VioletCity_Gym_EventScript_Abe::
	trainerbattle_single TRAINER_ABE_HNS, VioletGym_Text_BirdKeeperAbe_Seen, VioletGym_Text_BirdKeeperAbe_Beaten
	msgbox VioletGym_Text_BirdKeeperAbe_After, MSGBOX_AUTOCLOSE
	end

VioletCity_Gym_EventScript_Falkner::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_VIOLET_GYM, VioletCity_Gym_EventScript_Falkner_Defeated
	msgbox VioletGym_Text_Falkner_Intro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_FALKNER_1_HNS, VioletGym_Text_Falkner_WinLoss
	message VioletGym_Text_ReceivedZephyrBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox VioletGym_Text_Falkner_BadgeExplain, MSGBOX_DEFAULT
	setflag FLAG_BADGE01_GET
	setflag FLAG_DEFEATED_VIOLET_GYM
	addvar VAR_NUM_BADGES, 1
	setvar VAR_0x8008, 1
	call Common_EventScript_SetGymTrainers_hns
	giveitem ITEM_TM_ROOST
	msgbox VioletGym_Text_Falkner_TMExplain, MSGBOX_DEFAULT
	setvar VAR_VIOLET_CITY_STATE, 3
	setrespawn HEAL_LOCATION_VIOLET_CITY_HNS
	closemessage
	release
	end

VioletCity_Gym_EventScript_Falkner_Defeated::
	msgbox VioletGym_Text_Falkner_AfterFight, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletGym_Text_Falkner_Intro:
	.string "Soy FALKNER, el líder del\n"
	.string "GIMNASIO de CIUDAD MALVA!\p"
	.string "Dicen que puedes cortar las\n"
	.string "alas de los POKéMON VOLADOR\p"
	.string "con una descarga eléctrica...\n"
	.string "¡No permitiré tales insultos!\l"
	.string "exóticos POKéMON!\p"
	.string "¡Te mostraré el verdadero poder\n"
	.string "de los magníficos POKéMON ave!$"

VioletGym_Text_Falkner_WinLoss:
	.string "...¡Rayos! El ave favorita de papá\n"
	.string "POKéMON…\p"
	.string "Está bien. Toma esto.\p"
	.string "Es la insignia oficial de la\n"
	.string "LIGA POKéMON, la INSIGNIA CEFIRO.$"

VioletGym_Text_ReceivedZephyrBadge:
	.string "{PLAYER} recibió la MEDALLA CÉFIRO.$"

VioletGym_Text_Falkner_BadgeExplain:
	.string "La MEDALLA CÉFIRO sube el ATAQUE\n"
	.string "de los POKéMON.\p"
	.string "También permite que los POKéMON\n"
	.string "usen FLASH, si pueden aprenderlo.\l"
	.string "en cualquier momento.\p"
	.string "Toma, llévate esto también.$"

VioletGym_Text_Falkner_TMExplain:
	.string "Con una MT, un POKéMON podrá\n"
	.string "aprender un movimiento al instante.\p"
	.string "Esa MT contiene RESGUARDO.\p"
	.string "Restaura los PS hasta la mitad\n"
	.string "del máximo de tu POKéMON.\p"
	.string "En otras palabras, cura a tu\n"
	.string "POKéMON.$"

VioletGym_Text_Falkner_AfterFight:
	.string "Hay GIMNASIOS POKéMON en ciudades\n"
	.string "y pueblos más adelante.\p"
	.string "Deberías probar tu habilidad en\n"
	.string "estos GIMNASIOS.\p"
	.string "¡Entrenaré más duro para ser\n"
	.string "el mejor maestro de aves!$"

VioletGym_Text_Falkner_Rematch:
	.string "Felicidades por derrotar a\n"
	.string "¡el ALTO MANDO!\p"
	.string "He entrenado a mis\n"
	.string "POKéMON tipo VOLADOR aún más.\p"
	.string "¿Crees que puedes enfrentar el\n"
	.string "poder del cielo otra vez?$"

VioletGym_Text_Falkner_RematchLoss:
	.string "Vaya… Me ganaste otra vez.\p
Voy a entrenar más duro para\n
¡ser el mejor maestro de aves!$"

VioletGym_Text_BirdKeeperRod_Seen:
	.string "¡La palabra clave es valor!\p"
	.string "Aquí entrenan noche y día para\n"
	.string "ser maestros de POKéMON ave.\p"
	.string "¡Vamos!$"

VioletGym_Text_BirdKeeperRod_Beaten:
	.string "Gaaah!$"

VioletGym_Text_BirdKeeperRod_After:
	.string "¡Lo de FALKNER es en serio!\p
No te confíes solo porque\n
¡me ganaste!$"

VioletGym_Text_BirdKeeperAbe_Seen:
	.string "Veamos si eres lo bastante\n
bueno para retar a FALKNER!$"

VioletGym_Text_BirdKeeperAbe_Beaten:
	.string "¡No puede ser!$"

VioletGym_Text_BirdKeeperAbe_After:
	.string "Qué patético, perder contra\n
un entrenador novato…$"

VioletGym_Text_GymGuide_Intro:
	.string "¡Hola! ¿Qué pasa? No soy\n"
	.string "ENTRENADOR, ¡pero doy consejos!\p"
	.string "¡Créeme! Si tienes fe, el sueño\n"
	.string "de ser campeón se hará realidad.\p"
	.string "¿Crees? Entonces escucha.\p"
	.string "El as de FALKNER es un búho\n"
	.string "que ama comer BAYAS.\p"
	.string "Aunque no es el más fuerte,\n"
	.string "puede aguantar muchos golpes.\p"
	.string "Le haces daño con ataques de tipo\n"
	.string "ELÉCTRICO y ROCA, pero ten cuidado\l"
	.string "con Bofetón Lodo!\p"
	.string "Si quieres más ayuda, visita la\n"
	.string "ACADEMIA POKéMON.\p"
	.string "¡Los estudiantes de allí saben\n"
	.string "muchísimo!$"

VioletGym_Text_GymGuide_Win:
	.string "¡Buena batalla! Sigue así,\n
y serás el CAMPEÓN en un\l
¡abrir y cerrar de ojos!$"

VioletCity_Gym_EventScript_Statue::
	lock
	goto_if_set FLAG_DEFEATED_VIOLET_GYM, VioletCity_Gym_EventScript_Statue2
	msgbox VioletCity_Gym_Text_GymStatue, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_Gym_EventScript_Statue2::
	msgbox VioletCity_Gym_Text_GymStatueCertified, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_Gym_Text_GymStatue:
	.string "VIOLET CITY POKéMON GYM$"

VioletCity_Gym_Text_GymStatueCertified:
	.string "GIMNASIO POKéMON CIUDAD MALVA\p"
	.string "ENTRENADORES CERTIFICADOS DE FALKNER:\n"
	.string "{PLAYER}$"
