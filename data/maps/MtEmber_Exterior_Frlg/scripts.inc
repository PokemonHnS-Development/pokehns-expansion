MtEmber_Exterior_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MtEmber_Exterior_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, MtEmber_Exterior_OnLoad
	.byte 0

MtEmber_Exterior_OnTransition::
	setworldmapflag FLAG_WORLD_MAP_MT_EMBER_EXTERIOR
	call_if_eq VAR_MAP_SCENE_MT_EMBER_EXTERIOR, 2, MtEmber_Exterior_EventScript_RocketsFaceDown
	end

MtEmber_Exterior_EventScript_RocketsFaceDown::
	setobjectmovementtype LOCALID_MT_EMBER_GRUNT1, MOVEMENT_TYPE_FACE_DOWN
	setobjectmovementtype LOCALID_MT_EMBER_GRUNT2, MOVEMENT_TYPE_FACE_DOWN
	return

MtEmber_Exterior_OnLoad::
	call_if_ge VAR_MAP_SCENE_ONE_ISLAND_POKEMON_CENTER_1F, 4, MtEmber_Exterior_EventScript_OpenCave
	end

MtEmber_Exterior_EventScript_OpenCave::
	setmetatile 42, 39, METATILE_MtEmber_CaveEntrance, 0
	return

MtEmber_Exterior_EventScript_Grunt1::
	lock
	goto_if_defeated TRAINER_TEAM_ROCKET_GRUNT_43, MtEmber_Exterior_EventScript_Grunt1Defeated
	goto_if_eq VAR_MAP_SCENE_ONE_ISLAND_POKEMON_CENTER_1F, 4, MtEmber_Exterior_EventScript_BattleGrunt1
	msgbox MtEmber_Exterior_Text_WellTryDiggingHere
	release
	end

MtEmber_Exterior_EventScript_Grunt1Defeated::
	msgbox MtEmber_Exterior_Text_Grunt1PostBattle
	release
	end

MtEmber_Exterior_EventScript_BattleGrunt1::
	applymovement LOCALID_MT_EMBER_GRUNT1, Common_Movement_FacePlayer
	waitmovement 0
	playbgm MUS_RG_ENCOUNTER_ROCKET, 0
	msgbox MtEmber_Exterior_Text_Grunt1Intro
	trainerbattle_no_intro TRAINER_TEAM_ROCKET_GRUNT_43, MtEmber_Exterior_Text_Grunt1Defeat
	msgbox MtEmber_Exterior_Text_Grunt1PostBattle
	goto_if_defeated TRAINER_TEAM_ROCKET_GRUNT_44, MtEmber_Exterior_EventScript_DefeatedBothGrunts
	release
	end

MtEmber_Exterior_EventScript_DefeatedBothGrunts::
	msgbox MtEmber_Exterior_Text_WellRegroupDontStepInsideThere
	closemessage
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_MT_EMBER_GRUNT1
	removeobject LOCALID_MT_EMBER_GRUNT2
	fadescreenswapbuffers FADE_FROM_BLACK
	release
	end

MtEmber_Exterior_EventScript_Grunt2::
	lock
	faceplayer
	goto_if_defeated TRAINER_TEAM_ROCKET_GRUNT_44, MtEmber_Exterior_EventScript_DefeatedGrunt2
	goto_if_eq VAR_MAP_SCENE_ONE_ISLAND_POKEMON_CENTER_1F, 4, MtEmber_Exterior_EventScript_BattleGrunt2
	msgbox MtEmber_Exterior_Text_YoureInTheWayGetLost
	closemessage
	applymovement LOCALID_MT_EMBER_GRUNT2, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

MtEmber_Exterior_EventScript_DefeatedGrunt2::
	msgbox MtEmber_Exterior_Text_Grunt2PostBattle
	release
	end

