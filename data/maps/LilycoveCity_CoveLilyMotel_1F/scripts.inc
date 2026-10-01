LilycoveCity_CoveLilyMotel_1F_MapScripts::
	.byte 0

LilycoveCity_CoveLilyMotel_1F_EventScript_MotelOwner::
	lockall
	goto_if_set FLAG_SYS_GAME_CLEAR, LilycoveCity_CoveLilyMotel_1F_EventScript_GameClear
	goto_if_set FLAG_BADGE07_GET, LilycoveCity_CoveLilyMotel_1F_EventScript_AquaHideoutBusted
	msgbox LilycoveCity_CoveLilyMotel_1F_Text_GuestsDoubledByMascot, MSGBOX_DEFAULT
	applymovement LOCALID_MOTEL_OWNER, Common_Movement_FacePlayer
	waitmovement 0
	msgbox LilycoveCity_CoveLilyMotel_1F_Text_NoGuestsWithTeamAqua, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_MOTEL_OWNER, Common_Movement_FaceOriginalDirection
	waitmovement 0
	releaseall
	end

LilycoveCity_CoveLilyMotel_1F_EventScript_AquaHideoutBusted::
	msgbox LilycoveCity_CoveLilyMotel_1F_Text_MonFoundLostItem, MSGBOX_DEFAULT
	applymovement LOCALID_MOTEL_OWNER, Common_Movement_FacePlayer
	waitmovement 0
	msgbox LilycoveCity_CoveLilyMotel_1F_Text_HeardAquaHideoutBusted, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_MOTEL_OWNER, Common_Movement_FaceOriginalDirection
	waitmovement 0
	releaseall
	end

LilycoveCity_CoveLilyMotel_1F_EventScript_GameClear::
	msgbox LilycoveCity_CoveLilyMotel_1F_Text_HouseSittingMonCaughtBurglar, MSGBOX_DEFAULT
	applymovement LOCALID_MOTEL_OWNER, Common_Movement_FacePlayer
	waitmovement 0
	msgbox LilycoveCity_CoveLilyMotel_1F_Text_BetterGetWorkingOnGuestsDinner, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_MOTEL_OWNER, Common_Movement_FaceOriginalDirection
	waitmovement 0
	releaseall
	end

LilycoveCity_CoveLilyMotel_1F_EventScript_BlockingTV::
	lockall
	playse SE_PIN
	applymovement LOCALID_MOTEL_OWNER, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_MOTEL_OWNER, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox LilycoveCity_CoveLilyMotel_1F_Text_CantSeeTheTV, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, LilycoveCity_CoveLilyMotel_1F_Movement_PlayerPushFromTV
	applymovement LOCALID_MOTEL_OWNER, LilycoveCity_CoveLilyMotel_1F_Movement_OwnerPushPlayer
	waitmovement 0
	applymovement LOCALID_MOTEL_OWNER, LilycoveCity_CoveLilyMotel_1F_Movement_OwnerReturn
	waitmovement 0
	release
	end

LilycoveCity_CoveLilyMotel_1F_Movement_PlayerPushFromTV:
	face_right
	lock_facing_direction
	walk_left
	unlock_facing_direction
	step_end

LilycoveCity_CoveLilyMotel_1F_Movement_OwnerPushPlayer:
	walk_up
	step_end

LilycoveCity_CoveLilyMotel_1F_Movement_OwnerReturn:
	face_down
	walk_down
	face_up
	step_end

LilycoveCity_CoveLilyMotel_1F_Text_GuestsDoubledByMascot:
	.string "Hm, ¿así que duplicaron los huéspedes\n"
	.string "usando POKéMON como atracción?\p"
	.string "Hm, tal vez debería poner a un\n"
	.string "POKéMON lindo como mascota del hotel.\p"
	.string "¿Me pregunto si eso atraerá a más\n"
	.string "huéspedes para que se queden?$"

LilycoveCity_CoveLilyMotel_1F_Text_NoGuestsWithTeamAqua:
	.string "¡Oh, perdón, perdón!\n"
	.string "¡Estaba muy concentrado viendo la TV!\p"
	.string "Desde que el TEAM AQUA llegó aquí,\n"
	.string "los turistas han dejado de venir.$"

LilycoveCity_CoveLilyMotel_1F_Text_CantSeeTheTV:
	.string "¡Oye, quítate de delante!\n"
	.string "¡No puedo ver la TV!$"

LilycoveCity_CoveLilyMotel_1F_Text_MonFoundLostItem:
	.string "¡Increíble! ¿Me dices que un POKéMON\n"
	.string "halló el objeto perdido de alguien?\p"
	.string "Eso es algo. Si tuviéramos POKéMON\n"
	.string "tan inteligentes como ese...\p"
	.string "podríamos recuperar cualquier cosa\n"
	.string "que los huéspedes extravíen...$"

LilycoveCity_CoveLilyMotel_1F_Text_HeardAquaHideoutBusted:
	.string "¡Oh, perdón, perdón!\n"
	.string "¡Estaba muy concentrado viendo la TV!\p"
	.string "Oí que alguien desmanteló la\n"
	.string "GUARIDA del TEAM AQUA.\p"
	.string "Gracias a eso, acabamos de recibir\n"
	.string "una reserva de un grupo grande.\p"
	.string "Era una empresa llamada... eh...\n"
	.string "GAME algo...$"

LilycoveCity_CoveLilyMotel_1F_Text_HouseSittingMonCaughtBurglar:
	.string "¡Increíble! Un POKéMON cuidador\n"
	.string "¿atrapó a un ladrón?\p"
	.string "Eso es algo. Si tuviéramos un\n"
	.string "POKéMON fuerte de seguridad...\p"
	.string "Podríamos dar a nuestros huéspedes\n"
	.string "una mayor seguridad.$"

LilycoveCity_CoveLilyMotel_1F_Text_BetterGetWorkingOnGuestsDinner:
	.string "¡Oh, perdón, perdón!\n"
	.string "Estaba muy distraído viendo la TV.\p"
	.string "Ah, sí. Un grupo grande de huéspedes\n"
	.string "llegó hace poco.\p"
	.string "Se registraron como GAME FREAK,\n"
	.string "así que creo que hacen juegos.\p"
	.string "Uh-oh, mejor me pongo a trabajar\n"
	.string "¡su cena!$"

