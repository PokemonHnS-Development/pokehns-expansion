RustboroCity_Gym_MapScripts::
	.byte 0

RustboroCity_Gym_EventScript_Roxanne::
	trainerbattle_single TRAINER_ROXANNE_1, RustboroCity_Gym_Text_RoxanneIntro, RustboroCity_Gym_Text_RoxanneDefeat, RustboroCity_Gym_EventScript_RoxanneDefeated, NO_MUSIC
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, RustboroCity_Gym_EventScript_RoxanneRematch
	goto_if_unset FLAG_RECEIVED_TM_ROCK_TOMB, RustboroCity_Gym_EventScript_GiveRockTomb
	msgbox RustboroCity_Gym_Text_RoxannePostBattle, MSGBOX_DEFAULT
	release
	end

RustboroCity_Gym_EventScript_RoxanneDefeated::
	message RustboroCity_Gym_Text_ReceivedStoneBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox RustboroCity_Gym_Text_StoneBadgeInfoTakeThis, MSGBOX_DEFAULT
	setflag FLAG_DEFEATED_RUSTBORO_GYM
	setflag FLAG_BADGE01_GET
	setvar VAR_RUSTBORO_CITY_STATE, 1
	addvar VAR_PETALBURG_GYM_STATE, 1
	setvar VAR_0x8008, 1
	call Common_EventScript_SetGymTrainers
	call_if_eq VAR_PETALBURG_GYM_STATE, 6, Common_EventScript_ReadyPetalburgGymForBattle
	goto RustboroCity_Gym_EventScript_GiveRockTomb
	end

RustboroCity_Gym_EventScript_GiveRockTomb::
	giveitem ITEM_TM_ROCK_TOMB
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_TM_ROCK_TOMB
	msgbox RustboroCity_Gym_Text_ExplainRockTomb, MSGBOX_DEFAULT
	release
	end

RustboroCity_Gym_EventScript_RoxanneRematch::
	trainerbattle_rematch_double TRAINER_ROXANNE_1, RustboroCity_Gym_Text_RoxannePreRematch, RustboroCity_Gym_Text_RoxanneRematchDefeat, RustboroCity_Gym_Text_RoxanneRematchNeedTwoMons
	msgbox RustboroCity_Gym_Text_RoxannePostRematch, MSGBOX_AUTOCLOSE
	end

RustboroCity_Gym_EventScript_Josh::
	trainerbattle_single TRAINER_JOSH, RustboroCity_Gym_Text_JoshIntro, RustboroCity_Gym_Text_JoshDefeat
	msgbox RustboroCity_Gym_Text_JoshPostBattle, MSGBOX_AUTOCLOSE
	end

RustboroCity_Gym_EventScript_Tommy::
	trainerbattle_single TRAINER_TOMMY, RustboroCity_Gym_Text_TommyIntro, RustboroCity_Gym_Text_TommyDefeat
	msgbox RustboroCity_Gym_Text_TommyPostBattle, MSGBOX_AUTOCLOSE
	end

RustboroCity_Gym_EventScript_Marc::
	trainerbattle_single TRAINER_MARC, RustboroCity_Gym_Text_MarcIntro, RustboroCity_Gym_Text_MarcDefeat
	msgbox RustboroCity_Gym_Text_MarcPostBattle, MSGBOX_AUTOCLOSE
	end

RustboroCity_Gym_EventScript_GymGuide::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_RUSTBORO_GYM, RustboroCity_Gym_EventScript_GymGuidePostVictory
	msgbox RustboroCity_Gym_Text_GymGuideAdvice, MSGBOX_DEFAULT
	release
	end

RustboroCity_Gym_EventScript_GymGuidePostVictory::
	msgbox RustboroCity_Gym_Text_GymGuidePostVictory, MSGBOX_DEFAULT
	release
	end

RustboroCity_Gym_EventScript_LeftGymStatue::
	lockall
	goto_if_set FLAG_BADGE01_GET, RustboroCity_Gym_EventScript_GymStatueCertified
	goto RustboroCity_Gym_EventScript_GymStatue
	end

RustboroCity_Gym_EventScript_RightGymStatue::
	lockall
	goto_if_set FLAG_BADGE01_GET, RustboroCity_Gym_EventScript_GymStatueCertified
	goto RustboroCity_Gym_EventScript_GymStatue
	end

RustboroCity_Gym_EventScript_GymStatueCertified::
	msgbox RustboroCity_Gym_Text_GymStatueCertified, MSGBOX_DEFAULT
	releaseall
	end

RustboroCity_Gym_EventScript_GymStatue::
	msgbox RustboroCity_Gym_Text_GymStatue, MSGBOX_DEFAULT
	releaseall
	end

