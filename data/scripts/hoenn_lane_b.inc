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
