EventScript_StartDexNavBattle::
	lock
	playse SE_PIN
	applymovement OBJ_EVENT_ID_PLAYER Common_Movement_ExclamationMark
	waitmovement 0
	waitse
	dowildbattle	
	release
	end

EventScript_NotFoundNearby::
	msgbox sText_NotFoundNearby, MSGBOX_SIGN
	end

EventScript_MovedTooFast::
	msgbox sText_TryMovingSlower, MSGBOX_SIGN
	end

EventScript_PokemonGotAway::
	msgbox sText_PokemonGotAway, MSGBOX_SIGN
	end

EventScript_LostSignal::
	msgbox sText_LostSignal, MSGBOX_SIGN
	end

EventScript_TooDark::
	msgbox sText_TooDark, MSGBOX_SIGN
	end

sText_NotFoundNearby:
	.string "No se encontró nada cerca.\n"
	.string "¡Busca en otra zona!$"

sText_TryMovingSlower:
	.string "¡El POKéMON huyó!\n"
	.string "Intenta moverte más lento.$"

sText_PokemonGotAway:
	.string "¡El POKéMON huyó!$"

sText_LostSignal:
	.string "No hay reacción.\n"
	.string "¡Se perdió la señal!$"

sText_TooDark:
	.string "Está muy oscuro para buscar\nun POKéMON!$"
