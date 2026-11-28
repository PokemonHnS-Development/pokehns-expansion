@ Hoenn & Seek 2.0, lane A: parts 27b, 28, 31a, 32, 34b, 35b and 37 (Johto, the Unown Cipher, the sea, Lugia, Ho-Oh, the Regis).
@ Lane A's scenes, phone calls and texts go in this file (or a new data/scripts/hoenn_*.inc
@ of its own); the other lane has its own file, so the two never edit the same lines.
@ Rules: hoenn-docs/lanes/README.md. C code: src/hoenn_lane_a.c.

@ ---------------------------------------------------------------- event calls

@ The PokéGear event-call switch (HoennSeek_EventScript_PhoneEvent, hoenn_phone.inc)
@ falls through to lane A's cases, then to lane B's. Add one case per call:
@ 	case HOENN_CALL_X, HoennSeek_EventScript_CallX
HoennSeek_EventScript_PhoneEventLaneA::
	switch VAR_0x8004
	case HOENN_CALL_CIPHER, HoennSeek_EventScript_CallCipher @ part 27a (hoenn_cipher.inc)
	case HOENN_CALL_CIPHER_FRAGMENT, HoennSeek_EventScript_CallCipherFragment @ part 27b
	case HOENN_CALL_SNEASEL, HoennSeek_EventScript_CallSneasel @ part 31a
	case HOENN_CALL_CIPHER_SANCTUM, HoennSeek_EventScript_CallCipherSanctum @ part 28
	case HOENN_CALL_AMPHAROS, HoennSeek_EventScript_CallAmpharos @ part 32
	case HOENN_CALL_RAINBOW, HoennSeek_EventScript_CallRainbow @ part 35b (hoenn_johto_legends.inc)
	case HOENN_CALL_LUGIA, HoennSeek_EventScript_CallLugia @ part 34b
	case HOENN_CALL_WISHES, HoennSeek_EventScript_CallWishes @ part 37
	case HOENN_CALL_DEOXYS, HoennSeek_EventScript_CallDeoxys @ part 37
	case HOENN_CALL_REGIS, HoennSeek_EventScript_CallRegis @ part 37
	goto HoennSeek_EventScript_PhoneEventLaneB @ lane B's calls (hoenn_lane_b.inc)

@ ============================================================================
@ Part 27b: Unown Cipher B, the glyph sites (src/hoenn_lane_a.c has the design)
@ At night, once you've seen a place's word, a ring of Unown spelling it floats
@ in a quiet corner of that place. Talking to it sends one letter out to battle;
@ caught or knocked out, the ring is gone and a TABLET FRAGMENT with that letter
@ is left behind. The lab researcher (hoenn_cipher.inc) reads the fragments.
@ Sites (ring centre): BELL TOWER 2F (13,16), MT. MOON SQUARE (39,12), ICE PATH
@ 1F (33,28), WHIRL ISLANDS B2F (34,15), MT. MORTAR 1F south (30,15), UNION
@ CAVE B1F (22,27), SEAFOAM ISLANDS 1F (15,13).
@ ============================================================================

@ Called at the top of each site map's ON_TRANSITION (also Bell Tower's other
@ floors, which share its script: HoennGlyphRingShows is FALSE there).
HoennSeek_EventScript_GlyphRingArm::
	setflag FLAG_HOENN_CIPHER_HIDE_RING
	specialvar VAR_RESULT, HoennGlyphRingShows
	goto_if_eq VAR_RESULT, FALSE, HoennSeek_EventScript_GlyphRingArmDone
	clearflag FLAG_HOENN_CIPHER_HIDE_RING
	@ Each letter is its own Unown form, and each form loads its whole sprite
	@ sheet (96 tiles). A ring of five, the map's other Pokémon and a follower
	@ ran out of sprite memory, so letters went missing (review item 36). Your
	@ Pokémon stays in its ball while a ring is out (a temp flag: only for
	@ this visit).
	setflag FLAG_TEMP_HIDE_FOLLOWER
HoennSeek_EventScript_GlyphRingArmDone:
	return

@ ON_TRANSITION for the site maps that had no map scripts (Whirl Islands B2F,
@ Union Cave B1F).
HoennSeek_EventScript_GlyphRingOnTransition::
	call HoennSeek_EventScript_GlyphRingArm
	end

@ Every Unown of a ring runs this.
HoennSeek_EventScript_GlyphRing::
	lock
	special HoennGlyphRingPrepare
	playmoncry SPECIES_UNOWN, CRY_MODE_ENCOUNTER
	msgbox HoennSeek_Text_GlyphRingSee, MSGBOX_DEFAULT
	waitmoncry
	closemessage
	applymovement VAR_0x8005, HoennSeek_Movement_GlyphLetterOut
	waitmovement 0
	msgbox HoennSeek_Text_GlyphLetterOut, MSGBOX_DEFAULT
	closemessage
	special HoennGlyphSetupBattle
	dowildbattle
	special HoennGlyphRingPrepare @ the battle used the string buffers
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, HoennSeek_EventScript_GlyphRingStays
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, HoennSeek_EventScript_GlyphRingStays
	fadescreen FADE_TO_BLACK
	special HoennGlyphTakeFragment
	fadescreen FADE_FROM_BLACK
	msgbox HoennSeek_Text_GlyphRingGone, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_ITEM
	message HoennSeek_Text_GlyphFragment
	waitmessage
	waitfanfare
	waitbuttonpress
	specialvar VAR_RESULT, HoennCipherFragmentCount
	goto_if_ge VAR_RESULT, 7, HoennSeek_EventScript_GlyphAllFragments
	msgbox HoennSeek_Text_GlyphFragmentCount, MSGBOX_DEFAULT
	release
	end

HoennSeek_EventScript_GlyphAllFragments:
	msgbox HoennSeek_Text_GlyphAllFragments, MSGBOX_DEFAULT
	release
	end

HoennSeek_EventScript_GlyphRingStays:
	msgbox HoennSeek_Text_GlyphRingStays, MSGBOX_DEFAULT
	release
	end

HoennSeek_Movement_GlyphLetterOut:
	jump_in_place_down
	jump_in_place_down
	step_end

@ May: the Ruins lab phoned Birch once you showed them a fragment.
HoennSeek_EventScript_CallCipherFragment::
	setflag FLAG_HOENN_CALL_CIPHER_FRAGMENT
	setspeaker HoennSeek_Text_NameMay
	pokenavcall HoennSeek_Text_CallCipherFragment
	goto HoennSeek_EventScript_CallEnd

HoennSeek_Text_GlyphRingSee:
	.string "UNOWN float in a ring, turning\n"
	.string "slowly in the dark.\p"
	.string "Read clockwise from the top, their\n"
	.string "letters spell {STR_VAR_1}.$"

HoennSeek_Text_GlyphLetterOut:
	.string "The UNOWN {STR_VAR_2} breaks away\n"
	.string "from the ring!$"

HoennSeek_Text_GlyphRingStays:
	.string "The ring of UNOWN keeps turning,\n"
	.string "as if nothing happened.$"

HoennSeek_Text_GlyphRingGone:
	.string "The ring of UNOWN is gone.\p"
	.string "Something lies on the ground\n"
	.string "where it was floating…$"

HoennSeek_Text_GlyphFragment:
	.string "{PLAYER} found a TABLET FRAGMENT!\n"
	.string "The letter {STR_VAR_2} is carved on it.$"

HoennSeek_Text_GlyphFragmentCount:
	.string "Fragments so far: {STR_VAR_3} of 7.\n"
	.string "Their letters: {STR_VAR_1}.$"

HoennSeek_Text_GlyphAllFragments:
	.string "That's all seven fragments!\n"
	.string "Their letters: {STR_VAR_1}.\p"
	.string "The lab at the RUINS OF ALPH\n"
	.string "should see these.$"

HoennSeek_Text_CallCipherFragment:
	.string "Hi, {PLAYER}! It's MAY.\p"
	.string "The PROF just got off the phone\n"
	.string "with the RUINS OF ALPH lab.\p"
	.string "They said you brought them a piece\n"
	.string "of a stone tablet with an UNOWN\l"
	.string "letter carved on it!\p"
	.string "UNOWN dancing in a ring at night…\n"
	.string "I'd give anything to see that.\p"
	.string "Seven words, seven places, seven\n"
	.string "pieces, right? Go find the rest!$"


@ ============================================================================
@ Part 31a: the Sneasel thief (Ice Path B2F, nights)
@ Once all four B1F boulders have dropped onto B2F (they shape the ice), at
@ night an item ball sits out on the ice. Reach it and a SNEASEL darts in and
@ snatches it, and another ball shows farther across the ice; three times.
@ After the third it runs into the north-west nook, where talking to it starts
@ the battle (hidden ability Pickpocket, Razor Claw, catchable). The first
@ battle, won or caught, gives its stash; after that it waits in the nook on
@ later nights until caught (knocked out: back the next night).
@ Balls and how to reach them (B2F's sliding ice, from the ladder at (26,6);
@ when a ball vanishes you slide on the way you faced, so each leg starts
@ where that slide ends; every state on the way can still reach a ladder):
@   1 (15,11), from (15,12) facing up:    LLLLDLURU, then slide to (15,5)
@   2 (22,13), from (21,13) facing right: LDDRDR, then slide to (26,13)
@   3 (16,18), from (16,17) facing down:  ULLLLDLURDDDRD, then slide to (16,22)
@   nook: SNEASEL at (9,6), from (8,6) facing right: LUULD
@ Leaving the floor mid-chase starts it over (the OnTransition decides).
@ ============================================================================

@ One `call` at the top of IcePath_B2F's OnTransition.
HoennSeek_EventScript_SneaselArm::
	setflag FLAG_HOENN_HIDE_SNEASEL_BALL_1
	setflag FLAG_HOENN_HIDE_SNEASEL_BALL_2
	setflag FLAG_HOENN_HIDE_SNEASEL_BALL_3
	setflag FLAG_HOENN_HIDE_ICE_SNEASEL
	goto_if_set FLAG_HOENN_CAUGHT_ICE_SNEASEL, HoennSeek_EventScript_SneaselArmDone
	goto_if_set FLAG_HOENN_DAILY_ICE_SNEASEL, HoennSeek_EventScript_SneaselArmDone
	goto_if_set FLAG_HIDE_ICEPATH_B2F_BOULDER1, HoennSeek_EventScript_SneaselArmDone
	goto_if_set FLAG_HIDE_ICEPATH_B2F_BOULDER2, HoennSeek_EventScript_SneaselArmDone
	goto_if_set FLAG_HIDE_ICEPATH_B2F_BOULDER3, HoennSeek_EventScript_SneaselArmDone
	goto_if_set FLAG_HIDE_ICEPATH_B2F_BOULDER4, HoennSeek_EventScript_SneaselArmDone
	gettimeofday
	goto_if_ne VAR_0x8000, HOENN_TIME_NIGHT, HoennSeek_EventScript_SneaselArmDone
	goto_if_set FLAG_HOENN_SNEASEL_STASH, HoennSeek_EventScript_SneaselArmNook
	clearflag FLAG_HOENN_HIDE_SNEASEL_BALL_1
	setobjectxyperm LOCALID_HOENN_ICE_SNEASEL, 15, 10
HoennSeek_EventScript_SneaselArmDone:
	return

HoennSeek_EventScript_SneaselArmNook:
	setobjectxyperm LOCALID_HOENN_ICE_SNEASEL, 9, 6
	clearflag FLAG_HOENN_HIDE_ICE_SNEASEL
	return

@ The balls. Each one: the SNEASEL pops up behind it, grabs it and dashes
@ off; the next ball shows.
HoennSeek_EventScript_SneaselBall1::
	lock
	setobjectxyperm LOCALID_HOENN_ICE_SNEASEL, 15, 10
	setvar VAR_0x8004, LOCALID_HOENN_SNEASEL_BALL_1
	call HoennSeek_EventScript_SneaselSnatch
	applymovement LOCALID_HOENN_ICE_SNEASEL, HoennSeek_Movement_SneaselDashUp
	waitmovement 0
	call HoennSeek_EventScript_SneaselGone
	clearflag FLAG_HOENN_HIDE_SNEASEL_BALL_2
	addobject LOCALID_HOENN_SNEASEL_BALL_2
	setobjectxyperm LOCALID_HOENN_ICE_SNEASEL, 23, 13
	msgbox HoennSeek_Text_SneaselAnother, MSGBOX_DEFAULT
	release
	end

