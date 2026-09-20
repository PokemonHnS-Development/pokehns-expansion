MtChimney_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, MtChimney_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, MtChimney_OnTransition
	.byte 0

MtChimney_OnTransition:
	setvar VAR_JAGGED_PASS_ASH_WEATHER, 1
	end

MtChimney_OnResume:
	setstepcallback STEP_CB_ASH
	end

MtChimney_EventScript_Archie::
	lock
	faceplayer
	call_if_unset FLAG_EVIL_LEADER_PLEASE_STOP, MtChimney_EventScript_ArchieGoStopTeamMagma
	call_if_set FLAG_EVIL_LEADER_PLEASE_STOP, MtChimney_EventScript_ArchieBusyFighting
	closemessage
	applymovement LOCALID_MT_CHIMNEY_ARCHIE, Common_Movement_FaceOriginalDirection
	waitmovement 0
	setflag FLAG_EVIL_LEADER_PLEASE_STOP
	release
	end

MtChimney_EventScript_ArchieGoStopTeamMagma::
	msgbox MtChimney_Text_ArchieGoStopTeamMagma, MSGBOX_DEFAULT
	return

MtChimney_EventScript_ArchieBusyFighting::
	msgbox MtChimney_Text_ArchieIHaveMyHandsFull, MSGBOX_DEFAULT
	return

MtChimney_EventScript_Maxie::
	lockall
	playbgm MUS_ENCOUNTER_MAGMA, FALSE
	msgbox MtChimney_Text_MeteoriteWillActivateVolcano, MSGBOX_DEFAULT
	applymovement LOCALID_MT_CHIMNEY_MAXIE, Common_Movement_FacePlayer
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_MT_CHIMNEY_MAXIE, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_MT_CHIMNEY_MAXIE, Common_Movement_Delay48
	waitmovement 0
	msgbox MtChimney_Text_MaxieIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_MAXIE_MT_CHIMNEY, MtChimney_Text_MaxieDefeat
	msgbox MtChimney_Text_MaxieYouHaventSeenLastOfMagma, MSGBOX_DEFAULT
	closemessage
	delay 30
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_MT_CHIMNEY_MAXIE
	removeobject LOCALID_MT_CHIMNEY_MAGMA_GRUNT_1
	removeobject LOCALID_MT_CHIMNEY_TABITHA
	removeobject LOCALID_MT_CHIMNEY_MAGMA_GRUNT_2
	setflag FLAG_HIDE_MT_CHIMNEY_TEAM_MAGMA
	fadescreenswapbuffers FADE_FROM_BLACK
	setobjectxyperm LOCALID_MT_CHIMNEY_ARCHIE, 10, 12
	addobject LOCALID_MT_CHIMNEY_ARCHIE
	call_if_eq VAR_FACING, DIR_EAST, MtChimney_EventScript_ArchieApproachPlayerEast
	call_if_eq VAR_FACING, DIR_NORTH, MtChimney_EventScript_ArchieApproachPlayerNorth
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	msgbox MtChimney_Text_ArchieThankYou, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_FACING, DIR_EAST, MtChimney_EventScript_ArchieExitEast
	call_if_eq VAR_FACING, DIR_NORTH, MtChimney_EventScript_ArchieExitNorth
	removeobject LOCALID_MT_CHIMNEY_ARCHIE
	setflag FLAG_HIDE_MT_CHIMNEY_TEAM_AQUA
	setflag FLAG_DEFEATED_EVIL_TEAM_MT_CHIMNEY
	clearflag FLAG_HIDE_FALLARBOR_HOUSE_PROF_COZMO
	setflag FLAG_HIDE_METEOR_FALLS_1F_1R_COZMO
	clearflag FLAG_HIDE_MT_CHIMNEY_LAVA_COOKIE_LADY
	releaseall
	end

MtChimney_EventScript_ArchieApproachPlayerEast::
	applymovement LOCALID_MT_CHIMNEY_ARCHIE, MtChimney_Movement_ArchieApproachPlayerEast
	waitmovement 0
	return

