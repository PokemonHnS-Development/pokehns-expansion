Route3_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route3_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route3_OnTransition: 
	callnative SetTimeBasedEncounters
	end

Route3_EventScript_Otis::
	trainerbattle_single TRAINER_OTIS_HNS, Route3_Text_FirebreatherOtis_Seen, Route3_Text_FirebreatherOtis_Beaten
	msgbox Route3_Text_FirebreatherOtis_AfterBattle, MSGBOX_AUTOCLOSE
	end

Route3_EventScript_Warren::
	trainerbattle_single TRAINER_WARREN_HNS, Route3_Text_YoungsterWarren_Seen, Route3_Text_YoungsterWarren_Beaten
	msgbox Route3_Text_YoungsterWarren_AfterBattle, MSGBOX_AUTOCLOSE
	end

Route3_EventScript_Jimmy::
	trainerbattle_single TRAINER_JIMMY_HNS, Route3_Text_YoungsterJimmy_Seen, Route3_Text_YoungsterJimmy_Beaten
	msgbox Route3_Text_YoungsterJimmy_AfterBattle, MSGBOX_AUTOCLOSE
	end

Route3_EventScript_Burt::
	trainerbattle_single TRAINER_BURT_HNS, Route3_Text_FirebreatherBurt_Seen, Route3_Text_FirebreatherBurt_Beaten
	msgbox Route3_Text_FirebreatherBurt_AfterBattle, MSGBOX_AUTOCLOSE
	end

Route3_EventScript_Sign::
	msgbox Route3_Text_MtMoonSquareSign, MSGBOX_SIGN
	end

Route3_Text_FirebreatherOtis_Seen:
	.string "Ah! The weather's as fine as ever.$"

Route3_Text_FirebreatherOtis_Beaten:
	.string "It's sunny, but I'm all wet…$"

Route3_Text_FirebreatherOtis_AfterBattle:
	.string "Cuando llueve, es difícil lograr\n"
	.string "la ignición…$"

Route3_Text_YoungsterWarren_Seen:
	.string "Hmmm... No sé qué hacer...$"

Route3_Text_YoungsterWarren_Beaten:
	.string "I knew I'd lose…$"

Route3_Text_YoungsterWarren_AfterBattle:
	.string "Te veías fuerte.\p"
	.string "Me dio miedo enfrentarte…$"

Route3_Text_YoungsterJimmy_Seen:
	.string "¡Puedo correr como el viento!$"

Route3_Text_YoungsterJimmy_Beaten:
	.string "Blown away!$"

Route3_Text_YoungsterJimmy_AfterBattle:
	.string "Uso shorts todo el año.\p"
	.string "Esa es mi política de moda.$"

Route3_Text_FirebreatherBurt_Seen:
	.string "Step right up and take a look!$"

Route3_Text_FirebreatherBurt_Beaten:
	.string "Yow! That's hot!$"

Route3_Text_FirebreatherBurt_AfterBattle:
	.string "El mejor lanzallamas de KANTO,\n"
	.string "ese soy yo.\p"
	.string "Pero no el mejor entrenador…$"

Route3_Text_MtMoonSquareSign:
	.string "PLAZA DEL MT.MOON\p"
	.string "Solo sube las escaleras.$"

