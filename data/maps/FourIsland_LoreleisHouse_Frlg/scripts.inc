FourIsland_LoreleisHouse_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, FourIsland_LoreleisHouse_OnTransition
	.byte 0

FourIsland_LoreleisHouse_OnTransition::
	special UpdateLoreleiDollCollection
	end

FourIsland_LoreleisHouse_EventScript_Lorelei::
	lock
	faceplayer
	goto_if_set FLAG_TALKED_TO_LORELEI_AFTER_WAREHOUSE, FourIsland_LoreleisHouse_EventScript_Lorelei3
	goto_if_set FLAG_DEFEATED_ROCKETS_IN_WAREHOUSE, FourIsland_LoreleisHouse_EventScript_Lorelei2
	msgbox FourIsland_LoreleisHouse_Text_IfAnythingWereToHappenToIsland
	release
	end

FourIsland_LoreleisHouse_EventScript_Lorelei2::
	setflag FLAG_TALKED_TO_LORELEI_AFTER_WAREHOUSE
	msgbox FourIsland_LoreleisHouse_Text_IllReturnToLeagueInShortWhile
	release
	end

FourIsland_LoreleisHouse_EventScript_Lorelei3::
	msgbox FourIsland_LoreleisHouse_Text_WillDoWhatICanHereAndNow
	release
	end

FourIsland_LoreleisHouse_EventScript_Doll::
	lock
	msgbox FourIsland_LoreleisHouse_Text_StuffedMonDollsGalore
	release
	end

FourIsland_LoreleisHouse_Text_IfAnythingWereToHappenToIsland::
	.string "LORELEI: Hay algo que me\n"
	.string "pesa mucho en la mente.\p"
	.string "Si llegara a pasar algo en\n"
	.string "la isla donde nací...\p"
	.string "no lo sabría si fuera\n"
	.string "in the POKéMON LEAGUE.\p"
	.string "Me pregunto si eso me haría\n"
	.string "irresponsable con mi hogar...$"

FourIsland_LoreleisHouse_Text_IllReturnToLeagueInShortWhile::
	.string "LORELEI: Así que lograste\n"
	.string "todos los problemas de aquí?\p"
	.string "Qué maravilla.\p"
	.string "Eso significa que no hay razón\n"
	.string "para que yo esté aquí siempre.\p"
	.string "Gracias...\p"
	.string "I'll return to the POKéMON LEAGUE\n"
	.string "dentro de poco.$"

FourIsland_LoreleisHouse_Text_WillDoWhatICanHereAndNow::
	.string "No sé qué pasará\n"
	.string "el futuro, pero...\p"
	.string "Haré lo que pueda aquí y ahora.\n"
	.string "Es todo lo que puedo hacer.$"

FourIsland_LoreleisHouse_Text_StuffedMonDollsGalore::
	.string "Stuffed POKéMON dolls galore!$"