MtChimney_EventScript_ArchieApproachPlayerNorth::
	applymovement LOCALID_MT_CHIMNEY_ARCHIE, MtChimney_Movement_ArchieApproachPlayerNorth
	waitmovement 0
	return

MtChimney_EventScript_ArchieExitEast::
	applymovement LOCALID_MT_CHIMNEY_ARCHIE, MtChimney_Movement_ArchieExitEast
	waitmovement 0
	return

MtChimney_EventScript_ArchieExitNorth::
	applymovement LOCALID_MT_CHIMNEY_ARCHIE, MtChimney_Movement_ArchieExitNorth
	waitmovement 0
	return

MtChimney_EventScript_LavaCookieLady::
	lock
	faceplayer
	showmoneybox 0, 0
	msgbox MtChimney_Text_LavaCookiesJust200, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MtChimney_EventScript_DeclineLavaCookie
	checkmoney 200
	goto_if_eq VAR_RESULT, FALSE, MtChimney_EventScript_NotEnoughMoney
	msgbox MtChimney_Text_ThankYouDear, MSGBOX_DEFAULT
	checkitemspace ITEM_LAVA_COOKIE
	call_if_eq VAR_RESULT, TRUE, MtChimney_EventScript_RemoveMoney
.if OW_SHOW_ITEM_DESCRIPTIONS == OW_ITEM_DESCRIPTIONS_OFF
	giveitem ITEM_LAVA_COOKIE
	goto_if_eq VAR_RESULT, FALSE, MtChimney_EventScript_BagIsFull
	hidemoneybox
	release
	end

MtChimney_EventScript_BagIsFull::
	msgbox gText_TooBadBagIsFull, MSGBOX_DEFAULT
	hidemoneybox
	release
	end
.else
	hidemoneybox
	giveitem ITEM_LAVA_COOKIE
	goto_if_eq VAR_RESULT, FALSE, MtChimney_EventScript_BagIsFull
	release
	end

MtChimney_EventScript_BagIsFull::
	msgbox gText_TooBadBagIsFull, MSGBOX_DEFAULT
	release
	end
.endif @ OW_SHOW_ITEM_DESCRIPTIONS


MtChimney_EventScript_RemoveMoney::
	removemoney 200
	updatemoneybox
	return

MtChimney_EventScript_DeclineLavaCookie::
	msgbox MtChimney_Text_OhFineThen, MSGBOX_DEFAULT
	hidemoneybox
	release
	end

MtChimney_EventScript_NotEnoughMoney::
	msgbox MtChimney_Text_YouveNotGotTheMoney, MSGBOX_DEFAULT
	hidemoneybox
	release
	end

MtChimney_Movement_ArchieApproachPlayerEast:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	step_end

MtChimney_Movement_ArchieExitEast:
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtChimney_Movement_ArchieApproachPlayerNorth:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	step_end

MtChimney_Movement_ArchieExitNorth:
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtChimney_Movement_Unused1:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	step_end

MtChimney_Movement_Unused2:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_down
	step_end

MtChimney_Movement_Unused3:
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtChimney_Movement_Unused4:
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	step_end

MtChimney_Movement_Unused5:
	delay_16
	delay_16
	delay_16
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_down
	step_end

MtChimney_Movement_Unused6:
	delay_16
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtChimney_Movement_Unused7:
	delay_16
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	step_end

MtChimney_Movement_Unused8:
	delay_16
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_in_place_faster_down
	step_end

MtChimney_Movement_Unused9:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtChimney_Movement_Unused10:
	walk_down
	step_end

MtChimney_Movement_Unused11:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtChimney_Movement_Unused12:
	delay_16
	delay_16
	walk_in_place_faster_left
	delay_16
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtChimney_Movement_Unused13:
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	walk_in_place_faster_left
	delay_16
	walk_down
	walk_down
	step_end

MtChimney_Movement_Unused14:
	lock_facing_direction
	walk_fast_left
	unlock_facing_direction
	face_right
	step_end

