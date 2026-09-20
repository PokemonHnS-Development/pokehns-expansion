FortreeCity_Mart_MapScripts::
	.byte 0

FortreeCity_Mart_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart FortreeCity_Mart_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
FortreeCity_Mart_Pokemart:
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_HYPER_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_REVIVE
	.2byte ITEM_SUPER_REPEL
	.2byte ITEM_WOOD_MAIL
	pokemartlistend

FortreeCity_Mart_EventScript_Woman::
	msgbox FortreeCity_Mart_Text_SuperRepelBetter, MSGBOX_NPC
	end

FortreeCity_Mart_EventScript_Girl::
	msgbox FortreeCity_Mart_Text_StockUpOnItems, MSGBOX_NPC
	end

FortreeCity_Mart_EventScript_Boy::
	msgbox FortreeCity_Mart_Text_RareCandyMakesMonGrow, MSGBOX_NPC
	end

FortreeCity_Mart_Text_SuperRepelBetter:
	.string "El SUPERREPEL dura mucho tiempo,\n"
	.string "y cumple muy bien su función.\p"
	.string "Es mucho mejor que un REPELENTE\n"
	.string "común.$"

FortreeCity_Mart_Text_StockUpOnItems:
	.string "Siempre llevo más objetos de los\n"
	.string "que creo que voy a necesitar.\p"
	.string "Nunca se sabe qué puede pasar.\n"
	.string "¡Más vale prevenir que lamentar!$"

FortreeCity_Mart_Text_RareCandyMakesMonGrow:
	.string "Un CARAMELO RARO hace que un\n"
	.string "POKéMON suba un nivel al instante.$"

