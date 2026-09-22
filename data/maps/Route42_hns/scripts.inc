Route42_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route42_MapScript_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route42_MapScript_OnTransition::
	call_if_set FLAG_HIDE_ROUTE42_SUICUNE, Route42_MapScript_HideTrigger
	callnative SetTimeBasedEncounters
	end

Route42_MapScript_HideTrigger::
	setvar VAR_TEMP_0, 1
	return

Route42_EventScript_Suicune_Trigger::
	lock
	playmoncry SPECIES_SUICUNE, CRY_MODE_NORMAL
	applymovement LOCALID_ROUTE42_SUICUNE, Route42_Movement_Suicune1
	playse SE_LEDGE
	waitse
	playse SE_LEDGE
	waitse
	waitmovement 0
	waitmoncry
	playse SE_PIN
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement LOCALID_ROUTE42_SUICUNE, Route42_Movement_Suicune2
	playse SE_LEDGE
	delay 30
	playse SE_LEDGE
	delay 30
	playse SE_LEDGE
	delay 30
	playse SE_LEDGE
	delay 30
	waitmovement 0

	playmoncry SPECIES_SUICUNE, CRY_MODE_NORMAL
	applymovement LOCALID_ROUTE42_SUICUNE, Route42_Movement_Suicune3
	applymovement OBJ_EVENT_ID_PLAYER, Route42_Movement_Player
	playse SE_LEDGE
	delay 60
	playse SE_LEDGE
	delay 30
	playse SE_LEDGE
	delay 30
	playse SE_LEDGE
	delay 30
	playse SE_LEDGE
	delay 30
	playse SE_LEDGE
	waitmovement LOCALID_ROUTE42_SUICUNE
	waitmovement 0
	delay 60
	removeobject LOCALID_ROUTE42_SUICUNE
	setflag FLAG_HIDE_ROUTE42_SUICUNE
	clearflag FLAG_HIDE_ROUTE42_EUSINE
	addobject LOCALID_ROUTE42_EUSINE
	playse SE_EXIT
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	applymovement LOCALID_ROUTE42_EUSINE, Route42_Movement_Eusine1
	waitmovement 0
	msgbox Route42_Text_EusineAdmireSuicune, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_ROUTE42_EUSINE, DIR_WEST
	msgbox Route42_Text_EusineJealous, MSGBOX_DEFAULT
	turnobject LOCALID_ROUTE42_EUSINE, DIR_EAST
	msgbox Route42_Text_EusineWontGiveUp, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ROUTE42_EUSINE, Route42_Movement_Eusine2
	waitmovement 0
	setflag FLAG_HIDE_ROUTE42_EUSINE
	removeobject LOCALID_ROUTE42_EUSINE
	setvar VAR_TEMP_0, 1
	call_if_eq VAR_SUICUNE_ENCOUNTERS, 2, Route42_EventScript_DoneJohtoSuicune
	release
	end

Route42_EventScript_DoneJohtoSuicune::
	setvar VAR_SUICUNE_ENCOUNTERS, 3
	return

Route42_Movement_Suicune1:
	jump_in_place_right_left
	jump_in_place_right_left
	step_end

Route42_Movement_Suicune2:
	jump_2_left
	jump_2_left
	jump_2_left
	jump_2_up
	step_end

Route42_Movement_Suicune3:
	jump_in_place_up
	delay_2
	face_up
	jump_2_up
	jump_2_right
	jump_2_right
	jump_2_right
	jump_2_right
	jump_2_right
	step_end

Route42_Movement_Player:
	lock_facing_direction
	delay_2
	jump_2_up
	unlock_facing_direction
	step_end

Route42_Movement_Eusine1:
	walk_down
	walk_down
	walk_left
	face_right
	step_end

Route42_Movement_Eusine2:
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

Route42_Text_EusineAdmireSuicune:
	.string "EUSINE: SUICUNE...\n¡Qué valiente es!\p¡Qué refrescante es!\n¡Qué hermoso es!\p¡Y qué rápido se mueve!$"

Route42_Text_EusineJealous:
	.string "¡{PLAYER}!\p"
	.string "Parece que estás donde\n"
	.string "SUICUNE podría aparecer.\p"
	.string "Bueno, no importa.\l"
	.string "Mi deseo de buscar a\n"
	.string "SUICUNE es mayor que el tuyo...\p"
	.string "Mi abuelo... estaba muy\n"
	.string "interesado en los mitos.\p"
	.string "He oído muchísimas historias\n"
	.string "sobre SUICUNE por él.$"

Route42_Text_EusineWontGiveUp:
	.string "SUICUNE...\n"
	.string "No dejaré de seguirte\l"
	.string "hasta que descubra qué es\l"
	.string "lo que buscas...\p"
	.string "¡Escúchame bien!$"


Route42_EventScript_Tully::
	trainerbattle_single TRAINER_TULLY_HNS, Route42_Text_FisherTullySeen, Route42_Text_FisherTullyBeaten, Route42_EventScript_RegisterTully
	goto_if_set FLAG_TULLY_HAS_ITEM_HNS, Route42_EventScript_TullyGiveItem
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route42_EventScript_RematchTully
	msgbox Route42_Text_FisherTullyAfter, MSGBOX_AUTOCLOSE
	end

Route42_EventScript_RegisterTully::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route42_Text_TullyRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_TULLY_HNS
	release
	end

