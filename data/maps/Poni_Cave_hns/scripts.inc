Poni_Cave_hns_MapScripts::
	.byte 0


Alola_Poni_BattleRaichu::
# 4 "data/maps/Poni_Cave_hns/scripts.pory"
	lock
# 5 "data/maps/Poni_Cave_hns/scripts.pory"
	faceplayer
# 6 "data/maps/Poni_Cave_hns/scripts.pory"
	setflag FLAG_BATTLED_RAICHU
# 7 "data/maps/Poni_Cave_hns/scripts.pory"
	playmoncry SPECIES_RAICHU_ALOLA, 0
# 8 "data/maps/Poni_Cave_hns/scripts.pory"
	msgbox Alola_Poni_BattleRaichu_Text_0, MSGBOX_AUTOCLOSE
# 9 "data/maps/Poni_Cave_hns/scripts.pory"
	waitmoncry
# 10 "data/maps/Poni_Cave_hns/scripts.pory"
	setwildbattle SPECIES_RAICHU_ALOLA, 45
# 11 "data/maps/Poni_Cave_hns/scripts.pory"
	dowildbattle
# 12 "data/maps/Poni_Cave_hns/scripts.pory"
	specialvar VAR_RESULT, GetBattleOutcome
# 13 "data/maps/Poni_Cave_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_CAUGHT
	goto_if_eq Alola_Poni_BattleRaichu_2
# 19 "data/maps/Poni_Cave_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq Alola_Poni_BattleRaichu_3
# 26 "data/maps/Poni_Cave_hns/scripts.pory"
	release
	end

# 29 "data/maps/Poni_Cave_hns/scripts.pory"
	release
	end

Alola_Poni_BattleRaichu_2:
# 14 "data/maps/Poni_Cave_hns/scripts.pory"
	setflag FLAG_CAUGHT_RAICHU_ALOLA
# 15 "data/maps/Poni_Cave_hns/scripts.pory"
	removeobject Alola_Poni_Raichu
# 16 "data/maps/Poni_Cave_hns/scripts.pory"
	release
	end

Alola_Poni_BattleRaichu_3:
# 20 "data/maps/Poni_Cave_hns/scripts.pory"
	setflag FLAG_CAUGHT_RAICHU_ALOLA
# 21 "data/maps/Poni_Cave_hns/scripts.pory"
	removeobject Alola_Poni_Raichu
# 22 "data/maps/Poni_Cave_hns/scripts.pory"
	release
	end


Alola_Poni_BattleGolem::
# 34 "data/maps/Poni_Cave_hns/scripts.pory"
	lock
# 35 "data/maps/Poni_Cave_hns/scripts.pory"
	faceplayer
# 36 "data/maps/Poni_Cave_hns/scripts.pory"
	setflag FLAG_BATTLED_GOLEM
# 37 "data/maps/Poni_Cave_hns/scripts.pory"
	playmoncry SPECIES_GOLEM_ALOLA, 0
# 38 "data/maps/Poni_Cave_hns/scripts.pory"
	msgbox Alola_Poni_BattleRaichu_Text_0, MSGBOX_AUTOCLOSE
# 39 "data/maps/Poni_Cave_hns/scripts.pory"
	waitmoncry
# 40 "data/maps/Poni_Cave_hns/scripts.pory"
	setwildbattle SPECIES_GOLEM_ALOLA, 45
# 41 "data/maps/Poni_Cave_hns/scripts.pory"
	dowildbattle
# 42 "data/maps/Poni_Cave_hns/scripts.pory"
	specialvar VAR_RESULT, GetBattleOutcome
# 43 "data/maps/Poni_Cave_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_CAUGHT
	goto_if_eq Alola_Poni_BattleGolem_2
# 49 "data/maps/Poni_Cave_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq Alola_Poni_BattleGolem_3
# 56 "data/maps/Poni_Cave_hns/scripts.pory"
	release
	end

# 59 "data/maps/Poni_Cave_hns/scripts.pory"
	release
	end

Alola_Poni_BattleGolem_2:
# 44 "data/maps/Poni_Cave_hns/scripts.pory"
	setflag FLAG_CAUGHT_GOLEM_ALOLA
# 45 "data/maps/Poni_Cave_hns/scripts.pory"
	removeobject Alola_Poni_Golem
# 46 "data/maps/Poni_Cave_hns/scripts.pory"
	release
	end

Alola_Poni_BattleGolem_3:
# 50 "data/maps/Poni_Cave_hns/scripts.pory"
	setflag FLAG_CAUGHT_GOLEM_ALOLA
# 51 "data/maps/Poni_Cave_hns/scripts.pory"
	removeobject Alola_Poni_Golem
# 52 "data/maps/Poni_Cave_hns/scripts.pory"
	release
	end


Alola_Poni_Cave_FindItem1::
# 64 "data/maps/Poni_Cave_hns/scripts.pory"
	finditem ITEM_CALCIUM, 1
	end


Alola_Poni_Cave_FindItem2::
# 69 "data/maps/Poni_Cave_hns/scripts.pory"
	finditem ITEM_THUNDER_STONE, 1
	end


Alola_Poni_BattleRaichu_Text_0:
# 8 "data/maps/Poni_Cave_hns/scripts.pory"
	.string "Gaaah!$"
