DragonsDen_Cavern_hns_MapScripts::
	@map_script MAP_SCRIPT_ON_FRAME_TABLE, DragonsDen_Cavern_OnFrame
	.byte 0

DragonsDen_Cavern_OnFrame::
	map_script_2 VAR_BLACKTHORN_CITY_STATE, 3, DragonsDen_Cavern_EventScript_Clair
	.2byte 0

DragonsDen_EventScript_ClairRematch::
    lock
    faceplayer
    msgbox DragonsDen_Text_Clair, MSGBOX_DEFAULT
    closemessage
    fadescreenswapbuffers FADE_TO_BLACK
    setflag FLAG_HIDE_DEN_CLAIR
    removeobject LOCALID_DEN_CLAIR
    fadescreenswapbuffers FADE_FROM_BLACK
    clearflag FLAG_HIDE_DOJO_CLAIR
    release
    end

DragonsDen_Text_Clair:
    .string "{PLAYER}… Así que estás aquí.\p"
	.string "Si crees que puedes seguirme\n"
	.string "el ritmo, ven al DOJO DE LUCHA\l"
	.string "en CIUDAD AZAFRÁN.$"

DragonsDen_Cavern_Trigger_ClairLeft::
	lock
	setflag FLAG_TEMP_HIDE_FOLLOWER 
	playse SE_PIN
	playbgm MUS_HG_CLAIR, FALSE
	applymovement2 LOCALID_DRAGONSDEN2_CLAIR, Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_DRAGONSDEN2_CLAIR
	call DragonsDen_Cavern_EventScript_Clair
	applymovement OBJ_EVENT_ID_PLAYER, DragonsDen_Cavern_Movement_ClairLeaveLeftPLAYER
	waitmovement 0
	applymovement2 LOCALID_DRAGONSDEN2_CLAIR, DragonsDen_Cavern_Movement_ClairLeaveLeft
	waitmovement 0
	setflag FLAG_HIDE_DRAGONS_DEN_CAVERN_CLAIR
	removeobject LOCALID_DRAGONSDEN2_CLAIR
	playse SE_EXIT
	fadedefaultbgm
	setvar VAR_BLACKTHORN_CITY_STATE, 4
	setrespawn HEAL_LOCATION_BLACKTHORN_CITY_HNS
	releaseall
	end

DragonsDen_Cavern_Trigger_ClairMid::
	lock 
	playse SE_PIN
	playbgm MUS_HG_CLAIR, FALSE
	applymovement2 LOCALID_DRAGONSDEN2_CLAIR, Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_DRAGONSDEN2_CLAIR
	applymovement2 LOCALID_DRAGONSDEN2_CLAIR, Common_Movement_WalkRight1
	call DragonsDen_Cavern_EventScript_Clair
	applymovement2 LOCALID_DRAGONSDEN2_CLAIR, DragonsDen_Cavern_Movement_ClairLeaveMid
	waitmovement 0
	setflag FLAG_HIDE_DRAGONS_DEN_CAVERN_CLAIR
	removeobject LOCALID_DRAGONSDEN2_CLAIR
	playse SE_EXIT
	fadedefaultbgm
	setvar VAR_BLACKTHORN_CITY_STATE, 4
	release
	end

DragonsDen_Cavern_Trigger_ClairRight::
	lock 
	playse SE_PIN
	playbgm MUS_HG_CLAIR, FALSE
	applymovement2 LOCALID_DRAGONSDEN2_CLAIR, Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_DRAGONSDEN2_CLAIR
	applymovement2 LOCALID_DRAGONSDEN2_CLAIR, Common_Movement_WalkRight1
	waitmovement 0
	applymovement2 LOCALID_DRAGONSDEN2_CLAIR, Common_Movement_WalkRight1
	call DragonsDen_Cavern_EventScript_Clair
	applymovement2 LOCALID_DRAGONSDEN2_CLAIR, DragonsDen_Cavern_Movement_ClairLeaveRight
	waitmovement 0
	setflag FLAG_HIDE_DRAGONS_DEN_CAVERN_CLAIR
	removeobject LOCALID_DRAGONSDEN2_CLAIR
	playse SE_EXIT
	fadedefaultbgm
	setvar VAR_BLACKTHORN_CITY_STATE, 4
	release
	end

