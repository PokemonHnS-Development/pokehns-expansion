VerdanturfTown_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, VerdanturfTown_OnTransition
	.byte 0

VerdanturfTown_OnTransition:
	setflag FLAG_VISITED_VERDANTURF_TOWN
	setvar VAR_CONTEST_HALL_STATE, 0
	end

VerdanturfTown_EventScript_Twin::
	lock
	faceplayer
	goto_if_set FLAG_RUSTURF_TUNNEL_OPENED, VerdanturfTown_EventScript_TwinTunnelOpen
	msgbox VerdanturfTown_Text_ManTryingToDigTunnel, MSGBOX_DEFAULT
	applymovement LOCALID_VERDANTURF_TWIN, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

VerdanturfTown_EventScript_TwinTunnelOpen::
	msgbox VerdanturfTown_Text_ManDugTunnelForLove, MSGBOX_DEFAULT
	applymovement LOCALID_VERDANTURF_TWIN, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

VerdanturfTown_EventScript_Man::
	msgbox VerdanturfTown_Text_AirCleanHere, MSGBOX_NPC
	end

VerdanturfTown_EventScript_Camper::
	msgbox VerdanturfTown_Text_MakeBattleTentDebut, MSGBOX_NPC
	end

VerdanturfTown_EventScript_Boy::
	lock
	faceplayer
	goto_if_set FLAG_RUSTURF_TUNNEL_OPENED, VerdanturfTown_EventScript_BoyTunnelOpen
	msgbox VerdanturfTown_Text_GuyTryingToBustThroughCave, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_EventScript_BoyTunnelOpen::
	msgbox VerdanturfTown_Text_EasyToGetToRustboroNow, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_EventScript_TownSign::
	msgbox VerdanturfTown_Text_TownSign, MSGBOX_SIGN
	end

VerdanturfTown_EventScript_WandasHouseSign::
	msgbox VerdanturfTown_Text_WandasHouse, MSGBOX_SIGN
	end

VerdanturfTown_EventScript_BattleTentSign::
	msgbox VerdanturfTown_Text_BattleTentSign, MSGBOX_SIGN
	end

VerdanturfTown_EventScript_RusturfTunnelSign::
	msgbox VerdanturfTown_Text_RusturfTunnelSign, MSGBOX_SIGN
	end

VerdanturfTown_Text_ManTryingToDigTunnel:
	.string "Mi papá me lo contó.\p"
	.string "Dice que este túnel está lleno de\n"
	.string "POKéMON tímidos.\p"
	.string "Se asustan con los ruidos fuertes y\n"
	.string "arman un gran alboroto.\p"
	.string "Por eso tuvieron que detener el\n"
	.string "proyecto del túnel.\p"
	.string "¡Pero hay un hombre que intenta cavar\n"
	.string "el túnel él solo!$"

VerdanturfTown_Text_ManDugTunnelForLove:
	.string "Hubo un hombre que cavó un túnel por\n"
	.string "una mujer que amaba.\p"
	.string "No lo entiendo bien, ¡pero bueno!$"

VerdanturfTown_Text_AirCleanHere:
	.string "Por cómo soplan los vientos, la ceniza\n"
	.string "volcánica nunca llega hacia aquí.\p"
	.string "El aire es puro y delicioso aquí.\n"
	.string "Vivir aquí haría maravillas incluso\l"
	.string "para gente débil y enfermiza.$"

VerdanturfTown_Text_MakeBattleTentDebut:
	.string "Mis POKéMON y yo llevamos una racha\n"
	.string "de victorias increíble.\p"
	.string "Así que decidí debutar con mi\n"
	.string "BATTLE TENT en este pueblo.$"

VerdanturfTown_Text_GuyTryingToBustThroughCave:
	.string "¿Viste la cueva que está junto al\n"
	.string "POKéMON MART?\p"
	.string "Hay un tipo ahí que está intentando\n"
	.string "rompe rocas para que pueda salir\l"
	.string "hacia el otro lado.\p"
	.string "Sería genial si pudiéramos pasar...\n"
	.string "Será fácil visitar RUSTBORO.$"

VerdanturfTown_Text_EasyToGetToRustboroNow:
	.string "La cueva junto al POKéMON MART\n"
	.string "ahora es un túnel al otro lado.\p"
	.string "Es genial, ahora es fácil comprar\n"
	.string "productos DEVON en RUSTBORO.$"

VerdanturfTown_Text_TownSign:
	.string "PUEBLO VERDANTURF\p"
	.string "Tierras altas azotadas por el viento\n"
	.string "con dulce fragancia a hierba.$"

VerdanturfTown_Text_WandasHouse:
	.string "CASA DE WANDA$"

VerdanturfTown_Text_BattleTentSign:
	.string "TIENDA BATALLA CAMPO VERDE\n"
	.string "¡Mira estas batallas!$"

VerdanturfTown_Text_RusturfTunnelSign:
	.string "TÚNEL RUSTURF\n"
	.string "“Uniendo FUNDA y VERDANTURF,\p"
	.string "“el proyecto del túnel ha sido\n"
	.string "cancelado.”$"

