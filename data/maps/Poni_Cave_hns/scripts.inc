Poni_Cave_hns_MapScripts::
	.byte 0

Alola_Poni_BattleGolem::
	lock
	faceplayer
	setflag FLAG_BATTLED_GOLEM
	playmoncry SPECIES_GOLEM_ALOLA, 0
	msgbox Alola_Poni_BattleGolem_Text_0, MSGBOX_AUTOCLOSE
	waitmoncry
	setwildbattle SPECIES_GOLEM_ALOLA, 45
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	compare VAR_RESULT, B_OUTCOME_CAUGHT
	goto_if_eq Alola_Poni_BattleGolem_2
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq Alola_Poni_BattleGolem_3
	release
	end

	release
	end

Alola_Poni_BattleGolem_2:
	setflag FLAG_HIDE_GOLEM_ALOLA
	removeobject Alola_Poni_Golem
	release
	end

Alola_Poni_BattleGolem_3:
	setflag FLAG_HIDE_GOLEM_ALOLA
	removeobject Alola_Poni_Golem
	release
	end


Alola_Poni_Cave_FindItem1::
	finditem ITEM_LEAF_STONE, 1
	end


Alola_Poni_Cave_FindItem2::
	finditem ITEM_THUNDER_STONE, 1
	end


Alola_Poni_BattleGolem_Text_0:
	.string "Gaaah!$"
