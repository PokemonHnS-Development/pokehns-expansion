FuchsiaCity_House1_Frlg_MapScripts::
	.byte 0

FuchsiaCity_House1_EventScript_Woman::
	msgbox FuchsiaCity_House1_Text_WardenIsOldHasFalseTeeth, MSGBOX_NPC
	end

FuchsiaCity_House1_EventScript_OldMan::
	lock
	faceplayer
	famechecker FAMECHECKER_BILL, 2
	msgbox FuchsiaCity_House1_Text_BillIsMyGrandson
	release
	end

FuchsiaCity_House1_EventScript_LittleBoy::
	msgbox FuchsiaCity_House1_Text_BillFilesHisOwnMonData, MSGBOX_NPC
	end

FuchsiaCity_House1_Text_WardenIsOldHasFalseTeeth::
	.string "El GUARDA de la ZONA SAFARI es\n"
	.string "anciano, pero sigue muy activo.\p"
	.string "aunque todos sus dientes son falsos.$"

FuchsiaCity_House1_Text_BillIsMyGrandson::
	.string "¿Mmm?\n"
	.string "¿Conoces a BILL?\p"
	.string "¡Es mi nieto!\p"
	.string "Siempre le gustó coleccionar cosas,\n"
	.string "¡incluso de niño!$"

FuchsiaCity_House1_Text_BillFilesHisOwnMonData::
	.string "BILL files his own POKéMON data on\n"
	.string "su PC.\p"
	.string "¿Te lo mostró?$"

