@ Hoenn & Seek 2.0, lane B: parts 31b, 34a, 29, 30a, 30b, 33, 36 and 35a (Kanto, the Safari Zone, the birds, Mewtwo/Mew, Hoenn's weather legendaries).
@ Lane B's scenes, phone calls and texts go in this file (or a new data/scripts/hoenn_*.inc
@ of its own); the other lane has its own file, so the two never edit the same lines.
@ Rules: hoenn-docs/lanes/README.md. C code: src/hoenn_lane_b.c.

@ ---------------------------------------------------------------- event calls

@ The PokéGear event-call switch (HoennSeek_EventScript_PhoneEvent, hoenn_phone.inc)
@ falls through to lane A's cases, then to lane B's. Add one case per call:
@ 	case HOENN_CALL_X, HoennSeek_EventScript_CallX
HoennSeek_EventScript_PhoneEventLaneB::
	switch VAR_0x8004
	case HOENN_CALL_MOON_HOLLOW, HoennSeek_EventScript_CallMoonHollow @ part 31b
	case HOENN_CALL_BIRDS, HoennSeek_EventScript_CallBirds @ part 34a
	case HOENN_CALL_TUNNELS, HoennSeek_EventScript_CallTunnels @ part 29
	case HOENN_CALL_KANGASKHAN, HoennSeek_EventScript_CallKangaskhan @ part 30a
	case HOENN_CALL_STAMPEDE, HoennSeek_EventScript_CallStampede @ part 30b
	releaseall @ no call matched: the end of the chain
	end

