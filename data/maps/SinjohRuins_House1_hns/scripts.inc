SinjohRuins_House1_hns_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, SinjohRuins_Lab_OnFrame
	map_script 	MAP_SCRIPT_ON_TRANSITION, SinjohRuins_Lab_OnTransition
	.byte 0

SinjohRuins_Lab_OnTransition::
	call_if_eq VAR_SINJOH_STORYLINE, 7, SinjohRuins_Lab_SetupFinalPlateScene
	end

SinjohRuins_Lab_OnFrame::
	map_script_2 VAR_SINJOH_STORYLINE, 7, SinjohRuins_Lab_FinalPlateScene
	.2byte 0

@==========================Intro Cutscene SCRIPTS================================================================================

SinjohRuins_Lab_EventScript_TriggerIntroTop::
	lock
	playse SE_PIN
	applymovement2 LOCALID_SINJOHRUINS_LAB_STEVEN, Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_SINJOHRUINS_LAB_STEVEN
	msgbox SinjohRuins_Lab_Text_StevenIntroCutscene1, MSGBOX_DEFAULT
	closemessage
	applymovement2 LOCALID_PLAYER, Common_Movement_WalkDown1
	applymovement2 LOCALID_SINJOHRUINS_LAB_STEVEN, SinjohRuins_Lab_Movement_StevenMeetPlayer
	waitmovement 0
	waitmovement LOCALID_SINJOHRUINS_LAB_STEVEN
	goto SinjohRuins_Lab_EventScript_TriggerIntro

SinjohRuins_Lab_EventScript_TriggerIntroMid::
	lock
	playse SE_PIN
	applymovement2 LOCALID_SINJOHRUINS_LAB_STEVEN, Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_SINJOHRUINS_LAB_STEVEN
	msgbox SinjohRuins_Lab_Text_StevenIntroCutscene1, MSGBOX_DEFAULT
	closemessage
	applymovement2 LOCALID_SINJOHRUINS_LAB_STEVEN, SinjohRuins_Lab_Movement_StevenMeetPlayer
	waitmovement LOCALID_SINJOHRUINS_LAB_STEVEN
	goto SinjohRuins_Lab_EventScript_TriggerIntro

SinjohRuins_Lab_EventScript_TriggerIntroBot::
	lock
	playse SE_PIN
	applymovement2 LOCALID_SINJOHRUINS_LAB_STEVEN, Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_SINJOHRUINS_LAB_STEVEN
	msgbox SinjohRuins_Lab_Text_StevenIntroCutscene1, MSGBOX_DEFAULT
	closemessage
	applymovement2 LOCALID_PLAYER, Common_Movement_WalkUp1
	applymovement2 LOCALID_SINJOHRUINS_LAB_STEVEN, SinjohRuins_Lab_Movement_StevenMeetPlayer
	waitmovement 0
	waitmovement LOCALID_SINJOHRUINS_LAB_STEVEN
	goto SinjohRuins_Lab_EventScript_TriggerIntro

SinjohRuins_Lab_EventScript_TriggerIntro::
	turnobject LOCALID_PLAYER, DIR_EAST
	msgbox SinjohRuins_Lab_Text_StevenIntroCutscene2, MSGBOX_DEFAULT
	closemessage
	applymovement2 LOCALID_SINJOHRUINS_LAB_STEVEN, SinjohRuins_Lab_Movement_StevenSitsDown
	delay 10
	applymovement LOCALID_PLAYER, SinjohRuins_Lab_Movement_PlayerGoesToTable
	delay 40
	applymovement2 LOCALID_NEWSINJOH_LAB_LINGUIST, SinjohRuins_Lab_Movement_LinguistWalkDown
	waitmovement 0
	waitmovement LOCALID_SINJOHRUINS_LAB_STEVEN
	waitmovement LOCALID_NEWSINJOH_LAB_LINGUIST
	applymovement2 LOCALID_SINJOHRUINS_LAB_STEVEN, Common_Movement_WalkInPlaceRight
	waitmovement 0
	msgbox SinjohRuins_Lab_Text_StevenIntroCutscene3, MSGBOX_DEFAULT
	closemessage
	delay 10
	applymovement2 LOCALID_NEWSINJOH_LAB_LINGUIST, Common_Movement_WalkInPlaceDown
	waitmovement 0
	msgbox SinjohRuins_Lab_Text_StevenIntroCutscene4, MSGBOX_DEFAULT
	closemessage
	delay 10
	applymovement LOCALID_NEWSINJOH_LAB_LINGUIST, SinjohRuins_Lab_Movement_LinguistWalkUp
	applymovement2 LOCALID_SINJOHRUINS_LAB_STEVEN, Common_Movement_WalkInPlaceRight
	waitmovement 0
	msgbox SinjohRuins_Lab_Text_StevenIntroCutscene5, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE, SinjohRuins_Lab_EventScript_IntroChoseYes
