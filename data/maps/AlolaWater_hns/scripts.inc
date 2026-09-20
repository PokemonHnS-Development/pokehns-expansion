AlolaWater_hns_MapScripts::
	.byte 0


Alola_MelemeleSea_TrainerBattleSwimmer::
	trainerbattle_single TRAINER_MELEMELE_SWIMMER_2_HNS, Alola_MelemeleSea_TrainerBattleSwimmer_Text_0, Alola_MelemeleSea_TrainerBattleSwimmer_Text_1
	msgbox Alola_MelemeleSea_TrainerBattleSwimmer_Text_2, MSGBOX_AUTOCLOSE
	release
	end


Alola_MelemeleSea_TrainerBattleSwimmer_Text_0:
	.string "¡Hay tanta agua abierta aquí!$"

Alola_MelemeleSea_TrainerBattleSwimmer_Text_1:
	.string "Ay,\nme lesioné el isquio…$"

Alola_MelemeleSea_TrainerBattleSwimmer_Text_2:
	.string "Hay corrientes fuertes aquí.\n"
	.string "¡Creo que atrae POKéMON fuertes!$"