MtEmber_Exterior_EventScript_BattleGrunt2::
	playbgm MUS_RG_ENCOUNTER_ROCKET, 0
	msgbox MtEmber_Exterior_Text_Grunt2Intro
	trainerbattle_no_intro TRAINER_TEAM_ROCKET_GRUNT_44, MtEmber_Exterior_Text_Grunt2Defeat
	msgbox MtEmber_Exterior_Text_Grunt2PostBattle
	goto_if_defeated TRAINER_TEAM_ROCKET_GRUNT_43, MtEmber_Exterior_EventScript_DefeatedBothGrunts
	release
	end

MtEmber_Exterior_EventScript_RocketPasswordScene::
	lockall
	textcolor NPC_TEXT_COLOR_MALE
	msgbox MtEmber_Exterior_Text_PunchedThroughAtLast
	message MtEmber_Exterior_Text_WhatsPasswordAgain
	waitmessage
	playse SE_PIN
	applymovement LOCALID_MT_EMBER_GRUNT2, Common_Movement_QuestionMark
	waitmovement 0
	waitbuttonpress
	msgbox MtEmber_Exterior_Text_FirstPasswordGoldeen
	applymovement LOCALID_MT_EMBER_GRUNT1, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_MT_EMBER_GRUNT1, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_MT_EMBER_GRUNT1, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_MT_EMBER_GRUNT2, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	call MtEmber_Exterior_EventScript_RocketsFaceDown
	msgbox MtEmber_Exterior_Text_SnoopsBeenListeningIn
	setvar VAR_MAP_SCENE_MT_EMBER_EXTERIOR, 2
	releaseall
	end

MtEmber_Exterior_EventScript_Logan::
	trainerbattle_single TRAINER_PKMN_RANGER_LOGAN, MtEmber_Exterior_Text_LoganIntro, MtEmber_Exterior_Text_LoganDefeat
	msgbox MtEmber_Exterior_Text_LoganPostBattle, MSGBOX_AUTOCLOSE
	end

MtEmber_Exterior_EventScript_Beth::
	trainerbattle_single TRAINER_PKMN_RANGER_BETH, MtEmber_Exterior_Text_BethIntro, MtEmber_Exterior_Text_BethDefeat
	msgbox MtEmber_Exterior_Text_BethPostBattle, MSGBOX_AUTOCLOSE
	end

MtEmber_Exterior_EventScript_Jocelyn::
	trainerbattle_single TRAINER_CRUSH_GIRL_JOCELYN, MtEmber_Exterior_Text_JocelynIntro, MtEmber_Exterior_Text_JocelynDefeat
	msgbox MtEmber_Exterior_Text_JocelynPostBattle, MSGBOX_AUTOCLOSE
	end

Text_ExplosionTeach::
	.string "¿Te lo imaginas?\n"
	.string "¿Y si este volcán hiciera erupción?\p"
	.string "La explosión sería el fin de\n"
	.string "nosotros. ¿No es aterrador?\p"
	.string "Mientras temblamos, ¿quieres\n"
	.string "que te enseñe EXPLOSION?$"

Text_ExplosionDeclined::
	.string "Sí, tienes razón.\n"
	.string "Es demasiado aterrador.$"

Text_ExplosionWhichMon::
	.string "¡Eres muy valiente!\p"
	.string "¿A qué POKéMON le enseño\n"
	.string "EXPLOSION?$"

Text_ExplosionTaught::
	.string "Usar EXPLOSION encima de este\n"
	.string "volcán...\p"
	.string "¡Qué emoción tan aterradora!$"

MtEmber_Exterior_Text_WellTryDiggingHere::
	.string "Por aquí.\n"
	.string "Intentaremos cavar aquí.\p"
	.string "El tesoro del que hablaban los\n"
	.string "ADMINS debería estar aquí.$"

MtEmber_Exterior_Text_YoureInTheWayGetLost::
	.string "¿Qué...?\n"
	.string "Estás en medio. ¡Lárgate!$"

