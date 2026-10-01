CeladonCity_Gym_hns_MapScripts::
	.byte 0


CeladonCity_Gym_EventScript_Erika::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_CELADON_GYM, CeladonCity_Gym_EventScript_Erika_Defeated
	msgbox CeladonCity_Gym_Text_ErikaBeforeBattle, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_ERIKA_HNS, CeladonCity_Gym_Text_ErikaBeaten
	message CeladonCity_Gym_Text_PlayerReceivedRainbowBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox CeladonCity_Gym_Text_Erika_GiveTM, MSGBOX_DEFAULT
	giveitem ITEM_TM_GIGA_DRAIN
	msgbox CeladonCity_Gym_Text_Erika_ExplainTM, MSGBOX_DEFAULT
	setflag FLAG_BADGE12_GET
	setflag FLAG_DEFEATED_CELADON_GYM
	addvar VAR_NUM_BADGES, 1
	setvar VAR_0x8008, 12
	call Common_EventScript_SetGymTrainers_hns
	clearflag FLAG_HIDE_FOUNTAIN_ERIKA
	closemessage
	release
	end

CeladonCity_Gym_EventScript_Erika_Defeated::
	msgbox CeladonCity_Gym_Text_ErikaAfterBattle, MSGBOX_DEFAULT
	closemessage
	release
	end

CeladonCity_Gym_Text_ErikaBeforeBattle:
	.string "ERIKA: Hola... Qué lindo clima,\n"
	.string "¿no crees? Es tan agradable...\p"
	.string "...Tengo miedo de dormirme...\p"
	.string "Mi nombre es ERIKA. Soy la LÍDER\n"
	.string "del GIMNASIO de CIUDAD CELADON.\p"
	.string "...¿Oh? ¿Vienes desde JOHTO?\n"
	.string "Qué lindo...\p"
	.string "Oh. Lo siento, no me di cuenta\n"
	.string "de que querías desafiarme.\p"
	.string "Muy bien, pero no perderé.$"

CeladonCity_Gym_Text_ErikaBeaten:
	.string "ERIKA: ¡Oh! Admito mi derrota...\p"
	.string "Eres increíblemente fuerte...\p"
	.string "Te daré la MEDALLA ARCOÍRIS...$"

CeladonCity_Gym_Text_PlayerReceivedRainbowBadge:
	.string "{PLAYER} recibió la MEDALLA ARCOÍRIS.$"

CeladonCity_Gym_Text_Erika_GiveTM:
	.string "ERIKA: Fue un combate\n"
	.string "encantador.\p"
	.string "Me sentí inspirada. Por favor,\n"
	.string "toma esta MT.$"

CeladonCity_Gym_Text_Erika_ExplainTM:
	.string "Es GIGA DRENADO.\p"
	.string "Es un movimiento maravilloso que\n"
	.string "absorbe la mitad del daño hecho\l"
	.string "para curar a tu POKéMON.\p"
	.string "Úsala si así lo deseas...$"

CeladonCity_Gym_Text_ErikaAfterBattle:
	.string "ERIKA: Perder deja un sabor amargo\n"
	.string "regusto...\p"
	.string "Pero saber que hay entrenadores\n"
	.string "fuertes me impulsa a mejorar...$"

CeladonCity_Gym_Text_ErikaRematch:
	.string "ERIKA: Oh, hola.\p"
	.string "¡Qué sorpresa, CAMPEÓN DE KANTO!\p"
	.string "Es un gusto verte de nuevo.\p"
	.string "Tu viaje debe haber sido muy\n"
	.string "emocionante.\p"
	.string "Hasta los campeones aman los retos.\p"
	.string "¿Quieres otra revancha conmigo?$"

CeladonCity_Gym_Text_ErikaRematchDefeat:
	.string "ERIKA: Perder deja un regusto\n"
	.string "amargo...\p"
	.string "Pero saber que hay entrenadores\n"
	.string "fuertes me impulsa a mejorar...$"

CeladonCity_Gym_EventScript_Michelle::
	trainerbattle_single TRAINER_MICHELLE_HNS, CeladonCity_Gym_Text_LassMichelleSeen, CeladonCity_Gym_Text_LassMichelleBeaten
	msgbox CeladonCity_Gym_Text_LassMichelleAfter, MSGBOX_AUTOCLOSE
	end

CeladonCity_Gym_Text_LassMichelleSeen:
	.string "¿Crees que un GIMNASIO de chicas\n"
	.string "¿Raro?$"

CeladonCity_Gym_Text_LassMichelleBeaten:
	.string "Oh, bleah!$"

