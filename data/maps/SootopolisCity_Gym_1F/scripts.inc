SootopolisCity_Gym_1F_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, SootopolisCity_Gym_1F_OnFrame
	map_script MAP_SCRIPT_ON_RESUME, SootopolisCity_Gym_1F_OnResume
	map_script MAP_SCRIPT_ON_LOAD, SootopolisCity_Gym_1F_OnLoad
	map_script MAP_SCRIPT_ON_TRANSITION, SootopolisCity_Gym_1F_OnTransition
	.byte 0

SootopolisCity_Gym_1F_OnTransition:
	setvar VAR_ICE_STEP_COUNT, 1
	end

SootopolisCity_Gym_1F_OnResume:
	setstepcallback STEP_CB_SOOTOPOLIS_ICE
	end

SootopolisCity_Gym_1F_OnLoad:
	call SootopolisCity_Gym_1F_EventScript_CheckSetStairMetatiles
	special SetSootopolisGymCrackedIceMetatiles
	end

SootopolisCity_Gym_1F_EventScript_CheckSetStairMetatiles::
	goto_if_lt VAR_ICE_STEP_COUNT, 8, SootopolisCity_Gym_1F_EventScript_StopCheckingStairs  @ All stairs ice
	goto_if_lt VAR_ICE_STEP_COUNT, 28, SootopolisCity_Gym_1F_EventScript_OpenFirstStairs
	goto_if_lt VAR_ICE_STEP_COUNT, 67, SootopolisCity_Gym_1F_EventScript_OpenFirstAndSecondStairs
	setmetatile 8, 4, METATILE_SootopolisGym_Stairs, FALSE
	setmetatile 8, 5, METATILE_SootopolisGym_Stairs, FALSE
SootopolisCity_Gym_1F_EventScript_OpenFirstAndSecondStairs::
	setmetatile 8, 10, METATILE_SootopolisGym_Stairs, FALSE
	setmetatile 8, 11, METATILE_SootopolisGym_Stairs, FALSE
SootopolisCity_Gym_1F_EventScript_OpenFirstStairs::
	setmetatile 8, 15, METATILE_SootopolisGym_Stairs, FALSE
	setmetatile 8, 16, METATILE_SootopolisGym_Stairs, FALSE
SootopolisCity_Gym_1F_EventScript_StopCheckingStairs::
	return

SootopolisCity_Gym_1F_OnFrame:
	map_script_2 VAR_ICE_STEP_COUNT, 8, SootopolisCity_Gym_1F_EventScript_UnlockFirstStairs
	map_script_2 VAR_ICE_STEP_COUNT, 28, SootopolisCity_Gym_1F_EventScript_UnlockSecondStairs
	map_script_2 VAR_ICE_STEP_COUNT, 67, SootopolisCity_Gym_1F_EventScript_UnlockThirdStairs
	map_script_2 VAR_ICE_STEP_COUNT, 0, SootopolisCity_Gym_1F_EventScript_FallThroughIce
	.2byte 0

SootopolisCity_Gym_1F_EventScript_UnlockFirstStairs::
	addvar VAR_ICE_STEP_COUNT, 1
	delay 40
	playse SE_ICE_STAIRS
	call SootopolisCity_Gym_1F_EventScript_CheckSetStairMetatiles
	special DrawWholeMapView
	end

SootopolisCity_Gym_1F_EventScript_UnlockSecondStairs::
	addvar VAR_ICE_STEP_COUNT, 1
	delay 40
	playse SE_ICE_STAIRS
	call SootopolisCity_Gym_1F_EventScript_CheckSetStairMetatiles
	special DrawWholeMapView
	end

SootopolisCity_Gym_1F_EventScript_UnlockThirdStairs::
	addvar VAR_ICE_STEP_COUNT, 1
	delay 40
	playse SE_ICE_STAIRS
	call SootopolisCity_Gym_1F_EventScript_CheckSetStairMetatiles
	special DrawWholeMapView
	end

SootopolisCity_Gym_1F_EventScript_FallThroughIce::
	lockall
	delay 20
	applymovement LOCALID_PLAYER, SootopolisCity_Gym_1F_Movement_FallThroughIce
	waitmovement 0
	playse SE_FALL
	delay 60
	warphole MAP_SOOTOPOLIS_CITY_GYM_B1F
	waitstate
	end

