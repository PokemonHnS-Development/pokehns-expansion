MauvilleCity_House1_MapScripts::
	.byte 0

MauvilleCity_House1_EventScript_RockSmashDude::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_HM_ROCK_SMASH, MauvilleCity_House1_EventScript_ReceivedRockSmash
	msgbox MauvilleCity_House1_Text_ImRockSmashDudeTakeThis, MSGBOX_DEFAULT
	giveitem ITEM_HM_ROCK_SMASH
	setflag FLAG_RECEIVED_HM_ROCK_SMASH
	setflag FLAG_HIDE_ROUTE_111_ROCK_SMASH_TIP_GUY
	msgbox MauvilleCity_House1_Text_ExplainRockSmash, MSGBOX_DEFAULT
	release
	end

MauvilleCity_House1_EventScript_ReceivedRockSmash::
	msgbox MauvilleCity_House1_Text_MonCanFlyOutOfSmashedRock, MSGBOX_DEFAULT
	release
	end

MauvilleCity_House1_Text_ImRockSmashDudeTakeThis:
	.string "¡Yujuu!\p"
	.string "Dicen que soy el TIPO ROCA ROMPER,\n"
	.string "pero me parece algo degradante.\p"
	.string "Creo que merezco más respeto,\n"
	.string "como el TIPO ROCA ROMPER GENIAL.\p"
	.string "¡Yujuu!\p"
	.string "En fin, tus POKéMON se ven bien.\n"
	.string "increíblemente fuertes.\p"
	.string "¡Me gusta eso!\n"
	.string "¡Toma esta MO!$"

MauvilleCity_House1_Text_ExplainRockSmash:
	.string "Esa MO contiene ROCA ROMPER.\p"
	.string "Si te encuentras rocas grandes\n"
	.string "que bloqueen tu camino...\p"
	.string "bueno, usa esa MO y rompe\n"
	.string "¡quítalos de tu camino!\p"
	.string "¡Sí, señor! ¡Rompamos rocas!\n"
	.string "¡Yuju!$"

MauvilleCity_House1_Text_MonCanFlyOutOfSmashedRock:
	.string "Sí, si rompes una roca, un POKéMON\n"
	.string "podría salir volando de su escondite.\p"
	.string "¡Yuju!$"

