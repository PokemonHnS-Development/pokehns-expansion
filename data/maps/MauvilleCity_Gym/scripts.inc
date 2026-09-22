MauvilleCity_Gym_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, MauvilleCity_Gym_OnLoad
	.byte 0

MauvilleCity_Gym_OnLoad:
	goto_if_set FLAG_DEFEATED_MAUVILLE_GYM, MauvilleCity_Gym_EventScript_DeactivatePuzzle
	switch VAR_MAUVILLE_GYM_STATE
	case 0, MauvilleCity_Gym_EventScript_UpdateBarriers
	case 1, MauvilleCity_Gym_EventScript_Switch1Pressed
	case 2, MauvilleCity_Gym_EventScript_Switch2Pressed
	case 3, MauvilleCity_Gym_EventScript_Switch3Pressed
	case 4, MauvilleCity_Gym_EventScript_Switch4Pressed
	end

MauvilleCity_Gym_EventScript_UpdateBarriers::
	goto_if_set FLAG_MAUVILLE_GYM_BARRIERS_STATE, MauvilleCity_Gym_EventScript_SetAltBarriers
	end

MauvilleCity_Gym_EventScript_SetAltBarriers::
	setmetatile 3, 11, METATILE_MauvilleGym_RedBeamV1_On, TRUE
	setmetatile 3, 12, METATILE_MauvilleGym_RedBeamV2_On, TRUE
	setmetatile 3, 13, METATILE_MauvilleGym_PoleTop_On, TRUE
	setmetatile 4, 10, METATILE_MauvilleGym_RedBeamH1_On, FALSE
	setmetatile 5, 10, METATILE_MauvilleGym_RedBeamH2_On, FALSE
	setmetatile 4, 11, METATILE_MauvilleGym_RedBeamH3_On, TRUE
	setmetatile 5, 11, METATILE_MauvilleGym_RedBeamH4_On, TRUE
	setmetatile 7, 10, METATILE_MauvilleGym_RedBeamH1_On, FALSE
	setmetatile 8, 10, METATILE_MauvilleGym_RedBeamH2_On, FALSE
	setmetatile 7, 11, METATILE_MauvilleGym_RedBeamH3_On, TRUE
	setmetatile 8, 11, METATILE_MauvilleGym_RedBeamH4_On, TRUE
	setmetatile 4, 13, METATILE_MauvilleGym_GreenBeamH1_Off, FALSE
	setmetatile 5, 13, METATILE_MauvilleGym_GreenBeamH2_Off, FALSE
	setmetatile 4, 14, METATILE_MauvilleGym_GreenBeamH3_Off, FALSE
	setmetatile 5, 14, METATILE_MauvilleGym_GreenBeamH4_Off, FALSE
	setmetatile 1, 10, METATILE_MauvilleGym_GreenBeamH1_Off, FALSE
	setmetatile 2, 10, METATILE_MauvilleGym_GreenBeamH2_Off, FALSE
	setmetatile 1, 11, METATILE_MauvilleGym_GreenBeamH3_Off, FALSE
	setmetatile 2, 11, METATILE_MauvilleGym_GreenBeamH4_Off, FALSE
	setmetatile 6, 8, METATILE_MauvilleGym_PoleBottom_On, TRUE
	setmetatile 6, 9, METATILE_MauvilleGym_FloorTile, FALSE
	setmetatile 6, 10, METATILE_MauvilleGym_PoleTop_Off, FALSE
	setmetatile 4, 6, METATILE_MauvilleGym_GreenBeamH1_Off, FALSE
	setmetatile 5, 6, METATILE_MauvilleGym_GreenBeamH2_Off, FALSE
	setmetatile 4, 7, METATILE_MauvilleGym_GreenBeamH3_Off, FALSE
	setmetatile 5, 7, METATILE_MauvilleGym_GreenBeamH4_Off, FALSE
	end

MauvilleCity_Gym_EventScript_Switch1Pressed::
	setvar VAR_0x8004, 0
	special MauvilleGymPressSwitch
	goto MauvilleCity_Gym_EventScript_UpdateBarriers
	end

MauvilleCity_Gym_EventScript_Switch2Pressed::
	setvar VAR_0x8004, 1
	special MauvilleGymPressSwitch
	goto MauvilleCity_Gym_EventScript_UpdateBarriers
	end

