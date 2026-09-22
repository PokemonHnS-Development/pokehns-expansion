PokemonLeague_KarensRoom_hns_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, EliteFourRoom_OnFrame
	map_script MAP_SCRIPT_ON_RESUME, PokemonLeague_KarensRoom_OnResume
	map_script MAP_SCRIPT_ON_LOAD, EliteFourRoom_OnLoad
	.byte 0

PokemonLeague_KarensRoom_OnResume::
	setvar VAR_0x8004, 3
	special DoPokemonLeagueLightingEffect
	end

PokemonLeague_KarensRoom_EventScript_Karen::
	lock 
	faceplayer
	goto_if_ge VAR_LEAGUE_STATE, 5, PokemonLeague_KarensRoom_EventScript_KarenDefeated
	goto_if_set FLAG_IS_CHAMPION, PokemonLeague_KarensRoom_EventScript_KarenRematch
	msgbox PokemonLeague_KarensRoom_Text_Before, MSGBOX_DEFAULT
	setflag FLAG_TEMP_3
	setflag FLAG_TEMP_5
	trainerbattle_no_intro TRAINER_KAREN_1_HNS, PokemonLeague_KarensRoom_Text_Beaten
	goto PokemonLeague_KarensRoom_EventScript_KarenOnDefeat

PokemonLeague_KarensRoom_EventScript_KarenRematch::
	goto_if_unset FLAG_IS_KANTO_CHAMPION, PokemonLeague_KarensRoom_EventScript_KarenRematchStandard
	goto_if_ge VAR_SINJOH_STORYLINE, 13, PokemonLeague_KarensRoom_EventScript_KarenRematchPostOBC

PokemonLeague_KarensRoom_EventScript_KarenRematchStandard::
	msgbox PokemonLeague_KarensRoom_Text_RematchBefore, MSGBOX_DEFAULT
	setflag FLAG_TEMP_3
	setflag FLAG_TEMP_5
	trainerbattle_no_intro TRAINER_KAREN_2_HNS, PokemonLeague_KarensRoom_Text_Beaten
	goto PokemonLeague_KarensRoom_EventScript_KarenOnDefeat

PokemonLeague_KarensRoom_EventScript_KarenRematchPostOBC::
	msgbox PokemonLeague_KarensRoom_Text_RematchBefore, MSGBOX_DEFAULT
	setflag FLAG_TEMP_3
	setflag FLAG_TEMP_5
	trainerbattle_no_intro TRAINER_KAREN_POSTOBC_HNS, PokemonLeague_KarensRoom_Text_Beaten
	goto PokemonLeague_KarensRoom_EventScript_KarenOnDefeat

PokemonLeague_KarensRoom_EventScript_KarenOnDefeat::
    clearflag FLAG_TEMP_5
	msgbox PokemonLeague_KarensRoom_Text_Defeat, MSGBOX_DEFAULT
	closemessage
	setmetatile 6, 1, 0x28E, FALSE
	setmetatile 6, 2, 0x296, FALSE	
	playse SE_BANG
	setvar VAR_0x8004, 1  @ vertical pan
	setvar VAR_0x8005, 1  @ horizontal pan
	setvar VAR_0x8006, 4  @ num shakes
	setvar VAR_0x8007, 4  @ shake delay
	special ShakeCamera
	waitstate
	special DrawWholeMapView
	setvar VAR_LEAGUE_STATE, 5
	release
	end

PokemonLeague_KarensRoom_EventScript_KarenDefeated::
	msgbox PokemonLeague_KarensRoom_Text_Defeat, MSGBOX_DEFAULT
	closemessage
	release
	end

PokemonLeague_KarensRoom_Text_RematchBefore:
    .string "KAREN: Ah, eres tú otra vez.\p"
    .string "Confío en que no has olvidado\n"
    .string "mi creencia:\p"
    .string "La fuerza real nace de la confianza\n"
    .string "en los POKéMON.\p"
    .string "Desde nuestro último encuentro,\n"
    .string "mi vínculo con mis POKéMON\l"
    .string "se ha vuelto más profundo.\p"
    .string "¿Estás listo para enfrentar a un\n"
    .string "equipo con un vínculo irrompible?\p"
    .string "¡Muéstrame el poder del vínculo\n"
    .string "con tus POKéMON!$"

PokemonLeague_KarensRoom_Text_Before:
    .string "Soy KAREN, del ALTO MANDO.\p"
    .string "¿Tú eres {PLAYER}? Qué curioso.\p"
    .string "Amo los POKéMON tipo SINON.\p"
    .string "Su imagen salvaje y dura\n"
    .string "tan atractivos. Y además son\l"
    .string "son muy fuertes.\p"
    .string "¿Crees que puedes vencerlos?\n"
    .string "Intenta entretenerme.\p"
    .string "¡Vamos!$"

PokemonLeague_KarensRoom_Text_Beaten:
    .string "Vaya, eres bueno. Eso me\n"
    .string "de un ENTRENADOR.$"

PokemonLeague_KarensRoom_Text_Defeat:
    .string "POKéMON fuertes.\p"
    .string "POKéMON débiles.\p"
    .string "Esa es solo la percepción\n"
    .string "egoísta de la gente.\p"
    .string "Los entrenadores hábiles deben\n"
    .string "ganar con sus favoritos.\p"
    .string "Me gusta tu estilo. Entiendes\n"
    .string "lo que es importante.\p"
    .string "Ve ya, el CAMPEÓN te espera.$"