MtChimney_Movement_Unused15:
	walk_left
	walk_in_place_faster_right
	delay_16
	step_end

MtChimney_EventScript_BusyAquaGrunt1::
	msgbox MtChimney_Text_MagmaOutnumbersUs, MSGBOX_SIGN
	end

MtChimney_EventScript_BusyAquaGrunt2::
	msgbox MtChimney_Text_LessHabitatForWaterPokemon, MSGBOX_SIGN
	end

MtChimney_EventScript_BusyAquaGrunt3::
	msgbox MtChimney_Text_MagmasNameSimilar, MSGBOX_SIGN
	end

MtChimney_EventScript_Tabitha::
	trainerbattle_single TRAINER_TABITHA_MT_CHIMNEY, MtChimney_Text_TabithaIntro, MtChimney_Text_TabithaDefeat
	msgbox MtChimney_Text_TabithaPostBattle, MSGBOX_AUTOCLOSE
	end

MtChimney_EventScript_Grunt2::
	trainerbattle_single TRAINER_GRUNT_MT_CHIMNEY_2, MtChimney_Text_Grunt2Intro, MtChimney_Text_Grunt2Defeat
	msgbox MtChimney_Text_Grunt2PostBattle, MSGBOX_AUTOCLOSE
	end

MtChimney_EventScript_BusyMagmaGrunt1::
	msgbox MtChimney_Text_TeamAquaAlwaysMessingWithPlans, MSGBOX_SIGN
	end

MtChimney_EventScript_BusyMagmaGrunt2::
	msgbox MtChimney_Text_MeteoritesPackAmazingPower, MSGBOX_SIGN
	end

MtChimney_EventScript_BusyMagmaGrunt3::
	msgbox MtChimney_Text_YouBetterNotMessWithUs, MSGBOX_SIGN
	end

MtChimney_EventScript_BusyMagmaGrunt4::
	msgbox MtChimney_Text_AquasNameSimilar, MSGBOX_SIGN
	end

MtChimney_EventScript_BusyMagmaGrunt5::
	msgbox MtChimney_Text_DouseThemInFire, MSGBOX_SIGN
	end

MtChimney_EventScript_BusyMagmaGrunt6::
	msgbox MtChimney_Text_KeepMakingMoreLand, MSGBOX_SIGN
	end

MtChimney_EventScript_MagmaPoochyena::
	msgbox MtChimney_Text_Bufoh, MSGBOX_SIGN
	end

MtChimney_EventScript_AquaPoochyena::
	msgbox MtChimney_Text_Bushaa, MSGBOX_SIGN
	end

MtChimney_EventScript_MeteoriteMachine::
	lockall
	goto_if_unset FLAG_DEFEATED_EVIL_TEAM_MT_CHIMNEY, MtChimney_EventScript_MachineOn
	goto_if_set FLAG_RECEIVED_METEORITE, MtChimney_EventScript_MachineOff
	msgbox MtChimney_Text_RemoveTheMeteorite, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MtChimney_EventScript_LeaveMeteoriteAlone
	msgbox MtChimney_Text_PlayerRemovedMeteorite, MSGBOX_DEFAULT
	giveitem ITEM_METEORITE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_METEORITE
	releaseall
	end

MtChimney_EventScript_LeaveMeteoriteAlone::
	msgbox MtChimney_Text_PlayerLeftMeteorite, MSGBOX_DEFAULT
	releaseall
	end

MtChimney_EventScript_MachineOff::
	msgbox MtChimney_Text_MachineMakesNoResponse, MSGBOX_DEFAULT
	releaseall
	end

MtChimney_EventScript_MachineOn::
	msgbox MtChimney_Text_MetoriteFittedOnMachine, MSGBOX_DEFAULT
	releaseall
	end

MtChimney_EventScript_RouteSign::
	msgbox MtChimney_Text_RouteSign, MSGBOX_SIGN
	end

