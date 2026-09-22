CeladonCity_Gym_Frlg_MapScripts::
	.byte 0

CeladonCity_Gym_EventScript_Erika::
	famechecker FAMECHECKER_ERIKA, FCPICKSTATE_COLORED, UpdatePickStateFromSpecialVar8005
	trainerbattle_single TRAINER_LEADER_ERIKA, CeladonCity_Gym_Text_ErikaIntro, CeladonCity_Gym_Text_ErikaDefeat, CeladonCity_Gym_EventScript_DefeatedErika, NO_MUSIC
	goto_if_unset FLAG_GOT_TM19_FROM_ERIKA, CeladonCity_Gym_EventScript_GiveTM19
	famechecker FAMECHECKER_ERIKA, 4
	msgbox CeladonCity_Gym_Text_ErikaPostBattle
	release
	end

CeladonCity_Gym_EventScript_DefeatedErika::
	famechecker FAMECHECKER_ERIKA, 1
	clearflag FLAG_HIDE_FAME_CHECKER_ERIKA_JOURNALS
	setflag FLAG_DEFEATED_ERIKA
	setflag FLAG_BADGE04_GET
	set_gym_trainers_frlg 4
	goto CeladonCity_Gym_EventScript_GiveTM19
	end

CeladonCity_Gym_EventScript_GiveTM19::
	msgbox CeladonCity_Gym_Text_ExplainRainbowBadgeTakeThis
	checkitemspace ITEM_TM19
	goto_if_eq VAR_RESULT, FALSE, CeladonCity_Gym_EventScript_NoRoomForTM19
	giveitem_msg CeladonCity_Gym_Text_ReceivedTM19FromErika, ITEM_TM19
	setflag FLAG_GOT_TM19_FROM_ERIKA
	msgbox CeladonCity_Gym_Text_ExplainTM19
	release
	end

CeladonCity_Gym_EventScript_NoRoomForTM19::
	msgbox CeladonCity_Gym_Text_ShouldMakeRoomForThis
	release
	end

CeladonCity_Gym_EventScript_Kay::
	trainerbattle_single TRAINER_LASS_KAY, CeladonCity_Gym_Text_KayIntro, CeladonCity_Gym_Text_KayDefeat
	msgbox CeladonCity_Gym_Text_KayPostBattle, MSGBOX_AUTOCLOSE
	end

CeladonCity_Gym_EventScript_Lisa::
	trainerbattle_single TRAINER_LASS_LISA, CeladonCity_Gym_Text_LisaIntro, CeladonCity_Gym_Text_LisaDefeat
	famechecker FAMECHECKER_ERIKA, 2
	msgbox CeladonCity_Gym_Text_LisaPostBattle, MSGBOX_AUTOCLOSE
	end

CeladonCity_Gym_EventScript_Tina::
	trainerbattle_single TRAINER_PICNICKER_TINA, CeladonCity_Gym_Text_TinaIntro, CeladonCity_Gym_Text_TinaDefeat
	msgbox CeladonCity_Gym_Text_TinaPostBattle, MSGBOX_AUTOCLOSE
	end

CeladonCity_Gym_EventScript_Bridget::
	trainerbattle_single TRAINER_BEAUTY_BRIDGET, CeladonCity_Gym_Text_BridgetIntro, CeladonCity_Gym_Text_BridgetDefeat
	msgbox CeladonCity_Gym_Text_BridgetPostBattle, MSGBOX_AUTOCLOSE
	end

CeladonCity_Gym_EventScript_Tamia::
	trainerbattle_single TRAINER_BEAUTY_TAMIA, CeladonCity_Gym_Text_TamiaIntro, CeladonCity_Gym_Text_TamiaDefeat
	famechecker FAMECHECKER_ERIKA, 3
	msgbox CeladonCity_Gym_Text_TamiaPostBattle, MSGBOX_AUTOCLOSE
	end

CeladonCity_Gym_EventScript_Lori::
	trainerbattle_single TRAINER_BEAUTY_LORI, CeladonCity_Gym_Text_LoriIntro, CeladonCity_Gym_Text_LoriDefeat
	msgbox CeladonCity_Gym_Text_LoriPostBattle, MSGBOX_AUTOCLOSE
	end

CeladonCity_Gym_EventScript_Mary::
	trainerbattle_single TRAINER_COOLTRAINER_MARY, CeladonCity_Gym_Text_MaryIntro, CeladonCity_Gym_Text_MaryDefeat
	msgbox CeladonCity_Gym_Text_MaryPostBattle, MSGBOX_AUTOCLOSE
	end

CeladonCity_Gym_EventScript_GymStatue::
	lockall
	goto_if_set FLAG_BADGE04_GET, CeladonCity_Gym_EventScript_GymStatuePostVictory
	msgbox CeladonCity_Gym_Text_GymStatue
	releaseall
	end

CeladonCity_Gym_EventScript_GymStatuePostVictory::
	msgbox CeladonCity_Gym_Text_GymStatuePlayerWon
	releaseall
	end

CeladonCity_Gym_Text_ErikaIntro::
	.string "Hello…\n"
	.string "Hace un día precioso, ¿verdad?\l"
	.string "Es tan agradable…\p"
	.string "…Oh, dear…\n"
	.string "Debí quedarme dormido. Bienvenido.\p"
	.string "Me llamo ERIKA.\n"
	.string "Soy la LÍDER del GIMNASIO CELESTE.\p"
	.string "Soy un estudiante del arte de\n"
	.string "el arreglo floral.\p"
	.string "Mis POKéMON son únicamente de\n"
	.string "GRASS type.\p"
	.string "…Oh, lo siento, no tenía idea de que\n"
	.string "querías retarme.\p"
	.string "Muy bien, pero no perderé.{PLAY_BGM MUS_RG_ENCOUNTER_GYM_LEADER}$"

