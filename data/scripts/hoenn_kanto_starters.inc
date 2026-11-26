@ Hoenn & Seek 2.0 part 16: Kanto starters A (plan section 5).
@
@ Bulbasaur and Charmander each have an event of their own (Squirtle's Squad
@ is part 17). No gate: they're there as soon as you can reach Cerulean.
@ Each joins you at Lv 5, like the other gift starters:
@   Bulbasaur   holds an Everstone (it refused to evolve)
@   Charmander  max friendship (it waited for someone)
@ Charmander's old trainer waits outside the Cerulean Gym once it's with you,
@ for one battle (TRAINER_LEROY, renamed in data/hoenn/trainer_parties.party).

@ ---- Bulbasaur: the hidden garden behind Bill's house, mornings ------------
@ Route25_Garden_hoenn. Its way in is a gap in the trees at the top of Route
@ 25's fenced cape overlook (98-99, 9): stepping there warps you in.
@ The garden's family: a Venusaur and three Bulbasaur (FAMILY), three more
@ Bulbasaur that evolve in the first ceremony (YOUNG), the Ivysaur they
@ became (IVYSAUR), and the one that hid (BULBASAUR), which joins you. The
@ hide flags are decided on every arrival.

HoennSeek_EventScript_Route25ToGarden::
	getplayerxy VAR_0x8004, VAR_0x8005
	subvar VAR_0x8004, 88
	playse SE_EXIT
	warpsilent MAP_ROUTE25_GARDEN_HOENN, VAR_0x8004, 14
	waitstate
	end

HoennSeek_EventScript_GardenExit::
	getplayerxy VAR_0x8004, VAR_0x8005
	addvar VAR_0x8004, 88
	playse SE_EXIT
	warpsilent MAP_ROUTE25_HNS, VAR_0x8004, 10
	waitstate
	end

HoennSeek_EventScript_GardenOnTransition::
	setflag FLAG_HOENN_HIDE_GARDEN_FAMILY
	setflag FLAG_HOENN_HIDE_GARDEN_YOUNG
	setflag FLAG_HOENN_HIDE_GARDEN_IVYSAUR
	setflag FLAG_HOENN_HIDE_GARDEN_BULBASAUR
	gettimeofday
	goto_if_ne VAR_0x8000, HOENN_TIME_MORNING, HoennSeek_EventScript_KantoStarterEnd
	clearflag FLAG_HOENN_HIDE_GARDEN_FAMILY
	call_if_unset FLAG_HOENN_BULBASAUR_DONE, HoennSeek_EventScript_GardenShowHider
	goto_if_set FLAG_HOENN_BULBASAUR_SCENE, HoennSeek_EventScript_GardenShowIvysaur
	clearflag FLAG_HOENN_HIDE_GARDEN_YOUNG
	setvar VAR_TEMP_1, 1
	end
HoennSeek_EventScript_GardenShowHider:
	clearflag FLAG_HOENN_HIDE_GARDEN_BULBASAUR
	return
HoennSeek_EventScript_GardenShowIvysaur:
	clearflag FLAG_HOENN_HIDE_GARDEN_IVYSAUR
HoennSeek_EventScript_KantoStarterEnd::
	end

@ Trigger tiles (row 13, armed by VAR_TEMP_1): the ceremony, once. Three of
@ the young evolve in the Venusaur's pollen; the one at the edge hides from it.
HoennSeek_EventScript_GardenCeremony::
	lockall
	setvar VAR_TEMP_1, 0
	setflag FLAG_HOENN_BULBASAUR_SCENE
	special SpawnCameraObject
	applymovement OBJ_EVENT_ID_CAMERA, HoennSeek_Movement_CameraUp4
	waitmovement 0
	msgbox HoennSeek_Text_GardenArrive, MSGBOX_DEFAULT
	closemessage
	playmoncry SPECIES_VENUSAUR, CRY_MODE_NORMAL
	waitmoncry
	playse SE_M_PETAL_DANCE
	msgbox HoennSeek_Text_GardenPollen, MSGBOX_DEFAULT
	closemessage
	waitse
	clearflag FLAG_HOENN_HIDE_GARDEN_IVYSAUR
	setvar VAR_0x8004, LOCALID_HOENN_GARDEN_YOUNG_1
	setvar VAR_0x8005, LOCALID_HOENN_GARDEN_IVYSAUR_1
	call HoennSeek_EventScript_GardenEvolve
	setvar VAR_0x8004, LOCALID_HOENN_GARDEN_YOUNG_2
	setvar VAR_0x8005, LOCALID_HOENN_GARDEN_IVYSAUR_2
	call HoennSeek_EventScript_GardenEvolve
	setvar VAR_0x8004, LOCALID_HOENN_GARDEN_YOUNG_3
	setvar VAR_0x8005, LOCALID_HOENN_GARDEN_IVYSAUR_3
	call HoennSeek_EventScript_GardenEvolve
	playmoncry SPECIES_IVYSAUR, CRY_MODE_NORMAL
	waitmoncry
	msgbox HoennSeek_Text_GardenEvolved, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_HOENN_GARDEN_BULBASAUR, HoennSeek_Movement_KantoStarterHop
	waitmovement 0
	msgbox HoennSeek_Text_GardenHider, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_CAMERA, HoennSeek_Movement_CameraDown4
	waitmovement 0
	special RemoveCameraObject
	releaseall
	end

