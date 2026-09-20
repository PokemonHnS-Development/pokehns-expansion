JaggedPass_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, JaggedPass_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, JaggedPass_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, JaggedPass_OnLoad
	.byte 0

JaggedPass_OnResume:
	setstepcallback STEP_CB_ASH
	call_if_eq VAR_JAGGED_PASS_STATE, 0, JaggedPass_EventScript_CheckHasMagmaEmblem
	end

JaggedPass_EventScript_CheckHasMagmaEmblem::
	checkitem ITEM_MAGMA_EMBLEM
	goto_if_eq VAR_RESULT, TRUE, JaggedPass_EventScript_SetReadyToOpenHideout
	return

JaggedPass_EventScript_SetReadyToOpenHideout::
	setvar VAR_JAGGED_PASS_STATE, 1
	return

JaggedPass_OnTransition:
	call_if_eq VAR_JAGGED_PASS_ASH_WEATHER, 1, JaggedPass_EventScript_SetWeatherAsh
	end

JaggedPass_EventScript_SetWeatherAsh::
	setweather WEATHER_VOLCANIC_ASH
	doweather
	return

JaggedPass_OnLoad:
	goto_if_le VAR_JAGGED_PASS_STATE, 1, JaggedPass_EventScript_ConcealHideoutEntrance
	end

JaggedPass_EventScript_ConcealHideoutEntrance::
	setmetatile 16, 17, METATILE_Lavaridge_RockWall, TRUE
	setmetatile 16, 18, METATILE_Lavaridge_RockWall, TRUE
	end

JaggedPass_EventScript_OpenMagmaHideout::
	lockall
	setvar VAR_0x8004, 1  @ vertical pan
	setvar VAR_0x8005, 1  @ horizontal pan
	setvar VAR_0x8006, 8  @ num shakes
	setvar VAR_0x8007, 5  @ shake delay
	special ShakeCamera
	waitstate
	msgbox JaggedPass_Text_BoulderShakingInResponseToEmblem, MSGBOX_DEFAULT
	closemessage
	setvar VAR_0x8004, 1   @ vertical pan
	setvar VAR_0x8005, 1   @ horizontal pan
	setvar VAR_0x8006, 16  @ num shakes
	setvar VAR_0x8007, 3   @ shake delay
	special ShakeCamera
	waitstate
	playse SE_EFFECTIVE
	setmetatile 16, 17, METATILE_Lavaridge_CaveEntrance_Top, TRUE
	setmetatile 16, 18, METATILE_Lavaridge_CaveEntrance_Bottom, FALSE
	special DrawWholeMapView
	delay 30
	setvar VAR_JAGGED_PASS_STATE, 2
	waitse
	releaseall
	end

JaggedPass_EventScript_MagmaHideoutGuard::
	lockall
	goto_if_set FLAG_BEAT_MAGMA_GRUNT_JAGGED_PASS, JaggedPass_EventScript_GuardDefeated
	waitse
	playse SE_PIN
	applymovement LOCALID_MAGMA_HIDEOUT_GUARD, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_MAGMA_HIDEOUT_GUARD, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_MAGMA_HIDEOUT_GUARD, Common_Movement_FacePlayer
	waitmovement 0
	msgbox JaggedPass_Text_GruntIntro, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_GRUNT_JAGGED_PASS, JaggedPass_Text_GruntDefeat
	setflag FLAG_BEAT_MAGMA_GRUNT_JAGGED_PASS
	applymovement LOCALID_MAGMA_HIDEOUT_GUARD, Common_Movement_FaceOriginalDirection
	waitmovement 0
	releaseall
	end

JaggedPass_EventScript_GuardDefeated::
	applymovement LOCALID_MAGMA_HIDEOUT_GUARD, Common_Movement_FacePlayer
	waitmovement 0
	msgbox JaggedPass_Text_GoWhereverYouWant, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_MAGMA_HIDEOUT_GUARD, Common_Movement_FaceOriginalDirection
	waitmovement 0
	releaseall
	end

JaggedPass_EventScript_Eric::
	trainerbattle_single TRAINER_ERIC, JaggedPass_Text_EricIntro, JaggedPass_Text_EricDefeat
	msgbox JaggedPass_Text_EricPostBattle, MSGBOX_AUTOCLOSE
	end

JaggedPass_EventScript_Diana::
	trainerbattle_single TRAINER_DIANA_1, JaggedPass_Text_DianaIntro, JaggedPass_Text_DianaDefeat, JaggedPass_EventScript_RegisterDiana
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, JaggedPass_EventScript_DianaRematch
	msgbox JaggedPass_Text_DianaPostBattle, MSGBOX_DEFAULT
	release
	end

JaggedPass_EventScript_RegisterDiana::
	special PlayerFaceTrainerAfterBattle
	msgbox JaggedPass_Text_DianaRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_DIANA_1
	release
	end

JaggedPass_EventScript_DianaRematch::
	trainerbattle_rematch TRAINER_DIANA_1, JaggedPass_Text_DianaRematchIntro, JaggedPass_Text_DianaRematchDefeat
	msgbox JaggedPass_Text_DianaPostRematch, MSGBOX_AUTOCLOSE
	end

JaggedPass_EventScript_Ethan::
	trainerbattle_single TRAINER_ETHAN_1, JaggedPass_Text_EthanIntro, JaggedPass_Text_EthanDefeat, JaggedPass_EventScript_RegisterEthan
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, JaggedPass_EventScript_EthanRematch
	msgbox JaggedPass_Text_EthanPostBattle, MSGBOX_DEFAULT
	release
	end

