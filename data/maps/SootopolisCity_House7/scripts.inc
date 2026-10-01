SootopolisCity_House7_MapScripts::
	.byte 0

SootopolisCity_House7_EventScript_OldMan::
	msgbox SootopolisCity_House7_Text_CityFromEruptedVolcano, MSGBOX_NPC
	end

SootopolisCity_House7_EventScript_PokefanF::
	msgbox SootopolisCity_House7_Text_CaveMadeToKeepSomething, MSGBOX_NPC
	end

SootopolisCity_House7_Text_CityFromEruptedVolcano:
	.string "Un volcán submarino entró en erupción\n"
	.string "y surgió desde las profundidades.\p"
	.string "Su cráter emergió del mar y se\n"
	.string "llenó con el agua de lluvia.\p"
	.string "Así es como nació la CIUDAD\n"
	.string "FOCAL.$"

SootopolisCity_House7_Text_CaveMadeToKeepSomething:
	.string "La cueva que une CIUDAD FOCAL con\n"
	.string "el mundo exterior...\p"
	.string "Parece que la cueva fue hecha para\n"
	.string "evitar que algo saliera.\p"
	.string "¿O solo me lo estoy imaginando?$"

