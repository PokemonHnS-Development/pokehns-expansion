Poni_Cave_hns_MapScripts::
	.byte 0


Alola_Poni_BattleRaichu::
# 4 "data/maps/Poni_Cave_hns/scripts.pory"
	lock
# 5 "data/maps/Poni_Cave_hns/scripts.pory"
	faceplayer
# 6 "data/maps/Poni_Cave_hns/scripts.pory"
	playmoncry SPECIES_RAICHU_ALOLA, 0
# 7 "data/maps/Poni_Cave_hns/scripts.pory"
	msgbox Alola_Poni_BattleRaichu_Text_0, MSGBOX_AUTOCLOSE
# 8 "data/maps/Poni_Cave_hns/scripts.pory"
	waitmoncry
# 9 "data/maps/Poni_Cave_hns/scripts.pory"
	setwildbattle SPECIES_RAICHU_ALOLA, 45
# 10 "data/maps/Poni_Cave_hns/scripts.pory"
	dowildbattle
# 11 "data/maps/Poni_Cave_hns/scripts.pory"
	specialvar VAR_RESULT, GetBattleOutcome
# 12 "data/maps/Poni_Cave_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_CAUGHT
	goto_if_eq Alola_Poni_BattleRaichu_2
# 18 "data/maps/Poni_Cave_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq Alola_Poni_BattleRaichu_3
# 25 "data/maps/Poni_Cave_hns/scripts.pory"
	release
	end

# 28 "data/maps/Poni_Cave_hns/scripts.pory"
	release
	end

Alola_Poni_BattleRaichu_2:
# 13 "data/maps/Poni_Cave_hns/scripts.pory"
	setflag FLAG_CAUGHT_RAICHU_ALOLA
# 14 "data/maps/Poni_Cave_hns/scripts.pory"
	removeobject Alola_Poni_Raichu
# 15 "data/maps/Poni_Cave_hns/scripts.pory"
	release
	end

Alola_Poni_BattleRaichu_3:
# 19 "data/maps/Poni_Cave_hns/scripts.pory"
	setflag FLAG_CAUGHT_RAICHU_ALOLA
# 20 "data/maps/Poni_Cave_hns/scripts.pory"
	removeobject Alola_Poni_Raichu
# 21 "data/maps/Poni_Cave_hns/scripts.pory"
	release
	end


Alola_Poni_BattleGolem::
# 33 "data/maps/Poni_Cave_hns/scripts.pory"
	lock
# 34 "data/maps/Poni_Cave_hns/scripts.pory"
	faceplayer
# 35 "data/maps/Poni_Cave_hns/scripts.pory"
	playmoncry SPECIES_GOLEM_ALOLA, 0
# 36 "data/maps/Poni_Cave_hns/scripts.pory"
	msgbox Alola_Poni_BattleRaichu_Text_0, MSGBOX_AUTOCLOSE
# 37 "data/maps/Poni_Cave_hns/scripts.pory"
	waitmoncry
# 38 "data/maps/Poni_Cave_hns/scripts.pory"
	setwildbattle SPECIES_GOLEM_ALOLA, 45
# 39 "data/maps/Poni_Cave_hns/scripts.pory"
	dowildbattle
# 40 "data/maps/Poni_Cave_hns/scripts.pory"
	specialvar VAR_RESULT, GetBattleOutcome
# 41 "data/maps/Poni_Cave_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_CAUGHT
	goto_if_eq Alola_Poni_BattleGolem_2
# 47 "data/maps/Poni_Cave_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq Alola_Poni_BattleGolem_3
# 54 "data/maps/Poni_Cave_hns/scripts.pory"
	release
	end

# 57 "data/maps/Poni_Cave_hns/scripts.pory"
	release
	end

Alola_Poni_BattleGolem_2:
# 42 "data/maps/Poni_Cave_hns/scripts.pory"
	setflag FLAG_CAUGHT_GOLEM_ALOLA
# 43 "data/maps/Poni_Cave_hns/scripts.pory"
	removeobject Alola_Poni_Golem
# 44 "data/maps/Poni_Cave_hns/scripts.pory"
	release
	end

Alola_Poni_BattleGolem_3:
# 48 "data/maps/Poni_Cave_hns/scripts.pory"
	setflag FLAG_CAUGHT_GOLEM_ALOLA
# 49 "data/maps/Poni_Cave_hns/scripts.pory"
	removeobject Alola_Poni_Golem
# 50 "data/maps/Poni_Cave_hns/scripts.pory"
	release
	end


Alola_Poni_Cave_FindItem1::
# 62 "data/maps/Poni_Cave_hns/scripts.pory"
	finditem ITEM_POTION, 1
	end


Alola_Poni_Cave_FindItem2::
# 67 "data/maps/Poni_Cave_hns/scripts.pory"
	finditem ITEM_ANTIDOTE, 1
	end


Alola_Poni_BattleRaichu_Text_0:
# 7 "data/maps/Poni_Cave_hns/scripts.pory"
	.string "Gaaah!$"
