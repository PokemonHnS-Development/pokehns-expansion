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
	.string "las estadísticas de POKéMON.\p"
	.string "Son efectivas durante el curso\n"
	.string "de una sola batalla.\p"
	.string "ATAQUE X, DEFENSA X, VEL. X, \n"
	.string "y la X ESPECIAL es lo que busco.\p"
	.string "¿Sabes dónde puedo conseguirlas?$"

LavenderTown_Mart_Text_DidYouBuyRevives::
	.string "¿Compraste algunos REVIVIR?\n"
	.string "¡Reviven a todo POKéMON debilitado!$"

LavenderTown_Mart_Text_TrainerDuosCanChallengeYou::
	.string "A veces, un dúo de ENTRENADORES\n"
	.string "te retan con dos POKéMON\l"
	.string "al mismo tiempo.\p"
	.string "Si eso pasa, tienes que enviar\n"
	.string "a dos POKéMON a la batalla, también.$"

LavenderTown_Mart_Text_SoldNuggetFromMountainsFor5000::
	.string "この　あいだ　やまおくで\n"
	.string "きんのたまを　ひろい　ましてね！\p"
	.string "つかえない　しなもの　ですが\n"
	.string "うったら　なんと　5000¥でした$"
