RuinsOfAlph_Lab_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, RuinsOfAlph_Lab_OnTransition
	.byte 0

RuinsOfAlph_Lab_OnTransition:
	call_if_eq VAR_FOSSIL_RESURRECTION_STATE, 1, RustboroCity_DevonCorp_2F_EventScript_SetFossilReady
	end

RuinsOfAlph_Lab_EventScript_Scientist1::
	lock
	faceplayer
	msgbox RuinsOfAlph_Lab_Text_Scientist1, MSGBOX_DEFAULT
	release
	end
RuinsOfAlph_Lab_EventScript_Scientist2::
	lock
	faceplayer
	msgbox RuinsOfAlph_Lab_Text_Scientist2, MSGBOX_DEFAULT
	release
	end
RuinsOfAlph_Lab_EventScript_Fossils::
	lock
	msgbox RuinsOfAlph_Lab_Text_Fossils, MSGBOX_DEFAULT
	closemessage
	release
	end

RuinsOfAlph_Lab_Text_Scientist1:
	.string "Las RUINAS tienen unos 1500 años.\p"
	.string "Pero no se sabe por qué fueron\n"
	.string "construidas, ni por quién.$"

RuinsOfAlph_Lab_Text_Scientist2:
	.string "Hay patrones extraños dibujados\n"
	.string "en los muros de las RUINAS.\p"
	.string "Deben ser las claves para\n"
	.string "resolver el misterio de las RUINAS.$"

RuinsOfAlph_Lab_Text_Fossils:
	.string "Fósiles hallados en las RUINAS.\n"
	.string "Quizás haya más en algún lugar...$"


RuinsOfAlph_Lab_EventScript_FossilScientist::
	lock
	faceplayer
	goto_if_eq VAR_FOSSIL_RESURRECTION_STATE, 2, RuinsOfAlph_Lab_EventScript_FossilMonReady
	goto_if_eq VAR_FOSSIL_RESURRECTION_STATE, 1, RuinsOfAlph_Lab_EventScript_StillRegenerating
	msgbox RuinsOfAlph_Lab_Text_DevelopDeviceToResurrectFossils, MSGBOX_DEFAULT
	checkitem ITEM_ROOT_FOSSIL
	goto_if_eq VAR_RESULT, TRUE, RuinsOfAlph_Lab_EventScript_NoticeRootFossil
	checkitem ITEM_CLAW_FOSSIL
	goto_if_eq VAR_RESULT, TRUE, RuinsOfAlph_Lab_EventScript_NoticeClawFossil
	checkitem ITEM_HELIX_FOSSIL
	goto_if_eq VAR_RESULT, TRUE, RuinsOfAlph_Lab_EventScript_NoticeHelixFossil
	checkitem ITEM_DOME_FOSSIL
	goto_if_eq VAR_RESULT, TRUE, RuinsOfAlph_Lab_EventScript_NoticeDomeFossil
	checkitem ITEM_OLD_AMBER
	goto_if_eq VAR_RESULT, TRUE, RuinsOfAlph_Lab_EventScript_NoticeOldAmber
	release
	end

@ This whole section has needless duplication and could be condensed considerably
RuinsOfAlph_Lab_EventScript_NoticeRootFossil::
	closemessage
	playse SE_PIN
	applymovement LOCALID_RUINS_FOSSIL_SCIENTIST, Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_RUINS_FOSSIL_SCIENTIST
	applymovement LOCALID_RUINS_FOSSIL_SCIENTIST, Common_Movement_Delay48
	waitmovement 0
	msgbox RuinsOfAlph_Lab_Text_WantToBringFossilBackToLife, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RuinsOfAlph_Lab_EventScript_DeclineGiveFossil
	checkitem ITEM_CLAW_FOSSIL
	goto_if_eq VAR_RESULT, TRUE, RuinsOfAlph_Lab_EventScript_ChooseFossil
	checkitem ITEM_HELIX_FOSSIL
	goto_if_eq VAR_RESULT, TRUE, RuinsOfAlph_Lab_EventScript_ChooseFossil
	checkitem ITEM_DOME_FOSSIL
	goto_if_eq VAR_RESULT, TRUE, RuinsOfAlph_Lab_EventScript_ChooseFossil
	checkitem ITEM_OLD_AMBER
	goto_if_eq VAR_RESULT, TRUE, RuinsOfAlph_Lab_EventScript_ChooseFossil
	goto RuinsOfAlph_Lab_EventScript_GiveRootFossil
	end

RuinsOfAlph_Lab_EventScript_GiveRootFossil::
	bufferitemname STR_VAR_1, ITEM_ROOT_FOSSIL
	msgbox RuinsOfAlph_Lab_Text_HandedFossilToResearcher, MSGBOX_DEFAULT
	removeitem ITEM_ROOT_FOSSIL
	setvar VAR_FOSSIL_RESURRECTION_STATE, 1
	setvar VAR_WHICH_FOSSIL_REVIVED, 1
	release
	end

