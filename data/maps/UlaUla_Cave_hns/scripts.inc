UlaUla_Cave_hns_MapScripts::
	.byte 0


Alola_Ulaula_BattleSandslash::
	lock
	faceplayer
	setflag FLAG_BATTLED_SANDSLASH
	playmoncry SPECIES_SANDSLASH_ALOLA, 0
	msgbox Alola_Ulaula_BattleSandslash_Text_0, MSGBOX_AUTOCLOSE
	waitmoncry
	setwildbattle SPECIES_SANDSLASH_ALOLA, 45
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	compare VAR_RESULT, B_OUTCOME_CAUGHT
	goto_if_eq Alola_Ulaula_BattleSandslash_2
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq Alola_Ulaula_BattleSandslash_3
	release
	end

	release
	end

Alola_Ulaula_BattleSandslash_2:
	setflag FLAG_HIDE_SANDSLASH_ALOLA
	removeobject Alola_Ulaula_Sandslash
	release
	end

Alola_Ulaula_BattleSandslash_3:
	setflag FLAG_HIDE_SANDSLASH_ALOLA
	removeobject Alola_Ulaula_Sandslash
	release
	end


Alola_Ulaula_BattleNinetales::
	lock
	faceplayer
	setflag FLAG_BATTLED_NINETALES
	playmoncry SPECIES_NINETALES_ALOLA, 0
	msgbox Alola_Ulaula_BattleSandslash_Text_0, MSGBOX_AUTOCLOSE
	waitmoncry
	setwildbattle SPECIES_NINETALES_ALOLA, 45
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	compare VAR_RESULT, B_OUTCOME_CAUGHT
	goto_if_eq Alola_Ulaula_BattleNinetales_2
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq Alola_Ulaula_BattleNinetales_3
	release
	end

	release
	end

Alola_Ulaula_BattleNinetales_2:
	setflag FLAG_HIDE_NINETALES_ALOLA
	removeobject Alola_Ulaula_Ninetales
	release
	end

Alola_Ulaula_BattleNinetales_3:
	setflag FLAG_HIDE_NINETALES_ALOLA
	removeobject Alola_Ulaula_Ninetales
	release
	end


Alola_Ulaula_Cave_FindItem1::
	finditem ITEM_ICE_STONE, 1
	end


Alola_Ulaula_Cave_FindItem2::
	finditem ITEM_ADRENALINE_ORB, 1
	end


Alola_Ulaula_BattleSandslash_Text_0:
	.string "Graah!$"
