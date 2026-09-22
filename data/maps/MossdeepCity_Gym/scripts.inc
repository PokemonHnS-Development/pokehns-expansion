MossdeepCity_Gym_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MossdeepCity_Gym_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, MossdeepCity_Gym_OnLoad
	.byte 0

@ NOTE: Mossdeep Gym was redesigned between R/S and E. Leftover (and now functionally unused) scripts are commented below

MossdeepCity_Gym_OnTransition:
	setflag FLAG_TEMP_HIDE_FOLLOWER @ Hide follower since it can collide with moving statues
	end

@ All the below checks are leftover from RS. FLAG_MOSSDEEP_GYM_SWITCH_X is never set
MossdeepCity_Gym_OnLoad:
	goto_if_set FLAG_MOSSDEEP_GYM_SWITCH_1, MossdeepCity_Gym_EventScript_SetSwitch1Metatiles
	goto MossdeepCity_Gym_EventScript_CheckSwitch2
	end

MossdeepCity_Gym_EventScript_CheckSwitch2::
	goto_if_set FLAG_MOSSDEEP_GYM_SWITCH_2, MossdeepCity_Gym_EventScript_SetSwitch2Metatiles
	goto MossdeepCity_Gym_EventScript_CheckSwitch3
	end

MossdeepCity_Gym_EventScript_CheckSwitch3::
	goto_if_set FLAG_MOSSDEEP_GYM_SWITCH_3, MossdeepCity_Gym_EventScript_SetSwitch3Metatiles
	goto MossdeepCity_Gym_EventScript_CheckSwitch4
	end

MossdeepCity_Gym_EventScript_CheckSwitch4::
	goto_if_set FLAG_MOSSDEEP_GYM_SWITCH_4, MossdeepCity_Gym_EventScript_SetSwitch4Metatiles
	end

@ All the below set metatile scripts are leftover from RS and are functionally unused
MossdeepCity_Gym_EventScript_SetSwitch1Metatiles::
	setmetatile 5, 5, METATILE_RSMossdeepGym_RedArrow_Right, FALSE
	setmetatile 2, 7, METATILE_RSMossdeepGym_Switch_Down, TRUE
	goto MossdeepCity_Gym_EventScript_CheckSwitch2
	end

MossdeepCity_Gym_EventScript_SetSwitch2Metatiles::
	setmetatile 8, 14, METATILE_RSMossdeepGym_RedArrow_Right, FALSE
	setmetatile 8, 10, METATILE_RSMossdeepGym_Switch_Down, TRUE
	goto MossdeepCity_Gym_EventScript_CheckSwitch3
	end

MossdeepCity_Gym_EventScript_SetSwitch3Metatiles::
	setmetatile 15, 17, METATILE_RSMossdeepGym_RedArrow_Left, FALSE
	setmetatile 17, 15, METATILE_RSMossdeepGym_Switch_Down, TRUE
	goto MossdeepCity_Gym_EventScript_CheckSwitch4
	end

MossdeepCity_Gym_EventScript_SetSwitch4Metatiles::
	setmetatile 1, 23, METATILE_RSMossdeepGym_RedArrow_Up, FALSE
	setmetatile 5, 24, METATILE_RSMossdeepGym_Switch_Down, TRUE
	end

MossdeepCity_Gym_EventScript_TateAndLiza::
	trainerbattle_double TRAINER_TATE_AND_LIZA_1, MossdeepCity_Gym_Text_TateAndLizaIntro, MossdeepCity_Gym_Text_TateAndLizaDefeat, MossdeepCity_Gym_Text_TateAndLizaNeedTwoMons, MossdeepCity_Gym_EventScript_TateAndLizaDefeated, NO_MUSIC
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, MossdeepCity_Gym_EventScript_TateAndLizaRematch
	goto_if_unset FLAG_RECEIVED_TM_CALM_MIND, MossdeepCity_Gym_EventScript_GiveCalmMind2
	msgbox MossdeepCity_Gym_Text_TateAndLizaPostBattle, MSGBOX_DEFAULT
	release
	end

