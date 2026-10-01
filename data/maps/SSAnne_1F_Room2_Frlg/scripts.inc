SSAnne_1F_Room2_Frlg_MapScripts::
	.byte 0

SSAnne_1F_Room2_EventScript_Woman::
	msgbox SSAnne_1F_Room2_Text_CruisingAroundWorld, MSGBOX_NPC
	end

SSAnne_1F_Room2_EventScript_Ann::
	trainerbattle_single TRAINER_LASS_ANN, SSAnne_1F_Room2_Text_AnnIntro, SSAnne_1F_Room2_Text_AnnDefeat
	msgbox SSAnne_1F_Room2_Text_AnnPostBattle, MSGBOX_AUTOCLOSE
	end

SSAnne_1F_Room2_EventScript_Tyler::
	trainerbattle_single TRAINER_YOUNGSTER_TYLER, SSAnne_1F_Room2_Text_TylerIntro, SSAnne_1F_Room2_Text_TylerDefeat
	msgbox SSAnne_1F_Room2_Text_TylerPostBattle, MSGBOX_AUTOCLOSE
	end

SSAnne_1F_Room2_Text_TylerIntro::
	.string "¡Amo a los POKéMON!\n"
	.string "¿Tú sí?$"

SSAnne_1F_Room2_Text_TylerDefeat::
	.string "¡Vaya! \n"
	.string "¡Eres genial!$"

SSAnne_1F_Room2_Text_TylerPostBattle::
	.string "¡Escucha, escucha!\n"
	.string "Sé mi amigo, ¿de acuerdo?\p"
	.string "Así podremos intercambiar POKéMON\n"
	.string "y hacer cosas.$"

SSAnne_1F_Room2_Text_AnnIntro::
	.string "Recogí estos POKéMON\n"
	.string "¡de todo el mundo!$"

SSAnne_1F_Room2_Text_AnnDefeat::
	.string "¡Oh, no!\n"
	.string "¡Di la vuelta al mundo por esto!$"

SSAnne_1F_Room2_Text_AnnPostBattle::
	.string "You hurt my poor POKéMON!\p"
	.string "Exijo que los cures en un\n"
	.string "POKéMON CENTER!$"

SSAnne_1F_Room2_Text_CruisingAroundWorld::
	.string "Estamos dando la vuelta al mundo,\n"
	.string "mis hijos y yo.$"