MtEmber_Exterior_Text_PunchedThroughAtLast::
	.string "Uf, al fin atravesamos.\n"
	.string "¡Vamos a cazar el tesoro!$"

MtEmber_Exterior_Text_WhatsPasswordAgain::
	.string "Cualquier tesoro que hallemos,\n"
	.string "lo llevamos al ALMACÉN, ¿entendido?\p"
	.string "Ah... ¿y cuáles eran las claves?\n"
	.string "Las del ALMACÉN COHETE, digo.$"

MtEmber_Exterior_Text_FirstPasswordGoldeen::
	.string "¿Qué, olvidaste la clave?\n"
	.string "En realidad hay dos.\p"
	.string "La primera es “GOLDEEN need\n"
	.string "log.”\p"
	.string "Y la segunda es...$"

MtEmber_Exterior_Text_SnoopsBeenListeningIn::
	.string "¡Hola!\n"
	.string "¡Este fisgón nos ha estado escuchando!$"

MtEmber_Exterior_Text_Grunt1Intro::
	.string "Nos has estado espiando,\n"
	.string "¿verdad?$"

MtEmber_Exterior_Text_Grunt1Defeat::
	.string "¿Eh, qué?$"

MtEmber_Exterior_Text_Grunt1PostBattle::
	.string "¿Por qué tuviste que ganar?$"

MtEmber_Exterior_Text_Grunt2Intro::
	.string "¿Intentas meterte en nuestro tesoro?\n"
	.string "¡No cuentes con eso!$"

MtEmber_Exterior_Text_Grunt2Defeat::
	.string "¡Espera!\n"
	.string "¿Pero cómo?$"

MtEmber_Exterior_Text_Grunt2PostBattle::
	.string "Desarrolla amnesia oportuna y\n"
	.string "¡olvida todo lo que oíste!$"

MtEmber_Exterior_Text_WellRegroupDontStepInsideThere::
	.string "Qué revés...\n"
	.string "Tendremos que reagruparnos.\p"
	.string "¡Tú! ¡Ni se te ocurra dar\n"
	.string "un paso aquí dentro!\p"
	.string "Si sabes lo que te conviene,\n"
	.string "¡ni se te ocurra pensarlo!$"

MtEmber_Exterior_Text_LoganIntro::
	.string "Un volcán activo es el que está\n"
	.string "en erupción o a punto de estarlo.$"

MtEmber_Exterior_Text_LoganDefeat::
	.string "Uf... ¡Eso estuvo caliente!\n"
	.string "¡Me brota sudor por todo el cuerpo!$"

MtEmber_Exterior_Text_LoganPostBattle::
	.string "Dicen que hay más de 1,500\n"
	.string "volcanes activos en el mundo.\p"
	.string "Solo pensarlo me hace sentir\n"
	.string "¡todo caliente y pegajoso por dentro!$"

MtEmber_Exterior_Text_BethIntro::
	.string "¿Sabes cómo se forman las cuevas\n"
	.string "dentro de los volcanes?$"

MtEmber_Exterior_Text_BethDefeat::
	.string "¡Achís!\n"
	.string "¡Eres asombrosamente bueno!$"

MtEmber_Exterior_Text_BethPostBattle::
	.string "Cuando la lava en la superficie del\n"
	.string "magma se endurece, y el magma interior\l"
	.string "fluye, quedan cavernas detrás.$"

MtEmber_Exterior_Text_JocelynIntro::
	.string "He estado entrenando para reparar\n"
	.string "mi corazón roto...\p"
	.string "Al menos me fortaleció\n"
	.string "físicamente. ¡Hi-yah!$"

MtEmber_Exterior_Text_JocelynDefeat::
	.string "Creo que me esforcé demasiado...$"

MtEmber_Exterior_Text_JocelynPostBattle::
	.string "Tu forma de luchar me recuerda\n"
	.string "al chico que me dejó...$"

