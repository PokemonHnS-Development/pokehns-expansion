MtPyre_Summit_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MtPyre_Summit_OnTransition
	.byte 0

MtPyre_Summit_OnTransition:
	call_if_eq VAR_MT_PYRE_STATE, 2, MtPyre_Summit_EventScript_SetArchieMaxiePositions
	end

MtPyre_Summit_EventScript_SetArchieMaxiePositions::
	setobjectxyperm LOCALID_MT_PYRE_SUMMIT_MAXIE, 23, 6
	setobjectxyperm LOCALID_MT_PYRE_SUMMIT_ARCHIE, 22, 6
	end

MtPyre_Summit_EventScript_TeamAquaTrigger0::
	lockall
	setvar VAR_0x8008, 0
	goto MtPyre_Summit_EventScript_TeamAquaExits
	end

MtPyre_Summit_EventScript_TeamAquaTrigger1::
	lockall
	setvar VAR_0x8008, 1
	goto MtPyre_Summit_EventScript_TeamAquaExits
	end

MtPyre_Summit_EventScript_TeamAquaTrigger2::
	lockall
	setvar VAR_0x8008, 2
	goto MtPyre_Summit_EventScript_TeamAquaExits
	end

MtPyre_Summit_EventScript_TeamAquaExits::
	playbgm MUS_ENCOUNTER_AQUA, FALSE
	applymovement LOCALID_PLAYER, Common_Movement_FaceUp
	waitmovement 0
	applymovement LOCALID_MT_PYRE_SUMMIT_ARCHIE, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	delay 50
	call_if_eq VAR_0x8008, 0, MtPyre_Summit_EventScript_ArchieFacePlayer0
	call_if_eq VAR_0x8008, 1, MtPyre_Summit_EventScript_ArchieFacePlayer1
	call_if_eq VAR_0x8008, 2, MtPyre_Summit_EventScript_ArchieFacePlayer2
	msgbox MtPyre_Summit_Text_ArchieWeGotTheOrbLetsGo, MSGBOX_DEFAULT
	closemessage
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_MT_PYRE_SUMMIT_ARCHIE
	removeobject LOCALID_MT_PYRE_SUMMIT_GRUNT_1
	removeobject LOCALID_MT_PYRE_SUMMIT_GRUNT_2
	removeobject LOCALID_MT_PYRE_SUMMIT_GRUNT_3
	removeobject LOCALID_MT_PYRE_SUMMIT_GRUNT_4
	setflag FLAG_HIDE_MT_PYRE_SUMMIT_ARCHIE
	setflag FLAG_HIDE_MT_PYRE_SUMMIT_TEAM_AQUA
	fadedefaultbgm
	fadescreenswapbuffers FADE_FROM_BLACK
	delay 20
	setvar VAR_MT_PYRE_STATE, 1
	call_if_eq VAR_0x8008, 0, MtPyre_Summit_EventScript_OldLadyApproachPlayer0
	call_if_eq VAR_0x8008, 1, MtPyre_Summit_EventScript_OldLadyApproachPlayer1
	call_if_eq VAR_0x8008, 2, MtPyre_Summit_EventScript_OldLadyApproachPlayer2
	msgbox MtPyre_Summit_Text_BothOrbsTakenMagmaLeftThis, MSGBOX_DEFAULT
	giveitem ITEM_MAGMA_EMBLEM
	setflag FLAG_RECEIVED_RED_OR_BLUE_ORB
	setflag FLAG_HIDE_JAGGED_PASS_MAGMA_GUARD
	releaseall
	end

MtPyre_Summit_EventScript_ArchieFacePlayer0::
	applymovement LOCALID_MT_PYRE_SUMMIT_ARCHIE, MtPyre_Summit_Movement_ArchieFacePlayer0
	waitmovement 0
	return

@ Archie is already facing player
MtPyre_Summit_EventScript_ArchieFacePlayer1::
	return

MtPyre_Summit_EventScript_ArchieFacePlayer2::
	applymovement LOCALID_MT_PYRE_SUMMIT_ARCHIE, MtPyre_Summit_Movement_ArchieFacePlayer2
	waitmovement 0
	return

