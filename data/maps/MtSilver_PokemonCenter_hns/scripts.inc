MtSilver_PokemonCenter_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MtSilver_PokemonCenter_OnTransition
	.byte 0

MtSilver_PokemonCenter_OnTransition::
	setrespawn HEAL_LOCATION_MT_SILVER_HNS
	end

MtSilver_PokemonCenter_EventScript_Meara::
	lock
	faceplayer
	goto_if_ge VAR_SINJOH_STORYLINE, 1, MtSilver_PokemonCenter_EventScript_Meara_AfterUnlockSinjoh
	msgbox MtSilver_PokemonCenter_Text_Meara1, MSGBOX_AUTOCLOSE
	checkitem ITEM_AZURE_FLUTE
	goto_if_eq VAR_RESULT, TRUE, MtSilver_PokemonCenter_EventScript_Meara_BonusContentPrompt
	release
	end

MtSilver_PokemonCenter_EventScript_Meara_BonusContentPrompt::
	msgbox MtSilver_PokemonCenter_Text_Meara2, MSGBOX_AUTOCLOSE
	helpwindow HELP_SINJOH_WINDOW
	
	msgbox MtSilver_PokemonCenter_Text_Prompt, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, MtSilver_PokemonCenter_EventScript_Meara_BonusContentNo
	closemessage

	@sinjoh flagheap
	clearflag FLAG_MT_SILVER_1F_HIDE_SCIENTIST
    setflag FLAG_NEWSINJOH_HAUNTEDHOUSE_DOORLOCK
    setflag FLAG_NEWSINJOH_HAUNTEDHOUSE_GRAVELIGHT_N
    setflag FLAG_NEWSINJOH_HAUNTEDHOUSE_GRAVELIGHT_W
    setflag FLAG_NEWSINJOH_HAUNTEDHOUSE_GRAVELIGHT_E
    setflag FLAG_NEWSINJOH_HAUNTEDHOUSE_GRAVELIGHT_S
    setflag FLAG_NEWSINJOH_HAUNTEDHOUSE_FROSLASS
    setflag FLAG_FOUGHT_NOBLE_ELECTRODE
    setflag FLAG_FOUGHT_NOBLE_ARCANINE
    setflag FLAG_FOUGHT_NOBLE_SNEASLER
    setflag FLAG_FOUGHT_NOBLE_KLEAVOR
    setflag FLAG_FOUGHT_NOBLE_URSALUNA 
    setvar VAR_PLATECOUNTER, 0
    setvar VAR_SNOWSWEPT_FINALBRIDGE, 0
	setvar VAR_SINJOH_STORYLINE, 1

	warp MAP_MT_SILVER_1F_WATERFALL_ROOM_HNS, 43, 9
	waitstate
	end

MtSilver_PokemonCenter_EventScript_Meara_BonusContentNo::
	release
	end

MtSilver_PokemonCenter_EventScript_Meara_AfterUnlockSinjoh::
	msgbox MtSilver_PokemonCenter_Text_Meara3, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE, MtSilver_PokemonCenter_EventScript_Meara_WarpToSinjoh
	closemessage
	release
	end

MtSilver_PokemonCenter_EventScript_Meara_WarpToSinjoh::
	warp MAP_MT_SILVER_1F_WATERFALL_ROOM_HNS, 43, 9
	waitstate
	release
	end

MtSilver_PokemonCenter_Text_Meara1:
	.string "I'm a researcher from the PEWTER\n"
	.string "CITY museum.\p"
	.string "An unusual amount of artifacts have\n"
	.string "been discovered in this area, so\l"
	.string "I've come here to investigate.\p"
	.string "Have you found anything strange\n"
	.string "in the mountain?$"

MtSilver_PokemonCenter_Text_Meara2:
	.string "That flute!\p"
	.string "You have the spirit of a true\n"
	.string "archaeologist!\p"
	.string "There's a branch of the cave\n"
	.string "where the POKéMON are too strong\l"
	.string "for me to safely explore.\p"
	.string "If I take you there, would you\n"
	.string "explore it for more artifacts?$"

MtSilver_PokemonCenter_Text_Prompt:
	.string "If I take you there, would you\n"
	.string "explore it for more artifacts?$"

MtSilver_PokemonCenter_Text_Meara3:
	.string "Ready to search for more artifacts?$"

