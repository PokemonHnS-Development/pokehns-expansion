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

@ ---- Squirtle: the Squirtle Squad (part 17) ----------------------------------
@ Day, then night. Mornings and days, four Squirtle play on the grass south of
@ Route 6's pond; the leader wears sunglasses. Walk up the path beside them
@ (trigger tiles, VAR_TEMP_1) and they lure you onto one of their pitfalls,
@ which drops you into their hideout under the pond bank (Route6_Hideout_hoenn,
@ its frame script plays the meeting; its ladder leads back up). They don't
@ trust trainers. That night they put out a house fire in Vermilion (trigger
@ tiles on the main street, VAR_TEMP_3), and the leader joins you at Lv 5,
@ holding its sunglasses (Black Glasses). Afterwards the other three are back
@ at the pond by day. Hint: Vermilion's police officer.
@ VAR_HOENN_SQUIRTLE_STATE: 0 not met, 1 fell in, 2 met, 3 the leader joined.

HoennSeek_EventScript_Route6OnTransition::
	setflag FLAG_HOENN_HIDE_SQUAD_ROUTE6
	setflag FLAG_HOENN_HIDE_SQUAD_LEADER
	gettimeofday
	goto_if_gt VAR_0x8000, HOENN_TIME_DAY, HoennSeek_EventScript_KantoStarterReturn
	goto_if_eq VAR_HOENN_SQUIRTLE_STATE, 3, HoennSeek_EventScript_Route6ShowSquad
	goto_if_ne VAR_HOENN_SQUIRTLE_STATE, 0, HoennSeek_EventScript_KantoStarterReturn
	clearflag FLAG_HOENN_HIDE_SQUAD_LEADER
	setvar VAR_TEMP_1, 1
HoennSeek_EventScript_Route6ShowSquad:
	clearflag FLAG_HOENN_HIDE_SQUAD_ROUTE6
	return

@ Trigger tiles on the path east of the pond (x 40-41, rows 25-27).
HoennSeek_EventScript_Route6Pitfall::
	lockall
	setvar VAR_TEMP_1, 0
	playse SE_PIN
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceLeft
	waitmovement 0
	playmoncry SPECIES_SQUIRTLE, CRY_MODE_NORMAL
	applymovement LOCALID_HOENN_SQUAD_LEADER, HoennSeek_Movement_SquadHopRight
	waitmovement 0
	waitmoncry
	msgbox HoennSeek_Text_SquadByThePond, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, HoennSeek_Movement_SquadPlayerLeft2
	waitmovement 0
	goto HoennSeek_EventScript_SquadPitfall

@ Talking to the leader before the trigger tiles: same trap, where you stand.
HoennSeek_EventScript_Route6Leader::
	lockall
	setvar VAR_TEMP_1, 0
	playmoncry SPECIES_SQUIRTLE, CRY_MODE_NORMAL
	msgbox HoennSeek_Text_SquadLeaderWaves, MSGBOX_DEFAULT
	waitmoncry
	closemessage
HoennSeek_EventScript_SquadPitfall:
	msgbox HoennSeek_Text_SquadPitfall, MSGBOX_DEFAULT
	closemessage
	setvar VAR_HOENN_SQUIRTLE_STATE, 1
	applymovement OBJ_EVENT_ID_PLAYER, HoennSeek_Movement_SquadInvisible
	waitmovement 0
	playse SE_FALL
	delay 60
	setwarp MAP_ROUTE6_HIDEOUT_HOENN, 10, 12
	special DoFallWarp
	waitstate
	end

HoennSeek_EventScript_Route6Squirtle::
	lock
	faceplayer
	playmoncry SPECIES_SQUIRTLE, CRY_MODE_NORMAL
	goto_if_eq VAR_HOENN_SQUIRTLE_STATE, 3, HoennSeek_EventScript_Route6SquirtleAfter
	msgbox HoennSeek_Text_SquadDigging, MSGBOX_DEFAULT
	waitmoncry
	release
	end
HoennSeek_EventScript_Route6SquirtleAfter:
	msgbox HoennSeek_Text_SquadBackAtPond, MSGBOX_DEFAULT
	waitmoncry
	release
	end

@ The hideout: you land among them (frame script, state 1).
HoennSeek_HideoutOnFrame::
	map_script_2 VAR_HOENN_SQUIRTLE_STATE, 1, HoennSeek_EventScript_HideoutScene
	.2byte 0

