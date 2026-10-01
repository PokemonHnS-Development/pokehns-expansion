FuchsiaCity_Gym_Frlg_MapScripts::
	.byte 0

FuchsiaCity_Gym_EventScript_Koga::
	famechecker FAMECHECKER_KOGA, FCPICKSTATE_COLORED, UpdatePickStateFromSpecialVar8005
	trainerbattle_single TRAINER_LEADER_KOGA, FuchsiaCity_Gym_Text_KogaIntro, FuchsiaCity_Gym_Text_KogaDefeat, FuchsiaCity_Gym_EventScript_DefeatedKoga, NO_MUSIC
	goto_if_unset FLAG_GOT_TM06_FROM_KOGA, FuchsiaCity_Gym_EventScript_GiveTM06
	msgbox FuchsiaCity_Gym_Text_KogaPostBattle
	release
	end

FuchsiaCity_Gym_EventScript_DefeatedKoga::
	famechecker FAMECHECKER_KOGA, 1
	clearflag FLAG_HIDE_FAME_CHECKER_KOGA_JOURNAL
	setflag FLAG_DEFEATED_KOGA
	setflag FLAG_BADGE05_GET
	set_gym_trainers_frlg 5
	goto FuchsiaCity_Gym_EventScript_GiveTM06
	end

FuchsiaCity_Gym_EventScript_GiveTM06::
	msgbox FuchsiaCity_Gym_Text_KogaExplainSoulBadge
	checkitemspace ITEM_TM06
	goto_if_eq VAR_RESULT, FALSE, FuchsiaCity_Gym_EventScript_NoRoomForTM06
	giveitem_msg FuchsiaCity_Gym_Text_ReceivedTM06FromKoga, ITEM_TM06
	setflag FLAG_GOT_TM06_FROM_KOGA
	msgbox FuchsiaCity_Gym_Text_KogaExplainTM06
	release
	end

FuchsiaCity_Gym_EventScript_NoRoomForTM06::
	msgbox FuchsiaCity_Gym_Text_MakeSpaceForThis
	release
	end

FuchsiaCity_Gym_EventScript_Phil::
	trainerbattle_single TRAINER_TAMER_PHIL, FuchsiaCity_Gym_Text_PhilIntro, FuchsiaCity_Gym_Text_PhilDefeat
	msgbox FuchsiaCity_Gym_Text_PhilPostBattle, MSGBOX_AUTOCLOSE
	end

FuchsiaCity_Gym_EventScript_Edgar::
	trainerbattle_single TRAINER_TAMER_EDGAR, FuchsiaCity_Gym_Text_EdgarIntro, FuchsiaCity_Gym_Text_EdgarDefeat
	msgbox FuchsiaCity_Gym_Text_EdgarPostBattle, MSGBOX_AUTOCLOSE
	end

FuchsiaCity_Gym_EventScript_Kirk::
	trainerbattle_single TRAINER_JUGGLER_KIRK, FuchsiaCity_Gym_Text_KirkIntro, FuchsiaCity_Gym_Text_KirkDefeat
	famechecker FAMECHECKER_KOGA, 2
	msgbox FuchsiaCity_Gym_Text_KirkPostBattle, MSGBOX_AUTOCLOSE
	end

FuchsiaCity_Gym_EventScript_Shawn::
	trainerbattle_single TRAINER_JUGGLER_SHAWN, FuchsiaCity_Gym_Text_ShawnIntro, FuchsiaCity_Gym_Text_ShawnDefeat
	msgbox FuchsiaCity_Gym_Text_ShawnPostBattle, MSGBOX_AUTOCLOSE
	end

FuchsiaCity_Gym_EventScript_Kayden::
	trainerbattle_single TRAINER_JUGGLER_KAYDEN, FuchsiaCity_Gym_Text_KaydenIntro, FuchsiaCity_Gym_Text_KaydenDefeat
	msgbox FuchsiaCity_Gym_Text_KaydenPostBattle, MSGBOX_AUTOCLOSE
	end

