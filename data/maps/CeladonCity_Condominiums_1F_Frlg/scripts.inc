CeladonCity_Condominiums_1F_Frlg_MapScripts::
	.byte 0

CeladonCity_Condominiums_1F_EventScript_TeaWoman::
	lock
	faceplayer
	goto_if_set FLAG_TALKED_TO_TEA_LADY_AFTER_HOF, CeladonCity_Condominiums_1F_EventScript_TeaWomanAfterTea
	goto_if_set FLAG_SYS_GAME_CLEAR, CeladonCity_Condominiums_1F_EventScript_TeaWomanMentionDaisy
	goto_if_set FLAG_GOT_TEA, CeladonCity_Condominiums_1F_EventScript_TeaWomanAfterTea
	msgbox CeladonCity_Condominiums_1F_Text_TryThisDrinkInstead
	setflag FLAG_GOT_TEA
	giveitem ITEM_TEA
	goto_if_eq VAR_RESULT, FALSE, EventScript_BagIsFull
	msgbox CeladonCity_Condominiums_1F_Text_NothingBeatsThirstLikeTea
	release
	end

CeladonCity_Condominiums_1F_EventScript_TeaWomanAfterTea::
	msgbox CeladonCity_Condominiums_1F_Text_MyDearMonsKeepMeCompany
	release
	end

CeladonCity_Condominiums_1F_EventScript_TeaWomanMentionDaisy::
	famechecker FAMECHECKER_DAISY, 4
	setflag FLAG_TALKED_TO_TEA_LADY_AFTER_HOF
	msgbox CeladonCity_Condominiums_1F_Text_DaisyComesToBuyTea
	release
	end

CeladonCity_Condominiums_1F_EventScript_Meowth::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_MEOWTH, CRY_MODE_NORMAL
	msgbox CeladonCity_Condominiums_1F_Text_Meowth
	waitmoncry
	release
	end

CeladonCity_Condominiums_1F_EventScript_Clefairy::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_CLEFAIRY, CRY_MODE_NORMAL
	msgbox CeladonCity_Condominiums_1F_Text_Clefairy
	waitmoncry
	release
	end

CeladonCity_Condominiums_1F_EventScript_Nidoran::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_NIDORAN_F, CRY_MODE_NORMAL
	msgbox CeladonCity_Condominiums_1F_Text_Nidoran
	waitmoncry
	release
	end

CeladonCity_Condominiums_1F_EventScript_SuiteSign::
	msgbox CeladonCity_Condominiums_1F_Text_ManagersSuite, MSGBOX_SIGN
	end

CeladonCity_Condominiums_1F_Text_Meowth::
	.string "MEOWTH: ¡Miau!$"

CeladonCity_Condominiums_1F_Text_TryThisDrinkInstead::
	.string "No deberías gastar todo tu dinero\n"
	.string "en bebidas.\p"
	.string "Prueba con esto.$"

CeladonCity_Condominiums_1F_Text_NothingBeatsThirstLikeTea::
	.string "Nada quita la sed como un buen TÉ\n"
	.string "caliente.\p"
	.string "Realmente es el mejor.$"

CeladonCity_Condominiums_1F_Text_MyDearMonsKeepMeCompany::
	.string "Mis queridos POKéMON me hacen compañía.\n"
	.string "¡MEOWTH incluso trae dinero a casa!$"

CeladonCity_Condominiums_1F_Text_DaisyComesToBuyTea::
	.string "Oh, hola, cariño.\n"
	.string "¿Disfrutaste mi TÉ?\p"
	.string "Por cierto, cariño. ¿Tú, por casualidad\n"
	.string "¿Chance, de PUEBLO PALETA?\p"
	.string "Una chica de PUEBLO PALETA, BLANCA,\n"
	.string "disfruta del TÉ cada día.\p"
	.string "Visita el CENTRO COMERCIAL CELADON\n"
	.string "para comprar TÉ.$"

CeladonCity_Condominiums_1F_Text_Clefairy::
	.string "CLEFAIRY: Pi pippippi!$"

CeladonCity_Condominiums_1F_Text_Nidoran::
	.string "NIDORAN♀: ¡Kya kyaoo!$"

CeladonCity_Condominiums_1F_Text_ManagersSuite::
	.string "MANSION CELADON\n"
	.string "Suite del Gerente$"

