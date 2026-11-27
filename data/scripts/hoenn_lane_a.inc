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
	.string "UNOWN are gathering around the\n"
	.string "stone!$"

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
	.string "The letters settle back into the\n"
	.string "stone.$"

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