@ ==========================================================================
@ Part 31b: Teddiursa's honey trail (Route 45) and the moon hollow
@ ==========================================================================
@ - The beekeeper at the top of Route 45 (Route45_BeekeeperHouse_hoenn, a
@   generated building) gives one HONEY a day.
@ - HONEY spread on the old pine in the pond meadow (bg events at 21,83-84,
@   reached through the nook at 22,83-84) brings two Teddiursa on a later
@   morning (FLAG_HOENN_DAILY_HONEY_SPREAD keeps them away the same day).
@   Watching them counts (VAR_HOENN_HONEY_MORNINGS); shooing them leaves the
@   honey for another morning.
@ - After HOENN_HONEY_MORNINGS_NEEDED watched mornings, the next honey brings
@   their mother instead (stage CUBS -> NIGHT). On any later night she waits
@   at the pine, walks to the meadow's east cliff (32,85) and climbs it; you
@   follow her up into Route45_MoonHollow_hoenn (stage HOLLOW), where the bears
@   watch the moon. FLAG_HOENN_MOON_HOLLOW_FOUND is lane A's input for
@   Jirachi's wishing spot (part 37: HoennSeek_EventScript_MoonHollowPool is
@   the spot to hook). From then on the claw marks on that cliff (33,85) take
@   you back up any time, and the bears are there at night.
@ - No Pokémon is given (plan section 8). Brendan calls about it
@   (HOENN_CALL_MOON_HOLLOW: the beekeeper's letter to Birch).

	.include "data/maps/Route45_MoonHollow_hoenn/scripts.inc"

@ Route 45's OnTransition: which bears are at the pine.
HoennSeek_EventScript_Route45OnTransition::
	setflag FLAG_HOENN_HIDE_HONEY_TEDDI
	setflag FLAG_HOENN_HIDE_HONEY_URSARING
	gettimeofday
	goto_if_eq VAR_0x8000, HOENN_TIME_NIGHT, HoennSeek_EventScript_HoneyAtNight
	goto_if_ne VAR_0x8000, HOENN_TIME_MORNING, HoennSeek_EventScript_LaneBEnd
	goto_if_unset FLAG_HOENN_HONEY_ON_TREE, HoennSeek_EventScript_LaneBEnd
	goto_if_set FLAG_HOENN_DAILY_HONEY_SPREAD, HoennSeek_EventScript_LaneBEnd
	goto_if_ne VAR_HOENN_HONEY_STAGE, HOENN_HONEY_STAGE_CUBS, HoennSeek_EventScript_HoneyCubsCome
	goto_if_lt VAR_HOENN_HONEY_MORNINGS, HOENN_HONEY_MORNINGS_NEEDED, HoennSeek_EventScript_HoneyCubsCome
	clearflag FLAG_HOENN_HIDE_HONEY_URSARING
	end

HoennSeek_EventScript_HoneyCubsCome:
	clearflag FLAG_HOENN_HIDE_HONEY_TEDDI
	end

HoennSeek_EventScript_HoneyAtNight:
	goto_if_ne VAR_HOENN_HONEY_STAGE, HOENN_HONEY_STAGE_NIGHT, HoennSeek_EventScript_LaneBEnd
	clearflag FLAG_HOENN_HIDE_HONEY_URSARING
HoennSeek_EventScript_LaneBEnd:
	end

@ The pine (from the nook, facing west).
HoennSeek_EventScript_HoneyPine::
	lockall
	goto_if_set FLAG_HOENN_HONEY_ON_TREE, HoennSeek_EventScript_HoneyPineSticky
	checkitem ITEM_HONEY
	goto_if_eq VAR_RESULT, FALSE, HoennSeek_EventScript_HoneyPineBare
	msgbox HoennSeek_Text_HoneyPineSpread, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, HoennSeek_EventScript_LaneBRelease
	removeitem ITEM_HONEY
	setflag FLAG_HOENN_HONEY_ON_TREE
	setflag FLAG_HOENN_DAILY_HONEY_SPREAD
	msgbox HoennSeek_Text_HoneyPineSpreadDone, MSGBOX_DEFAULT
	goto HoennSeek_EventScript_LaneBRelease

HoennSeek_EventScript_HoneyPineSticky:
	msgbox HoennSeek_Text_HoneyPineSticky, MSGBOX_DEFAULT
	goto HoennSeek_EventScript_LaneBRelease

HoennSeek_EventScript_HoneyPineBare:
	msgbox HoennSeek_Text_HoneyPineBare, MSGBOX_DEFAULT
HoennSeek_EventScript_LaneBRelease:
	releaseall
	end

@ The Teddiursa at the pine (you can only stand at 22,85, below them).
HoennSeek_EventScript_HoneyTeddiursa::
	lockall
	playmoncry SPECIES_TEDDIURSA, CRY_MODE_NORMAL
	msgbox HoennSeek_Text_HoneyCubsLicking, MSGBOX_DEFAULT
	waitmoncry
	msgbox HoennSeek_Text_HoneyCubsWatch, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, HoennSeek_EventScript_HoneyCubsShoo
	closemessage
	applymovement LOCALID_HOENN_HONEY_TEDDI_1, HoennSeek_Movement_HoneyLick
	applymovement LOCALID_HOENN_HONEY_TEDDI_2, HoennSeek_Movement_HoneyLick
	waitmovement LOCALID_HOENN_HONEY_TEDDI_1
	waitmovement LOCALID_HOENN_HONEY_TEDDI_2
	applymovement LOCALID_HOENN_HONEY_TEDDI_2, Common_Movement_FaceDown
	waitmovement LOCALID_HOENN_HONEY_TEDDI_2
	clearflag FLAG_HOENN_HONEY_ON_TREE
	goto_if_ge VAR_HOENN_HONEY_MORNINGS, HOENN_HONEY_MORNINGS_NEEDED, HoennSeek_EventScript_HoneyCubsSated
	addvar VAR_HOENN_HONEY_MORNINGS, 1
	goto_if_ge VAR_HOENN_HONEY_MORNINGS, HOENN_HONEY_MORNINGS_NEEDED, HoennSeek_EventScript_HoneyCubsTrust
HoennSeek_EventScript_HoneyCubsSated:
	msgbox HoennSeek_Text_HoneyCubsDone, MSGBOX_DEFAULT
	goto HoennSeek_EventScript_HoneyCubsLeave

HoennSeek_EventScript_HoneyCubsTrust:
	msgbox HoennSeek_Text_HoneyCubsTrust, MSGBOX_DEFAULT
HoennSeek_EventScript_HoneyCubsLeave:
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, HoennSeek_Movement_HoneyStepAside
	waitmovement 0
	applymovement LOCALID_HOENN_HONEY_TEDDI_2, HoennSeek_Movement_HoneyCub2Leave
	applymovement LOCALID_HOENN_HONEY_TEDDI_1, HoennSeek_Movement_HoneyCub1Leave
	waitmovement LOCALID_HOENN_HONEY_TEDDI_2
	removeobject LOCALID_HOENN_HONEY_TEDDI_2
	waitmovement LOCALID_HOENN_HONEY_TEDDI_1
	applymovement LOCALID_HOENN_HONEY_TEDDI_1, HoennSeek_Movement_HoneyClimb
	waitmovement LOCALID_HOENN_HONEY_TEDDI_1
	removeobject LOCALID_HOENN_HONEY_TEDDI_1
	setflag FLAG_HOENN_HIDE_HONEY_TEDDI
	releaseall
	end

@ Shooing: they run, and the honey stays for another morning.
HoennSeek_EventScript_HoneyCubsShoo:
	closemessage
	applymovement LOCALID_HOENN_HONEY_TEDDI_1, Common_Movement_ExclamationMark
	applymovement LOCALID_HOENN_HONEY_TEDDI_2, Common_Movement_ExclamationMark
	waitmovement LOCALID_HOENN_HONEY_TEDDI_1
	waitmovement LOCALID_HOENN_HONEY_TEDDI_2
	applymovement OBJ_EVENT_ID_PLAYER, HoennSeek_Movement_HoneyStepAside
	waitmovement 0
	applymovement LOCALID_HOENN_HONEY_TEDDI_2, HoennSeek_Movement_HoneyCub2Flee
	applymovement LOCALID_HOENN_HONEY_TEDDI_1, HoennSeek_Movement_HoneyCub1Flee
	waitmovement LOCALID_HOENN_HONEY_TEDDI_2
	removeobject LOCALID_HOENN_HONEY_TEDDI_2
	waitmovement LOCALID_HOENN_HONEY_TEDDI_1
	applymovement LOCALID_HOENN_HONEY_TEDDI_1, HoennSeek_Movement_HoneyClimb
	waitmovement LOCALID_HOENN_HONEY_TEDDI_1
	removeobject LOCALID_HOENN_HONEY_TEDDI_1
	setflag FLAG_HOENN_HIDE_HONEY_TEDDI
	setflag FLAG_HOENN_DAILY_HONEY_SPREAD
	msgbox HoennSeek_Text_HoneyCubsShooed, MSGBOX_DEFAULT
	releaseall
	end

@ The mother at the pine: one morning (she takes the honey and leaves by the
@ cliff), then any night until you follow her.
HoennSeek_EventScript_HoneyUrsaring::
	lockall
	playmoncry SPECIES_URSARING, CRY_MODE_NORMAL
	goto_if_eq VAR_HOENN_HONEY_STAGE, HOENN_HONEY_STAGE_NIGHT, HoennSeek_EventScript_HoneyUrsaringNight
	msgbox HoennSeek_Text_HoneyMotherMorning, MSGBOX_DEFAULT
	waitmoncry
	closemessage
	applymovement LOCALID_HOENN_HONEY_URSARING, Common_Movement_FaceDown
	waitmovement 0
	msgbox HoennSeek_Text_HoneyMotherSniffs, MSGBOX_DEFAULT
	closemessage
	clearflag FLAG_HOENN_HONEY_ON_TREE
	setvar VAR_HOENN_HONEY_STAGE, HOENN_HONEY_STAGE_NIGHT
	applymovement OBJ_EVENT_ID_PLAYER, HoennSeek_Movement_HoneyStepAside
	waitmovement 0
	applymovement LOCALID_HOENN_HONEY_URSARING, HoennSeek_Movement_HoneyMotherWalk
	waitmovement 0
	applymovement LOCALID_HOENN_HONEY_URSARING, HoennSeek_Movement_HoneyClimb
	waitmovement 0
	removeobject LOCALID_HOENN_HONEY_URSARING
	setflag FLAG_HOENN_HIDE_HONEY_URSARING
	msgbox HoennSeek_Text_HoneyMotherGone, MSGBOX_DEFAULT
	releaseall
	end

HoennSeek_EventScript_HoneyUrsaringNight:
	msgbox HoennSeek_Text_HoneyMotherNight, MSGBOX_DEFAULT
	waitmoncry
	closemessage
	applymovement LOCALID_HOENN_HONEY_URSARING, Common_Movement_FaceDown
	waitmovement 0
	msgbox HoennSeek_Text_HoneyMotherFollow, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, HoennSeek_Movement_HoneyStepAside
	waitmovement 0
	applymovement LOCALID_HOENN_HONEY_URSARING, HoennSeek_Movement_HoneyMotherWalk
	applymovement OBJ_EVENT_ID_PLAYER, HoennSeek_Movement_HoneyFollowMother
	waitmovement LOCALID_HOENN_HONEY_URSARING
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement LOCALID_HOENN_HONEY_URSARING, HoennSeek_Movement_HoneyClimb
	waitmovement 0
	removeobject LOCALID_HOENN_HONEY_URSARING
	setflag FLAG_HOENN_HIDE_HONEY_URSARING
	msgbox HoennSeek_Text_HoneyMotherClimbs, MSGBOX_DEFAULT
	closemessage
	goto HoennSeek_EventScript_ClimbToHollow

@ The claw marks on the meadow's east cliff (from 32,85, facing east).
HoennSeek_EventScript_ClawMarks::
	lockall
	goto_if_ne VAR_HOENN_HONEY_STAGE, HOENN_HONEY_STAGE_HOLLOW, HoennSeek_EventScript_ClawMarksOnly
	msgbox HoennSeek_Text_ClawMarksClimb, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, HoennSeek_EventScript_LaneBRelease
	closemessage
HoennSeek_EventScript_ClimbToHollow:
	playse SE_LEDGE
	warp MAP_ROUTE45_MOON_HOLLOW_HOENN, 7, 13
	waitstate
	end

HoennSeek_EventScript_ClawMarksOnly:
	msgbox HoennSeek_Text_ClawMarks, MSGBOX_DEFAULT
	goto HoennSeek_EventScript_LaneBRelease

@ ---- The moon hollow --------------------------------------------------------

@ The bears are up here at night once she has led you (stage NIGHT is the
@ climb itself: she walks up to the pool as you arrive).
HoennSeek_EventScript_MoonHollowOnTransition::
	setflag FLAG_HOENN_HIDE_HOLLOW_BEARS
	gettimeofday
	goto_if_ne VAR_0x8000, HOENN_TIME_NIGHT, HoennSeek_EventScript_LaneBEnd
	goto_if_eq VAR_HOENN_HONEY_STAGE, HOENN_HONEY_STAGE_CUBS, HoennSeek_EventScript_LaneBEnd
	clearflag FLAG_HOENN_HIDE_HOLLOW_BEARS
	goto_if_ne VAR_HOENN_HONEY_STAGE, HOENN_HONEY_STAGE_NIGHT, HoennSeek_EventScript_LaneBEnd
	setobjectxyperm LOCALID_HOENN_HOLLOW_URSARING, 7, 11
	setvar VAR_TEMP_1, 1
	end

HoennSeek_EventScript_MoonHollowArrival::
	lockall
	setvar VAR_TEMP_1, 0
	applymovement LOCALID_HOENN_HOLLOW_URSARING, HoennSeek_Movement_HollowMotherSits
	waitmovement 0
	msgbox HoennSeek_Text_HollowArrive, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, HoennSeek_Movement_HollowPlayerWalksUp
	waitmovement 0
	playmoncry SPECIES_URSARING, CRY_MODE_WEAK
	msgbox HoennSeek_Text_HollowMoon, MSGBOX_DEFAULT
	waitmoncry
	setvar VAR_HOENN_HONEY_STAGE, HOENN_HONEY_STAGE_HOLLOW
	setflag FLAG_HOENN_MOON_HOLLOW_FOUND
	releaseall
	end

HoennSeek_EventScript_HollowBear::
	lock
	goto_if_eq VAR_LAST_TALKED, LOCALID_HOENN_HOLLOW_URSARING, HoennSeek_EventScript_HollowMother
	playmoncry SPECIES_TEDDIURSA, CRY_MODE_WEAK
	msgbox HoennSeek_Text_HollowCub, MSGBOX_DEFAULT
	waitmoncry
	release
	end

HoennSeek_EventScript_HollowMother:
	playmoncry SPECIES_URSARING, CRY_MODE_WEAK
	msgbox HoennSeek_Text_HollowMother, MSGBOX_DEFAULT
	waitmoncry
	release
	end

@ The pool below the moon. Lane A's part 37 (Jirachi) hooks its wish here.
HoennSeek_EventScript_MoonHollowPool::
	lockall
	gettimeofday
	goto_if_eq VAR_0x8000, HOENN_TIME_NIGHT, HoennSeek_EventScript_MoonHollowPoolNight
	msgbox HoennSeek_Text_HollowPoolDay, MSGBOX_DEFAULT
	goto HoennSeek_EventScript_LaneBRelease

HoennSeek_EventScript_MoonHollowPoolNight:
	msgbox HoennSeek_Text_HollowPoolNight, MSGBOX_DEFAULT
	goto HoennSeek_EventScript_LaneBRelease

HoennSeek_EventScript_LeaveMoonHollow::
	warp MAP_ROUTE45_HNS, 32, 85
	waitstate
	end

@ ---- Movements --------------------------------------------------------------

HoennSeek_Movement_HoneyLick:
	walk_in_place_left
	delay_8
	walk_in_place_left
	delay_16
	walk_in_place_left
	step_end

@ From (22,85), out of the nook's mouth.
HoennSeek_Movement_HoneyStepAside:
	walk_down
	face_up
	step_end

@ The cubs and their mother leave along row 85 to the east cliff (32,85).
HoennSeek_Movement_HoneyCub2Leave:
	walk_down
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
	face_right
	jump_in_place_right
	step_end

HoennSeek_Movement_HoneyCub1Leave:
	delay_16
	walk_down
	walk_down
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

HoennSeek_Movement_HoneyCub2Flee:
	walk_fast_down
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	jump_in_place_right
	step_end

HoennSeek_Movement_HoneyCub1Flee:
	delay_8
	walk_fast_down
	walk_fast_down
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

HoennSeek_Movement_HoneyClimb:
	walk_right
	jump_in_place_right
	step_end

HoennSeek_Movement_HoneyMotherWalk:
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	face_right
	step_end

@ The player (stepped aside to 22,86) follows her to (30,85).
HoennSeek_Movement_HoneyFollowMother:
	delay_16
	delay_16
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	face_right
	step_end

@ The hollow: from (7,11) to the pool's edge (11,9).
HoennSeek_Movement_HollowMotherSits:
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	face_up
	step_end

HoennSeek_Movement_HollowPlayerWalksUp:
	walk_up
	walk_up
	face_up
	step_end

@ ---- Part 31b's call ---------------------------------------------------------

HoennSeek_EventScript_CallMoonHollow::
	setflag FLAG_HOENN_CALL_MOON_HOLLOW
	setspeaker HoennSeek_Text_NameBrendan
	pokenavcall HoennSeek_Text_CallMoonHollow
	goto HoennSeek_EventScript_CallEnd

@ ---- Part 31b texts ----------------------------------------------------------

HoennSeek_Text_HoneyPineBare:
	.string "An old pine. Its bark is scored\n"
	.string "with little claw marks, and it\l"
	.string "smells faintly sweet.$"

HoennSeek_Text_HoneyPineSpread:
	.string "An old pine, scored with little\n"
	.string "claw marks. Spread some HONEY\l"
	.string "on its bark?$"

HoennSeek_Text_HoneyPineSpreadDone:
	.string "{PLAYER} spread HONEY on the bark.\p"
	.string "A sweet smell drifts out across\n"
	.string "the meadow…\p"
	.string "Something might come for it\n"
	.string "in the morning.$"

HoennSeek_Text_HoneyPineSticky:
	.string "The bark is still sticky with\n"
	.string "HONEY. Something will come for it\l"
	.string "in the morning.$"

HoennSeek_Text_HoneyCubsLicking:
	.string "Two TEDDIURSA are licking HONEY\n"
	.string "off the pine's bark!$"

HoennSeek_Text_HoneyCubsWatch:
	.string "Stay still and let them eat?$"

HoennSeek_Text_HoneyCubsDone:
	.string "The TEDDIURSA licked the bark\n"
	.string "clean. One of them gave you a long\l"
	.string "look before they wandered off.$"

HoennSeek_Text_HoneyCubsTrust:
	.string "The cubs licked the bark clean.\p"
	.string "This time they toddled right up to\n"
	.string "you and sniffed your shoes before\l"
	.string "they left. They kept looking back,\l"
	.string "as if to tell someone about you.$"

HoennSeek_Text_HoneyCubsShooed:
	.string "The TEDDIURSA ran off!\p"
	.string "Most of the HONEY is still on the\n"
	.string "bark. They'll be back for it\l"
	.string "another morning.$"

HoennSeek_Text_HoneyMotherMorning:
	.string "A big URSARING is licking HONEY\n"
	.string "off the pine. It must be the\l"
	.string "TEDDIURSA's mother!$"

HoennSeek_Text_HoneyMotherSniffs:
	.string "URSARING sniffed you all over…\p"
	.string "Then it looked up at the cliffs\n"
	.string "and gave a low, rumbling growl.\p"
	.string "It seems to be trying to tell\n"
	.string "you something.$"

HoennSeek_Text_HoneyMotherGone:
	.string "URSARING climbed the cliff and\n"
	.string "was gone.\p"
	.string "Maybe it'll come back when the\n"
	.string "moon is out…$"

HoennSeek_Text_HoneyMotherNight:
	.string "The URSARING is waiting by the\n"
	.string "pine in the moonlight!$"

HoennSeek_Text_HoneyMotherFollow:
	.string "URSARING turned toward the meadow\n"
	.string "and looked back at you.\p"
	.string "It wants you to follow!$"

HoennSeek_Text_HoneyMotherClimbs:
	.string "URSARING dug its claws into the\n"
	.string "rock and climbed!\p"
	.string "Its claws left deep holds in the\n"
	.string "cliff, and {PLAYER} climbed up\l"
	.string "after it!$"

HoennSeek_Text_ClawMarks:
	.string "The rock is scored with deep claw\n"
	.string "marks, as if something big climbs\l"
	.string "up here.$"

HoennSeek_Text_ClawMarksClimb:
	.string "URSARING's claw holds lead up the\n"
	.string "rock to the moon hollow.\p"
	.string "Climb up?$"

HoennSeek_Text_HollowArrive:
	.string "URSARING sat down by a little\n"
	.string "pool. Its cubs were already\l"
	.string "waiting there.$"

HoennSeek_Text_HollowMoon:
	.string "The moon hangs huge and bright\n"
	.string "over the hollow. Its reflection\l"
	.string "floats on the still water.\p"
	.string "The bears sat quietly, watching\n"
	.string "the moon together…\p"
	.string "Up here, the moon feels close\n"
	.string "enough to touch. It feels like the\l"
	.string "kind of place where a wish might\l"
	.string "come true.$"

HoennSeek_Text_HollowMother:
	.string "URSARING is gazing up at the moon.\n"
	.string "It looks completely at peace.$"

HoennSeek_Text_HollowCub:
	.string "TEDDIURSA is dozing against the\n"
	.string "warm grass, full of HONEY.$"

HoennSeek_Text_HollowPoolNight:
	.string "The moon's reflection floats on\n"
	.string "the pool, perfectly still.\p"
	.string "It feels as if you could make a\n"
	.string "wish on it…$"

HoennSeek_Text_HollowPoolDay:
	.string "A little pool of clear rainwater.\n"
	.string "At night it would hold the moon.$"

HoennSeek_Text_CallMoonHollow:
	.string "Hey, {PLAYER}! It's BRENDAN.\p"
	.string "A jar of HONEY came to the lab\n"
	.string "today, from a beekeeper on JOHTO's\l"
	.string "ROUTE 45. He and Dad swap notes\l"
	.string "about COMBEE.\p"
	.string "His letter says his granddaughter\n"
	.string "saw a trainer climb a cliff after\l"
	.string "an URSARING one night.\p"
	.string "That was you, right?\p"
	.string "There's an old HOENN story about a\n"
	.string "POKéMON that wakes to grant wishes\l"
	.string "under the stars.\p"
	.string "Dad says a place like your moon\n"
	.string "hollow is just where it'd listen.\l"
	.string "Make a good wish, okay? Later!$"

@ ==========================================================================
@ Part 34a: the three birds (Bill's hub, the feathers, the roosts)
@ ==========================================================================
@ - Bill (GoldenrodCity_BillsHouse_hns, object script swap) tracks the three
@   legendary birds through his PC network. Once you have his Eevee he tells
@   you, for each bird not yet caught, where its feather is said to be or,
@   if you carry it, where the bird roosts.
@ - Feathers (key items): the FROST FEATHER (part 26b, Shoal Cave's ice
@   chamber); the THUNDER FEATHER, which the Power Plant manager gives you on
@   Route 10's thunderstorm day (his object script is swapped; HnS's script
@   runs until the Machine Part is back); the FLAME FEATHER, dropped into
@   Route 113's ash when Moltres flies over (the cameo: trigger column x 56,
@   rows 2-12, any time, once).
@ - Roosts: Seafoam B1F's middle island (Articuno, 31,31), the Power Plant's
@   back yard on Route 10 (Zapdos, 5,48; reached through the plant's back
@   room), Mt. Silver's Moltres room (Moltres, 17,18, in the pit; HnS had it at 17,20,
@   out of view under the text box from the foot of the stairs). HnS's bird
@   objects stay, with Hoenn & Seek flags (HnS's own bird hide flags are 0, so its
@   birds came back after every battle). Each roost map's OnTransition asks
@   HoennBirdRoostState (src/hoenn_lane_b.c): a bird that already landed is
@   shown; with the feather in the bag the roost's triggers are armed
@   (VAR_TEMP_6 1), and stepping on one calls the bird down. It waits there
@   until you battle it (HnS's Lv 50 legendary battle): caught, gone for good;
@   knocked out, back another day (daily flag); ran, it stays. Feathers stay in
@   the bag: Lugia's shrine (lane A's part 34b) asks for all three.
@ - Phone: May, once a feather has called a bird down (Bill phoned Birch).