SinjohRuins_Lab_EventScript_IntroChoice::
	msgbox SinjohRuins_Lab_Text_StevenIntroCutsceneRefused, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE, SinjohRuins_Lab_EventScript_IntroChoseYes
	goto SinjohRuins_Lab_EventScript_IntroChoice

SinjohRuins_Lab_EventScript_IntroChoseYes::
	msgbox SinjohRuins_Lab_Text_StevenIntroCutscene6, MSGBOX_DEFAULT
	closemessage
	setvar VAR_SINJOH_STORYLINE, 6
	setvar VAR_NOBLE_SNEASLER, 1
	setvar VAR_NOBLE_OVERQWIL, 1
	setvar VAR_NOBLE_WYRDEER, 1
	setvar VAR_NOBLE_ARCANINE, 1
	setvar VAR_NOBLE_URSALUNA, 1
	setvar VAR_NOBLE_KLEAVOR, 1
	setvar VAR_NOBLE_ELECTRODE, 1
	setvar VAR_NOBLE_TYPHLOSION, 1
	release
	end

SinjohRuins_Lab_Movement_StevenMeetPlayer:
	walk_up
	walk_up
	walk_up
	face_left
	step_end

SinjohRuins_Lab_Movement_StevenSitsDown:
	walk_down
	walk_down
	walk_down
	face_right
	step_end

SinjohRuins_Lab_Movement_PlayerGoesToTable:
	walk_right
	walk_right
	walk_right
	walk_down
	walk_right
	walk_right
	walk_down
	walk_down
	walk_right
	face_left
	step_end

SinjohRuins_Lab_Movement_LinguistWalkDown:
	walk_down
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	face_down
	step_end

SinjohRuins_Lab_Movement_LinguistWalkUp:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	walk_up
	step_end


SinjohRuins_Lab_Text_StevenIntroCutscene1:
   	.string "STEVEN: ¿Hm?$"

SinjohRuins_Lab_Text_StevenIntroCutscene2:
	.string "STEVEN: ¡{PLAYER}!\p"
	.string "Reconocería esos ojos donde sea.\p"
	.string "¿Qué te trae tan al norte?\p"
	.string ".............\p"
	.string "Ya veo, las KIMONO GIRLS de\n"
	.string "NUEVA SINJOH te enviaron para\l"
	.string "ayudar en la investigación.\p"
	.string "En ese caso, permíteme ponerte\n"
	.string "al día.$"

SinjohRuins_Lab_Text_StevenIntroCutscene3:
	.string "STEVEN: Cuando oí hablar de\n"
	.string "estas ruinas, tuve que venir a\l"
	.string "verlas por mí mismo.\p"
	.string "Armé un equipo de DEVON CORP.\n"
	.string "y partimos en una expedición\l"
	.string "de investigación.\p"
	.string "Quién sabe qué hallaremos enterrado\n"
	.string "pueden entrenar aquí.\p"
	.string "Ya hemos aprendido bastante\n"
	.string "por ahora.$"

SinjohRuins_Lab_Text_StevenIntroCutscene4:
	.string "LINGÜISTA: Aunque la traducción\n"
	.string "de los glifos de las ruinas\l"
	.string "aún se me resiste, he podido\l"
	.string "descifrar algunos aspectos.\p"
	.string "Hay 17 TABLAS peculiares.\p"
	.string "Tienen cierta importancia\n"
	.string "a las ruinas, pero solo hemos\l"
	.string "encontrado una hasta ahora.\p"
	.string "Dicen que el resto están\n"
	.string "protegidas por POKéMON y\l"
	.string "entrenadores muy fuertes.$"

SinjohRuins_Lab_Text_StevenIntroCutscene5:
	.string "STEVEN: Esa es la historia, {PLAYER}.\p"
	.string "Los POKéMON NOBLES que cuidan\n"
	.string "las PLACAS restantes son muy\l"
	.string "fuertes para mi equipo, temo.\p"
	.string "Y debo quedarme aquí para\n"
	.string "supervisar la investigación.\p"
	.string "Pero creo que tú podrías lograrlo.\n"
	.string "¿Nos ayudarás?$"

SinjohRuins_Lab_Text_StevenIntroCutscene6:
	.string "Excelente.\p"
	.string "Los glifos dicen que las PLACAS\n"
	.string "están con POKéMON NOBLES y\l"
	.string "fuertes entrenadores en SINJOH.\p"
	.string "Llamaré a tu POKéGEAR si\n"
	.string "sabemos algo nuevo.\p"
	.string "Gracias, {PLAYER}.$"

SinjohRuins_Lab_Text_StevenIntroCutsceneRefused:
	.string "¿Estás seguro?\p"
	.string "Quién sabe qué hallaremos enterrado\n"
	.string "pueden entrenar aquí.\p"
	.string "¿No quieres reconsiderarlo?$"

@==========================Final plate Cutscene SCRIPTS================================================================================

