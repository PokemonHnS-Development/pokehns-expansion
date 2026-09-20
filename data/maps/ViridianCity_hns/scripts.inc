ViridianCity_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, ViridianCity_EventScript_CityEnter
	map_script MAP_SCRIPT_ON_FRAME_TABLE, ViridianCity_OnFrame
	.byte 0

ViridianCity_EventScript_CityEnter::
	setflag FLAG_VISITED_VIRIDIAN_CITY
	end

ViridianCity_OnFrame::
	map_script_2 VAR_OAK_MT_SILVER_CALL, 1, ViridianCity_EventScript_OakCall
	.2byte 0

ViridianCity_EventScript_OakCall::
	lock
	setspeaker ViridianCity_Text_OakName
	pokenavcall ViridianCity_Text_OakCall
	waitmessage
	delay 30
	setvar VAR_OAK_MT_SILVER_CALL, 2
	release
	end

ViridianCity_Text_OakName:
	.string "OAK$"

ViridianCity_Text_OakCall:
	.string "OAK: ¡Ah, {PLAYER}!\p"
	.string "Ven a verme a mi\n"
	.string "LAB en PUEBLO PALETA\l"
	.string "cuando tengas oportunidad.$"

ViridianCity_EventScript_Gramps::
	lock
	faceplayer
	msgbox ViridianCity_Text_CoffeeGramps_Question, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, ViridianCity_EventScript_GrampsDoubted
	msgbox ViridianCity_Text_CoffeeGramps_Believed, MSGBOX_DEFAULT
	closemessage
	release
	end

ViridianCity_EventScript_GrampsDoubted::
	msgbox ViridianCity_Text_CoffeeGramps_Doubted, MSGBOX_DEFAULT
	closemessage
	release
	end

VirianCity_EventScript_GymGramps::
	goto_if_set FLAG_HIDE_CINNABAR_BLUE, VirianCity_EventScript_GymGrampsBlue
	msgbox ViridianCity_Text_GrampsNearGym, MSGBOX_NPC
	end

VirianCity_EventScript_GymGrampsBlue::
	msgbox ViridianCity_Text_GrampsNearGym_BlueReturned, MSGBOX_NPC
	end

ViridianCity_EventScript_Fisher::
	goto_if_set FLAG_GOT_VIRIDIAN_TM_DREAM_EATER, ViridianCity_EventScript_FisherAfter
	msgbox ViridianCity_Text_DreamEaterFisher, MSGBOX_NPC
	giveitem ITEM_TM_DREAM_EATER
	setflag FLAG_GOT_VIRIDIAN_TM_DREAM_EATER
	end

ViridianCity_EventScript_FisherAfter::
	msgbox ViridianCity_Text_DreamEaterFisher_GotTM, MSGBOX_NPC
	end

ViridianCity_EventScript_Youngster::
	msgbox ViridianCity_Text_Youngster, MSGBOX_NPC
	end

ViridianCity_EventScript_CitySign::
	msgbox ViridianCity_Text_WelcomeSign, MSGBOX_SIGN
	end

ViridianCity_EventScript_CitySign2::
	msgbox ViridianCity_Text_Sign, MSGBOX_SIGN
	end

ViridianCity_EventScript_GymSign::
	msgbox ViridianCity_Text_GymSign, MSGBOX_SIGN
	end

ViridianCity_Text_CoffeeGramps_Question:
	.string "¡Oye, chico! Me acabo de tomar un\n"
	.string "espresso doble, ¡estoy activado!\p"
	.string "Necesito hablar con alguien, ¡así que\n"
	.string "tendrás que ser tú!\p"
	.string "Quizá no lo parezca ahora, pero\n"
	.string "era un experto capturando POKéMON.\p"
	.string "¿Me crees?$"

ViridianCity_Text_CoffeeGramps_Believed:
	.string "Bien, bien. Sí, yo era alguien\n"
	.string "fuera de lo común, deja que te cuente\l"
	.string "eres!$"

ViridianCity_Text_CoffeeGramps_Doubted:
	.string "¿Qué? ¡Pequeño mocoso!\p"
	.string "Si fuera un poco más joven,\n"
	.string "te daría una lección. ¡Humph!$"

ViridianCity_Text_GrampsNearGym:
	.string "Este GIMNASIO no tenía LÍDER\n"
	.string "hasta hace poco.\p"
	.string "Un joven de PALLET se convirtió\n"
	.string "en LÍDER, pero suele estar fuera.$"

ViridianCity_Text_GrampsNearGym_BlueReturned:
	.string "¿Vas a luchar contra el\n"
	.string "LÍDER?\p"
	.string "Buena suerte. La vas a necesitar.$"

ViridianCity_Text_DreamEaterFisherNew:
	.string "...Zzzzz...\p" 
	.string "¡Bostezo!\p"
	.string "I must have dozed off in the sun.\p"
	.string "What? I remind you of somebody?\p"
	.string "I don't know, here, have this.$"


ViridianCity_Text_DreamEaterFisher_GotTM::
	.string "…Zzzzz…$"

ViridianCity_Text_DreamEaterFisher:
	.string "¡Bostezo!\p"
	.string "I must have dozed off in the sun.\p"
	.string "…I had this dream about a DROWZEE\n"
	.string "eating my dream. Weird, huh?\p"
	.string "Huh? What's this?\p"
	.string "Where did this TM come from?\p"
	.string "This is spooky! Here, you can have\n"
	.string "this TM.$"

ViridianCity_Text_DreamEaterFisher_GotDreamEater:
	.string "TM42 contains DREAM EATER…\p"
	.string "…Zzzzz…$"

ViridianCity_Text_Youngster:
	.string "I heard that there are many items\n"
	.string "on the ground in VIRIDIAN FOREST.$"

ViridianCity_Text_Sign:
	.string "CIUDAD VERIDIAN\p"
	.string "El Paraíso Eternamente Verde$"

ViridianCity_Text_GymSign:
	.string "GIMNASIO POKéMON C. VERIDIAN\n"
	.string "LÍDER: …\p"
	.string "El resto del texto es ilegible…$"

ViridianCity_Text_WelcomeSign:
	.string "BIENVENIDO A CIUDAD VERIDIAN,\p"
	.string "LA PUERTA A LA MESETA AÑIL$"

ViridianCity_Text_TrainerHouseSign:
	.string "CASA DEL ENTRENADOR\p"
	.string "Club de Batallas de Top Entrenadores$"
