AzaleaTown_PokemonCenter_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, AzaleaTown_Pokecenter_OnTransition
	.byte 0

AzaleaTown_Pokecenter_OnTransition::
	setrespawn HEAL_LOCATION_AZALEA_TOWN_HNS
	end

AzaleaPokeCenter_EventScript_Gentleman::
	lock
	faceplayer
	msgbox AzaleaPokecenter_Text_Gentleman, MSGBOX_DEFAULT
	closemessage
	release
	end

AzaleaPokeCenter_EventScript_Fisher::
	lock
	faceplayer
	msgbox AzaleaPokecenter_Text_FishingGuru, MSGBOX_DEFAULT
	closemessage
	release
	end

AzaleaPokeCenter_EventScript_PokefanF::
	lock
	faceplayer
	msgbox AzaleaPokecenter_Text_PokefanF, MSGBOX_DEFAULT
	closemessage
	release
	end

AzaleaPokecenter_Text_Gentleman:
	.string "הפוקימונים שלך יודעים מהלכי מ”נ?\p"
	.string "אפשר להשתמש במהלכים האלה\n"
	.string "גם אם הפוקימון שלך התעלף.$"

AzaleaPokecenter_Text_UnusedPCExplanation:
	.string "This BILL guy created the system\n"
	.string "for storing POKéMON in a PC.\p"
	.string "BILL's PC can store up to 30\n"
	.string "POKéMON per BOX.$"

AzaleaPokecenter_Text_FishingGuru:
	.string "המחשב של ביל יכול לאחסן\n"
	.string "עד 30 פוקימונים בכל תיבה.$"

AzaleaPokecenter_Text_PokefanF:
	.string "אתה מכיר את הפירות?\p"
	.string "פותחים אחד, מרוקנים אותו\n"
	.string "ומכניסים לתוכו מתקן מיוחד.\p"
	.string "ואז אפשר לתפוס איתו פוקימונים.\p"
	.string "לפני שהמציאו את הפוכדורים,\n"
	.string "כולם השתמשו בפירות.$"
