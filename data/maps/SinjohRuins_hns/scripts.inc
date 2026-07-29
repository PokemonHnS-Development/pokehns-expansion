SinjohRuins_hns_MapScripts::
    map_script 	MAP_SCRIPT_ON_TRANSITION, SinjohRuins_hns_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, SinjohRuins_hns_OnLoad
	.byte 0

SinjohRuins_hns_OnTransition::
	end

SinjohRuins_hns_OnLoad::
    call_if_ge VAR_PLATECOUNTER, 3, SinjohRuins_OpenRegirock
    call_if_ge VAR_PLATECOUNTER, 6, SinjohRuins_OpenRegice
    call_if_ge VAR_PLATECOUNTER, 9, SinjohRuins_OpenRegisteel
    call_if_ge VAR_PLATECOUNTER, 12, SinjohRuins_OpenRegieleki
    call_if_ge VAR_PLATECOUNTER, 15, SinjohRuins_OpenRegidrago
    @call_if_ge VAR_PLATECOUNTER, 17, SinjohRuins_OpenArceus @todo
    end

SinjohRuins_OpenRegirock::
    setmetatile 9, 44, 0x378, FALSE
    setmetatile 8, 44, 0x0BE, TRUE
    return
SinjohRuins_OpenRegice::
    setmetatile 7, 48, 0x370, FALSE
    setmetatile 6, 48, 0x0BE, TRUE
    return
SinjohRuins_OpenRegisteel::
    setmetatile 8, 54, 0x370, FALSE
    setmetatile 7, 54, 0x0BE, TRUE
    return
SinjohRuins_OpenRegieleki::
    setmetatile 38, 44, 0x371, FALSE
    setmetatile 39, 44, 0x0BD, TRUE
    return
SinjohRuins_OpenRegidrago::
    setmetatile 37, 49, 0x371, FALSE
    setmetatile 38, 49, 0x0BD, TRUE
    return

SinjohRuins_OpenArceus::
    @left stairs
    setmetatile 17, 32, 0x089, FALSE
    setmetatile 17, 33, 0x089, FALSE
    setmetatile 17, 34, 0x089, FALSE
    setmetatile 17, 35, 0x089, FALSE
    setmetatile 17, 36, 0x089, FALSE
    setmetatile 18, 32, 0x091, FALSE
    setmetatile 18, 33, 0x091, FALSE
    setmetatile 18, 34, 0x091, FALSE
    setmetatile 18, 35, 0x091, FALSE
    setmetatile 18, 36, 0x091, FALSE
    setmetatile 19, 32, 0x091, FALSE
    setmetatile 19, 33, 0x091, FALSE
    setmetatile 19, 34, 0x091, FALSE
    setmetatile 19, 35, 0x091, FALSE
    setmetatile 19, 36, 0x091, FALSE
    @right stairs
    setmetatile 29, 32, 0x089, FALSE
    setmetatile 29, 33, 0x089, FALSE
    setmetatile 29, 34, 0x089, FALSE
    setmetatile 29, 35, 0x089, FALSE
    setmetatile 29, 36, 0x089, FALSE
    setmetatile 30, 32, 0x091, FALSE
    setmetatile 30, 33, 0x091, FALSE
    setmetatile 30, 34, 0x091, FALSE
    setmetatile 30, 35, 0x091, FALSE
    setmetatile 30, 36, 0x091, FALSE
    setmetatile 31, 32, 0x091, FALSE
    setmetatile 31, 33, 0x091, FALSE
    setmetatile 31, 34, 0x091, FALSE
    setmetatile 31, 35, 0x091, FALSE
    setmetatile 31, 36, 0x091, FALSE
    return

SinjohRuins_EventScript_Sign::
    msgbox SinjohRuins_Text_Sign, MSGBOX_SIGN
    end

SinjohRuins_Text_Sign:
    .string "SINJOH RUINS$"