HoennSeek_EventScript_SneaselBall2::
	lock
	setvar VAR_0x8004, LOCALID_HOENN_SNEASEL_BALL_2
	call HoennSeek_EventScript_SneaselSnatch
	applymovement LOCALID_HOENN_ICE_SNEASEL, HoennSeek_Movement_SneaselDashRight
	waitmovement 0
	call HoennSeek_EventScript_SneaselGone
	clearflag FLAG_HOENN_HIDE_SNEASEL_BALL_3
	addobject LOCALID_HOENN_SNEASEL_BALL_3
	setobjectxyperm LOCALID_HOENN_ICE_SNEASEL, 16, 19
	msgbox HoennSeek_Text_SneaselAgain, MSGBOX_DEFAULT
	release
	end

HoennSeek_EventScript_SneaselBall3::
	lock
	setvar VAR_0x8004, LOCALID_HOENN_SNEASEL_BALL_3
	call HoennSeek_EventScript_SneaselSnatch
	applymovement LOCALID_HOENN_ICE_SNEASEL, HoennSeek_Movement_SneaselDashDown
	waitmovement 0
	call HoennSeek_EventScript_SneaselGone
	setobjectxyperm LOCALID_HOENN_ICE_SNEASEL, 9, 6
	clearflag FLAG_HOENN_HIDE_ICE_SNEASEL
	addobject LOCALID_HOENN_ICE_SNEASEL
	msgbox HoennSeek_Text_SneaselToNook, MSGBOX_DEFAULT
	release
	end

@ VAR_0x8004: the ball's local ID. The SNEASEL's spot was set by the caller.
HoennSeek_EventScript_SneaselSnatch:
	clearflag FLAG_HOENN_HIDE_ICE_SNEASEL
	addobject LOCALID_HOENN_ICE_SNEASEL
	playmoncry SPECIES_SNEASEL, CRY_MODE_ENCOUNTER
	applymovement LOCALID_HOENN_ICE_SNEASEL, HoennSeek_Movement_SneaselHop
	waitmovement 0
	removeobject VAR_0x8004 @ (also sets the ball's hide flag)
	playse SE_BALL
	waitmoncry
	msgbox HoennSeek_Text_SneaselSnatch, MSGBOX_DEFAULT
	closemessage
	return

HoennSeek_EventScript_SneaselGone:
	removeobject LOCALID_HOENN_ICE_SNEASEL
	setflag FLAG_HOENN_HIDE_ICE_SNEASEL
	return

@ The cornered SNEASEL in the nook.
HoennSeek_EventScript_IceSneasel::
	lock
	faceplayer
	playmoncry SPECIES_SNEASEL, CRY_MODE_ENCOUNTER
	msgbox HoennSeek_Text_SneaselCornered, MSGBOX_DEFAULT
	waitmoncry
	closemessage
	setvar VAR_0x8004, SPECIES_SNEASEL
	special HoennSetupScaledWildBattle
	setvar VAR_0x8005, MOVE_NONE
	setvar VAR_0x8006, FALSE
	setvar VAR_0x8007, ITEM_RAZOR_CLAW
	setvar VAR_0x8008, 0
	setvar VAR_0x8009, HOENN_TUNE_HIDDEN_ABILITY
	special HoennTuneWildMonSlot
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, HoennSeek_EventScript_SneaselStays
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, HoennSeek_EventScript_SneaselStays
	call HoennSeek_EventScript_SneaselGone
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, HoennSeek_EventScript_SneaselCaught
	setflag FLAG_HOENN_DAILY_ICE_SNEASEL
	msgbox HoennSeek_Text_SneaselFled, MSGBOX_DEFAULT
	goto HoennSeek_EventScript_SneaselStash

HoennSeek_EventScript_SneaselCaught:
	setflag FLAG_HOENN_CAUGHT_ICE_SNEASEL
HoennSeek_EventScript_SneaselStash:
	goto_if_set FLAG_HOENN_SNEASEL_STASH, HoennSeek_EventScript_SneaselEnd
	setflag FLAG_HOENN_SNEASEL_STASH
	msgbox HoennSeek_Text_SneaselStash, MSGBOX_DEFAULT
	giveitem ITEM_PP_UP, 2
	giveitem ITEM_LUCKY_EGG
	giveitem ITEM_LANSAT_BERRY
	giveitem ITEM_STARF_BERRY
HoennSeek_EventScript_SneaselEnd:
	release
	end

HoennSeek_EventScript_SneaselStays:
	release
	end

HoennSeek_Movement_SneaselHop:
	jump_in_place_down
	step_end

HoennSeek_Movement_SneaselDashUp:
	walk_faster_up
	walk_faster_up
	step_end

HoennSeek_Movement_SneaselDashRight:
	walk_faster_right
	walk_faster_right
	step_end

HoennSeek_Movement_SneaselDashDown:
	walk_faster_down
	walk_faster_down
	step_end

@ Brendan: May's dad (Norman) reads every gym's report to the League, and
@ Clair's says the Ice Path thief was caught. (Brendan's own dad is Birch.)
HoennSeek_EventScript_CallSneasel::
	setflag FLAG_HOENN_CALL_SNEASEL
	setspeaker HoennSeek_Text_NameBrendan
	pokenavcall HoennSeek_Text_CallSneasel
	goto HoennSeek_EventScript_CallEnd

HoennSeek_Text_SneaselSnatch:
	.string "A SNEASEL darts out of the dark\n"
	.string "and snatches the item!$"

HoennSeek_Text_SneaselAnother:
	.string "It skated off across the ice!\p"
	.string "Something else glints out on the\n"
	.string "ice, farther away…$"

HoennSeek_Text_SneaselAgain:
	.string "Gone again!\p"
	.string "There's one more glint out on the\n"
	.string "ice. Is it leading you somewhere?$"

HoennSeek_Text_SneaselToNook:
	.string "The SNEASEL skidded off toward the\n"
	.string "cave's far corner…$"

HoennSeek_Text_SneaselCornered:
	.string "The SNEASEL is cornered! It hisses\n"
	.string "and clutches its stolen hoard!$"

HoennSeek_Text_SneaselFled:
	.string "The SNEASEL scrambled off\n"
	.string "across the ice!$"

HoennSeek_Text_SneaselStash:
	.string "It left its hoard behind! Tucked\n"
	.string "into the corner is the SNEASEL's\l"
	.string "stash of stolen things!$"

HoennSeek_Text_CallSneasel:
	.string "{PLAYER}! It's BRENDAN.\p"
	.string "MAY's dad gets every gym's\n"
	.string "report from the LEAGUE, and\l"
	.string "guess what was in CLAIR's,\l"
	.string "from BLACKTHORN?\p"
	.string "The thief of the ICE PATH! Some\n"
	.string "SNEASEL was swiping items right\l"
	.string "off the ice for years.\p"
	.string "And a trainer from out of town\n"
	.string "finally cornered it. That was\l"
	.string "you, wasn't it? Ha! Nice one!$"
