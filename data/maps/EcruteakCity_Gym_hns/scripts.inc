EcruteakCity_Gym_hns_MapScripts::
	.byte 0

EcruteakCity_Gym_EventScript_GymGuy::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_ECRUTEAK_CITY_GYM, EcruteakCity_Gym_EventScript_GymGuy2
	msgbox EcruteakCity_GymGuideText, MSGBOX_DEFAULT
	closemessage
	release
	end
	
EcruteakCity_Gym_EventScript_GymGuy2::
	msgbox EcruteakCity_GymGuideWinText, MSGBOX_DEFAULT
	release
	end	

EcruteakCity_Gym_EventScript_Jeffrey::
	trainerbattle_single TRAINER_JEFFREY_HNS, SageJeffreySeenText, SageJeffreyBeatenText
	msgbox SageJeffreyAfterBattleText, MSGBOX_AUTOCLOSE
	end
EcruteakCity_Gym_EventScript_Ping::
	trainerbattle_single TRAINER_PING_HNS, SagePingSeenText, SagePingBeatenText
	msgbox SagePingAfterBattleText, MSGBOX_AUTOCLOSE
	end

EcruteakCity_Gym_EventScript_Martha::
	trainerbattle_single TRAINER_MARTHA_HNS, MediumMarthaSeenText, MediumMarthaBeatenText
	msgbox MediumMarthaAfterBattleText, MSGBOX_AUTOCLOSE
	end

EcruteakCity_Gym_EventScript_Grace::
	trainerbattle_single TRAINER_GRACE_HNS, MediumGraceSeenText, MediumGraceBeatenText
	msgbox MediumGraceAfterBattleText, MSGBOX_AUTOCLOSE
	end

EcruteakCity_Gym_EventScript_Morty::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_ECRUTEAK_CITY_GYM, EcruteakCity_Gym_EventScript_Morty_Defeated
	msgbox MortyIntroText, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_MORTY_1_HNS, MortyWinLossText
	message Text_ReceivedFogBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox MortyText_FogBadgeSpeech, MSGBOX_DEFAULT
	setflag FLAG_BADGE04_GET
	setflag FLAG_DEFEATED_ECRUTEAK_CITY_GYM
	addvar VAR_NUM_BADGES, 1
	setvar VAR_0x8008, 4
	call Common_EventScript_SetGymTrainers_hns
	giveitem ITEM_TM_SHADOW_BALL
	msgbox MortyText_ShadowBallSpeech, MSGBOX_DEFAULT
	setvar VAR_ECRUTEAK_CITY_STATE, 4
	closemessage
	release
	end

EcruteakCity_Gym_EventScript_Morty_Defeated::
	msgbox MortyFightDoneText, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_Gym_EventScript_Statue::
	lock
	goto_if_set FLAG_DEFEATED_ECRUTEAK_CITY_GYM, EcruteakCity_Gym_EventScript_Statue2
	msgbox EcruteakCity_Gym_Text_GymStatue, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_Gym_EventScript_Statue2::
	msgbox EcruteakCity_Gym_Text_GymStatueCertified, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_Gym_Text_GymStatue:
	.string "ECRUTEAK CITY POKéMON GYM$"

EcruteakCity_Gym_Text_GymStatueCertified:
	.string "GIMNASIO POKéMON CIUDAD IRIS\p"
	.string "ENTRENADORES DE MORTY:\n"
	.string "{PLAYER}$"

MortyIntroText:
	.string "Qué bueno que hayas venido.\p"
	.string "Aquí en CIUDAD IRIS, los POKéMON\n"
	.string "siempre han sido venerados.\p"
	.string "Dicen que un POKéMON de colores\n"
	.string "del arcoíris bajará para\l"
	.string "aparecer ante un gran Entrenador.\p"
	.string "Creí en ese cuento, así que me\n"
	.string "entrené aquí en secreto.\p"
	.string "Gracias a eso, ahora puedo ver lo\n"
	.string "que otros no pueden.\p"
	.string "Solo un poco más...\p"
	.string "Con un poco más, podría ver\n"
	.string "un futuro donde encuentre al\l"
	.string "POKéMON color arcoíris.\p"
	.string "¡Tú me ayudarás a alcanzar\n"
	.string "ese nivel!$"

MortyWinLossText:
	.string "Aún no soy lo bastante bueno...\p"
	.string "Está bien. Esta MEDALLA es tuya.$"

