PewterCity_Gym_Frlg_MapScripts::
	.byte 0

PewterCity_Gym_EventScript_Brock::
	famechecker FAMECHECKER_BROCK, FCPICKSTATE_COLORED, UpdatePickStateFromSpecialVar8005
	trainerbattle_single TRAINER_LEADER_BROCK, PewterCity_Gym_Text_BrockIntro, PewterCity_Gym_Text_BrockDefeat, PewterCity_Gym_EventScript_DefeatedBrock, NO_MUSIC
	goto_if_unset FLAG_GOT_TM39_FROM_BROCK, PewterCity_Gym_EventScript_GiveTM39
	msgbox PewterCity_Gym_Text_BrockPostBattle
	release
	end

PewterCity_Gym_EventScript_DefeatedBrock::
	famechecker FAMECHECKER_BROCK, 1
	setflag FLAG_DEFEATED_BROCK
	setflag FLAG_BADGE01_GET
	setvar VAR_MAP_SCENE_PEWTER_CITY, 1
	setflag FLAG_HIDE_PEWTER_CITY_GYM_GUIDE
	clearflag FLAG_HIDE_PEWTER_CITY_RUNNING_SHOES_GUY
	set_gym_trainers_frlg 1
	goto PewterCity_Gym_EventScript_GiveTM39
	end

PewterCity_Gym_EventScript_GiveTM39::
	msgbox PewterCity_Gym_Text_TakeThisWithYou
	checkitemspace ITEM_TM39
	goto_if_eq VAR_RESULT, FALSE, PewterCity_Gym_EventScript_NoRoomForTM39
	giveitem_msg PewterCity_Gym_Text_ReceivedTM39FromBrock, ITEM_TM39
	setflag FLAG_GOT_TM39_FROM_BROCK
	msgbox PewterCity_Gym_Text_ExplainTM39
	release
	end

PewterCity_Gym_EventScript_NoRoomForTM39::
	msgbox PewterCity_Gym_Text_DontHaveRoomForThis
	release
	end

PewterCity_Gym_EventScript_Liam::
	trainerbattle_single TRAINER_CAMPER_LIAM, PewterCity_Gym_Text_LiamIntro, PewterCity_Gym_Text_LiamDefeat
	msgbox PewterCity_Gym_Text_LiamPostBattle, MSGBOX_AUTOCLOSE
	end

PewterCity_Gym_EventScript_GymGuy::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_BROCK, PewterCity_Gym_EventScript_GymGuyPostVictory
	msgbox PewterCity_Gym_Text_LetMeTakeYouToTheTop, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, PewterCity_Gym_EventScript_GymGuyTakeMeToTop
	goto_if_eq VAR_RESULT, NO, PewterCity_Gym_EventScript_GymGuyDontTakeMeToTop
	end

PewterCity_Gym_EventScript_GymGuyPostVictory::
	msgbox PewterCity_Gym_Text_YoureChampMaterial
	release
	end

PewterCity_Gym_EventScript_GymGuyTakeMeToTop::
	msgbox PewterCity_Gym_Text_LetsGetHappening
	goto PewterCity_Gym_EventScript_GymGuyAdvice
	end

PewterCity_Gym_EventScript_GymGuyDontTakeMeToTop::
	msgbox PewterCity_Gym_Text_ItsFreeLetsGetHappening
	goto PewterCity_Gym_EventScript_GymGuyAdvice
	end

PewterCity_Gym_EventScript_GymGuyAdvice::
	msgbox PewterCity_Gym_Text_TryDifferentPartyOrders
	release
	end

PewterCity_Gym_EventScript_GymStatue::
	lockall
	goto_if_set FLAG_BADGE01_GET, PewterCity_Gym_EventScript_GymStatuePostVictory
	msgbox PewterCity_Gym_Text_GymStatue
	releaseall
	end

PewterCity_Gym_EventScript_GymStatuePostVictory::
	msgbox PewterCity_Gym_Text_GymStatuePlayerWon
	releaseall
	end

PewterCity_Gym_Text_BrockIntro::
	.string "Así que estás aquí. Soy BROCK.\n"
	.string "Soy el LÍDER de PLATEADA.\p"
	.string "Mi voluntad de roca es evidente\n"
	.string "incluso en mis POKéMON.\p"
	.string "Mis POKéMON son duros como\n"
	.string "roca y tienen gran determinación.\p"
	.string "Así es, ¡todos mis POKéMON son\n"
	.string "¡en el tipo Roca!\p"
	.string "¡Jajaja! ¿Vas a desafiarme\n"
	.string "sabiendo que perderás?\p"
	.string "Ese es el honor de ENTRENADOR\n"
	.string "que te impulsa a desafiarme.\p"
	.string "¡Muy bien, entonces!\n"
	.string "¡Muéstrame lo mejor que tienes!{PLAY_BGM}{MUS_RG_ENCOUNTER_GYM_LEADER}$"

