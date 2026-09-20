Route41_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route41_MapScript_OnTransition
	.byte 0

Route41_MapScript_OnTransition::
	goto_if_eq VAR_COMPLETED_LUGIA, 4, Route41_MapScript_DoNothing
	goto_if_ge VAR_OLIVINE_CITY_STATE, 5, OlivineCity_MapScript_ClearWeather
	end

Route41_MapScript_DoNothing::
	end

Route41_EventScript_Charlie::
	trainerbattle_single TRAINER_CHARLIE_HNS, Route41_Text_SwimmermCharlieSeen, Route41_Text_SwimmermCharlieBeaten
	msgbox Route41_Text_SwimmermCharlieAfter, MSGBOX_AUTOCLOSE
	end

Route41_Text_SwimmermCharlieSeen:
	.string "El agua está tibia aquí.\n"
	.string "Estoy ágil y flexible.\p"
	.string "¡Claro, pelearé contigo!$"

Route41_Text_SwimmermCharlieBeaten:
	.string "Yikes! I've got prune skin!$"

Route41_Text_SwimmermCharlieAfter:
	.string "¿No es relajante flotar\n"
	.string "así?$"

Route41_EventScript_George::
	trainerbattle_single TRAINER_GEORGE_HNS, Route41_Text_SwimmermGeorgeSeen, Route41_Text_SwimmermGeorgeBeaten
	msgbox Route41_Text_SwimmermGeorgeAfter, MSGBOX_AUTOCLOSE
	end

Route41_Text_SwimmermGeorgeSeen:
	.string "Estoy un poco cansado.\n"
	.string "Si gano, préstame tu POKéMON.$"

Route41_Text_SwimmermGeorgeBeaten:
	.string "Pant, pant…$"

Route41_Text_SwimmermGeorgeAfter:
	.string "CIUDAD ORQUIDEA está muy lejos.\p"
	.string "Pero volver a CIUDAD OLIVO\n"
	.string "tampoco es fácil.\p"
	.string "¿Qué debo hacer?$"

Route41_EventScript_Berke::
	trainerbattle_single TRAINER_BERKE_HNS, Route41_Text_SwimmermBerkeSeen, Route41_Text_SwimmermBerkeBeaten
	msgbox Route41_Text_SwimmermBerkeAfter, MSGBOX_AUTOCLOSE
	end

Route41_Text_SwimmermBerkeSeen:
	.string "¿Ves esas islas que están\n"
	.string "bloqueadas por remolinos?\p"
	.string "¡Seguro que hay un secreto!$"

Route41_Text_SwimmermBerkeBeaten:
	.string "¿Cuál es el secreto de tu\n"
	.string "fuerza?$"

Route41_Text_SwimmermBerkeAfter:
	.string "Era una noche oscura y tormentosa...\p"
	.string "Vi a un POKéMON gigante volando\n"
	.string "desde las islas.\p"
	.string "Soltaba plumas de sus\n"
	.string "alas plateadas.$"

Route41_EventScript_Kirk::
	trainerbattle_single TRAINER_KIRK_HNS, Route41_Text_SwimmermKirkSeen, Route41_Text_SwimmermKirkBeaten
	msgbox Route41_Text_SwimmermKirkAfter, MSGBOX_AUTOCLOSE
	end

Route41_Text_SwimmermKirkSeen:
	.string "Las olas son fuertes aquí.\p"
	.string "Te agotan mientras\n"
	.string "puedes nadar.$"

Route41_Text_SwimmermKirkBeaten:
	.string "I'm beat!$"

Route41_Text_SwimmermKirkAfter:
	.string "Las corrientes no me dejan\n"
	.string "llegar a esa isla.$"

Route41_EventScript_Mathew::
	trainerbattle_single TRAINER_MATHEW_HNS, Route41_Text_SwimmermMathewSeen, Route41_Text_SwimmermMathewBeaten
	msgbox Route41_Text_SwimmermMathewAfter, MSGBOX_AUTOCLOSE
	end

Route41_Text_SwimmermMathewSeen:
	.string "¿Buscas los secretos\n"
	.string "de las ISLAS REMOLINO?$"

