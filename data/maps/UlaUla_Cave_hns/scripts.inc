UlaUla_Cave_hns_MapScripts::
	.byte 0


Alola_Ulaula_BattleSandslash::
# 4 "data/maps/UlaUla_Cave_hns/scripts.pory"
	lock
# 5 "data/maps/UlaUla_Cave_hns/scripts.pory"
	faceplayer
# 6 "data/maps/UlaUla_Cave_hns/scripts.pory"
	playmoncry SPECIES_SANDSLASH_ALOLA, 0
# 7 "data/maps/UlaUla_Cave_hns/scripts.pory"
	msgbox Alola_Ulaula_BattleSandslash_Text_0, MSGBOX_AUTOCLOSE
# 8 "data/maps/UlaUla_Cave_hns/scripts.pory"
	waitmoncry
# 9 "data/maps/UlaUla_Cave_hns/scripts.pory"
	setwildbattle SPECIES_SANDSLASH_ALOLA, 45
# 10 "data/maps/UlaUla_Cave_hns/scripts.pory"
	dowildbattle
# 11 "data/maps/UlaUla_Cave_hns/scripts.pory"
	specialvar VAR_RESULT, GetBattleOutcome
# 12 "data/maps/UlaUla_Cave_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_CAUGHT
	goto_if_eq Alola_Ulaula_BattleSandslash_2
# 18 "data/maps/UlaUla_Cave_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq Alola_Ulaula_BattleSandslash_3
# 25 "data/maps/UlaUla_Cave_hns/scripts.pory"
	release
	end

# 28 "data/maps/UlaUla_Cave_hns/scripts.pory"
	release
	end

Alola_Ulaula_BattleSandslash_2:
# 13 "data/maps/UlaUla_Cave_hns/scripts.pory"
	setflag FLAG_CAUGHT_SANDSLASH_ALOLA
# 14 "data/maps/UlaUla_Cave_hns/scripts.pory"
	removeobject Alola_Ulaula_Sandslash
# 15 "data/maps/UlaUla_Cave_hns/scripts.pory"
	release
	end

Alola_Ulaula_BattleSandslash_3:
# 19 "data/maps/UlaUla_Cave_hns/scripts.pory"
	setflag FLAG_CAUGHT_SANDSLASH_ALOLA
# 20 "data/maps/UlaUla_Cave_hns/scripts.pory"
	removeobject Alola_Ulaula_Sandslash
# 21 "data/maps/UlaUla_Cave_hns/scripts.pory"
	release
	end


Alola_Ulaula_BattleNinetales::
# 33 "data/maps/UlaUla_Cave_hns/scripts.pory"
	lock
# 34 "data/maps/UlaUla_Cave_hns/scripts.pory"
	faceplayer
# 35 "data/maps/UlaUla_Cave_hns/scripts.pory"
	playmoncry SPECIES_NINETALES_ALOLA, 0
# 36 "data/maps/UlaUla_Cave_hns/scripts.pory"
	msgbox Alola_Ulaula_BattleSandslash_Text_0, MSGBOX_AUTOCLOSE
# 37 "data/maps/UlaUla_Cave_hns/scripts.pory"
	waitmoncry
# 38 "data/maps/UlaUla_Cave_hns/scripts.pory"
	setwildbattle SPECIES_NINETALES_ALOLA, 45
# 39 "data/maps/UlaUla_Cave_hns/scripts.pory"
	dowildbattle
# 40 "data/maps/UlaUla_Cave_hns/scripts.pory"
	specialvar VAR_RESULT, GetBattleOutcome
# 41 "data/maps/UlaUla_Cave_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_CAUGHT
	goto_if_eq Alola_Ulaula_BattleNinetales_2
# 47 "data/maps/UlaUla_Cave_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq Alola_Ulaula_BattleNinetales_3
# 54 "data/maps/UlaUla_Cave_hns/scripts.pory"
	release
	end

# 57 "data/maps/UlaUla_Cave_hns/scripts.pory"
	release
	end

Alola_Ulaula_BattleNinetales_2:
# 42 "data/maps/UlaUla_Cave_hns/scripts.pory"
	setflag FLAG_CAUGHT_NINETALES_ALOLA
# 43 "data/maps/UlaUla_Cave_hns/scripts.pory"
	removeobject Alola_Ulaula_Ninetales
# 44 "data/maps/UlaUla_Cave_hns/scripts.pory"
	release
	end

Alola_Ulaula_BattleNinetales_3:
# 48 "data/maps/UlaUla_Cave_hns/scripts.pory"
	setflag FLAG_CAUGHT_NINETALES_ALOLA
# 49 "data/maps/UlaUla_Cave_hns/scripts.pory"
	removeobject Alola_Ulaula_Ninetales
# 50 "data/maps/UlaUla_Cave_hns/scripts.pory"
	release
	end


Alola_Ulaula_Cave_FindItem1::
# 62 "data/maps/UlaUla_Cave_hns/scripts.pory"
	finditem ITEM_POTION, 1
	end


Alola_Ulaula_Cave_FindItem2::
# 67 "data/maps/UlaUla_Cave_hns/scripts.pory"
	finditem ITEM_ANTIDOTE, 1
	end


Alola_Ulaula_BattleSandslash_Text_0:
# 7 "data/maps/UlaUla_Cave_hns/scripts.pory"
	.string "Gaaah!$"
