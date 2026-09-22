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
	.string "Ready?\n"
	.string "Boing!\p"
	.string "Tenemos un combate de GOLPE\n"
	.string "to see who wimps out first.\p"
	.string "If you were to join us, you'd be\n"
	.string "squashed like a bug, though...\p"
	.string "¿Qué tal si le enseño GOLPE CUERPO a\n"
	.string "a POKéMON of yours instead?$"

Text_BodySlamDeclined::
	.string "Come again!\n"
	.string "Boing!$"

Text_BodySlamWhichMon::
	.string "Which POKéMON wants to learn how\n"
	.string "GOLPE CUERPO?$"

Text_BodySlamTaught::
	.string "Boioing!$"

FourIsland_House1_Text_FatMan::
	.string "それ　ぼよーん！\n"
	.string "おまえ　おもいなあー！$"

FourIsland_PokemonCenter_1F_Text_RareIceMonsInCave::
	.string "There's a rare kind of ICE POKéMON\n"
	.string "que vive en la cueva.\p"
	.string "Recibimos muchos visitantes que\n"
	.string "see that POKéMON.$"

FourIsland_PokemonCenter_1F_Text_DayCarePeopleFoundEggBefore::
	.string "Oh? A POKéMON EGG?\n"
	.string "...No tengo idea.\p"
	.string "...Ah, espera. La gente de la\n"
	.string "GUARDERÍA decía algo.\p"
	.string "Dijeron que habían encontrado\n"
	.string "HUEVOS antes en su terreno.$"

FourIsland_PokemonCenter_1F_Text_NewPokemonJournalHasntArrived::
	.string "¿Qué es esto?\p"
	.string "The new POKéMON JOURNAL hasn't\n"
	.string "llegaste a esta isla?$"

