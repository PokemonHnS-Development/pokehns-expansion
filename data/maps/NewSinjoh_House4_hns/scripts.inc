NewSinjoh_House4_hns_MapScripts::
	.byte 0

NewSinjoh_Script_Resturant::
	lock
	faceplayer
	message NewSinjoh_Text_ResturantGreeting
	waitmessage
	pokemart NewSinjoh_Pokemart_Resturant
	msgbox NewSinjoh_Text_ResturantEnd, MSGBOX_DEFAULT
	release
	end

	.align 2
NewSinjoh_Pokemart_Resturant:
	.2byte ITEM_YACHE_BERRY
    .2byte ITEM_LANSAT_BERRY
    .2byte ITEM_ROWAP_BERRY
    .2byte ITEM_BERRY_JUICE
	.2byte ITEM_SODA_POP
	.2byte ITEM_LAVA_COOKIE
	.2byte ITEM_HEAL_POWDER
	.2byte ITEM_LEEK
	.2byte ITEM_BIG_ROOT
	.2byte ITEM_LEFTOVERS
	.2byte ITEM_NONE
	release
	end

NewSinjoh_Text_ResturantGreeting:
	.string "H-hello! Welcome to our Cafe!\n"
	.string "How can I help you today?$"

NewSinjoh_Text_ResturantEnd:
	.string "Please come again!$"

NewSinjoh_EventScript_ENGIE::
	lock
	faceplayer
	msgbox NewSinjoh_Text_ENGIE, MSGBOX_DEFAULT
	closemessage
	release
    face_right
	end

	NewSinjoh_Text_ENGIE:
	.string "This food hits the spot after\n"
	.string "a hard days work!$"

NewSinjoh_EventScript_BaldingMan::
	lock
	faceplayer
	msgbox NewSinjoh_Text_BaldingMan, MSGBOX_DEFAULT
	closemessage
	release
    face_right
	end

	NewSinjoh_Text_BaldingMan:
	.string "I heard that Serana moved her\n"
	.string "cafe into this brush to hide from\l"
	.string "tourists.\l"
	.string "Her little sister still isn't used\l"
	.string "to serving people yet..\p"
	.string "So by having only regulars\n"
	.string "show up, she could learn at\l"
	.string "her own pace!$"

NewSinjoh_EventScript_FemDoctor::
	lock
	faceplayer
	msgbox NewSinjoh_Text_FemDoctor, MSGBOX_DEFAULT
	closemessage
	release
    face_right
	end

	NewSinjoh_Text_FemDoctor:
	.string "Hello~.\p"
	.string "This drink is so goood~!\n"
	.string ".......\p"
	.string "Actually...you look a little\l"
	.string "to young..$"

NewSinjoh_EventScript_Girl::
	lock
	faceplayer
	msgbox NewSinjoh_Text_Girl, MSGBOX_DEFAULT
	closemessage
	release
	end

	NewSinjoh_Text_Girl:
	.string "Please forgive my older Sister..\p"
	.string "Outside of Nurse Joy she's our\n"
	.string "town's only Doctor.\l"
	.string "As you can imagine, she doesn't\l"
	.string "get to relax very often..$"

NewSinjoh_EventScript_Gentleman::
	lock
	faceplayer
	msgbox NewSinjoh_Text_Gentleman, MSGBOX_DEFAULT
	closemessage
	release
    face_right
	end

	NewSinjoh_Text_Gentleman:
	.string "There you go SCIZOR..\n"
	.string "Enjoy your food, you've earned it.$"

Script_Scizor::
	lock
	playmoncry SPECIES_SCIZOR, 0
	msgbox Text_CryScizor, MSGBOX_DEFAULT
	waitmoncry
        closemessage
	release
	end

Text_CryScizor:
	.string "Shraah!$"

Script_Raichu::
	lock
	faceplayer
	playmoncry SPECIES_RAICHU, 0
	msgbox Text_CryRaichu, MSGBOX_DEFAULT
	waitmoncry
        closemessage
	release
	face_right
	end

Text_CryRaichu:
	.string "Rhaai! Rhaii!$"

