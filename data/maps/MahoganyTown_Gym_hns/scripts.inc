MahoganyTown_Gym_hns_MapScripts::
	.byte 0


MahoganyTown_Gym_EventScript_Statue::
	lock
	goto_if_set FLAG_DEFEATED_MAHOGANY_TOWN_GYM,  MahoganyTown_Gym_EventScript_Statue2
	msgbox MahoganyTown_Gym_Text_GymStatue, MSGBOX_DEFAULT
	closemessage
	release
	end

MahoganyTown_Gym_EventScript_Statue2::
	msgbox MahoganyTown_Gym_Text_GymStatueCertified, MSGBOX_DEFAULT
	closemessage
	release
	end

MahoganyTown_Gym_Text_GymStatue:
	.string "MAHOGANY TOWN POKéMON GYM$"

MahoganyTown_Gym_Text_GymStatueCertified:
	.string "GIMNASIO POKéMON DE PUEBLO CAOBA\p"
	.string "ENTRENADORES DE PRYCE:\n"
	.string "{PLAYER}$"


MahoganyTown_GymEventScript_GymGuy::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_MAHOGANY_TOWN_GYM, MahoganyTown_Gym_EventScript_GymGuy2
	msgbox MahoganyTown_Gym_Text_Guide, MSGBOX_DEFAULT
	closemessage
	release
	end
	
MahoganyTown_Gym_EventScript_GymGuy2::
	msgbox MahoganyTown_Gym_Text_GuideWin, MSGBOX_DEFAULT
	release
	end	

MahoganyTown_Gym_EventScript_Ronald::
	trainerbattle_single TRAINER_RONALD_HNS, MahoganyTown_Gym_Text_BoarderRonaldSeen, MahoganyTown_Gym_Text_BoarderRonaldBeaten
	msgbox MahoganyTown_Gym_Text_BoarderRonaldAfter, MSGBOX_AUTOCLOSE
	end

MahoganyTown_Gym_EventScript_Brad::
	trainerbattle_single TRAINER_BRAD_HNS, MahoganyTown_Gym_Text_BoarderBradSeen, MahoganyTown_Gym_Text_BoarderBradBeaten
	msgbox MahoganyTown_Gym_Text_BoarderBradAfter, MSGBOX_AUTOCLOSE
	end

MahoganyTown_Gym_EventScript_Douglas::
	trainerbattle_single TRAINER_DOUGLAS_HNS, MahoganyTown_Gym_Text_BoarderDouglasSeen, MahoganyTown_Gym_Text_BoarderDouglasBeaten
	msgbox MahoganyTown_Gym_Text_BoarderDouglasAfter, MSGBOX_AUTOCLOSE
	end

MahoganyTown_Gym_EventScript_Roxanne::
	trainerbattle_single TRAINER_ROXANNE_HNS, MahoganyTown_Gym_Text_SkierRoxanneSeen, MahoganyTown_Gym_Text_SkierRoxanneBeaten
	msgbox MahoganyTown_Gym_Text_SkierRoxanneAfter, MSGBOX_AUTOCLOSE
	end

MahoganyTown_Gym_EventScript_Clarissa::
	trainerbattle_single TRAINER_CLARISSA_HNS, MahoganyTown_Gym_Text_SkierClarissaSeen, MahoganyTown_Gym_Text_SkierClarissaBeaten
	msgbox MahoganyTown_Gym_Text_SkierClarissaAfter, MSGBOX_AUTOCLOSE
	end

MahoganyTown_Gym_EventScript_Pryce::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_MAHOGANY_TOWN_GYM, MahoganyTown_Gym_EventScript_Pryce_Defeated
	msgbox MahoganyTown_Gym_Text_PryceIntro, MSGBOX_DEFAULT
	goto_if_set FLAG_DEFEATED_OLIVINE_CITY_GYM, MahoganyTown_Gym_EventScript_OlivineCheckCianwood
	goto_if_set FLAG_DEFEATED_CIANWOOD_GYM, MahoganyTown_Gym_EventScript_CianwoodCheckOlivine
	goto MahoganyTown_Gym_EventScript_Pryce_Battle1

