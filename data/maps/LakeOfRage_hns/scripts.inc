LakeOfRage_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, LakeOfRage_OnTransition
	.byte 0

LakeOfRage_OnTransition::
	setflag FLAG_VISITED_LAKE_OF_RAGE
	call_if_lt VAR_MAHOGANY_TOWN_STATE, 2, LakeOfRage_EventScript_HideLois
	goto_if_lt VAR_MAHOGANY_TOWN_STATE, 14, LakeOfRage_EventScript_SetHighTide
	special UpdateShoalTideFlag
	goto_if_set FLAG_SYS_LAKE_OF_RAGE_TIDE, LakeOfRage_EventScript_SetHighTide
	goto LakeOfRage_EventScript_SetLowTide

LakeOfRage_EventScript_SetLowTide::
	setweather WEATHER_NONE
	setmaplayoutindex LAYOUT_LAKE_OF_RAGE_LOW_TIDE_HNS
	end

LakeOfRage_EventScript_SetHighTide::
	setmaplayoutindex LAYOUT_LAKE_OF_RAGE_HNS
	goto_if_lt VAR_MAHOGANY_TOWN_STATE, 14, LakeOfRage_EventScript_ThunderStorm
	random 2
	goto_if_eq VAR_RESULT, 1, LakeOfRage_EventScript_ThunderStorm
	end

LakeOfRage_EventScript_HideLois::
	setflag FLAG_TEMP_1
	return

LakeOfRage_EventScript_ThunderStorm::
	setweather WEATHER_RAIN_THUNDERSTORM
	end

LakeOfRage_EventScript_Pryce::
    lock
    faceplayer
    msgbox LakeOfRage_Text_Pryce, MSGBOX_DEFAULT
    closemessage
    fadescreenswapbuffers FADE_TO_BLACK
    setflag FLAG_HIDE_LAKE_PRYCE
    removeobject LOCALID_LAKE_PRYCE
    fadescreenswapbuffers FADE_FROM_BLACK
    clearflag FLAG_HIDE_DOJO_PRYCE
    release
    end

LakeOfRage_Text_Pryce:
    .string "{PLAYER}.\p"
	.string "Incluso aquí, el frío me mantiene\p"
	.string "alerta.\n"
	.string "al DOJO DE LUCHA.$"

LakeOfRage_EventScript_Gramps::
	goto_if_ge VAR_MAHOGANY_TOWN_STATE, 14, LakeOfRage_EventScript_Gramps2
	msgbox LakeOfRage_Text_Gramps, MSGBOX_NPC
	end

LakeOfRage_EventScript_Gramps2::
	msgbox LakeOfRage_Text_GrampsCleared, MSGBOX_NPC
	end
LakeOfRage_EventScript_Lass::
	msgbox LakeOfRage_Text_CooltrainerF, MSGBOX_NPC
	end

LakeOfRage_EventScript_Nerd::
	msgbox LakeOfRage_Text_SuperNerd, MSGBOX_NPC
	end

LakeOfRage_EventScript_Andre::
	trainerbattle_single TRAINER_ANDRE_HNS, LakeOfRage_Text_FisherAndreSeen, LakeOfRage_Text_FisherAndreBeaten
	msgbox LakeOfRage_Text_FisherAndreAfter, MSGBOX_AUTOCLOSE
	end

LakeOfRage_EventScript_Raymond::
	trainerbattle_single TRAINER_RAYMOND_HNS, LakeOfRage_Text_FisherRaymondSeen, LakeOfRage_Text_FisherRaymondBeaten
	msgbox LakeOfRage_Text_FisherRaymondAfter, MSGBOX_AUTOCLOSE
	end

LakeOfRage_EventScript_Aaron::
	trainerbattle_single TRAINER_AARON_HNS, LakeOfRage_Text_CooltrainermAaronSeen, LakeOfRage_Text_CooltrainermAaronBeaten
	msgbox LakeOfRage_Text_CooltrainermAaronAfter, MSGBOX_AUTOCLOSE
	end

LakeOfRage_EventScript_Lois::
	trainerbattle_single TRAINER_LOIS_HNS, LakeOfRage_Text_CooltrainerfLoisSeen, LakeOfRage_Text_CooltrainerfLoisBeaten
	msgbox LakeOfRage_Text_CooltrainerfLoisAfter, MSGBOX_AUTOCLOSE
	end

