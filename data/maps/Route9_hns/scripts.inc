Route9_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route9_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route9_OnTransition: 
	callnative SetTimeBasedEncounters
	end

Route9_EventScript_Dean::
	trainerbattle_single TRAINER_DEAN_HNS, Route9_Text_CamperDeanSeen, Route9_Text_CamperDeanBeaten
	msgbox Route9_Text_CamperDeanAfter, MSGBOX_AUTOCLOSE
	end

Route9_EventScript_Heidi::
	trainerbattle_single TRAINER_HEIDI_HNS, Route9_Text_PicnickerHeidiSeen, Route9_Text_PicnickerHeidiBeaten
	msgbox Route9_Text_PicnickerHeidiAfter, MSGBOX_AUTOCLOSE
	end

Route9_EventScript_Edna::
	trainerbattle_single TRAINER_EDNA_HNS, Route9_Text_PicnickerEdnaSeen, Route9_Text_PicnickerEdnaBeaten
	msgbox Route9_Text_PicnickerEdnaAfter, MSGBOX_AUTOCLOSE
	end

Route9_EventScript_Sid::
	trainerbattle_single TRAINER_SID_HNS, Route9_Text_CamperSidSeen, Route9_Text_CamperSidBeaten
	msgbox Route9_Text_CamperSidAfter, MSGBOX_AUTOCLOSE
	end

Route9_EventScript_Tim::
	trainerbattle_single TRAINER_TIM_HNS, Route9_Text_HikerTimSeen, Route9_Text_HikerTimBeaten
	msgbox Route9_Text_HikerTimAfter, MSGBOX_AUTOCLOSE
	end

Route9_EventScript_Sidney::
	trainerbattle_single TRAINER_SIDNEY_HNS, Route9_Text_HikerSidneySeen, Route9_Text_HikerSidneyBeaten
	msgbox Route9_Text_HikerSidneyAfter, MSGBOX_AUTOCLOSE
	end

Route9_EventScript_Sign::
	msgbox Route9_Text_Sign, MSGBOX_SIGN
	end

Route9_EventScript_Item_Flash_Cannon::
    finditem ITEM_TM_FLASH_CANNON
    end

Route9_Text_CamperDeanSeen:
	.string "I came to explore ROCK TUNNEL.$"

Route9_Text_CamperDeanBeaten:
	.string "Whoa! Danger, man.$"

Route9_Text_CamperDeanAfter:
	.string "Mis POKéMON se hirieron incluso\n"
	.string "antes de entrar al TÚNEL ROCA.\p"
	.string "Será mejor llevarlos a un CENTRO\n"
	.string "POKéMON ahora mismo.$"

Route9_Text_PicnickerHeidiSeen:
	.string "¿Alguna vez has ido de picnic?\p"
	.string "¡Son muy divertidos!$"

Route9_Text_PicnickerHeidiBeaten:
	.string "Ohhhh!$"

Route9_Text_PicnickerHeidiAfter:
	.string "Hacemos muchos dulces y los\n"
	.string "compartimos con todos.\p"
	.string "¡Están deliciosos!$"

Route9_Text_CamperSidSeen:
	.string "¡Oye, tú! ¡No tires basura!$"

Route9_Text_CamperSidBeaten:
	.string "Solo estaba señalando…$"

Route9_Text_CamperSidAfter:
	.string "Perdón. No estabas tirando basura.\n"
	.string "Fue mi error.$"

Route9_Text_PicnickerEdnaSeen:
	.string "La gente no debería dejar basura\n"
	.string "tirada.$"

Route9_Text_PicnickerEdnaBeaten:
	.string "Ohh… I lost…$"

Route9_Text_PicnickerEdnaAfter:
	.string "Ahorrar energía es importante,\n"
	.string "pero el medio ambiente es aún más\l"
	.string "vital.$"

Route9_Text_HikerTimSeen:
	.string "Ella pasará por el MT.SILVER\n"
	.string "cuando venga...\p"
	.string "MT.SILVER está en JOHTO, ¿verdad?$"

Route9_Text_HikerTimBeaten:
	.string "I was too busy singing…$"

Route9_Text_HikerTimAfter:
	.string "Las batallas son de concentración.$"

Route9_Text_HikerSidneySeen:
	.string "Te contaré un secreto.\p"
	.string "¡Pero primero, luchamos!$"

Route9_Text_HikerSidneyBeaten:
	.string "¡Ay, no! Perdí eso…$"

Route9_Text_HikerSidneyAfter:
	.string "La CENTRAL ELÉCTRICA está tras un\n"
	.string "río.$"

Route9_Text_Sign:
	.string "RUTA 9\p"
	.string "CIUDAD CERULEAN - TÚNEL ROCA$"
