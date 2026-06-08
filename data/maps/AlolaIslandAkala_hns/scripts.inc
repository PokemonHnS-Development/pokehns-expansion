AlolaIslandAkala_hns_MapScripts::
	.byte 0


Alola_Ulaula_BattlePalossand::
# 4 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	lock
# 5 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	faceplayer
# 6 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	playmoncry SPECIES_PALOSSAND, 0
# 7 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	msgbox Alola_Ulaula_BattlePalossand_Text_0, MSGBOX_AUTOCLOSE
# 8 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	waitmoncry
# 9 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	setwildbattle SPECIES_PALOSSAND, 45
# 10 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	dowildbattle
# 11 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	specialvar VAR_RESULT, GetBattleOutcome
# 12 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_CAUGHT
	goto_if_eq Alola_Ulaula_BattlePalossand_2
# 18 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq Alola_Ulaula_BattlePalossand_3
# 25 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	release
	end

# 28 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	release
	end

Alola_Ulaula_BattlePalossand_2:
# 13 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	setflag FLAG_CAUGHT_PALOSSAND
# 14 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	removeobject Alola_Ulaula_Palossand
# 15 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	release
	end

Alola_Ulaula_BattlePalossand_3:
# 19 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	setflag FLAG_CAUGHT_PALOSSAND
# 20 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	removeobject Alola_Ulaula_Palossand
# 21 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	release
	end


Alola_Ulaula_FindItem1::
# 33 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	finditem ITEM_POTION, 1
	end


Alola_Ulaula_FindItem2::
# 38 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	finditem ITEM_ANTIDOTE, 1
	end


Alola_Ulaula_MtLanikalaSign::
# 43 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	lock
# 44 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	msgbox Alola_Ulaula_MtLanikalaSign_Text_0
# 45 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	release
	end


Alola_Ulaula_BattlePalossand_Text_0:
# 7 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	.string "Gaaah!$"

Alola_Ulaula_MtLanikalaSign_Text_0:
# 44 "data/maps/AlolaIslandAkala_hns/scripts.pory"
	.string "Mt. Lanakila$"