MtChimney_EventScript_Shelby::
	trainerbattle_single TRAINER_SHELBY_1, MtChimney_Text_ShelbyIntro, MtChimney_Text_ShelbyDefeat, MtChimney_EventScript_DefeatedShelby
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, MtChimney_EventScript_RematchShelby
	msgbox MtChimney_Text_ShelbyPostBattle, MSGBOX_DEFAULT
	release
	end

MtChimney_EventScript_DefeatedShelby::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox MtChimney_Text_ShelbyRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_SHELBY_1
	release
	end

MtChimney_EventScript_RematchShelby::
	trainerbattle_rematch TRAINER_SHELBY_1, MtChimney_Text_ShelbyRematchIntro, MtChimney_Text_ShelbyRematchDefeat
	msgbox MtChimney_Text_ShelbyPostRematch, MSGBOX_AUTOCLOSE
	end

MtChimney_EventScript_Melissa::
	trainerbattle_single TRAINER_MELISSA, MtChimney_Text_MelissaIntro, MtChimney_Text_MelissaDefeat
	msgbox MtChimney_Text_MelissaPostBattle, MSGBOX_AUTOCLOSE
	end

MtChimney_EventScript_Sheila::
	trainerbattle_single TRAINER_SHEILA, MtChimney_Text_SheilaIntro, MtChimney_Text_SheilaDefeat
	msgbox MtChimney_Text_SheilaPostBattle, MSGBOX_AUTOCLOSE
	end

MtChimney_EventScript_Shirley::
	trainerbattle_single TRAINER_SHIRLEY, MtChimney_Text_ShirleyIntro, MtChimney_Text_ShirleyDefeat
	msgbox MtChimney_Text_ShirleyPostBattle, MSGBOX_AUTOCLOSE
	end

MtChimney_EventScript_Grunt1::
	trainerbattle_single TRAINER_GRUNT_MT_CHIMNEY_1, MtChimney_Text_Grunt1Intro, MtChimney_Text_Grunt1Defeat
	msgbox MtChimney_Text_Grunt1PostBattle, MSGBOX_AUTOCLOSE
	end

MtChimney_EventScript_Sawyer::
	trainerbattle_single TRAINER_SAWYER_1, MtChimney_Text_SawyerIntro, MtChimney_Text_SawyerDefeat, MtChimney_EventScript_SawyerDefeated
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, MtChimney_EventScript_SawyerRematch
	msgbox MtChimney_Text_SawyerPostBattle, MSGBOX_DEFAULT
	release
	end

MtChimney_EventScript_SawyerDefeated::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox MtChimney_Text_SawyerRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_SAWYER_1
	release
	end

MtChimney_EventScript_SawyerRematch::
	trainerbattle_rematch TRAINER_SAWYER_1, MtChimney_Text_SawyerRematchIntro, MtChimney_Text_SawyerRematchDefeat
	msgbox MtChimney_Text_SawyerPostRematch, MSGBOX_AUTOCLOSE
	end

MtChimney_Text_MeteoriteWillActivateVolcano:
	.string "El poder del METEORITO...\p"
	.string "Al amplificar su poder con esta\n"
	.string "máquina, la actividad volcánica\l"
	.string "del MT. CHIMNEY se intensificará...\p"
	.string "Su energía crecerá en lo profundo\n"
	.string "del cráter y...\l"
	.string "Fufufu...$"

MtChimney_Text_MaxieIntro:
	.string "MAXIE: ¿Hm?\n"
	.string "¿Quién eres?\p"
	.string "… … … … … …\n"
	.string "… … … … … …\p"
	.string "Oí a ARCHIE quejarse de un niño\n"
	.string "que se ha metido en los asuntos\l"
	.string "del TEAM AQUA.\p"
	.string "Debes ser tú a quien se refería.\p"
	.string "¡Bah! ¿Así que piensas\n"
	.string "estorbarnos, TEAM MAGMA?\p"
	.string "Ahora escucha bien.\n"
	.string "Hace mucho, los seres vivos usaban\l"
	.string "la tierra para vivir y crecer.\p"
	.string "¡Por eso la tierra es lo más vital!\n"
	.string "¡Es la cuna de todo!\p"
	.string "Por eso TEAM MAGMA se dedica\n"
	.string "a expandir la masa terrestre.\p"
	.string "¡Es para el progreso de la\n"
	.string "humanidad y los POKéMON!\p"
	.string "Y para eso, necesitamos el poder de\n"
	.string "lo que duerme en esta montaña...\p"
	.string "¡Oh! No era necesario que\n"
	.string "supieras tanto.\p"
	.string "¡Pero no importa!\n"
	.string "¡Te enseñaré las consecuencias de\l"
	.string "entrometerte en nuestro plan!$"

