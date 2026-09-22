SevenIsland_TrainerTower_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SevenIsland_TrainerTower_OnTransition
	.byte 0

SevenIsland_TrainerTower_OnTransition::
	setvar VAR_MAP_SCENE_TRAINER_TOWER, 0
	end

SevenIsland_TrainerTower_EventScript_TrainerTowerSign::
	msgbox SevenIsland_TrainerTower_Text_TrainerTowerSign, MSGBOX_SIGN
	end

SevenIsland_TrainerTower_EventScript_TrainerTowerAheadSign::
	msgbox SevenIsland_TrainerTower_Text_TrainerTowerAhead, MSGBOX_SIGN
	end

SevenIsland_TrainerTower_Text_DarioIntro::
	.string "Sentí que te acercabas.$"

SevenIsland_TrainerTower_Text_DarioDefeat::
	.string "Ríndete...$"

SevenIsland_TrainerTower_Text_DarioPostBattle::
	.string "En tu futuro, veo que conocerás\n"
	.string "a muchas otras personas.\p"
	.string "Creo que estarán unidos entre\n"
	.string "sí por un poder extraño.$"

SevenIsland_TrainerTower_Text_RodetteIntro::
	.string "En algún lugar de esta isla, hay\n"
	.string "POKéMON peculiares durmiendo.$"

SevenIsland_TrainerTower_Text_RodetteDefeat::
	.string "¡Qué ENTRENADOR tan increíble!$"

SevenIsland_TrainerTower_Text_RodettePostBattle::
	.string "En algún lugar de esta isla, hay\n"
	.string "POKéMON are sleeping.\p"
	.string "¿Será que están esperando\n"
	.string "a ti?$"

SevenIsland_TrainerTower_Text_TrainerTowerSign::
	.string "TRAINER TOWER ENTRANCE\n"
	.string "Rise to the Challenge, TRAINERS!$"

SevenIsland_TrainerTower_Text_TrainerTowerAhead::
	.string "TRAINER TOWER AHEAD$"

