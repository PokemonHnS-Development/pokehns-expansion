MtMoon_B2F_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MtMoon_B2F_OnTransition
	.byte 0

MtMoon_B2F_OnTransition::
	call_if_unset FLAG_GOT_FOSSIL_FROM_MT_MOON, MtMoon_B2F_EventScript_ShowFossils
	end

MtMoon_B2F_EventScript_ShowFossils::
	clearflag FLAG_HIDE_DOME_FOSSIL
	clearflag FLAG_HIDE_HELIX_FOSSIL
	return

MtMoon_B2F_EventScript_MiguelTrigger::
	lockall
	applymovement LOCALID_MIGUEL, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	call MtMoon_B2F_EventScript_BattleMiguel
	releaseall
	end

MtMoon_B2F_EventScript_Miguel::
	lock
	faceplayer
	goto_if_set FLAG_GOT_FOSSIL_FROM_MT_MOON, MtMoon_B2F_EventScript_MiguelFossilPicked
	goto_if_defeated TRAINER_SUPER_NERD_MIGUEL, MtMoon_B2F_EventScript_MiguelGoPickFossil
	call MtMoon_B2F_EventScript_BattleMiguel
	release
	end

MtMoon_B2F_EventScript_BattleMiguel::
	textcolor NPC_TEXT_COLOR_MALE
	message MtMoon_B2F_Text_MiguelIntro
	waitmessage
	playbgm MUS_RG_ENCOUNTER_GYM_LEADER, 0
	waitbuttonpress
	setvar VAR_LAST_TALKED, LOCALID_MIGUEL
	trainerbattle_no_intro TRAINER_SUPER_NERD_MIGUEL, MtMoon_B2F_Text_MiguelDefeat
	setvar VAR_MAP_SCENE_MT_MOON_B2F, 1
	msgbox MtMoon_B2F_Text_WellEachTakeAFossil
	return

MtMoon_B2F_EventScript_MiguelFossilPicked::
	msgbox MtMoon_B2F_Text_LabOnCinnabarRegeneratesFossils
	release
	end

MtMoon_B2F_EventScript_MiguelGoPickFossil::
	msgbox MtMoon_B2F_Text_WellEachTakeAFossil
	release
	end

MtMoon_B2F_EventScript_DomeFossil::
	lock
	faceplayer
	msgbox MtMoon_B2F_Text_YouWantDomeFossil, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MtMoon_B2F_EventScript_DontTakeFossil
	removeobject LOCALID_DOME_FOSSIL
	giveitem_msg MtMoon_B2F_Text_ObtainedDomeFossil, ITEM_DOME_FOSSIL, 1, MUS_RG_OBTAIN_KEY_ITEM
	closemessage
	delay 10
	applymovement LOCALID_MIGUEL, MtMoon_B2F_Movement_MiguelToHelixFossil
	waitmovement 0
	copyobjectxytoperm LOCALID_MIGUEL
	textcolor NPC_TEXT_COLOR_MALE
	playfanfare MUS_RG_OBTAIN_KEY_ITEM
	message MtMoon_B2F_Text_ThenThisFossilIsMine
	waitmessage
	waitfanfare
	removeobject LOCALID_HELIX_FOSSIL
	setflag FLAG_GOT_DOME_FOSSIL
	setflag FLAG_GOT_FOSSIL_FROM_MT_MOON
	release
	end

MtMoon_B2F_Movement_MiguelToHelixFossil::
	walk_right
	walk_up
	walk_up
	walk_up
	step_end

MtMoon_B2F_EventScript_HelixFossil::
	lock
	faceplayer
	msgbox MtMoon_B2F_Text_YouWantHelixFossil, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MtMoon_B2F_EventScript_DontTakeFossil
	removeobject LOCALID_HELIX_FOSSIL
	giveitem_msg MtMoon_B2F_Text_ObtainedHelixFossil, ITEM_HELIX_FOSSIL, 1, MUS_RG_OBTAIN_KEY_ITEM
	closemessage
	delay 10
	applymovement LOCALID_MIGUEL, MtMoon_B2F_Movement_MiguelToDomeFossil
	waitmovement 0
	copyobjectxytoperm LOCALID_MIGUEL
	textcolor NPC_TEXT_COLOR_MALE
	playfanfare MUS_RG_OBTAIN_KEY_ITEM
	message MtMoon_B2F_Text_ThenThisFossilIsMine
	waitmessage
	waitfanfare
	removeobject LOCALID_DOME_FOSSIL
	setflag FLAG_GOT_HELIX_FOSSIL
	setflag FLAG_GOT_FOSSIL_FROM_MT_MOON
	release
	end

MtMoon_B2F_EventScript_DontTakeFossil::
	release
	end

MtMoon_B2F_Movement_MiguelToDomeFossil::
	walk_up
	walk_up
	walk_up
	step_end