DragonsDen_Cavern_EventScript_Clair::
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	msgbox DragonsDen_Cavern_Text_Clair_GiveTM, MSGBOX_DEFAULT
	giveitem ITEM_TM_DRAGON_PULSE
	msgbox DragonsDen_Cavern_Text_Clair_ExplainTM, MSGBOX_DEFAULT
	closemessage
	delay 30
	msgbox DragonsDen_Cavern_Text_ClairWhatsTheMatter, MSGBOX_DEFAULT
	closemessage
	delay 10
	clearflag FLAG_GOT_DRATINI
	return

DragonsDen_Cavern_Movement_ClairLeaveLeftPLAYER:
	walk_fast_down
	face_up
	step_end

DragonsDen_Cavern_Movement_ClairLeaveLeft:
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

DragonsDen_Cavern_Movement_ClairLeaveMid:
	walk_up
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

DragonsDen_Cavern_Movement_ClairLeaveRight:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

DragonsDen_Cavern_Text_Clair_GiveTM:
    .string "CLAIR: ¡ESPERA!\p"
	.string "Siento mucho lo ocurrido.\n"
    .string "Toma esto como mi disculpa.$"

DragonsDen_Cavern_Text_Clair_ExplainTM:
    .string "PULSO DRAGÓN es una especie de er...\n"
	.string "¡olvídalo!\p"
	.string "Es una energía enorme de algún tipo.\p"
	.string "Si no lo quieres, no hace falta\n"
	.string "que lo aceptes.$"

DragonsDen_Cavern_Text_ClairWhatsTheMatter:
    .string "¿Qué pasa? ¿No vas a ir a la\n"
    .string "LIGA POKéMON?\l"
    .string "con los POKéMON?\p"
    .string "Cuando seas CAMPEÓN, podrás\n"
    .string "retar a cualquier LÍDER de\l"
    .string "GIMNASIO que quieras.\p"
    .string "Ve a la LIGA POKéMON.\p"
    .string "¿Sabes cómo llegar?\p"
    .string "Ve a PUEBLO PRIMAVERA.\p"
    .string "Usa SURF al este hacia la\p"
    .string "LIGA POKéMON. Es una ruta dura.\p"
    .string "¡Ni se te ocurra perder en la\n"
    .string "LIGA POKéMON!\p"
    .string "Si lo haces, me sentiré peor\n"
    .string "por haber perdido contra ti!\p"
    .string "¡Da todo lo que tengas!$"

DragonsDen_Cavern_EventScript_Darin::
	trainerbattle_single TRAINER_DARIN_HNS, DragonsDen_Cavern_Text_CooltrainermDarinSeen, DragonsDen_Cavern_Text_CooltrainermDarinBeaten
	msgbox DragonsDen_Cavern_Text_CooltrainermDarinAfter, MSGBOX_AUTOCLOSE
	end

DragonsDen_Cavern_EventScript_Cara::
	trainerbattle_single TRAINER_CARA_HNS, DragonsDen_Cavern_Text_CooltrainerfCaraSeen, DragonsDen_Cavern_Text_CooltrainerfCaraBeaten
	msgbox DragonsDen_Cavern_Text_CooltrainerfCaraAfter, MSGBOX_AUTOCLOSE
	end

DragonsDen_Cavern_EventScript_TwinLea::
	trainerbattle_double TRAINER_LEA_AND_PIA_HNS, DragonsDen_Cavern_Text_TwinsLeaandPia1Seen, DragonsDen_Cavern_Text_TwinsLeaandPia1Beaten, Route104_Text_GinaNotEnoughMons
	special GetPlayerBigGuyGirlString
	msgbox DragonsDen_Cavern_Text_TwinsLeaandPia1After, MSGBOX_DEFAULT
	release
	end
	