LakeOfRage_EventScript_Gyarados::
	lock
	faceplayer
	msgbox LakeOfRage_Text_GyaradosCry, MSGBOX_DEFAULT
	waitse
	playmoncry SPECIES_GYARADOS, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setwildbattleshiny SPECIES_GYARADOS, 30
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, LakeOfRage_EventScript_Defeated_Gyarados
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, LakeOfRage_EventScript_Ran_Gyarados
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, LakeOfRage_EventScript_Ran_Gyarados
LakeOfRage_EventScript_Defeated_Gyarados::
	setflag FLAG_HIDE_LAKE_OF_RAGE_GYARADOS
	clearflag FLAG_TEMP_1
	removeobject LOCALID_LAKEOFRAGE_GYARADOS
	clearflag FLAG_HIDE_LAKE_OF_RAGE_LANCE
	addobject LOCALID_LAKEOFRAGE_LANCE
	giveitem ITEM_RED_SCALE
	setobjectxyperm LOCALID_LAKEOFRAGE_OLDMAN, 32, 38
	setvar VAR_MAHOGANY_TOWN_STATE, 2
	release
	end

LakeOfRage_EventScript_Ran_Gyarados::
	release
	end

LakeOfRage_EventScript_Item_Full_Restore::
	finditem ITEM_FULL_RESTORE
	end
LakeOfRage_EventScript_Item_Secret_Power::
    finditem ITEM_TM_SECRET_POWER
    end
LakeOfRage_EventScript_Item_Red_Flute::
	finditem ITEM_RED_FLUTE
	end

LakeOfRage_EventScript_Dragonite::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_DRAGONITE, CRY_MODE_NORMAL
	msgbox LakeOfRage_Text_Dragonite, MSGBOX_DEFAULT
	waitmoncry
	turnobject LOCALID_LAKEOFRAGE_DRAGONITE, DIR_WEST
	release
	end

LakeOfRage_EventScript_Lance::
	lock
	goto_if_eq VAR_MAHOGANY_TOWN_STATE, 3, LakeOfRage_EventScript_Lance_Return
	msgbox LakeOfRage_Text_LanceForcedToEvolve, MSGBOX_DEFAULT
	closemessage
	delay 20
	faceplayer
	turnobject LOCALID_LAKEOFRAGE_OLDMAN, DIR_WEST
	msgbox LakeOfRage_Text_LanceIntro2, MSGBOX_DEFAULT
	setvar VAR_MAHOGANY_TOWN_STATE, 3
	msgbox LakeOfRage_Text_LanceIntro3, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, LakeOfRage_EventScript_LancDeclined
LakeOfRage_EventScript_LanceAccept::
	lock
	msgbox LakeOfRage_Text_LanceRadioSignal, MSGBOX_DEFAULT
	closemessage
	goto_if_eq VAR_FACING, DIR_NORTH, LakeOfRage_EventScript_LanceDragoniteLeaveNorth
	applymovement LOCALID_LAKEOFRAGE_LANCE, LakeOfRage_Movement_LanceLeave
	applymovement LOCALID_LAKEOFRAGE_DRAGONITE, LakeOfRage_Movement_DragoniteLeave
	waitmovement LOCALID_LAKEOFRAGE_LANCE
	waitmovement LOCALID_LAKEOFRAGE_DRAGONITE
LakeOfRage_EventScript_EndScene::
	setflag FLAG_HIDE_LAKE_OF_RAGE_LANCE
	removeobject LOCALID_LAKEOFRAGE_LANCE
	removeobject LOCALID_LAKEOFRAGE_DRAGONITE
	setvar VAR_MAHOGANY_TOWN_STATE, 4
	clearflag FLAG_HIDE_MAHOGANY_TOWN_SHOP_NPCS
	release
	end

LakeOfRage_EventScript_Lance_Return::
	lock
	faceplayer
	msgbox LakeOfRage_Text_LanceAskHelp, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE, LakeOfRage_EventScript_LanceAccept
	goto_if_eq VAR_RESULT, FALSE, LakeOfRage_EventScript_LancDeclined

LakeOfRage_EventScript_LancDeclined::
	msgbox LakeOfRage_Text_LanceRefused, MSGBOX_DEFAULT
	closemessage
	release
	end


