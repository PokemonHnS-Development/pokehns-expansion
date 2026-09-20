Route29_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route29_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route29_OnTransition: 
	callnative SetTimeBasedEncounters
	end

Route29_Trigger_Monview::
	special SpawnCameraObject
	applymovement2 OBJ_EVENT_ID_CAMERA, Common_Movement_WalkUp1 
	waitmovement 0
	applymovement2 OBJ_EVENT_ID_CAMERA, Common_Movement_WalkUp1
	waitmovement 0
	applymovement2 OBJ_EVENT_ID_CAMERA, Common_Movement_WalkUp1
	waitmovement 0
	applymovement2 OBJ_EVENT_ID_CAMERA, Common_Movement_WalkUp1
	waitmovement 0
	message Route29_Text_PressAorB
	waitbuttonpress
	closemessage
	applymovement2 OBJ_EVENT_ID_CAMERA, Common_Movement_WalkDown1
	waitmovement 0
	applymovement2 OBJ_EVENT_ID_CAMERA, Common_Movement_WalkDown1
	waitmovement 0
	applymovement2 OBJ_EVENT_ID_CAMERA, Common_Movement_WalkDown1
	waitmovement 0
	applymovement2 OBJ_EVENT_ID_CAMERA, Common_Movement_WalkDown1
	waitmovement 0
	special RemoveCameraObject
	applymovement2 OBJ_EVENT_ID_PLAYER, Common_Movement_WalkDown1
	waitmovement 0
	end

Route29_Text_PressAorB:
	.string "Press A or B to stop viewing.$"

Route29_EventScript_OldMan::
	lock
	faceplayer
	goto_if_set FLAG_ADVENTURE_STARTED, Route29_EventScript_OldMan2
	msgbox Route29_Text_OldMan1, MSGBOX_DEFAULT
	closemessage
	release
	end

Route29_EventScript_OldMan2::
	msgbox Route29_Text_OldMan2, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route29_EventScript_OldMan_Tutorial
	waitmessage
	msgbox Route29_Text_OldManDeclined, MSGBOX_DEFAULT
	closemessage
	release
	end

Route29_EventScript_OldMan_Tutorial::
	msgbox Route29_Text_OldManExplanation, MSGBOX_DEFAULT
	closemessage
	release
	end

Route29_EventScript_Lass::
	lock
	faceplayer
	msgbox Route29_Text_Lass, MSGBOX_DEFAULT
	closemessage
	release
	end

Route29_EventScript_Youngster::
	lock
	faceplayer
	msgbox Route29_Text_Youngster, MSGBOX_DEFAULT
	closemessage
	release
	end


Route29_EventScript_Tuscany::
	lock
	faceplayer
	goto_if_set FLAG_GOT_SILK_SCARF, Route29_EventScript_TuscanyCompleted
	msgbox Route29_Text_MeetTuscany, MSGBOX_DEFAULT
	closemessage
	multichoice 20, 0, MULTI_DAYS_OF_WEEK, FALSE
	switch VAR_RESULT
	case 0, Route29_EventScript_TuscanyNope
	case 1, Route29_EventScript_TuscanyNope
	case 2, Route29_EventScript_TuscanyYes
	case 3, Route29_EventScript_TuscanyNope
	case 4, Route29_EventScript_TuscanyNope
	case 5, Route29_EventScript_TuscanyNope
	case 6, Route29_EventScript_TuscanyNope
	case 7 Route29_EventScript_TuscanyCancel
	case MULTI_B_PRESSED, Route29_EventScript_TuscanyCancel
	closemessage
	release
	end
Route29_EventScript_TuscanyYes::
	msgbox Route29_Text_TuscanyGivesGift, MSGBOX_DEFAULT
	giveitem ITEM_SILK_SCARF
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_GOT_SILK_SCARF
	msgbox Route29_Text_TuscanyGaveGift, MSGBOX_DEFAULT
	closemessage
	release
	end
Route29_EventScript_TuscanyNope::
	msgbox Route29_Text_TuscanyNope, MSGBOX_DEFAULT
	closemessage
	release
	end
Route29_EventScript_TuscanyCancel::
	closemessage
	release
	end
Route29_EventScript_TuscanyCompleted::
	msgbox Route29_Text_TuscanyTuesday, MSGBOX_DEFAULT
	closemessage
	release
	end