SinjohRuins_Lab_SetupFinalPlateScene::
	setobjectxyperm LOCALID_SINJOHRUINS_LAB_STEVEN, 4, 7
	setobjectmovementtype LOCALID_SINJOHRUINS_LAB_STEVEN, MOVEMENT_TYPE_FACE_RIGHT
	setobjectxyperm LOCALID_NEWSINJOH_LAB_LINGUIST, 5, 7
	setobjectmovementtype LOCALID_NEWSINJOH_LAB_LINGUIST, MOVEMENT_TYPE_FACE_LEFT
	return

SinjohRuins_Lab_FinalPlateScene::
	lock
	applymovement LOCALID_PLAYER, Common_Movement_WalkUp1
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkUp1
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_SINJOHRUINS_LAB_STEVEN, Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_SINJOHRUINS_LAB_STEVEN
	turnobject LOCALID_SINJOHRUINS_LAB_STEVEN, DIR_SOUTH
	delay 30
	applymovement LOCALID_SINJOHRUINS_LAB_STEVEN, Common_Movement_WalkDown1
	turnobject LOCALID_NEWSINJOH_LAB_LINGUIST, DIR_SOUTH
	delay 30
	msgbox SinjohRuins_Lab_Text_FinalPlateScene1, MSGBOX_DEFAULT
	closemessage
	dofieldeffectsparkle 3, 8, 0
	waitfieldeffect FLDEFF_SPARKLE
	setvar VAR_RESULT, 3
	playfanfare MUS_AWAKEN_LEGEND
	playse SE_ORB
	special DoOrbEffect
	delay 200
	special FadeOutOrbEffect
	waitstate
	setvar VAR_0x8004, 2  @ vertical pan
	setvar VAR_0x8005, 2  @ horizontal pan
	setvar VAR_0x8006, 40  @ num shakes
	setvar VAR_0x8007, 3  @ shake delay
	special ShakeCamera
	waitstate
	msgbox SinjohRuins_Lab_Text_FinalPlateScene2, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, SinjohRuins_Lab_Movement_PlayerLeaveLab
	applymovement LOCALID_SINJOHRUINS_LAB_STEVEN, SinjohRuins_Lab_Movement_StevenLeaveLab
	waitmovement 0
	waitmovement 0
	setvar VAR_SINJOH_STORYLINE, 8
	warp MAP_SINJOH_RUINS_HNS, 0
	waitstate
	end

SinjohRuins_Lab_Text_FinalPlateScene1:
	.string "STEVEN: ¡{PLAYER}!\p"
	.string "Creo que sé qué pasará si\n"
	.string "reunimos las 17 placas.\l"
	.string "las PLACAS.\p"
	.string "Siento...\l"
	.string ".....................$"

SinjohRuins_Lab_Text_FinalPlateScene2:
	.string "STEVEN: ¡Necesito ver esto con\n"
	.string "mis propios ojos!\p"
	.string "¡Afuera, {PLAYER}!$" 

SinjohRuins_Lab_Movement_PlayerLeaveLab:
	walk_fast_down
	walk_fast_down
	walk_in_place_fast_down
	step_end

SinjohRuins_Lab_Movement_StevenLeaveLab:
	walk_fast_down
	walk_fast_down
	walk_in_place_fast_down
	step_end

@==========================NPC SCRIPTS================================================================================

SinjohRuins_Lab_EventScript_Steven::
	lock
	faceplayer
	buffernumberstring STR_VAR_1, VAR_PLATECOUNTER
	goto_if_ge VAR_PLATECOUNTER, 17, SinjohRuins_Lab_EventScript_StevenAfterAllPlates
	goto_if_ge VAR_PLATECOUNTER, 15, SinjohRuins_Lab_EventScript_StevenAfter15Plates
	goto_if_ge VAR_PLATECOUNTER, 12, SinjohRuins_Lab_EventScript_StevenAfter12Plates
	goto_if_ge VAR_PLATECOUNTER, 9, SinjohRuins_Lab_EventScript_StevenAfter9Plates
	goto_if_ge VAR_PLATECOUNTER, 6, SinjohRuins_Lab_EventScript_StevenAfter6Plates
	goto_if_ge VAR_PLATECOUNTER, 3, SinjohRuins_Lab_EventScript_StevenAfter3Plates
	msgbox SinjohRuins_Lab_Text_StevenFindPlates, MSGBOX_AUTOCLOSE
	release
	end

SinjohRuins_Lab_EventScript_StevenAfter3Plates::
	msgbox SinjohRuins_Lab_Text_StevenFindPlates3, MSGBOX_AUTOCLOSE
	release
	end

SinjohRuins_Lab_EventScript_StevenAfter6Plates::
	msgbox SinjohRuins_Lab_Text_StevenFindPlates3, MSGBOX_AUTOCLOSE
	release
	end

SinjohRuins_Lab_EventScript_StevenAfter9Plates::
	msgbox SinjohRuins_Lab_Text_StevenFindPlates9, MSGBOX_AUTOCLOSE
	release
	end

