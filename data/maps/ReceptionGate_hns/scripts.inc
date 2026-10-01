ReceptionGate_hns_MapScripts::
	.byte 0

ReceptionGate_EventScript_Janine::
    lock
    faceplayer
    msgbox ReceptionGate_Text_Janine, MSGBOX_DEFAULT
    closemessage
    fadescreenswapbuffers FADE_TO_BLACK
    setflag FLAG_HIDE_ROUTE22_JANINE
    removeobject LOCALID_INDIGOJUNCTION_JANINE
    fadescreenswapbuffers FADE_FROM_BLACK
    clearflag FLAG_HIDE_DOJO_JANINE
    release
    end

ReceptionGate_Text_Janine:
    .string "JANINE: Voy camino a la casa de mi\n"
    .string "papá para llevarle el almuerzo.\p"
    .string "El ALTO MANDO no tiene tiempo de\n"
    .string "descansar ni día ni noche. Es un\l"
    .string "trabajo duro, ¿sabes?\p"
    .string "Si estás listo para otra batalla,\n"
    .string "estaré en el DOJO más tarde.$"


ReceptionGate_EventScript_Officer::
    msgbox VictoryRoadGate_Text_EightBadges, MSGBOX_NPC
    end

ReceptionGate_Trigger::
    lock
    playse SE_PIN
    applymovement LOCALID_INDIGOJUNCTION_POLICEMAN, Common_Movement_ExclamationMark
    delay 55
    waitmovement LOCALID_INDIGOJUNCTION_POLICEMAN
    goto_if_lt VAR_ECRUTEAK_CITY_THEATER, 8, ReceptionGate_EventScript_Kimono
    msgbox VictoryRoadGate_Text_Officer, MSGBOX_DEFAULT
    goto_if_unset FLAG_BADGE08_GET, ReceptionGate_EventScript_NotEnough
    msgbox VictoryRoadGate_Text_EightBadges, MSGBOX_DEFAULT
    closemessage
    setvar VAR_ROUTE27_STATE, 2
    release
    end

ReceptionGate_EventScript_Kimono::
    msgbox VictoryRoadGate_Text_Kimono, MSGBOX_DEFAULT
    closemessage
    applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkDown1
    waitmovement 0
    release
    end 

ReceptionGate_EventScript_NotEnough::
    msgbox VictoryRoadGate_Text_NotEnoughBadges, MSGBOX_DEFAULT
    closemessage
    applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkDown1
    waitmovement 0
    release
    end

ReceptionGate_EventScript_SilverGuard::
    msgbox VictoryRoadGate_Text_LeftBlackBelt, MSGBOX_NPC
    end
ReceptionGate_EventScript_KantoGuard::
    msgbox VictoryRoadGate_Text_RightBlackBelt, MSGBOX_NPC
    end

VictoryRoadGate_Text_Officer:
    .string "Solo los ENTRENADORES que se han\n"
    .string "demostrado pueden pasar.$"

VictoryRoadGate_Text_Kimono:
    .string "Lo siento, niño, el camino está\n"
    .string "cerrado hasta que alguien se ocupe\l"
    .string "de ese POKéMON LEGENDARIO...$"

VictoryRoadGate_Text_NotEnoughBadges:
    .string "No tienes todas las MEDALLAS de\n"
    .string "JOHTO.\p"
    .string "Lo siento, pero no puedo dejarte\n"
    .string "pasar.$"

VictoryRoadGate_Text_EightBadges:
    .string "¡Oh! ¡Las ocho MEDALLAS de JOHTO!\p"
    .string "¡Por favor, pasa adelante!$"

VictoryRoadGate_Text_LeftBlackBelt:
    .string "Este camino lleva al MT.SILVER.\p"
    .string "Verás POKéMON fuertes y aterradores\n"
    .string "raras allí.$"

VictoryRoadGate_Text_RightBlackBelt:
    .string "¿Vas camino a la LIGA POKéMON?\p"
    .string "El ALTO MANDO es tan fuerte que\n"
    .string "da miedo, ¡y ya te están esperando!$"
