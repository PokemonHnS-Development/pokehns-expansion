AlolaWater_hns_MapScripts::
	.byte 0


Alola_MelemeleSea_TrainerBattleSwimmer::
	trainerbattle_single TRAINER_MELEMELE_SWIMMER_2_HNS, Alola_MelemeleSea_TrainerBattleSwimmer_Text_0, Alola_MelemeleSea_TrainerBattleSwimmer_Text_1
	msgbox Alola_MelemeleSea_TrainerBattleSwimmer_Text_2, MSGBOX_AUTOCLOSE
	release
	end


Alola_MelemeleSea_TrainerBattleSwimmer_Text_0:
	.string "So much open water here!$"

Alola_MelemeleSea_TrainerBattleSwimmer_Text_1:
	.string "Ouch,\npulled a hamstring…$"

Alola_MelemeleSea_TrainerBattleSwimmer_Text_2:
	.string "There are some strong currents here.\n"
	.string "I think it attracts strong Pokémon!$"