RustboroCity_Gym_EventScript_RegisterRoxanne::
	lockall
	pokenavcall RustboroCity_Gym_Text_RoxanneRegisterCall
	waitmessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox RustboroCity_Gym_Text_RegisteredRoxanne, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_ROXANNE_MATCH_CALL
	clearflag FLAG_ENABLE_ROXANNE_FIRST_CALL
	releaseall
	end

RustboroCity_Gym_Text_GymGuideAdvice:
	.string "¡Hola! ¿Cómo va todo?\p"
	.string "¡Escucha, amigo!\n"
	.string "¿Quieres ser el CAMPEÓN?\p"
	.string "No soy ENTRENADOR, pero puedo\n"
	.string "darte consejos para ganar.\p"
	.string "¡Trato hecho! ¡Iremos juntos por el\n"
	.string "CAMPEONATO POKéMON!\p"
	.string "Tu trabajo como ENTRENADOR es reunir\n"
	.string "MEDALLAS de GIMNASIO, ¿verdad?\p"
	.string "¡Pero los LÍDERES no son fáciles!\p"
	.string "¡Y ahí es donde entro yo!\n"
	.string "¡Estoy aquí para darte consejos!\p"
	.string "ROXANNE, la LÍDER del GIMNASIO, usa\n"
	.string "POKéMON tipo ROCA.\p"
	.string "El tipo ROCA es muy resistente, pero\n"
	.string "no soporta los movimientos de tipo\l"
	.string "AGUA y PLANTA.\p"
	.string "Ven a verme después, si vences al\n"
	.string "LÍDER del GIMNASIO.\p"
	.string "¡Bueno, ve a por ello!$"

RustboroCity_Gym_Text_GymGuidePostVictory:
	.string "¡Vaya! ¡Qué victoria tan increíble!\n"
	.string "¡Mis ánimos debieron funcionar!\p"
	.string "¡Genial!\n"
	.string "Revisa tu TARJETA de ENTRENADOR.\p"
	.string "La MEDALLA ROCA que ganaste debe\n"
	.string "está registrado correctamente.\p"
	.string "En otras palabras...\p"
	.string "¡Has subido el primer escalón\n"
	.string "hacia el CAMPEONATO!\p"
	.string "¡Eso debe sentirse genial!$"

RustboroCity_Gym_Text_JoshIntro:
	.string "¡No subestimes a los ENTRENADORES\n"
	.string "¡Te mostraré por qué somos mejores!$"

RustboroCity_Gym_Text_JoshDefeat:
	.string "Fuiste demasiado bueno para mí...$"

RustboroCity_Gym_Text_JoshPostBattle:
	.string "¡Aún no has visto el terrorífico\n"
	.string "poder del tipo ROCA!$"

RustboroCity_Gym_Text_TommyIntro:
	.string "Si no puedes vencerme, no tendrás\n"
	.string "oportunidad contra ROXANNE!$"

RustboroCity_Gym_Text_TommyDefeat:
	.string "¡Vaya! ¡Tienes potencial!$"

RustboroCity_Gym_Text_TommyPostBattle:
	.string "ROXANNE es mucho más fuerte que\n"
	.string "yo.\p"
	.string "¡Más vale que estés alerta!$"

RustboroCity_Gym_Text_MarcIntro:
	.string "Puede que estemos en el pueblo,\n"
	.string "¡pero qué importa!\p"
	.string "¡Mis POKéMON roca necesitan espacio\n"
	.string "para arrasar!$"

RustboroCity_Gym_Text_MarcDefeat:
	.string "¡Cielos, cielos!\n"
	.string "¡Este retador es muy aguerrido!$"

RustboroCity_Gym_Text_MarcPostBattle:
	.string "Debo reconocerlo con nuestra LÍDER.\p"
	.string "Hizo falta astucia y sentido para\n"
	.string "eligió el tipo ROCA siendo joven.$"

RustboroCity_Gym_Text_RoxanneIntro:
	.string "Hola, soy ROXANNE, la LÍDER del\n"
	.string "GIMNASIO de CIUDAD FUNDA.\p"
	.string "Soy LÍDER para poder aplicar lo que\n"
	.string "aprendí en la ESCUELA de\l"
	.string "ENTRENADORES POKéMON en batalla.\p"
	.string "¿Podrías mostrarme cómo luchas\n"
	.string "y con qué POKéMON?$"

