CeruleanCity_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, CeruleanCity_OnTransition
	.byte 0

CeruleanCity_OnTransition::
	setworldmapflag FLAG_WORLD_MAP_CERULEAN_CITY
	call_if_unset FLAG_GOT_SS_TICKET, CeruleanCity_EventScript_BlockExits
	end

CeruleanCity_EventScript_BlockExits::
	setobjectxyperm LOCALID_CERULEAN_POLICEMAN, 30, 12
	setobjectxyperm LOCALID_CERULEAN_SLOWBRO, 26, 31
	setobjectxyperm LOCALID_CERULEAN_LASS, 27, 31
	return

CeruleanCity_EventScript_RivalTriggerLeft::
	lockall
	setvar VAR_TEMP_1, 0
	goto CeruleanCity_EventScript_Rival
	end

CeruleanCity_EventScript_RivalTriggerMid::
	lockall
	setvar VAR_TEMP_1, 1
	setobjectxyperm LOCALID_CERULEAN_RIVAL, 23, 0
	goto CeruleanCity_EventScript_Rival
	end

CeruleanCity_EventScript_RivalTriggerRight::
	lockall
	setvar VAR_TEMP_1, 2
	setobjectxyperm LOCALID_CERULEAN_RIVAL, 24, 0
	goto CeruleanCity_EventScript_Rival
	end

CeruleanCity_EventScript_Rival::
	textcolor NPC_TEXT_COLOR_MALE
	setvar VAR_MAP_SCENE_ROUTE22, 2
	playbgm MUS_RG_ENCOUNTER_RIVAL, 0
	addobject LOCALID_CERULEAN_RIVAL
	applymovement LOCALID_CERULEAN_RIVAL, CeruleanCity_Movement_RivalEnter
	waitmovement 0
	msgbox CeruleanCity_Text_RivalIntro
	setvar VAR_LAST_TALKED, LOCALID_CERULEAN_RIVAL
	call_if_eq VAR_STARTER_MON, 2, CeruleanCity_EventScript_RivalSquirtle
	call_if_eq VAR_STARTER_MON, 1, CeruleanCity_EventScript_RivalBulbasaur
	call_if_eq VAR_STARTER_MON, 0, CeruleanCity_EventScript_RivalCharmander
	famechecker FAMECHECKER_BILL, 0
	msgbox CeruleanCity_Text_RivalPostBattle
	closemessage
	playbgm MUS_RG_RIVAL_EXIT, 0
	call_if_eq VAR_TEMP_1, 0, CeruleanCity_EventScript_RivalStartExit
	call_if_eq VAR_TEMP_1, 1, CeruleanCity_EventScript_RivalStartExit
	call_if_eq VAR_TEMP_1, 2, CeruleanCity_EventScript_RivalStartExitRight
	msgbox CeruleanCity_Text_OhRightLittlePresentAsFavor
	setvar VAR_MAP_SCENE_CERULEAN_CITY_RIVAL, 1
	setflag FLAG_GOT_FAME_CHECKER
	giveitem ITEM_FAME_CHECKER
	msgbox CeruleanCity_Text_ExplainFameCheckerSmellYa
	closemessage
	applymovement LOCALID_CERULEAN_RIVAL, CeruleanCity_Movement_RivalExit
	waitmovement 0
	fadedefaultbgm
	removeobject LOCALID_CERULEAN_RIVAL
	releaseall
	end

CeruleanCity_EventScript_RivalSquirtle::
	trainerbattle_no_intro TRAINER_RIVAL_CERULEAN_SQUIRTLE, CeruleanCity_Text_RivalDefeat
	return

CeruleanCity_EventScript_RivalBulbasaur::
	trainerbattle_no_intro TRAINER_RIVAL_CERULEAN_BULBASAUR, CeruleanCity_Text_RivalDefeat
	return

CeruleanCity_EventScript_RivalCharmander::
	trainerbattle_no_intro TRAINER_RIVAL_CERULEAN_CHARMANDER, CeruleanCity_Text_RivalDefeat
	return