MauvilleCity_Gym_EventScript_Switch3Pressed::
	setvar VAR_0x8004, 2
	special MauvilleGymPressSwitch
	goto MauvilleCity_Gym_EventScript_UpdateBarriers
	end

MauvilleCity_Gym_EventScript_Switch4Pressed::
	setvar VAR_0x8004, 3
	special MauvilleGymPressSwitch
	goto MauvilleCity_Gym_EventScript_UpdateBarriers
	end

MauvilleCity_Gym_EventScript_DeactivatePuzzle::
	special MauvilleGymDeactivatePuzzle
	end

MauvilleCity_Gym_EventScript_Wattson::
	trainerbattle_single TRAINER_WATTSON_1, MauvilleCity_Gym_Text_WattsonIntro, MauvilleCity_Gym_Text_WattsonDefeat, MauvilleCity_Gym_EventScript_WattsonDefeated, NO_MUSIC
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_Gym_EventScript_WattsonRematch
	goto_if_unset FLAG_RECEIVED_TM_SHOCK_WAVE, MauvilleCity_Gym_EventScript_GiveShockWave2
	goto_if_eq VAR_NEW_MAUVILLE_STATE, 2, MauvilleCity_Gym_EventScript_CompletedNewMauville
	msgbox MauvilleCity_Gym_Text_WattsonPostBattle, MSGBOX_DEFAULT
	release
	end

MauvilleCity_Gym_EventScript_WattsonDefeated::
	message MauvilleCity_Gym_Text_ReceivedDynamoBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox MauvilleCity_Gym_Text_ExplainDynamoBadgeTakeThis, MSGBOX_DEFAULT
	setvar VAR_SLATEPORT_OUTSIDE_MUSEUM_STATE, 3
	clearflag FLAG_HIDE_VERDANTURF_TOWN_SCOTT
	setflag FLAG_DEFEATED_MAUVILLE_GYM
	setflag FLAG_BADGE03_GET
	addvar VAR_PETALBURG_GYM_STATE, 1
	call_if_eq VAR_PETALBURG_GYM_STATE, 6, Common_EventScript_ReadyPetalburgGymForBattle
	setvar VAR_0x8008, 3
	call Common_EventScript_SetGymTrainers
	special MauvilleGymDeactivatePuzzle
	special DrawWholeMapView
	playse SE_UNLOCK
	call MauvilleCity_Gym_EventScript_GiveShockWave
	closemessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox MauvilleCity_Gym_Text_RegisteredWattson, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_WATTSON_MATCH_CALL
	release
	end

MauvilleCity_Gym_EventScript_GiveShockWave2::
	giveitem ITEM_TM_SHOCK_WAVE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	msgbox MauvilleCity_Gym_Text_ExplainShockWave, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM_SHOCK_WAVE
	release
	end

MauvilleCity_Gym_EventScript_GiveShockWave::
	giveitem ITEM_TM_SHOCK_WAVE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_BagIsFull
	msgbox MauvilleCity_Gym_Text_ExplainShockWave, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM_SHOCK_WAVE
	return

MauvilleCity_Gym_EventScript_CompletedNewMauville::
	msgbox MauvilleCity_Gym_Text_WattsonGoForthAndEndeavor, MSGBOX_DEFAULT
	release
	end

MauvilleCity_Gym_EventScript_WattsonRematch::
	trainerbattle_rematch_double TRAINER_WATTSON_1, MauvilleCity_Gym_Text_WattsonPreRematch, MauvilleCity_Gym_Text_WattsonRematchDefeat, MauvilleCity_Gym_Text_WattsonRematchNeedTwoMons
	msgbox MauvilleCity_Gym_Text_WattsonPostRematch, MSGBOX_AUTOCLOSE
	end

MauvilleCity_Gym_EventScript_Switch1::
	lockall
	goto_if_set FLAG_DEFEATED_MAUVILLE_GYM, MauvilleCity_Gym_EventScript_SwitchDoNothing
	goto_if_eq VAR_MAUVILLE_GYM_STATE, 1, MauvilleCity_Gym_EventScript_SwitchDoNothing
	setvar VAR_MAUVILLE_GYM_STATE, 1
	setvar VAR_0x8004, 0
	goto MauvilleCity_Gym_EventScript_PressFloorSwitch
	end