RustboroCity_Gym_Text_RoxanneDefeat:
	.string "So...\n"
	.string "Perdí...\p"
	.string "Parece que todavía me queda mucho\n"
	.string "por aprender...\p"
	.string "Entiendo.\p"
	.string "Las reglas de la LIGA POKéMON dicen\n"
	.string "que los ENTRENADORES reciben esto\l"
	.string "si vencen a un LÍDER de GIMNASIO.\p"
	.string "Por favor, acepta la oficial\n"
	.string "MEDALLA DE PIEDRA de la LIGA.$"

RustboroCity_Gym_Text_ReceivedStoneBadge:
	.string "{PLAYER} recibió la MEDALLA DE\n"
	.string "PIEDRA de ROXANNE.$"

RustboroCity_Gym_Text_StoneBadgeInfoTakeThis:
	.string "La MEDALLA DE PIEDRA sube el ATAQUE\n"
	.string "de tus POKéMON.\p"
	.string "También permite usar el movimiento\n"
	.string "MO CORTE fuera de combate.\p"
	.string "Por favor, llévate esto también.$"

RustboroCity_Gym_Text_ExplainRockTomb:
	.string "Esa MT, la MT39,\n"
	.string "contiene Tumba Rocas.\p"
	.string "No solo hace daño al lanzar\n"
	.string "rocas, también baja la VELOCIDAD.\p"
	.string "Si usas una MT, le enseña el\n"
	.string "movimiento a un POKéMON al instante.\p"
	.string "Recuerda, una MT se usa solo una vez,\n"
	.string "así que piénsalo antes de usarla.$"

RustboroCity_Gym_Text_RoxannePostBattle:
	.string "Como eres tan fuerte, deberías\n"
	.string "retar a otros LÍDERES de GIMNASIO.\p"
	.string "Luchando contra muchos ENTRENADORES,\n"
	.string "aprenderás muchas cosas.$"

RustboroCity_Gym_Text_GymStatue:
	.string "GIMNASIO POKéMON DE PORTUAL$"

RustboroCity_Gym_Text_GymStatueCertified:
	.string "GIMNASIO POKéMON DE CIUDAD FUNDA\p"
	.string "ENTRENADORES CERTIFICADOS DE ROXANNE:\n"
	.string "{PLAYER}$"

RustboroCity_Gym_Text_RoxanneRegisterCall:
	.string "... ... ... ... ... ...\n"
	.string "... ... ... ... ... ¡Bip!\p"
	.string "ROXANNE: Oh, ¿hola, {PLAYER}?\n"
	.string "Soy ROXANNE de CIUDAD PORTALIA.\p"
	.string "BRAWLY me dijo que estás\n"
	.string "subiendo de rango entre los\l"
	.string "ENTRENADORES a un ritmo increíble.\p"
	.string "Bueno, prefiero no pensar que\n"
	.string "no puedo vencerte.\p"
	.string "Prometo mejorar mi GIMNASIO\n"
	.string "para que nos desafíes de nuevo.\p"
	.string "¡Espero que aguardes esa ocasión\n"
	.string "tanto como yo!\p"
	.string "... ... ... ... ... ...\n"
	.string "... ... ... ... ... ¡Click!$"

RustboroCity_Gym_Text_RegisteredRoxanne:
	.string "LÍDER de GIMNASIO ROXANNE registrada\n"
	.string "en el POKéNAV.$"

RustboroCity_Gym_Text_RoxannePreRematch:
	.string "ROXANNE: Me alegra verte de nuevo.\n"
	.string "Soy ROXANNE, la LÍDER del GIMNASIO.\p"
	.string "Seguro que ambos hemos tenido muchas\n"
	.string "batallas desde la última vez.\p"
	.string "Quiero ver cuánto hemos mejorado.\n"
	.string "¡Luchemos!$"

RustboroCity_Gym_Text_RoxanneRematchDefeat:
	.string "Grr...\n"
	.string "He perdido otra vez...$"

RustboroCity_Gym_Text_RoxannePostRematch:
	.string "ROXANNE: Aún me queda mucho por\n"
	.string "aprender sobre luchar con POKéMON.\p"
	.string "Saber eso me hace amar las batallas\n"
	.string "¡mucho más!$"

RustboroCity_Gym_Text_RoxanneRematchNeedTwoMons:
	.string "ROXANNE: Me alegra verte de nuevo.\n"
	.string "Soy ROXANNE, la LÍDER del GIMNASIO.\p"
	.string "Seguro que ambos hemos tenido muchas\n"
	.string "batallas desde la última vez.\p"
	.string "Quiero ver cuánto hemos mejorado.\n"
	.string "nos hemos vuelto...\p"
	.string "Oh, no...\n"
	.string "¿Solo traes un POKéMON contigo?\p"
	.string "Vuelve con al menos uno más\n"
	.string "POKéMON.$"
