.equ PLAYER_X_POS, VAR_0x8004
.equ PLAYER_Y_POS, VAR_0x8005

FiveIsland_RocketWarehouse_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, FiveIsland_RocketWarehouse_OnLoad
	map_script MAP_SCRIPT_ON_TRANSITION, FiveIsland_RocketWarehouse_OnTransition
	.byte 0

FiveIsland_RocketWarehouse_OnTransition::
	setworldmapflag FLAG_WORLD_MAP_FIVE_ISLAND_ROCKET_WAREHOUSE
	end

FiveIsland_RocketWarehouse_OnLoad::
	call_if_defeated TRAINER_TEAM_ROCKET_ADMIN, FiveIsland_RocketWarehouse_EventScript_SetArrowsForReEntry
	end

FiveIsland_RocketWarehouse_EventScript_SetArrowsForReEntry::
	setmetatile 26, 20, METATILE_SilphCo_Arrow_Up, 0
	setmetatile 27, 20, METATILE_SilphCo_Arrow_Up, 0
	return

FiveIsland_RocketWarehouse_EventScript_Cage::
	lockall
	goto_if_set FLAG_DEFEATED_ROCKETS_IN_WAREHOUSE, FiveIsland_RocketWarehouse_EventScript_CageUnlocked
	msgbox FiveIsland_RocketWarehouse_Text_ManyMonsLockedInPen
	releaseall
	end

FiveIsland_RocketWarehouse_EventScript_CageUnlocked::
	msgbox FiveIsland_RocketWarehouse_Text_PenUnlockedMonsFled
	releaseall
	end

FiveIsland_RocketWarehouse_EventScript_Computer::
	msgbox FiveIsland_RocketWarehouse_Text_ReportWithGraphsAndText, MSGBOX_SIGN
	end

FiveIsland_RocketWarehouse_EventScript_Admin2Trigger::
	lockall
	applymovement LOCALID_WAREHOUSE_ADMIN2, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	setvar VAR_MAP_SCENE_ROCKET_WAREHOUSE, 1
	releaseall
	end

FiveIsland_RocketWarehouse_EventScript_Gideon::
	trainerbattle_single TRAINER_SCIENTIST_GIDEON, FiveIsland_RocketWarehouse_Text_GideonIntro, FiveIsland_RocketWarehouse_Text_GideonDefeat, FiveIsland_RocketWarehouse_EventScript_DefeatedGideon
	goto_if_set FLAG_IS_CHAMPION, FiveIsland_RocketWarehouse_EventScript_MentionGiovannisKid
	msgbox FiveIsland_RocketWarehouse_Text_GetLostLeaveMeBe, MSGBOX_AUTOCLOSE
	end

FiveIsland_RocketWarehouse_EventScript_MentionGiovannisKid::
	famechecker FAMECHECKER_GIOVANNI, 5
	msgbox FiveIsland_RocketWarehouse_Text_GiovannisKidHasRedHair, MSGBOX_AUTOCLOSE
	end

FiveIsland_RocketWarehouse_EventScript_DefeatedGideon::
	msgbox FiveIsland_RocketWarehouse_Text_GideonPostBattle
	setflag FLAG_RECOVERED_SAPPHIRE
	giveitem ITEM_SAPPHIRE
	release
	end

FiveIsland_RocketWarehouse_EventScript_Grunt2::
	trainerbattle_single TRAINER_TEAM_ROCKET_GRUNT_47, FiveIsland_RocketWarehouse_Text_Grunt2Intro, FiveIsland_RocketWarehouse_Text_Grunt2Defeat
	msgbox FiveIsland_RocketWarehouse_Text_Grunt2PostBattle, MSGBOX_AUTOCLOSE
	end

FiveIsland_RocketWarehouse_EventScript_Grunt3::
	trainerbattle_single TRAINER_TEAM_ROCKET_GRUNT_48, FiveIsland_RocketWarehouse_Text_Grunt3Intro, FiveIsland_RocketWarehouse_Text_Grunt3Defeat
	msgbox FiveIsland_RocketWarehouse_Text_Grunt3PostBattle, MSGBOX_AUTOCLOSE
	end

