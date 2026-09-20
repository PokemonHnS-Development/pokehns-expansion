MossdeepCity_Mart_MapScripts::
	.byte 0

MossdeepCity_Mart_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart MossdeepCity_Mart_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
MossdeepCity_Mart_Pokemart:
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_NET_BALL
	.2byte ITEM_DIVE_BALL
	.2byte ITEM_HYPER_POTION
	.2byte ITEM_FULL_HEAL
	.2byte ITEM_REVIVE
	.2byte ITEM_MAX_REPEL
	.2byte ITEM_X_ATTACK
	.2byte ITEM_X_DEFENSE
	pokemartlistend

MossdeepCity_Mart_EventScript_Woman::
	msgbox MossdeepCity_Mart_Text_ReviveIsFantastic, MSGBOX_NPC
	end

MossdeepCity_Mart_EventScript_Boy::
	msgbox MossdeepCity_Mart_Text_MaxRepelLastsLongest, MSGBOX_NPC
	end

MossdeepCity_Mart_EventScript_Sailor::
	msgbox MossdeepCity_Mart_Text_NetAndDiveBallsRare, MSGBOX_NPC
	end

MossdeepCity_Mart_Text_ReviveIsFantastic:
	.string "¡REVIVIR es fantástico!\p"
	.string "Dáselo a un POKéMON debilitado\n"
	.string "y el POKéMON se recuperará.\p"
	.string "Pero cuidado, REVIVIR no restaura\n"
	.string "los PP usados de los movimientos.$"

MossdeepCity_Mart_Text_MaxRepelLastsLongest:
	.string "MAX REPEL aleja a POKéMON débiles.\p"
	.string "De todos los REPELENTES, es el que\n"
	.string "más dura.$"

MossdeepCity_Mart_Text_NetAndDiveBallsRare:
	.string "NET BALL y DIVE BALL son POKé BALL\n"
	.string "raras que solo se hacen en FONDALMAR.\p"
	.string "La NET BALL es eficaz contra\n"
	.string "POKéMON tipo BICHOS y AGUA.\p"
	.string "La DIVE BALL es mejor para POKéMON\n"
	.string "en el fondo del mar.$"