RuinsOfAlph_Lab_EventScript_NoticeClawFossil::
	closemessage
	playse SE_PIN
	applymovement LOCALID_RUINS_FOSSIL_SCIENTIST, Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_RUINS_FOSSIL_SCIENTIST
	applymovement LOCALID_RUINS_FOSSIL_SCIENTIST, Common_Movement_Delay48
	waitmovement 0
	msgbox RuinsOfAlph_Lab_Text_WantToBringFossilBackToLife, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RuinsOfAlph_Lab_EventScript_DeclineGiveFossil
	checkitem ITEM_ROOT_FOSSIL
	goto_if_eq VAR_RESULT, TRUE, RuinsOfAlph_Lab_EventScript_ChooseFossil
	checkitem ITEM_HELIX_FOSSIL
	goto_if_eq VAR_RESULT, TRUE, RuinsOfAlph_Lab_EventScript_ChooseFossil
	checkitem ITEM_DOME_FOSSIL
	goto_if_eq VAR_RESULT, TRUE, RuinsOfAlph_Lab_EventScript_ChooseFossil
	checkitem ITEM_OLD_AMBER
	goto_if_eq VAR_RESULT, TRUE, RuinsOfAlph_Lab_EventScript_ChooseFossil
	goto RuinsOfAlph_Lab_EventScript_GiveClawFossil
	end

RuinsOfAlph_Lab_EventScript_GiveClawFossil::
	bufferitemname STR_VAR_1, ITEM_CLAW_FOSSIL
	msgbox RuinsOfAlph_Lab_Text_HandedFossilToResearcher, MSGBOX_DEFAULT
	removeitem ITEM_CLAW_FOSSIL
	setvar VAR_FOSSIL_RESURRECTION_STATE, 1
	setvar VAR_WHICH_FOSSIL_REVIVED, 2
	release
	end

RuinsOfAlph_Lab_EventScript_NoticeHelixFossil::
	closemessage
	playse SE_PIN
	applymovement LOCALID_RUINS_FOSSIL_SCIENTIST, Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_RUINS_FOSSIL_SCIENTIST
	applymovement LOCALID_RUINS_FOSSIL_SCIENTIST, Common_Movement_Delay48
	waitmovement 0
	msgbox RuinsOfAlph_Lab_Text_WantToBringFossilBackToLife, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RuinsOfAlph_Lab_EventScript_DeclineGiveFossil
	checkitem ITEM_ROOT_FOSSIL
	goto_if_eq VAR_RESULT, TRUE, RuinsOfAlph_Lab_EventScript_ChooseFossil
	checkitem ITEM_CLAW_FOSSIL
	goto_if_eq VAR_RESULT, TRUE, RuinsOfAlph_Lab_EventScript_ChooseFossil
	checkitem ITEM_DOME_FOSSIL
	goto_if_eq VAR_RESULT, TRUE, RuinsOfAlph_Lab_EventScript_ChooseFossil
	checkitem ITEM_OLD_AMBER
	goto_if_eq VAR_RESULT, TRUE, RuinsOfAlph_Lab_EventScript_ChooseFossil
	goto RuinsOfAlph_Lab_EventScript_GiveHelixFossil
	end

RuinsOfAlph_Lab_EventScript_GiveHelixFossil::
	bufferitemname STR_VAR_1, ITEM_HELIX_FOSSIL
	msgbox RuinsOfAlph_Lab_Text_HandedFossilToResearcher, MSGBOX_DEFAULT
	removeitem ITEM_HELIX_FOSSIL
	setvar VAR_FOSSIL_RESURRECTION_STATE, 1
	setvar VAR_WHICH_FOSSIL_REVIVED, 3
	release
	end

RuinsOfAlph_Lab_EventScript_NoticeDomeFossil::
	closemessage
	playse SE_PIN
	applymovement LOCALID_RUINS_FOSSIL_SCIENTIST, Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_RUINS_FOSSIL_SCIENTIST
	applymovement LOCALID_RUINS_FOSSIL_SCIENTIST, Common_Movement_Delay48
	waitmovement 0
	msgbox RuinsOfAlph_Lab_Text_WantToBringFossilBackToLife, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RuinsOfAlph_Lab_EventScript_DeclineGiveFossil
	checkitem ITEM_ROOT_FOSSIL
	goto_if_eq VAR_RESULT, TRUE, RuinsOfAlph_Lab_EventScript_ChooseFossil
	checkitem ITEM_CLAW_FOSSIL
	goto_if_eq VAR_RESULT, TRUE, RuinsOfAlph_Lab_EventScript_ChooseFossil
	checkitem ITEM_HELIX_FOSSIL
	goto_if_eq VAR_RESULT, TRUE, RuinsOfAlph_Lab_EventScript_ChooseFossil
	checkitem ITEM_OLD_AMBER
	goto_if_eq VAR_RESULT, TRUE, RuinsOfAlph_Lab_EventScript_ChooseFossil
	goto RuinsOfAlph_Lab_EventScript_GiveDomeFossil
	end

