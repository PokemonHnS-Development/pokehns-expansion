SaffronCity_PokemonCenter_hns_MapScripts::
map_script MAP_SCRIPT_ON_TRANSITION, SaffronCity_PokemonCenter_OnTransition
	.byte 0

SaffronCity_PokemonCenter_OnTransition::
	setrespawn HEAL_LOCATION_SAFFRON_CITY_HNS
	end

SaffronCity_PokemonCenter_EventScript_Teacher::
	msgbox SaffronCity_PokemonCenter1F_Text_Teacher, MSGBOX_NPC	
	end

SaffronCity_PokemonCenter_EventScript_Fisher::
	goto_if_set FLAG_RETURNED_MACHINE_PART, SaffronCity_PokemonCenter_EventScript_FisherReturnedMachinePart
	msgbox SaffronCity_PokemonCenter1F_Text_Fisher, MSGBOX_NPC	
	end
SaffronCity_PokemonCenter_EventScript_FisherReturnedMachinePart::
	msgbox SaffronCity_PokemonCenter1F_Text_Fisher_ReturnedPart, MSGBOX_NPC
	end

SaffronCity_PokemonCenter_EventScript_Youngster::
	msgbox SaffronCity_PokemonCenter1F_Text_Youngster, MSGBOX_NPC
	end

SaffronCity_PokemonCenter1F_Text_Teacher:
	.string "איך נראים מרכזי הפוקימון\n"
	.string "בג'וטו?\p"
	.string "…אה, הבנתי. אז הם לא שונים\n"
	.string "בהרבה מאלה שבקאנטו.\p"
	.string "אם כך, אני יכולה לנסוע לג'וטו\n"
	.string "בלי לדאוג!$"

SaffronCity_PokemonCenter1F_Text_Fisher:
	.string "במקרה עברתי דרך\n"
	.string "מערת האבן.\p"
	.string "הייתה איזו מהומה\n"
	.string "במפעל החשמל.$"

SaffronCity_PokemonCenter1F_Text_Fisher_ReturnedPart:
	.string "יש מערה מוזרה בסרוליאן.\p"
	.string "בתור מטייל מקצועי, אני אמור לחקור\n"
	.string "אותה, אבל המקום הזה מפחיד אפילו אותי.$"

SaffronCity_PokemonCenter1F_Text_Youngster:
	.string "המטה של סילף בע”מ ותחנת הרכבת\n"
	.string "המגנטית הם האטרקציות של סאפרון.$"
