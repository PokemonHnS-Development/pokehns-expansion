ViridianCity_Gym_hns_MapScripts::
	.byte 0

ViridianCity_Gym_EventScript_Blue::
	lock
	faceplayer
	goto_if_unset FLAG_HIDE_DOJO_BLUE, ViridianCity_Gym_EventScript_BlueAtDojo
	goto_if_set FLAG_DEFEATED_VIRIDIAN_GYM, ViridianCity_Gym_EventScript_BlueGotoDojo
	goto_if_set FLAG_DEFEATED_VIRIDIAN_GYM, ViridianCity_Gym_EventScript_Blue_Defeated
	msgbox ViridianCity_Gym_Text_LeaderBlue_Before, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_BLUE_HNS, ViridianCity_Gym_Text_LeaderBlue_Win
	message ViridianCity_Gym_Text_ReceivedEarthBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox ViridianCity_Gym_Text_LeaderBlue_After, MSGBOX_DEFAULT
	msgbox ViridianCity_Gym_Text_LeaderBlue_GiveTM, MSGBOX_DEFAULT
	giveitem ITEM_TM_TRICK_ROOM
	msgbox ViridianCity_Gym_Text_LeaderBlue_ExplainTM, MSGBOX_DEFAULT
	setflag FLAG_BADGE16_GET
	setflag FLAG_DEFEATED_VIRIDIAN_GYM
	addvar VAR_NUM_BADGES, 1
	setvar VAR_0x8008, 16
	call Common_EventScript_SetGymTrainers_hns
	closemessage
	setflag FLAG_HIDE_LEAGUE_BLACKBELT
	setflag FLAG_HIDE_SEAFOAM_BLAINE
	clearflag FLAG_HIDE_CINNABAR_BLAINE
	setvar VAR_OAK_MT_SILVER_CALL, 1
	release
	end

ViridianCity_Gym_EventScript_Blue_Defeated::
	msgbox ViridianCity_Gym_Text_LeaderBlue_Epilogue, MSGBOX_DEFAULT
	closemessage
	release
	end

ViridianCity_Gym_EventScript_BlueGotoDojo::
	msgbox ViridianCity_Gym_Text_BlueGotoDojo, MSGBOX_DEFAULT
	closemessage
	clearflag FLAG_HIDE_DOJO_BLUE
	release
	end

ViridianCity_Gym_Text_BlueGotoDojo:
	.string "BLUE: ¿Ya volviste por más?\p"
	.string "Si quieres otra oportunidad,\n"
	.string "¡ve al DOJO DE LUCHA!$"

ViridianCity_Gym_EventScript_BlueAtDojo::
	msgbox ViridianCity_Gym_Text_LeaderBlue_Epilogue, MSGBOX_DEFAULT
	closemessage
	release
	end

ViridianCity_Gym_Text_LeaderBlue_Before:
	.string "BLUE: ¡Ey! Al fin llegaste, ¿eh?\p"
	.string "No tenía ganas en ISLA CANELA,\p"
	.string "pero ahora estoy listo para luchar.\p"
	.string "…\p"
	.string " ¿Me dices que venciste a todos\n"
	.string "los GIMNASIOS de JOHTO?\p"
	.string "¡Je! Los GIMNASIOS de JOHTO deben\n"
	.string "ser patéticos entonces.\p"
	.string "Oye, no te preocupes por eso.\p"
	.string "Sabré si eres bueno o no al\n"
	.string "luchando contra ti ahora.\p"
	.string "¿Listo, CAMPEÓN DE JOHTO?$"

ViridianCity_Gym_Text_LeaderBlue_Win:
	.string "BLUE: ¿Qué?\p"
	.string "¿Cómo rayos pude perder contigo?\p"
	.string "…\p"
	.string "Tch, está bien... Toma esto, es la\n"
	.string "MEDALLA TIERRA.$"

ViridianCity_Gym_Text_ReceivedEarthBadge:
	.string "{PLAYER} recibió la MEDALLA TIERRA.$"

ViridianCity_Gym_Text_LeaderBlue_After:
	.string "BLUE: ...\p"
	.string "Está bien, me equivoqué. Eres el\n"
	.string "verdadero campeón. Eres muy bueno.\p"
	.string "Pero algún día te derrotaré.\p"
	.string "¡No lo olvides!$"

ViridianCity_Gym_Text_LeaderBlue_GiveTM:
	.string "Llévate esto contigo.$"

ViridianCity_Gym_Text_LeaderBlue_ExplainTM:
	.string "Eso es ESPACIO RARO.\pEn combate cambiará la Velocidad.\nPrimero el lento. Último el rápido.\pÚsalo para dar vuelta al combate.$"

ViridianCity_Gym_Text_LeaderBlue_Epilogue:
	.string "BLUE: Escucha bien.\p"
	.string "Más vale que no pierdas hasta que\n"
	.string "yo te venza. ¿Entendido?$"


ViridianCity_Gym_EventScript_GymGuy::
	goto_if_set FLAG_DEFEATED_VIRIDIAN_GYM, ViridianCity_Gym_EventScript_GymGuyAfter
	msgbox ViridianCity_Gym_Text_Guide, MSGBOX_NPC
	end

ViridianCity_Gym_EventScript_GymGuyAfter::
	msgbox ViridianCity_Gym_Text_Guide_Win, MSGBOX_NPC
	end

ViridianCity_Gym_Text_Guide:
	.string "¡Hola, futuro CAMPEÓN!\p"
	.string "¿Cómo va todo? Parece que estás\n"
	.string "en racha.\p"
	.string "El LÍDER de GIMNASIO luchó contra\n"
	.string "el CAMPEÓN hace tres años.\p"
	.string "No es ningún novato.\p"
	.string "¡Da todo lo que tengas!$"

ViridianCity_Gym_Text_Guide_Win:
	.string "Vaya, eres realmente fuerte...\p"
	.string "Eso fue muy inspirador\n"
	.string "Se me saltaron las lágrimas.$"


ViridianCity_Gym_EventScript_GymStatue::
	lockall
	goto_if_set FLAG_BADGE16_GET, ViridianCity_Gym_EventScript_GymStatuePostVictory
	msgbox ViridianCity_Gym_Text_GymStatue
	releaseall
	end

ViridianCity_Gym_EventScript_GymStatuePostVictory::
	msgbox ViridianCity_Gym_Text_GymStatuePlayerWon
	releaseall
	end

ViridianCity_Gym_Text_GymStatue::
    .string "GIMNASIO POKéMON VERDIANA\n"
    .string "LÍDER: BLUE\p"
	.string "ENTRENADORES GANADORES:\n"
	.string "BLUE, RED$"

ViridianCity_Gym_Text_GymStatuePlayerWon::
    .string "GIMNASIO POKéMON VERDIANA\n"
    .string "LÍDER: BLUE\p"
    .string "ENTRENADORES GANADORES:\n"
	.string "BLUE, RED, {PLAYER}$"