CeladonCity_Gym_Text_LassMichelleAfter:
	.string "¡Solo fui descuidado, nada más!$"


CeladonCity_Gym_EventScript_Tanya::
	trainerbattle_single TRAINER_TANYA_HNS, CeladonCity_Gym_Text_PicnickerTanyaSeen, CeladonCity_Gym_Text_PicnickerTanyaBeaten
	msgbox CeladonCity_Gym_Text_PicnickerTanyaAfter, MSGBOX_AUTOCLOSE
	end

CeladonCity_Gym_Text_PicnickerTanyaSeen:
	.string "Oh, ¿una batalla? Da miedo,\n"
	.string "¡pero está bien!$"

CeladonCity_Gym_Text_PicnickerTanyaBeaten:
	.string "¿Oh, eso es todo?$"

CeladonCity_Gym_Text_PicnickerTanyaAfter:
	.string "Mira todas tus MEDALLAS. ¡Con\n"
	.string "razón no pude ganar!$"

CeladonCity_Gym_EventScript_Julia::
	trainerbattle_single TRAINER_JULIA_HNS, CeladonCity_Gym_Text_BeautyJuliaSeen, CeladonCity_Gym_Text_BeautyJuliaBeaten
	msgbox CeladonCity_Gym_Text_BeautyJuliaAfter, MSGBOX_AUTOCLOSE
	end

CeladonCity_Gym_Text_BeautyJuliaSeen:
	.string "¿Estabas mirando estas flores?\n"
	.string "¿o a mí?$"

CeladonCity_Gym_Text_BeautyJuliaBeaten:
	.string "¡Qué molesto!$"

CeladonCity_Gym_Text_BeautyJuliaAfter:
	.string "¿Cómo puedo llegar a ser\n"
	.string "femenina como ERIKA?$"

CeladonCity_Gym_EventScript_Jo::
	trainerbattle_double TRAINER_JO_AND_ZOE_HNS, CeladonCity_Gym_Text_TwinsJoAndZoe1Seen, CeladonCity_Gym_Text_TwinsJoAndZoe1Beaten, Route104_Text_GinaNotEnoughMons
	special GetPlayerBigGuyGirlString
	msgbox CeladonCity_Gym_Text_TwinsJoAndZoe1After, MSGBOX_AUTOCLOSE
	end

CeladonCity_Gym_EventScript_Zoe::
	trainerbattle_double TRAINER_JO_AND_ZOE_HNS, CeladonCity_Gym_Text_TwinsJoAndZoe2Seen, CeladonCity_Gym_Text_TwinsJoAndZoe2Beaten, Route104_Text_GinaNotEnoughMons
	msgbox CeladonCity_Gym_Text_TwinsJoAndZoe2After, MSGBOX_AUTOCLOSE
	end

CeladonCity_Gym_Text_TwinsJoAndZoe1Seen:
	.string "¡Te mostraremos los movimientos\n"
	.string "que ERIKA nos enseñó!$"

CeladonCity_Gym_Text_TwinsJoAndZoe1Beaten:
	.string "Oh... Perdimos...$"

CeladonCity_Gym_Text_TwinsJoAndZoe1After:
	.string "¡ERIKA te las hará pagar por nosotros!$"

CeladonCity_Gym_Text_TwinsJoAndZoe2Seen:
	.string "¡Vamos a proteger a ERIKA!$"

CeladonCity_Gym_Text_TwinsJoAndZoe2Beaten:
	.string "No pudimos ganar...$"

CeladonCity_Gym_Text_TwinsJoAndZoe2After:
	.string "¡ERIKA es mucho más fuerte!$"

CeladonCity_Gym_EventScript_GymStatue::
	lockall
	goto_if_set FLAG_BADGE12_GET, CeladonCity_Gym_EventScript_GymStatuePostVictory
	msgbox CeladonCity_Gym_Text_GymStatue
	releaseall
	end

CeladonCity_Gym_EventScript_GymStatuePostVictory::
	msgbox CeladonCity_Gym_Text_GymStatuePlayerWon
	releaseall
	end

CeladonCity_Gym_Text_GymStatue::
    .string "GIMNASIO POKéMON DE CIUDAD CELESTE\n"
    .string "LÍDER: ERIKA\p"
	.string "ENTRENADORES GANADORES:\n"
	.string "BLUE, RED$"

CeladonCity_Gym_Text_GymStatuePlayerWon::
    .string "GIMNASIO POKéMON DE CIUDAD CELESTE\n"
    .string "LÍDER: ERIKA\p"
    .string "ENTRENADORES GANADORES:\n"
	.string "BLUE, RED, {PLAYER}$"