MtPyre_Summit_EventScript_OldLadyApproachPlayer0::
	applymovement LOCALID_MT_PYRE_SUMMIT_OLD_LADY, MtPyre_Summit_Movement_OldLadyApproachPlayer0
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	return

MtPyre_Summit_EventScript_OldLadyApproachPlayer1::
	applymovement LOCALID_MT_PYRE_SUMMIT_OLD_LADY, MtPyre_Summit_Movement_OldLadyApproachPlayer1
	waitmovement 0
	return

MtPyre_Summit_EventScript_OldLadyApproachPlayer2::
	applymovement LOCALID_MT_PYRE_SUMMIT_OLD_LADY, MtPyre_Summit_Movement_OldLadyApproachPlayer2
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	return

MtPyre_Summit_Movement_OldLadyApproachPlayer0:
	walk_down
	walk_down
	walk_in_place_faster_left
	step_end

MtPyre_Summit_Movement_OldLadyApproachPlayer1:
	walk_down
	step_end

MtPyre_Summit_Movement_OldLadyApproachPlayer2:
	walk_down
	walk_down
	walk_in_place_faster_right
	step_end

MtPyre_Summit_Movement_ArchieFacePlayer0:
	walk_left
	walk_in_place_faster_down
	step_end

MtPyre_Summit_Movement_ArchieFacePlayer2:
	walk_right
	walk_in_place_faster_down
	step_end

MtPyre_Summit_EventScript_OldMan::
	lock
	faceplayer
	goto_if_set FLAG_SOOTOPOLIS_ARCHIE_MAXIE_LEAVE, MtPyre_Summit_EventScript_OldManAfterRayquaza
	msgbox MtPyre_Summit_Text_WillYouHearOutMyTale, MSGBOX_YESNO
	call_if_eq VAR_RESULT, YES, MtPyre_Summit_EventScript_OldManTale
	call_if_eq VAR_RESULT, NO, MtPyre_Summit_EventScript_DeclineOldManTale
	release
	end

MtPyre_Summit_EventScript_OldManAfterRayquaza::
	msgbox MtPyre_Summit_Text_HearTheNewLegendOfHoenn, MSGBOX_YESNO
	call_if_eq VAR_RESULT, YES, MtPyre_Summit_EventScript_OldManNewTale
	call_if_eq VAR_RESULT, NO, MtPyre_Summit_EventScript_DeclineOldManTale
	release
	end

MtPyre_Summit_EventScript_OldManTale::
	msgbox MtPyre_Summit_Text_GroudonKyogreTale, MSGBOX_DEFAULT
	return

MtPyre_Summit_EventScript_DeclineOldManTale::
	msgbox MtPyre_Summit_Text_WellThatTooIsFine, MSGBOX_DEFAULT
	return

MtPyre_Summit_EventScript_OldManNewTale::
	msgbox MtPyre_Summit_Text_HoennTrioTale, MSGBOX_DEFAULT
	return

MtPyre_Summit_EventScript_OldLady::
	lock
	faceplayer
	goto_if_set FLAG_RETURNED_RED_OR_BLUE_ORB, MtPyre_Summit_EventScript_OldLadyAfterOrbsReturned
	call_if_ge VAR_MT_PYRE_STATE, 3, MtPyre_Summit_EventScript_OldLadyOrbsReturned
	goto_if_set FLAG_KYOGRE_ESCAPED_SEAFLOOR_CAVERN, MtPyre_Summit_EventScript_OldLadyLegendariesAwake
	msgbox MtPyre_Summit_Text_OrbsHaveBeenTaken, MSGBOX_DEFAULT
	release
	end

MtPyre_Summit_EventScript_OldLadyOrbsReturned::
	msgbox MtPyre_Summit_Text_ThoseTwoMenReturnedOrbs, MSGBOX_DEFAULT
	setflag FLAG_RETURNED_RED_OR_BLUE_ORB
	release
	end

