SaffronCity_Gym_hns_MapScripts::
	.byte 0

SaffronCity_Gym_EventScript_GymGuy::
	goto_if_set FLAG_DEFEATED_SAFFRON_GYM, SaffronCity_Gym_EventScript_GymGuy2
	msgbox SaffronCity_Gym_Text_GymGuideIntro, MSGBOX_NPC
	end

SaffronCity_Gym_EventScript_GymGuy2::
	msgbox SaffronCity_Gym_Text_GymGuideWin, MSGBOX_NPC
	end

SaffronCity_Gym_EventScript_Rebecca::
	trainerbattle_single TRAINER_REBECCA_HNS, SaffronCity_Gym_Text_MediumRebeccaSeen, SaffronCity_Gym_Text_MediumRebeccaBeaten
	msgbox SaffronCity_Gym_Text_MediumRebeccaAfter, MSGBOX_AUTOCLOSE
	end

SaffronCity_Gym_EventScript_Franklin::
	trainerbattle_single TRAINER_FRANKLIN_HNS, SaffronCity_Gym_Text_PsychicFranklinSeen, SaffronCity_Gym_Text_PsychicFranklinBeaten
	msgbox SaffronCity_Gym_Text_PsychicFranklinAfter, MSGBOX_AUTOCLOSE
	end

SaffronCity_Gym_EventScript_Doris::
	trainerbattle_single TRAINER_DORIS_HNS, SaffronCity_Gym_Text_MediumDorisSeen, SaffronCity_Gym_Text_MediumDorisBeaten
	msgbox SaffronCity_Gym_Text_MediumDorisAfter, MSGBOX_AUTOCLOSE
	end

SaffronCity_Gym_EventScript_Jared::
	trainerbattle_single TRAINER_JARED_HNS, SaffronCity_Gym_Text_PsychicJaredSeen, SaffronCity_Gym_Text_PsychicJaredBeaten
	msgbox SaffronCity_Gym_Text_PsychicJaredAfter, MSGBOX_AUTOCLOSE
	end

SaffronCity_Gym_EventScript_Sabrina::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_SAFFRON_GYM, SaffronCity_Gym_EventScript_Sabrina_Defeated
	msgbox SaffronCity_Gym_Text_SabrinaIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_SABRINA_HNS, SaffronCity_Gym_Text_SabrinaWinLoss
	message SaffronCity_Gym_Text_ReceivedMarshBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox SaffronCity_Gym_Text_MarshBadgeInfo, MSGBOX_DEFAULT
	msgbox SaffronCity_Gym_Text_Sabrina_GiveTM, MSGBOX_DEFAULT
	giveitem ITEM_TM_SKILL_SWAP
	msgbox SaffronCity_Gym_Text_Sabrina_ExplainTM, MSGBOX_DEFAULT
	setflag FLAG_BADGE13_GET
	setflag FLAG_DEFEATED_SAFFRON_GYM
	addvar VAR_NUM_BADGES, 1
	setvar VAR_0x8008, 13
	call Common_EventScript_SetGymTrainers_hns
	closemessage
	clearflag FLAG_HIDE_OLIVINE_SABRINA
	release
	end

SaffronCity_Gym_EventScript_Sabrina_Defeated::
	msgbox SaffronCity_Gym_Text_SabrinaPostBattle, MSGBOX_DEFAULT
	closemessage
	release
	end

SaffronCity_Gym_Text_SabrinaIntro:
	.string "SABRINA: Sabía que vendrías...\p"
	.string "Hace tres años tuve una visión\n"
	.string "de tu llegada.\p"
	.string "Buscas mi MEDALLA.\p"
	.string "No disfruto luchar, pero es\n"
	.string "mi deber como LÍDER dar\l"
	.string "MEDALLAS a quien haya demostrado\l"
	.string "ser digno de ella.\p"
	.string "Ya que lo deseas, ¡te mostraré\n"
	.string "mis poderes psíquicos!$"

SaffronCity_Gym_Text_SabrinaWinLoss:
	.string "SABRINA: Tu poder...\p"
	.string "Supera mucho lo que preví...\p"
	.string "Tal vez no sea posible predecir\n"
	.string "totalmente lo que traerá el futuro…\p"
	.string "Está bien, ganaste. Te has ganado\n"
	.string "la MEDALLA MARJA.$"

SaffronCity_Gym_Text_ReceivedMarshBadge:
	.string "{PLAYER} recibió la MEDALLA PANTANO.$"

SaffronCity_Gym_Text_MarshBadgeInfo:
	.string "SABRINA: La MEDALLA MARJA saca\n"
	.string "tus poderes subliminales…\p"
	.string "Aunque no pude predecir con\n"
	.string "exactitud tu poder, esto sí lo\l"
	.string "sé que es verdad.\p"
	.string "¡Te convertirás en un CAMPEÓN\n"
	.string "célebre y muy querido!$"

