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
	.string "Quisiera más tiempo para estudiarlos.$"

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
	.string "El hielo aquí es demasiado grueso,\n"
	.string "y la roca simplemente rompe todo\l"
	.string "nuestro equipo.\p"
	.string "Ni siquiera MACHAMP pudo\n"
	.string "hacerle un rasguño.\p"
	.string "¿Qué es este lugar?\p"
	.string "Debemos averiguarlo.$"

SinjohRuins_Lab_Text_Note3:
    .string "Bitácora 3: 14 de mayo, 1975\p"
	.string "No avanzas en la vida si te\n"
	.string "quedas ahí sin hacer nada.\p"
	.string "Solo soy un trabajador.\p"
	.string "Pero tuve una idea de cómo\n"
	.string "atravesar el hielo.\p"
	.string "O mejor dicho, derretirlo.\p"
	.string "Necesitamos POKéMON tipo FUEGO y\n"
	.string "muchos de ellos.\p"
	.string "Pero ¿cómo los traeremos\n"
	.string "desde SINNOH?$"

SinjohRuins_Lab_Text_Note4:
    .string "Bitácora 4: 21 de mayo, 1975\p"
	.string "Hemos estado ocupados.\p"
	.string "Mi idea funcionó para cruzar\n"
	.string "el hielo. Solo que no trajimos\l"
	.string "los tipo FUEGO de nuestro hogar.\p"
	.string "El jefe insistió en comprarlas aquí.\p"
	.string "Hallamos una fuente termal cerca de\n"
	.string "un pueblo...\p"
	.string "Y tomamos lo que necesitábamos...\p"
	.string "I'm not proud of it. But sacrifices\n"
	.string "son necesarios para el progreso.\p"
	.string "Así que el hielo desapareció.\p"
	.string "Hay 6 cámaras y un templo sellado\n"
	.string "en el centro.\p"
	.string "La arquitectura de la estructura\n"
	.string "principal indica que podría ser de\l"
	.string "los antiguos pueblos de Celestica...\p"
	.string "Ancestros, antes de ir al norte.\p"
	.string "El jefe quiere que abran el templo\n"
	.string "lo antes posible...$"

SinjohRuins_Lab_Text_Note5:
    .string "Bitácora 5: 2 de junio de 1975\p"
	.string "Logramos abrirlo...\p"
	.string "Pensé que estaría feliz...\p"
	.string "Pero perdimos hombres buenos en la\n"
	.string "explosión de energía que surgió.\l"
	.string "siniestro.\p"
	.string "Sin mencionar a los POKéMON que\n"
	.string "nos ayudaron a abrirlo.\l"
	.string "Que Dios descanse sus almas...\p"
	.string "........................\p"
	.string "Sea como sea.\p"
	.string "El templo está abierto, pero solo\n"
	.string "nos quedan más preguntas.\p"
	.string "No hay ningún POKéMON legendario\n"
	.string "dentro. Ni tesoros.\p"
	.string "Nuestros suministros se están\n"
	.string "agotando y no tenemos nada que\l"
	.string "mostrar por nuestro esfuerzo...$"

SinjohRuins_Lab_Text_Note6:
  	.string "Bitácora 6: 10 de junio, 1975\p"
    .string "La expedición ha terminado.\n"
	.string "Los demás hombres están empacando.\p"
	.string "Pero yo no puedo.\p"
	.string "No puedo abandonar esta misión.\n"
	.string "No después de lo que perdimos.\p"
	.string "Me quedaré aquí.$"

SinjohRuins_Lab_Text_Note7:
  	.string "Bitácora 7: 10 de sept. de 1975\p"
	.string "Han pasado meses desde que\n"
	.string "llegamos. Desde que yo llegué.\p"
	.string "El resto de los hombres se fue.\p"
	.string "Ahora solo quedo yo y los\n"
	.string "POKéMON que capturamos para\l"
	.string "ayudarnos con el trabajo.\p"
	.string "Los he entrenado para lograrlo,\n"
	.string "corazón sea más fuerte.\p"
	.string "sobre todo a mi TYPHLOSION.\p"
	.string "Debemos saber qué hay debajo\n"
	.string "el templo.$"

