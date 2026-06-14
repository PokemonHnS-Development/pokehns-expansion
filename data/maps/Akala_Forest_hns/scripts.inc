Akala_Forest_hns_MapScripts::
	.byte 0


Alola_Akala_Forest_FindItem1::
# 4 "data/maps/Akala_Forest_hns/scripts.pory"
	finditem ITEM_FULL_RESTORE, 1
	end


Alola_Akala_Forest_FindItem2::
# 9 "data/maps/Akala_Forest_hns/scripts.pory"
	finditem ITEM_PP_UP, 1
	end


Alola_AkalaForest_TrainerBattleBugCatcher1::
# 14 "data/maps/Akala_Forest_hns/scripts.pory"
	trainerbattle_single TRAINER_AKALA_FOREST_BUGCATCHER_1_HNS, Alola_AkalaForest_TrainerBattleBugCatcher1_Text_0, Alola_AkalaForest_TrainerBattleBugCatcher1_Text_1
# 15 "data/maps/Akala_Forest_hns/scripts.pory"
	msgbox Alola_AkalaForest_TrainerBattleBugCatcher1_Text_2, MSGBOX_AUTOCLOSE
# 18 "data/maps/Akala_Forest_hns/scripts.pory"
	release
	end


Alola_AkalaForest_TrainerBattleBugCatcher2::
# 23 "data/maps/Akala_Forest_hns/scripts.pory"
	trainerbattle_single TRAINER_AKALA_FOREST_BUGCATCHER_2_HNS, Alola_AkalaForest_TrainerBattleBugCatcher2_Text_0, Alola_AkalaForest_TrainerBattleBugCatcher2_Text_1
# 24 "data/maps/Akala_Forest_hns/scripts.pory"
	msgbox Alola_AkalaForest_TrainerBattleBugCatcher2_Text_2, MSGBOX_AUTOCLOSE
# 29 "data/maps/Akala_Forest_hns/scripts.pory"
	release
	end


Alola_AkalaForest_TrainerBattleBugCatcher1_Text_0:
# 14 "data/maps/Akala_Forest_hns/scripts.pory"
	.string "Look at all the cool bugs here on the \nIsles!$"

Alola_AkalaForest_TrainerBattleBugCatcher1_Text_1:
# 14 "data/maps/Akala_Forest_hns/scripts.pory"
	.string "Ouch, that stung!$"

Alola_AkalaForest_TrainerBattleBugCatcher1_Text_2:
# 15 "data/maps/Akala_Forest_hns/scripts.pory"
	.string "The Isles are far away from other land,\n"
	.string "so Bug-type Pokémon here must have\l"
	.string "adapted to the environment.$"

Alola_AkalaForest_TrainerBattleBugCatcher2_Text_0:
# 23 "data/maps/Akala_Forest_hns/scripts.pory"
	.string "Look at what I caught!$"

Alola_AkalaForest_TrainerBattleBugCatcher2_Text_1:
# 23 "data/maps/Akala_Forest_hns/scripts.pory"
	.string "Awh, that bites!$"

Alola_AkalaForest_TrainerBattleBugCatcher2_Text_2:
# 24 "data/maps/Akala_Forest_hns/scripts.pory"
	.string "The climate is a bit different on the\n"
	.string "Alola Isles…\p"
	.string "I'm sure that's why there are some\n"
	.string "unique Bug-type Pokémon here.$"
