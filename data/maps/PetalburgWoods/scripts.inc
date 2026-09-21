PetalburgWoods_MapScripts::
	.byte 0

PetalburgWoods_EventScript_DevonResearcherLeft::
	lockall
	call PetalburgWoods_EventScript_DevonResearcherIntro
	applymovement LOCALID_PETALBURG_WOODS_DEVON_EMPLOYEE, PetalburgWoods_Movement_DevonResearcherApproachPlayerLeft
	waitmovement 0
	msgbox PetalburgWoods_Text_HaveYouSeenShroomish, MSGBOX_DEFAULT
	closemessage
	playbgm MUS_ENCOUNTER_AQUA, FALSE
	applymovement LOCALID_PETALBURG_WOODS_GRUNT, PetalburgWoods_Movement_AquaEntrance
	waitmovement 0
	msgbox PetalburgWoods_Text_IWasGoingToAmbushYou, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PETALBURG_WOODS_GRUNT, PetalburgWoods_Movement_AquaApproachResearcherLeft
	waitmovement 0
	applymovement LOCALID_PETALBURG_WOODS_DEVON_EMPLOYEE, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox PetalburgWoods_Text_HandOverThosePapers, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PETALBURG_WOODS_DEVON_EMPLOYEE, PetalburgWoods_Movement_DevonResearcherFleeToPlayerLeft
	waitmovement 0
	msgbox PetalburgWoods_Text_YouHaveToHelpMe, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PETALBURG_WOODS_GRUNT, PetalburgWoods_Movement_AquaApproachPlayer
	waitmovement 0
	msgbox PetalburgWoods_Text_NoOneCrossesTeamAqua, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_GRUNT_PETALBURG_WOODS, PetalburgWoods_Text_YoureKiddingMe
	applymovement LOCALID_PETALBURG_WOODS_GRUNT, PetalburgWoods_Movement_AquaBackOff
	waitmovement 0
	call PetalburgWoods_EventScript_DevonResearcherPostBattle
	applymovement LOCALID_PLAYER, PetalburgWoods_Movement_WatchResearcherLeave
	applymovement LOCALID_PETALBURG_WOODS_DEVON_EMPLOYEE, PetalburgWoods_Movement_DevonResearcherExitLeft
	waitmovement 0
	goto PetalburgWoods_EventScript_RemoveDevonResearcher
	end

PetalburgWoods_EventScript_DevonResearcherRight::
	lockall
	call PetalburgWoods_EventScript_DevonResearcherIntro
	applymovement LOCALID_PETALBURG_WOODS_DEVON_EMPLOYEE, PetalburgWoods_Movement_DevonResearcherApproachPlayerRight
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	msgbox PetalburgWoods_Text_HaveYouSeenShroomish, MSGBOX_DEFAULT
	closemessage
	playbgm MUS_ENCOUNTER_AQUA, FALSE
	applymovement LOCALID_PETALBURG_WOODS_GRUNT, PetalburgWoods_Movement_AquaEntrance
	waitmovement 0
	msgbox PetalburgWoods_Text_IWasGoingToAmbushYou, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PETALBURG_WOODS_GRUNT, PetalburgWoods_Movement_AquaApproachResearcherRight
	waitmovement 0
	applymovement LOCALID_PETALBURG_WOODS_DEVON_EMPLOYEE, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox PetalburgWoods_Text_HandOverThosePapers, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PETALBURG_WOODS_DEVON_EMPLOYEE, PetalburgWoods_Movement_DevonResearcherFleeToPlayerRight
	waitmovement 0
	msgbox PetalburgWoods_Text_YouHaveToHelpMe, MSGBOX_DEFAULT
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox PetalburgWoods_Text_NoOneCrossesTeamAqua, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_GRUNT_PETALBURG_WOODS, PetalburgWoods_Text_YoureKiddingMe
	applymovement LOCALID_PETALBURG_WOODS_GRUNT, PetalburgWoods_Movement_AquaBackOff
	waitmovement 0
	call PetalburgWoods_EventScript_DevonResearcherPostBattle
	applymovement LOCALID_PLAYER, PetalburgWoods_Movement_WatchResearcherLeave
	applymovement LOCALID_PETALBURG_WOODS_DEVON_EMPLOYEE, PetalburgWoods_Movement_DevonResearcherExitRight
	waitmovement 0
	goto PetalburgWoods_EventScript_RemoveDevonResearcher
	end

