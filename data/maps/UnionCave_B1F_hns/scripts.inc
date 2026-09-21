UnionCave_B1F_hns_MapScripts::
	.byte 0

UnionCave_B1F_EventScript_HikerPhillip::
	trainerbattle_single TRAINER_PHILLIP_HNS, UnionCave_B1F_Text_HikerPhillipSeen, UnionCave_B1F_Text_HikerPhillipBeaten
	msgbox UnionCave_B1F_Text_HikerPhillipAfter, MSGBOX_AUTOCLOSE
	end

UnionCave_B1F_EventScript_HikerLeonard::
	trainerbattle_single TRAINER_LEONARD_HNS, UnionCave_B1F_Text_HikerLeonardSeen, UnionCave_B1F_Text_HikerLeonardBeaten
	msgbox UnionCave_B1F_Text_HikerLeonardAfter, MSGBOX_AUTOCLOSE
	end

UnionCave_B1F_EventScript_PokemaniacAndrew::
	trainerbattle_single TRAINER_ANDREW_HNS, UnionCave_B1F_Text_PokemaniacAndrewSeen, UnionCave_B1F_Text_PokemaniacAndrewBeaten
	msgbox UnionCave_B1F_Text_PokemaniacAndrewAfter, MSGBOX_AUTOCLOSE
	end

UnionCave_B1F_EventScript_PokemaniacCalvin::
	trainerbattle_single TRAINER_CALVIN_HNS, UnionCave_B1F_Text_PokemaniacCalvinSeen, UnionCave_B1F_Text_PokemaniacCalvinBeaten
	msgbox UnionCave_B1F_Text_PokemaniacCalvinAfter, MSGBOX_AUTOCLOSE
	end

UnionCave_B1F_EventScript_Item_RockTomb::
	finditem ITEM_TM_ROCK_TOMB
	end

UnionCave_B1F_EventScript_Item_Xdefend::
	finditem ITEM_X_DEFEND
	end

UnionCave_B1F_Text_HikerPhillipSeen:
	.string "Ha pasado tiempo desde que vi a\n"
	.string "otra persona.\p"
	.string "No seas tímido. ¡Luchemos!$"

UnionCave_B1F_Text_HikerPhillipBeaten:
	.string "Uurggh…$"

UnionCave_B1F_Text_HikerPhillipAfter:
	.string "Llevo mucho tiempo perdido...\p"
	.string "No me molesta estar aquí, ¡pero\n"
	.string "tengo muchísima hambre!$"

UnionCave_B1F_Text_HikerLeonardSeen:
	.string "¡No me digas! ¡Una visita!$"

UnionCave_B1F_Text_HikerLeonardBeaten:
	.string "Wahahah! You're a feisty one!$"

UnionCave_B1F_Text_HikerLeonardAfter:
	.string "Vivo aquí abajo.\p"
	.string "Tú también puedes, si quieres.\p"
	.string "Hay espacio de sobra, ¿ves?$"

UnionCave_B1F_Text_PokemaniacAndrewSeen:
	.string "¿Quién está ahí?\p"
	.string "¡Déjame en paz a mí y a mi POKéMON!$"

UnionCave_B1F_Text_PokemaniacAndrewBeaten:
	.string "Go… Go away!$"

UnionCave_B1F_Text_PokemaniacAndrewAfter:
	.string "Solo mi POKéMON y yo. Estoy de-\n"
	.string "lirante de alegría.$"

UnionCave_B1F_Text_PokemaniacCalvinSeen:
	.string "Vine hasta aquí para realizar mi\n"
	.string "investigación POKéMON.\p"
	.string "¡Déjame demostrar mis hallazgos en\n"
	.string "una batalla real!$"

UnionCave_B1F_Text_PokemaniacCalvinBeaten:
	.string "You demonstrated on me!$"

UnionCave_B1F_Text_PokemaniacCalvinAfter:
	.string "Debo compilar y anunciar los\n"
	.string "resultados de mi estudio.\p"
	.string "¡Incluso podría ser famoso como\n"
	.string "PROF.ELM.$"
