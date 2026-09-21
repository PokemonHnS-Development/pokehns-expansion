Route39_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route39_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route39_OnTransition: 
	callnative SetTimeBasedEncounters
	end

Route39_EventScript_Item_TM::
	finditem ITEM_TM_DRAIN_PUNCH
	end

Route39_EventScript_Item_Nugget::
	finditem ITEM_BIG_NUGGET
	end

Route39_EventScript_LegendaryTrigger::
	lock
	clearflag FLAG_HIDE_ROUTE39_SHADOW
	addobject LOCALID_R39_SHADOW
	playse SE_M_RAZOR_WIND
	applymovement LOCALID_R39_SHADOW, Route39_Movement_ShadowSlideDown
	waitmovement 0
	setflag FLAG_HIDE_ROUTE39_SHADOW
	removeobject LOCALID_R39_SHADOW
	playse SE_PIN
	applymovement LOCALID_R39_BAOBA, Common_Movement_QuestionMark
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_QuestionMark
	turnobject LOCALID_R39_BAOBA DIR_SOUTH
	turnobject OBJ_EVENT_ID_PLAYER DIR_SOUTH
	delay 60

	getplayerxy VAR_TEMP_0, VAR_TEMP_1

	call_if_eq VAR_TEMP_1, 20, Route39_EventScript_BaobaMovement1
	call_if_eq VAR_TEMP_1, 21, Route39_EventScript_BaobaMovement2
	call_if_eq VAR_TEMP_1, 22, Route39_EventScript_BaobaMovement3
	call_if_eq VAR_TEMP_1, 23, Route39_EventScript_BaobaMovement4

	turnobject LOCALID_R39_BAOBA DIR_EAST
	turnobject OBJ_EVENT_ID_PLAYER DIR_WEST
Route39_EventScript_ChooseLegend::
	msgbox Route39_Text_ChooseLegend, MSGBOX_DEFAULT
	multichoice 20, 8, MULTI_GOLDSILVER, FALSE
	switch VAR_RESULT
	case 0, Route39_EventScript_LegendaryTriggerGold
	case 1, Route39_EventScript_LegendaryTriggerSilver
	case MULTI_B_PRESSED, Route39_EventScript_ChooseLegend
	release
	end

Route39_EventScript_BaobaMovement1::
	applymovement LOCALID_R39_BAOBA, Route39_Movement_Baoba1
	waitmovement 0
	return
Route39_EventScript_BaobaMovement2::
	applymovement LOCALID_R39_BAOBA, Route39_Movement_Baoba2
	waitmovement 0
	return
Route39_EventScript_BaobaMovement3::
	applymovement LOCALID_R39_BAOBA, Route39_Movement_Baoba3
	waitmovement 0
	return
Route39_EventScript_BaobaMovement4::
	applymovement LOCALID_R39_BAOBA, Route39_Movement_Baoba4
	waitmovement 0
	return

Route39_Movement_Baoba1:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	step_end
Route39_Movement_Baoba2:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	step_end
Route39_Movement_Baoba3:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	step_end
Route39_Movement_Baoba4:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	step_end

Route39_EventScript_LegendaryTriggerGold::
	setvar VAR_LUGIA_OR_HOOH, 2
	goto Route39_EventScript_BaobaIntro

Route39_EventScript_LegendaryTriggerSilver::
	setvar VAR_LUGIA_OR_HOOH, 1
	goto Route39_EventScript_BaobaIntro

Route39_EventScript_BaobaIntro::
	msgbox Route39_Text_BaobaIntro, MSGBOX_DEFAULT
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox Route39_Text_Registered, MSGBOX_DEFAULT
	waitfanfare
	msgbox Route39_Text_WillCall, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_R39_BAOBA, Route39_Movement_BaobaLeave
	waitmovement 0
	setflag FLAG_ENABLE_BAOBA_MATCH_CALL
	removeobject LOCALID_R39_BAOBA
	release
	end

Route39_Text_ChooseLegend::
	.string "BAOBA: ¡Cielos! ¿Esa sombra\n"
	.string "era de un POKéMON?\p"
	.string "¿Lograste verlo bien?\n"
	.string "No sé de qué color era...$"