MossdeepCity_Gym_EventScript_TateAndLizaDefeated::
	message MossdeepCity_Gym_Text_ReceivedMindBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox MossdeepCity_Gym_Text_ExplainMindBadgeTakeThis, MSGBOX_DEFAULT
	setflag FLAG_DEFEATED_MOSSDEEP_GYM
	setflag FLAG_BADGE07_GET
	setflag FLAG_HIDE_AQUA_HIDEOUT_GRUNTS
	clearflag FLAG_HIDE_SLATEPORT_CITY_STERNS_SHIPYARD_MR_BRINEY
	clearflag FLAG_UNKNOWN_0x393
	setvar VAR_0x8008, 7
	call Common_EventScript_SetGymTrainers
	clearflag FLAG_HIDE_SLATEPORT_CITY_HARBOR_PATRONS
	clearflag FLAG_HIDE_MOSSDEEP_CITY_TEAM_MAGMA
	clearflag FLAG_HIDE_MOSSDEEP_CITY_SPACE_CENTER_1F_TEAM_MAGMA
	clearflag FLAG_HIDE_MOSSDEEP_CITY_SPACE_CENTER_2F_TEAM_MAGMA
	clearflag FLAG_HIDE_MOSSDEEP_CITY_SPACE_CENTER_2F_STEVEN
	setvar VAR_MOSSDEEP_CITY_STATE, 1
	setflag FLAG_HIDE_MOSSDEEP_CITY_SPACE_CENTER_1F_STEVEN
	setvar VAR_MOSSDEEP_SPACE_CENTER_STATE, 1
	call MossdeepCity_Gym_EventScript_GiveCalmMind
	closemessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox MossdeepCity_Gym_Text_RegisteredTateAndLiza, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_TATE_AND_LIZA_MATCH_CALL
	release
	end

MossdeepCity_Gym_EventScript_GiveCalmMind2::
	giveitem ITEM_TM_CALM_MIND
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	msgbox MossdeepCity_Gym_Text_ExplainCalmMind, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM_CALM_MIND
	release
	end

MossdeepCity_Gym_EventScript_GiveCalmMind::
	giveitem ITEM_TM_CALM_MIND
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_BagIsFull
	msgbox MossdeepCity_Gym_Text_ExplainCalmMind, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM_CALM_MIND
	return

MossdeepCity_Gym_EventScript_TateAndLizaRematch::
	trainerbattle_rematch_double TRAINER_TATE_AND_LIZA_1, MossdeepCity_Gym_Text_TateAndLizaPreRematch, MossdeepCity_Gym_Text_TateAndLizaRematchDefeat, MossdeepCity_Gym_Text_TateAndLizaRematchNeedTwoMons
	msgbox MossdeepCity_Gym_Text_TateAndLizaPostRematch, MSGBOX_AUTOCLOSE
	end

@ All the below switch scripts are leftover from RS and are functionally unused
MossdeepCity_Gym_EventScript_Switch1::
	lockall
	goto_if_set FLAG_MOSSDEEP_GYM_SWITCH_1, MossdeepCity_Gym_EventScript_ClearSwitch1
	setflag FLAG_MOSSDEEP_GYM_SWITCH_1
	applymovement LOCALID_PLAYER, MossdeepCity_Gym_Movement_WaitAfterSwitchUse
	waitmovement 0
	setmetatile 5, 5, METATILE_RSMossdeepGym_RedArrow_Right, FALSE
	setmetatile 2, 7, METATILE_RSMossdeepGym_Switch_Down, TRUE
	goto MossdeepCity_Gym_EventScript_DrawMapAfterSwitchUsed
	end

MossdeepCity_Gym_EventScript_DrawMapAfterSwitchUsed::
	special DrawWholeMapView
	playse SE_CLICK
	releaseall
	end

