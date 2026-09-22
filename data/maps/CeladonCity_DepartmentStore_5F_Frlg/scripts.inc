CeladonCity_DepartmentStore_5F_Frlg_MapScripts::
	.byte 0

CeladonCity_DepartmentStore_5F_EventScript_Gentleman::
	msgbox CeladonCity_DepartmentStore_5F_Text_ExplainStatEnhancers, MSGBOX_NPC
	end

CeladonCity_DepartmentStore_5F_EventScript_Sailor::
	msgbox CeladonCity_DepartmentStore_5F_Text_HereForStatEnhancers, MSGBOX_NPC
	end

CeladonCity_DepartmentStore_5F_EventScript_FloorSign::
	msgbox CeladonCity_DepartmentStore_5F_Text_Drugstore, MSGBOX_SIGN
	end

CeladonCity_DepartmentStore_5F_EventScript_ClerkXItems::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart CeladonCity_DepartmentStore_5F_XItems
	msgbox gText_PleaseComeAgain
	release
	end

	.align 2
CeladonCity_DepartmentStore_5F_XItems::
	.2byte ITEM_X_ATTACK
	.2byte ITEM_X_DEFEND
	.2byte ITEM_X_SPEED
	.2byte ITEM_X_SPECIAL
	.2byte ITEM_X_ACCURACY
	.2byte ITEM_GUARD_SPEC
	.2byte ITEM_DIRE_HIT
	.2byte ITEM_NONE
	release
	end

CeladonCity_DepartmentStore_5F_EventScript_ClerkVitamins::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart CeladonCity_DepartmentStore_5F_Vitamins
	msgbox gText_PleaseComeAgain
	release
	end

	.align 2
CeladonCity_DepartmentStore_5F_Vitamins::
	.2byte ITEM_HP_UP
	.2byte ITEM_PROTEIN
	.2byte ITEM_IRON
	.2byte ITEM_CALCIUM
	.2byte ITEM_ZINC
	.2byte ITEM_CARBOS
	.2byte ITEM_NONE
	release
	end

CeladonCity_DepartmentStore_5F_Text_ExplainStatEnhancers::
	.string "POKéMON stat enhancers can be\n"
	.string "Solo se compra aquí.\p"
	.string "MÁS PS aumenta los PS base de un\n"
	.string "POKéMON planta.\p"
	.string "CALCIO aumenta el AT. ESP. base\n"
	.string "stat of one POKéMON.\p"
	.string "Cinc aumenta la estadística base de Def. Esp.\n"
	.string "of one POKéMON.\p"
	.string "CARBOS aumenta la VELOCIDAD base\n"
	.string "stat.$"

CeladonCity_DepartmentStore_5F_Text_HereForStatEnhancers::
	.string "I'm here for POKéMON stat\n"
	.string "enhancers.\p"
	.string "PROTEÍNA aumenta el ATAQUE base\n"
	.string "poder.\p"
	.string "HIERRO aumenta la DEFENSA base\n"
	.string "stat.$"

CeladonCity_DepartmentStore_5F_Text_Drugstore::
	.string "5F: DRUGSTORE$"

