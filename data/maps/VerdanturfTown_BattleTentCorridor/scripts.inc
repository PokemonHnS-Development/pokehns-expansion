VerdanturfTown_BattleTentCorridor_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, VerdanturfTown_BattleTentCorridor_OnFrame
	.byte 0

VerdanturfTown_BattleTentCorridor_OnFrame:
	map_script_2 VAR_TEMP_0, 0, VerdanturfTown_BattleTentCorridor_EventScript_EnterCorridor
	.2byte 0

VerdanturfTown_BattleTentCorridor_EventScript_EnterCorridor::
	lockall
	setvar VAR_TEMP_0, 1
	applymovement LOCALID_VERDANTURF_TENT_CORRIDOR_ATTENDANT, VerdanturfTown_BattleTentCorridor_Movement_WalkToDoor
	applymovement LOCALID_PLAYER, VerdanturfTown_BattleTentCorridor_Movement_WalkToDoor
	waitmovement 0
	opendoor 2, 1
	waitdooranim
	applymovement LOCALID_VERDANTURF_TENT_CORRIDOR_ATTENDANT, VerdanturfTown_BattleTentCorridor_Movement_AttendantEnterDoor
	applymovement LOCALID_PLAYER, VerdanturfTown_BattleTentCorridor_Movement_PlayerEnterDoor
	waitmovement 0
	closedoor 2, 1
	waitdooranim
	setvar VAR_0x8006, 0
	warp MAP_VERDANTURF_TOWN_BATTLE_TENT_BATTLE_ROOM, 6, 5
	waitstate
	releaseall
	end

VerdanturfTown_BattleTentCorridor_Movement_WalkToDoor:
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

VerdanturfTown_BattleTentCorridor_Movement_PlayerEnterDoor:
	walk_up
VerdanturfTown_BattleTentCorridor_Movement_AttendantEnterDoor:
	walk_up
	set_invisible
	step_end


@ Leftover text from when this was a Contest Hall in R/S
@ Unused
VerdanturfTown_ContestHall_Text_WhichContestYouEntering:
	.string "¿A qué CONCURSO entrarás?\n"
	.string "¿Quieres un consejo?\p"
	.string "En cualquier CONCURSO, por ejemplo,\n"
	.string "en el de BELLEZA, no creo que juzguen\l"
	.string "solo la belleza en la primera ronda.\p"
	.string "Debes buscar formas de mejorar a tus\n"
	.string "POKéMON.$"

@ Unused
VerdanturfTown_ContestHall_Text_RaisedMonToBeCute:
	.string "Crié a mi POKéMON para ser lindo.\p"
	.string "¡Descubrí que puedes inscribir a un\n"
	.string "POKéMON en el CONCURSO de BELLEZA!\p"
	.string "Me alegra haber criado a mi POKéMON\n"
	.string "con mucho cariño...$"

@ Unused
VerdanturfTown_ContestHall_Text_MyMonRules:
	.string "¡Mi POKéMON es el mejor!\p"
	.string "Es genial, fuerte pero hermoso, lindo,\n"
	.string "y listo. ¡Es perfecto!\p"
	.string "Podría ganar en cada uno de los\n"
	.string "CONCURSOS.$"

@ Unused
VerdanturfTown_ContestHall_Text_NormalRankStage:
	.string "CONCURSOS POKéMON\n"
	.string "¡ETAPA DE RANGO NORMAL!$"