MossdeepCity_Gym_EventScript_ClearSwitch1::
	clearflag FLAG_MOSSDEEP_GYM_SWITCH_1
	applymovement LOCALID_PLAYER, MossdeepCity_Gym_Movement_WaitAfterSwitchUse
	waitmovement 0
	setmetatile 5, 5, METATILE_RSMossdeepGym_RedArrow_Left, FALSE
	setmetatile 2, 7, METATILE_RSMossdeepGym_Switch_Up, TRUE
	goto MossdeepCity_Gym_EventScript_DrawMapAfterSwitchUsed
	end

MossdeepCity_Gym_EventScript_Switch2::
	lockall
	goto_if_set FLAG_MOSSDEEP_GYM_SWITCH_2, MossdeepCity_Gym_EventScript_ClearSwitch2
	setflag FLAG_MOSSDEEP_GYM_SWITCH_2
	applymovement LOCALID_PLAYER, MossdeepCity_Gym_Movement_WaitAfterSwitchUse
	waitmovement 0
	setmetatile 8, 14, METATILE_RSMossdeepGym_RedArrow_Right, FALSE
	setmetatile 8, 10, METATILE_RSMossdeepGym_Switch_Down, TRUE
	goto MossdeepCity_Gym_EventScript_DrawMapAfterSwitchUsed
	end

MossdeepCity_Gym_EventScript_ClearSwitch2::
	clearflag FLAG_MOSSDEEP_GYM_SWITCH_2
	applymovement LOCALID_PLAYER, MossdeepCity_Gym_Movement_WaitAfterSwitchUse
	waitmovement 0
	setmetatile 8, 14, METATILE_RSMossdeepGym_RedArrow_Down, FALSE
	setmetatile 8, 10, METATILE_RSMossdeepGym_Switch_Up, TRUE
	goto MossdeepCity_Gym_EventScript_DrawMapAfterSwitchUsed
	end

MossdeepCity_Gym_EventScript_Switch3::
	lockall
	goto_if_set FLAG_MOSSDEEP_GYM_SWITCH_3, MossdeepCity_Gym_EventScript_ClearSwitch3
	setflag FLAG_MOSSDEEP_GYM_SWITCH_3
	applymovement LOCALID_PLAYER, MossdeepCity_Gym_Movement_WaitAfterSwitchUse
	waitmovement 0
	setmetatile 15, 17, METATILE_RSMossdeepGym_RedArrow_Left, FALSE
	setmetatile 17, 15, METATILE_RSMossdeepGym_Switch_Down, TRUE
	goto MossdeepCity_Gym_EventScript_DrawMapAfterSwitchUsed
	end

MossdeepCity_Gym_EventScript_ClearSwitch3::
	clearflag FLAG_MOSSDEEP_GYM_SWITCH_3
	applymovement LOCALID_PLAYER, MossdeepCity_Gym_Movement_WaitAfterSwitchUse
	waitmovement 0
	setmetatile 15, 17, METATILE_RSMossdeepGym_RedArrow_Right, FALSE
	setmetatile 17, 15, METATILE_RSMossdeepGym_Switch_Up, TRUE
	goto MossdeepCity_Gym_EventScript_DrawMapAfterSwitchUsed
	end

MossdeepCity_Gym_EventScript_Switch4::
	lockall
	goto_if_set FLAG_MOSSDEEP_GYM_SWITCH_4, MossdeepCity_Gym_EventScript_ClearSwitch4
	setflag FLAG_MOSSDEEP_GYM_SWITCH_4
	applymovement LOCALID_PLAYER, MossdeepCity_Gym_Movement_WaitAfterSwitchUse
	waitmovement 0
	setmetatile 1, 23, METATILE_RSMossdeepGym_RedArrow_Up, FALSE
	setmetatile 5, 24, METATILE_RSMossdeepGym_Switch_Down, TRUE
	goto MossdeepCity_Gym_EventScript_DrawMapAfterSwitchUsed
	end

