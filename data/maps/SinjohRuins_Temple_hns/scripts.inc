SinjohRuins_Temple_hns_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, SinjohRuins_Temple_OnLoad
	.byte 0


SinjohRuins_Temple_OnLoad::
	call_if_ge VAR_REGIS_SCANNED, 5, SinjohRuins_Temple_OpenDoor
	end

SinjohRuins_Temple_OpenDoor::
	setmetatile 18, 7, 0x308, FALSE
	return

SinjohRuins_Temple_Text_Mon:
	.string "Some kind of ancient sensor.\n"
	.string "What is it looking for?$"

SinjohRuins_Temple_EventScript_RegiceScanner::
	lock
	goto_if_set FLAG_BROUGHT_REGICE, SinjohRuins_Temple_EventScript_ScannerAlreadyDone
	msgbox SinjohRuins_Temple_Text_Mon, MSGBOX_AUTOCLOSE
	checkspecies SPECIES_REGICE
	goto_if_eq VAR_RESULT, FALSE, SinjohRuins_Lab_EventScript_NoOp
	setflag FLAG_BROUGHT_REGICE
    goto_if_eq VAR_RESULT, TRUE, SinjohRuins_Temple_EventScript_SeenPokemon
	release
	end

SinjohRuins_Temple_EventScript_RegirockScanner::
	lock
	goto_if_set FLAG_BROUGHT_REGIROCK, SinjohRuins_Temple_EventScript_ScannerAlreadyDone
	msgbox SinjohRuins_Temple_Text_Mon, MSGBOX_AUTOCLOSE
	checkspecies SPECIES_REGIROCK
	goto_if_eq VAR_RESULT, FALSE, SinjohRuins_Lab_EventScript_NoOp
	setflag FLAG_BROUGHT_REGIROCK
    goto_if_eq VAR_RESULT, TRUE, SinjohRuins_Temple_EventScript_SeenPokemon
	release
	end

SinjohRuins_Temple_EventScript_RegisteelScanner::
	lock
	goto_if_set FLAG_BROUGHT_REGISTEEL, SinjohRuins_Temple_EventScript_ScannerAlreadyDone
	msgbox SinjohRuins_Temple_Text_Mon, MSGBOX_AUTOCLOSE
	checkspecies SPECIES_REGISTEEL
	goto_if_eq VAR_RESULT, FALSE, SinjohRuins_Lab_EventScript_NoOp
	setflag FLAG_BROUGHT_REGISTEEL
    goto_if_eq VAR_RESULT, TRUE, SinjohRuins_Temple_EventScript_SeenPokemon
	release
	end

SinjohRuins_Temple_EventScript_RegielekiScanner::
	lock
	goto_if_set FLAG_BROUGHT_REGIELEKI, SinjohRuins_Temple_EventScript_ScannerAlreadyDone
	msgbox SinjohRuins_Temple_Text_Mon, MSGBOX_AUTOCLOSE
	checkspecies SPECIES_REGIELEKI
	goto_if_eq VAR_RESULT, FALSE, SinjohRuins_Lab_EventScript_NoOp
	setflag FLAG_BROUGHT_REGIELEKI
    goto_if_eq VAR_RESULT, TRUE, SinjohRuins_Temple_EventScript_SeenPokemon
	release
	end

SinjohRuins_Temple_EventScript_RegidragoScanner::
	lock
	goto_if_set FLAG_BROUGHT_REGIDRAGO, SinjohRuins_Temple_EventScript_ScannerAlreadyDone
	msgbox SinjohRuins_Temple_Text_Mon, MSGBOX_AUTOCLOSE
	checkspecies SPECIES_REGIDRAGO
	goto_if_eq VAR_RESULT, FALSE, SinjohRuins_Lab_EventScript_NoOp
	setflag FLAG_BROUGHT_REGIDRAGO
    goto_if_eq VAR_RESULT, TRUE, SinjohRuins_Temple_EventScript_SeenPokemon
	release
	end

SinjohRuins_Temple_EventScript_SeenPokemon::
	playse SE_CLICK
	waitse
	setvar VAR_0x8004, 2  @ vertical pan
    setvar VAR_0x8005, 2  @ horizontal pan
    setvar VAR_0x8006, 20  @ num shakes
    setvar VAR_0x8007, 4  @ shake delay
    special ShakeCamera
    waitstate
	msgbox SinjohRuins_Temple_Text_Responds, MSGBOX_AUTOCLOSE
	addvar VAR_REGIS_SCANNED, 1
	call_if_eq VAR_REGIS_SCANNED, 5, SinjohRuins_Temple_EventScript_UnlockDoor
	release
	end

SinjohRuins_Temple_EventScript_UnlockDoor::
	setvar VAR_0x8004, 2  @ vertical pan
    setvar VAR_0x8005, 2  @ horizontal pan
    setvar VAR_0x8006, 20  @ num shakes
    setvar VAR_0x8007, 4  @ shake delay
    special ShakeCamera
    waitstate
	setmetatile 18, 7, 0x308, FALSE
	special DrawWholeMapView
	msgbox SinjohRuins_Temple_Text_Door, MSGBOX_AUTOCLOSE
	return

SinjohRuins_Temple_EventScript_ScannerAlreadyDone::
	msgbox SinjohRuins_Temple_Text_ScannerAlreadyDone, MSGBOX_SIGN
	release
	end

SinjohRuins_Temple_Text_ScannerAlreadyDone:
	.string "This sensor already been activated.$"

SinjohRuins_Temple_Text_Responds:
	.string "The temple responds to your actions.$"

SinjohRuins_Temple_Text_Door:
	.string "The way is open.$"