MtPyre_Summit_EventScript_OldLadyLegendariesAwake::
	msgbox MtPyre_Summit_Text_GroudonKyogreAwakened, MSGBOX_DEFAULT
	release
	end

MtPyre_Summit_EventScript_OldLadyAfterOrbsReturned::
	msgbox MtPyre_Summit_Text_SuperAncientPokemonTaughtUs, MSGBOX_DEFAULT
	release
	end

MtPyre_Summit_EventScript_ArchieMaxieTrigger0::
	lockall
	setvar VAR_0x8008, 0
	goto MtPyre_Summit_EventScript_ArchieMaxieReturnOrbs
	end

MtPyre_Summit_EventScript_ArchieMaxieTrigger1::
	lockall
	setvar VAR_0x8008, 1
	goto MtPyre_Summit_EventScript_ArchieMaxieReturnOrbs
	end

MtPyre_Summit_EventScript_ArchieMaxieTrigger2::
	lockall
	setvar VAR_0x8008, 2
	goto MtPyre_Summit_EventScript_ArchieMaxieReturnOrbs
	end

MtPyre_Summit_EventScript_ArchieMaxieReturnOrbs::
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	delay 60
	call_if_eq VAR_0x8008, 0, MtPyre_Summit_EventScript_ArchieMaxieBeginExit0
	call_if_eq VAR_0x8008, 1, MtPyre_Summit_EventScript_ArchieMaxieBeginExit1
	call_if_eq VAR_0x8008, 2, MtPyre_Summit_EventScript_ArchieMaxieBeginExit2
	playse SE_PIN
	applymovement LOCALID_MT_PYRE_SUMMIT_MAXIE, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_MT_PYRE_SUMMIT_MAXIE, Common_Movement_Delay48
	waitmovement 0
	delay 30
	call_if_eq VAR_0x8008, 0, MtPyre_Summit_EventScript_MaxieApproachPlayer0
	call_if_eq VAR_0x8008, 1, MtPyre_Summit_EventScript_MaxieApproachPlayer1
	call_if_eq VAR_0x8008, 2, MtPyre_Summit_EventScript_MaxieApproachPlayer2
	msgbox MtPyre_Summit_Text_MaxieSilence, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_0x8008, 0, MtPyre_Summit_EventScript_MaxieApproachArchie0
	call_if_eq VAR_0x8008, 1, MtPyre_Summit_EventScript_MaxieApproachArchie1
	call_if_eq VAR_0x8008, 2, MtPyre_Summit_EventScript_MaxieApproachArchie2
	delay 30
	applymovement LOCALID_MT_PYRE_SUMMIT_ARCHIE, MtPyre_Summit_Movement_ArchieExit
	applymovement LOCALID_MT_PYRE_SUMMIT_MAXIE, MtPyre_Summit_Movement_MaxieExit
	waitmovement 0
	removeobject LOCALID_MT_PYRE_SUMMIT_ARCHIE
	removeobject LOCALID_MT_PYRE_SUMMIT_MAXIE
	setvar VAR_MT_PYRE_STATE, 3
	releaseall
	end

MtPyre_Summit_EventScript_ArchieMaxieBeginExit0::
	applymovement LOCALID_PLAYER, MtPyre_Summit_Movement_PlayerWatchArchieMaxieExit0
	applymovement LOCALID_MT_PYRE_SUMMIT_ARCHIE, MtPyre_Summit_Movement_ArchieExit
	applymovement LOCALID_MT_PYRE_SUMMIT_MAXIE, MtPyre_Summit_Movement_MaxieExit
	waitmovement 0
	return

MtPyre_Summit_EventScript_ArchieMaxieBeginExit1::
	applymovement LOCALID_PLAYER, MtPyre_Summit_Movement_PlayerWatchArchieMaxieExit1
	applymovement LOCALID_MT_PYRE_SUMMIT_ARCHIE, MtPyre_Summit_Movement_ArchieExit
	applymovement LOCALID_MT_PYRE_SUMMIT_MAXIE, MtPyre_Summit_Movement_MaxieExit
	waitmovement 0
	return