MossdeepCity_Gym_EventScript_ClearSwitch4::
	clearflag FLAG_MOSSDEEP_GYM_SWITCH_4
	applymovement LOCALID_PLAYER, MossdeepCity_Gym_Movement_WaitAfterSwitchUse
	waitmovement 0
	setmetatile 1, 23, METATILE_RSMossdeepGym_RedArrow_Right, FALSE
	setmetatile 5, 24, METATILE_RSMossdeepGym_Switch_Up, TRUE
	goto MossdeepCity_Gym_EventScript_DrawMapAfterSwitchUsed
	end

MossdeepCity_Gym_EventScript_WarpToEntrance::
	lockall
	warpmossdeepgym MAP_MOSSDEEP_CITY_GYM, 7, 30
	waitstate
	releaseall
	end

MossdeepCity_Gym_EventScript_Preston::
	trainerbattle_single TRAINER_PRESTON, MossdeepCity_Gym_Text_PrestonIntro, MossdeepCity_Gym_Text_PrestonDefeat
	msgbox MossdeepCity_Gym_Text_PrestonPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Virgil::
	trainerbattle_single TRAINER_VIRGIL, MossdeepCity_Gym_Text_VirgilIntro, MossdeepCity_Gym_Text_VirgilDefeat
	msgbox MossdeepCity_Gym_Text_VirgilPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Blake::
	trainerbattle_single TRAINER_BLAKE, MossdeepCity_Gym_Text_BlakeIntro, MossdeepCity_Gym_Text_BlakeDefeat
	msgbox MossdeepCity_Gym_Text_BlakePostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Hannah::
	trainerbattle_single TRAINER_HANNAH, MossdeepCity_Gym_Text_HannahIntro, MossdeepCity_Gym_Text_HannahDefeat
	msgbox MossdeepCity_Gym_Text_HannahPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Samantha::
	trainerbattle_single TRAINER_SAMANTHA, MossdeepCity_Gym_Text_SamanthaIntro, MossdeepCity_Gym_Text_SamanthaDefeat
	msgbox MossdeepCity_Gym_Text_SamanthaPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Maura::
	trainerbattle_single TRAINER_MAURA, MossdeepCity_Gym_Text_MauraIntro, MossdeepCity_Gym_Text_MauraDefeat
	msgbox MossdeepCity_Gym_Text_MauraPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Sylvia::
	trainerbattle_single TRAINER_SYLVIA, MossdeepCity_Gym_Text_SylviaIntro, MossdeepCity_Gym_Text_SylviaDefeat
	msgbox MossdeepCity_Gym_Text_SylviaPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Nate::
	trainerbattle_single TRAINER_NATE, MossdeepCity_Gym_Text_NateIntro, MossdeepCity_Gym_Text_NateDefeat
	msgbox MossdeepCity_Gym_Text_NatePostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Macey::
	trainerbattle_single TRAINER_MACEY, MossdeepCity_Gym_Text_MaceyIntro, MossdeepCity_Gym_Text_MaceyDefeat
	msgbox MossdeepCity_Gym_Text_MaceyPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Clifford::
	trainerbattle_single TRAINER_CLIFFORD, MossdeepCity_Gym_Text_CliffordIntro, MossdeepCity_Gym_Text_CliffordDefeat
	msgbox MossdeepCity_Gym_Text_CliffordPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Nicholas::
	trainerbattle_single TRAINER_NICHOLAS, MossdeepCity_Gym_Text_NicholasIntro, MossdeepCity_Gym_Text_NicholasDefeat
	msgbox MossdeepCity_Gym_Text_NicholasPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Kathleen::
	trainerbattle_single TRAINER_KATHLEEN, MossdeepCity_Gym_Text_KathleenIntro, MossdeepCity_Gym_Text_KathleenDefeat
	msgbox MossdeepCity_Gym_Text_KathleenPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_GymGuide::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_MOSSDEEP_GYM, MossdeepCity_Gym_EventScript_GymGuidePostVictory
	msgbox MossdeepCity_Gym_Text_GymGuideAdvice, MSGBOX_DEFAULT
	release
	end

MossdeepCity_Gym_EventScript_GymGuidePostVictory::
	msgbox MossdeepCity_Gym_Text_GymGuidePostVictory, MSGBOX_DEFAULT
	release
	end

