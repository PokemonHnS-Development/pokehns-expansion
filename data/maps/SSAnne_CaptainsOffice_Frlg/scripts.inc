SSAnne_CaptainsOffice_Frlg_MapScripts::
	.byte 0

SSAnne_CaptainsOffice_EventScript_Captain::
	lock
	goto_if_set FLAG_GOT_HM01, SSAnne_CaptainsOffice_EventScript_AlreadyGotCut
	msgbox SSAnne_CaptainsOffice_Text_CaptainIFeelSeasick
	textcolor NPC_TEXT_COLOR_NEUTRAL
	message SSAnne_CaptainsOffice_Text_RubbedCaptainsBack
	waitmessage
	playfanfare MUS_HEAL
	waitfanfare
	call EventScript_RestorePrevTextColor
	delay 50
	applymovement LOCALID_SS_ANNE_CAPTAIN, Common_Movement_FacePlayer
	waitmovement 0
	msgbox SSAnne_CaptainsOffice_Text_ThankYouHaveHMForCut
	giveitem_msg SSAnne_CaptainsOffice_Text_ObtainedHM01FromCaptain, ITEM_HM01, 1, MUS_RG_OBTAIN_KEY_ITEM
	msgbox SSAnne_CaptainsOffice_Text_ExplainCut
	setflag FLAG_GOT_HM01
	setvar VAR_MAP_SCENE_VERMILION_CITY, 1
	release
	end

@ Unused
SSAnne_CaptainsOffice_EventScript_NoRoomForCut::
	msgbox SSAnne_CaptainsOffice_Text_YouHaveNoRoomForThis
	closemessage
	applymovement LOCALID_SS_ANNE_CAPTAIN, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

SSAnne_CaptainsOffice_EventScript_AlreadyGotCut::
	applymovement LOCALID_SS_ANNE_CAPTAIN, Common_Movement_FacePlayer
	waitmovement 0
	msgbox SSAnne_CaptainsOffice_Text_SSAnneWillSetSailSoon
	release
	end

SSAnne_CaptainsOffice_EventScript_TrashCan::
	msgbox SSAnne_CaptainsOffice_Text_YuckShouldntHaveLooked, MSGBOX_SIGN
	end

SSAnne_CaptainsOffice_EventScript_Book::
	msgbox SSAnne_CaptainsOffice_Text_HowToConquerSeasickness, MSGBOX_SIGN
	end

SSAnne_CaptainsOffice_Text_CaptainIFeelSeasick::
	.string "CAPITÁN: Ooargh...\n"
	.string "Me siento fatal...\l"
	.string "¡Urrp! Mareo...$"

SSAnne_CaptainsOffice_Text_RubbedCaptainsBack::
	.string "{PLAYER} le frotó la espalda\n"
	.string "al CAPITÁN!\p"
	.string "Frota-frota...\n"
	.string "Frota-frota...$"

SSAnne_CaptainsOffice_Text_ThankYouHaveHMForCut::
	.string "CAPITÁN: ¡Uf! ¡Gracias!\n"
	.string "Ahora me siento mucho mejor.\p"
	.string "¿Quieres ver mi técnica de\n"
	.string "CORTE secreta?\p"
	.string "Podría mostrarte mi preciada\n"
	.string "técnica si no estuviera tan enfermo...\p"
	.string "¡Ya sé! ¡Puedes tener esto!\n"
	.string "¡Esta MÁQUINA OCULTA!\p"
	.string "¡Enséñale CORTE a tus POKéMON y\n"
	.string "podrás cortar cuando quieras!$"

SSAnne_CaptainsOffice_Text_ObtainedHM01FromCaptain::
	.string "{PLAYER} obtuvo HM01\n"
	.string "¡del CAPITÁN!$"

SSAnne_CaptainsOffice_Text_ExplainCut::
	.string "Con CORTE puedes talar los\n"
	.string "árboles pequeños.\p"
	.string "¿Por qué no probarlo con los árboles\n"
	.string "de los alrededores de VERMILION?$"

SSAnne_CaptainsOffice_Text_SSAnneWillSetSailSoon::
	.string "CAPITÁN: ...¡Uf!\p"
	.string "Ahora que ya no estoy enfermo,\n"
	.string "creo que es el momento.\p"
	.string "¡El S.S. ANNE zarpará pronto!\p"
	.string "Adiós, hasta que volvamos a\n"
	.string "¡VERMILION!$"

SSAnne_CaptainsOffice_Text_YouHaveNoRoomForThis::
	.string "¡Oh, no!\n"
	.string "¡No tienes espacio para esto!$"

SSAnne_CaptainsOffice_Text_YuckShouldntHaveLooked::
	.string "¡Qué asco!\n"
	.string "¡No debí mirar!$"

SSAnne_CaptainsOffice_Text_HowToConquerSeasickness::
	.string "Cómo vencer el mareo...\n"
	.string "¡Lo lee el CAPITÁN!$"

