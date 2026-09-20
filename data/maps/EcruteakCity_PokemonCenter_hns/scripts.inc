EcruteakCity_PokemonCenter_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, EcruteakCity_PokemonCenter_OnTransition
	.byte 0

EcruteakCity_PokemonCenter_OnTransition::
	setrespawn HEAL_LOCATION_ECRUTEAK_CITY_HNS
	end

EcruteakCity_PokemonCenter_EventScript_Bill::
	lock
	delay 30
	playse SE_PC_OFF
	delay 55
	faceplayer
	msgbox EcruteakCity_PokemonCenter1F_Text_Bill1, MSGBOX_DEFAULT
	msgbox EcruteakCity_PokemonCenter1F_Text_Bill2, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_FACING, DIR_NORTH, EcruteakCity_PokemonCenter_EventScript_BillLeaveBot
	call_if_eq VAR_FACING, DIR_WEST, EcruteakCity_PokemonCenter_EventScript_BillLeaveTop
	playse SE_EXIT
	setflag FLAG_HIDE_ECRUTEAK_BILL
	removeobject LOCALID_ECRUTEAK_BILL
	setflag FLAG_SYS_PC_BILL
	clearflag FLAG_HIDE_GOLDENROD_BILL
	release
	end

EcruteakCity_PokemonCenter_EventScript_BillFaceDown::
	turnobject LOCALID_ECRUTEAK_BILL, DIR_SOUTH
	return

EcruteakCity_PokemonCenter_EventScript_BillFaceRight::
	turnobject LOCALID_ECRUTEAK_BILL, DIR_EAST
	return

EcruteakCity_PokemonCenter_EventScript_BillLeaveTop::
	applymovement LOCALID_ECRUTEAK_BILL, EcruteakCity_PokemonCenter_Movement_BillTop
	waitmovement 0
	return

EcruteakCity_PokemonCenter_EventScript_BillLeaveBot::
	applymovement LOCALID_ECRUTEAK_BILL, EcruteakCity_PokemonCenter_Movement_BillBot
	waitmovement 0
	return

EcruteakCity_PokemonCenter_EventScript_Hiker::
	lock
	faceplayer
	msgbox EcruteakCity_PokemonCenter1F_Text_PokefanM, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_PokemonCenter_EventScript_Woman::
	lock
	faceplayer
	msgbox EcruteakCity_PokemonCenter1F_Text_CooltrainerF, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_PokemonCenter_EventScript_Nerd::
	lock
	faceplayer
	msgbox EcruteakCity_PokemonCenter1F_Text_GymGuide, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_PokemonCenter_Movement_BillTop:
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

EcruteakCity_PokemonCenter_Movement_BillBot:
	walk_right
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	step_end


EcruteakCity_PokemonCenter1F_Text_Bill1:
	.string "Hola, soy BILL. ¿Y tú quién eres?\p"
	.string "Hmm, {PLAYER}, ¿eh?\n"
	.string "Llegas en el momento justo.$"

EcruteakCity_PokemonCenter1F_Text_Bill2:
	.string "Acabo de terminar los ajustes de mi\n"
	.string "SISTEMA DE ALMACÉN POKéMON.\p"
	.string "Sabes que PC usas para guardar\n"
	.string "a todos tus POKéMON?\p"
	.string "¡Yo mismo lo desarrollé!\p"
	.string "Ahora que instalé este,\n"
	.string "mi PC funciona en todos los\l"
	.string "CENTROS POKéMON de JOHTO y KANTO.\p"
	.string "Tengo que volver rápido a\n"
	.string "CIUDAD TRIGAL y ver a mis padres. Feel\l"
	.string "puedes visitarlos cuando quieras!\p"
	.string "¡Adiós!$"

EcruteakCity_PokemonCenter1F_Text_PokefanM:
	.string "El baile de las KIMONO GIRLS es\n"
	.string "es maravillosa.\p"
	.string "Igual que la forma en que usan sus\n"
	.string "POKéMON.$"

EcruteakCity_PokemonCenter1F_Text_PokefanM_Mobile:
	.string "Seguro que quieres luchar contra más\n"
	.string "gente, ¿verdad?\p"
	.string "Al parecer hay un lugar donde se\n"
	.string "reúnen los ENTRENADORES.\p"
	.string "¿Que dónde?\p"
	.string "Está un poco después de CIUDAD OLIVO.$"

EcruteakCity_PokemonCenter1F_Text_CooltrainerF:
	.string "MORTY, el LÍDER del GIMNASIO, es\n"
	.string "genial.\p"
	.string "Sus POKéMON también son fuertes.$"

EcruteakCity_PokemonCenter1F_Text_GymGuide:
	.string "LAGO DE la FURIA…\p"
	.string "La aparición de un grupo de\n"
	.string "GYARADOS…\p"
	.string "Huelo una conspiración. ¡Lo sé!$"