@ Leftover from RS, functionally unused
MossdeepCity_Gym_Movement_WaitAfterSwitchUse:
	delay_16
	delay_16
	step_end

MossdeepCity_Gym_EventScript_LeftGymStatue::
	lockall
	goto_if_set FLAG_BADGE07_GET, MossdeepCity_Gym_EventScript_GymStatueCertified
	goto MossdeepCity_Gym_EventScript_GymStatue
	end

MossdeepCity_Gym_EventScript_RightGymStatue::
	lockall
	goto_if_set FLAG_BADGE07_GET, MossdeepCity_Gym_EventScript_GymStatueCertified
	goto MossdeepCity_Gym_EventScript_GymStatue
	end

MossdeepCity_Gym_EventScript_GymStatueCertified::
	msgbox MossdeepCity_Gym_Text_GymStatueCertified, MSGBOX_DEFAULT
	releaseall
	end

MossdeepCity_Gym_EventScript_GymStatue::
	msgbox MossdeepCity_Gym_Text_GymStatue, MSGBOX_DEFAULT
	releaseall
	end

MossdeepCity_Gym_EventScript_YellowFloorSwitch::
	playse SE_SWITCH
	waitse
	playse SE_REPEL
	initrotatingtilepuzzle FALSE
	moverotatingtileobjects 0
	waitmovement 0
	turnrotatingtileobjects
	waitmovement 0
	freerotatingtilepuzzle
	end

MossdeepCity_Gym_EventScript_BlueFloorSwitch::
	playse SE_SWITCH
	waitse
	playse SE_REPEL
	initrotatingtilepuzzle FALSE
	moverotatingtileobjects 1
	waitmovement 0
	turnrotatingtileobjects
	waitmovement 0
	freerotatingtilepuzzle
	end

MossdeepCity_Gym_EventScript_GreenFloorSwitch::
	playse SE_SWITCH
	waitse
	playse SE_REPEL
	initrotatingtilepuzzle FALSE
	moverotatingtileobjects 2
	waitmovement 0
	turnrotatingtileobjects
	waitmovement 0
	freerotatingtilepuzzle
	end

MossdeepCity_Gym_EventScript_PurpleFloorSwitch::
	playse SE_SWITCH
	waitse
	playse SE_REPEL
	initrotatingtilepuzzle FALSE
	moverotatingtileobjects 3
	waitmovement 0
	turnrotatingtileobjects
	waitmovement 0
	freerotatingtilepuzzle
	end

MossdeepCity_Gym_EventScript_RedFloorSwitch::
	playse SE_SWITCH
	waitse
	playse SE_REPEL
	initrotatingtilepuzzle FALSE
	moverotatingtileobjects 4
	waitmovement 0
	turnrotatingtileobjects
	waitmovement 0
	freerotatingtilepuzzle
	end

MossdeepCity_Gym_Text_GymGuideAdvice:
	.string "Hola, ¿cómo va todo, futuro CAMPEÓN?\n"
	.string "¿{PLAYER}?\p"
	.string "Los LÍDERES de GIMNASIO de aquí\n"
	.string "usan POKéMON tipo PSÍQUICO.\p"
	.string "Si luchas contra ellos con\n"
	.string "POKéMON tipo LUCHA o VENENO,\l"
	.string "¡te harán un daño horrible!\p"
	.string "Además, te atacarán con\n"
	.string "combinaciones de ataques increíbles.\p"
	.string "Si quieres ganar, debes demostrar\n"
	.string "qué tan unido estás a tus\l"
	.string "POKéMON. ¡Ve a por ello!$"

MossdeepCity_Gym_Text_GymGuidePostVictory:
	.string "¡Vaya, eres asombroso!\n"
	.string "¡Eres un gran ENTRENADOR!$"

MossdeepCity_Gym_Text_PrestonIntro:
	.string "Las batallas dependen de la fuerza\n"
	.string "del espíritu! ¡El débil no ganará!$"