SaffronCity_Gym_Text_Sabrina_GiveTM:
	.string "Toma, llévate esto también.$"

SaffronCity_Gym_Text_Sabrina_ExplainTM:
	.string "Contiene INTERCAMBIO DE HABILIDAD.\p"
	.string "Puede quitarle las habilidades\n"
	.string "al rival y darle las tuyas.\p"
	.string "Úsalo con sabiduría...$"

SaffronCity_Gym_Text_SabrinaPostBattle:
	.string "SABRINA: El amor por tus\n"
	.string "Los POKéMON superaron mi poder\l"
	.string "psíquico...\p"
	.string "El poder del amor, creo, es\n"
	.string "también un tipo de poder psíquico...$"

SaffronCity_Gym_Text_SabrinaRematch:
	.string "SABRINA: Ah, el CAMPEÓN de KANTO.\p"
	.string "Sentí tu regreso.\p"
	.string "Tu poder ha crecido inmensamente.\p"
	.string "Aún ahora, siento tu aura.\p"
	.string "¿Quieres otra revancha conmigo?$"

SaffronCity_Gym_Text_SabrinaRematchDefeat:
	.string "SABRINA: El amor por tus\n"
	.string "POKéMON volvió a abrumar mi\l"
	.string "poder psíquico…$"

SaffronCity_Gym_Text_MediumRebeccaSeen:
	.string "¡El poder de todos los que\n"
	.string "derrotaste ahora es mío!$"

SaffronCity_Gym_Text_MediumRebeccaBeaten:
	.string "Strong… Far too strong…$"

SaffronCity_Gym_Text_MediumRebeccaAfter:
	.string "¿Cuál es la fuente de tu poder?$"

SaffronCity_Gym_Text_PsychicFranklinSeen:
	.string "El poder psíquico es el poder de\n"
	.string "tu alma.$"

SaffronCity_Gym_Text_PsychicFranklinBeaten:
	.string "¡Tu alma tiene más poder que la\n"
	.string "mía!$"

SaffronCity_Gym_Text_PsychicFranklinAfter:
	.string "Hiciste tu alma más fuerte, no solo\n"
	.string "tus habilidades.$"

SaffronCity_Gym_Text_MediumDorisSeen:
	.string "Fufufufu... Lo veo claramente.\p"
	.string "¡Puedo ver dentro de tu alma!$"

SaffronCity_Gym_Text_MediumDorisBeaten:
	.string "Though I read you, I still lost…$"

SaffronCity_Gym_Text_MediumDorisAfter:
	.string "¡Rayos! Olvidé que predije que\n"
	.string "perdería contra ti.$"

SaffronCity_Gym_Text_PsychicJaredSeen:
	.string "El DOJO DE LUCHA de al lado fue\n"
	.string "alguna vez el GIMNASIO de aquí.$"

SaffronCity_Gym_Text_PsychicJaredBeaten:
	.string "I was no match…$"

SaffronCity_Gym_Text_PsychicJaredAfter:
	.string "El REY DEL KARATE, maestro del\n"
	.string "DOJO DE LUCHA, fue derrotado\l"
	.string "por SABRINA.$"

SaffronCity_Gym_Text_GymGuideIntro:
	.string "¡Hola, futuro CAMPEÓN!\p"
	.string "Un ENTRENADOR tan hábil como tú\n"
	.string "no necesita que le digan cómo\l"
	.string "vencer a POKéMON tipo PSÍQUICO,\l"
	.string "¿Verdad?\p"
	.string "¡Espero grandes cosas de ti!\p"
	.string "¡Buena suerte!$"

SaffronCity_Gym_Text_GymGuideWin:
	.string "¡Fue otra batalla fantástica!$"

SaffronCity_Gym_EventScript_GymStatue::
	lockall
	goto_if_set FLAG_BADGE13_GET, SaffronCity_Gym_EventScript_GymStatuePostVictory
	msgbox SaffronCity_Gym_Text_GymStatue
	releaseall
	end

SaffronCity_Gym_EventScript_GymStatuePostVictory::
	msgbox SaffronCity_Gym_Text_GymStatuePlayerWon
	releaseall
	end


SaffronCity_Gym_Text_GymStatue::
    .string "GIMNASIO POKéMON DE AZAFRÁN\n"
    .string "LÍDER: SABRINA\p"
	.string "ENTRENADORES GANADORES:\n"
	.string "BLUE, RED$"

SaffronCity_Gym_Text_GymStatuePlayerWon::
    .string "GIMNASIO POKéMON DE AZAFRÁN\n"
    .string "LÍDER: SABRINA\p"
    .string "ENTRENADORES GANADORES:\n"
	.string "BLUE, RED, {PLAYER}$"