SinjohRuins_Lab_EventScript_StevenAfter12Plates::
	msgbox SinjohRuins_Lab_Text_StevenFindPlates9, MSGBOX_AUTOCLOSE
	release
	end

SinjohRuins_Lab_EventScript_StevenAfter15Plates::
	msgbox SinjohRuins_Lab_Text_StevenFindPlates9, MSGBOX_AUTOCLOSE
	release
	end

SinjohRuins_Lab_EventScript_StevenAfterAllPlates::
	msgbox SinjohRuins_Lab_Text_StevenAfterAll, MSGBOX_AUTOCLOSE
	release
	end

SinjohRuins_Lab_Text_StevenFindPlates:
	.string "STEVEN: Ah, {PLAYER}.\p"
	.string "{STR_VAR_1} PLACAS hasta ahora.\n"
	.string "Nada mal.\p"
	.string "Debo admitir que tengo curiosidad\n"
	.string "por saber qué pasará cuando\l"
	.string "estén todas reunidas.\p"
	.string "Bueno, veamos qué encuentras.$"

SinjohRuins_Lab_Text_StevenFindPlates3:
	.string "STEVEN: Ah, {PLAYER}.\p"
	.string "{STR_VAR_1} PLACAS hasta ahora.\n"
	.string "Nada mal.\p"
	.string "¿Ya investigaste esa\n"
	.string "cámara?\l"
	.string "Todo es muy misterioso.$"

SinjohRuins_Lab_Text_StevenFindPlates9:
	.string "STEVEN: Ah, {PLAYER}.\p"
	.string "{STR_VAR_1} PLACAS hasta ahora.\n"
	.string "Hago grandes progresos.\p"
	.string "Las cámaras que se abrieron\n"
	.string "son muy similares a una serie\l"
	.string "de cámaras que hay\l"
	.string "en la región de HOENN.\p"
	.string "Cada una albergaba a un\n"
	.string "POKéMON legendario.\p"
	.string "Pero en HOENN solo hubo 3,\n"
	.string "hace muy poco.\p"
	.string "y aquí hay al menos 6.\p"
	.string "Quién sabe qué hallaremos ahora.$"

SinjohRuins_Lab_Text_StevenAfterAll:
	.string "STEVEN: ¡{PLAYER}!\p"
	.string "Esta expedición ha sido la\n"
	.string "experiencia de mi vida.\p"
	.string "Desde que oí sobre estas ruinas,\n"
	.string "tuve este presentimiento.\p"
	.string "Pensé que descubriríamos algo\n"
	.string "increíble.\p"
	.string "Y mis predicciones suelen cumplirse.\p"
	.string "Gracias por toda tu ayuda,\n"
	.string "Campeón.\p"
	.string "¿A dónde irás ahora?\p"
	.string "Espero que nos veamos pronto.$"

SinjohRuins_Lab_EventScript_Geologist::
	goto_if_ge VAR_SINJOH_STORYLINE, 13, SinjohRuins_Lab_EventScript_GeologistAfterEvent
	goto_if_ge VAR_SINJOH_STORYLINE, 9, SinjohRuins_Lab_EventScript_GeologistDuringEvent
	msgbox SinjohRuins_Lab_Text_Geologist MSGBOX_NPC
	end
SinjohRuins_Lab_EventScript_GeologistDuringEvent::
	msgbox SinjohRuins_Lab_Text_GeologistDuring, MSGBOX_NPC
	end
SinjohRuins_Lab_EventScript_GeologistAfterEvent::
	msgbox SinjohRuins_Lab_Text_GeologistAfter, MSGBOX_NPC
	end

SinjohRuins_Lab_Text_Geologist:
    .string "El radar de penetración muestra\n"
	.string "6 cámaras subterráneas en este\l"
	.string "valle.\p"
	.string "5 parecen estar más cerca de\n"
	.string "la superficie, y 1 está\l"
	.string "enterrada aún más profundo.$"
SinjohRuins_Lab_Text_GeologistDuring:
	.string "Todo este tiempo dirigí mi\n"
	.string "equipo hacia abajo para ver\l"
	.string "el subsuelo.\p"
	.string "Cuando debí haber apuntado...\n"
	.string "it up!$"
SinjohRuins_Lab_Text_GeologistAfter:
	.string "¿Esas PLACAS se relacionan con\n"
	.string "el POKéMON más poderoso??\p"
	.string "I wish I had more time to study them.$"

SinjohRuins_Lab_EventScript_Linguist::
	goto_if_ge VAR_SINJOH_STORYLINE, 13, SinjohRuins_Lab_EventScript_LinguistAfterEvent
	goto_if_ge VAR_SINJOH_STORYLINE, 9, SinjohRuins_Lab_EventScript_LinguistDuringEvent
	msgbox SinjohRuins_Lab_Text_Linguist MSGBOX_NPC
	end
SinjohRuins_Lab_EventScript_LinguistDuringEvent::
	msgbox SinjohRuins_Lab_Text_LinguistDuring, MSGBOX_NPC
	end