HoennSeek_EventScript_HideoutScene::
	lockall
	setvar VAR_HOENN_SQUIRTLE_STATE, 2
	playmoncry SPECIES_SQUIRTLE, CRY_MODE_NORMAL
	applymovement LOCALID_HOENN_HIDEOUT_SQUAD_2, HoennSeek_Movement_SquadHopRight
	applymovement LOCALID_HOENN_HIDEOUT_SQUAD_3, HoennSeek_Movement_SquadHopLeft
	waitmovement 0
	waitmoncry
	msgbox HoennSeek_Text_HideoutLaugh, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_HOENN_HIDEOUT_LEADER, HoennSeek_Movement_HideoutLeaderIn
	waitmovement 0
	msgbox HoennSeek_Text_HideoutLeader, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_HOENN_HIDEOUT_LEADER, HoennSeek_Movement_HideoutLeaderOut
	waitmovement 0
	msgbox HoennSeek_Text_HideoutLadder, MSGBOX_DEFAULT
	releaseall
	end

HoennSeek_EventScript_HideoutLeader::
	lock
	playmoncry SPECIES_SQUIRTLE, CRY_MODE_NORMAL
	msgbox HoennSeek_Text_HideoutLeaderTalk, MSGBOX_DEFAULT
	waitmoncry
	release
	end

HoennSeek_EventScript_HideoutSquirtle::
	lock
	faceplayer
	playmoncry SPECIES_SQUIRTLE, CRY_MODE_NORMAL
	msgbox HoennSeek_Text_HideoutSquirtleTalk, MSGBOX_DEFAULT
	waitmoncry
	release
	end

@ Vermilion, at night once you've met them (state 2). Until the fire scene has
@ played the Squad is hidden and the street's trigger tiles are armed; after
@ it (if the leader couldn't join), they're at the house every night.
HoennSeek_EventScript_VermilionOnTransition::
	setflag FLAG_HOENN_HIDE_SQUAD_VERMILION
	goto_if_ne VAR_HOENN_SQUIRTLE_STATE, 2, HoennSeek_EventScript_KantoStarterReturn
	gettimeofday
	goto_if_ne VAR_0x8000, HOENN_TIME_NIGHT, HoennSeek_EventScript_KantoStarterReturn
	goto_if_set FLAG_HOENN_SQUIRTLE_FIRE_OUT, HoennSeek_EventScript_VermilionShowSquad
	setvar VAR_TEMP_3, 1
	return
HoennSeek_EventScript_VermilionShowSquad:
	clearflag FLAG_HOENN_HIDE_SQUAD_VERMILION
	return

@ Trigger tiles on the main street (x 30-37, rows 17-18). The camera pans to
@ the house and the Squad below it (36,22) one tile at a time from wherever you are.
HoennSeek_EventScript_VermilionFire::
	lockall
	setvar VAR_TEMP_3, 0
	playse SE_PIN
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
	waitmovement 0
	getplayerxy VAR_0x8004, VAR_0x8005
	special SpawnCameraObject
HoennSeek_EventScript_FirePanX:
	goto_if_eq VAR_0x8004, 36, HoennSeek_EventScript_FirePanY
	goto_if_gt VAR_0x8004, 36, HoennSeek_EventScript_FirePanLeft
	applymovement OBJ_EVENT_ID_CAMERA, Common_Movement_WalkRight1
	waitmovement 0
	addvar VAR_0x8004, 1
	goto HoennSeek_EventScript_FirePanX
HoennSeek_EventScript_FirePanLeft:
	applymovement OBJ_EVENT_ID_CAMERA, Common_Movement_WalkLeft1
	waitmovement 0
	subvar VAR_0x8004, 1
	goto HoennSeek_EventScript_FirePanX
HoennSeek_EventScript_FirePanY:
	goto_if_ge VAR_0x8005, 22, HoennSeek_EventScript_FireStarts
	applymovement OBJ_EVENT_ID_CAMERA, Common_Movement_WalkDown1
	waitmovement 0
	addvar VAR_0x8005, 1
	goto HoennSeek_EventScript_FirePanY
HoennSeek_EventScript_FireStarts:
	playse SE_M_FLAMETHROWER
	call HoennSeek_EventScript_FireSmoke
	waitse
	msgbox HoennSeek_Text_FireSmoke, MSGBOX_DEFAULT
	closemessage
	call HoennSeek_EventScript_FireSmoke
	clearflag FLAG_HOENN_HIDE_SQUAD_VERMILION
	addobject LOCALID_HOENN_FIRE_LEADER
	addobject LOCALID_HOENN_FIRE_SQUAD_1
	addobject LOCALID_HOENN_FIRE_SQUAD_2
	addobject LOCALID_HOENN_FIRE_SQUAD_3
	playmoncry SPECIES_SQUIRTLE, CRY_MODE_NORMAL
	applymovement LOCALID_HOENN_FIRE_LEADER, HoennSeek_Movement_SquadHopUp
	waitmovement 0
	waitmoncry
	msgbox HoennSeek_Text_FireSquadArrives, MSGBOX_DEFAULT
	closemessage
	call HoennSeek_EventScript_FireSpray
	call HoennSeek_EventScript_FireSmoke
	call HoennSeek_EventScript_FireSpray
	call HoennSeek_EventScript_FireSmoke
	call HoennSeek_EventScript_FireSpray
	msgbox HoennSeek_Text_FireOut, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_HOENN_SQUIRTLE_FIRE_OUT
	playmoncry SPECIES_SQUIRTLE, CRY_MODE_NORMAL
	applymovement LOCALID_HOENN_FIRE_LEADER, Common_Movement_FaceUp
	waitmovement 0
	waitmoncry
	msgbox HoennSeek_Text_FireLeaderLooks, MSGBOX_DEFAULT
	closemessage
	special RemoveCameraObject
	releaseall
	end

@ Smoke puffs over the roof: Lavaridge Gym's ash puff (map coordinates + 7;
@ argument 2 is the subpriority, 3 the priority, above the roof).
HoennSeek_EventScript_FireSmoke:
	setvar VAR_0x8006, 0
