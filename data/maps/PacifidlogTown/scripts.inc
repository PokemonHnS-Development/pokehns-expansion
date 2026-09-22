PacifidlogTown_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, PacifidlogTown_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, PacifidlogTown_OnResume
	.byte 0

PacifidlogTown_OnTransition:
	setflag FLAG_VISITED_PACIFIDLOG_TOWN
	end

PacifidlogTown_OnResume:
	setstepcallback STEP_CB_PACIFIDLOG_BRIDGE
	end

PacifidlogTown_EventScript_NinjaBoy::
	msgbox PacifidlogTown_Text_NeatHousesOnWater, MSGBOX_NPC
	end

PacifidlogTown_EventScript_Girl::
	msgbox PacifidlogTown_Text_FastRunningCurrent, MSGBOX_NPC
	end

PacifidlogTown_EventScript_Fisherman::
	msgbox PacifidlogTown_Text_SkyPillarTooScary, MSGBOX_NPC
	end

PacifidlogTown_EventScript_TownSign::
	msgbox PacifidlogTown_Text_TownSign, MSGBOX_SIGN
	end

PacifidlogTown_Text_FastRunningCurrent:
	.string "El mar entre PACIFIDLOG y\n"
	.string "SLATEPORT tiene mareas rápidas.\p"
	.string "Si decides usar SURF, podrías\n"
	.string "terminar en otro lugar.$"

PacifidlogTown_Text_NeatHousesOnWater:
	.string "Mira, ¿no es genial?\n"
	.string "¡Estas casas están sobre el agua!\p"
	.string "¡Yo nací aquí!$"

PacifidlogTown_Text_SkyPillarTooScary:
	.string "¿El SKY PILLAR?\p"
	.string "...Oh, debes referirte a esa torre\n"
	.string "tan alta que está más allá.\p"
	.string "Yo que tú, no subiría.\n"
	.string "Da miedo subir tan alto.\p"
	.string "La vida a nivel del mar en\n"
	.string "me parece perfecta.$"

PacifidlogTown_Text_TownSign:
	.string "PUEBLO PACIFIDLOG\p"
	.string "“Donde el sol de la mañana sonríe\n"
	.string "sobre las aguas.”$"