@ ============================================================================
@ Part 28: Unown Cipher C, the sanctum (src/hoenn_lane_a.c has the design)
@ The tablet's mark is the boulder in the middle of the RUINS OF ALPH (Outside,
@ 23,27). At night the UNOWN open it; a ladder leads down to the sanctum
@ (RuinsOfAlph_Sanctum_hoenn), whose mural calls any of the 28 letters once a
@ day and whose middle statue holds the final inscription (part 37's start).
@ ============================================================================

@ Ruins of Alph Outside, ON_LOAD: the opened boulder.
HoennSeek_EventScript_AlphOutsideOnLoad::
	goto_if_unset FLAG_HOENN_CIPHER_SANCTUM_OPEN, HoennSeek_EventScript_AlphOutsideOnLoadEnd
	setmetatile 23, 27, 0xA9, FALSE
HoennSeek_EventScript_AlphOutsideOnLoadEnd:
	end

@ Ruins of Alph Outside, ON_TRANSITION (a call): the opening scene's UNOWN
@ only appear in the scene.
HoennSeek_EventScript_AlphSealArm::
	setflag FLAG_HOENN_CIPHER_HIDE_SEAL
	@ Like the glyph rings (review item 36): the seal's three Unown forms each
	@ load a whole sprite sheet, so your Pokémon stays in its ball on the nights
	@ the boulder can still open.
	goto_if_unset FLAG_HOENN_CIPHER_TABLET, HoennSeek_EventScript_AlphSealArmDone
	goto_if_set FLAG_HOENN_CIPHER_SANCTUM_OPEN, HoennSeek_EventScript_AlphSealArmDone
	gettimeofday
	goto_if_ne VAR_0x8000, HOENN_TIME_NIGHT, HoennSeek_EventScript_AlphSealArmDone
	setflag FLAG_TEMP_HIDE_FOLLOWER
HoennSeek_EventScript_AlphSealArmDone:
	return

@ The sanctum's five floating Unown are five forms: no follower in there either.
HoennSeek_EventScript_SanctumOnTransition::
	setflag FLAG_TEMP_HIDE_FOLLOWER
	return

@ The boulder's face (a sign facing north at 23,27).
HoennSeek_EventScript_AlphBoulder::
	goto_if_set FLAG_HOENN_CIPHER_SANCTUM_OPEN, HoennSeek_EventScript_AlphBoulderOpen
	goto_if_unset FLAG_HOENN_CIPHER_TABLET, HoennSeek_EventScript_AlphBoulderEnd
	lockall
	gettimeofday
	goto_if_ne VAR_0x8000, HOENN_TIME_NIGHT, HoennSeek_EventScript_AlphBoulderDay
	msgbox HoennSeek_Text_AlphBoulderNight, MSGBOX_DEFAULT
	closemessage
	clearflag FLAG_HOENN_CIPHER_HIDE_SEAL
	addobject LOCALID_HOENN_ALPH_SEAL_1
	playmoncry SPECIES_UNOWN, CRY_MODE_ENCOUNTER
	delay 30
	addobject LOCALID_HOENN_ALPH_SEAL_2
	delay 30
	addobject LOCALID_HOENN_ALPH_SEAL_3
	waitmoncry
	msgbox HoennSeek_Text_AlphBoulderGather, MSGBOX_DEFAULT
	closemessage
	playse SE_M_EARTHQUAKE
	setvar VAR_0x8004, 1  @ vertical pan
	setvar VAR_0x8005, 1  @ horizontal pan
	setvar VAR_0x8006, 8  @ number of shakes
	setvar VAR_0x8007, 5  @ shake delay
	special ShakeCamera
	waitstate
	fadescreen FADE_TO_WHITE
	removeobject LOCALID_HOENN_ALPH_SEAL_1
	removeobject LOCALID_HOENN_ALPH_SEAL_2
	removeobject LOCALID_HOENN_ALPH_SEAL_3
	setflag FLAG_HOENN_CIPHER_HIDE_SEAL
	setflag FLAG_HOENN_CIPHER_SANCTUM_OPEN
	setmetatile 23, 27, 0xA9, FALSE
	special DrawWholeMapView
	fadescreen FADE_FROM_WHITE
	msgbox HoennSeek_Text_AlphBoulderOpens, MSGBOX_DEFAULT
	releaseall
	end

HoennSeek_EventScript_AlphBoulderDay:
	msgbox HoennSeek_Text_AlphBoulderDay, MSGBOX_DEFAULT
	releaseall
	end

HoennSeek_EventScript_AlphBoulderOpen:
	msgbox HoennSeek_Text_AlphBoulderIsOpen, MSGBOX_SIGN
HoennSeek_EventScript_AlphBoulderEnd:
	end

@ ---- The sanctum ---------------------------------------------------------------
@ The floating UNOWN.
HoennSeek_EventScript_SanctumUnown::
	lock
	playmoncry SPECIES_UNOWN, CRY_MODE_NORMAL
	msgbox HoennSeek_Text_SanctumUnown, MSGBOX_DEFAULT
	waitmoncry
	release
	end

@ The mural (the north wall's frieze, signs facing north on row 1).
HoennSeek_EventScript_SanctumMural::
	lockall
	goto_if_set FLAG_HOENN_DAILY_SANCTUM_MURAL, HoennSeek_EventScript_SanctumMuralQuiet
	msgbox HoennSeek_Text_SanctumMural, MSGBOX_DEFAULT
	message HoennSeek_Text_SanctumMuralWhich
	waitmessage
	dynmultichoice 19, 0, FALSE, 6, 0, DYN_MULTICHOICE_CB_NONE, HoennSeek_Text_SanctumLetter0, HoennSeek_Text_SanctumLetter1, HoennSeek_Text_SanctumLetter2, HoennSeek_Text_SanctumLetter3, HoennSeek_Text_SanctumLetter4, HoennSeek_Text_SanctumLetter5, HoennSeek_Text_SanctumLetter6, HoennSeek_Text_SanctumLetter7, HoennSeek_Text_SanctumLetter8, HoennSeek_Text_SanctumLetter9, HoennSeek_Text_SanctumLetter10, HoennSeek_Text_SanctumLetter11, HoennSeek_Text_SanctumLetter12, HoennSeek_Text_SanctumLetter13, HoennSeek_Text_SanctumLetter14, HoennSeek_Text_SanctumLetter15, HoennSeek_Text_SanctumLetter16, HoennSeek_Text_SanctumLetter17, HoennSeek_Text_SanctumLetter18, HoennSeek_Text_SanctumLetter19, HoennSeek_Text_SanctumLetter20, HoennSeek_Text_SanctumLetter21, HoennSeek_Text_SanctumLetter22, HoennSeek_Text_SanctumLetter23, HoennSeek_Text_SanctumLetter24, HoennSeek_Text_SanctumLetter25, HoennSeek_Text_SanctumLetter26, HoennSeek_Text_SanctumLetter27, HoennSeek_Text_SanctumCancel
	closemessage
	goto_if_ge VAR_RESULT, HOENN_SANCTUM_LETTERS, HoennSeek_EventScript_SanctumMuralCancel
	special HoennSanctumLetter
	msgbox HoennSeek_Text_SanctumMuralCalls, MSGBOX_DEFAULT
	closemessage
	playmoncry SPECIES_UNOWN, CRY_MODE_ENCOUNTER
	waitmoncry
	special HoennGlyphSetupBattle
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, HoennSeek_EventScript_SanctumMuralRan
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, HoennSeek_EventScript_SanctumMuralRan
	setflag FLAG_HOENN_DAILY_SANCTUM_MURAL
	msgbox HoennSeek_Text_SanctumMuralAfter, MSGBOX_DEFAULT
	releaseall
	end

HoennSeek_EventScript_SanctumMuralRan:
	msgbox HoennSeek_Text_SanctumMuralRan, MSGBOX_DEFAULT
	releaseall
	end

HoennSeek_EventScript_SanctumMuralCancel:
	msgbox HoennSeek_Text_SanctumMuralCancel, MSGBOX_DEFAULT
	releaseall
	end

HoennSeek_EventScript_SanctumMuralQuiet:
	msgbox HoennSeek_Text_SanctumMuralQuiet, MSGBOX_DEFAULT
	releaseall
	end

@ The final inscription (the middle statue).
HoennSeek_EventScript_SanctumInscription::
	lockall
	msgbox HoennSeek_Text_SanctumInscriptionSee, MSGBOX_DEFAULT
	braillemessage HoennSeek_Braille_Sinjoh
	waitbuttonpress
	closebraillemessage
	msgbox HoennSeek_Text_SanctumInscriptionRead, MSGBOX_DEFAULT
	goto_if_set FLAG_HOENN_CIPHER_INSCRIPTION, HoennSeek_EventScript_SanctumInscriptionEnd
	setflag FLAG_HOENN_CIPHER_INSCRIPTION
	msgbox HoennSeek_Text_SanctumInscriptionLab, MSGBOX_DEFAULT
HoennSeek_EventScript_SanctumInscriptionEnd:
	releaseall
	end

@ Brendan: the Ruins lab phoned Birch once it read the inscription with you.
HoennSeek_EventScript_CallCipherSanctum::
	setflag FLAG_HOENN_CALL_CIPHER_SANCTUM
	setspeaker HoennSeek_Text_NameBrendan
	pokenavcall HoennSeek_Text_CallCipherSanctum
	goto HoennSeek_EventScript_CallEnd

HoennSeek_Braille_Sinjoh:
	brailleformat 0, 0, 0, 0, 0, 0
	.braille "SINJOH\n"
	.braille "THREE SLEEP$"

HoennSeek_Text_AlphBoulderDay:
	.string "This boulder sits right where the\n"
	.string "tablet's mark is.\p"
	.string "Faint UNOWN letters are worn into\n"
	.string "its face, too faint to read…\p"
	.string "AT NIGHT WE SPEAK, the braille in\n"
	.string "the RUINS said.$"

HoennSeek_Text_AlphBoulderNight:
	.string "The worn UNOWN letters on the\n"
	.string "boulder are glowing!\p"
	.string "A-N-C-I-E-N-T. The same word as\n"
	.string "the tablet!$"

HoennSeek_Text_AlphBoulderGather:
	.string "UNOWN are gathering around\n"
	.string "the stone!$"

HoennSeek_Text_AlphBoulderOpens:
	.string "The UNOWN are gone.\p"
	.string "The boulder has split open. A\n"
	.string "ladder leads down into the dark…$"

HoennSeek_Text_AlphBoulderIsOpen:
	.string "The opening in the boulder leads\n"
	.string "down into the RUINS.$"

HoennSeek_Text_SanctumUnown:
	.string "The UNOWN drifts by without a\n"
	.string "sound. It doesn't seem to mind you.$"

HoennSeek_Text_SanctumMural:
	.string "The wall is carved with UNOWN of\n"
	.string "every shape, even ! and ?.\p"
	.string "As you look along it, the letters\n"
	.string "seem to stir…$"

HoennSeek_Text_SanctumMuralWhich:
	.string "Which letter will you call?$"

HoennSeek_Text_SanctumMuralCalls:
	.string "The letter {STR_VAR_1} glows on the wall…\n"
	.string "and an UNOWN {STR_VAR_1} slips out of it!$"

HoennSeek_Text_SanctumMuralAfter:
	.string "The mural is still again. The UNOWN\n"
	.string "won't answer again until tomorrow.$"

HoennSeek_Text_SanctumMuralRan:
	.string "The UNOWN drifted back into the\n"
	.string "wall. The letters still stir.$"

HoennSeek_Text_SanctumMuralCancel:
	.string "The letters settle back into\n"
	.string "the stone.$"

HoennSeek_Text_SanctumMuralQuiet:
	.string "The mural is still. The UNOWN won't\n"
	.string "answer again until tomorrow.$"

HoennSeek_Text_SanctumInscriptionSee:
	.string "UNOWN letters circle the statue,\n"
	.string "with braille carved under them.$"

HoennSeek_Text_SanctumInscriptionRead:
	.string "With the UNOWN letters and the\n"
	.string "braille, you can read all of it:\p"
	.string "WE WERE BORN AT SINJOH, PAST\n"
	.string "THE SNOWS.\p"
	.string "THREE SLEEP THERE BEHIND SEALED\n"
	.string "DOORS. THE OLDEST OF THE DEEP AND\l"
	.string "THE GREATEST OF THE SEA WAKE THEM.$"

HoennSeek_Text_SanctumInscriptionLab:
	.string "The lab at the RUINS will want to\n"
	.string "hear about this!$"

HoennSeek_Text_SanctumCancel:
	.string "CANCEL$"

HoennSeek_Text_SanctumLetter0:
	.string "UNOWN A$"

HoennSeek_Text_SanctumLetter1:
	.string "UNOWN B$"

HoennSeek_Text_SanctumLetter2:
	.string "UNOWN C$"

HoennSeek_Text_SanctumLetter3:
	.string "UNOWN D$"

HoennSeek_Text_SanctumLetter4:
	.string "UNOWN E$"

HoennSeek_Text_SanctumLetter5:
	.string "UNOWN F$"

HoennSeek_Text_SanctumLetter6:
	.string "UNOWN G$"

HoennSeek_Text_SanctumLetter7:
	.string "UNOWN H$"

HoennSeek_Text_SanctumLetter8:
	.string "UNOWN I$"

HoennSeek_Text_SanctumLetter9:
	.string "UNOWN J$"

HoennSeek_Text_SanctumLetter10:
	.string "UNOWN K$"

HoennSeek_Text_SanctumLetter11:
	.string "UNOWN L$"

HoennSeek_Text_SanctumLetter12:
	.string "UNOWN M$"

HoennSeek_Text_SanctumLetter13:
	.string "UNOWN N$"

HoennSeek_Text_SanctumLetter14:
	.string "UNOWN O$"

HoennSeek_Text_SanctumLetter15:
	.string "UNOWN P$"

HoennSeek_Text_SanctumLetter16:
	.string "UNOWN Q$"

HoennSeek_Text_SanctumLetter17:
	.string "UNOWN R$"

HoennSeek_Text_SanctumLetter18:
	.string "UNOWN S$"

HoennSeek_Text_SanctumLetter19:
	.string "UNOWN T$"

HoennSeek_Text_SanctumLetter20:
	.string "UNOWN U$"

HoennSeek_Text_SanctumLetter21:
	.string "UNOWN V$"

HoennSeek_Text_SanctumLetter22:
	.string "UNOWN W$"

HoennSeek_Text_SanctumLetter23:
	.string "UNOWN X$"

HoennSeek_Text_SanctumLetter24:
	.string "UNOWN Y$"

HoennSeek_Text_SanctumLetter25:
	.string "UNOWN Z$"

HoennSeek_Text_SanctumLetter26:
	.string "UNOWN !$"

HoennSeek_Text_SanctumLetter27:
	.string "UNOWN ?$"

HoennSeek_Text_CallCipherSanctum:
	.string "Hey, {PLAYER}! BRENDAN here.\p"
	.string "The RUINS OF ALPH lab just phoned\n"
	.string "my dad again. You found a room\l"
	.string "under a boulder?\p"
	.string "And an UNOWN carving about three\n"
	.string "of something sleeping at SINJOH?\p"
	.string "Dad says the oldest of the deep\n"
	.string "could be RELICANTH. It hasn't\l"
	.string "changed in a hundred million years.\p"
	.string "And the greatest of the sea… that\n"
	.string "has to be WAILORD!\p"
	.string "Sounds like a Hoenn job to me.\n"
	.string "Good luck!$"

@ ============================================================================
@ Part 32: Olivine nights (Route 41, Route41_Lagoon_hoenn, Route 40, Olivine Lighthouse)
@ The Lanturn lights: at night a LANTURN's light waits off Route 41's north
@ shore (41,17) and drifts on whenever you swim close (src/hoenn_lights.c,
@ path LANTURN_LIGHTS in data/hoenn/light_paths.json: on the water only,
@ around the whirlpools and swimmers). It leads south-east to the foot of the
@ east ridge, where it swims into a sea cave (57,53) that nobody had noticed.
@ The cave stays open from then on (ON_LOAD draws it); swimming under it
@ (57,54) takes you into the hidden lagoon, where a LANTURN and its CHINCHOU
@ school light an old stone on the beach: Lugia's shrine (part 34b adds what
@ the stone does). The lagoon's channel (16-17, 23) leads back out.
@ The stranded AMPHAROS: at night it stands on a sea rock off Route 40 (31,32),
@ blinking its tail. AMPHY, at the top of the lighthouse, watches that light
@ after dark. (Route 41 already has 64 object templates, the most a map can
@ hold, so it lives on Route 40, the sea right below the lighthouse. Its
@ template elevation is 4 so it's drawn above the rock's top layer; standing
@ on an elevation-0 rock tile, it can still be talked to from the water.)
@ A rescue, not a battle or a catch (Bryan, 32 review). It's too frightened
@ to come near you at first: it takes a BERRY from you once a night, and after
@ the third it trusts you and climbs on behind you. It rides as your follower
@ Pokémon, so the moment you land on any shore it's there; your first step
@ ashore it hops off and runs, and a short scene at the lighthouse top shows
@ it reaching JASMINE and AMPHY, then you're back where you landed. It lives
@ there from then on (May calls). VAR_HOENN_AMPHAROS_STATE has the stages.
@ ============================================================================

@ One `call` at the top of Route 41's OnTransition.
HoennSeek_EventScript_Route41Night::
	setflag FLAG_HOENN_HIDE_LANTURN_LIGHT
	call_if_set FLAG_HOENN_LAGOON_FOUND, HoennSeek_EventScript_ArmLagoonCave
	call HoennSeek_EventScript_ArmLugiaCameo @ part 34b
	goto_if_set FLAG_HOENN_LAGOON_FOUND, HoennSeek_EventScript_Route41NightDone
	gettimeofday
	goto_if_ne VAR_0x8000, HOENN_TIME_NIGHT, HoennSeek_EventScript_Route41NightDone
	clearflag FLAG_HOENN_HIDE_LANTURN_LIGHT
HoennSeek_EventScript_Route41NightDone:
	return

@ One `call` at the top of Route 40's OnTransition. Hidden while it rides
@ with you, or once it's home.
HoennSeek_EventScript_Route40Night::
	setflag FLAG_HOENN_HIDE_STRANDED_AMPHAROS
	goto_if_ge VAR_HOENN_AMPHAROS_STATE, HOENN_AMPHAROS_RIDING, HoennSeek_EventScript_Route41NightDone
	gettimeofday
	goto_if_ne VAR_0x8000, HOENN_TIME_NIGHT, HoennSeek_EventScript_Route41NightDone
	clearflag FLAG_HOENN_HIDE_STRANDED_AMPHAROS
	return

HoennSeek_EventScript_ArmLagoonCave:
	setvar VAR_TEMP_3, 1
	return

@ Route 41's ON_LOAD.
HoennSeek_EventScript_Route41OnLoad::
	call_if_set FLAG_HOENN_LAGOON_FOUND, HoennSeek_EventScript_DrawLagoonCave
	end

@ The east ridge's bottom edge at (57,53) becomes a cave mouth (the Whirl
@ Islands' own, which fits the ridge's bottom row; still a wall).
HoennSeek_EventScript_DrawLagoonCave:
	setmetatile 57, 53, 0x368, TRUE
	return