SinjohRuins_Lab_EventScript_LinguistAfterEvent::
	msgbox SinjohRuins_Lab_Text_LinguistAfter, MSGBOX_NPC
	end

SinjohRuins_Lab_Text_Linguist:
    .string "Ugh....\n"
	.string "Hay demasiados glifos que\l"
	.string "traducir..\p"
	.string "No tenemos nada parecido a esto\n"
	.string "en la región de HOENN.$"
SinjohRuins_Lab_Text_LinguistDuring:
    .string "¡Imagina mi sorpresa al\n"
	.string "traducir el glifo!\p"
	.string "¡Lo revisé tres y cuatro veces\n"
	.string "antes de decírselo a STEVEN!\p"
	.string "Digo, en serio, ¡el Dios de\n"
	.string "con los POKéMON?\p"
	.string "Es increíble.$"
SinjohRuins_Lab_Text_LinguistAfter:
    .string "Esta expedición ha sido un\n"
	.string "placer, {PLAYER}.\p"
	.string "Gracias por encargarte de todo\n"
	.string "el trabajo de campo.$"

SinjohRuins_Lab_EventScript_Archaeologist::
	goto_if_ge VAR_SINJOH_STORYLINE, 13, SinjohRuins_Lab_EventScript_ArchaeologistAfterEvent
	goto_if_ge VAR_SINJOH_STORYLINE, 9, SinjohRuins_Lab_EventScript_ArchaeologistDuringEvent
	msgbox SinjohRuins_Lab_Text_Archaeologist MSGBOX_NPC
	end
SinjohRuins_Lab_EventScript_ArchaeologistDuringEvent::
	msgbox SinjohRuins_Lab_Text_ArchaeologistDuring, MSGBOX_NPC
	end
SinjohRuins_Lab_EventScript_ArchaeologistAfterEvent::
	msgbox SinjohRuins_Lab_Text_ArchaeologistAfter, MSGBOX_NPC
	end

SinjohRuins_Lab_Text_Archaeologist:
	.string "La existencia de una civilización\n"
    .string "en esta zona cambia todo nuestro\l"
	.string "entendimiento de la historia.\p"
	.string "Muchos artefactos que hallamos\n"
	.string "tienen más de mil años.\p"
	.string "El carbono coincide con los\n"
	.string "objetos de la región de SINNOH.\p"
	.string "Aunque, esa flauta que hallaste...\n"
	.string "Parece mucho más antiguo.$"
SinjohRuins_Lab_Text_ArchaeologistDuring:
	.string "Esas placas...\n"
	.string "La conexión con la región\l"
	.string "de SINNOH...\l"
	.string "Esa flauta....\l"
	.string "Todo empieza a tener sentido.$"
SinjohRuins_Lab_Text_ArchaeologistAfter:
	.string "El valor histórico de lo que\n"
	.string "nos ayudaste a desenterrar\l"
	.string "es incalculable, \l"
	.string "{PLAYER}.\p"
	.string "De verdad, gracias.$"

SinjohRuins_Lab_EventScript_Growlithe_Hisui::
    lock
	faceplayer
	playmoncry SPECIES_GROWLITHE, 0
	msgbox SinjohRuins_Lab_Text_Growlithe_Cry, MSGBOX_DEFAULT
	waitmoncry
    closemessage
	release
	end

SinjohRuins_Lab_Text_Growlithe_Cry:
    .string "¡Growh owh!!$"

SinjohRuins_Lab_EventScript_GrowlithePokeball::
    msgbox SinjohRuins_Lab_Text_GrowlitheBall MSGBOX_SIGN
	end

SinjohRuins_Lab_Text_GrowlitheBall:
    .string "Parece ser la BALL de Growlithe..\n"
	.string "Mejor dejarlo tranquilo.$"

SinjohRuins_Lab_EventScript_Biologist::
	goto_if_ge VAR_SINJOH_STORYLINE, 13, SinjohRuins_Lab_EventScript_BiologistAfterEvent
	goto_if_ge VAR_SINJOH_STORYLINE, 9, SinjohRuins_Lab_EventScript_BiologistDuringEvent
	msgbox SinjohRuins_Lab_Text_Biologist MSGBOX_NPC
	end
SinjohRuins_Lab_EventScript_BiologistDuringEvent::
	msgbox SinjohRuins_Lab_Text_BiologistDuring, MSGBOX_NPC
	end
SinjohRuins_Lab_EventScript_BiologistAfterEvent::
	msgbox SinjohRuins_Lab_Text_BiologistAfter, MSGBOX_NPC
	end

SinjohRuins_Lab_Text_Biologist:
    .string "¡Mira este espécimen tan maravilloso!\p"
	.string "Esta especie de GROWLITHE es distinta\n"
	.string "a las que se encuentran en cualquier\l"
	.string "otra parte del mundo.\p"
	.string "El análisis de ADN revela que tiene\n"
	.string "un ancestro común con los GROWLITHE\l"
	.string "de otras regiones.\p"
	.string "Aun así, su temperamento y tipo\n"
	.string "son muy diferentes.\p"
	.string "Los GROWLITHE de los antiguos\n"
	.string "registros de SINNOH parecen coincidir.\p"
	.string "Tal vez esta especie ocupó\n"
	.string "un territorio mucho más grande,\l"
	.string "hacia el norte de SINNOH.$"
