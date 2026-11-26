FortreeCity_PokemonCenter_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, FortreeCity_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

FortreeCity_PokemonCenter_1F_OnTransition:
	setrespawn HEAL_LOCATION_FORTREE_CITY
	end

FortreeCity_PokemonCenter_1F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_FORTREE_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

FortreeCity_PokemonCenter_1F_EventScript_Gentleman::
	msgbox FortreeCity_PokemonCenter_1F_Text_GoToSafariZone, MSGBOX_NPC
	end

FortreeCity_PokemonCenter_1F_EventScript_Man::
	msgbox FortreeCity_PokemonCenter_1F_Text_RecordCornerIsNeat, MSGBOX_NPC
	end

FortreeCity_PokemonCenter_1F_EventScript_Boy::
	msgbox FortreeCity_PokemonCenter_1F_Text_DoYouKnowAboutPokenav, MSGBOX_NPC
	end

FortreeCity_PokemonCenter_1F_Text_GoToSafariZone:
	.string "Listen, kid, are you working\n"
	.string "on a POKéDEX?\p"
	.string "Hmm… Go to the SAFARI ZONE.\n"
	.string "That's my suggestion.$"

FortreeCity_PokemonCenter_1F_Text_RecordCornerIsNeat:
	.string "Have you done anything at\n"
	.string "the RECORD CORNER?\p"
	.string "It's pretty neat. It mixes and matches\n"
	.string "the records of TRAINERS.\p"
	.string "I don't know quite how it works,\n"
	.string "but it's cool. It's exciting, even!$"

FortreeCity_PokemonCenter_1F_Text_DoYouKnowAboutPokenav:
	.string "Oh, wow, is that a POKéGEAR?\n"
	.string "From JOHTO? Can I see?\p"
	.string "I've got a POKéNAV. DEVON makes\n"
	.string "them in RUSTBORO.\p"
	.string "Mine has MATCH CALL, so I can chat\n"
	.string "with TRAINERS I've battled.\p"
	.string "Yours has a phone, too? And a radio?\n"
	.string "No fair!$"
