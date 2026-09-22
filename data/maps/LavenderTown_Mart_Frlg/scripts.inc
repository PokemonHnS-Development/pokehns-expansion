LavenderTown_Mart_Frlg_MapScripts::
	.byte 0

LavenderTown_Mart_EventScript_BaldingMan::
	msgbox LavenderTown_Mart_Text_SearchingForStatRaiseItems, MSGBOX_NPC
	end

LavenderTown_Mart_EventScript_Rocker::
	msgbox LavenderTown_Mart_Text_DidYouBuyRevives, MSGBOX_NPC
	end

LavenderTown_Mart_EventScript_Youngster::
	msgbox LavenderTown_Mart_Text_TrainerDuosCanChallengeYou, MSGBOX_NPC
	end

LavenderTown_Mart_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart LavenderTown_Mart_Items
	msgbox gText_PleaseComeAgain
	release
	end

	.align 2
LavenderTown_Mart_Items::
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_REVIVE
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_BURN_HEAL
	.2byte ITEM_ICE_HEAL
	.2byte ITEM_ESCAPE_ROPE
	.2byte ITEM_SUPER_REPEL
	.2byte ITEM_NONE
	release
	end

LavenderTown_Mart_Text_SearchingForStatRaiseItems::
	.string "Busco objetos que aumenten\n"
	.string "the stats of POKéMON.\p"
	.string "They're effective over the course\n"
	.string "de una sola batalla.\p"
	.string "X ATTACK, X DEFEND, X SPEED, \n"
	.string "y la X ESPECIAL es lo que busco.\p"
	.string "¿Sabes dónde puedo conseguirlas?$"

LavenderTown_Mart_Text_DidYouBuyRevives::
	.string "¿Compraste algunos REVIVIR?\n"
	.string "They revive any fainted POKéMON!$"

LavenderTown_Mart_Text_TrainerDuosCanChallengeYou::
	.string "A veces, un dúo de ENTRENADORES\n"
	.string "challenge you with two POKéMON\l"
	.string "al mismo tiempo.\p"
	.string "Si eso pasa, tienes que enviar\n"
	.string "out two POKéMON to battle, too.$"

LavenderTown_Mart_Text_SoldNuggetFromMountainsFor5000::
	.string "この　あいだ　やまおくで\n"
	.string "きんのたまを　ひろい　ましてね！\p"
	.string "つかえない　しなもの　ですが\n"
	.string "うったら　なんと　5000¥でした$"