FiveIsland_RocketWarehouse_EventScript_Admin2::
	trainerbattle_single TRAINER_TEAM_ROCKET_ADMIN_2, FiveIsland_RocketWarehouse_Text_Admin2Intro, FiveIsland_RocketWarehouse_Text_Admin2Defeat, FiveIsland_RocketWarehouse_EventScript_DefeatedAdmin2
	msgbox FiveIsland_RocketWarehouse_Text_Admin2PostBattle, MSGBOX_AUTOCLOSE
	end

FiveIsland_RocketWarehouse_EventScript_DefeatedAdmin2::
	getplayerxy PLAYER_X_POS, PLAYER_Y_POS
	call_if_le PLAYER_X_POS, 24, FiveIsland_RocketWarehouse_EventScript_PlayerFaceAdmin2
	msgbox FiveIsland_RocketWarehouse_Text_Admin2PostBattle
	closemessage
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_WAREHOUSE_GRUNT2
	removeobject LOCALID_WAREHOUSE_GRUNT3
	removeobject LOCALID_WAREHOUSE_ADMIN2
	removeobject LOCALID_WAREHOUSE_ADMIN1
	setflag FLAG_HIDE_FIVE_ISLAND_ROCKETS
	fadescreen FADE_FROM_BLACK
	setvar VAR_MAP_SCENE_ROCKET_WAREHOUSE, 1
	setflag FLAG_DEFEATED_ROCKETS_IN_WAREHOUSE
	release
	end

FiveIsland_RocketWarehouse_EventScript_PlayerFaceAdmin2::
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	return

FiveIsland_RocketWarehouse_EventScript_Grunt1::
	trainerbattle_single TRAINER_TEAM_ROCKET_GRUNT_42, FiveIsland_RocketWarehouse_Text_Grunt1Intro, FiveIsland_RocketWarehouse_Text_Grunt1Defeat
	msgbox FiveIsland_RocketWarehouse_Text_Grunt1PostBattle, MSGBOX_AUTOCLOSE
	end

FiveIsland_RocketWarehouse_EventScript_Admin1::
	trainerbattle_single TRAINER_TEAM_ROCKET_ADMIN, FiveIsland_RocketWarehouse_Text_Admin1Intro, FiveIsland_RocketWarehouse_Text_Admin1Defeat, FiveIsland_RocketWarehouse_EventScript_DefeatedAdmin1
	msgbox FiveIsland_RocketWarehouse_Text_MadeItSoYouCanComeBackThrough, MSGBOX_AUTOCLOSE
	end

FiveIsland_RocketWarehouse_EventScript_DefeatedAdmin1::
	getplayerxy PLAYER_X_POS, PLAYER_Y_POS
	specialvar VAR_RESULT, GetPlayerFacingDirection
	call_if_eq VAR_RESULT, DIR_NORTH, FiveIsland_RocketWarehouse_EventScript_PlayerFaceAdmin1
	msgbox FiveIsland_RocketWarehouse_Text_Admin1PostBattle
	closemessage
	call_if_le PLAYER_X_POS, 24, FiveIsland_RocketWarehouse_EventScript_AdminWalkToSwitchFar
	call_if_eq PLAYER_X_POS, 25, FiveIsland_RocketWarehouse_EventScript_AdminWalkToSwitch
	call_if_eq PLAYER_X_POS, 26, FiveIsland_RocketWarehouse_EventScript_AdminFaceSwitch
	call_if_eq PLAYER_X_POS, 27, FiveIsland_RocketWarehouse_EventScript_AdminFaceSwitch
	playse SE_PIN
	call FiveIsland_RocketWarehouse_EventScript_SetArrowsForReEntry
	special DrawWholeMapView
	waitse
	call_if_le PLAYER_X_POS, 24, FiveIsland_RocketWarehouse_EventScript_AdminFacePlayerLeft
	call_if_eq PLAYER_X_POS, 25, FiveIsland_RocketWarehouse_EventScript_AdminFacePlayerLeft
	call_if_eq PLAYER_X_POS, 26, FiveIsland_RocketWarehouse_EventScript_AdminFacePlayerLeft
	call_if_eq PLAYER_X_POS, 27, FiveIsland_RocketWarehouse_EventScript_AdminFacePlayerDown
	msgbox FiveIsland_RocketWarehouse_Text_MadeItSoYouCanComeBackThrough
	release
	end