CeruleanCity_EventScript_RivalStartExit::
	applymovement LOCALID_PLAYER, CeruleanCity_Movement_PlayerWatchRivalExit
	applymovement LOCALID_CERULEAN_RIVAL, CeruleanCity_Movement_RivalStartExit
	waitmovement 0
	return

CeruleanCity_EventScript_RivalStartExitRight::
	applymovement LOCALID_PLAYER, CeruleanCity_Movement_PlayerWatchRivalExitRight
	applymovement LOCALID_CERULEAN_RIVAL, CeruleanCity_Movement_RivalStartExitRight
	waitmovement 0
	return

CeruleanCity_Movement_PlayerWatchRivalExit::
	delay_16
	delay_8
	walk_in_place_faster_right
	delay_16
	walk_in_place_faster_down
	step_end

CeruleanCity_Movement_PlayerWatchRivalExitRight::
	delay_16
	delay_8
	walk_in_place_faster_left
	delay_16
	walk_in_place_faster_down
	step_end

CeruleanCity_Movement_RivalEnter::
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

CeruleanCity_Movement_RivalStartExit::
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	delay_16
	delay_16
	walk_left
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

CeruleanCity_Movement_RivalStartExitRight::
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	delay_16
	delay_16
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

CeruleanCity_Movement_RivalExit::
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

CeruleanCity_EventScript_Grunt::
	lock
	faceplayer
	goto_if_defeated TRAINER_TEAM_ROCKET_GRUNT_5, CeruleanCity_EventScript_GruntDefeated
	message CeruleanCity_Text_GruntIntro
	waitmessage
	playbgm MUS_RG_ENCOUNTER_ROCKET, 0
	waitbuttonpress
	trainerbattle_no_intro TRAINER_TEAM_ROCKET_GRUNT_5, CeruleanCity_Text_GruntDefeat
	setvar VAR_MAP_SCENE_CERULEAN_CITY_ROCKET, 1
	goto CeruleanCity_EventScript_GruntDefeated
	end

CeruleanCity_EventScript_GruntDefeated::
	msgbox CeruleanCity_Text_OkayIllReturnStolenTM
	checkitemspace ITEM_TM28
	goto_if_eq VAR_RESULT, FALSE, CeruleanCity_EventScript_NoRoomForTM28
	giveitem_msg CeruleanCity_Text_RecoveredTM28FromGrunt, ITEM_TM28
	msgbox CeruleanCity_Text_BetterGetMovingBye
	closemessage
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_CERULEAN_GRUNT
	fadescreenswapbuffers FADE_FROM_BLACK
	setflag FLAG_GOT_TM28_FROM_ROCKET
	release
	end

CeruleanCity_EventScript_NoRoomForTM28::
	textcolor NPC_TEXT_COLOR_MALE
	msgbox CeruleanCity_Text_MakeRoomForThisCantRun
	release
	end

CeruleanCity_EventScript_GruntTriggerTop::
	lockall
	setvar VAR_TEMP_1, 0
	applymovement LOCALID_CERULEAN_GRUNT, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	goto CeruleanCity_EventScript_GruntTrigger
	end

CeruleanCity_EventScript_GruntTriggerBottom::
	lockall
	setvar VAR_TEMP_1, 1
	applymovement LOCALID_CERULEAN_GRUNT, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	goto CeruleanCity_EventScript_GruntTrigger
	end

CeruleanCity_EventScript_GruntTrigger::
	textcolor NPC_TEXT_COLOR_MALE
	msgbox CeruleanCity_Text_GruntIntro
	setvar VAR_LAST_TALKED, LOCALID_CERULEAN_GRUNT
	trainerbattle_no_intro TRAINER_TEAM_ROCKET_GRUNT_5, CeruleanCity_Text_GruntDefeat
	setvar VAR_MAP_SCENE_CERULEAN_CITY_ROCKET, 1
	goto CeruleanCity_EventScript_GruntDefeated
	end

CeruleanCity_EventScript_Policeman::
	lock
	faceplayer
	msgbox CeruleanCity_Text_PeopleHereWereRobbed
	closemessage
	applymovement LOCALID_CERULEAN_POLICEMAN, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

