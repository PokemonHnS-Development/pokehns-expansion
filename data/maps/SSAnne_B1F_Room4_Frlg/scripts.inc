SSAnne_B1F_Room4_Frlg_MapScripts::
	.byte 0

SSAnne_B1F_Room4_EventScript_Leonard::
	trainerbattle_single TRAINER_SAILOR_LEONARD, SSAnne_B1F_Room4_Text_LeonardIntro, SSAnne_B1F_Room4_Text_LeonardDefeat
	msgbox SSAnne_B1F_Room4_Text_LeonardPostBattle, MSGBOX_AUTOCLOSE
	end

SSAnne_B1F_Room4_EventScript_Duncan::
	trainerbattle_single TRAINER_SAILOR_DUNCAN, SSAnne_B1F_Room4_Text_DuncanIntro, SSAnne_B1F_Room4_Text_DuncanDefeat
	msgbox SSAnne_B1F_Room4_Text_DuncanPostBattle, MSGBOX_AUTOCLOSE
	end

SSAnne_B1F_Room4_Text_LeonardIntro::
	.string "Ya sabes lo que dicen sobre\n"
	.string "los marineros y las batallas!$"

SSAnne_B1F_Room4_Text_LeonardDefeat::
	.string "Right!\n"
	.string "Good battle, mate!$"

SSAnne_B1F_Room4_Text_LeonardPostBattle::
	.string "¡Jajaja!\n"
	.string "¿Quieres ser marinero, amigo?$"

SSAnne_B1F_Room4_Text_DuncanIntro::
	.string "¡Vamos, entonces!\n"
	.string "My sailor's pride is at stake!$"

SSAnne_B1F_Room4_Text_DuncanDefeat::
	.string "¡Tu espíritu me hundió!$"

SSAnne_B1F_Room4_Text_DuncanPostBattle::
	.string "¿Viste al GURÚ PESCADOR en\n"
	.string "VERMILION CITY?$"

