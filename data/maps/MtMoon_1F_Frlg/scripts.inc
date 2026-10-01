MtMoon_1F_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MtMoon_1F_OnTransition
	.byte 0

MtMoon_1F_OnTransition::
	setworldmapflag FLAG_WORLD_MAP_MT_MOON_1F
	end

MtMoon_1F_EventScript_ZubatSign::
	msgbox MtMoon_1F_Text_ZubatIsABloodsucker, MSGBOX_SIGN
	end

MtMoon_1F_EventScript_Marcos::
	trainerbattle_single TRAINER_HIKER_MARCOS, MtMoon_1F_Text_MarcosIntro, MtMoon_1F_Text_MarcosDefeat
	msgbox MtMoon_1F_Text_MarcosPostBattle, MSGBOX_AUTOCLOSE
	end

MtMoon_1F_EventScript_Josh::
	trainerbattle_single TRAINER_YOUNGSTER_JOSH, MtMoon_1F_Text_JoshIntro, MtMoon_1F_Text_JoshDefeat
	msgbox MtMoon_1F_Text_JoshPostBattle, MSGBOX_AUTOCLOSE
	end

MtMoon_1F_EventScript_Miriam::
	trainerbattle_single TRAINER_LASS_MIRIAM, MtMoon_1F_Text_MiriamIntro, MtMoon_1F_Text_MiriamDefeat
	msgbox MtMoon_1F_Text_MiriamPostBattle, MSGBOX_AUTOCLOSE
	end

MtMoon_1F_EventScript_Iris::
	trainerbattle_single TRAINER_LASS_IRIS, MtMoon_1F_Text_IrisIntro, MtMoon_1F_Text_IrisDefeat
	msgbox MtMoon_1F_Text_IrisPostBattle, MSGBOX_AUTOCLOSE
	end

MtMoon_1F_EventScript_Jovan::
	trainerbattle_single TRAINER_SUPER_NERD_JOVAN, MtMoon_1F_Text_JovanIntro, MtMoon_1F_Text_JovanDefeat
	msgbox MtMoon_1F_Text_JovanPostBattle, MSGBOX_AUTOCLOSE
	end

MtMoon_1F_EventScript_Kent::
	trainerbattle_single TRAINER_BUG_CATCHER_KENT, MtMoon_1F_Text_KentIntro, MtMoon_1F_Text_KentDefeat
	msgbox MtMoon_1F_Text_KentPostBattle, MSGBOX_AUTOCLOSE
	end

MtMoon_1F_EventScript_Robby::
	trainerbattle_single TRAINER_BUG_CATCHER_ROBBY, MtMoon_1F_Text_RobbyIntro, MtMoon_1F_Text_RobbyDefeat
	msgbox MtMoon_1F_Text_RobbyPostBattle, MSGBOX_AUTOCLOSE
	end

MtMoon_1F_Text_MarcosIntro::
	.string "¡VAYA!\n"
	.string "¡Me sorprendiste!\l"
	.string "...¡Ah, eres solo un niño!$"

MtMoon_1F_Text_MarcosDefeat::
	.string "¡Guau!\n"
	.string "¡Sorprendido otra vez!$"

MtMoon_1F_Text_MarcosPostBattle::
	.string "Chicos como tú no deberían\n"
	.string "andar aquí en la oscuridad.$"

MtMoon_1F_Text_JoshIntro::
	.string "¿Vienes a explorar la cueva?\n"
	.string "las pinturas?$"

MtMoon_1F_Text_JoshDefeat::
	.string "¡Perder apesta!\n"
	.string "Qué poco genial.$"

MtMoon_1F_Text_JoshPostBattle::
	.string "Vine hasta aquí abajo para\n"
	.string "presumir ante las chicas.$"

MtMoon_1F_Text_MiriamIntro::
	.string "¡Guau! Es mucho más grande aquí\n"
	.string "que pensaba!$"

MtMoon_1F_Text_MiriamDefeat::
	.string "Oh!\n"
	.string "¡Lo perdí!$"

MtMoon_1F_Text_MiriamPostBattle::
	.string "¿Cómo salgo de este lugar?\n"
	.string "Es tan grande que puedo perderme.$"

MtMoon_1F_Text_JovanIntro::
	.string "¡Qué!\n"
	.string "¡No me asustes así!$"

MtMoon_1F_Text_JovanDefeat::
	.string "¡Mis POKéMON no sirven!$"

MtMoon_1F_Text_JovanPostBattle::
	.string "Debo hallar POKéMON más fuertes.\n"
	.string "¿Dónde estarán?$"

MtMoon_1F_Text_IrisIntro::
	.string "¿Qué?\n"
	.string "Estoy esperando a que mis amigos\l"
	.string "me encuentren aquí.$"

MtMoon_1F_Text_IrisDefeat::
	.string "¿Perdí?$"

MtMoon_1F_Text_IrisPostBattle::
	.string "Vine porque escuché que hay\n"
	.string "fósiles muy raros aquí.$"

MtMoon_1F_Text_KentIntro::
	.string "Hombres sospechosos en la cueva.\n"
	.string "¿Y tú qué?$"

MtMoon_1F_Text_KentDefeat::
	.string "¡Me atrapaste!$"

MtMoon_1F_Text_KentPostBattle::
	.string "¡Los vi!\n"
	.string "¡Seguro que son del EQUIPO ROCKET!$"

MtMoon_1F_Text_RobbyIntro::
	.string "Tienes que cruzar esta cueva\n"
	.string "para llegar a CIUDAD CELESTE.$"

MtMoon_1F_Text_RobbyDefeat::
	.string "Perdí.$"

MtMoon_1F_Text_RobbyPostBattle::
	.string "¡ZUBAT es fuerte!\n"
	.string "Pero si atrapas uno, \l"
	.string "poder contar con él.$"

MtMoon_1F_Text_ZubatIsABloodsucker::
	.string "¡Cuidado!\n"
	.string "¡ZUBAT es un chupasangre!$"

MtMoon_1F_Text_BrockHelpsExcavateFossils::
	.string "Hola, estoy excavando fósiles\n"
	.string "bajo el MT. MOON.\p"
	.string "A veces, BROCK del GIMNASIO de\n"
	.string "CIUDAD PLATEA me ayuda.$"