HoennSeek_EventScript_FireSmokeLoop:
	setfieldeffectargument 0, 43
	setfieldeffectargument 1, 25
	setfieldeffectargument 2, 0
	setfieldeffectargument 3, 1
	dofieldeffect FLDEFF_ASH_PUFF
	delay 10
	setfieldeffectargument 0, 45
	setfieldeffectargument 1, 26
	dofieldeffect FLDEFF_ASH_PUFF
	delay 10
	setfieldeffectargument 0, 44
	setfieldeffectargument 1, 26
	dofieldeffect FLDEFF_ASH_PUFF
	delay 10
	addvar VAR_0x8006, 1
	goto_if_lt VAR_0x8006, 2, HoennSeek_EventScript_FireSmokeLoop
	return

HoennSeek_EventScript_FireSpray:
	playse SE_M_HYDRO_PUMP
	applymovement LOCALID_HOENN_FIRE_SQUAD_1, HoennSeek_Movement_SquadHopUp
	applymovement LOCALID_HOENN_FIRE_SQUAD_2, HoennSeek_Movement_SquadHopUp
	applymovement LOCALID_HOENN_FIRE_SQUAD_3, HoennSeek_Movement_SquadHopUp
	waitmovement 0
	waitse
	return

@ The leader joins you, holding its sunglasses.
HoennSeek_EventScript_FireLeader::
	lock
	faceplayer
	playmoncry SPECIES_SQUIRTLE, CRY_MODE_NORMAL
	msgbox HoennSeek_Text_SquirtleJoins, MSGBOX_DEFAULT
	waitmoncry
	bufferspeciesname STR_VAR_1, SPECIES_SQUIRTLE
	givemon SPECIES_SQUIRTLE, 5, ITEM_BLACK_GLASSES
	goto_if_eq VAR_RESULT, MON_CANT_GIVE, HoennSeek_EventScript_KantoStarterNoRoom
	setvar VAR_HOENN_SQUIRTLE_STATE, 3
	setflag FLAG_HOENN_SQUIRTLE_DONE
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_SQUIRTLE
	call Common_EventScript_GiftMon
	removeobject VAR_LAST_TALKED
	msgbox HoennSeek_Text_SquadSalutes, MSGBOX_DEFAULT
	release
	end

HoennSeek_EventScript_FireSquirtle::
	lock
	faceplayer
	playmoncry SPECIES_SQUIRTLE, CRY_MODE_NORMAL
	msgbox HoennSeek_Text_FireSquirtleTalk, MSGBOX_DEFAULT
	waitmoncry
	release
	end

@ The hint: Vermilion's police officer, on the main street.
HoennSeek_EventScript_VermilionOfficer::
	lock
	faceplayer
	goto_if_eq VAR_HOENN_SQUIRTLE_STATE, 3, HoennSeek_EventScript_OfficerAfter
	goto_if_set FLAG_HOENN_SQUIRTLE_FIRE_OUT, HoennSeek_EventScript_OfficerFireOut
	goto_if_eq VAR_HOENN_SQUIRTLE_STATE, 2, HoennSeek_EventScript_OfficerMet
	msgbox HoennSeek_Text_OfficerPitfalls, MSGBOX_DEFAULT
	release
	end
HoennSeek_EventScript_OfficerMet:
	msgbox HoennSeek_Text_OfficerMet, MSGBOX_DEFAULT
	release
	end
HoennSeek_EventScript_OfficerFireOut:
	msgbox HoennSeek_Text_OfficerFireOut, MSGBOX_DEFAULT
	release
	end
HoennSeek_EventScript_OfficerAfter:
	msgbox HoennSeek_Text_OfficerAfter, MSGBOX_DEFAULT
	release
	end

HoennSeek_Movement_SquadHopRight:
	jump_in_place_right
	jump_in_place_right
	step_end
HoennSeek_Movement_SquadHopLeft:
	jump_in_place_left
	jump_in_place_left
	step_end
