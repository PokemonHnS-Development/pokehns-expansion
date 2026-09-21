VerdanturfTown_PokemonCenter_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, VerdanturfTown_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

VerdanturfTown_PokemonCenter_1F_OnTransition:
	setrespawn HEAL_LOCATION_VERDANTURF_TOWN
	call Common_EventScript_UpdateBrineyLocation
	end

VerdanturfTown_PokemonCenter_1F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_VERDANTURF_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

VerdanturfTown_PokemonCenter_1F_EventScript_Gentleman::
	msgbox VerdanturfTown_PokemonCenter_1F_Text_FaithInYourPokemon, MSGBOX_NPC
	end

VerdanturfTown_PokemonCenter_1F_EventScript_ExpertM::
	msgbox VerdanturfTown_PokemonCenter_1F_Text_VisitForBattleTent, MSGBOX_NPC
	end

VerdanturfTown_PokemonCenter_1F_Text_FaithInYourPokemon:
	.string "No puedes considerarte un real\n"
	.string "ENTRENADOR si no tienes fe\l"
	.string "en tus POKéMON.\p"
	.string "Solo quienes pueden creer\n"
	.string "en sus POKéMON de combate ganan\l"
	.string "hasta el puro final.$"

VerdanturfTown_PokemonCenter_1F_Text_VisitForBattleTent:
	.string "La razón por la que alguien\nvisitaría PUEBLO VERDANTURF…\pEs la CARPA BATALLA. No hace falta\ndecirlo.\p¿O hay alguien a quien hayas\nvenido a ver?$"

