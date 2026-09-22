ThreeIsland_House2_Frlg_MapScripts::
	.byte 0

ThreeIsland_House2_EventScript_Man::
	lock
	faceplayer
	famechecker FAMECHECKER_SABRINA, 1
	msgbox ThreeIsland_House2_Text_IAdmireSabrina
	release
	end

ThreeIsland_House2_EventScript_Rocker::
	msgbox ThreeIsland_House2_Text_CantMakeThisSpoonBend, MSGBOX_NPC
	end

ThreeIsland_House2_Text_CantMakeThisSpoonBend::
	.string "Urrrrrrrrgggghhhh…\n"
	.string "Kwaaaaah!\p"
	.string "…¡Es inútil! No puedo doblar\n"
	.string "esta cuchara con la mente.\p"
	.string "Quizá de verdad no tengo\n"
	.string "psychic powers.$"

ThreeIsland_House2_Text_IAdmireSabrina::
	.string "¿Sabes de una chica LÍDER DE GYM\n"
	.string "en CIUDAD AZAFRÁN?\p"
	.string "Usa POKéMON de tipo PSÍQUICO,\n"
	.string "¿Verdad?\p"
	.string "La admiro, de verdad.\p"
	.string "He oído que es muy serena\n"
	.string "y además hermosa.$"

