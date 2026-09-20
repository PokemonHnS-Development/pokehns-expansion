SeafloorCavern_Room3_MapScripts::
	.byte 0

SeafloorCavern_Room3_EventScript_Shelly::
	trainerbattle_single TRAINER_SHELLY_SEAFLOOR_CAVERN, SeafloorCavern_Room3_Text_ShellyIntro, SeafloorCavern_Room3_Text_ShellyDefeat
	msgbox SeafloorCavern_Room3_Text_ShellyPostBattle, MSGBOX_AUTOCLOSE
	end

SeafloorCavern_Room3_EventScript_Grunt5::
	trainerbattle_single TRAINER_GRUNT_SEAFLOOR_CAVERN_5, SeafloorCavern_Room3_Text_Grunt5Intro, SeafloorCavern_Room3_Text_Grunt5Defeat
	msgbox SeafloorCavern_Room3_Text_Grunt5PostBattle, MSGBOX_AUTOCLOSE
	end

SeafloorCavern_Room3_Text_ShellyIntro:
	.string "¡Ahajajaja!\p"
	.string "¿Cómo lograste llegar hasta aquí sin\n"
	.string "un submarino?\l"
	.string "¡Qué niño tan impresionante!\p"
	.string "Pero... no puedo dejar que andes\n"
	.string "metiendo las narices por aquí.\p"
	.string "Y quiero venganza por lo que\n"
	.string "pasó en el INST. CLIMATOLÓGICO...\p"
	.string "¡Voy a darte una pequeña dosis\n"
	.string "de dolor! ¡Resígnate!$"

SeafloorCavern_Room3_Text_ShellyDefeat:
	.string "¡Ahajajaja!\p"
	.string "¡Ay!$"

SeafloorCavern_Room3_Text_ShellyPostBattle:
	.string "¡Ahajajaja!\n"
	.string "Eres demasiado fuerte.\p"
	.string "Es muy decepcionante que seas\n"
	.string "no eres del TEAM AQUA.\p"
	.string "Pudiste disfrutar del fabuloso\n"
	.string "mundo que nuestro JEFE prometió\l"
	.string "como uno de nosotros…$"

SeafloorCavern_Room3_Text_Grunt5Intro:
	.string "Nuestro sueño necesita el\npoder de los POKéMON.\pPero entrometidos\ncomo tú usan el\npoder POKéMON para molestarnos\l¡hasta\nen un lugar así!\p¡La vida no funciona\ncomo nosotros\nqueremos!$"

SeafloorCavern_Room3_Text_Grunt5Defeat:
	.string "Gwah!$"

SeafloorCavern_Room3_Text_Grunt5PostBattle:
	.string "Sabes, no nos atrevemos a cuestionar\n"
	.string "los motivos de nuestro líder.\p"
	.string "Pero tú no eres más que un novato\n"
	.string "enfrentándote a nuestro JEFE.\p"
	.string "Tal vez...\n"
	.string "debas ser alguien especial...$"

