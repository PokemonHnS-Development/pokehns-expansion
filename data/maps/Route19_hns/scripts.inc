Route19_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route19_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route19_OnTransition:
	callnative SetTimeBasedEncounters
	end

Route19_EventScript_Harold::
	trainerbattle_single TRAINER_HAROLD_HNS, Route19_Text_SwimmermHaroldSeen, Route19_Text_SwimmermHaroldBeaten
	msgbox Route19_Text_SwimmermHaroldAfterBattle, MSGBOX_AUTOCLOSE
	end

Route19_EventScript_Tucker::
	trainerbattle_single TRAINER_TUCKER_HNS, Route19_Text_SwimmermTuckerSeen, Route19_Text_SwimmermTuckerBeaten
	msgbox Route19_Text_SwimmermTuckerAfterBattle, MSGBOX_AUTOCLOSE
	end

Route19_EventScript_Dawn::
	trainerbattle_single TRAINER_DAWN_HNS, Route19_Text_SwimmerfDawnSeen, Route19_Text_SwimmerfDawnBeaten
	msgbox Route19_Text_SwimmerfDawnAfterBattle, MSGBOX_AUTOCLOSE
	end

Route19_EventScript_Jerome::
	trainerbattle_single TRAINER_JEROME_HNS, Route19_Text_SwimmermJeromeSeen, Route19_Text_SwimmermJeromeBeaten
	msgbox Route19_Text_SwimmermJeromeAfterBattle, MSGBOX_AUTOCLOSE
	end

Route19_EventScript_Fatman::
	goto_if_unset FLAG_DEFEATED_CINNABAR_ISLAND_GYM, Route19_EventScript_FatmanBefore
	msgbox Route19_Text_Fisher1_RocksCleared, MSGBOX_NPC
	end

Route19_EventScript_FatmanBefore::
	msgbox Route19_Text_Fisher2, MSGBOX_NPC
	end

Route19_EventScript_Sign::
	msgbox Route19_Text_Sign, MSGBOX_SIGN
	end

Route19_EventScript_SwimSign::
	msgbox Route19_Text_CarefulSwimmingSign, MSGBOX_SIGN
	end

CherryGroveCity_EventScript_Kingler::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_KINGLER, CRY_MODE_NORMAL
	msgbox Route19_Text_Kingler, MSGBOX_DEFAULT
	waitmoncry
	release
	end

Route19_EventScript_Fisher::
	goto_if_unset FLAG_DEFEATED_CINNABAR_ISLAND_GYM, Route19_EventScript_FisherBefore
	msgbox Route19_Text_Fisher2_RocksCleared, MSGBOX_NPC
	end

Route19_EventScript_FisherBefore::
	msgbox Route19_Text_FisherBefore, MSGBOX_NPC
	end

Route19_EventScript_Item_Brine::
    finditem ITEM_TM_BRINE
    end

Route19_Text_SwimmermHaroldSeen:
	.string "¿Alguna vez has nadado en el\n"
	.string "mar por la noche?$"

Route19_Text_SwimmermHaroldBeaten:
	.string "Glub…$"

Route19_Text_SwimmermHaroldAfterBattle:
	.string "De noche, el mar se vuelve negro.\n"
	.string "Sientes que te tragará.$"

Route19_Text_SwimmermTuckerSeen:
	.string "Jadeo, jadeo... Solo... un poco...\p"
	.string "más... hasta... FUCHSIA...$"

Route19_Text_SwimmermTuckerBeaten:
	.string "I'm drowning!$"

Route19_Text_SwimmermTuckerAfterBattle:
	.string "Le... pedí a mi novia que nadara\n"
	.string "hasta FUCHSIA... Jadeo...$"

Route19_Text_SwimmerfDawnSeen:
	.string "I'm disgusted by wimpy people!$"

Route19_Text_SwimmerfDawnBeaten:
	.string "I could beat you at swimming…$"

Route19_Text_SwimmerfDawnAfterBattle:
	.string "Es un nado rápido hasta FUCHSIA\n"
	.string "y las ISLAS ESPUMA...\p"
	.string "Cielos, ¡mi novio se cree\n"
	.string "muy hombre! ¡Qué miedoso!$"

Route19_Text_SwimmermJeromeSeen:
	.string "¿Nadar? Soy malísima en eso.\p"
	.string "Solo chapoteo en estas\n"
	.string "aguas poco profundas.$"

Route19_Text_SwimmermJeromeBeaten:
	.string "I thought I could win.$"

Route19_Text_SwimmermJeromeAfterBattle:
	.string "Seré mala nadando, pero\n"
	.string "amo el mar.$"

Route19_Text_Fisher1:
	.string "Lo siento. Este camino está cerrado\n"
	.string "la construcción.\p"
	.string "Si quieres ir a CINNABAR,\n"
	.string "mejor ve al sur de PALLET\n"
	.string "CIUDAD.$"

Route19_Text_Kingler:
	.string "KINGLER: KEEEEEEEEEEEE$"

Route19_Text_Fisher1_RocksCleared:
	.string "I'm all sweaty. Time for a swim!$"

Route19_Text_Fisher2:
	.string "Rayos, un KINGLER está bloqueando\n"
	.string "la playa.$"

Route19_Text_FisherBefore:
	.string "No hay pesca hasta que esos\n"
	.string "KINGLER se vayan.$"

Route19_Text_Fisher2_RocksCleared:
	.string "¡Esos KINGLER al fin se fueron!\p"
	.string "Ahora puedo volver a pescar.$"

Route19_Text_Sign:
	.string "RUTA 19\p"
	.string "CIUDAD FUXIA - ISLAS CANELA$"

Route19_Text_CarefulSwimmingSign:
	.string "Ten cuidado si vas a\n"
	.string "nadando hacia ISLAS ESPUMA.\p"
	.string "POLICÍA DE FUCHSIA$"

