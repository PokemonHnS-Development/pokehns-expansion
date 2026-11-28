@ Hoenn & Seek 2.0 part 35b (lane A): Ho-Oh, Raikou and Entei, Celebi.
@ src/hoenn_johto_legends.c explains the design; flags and constants are in
@ part 35b's section of include/constants/hoenn_events.h.
@
@ Hooks into HnS (each one line):
@ - TinTower_RoofDay_hns: the state-4 Ho-Oh branch calls HoennSeek_EventScript_HoOhDawnGate.
@ - TinTower_RoofNight_hns: an ON_TRANSITION that hides the state-4 Ho-Oh at night.
@ - EcruteakCity_hns: OnTransition calls HoennSeek_EventScript_EcruteakDawn, and an
@   ON_FRAME entry (VAR_TEMP_1 == 1) plays the rainbow.
@ - map.json script swaps: EUSINE (Celadon Pokémon Center), the middle Tin Tower 1F
@   sage, the Ilex Forest shrine. New bg events: the three soil spots.
@ - src/hoenn_roamer.c notes every Raikou/Entei battle; src/pokenav_radio.c reads
@   EUSINE's notes in OAK's POKéMON TALK intro.

@ ---------------------------------------------------------------- Raikou and Entei

@ EUSINE stays at the Celadon Pokémon Center after the Suicune chase. Once you've
@ caught one of the two roaming beasts, the other runs alone and leaves a trail
@ he can read: he sends his notes to MARY on OAK's POKéMON TALK.
HoennSeek_EventScript_CeladonEusine::
	lock
	faceplayer
	specialvar VAR_RESULT, HoennEusineState
	goto_if_set FLAG_HOENN_EUSINE_NOTES, HoennSeek_EventScript_EusineNotesSent
	goto_if_eq VAR_RESULT, 1, HoennSeek_EventScript_EusineGiveNotes
	goto_if_eq VAR_RESULT, 2, HoennSeek_EventScript_EusineNoTrail
	msgbox Celadon_Text_Eusine1, MSGBOX_DEFAULT
	msgbox HoennSeek_Text_EusineBeastsRoam, MSGBOX_DEFAULT
	release
	end

HoennSeek_EventScript_EusineGiveNotes::
	msgbox HoennSeek_Text_EusineGiveNotes, MSGBOX_DEFAULT
	setflag FLAG_HOENN_EUSINE_NOTES
	release
	end

HoennSeek_EventScript_EusineNotesSent::
	goto_if_ne VAR_RESULT, 1, HoennSeek_EventScript_EusineNoTrail
	msgbox HoennSeek_Text_EusineListen, MSGBOX_DEFAULT
	release
	end

HoennSeek_EventScript_EusineNoTrail::
	msgbox HoennSeek_Text_EusineNoTrail, MSGBOX_DEFAULT
	release
	end

@ ---------------------------------------------------------------- Ho-Oh

@ HnS's state 4 (after the Hall of Fame, or the Pewter grandpa's Rainbow Wing)
@ shows Ho-Oh on the roof every visit. From part 35b it's only there at dawn
@ with every clue in place (HoennHoOhClue).
HoennSeek_EventScript_HoOhDawnGate::
	specialvar VAR_RESULT, HoennHoOhClue
	goto_if_eq VAR_RESULT, HOENN_HOOH_READY, HoennSeek_EventScript_HoOhGateReturn
	setflag FLAG_HIDE_HO_OH
HoennSeek_EventScript_HoOhGateReturn::
	return

@ The night roof is a map of its own with no scripts: never at night.
HoennSeek_EventScript_TinTowerRoofNight::
	goto_if_ne VAR_COMPLETED_HO_OH, 4, HoennSeek_EventScript_TinTowerRoofNightEnd
	setflag FLAG_HIDE_HO_OH
HoennSeek_EventScript_TinTowerRoofNightEnd::
	end

