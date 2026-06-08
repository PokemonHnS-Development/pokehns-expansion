AlolaIslandRight_hns_MapScripts::
	.byte 0


Alola_Akala_BattleSandygast::
# 4 "data/maps/AlolaIslandRight_hns/scripts.pory"
	lock
# 5 "data/maps/AlolaIslandRight_hns/scripts.pory"
	faceplayer
# 6 "data/maps/AlolaIslandRight_hns/scripts.pory"
	playmoncry SPECIES_SANDYGAST, 0
# 7 "data/maps/AlolaIslandRight_hns/scripts.pory"
	msgbox Alola_Akala_BattleSandygast_Text_0, MSGBOX_AUTOCLOSE
# 8 "data/maps/AlolaIslandRight_hns/scripts.pory"
	waitmoncry
# 9 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setwildbattle SPECIES_SANDYGAST, 45
# 10 "data/maps/AlolaIslandRight_hns/scripts.pory"
	dowildbattle
# 11 "data/maps/AlolaIslandRight_hns/scripts.pory"
	specialvar VAR_RESULT, GetBattleOutcome
# 12 "data/maps/AlolaIslandRight_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_CAUGHT
	goto_if_eq Alola_Akala_BattleSandygast_2
# 18 "data/maps/AlolaIslandRight_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq Alola_Akala_BattleSandygast_3
# 25 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end

# 28 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end

Alola_Akala_BattleSandygast_2:
# 13 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setflag FLAG_CAUGHT_SANDYGAST2
# 14 "data/maps/AlolaIslandRight_hns/scripts.pory"
	removeobject Alola_Akala_Sandygast
# 15 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end

Alola_Akala_BattleSandygast_3:
# 19 "data/maps/AlolaIslandRight_hns/scripts.pory"
	setflag FLAG_CAUGHT_SANDYGAST2
# 20 "data/maps/AlolaIslandRight_hns/scripts.pory"
	removeobject Alola_Akala_Sandygast
# 21 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end


Alola_Akala_Island_FindItem1::
# 33 "data/maps/AlolaIslandRight_hns/scripts.pory"
	finditem ITEM_POTION, 1
	end


Alola_Akala_Island_FindItem2::
# 38 "data/maps/AlolaIslandRight_hns/scripts.pory"
	finditem ITEM_ANTIDOTE, 1
	end


Alola_Akala_Island_Finditem3::
# 43 "data/maps/AlolaIslandRight_hns/scripts.pory"
	finditem ITEM_ORAN_BERRY, 1
	end


Alola_Akala_Sign::
# 48 "data/maps/AlolaIslandRight_hns/scripts.pory"
	lock
# 49 "data/maps/AlolaIslandRight_hns/scripts.pory"
	msgbox Alola_Akala_Sign_Text_0
# 50 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end


Alola_Akala_House_Sign::
# 55 "data/maps/AlolaIslandRight_hns/scripts.pory"
	lock
# 56 "data/maps/AlolaIslandRight_hns/scripts.pory"
	msgbox Alola_Akala_House_Sign_Text_0
# 57 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end


Alola_Akala_Pikipek::
# 62 "data/maps/AlolaIslandRight_hns/scripts.pory"
	lock
# 63 "data/maps/AlolaIslandRight_hns/scripts.pory"
	faceplayer
# 64 "data/maps/AlolaIslandRight_hns/scripts.pory"
	playmoncry SPECIES_PIKIPEK, 0
# 65 "data/maps/AlolaIslandRight_hns/scripts.pory"
	msgbox Alola_Akala_Pikipek_Text_0, MSGBOX_AUTOCLOSE
# 66 "data/maps/AlolaIslandRight_hns/scripts.pory"
	waitmoncry
# 67 "data/maps/AlolaIslandRight_hns/scripts.pory"
	release
	end


Alola_Akala_BattleSandygast_Text_0:
# 7 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "Gaaah!$"

Alola_Akala_Sign_Text_0:
# 49 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "Akala Island$"

Alola_Akala_House_Sign_Text_0:
# 56 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "???'s House$"

Alola_Akala_Pikipek_Text_0:
# 65 "data/maps/AlolaIslandRight_hns/scripts.pory"
	.string "Pek!$"
