LavaridgeTown_Gym_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, LavaridgeTown_Gym_1F_OnTransition
	.byte 0

LavaridgeTown_Gym_1F_OnTransition:
	call LavaridgeTown_Gym_1F_EventScript_SetTrainerTempVars
	call LavaridgeTown_Gym_1F_EventScript_CheckBuryTrainers
	end

@ Unclear where/if these temp vars are getting checked
LavaridgeTown_Gym_1F_EventScript_SetTrainerTempVars::
	setvar VAR_TEMP_B, 0
	setvar VAR_TEMP_C, 0
	setvar VAR_TEMP_D, 0
	setvar VAR_TEMP_E, 0
	setvar VAR_TEMP_F, 0
	goto_if_defeated TRAINER_COLE, LavaridgeTown_Gym_1F_EventScript_SetGeraldTempVar
	setvar VAR_TEMP_B, 1
LavaridgeTown_Gym_1F_EventScript_SetGeraldTempVar::
	goto_if_defeated TRAINER_GERALD, LavaridgeTown_Gym_1F_EventScript_SetAxleTempVar
	setvar VAR_TEMP_C, 1
LavaridgeTown_Gym_1F_EventScript_SetAxleTempVar::
	goto_if_defeated TRAINER_AXLE, LavaridgeTown_Gym_1F_EventScript_SetDanielleTempVar
	setvar VAR_TEMP_D, 1
LavaridgeTown_Gym_1F_EventScript_SetDanielleTempVar::
	goto_if_defeated TRAINER_DANIELLE, LavaridgeTown_Gym_1F_EventScript_EndSetTrainerTempVars
	setvar VAR_TEMP_E, 1
LavaridgeTown_Gym_1F_EventScript_EndSetTrainerTempVars::
	return

LavaridgeTown_Gym_1F_EventScript_CheckBuryTrainers::
	goto_if_defeated TRAINER_COLE, LavaridgeTown_Gym_1F_EventScript_CheckBuryGerald
	setobjectmovementtype LOCALID_COLE, MOVEMENT_TYPE_BURIED
LavaridgeTown_Gym_1F_EventScript_CheckBuryGerald::
	goto_if_defeated TRAINER_GERALD, LavaridgeTown_Gym_1F_EventScript_CheckBuryAxle
	setobjectmovementtype LOCALID_GERALD, MOVEMENT_TYPE_BURIED
LavaridgeTown_Gym_1F_EventScript_CheckBuryAxle::
	goto_if_defeated TRAINER_AXLE, LavaridgeTown_Gym_1F_EventScript_CheckBuryDanielle
	setobjectmovementtype LOCALID_AXLE, MOVEMENT_TYPE_BURIED
LavaridgeTown_Gym_1F_EventScript_CheckBuryDanielle::
	goto_if_defeated TRAINER_DANIELLE, LavaridgeTown_Gym_1F_EventScript_EndCheckBuryTrainers
	setobjectmovementtype LOCALID_DANIELLE, MOVEMENT_TYPE_BURIED
LavaridgeTown_Gym_1F_EventScript_EndCheckBuryTrainers::
	return

LavaridgeTown_Gym_1F_EventScript_Flannery::
	trainerbattle_single TRAINER_FLANNERY_1, LavaridgeTown_Gym_1F_Text_FlanneryIntro, LavaridgeTown_Gym_1F_Text_FlanneryDefeat, LavaridgeTown_Gym_1F_EventScript_FlanneryDefeated, NO_MUSIC
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, LavaridgeTown_Gym_1F_EventScript_FlanneryRematch
	goto_if_unset FLAG_RECEIVED_TM_OVERHEAT, LavaridgeTown_Gym_1F_EventScript_GiveOverheat2
	msgbox LavaridgeTown_Gym_1F_Text_FlanneryPostBattle, MSGBOX_DEFAULT
	release
	end

