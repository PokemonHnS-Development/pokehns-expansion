Akala_Cave_hns_MapScripts::
	.byte 0


Alola_Melemele_BattleMarowak::
# 4 "data/maps/Akala_Cave_hns/scripts.pory"
	lock
# 5 "data/maps/Akala_Cave_hns/scripts.pory"
	faceplayer
# 6 "data/maps/Akala_Cave_hns/scripts.pory"
	setflag FLAG_BATTLED_MAROWAK
# 7 "data/maps/Akala_Cave_hns/scripts.pory"
	playmoncry SPECIES_MAROWAK_ALOLA, 0
# 8 "data/maps/Akala_Cave_hns/scripts.pory"
	msgbox Alola_Melemele_BattleMarowak_Text_0, MSGBOX_AUTOCLOSE
# 9 "data/maps/Akala_Cave_hns/scripts.pory"
	waitmoncry
# 10 "data/maps/Akala_Cave_hns/scripts.pory"
	setwildbattle SPECIES_MAROWAK_ALOLA, 45
# 11 "data/maps/Akala_Cave_hns/scripts.pory"
	dowildbattle
# 12 "data/maps/Akala_Cave_hns/scripts.pory"
	specialvar VAR_RESULT, GetBattleOutcome
# 13 "data/maps/Akala_Cave_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_CAUGHT
	goto_if_eq Alola_Melemele_BattleMarowak_2
# 19 "data/maps/Akala_Cave_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq Alola_Melemele_BattleMarowak_3
# 26 "data/maps/Akala_Cave_hns/scripts.pory"
	release
	end

# 29 "data/maps/Akala_Cave_hns/scripts.pory"
	release
	end

Alola_Melemele_BattleMarowak_2:
# 14 "data/maps/Akala_Cave_hns/scripts.pory"
	setflag FLAG_CAUGHT_MAROWAK_ALOLA
# 15 "data/maps/Akala_Cave_hns/scripts.pory"
	removeobject Alola_Melemele_Marowak
# 16 "data/maps/Akala_Cave_hns/scripts.pory"
	release
	end

Alola_Melemele_BattleMarowak_3:
# 20 "data/maps/Akala_Cave_hns/scripts.pory"
	setflag FLAG_CAUGHT_MAROWAK_ALOLA
# 21 "data/maps/Akala_Cave_hns/scripts.pory"
	removeobject Alola_Melemele_Marowak
# 22 "data/maps/Akala_Cave_hns/scripts.pory"
	release
	end


Alola_Melemele_BattleDugtrio::
# 34 "data/maps/Akala_Cave_hns/scripts.pory"
	lock
# 35 "data/maps/Akala_Cave_hns/scripts.pory"
	faceplayer
# 36 "data/maps/Akala_Cave_hns/scripts.pory"
	setflag FLAG_BATTLED_DUGTRIO
# 37 "data/maps/Akala_Cave_hns/scripts.pory"
	playmoncry SPECIES_DUGTRIO_ALOLA, 0
# 38 "data/maps/Akala_Cave_hns/scripts.pory"
	msgbox Alola_Melemele_BattleMarowak_Text_0, MSGBOX_AUTOCLOSE
# 39 "data/maps/Akala_Cave_hns/scripts.pory"
	waitmoncry
# 40 "data/maps/Akala_Cave_hns/scripts.pory"
	setwildbattle SPECIES_DUGTRIO_ALOLA, 45
# 41 "data/maps/Akala_Cave_hns/scripts.pory"
	dowildbattle
# 42 "data/maps/Akala_Cave_hns/scripts.pory"
	specialvar VAR_RESULT, GetBattleOutcome
# 43 "data/maps/Akala_Cave_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_CAUGHT
	goto_if_eq Alola_Melemele_BattleDugtrio_2
# 49 "data/maps/Akala_Cave_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq Alola_Melemele_BattleDugtrio_3
# 56 "data/maps/Akala_Cave_hns/scripts.pory"
	release
	end

# 59 "data/maps/Akala_Cave_hns/scripts.pory"
	release
	end

Alola_Melemele_BattleDugtrio_2:
# 44 "data/maps/Akala_Cave_hns/scripts.pory"
	setflag FLAG_CAUGHT_DUGTRIO_ALOLA
# 45 "data/maps/Akala_Cave_hns/scripts.pory"
	removeobject Alola_Melemele_Dugtrio
# 46 "data/maps/Akala_Cave_hns/scripts.pory"
	release
	end

Alola_Melemele_BattleDugtrio_3:
# 50 "data/maps/Akala_Cave_hns/scripts.pory"
	setflag FLAG_CAUGHT_DUGTRIO_ALOLA
# 51 "data/maps/Akala_Cave_hns/scripts.pory"
	removeobject Alola_Melemele_Dugtrio
# 52 "data/maps/Akala_Cave_hns/scripts.pory"
	release
	end


Alola_Akala_Cave_FindItem1::
# 65 "data/maps/Akala_Cave_hns/scripts.pory"
	finditem ITEM_POTION, 1
	end


Alola_Akala_Cave_FindItem2::
# 70 "data/maps/Akala_Cave_hns/scripts.pory"
	finditem ITEM_ANTIDOTE, 1
	end


Alola_Melemele_BattleMarowak_Text_0:
# 8 "data/maps/Akala_Cave_hns/scripts.pory"
	.string "Gaaah!$"
