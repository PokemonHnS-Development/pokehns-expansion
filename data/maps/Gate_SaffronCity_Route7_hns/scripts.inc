Gate_SaffronCity_Route7_hns_MapScripts::
	.byte 0

Gate_SaffronCity_Route7_EventScript_Guard::
	goto_if_set FLAG_RETURNED_MACHINE_PART, Gate_SaffronCity_Route7_EventScript_GuardReturnedPart
	msgbox Route7_Text_SaffronGuard_PowerPlant, MSGBOX_NPC
	end

Gate_SaffronCity_Route7_EventScript_GuardReturnedPart::
	msgbox Route7_Text_SaffronGuard_Serious, MSGBOX_NPC
	end

Route7_Text_SaffronGuard_PowerPlant:
	.string "¿Oíste sobre el accidente\n"
	.string "en la CENTRAL ELÉCTRICA?\p"
	.string "Está al este, muy cerca\n"
	.string "de PUEBLO LAVANDA.$"

Route7_Text_SaffronGuard_Serious:
	.string "Tomo en serio mi trabajo de guardia.\p"
	.string "¡Oye! Tienes una POKéDEX.\p"
	.string "Está bien. Puedes pasar.$"
