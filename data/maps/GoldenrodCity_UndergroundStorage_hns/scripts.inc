GoldenrodCity_UndergroundStorage_hns_MapScripts::
	.byte 0

GoldenrodCity_UndergroundStorage_EventScript_Director::
    lock
    faceplayer
    checkitem ITEM_CARD_KEY
    goto_if_eq VAR_RESULT, TRUE, GoldenrodCity_UndergroundStorage_EventScript_Director2
    msgbox RadioTowerBasement_Text_DirectorIntro, MSGBOX_DEFAULT
    closemessage
    giveitem ITEM_CARD_KEY
    msgbox RadioTowerBasement_Text_DirectorCardKey, MSGBOX_DEFAULT
    closemessage
    release
    end

GoldenrodCity_UndergroundStorage_EventScript_Director2::
    msgbox RadioTowerBasement_Text_DirectorAfter, MSGBOX_DEFAULT
    closemessage
    release
    end

GoldenrodCity_UndergroundStorage_EventScript_Grunt19::
    trainerbattle_single TRAINER_GRUNT_19_HNS, RadioTowerBasement_Text_GruntM24Seen, RadioTowerBasement_Text_GruntM24Beaten
	msgbox RadioTowerBasement_Text_GruntM24After, MSGBOX_AUTOCLOSE
	end

GoldenrodCity_UndergroundStorage_EventScript_Grunt12::
    trainerbattle_single TRAINER_GRUNT_12_HNS, RadioTowerBasement_Text_GruntM14Seen, RadioTowerBasement_Text_GruntM14Beaten
	msgbox RadioTowerBasement_Text_GruntM14After, MSGBOX_AUTOCLOSE
	end

GoldenrodCity_UndergroundStorage_EventScript_Eto::
    trainerbattle_single TRAINER_ETO_3_HNS, RadioTowerBasement_Text_GruntM15Seen, RadioTowerBasement_Text_GruntM15Beaten
	msgbox RadioTowerBasement_Text_GruntM15After, MSGBOX_AUTOCLOSE
	end

GoldenrodCity_UndergroundStorage_EventScript_Item_TM_CALM_MIND::
    finditem ITEM_TM_CALM_MIND
    end

GoldenrodCity_UndergroundStorage_EventScript_Item_UltraBall::
    finditem ITEM_ULTRA_BALL
    end

GoldenrodCity_UndergroundStorage_EventScript_Item_MaxEther::
    finditem ITEM_MAX_ETHER
    end

RadioTowerBasement_Text_GruntM24Seen:
    .string "¿Cómo llegaste hasta aquí?\p"
    .string "Supongo que no hay remedio. Yo\n"
    .string "me encargaré de ti.$"

RadioTowerBasement_Text_GruntM24Beaten:
    .string "Me derrotaron...$"

RadioTowerBasement_Text_GruntM24After:
    .string "EL TEAM ROCKET seguirá, esperando\n"
    .string "el regreso de GIOVANNI.\p"
    .string "Haremos lo que sea necesario.$"

RadioTowerBasement_Text_GruntM14Seen:
    .string "¡No pasarás de aquí!\p"
    .string "No tengo piedad con mis enemigos,\n"
    .string "¡ni siquiera con mocosos!$"

RadioTowerBasement_Text_GruntM14Beaten:
    .string "Maldición!$"

RadioTowerBasement_Text_GruntM14After:
    .string "Perdí...\p"
    .string "¡Perdóneme, GIOVANNI!$"

RadioTowerBasement_Text_GruntM15Seen:
    .string "¡Je-je-je! ¡Mira quién es!\p"
    .string "¿Listo? ¡Ahora soy muy fuerte!$"

RadioTowerBasement_Text_GruntM15Beaten:
    .string "¡Je-je-je! ¡Eres muy bueno!\p"
    .string "Esto del TEAM ROCKET es solo\n"
    .string "un trabajo, pero veo que daña a otros.\p"
    .string "Ya está, me largo.\p"
    .string "Muchas gracias. ¡Lo siento, GIOVANNI!$"

RadioTowerBasement_Text_GruntM15After:
    .string "¡Je-je-je! ¡Fue genial!\n"
    .string "¡Te recordaré!$"

RadioTowerBasement_Text_DirectorIntro:
    .string "DIRECTOR: ¿Quién? ¿Qué? ¿Viniste a\n"
    .string "rescatarme?\p"
    .string "¡Gracias!\p"
    .string "¡La TORRE RADIO!\p"
    .string "¿Qué está pasando ahí?\p"
    .string "¿El TEAM ROCKET lo tomó?\p"
    .string "Toma. Ten esta CARD KEY.$"

RadioTowerBasement_Text_DirectorCardKey:
    .string "DIRECTOR: Úsala para abrir las\n"
    .string "persianas del 3F.$"

RadioTowerBasement_Text_DirectorAfter:
    .string "Te ruego que nos ayudes.\p"
    .string "No sabemos qué harán si\n"
    .string "controlan el transmisor.\p"
    .string "¡Podrían controlar a los\n"
    .string "POKéMON con una señal especial!\p"
    .string "Eres el único al que puedo acudir.\p"
    .string "Por favor, salva la RADIO TOWER...\p"
    .string "¡Y todos los POKéMON del país!$"
