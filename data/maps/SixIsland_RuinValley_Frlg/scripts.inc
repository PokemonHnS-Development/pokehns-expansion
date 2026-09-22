SixIsland_RuinValley_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, SixIsland_RuinValley_OnLoad
	.byte 0

SixIsland_RuinValley_OnLoad::
	call_if_set FLAG_USED_CUT_ON_RUIN_VALLEY_BRAILLE, SixIsland_RuinValley_EventScript_OpenDottedHoleDoor
	end

SixIsland_RuinValley_EventScript_OpenDottedHoleDoor::
	setmetatile 24, 24, METATILE_SeviiIslands67_DottedHoleDoor_Open, 0
	return

SixIsland_RuinValley_EventScript_Scientist::
	lock
	msgbox SixIsland_RuinValley_Text_CantFigureOutHowToGetInside
	applymovement LOCALID_RUIN_VALLEY_SCIENTIST, Common_Movement_FacePlayer
	waitmovement 0
	msgbox SixIsland_RuinValley_Text_IFoundThisPlace
	applymovement LOCALID_RUIN_VALLEY_SCIENTIST, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

SixIsland_RuinValley_EventScript_DottedHoleDoor::
	lockall
	goto_if_set FLAG_USED_CUT_ON_RUIN_VALLEY_BRAILLE, SixIsland_RuinValley_EventScript_DottedHoleDoorOpen
	msgbox SixIsland_RuinValley_Text_CheckDoorMoreThoroughly, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, SixIsland_RuinValley_EventScript_IgnoreDottedHoleDoor
	msgbox SixIsland_RuinValley_Text_SeveralDotsOnTheDoor
	braillemsgbox Braille_Text_Cut
	releaseall
	end

SixIsland_RuinValley_EventScript_DottedHoleDoorOpen::
	msgbox SixIsland_RuinValley_Text_DoorIsOpen
	releaseall
	end

SixIsland_RuinValley_EventScript_IgnoreDottedHoleDoor::
	msgbox SixIsland_RuinValley_Text_LeftDoorAlone
	releaseall
	end

SixIsland_RuinValley_Text_CantFigureOutHowToGetInside::
	.string "No logro entender cómo\n"
	.string "se entra ahí dentro.$"

SixIsland_RuinValley_Text_IFoundThisPlace::
	.string "Les diré, encontré esto\n"
	.string "place.\p"
	.string "No mires con tanta envidia, ¿eh?$"

SixIsland_RuinValley_Text_CheckDoorMoreThoroughly::
	.string "La puerta no se mueve.\n"
	.string "¿Revisarla más a fondo?$"

SixIsland_RuinValley_Text_LeftDoorAlone::
	.string "{PLAYER} dejó la puerta en paz.$"

SixIsland_RuinValley_Text_SeveralDotsOnTheDoor::
	.string "Al mirar de cerca, hay\n"
	.string "varios puntos en la puerta…$"

SixIsland_RuinValley_Text_DoorIsOpen::
	.string "La puerta está abierta.$"

SixIsland_RuinValley_Text_StanlyIntro::
	.string "Parece que hay muchos secretos\n"
	.string "aún sin resolver en este mundo.$"

SixIsland_RuinValley_Text_StanlyDefeat::
	.string "Hmm…$"

SixIsland_RuinValley_Text_StanlyPostBattle::
	.string "Te sugiero que tú también,\n"
	.string "pienses una vez al día en los\l"
	.string "mysteries of our world once a day.$"

SixIsland_RuinValley_Text_FosterIntro::
	.string "I'm curious, what compelled you to\n"
	.string "¿vienes?$"

SixIsland_RuinValley_Text_FosterDefeat::
	.string "Ha pasado tanto desde que peleé,\n"
	.string "mi instinto está oxidado.$"

SixIsland_RuinValley_Text_FosterPostBattle::
	.string "Hay varias ruinas en la\n"
	.string "SEVII ISLANDS.\p"
	.string "La mayoría de ellas datan\n"
	.string "un largo camino.$"

SixIsland_RuinValley_Text_LarryIntro::
	.string "Dicen que hay piedras\n"
	.string "misteriosas en esta isla.\p"
	.string "Sospecho que tiene algo que ver\n"
	.string "con las ruinas de aquí.$"

SixIsland_RuinValley_Text_LarryDefeat::
	.string "Oh, interesting.$"

SixIsland_RuinValley_Text_LarryPostBattle::
	.string "Aquellas ruinas de allá…\p"
	.string "No he tenido suerte en encontrar\n"
	.string "cómo puedo entrar.$"

SixIsland_RuinValley_Text_DarylIntro::
	.string "¡Una batalla contigo, tan arriba!$"

SixIsland_RuinValley_Text_DarylDefeat::
	.string "¡Ay, qué dolor perder así\n"
	.string "de fácil ante ti!$"

SixIsland_RuinValley_Text_DarylPostBattle::
	.string "¡Siente la alegría de escalar!$"

SixIsland_RuinValley_Text_HectorIntro::
	.string "Conozco muy bien las tierras\n"
	.string "de por aquí.$"

SixIsland_RuinValley_Text_HectorDefeat::
	.string "No hace falta que presiones.\n"
	.string "Con gusto te lo diré.$"

SixIsland_RuinValley_Text_HectorPostBattle::
	.string "La puerta de las ruinas…\n"
	.string "Tiene extraños grabados\l"
	.string "en el exterior.\p"
	.string "No sé qué significan,\n"
	.string "su voz.$"