Route39_Text_BaobaIntro::
	.string "Qué extraño...\p"
	.string "...¡Oh!\n"
	.string "Lo que tienes ahí es...\l"
	.string "¡lo que llaman... una POKéDEX!\p"
	.string "No veía una hace siglos.\p"
	.string "¡Mi nombre es BAOBA!\n"
	.string "Dirigía una ZONA SAFARI en\l"
	.string "CIUDAD FUSCHIA, pero se estaba\l"
	.string "estaba desactualizado con el nuevo\l"
	.string "entretenimiento disponible.\p"
	.string "Decidí ir al extranjero para aprender\n"
	.string "la tecnología más nueva y abrir una\l"
	.string "ZONA SAFARI vanguardista\l"
	.string "en CIUDAD ORQUIDEA.\p"
	.string "Puede que no sea coincidencia\n"
	.string "que estemos charlando.\p"
	.string "¡Registremos nuestros números\n"
	.string "en el POKéGEAR!\p"
	.string "Te llamaré en cuanto la\n"
	.string "La ZONA SAFARI abre antes de llamar\l"
	.string "¡nadie más!$"

Route39_Text_Registered:
	.string "{PLAYER} registró a BAOBA\n"
	.string "¡en el POKéGEAR!$"


Route39_Text_WillCall:
	.string "BAOBA: ¡Te avisaré\n"
	.string "pronto por el POKéGEAR!$"

Route39_Movement_BaobaLeave:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

Route39_Movement_ShadowSlideDown:
	slide_down
	slide_down
	slide_down
	slide_down
	slide_down
	slide_down
	slide_down
	slide_down
	slide_down
	slide_down
	slide_down
	slide_down
	slide_down
	slide_down
	slide_down
	slide_down
	slide_down
	slide_down
	slide_down
	slide_down
	step_end

Route39_EventScript_Woman::
	lock
	faceplayer
	msgbox Route39_Text_Woman, MSGBOX_DEFAULT
	closemessage
	release
	end

Route39_Text_Woman:
	.string "Esa sombra... ¿Será un PIDGEY\n
gigante?$"

Route39_EventScript_Miltank::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_MILTANK, CRY_MODE_NORMAL
	msgbox Route39_Text_Miltank, MSGBOX_DEFAULT
	waitmoncry
	release
	end

Route39_Text_Miltank:
	.string "MILTANK: Mooo!$"

Route39_EventScript_Eugene::
	trainerbattle_single TRAINER_EUGENE_HNS, Route39_Text_SailorEugeneSeen, Route39_Text_SailorEugeneBeaten
	msgbox Route39_Text_SailorEugeneAfter, MSGBOX_AUTOCLOSE
	end

Route39_Text_SailorEugeneSeen:
	.string "Acabo de volver a CIUDAD OLIVO.\p"
	.string "¿Qué tal una batalla POKéMON?$"

Route39_Text_SailorEugeneBeaten:
	.string "Awaaargh!$"

Route39_Text_SailorEugeneAfter:
	.string "Mis POKéMON fueron capturados y\n"
	.string "criados en el extranjero.\p"
	.string "Son mis compañeros en\n"
	.string "esos largos viajes.$"

Route39_EventScript_Derek::
	trainerbattle_single TRAINER_DEREK_HNS, Route39_Text_PokefanMDerekSeen, Route39_Text_PokefanMDerekBeaten, Route39_EventScript_RegisterDerek
	goto_if_set FLAG_DEREK_HAS_ITEM_HNS, Route39_EventScript_DerekGiveItem
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route39_EventScript_RematchDerek
	msgbox Route39_Text_PokefanMDerekAfter, MSGBOX_AUTOCLOSE
	end

Route39_EventScript_RematchDerek::
	trainerbattle_rematch TRAINER_DEREK_HNS, Route39_Text_PokefanMDerekSeen, Route39_Text_PokefanMDerekBeaten
	msgbox Route39_Text_PokefanMDerekAfter, MSGBOX_AUTOCLOSE
	end

Route39_EventScript_RegisterDerek::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route39_Text_DerekRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_DEREK_HNS
	release
	end

Route39_EventScript_DerekGiveItem::
	msgbox Route39_Text_DerekHasItem, MSGBOX_DEFAULT
	giveitem VAR_DEREK_ITEM_HNS
	goto_if_eq VAR_RESULT, FALSE, Route39_EventScript_DerekNoRoom
	clearflag FLAG_DEREK_HAS_ITEM_HNS
	msgbox Route39_Text_DerekGaveItem, MSGBOX_AUTOCLOSE
	end

Route39_EventScript_DerekNoRoom::
	msgbox Route39_Text_DerekNoRoom, MSGBOX_AUTOCLOSE
	end

Route39_Text_PokefanMDerekSeen:
	.string "¡Es buen momento para presumir\n"
	.string "de mi PIKACHU!$"

Route39_Text_PokefanMDerekBeaten:
	.string "No tuve tiempo de lucir a\n"
	.string "PIKACHU…$"

