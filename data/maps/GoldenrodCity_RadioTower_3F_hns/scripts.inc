GoldenrodCity_RadioTower_3F_hns_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, GoldenrodCity_RadioTower_3F_OnLoad
	.byte 0

GoldenrodCity_RadioTower_3F_OnLoad::
	call_if_set FLAG_HIDE_RADIOTOWER_GATE, GoldenrodCity_RadioTower_3F_HideGate
	end
	
GoldenrodCity_RadioTower_3F_HideGate::
	setmetatile 25, 8, 0x335, FALSE
	setmetatile 25, 9, 0x335, FALSE

	setmetatile 26, 8, 0X334, FALSE
	setmetatile 26, 9, 0X334, FALSE

	setmetatile 27, 8, 0X334, FALSE
	setmetatile 27, 9, 0X334, FALSE

	setmetatile 28, 8, 0X334, FALSE
	setmetatile 28, 9, 0X334, FALSE

	setmetatile 29, 8, 0X334, FALSE
	setmetatile 29, 9, 0X334, FALSE

	setmetatile 30, 8, 0X334, FALSE
	setmetatile 30, 9, 0X334, FALSE

	setmetatile 31, 8, 0X334, FALSE
	setmetatile 31, 9, 0X334, FALSE
	return


GoldenrodRaidoTower3_EventScript_Grunt6::
	trainerbattle_single TRAINER_GRUNT_6_HNS, GoldenrodCity_RadioTower_3F_Text_GruntM7Seen, GoldenrodCity_RadioTower_3F_Text_GruntM7Beaten
	msgbox GoldenrodCity_RadioTower_3F_Text_GruntM7After, MSGBOX_AUTOCLOSE
	end

GoldenrodRaidoTower3_EventScript_Grunt7::
	trainerbattle_single TRAINER_GRUNT_7_HNS, GoldenrodCity_RadioTower_3F_Text_GruntM8Seen, GoldenrodCity_RadioTower_3F_Text_GruntM8Beaten
	msgbox GoldenrodCity_RadioTower_3F_Text_GruntM8After, MSGBOX_AUTOCLOSE
	end

GoldenrodRaidoTower3_EventScript_Grunt8::
	trainerbattle_single TRAINER_GRUNT_8_HNS, GoldenrodCity_RadioTower_3F_Text_GruntM9Seen, GoldenrodCity_RadioTower_3F_Text_GruntM9Beaten
	msgbox GoldenrodCity_RadioTower_3F_Text_GruntM9After, MSGBOX_AUTOCLOSE
	end

GoldenrodRaidoTower3_EventScript_Scientist::
	trainerbattle_single TRAINER_MARC_HNS, GoldenrodCity_RadioTower_3F_Text_ScientistMarcSeen, GoldenrodCity_RadioTower_3F_Text_ScientistMarcBeaten
	msgbox GoldenrodCity_RadioTower_3F_Text_ScientistMarcAfter, MSGBOX_AUTOCLOSE
	end


GoldenrodCity_RadioTower_3F_EventScript_Cooltrainer::
	lock
	faceplayer
	goto_if_set FLAG_GOT_SUNNY_DAY, GoldenrodCity_RadioTower_3F_EventScript_Cooltrainer3
	goto_if_ge VAR_GOLDENROD_CITY_STATE, 10, GoldenrodCity_RadioTower_3F_EventScript_Cooltrainer2

	msgbox GoldenrodCity_RadioTower_3F_Text_CooltrainerFPleaseSave, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_RadioTower_3F_EventScript_Cooltrainer2::
	lock
	faceplayer
	msgbox GoldenrodCity_RadioTower_3F_Text_CooltrainerFHeroGift, MSGBOX_DEFAULT
	closemessage
	giveitem ITEM_TM_SUNNY_DAY
	setflag FLAG_GOT_SUNNY_DAY
	msgbox GoldenrodCity_RadioTower_3F_Text_CooltrainerFSunnyDay, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_RadioTower_3F_EventScript_Cooltrainer3::
	msgbox GoldenrodCity_RadioTower_3F_Text_CooltrainerFMarvelous, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_RadioTower_3F_EventScript_Nerd::
	lock
	faceplayer
	msgbox GoldenrodCity_RadioTower_3F_Text_SuperNerd, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_RadioTower_3F_EventScript_Gate::
	lock
	msgbox GoldenrodCity_RadioTower_3F_Text_CardKeySlot, MSGBOX_SIGN
	goto_if_set FLAG_HIDE_RADIOTOWER_GATE, GoldenrodCity_RadioTower_3F_EventScript_GateOpened
	checkitem ITEM_CARD_KEY
	goto_if_eq VAR_RESULT, TRUE, GoldenrodCity_RadioTower_3F_EventScript_OpenGate
	closemessage
	release
	end


GoldenrodCity_RadioTower_3F_EventScript_GateOpened::
	msgbox GoldenrodCity_RadioTower_3F_Text_Open, MSGBOX_SIGN
	closemessage
	release
	end

GoldenrodCity_RadioTower_3F_EventScript_OpenGate::
	msgbox GoldenrodCity_RadioTower_3F_Text_InsertedCardKey, MSGBOX_SIGN
	call GoldenrodCity_RadioTower_3F_HideGate
	playse SE_CLICK
	special DrawWholeMapView
	msgbox GoldenrodCity_RadioTower_3F_Text_Open, MSGBOX_SIGN
	setflag FLAG_HIDE_RADIOTOWER_GATE
	closemessage
	release
	end