PewterCity_Gym_Text_BrockDefeat::
	.string "Te tuve por sentado, y por eso\n"
	.string "Perdí.\p"
	.string "Como prueba de tu victoria, te doy\n"
	.string "a ti esto... la MEDALLA ROCA\l"
	.string "oficial de la LIGA POKéMON.\p"
	.string "{FONT_NORMAL}{PLAYER} recibió la MEDALLA ROCA\n"
	.string "de BROCK!{PAUSE_MUSIC}{PLAY_BGM}{MUS_OBTAIN_BADGE}{PAUSE 0xFE}{PAUSE 0x56}{RESUME_MUSIC}\p"
	.string "{FONT_MALE}Con solo la MEDALLA ROCA\n"
	.string "tus POKéMON más poderosos.\p"
	.string "También permite usar el movimiento\n"
	.string "DESTELLO fuera de combate.\p"
	.string "Claro, un POKéMON debe saber el\n"
	.string "DESTELLO para usarlo.$"

PewterCity_Gym_Text_TakeThisWithYou::
	.string "¡Espera!\n"
	.string "Llévate esto contigo.$"

PewterCity_Gym_Text_ReceivedTM39FromBrock::
	.string "{PLAYER} recibió MT39\n"
	.string "de BROCK.$"

PewterCity_Gym_Text_ExplainTM39::
	.string "Una MT, Máquina Técnica, contiene un\n"
	.string "technique for POKéMON.\p"
	.string "Usar una MT enseña el movimiento que\n"
	.string "contains to a POKéMON.\p"
	.string "Una MT solo puede usarse una vez.\p"
	.string "Así que, al usar una, elige la\n"
	.string "POKéMON carefully.\p"
	.string "Bueno...\n"
	.string "La MT39 contiene TUMBA ROCA.\p"
	.string "Lanza rocas al rival y puede\n"
	.string "reduce su VELOCIDAD.$"

PewterCity_Gym_Text_BrockPostBattle::
	.string "Hay todo tipo de ENTRENADORES en\n"
	.string "este enorme mundo nuestro.\p"
	.string "Parece que tienes mucho talento\n"
	.string "POKéMON TRAINER.\p"
	.string "Así que te haré una propuesta.\p"
	.string "Ve al GIMNASIO de AZULONA y pon\n"
	.string "a prueba tus habilidades.$"

PewterCity_Gym_Text_DontHaveRoomForThis::
	.string "No tienes espacio para esto.$"

PewterCity_Gym_Text_LiamIntro::
	.string "¡Alto ahí, niño!\p"
	.string "Estás a diez mil años luz \n"
	.string "de enfrentar a BROCK!$"

PewterCity_Gym_Text_LiamDefeat::
	.string "¡Rayos!\p"
	.string "Un año luz no es tiempo...\n"
	.string "¡Mide la distancia!$"

PewterCity_Gym_Text_LiamPostBattle::
	.string "Estás bien buena.\n"
	.string "...Pero no tanto como ¡BROCK!$"

PewterCity_Gym_Text_LetMeTakeYouToTheTop::
	.string "¡Hola!\n"
	.string "¿Quieres soñar en grande?\p"
	.string "¿Te atreves a soñar con convertirte\n"
	.string "¿el campeón POKéMON?\p"
	.string "No soy ENTRENADOR, pero puedo\n"
	.string "aconsejarte para ganar.\p"
	.string "¡Te llevaré a la cima!$"

PewterCity_Gym_Text_LetsGetHappening::
	.string "¡Muy bien!\n"
	.string "¡Vamos a la acción!$"

PewterCity_Gym_Text_TryDifferentPartyOrders::
	.string "El primer POKéMON que sale en un\n"
	.string "combate es el de la izquierda de\p"
	.string "Al cambiar el orden de POKéMON,\n"
	.string "puedes obtener una ventaja.\p"
	.string "Prueba distintos órdenes para\n"
	.string "vencer al equipo rival.$"

PewterCity_Gym_Text_ItsFreeLetsGetHappening::
	.string "¡Es un servicio gratis!\n"
	.string "¡Vamos a la acción!$"

PewterCity_Gym_Text_YoureChampMaterial::
	.string "¡Tal como pensaba!\n"
	.string "¡Tienes madera de campeón!$"

PewterCity_Gym_Text_GymStatue::
	.string "GIMNASIO POKéMON DE PIEDRA\n"
	.string "LÍDER: BROCK\p"
	.string "ENTRENADORES GANADORES:\n"
	.string "{RIVAL}$"

PewterCity_Gym_Text_GymStatuePlayerWon::
	.string "GIMNASIO POKéMON DE PIEDRA\n"
	.string "LÍDER: BROCK\p"
	.string "ENTRENADORES GANADORES:\n"
	.string "{RIVAL}, {PLAYER}$"