MauvilleCity_Gym_EventScript_Switch2::
	lockall
	goto_if_set FLAG_DEFEATED_MAUVILLE_GYM, MauvilleCity_Gym_EventScript_SwitchDoNothing
	goto_if_eq VAR_MAUVILLE_GYM_STATE, 2, MauvilleCity_Gym_EventScript_SwitchDoNothing
	setvar VAR_MAUVILLE_GYM_STATE, 2
	setvar VAR_0x8004, 1
	goto MauvilleCity_Gym_EventScript_PressFloorSwitch
	end

MauvilleCity_Gym_EventScript_Switch3::
	lockall
	goto_if_set FLAG_DEFEATED_MAUVILLE_GYM, MauvilleCity_Gym_EventScript_SwitchDoNothing
	goto_if_eq VAR_MAUVILLE_GYM_STATE, 3, MauvilleCity_Gym_EventScript_SwitchDoNothing
	setvar VAR_MAUVILLE_GYM_STATE, 3
	setvar VAR_0x8004, 2
	goto MauvilleCity_Gym_EventScript_PressFloorSwitch
	end

MauvilleCity_Gym_EventScript_Switch4::
	lockall
	goto_if_set FLAG_DEFEATED_MAUVILLE_GYM, MauvilleCity_Gym_EventScript_SwitchDoNothing
	goto_if_eq VAR_MAUVILLE_GYM_STATE, 4, MauvilleCity_Gym_EventScript_SwitchDoNothing
	setvar VAR_MAUVILLE_GYM_STATE, 4
	setvar VAR_0x8004, 3
	goto MauvilleCity_Gym_EventScript_PressFloorSwitch
	end

MauvilleCity_Gym_EventScript_PressFloorSwitch::
	special MauvilleGymSetDefaultBarriers
	special MauvilleGymPressSwitch
	special DrawWholeMapView
	playse SE_UNLOCK
	goto_if_set FLAG_MAUVILLE_GYM_BARRIERS_STATE, MauvilleCity_Gym_EventScript_ClearBarriersAltState
	goto_if_unset FLAG_MAUVILLE_GYM_BARRIERS_STATE, MauvilleCity_Gym_EventScript_SetBarriersAltState
	releaseall
	end

MauvilleCity_Gym_EventScript_SwitchDoNothing::
	releaseall
	end

MauvilleCity_Gym_EventScript_SetBarriersAltState::
	setflag FLAG_MAUVILLE_GYM_BARRIERS_STATE
	releaseall
	end

MauvilleCity_Gym_EventScript_ClearBarriersAltState::
	clearflag FLAG_MAUVILLE_GYM_BARRIERS_STATE
	releaseall
	end

MauvilleCity_Gym_EventScript_Kirk::
	trainerbattle_single TRAINER_KIRK, MauvilleCity_Gym_Text_KirkIntro, MauvilleCity_Gym_Text_KirkDefeat
	msgbox MauvilleCity_Gym_Text_KirkPostBattle, MSGBOX_AUTOCLOSE
	end

MauvilleCity_Gym_EventScript_Shawn::
	trainerbattle_single TRAINER_SHAWN, MauvilleCity_Gym_Text_ShawnIntro, MauvilleCity_Gym_Text_ShawnDefeat
	msgbox MauvilleCity_Gym_Text_ShawnPostBattle, MSGBOX_AUTOCLOSE
	end

MauvilleCity_Gym_EventScript_Ben::
	trainerbattle_single TRAINER_BEN, MauvilleCity_Gym_Text_BenIntro, MauvilleCity_Gym_Text_BenDefeat
	msgbox MauvilleCity_Gym_Text_BenPostBattle, MSGBOX_AUTOCLOSE
	end

MauvilleCity_Gym_EventScript_Vivian::
	trainerbattle_single TRAINER_VIVIAN, MauvilleCity_Gym_Text_VivianIntro, MauvilleCity_Gym_Text_VivianDefeat
	msgbox MauvilleCity_Gym_Text_VivianPostBattle, MSGBOX_AUTOCLOSE
	end

MauvilleCity_Gym_EventScript_Angelo::
	trainerbattle_single TRAINER_ANGELO, MauvilleCity_Gym_Text_AngeloIntro, MauvilleCity_Gym_Text_AngeloDefeat
	msgbox MauvilleCity_Gym_Text_AngeloPostBattle, MSGBOX_AUTOCLOSE
	end

MauvilleCity_Gym_EventScript_GymGuide::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_MAUVILLE_GYM, MauvilleCity_Gym_EventScript_GymGuidePostVictory
	msgbox MauvilleCity_Gym_Text_GymGuideAdvice, MSGBOX_DEFAULT
	release
	end

