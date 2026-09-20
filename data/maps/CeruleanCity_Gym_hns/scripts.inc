CeruleanCity_Gym_hns_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, CeruleanCity_Gym_OnFrame
	.byte 0

CeruleanCity_Gym_OnFrame::
	map_script_2 VAR_KANTO_ROCKET_STORY_STATE, 2,  CeruleanCity_Gym_EventScript_RocketGrunt
	map_script_2 VAR_TEMP_0, 0,  CeruleanCity_Gym_EventScript_TryMachinePart
	.2byte 0

CeruleanCity_Gym_EventScript_RocketGrunt::
	lock
	applymovement LOCALID_CERULEAN_GYM_ROCKET, CeruleanCity_Gym_Movement_GruntBumpPlayer
	delay 20
	playse SE_BANG
	waitmovement 0
	
	msgbox CeruleanGym_Text_GruntIntro, MSGBOX_DEFAULT
	closemessage
	playse SE_PIN
	applymovement LOCALID_CERULEAN_GYM_ROCKET, Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_CERULEAN_GYM_ROCKET
	applymovement LOCALID_CERULEAN_GYM_ROCKET, CeruleanCity_Gym_Movement_GruntWalkBack
	waitmovement 0
	msgbox CeruleanGym_Text_GruntBigMistake, MSGBOX_DEFAULT
	applymovement LOCALID_CERULEAN_GYM_ROCKET, CeruleanCity_Gym_Movement_GruntWalkToPlayerAgain
	waitmovement 0
	msgbox CeruleanGym_Text_GruntBye, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, CeruleanCity_Gym_Movement_PlayerSlide
	delay 10
	applymovement LOCALID_CERULEAN_GYM_ROCKET, CeruleanCity_Gym_Movement_GruntLeave
	waitmovement 0
	fadescreenswapbuffers FADE_TO_BLACK
	playse SE_EXIT
	setflag FLAG_HIDE_CERULEAN_GYM_ROCKET
	removeobject LOCALID_CERULEAN_GYM_ROCKET
	fadescreenswapbuffers FADE_FROM_BLACK
	clearflag FLAG_HIDE_CERULEAN_CAPE_ROCKET
	setvar VAR_KANTO_ROCKET_STORY_STATE, 3
	release
	end

CeruleanCity_Gym_EventScript_TryMachinePart::
	goto_if_eq VAR_KANTO_ROCKET_STORY_STATE, 5, CeruleanCity_Gym_EventScript_MachinePart
	setvar VAR_TEMP_0, 1
	end

CeruleanCity_Gym_EventScript_MachinePart::
	special SpawnCameraObject
	applymovement OBJ_EVENT_ID_CAMERA, CeruleanCity_Movement_CameraPanUp
	waitmovement 0
	delay 30
	setvar VAR_0x8004, 5  @ x
	setvar VAR_0x8005, 13  @ y
	playse SE_PIN
	call Route110_TrickHouseEntrance_EventScript_DoHidingSpotSparkle
	delay 55
	applymovement OBJ_EVENT_ID_CAMERA, CeruleanCity_Movement_CameraPanDown
	waitmovement 0
	special RemoveCameraObject
	setvar VAR_TEMP_0, 1
	end

CeruleanCity_Gym_EventScript_MachinePartItem::
	goto_if_lt VAR_KANTO_ROCKET_STORY_STATE, 5, CeruleanCity_Gym_EventScript_DoNothing
	goto_if_ge VAR_KANTO_ROCKET_STORY_STATE, 6, CeruleanCity_Gym_EventScript_DoNothing
	finditem ITEM_MACHINE_PART
	setvar VAR_KANTO_ROCKET_STORY_STATE, 6
	setflag FLAG_HIDDEN_ITEM_MACHINE_PART
	end

CeruleanCity_Gym_EventScript_DoNothing::
	end

CeruleanCity_Movement_CameraPanUp:
	walk_up
	walk_up
	walk_up
	step_end

CeruleanCity_Movement_CameraPanDown:
	walk_down
	walk_down
	walk_down
	step_end

CeruleanCity_Gym_Movement_GruntBumpPlayer:
	walk_fast_down
	walk_fast_down
	walk_in_place_fast_down
	lock_facing_direction
	jump_up
	unlock_facing_direction
	delay_16
	walk_down
	step_end

CeruleanCity_Gym_Movement_GruntWalkBack:
	lock_facing_direction
	walk_slow_up
	walk_slow_up
	unlock_facing_direction
	step_end

CeruleanCity_Gym_Movement_GruntWalkToPlayerAgain:
	walk_down
	walk_down
	step_end

CeruleanCity_Gym_Movement_PlayerSlide:
	lock_facing_direction
	walk_fast_right
	unlock_facing_direction
	step_end

