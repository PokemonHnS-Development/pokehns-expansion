CliffEdgeGate_hns_MapScripts::
	.byte 0

CliffEdgeGate_EventScript_Woman::
	lock
	faceplayer
	msgbox CliffEdgeGate_Text_IntroOpen, MSGBOX_DEFAULT
	closemessage
	release
	end

CliffEdgeGate_EventScript_Picnicker::
	lock
	faceplayer
	msgbox CliffEdgeGate_Text_Expectations, MSGBOX_DEFAULT
	closemessage
	release
	end

CliffEdgeGate_Text_IntroOpen:
	.string "¿Sabías que hay una ZONA SAFARI\n"
	.string "aquí mismo a la vuelta?\p"
	.string "¡Es muy divertida!\n"
	.string "Verás muchos tipos diferentes de\l"
	.string "POKéMON, ¡y puedes atraparlos todos!\p"
	.string "No hay razón para no ir, ¿verdad?\n"
	.string "Aquí mismo a la vuelta.$"

CliffEdgeGate_Text_Expectations:
	.string "Agradezco que todos tengan tantas\n"
	.string "ganas de ir.\p"
	.string "Pero la recepcionista parece\n"
	.string "demasiado dramática...\p"
	.string "¡No te hagas demasiadas ilusiones!$"

CliffEdgeGate_EventScript_CaveSign::
	lock
	msgbox CliffEdgeGate_Text_SignOpen, MSGBOX_SIGN
	closemessage
	release
	end

CliffEdgeGate_Text_SignOpen:
	.string "¡Todo es emocionante!\n"
	.string "¡Explora para hallar POKéMON!\l"
	.string "ZONA SAFARI del Guardián BAOBA\l"
	.string "¡Ya está funcionando!$"

