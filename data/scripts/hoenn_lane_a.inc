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
	case HOENN_CALL_AMPHAROS, HoennSeek_EventScript_CallAmpharos @ part 32
	goto HoennSeek_EventScript_PhoneEventLaneB @ lane B's calls (hoenn_lane_b.inc)

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
