Route33_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route33_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route33_OnTransition: 
	callnative SetTimeBasedEncounters
	end

Route33_EventScript_HikerAnthony::
	trainerbattle_single TRAINER_ANTHONY_HNS, Route33_Text_HikerAnthony2Seen, Route33_Text_HikerAnthony2Beaten, Route33_EventScript_RegisterAnthony
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route33_EventScript_RematchAnthony
	msgbox Route33_Text_HikerAnthony2After, MSGBOX_AUTOCLOSE
	end

Route33_EventScript_RegisterAnthony::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route33_Text_AnthonyRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_ANTHONY_HNS
	release
	end

Route33_EventScript_RematchAnthony::
	trainerbattle_rematch TRAINER_ANTHONY_HNS, Route33_Text_AnthonyRematchIntro, Route33_Text_AnthonyRematchDefeat
	msgbox Route33_Text_AnthonyPostRematch, MSGBOX_AUTOCLOSE
	end

Route33_EventScript_Lass::
	lock
	faceplayer
	msgbox Route33_Text_Lass, MSGBOX_DEFAULT
	closemessage
	release
	end

Route33_Text_HikerAnthony2Seen:
	.string "Vine por el túnel,\n"
	.string "pero aún me queda mucha\l"
	.string "energía.$"

Route33_Text_HikerAnthony2Beaten:
	.string "¡Vaya! ¡Tienes más chispa\n"
	.string "que yo!$"

Route33_Text_HikerAnthony2After:
	.string "Los EXCURSIONISTAS damos\n"
	.string "lo mejor en las montañas.$"

Route33_Text_AnthonyRegister:
	.string "Los EXCURSIONISTAS damos\n"
	.string "lo mejor en las montañas.$"

Route33_Text_AnthonyRematchIntro:
	.string "Vine por el túnel,\n"
	.string "pero aún me queda mucha\l"
	.string "energía.$"

Route33_Text_AnthonyRematchDefeat:
	.string "¡Vaya! ¡Tienes más chispa\n"
	.string "que yo!$"

Route33_Text_AnthonyPostRematch:
	.string "Los EXCURSIONISTAS damos\n"
	.string "lo mejor en las montañas.$"

Route33_Text_HikerAnthonyDunsparce:
	.string "Oye, ¿conseguiste un DUNSPARCE?\p"
	.string "Yo también atrapé uno.\p"
	.string "Míralo bien con la luz.\n"
	.string "¡Tiene una cara muy graciosa!$"

Route33_Text_Lass:
	.string "Jadeo, jadeo…\p"
	.string "Esa cueva era más grande que\n"
	.string "Era lo que esperaba.\p"
	.string "Me cansé de explorar\n"
	.string "por MARILL, así que salí.$"