LakeOfRage_EventScript_LanceDragoniteLeaveNorth::
	applymovement LOCALID_LAKEOFRAGE_LANCE, LakeOfRage_Movement_LanceLeaveNorth
	applymovement LOCALID_LAKEOFRAGE_DRAGONITE, LakeOfRage_Movement_DragoniteLeaveNorth
	waitmovement LOCALID_LAKEOFRAGE_LANCE
	waitmovement LOCALID_LAKEOFRAGE_DRAGONITE
	goto LakeOfRage_EventScript_EndScene

LakeOfRage_Movement_LanceLeaveNorth:
	walk_left
	walk_down
	delay_8
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

LakeOfRage_Movement_DragoniteLeaveNorth:
	delay_16
	delay_16
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

LakeOfRage_Movement_LanceLeave:
	walk_down
	delay_8
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

LakeOfRage_Movement_DragoniteLeave:
	delay_16
	delay_16
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

LakeOfRage_Text_Dragonite:
	.string "DRAGONITE: Gyafooha!$"

LakeOfRage_Text_LanceForcedToEvolve:
    .string "Este lago está lleno de GYARADOS\n"
    .string "pero nada más...\p"
    .string "Así que los MAGIKARP son forzados\n"
    .string "a evolucionar...$"

LakeOfRage_Text_LanceIntro1:
    .string "¿Viniste aquí por los\n"
    .string "rumores?\p"
    .string "¿Eres {PLAYER}? Soy LANCE, un\n"
    .string "entrenador como tú.$"

LakeOfRage_Text_LanceIntro2:
    .string "Este hombre me informó sobre\n"
    .string "algunos rumores.\p"
    .string "Así que vinimos a investigar...$"

LakeOfRage_Text_LanceIntro3:
    .string "Vi cómo luchaste\n"
    .string "hace un momento, {PLAYER}.\p"
    .string "Noto que eres un entrenador\n"
    .string "con gran habilidad.\p"
    .string "Si no te importa, ¿podrías\n"
    .string "ayudarnos a investigar?$"

LakeOfRage_Text_LanceRadioSignal:
    .string "LANCE: ¡Excelente!\p"
    .string "Parece que el MAGIKARP del LAGO\n"
    .string "están siendo forzados a evolucionar.\p"
    .string "Una misteriosa transmisión de radio\n"
    .string "desde PUEBLO CAOBA es la causa.\p"
    .string "Estaremos esperándote,\n"
    .string "{PLAYER}.$"

LakeOfRage_Text_LanceRefused:
    .string "Oh... Bueno, si cambias de opinión,\n"
    .string "por favor, ayúdanos.$"

LakeOfRage_Text_LanceAskHelp:
    .string "LANCE: ¿Hm? ¿Vas a ayudar?\n"
    .string "us?$"

LakeOfRage_Text_GyaradosCry:
    .string "GYARADOS: Gyashaa!$"

LakeOfRage_Text_Gramps:
    .string "¡Los GYARADOS están furiosos!\p"
    .string "¡Es un mal presagio!$"

LakeOfRage_Text_GrampsCleared:
    .string "¡Jajaja! ¡Los MAGIKARP están picando!$"

LakeOfRage_Text_SuperNerd:
    .string "Oí que este lago fue creado por\n"
    .string "GYARADOS enfurecidos.\p"
    .string "Me pregunto si habrá alguna\n"
    .string "conexión con su brote masivo\l"
    .string "actual?$"

LakeOfRage_Text_CooltrainerF:
    .string "¿Me engañaron los ojos? Vi un\n"
    .string "GYARADOS rojo en el LAGO...\p"
    .string "Pero creía que los GYARADOS\n"
    .string "solían ser azules?$"


LakeOfRage_Text_FisherAndreSeen:
    .string "¡Lucharé con el POKéMON que\n"
    .string "acabo de atrapar!$"

LakeOfRage_Text_FisherAndreBeaten:
    .string "Seré un experto pescador, pero\n"
    .string "Soy un mal ENTRENADOR POKéMON...$"

LakeOfRage_Text_FisherAndreAfter:
    .string "¡No perderé como pescador! Atrapé\n"
    .string "POKéMON todo el día.$"


LakeOfRage_Text_FisherRaymondSeen:
    .string "Haga lo que haga, siempre atrapo\n"
    .string "los mismos POKéMON...$"

LakeOfRage_Text_FisherRaymondBeaten:
    .string "Mi línea está toda enredada...$"

LakeOfRage_Text_FisherRaymondAfter:
    .string "¿Por qué no puedo atrapar buenos\n"
    .string "POKéMON?$"

