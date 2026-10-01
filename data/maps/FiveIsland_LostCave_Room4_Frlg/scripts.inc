FiveIsland_LostCave_Room4_Frlg_MapScripts::
	.byte 0

FiveIsland_LostCave_Room4_EventScript_Laura::
	trainerbattle_single TRAINER_PSYCHIC_LAURA, FiveIsland_LostCave_Room4_Text_LauraIntro, FiveIsland_LostCave_Room4_Text_LauraDefeat
	msgbox FiveIsland_LostCave_Room4_Text_LauraPostBattle, MSGBOX_AUTOCLOSE
	end

FiveIsland_LostCave_Room4_Text_LauraIntro::
	.string "Creo que hay un poder misterioso\n"
	.string "trabajando en esta cueva.$"

FiveIsland_LostCave_Room4_Text_LauraDefeat::
	.string "Si no entras por el túnel\n"
	.string "correcto, no avanzarás.$"

FiveIsland_LostCave_Room4_Text_LauraPostBattle::
	.string "Antes, una señora entró en las\n"
	.string "ahead.$"