Route41_Text_SwimmermMathewBeaten:
	.string "Ooh, you've got great endurance!$"

Route41_Text_SwimmermMathewAfter:
	.string "Un secreto de ISLAS REMOLINO...\p"
	.string "¡Está oscuro como la noche!$"

Route41_EventScript_Kaylee::
	trainerbattle_single TRAINER_KAYLEE_HNS, Route41_Text_SwimmerfKayleeSeen, Route41_Text_SwimmerfKayleeBeaten
	msgbox Route41_Text_SwimmerfKayleeAfter, MSGBOX_AUTOCLOSE
	end

Route41_Text_SwimmerfKayleeSeen:
	.string "Voy camino a ISLAS REMOLINO.\p"
	.string "Iré a explorar con amigos.$"

Route41_Text_SwimmerfKayleeBeaten:
	.string "¿Así se hace?$"

Route41_Text_SwimmerfKayleeAfter:
	.string "Se supone que hay un gran\n"
	.string "POKéMON bajo LAS ISLAS REMOLINO.\p"
	.string "¿Me pregunto cuál será?$"

Route41_EventScript_Susie::
	trainerbattle_single TRAINER_SUSIE_HNS, Route41_Text_SwimmerfSusieSeen, Route41_Text_SwimmerfSusieBeaten
	msgbox Route41_Text_SwimmerfSusieAfter, MSGBOX_AUTOCLOSE
	end

Route41_Text_SwimmerfSusieSeen:
	.string "Te ves muy elegante\n"
	.string "montando tu POKéMON.$"

Route41_Text_SwimmerfSusieBeaten:
	.string "I'm crushed…$"

Route41_Text_SwimmerfSusieAfter:
	.string "¿No había una canción famosa\n"
	.string "sobre un chico en un LAPRAS?$"

Route41_EventScript_Denise::
	trainerbattle_single TRAINER_DENISE_HNS, Route41_Text_SwimmerfDeniseSeen, Route41_Text_SwimmerfDeniseBeaten
	msgbox Route41_Text_SwimmerfDeniseAfter, MSGBOX_AUTOCLOSE
	end

Route41_Text_SwimmerfDeniseSeen:
	.string "¡El clima es tan hermoso\n"
	.string "que estoy distraído!$"

Route41_Text_SwimmerfDeniseBeaten:
	.string "Ohhh!$"

Route41_Text_SwimmerfDeniseAfter:
	.string "Las quemaduras son malísimas.\p"
	.string "Pero no uso protector solar.\p"
	.string "No contaminaré el agua.$"

Route41_EventScript_Kara::
	trainerbattle_single TRAINER_KARA_HNS, Route41_Text_SwimmerfKaraSeen, Route41_Text_SwimmerfKaraBeaten
	msgbox Route41_Text_SwimmerfKaraAfter, MSGBOX_AUTOCLOSE
	end

Route41_Text_SwimmerfKaraSeen:
	.string "Si necesitas descansar,\n"
	.string "solo flota en el agua.\p"
	.string "Recuperarás el aliento,\n"
	.string "así podrás seguir con fuerza.$"

Route41_Text_SwimmerfKaraBeaten:
	.string "¡Oh! Tienes más energía que yo.$"

Route41_Text_SwimmerfKaraAfter:
	.string "Oí rugidos desde lo profundo\n"
	.string "de las ISLAS.$"

Route41_EventScript_Wendy::
	trainerbattle_single TRAINER_WENDY_HNS, Route41_Text_SwimmerfWendySeen, Route41_Text_SwimmerfWendyBeaten
	msgbox Route41_Text_SwimmerfWendyAfter, MSGBOX_AUTOCLOSE
	end

Route41_Text_SwimmerfWendySeen:
	.string "De noche, STARYU se juntan\n"
	.string "cerca de la superficie.$"

Route41_Text_SwimmerfWendyBeaten:
	.string "Oh, dear…$"