MossdeepCity_Gym_Text_PrestonDefeat:
	.string "¡Perdí!\n"
	.string "¡Debo templar mi espíritu otra vez!$"

MossdeepCity_Gym_Text_PrestonPostBattle:
	.string "Los indecisos pierden.\n"
	.string "Esa es mi advertencia para ti.$"

MossdeepCity_Gym_Text_VirgilIntro:
	.string "¡Muéstrame tu talento!$"

MossdeepCity_Gym_Text_VirgilDefeat:
	.string "¡Tienes un talento espectacular!$"

MossdeepCity_Gym_Text_VirgilPostBattle:
	.string "Si existen prodigios en el mundo,\n"
	.string "¡entonces son nuestros LÍDERES de GYM!\p"
	.string "Sin embargo, puede que seas más\n"
	.string "talentoso que ellos...$"

MossdeepCity_Gym_Text_BlakeIntro:
	.string "Fufufufu... ¡Mira cómo levito una\n"
	.string "POKé BALL con telequinesis!\p"
	.string "¡Wrooooooooaaaar!\n"
	.string "... ... ... ... ... ... ...\p"
	.string "A veces, estoy desincronizado...$"

MossdeepCity_Gym_Text_BlakeDefeat:
	.string "¡Mis habilidades de batalla POKéMON\n"
	.string "también están desincronizadas!$"

MossdeepCity_Gym_Text_BlakePostBattle:
	.string "Una POKé BALL pesaba mucho para\n"
	.string "mi mente. Pero esta pelusa...\p"
	.string "¡Whoooooooooooooooh!\n"
	.string "... ... ... ... ... ...\p"
	.string "¡No, no estoy haciendo trampa!\n"
	.string "¡No soplé la pelusa! ¡Lo juro!$"

MossdeepCity_Gym_Text_HannahIntro:
	.string "Cuando pierdas, no seas tan duro\n"
	.string "a ti mismo.\p"
	.string "No es que seas débil... ¡es que yo\n"
	.string "soy muy fuerte!$"

MossdeepCity_Gym_Text_HannahDefeat:
	.string "¡Eres demasiado fuerte!$"

MossdeepCity_Gym_Text_HannahPostBattle:
	.string "No me desanimaré por haber\n"
	.string "perdido. Solo debo entrenar más.\p"
	.string "¡El optimismo es mi punto\n"
	.string "fuerte!$"

MossdeepCity_Gym_Text_SamanthaIntro:
	.string "Lo veo...\n"
	.string "Veo tu futuro...\p"
	.string "Si puedes vencerme, ¡te diré\n"
	.string "cuál es tu futuro!$"

MossdeepCity_Gym_Text_SamanthaDefeat:
	.string "I surrender!$"

MossdeepCity_Gym_Text_SamanthaPostBattle:
	.string "Librarás una batalla intensamente\n"
	.string "fuerte con nuestros LÍDERES de GYM...\p"
	.string "El resultado...\n"
	.string "¡No me lo preguntes a mí!$"

MossdeepCity_Gym_Text_MauraIntro:
	.string "Los caminos que has recorrido...\n"
	.string "Lo que has experimentado...\p"
	.string "¡Ven a mí con todo lo que has\n"
	.string "aprendido!$"

MossdeepCity_Gym_Text_MauraDefeat:
	.string "¡Has recorrido un camino de grandeza!$"

MossdeepCity_Gym_Text_MauraPostBattle:
	.string "Un futuro brillante espera a quien\n"
	.string "ha trabajado con diligencia.\p"
	.string "Para quienes fueron perezosos,\n"
	.string "solo hay desesperación al final.\p"
	.string "Todo vuelve a quien lo hace...$"

MossdeepCity_Gym_Text_SylviaIntro:
	.string "¡Aun arriesgando mi vida, ganaré\n"
	.string "esta batalla!$"

MossdeepCity_Gym_Text_SylviaDefeat:
	.string "Lo que haces...\n"
	.string "me horroriza...$"

