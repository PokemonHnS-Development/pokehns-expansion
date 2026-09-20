CherrygroveCity_House1_hns_MapScripts::
	.byte 0

CherrygroveCity_House1_EventScript_Baldingman::
	lock
	faceplayer
	msgbox CherrygroveCity_GymSpeechHouse_Text_PokefanM, MSGBOX_DEFAULT
	closemessage
	release
	end

CherrygroveCity_House1_EventScript_Kid::
	lock
	faceplayer
	msgbox CherrygroveCity_GymSpeechHouse_Text_BugCatcher, MSGBOX_DEFAULT
	closemessage
	release
	end

CherrygroveCity_GymSpeechHouse_Text_PokefanM:
	.string "¿Quieres ver qué tan bueno\n"
	.string "eres como ENTRENADOR POKéMON?\p"
	.string "Será mejor que visites los\n"
	.string "GIMNASIOS de JOHTO y consigas\l"
	.string "MEDALLAS.$"

CherrygroveCity_GymSpeechHouse_Text_BugCatcher:
	.string "¡Cuando sea mayor, voy a ser\n"
	.string "un LÍDER de GIMNASIO!\p"
	.string "Hago luchar a mis POKéMON con\n"
	.string "los de mi amigo para que sean\l"
	.string "más fuertes!$"
