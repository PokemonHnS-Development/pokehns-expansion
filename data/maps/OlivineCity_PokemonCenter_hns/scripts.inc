OlivineCity_PokemonCenter_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, OlivineCity_PokemonCenter_OnTransition
	.byte 0

OlivineCity_PokemonCenter_OnTransition::
	setrespawn HEAL_LOCATION_OLIVINE_CITY_HNS
	end

OlivineCity_EventScript_Fisher::
	lock
	faceplayer
	msgbox OlivineCity_Text_PokecenterFisher, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_EventScript_Teacher::
	lock
	faceplayer
	msgbox OlivineCity_Text_PokecenterTeacher, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_Text_PokecenterFisher:
	.string "המלח בקפה אוליבין הסמוך\n"
	.string "ממש נדיב.\p"
	.string "הוא לימד את הפוקימון שלי\n"
	.string "את המהלך עוצמה.\p"
	.string "עכשיו הוא יכול להזיז סלעים\n"
	.string "גדולים בלי להזיע.$"

OlivineCity_Text_PokecenterTeacher:
	.string "יש מישהו בעיר סיאנווד\n"
	.string "שמעבר לים.\p"
	.string "שמעתי אותו מתרברב כל הזמן\n"
	.string "בפוקימון הנדיר שלו.$"