PetalburgWoods_EventScript_DevonResearcherIntro::
	applymovement LOCALID_PETALBURG_WOODS_DEVON_EMPLOYEE, PetalburgWoods_Movement_DevonResearcherLookAround
	waitmovement 0
	msgbox PetalburgWoods_Text_NotAOneToBeFound, MSGBOX_DEFAULT
	closemessage
	return

PetalburgWoods_EventScript_DevonResearcherPostBattle::
	msgbox PetalburgWoods_Text_YouveGotSomeNerve, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PETALBURG_WOODS_GRUNT, PetalburgWoods_Movement_AquaRunAway
	waitmovement 0
	removeobject LOCALID_PETALBURG_WOODS_GRUNT
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox PetalburgWoods_Text_ThatWasAwfullyClose, MSGBOX_DEFAULT
	giveitem ITEM_GREAT_BALL
	goto_if_eq VAR_RESULT, FALSE, PetalburgWoods_EventScript_BagFull
	goto PetalburgWoods_EventScript_DevonResearcherFinish
	end

PetalburgWoods_EventScript_BagFull::
	msgbox PetalburgWoods_Text_YoureLoadedWithItems, MSGBOX_DEFAULT
	goto PetalburgWoods_EventScript_DevonResearcherFinish
	end

PetalburgWoods_EventScript_DevonResearcherFinish::
	msgbox PetalburgWoods_Text_TeamAquaAfterSomethingInRustboro, MSGBOX_DEFAULT
	applymovement LOCALID_PETALBURG_WOODS_DEVON_EMPLOYEE, PetalburgWoods_Movement_DevonResearcherStartExit
	waitmovement 0
	msgbox PetalburgWoods_Text_ICantBeWastingTime, MSGBOX_DEFAULT
	closemessage
	return

PetalburgWoods_EventScript_RemoveDevonResearcher::
	removeobject LOCALID_PETALBURG_WOODS_DEVON_EMPLOYEE
	setvar VAR_PETALBURG_WOODS_STATE, 1
	releaseall
	end

PetalburgWoods_Movement_DevonResearcherLookAround:
	face_up
	delay_16
	delay_4
	face_right
	delay_16
	delay_8
	face_left
	delay_16
	delay_8
	face_down
	delay_16
	face_right
	delay_16
	delay_8
	face_up
	delay_16
	step_end

PetalburgWoods_Movement_DevonResearcherExitLeft:
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

PetalburgWoods_Movement_DevonResearcherApproachPlayerLeft:
	delay_16
	face_player
	walk_down
	walk_down
	step_end

PetalburgWoods_Movement_DevonResearcherApproachPlayerRight:
	delay_16
	face_player
	walk_down
	walk_down
	walk_down
	walk_in_place_faster_right
	step_end

PetalburgWoods_Movement_DevonResearcherExitRight:
	walk_fast_left
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

PetalburgWoods_Movement_WatchResearcherLeave:
	delay_16
	delay_16
	walk_in_place_faster_up
	step_end

PetalburgWoods_Movement_DevonResearcherFleeToPlayerLeft:
	walk_fast_right
	walk_fast_down
	walk_fast_down
	walk_fast_left
	walk_in_place_faster_up
	step_end

PetalburgWoods_Movement_DevonResearcherFleeToPlayerRight:
	walk_fast_down
	walk_fast_right
	walk_in_place_faster_up
	step_end

