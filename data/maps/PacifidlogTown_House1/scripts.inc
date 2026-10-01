PacifidlogTown_House1_MapScripts::
	.byte 0

PacifidlogTown_House1_EventScript_Man::
	msgbox PacifidlogTown_House1_Text_RegiStory, MSGBOX_NPC
	end

PacifidlogTown_House1_EventScript_Woman::
	msgbox PacifidlogTown_House1_Text_SixDotsOpenThreeDoors, MSGBOX_NPC
	end

PacifidlogTown_House1_Text_RegiStory:
	.string "En la región de HOENN, hay tres\n"
	.string "POKéMON que representan el poder de\l"
	.string "la roca, el hielo y el acero.\p"
	.string "Se dice que cada uno se oculta en\n"
	.string "lo profundo de las cuevas.\p"
	.string "Esa es la historia que escuché cuando\n"
	.string "era solo un niño.$"

PacifidlogTown_House1_Text_SixDotsOpenThreeDoors:
	.string "“Seis puntos abren tres puertas.”\p"
	.string "Mi abuelo decía eso, pero no sé\n"
	.string "qué quería decir.$"