SinjohRuins_Lab_Text_BiologistDuring:
	.string "Si la criatura al final de\n"
	.string "esas escaleras es el Dios\l"
	.string "de los POKéMON, ¿significa que\l"
	.string "es el primer ancestro común?$"
SinjohRuins_Lab_Text_BiologistAfter:
	.string "He podido reunir muchos datos\n"
	.string "sobre formas regionales y\l"
	.string "evolución divergente en esta\l"
	.string "expedición. Gracias,\l"
	.string "{PLAYER}.$"

SinjohRuins_Lab_EventScript_Hiker::
	goto_if_ge VAR_SINJOH_STORYLINE, 9, SinjohRuins_Lab_EventScript_HikerDuringAfter
	msgbox SinjohRuins_Lab_Text_Hiker MSGBOX_NPC
	end
SinjohRuins_Lab_EventScript_HikerDuringAfter::
	msgbox SinjohRuins_Lab_Text_HikerDuringAfter, MSGBOX_NPC
	end
SinjohRuins_Lab_Text_Hiker:
   	.string "Por diez años, recorrí estas\n"
	.string "salvajes.\p"
	.string "No, mejor digamos veinte años.\p"
	.string "Hasta que un día hallé esos grandes\n"
	.string "pilares de piedra y aquel templo\l"
	.string "siniestro.\p"
	.string "Son las RUINAS SINJOH.\n"
	.string "O eso he oído.\p"
	.string "En ese entonces no sabía del pueblo.\p"
	.string "Solo se lo conté a algunos de mis\n"
	.string "amigos. Pero las noticias vuelan.\p"
	.string "Nunca pensé que atraería tanta\n"
	.string "atención a la zona.\p"
	.string "Me hace sentir algo raro.\n"
	.string "¿Sabes?$"
SinjohRuins_Lab_Text_HikerDuringAfter:
   	.string "No se lo digas a nadie, {PLAYER},\n"
	.string "pero vi aquel templo en la\l"
	.string "cima de la montaña cuando\l"
	.string "descubrí este lugar.\p"
	.string "Me lo guardé para mí.\p"
	.string "Ya he hablado demasiado\n"
	.string "sobre estas ruinas.\p"
	.string "Parece que todo salió bien,\n"
	.string "al menos.$"

@ENVIRONMENT
SinjohRuins_Lab_EventScript_Notes1::
	msgbox SinjohRuins_Lab_Text_Note1 MSGBOX_SIGN
	end
SinjohRuins_Lab_EventScript_Notes2::
	msgbox SinjohRuins_Lab_Text_Note2 MSGBOX_SIGN
	end
SinjohRuins_Lab_EventScript_Notes3::
	msgbox SinjohRuins_Lab_Text_Note3 MSGBOX_SIGN
	end
SinjohRuins_Lab_EventScript_Notes4::
	msgbox SinjohRuins_Lab_Text_Note4 MSGBOX_SIGN
	end
SinjohRuins_Lab_EventScript_Notes5::
	msgbox SinjohRuins_Lab_Text_Note5 MSGBOX_SIGN
	end
SinjohRuins_Lab_EventScript_Notes6::
	msgbox SinjohRuins_Lab_Text_Note6 MSGBOX_SIGN
	end
SinjohRuins_Lab_EventScript_Notes7::
	msgbox SinjohRuins_Lab_Text_Note7 MSGBOX_SIGN
	end
SinjohRuins_Lab_EventScript_Notes8::
	msgbox SinjohRuins_Lab_Text_Note8 MSGBOX_SIGN
	end

SinjohRuins_Lab_Text_Note1:
    .string "Diario 1: 3 de mayo de 1975\p"
	.string "Llegamos al lugar\n"
	.string "de las ruinas.\p"
	.string "El frío intenso del Mt.Silver\n"
	.string "se siente incluso\l"
	.string "desde aquí abajo...\p"
	.string "Pronto el equipo de excavación\n"
	.string "atravesará la montaña...\l"
	.string "¡No puedo esperar a ver qué hay\l"
	.string "bajo nuestros pies!$"

SinjohRuins_Lab_Text_Note2:
    .string "Bitácora 2: 10 de mayo, 1975\p"
	.string "Una semana de excavación no ha\n"
	.string "dado ningún resultado.\p"
	.string "The ice here is impossibly thick,\n"
	.string "and the rock just breaks our\l"
	.string "equipment entirely.\p"
	.string "Not even MACHAMP was able to\n"
	.string "make a dent.\p"
	.string "What is this place?\p"
	.string "We must find out.$"