RuinsOfAlph_Lab_EventScript_GiveDomeFossil::
	bufferitemname STR_VAR_1, ITEM_DOME_FOSSIL
	msgbox RuinsOfAlph_Lab_Text_HandedFossilToResearcher, MSGBOX_DEFAULT
	removeitem ITEM_DOME_FOSSIL
	setvar VAR_FOSSIL_RESURRECTION_STATE, 1
	setvar VAR_WHICH_FOSSIL_REVIVED, 4
	release
	end

RuinsOfAlph_Lab_EventScript_NoticeOldAmber::
	closemessage
	playse SE_PIN
	applymovement LOCALID_RUINS_FOSSIL_SCIENTIST, Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_RUINS_FOSSIL_SCIENTIST
	applymovement LOCALID_RUINS_FOSSIL_SCIENTIST, Common_Movement_Delay48
	waitmovement 0
	msgbox RuinsOfAlph_Lab_Text_WantToBringFossilBackToLife, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RuinsOfAlph_Lab_EventScript_DeclineGiveFossil
	checkitem ITEM_ROOT_FOSSIL
	goto_if_eq VAR_RESULT, TRUE, RuinsOfAlph_Lab_EventScript_ChooseFossil
	checkitem ITEM_CLAW_FOSSIL
	goto_if_eq VAR_RESULT, TRUE, RuinsOfAlph_Lab_EventScript_ChooseFossil
	checkitem ITEM_HELIX_FOSSIL
	goto_if_eq VAR_RESULT, TRUE, RuinsOfAlph_Lab_EventScript_ChooseFossil
	checkitem ITEM_DOME_FOSSIL
	goto_if_eq VAR_RESULT, TRUE, RuinsOfAlph_Lab_EventScript_ChooseFossil
	goto RuinsOfAlph_Lab_EventScript_GiveOldAmber
	end

RuinsOfAlph_Lab_EventScript_GiveOldAmber::
	bufferitemname STR_VAR_1, ITEM_OLD_AMBER
	msgbox RuinsOfAlph_Lab_Text_HandedFossilToResearcher, MSGBOX_DEFAULT
	removeitem ITEM_OLD_AMBER
	setvar VAR_FOSSIL_RESURRECTION_STATE, 1
	setvar VAR_WHICH_FOSSIL_REVIVED, 5
	release
	end

RuinsOfAlph_Lab_EventScript_DeclineGiveFossil::
	msgbox RuinsOfAlph_Lab_Text_OhIsThatSo, MSGBOX_DEFAULT
	release
	end

RuinsOfAlph_Lab_EventScript_DeclineGiveFossil2::
	msgbox RuinsOfAlph_Lab_Text_OhIsThatSo2, MSGBOX_DEFAULT
	release
	end

RuinsOfAlph_Lab_EventScript_StillRegenerating::
	msgbox RuinsOfAlph_Lab_Text_FossilRegeneratorTakesTime, MSGBOX_DEFAULT
	release
	end

RuinsOfAlph_Lab_EventScript_FossilMonReady::
	goto_if_eq VAR_WHICH_FOSSIL_REVIVED, 1, RuinsOfAlph_Lab_EventScript_LileepReady
	goto_if_eq VAR_WHICH_FOSSIL_REVIVED, 2, RuinsOfAlph_Lab_EventScript_AnorithReady
	goto_if_eq VAR_WHICH_FOSSIL_REVIVED, 3, RuinsOfAlph_Lab_EventScript_OmanyteReady
	goto_if_eq VAR_WHICH_FOSSIL_REVIVED, 4, RuinsOfAlph_Lab_EventScript_KabutoReady
	goto_if_eq VAR_WHICH_FOSSIL_REVIVED, 5, RuinsOfAlph_Lab_EventScript_AeroReady
	end

RuinsOfAlph_Lab_EventScript_LileepReady::
	bufferspeciesname STR_VAR_2, SPECIES_LILEEP
	msgbox RuinsOfAlph_Lab_Text_FossilizedMonBroughtBackToLife, MSGBOX_DEFAULT
	goto RuinsOfAlph_Lab_EventScript_ReceiveLileep
	end

RuinsOfAlph_Lab_EventScript_AnorithReady::
	bufferspeciesname STR_VAR_2, SPECIES_ANORITH
	msgbox RuinsOfAlph_Lab_Text_FossilizedMonBroughtBackToLife, MSGBOX_DEFAULT
	goto RuinsOfAlph_Lab_EventScript_ReceiveAnorith
	end

