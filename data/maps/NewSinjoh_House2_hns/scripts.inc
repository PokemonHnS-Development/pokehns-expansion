NewSinjoh_House2_hns_MapScripts::
	.byte 0


NewSinjoh_House2_EventScripts_DeskLady::
    lock
	msgbox NewSinjoh_House2_DeskLady_Text MSGBOX_DEFAULT
	release
	end

NewSinjoh_House2_DeskLady_Text::
    .string "Hello little one..\n"
	.string "Welcome to New Sinjoh's\l"
	.string "famous hotsprings..!\p"
	.string "Entry is free and the bathes are mixed,\n"
	.string "just make sure to not track in any\l"
	.string "gunk into the springs and you'll\l"
	.string "be good.$"


NewSinjoh_House2_EventScript_Torkoal::
	lock
	faceplayer
	playmoncry SPECIES_TORKOAL, 0
	msgbox NewSinjoh_Hosue2_Text_CryTorkoal, MSGBOX_DEFAULT
	waitmoncry
        closemessage
	release
	end

NewSinjoh_Hosue2_Text_CryTorkoal:
	.string "Tooor?$"


NewSinjoh_House2_EventScript_BookShelf_North::
    lock
	msgbox NewSinjoh_House2_Text_Bookshelf_North MSGBOX_DEFAULT
	release
	end

NewSinjoh_House2_Text_Bookshelf_North:
    .string "This shelf is lined side to side\n"
	.string "in all the latest travel magazines\l"
	.string "and resturant review guides!$"


NewSinjoh_House2_EventScript_BookShelf_South::
    lock
	msgbox NewSinjoh_House2_Text_Bookshelf_South MSGBOX_DEFAULT
	release
	end

NewSinjoh_House2_Text_Bookshelf_South:
    .string "This shelf is lined side to side\n"
	.string "with books of all sorts\l"
	.string "of diffrent genres and authors!$"