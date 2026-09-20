SSAqua_B1F_hns_MapScripts::
	.byte 0

SSAqua_B1F_EventScript_Trigger::
	lock
	turnobject LOCALID_SSAQUA_B1F_SAILORLOOKING, DIR_EAST
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	msgbox SSAqua_B1F_Text_FastShipOnDutySailor, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkDown1
	waitmovement 0 
	turnobject LOCALID_SSAQUA_B1F_SAILORLOOKING, DIR_SOUTH
	release
	end

SSAqua_B1F_EventScript_SailorLookingForBuddy::
	lock
	faceplayer
	goto_if_set FLAG_HIDE_SSAQUA_SAILOR, SSAqua_B1F_EventScript_SailorLookingFoundBuddy
	msgbox SSAqua_B1F_Text_FastShipOnDutySailor, MSGBOX_DEFAULT
	closemessage
	release
	end

SSAqua_B1F_EventScript_SailorLookingFoundBuddy::
	msgbox SSAqua_B1F_Text_FastShipOnDutySailorThanks, MSGBOX_DEFAULT
	goto_if_lt VAR_SSAQUA_STATE, 5, SSAqua_B1F_EventScript_SailorGirl
	closemessage
	release
	end
SSAqua_B1F_EventScript_SailorGirl::
	msgbox SSAqua_B1F_Text_FastShipOnDutySailorSawGirl, MSGBOX_DEFAULT
	closemessage
	release
	end

SSAqua_B1F_EventScript_SleepySailor::
	msgbox SSAqua_B1F_Text_FastShipOnDutySailorDirections, MSGBOX_NPC
	end

SSAqua_B1F_EventScript_Barfcan::
	msgbox SSAqua_B1F_Text_BarfCan, MSGBOX_SIGN
	end

SSAqua_B1F_Text_BarfCan:
    .string "¡Qué asco!\n"
    .string "¡No debí mirar!$"

SSAqua_B1F_Text_FastShipOnDutySailor:
	.string "Oye, chico. ¿Podrías\n"
	.string "buscar a mi compañero?\p"
	.string "Está perdiendo el tiempo,\n"
	.string "¡ese vago!\p"
	.string "Quiero ir a buscarlo, pero\n"
	.string "estoy de servicio ahora.$"

SSAqua_B1F_Text_FastShipOnDutySailorRefused:
	.string "Vaya...\p"
	.string "El CAPITÁN estará furioso...$"

SSAqua_B1F_Text_FastShipOnDutySailorThanks:
	.string "¡Gracias! Le he regañado\n"
	.string "bien para que deje de holgazanear!$"

SSAqua_B1F_Text_FastShipOnDutySailorSawGirl:
	.string "¿Una niña?\p"
	.string "Creo que la vi pasar por aquí.$"

SSAqua_B1F_Text_FastShipOnDutySailorDirections:
	.string "El comedor está más adelante.\p"
	.string "Las escaleras del final llevan a\n"
	.string "la cabina del CAPITÁN.$"

SSAqua_B1F_EventScript_Jeff::
	trainerbattle_single TRAINER_JEFF_HNS, SSAqua_B1F_Text_SailorJeffSeen, SSAqua_B1F_Text_SailorJeffBeaten
	msgbox SSAqua_B1F_Text_SailorJeffAfter, MSGBOX_AUTOCLOSE
	end

SSAqua_B1F_Text_SailorJeffSeen:
	.string "Nada supera una batalla cuando\n"
	.string "estoy en mi descanso.$"

SSAqua_B1F_Text_SailorJeffBeaten:
	.string "Win or lose, my break's over!$"

SSAqua_B1F_Text_SailorJeffAfter:
	.string "Supongo que no ganaré si no me\n"
	.string "tomo esto en serio.$"

SSAqua_B1F_EventScript_Debra::
	trainerbattle_single TRAINER_DEBRA_HNS, SSAqua_B1F_Text_PicnickerDebraSeen, SSAqua_B1F_Text_PicnickerDebraBeaten
	msgbox SSAqua_B1F_Text_PicnickerDebraAfter, MSGBOX_AUTOCLOSE
	end

SSAqua_B1F_Text_PicnickerDebraSeen:
	.string "I'm so bored. Want to battle?$"

SSAqua_B1F_Text_PicnickerDebraBeaten:
	.string "Yow! You're too strong!$"

SSAqua_B1F_Text_PicnickerDebraAfter:
	.string "Saffron, Celadon... He oído que\n"
	.string "hay muchas ciudades en KANTO.$"

SSAqua_B1F_EventScript_Fritz::
	trainerbattle_single TRAINER_FRITZ_HNS, SSAqua_B1F_Text_JugglerFritzSeen, SSAqua_B1F_Text_JugglerFritzBeaten
	msgbox SSAqua_B1F_Text_JugglerFritzAfter, MSGBOX_AUTOCLOSE
	end

SSAqua_B1F_Text_JugglerFritzSeen:
	.string "Urrf… I'm seasick!$"

SSAqua_B1F_Text_JugglerFritzBeaten:
	.string "I can't move anymore…$"

SSAqua_B1F_Text_JugglerFritzAfter:
	.string "No más barcos para mí.\n"
	.string "La próxima vez,\p"
	.string "iré en el MAGNET TRAIN.$"

SSAqua_B1F_EventScript_Garrett::
	trainerbattle_single TRAINER_GARRETT_HNS, SSAqua_B1F_Text_SailorGarrettSeen, SSAqua_B1F_Text_SailorGarrettBeaten
	msgbox SSAqua_B1F_Text_SailorGarrettAfter, MSGBOX_AUTOCLOSE
	end

