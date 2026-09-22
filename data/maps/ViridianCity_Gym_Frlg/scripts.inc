ViridianCity_Gym_Frlg_MapScripts::
	.byte 0

ViridianCity_Gym_EventScript_Giovanni::
	famechecker FAMECHECKER_GIOVANNI, FCPICKSTATE_COLORED, UpdatePickStateFromSpecialVar8005
	trainerbattle_single TRAINER_LEADER_GIOVANNI, ViridianCity_Gym_Text_GiovanniIntro, ViridianCity_Gym_Text_GiovanniDefeat, ViridianCity_Gym_EventScript_DefeatedGiovanni, NO_MUSIC
	goto_if_unset FLAG_GOT_TM26_FROM_GIOVANNI, ViridianCity_Gym_EventScript_GiveTM26
	msgbox ViridianCity_Gym_Text_GiovanniPostBattle
	closemessage
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_VIRIDIAN_GIOVANNI
	fadescreen FADE_FROM_BLACK
	release
	end

ViridianCity_Gym_EventScript_DefeatedGiovanni::
	famechecker FAMECHECKER_GIOVANNI, 3
	setflag FLAG_HIDE_MISC_KANTO_ROCKETS
	setflag FLAG_DEFEATED_LEADER_GIOVANNI
	setflag FLAG_BADGE08_GET
	setvar VAR_MAP_SCENE_ROUTE22, 3
	set_gym_trainers_frlg 8
	goto ViridianCity_Gym_EventScript_GiveTM26
	end

ViridianCity_Gym_EventScript_GiveTM26::
	msgbox ViridianCity_Gym_Text_ExplainEarthBadgeTakeThis
	checkitemspace ITEM_TM26
	goto_if_eq VAR_RESULT, FALSE, ViridianCity_Gym_EventScript_NoRoomForTM26
	giveitem_msg ViridianCity_Gym_Text_ReceivedTM26FromGiovanni, ITEM_TM26
	setflag FLAG_GOT_TM26_FROM_GIOVANNI
	msgbox ViridianCity_Gym_Text_ExplainTM26
	release
	end

ViridianCity_Gym_EventScript_NoRoomForTM26::
	msgbox ViridianCity_Gym_Text_YouDoNotHaveSpace
	release
	end

ViridianCity_Gym_EventScript_Jason::
	trainerbattle_single TRAINER_TAMER_JASON, ViridianCity_Gym_Text_JasonIntro, ViridianCity_Gym_Text_JasonDefeat
	msgbox ViridianCity_Gym_Text_JasonPostBattle, MSGBOX_AUTOCLOSE
	end

ViridianCity_Gym_EventScript_Cole::
	trainerbattle_single TRAINER_TAMER_COLE, ViridianCity_Gym_Text_ColeIntro, ViridianCity_Gym_Text_ColeDefeat
	msgbox ViridianCity_Gym_Text_ColePostBattle, MSGBOX_AUTOCLOSE
	end

ViridianCity_Gym_EventScript_Atsushi::
	trainerbattle_single TRAINER_BLACK_BELT_ATSUSHI, ViridianCity_Gym_Text_AtsushiIntro, ViridianCity_Gym_Text_AtsushiDefeat
	msgbox ViridianCity_Gym_Text_AtsushiPostBattle, MSGBOX_AUTOCLOSE
	end

ViridianCity_Gym_EventScript_Kiyo::
	trainerbattle_single TRAINER_BLACK_BELT_KIYO, ViridianCity_Gym_Text_KiyoIntro, ViridianCity_Gym_Text_KiyoDefeat
	msgbox ViridianCity_Gym_Text_KiyoPostBattle, MSGBOX_AUTOCLOSE
	end

ViridianCity_Gym_EventScript_Takashi::
	trainerbattle_single TRAINER_BLACK_BELT_TAKASHI, ViridianCity_Gym_Text_TakashiIntro, ViridianCity_Gym_Text_TakashiDefeat
	msgbox ViridianCity_Gym_Text_TakashiPostBattle, MSGBOX_AUTOCLOSE
	end

ViridianCity_Gym_EventScript_Samuel::
	trainerbattle_single TRAINER_COOLTRAINER_SAMUEL, ViridianCity_Gym_Text_SamuelIntro, ViridianCity_Gym_Text_SamuelDefeat
	msgbox ViridianCity_Gym_Text_SamuelPostBattle, MSGBOX_AUTOCLOSE
	end