FiveIsland_RocketWarehouse_EventScript_PlayerFaceAdmin1::
	goto_if_eq PLAYER_X_POS, 27, Common_EventScript_NopReturn
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	return

FiveIsland_RocketWarehouse_EventScript_AdminWalkToSwitchFar::
	applymovement LOCALID_WAREHOUSE_ADMIN1, FiveIsland_RocketWarehouse_Movement_AdminWalkToSwitchFar
	waitmovement 0
	return

FiveIsland_RocketWarehouse_EventScript_AdminWalkToSwitch::
	applymovement LOCALID_WAREHOUSE_ADMIN1, FiveIsland_RocketWarehouse_Movement_AdminWalkToSwitch
	waitmovement 0
	return

FiveIsland_RocketWarehouse_EventScript_AdminFaceSwitch::
	applymovement LOCALID_WAREHOUSE_ADMIN1, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	return

FiveIsland_RocketWarehouse_EventScript_AdminFacePlayerLeft::
	applymovement LOCALID_WAREHOUSE_ADMIN1, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	return

FiveIsland_RocketWarehouse_EventScript_AdminFacePlayerDown::
	applymovement LOCALID_WAREHOUSE_ADMIN1, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	return

FiveIsland_RocketWarehouse_Movement_AdminWalkToSwitchFar::
	walk_right
	walk_right
	walk_in_place_faster_up
	step_end

FiveIsland_RocketWarehouse_Movement_AdminWalkToSwitch::
	walk_right
	walk_in_place_faster_up
	step_end

FiveIsland_RocketWarehouse_Text_ManyMonsLockedInPen::
	.string "Hay muchos POKéMON encerrados\n"
	.string "lejos en el corral...$"

FiveIsland_RocketWarehouse_Text_PenUnlockedMonsFled::
	.string "La puerta del corral está\n"
	.string "Los POKéMON parecen haber huido.$"

FiveIsland_RocketWarehouse_Text_Grunt2Intro::
	.string "¿Viniste sabiendo que\n"
	.string "¿EL ALMACÉN DE ROCKET?$"

FiveIsland_RocketWarehouse_Text_Grunt2Defeat::
	.string "¿¡Qué te crees que estás haciendo!?$"

FiveIsland_RocketWarehouse_Text_Grunt2PostBattle::
	.string "¿El EQUIPO ROCKET acabó?\n"
	.string "¿De qué planeta vienes?$"

FiveIsland_RocketWarehouse_Text_Grunt1Intro::
	.string "Oh, tus POKéMON se ven fuertes.\n"
	.string "¿Estás dispuesto a venderlos?\p"
	.string "¿Eh?\n"
	.string "¿Querías batallar?$"

FiveIsland_RocketWarehouse_Text_Grunt1Defeat::
	.string "Oh, pero...\n"
	.string "¡Demasiado!$"

FiveIsland_RocketWarehouse_Text_Grunt1PostBattle::
	.string "Podemos darte un buen precio.\n"
	.string "¡Véndenos tus POKéMON!$"

FiveIsland_RocketWarehouse_Text_Grunt3Intro::
	.string "Recibí información sobre ti\n"
	.string "otros.\p"
	.string "Pero no hay forma de que un niño\n"
	.string "¡conoce a nuestro JEFE GIOVANNI!$"

FiveIsland_RocketWarehouse_Text_Grunt3Defeat::
	.string "No...te...atrevas...a...reír...$"

FiveIsland_RocketWarehouse_Text_Grunt3PostBattle::
	.string "No te metas en asuntos de adultos,\n"
	.string "¡mocoso presumido!$"

FiveIsland_RocketWarehouse_Text_Admin1Intro::
	.string "No sé ni me importa si lo que hago\n"
	.string "está bien o mal...\p"
	.string "Solo deposito mi fe en GIOVANNI\n"
	.string "y hago lo que me ordenan.$"