CeruleanCity_Gym_Movement_GruntLeave:
	walk_fast_down
	walk_in_place_fast_down
	step_end

CeruleanCity_Gym_EventScript_Statue::
	lockall
	goto_if_set FLAG_BADGE10_GET, CeruleanCity_Gym_EventScript_GymStatuePostVictory
	msgbox CeruleanCity_Gym_Text_GymStatue
	releaseall
	end

CeruleanCity_Gym_EventScript_StatueDuringRocket::
	msgbox CeruleanGym_Text_Note, MSGBOX_SIGN
	end 

CeruleanCity_Gym_EventScript_GymStatuePostVictory::
	msgbox CeruleanCity_Gym_Text_GymStatuePlayerWon
	releaseall
	end

CeruleanGym_EventScript_Diana::
	trainerbattle_single TRAINER_DIANA_HNS, CeruleanGym_Text_SwimmerfDianaSeen, CeruleanGym_Text_SwimmerfDianaBeaten
	msgbox CeruleanGym_Text_SwimmerfDianaAfter, MSGBOX_AUTOCLOSE
	end

CeruleanGym_EventScript_Briana::
	trainerbattle_single TRAINER_BRIANA_HNS, CeruleanGym_Text_SwimmerfBrianaSeen, CeruleanGym_Text_SwimmerfBrianaBeaten
	msgbox CeruleanGym_Text_SwimmerfBrianaAfter, MSGBOX_AUTOCLOSE
	end

CeruleanGym_EventScript_Parker::
	trainerbattle_single TRAINER_PARKER_HNS, CeruleanGym_Text_SwimmermParkerSeen, CeruleanGym_Text_SwimmermParkerBeaten
	msgbox CeruleanGym_Text_SwimmermParkerAfter, MSGBOX_AUTOCLOSE
	end

CeruleanCity_Gym_EventScript_GymGuy::
	goto_if_set FLAG_DEFEATED_CERULEAN_GYM, CeruleanCity_Gym_EventScript_GymGuyAfter
	msgbox CeruleanGym_Text_GuideIntro, MSGBOX_NPC
	end

CeruleanCity_Gym_EventScript_GymGuyAfter::
	msgbox CeruleanGym_Text_GuideWin, MSGBOX_NPC
	end

CeruleanCity_Gym_Text_GymStatue::
    .string "GIMNASIO POKéMON AZULONA\n"
    .string "LÍDER: MISTY\p"
	.string "ENTRENADORES GANADORES:\n"
	.string "BLUE, RED$"

CeruleanCity_Gym_Text_GymStatuePlayerWon::
    .string "GIMNASIO POKéMON AZULONA\n"
    .string "LÍDER: MISTY\p"
    .string "ENTRENADORES GANADORES:\n"
	.string "BLUE, RED, {PLAYER}$"

CeruleanGym_Text_Note:
	.string "Lo siento, estaré fuera un tiempo.\n"
	.string "MISTY, LÍDER DE GIMNASIO\p"
	.string "Como MISTY no está, nosotros\n"
	.string "también nos iremos.\l"
	.string "ENTRENADORES DEL GIMNASIO$"


CeruleanCity_Gym_EventScript_Misty::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_CERULEAN_GYM, CeruleanCity_Gym_EventScript_Misty_Defeated
	msgbox CeruleanGym_Text_MistyIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_MISTY_HNS, CeruleanGym_Text_MistyWinLoss
	message CeruleanGym_Text_ReceivedBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	setflag FLAG_BADGE10_GET
	setflag FLAG_DEFEATED_CERULEAN_GYM
	addvar VAR_NUM_BADGES, 1
	setvar VAR_0x8008, 10
	call Common_EventScript_SetGymTrainers_hns
	msgbox CeruleanGym_Text_Misty_GiveTM, MSGBOX_DEFAULT
	giveitem ITEM_TM_WATER_PULSE
	msgbox CeruleanGym_Text_Misty_ExplainTM, MSGBOX_DEFAULT
	clearflag FLAG_HIDE_CAPE_MISTY
	call_if_eq VAR_SUICUNE_ENCOUNTERS, 5, CeruleanCity_Gym_SetSuicuneScene
	closemessage
	release
	end

CeruleanCity_Gym_SetSuicuneScene::
	setvar VAR_SUICUNE_ENCOUNTERS, 6
	clearflag FLAG_HIDE_ROUTE25_SUICUNE
	return

CeruleanCity_Gym_EventScript_Misty_Defeated::
	msgbox CeruleanGym_Text_MistyFightDone, MSGBOX_DEFAULT
	closemessage
	release
	end