ViridianCity_Gym_EventScript_Yuji::
	trainerbattle_single TRAINER_COOLTRAINER_YUJI, ViridianCity_Gym_Text_YujiIntro, ViridianCity_Gym_Text_YujiDefeat
	msgbox ViridianCity_Gym_Text_YujiPostBattle, MSGBOX_AUTOCLOSE
	end

ViridianCity_Gym_EventScript_Warren::
	trainerbattle_single TRAINER_COOLTRAINER_WARREN, ViridianCity_Gym_Text_WarrenIntro, ViridianCity_Gym_Text_WarrenDefeat
	msgbox ViridianCity_Gym_Text_WarrenPostBattle, MSGBOX_AUTOCLOSE
	end

ViridianCity_Gym_EventScript_GymGuy::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_LEADER_GIOVANNI, ViridianCity_Gym_EventScript_GymGuyPostVictory
	msgbox ViridianCity_Gym_Text_GymGuyAdvice
	release
	end

ViridianCity_Gym_EventScript_GymGuyPostVictory::
	famechecker FAMECHECKER_GIOVANNI, 4
	msgbox ViridianCity_Gym_Text_GymGuyPostVictory
	release
	end

ViridianCity_Gym_EventScript_GymStatue::
	lockall
	goto_if_set FLAG_BADGE08_GET, ViridianCity_Gym_EventScript_GymStatuePostVictory
	msgbox ViridianCity_Gym_Text_GymStatue
	releaseall
	end

ViridianCity_Gym_EventScript_GymStatuePostVictory::
	msgbox ViridianCity_Gym_Text_GymStatuePlayerWon
	releaseall
	end

ViridianCity_Gym_Text_GiovanniIntro::
	.string "Fwahahaha!\n"
	.string "¡Bienvenido a mi escondite!\p"
	.string "Así será hasta que devuelva al\n"
	.string "TEAM ROCKET to its former glory.\p"
	.string "Pero me has encontrado otra vez.\n"
	.string "Así que sea.\l"
	.string "¡Esta vez no me contengo!\p"
	.string "Una vez más enfrentarás\n"
	.string "¡a GIOVANNI, el mejor ENTRENADOR!{PLAY_BGM}{MUS_RG_ENCOUNTER_ROCKET}$"

ViridianCity_Gym_Text_GiovanniDefeat::
	.string "Ha!\n"
	.string "Fue una pelea muy intensa.\l"
	.string "¡Has ganado!\p"
	.string "As proof, here is the MEDALLA TIERRA!\n"
	.string "{PAUSE_MUSIC}{PLAY_BGM}{MUS_OBTAIN_BADGE}{PAUSE 0xFE}{PAUSE 0x56}{RESUME_MUSIC}$"

ViridianCity_Gym_Text_GiovanniPostBattle::
	.string "Habiendo perdido así,\n"
	.string "I can't face my followers.\l"
	.string "He traicionado su confianza.\p"
	.string "As of today, TEAM ROCKET is\n"
	.string "finished forever!\p"
	.string "En cuanto a mí, dedicaré\n"
	.string "mi vida a entrenar de nuevo.\p"
	.string "¡Nos veremos algún día!\n"
	.string "¡Adiós!$"

ViridianCity_Gym_Text_ExplainEarthBadgeTakeThis::
	.string "The MEDALLA TIERRA makes POKéMON of\n"
	.string "any level obey without question.\p"
	.string "Es prueba de tu maestría como\n"
	.string "a POKéMON TRAINER.\p"
	.string "Con él puedes desafiar a\n"
	.string "POKéMON LEAGUE.\p"
	.string "Toma también esta MT.\p"
	.string "Consider it a gift for your POKéMON\n"
	.string "LEAGUE challenge.$"

ViridianCity_Gym_Text_ReceivedTM26FromGiovanni::
	.string "{PLAYER} received TM26\n"
	.string "de GIOVANNI.$"

ViridianCity_Gym_Text_ExplainTM26::
	.string "TM26 contains EARTHQUAKE.\p"
	.string "Es un ataque poderoso que\n"
	.string "provoca un temblor enorme.\p"
	.string "Lo creé cuando dirigía el\n"
	.string "far too long ago… $"

ViridianCity_Gym_Text_YouDoNotHaveSpace::
	.string "¡No tienes espacio para esto!$"

ViridianCity_Gym_Text_YujiIntro::
	.string "Heh!\n"
	.string "Ya te estás quedando sin fuerzas\l"
	.string "by now!$"