MtMoon_B2F_EventScript_Grunt1::
	trainerbattle_single TRAINER_TEAM_ROCKET_GRUNT, MtMoon_B2F_Text_Grunt1Intro, MtMoon_B2F_Text_Grunt1Defeat
	msgbox MtMoon_B2F_Text_Grunt1PostBattle, MSGBOX_AUTOCLOSE
	end

MtMoon_B2F_EventScript_Grunt2::
	trainerbattle_single TRAINER_TEAM_ROCKET_GRUNT_2, MtMoon_B2F_Text_Grunt2Intro, MtMoon_B2F_Text_Grunt2Defeat
	msgbox MtMoon_B2F_Text_Grunt2PostBattle, MSGBOX_AUTOCLOSE
	end

MtMoon_B2F_EventScript_Grunt3::
	trainerbattle_single TRAINER_TEAM_ROCKET_GRUNT_3, MtMoon_B2F_Text_Grunt3Intro, MtMoon_B2F_Text_Grunt3Defeat
	msgbox MtMoon_B2F_Text_Grunt3PostBattle, MSGBOX_AUTOCLOSE
	end

MtMoon_B2F_EventScript_Grunt4::
	trainerbattle_single TRAINER_TEAM_ROCKET_GRUNT_4, MtMoon_B2F_Text_Grunt4Intro, MtMoon_B2F_Text_Grunt4Defeat
	msgbox MtMoon_B2F_Text_Grunt4PostBattle, MSGBOX_AUTOCLOSE
	end

MtMoon_B2F_Text_MiguelIntro::
	.string "Hey, stop!\p"
	.string "I found these fossils!\n"
	.string "¡Los dos son míos!$"

MtMoon_B2F_Text_MiguelDefeat::
	.string "¡Está bien!\n"
	.string "I'll share!$"

MtMoon_B2F_Text_WellEachTakeAFossil::
	.string "¡Cada uno tomará un fósil!\n"
	.string "¡No seas codicioso!$"

MtMoon_B2F_Text_ThenThisFossilIsMine::
	.string "Está bien.\n"
	.string "¡Entonces este fósil es mío!$"

MtMoon_B2F_Text_LabOnCinnabarRegeneratesFossils::
	.string "Lejos, en la ISLA CANNELLE,\n"
	.string "there's a POKéMON LAB.\p"
	.string "Investigan la regeneración\n"
	.string "fossils.$"

MtMoon_B2F_Text_Grunt1Intro::
	.string "We, TEAM ROCKET, shall find the\n"
	.string "fossils!\p"
	.string "Reviving POKéMON from them will\n"
	.string "riquezas enormes!$"

MtMoon_B2F_Text_Grunt1Defeat::
	.string "¡Urgh!\n"
	.string "Now I'm mad!$"

MtMoon_B2F_Text_Grunt1PostBattle::
	.string "Me has enfurecido!\n"
	.string "El EQUIPO ROCKET te excluye!$"

MtMoon_B2F_Text_Grunt2Intro::
	.string "We, TEAM ROCKET, are POKéMON\n"
	.string "gangsters!\l"
	.string "¡Nuestro poder infunde miedo!$"

MtMoon_B2F_Text_Grunt2Defeat::
	.string "¡Lo arruiné!$"

MtMoon_B2F_Text_Grunt2PostBattle::
	.string "Maldición sea!\n"
	.string "¡Mis socios no lo permitirán!$"

MtMoon_B2F_Text_Grunt3Intro::
	.string "¡Estamos en un gran golpe!\n"
	.string "¡Lárgate, niño!$"

MtMoon_B2F_Text_Grunt3Defeat::
	.string "Vaya, eres muy hábil…$"

MtMoon_B2F_Text_Grunt3PostBattle::
	.string "Si encuentras un fósil, dámelo\n"
	.string "¡y vete!$"

MtMoon_B2F_Text_Grunt4Intro::
	.string "Los niños no deberían meterse\n"
	.string "con los adultos!\p"
	.string "¡Podrían ser malas noticias!$"

MtMoon_B2F_Text_Grunt4Defeat::
	.string "I'm steamed!$"

MtMoon_B2F_Text_Grunt4PostBattle::
	.string "POKéMON lived here long before\n"
	.string "people came.$"

MtMoon_B2F_Text_YouWantDomeFossil::
	.string "¿Quieres el FÓSIL DOMO?$"

MtMoon_B2F_Text_YouWantHelixFossil::
	.string "¿Quieres el FÓSIL HÉLIX?$"

MtMoon_B2F_Text_ObtainedHelixFossil::
	.string "¡Obtuviste el FÓSIL HELIX!$"

MtMoon_B2F_Text_ObtainedDomeFossil::
	.string "¡Obtuviste el FÓSIL DOME!$"

