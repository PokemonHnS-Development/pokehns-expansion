CeruleanCity_PokemonCenter_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, CeruleanCity_PokemonCenter_OnTransition
	.byte 0

CeruleanCity_PokemonCenter_OnTransition::
	setrespawn HEAL_LOCATION_CERULEAN_CITY_HNS
	end

CeruleanCity_PokemonCenter_EventScript_Nerd::
	msgbox CeruleanCity_PokemonCenter1F_Text_SuperNerd, MSGBOX_NPC
	end

CeruleanCity_PokemonCenter_EventScript_Guy::
	msgbox CeruleanCity_PokemonCenter1F_Text_GymGuide, MSGBOX_NPC
	end

CeruleanCity_PokemonCenter1F_Text_SuperNerd:
	.string "בקרבות, אני מעדיף בהרבה להשתמש\n"
	.string "בפוקימונים שגידלתי בעצמי,\p"
	.string "גם אם הם חלשים יותר\n"
	.string "מפוקימונים שזה עתה נתפסו.$"

CeruleanCity_PokemonCenter1F_Text_GymGuide:
	.string "הרכבת המגנטית נוסעת במהירות\n"
	.string "של יותר מ-340 מייל לשעה.\p"
	.string "היא עוברת בין קאנטו לג'וטו\n"
	.string "כמעט בן רגע.\p"
	.string "בזכותה ממש קל להגיע לג'וטו.$"