RuinsOfAlph_Lab_EventScript_OmanyteReady::
	bufferspeciesname STR_VAR_2, SPECIES_OMANYTE
	msgbox RuinsOfAlph_Lab_Text_FossilizedMonBroughtBackToLife, MSGBOX_DEFAULT
	goto RuinsOfAlph_Lab_EventScript_ReceiveOmanyte
	end

RuinsOfAlph_Lab_EventScript_KabutoReady::
	bufferspeciesname STR_VAR_2, SPECIES_KABUTO
	msgbox RuinsOfAlph_Lab_Text_FossilizedMonBroughtBackToLife, MSGBOX_DEFAULT
	goto RuinsOfAlph_Lab_EventScript_ReceiveKabuto
	end

RuinsOfAlph_Lab_EventScript_AeroReady::
	bufferspeciesname STR_VAR_2, SPECIES_AERODACTYL
	msgbox RuinsOfAlph_Lab_Text_FossilizedMonBroughtBackToLife, MSGBOX_DEFAULT
	goto RuinsOfAlph_Lab_EventScript_ReceiveAero
	end

RuinsOfAlph_Lab_EventScript_ReceiveLileep::
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_LILEEP
	givemon SPECIES_LILEEP, 20
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, RuinsOfAlph_Lab_EventScript_ReceiveLileepParty
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, RuinsOfAlph_Lab_EventScript_ReceiveLileepPC
	goto Common_EventScript_NoMoreRoomForPokemon
	end

RuinsOfAlph_Lab_EventScript_ReceiveLileepParty::
	call RuinsOfAlph_Lab_EventScript_ReceivedLileepFanfare
	specialvar VAR_RESULT, IsNuzlockeNicknamingActive
	goto_if_eq VAR_RESULT, TRUE, RuinsOfAlph_Lab_EventScript_ReceiveLileepParty_Nuzlocke
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RuinsOfAlph_Lab_EventScript_FinishReceivingLileep
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto RuinsOfAlph_Lab_EventScript_FinishReceivingLileep
	end

RuinsOfAlph_Lab_EventScript_ReceiveLileepParty_Nuzlocke::
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto RuinsOfAlph_Lab_EventScript_FinishReceivingLileep
	end

RuinsOfAlph_Lab_EventScript_ReceiveLileepPC::
	call RuinsOfAlph_Lab_EventScript_ReceivedLileepFanfare
	specialvar VAR_RESULT, IsNuzlockeNicknamingActive
	goto_if_eq VAR_RESULT, TRUE, RuinsOfAlph_Lab_EventScript_ReceiveLileepPC_Nuzlocke
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RuinsOfAlph_Lab_EventScript_TransferLileepToPC
	call Common_EventScript_NameReceivedBoxMon
	goto RuinsOfAlph_Lab_EventScript_TransferLileepToPC
	end

RuinsOfAlph_Lab_EventScript_ReceiveLileepPC_Nuzlocke::
	call Common_EventScript_NameReceivedBoxMon
	goto RuinsOfAlph_Lab_EventScript_TransferLileepToPC
	end
	
RuinsOfAlph_Lab_EventScript_TransferLileepToPC::
	call Common_EventScript_TransferredToPC
	goto RuinsOfAlph_Lab_EventScript_FinishReceivingLileep
	end

RuinsOfAlph_Lab_EventScript_ReceivedLileepFanfare::
	bufferspeciesname STR_VAR_2, SPECIES_LILEEP
	playfanfare MUS_OBTAIN_ITEM
	message RuinsOfAlph_Lab_Text_ReceivedMonFromResearcher
	waitmessage
	waitfanfare
	bufferspeciesname STR_VAR_1, SPECIES_LILEEP
	return

RuinsOfAlph_Lab_EventScript_FinishReceivingLileep::
	setvar VAR_FOSSIL_RESURRECTION_STATE, 0
	setflag FLAG_RECEIVED_REVIVED_FOSSIL_MON
	release
	end

RuinsOfAlph_Lab_EventScript_ReceiveAnorith::
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_ANORITH
	givemon SPECIES_ANORITH, 20
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, RuinsOfAlph_Lab_EventScript_ReceiveAnorithParty
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, RuinsOfAlph_Lab_EventScript_ReceiveAnorithPC
	goto Common_EventScript_NoMoreRoomForPokemon
	end

RuinsOfAlph_Lab_EventScript_ReceiveAnorithParty::
	call RuinsOfAlph_Lab_EventScript_ReceivedAnorithFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RuinsOfAlph_Lab_EventScript_FinishReceivingAnorith
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto RuinsOfAlph_Lab_EventScript_FinishReceivingAnorith
	end