FuchsiaCity_Gym_EventScript_Nate::
	trainerbattle_single TRAINER_JUGGLER_NATE, FuchsiaCity_Gym_Text_NateIntro, FuchsiaCity_Gym_Text_NateDefeat
	msgbox FuchsiaCity_Gym_Text_NatePostBattle, MSGBOX_AUTOCLOSE
	end

FuchsiaCity_Gym_EventScript_GymGuy::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_KOGA, FuchsiaCity_Gym_EventScript_GymGuyPostVictory
	msgbox FuchsiaCity_Gym_Text_GymGuyAdvice
	release
	end

FuchsiaCity_Gym_EventScript_GymGuyPostVictory::
	msgbox FuchsiaCity_Gym_Text_GymGuyPostVictory
	release
	end

FuchsiaCity_Gym_EventScript_GymStatue::
	lockall
	goto_if_set FLAG_BADGE05_GET, FuchsiaCity_Gym_EventScript_GymStatuePostVictory
	msgbox FuchsiaCity_Gym_Text_GymStatue
	releaseall
	end

FuchsiaCity_Gym_EventScript_GymStatuePostVictory::
	msgbox FuchsiaCity_Gym_Text_GymStatuePlayerWon
	releaseall
	end

FuchsiaCity_Gym_Text_KogaIntro::
	.string "KOGA: ¡Jajajaja!\p"
	.string "¿Un niño como tú se atreve a\n"
	.string "desafiarme?\p"
	.string "La sola idea me hace estremecer\n"
	.string "de risa!\p"
	.string "Muy bien, te mostraré el verdadero\n"
	.string "terror como maestro ninja.\p"
	.string "El veneno trae una muerte lenta.\n"
	.string "El sueño los deja indefensos.\p"
	.string "Desesperad ante el horror\n"
	.string "¡de los POKéMON de tipo VENENO!{PLAY_BGM}{MUS_RG_ENCOUNTER_GYM_LEADER}$"

FuchsiaCity_Gym_Text_KogaDefeat::
	.string "¡Hmph!\n"
	.string "¡Has demostrado tu valor!\p"
	.string "¡Toma!\n"
	.string "¡Toma la MEDALLA ALMA!$"

FuchsiaCity_Gym_Text_KogaPostBattle::
	.string "Cuando un POKéMON sufre de TÓXICO,\n"
	.string "sufre cada vez más.\p"
	.string "Sufre un daño cada vez mayor\n"
	.string "mientras avanza la batalla!\p"
	.string "¡Aterrorizará a sus enemigos!$"

FuchsiaCity_Gym_Text_KogaExplainSoulBadge::
	.string "Ahora que tienes la MEDALLA\nALMA,"
	.string "la DEFENSA de tus POKéMON aumenta.\p"
	.string "También te permite usar SURF fuera de\n"
	.string "fantástica.\p"
	.string "Ah!\n"
	.string "¡Toma esto también!$"

FuchsiaCity_Gym_Text_ReceivedTM06FromKoga::
	.string "{PLAYER} received TM06\n"
	.string "de KOGA.$"

FuchsiaCity_Gym_Text_KogaExplainTM06::
	.string "Sellada en esa MT06 hay\n"
	.string "¡TÓXICO!\p"
	.string "Es una técnica secreta que data\n"
	.string "de hace unos cuatrocientos años.$"

FuchsiaCity_Gym_Text_MakeSpaceForThis::
	.string "¡Hazte a un lado, niño!$"

FuchsiaCity_Gym_Text_KaydenIntro::
	.string "La fuerza no es la clave para los POKéMON.\n"
	.string "¿Entiendes esto?\p"
	.string "¡Los POKéMON son estrategia!\p"
	.string "Te mostraré cómo la estrategia\n"
	.string "vence a la fuerza bruta.$"

FuchsiaCity_Gym_Text_KaydenDefeat::
	.string "¿Qué?\n"
	.string "Extraordinary!$"