@ Talking to the light while it waits.
HoennSeek_EventScript_LanturnLight::
	lock
	playmoncry SPECIES_LANTURN, CRY_MODE_NORMAL
	msgbox HoennSeek_Text_LanturnLightBlinks, MSGBOX_DEFAULT
	waitmoncry
	release
	end

@ Started by src/hoenn_lights.c at the last stop (57,55), below the ridge.
HoennSeek_EventScript_LanturnLightsEnd::
	lockall
	playmoncry SPECIES_LANTURN, CRY_MODE_NORMAL
	applymovement LOCALID_HOENN_LANTURN_LIGHT, HoennSeek_Movement_LanturnIntoCave
	waitmovement 0
	waitmoncry
	removeobject LOCALID_HOENN_LANTURN_LIGHT
	setflag FLAG_HOENN_HIDE_LANTURN_LIGHT
	setflag FLAG_HOENN_LAGOON_FOUND
	call HoennSeek_EventScript_DrawLagoonCave
	special DrawWholeMapView
	playse SE_M_BUBBLE
	waitse
	msgbox HoennSeek_Text_LanturnIntoCave, MSGBOX_DEFAULT
	call HoennSeek_EventScript_ArmLagoonCave
	releaseall
	end

HoennSeek_Movement_LanturnIntoCave:
	walk_slow_up
	walk_slow_up
	step_end

@ Coord trigger under the cave (57,54), once it's open (VAR_TEMP_3 = 1).
HoennSeek_EventScript_LagoonCave::
	lockall
	warp MAP_ROUTE41_LAGOON_HOENN, 16, 22
	waitstate
	releaseall
	end

@ Coord triggers on the lagoon channel's last row (16-17, 23).
HoennSeek_EventScript_LagoonExit::
	lockall
	warp MAP_ROUTE41_HNS, 57, 55
	waitstate
	releaseall
	end

HoennSeek_EventScript_LagoonLanturn::
	lock
	faceplayer
	playmoncry SPECIES_LANTURN, CRY_MODE_NORMAL
	msgbox HoennSeek_Text_LagoonLanturn, MSGBOX_DEFAULT
	waitmoncry
	release
	end

HoennSeek_EventScript_LagoonChinchou::
	lock
	faceplayer
	playmoncry SPECIES_CHINCHOU, CRY_MODE_NORMAL
	msgbox HoennSeek_Text_LagoonChinchou, MSGBOX_DEFAULT
	waitmoncry
	release
	end

@ The old stone (bg events on 11-12, 6): Lugia's shrine, part 34b's section.