Text_ReceivedFogBadge:
	.string "{PLAYER} received the MEDALLA Niebla.$"

MortyText_FogBadgeSpeech:
	.string "Con la MEDALLA NIEBLA, los\n"
	.string "POKéMON hasta el nivel 50\p"
	.string "te obedecerán. Además, cualquier\n"
	.string "Podrás usar SURF\l"
	.string "en cualquier momento.\p"
	.string "Quiero que tengas esto también.$"

MortyText_ShadowBallSpeech:
	.string "Es BOLA SOMBRE.\n"
	.string "Causa daño y puede\l"
	.string "bajar la DEF. ESP.\p"
	.string "Úsala si te conviene.$"

MortyFightDoneText:
	.string "Ya veo...\p"
	.string "Tu viaje te ha llevado a\n"
	.string "lugares muy lejanos.\p"
	.string "Has visto mucho más de lo que\n"
	.string "yo jamás he visto.\p"
	.string "Te envidio por eso...$"

MortyRematchText:
	.string "¡Ah, el CAMPEÓN de JOHTO!\n"
	.string "Qué bueno que vinieras.\p"
	.string "Has demostrado fuerza y habilidad,\n"
	.string "¿pero habrás crecido desde la\l"
	.string "última vez que luchamos?\p"
	.string "He entrenado con mis POKéMON\n"
	.string "tipo FANTASMA desde entonces.\p"
	.string "Veamos si puedes superar\n"
	.string "las sombras otra vez.\p"
	.string "¿Quieres una revancha?$"

Morty_RematchDefeatText:
	.string "Aún no soy lo bastante bueno...\p"
	.string "Has visto mucho más de lo que\n"
	.string "yo jamás he visto.\p"
	.string "Te envidio por eso...$"

SageJeffreySeenText:
	.string "Pasé la primavera con mis\n"
	.string "POKéMON planta.\p"
	.string "Luego verano, otoño e invierno...\p"
	.string "Luego llegó la primavera.\n"
	.string "Llevamos mucho tiempo juntos.$"

SageJeffreyBeatenText:
	.string "Victorias y derrotas... he\n"
	.string "conocido ambas.$"

SageJeffreyAfterBattleText:
	.string "Where did POKéMON come from?$"

SagePingSeenText:
	.string "¿Puedes hacerle algún daño\n"
	.string "a nuestros POKéMON?$"

SagePingBeatenText:
	.string "Ah! Well done!$"

SagePingAfterBattleText:
	.string "Usamos POKéMON tipo FANTASMA.\p"
	.string "¡Ningún ataque tipo NORMAL\n"
	.string "puede dañarlos!$"

MediumMarthaSeenText:
	.string "I shall win!$"

MediumMarthaBeatenText:
	.string "I... I... I lost!$"

MediumMarthaAfterBattleText:
	.string "¡Quien más desea ganar,\n"
	.string "es quien lo logrará!$"

MediumGraceSeenText:
	.string "¿Perdido en los pasillos oscuros?\n"
	.string "¡Vénceme si quieres una pista!$"

MediumGraceBeatenText:
	.string "Wha-what?$"

MediumGraceAfterBattleText:
	.string "Está bien. Te diré el secreto\n"
	.string "de las sombras.\p"
	.string "¡El camino está justo frente a\n"
	.string "tus ojos!$"

EcruteakCity_GymGuideText:
	.string "¡Hola, CAMPEÓN! Ya casi\n"
	.string "estás a la mitad.\p"
	.string "Los ENTRENADORES usan GHOST y\n"
	.string "POKéMON tipo SIN DIESTRO.\p"
	.string "Aunque MORTY es experto en\n"
	.string "tipo FANTASMA, ten cuidado con\l"
	.string "su ciervo místico.\p"
	.string "Dicen que provoca extrañas\n"
	.string "pesadillas...$"

EcruteakCity_GymGuideWinText:
	.string "¡Uff, {PLAYER}! ¡Lo hiciste genial!\p"
	.string "¡Yo estaba encogido en el rincón\n"
	.string "de puro terror!$"

EcruteakCity_GymClosedText:
	.string "MORTY, el LÍDER del GIMNASIO,\n"
	.string "está ausente.\p"
	.string "Lo siento, pero tendrás que\n"
	.string "vete.\p"
	.string "Jo jojojo.$"