SinjohRuins_Lab_Text_Note3:
    .string "Research Log 3:  May 14, 1975\p"
	.string "You don't get ahead in life by\n"
	.string "standing by and doing nothing.\p"
	.string "I'm just a worker.\p"
	.string "But I had an idea of how we could\n"
	.string "break through the ice.\p"
	.string "Or rather, melt through it.\p"
	.string "We need FIRE-TYPE POKéMON and\n"
	.string "lots of them.\p"
	.string "But how will we get them here\n"
	.string "all the way from SINNOH?$"

SinjohRuins_Lab_Text_Note4:
    .string "Research Log 4:  May 21, 1975\p"
	.string "We've been busy.\p"
	.string "My idea worked to get us through\n"
	.string "the ice. Only we didn't get the\l"
	.string "FIRE-TYPEs from back home.\p"
	.string "The boss insisted we get them locally.\p"
	.string "We found a hot spring by a nearby\n"
	.string "village....\p"
	.string "And we took what we needed...\p"
	.string "I'm not proud of it. But sacrifices\n"
	.string "are sometimes required for progress.\p"
	.string "So, the ice is gone.\p"
	.string "There are 6 chambers, and a sealed\n"
	.string "temple in the center.\p"
	.string "The architecture of the main \n"
	.string "structure indicates it may be of the\l"
	.string "the ancient Celestica peoples...\p"
	.string "Our ancestors. Before they moved north.\p"
	.string "The boss wants that temple open as\n"
	.string "soon as possible...$"

SinjohRuins_Lab_Text_Note5:
    .string "Research Log 5:  June 2, 1975\p"
	.string "We managed to get it open...\p"
	.string "I thought I'd be overjoyed...\p"
	.string "But we lost good men in the blast\n"
	.string "of energy that sprung from the\l"
	.string "siniestro.\p"
	.string "Not to mention the POKéMON that\n"
	.string "helped us get it open.\l"
	.string "God rest their souls...\p"
	.string "........................\p"
	.string "Regardless.\p"
	.string "The temple is open, but we are\n"
	.string "only left with more questions.\p"
	.string "There is no legendary POKéMON\n"
	.string "inside. No treasure.\p"
	.string "Our supplies are starting to run\n"
	.string "out and we have nothing to show\l"
	.string "for our efforts...$"

SinjohRuins_Lab_Text_Note6:
  	.string "Research Log 6:  June 10, 1975\p"
    .string "The expedition is done.\n"
	.string "The rest of the men are packing up.\p"
	.string "But I can't.\p"
	.string "I can't abandon this mission.\n"
	.string "Not after what we've lost.\p"
	.string "I'm going to stay behind.$"

SinjohRuins_Lab_Text_Note7:
  	.string "Research Log 7:  September 10, 1975\p"
	.string "It's been months since we got\n"
	.string "here. Since I got here.\p"
	.string "The rest of the men are gone.\p"
	.string "Now it's just me and the\n"
	.string "POKéMON we captured to help us\l"
	.string "with the work.\p"
	.string "I've been training them to get\n"
	.string "corazón sea más fuerte.\p"
	.string "My TYPHLOSION, most of all.\p"
	.string "We must find out what's beneath\n"
	.string "the temple.$"

SinjohRuins_Lab_Text_Note8:
  	.string "Research Log 8:  September 15, 1975\p"
	.string "Failure.\p"
	.string "......................\p"
	.string "My POKéMON....\p"
	.string "Together, all 6 of my POKéMON\n"
	.string "were able to smash through\n"
	.string "A false wall in the temple.\p"
	.string "But it was waiting for us...\p"
	.string "Something like a giant titan...\p"
	.string "The energy it released was just\n"
	.string "like what happened before.\p"
	.string "They were all destroyed...\p"
	.string "And worst of all, that beast\n"
	.string "sealed the wall back up.\p"
	.string "I can't go home.\n"
	.string "They won't recognize me anymore...\p"
	.string "This place has changed me...\p"
	.string "I'm going to talk with the\n"
	.string "villagers.\p"
	.string "They don't know what I've done.\p"
	.string "Since the other men are long\n"
	.string "gone, they'll think I'm just a\l"
	.string "lost hiker.\p"
	.string "There is no place left for me\n"
	.string "but here.$"

SinjohRuins_EventScript_DisplayCase::
    lock
	msgbox SinjohRuins_DisplayCase_Text MSGBOX_DEFAULT
	release
	end

SinjohRuins_DisplayCase_Text:
    .string "It's a display case neatly\n"
	.string "packed and lined with samples\l"
	.string "and artifacts!$"

SinjohRuins_EventScript_WallSign::
    lock
	msgbox SinjohRuins_WallSign_Text MSGBOX_DEFAULT
	release
	end

SinjohRuins_WallSign_Text:
   .string "Xray and printing lab.$"


SinjohRuins_EventScript_Artifact::
   lock
   msgbox SinjohRuins_Artifact_Text MSGBOX_DEFAULT
   release
   end