MtChimney_Text_MaxieDefeat:
	.string "¡¿Qué?!\p"
	.string "¡¿Yo, MAXIE, fui sorprendido?!$"

MtChimney_Text_MaxieYouHaventSeenLastOfMagma:
	.string "MAXIE: Pero basta.\n"
	.string "Me retiraré por esta vez.\p"
	.string "Pero no creas que es la última vez\n"
	.string "que verás al TEAM MAGMA.\p"
	.string "Fufufu...\p"
	.string "Aun sin el METEORITO, si nosotros\n"
	.string "obtener ese ORBE... Jejeje...$"

MtChimney_Text_TabithaIntro:
	.string "¡Jejeje!\p"
	.string "¡Así que viniste hasta aquí!\p"
	.string "¡Pero llegas demasiado tarde!\n"
	.string "¡Ya entregué la METEORITA\l"
	.string "de METEOR FALLS al JEFE!$"

MtChimney_Text_TabithaDefeat:
	.string "Jejeje...\p"
	.string "Aunque perdí, si nuestro líder\n"
	.string "despierta a esa cosa...$"

MtChimney_Text_TabithaPostBattle:
	.string "¡JEFE, date prisa!\n"
	.string "¡Dale la energía de la METEORITA!\p"
	.string "Jejeje...$"

MtChimney_Text_Grunt2Intro:
	.string "Nosotros, el TEAM MAGMA, trabajamos\n"
	.string "por el bien de todos.\p"
	.string "O sea, si el poder de esa cosa creara\n"
	.string "más tierra, habría más donde vivir.\p"
	.string "¡Todos serían felices!$"

MtChimney_Text_Grunt2Defeat:
	.string "¿Eh?\n"
	.string "¿Cómo que perdí?$"

MtChimney_Text_Grunt2PostBattle:
	.string "Nuestro JEFE dice: “Hará que todos\n"
	.string "happy.”\p"
	.string "Pero, ¿por qué todos se interponen\n"
	.string "en nuestro camino?$"

MtChimney_Text_Grunt1Intro:
	.string "¡Si hubiera más tierra, tendría\n"
	.string "mi propia casa gigante!\p"
	.string "¡La haré sobre lava endurecida!$"

MtChimney_Text_Grunt1Defeat:
	.string "My dream of a big house…$"

MtChimney_Text_Grunt1PostBattle:
	.string "Un chico como tú debería estar\n"
	.string "jugando entre las olas!$"

MtChimney_Text_TeamAquaAlwaysMessingWithPlans:
	.string "El molesto TEAM AQUA...\n"
	.string "¡Siempre arruinan nuestros planes!$"

MtChimney_Text_MeteoritesPackAmazingPower:
	.string "METEORITES pack amazing power!$"

MtChimney_Text_YouBetterNotMessWithUs:
	.string "¡Mejor no te metas con nosotros!\p"
	.string "Intentamos despertar a esa cosa\n"
	.string "¡por el bien de todos!$"

MtChimney_Text_AquasNameSimilar:
	.string "¡Somos el TEAM MAGMA!\p"
	.string "¡Ellos son el TEAM AQUA!\p"
	.string "¡Me molesta muchísimo que\n"
	.string "usen un nombre como el nuestro!$"

MtChimney_Text_DouseThemInFire:
	.string "¡Sí!\n"
	.string "¡Quémalos con fuego!$"

