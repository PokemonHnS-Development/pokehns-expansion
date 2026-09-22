CeruleanCity_Gym_Frlg_MapScripts::
	.byte 0

CeruleanCity_Gym_EventScript_Misty::
	famechecker FAMECHECKER_MISTY, FCPICKSTATE_COLORED, UpdatePickStateFromSpecialVar8005
	trainerbattle_single TRAINER_LEADER_MISTY, CeruleanCity_Gym_Text_MistyIntro, CeruleanCity_Gym_Text_MistyDefeat, CeruleanCity_Gym_EventScript_MistyDefeated, NO_MUSIC
	goto_if_unset FLAG_GOT_TM03_FROM_MISTY, CeruleanCity_Gym_EventScript_GiveTM03
	msgbox CeruleanCity_Gym_Text_ExplainTM03
	release
	end

CeruleanCity_Gym_EventScript_MistyDefeated::
	famechecker FAMECHECKER_MISTY, 1
	setflag FLAG_DEFEATED_MISTY
	setflag FLAG_BADGE02_GET
	setrespawn HEAL_LOCATION_CERULEAN_CITY
	set_gym_trainers_frlg 2
	goto CeruleanCity_Gym_EventScript_GiveTM03
	end

CeruleanCity_Gym_EventScript_GiveTM03::
	msgbox CeruleanCity_Gym_Text_ExplainCascadeBadge
	checkitemspace ITEM_TM03
	goto_if_eq VAR_RESULT, FALSE, CeruleanCity_Gym_EventScript_NoRoomForTM03
	giveitem_msg CeruleanCity_Gym_Text_ReceivedTM03FromMisty, ITEM_TM03
	setflag FLAG_GOT_TM03_FROM_MISTY
	msgbox CeruleanCity_Gym_Text_ExplainTM03
	release
	end

CeruleanCity_Gym_EventScript_NoRoomForTM03::
	msgbox CeruleanCity_Gym_Text_BetterMakeRoomForThis
	release
	end

CeruleanCity_Gym_EventScript_Diana::
	trainerbattle_single TRAINER_PICNICKER_DIANA, CeruleanCity_Gym_Text_DianaIntro, CeruleanCity_Gym_Text_DianaDefeat
	msgbox CeruleanCity_Gym_Text_DianaPostBattle, MSGBOX_AUTOCLOSE
	end

CeruleanCity_Gym_EventScript_Luis::
	trainerbattle_single TRAINER_SWIMMER_MALE_LUIS, CeruleanCity_Gym_Text_LuisIntro, CeruleanCity_Gym_Text_LuisDefeat
	famechecker FAMECHECKER_MISTY, 2
	msgbox CeruleanCity_Gym_Text_LuisPostBattle, MSGBOX_AUTOCLOSE
	end

CeruleanCity_Gym_EventScript_GymGuy::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_MISTY, CeruleanCity_Gym_EventScript_GymGuyPostVictory
	msgbox CeruleanCity_Gym_Text_GymGuyAdvice
	release
	end

CeruleanCity_Gym_EventScript_GymGuyPostVictory::
	msgbox CeruleanCity_Gym_Text_WeMakePrettyGoodTeam
	release
	end

CeruleanCity_Gym_EventScript_GymStatue::
	lockall
	goto_if_set FLAG_BADGE02_GET, CeruleanCity_Gym_EventScript_GymStatuePostVictory
	msgbox CeruleanCity_Gym_Text_GymStatue
	releaseall
	end

CeruleanCity_Gym_EventScript_GymStatuePostVictory::
	msgbox CeruleanCity_Gym_Text_GymStatuePlayerWon
	releaseall
	end