@ The middle sage on Tin Tower 1F names the first missing clue. A player who took
@ Lugia's path never got the CLEAR BELL (the Theater gives it on Ho-Oh's path),
@ so he gives it to anyone who shows the Rainbow Wing ("The bell of tin rings
@ clearly for those under the tower's wing", the Sage Office sign).
HoennSeek_EventScript_TinTowerSage::
	goto_if_ne VAR_COMPLETED_HO_OH, 4, TinTower_1F_EventScript_SageB
	lock
	faceplayer
	checkitem ITEM_CLEAR_BELL
	goto_if_eq VAR_RESULT, FALSE, HoennSeek_EventScript_SageNoBell
HoennSeek_EventScript_SageClue::
	specialvar VAR_RESULT, HoennHoOhClue
	switch VAR_RESULT
	case HOENN_HOOH_NEEDS_PUZZLE, HoennSeek_EventScript_SagePuzzle
	case HOENN_HOOH_NEEDS_BEASTS, HoennSeek_EventScript_SageBeasts
	case HOENN_HOOH_NEEDS_DAWN, HoennSeek_EventScript_SageDawn
	msgbox HoennSeek_Text_SageReady, MSGBOX_DEFAULT
	release
	end

HoennSeek_EventScript_SagePuzzle::
	msgbox HoennSeek_Text_SagePuzzle, MSGBOX_DEFAULT
	release
	end

HoennSeek_EventScript_SageBeasts::
	msgbox HoennSeek_Text_SageBeasts, MSGBOX_DEFAULT
	release
	end

HoennSeek_EventScript_SageDawn::
	msgbox HoennSeek_Text_SageDawn, MSGBOX_DEFAULT
	release
	end

HoennSeek_EventScript_SageNoBell::
	checkitem ITEM_RAINBOW_WING
	goto_if_eq VAR_RESULT, FALSE, HoennSeek_EventScript_SageNoWing
	msgbox HoennSeek_Text_SageGivesBell, MSGBOX_DEFAULT
	giveitem ITEM_CLEAR_BELL
	goto_if_eq VAR_RESULT, FALSE, HoennSeek_EventScript_SageBagFull
	msgbox HoennSeek_Text_SageAfterBell, MSGBOX_DEFAULT
	goto HoennSeek_EventScript_SageClue

HoennSeek_EventScript_SageNoWing::
	msgbox HoennSeek_Text_SageNoWing, MSGBOX_DEFAULT
	release
	end

HoennSeek_EventScript_SageBagFull::
	msgbox gText_TooBadBagIsFull, MSGBOX_DEFAULT
	release
	end

@ The cameo: the first dawn every clue is in place, a rainbow crosses Ecruteak
@ and Ho-Oh flies through it toward the tower (wherever you come in from).
HoennSeek_EventScript_EcruteakDawn::
	goto_if_set FLAG_HOENN_HOOH_RAINBOW, HoennSeek_EventScript_EcruteakDawnEnd
	goto_if_ne VAR_COMPLETED_HO_OH, 4, HoennSeek_EventScript_EcruteakDawnEnd
	specialvar VAR_RESULT, HoennHoOhClue
	goto_if_ne VAR_RESULT, HOENN_HOOH_READY, HoennSeek_EventScript_EcruteakDawnEnd
	setvar VAR_TEMP_1, 1
HoennSeek_EventScript_EcruteakDawnEnd::
	return

HoennSeek_EventScript_EcruteakRainbow::
	lockall
	setvar VAR_TEMP_1, 2
	setflag FLAG_HOENN_HOOH_RAINBOW
	delay 20
	msgbox HoennSeek_Text_RainbowAppears, MSGBOX_DEFAULT
	closemessage
	@ Ho-Oh flies in from the left, two tiles above you, and out on the right
	@ (elevation 13 draws it above roofs and trees).
	getplayerxy VAR_0x8008, VAR_0x8009
	call_if_lt VAR_0x8008, 8, HoennSeek_EventScript_RainbowClampX
	subvar VAR_0x8008, 8
	call_if_lt VAR_0x8009, 2, HoennSeek_EventScript_RainbowClampY
	subvar VAR_0x8009, 2
	setobjectxyperm LOCALID_HOENN_ECRUTEAK_HOOH, VAR_0x8008, VAR_0x8009
	addobject LOCALID_HOENN_ECRUTEAK_HOOH
	setvar VAR_0x8004, 4  @ wing flaps
	setvar VAR_0x8005, 30 @ frames between flaps
	special LoopWingFlapSE
	applymovement LOCALID_HOENN_ECRUTEAK_HOOH, HoennSeek_Movement_HoOhCrosses
	waitmovement 0
	playmoncry SPECIES_HO_OH, CRY_MODE_ENCOUNTER
	waitmoncry
	removeobject LOCALID_HOENN_ECRUTEAK_HOOH
	@ Back off the map, where its template sits (-8,0, never in view), so it can't
	@ respawn when you walk back here. Through a var: a literal -8 would be read
	@ as a var ID.
	setvar VAR_0x8008, -8
	setobjectxyperm LOCALID_HOENN_ECRUTEAK_HOOH, VAR_0x8008, 0
	msgbox HoennSeek_Text_RainbowHoOh, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

HoennSeek_EventScript_RainbowClampX::
	setvar VAR_0x8008, 8
	return

HoennSeek_EventScript_RainbowClampY::
	setvar VAR_0x8009, 2
	return

HoennSeek_Movement_HoOhCrosses:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

HoennSeek_EventScript_CallRainbow::
	setflag FLAG_HOENN_CALL_RAINBOW
	setspeaker HoennSeek_Text_NameBrendan
	pokenavcall HoennSeek_Text_CallRainbow
	goto HoennSeek_EventScript_CallEnd

@ ---------------------------------------------------------------- Celebi

@ Three spots of old soil: by the Ilex Forest shrine, at the foot of the lone tree
@ in Viridian Forest's south, and at the foot of a lone tree in Petalburg Woods'
@ tall grass. They only take a berry while the GS BALL is waiting at the shrine
@ (VAR_AZALEA_TOWN_STATE 9).
HoennSeek_EventScript_SoilIlex::
	setvar VAR_0x8004, HOENN_SOIL_ILEX
	goto HoennSeek_EventScript_ForestSoil

HoennSeek_EventScript_SoilViridian::
	setvar VAR_0x8004, HOENN_SOIL_VIRIDIAN
	goto HoennSeek_EventScript_ForestSoil

HoennSeek_EventScript_SoilPetalburg::
	setvar VAR_0x8004, HOENN_SOIL_PETALBURG
	goto HoennSeek_EventScript_ForestSoil

HoennSeek_EventScript_ForestSoil::
	lockall
	goto_if_ne VAR_AZALEA_TOWN_STATE, 9, HoennSeek_EventScript_SoilPlain
	goto_if_set FLAG_HOENN_SHRINE_OFFERED, HoennSeek_EventScript_SoilPlain
	specialvar VAR_RESULT, HoennForestSoilState
	switch VAR_RESULT
	case HOENN_SOIL_GROWING, HoennSeek_EventScript_SoilGrowing
	case HOENN_SOIL_GROWN, HoennSeek_EventScript_SoilGrown
	case HOENN_SOIL_TAKEN, HoennSeek_EventScript_SoilTaken
	msgbox HoennSeek_Text_SoilAskPlant, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, HoennSeek_EventScript_SoilEnd
	fadescreen FADE_TO_BLACK
	closemessage
	special Bag_ChooseBerry
	waitstate
	goto_if_eq VAR_ITEM_ID, ITEM_NONE, HoennSeek_EventScript_SoilEnd
	removeitem VAR_ITEM_ID
	special HoennForestSoilPlant
	bufferitemname STR_VAR_1, VAR_ITEM_ID
	msgbox HoennSeek_Text_SoilPlanted, MSGBOX_DEFAULT
HoennSeek_EventScript_SoilEnd::
	releaseall
	end

HoennSeek_EventScript_SoilPlain::
	msgbox HoennSeek_Text_SoilPlain, MSGBOX_DEFAULT
	releaseall
	end

HoennSeek_EventScript_SoilGrowing::
	msgbox HoennSeek_Text_SoilGrowing, MSGBOX_DEFAULT
	releaseall
	end

HoennSeek_EventScript_SoilGrown::
	msgbox HoennSeek_Text_SoilGrown, MSGBOX_DEFAULT
	special HoennForestSoilTake
	playfanfare MUS_OBTAIN_BERRY
	message HoennSeek_Text_SoilTookBerry
	waitfanfare
	waitmessage
	waitbuttonpress
	specialvar VAR_RESULT, HoennForestOfferings
	buffernumberstring STR_VAR_1, VAR_RESULT
	goto_if_eq VAR_RESULT, HOENN_SOIL_COUNT, HoennSeek_EventScript_SoilAllThree
	msgbox HoennSeek_Text_SoilCount, MSGBOX_DEFAULT
	releaseall
	end

HoennSeek_EventScript_SoilAllThree::
	msgbox HoennSeek_Text_SoilAllThree, MSGBOX_DEFAULT
	releaseall
	end

HoennSeek_EventScript_SoilTaken::
	msgbox HoennSeek_Text_SoilTaken, MSGBOX_DEFAULT
	releaseall
	end

@ The shrine takes the GS BALL only once the three glowing berries are in its
@ dishes; then HnS's Celebi scene runs as it always did.
HoennSeek_EventScript_IlexShrine::
	goto_if_ne VAR_AZALEA_TOWN_STATE, 9, IlexForest_EventScript_Shrine
	goto_if_set FLAG_HOENN_SHRINE_OFFERED, IlexForest_EventScript_Shrine
	lock
	specialvar VAR_RESULT, HoennForestOfferings
	goto_if_eq VAR_RESULT, HOENN_SOIL_COUNT, HoennSeek_EventScript_ShrineOffer
	msgbox HoennSeek_Text_ShrineDishes, MSGBOX_DEFAULT
	goto_if_eq VAR_RESULT, 0, HoennSeek_EventScript_ShrineEnd
	buffernumberstring STR_VAR_1, VAR_RESULT
	msgbox HoennSeek_Text_ShrineHaveSome, MSGBOX_DEFAULT
HoennSeek_EventScript_ShrineEnd::
	release
	end

HoennSeek_EventScript_ShrineOffer::
	msgbox HoennSeek_Text_ShrineOffer, MSGBOX_DEFAULT
	closemessage
	playse SE_M_PETAL_DANCE
	waitse
	setflag FLAG_HOENN_SHRINE_OFFERED
	goto IlexForest_EventScript_Shrine

@ ---------------------------------------------------------------- texts

HoennSeek_Text_EusineBeastsRoam:
	.string "RAIKOU and ENTEI still roam JOHTO,\n"
	.string "faster than anyone can follow.\p"
	.string "They run side by side, and their\n"
	.string "tracks cross until they're useless.\p"
	.string "If you ever caught one of them, the\n"
	.string "other would run alone. A lone beast\l"
	.string "leaves a trail I could read!$"

HoennSeek_Text_EusineGiveNotes:
	.string "EUSINE: {PLAYER}! You caught one of\n"
	.string "the legendary beasts!\p"
	.string "Then {STR_VAR_1} runs alone now, and\n"
	.string "I can read its trail.\p"
	.string "I'll send my tracking notes to MARY\n"
	.string "at OAK's POKéMON TALK every day.\p"
	.string "Tune in, and she'll tell you where\n"
	.string "{STR_VAR_1} was last seen!$"

HoennSeek_Text_EusineListen:
	.string "EUSINE: MARY reads my notes on\n"
	.string "{STR_VAR_1} at the start of OAK's\l"
	.string "POKéMON TALK. Good hunting!$"

HoennSeek_Text_EusineNoTrail:
	.string "EUSINE: There's no fresh trail for\n"
	.string "me to read right now.\p"
	.string "I'm back visiting my hometown for\n"
	.string "a while.$"

HoennSeek_Text_SagePuzzle:
	.string "The rainbow POKéMON returns only to\n"
	.string "those who know its likeness.\p"
	.string "In the RUINS OF ALPH, a stone panel\n"
	.string "shows HO-OH in pieces. Have you put\l"
	.string "it back together?$"

HoennSeek_Text_SageBeasts:
	.string "Long ago, HO-OH raised three POKéMON\n"
	.string "from the ashes of the BURNED TOWER.\p"
	.string "It will not come down until all\n"
	.string "three have met you: SUICUNE, RAIKOU\l"
	.string "and ENTEI, face to face.$"

HoennSeek_Text_SageDawn:
	.string "You carry the bell, you know its\n"
	.string "likeness, and the three beasts\l"
	.string "know you.\p"
	.string "Now go up at dawn, when the first\n"
	.string "light touches the roof.$"

HoennSeek_Text_SageReady:
	.string "Dawn… The first light is on\n"
	.string "the roof.\p"
	.string "If it is ever coming, it is\n"
	.string "coming now.$"

HoennSeek_Text_SageNoWing:
	.string "The bell of tin rings for those\n"
	.string "under the tower's wing.\p"
	.string "They say an old man in PEWTER keeps\n"
	.string "a feather of rainbow colors…$"

HoennSeek_Text_SageGivesBell:
	.string "That feather… a RAINBOW WING!\p"
	.string "The bell of tin rings for those\n"
	.string "under the tower's wing. This is\l"
	.string "yours now.$"

HoennSeek_Text_SageAfterBell:
	.string "Its sound will carry to the roof.$"

HoennSeek_Text_RainbowAppears:
	.string "The morning sun breaks\n"
	.string "over ECRUTEAK…\p"
	.string "A rainbow arcs across the sky, from\n"
	.string "the hills to the top of TIN TOWER!$"

HoennSeek_Text_RainbowHoOh:
	.string "A great bird of every color flew\n"
	.string "along the rainbow, toward the roof\l"
	.string "of TIN TOWER!$"

HoennSeek_Text_CallRainbow:
	.string "Hi, {PLAYER}! It's BRENDAN.\p"
	.string "The sages in ECRUTEAK reported to\n"
	.string "the LEAGUE this morning, and Dad\l"
	.string "read it to us.\p"
	.string "A rainbow over TIN TOWER at dawn,\n"
	.string "and a bird of every color flying\l"
	.string "into it!\p"
	.string "They said a trainer from out of town\n"
	.string "saw it too. That was you, right?\p"
	.string "Go climb that tower at dawn!$"

HoennSeek_Text_SoilPlain:
	.string "A patch of soft, dark soil in a\n"
	.string "shaft of sunlight.$"

HoennSeek_Text_SoilAskPlant:
	.string "A patch of soft, dark soil in a\n"
	.string "shaft of sunlight. It feels old,\l"
	.string "and somehow kind.\p"
	.string "Plant a BERRY here?$"

HoennSeek_Text_SoilPlanted:
	.string "{PLAYER} planted the {STR_VAR_1} in the\n"
	.string "soft soil.\p"
	.string "A little sprout pushed up at once!$"

HoennSeek_Text_SoilGrowing:
	.string "A little sprout. It sways in\n"
	.string "the sunlight.\p"
	.string "It might be grown by tomorrow.$"

HoennSeek_Text_SoilGrown:
	.string "The sprout has grown into a small\n"
	.string "leafy plant overnight!\p"
	.string "Among its leaves, one BERRY glows\n"
	.string "a soft green…$"

HoennSeek_Text_SoilTookBerry:
	.string "{PLAYER} took the glowing BERRY!$"

HoennSeek_Text_SoilCount:
	.string "That makes {STR_VAR_1} of the three.$"

HoennSeek_Text_SoilAllThree:
	.string "That makes all three! They're meant\n"
	.string "for the ILEX FOREST SHRINE.$"

HoennSeek_Text_SoilTaken:
	.string "A small leafy plant. Its glowing\n"
	.string "BERRY is with you.$"

HoennSeek_Text_ShrineDishes:
	.string "ILEX FOREST SHRINE…\p"
	.string "There's a hole the GS BALL would\n"
	.string "fit in, but the BALL won't settle.\p"
	.string "Three little stone dishes sit\n"
	.string "around it, empty. Words are carved\l"
	.string "under them:\p"
	.string "“Plant where the sun reaches the\n"
	.string "floor of three woods: this one, the\l"
	.string "wood by VIRIDIAN, and PETALBURG's\l"
	.string "wood across the sea.”\p"
	.string "“The protector will know the fruit\n"
	.string "of its woods.”$"

HoennSeek_Text_ShrineHaveSome:
	.string "You have {STR_VAR_1} of the glowing BERRIES.$"

HoennSeek_Text_ShrineOffer:
	.string "{PLAYER} laid the three glowing\n"
	.string "BERRIES in the shrine's dishes.\p"
	.string "A warm wind stirs the leaves of\n"
	.string "ILEX FOREST…$"
