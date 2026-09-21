Route32_PokemonCenter_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route32_PokemonCenter_OnTransition	
	.byte 0

Route32_PokemonCenter_OnTransition::
	setrespawn HEAL_LOCATION_ROUTE_32_HNS
	end

Route32_PokemonCenter_EventScript_Lass::
	lock
	faceplayer
	msgbox Route32_Pokecenter_Text_CooltrainerF, MSGBOX_DEFAULT
	closemessage
	release
	end

Route32_PokemonCenter_EventScript_FishingGuru::
	lock
	faceplayer
	checkitem ITEM_OLD_ROD
	goto_if_eq VAR_RESULT, TRUE, Route32_PokemonCenter_EventScript_FishingGuru3
	msgbox Route32_Pokecenter_Text_FishingGuruQuestion, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE, Route32_PokemonCenter_EventScript_FishingGuru2
	msgbox Route32_Pokecenter_Text_FishingGuruNo, MSGBOX_DEFAULT
	closemessage
	release
	end
Route32_PokemonCenter_EventScript_FishingGuru2::
	msgbox Route32_Pokecenter_Text_FishingGuruYes, MSGBOX_DEFAULT
	giveitem ITEM_OLD_ROD
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	msgbox Route32_Pokecenter_Text_FishingGuruGiveRod, MSGBOX_DEFAULT
	closemessage
	release
	end
Route32_PokemonCenter_EventScript_FishingGuru3::
	msgbox Route32_Pokecenter_Text_FishingGuruAfter, MSGBOX_DEFAULT
	release
	end



Route32_Pokecenter_Text_FishingGuruQuestion:
	.string "Este es un gran sitio para pescar.\p
¿Viste a gente pescando?\n
¿Y tú qué?\p
¿Quieres una de mis CAÑAS?$"

Route32_Pokecenter_Text_FishingGuruYes:
	.string "Je, qué bueno oírlo.\p
¡Ahora también eres pescador!$"

Route32_Pokecenter_Text_FishingGuruGiveRod:
	.string "¡Pescar es genial!\p
Si hay agua, ya sea el mar o\n
un río, prueba tu CAÑA.$"

Route32_Pokecenter_Text_FishingGuruNo:
	.string "Oh. That's rather disappointing…$"

Route32_Pokecenter_Text_FishingGuruAfter:
	.string "Oye, chico. ¿Cómo pican?$"

Route32_Pokecenter_Text_CooltrainerF:
	.string "¿Qué objeto le daré a mi POKéMON?\p"
	.string "Tal vez un objeto que aumente\n"
	.string "el ATQUE…$"