@ ---- Bill's hub ---------------------------------------------------------------

HoennSeek_EventScript_BillBirds::
	goto_if_unset FLAG_GOT_EEVEE, GoldenrodCity_BillsHouse_EventScript_Bill
	lock
	faceplayer
	goto_if_set FLAG_HOENN_BILL_BIRDS, HoennSeek_EventScript_BillBirdsStatus
	msgbox HoennSeek_Text_BillBirdsIntro, MSGBOX_DEFAULT
	setflag FLAG_HOENN_BILL_BIRDS
HoennSeek_EventScript_BillBirdsStatus:
	goto_if_unset FLAG_HOENN_CAUGHT_ARTICUNO, HoennSeek_EventScript_BillBirdsReport
	goto_if_unset FLAG_HOENN_CAUGHT_ZAPDOS, HoennSeek_EventScript_BillBirdsReport
	goto_if_unset FLAG_HOENN_CAUGHT_MOLTRES, HoennSeek_EventScript_BillBirdsReport
	msgbox HoennSeek_Text_BillBirdsAllCaught, MSGBOX_DEFAULT
	goto HoennSeek_EventScript_LaneBRelease

HoennSeek_EventScript_BillBirdsReport:
	msgbox HoennSeek_Text_BillBirdsReport, MSGBOX_DEFAULT
	call HoennSeek_EventScript_BillArticuno
	call HoennSeek_EventScript_BillZapdos
	call HoennSeek_EventScript_BillMoltres
	msgbox HoennSeek_Text_BillBirdsBye, MSGBOX_DEFAULT
	goto HoennSeek_EventScript_LaneBRelease

HoennSeek_EventScript_BillArticuno:
	goto_if_set FLAG_HOENN_CAUGHT_ARTICUNO, HoennSeek_EventScript_BillArticunoCaught
	checkitem ITEM_FROST_FEATHER
	goto_if_eq VAR_RESULT, TRUE, HoennSeek_EventScript_BillArticunoRoost
	msgbox HoennSeek_Text_BillArticunoClue, MSGBOX_DEFAULT
	return
HoennSeek_EventScript_BillArticunoRoost:
	msgbox HoennSeek_Text_BillArticunoRoost, MSGBOX_DEFAULT
	return
HoennSeek_EventScript_BillArticunoCaught:
	msgbox HoennSeek_Text_BillArticunoCaught, MSGBOX_DEFAULT
	return

HoennSeek_EventScript_BillZapdos:
	goto_if_set FLAG_HOENN_CAUGHT_ZAPDOS, HoennSeek_EventScript_BillZapdosCaught
	checkitem ITEM_THUNDER_FEATHER
	goto_if_eq VAR_RESULT, TRUE, HoennSeek_EventScript_BillZapdosRoost
	msgbox HoennSeek_Text_BillZapdosClue, MSGBOX_DEFAULT
	return
HoennSeek_EventScript_BillZapdosRoost:
	msgbox HoennSeek_Text_BillZapdosRoost, MSGBOX_DEFAULT
	return
HoennSeek_EventScript_BillZapdosCaught:
	msgbox HoennSeek_Text_BillZapdosCaught, MSGBOX_DEFAULT
	return

HoennSeek_EventScript_BillMoltres:
	goto_if_set FLAG_HOENN_CAUGHT_MOLTRES, HoennSeek_EventScript_BillMoltresCaught
	checkitem ITEM_FLAME_FEATHER
	goto_if_eq VAR_RESULT, TRUE, HoennSeek_EventScript_BillMoltresRoost
	msgbox HoennSeek_Text_BillMoltresClue, MSGBOX_DEFAULT
	return
HoennSeek_EventScript_BillMoltresRoost:
	msgbox HoennSeek_Text_BillMoltresRoost, MSGBOX_DEFAULT
	return
HoennSeek_EventScript_BillMoltresCaught:
	msgbox HoennSeek_Text_BillMoltresCaught, MSGBOX_DEFAULT
	return

@ ---- Zapdos: the Power Plant manager's feather ----------------------------------

HoennSeek_EventScript_PowerPlantManager::
	goto_if_lt VAR_KANTO_ROCKET_STORY_STATE, 7, Route10_PowerPlantBackRoom_EventScript_Manager
	lock
	faceplayer
	goto_if_set FLAG_HOENN_GOT_THUNDER_FEATHER, HoennSeek_EventScript_ManagerAfterFeather
	setvar VAR_0x8004, MAP_ROUTE10_HNS
	specialvar VAR_RESULT, HoennIsSpecialWeatherOn
	goto_if_eq VAR_RESULT, TRUE, HoennSeek_EventScript_ManagerStormFeather
	msgbox HoennSeek_Text_ManagerStormHint, MSGBOX_DEFAULT
	goto HoennSeek_EventScript_LaneBRelease

HoennSeek_EventScript_ManagerStormFeather:
	msgbox HoennSeek_Text_ManagerStorm, MSGBOX_DEFAULT
	giveitem ITEM_THUNDER_FEATHER
	setflag FLAG_HOENN_GOT_THUNDER_FEATHER
	msgbox HoennSeek_Text_ManagerYard, MSGBOX_DEFAULT
	goto HoennSeek_EventScript_LaneBRelease

HoennSeek_EventScript_ManagerAfterFeather:
	msgbox HoennSeek_Text_ManagerAfterFeather, MSGBOX_DEFAULT
	goto HoennSeek_EventScript_LaneBRelease

@ ---- Moltres: the flyover on Route 113 ---------------------------------------------

@ Called from Route 113's OnTransition.
HoennSeek_EventScript_Route113BirdsOnTransition::
	setflag FLAG_HOENN_HIDE_ROUTE113_MOLTRES
	setflag FLAG_HOENN_HIDE_FLAME_FEATHER
	goto_if_set FLAG_HOENN_GOT_FLAME_FEATHER, HoennSeek_EventScript_LaneBReturn
	goto_if_set FLAG_HOENN_MOLTRES_CAMEO, HoennSeek_EventScript_FlameFeatherShow
	setvar VAR_TEMP_6, 1
	return
HoennSeek_EventScript_FlameFeatherShow:
	clearflag FLAG_HOENN_HIDE_FLAME_FEATHER
HoennSeek_EventScript_LaneBReturn:
	return

