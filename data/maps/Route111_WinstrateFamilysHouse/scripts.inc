Route111_WinstrateFamilysHouse_MapScripts::
	.byte 0

Route111_WinstrateFamilysHouse_EventScript_Victor::
	lock
	faceplayer
	setvar VAR_0x8008, LOCALID_WINSTRATE_HOUSE_VICTOR
	msgbox Route111_WinstrateFamilysHouse_Text_MySonIsStrongerThanYou, MSGBOX_DEFAULT
	goto Route111_WinstrateFamilysHouse_EventScript_FaceOriginalDirection
	end

Route111_WinstrateFamilysHouse_EventScript_Victoria::
	lock
	faceplayer
	setvar VAR_0x8008, LOCALID_WINSTRATE_HOUSE_VICTORIA
	goto_if_set FLAG_RECEIVED_MACHO_BRACE, Route111_WinstrateFamilysHouse_EventScript_ReceivedMachoBrace
	msgbox Route111_WinstrateFamilysHouse_Text_LikeYouToHaveMachoBrace, MSGBOX_DEFAULT
	giveitem ITEM_MACHO_BRACE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_MACHO_BRACE
	goto Route111_WinstrateFamilysHouse_EventScript_FaceOriginalDirection
	end

Route111_WinstrateFamilysHouse_EventScript_ReceivedMachoBrace::
	msgbox Route111_WinstrateFamilysHouse_Text_PassionateAboutBattles, MSGBOX_DEFAULT
	goto Route111_WinstrateFamilysHouse_EventScript_FaceOriginalDirection
	end

Route111_WinstrateFamilysHouse_EventScript_Vivi::
	lock
	faceplayer
	setvar VAR_0x8008, LOCALID_WINSTRATE_HOUSE_VIVI
	msgbox Route111_WinstrateFamilysHouse_Text_StrongerFamilyMembers, MSGBOX_DEFAULT
	goto Route111_WinstrateFamilysHouse_EventScript_FaceOriginalDirection
	end

Route111_WinstrateFamilysHouse_EventScript_Vicky::
	lock
	faceplayer
	setvar VAR_0x8008, LOCALID_WINSTRATE_HOUSE_VICKY
	goto_if_set FLAG_TEMP_4, Route111_WinstrateFamilysHouse_EventScript_AlreadySpokenTo
	msgbox Route111_WinstrateFamilysHouse_Text_GrandsonStrong, MSGBOX_DEFAULT
	setflag FLAG_TEMP_4
	goto Route111_WinstrateFamilysHouse_EventScript_FaceOriginalDirection
	end

Route111_WinstrateFamilysHouse_EventScript_AlreadySpokenTo::
	msgbox Route111_WinstrateFamilysHouse_Text_GrandsonStrongShort, MSGBOX_DEFAULT
	goto Route111_WinstrateFamilysHouse_EventScript_FaceOriginalDirection
	end

Route111_WinstrateFamilysHouse_EventScript_FaceOriginalDirection::
	closemessage
	applymovement VAR_0x8008, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

Route111_WinstrateFamilysHouse_Text_MySonIsStrongerThanYou:
	.string "Eres el primer ENTRENADOR que veo\n"
	.string "usar POKéMON con tanta maestría.\p"
	.string "Pero debo decirte que mi hijo es\n"
	.string "más fuerte que tú.\p"
	.string "Incluso aceptó el desafío de la\n"
	.string "LIGA POKéMON, que lo sepas.$"

Route111_WinstrateFamilysHouse_Text_LikeYouToHaveMachoBrace:
	.string "Usamos este PRENTAFUERZAS para\n"
	.string "fortalecer mejor a nuestros\l"
	.string "POKéMON al entrenar.\p"
	.string "Como nos has vencido a todos,\n"
	.string "no sé si lo necesites, pero queremos\l"
	.string "darte nuestro PRENTAFUERZAS.$"

Route111_WinstrateFamilysHouse_Text_PassionateAboutBattles:
	.string "En las batallas POKéMON,\n"
	.string "solemos ser muy apasionados.$"

Route111_WinstrateFamilysHouse_Text_StrongerFamilyMembers:
	.string "Mamá es más fuerte que Papá.\p"
	.string "Yo soy más fuerte que Mamá.\p"
	.string "¡Y la abuela es más fuerte que yo!\p"
	.string "Pero mi hermano mayor es aún más\n"
	.string "fuerte que la abuela.$"

Route111_WinstrateFamilysHouse_Text_GrandsonStrong:
	.string "No hay duda de que eres fuerte.\p"
	.string "Pero si lucharas con mi nieto,\n"
	.string "terminarías llorando de rabia.\p"
	.string "Es más fuerte que cualquier\n"
	.string "our family knows.\p"
	.string "Ya debe estar desafiando al\n"
	.string "CAMPEÓN de la LIGA POKéMON.\p"
	.string "Conociendo a mi nieto, ¡podría ser\n"
	.string "el CAMPEÓN ahora mismo!$"

Route111_WinstrateFamilysHouse_Text_GrandsonStrongShort:
	.string "Mi nieto ya debe estar desafiando al\n"
	.string "CAMPEÓN de la LIGA POKéMON.\p"
	.string "Conociendo a mi nieto, ¡podría ser\n"
	.string "el CAMPEÓN ahora mismo!$"

