PewterCity_Gym_hns_MapScripts::
	.byte 0



PewterCity_Gym_EventScript_Jerry::
	trainerbattle_single TRAINER_JERRY_HNS, PewterCity_Gym_Text_CamperJerry_Seen, PewterCity_Gym_Text_CamperJerry_Beaten
	msgbox PewterCity_Gym_Text_CamperJerry_AfterBattle, MSGBOX_AUTOCLOSE
	end

PewterCity_Gym_EventScript_Brock::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_PEWTER_GYM, PewterCity_Gym_EventScript_Brock_Defeated
	msgbox PewterCity_Gym_Text_Brock_Intro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_BROCK_HNS, PewterCity_Gym_Text_Brock_WinLoss
	message PewterCity_Gym_Text_ReceivedBoulderBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox PewterCity_Gym_Text_Brock_GiveTM, MSGBOX_DEFAULT
	giveitem ITEM_TM_ROCK_SLIDE
	msgbox PewterCity_Gym_Text_Brock_ExplainTM, MSGBOX_DEFAULT
	setflag FLAG_BADGE09_GET
	setflag FLAG_DEFEATED_PEWTER_GYM
	addvar VAR_NUM_BADGES, 1
	setvar VAR_0x8008, 9
	call Common_EventScript_SetGymTrainers_hns
	clearflag FLAG_HIDE_DIGLETT_BROCK
	closemessage
	release
	end

PewterCity_Gym_EventScript_Brock_Defeated::
	goto_if_unset FLAG_HIDE_DOJO_BROCK, PewterCity_Gym_EventScript_Brock_Trade
	msgbox PewterCity_Gym_Text_Brock_FightDone, MSGBOX_DEFAULT
	closemessage
	release
	end


PewterCity_Gym_Text_Brock_Intro:
	.string "BROCK: Vaya, no es común recibir a un\n"
	.string "desafiante de JOHTO.\p"
	.string "Soy BROCK, LÍDER DEL GIMNASIO PEWTER.\p"
	.string "Soy experto en POKéMON tipo ROCA.\p"
	.string "Mis POKéMON resisten la mayoría de\n"
	.string "ataques físicos. Te costará mucho\l"
	.string "causarles algún daño.\p"
	.string "¡Vamos!$"

PewterCity_Gym_Text_Brock_WinLoss:
	.string "BROCK: Los fuertes ataques de tus\n"
	.string "superó mi defensa tan dura...\p"
	.string "Eres más fuerte de lo que esperaba...\p"
	.string "Toma, llévate esta MEDALLA.$"

PewterCity_Gym_Text_ReceivedBoulderBadge:
	.string "{PLAYER} recibió la MEDALLA ROCA.$"

PewterCity_Gym_Text_Brock_GiveTM:
	.string "Toma, llévate esta MT.$"

PewterCity_Gym_Text_Brock_ExplainTM:
	.string "Contiene AVALANCHA.\p"
	.string "Lanza rocas a los oponentes\n"
	.string "y puede hacer que retrocedan.\p"
	.string "Úsala para detenerlos en seco.$"

PewterCity_Gym_Text_Brock_BoulderBadge:
	.string "BROCK: {PLAYER}, gracias. Disfruté\n"
	.string "luchar contigo, aunque estoy un\l"
	.string "poco molesto.\p"
	.string "Esa MEDALLA ROCA hará que tus\n"
	.string "POKéMON sean más poderosos.$"

PewterCity_Gym_Text_Brock_FightDone:
	.string "BROCK: El mundo es enorme. Aún hay\n"
	.string "muchos entrenadores fuertes como tú.\p"
	.string "Solo espera y verás. Yo también\n"
	.string "me volveré mucho más fuerte.$"

PewterCity_Gym_Text_CamperJerry_Seen:
	.string "Los entrenadores de este GIMNASIO\n"
	.string "POKéMON planta.\p"
	.string "usan tipos ROCA. Tienen mucha DEF.\p"
	.string "Las batallas pueden durar mucho.\n"
	.string "¿Estás listo para esto?$"

PewterCity_Gym_Text_CamperJerry_Beaten:
	.string "Tengo que ganar estas...$"

PewterCity_Gym_Text_CamperJerry_AfterBattle:
	.string "¡Oye, tú! ¡Entrenador de JOHTO! BROCK\n"
	.string "es duro. Te castigará si no lo\l"
	.string "tomas en serio.$"

