RustboroCity_DevonCorp_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, RustboroCity_DevonCorp_1F_OnTransition
	.byte 0

RustboroCity_DevonCorp_1F_OnTransition:
	call_if_unset FLAG_RETURNED_DEVON_GOODS, RustboroCity_DevonCorp_1F_EventScript_BlockStairs
	end

RustboroCity_DevonCorp_1F_EventScript_BlockStairs::
	setobjectxyperm LOCALID_DEVON_CORP_STAIR_GUARD, 14, 2
	setobjectmovementtype LOCALID_DEVON_CORP_STAIR_GUARD, MOVEMENT_TYPE_FACE_DOWN
	return

RustboroCity_DevonCorp_1F_EventScript_Employee::
	lock
	faceplayer
	goto_if_set FLAG_RETURNED_DEVON_GOODS, RustboroCity_DevonCorp_1F_EventScript_GoodsRecovered
	goto_if_set FLAG_DEVON_GOODS_STOLEN, RustboroCity_DevonCorp_1F_EventScript_RobberWasntBright
	msgbox RustboroCity_DevonCorp_1F_Text_ThoseShoesAreOurProduct, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_1F_EventScript_RobberWasntBright::
	msgbox RustboroCity_DevonCorp_1F_Text_RobberWasntVeryBright, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_1F_EventScript_GoodsRecovered::
	msgbox RustboroCity_DevonCorp_1F_Text_SoundsLikeStolenGoodsRecovered, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_1F_EventScript_StairGuard::
	lock
	faceplayer
	goto_if_set FLAG_RETURNED_DEVON_GOODS, RustboroCity_DevonCorp_1F_EventScript_AlwaysWelcome
	goto_if_set FLAG_RECOVERED_DEVON_GOODS, RustboroCity_DevonCorp_1F_EventScript_GotRobbed
	goto_if_set FLAG_DEVON_GOODS_STOLEN, RustboroCity_DevonCorp_1F_EventScript_GotRobbed
	msgbox RustboroCity_DevonCorp_1F_Text_OnlyAuthorizedPeopleEnter, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_1F_EventScript_AlwaysWelcome::
	msgbox RustboroCity_DevonCorp_1F_Text_YoureAlwaysWelcomeHere, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_1F_EventScript_GotRobbed::
	msgbox RustboroCity_DevonCorp_1F_Text_HowCouldWeGetRobbed, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_1F_EventScript_Greeter::
	lock
	faceplayer
	goto_if_set FLAG_RETURNED_DEVON_GOODS, RustboroCity_DevonCorp_1F_EventScript_WelcomeToDevonCorp
	goto_if_set FLAG_RECOVERED_DEVON_GOODS, RustboroCity_DevonCorp_1F_EventScript_StaffGotRobbed
	goto_if_set FLAG_DEVON_GOODS_STOLEN, RustboroCity_DevonCorp_1F_EventScript_StaffGotRobbed
	msgbox RustboroCity_DevonCorp_1F_Text_WelcomeToDevonCorp, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_1F_EventScript_WelcomeToDevonCorp::
	msgbox RustboroCity_DevonCorp_1F_Text_WelcomeToDevonCorp, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_1F_EventScript_StaffGotRobbed::
	msgbox RustboroCity_DevonCorp_1F_Text_StaffGotRobbed, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_1F_EventScript_RocksMetalDisplay::
	msgbox RustboroCity_DevonCorp_1F_Text_RocksMetalDisplay, MSGBOX_SIGN
	end

RustboroCity_DevonCorp_1F_EventScript_ProductsDisplay::
	msgbox RustboroCity_DevonCorp_1F_Text_ProductDisplay, MSGBOX_SIGN
	end

RustboroCity_DevonCorp_1F_Text_WelcomeToDevonCorp:
	.string "Hola y bienvenido a la\n"
	.string "CORPORACIÓN DEVON.\p"
	.string "Somos orgullosos creadores de objetos\n"
	.string "y medicinas que mejoran tu vida.$"

RustboroCity_DevonCorp_1F_Text_StaffGotRobbed:
	.string "A un miembro del staff le robaron\n"
	.string "estúpidamente un paquete importante.$"

RustboroCity_DevonCorp_1F_Text_ThoseShoesAreOurProduct:
	.string "¡Oye, esas ZAPATILLAS DE CORRER!\n"
	.string "¡Son uno de nuestros productos!\p"
	.string "Me alegra ver a alguien usando\n"
	.string "algo que nosotros fabricamos.$"

RustboroCity_DevonCorp_1F_Text_RobberWasntVeryBright:
	.string "Ese paquete robado...\p"
	.string "Bueno, es importante, pero no es\n"
	.string "algo que cualquiera puede usar.\p"
	.string "Según yo, ese ladrón no debe\n"
	.string "haber sido muy listo.$"

RustboroCity_DevonCorp_1F_Text_SoundsLikeStolenGoodsRecovered:
	.string "Parece que han recuperado\n"
	.string "los PRODUCTOS DEVON robados.$"

RustboroCity_DevonCorp_1F_Text_OnlyAuthorizedPeopleEnter:
	.string "Lo siento, solo el personal\n"
	.string "autorizado puede entrar aquí.$"

RustboroCity_DevonCorp_1F_Text_HowCouldWeGetRobbed:
	.string "Es más que estúpido.\n"
	.string "¿Cómo pudieron robarnos?$"

RustboroCity_DevonCorp_1F_Text_YoureAlwaysWelcomeHere:
	.string "¡Hola!\n"
	.string "¡Siempre eres bienvenido aquí!$"

RustboroCity_DevonCorp_1F_Text_RocksMetalDisplay:
	.string "Hay muestras de rocas y metal\n"
	.string "en la vitrina de cristal.\p"
	.string "Hay un panel con un texto\n"
	.string "en ello…\p"
	.string "“DEVON CORPORATION comenzó como\n"
	.string "productor de piedras de canteras.\p"
	.string "“La empresa también producía hierro\n"
	.string "de limaduras de arena.\p"
	.string "“Desde ese humilde inicio como\n"
	.string "productor de materia prima, creció.\p"
	.string "“DEVON ahora fabrica una amplia\n"
	.string "gama de productos industriales.”$"

RustboroCity_DevonCorp_1F_Text_ProductDisplay:
	.string "Prototipos y pruebas llenan\n"
	.string "la vitrina de cristal.\p"
	.string "Hay un panel con una descripción…\p"
	.string "“Además de productos industriales,\n"
	.string "DEVON ahora vende artículos varios\l"
	.string "y fármacos para una mejor vida.\p"
	.string "“Hace poco, DEVON empezó a vender\n"
	.string "útiles para ENTRENADORES POKéMON,\l"
	.string "como POKé BALLS y el POKéNAV.”$"

