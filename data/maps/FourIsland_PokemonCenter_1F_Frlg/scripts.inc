FourIsland_PokemonCenter_1F_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, FourIsland_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

FourIsland_PokemonCenter_1F_OnTransition::
	setrespawn HEAL_LOCATION_FOUR_ISLAND
	end

FourIsland_PokemonCenter_1F_EventScript_Nurse::
	lock
	faceplayer
	call EventScript_PkmnCenterNurse_Frlg
	release
	end

FourIsland_PokemonCenter_1F_EventScript_Man::
	msgbox FourIsland_PokemonCenter_1F_Text_RareIceMonsInCave, MSGBOX_NPC
	end

FourIsland_PokemonCenter_1F_EventScript_Woman::
	msgbox FourIsland_PokemonCenter_1F_Text_DayCarePeopleFoundEggBefore, MSGBOX_NPC
	end

FourIsland_PokemonCenter_1F_EventScript_Gentleman::
	msgbox FourIsland_PokemonCenter_1F_Text_NewPokemonJournalHasntArrived, MSGBOX_NPC
	end

@ The 5 texts below are supposed to be in FourIsland_House1
Text_BodySlamTeach::
	.string "¿Listo?\n"
	.string "Boing!\p"
	.string "Tenemos un combate de GOLPE\n"
	.string "a ver quién se rinde primero.\p"
	.string "Si te unieras a nosotros, serías\n"
	.string "aplastado como un insecto...\p"
	.string "¿Qué tal si le enseño GOLPE CUERPO a\n"
	.string "a un POKéMON tuyo?$"

Text_BodySlamDeclined::
	.string "¡Vuelve pronto!\n"
	.string "Boing!$"

Text_BodySlamWhichMon::
	.string "¿Qué POKéMON quiere aprender\n"
	.string "GOLPE CUERPO?$"

Text_BodySlamTaught::
	.string "Boioing!$"

FourIsland_House1_Text_FatMan::
	.string "それ　ぼよーん！\n"
	.string "おまえ　おもいなあー！$"

FourIsland_PokemonCenter_1F_Text_RareIceMonsInCave::
	.string "Hay un raro POKéMON de HIELO\n"
	.string "que vive en la cueva.\p"
	.string "Recibimos muchos visitantes que\n"
	.string "ver a ese POKéMON.$"

FourIsland_PokemonCenter_1F_Text_DayCarePeopleFoundEggBefore::
	.string "Oh? A POKéMON EGG?\n"
	.string "...No tengo idea.\p"
	.string "...Ah, espera. La gente de la\n"
	.string "GUARDERÍA decía algo.\p"
	.string "Dijeron que habían encontrado\n"
	.string "HUEVOS antes en su terreno.$"

FourIsland_PokemonCenter_1F_Text_NewPokemonJournalHasntArrived::
	.string "¿Qué es esto?\p"
	.string "La nueva REVISTA POKéMON no\n"
	.string "llegó a esta isla?$"