MossdeepCity_Gym_Text_SylviaPostBattle:
	.string "Cómo te atreves a vencerme...\p"
	.string "No será mi culpa si algo\n"
	.string "terrible te sucede...$"

MossdeepCity_Gym_Text_NateIntro:
	.string "Jo, jo, jo.\p"
	.string "Debo mostrarte lo tenaz que soy\n"
	.string "el tipo PSÍQUICO puede ser.$"

MossdeepCity_Gym_Text_NateDefeat:
	.string "¡Oh! Vaya, vaya!\n"
	.string "¡Tu estilo de combate es genial!$"

MossdeepCity_Gym_Text_NatePostBattle:
	.string "Yo... no dejo que la derrota me\n"
	.string "aunque sea m-muy mal.$"

MossdeepCity_Gym_Text_KathleenIntro:
	.string "¡Déjame mostrarte un momento\n"
	.string "perfectamente horrible y aterrador!$"

MossdeepCity_Gym_Text_KathleenDefeat:
	.string "N-nooooo!$"

MossdeepCity_Gym_Text_KathleenPostBattle:
	.string "¡Tu vitalidad es contagiosa!\n"
	.string "¡Aléjate de mí rápido!$"

MossdeepCity_Gym_Text_CliffordIntro:
	.string "Ya no estoy en mi mejor momento, pero\n"
	.string "no me trates con condescendencia.$"

MossdeepCity_Gym_Text_CliffordDefeat:
	.string "Ah, rebosas el poder\n"
	.string "de la juventud!$"

MossdeepCity_Gym_Text_CliffordPostBattle:
	.string "Parece que no pude superar\n"
	.string "tu energía juvenil.$"

MossdeepCity_Gym_Text_MaceyIntro:
	.string "¡No llegarás hasta el final!\n"
	.string "¡No si yo puedo evitarlo!$"

MossdeepCity_Gym_Text_MaceyDefeat:
	.string "¿Cómo puedes ser tan\n"
	.string "ridículamente fuerte?$"

MossdeepCity_Gym_Text_MaceyPostBattle:
	.string "¡Humph! Serás fuerte, pero no eres\n"
	.string "apto para el tipo PSÍQUICO!\p"
	.string "¡Tu forma de luchar es muy brutal!$"

MossdeepCity_Gym_Text_NicholasIntro:
	.string "¡Wroooar! ¡Prueba el poder de mis\n"
	.string "super POKéMON en combate!$"

MossdeepCity_Gym_Text_NicholasDefeat:
	.string "Oh!\n"
	.string "¡Acabado!$"

MossdeepCity_Gym_Text_NicholasPostBattle:
	.string "¡Bien! Creo que crearé un poder\n"
	.string "invencible para POKéMON ahora.$"

MossdeepCity_Gym_Text_TateAndLizaIntro:
	.string "TATE: Jejeje... ¿Te sorprendiste?\pLIZA:\nJajaja... ¿Te sorprendiste?\pTATE: ¿Que\nhay dos LÍDERES de GIMNASIO?\nLIZA: ¿Que hay dos LÍDERES de\nGIMNASIO?\pTATE: ¡Somos gemelos!\nLIZA: ¡Somos gemelas!\pTATE: No hace\nfalta hablar porque...\nLIZA: Cada uno puede determinar\nqué...\pTATE: El otro está pensando...\nLIZA: ¡Todo está en la mente!\pTATE:\nNuestra combinación...\nLIZA: ¿Podrás vencerla?$"

MossdeepCity_Gym_Text_TateAndLizaDefeat:
	.string "TATE: ¡¿Qué?! Nuestra combinación...\n"
	.string "LIZA: ¡Fue destrozada!\p"
	.string "TATE: No hay remedio. Ganaste...\n"
	.string "LIZA: Toma esto en reconocimiento.$"

MossdeepCity_Gym_Text_ReceivedMindBadge:
	.string "{PLAYER} recibió la MEDALLA MENTE\n"
	.string "de TATE y LIZA.$"