@ The stranded AMPHAROS on its rock off Route 40 (31,32), talked to from the
@ open water north of it (31,31), eight tiles off the beach. (Until the 32
@ review it stood on a small rock at (32,33), only reachable from the sealed
@ channel south of the rocks: 180 tiles of surfing from any shore. The rock is
@ now two of Route 40's brown sea boulders side by side, 29-32, 32-33.)
HoennSeek_EventScript_StrandedAmpharos::
	lock
	faceplayer
	goto_if_ge VAR_HOENN_AMPHAROS_STATE, HOENN_AMPHAROS_TRUSTS, HoennSeek_EventScript_StrandedAmpharosTrusts
	playmoncry SPECIES_AMPHAROS, CRY_MODE_ENCOUNTER
	goto_if_set FLAG_HOENN_DAILY_AMPHAROS_BERRY, HoennSeek_EventScript_StrandedAmpharosFed
	call_if_eq VAR_HOENN_AMPHAROS_STATE, 0, HoennSeek_EventScript_StrandedAmpharosFirst
	call_if_ne VAR_HOENN_AMPHAROS_STATE, 0, HoennSeek_EventScript_StrandedAmpharosAgain
	waitmoncry
	specialvar VAR_RESULT, HoennHasAnyBerry
	goto_if_eq VAR_RESULT, FALSE, HoennSeek_EventScript_StrandedAmpharosNoBerry
	msgbox HoennSeek_Text_StrandedAmpharosOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, HoennSeek_EventScript_StrandedAmpharosStays
	fadescreen FADE_TO_BLACK
	special Bag_ChooseBerry
	waitstate
	goto_if_eq VAR_ITEM_ID, ITEM_NONE, HoennSeek_EventScript_StrandedAmpharosStays
	removeitem VAR_ITEM_ID
	bufferitemname STR_VAR_1, VAR_ITEM_ID
	setflag FLAG_HOENN_DAILY_AMPHAROS_BERRY
	addvar VAR_HOENN_AMPHAROS_STATE, 1
	playmoncry SPECIES_AMPHAROS, CRY_MODE_NORMAL
	msgbox HoennSeek_Text_StrandedAmpharosAte, MSGBOX_DEFAULT
	waitmoncry
	goto_if_ge VAR_HOENN_AMPHAROS_STATE, HOENN_AMPHAROS_TRUSTS, HoennSeek_EventScript_StrandedAmpharosNowTrusts
	msgbox HoennSeek_Text_StrandedAmpharosWary, MSGBOX_DEFAULT
	release
	end

HoennSeek_EventScript_StrandedAmpharosFirst:
	msgbox HoennSeek_Text_StrandedAmpharos, MSGBOX_DEFAULT
	return

HoennSeek_EventScript_StrandedAmpharosAgain:
	msgbox HoennSeek_Text_StrandedAmpharosAgain, MSGBOX_DEFAULT
	return

HoennSeek_EventScript_StrandedAmpharosFed:
	msgbox HoennSeek_Text_StrandedAmpharosFed, MSGBOX_DEFAULT
	waitmoncry
	release
	end

HoennSeek_EventScript_StrandedAmpharosNoBerry:
	msgbox HoennSeek_Text_StrandedAmpharosNoBerry, MSGBOX_DEFAULT
	release
	end

HoennSeek_EventScript_StrandedAmpharosStays:
	msgbox HoennSeek_Text_StrandedAmpharosStays, MSGBOX_DEFAULT
	release
	end

@ The third BERRY: it trusts you now, and asks straight away.
HoennSeek_EventScript_StrandedAmpharosNowTrusts:
	msgbox HoennSeek_Text_StrandedAmpharosNowTrusts, MSGBOX_DEFAULT
	goto HoennSeek_EventScript_StrandedAmpharosRide

HoennSeek_EventScript_StrandedAmpharosTrusts:
	playmoncry SPECIES_AMPHAROS, CRY_MODE_NORMAL
	msgbox HoennSeek_Text_StrandedAmpharosTrusts, MSGBOX_DEFAULT
	waitmoncry
HoennSeek_EventScript_StrandedAmpharosRide:
	msgbox HoennSeek_Text_StrandedAmpharosRide, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, HoennSeek_EventScript_StrandedAmpharosStays
	playmoncry SPECIES_AMPHAROS, CRY_MODE_NORMAL
	removeobject LOCALID_HOENN_STRANDED_AMPHAROS
	waitmoncry
	setvar VAR_HOENN_AMPHAROS_STATE, HOENN_AMPHAROS_RIDING
	updatefollowingmon
	msgbox HoennSeek_Text_StrandedAmpharosClimbs, MSGBOX_DEFAULT
	release
	end

@ HoennLaneAOnStep (src/hoenn_lane_a.c) runs this on your first step on land
@ while it rides (landing from Surf isn't a step; the next one is), on any
@ map. It's your follower then, so it hops, runs off along open land
@ (HoennAmpharosRunDir), and the lighthouse scene follows; you're put back on
@ this tile afterwards (HoennAmpharosSaveReturn).
HoennSeek_EventScript_AmpharosAshore::
	lockall
	setvar VAR_HOENN_AMPHAROS_STATE, HOENN_AMPHAROS_ARRIVING
	special HoennAmpharosSaveReturn
	specialvar VAR_0x800B, HoennAmpharosRunDir
	goto_if_eq VAR_0x800B, DIR_NONE, HoennSeek_EventScript_AmpharosAshoreCry
	applymovement OBJ_EVENT_ID_FOLLOWER, HoennSeek_Movement_AmpharosHopOff
	waitmovement 0
HoennSeek_EventScript_AmpharosAshoreCry:
	playmoncry SPECIES_AMPHAROS, CRY_MODE_NORMAL
	msgbox HoennSeek_Text_AmpharosAshore, MSGBOX_DEFAULT
	waitmoncry
	closemessage
	call_if_eq VAR_0x800B, DIR_NORTH, HoennSeek_EventScript_AmpharosRunsNorth
	call_if_eq VAR_0x800B, DIR_SOUTH, HoennSeek_EventScript_AmpharosRunsSouth
	call_if_eq VAR_0x800B, DIR_WEST, HoennSeek_EventScript_AmpharosRunsWest
	call_if_eq VAR_0x800B, DIR_EAST, HoennSeek_EventScript_AmpharosRunsEast
	msgbox HoennSeek_Text_AmpharosRanHome, MSGBOX_DEFAULT
	closemessage
	special HoennAmpharosToLighthouse @ warpsilent can't take x 158 (s8)
	waitstate
	end

HoennSeek_EventScript_AmpharosRunsNorth:
	applymovement OBJ_EVENT_ID_FOLLOWER, HoennSeek_Movement_AmpharosRunsNorth
	waitmovement 0
	return

HoennSeek_EventScript_AmpharosRunsSouth:
	applymovement OBJ_EVENT_ID_FOLLOWER, HoennSeek_Movement_AmpharosRunsSouth
	waitmovement 0
	return

HoennSeek_EventScript_AmpharosRunsWest:
	applymovement OBJ_EVENT_ID_FOLLOWER, HoennSeek_Movement_AmpharosRunsWest
	waitmovement 0
	return

HoennSeek_EventScript_AmpharosRunsEast:
	applymovement OBJ_EVENT_ID_FOLLOWER, HoennSeek_Movement_AmpharosRunsEast
	waitmovement 0
	return

HoennSeek_Movement_AmpharosHopOff:
	jump_in_place_down
	face_player
	step_end

HoennSeek_Movement_AmpharosRunsNorth:
	walk_fast_up
	walk_fast_up
	walk_fast_up
	set_invisible
	step_end

HoennSeek_Movement_AmpharosRunsSouth:
	walk_fast_down
	walk_fast_down
	walk_fast_down
	set_invisible
	step_end

HoennSeek_Movement_AmpharosRunsWest:
	walk_fast_left
	walk_fast_left
	walk_fast_left
	set_invisible
	step_end

HoennSeek_Movement_AmpharosRunsEast:
	walk_fast_right
	walk_fast_right
	walk_fast_right
	set_invisible
	step_end

@ ---- The lighthouse top --------------------------------------------------------
@ ON_TRANSITION: the rescued AMPHAROS lives next to AMPHY. On the arrival scene
@ JASMINE is shown even if she has gone back to her gym (and hidden again
@ after), your follower stays in its ball, and the AMPHAROS waits off screen.
HoennSeek_EventScript_LighthouseOnTransition::
	setflag FLAG_HOENN_HIDE_LIGHTHOUSE_AMPHAROS
	goto_if_eq VAR_HOENN_AMPHAROS_STATE, HOENN_AMPHAROS_ARRIVING, HoennSeek_EventScript_LighthouseArriving
	goto_if_unset FLAG_HOENN_RESCUED_AMPHAROS, HoennSeek_EventScript_LighthouseOnTransitionEnd
	clearflag FLAG_HOENN_HIDE_LIGHTHOUSE_AMPHAROS
HoennSeek_EventScript_LighthouseOnTransitionEnd:
	end

HoennSeek_EventScript_LighthouseArriving:
	setflag FLAG_TEMP_HIDE_FOLLOWER
	clearflag FLAG_HOENN_AMPHAROS_JASMINE_AWAY
	goto_if_unset FLAG_HIDE_LIGHTHOUSE_JASMINE, HoennSeek_EventScript_LighthouseOnTransitionEnd
	setflag FLAG_HOENN_AMPHAROS_JASMINE_AWAY
	clearflag FLAG_HIDE_LIGHTHOUSE_JASMINE
	end

@ ON_WARP_INTO_MAP_TABLE: you aren't in the scene (the camera stays on your
@ hidden avatar at 158,11, which frames the stairs and AMPHY's corner).
HoennSeek_EventScript_LighthouseHidePlayer::
	special HoennAmpharosHidePlayer
	end

@ ON_FRAME_TABLE: it comes up the stairs to JASMINE and AMPHY.
HoennSeek_EventScript_LighthouseAmpharosArrives::
	lockall
	setobjectxyperm LOCALID_HOENN_LIGHTHOUSE_AMPHAROS, 156, 14
	clearflag FLAG_HOENN_HIDE_LIGHTHOUSE_AMPHAROS
	addobject LOCALID_HOENN_LIGHTHOUSE_AMPHAROS
	applymovement LOCALID_HOENN_LIGHTHOUSE_AMPHAROS, HoennSeek_Movement_AmpharosUpTheStairs
	waitmovement 0
	applymovement LOCALID_LIGHTHOUSE_JASMINE, Common_Movement_FaceRight
	waitmovement 0
	playmoncry SPECIES_AMPHAROS, CRY_MODE_NORMAL
	msgbox HoennSeek_Text_JasmineMeetsAmpharos, MSGBOX_DEFAULT
	waitmoncry
	playmoncry SPECIES_AMPHAROS, CRY_MODE_NORMAL
	msgbox HoennSeek_Text_AmphyMeetsAmpharos, MSGBOX_DEFAULT
	waitmoncry
	setvar VAR_HOENN_AMPHAROS_STATE, HOENN_AMPHAROS_HOME
	setflag FLAG_HOENN_RESCUED_AMPHAROS
	setobjectxyperm LOCALID_HOENN_LIGHTHOUSE_AMPHAROS, 157, 8
	call_if_set FLAG_HOENN_AMPHAROS_JASMINE_AWAY, HoennSeek_EventScript_LighthouseJasmineAway
	fadescreen FADE_TO_BLACK
	special HoennAmpharosReturn
	waitstate
	end

HoennSeek_EventScript_LighthouseJasmineAway:
	setflag FLAG_HIDE_LIGHTHOUSE_JASMINE
	clearflag FLAG_HOENN_AMPHAROS_JASMINE_AWAY
	return

HoennSeek_Movement_AmpharosUpTheStairs:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_up
	walk_up
	face_left
	step_end

HoennSeek_EventScript_LighthouseRescuedAmpharos::
	lock
	faceplayer
	playmoncry SPECIES_AMPHAROS, CRY_MODE_NORMAL
	msgbox HoennSeek_Text_LighthouseRescuedAmpharos, MSGBOX_DEFAULT
	waitmoncry
	release
	end

@ AMPHY at the top of the lighthouse (map.json script swap). After dark, once
@ healed, it watches the second light; otherwise HnS's own script runs.
HoennSeek_EventScript_LighthouseAmphy::
	goto_if_lt VAR_OLIVINE_CITY_STATE, 5, OlivineLighthouse_EventScript_Ampharos
	gettimeofday
	goto_if_ne VAR_0x8000, HOENN_TIME_NIGHT, OlivineLighthouse_EventScript_Ampharos
	lock
	playmoncry SPECIES_AMPHAROS, CRY_MODE_NORMAL
	goto_if_set FLAG_HOENN_RESCUED_AMPHAROS, HoennSeek_EventScript_AmphyContent
	msgbox HoennSeek_Text_AmphyWatchesLight, MSGBOX_DEFAULT
	waitmoncry
	release
	end

HoennSeek_EventScript_AmphyContent:
	msgbox HoennSeek_Text_AmphyContent, MSGBOX_DEFAULT
	waitmoncry
	release
	end

@ May: Jasmine keeps the LEAGUE posted about the lighthouse, and Norman reads
@ the reports.
HoennSeek_EventScript_CallAmpharos::
	setflag FLAG_HOENN_CALL_AMPHAROS
	setspeaker HoennSeek_Text_NameMay
	pokenavcall HoennSeek_Text_CallAmpharos
	goto HoennSeek_EventScript_CallEnd

HoennSeek_Text_LanturnLightBlinks:
	.string "A LANTURN bobs on the dark water.\n"
	.string "Its light blinks on and off…\p"
	.string "It swims off a little way and\n"
	.string "waits. It wants you to follow!$"

HoennSeek_Text_LanturnIntoCave:
	.string "The LANTURN swam into the rocks!\p"
	.string "There's a low sea cave at the foot\n"
	.string "of the ridge, hidden in its shadow.\p"
	.string "Its light glows somewhere\n"
	.string "far inside…$"

HoennSeek_Text_LagoonLanturn:
	.string "The LANTURN's light sways slowly\n"
	.string "over the water, toward the stone\l"
	.string "on the beach.$"

HoennSeek_Text_LagoonChinchou:
	.string "The CHINCHOU's lights blink in\n"
	.string "time with the others.$"

HoennSeek_Text_LagoonShrine:
	.string "An old stone, worn smooth\n"
	.string "by the waves.\p"
	.string "Three small hollows ring a larger\n"
	.string "one on its top. Something was\l"
	.string "meant to rest in them…$"

HoennSeek_Text_LagoonShrineProphecy:
	.string "The SLOWKING's words come back to\n"
	.string "you: lay the treasures down on the\l"
	.string "hidden shore…$"

HoennSeek_Text_StrandedAmpharos:
	.string "An AMPHAROS is stranded on the\n"
	.string "rock! Its tail light blinks\l"
	.string "and blinks.\p"
	.string "It's shaking, and it shrinks back\n"
	.string "from you. It doesn't trust you.$"

HoennSeek_Text_StrandedAmpharosAgain:
	.string "The AMPHAROS on the rock knows\n"
	.string "you. It edges a little closer.$"

HoennSeek_Text_StrandedAmpharosOffer:
	.string "It keeps eyeing your BAG.\n"
	.string "Offer it a BERRY?$"

HoennSeek_Text_StrandedAmpharosNoBerry:
	.string "It keeps eyeing your BAG. If only\n"
	.string "you had a BERRY to give it…$"

HoennSeek_Text_StrandedAmpharosAte:
	.string "The AMPHAROS snatched the\n"
	.string "{STR_VAR_1} and gobbled it up!$"

HoennSeek_Text_StrandedAmpharosWary:
	.string "It still won't come near you.\n"
	.string "Maybe tomorrow night…$"

HoennSeek_Text_StrandedAmpharosFed:
	.string "The AMPHAROS is nibbling the last\n"
	.string "of your BERRY. It's still wary.$"

HoennSeek_Text_StrandedAmpharosNowTrusts:
	.string "It isn't shaking anymore.\n"
	.string "It's looking right at you!$"

HoennSeek_Text_StrandedAmpharosTrusts:
	.string "The AMPHAROS blinks its tail at\n"
	.string "you. It's been waiting for you!$"

HoennSeek_Text_StrandedAmpharosRide:
	.string "Let it climb on behind you and\n"
	.string "take it back to land?$"

HoennSeek_Text_StrandedAmpharosClimbs:
	.string "The AMPHAROS climbed on behind\n"
	.string "you and is clinging on tight!\p"
	.string "Better get it back to dry land.\n"
	.string "Any shore will do!$"

HoennSeek_Text_StrandedAmpharosStays:
	.string "The AMPHAROS huddles on its rock,\n"
	.string "blinking out at the dark sea.$"

HoennSeek_Text_AmpharosAshore:
	.string "The AMPHAROS hopped down onto\n"
	.string "dry land and shook itself off.\p"
	.string "Its tail lit up bright as a\n"
	.string "lamp! It looks so relieved!$"

HoennSeek_Text_AmpharosRanHome:
	.string "It ran off toward the LIGHTHOUSE,\n"
	.string "its tail blinking all the way.$"

HoennSeek_Text_JasmineMeetsAmpharos:
	.string "JASMINE: Oh! An AMPHAROS…\n"
	.string "And it's soaking wet!\p"
	.string "You're the one out on the rock,\n"
	.string "aren't you? AMPHY never stopped\l"
	.string "watching your light.\p"
	.string "Someone brought you back…\n"
	.string "You can stay here with us now.$"

HoennSeek_Text_AmphyMeetsAmpharos:
	.string "AMPHY: Palulu!\p"
	.string "The two AMPHAROS blinked their\n"
	.string "tails at each other.$"

HoennSeek_Text_LighthouseRescuedAmpharos:
	.string "It's the AMPHAROS from the sea\n"
	.string "rock! JASMINE has taken it in.\p"
	.string "It blinks its tail at AMPHY, and\n"
	.string "AMPHY blinks back. Palulu!$"

HoennSeek_Text_AmphyWatchesLight:
	.string "AMPHY is gazing out to sea.\p"
	.string "Out on the dark water, past the\n"
	.string "beach, a tiny light blinks…\l"
	.string "On, off. On, off.\p"
	.string "AMPHY: Palu… Palulu?$"

HoennSeek_Text_AmphyContent:
	.string "AMPHY is gazing out to sea.\p"
	.string "The light on the water is gone.\n"
	.string "Its friend is safe beside it now.\p"
	.string "AMPHY: Palulu!$"

HoennSeek_Text_CallAmpharos:
	.string "{PLAYER}? It's MAY!\p"
	.string "JASMINE from OLIVINE keeps the\n"
	.string "LEAGUE posted on her lighthouse,\l"
	.string "and Dad reads all the reports.\p"
	.string "She says AMPHY kept staring at a\n"
	.string "second light out at sea every\l"
	.string "night. A stranded AMPHAROS!\p"
	.string "A trainer from out of town won\n"
	.string "it over with BERRIES, then gave\l"
	.string "it a ride back to shore. It ran\l"
	.string "all the way up the lighthouse!\p"
	.string "That was you, right? AMPHY must\n"
	.string "be so happy!$"

@ ============================================================================
@ Part 34b: Lugia (Route41_Lagoon_hoenn's stone, Route 41, Whirl Islands)
@ The lagoon's old stone is Lugia's shrine: three small hollows (frost,
@ thunder, flame) ring a larger one (the SILVER WING). Carrying all four
@ treasures, you lay them down: the stone answers, the sea goes still, and
@ the way to Lugia's chamber opens (FLAG_HOENN_LUGIA_SHRINE_OPEN). The
@ treasures rise back into your hands, because the feathers still call the
@ three birds (part 34a). Missing ones show as empty hollows.
@ Lugia keeps HnS's own post-story battle in the Whirl Islands chamber
@ (VAR_COMPLETED_LUGIA 4, Lv 70); one line in the chamber's OnTransition
@ keeps it away until the shrine is open. Opening the shrine also sets that
@ var to 4 when HnS's story left it at 3 (the story battle was run from or
@ won) and Lugia isn't caught, and keeps the islands' TENTACRUEL away.
@ The cameo: at night, once the lagoon is found and the SLOWKING's prophecy
@ known (part 19), the first time you swim along the ridge's foot (row 56,
@ x 52-63) Lugia surfaces at (62,58), sings one note and dives toward the
@ islands. Route 41 has no free object template, so the cameo borrows the
@ Lanturn light's, which never shows once the lagoon is found
@ (HoennLugiaCameoPrepare, src/hoenn_lane_a.c).
@ ============================================================================

HoennSeek_EventScript_LagoonShrine::
	lockall
	goto_if_set FLAG_HOENN_LUGIA_SHRINE_OPEN, HoennSeek_EventScript_LugiaShrineOpen
	msgbox HoennSeek_Text_LagoonShrine, MSGBOX_DEFAULT
	call_if_set FLAG_HOENN_SLOWKING_PROPHECY, HoennSeek_EventScript_LugiaShrineProphecy
	setvar VAR_0x8006, 0 @ treasures carried
	checkitem ITEM_FROST_FEATHER
	call_if_eq VAR_RESULT, TRUE, HoennSeek_EventScript_LugiaShrineCount
	checkitem ITEM_THUNDER_FEATHER
	call_if_eq VAR_RESULT, TRUE, HoennSeek_EventScript_LugiaShrineCount
	checkitem ITEM_FLAME_FEATHER
	call_if_eq VAR_RESULT, TRUE, HoennSeek_EventScript_LugiaShrineCount
	checkitem ITEM_SILVER_WING
	call_if_eq VAR_RESULT, TRUE, HoennSeek_EventScript_LugiaShrineCount
	goto_if_eq VAR_0x8006, 4, HoennSeek_EventScript_LugiaShrineOffer
	goto_if_eq VAR_0x8006, 0, HoennSeek_EventScript_LugiaShrineEnd
	@ Some of them: say which hollows stay empty.
	msgbox HoennSeek_Text_LugiaShrineSome, MSGBOX_DEFAULT
	checkitem ITEM_FROST_FEATHER
	call_if_eq VAR_RESULT, FALSE, HoennSeek_EventScript_LugiaShrineNoFrost
	checkitem ITEM_THUNDER_FEATHER
	call_if_eq VAR_RESULT, FALSE, HoennSeek_EventScript_LugiaShrineNoThunder
	checkitem ITEM_FLAME_FEATHER
	call_if_eq VAR_RESULT, FALSE, HoennSeek_EventScript_LugiaShrineNoFlame
	checkitem ITEM_SILVER_WING
	call_if_eq VAR_RESULT, FALSE, HoennSeek_EventScript_LugiaShrineNoWing
HoennSeek_EventScript_LugiaShrineEnd:
	releaseall
	end

HoennSeek_EventScript_LugiaShrineCount:
	addvar VAR_0x8006, 1
	return
HoennSeek_EventScript_LugiaShrineProphecy:
	msgbox HoennSeek_Text_LagoonShrineProphecy, MSGBOX_DEFAULT
	return
HoennSeek_EventScript_LugiaShrineNoFrost:
	msgbox HoennSeek_Text_LugiaShrineNoFrost, MSGBOX_DEFAULT
	return
HoennSeek_EventScript_LugiaShrineNoThunder:
	msgbox HoennSeek_Text_LugiaShrineNoThunder, MSGBOX_DEFAULT
	return
HoennSeek_EventScript_LugiaShrineNoFlame:
	msgbox HoennSeek_Text_LugiaShrineNoFlame, MSGBOX_DEFAULT
	return
HoennSeek_EventScript_LugiaShrineNoWing:
	msgbox HoennSeek_Text_LugiaShrineNoWing, MSGBOX_DEFAULT
	return

HoennSeek_EventScript_LugiaShrineOffer:
	msgbox HoennSeek_Text_LugiaShrineOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, HoennSeek_EventScript_LugiaShrineEnd
	msgbox HoennSeek_Text_LugiaShrineFeathers, MSGBOX_DEFAULT
	playse SE_M_ICY_WIND
	waitse
	playse SE_M_THUNDERBOLT
	waitse
	playse SE_M_FLAME_WHEEL
	waitse
	msgbox HoennSeek_Text_LugiaShrineWing, MSGBOX_DEFAULT
	closemessage
	playse SE_M_MORNING_SUN
	@ swapbuffers keeps the map's own palettes (a plain fade back from
	@ white came back with the day/night tint on this cave map)
	fadescreenswapbuffers FADE_TO_WHITE
	delay 30
	fadescreenswapbuffers FADE_FROM_WHITE
	waitse
	delay 30
	playmoncry SPECIES_LUGIA, CRY_MODE_ECHO_END
	waitmoncry
	setflag FLAG_HOENN_LUGIA_SHRINE_OPEN
	setflag FLAG_HIDE_WHIRL_ISLANDS_TENTACRUEL
	goto_if_set FLAG_CAUGHT_LUGIA, HoennSeek_EventScript_LugiaShrineOpened
	call_if_eq VAR_COMPLETED_LUGIA, 3, HoennSeek_EventScript_LugiaShrineWakes