PewterCity_Gym_Text_Guide:
	.string "¡Hola! ¡Futuro CAMPEÓN! De verdad\n"
	.string "estás arrasando.\p"
	.string "¿Luchas contra los LÍDERES de\n"
	.string "KANTO?\p"
	.string "Son fuertes y dedicados,\n"
	.string "como los LÍDERES de JOHTO.$"

PewterCity_Gym_Text_Guide_Win:
	.string "¡Ey! ¡Futuro CAMPEÓN! Ese GIMNASIO\n"
	.string "no te dio muchos problemas.\p"
	.string "Tu forma de tomar el mando fue\n"
	.string "inspiradora. Lo digo en serio.$"

PewterCity_Gym_EventScript_GymGuy::
	goto_if_set FLAG_DEFEATED_PEWTER_GYM, PewterCity_Gym_EventScript_GymGuyAfter
	msgbox PewterCity_Gym_Text_Guide, MSGBOX_NPC
	end

PewterCity_Gym_EventScript_GymGuyAfter::
	msgbox PewterCity_Gym_Text_Guide_Win, MSGBOX_NPC
	end


PewterCity_Gym_EventScript_GymStatue::
	lockall
	goto_if_set FLAG_BADGE09_GET, PewterCity_Gym_EventScript_GymStatuePostVictory
	msgbox PewterCity_Gym_Text_GymStatue
	releaseall
	end

PewterCity_Gym_EventScript_GymStatuePostVictory::
	msgbox PewterCity_Gym_Text_GymStatuePlayerWon
	releaseall
	end

PewterCity_Gym_Text_GymStatue::
    .string "GIMNASIO POKéMON DE PIEDRA\n"
    .string "LÍDER: BROCK\p"
	.string "ENTRENADORES GANADORES:\n"
	.string "BLUE, RED$"

PewterCity_Gym_Text_GymStatuePlayerWon::
    .string "GIMNASIO POKéMON DE PIEDRA\n"
    .string "LÍDER: BROCK\p"
    .string "ENTRENADORES GANADORES:\n"
	.string "BLUE, RED, {PLAYER}$"

PewterCity_Gym_EventScript_Brock_Trade::
	goto_if_set FLAG_PEWTER_GYM_NPC_TRADE_COMPLETED, PewterCity_Gym_EventScript_BrockTradeCompleted
	ingame_trade INGAME_TRADE_BONSLY, PewterCity_Gym_Text_BrockWantToTrade, PewterCity_Gym_EventScript_BrockDeclineTrade, PewterCity_Gym_EventScript_BrockNotRequestedMon, PewterCity_Gym_Text_BrockTakeCare
	setflag FLAG_PEWTER_GYM_NPC_TRADE_COMPLETED
	release
	end

PewterCity_Gym_EventScript_BrockDeclineTrade::
	msgbox PewterCity_Gym_Text_BrockDeclineTrade, MSGBOX_DEFAULT
	release
	end

PewterCity_Gym_EventScript_BrockNotRequestedMon::
	bufferspeciesname STR_VAR_1, VAR_0x8009
	msgbox PewterCity_Gym_Text_BrockNotRequestedMon, MSGBOX_DEFAULT
	release
	end

PewterCity_Gym_EventScript_BrockTradeCompleted::
	msgbox PewterCity_Gym_Text_BrockTradeCompleted, MSGBOX_DEFAULT
	release
	end

PewterCity_Gym_Text_BrockWantToTrade:
	.string "BROCK: Hola, {PLAYER}. Hallé a este\n"
	.string "pequeño BONSLY entrenando en la\l"
	.string "montañas.\p"
	.string "Es lindo, pero creo que necesita\n"
	.string "un tipo de entrenador distinto.\p"
	.string "¿Cambiarías un {STR_VAR_1}?\n"
	.string "por mi {STR_VAR_2}?$"

PewterCity_Gym_Text_BrockTakeCare:
	.string "BROCK: ¡Gracias! ¡Cuida muy bien\n"
	.string "de WOODY por mí!$"

PewterCity_Gym_Text_BrockDeclineTrade:
	.string "BROCK: ¿No? No pasa nada.\n"
	.string "WOODY y yo seguiremos entrenando.$"

PewterCity_Gym_Text_BrockNotRequestedMon:
	.string "BROCK: Eso no es un {STR_VAR_1}.\n"
	.string "Eso no es lo que estoy buscando.$"

PewterCity_Gym_Text_BrockTradeCompleted:
	.string "BROCK: ¿Cómo le va a WOODY?\n¡Los BONSLY son más duros de\nlo que parecen!$"
