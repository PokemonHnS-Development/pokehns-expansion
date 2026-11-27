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
	case HOENN_CALL_AMPHAROS, HoennSeek_EventScript_CallAmpharos @ part 32
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
@ The stranded AMPHAROS: at night it stands on a sea rock off Route 40 (32,33),
@ blinking its tail. AMPHY, at the top of the lighthouse, watches that light
@ after dark. (Route 41 already has 64 object templates, the most a map can
@ hold, so it lives on Route 40, the sea right below the lighthouse. Its
@ template elevation is 4 so it's drawn above the rock's top layer; standing
@ on an elevation-0 rock tile, it can still be talked to from the water.) Talking to it starts a scaled battle (Tail Glow); knocked out it
@ rests on its rock until the next night, caught it's done (May calls).
@ ============================================================================

@ One `call` at the top of Route 41's OnTransition.
HoennSeek_EventScript_Route41Night::
	setflag FLAG_HOENN_HIDE_LANTURN_LIGHT
	call_if_set FLAG_HOENN_LAGOON_FOUND, HoennSeek_EventScript_ArmLagoonCave
	goto_if_set FLAG_HOENN_LAGOON_FOUND, HoennSeek_EventScript_Route41NightDone
	gettimeofday
	goto_if_ne VAR_0x8000, HOENN_TIME_NIGHT, HoennSeek_EventScript_Route41NightDone
	clearflag FLAG_HOENN_HIDE_LANTURN_LIGHT
HoennSeek_EventScript_Route41NightDone:
	return

@ One `call` at the top of Route 40's OnTransition.
HoennSeek_EventScript_Route40Night::
	setflag FLAG_HOENN_HIDE_STRANDED_AMPHAROS
	goto_if_set FLAG_HOENN_CAUGHT_STRANDED_AMPHAROS, HoennSeek_EventScript_Route41NightDone
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

@ The old stone (bg events on 11-12, 6). Part 34b adds the feathers.
HoennSeek_EventScript_LagoonShrine::
	lockall
	msgbox HoennSeek_Text_LagoonShrine, MSGBOX_DEFAULT
	goto_if_unset FLAG_HOENN_SLOWKING_PROPHECY, HoennSeek_EventScript_LagoonShrineEnd
	msgbox HoennSeek_Text_LagoonShrineProphecy, MSGBOX_DEFAULT
HoennSeek_EventScript_LagoonShrineEnd:
	releaseall
	end

@ The stranded AMPHAROS on its rock off Route 40 (32,33).
HoennSeek_EventScript_StrandedAmpharos::
	lock
	faceplayer
	goto_if_set FLAG_HOENN_DAILY_STRANDED_AMPHAROS, HoennSeek_EventScript_StrandedAmpharosResting
	playmoncry SPECIES_AMPHAROS, CRY_MODE_ENCOUNTER
	msgbox HoennSeek_Text_StrandedAmpharos, MSGBOX_DEFAULT
	waitmoncry
	closemessage
	setvar VAR_0x8004, SPECIES_AMPHAROS
	special HoennSetupScaledWildBattle
	setvar VAR_0x8005, MOVE_TAIL_GLOW
	setvar VAR_0x8006, FALSE
	setvar VAR_0x8007, ITEM_NONE
	special HoennTuneWildMon
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, HoennSeek_EventScript_StrandedAmpharosCaught
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, HoennSeek_EventScript_StrandedAmpharosEnd
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, HoennSeek_EventScript_StrandedAmpharosEnd
	setflag FLAG_HOENN_DAILY_STRANDED_AMPHAROS
	msgbox HoennSeek_Text_StrandedAmpharosDown, MSGBOX_DEFAULT
	release
	end

HoennSeek_EventScript_StrandedAmpharosCaught:
	setflag FLAG_HOENN_CAUGHT_STRANDED_AMPHAROS
	removeobject LOCALID_HOENN_STRANDED_AMPHAROS
HoennSeek_EventScript_StrandedAmpharosEnd:
	release
	end

HoennSeek_EventScript_StrandedAmpharosResting:
	playmoncry SPECIES_AMPHAROS, CRY_MODE_WEAK
	msgbox HoennSeek_Text_StrandedAmpharosResting, MSGBOX_DEFAULT
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
	goto_if_set FLAG_HOENN_CAUGHT_STRANDED_AMPHAROS, HoennSeek_EventScript_AmphyContent
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
	.string "Its light glows somewhere far\n"
	.string "inside…$"

HoennSeek_Text_LagoonLanturn:
	.string "The LANTURN's light sways slowly\n"
	.string "over the water, toward the stone\l"
	.string "on the beach.$"

HoennSeek_Text_LagoonChinchou:
	.string "The CHINCHOU's lights blink in\n"
	.string "time with the others.$"

HoennSeek_Text_LagoonShrine:
	.string "An old stone, worn smooth by the\n"
	.string "waves.\p"
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
	.string "It's frightened! It lashes out!$"

HoennSeek_Text_StrandedAmpharosDown:
	.string "The AMPHAROS huddled down on its\n"
	.string "rock. Its light has gone dim.\p"
	.string "It'll still be stuck out here\n"
	.string "tomorrow night…$"

HoennSeek_Text_StrandedAmpharosResting:
	.string "The AMPHAROS is huddled on its\n"
	.string "rock, resting. Its light is dim.$"

HoennSeek_Text_AmphyWatchesLight:
	.string "AMPHY is gazing out to sea.\p"
	.string "Out on the dark water, past the\n"
	.string "beach, a tiny light blinks…\l"
	.string "On, off. On, off.\p"
	.string "AMPHY: Palu… Palulu?$"

HoennSeek_Text_AmphyContent:
	.string "AMPHY is gazing out to sea.\p"
	.string "The light on the water is gone.\n"
	.string "AMPHY: Palulu!$"

HoennSeek_Text_CallAmpharos:
	.string "{PLAYER}? It's MAY!\p"
	.string "JASMINE from OLIVINE keeps the\n"
	.string "LEAGUE posted on her lighthouse,\l"
	.string "and Dad reads all the reports.\p"
	.string "She says AMPHY kept staring at a\n"
	.string "second light out at sea every\l"
	.string "night. A stranded AMPHAROS!\p"
	.string "Then a trainer from out of town\n"
	.string "brought it in off its rock on\l"
	.string "ROUTE 40.\p"
	.string "That was you, right? AMPHY must\n"
	.string "be so happy!$"
