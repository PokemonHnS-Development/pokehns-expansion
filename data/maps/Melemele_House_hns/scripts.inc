Melemele_House_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Melemele_House_hns_MapScripts_MAP_SCRIPT_ON_TRANSITION
	.byte 0

Melemele_House_hns_MapScripts_MAP_SCRIPT_ON_TRANSITION:
	setrespawn HEAL_LOCATION_MELEMELE_ISLE_HNS
	end

Alola_Melemele_Pokecenter_Map::
	lock
	setvar VAR_0x8000, 0
	callnative OpenScreenshotsFromScript
	waitstate
	release
	end

Alola_Melemele_Pokecenter_AceTrainer::
	lock
	faceplayer
	msgbox Alola_Melemele_Pokecenter_AceTrainer_Text_0, MSGBOX_AUTOCLOSE
	release
	end


Alola_Melemele_Pokecenter_BugCatcher::
	lock
	faceplayer
	msgbox Alola_Melemele_Pokecenter_BugCatcher_Text_0, MSGBOX_AUTOCLOSE
	playse SE_PIN
	applymovement Melemele_PokecenterGrubbin, Alola_Melemele_Pokecenter_BugCatcher_Movement_0
	waitmovement 0
	waitse
	playmoncry SPECIES_RATTATA, 0
	waitmoncry
	release
	end


Alola_Melemele_Pokecenter_Grubbin::
	lock
	faceplayer
	playmoncry SPECIES_RATTATA, 0
	msgbox Alola_Melemele_Pokecenter_Grubbin_Text_0, MSGBOX_AUTOCLOSE
	waitmoncry
	release
	end


Alola_Melemele_Pokecenter_BugCatcher_Movement_0:
	face_up
	emote_exclamation_mark
	step_end

Alola_Melemele_Pokecenter_AceTrainer_Text_0:
	.string "There are so many unique POKéMON here!\n"
	.string "I'm gonna catch 'em all!$"

Alola_Melemele_Pokecenter_BugCatcher_Text_0:
	.string "I found some brand new POKéMON\n"
	.string "here on the ISLES!\p"
	.string "Like my new friend RATTATA here!$"

Alola_Melemele_Pokecenter_Grubbin_Text_0:
	.string "Grrr!$"


@ Jessica's Paldean Tauros trade. Which Tauros she offers depends on the
@ player's starter, so the trade always covers one of its weaknesses:
@ Cyndaquil -> Aqua, Totodile -> Blaze, Chikorita -> Combat.
Alola_Melemele_Pokecenter_Jessica::
	lock
	faceplayer
	goto_if_set FLAG_COMPLETED_TAUROS_TRADE, Alola_Melemele_Pokecenter_Jessica_TradeCompleted
	goto_if_eq VAR_STARTER_MON, 0, Alola_Melemele_Pokecenter_Jessica_TradeWater
	goto_if_eq VAR_STARTER_MON, 1, Alola_Melemele_Pokecenter_Jessica_TradeFire
	goto Alola_Melemele_Pokecenter_Jessica_TradeFight
	end

Alola_Melemele_Pokecenter_Jessica_TradeWater::
	setvar VAR_0x8005, INGAME_TRADE_TAUROS_WATER
	specialvar VAR_0x8009, GetInGameTradeSpeciesInfo
	msgbox Alola_Melemele_Pokecenter_Jessica_Text_WantToTrade, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Alola_Melemele_Pokecenter_Jessica_DeclineTrade
	chooseboxmon SELECT_PC_MON_TRADE
	waitstate
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, Alola_Melemele_Pokecenter_Jessica_DeclineTrade
	special CreateInGameTradePokemon
	special DoInGameTradeScene
	waitstate
	msgbox Alola_Melemele_Pokecenter_Jessica_Text_TakeCare, MSGBOX_DEFAULT
	setflag FLAG_COMPLETED_TAUROS_TRADE
	release
	end

Alola_Melemele_Pokecenter_Jessica_TradeFight::
	setvar VAR_0x8005, INGAME_TRADE_TAUROS_FIGHT
	specialvar VAR_0x8009, GetInGameTradeSpeciesInfo
	msgbox Alola_Melemele_Pokecenter_Jessica_Text_WantToTrade, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Alola_Melemele_Pokecenter_Jessica_DeclineTrade
	chooseboxmon SELECT_PC_MON_TRADE
	waitstate
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, Alola_Melemele_Pokecenter_Jessica_DeclineTrade
	special CreateInGameTradePokemon
	special DoInGameTradeScene
	waitstate
	msgbox Alola_Melemele_Pokecenter_Jessica_Text_TakeCare, MSGBOX_DEFAULT
	setflag FLAG_COMPLETED_TAUROS_TRADE
	release
	end

Alola_Melemele_Pokecenter_Jessica_TradeFire::
	setvar VAR_0x8005, INGAME_TRADE_TAUROS_FIRE
	specialvar VAR_0x8009, GetInGameTradeSpeciesInfo
	msgbox Alola_Melemele_Pokecenter_Jessica_Text_WantToTrade, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Alola_Melemele_Pokecenter_Jessica_DeclineTrade
	chooseboxmon SELECT_PC_MON_TRADE
	waitstate
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, Alola_Melemele_Pokecenter_Jessica_DeclineTrade
	special CreateInGameTradePokemon
	special DoInGameTradeScene
	waitstate
	msgbox Alola_Melemele_Pokecenter_Jessica_Text_TakeCare, MSGBOX_DEFAULT
	setflag FLAG_COMPLETED_TAUROS_TRADE
	release
	end

Alola_Melemele_Pokecenter_Jessica_DeclineTrade::
	msgbox Alola_Melemele_Pokecenter_Jessica_Text_DeclineTrade, MSGBOX_DEFAULT
	release
	end

Alola_Melemele_Pokecenter_Jessica_TradeCompleted::
	msgbox Alola_Melemele_Pokecenter_Jessica_Text_TradeCompleted, MSGBOX_DEFAULT
	release
	end

Alola_Melemele_Pokecenter_Jessica_Text_WantToTrade:
	.string "The {STR_VAR_2} out here aren't like\n"
	.string "the ones on the mainland.\p"
	.string "Want to trade for my {STR_VAR_2}?$"

Alola_Melemele_Pokecenter_Jessica_Text_TakeCare:
	.string "Thanks!\n"
	.string "TORY, you take care!$"

Alola_Melemele_Pokecenter_Jessica_Text_DeclineTrade:
	.string "You don't want to trade? Aww...$"

Alola_Melemele_Pokecenter_Jessica_Text_TradeCompleted:
	.string "Hi, how's my old TORY doing?$"
