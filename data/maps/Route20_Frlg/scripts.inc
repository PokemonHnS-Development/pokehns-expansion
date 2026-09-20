Route20_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route20_OnTransition
	.byte 0

Route20_OnTransition::
	call_if_unset FLAG_STOPPED_SEAFOAM_B3F_CURRENT, Route20_EventScript_ResetSeafoamBouldersForB3F
	call_if_unset FLAG_STOPPED_SEAFOAM_B4F_CURRENT, Route20_EventScript_ResetSeafoamBouldersForB4F
	end

Route20_EventScript_ResetSeafoamBouldersForB3F::
	clearflag FLAG_HIDE_SEAFOAM_1F_BOULDER_1
	clearflag FLAG_HIDE_SEAFOAM_1F_BOULDER_2
	setflag FLAG_HIDE_SEAFOAM_B1F_BOULDER_1
	setflag FLAG_HIDE_SEAFOAM_B1F_BOULDER_2
	setflag FLAG_HIDE_SEAFOAM_B2F_BOULDER_1
	setflag FLAG_HIDE_SEAFOAM_B2F_BOULDER_2
	setflag FLAG_HIDE_SEAFOAM_B3F_BOULDER_1
	setflag FLAG_HIDE_SEAFOAM_B3F_BOULDER_2
	return

Route20_EventScript_ResetSeafoamBouldersForB4F::
	clearflag FLAG_HIDE_SEAFOAM_B3F_BOULDER_3
	clearflag FLAG_HIDE_SEAFOAM_B3F_BOULDER_4
	clearflag FLAG_HIDE_SEAFOAM_B3F_BOULDER_5
	clearflag FLAG_HIDE_SEAFOAM_B3F_BOULDER_6
	setflag FLAG_HIDE_SEAFOAM_B4F_BOULDER_1
	setflag FLAG_HIDE_SEAFOAM_B4F_BOULDER_2
	return

Route20_EventScript_SeafoamIslandsSign::
	msgbox Route20_Text_SeafoamIslands, MSGBOX_SIGN
	end

Route20_Text_BarryIntro::
	.string "El agua es poco profunda aquí.\n"
	.string "Hay mucha gente nadando.$"

Route20_Text_BarryDefeat::
	.string "Splash!$"

Route20_Text_BarryPostBattle::
	.string "I wish I could ride my POKéMON.\n"
	.string "I bet you're not tired.$"

Route20_Text_ShirleyIntro::
	.string "SEAFOAM is a quiet getaway.\n"
	.string "I'm vacationing here.$"

Route20_Text_ShirleyDefeat::
	.string "Quit it!$"

Route20_Text_ShirleyPostBattle::
	.string "There's a huge cavern underneath\n"
	.string "this island.$"

Route20_Text_TiffanyIntro::
	.string "Amo flotar con los peces\n"
	.string "aquí entre las olas.$"

Route20_Text_TiffanyDefeat::
	.string "Yowch!$"

Route20_Text_TiffanyPostBattle::
	.string "Want to float with me?$"

Route20_Text_IreneIntro::
	.string "Are you on vacation, too?$"

Route20_Text_IreneDefeat::
	.string "No mercy at all!$"

Route20_Text_IrenePostBattle::
	.string "SEAFOAM used to be a single island\n"
	.string "in the distant past.$"

Route20_Text_DeanIntro::
	.string "Check out my buff physique!$"

Route20_Text_DeanDefeat::
	.string "Wimpy!$"

Route20_Text_DeanPostBattle::
	.string "I should've been buffing up my\n"
	.string "POKéMON, not me!$"

Route20_Text_DarrinIntro::
	.string "¿Por qué montas un POKéMON?\n"
	.string "Can't you swim?$"

Route20_Text_DarrinDefeat::
	.string "¡Ay!\n"
	.string "Torpedoed!$"

Route20_Text_DarrinPostBattle::
	.string "Riding a POKéMON sure looks fun!$"

Route20_Text_RogerIntro::
	.string "Vine aquí en mi POKéMON ave.$"

Route20_Text_RogerDefeat::
	.string "Oh, no!\n"
	.string "Now what am I to do?$"

Route20_Text_RogerPostBattle::
	.string "My birds are exhausted.\n"
	.string "They can't FLY me back!$"

Route20_Text_NoraIntro::
	.string "My boyfriend gave me big pearls.$"

Route20_Text_NoraDefeat::
	.string "Oh, no!\n"
	.string "My pearls were in them!$"

Route20_Text_NoraPostBattle::
	.string "Will my pearls grow bigger inside\n"
	.string "CLOYSTER?$"

Route20_Text_MissyIntro::
	.string "Nadé desde ISLA CANELA hasta aquí.\n"
	.string "It wasn't easy, I tell you.$"

Route20_Text_MissyDefeat::
	.string "I'm so disappointed!$"

Route20_Text_MissyPostBattle::
	.string "POKéMON have taken over an\n"
	.string "abandoned mansion on CINNABAR.\p"
	.string "They call it the POKéMON MANSION\n"
	.string "now.$"

Route20_Text_MelissaIntro::
	.string "En CANELA, al oeste, hay un LAB\n"
	.string "POKéMON.\p"
	.string "Mi papá trabaja allí.$"

Route20_Text_MelissaDefeat::
	.string "¡Espera!\n"
	.string "You're supposed to wait!$"

Route20_Text_MelissaPostBattle::
	.string "CINNABAR is a volcanic island.\p"
	.string "I heard it rose out of the sea\n"
	.string "when a volcano erupted.$"

Route20_Text_SeafoamIslands::
	.string "SEAFOAM ISLANDS$"

Route20_Text_MistyTrainsHere::
	.string "Strong TRAINERS and WATER POKéMON\n"
	.string "de AGUA abundan por aquí.\p"
	.string "Dicen que MISTY, del\n"
	.string "GIMNASIO CERULEAN, entrena aquí.$"