HoennSeek_EventScript_LugiaShrineOpened:
	msgbox HoennSeek_Text_LugiaShrineOpened, MSGBOX_DEFAULT
	releaseall
	end

@ HnS's chamber shows its post-story Lugia at VAR_COMPLETED_LUGIA 4.
HoennSeek_EventScript_LugiaShrineWakes:
	setvar VAR_COMPLETED_LUGIA, 4
	return

HoennSeek_EventScript_LugiaShrineOpen:
	msgbox HoennSeek_Text_LugiaShrineAfter, MSGBOX_DEFAULT
	releaseall
	end

@ One line at the top of HnS's post-story branch in the Lugia chamber's
@ OnTransition: until the shrine is open, the chamber is empty.
HoennSeek_EventScript_LugiaChamberAsleep::
	setflag FLAG_HIDE_WHIRL_ISLANDS_KIMONO_GIRLS
	setflag FLAG_HIDE_LUGIA
	end

@ Called from Route 41's night check (HoennSeek_EventScript_Route41Night).
HoennSeek_EventScript_ArmLugiaCameo:
	goto_if_set FLAG_HOENN_LUGIA_CAMEO_SEEN, HoennSeek_EventScript_ArmLugiaCameoDone
	goto_if_unset FLAG_HOENN_LAGOON_FOUND, HoennSeek_EventScript_ArmLugiaCameoDone
	goto_if_unset FLAG_HOENN_SLOWKING_PROPHECY, HoennSeek_EventScript_ArmLugiaCameoDone
	goto_if_set FLAG_CAUGHT_LUGIA, HoennSeek_EventScript_ArmLugiaCameoDone
	gettimeofday
	goto_if_ne VAR_0x8000, HOENN_TIME_NIGHT, HoennSeek_EventScript_ArmLugiaCameoDone
	setvar VAR_TEMP_4, 1
HoennSeek_EventScript_ArmLugiaCameoDone:
	return

@ Coord triggers on row 56 (x 52-63), VAR_TEMP_4 = 1.
HoennSeek_EventScript_LugiaCameo::
	lockall
	setvar VAR_TEMP_4, 0
	setflag FLAG_HOENN_LUGIA_CAMEO_SEEN
	setvar VAR_0x8008, 60
	setvar VAR_0x8009, 57
	call HoennSeek_EventScript_StarterPanTo
	msgbox HoennSeek_Text_LugiaCameoSwell, MSGBOX_DEFAULT
	closemessage
	special HoennLugiaCameoPrepare
	setobjectxyperm LOCALID_HOENN_LANTURN_LIGHT, 62, 58
	clearflag FLAG_HOENN_HIDE_LANTURN_LIGHT
	playse SE_M_DIVE
	addobject LOCALID_HOENN_LANTURN_LIGHT
	waitse
	msgbox HoennSeek_Text_LugiaCameoRise, MSGBOX_DEFAULT
	closemessage
	playmoncry SPECIES_LUGIA, CRY_MODE_HIGH_PITCH
	waitmoncry
	msgbox HoennSeek_Text_LugiaCameoSing, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_HOENN_LANTURN_LIGHT, HoennSeek_Movement_LugiaCameoDive
	waitmovement 0
	playse SE_M_DIVE
	removeobject LOCALID_HOENN_LANTURN_LIGHT
	waitse
	msgbox HoennSeek_Text_LugiaCameoGone, MSGBOX_DEFAULT
	closemessage
	call HoennSeek_EventScript_StarterPanBack
	releaseall
	end

HoennSeek_Movement_LugiaCameoDive:
	walk_slow_down
	walk_slow_left
	walk_slow_down
	step_end

HoennSeek_EventScript_CallLugia::
	setflag FLAG_HOENN_CALL_LUGIA
	setspeaker HoennSeek_Text_NameBrendan
	pokenavcall HoennSeek_Text_CallLugia
	goto HoennSeek_EventScript_CallEnd

HoennSeek_Text_LugiaShrineSome:
	.string "You hold out what you carry. The\n"
	.string "stone stays cold. Some of its\l"
	.string "hollows are still waiting…$"

HoennSeek_Text_LugiaShrineNoFrost:
	.string "One small hollow is rimmed with\n"
	.string "frost, as if it misses something.$"

HoennSeek_Text_LugiaShrineNoThunder:
	.string "One small hollow is scorched in a\n"
	.string "jagged line, like a lightning bolt.$"

HoennSeek_Text_LugiaShrineNoFlame:
	.string "One small hollow is warm to the\n"
	.string "touch, as if a fire burned in it.$"

HoennSeek_Text_LugiaShrineNoWing:
	.string "The large hollow in the middle\n"
	.string "is shaped like a silver wing.$"

HoennSeek_Text_LugiaShrineOffer:
	.string "The FROST, THUNDER and FLAME\n"
	.string "FEATHERS stir in your bag, and\l"
	.string "the SILVER WING with them.\p"
	.string "Lay the treasures down in\n"
	.string "the hollows?$"

HoennSeek_Text_LugiaShrineFeathers:
	.string "{PLAYER} laid the three feathers in\n"
	.string "the small hollows.$"

HoennSeek_Text_LugiaShrineWing:
	.string "{PLAYER} laid the SILVER WING\n"
	.string "in the middle…$"

HoennSeek_Text_LugiaShrineOpened:
	.string "The stone shone, and a song rose\n"
	.string "from deep under the sea.\p"
	.string "Out past the lagoon, the waves\n"
	.string "around the WHIRL ISLANDS fell still.\p"
	.string "The treasures rose from the stone\n"
	.string "and drifted back into your hands.\p"
	.string "The way into the islands'\n"
	.string "deepest chamber is open.$"

HoennSeek_Text_LugiaShrineAfter:
	.string "The old stone's hollows still\n"
	.string "shimmer faintly.\p"
	.string "Out past the lagoon, the sea\n"
	.string "around the WHIRL ISLANDS is calm.$"

HoennSeek_Text_LugiaCameoSwell:
	.string "The sea swells, out past\n"
	.string "the ridge…$"

HoennSeek_Text_LugiaCameoRise:
	.string "A huge silver shape rises out\n"
	.string "of the waves!$"

HoennSeek_Text_LugiaCameoSing:
	.string "It sang one long, clear note\n"
	.string "over the dark water…$"

HoennSeek_Text_LugiaCameoGone:
	.string "…and dove, heading for the\n"
	.string "WHIRL ISLANDS.$"

HoennSeek_Text_CallLugia:
	.string "{PLAYER}! It's BRENDAN.\p"
	.string "BILL just phoned. He's been\n"
	.string "calling us about those three\l"
	.string "birds, remember?\p"
	.string "JASMINE's lighthouse keeper told\n"
	.string "him the sea round the WHIRL\l"
	.string "ISLANDS went flat calm last night.\p"
	.string "No wind, no whirlpools, and a song\n"
	.string "coming up from under the water.\p"
	.string "BILL says that's the old AZALEA\n"
	.string "song come true. Someone laid the\l"
	.string "three feathers down!\p"
	.string "Was that you? Whatever sings down\n"
	.string "there is waiting deep in the\l"
	.string "islands now. Go and see it!$"

@ Part 37: Jirachi, Deoxys, the Regis, Arceus (src/hoenn_lane_a.c has the design)
@ - Jirachi: wish on a shooting star at night at three spots (Meteor Falls
@   clifftop, the Space Center's 2F windows, the moon hollow's pool); then the
@   white rock answers on the Clefairy's Monday night (HnS's summon).
@ - Deoxys: the Space Center 2F scientist logs a signal on three different
@   nights, then gives the AURORA TICKET (Vermilion's ferry to Birth Island).
@ - Regis: boulders seal HnS's three Regi doors at the Sinjoh Ruins. Their
@   braille reads only after part 28's inscription; RELICANTH and WAILORD in the
@   party roll them aside.
@ - Arceus: after HnS's first (uncatchable) battle, the second waits until
@   you've read the inscription (one hook line in its room's script).
@ ============================================================================