CeruleanCity_EventScript_LittleBoy::
	lock
	faceplayer
	goto_if_set FLAG_GOT_SS_TICKET, CeruleanCity_EventScript_LittleBoySlowbroMoved
	msgbox CeruleanCity_Text_IfSlowbroWasntThereCouldCutTree
	release
	end

CeruleanCity_EventScript_LittleBoySlowbroMoved::
	msgbox CeruleanCity_Text_YouCanCutDownSmallTrees
	release
	end

CeruleanCity_EventScript_BaldingMan::
	msgbox CeruleanCity_Text_PokemonEncyclopediaAmusing, MSGBOX_NPC
	end

CeruleanCity_EventScript_Youngster::
	msgbox CeruleanCity_Text_TrainerLifeIsToughIsntIt, MSGBOX_NPC
	end

CeruleanCity_EventScript_CeruleanCaveGuard::
	msgbox CeruleanCity_Text_ThisIsCeruleanCave, MSGBOX_NPC
	end

CeruleanCity_EventScript_Woman::
	lock
	faceplayer
	msgbox CeruleanCity_Text_WantBrightRedBicycle
	closemessage
	applymovement LOCALID_CERULEAN_WOMAN, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

CeruleanCity_EventScript_Lass::
	lock
	random 3
	copyvar VAR_0x8008, VAR_RESULT
	call_if_eq VAR_0x8008, 0, CeruleanCity_EventScript_SlowbroCommand1
	call_if_eq VAR_0x8008, 1, CeruleanCity_EventScript_SlowbroCommand2
	call_if_eq VAR_0x8008, 2, CeruleanCity_EventScript_SlowbroCommand3
	waitmessage
	delay 40
	playse SE_PIN
	applymovement LOCALID_CERULEAN_SLOWBRO, Common_Movement_QuestionMark
	waitmovement 0
	delay 30
	call_if_eq VAR_0x8008, 0, CeruleanCity_EventScript_SlowbroFailed1
	call_if_eq VAR_0x8008, 1, CeruleanCity_EventScript_SlowbroFailed2
	call_if_eq VAR_0x8008, 2, CeruleanCity_EventScript_SlowbroFailed3
	release
	end

CeruleanCity_EventScript_SlowbroCommand1::
	message CeruleanCity_Text_SlowbroUseSonicboom
	return

CeruleanCity_EventScript_SlowbroCommand2::
	message CeruleanCity_Text_SlowbroPunch
	return

CeruleanCity_EventScript_SlowbroCommand3::
	message CeruleanCity_Text_SlowbroWithdraw
	return

CeruleanCity_EventScript_SlowbroFailed1::
	msgbox CeruleanCity_Text_SlowbroPayAttention
	return

CeruleanCity_EventScript_SlowbroFailed2::
	msgbox CeruleanCity_Text_NoYouBlewItAgain
	return

CeruleanCity_EventScript_SlowbroFailed3::
	msgbox CeruleanCity_Text_HardToControlMonsObedience
	return

CeruleanCity_EventScript_Slowbro::
	lock
	random 4
	copyvar VAR_0x8008, VAR_RESULT
	call_if_eq VAR_0x8008, 0, CeruleanCity_EventScript_SlowbroText1
	call_if_eq VAR_0x8008, 1, CeruleanCity_EventScript_SlowbroText2
	call_if_eq VAR_0x8008, 2, CeruleanCity_EventScript_SlowbroText3
	call_if_eq VAR_0x8008, 3, CeruleanCity_EventScript_SlowbroText4
	release
	end

CeruleanCity_EventScript_SlowbroText1::
	msgbox CeruleanCity_Text_SlowbroTookSnooze
	return

CeruleanCity_EventScript_SlowbroText2::
	msgbox CeruleanCity_Text_SlowbroLoafingAround
	return

CeruleanCity_EventScript_SlowbroText3::
	msgbox CeruleanCity_Text_SlowbroTurnedAway
	return

CeruleanCity_EventScript_SlowbroText4::
	msgbox CeruleanCity_Text_SlowbroIgnoredOrders
	return