SootopolisCity_Gym_1F_Movement_FallThroughIce:
	set_invisible
	step_end

SootopolisCity_Gym_1F_EventScript_Juan::
	trainerbattle_single TRAINER_JUAN_1, SootopolisCity_Gym_1F_Text_JuanIntro, SootopolisCity_Gym_1F_Text_JuanDefeat, SootopolisCity_Gym_1F_EventScript_JuanDefeated, NO_MUSIC
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, SootopolisCity_Gym_1F_EventScript_JuanRematch
	goto_if_unset FLAG_RECEIVED_TM_WATER_PULSE, SootopolisCity_Gym_1F_EventScript_GiveWaterPulse2
	goto_if_unset FLAG_BADGE06_GET, SootopolisCity_Gym_1F_EventScript_GoGetFortreeBadge
	msgbox SootopolisCity_Gym_1F_Text_JuanPostBattle, MSGBOX_DEFAULT
	release
	end

SootopolisCity_Gym_1F_EventScript_JuanDefeated::
	message SootopolisCity_Gym_1F_Text_ReceivedRainBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox SootopolisCity_Gym_1F_Text_ExplainRainBadgeTakeThis, MSGBOX_DEFAULT
	setflag FLAG_DEFEATED_SOOTOPOLIS_GYM
	setflag FLAG_BADGE08_GET
	setflag FLAG_HIDE_SOOTOPOLIS_CITY_RESIDENTS
	setflag FLAG_HIDE_SOOTOPOLIS_CITY_STEVEN
	setflag FLAG_HIDE_SOOTOPOLIS_CITY_WALLACE
	setvar VAR_SOOTOPOLIS_CITY_STATE, 6
	clearflag FLAG_HIDE_SOOTOPOLIS_CITY_MAN_1
	setvar VAR_0x8008, 8
	call Common_EventScript_SetGymTrainers
	call SootopolisCity_Gym_1F_EventScript_GiveWaterPulse
	closemessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox SootopolisCity_Gym_1F_Text_RegisteredJuan, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_JUAN_MATCH_CALL
	release
	end

SootopolisCity_Gym_1F_EventScript_GiveWaterPulse::
	giveitem ITEM_TM_WATER_PULSE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_BagIsFull
	msgbox SootopolisCity_Gym_1F_Text_ExplainWaterPulse, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM_WATER_PULSE
	return

SootopolisCity_Gym_1F_EventScript_GiveWaterPulse2::
	giveitem ITEM_TM_WATER_PULSE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	msgbox SootopolisCity_Gym_1F_Text_ExplainWaterPulse, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM_WATER_PULSE
	release
	end

SootopolisCity_Gym_1F_EventScript_GoGetFortreeBadge::
	msgbox SootopolisCity_Gym_1F_Text_GoGetFortreeBadge, MSGBOX_DEFAULT
	release
	end

SootopolisCity_Gym_1F_EventScript_JuanRematch::
	trainerbattle_rematch_double TRAINER_JUAN_1, SootopolisCity_Gym_1F_Text_JuanPreRematch, SootopolisCity_Gym_1F_Text_JuanRematchDefeat, SootopolisCity_Gym_1F_Text_JuanRematchNeedTwoMons
	msgbox SootopolisCity_Gym_1F_Text_JuanPostRematch, MSGBOX_AUTOCLOSE
	end

SootopolisCity_Gym_1F_EventScript_GymGuide::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_SOOTOPOLIS_GYM, SootopolisCity_Gym_1F_EventScript_GymGuidePostVictory
	msgbox SootopolisCity_Gym_1F_Text_GymGuideAdvice, MSGBOX_DEFAULT
	release
	end

SootopolisCity_Gym_1F_EventScript_GymGuidePostVictory::
	msgbox SootopolisCity_Gym_1F_Text_GymGuidePostVictory, MSGBOX_DEFAULT
	release
	end

