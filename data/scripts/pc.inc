EventScript_PC::
	lockall
#if IS_HNS
	setvar VAR_0x8004, PC_LOCATION_HNS
#else
	setvar VAR_0x8004, PC_LOCATION_OTHER
#endif
	special DoPCTurnOnEffect
	playse SE_PC_ON
	msgbox Text_BootUpPC, MSGBOX_DEFAULT
	goto EventScript_PCMainMenu
	end

EventScript_FakePC::
	lockall
#if IS_HNS
	setvar VAR_0x8004, PC_LOCATION_HNS
#else
	setvar VAR_0x8004, PC_LOCATION_OTHER
#endif
	playse SE_PC_ON
	msgbox Text_BootUpPC, MSGBOX_DEFAULT
	goto EventScript_FakePCMainMenu
	end

EventScript_PCMainMenu::
	message gText_WhichPCShouldBeAccessed
	waitmessage
	special ScriptMenu_CreatePCMultichoice
	waitstate
	goto_if_unset FLAG_SYS_GAME_CLEAR, EventScript_AccessPC_BeforeLeague
	goto EventScript_AccessPC_AfterLeague
	end


EventScript_FakePCMainMenu::
	message gText_WhichPCShouldBeAccessed
	waitmessage
	special ScriptMenu_CreatePCMultichoice
	waitstate
	goto_if_unset FLAG_SYS_GAME_CLEAR, EventScript_AccessFakePC_BeforeLeague
	goto EventScript_AccessFakePC_AfterLeague
	end

EventScript_AccessPC_BeforeLeague::
	switch VAR_RESULT
	case 0, EventScript_AccessPokemonStorage
	case 1, EventScript_AccessPlayersPC
	case 2, EventScript_ChallengeViewer
	case 3, EventScript_TurnOffPC
	case MULTI_B_PRESSED, EventScript_TurnOffPC
	end

EventScript_AccessFakePC_BeforeLeague::
	switch VAR_RESULT
	case 0, EventScript_AccessFakePokemonStorage
	case 1, EventScript_AccessPlayersFakePC
	case 2, EventScript_FakeChallengeViewer
	case 3, EventScript_TurnOffFakePC
	case MULTI_B_PRESSED, EventScript_TurnOffFakePC
	end

EventScript_AccessPC_AfterLeague::
	switch VAR_RESULT
	case 0, EventScript_AccessPokemonStorage
	case 1, EventScript_AccessPlayersPC
	case 2, EventScript_AccessHallOfFame
	case 3, EventScript_ChallengeViewer
	case 4, EventScript_TurnOffPC
	case MULTI_B_PRESSED, EventScript_TurnOffPC
	end

EventScript_AccessFakePC_AfterLeague::
	switch VAR_RESULT
	case 0, EventScript_AccessFakePokemonStorage
	case 1, EventScript_AccessPlayersFakePC
	case 2, EventScript_AccessFakeHallOfFame
	case 3, EventScript_FakeChallengeViewer
	case 4, EventScript_TurnOffFakePC
	case MULTI_B_PRESSED, EventScript_TurnOffFakePC
	end

EventScript_ChallengeViewer::
	playse SE_PC_LOGIN
	callnative Script_OpenChallengeMenu
	waitstate
	goto EventScript_PCMainMenu
	end

EventScript_FakeChallengeViewer::
	playse SE_PC_LOGIN
	callnative Script_OpenChallengeMenu
	delay 30
	goto EventScript_FakePCMainMenu
	end

EventScript_AccessPlayersPC::
	playse SE_PC_LOGIN
	msgbox gText_AccessedPlayersPC, MSGBOX_DEFAULT
	special PlayerPC
	waitstate
	goto EventScript_PCMainMenu
	end

EventScript_AccessPlayersFakePC::
	playse SE_PC_LOGIN
	msgbox gText_AccessedPlayersPC, MSGBOX_DEFAULT
	special PlayerPC
	waitstate
	goto EventScript_FakePCMainMenu
	end

EventScript_AccessPokemonStorage::
	playse SE_PC_LOGIN
	call_if_unset FLAG_SYS_PC_LANETTE, EventScript_AccessSomeonesPC
	call_if_set FLAG_SYS_PC_LANETTE, EventScript_AccessLanettesPC
	msgbox gText_StorageSystemOpened, MSGBOX_DEFAULT
	special ShowPokemonStorageSystemPC
	waitstate
	goto EventScript_PCMainMenu
	end

EventScript_AccessFakePokemonStorage::
	playse SE_PC_LOGIN
	call_if_unset FLAG_SYS_PC_LANETTE, EventScript_AccessSomeonesPC
	call_if_set FLAG_SYS_PC_LANETTE, EventScript_AccessLanettesPC
	msgbox gText_StorageSystemOpened, MSGBOX_DEFAULT
	special ShowPokemonStorageSystemPC
	waitstate
	goto EventScript_FakePCMainMenu
	end

EventScript_AccessSomeonesPC::
	msgbox gText_AccessedSomeonesPC, MSGBOX_DEFAULT
	return

EventScript_AccessLanettesPC::
#if IS_FRLG
	msgbox gText_AccessedBillsPC, MSGBOX_DEFAULT
#else
	msgbox gText_AccessedLanettesPC, MSGBOX_DEFAULT
#endif
	return

EventScript_TurnOffPC::
#if IS_HNS
	setvar VAR_0x8004, PC_LOCATION_HNS
#else
	setvar VAR_0x8004, PC_LOCATION_OTHER
#endif
	playse SE_PC_OFF
	special DoPCTurnOffEffect
	releaseall
	end

EventScript_TurnOffFakePC::
	playse SE_PC_OFF
	releaseall
	end

EventScript_AccessHallOfFame::
	goto_if_unset FLAG_SYS_GAME_CLEAR, EventScript_TurnOffPC
	playse SE_PC_LOGIN
	special AccessHallOfFamePC
	waitstate
	goto EventScript_AccessPC_AfterLeague
	end

EventScript_AccessFakeHallOfFame::
	playse SE_PC_LOGIN
	special AccessHallOfFamePC
	waitstate
	goto EventScript_AccessFakePC_AfterLeague
	end

EventScript_AccessPokemonBoxLink::
	playse SE_PC_LOGIN
	msgbox gText_StorageSystemOpened, MSGBOX_DEFAULT
	special ShowPokemonStorageSystemPC
	waitstate
	goto EventScript_TurnOffPC
	end
