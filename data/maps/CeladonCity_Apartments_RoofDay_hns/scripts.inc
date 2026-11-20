CeladonCity_Apartments_RoofDay_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, CeladonCity_Apartments_RoofDay_OnTransition
	.byte 0

CeladonCity_Apartments_RoofDay_OnTransition:
	call_if_set FLAG_DAY_POKEMON, CeladonCity_Apartments_RoofDay_EventScript_SetNight
	call_if_unset FLAG_DAY_POKEMON, CeladonCity_Apartments_RoofDay_EventScript_SetDay
	end

CeladonCity_Apartments_RoofDay_EventScript_SetNight::
	setmaplayoutindex LAYOUT_CELADON_CITY_APARTMENTS_ROOF_NIGHT_HNS
	return

CeladonCity_Apartments_RoofDay_EventScript_SetDay::
	setmaplayoutindex LAYOUT_CELADON_CITY_APARTMENTS_ROOF_DAY_HNS
	return

CeladonCity_Apartments_RoofDay_EventScript_Fisher::
	msgbox CeladonMansionRoof_Text_Fisher, MSGBOX_NPC
	end

CeladonCity_Apartments_RoofDay_EventScript_Sign::
	msgbox CeladonMansionRoof_Text_Graffiti, MSGBOX_NPC
	end

CeladonMansionRoof_Text_Fisher:
	.string "מקומות גבוהים - אני פשוט מת עליהם!\p"
	.string "נראה לי שהדבר היחיד שאוהב גבהים\n"
	.string "כמוני זה עשן!$"

CeladonMansionRoof_Text_Graffiti:
	.string "יש גרפיטי על הקיר…\p"
	.string "{PLAYER} הוסיף לציור שפם!$"