SSAqua_B1F_Text_SailorGarrettSeen:
	.string "This is where we sailors work!$"

SSAqua_B1F_Text_SailorGarrettBeaten:
	.string "I lost on my home field…$"

SSAqua_B1F_Text_SailorGarrettAfter:
	.string "Llegan pasajeros distintos\n"
	.string "desde CIUDAD VERMILIAN hasta\p"
	.string "CIUDAD OLIVO.$"

SSAqua_B1F_EventScript_Jonah::
	trainerbattle_single TRAINER_JONAH_HNS, SSAqua_B1F_Text_FisherJonahSeen, SSAqua_B1F_Text_FisherJonahBeaten
	msgbox SSAqua_B1F_Text_FisherJonahAfter, MSGBOX_AUTOCLOSE
	end

SSAqua_B1F_Text_FisherJonahSeen:
	.string "Aunque estemos fuera en el\n"
	.string "mar, ¡no puedo pescar!\p"
	.string "¡Qué aburrimiento! ¡Luchemos!$"

SSAqua_B1F_Text_FisherJonahBeaten:
	.string "I… I'm not bored anymore…$"

SSAqua_B1F_Text_FisherJonahAfter:
	.string "Pienso pescar desde\n"
	.string "el muelle de VERMILION.$"

SSAqua_B1F_EventScript_Wai::
	trainerbattle_single TRAINER_WAI_HNS, SSAqua_B1F_Text_BlackbeltWaiSeen, SSAqua_B1F_Text_BlackbeltWaiBeaten
	msgbox SSAqua_B1F_Text_BlackbeltWaiAfter, MSGBOX_AUTOCLOSE
	end

SSAqua_B1F_Text_BlackbeltWaiSeen:
	.string "Fortalezco mis piernas\n"
	.string "resistiendo\p"
	.string "¡el balanceo del barco!$"

SSAqua_B1F_Text_BlackbeltWaiBeaten:
	.string "Rocked and rolled over!$"

SSAqua_B1F_Text_BlackbeltWaiAfter:
	.string "No hallé al REY KARATE\n"
	.string "en JOHTO.\p"
	.string "Se supone que entrena en\n"
	.string "una cueva en algún lugar.$"

SSAqua_B1F_EventScript_Kenneth::
	trainerbattle_single TRAINER_KENNETH_HNS, SSAqua_B1F_Text_SailorKennethSeen, SSAqua_B1F_Text_SailorKennethBeaten
	msgbox SSAqua_B1F_Text_SailorKennethAfter, MSGBOX_AUTOCLOSE
	end

SSAqua_B1F_Text_SailorKennethSeen:
	.string "¡Soy un marinero!\p"
	.string "Pero entreno POKéMON para\n"
	.string "¡ser el CAMPEÓN!$"

SSAqua_B1F_Text_SailorKennethBeaten:
	.string "My lack of training is obvious…$"

SSAqua_B1F_Text_SailorKennethAfter:
	.string "¡Ocho MEDALLAS! Eso demuestra\n"
	.string "que has vencido a los\p"
	.string "LÍDERES de GIMNASIO.\p"
	.string "¡Con razón eres tan bueno!$"

SSAqua_B1F_EventScript_Shirley::
	trainerbattle_single TRAINER_SHIRLEY_HNS, SSAqua_B1F_Text_TeacherShirleySeen, SSAqua_B1F_Text_TeacherShirleyBeaten
	msgbox SSAqua_B1F_Text_TeacherShirleyAfter, MSGBOX_AUTOCLOSE
	end

SSAqua_B1F_Text_TeacherShirleySeen:
	.string "¡No pongas un dedo sobre mis\n"
	.string "estudiantes!$"

SSAqua_B1F_Text_TeacherShirleyBeaten:
	.string "Aaack!$"

SSAqua_B1F_Text_TeacherShirleyAfter:
	.string "Estamos de excursión en las\n"
	.string "RUINAS fuera de CIUDAD MALVA.$"

SSAqua_B1F_EventScript_Nate::
	trainerbattle_single TRAINER_NATE_HNS, SSAqua_B1F_Text_SchoolboyNateSeen, SSAqua_B1F_Text_SchoolboyNateBeaten
	msgbox SSAqua_B1F_Text_SchoolboyNateAfter, MSGBOX_AUTOCLOSE
	end

SSAqua_B1F_Text_SchoolboyNateSeen:
	.string "Do you know the RUINS OF ALPH?$"

SSAqua_B1F_Text_SchoolboyNateBeaten:
	.string "Yaargh!$"

SSAqua_B1F_Text_SchoolboyNateAfter:
	.string "Las radios captan señales raras\n"
	.string "dentro de las RUINAS.$"

SSAqua_B1F_EventScript_Ricky::
	trainerbattle_single TRAINER_RICKY_HNS, SSAqua_B1F_Text_SchoolboyRickySeen, SSAqua_B1F_Text_SchoolboyRickyBeaten
	msgbox SSAqua_B1F_Text_SchoolboyRickyAfter, MSGBOX_AUTOCLOSE
	end

SSAqua_B1F_Text_SchoolboyRickySeen:
	.string "Hay unos paneles de piedra\n"
	.string "en las RUINAS ALFA.$"

SSAqua_B1F_Text_SchoolboyRickyBeaten:
	.string "I was done in!$"

SSAqua_B1F_Text_SchoolboyRickyAfter:
	.string "Leí que hay cuatro de\n"
	.string "esos paneles de piedra.$"