LavaridgeTown_Gym_1F_EventScript_FlanneryDefeated::
	message LavaridgeTown_Gym_1F_Text_ReceivedHeatBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox LavaridgeTown_Gym_1F_Text_ExplainHeatBadgeTakeThis, MSGBOX_DEFAULT
	setflag FLAG_WHITEOUT_TO_LAVARIDGE
	setflag FLAG_DEFEATED_LAVARIDGE_GYM
	setflag FLAG_BADGE04_GET
	addvar VAR_PETALBURG_GYM_STATE, 1
	call_if_eq VAR_PETALBURG_GYM_STATE, 6, Common_EventScript_ReadyPetalburgGymForBattle
	setvar VAR_0x8008, 4
	call Common_EventScript_SetGymTrainers
	setflag FLAG_HIDE_VERDANTURF_TOWN_WANDAS_HOUSE_WALLY
	setvar VAR_LAVARIDGE_TOWN_STATE, 1
	call LavaridgeTown_Gym_1F_EventScript_GiveOverheat
	closemessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox LavaridgeTown_Gym_1F_Text_RegisteredFlannery, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_FLANNERY_MATCH_CALL
	release
	end

LavaridgeTown_Gym_1F_EventScript_GiveOverheat2::
	giveitem ITEM_TM_OVERHEAT
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	msgbox LavaridgeTown_Gym_1F_Text_ExplainOverheat, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM_OVERHEAT
	release
	end

LavaridgeTown_Gym_1F_EventScript_GiveOverheat::
	giveitem ITEM_TM_OVERHEAT
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_BagIsFull
	msgbox LavaridgeTown_Gym_1F_Text_ExplainOverheat, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM_OVERHEAT
	return

LavaridgeTown_Gym_1F_EventScript_FlanneryRematch::
	trainerbattle_rematch_double TRAINER_FLANNERY_1, LavaridgeTown_Gym_1F_Text_FlanneryPreRematch, LavaridgeTown_Gym_1F_Text_FlanneryRematchDefeat, LavaridgeTown_Gym_1F_Text_FlanneryRematchNeedTwoMons
	msgbox LavaridgeTown_Gym_1F_Text_FlanneryPostRematch, MSGBOX_AUTOCLOSE
	end

LavaridgeTown_Gym_1F_EventScript_Cole::
	trainerbattle TRAINER_BATTLE_CONTINUE_SCRIPT, LOCALID_COLE, TRAINER_COLE, LavaridgeTown_Gym_1F_Text_ColeIntro, LavaridgeTown_Gym_1F_Text_ColeDefeat, LavaridgeTown_Gym_EventScript_CheckTrainerScript, OBJ_ID_NONE, TRAINER_NONE, NULL, NULL, NULL, NULL, NULL, FALSE, TRUE, FALSE, FALSE
	msgbox LavaridgeTown_Gym_1F_Text_ColePostBattle, MSGBOX_AUTOCLOSE
	end

LavaridgeTown_Gym_EventScript_CheckTrainerScript::
	call LavaridgeTown_Gym_1F_EventScript_SetTrainerTempVars
	release
	special ShouldTryGetTrainerScript
	goto_if_eq VAR_RESULT, 1, EventScript_GotoTrainerScript
	end

LavaridgeTown_Gym_1F_EventScript_Axle::
	trainerbattle TRAINER_BATTLE_CONTINUE_SCRIPT, LOCALID_AXLE, TRAINER_AXLE, LavaridgeTown_Gym_1F_Text_AxleIntro, LavaridgeTown_Gym_1F_Text_AxleDefeat, LavaridgeTown_Gym_EventScript_CheckTrainerScript, OBJ_ID_NONE, TRAINER_NONE, NULL, NULL, NULL, NULL, NULL, FALSE, TRUE, FALSE, FALSE
	msgbox LavaridgeTown_Gym_1F_Text_AxlePostBattle, MSGBOX_AUTOCLOSE
	end

