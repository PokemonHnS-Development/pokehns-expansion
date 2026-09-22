CeladonCity_Apartments_2F_hns_MapScripts::
	.byte 0

CeladonCity_Apartments_2F_EventScript_Computer::
	lock
	playse SE_PC_ON
	msgbox CeladonMansion2F_Text_Computer
	playse SE_PC_OFF
	waitse
	release
	end

CeladonCity_Apartments_2F_EventScript_Sign::
	msgbox CeladonMansion2F_Text_DevOfficeSign, MSGBOX_SIGN
	end

CeladonMansion2F_Text_Computer:
	.string "{PLAYER} encendió la PC.\p"
	.string "...\p"
	.string "Alguien estaba escribiendo\n"
	.string "un correo electrónico.\p"
	.string "...Espero que visites KANTO.\p"
	.string "Creo que te sorprenderá\n"
	.string "cuánto han cambiado las cosas.\p"
	.string "Verás muchos POKéMON que\n"
	.string "no son nativos de JOHTO.\p"
	.string "Para el PRODUCTOR\p"
	.string "...$"

CeladonMansion2F_Text_DevOfficeSign:
	.string "HEART & SOUL DEVELOPMENT OFFICE$"

CeladonMansion2F_EventScript_LilDill::
	msgbox CeladonMansion2F_Text_LilDill, MSGBOX_NPC
	end

CeladonMansion2F_EventScript_InfiniteBacon::
	msgbox CeladonMansion2F_Text_InfiniteBacon, MSGBOX_NPC
	end

CeladonMansion2F_EventScript_TixoRebel::
	msgbox CeladonMansion2F_Text_TixoRebel, MSGBOX_NPC
	end

CeladonMansion2F_EventScript_Phant::
	msgbox CeladonMansion2F_Text_Phant, MSGBOX_NPC
	end

CeladonMansion2F_EventScript_Exclsior::
	msgbox CeladonMansion2F_Text_Exclsior, MSGBOX_NPC
	end

CeladonMansion2F_EventScript_DaniRainbow::
    msgbox CeladonMansion2F_Text_DaniRaibow, MSGBOX_NPC
    end

CeladonMansion2F_Text_LilDill:
	.string "Hola a todos, Parche 15--\p"
	.string "Perdón, quiero decir...\p"
	.string "¡Hola! ¡Soy el DIRECTOR DEL JUEGO!\p"
	.string "Hice los mapas, los tilesets, los\n"
	.string "scripts y mucho más.\p"
	.string "Pero no lo habría logrado sin\n"
	.string "los otros devs y los playtesters.\p"
	.string "¡Gracias por jugar! Espero que\n"
	.string "disfrutes POKéMON HEART & SOUL.$"

CeladonMansion2F_Text_InfiniteBacon:
	.string "¡Estamos trabajando para rehacerlo\n"
	.string "en pokeemerald expansion!$"

CeladonMansion2F_Text_TixoRebel:
	.string "¿Has oído hablar de THE EGGENING?\n"
	.string "Fue un error del playtest que\l"
	.string "cambiaba POKéMON al azar por\l"
	.string "¡HUEVOS!\p"
	.string "¡Desarrollé la solución!$"

CeladonMansion2F_Text_Phant:
	.string "¡Amo los DEMAKES!\p"
	.string "¿Has jugado SWORD AND SHIELD\n"
	.string "ULTIMATE PLUS - ENGLISH?\l"
	.string "¡Yo lo traduje!\p"
	.string "Para mi próximo DEMAKE, creo que\n"
	.string "¡haré ALOLA!$"

CeladonMansion2F_Text_Exclsior:
	.string "¡Implementé sprites de surf\n"
	.string "únicos para cada POKéMON!\p"
	.string "Como el proyecto es OPEN SOURCE,\n"
	.string "¡tú también puedes añadir cosas!$"

CeladonMansion2F_Text_DaniRaibow:
	.string "Hi!\p"
	.string "Soy muy bueno hallando problemas,\n"
	.string "y puedo arreglar los pequeños.\p"
    .string "¿Quieres oír un chiste?\p"
    .string "Lance intentó enseñarle a DRAGONITE\n"
    .string "el movimiento ALIENTO DRAGÓN.\p"
    .string "Pero DRAGONITE iba muy rápido con\n"
    .string "EXTREMESPEED; ¡no podía\l"
    .string "atraparlo!$"