MtPyre_Summit_EventScript_ArchieMaxieBeginExit2::
	applymovement LOCALID_PLAYER, MtPyre_Summit_Movement_PlayerWatchArchieMaxieExit2
	applymovement LOCALID_MT_PYRE_SUMMIT_ARCHIE, MtPyre_Summit_Movement_ArchieExit
	applymovement LOCALID_MT_PYRE_SUMMIT_MAXIE, MtPyre_Summit_Movement_MaxieExit
	waitmovement 0
	return

MtPyre_Summit_EventScript_MaxieApproachPlayer0::
	applymovement LOCALID_PLAYER, MtPyre_Summit_Movement_PlayerFaceMaxie0
	applymovement LOCALID_MT_PYRE_SUMMIT_ARCHIE, MtPyre_Summit_Movement_ArchieWatchMaxie
	applymovement LOCALID_MT_PYRE_SUMMIT_MAXIE, MtPyre_Summit_Movement_MaxieApproachPlayer0
	waitmovement 0
	return

MtPyre_Summit_EventScript_MaxieApproachPlayer1::
	applymovement LOCALID_PLAYER, MtPyre_Summit_Movement_PlayerFaceMaxie
	applymovement LOCALID_MT_PYRE_SUMMIT_ARCHIE, MtPyre_Summit_Movement_ArchieWatchMaxie
	applymovement LOCALID_MT_PYRE_SUMMIT_MAXIE, MtPyre_Summit_Movement_MaxieApproachPlayer1
	waitmovement 0
	return

MtPyre_Summit_EventScript_MaxieApproachPlayer2::
	applymovement LOCALID_PLAYER, MtPyre_Summit_Movement_PlayerFaceMaxie
	applymovement LOCALID_MT_PYRE_SUMMIT_ARCHIE, MtPyre_Summit_Movement_ArchieWatchMaxie
	applymovement LOCALID_MT_PYRE_SUMMIT_MAXIE, MtPyre_Summit_Movement_MaxieApproachPlayer2
	waitmovement 0
	return

MtPyre_Summit_EventScript_MaxieApproachArchie0::
	applymovement LOCALID_PLAYER, MtPyre_Summit_Movement_PlayerWatchMaxie
	applymovement LOCALID_MT_PYRE_SUMMIT_MAXIE, MtPyre_Summit_Movement_MaxieApproachArchie0
	waitmovement 0
	applymovement LOCALID_MT_PYRE_SUMMIT_ARCHIE, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	return

MtPyre_Summit_EventScript_MaxieApproachArchie1::
	applymovement LOCALID_PLAYER, MtPyre_Summit_Movement_PlayerWatchMaxie
	applymovement LOCALID_MT_PYRE_SUMMIT_MAXIE, MtPyre_Summit_Movement_MaxieApproachArchie1
	waitmovement 0
	applymovement LOCALID_MT_PYRE_SUMMIT_ARCHIE, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	return

MtPyre_Summit_EventScript_MaxieApproachArchie2::
	applymovement LOCALID_PLAYER, MtPyre_Summit_Movement_PlayerWatchMaxie
	applymovement LOCALID_MT_PYRE_SUMMIT_MAXIE, MtPyre_Summit_Movement_MaxieApproachArchie2
	waitmovement 0
	applymovement LOCALID_MT_PYRE_SUMMIT_ARCHIE, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	return

MtPyre_Summit_Movement_PlayerFaceMaxie0:
	delay_16
	delay_16
	walk_in_place_faster_right
	step_end

MtPyre_Summit_Movement_PlayerFaceMaxie:
	delay_16
	delay_16
	walk_in_place_faster_left
	step_end

MtPyre_Summit_Movement_ArchieExit:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtPyre_Summit_Movement_MaxieExit:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtPyre_Summit_Movement_PlayerWatchArchieMaxieExit0:
	delay_16
	delay_8
	walk_left
	walk_in_place_faster_right
	delay_16
	walk_in_place_faster_down
	step_end

MtPyre_Summit_Movement_PlayerWatchArchieMaxieExit1:
	delay_16
	delay_8
	walk_right
	walk_in_place_faster_left
	delay_16
	walk_in_place_faster_down
	step_end

