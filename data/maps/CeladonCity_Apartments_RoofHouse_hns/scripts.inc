CeladonCity_Apartments_RoofHouse_hns_MapScripts::
	.byte 0

CeladonCity_Apartments_RoofHouse_EventScript_BlackBelt::
	lock 
	faceplayer
	goto_if_set FLAG_GOT_TM_SLEEP_TALK, CeladonCity_Apartments_RoofHouse_EventScript_BlackBeltAfter
	msgbox CeladonMansionRoofHouse_Text_PharmacistIntro, MSGBOX_DEFAULT	
	goto_if_set FLAG_NIGHT_POKEMON, CeladonCity_Apartments_RoofHouse_EventScript_BlackBeltRefused
	msgbox CeladonMansionRoofHouse_Text_PharmacistStory, MSGBOX_NPC
	giveitem ITEM_TM_SLEEP_TALK
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_GOT_TM_SLEEP_TALK
	msgbox CeladonMansionRoofHouse_Text_PharmacistCurse, MSGBOX_NPC
	closemessage
	release
	end

CeladonCity_Apartments_RoofHouse_EventScript_BlackBeltRefused::
	msgbox CeladonMansionRoofHouse_Text_PharmacistNotNight, MSGBOX_NPC
	closemessage
	release
	end

CeladonCity_Apartments_RoofHouse_EventScript_BlackBeltAfter::
	msgbox CeladonMansionRoofHouse_Text_PharmacistCurse, MSGBOX_NPC
	release
	end

CeladonMansionRoofHouse_Text_PharmacistIntro:
	.string "Let me recount a terrifying tale…$"

CeladonMansionRoofHouse_Text_PharmacistNotNight:
	.string "Aunque no da tanto miedo\n"
	.string "mientras haya luz afuera.\p"
	.string "Vuelve después del ocaso, ¿sí?$"

CeladonMansionRoofHouse_Text_PharmacistStory:
	.string "Había una vez un\n"
	.string "niño pequeño que recibió una\l"
	.string "BICICLETA nueva…\p"
	.string "Quiso probarla enseguida…\p"
	.string "Se divertía tanto que\n"
	.string "no notó que el sol se ocultó…\p"
	.string "Mientras volvía a casa en la\n"
	.string "oscuridad, la bici de repente\l"
	.string "¡se frenó!\p"
	.string "¡Los pedales pesaban mucho!\p"
	.string "Al dejar de pedalear, la\n"
	.string "¡bici empezó a retroceder!\p"
	.string "Era como si la bici estuviera\n"
	.string "maldita y quisiera arrastrarlo\l"
	.string "al olvido!\p"
	.string "…\p"
	.string "…\p"
	.string "¡¡¡GRIIIIIIIIII!!!\p"
	.string "El chico subía la colina en la\n"
	.string "¡CICLOVÍA!\p"
	.string "…\n"
	.string "¡Tucún tucún!\p"
	.string "Por escuchar tan pacientemente,\n"
	.string "¡Toma esto, la MT82!$"

CeladonMansionRoofHouse_Text_PharmacistCurse:
	.string "La MT82 es SONÁMBULO.\p"
	.string "Permite que tu POKéMON use\n"
	.string "un movimiento al azar dormido.\p"
	.string "¡Pero buena suerte durmiendo tras\n"
	.string "ese cuento tan aterrador!$"

