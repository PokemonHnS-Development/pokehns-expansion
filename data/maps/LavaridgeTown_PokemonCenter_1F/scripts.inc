LavaridgeTown_PokemonCenter_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, LavaridgeTown_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

LavaridgeTown_PokemonCenter_1F_OnTransition:
	setrespawn HEAL_LOCATION_LAVARIDGE_TOWN
	call Common_EventScript_UpdateBrineyLocation
	end

LavaridgeTown_PokemonCenter_1F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_LAVARIDGE_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

LavaridgeTown_PokemonCenter_1F_EventScript_Youngster::
	msgbox LavaridgeTown_PokemonCenter_1F_Text_HotSpringCanInvigorate, MSGBOX_NPC
	end

LavaridgeTown_PokemonCenter_1F_EventScript_Woman::
	msgbox LavaridgeTown_PokemonCenter_1F_Text_TrainersPokemonSpendTimeTogether, MSGBOX_NPC
	end

LavaridgeTown_PokemonCenter_1F_EventScript_Gentleman::
	msgbox LavaridgeTown_PokemonCenter_1F_Text_TrainersShouldRestToo, MSGBOX_NPC
	end

LavaridgeTown_PokemonCenter_1F_Text_TrainersPokemonSpendTimeTogether:
	.string "Creo que los POKéMON se unen más a\n"
	.string "sus ENTRENADORES si pasan tiempo.\p"
	.string "Cuanto más tiempo, mejor.\n"
	.string "Eso es lo que pienso.$"

LavaridgeTown_PokemonCenter_1F_Text_HotSpringCanInvigorate:
	.string "Es casi mágico cómo estar en una\n"
	.string "fuente termal puede vigorizar.\p"
	.string "Desearía que mis POKéMON también\n"
	.string "pudieran sumergirse.$"

LavaridgeTown_PokemonCenter_1F_Text_TrainersShouldRestToo:
	.string "¡Jo jo jo! Oye, niño, puedes ir a\n"
	.string "las fuentes termales desde aquí.\p"
	.string "Si los POKéMON descansan, sus\n"
	.string "ENTRENADORES también deben hacerlo.$"