MtPyre_Summit_Movement_PlayerWatchArchieMaxieExit2:
	delay_16
	delay_8
	walk_in_place_faster_left
	delay_16
	walk_in_place_faster_down
	step_end

MtPyre_Summit_Movement_MaxieApproachPlayer0:
	walk_up
	walk_up
	walk_up
	walk_left
	step_end

MtPyre_Summit_Movement_MaxieApproachPlayer1:
	walk_up
	walk_up
	walk_up
	walk_in_place_faster_right
	step_end

MtPyre_Summit_Movement_MaxieApproachPlayer2:
	walk_up
	walk_up
	walk_up
	walk_in_place_faster_right
	step_end

MtPyre_Summit_Movement_ArchieWatchMaxie:
	delay_16
	walk_in_place_faster_up
	step_end

MtPyre_Summit_Movement_PlayerWatchMaxie:
	delay_16
	walk_in_place_faster_down
	step_end

MtPyre_Summit_Movement_MaxieApproachArchie0:
	walk_down
	walk_right
	walk_down
	walk_down
	walk_in_place_faster_left
	step_end

MtPyre_Summit_Movement_MaxieApproachArchie1:
	walk_down
	walk_down
	walk_down
	walk_in_place_faster_left
	step_end

MtPyre_Summit_Movement_MaxieApproachArchie2:
	walk_down
	walk_down
	walk_down
	walk_in_place_faster_left
	step_end

MtPyre_Summit_EventScript_Grunt1::
	trainerbattle_single TRAINER_GRUNT_MT_PYRE_1, MtPyre_Summit_Text_Grunt1Intro, MtPyre_Summit_Text_Grunt1Defeat
	msgbox MtPyre_Summit_Text_Grunt1PostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_Summit_EventScript_Grunt2::
	trainerbattle_single TRAINER_GRUNT_MT_PYRE_2, MtPyre_Summit_Text_Grunt2Intro, MtPyre_Summit_Text_Grunt2Defeat
	msgbox MtPyre_Summit_Text_Grunt2PostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_Summit_EventScript_Grunt3::
	trainerbattle_single TRAINER_GRUNT_MT_PYRE_3, MtPyre_Summit_Text_Grunt3Intro, MtPyre_Summit_Text_Grunt3Defeat
	msgbox MtPyre_Summit_Text_Grunt3PostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_Summit_EventScript_Grunt4::
	trainerbattle_single TRAINER_GRUNT_MT_PYRE_4, MtPyre_Summit_Text_Grunt4Intro, MtPyre_Summit_Text_Grunt4Defeat
	msgbox MtPyre_Summit_Text_Grunt4PostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_Summit_Text_Grunt1Intro:
	.string "¡No! Esos tontos del TEAM MAGMA\n"
	.string "¡llegaron antes que nosotros!\p"
	.string "¡No podemos quedarnos atrás!$"

MtPyre_Summit_Text_Grunt1Defeat:
	.string "Pensé que eras uno de los MAGMA\n"
	.string "que casualmente regresaba...$"

MtPyre_Summit_Text_Grunt1PostBattle:
	.string "Sí, puede que seas fuerte...\n"
	.string "¡Pero somos muchos nosotros!$"

MtPyre_Summit_Text_Grunt2Intro:
	.string "¡Ja!\n"
	.string "¡Qué mala suerte tienes!\p"
	.string "Si hubieras venido antes, solo\n"
	.string "lucharías con el débil TEAM MAGMA.\p"
	.string "Pero como llegaste ahora, ¡tienes\n"
	.string "que luchar contra los fuertes!$"

MtPyre_Summit_Text_Grunt2Defeat:
	.string "Urgh... Debí dejar que te encargaras\n"
	.string "del TEAM MAGMA primero...$"

MtPyre_Summit_Text_Grunt2PostBattle:
	.string "¡Tú no sabes nada!\n"
	.string "¿Entonces por qué nos molestas?$"

