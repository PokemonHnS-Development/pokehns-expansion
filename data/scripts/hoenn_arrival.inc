@ Hoenn & Seek (part 16b): arriving in Hoenn and the gifts around it.
@ Birch's aide at the Slateport harbor, Birch's Mudkip, Wally at the lab,
@ and Steven's shiny Beldum egg at Silph Co. (replaces HnS's Hoenn starter choice).

@ ---------------------------------------------------------------- Slateport harbor

@ Harbor OnFrame while VAR_HOENN_AIDE_STATE is 0: the aide greets you as you step
@ off the ferry at (8,11). He stands at (9,11) until you have Mudkip.
HoennSeek_EventScript_SlateportAideGreet::
	lockall
	playse SE_PIN
	applymovement LOCALID_SLATEPORT_HARBOR_BIRCH_AIDE, Common_Movement_ExclamationMark
	waitmovement 0
	turnobject LOCALID_PLAYER, DIR_EAST
	turnobject LOCALID_SLATEPORT_HARBOR_BIRCH_AIDE, DIR_WEST
	msgbox HoennSeek_Text_SlateportAideGreet, MSGBOX_DEFAULT
	setvar VAR_HOENN_AIDE_STATE, 1
	releaseall
	end

HoennSeek_EventScript_SlateportAide::
	msgbox HoennSeek_Text_SlateportAideDirections, MSGBOX_NPC
	end

@ ---------------------------------------------------------------- Birch's lab

HoennSeek_EventScript_Birch::
	lock
	faceplayer
	goto_if_set FLAG_HOENN_RECEIVED_MUDKIP, HoennSeek_EventScript_BirchAfter
	msgbox HoennSeek_Text_BirchWelcome, MSGBOX_DEFAULT
	showmonpic SPECIES_MUDKIP, 10, 3
	msgbox HoennSeek_Text_BirchMudkip, MSGBOX_DEFAULT
	hidemonpic
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_MUDKIP
	bufferspeciesname STR_VAR_1, SPECIES_MUDKIP
	givemon SPECIES_MUDKIP, 5
	goto_if_eq VAR_RESULT, MON_CANT_GIVE, HoennSeek_EventScript_BirchNoRoom
	call Common_EventScript_GiftMon
	setflag FLAG_HOENN_RECEIVED_MUDKIP
	msgbox HoennSeek_Text_BirchAfterGift, MSGBOX_DEFAULT
	call HoennSeek_EventScript_BirchGivesNumbers @ part 16d
	release
	end
HoennSeek_EventScript_BirchNoRoom::
	msgbox HoennSeek_Text_BirchNoRoom, MSGBOX_DEFAULT
	release
	end
HoennSeek_EventScript_BirchAfter::
	goto_if_set FLAG_HOENN_BEAT_BM, HoennSeek_EventScript_BirchAfterBM
	goto_if_set FLAG_HOENN_BM_BACK_CALLED, HoennSeek_EventScript_BirchBMBack
	msgbox HoennSeek_Text_BirchAfter, MSGBOX_DEFAULT
	release
	end
HoennSeek_EventScript_BirchBMBack::
	msgbox HoennSeek_Text_BirchBMBack, MSGBOX_DEFAULT
	release
	end
HoennSeek_EventScript_BirchAfterBM::
	msgbox HoennSeek_Text_BirchAfterBM, MSGBOX_DEFAULT
	release
	end

@ Wally visits the lab, then leaves (FLAG_HOENN_HIDE_LAB_WALLY). He waits at the
@ end of Victory Road (part 14).
HoennSeek_EventScript_LabWally::
	lock
	faceplayer
	goto_if_set FLAG_HOENN_STAMP_WALLACE, HoennSeek_EventScript_LabWallyLate
	msgbox HoennSeek_Text_LabWally, MSGBOX_DEFAULT
	goto HoennSeek_EventScript_LabWallyLeave
HoennSeek_EventScript_LabWallyLate::
	msgbox HoennSeek_Text_LabWallyLate, MSGBOX_DEFAULT
HoennSeek_EventScript_LabWallyLeave::
	closemessage
	fadescreen FADE_TO_BLACK
	removeobject VAR_LAST_TALKED
	fadescreen FADE_FROM_BLACK
	release
	end

@ ---------------------------------------------------------------- Silph Co. (Saffron)

@ Replaces SaffronCity_SilphCo_EventScript_Steven (map.json script swap). Same scene
@ and exit as HnS's; the gift is a shiny Beldum egg instead of a Hoenn starter.
HoennSeek_EventScript_SilphSteven::
	lock
	msgbox SaffronCity_SilphCo_Text_Steven1, MSGBOX_DEFAULT
	closemessage
	delay 20
	faceplayer
	delay 20
	playse SE_PIN
	applymovement LOCALID_SILPHCO_STEVEN, Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_SILPHCO_STEVEN
	msgbox HoennSeek_Text_SilphSteven, MSGBOX_DEFAULT
	setvar VAR_0x8004, SPECIES_BELDUM
	specialvar VAR_RESULT, HoennGiveShinyEgg
	goto_if_eq VAR_RESULT, MON_CANT_GIVE, HoennSeek_EventScript_SilphStevenNoRoom
	playfanfare MUS_OBTAIN_ITEM
	message HoennSeek_Text_ReceivedStevenEgg
	waitmessage
	waitfanfare
	call_if_eq VAR_RESULT, MON_GIVEN_TO_PC, HoennSeek_EventScript_SilphEggToPC
	msgbox HoennSeek_Text_SilphStevenAfter, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_FACING, DIR_NORTH, SaffronCity_SilphCo_EventScript_PlayerMove
	applymovement LOCALID_SILPHCO_STEVEN, SaffronCity_SilphCo_Movement_StevenLeave
	waitmovement 0
	playse SE_EXIT
	setflag FLAG_GOT_HOENN_STARTER
	removeobject LOCALID_SILPHCO_STEVEN
	release
	end