CeruleanGym_Text_GruntIntro:
	.string "¡Ups! ¡Lo siento mucho! No te\n"
	.string "lastimaste, ¿verdad?\p"
	.string "Estoy muy ocupada. No tengo tiempo\n"
	.string "de hablar contigo. No sería bueno\l"
	.string "que alguien me viera.$"

CeruleanGym_Text_GruntBigMistake:
	.string "¡Oh no! ¡Ya me viste!\n"
	.string "¡Cometí un gran error!$"

CeruleanGym_Text_GruntBye:
	.string "¡Oye, tú! Olvida que me viste,\n"
	.string "lastimaste, ¿verdad?\p"
	.string "no viste, oíste ni sabes nada,\p"
	.string "¿está bien? ¡Adiós, niño! ¡Nada!\p"
	.string "¡Adiós, adiós!$"

CeruleanGym_Text_Note1:
	.string "Lo siento, estaré fuera un tiempo.\n"
	.string "MISTY, LÍDER DE GIMNASIO\p"
	.string "Como MISTY no está, nosotros\n"
	.string "también. ENTRENADORES DEL GYM$"

CeruleanGym_Text_MistyIntro:
	.string "MISTY: Te estaba esperando, ¡pedazo\n"
	.string "de plaga!\p"
	.string "Tendrás muchas MEDALLAS DE GYM\n"
	.string "de JOHTO, pero más vale que no\l"
	.string "me subestimes.\p"
	.string "¡Mis POKéMON tipo AGUA son\n"
	.string "fuertes!$"

CeruleanGym_Text_MistyWinLoss:
	.string "MISTY: Eres muy bueno...\p"
	.string "Admito que tienes habilidad…\p"
	.string "Toma. Es la MEDALLA CASCADA.$"

CeruleanGym_Text_ReceivedBadge:
	.string "{PLAYER} recibió la MEDALLA Cascada.$"

CeruleanGym_Text_MistyFightDone:
	.string "MISTY: ¿Hay muchos\n"
	.string "ENTRENADORES fuertes en JOHTO?\l"
	.string "Me refiero, como tú.\p"
	.string "Algún día viajaré para\n"
	.string "poder luchar contra\l"
	.string "grandes ENTRENADORES.$"

CeruleanGym_Text_MistyRematch:
	.string "MISTY: Vaya, eres el KANTO\n"
	.string "¡Ya eres CAMPEÓN!\p"
	.string "¡Es increíble! Has llegado muy\n"
	.string "lejos, {PLAYER}.\p"
	.string "Pero no me rendiré.\p"
	.string "¿Quieres otra revancha conmigo?$"

CeruleanGym_Text_MistyRematchDefeat:
	.string "MISTY: Eres realmente bueno…$"

CeruleanGym_Text_SwimmerfDianaSeen:
	.string "Siento haberme ido. ¡Que\n"
	.string "empiece la batalla!$"

CeruleanGym_Text_SwimmerfDianaBeaten:
	.string "¡Me rindo! ¡Tú ganas!$"

CeruleanGym_Text_SwimmerfDianaAfter:
	.string "I'll be swimming quietly.$"

CeruleanGym_Text_SwimmerfBrianaSeen:
	.string "Que mi nado elegante no te\n"
	.string "ponga nervioso.$"

CeruleanGym_Text_SwimmerfBrianaBeaten:
	.string "Vaya, me venciste con calma…$"

CeruleanGym_Text_SwimmerfBrianaAfter:
	.string "No presumas por haber ganado,\n"
	.string "me.\p"
	.string "MISTY te destruirá si te\n"
	.string "confías.$"

CeruleanGym_Text_SwimmermParkerSeen:
	.string "Glub...\p"
	.string "¡Yo voy primero! ¡Atrápame!$"

CeruleanGym_Text_SwimmermParkerBeaten:
	.string "Esto no puede ser…$"

CeruleanGym_Text_SwimmermParkerAfter:
	.string "MISTY ha mejorado mucho en\n"
	.string "estos últimos años.\p"
	.string "¡No bajes la guardia o\n"
	.string "te aplastará!$"

CeruleanGym_Text_GuideIntro:
	.string "¡Ey! ¡Futuro CAMPEÓN!\p"
	.string "Como MISTY no estaba, yo también\p"
	.string "salí a divertirme. Je-je-je.$"

CeruleanGym_Text_GuideWin:
	.string "Vaya, me has demostrado lo fuerte\n"
	.string "que eres.\p"
	.string "Como siempre, ¡ha sido una\n"
	.string "batalla increíble!$"

CeruleanGym_Text_Misty_GiveTM:
	.string "Here, take this too.$"

CeruleanGym_Text_Misty_ExplainTM:
	.string "Es la MT de PULSO AGUA.\p"
	.string "Causa daño y a veces también\n"
	.string "provoca confusión!$"
