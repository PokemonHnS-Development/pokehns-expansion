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
	.string "זה מקום מעולה לדיג.\p"
	.string "ראית את האנשים שדגים פה?\n"
	.string "ומה איתך?\p"
	.string "רוצה אחת מהחכות שלי?$"

Route32_Pokecenter_Text_FishingGuruYes:
	.string "הה, טוב לשמוע.\p"
	.string "עכשיו גם אתה דייג!$"

Route32_Pokecenter_Text_FishingGuruGiveRod:
	.string "דיג זה נהדר!\p"
	.string "בכל מקום שיש בו מים, ים או נחל,\n"
	.string "כדאי לנסות את החכה שלך.$"

Route32_Pokecenter_Text_FishingGuruNo:
	.string "אה. זה די מאכזב…$"

Route32_Pokecenter_Text_FishingGuruAfter:
	.string "היי, ילד. איך הולך עם הדגים?$"

Route32_Pokecenter_Text_CooltrainerF:
	.string "מה כדאי לתת לפוקימון שלי להחזיק?\p"
	.string "אולי פריט שמגביר את כוח ההתקפה…$"