MossdeepCity_Gym_Text_ExplainMindBadgeTakeThis:
	.string "TATE: La MEDALLA MENTE sube el\n"
	.string "ATQ. ESP. y DEF. ESP. de POKéMON.\p"
	.string "LIZA: También permite usar el MO\n"
	.string "BUCEO fuera de combate.\p"
	.string "TATE: También deberías llevarte esto.$"

MossdeepCity_Gym_Text_ExplainCalmMind:
	.string "TATE: Esa MT04 contiene...\n"
	.string "LIZA: ¡CALMA!\p"
	.string "TATE: Sube el ATQ. ESP. y...\n"
	.string "LIZA: ¡Sube la DEF. ESP.!\p"
	.string "TATE: Es un movimiento perfecto...\n"
	.string "LIZA: ¡Para POKéMON PSÍQUICOS!\p"
	.string "... ... ... ... ... ...$"

MossdeepCity_Gym_Text_RegisteredTateAndLiza:
	.string "LÍDERES de GIMNASIO TATE y LIZA\n"
	.string "en el POKéNAV.$"

MossdeepCity_Gym_Text_TateAndLizaPostBattle:
	.string "TATE: Parece que el vínculo contigo\n"
	.string "y tus POKéMON es mucho más fuerte que\l"
	.string "el vínculo que tenemos como gemelos.\p"
	.string "LIZA: ¡Te volverás aún más fuerte!\n"
	.string "Peleamos contigo, así que lo sabemos.$"

MossdeepCity_Gym_Text_TateAndLizaNeedTwoMons:
	.string "TATE: Jejeje... ¿Te sorprendiste?\pLIZA:\n¿Que hay dos LÍDERES de GIMNASIO?\pTATE:\nUps, solo tienes un...\nLIZA: POKéMON que puede luchar.\pTATE:\n¡No podemos luchar así!\pLIZA: Si\nquieres retarnos,\ntrae más POKéMON.$"

MossdeepCity_Gym_Text_GymStatue:
	.string "MOSSDEEP CITY POKéMON GYM$"

MossdeepCity_Gym_Text_GymStatueCertified:
	.string "GIMNASIO POKéMON CIUDAD FONDO MAR\p"
	.string "LIZA AND TATE'S CERTIFIED TRAINERS:\n"
	.string "{PLAYER}$"

MossdeepCity_Gym_Text_TateAndLizaPreRematch:
	.string "TATE: POKéMON...\nLIZA: POKéMON...\pTATE: Al cambiar la\nmezcla del equipo...\nLIZA: El estilo de combate\ncambia.\pTATE: Pero yo...\nLIZA: Pero yo...\pTATE: ¡Siempre estaré\ncon LIZA!\nLIZA: ¡Siempre estaré con TATE!\pTATE:\nNuestra combinación...\nLIZA: ¡Te lo mostraremos una y otra\nvez!$"

MossdeepCity_Gym_Text_TateAndLizaRematchDefeat:
	.string "TATE: Tú y tu POKéMON...\n"
	.string "LIZA: ¡Es como si fueran hermanos!$"

MossdeepCity_Gym_Text_TateAndLizaPostRematch:
	.string "TATE: Puedes derribarnos,\n"
	.string "¡pero nunca nos rendiremos!\p"
	.string "LIZA: Porque nosotros dos,\n"
	.string "¡Siempre nos apoyamos mutuamente!$"

MossdeepCity_Gym_Text_TateAndLizaRematchNeedTwoMons:
	.string "TATE: Has vuelto...\n"
	.string "LIZA: Has vuelto...\p"
	.string "TATE: Para una revancha.\n"
	.string "LIZA: Para una revancha.\p"
	.string "TATE: Pero...\n"
	.string "LIZA: Para el combate...\p"
	.string "TATE: ¡Traes solo un POKéMON!\n"
	.string "LIZA: ¡Traes solo un POKéMON!\p"
	.string "TATE: Necesitamos que traigas...\n"
	.string "LIZA: Dos POKéMON la próxima vez.$"