RuinsOfAlph_Lab_EventScript_ReceiveAnorithPC::
	call RuinsOfAlph_Lab_EventScript_ReceivedAnorithFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RuinsOfAlph_Lab_EventScript_TransferAnorithToPC
	call Common_EventScript_NameReceivedBoxMon
	goto RuinsOfAlph_Lab_EventScript_TransferAnorithToPC
	end

RuinsOfAlph_Lab_EventScript_TransferAnorithToPC::
	call Common_EventScript_TransferredToPC
	goto RuinsOfAlph_Lab_EventScript_FinishReceivingAnorith
	end

RuinsOfAlph_Lab_EventScript_ReceivedAnorithFanfare::
	bufferspeciesname STR_VAR_2, SPECIES_ANORITH
	playfanfare MUS_OBTAIN_ITEM
	message RuinsOfAlph_Lab_Text_ReceivedMonFromResearcher
	waitmessage
	waitfanfare
	bufferspeciesname STR_VAR_1, SPECIES_ANORITH
	return

RuinsOfAlph_Lab_EventScript_FinishReceivingAnorith::
	setvar VAR_FOSSIL_RESURRECTION_STATE, 0
	setflag FLAG_RECEIVED_REVIVED_FOSSIL_MON
	release
	end

RuinsOfAlph_Lab_EventScript_ReceiveOmanyte::
	setvar VAR_TEMP_1, SPECIES_OMANYTE
	givemon SPECIES_OMANYTE, 20
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, RuinsOfAlph_Lab_EventScript_ReceiveOmanyteParty
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, RuinsOfAlph_Lab_EventScript_ReceiveOmanytePC
	goto Common_EventScript_NoMoreRoomForPokemon
	end

RuinsOfAlph_Lab_EventScript_ReceiveOmanyteParty::
	call RuinsOfAlph_Lab_EventScript_ReceivedOmanyteFanfare
	specialvar VAR_RESULT, IsNuzlockeNicknamingActive
	goto_if_eq VAR_RESULT, TRUE, RuinsOfAlph_Lab_EventScript_ReceiveOmanyteParty_Nuzlocke
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RuinsOfAlph_Lab_EventScript_FinishReceivingOmanyte
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto RuinsOfAlph_Lab_EventScript_FinishReceivingOmanyte
	end

RuinsOfAlph_Lab_EventScript_ReceiveOmanyteParty_Nuzlocke::
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto RuinsOfAlph_Lab_EventScript_FinishReceivingOmanyte
	end

RuinsOfAlph_Lab_EventScript_ReceiveOmanytePC::
	call RuinsOfAlph_Lab_EventScript_ReceivedOmanyteFanfare
	specialvar VAR_RESULT, IsNuzlockeNicknamingActive
	goto_if_eq VAR_RESULT, TRUE, RuinsOfAlph_Lab_EventScript_ReceiveOmanytePC_Nuzlocke
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RuinsOfAlph_Lab_EventScript_TransferOmanyteToPC
	call Common_EventScript_NameReceivedBoxMon
	goto RuinsOfAlph_Lab_EventScript_TransferOmanyteToPC
	end

RuinsOfAlph_Lab_EventScript_ReceiveOmanytePC_Nuzlocke::
	call Common_EventScript_NameReceivedBoxMon
	goto RuinsOfAlph_Lab_EventScript_TransferOmanyteToPC
	end
	
RuinsOfAlph_Lab_EventScript_TransferOmanyteToPC::
	call Common_EventScript_TransferredToPC
	goto RuinsOfAlph_Lab_EventScript_FinishReceivingOmanyte
	end

RuinsOfAlph_Lab_EventScript_ReceivedOmanyteFanfare::
	bufferspeciesname STR_VAR_2, SPECIES_OMANYTE
	playfanfare MUS_OBTAIN_ITEM
	message RuinsOfAlph_Lab_Text_ReceivedMonFromResearcher
	waitmessage
	waitfanfare
	bufferspeciesname STR_VAR_1, SPECIES_OMANYTE
	return

RuinsOfAlph_Lab_EventScript_FinishReceivingOmanyte::
	setvar VAR_FOSSIL_RESURRECTION_STATE, 0
	setflag FLAG_RECEIVED_REVIVED_FOSSIL_MON
	release
	end

RuinsOfAlph_Lab_EventScript_ReceiveKabuto::
	setvar VAR_TEMP_1, SPECIES_KABUTO
	call_if_unset FLAG_BADGE04_GET, RuinsOfAlph_Lab_EventScript_GiveEarlyKabuto
	call_if_set FLAG_BADGE04_GET, RuinsOfAlph_Lab_EventScript_GiveLateKabuto
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, RuinsOfAlph_Lab_EventScript_ReceiveKabutoParty
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, RuinsOfAlph_Lab_EventScript_ReceiveKabutoPC
	goto Common_EventScript_NoMoreRoomForPokemon
	end

