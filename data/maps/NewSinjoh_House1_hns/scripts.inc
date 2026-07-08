NewSinjoh_House1_hns_MapScripts::
	.byte 0


NewSinjoh__House1_EventScripts_Elizabeth_2ndEncounter::
    lock
	faceplayer
	goto_if_set FLAG_NEWSINJOH_HOUSE1_ELIZABETH_GAVEWOOPER, NewSinjoh_House1_EventScript_Elizabeth_3rdEncounter
    msgbox NewSinjoh_House1_Text_Looking4Celebi MSGBOX_DEFAULT
    checkspecies SPECIES_CELEBI
    goto_if VAR_RESULT, NewSinjoh_House1_EventScript_GiveWooperPaldea
    msgbox NewSinjoh_House1_Text_NicePokemonButNotCelebi MSGBOX_DEFAULT
    release
    end

NewSinjoh_House1_EventScript_GiveWooperPaldea::
    applymovement LOCALID_NEWSINJOH_HOUSE1_ELIZABETH, Common_Movement_ExclamationMark
	playse SE_PIN
	waitse
	waitmovement
    msgbox NewSinjoh_House1_OffersWooper MSGBOX_DEFAULT
    getpartysize
	compare VAR_RESULT, 6
    goto_if_eq VAR_RESULT, PARTY_SIZE, NewSinhoh_EventScript_House1_PlayerHasFullParty
    givemon SPECIES_WOOPER_PALDEA, 5, ITEM_FRESH_START_MOCHI
    playfanfare MUS_OBTAIN_ITEM
    msgbox NewSinjoh_House1_Text_TakeCareOfWooper MSGBOX_DEFAULT
    waitfanfare
	setflag FLAG_NEWSINJOH_HOUSE1_ELIZABETH_GAVEWOOPER
    release
    end

NewSinhoh_EventScript_House1_PlayerHasFullParty::
	msgbox NewSinjoh_House1_Text_PlayerHasFullParty MSGBOX_DEFAULT
	release
	end



NewSinjoh_House1_Text_Looking4Celebi:
    .string "Hey there Champion!\p"
	.string "You caught me while I was playing\n"
	.string "a rougelike I found online!\l"
	.string "Anyways, that's enough about that..\p"
	.string "I have a request for someone as\n"
	.string "well traveled as you are.\l"
	.string "You see, my favorite POKEMON in the\l"
	.string "whole world just so happens to be\l"
	.string "the mythical POKEMON known as Celebi.\p"
	.string "If you happen to have one, would\n"
	.string "you mind showing it to me?$"

NewSinjoh_House1_Text_NicePokemonButNotCelebi:
    .string "That's a very wonderful POKEMON\n"
	.string "you have there but that's\l"
	.string "not exactly what i was looking for..$"

 
NewSinjoh_House1_OffersWooper:
    .string "That's it!! That's a real living CELEBI!!\p"
	.string "Thank you show much for bringing it\l"
	.string "all the way up north for me to see.\p"
    .string "My girlfriend happened to catch\n"
	.string "a few too many of these during\l"
	.string "her trip to a far away reigon..\p"
    .string "Please take this special WOOPER as thanks {PLAYER}.$"

NewSinjoh_House1_Text_TakeCareOfWooper:
    .string "Take good care of that WOOPER for me okay?$"

NewSinjoh_House1_Text_PlayerHasFullParty:
    .string "Oh! You appear to have a full party already..\p"
	.string "Please make some space first\n"
	.string "and come back soon!$"

NewSinjoh_House1_EventScript_Elizabeth_3rdEncounter::
	msgbox NewSinjoh_House1_Text_GoodToSeeYouAgain MSGBOX_DEFAULT
	release
	end

NewSinjoh_House1_Text_GoodToSeeYouAgain:
    .string "It's good to see you again {PLAYER}\n"
	.string "How have you been treating that WOOPER?\p"
	.string "Good i hope?$"

NewSinjoh_House1_Bookshelf::
    lock
	msgbox NewSinjoh_House1_Bookshelf_Text MSGBOX_DEFAULT
	release
	end

NewSinjoh_House1_Bookshelf_Text:
    .string "It's a shelf packed full of\n"
	.string "games and manga!$"

Snowswept_EventScript_Item_SKYPLATE::
    finditem ITEM_SKY_PLATE
    addvar VAR_PLATECOUNTER, 1
    end

NewSinjoh_House1_Eevee::
    lock
	faceplayer
	playmoncry SPECIES_EEVEE, 0
	msgbox NewSinjoh_House1_Text_Eevee_Cry, MSGBOX_DEFAULT
	waitmoncry
    closemessage
	release
	end

NewSinjoh_House1_Text_Eevee_Cry:
    .string "Vee Vee?$"