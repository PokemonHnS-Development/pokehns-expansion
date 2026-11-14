ViridianCity_PokemonCenter_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, ViridianCity_PokemonCenter_OnTransition
	.byte 0

ViridianCity_PokemonCenter_OnTransition::
	setrespawn HEAL_LOCATION_VIRIDIAN_CITY_HNS
	end

ViridianCity_PokemonCenter_EventScript_CooltrainerM::
	goto_if_set FLAG_HIDE_CINNABAR_BLUE, VirianCity_EventScript_GymGrampsBlue
	msgbox ViridianCity_PokemonCenter_Text_1FCooltrainerM, MSGBOX_NPC
	end

ViridianCity_PokemonCenter_EventScript_CooltrainerMBlue::
	msgbox ViridianCity_PokemonCenter_Text_1FCooltrainerM_BlueReturned, MSGBOX_NPC
	end

ViridianCity_PokemonCenter_EventScript_CooltrainerF::
	msgbox ViridianCity_PokemonCenter_Text_1FCooltrainerF, MSGBOX_NPC
	end

ViridianCity_PokemonCenter_EventScript_BugCatcher::
	msgbox ViridianCity_PokemonCenter_Text_1FBugCatcher, MSGBOX_NPC
	end

ViridianCity_PokemonCenter_Text_1FCooltrainerM:
	.string "לאן נעלם המנהיג של מכון\n"
	.string "וירידיאן? רציתי לאתגר אותו.$"

ViridianCity_PokemonCenter_Text_1FCooltrainerM_BlueReturned:
	.string "There are no GYM TRAINERS at the\n"
	.string "VIRIDIAN GYM.\p"
	.string "The LEADER claims his policy is to\n"
	.string "win without having any underlings.$"

ViridianCity_PokemonCenter_Text_1FCooltrainerF:
	.string "שמעתי שהמכון בסיננבר\n"
	.string "כבר לא קיים.\p"
	.string "מעניין מה קרה לבליין,\n"
	.string "מנהיג המכון.$"

ViridianCity_PokemonCenter_Text_1FBugCatcher:
	.string "החלום שלי הוא להיות מנהיג מכון.$"