SinjohRuins_Lab_Text_Note8:
  	.string "Bitácora 8: 15 de sept. de 1975\p"
	.string "Fracaso.\p"
	.string "......................\p"
	.string "Mis POKéMON....\p"
	.string "Juntos, mis 6 POKéMON\n"
	.string "pudieron atravesar\n"
	.string "una pared falsa en el templo.\p"
	.string "Pero algo nos esperaba...\p"
	.string "Algo como un titán gigante...\p"
	.string "La energía que liberó fue\n"
	.string "como lo que pasó antes.\p"
	.string "Todos fueron destruidos...\p"
	.string "Y lo peor de todo, que esa bestia\n"
	.string "volvió a sellar el muro.\p"
	.string "No puedo volver a casa.\n"
	.string "Ya no me reconocerán...\p"
	.string "Este lugar me ha cambiado...\p"
	.string "Voy a hablar con los\n"
	.string "aldeanos.\p"
	.string "No saben lo que he hecho.\p"
	.string "Como los otros hombres se han\n"
	.string "ido, creerán que soy solo un\l"
	.string "senderista perdido.\p"
	.string "Ya no queda lugar para mí\n"
	.string "pero aquí.$"

SinjohRuins_EventScript_DisplayCase::
    lock
	msgbox SinjohRuins_DisplayCase_Text MSGBOX_DEFAULT
	release
	end

SinjohRuins_DisplayCase_Text:
    .string "Es una vitrina muy bien\n"
	.string "llena de muestras\l"
	.string "y artefactos!$"

SinjohRuins_EventScript_WallSign::
    lock
	msgbox SinjohRuins_WallSign_Text MSGBOX_DEFAULT
	release
	end

SinjohRuins_WallSign_Text:
   .string "Lab. de rayos X e impresión.$"


SinjohRuins_EventScript_Artifact::
   lock
   msgbox SinjohRuins_Artifact_Text MSGBOX_DEFAULT
   release
   end

SinjohRuins_Artifact_Text:
   .string "¡Es un artefacto hallado\n"
   .string "dentro de las ruinas!$"


@==========================Unified other map SCRIPTS================================================================================

SinjohRuins_Lab_EventScript_NoOp::
	release
	end

SinjohRuins_Lab_Text_PlayFlute:
	.string "La FLAUTA AZUL reacciona.\n"
	.string "¿Tocar la flauta?$"

SinjohRuins_Lab_Text_DropedItem:
	.string "El NOBLE {STR_VAR_1} soltó\n"
	.string "un objeto...$"

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
	.string "Sentimos un temblor en las ruinas\n"
	.string "ahora mismo.\p"
	.string "Todos están bien, no te preocupes.\p"
	.string "Es muy intrigante, una de las\n"
	.string "cámaras subterráneas bajo las\l"
	.string "ruinas se ha abierto.\p"
	.string "Las marcas de adentro me\n"
	.string "recuerdan a algo de HOENN.\p"
	.string "Deberías venir a echar un vistazo\n"
	.string "cuando puedas.$"

SinjohRuins_Lab_Text_StevenCall6Plates:
	.string "STEVEN: {PLAYER}.\p"
	.string "¿Cómo va la búsqueda?\p"
	.string "Hubo otro temblor aquí.\n"
	.string "Se abrió una segunda cámara\l"
	.string "esta vez.\p"
	.string "Le pedí al geólogo que guardara\n"
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
	.string "Sinceramente, no lo sé.$"

SinjohRuins_Lab_Text_StevenCall12Plates:
	.string "STEVEN: {PLAYER}.\p"
	.string "Otro temblor. Otra cámara\n"
	.string "abriéndose.\p"
	.string "Aún no entendemos el\n"
	.string "patrón de los tiempos.\p"
	.string "Oye, {PLAYER}... no estarás\n"
	.string "haciendo algo para causar\l"
	.string "todo esto, ¿verdad?\p"
	.string "No, eso no puede ser.$"

SinjohRuins_Lab_Text_StevenCall15Plates:
	.string "STEVEN: {PLAYER}.\p"
	.string "¿Acabas de hallar otra PLACA?\p"
	.string ".................\p"
	.string "Claro que sí.\p"
	.string "El POKéMON legendario que yace\n"
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