CeruleanCity_EventScript_CitySign::
	msgbox CeruleanCity_Text_CitySign, MSGBOX_SIGN
	end

CeruleanCity_EventScript_TrainerTips::
	msgbox CeruleanCity_Text_TrainerTipsHeldItems, MSGBOX_SIGN
	end

CeruleanCity_EventScript_BikeShopSign::
	msgbox CeruleanCity_Text_BikeShopSign, MSGBOX_SIGN
	end

CeruleanCity_EventScript_GymSign::
	lockall
	famechecker FAMECHECKER_MISTY, 0
	msgbox CeruleanCity_Text_GymSign
	releaseall
	end

CeruleanCity_Text_RivalIntro::
	.string "{RIVAL}: Yo! {PLAYER}!\p"
	.string "¿Sigues batallando allá\n"
	.string "atrás?\p"
	.string "¡Me va genial! Atrapé un montón\n"
	.string "of strong and smart POKéMON!\p"
	.string "Ven, déjame ver qué atrapaste,\n"
	.string "¡{PLAYER}!$"

CeruleanCity_Text_RivalDefeat::
	.string "¡Hola!\n"
	.string "¡Tranquilo!\l"
	.string "¡Ya ganaste!$"

CeruleanCity_Text_RivalPostBattle::
	.string "{RIVAL}: Oye, ¿adivina qué?\p"
	.string "Fui a casa de BILL y logré que\n"
	.string "show me his rare POKéMON.\p"
	.string "Eso agregó muchas páginas a mi\n"
	.string "POKéDEX!\p"
	.string "Al fin y al cabo, BILL es famoso\n"
	.string "como un POKéMANÍACO.\p"
	.string "Inventó también el Sistema de\n"
	.string "por su sistema en PC también.\p"
	.string "Como usas su sistema,\n"
	.string "deberías ir a agradecerle.\p"
	.string "¡Bueno, mejor me voy!\n"
	.string "Smell ya later!$"

CeruleanCity_Text_OhRightLittlePresentAsFavor::
	.string "Oh, yeah, right.\p"
	.string "Siento lástima por ti. De verdad.\n"
	.string "Siempre vas arrastrándote detrás\p"
	.string "de mí. Así que aquí, te doy un\n"
	.string "pequeño regalo como favor.$"

CeruleanCity_Text_ExplainFameCheckerSmellYa::
	.string "Una chismosa parlanchina como\n"
	.string "Esa cosa es perfecta.\p"
	.string "No lo necesito porque no me\n"
	.string "importan los demás.\p"
	.string "Está bien, esta vez sí voy\n"
	.string "gone. Smell ya!$"

CeruleanCity_Text_GruntIntro::
	.string "Hey! Stay out!\n"
	.string "¡No es tu patio!\p"
	.string "…¿Eh?\n"
	.string "¿Yo?\p"
	.string "¡Soy un inocente\ntranseúnte!"
	.string "¿No me crees?{PLAY_BGM}{MUS_RG_ENCOUNTER_ROCKET}$"

CeruleanCity_Text_GruntDefeat::
	.string "GRUNT: ¡Alto! ¡Me rindo!\n"
	.string "I'll leave quietly!$"

CeruleanCity_Text_OkayIllReturnStolenTM::
	.string "…Okay.\n"
	.string "Devolveré la MT que robé.$"

CeruleanCity_Text_RecoveredTM28FromGrunt::
	.string "{PLAYER} recuperó la MT28 de\n"
	.string "el RECLUTA del EQUIPO ROCKET.$"

CeruleanCity_Text_BetterGetMovingBye::
	.string "¡Mejor me doy prisa!\n"
	.string "¡Adiós!$"

CeruleanCity_Text_MakeRoomForThisCantRun::
	.string "¡Haz espacio para esto!\n"
	.string "¡No puedo correr hasta dártelo!$"

CeruleanCity_Text_TrainerLifeIsToughIsntIt::
	.string "You're a TRAINER, too?\p"
	.string "Collecting, battling…\n"
	.string "Es una vida dura, ¿verdad?$"