PetalburgWoods_Movement_DevonResearcherStartExit:
	walk_in_place_faster_down
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	face_up
	step_end

PetalburgWoods_Movement_AquaApproachResearcherLeft:
	walk_fast_down
	walk_fast_down
	step_end

PetalburgWoods_Movement_AquaBackOff:
	lock_facing_direction
	walk_up
	unlock_facing_direction
	step_end

PetalburgWoods_Movement_AquaRunAway:
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	delay_16
	delay_16
	step_end

PetalburgWoods_Movement_AquaApproachResearcherRight:
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end

PetalburgWoods_Movement_AquaEntrance:
	walk_down
	walk_down
	delay_16
	delay_16
	step_end

PetalburgWoods_Movement_AquaApproachPlayer:
	walk_down
	step_end

PetalburgWoods_EventScript_Boy1::
	msgbox PetalburgWoods_Text_StayOutOfTallGrass, MSGBOX_NPC
	end

PetalburgWoods_EventScript_Boy2::
	msgbox PetalburgWoods_Text_HiddenItemsExplanation, MSGBOX_NPC
	end

PetalburgWoods_EventScript_Girl::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_MIRACLE_SEED, PetalburgWoods_EventScript_ExplainMiracleSeed
	msgbox PetalburgWoods_Text_TryUsingThisItem, MSGBOX_DEFAULT
	giveitem ITEM_MIRACLE_SEED
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_MIRACLE_SEED
	release
	end

PetalburgWoods_EventScript_ExplainMiracleSeed::
	msgbox PetalburgWoods_Text_MiracleSeedExplanation, MSGBOX_DEFAULT
	release
	end

PetalburgWoods_EventScript_Sign1::
	msgbox PetalburgWoods_Text_TrainerTipsExperience, MSGBOX_SIGN
	end

PetalburgWoods_EventScript_Sign2::
	msgbox PetalburgWoods_Text_TrainerTipsPP, MSGBOX_SIGN
	end

PetalburgWoods_EventScript_Lyle::
	trainerbattle_single TRAINER_LYLE, PetalburgWoods_Text_GoBugPokemonTeam, PetalburgWoods_Text_ICouldntWin
	msgbox PetalburgWoods_Text_ImOutOfPokeBalls, MSGBOX_AUTOCLOSE
	end

PetalburgWoods_EventScript_James::
	trainerbattle_single TRAINER_JAMES_1, PetalburgWoods_Text_InstantlyPopularWithBugPokemon, PetalburgWoods_Text_CantBePopularIfILose, PetalburgWoods_EventScript_TryRegisterJames
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, PetalburgWoods_EventScript_JamesRematch
	setvar VAR_0x8004, TRAINER_JAMES_1
	specialvar VAR_RESULT, IsTrainerRegistered
	goto_if_eq VAR_RESULT, FALSE, PetalburgWoods_EventScript_TryRegisterJames2
	msgbox PetalburgWoods_Text_PeopleRespectYou, MSGBOX_DEFAULT
	release
	end

PetalburgWoods_EventScript_TryRegisterJames::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	goto_if_set FLAG_HAS_MATCH_CALL, PetalburgWoods_EventScript_RegisterJames
	release
	end

PetalburgWoods_EventScript_RegisterJames::
	msgbox PetalburgWoods_Text_IWantRematch1, MSGBOX_DEFAULT
	register_matchcall TRAINER_JAMES_1
	release
	end

PetalburgWoods_EventScript_TryRegisterJames2::
	goto_if_set FLAG_HAS_MATCH_CALL, PetalburgWoods_EventScript_RegisterJames2
	msgbox PetalburgWoods_Text_PeopleRespectYou, MSGBOX_DEFAULT
	release
	end