RuinsOfAlph_Lab_EventScript_GiveEarlyKabuto::
	givemon SPECIES_KABUTO, 5
	return

RuinsOfAlph_Lab_EventScript_GiveLateKabuto::
	givemon SPECIES_KABUTO, 20
	return

RuinsOfAlph_Lab_EventScript_ReceiveKabutoParty::
	call RuinsOfAlph_Lab_EventScript_ReceivedKabutoFanfare
	specialvar VAR_RESULT, IsNuzlockeNicknamingActive
	goto_if_eq VAR_RESULT, TRUE, RuinsOfAlph_Lab_EventScript_ReceiveKabutoParty_Nuzlocke
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RuinsOfAlph_Lab_EventScript_FinishReceivingKabuto
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto RuinsOfAlph_Lab_EventScript_FinishReceivingKabuto
	end

RuinsOfAlph_Lab_EventScript_ReceiveKabutoParty_Nuzlocke::
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto RuinsOfAlph_Lab_EventScript_FinishReceivingKabuto
	end

RuinsOfAlph_Lab_EventScript_ReceiveKabutoPC::
	call RuinsOfAlph_Lab_EventScript_ReceivedKabutoFanfare
	specialvar VAR_RESULT, IsNuzlockeNicknamingActive
	goto_if_eq VAR_RESULT, TRUE, RuinsOfAlph_Lab_EventScript_ReceiveKabutoPC_Nuzlocke
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RuinsOfAlph_Lab_EventScript_TransferKabutoToPC
	call Common_EventScript_NameReceivedBoxMon
	goto RuinsOfAlph_Lab_EventScript_TransferKabutoToPC
	end

RuinsOfAlph_Lab_EventScript_ReceiveKabutoPC_Nuzlocke::
	call Common_EventScript_NameReceivedBoxMon
	goto RuinsOfAlph_Lab_EventScript_TransferKabutoToPC
	end
	
RuinsOfAlph_Lab_EventScript_TransferKabutoToPC::
	call Common_EventScript_TransferredToPC
	goto RuinsOfAlph_Lab_EventScript_FinishReceivingKabuto
	end

RuinsOfAlph_Lab_EventScript_ReceivedKabutoFanfare::
	bufferspeciesname STR_VAR_2, SPECIES_KABUTO
	playfanfare MUS_OBTAIN_ITEM
	message RuinsOfAlph_Lab_Text_ReceivedMonFromResearcher
	waitmessage
	waitfanfare
	bufferspeciesname STR_VAR_1, SPECIES_KABUTO
	return

RuinsOfAlph_Lab_EventScript_FinishReceivingKabuto::
	setvar VAR_FOSSIL_RESURRECTION_STATE, 0
	setflag FLAG_RECEIVED_REVIVED_FOSSIL_MON
	release
	end

RuinsOfAlph_Lab_EventScript_ReceiveAero::
	setvar VAR_TEMP_1, SPECIES_AERODACTYL
	givemon SPECIES_AERODACTYL, 20
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, RuinsOfAlph_Lab_EventScript_ReceiveAeroParty
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, RuinsOfAlph_Lab_EventScript_ReceiveAeroPC
	goto Common_EventScript_NoMoreRoomForPokemon
	end

RuinsOfAlph_Lab_EventScript_ReceiveAeroParty::
	call RuinsOfAlph_Lab_EventScript_ReceivedAeroFanfare
	specialvar VAR_RESULT, IsNuzlockeNicknamingActive
	goto_if_eq VAR_RESULT, TRUE, RuinsOfAlph_Lab_EventScript_ReceiveAeroParty_Nuzlocke
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RuinsOfAlph_Lab_EventScript_FinishReceivingAero
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto RuinsOfAlph_Lab_EventScript_FinishReceivingAero
	end

RuinsOfAlph_Lab_EventScript_ReceiveAeroParty_Nuzlocke::
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto RuinsOfAlph_Lab_EventScript_FinishReceivingAero
	end

RuinsOfAlph_Lab_EventScript_ReceiveAeroPC::
	call RuinsOfAlph_Lab_EventScript_ReceivedAeroFanfare
	specialvar VAR_RESULT, IsNuzlockeNicknamingActive
	goto_if_eq VAR_RESULT, TRUE, RuinsOfAlph_Lab_EventScript_ReceiveAeroPC_Nuzlocke
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RuinsOfAlph_Lab_EventScript_TransferAeroToPC
	call Common_EventScript_NameReceivedBoxMon
	goto RuinsOfAlph_Lab_EventScript_TransferAeroToPC
	end

RuinsOfAlph_Lab_EventScript_ReceiveAeroPC_Nuzlocke::
	call Common_EventScript_NameReceivedBoxMon
	goto RuinsOfAlph_Lab_EventScript_TransferAeroToPC
	end
	