MauvilleCity_Gym_EventScript_GymGuidePostVictory::
	msgbox MauvilleCity_Gym_Text_GymGuidePostVictory, MSGBOX_DEFAULT
	release
	end

MauvilleCity_Gym_EventScript_LeftGymStatue::
	lockall
	goto_if_set FLAG_BADGE03_GET, MauvilleCity_Gym_EventScript_GymStatueCertified
	goto MauvilleCity_Gym_EventScript_GymStatue
	end

MauvilleCity_Gym_EventScript_RightGymStatue::
	lockall
	goto_if_set FLAG_BADGE03_GET, MauvilleCity_Gym_EventScript_GymStatueCertified
	goto MauvilleCity_Gym_EventScript_GymStatue
	end

MauvilleCity_Gym_EventScript_GymStatueCertified::
	msgbox MauvilleCity_Gym_Text_GymStatueCertified, MSGBOX_DEFAULT
	releaseall
	end

MauvilleCity_Gym_EventScript_GymStatue::
	msgbox MauvilleCity_Gym_Text_GymStatue, MSGBOX_DEFAULT
	releaseall
	end

MauvilleCity_Gym_Text_GymGuideAdvice:
	.string "Hola, ¿cómo va todo, futuro\n"
	.string "CAMPEÓN {PLAYER}?\p"
	.string "WATTSON, el LÍDER del GIMNASIO\n"
	.string "de MALVALA, usa POKéMON ELÉCTRICOS.\p"
	.string "Si lo retas con POKéMON de tipo\n"
	.string "AGUA, ¡los electrocutará! ¡Bzzz!\p"
	.string "¡Y puso puertas con interruptores\n"
	.string "por todo el GIMNASIO! ¡Qué loco!\p"
	.string "¡Oye, ve a por ello!$"

MauvilleCity_Gym_Text_GymGuidePostVictory:
	.string "¡Vaya, eres electrizante!\n"
	.string "¡Diste energía para abrir la puerta!$"

MauvilleCity_Gym_Text_KirkIntro:
	.string "Mi alma eléctrica destrozará todos\n"
	.string "tus sueños, ¡whoa-yeahah!$"

MauvilleCity_Gym_Text_KirkDefeat:
	.string "Eso estaba conectado y amplificado,\n"
	.string "¡Electricidad al máximo, amigo!$"

MauvilleCity_Gym_Text_KirkPostBattle:
	.string "POKéMON y roca, ¡es cuestión de\n"
	.string "corazón, sí!$"

MauvilleCity_Gym_Text_ShawnIntro:
	.string "¡Entrené con WATTSON!\n"
	.string "¡No hay forma de que pierda fácil!$"

MauvilleCity_Gym_Text_ShawnDefeat:
	.string "Desconectado y apagado...$"

MauvilleCity_Gym_Text_ShawnPostBattle:
	.string "WATTSON, nuestro LÍDER de GIMNASIO,\n"
	.string "lleva aquí muchísimo tiempo.\p"
	.string "Luchaba incluso antes de que\n"
	.string "naciera tu padre, ¡ese viejo duro!$"

MauvilleCity_Gym_Text_BenIntro:
	.string "¡Este GIMNASIO tiene acertijos!\n"
	.string "¿No es divertido?$"

MauvilleCity_Gym_Text_BenDefeat:
	.string "Perder no es divertido...$"

MauvilleCity_Gym_Text_BenPostBattle:
	.string "WATTSON dice que le gusta poner\n"
	.string "trampas con interruptores.$"

MauvilleCity_Gym_Text_VivianIntro:
	.string "Con mi encanto y los ataques de mis\n"
	.string "POKéMON, ¡quedarás impactado!$"

MauvilleCity_Gym_Text_VivianDefeat:
	.string "¡Tu poder me sorprende!$"

MauvilleCity_Gym_Text_VivianPostBattle:
	.string "He oído que MALVILLAR fue fundada\n"
	.string "por WATTSON.\p"
	.string "Él era ENTRENADOR mucho antes de que\n"
	.string "nosotros lo fuéramos.\l"
	.string "¡Debe saber todo tipo de cosas!$"

MauvilleCity_Gym_Text_AngeloIntro:
	.string "I love shiny things!$"

MauvilleCity_Gym_Text_AngeloDefeat:
	.string "Oh...\n"
	.string "Mis ojos están agotados...$"