LavaridgeTown_Gym_B1F_EventScript_Keegan::
	trainerbattle TRAINER_BATTLE_CONTINUE_SCRIPT, LOCALID_KEEGAN, TRAINER_KEEGAN, LavaridgeTown_Gym_B1F_Text_KeeganIntro, LavaridgeTown_Gym_B1F_Text_KeeganDefeat, LavaridgeTown_Gym_EventScript_CheckTrainerScript, OBJ_ID_NONE, TRAINER_NONE, NULL, NULL, NULL, NULL, NULL, FALSE, TRUE, FALSE, FALSE
	msgbox LavaridgeTown_Gym_B1F_Text_KeeganPostBattle, MSGBOX_AUTOCLOSE
	end

LavaridgeTown_Gym_1F_EventScript_Danielle::
	trainerbattle TRAINER_BATTLE_CONTINUE_SCRIPT, LOCALID_DANIELLE, TRAINER_DANIELLE, LavaridgeTown_Gym_1F_Text_DanielleIntro, LavaridgeTown_Gym_1F_Text_DanielleDefeat, LavaridgeTown_Gym_EventScript_CheckTrainerScript, OBJ_ID_NONE, TRAINER_NONE, NULL, NULL, NULL, NULL, NULL, FALSE, TRUE, FALSE, FALSE
	msgbox LavaridgeTown_Gym_1F_Text_DaniellePostBattle, MSGBOX_AUTOCLOSE
	end

LavaridgeTown_Gym_1F_EventScript_Gerald::
	trainerbattle TRAINER_BATTLE_CONTINUE_SCRIPT, LOCALID_GERALD, TRAINER_GERALD, LavaridgeTown_Gym_1F_Text_GeraldIntro, LavaridgeTown_Gym_1F_Text_GeraldDefeat, LavaridgeTown_Gym_EventScript_CheckTrainerScript, OBJ_ID_NONE, TRAINER_NONE, NULL, NULL, NULL, NULL, NULL, FALSE, TRUE, FALSE, FALSE
	msgbox LavaridgeTown_Gym_1F_Text_GeraldPostBattle, MSGBOX_AUTOCLOSE
	end

LavaridgeTown_Gym_B1F_EventScript_Jace::
	trainerbattle TRAINER_BATTLE_CONTINUE_SCRIPT, LOCALID_JACE, TRAINER_JACE, LavaridgeTown_Gym_B1F_Text_JaceIntro, LavaridgeTown_Gym_B1F_Text_JaceDefeat, LavaridgeTown_Gym_EventScript_CheckTrainerScript, OBJ_ID_NONE, TRAINER_NONE, NULL, NULL, NULL, NULL, NULL, FALSE, TRUE, FALSE, FALSE
	msgbox LavaridgeTown_Gym_B1F_Text_JacePostBattle, MSGBOX_AUTOCLOSE
	end

LavaridgeTown_Gym_B1F_EventScript_Jeff::
	trainerbattle TRAINER_BATTLE_CONTINUE_SCRIPT, LOCALID_JEFF, TRAINER_JEFF, LavaridgeTown_Gym_B1F_Text_JeffIntro, LavaridgeTown_Gym_B1F_Text_JeffDefeat, LavaridgeTown_Gym_EventScript_CheckTrainerScript, OBJ_ID_NONE, TRAINER_NONE, NULL, NULL, NULL, NULL, NULL, FALSE, TRUE, FALSE, FALSE
	msgbox LavaridgeTown_Gym_B1F_Text_JeffPostBattle, MSGBOX_AUTOCLOSE
	end

LavaridgeTown_Gym_B1F_EventScript_Eli::
	trainerbattle TRAINER_BATTLE_CONTINUE_SCRIPT, LOCALID_ELI, TRAINER_ELI, LavaridgeTown_Gym_B1F_Text_EliIntro, LavaridgeTown_Gym_B1F_Text_EliDefeat, LavaridgeTown_Gym_EventScript_CheckTrainerScript, OBJ_ID_NONE, TRAINER_NONE, NULL, NULL, NULL, NULL, NULL, FALSE, TRUE, FALSE, FALSE
	msgbox LavaridgeTown_Gym_B1F_Text_EliPostBattle, MSGBOX_AUTOCLOSE
	end