DragonsDen_Cavern_EventScript_TwinPia::
	trainerbattle_double TRAINER_LEA_AND_PIA_HNS, DragonsDen_Cavern_Text_TwinsLeaandPia2Seen, DragonsDen_Cavern_Text_TwinsLeaandPia2Beaten, Route104_Text_GinaNotEnoughMons
	special GetPlayerBigGuyGirlString
	msgbox DragonsDen_Cavern_Text_TwinsLeaandPia2After, MSGBOX_DEFAULT
	release
	end

DragonsDen_Cavern_EventScript_Item_Dragon_Fang::
	finditem ITEM_DRAGON_FANG
	end
DragonsDen_Cavern_EventScript_Item_Max_Potion::
	finditem ITEM_MAX_POTION
	end
DragonsDen_Cavern_EventScript_Item_PP_Max::
	finditem ITEM_PP_MAX
	end



DragonsDen_Cavern_Text_DragonShrineSign:
    .string "SANTUARIO DRAGÓN\p"
    .string "Un santuario en honor a los\n"
    .string "POKéMON dragón\p"
    .string "dicen que vivió en la GUERRA\n"
    .string "DE DRAGONES.$"

DragonsDen_Cavern_Text_SilverTraining1:
    .string "…\n"
    .string "¿Qué? ¿{PLAYER}?\p"
    .string "...No, no lucharé contigo ahora...\p"
    .string "Mis POKéMON no están listos para\n"
    .string "vencerte.\p"
    .string "No puedo forzarlos demasiado ahora.\p"
    .string "Debo ser disciplinado para ser el\n"
    .string "mejor ENTRENADOR POKéMON...$"

DragonsDen_Cavern_Text_SilverTraining2:
    .string "…\p"
    .string "Uff...\p"
    .string "Aprende a no cruzarte en mi camino...$"

DragonsDen_Cavern_Text_CooltrainermDarinSeen:
    .string "¡Tú! ¡Cómo te atreves a entrar\n"
    .string "sin invitación!$"

DragonsDen_Cavern_Text_CooltrainermDarinBeaten:
    .string "S-strong!$"

DragonsDen_Cavern_Text_CooltrainermDarinAfter:
    .string "El SANTUARIO de adelante es el hogar\n"
    .string "del MAESTRO de nuestro clan dragón.\p"
    .string "¡No puedes entrar así nada más!$"

DragonsDen_Cavern_Text_CooltrainerfCaraSeen:
    .string "¡No deberías estar aquí!$"

DragonsDen_Cavern_Text_CooltrainerfCaraBeaten:
    .string "Oh yikes, I lost!$"

DragonsDen_Cavern_Text_CooltrainerfCaraAfter:
    .string "Pronto tendré el permiso\n"
    .string "de nuestro MAESTRO para usar dragones.\p"
    .string "Cuando pase, seré un\n"
    .string "admirable ENTRENADOR dragón y tendré\l"
    .string "la aprobación de nuestro MAESTRO.$"

DragonsDen_Cavern_Text_TwinsLeaandPia1Seen:
    .string "Es un desconocido que no conocemos.$"

DragonsDen_Cavern_Text_TwinsLeaandPia1Beaten:
    .string "Ouchies.$"

DragonsDen_Cavern_Text_TwinsLeaandPia1After:
    .string "Fue como tener que luchar\n"
    .string "contra LANCE.$"

DragonsDen_Cavern_Text_TwinsLeaandPia2Seen:
    .string "¿Quién eres?$"

DragonsDen_Cavern_Text_TwinsLeaandPia2Beaten:
    .string "Meanie.$"

DragonsDen_Cavern_Text_TwinsLeaandPia2After:
    .string "Te vamos a delatar.\p"
    .string "El MAESTRO se enojará contigo.$"
