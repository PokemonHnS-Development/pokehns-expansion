NewSinjoh_PokemonCenter_hns_MapScripts::
    map_script MAP_SCRIPT_ON_TRANSITION, NewSinjoh_PokemonCenter_OnTransition
    .byte 0

NewSinjoh_PokemonCenter_OnTransition: 
    setrespawn HEAL_LOCATION_NEW_SINJOH_HNS
    end

NewSinoh_EventScript_Nurse::
    setvar VAR_0x800B, 1
    call Common_EventScript_PkmnCenterNurse
    waitmessage
    waitbuttonpress
    release
    end

NewSinjoh_EventScript_Artist::
	lock
	faceplayer
    goto_if_set FLAG_NEWSINJOH_POKEMONCENTER_ARTIST_GIFT, Script_HasZoomLensAlready
	msgbox NewSinjoh_Text_Artist, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, TRUE, NewSinjoh_PokemonCenter_EventScript_ArtistYes
    msgbox NewSinjoh_Text_Artist_No
	closemessage
	release
	end

NewSinjoh_Text_Artist:
	.string "Don't you think the area around\n"
    .string "here is breathtaking?$"

NewSinjoh_Text_Artist_No:
	.string "Your life must be pretty borning then\n"
    .string "if this wonderful winter wonderland\l"
    .string "doesn't spark your imagination..$"
	
NewSinjoh_PokemonCenter_EventScript_ArtistYes::
	goto_if_set FLAG_NEWSINJOH_POKEMONCENTER_ARTIST_GIFT, NewSinjoh_EventScript_ZoomLens_Gotten
	msgbox Text_ItemGiveaway2, MSGBOX_DEFAULT
	checkitem ITEM_ZOOM_LENS, 1
	compare VAR_RESULT, 1
	goto_if_ge Script_HasZoomLensAlready
	msgbox Text_GivingLens, MSGBOX_DEFAULT
	giveitem ITEM_ZOOM_LENS, 1
	compare VAR_RESULT, 0
	goto_if_eq Script_BagMightBeFull
	setflag FLAG_NEWSINJOH_POKEMONCENTER_ARTIST_GIFT
	release
	end

Script_HasZoomLensAlready::
	msgbox Text_HasZoomLensAlready, MSGBOX_DEFAULT
	release
	end

Script_BagMightBeFull::
	msgbox Text_BagIsFull, MSGBOX_DEFAULT
	release
	end

Text_ItemGiveaway2:
	.string "I see! You must be an artist as well!\n"
	.string "I happen to have an extra something\l"
	.string "that'll help you notice the tiny details\l"
    .string "of life!$"

Text_GivingLens:
	.string "Here!\n"
    .string "Take this friend!$"

Text_HasZoomLensAlready:
	.string "Oh you already have one?\n"
	.string "I'll hold onto this for now\l"
    .string "until you might need it.$"

Text_BagMightBeFull:
	.string "Your BAG looks pretty packed there.\n"
	.string "Why don't you make space first?$"

NewSinjoh_EventScript_ZoomLens_Got::
    msgbox Text_ItemGiveaway, MSGBOX_DEFAULT 
	msgbox Text_HasZoomLensAlready, MSGBOX_DEFAULT
	release
	end


Text_WasGiven_ZoomLensAlready:
	.string "I hope you enjoy those lenses!$"

NewSinjoh_EventScript_ZoomLens_Gotten::
	msgbox Text_WasGiven_ZoomLensAlready, MSGBOX_DEFAULT
	release
	end

NewSinjoh_EventScript_FemAce::
	lock
	faceplayer
	msgbox NewSinjoh_Text_FemAce, MSGBOX_DEFAULT
	closemessage
	release
    face_right
	end

	NewSinjoh_Text_FemAce:
	.string "There's so many incredible POKéMON here!\p"
	.string "I saw a tall SNEASLE on Route 49\n"
	.string "the other day!$"

NewSinjoh_EventScript_GameboyKid1::
	lock
	msgbox NewSinjoh_Text_GameboyKid1, MSGBOX_DEFAULT
	closemessage
	release
	end

	NewSinjoh_Text_GameboyKid1:
	.string "He must be cheating!\p"
	.string "There is no way he can move\n"
	.string "blocks that fast!$"

NewSinjoh_EventScript_GameboyKid2::
	lock
	faceplayer
	msgbox NewSinjoh_Text_GameboyKid2, MSGBOX_DEFAULT
	closemessage
	release
	end

	NewSinjoh_Text_GameboyKid2:
	.string "Heh....\p"
	.string "Don't tell him but I am\n"
	.string "actually using save states\l"
    .string "so that i never miss a drop!\p"
    .string "It's not cheating if it's RETRO!$"

Script_Chansey::
	lock
	faceplayer
	playmoncry SPECIES_CHANSEY, 0
	msgbox Text_CryChansey, MSGBOX_DEFAULT
	waitmoncry
        closemessage
	release
	end

Text_CryChansey:
	.string "Chan Chan!$"

Script_NewSinjoh_PokemonCenter_LeftBookshelf::
	lock
	faceplayer
	msgbox Text_LeftBookShelf, MSGBOX_DEFAULT
	release
	end

Text_LeftBookShelf:
	.string "This shelf is full of travel magazines!\p"
	.string "Welp! Better get going.$"

Script_NewSinjoh_PokemonCenter_RightBookshelf::
	lock
	faceplayer
	msgbox Text_RightBookShelf, MSGBOX_DEFAULT
	release
	end

Text_RightBookShelf:
	.string "This shelf is full of Manga!\p"
    .string "The one about a boy drilling\n"
    .string "through the heavens intrests you.\p"
	.string "Welp! Better get going for now.$"

NewSinjoh_EventScript_SleepingTrainer::
	lock
	msgbox NewSinjoh_Text_SleepingTrainer, MSGBOX_DEFAULT
	closemessage
	release
	end

	NewSinjoh_Text_SleepingTrainer:
	.string "Zzzzzz....\n"
	.string "ZzzZzzz...\p"
	.string "She appears to be sleeping!\l"
    .string "Best not to wake her up!$"

Script_NewSinjoh_PokemonCenter_Charizard::
	lock
	faceplayer
	playmoncry SPECIES_CHARIZARD, 0
	msgbox Text_CryCharizard, MSGBOX_DEFAULT
	waitmoncry
        closemessage
	release
	end

Text_CryCharizard:
	.string "Graaayh!$"


Script_NewSinjoh_PokemonCenter_Juggler::
	lock
	faceplayer
	msgbox Text_NewSinjoh_PokemonCenter_Juggler, MSGBOX_DEFAULT
	release
	end

Text_NewSinjoh_PokemonCenter_Juggler:
	.string "That CHARIZARD over there\n"
    .string "actually belongs to Nurse Joy!\p"
	.string "She lets it roam around\n"
    .string "to help keep this place\l"
    .string "nice and warm!$"

