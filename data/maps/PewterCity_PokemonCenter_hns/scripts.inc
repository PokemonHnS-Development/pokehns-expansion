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
	.string "…כן, והמכון בסיננבר נעלם.\p"
	.string "ממש נדהמתי.\p"
	.string "…כן? אני בטלפון. לך מפה!$"

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
	.string "טיילתי בכל מקום, בחיפוש אחר\n"
	.string "{STR_VAR_1} טוב.\p"
	.string "תסכים לתת לי אחד בתמורה\n"
	.string "ל{STR_VAR_2} שלי?$"

PewterCity_PokemonCenter_Text_TakeCare:
	.string "תודה רבה!\n"
	.string "תשמור היטב על ה{STR_VAR_1} שלי!$"

PewterCity_PokemonCenter_Text_DeclineTrade:
	.string "לא? חבל…\n"
	.string "אני חושב שהיית אוהב את ההאנטר שלי.$"

PewterCity_PokemonCenter_Text_NotRequestedMon:
	.string "הממ, זה לא {STR_VAR_1}.\n"
	.string "זה לא מה שאני מחפש.$"

PewterCity_PokemonCenter_Text_TradeCompleted:
	.string "איך ההאנטר מתייחס אליך?\n"
	.string "הוא ממש שובב!$"

PewterCity_PokemonCenter1F_Text_BugCatcher:
	.string "רוב הפוקימונים נהיים ישנוניים כשהם\n"
	.string "שומעים ג'יגליפאף שר.\p"
	.string "יש כמה מהלכים שאפשר להשתמש\n"
	.string "בהם רק כשהפוקימון ישן.$"
