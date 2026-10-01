CinnabarIsland_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, CinnabarIsland_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0
	
CinnabarIsland_OnTransition:
	setflag FLAG_VISITED_CINNABAR_ISLAND
	callnative SetTimeBasedEncounters
	end

CinnabarIsland_EventScript_Blaine::
    lock
    faceplayer
    msgbox CinnabarIsland_Text_Blaine, MSGBOX_DEFAULT
    closemessage
    fadescreenswapbuffers FADE_TO_BLACK
    setflag FLAG_HIDE_CINNABAR_BLAINE
    removeobject LOCALID_CINNABAR_BLAINE
    fadescreenswapbuffers FADE_FROM_BLACK
    clearflag FLAG_HIDE_DOJO_BLAINE
    release
    end

CinnabarIsland_Text_Blaine:
    .string "BLAINE: Jamás me rendiré\n"
	.string "hasta el día en que reconstruya\l"
	.string "¡el GIMNASIO CANELA!\p"
	.string "Estaré en el DOJO DE LUCHA\n"
	.string "hasta entonces.$"



CinnabarIsland_EventScript_Blue::
	lock
	faceplayer
	goto_if_eq VAR_NUM_BADGES, 15, CinnabarIsland_EventScript_BlueActive
	msgbox CinnabarIsland_Text_BlueBefore, MSGBOX_NPC
	release
	end

CinnabarIsland_EventScript_BlueActive::
	msgbox CinnabarIsland_Text_Blue, MSGBOX_NPC
	fadescreenswapbuffers FADE_TO_BLACK
	setflag FLAG_HIDE_CINNABAR_BLUE
	removeobject LOCALID_CINNABAR_BLUE
	clearflag FLAG_HIDE_VIRIDIAN_BLUE
	fadescreenswapbuffers FADE_FROM_BLACK
	release
	end


CinnabarIsland_Text_BlueBefore:
	.string "¿Quién eres?\p"
	.string "Bueno, es evidente que eres\n"
	.string "un ENTRENADOR...\p"
	.string "Mi nombre es BLUE.\p"
	.string "Fui el CAMPEÓN, aunque\n"
	.string "fue solo por poco tiempo...\p"
	.string "Ese entrometido RED me venció...\p"
	.string "En fin, ¿qué quieres? ¿Quieres?\n"
	.string "¿Vienes a desafiarme o algo así?\p"
	.string "...Odio decirlo, pero no estoy en\n"
	.string "ánimo de luchar ahora mismo.\p"
	.string "Mira bien a tu alrededor...\p"
	.string "Un volcán erupciona y, así de\n"
	.string "repente, un pueblo entero desaparece.\p"
	.string "Podemos ganar o perder con los\n"
	.string "POKéMON. Pero si la naturaleza se\l"
	.string "mueve, podemos perder en un segundo.\p"
	.string "...\p"
	.string "Así son las cosas...\p"
	.string "Pero, sea como sea, soy entrenador.\p"
	.string "Si veo a un rival fuerte, entonces\n"
	.string "me dan ganas de luchar.\p"
	.string "Si quieres luchar conmigo, primero\n"
	.string "necesitarás 15 medallas.\p"
	.string "Te enfrentaré entonces.$"

CinnabarIsland_Text_Blue:
	.string "¿Quién eres?\p"
	.string "Bueno, es evidente que eres\n"
	.string "un ENTRENADOR...\p"
	.string "Mi nombre es BLUE.\p"
	.string "Fui el CAMPEÓN, aunque\n"
	.string "fue solo por poco tiempo...\p"
	.string "Ese entrometido RED me venció...\p"
	.string "En fin, ¿qué quieres? ¿Quieres?\n"
	.string "¿Vienes a desafiarme o algo así?\p"
	.string "...Odio decirlo, pero no estoy en\n"
	.string "ánimo de luchar ahora mismo.\p"
	.string "Mira bien a tu alrededor...\p"
	.string "Un volcán erupciona y, así de\n"
	.string "repente, un pueblo entero desaparece.\p"
	.string "Podemos ganar o perder con los\n"
	.string "POKéMON. Pero si la naturaleza se\l"
	.string "mueve, podemos perder en un segundo.\p"
	.string "...\p"
	.string "Así son las cosas...\p"
	.string "Pero, sea como sea, soy entrenador.\p"
	.string "Si veo a un rival fuerte, entonces\n"
	.string "me dan ganas de luchar.\p"
	.string "Si quieres luchar conmigo, ve al\n"
	.string "GIMNASIO VIRIDIAN.\p"
	.string "Te enfrentaré entonces.$"

CinnabarIsland_EventScript_Sign::
	msgbox CinnabarIsland_Text_Sign, MSGBOX_SIGN
	end

CinnabarIsland_EventScript_GymSign::
	msgbox CinnabarIsland_Text_GymSign, MSGBOX_SIGN
	end

CinnabarIsland_Text_GymSign:
	.string "Hay un aviso aquí...\p"
	.string "El GIMNASIO CINNABAR se mudó a\n"
	.string "LAS ISLAS SEAFOAM.\p"
	.string "BLAINE$"

CinnabarIsland_Text_Sign:
	.string "ISLA CINNABAR\p"
	.string "El Pueblo Ardiente del Deseo$"