PetalburgWoods_EventScript_RegisterJames2::
	msgbox PetalburgWoods_Text_IWantRematch2, MSGBOX_DEFAULT
	register_matchcall TRAINER_JAMES_1
	release
	end

PetalburgWoods_EventScript_JamesRematch::
	trainerbattle_rematch TRAINER_JAMES_1, PetalburgWoods_Text_MyPokemonHaveGrown, PetalburgWoods_Text_CantBePopularIfLose
	msgbox PetalburgWoods_Text_IveBeenTrainingHard, MSGBOX_AUTOCLOSE
	end

PetalburgWoods_Text_NotAOneToBeFound:
	.string "Hmmm...\n"
	.string "No hay ni uno solo...$"

PetalburgWoods_Text_HaveYouSeenShroomish:
	.string "Hola, ¿has visto algún POKéMON\n"
	.string "llamado SHROOMISH por aquí?\p"
	.string "¡Me encanta ese POKéMON!$"

PetalburgWoods_Text_IWasGoingToAmbushYou:
	.string "Iba a emboscarte, pero tuviste\n"
	.string "que tardar en el BOSQUE PETALBURG\l"
	.string "una eternidad, ¿verdad?\p"
	.string "¡Me cansé de esperar, así que vine!$"

PetalburgWoods_Text_HandOverThosePapers:
	.string "¡Tú! ¡INVESTIGADOR DE DEVON!\p"
	.string "¡Dame esos papeles!$"

PetalburgWoods_Text_YouHaveToHelpMe:
	.string "¡Aiyeeeh!\p"
	.string "Eres ENTRENADOR POKéMON, ¿verdad?\n"
	.string "¡Tienes que ayudarme, por favor!$"

PetalburgWoods_Text_NoOneCrossesTeamAqua:
	.string "¿Eh? ¿Qué crees que estás haciendo?\n"
	.string "¿Qué, vas a protegerlo?\p"
	.string "Nadie que se cruce con el TEAM AQUA\n"
	.string "tendrá piedad, ¡ni siquiera un niño!\p"
	.string "¡Ven y lucha contra mí!$"

PetalburgWoods_Text_YoureKiddingMe:
	.string "¡No me digas! ¡Eres fuerte!$"

PetalburgWoods_Text_YouveGotSomeNerve:
	.string "Grrr... Tienes mucho valor al\n"
	.string "meterte con el TEAM AQUA!\l"
	.string "¡Ven y lucha contra mí otra vez!\p"
	.string "Quisiera decir que sí, pero me he\n"
	.string "POKéMON…\p"
	.string "Y, oye, nosotros del TEAM AQUA también\n"
	.string "algo en FUNDAHOJA.\p"
	.string "¡Te dejaré ir hoy!$"

PetalburgWoods_Text_ThatWasAwfullyClose:
	.string "Uff...\n"
	.string "¡Eso estuvo muy cerca!\p"
	.string "Gracias a ti, no me robó\n"
	.string "estos papeles importantes.\p"
	.string "Lo sé, ¡te daré una GREAT BALL\n"
	.string "como agradecimiento!$"

PetalburgWoods_Text_TeamAquaAfterSomethingInRustboro:
	.string "¿No dijo ese matón del TEAM AQUA\n"
	.string "que buscaban algo en\l"
	.string "FUNDAHOJA también?$"

PetalburgWoods_Text_ICantBeWastingTime:
	.string "¡Oh, no! ¡Es una crisis!\n"
	.string "¡No puedo perder tiempo!$"

PetalburgWoods_Text_YoureLoadedWithItems:
	.string "Llevas demasiados objetos.\n"
	.string "No puedo darte esta GREAT BALL.$"

PetalburgWoods_Text_GoBugPokemonTeam:
	.string "¡Atrapé muchísimos POKéMON!\p"
	.string "Go, go, go!\n"
	.string "¡Mi equipo de POKéMON bicho!$"