MtChimney_Text_KeepMakingMoreLand:
	.string "We're going to keep making more land!$"

MtChimney_Text_Bufoh:
	.string "Bufoh!$"

MtChimney_Text_ArchieGoStopTeamMagma:
	.string "ARCHIE: ¡Grr, {PLAYER}!\n"
	.string "¡Sabía que aparecerías!\p"
	.string "¡Mira lo que los fanáticos del\n"
	.string "TEAM MAGMA están tramando!\p"
	.string "¡Quieren inyectar el poder del\n"
	.string "METEORITO robado en el volcán!\p"
	.string "¡Hacer algo así causará la\n"
	.string "erupción del volcán!$"

MtChimney_Text_ArchieIHaveMyHandsFull:
	.string "ARCHIE: Grrr…\p"
	.string "Quiero detener a ese MAXIE,\n"
	.string "¡pero no puedo!\p"
	.string "¡No mientras lucho contra\n"
	.string "tres oponentes a la vez!$"

MtChimney_Text_ArchieThankYou:
	.string "ARCHIE: {PLAYER}!\n"
	.string "¡Gracias!\p"
	.string "¡Con tu ayuda frustramos el plan\n"
	.string "destructivo del TEAM MAGMA!\p"
	.string "Pero... Tú...\n"
	.string "¿De qué lado estás?\p"
	.string "Ah, no importa.\p"
	.string "Seguiremos vigilantes y no\n"
	.string "dejaremos de buscar al TEAM MAGMA.\p"
	.string "{PLAYER}, ¡nos volveremos a ver!$"

MtChimney_Text_MagmaOutnumbersUs:
	.string "Rayos... ¡el TEAM MAGMA nos supera!\n"
	.string "¡No podemos seguirles el ritmo!$"

MtChimney_Text_LessHabitatForWaterPokemon:
	.string "Si expanden la tierra, habrá\n"
	.string "menos hábitats para POKéMON agua!$"

MtChimney_Text_MagmasNameSimilar:
	.string "¡Nosotros somos el TEAM AQUA!\p"
	.string "¡Ellos son el TEAM MAGMA!\p"
	.string "¡Me hierve la sangre que usen un\n"
	.string "nombre tan confuso!$"

MtChimney_Text_Bushaa:
	.string "Bushaa!$"

MtChimney_Text_LavaCookiesJust200:
	.string "LAVA COOKIES are MT. CHIMNEY's local\n"
	.string "del MT. CHIMNEY.\p"
	.string "Prueba uno. Solo cuesta ¥200.$"

MtChimney_Text_ThankYouDear:
	.string "Thank you, dear!$"

MtChimney_Text_YouveNotGotTheMoney:
	.string "Ay, cielo. No puedes comprar nada si\n"
	.string "no tienes el dinero.$"

MtChimney_Text_OhFineThen:
	.string "Oh, fine then.$"

MtChimney_Text_MetoriteFittedOnMachine:
	.string "Un METEORITO está puesto en una\n"
	.string "máquina misteriosa…\p"
	.string "La máquina parece estar guardando\n"
	.string "energía en el METEORITO.$"

MtChimney_Text_RemoveTheMeteorite:
	.string "Un METEORITO está puesto en una\n"
	.string "máquina misteriosa…\p"
	.string "¿Quieres quitar el METEORITO?$"

MtChimney_Text_PlayerRemovedMeteorite:
	.string "{PLAYER} quitó el METEORITO de la\n"
	.string "máquina misteriosa.$"

MtChimney_Text_PlayerLeftMeteorite:
	.string "{PLAYER} dejó el METEORITO aquí\n"
	.string "estaba.$"

MtChimney_Text_MachineMakesNoResponse:
	.string "Esta máquina misteriosa...\n"
	.string "No da respuesta alguna.$"

MtChimney_Text_RouteSign:
	.string "{DOWN_ARROW} SENDERO ROCOSO\n"
	.string "PUEBLO LAVARIDGE ADELANTE$"

