FiveIsland_LostCave_Room1_Frlg_MapScripts::
	.byte 0

FiveIsland_LostCave_Room1_EventScript_Lawson::
	trainerbattle_single TRAINER_RUIN_MANIAC_LAWSON, FiveIsland_LostCave_Room1_Text_LawsonIntro, FiveIsland_LostCave_Room1_Text_LawsonDefeat
	msgbox FiveIsland_LostCave_Room1_Text_LawsonPostBattle, MSGBOX_AUTOCLOSE
	end

FiveIsland_LostCave_Room1_Text_LawsonIntro::
	.string "Aiyeeeeeh!\p"
	.string "Pensé que era una ruina antigua.\n"
	.string "¡Pero está llena de fantasmas!$"

FiveIsland_LostCave_Room1_Text_LawsonDefeat::
	.string "Aiyeeeeeh!\n"
	.string "Mercy!$"

FiveIsland_LostCave_Room1_Text_LawsonPostBattle::
	.string "Intento salir de aquí, pero\n"
	.string "siempre acabo en el mismo lugar.\p"
	.string "Quizá la cantidad de rocas es\n"
	.string "una pista...$"

