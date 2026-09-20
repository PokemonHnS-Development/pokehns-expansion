UnionCave_1F_hns_MapScripts::
	.byte 0


UnionCave_1F_Trigger_Monview::
	special SpawnCameraObject
	applymovement2 OBJ_EVENT_ID_CAMERA, Common_Movement_WalkRight1
	waitmovement 0
	applymovement2 OBJ_EVENT_ID_CAMERA, Common_Movement_WalkRight1
	waitmovement 0
	applymovement2 OBJ_EVENT_ID_CAMERA, Common_Movement_WalkRight1
	waitmovement 0
	applymovement2 OBJ_EVENT_ID_CAMERA, Common_Movement_WalkRight1
	waitmovement 0
	message Route29_Text_PressAorB
	waitbuttonpress
	closemessage
	applymovement2 OBJ_EVENT_ID_CAMERA, Common_Movement_WalkLeft1
	waitmovement 0
	applymovement2 OBJ_EVENT_ID_CAMERA, Common_Movement_WalkLeft1
	waitmovement 0
	applymovement2 OBJ_EVENT_ID_CAMERA, Common_Movement_WalkLeft1
	waitmovement 0
	applymovement2 OBJ_EVENT_ID_CAMERA, Common_Movement_WalkLeft1
	waitmovement 0
	special RemoveCameraObject
	applymovement2 OBJ_EVENT_ID_PLAYER, Common_Movement_WalkLeft1
	waitmovement 0
	end


UnionCave_1F_EventScript_HikerRussell::
	trainerbattle_single TRAINER_RUSSELL_HNS, UnionCave_1F_Text_HikerRussellSeen, UnionCave_1F_Text_HikerRussellBeaten
	msgbox UnionCave_1F_Text_HikerRussellAfter, MSGBOX_AUTOCLOSE
	end

UnionCave_1F_EventScript_PokemaniacLarry::
	trainerbattle_single TRAINER_LARRY_HNS, UnionCave_1F_Text_PokemaniacLarrySeen, UnionCave_1F_Text_PokemaniacLarryBeaten
	msgbox UnionCave_1F_Text_PokemaniacLarryAfter, MSGBOX_AUTOCLOSE
	end

UnionCave_1F_EventScript_HikerDaniel::
	trainerbattle_single TRAINER_DANIEL_HNS, UnionCave_1F_Text_HikerDanielSeen, UnionCave_1F_Text_HikerDanielBeaten
	msgbox UnionCave_1F_Text_HikerDanielAfter, MSGBOX_AUTOCLOSE
	end

UnionCave_1F_EventScript_FirebreatherBill::
	trainerbattle_single TRAINER_BILL_HNS, UnionCave_1F_Text_FirebreatherBillSeen, UnionCave_1F_Text_FirebreatherBillBeaten
	msgbox UnionCave_1F_Text_FirebreatherBillAfter, MSGBOX_AUTOCLOSE
	end

UnionCave_1F_EventScript_FirebreatherRay::
	trainerbattle_single TRAINER_RAY_HNS, UnionCave_1F_Text_FirebreatherRaySeen, UnionCave_1F_Text_FirebreatherRayBeaten
	msgbox UnionCave_1F_Text_FirebreatherRayAfter, MSGBOX_AUTOCLOSE
	end	

UnionCave_1F_EventScript_Item_Potion::
	finditem ITEM_POTION
	end

UnionCave_1F_EventScript_Item_GreatBall::
	finditem ITEM_GREAT_BALL
	end

UnionCave_1F_EventScript_Item_Xattack::
	finditem ITEM_X_ATTACK
	end

UnionCave_1F_EventScript_Item_Awakening::
	finditem ITEM_AWAKENING
	end

UnionCave_1F_Text_HikerRussellSeen:
	.string "Vas camino a PUEBLO AZALEA, ¿no?\p"
	.string "Dejaré que mi POKéMON vea si eres\n"
	.string "suficientemente bueno para luchar.$"

UnionCave_1F_Text_HikerRussellBeaten:
	.string "Oh, oh, oh!$"

UnionCave_1F_Text_HikerRussellAfter:
	.string "¡Muy bien! Ya me he decidido.\p"
	.string "¡No me iré hasta que mi POKéMON\n"
	.string "sea más fuerte!$"

UnionCave_1F_Text_PokemaniacLarrySeen:
	.string "Viajo por todas partes buscando...\n"
	.string "POKéMON planta.\p"
	.string "¿Tú también buscas POKéMON?\p"
	.string "¡Entonces eres mi rival de captura!$"

UnionCave_1F_Text_PokemaniacLarryBeaten:
	.string "Ugh. My poor POKéMON…$"

UnionCave_1F_Text_PokemaniacLarryAfter:
	.string "A veces se oyen rugidos de POKéMON\n"
	.string "desde lo profundo de la cueva.$"

UnionCave_1F_Text_HikerDanielSeen:
	.string "¡Vaya! ¡Qué sorpresa!\p"
	.string "¡No esperaba ver a nadie aquí!$"

UnionCave_1F_Text_HikerDanielBeaten:
	.string "Whoa! I'm beaten big time!$"

UnionCave_1F_Text_HikerDanielAfter:
	.string "Me engañaron para que comprara una\n"
	.string "COLA DE SLOWPOK.\p"
	.string "Siento pena por el pobre POKéMON.$"

UnionCave_1F_Text_FirebreatherBillSeen:
	.string "El SUPERSONIDO de ZUBAT confunde\n"
	.string "mi POKéMON.\p"
	.string "¡Eso me molesta muchísimo!$"

UnionCave_1F_Text_FirebreatherBillBeaten:
	.string "I flamed out!$"

UnionCave_1F_Text_FirebreatherBillAfter:
	.string "Los fines de semana se oyen rugidos\n"
	.string "extraños desde el fondo de la cueva.$"

UnionCave_1F_Text_FirebreatherRaySeen:
	.string "Si hay luz, la cueva no asusta.\p"
	.string "Si eres fuerte, los POKéMON no son\n"
	.string "aterradores.$"

UnionCave_1F_Text_FirebreatherRayBeaten:
	.string "FLASH!$"

UnionCave_1F_Text_FirebreatherRayAfter:
	.string "Es el fuego de mi POKéMON lo que\n"
	.string "ilumina esta cueva.$"
