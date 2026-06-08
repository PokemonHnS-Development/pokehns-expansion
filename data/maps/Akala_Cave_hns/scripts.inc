Akala_Cave_hns_MapScripts::
	.byte 0


Alola_Melemele_BattleMarowak::
# 4 "data/maps/Akala_Cave_hns/scripts.pory"
	lock
# 5 "data/maps/Akala_Cave_hns/scripts.pory"
	faceplayer
# 6 "data/maps/Akala_Cave_hns/scripts.pory"
	playmoncry SPECIES_MAROWAK_ALOLA, 0
# 7 "data/maps/Akala_Cave_hns/scripts.pory"
	msgbox Alola_Melemele_BattleMarowak_Text_0, MSGBOX_AUTOCLOSE
# 8 "data/maps/Akala_Cave_hns/scripts.pory"
	waitmoncry
# 9 "data/maps/Akala_Cave_hns/scripts.pory"
	setwildbattle SPECIES_MAROWAK_ALOLA, 45
# 10 "data/maps/Akala_Cave_hns/scripts.pory"
	dowildbattle
# 11 "data/maps/Akala_Cave_hns/scripts.pory"
	specialvar VAR_RESULT, GetBattleOutcome
# 12 "data/maps/Akala_Cave_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_CAUGHT
	goto_if_eq Alola_Melemele_BattleMarowak_2
# 18 "data/maps/Akala_Cave_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq Alola_Melemele_BattleMarowak_3
# 25 "data/maps/Akala_Cave_hns/scripts.pory"
	release
	end

# 28 "data/maps/Akala_Cave_hns/scripts.pory"
	release
	end

Alola_Melemele_BattleMarowak_2:
# 13 "data/maps/Akala_Cave_hns/scripts.pory"
	setflag FLAG_CAUGHT_MAROWAK_ALOLA
# 14 "data/maps/Akala_Cave_hns/scripts.pory"
	removeobject Alola_Melemele_Marowak
# 15 "data/maps/Akala_Cave_hns/scripts.pory"
	release
	end

Alola_Melemele_BattleMarowak_3:
# 19 "data/maps/Akala_Cave_hns/scripts.pory"
	setflag FLAG_CAUGHT_MAROWAK_ALOLA
# 20 "data/maps/Akala_Cave_hns/scripts.pory"
	removeobject Alola_Melemele_Marowak
# 21 "data/maps/Akala_Cave_hns/scripts.pory"
	release
	end


Alola_Melemele_BattleDugtrio::
# 33 "data/maps/Akala_Cave_hns/scripts.pory"
	lock
# 34 "data/maps/Akala_Cave_hns/scripts.pory"
	faceplayer
# 35 "data/maps/Akala_Cave_hns/scripts.pory"
	playmoncry SPECIES_DUGTRIO_ALOLA, 0
# 36 "data/maps/Akala_Cave_hns/scripts.pory"
	msgbox Alola_Melemele_BattleMarowak_Text_0, MSGBOX_AUTOCLOSE
# 37 "data/maps/Akala_Cave_hns/scripts.pory"
	waitmoncry
# 38 "data/maps/Akala_Cave_hns/scripts.pory"
	setwildbattle SPECIES_DUGTRIO_ALOLA, 45
# 39 "data/maps/Akala_Cave_hns/scripts.pory"
	dowildbattle
# 40 "data/maps/Akala_Cave_hns/scripts.pory"
	specialvar VAR_RESULT, GetBattleOutcome
# 41 "data/maps/Akala_Cave_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_CAUGHT
	goto_if_eq Alola_Melemele_BattleDugtrio_2
# 47 "data/maps/Akala_Cave_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq Alola_Melemele_BattleDugtrio_3
# 54 "data/maps/Akala_Cave_hns/scripts.pory"
	release
	end

# 57 "data/maps/Akala_Cave_hns/scripts.pory"
	release
	end

Alola_Melemele_BattleDugtrio_2:
# 42 "data/maps/Akala_Cave_hns/scripts.pory"
	setflag FLAG_CAUGHT_DUGTRIO_ALOLA
# 43 "data/maps/Akala_Cave_hns/scripts.pory"
	removeobject Alola_Melemele_Dugtrio
# 44 "data/maps/Akala_Cave_hns/scripts.pory"
	release
	end

Alola_Melemele_BattleDugtrio_3:
# 48 "data/maps/Akala_Cave_hns/scripts.pory"
	setflag FLAG_CAUGHT_DUGTRIO_ALOLA
# 49 "data/maps/Akala_Cave_hns/scripts.pory"
	removeobject Alola_Melemele_Dugtrio
# 50 "data/maps/Akala_Cave_hns/scripts.pory"
	release
	end


Alola_Akala_Cave_FindItem1::
# 63 "data/maps/Akala_Cave_hns/scripts.pory"
	finditem ITEM_POTION, 1
	end


Alola_Akala_Cave_FindItem2::
# 68 "data/maps/Akala_Cave_hns/scripts.pory"
	finditem ITEM_ANTIDOTE, 1
	end


Alola_Melemele_BattleMarowak_Text_0:
# 7 "data/maps/Akala_Cave_hns/scripts.pory"
	.string "Gaaah!$"
