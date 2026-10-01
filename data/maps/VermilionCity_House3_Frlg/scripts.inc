VermilionCity_House3_Frlg_MapScripts::
	.byte 0

VermilionCity_House3_EventScript_Boy::
	msgbox VermilionCity_House3_Text_PidgeyFlyLetterToSaffron, MSGBOX_NPC
	end

VermilionCity_House3_EventScript_Lass::
	msgbox VermilionCity_House3_Text_SendMyPidgeyToUnionRoom, MSGBOX_NPC
	end

VermilionCity_House3_EventScript_Pidgey::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_PIDGEY, CRY_MODE_NORMAL
	msgbox VermilionCity_House3_Text_Pidgey
	waitmoncry
	release
	end

VermilionCity_House3_EventScript_Letter::
	msgbox VermilionCity_House3_Text_DearPippiLetter, MSGBOX_SIGN
	end

VermilionCity_House3_Text_PidgeyFlyLetterToSaffron::
	.string "Estoy haciendo que mi PIDGEY\n"
	.string "lleve una carta a PALDEA al norte.$"

VermilionCity_House3_Text_Pidgey::
	.string "PIDGEY: ¡Kurukkoo!$"

VermilionCity_House3_Text_DearPippiLetter::
	.string "Querida PIPPI,\n"
	.string "Espero verte pronto.\p"
	.string "Oí que AZULONA tiene problemas\n"
	.string "TEAM ROCKET.\p"
	.string "CARMEÍN parece estar segura.$"

VermilionCity_House3_Text_SendMyPidgeyToUnionRoom::
	.string "Quiero intercambiar CORREO con\n"
	.string "toda clase de personas.\p"
	.string "Envío mi PIDGEY a una SALA\n"
	.string "UNIÓN para cambiar CORREO por mí.$"

