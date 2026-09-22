SSAnne_Kitchen_Frlg_MapScripts::
	.byte 0

SSAnne_Kitchen_EventScript_Chef1::
	msgbox SSAnne_Kitchen_Text_BusyOutOfTheWay, MSGBOX_NPC
	end

SSAnne_Kitchen_EventScript_Chef2::
	msgbox SSAnne_Kitchen_Text_SawOddBerryInTrash, MSGBOX_NPC
	end

SSAnne_Kitchen_EventScript_Chef3::
	msgbox SSAnne_Kitchen_Text_SoBusyImDizzy, MSGBOX_NPC
	end

SSAnne_Kitchen_EventScript_Chef4::
	lock
	faceplayer
	msgbox SSAnne_Kitchen_Text_IAmLeChefMainCourseIs
	random 3
	copyvar VAR_0x8008, VAR_RESULT
	call_if_eq VAR_0x8008, 0, SSAnne_Kitchen_EventScript_SalmonDuSalad
	call_if_eq VAR_0x8008, 1, SSAnne_Kitchen_EventScript_EelsAuBarbecue
	call_if_eq VAR_0x8008, 2, SSAnne_Kitchen_EventScript_PrimeBeefsteak
	release
	end

SSAnne_Kitchen_EventScript_SalmonDuSalad::
	msgbox SSAnne_Kitchen_Text_SalmonDuSalad
	return

SSAnne_Kitchen_EventScript_EelsAuBarbecue::
	msgbox SSAnne_Kitchen_Text_EelsAuBarbecue
	return

SSAnne_Kitchen_EventScript_PrimeBeefsteak::
	msgbox SSAnne_Kitchen_Text_PrimeBeefsteak
	return

SSAnne_Kitchen_EventScript_Chef5::
	msgbox SSAnne_Kitchen_Text_PeelSpudsEveryDay, MSGBOX_NPC
	end

SSAnne_Kitchen_EventScript_Chef6::
	msgbox SSAnne_Kitchen_Text_HearAboutSnorlaxItsAGlutton, MSGBOX_NPC
	end

SSAnne_Kitchen_EventScript_Chef7::
	msgbox SSAnne_Kitchen_Text_OnlyGetToPeelOnions, MSGBOX_NPC
	end

SSAnne_Kitchen_Text_BusyOutOfTheWay::
	.string "¡Tú, mon petit!\n"
	.string "¡Estamos ocupados!\l"
	.string "¡Quítate de en medio!$"

SSAnne_Kitchen_Text_SawOddBerryInTrash::
	.string "basura.\n"
	.string "¿Qué sería eso?$"

SSAnne_Kitchen_Text_SoBusyImDizzy::
	.string "I'm so busy I'm getting dizzy!\n"
	.string "¡Debes darme espacio aquí!$"

SSAnne_Kitchen_Text_PeelSpudsEveryDay::
	.string "Hum-de-hum-de-ho...\p"
	.string "I peel spuds every day!\n"
	.string "Hum-hum...$"

SSAnne_Kitchen_Text_HearAboutSnorlaxItsAGlutton::
	.string "¿Oíste hablar de SNORLAX?\n"
	.string "Es un glotón.\p"
	.string "No other POKéMON eats and sleeps\n"
	.string "¡como puede y lo hace SNORLAX!$"

SSAnne_Kitchen_Text_OnlyGetToPeelOnions::
	.string "Snivel... Sniff...\p"
	.string "Solo puedo pelar cebollas...\n"
	.string "Snif...$"

SSAnne_Kitchen_Text_IAmLeChefMainCourseIs::
	.string "Er-hem!\n"
	.string "Indeed I am le CHEF!\p"
	.string "El plato principal es$"

SSAnne_Kitchen_Text_SalmonDuSalad::
	.string "Salmon du Salad!\p"
	.string "Los invitados pueden quejarse\n"
	.string "again, however!$"

SSAnne_Kitchen_Text_EelsAuBarbecue::
	.string "Eels au Barbecue!\p"
	.string "de que es pescado, temo motín.$"

SSAnne_Kitchen_Text_PrimeBeefsteak::
	.string "Prime Beefsteak!\p"
	.string "Pero, ¿tengo suficientes filetes\n"
	.string "beef?$"