MtPyre_Summit_Text_Grunt3Intro:
	.string "Tú...\n"
	.string "Te vimos en el MT. CHIMNEY.\p"
	.string "No perteneces a ningún TEAM,\n"
	.string "¿así que por qué estás aquí?$"

MtPyre_Summit_Text_Grunt3Defeat:
	.string "Si vas a molestar a alguien,\n"
	.string "que sea al TEAM MAGMA...$"

MtPyre_Summit_Text_Grunt3PostBattle:
	.string "¡Je, no importa!\n"
	.string "¡Ganamos algo de tiempo!\p"
	.string "¡El BOSS ya debería haber tomado\n"
	.string "lo que buscaba!$"

MtPyre_Summit_Text_Grunt4Intro:
	.string "¡Ah, ya lo sé!\n"
	.string "Intentaste unirte al TEAM MAGMA,\l"
	.string "¡pero no te aceptaron!\p"
	.string "Bueno, ¡no creas que te dejaremos\n"
	.string "unirte al TEAM AQUA!$"

MtPyre_Summit_Text_Grunt4Defeat:
	.string "Si tantas ganas tienes de unirte\n"
	.string "al TEAM AQUA, lo pensaremos...$"

MtPyre_Summit_Text_Grunt4PostBattle:
	.string "Tenemos una gran combinación\n"
	.string "entre los miembros y el líder.$"

MtPyre_Summit_Text_ArchieWeGotTheOrbLetsGo:
	.string "ARCHIE: MAXIE del TEAM MAGMA nos\n"
	.string "ganó, pero logramos lo que queríamos.\p"
	.string "El ORBE ROJO del MONTE CENIZA...\n"
	.string "¡Yo, ARCHIE, ya lo tengo conmigo!\p"
	.string "Fufufu... ¡Ahora podemos hacer\n"
	.string "realidad nuestro objetivo final!\p"
	.string "¡Muy bien, EQUIPO!\n"
	.string "¡Nos retiramos!$"

MtPyre_Summit_Text_BothOrbsTakenMagmaLeftThis:
	.string "Oh, no...\n"
	.string "Esto no puede pasar...\p"
	.string "No solo el ORBE AZUL, sino que\n"
	.string "también se llevaron el ORBE ROJO...\p"
	.string "El ORBE AZUL y el ORBE ROJO nunca\n"
	.string "deben separarse. Van juntos.\p"
	.string "¿Qué intentan hacer esos hombres\n"
	.string "con los dos ORBES?\p"
	.string "... ... ... ... ... ...\n"
	.string "... ... ... ... ... ...\p"
	.string "Ah, sí. ¿Fue el TEAM MAGMA quien vino\n"
	.string "y se llevó el ORBE AZUL primero?\p"
	.string "Bueno, con las prisas, dejaron esto\n"
	.string "aquí.\p"
	.string "No podía imaginar qué sería\n"
	.string "exactamente.\p"
	.string "Me gustaría que te lo quedaras.\n"
	.string "Tal vez sea útil de alguna forma.$"

MtPyre_Summit_Text_OrbsHaveBeenTaken:
	.string "El ORBE AZUL y el ORBE ROJO que\n"
	.string "llevaron esos hombres siniestros...\p"
	.string "Nunca deben estar separados...\n"
	.string "Temo que pase algo terrible...$"

MtPyre_Summit_Text_GroudonKyogreAwakened:
	.string "Cielos...\p"
	.string "Dices que tanto GROUDON como KYOGRE\n"
	.string "han despertado?\p"
	.string "Dicen que el ORBE AZUL y el\n"
	.string "ORBE ROJO calmaron la furia de\l"
	.string "los dos POKéMON...\p"
	.string "También dicen que el dueño real\n"
	.string "de los ORBES aún existe.\p"
	.string "Pero nadie sabe quién, o qué\n"
	.string "exactamente, posee los ORBES.\p"
	.string "Podría ser un humano, o tal vez\n"
	.string "un POKéMON, pero nadie lo sabe.$"

MtPyre_Summit_Text_ThoseTwoMenReturnedOrbs:
	.string "Los dos hombres que llevaron los ORBS\n"
	.string "regresaron para devolverlos solos.\p"
	.string "Esos hombres...\n"
	.string "Tal vez no sean tan malos después...$"

