GoldenrodCity_Gym_hns_MapScripts::
	.byte 0
@Carrie, Bridget, Victoria, Samantha, gym guy


GoldenrodCity_Gym_EventScript_Carrie::
	trainerbattle_single TRAINER_CARRIE_HNS, GoldenrodCity_Gym_Text_LassCarrieSeen, GoldenrodCity_Gym_Text_LassCarrieBeaten
	msgbox GoldenrodCity_Gym_Text_LassCarrieAfter, MSGBOX_AUTOCLOSE
	end

GoldenrodCity_Gym_EventScript_Bridget::
	trainerbattle_single TRAINER_BRIDGET_HNS, GoldenrodCity_Gym_Text_LassBridgetSeen, GoldenrodCity_Gym_Text_LassBridgetBeaten
	msgbox GoldenrodCity_Gym_Text_LassBridgetAfter, MSGBOX_AUTOCLOSE
	end

GoldenrodCity_Gym_EventScript_Victoria::
	trainerbattle_single TRAINER_VICTORIA_HNS, GoldenrodCity_Gym_Text_BeautyVictoriaSeen, GoldenrodCity_Gym_Text_BeautyVictoriaBeaten
	msgbox GoldenrodCity_Gym_Text_BeautyVictoriaAfter, MSGBOX_AUTOCLOSE
	end

GoldenrodCity_Gym_EventScript_Samantha::
	trainerbattle_single TRAINER_SAMANTHA_HNS, GoldenrodCity_Gym_Text_BeautySamanthaSeen, GoldenrodCity_Gym_Text_BeautySamanthaBeaten
	msgbox GoldenrodCity_Gym_Text_BeautySamanthaAfter, MSGBOX_AUTOCLOSE
	end

GoldenrodCity_Gym_EventScript_Gym_Guy::
	lock
	faceplayer
	goto_if_set FLAG_BADGE03_GET, GoldenrodCity_Gym_EventScript_Gym_Guy_After
	msgbox GoldenrodCity_Gym_Text_GymGuide, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_Gym_EventScript_Gym_Guy_After::
	msgbox GoldenrodCity_Gym_Text_GymGuideWin, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_Gym_EventScript_Whitney::
	lock
	faceplayer
	goto_if_eq VAR_GOLDENROD_CITY_STATE, 3, GoldenrodCity_Gym_EventScript_WhitneyCrying
	goto_if_eq VAR_GOLDENROD_CITY_STATE, 4, GoldenrodCity_Gym_EventScript_WhitneyBadge
	goto_if_set FLAG_DEFEATED_GOLDENROD_CITY_GYM, GoldenrodCity_Gym_EventScript_WhitneyDefeated
	msgbox GoldenrodCity_Gym_Text_WhitneyBefore, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_WHITNEY_1_HNS, GoldenrodCity_Gym_Text_WhitneyShouldntBeSoSerious
	msgbox GoldenrodCity_Gym_Text_WhitneyYouMeanie, MSGBOX_DEFAULT
	setvar VAR_GOLDENROD_CITY_STATE, 3
	closemessage
	release
	end

GoldenrodCity_Gym_EventScript_WhitneyCrying::
	lock
	faceplayer
	msgbox GoldenrodCity_Gym_Text_WhitneyYouMeanie, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_Gym_EventScript_WhitneyBadge::
	lock
	faceplayer
	msgbox GoldenrodCity_Gym_Text_WhitneyWhatDoYouWant, MSGBOX_DEFAULT
	closemessage
	message GoldenrodCity_Gym_Text_PlayerReceivedPlainBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox GoldenrodCity_Gym_Text_WhitneyPlainBadge, MSGBOX_DEFAULT
	setflag FLAG_BADGE03_GET
	setflag FLAG_DEFEATED_GOLDENROD_CITY_GYM
	addvar VAR_NUM_BADGES, 1
	setvar VAR_0x8008, 3
	call Common_EventScript_SetGymTrainers_hns
	giveitem ITEM_TM_ATTRACT
	msgbox GoldenrodCity_Gym_Text_WhitneyAttract, MSGBOX_DEFAULT
	setvar VAR_GOLDENROD_CITY_STATE, 5
	closemessage
	release
	end

GoldenrodCity_Gym_EventScript_WhitneyDefeated::
	lock
	faceplayer
	msgbox GoldenrodCity_Gym_Text_WhitneyGoodCry, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_Gym_EventScript_Trigger::	
	turnobject LOCALID_GOLDENROD_CITY_GYM_BRIDGET DIR_WEST
	msgbox GoldenrodCity_Gym_Text_BridgetWhitneyCries, MSGBOX_DEFAULT
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkUp1
	waitmovement 0
	setvar VAR_GOLDENROD_CITY_STATE, 4
	closemessage
	release
	end


GoldenrodCity_Gym_EventScript_Statue::
	lock
	goto_if_set FLAG_DEFEATED_GOLDENROD_CITY_GYM, GoldenrodCity_Gym_EventScript_Statue2
	msgbox GoldenrodCity_Gym_Text_GymStatue, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_Gym_EventScript_Statue2::
	msgbox GoldenrodCity_Gym_Text_GymStatueCertified, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_Gym_Text_GymStatue:
	.string "GOLDENROD POKéMON GYM$"

GoldenrodCity_Gym_Text_GymStatueCertified:
	.string "GIMNASIO POKéMON DE CIUDAD TRIGAL\p"
	.string "ENTRENADORES DE WHITNEY:\n"
	.string "{PLAYER}$"