Route39_Text_PokefanMDerekAfter:
	.string "¡No voy a escuchar tus\n"
	.string "presunciones!\p"
	.string "¡Los POKé FANS no tenemos\n"
	.string "costumbre de oír presumidos!$"

Route39_EventScript_Ruth::
	trainerbattle_single TRAINER_RUTH_HNS, Route39_Text_PokefanFRuthSeen, Route39_Text_PokefanFRuthBeaten
	msgbox Route39_Text_PokefanFRuthAfter, MSGBOX_AUTOCLOSE
	end

Route39_Text_PokefanFRuthSeen:
	.string "Qué POKéMON tan lindos.\p"
	.string "Mostremos nuestros POKéMON\n"
	.string "juntos al mismo tiempo.$"

Route39_Text_PokefanFRuthBeaten:
	.string "I don't mind losing.$"

Route39_Text_PokefanFRuthAfter:
	.string "¿Sabes sobre los bebés\n"
	.string "con los POKéMON?\p"
	.string "¡Apuesto a que son adorables!$"

Route39_EventScript_Norman::
	trainerbattle_single TRAINER_NORMAN_HNS, Route39_Text_PsychicNormanSeen, Route39_Text_PsychicNormanBeaten
	msgbox Route39_Text_PsychicNormanAfter, MSGBOX_AUTOCLOSE
	end

Route39_Text_PsychicNormanSeen:
	.string "Déjame ver de qué son\n"
	.string "capaces tus POKéMON.$"

Route39_Text_PsychicNormanBeaten:
	.string "Ooh, tus POKéMON tienen\n"
	.string "potencial.$"

Route39_Text_PsychicNormanAfter:
	.string "Sabes que los POKéMON tienen\n"
	.string "¿habilidades diferentes?\p"
	.string "Las personas son así también.\n"
	.string "Todos tienen cosas\l"
	.string "potencial.$"

Route39_EventScript_Jamie::
	trainerbattle_single TRAINER_JAMIE_HNS, Route39_Text_PokefanFJaimeSeen, Route39_Text_PokefanFJaimeBeaten
	msgbox Route39_Text_PokefanFJaimeAfter, MSGBOX_AUTOCLOSE
	end

Route39_Text_PokefanFJaimeSeen:
	.string "Llegaste en el momento\n
justo.\p
¡A luchar!$"

Route39_Text_PokefanFJaimeBeaten:
	.string "Oh, how disappointing…$"

Route39_Text_PokefanFJaimeAfter:
	.string "Conocí a UMBREON de noche\n
aquí, en la RUTA 39.\p
No sé por qué, pero parece\n
que le gusta que entrene\l
aquí.\p
Parece volverse más amistoso\n
entrenando aquí que en\l
cualquier otro lugar.$"

Route39_EventScript_Sign1::
	lock
	msgbox Route39_Text_Sign, MSGBOX_SIGN
	closemessage
	release
	end

Route39_Text_Sign:
	.string "RUTA 39\p"
	.string "CIUDAD OLIVO - CIUDAD IRIS$"

Route39_EventScript_Sign2::
	lock
	msgbox Route39_Text_MoomooFarmSign, MSGBOX_SIGN
	closemessage
	release
	end

Route39_Text_MoomooFarmSign:
	.string "GRANJA MOOMOO\p
Disfruta nuestra leche fresca$"

Route39_EventScript_Sign3::
	lock
	msgbox Route39_Text_TrainerTips, MSGBOX_SIGN
	closemessage
	release
	end

Route39_Text_TrainerTips:
	.string "CONSEJOS DE ENTRENADOR\p"
	.string "Usa CABEZAZO en los árboles para\n"
	.string "sacar POKéMON.\p"
	.string "Aparecen distintos tipos de\n"
	.string "que caigan de los árboles.\p"
	.string "¡Usa CABEZAZO en cualquier árbol\n"
	.string "que veas!$"

Route39_Text_DerekRegister:
	.string "¡No voy a escuchar tus\n"
	.string "presunciones!\p"
	.string "¡Los POKé FANS no tenemos\n"
	.string "costumbre de oír presumidos!$"

Route39_Text_DerekHasItem:
	.string "¡Oye! Presumía de mi\n"
	.string "PIKACHU y encontré algo.\p"
	.string "¡Toma, puedes quedártelo!$"

Route39_Text_DerekGaveItem:
	.string "¡Es un PIKACHU!\n"
	.string "¿No estás de acuerdo?$"

Route39_Text_DerekNoRoom:
	.string "Hmm, tu MOCHILA está llena.\p"
	.string "Vuelve cuando tengas espacio.$"