ViridianCity_Gym_Text_YujiDefeat::
	.string "¡Me quedé sin gasolina!$"

ViridianCity_Gym_Text_YujiPostBattle::
	.string "Necesitarás energía para seguir\n"
	.string "nuestro LÍDER de GIMNASIO.$"

ViridianCity_Gym_Text_AtsushiIntro::
	.string "Rrrroar!\n"
	.string "¡Me estoy llenando de furia!$"

ViridianCity_Gym_Text_AtsushiDefeat::
	.string "Wargh!$"

ViridianCity_Gym_Text_AtsushiPostBattle::
	.string "¡Todavía no soy digno!$"

ViridianCity_Gym_Text_JasonIntro::
	.string "POKéMON and I, we make wonderful\n"
	.string "music together!$"

ViridianCity_Gym_Text_JasonDefeat::
	.string "¡Estás en perfecta armonía!$"

ViridianCity_Gym_Text_JasonPostBattle::
	.string "¿Conoces la identidad de nuestro\n"
	.string "GYM LEADER?$"

ViridianCity_Gym_Text_KiyoIntro::
	.string "El karate es la forma suprema\n"
	.string "martial arts!$"

ViridianCity_Gym_Text_KiyoDefeat::
	.string "Aiyah!$"

ViridianCity_Gym_Text_KiyoPostBattle::
	.string "If my POKéMON were as good at\n"
	.string "karate as I…$"

ViridianCity_Gym_Text_WarrenIntro::
	.string "Solo los de talento ganan con estilo.$"

ViridianCity_Gym_Text_WarrenDefeat::
	.string "¡Perdí el control!$"

ViridianCity_Gym_Text_WarrenPostBattle::
	.string "El LÍDER me regañará por\n"
	.string "perder de esta forma…$"

ViridianCity_Gym_Text_TakashiIntro::
	.string "¡Soy el REY DEL KARATE!\n"
	.string "¡Tu destino está en mis manos!$"

ViridianCity_Gym_Text_TakashiDefeat::
	.string "Ayah!$"

ViridianCity_Gym_Text_TakashiPostBattle::
	.string "The POKéMON LEAGUE?\n"
	.string "¿Tú? ¡No te creas!$"

ViridianCity_Gym_Text_ColeIntro::
	.string "Your POKéMON will cower at the\n"
	.string "¡latigazo de mi látigo!$"

ViridianCity_Gym_Text_ColeDefeat::
	.string "¡Ay!\n"
	.string "Whiplash!$"

ViridianCity_Gym_Text_ColePostBattle::
	.string "¡Espera!\n"
	.string "¡Solo fui descuidado!$"

ViridianCity_Gym_Text_SamuelIntro::
	.string "El GIMNASIO VERDE estaba cerrado\n"
	.string "mucho tiempo.\p"
	.string "¡Pero ya volvió nuestro LÍDER!$"

ViridianCity_Gym_Text_SamuelDefeat::
	.string "¿Me derrotaron?$"

ViridianCity_Gym_Text_SamuelPostBattle::
	.string "You can go on to the POKéMON\n"
	.string "LIGA solo venciendo a nuestro GYM\l"
	.string "LEADER!$"

ViridianCity_Gym_Text_GymGuyAdvice::
	.string "Yo!\n"
	.string "¡Un futuro campeón!\p"
	.string "Ni yo sé del VERDE\n"
	.string "LEADER's identity.\p"
	.string "But one thing's certain.\n"
	.string "Este será el más duro de todos\l"
	.string "los LÍDERES de GIMNASIO.\p"
	.string "Además, escuché que los\n"
	.string "here like GROUND-type POKéMON.$"

ViridianCity_Gym_Text_GymGuyPostVictory::
	.string "¡Me impresionó! GIOVANNI era\n"
	.string "LÍDER del GIMNASIO VIRIDIAN?$"

ViridianCity_Gym_Text_GymStatue::
	.string "GIMNASIO POKéMON VERDIANA\n"
	.string "LEADER: ?\p"
	.string "ENTRENADORES GANADORES:\n"
	.string "{RIVAL}$"

ViridianCity_Gym_Text_GymStatuePlayerWon::
	.string "GIMNASIO POKéMON VERDIANA\n"
	.string "LEADER: GIOVANNI\p"
	.string "ENTRENADORES GANADORES:\n"
	.string "{RIVAL}, {PLAYER}$"

