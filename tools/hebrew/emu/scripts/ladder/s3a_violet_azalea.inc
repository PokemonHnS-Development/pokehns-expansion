@ Story step 3a: after Falkner, Violet City to the Azalea Town gate (Union Cave / Route 33).
@ Same convention as s1/s2: the state ops of the named ROM scripts, in story order; text,
@ movement and sound left out. Paths are pokehns-en/data/maps/<map>/scripts.inc.

@ Violet Pokemon Center: the aide gives the Togepi Egg and an Exp. Share
@ (VioletCity_PokemonCenter_hns VioletCity_PokemonCenter_EventScript_Aide_GiveEgg:49-66).
@ The Egg itself is not given here: the party file gives the hatched Togepi.
	setflag FLAG_RECEIVED_TOGEPI_EGG
	additem ITEM_EXP_SHARE_SMALL
	setflag FLAG_HIDE_VIOLET_CITY_AIDE
	setvar VAR_VIOLET_CITY_KIMONO_GIRL, 1
	clearflag FLAG_HIDE_VIOLET_CITY_KIMONO_GIRL
	clearflag FLAG_HIDE_NEWBARKTOWN_LAB_AIDE
@ Violet City: the first Kimono Girl dances and leaves (VioletCity_EventScript_Kimono_Girl:190-221)
	setvar VAR_VIOLET_CITY_KIMONO_GIRL, 2
	setflag FLAG_HIDE_VIOLET_CITY_KIMONO_GIRL
@ Route 32: the Slowpoke Tail seller (Route32_EventScript_SlowpokeTail_Trigger:133-140, declined)
	setvar VAR_SLOWPOKE_TAIL, 1
@ Route 32: the balding man's Miracle Seed (Route32_EventScript_BaldingManCheck:263-273)
	additem ITEM_MIRACLE_SEED
	setvar VAR_VIOLET_CITY_STATE, 5
@ Route 32 Pokemon Center: the fishing guru's Old Rod (Route32_PokemonCenter_hns:26-31)
	additem ITEM_OLD_ROD
	end
