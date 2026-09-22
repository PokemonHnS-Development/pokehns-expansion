CaveOfOrigin_B1F_MapScripts::
	.byte 0

CaveOfOrigin_B1F_EventScript_Wallace::
	lock
	faceplayer
	msgbox CaveOfOrigin_B1F_Text_WallaceStory, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CAVE_OF_ORIGIN_WALLACE, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	delay 60
	playse SE_PIN
	applymovement LOCALID_CAVE_OF_ORIGIN_WALLACE, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_CAVE_OF_ORIGIN_WALLACE, Common_Movement_Delay48
	waitmovement 0
	delay 30
	applymovement LOCALID_CAVE_OF_ORIGIN_WALLACE, Common_Movement_FacePlayer
	waitmovement 0
	message CaveOfOrigin_B1F_Text_WhereIsRayquaza
	waitmessage
	goto CaveOfOrigin_B1F_EventScript_WheresRayquaza

CaveOfOrigin_B1F_EventScript_WheresRayquaza::
	multichoice 0, 0, MULTI_WHERES_RAYQUAZA, FALSE
	switch VAR_RESULT
	case 0, CaveOfOrigin_B1F_EventScript_AtCaveOfOrigin
	case 1, CaveOfOrigin_B1F_EventScript_AtMtPyre
	case 2, CaveOfOrigin_B1F_EventScript_AtSkyPillar
	case 3, CaveOfOrigin_B1F_EventScript_DontRemember
	goto CaveOfOrigin_B1F_EventScript_DontRemember
	end

CaveOfOrigin_B1F_EventScript_AtCaveOfOrigin::
	message CaveOfOrigin_B1F_Text_ButWereInCaveOfOrigin
	waitmessage
	goto CaveOfOrigin_B1F_EventScript_WheresRayquaza

CaveOfOrigin_B1F_EventScript_AtMtPyre::
	message CaveOfOrigin_B1F_Text_OldLadyDidntMentionThat
	waitmessage
	goto CaveOfOrigin_B1F_EventScript_WheresRayquaza

CaveOfOrigin_B1F_EventScript_DontRemember::
	message CaveOfOrigin_B1F_Text_CantYouRememberSomehow
	waitmessage
	goto CaveOfOrigin_B1F_EventScript_WheresRayquaza

CaveOfOrigin_B1F_EventScript_AtSkyPillar::
	msgbox CaveOfOrigin_B1F_Text_WellHeadToSkyPillar, MSGBOX_DEFAULT
	closemessage
	playse SE_EXIT
	fadescreenspeed FADE_TO_BLACK, 4
	setflag FLAG_WALLACE_GOES_TO_SKY_PILLAR
	setvar VAR_SOOTOPOLIS_CITY_STATE, 3
	removeobject LOCALID_CAVE_OF_ORIGIN_WALLACE
	clearflag FLAG_HIDE_SKY_PILLAR_WALLACE
	fadescreen FADE_FROM_BLACK
	release
	end

CaveOfOrigin_B1F_Text_WallaceStory:
	.string "Ah, ¿así que tú eres {PLAYER}{KUN}?\n"
	.string "He oído hablar de tus hazañas.\p"
	.string "Mi nombre es WALLACE.\p"
	.string "Alguna vez fui el LÍDER de\n"
	.string "SOTOPOLIS, pero surgió algo.\p"
	.string "Así que le confié al mentor JUAN\n"
	.string "la gestión del GIMNASIO.\p"
	.string "... ... ... ... ... ...\n"
	.string "... ... ... ... ... ...\p"
	.string "GROUDON y KYOGRE, los dos POKéMON\n"
	.string "que causan caos aquí, son\l"
	.string "considerados POKéMON ancestrales.\p"
	.string "Pero no solo existen dos POKéMON\n"
	.string "ancestrales.\p"
	.string "Hay uno más en algún lugar.\p"
	.string "En algún lugar, hay un super-\n"
	.string "antiguo POKéMON llamado RAYQUAZA.\p"
	.string "Dicen que fue RAYQUAZA quien\n"
	.string "calmó a los dos combatientes en\l"
	.string "el pasado remoto.\p"
	.string "Pero ni yo tengo idea de\n"
	.string "dónde se encuentra RAYQUAZA...$"

CaveOfOrigin_B1F_Text_WhereIsRayquaza:
	.string "WALLACE: {PLAYER}{KUN}, ¿por casualidad?\n"
	.string "sabes dónde está RAYQUAZA ahora?\p"
	.string "Si lo sabes, por favor dímelo.$"

CaveOfOrigin_B1F_Text_ButWereInCaveOfOrigin:
	.string "WALLACE: ¿La CUEVA ORIGEN?\p"
	.string "¡Pero si está justo aquí!\n"
	.string "¡Necesito que te esfuerces más!\p"
	.string "Por favor, piensa en dónde\n"
	.string "podría estar RAYQUAZA ahora mismo.$"

CaveOfOrigin_B1F_Text_OldLadyDidntMentionThat:
	.string "WALLACE: ¿En el MONTE CENIZA?\p"
	.string "Pero cuando vi a la anciana allí\n"
	.string "hace poco, no mencionó nada.\p"
	.string "Dudo mucho que la anciana\n"
	.string "intente ocultarme algo...\p"
	.string "{PLAYER}{KUN}, ¿podrías pensar en esto\n"
	.string "con más cuidado por mí?$"

CaveOfOrigin_B1F_Text_CantYouRememberSomehow:
	.string "WALLACE: ¿Eh? ¿No te acuerdas?\n"
	.string "Hmm... Eso es un problema...\p"
	.string "¿No puedes recordarlo de algún modo?$"

CaveOfOrigin_B1F_Text_WellHeadToSkyPillar:
	.string "WALLACE: ¿El PILAR CELESTE?\p"
	.string "¡Eso es!\n"
	.string "¡Debe ser el PILAR CELESTE!\p"
	.string "{PLAYER}{KUN}, ¡no hay tiempo que perder!\n"
	.string "¡Iremos al PILAR CELESTE ahora mismo!$"

