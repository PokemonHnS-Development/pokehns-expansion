UlaUla_Cave_hns_MapScripts::
	.byte 0


Alola_Ulaula_BattleSandslash::
# 4 "data/maps/UlaUla_Cave_hns/scripts.pory"
	lock
# 5 "data/maps/UlaUla_Cave_hns/scripts.pory"
	faceplayer
# 6 "data/maps/UlaUla_Cave_hns/scripts.pory"
	setflag FLAG_BATTLED_SANDSLASH
# 7 "data/maps/UlaUla_Cave_hns/scripts.pory"
	playmoncry SPECIES_SANDSLASH_ALOLA, 0
# 8 "data/maps/UlaUla_Cave_hns/scripts.pory"
	msgbox Alola_Ulaula_BattleSandslash_Text_0, MSGBOX_AUTOCLOSE
# 9 "data/maps/UlaUla_Cave_hns/scripts.pory"
	waitmoncry
# 10 "data/maps/UlaUla_Cave_hns/scripts.pory"
	setwildbattle SPECIES_SANDSLASH_ALOLA, 45
# 11 "data/maps/UlaUla_Cave_hns/scripts.pory"
	dowildbattle
# 12 "data/maps/UlaUla_Cave_hns/scripts.pory"
	specialvar VAR_RESULT, GetBattleOutcome
# 13 "data/maps/UlaUla_Cave_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_CAUGHT
	goto_if_eq Alola_Ulaula_BattleSandslash_2
# 19 "data/maps/UlaUla_Cave_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq Alola_Ulaula_BattleSandslash_3
# 26 "data/maps/UlaUla_Cave_hns/scripts.pory"
	release
	end

# 29 "data/maps/UlaUla_Cave_hns/scripts.pory"
	release
	end

Alola_Ulaula_BattleSandslash_2:
# 14 "data/maps/UlaUla_Cave_hns/scripts.pory"
	setflag FLAG_CAUGHT_SANDSLASH_ALOLA
# 15 "data/maps/UlaUla_Cave_hns/scripts.pory"
	removeobject Alola_Ulaula_Sandslash
# 16 "data/maps/UlaUla_Cave_hns/scripts.pory"
	release
	end

Alola_Ulaula_BattleSandslash_3:
# 20 "data/maps/UlaUla_Cave_hns/scripts.pory"
	setflag FLAG_CAUGHT_SANDSLASH_ALOLA
# 21 "data/maps/UlaUla_Cave_hns/scripts.pory"
	removeobject Alola_Ulaula_Sandslash
# 22 "data/maps/UlaUla_Cave_hns/scripts.pory"
	release
	end


Alola_Ulaula_BattleNinetales::
# 34 "data/maps/UlaUla_Cave_hns/scripts.pory"
	lock
# 35 "data/maps/UlaUla_Cave_hns/scripts.pory"
	faceplayer
# 36 "data/maps/UlaUla_Cave_hns/scripts.pory"
	setflag FLAG_BATTLED_NINETALES
# 37 "data/maps/UlaUla_Cave_hns/scripts.pory"
	playmoncry SPECIES_NINETALES_ALOLA, 0
# 38 "data/maps/UlaUla_Cave_hns/scripts.pory"
	msgbox Alola_Ulaula_BattleSandslash_Text_0, MSGBOX_AUTOCLOSE
# 39 "data/maps/UlaUla_Cave_hns/scripts.pory"
	waitmoncry
# 40 "data/maps/UlaUla_Cave_hns/scripts.pory"
	setwildbattle SPECIES_NINETALES_ALOLA, 45
# 41 "data/maps/UlaUla_Cave_hns/scripts.pory"
	dowildbattle
# 42 "data/maps/UlaUla_Cave_hns/scripts.pory"
	specialvar VAR_RESULT, GetBattleOutcome
# 43 "data/maps/UlaUla_Cave_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_CAUGHT
	goto_if_eq Alola_Ulaula_BattleNinetales_2
# 49 "data/maps/UlaUla_Cave_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq Alola_Ulaula_BattleNinetales_3
# 56 "data/maps/UlaUla_Cave_hns/scripts.pory"
	release
	end

# 59 "data/maps/UlaUla_Cave_hns/scripts.pory"
	release
	end

Alola_Ulaula_BattleNinetales_2:
# 44 "data/maps/UlaUla_Cave_hns/scripts.pory"
	setflag FLAG_CAUGHT_NINETALES_ALOLA
# 45 "data/maps/UlaUla_Cave_hns/scripts.pory"
	removeobject Alola_Ulaula_Ninetales
# 46 "data/maps/UlaUla_Cave_hns/scripts.pory"
	release
	end

Alola_Ulaula_BattleNinetales_3:
# 50 "data/maps/UlaUla_Cave_hns/scripts.pory"
	setflag FLAG_CAUGHT_NINETALES_ALOLA
# 51 "data/maps/UlaUla_Cave_hns/scripts.pory"
	removeobject Alola_Ulaula_Ninetales
# 52 "data/maps/UlaUla_Cave_hns/scripts.pory"
	release
	end


Alola_Ulaula_Cave_FindItem1::
# 64 "data/maps/UlaUla_Cave_hns/scripts.pory"
	finditem ITEM_RARE_CANDY, 1
	end


Alola_Ulaula_Cave_FindItem2::
# 69 "data/maps/UlaUla_Cave_hns/scripts.pory"
	finditem ITEM_ADRENALINE_ORB, 1
	end


Alola_Ulaula_BattleSandslash_Text_0:
# 8 "data/maps/UlaUla_Cave_hns/scripts.pory"
	.string "Gaaah!$"