HoennSeek_EventScript_MoltresFlyover::
	lockall
	setvar VAR_TEMP_6, 0
	setflag FLAG_HOENN_MOLTRES_CAMEO
	msgbox HoennSeek_Text_FlyoverHeat, MSGBOX_DEFAULT
	closemessage
	setvar VAR_0x8008, 57
	setvar VAR_0x8009, 6
	call HoennSeek_EventScript_StarterPanTo
	clearflag FLAG_HOENN_HIDE_ROUTE113_MOLTRES
	addobject LOCALID_HOENN_ROUTE113_MOLTRES
	playmoncry SPECIES_MOLTRES, CRY_MODE_ENCOUNTER
	applymovement LOCALID_HOENN_ROUTE113_MOLTRES, HoennSeek_Movement_MoltresFlyover
	delay 96
	setfieldeffectargument 0, 64 @ (57,4) + MAP_OFFSET
	setfieldeffectargument 1, 11
	setfieldeffectargument 2, 0
	setfieldeffectargument 3, 1
	dofieldeffect FLDEFF_ASH_PUFF
	clearflag FLAG_HOENN_HIDE_FLAME_FEATHER
	addobject LOCALID_HOENN_FLAME_FEATHER
	waitmovement LOCALID_HOENN_ROUTE113_MOLTRES
	removeobject LOCALID_HOENN_ROUTE113_MOLTRES
	waitmoncry
	msgbox HoennSeek_Text_FlyoverPassed, MSGBOX_DEFAULT
	closemessage
	call HoennSeek_EventScript_StarterPanBack
	releaseall
	end

HoennSeek_EventScript_FlameFeather::
	lock
	msgbox HoennSeek_Text_FlameFeatherAsh, MSGBOX_DEFAULT
	giveitem ITEM_FLAME_FEATHER
	setflag FLAG_HOENN_GOT_FLAME_FEATHER
	removeobject LOCALID_HOENN_FLAME_FEATHER
	goto HoennSeek_EventScript_LaneBRelease

@ ---- The roosts ------------------------------------------------------------------

@ Each roost map's OnTransition: VAR_0x8009 = the bird; arms VAR_TEMP_6.
HoennSeek_EventScript_ArticunoRoostOnTransition::
	setvar VAR_0x8009, HOENN_BIRD_ARTICUNO
	goto HoennSeek_EventScript_BirdRoostOnTransition
HoennSeek_EventScript_ZapdosRoostOnTransition::
	setvar VAR_0x8009, HOENN_BIRD_ZAPDOS
	goto HoennSeek_EventScript_BirdRoostOnTransition
HoennSeek_EventScript_MoltresRoostOnTransition::
	setvar VAR_0x8009, HOENN_BIRD_MOLTRES
HoennSeek_EventScript_BirdRoostOnTransition:
	setvar VAR_TEMP_6, 0
	specialvar VAR_RESULT, HoennBirdRoostState
	goto_if_ne VAR_RESULT, HOENN_ROOST_CALL, HoennSeek_EventScript_LaneBReturn
	setvar VAR_TEMP_6, 1
	return

@ Seafoam B1F has no map scripts of its own.
HoennSeek_EventScript_SeafoamB1FOnTransition::
	call HoennSeek_EventScript_ArticunoRoostOnTransition
	end

@ The calls: the feather reacts, the bird flies down onto its roost.
HoennSeek_EventScript_ArticunoRoostCall::
	lockall
	setvar VAR_TEMP_6, 0
	msgbox HoennSeek_Text_FrostFeatherGlows, MSGBOX_DEFAULT
	closemessage
	playmoncry SPECIES_ARTICUNO, CRY_MODE_ENCOUNTER
	setvar VAR_0x8009, HOENN_BIRD_ARTICUNO
	special HoennBirdLand
	setobjectxyperm LOCALID_SEAFOAM_ARTICUNO, 31, 25
	addobject LOCALID_SEAFOAM_ARTICUNO
	applymovement LOCALID_SEAFOAM_ARTICUNO, HoennSeek_Movement_BirdLand
	waitmovement 0
	setobjectxyperm LOCALID_SEAFOAM_ARTICUNO, 31, 31
	waitmoncry
	msgbox HoennSeek_Text_ArticunoLanded, MSGBOX_DEFAULT
	releaseall
	end

HoennSeek_EventScript_ZapdosRoostCall::
	lockall
	setvar VAR_TEMP_6, 0
	msgbox HoennSeek_Text_ThunderFeatherCrackles, MSGBOX_DEFAULT
	closemessage
	playse SE_THUNDER
	playmoncry SPECIES_ZAPDOS, CRY_MODE_ENCOUNTER
	setvar VAR_0x8009, HOENN_BIRD_ZAPDOS
	special HoennBirdLand
	setobjectxyperm LOCALID_ROUTE10_ZAPDOS, 5, 42
	addobject LOCALID_ROUTE10_ZAPDOS
	applymovement LOCALID_ROUTE10_ZAPDOS, HoennSeek_Movement_BirdLand
	waitmovement 0
	setobjectxyperm LOCALID_ROUTE10_ZAPDOS, 5, 48
	waitmoncry
	msgbox HoennSeek_Text_ZapdosLanded, MSGBOX_DEFAULT
	releaseall
	end

HoennSeek_EventScript_MoltresRoostCall::
	lockall
	setvar VAR_TEMP_6, 0
	msgbox HoennSeek_Text_FlameFeatherBurns, MSGBOX_DEFAULT
	closemessage
	playmoncry SPECIES_MOLTRES, CRY_MODE_ENCOUNTER
	setvar VAR_0x8009, HOENN_BIRD_MOLTRES
	special HoennBirdLand
	setobjectxyperm LOCALID_MTSILVER_MOLTRES, 11, 18
	addobject LOCALID_MTSILVER_MOLTRES
	applymovement LOCALID_MTSILVER_MOLTRES, HoennSeek_Movement_BirdLandFromLeft
	waitmovement 0
	setobjectxyperm LOCALID_MTSILVER_MOLTRES, 17, 18
	waitmoncry
	msgbox HoennSeek_Text_MoltresLanded, MSGBOX_DEFAULT
	releaseall
	end

