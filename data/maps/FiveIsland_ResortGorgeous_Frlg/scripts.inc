FiveIsland_ResortGorgeous_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, FiveIsland_ResortGorgeous_OnWarp
	map_script MAP_SCRIPT_ON_FRAME_TABLE, FiveIsland_ResortGorgeous_OnFrame
	.byte 0

FiveIsland_ResortGorgeous_OnWarp::
	map_script_2 VAR_MAP_SCENE_FIVE_ISLAND_RESORT_GORGEOUS, 1, FiveIsland_ResortGorgeous_EventScript_TurnPlayerNorth
	.2byte 0

FiveIsland_ResortGorgeous_EventScript_TurnPlayerNorth::
	turnobject LOCALID_PLAYER, DIR_NORTH
	end

FiveIsland_ResortGorgeous_OnFrame::
	map_script_2 VAR_MAP_SCENE_FIVE_ISLAND_RESORT_GORGEOUS, 1, FiveIsland_ResortGorgeous_EventScript_SelphyReturnHomeScene
	.2byte 0

FiveIsland_ResortGorgeous_EventScript_SelphyReturnHomeScene::
	lockall
	textcolor NPC_TEXT_COLOR_FEMALE
	msgbox FiveIsland_ResortGorgeous_Text_SelphyThanksYouMayGoNow
	closemessage
	applymovement LOCALID_RESORT_GORGEOUS_SELPHY, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	opendoor 39, 8
	waitdooranim
	applymovement LOCALID_RESORT_GORGEOUS_SELPHY, FiveIsland_ResortGorgeous_Movement_SelphyEnterHome
	waitmovement 0
	closedoor 39, 8
	waitdooranim
	removeobject LOCALID_RESORT_GORGEOUS_SELPHY
	clearflag FLAG_HIDE_RESORT_GORGEOUS_INSIDE_SELPHY
	setvar VAR_MAP_SCENE_FIVE_ISLAND_RESORT_GORGEOUS, 2
	releaseall
	end

FiveIsland_ResortGorgeous_Movement_SelphyEnterHome::
	walk_up
	set_invisible
	step_end

FiveIsland_ResortGorgeous_EventScript_SelphysHouseSign::
	msgbox FiveIsland_ResortGorgeous_Text_SelphysHouse, MSGBOX_SIGN
	end

FiveIsland_ResortGorgeous_Text_DaisyIntro::
	.string "Con estas manos, crearé\n"
	.string "¡mi victoria!$"

FiveIsland_ResortGorgeous_Text_DaisyDefeat::
	.string "La vergüenza de esto…\n"
	.string "I'm red-faced…$"

FiveIsland_ResortGorgeous_Text_DaisyPostBattle::
	.string "Ay no, mis tubos de pintura\n"
	.string "scattered everywhere!$"

FiveIsland_ResortGorgeous_Text_CelinaIntro::
	.string "¡Disculpa!\n"
	.string "Estoy intentando pintar.\l"
	.string "¡Por favor, no me molestes!$"

FiveIsland_ResortGorgeous_Text_CelinaDefeat::
	.string "Esta derrota…\n"
	.string "I feel like I'm whiting out…$"

FiveIsland_ResortGorgeous_Text_CelinaPostBattle::
	.string "GILLIAN?\n"
	.string "Inclina un poco la cabeza…\l"
	.string "¡Ahí! ¡Ese look que quiero!$"

FiveIsland_ResortGorgeous_Text_RaynaIntro::
	.string "Hmm…\n"
	.string "El ángulo, aún no está…$"

FiveIsland_ResortGorgeous_Text_RaynaDefeat::
	.string "Oh…\n"
	.string "Mis sentimientos son tristes…$"

FiveIsland_ResortGorgeous_Text_RaynaPostBattle::
	.string "El cielo y el mar…\n"
	.string "Son tan cambiantes.\p"
	.string "Sus expresiones cambiantes hacen\n"
	.string "difícil atraparlos.$"

FiveIsland_ResortGorgeous_Text_JackiIntro::
	.string "Estoy visitando el retiro de un\n"
	.string "amigo, si quieres saberlo.$"

FiveIsland_ResortGorgeous_Text_JackiDefeat::
	.string "Oh, vaya, qué fuerte.$"

FiveIsland_ResortGorgeous_Text_JackiPostBattle::
	.string "Me resulta agradable combatir con\n"
	.string "calma en la brisa del mar.$"

FiveIsland_ResortGorgeous_Text_GillianIntro::
	.string "Estoy pensando en poner una alberca\n"
	.string "made specially for POKéMON.$"

FiveIsland_ResortGorgeous_Text_GillianDefeat::
	.string "¡Oh, por Dios mío!$"

FiveIsland_ResortGorgeous_Text_GillianPostBattle::
	.string "Una alberca estaría bien, pero\n"
	.string "una sala de sol puede ser sublime.$"

FiveIsland_ResortGorgeous_Text_DestinIntro::
	.string "Soy un buen corredor.\n"
	.string "I'm really fast!$"

FiveIsland_ResortGorgeous_Text_DestinDefeat::
	.string "¡Ups!\n"
	.string "I rushed things!$"

FiveIsland_ResortGorgeous_Text_DestinPostBattle::
	.string "Cuando corro con el viento, siento\n"
	.string "que podría volar!$"

FiveIsland_ResortGorgeous_Text_TobyIntro::
	.string "Esta vida marina del resort me\n"
	.string "queda muy bien.$"

FiveIsland_ResortGorgeous_Text_TobyDefeat::
	.string "¡Qué sorpresa!\n"
	.string "Debes estar bromeando.$"

FiveIsland_ResortGorgeous_Text_TobyPostBattle::
	.string "Ponerse tan serio por esto…\n"
	.string "How nonsensical.$"

FiveIsland_ResortGorgeous_Text_SelphyThanksYouMayGoNow::
	.string "SELPHY: Gracias.\p"
	.string "Puedes irte ya.$"

FiveIsland_ResortGorgeous_Text_SelphysHouse::
	.string "SELPHY'S HOUSE$"