GoldenrodCity_RadioTower_3F_EventScript_Sign1::
	lock
	msgbox GoldenrodCity_RadioTower_3F_Text_PersonnelSign, MSGBOX_SIGN
	closemessage
	release
	end

GoldenrodCity_RadioTower_3F_EventScript_Sign2::
	lock
	msgbox GoldenrodCity_RadioTower_3F_Text_PokemonMusicSign, MSGBOX_SIGN
	closemessage
	release
	end

GoldenrodCity_RadioTower_3F_Text_CardKeySlot:
	.string "Es la ranura de LLAVE MAGNÉTICA.$"

GoldenrodCity_RadioTower_3F_Text_InsertedCardKey:
	.string "{PLAYER} inserted the CARD KEY.$"
 
GoldenrodCity_RadioTower_3F_Text_Open:
	.string "La reja está abierta.$"

GoldenrodCity_RadioTower_3F_Text_PersonnelSign:
	.string "3F PERSONNEL$"

GoldenrodCity_RadioTower_3F_Text_PokemonMusicSign:
	.string "POKéMON MUSIC with Host DJ BEN$"

GoldenrodCity_RadioTower_3F_Text_SuperNerd:
	.string "Tenemos grabaciones de los gritos\n"
	.string "de todos los POKéMON que han sido\l"
	.string "encontrados.\p"
	.string "Debemos tener unas 400 especies.$"

GoldenrodCity_RadioTower_3F_Text_GymGuideRockets:
	.string "Para los ENTRENADORES, los POKéMON\n"
	.string "son sus queridos compañeros.\p"
	.string "Es terrible cómo el TEAM ROCKET\n"
	.string "intenta controlar a los POKéMON.$"

GoldenrodCity_RadioTower_3F_Text_GymGuide:
	.string "Transmitimos las 24 horas del día\n"
	.string "programas entretenidos.\p"
	.string "¡Yo también me esforzaré al\n"
	.string "máximo todo el día!$"

GoldenrodCity_RadioTower_3F_Text_CooltrainerFPleaseSave:
	.string "El jefe del TEAM ROCKET se ha\n"
	.string "encerrado allí.\p"
	.string "Pero el DIRECTOR puede abrirlo.\p"
	.string "Está en el quinto piso.\p"
	.string "¡Por favor, sálvalo!$"

GoldenrodCity_RadioTower_3F_Text_CooltrainerFDirectorSafe:
	.string "¿El DIRECTOR está a salvo?$"

GoldenrodCity_RadioTower_3F_Text_CooltrainerFHeroGift:
	.string "¡Gracias! ¡Eres mi héroe!\p"
	.string "Toma esto como muestra de gratitud.$"

GoldenrodCity_RadioTower_3F_Text_CooltrainerFSunnyDay:
	.string "Es un DÍA SOLEADO.\p"
	.string "Potencia los movimientos de tipo\n"
	.string "fuego por un tiempo.$"

GoldenrodCity_RadioTower_3F_Text_CooltrainerFMarvelous:
	.string "¡Estuviste simplemente increíble!$"

GoldenrodCity_RadioTower_3F_Text_GruntM7Seen:
	.string "Recibí órdenes muy estrictas.\p"
	.string "Debo aplastar a quien me desafíe\n"
	.string "TEAM ROCKET!$"

GoldenrodCity_RadioTower_3F_Text_GruntM7Beaten:
	.string "What?!$"

GoldenrodCity_RadioTower_3F_Text_GruntM7After:
	.string "Fallé en mis deberes...\p"
	.string "ARCHER estará muy molesto...$"

GoldenrodCity_RadioTower_3F_Text_GruntM8Seen:
	.string "Es genial ordenar a los POKéMON\n"
	.string "que cometan crímenes.$"

GoldenrodCity_RadioTower_3F_Text_GruntM8Beaten:
	.string "You're kidding!$"

GoldenrodCity_RadioTower_3F_Text_GruntM8After:
	.string "¡Me siento fatal por perder!\p"
	.string "¡Rayos! ¡Odio los POKéMON inútiles!$"

GoldenrodCity_RadioTower_3F_Text_GruntM9Seen:
	.string "¿Por qué se abrió la persiana? ¿Tú\n"
	.string "algo que ver con esto?$"

GoldenrodCity_RadioTower_3F_Text_GruntM9Beaten:
	.string "I'm done for!$"

GoldenrodCity_RadioTower_3F_Text_GruntM9After:
	.string "¿¡Qué!? ¿Pasaste a nuestros hombres\n"
	.string "del SUBTERRÁNEO?\p"
	.string "¿Cómo pudiste?$"

GoldenrodCity_RadioTower_3F_Text_ScientistMarcSeen:
	.string "¿Un niño desconocido por aquí?\p"
	.string "¿Quién eres?$"

GoldenrodCity_RadioTower_3F_Text_ScientistMarcBeaten:
	.string "Tch! I took you too lightly!$"

GoldenrodCity_RadioTower_3F_Text_ScientistMarcAfter:
	.string "Bwahahaha…\p"
	.string "Puedo transmitir una señal tan fuerte\n"
	.string "como necesite desde aquí.$"

