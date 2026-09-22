Route11_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route11_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route11_OnTransition:
	callnative SetTimeBasedEncounters
	end

Route11_EventScript_Owen::
	trainerbattle_single TRAINER_OWEN_HNS, Route11_Text_YoungsterOwenSeen, Route11_Text_YoungsterOwenBeaten
	msgbox Route11_Text_YoungsterOwenAfterBattle, MSGBOX_AUTOCLOSE
	end

Route11_EventScript_Jason::
	trainerbattle_single TRAINER_JASON_HNS, Route11_Text_YoungsterJasonSeen, Route11_Text_YoungsterJasonBeaten
	msgbox Route11_Text_YoungsterJasonAfterBattle, MSGBOX_AUTOCLOSE
	end

Route11_EventScript_Herman::
	trainerbattle_single TRAINER_HERMAN_HNS, Route11_Text_PsychicHermanSeen, Route11_Text_PsychicHermanBeaten
	msgbox Route11_Text_PsychicHermanAfterBattle, MSGBOX_AUTOCLOSE
	end

Route11_EventScript_Fidel::
	trainerbattle_single TRAINER_FIDEL_HNS, Route11_Text_PsychicFidelSeen, Route11_Text_PsychicFidelBeaten
	msgbox Route11_Text_PsychicFidelAfterBattle, MSGBOX_AUTOCLOSE
	end

Route11_EventScript_Engineer::
	msgbox Route11_Text_Engineer, MSGBOX_NPC
	end

Route11_EventScript_Item_Grass_Knot::
    finditem ITEM_TM_GRASS_KNOT
    end

Route11_Text_Engineer:
	.string "Vi un POKéMON extraño trepando\n"
	.string "por los árboles, pero no\l"
	.string "parecía un MANKEY...$"

Route11_Text_YoungsterOwenSeen:
	.string "No se hace trampa en POKéMON.\p"
	.string "¡Mantengamos el juego limpio!$"

Route11_Text_YoungsterOwenBeaten:
	.string "¿Eh? ¿Cómo pasó esto?$"

Route11_Text_YoungsterOwenAfterBattle:
	.string "Luché limpio y con\nhonor.\pNo me arrepiento en absoluto.$"

Route11_Text_YoungsterJasonSeen:
	.string "Pica y da cosquillas cuando\nllevo shorts en el pasto.$"

Route11_Text_YoungsterJasonBeaten:
	.string "¡Aaaah! ¡Me aplastaste!$"

Route11_Text_YoungsterJasonAfterBattle:
	.string "Atraparé más POKéMON en\n"
	.string "caminar por la hierba.$"

Route11_Text_PsychicHermanSeen:
	.string "...$"

Route11_Text_PsychicHermanBeaten:
	.string "...$"

Route11_Text_PsychicHermanAfterBattle:
	.string "...\p"
	.string "Perdí mientras cerraba los ojos...$"

Route11_Text_PsychicFidelSeen:
	.string "Puedo verlo...\pTodo lo que hay que ver de ti...$"

Route11_Text_PsychicFidelBeaten:
	.string "No pude prever tu poder...$"

Route11_Text_PsychicFidelAfterBattle:
	.string "Fuerza en la convicción...\p"
	.string "Eres fuerte porque crees\n"
	.string "en tus POKéMON.$"

Route11_Text_Sign:
	.string "ROUTE 11$"

