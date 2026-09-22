SilphCo_2F_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, SilphCo_2F_OnLoad
	.byte 0

SilphCo_2F_OnLoad::
	call_if_unset FLAG_SILPH_2F_DOOR_1, EventScript_Close2FDoor1
	call_if_unset FLAG_SILPH_2F_DOOR_2, EventScript_Close2FDoor2
	end

SilphCo_2F_EventScript_ThunderWaveTutor::
	goto EventScript_ThunderWaveTutor
	end

SilphCo_2F_EventScript_FloorSign::
	msgbox SilphCo_2F_Text_FloorSign, MSGBOX_SIGN
	end

SilphCo_2F_EventScript_Connor::
	trainerbattle_single TRAINER_SCIENTIST_CONNOR, SilphCo_2F_Text_ConnorIntro, SilphCo_2F_Text_ConnorDefeat
	msgbox SilphCo_2F_Text_ConnorPostBattle, MSGBOX_AUTOCLOSE
	end

SilphCo_2F_EventScript_Jerry::
	trainerbattle_single TRAINER_SCIENTIST_JERRY, SilphCo_2F_Text_JerryIntro, SilphCo_2F_Text_JerryDefeat
	msgbox SilphCo_2F_Text_JerryPostBattle, MSGBOX_AUTOCLOSE
	end

SilphCo_2F_EventScript_Grunt1::
	trainerbattle_single TRAINER_TEAM_ROCKET_GRUNT_23, SilphCo_2F_Text_Grunt1Intro, SilphCo_2F_Text_Grunt1Defeat
	msgbox SilphCo_2F_Text_Grunt1PostBattle, MSGBOX_AUTOCLOSE
	end

SilphCo_2F_EventScript_Grunt2::
	trainerbattle_single TRAINER_TEAM_ROCKET_GRUNT_24, SilphCo_2F_Text_Grunt2Intro, SilphCo_2F_Text_Grunt2Defeat
	msgbox SilphCo_2F_Text_Grunt2PostBattle, MSGBOX_AUTOCLOSE
	end

SilphCo_2F_Text_ConnorIntro::
	.string "Help!\n"
	.string "Soy empleado de SILPH.$"

SilphCo_2F_Text_ConnorDefeat::
	.string "¿Cómo supiste que\n"
	.string "fui un ROCKET?$"

SilphCo_2F_Text_ConnorPostBattle::
	.string "Trabajo para SILPH y para el\n"
	.string "ROCKET.$"

SilphCo_2F_Text_JerryIntro::
	.string "¡Aquí está prohibido pasar!\n"
	.string "¡Vete a casa!$"

SilphCo_2F_Text_JerryDefeat::
	.string "Eres bueno.$"

SilphCo_2F_Text_JerryPostBattle::
	.string "¿Puedes resolver el laberinto?\n"
	.string "¡No es fácil, te lo digo!$"

SilphCo_2F_Text_Grunt1Intro::
	.string "¡Aquí no se permiten niños!$"

SilphCo_2F_Text_Grunt1Defeat::
	.string "Tough!$"

SilphCo_2F_Text_Grunt1PostBattle::
	.string "Las baldosas en forma de diamante\n"
	.string "blocks.\p"
	.string "Son transportadores de este lugar\n"
	.string "high-tech building.$"

SilphCo_2F_Text_Grunt2Intro::
	.string "Hey, kid!\n"
	.string "¿Qué haces vagando por aquí?$"

SilphCo_2F_Text_Grunt2Defeat::
	.string "I goofed!$"

SilphCo_2F_Text_Grunt2PostBattle::
	.string "SILPH CO. se asociará con\n"
	.string "TEAM ROCKET!$"

Text_ThunderWaveTeach::
	.string "Eeek!\n"
	.string "¡No! ¡Alto! ¡Auxilio!\p"
	.string "Oh, no eres del TEAM ROCKET.\n"
	.string "I'm sorry, I thought...\p"
	.string "¿Me perdonarás si te enseño\n"
	.string "la técnica ONDA TRUENO?$"

Text_ThunderWaveDeclined::
	.string "Oh...\n"
	.string "Pero ONDA TRUENO es útil...$"

Text_ThunderWaveWhichMon::
	.string "¿A qué POKéMON le enseño\n"
	.string "THUNDER WAVE?$"

Text_ThunderWaveTaught::
	.string "ONDA TRUENO causa parálisis en\n"
	.string "the target POKéMON.\p"
	.string "A paralyzed POKéMON may be unable\n"
	.string "para moverse en batalla.\p"
	.string "Es un movimiento tipo ELÉCTRICO, así\n"
	.string "won't work on some POKéMON.$"

SilphCo_2F_Text_FloorSign::
	.string "SILPH CO. HEAD OFFICE\n"
	.string "2F$"