LavaridgeTown_Gym_1F_EventScript_GymGuide::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_LAVARIDGE_GYM, LavaridgeTown_Gym_1F_EventScript_GymGuidePostVictory
	msgbox LavaridgeTown_Gym_1F_Text_GymGuideAdvice, MSGBOX_DEFAULT
	release
	end

LavaridgeTown_Gym_1F_EventScript_GymGuidePostVictory::
	msgbox LavaridgeTown_Gym_1F_Text_GymGuidePostVictory, MSGBOX_DEFAULT
	release
	end

LavaridgeTown_Gym_1F_EventScript_LeftGymStatue::
	lockall
	goto_if_set FLAG_BADGE04_GET, LavaridgeTown_Gym_1F_EventScript_GymStatueCertified
	goto LavaridgeTown_Gym_1F_EventScript_GymStatue
	end

LavaridgeTown_Gym_1F_EventScript_RightGymStatue::
	lockall
	goto_if_set FLAG_BADGE04_GET, LavaridgeTown_Gym_1F_EventScript_GymStatueCertified
	goto LavaridgeTown_Gym_1F_EventScript_GymStatue
	end

LavaridgeTown_Gym_1F_EventScript_GymStatueCertified::
	msgbox LavaridgeTown_Gym_1F_Text_GymStatueCertified, MSGBOX_DEFAULT
	releaseall
	end

LavaridgeTown_Gym_1F_EventScript_GymStatue::
	msgbox LavaridgeTown_Gym_1F_Text_GymStatue, MSGBOX_DEFAULT
	releaseall
	end

LavaridgeTown_Gym_1F_Text_GymGuideAdvice:
	.string "Hola, ¿cómo va todo, futuro\n"
	.string "CAMPEÓN {PLAYER}?\p"
	.string "FLANNERY, LÍDER DEL GIMNASIO\n"
	.string "usa POKéMON tipo FUEGO.\p"
	.string "Su pasión por los POKéMON arde más\n"
	.string "y fuerte que un volcán.\p"
	.string "¡No te acerques o te quemarás!\n"
	.string "¡Échale agua y luego\l"
	.string "ve a por ella!$"

LavaridgeTown_Gym_1F_Text_GymGuidePostVictory:
	.string "¡Vaya! ¡Qué batalla tan ardiente!$"

LavaridgeTown_Gym_1F_Text_ColeIntro:
	.string "¡Ay ay ay ay ay!\n"
	.string "¡Cielos, quema!$"

LavaridgeTown_Gym_1F_Text_ColeDefeat:
	.string "I'm blinded by sweat in my eyes…$"

LavaridgeTown_Gym_1F_Text_ColePostBattle:
	.string "Enterrarse en arena caliente ayuda\n"
	.string "circulación.\p"
	.string "Es eficaz para aliviar el dolor en\n"
	.string "tus articulaciones.$"

LavaridgeTown_Gym_1F_Text_AxleIntro:
	.string "Intento aliviar mi estrés.\n"
	.string "¡No vengas a estresarme más!$"

LavaridgeTown_Gym_1F_Text_AxleDefeat:
	.string "I hope FLANNERY flames you good!$"

LavaridgeTown_Gym_1F_Text_AxlePostBattle:
	.string "Haaah… Uff…\p"
	.string "Si pasas mucho tiempo enterrado en\n"
	.string "arena caliente, te agotas…$"

LavaridgeTown_Gym_B1F_Text_KeeganIntro:
	.string "Ya debes de estar cansado.\n"
	.string "Te gustaría descansar en la arena\l"
	.string "caliente, ¿verdad?\p"
	.string "Pero debes saber que mantener\n"
	.string "tu voluntad es una habilidad\l"
	.string "clave para todo ENTRENADOR.$"

LavaridgeTown_Gym_B1F_Text_KeeganDefeat:
	.string "Juega con fuego y te quemarás…$"

