SlowpokeWell_B1F_hns_MapScripts::
	.byte 0

SlowpokeWell_B1F_EventScript_Item_Super_Potion_1::
	finditem ITEM_SUPER_POTION
	end

SlowpokeWell_B1F_EventScript_Item_Super_Potion_2::
	finditem ITEM_SUPER_POTION
	end

SlowpokeWell_B1F_EventScript_Item_Great_Ball::
	finditem ITEM_GREAT_BALL
	end

SlowpokeWell_B1F_EventScript_Item_Full_Heal::
	finditem ITEM_FULL_HEAL
	end

SlowpokeWell_B1F_EventScript_Kurt::
	lock
	msgbox SlowpokeWell_B1F_Text_KurtIntro, MSGBOX_DEFAULT
	closemessage
	end

SlowpokeWell_B1F_EventScript_Grunt21::
	trainerbattle_single TRAINER_GRUNT_21_HNS, SlowpokeWell_B1F_Text_GruntM29Seen, SlowpokeWell_B1F_Text_GruntM29Beaten
	msgbox SlowpokeWell_B1F_Text_GruntM29After, MSGBOX_AUTOCLOSE
	end

SlowpokeWell_B1F_EventScript_Grunt22F::
	trainerbattle_single TRAINER_GRUNT_22_HNS, SlowpokeWell_B1F_Text_GruntF1Seen, SlowpokeWell_B1F_Text_GruntF1Beaten
	msgbox SlowpokeWell_B1F_Text_GruntF1After, MSGBOX_AUTOCLOSE
	end

SlowpokeWell_B1F_EventScript_Eto::
	trainerbattle_single TRAINER_ETO_HNS, SlowpokeWell_B1F_Text_GruntM2Seen, SlowpokeWell_B1F_Text_GruntM2Beaten
	msgbox SlowpokeWell_B1F_Text_GruntM2After, MSGBOX_AUTOCLOSE
	end

SlowpokeWell_B1F_EventScript_Proton::
	lock
	faceplayer
	msgbox SlowpokeWell_B1F_Text_ProtonSeen, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_PROTON_1_HNS, SlowpokeWell_B1F_Text_ProtonBeaten
	msgbox SlowpokeWell_B1F_Text_ProtonAfter, MSGBOX_AUTOCLOSE
	closemessage
	fadescreen FADE_TO_BLACK
	setflag FLAG_HIDE_AZALEA_TOWN_ROCKETS
	clearflag FLAG_HIDE_KURT_1
	addobject LOCALID_WELL_KURT
	removeobject 11
	removeobject 12
	removeobject 13
	delay 120
	fadescreen FADE_FROM_BLACK
	special DrawWholeMapView
	turnobject OBJ_EVENT_ID_PLAYER, DIR_SOUTH
	applymovement LOCALID_WELL_KURT, SlowpokeWell_B1F_Movement_Kurt
	waitmovement 0
	msgbox SlowpokeWell_B1F_Text_KurtAfter, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	setflag FLAG_HIDE_SLOWPOKE_WELL_KURT
	setflag FLAG_HIDE_KURT_1
	clearflag FLAG_HIDE_KURT_2
	clearflag FLAG_HIDE_AZALEA_TOWN_SLOWPOKE
	setvar VAR_AZALEA_TOWN_STATE, 3
	warp MAP_AZALEA_TOWN_KURTS_HOUSE_HNS, 15, 4
	waitstate
	end

SlowpokeWell_B1F_Movement_Kurt:
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	walk_up
	step_end

SlowpokeWell_B1F_Text_KurtIntro:
	.string "KURT: ¡Hola, {PLAYER}!\p"
	.string "El guardia de arriba huyó cuando\n"
	.string "le grité.\p"
	.string "Pero luego me caí por el\n"
	.string "POZO.\p"
	.string "Caí fuerte sobre mi espalda,\n"
	.string "así que no puedo moverme.\p"
	.string "¡Rayos! Si estuviera bien, mis\n"
	.string "POKéMON los habrían castigado...\p"
	.string "Ah, no hay nada que hacer.\p"
	.string "{PLAYER}, ¡demuéstrales lo valiente\n"
	.string "que eres en mi lugar!$"

