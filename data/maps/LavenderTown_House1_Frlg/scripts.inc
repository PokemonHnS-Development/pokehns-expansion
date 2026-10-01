LavenderTown_House1_Frlg_MapScripts::
	.byte 0

LavenderTown_House1_EventScript_CooltrainerF::
	lock
	faceplayer
	goto_if_set FLAG_RESCUED_MR_FUJI, LavenderTown_House1_EventScript_CooltrainerFGhostGone
	msgbox LavenderTown_House1_Text_RocketsKilledCubonesMother
	release
	end

LavenderTown_House1_EventScript_CooltrainerFGhostGone::
	msgbox LavenderTown_House1_Text_GhostOfPokemonTowerIsGone
	release
	end

LavenderTown_House1_EventScript_Cubone::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_CUBONE, CRY_MODE_NORMAL
	msgbox LavenderTown_House1_Text_Cubone
	waitmoncry
	release
	end

LavenderTown_House1_Text_Cubone::
	.string "CUBONE: Kyarugoo!$"

LavenderTown_House1_Text_RocketsKilledCubonesMother::
	.string "¡Esos ROCKETS horribles!\n"
	.string "¡No merecen piedad!\p"
	.string "La pobre madre de ese CUBONE...\p"
	.string "Murió al intentar escapar de\n"
	.string "TEAM ROCKET.$"

LavenderTown_House1_Text_GhostOfPokemonTowerIsGone::
	.string "El fantasma de la TORRE\n"
	.string "POKéMON se ha ido!\p"
	.string "Alguien debe haberlo calmado\n"
	.string "¡espíritu inquieto!$"