@ VAR_0x8004 = the young Bulbasaur, VAR_0x8005 = the Ivysaur in its place.
HoennSeek_EventScript_GardenEvolve:
	applymovement VAR_0x8004, HoennSeek_Movement_KantoStarterHop
	waitmovement 0
	playse SE_M_MORNING_SUN
	removeobject VAR_0x8004
	addobject VAR_0x8005
	waitse
	return

HoennSeek_EventScript_GardenVenusaur::
	lock
	faceplayer
	playmoncry SPECIES_VENUSAUR, CRY_MODE_NORMAL
	msgbox HoennSeek_Text_GardenVenusaurTalk, MSGBOX_DEFAULT
	waitmoncry
	release
	end

HoennSeek_EventScript_GardenBulbasaurFamily::
	lock
	faceplayer
	playmoncry SPECIES_BULBASAUR, CRY_MODE_NORMAL
	msgbox HoennSeek_Text_GardenBulbasaurTalk, MSGBOX_DEFAULT
	waitmoncry
	release
	end

HoennSeek_EventScript_GardenIvysaur::
	lock
	faceplayer
	playmoncry SPECIES_IVYSAUR, CRY_MODE_NORMAL
	msgbox HoennSeek_Text_GardenIvysaurTalk, MSGBOX_DEFAULT
	waitmoncry
	release
	end

@ The one that hid joins you, holding an Everstone.
HoennSeek_EventScript_GardenBulbasaur::
	lock
	faceplayer
	playmoncry SPECIES_BULBASAUR, CRY_MODE_NORMAL
	msgbox HoennSeek_Text_BulbasaurJoins, MSGBOX_DEFAULT
	waitmoncry
	bufferspeciesname STR_VAR_1, SPECIES_BULBASAUR
	givemon SPECIES_BULBASAUR, 5, ITEM_EVERSTONE
	goto_if_eq VAR_RESULT, MON_CANT_GIVE, HoennSeek_EventScript_KantoStarterNoRoom
	setflag FLAG_HOENN_BULBASAUR_DONE
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_BULBASAUR
	call Common_EventScript_GiftMon
	removeobject VAR_LAST_TALKED
	release
	end

