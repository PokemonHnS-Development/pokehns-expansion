FourIsland_Mart_Frlg_MapScripts::
	.byte 0

FourIsland_Mart_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart FourIsland_Mart_Items
	msgbox gText_PleaseComeAgain
	release
	end

	.align 2
FourIsland_Mart_Items::
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_FULL_RESTORE
	.2byte ITEM_MAX_POTION
	.2byte ITEM_REVIVE
	.2byte ITEM_ICE_HEAL
	.2byte ITEM_FULL_HEAL
	.2byte ITEM_ESCAPE_ROPE
	.2byte ITEM_MAX_REPEL
	.2byte ITEM_NONE
	release
	end

FourIsland_Mart_EventScript_Camper::
	msgbox FourIsland_Mart_Text_IcefallCaveIsFrigid, MSGBOX_NPC
	end

FourIsland_Mart_Text_LoreleiGrewUpOnThisIsland::
	.string "Hemos tenido un gran y poderoso\n"
	.string "ENTRENADOR creció en esta isla.\p"
	.string "Apuesto a que hasta tú la conoces.\n"
	.string "¡Es LORELEI del ALTO MANDO!\p"
	.string "Cuando LORELEI era pequeña,\n"
	.string "I taught her about POKéMON.$"

FourIsland_Mart_Text_IcefallCaveIsFrigid::
	.string "Las ISLAS SEVII tienen un clima\n"
	.string "region overall.\p"
	.string "Pero hay una excepción que\n"
	.string "debes conocer.\p"
	.string "La CUEVA DEL HIELO es helada\n"
	.string "of the POKéMON that live in it.$"