RuinsOfAlph_Lab_EventScript_TransferAeroToPC::
	call Common_EventScript_TransferredToPC
	goto RuinsOfAlph_Lab_EventScript_FinishReceivingAero
	end

RuinsOfAlph_Lab_EventScript_ReceivedAeroFanfare::
	bufferspeciesname STR_VAR_2, SPECIES_AERODACTYL
	playfanfare MUS_OBTAIN_ITEM
	message RuinsOfAlph_Lab_Text_ReceivedMonFromResearcher
	waitmessage
	waitfanfare
	bufferspeciesname STR_VAR_1, SPECIES_AERODACTYL
	return

RuinsOfAlph_Lab_EventScript_FinishReceivingAero::
	setvar VAR_FOSSIL_RESURRECTION_STATE, 0
	setflag FLAG_RECEIVED_REVIVED_FOSSIL_MON
	release
	end


RuinsOfAlph_Lab_EventScript_ChooseFossil::
	message RuinsOfAlph_Lab_Text_TwoFossilsPickOne
	waitmessage
	multichoice 17, 0, MULTI_FOSSIL_HNS, FALSE
	switch VAR_RESULT
	case 0, RuinsOfAlph_Lab_EventScript_ChooseClawFossil
	case 1, RuinsOfAlph_Lab_EventScript_ChooseRootFossil
	case 2, RuinsOfAlph_Lab_EventScript_ChooseHelixFossil
	case 3, RuinsOfAlph_Lab_EventScript_ChooseDomeFossil
	case 4, RuinsOfAlph_Lab_EventScript_ChooseOldAmber
	case 5, RuinsOfAlph_Lab_EventScript_CancelFossilSelect
	case MULTI_B_PRESSED, RuinsOfAlph_Lab_EventScript_CancelFossilSelect
	end

RuinsOfAlph_Lab_EventScript_ChooseClawFossil::
	checkitem ITEM_CLAW_FOSSIL
	goto_if_eq VAR_RESULT, TRUE, RuinsOfAlph_Lab_EventScript_GiveClawFossil
	goto_if_eq VAR_RESULT, FALSE, RuinsOfAlph_Lab_EventScript_DeclineGiveFossil2
	end

RuinsOfAlph_Lab_EventScript_ChooseRootFossil::
	checkitem ITEM_ROOT_FOSSIL
	goto_if_eq VAR_RESULT, TRUE, RuinsOfAlph_Lab_EventScript_GiveRootFossil
	goto_if_eq VAR_RESULT, FALSE, RuinsOfAlph_Lab_EventScript_DeclineGiveFossil2
	end

RuinsOfAlph_Lab_EventScript_ChooseHelixFossil::
	checkitem ITEM_HELIX_FOSSIL
	goto_if_eq VAR_RESULT, TRUE, RuinsOfAlph_Lab_EventScript_GiveHelixFossil
	goto_if_eq VAR_RESULT, FALSE, RuinsOfAlph_Lab_EventScript_DeclineGiveFossil2
	end

RuinsOfAlph_Lab_EventScript_ChooseDomeFossil::
	checkitem ITEM_DOME_FOSSIL
	goto_if_eq VAR_RESULT, TRUE, RuinsOfAlph_Lab_EventScript_GiveDomeFossil
	goto_if_eq VAR_RESULT, FALSE, RuinsOfAlph_Lab_EventScript_DeclineGiveFossil2
	end

RuinsOfAlph_Lab_EventScript_ChooseOldAmber::
	checkitem ITEM_OLD_AMBER
	goto_if_eq VAR_RESULT, TRUE, RuinsOfAlph_Lab_EventScript_GiveOldAmber
	goto_if_eq VAR_RESULT, FALSE, RuinsOfAlph_Lab_EventScript_DeclineGiveFossil2
	end

RuinsOfAlph_Lab_EventScript_CancelFossilSelect::
	release
	end

RuinsOfAlph_Lab_EventScript_WorkOnNext::
	msgbox RuinsOfAlph_Lab_Text_WhatToWorkOnNext, MSGBOX_DEFAULT
	release
	end

RuinsOfAlph_Lab_Text_DeviceForTalkingToPokemon:
	.string "Creamos un aparato para hablar,\n"
	.string "vínculo ideal con los POKéMON.\p"
	.string "pero no hemos tenido éxito...$"

RuinsOfAlph_Lab_Text_DevelopingNewBalls:
	.string "Estoy creando nuevos tipos de\n"
	.string "POKé BALLS…\p"
	.string "Pero no he avanzado mucho…$"

RuinsOfAlph_Lab_Text_WeFinallyMadeNewBalls:
	.string "¡Al fin creamos nuevos tipos de\n"
	.string "POKé BALLS!\p"
	.string "La REPEAT BALL facilita capturar\n"
	.string "POKéMON que ya has atrapado.\p"
	.string "La TIMER BALL mejora su captura\n"
	.string "mientras más dura la batalla.\p"
	.string "Ambas fueron desarrolladas por la\n"
	.string "DEVON CORPORATION.\p"
	.string "¡Por favor, pruébalas!$"

