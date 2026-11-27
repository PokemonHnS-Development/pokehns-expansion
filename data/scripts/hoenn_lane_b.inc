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