GoldenrodCity_Gym_Text_WhitneyBefore:
    .string "¡Hola! ¡Soy WHITNEY!\p"
    .string "Todos amaban los POKéMON, ¡así que\n"
    .string "yo también!\p"
    .string "¡Los POKéMON son súper lindos!\p"
    .string "¿Quieres luchar? Te advierto...\n"
    .string "¡soy muy buena!$"

GoldenrodCity_Gym_Text_WhitneyShouldntBeSoSerious:
    .string "Bua...\p"
    .string "¡Buaaaaah! ¡Eres malo!\p"
    .string "¡No seas tan serio! Tú...\n"
    .string "¡Tú, niño, tú!$"

GoldenrodCity_Gym_Text_WhitneyYouMeanie:
    .string "¡Buaaaaa!\p"
    .string "¡Buaaaaa!\p"
    .string "…Snif, hic… ¡Eres malo!$"

GoldenrodCity_Gym_Text_WhitneyWhatDoYouWant:
    .string "…Snif…\p"
    .string "¿Qué? ¿Qué quieres? ¿UNA MEDALLA?\p"
    .string "Ah, cierto. Lo olvidé. Ten,\n"
    .string "MEDALLA LLANA.$"

GoldenrodCity_Gym_Text_PlayerReceivedPlainBadge:
    .string "{PLAYER} received PLAINBADGE.$"

GoldenrodCity_Gym_Text_WhitneyPlainBadge:
    .string "La MEDALLA LLANA permite que tus\n"
    .string "POKéMON usen FUERZA fuera de combate.\p"
    .string "También aumenta la\n"
	.string "DEFENSA de tus POKéMON.\p"
    .string "¡Oh, también puedes tener esto!$"

GoldenrodCity_Gym_Text_WhitneyAttract:
    .string "¡Es ATRAER! Aprovecha todo el\n"
    .string "encanto de un POKéMON.\p"
    .string "¿No es perfecto para alguien tan\n"
    .string "linda como yo?$"

GoldenrodCity_Gym_Text_WhitneyGoodCry:
    .string "¡Ah, qué buen llanto!$"

GoldenrodCity_Gym_Text_WhitneyRematch:
    .string "¡Hola! ¡Eres tú!\p"
    .string "¿Wow, ya eres CAMPEÓN de JOHTO?\p"
    .string "¡De verdad eres increíble!\p"
    .string "Quiero ver qué tan fuerte eres.\p"
    .string "¿Quieres otra revancha conmigo?$"

GoldenrodCity_Gym_Text_WhitneyRematchDefeat:
    .string "¡Buaaaaa!\p"
    .string "¡Buaaaaa!\p"
    .string "…Snif, hic… ¡Eres malo!$"

GoldenrodCity_Gym_Text_LassCarrieSeen:
    .string "Que la linda apariencia de mis\n"
    .string "POKéMON no te engañe.\p"
    .string "¡Pueden azotarte!$"

GoldenrodCity_Gym_Text_LassCarrieBeaten:
    .string "Vaya… creía que eras débil…$"

GoldenrodCity_Gym_Text_LassCarrieAfter:
    .string "Do my POKéMON think I'm cute?$"

GoldenrodCity_Gym_Text_LassBridgetSeen:
    .string "Prefiero los POKéMON lindos que\n"
    .string "los POKéMON fuertes.\p"
    .string "¡Pero tengo POKéMON fuertes y lindos!$"

GoldenrodCity_Gym_Text_LassBridgetBeaten:
    .string "Oh, no, no, no!$"

GoldenrodCity_Gym_Text_LassBridgetAfter:
    .string "Intento vencer a WHITNEY, pero...\n"
    .string "Es depresivo.\p"
    .string "¡Estoy bien! Si pierdo, me esforzaré\n"
    .string "más la próxima vez!$"

GoldenrodCity_Gym_Text_BridgetWhitneyCries:
    .string "Oh, no. Hiciste llorar a WHITNEY.\p"
    .string "Está bien. Ya parará. Ella\n"
    .string "siempre llora cuando pierde.$"

GoldenrodCity_Gym_Text_BeautyVictoriaSeen:
    .string "¡Oh, eres un entrenador muy lindo!\p"
    .string "¡Me caes bien, pero no me rendiré!$"

GoldenrodCity_Gym_Text_BeautyVictoriaBeaten:
    .string "Let's see… Oops, it's over?$"

GoldenrodCity_Gym_Text_BeautyVictoriaAfter:
    .string "¡Vaya, debes ser bueno para vencerme!\n"
    .string "¡Sigue así!$"

GoldenrodCity_Gym_Text_BeautySamanthaSeen:
    .string "¡Da lo mejor de ti o te derrotaré\n"
    .string "por completo!$"

GoldenrodCity_Gym_Text_BeautySamanthaBeaten:
    .string "No! Oh, MEOWTH, I'm so sorry!$"

GoldenrodCity_Gym_Text_BeautySamanthaAfter:
    .string "Le enseñé a MEOWTH movimientos para\n"
    .string "cualquier tipo…$"

GoldenrodCity_Gym_Text_GymGuide:
    .string "¡Ey! ¡Futuro CAMPEÓN!\p"
    .string "En este GIMNASIO está WHITNEY, la\n"
    .string "maestro de POKéMON tipo NORMAL.\p"
    .string "Cuidado con su lindo equipo.\p"
    .string "Algunos POKéMON de este gimnasio\n"
    .string "también tienen el recién\l"
    .string "descubierto tipo HADA.\p"
    .string "Ve a la RUTA 34 si buscas uno\n"
    .string "tipo LUCHA o tipo VENENO.$"

GoldenrodCity_Gym_Text_GymGuideWin:
    .string "¿Ganaste? ¡Genial! Estaba ocupado\n"
    .string "admirando a las chicas de aquí.$"

