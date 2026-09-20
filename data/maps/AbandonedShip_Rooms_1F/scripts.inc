AbandonedShip_Rooms_1F_MapScripts::
	.byte 0

AbandonedShip_Rooms_1F_EventScript_Gentleman::
	msgbox AbandonedShip_Rooms_1F_Text_TakingALookAround, MSGBOX_NPC
	end

AbandonedShip_Rooms_1F_EventScript_Demetrius::
	trainerbattle_single TRAINER_DEMETRIUS, AbandonedShip_Rooms_1F_Text_DemetriusIntro, AbandonedShip_Rooms_1F_Text_DemetriusDefeat
	msgbox AbandonedShip_Rooms_1F_Text_DemetriusPostBattle, MSGBOX_AUTOCLOSE
	end

AbandonedShip_Rooms_1F_EventScript_Thalia::
	trainerbattle_single TRAINER_THALIA_1, AbandonedShip_Rooms_1F_Text_ThaliaIntro, AbandonedShip_Rooms_1F_Text_ThaliaDefeat, AbandonedShip_Rooms_1F_EventScript_RegisterThalia
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, AbandonedShip_Rooms_1F_EventScript_ThaliaRematch
	msgbox AbandonedShip_Rooms_1F_Text_ThaliaPostBattle, MSGBOX_DEFAULT
	release
	end

AbandonedShip_Rooms_1F_EventScript_RegisterThalia::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox AbandonedShip_Rooms_1F_Text_ThaliaRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_THALIA_1
	release
	end

AbandonedShip_Rooms_1F_EventScript_ThaliaRematch::
	trainerbattle_rematch TRAINER_THALIA_1, AbandonedShip_Rooms_1F_Text_ThaliaRematchIntro, AbandonedShip_Rooms_1F_Text_ThaliaRematchDefeat
	msgbox AbandonedShip_Rooms_1F_Text_ThaliaPostRematch, MSGBOX_AUTOCLOSE
	end

AbandonedShip_Rooms_1F_Text_TakingALookAround:
	.string "Barcos así son raros, por eso\n"
	.string "estoy echando un vistazo.\p"
	.string "Hmhm...\n"
	.string "Parece que hay otras cabinas...$"

AbandonedShip_Rooms_1F_Text_ThaliaIntro:
	.string "¿Qué te impulsaría a venir\n"
	.string "hasta aquí? ¡Debes ser curioso!$"

AbandonedShip_Rooms_1F_Text_ThaliaDefeat:
	.string "Not just curious, but also strong…$"

AbandonedShip_Rooms_1F_Text_ThaliaPostBattle:
	.string "El hombre de al lado...\p"
	.string "Dice que solo está de turismo,\n"
	.string "pero no estoy tan segura.$"

AbandonedShip_Rooms_1F_Text_ThaliaRegister:
	.string "¡Eres un ENTRENADOR muy fuerte!\n"
	.string "¡Te registraré como recuerdo!$"

AbandonedShip_Rooms_1F_Text_ThaliaRematchIntro:
	.string "¿Qué te impulsaría a venir\n"
	.string "¿Vuelves? ¡Debes tener curiosidad!$"

AbandonedShip_Rooms_1F_Text_ThaliaRematchDefeat:
	.string "Aren't you too strong?$"

AbandonedShip_Rooms_1F_Text_ThaliaPostRematch:
	.string "¡Seguro que ese hombre trama algo!\n"
	.string "¡Actúa de forma muy sospechosa!$"

AbandonedShip_Rooms_1F_Text_DemetriusIntro:
	.string "¡Waaah!\n"
	.string "¡Me encontraron! ...¿Eh?$"

AbandonedShip_Rooms_1F_Text_DemetriusDefeat:
	.string "Oh, no eres mi mamá.$"

AbandonedShip_Rooms_1F_Text_DemetriusPostBattle:
	.string "Tengo problemas con mi mamá y huí.\n"
	.string "¡No digas dónde estoy!$"

