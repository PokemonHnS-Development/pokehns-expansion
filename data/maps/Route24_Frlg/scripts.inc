Route24_Frlg_MapScripts::
	.byte 0

Route24_EventScript_Rocket::
	lock
	faceplayer
	goto_if_eq VAR_MAP_SCENE_ROUTE24, 1, Route24_EventScript_RocketPostBattle
	msgbox Route24_Text_JustEarnedFabulousPrize
	checkitemspace ITEM_NUGGET
	goto_if_eq VAR_RESULT, FALSE, Route24_EventScript_NoRoomForNugget
	call Route24_EventScript_BattleRocket
	release
	end

Route24_EventScript_NoRoomForNugget::
	msgbox Route24_Text_YouDontHaveAnyRoom
	release
	end

Route24_EventScript_RocketPostBattle::
	msgbox Route24_Text_YoudBecomeTopRocketLeader
	release
	end

Route24_EventScript_RocketTriggerLeft::
	lockall
	setvar VAR_TEMP_1, 0
	goto Route24_EventScript_RocketTrigger
	end

Route24_EventScript_RocketTriggerRight::
	lockall
	setvar VAR_TEMP_1, 1
	goto Route24_EventScript_RocketTrigger
	end

Route24_EventScript_RocketTrigger::
	textcolor NPC_TEXT_COLOR_MALE
	call_if_eq VAR_TEMP_1, 0, Route24_EventScript_RocketApproachPlayer
	call_if_eq VAR_TEMP_1, 1, Route24_EventScript_RocketMotionToPlayer
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox Route24_Text_JustEarnedFabulousPrize
	checkitemspace ITEM_NUGGET
	goto_if_eq VAR_RESULT, FALSE, Route24_EventScript_NoRoomForNuggetTrigger
	call Route24_EventScript_BattleRocket
	releaseall
	end

Route24_EventScript_BattleRocket::
	giveitem_msg Route24_Text_ReceivedNuggetFromMysteryTrainer, ITEM_NUGGET
	message Route24_Text_JoinTeamRocket
	waitmessage
	playbgm MUS_RG_ENCOUNTER_ROCKET, 0
	waitbuttonpress
	setvar VAR_LAST_TALKED, LOCALID_ROUTE24_ROCKET
	trainerbattle_no_intro TRAINER_TEAM_ROCKET_GRUNT_6, Route24_Text_RocketDefeat
	msgbox Route24_Text_YoudBecomeTopRocketLeader
	setvar VAR_MAP_SCENE_ROUTE24, 1
	return

Route24_EventScript_RocketApproachPlayer::
	applymovement LOCALID_ROUTE24_ROCKET, Route24_Movement_RocketApproachPlayer
	waitmovement 0
	return

Route24_EventScript_RocketMotionToPlayer::
	applymovement LOCALID_ROUTE24_ROCKET, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	return

Route24_EventScript_NoRoomForNuggetTrigger::
	msgbox Route24_Text_YouDontHaveAnyRoom
	closemessage
	applymovement LOCALID_PLAYER, Route24_Movement_WalkDown
	waitmovement 0
	call_if_eq VAR_TEMP_1, 0, Route24_EventScript_RocketWalkBackToPos
	release
	end

Route24_EventScript_RocketWalkBackToPos::
	applymovement LOCALID_ROUTE24_ROCKET, Route24_Movement_RocketWalkBackToPos
	waitmovement 0
	return

Route24_Movement_RocketApproachPlayer::
	walk_left
	step_end

Route24_Movement_RocketWalkBackToPos::
	walk_right
	walk_in_place_faster_left
	step_end

Route24_Movement_WalkDown::
	walk_down
	step_end

Route24_Text_JustEarnedFabulousPrize::
	.string "¡Felicitaciones! Venciste a\n"
	.string "five contest TRAINERS!\p"
	.string "¡Acabas de ganar un premio fabuloso!$"

Route24_Text_ReceivedNuggetFromMysteryTrainer::
	.string "{PLAYER} recibió una PEPITA\n"
	.string "¡del ENTRENADOR misterioso!$"

Route24_Text_YouDontHaveAnyRoom::
	.string "¡No tienes espacio!$"

Route24_Text_JoinTeamRocket::
	.string "Por cierto, ¿te gustaría\n"
	.string "join TEAM ROCKET?\p"
	.string "Somos un grupo de profesionales\n"
	.string "criminals specializing in POKéMON!\p"
	.string "¿Quieres unirte?\p"
	.string "¿Estás seguro?\p"
	.string "¡Vamos, únete a nosotros!\p"
	.string "¡Te digo que te unas!\p"
	.string "…Vale, necesitas convencerte.\p"
	.string "Te haré una oferta que no\n"
	.string "refuse!$"

Route24_Text_RocketDefeat::
	.string "¡Arrgh!\n"
	.string "¡Eres bueno!$"

Route24_Text_YoudBecomeTopRocketLeader::
	.string "Con tu talento, te volverías\n"
	.string "un gran líder del EQUIPO ROCKET.\p"
	.string "¡Vamos, piensa en la oportunidad!\n"
	.string "No desperdicies esta ocasión.$"

Route24_Text_ShaneIntro::
	.string "¡Vi tu hazaña desde el pasto!$"

Route24_Text_ShaneDefeat::
	.string "¡Pensé que no!$"

Route24_Text_ShanePostBattle::
	.string "Me escondí porque la gente del\n"
	.string "puente me asustó.$"

Route24_Text_EthanIntro::
	.string "¡Bien! ¡Soy el número 5!\n"
	.string "¡Te voy a aplastar!$"

Route24_Text_EthanDefeat::
	.string "¡Vaya!\n"
	.string "Too much!$"

Route24_Text_EthanPostBattle::
	.string "I did my best. I have no regrets!$"

Route24_Text_ReliIntro::
	.string "¡Soy el número 4!\n"
	.string "¿Te estás cansando?$"

Route24_Text_ReliDefeat::
	.string "¡Yo también perdí!$"

Route24_Text_ReliPostBattle::
	.string "I did my best, so I've no regrets!$"

Route24_Text_TimmyIntro::
	.string "¡Aquí llega el No. 3!\n"
	.string "¡No será fácil!$"

Route24_Text_TimmyDefeat::
	.string "Ow!\n"
	.string "Stomped flat!$"

Route24_Text_TimmyPostBattle::
	.string "I did my best. I have no regrets!$"

Route24_Text_AliIntro::
	.string "I'm second!\n"
	.string "¡Ahora esto va en serio!$"

Route24_Text_AliDefeat::
	.string "¿Cómo pude perder?$"

Route24_Text_AliPostBattle::
	.string "I did my best. I have no regrets!$"

Route24_Text_CaleIntro::
	.string "¡La gente llama a esto el PUENTE\n"
	.string "PÉPITA!\p"
	.string "Vencenos a cinco ENTRENADORES\n"
	.string "¡un premio fabuloso!\p"
	.string "¿Crees que puedes lograrlo?$"

Route24_Text_CaleDefeat::
	.string "Whoo!\n"
	.string "Good stuff!$"

Route24_Text_CalePostBattle::
	.string "I did my best. I have no regrets!$"