SootopolisCity_Gym_1F_EventScript_LeftGymStatue::
	lockall
	goto_if_set FLAG_BADGE08_GET, SootopolisCity_Gym_1F_EventScript_GymStatueCertified
	goto SootopolisCity_Gym_1F_EventScript_GymStatue
	end

SootopolisCity_Gym_1F_EventScript_RightGymStatue::
	lockall
	goto_if_set FLAG_BADGE08_GET, SootopolisCity_Gym_1F_EventScript_GymStatueCertified
	goto SootopolisCity_Gym_1F_EventScript_GymStatue
	end

SootopolisCity_Gym_1F_EventScript_GymStatueCertified::
	msgbox SootopolisCity_Gym_1F_Text_GymStatueCertified, MSGBOX_DEFAULT
	releaseall
	end

SootopolisCity_Gym_1F_EventScript_GymStatue::
	msgbox SootopolisCity_Gym_1F_Text_GymStatue, MSGBOX_DEFAULT
	releaseall
	end

SootopolisCity_Gym_1F_Text_GymGuideAdvice:
	.string "¡Hola! ¿Cómo va todo, CAMPEÓN?\n"
	.string "CAMPEÓN {PLAYER}?\p"
	.string "JUAN, el LÍDER del GIMNASIO de\n"
	.string "CIUDAD ARRECIFE, es un maestro\p"
	.string "And, to get to JUAN, an icy floor\n"
	.string "de hielo frenará tu camino...\p"
	.string "Mira, lo siento, pero eso es todo\n"
	.string "el consejo que tengo para ti.\p"
	.string "El resto del camino, tendrás que\n"
	.string "¡Hazlo tú mismo!$"

SootopolisCity_Gym_1F_Text_GymGuidePostVictory:
	.string "¡Vaya! Venciste hasta a JUAN, quien\nsupuestamente era el mejor de\nHOENN!\p¡Bien! Mira tu TARJETA DE\nENTRENADOR.\pSi ya tienes todas las\nMEDALLAS,\n¡estás listo para la LIGA POKéMON!$"

SootopolisCity_Gym_1F_Text_JuanIntro:
	.string "Déjame preguntarte.\n"
	.string "¿Sabías esto?\l"
	.string "Ah, no debería ser tan reservado.\p"
	.string "Yo fui quien le enseñó a WALLACE\n"
	.string "todo lo que hay que saber de POKéMON.\p"
	.string "Una vez, dejé mi puesto como\n"
	.string "LÍDER del GIMNASIO.\p"
	.string "En mi lugar, le confié a WALLACE\n"
	.string "el GIMNASIO.\p"
	.string "Sin embargo, surgió un motivo\n"
	.string "para que yo regresara.\p"
	.string "Ah, pero basta de charla.\n"
	.string "Empecemos el combate, ¿te parece?\p"
	.string "Por favor, sé testigo de\n"
	.string "nuestro arte.\p"
	.string "¡Una gran ilusión de agua creada\n"
	.string "por POKéMON y por mí!$"

@ NOTE: This defeat text actually causes a buffer overflow. It's about 50 bytes too long for
@ the gDisplayedStringBattle buffer that it's put into, and it stomps all over the gBattleTextBuffs
@ after, as well as the otherwise unused array after that. One wonders if that's the reason for
@ the existence of that unused array of ints.
SootopolisCity_Gym_1F_Text_JuanDefeat:
	.string "¡Ahahaha, excelente!\n"
	.string "Muy bien, tú eres el ganador.\p"
	.string "Siento en ti el brillo radiante\n"
	.string "de una habilidad que todo vence.\p"
	.string "Pero, comparado conmigo o incluso\n"
	.string "con WALLACE, te falta elegancia.\p"
	.string "Tal vez debería darte un préstamo\n"
	.string "¿de mi ropa?\p"
	.string "… … … … … …\n"
	.string "… … … … … …\p"
	.string "¡Jajaja, solo bromeaba!\p"
	.string "En vez de mi ropa, te daré\n"
	.string "¡esto, la MEDALLA LLUVIA!$"

SootopolisCity_Gym_1F_Text_ReceivedRainBadge:
	.string "{PLAYER} recibió la MEDALLA LLUVIA\n"
	.string "de JUAN.$"