MauvilleCity_Gym_Text_AngeloPostBattle:
	.string "WATTSON del GIMNASIO de MALDITA\n"
	.string "la frente. ¡Me hace feliz!$"

MauvilleCity_Gym_Text_WattsonIntro:
	.string "alegría! He abandonado mis planes\nde convertir la ciudad, así es.\pPor\neso, dedico mi tiempo a crear\ntrampas en las puertas de mi GIMNASIO.\p\n¿Oh? ¿Y tú qué haces por aquí?\p¿Qué\ndices? ¿Que pasaste todas\nmis puertas trucadas?\p¡Jajajajaja!\n¡Eso sí que es divertido!\pEntonces, yo,\nWATTSON, el LÍDER de\nMAUVILLE GYM, ¡te electrocutaré!$"

MauvilleCity_Gym_Text_WattsonDefeat:
	.string "¡Jajajajaja!\n"
	.string "Está bien, ¡perdí!\p"
	.string "¡Al final me diste una emoción!\n"
	.string "¡Toma esta MEDALLA!$"

MauvilleCity_Gym_Text_ReceivedDynamoBadge:
	.string "{PLAYER} recibió la MEDALLA DINAMO\n"
	.string "de WATTSON.$"

MauvilleCity_Gym_Text_ExplainDynamoBadgeTakeThis:
	.string "Con la MEDALLA DINAMO, los POKéMON\n"
	.string "pueden usar ROMPER ROCAS fuera\p"
	.string "de combate. Además, hará que tus\n"
	.string "POKéMON sean un poco más rápidos.\p"
	.string "Hmm...\n"
	.string "¡También deberías llevarte esto!$"

MauvilleCity_Gym_Text_ExplainShockWave:
	.string "Esa MT34 contiene ONDA DE CHOQUE.\p"
	.string "¡Es un movimiento confiable que\n"
	.string "nunca falla! ¡Puedes contar con él!\p"
	.string "... ... ... ... ... ...$"

MauvilleCity_Gym_Text_RegisteredWattson:
	.string "LÍDER DE GIMNASIO WATTSON\n"
	.string "en el POKéNAV.$"

MauvilleCity_Gym_Text_WattsonPostBattle:
	.string "¡Me llena de optimismo ver a un\n"
	.string "joven ENTRENADOR como tú!$"

MauvilleCity_Gym_Text_WattsonGoForthAndEndeavor:
	.string "¡Jajajajaja!\n"
	.string "¡Sigue esforzándote, muchacho!$"

MauvilleCity_Gym_Text_GymStatue:
	.string "MAUVILLE CITY POKéMON GYM$"

MauvilleCity_Gym_Text_GymStatueCertified:
	.string "GIMNASIO POKéMON DE MALVALA\p"
	.string "ENTRENADORES DE WATTSON:\n"
	.string "{PLAYER}$"

MauvilleCity_Gym_Text_WattsonPreRematch:
	.string "WATTSON: ¡Ah-ja! ¡Al fin llegaste!\n"
	.string "Sé lo que quieres.\l"
	.string "¡Quieres luchar contra mis POKéMON!\p"
	.string "¡Wahajajaja!\p"
	.string "¡Haré que salten chispas de ti!\n"
	.string "¡No digas que no te advertí!$"

MauvilleCity_Gym_Text_WattsonRematchDefeat:
	.string "Uff...\n"
	.string "Nuestras baterías se agotaron...$"

MauvilleCity_Gym_Text_WattsonPostRematch:
	.string "WATTSON: Tendremos que recargar\n"
	.string "nuestras baterías otra vez.\p"
	.string "Cuando estemos cargados, con gusto\n"
	.string "aceptaremos tu desafío.\p"
	.string "Así que, vuelve más tarde.\n"
	.string "¿verdad?$"

MauvilleCity_Gym_Text_WattsonRematchNeedTwoMons:
	.string "WATTSON: ¡Ah-ja! ¡Al fin llegaste!\n"
	.string "Sé lo que quieres.\l"
	.string "¡Quieres luchar contra mis POKéMON!\p"
	.string "¡Wahajajaja!\p"
	.string "¡Ups! ¡Espera!\n"
	.string "¡Solo tienes un POKéMON contigo!\p"
	.string "Vuelve conmigo con dos o más\n"
	.string "POKéMON, ¿está todo bien?$"