JaggedPass_EventScript_RegisterEthan::
	special PlayerFaceTrainerAfterBattle
	msgbox JaggedPass_Text_EthanRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_ETHAN_1
	release
	end

JaggedPass_EventScript_EthanRematch::
	trainerbattle_rematch TRAINER_ETHAN_1, JaggedPass_Text_EthanRematchIntro, JaggedPass_Text_EthanRematchDefeat
	msgbox JaggedPass_Text_EthanPostRematch, MSGBOX_AUTOCLOSE
	end

JaggedPass_EventScript_Julio::
	trainerbattle_single TRAINER_JULIO, JaggedPass_Text_JulioIntro, JaggedPass_Text_JulioDefeat
	msgbox JaggedPass_Text_JulioPostBattle, MSGBOX_AUTOCLOSE
	end

JaggedPass_EventScript_Autumn::
	trainerbattle_single TRAINER_AUTUMN, JaggedPass_Text_AutumnIntro, JaggedPass_Text_AutumnDefeat
	msgbox JaggedPass_Text_AutumnPostBattle, MSGBOX_AUTOCLOSE
	end

JaggedPass_Text_EricIntro:
	.string "PASO ESCARPADO DEL MT. CHIMNEY…\p"
	.string "Esto es lo que siempre he querido\n"
	.string "en una montaña.\p"
	.string "Este relieve tan escarpado…\n"
	.string "¡Me llega al alma!$"

JaggedPass_Text_EricDefeat:
	.string "Losing left me bitter!$"

JaggedPass_Text_EricPostBattle:
	.string "Sí, perdí en las batallas POKéMON…\p"
	.string "Pero, en el amor por las\n"
	.string "montañas, ¡te he ganado!$"

JaggedPass_Text_DianaIntro:
	.string "Este lugar no es para pasear.\n"
	.string "No es apto para un picnic.$"

JaggedPass_Text_DianaDefeat:
	.string "¡Ohhh, no!\n"
	.string "El suelo es muy irregular…$"

JaggedPass_Text_DianaPostBattle:
	.string "¿Sabías esto?\p"
	.string "Hay quienes usan sus bicicletas\n"
	.string "en este paso tan accidentado.$"

JaggedPass_Text_DianaRegister:
	.string "¿Volverás alguna vez por aquí?\n"
	.string "Si regresas, quiero una revancha.$"

JaggedPass_Text_DianaRematchIntro:
	.string "Los picnics son divertidos donde sea.\n"
	.string "¡Igual que los POKéMON!$"

JaggedPass_Text_DianaRematchDefeat:
	.string "¡Solo perdí porque el suelo es\n"
	.string "muy irregular!$"

JaggedPass_Text_DianaPostRematch:
	.string "Olvidaré la derrota y disfrutaré\n"
	.string "de esta caminata accidentada.$"

JaggedPass_Text_EthanIntro:
	.string "PASO ESCARPADO es difícil de andar.\n"
	.string "Es un buen lugar para entrenar.$"

JaggedPass_Text_EthanDefeat:
	.string "Todo terminó mientras aún\n"
	.string "buscábamos estabilidad…$"

JaggedPass_Text_EthanPostBattle:
	.string "Si tuviera una ACRO BIKE, podría\n"
	.string "saltar los riscos.$"

JaggedPass_Text_EthanRegister:
	.string "Cuando me acostumbre a los saltos,\n"
	.string "¡seguro que ganaré!\p"
	.string "¿Me registras en tu POKéNAV?$"

JaggedPass_Text_EthanRematchIntro:
	.string "Ya me acostumbré a los saltos.\n"
	.string "Ahora canto mientras subo.$"

JaggedPass_Text_EthanRematchDefeat:
	.string "Sigue siendo difícil luchar en este\n"
	.string "terreno tan irregular…$"

JaggedPass_Text_EthanPostRematch:
	.string "Debo conseguir una ACRO BIKE de RYDEL\n"
	.string "en CIUDAD MALVA…$"

JaggedPass_Text_GruntIntro:
	.string "¡Wah!\n"
	.string "¿Qué haces aquí?\p"
	.string "¿Qué hago yo en un lugar así?\p"
	.string "¿Y a ti qué te importa?$"

JaggedPass_Text_GruntDefeat:
	.string "Urrrgh…\p"
	.string "Debí entrar a nuestro ESCONDITE\n"
	.string "de inmediato…$"

JaggedPass_Text_GoWhereverYouWant:
	.string "¡Está bien, está bien!\n"
	.string "Lo admito... ¡eres fuerte!\p"
	.string "No te preocupes por mí.\n"
	.string "¡Ve a donde quieras!$"

JaggedPass_Text_BoulderShakingInResponseToEmblem:
	.string "¡Oh! Esta roca vibra al sentir el\n"
	.string "EMBLEMA MAGMA!$"

JaggedPass_Text_JulioIntro:
	.string "¡Ayyy! ¡Da mucho miedo bajar la\n"
	.string "montaña de un solo golpe!$"

JaggedPass_Text_JulioDefeat:
	.string "I feel like I'm falling apart…$"

JaggedPass_Text_JulioPostBattle:
	.string "Mi BICICLETA saltó tanto que\n"
	.string "me duele el trasero…$"

JaggedPass_Text_AutumnIntro:
	.string "Subo esta colina cada día.\n"
	.string "¡Confío en mi fuerza!$"

JaggedPass_Text_AutumnDefeat:
	.string "Hmm…\n"
	.string "¿Qué salió mal?$"

JaggedPass_Text_AutumnPostBattle:
	.string "¿Qué es esa extraña roca?\n"
	.string "¿un poco más arriba de aquí?$"

