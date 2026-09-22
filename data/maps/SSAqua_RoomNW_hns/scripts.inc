SSAqua_RoomNW_hns_MapScripts::
    map_script MAP_SCRIPT_ON_TRANSITION, SSAqua_RoomNW_OnTransition
	.byte 0

SSAqua_RoomNW_OnTransition::
    goto_if_ge VAR_SSAQUA_STATE, 3, SSAqua_RoomNW_SetTrainerPos
    end

SSAqua_RoomNW_SetTrainerPos::
    setobjectxyperm 2, 2, 6
    setobjectxyperm 3, 4, 3
    end

SSAqua_RoomNW_EventScript_Stanly::
    lock
    faceplayer
    msgbox SSAqua_RoomNW_Text_SailorStanlySeen, MSGBOX_DEFAULT
    trainerbattle_no_intro TRAINER_STANLY_HNS, SSAqua_RoomNW_Text_SailorStanlyBeaten
	msgbox SSAqua_RoomNW_Text_SailorStanlyAfterBattle, MSGBOX_DEFAULT
    closemessage
    fadescreenswapbuffers FADE_TO_BLACK
    delay 60
    playse SE_DOOR
    removeobject LOCALID_SSAQUA_SLEEPYSAILOR
    fadescreenswapbuffers FADE_FROM_BLACK
    setvar VAR_SSAQUA_STATE, 3
	end

SSAqua_RoomNW_EventScript_Edward::
    trainerbattle_single TRAINER_EDWARD_HNS, SSAqua_RoomNW_Text_GentlemanEdwardSeen, SSAqua_RoomNW_Text_GentlemanEdwardBeaten
	msgbox SSAqua_RoomNW_Text_GentlemanEdwardAfterBattle, MSGBOX_AUTOCLOSE
	end

SSAqua_RoomNW_EventScript_Corey::
    trainerbattle_single TRAINER_COREY_HNS, SSAqua_RoomNW_Text_BurglarCoreySeen, SSAqua_RoomNW_Text_BurglarCoreyBeaten
	msgbox SSAqua_RoomNW_Text_BurglarCoreyAfterBattle, MSGBOX_AUTOCLOSE
	end


SSAqua_RoomNW_Text_SailorStanlySeen:
	.string "Sí, soy marinero, está bien.\p"
	.string "¡No estaba perdiendo el tiempo!\p"
	.string "Esta cabina estaba vacía, así que\n"
	.string "¡solo tomé una siesta rápida!\p"
	.string "¡Ah, olvídalo! ¡Luchemos!$"

SSAqua_RoomNW_Text_SailorStanlyBeaten:
	.string "¡Perdón! ¡Todo es mi culpa!$"

SSAqua_RoomNW_Text_SailorStanlyAfterBattle:
	.string "Como marinero, tengo que hacer\n"
	.string "trabajo físico. ¡Es agotador!$"

SSAqua_RoomNW_Text_GentlemanEdwardSeen:
	.string "Oh, no. He perdido algo\n"
	.string "que es muy importante.$"

SSAqua_RoomNW_Text_GentlemanEdwardBeaten:
	.string "No... no lo encuentro...$"

SSAqua_RoomNW_Text_GentlemanEdwardAfterBattle:
	.string "Me rindo. No tienes que\n"
	.string "Mira.\p"
	.string "¡Solo olvídalo!$"

SSAqua_RoomNW_Text_BurglarCoreySeen:
	.string "Yeehaw! Lucky!$"

SSAqua_RoomNW_Text_BurglarCoreyBeaten:
	.string "How unlucky! I lost!$"

SSAqua_RoomNW_Text_BurglarCoreyAfterBattle:
	.string "Hallé una moneda linda aquí.\p"
	.string "Alguien debe haberla perdido...$"
