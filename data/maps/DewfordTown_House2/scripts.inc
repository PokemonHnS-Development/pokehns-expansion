DewfordTown_House2_MapScripts::
	.byte 0

DewfordTown_House2_EventScript_Man::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_SILK_SCARF, DewfordTown_House2_EventScript_ExplainSilkScarf
	msgbox DewfordTown_House2_Text_WantYouToHaveSilkScarf, MSGBOX_DEFAULT
	giveitem ITEM_SILK_SCARF
	goto_if_eq VAR_RESULT, FALSE, DewfordTown_House2_EventScript_NoRoomForScarf
	setflag FLAG_RECEIVED_SILK_SCARF
	release
	end

DewfordTown_House2_EventScript_NoRoomForScarf::
	msgbox DewfordTown_House2_Text_NoRoom, MSGBOX_DEFAULT
	release
	end

DewfordTown_House2_EventScript_ExplainSilkScarf::
	msgbox DewfordTown_House2_Text_ExplainSilkScarf, MSGBOX_DEFAULT
	release
	end

DewfordTown_House2_EventScript_Boy::
	msgbox DewfordTown_House2_Text_BrawlySoCool, MSGBOX_NPC
	end

DewfordTown_House2_Text_WantYouToHaveSilkScarf:
	.string "¡Mira esto con atención!\p"
	.string "Es un PAÑUELO SEDA. Está a la\n"
	.string "vanguardia de la moda, ¡sí!\p"
	.string "¡Veo que tus ojos brillan!\n"
	.string "¡Aprecias mi estilo deslumbrante!\p"
	.string "¡Ay, eres un encanto!\n"
	.string "Toma. ¡Quiero que te lo quedes!$"

DewfordTown_House2_Text_NoRoom:
	.string "¡Oh! ¿No tienes espacio?\p"
	.string "Escucha bien, ¡este PAÑUELO es im-\n"
	.string "prescindible! ¡Vendería todo lo\l"
	.string "que tengo por conseguirlo!$"

DewfordTown_House2_Text_ExplainSilkScarf:
	.string "El PAÑUELO SEDA sube el poder de\n"
	.string "Movimientos tipo NORMAL.\p"
	.string "¡Es una BUFANDA maravillosa que\n"
	.string "le queda a casi todo POKéMON!$"

DewfordTown_House2_Text_BrawlySoCool:
	.string "Vaya, ¿te molestaste en cruzar el\n"
	.string "mar para visitar ISLA ROCA?\p"
	.string "¿Tal vez viniste porque oíste\n"
	.string "hablar de BRAWLY?\p"
	.string "Es tan genial...\n"
	.string "Todos lo idolatran.$"