Route41_Text_SwimmerfWendyAfter:
	.string "Los grupos de STARYU se iluminan\n"
	.string "al mismo tiempo.\p"
	.string "Es tan bello que asusta.$"

Route41_EventScript_Tentacruel1::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_TENTACRUEL, CRY_MODE_NORMAL
	goto_if_ge VAR_TEMP_0, 2, Route41_EventScript_TentacruelAttack1
	msgbox Route41_Text_Tentacruel, MSGBOX_DEFAULT
	waitmoncry
	addvar VAR_TEMP_0, 1
	release
	end
Route41_EventScript_TentacruelAttack1::
	msgbox Route41_Text_TentacruelAttack, MSGBOX_DEFAULT
	waitmessage
	setflag FLAG_NO_WILD_CATCHING
	setflag FLAG_NO_SHINY
	setwildbattle SPECIES_TENTACRUEL, 100, ITEM_NONE
	dowildbattle
	closemessage
	clearflag FLAG_NO_WILD_CATCHING
	clearflag FLAG_NO_SHINY
	playse SE_USE_ITEM
	msgbox Route41_Text_TentacruelHeal, MSGBOX_DEFAULT
	setvar VAR_TEMP_0, 0
	closemessage
	release
	end

Route41_EventScript_Tentacruel2::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_TENTACRUEL, CRY_MODE_NORMAL
	goto_if_ge VAR_TEMP_1, 2, Route41_EventScript_TentacruelAttack2
	msgbox Route41_Text_Tentacruel, MSGBOX_DEFAULT
	waitmoncry
	addvar VAR_TEMP_1, 1
	release
	end
Route41_EventScript_TentacruelAttack2::
	msgbox Route41_Text_TentacruelAttack, MSGBOX_DEFAULT
	waitmessage
	setwildbattle SPECIES_TENTACRUEL, 100, ITEM_NONE
	dowildbattle
	closemessage
	playse SE_USE_ITEM
	msgbox Route41_Text_TentacruelHeal, MSGBOX_DEFAULT
	setvar VAR_TEMP_1, 0
	closemessage
	release
	end

Route41_EventScript_Tentacruel3::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_TENTACRUEL, CRY_MODE_NORMAL
	goto_if_ge VAR_TEMP_2, 2, Route41_EventScript_TentacruelAttack3
	msgbox Route41_Text_Tentacruel, MSGBOX_DEFAULT
	waitmoncry
	addvar VAR_TEMP_2, 1
	release
	end
Route41_EventScript_TentacruelAttack3::
	msgbox Route41_Text_TentacruelAttack, MSGBOX_DEFAULT
	waitmessage
	setwildbattle SPECIES_TENTACRUEL, 100, ITEM_NONE
	dowildbattle
	closemessage
	playse SE_USE_ITEM
	msgbox Route41_Text_TentacruelHeal, MSGBOX_DEFAULT
	setvar VAR_TEMP_2, 0
	closemessage
	release
	end

Route41_EventScript_Tentacruel4::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_TENTACRUEL, CRY_MODE_NORMAL
	goto_if_ge VAR_TEMP_3, 2, Route41_EventScript_TentacruelAttack4
	msgbox Route41_Text_Tentacruel, MSGBOX_DEFAULT
	waitmoncry
	addvar VAR_TEMP_3, 1
	release
	end
Route41_EventScript_TentacruelAttack4::
	msgbox Route41_Text_TentacruelAttack, MSGBOX_DEFAULT
	waitmessage
	setwildbattle SPECIES_TENTACRUEL, 100, ITEM_NONE
	dowildbattle
	closemessage
	playse SE_USE_ITEM
	msgbox Route41_Text_TentacruelHeal, MSGBOX_DEFAULT
	setvar VAR_TEMP_3, 0
	closemessage
	release
	end

Route41_Text_Tentacruel:
	.string "TENTACRUEL: Cruooo...$"

Route41_Text_TentacruelAttack:
	.string "TENTACRUEL: CRUOOOOOO!$"

Route41_Text_TentacruelHeal:
	.string "¡TENTACRUEL usó RECUPERAR!\n"
	.string "¡Se ha curado por completo!$"