MahoganyTown_Gym_EventScript_PryceVictory::
	message MahoganyTown_Gym_Text_ReceivedBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox MahoganyTown_Gym_Text_GlacierBadgeSpeech, MSGBOX_DEFAULT
	setflag FLAG_BADGE07_GET
	setflag FLAG_DEFEATED_MAHOGANY_TOWN_GYM
    addvar VAR_NUM_BADGES, 1
	setvar VAR_0x8008, 7
	call Common_EventScript_SetGymTrainers_hns
	giveitem ITEM_TM_HAIL
	msgbox MahoganyTown_Gym_Text_HailSpeech, MSGBOX_DEFAULT
	setvar VAR_MAHOGANY_TOWN_STATE, 15
    setrespawn HEAL_LOCATION_MAHOGANY_TOWN_HNS
    call_if_eq VAR_NUM_BADGES, 7, MahoganyTown_Gym_EventScript_SetupElmRocketCall
	closemessage
	release
	end

MahoganyTown_Gym_EventScript_SetupElmRocketCall::
    setvar VAR_TRIGGER_ELM_ROCKET_CALL, 1
    return

MahoganyTown_Gym_EventScript_OlivineCheckCianwood::
	goto_if_set FLAG_DEFEATED_CIANWOOD_GYM, MahoganyTown_Gym_EventScript_Pryce_Battle3
	goto MahoganyTown_Gym_EventScript_Pryce_Battle2

MahoganyTown_Gym_EventScript_CianwoodCheckOlivine::
	goto_if_set FLAG_DEFEATED_OLIVINE_CITY_GYM, MahoganyTown_Gym_EventScript_Pryce_Battle3
	goto MahoganyTown_Gym_EventScript_Pryce_Battle2
	
MahoganyTown_Gym_EventScript_Pryce_Battle1::
	trainerbattle_no_intro TRAINER_PRYCE_1_HNS, MahoganyTown_Gym_Text_PryceImpressed
	goto MahoganyTown_Gym_EventScript_PryceVictory

MahoganyTown_Gym_EventScript_Pryce_Battle2::
	trainerbattle_no_intro TRAINER_PRYCE_1_2_HNS, MahoganyTown_Gym_Text_PryceImpressed
	goto MahoganyTown_Gym_EventScript_PryceVictory

MahoganyTown_Gym_EventScript_Pryce_Battle3::
	trainerbattle_no_intro TRAINER_PRYCE_1_3_HNS, MahoganyTown_Gym_Text_PryceImpressed
	goto MahoganyTown_Gym_EventScript_PryceVictory

MahoganyTown_Gym_EventScript_Pryce_Defeated::
	msgbox MahoganyTown_Gym_Text_CherishPokemon, MSGBOX_DEFAULT
	closemessage
	release
	end

MahoganyTown_Gym_Text_PryceIntro:
    .string "Los POKéMON viven muchas cosas\n"
    .string "en su vida, igual que nosotros.\p"
    .string "Yo también he visto y sufrido\n"
    .string "mucho en mi vida.\p"
    .string "Como soy mayor que tú, deja que\n"
    .string "te muestre a qué me refiero.\p"
    .string "He estado con POKéMON desde\n"
    .string "antes de que nacieras.\p"
    .string "No pierdo fácilmente.\p"
    .string "Yo, PRYCE, el entrenador del invierno\n"
    .string "¡Demostraré mi poder!$"

MahoganyTown_Gym_Text_PryceImpressed:
    .string "Ah, estoy impresionado por tu\n"
    .string "destreza.\p"
    .string "Con tu voluntad, sé que\n"
    .string "superarás todo obstáculo.\p"
    .string "¡Eres digno de esta MEDALLA!$"

MahoganyTown_Gym_Text_ReceivedBadge:
    .string "{PLAYER} recibió la MEDALLA GLACIAR.$"

MahoganyTown_Gym_Text_GlacierBadgeSpeech:
    .string "Esa MEDALLA subirá el ATAQUE\n"
    .string "ESPECIAL de tus POKéMON.\p"
    .string "También permite que tus POKéMON\n"
    .string "usen REMOLINO para cruzar\l"
    .string "remolinos reales.\p"
    .string "Y esto... ¡Es un regalo mío!$"

MahoganyTown_Gym_Text_HailSpeech:
    .string "Esa MT contiene GRANIZO.\p"
    .string "Causa daño cada\n"
    .string "turno durante 5 turnos.\p"
    .string "Demuestra la dureza\n"
    .string "del invierno.$"