CeruleanCity_Text_YouCanCutDownSmallTrees::
	.string "¿Sabías que puedes TALAR\n"
	.string "small trees?\p"
	.string "Incluso ese árbol pequeño\n"
	.string "the shop can be CUT down.\p"
	.string "Creo que hay otra forma,\n"
	.string "su voz.$"

CeruleanCity_Text_IfSlowbroWasntThereCouldCutTree::
	.string "Si ese SLOWBRO no estuviera ahí,\n"
	.string "podrías usar CORTE en el árbol.\p"
	.string "Así podrías llegar a la\n"
	.string "other side.\p"
	.string "Creo que hay otra forma,\n"
	.string "su voz.$"

CeruleanCity_Text_PokemonEncyclopediaAmusing::
	.string "Estás haciendo una enciclopedia\n"
	.string "POKéMON? That sounds amusing.$"

CeruleanCity_Text_PeopleHereWereRobbed::
	.string "A la gente de aquí la robaron.\p"
	.string "Es obvio que el EQUIPO ROCKET\n"
	.string "atroz!\p"
	.string "Hasta nuestra POLICÍA ha\n"
	.string "¡problemas con el EQUIPO ROCKET!$"

CeruleanCity_Text_SlowbroUseSonicboom::
	.string "Okay! SLOWBRO!\n"
	.string "Use SONICBOOM!$"

CeruleanCity_Text_SlowbroPayAttention::
	.string "¡Vamos, SLOWBRO, presta atención!$"

CeruleanCity_Text_SlowbroPunch::
	.string "SLOWBRO, punch!$"

CeruleanCity_Text_NoYouBlewItAgain::
	.string "¡No!\n"
	.string "¡Lo arruinaste otra vez!$"

CeruleanCity_Text_SlowbroWithdraw::
	.string "SLOWBRO, WITHDRAW!$"

CeruleanCity_Text_HardToControlMonsObedience::
	.string "¡No! ¡Eso está mal!\n"
	.string "It's so hard to control POKéMON!\p"
	.string "Your POKéMON's obedience depends\n"
	.string "en tus habilidades como ENTRENADOR.$"

CeruleanCity_Text_SlowbroTookSnooze::
	.string "SLOWBRO se echó una siesta…$"

CeruleanCity_Text_SlowbroLoafingAround::
	.string "SLOWBRO está holgazaneando…$"

CeruleanCity_Text_SlowbroTurnedAway::
	.string "SLOWBRO turned away…$"

CeruleanCity_Text_SlowbroIgnoredOrders::
	.string "SLOWBRO ignored orders…$"

CeruleanCity_Text_WantBrightRedBicycle::
	.string "Quiero una bicicleta roja\p"
	.string "brillante. La guardaré en casa,\n"
	.string "ensuciarse.$"

CeruleanCity_Text_ThisIsCeruleanCave::
	.string "Esta es la CAVERNA AZUL.\p"
	.string "Viven POKéMON terriblemente\n"
	.string "fuertes allí.\p"
	.string "Se requiere un ENTRENADOR muy\n"
	.string "especial para entrar allí.\p"
	.string "Tendrías que ser lo bastante\n"
	.string "become the POKéMON LEAGUE\l"
	.string "LIGA POKéMON de KANTO primero.\p"
	.string "Y tendrías que haber logrado\n"
	.string "un gran hazaña.$"

CeruleanCity_Text_CitySign::
	.string "CIUDAD MALVA\n"
	.string "Un aura azul misteriosa rodea\l"
	.string "It$"

CeruleanCity_Text_TrainerTipsHeldItems::
	.string "CONSEJOS DE ENTRENADOR\p"
	.string "A POKéMON can be made to hold\n"
	.string "un objeto.\p"
	.string "Algunos objetos incluso pueden ser\n"
	.string "the holding POKéMON in battle.$"

CeruleanCity_Text_BikeShopSign::
	.string "¡Hierba y cuevas sin problema!\n"
	.string "TIENDA DE BICICLETAS$"

CeruleanCity_Text_GymSign::
	.string "CERULEAN CITY POKéMON GYM\n"
	.string "LÍDER: MISTY\l"
	.string "¡La sirena marimacho!$"

