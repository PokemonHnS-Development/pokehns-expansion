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

NewSinjoh_PokemonCenter_EventScript_Skiier::
	lock
	faceplayer
	msgbox NewSinjoh_PokemonCenter_Text_Skiier, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_NEWSINJOH_POKEMONCENTER_SKIIER, DIR_NORTH
	release
	end

NewSinjoh_PokemonCenter_hns_Map::
	lockall
	setvar VAR_0x8000, 1 @ SCREENSHOT_SINJOH_MAP
	msgbox NewSinjoh_PokemonCenter_hns_Text_0, MSGBOX_DEFAULT
	closemessage
	callnative OpenScreenshotsFromScript
	waitstate
	releaseall
	end

NewSinjoh_PokemonCenter_Text_Skiier:
	.string "La nieve dificulta mucho el\n"
	.string "recorrido por aquí.\p"
	.string "Todo se ve igual.\p"
	.string "¡Así que este mapa ayuda mucho!\p"
	.string "¡Qué región tan hermosa!$"

NewSinjoh_Text_Artist:
	.string "¡He hallado mucha inspiración en\n"
	.string "este pueblo oculto!\p"
	.string "¿No crees que el paisaje\n"
    .string "es impresionante?$"

Text_ItemGiveaway:
	.string "¡Ya veo!\n"
	.string "¡Tú también debes ser artista!\p"
	.string "Resulta que tengo algo extra\n"
	.string "¡Eso te ayudará a notar los\l"
    .string "pequeños detalles de la vida!$"

NewSinjoh_Text_Artist_No:
    .string "No serás de esos tipos que\n"
    .string "odian a los turistas, ¿verdad?\n"
	.string "La belleza debe ser compartida.$"

NewSinjoh_EventScript_ZoomLens_No::
	msgbox NewSinjoh_Text_Artist_No, MSGBOX_DEFAULT
	release
	end

NewSinjoh_EventScript_ZoomLens_Gotten::
	msgbox Text_WasGiven_ZoomLensAlready, MSGBOX_DEFAULT
	release
	end

Text_WasGiven_ZoomLensAlready:
	.string "¡Espero que disfrutes el lente!$"

NewSinjoh_EventScript_FemAce::
	msgbox NewSinjoh_Text_FemAce, MSGBOX_NPC
	end

NewSinjoh_Text_FemAce:
	.string "No tenemos muchos artículos\n"
	.string "modernos en NUEVA SINJOH.\p"
	.string "Pero al menos tenemos este\n"
	.string "CENTRO POKéMON.$"


NewSinjoh_PokemonCenter_hns_Text_0:
	.string "{PLAYER} miró más de cerca el\n"
	.string "mapa de SINJOH.$"