MtPyre_Summit_Text_SuperAncientPokemonTaughtUs:
	.string "Las encarnaciones de la tierra, el mar\n"
	.string "y el cielo...\p"
	.string "Se dice que esas son las identidades\n"
	.string "de los POKéMON superantiguos...\p"
	.string "Así como los humanos y los\n"
	.string "POKéMON tienen vida, nuestro mundo\l"
	.string "también está vivo...\p"
	.string "Los POKéMON superantiguos tienen\n"
	.string "nos enseñó que...$"

MtPyre_Summit_Text_WillYouHearOutMyTale:
	.string "en el MONTE CENIZA calmamos los\n"
	.string "espíritus de POKéMON que partieron...\p"
	.string "Este es un lugar elevado donde se\n"
	.string "puede ver todo HOENN...\p"
	.string "Los espíritus de los POKéMON\n"
	.string "deben hallar consuelo aquí...\p"
	.string "¿Es coincidencia que estés aquí...?\p"
	.string "¿Escucharás mi historia? Una que se\n"
	.string "cuenta mucho en la región de HOENN?$"

MtPyre_Summit_Text_GroudonKyogreTale:
	.string "Pasó hace muchísimo tiempo...\p"
	.string "El mundo fue azotado por una feroz\n"
	.string "choque entre los POKéMON de tierra\l"
	.string "y los POKéMON del mar...\p"
	.string "Los POKéMON de tierra alzaron\n"
	.string "montañas y crearon continentes...\p"
	.string "Los POKéMON del mar alzaron huge\n"
	.string "olas y esculpieron los océanos...\p"
	.string "Su feroz duelo no tenía final.\p"
	.string "El mundo fue envuelto en masivos\n"
	.string "infernos y tormentas feroces.\p"
	.string "El ORBE AZUL y el ORBE ROJO trajeron\n"
	.string "el fin de la calamidad.\p"
	.string "La luz brotó de los dos ORBES y\n"
	.string "calmó a los adversarios furiosos.\p"
	.string "La pareja, ya dócil, se sumergió\n"
	.string "en el mar donde finalmente\l"
	.string "desaparecieron...$"

MtPyre_Summit_Text_WellThatTooIsFine:
	.string "Ya veo...\n"
	.string "Bueno, eso también está bien...$"

MtPyre_Summit_Text_MaxieSilence:
	.string "MAXIE: {PLAYER}...\p"
	.string "... ... ... ... ... ...\n"
	.string "... ... ... ... ... ...$"

MtPyre_Summit_Text_HearTheNewLegendOfHoenn:
	.string "Es mi deber pasar las leyendas\n"
	.string "de HOENN a futuras generaciones.\p"
	.string "Y la crisis que acaba de terminar en\n"
	.string "CIUDAD CALMA reescribió una leyenda...\p"
	.string "¿Tienes tiempo de escuchar la nueva\n"
	.string "leyenda de HOENN?$"

MtPyre_Summit_Text_HoennTrioTale:
	.string "Pasó hace muchísimo tiempo...\p"
	.string "El mundo fue azotado por una feroz\n"
	.string "choque entre los POKéMON de tierra\l"
	.string "y los POKéMON del mar...\p"
	.string "Los POKéMON de tierra alzaron\n"
	.string "montañas y crearon continentes...\p"
	.string "Los POKéMON del mar alzaron huge\n"
	.string "olas y esculpieron los océanos...\p"
	.string "Su feroz duelo no tenía final.\p"
	.string "El mundo fue envuelto en masivos\n"
	.string "fuegos y tormentas feroces.\p"
	.string "Fue entonces cuando los POKéMON\n"
	.string "del cielo bajaron de una tormenta.\p"
	.string "El POKéMON, de un verde brillante,\n"
	.string "calmó a los dos POKéMON enfurecidos.\p"
	.string "Luego, cumplido su deber, el POKéMON\n"
	.string "verde voló hacia el azul infinito...$"

