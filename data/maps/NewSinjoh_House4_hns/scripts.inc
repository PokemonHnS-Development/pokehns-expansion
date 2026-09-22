NewSinjoh_House4_hns_MapScripts::
	.byte 0

NewSinjoh_Cafe_Script_Sister::
	lock
	faceplayer
	message NewSinjoh_Cafe_Text_ResturantGreeting
	waitmessage
	pokemart NewSinjoh_Cafe_Pokemart_Resturant
	msgbox NewSinjoh_Cafe_Text_ResturantEnd, MSGBOX_DEFAULT
	release
	end

	.align 2
NewSinjoh_Cafe_Pokemart_Resturant:
	.2byte ITEM_YACHE_BERRY
    .2byte ITEM_LANSAT_BERRY
    .2byte ITEM_ROWAP_BERRY
    .2byte ITEM_BERRY_JUICE
	.2byte ITEM_SODA_POP
	.2byte ITEM_LAVA_COOKIE
	.2byte ITEM_HEAL_POWDER
	.2byte ITEM_LEEK
	.2byte ITEM_BIG_ROOT
	.2byte ITEM_NONE
	release
	end

NewSinjoh_Cafe_Text_ResturantGreeting:
	.string "¡H-hola! ¡Bienvenidos al café!\n"
	.string "¿En qué puedo ayudarte hoy?$"

NewSinjoh_Cafe_Text_ResturantEnd:
	.string "¡Vuelve pronto!$"

NewSinjoh_Cafe_EventScript_BaldingMan::
	msgbox NewSinjoh_Cafe_Text_BaldingMan, MSGBOX_NPC
	end

NewSinjoh_Cafe_Text_BaldingMan:
	.string "Una familia local ha llevado este\n"
	.string "café desde hace muchísimo\l"
	.string "tiempo.\p"
	.string "Su hija menor, la de allá,\n"
	.string "no está acostumbrada a atender a\l"
	.string "tantos desconocidos.$"

NewSinjoh_Cafe_EventScript_ScientistF::
	msgbox NewSinjoh_Cafe_Text_ScientistF, MSGBOX_NPC
	end

NewSinjoh_Cafe_Text_ScientistF:
	.string "¡Esta bebida está tan bu-uena!\n"
	.string ".......\p"
	.string ".......\p"
	.string "Jajaja\p"
	.string ".......$"

NewSinjoh_Cafe_EventScript_ScientistM::
	lock
	faceplayer
	msgbox NewSinjoh_Cafe_Text_ScientistM, MSGBOX_DEFAULT
	closemessage
	release
	end

NewSinjoh_Cafe_Text_ScientistM:
	.string "Perdona a mi colega...\p"
	.string "Las bebidas aquí son más fuertes que\n"
	.string "las que usamos en HOENN.\p"
	.string "Traté de advertirle, pero dijo que\n"
	.string "necesitaba relajarse.\p"
	.string "Esta expedición de investigación\n"
	.string "ha sido dura para todos.$"

NewSinjoh_Cafe_EventScript_Gentleman::
	msgbox NewSinjoh_Cafe_Text_Gentleman, MSGBOX_NPC
	end

NewSinjoh_Cafe_Text_Gentleman:
	.string "¿Qué miras, niño?\p"
	.string "No hay nada de malo en que un hombre\n"
	.string "y su POKéMON coman en la misma mesa.$"

NewSinjoh_EventScript_Scyther::
	lock
	faceplayer
	playmoncry SPECIES_SCYTHER, 0
	msgbox NewSinjoh_Text_Scyther, MSGBOX_DEFAULT
	waitmoncry
    closemessage
	release
	end

NewSinjoh_Text_Scyther:
	.string "¡Scyyy!$"