LavaridgeTown_Gym_B1F_Text_KeeganPostBattle:
	.string "Tu habilidad es real…\n"
	.string "Pero nuestra LÍDER FLANNERY es fuerte.\p"
	.string "Si no tienes cuidado, podrías\n"
	.string "quemarte seriamente.$"

LavaridgeTown_Gym_1F_Text_GeraldIntro:
	.string "¿Podrán tus POKéMON resistir\n"
	.string "un calor de 392 grados?$"

LavaridgeTown_Gym_1F_Text_GeraldDefeat:
	.string "It didn't burn hotly enough…$"

LavaridgeTown_Gym_1F_Text_GeraldPostBattle:
	.string "La temperatura del magma es\n"
	.string "392 grados.\p"
	.string "Tu POKéMON me venció, así que\n"
	.string "sobrevivirá fácil en el magma.$"

LavaridgeTown_Gym_1F_Text_DanielleIntro:
	.string "Um…\n"
	.string "Está bien, lucharé contigo.$"

LavaridgeTown_Gym_1F_Text_DanielleDefeat:
	.string "Oh, but you're too strong.$"

LavaridgeTown_Gym_1F_Text_DaniellePostBattle:
	.string "Seré una ENTRENADORA linda y\n"
	.string "fuerte como FLANNERY.$"

LavaridgeTown_Gym_B1F_Text_JaceIntro:
	.string "¡Vamos, date prisa!\n"
	.string "¡Luchemos antes de que me enfríe!$"

LavaridgeTown_Gym_B1F_Text_JaceDefeat:
	.string "Hace calor, pero mi corazón\n"
	.string "está congelado...$"

LavaridgeTown_Gym_B1F_Text_JacePostBattle:
	.string "La forma en que arde el espíritu\n"
	.string "así podrías tener una oportunidad\l"
	.string "contra nuestro LÍDER.$"

LavaridgeTown_Gym_B1F_Text_JeffIntro:
	.string "¿Ves cómo arden las llamas?\n"
	.string "¡Brillan anticipando mi victoria!$"

LavaridgeTown_Gym_B1F_Text_JeffDefeat:
	.string "Something didn't go right.$"

LavaridgeTown_Gym_B1F_Text_JeffPostBattle:
	.string "Bueno, ¿y qué? ¡Digo, ¿y qué?\n"
	.string "¡Puedo caminar sobre brasas!\p"
	.string "…¡Ni se te ocurra intentarlo!$"

LavaridgeTown_Gym_B1F_Text_EliIntro:
	.string "Aunque amo las montañas,\n"
	.string "amo especialmente los volcanes.$"

LavaridgeTown_Gym_B1F_Text_EliDefeat:
	.string "Bueno, parece que perdí sin\n"
	.string "haber tenido el control.$"

LavaridgeTown_Gym_B1F_Text_EliPostBattle:
	.string "Me quedé aquí porque me volví fan\n"
	.string "del poder de FLANNERY.\p"
	.string "Jejejeje.$"

LavaridgeTown_Gym_1F_Text_FlanneryIntro:
	.string "Bienvenido... No, espera.\p"
	.string "Pobre ENTRENADOR, ¡qué bueno que\n"
	.string "hayas llegado!\p"
	.string "Se me ha confiado el...\n"
	.string "No, espera.\p"
	.string "¡Soy FLANNERY, la LÍDER del\n"
	.string "GIMNASIO de aquí!\p"
	.string "Uh…\n"
	.string "¡No me subestimes aunque lleve\l"
	.string "poco tiempo como LÍDER!\p"
	.string "Con las habilidades de mi abue-\n"
	.string "lo, voy a... demostrar los\l"
	.string "movimientos que pulimos aquí!$"

