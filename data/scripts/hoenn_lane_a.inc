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