CeruleanCity_Gym_Text_MistyIntro::
	.string "¡Hola, cara nueva!\p"
	.string "Solo los ENTRENADORES que\n"
	.string "policy about POKéMON can turn pro.\p"
	.string "¿Cuál es tu enfoque cuando\n"
	.string "catch and train POKéMON?\p"
	.string "Mi política es una ofensiva\n"
	.string "with WATER-type POKéMON!{PLAY_BGM}{MUS_RG_ENCOUNTER_GYM_LEADER}$"

CeruleanCity_Gym_Text_ExplainTM03::
	.string "TM03 teaches WATER PULSE.\p"
	.string "Use it on an aquatic POKéMON!$"

CeruleanCity_Gym_Text_ExplainCascadeBadge::
	.string "La MEDALLA CASCADA hace que\n"
	.string "POKéMON up to Lv. 30 obey.\p"
	.string "Eso incluye hasta a forasteros que\n"
	.string "llegaron en intercambios.\p"
	.string "Hay más. Ahora puedes usar CORTE\n"
	.string "anytime, even out of battle.\p"
	.string "You can CUT down small trees to\n"
	.string "open new pathways.\p"
	.string "También puedes tener mi MT favorita.$"

CeruleanCity_Gym_Text_ReceivedTM03FromMisty::
	.string "{PLAYER} received TM03\n"
	.string "de MISTY.$"

CeruleanCity_Gym_Text_BetterMakeRoomForThis::
	.string "¡Más te vale hacer espacio!$"

CeruleanCity_Gym_Text_MistyDefeat::
	.string "¡Guau!\n"
	.string "¡Eres demasiado!\p"
	.string "All right!\p"
	.string "Puedes tener la MEDALLA CASCADA\n"
	.string "para mostrar que me venciste.$"

CeruleanCity_Gym_Text_DianaIntro::
	.string "¿Qué? ¿Tú?\n"
	.string "¡Soy más que suficiente para ti!\p"
	.string "MISTY no tendrá que molestarse.$"

CeruleanCity_Gym_Text_DianaDefeat::
	.string "¡Me abrumaste!$"

CeruleanCity_Gym_Text_DianaPostBattle::
	.string "Debes enfrentar a otros\n"
	.string "qué tan bueno eres de verdad.$"

CeruleanCity_Gym_Text_LuisIntro::
	.string "¡Splash!\p"
	.string "I'm first up!\n"
	.string "¡Hagámoslo!$"

CeruleanCity_Gym_Text_LuisDefeat::
	.string "¡Eso no puede ser!$"

CeruleanCity_Gym_Text_LuisPostBattle::
	.string "MISTY es una ENTRENADORA que va\n"
	.string "dejará de mejorar.\p"
	.string "¡Ella no perderá contra ti!$"

CeruleanCity_Gym_Text_GymGuyAdvice::
	.string "Yo!\n"
	.string "¡Un futuro campeón!\p"
	.string "¡Te daré un consejo!\p"
	.string "La LÍDER MISTY es una pro que\n"
	.string "uses WATER-type POKéMON.\p"
	.string "Puedes drenar toda su agua con\n"
	.string "GRASS-type POKéMON.\p"
	.string "O puedes usar tipo ELÉCTRICO\n"
	.string "POKéMON and zap them!$"

CeruleanCity_Gym_Text_WeMakePrettyGoodTeam::
	.string "¡Venciste a MISTY!\n"
	.string "¿Ves? ¿Qué te dije?\p"
	.string "Tú y yo, chico, hacemos buena\n"
	.string "darn-good team!$"

CeruleanCity_Gym_Text_GymStatue::
	.string "GIMNASIO POKéMON AZULONA\n"
	.string "LÍDER: MISTY\p"
	.string "ENTRENADORES GANADORES:\n"
	.string "{RIVAL}$"

CeruleanCity_Gym_Text_GymStatuePlayerWon::
	.string "GIMNASIO POKéMON AZULONA\n"
	.string "LÍDER: MISTY\p"
	.string "ENTRENADORES GANADORES:\n"
	.string "{RIVAL}, {PLAYER}$"