HoennSeek_Movement_SquadHopUp:
	jump_in_place_up
	step_end
HoennSeek_Movement_SquadPlayerLeft2:
	walk_left
	walk_left
	step_end
HoennSeek_Movement_SquadInvisible:
	set_invisible
	step_end
HoennSeek_Movement_HideoutLeaderIn:
	walk_down
	walk_down
	walk_right
	walk_right
	face_right
	step_end
HoennSeek_Movement_HideoutLeaderOut:
	walk_left
	walk_left
	walk_up
	walk_up
	face_down
	step_end

HoennSeek_Text_SquadByThePond::
	.string "Four SQUIRTLE are playing by\n"
	.string "the pond.\p"
	.string "The one in front is wearing\n"
	.string "sunglasses!\p"
	.string "It's waving at you to come\n"
	.string "over and play…$"

HoennSeek_Text_SquadLeaderWaves::
	.string "The SQUIRTLE in sunglasses is\n"
	.string "waving at you to come closer…$"

HoennSeek_Text_SquadPitfall::
	.string "Whoa! The ground gave way!\n"
	.string "It's a pitfall!$"

HoennSeek_Text_SquadDigging::
	.string "Squirt! It's scraping at the\n"
	.string "soft ground by the pond.$"

HoennSeek_Text_SquadBackAtPond::
	.string "Squirt! It's back to playing\n"
	.string "by the pond. It salutes you!$"

HoennSeek_Text_HideoutLaugh::
	.string "Squirt squirt squirt!\p"
	.string "The SQUIRTLE are rolling around\n"
	.string "laughing. You fell right into\l"
	.string "their hideout!$"

HoennSeek_Text_HideoutLeader::
	.string "The one in sunglasses steps\n"
	.string "forward. It must be the leader\l"
	.string "of this SQUIRTLE SQUAD.\p"
	.string "It looks you up and down…\n"
	.string "then turns its back on you.\p"
	.string "These SQUIRTLE don't seem to\n"
	.string "trust TRAINERS.$"

HoennSeek_Text_HideoutLadder::
	.string "There's a ladder back up to\n"
	.string "ROUTE 6.$"

HoennSeek_Text_HideoutLeaderTalk::
	.string "The leader is ignoring you.\p"
	.string "Its sunglasses are scratched,\n"
	.string "like it's had them a long time.$"

HoennSeek_Text_HideoutSquirtleTalk::
	.string "Squirt! It's practicing WATER\n"
	.string "GUN on the wall of the hideout.$"

HoennSeek_Text_FireSmoke::
	.string "Smoke is pouring out of that\n"
	.string "house! It's on fire!$"

HoennSeek_Text_FireSquadArrives::
	.string "Squirt! Squirt!\p"
	.string "It's the SQUIRTLE SQUAD! The\n"
	.string "leader is giving the orders!$"

HoennSeek_Text_FireOut::
	.string "The SQUIRTLE SQUAD put the\n"
	.string "fire out with WATER GUN!\p"
	.string "Everyone inside got out safely.$"

HoennSeek_Text_FireLeaderLooks::
	.string "The leader in sunglasses is\n"
	.string "looking your way.$"

HoennSeek_Text_SquirtleJoins::
	.string "The leader takes off its\n"
	.string "sunglasses and looks at you.\p"
	.string "Then it puts them back on and\n"
	.string "hops to your side.\p"
	.string "It wants to come with you!$"

HoennSeek_Text_SquadSalutes::
	.string "The rest of the SQUIRTLE SQUAD\n"
	.string "salutes their leader goodbye!$"

HoennSeek_Text_FireSquirtleTalk::
	.string "Squirt! It's soaking wet and\n"
	.string "very proud of itself.$"

HoennSeek_Text_OfficerPitfalls::
	.string "People keep falling into holes\n"
	.string "on ROUTE 6, right by the pond.\p"
	.string "Witnesses blame a gang of\n"
	.string "SQUIRTLE that plays there by day.\p"
	.string "And the ringleader wears\n"
	.string "sunglasses, if you can believe it!$"

HoennSeek_Text_OfficerMet::
	.string "You found that SQUIRTLE SQUAD's\n"
	.string "hideout? Ha! You fell in too?\p"
	.string "They've been seen sneaking\n"
	.string "around town after dark.\p"
	.string "I'll be keeping an eye out\n"
	.string "tonight.$"

HoennSeek_Text_OfficerFireOut::
	.string "That SQUIRTLE SQUAD put out\n"
	.string "the fire before the engines came!\p"
	.string "Their leader keeps looking\n"
	.string "for you at night, you know.$"

HoennSeek_Text_OfficerAfter::
	.string "I made the rest of that SQUAD\n"
	.string "honorary firefighters.\p"
	.string "Don't tell the chief, all right?\n"
	.string "They still dig pitfalls.$"
