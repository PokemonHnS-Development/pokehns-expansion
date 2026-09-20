NewBarkTown_House1_hns_MapScripts::
	.byte 0

NewBarkTown_House1_EventScript_Mother::
	lock
	faceplayer
	msgbox NewBarkTown_House1_Text_Neighbor, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_House1_EventScript_Daughter::
	lock
	faceplayer
	msgbox NewBarkTown_House1_Text_NeighborsDaughter, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_House1_Text_NeighborsDaughter:
	.string "PIKACHU es un POKéMON evolucionado.\p"
	.string "Me asombró lo que dijo el PROF.ELM\n"
	.string "hallazgos.\p"
	.string "Es muy famoso por su estudio\n"
	.string "sobre la evolución POKéMON.\p"
	.string "...suspiro...\p"
	.string "Desearía ser un investigador\n"
	.string "como él...$"


NewBarkTown_House1_Text_Neighbor:
	.string "Mi hija está decidida a\n"
	.string "ser la asistente del PROF.ELM.\p"
	.string "¡Ella ama mucho a los POKéMON!\p"
	.string "¡Pero yo también los amo!$"