SootopolisCity_Gym_1F_Text_ExplainRainBadgeTakeThis:
	.string "Tener la MEDALLA LLUVIA asegura\n"
	.string "la obediencia total de tus POKéMON\l"
	.string "a cada una de tus órdenes.\p"
	.string "La MEDALLA LLUVIA también permite\n"
	.string "usar la MO CASCADA para subir\l"
	.string "paredes de agua cayendo.\p"
	.string "Y, para que nunca olvides la\n"
	.string "batalla que tuvimos, toma esto…$"

SootopolisCity_Gym_1F_Text_ExplainWaterPulse:
	.string "La MT que te he entregado\n"
	.string "contiene PULSO AGUA.\p"
	.string "Al usarlo, a veces confundirá al\n"
	.string "rival con ondas ultrasónicas.\p"
	.string "… … … … … …$"

SootopolisCity_Gym_1F_Text_RegisteredJuan:
	.string "LÍDER DE GIMNASIO JUAN registrado\n"
	.string "en el POKéNAV.$"

SootopolisCity_Gym_1F_Text_JuanPostBattle:
	.string "Los ENTRENADORES que tengan todas\n"
	.string "las MEDALLAS de HOENN deben ir\l"
	.string "hacia el destino final.\p"
	.string "La LIGA POKéMON.\p"
	.string "Viaja hasta los confines del este\n"
	.string "de HOENN, a la ISLA EVER GRANDE.\p"
	.string "Allí encontrarás la LIGA\n"
	.string "POKéMON.$"

SootopolisCity_Gym_1F_Text_GoGetFortreeBadge:
	.string "Solo queda una MEDALLA por\n"
	.string "obtener en HOENN.\p"
	.string "Si quieres desafiar la LIGA\n"
	.string "POKéMON, debes obtener la última\l"
	.string "MEDALLA del GIMNASIO de FORTREE.$"

SootopolisCity_Gym_1F_Text_GymStatue:
	.string "SOOTOPOLIS CITY POKéMON GYM$"

SootopolisCity_Gym_1F_Text_GymStatueCertified:
	.string "GIMNASIO POKéMON DE CIUDAD SOOTOPOLIS\p"
	.string "ENTRENADORES CERTIFICADOS DE JUAN:\n"
	.string "{PLAYER}$"

SootopolisCity_Gym_1F_Text_JuanPreRematch:
	.string "JUAN: Ah, este GIMNASIO volvió a su\n"
	.string "estado habitual de serenidad…\p"
	.string "Pero nuestro joven tifón ha vuelto\n"
	.string "¡para ponernos a prueba otra vez!\p"
	.string "¡Bueno, amigo, ciertamente!\p"
	.string "¡Estaré encantado de bailar contigo\n"
	.string "tantas veces como quieras!$"

SootopolisCity_Gym_1F_Text_JuanRematchDefeat:
	.string "¡Ahahaha, tú eres el ganador!\n"
	.string "¡Me has derrotado otra vez!$"

SootopolisCity_Gym_1F_Text_JuanPostRematch:
	.string "JUAN: Si te pidiera que fueras mi\n"
	.string "aprendiz, seguro que rechazarías.\p"
	.string "Me gustaría regalarte mi abrigo\n"
	.string "a ti.\p"
	.string "Pero, de nuevo, lo rechazarías.\n"
	.string "Imagino que así es.\p"
	.string "Y eso, amigo mío, es una señal\n"
	.string "de nobleza!$"

SootopolisCity_Gym_1F_Text_JuanRematchNeedTwoMons:
	.string "JUAN: Ah, este GIMNASIO volvió a su\n"
	.string "estado habitual de serenidad…\p"
	.string "Pero nuestro joven tifón ha vuelto\n"
	.string "¡para ponernos a prueba otra vez!\p"
	.string "¡Bueno, amigo, ciertamente!\n"
	.string "Estaré encantado de bailar contigo…\p"
	.string "Ah, no, no, no.\n"
	.string "Solo tienes un POKéMON contigo.\p"
	.string "Deseo que regreses con dos,\n"
	.string "o quizás más POKéMON, por favor.$"

