Route1_Frlg_MapScripts::
	.byte 0

Route1_EventScript_MartClerk::
	lock
	faceplayer
	goto_if_set FLAG_GOT_POTION_ON_ROUTE_1, Route1_EventScript_AlreadyGotPotion
	msgbox Route1_Text_WorkAtPokeMartTakeSample
	textcolor NPC_TEXT_COLOR_NEUTRAL
	checkitemspace ITEM_POTION
	goto_if_eq VAR_RESULT, FALSE, EventScript_BagIsFull
	bufferitemname STR_VAR_2, ITEM_POTION
	playfanfare MUS_LEVEL_UP
	message gText_ObtainedTheItem
	waitmessage
	waitfanfare
	additem ITEM_POTION
	msgbox Route1_Text_PutPotionAway
	call EventScript_RestorePrevTextColor
	setflag FLAG_GOT_POTION_ON_ROUTE_1
	release
	end

Route1_EventScript_AlreadyGotPotion::
	msgbox Route1_Text_ComeSeeUsIfYouNeedPokeBalls
	release
	end

Route1_EventScript_Boy::
	msgbox Route1_Text_CanJumpFromLedges, MSGBOX_NPC
	end

Route1_EventScript_RouteSign::
	msgbox Route1_Text_RouteSign, MSGBOX_SIGN
	end

Route1_Text_WorkAtPokeMartTakeSample::
	.string "Hi!\n"
	.string "Trabajo en un POKéMON MART.\p"
	.string "Es parte de una cadena muy\n"
	.string "práctica que vende de todo.\p"
	.string "Visítanos en CIUDAD VERDE.\p"
	.string "¡Ya sé! Te daré una muestra.\n"
	.string "¡Toma esto!$"

Route1_Text_ComeSeeUsIfYouNeedPokeBalls::
	.string "Ven a vernos si lo necesitas.\n"
	.string "POKé BALLS para atrapar POKéMON.$"

Route1_Text_PutPotionAway::
	.string "{PLAYER} guardó la POCIÓN en\n"
	.string "el BOLSILLO de OBJETOS de la BOLSA.$"

Route1_Text_CanJumpFromLedges::
	.string "¿Ves esos riscos en el camino?\p"
	.string "Da un poco de miedo, pero puedes\n"
	.string "saltar desde ellas.\p"
	.string "Así puedes volver a PUEBLO PALETA\n"
	.string "más rápido.$"

Route1_Text_RouteSign::
	.string "RUTA 1\n"
	.string "PUEBLO PALETA - CIUDAD VERIDIAN$"

