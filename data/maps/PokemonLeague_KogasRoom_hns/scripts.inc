PokemonLeague_KogasRoom_hns_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, EliteFourRoom_OnFrame
	map_script MAP_SCRIPT_ON_RESUME, PokemonLeague_KogasRoom_OnResume
	map_script MAP_SCRIPT_ON_LOAD, EliteFourRoom_OnLoad
	.byte 0

PokemonLeague_KogasRoom_OnResume::
	setvar VAR_0x8004, 1
	special DoPokemonLeagueLightingEffect
	end

PokemonLeague_KogasRoom_EventScript_Koga::
	lock 
	faceplayer
	goto_if_ge VAR_LEAGUE_STATE, 3, PokemonLeague_KogasRoom_EventScript_KogaDefeated
	goto_if_set FLAG_IS_CHAMPION, PokemonLeague_KogasRoom_EventScript_KogaRematch
	msgbox PokemonLeague_KogasRoom_Text_Before, MSGBOX_DEFAULT
	setflag FLAG_TEMP_3
	setflag FLAG_TEMP_5
	trainerbattle_no_intro TRAINER_KOGA_1_HNS, PokemonLeague_KogasRoom_Text_Beaten
	goto PokemonLeague_KogasRoom_EventScript_KogaOnDefeat

PokemonLeague_KogasRoom_EventScript_KogaRematch::
	goto_if_unset FLAG_IS_KANTO_CHAMPION, PokemonLeague_KogasRoom_EventScript_KogaRematchStandard
	goto_if_ge VAR_SINJOH_STORYLINE, 13, PokemonLeague_KogasRoom_EventScript_KogaRematchPostOBC

PokemonLeague_KogasRoom_EventScript_KogaRematchStandard::
	msgbox PokemonLeague_KogasRoom_Text_RematchBefore, MSGBOX_DEFAULT
	setflag FLAG_TEMP_3
	setflag FLAG_TEMP_5
	trainerbattle_no_intro TRAINER_KOGA_2_HNS, PokemonLeague_KogasRoom_Text_Beaten
	goto PokemonLeague_KogasRoom_EventScript_KogaOnDefeat

PokemonLeague_KogasRoom_EventScript_KogaRematchPostOBC::
	msgbox PokemonLeague_KogasRoom_Text_RematchBefore, MSGBOX_DEFAULT
	setflag FLAG_TEMP_3
	setflag FLAG_TEMP_5
	trainerbattle_no_intro TRAINER_KOGA_POSTOBC_HNS, PokemonLeague_KogasRoom_Text_Beaten
	goto PokemonLeague_KogasRoom_EventScript_KogaOnDefeat

PokemonLeague_KogasRoom_EventScript_KogaOnDefeat::
	clearflag FLAG_TEMP_5
	msgbox PokemonLeague_KogasRoom_Text_Defeat, MSGBOX_DEFAULT
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
	setvar VAR_LEAGUE_STATE, 3
	release
	end

PokemonLeague_KogasRoom_EventScript_KogaDefeated::
	msgbox PokemonLeague_KogasRoom_Text_Defeat, MSGBOX_DEFAULT
	closemessage
	release
	end

PokemonLeague_KogasRoom_Text_RematchBefore:
    .string "KOGA: ¡Fwahahahaha!\p"
    .string "Vuelves, valiente retador.\p"
    .string "Mis artes ninja se han pulido.\p"
    .string "Nuevas trampas te esperan.\p"
    .string "Veneno, sueño y mucho más...\n"
    .string "¡Prepárate!\p"
    .string "¡Fwahahahaha!\p"
    .string "¡Muéstrame cuánto has crecido!$"

PokemonLeague_KogasRoom_Text_Before:
    .string "¡Fwahahahaha!\p"
    .string "Soy KOGA, del ALTO MANDO.\p"
    .string "¡Vivo en las sombras, soy ninja!\p"
    .string "Mi estilo complejo te confundirá\n"
    .string "¡y te destruirá!\p"
    .string "Confusión, sueño, veneno...\p"
    .string "¡Prepárate para ser la víctima de\n"
    .string "mi técnica siniestra!\p"
    .string "¡Fwahahahaha!\p"
    .string "POKéMON no es solo fuerza bruta...\n"
    .string "¡Pronto lo verás!$"

PokemonLeague_KogasRoom_Text_Beaten:
    .string "Ah!\n"
    .string "¡Has demostrado tu valor!$"

PokemonLeague_KogasRoom_Text_Defeat:
    .string "Te sometí a todo lo que pude\n"
    .string "reunir.\p"
    .string "Pero fallé. Debo perfeccionar\n"
    .string "mis habilidades.\p"
    .string "¡Ve a la siguiente sala y pon a\n"
    .string "prueba tu capacidad!$"