PetalburgWoods_Text_ICouldntWin:
	.string "Tengo todos estos POKéMON,\n"
	.string "pero no pude ganar…$"

PetalburgWoods_Text_ImOutOfPokeBalls:
	.string "Atrapé varios POKéMON.\n"
	.string "Ahora no tengo POKé BALLS.$"

PetalburgWoods_Text_InstantlyPopularWithBugPokemon:
	.string "Si llevas POKéMON bicho a clase,\n"
	.string "¡te haces popular al instante!$"

PetalburgWoods_Text_CantBePopularIfILose:
	.string "No puedo ser popular si pierdo.$"

PetalburgWoods_Text_PeopleRespectYou:
	.string "Si tienes un POKéMON bicho grande,\n"
	.string "la gente te respeta por eso.$"

PetalburgWoods_Text_IWantRematch1:
	.string "Quiero revancha cuando mi POKéMON\n"
	.string "BICHÓ crezca!\p"
	.string "¡Te registraré en mi POKéNAV!$"

PetalburgWoods_Text_IWantRematch2:
	.string "Quiero revancha cuando mi BICHÓ \n"
	.string "BICHÓ crezca!\p"
	.string "¡Te registraré en mi POKéNAV!$"

PetalburgWoods_Text_MyPokemonHaveGrown:
	.string "Mis POKéMON BICHÓ han crecido.\n"
	.string "Volveré a ser popular.$"

PetalburgWoods_Text_CantBePopularIfLose:
	.string "No puedo ser popular si pierdo.$"

PetalburgWoods_Text_IveBeenTrainingHard:
	.string "Eres popular si tienes\n"
	.string "POKéMON fuertes, ¿verdad?\l"
	.string "Por eso, he entrenado duro.$"

PetalburgWoods_Text_StayOutOfTallGrass:
	.string "¡Hola, tú!\n"
	.string "¿Tus POKéMON están bien?\p"
	.string "Si tus POKéMON son débiles y quieres\n"
	.string "para evitar batallas, no entres\l"
	.string "en la hierba alta.$"

PetalburgWoods_Text_HiddenItemsExplanation:
	.string "A veces hay cosas en el suelo\n"
	.string "aunque no se puedan ver.\p"
	.string "Por eso siempre reviso por dónde\n"
	.string "camino.$"

PetalburgWoods_Text_TryUsingThisItem:
	.string "¡Oh, genial!\n"
	.string "¡Es la MEDALLA del GIMNASIO RUSTBORO!\p"
	.string "Debes ser un ENTRENADOR.\n"
	.string "Deberías intentar usar este objeto.$"

PetalburgWoods_Text_MiracleSeedExplanation:
	.string "Es una SEMILLA MILAGRO.\n"
	.string "Si un POKéMON lo lleva, su\l"
	.string "GRASS-type moves become stronger.\p"
	.string "Además de la SEMILLA MILAGRO, creo\n"
	.string "que hay otros objetos útiles para que\l"
	.string "los POKéMON los lleven.$"

PetalburgWoods_Text_TrainerTipsExperience:
	.string "CONSEJOS DE ENTRENADOR\p"
	.string "Cualquier POKéMON que aparezca aunque\n"
	.string "sea una vez ganará puntos de EXP.\p"
	.string "Para subir a un POKéMON débil, ponlo\n"
	.string "al principio de la lista del equipo.\p"
	.string "Al iniciar el combate, cámbialo\n"
	.string "Ganará puntos de EXP sin correr\l"
	.string "ningún peligro.$"

PetalburgWoods_Text_TrainerTipsPP:
	.string "CONSEJOS DE ENTRENADOR\p"
	.string "In addition to Hit Points (HP), POKéMON\n"
	.string "tienen Puntos de Poder (PP) que se\l"
	.string "usan para hacer ataques en batalla.\p"
	.string "Si un POKéMON se queda sin PP, debe\n"
	.string "ir a un CENTRO POKéMON.$"

