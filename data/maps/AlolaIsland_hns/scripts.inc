AlolaIsland_hns_MapScripts::
	.byte 0


Alola_Poni_BattleExeggutor::
# 6 "data/maps/AlolaIsland_hns/scripts.pory"
	lock
# 7 "data/maps/AlolaIsland_hns/scripts.pory"
	faceplayer
# 8 "data/maps/AlolaIsland_hns/scripts.pory"
	playmoncry SPECIES_EXEGGUTOR_ALOLA, 0
# 9 "data/maps/AlolaIsland_hns/scripts.pory"
	msgbox Alola_Poni_BattleExeggutor_Text_0, MSGBOX_AUTOCLOSE
# 10 "data/maps/AlolaIsland_hns/scripts.pory"
	waitmoncry
# 11 "data/maps/AlolaIsland_hns/scripts.pory"
	setwildbattle SPECIES_EXEGGUTOR_ALOLA, 45
# 12 "data/maps/AlolaIsland_hns/scripts.pory"
	dowildbattle
# 13 "data/maps/AlolaIsland_hns/scripts.pory"
	specialvar VAR_RESULT, GetBattleOutcome
# 14 "data/maps/AlolaIsland_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_CAUGHT
	goto_if_eq Alola_Poni_BattleExeggutor_2
# 20 "data/maps/AlolaIsland_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq Alola_Poni_BattleExeggutor_3
# 27 "data/maps/AlolaIsland_hns/scripts.pory"
	release
	end

# 30 "data/maps/AlolaIsland_hns/scripts.pory"
	release
	end

Alola_Poni_BattleExeggutor_2:
# 15 "data/maps/AlolaIsland_hns/scripts.pory"
	setflag FLAG_CAUGHT_EXEGGUTOR_ALOLA
# 16 "data/maps/AlolaIsland_hns/scripts.pory"
	removeobject Alola_Poni_Exeggutor
# 17 "data/maps/AlolaIsland_hns/scripts.pory"
	release
	end

Alola_Poni_BattleExeggutor_3:
# 21 "data/maps/AlolaIsland_hns/scripts.pory"
	setflag FLAG_CAUGHT_EXEGGUTOR_ALOLA
# 22 "data/maps/AlolaIsland_hns/scripts.pory"
	removeobject Alola_Poni_Exeggutor
# 23 "data/maps/AlolaIsland_hns/scripts.pory"
	release
	end


Alola_Poni_Island_Sign::
# 35 "data/maps/AlolaIsland_hns/scripts.pory"
	lock
# 36 "data/maps/AlolaIsland_hns/scripts.pory"
	msgbox Alola_Poni_Island_Sign_Text_0
# 37 "data/maps/AlolaIsland_hns/scripts.pory"
	release
	end


Alola_Poni_BattleExeggutor_Text_0:
# 9 "data/maps/AlolaIsland_hns/scripts.pory"
	.string "Gaaah!$"

Alola_Poni_Island_Sign_Text_0:
# 36 "data/maps/AlolaIsland_hns/scripts.pory"
	.string "Poni Island$"