LakeOfRage_Text_CooltrainermAaronSeen:
    .string "Si un ENTRENADOR ve a otro,\n"
    .string "debe lanzarle un desafío.\p"
    .string "Ese es nuestro destino.$"

LakeOfRage_Text_CooltrainermAaronBeaten:
    .string "Whew... Good battle.$"

LakeOfRage_Text_CooltrainermAaronAfter:
    .string "Los POKéMON y su ENTRENADOR se\n"
    .string "hacen fuertes luchando siempre.$"

LakeOfRage_Text_CooltrainerfLoisSeen:
    .string "¿Qué pasó con el GYARADOS\n"
    .string "rojo?\p"
    .string "¿Se ha ido?\p"
    .string "Rayos. ¿Vine hasta aquí para\n"
    .string "nada?\p"
    .string "Ya sé... ¡luchemos!$"

LakeOfRage_Text_CooltrainerfLoisBeaten:
    .string "Good going!$"

LakeOfRage_Text_CooltrainerfLoisAfter:
    .string "Ahora que lo pienso, vi un\n"
    .string "BUTTERFREE rosa.$"



LakeOfRage_EventScript_Wesley::
	lock
	faceplayer
	goto_if_set FLAG_GOT_BLACK_BELT, LakeOfRage_EventScript_WesleyCompleted
	msgbox LakeOfRage_Text_MeetWesley, MSGBOX_DEFAULT
	closemessage
	multichoice 20, 0, MULTI_DAYS_OF_WEEK, FALSE
	switch VAR_RESULT
	case 0, LakeOfRage_EventScript_WesleyNope
	case 1, LakeOfRage_EventScript_WesleyNope
	case 2, LakeOfRage_EventScript_WesleyNope
	case 3, LakeOfRage_EventScript_WesleyYes
	case 4, LakeOfRage_EventScript_WesleyNope
	case 5, LakeOfRage_EventScript_WesleyNope
	case 6, LakeOfRage_EventScript_WesleyNope
	case 7 LakeOfRage_EventScript_WesleyCancel
	case MULTI_B_PRESSED, LakeOfRage_EventScript_WesleyCancel
	closemessage
	release
	end
LakeOfRage_EventScript_WesleyYes::
	msgbox LakeOfRage_Text_WesleyGivesGift, MSGBOX_DEFAULT
	giveitem ITEM_BLACK_BELT
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_GOT_BLACK_BELT
	msgbox LakeOfRage_Text_WesleyGaveGift, MSGBOX_DEFAULT
	closemessage
	release
	end
LakeOfRage_EventScript_WesleyNope::
	msgbox LakeOfRage_Text_WesleyNotWednesday, MSGBOX_DEFAULT
	closemessage
	release
	end
LakeOfRage_EventScript_WesleyCancel::
	closemessage
	release
	end
LakeOfRage_EventScript_WesleyCompleted::
	msgbox LakeOfRage_Text_WesleyWednesday, MSGBOX_DEFAULT
	closemessage
	release
	end

LakeOfRage_Text_MeetWesley:
    .string "WESLEY: Bueno, ¿cómo estás?\p"
    .string "¡Soy de la familia WEEKDAY!\n"
	.string "¿Adivinas mi día favorito?$"

LakeOfRage_Text_WesleyGivesGift:
    .string "Mucho gusto. Por favor, toma un\n"
    .string "recuerdo.$"

LakeOfRage_Text_WesleyGaveGift:
    .string "WESLEY: El CINTURÓN NEGRO sube el\n"
    .string "poder de los ataques lucha.$"

LakeOfRage_Text_WesleyWednesday:
    .string "WESLEY: Si me encontraste, ya\n"
    .string "debiste conocer a mis hermanos y\l"
    .string "hermanas.\p"
    .string "¿O solo tuviste suerte?$"

LakeOfRage_Text_WesleyNotWednesday:
    .string "WESLEY: No exactamente...$"

LakeOfRage_EventScript_Sign1::
	msgbox LakeOfRage_Text_Sign, MSGBOX_SIGN
	end

LakeOfRage_EventScript_Sign2::
	msgbox LakeOfRage_Text_FishingGuruSign, MSGBOX_SIGN
	end

LakeOfRage_Text_Sign:
    .string "LAGO DE LA FURIA,\n"
    .string "también llamado LAGO GYARADOS.$"

LakeOfRage_Text_FishingGuruSign:
    .string "FISHING GURU'S HOUSE$"