MtChimney_Text_ShelbyIntro:
	.string "Fui a las aguas termales y\n"
	.string "descansé mis cansados huesos.\l"
	.string "¡Ahora me siento fuerte!$"

MtChimney_Text_ShelbyDefeat:
	.string "Cielos, no puede ser.\n"
	.string "¡Vaya, eres increíble!$"

MtChimney_Text_ShelbyPostBattle:
	.string "Bueno, he perdido. Ya no puedo\n"
	.string "llamarme EXPERTO, ¿verdad?$"

MtChimney_Text_ShelbyRegister:
	.string "Gracias, niño. Fue divertido, como si\n"
	.string "estuviera luchando con mi nieto.\p"
	.string "Por favor, vuelve a visitarme para\n"
	.string "una revancha.$"

MtChimney_Text_ShelbyRematchIntro:
	.string "Si unes tu corazón con el de tus\n"
	.string "POKéMON, podrás lograr cosas\l"
	.string "grandiosas.$"

MtChimney_Text_ShelbyRematchDefeat:
	.string "Cielos, no puede ser.\n"
	.string "¡Vaya, eres increíble!$"

MtChimney_Text_ShelbyPostRematch:
	.string "Tal vez tu corazón se ha vuelto uno\n"
	.string "con el de tus POKéMON.$"

MtChimney_Text_MelissaIntro:
	.string "Tengo el fuego interno, nene.\n"
	.string "¡No aguanto más! ¡Tengo que luchar!$"

MtChimney_Text_MelissaDefeat:
	.string "Ooh, that was a scorching-hot match!$"

MtChimney_Text_MelissaPostBattle:
	.string "El calor del MT. CHIMNEY me\n"
	.string "reconforta, ¡cariño!$"

MtChimney_Text_SheilaIntro:
	.string "Al fin llegué al MT. CHIMNEY.\n"
	.string "¡Quiero que mis POKéMON luchen!$"

MtChimney_Text_SheilaDefeat:
	.string "Tu forma de luchar...\n"
	.string "¡Es como una erupción del MT. CHIMNEY!$"

MtChimney_Text_SheilaPostBattle:
	.string "Como dije, al fin llegué al\n"
	.string "MT. CHIMNEY. Sería una pena si\l"
	.string "solo viniera a hacer turismo...\p"
	.string "Quiero luchar y comprar algunas\n"
	.string "GALLETAS de recuerdo.$"

MtChimney_Text_ShirleyIntro:
	.string "Desde que me bañé en las termas,\n"
	.string "¡Me he sentido genial!\l"
	.string "¡Seguro que voy a ganar!$"

MtChimney_Text_ShirleyDefeat:
	.string "¡Ay!\n"
	.string "El agua me da escalofríos.$"

MtChimney_Text_ShirleyPostBattle:
	.string "Tendré que darme otro chapuzón en las\n"
	.string "aguas termales. ¿Vienes conmigo?\p"
	.string "¡Es broma!$"

MtChimney_Text_SawyerIntro:
	.string "¡Qué montaña tan linda! ¡Hay mucha\n"
	.string "gente fogosa para hacer compañía!$"

MtChimney_Text_SawyerDefeat:
	.string "Oh, you're a real firebrand, too!$"

MtChimney_Text_SawyerPostBattle:
	.string "¡Necesito un baño en las AGUAS\n"
	.string "TERMALES DE LAVARIDGE con los locales!$"

MtChimney_Text_SawyerRegister:
	.string "Me gustan las bolitas de fuego\n"
	.string "Déjame registrarte en mi POKéNAV.$"

MtChimney_Text_SawyerRematchIntro:
	.string "como tú. Me encanta estar rodeada\n"
	.string "por estos rumbos. ¡No perderé!$"

MtChimney_Text_SawyerRematchDefeat:
	.string "Gosh, you're still the same\n"
	.string "tan impulsiva como antes!$"

MtChimney_Text_SawyerPostRematch:
	.string "La verdad es que hace calor aquí.\n"
	.string "Llevo demasiada ropa para este lugar.$"
