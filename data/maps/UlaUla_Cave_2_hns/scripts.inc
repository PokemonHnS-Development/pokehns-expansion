UlaUla_Cave_2_hns_MapScripts::
	.byte 0


Alola_Ulaula_BattleMuk::
# 4 "data/maps/UlaUla_Cave_2_hns/scripts.pory"
	lock
# 5 "data/maps/UlaUla_Cave_2_hns/scripts.pory"
	faceplayer
# 6 "data/maps/UlaUla_Cave_2_hns/scripts.pory"
	playmoncry SPECIES_MUK_ALOLA, 0
# 7 "data/maps/UlaUla_Cave_2_hns/scripts.pory"
	msgbox Alola_Ulaula_BattleMuk_Text_0, MSGBOX_AUTOCLOSE
# 8 "data/maps/UlaUla_Cave_2_hns/scripts.pory"
	waitmoncry
# 9 "data/maps/UlaUla_Cave_2_hns/scripts.pory"
	setwildbattle SPECIES_MUK_ALOLA, 45
# 10 "data/maps/UlaUla_Cave_2_hns/scripts.pory"
	dowildbattle
# 11 "data/maps/UlaUla_Cave_2_hns/scripts.pory"
	specialvar VAR_RESULT, GetBattleOutcome
# 12 "data/maps/UlaUla_Cave_2_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_CAUGHT
	goto_if_eq Alola_Ulaula_BattleMuk_2
# 18 "data/maps/UlaUla_Cave_2_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq Alola_Ulaula_BattleMuk_3
# 25 "data/maps/UlaUla_Cave_2_hns/scripts.pory"
	release
	end

# 28 "data/maps/UlaUla_Cave_2_hns/scripts.pory"
	release
	end

Alola_Ulaula_BattleMuk_2:
# 13 "data/maps/UlaUla_Cave_2_hns/scripts.pory"
	setflag FLAG_CAUGHT_MUK_ALOLA
# 14 "data/maps/UlaUla_Cave_2_hns/scripts.pory"
	removeobject Alola_Ulaula_Muk
# 15 "data/maps/UlaUla_Cave_2_hns/scripts.pory"
	release
	end

Alola_Ulaula_BattleMuk_3:
# 19 "data/maps/UlaUla_Cave_2_hns/scripts.pory"
	setflag FLAG_CAUGHT_MUK_ALOLA
# 20 "data/maps/UlaUla_Cave_2_hns/scripts.pory"
	removeobject Alola_Ulaula_Muk
# 21 "data/maps/UlaUla_Cave_2_hns/scripts.pory"
	release
	end


Alola_Ulaula_BattleMuk_Text_0:
# 7 "data/maps/UlaUla_Cave_2_hns/scripts.pory"
	.string "Gaaah!$"