CeladonCity_Gym_Text_ErikaDefeat::
	.string "Oh!\n"
	.string "I concede defeat.\l"
	.string "Eres notablemente fuerte.\p"
	.string "Debo conferirte el\n"
	.string "MEDALLA ARCOÍRIS.$"

CeladonCity_Gym_Text_ErikaPostBattle::
	.string "You are cataloging POKéMON?\n"
	.string "I must say I'm impressed.\p"
	.string "I would never collect POKéMON if\n"
	.string "no fueran atractivos.$"

CeladonCity_Gym_Text_ExplainRainbowBadgeTakeThis::
	.string "La MEDALLA ARCOÍRIS hará\n"
	.string "POKéMON up to Lv. 50 obey.\p"
	.string "It also allows POKéMON to use\n"
	.string "Fuerza en y fuera de combate.\p"
	.string "Por favor, llévate también esto.$"

CeladonCity_Gym_Text_ReceivedTM19FromErika::
	.string "{PLAYER} received TM19\n"
	.string "de ERIKA.$"

CeladonCity_Gym_Text_ExplainTM19::
	.string "TM19 contains GIGA DRAIN.\p"
	.string "La mitad del daño que inflige es\n"
	.string "drained to heal your POKéMON.\p"
	.string "¿No crees que es un\n"
	.string "wonderful move?$"

CeladonCity_Gym_Text_ShouldMakeRoomForThis::
	.string "Deberías hacer espacio para esto.$"

CeladonCity_Gym_Text_KayIntro::
	.string "Debería contarte sobre este GIMNASIO.\p"
	.string "Solo las verdaderas damas pueden entrar\n"
	.string "¡Aquí!$"

CeladonCity_Gym_Text_KayDefeat::
	.string "¡Eres muy brusco!"

CeladonCity_Gym_Text_KayPostBattle::
	.string "Bleaah!\n"
	.string "Espero que ERIKA te elimine$"

CeladonCity_Gym_Text_BridgetIntro::
	.string "Oh, welcome.\n"
	.string "Me estaba aburriendo.$"

CeladonCity_Gym_Text_BridgetDefeat::
	.string "¡Mi maquillaje!$"

CeladonCity_Gym_Text_BridgetPostBattle::
	.string "GRASS-type POKéMON are tough\n"
	.string "contra el tipo AGUA.\p"
	.string "También tienen ventaja contra ROCA-\n"
	.string "and GROUND-type POKéMON.$"

CeladonCity_Gym_Text_TinaIntro::
	.string "…¿No estabas espiando aquí\n"
	.string "earlier?$"

CeladonCity_Gym_Text_TinaDefeat::
	.string "¡Eres toda una revelación!$"

CeladonCity_Gym_Text_TinaPostBattle::
	.string "Oh, estabas mirando a ERIKA…\n"
	.string "No me mirabas…$"

CeladonCity_Gym_Text_TamiaIntro::
	.string "Look, look!\n"
	.string "See my POKéMON!\p"
	.string "Me gusta el tipo PLANTA.\n"
	.string "Me gusta que sean fáciles de criar.$"

CeladonCity_Gym_Text_TamiaDefeat::
	.string "¡No!$"

CeladonCity_Gym_Text_TamiaPostBattle::
	.string "We only use GRASS-type POKéMON at\n"
	.string "en nuestro GIMNASIO.\p"
	.string "¿Por qué? ¡También los usamos para\n"
	.string "hacer arreglos florales!$"

CeladonCity_Gym_Text_LisaIntro::
	.string "Oh, hey!\p"
	.string "No nos gustan los tipo Bicho ni Fuego\n"
	.string "POKéMON in here!$"

CeladonCity_Gym_Text_LisaDefeat::
	.string "Oh!\n"
	.string "¡Tú!$"

CeladonCity_Gym_Text_LisaPostBattle::
	.string "Nuestra LÍDER ERIKA podría ser callada,\n"
	.string "pero es famosa por aquí.$"

CeladonCity_Gym_Text_LoriIntro::
	.string "Mucho gusto.\n"
	.string "My hobby is POKéMON training.$"

CeladonCity_Gym_Text_LoriDefeat::
	.string "Oh!\n"
	.string "Splendid!$"

CeladonCity_Gym_Text_LoriPostBattle::
	.string "Tengo una cita a ciegas pronto.\n"
	.string "Tengo que aprender a ser educado,\l"
	.string "especialmente si tengo que combatir.$"

CeladonCity_Gym_Text_MaryIntro::
	.string "¡Bienvenido al GIMNASIO CELESTE!\p"
	.string "Más te vale no subestimar\n"
	.string "Las amables señoras aquí.$"

CeladonCity_Gym_Text_MaryDefeat::
	.string "Oh!\n"
	.string "Beaten!$"

CeladonCity_Gym_Text_MaryPostBattle::
	.string "I didn't bring my best POKéMON.\n"
	.string "Wait until next time!$"

CeladonCity_Gym_Text_GymStatue::
	.string "GIMNASIO POKéMON DE CIUDAD CELESTE\n"
	.string "LÍDER: ERIKA\p"
	.string "ENTRENADORES GANADORES:\n"
	.string "{RIVAL}$"

CeladonCity_Gym_Text_GymStatuePlayerWon::
	.string "GIMNASIO POKéMON DE CIUDAD CELESTE\n"
	.string "LÍDER: ERIKA\p"
	.string "ENTRENADORES GANADORES:\n"
	.string "{RIVAL}, {PLAYER}$"

