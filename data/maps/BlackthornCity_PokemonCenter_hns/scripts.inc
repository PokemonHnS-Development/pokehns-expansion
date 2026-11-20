BlackthornCity_PokemonCenter_hns_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, BlackthornCity_PokemonCenter_OnTransition
	.byte 0

BlackthornCity_PokemonCenter_OnTransition::
	setrespawn HEAL_LOCATION_BLACKTHORN_CITY_HNS
	end

BlackthornCity_PokemonCenter_EventScript_Gent::
	msgbox BlackthornCity_PokemonCenter1FGentlemanText, MSGBOX_NPC
	end

BlackthornCity_PokemonCenter_EventScript_Twin::
	msgbox BlackthornCity_PokemonCenter1FTwinText, MSGBOX_NPC
	end

BlackthornCity_PokemonCenter1FGentlemanText:
	.string "עמוק בתוך רמת אינדיגו\n"
	.string "הרחוקה נמצאת ליגת הפוקימון.\p"
	.string "שמעתי שהמאמנים הטובים ביותר\n"
	.string "מכל הארץ מתאספים שם.$"

BlackthornCity_PokemonCenter1FTwinText:
	.string "היה מהלך אחד שפשוט הייתי\n"
	.string "חייבת ללמד את הפוקימון שלי.\p"
	.string "אז ביקשתי ממוחק המהלכים\n"
	.string "שיגרום לו לשכוח מהלך מ”נ.$"