SlowpokeWell_B1F_Text_KurtAfter:
	.string "KURT: ¡Bien hecho, {PLAYER}!\p"
	.string "El TEAM ROCKET huyó.\p"
	.string "Mi espalda ya está mejor.\n"
	.string "Salgamos de aquí.$"

SlowpokeWell_B1F_Text_GruntM29Seen:
	.string "¡Rayos! Vigilaba arriba\n"
	.string "cuando un viejo gritó.\l"
	.string "at me.\p"
	.string "Me asustó tanto que\n"
	.string "caí hasta aquí abajo.\p"
	.string "¡Descargaré mi rabia\n"
	.string "peleando contra ti!$"

SlowpokeWell_B1F_Text_GruntM29Beaten:
	.string "¡Arrgh! ¡Este NO es mi día!$"

SlowpokeWell_B1F_Text_GruntM29After:
	.string "Claro, hemos estado hackeando\n"
	.string "le cortan la cola a SLOWPOKE y\l"
	.string "las venden.\p"
	.string "Todo lo que hacemos es por lucro.\p"
	.string "¡Así es! Somos el TEAM ROCKET,\n"
	.string "¡y haremos lo que sea por dinero!$"

SlowpokeWell_B1F_Text_ProtonSeen:
	.string "¿Qué es lo que quieres?\p"
	.string "Si interrumpes nuestro trabajo,\n"
	.string "¡no esperes ninguna piedad!$"

SlowpokeWell_B1F_Text_ProtonBeaten:
	.string "Te fue bien hoy,\n"
	.string "¡pero espera a la próxima vez!$"

SlowpokeWell_B1F_Text_ProtonAfter:
	.string "Sí, el TEAM ROCKET fue derrotado\n"
	.string "hace tres años.\p"
	.string "El jefe se ha escondido.\p"
	.string "Pero seguimos con nuestras\n"
	.string "actividades clandestinas!\p"
	.string "Un obstáculo como tú no será\n"
	.string "problema para nuestra misión.\p"
	.string "¡Te aconsejo que tengas miedo de\n"
	.string "lo que vendrá!$"

SlowpokeWell_B1F_Text_GruntM2Seen:
	.string "¡Ji-ji-ji!\n"
	.string "¿Dejar de usar COLAS DE SLOWPOKE?\p"
	.string "¡Estás loco!\n"
	.string "¡Si te hiciéramos caso, la fama\l"
	.string "del TEAM ROCKET se arruinaría!$"

SlowpokeWell_B1F_Text_GruntM2Beaten:
	.string "Jeje...\n"
	.string "Demasiado fuerte...$"

SlowpokeWell_B1F_Text_GruntM2After:
	.string "Necesitamos el dinero,\n"
	.string "¿pero vender COLAS DE SLOWPOKE?\p"
	.string "¡Es duro ser un RECLUTA ROCKET!$"

SlowpokeWell_B1F_Text_GruntF1Seen:
	.string "¿Que deje de quitar colas?\p¡Sí, solo\nintenta vencernos!$"

SlowpokeWell_B1F_Text_GruntF1Beaten:
	.string "You rotten brat!$"

SlowpokeWell_B1F_Text_GruntF1After:
	.string "¡Las COLAS DE SLOWPOKE crecen rápido!\p"
	.string "¿Qué tiene de malo venderlas?$"

SlowpokeWell_B1F_Text_SlowpokeWithMail:
	.string "Un SLOWPOKE con la cola cortada…\p"
	.string "¿Eh? Tiene CORREO.\n"
	.string "¿Lo lees?$"

SlowpokeWell_B1F_Text_SlowpokeMail:
	.string "{PLAYER} leyó el CORREO.\p"
	.string "Sé bueno y cuida la\n"
	.string "casa con el abuelo y SLOWPOKE.\p"
	.string "Con amor, Papá$"

SlowpokeWell_B1F_Text_TaillessSlowpoke:
	.string "Un SLOWPOKE con la COLA cortada…$"
