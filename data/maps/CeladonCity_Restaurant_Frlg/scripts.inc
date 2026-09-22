CeladonCity_Restaurant_Frlg_MapScripts::
	.byte 0

CeladonCity_Restaurant_EventScript_Chef::
	msgbox CeladonCity_Restaurant_Text_TakingBreakRightNow, MSGBOX_NPC
	end

CeladonCity_Restaurant_EventScript_Woman::
	msgbox CeladonCity_Restaurant_Text_OftenGoToDrugstore, MSGBOX_NPC
	end

CeladonCity_Restaurant_EventScript_CoinCaseMan::
	lock
	faceplayer
	goto_if_set FLAG_GOT_COIN_CASE, CeladonCity_Restaurant_EventScript_AlreadyGotCoinCase
	msgbox CeladonCity_Restaurant_Text_TakeThisImBusted
	checkitemspace ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, CeladonCity_Restaurant_EventScript_NoRoomForCoinCase
	giveitem_msg CeladonCity_Restaurant_Text_ReceivedCoinCaseFromMan, ITEM_COIN_CASE
	setflag FLAG_GOT_COIN_CASE
	release
	end

CeladonCity_Restaurant_EventScript_NoRoomForCoinCase::
	msgbox CeladonCity_Restaurant_Text_MakeRoomForThis
	release
	end

CeladonCity_Restaurant_EventScript_AlreadyGotCoinCase::
	msgbox CeladonCity_Restaurant_Text_ThoughtIdWinItBack
	release
	end

CeladonCity_Restaurant_EventScript_WorkerM::
	msgbox CeladonCity_Restaurant_Text_PsstBasementUnderGameCorner, MSGBOX_NPC
	end

CeladonCity_Restaurant_EventScript_FatMan::
	msgbox CeladonCity_Restaurant_Text_ManLostItAllAtSlots, MSGBOX_NPC
	end

CeladonCity_Restaurant_Text_TakingBreakRightNow::
	.string "Hi!\p"
	.string "Lo siento, pero estamos tomando un descanso\n"
	.string "en este momento.$"

CeladonCity_Restaurant_Text_OftenGoToDrugstore::
	.string "My POKéMON are weak, so I often\n"
	.string "Tengo que ir a la FARMACIA.$"

CeladonCity_Restaurant_Text_PsstBasementUnderGameCorner::
	.string "¡Pst! Hay un sótano debajo del\n"
	.string "GAME CORNER, I hear.$"

CeladonCity_Restaurant_Text_ManLostItAllAtSlots::
	.string "Munch...\p"
	.string "El hombre de esa mesa lo perdió todo\n"
	.string "en las tragamonedas.$"

CeladonCity_Restaurant_Text_TakeThisImBusted::
	.string "¡Adelante! ¡Ríete!\n"
	.string "I'm flat-out busted!\p"
	.string "¡Ya no me quedan espacios!\n"
	.string "I'm going straight!\p"
	.string "¡Toma!\n"
	.string "¡Ya no necesitaré esto!$"

CeladonCity_Restaurant_Text_ReceivedCoinCaseFromMan::
	.string "{PLAYER} recibió un Estuche Moneda\n"
	.string "del hombre.$"

CeladonCity_Restaurant_Text_MakeRoomForThis::
	.string "¡Haz espacio para esto!$"

CeladonCity_Restaurant_Text_ThoughtIdWinItBack::
	.string "Siempre pensé que iba a\n"
	.string "Recupéralo...$"

