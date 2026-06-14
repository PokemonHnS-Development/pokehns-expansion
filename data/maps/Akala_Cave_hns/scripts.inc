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
	msgbox Alola_Melemele_BattleDugtrio_Text_0, MSGBOX_AUTOCLOSE
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
	finditem ITEM_CARBOS, 1
	end


Alola_Akala_Cave_FindItem2::
# 70 "data/maps/Akala_Cave_hns/scripts.pory"
	finditem ITEM_HP_UP, 1
	end


Alola_AkalaCave_TrainerBattleHiker::
# 75 "data/maps/Akala_Cave_hns/scripts.pory"
	trainerbattle_single TRAINER_AKALA_CAVE_HIKER_HNS, Alola_AkalaCave_TrainerBattleHiker_Text_0, Alola_AkalaCave_TrainerBattleHiker_Text_1
# 76 "data/maps/Akala_Cave_hns/scripts.pory"
	msgbox Alola_AkalaCave_TrainerBattleHiker_Text_2, MSGBOX_AUTOCLOSE
# 81 "data/maps/Akala_Cave_hns/scripts.pory"
	release
	end


Alola_AkalaCave_TrainerBattlePicnicker::
# 86 "data/maps/Akala_Cave_hns/scripts.pory"
	trainerbattle_single TRAINER_AKALA_CAVE_PICNICKER_HNS, Alola_AkalaCave_TrainerBattlePicnicker_Text_0, Alola_AkalaCave_TrainerBattlePicnicker_Text_1
# 87 "data/maps/Akala_Cave_hns/scripts.pory"
	msgbox Alola_AkalaCave_TrainerBattlePicnicker_Text_2, MSGBOX_AUTOCLOSE
# 89 "data/maps/Akala_Cave_hns/scripts.pory"
	release
	end


Alola_AkalaCave_TrainerBattleCamper::
# 94 "data/maps/Akala_Cave_hns/scripts.pory"
	trainerbattle_single TRAINER_AKALA_CAVE_CAMPER_HNS, Alola_AkalaCave_TrainerBattleCamper_Text_0, Alola_AkalaCave_TrainerBattleCamper_Text_1
# 95 "data/maps/Akala_Cave_hns/scripts.pory"
	msgbox Alola_AkalaCave_TrainerBattleCamper_Text_2, MSGBOX_AUTOCLOSE
# 96 "data/maps/Akala_Cave_hns/scripts.pory"
	release
	end


Alola_Melemele_BattleMarowak_Text_0:
# 8 "data/maps/Akala_Cave_hns/scripts.pory"
	.string "Raah!$"

Alola_Melemele_BattleDugtrio_Text_0:
# 38 "data/maps/Akala_Cave_hns/scripts.pory"
	.string "Cha-Cha!$"

Alola_AkalaCave_TrainerBattleHiker_Text_0:
# 75 "data/maps/Akala_Cave_hns/scripts.pory"
	.string "You must be tough if you made it all the\nway up here!$"

Alola_AkalaCave_TrainerBattleHiker_Text_1:
# 75 "data/maps/Akala_Cave_hns/scripts.pory"
	.string "Tougher than me!$"

Alola_AkalaCave_TrainerBattleHiker_Text_2:
# 76 "data/maps/Akala_Cave_hns/scripts.pory"
	.string "I had to stop climbing because it was\n"
	.string "getting far too hot.\p"
	.string "It's like someone's got a fire going\n"
	.string "up on the peak…$"

Alola_AkalaCave_TrainerBattlePicnicker_Text_0:
# 86 "data/maps/Akala_Cave_hns/scripts.pory"
	.string "I'm tired from all this walking,\nlet's have a battle!$"

Alola_AkalaCave_TrainerBattlePicnicker_Text_1:
# 86 "data/maps/Akala_Cave_hns/scripts.pory"
	.string "Well that was refreshing!$"

Alola_AkalaCave_TrainerBattlePicnicker_Text_2:
# 87 "data/maps/Akala_Cave_hns/scripts.pory"
	.string "I'm usually not this tired but\n"
	.string "the heat in this cave is exhausting!$"

Alola_AkalaCave_TrainerBattleCamper_Text_0:
# 94 "data/maps/Akala_Cave_hns/scripts.pory"
	.string "Check me out!\nI caught some strong Pokémon!$"

Alola_AkalaCave_TrainerBattleCamper_Text_1:
# 94 "data/maps/Akala_Cave_hns/scripts.pory"
	.string "Not bad,\nbut not good enough!$"

Alola_AkalaCave_TrainerBattleCamper_Text_2:
# 95 "data/maps/Akala_Cave_hns/scripts.pory"
	.string "Is it warm in here or is it just me?$"