@ The battles (the birds' object scripts): HnS's Lv 50 legendary battle, then
@ HoennBirdBattleEnded decides whether the bird leaves.
HoennSeek_EventScript_ArticunoRoost::
	lock
	faceplayer
	playmoncry SPECIES_ARTICUNO, CRY_MODE_ENCOUNTER
	msgbox SeafoamIslands_B1F_Text_ArticunoBattle
	delay 40
	waitmoncry
	seteventmon SPECIES_ARTICUNO, 50
	special BattleSetup_StartLegendaryBattle
	waitstate
	setvar VAR_0x8009, HOENN_BIRD_ARTICUNO
	specialvar VAR_RESULT, HoennBirdBattleEnded
	goto_if_eq VAR_RESULT, FALSE, HoennSeek_EventScript_LaneBRelease
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_SEAFOAM_ARTICUNO
	fadescreenswapbuffers FADE_FROM_BLACK
	goto HoennSeek_EventScript_LaneBRelease

HoennSeek_EventScript_ZapdosRoost::
	lock
	faceplayer
	playmoncry SPECIES_ZAPDOS, CRY_MODE_ENCOUNTER
	msgbox SeafoamIslands_B1F_Text_ArticunoBattle
	delay 40
	waitmoncry
	seteventmon SPECIES_ZAPDOS, 50
	special BattleSetup_StartLegendaryBattle
	waitstate
	setvar VAR_0x8009, HOENN_BIRD_ZAPDOS
	specialvar VAR_RESULT, HoennBirdBattleEnded
	goto_if_eq VAR_RESULT, FALSE, HoennSeek_EventScript_LaneBRelease
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_ROUTE10_ZAPDOS
	fadescreenswapbuffers FADE_FROM_BLACK
	goto HoennSeek_EventScript_LaneBRelease

HoennSeek_EventScript_MoltresRoost::
	lock
	faceplayer
	playmoncry SPECIES_MOLTRES, CRY_MODE_ENCOUNTER
	msgbox SeafoamIslands_B1F_Text_ArticunoBattle
	delay 40
	waitmoncry
	seteventmon SPECIES_MOLTRES, 50
	special BattleSetup_StartLegendaryBattle
	waitstate
	setvar VAR_0x8009, HOENN_BIRD_MOLTRES
	specialvar VAR_RESULT, HoennBirdBattleEnded
	goto_if_eq VAR_RESULT, FALSE, HoennSeek_EventScript_LaneBRelease
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_MTSILVER_MOLTRES
	fadescreenswapbuffers FADE_FROM_BLACK
	goto HoennSeek_EventScript_LaneBRelease

@ ---- May's call -------------------------------------------------------------------

HoennSeek_EventScript_CallBirds::
	setflag FLAG_HOENN_CALL_BIRDS
	setspeaker HoennSeek_Text_NameMay
	pokenavcall HoennSeek_Text_CallBirds
	goto HoennSeek_EventScript_CallEnd

@ ---- Part 34a movements -------------------------------------------------------------

HoennSeek_Movement_BirdLand:
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_fast_down
	walk_slow_down
	face_down
	step_end

@ Moltres comes in from the side of its pit (you stand at the foot of the
@ stairs, above its roost).
HoennSeek_Movement_BirdLandFromLeft:
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_fast_right
	walk_slow_right
	face_up
	step_end

@ From (65,9), off screen east of the camera at (57,6), to (47,1), off screen
@ to the north-west.
HoennSeek_Movement_MoltresFlyover:
	walk_fast_left
	walk_fast_left
	walk_fast_up
	walk_fast_left
	walk_fast_left
	walk_fast_up
	walk_fast_left
	walk_fast_left
	walk_fast_up
	walk_fast_left
	walk_fast_left
	walk_fast_up
	walk_fast_left
	walk_fast_left
	walk_fast_up
	walk_fast_left
	walk_fast_left
	walk_fast_up
	walk_fast_left
	walk_fast_left
	walk_fast_up
	walk_fast_left
	walk_fast_left
	walk_fast_up
	walk_fast_left
	walk_fast_left
	step_end

@ ---- Part 34a texts ---------------------------------------------------------------

HoennSeek_Text_BillBirdsIntro:
	.string "BILL: Oh, hey! You've been to\n"
	.string "HOENN, haven't you? Lucky!\p"
	.string "I've hooked my PC network up to\n"
	.string "trainers all over, and I'm using\l"
	.string "it to track three legendary birds:\l"
	.string "ARTICUNO, ZAPDOS and MOLTRES.\p"
	.string "Here's the funny thing. Every\n"
	.string "report mentions a feather.\p"
	.string "I think each bird drops one\n"
	.string "somewhere, and if you carry it\l"
	.string "back to where the bird roosts,\l"
	.string "the bird comes to see who has it!$"

HoennSeek_Text_BillBirdsReport:
	.string "BILL: Here's what my network\n"
	.string "has picked up so far…$"

HoennSeek_Text_BillArticunoClue:
	.string "ARTICUNO: a trainer in HOENN saw\n"
	.string "an icy glow deep in SHOAL CAVE,\l"
	.string "off ROUTE 125.\p"
	.string "An ice bird would leave its\n"
	.string "feather where it's coldest.$"

HoennSeek_Text_BillArticunoRoost:
	.string "ARTICUNO: you've got its FROST\n"
	.string "FEATHER! It roosts deep in the\l"
	.string "SEAFOAM ISLANDS, on the island in\l"
	.string "the middle of the cold water.$"

HoennSeek_Text_BillArticunoCaught:
	.string "ARTICUNO: it's with you now. Wow!$"

HoennSeek_Text_BillZapdosClue:
	.string "ZAPDOS: the POWER PLANT on\n"
	.string "ROUTE 10 has trouble whenever\l"
	.string "a thunderstorm hits.\p"
	.string "Lightning hits the roof, and the\n"
	.string "manager finds strange things in\l"
	.string "his generator. Ask him on a\l"
	.string "stormy day!$"

HoennSeek_Text_BillZapdosRoost:
	.string "ZAPDOS: you've got its THUNDER\n"
	.string "FEATHER! It roosts in the yard\l"
	.string "behind the POWER PLANT. The back\l"
	.string "door is in the generator room.$"

HoennSeek_Text_BillZapdosCaught:
	.string "ZAPDOS: it's with you now. Wow!$"

HoennSeek_Text_BillMoltresClue:
	.string "MOLTRES: hikers in HOENN keep\n"
	.string "seeing a burning shadow over the\l"
	.string "ash on ROUTE 113.\p"
	.string "Something that hot would shed a\n"
	.string "feather or two!$"

HoennSeek_Text_BillMoltresRoost:
	.string "MOLTRES: you've got its FLAME\n"
	.string "FEATHER! It roosts on MT. SILVER,\l"
	.string "in the big cave with the stone\l"
	.string "pit, past the waterfall.$"

HoennSeek_Text_BillMoltresCaught:
	.string "MOLTRES: it's with you now. Wow!$"

HoennSeek_Text_BillBirdsBye:
	.string "BILL: Come back and tell me how\n"
	.string "it goes, okay? My network loves\l"
	.string "a good story!$"

HoennSeek_Text_BillBirdsAllCaught:
	.string "BILL: You caught all three birds!\n"
	.string "My network's gone wild!\p"
	.string "Hang on to those feathers, okay?\p"
	.string "A man in AZALEA posted an old\n"
	.string "song about fire, ice and thunder.\l"
	.string "It says their feathers, together,\l"
	.string "wake something under the sea…$"

HoennSeek_Text_ManagerStormHint:
	.string "MANAGER: My beloved generator\n"
	.string "runs like a dream now…\p"
	.string "Except on thunderstorm days!\n"
	.string "Lightning hits the roof, and my\l"
	.string "generator sparks like crazy!\p"
	.string "Last storm, I found a gold feather\n"
	.string "stuck to the coils. It blew away\l"
	.string "before I could grab it.$"

HoennSeek_Text_ManagerStorm:
	.string "MANAGER: Did you hear that crash?\n"
	.string "Lightning hit the roof again!\p"
	.string "And look what came down the cable\n"
	.string "into my generator…\p"
	.string "A gold feather, fizzing with\n"
	.string "sparks! It shorts out everything\l"
	.string "it touches.\p"
	.string "Please, take it away from my\n"
	.string "precious machine!$"

HoennSeek_Text_ManagerYard:
	.string "MANAGER: The sparks always come\n"
	.string "from the yard out the back door.\p"
	.string "Something big sits out there when\n"
	.string "it storms. I don't go and look!$"

HoennSeek_Text_ManagerAfterFeather:
	.string "MANAGER: My generator has been as\n"
	.string "calm as a MAREEP since you took\l"
	.string "that feather. Thank you!$"

HoennSeek_Text_FlyoverHeat:
	.string "The ash underfoot is warm…\n"
	.string "Something is coming!$"

HoennSeek_Text_FlyoverPassed:
	.string "A great bird of flame swept over\n"
	.string "ROUTE 113, heading north-west!\p"
	.string "Something dropped into the ash\n"
	.string "where it passed…$"

HoennSeek_Text_FlameFeatherAsh:
	.string "A red feather lies in the ash,\n"
	.string "still glowing like an ember.$"

HoennSeek_Text_FrostFeatherGlows:
	.string "The FROST FEATHER is glowing with\n"
	.string "a cold blue light…\p"
	.string "A chill wind sweeps over the water!$"

HoennSeek_Text_ArticunoLanded:
	.string "ARTICUNO came down to its roost!\n"
	.string "It's watching the FROST FEATHER…$"

HoennSeek_Text_ThunderFeatherCrackles:
	.string "The THUNDER FEATHER is crackling\n"
	.string "with sparks…\p"
	.string "The air smells like a storm!$"

HoennSeek_Text_ZapdosLanded:
	.string "ZAPDOS came down to its roost!\n"
	.string "Its eyes are fixed on your\l"
	.string "THUNDER FEATHER…$"

HoennSeek_Text_FlameFeatherBurns:
	.string "The FLAME FEATHER is burning\n"
	.string "brighter and brighter…\p"
	.string "The cave is suddenly hot!$"

HoennSeek_Text_MoltresLanded:
	.string "MOLTRES came down to its roost!\n"
	.string "It's watching the FLAME FEATHER…$"

HoennSeek_Text_CallBirds:
	.string "Hi, {PLAYER}! It's MAY!\p"
	.string "BILL from GOLDENROD just phoned\n"
	.string "Professor BIRCH, all excited.\p"
	.string "His PC network picked up a report\n"
	.string "of a legendary bird coming down\l"
	.string "right where you were standing!\p"
	.string "The Professor wants to hear\n"
	.string "everything. So do I!\p"
	.string "Did its feather really bring it\n"
	.string "to you? I want the whole story!$"

@ ==========================================================================
@ Part 29: shifting tunnels (Rock Tunnel's Onix, Dark Cave's Dunsparce,
@ Route 21's Tangela vines)
@ ==========================================================================
@ - Onix: at night, a fresh hole opens in a different wall of Rock Tunnel B1F
@   each weekday (sOnixHoles in src/hoenn_lane_b.c; B1F's warps 6-12, which only
@   work while their hole is drawn). It leads into the Onix's bore
@   (RockTunnel_OnixBore_hoenn), where a shiny Onix that knows Diamond Storm
@   rests in the chamber at night. Run: it stays. Knocked out: back tomorrow
@   night. Caught: gone (the holes keep opening at night, so the chamber's items
@   and the Metal Coat under its resting spot can still be fetched). The first
@   time each night you enter B1F while it's there, the tunnel rumbles.
@ - Dunsparce: Dark Cave's south side has four burrow holes, one open in each
@   time of day (sBurrowHoles; warps 3-6). All drop into the burrow
@   (DarkCave_Burrow_hoenn). The first visit in each time of day, a Dunsparce
@   digs one row of rubble out of the passage to the chamber; after all four,
@   a Three-Segment Dudunsparce sleeps there. Knocked out: back tomorrow.
@ - Tangela: four Tangela wrap a shiny one on Route 21's islet near Pallet
@   (5-7, 28-30). They writhe and won't let you near, except in the morning,
@   when they lie limp a step away. The shiny one knows AncientPower and holds
@   a Big Root; a Miracle Seed is hidden where it sat.
@ - Levels follow your progress (HoennSetupProgressWildBattle, 5 below your
@   level cap; never below 40 for the Onix, 32 for the Dudunsparce, 30 for the
@   Tangela).

	.include "data/maps/RockTunnel_OnixBore_hoenn/scripts.inc"
	.include "data/maps/DarkCave_Burrow_hoenn/scripts.inc"

@ ---- Onix: Rock Tunnel B1F -------------------------------------------------

HoennSeek_EventScript_RockTunnelB1FOnLoad::
	special HoennDrawOnixHole
	end

@ From B1F's OnTransition: arms the rumble the first time tonight.
HoennSeek_EventScript_RockTunnelB1FOnTransition::
	goto_if_set FLAG_HOENN_ONIX_CAUGHT, HoennSeek_EventScript_LaneBReturn
	goto_if_set FLAG_HOENN_DAILY_ONIX_GONE, HoennSeek_EventScript_LaneBReturn
	goto_if_set FLAG_HOENN_DAILY_ONIX_RUMBLE, HoennSeek_EventScript_LaneBReturn
	specialvar VAR_RESULT, HoennOnixHoleTonight
	goto_if_eq VAR_RESULT, HOENN_ONIX_NO_HOLE, HoennSeek_EventScript_LaneBReturn
	setvar VAR_TEMP_5, 1
	return

HoennSeek_EventScript_RockTunnelB1FOnFrame::
	map_script_2 VAR_TEMP_5, 1, HoennSeek_EventScript_OnixRumble
	.2byte 0

HoennSeek_EventScript_OnixRumble::
	lockall
	setvar VAR_TEMP_5, 2
	setflag FLAG_HOENN_DAILY_ONIX_RUMBLE
	playse SE_M_EARTHQUAKE
	setvar VAR_0x8004, 1  @ vertical pan
	setvar VAR_0x8005, 2  @ horizontal pan
	setvar VAR_0x8006, 10 @ number of shakes
	setvar VAR_0x8007, 4  @ shake delay
	special ShakeCamera
	waitstate
	msgbox HoennSeek_Text_OnixRumble, MSGBOX_DEFAULT
	releaseall
	end

@ ---- Onix: the bore ----------------------------------------------------------

HoennSeek_EventScript_BoreExit::
	special HoennOnixHoleExit
	warp MAP_ROCK_TUNNEL_B1F_HNS, VAR_0x8008, VAR_0x8009
	waitstate
	end

HoennSeek_EventScript_BoreOnix::
	lock
	setflag FLAG_HOENN_ONIX_FOUND
	playmoncry SPECIES_ONIX, CRY_MODE_ENCOUNTER
	msgbox HoennSeek_Text_BoreOnix, MSGBOX_DEFAULT
	waitmoncry
	closemessage
	setvar VAR_0x8004, SPECIES_ONIX
	setvar VAR_0x8005, 40
	special HoennSetupProgressWildBattle
	setvar VAR_0x8005, MOVE_DIAMOND_STORM
	setvar VAR_0x8006, FALSE
	setvar VAR_0x8007, ITEM_NONE
	setvar VAR_0x8008, 0
	setvar VAR_0x8009, HOENN_TUNE_SHINY
	special HoennTuneWildMonSlot
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, HoennSeek_EventScript_BoreOnixCaught
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, HoennSeek_EventScript_BoreOnixGone
	release
	end

HoennSeek_EventScript_BoreOnixCaught::
	setflag FLAG_HOENN_ONIX_CAUGHT
	goto HoennSeek_EventScript_BoreOnixLeaves

HoennSeek_EventScript_BoreOnixGone::
	setflag FLAG_HOENN_DAILY_ONIX_GONE
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_HOENN_BORE_ONIX
	fadescreenswapbuffers FADE_FROM_BLACK
	msgbox HoennSeek_Text_BoreOnixFled, MSGBOX_DEFAULT
	release
	end

HoennSeek_EventScript_BoreOnixLeaves::
	removeobject LOCALID_HOENN_BORE_ONIX
	msgbox HoennSeek_Text_BoreOnixSpot, MSGBOX_DEFAULT
	release
	end

HoennSeek_EventScript_BoreIronBall::
	finditem ITEM_IRON_BALL
	end

HoennSeek_EventScript_BoreStarPiece::
	finditem ITEM_STAR_PIECE
	end

HoennSeek_EventScript_BoreBigNugget::
	finditem ITEM_BIG_NUGGET
	end

@ ---- Dunsparce: Dark Cave --------------------------------------------------

HoennSeek_EventScript_DarkCaveSouthOnLoad::
	special HoennDrawBurrowHole
	end

@ The burrow's ON_FRAME (VAR_TEMP_1 1): this time of day's Dunsparce digs out
@ one row of rubble, then burrows away into the wall.
HoennSeek_EventScript_BurrowDig::
	lockall
	setvar VAR_TEMP_1, 2
	playmoncry SPECIES_DUNSPARCE, CRY_MODE_NORMAL
	msgbox HoennSeek_Text_BurrowDigger, MSGBOX_DEFAULT
	waitmoncry
	closemessage
	applymovement LOCALID_HOENN_BURROW_DIGGER, HoennSeek_Movement_BurrowDig
	waitmovement 0
	playse SE_M_DIG
	specialvar VAR_RESULT, HoennBurrowDig
	copyvar VAR_0x800A, VAR_0x8008
	addvar VAR_0x800A, 7
	setfieldeffectargument 0, 17
	setfieldeffectargument 1, VAR_0x800A
	setfieldeffectargument 2, 0
	setfieldeffectargument 3, 1
	dofieldeffect FLDEFF_ASH_PUFF
	setfieldeffectargument 0, 18
	dofieldeffect FLDEFF_ASH_PUFF
	setmetatile 10, VAR_0x8008, 0x281, FALSE
	setmetatile 11, VAR_0x8008, 0x281, FALSE
	special DrawWholeMapView
	delay 20
	applymovement LOCALID_HOENN_BURROW_DIGGER, HoennSeek_Movement_BurrowAway
	waitmovement 0
	removeobject LOCALID_HOENN_BURROW_DIGGER
	goto_if_eq VAR_RESULT, 0, HoennSeek_EventScript_BurrowOpen
	buffernumberstring STR_VAR_1, VAR_RESULT
	msgbox HoennSeek_Text_BurrowDug, MSGBOX_DEFAULT
	releaseall
	end

HoennSeek_EventScript_BurrowOpen::
	clearflag FLAG_HOENN_HIDE_DUDUNSPARCE
	addobject LOCALID_HOENN_DUDUNSPARCE
	msgbox HoennSeek_Text_BurrowOpen, MSGBOX_DEFAULT
	releaseall
	end

@ Talking to the digger before its scene plays (it can't, the scene comes first).
HoennSeek_EventScript_BurrowDigger::
	lock
	playmoncry SPECIES_DUNSPARCE, CRY_MODE_NORMAL
	msgbox HoennSeek_Text_BurrowDiggerBusy, MSGBOX_DEFAULT
	waitmoncry
	release
	end

HoennSeek_EventScript_BurrowDudunsparce::
	lock
	playmoncry SPECIES_DUDUNSPARCE_THREE_SEGMENT, CRY_MODE_ENCOUNTER
	msgbox HoennSeek_Text_BurrowDudunsparce, MSGBOX_DEFAULT
	waitmoncry
	closemessage
	setvar VAR_0x8004, SPECIES_DUDUNSPARCE_THREE_SEGMENT
	setvar VAR_0x8005, 32
	special HoennSetupProgressWildBattle
	setvar VAR_0x8005, MOVE_NONE
	setvar VAR_0x8006, FALSE
	setvar VAR_0x8007, ITEM_NONE
	setvar VAR_0x8008, 0
	setvar VAR_0x8009, 0
	special HoennTuneWildMonSlot
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, HoennSeek_EventScript_BurrowDudunsparceCaught
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, HoennSeek_EventScript_BurrowDudunsparceGone
	release
	end

HoennSeek_EventScript_BurrowDudunsparceCaught::
	setflag FLAG_HOENN_DUDUNSPARCE_CAUGHT
	removeobject LOCALID_HOENN_DUDUNSPARCE
	release
	end

HoennSeek_EventScript_BurrowDudunsparceGone::
	setflag FLAG_HOENN_DAILY_DUDUNSPARCE_GONE
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_HOENN_DUDUNSPARCE
	fadescreenswapbuffers FADE_FROM_BLACK
	msgbox HoennSeek_Text_BurrowDudunsparceFled, MSGBOX_DEFAULT
	release
	end

HoennSeek_Movement_BurrowDig:
	walk_in_place_up
	walk_in_place_up
	walk_in_place_up
	walk_in_place_up
	step_end

HoennSeek_Movement_BurrowAway:
	walk_up
	walk_in_place_fast_up
	walk_in_place_fast_up
	step_end

@ ---- Tangela: Route 21's islet ------------------------------------------------

@ From Route 21's OnTransition: the shiny one shows unless caught or knocked
@ out today; in the morning the vines lie limp a step back from it.
HoennSeek_EventScript_Route21OnTransition::
	goto_if_set FLAG_HOENN_TANGELA_CAUGHT, HoennSeek_EventScript_LaneBReturn
	clearflag FLAG_HOENN_HIDE_TANGELA
	call_if_set FLAG_HOENN_DAILY_TANGELA_GONE, HoennSeek_EventScript_IsletTangelaAway
	gettimeofday
	goto_if_ne VAR_0x8000, HOENN_TIME_MORNING, HoennSeek_EventScript_LaneBReturn
	setobjectxyperm LOCALID_HOENN_ISLET_VINE_1, 6, 27
	setobjectxyperm LOCALID_HOENN_ISLET_VINE_2, 4, 29
	setobjectxyperm LOCALID_HOENN_ISLET_VINE_3, 9, 30
	setobjectxyperm LOCALID_HOENN_ISLET_VINE_4, 5, 31
	setobjectmovementtype LOCALID_HOENN_ISLET_VINE_1, MOVEMENT_TYPE_FACE_DOWN
	setobjectmovementtype LOCALID_HOENN_ISLET_VINE_2, MOVEMENT_TYPE_FACE_RIGHT
	setobjectmovementtype LOCALID_HOENN_ISLET_VINE_3, MOVEMENT_TYPE_FACE_LEFT
	setobjectmovementtype LOCALID_HOENN_ISLET_VINE_4, MOVEMENT_TYPE_FACE_UP
	return

HoennSeek_EventScript_IsletTangelaAway::
	setflag FLAG_HOENN_HIDE_TANGELA
	return

HoennSeek_EventScript_IsletVines::
	lock
	setflag FLAG_HOENN_TANGELA_SEEN
	gettimeofday
	goto_if_eq VAR_0x8000, HOENN_TIME_MORNING, HoennSeek_EventScript_IsletVinesLimp
	playmoncry SPECIES_TANGELA, CRY_MODE_NORMAL
	msgbox HoennSeek_Text_IsletVines, MSGBOX_DEFAULT
	waitmoncry
	release
	end

HoennSeek_EventScript_IsletVinesLimp::
	msgbox HoennSeek_Text_IsletVinesLimp, MSGBOX_DEFAULT
	release
	end

HoennSeek_EventScript_IsletTangela::
	lock
	faceplayer
	setflag FLAG_HOENN_TANGELA_SEEN
	playmoncry SPECIES_TANGELA, CRY_MODE_ENCOUNTER
	msgbox HoennSeek_Text_IsletTangela, MSGBOX_DEFAULT
	waitmoncry
	closemessage
	setvar VAR_0x8004, SPECIES_TANGELA
	setvar VAR_0x8005, 30
	special HoennSetupProgressWildBattle
	setvar VAR_0x8005, MOVE_ANCIENT_POWER
	setvar VAR_0x8006, FALSE
	setvar VAR_0x8007, ITEM_BIG_ROOT
	setvar VAR_0x8008, 0
	setvar VAR_0x8009, HOENN_TUNE_SHINY
	special HoennTuneWildMonSlot
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, HoennSeek_EventScript_IsletTangelaCaught
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, HoennSeek_EventScript_IsletTangelaGone
	release
	end

HoennSeek_EventScript_IsletTangelaCaught::
	setflag FLAG_HOENN_TANGELA_CAUGHT
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_HOENN_ISLET_TANGELA
	removeobject LOCALID_HOENN_ISLET_VINE_1
	removeobject LOCALID_HOENN_ISLET_VINE_2
	removeobject LOCALID_HOENN_ISLET_VINE_3
	removeobject LOCALID_HOENN_ISLET_VINE_4
	fadescreenswapbuffers FADE_FROM_BLACK
	msgbox HoennSeek_Text_IsletVinesGone, MSGBOX_DEFAULT
	release
	end

HoennSeek_EventScript_IsletTangelaGone::
	setflag FLAG_HOENN_DAILY_TANGELA_GONE
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_HOENN_ISLET_TANGELA
	fadescreenswapbuffers FADE_FROM_BLACK
	msgbox HoennSeek_Text_IsletTangelaFled, MSGBOX_DEFAULT
	release
	end

@ ---- Brendan's call -------------------------------------------------------------

HoennSeek_EventScript_CallTunnels::
	setflag FLAG_HOENN_CALL_TUNNELS
	setspeaker HoennSeek_Text_NameBrendan
	pokenavcall HoennSeek_Text_CallTunnels
	goto HoennSeek_EventScript_CallEnd

@ ---- Part 29 texts ----------------------------------------------------------

HoennSeek_Text_OnixRumble:
	.string "The ground shakes!\p"
	.string "Something huge is boring through\n"
	.string "the rock somewhere nearby…\p"
	.string "A fresh hole must have opened in\n"
	.string "one of these walls tonight.$"

HoennSeek_Text_BoreOnix:
	.string "A huge ONIX rests in its chamber.\p"
	.string "Its body glitters like crystal in\n"
	.string "the dark!$"

HoennSeek_Text_BoreOnixFled:
	.string "The ONIX bored away into the rock.\p"
	.string "It will be back to rest here\n"
	.string "tomorrow night.$"

HoennSeek_Text_BoreOnixSpot:
	.string "Something glints in the dirt where\n"
	.string "the ONIX was lying.$"

HoennSeek_Text_BurrowDigger:
	.string "A DUNSPARCE is chewing at the\n"
	.string "rubble in the passage!$"

HoennSeek_Text_BurrowDiggerBusy:
	.string "The DUNSPARCE is too busy digging\n"
	.string "to notice you.$"

HoennSeek_Text_BurrowDug:
	.string "It cleared away a whole row of\n"
	.string "rubble and wriggled into the wall!\p"
	.string "There's still rubble in the way.\n"
	.string "Rows left: {STR_VAR_1}.\p"
	.string "Another DUNSPARCE might come at\n"
	.string "a different time of day.$"

HoennSeek_Text_BurrowOpen:
	.string "The last of the rubble fell away!\p"
	.string "The passage is open, and something\n"
	.string "is snoring at the far end…$"

HoennSeek_Text_BurrowDudunsparce:
	.string "A DUDUNSPARCE is curled up at the\n"
	.string "end of its burrow.\p"
	.string "It has three segments!\n"
	.string "It's waking up!$"

HoennSeek_Text_BurrowDudunsparceFled:
	.string "The DUDUNSPARCE burrowed away.\p"
	.string "It will come back to sleep\n"
	.string "here tomorrow.$"

HoennSeek_Text_IsletVines:
	.string "A tangle of writhing vines guards\n"
	.string "the middle of the islet.\p"
	.string "They squirm away from your hand.\n"
	.string "Even CUT couldn't get through.$"

HoennSeek_Text_IsletVinesLimp:
	.string "The vines lie limp in the morning\n"
	.string "sun. They're fast asleep.$"

HoennSeek_Text_IsletTangela:
	.string "The TANGELA in the middle of the\n"
	.string "vines is a different color!$"

HoennSeek_Text_IsletTangelaFled:
	.string "The TANGELA dove into the sea.\p"
	.string "It will come back to the\n"
	.string "islet tomorrow.$"

HoennSeek_Text_IsletVinesGone:
	.string "The other TANGELA slipped into the\n"
	.string "sea and swam away.$"

HoennSeek_Text_CallTunnels:
	.string "Hey, {PLAYER}! It's BRENDAN.\p"
	.string "A hiker from LAVENDER phoned the\n"
	.string "lab. He's been mapping ROCK TUNNEL\l"
	.string "for Dad for years.\p"
	.string "He swears he saw a trainer walk\n"
	.string "out of a hole in the wall with an\l"
	.string "ONIX that sparkled like crystal!\p"
	.string "That was you, right? Dad wants to\n"
	.string "see it. Bring it to HOENN sometime!$"

@ ==========================================================================
@ Part 30a: the lost Kangaskhan baby (Fuchsia Safari Zone)
@ ==========================================================================
@ Evenings (once the BRUSH is open to you, SAFARI LEVEL 2), a Kangaskhan baby
@ cries on the BEACH's sand at (39,36). Say YES and it follows you like your
@ follower Pokémon, drawn with its own sprite (src/hoenn_lane_b.c,
@ HoennFollowerOverride). Its mother paces in a nook of the BRUSH's woods (4,15),
@ reached through the grass notch at (8-9,17-18); stepping into the nook with
@ the baby (triggers at x 7, rows 17-18) plays the reunion and she gives a
@ LUCKY EGG. Afterwards the pair sit there together. If the Safari game ends
@ first, the entrance clears the follow flag and the baby is back on the BEACH
@ the next evening.

HoennSeek_EventScript_SafariBeachOnTransition::
	setflag FLAG_HOENN_HIDE_KANGA_BABY
	goto_if_set FLAG_HOENN_KANGA_REUNITED, HoennSeek_EventScript_LaneBEnd
	goto_if_set FLAG_HOENN_KANGA_BABY_FOLLOWING, HoennSeek_EventScript_LaneBEnd
	goto_if_lt VAR_KANTO_SAFARI_ZONE_PROGRESS, 2, HoennSeek_EventScript_LaneBEnd
	gettimeofday
	goto_if_ne VAR_0x8000, HOENN_TIME_EVENING, HoennSeek_EventScript_LaneBEnd
	clearflag FLAG_HOENN_HIDE_KANGA_BABY
	end

HoennSeek_EventScript_SafariBrushOnTransition::
	setflag FLAG_HOENN_HIDE_KANGA_PAIR_BABY
	goto_if_set FLAG_HOENN_KANGA_REUNITED, HoennSeek_EventScript_KangaPairShow
	goto_if_unset FLAG_HOENN_KANGA_BABY_FOLLOWING, HoennSeek_EventScript_LaneBEnd
	setvar VAR_TEMP_1, 1
	end

HoennSeek_EventScript_KangaPairShow:
	clearflag FLAG_HOENN_HIDE_KANGA_PAIR_BABY
	end

HoennSeek_EventScript_KangaBaby::
	lock
	faceplayer
	playmoncry SPECIES_KANGASKHAN, CRY_MODE_HIGH_PITCH
	msgbox HoennSeek_Text_KangaBaby, MSGBOX_DEFAULT
	waitmoncry
	msgbox HoennSeek_Text_KangaBabyAsk, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, HoennSeek_EventScript_KangaBabyStays
	msgbox HoennSeek_Text_KangaBabyFollows, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_HOENN_KANGA_BABY_FOLLOWING
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_HOENN_KANGA_BABY
	updatefollowingmon
	fadescreenswapbuffers FADE_FROM_BLACK
	release
	end

HoennSeek_EventScript_KangaBabyStays:
	msgbox HoennSeek_Text_KangaBabyStays, MSGBOX_DEFAULT
	release
	end

@ Talking to the baby while it follows you (HoennFollowerScript).
HoennSeek_EventScript_KangaBabyFollower::
	lock
	faceplayer
	playmoncry SPECIES_KANGASKHAN, CRY_MODE_HIGH_PITCH
	msgbox HoennSeek_Text_KangaBabyFollower, MSGBOX_DEFAULT
	waitmoncry
	release
	end

HoennSeek_EventScript_KangaMother::
	lock
	faceplayer
	playmoncry SPECIES_KANGASKHAN, CRY_MODE_NORMAL
	goto_if_unset FLAG_HOENN_KANGA_REUNITED, HoennSeek_EventScript_KangaMotherAlone
	goto_if_unset FLAG_HOENN_KANGA_EGG_GIVEN, HoennSeek_EventScript_KangaMotherEgg
	msgbox HoennSeek_Text_KangaMotherAfter, MSGBOX_DEFAULT
	waitmoncry
	release
	end

HoennSeek_EventScript_KangaMotherAlone:
	msgbox HoennSeek_Text_KangaMotherAlone, MSGBOX_DEFAULT
	waitmoncry
	release
	end

HoennSeek_EventScript_KangaMotherEgg:
	msgbox HoennSeek_Text_KangaMotherEggAgain, MSGBOX_DEFAULT
	waitmoncry
	call HoennSeek_EventScript_KangaGiveEgg
	release
	end

HoennSeek_EventScript_KangaPairBaby::
	lock
	faceplayer
	playmoncry SPECIES_KANGASKHAN, CRY_MODE_HIGH_PITCH
	msgbox HoennSeek_Text_KangaPairBaby, MSGBOX_DEFAULT
	waitmoncry
	release
	end

@ The nook's entrance with the baby behind you (it walks one tile behind, so
@ it's at (8, your row)): it hops over you and runs to its mother.
HoennSeek_EventScript_KangaReunion::
	lockall
	setvar VAR_TEMP_1, 0
	playmoncry SPECIES_KANGASKHAN, CRY_MODE_HIGH_PITCH
	msgbox HoennSeek_Text_KangaReunionSniff, MSGBOX_DEFAULT
	waitmoncry
	closemessage
	clearflag FLAG_HOENN_KANGA_BABY_FOLLOWING
	updatefollowingmon
	getplayerxy VAR_0x8004, VAR_0x8005
	setobjectxyperm LOCALID_HOENN_KANGA_PAIR_BABY, 8, VAR_0x8005
	clearflag FLAG_HOENN_HIDE_KANGA_PAIR_BABY
	addobject LOCALID_HOENN_KANGA_PAIR_BABY
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceRight
	waitmovement 0
	call_if_eq VAR_0x8005, 17, HoennSeek_EventScript_KangaBabyRunsFrom17
	call_if_eq VAR_0x8005, 18, HoennSeek_EventScript_KangaBabyRunsFrom18
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceLeft
	waitmovement 0
	applymovement LOCALID_HOENN_KANGA_MOTHER, HoennSeek_Movement_KangaMotherTurns
	waitmovement 0
	playmoncry SPECIES_KANGASKHAN, CRY_MODE_ENCOUNTER
	applymovement LOCALID_HOENN_KANGA_MOTHER, HoennSeek_Movement_KangaHeart
	applymovement LOCALID_HOENN_KANGA_PAIR_BABY, HoennSeek_Movement_KangaHeart
	waitmovement LOCALID_HOENN_KANGA_PAIR_BABY
	waitmoncry
	msgbox HoennSeek_Text_KangaReunion, MSGBOX_DEFAULT
	setobjectxyperm LOCALID_HOENN_KANGA_PAIR_BABY, 5, 15
	setobjectmovementtype LOCALID_HOENN_KANGA_PAIR_BABY, MOVEMENT_TYPE_FACE_LEFT
	setflag FLAG_HOENN_KANGA_REUNITED
	call HoennSeek_EventScript_KangaGiveEgg
	releaseall
	end

HoennSeek_EventScript_KangaBabyRunsFrom17:
	applymovement LOCALID_HOENN_KANGA_PAIR_BABY, HoennSeek_Movement_KangaBabyRun17
	waitmovement 0
	return

HoennSeek_EventScript_KangaBabyRunsFrom18:
	applymovement LOCALID_HOENN_KANGA_PAIR_BABY, HoennSeek_Movement_KangaBabyRun18
	waitmovement 0
	return

HoennSeek_EventScript_KangaGiveEgg:
	msgbox HoennSeek_Text_KangaEgg, MSGBOX_DEFAULT
	giveitem ITEM_LUCKY_EGG
	goto_if_eq VAR_RESULT, FALSE, HoennSeek_EventScript_KangaEggNoRoom
	setflag FLAG_HOENN_KANGA_EGG_GIVEN
	msgbox HoennSeek_Text_KangaEggAfter, MSGBOX_DEFAULT
	return

HoennSeek_EventScript_KangaEggNoRoom:
	msgbox HoennSeek_Text_KangaEggNoRoom, MSGBOX_DEFAULT
	return

HoennSeek_EventScript_CallKangaskhan::
	setflag FLAG_HOENN_CALL_KANGASKHAN
	setspeaker HoennSeek_Text_NameMay
	pokenavcall HoennSeek_Text_CallKangaskhan
	goto HoennSeek_EventScript_CallEnd

@ From (8,17): over you to (6,17), left to (5,17), up beside its mother.
HoennSeek_Movement_KangaBabyRun17:
	jump_2_left
	walk_fast_left
	walk_fast_up
	walk_fast_up
	face_left
	step_end

@ From (8,18): over you to (6,18), left to (5,18), up beside its mother.
HoennSeek_Movement_KangaBabyRun18:
	jump_2_left
	walk_fast_left
	walk_fast_up
	walk_fast_up
	walk_fast_up
	face_left
	step_end

HoennSeek_Movement_KangaMotherTurns:
	face_right
	step_end

HoennSeek_Movement_KangaHeart:
	emote_heart
	step_end

@ ---- Part 30a texts ---------------------------------------------------------

HoennSeek_Text_KangaBaby:
	.string "A tiny KANGASKHAN is crying all\n"
	.string "alone at the water's edge!\p"
	.string "It must have wandered off from\n"
	.string "its mother and gotten lost.$"

HoennSeek_Text_KangaBabyAsk:
	.string "It's looking up at you with big,\n"
	.string "wet eyes. Help it find its mother?$"

HoennSeek_Text_KangaBabyFollows:
	.string "The baby grabs your leg and won't\n"
	.string "let go. It's coming with you!\p"
	.string "Better find its mother before your\n"
	.string "SAFARI GAME ends.$"

HoennSeek_Text_KangaBabyStays:
	.string "The baby sniffles and curls up on\n"
	.string "the sand. It keeps crying…$"

HoennSeek_Text_KangaBabyFollower:
	.string "The baby clings to you. It keeps\n"
	.string "sniffing the air and peering\l"
	.string "toward the woods of the BRUSH.$"

HoennSeek_Text_KangaMotherAlone:
	.string "The KANGASKHAN paces back and\n"
	.string "forth, peering out of the woods.\p"
	.string "Its pouch is empty…$"

HoennSeek_Text_KangaReunionSniff:
	.string "The baby squeals and wriggles!\n"
	.string "It smells something up ahead!$"

HoennSeek_Text_KangaReunion:
	.string "The baby runs to its mother and\n"
	.string "hugs her leg. Together again!$"

HoennSeek_Text_KangaEgg:
	.string "The mother KANGASKHAN nudges\n"
	.string "something to you with her nose.$"

HoennSeek_Text_KangaEggAfter:
	.string "A LUCKY EGG! She must have been\n"
	.string "keeping it safe in her nest.$"

HoennSeek_Text_KangaEggNoRoom:
	.string "Your BAG is too full to take it.\n"
	.string "She'll keep it safe for now.$"

HoennSeek_Text_KangaMotherEggAgain:
	.string "The KANGASKHAN still has something\n"
	.string "for you, tucked in the grass.$"

HoennSeek_Text_KangaMotherAfter:
	.string "The KANGASKHAN keeps a calm watch\n"
	.string "over its baby. It looks content.$"

HoennSeek_Text_KangaPairBaby:
	.string "The baby peeks out of the grass\n"
	.string "and squeaks happily at you!$"

HoennSeek_Text_CallKangaskhan:
	.string "Hi, {PLAYER}! It's MAY!\p"
	.string "One of PROF. BIRCH's aides does\n"
	.string "fieldwork at the FUCHSIA SAFARI\l"
	.string "ZONE, and the warden told her a\l"
	.string "story about you!\p"
	.string "You walked a lost KANGASKHAN baby\n"
	.string "all the way back to its mother?\p"
	.string "That's so sweet! I'd have cried\n"
	.string "right along with it!$"

@ ==========================================================================
@ ==========================================================================
@ Part 30b: the Tauros stampede (Fuchsia Safari Zone)
@ ==========================================================================
@ The MOUNTAIN's east canyon (SAFARI LEVEL 3) climbs to a new highland,
@ FuchsiaCity_SafariZoneHighland_hoenn (a map connection). On Monday mornings
@ six Tauros charge back and forth across it, one per lane (rows 7, 9, 10, 12,
@ 14, 15); src/hoenn_lane_b.c's stampede task moves them and knocks you back
@ to the canyon (HoennSeek_EventScript_StampedeHit) when one runs into you.
@ Past the herd, the lead bull stands in the north cliff's nook (13,4): a
@ Paldean Tauros, this week's breed from HoennStampedeBreed (the three rotate
@ by week; caught breeds are skipped). Perfect Attack and Speed; caught or
@ knocked out, it's gone until next Monday and the herd stops to graze.
	.include "data/maps/FuchsiaCity_SafariZoneHighland_hoenn/scripts.inc"

HoennSeek_EventScript_HighlandOnTransition::
	special HoennStampedeReset
	setflag FLAG_HOENN_HIDE_STAMPEDE
	setflag FLAG_HOENN_HIDE_BULL_COMBAT
	setflag FLAG_HOENN_HIDE_BULL_BLAZE
	setflag FLAG_HOENN_HIDE_BULL_AQUA
	setvar VAR_0x8004, HOENN_MONDAY
	specialvar VAR_RESULT, HoennIsItWeekday
	goto_if_eq VAR_RESULT, FALSE, HoennSeek_EventScript_LaneBEnd
	gettimeofday
	goto_if_ne VAR_0x8000, HOENN_TIME_MORNING, HoennSeek_EventScript_LaneBEnd
	clearflag FLAG_HOENN_HIDE_STAMPEDE
	goto_if_set FLAG_HOENN_WEEKLY_LEAD_BULL, HoennSeek_EventScript_LaneBEnd
	specialvar VAR_RESULT, HoennStampedeBreed
	switch VAR_RESULT
	case HOENN_BULL_COMBAT, HoennSeek_EventScript_ShowBullCombat
	case HOENN_BULL_BLAZE, HoennSeek_EventScript_ShowBullBlaze
	case HOENN_BULL_AQUA, HoennSeek_EventScript_ShowBullAqua
	end

HoennSeek_EventScript_ShowBullCombat:
	clearflag FLAG_HOENN_HIDE_BULL_COMBAT
	end

HoennSeek_EventScript_ShowBullBlaze:
	clearflag FLAG_HOENN_HIDE_BULL_BLAZE
	end

HoennSeek_EventScript_ShowBullAqua:
	clearflag FLAG_HOENN_HIDE_BULL_AQUA
	end

@ Runs on every load and after every battle or menu: (re)starts the herd.
HoennSeek_EventScript_HighlandOnResume::
	special HoennStartStampede
	end

@ A Tauros ran into you (started by the stampede task).
HoennSeek_EventScript_StampedeHit::
	lockall
	playmoncry SPECIES_TAUROS, CRY_MODE_ENCOUNTER
	playse SE_M_DOUBLE_SLAP
	applymovement OBJ_EVENT_ID_PLAYER, HoennSeek_Movement_StampedeTumble
	waitmovement 0
	waitmoncry
	goto_if_set FLAG_HOENN_STAMPEDE_HIT_ONCE, HoennSeek_EventScript_StampedeHitAgain
	setflag FLAG_HOENN_STAMPEDE_HIT_ONCE
	msgbox HoennSeek_Text_StampedeHitFirst, MSGBOX_DEFAULT
	goto HoennSeek_EventScript_StampedeBack

HoennSeek_EventScript_StampedeHitAgain:
	msgbox HoennSeek_Text_StampedeHit, MSGBOX_DEFAULT
HoennSeek_EventScript_StampedeBack:
	closemessage
	warpsilent MAP_FUCHSIA_CITY_SAFARI_ZONE_HIGHLAND_HOENN, 12, 18
	waitstate
	releaseall
	end

HoennSeek_Movement_StampedeTumble:
	jump_in_place_down
	face_left
	face_up
	face_right
	face_down
	step_end

@ Talking to a herd Tauros (it has to be standing still: at a lane's end, or
@ grazing once the lead bull is gone for the week).
HoennSeek_EventScript_StampedeTauros::
	lock
	playmoncry SPECIES_TAUROS, CRY_MODE_NORMAL
	goto_if_set FLAG_HOENN_WEEKLY_LEAD_BULL, HoennSeek_EventScript_StampedeGrazing
	msgbox HoennSeek_Text_StampedeTauros, MSGBOX_DEFAULT
	waitmoncry
	release
	end

HoennSeek_EventScript_StampedeGrazing:
	msgbox HoennSeek_Text_StampedeGrazing, MSGBOX_DEFAULT
	waitmoncry
	release
	end

HoennSeek_EventScript_LeadBull::
	lock
	faceplayer
	specialvar VAR_RESULT, HoennStampedeBreed
	switch VAR_RESULT
	case HOENN_BULL_BLAZE, HoennSeek_EventScript_LeadBullBlaze
	case HOENN_BULL_AQUA, HoennSeek_EventScript_LeadBullAqua
	setvar VAR_0x8004, SPECIES_TAUROS_PALDEA_COMBAT
	goto HoennSeek_EventScript_LeadBullBattle

HoennSeek_EventScript_LeadBullBlaze:
	setvar VAR_0x8004, SPECIES_TAUROS_PALDEA_BLAZE
	goto HoennSeek_EventScript_LeadBullBattle

HoennSeek_EventScript_LeadBullAqua:
	setvar VAR_0x8004, SPECIES_TAUROS_PALDEA_AQUA
HoennSeek_EventScript_LeadBullBattle:
	playmoncry VAR_0x8004, CRY_MODE_ENCOUNTER
	msgbox HoennSeek_Text_LeadBull, MSGBOX_DEFAULT
	waitmoncry
	closemessage
	setvar VAR_0x8005, 35
	special HoennSetupProgressWildBattle
	special HoennTuneLeadBull
	dowildbattle
	specialvar VAR_RESULT, HoennLeadBullBattleEnded
	goto_if_eq VAR_RESULT, FALSE, HoennSeek_EventScript_LaneBRelease
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_HOENN_LEAD_BULL_COMBAT
	removeobject LOCALID_HOENN_LEAD_BULL_BLAZE
	removeobject LOCALID_HOENN_LEAD_BULL_AQUA
	fadescreenswapbuffers FADE_FROM_BLACK
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, HoennSeek_EventScript_LeadBullCaught
	msgbox HoennSeek_Text_LeadBullFled, MSGBOX_DEFAULT
	release
	end

HoennSeek_EventScript_LeadBullCaught:
	msgbox HoennSeek_Text_LeadBullCaught, MSGBOX_DEFAULT
	release
	end

@ ---- Part 30b's call --------------------------------------------------------
HoennSeek_EventScript_CallStampede::
	setflag FLAG_HOENN_CALL_STAMPEDE
	setspeaker HoennSeek_Text_NameBrendan
	pokenavcall HoennSeek_Text_CallStampede
	goto HoennSeek_EventScript_CallEnd

@ ---- Part 30b texts ---------------------------------------------------------
HoennSeek_Text_StampedeHitFirst:
	.string "Whoa! A charging TAUROS knocked\n"
	.string "you flat!\p"
	.string "You tumbled all the way back down\n"
	.string "to the canyon.\p"
	.string "The herd runs in lanes. Slip\n"
	.string "across each one while its TAUROS\l"
	.string "is charging the other way!$"

HoennSeek_Text_StampedeHit:
	.string "A TAUROS bowled you over! You\n"
	.string "tumbled back down to the canyon.$"

HoennSeek_Text_StampedeTauros:
	.string "The TAUROS snorts and paws at the\n"
	.string "ground. It's ready to charge again!$"

HoennSeek_Text_StampedeGrazing:
	.string "The TAUROS is grazing. It barely\n"
	.string "looks up at you.$"

HoennSeek_Text_LeadBull:
	.string "The herd's leader! A TAUROS unlike\n"
	.string "any from KANTO lowers its horns…$"

HoennSeek_Text_LeadBullFled:
	.string "The lead bull limped off down the\n"
	.string "far side of the highland.\p"
	.string "Without it, the herd slows to a\n"
	.string "trot, then settles down to graze.\p"
	.string "It may lead them again next\n"
	.string "MONDAY morning.$"

HoennSeek_Text_LeadBullCaught:
	.string "Without its leader, the herd slows\n"
	.string "to a trot, then starts grazing.\p"
	.string "Next MONDAY, a new bull may well\n"
	.string "be leading them.$"

HoennSeek_Text_CallStampede:
	.string "Hey, {PLAYER}! It's BRENDAN.\p"
	.string "PROF. BIRCH's aide at the FUCHSIA\n"
	.string "SAFARI ZONE says the wardens saw\l"
	.string "you catch the TAUROS herd's leader!\p"
	.string "A bull from PALDEA, way out in\n"
	.string "KANTO! May's going to be so\l"
	.string "jealous when I tell her.$"