SinjohRuins_Artifact_Text:
   .string "It's an artifact found from\n"
   .string "inside the ruins!$"


@==========================Unified other map SCRIPTS================================================================================

SinjohRuins_Lab_EventScript_NoOp::
	release
	end

SinjohRuins_Lab_Text_PlayFlute:
	.string "The AZURE FLUTE is reacting.\n"
	.string "Play the flute?$"

SinjohRuins_Lab_Text_DropedItem:
	.string "The NOBLE {STR_VAR_1} dropped\n"
	.string "an item...$"

SinjohRuins_Lab_Text_StevenName:
	.string "STEVEN$"

SinjohRuins_Lab_EventScript_3Plates::
	setspeaker SinjohRuins_Lab_Text_StevenName
	pokenavcall SinjohRuins_Lab_Text_StevenCall3Plates
	waitmessage
	delay 30
	return
SinjohRuins_Lab_EventScript_6Plates::
	setspeaker SinjohRuins_Lab_Text_StevenName
	pokenavcall SinjohRuins_Lab_Text_StevenCall6Plates
	waitmessage
	delay 30
	return
SinjohRuins_Lab_EventScript_9Plates::
	setspeaker SinjohRuins_Lab_Text_StevenName
	pokenavcall SinjohRuins_Lab_Text_StevenCall9Plates
	waitmessage
	delay 30
	return
SinjohRuins_Lab_EventScript_12Plates::
	setspeaker SinjohRuins_Lab_Text_StevenName
	pokenavcall SinjohRuins_Lab_Text_StevenCall12Plates
	waitmessage
	delay 30
	return
SinjohRuins_Lab_EventScript_15Plates::
	setspeaker SinjohRuins_Lab_Text_StevenName
	pokenavcall SinjohRuins_Lab_Text_StevenCall15Plates
	waitmessage
	delay 30
	return
SinjohRuins_Lab_EventScript_16Plates::
	setspeaker SinjohRuins_Lab_Text_StevenName
	pokenavcall SinjohRuins_Lab_Text_StevenCall16Plates
	waitmessage
	delay 30
	setvar VAR_SINJOH_STORYLINE, 7
	return

SinjohRuins_Lab_Text_StevenCall3Plates:
	.string "STEVEN: {PLAYER}.\p"
	.string "We felt a tremor at the ruins\n"
	.string "just now.\p"
	.string "Everyone's fine, don't worry.\p"
	.string "It's quite intriguing, one of the\n"
	.string "subterranean chambers beneath the\l"
	.string "ruins has sprung open.\p"
	.string "The markings inside remind\n"
	.string "me of something from HOENN.\p"
	.string "You should come take a look\n"
	.string "when you can.$"

SinjohRuins_Lab_Text_StevenCall6Plates:
	.string "STEVEN: {PLAYER}.\p"
	.string "How's the search going?\p"
	.string "We had another tremor here.\n"
	.string "A second chamber opened up\l"
	.string "esta vez.\p"
	.string "I've asked our geologist to keep\n"
	.string "sus instrumentos listos por si\l"
	.string "vuelve a pasar.\p"
	.string "Cuanto más cavamos... más\n"
	.string "preguntas surgen.$"

SinjohRuins_Lab_Text_StevenCall9Plates:
	.string "STEVEN: {PLAYER}.\p"
	.string "Otro temblor aquí en las ruinas.\p"
	.string "Los datos muestran un panorama\n"
	.string "intrigante.\p"
	.string "No fue un terremoto en absoluto.\p"
	.string "Cierta energía se acumuló\n"
	.string "bajo tierra y rompió la\l"
	.string "roca desde el interior.\p"
	.string "Qué podría causar eso...\n"
	.string "I honestly don't know.$"

SinjohRuins_Lab_Text_StevenCall12Plates:
	.string "STEVEN: {PLAYER}.\p"
	.string "Another tremor. Another chamber\n"
	.string "opening up.\p"
	.string "We still can't figure out the\n"
	.string "pattern behind the timing.\p"
	.string "Say, {PLAYER}... you're not\n"
	.string "doing something to cause all\l"
	.string "this, are you?\p"
	.string "No, that can't be right.$"

SinjohRuins_Lab_Text_StevenCall15Plates:
	.string "STEVEN: {PLAYER}.\p"
	.string "Did you just find another PLATE?\p"
	.string ".................\p"
	.string "Of course.\p"
	.string "The legendary POKéMON lying\n"
	.string "en estas ruinas... responden\l"
	.string "a ti, ¿verdad?\p"
	.string "Como si quisieran ser hallados.\p"
	.string "Mis predicciones suelen cumplirse.\n"
	.string "No debí haber cometido el error\l"
	.string "de dudar de ti.$"

SinjohRuins_Lab_Text_StevenCall16Plates:
	.string "STEVEN: {PLAYER}.\p"
	.string "Estamos muy cerca. Lo siento.\p"
	.string "..................\p"
	.string "Deberías venir a ver esto por\n"
	.string "ti mismo.$"