RuinsOfAlph_Lab_Text_IMadePokenav:
	.string "¡Yo hice el POKéNAV!\p"
	.string "Como ingeniero, me siento bendecido\n"
	.string "¡de haber creado algo tan genial!$"

RuinsOfAlph_Lab_Text_WowThatsAPokenav:
	.string "¡Oh, vaya!\n"
	.string "¡Eso es un POKéNAV!\p"
	.string "Surgió gracias al deseo de nuestro\n"
	.string "PRESIDENTE de conocer mejor\l"
	.string "los sentimientos de los POKéMON.\p"
	.string "¿Quieres que te describa sus\n"
	.string "funciones en detalle?\p"
	.string "No, no. Creo que lo descubrirás al\n"
	.string "probar el POKéNAV.$"

RuinsOfAlph_Lab_Text_DeviceToVisualizePokemonDreams:
	.string "Intento crear un dispositivo que\n"
	.string "reproduzca visualmente los sueños de\l"
	.string "POKéMON…\p"
	.string "Pero no va muy bien.$"

RuinsOfAlph_Lab_Text_DevelopDeviceToResurrectFossils:
	.string "He intentado crear un aparato\n"
	.string "que reviva POKéMON de fósiles…\p"
	.string "¡Y está funcionando!$"

RuinsOfAlph_Lab_Text_WantToBringFossilBackToLife:
	.string "¡Espera! Eso que tienes ahí…\n"
	.string "¿Es un fósil POKéMON?\p"
	.string "¿Te gustaría devolver a la vida\n"
	.string "a ese POKéMON?\p"
	.string "Puedo hacerlo con mi nuevo\n"
	.string "REGENERADOR DE FÓSILES.$"

RuinsOfAlph_Lab_Text_OhIsThatSo:
	.string "Ah, ¿es así?\p"
	.string "Mi pericia tecnológica\n"
	.string "es extraordinaria, te lo digo.$"

RuinsOfAlph_Lab_Text_OhIsThatSo2:
	.string "Oh, no tienes este fósil.\n"
	.string "Vuelve si logras encontrarlo.$"

RuinsOfAlph_Lab_Text_TwoFossilsPickOne:
	.string "¡Vaya, eso es una sorpresa!\n"
	.string "¿Tienes más de un fósil?\p"
	.string "Lamentablemente, mi máquina solo\n"
	.string "regenera un POKéMON a la vez.\p"
	.string "¿Qué fósil te gustaría\n"
	.string "regenerar?$"

RuinsOfAlph_Lab_Text_HandedFossilToResearcher:
	.string "¡Excelente!\n"
	.string "Hagámoslo ahora mismo.\p"
	.string "{PLAYER} le dio el {STR_VAR_1} al\n"
	.string "INVESTIGADOR DE RUINAS.$"

RuinsOfAlph_Lab_Text_FossilRegeneratorTakesTime:
	.string "El REGENERADOR DE FÓSILES, que hice,\n"
	.string "es increíble.\p"
	.string "Pero tiene un inconveniente: tarda\n"
	.string "mucho tiempo en funcionar.\p"
	.string "Así que... ¿qué tal si das un paseo\n"
	.string "y miras alrededor un rato?$"

RuinsOfAlph_Lab_Text_FossilizedMonBroughtBackToLife:
	.string "¡Gracias por esperar!\p"
	.string "Tu POKéMON fósil ha sido\n"
	.string "¡devuelto a la vida!\p"
	.string "El fósil era un antiguo POKéMON.\n"
	.string "¡Era un {STR_VAR_2}!$"

RuinsOfAlph_Lab_Text_ReceivedMonFromResearcher:
	.string "{PLAYER} recibió a {STR_VAR_2} del\n"
	.string "INVESTIGADOR.$"

@ Unused
RuinsOfAlph_Lab_Text_TooManyPokemon:
	.string "Oh no, tienes demasiados POKéMON.\n"
	.string "No tienes espacio para este.$"

RuinsOfAlph_Lab_Text_DevelopNewPokenavFeature:
	.string "Intento crear una función nueva\n"
	.string "para el POKéNAV…\p"
	.string "Pero no va muy bien.$"

RuinsOfAlph_Lab_Text_WhatToWorkOnNext:
	.string "Bueno, ¿en qué debería trabajar\n"
	.string "ahora para desarrollarlo?\p"
	.string "Nuestra empresa nos permite hacer\n"
	.string "realidad nuestras inspiraciones.\p"
	.string "Un ingeniero no podría pedir un\n"
	.string "mejor entorno de trabajo.$"


