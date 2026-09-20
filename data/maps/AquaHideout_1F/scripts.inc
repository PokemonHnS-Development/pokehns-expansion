AquaHideout_1F_MapScripts::
	.byte 0

@ The below two entrance guards give hints about what to do to progress the story
AquaHideout_1F_EventScript_HideoutEntranceGrunt1::
	lock
	faceplayer
	goto_if_set FLAG_GROUDON_AWAKENED_MAGMA_HIDEOUT, AquaHideout_1F_EventScript_SlateportHint1
	goto_if_set FLAG_RECEIVED_RED_OR_BLUE_ORB, AquaHideout_1F_EventScript_MagmaHideoutHint1
	msgbox AquaHideout_1F_Text_OurBossIsSnatchingSomething, MSGBOX_DEFAULT
	release
	end

AquaHideout_1F_EventScript_MagmaHideoutHint1::
	msgbox AquaHideout_1F_Text_WhereMightMagmaHideoutBe, MSGBOX_DEFAULT
	release
	end

AquaHideout_1F_EventScript_SlateportHint1::
	msgbox AquaHideout_1F_Text_BossWentToJackASubmarine, MSGBOX_DEFAULT
	release
	end

AquaHideout_1F_EventScript_HideoutEntranceGrunt2::
	lock
	faceplayer
	goto_if_set FLAG_GROUDON_AWAKENED_MAGMA_HIDEOUT, AquaHideout_1F_EventScript_SlateportHint2
	goto_if_set FLAG_RECEIVED_RED_OR_BLUE_ORB, AquaHideout_1F_EventScript_MagmaHideoutHint2
	msgbox AquaHideout_1F_Text_BossIsOnRoute122, MSGBOX_DEFAULT
	release
	end

AquaHideout_1F_EventScript_MagmaHideoutHint2::
	msgbox AquaHideout_1F_Text_TeamMagmaAtMtChimney, MSGBOX_DEFAULT
	release
	end

AquaHideout_1F_EventScript_SlateportHint2::
	msgbox AquaHideout_1F_Text_BossIsInSlateportCity, MSGBOX_DEFAULT
	release
	end

AquaHideout_1F_EventScript_Grunt1::
	trainerbattle_single TRAINER_GRUNT_AQUA_HIDEOUT_1, AquaHideout_1F_Text_Grunt1Intro, AquaHideout_1F_Text_Grunt1Defeat, AquaHideout_1F_EventScript_Grunt1Defeated
	msgbox AquaHideout_1F_Text_Grunt1PostBattle, MSGBOX_AUTOCLOSE
	end

AquaHideout_1F_EventScript_Grunt1Defeated::
	msgbox AquaHideout_1F_Text_Grunt1PostBattle, MSGBOX_DEFAULT
	release
	end

AquaHideout_1F_Text_OurBossIsSnatchingSomething:
	.string "¿Qué? ¿Qué? ¿Qué quieres con el \n"
	.string "EQUIPO AQUA?\p"
	.string "¡Nuestro JEFE no está! Se fue para\n"
	.string "¡robar algo importante!\p"
	.string "… …\n"
	.string "¿A dónde se fue?\p"
	.string "¡Jajaja! ¿De verdad crees que te\n"
	.string "diría algo tan crucial?$"

AquaHideout_1F_Text_WhereMightMagmaHideoutBe:
	.string "¿Qué? ¿Qué?\n"
	.string "¿Eres un recluta del EQUIPO MAGMA?\p"
	.string "Oigo que el EQUIPO MAGMA intenta\n"
	.string "despertar a un POKéMON increíble en su\l"
	.string "GUARIDA.\p"
	.string "¿Pero dónde estará su GUARIDA?$"

AquaHideout_1F_Text_BossWentToJackASubmarine:
	.string "¿Qué? ¿Qué? ¿Qué quieres con el \n"
	.string "EQUIPO AQUA?\p"
	.string "¡Nuestro JEFE no está aquí!\n"
	.string "¡Se fue a robar un submarino!\p"
	.string "… …\n"
	.string "¿A dónde se fue?\p"
	.string "¡Jajaja! ¿De verdad crees que te\n"
	.string "diría algo tan crucial?$"

AquaHideout_1F_Text_BossIsOnRoute122:
	.string "¿Qué? ¿Qué? ¿Qué quieres con el \n"
	.string "EQUIPO AQUA?\p"
	.string "¡Nuestro JEFE no está! Va camino al\n"
	.string "MONTE CENIZA en la RUTA 122!\p"
	.string "… …\n"
	.string "¿Por qué se fue?\p"
	.string "¡Jajaja! ¿De verdad crees que te\n"
	.string "diría algo tan crucial?$"

AquaHideout_1F_Text_TeamMagmaAtMtChimney:
	.string "¿Qué? ¿Qué?\n"
	.string "¿Eres un recluta del EQUIPO MAGMA?\p"
	.string "Oigo que el EQUIPO MAGMA busca a\n"
	.string "un gran POKéMON en el MT. CHIMNEY.\p"
	.string "¿Pero cómo es ese POKéMON?$"

AquaHideout_1F_Text_BossIsInSlateportCity:
	.string "¿Qué? ¿Qué? ¿Qué quieres de mí?\n"
	.string "EQUIPO AQUA?\p"
	.string "¡Nuestro JEFE no está aquí!\n"
	.string "¡Va camino a CIUDAD MALTA!\p"
	.string "… …\n"
	.string "¿Por qué se fue?\p"
	.string "¡Jajaja! ¿De verdad crees que te\n"
	.string "diría algo tan crucial?$"

AquaHideout_1F_Text_Grunt1Intro:
	.string "¡Ayiyiyi!\n"
	.string "¡He visto a alguien sospechoso!$"

AquaHideout_1F_Text_Grunt1Defeat:
	.string "Grrrrr...\n"
	.string "¡Lo perdí!$"

AquaHideout_1F_Text_Grunt1PostBattle:
	.string "Perdí por el bien del EQUIPO,\n"
	.string "pero cumplí mi misión...$"

