ThreeIsland_Mart_Frlg_MapScripts::
	.byte 0

ThreeIsland_Mart_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart ThreeIsland_Mart_Items
	msgbox gText_PleaseComeAgain
	release
	end

	.align 2
ThreeIsland_Mart_Items::
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_HYPER_POTION
	.2byte ITEM_REVIVE
	.2byte ITEM_FULL_HEAL
	.2byte ITEM_ESCAPE_ROPE
	.2byte ITEM_MAX_REPEL
	.2byte ITEM_NONE
	release
	end

ThreeIsland_Mart_EventScript_Picnicker::
	msgbox ThreeIsland_Mart_Text_TrueThatCeldadonDeptStoreBigger, MSGBOX_NPC
	end

ThreeIsland_Mart_EventScript_BugCatcher::
	msgbox ThreeIsland_Mart_Text_PeopleHealWithBerriesFromForest, MSGBOX_NPC
	end

ThreeIsland_Mart_EventScript_Youngster::
	msgbox ThreeIsland_Mart_Text_BikersWereAboutToTrashMart, MSGBOX_NPC
	end

ThreeIsland_Mart_Text_TrueThatCeldadonDeptStoreBigger::
	.string "¿Es verdad?\p"
	.string "La TIENDA DE CELADON es varios\n"
	.string "veces más grande que esta tienda?$"

ThreeIsland_Mart_Text_PeopleHealWithBerriesFromForest::
	.string "A veces compro medicina aquí.\p"
	.string "Pero mucha gente cura a sus POKéMON\n"
	.string "con BAYAS del BOSQUE BAYA.\p"
	.string "Después de todo, las BAYAS son gratis\n"
	.string "nunca se acaban.$"

ThreeIsland_Mart_Text_BikersWereAboutToTrashMart::
	.string "Esos MOTOCICLISTAS iban a destrozar\n"
	.string "esta TIENDA POKéMON.\p"
	.string "¡Qué bueno que decidieron irse!$"

