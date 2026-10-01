PetalburgCity_House2_MapScripts::
	.byte 0

PetalburgCity_House2_EventScript_Woman::
	msgbox PetalburgCity_House2_Text_NormanBecameGymLeader, MSGBOX_NPC
	end

PetalburgCity_House2_EventScript_SchoolKid::
	msgbox PetalburgCity_House2_Text_BattledNormanOnce, MSGBOX_NPC
	end

PetalburgCity_House2_Text_NormanBecameGymLeader:
	.string "NORMAN se volvió el nuevo\n"
	.string "LÍDER del GIMNASIO.\p"
	.string "Creo que llamó a su familia desde\n"
	.string "un lugar muy lejano.$"

PetalburgCity_House2_Text_BattledNormanOnce:
	.string "Luché contra NORMAN una vez, pero\n"
	.string "era demasiado fuerte.\p"
	.string "¿Cómo lo diría?\p"
	.string "Sentí que él simplemente\n"
	.string "vive para los POKéMON.$"