FiveIsland_RocketWarehouse_Text_Admin1Defeat::
	.string "I...\n"
	.string "Estoy destrozado...$"

FiveIsland_RocketWarehouse_Text_Admin1PostBattle::
	.string "Tú haces las cosas según\n"
	.string "tus creencias y moral.\p"
	.string "Ahora lo entiendo...$"

FiveIsland_RocketWarehouse_Text_MadeItSoYouCanComeBackThrough::
	.string "He hecho que puedas volver\n"
	.string "por ahí.\p"
	.string "¿Por qué no vas a descansar\n"
	.string "y recuperarte para lo que viene?\p"
	.string "El ADMIN que sigue me supera\n"
	.string "ampliamente como ENTRENADOR.\p"
	.string "Mejor prepárate para lo que\n"
	.string "un reto muy duro.$"

FiveIsland_RocketWarehouse_Text_Admin2Intro::
	.string "Ya es suficiente con que tú \n"
	.string "quieras ser el héroe, niño.\p"
	.string "Difundes mentiras de que el TEAM\n"
	.string "El EQUIPO ROCKET se disolvió...\p"
	.string "Es un intento tan obvio de\n"
	.string "causar confusión en nuestras filas.\p"
	.string "Por suerte, no somos tan ingenuos\n"
	.string "de caer en las mentiras de un niño!\p"
	.string "Y ahora, les mostraré qué tan\n"
	.string "temible es un adulto furioso!$"

FiveIsland_RocketWarehouse_Text_Admin2Defeat::
	.string "Uf...\n"
	.string "Eras demasiado fuerte...\p"
	.string "...\n"
	.string "¡Esa es la MEDALLA de GIOVANNI!\p"
	.string "¿Así que es verdad?\n"
	.string "¿El EQUIPO ROCKET se disolvió?$"

FiveIsland_RocketWarehouse_Text_Admin2PostBattle::
	.string "Abandonaremos este ALMACÉN...\p"
	.string "Pero no creas que esto ha terminado.\n"
	.string "No dejaré que esto sea el fin.\p"
	.string "Encontraré a GIOVANNI.\n"
	.string "¡Y resucitaré al EQUIPO ROCKET!\l"
	.string "Yo...\p"
	.string "¡Hasta entonces, adiós!$"

FiveIsland_RocketWarehouse_Text_ReportWithGraphsAndText::
	.string "Un informe con gráficos y texto está\n"
	.string "la pantalla de la PC.\p"
	.string "“La influencia de las ondas\n"
	.string "en la Evolución POKéMON”...\p"
	.string "... ... ... ... ... ...\p"
	.string "Es muy difícil de entender...$"

FiveIsland_RocketWarehouse_Text_GideonIntro::
	.string "Casi logré vender el\n"
	.string "ZAFIRO por mucho dinero...\p"
	.string "Entonces, tú solo tuviste que venir\n"
	.string "¡y arruinar todo el trato!\p"
	.string "Fufu... Fufufufu...\n"
	.string "¡No hay perdón para ti!$"

FiveIsland_RocketWarehouse_Text_GideonDefeat::
	.string "¡Gah! ¡Rayos!\n"
	.string "¡Rayos! ¡Rayos!$"

FiveIsland_RocketWarehouse_Text_GideonPostBattle::
	.string "Si no puedo venderlo, no vale nada!\n"
	.string "¡Adelante, tómalo!$"

FiveIsland_RocketWarehouse_Text_GetLostLeaveMeBe::
	.string "¿Qué quieres ahora?\n"
	.string "Vamos, vete y déjame en paz.$"

FiveIsland_RocketWarehouse_Text_GiovannisKidHasRedHair::
	.string "¿Qué, otra vez tú?\p"
	.string "Tú... Tú no eres el hijo\nde GIOVANNI,"
	.string "¿verdad?\p"
	.string "¡No, eso no puede ser!\n"
	.string "El hijo de GIOVANNI es pelirrojo.\p"
	.string "No tienes ninguna razón para\n"
	.string "molestarme. ¡Déjame en paz!$"

