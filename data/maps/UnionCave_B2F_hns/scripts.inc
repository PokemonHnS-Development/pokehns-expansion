UnionCave_B2F_hns_MapScripts::
	.byte 0

UnionCave_B2F_EventScript_CooltrainerNick::
	trainerbattle_single TRAINER_NICK_HNS, UnionCave_B2F_Text_CooltrainermNickSeen, UnionCave_B2F_Text_CooltrainermNickBeaten
	msgbox UnionCave_B2F_Text_CooltrainermNickAfter, MSGBOX_AUTOCLOSE
	end

UnionCave_B2F_EventScript_CooltrainerfGwen::
	trainerbattle_single TRAINER_GWEN_HNS, UnionCave_B2F_Text_CooltrainerfGwenSeen, UnionCave_B2F_Text_CooltrainerfGwenBeaten
	msgbox UnionCave_B2F_Text_CooltrainerfGwenAfter, MSGBOX_AUTOCLOSE
	end

UnionCave_B2F_EventScript_CooltrainerfEmma::
	trainerbattle_single TRAINER_EMMA_HNS, UnionCave_B2F_Text_CooltrainerfEmmaSeen, UnionCave_B2F_Text_CooltrainerfEmmaBeaten
	msgbox UnionCave_B2F_Text_CooltrainerfEmmaAfter, MSGBOX_AUTOCLOSE
	end

UnionCave_B2F_EventScript_Lapras::
	lock
	faceplayer
	playmoncry SPECIES_LAPRAS, CRY_MODE_ENCOUNTER
	waitmoncry
	setwildbattle SPECIES_LAPRAS, 20
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, UnionCave_B2F_EventScript_LaprasRan
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_UNION_CAVE_LAPRAS
	setflag FLAG_HIDE_UNION_CAVE_LAPRAS
	fadescreenswapbuffers FADE_FROM_BLACK
	release
	end

UnionCave_B2F_EventScript_LaprasRan::
	release
	end


UnionCave_B2F_EventScript_Item_Ether::
	finditem ITEM_ETHER
	end

UnionCave_B2F_EventScript_Item_HyperPotion::
	finditem ITEM_HYPER_POTION
	end

UnionCave_B2F_EventScript_Item_MaxRevive::
	finditem ITEM_MAX_REVIVE
	end

UnionCave_B2F_Text_CooltrainermNickSeen:
	.string "Hay dos tipos de personas.\p"
	.string "Las que tienen estilo y las que\n"
	.string "no lo tienen.\p"
	.string "¿Qué tipo de persona eres tú?$"

UnionCave_B2F_Text_CooltrainermNickBeaten:
	.string "You've got dazzling style!$"

UnionCave_B2F_Text_CooltrainermNickAfter:
	.string "Tu estilo POKéMON es deslumbrante y\n"
	.string "colorido, lo admito.\p"
	.string "¡Seguirás mejorando cada vez más!$"

UnionCave_B2F_Text_CooltrainerfGwenSeen:
	.string "I'm in training. Care for a round?$"

UnionCave_B2F_Text_CooltrainerfGwenBeaten:
	.string "Aww, no! You're too good for me.$"

UnionCave_B2F_Text_CooltrainerfGwenAfter:
	.string "Entrenaré por mi cuenta hasta que\n"
	.string "me mejore.$"

UnionCave_B2F_Text_CooltrainerfEmmaSeen:
	.string "Si los POKéMON que me gustan\n"
	.string "estuvieran allí,\p"
	.string "Eso es lo que hace un entrenador.$"

UnionCave_B2F_Text_CooltrainerfEmmaBeaten:
	.string "I'd rather pet my babies than this!$"

UnionCave_B2F_Text_CooltrainerfEmmaAfter:
	.string "Una vez por semana, un POKéMON\n"
	.string "viene a la orilla del agua.\p"
	.string "Quería ver a ese POKéMON…$"
