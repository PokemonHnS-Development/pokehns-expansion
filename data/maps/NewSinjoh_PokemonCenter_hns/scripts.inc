NewSinjoh_PokemonCenter_hns_MapScripts::
    map_script MAP_SCRIPT_ON_TRANSITION, NewSinjoh_PokemonCenter_OnTransition
    .byte 0

NewSinjoh_PokemonCenter_OnTransition: 
    setrespawn HEAL_LOCATION_NEW_SINJOH_HNS
    end

NewSinjoh_EventScript_Artist::
	lock
	faceplayer
	goto_if_set FLAG_NEWSINJOH_POKEMONCENTER_ARTIST_GIFT, NewSinjoh_EventScript_ZoomLens_Gotten
	msgbox NewSinjoh_Text_Artist, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, NewSinjoh_EventScript_ZoomLens_No
	msgbox Text_ItemGiveaway, MSGBOX_DEFAULT
	giveitem ITEM_ZOOM_LENS
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_BagIsFull
	setflag FLAG_NEWSINJOH_POKEMONCENTER_ARTIST_GIFT
	release
	end

NewSinjoh_Text_Artist:
	.string "I've found great inspiration in\n"
	.string "this hidden town!\p"
	.string "Don't you think the landscape\n"
    .string "is breathtaking?$"

Text_ItemGiveaway:
	.string "I see!\n"
	.string "You must be an artist as well!\p"
	.string "I happen to have an extra something\n"
	.string "that'll help you notice the tiny\l"
    .string "details of life!$"

NewSinjoh_Text_Artist_No:
    .string "You aren't one of those anti-tourist\n"
    .string "types are you?\n"
	.string "Beauty is meant to be shared.$"

NewSinjoh_EventScript_ZoomLens_No::
	msgbox NewSinjoh_Text_Artist_No, MSGBOX_DEFAULT
	release
	end

NewSinjoh_EventScript_ZoomLens_Gotten::
	msgbox Text_WasGiven_ZoomLensAlready, MSGBOX_DEFAULT
	release
	end

Text_WasGiven_ZoomLensAlready:
	.string "I hope you enjoy that lens!$"

NewSinjoh_EventScript_FemAce::
	msgbox NewSinjoh_Text_FemAce, MSGBOX_NPC
	end

NewSinjoh_Text_FemAce:
	.string "We don't have many modern\n"
	.string "commodities in NEW SINJOH.\p"
	.string "But at least we have this\n"
	.string "POKéMON CENTER.$"
