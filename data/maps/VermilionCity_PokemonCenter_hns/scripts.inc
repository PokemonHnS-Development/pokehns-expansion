VermilionCity_PokemonCenter_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, VermilionCity_PokemonCenter_OnTransition
	.byte 0

VermilionCity_PokemonCenter_OnTransition::
	setrespawn HEAL_LOCATION_VERMILION_CITY_HNS
	end

VermilionPokeCenter_EventScript_FishingGuru::
	goto_if_set FLAG_HIDE_VERMILION_SNORLAX, VermilionPokeCenter_EventScript_FishingGuru2
	msgbox VermilionCity_PokemonCenter1F_Text_FishingGuru, MSGBOX_NPC
	end

VermilionPokeCenter_EventScript_FishingGuru2::
	msgbox VermilionCity_PokemonCenter1F_Text_FishingGuru_FoughtSnorlax, MSGBOX_NPC
	end

VermilionPokeCenter_EventScript_Sailor::
	msgbox VermilionCity_PokemonCenter1F_Text_Sailor, MSGBOX_NPC
	end

VermilionPokeCenter_EventScript_Bugcatcher::
	msgbox VermilionCity_PokemonCenter1F_Text_BugCatcher, MSGBOX_NPC
	end

VermilionCity_PokemonCenter1F_Text_FishingGuru:
	.string "פוקימון ישן שוכב מול\n"
	.string "מערת דיגלט.\p"
	.string "זו הזדמנות פנטסטית לתפוס\n"
	.string "אותו, אבל איך מעירים אותו?$"

VermilionCity_PokemonCenter1F_Text_FishingGuru_FoughtSnorlax:
	.string "פעם שכב פוקימון ישן\n"
	.string "מול מערת דיגלט.\p"
	.string "אבל נראה שהוא נעלם.$"

VermilionCity_PokemonCenter1F_Text_Sailor:
	.string "הספינה המהירה היא מקום מעולה\n"
	.string "לפגוש מאמנים ולהילחם בהם.$"

VermilionCity_PokemonCenter1F_Text_BugCatcher:
	.string "אה? יש לך תגים שלא ראיתי\n"
	.string "אף פעם.\p"
	.string "אה, הבנתי. השגת אותם\n"
	.string "בג'וטו.$"