@ ---- Charmander: waiting in the rain at the foot of Nugget Bridge ----------
@ Route 24, evenings and nights (HnS's evening is only 6-7 PM). Its trainer
@ told it to wait there and never came back. While it waits, Route 24 rains.
@ Shield it and you rush it to the Cerulean Pokémon Center, where it chooses
@ you (VAR_HOENN_CHARMANDER_STATE 1 plays that scene from the Center's frame
@ table, one hook line in HnS's map script).

HoennSeek_EventScript_Route24OnTransition::
	setflag FLAG_HOENN_HIDE_CHARMANDER
	goto_if_ne VAR_HOENN_CHARMANDER_STATE, 0, HoennSeek_EventScript_KantoStarterReturn
	gettimeofday
	goto_if_lt VAR_0x8000, HOENN_TIME_EVENING, HoennSeek_EventScript_KantoStarterReturn
	clearflag FLAG_HOENN_HIDE_CHARMANDER
	setweather WEATHER_RAIN
HoennSeek_EventScript_KantoStarterReturn::
	return

HoennSeek_EventScript_Charmander::
	lock
	faceplayer
	playmoncry SPECIES_CHARMANDER, CRY_MODE_WEAK
	msgbox HoennSeek_Text_CharmanderWaiting, MSGBOX_DEFAULT
	waitmoncry
	msgbox HoennSeek_Text_CharmanderShield, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, HoennSeek_EventScript_CharmanderKeepsWaiting
	msgbox HoennSeek_Text_CharmanderShielded, MSGBOX_DEFAULT
	closemessage
	setvar VAR_HOENN_CHARMANDER_STATE, 1
	fadescreen FADE_TO_BLACK
	removeobject VAR_LAST_TALKED
	warpsilent MAP_CERULEAN_CITY_POKEMON_CENTER_HNS, 7, 4
	waitstate
	end
HoennSeek_EventScript_CharmanderKeepsWaiting:
	msgbox HoennSeek_Text_CharmanderKeepsWaiting, MSGBOX_DEFAULT
	release
	end

HoennSeek_CeruleanPC_OnFrame::
	map_script_2 VAR_HOENN_CHARMANDER_STATE, 1, HoennSeek_EventScript_CharmanderHealed
	.2byte 0

HoennSeek_EventScript_CharmanderHealed::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceUp
	waitmovement 0
	msgbox HoennSeek_Text_NurseCharmander, MSGBOX_DEFAULT
	closemessage
	playfanfare MUS_HEAL
	waitfanfare
	playmoncry SPECIES_CHARMANDER, CRY_MODE_NORMAL
	waitmoncry
	msgbox HoennSeek_Text_NurseCharmanderHealed, MSGBOX_DEFAULT
	bufferspeciesname STR_VAR_1, SPECIES_CHARMANDER
	givemon SPECIES_CHARMANDER, 5
	goto_if_eq VAR_RESULT, MON_CANT_GIVE, HoennSeek_EventScript_CharmanderNoRoom
	special HoennMaxFriendshipOfGift
	setvar VAR_HOENN_CHARMANDER_STATE, 2
	setflag FLAG_HOENN_CHARMANDER_DONE
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_CHARMANDER
	call Common_EventScript_GiftMon
	releaseall
	end
@ Nowhere to put it: it goes back to the bridge to wait (there next evening).
HoennSeek_EventScript_CharmanderNoRoom:
	setvar VAR_HOENN_CHARMANDER_STATE, 0
	msgbox HoennSeek_Text_CharmanderNoRoom, MSGBOX_DEFAULT
	releaseall
	end

@ Its old trainer, outside the Cerulean Gym from the first visit after it
@ joined you, until you beat him.
HoennSeek_EventScript_CeruleanOnTransition::
	setflag FLAG_HOENN_HIDE_CHARMANDER_TRAINER
	goto_if_unset FLAG_HOENN_CHARMANDER_DONE, HoennSeek_EventScript_KantoStarterReturn
	goto_if_set FLAG_HOENN_CHARMANDER_TRAINER_BEATEN, HoennSeek_EventScript_KantoStarterReturn
	clearflag FLAG_HOENN_HIDE_CHARMANDER_TRAINER
	return

HoennSeek_EventScript_CharmanderTrainer::
	lock
	faceplayer
	msgbox HoennSeek_Text_CharmanderTrainerIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_LEROY, HoennSeek_Text_CharmanderTrainerDefeat
	msgbox HoennSeek_Text_CharmanderTrainerAfter, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_HOENN_CHARMANDER_TRAINER_BEATEN
	fadescreen FADE_TO_BLACK
	removeobject VAR_LAST_TALKED
	fadescreen FADE_FROM_BLACK
	release
	end

@ ---- Shared ------------------------------------------------------------------

HoennSeek_EventScript_KantoStarterNoRoom::
	msgbox HoennSeek_Text_StarterNoRoom, MSGBOX_DEFAULT
	release
	end

HoennSeek_Movement_KantoStarterHop:
	jump_in_place_down
	step_end

HoennSeek_Movement_CameraUp4:
	walk_slow_up
	walk_slow_up
	walk_slow_up
	walk_slow_up
	step_end
HoennSeek_Movement_CameraDown4:
	walk_slow_down
	walk_slow_down
	walk_slow_down
	walk_slow_down
	step_end

@ ---- Text ---------------------------------------------------------------------

HoennSeek_Text_GardenArrive::
	.string "A hidden garden…\p"
	.string "BULBASAUR have gathered in a\n"
	.string "ring around a VENUSAUR.$"

HoennSeek_Text_GardenPollen::
	.string "The VENUSAUR's flower opens\n"
	.string "wide and scatters golden pollen.\p"
	.string "The BULBASAUR's bulbs are\n"
	.string "starting to glow!$"

HoennSeek_Text_GardenEvolved::
	.string "Three of the BULBASAUR evolved\n"
	.string "into IVYSAUR!$"

HoennSeek_Text_GardenHider::
	.string "One BULBASAUR kept to the edge\n"
	.string "of the garden, out of the pollen.\p"
	.string "It doesn't want to evolve. It's\n"
	.string "peeking over at you…$"

HoennSeek_Text_GardenVenusaurTalk::
	.string "VENUSAUR: Saaaur…\p"
	.string "The sweet smell of its flower\n"
	.string "fills the whole garden.$"

HoennSeek_Text_GardenBulbasaurTalk::
	.string "The BULBASAUR is soaking up the\n"
	.string "morning sun with its bulb.$"

HoennSeek_Text_GardenIvysaurTalk::
	.string "The IVYSAUR is proudly showing\n"
	.string "off its new bud.$"

HoennSeek_Text_BulbasaurJoins::
	.string "The BULBASAUR is happy just the\n"
	.string "way it is.\p"
	.string "It trots right up to you, ready\n"
	.string "to come along!\p"
	.string "It's holding a smooth round stone\n"
	.string "in its vines…$"

HoennSeek_Text_CharmanderWaiting::
	.string "A CHARMANDER is huddled at the\n"
	.string "foot of the bridge in the rain.\p"
	.string "The flame on its tail is barely\n"
	.string "flickering…\p"
	.string "It keeps staring down the road.\n"
	.string "Someone told it to wait here.$"

HoennSeek_Text_CharmanderShield::
	.string "Shield the CHARMANDER\n"
	.string "from the rain?$"

HoennSeek_Text_CharmanderShielded::
	.string "{PLAYER} held their jacket over\n"
	.string "the CHARMANDER's tail…\p"
	.string "The flame is still fading! It\n"
	.string "needs a POKéMON CENTER, now!\p"
	.string "{PLAYER} scooped it up and ran\n"
	.string "for CERULEAN CITY!$"

HoennSeek_Text_CharmanderKeepsWaiting::
	.string "The CHARMANDER keeps waiting\n"
	.string "in the rain…$"

HoennSeek_Text_NurseCharmander::
	.string "NURSE: Oh my! This CHARMANDER\n"
	.string "is soaked through!\p"
	.string "Leave it to me. We'll have its\n"
	.string "flame burning in no time!$"

HoennSeek_Text_NurseCharmanderHealed::
	.string "NURSE: There! Its flame is\n"
	.string "burning brightly again.\p"
	.string "It must have waited out there\n"
	.string "for a trainer who never came.\p"
	.string "But look at it now. It hasn't\n"
	.string "taken its eyes off you!\p"
	.string "The CHARMANDER hopped into\n"
	.string "{PLAYER}'s arms. It chose you!$"

HoennSeek_Text_CharmanderNoRoom::
	.string "…but there's no room for it in\n"
	.string "your party or BOXES.\p"
	.string "NURSE: It ran back toward the\n"
	.string "bridge. It's still waiting…$"

HoennSeek_Text_CharmanderTrainerIntro::
	.string "That CHARMANDER… Is that the one\n"
	.string "I left at NUGGET BRIDGE?\p"
	.string "I told it to wait while I went\n"
	.string "after stronger POKéMON.\p"
	.string "I never went back for it.\n"
	.string "And it picked you instead, huh?\p"
	.string "Fine. Show me what kind of\n"
	.string "TRAINER it chose over me!$"

HoennSeek_Text_CharmanderTrainerDefeat::
	.string "…It never gave up on me.\n"
	.string "I'm the one who gave up.$"

HoennSeek_Text_CharmanderTrainerAfter::
	.string "It waited in the rain for me,\n"
	.string "and I never even came back.\p"
	.string "It picked the right TRAINER.\n"
	.string "Take good care of it.$"