@ ---- Jirachi: the three wishes ----------------------------------------------
@ Meteor Falls clifftop: the boulder at its top right (bg events).
HoennSeek_EventScript_WishMeteorFalls::
	lockall
	gettimeofday
	goto_if_ne VAR_0x8000, HOENN_TIME_NIGHT, HoennSeek_EventScript_WishFallsDay
	goto_if_set FLAG_HOENN_WISH_METEOR_FALLS, HoennSeek_EventScript_WishAlreadyMade
	msgbox HoennSeek_Text_WishFallsNight, MSGBOX_DEFAULT
	call HoennSeek_EventScript_ShootingStar
	goto_if_eq VAR_RESULT, NO, HoennSeek_EventScript_WishEnd
	setflag FLAG_HOENN_WISH_METEOR_FALLS
	goto HoennSeek_EventScript_WishMade

HoennSeek_EventScript_WishFallsDay:
	msgbox HoennSeek_Text_WishFallsDay, MSGBOX_DEFAULT
	goto HoennSeek_EventScript_WishEnd

@ Space Center 2F: the windows along its north wall (bg events, facing up).
HoennSeek_EventScript_WishSpaceCenter::
	lockall
	gettimeofday
	goto_if_ne VAR_0x8000, HOENN_TIME_NIGHT, HoennSeek_EventScript_WishWindowDay
	goto_if_set FLAG_HOENN_WISH_SPACE_CENTER, HoennSeek_EventScript_WishAlreadyMade
	msgbox HoennSeek_Text_WishWindowNight, MSGBOX_DEFAULT
	call HoennSeek_EventScript_ShootingStar
	goto_if_eq VAR_RESULT, NO, HoennSeek_EventScript_WishEnd
	setflag FLAG_HOENN_WISH_SPACE_CENTER
	goto HoennSeek_EventScript_WishMade

HoennSeek_EventScript_WishWindowDay:
	msgbox HoennSeek_Text_WishWindowDay, MSGBOX_DEFAULT
	goto HoennSeek_EventScript_WishEnd

@ The moon hollow's pool at night (lane B's HoennSeek_EventScript_MoonHollowPool
@ shows the moon's reflection, then comes here; it has already locked).
HoennSeek_EventScript_WishMoonHollow::
	goto_if_set FLAG_HOENN_WISH_MOON_HOLLOW, HoennSeek_EventScript_WishEnd
	call HoennSeek_EventScript_ShootingStar
	goto_if_eq VAR_RESULT, NO, HoennSeek_EventScript_WishEnd
	setflag FLAG_HOENN_WISH_MOON_HOLLOW
	goto HoennSeek_EventScript_WishMade

@ A streak of light, then "Make a wish?" (answer in VAR_RESULT).
HoennSeek_EventScript_ShootingStar:
	playse SE_SHINY
	fadescreenswapbuffers FADE_TO_WHITE
	delay 6
	fadescreenswapbuffers FADE_FROM_WHITE
	waitse
	msgbox HoennSeek_Text_ShootingStar, MSGBOX_YESNO
	return

HoennSeek_EventScript_WishMade:
	msgbox HoennSeek_Text_WishMade, MSGBOX_DEFAULT
	specialvar VAR_RESULT, HoennWishCount
	goto_if_lt VAR_RESULT, 3, HoennSeek_EventScript_WishEnd
	playse SE_M_HEAL_BELL
	msgbox HoennSeek_Text_WishThird, MSGBOX_DEFAULT
	waitse
	goto HoennSeek_EventScript_WishEnd

HoennSeek_EventScript_WishAlreadyMade:
	msgbox HoennSeek_Text_WishAlreadyMade, MSGBOX_DEFAULT
HoennSeek_EventScript_WishEnd:
	releaseall
	end

@ ---- Jirachi: the white rock (MtMoon_Outside_hns's sign, a map.json swap) ----
@ HnS's rock summoned Jirachi on any night. Now it needs the three wishes and
@ the Clefairy's dance (Monday nights: FLAG_HOENN_HIDE_CLEFAIRY_DANCE is clear,
@ part 3 decides it on arrival); then HnS's own summon scene runs.
HoennSeek_EventScript_WhiteRock::
	lock
	msgbox MtMoon_Outside_Text_WhiteRockTouchIt, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, MtMoon_Outside_EventScript_WhiteRockNoOp
	goto_if_set FLAG_SUMMONED_MTMOON_JIRACHI, MtMoon_OutsideEventScript_WhiteRockNoReaction
	goto_if_set FLAG_HOENN_DAILY_JIRACHI_GONE, HoennSeek_EventScript_WhiteRockWaiting @ part 38: not again tonight
	specialvar VAR_RESULT, HoennWishCount
	goto_if_eq VAR_RESULT, 0, MtMoon_OutsideEventScript_WhiteRockNoReaction
	goto_if_lt VAR_RESULT, 3, HoennSeek_EventScript_WhiteRockListening
	goto_if_set FLAG_HOENN_HIDE_CLEFAIRY_DANCE, HoennSeek_EventScript_WhiteRockWaiting
	goto MtMoon_Outside_EventScript_WhiteRockSpawnJirachi

HoennSeek_EventScript_WhiteRockListening:
	msgbox HoennSeek_Text_WhiteRockListening, MSGBOX_DEFAULT
	release
	end

HoennSeek_EventScript_WhiteRockWaiting:
	msgbox HoennSeek_Text_WhiteRockWaiting, MSGBOX_DEFAULT
	release
	end

@ Jirachi's object (a map.json swap of HnS's script, same battle at Lv 50).
@ Caught: gone. Knocked out: gone, but the rock can wake it again on a later
@ Monday night (HnS lost it until the next Hall of Fame). Ran: it stays.
HoennSeek_EventScript_MtMoonJirachi::
	lock
	faceplayer
	playmoncry SPECIES_JIRACHI, CRY_MODE_ENCOUNTER
	msgbox MtMoon_Outside_Text_Jirachi
	delay 40
	waitmoncry
	seteventmon SPECIES_JIRACHI, 50
	special BattleSetup_StartLegendaryBattle
	waitstate
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, MtMoon_Outside_EventScript_JirachiRan
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, HoennSeek_EventScript_MtMoonJirachiGone
	clearflag FLAG_SUMMONED_MTMOON_JIRACHI
	setflag FLAG_HOENN_DAILY_JIRACHI_GONE @ part 38: back on another dancing night, not tonight
HoennSeek_EventScript_MtMoonJirachiGone:
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_MTMOON_JIRACHI
	setflag FLAG_HIDE_MTMOON_JIRACHI
	fadescreenswapbuffers FADE_FROM_BLACK
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, HoennSeek_EventScript_MtMoonJirachiEnd
	msgbox HoennSeek_Text_JirachiBackToSleep, MSGBOX_DEFAULT
HoennSeek_EventScript_MtMoonJirachiEnd:
	release
	end

