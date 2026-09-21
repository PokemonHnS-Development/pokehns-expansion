Route4_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route4_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route4_OnTransition: 
	callnative SetTimeBasedEncounters
	end

Route4_EventScript_HpUp::
	finditem ITEM_HP_UP
	end

Route4_EventScript_UltraBall::
	finditem ITEM_ULTRA_BALL
	end

Route4_EventScript_Hank::
	trainerbattle_single TRAINER_HANK_HNS, Route4_Text_BirdKeeperHank_Seen, Route4_Text_BirdKeeperHank_Beaten
	msgbox Route4_Text_BirdKeeperHank_AfterBattle, MSGBOX_AUTOCLOSE
	end

Route4_EventScript_Hope::
	trainerbattle_single TRAINER_HOPE_HNS, Route4_Text_PicnickerHope_Seen, Route4_Text_PicnickerHope_Beaten
	msgbox Route4_Text_PicnickerHope_AfterBattle, MSGBOX_AUTOCLOSE
	end

Route4_EventScript_Sharon::
	trainerbattle_single TRAINER_SHARON_HNS, Route4_Text_PicnickerSharon_Seen, Route4_Text_PicnickerSharon_Beaten
	msgbox Route4_Text_PicnickerSharon_AfterBattle, MSGBOX_AUTOCLOSE
	end

Route4_EventScript_Sign::
	msgbox Route4_Text_MtMoonSquareSign, MSGBOX_SIGN
	end

Route4_Text_BirdKeeperHank_Seen:
	.string "Entreno a mis POKéMON. ¿Batallamos?\n"
	.string "conmigo?$"

Route4_Text_BirdKeeperHank_Beaten:
	.string "Ack! I lost that one…$"

Route4_Text_BirdKeeperHank_AfterBattle:
	.string "Si tienes un POKéMON específico que\n"
	.string "quieras entrenar, sácalo primero y\l"
	.string "cámbialo enseguida.\p"
	.string "Así es como se hace.$"

Route4_Text_PicnickerHope_Seen:
	.string "Presiento que puedo ganar.\p¡Veamos si tengo razón!$"

Route4_Text_PicnickerHope_Beaten:
	.string "Ay, eres demasiado fuerte.$"

Route4_Text_PicnickerHope_AfterBattle:
	.string "Oí que CLEFAIRY sale en MT.MOON.\p"
	.string "Pero, ¿dónde podrían estar?$"

Route4_Text_PicnickerSharon_Seen:
	.string "Um…\n"
	.string "I…$"

Route4_Text_PicnickerSharon_Beaten:
	.string "…$"

Route4_Text_PicnickerSharon_AfterBattle:
	.string "……I'll go train some more…$"

Route4_Text_MtMoonSquareSign:
	.string "NUEVA ENTRADA MT.MOON\n"
	.string "DEBIDO A UN DERRUMBE\p"
	.string "TEN CUIDADO AL PASAR$"