LavaridgeTown_Gym_1F_Text_FlanneryDefeat:
	.string "Oh…\n"
	.string "Creo que me esforcé demasiado...\p"
	.string "Yo... hace poco que soy\n"
	.string "LÍDER de GIMNASIO.\p"
	.string "Intenté ser alguien que\n"
	.string "no soy.\p"
	.string "Debo hacer las cosas a mi modo. Si\n"
	.string "no, mis POKéMON se confundirán.\p"
	.string "Gracias por enseñarme eso.\n"
	.string "Por eso, mereces esto.$"

LavaridgeTown_Gym_1F_Text_ReceivedHeatBadge:
	.string "{PLAYER} recibió la MEDALLA CALOR\n"
	.string "de FLANNERY.$"

LavaridgeTown_Gym_1F_Text_ExplainHeatBadgeTakeThis:
	.string "Con la MEDALLA CALOR, los POKéMON\n"
	.string "hasta el nivel 50, incluso los de\l"
	.string "intercambio, te obedecerán\l"
	.string "completamente.\p"
	.string "Y permite usar la MO\n"
	.string "POKéMON usen FUERZA fuera de combate.\p"
	.string "Es una muestra de mi gratitud.\n"
	.string "¡No tengas pena en aceptarla!$"

LavaridgeTown_Gym_1F_Text_ExplainOverheat:
	.string "Esa MT50 contiene SOBRECALENTAR.\p"
	.string "Ese movimiento inflige un daño\n"
	.string "grave al rival.\p"
	.string "Pero también reduce drásticamente el\n"
	.string "del POKéMON que lo usa. Puede que no\l"
	.string "será útil en batallas largas.$"

LavaridgeTown_Gym_1F_Text_RegisteredFlannery:
	.string "LÍDER de GIMNASIO FLANNERY registrado\n"
	.string "en el POKéNAV.$"

LavaridgeTown_Gym_1F_Text_FlanneryPostBattle:
	.string "Tu poder me recuerda a alguien...\p"
	.string "¡Ah! ¡Ya sé! Peleas como NORMAN,\n"
	.string "el LÍDER de PETALBURG.$"

LavaridgeTown_Gym_1F_Text_GymStatue:
	.string "LAVARIDGE TOWN POKéMON GYM$"

LavaridgeTown_Gym_1F_Text_GymStatueCertified:
	.string "GIMNASIO POKéMON de PUEBLO LAVARIDGE\p"
	.string "ENTRENADORES CERTIFICADOS DE FLANNERY:\n"
	.string "{PLAYER}$"

LavaridgeTown_Gym_1F_Text_FlanneryPreRematch:
	.string "FLANNERY: Perder una batalla no me\n"
	.string "desanimará.\p"
	.string "Amo a los POKéMON.\n"
	.string "Amo combatir.\l"
	.string "Y... ¡amo este GIMNASIO!\p"
	.string "¡Intercambiemos movimientos\n"
	.string "geniales en otra batalla!$"

LavaridgeTown_Gym_1F_Text_FlanneryRematchDefeat:
	.string "¡Uff!\n"
	.string "¡Estoy a punto de erupcionar!$"

LavaridgeTown_Gym_1F_Text_FlanneryPostRematch:
	.string "FLANNERY: Perdí el combate,\n"
	.string "pero estoy muy satisfecha.\p"
	.string "No es común disfrutar una batalla\n"
	.string "tan ardiente.\p"
	.string "¡Tengamos otra así\n"
	.string "en algún momento!$"

LavaridgeTown_Gym_1F_Text_FlanneryRematchNeedTwoMons:
	.string "FLANNERY: Perder una batalla no me\n"
	.string "desanimará.\p"
	.string "Amo a los POKéMON.\n"
	.string "Amo combatir.\l"
	.string "Y... ¡amo este GIMNASIO!\p"
	.string "¡Intercambiemos movimientos\n"
	.string "¡en otra batalla!\p"
	.string "Oh, espera. ¿Solo tienes un POKéMON\n"
	.string "que pueda luchar?\p"
	.string "Lamento decir esto, pero cuando vengas\n"
	.string "a verme, trae al menos dos POKéMON.$"