@ ---- Deoxys: the signal (MossdeepCity_SpaceCenter_2F's scientist, a swap) ----
HoennSeek_EventScript_SignalScientist::
	lock
	faceplayer
	goto_if_set FLAG_HOENN_DEOXYS_TICKET, HoennSeek_EventScript_SignalAfter
	specialvar VAR_RESULT, HoennDeoxysSignalNight
	goto_if_eq VAR_RESULT, 0, HoennSeek_EventScript_SignalDay
	goto_if_ge VAR_HOENN_DEOXYS_SIGNAL, HOENN_DEOXYS_NIGHTS, HoennSeek_EventScript_SignalTicket
	goto_if_eq VAR_RESULT, 1, HoennSeek_EventScript_SignalSameNight
	goto_if_eq VAR_HOENN_DEOXYS_SIGNAL, 2, HoennSeek_EventScript_SignalSecond
	msgbox HoennSeek_Text_SignalFirst, MSGBOX_DEFAULT
	release
	end

HoennSeek_EventScript_SignalSecond:
	msgbox HoennSeek_Text_SignalSecond, MSGBOX_DEFAULT
	release
	end

HoennSeek_EventScript_SignalSameNight:
	msgbox HoennSeek_Text_SignalSameNight, MSGBOX_DEFAULT
	release
	end

HoennSeek_EventScript_SignalDay:
	goto_if_eq VAR_HOENN_DEOXYS_SIGNAL, 0, MossdeepCity_SpaceCenter_2F_EventScript_ScientistNormal
	msgbox HoennSeek_Text_SignalDay, MSGBOX_DEFAULT
	release
	end

HoennSeek_EventScript_SignalTicket:
	msgbox HoennSeek_Text_SignalThird, MSGBOX_DEFAULT
	checkitem ITEM_AURORA_TICKET
	goto_if_eq VAR_RESULT, TRUE, HoennSeek_EventScript_SignalTicketDone
	giveitem ITEM_AURORA_TICKET
	goto_if_eq VAR_RESULT, FALSE, HoennSeek_EventScript_SignalTicketEnd
HoennSeek_EventScript_SignalTicketDone:
	setflag FLAG_HOENN_DEOXYS_TICKET
	msgbox HoennSeek_Text_SignalTicketHow, MSGBOX_DEFAULT
HoennSeek_EventScript_SignalTicketEnd:
	release
	end

HoennSeek_EventScript_SignalAfter:
	msgbox HoennSeek_Text_SignalAfter, MSGBOX_DEFAULT
	release
	end

@ HnS's Olivine fan (OlivineCity_hns, a swap) gave the AURORA TICKET to any
@ champion. She now passes on what MARY's show said about the signal instead.
HoennSeek_EventScript_OlivineAuroraFan::
	lock
	faceplayer
	checkitem ITEM_AURORA_TICKET
	goto_if_eq VAR_RESULT, TRUE, OlivineCity_EventScript_EonTicketWomanAfter
	goto_if_unset FLAG_IS_KANTO_CHAMPION, OlivineCity_EventScript_EonTicketWoman
	msgbox HoennSeek_Text_OlivineFanSignal, MSGBOX_DEFAULT
	closemessage
	release
	end

@ ---- The Regis: the sealed doors (SinjohRuins_hns) ---------------------------
@ HnS opens each door on ON_LOAD once enough plates are found (VAR_PLATECOUNTER
@ 3, 6, 9). A boulder object now stands in each open doorway until it's rolled
@ aside; Regieleki's and Regidrago's doors are HnS's as they were.
@ Called from SinjohRuins_hns's ON_TRANSITION (one hook line).
HoennSeek_EventScript_RegiSealsArm::
	setflag FLAG_HOENN_REGI_HIDE_ROCK
	setflag FLAG_HOENN_REGI_HIDE_ICE
	setflag FLAG_HOENN_REGI_HIDE_STEEL
	goto_if_lt VAR_PLATECOUNTER, 3, HoennSeek_EventScript_RegiSealsArmEnd
	call_if_unset FLAG_HOENN_REGI_OPEN_ROCK, HoennSeek_EventScript_RegiSealShowRock
	goto_if_lt VAR_PLATECOUNTER, 6, HoennSeek_EventScript_RegiSealsArmEnd
	call_if_unset FLAG_HOENN_REGI_OPEN_ICE, HoennSeek_EventScript_RegiSealShowIce
	goto_if_lt VAR_PLATECOUNTER, 9, HoennSeek_EventScript_RegiSealsArmEnd
	call_if_unset FLAG_HOENN_REGI_OPEN_STEEL, HoennSeek_EventScript_RegiSealShowSteel
HoennSeek_EventScript_RegiSealsArmEnd:
	return

HoennSeek_EventScript_RegiSealShowRock:
	clearflag FLAG_HOENN_REGI_HIDE_ROCK
	return

HoennSeek_EventScript_RegiSealShowIce:
	clearflag FLAG_HOENN_REGI_HIDE_ICE
	return

HoennSeek_EventScript_RegiSealShowSteel:
	clearflag FLAG_HOENN_REGI_HIDE_STEEL
	return

@ The boulders' object scripts. Flag commands can't take a var, so each door
@ has its own short tail.
HoennSeek_EventScript_RegiSealRock::
	lock
	call HoennSeek_EventScript_RegiSealRead
	goto_if_eq VAR_RESULT, FALSE, HoennSeek_EventScript_RegiSealEnd
	setflag FLAG_HOENN_REGI_OPEN_ROCK
	goto HoennSeek_EventScript_RegiSealMove

HoennSeek_EventScript_RegiSealIce::
	lock
	call HoennSeek_EventScript_RegiSealRead
	goto_if_eq VAR_RESULT, FALSE, HoennSeek_EventScript_RegiSealEnd
	setflag FLAG_HOENN_REGI_OPEN_ICE
	goto HoennSeek_EventScript_RegiSealMove

HoennSeek_EventScript_RegiSealSteel::
	lock
	call HoennSeek_EventScript_RegiSealRead
	goto_if_eq VAR_RESULT, FALSE, HoennSeek_EventScript_RegiSealEnd
	setflag FLAG_HOENN_REGI_OPEN_STEEL
	goto HoennSeek_EventScript_RegiSealMove

@ The braille, its translation once the inscription is read, the cameo the
@ first time, then the party check. VAR_RESULT: TRUE when the boulder moves.
HoennSeek_EventScript_RegiSealRead:
	msgbox HoennSeek_Text_RegiSealSee, MSGBOX_DEFAULT
	braillemessage HoennSeek_Braille_RegiSeal
	waitbuttonpress
	closebraillemessage
	goto_if_set FLAG_HOENN_CIPHER_INSCRIPTION, HoennSeek_EventScript_RegiSealTranslate
	msgbox HoennSeek_Text_RegiSealUnread, MSGBOX_DEFAULT
	setvar VAR_RESULT, FALSE
	return

HoennSeek_EventScript_RegiSealTranslate:
	msgbox HoennSeek_Text_RegiSealRead, MSGBOX_DEFAULT
	call_if_unset FLAG_HOENN_REGI_STIRRED, HoennSeek_EventScript_RegiSealStir
	checkspecies SPECIES_RELICANTH
	goto_if_eq VAR_RESULT, FALSE, HoennSeek_EventScript_RegiSealStays
	checkspecies SPECIES_WAILORD
	goto_if_eq VAR_RESULT, FALSE, HoennSeek_EventScript_RegiSealStays
	setvar VAR_RESULT, TRUE
	return

HoennSeek_EventScript_RegiSealStays:
	msgbox HoennSeek_Text_RegiSealStays, MSGBOX_DEFAULT
	setvar VAR_RESULT, FALSE
	return

@ The cameo: the first time the braille is read, the giant behind it stirs.
HoennSeek_EventScript_RegiSealStir:
	setflag FLAG_HOENN_REGI_STIRRED
	closemessage
	delay 20
	playse SE_M_STRENGTH
	setvar VAR_0x8004, 1  @ vertical pan
	setvar VAR_0x8005, 0  @ horizontal pan
	setvar VAR_0x8006, 4  @ num shakes
	setvar VAR_0x8007, 8  @ shake delay
	special ShakeCamera
	waitstate
	delay 30
	playse SE_M_STRENGTH
	setvar VAR_0x8004, 1
	setvar VAR_0x8005, 0
	setvar VAR_0x8006, 4
	setvar VAR_0x8007, 8
	special ShakeCamera
	waitstate
	msgbox HoennSeek_Text_RegiSealStir, MSGBOX_DEFAULT
	return

HoennSeek_EventScript_RegiSealMove:
	msgbox HoennSeek_Text_RegiSealCry, MSGBOX_DEFAULT
	closemessage
	playse SE_M_STRENGTH
	setvar VAR_0x8004, 2  @ vertical pan
	setvar VAR_0x8005, 2  @ horizontal pan
	setvar VAR_0x8006, 10 @ num shakes
	setvar VAR_0x8007, 4  @ shake delay
	special ShakeCamera
	waitstate
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject VAR_LAST_TALKED
	fadescreenswapbuffers FADE_FROM_BLACK
	msgbox HoennSeek_Text_RegiSealOpen, MSGBOX_DEFAULT
HoennSeek_EventScript_RegiSealEnd:
	release
	end

HoennSeek_Braille_RegiSeal:
	brailleformat 0, 0, 0, 0, 0, 0
	.braille "THE DEEP\n"
	.braille "THE SEA$"

@ ---- Arceus (one hook line at the top of HnS's second battle) ----------------
@ HnS's first battle (Arceus with the Iron Plate, uncatchable) is unchanged.
@ The second, catchable one now waits for part 28's inscription.
HoennSeek_EventScript_ArceusWaits::
	msgbox HoennSeek_Text_ArceusWaits, MSGBOX_DEFAULT
	release
	end

@ ---- Phone ------------------------------------------------------------------
HoennSeek_EventScript_CallWishes::
	setflag FLAG_HOENN_CALL_WISHES
	setspeaker HoennSeek_Text_NameMay
	pokenavcall HoennSeek_Text_CallWishes
	goto HoennSeek_EventScript_CallEnd

HoennSeek_EventScript_CallDeoxys::
	setflag FLAG_HOENN_CALL_DEOXYS
	setspeaker HoennSeek_Text_NameBrendan
	pokenavcall HoennSeek_Text_CallDeoxys
	goto HoennSeek_EventScript_CallEnd

HoennSeek_EventScript_CallRegis::
	setflag FLAG_HOENN_CALL_REGIS
	setspeaker HoennSeek_Text_NameMay
	pokenavcall HoennSeek_Text_CallRegis
	goto HoennSeek_EventScript_CallEnd

@ ---- Texts ------------------------------------------------------------------
HoennSeek_Text_WishFallsDay:
	.string "A smooth boulder, warm from the\n"
	.string "sun. Its top faces the open sky.$"

HoennSeek_Text_WishFallsNight:
	.string "From the boulder you can see the\n"
	.string "whole night sky over the falls.$"

HoennSeek_Text_WishWindowDay:
	.string "Through the windows: the rocket\n"
	.string "pad, and the sea beyond it.$"

HoennSeek_Text_WishWindowNight:
	.string "Through the windows: stars over\n"
	.string "the rocket pad and the dark sea.$"

HoennSeek_Text_ShootingStar:
	.string "A shooting star streaks across\n"
	.string "the sky!\p"
	.string "Make a wish?$"

HoennSeek_Text_WishMade:
	.string "{PLAYER} closed their eyes and made\n"
	.string "a wish on the falling star…$"

HoennSeek_Text_WishThird:
	.string "Far away, something seemed to\n"
	.string "chime, like a little bell.\p"
	.string "Three wishes, made on three\n"
	.string "falling stars…$"

HoennSeek_Text_WishAlreadyMade:
	.string "You've already made your wish here.\n"
	.string "The stars keep turning overhead.$"

HoennSeek_Text_WhiteRockListening:
	.string "{PLAYER} touched the unusual rock.\n"
	.string "..........................\p"
	.string "It feels faintly warm, as if it\n"
	.string "were listening for something.$"

HoennSeek_Text_WhiteRockWaiting:
	.string "{PLAYER} touched the unusual rock.\n"
	.string "..........................\p"
	.string "It glows softly, like the moon.\n"
	.string "But nothing more happens.\p"
	.string "It seems to be waiting for\n"
	.string "something to happen here.$"

HoennSeek_Text_JirachiBackToSleep:
	.string "JIRACHI curled up and drifted back\n"
	.string "into the stars.\p"
	.string "Maybe the white rock will wake it\n"
	.string "on another dancing night.$"

HoennSeek_Text_SignalFirst:
	.string "Shh! Listen… beep… beep-beep…\p"
	.string "That pulse is coming from space!\n"
	.string "From a meteorite, I'd bet my job.\p"
	.string "It only comes through at night.\n"
	.string "If I could just log it a few more\l"
	.string "nights, I'd know where it lands.$"

HoennSeek_Text_SignalSecond:
	.string "You're back! Listen, it's the same\n"
	.string "pulse as before, but louder.\p"
	.string "Two nights of readings… One more\n"
	.string "and I can plot where it lands.$"

HoennSeek_Text_SignalSameNight:
	.string "Tonight's readings are logged.\n"
	.string "The pulse only changes between\l"
	.string "nights, so come back another one.$"

HoennSeek_Text_SignalDay:
	.string "The signal? It's drowned out by\n"
	.string "the sun all day.\p"
	.string "Come back at night, when the sky\n"
	.string "is quiet.$"

HoennSeek_Text_SignalThird:
	.string "Three nights of readings… Here!\n"
	.string "The pulse comes from an island far\l"
	.string "south of KANTO's VERMILION CITY.\p"
	.string "There's a triangle of rock on it,\n"
	.string "in the photos. Something's waiting\l"
	.string "there for a visitor.\p"
	.string "The SPACE CENTER chartered a pass\n"
	.string "for the ferry. You go. I'll listen.$"

HoennSeek_Text_SignalTicketHow:
	.string "Show the AURORA TICKET to the\n"
	.string "sailor at VERMILION's port and ask\l"
	.string "for BIRTH ISLAND.$"

HoennSeek_Text_SignalAfter:
	.string "The pulse from BIRTH ISLAND?\n"
	.string "Some nights it's quiet, some nights\l"
	.string "it shouts. What's out there?$"

HoennSeek_Text_OlivineFanSignal:
	.string "You must be {PLAYER}! The champion!\p"
	.string "On MARY's show last night, a guest\n"
	.string "from HOENN's SPACE CENTER said\l"
	.string "they hear a beeping from space!\p"
	.string "Only at night, though. Spooky!\n"
	.string "Their scientist logs it upstairs.$"

HoennSeek_Text_RegiSealSee:
	.string "A huge boulder fills the cave mouth.\n"
	.string "Braille is carved into its face.$"

HoennSeek_Text_RegiSealUnread:
	.string "The braille is old, older than any\n"
	.string "you know. You can't make out what\l"
	.string "it means.$"

HoennSeek_Text_RegiSealRead:
	.string "With the inscription from the\n"
	.string "RUINS OF ALPH, you can read it:\p"
	.string "LET THE OLDEST OF THE DEEP AND\n"
	.string "THE GREATEST OF THE SEA STAND\l"
	.string "BEFORE THIS STONE.$"

HoennSeek_Text_RegiSealStir:
	.string "Something huge moved, deep\n"
	.string "behind the boulder…\p"
	.string "One heavy step, then another.\n"
	.string "Then silence.$"

HoennSeek_Text_RegiSealStays:
	.string "The boulder doesn't budge.$"

HoennSeek_Text_RegiSealCry:
	.string "RELICANTH and WAILORD cry out\n"
	.string "from their POKé BALLS!\p"
	.string "The boulder starts to tremble…$"

HoennSeek_Text_RegiSealOpen:
	.string "The boulder rolled aside!\n"
	.string "The way in is open.$"

HoennSeek_Text_ArceusWaits:
	.string "ARCEUS watches you, perfectly\n"
	.string "still and silent.\p"
	.string "It seems to be waiting for words\n"
	.string "older than these RUINS.$"

HoennSeek_Text_CallWishes:
	.string "Hi, {PLAYER}! It's MAY.\p"
	.string "An old man from MOSSDEEP's SPACE\n"
	.string "CENTER phoned PROF. BIRCH. He's an\l"
	.string "old stargazing friend of his.\p"
	.string "He said a trainer's been making\n"
	.string "wishes on shooting stars, in all\l"
	.string "three places from his old story!\p"
	.string "That's you, isn't it? In the story,\n"
	.string "the wish comes true at the white\l"
	.string "rock on MT. MOON…\p"
	.string "on the night the CLEFAIRY dance.\n"
	.string "Good luck!$"

HoennSeek_Text_CallDeoxys:
	.string "Hey, {PLAYER}, it's BRENDAN.\p"
	.string "The SPACE CENTER phoned Dad to\n"
	.string "borrow a meteorite sample, and\l"
	.string "mentioned their signal.\p"
	.string "They gave you the ferry pass to\n"
	.string "BIRTH ISLAND?\p"
	.string "Dad says if something fell from\n"
	.string "space, it may not like visitors.\l"
	.string "Be careful out there!$"

HoennSeek_Text_CallRegis:
	.string "Hi, {PLAYER}! It's MAY.\p"
	.string "STEVEN phoned PROF. BIRCH from\n"
	.string "the SINJOH RUINS!\p"
	.string "He said the ground shook, and a\n"
	.string "boulder rolled away from one of\l"
	.string "the old doors in the cliffs.\p"
	.string "With RELICANTH and WAILORD, just\n"
	.string "like the braille said! You really\l"
	.string "did it, didn't you?$"
