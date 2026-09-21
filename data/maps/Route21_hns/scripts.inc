Route21_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route21_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route21_OnTransition:
	callnative SetTimeBasedEncounters
	end

Route21_EventScript_Seth::
	trainerbattle_single TRAINER_SETH_HNS, Route21_Text_SwimmermSethSeen, Route21_Text_SwimmermSethBeaten
	msgbox Route21_Text_SwimmermSethAfterBattle, MSGBOX_AUTOCLOSE
	end

Route21_EventScript_Nikki::
	trainerbattle_single TRAINER_NIKKI_HNS, Route21_Text_SwimmerfNikkiSeen, Route21_Text_SwimmerfNikkiBeaten
	msgbox Route21_Text_SwimmerfNikkiAfterBattle, MSGBOX_AUTOCLOSE
	end

Route21_EventScript_Arnold::
	trainerbattle_single TRAINER_ARNOLD_HNS, Route21_Text_FisherArnoldSeen, Route21_Text_FisherArnoldBeaten
	msgbox Route21_Text_FisherArnoldAfterBattle, MSGBOX_AUTOCLOSE
	end

Route21_Text_SwimmermSethSeen:
	.string "Land ho! Gotta keep going!$"

Route21_Text_SwimmermSethBeaten:
	.string "Glug…$"

Route21_Text_SwimmermSethAfterBattle:
	.string "Ese arrogante estaba en el\n
volcán de ISLA CANELA.$"

Route21_Text_SwimmerfNikkiSeen:
	.string "¡Si gano, me tienes que ayudar con\n
mi crema bronceadora!$"

Route21_Text_SwimmerfNikkiBeaten:
	.string "I'm worried about sunburn…$"

Route21_Text_SwimmerfNikkiAfterBattle:
	.string "Tengo que cuidarme de las manchas\n
que causa el sol.$"

Route21_Text_FisherArnoldSeen:
	.string "I'm bored by fishing. Let's battle!$"

Route21_Text_FisherArnoldBeaten:
	.string "Utter failure…$"

Route21_Text_FisherArnoldAfterBattle:
	.string "I'll just go back to fishing…$"