FuchsiaCity_Gym_Text_KaydenPostBattle::
	.string "¿Mezclas fuerza con inteligencia?\n"
	.string "¡Buena estrategia!\p"
	.string "Eso es notable para un niño\n"
	.string "ENTRENADOR.$"

FuchsiaCity_Gym_Text_KirkIntro::
	.string "Fui mago hace mucho tiempo.\p"
	.string "Pero soñaba con ser ninja,\n"
	.string "así que entré a este GYM.$"

FuchsiaCity_Gym_Text_KirkDefeat::
	.string "¡Estoy acabado!$"

FuchsiaCity_Gym_Text_KirkPostBattle::
	.string "Aunque he perdido, seguiré\n"
	.string "entrenando según las enseñanzas\l"
	.string "de KOGA, mi maestro ninja.$"

FuchsiaCity_Gym_Text_NateIntro::
	.string "Ve si puedes vencer mi especial\n"
	.string "techniques!$"

FuchsiaCity_Gym_Text_NateDefeat::
	.string "¡Me engañaste!$"

FuchsiaCity_Gym_Text_NatePostBattle::
	.string "Me gustan las técnicas de veneno\n"
	.string "y sueño, ¡siguen tras la batalla!$"

FuchsiaCity_Gym_Text_PhilIntro::
	.string "¡Detente ahí!\p"
	.string "Las famosas paredes invisibles\n"
	.string "del GIMNASIO FUCSIA te frustran?$"

FuchsiaCity_Gym_Text_PhilDefeat::
	.string "¡Vaya!\n"
	.string "¡Lo lograste!$"

FuchsiaCity_Gym_Text_PhilPostBattle::
	.string "¡Me impresionaste!\n"
	.string "¡Aquí va una pista!\p"
	.string "Mira muy de cerca los huecos en la\n"
	.string "invisible walls!$"

FuchsiaCity_Gym_Text_EdgarIntro::
	.string "Yo también estudio el camino del\n"
	.string "con el Maestro KOGA!\p"
	.string "Los ninjas tienen una larga historia\n"
	.string "animals!$"

FuchsiaCity_Gym_Text_EdgarDefeat::
	.string "Awoo!$"

FuchsiaCity_Gym_Text_EdgarPostBattle::
	.string "Aún me queda mucho por aprender.$"

FuchsiaCity_Gym_Text_ShawnIntro::
	.string "El maestro KOGA proviene de una\n"
	.string "de ninjas.\p"
	.string "¿De qué desciendes?$"

FuchsiaCity_Gym_Text_ShawnDefeat::
	.string "Eres más hábil de lo que yo\n"
	.string "thought!$"

FuchsiaCity_Gym_Text_ShawnPostBattle::
	.string "Donde hay luz, también hay\n"
	.string "shadow!\p"
	.string "¡Luz y sombra!\n"
	.string "¿Cuál eliges tú?$"

FuchsiaCity_Gym_Text_GymGuyAdvice::
	.string "Yo!\n"
	.string "¡Un futuro campeón!\p"
	.string "El GIMNASIO FUCSIA está lleno\n"
	.string "de trucos.\p"
	.string "KOGA puede parecer cercano, pero\n"
	.string "no lograrás alcanzarlo.\p"
	.string "KOGA puede parecer cercano, pero\n"
	.string "bloqueado.$"

FuchsiaCity_Gym_Text_GymGuyPostVictory::
	.string "Es increíble cómo asustan los\nninja."
	.string "¡incluso ahora!$"

FuchsiaCity_Gym_Text_GymStatue::
	.string "GIMNASIO POKéMON DE Fucsia\n"
	.string "LEADER: KOGA\p"
	.string "ENTRENADORES GANADORES:\n"
	.string "{RIVAL}$"

FuchsiaCity_Gym_Text_GymStatuePlayerWon::
	.string "GIMNASIO POKéMON DE Fucsia\n"
	.string "LEADER: KOGA\p"
	.string "ENTRENADORES GANADORES:\n"
	.string "{RIVAL}, {PLAYER}$"

