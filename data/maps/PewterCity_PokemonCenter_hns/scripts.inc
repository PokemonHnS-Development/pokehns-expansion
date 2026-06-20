PewterCity_PokemonCenter_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, PewterCity_PokemonCenter_OnTransition
	.byte 0

PewterCity_PokemonCenter_OnTransition::
	setrespawn HEAL_LOCATION_PEWTER_CITY_HNS
	end

PewterCity_PokemonCenter_EventScript_Teacher::
	msgbox PewterCity_PokemonCenter1F_Text_Teacher, MSGBOX_NPC
	end

PewterCity_PokemonCenter_EventScript_BugCatcher::
	msgbox PewterCity_PokemonCenter1F_Text_BugCatcher, MSGBOX_NPC
	end

PewterCity_PokemonCenter1F_Text_Teacher:
	.string "…Yeah, and the GYM in CINNABAR's gone.\p"
	.string "I was really amazed.\p"
	.string "…Yes? I'm on the phone. Go away!$"

PewterCity_PokemonCenter1F_Text_Jigglypuff:
	.string "JIGGLYPUFF: Puu pupuu.$"

PewterCity_PokemonCenter_EventScript_Mondo::
	lock
	faceplayer
	goto_if_set FLAG_PEWTER_NPC_TRADE_COMPLETED, PewterCity_PokemonCenter_EventScript_TradeCompleted
	ingame_trade INGAME_TRADE_HAUNTER, PewterCity_PokemonCenter_Text_WantToTrade, PewterCity_PokemonCenter_EventScript_DeclineTrade, PewterCity_PokemonCenter_EventScript_NotRequestedMon, PewterCity_PokemonCenter_Text_TakeCare
	setflag FLAG_PEWTER_NPC_TRADE_COMPLETED
	release
	end

PewterCity_PokemonCenter_EventScript_DeclineTrade::
	msgbox PewterCity_PokemonCenter_Text_DeclineTrade, MSGBOX_DEFAULT
	release
	end

PewterCity_PokemonCenter_EventScript_NotRequestedMon::
	bufferspeciesname STR_VAR_1, VAR_0x8009
	msgbox PewterCity_PokemonCenter_Text_NotRequestedMon, MSGBOX_DEFAULT
	release
	end

PewterCity_PokemonCenter_EventScript_TradeCompleted::
	msgbox PewterCity_PokemonCenter_Text_TradeCompleted, MSGBOX_DEFAULT
	release
	end

PewterCity_PokemonCenter_Text_WantToTrade:
	.string "I've been traveling all over, looking\n"
	.string "for a good {STR_VAR_1}.\p"
	.string "Would you trade one for my\n"
	.string "{STR_VAR_2}?$"

PewterCity_PokemonCenter_Text_TakeCare:
	.string "Thanks a bunch!\n"
	.string "Take good care of my {STR_VAR_1}!$"

PewterCity_PokemonCenter_Text_DeclineTrade:
	.string "No? That's too bad…\n"
	.string "I think you'd like my HAUNTER.$"

PewterCity_PokemonCenter_Text_NotRequestedMon:
	.string "Hmm, that's not a {STR_VAR_1}.\n"
	.string "That's not what I'm looking for.$"

PewterCity_PokemonCenter_Text_TradeCompleted:
	.string "How's that HAUNTER treating you?\n"
	.string "It's a real trickster!$"

PewterCity_PokemonCenter1F_Text_BugCatcher:
	.string "Most POKéMON get drowsy if they hear a\n"
	.string "JIGGLYPUFF singing.\p"
	.string "There are several moves that can be\n"
	.string "used only while a POKéMON is asleep.$"
