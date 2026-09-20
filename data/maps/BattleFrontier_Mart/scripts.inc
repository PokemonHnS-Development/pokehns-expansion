BattleFrontier_Mart_MapScripts::
	.byte 0

BattleFrontier_Mart_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart BattleFrontier_Mart_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
BattleFrontier_Mart_Pokemart:
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_HYPER_POTION
	.2byte ITEM_MAX_POTION
	.2byte ITEM_FULL_RESTORE
	.2byte ITEM_FULL_HEAL
	.2byte ITEM_REVIVE
	.2byte ITEM_MAX_REPEL
	.2byte ITEM_PROTEIN
	.2byte ITEM_CALCIUM
	.2byte ITEM_IRON
	.2byte ITEM_ZINC
	.2byte ITEM_CARBOS
	.2byte ITEM_HP_UP
	pokemartlistend

BattleFrontier_Mart_EventScript_OldMan::
	msgbox BattleFrontier_Mart_Text_ChaperonGrandson, MSGBOX_NPC
	end

BattleFrontier_Mart_EventScript_OldWoman::
	lock
	applymovement LOCALID_FRONTIER_MART_OLD_WOMAN, Common_Movement_FaceDown
	waitmovement 0
	msgbox BattleFrontier_Mart_Text_ProteinMakeNiceGift, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Mart_EventScript_Boy::
	msgbox BattleFrontier_Mart_Text_FacilitiesDontAllowItems, MSGBOX_NPC
	end

BattleFrontier_Mart_Text_ChaperonGrandson:
	.string "Vinimos aquí para acompañar a nuestro\n"
	.string "nieto.\p"
	.string "Pero ya que estamos aquí, pensamos\n"
	.string "en comprar algunos recuerdos.$"

BattleFrontier_Mart_Text_ProteinMakeNiceGift:
	.string "Cariño, ¿qué te parece esto?\n"
	.string "¿No sería un regalo lindo?\p"
	.string "¿Es... PRO... TE... ÍNA?\n"
	.string "Suena delicioso, ¿verdad?$"

BattleFrontier_Mart_Text_FacilitiesDontAllowItems:
	.string "Muchas instalaciones de la\n"
	.string "BATTLE FRONTIER no permiten usar\l"
	.string "objetos durante las batallas.\p"
	.string "Esa regla hace que todo sea más\n"
	.string "¡Ya lo están!$"

