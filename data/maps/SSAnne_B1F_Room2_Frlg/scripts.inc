SSAnne_B1F_Room2_Frlg_MapScripts::
	.byte 0

SSAnne_B1F_Room2_EventScript_Huey::
	trainerbattle_single TRAINER_SAILOR_HUEY, SSAnne_B1F_Room2_Text_HueyIntro, SSAnne_B1F_Room2_Text_HueyDefeat
	msgbox SSAnne_B1F_Room2_Text_HueyPostBattle, MSGBOX_AUTOCLOSE
	end

SSAnne_B1F_Room2_Text_HueyIntro::
	.string "¡Hasta los marineros tenemos POKéMON!$"

SSAnne_B1F_Room2_Text_HueyDefeat::
	.string "Bien, no eres malo.$"

SSAnne_B1F_Room2_Text_HueyPostBattle::
	.string "Atrapamos a todos nuestros POKéMON\n"
	.string "mientras estábamos en alta mar.$"