HoennSeek_EventScript_SilphEggToPC::
	msgbox HoennSeek_Text_SilphEggToPC, MSGBOX_DEFAULT
	return
HoennSeek_EventScript_SilphStevenNoRoom::
	msgbox HoennSeek_Text_SilphStevenNoRoom, MSGBOX_DEFAULT
	turnobject LOCALID_SILPHCO_STEVEN, DIR_NORTH
	release
	end

@ ---------------------------------------------------------------- text

HoennSeek_Text_SlateportAideGreet:
	.string "Oh! You must be {PLAYER}, from JOHTO!\n"
	.string "The professor said you were coming!\p"
	.string "I'm one of PROF. BIRCH's aides.\n"
	.string "His lab is in LITTLEROOT TOWN.\p"
	.string "Head north on ROUTE 110, then SURF\n"
	.string "west across ROUTE 103 to OLDALE.\p"
	.string "LITTLEROOT is just south of there.\n"
	.string "The professor has something for you!$"

HoennSeek_Text_SlateportAideDirections:
	.string "PROF. BIRCH's lab is in LITTLEROOT.\p"
	.string "North on ROUTE 110, SURF west across\n"
	.string "ROUTE 103 to OLDALE, then south!$"

HoennSeek_Text_BirchWelcome:
	.string "PROF. BIRCH: You're {PLAYER}!\n"
	.string "PROF. OAK told me all about you.\p"
	.string "Welcome to HOENN! I'm BIRCH.\n"
	.string "I study POKéMON out in the field.\p"
	.string "I'd like you to have a POKéMON\n"
	.string "from HOENN, to remember us by.\p"
	.string "My son BRENDAN took TREECKO, and\n"
	.string "NORMAN's daughter MAY took TORCHIC.\p"
	.string "So that leaves this one!$"

HoennSeek_Text_BirchMudkip:
	.string "It's MUDKIP, the WATER type.\n"
	.string "Take good care of it!$"

HoennSeek_Text_BirchNoRoom:
	.string "PROF. BIRCH: Oh, your party and your\n"
	.string "BOXES are full!\p"
	.string "Make some room, and come back for\n"
	.string "MUDKIP.$"

HoennSeek_Text_BirchAfterGift:
	.string "PROF. BIRCH: HOENN has eight GYMS\n"
	.string "and a LEAGUE, just like JOHTO.\p"
	.string "The LEAGUE is in EVER GRANDE CITY,\n"
	.string "far to the east. Enjoy HOENN!$"

HoennSeek_Text_BirchAfter:
	.string "PROF. BIRCH: BRENDAN and MAY are\n"
	.string "in KANTO, training to battle RED.\p"
	.string "They'll be back eventually. They\n"
	.string "always come home hungry!$"

HoennSeek_Text_BirchBMBack:
	.string "PROF. BIRCH: BRENDAN and MAY are\n"
	.string "back! They're waiting outside.\p"
	.string "They've been dying to battle you!$"

HoennSeek_Text_BirchAfterBM:
	.string "PROF. BIRCH: You beat BRENDAN and\n"
	.string "MAY together? Ha! Remarkable.\p"
	.string "Fieldwork has nothing on that!$"

HoennSeek_Text_LabWally:
	.string "WALLY: Oh, hello! You're the trainer\n"
	.string "from JOHTO, aren't you?\p"
	.string "You look really strong. I can tell.\p"
	.string "If you want a real battle, look for\n"
	.string "BRENDAN and MAY. They're the best\l"
	.string "trainers in HOENN.\p"
	.string "They're in KANTO right now,\n"
	.string "though.\p"
	.string "Me? I train at the end of VICTORY\n"
	.string "ROAD. Collect the GYM BADGES first,\l"
	.string "then come find me.\p"
	.string "I know you can do it. See you there!$"

HoennSeek_Text_LabWallyLate:
	.string "WALLY: {PLAYER}! You're the new\n"
	.string "talk of HOENN!\p"
	.string "I'm heading back to VICTORY ROAD.\n"
	.string "Come battle me anytime!$"

HoennSeek_Text_SilphSteven:
	.string "STEVEN: You are… I remember your\n"
	.string "eyes.\p"
	.string "When I see a trainer whose eyes\n"
	.string "twinkle, I always remember.\p"
	.string "I'm STEVEN. I'm from HOENN, far to\n"
	.string "the south.\p"
	.string "Here, take this EGG. The POKéMON\n"
	.string "inside is a little special.\p"
	.string "It shines like a rare stone.\n"
	.string "I think you'll like it.$"

HoennSeek_Text_ReceivedStevenEgg:
	.string "{PLAYER} received an EGG\n"
	.string "from STEVEN!$"

HoennSeek_Text_SilphEggToPC:
	.string "The EGG was sent to the PC.$"

HoennSeek_Text_SilphStevenNoRoom:
	.string "STEVEN: Oh, you have no room for\n"
	.string "it. Come back when you do.$"

HoennSeek_Text_SilphStevenAfter:
	.string "STEVEN: Take good care of it.\p"
	.string "If you ever visit HOENN, maybe\n"
	.string "we'll meet again.$"
