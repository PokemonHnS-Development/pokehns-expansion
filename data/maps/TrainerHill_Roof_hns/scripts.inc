TrainerHill_Roof_hns_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, TrainerHill_OnResume
	map_script MAP_SCRIPT_ON_FRAME_TABLE, TrainerHill_OnFrame
	map_script MAP_SCRIPT_ON_LOAD, TrainerHill_Roof_hns_OnLoad
	.byte 0

TrainerHill_Roof_hns_OnLoad::
	setflag FLAG_TEMP_HIDE_FOLLOWER
	end

TrainerHill_Roof_hns_EventScript_Owner::
	trainerhill_settrainerflags
	lock
	faceplayer
	trainerhill_getownerstate
	switch VAR_RESULT
	case 0, TrainerHill_Roof_hns_EventScript_Arrived
	case 1, TrainerHill_Roof_hns_EventScript_GivePrize
	case 2, TrainerHill_Roof_hns_EventScript_AlreadyReceivedPrize
TrainerHill_Roof_hns_EventScript_Arrived::
	msgbox TrainerHill_Roof_hns_Text_YouFinallyCameBravo, MSGBOX_DEFAULT
TrainerHill_Roof_hns_EventScript_GivePrize::
	trainerhill_giveprize
	switch VAR_RESULT
	case 0, TrainerHill_Roof_hns_EventScript_ReceivePrize
	case 1, TrainerHill_Roof_hns_EventScript_NoRoomForPrize
	case 2, TrainerHill_Roof_hns_EventScript_CheckFinalTime
TrainerHill_Roof_hns_EventScript_ReceivePrize::
	msgbox TrainerHill_Roof_hns_Text_HaveTheMostMarvelousGift, MSGBOX_DEFAULT
	playfanfare MUS_LEVEL_UP
	message gText_ObtainedTheItem
	waitfanfare
	waitmessage
	goto TrainerHill_Roof_hns_EventScript_CheckFinalTime

TrainerHill_Roof_hns_EventScript_NoRoomForPrize::
	msgbox TrainerHill_Roof_hns_Text_HaveTheMostMarvelousGift, MSGBOX_DEFAULT
	msgbox gText_TheBagIsFull, MSGBOX_DEFAULT
	msgbox TrainerHill_Roof_hns_Text_FullUpBeBackLaterForThis, MSGBOX_DEFAULT
	goto TrainerHill_Roof_hns_EventScript_CheckFinalTime

TrainerHill_Roof_hns_EventScript_CheckFinalTime::
	trainerhill_finaltime
	switch VAR_RESULT
	case 0, TrainerHill_Roof_hns_EventScript_NewRecord
	case 1, TrainerHill_Roof_hns_EventScript_NoNewRecord
	case 2, TrainerHill_Roof_hns_EventScript_EndSpeakToOwner
TrainerHill_Roof_hns_EventScript_NewRecord::
	msgbox TrainerHill_Roof_hns_Text_GotHereMarvelouslyQuickly, MSGBOX_DEFAULT
	goto TrainerHill_Roof_hns_EventScript_EndSpeakToOwner
	end

TrainerHill_Roof_hns_EventScript_NoNewRecord::
	msgbox TrainerHill_Roof_hns_Text_YouWerentVeryQuick, MSGBOX_DEFAULT
	goto TrainerHill_Roof_hns_EventScript_EndSpeakToOwner
	end

TrainerHill_Roof_hns_EventScript_EndSpeakToOwner::
	msgbox TrainerHill_Roof_hns_Text_ArriveZippierNextTime, MSGBOX_DEFAULT
	release
	end

TrainerHill_Roof_hns_EventScript_AlreadyReceivedPrize::
	msgbox TrainerHill_Roof_hns_Text_ArriveZippierNextTime, MSGBOX_DEFAULT
	release
	end

TrainerHill_Roof_hns_Text_YouFinallyCameBravo:
	.string "Hm! Hm!\p"
	.string "¡Al fin viniste!\n"
	.string "¡Sí, ya llegaste!\p"
	.string "¡Espera! ¡No lo digas!\n"
	.string "Sé por qué viniste hasta aquí\l"
	.string "tú solo!\p"
	.string "Querías verme a mí, el dueño\n"
	.string "de la COLINA ENTRENADOR, porque...\p"
	.string "¡Quieres formar un equipo conmigo!\n"
	.string "¡Wa-hoo!\p"
	.string "…Uh?\n"
	.string "¿No es eso?\p"
	.string "En fin, te vi mientras subías.\n"
	.string "¡Combates maravillosos! ¡Bravo!$"

TrainerHill_Roof_hns_Text_HaveTheMostMarvelousGift:
	.string "Para alguien tan maravilloso,\n"
	.string "Tengo el regalo más maravilloso,\l"
	.string "¡y algo de dinero por tu esfuerzo!$"

TrainerHill_Roof_hns_Text_FullUpBeBackLaterForThis:
	.string "¡Oh, no, está lleno de cosas!\n"
	.string "¡Volverás más tarde por esto!$"

TrainerHill_Roof_hns_Text_GotHereMarvelouslyQuickly:
	.string "¡Oh, espera! ¿Acaso llegaste\n"
	.string "aquí sorprendentemente rápido?\p"
	.string "¡Qué espléndido! ¡No hacía falta\n"
	.string "que te apresuraras tanto!\p"
	.string "Es encantador. ¡Actualizaré el\n"
	.string "Tablero de Tiempos en la recepción!$"

TrainerHill_Roof_hns_Text_YouWerentVeryQuick:
	.string "Pero, oh...\n"
	.string "No fuiste muy rápido al llegar.$"

TrainerHill_Roof_hns_Text_ArriveZippierNextTime:
	.string "Quizás me gustaría más que\n"
	.string "llegaras más veloz la próxima vez.\p"
	.string "Entonces, me gustaría formar\n"
	.string "¡un equipo doble contigo!\p"
	.string "¡Hasta que nos veamos, amigo!$"