MahoganyTown_Gym_Text_CherishPokemon:
    .string "Cuando el hielo y la nieve\n"
    .string "se derriten, llega la primavera.\p"
    .string "Tú y tu POKéMON estarán\n"
    .string "juntos por muchos años más.\p"
    .string "¡Valoren su tiempo juntos!$"

MahoganyTown_Gym_Text_PryceRematch:
    .string "¡Ah, CAMPEÓN DE JOHTO!\p"
    .string "Tus habilidades son\n"
    .string "notables.\p"
    .string "Estoy impresionado.\p"
    .string "Pero aún hay mucho que\n"
    .string "aprender el uno del otro.\p"
    .string "Yo, PRYCE, el entrenador del invierno\n"
    .string "aún me quedan algunos trucos.\p"
    .string "¿Quieres otra revancha conmigo?$"

MahoganyTown_Gym_Text_PryceRematchDefeat:
    .string "Ah, otra vez me impresiona\n"
    .string "tu destreza.\p"
    .string "Con tu voluntad, sé que\n"
    .string "superará todo obstáculo de la vida.$"

MahoganyTown_Gym_Text_Guide:
    .string "PRYCE es un veterano que ha\n"
    .string "entrenado POKéMON por 50 años.\p"
    .string "Tiene un equipo sólido de\n"
    .string "POKéMON para cubrir cualquier\l"
    .string "cosa que traigas.\p"
    .string "El fuego es un buen inicio,\n"
    .string "¡pero cuidado con la lluvia!$"

MahoganyTown_Gym_Text_GuideWin:
    .string "PRYCE es bueno, ¡pero tú\n"
    .string "estás a otro nivel!\p"
    .string "¡Fue una batalla intensa que\n"
    .string "unió a dos generaciones!$"

MahoganyTown_Gym_Text_BoarderRonaldSeen:
    .string "¡Congelaré a tus POKéMON\n"
    .string "para que no puedas hacer nada!$"

MahoganyTown_Gym_Text_BoarderRonaldBeaten:
    .string "Maldición. No pude hacer nada.$"

MahoganyTown_Gym_Text_BoarderRonaldAfter:
    .string "Creo que hay un movimiento a\n"
    .string "El POKéMON puede usarlo aunque\l"
    .string "esté congelado.$"

MahoganyTown_Gym_Text_BoarderBradSeen:
    .string "El suelo del GIMNASIO resbala.\p"
    .string "Es divertido, ¿verdad?\p"
    .string "Pero oye, ¡no hemos venido a\n"
    .string "jugar aquí!$"

MahoganyTown_Gym_Text_BoarderBradBeaten:
    .string "¿Ves lo serios que somos?$"

MahoganyTown_Gym_Text_BoarderBradAfter:
    .string "Este GIMNASIO es genial.\n"
    .string "Me encanta deslizarme con mi\l"
    .string "POKéMON!$"

MahoganyTown_Gym_Text_BoarderDouglasSeen:
    .string "Conozco el secreto de PRYCE.$"

MahoganyTown_Gym_Text_BoarderDouglasBeaten:
    .string "Bien. Te contaré el secreto de PRYCE.$"

MahoganyTown_Gym_Text_BoarderDouglasAfter:
    .string "El secreto del poder de PRYCE...\p"
    .string "Él medita bajo una cascada\n"
    .string "a diario para fortalecer su mente\l"
    .string "y su cuerpo.$"

MahoganyTown_Gym_Text_SkierRoxanneSeen:
    .string "Para llegar a PRYCE, el LÍDER de\n"
    .string "GIMNASIO, piensa antes de esquiar.$"

MahoganyTown_Gym_Text_SkierRoxanneBeaten:
    .string "¡No te ganaría en esquí!$"

MahoganyTown_Gym_Text_SkierRoxanneAfter:
    .string "Si no esquías con precisión,\n"
    .string "no llegarás lejos en este GIMNASIO.$"

MahoganyTown_Gym_Text_SkierClarissaSeen:
	.string "¡Mira mi giro paralelo!$"

MahoganyTown_Gym_Text_SkierClarissaBeaten:
	.string "¡No! ¡Me hiciste caer!$"

MahoganyTown_Gym_Text_SkierClarissaAfter:
    .string "No debí presumir\n"
    .string "de mi forma de esquiar...$"