Route29_EventScript_Girl::
	lock
	faceplayer
	msgbox Route29_Text_Girl, MSGBOX_DEFAULT
	closemessage
	release
	end

Route29_EventScript_Boy::
	lock
	faceplayer
	goto_if_set FLAG_NIGHT_POKEMON, Route29_EventScript_Boy2
	msgbox Route29_Text_Boy_WaitingForDay, MSGBOX_DEFAULT
	closemessage
	release
	end

Route29_EventScript_Boy2::
	msgbox Route29_Text_Boy_WaitingForNight, MSGBOX_DEFAULT
	closemessage
	release
	end

Route29_EventScript_Sign::
	lock
	msgbox Route29_Text_Sign1, MSGBOX_SIGN
	closemessage
	release
	end

Route29_EventScript_ItemPotion::
	finditem ITEM_POTION
	end

Route29_Text_OldMan1:
	.string "Los POKéMON se ocultan en el pasto.\n"
	.string "Quién sabe cuándo saldrán...$"

Route29_Text_OldMan2:
	.string "Te he visto un par de veces.\n"
	.string "¿Cuántos POKéMON has atrapado?\p"
	.string "¿Quieres que te explique\n"
	.string "cómo atrapar POKéMON?$"

Route29_Text_OldManExplanation:
	.string "Si los debilitas primero,\n"
	.string "Es más fácil capturar POKéMON.\p"
	.string "¡Luego, lanza una BALL de tu\n"
	.string "mochila! Cualquier BALL sirve.\p"
	.string "Si quieres aprender más,\n"
	.string "go to the ACADEMY in VIOLET CITY!\p"
	.string "The students there know a lot\n"
	.string "about POKéMON.$"

Route29_Text_OldManDeclined:
	.string "Oh. Fine, then.\p"
	.string "Check every route to find\n"
	.string "different types of POKéMON.\p"
	.string "Your POKéDEX shows where you can\n"
	.string "find them too!\p"
	.string "Si quieres aprender más,\n"
	.string "go to the ACADEMY in VIOLET CITY!\p"
	.string "The students know a lot about\n"
	.string "POKéMON.$"

Route29_Text_Youngster:
	.string "Yo. How are your POKéMON?\p"
	.string "If they're weak and not ready\n"
	.string "for battle, keep out of the grass.$"

Route29_Text_Lass:
	.string "¿Ves esos salientes?\n"
	.string "Da miedo saltar desde ahí.\p"
	.string "Pero puedes ir a PUEBLO PRIMAVERA\n"
	.string "sin caminar por la hierba.$"

Route29_Text_Girl:
	.string "Quería tomarme un descanso,\n"
	.string "así que guardé mi progreso.$"

Route29_Text_Boy_WaitingForDay:
	.string "Espero a los POKéMON que\n"
	.string "aparecen más tarde en el día.$"

Route29_Text_Boy_WaitingForNight:
	.string "Espero a los POKéMON que\n"
	.string "aparecen solo por la noche.$"

Route29_Text_MeetTuscany:
	.string "TUSCANY: Creo que es la primera\n"
	.string "vez que nos conocemos, ¿no?\p"
	.string "Soy TUSCANY de la FAMILIA SEMANA.\p"
	.string "Si adivinas mi día favorito,\n"
	.string "te daré una recompensa.$"

Route29_Text_TuscanyNope:
	.string "Not quite!$"

Route29_Text_TuscanyGivesGift:
	.string "¡Sí! Para presentarnos,\n"
	.string "acepta este regalo, un PAÑUELO\l"
	.string "SEDA.$"

Route29_Text_TuscanyGaveGift:
	.string "TUSCANY: ¿No estás de acuerdo\n"
	.string "en que es muy adorable?\p"
	.string "Potencia los movimientos\n"
	.string "tipo NORMAl.\p"
	.string "Seguro que te será útil.$"

Route29_Text_TuscanyTuesday:
	.string "TUSCANY: ¿Conoces a MONICA?\n"
	.string "¿Mi hermana mayor?\p"
	.string "¿O mi hermano menor, WESLEY?\p"
	.string "Soy el tercero de siete\n"
	.string "hijos.$"

Route29_Text_Sign1:
	.string "RUTA 29\p"
	.string "CIUDAD CEREZO - PUEBLO PRIMAVERA$"

