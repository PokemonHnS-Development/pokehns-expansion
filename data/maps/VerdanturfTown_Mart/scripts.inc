VerdanturfTown_Mart_MapScripts::
	.byte 0

VerdanturfTown_Mart_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart VerdanturfTown_Mart_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
VerdanturfTown_Mart_Pokemart:
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_NEST_BALL
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_BURN_HEAL
	.2byte ITEM_ICE_HEAL
	.2byte ITEM_REPEL
	.2byte ITEM_X_SP_ATK
	.2byte ITEM_FLUFFY_TAIL
	pokemartlistend

VerdanturfTown_Mart_EventScript_Boy::
	msgbox VerdanturfTown_Mart_Text_XSpecialIsCrucial, MSGBOX_NPC
	end

VerdanturfTown_Mart_EventScript_ExpertF::
	msgbox VerdanturfTown_Mart_Text_NoStrategyGuidesForBattleTent, MSGBOX_NPC
	end

VerdanturfTown_Mart_EventScript_Lass::
	msgbox VerdanturfTown_Mart_Text_NestBallOnWeakenedPokemon, MSGBOX_NPC
	end

VerdanturfTown_Mart_Text_XSpecialIsCrucial:
	.string "Para cualquier combate POKéMON, X\n"
	.string "ESPECIAL es crucial.\p"
	.string "Sube el poder de algunos movimientos\n"
	.string "aunque sea solo por una batalla.$"

VerdanturfTown_Mart_Text_NoStrategyGuidesForBattleTent:
	.string "No parece que vendan guías de\n
estrategia para la CARPA DE COMBATE…\p
Parece que uno debe confiar en su\n
propio ingenio después de todo…$"

VerdanturfTown_Mart_Text_NestBallOnWeakenedPokemon:
	.string "La NEST BALL funciona mejor con\n"
	.string "POKéMON debilitados.\p"
	.string "VERDANTURF es el único lugar donde\n"
	.string "puedes comprarla.$"

