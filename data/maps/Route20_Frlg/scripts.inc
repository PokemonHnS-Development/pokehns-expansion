Route20_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route20_OnTransition
	.byte 0

Route20_OnTransition::
	call_if_unset FLAG_STOPPED_SEAFOAM_B3F_CURRENT, Route20_EventScript_ResetSeafoamBouldersForB3F
	call_if_unset FLAG_STOPPED_SEAFOAM_B4F_CURRENT, Route20_EventScript_ResetSeafoamBouldersForB4F
	end

Route20_EventScript_ResetSeafoamBouldersForB3F::
	clearflag FLAG_HIDE_SEAFOAM_1F_BOULDER_1
	clearflag FLAG_HIDE_SEAFOAM_1F_BOULDER_2
	setflag FLAG_HIDE_SEAFOAM_B1F_BOULDER_1
	setflag FLAG_HIDE_SEAFOAM_B1F_BOULDER_2
	setflag FLAG_HIDE_SEAFOAM_B2F_BOULDER_1
	setflag FLAG_HIDE_SEAFOAM_B2F_BOULDER_2
	setflag FLAG_HIDE_SEAFOAM_B3F_BOULDER_1
	setflag FLAG_HIDE_SEAFOAM_B3F_BOULDER_2
	return

Route20_EventScript_ResetSeafoamBouldersForB4F::
	clearflag FLAG_HIDE_SEAFOAM_B3F_BOULDER_3
	clearflag FLAG_HIDE_SEAFOAM_B3F_BOULDER_4
	clearflag FLAG_HIDE_SEAFOAM_B3F_BOULDER_5
	clearflag FLAG_HIDE_SEAFOAM_B3F_BOULDER_6
	setflag FLAG_HIDE_SEAFOAM_B4F_BOULDER_1
	setflag FLAG_HIDE_SEAFOAM_B4F_BOULDER_2
	return

Route20_EventScript_SeafoamIslandsSign::
	msgbox Route20_Text_SeafoamIslands, MSGBOX_SIGN
	end

Route20_Text_BarryIntro::
	.string "El agua es poco profunda aquí.\n"
	.string "Hay mucha gente nadando.$"

Route20_Text_BarryDefeat::
	.string "¡Chof!$"

Route20_Text_BarryPostBattle::
	.string "Ojalá pudiera montar mi POKéMON.\n"
	.string "Apuesto a que no estás cansado.$"

Route20_Text_ShirleyIntro::
	.string "ISLA ESPUMA es un lugar tranquilo.\n"
	.string "Estoy de vacaciones aquí.$"

Route20_Text_ShirleyDefeat::
	.string "¡Basta!$"

Route20_Text_ShirleyPostBattle::
	.string "Hay una caverna enorme debajo\n"
	.string "de esta isla.$"

Route20_Text_TiffanyIntro::
	.string "Amo flotar con los peces\n"
	.string "aquí entre las olas.$"

Route20_Text_TiffanyDefeat::
	.string "¡Auch!$"

Route20_Text_TiffanyPostBattle::
	.string "¿Quieres flotar conmigo?$"

Route20_Text_IreneIntro::
	.string "¿También estás de vacaciones?$"

Route20_Text_IreneDefeat::
	.string "¡Sin piedad alguna!$"

Route20_Text_IrenePostBattle::
	.string "ISLA ESPUMA era una sola isla\n"
	.string "en el pasado lejano.$"

Route20_Text_DeanIntro::
	.string "¡Mira mi físico musculoso!$"

Route20_Text_DeanDefeat::
	.string "¡Cobarde!$"

Route20_Text_DeanPostBattle::
	.string "Debí haber estado fortaleciendo\n"
	.string "POKéMON, not me!$"

Route20_Text_DarrinIntro::
	.string "¿Por qué montas un POKéMON?\n"
	.string "¿No sabes nadar?$"

Route20_Text_DarrinDefeat::
	.string "¡Ay!\n"
	.string "¡Torpedeado!$"

Route20_Text_DarrinPostBattle::
	.string "Riding a POKéMON sure looks fun!$"

Route20_Text_RogerIntro::
	.string "Vine aquí en mi POKéMON ave.$"

Route20_Text_RogerDefeat::
	.string "¡Oh, no!\n"
	.string "¿Y ahora qué hago?$"

Route20_Text_RogerPostBattle::
	.string "Mis pájaros están agotados.\n"
	.string "¡No pueden VOLAR de vuelta!$"

Route20_Text_NoraIntro::
	.string "Mi novio me dio perlas grandes.$"

Route20_Text_NoraDefeat::
	.string "¡Oh, no!\n"
	.string "¡Mis perlas estaban en ellas!$"

Route20_Text_NoraPostBattle::
	.string "¿Mis perlas crecerán más dentro\n"
	.string "¿CLOYSTER?$"

Route20_Text_MissyIntro::
	.string "Nadé desde ISLA CANELA hasta aquí.\n"
	.string "No fue fácil, te lo digo.$"

Route20_Text_MissyDefeat::
	.string "¡Qué decepción!$"

Route20_Text_MissyPostBattle::
	.string "POKéMON se han apoderado de una\n"
	.string "mansión abandonada de ISLA C.\p"
	.string "La llaman la MANSIÓN POKéMON\n"
	.string "ahora.$"

Route20_Text_MelissaIntro::
	.string "En CANELA, al oeste, hay un LAB\n"
	.string "POKéMON planta.\p"
	.string "Mi papá trabaja allí.$"

Route20_Text_MelissaDefeat::
	.string "¡Espera!\n"
	.string "¡Se supone que debes esperar!$"

Route20_Text_MelissaPostBattle::
	.string "ISLA C. es una isla volcánica.\p"
	.string "Escuché que surgió del mar\n"
	.string "cuando un volcán hizo erupción.$"

Route20_Text_SeafoamIslands::
	.string "ISLAS ESPUMA$"

Route20_Text_MistyTrainsHere::
	.string "ENTRENADORES fuertes y POKéMON de\n"
	.string "de AGUA abundan por aquí.\p"
	.string "Dicen que MISTY, del\n"
	.string "GIMNASIO CERULEAN, entrena aquí.$"
