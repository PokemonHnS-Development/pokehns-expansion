Gate_GoldenrodCity_Route35_hns_MapScripts::
	.byte 0

Gate_GoldenrodCity_Route35_EventScript_Randy::
	lock
	faceplayer
	goto_if_eq VAR_KENYA, 3, Gate_GoldenrodCity_Route35_EventScript_RandyPostKenya
	goto_if_eq VAR_KENYA, 2, Gate_GoldenrodCity_Route35_EventScript_RandyDeliveredKenya
	goto_if_eq VAR_KENYA, 1, Gate_GoldenrodCity_Route35_EventScript_RandyHaveKenya
	msgbox Route35GoldenrodGate_Text_RandyAskFavor, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, Gate_GoldenrodCity_Route35_EventScript_RandyCancel
	closemessage

	msgbox Route35GoldenrodGate_Text_RandyThanks, MSGBOX_DEFAULT

	@HnS named gift pokemon setup
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_SPEAROW
	bufferspeciesname STR_VAR_1, SPECIES_SPEAROW
	givenamedmon 1
	call Common_EventScript_GiftMonNamed

	setvar VAR_KENYA, 1
	release
	end

Gate_GoldenrodCity_Route35_EventScript_RandyCancel::
	msgbox Route35GoldenrodGate_Text_RandyNeverMind, MSGBOX_DEFAULT
	closemessage
	release
	end

Gate_GoldenrodCity_Route35_EventScript_RandyHaveKenya::
	msgbox Route35GoldenrodGate_Text_RandyWeirdTree, MSGBOX_DEFAULT
	closemessage
	release
	end

Gate_GoldenrodCity_Route35_EventScript_RandyDeliveredKenya::
	msgbox Route35GoldenrodGate_Text_ThanksForDelivery, MSGBOX_DEFAULT
	closemessage
	giveitem ITEM_HP_UP
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_BagIsFull
	msgbox Route35GoldenrodGate_Text_RandyMyPalSnoozing, MSGBOX_DEFAULT
	closemessage
	setvar VAR_KENYA, 3
	release
	end

Gate_GoldenrodCity_Route35_EventScript_RandyPostKenya::
	msgbox Route35GoldenrodGate_Text_RandyMyPalSnoozing, MSGBOX_DEFAULT
	closemessage
	release
	end

Gate_GoldenrodCity_Route35_EventScript_Lady::
	lock
	faceplayer
	goto_if_set FLAG_HIDE_SUDOWOODO, Gate_GoldenrodCity_Route35_EventScript_Lady2
	msgbox Route35GoldenrodGate_Text_PokefanF_TreeBlocking, MSGBOX_DEFAULT
	closemessage
	release
	end

Gate_GoldenrodCity_Route35_EventScript_Lady2::
	msgbox Route35GoldenrodGate_Text_PokefanF_Lullaby, MSGBOX_DEFAULT
	closemessage
	release
	end

Gate_GoldenrodCity_Route35_EventScript_Fisher::
	lock
	faceplayer
	msgbox Route35GoldenrodGate_Text_Fisher, MSGBOX_DEFAULT
	closemessage
	release
	end

Route35GoldenrodGate_Text_RandyAskFavor:
	.string "¡Oye, chico! ¿Puedes hacerme\n"
	.string "un favor?\p"
	.string "¿Llevarías este POKéMON con MAIL\n"
	.string "a mi amigo?\p"
	.string "Está en la RUTA 31.$"

Route35GoldenrodGate_Text_RandyThanks:
	.string "¿Lo harás? ¡Genial! ¡Gracias!\p"
	.string "Mi amigo es un tipo gordito que\n"
	.string "siempre está durmiendo.\p"
	.string "¡Lo reconocerás enseguida!$"

Route35GoldenrodGate_Text_ReceivedMonWithMail:
	.string "{PLAYER} received a POKéMON with MAIL.$"

Route35GoldenrodGate_Text_RandyWeirdTree:
	.string "¡Ponlo al frente de tu equipo\n"
	.string "cuando encuentres a mi amigo!\p"
	.string "¡RUTA 31!\p"
	.string "Ah, sí. Había un árbol raro\n"
	.string "bloqueando el camino.\p"
	.string "¿Me pregunto si ya lo quitaron?$"

Route35GoldenrodGate_Text_CantCarryMoreMon:
	.string "You can't carry another POKéMON…$"

Route35GoldenrodGate_Text_RandyNeverMind:
	.string "Oh… Never mind, then…$"

Route35GoldenrodGate_Text_ThanksForDelivery:
	.string "¡Gracias, chico! Hiciste la entrega\n"
	.string "por mí!\p"
	.string "¡Toma esto por las molestias!$"

Route35GoldenrodGate_Text_RandyMyPalSnoozing:
	.string "Mi amigo dormía, ¿verdad? Je,\n"
	.string "¿qué dije?$"

Route35GoldenrodGate_Text_PokefanF_TreeBlocking:
	.string "Un árbol raro bloquea el camino.\p"
	.string "Se mueve si le hablas.\p"
	.string "Oí que se volvió salvaje cuando\n"
	.string "lo regaron con un ROCIADOR.$"

Route35GoldenrodGate_Text_PokefanF_Lullaby:
	.string "Me gusta la canción de cuna POKéMON\n"
	.string "que ponen en la radio.$"

Route35GoldenrodGate_Text_Fisher:
	.string "Me pregunto cuántas especies de\n"
	.string "POKéMON hay en el mundo.\p"
	.string "Hace tres años, el PROF.OAK dijo\n"
	.string "que había 150 especies distintas.\p"
	.string "¡Pero hace poco oí que hay\n"
	.string "más de 400!$"