Route42_EventScript_RematchTully::
	trainerbattle_rematch TRAINER_TULLY_HNS, Route42_Text_TullyRematchIntro, Route42_Text_TullyRematchDefeat
	msgbox Route42_Text_TullyPostRematch, MSGBOX_AUTOCLOSE
	end

Route42_EventScript_TullyGiveItem::
	msgbox Route42_Text_TullyHasItem, MSGBOX_DEFAULT
	giveitem VAR_TULLY_ITEM_HNS
	goto_if_eq VAR_RESULT, FALSE, Route42_EventScript_TullyNoRoom
	clearflag FLAG_TULLY_HAS_ITEM_HNS
	msgbox Route42_Text_TullyGaveItem, MSGBOX_AUTOCLOSE
	end

Route42_EventScript_TullyNoRoom::
	msgbox Route42_Text_TullyNoRoom, MSGBOX_AUTOCLOSE
	end

Route42_EventScript_Ben::
	trainerbattle_single TRAINER_BENJAMIN_HNS, Route42_Text_HikerBenjaminSeen, Route42_Text_HikerBenjaminBeaten
	msgbox Route42_Text_HikerBenjaminAfter, MSGBOX_AUTOCLOSE
	end

Route42_EventScript_Shane::
	trainerbattle_single TRAINER_SHANE_HNS, Route42_Text_PokemaniacShaneSeen, Route42_Text_PokemaniacShaneBeaten
	msgbox Route42_Text_PokemaniacShaneAfter, MSGBOX_AUTOCLOSE
	end

Route42_EventScript_Sign::
	lock
	msgbox Route42_Text_Sign1, MSGBOX_SIGN
	closemessage
	release
	end

Route42_EventScript_MortarSign::
	lock
	msgbox Route42_Text_MtMortarSign1, MSGBOX_SIGN
	closemessage
	release
	end

Route42_EventScript_Item_SuperPotion::
	finditem ITEM_SUPER_POTION
	end
Route42_EventScript_Item_Shadow_Claw::
    finditem ITEM_TM_SHADOW_CLAW
    end
Route42_EventScript_Item_UltraBall::
	finditem ITEM_ULTRA_BALL
	end

Route42_Text_FisherTullySeen:
	.string "¡Déjame mostrarte el poder\n"
	.string "de los POKéMON que atrapé!$"

Route42_Text_FisherTullyBeaten:
	.string "¿Qué? Esto no puede ser.\n"
	.string "¡No puedo creerlo!$"

Route42_Text_FisherTullyAfter:
	.string "Quiero ser el mejor entrenador\n"
	.string "CAMPEÓN usando el POKéMON que\l"
	.string "yo mismo atrapé.\p"
	.string "¡Es lo mejor de pescar!$"

Route42_Text_HikerBenjaminSeen:
	.string "¡Ah, es bueno estar fuera!\n"
	.string "¡Me siento tan libre!$"

Route42_Text_HikerBenjaminBeaten:
	.string "¡Gajajaj! ¡Fue una buena\n"
	.string "batalla!$"

Route42_Text_HikerBenjaminAfter:
	.string "¡Perder no importa si miras\n"
	.string "el gran cielo arriba!$"

Route42_Text_PokemaniacShaneSeen:
	.string "¡OYE!\p"
	.string "¡Este es mi lugar secreto!\n"
	.string "¡Lárgate, forastero!$"

Route42_Text_PokemaniacShaneBeaten:
	.string "Debí haber usado mi\n"
	.string "PIEDRA LUNAR...$"

Route42_Text_PokemaniacShaneAfter:
	.string "¿Trabajas en una POKéDEX?\p"
	.string "¡Vaya, debes conocer algunos\n"
	.string "POKéMON muy raros!\p"
	.string "¿Puedo verlo, por favor?\n"
	.string "¿Por favor?$"

Route42_Text_Sign1:
	.string "RUTA 42\p"
	.string "CD. IRIS - PUEBLO CAOBA$"

Route42_Text_MtMortarSign1:
	.string "MT. MORTAR\p"
	.string "DENTRO DE LA CUEVA CASCADA$"

Route42_Text_TullyRegister:
	.string "Quiero ser el mejor entrenador\n"
	.string "CAMPEÓN usando el POKéMON que\l"
	.string "yo mismo atrapé.\p"
	.string "¡Es lo mejor de pescar!$"

Route42_Text_TullyRematchIntro:
	.string "¡Déjame mostrarte el poder\n"
	.string "de los POKéMON que atrapé!$"

Route42_Text_TullyRematchDefeat:
	.string "¿Qué? Esto no puede ser.\n"
	.string "¡No puedo creerlo!$"

Route42_Text_TullyPostRematch:
	.string "Quiero ser el mejor entrenador\n"
	.string "CAMPEÓN usando el POKéMON que\l"
	.string "yo mismo atrapé.\p"
	.string "¡Es lo mejor de pescar!$"

Route42_Text_TullyHasItem:
	.string "¡Oye! Encontré algo brillante\n"
	.string "¡mientras pescaba!\p"
	.string "¡Toma, puedes quedártelo!$"

Route42_Text_TullyGaveItem:
	.string "Te avisaré si\n"
	.string "¡No pescaste nada más!$"

Route42_Text_TullyNoRoom:
	.string "Hmm, tu MOCHILA está llena.\p"
	.string "Vuelve cuando tengas espacio.$"
