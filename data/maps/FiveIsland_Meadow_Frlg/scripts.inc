FiveIsland_Meadow_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, FiveIsland_Meadow_OnLoad
	.byte 0

FiveIsland_Meadow_OnLoad::
	call_if_set FLAG_UNLOCKED_ROCKET_WAREHOUSE, FiveIsland_Meadow_EventScript_SetWarehouseDoorUnlocked
	end

FiveIsland_Meadow_EventScript_WarehouseDoor::
	lockall
	goto_if_set FLAG_UNLOCKED_ROCKET_WAREHOUSE, FiveIsland_Meadow_EventScript_WarehouseDoorAlreadyOpen
	goto_if_set FLAG_LEARNED_YES_NAH_CHANSEY, FiveIsland_Meadow_EventScript_OpenWarehouseDoor
	msgbox FiveIsland_Meadow_Text_EnteredPasswordAnotherNeeded
	releaseall
	end

FiveIsland_Meadow_EventScript_OpenWarehouseDoor::
	setflag FLAG_UNLOCKED_ROCKET_WAREHOUSE
	message FiveIsland_Meadow_Text_EnteredPasswordDoorOpened
	waitmessage
	delay 60
	call FiveIsland_Meadow_EventScript_SetWarehouseDoorUnlocked
	special DrawWholeMapView
	playse SE_PIN
	waitse
	releaseall
	end

FiveIsland_Meadow_EventScript_WarehouseDoorAlreadyOpen::
	msgbox FiveIsland_Meadow_Text_WarehouseDoorAlreadyOpen
	releaseall
	end

FiveIsland_Meadow_EventScript_SetWarehouseDoorUnlocked::
	setmetatile 12, 21, METATILE_SeviiIslands45_RocketWarehouseDoor_Unlocked, 1
	return

FiveIsland_Meadow_EventScript_Rocket1::
	trainerbattle_single TRAINER_TEAM_ROCKET_GRUNT_49, FiveIsland_Meadow_Text_Rocket1Intro, FiveIsland_Meadow_Text_Rocket1Defeat
	msgbox FiveIsland_Meadow_Text_Rocket1PostBattle, MSGBOX_AUTOCLOSE
	end

FiveIsland_Meadow_EventScript_Rocket2::
	trainerbattle_single TRAINER_TEAM_ROCKET_GRUNT_50, FiveIsland_Meadow_Text_Rocket2Intro, FiveIsland_Meadow_Text_Rocket2Defeat
	msgbox FiveIsland_Meadow_Text_Rocket2PostBattle, MSGBOX_AUTOCLOSE
	end

FiveIsland_Meadow_EventScript_Rocket3::
	trainerbattle_single TRAINER_TEAM_ROCKET_GRUNT_51, FiveIsland_Meadow_Text_Rocket3Intro, FiveIsland_Meadow_Text_Rocket3Defeat
	msgbox FiveIsland_Meadow_Text_Rocket3PostBattle, MSGBOX_AUTOCLOSE
	end

@ Unused
FiveIsland_Meadow_Text_DoorNeedsTwoPasswords::
	.string "とびらを　あけるには\n"
	.string "パスワードが　2つ　いるようだ$"

FiveIsland_Meadow_Text_EnteredPasswordAnotherNeeded::
	.string "{PLAYER} ingresó una contraseña.\p"
	.string "“GOLDEEN necesita tronco.”\p"
	.string "... ...  ... ...  ... ...\p"
	.string "Se necesita otra contraseña\n"
	.string "para abrir la puerta...$"

FiveIsland_Meadow_Text_EnteredPasswordDoorOpened::
	.string "{PLAYER} ingresó dos contraseñas.\p"
	.string "“GOLDEEN necesita tronco.”\n"
	.string "“Sí, claro, CHANSEY.“\p"
	.string "... ...  ... ...  ... ...\p"
	.string "¡La puerta del ALMACÉN se abrió!$"

FiveIsland_Meadow_Text_WarehouseDoorAlreadyOpen::
	.string "La puerta del ALMACÉN ya\n"
	.string "abierta.$"

FiveIsland_Meadow_Text_Rocket1Intro::
	.string "¡Esta zona es de acceso prohibido!\n"
	.string "¡Fuera, fuera!$"

FiveIsland_Meadow_Text_Rocket1Defeat::
	.string "¿Es en serio?$"

FiveIsland_Meadow_Text_Rocket1PostBattle::
	.string "¡No tienes nada que hacer aquí!\n"
	.string "¡Vete a casa!$"

FiveIsland_Meadow_Text_Rocket2Intro::
	.string "Más adelante solo está\n"
	.string "nuestro ALMACÉN.\p"
	.string "¿Y qué te trae por aquí?$"

FiveIsland_Meadow_Text_Rocket2Defeat::
	.string "Eso no debía pasar...$"

FiveIsland_Meadow_Text_Rocket2PostBattle::
	.string "¿Quieres saber qué hay dentro\n"
	.string "de este ALMACÉN?\p"
	.string "Mejor que no lo sepas.\n"
	.string "Por tu propio bien, digo.$"

FiveIsland_Meadow_Text_Rocket3Intro::
	.string "Perderías el tiempo aunque\n"
	.string "lograras pasarme.$"

FiveIsland_Meadow_Text_Rocket3Defeat::
	.string "¡Oh, eso me enfurece!$"

FiveIsland_Meadow_Text_Rocket3PostBattle::
	.string "No podrás entrar sin las\n"
	.string "contraseñas de todos modos.$"

