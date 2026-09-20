Route6_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route6_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route6_OnTransition:
	callnative SetTimeBasedEncounters
	end

Route6_EventScript_Rex::
	trainerbattle_single TRAINER_REX_HNS, PokefanM_Text_RexSeen, PokefanM_Text_RexBeaten
	msgbox PokefanM_Text_RexAfter, MSGBOX_AUTOCLOSE
	end

Route6_EventScript_Allan::
	trainerbattle_single TRAINER_ALLAN_HNS, PokefanM_Text_AllanSeen, PokefanM_Text_AllanBeaten
	msgbox PokefanM_Text_AllanAfter, MSGBOX_AUTOCLOSE
	end

Route6_EventScript_Pokefan::
	msgbox Route6_Text_PokefanM, MSGBOX_NPC
	end

Route6_EventScript_Sign::
	msgbox Route6_Text_UndergroundPathSign, MSGBOX_SIGN
	end

Route6_EventScript_Item_Silver_Wind::
    finditem ITEM_TM_SILVER_WIND
    end

Route6_Text_PokefanM:
	.string "El camino está cerrado hasta que\n"
	.string "el problema de la CENTRAL ELÉCTRICA\l"
	.string "se solucione.$"

Route6_Text_UndergroundPathSign:
	.string "CAMINO SUBTERRÁNEO\p"
	.string "CIUDAD CELADON - CIUDAD VERMILION$"

PokefanM_Text_RexSeen:
	.string "Mi STANTLER es el más lindo del\n"
	.string "mundo.$"

PokefanM_Text_RexBeaten:
	.string "My STANTLER!$"

PokefanM_Text_RexAfter:
	.string "¡Mira qué adorable es mi\n"
	.string "STANTLER!\p"
	.string "¿No es tan lindo que hace que\n"
	.string "tu corazón se derrita?$"

PokefanM_Text_AllanSeen:
	.string "Mi GRANBULL es el más lindo del\n"
	.string "mundo.$"

PokefanM_Text_AllanBeaten:
	.string "My GRANBULL!$"

PokefanM_Text_AllanAfter:
	.string "Mira qué adorable es mi GRANBULL\n"
	.string "STANTLER!\p"
	.string "¿No es tan lindo que hace que\n"
	.string "tu corazón se derrita?$"

